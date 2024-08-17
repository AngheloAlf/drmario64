/**
 * Original filename: calc.c
 */

#include "calc.h"

#include "include_asm.h"
#include "macros_defines.h"
#include "unknown_structs.h"
#include "main_segment_variables.h"
#include "066840.h"

static s32 randomindex;
static s32 randomtable[55];

s32 D_800AAE60[] = {
    0,  1,  2,  3,  4,  5,  6,  8,  9,  10, 11, 12, 13, 14, 15, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 28,
    29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54,
    54, 55, 56, 57, 58, 59, 60, 61, 61, 62, 63, 64, 65, 66, 66, 67, 68, 69, 69, 70, 71, 72, 73, 73, 74, 75,
    75, 76, 77, 78, 78, 79, 80, 80, 81, 82, 82, 83, 83, 84, 85, 85, 86, 87, 87, 88, 88, 89, 90,
};

f32 D_800AAFF4[] = {
    0.0f,        0.008726868f, 0.017455066f, 0.026185922f, 0.03492077f, 0.043660942f, 0.05240778f, 0.06116262f,
    0.06992681f, 0.078701705f, 0.087488666f, 0.096289046f, 0.10510424f, 0.113935605f, 0.12278456f, 0.1316525f,
    0.14054084f, 0.149451f,    0.15838444f,  0.1673426f,   0.17632698f, 0.18533905f,  0.19438031f, 0.2034523f,
    0.21255656f, 0.22169466f,  0.23086819f,  0.24007876f,  0.249328f,   0.25861758f,  0.2679492f,  0.27732456f,
    0.2867454f,  0.2962135f,   0.30573067f,  0.3152988f,   0.3249197f,  0.33459532f,  0.3443276f,  0.3541186f,
    0.36397022f, 0.37388468f,  0.38386405f,  0.39391047f,  0.40402624f, 0.41421357f,  0.4244748f,  0.43481237f,
    0.4452287f,  0.45572627f,  0.46630767f,  0.47697553f,  0.4877326f,  0.49858162f,  0.5095255f,  0.52056706f,
    0.53170943f, 0.5429557f,   0.55430907f,  0.5657728f,   0.57735026f, 0.589045f,    0.6008606f,  0.6128008f,
    0.62486935f, 0.63707024f,  0.64940757f,  0.66188556f,  0.6745085f,  0.68728095f,  0.70020753f, 0.7132931f,
    0.72654253f, 0.7399611f,   0.75355405f,  0.767327f,    0.78128564f, 0.7954359f,   0.80978405f, 0.8243364f,
    0.83909965f, 0.8540807f,   0.8692867f,   0.8847253f,   0.90040404f, 0.9163312f,   0.9325151f,  0.9489646f,
    0.96568877f, 0.98269725f,  1.0f,         999.0f,
};

// "tanf"
f32 func_8007BC20(f32 arg0) {
    return sinf(arg0) / cosf(arg0);
}

// Matrix multiplication?
void func_8007BC54(f32 arg0[4][4], f32 arg1[4][4], f32 arg2[4][4]) {
    f32 sp8[4][4];
    s32 i;
    s32 j;
    s32 k;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            sp8[i][j] = 0.0f;

            for (k = 0; k < 4; k++) {
                sp8[i][j] += arg0[i][k] * arg1[k][j];
            }
        }
    }

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            arg2[i][j] = sp8[i][j];
        }
    }
}

/**
 * Creates a general rotation + translation matrix. Uses Y1 X2 Z3 Tait-Bryan angles
 * (https://en.wikipedia.org/wiki/Euler_angles#Rotation_matrix). `rotX`, `rotY`, `rotZ` are in degrees.
 */
void func_8007BD30(f32 m[4][4], f32 rotX, f32 rotY, f32 rotZ, f32 transX, f32 transY, f32 transZ) {
    f32 a2 = DEG_TO_RAD(rotX);
    f32 a1 = DEG_TO_RAD(rotY);
    f32 a3 = DEG_TO_RAD(rotZ);
    f32 s2 = sinf(a2);
    f32 s1 = sinf(a1);
    f32 s3 = sinf(a3);
    f32 c2 = cosf(a2);
    f32 c1 = cosf(a1);
    f32 c3 = cosf(a3);

    m[0][0] = (s3 * s2 * s1) + (c3 * c1);
    m[0][1] = s3 * c2;
    m[0][2] = (s3 * s2 * c1) - (c3 * s1);

    m[1][0] = (c3 * s2 * s1) - (s3 * c1);
    m[1][1] = c3 * c2;
    m[1][2] = (c3 * s2 * c1) + (s3 * s1);

    m[2][0] = c2 * s1;
    m[2][1] = -s2;
    m[2][2] = c2 * c1;

    m[3][0] = transX;
    m[3][1] = transY;
    m[3][2] = transZ;

    m[0][3] = m[1][3] = m[2][3] = 0.0f;
    m[3][3] = 1.0f;
}

/**
 * convert a pair of binary angles theta, phi to spherical coordinates x, y, z; origin (0,0) -> (0,0,1) and theta points
 * towards the downwards y direction
 */
void func_8007BEEC(s16 theta, s16 phi, f32 *x, f32 *y, f32 *z) {
    f32 thetaRad;
    f32 phiRad;
    f32 cosTheta;
    f32 sinTheta;
    f32 cosPhi;
    f32 sinPhi;

    thetaRad = func_8007C480(theta);
    phiRad = func_8007C480(phi);
    thetaRad = DEG_TO_RAD(thetaRad);
    phiRad = DEG_TO_RAD(phiRad);

    sinTheta = sinf(thetaRad);
    sinPhi = sinf(phiRad);
    cosTheta = cosf(thetaRad);
    cosPhi = cosf(phiRad);

    *x = cosTheta * sinPhi;
    *y = -sinTheta;
    *z = cosTheta * cosPhi;
}

void func_8007BFE0(f32 arg0, f32 arg1, f32 arg2, s16 *arg3, s16 *arg4) {
    s16 temp_s0 = angleF2S(func_8007C244(arg2, arg0));

    arg2 = sqrtf(SQ(arg0) + SQ(arg2));

    if (temp_s0 & 0x8000) {
        if (arg0 >= 0.0f) {
            arg2 = -arg2;
        }
    }

    *arg3 = angleF2S(func_8007C244(arg2, -arg1));
    *arg4 = temp_s0;
}

f32 func_8007C0C4(f32 arg0) {
    f32 var_fv1;
    s32 var_a0;
    u8 var_a1;
    f32 temp;

    var_a1 = 0;
    if (arg0 == 0.0f) {
        return 0.0f;
    }

    if (arg0 < 0.0f) {
        var_a1 = 0x10;
        arg0 = -arg0;
    }
    if (arg0 == 1.0f) {
        if (var_a1 == 0) {
            return 45.0f;
        } else {
            return -45.0f;
        }
    }
    if (arg0 > 1.0f) {
        arg0 = 1.0f / arg0;
        var_a1 |= 1;
    }

    temp = arg0;

    var_a0 = temp * 100.0f;
    var_a0 = D_800AAE60[var_a0];

    while (D_800AAFF4[var_a0] <= temp) {
        var_a0++;
    }

    var_a0--;
    var_fv1 = var_a0;

    if (temp != D_800AAFF4[var_a0]) {
        temp -= D_800AAFF4[var_a0];
        temp /= D_800AAFF4[var_a0 + 1] - D_800AAFF4[var_a0];
        var_fv1 += temp;
    }

    var_fv1 = var_fv1 / 2.0f;
    if (var_a1 & 1) {
        var_fv1 = 90.0f - var_fv1;
    }
    if (var_a1 & 0x10) {
        var_fv1 = -var_fv1;
    }
    return var_fv1;
}

f32 func_8007C244(f32 arg0, f32 arg1) {
    f32 temp_ft0;
    f32 var_fv1;
    s32 var_a0;
    s32 var_a1;

    var_a1 = 0;
    if (arg0 == 0.0f) {
        if (arg1 == 0.0f) {
            return 0.0f;
        }

        if (arg1 < 0.0f) {
            return -90.0f;
        } else {
            return 90.0f;
        }
    }

    if (arg0 < 0.0f) {
        var_a1 = 0x110;
        arg0 = -arg0;
    }

    if (arg1 == 0.0f) {
        if (var_a1 == 0) {
            return 0.0f;
        } else {
            return 180.0f;
        }
    }

    if (arg1 < 0.0f) {
        var_a1 ^= 0x10;
        arg1 = -arg1;
    }
    if (arg0 < arg1) {
        temp_ft0 = arg0;
        arg0 = arg1;
        arg1 = temp_ft0;
        var_a1 ^= 1;
    }
    temp_ft0 = arg1 / arg0;

    var_a0 = temp_ft0 * 100.0f;
    var_a0 = D_800AAE60[var_a0];
    while (D_800AAFF4[var_a0] <= temp_ft0) {
        var_a0++;
    }

    var_a0--;
    var_fv1 = var_a0;
    if (temp_ft0 != D_800AAFF4[var_a0]) {
        temp_ft0 -= D_800AAFF4[var_a0];
        temp_ft0 /= D_800AAFF4[var_a0 + 1] - D_800AAFF4[var_a0];
        var_fv1 += temp_ft0;
    }

    var_fv1 /= 2.0f;
    if (var_a1 & 1) {
        var_fv1 = 90.0f - var_fv1;
    }
    if (var_a1 & 0x10) {
        var_fv1 = -var_fv1;
    }
    if (var_a1 & 0x100) {
        var_fv1 += 180.0f;
    }
    if (var_fv1 > 180.0f) {
        var_fv1 -= 360.0f;
    }

    if (var_fv1 < -180.0f) {
        var_fv1 += 360.0f;
    }
    return var_fv1;
}

/**
 * Original name most likely angleS2F
 *
 * Convert binary angle to float angle in degrees.
 */
f32 func_8007C480(s16 arg0) {
    return ((f32)arg0) * (360.0 / 0x10000);
}

/**
 * Original name: angleF2S
 *
 * Convert float angle in degrees to a binary angle.
 */
s16 angleF2S(f32 arg0) {
    return (s32)(f32)(arg0 * (0x10000 / 360.0));
}

/**
 * Convert an Mtx to an MtxF.
 */
void func_8007C4D8(f32 mtxf[4][4], Mtx *mtx) {
    s32 i;

    for (i = 0; i < 4; i++) {
        mtxf[i][0] = (f32)mtx->m[i][0] / 0x8000;
        mtxf[i][1] = (f32)mtx->m[i][1] / 0x8000;
        mtxf[i][2] = (f32)mtx->m[i][2] / 0x8000;
        mtxf[i][3] = (f32)mtx->m[i][3] / 0x8000;
    }
}

/**
 * Convert an Mtx to an MtxF.
 */
void func_8007C540(Mtx *mtx, f32 mtxf[4][4]) {
    s32 i;

    for (i = 0; i < 4; i++) {
        mtx->m[i][0] = mtxf[i][0] * 0x8000;
        mtx->m[i][1] = mtxf[i][1] * 0x8000;
        mtx->m[i][2] = mtxf[i][2] * 0x8000;
        mtx->m[i][3] = mtxf[i][3] * 0x8000;
    }
}

/**
 * Convert an Mtx to an MtxF, and set the last row to (0, 0, 0, 1).
 */
void func_8007C5A8(Mtx *mtx, f32 mtxf[4][4]) {
    s32 i;

    for (i = 0; i < 3; i++) {
        mtx->m[i][0] = mtxf[i][0] * 0x8000;
        mtx->m[i][1] = mtxf[i][1] * 0x8000;
        mtx->m[i][2] = mtxf[i][2] * 0x8000;
        mtx->m[i][3] = mtxf[i][3] * 0x8000;
    }
    mtx->m[3][0] = 0;
    mtx->m[3][1] = 0;
    mtx->m[3][2] = 0;
    mtx->m[3][3] = 1.0f * 0x8000;
}

/**
 * Rotate `(pointX, pointY)` about `(centreX, centreY)` by `angle` degrees, modifying in-place.
 */
void func_8007C624(f32 angle, f32 centreX, f32 centreY, f32 *pointX, f32 *pointY) {
    f32 angleRad = angle * M_DTOR;
    f32 sin = sinf(angleRad);
    f32 cos = cosf(angleRad);
    f32 diffX = *pointX - centreX;
    f32 diffY = *pointY - centreY;

    *pointX = (diffX * cos) - (diffY * sin) + centreX;
    *pointY = (diffY * cos) + (diffX * sin) + centreY;
}

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/calc", func_8007C6D8);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/calc", func_8007C6D8);
#endif

#if VERSION_CN
f32 func_8007C6D8(f32 arg0, f32 arg1) {
    s32 temp_s0 = angleF2S(arg0) & 0xFFFF;
    s32 temp_a1 = angleF2S(arg1) & 0xFFFF;
    s32 var_v0;
    s32 var_a0;
    s32 var_v1;

    if (temp_s0 < temp_a1) {
        var_v1 = temp_s0 + 0x10000;
        var_a0 = temp_a1;
    } else {
        var_v1 = temp_s0;
        var_a0 = temp_a1 + 0x10000;
    }

    temp_a1 -= temp_s0;
    var_a0 -= var_v1;

    var_v1 = (temp_a1 >= 0) ? temp_a1 : -temp_a1;

    if (var_a0 >= 0) {
        if (var_a0 < var_v1) {
            var_v0 = var_a0;
        } else {
            var_v0 = temp_a1;
        }
    } else {
        if (-var_a0 < var_v1) {
            var_v0 = var_a0;
        } else {
            var_v0 = temp_a1;
        }
    }

    return func_8007C480(var_v0);
}
#endif

/**
 * Calculate the distance between two points.
 */
f32 func_8007C780(f32 aX, f32 aY, f32 aZ, f32 bX, f32 bY, f32 bZ) {
    f32 diffX = bX - aX;
    f32 diffY = bY - aY;
    f32 diffZ = bZ - aZ;

    return sqrtf((diffX * diffX) + (diffY * diffY) + (diffZ * diffZ));
}

f32 func_8007C7E8(f32 arg0, f32 *arg1) {
    f32 temp_ft1 = arg1[0];
    f32 temp_ft0 = arg1[1];
    f32 var_ft1;
    s32 temp_ft2;
    s32 temp_v1;
    s32 index;

    if (arg0 < temp_ft1) {
        arg0 = temp_ft1;
    }
    if (temp_ft0 < arg0) {
        arg0 = temp_ft0;
    }

    temp_ft2 = (arg0 - temp_ft1) * 65536.0f / (temp_ft0 - temp_ft1);
    index = temp_ft2 >> 8;
    temp_v1 = temp_ft2 & 0xFF;

    var_ft1 = arg1[index + 2];
    if (temp_v1 != 0) {
        var_ft1 = temp_v1 * (arg1[index + 3] - var_ft1) / 256.0 + var_ft1;
    }
    return var_ft1;
}

f32 func_8007C894(f32 arg0, f32 *arg1, f32 arg2, f32 arg3) {
    f32 temp_ft1_2;
    f32 temp_ft2;
    f32 var_ft0;
    f32 var_fv0;
    s32 temp_v1;
    s32 var_a2;

    temp_ft2 = arg1[0];
    temp_ft1_2 = arg1[1];
    if (arg0 < temp_ft2) {
        arg0 = temp_ft2;
    }
    if (temp_ft1_2 < arg0) {
        arg0 = temp_ft1_2;
    }

    var_a2 = (s32)(((arg2 - temp_ft2) * 65536.0f) / (temp_ft1_2 - temp_ft2)) >> 8;
    temp_v1 = (s32)(((arg3 - temp_ft2) * 65536.0f) / (temp_ft1_2 - temp_ft2)) >> 8;

    var_ft0 = 9999999.0f;

    while (var_a2 < temp_v1) {
        var_fv0 = arg0 - arg1[var_a2 + 3];
        if (var_fv0 < 0.0f) {
            var_fv0 = -var_fv0;
        }

        if (!(var_ft0 > var_fv0)) {
            break;
        }
        var_ft0 = var_fv0;
        var_a2 += 1;
    }

    var_fv0 = 2.0f * (arg0 - arg1[var_a2 + 1]) / (arg1[var_a2 + 3] - arg1[var_a2 + 1]) + (var_a2 - 1);
    var_fv0 = temp_ft2 + var_fv0 * (temp_ft1_2 - temp_ft2) / 256.0f;
    return var_fv0;
}

void func_8007C9C8(f32 arg0[4][4], f32 *arg1, f32 *arg2, f32 *arg3) {
    f32 var_fs0;
    f32 var_fs1;
    f32 var_fs2;

    if ((arg0[2][0] == 0.0f) && (arg0[2][2] == 0.0f)) {
        var_fs0 = (arg0[2][1] > 0.0f) ? -16384.0f : 16384.0f;
        var_fs1 = func_8007C244(arg0[0][0], -arg0[0][2]);
        var_fs2 = 0.0f;
    } else {
        f32 var_fs0_2 = sqrtf(SQ(arg0[2][0]) + SQ(arg0[2][2]));

        var_fs2 = func_8007C244(arg0[1][1], arg0[0][1]);
        var_fs1 = func_8007C244(arg0[2][2], arg0[2][0]);
        var_fs0 = func_8007C244(var_fs0_2, -arg0[2][1]);
    }

    *arg1 = var_fs0;
    *arg2 = var_fs1;
    *arg3 = var_fs2;
}

void func_8007CAFC(Mtx *arg0, s16 *arg1, s16 *arg2, s16 *arg3) {
    s32 var_s0;
    s32 var_s2;
    s32 var_s3;

    if ((arg0->m[2][0] == 0) && (arg0->m[2][2] == 0)) {
        var_s0 = (arg0->m[2][1] > 0) ? -0x4000 : 0x4000;
        var_s3 = 0;
        var_s2 = func_8007EAEC(arg0->m[0][0], -arg0->m[0][2]);
    } else {
        s32 temp_s0 = func_8007F720(arg0->m[2][0], arg0->m[2][2]);

        var_s3 = func_8007EAEC(arg0->m[1][1], arg0->m[0][1]);
        var_s2 = func_8007EAEC(arg0->m[2][2], arg0->m[2][0]);
        var_s0 = func_8007EAEC(temp_s0, -arg0->m[2][1]);
    }

    *arg1 = var_s0;
    *arg2 = var_s2;
    *arg3 = var_s3;
}

/**
 * Multiply the vector `(inX, inY, inZ)` by the matrix `m` and write to `(outX, outY, outZ)`.
 *
 * Caries out a general affine transformation.
 */
void func_8007CBE4(f32 m[4][4], f32 inX, f32 inY, f32 inZ, f32 *outX, f32 *outY, f32 *outZ) {
    f32 vec[3];
    s32 i;

    for (i = 0; i < 3; i++) {
        vec[i] = m[3][i] + ((m[0][i] * inX) + (m[1][i] * inY) + (m[2][i] * inZ));
    }

    *outX = vec[0];
    *outY = vec[1];
    *outZ = vec[2];
}

/**
 * Shift the vector `(inX, inY, inZ)` by the negative of the translational part of the matrix `m` and multiply it by the
 * linear part of `m` and write to `(outX, outY, outZ)`.
 *
 * (This is equivalent to multiplying by the inverse of `m` if the linear part of `m` is orthogonal.)
 */
void func_8007CC68(f32 m[4][4], f32 inX, f32 inY, f32 inZ, f32 *outX, f32 *outY, f32 *outZ) {
    f32 vec[3];
    f32 tempX = inX - m[3][0];
    f32 tempY = inY - m[3][1];
    f32 tempZ = inZ - m[3][2];
    s32 i;

    for (i = 0; i < 3; i++) {
        vec[i] = (m[i][0] * tempX) + (m[i][1] * tempY) + (m[i][2] * tempZ);
    }

    *outX = vec[0];
    *outY = vec[1];
    *outZ = vec[2];
}

/**
 * Multiply the vector `(inX, inY, inZ)` by the linear part of the matrix `m` and write to `(outX, outY, outZ)`.
 *
 * (This is equivalent to multiplying by the inverse of the linear part of `m`, if the linear part of `m` is
 * orthogonal.)
 */
void func_8007CCFC(f32 m[4][4], f32 inX, f32 inY, f32 inZ, f32 *outX, f32 *outY, f32 *outZ) {
    f32 vec[3];
    s32 i;

    for (i = 0; i < 3; i++) {
        vec[i] = (m[i][0] * inX) + (m[i][1] * inY) + (m[i][2] * inZ);
    }
    *outX = vec[0];
    *outY = vec[1];
    *outZ = vec[2];
}

void func_8007CD78(f32 arg0[4][4], f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7) {
    f32 temp_fs4;
    f32 temp_fs5;
    f32 var_fs2;

    func_8007CFB4(&arg2, &arg3, &arg4);

    arg1 = DEG_TO_RAD(arg1);
    temp_fs5 = sinf(arg1);
    temp_fs4 = cosf(arg1);

    var_fs2 = sqrtf((arg2 * arg2) + (arg4 * arg4));
    if (var_fs2 != 0.0f) {
        arg0[0][0] = (arg4 * temp_fs4 - temp_fs5 * arg3 * arg2) * (1.0f / var_fs2);
        arg0[0][1] = temp_fs5 * var_fs2;
        arg0[0][2] = -(arg2 * temp_fs4 + temp_fs5 * arg3 * arg4) * (1.0f / var_fs2);
        arg0[0][3] = 0.0f;

        arg0[1][0] = -(arg4 * temp_fs5 + temp_fs4 * arg3 * arg2) * (1.0f / var_fs2);
        arg0[1][1] = temp_fs4 * var_fs2;
        arg0[1][2] = (arg2 * temp_fs5 - temp_fs4 * arg3 * arg4) * (1.0f / var_fs2);
        arg0[1][3] = 0.0f;

        arg0[2][0] = arg2;
        arg0[2][1] = arg3;
        arg0[2][2] = arg4;
        arg0[2][3] = 0.0f;

        arg0[3][0] = arg5;
        arg0[3][1] = arg6;
        arg0[3][2] = arg7;
        arg0[3][3] = 1.0f;
    } else {
        arg0[0][0] = temp_fs4;
        arg0[0][2] = -arg3 * temp_fs5;
        arg0[0][1] = 0.0f;
        arg0[0][3] = 0.0f;

        arg0[1][0] = -temp_fs5;
        arg0[1][1] = 0.0f;
        arg0[1][2] = -arg3 * temp_fs4;
        arg0[1][3] = 0.0f;

        arg0[2][0] = 0.0f;
        arg0[2][1] = arg3;
        arg0[2][2] = 0.0f;
        arg0[2][3] = 0.0f;

        arg0[3][0] = arg5;
        arg0[3][1] = arg6;
        arg0[3][2] = arg7;
        arg0[3][3] = 1.0f;
    }
}

/**
 * Normalise a vector consisting of three passed floats in-place. Returns the length of the original vector.
 */
f32 func_8007CFB4(f32 *x, f32 *y, f32 *z) {
    f32 tempX = *x;
    f32 tempY = *y;
    f32 tempZ = *z;
    f32 length = sqrtf((tempX * tempX) + (tempY * tempY) + (tempZ * tempZ));

    if (length != 0.0f) {
        tempX /= length;
        tempY /= length;
        tempZ /= length;
    }
    *x = tempX;
    *y = tempY;
    *z = tempZ;
    return length;
}

/**
 * Original name: randomize00
 */
void randomize00(void) {
    s32 oldValue1;
    s32 oldValue2;
    s32 newValue;
    s32 i;

    for (i = 0; i < 24; i++) {
        oldValue1 = randomtable[i];
        oldValue2 = randomtable[i + 31];
        newValue = oldValue1 - oldValue2;
        if (newValue < 0) {
            newValue += 0x10000;
        }
        randomtable[i] = newValue;
    }

    for (i = 24; i < ARRAY_COUNT(randomtable); i++) {
        oldValue1 = randomtable[i];
        oldValue2 = randomtable[i - 24];
        newValue = oldValue1 - oldValue2;
        if (newValue < 0) {
            newValue += 0x10000;
        }
        randomtable[i] = newValue;
    }
}

/**
 * Original name: randomseed
 */
void randomseed(s32 seed) {
    s32 value;
    s32 i;
    s32 index;

    randomtable[ARRAY_COUNT(randomtable) - 1] = seed;
    for (value = 1, i = 1; i < ARRAY_COUNT(randomtable); i++) {
        index = ((21 * i) % ARRAY_COUNT(randomtable)) - 1;
        randomtable[index] = value;
        value = seed - value;
        if (value < 0) {
            value += 0x10000;
        }
        seed = randomtable[index];
    }
    randomize00();
    randomize00();
    randomize00();
    randomize00();
    randomindex = 0;
}

/**
 * Original name: irandom
 */
s32 irandom(void) {
    randomindex++;

    if (randomindex >= ARRAY_COUNT(randomtable)) {
        randomize00();
        randomindex = 0;
    }
    return (u16)randomtable[randomindex];
}

/**
 * Original name: random
 */
s32 random(s32 arg0) {
    return (arg0 * irandom()) >> 0x10;
}

/**
 * Original filename: calc.c
 */

#include "calc.h"

#include "include_asm.h"
#include "macros_defines.h"

#include "calcsub.h"

static s32 randomindex;
static s32 randomtable[55];

s32 start_tbl[] = {
    0,  1,  2,  3,  4,  5,  6,  8,  9,  10, 11, 12, 13, 14, 15, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 28,
    29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54,
    54, 55, 56, 57, 58, 59, 60, 61, 61, 62, 63, 64, 65, 66, 66, 67, 68, 69, 69, 70, 71, 72, 73, 73, 74, 75,
    75, 76, 77, 78, 78, 79, 80, 80, 81, 82, 82, 83, 83, 84, 85, 85, 86, 87, 87, 88, 88, 89, 90,
};

f32 tan_table[] = {
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

/**
 * Original name: tanf
 */
f32 tanf(f32 a) {
    return sinf(a) / cosf(a);
}

/**
 * Original name: matrixMulF
 */
void matrixMulF(const f32 s[4][4], const f32 d[4][4], f32 r[4][4]) {
    f32 res[4][4];
    s32 i;
    s32 j;
    s32 k;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            res[i][j] = 0.0f;

            for (k = 0; k < 4; k++) {
                res[i][j] += s[i][k] * d[k][j];
            }
        }
    }

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            r[i][j] = res[i][j];
        }
    }
}

/**
 * Original name: makeMatrixF
 *
 * Creates a general rotation + translation matrix. Uses Y1 X2 Z3 Tait-Bryan angles
 * (https://en.wikipedia.org/wiki/Euler_angles#Rotation_matrix). `rx`, `ry`, `rz` are in degrees.
 * `lx`, `ly` and `lz` are the translation part.
 */
void makeMatrixF(f32 m[4][4], f32 rx, f32 ry, f32 rz, f32 lx, f32 ly, f32 lz) {
    f32 rad_x = DEG_TO_RAD(rx);
    f32 rad_y = DEG_TO_RAD(ry);
    f32 rad_z = DEG_TO_RAD(rz);
    f32 sx = sinf(rad_x);
    f32 sy = sinf(rad_y);
    f32 sz = sinf(rad_z);
    f32 cx = cosf(rad_x);
    f32 cy = cosf(rad_y);
    f32 cz = cosf(rad_z);

    m[0][0] = (sz * sx * sy) + (cz * cy);
    m[0][1] = sz * cx;
    m[0][2] = (sz * sx * cy) - (cz * sy);

    m[1][0] = (cz * sx * sy) - (sz * cy);
    m[1][1] = cz * cx;
    m[1][2] = (cz * sx * cy) + (sz * sy);

    m[2][0] = cx * sy;
    m[2][1] = -sx;
    m[2][2] = cx * cy;

    m[3][0] = lx;
    m[3][1] = ly;
    m[3][2] = lz;

    m[0][3] = m[1][3] = m[2][3] = 0.0f;
    m[3][3] = 1.0f;
}

/**
 * Original name: angle2vct
 *
 * convert a pair of binary angles theta, phi to spherical coordinates x, y, z; origin (0,0) -> (0,0,1) and theta points
 * towards the downwards y direction.
 *
 * `pit` is `theta`, `yaw` is `phi`.
 */
void angle2vct(s16 pit, s16 yaw, f32 *x, f32 *y, f32 *z) {
    f32 thetaRad = angleS2F(pit);
    f32 phiRad = angleS2F(yaw);
    f32 cosTheta;
    f32 sinTheta;
    f32 cosPhi;
    f32 sinPhi;

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

/**
 * Original name: vct2angle
 */
void vct2angle(f32 x, f32 y, f32 z, s16 *pit, s16 *yaw) {
    s16 temp_s0 = angleF2S(get_angleF(z, x));

    z = sqrtf(SQ(x) + SQ(z));

    if (temp_s0 & 0x8000) {
        if (x >= 0.0f) {
            z = -z;
        }
    }

    *pit = angleF2S(get_angleF(z, -y));
    *yaw = temp_s0;
}

/**
 * Original name: atanF
 */
f32 atanF(f32 t) {
    f32 ang;
    s32 i;
    u8 flag;
    f32 wk;

    flag = 0;
    if (t == 0.0f) {
        return 0.0f;
    }

    if (t < 0.0f) {
        flag = 0x10;
        t = -t;
    }
    if (t == 1.0f) {
        if (flag == 0) {
            return 45.0f;
        } else {
            return -45.0f;
        }
    }
    if (t > 1.0f) {
        t = 1.0f / t;
        flag |= 1;
    }

    wk = t;

    i = wk * 100.0f;
    i = start_tbl[i];

    while (tan_table[i] <= wk) {
        i++;
    }

    i--;
    ang = i;

    if (wk != tan_table[i]) {
        wk -= tan_table[i];
        wk /= tan_table[i + 1] - tan_table[i];
        ang += wk;
    }

    ang = ang / 2.0f;
    if (flag & 1) {
        ang = 90.0f - ang;
    }
    if (flag & 0x10) {
        ang = -ang;
    }
    return ang;
}

/**
 * Original name: get_angleF
 */
f32 get_angleF(f32 x, f32 y) {
#define ATAN2_FLG_SWAP 0x1
#define ATAN2_FLG_NEGY 0x10
#define ATAN2_FLG_NEGX 0x100

    f32 wk;
    f32 ang;
    s32 i;
    u32 flag;

    flag = 0;
    if (x == 0.0f) {
        if (y == 0.0f) {
            return 0.0f;
        }

        if (y < 0.0f) {
            return -90.0f;
        } else {
            return 90.0f;
        }
    }

    if (x < 0.0f) {
        x = -x;
        flag = ATAN2_FLG_NEGX | ATAN2_FLG_NEGY;
    }

    if (y == 0.0f) {
        if (flag == 0) {
            return 0.0f;
        } else {
            return 180.0f;
        }
    }

    if (y < 0.0f) {
        flag ^= ATAN2_FLG_NEGY;
        y = -y;
    }
    if (x < y) {
        wk = x;
        x = y;
        y = wk;
        flag ^= ATAN2_FLG_SWAP;
    }
    wk = y / x;

    i = wk * 100.0f;
    i = start_tbl[i];
    while (tan_table[i] <= wk) {
        i++;
    }

    i--;
    ang = i;
    if (wk != tan_table[i]) {
        wk -= tan_table[i];
        wk /= tan_table[i + 1] - tan_table[i];
        ang += wk;
    }

    ang /= 2.0f;
    if (flag & ATAN2_FLG_SWAP) {
        ang = 90.0f - ang;
    }
    if (flag & ATAN2_FLG_NEGY) {
        ang = -ang;
    }
    if (flag & ATAN2_FLG_NEGX) {
        ang += 180.0f;
    }
    if (ang > 180.0f) {
        ang -= 360.0f;
    }

    if (ang < -180.0f) {
        ang += 360.0f;
    }
    return ang;

#undef ATAN2_FLG_SWAP
#undef ATAN2_FLG_NEGY
#undef ATAN2_FLG_NEGX
}

/**
 * Original name: angleS2F
 *
 * Convert binary angle to float angle in degrees.
 */
f32 angleS2F(s16 a) {
    return ((f32)(s32)a) * (360.0 / 0x10000);
}

/**
 * Original name: angleF2S
 *
 * Convert float angle in degrees to a binary angle.
 */
s16 angleF2S(f32 a) {
    return (s32)(f32)(a * (0x10000 / 360.0));
}

/**
 * Original name: matrixL2F
 *
 * Convert an Mtx to an MtxF.
 */
void matrixL2F(f32 mtxf[4][4], CONST_ARG Mtx *mtx) {
    s32 i;

    for (i = 0; i < 4; i++) {
        mtxf[i][0] = (f32)mtx->m[i][0] / 0x8000;
        mtxf[i][1] = (f32)mtx->m[i][1] / 0x8000;
        mtxf[i][2] = (f32)mtx->m[i][2] / 0x8000;
        mtxf[i][3] = (f32)mtx->m[i][3] / 0x8000;
    }
}

/**
 * Original name: matrixL2F
 *
 * Convert an Mtx to an MtxF.
 */
void matrixF2L(Mtx *mtx, CONST_ARG f32 mtxf[4][4]) {
    s32 i;

    for (i = 0; i < 4; i++) {
        mtx->m[i][0] = mtxf[i][0] * 0x8000;
        mtx->m[i][1] = mtxf[i][1] * 0x8000;
        mtx->m[i][2] = mtxf[i][2] * 0x8000;
        mtx->m[i][3] = mtxf[i][3] * 0x8000;
    }
}

/**
 * Original name: matrixF2Lloc0
 *
 * Convert an Mtx to an MtxF, and set the last row to (0, 0, 0, 1).
 */
void matrixF2Lloc0(Mtx *mtx, CONST_ARG f32 mtxf[4][4]) {
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
 * Original name: rotpoint
 *
 * Rotate `(pointX, pointY)` about `(centreX, centreY)` by `angle` degrees, modifying in-place.
 */
void rotpoint(f32 angle, f32 centreX, f32 centreY, f32 *pointX, f32 *pointY) {
    f32 angleRad = angle * M_DTOR;
    f32 sin = sinf(angleRad);
    f32 cos = cosf(angleRad);
    f32 diffX = *pointX - centreX;
    f32 diffY = *pointY - centreY;

    *pointX = (diffX * cos) - (diffY * sin) + centreX;
    *pointY = (diffY * cos) + (diffX * sin) + centreY;
}

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/calc", defangle);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/calc", defangle);
#endif

#if VERSION_CN
/**
 * Original name: defangle
 */
f32 defangle(f32 arg0, f32 arg1) {
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

    return angleS2F(var_v0);
}
#endif

/**
 * Original name: distance
 *
 * Calculate the distance between two points.
 */
f32 distance(f32 aX, f32 aY, f32 aZ, f32 bX, f32 bY, f32 bZ) {
    f32 diffX = bX - aX;
    f32 diffY = bY - aY;
    f32 diffZ = bZ - aZ;

    return sqrtf((diffX * diffX) + (diffY * diffY) + (diffZ * diffZ));
}

/**
 * Original name: calcTableF
 */
f32 calcTableF(f32 x, const f32 table[]) {
    f32 min = table[0];
    f32 max = table[1];
    f32 res;
    s32 temp_ft2;
    s32 temp_v1;
    s32 index;

#if 0
    long n; // r4
    long h; // r1+0x8
    long l; // r4
#endif

    if (x < min) {
        x = min;
    }
    if (max < x) {
        x = max;
    }

    temp_ft2 = (x - min) * 0x10000 / (max - min);
    index = temp_ft2 >> 8;
    temp_v1 = temp_ft2 & 0xFF;

    res = table[index + 2];
    if (temp_v1 != 0) {
        res = temp_v1 * (table[index + 3] - res) / DOUBLE_LITERAL(0x100) + res;
    }
    return res;
}

/**
 * Original name: calcTableF_Rev
 */
f32 calcTableF_Rev(f32 x, const f32 table[], f32 s, f32 e) {
    f32 max;
    f32 min;
    f32 old;
    f32 res;
    s32 temp_v1;
    s32 var_a2;

    min = table[0];
    max = table[1];
    if (x < min) {
        x = min;
    }
    if (max < x) {
        x = max;
    }

    var_a2 = (s32)(((s - min) * 0x10000) / (max - min)) >> 8;
    temp_v1 = (s32)(((e - min) * 0x10000) / (max - min)) >> 8;

    old = 9999999.0f;

    while (var_a2 < temp_v1) {
        res = x - table[var_a2 + 3];
        if (res < 0.0f) {
            res = -res;
        }

        if (!(old > res)) {
            break;
        }
        old = res;
        var_a2 += 1;
    }

    res = 2.0f * (x - table[var_a2 + 1]) / (table[var_a2 + 3] - table[var_a2 + 1]) + (var_a2 - 1);
    res = min + res * (max - min) / 0x100;
    return res;
}

/**
 * Original name: mtx2angleF
 */
void mtx2angleF(CONST_ARG f32 m[4][4], f32 *rx, f32 *ry, f32 *rz) {
    f32 xr;
    f32 yr;
    f32 zr;

    if ((m[2][0] == 0.0f) && (m[2][2] == 0.0f)) {
        xr = (m[2][1] > 0.0f) ? -0x4000 : 0x4000;
        yr = get_angleF(m[0][0], -m[0][2]);
        zr = 0.0f;
    } else {
        f32 wk = sqrtf(SQ(m[2][0]) + SQ(m[2][2]));

        zr = get_angleF(m[1][1], m[0][1]);
        yr = get_angleF(m[2][2], m[2][0]);
        xr = get_angleF(wk, -m[2][1]);
    }

    *rx = xr;
    *ry = yr;
    *rz = zr;
}

void func_8007CAFC(CONST_ARG Mtx *arg0, s16 *arg1, s16 *arg2, s16 *arg3) {
    s32 var_s0;
    s32 var_s2;
    s32 var_s3;

    if ((arg0->m[2][0] == 0) && (arg0->m[2][2] == 0)) {
        var_s0 = (arg0->m[2][1] > 0) ? -0x4000 : 0x4000;
        var_s3 = 0;
        var_s2 = get_angle(arg0->m[0][0], -arg0->m[0][2]);
    } else {
        s32 temp_s0 = sqrt_a2b2(arg0->m[2][0], arg0->m[2][2]);

        var_s3 = get_angle(arg0->m[1][1], arg0->m[0][1]);
        var_s2 = get_angle(arg0->m[2][2], arg0->m[2][0]);
        var_s0 = get_angle(temp_s0, -arg0->m[2][1]);
    }

    *arg1 = var_s0;
    *arg2 = var_s2;
    *arg3 = var_s3;
}

/**
 * Original name: lc2wcF
 *
 * Multiply the vector `(inX, inY, inZ)` by the matrix `m` and write to `(outX, outY, outZ)`.
 *
 * Caries out a general affine transformation.
 */
void lc2wcF(const f32 m[4][4], f32 inX, f32 inY, f32 inZ, f32 *outX, f32 *outY, f32 *outZ) {
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
 * Original name: wc2lcF
 *
 * Shift the vector `(inX, inY, inZ)` by the negative of the translational part of the matrix `m` and multiply it by the
 * linear part of `m` and write to `(outX, outY, outZ)`.
 *
 * (This is equivalent to multiplying by the inverse of `m` if the linear part of `m` is orthogonal.)
 */
void wc2lcF(const f32 m[4][4], f32 inX, f32 inY, f32 inZ, f32 *outX, f32 *outY, f32 *outZ) {
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
 * Original name: wc2lcF0
 *
 * Multiply the vector `(inX, inY, inZ)` by the linear part of the matrix `m` and write to `(outX, outY, outZ)`.
 *
 * (This is equivalent to multiplying by the inverse of the linear part of `m`, if the linear part of `m` is
 * orthogonal.)
 */
void wc2lcF0(const f32 m[4][4], f32 inX, f32 inY, f32 inZ, f32 *outX, f32 *outY, f32 *outZ) {
    f32 vec[3];
    s32 i;

    for (i = 0; i < 3; i++) {
        vec[i] = (m[i][0] * inX) + (m[i][1] * inY) + (m[i][2] * inZ);
    }
    *outX = vec[0];
    *outY = vec[1];
    *outZ = vec[2];
}

/**
 * Original name: makeMatrixVctZ
 */
void makeMatrixVctZ(f32 mf[4][4], f32 a, f32 x, f32 y, f32 z, f32 lx, f32 ly, f32 lz) {
    f32 c;
    f32 s;
    f32 h;

    normalVct(&x, &y, &z);

    a = DEG_TO_RAD(a);
    s = sinf(a);
    c = cosf(a);

    h = sqrtf(SQ(x) + SQ(z));
    if (h != 0.0f) {
        f32 hinv = 1 / h;

        mf[0][0] = (z * c - s * y * x) * hinv;
        mf[0][1] = s * h;
        mf[0][2] = -(x * c + s * y * z) * hinv;
        mf[0][3] = 0.0f;

        mf[1][0] = -(z * s + c * y * x) * hinv;
        mf[1][1] = c * h;
        mf[1][2] = (x * s - c * y * z) * hinv;
        mf[1][3] = 0.0f;

        mf[2][0] = x;
        mf[2][1] = y;
        mf[2][2] = z;
        mf[2][3] = 0.0f;

        mf[3][0] = lx;
        mf[3][1] = ly;
        mf[3][2] = lz;
        mf[3][3] = 1.0f;
    } else {
        mf[0][0] = c;
        mf[0][2] = -y * s;
        mf[0][1] = 0.0f;
        mf[0][3] = 0.0f;

        mf[1][0] = -s;
        mf[1][1] = 0.0f;
        mf[1][2] = -y * c;
        mf[1][3] = 0.0f;

        mf[2][0] = 0.0f;
        mf[2][1] = y;
        mf[2][2] = 0.0f;
        mf[2][3] = 0.0f;

        mf[3][0] = lx;
        mf[3][1] = ly;
        mf[3][2] = lz;
        mf[3][3] = 1.0f;
    }
}

/**
 * Original name: normalVct
 *
 * Normalise a vector consisting of three passed floats in-place. Returns the length of the original vector.
 */
f32 normalVct(f32 *x, f32 *y, f32 *z) {
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
s32 random(s32 n) {
    return (n * irandom()) >> 0x10;
}

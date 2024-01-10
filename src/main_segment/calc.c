/**
 * Original filename: calc.c
 */

#include "calc.h"

#include "include_asm.h"
#include "macros_defines.h"
#include "unknown_structs.h"
#include "main_segment_variables.h"

// Currently only used in this file, consider moving to a header in future

#define DEG_TO_RAD(x) ((x)*M_PI / 180.0)

typedef float MtxF_t[4][4];

typedef union {
    MtxF_t mf;
    struct {
        // Note: The order displayed here is the transpose of the order in which matrices are typically written.
        // For example, [xw, yw, zw] is the translation part of the matrix, not [wx, wy, wz].
        float xx, yx, zx, wx, //
            xy, yy, zy, wy,   //
            xz, yz, zz, wz,   //
            xw, yw, zw, ww;
    };
} MtxF;

f32 func_8007C244(f32, f32);
f32 func_8007C480(s16 arg0);

#if VERSION_US
// "tanf"
f32 func_8007BC20(f32 arg0) {
    return sinf(arg0) / cosf(arg0);
}
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/calc", func_8007BC54);
#endif

#if VERSION_US
/**
 * Creates a general rotation + translation matrix. Uses Y1 X2 Z3 Tait-Bryan angles
 * (https://en.wikipedia.org/wiki/Euler_angles#Rotation_matrix). `rotX`, `rotY`, `rotZ` are in degrees.
 */
void func_8007BD30(MtxF *m, f32 rotX, f32 rotY, f32 rotZ, f32 transX, f32 transY, f32 transZ) {
    f32 a2 = DEG_TO_RAD(rotX);
    f32 a1 = DEG_TO_RAD(rotY);
    f32 a3 = DEG_TO_RAD(rotZ);
    f32 s2 = sinf(a2);
    f32 s1 = sinf(a1);
    f32 s3 = sinf(a3);
    f32 c2 = cosf(a2);
    f32 c1 = cosf(a1);
    f32 c3 = cosf(a3);

    m->mf[0][0] = (s3 * s2 * s1) + (c3 * c1);
    m->mf[0][1] = s3 * c2;
    m->mf[0][2] = (s3 * s2 * c1) - (c3 * s1);

    m->mf[1][0] = (c3 * s2 * s1) - (s3 * c1);
    m->mf[1][1] = c3 * c2;
    m->mf[1][2] = (c3 * s2 * c1) + (s3 * s1);

    m->mf[2][0] = c2 * s1;
    m->mf[2][1] = -s2;
    m->mf[2][2] = c2 * c1;

    m->mf[3][0] = transX;
    m->mf[3][1] = transY;
    m->mf[3][2] = transZ;

    m->mf[0][3] = m->mf[1][3] = m->mf[2][3] = 0.0f;
    m->mf[3][3] = 1.0f;
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
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/calc", func_8007BFE0);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/calc", func_8007C0C4);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/calc", func_8007C244);
#endif

#if VERSION_US
/**
 * Original name most likely angleS2F
 *
 * Convert binary angle to float angle in degrees.
 */
f32 func_8007C480(s16 arg0) {
    return ((f32)arg0) * (360.0 / 0x10000);
}
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/calc", func_80086AB0_cn);
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/calc", func_80086B08_cn);
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/calc", func_80086BE4_cn);
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/calc", func_80086DBC_cn);
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/calc", func_80086EFC_cn);
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/calc", func_80086FF8_cn);
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/calc", func_80087140_cn);
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/calc", func_80087318_cn);
#endif

/**
 * Original name: angleF2S
 *
 * Convert float angle in degrees to a binary angle.
 */
s16 angleF2S(f32 arg0) {
    return (s32)(f32)(arg0 * (0x10000 / 360.0));
}

#if VERSION_US
/**
 * Convert an Mtx to an MtxF.
 */
void func_8007C4D8(MtxF *mtxf, Mtx *mtx) {
    s32 i;

    for (i = 0; i < 4; i++) {
        mtxf->mf[i][0] = (f32)mtx->m[i][0] / 0x8000;
        mtxf->mf[i][1] = (f32)mtx->m[i][1] / 0x8000;
        mtxf->mf[i][2] = (f32)mtx->m[i][2] / 0x8000;
        mtxf->mf[i][3] = (f32)mtx->m[i][3] / 0x8000;
    }
}

/**
 * Convert an Mtx to an MtxF.
 */
void func_8007C540(Mtx *mtx, MtxF *mtxf) {
    s32 i;

    for (i = 0; i < 4; i++) {
        mtx->m[i][0] = mtxf->mf[i][0] * 0x8000;
        mtx->m[i][1] = mtxf->mf[i][1] * 0x8000;
        mtx->m[i][2] = mtxf->mf[i][2] * 0x8000;
        mtx->m[i][3] = mtxf->mf[i][3] * 0x8000;
    }
}

/**
 * Convert an Mtx to an MtxF, and set the last row to (0, 0, 0, 1).
 */
void func_8007C5A8(Mtx *mtx, MtxF *mtxf) {
    s32 i;

    for (i = 0; i < 3; i++) {
        mtx->m[i][0] = mtxf->mf[i][0] * 0x8000;
        mtx->m[i][1] = mtxf->mf[i][1] * 0x8000;
        mtx->m[i][2] = mtxf->mf[i][2] * 0x8000;
        mtx->m[i][3] = mtxf->mf[i][3] * 0x8000;
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
#endif

f32 func_8007C6D8(f32 arg0, f32 arg1);
#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/calc", func_8007C6D8);
#endif

#if VERSION_US
/**
 * Calculate the distance between two points.
 */
f32 func_8007C780(f32 aX, f32 aY, f32 aZ, f32 bX, f32 bY, f32 bZ) {
    f32 diffX = bX - aX;
    f32 diffY = bY - aY;
    f32 diffZ = bZ - aZ;

    return sqrtf((diffX * diffX) + (diffY * diffY) + (diffZ * diffZ));
}
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/calc", func_8007C7E8);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/calc", func_8007C894);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/calc", func_8007C9C8);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/calc", func_8007CAFC);
#endif

#if VERSION_US
/**
 * Multiply the vector `(inX, inY, inZ)` by the matrix `m` and write to `(outX, outY, outZ)`.
 *
 * Caries out a general affine transformation.
 */
void func_8007CBE4(MtxF *m, f32 inX, f32 inY, f32 inZ, f32 *outX, f32 *outY, f32 *outZ) {
    f32 vec[3];
    s32 i;

    for (i = 0; i < 3; i++) {
        vec[i] = m->mf[3][i] + ((m->mf[0][i] * inX) + (m->mf[1][i] * inY) + (m->mf[2][i] * inZ));
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
void func_8007CC68(MtxF *m, f32 inX, f32 inY, f32 inZ, f32 *outX, f32 *outY, f32 *outZ) {
    f32 vec[3];
    f32 tempX = inX - m->mf[3][0];
    f32 tempY = inY - m->mf[3][1];
    f32 tempZ = inZ - m->mf[3][2];
    s32 i;

    for (i = 0; i < 3; i++) {
        vec[i] = (m->mf[i][0] * tempX) + (m->mf[i][1] * tempY) + (m->mf[i][2] * tempZ);
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
void func_8007CCFC(MtxF *m, f32 inX, f32 inY, f32 inZ, f32 *outX, f32 *outY, f32 *outZ) {
    f32 vec[3];
    s32 i;

    for (i = 0; i < 3; i++) {
        vec[i] = (m->mf[i][0] * inX) + (m->mf[i][1] * inY) + (m->mf[i][2] * inZ);
    }
    *outX = vec[0];
    *outY = vec[1];
    *outZ = vec[2];
}
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/calc", func_8007CD78);
#endif

/**
 * Normalise a vector consisting of three passed floats in-place. Returns the length of the original vector.
 */
#if VERSION_US
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

    randomtable[54] = seed;
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
    return arg0 * irandom() >> 0x10;
}
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/calc", func_80087368_cn);
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/calc", func_80087400_cn);
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/calc", func_80087498_cn);
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/calc", func_80087544_cn);
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/calc", func_80087614_cn);
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/calc", func_800876E4_cn);
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/calc", func_80087748_cn);
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/calc", func_800877DC_cn);
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/calc", func_800878DC_cn);
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/calc", func_80087A40_cn);
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/calc", func_80087B6C_cn);
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/calc", func_80087C0C_cn);
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/calc", func_80087CB8_cn);
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/calc", func_80087D48_cn);
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/calc", func_80087F84_cn);
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/calc", func_80088044_cn);
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/calc", randomseed);
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/calc", irandom);
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/calc", random);
#endif

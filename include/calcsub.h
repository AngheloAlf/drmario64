#ifndef CALCSUB_H
#define CALCSUB_H

#include "libultra.h"

#if 0
// Erased
static long mulS32S32(long a /* r27 */, long b /* r25 */, long shift /* r22 */) {
    // Local variables
    long long c; // r24
}
#endif

/**
 * This function does not halt until `*var` is equal to `data`.
 */
void waitEQ4(vs32 *var, s32 data);

s32 func_8007EA38(s32 value);
// void func_8007EA58();

#if 0
// Erased
static long sqrtS(unsigned long v /* r1+0x8 */) {
    // References
    // -> static int __float_huge[];
    // -> static int __float_nan[];
}

// Erased
static long sqrtL() {}

#endif

/**
 * Compute an angle by using atan2.
 */
s32 get_angle(s32 x, s32 y);

/**
 * Calculate sin of a binary angle.
 */
s16 sinL(s16 angle);

/**
 * Calculate cos of a binary angle.
 */
s16 cosL(s16 angle);

// void func_8007ECE0();
// void func_8007ED74();

#if 0
// Erased
static void lc2wc() {}

// Erased
static void wc2lc() {}
#endif

/**
 * r = m * n;
 */
void matrixMulL(const Mtx *m, const Mtx *n, Mtx *r);

/**
 * Initializes `m` to :
 *
 * | 0x8000      0      0      0 |
 * |      0 0x8000      0      0 |
 * |      0      0 0x8000      0 |
 * |      x      y      z 0x8000 |
 */
void makeTransrateMatrix(Mtx *m, s32 xofs, s32 yofs, s32 zofs);

#define MAKE_TRANSRATE_MATRIX(m, x, y, z) \
    makeTransrateMatrix(m, ((u32)(x)) << 15, ((u32)(y)) << 15, ((u32)(z)) << 15)

/**
 * Initializes `mtx` to :
 *
 * |  scale      0      0      0 |
 * |      0  scale      0      0 |
 * |      0      0  scale      0 |
 * |      0      0      0 0x8000 |
 */
void makeScaleMatrix(Mtx *m, s32 scale);

void makeMatrix(Mtx *m, s16 xrot, s16 yrot, s16 zrot, s32 xofs, s32 yofs, s32 zofs);

void makeXrotMatrix(Mtx *m, s16 xrot, s32 xofs, s32 yofs, s32 zofs);
void makeYrotMatrix(Mtx *m, s16 yrot, s32 xofs, s32 yofs, s32 zofs);
void makeZrotMatrix(Mtx *m, s16 zrot, s32 xofs, s32 yofs, s32 zofs);
void makeXZMatrix(Mtx *m, s16 xrot, s16 zrot);

void matrixConv(const Mtx *m, Mtx *mtx, s32 shift);

void matrixCopyL(Mtx *dst, const Mtx *src);

/**
 * Rotate (`x`, `y`) relative to (`center_x`, `center_y`) by `angle` degrees.
 */
void rotpointL(s16 angle, s32 center_x, s32 center_y, s32 *x, s32 *y);

s32 defangleL(u16 arg0, u16 arg1);

/**
 * Distance between 3D points.
 *
 * Uses integer operations internally, so there will be precision loss.
 */
s32 distanceS(s32 x0, s32 y0, s32 z0, s32 x1, s32 y1, s32 z1);

/**
 * Distance between 3D points.
 *
 * Uses float operations internally for minimal precision loss.
 */
s32 distanceL(s32 x0, s32 y0, s32 z0, s32 x1, s32 y1, s32 z1);

/**
 * ((a^2) + (b^2)) ^ (1/2)
 */
s32 sqrt_a2b2(s32 a, s32 b);

/**
 * ((a^2) + (b^2) + (c^2)) ^ (1/2)
 */
s32 sqrt_abc(s32 a, s32 b, s32 c);

/**
 * Computes (a * b) / c without overflowing.
 */
s32 muldiv(s32 a, s32 b, s32 c);

void makeVect(s16 arg0, s16 arg1, s32 *arg2, s32 *arg3, s32 *arg4);

extern u8 D_800AB320[];
extern s32 D_800AB334[];
extern s32 D_800AB3BC[];
extern s16 calc_sintable[1026];

#endif

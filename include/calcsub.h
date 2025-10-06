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

// void func_8007F214();
// void func_8007F284();
// void func_8007F2F4();
// void func_8007F364();

#if 0
// Erased
static void makeXrotMatrix() {}

// Erased
static void makeYrotMatrix() {}

// Erased
static void makeZrotMatrix() {}

// Erased
static void makeXZMatrix() {}
#endif

void matrixConv(const Mtx *m, Mtx *mtx, s32 shift);

void matrixCopyL(Mtx *dst, const Mtx *src);

// void func_8007F550();
// void func_8007F60C();
// void func_8007F670();
// void func_8007F6C4();

#if 0
// Erased
static void rotpointL() {}

// Erased
static long defangleL() {}

// Erased
static long distanceS() {}

// Erased
static long distanceL() {}
#endif

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

// void func_8007F824();
#if 0
// Erased
static void makeVect() {}
#endif

extern u8 D_800AB320[];
extern s32 D_800AB334[];
extern s32 D_800AB3BC[];
extern s16 calc_sintable[1026];

#endif

#ifndef CALC_H
#define CALC_H

#include "libultra.h"

#include "macros_defines.h"

#define DEG_TO_RAD(x) ((x)*M_PI / 180.0)

f32 tanf(f32 a);
void matrixMulF(const f32 s[4][4], const f32 d[4][4], f32 r[4][4]);
void makeMatrixF(f32 m[4][4], f32 rx, f32 ry, f32 rz, f32 lx, f32 ly, f32 lz);
void angle2vct(s16 pit, s16 yaw, f32 *x, f32 *y, f32 *z);
void vct2angle(f32 x, f32 y, f32 z, s16 *pit, s16 *yaw);
f32 atanF(f32 t);
f32 get_angleF(f32 x, f32 y);
f32 angleS2F(s16 a);
s16 angleF2S(f32 a);
void matrixL2F(f32 mtxf[4][4], CONST_ARG Mtx *mtx);
void matrixF2L(Mtx *mtx, CONST_ARG f32 mtxf[4][4]);
void matrixF2Lloc0(Mtx *mtx, CONST_ARG f32 mtxf[4][4]);
void rotpoint(f32 angle, f32 centreX, f32 centreY, f32 *pointX, f32 *pointY);
f32 defangle(f32 arg0, f32 arg1);
f32 distance(f32 aX, f32 aY, f32 aZ, f32 bX, f32 bY, f32 bZ);
f32 calcTableF(f32 x, const f32 table[]);
f32 calcTableF_Rev(f32 x, const f32 *table, f32 s, f32 e);
void mtx2angleF(CONST_ARG f32 m[4][4], f32 *rx, f32 *ry, f32 *rz);
void func_8007CAFC(CONST_ARG Mtx *arg0, s16 *arg1, s16 *arg2, s16 *arg3);
void lc2wcF(const f32 m[4][4], f32 inX, f32 inY, f32 inZ, f32 *outX, f32 *outY, f32 *outZ);
void wc2lcF(const f32 m[4][4], f32 inX, f32 inY, f32 inZ, f32 *outX, f32 *outY, f32 *outZ);
void wc2lcF0(const f32 m[4][4], f32 inX, f32 inY, f32 inZ, f32 *outX, f32 *outY, f32 *outZ);
void makeMatrixVctZ(f32 mf[4][4], f32 a, f32 x, f32 y, f32 z, f32 lx, f32 ly, f32 lz);
f32 normalVct(f32 *x, f32 *y, f32 *z);
void randomize00(void);
void randomseed(s32 seed);
s32 irandom(void);
s32 random(s32 n);

#endif

#ifndef CALC_H
#define CALC_H

#include "libultra.h"

#define DEG_TO_RAD(x) ((x)*M_PI / 180.0)

f32 func_8007BC20(f32 arg0);
void func_8007BC54(f32 arg0[4][4], f32 arg1[4][4], f32 arg2[4][4]);
void func_8007BD30(f32 m[4][4], f32 rotX, f32 rotY, f32 rotZ, f32 transX, f32 transY, f32 transZ);
void func_8007BEEC(s16 theta, s16 phi, f32 *x, f32 *y, f32 *z);
void func_8007BFE0(f32 arg0, f32 arg1, f32 arg2, s16 *arg3, s16 *arg4);
f32 func_8007C0C4(f32 arg0);
f32 func_8007C244(f32 arg0, f32 arg1);
f32 func_8007C480(s16 arg0);
s16 angleF2S(f32 arg0);
void func_8007C4D8(f32 mtxf[4][4], Mtx *mtx);
void func_8007C540(Mtx *mtx, f32 mtxf[4][4]);
void func_8007C5A8(Mtx *mtx, f32 mtxf[4][4]);
void func_8007C624(f32 angle, f32 centreX, f32 centreY, f32 *pointX, f32 *pointY);
f32 func_8007C6D8(f32 arg0, f32 arg1);
f32 func_8007C780(f32 aX, f32 aY, f32 aZ, f32 bX, f32 bY, f32 bZ);
f32 func_8007C7E8(f32 arg0, f32 *arg1);
f32 func_8007C894(f32 arg0, f32 *arg1, f32 arg2, f32 arg3);
void func_8007C9C8(f32 arg0[4][4], f32 *arg1, f32 *arg2, f32 *arg3);
void func_8007CAFC(Mtx *arg0, s16 *arg1, s16 *arg2, s16 *arg3);
void func_8007CBE4(f32 m[4][4], f32 inX, f32 inY, f32 inZ, f32 *outX, f32 *outY, f32 *outZ);
void func_8007CC68(f32 m[4][4], f32 inX, f32 inY, f32 inZ, f32 *outX, f32 *outY, f32 *outZ);
void func_8007CCFC(f32 m[4][4], f32 inX, f32 inY, f32 inZ, f32 *outX, f32 *outY, f32 *outZ);
void func_8007CD78(f32 arg0[4][4], f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7);
f32 func_8007CFB4(f32 *x, f32 *y, f32 *z);
void randomize00(void);
void randomseed(s32 seed);
s32 irandom(void);
s32 random(s32 arg0);

#endif

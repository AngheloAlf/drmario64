#ifndef _066840_H
#define _066840_H

#include "libultra.h"

// void func_8007EA20();
// void func_8007EA38();
// void func_8007EA58();
// void func_8007EAEC();
// void func_8007EC54();
// void func_8007EC98();
// void func_8007ECE0();
// void func_8007ED74();
void matrixMulL(Mtx *, Mtx *, Mtx *);
void makeTransrateMatrix(Mtx *mtx, u32 x, u32 y, u32 z);
void makeScaleMatrix(Mtx *mtx, u32 scale);
void makeMatrix(Mtx *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
// void func_8007F214();
// void func_8007F284();
// void func_8007F2F4();
// void func_8007F364();
void matrixConv(Mtx *arg0, Mtx *arg1, s32 arg2);
// void func_8007F514();
// void func_8007F550();
// void func_8007F60C();
// void func_8007F670();
// void func_8007F6C4();
// void func_8007F720();
// void func_8007F754();
// void func_8007F79C();
// void func_8007F824();

#endif

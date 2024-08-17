#ifndef _065080_H
#define _065080_H

#include "libultra.h"
#include "libc/stdbool.h"

void func_8007D260(f32 arg0[3], Mtx *arg1, f32 arg2[3]);
void mult_func_8007D348(f32 arg0[3], Mtx *arg1, f32 arg2[3]);
void mult_func_8007D410(f32 arg0[3], f32 arg1[4][4], f32 arg2[3]);
void mult_func_8007D4CC(f32 arg0[3], f32 arg1[4][4], f32 arg2[3]);
void mult_func_8007D568(Mtx *arg0, Mtx *arg1, Mtx *arg2);
void mult_func_8007D644(f32 arg0[4][4], f32 arg1[4][4], f32 arg2[4][4]);
void func_8007D74C(f32 arg0[3][3], s32 arg1, s32 arg2, s32 arg3);
bool func_8007D83C(f32 arg0[3][3], f32 arg1[3][3], s32 arg2);
bool func_8007DB78(f32 arg0[3][3], f32 arg1[3][3]);
bool func_8007DD70(f32 arg0[4][4], f32 arg1[4], f32 *arg2, s32 *arg3);
bool func_8007DF64(f32 arg0[4][4], f32 arg1[4][4]);

#endif

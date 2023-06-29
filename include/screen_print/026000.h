#ifndef SCREEN_PRINT_026000_H
#define SCREEN_PRINT_026000_H

#include "printer.h"

typedef void (*func_8003E69C_arg1)(Gfx **, s32, s32, s32);


void func_8003E1E0(Gfx **gfxP);
void func_8003E208(Gfx **gfxP, s32 index);
// void func_8003E278();
void func_8003E3F0(Gfx **gfxP, s32 arg1, s32 arg2, s32 character);
s32 func_8003E430(struct_8008E364 *arg0, va_list args);
s32 func_8003E4AC(void);
s32 func_8003E4B4(struct_8008E364 *arg0, char *arg1, s32 arg2);
s32 func_8003E69C(Gfx **gfxP, func_8003E69C_arg1 arg1, s32 arg2, s32 arg3);
void func_8003E6D8(void);
void func_8003E6F8(const char *fmt, ...);

#endif

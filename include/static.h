#ifndef STATIC_H
#define STATIC_H

#include "libultra.h"
#include "libc/stdbool.h"
#include "other_types.h"

void func_8002BD20(u8 red, u8 green, u8 blue, u8 alpha, s32 arg4, s32 arg5, s32 arg6, s32 arg7);
void load_TexPal(TexturePtr tlut);
void func_8002BF90(TexturePtr tlut, u32 pal);
void load_TexBlock_4b(TexturePtr texture, s32 width, s32 height);
void func_8002C1E8(TexturePtr texture, s32 width, s32 height);
void load_TexTile_4b(TexturePtr texture, s32 width, s32 height, s32 uls, s32 ult, s32 lrs, s32 lrt);
void func_8002C4EC(TexturePtr texture, s32 width, s32 height);
void func_8002C688(u8 *texture, s32 width, s32 height, s32 uls, s32 ult, s32 lrs, s32 lrt);
void draw_Tex(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
void func_8002C914(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
void func_8002CA68(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7);
void func_8002CD08(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, bool arg6, bool arg7);
void func_8002CF04(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, bool argA, bool argB);

#endif

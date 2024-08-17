#ifndef FONT_H
#define FONT_H

#include "libultra.h"
#include "libc/stdbool.h"

s32 fontStr_nextChar(const unsigned char *arg0);
s32 fontStr_length(const unsigned char *arg0);
s32 fontStr_charSize(const unsigned char *arg0, s32 arg1);
u16 func_8005B8D8(u8 arg0);
s32 font2index(const unsigned char *arg0);
void ascii2index(s32 character, s32 arg1, s32 *indexP, s32 *sizeP);
void font16_initDL(Gfx **gfxP);
void font16_initDL2(Gfx **gfxP);
void fontXX_draw(Gfx **gfxP, f32 x, f32 y, f32 width, f32 height, const unsigned char *str);
bool fontXX_drawID(Gfx **gfxP, f32 x, f32 y, f32 width, f32 height, s32 index);
void fontXX_draw2(Gfx **gfxP, f32 arg1, f32 arg2, f32 arg3, f32 arg4, const unsigned char *str);
bool fontXX_drawID2(Gfx **gfxP, f32 x, f32 y, f32 width, f32 height, s32 index);
bool fontAsc_draw(Gfx **gfxP, f32 arg1, f32 arg2, f32 arg3, f32 arg4, unsigned char * arg5);
bool fontAsc_drawID(Gfx **gfxP, f32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 index);
bool fontAsc_draw2(Gfx **gfxP, f32 arg1, f32 arg2, f32 arg3, f32 arg4, unsigned char * arg5);
bool fontAsc_drawID2(Gfx **gfxP, f32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5);

#endif

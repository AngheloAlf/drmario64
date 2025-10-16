#ifndef FONT_H
#define FONT_H

#include "libultra.h"
#include "libc/stdbool.h"

s32 fontStr_nextChar(const unsigned char *str);
s32 fontStr_length(const unsigned char *str);
s32 fontStr_charSize(const unsigned char *arg0, s32 arg1);
u16 index2font(u8 code);
s32 font2index(const unsigned char *charcode);
void ascii2index(s32 code, s32 type, s32 *indexP, s32 *widthP);
void font16_initDL(Gfx **gfxP);
void font16_initDL2(Gfx **gfxP);
void fontXX_draw(Gfx **gfxP, f32 x, f32 y, f32 width, f32 height, const unsigned char *charcode);
bool fontXX_drawID(Gfx **gfxP, f32 x, f32 y, f32 width, f32 height, s32 index);
void fontXX_draw2(Gfx **gfxP, f32 x, f32 y, f32 w, f32 h, const unsigned char *charcode);
bool fontXX_drawID2(Gfx **gfxP, f32 x, f32 y, f32 width, f32 height, s32 index);
bool fontAsc_draw(Gfx **gfxP, f32 x, f32 y, f32 w, f32 h, unsigned char *arg5);
bool fontAsc_drawID(Gfx **gfxP, f32 x, f32 y, f32 w, f32 h, s32 index);
bool fontAsc_draw2(Gfx **gfxP, f32 x, f32 y, f32 w, f32 h, unsigned char *charcode);
bool fontAsc_drawID2(Gfx **gfxP, f32 x, f32 y, f32 w, f32 h, s32 arg5);

#endif

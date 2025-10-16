#ifndef STATIC_H
#define STATIC_H

#include "libultra.h"
#include "libc/stdbool.h"

void disp_rect(u8 red, u8 green, u8 blue, u8 alpha, s32 x, s32 y, s32 width, s32 height);
void load_TexPal(const u16 tlut[]);
void load_TexPal_16(const u16 tlut[], s32 pal_no);
void load_TexBlock_4b(const u8 texture[], s32 size_w, s32 size_h);
void load_TexBlock_i(const u8 texture[], s32 size_w, s32 size_h);
void load_TexTile_4b(const u8 texture[], s32 size_w, s32 height, s32 start_w, s32 start_h, s32 end_w, s32 end_h);
void load_TexBlock_8b(const u8 texture[], s32 size_w, s32 size_h);
void load_TexTile_8b(const u8 texture[], s32 size_w, s32 height, s32 start_w, s32 start_h, s32 end_w, s32 end_h);
void draw_Tex(s32 x_pos, s32 y_pos, s32 draw_w, s32 draw_h, s32 start_w, s32 start_h);
void draw_Tex_Copy(s32 x_pos, s32 y_pos, s32 draw_w, s32 draw_h, s32 start_w, s32 start_h);
void draw_ScaleTex(s32 x_pos, s32 y_pos, s32 size_w, s32 size_h, s32 draw_w, s32 draw_h, s32 start_w, s32 start_h);
void draw_TexFlip(s32 x_pos, s32 y_pos, s32 draw_w, s32 draw_h, s32 start_w, s32 start_h, bool x_flip, bool y_flip);
void draw_TexScaleFlip(s32 x_pos, s32 y_pos, s32 size_w, s32 size_h, s32 draw_w, s32 draw_h, s32 start_w, s32 start_h,
                       s32 end_w, s32 end_h, bool x_flip, bool y_flip);

extern Gfx S2RDPinit_dl[];
extern Gfx S2ClearCFB_dl[];
extern Gfx S2Spriteinit_dl[];
extern Gfx F3RDPinit_dl[];
extern Gfx F3SetupRDP_dl[];
extern Gfx F3SetupRSP_dl[];
extern Gfx D_80088360[];
extern Gfx D_800883A8[];

#endif

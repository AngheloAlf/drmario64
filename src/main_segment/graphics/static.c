/**
 * Original filename: static.c
 */

#include "static.h"

#include "macros_defines.h"

#include "graphic.h"

Gfx S2RDPinit_dl[] = {
    gsDPPipeSync(),
    gsDPPipelineMode(G_PM_1PRIMITIVE),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsDPSetTexturePersp(G_TP_NONE),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTextureConvert(G_TC_FILT),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPSetColorDither(G_CD_DISABLE),
    gsSPEndDisplayList(),
};

Gfx S2ClearCFB_dl[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_FILL),
    gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
    gsDPSetFillColor((GPACK_RGBA5551(16, 16, 16, 1) << 16) | GPACK_RGBA5551(16, 16, 16, 1)),
    gsSPEndDisplayList(),
};

Gfx S2Spriteinit_dl[] = {
    gsDPPipeSync(),
    gsDPSetTexturePersp(G_TP_NONE),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetTextureConvert(G_TC_FILT),
    gsDPSetAlphaCompare(G_AC_THRESHOLD),
    gsDPSetBlendColor(0, 0, 0, 1),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsSPEndDisplayList(),
};

Gfx F3RDPinit_dl[] = {
    gsDPSetEnvColor(0x00, 0x00, 0x00, 0x00),
    gsDPSetPrimColor(0, 0, 0x00, 0x00, 0x00, 0x00),
    gsDPSetBlendColor(0x00, 0x00, 0x00, 0x00),
    gsDPSetFogColor(0x00, 0x00, 0x00, 0x00),
    gsDPSetFillColor((GPACK_RGBA5551(0, 0, 0, 0) << 16) | GPACK_RGBA5551(0, 0, 0, 0)),
    gsDPSetPrimDepth(0, 0),
    gsDPSetConvert(0, 0, 0, 0, 0, 0),
    gsDPSetKeyR(0x00000000, 0x00, 0),
    gsDPSetKeyGB(0x00000000, 0x00, 0, 0x00000000, 0x00, 0),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0x0000, G_TX_RENDERTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK,
                G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0x0000, 1, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD,
                G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0x0000, 2, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD,
                G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0x0000, 3, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD,
                G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0x0000, 4, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD,
                G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0x0000, 5, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD,
                G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0x0000, 6, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD,
                G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0x0000, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK,
                G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 0, 0),
    gsDPSetTileSize(1, 0, 0, 0, 0),
    gsDPSetTileSize(2, 0, 0, 0, 0),
    gsDPSetTileSize(3, 0, 0, 0, 0),
    gsDPSetTileSize(4, 0, 0, 0, 0),
    gsDPSetTileSize(5, 0, 0, 0, 0),
    gsDPSetTileSize(6, 0, 0, 0, 0),
    gsDPSetTileSize(G_TX_LOADTILE, 0, 0, 0, 0),
    gsDPPipeSync(),
    gsSPEndDisplayList(),
};

Gfx F3SetupRDP_dl[] = {
    gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
    gsDPSetColorDither(G_CD_DISABLE),
    gsDPPipeSync(),
    gsSPEndDisplayList(),
};

Gfx F3SetupRSP_dl[] = {
    gsSPClipRatio(FRUSTRATIO_6),
    gsSPClearGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_OFF),
    gsSPEndDisplayList(),
};

Gfx D_80088360[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetTexturePersp(G_TP_NONE),
    gsDPSetCombineMode(G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM),
    gsDPSetPrimColor(0, 0, 255, 255, 255, 255),
    gsDPSetTextureFilter(G_TF_POINT),
    gsSPEndDisplayList(),
};

Gfx D_800883A8[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetRenderMode(G_RM_TEX_EDGE, G_RM_TEX_EDGE2),
    gsDPSetTexturePersp(G_TP_NONE),
    gsDPSetCombineMode(G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM),
    gsDPSetPrimColor(0, 0, 255, 255, 255, 255),
    gsDPSetTextureFilter(G_TF_POINT),
    gsSPEndDisplayList(),
};

/**
 * Original name: disp_rect
 */
void disp_rect(u8 red, u8 green, u8 blue, u8 alpha, s32 x, s32 y, s32 width, s32 height) {
    s32 x0;
    s32 y0;
    s32 x1;
    s32 y1;

    gDPPipeSync(gGfxHead++);
    gDPSetPrimColor(gGfxHead++, 0, 0, red, green, blue, alpha);
    gDPSetCombineMode(gGfxHead++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);

    x0 = x << 2;
    y0 = y << 2;
    x1 = (x + width) << 2;
    y1 = (y + height) << 2;

    gSPScisTextureRectangle(gGfxHead++, x0, y0, x1, y1, G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);
}

/**
 * Original name: load_TexPal
 */
void load_TexPal(const u16 tlut[]) {
    gDPLoadTLUT_pal256(gGfxHead++, tlut);
}

/**
 * Original name: load_TexPal_16
 */
void load_TexPal_16(const u16 tlut[], s32 pal_no) {
    gDPLoadTLUT_pal16(gGfxHead++, pal_no, tlut);
}

/**
 * Original name: load_TexBlock_4b
 */
void load_TexBlock_4b(const u8 texture[], s32 size_w, s32 size_h) {
    gDPLoadTextureBlock_4b(gGfxHead++, texture, G_IM_FMT_CI, size_w, size_h, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                           G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
}

/**
 * Original name: load_TexBlock_i
 */
void load_TexBlock_i(const u8 texture[], s32 size_w, s32 size_h) {
    gDPLoadTextureBlock_4b(gGfxHead++, texture, G_IM_FMT_I, size_w, size_h, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                           G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
}

/**
 * Original name: load_TexTile_4b
 */
void load_TexTile_4b(const u8 texture[], s32 size_w, s32 size_h UNUSED, s32 start_w, s32 start_h, s32 end_w,
                     s32 end_h) {
    gDPLoadTextureTile_4b(gGfxHead++, texture, G_IM_FMT_CI, size_w, size_h, start_w, start_h, end_w, end_h, 0,
                          G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                          G_TX_NOLOD);
}

/**
 * Original name: load_TexBlock_8b
 */
void load_TexBlock_8b(const u8 texture[], s32 size_w, s32 size_h) {
    gDPLoadTextureBlock(gGfxHead++, texture, G_IM_FMT_CI, G_IM_SIZ_8b, size_w, size_h, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
}

/**
 * Original name: load_TexTile_8b
 */
void load_TexTile_8b(const u8 texture[], s32 size_w, s32 size_h UNUSED, s32 start_w, s32 start_h, s32 end_w,
                     s32 end_h) {
    gDPLoadTextureTile(gGfxHead++, texture, G_IM_FMT_CI, G_IM_SIZ_8b, size_w, size_h, start_w, start_h, end_w, end_h, 0,
                       G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                       G_TX_NOLOD);
}

/**
 * Original name: draw_Tex
 */
void draw_Tex(s32 x_pos, s32 y_pos, s32 draw_w, s32 draw_h, s32 start_w, s32 start_h) {
    gSPScisTextureRectangle(gGfxHead++, x_pos << 2, y_pos << 2, (x_pos + draw_w) << 2, (y_pos + draw_h) << 2,
                            G_TX_RENDERTILE, start_w << 5, start_h << 5, 1 << 10, 1 << 10);
}

/**
 * Original name: draw_Tex_Copy
 */
void draw_Tex_Copy(s32 x_pos, s32 y_pos, s32 draw_w, s32 draw_h, s32 start_w, s32 start_h) {
    gSPScisTextureRectangle(gGfxHead++, x_pos << 2, y_pos << 2, (x_pos + draw_w) << 2, (y_pos + draw_h) << 2,
                            G_TX_RENDERTILE, start_w << 5, start_h << 5, 4 << 10, 4 << 10);
}

/**
 * Original name: draw_ScaleTex
 */
void draw_ScaleTex(s32 x_pos, s32 y_pos, s32 size_w, s32 size_h, s32 draw_w, s32 draw_h, s32 start_w, s32 start_h) {
    gSPScisTextureRectangle(gGfxHead++, x_pos << 2, y_pos << 2, (x_pos + draw_w) << 2, (y_pos + draw_h) << 2,
                            G_TX_RENDERTILE, start_w << 5, start_h << 5, (size_w << 10) / draw_w,
                            (size_h << 10) / draw_h);
}

/**
 * Original name: draw_TexFlip
 */
void draw_TexFlip(s32 x_pos, s32 y_pos, s32 draw_w, s32 draw_h, s32 start_w, s32 start_h, bool x_flip, bool y_flip) {
    s32 f_y = 1 << 10;
    s32 f_x = 1 << 10;

    if (x_flip) {
        f_x = ((u32)-1 << 10) & 0xFFFF;
        start_w = draw_w - 1;
    }
    if (y_flip) {
        f_y = ((u32)-1 << 10) & 0xFFFF;
        start_h = draw_h - 1;
    }

    gSPScisTextureRectangle(gGfxHead++, x_pos << 2, y_pos << 2, (x_pos + draw_w) << 2, (y_pos + draw_h) << 2,
                            G_TX_RENDERTILE, start_w << 5, start_h << 5, f_x, f_y);
}

/**
 * Original name: draw_TexScaleFlip
 */
void draw_TexScaleFlip(s32 x_pos, s32 y_pos, s32 size_w, s32 size_h, s32 draw_w, s32 draw_h, s32 start_w, s32 start_h,
                       s32 end_w, s32 end_h, bool x_flip, bool y_flip) {
    s32 f_x = (size_w << 10) / draw_w;
    s32 f_y = (size_h << 10) / draw_h;

    if (x_flip) {
        f_x = ((u32)-f_x) & 0xFFFF;
        start_w = end_w - 1;
    }
    if (y_flip) {
        f_y = ((u32)-f_y) & 0xFFFF;
        start_h = end_h - 1;
    }

    gSPScisTextureRectangle(gGfxHead++, x_pos << 2, y_pos << 2, (x_pos + draw_w) << 2, (y_pos + draw_h) << 2,
                            G_TX_RENDERTILE, start_w << 5, start_h << 5, f_x, f_y);
}

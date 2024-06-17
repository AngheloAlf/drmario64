/**
 * Original filename: static.c
 */
#include "static.h"

#include "include_asm.h"
#include "macros_defines.h"
#include "unknown_structs.h"
#include "unk.h"
#include "main_segment_variables.h"

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
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0x0000, G_TX_RENDERTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0x0000, 1, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0x0000, 2, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0x0000, 3, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0x0000, 4, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0x0000, 5, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0x0000, 6, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0x0000, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
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

void func_8002BD20(u8 red, u8 green, u8 blue, u8 alpha, s32 arg4, s32 arg5, s32 arg6, s32 arg7) {
    s32 a;
    s32 b;
    s32 c;
    s32 d;

    gDPPipeSync(gGfxHead++);
    gDPSetPrimColor(gGfxHead++, 0, 0, red, green, blue, alpha);
    gDPSetCombineMode(gGfxHead++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);

    a = arg4 << 2;
    b = arg5 << 2;
    c = (arg4 + arg6) << 2;
    d = (arg5 + arg7) << 2;

    gSPScisTextureRectangle(gGfxHead++, a, b, c, d, G_TX_RENDERTILE, 0, 0, 0x0400, 0x0400);
}

/**
 * Original name: load_TexPal
 */
void load_TexPal(TexturePtr tlut) {
    gDPLoadTLUT_pal256(gGfxHead++, tlut);
}

void func_8002BF90(TexturePtr tlut, u32 pal) {
    gDPLoadTLUT_pal16(gGfxHead++, pal, tlut);
}

/**
 * Original name: load_TexBlock_4b
 */
void load_TexBlock_4b(TexturePtr texture, s32 width, s32 height) {
    gDPLoadTextureBlock_4b(gGfxHead++, texture, G_IM_FMT_CI, width, height, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                           G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
}

void func_8002C1E8(TexturePtr texture, s32 width, s32 height) {
    gDPLoadTextureBlock_4b(gGfxHead++, texture, G_IM_FMT_I, width, height, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                           G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
}

/**
 * Original name: load_TexTile_4b
 */
void load_TexTile_4b(TexturePtr texture, s32 width, s32 height UNUSED, s32 uls, s32 ult, s32 lrs, s32 lrt) {
    gDPLoadTextureTile_4b(gGfxHead++, texture, G_IM_FMT_CI, width, height, uls, ult, lrs, lrt, 0,
                          G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                          G_TX_NOLOD);
}

void func_8002C4EC(TexturePtr texture, s32 width, s32 height) {
    gDPLoadTextureBlock(gGfxHead++, texture, G_IM_FMT_CI, G_IM_SIZ_8b, width, height, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
}

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/graphics/static", func_8002C688);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/graphics/static", func_8002E36C_cn);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/graphics/static", func_8002C688);
#endif

/**
 * Original name: draw_Tex
 */
void draw_Tex(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    gSPScisTextureRectangle(gGfxHead++, arg0 << 2, arg1 << 2, (arg0 + arg2) << 2, (arg1 + arg3) << 2, G_TX_RENDERTILE,
                            arg4 << 5, arg5 << 5, 1 << 10, 1 << 10);
}

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/graphics/static", func_8002C914);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/graphics/static", func_8002E5E8_cn);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/graphics/static", func_8002C914);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/graphics/static", func_8002CA68);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/graphics/static", func_8002E710_cn);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/graphics/static", func_8002CA68);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/graphics/static", func_8002CD08);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/graphics/static", func_8002E968_cn);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/graphics/static", func_8002CD08);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/graphics/static", func_8002CF04);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/graphics/static", func_8002EB24_cn);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/graphics/static", func_8002CF04);
#endif

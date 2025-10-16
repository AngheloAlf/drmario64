#include "libc/assert.h"

#include "alignment.h"
#include "lws.h"
#include "macros_defines.h"

#define menu_bg_D_05000000_COUNT (5)

extern Lws menu_bg_D_05000000;
extern u32 menu_bg_D_05000018[];
extern u16 menu_bg_D_05000028[];
extern u8 menu_bg_D_05000228[];
extern u8 menu_bg_D_050009A8[];
extern u8 menu_bg_D_050019A0[];
extern u8 menu_bg_D_05002990[];
extern Gfx menu_bg_D_05002F90[];
extern u32 menu_bg_D_05002F98[];
extern Vtx menu_bg_D_05002FB8[];
extern Gfx menu_bg_D_05002FF8[];
extern u32 menu_bg_D_050030F0[];
extern Vtx menu_bg_D_05003110[];
extern Gfx menu_bg_D_05003310[];
extern u32 menu_bg_D_05003448[];
extern Vtx menu_bg_D_05003468[];
extern Gfx menu_bg_D_050035E8[];
extern u32 menu_bg_D_05003710[];
extern Vtx menu_bg_D_05003730[];
extern Gfx menu_bg_D_050037F0[];
extern LwsObj menu_bg_D_050038C8[];
extern LwsKey menu_bg_D_05003940[];
extern u32 menu_bg_D_05003A74[];

Lws menu_bg_D_05000000 = {
    1, 8640, 60, menu_bg_D_05000000_COUNT, menu_bg_D_050038C8, menu_bg_D_05003940,
};

/* unreferenced data */
u32 menu_bg_D_05000018[] = {
    0x0001FFFF,
    0x00000000,
    0x00000000,
    0xFFFFFFFF,
};

u16 menu_bg_D_05000028[] ALIGNED(8) = {
#include "assets/menu_bg/menu_bg/menu_bg_D_05000228.palette.inc"
};

u8 menu_bg_D_05000228[] ALIGNED(8) = {
#include "assets/menu_bg/menu_bg/menu_bg_D_05000228.ci8.inc"
};

u8 menu_bg_D_050009A8[] ALIGNED(8) = {
#include "assets/menu_bg/menu_bg/menu_bg_D_050009A8.i4.inc"
};

u8 menu_bg_D_050019A0[] ALIGNED(8) = {
#include "assets/menu_bg/menu_bg/menu_bg_D_050019A0.i4.inc"
};

u8 menu_bg_D_05002990[] ALIGNED(8) = {
#include "assets/menu_bg/menu_bg/menu_bg_D_05002990.i4.inc"
};

Gfx menu_bg_D_05002F90[] = {
    gsSPEndDisplayList(),
};

/* unreferenced data */
u32 menu_bg_D_05002F98[] = {
    0xFFFFFF60, 0x000000A0, 0xFFFFFF88, 0x00000078, 0x00000000, 0x00000000, 0x000000A0, 0x00000000,
};

Vtx menu_bg_D_05002FB8[] = {
#include "assets/menu_bg/menu_bg/menu_bg_D_05002FB8.vtx.inc.c"
};

Gfx menu_bg_D_05002FF8[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsDPSetPrimColor(0, 0, 255, 255, 255, 255),
    gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, PRIMITIVE, COMBINED, ENVIRONMENT, COMBINED, 0, 0, 0, COMBINED),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_FRONT | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPLoadTLUT_pal256(menu_bg_D_05000028),
    gsDPLoadTextureBlock(menu_bg_D_05000228, G_IM_FMT_CI, G_IM_SIZ_8b, 8, 240, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                         G_TX_NOMIRROR | G_TX_CLAMP, 3, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(menu_bg_D_05002FB8, 4, 0),
    gsSP2Triangles(2, 0, 1, 0, 3, 0, 2, 0),
    gsSPEndDisplayList(),
};

/* unreferenced data */
u32 menu_bg_D_050030F0[] = {
    0xFFFFFEC0, 0x00000140, 0xFFFFFEC0, 0x00000140, 0x00000000, 0x00000000, 0x00000140, 0x00000000,
};

Vtx menu_bg_D_05003110[] = {
#include "assets/menu_bg/menu_bg/menu_bg_D_05003110.vtx.inc.c"
};

Gfx menu_bg_D_05003310[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsDPSetPrimColor(0, 0, 255, 255, 255, 255),
    gsDPSetCombineLERP(0, 0, 0, SHADE, TEXEL0, 0, SHADE, 0, PRIMITIVE, COMBINED, ENVIRONMENT, COMBINED, 0, 0, 0,
                       COMBINED),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_FRONT | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetAlphaCompare(G_AC_THRESHOLD),
    gsDPLoadTextureBlock_4b(menu_bg_D_050009A8, G_IM_FMT_I, 112, 73, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(menu_bg_D_05003110, 32, 0),
    gsSP2Triangles(2, 0, 1, 0, 3, 1, 0, 0),
    gsSP2Triangles(6, 4, 5, 0, 7, 5, 4, 0),
    gsSP2Triangles(10, 8, 9, 0, 11, 9, 8, 0),
    gsSP2Triangles(14, 12, 13, 0, 15, 13, 12, 0),
    gsDPLoadTextureBlock_4b(menu_bg_D_050019A0, G_IM_FMT_I, 80, 102, 0, G_TX_NOMIRROR | G_TX_WRAP,
                            G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP2Triangles(18, 16, 17, 0, 19, 17, 16, 0),
    gsSP2Triangles(22, 20, 21, 0, 23, 21, 20, 0),
    gsSP2Triangles(26, 24, 25, 0, 27, 25, 24, 0),
    gsSP2Triangles(30, 28, 29, 0, 31, 29, 28, 0),
    gsSPEndDisplayList(),
};

/* unreferenced data */
u32 menu_bg_D_05003448[] = {
    0xFFFFFF21, 0x000000DD, 0xFFFFFF1E, 0x000000A1, 0x00000000, 0x00000000, 0x000000E2, 0x00000000,
};

Vtx menu_bg_D_05003468[] = {
#include "assets/menu_bg/menu_bg/menu_bg_D_05003468.vtx.inc.c"
};

Gfx menu_bg_D_050035E8[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsDPSetPrimColor(0, 0, 255, 255, 255, 255),
    gsDPSetCombineLERP(0, 0, 0, SHADE, TEXEL0, 0, SHADE, 0, PRIMITIVE, COMBINED, ENVIRONMENT, COMBINED, 0, 0, 0,
                       COMBINED),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_FRONT | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetAlphaCompare(G_AC_THRESHOLD),
    gsDPLoadTextureBlock_4b(menu_bg_D_050019A0, G_IM_FMT_I, 80, 102, 0, G_TX_NOMIRROR | G_TX_WRAP,
                            G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(menu_bg_D_05003468, 24, 0),
    gsSP2Triangles(2, 0, 1, 0, 3, 1, 0, 0),
    gsSP2Triangles(6, 4, 5, 0, 7, 5, 4, 0),
    gsSP2Triangles(10, 8, 9, 0, 11, 9, 8, 0),
    gsDPLoadTextureBlock_4b(menu_bg_D_05002990, G_IM_FMT_I, 48, 64, 0, G_TX_NOMIRROR | G_TX_WRAP,
                            G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, 6, G_TX_NOLOD, G_TX_NOLOD),
    gsSP2Triangles(14, 12, 13, 0, 15, 13, 12, 0),
    gsSP2Triangles(18, 16, 17, 0, 19, 17, 16, 0),
    gsSP2Triangles(22, 20, 21, 0, 23, 21, 20, 0),
    gsSPEndDisplayList(),
};

/* unreferenced data */
u32 menu_bg_D_05003710[] = {
    0xFFFFFFB9, 0x0000005A, 0xFFFFFFA6, 0x0000005D, 0x00000000, 0x00000000, 0x0000005D, 0x00000000,
};

Vtx menu_bg_D_05003730[] = {
#include "assets/menu_bg/menu_bg/menu_bg_D_05003730.vtx.inc.c"
};

Gfx menu_bg_D_050037F0[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsDPSetPrimColor(0, 0, 255, 255, 255, 255),
    gsDPSetCombineLERP(0, 0, 0, SHADE, TEXEL0, 0, SHADE, 0, PRIMITIVE, COMBINED, ENVIRONMENT, COMBINED, 0, 0, 0,
                       COMBINED),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_FRONT | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetAlphaCompare(G_AC_THRESHOLD),
    gsDPLoadTextureBlock_4b(menu_bg_D_05002990, G_IM_FMT_I, 48, 64, 0, G_TX_NOMIRROR | G_TX_WRAP,
                            G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, 6, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(menu_bg_D_05003730, 12, 0),
    gsSP2Triangles(2, 0, 1, 0, 3, 1, 0, 0),
    gsSP2Triangles(6, 4, 5, 0, 7, 5, 4, 0),
    gsSP2Triangles(10, 8, 9, 0, 11, 9, 8, 0),
    gsSPEndDisplayList(),
};

LwsObj menu_bg_D_050038C8[] = {
    { menu_bg_D_05002F90, -1, 1, 0, 0, 0, 0 }, { menu_bg_D_05002FF8, -1, 1, 1, 0, 0, 0 },
    { menu_bg_D_05003310, -1, 4, 2, 0, 0, 0 }, { menu_bg_D_050035E8, -1, 3, 6, 0, 0, 0 },
    { menu_bg_D_050037F0, -1, 2, 9, 0, 0, 0 },
};
static_assert(ARRAY_COUNT(menu_bg_D_050038C8) == menu_bg_D_05000000_COUNT, "");

LwsKey menu_bg_D_05003940[] = {
    { 0, -1, 0, 0, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 0, -1, 0, 960, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 0, 3, 1280, 1920, 80, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 2880, 4, 1280, 1920, 80, -2880, 2880, -8640, 4096, 4096, 4096 },
    { 5760, 5, 1280, 1920, 80, -2880, 2880, -14400, 4096, 4096, 4096 },
    { 8640, -1, 1280, 1920, 80, -2880, 2880, -20160, 4096, 4096, 4096 },
    { 0, 7, 1280, 1920, 80, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 4320, 8, 1280, 1920, 80, -2880, 2880, -8640, 4096, 4096, 4096 },
    { 8640, -1, 1280, 1920, 80, -2880, 2880, -14400, 4096, 4096, 4096 },
    { 0, 10, 1280, 1920, 80, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 8640, -1, 1280, 1920, 80, -2880, 2880, -8640, 4096, 4096, 4096 },
};

/* unreferenced data */
u32 menu_bg_D_05003A74[] = {
    0x00000000, 0xFFFFFFFF, 0x00D40000, 0x3333F4C0, 0x0B40F4C0, 0x10001000, 0x10000000,
};

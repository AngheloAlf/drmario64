/**
 * Original filename: main_story.c
 */

#include "main_story.h"

#include "include_asm.h"
#include "macros_defines.h"
#include "unknown_structs.h"
#include "main_segment_variables.h"

#include "libc/assert.h"

#include "util.h"
#include "rom_offsets.h"
#include "audio/sound.h"
#include "buffers.h"
#include "tex_func.h"
#include "graphic.h"
#include "main1x.h"
#include "nnsched.h"
#include "lws.h"
#include "066840.h"

#include "graphbin.h"

#include "assets/coffee/coffee01.h"
#include "assets/title/title_all.h"
#include "assets/title/title_bmp.h"
#include "assets/waku/waku2.h"

#if VERSION_US || VERSION_GW || CC_CHECK
#else
// The compiler needs to not see the declared functions to match the cn version
#define AVOID_JOY_FUNCTIONS 1
#endif
#include "joy.h"

static s32 fin_frame_440;
static TitleAllLwsIndex fin_demo_441;
static s32 fin_frame_543;
static s32 fin_frame_568;
static TitleAllLwsIndex fin_demo_569;
static s32 fin_frame_623;
static TitleAllLwsIndex fin_demo_624;
static s32 fin_frame_667;
static s32 fin_frame_737;
static s32 fin_frame_768;
static s32 title_time;
static s32 title_wait;
static void *title_data;
static void *title_bmp_data;
static void **lws_data;
static Lws *lws_scene;
static MessageWnd mess_st;
static MessageWnd mess_roll_st;
static HEAP(mess_heap_area, 0x400);
static void *mess_roll_heap;
static s32 st_message_count;
static struct_mes_data *st_mes_ptr;
static bool loop_flg;
static s32 story_staff_roll;
static u16 story_norm;    /* Original name: story_norm */
static Mtx story_viewMtx; /* Original name: story_viewMtx */
static Mtx story_objectMtx[2][0x50];
static void *wakuGraphic;
static u8 D_800E8750[0x50] UNUSED;
static void *bgGraphic; /* Original name: bgGraphic */
static void *storyGraphic;
static void *messageData;
static s32 first_copy;

Mtx *pObjectMtx;

u8 D_800A73A0[] = {
    0x03, 0x25, 0x23, 0x2A, 0x24, 0x28, 0x27, 0x2B, 0x2C, 0x2C, 0x2C, 0x00,
    0x00, 0x25, 0x23, 0x2A, 0x24, 0x29, 0x26, 0x2B, 0x2C, 0x2C, 0x2C, 0x00,
};

// unused
Gfx D_800A73B8[] = {
    gsSPEndDisplayList(),
};

u8 curtain_alpha_00_tex[] ALIGNED(8) = {
#include "main_segment/main_story/curtain_alpha_00_tex.i4.inc"
};

u16 curtain_00_tex[] ALIGNED(8) = {
#include "main_segment/main_story/curtain_00_tex.rgba16.inc"
};

u8 changestar_tex[] ALIGNED(8) = {
#include "main_segment/main_story/changestar_tex.i4.inc"
};

typedef enum TitleBmpIndex {
    /* 0 */ TITLE_BMP_INDEX_NINTENDO_LOGO,
    /* 1 */ TITLE_BMP_INDEX_PRESS_ANY_BUTTON,
    /* 2 */ TITLE_BMP_INDEX_PRESS_ANY_BUTTON_SHADOW,
    /* 3 */ TITLE_BMP_INDEX_MAX,
} TitleBmpIndex;

/**
 * Original name: title_bmp_tbl
 */
void *title_bmp_tbl[] = {
    &title_bmp_00,
    &title_bmp_01,
    &title_bmp_02,
};

static_assert(ARRAY_COUNT(title_bmp_tbl) == TITLE_BMP_INDEX_MAX, "");

void *mess_heap = mess_heap_area;

#include "main_story.msg.inc"

/**
 * Original name: story_proc_no
 */
BgRomDataIndex story_proc_no = BGROMDATA_INDEX0;

char STR_800AACF0[] = MSG_COLOR(BLACK) "ＴＥＳＴ　" MSG_WAIT(2) MSG_END;

char *EndingLastMessage = STR_800AACF0;

s32 story_time_cnt = 0;

s32 story_seq_step = 0;

s32 story_zoom = 0;

s32 story_curtain = 0;

s32 story_spot_cnt = 0;

s32 story_kay_wait = 0;

s32 story_message_on = 0;

s32 story_message_start = 0;

s32 story_doing = 1;

s32 bgtime = 0;

s32 D_800AAD30 = 0;

s32 mes_time = 0;

u8 *story_read_buf = gfx_freebuf;

void *story_buffer = &gfx_freebuf[0x10000];

void *story_z_buffer = gfx_freebuf;

s32 objMtx_FF = 0;

typedef enum wakuGraphicIndex {
    /* 0 */ WAKUGRAPHICINDEX_0,
    /* 1 */ WAKUGRAPHICINDEX_1,
    /* 2 */ WAKUGRAPHICINDEX_2,
    /* 3 */ WAKUGRAPHICINDEX_MAX,
} wakuGraphicIndex;

/**
 * Original name: wakuGraphic_ofs
 */
void *wakuGraphic_ofs[] = {
    &waku2_00,
    &waku2_01,
    &waku2_02,
};

static_assert(ARRAY_COUNT(wakuGraphic_ofs) == WAKUGRAPHICINDEX_MAX, "");

Vp D_800AAD58 = { { { 0x280, 0x1E0, 0x1FF, 0 }, { 0x280, 0x1E0, 0x1FF, 0 } } };

Gfx story_setup[] = {
    gsDPPipeSync(),
    gsSPViewport(&D_800AAD58),
    gsDPSetBlendColor(0, 0, 0, 4),
    gsDPSetScissor(G_SC_NON_INTERLACE, 60, 37, 260, 137),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPPipelineMode(G_PM_1PRIMITIVE),
    gsDPSetRenderMode(G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_OFF),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsDPSetTextureConvert(G_TC_FILT),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_NONE),
    gsDPPipeSync(),
    gsSPEndDisplayList(),
};

// TODO: static_assert for array size
SeqIndex snd_tbl_838[] = {
    SEQ_INDEX_10, // BGROMDATA_INDEX0
    SEQ_INDEX_10, // BGROMDATA_INDEX1
    SEQ_INDEX_20, // BGROMDATA_INDEX2
    SEQ_INDEX_19, // BGROMDATA_INDEX3
    SEQ_INDEX_20, // BGROMDATA_INDEX4
    SEQ_INDEX_19, // BGROMDATA_INDEX5
    SEQ_INDEX_20, // BGROMDATA_INDEX6
    SEQ_INDEX_19, // BGROMDATA_INDEX7
    SEQ_INDEX_21, // BGROMDATA_INDEX8
    SEQ_INDEX_20, // BGROMDATA_INDEX9
    SEQ_INDEX_22, // BGROMDATA_INDEX10
    SEQ_INDEX_22, // BGROMDATA_INDEX11
    SEQ_INDEX_10, // BGROMDATA_INDEX12
    SEQ_INDEX_10, // BGROMDATA_INDEX13
    SEQ_INDEX_20, // BGROMDATA_INDEX14
    SEQ_INDEX_19, // BGROMDATA_INDEX15
    SEQ_INDEX_20, // BGROMDATA_INDEX16
    SEQ_INDEX_19, // BGROMDATA_INDEX17
    SEQ_INDEX_20, // BGROMDATA_INDEX18
    SEQ_INDEX_19, // BGROMDATA_INDEX19
    SEQ_INDEX_21, // BGROMDATA_INDEX20
    SEQ_INDEX_20, // BGROMDATA_INDEX21
    SEQ_INDEX_22, // BGROMDATA_INDEX22
    SEQ_INDEX_22, // BGROMDATA_INDEX23
};
static_assert(ARRAY_COUNT(snd_tbl_838) == BGROMDATA_MAX, "");

/**
 * Original name: story_zoomfade
 */
void story_zoomfade(Gfx **gfxP, s32 arg1) {
    Gfx *gfx = *gfxP;
    u16 *framebuffer = gFramebuffers[gCurrentFramebufferIndex ^ 1];
    f32 temp_fs1_2;
    f32 temp_ft1;
    s32 var_v1;
    f32 temp;
    f32 argA;
    f32 new_var;
    f32 argB;
    f32 temp3;

    gSPDisplayList(gfx++, normal_texture_init_dl);

    gDPSetTextureLUT(gfx++, G_TT_NONE);
    gDPSetTextureFilter(gfx++, G_TF_BILERP);
    gDPSetEnvColor(gfx++, 255, 255, 255, 255);
    gDPSetRenderMode(gfx++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
    gDPSetCombineLERP(gfx++, TEXEL0, ENVIRONMENT, PRIMITIVE, ENVIRONMENT, 0, 0, 0, 1, TEXEL0, ENVIRONMENT, PRIMITIVE,
                      ENVIRONMENT, 0, 0, 0, 1);

    arg1 = MAX(arg1, 0);
    arg1 = MIN(arg1, 0x5A);

    temp_ft1 = arg1;
    temp_ft1 = temp_ft1 / 90.0f;

    if (temp_ft1 > 0.75) {
        temp = (temp_ft1 - 0.75) / (1 / 4.0);
        temp3 = 223.125f;
        temp_fs1_2 = 31.875f;

        var_v1 = (255.0f - temp3 * temp) - temp_fs1_2;
        var_v1 = MAX(var_v1, 0);
    } else {
        var_v1 = (temp_ft1 * 255.0f) / 6.0;
        var_v1 = 0xFF - var_v1;
    }

    gDPSetPrimColor(gfx++, 0, 0, var_v1, var_v1, var_v1, 255);

    temp_fs1_2 = sinf(temp_ft1 * 6.0f) * 1.5;
    temp = cosf(temp_ft1 * 6.0f) * 1.5;
    temp_ft1 = 2.0 * temp_ft1 + 1.0;

    temp_fs1_2 *= temp_ft1;
    temp *= temp_ft1;

    temp_ft1 = 1.0625;
    argA = 320.0 * temp_ft1;
    new_var = 320.0f;
    argB = 240.0 * temp_ft1;
    temp_fs1_2 += (320.0 - argA) / 2;
    temp += (240.0 - argB) / 2;
    StretchTexTile16(&gfx, SCREEN_WIDTH, SCREEN_HEIGHT, framebuffer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, temp_fs1_2,
                     temp, argA, argB);

    gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gDPSetCombineLERP(gfx++, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE);
    gDPSetPrimColor(gfx++, 0, 0, 128, 128, 128, 50);

    StretchTexTile16(&gfx, SCREEN_WIDTH, SCREEN_HEIGHT, framebuffer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f,
                     new_var, 240.0f);

    *gfxP = gfx;
}

/**
 * Original name: get_gbi_stat
 */
void get_gbi_stat(GbiStat *arg0, GraphBinGeneric *graphBin) {
    arg0->width = graphBin->header.width;
    arg0->height = graphBin->header.height;
    arg0->siz = graphBin->header.siz;
    arg0->tlut = graphBin->header.tlut;
    arg0->texture = graphBin->texture;
}

/**
 * Original name: curtain_proc
 */
void curtain_proc(Gfx **gfxP, s32 arg1) {
    Gfx *gfx = *gfxP;
    f32 temp;
    s32 alpha;

    if (arg1 <= 0) {
        return;
    }

    arg1 = MIN(arg1, 30);

    temp = arg1 + 1;
    temp /= 30.0f;

    alpha = temp * 255.0 + 0.5;
    alpha = MIN(alpha, 255);

    gDPSetCombineMode(gfx++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
    gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, alpha);
    gDPFillRectangle(gfx++, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    *gfxP = gfx;
}

/**
 * Original name: curtain_proc_org
 */
void curtain_proc_org(Gfx **gfxP, s32 arg1) {
    Gfx *gfx = *gfxP;
    f32 temp_fv1;
    f32 var_fv0;
    s32 temp_ft3;
    s32 var_t8;
    f32 ftemp;
    f32 ftemp2;
    s32 temp;

    if (arg1 <= 0) {
        return;
    }

    arg1 = MIN(arg1, 0x1E);

    gSPDisplayList(gfx++, alpha_texture_init_dl);
    gDPLoadTextureBlock(gfx++, curtain_00_tex, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 48, 0, G_TX_MIRROR | G_TX_WRAP,
                        G_TX_NOMIRROR | G_TX_CLAMP, 5, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gDPLoadMultiBlock_4b(gfx++, curtain_alpha_00_tex, 0x0180, 1, G_IM_FMT_I, 32, 48, 0, G_TX_MIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_CLAMP, 5, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    ftemp = arg1;
    ftemp /= 30.0f;

    for (var_t8 = 0; var_t8 < 7; var_t8++) {
        temp_fv1 = (6 - var_t8) * 0x28;
        ftemp2 = var_t8 * 8;

        var_fv0 = (ftemp * 280.0f - 48.0) - ftemp2;
        if (temp_fv1 < var_fv0) {
            var_fv0 = temp_fv1;
        }

        temp_ft3 = var_fv0 * 4.0 + 0.5;
        temp = temp_ft3 + 0xC0;

        gSPTextureRectangle(gfx++, 0, temp_ft3, 0x0500, temp, G_TX_RENDERTILE, 0, 0, 0x0400, 0x0400);
    }

    *gfxP = gfx;
}

void func_800770E8(Gfx **gfxP, GraphBinGeneric *graphBin) {
    Gfx *gfx = *gfxP;

    gSPDisplayList(gfx++, normal_texture_init_dl);
    StretchTexBlock8(&gfx, SCREEN_WIDTH + 8, SCREEN_HEIGHT, graphBin->header.tlut, &graphBin->texture, 0.0f, 0.0f,
                     SCREEN_WIDTH + 8, SCREEN_HEIGHT);
    *gfxP = gfx;
}

/**
 * Original name: story_bg_init
 */
void *story_bg_init(BgRomDataIndex index, void *dstAddr) {
    bgGraphic = dstAddr;
    wakuGraphic =
        ALIGN_PTR(DecompressRomToRam(bgRomData[index].start, dstAddr, bgRomData[index].end - bgRomData[index].start));
    return ALIGN_PTR(DecompressRomToRam(storyRomData[STORYROMDATA_WAKU2].start, wakuGraphic,
                                        storyRomData[STORYROMDATA_WAKU2].end - storyRomData[STORYROMDATA_WAKU2].start));
}

/**
 * Original name: story_bg_proc
 */
void story_bg_proc(Gfx **gfxP) {
    GbiStat sp48;
    GbiStat sp60;
    s32 pad[0x10] UNUSED;
    Gfx *gfx = *gfxP;

    get_gbi_stat(&sp48, bgGraphic);

    gSPDisplayList(gfx++, normal_texture_init_dl);
    StretchTexBlock8(&gfx, sp48.width, sp48.height, sp48.tlut, sp48.texture, 0.0f, 0.0f, sp48.width, sp48.height);

    get_gbi_stat(&sp48, RELOCATE_OFFSET(wakuGraphic, wakuGraphic_ofs[WAKUGRAPHICINDEX_0]));
    get_gbi_stat(&sp60, RELOCATE_OFFSET(wakuGraphic, wakuGraphic_ofs[WAKUGRAPHICINDEX_1]));

    gSPDisplayList(gfx++, alpha_texture_init_dl);
    StretchAlphaTexTile(&gfx, sp48.width, sp48.height, sp48.texture, sp48.width, sp60.texture, sp60.width, 0, 0,
                        sp48.width, sp48.height, 0.0f, 140.0f, sp48.width, sp48.height);

    get_gbi_stat(&sp48, RELOCATE_OFFSET(wakuGraphic, wakuGraphic_ofs[WAKUGRAPHICINDEX_2]));

    gSPDisplayList(gfx++, normal_texture_init_dl);
    StretchTexTile8(&gfx, sp48.width, sp48.height, sp48.tlut, sp48.texture, 0, 0, sp48.width, sp48.height, 0.0f, 160.0f,
                    sp48.width, sp48.height);

    *gfxP = gfx;
}

void func_800773F0(void) {
    if (story_curtain == 0) {
        story_time_cnt = 0;
        story_message_on = 1;
        story_message_start = 0;
        story_seq_step++;
    } else {
        story_message_on = 0;
        story_curtain--;
    }
}

void func_8007744C(void) {
    story_doing = 0;
    story_zoom++;
}

void func_8007746C(void) {
    msgWnd_clear(&mess_st);
    story_kay_wait = 0;
    story_message_start = 0;
    story_time_cnt = 0;
    story_message_start = 0;
    story_seq_step++;
}

bool func_800774C4(void) {
    bool temp_v0 = msgWnd_isEnd(&mess_st);

    if (temp_v0) {
        func_8007746C();
    }
    return temp_v0;
}

/**
 * Original name: story_bg_proc
 */
void story_spot(Gfx **gfxP, s32 arg1, s32 arg2, s32 arg3, void *tex) {
    s32 pad[6] UNUSED;
    Gfx *gfx = *gfxP;
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_fv1;
    s32 temp_ft4;
    s32 temp_ft4_2;
    s32 temp_ft4_3;
    s32 temp_ft4_4;
    f32 a;
    f32 b;
    f32 a1;
    f32 a2;

    if (arg3 >= 0xFF) {
        return;
    }

    if (arg3 < 0) {
        arg3 = 0;
    }

    temp_fa0 = ((f32)arg3 / 18.0);
    a1 = arg1;
    a2 = arg2;

    a = temp_fa0 * 64.0;
    b = temp_fa0 * 64.0;

    temp_fa1 = (a1 - a / 2.0);
    temp_fv1 = (a2 - b / 2.0);

    temp_ft4 = temp_fa1 + 1.0f;
    temp_ft4_2 = temp_fa1 + a - 1.0f;
    temp_ft4_3 = temp_fv1 + 1.0f;
    temp_ft4_4 = temp_fv1 + b - 1.0f;

    gDPSetTextureLUT(gfx++, G_TT_NONE);

    gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, 255);

    gDPSetRenderMode(gfx++, G_RM_OPA_SURF, G_RM_OPA_SURF2);

    gDPSetCombineMode(gfx++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);

    if ((a < 1.0f) || (b < 1.0f)) {
        arg3 = 0;
    }

    if (arg3 == 0) {
        gDPFillRectangle(gfx++, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    } else {
        if (temp_ft4 > 0) {
            gDPFillRectangle(gfx++, 0, 0, temp_ft4, SCREEN_HEIGHT);
        }
        if (temp_ft4_2 < SCREEN_WIDTH) {
            gDPFillRectangle(gfx++, temp_ft4_2, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        }
        if (temp_ft4_3 > 0) {
            gDPFillRectangle(gfx++, 0, 0, SCREEN_WIDTH, temp_ft4_3);
        }
        if (temp_ft4_4 < SCREEN_HEIGHT) {
            gDPFillRectangle(gfx++, 0, temp_ft4_4, SCREEN_WIDTH, SCREEN_HEIGHT);
        }

        gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
        gDPSetCombineLERP(gfx++, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0);

        StretchTexBlock4i(&gfx, 0x40, 0x40, tex, temp_fa1, temp_fv1, a, b);
    }

    gSPDisplayList(gfx++, normal_texture_init_dl);

    *gfxP = gfx;
}

void func_800777E8(Gfx **gfxP, s32 arg1, s32 arg2, s32 arg3) {
    story_spot(gfxP, arg1, arg2, arg3, changestar_tex);
}

/**
 * Original name: init_coffee_break
 */
void *init_coffee_break(void *dstAddr, UNK_TYPE arg1 UNUSED) {
    void *temp_s0;

    bgGraphic = ALIGN_PTR(dstAddr);
    temp_s0 = ALIGN_PTR(
        DecompressRomToRam(storyRomData[STORYROMDATA_COFFEE_01].start, bgGraphic,
                           storyRomData[STORYROMDATA_COFFEE_01].end - storyRomData[STORYROMDATA_COFFEE_01].start));
    init_coffee_break_cnt();
    return temp_s0;
}

/**
 * Original name: init_coffee_break_cnt
 */
void init_coffee_break_cnt(void) {
    guOrtho(&story_viewMtx, -160.0f, 160.0f, -120.0f, 120.0f, 1.0f, 2000.0f, 1.0f);
    bgtime = 0;
    mes_time = 0x15E;
    story_time_cnt = -0x59;
    story_seq_step = 0;
}

/**
 * Original name: draw_coffee_break
 */
void draw_coffee_break(Gfx **gfxP, s32 arg1, s32 arg2, s32 arg3) {
    Mtx mtx;
    Gfx *gfx;
    bool var_s1;
    Lws *var_v0;
    Lws *var_s0;

    init_objMtx();

    gfx = *gfxP;

    gSPSegment(gfx++, 0x00, 0x00000000);
    gSPSegment(gfx++, 0x05, osVirtualToPhysical(bgGraphic));
    gSPMatrix(gfx++, OS_K0_TO_PHYSICAL(&story_viewMtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gSPDisplayList(gfx++, normal_texture_init_dl);
    gSPDisplayList(gfx++, story_setup);
    gDPSetScissor(gfx++, G_SC_NON_INTERLACE, 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1);

    lws_data = (void **)bgGraphic;
    if (arg2 != 0) {
        gDPSetEnvColor(gfx++, 183, 127, 95, 255);
        var_s0 = RELOCATE_SEGMENTED(lws_data[COFFEE01_LWS_INDEX_1], bgGraphic);
        var_v0 = RELOCATE_SEGMENTED(lws_data[COFFEE01_LWS_INDEX_6], bgGraphic);
    } else {
        gDPSetEnvColor(gfx++, 255, 255, 255, 255);
        var_s0 = RELOCATE_SEGMENTED(lws_data[COFFEE01_LWS_INDEX_0], bgGraphic);
        var_v0 = RELOCATE_SEGMENTED(lws_data[COFFEE01_LWS_INDEX_5], bgGraphic);
    }

    makeTransrateMatrix(&mtx, 0U, 0xFFC40000U, 0xFC4A0000U);
    if (lws_anim(&gfx, &mtx, var_s0, bgtime, bgGraphic) == 1) {
        bgtime = 0x31;
    }

    bgtime += 1;
    switch (story_seq_step) {
        case 0:
            var_s0 = RELOCATE_SEGMENTED(lws_data[COFFEE01_LWS_INDEX_2], bgGraphic);
            break;

        case 1:
            var_s0 = RELOCATE_SEGMENTED(lws_data[COFFEE01_LWS_INDEX_3], bgGraphic);
            break;

        case 2:
            var_s0 = RELOCATE_SEGMENTED(lws_data[COFFEE01_LWS_INDEX_4], bgGraphic);
            break;

        default:
            var_s0 = NULL;
            story_time_cnt = -1;
            break;
    }

    var_s1 = false;
    if ((story_time_cnt >= 0) && (var_s0 != NULL)) {
        if (lws_anim(&gfx, &mtx, var_s0, story_time_cnt, bgGraphic) == 1) {
            var_s1 = true;
            story_time_cnt = -1;
            story_seq_step++;
        }
    }

    story_time_cnt++;

    if (var_s1) {
        switch (arg1) {
            case 0:
                story_seq_step = 3;
                break;

            case 1:
                if (story_seq_step == 1) {
                    story_time_cnt = -0x3C;
                } else {
                    story_seq_step = 3;
                }
                break;

            default:
                if (story_seq_step == 1) {
                    story_time_cnt = -0x3C;
                } else if (story_seq_step == 2) {
                    story_time_cnt = -0x28;
                } else {
                    story_seq_step = 3;
                }
                break;
        }
    }

    if (arg3 != 0) {
        if (lws_anim(&gfx, &mtx, var_v0, mes_time, bgGraphic) == 1) {
            mes_time = 0x28A;
        } else {
            mes_time = mes_time + 1;
        }
    }

    gDPSetCycleType(gfx++, G_CYC_1CYCLE);
    gDPSetRenderMode(gfx++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
    gDPSetCombineMode(gfx++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
    gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, 255);
    gDPFillRectangle(gfx++, 0, 0, SCREEN_WIDTH, 32);
    gDPFillRectangle(gfx++, 0, 208, SCREEN_WIDTH, SCREEN_HEIGHT);
    gSPDisplayList(gfx++, normal_texture_init_dl);

    *gfxP = gfx;
}

/**
 * Original name: init_menu_bg
 */
void *init_menu_bg(void *dstAddr, bool arg1) {
    void *alignedAddress;
    RomOffset segmentRomStart;
    RomOffset segmentRomEnd;

    bgtime = 0;
    guOrtho(&story_viewMtx, -160.0f, 160.0f, -120.0f, 120.0f, 1.0f, 2000.0f, 1.0f);
    alignedAddress = ALIGN_PTR(dstAddr);
    bgGraphic = alignedAddress;
    if (arg1) {
        segmentRomStart = storyRomData[STORYROMDATA_MENU_BG2].start;
        segmentRomEnd = storyRomData[STORYROMDATA_MENU_BG2].end;
    } else {
        segmentRomStart = storyRomData[STORYROMDATA_MENU_BG].start;
        segmentRomEnd = storyRomData[STORYROMDATA_MENU_BG].end;
    }
    return ALIGN_PTR(DecompressRomToRam(segmentRomStart, alignedAddress, segmentRomEnd - segmentRomStart));
}

/**
 * Original name: draw_menu_bg
 */
void draw_menu_bg(Gfx **gfxP, s32 arg1, s32 arg2) {
    Mtx mtx;
    Gfx *gfx;

    init_objMtx();

    gfx = *gfxP;

    gSPSegment(gfx++, 0x00, 0x00000000);
    gSPSegment(gfx++, 0x05, osVirtualToPhysical(bgGraphic));
    gSPMatrix(gfx++, OS_K0_TO_PHYSICAL(&story_viewMtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gSPDisplayList(gfx++, normal_texture_init_dl);
    gSPDisplayList(gfx++, story_setup);
    gDPSetScissor(gfx++, G_SC_NON_INTERLACE, 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1);

    makeTransrateMatrix(&mtx, arg1 << 0xF, arg2 << 0xF, 0x1F894 << 0xF);
    if (lws_anim(&gfx, &mtx, bgGraphic, bgtime, bgGraphic) == 1) {
        bgtime = 0;
    } else {
        bgtime += 1;
    }

    gSPDisplayList(gfx++, normal_texture_init_dl);

    *gfxP = gfx;
}

/**
 * Original name: init_title
 */
void *init_title(void *dstAddr, bool arg1) {
    if (arg1) {
        title_time = 0;
        story_spot_cnt = -0x64;
    } else {
        title_time = 0x2D0;
        story_spot_cnt = 0x100;
    }

    title_wait = 0;
    guOrtho(&story_viewMtx, -160.0f, 160.0f, -120.0f, 120.0f, 1.0f, 2000.0f, 1.0f);

    title_data = ALIGN_PTR(dstAddr);
    title_bmp_data = ALIGN_PTR(
        DecompressRomToRam(storyRomData[STORYROMDATA_TITLE_ALL].start, title_data,
                           storyRomData[STORYROMDATA_TITLE_ALL].end - storyRomData[STORYROMDATA_TITLE_ALL].start));
    return ALIGN_PTR(
        DecompressRomToRam(storyRomData[STORYROMDATA_TITLE_BMP].start, title_bmp_data,
                           storyRomData[STORYROMDATA_TITLE_BMP].end - storyRomData[STORYROMDATA_TITLE_BMP].start));
}

/**
 * Original name: demo_title
 */
s32 demo_title(Gfx **gfxP, bool arg1) {
    GbiStat textureInfo;
    GbiStat shadowInfo;
    Mtx mtx;
    Gfx *gfx;
    bool temp_s2;
    s32 color;
    s32 var_s3;
    u32 var_v0_3;

    init_objMtx();

    var_s3 = 0;
    if (title_time >= 720) {
        temp_s2 = true;
    } else {
        temp_s2 = false;
    }

    gfx = *gfxP;

    gSPSegment(gfx++, 0x00, 0x00000000);
    gSPSegment(gfx++, 0x05, osVirtualToPhysical(title_data));
    gSPMatrix(gfx++, OS_K0_TO_PHYSICAL(&story_viewMtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gSPDisplayList(gfx++, normal_texture_init_dl);
    gSPDisplayList(gfx++, story_setup);
    gDPSetScissor(gfx++, G_SC_NON_INTERLACE, 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1);

    lws_data = title_data;
    if (arg1) {
        gDPSetEnvColor(gfx++, 183, 127, 95, 255);

        lws_scene = RELOCATE_SEGMENTED(lws_data[TITLEALL_LWS_INDEX_33], title_data);
    } else {
        gDPSetEnvColor(gfx++, 255, 255, 255, 255);

        lws_scene = RELOCATE_SEGMENTED(lws_data[TITLEALL_LWS_INDEX_0], title_data);
    }

    makeTransrateMatrix(&mtx, 0, 0xFFC4 << 16, 0xFC4A << 16);

    if ((story_spot_cnt > 0) && (gControllerPressedButtons[main_joy[0]] & ANY_BUTTON)) {
        if (temp_s2) {
            if (title_wait == 0) {
                dm_snd_play(SND_INDEX_103);
                title_wait = 1;
            }
        } else {
            title_time = 720;
        }
    }

    if (title_wait > 0) {
        title_wait++;
        if (title_wait >= 0x3C) {
            var_s3 = 1;
        }
    }

    if (lws_anim(&gfx, &mtx, lws_scene, title_time, title_data) == 1) {
        var_s3 = -1;
    }

    gSPDisplayList(gfx++, normal_texture_init_dl);

    if (story_spot_cnt > 0) {
        title_time++;
    }

    if (story_spot_cnt < 0x100) {
        gSPDisplayList(gfx++, normal_texture_init_dl);
        story_spot(&gfx, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, story_spot_cnt, changestar_tex);

        if (story_spot_cnt < 0) {
            color = 255;
            if (story_spot_cnt > -0x18) {
                color = (story_spot_cnt * -255) / 24;
                if (color > 255) {
                    color = 255;
                }
                if (color < 0) {
                    color = 0;
                }
            }

            if (story_spot_cnt < -0x4C) {
                color = 255 - (((story_spot_cnt + 0x4C) * -255) / 24);
                if (color > 255) {
                    color = 255;
                }
                if (color < 0) {
                    color = 0;
                }
            }

            get_gbi_stat(&textureInfo, RELOCATE_OFFSET(title_bmp_data, title_bmp_tbl[TITLE_BMP_INDEX_NINTENDO_LOGO]));

            gDPSetTextureLUT(gfx++, G_TT_NONE);
            gDPSetPrimColor(gfx++, 0, 0, color, color, color, 255);
            gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
            gDPSetCombineLERP(gfx++, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0);

            StretchTexBlock4i(&gfx, textureInfo.width, textureInfo.height, textureInfo.texture,
                              SCREEN_WIDTH / 2 - textureInfo.width / 2, SCREEN_HEIGHT / 2 - textureInfo.height / 2,
                              textureInfo.width, textureInfo.height);

            story_spot_cnt += 1;
        } else {
            story_spot_cnt += 5;
        }
    }

    var_v0_3 = 1;
    if (title_wait == 0) {
        var_v0_3 = 0x10;
    }

    if ((title_time & var_v0_3) && (title_time > 720) && (title_wait == 0)) {
        get_gbi_stat(&textureInfo, RELOCATE_OFFSET(title_bmp_data, title_bmp_tbl[TITLE_BMP_INDEX_PRESS_ANY_BUTTON]));
        get_gbi_stat(&shadowInfo,
                     RELOCATE_OFFSET(title_bmp_data, title_bmp_tbl[TITLE_BMP_INDEX_PRESS_ANY_BUTTON_SHADOW]));

        gSPDisplayList(gfx++, alpha_texture_init_dl);
        StretchAlphaTexBlock(&gfx, textureInfo.width, textureInfo.height, textureInfo.texture, textureInfo.width,
                             shadowInfo.texture, shadowInfo.width, 88.0f, 165.0f, textureInfo.width,
                             textureInfo.height);
    }

    *gfxP = gfx;
    return var_s3;
}

// unused
void func_80078648(Gfx **gfxP) {
    Gfx *gfx = *gfxP;
    s32 pad[0x1C] UNUSED;

    *gfxP = gfx;
}

void func_8007865C(void) {
    if (st_message_count < st_mes_ptr->unk_0) {
        if (st_mes_ptr[st_message_count + 1].unk_0 < framecont) {
            msgWnd_clear(&mess_st);
            msgWnd_addStr(&mess_st, st_mes_ptr[st_message_count + 1].unk_4);
            st_message_count++;

            if (gControllerHoldButtons[main_joy[0]] & A_BUTTON) {
                msgWnd_skip(&mess_st);
            }
        }
    } else {
        st_message_count = 9999;
    }
}

/**
 * Original name: story_st_new_op
 */
void story_st_new_op(Gfx **gfxP, bool arg1) {
    Gfx *gfx = *gfxP;
    Mtx mtx;
    TitleAllLwsIndex var_s0;
    s32 var_v0;
    s32 var_v1;

    gSPDisplayList(gfx++, normal_texture_init_dl);
    gSPDisplayList(gfx++, story_setup);

    makeTransrateMatrix(&mtx, 0U, 0xFFF38000U, 0xFC4A0000U);

    switch (story_seq_step) {
        case 0x0:
            if (arg1) {
                var_s0 = TITLEALL_LWS_INDEX_26;
            } else {
                var_s0 = TITLEALL_LWS_INDEX_27;
            }

            func_800773F0();
            lws_anim(&gfx, &mtx, RELOCATE_SEGMENTED(lws_data[var_s0], story_buffer), 0, story_buffer);
            framecont = 0;
            fin_frame_440 = 0;
            fin_demo_441 = var_s0;
            break;

        case 0x1:
            if (arg1) {
                var_s0 = TITLEALL_LWS_INDEX_26;
                var_v1 = 0;
            } else {
                var_s0 = TITLEALL_LWS_INDEX_27;
                var_v1 = 1;
            }
            fin_demo_441 = var_s0;
            story_time_cnt = framecont;
            fin_frame_440 = framecont;
            st_mes_ptr = mes_data[var_v1];

            if (gControllerPressedButtons[main_joy[0]] & (B_BUTTON | START_BUTTON)) {
                framecont = 0;
                story_time_cnt = 0;
                st_message_count = 0;
                story_seq_step += 0x63;
            }

            if (gControllerHoldButtons[main_joy[0]] & A_BUTTON) {
                story_time_cnt += 3;
                framecont += 3;
            }

            func_8007865C();
            if (lws_anim(&gfx, &mtx, RELOCATE_SEGMENTED(lws_data[var_s0], story_buffer), story_time_cnt,
                         story_buffer) == 1) {
                if (msgWnd_isEnd(&mess_st)) {
                    framecont = 0;
                    story_time_cnt = 0;
                    st_message_count = 0;
                    story_seq_step += 1;
                }
            }
            break;

        case 0x2:
            var_s0 = TITLEALL_LWS_INDEX_28;
            fin_demo_441 = var_s0;
            story_time_cnt = framecont;
            fin_frame_440 = framecont;
            st_mes_ptr = mes_data[2];
            if (gControllerPressedButtons[main_joy[0]] & (B_BUTTON | START_BUTTON)) {
                framecont = 0;
                story_time_cnt = 0;
                st_message_count = 0;
                story_seq_step += 0x63;
            }
            if (gControllerHoldButtons[main_joy[0]] & A_BUTTON) {
                story_time_cnt += 3;
                framecont += 3;
            }

            func_8007865C();
            if (lws_anim(&gfx, &mtx, RELOCATE_SEGMENTED(lws_data[var_s0], story_buffer), story_time_cnt,
                         story_buffer) == 1) {
                if (msgWnd_isEnd(&mess_st)) {
                    framecont = 0;
                    story_time_cnt = 0;
                    st_message_count = 0;
                    story_seq_step += 1;
                }
            }

            if (fin_frame_440 > 0x61D) {
                var_v0 = fin_frame_440 - 0x61D;
                var_v0 = ((0x1E - var_v0) * 0xFF) / 30;

                gSPDisplayList(gfx++, normal_texture_init_dl);

                story_spot(&gfx, 0xA0, 0x56, var_v0, changestar_tex);
            }
            break;

        case 0x3:
            var_s0 = TITLEALL_LWS_INDEX_29;
            fin_demo_441 = var_s0;
            story_time_cnt = framecont;
            fin_frame_440 = framecont;
            st_mes_ptr = mes_data[3];
            if (gControllerPressedButtons[main_joy[0]] & (B_BUTTON | START_BUTTON)) {
                framecont = 0;
                story_time_cnt = 0;
                st_message_count = 0;
                story_seq_step += 0x63;
            }

            if (gControllerHoldButtons[main_joy[0]] & A_BUTTON) {
                story_time_cnt += 3;
                framecont += 3;
            }

            func_8007865C();
            if (lws_anim(&gfx, &mtx, RELOCATE_SEGMENTED(lws_data[var_s0], story_buffer), story_time_cnt,
                         story_buffer) == 1) {
                if (msgWnd_isEnd(&mess_st)) {
                    framecont = 0;
                    story_time_cnt = 0;
                    st_message_count = 0;
                    story_seq_step += 1;
                }
            }

            if (fin_frame_440 < 0x1E) {
                var_v0 = fin_frame_440;
                var_v0 = (var_v0 * 0xFF) / 30;
                gSPDisplayList(gfx++, normal_texture_init_dl);

                story_spot(&gfx, 0xA0, 0x56, var_v0, changestar_tex);
            }
            if (fin_frame_440 > 0x262) {
                var_v0 = fin_frame_440 - 0x262;
                var_v0 = ((0x1E - var_v0) * 0xFF) / 30;

                gSPDisplayList(gfx++, normal_texture_init_dl);

                story_spot(&gfx, 0xA0, 0x56, var_v0, changestar_tex);
            }
            break;

        case 0x4:
            var_s0 = TITLEALL_LWS_INDEX_1;
            fin_demo_441 = var_s0;
            story_time_cnt = framecont;
            fin_frame_440 = story_time_cnt;
            st_mes_ptr = mes_data[4];
            if (gControllerPressedButtons[main_joy[0]] & (B_BUTTON | START_BUTTON)) {
                story_time_cnt = 0;
                story_seq_step += 1;
            }
            if (gControllerHoldButtons[main_joy[0]] & A_BUTTON) {
                framecont += 3;
                story_time_cnt += 3;
            }

            func_8007865C();
            if (lws_anim(&gfx, &mtx, RELOCATE_SEGMENTED(lws_data[var_s0], story_buffer), story_time_cnt,
                         story_buffer) == 1) {
                if (msgWnd_isEnd(&mess_st)) {
                    story_time_cnt = 0;
                    story_seq_step += 1;
                }
            }
            if (fin_frame_440 < 0x1E) {
                var_v0 = fin_frame_440;
                var_v0 = (var_v0 * 0xFF) / 30;

                gSPDisplayList(gfx++, normal_texture_init_dl);
                story_spot(&gfx, 0xA0, 0x56, var_v0, changestar_tex);
            }
            break;

        default:
            func_8007744C();
            lws_anim(&gfx, &mtx, RELOCATE_SEGMENTED(lws_data[fin_demo_441], story_buffer), fin_frame_440, story_buffer);
            break;
    }

    gDPSetScissor(gfx++, G_SC_NON_INTERLACE, 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1);

    *gfxP = gfx;
}

/**
 * Original name: story_st_new
 */
void story_st_new(Gfx **gfxP, TitleAllLwsIndex arg1, s32 arg2) {
    Mtx mtx;
    Gfx *gfx = *gfxP;
    Lws *lws;

    st_mes_ptr = mes_data[arg2];

    gSPDisplayList(gfx++, normal_texture_init_dl);

    gSPDisplayList(gfx++, story_setup);

    makeTransrateMatrix(&mtx, 0, 0x1FFE7 << 0xF, 0x1F894 << 0xF);

    lws = RELOCATE_SEGMENTED(lws_data[arg1], story_buffer);

    switch (story_seq_step) {
        case 0:
            func_800773F0();
            lws_anim(&gfx, &mtx, lws, 0, story_buffer);
            framecont = 0;
            break;

        case 1:
            story_time_cnt = framecont;
            fin_frame_543 = framecont;
            if (gControllerPressedButtons[main_joy[0]] & (START_BUTTON | B_BUTTON)) {
                story_seq_step = 2;
                story_time_cnt = 0;
            }
            if (gControllerHoldButtons[main_joy[0]] & A_BUTTON) {
                framecont += 3;
                story_time_cnt += 3;
            }

            func_8007865C();
            if ((lws_anim(&gfx, &mtx, lws, story_time_cnt, story_buffer) == 1) && msgWnd_isEnd(&mess_st)) {
                story_time_cnt = 0;
                story_seq_step++;
            }
            break;

        default:
            func_8007744C();
            lws_anim(&gfx, &mtx, lws, fin_frame_543, story_buffer);
            break;
    }

    gDPSetScissor(gfx++, G_SC_NON_INTERLACE, 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1);

    *gfxP = gfx;
}

/**
 * Original name: story_st_new2_f
 */
void story_st_new2_f(Gfx **gfxP, TitleAllLwsIndex arg1, s32 arg2, TitleAllLwsIndex arg3, s32 arg4) {
    Gfx *gfx = *gfxP;
    Mtx mtx;
    s32 temp;

    gSPDisplayList(gfx++, normal_texture_init_dl);
    gSPDisplayList(gfx++, story_setup);

    makeTransrateMatrix(&mtx, 0U, 0xFFF38000U, 0xFC4A0000U);

    lws_scene = RELOCATE_SEGMENTED(lws_data[arg1], story_buffer);

    switch (story_seq_step) {
        case 0x0:
            func_800773F0();
            lws_anim(&gfx, &mtx, RELOCATE_SEGMENTED(lws_data[arg1], story_buffer), 0, story_buffer);
            framecont = 0;
            fin_frame_568 = 0;
            fin_demo_569 = arg1;
            break;

        case 0x1:
            fin_demo_569 = arg1;
            story_time_cnt = framecont;
            fin_frame_568 = framecont;
            st_mes_ptr = mes_data[arg2];
            if (gControllerPressedButtons[main_joy[0]] & (START_BUTTON | B_BUTTON)) {
                story_seq_step = 0x64;
                framecont = 0;
                story_time_cnt = 0;
                st_message_count = 0;
            }
            if (gControllerHoldButtons[main_joy[0]] & A_BUTTON) {
                story_time_cnt += 3;
                framecont += 3;
            }

            func_8007865C();
            if (lws_anim(&gfx, &mtx, RELOCATE_SEGMENTED(lws_data[arg1], story_buffer), story_time_cnt, story_buffer) ==
                1) {
                if (msgWnd_isEnd(&mess_st)) {
                    framecont = 0;
                    story_time_cnt = 0;
                    st_message_count = 0;
                    story_seq_step += 1;
                }
            }

            if (fin_frame_568 > (lws_scene->unk_04 - 0x20)) {
                temp = fin_frame_568 - (lws_scene->unk_04 - 0x20);
                temp = ((0x1E - temp) * 0xFF) / 30;

                gSPDisplayList(gfx++, normal_texture_init_dl);
                story_spot(&gfx, 0xA0, 0x56, temp, changestar_tex);
            }
            break;

        case 0x2:
            fin_demo_569 = arg3;
            story_time_cnt = framecont;
            fin_frame_568 = framecont;
            st_mes_ptr = mes_data[arg4];
            if (gControllerPressedButtons[main_joy[0]] & (START_BUTTON | B_BUTTON)) {
                story_seq_step = 3;
                story_time_cnt = 0;
            }
            if (gControllerHoldButtons[main_joy[0]] & A_BUTTON) {
                framecont += 3;
                story_time_cnt += 3;
            }

            func_8007865C();
            if ((lws_anim(&gfx, &mtx, RELOCATE_SEGMENTED(lws_data[arg3], story_buffer), story_time_cnt, story_buffer) ==
                 1) &&
                msgWnd_isEnd(&mess_st)) {
                story_time_cnt = 0;
                story_seq_step += 1;
            }
            if (fin_frame_568 < 0x1E) {
                temp = fin_frame_568;
                temp = (temp * 0xFF) / 30;

                gSPDisplayList(gfx++, normal_texture_init_dl);
                story_spot(&gfx, 0xA0, 0x56, temp, changestar_tex);
            }
            break;

        default:
            func_8007744C();
            lws_anim(&gfx, &mtx, RELOCATE_SEGMENTED(lws_data[fin_demo_569], story_buffer), fin_frame_568, story_buffer);
            break;
    }

    gDPSetScissor(gfx++, G_SC_NON_INTERLACE, 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1);

    *gfxP = gfx;
}

/**
 * Original name: story_st_new2
 */
void story_st_new2(Gfx **gfxP, TitleAllLwsIndex arg1, s32 arg2, TitleAllLwsIndex arg3, s32 arg4) {
    Mtx sp20;
    Gfx *gfx = *gfxP;

    gSPDisplayList(gfx++, normal_texture_init_dl);
    gSPDisplayList(gfx++, story_setup);

    makeTransrateMatrix(&sp20, 0U, 0xFFF38000U, 0xFC4A0000U);

    switch (story_seq_step) {
        case 0x0:
            func_800773F0();
            lws_anim(&gfx, &sp20, RELOCATE_SEGMENTED(lws_data[arg1], story_buffer), 0, story_buffer);
            framecont = 0;
            fin_frame_623 = 0;
            fin_demo_624 = arg1;
            break;

        case 0x1:
            fin_demo_624 = arg1;
            story_time_cnt = framecont;
            fin_frame_623 = framecont;
            st_mes_ptr = mes_data[arg2];
            if (gControllerPressedButtons[*main_joy] & (START_BUTTON | B_BUTTON)) {
                story_seq_step = 0x64;
                framecont = 0;
                story_time_cnt = 0;
                st_message_count = 0;
            }
            if (gControllerHoldButtons[*main_joy] & A_BUTTON) {
                story_time_cnt += 3;
                framecont += 3;
            }
            func_8007865C();
            if ((lws_anim(&gfx, &sp20, RELOCATE_SEGMENTED(lws_data[arg1], story_buffer), story_time_cnt,
                          story_buffer) == 1) &&
                (msgWnd_isEnd(&mess_st) != false)) {
                framecont = 0;
                story_time_cnt = 0;
                st_message_count = 0;
                story_seq_step++;
            }
            break;

        case 0x2:
            fin_demo_624 = arg3;
            story_time_cnt = framecont;
            fin_frame_623 = framecont;
            st_mes_ptr = mes_data[arg4];
            if (gControllerPressedButtons[*main_joy] & (START_BUTTON | B_BUTTON)) {
                story_seq_step = 3;
                story_time_cnt = 0;
            }
            if (gControllerHoldButtons[*main_joy] & A_BUTTON) {
                framecont += 3;
                story_time_cnt += 3;
            }

            func_8007865C();
            if ((lws_anim(&gfx, &sp20, RELOCATE_SEGMENTED(lws_data[arg3], story_buffer), story_time_cnt,
                          story_buffer) == 1) &&
                (msgWnd_isEnd(&mess_st) != false)) {
                story_time_cnt = 0;
                story_seq_step++;
            }
            break;

        default:
            func_8007744C();
            lws_anim(&gfx, &sp20, RELOCATE_SEGMENTED(lws_data[fin_demo_624], story_buffer), fin_frame_623,
                     story_buffer);
            break;
    }

    gDPSetScissor(gfx++, G_SC_NON_INTERLACE, 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1);

    *gfxP = gfx;
}

/**
 * Original name: story_m_end
 */
void story_m_end(Gfx **gfxP, TitleAllLwsIndex arg1, s32 arg2) {
    Mtx mtx;
    Gfx *gfx = *gfxP;
    s32 var_a3;
    s32 var_t0;
    s32 var_t1;
    s32 var_t2;

    gSPDisplayList(gfx++, normal_texture_init_dl);
    gSPDisplayList(gfx++, story_setup);

    makeTransrateMatrix(&mtx, 0U, 0xFFF38000U, 0xFC4A0000U);

    switch (story_seq_step) {
        case 0:
            func_800773F0();
            lws_anim(&gfx, &mtx, RELOCATE_SEGMENTED(lws_data[arg1], story_buffer), 0, story_buffer);
            framecont = 0;
            story_spot_cnt = 0x100;
            st_mes_ptr = mes_data[arg2];
            break;

        case 1:
            story_time_cnt = framecont;
            fin_frame_667 = framecont;

            func_8007865C();
            if (gControllerPressedButtons[*main_joy] & 0x5000) {
                framecont = 0;
                story_time_cnt = 0;
                st_message_count = 0;
                story_seq_step += 1;
            }

            if (lws_anim(&gfx, &mtx, RELOCATE_SEGMENTED(lws_data[arg1], story_buffer), story_time_cnt, story_buffer) ==
                1) {
                framecont = 0;
                story_time_cnt = 0;
                st_message_count = 0;
                story_seq_step += 1;
            }
            break;

        default:
            story_time_cnt = framecont;
            fin_frame_667 = framecont;
            st_mes_ptr = mes_data[0x16];

            var_a3 = 0xFF;
            var_t1 = 0xFF;
            var_t2 = 0xFF;
            if (story_time_cnt >= 0x15F) {
                var_t0 = story_time_cnt - 0x15E;
                if (story_time_cnt < 0x1F4) {
                    var_t2 = ((var_t0 * -0x69) / 149) + 0xFF;
                    var_t1 = (-(var_t0 * 0xA0) / 149) + 0xFF;
                    var_a3 = ((var_t0 * -0xAF) / 149) + 0xFF;
                } else {
                    var_t0 = (story_time_cnt - 0x1F4);
                    if (story_time_cnt < 0x2BC) {
                        var_t2 = ((var_t0 * -0x5F) / 199) + 0x96;
                        var_t1 = (-(var_t0 * 0x10) / 199) + 0x5F;
                        var_a3 = ((var_t0 * 0x1E) / 199) + 0x50;
                    } else if (story_time_cnt < 0x3E8) {
                        var_t2 = 0x37;
                        var_t1 = 0x4F;
                        var_a3 = 0x6E;
                    } else if (story_time_cnt < 0x4E2) {
                        var_t0 = story_time_cnt - 0x3E8;
                        var_t2 = ((var_t0 * 0xC8) / 249) + 0x37;
                        var_t1 = ((var_t0 * 0xB0) / 249) + 0x4F;
                        var_a3 = ((var_t0 * 0x91) / 249) + 0x6E;
                    }
                }
            }

            var_t0 = 0xFF;
            if ((story_time_cnt > 0x276) && (story_time_cnt < 0x3E8)) {
                if (story_time_cnt < 0x2BC) {
                    var_t0 = story_time_cnt - 0x276;
                    var_t0 = ((var_t0 * -0xFF) / 69) + 0xFF;
                } else if (story_time_cnt >= 0x3B7) {
                    var_t0 = story_time_cnt - 0x3B6;
                    var_t0 = (var_t0 * 0xFF) / 49;
                } else {
                    var_t0 = 0;
                }
            }

            gDPSetEnvColor(gfx++, var_t2, var_t1, var_a3, var_t0);

            if (story_staff_roll != 0) {
                if (st_message_count != 9999) {
                    func_8007865C();
                }
            }

            if (lws_anim(&gfx, &mtx, RELOCATE_SEGMENTED(lws_data[TITLEALL_LWS_INDEX_21], story_buffer), story_time_cnt,
                         story_buffer) == 1) {
                framecont = 0x117;
                story_time_cnt = 0x117;
            }

            if (story_time_cnt >= 0x1F) {
                if (story_staff_roll == 0) {
                    story_staff_roll = 1;
                }
            }
            break;
    }

    gDPSetScissor(gfx++, G_SC_NON_INTERLACE, 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1);

    if ((story_staff_roll == 2) && !msgWnd_isScroll(&mess_roll_st)) {
        story_staff_roll = -1;
    }

    if (story_staff_roll == 1) {
        msgWnd_addStr(&mess_roll_st, st_staffroll_txt);
        msgWnd_skip(&mess_roll_st);
        mess_roll_st.unk_1C = 0;
        story_staff_roll = 2;
        mess_roll_st.unk_5C = 1.0f / 60.0f;
    }

    *gfxP = gfx;
}

/**
 * Original name: story_st_new_w9
 */
void story_st_new_w9(Gfx **gfxP, TitleAllLwsIndex arg1, s32 arg2) {
    Gfx *gfx = *gfxP;
    Mtx mtx;
    s32 red;
    s32 green;
    s32 blue;
    s32 alpha;
    Lws *lws;

    st_mes_ptr = mes_data[arg2];

    gSPDisplayList(gfx++, normal_texture_init_dl);
    gSPDisplayList(gfx++, story_setup);

    makeTransrateMatrix(&mtx, 0, 0xFFF38000, 0xFC4A0000);

    lws = RELOCATE_SEGMENTED(lws_data[arg1], story_buffer);

    switch (story_seq_step) {
        case 0:
            func_800773F0();
            lws_anim(&gfx, &mtx, lws, 0, story_buffer);
            framecont = 0;
            break;

        case 1:
            story_time_cnt = framecont;
            fin_frame_737 = framecont;

            red = green = blue = 0;

            if ((story_time_cnt >= 0x2F7) && (story_time_cnt <= 0x333)) {
                alpha = story_time_cnt - 0x2F7;
                alpha = (alpha * 0xFF) / 60;

                green = alpha;
                red = alpha;
                blue = alpha;
            } else if (story_time_cnt > 0x333) {
                blue = 255;
                green = 255;
                red = 255;
            }
            alpha = 255;

            gDPSetEnvColor(gfx++, red, green, blue, alpha);

            if (gControllerPressedButtons[main_joy[0]] & (START_BUTTON | B_BUTTON)) {
                story_time_cnt = 0;
                story_seq_step += 1;
            }
            if (gControllerHoldButtons[main_joy[0]] & A_BUTTON) {
                story_time_cnt += 3;
                framecont += 3;
            }

            func_8007865C();
            if (lws_anim(&gfx, &mtx, lws, story_time_cnt, story_buffer) == 1) {
                story_time_cnt = 0;
                story_seq_step += 1;
            }
            break;

        default:
            func_8007744C();
            lws_anim(&gfx, &mtx, lws, fin_frame_737, story_buffer);
            break;
    }

    gDPSetScissor(gfx++, G_SC_NON_INTERLACE, 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1);

    *gfxP = gfx;
}

/**
 * Original name: story_w_end
 */
void story_w_end(Gfx **gfxP, TitleAllLwsIndex arg1) {
    Mtx mtx;
    Gfx *gfx = *gfxP;
    s32 blue;
    s32 green;
    s32 red;

    gSPDisplayList(gfx++, normal_texture_init_dl);

    gSPDisplayList(gfx++, story_setup);

    makeTransrateMatrix(&mtx, 0U, 0xFFF38000U, 0xFC4A0000U);

    switch (story_seq_step) {
        case 0:
            func_800773F0();
            lws_anim(&gfx, &mtx, RELOCATE_SEGMENTED(lws_data[arg1], story_buffer), 0, story_buffer);
            framecont = 0;
            story_spot_cnt = 0x100;
            st_mes_ptr = mes_data[0x17];
            break;

        case 1:
            story_time_cnt = (s32)framecont;
            fin_frame_768 = (s32)framecont;
            func_8007865C();
            if (gControllerPressedButtons[main_joy[0]] & (B_BUTTON | START_BUTTON)) {
                framecont = 0;
                story_time_cnt = 0;
                st_message_count = 0;
                story_seq_step += 1;
            }
            if (lws_anim(&gfx, &mtx, RELOCATE_SEGMENTED(lws_data[arg1], story_buffer), story_time_cnt, story_buffer) ==
                1) {
                framecont = 0;
                story_time_cnt = 0;
                st_message_count = 0;
                story_seq_step += 1;
            }
            break;

        default:
            story_time_cnt = (s32)framecont;
            fin_frame_768 = (s32)framecont;
            st_mes_ptr = mes_data[0x18];
            blue = 255;
            green = 255;
            red = 255;
            if ((s32)framecont >= 0x262) {
                s32 temp_t0_2;

                if ((s32)framecont < 0x31B) {
                    temp_t0_2 = framecont - 0x262;
                    red = ((temp_t0_2 * -0x69) / 184) + 0xFF;
                    green = (-(temp_t0_2 * 0xA0) / 184) + 0xFF;
                    blue = ((temp_t0_2 * -0xAF) / 184) + 0xFF;
                } else if ((s32)framecont < 0x3D4) {
                    temp_t0_2 = framecont - 0x31B;
                    red = ((temp_t0_2 * -0x5F) / 184) + 0x96;
                    green = (-(temp_t0_2 * 0x10) / 184) + 0x5F;
                    blue = ((temp_t0_2 * 0x1E) / 184) + 0x50;
                } else if ((s32)framecont < 0x5C8) {
                    red = 0x37;
                    green = 0x4F;
                    blue = 0x6E;
                } else if ((s32)framecont < 0x708) {
                    temp_t0_2 = framecont - 0x5C8;
                    red = ((temp_t0_2 * 0xC8) / 319) + 0x37;
                    green = ((temp_t0_2 * 0xB0) / 319) + 0x4F;
                    blue = ((temp_t0_2 * 0x91) / 319) + 0x6E;
                }
            }

            gDPSetEnvColor(gfx++, red, green, blue, 255);

            if (story_staff_roll != 0) {
                if (st_message_count != 0x270F) {
                    func_8007865C();
                }
            }
            if (lws_anim(&gfx, &mtx, RELOCATE_SEGMENTED(lws_data[TITLEALL_LWS_INDEX_24], story_buffer), story_time_cnt,
                         story_buffer) == 1) {
                framecont = 0x6D;
                story_time_cnt = 0x6D;
            }
            if (story_time_cnt >= 0x1F) {
                if (story_staff_roll == 0) {
                    story_staff_roll = 1;
                }
            }
            break;
    }

    gDPSetScissor(gfx++, G_SC_NON_INTERLACE, 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1);

    if ((story_staff_roll == 2) && !msgWnd_isScroll(&mess_roll_st)) {
        story_staff_roll = -1;
    }

    if (story_staff_roll == 1) {
        msgWnd_addStr(&mess_roll_st, st_staffroll_txt);
        msgWnd_skip(&mess_roll_st);
        mess_roll_st.unk_1C = 0;
        story_staff_roll = 2;
        mess_roll_st.unk_5C = 1.0f / 60.0f;
    }

    *gfxP = gfx;
}

void func_8007A9DC(void) {
    void *ptr = story_buffer;

    storyGraphic = ptr;

    ptr = ALIGN_PTR(
        DecompressRomToRam(storyRomData[STORYROMDATA_TITLE_ALL].start, ptr,
                           storyRomData[STORYROMDATA_TITLE_ALL].end - storyRomData[STORYROMDATA_TITLE_ALL].start));
    wakuGraphic = ptr;

    ptr = ALIGN_PTR(DecompressRomToRam(storyRomData[STORYROMDATA_WAKU].start, ptr,
                                       storyRomData[STORYROMDATA_WAKU].end - storyRomData[STORYROMDATA_WAKU].start));
    bgGraphic = ptr;

    ptr = ALIGN_PTR(
        DecompressRomToRam(storyRomData[STORYROMDATA_MENU_BG].start, ptr,
                           storyRomData[STORYROMDATA_MENU_BG].end - storyRomData[STORYROMDATA_MENU_BG].start));
    messageData = ptr;
}

#if VERSION_US || VERSION_GW
#define MESS_ROLL_ST_ARG2 0x77A
#elif VERSION_CN
#define MESS_ROLL_ST_ARG2 0x7A7
#endif

/**
 * Original name: main_story
 */
void main_story(NNSched *sc) {
    OSMesgQueue scMQ;
    OSMesg scMsgBuf[NN_SC_MAX_MESGS];
    NNScClient scClient;
    s32 i;
    s32 temp;

    osCreateMesgQueue(&scMQ, scMsgBuf, ARRAY_COUNT(scMsgBuf));
    nnScAddClient(sc, &scClient, &scMQ);

    graphic_no = GRAPHIC_NO_0;
    story_z_buffer = gfx_freebuf;
    guPerspective(&story_viewMtx, &story_norm, 45.0f, 4.0f / 3.0f, 1.0f, 1000.0f, 1.0f);
    guOrtho(&story_viewMtx, -SCREEN_WIDTH / 2, SCREEN_WIDTH / 2, -SCREEN_HEIGHT / 2, SCREEN_HEIGHT / 2, 1.0f, 2000.0f,
            1.0f);

    first_copy = 1;
    for (i = 0; i < ARRAY_COUNT(joyflg); i++) {
        joyflg[i] = U_JPAD | L_JPAD | R_JPAD | D_JPAD;
    }

    story_read_buf = gfx_freebuf;
    story_buffer = &story_read_buf[0x10000];
    framecont = 0;
    story_time_cnt = 0;
    story_seq_step = 0;
    story_kay_wait = 0;
    story_curtain = 0x1E;
    story_zoom = 0;
    story_message_on = 0;
    story_message_start = 0;
    story_doing = 1;
    story_staff_roll = 0;
    st_message_count = 0;
    loop_flg = true;

    mess_heap = &mess_heap_area;
    msgWnd_init(&mess_st, &mess_heap, 0x10, 3, 0x42, 0xB1);
    mess_st.unk_30 = 0xC;
    mess_st.unk_34 = 0xC;
    mess_st.unk_3C = 6;
    mess_st.unk_48 = 0xE;
    mess_st.unk_54 = 0.4f;

    mess_roll_heap = gfx_freebuf;
    msgWnd_init2(&mess_roll_st, &mess_roll_heap, MESS_ROLL_ST_ARG2, 0x14, 0xB, 0x28, 0x16);
    mess_roll_st.unk_24 = 1;
    mess_roll_st.unk_30 = 0xC;
    mess_roll_st.unk_34 = 0xC;
    mess_roll_st.unk_3C = 6;
    mess_roll_st.unk_48 = 0xE;
    mess_roll_st.unk_20 = 1;
    mess_roll_st.unk_54 = 0.25f;

    func_8007A9DC();
    joyProcCore();
    dm_seq_play(snd_tbl_838[story_proc_no]);

    for (; loop_flg != 0; dm_audio_update()) {
        osRecvMesg(&scMQ, NULL, OS_MESG_BLOCK);

#ifdef NN_SC_PERF
        if (D_80092F10_cn) {
            joyProcCore();
            graphic_no = GRAPHIC_NO_0;
            continue;
        }

        graphic_no = GRAPHIC_NO_1;
#endif
        msgWnd_update(&mess_st);
        msgWnd_update(&mess_roll_st);
        if ((story_doing == 0) && (story_zoom >= 0x5A)) {
            loop_flg = 0;
        }
        joyProcCore();
#ifndef NN_SC_PERF
        graphic_no = GRAPHIC_NO_1;
#endif
    }

    dm_audio_stop();
    graphic_no = GRAPHIC_NO_0;

    while ((pendingGFX != 0) || !dm_audio_is_stopped()) {
        osRecvMesg(&scMQ, NULL, OS_MESG_BLOCK);
        dm_audio_update();
    }

    for (i = 0; i < 3; i++) {
        osRecvMesg(&scMQ, NULL, OS_MESG_BLOCK);
    }

    nnScRemoveClient(sc, &scClient);
    evs_story_no = story_proc_no;
    if (evs_story_no >= 0xC) {
        evs_story_no -= 0xC;
    }
    temp = evs_story_no;
    evs_seqnumb = temp % 3;
}

/**
 * Original name: init_objMtx
 */
void init_objMtx(void) {
    pObjectMtx = story_objectMtx[objMtx_FF];
    objMtx_FF ^= 1;
}

/**
 * Original name: graphic_story
 */
void graphic_story(void) {
    s32 pad[6] UNUSED;
    OSScTask *task;

    gGfxHead = gGfxGlist[gfx_gtask_no];
    task = &B_800FAE80[gfx_gtask_no];

    init_objMtx();

    gSPSegment(gGfxHead++, 0x00, 0x00000000);
    gSPSegment(gGfxHead++, 0x05, osVirtualToPhysical(story_buffer));

    lws_data = story_buffer;
    S2RDPinitRtn(1);

    gDPPipeSync(gGfxHead++);
    gDPSetCycleType(gGfxHead++, G_CYC_FILL);
    gDPSetCycleType(gGfxHead++, G_CYC_1CYCLE);
    gDPSetEnvColor(gGfxHead++, 255, 255, 255, 255);

    S2ClearCFBRtn(1);

    gSPMatrix(gGfxHead++, OS_K0_TO_PHYSICAL(&story_viewMtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);

    if (story_zoom > 0) {
        story_zoomfade(&gGfxHead, story_zoom);
        story_zoom++;
    } else {
        switch (story_proc_no) {
            case BGROMDATA_INDEX0:
            case BGROMDATA_INDEX12:
                story_st_new(&gGfxHead, TITLEALL_LWS_INDEX_1, 0);
                break;

            case BGROMDATA_INDEX10:
                story_m_end(&gGfxHead, TITLEALL_LWS_INDEX_20, 0x1B);
                break;

            case BGROMDATA_INDEX11:
                story_m_end(&gGfxHead, TITLEALL_LWS_INDEX_22, 0x1C);
                break;

            case BGROMDATA_INDEX22:
                story_w_end(&gGfxHead, TITLEALL_LWS_INDEX_23);
                break;

            case BGROMDATA_INDEX23:
                story_w_end(&gGfxHead, TITLEALL_LWS_INDEX_25);
                break;

            case BGROMDATA_INDEX1:
                story_st_new_op(&gGfxHead, true);
                break;

            case BGROMDATA_INDEX2:
                story_st_new2(&gGfxHead, TITLEALL_LWS_INDEX_2, 5, TITLEALL_LWS_INDEX_3, 7);
                break;

            case BGROMDATA_INDEX3:
                gDPSetEnvColor(gGfxHead++, 170, 150, 185, 255);

                story_st_new(&gGfxHead, TITLEALL_LWS_INDEX_5, 9);
                break;

            case BGROMDATA_INDEX4:
                story_st_new2_f(&gGfxHead, TITLEALL_LWS_INDEX_34, 0x1D, TITLEALL_LWS_INDEX_7, 0xB);
                break;

            case BGROMDATA_INDEX5:
                story_st_new(&gGfxHead, TITLEALL_LWS_INDEX_9, 0xD);
                break;

            case BGROMDATA_INDEX6:
                story_st_new(&gGfxHead, TITLEALL_LWS_INDEX_12, 0xF);
                break;

            case BGROMDATA_INDEX7:
                if (evs_story_level == 0) {
                    story_st_new(&gGfxHead, TITLEALL_LWS_INDEX_30, 0x19);
                } else {
                    story_st_new(&gGfxHead, TITLEALL_LWS_INDEX_13, 0x11);
                }
                break;

            case BGROMDATA_INDEX8:
                if (evs_story_level == 0) {
                    story_st_new2_f(&gGfxHead, TITLEALL_LWS_INDEX_32, 0x1A, TITLEALL_LWS_INDEX_16, 0x13);
                } else {
                    story_st_new2_f(&gGfxHead, TITLEALL_LWS_INDEX_14, 0x12, TITLEALL_LWS_INDEX_16, 0x13);
                }
                break;

            case BGROMDATA_INDEX9:
                story_st_new(&gGfxHead, TITLEALL_LWS_INDEX_18, 0x14);
                break;

            case BGROMDATA_INDEX13:
                story_st_new_op(&gGfxHead, false);
                break;

            case BGROMDATA_INDEX14:
                story_st_new2(&gGfxHead, TITLEALL_LWS_INDEX_2, 6, TITLEALL_LWS_INDEX_4, 8);
                break;

            case BGROMDATA_INDEX15:
                gDPSetEnvColor(gGfxHead++, 170, 150, 185, 255);
                story_st_new(&gGfxHead, TITLEALL_LWS_INDEX_6, 0xA);
                break;

            case BGROMDATA_INDEX16:
                story_st_new2_f(&gGfxHead, TITLEALL_LWS_INDEX_34, 0x1D, TITLEALL_LWS_INDEX_8, 0xC);
                break;

            case BGROMDATA_INDEX17:
                story_st_new(&gGfxHead, TITLEALL_LWS_INDEX_10, 0xE);
                break;

            case BGROMDATA_INDEX18:
                story_st_new(&gGfxHead, TITLEALL_LWS_INDEX_11, 0x10);
                break;

            case BGROMDATA_INDEX19:
                if (evs_story_level == 0) {
                    story_st_new(&gGfxHead, TITLEALL_LWS_INDEX_31, 0x19);
                } else {
                    story_st_new(&gGfxHead, TITLEALL_LWS_INDEX_13, 0x11);
                }
                break;

            case BGROMDATA_INDEX20:
                if (evs_story_level == 0) {
                    story_st_new2_f(&gGfxHead, TITLEALL_LWS_INDEX_32, 0x1A, TITLEALL_LWS_INDEX_17, 0x13);
                } else {
                    story_st_new2_f(&gGfxHead, TITLEALL_LWS_INDEX_15, 0x12, TITLEALL_LWS_INDEX_17, 0x13);
                }
                break;

            case BGROMDATA_INDEX21:
                story_st_new_w9(&gGfxHead, TITLEALL_LWS_INDEX_19, 0x15);
                break;

            default:
                break;
        }

        curtain_proc_org(&gGfxHead, story_curtain);
        if (story_staff_roll == 2) {
            msgWnd_draw(&mess_roll_st, &gGfxHead);

            if (gControllerPressedButtons[main_joy[0]] & START_BUTTON) {
                story_staff_roll = -1;
            }

            if (gControllerHoldButtons[main_joy[0]] & (A_BUTTON | B_BUTTON)) {
                mess_roll_st.unk_5C = 1.0f / 6.0f;
            } else {
                mess_roll_st.unk_5C = 1.0f / 60.0f;
            }
        }

        func_800770E8(&gGfxHead, wakuGraphic);
        if (story_message_on != 0) {
            msgWnd_draw(&mess_st, &gGfxHead);
            gDPSetScissor(gGfxHead++, G_SC_NON_INTERLACE, 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1);
        }
    }

    if (story_staff_roll < 0) {
        gSPDisplayList(gGfxHead++, normal_texture_init_dl);
        story_spot(&gGfxHead, 0xA0, 0x78, story_spot_cnt, changestar_tex);
        story_spot_cnt -= 4;
        if (story_spot_cnt < -0x14) {
            loop_flg = false;
        }
    }

    story_time_cnt++;
    gDPFullSync(gGfxHead++);
    gSPEndDisplayList(gGfxHead++);

    osWritebackDCacheAll();
    gfxTaskStart(task, gGfxGlist[gfx_gtask_no], (gGfxHead - gGfxGlist[gfx_gtask_no]) * sizeof(Gfx), 0,
                 OS_SC_SWAPBUFFER);
}

void func_8007B62C(Gfx **gfxP) {
    draw_menu_bg(gfxP, 0xA0, 0x78);
}

/**
 * Original filename: game_etc.c
 */

#include "game_etc.h"

#include "attributes.h"
#include "libc/assert.h"
#include "gcc/stdlib.h"

#include "defines.h"
#include "macros_defines.h"

#include "calc.h"
#include "calcsub.h"
#include "dm_game_main.h"
#include "lws.h"
#include "main_story.h"
#include "tex_func.h"

#include "assets/game_etc/etc.h"

/**
 * Original name: attack_effect_idx
 */
s32 attack_effect_idx;

/**
 * Original name: attack_effect
 */
struct_attack_effect attack_effect[0x10];

/**
 * Original name: attack_sprite_idx
 */
s32 attack_sprite_idx;

/**
 * Original name: attack_sprite
 */
struct_attack_sprite attack_sprite[0x80];

/**
 * Original name: attack_sprite_address
 */
u8 (*attack_sprite_address)[10][32 * 32 / 2];

#define G_ETC_WORK_VAL 8

typedef struct struct_g_etc_work {
    /* 0x00 */ f32 x0;
    /* 0x04 */ f32 y0;
    /* 0x08 */ f32 xs;
    /* 0x0C */ f32 ys;
    /* 0x10 */ s32 timer[G_ETC_WORK_VAL];
    /* 0x30 */ f32 px[G_ETC_WORK_VAL];
    /* 0x50 */ f32 py[G_ETC_WORK_VAL];
    /* 0x70 */ s32 r[G_ETC_WORK_VAL];
    /* 0x70 */ s32 g[G_ETC_WORK_VAL];
    /* 0x70 */ s32 b[G_ETC_WORK_VAL];
    /* 0x70 */ s32 a[G_ETC_WORK_VAL];
} struct_g_etc_work; // size = 0xF0

/**
 * Original name: binCount
 */
static s32 binCount;

/**
 * Original name: cont_bg_flg
 */
static bool cont_bg_flg;

/**
 * Original name: etcTexAddress
 */
static void *etcTexAddress;

/**
 * Original name: etcLwsAddress
 */
static void **etcLwsAddress;

/**
 * Original name: etcLwsTbl
 */
static void *etcLwsTbl[14];

/**
 * Original name: D_800E5408
 */
static u8 D_800E5408[0x8] UNUSED;

/**
 * Original name: logo_ofsY
 */
static s32 logo_ofsY;

/**
 * Original name: etc_mode
 */
static s32 etc_mode;

/**
 * Original name: g_etc_work
 */
static struct_g_etc_work g_etc_work[MAX_PLAYERS];

/**
 * Original name: D_800E57D8
 */
static u8 D_800E57D8[0x40] UNUSED;

/**
 * Original name: etc_viewMtx
 */
static Mtx etc_viewMtx;

/**
 * Original name: pause_table
 */
EtcPartIndex pause_table[][6] = {
    {
        ETC_PART_INDEX_GRAPHBIN_2,
        ETC_PART_INDEX_GRAPHBIN_8,
        ETC_PART_INDEX_GRAPHBIN_1,
        ETC_PART_INDEX_GRAPHBIN_0,
        ETC_PART_INDEX_GRAPHBIN_2,
        ETC_PART_INDEX_GRAPHBIN_2,
    },
    {
        ETC_PART_INDEX_GRAPHBIN_3,
        ETC_PART_INDEX_GRAPHBIN_7,
        ETC_PART_INDEX_GRAPHBIN_2,
        ETC_PART_INDEX_GRAPHBIN_0,
        ETC_PART_INDEX_GRAPHBIN_1,
        ETC_PART_INDEX_GRAPHBIN_2,
    },
};

/**
 * Original name: cont_table
 */
EtcPartIndex cont_table[][6] = {
    {
        ETC_PART_INDEX_GRAPHBIN_2,
        ETC_PART_INDEX_GRAPHBIN_0,
        ETC_PART_INDEX_GRAPHBIN_1,
        ETC_PART_INDEX_GRAPHBIN_0,
        ETC_PART_INDEX_GRAPHBIN_3,
        ETC_PART_INDEX_GRAPHBIN_3,
    },
    {
        ETC_PART_INDEX_GRAPHBIN_3,
        ETC_PART_INDEX_GRAPHBIN_6,
        ETC_PART_INDEX_GRAPHBIN_2,
        ETC_PART_INDEX_GRAPHBIN_0,
        ETC_PART_INDEX_GRAPHBIN_2,
        ETC_PART_INDEX_GRAPHBIN_3,
    },
    {
        ETC_PART_INDEX_GRAPHBIN_2,
        ETC_PART_INDEX_GRAPHBIN_4,
        ETC_PART_INDEX_GRAPHBIN_1,
        ETC_PART_INDEX_GRAPHBIN_0,
        ETC_PART_INDEX_GRAPHBIN_1,
        ETC_PART_INDEX_GRAPHBIN_1,
    },
    {
        ETC_PART_INDEX_GRAPHBIN_3,
        ETC_PART_INDEX_GRAPHBIN_9,
        ETC_PART_INDEX_GRAPHBIN_2,
        ETC_PART_INDEX_GRAPHBIN_0,
        ETC_PART_INDEX_GRAPHBIN_1,
        ETC_PART_INDEX_GRAPHBIN_3,
    },
};

/**
 * Original name: etc_parts_tbl
 */
void *etc_parts_tbl[] = {
    &etc_00,             // ETC_PART_INDEX_GRAPHBIN_0
    &etc_01,             // ETC_PART_INDEX_GRAPHBIN_1
    &etc_02,             // ETC_PART_INDEX_GRAPHBIN_2
    &etc_03,             // ETC_PART_INDEX_GRAPHBIN_3
    &etc_04,             // ETC_PART_INDEX_GRAPHBIN_4
    &etc_05,             // ETC_PART_INDEX_GRAPHBIN_5
    &etc_06,             // ETC_PART_INDEX_GRAPHBIN_6
    &etc_07,             // ETC_PART_INDEX_GRAPHBIN_7
    &etc_08,             // ETC_PART_INDEX_GRAPHBIN_8
    &etc_09,             // ETC_PART_INDEX_GRAPHBIN_9
    &etc_10,             // ETC_PART_INDEX_GRAPHBIN_10
    &etc_11,             // ETC_PART_INDEX_GRAPHBIN_11
    &etc_12,             // ETC_PART_INDEX_GRAPHBIN_12
    &etc_00,             // ETC_PART_INDEX_GRAPHBIN_13
    &game_etc_lws,       // ETC_PART_INDEX_LWS
    &etc_attack_sprites, // ETC_PART_INDEX_ATTACK_SPRITE
};
static_assert(ARRAY_COUNT(etc_parts_tbl) == ETC_PART_INDEX_MAX, "");

/**
 * Original name: x2p
 */
s32 x2p[2] = { -0x5C, 0x5C };

/**
 * Original name: x4p
 */
s32 x4p[4] = { -0x6C, -0x24, 0x24, 0x6C };

/**
 * Original name: etc_vp
 */
Vp etc_vp = { {
    { SCREEN_WIDTH / 2 * 4, SCREEN_HEIGHT / 2 * 4, 0x1FF, 0 },
    { SCREEN_WIDTH / 2 * 4, SCREEN_HEIGHT / 2 * 4, 0x1FF, 0 },
} };

/**
 * Original name: etc_setup
 */
Gfx etc_setup[] = {
    gsDPPipeSync(),
    gsSPViewport(&etc_vp),
    gsDPSetBlendColor(0, 0, 0, 4),
    gsDPSetScissor(G_SC_NON_INTERLACE, 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1),
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

/**
 * Original name: col_prim_434
 */
Color_RGB32 col_prim_434[] = {
    { 255, 0, 48 },
    { 64, 64, 255 },
    { 255, 200, 0 },
    { 0, 255, 0 },
};

/**
 * Original name: col_env_435
 */
Color_RGB32 col_env_435[] = {
    { 255, 192, 210 },
    { 220, 220, 255 },
    { 255, 255, 220 },
    { 210, 255, 210 },
};

/**
 * Original name: initEtcWork
 */
void initEtcWork(void *gameEtcSeg, s32 count) {
    s32 i;

    if (evs_gamemode == GMD_TIME_ATTACK) {
        logo_ofsY = 0x10;
    } else {
        logo_ofsY = 0;
    }

    binCount = count;
    etcTexAddress = gameEtcSeg;
    etcLwsAddress = RELOCATE_OFFSET(gameEtcSeg, etc_parts_tbl[ETC_PART_INDEX_LWS]);
    attack_sprite_address = RELOCATE_OFFSET(gameEtcSeg, etc_parts_tbl[ETC_PART_INDEX_ATTACK_SPRITE]);

    for (i = 0; i < ARRAY_COUNT(etcLwsTbl); i++) {
        void *temp = etcLwsAddress[i];

        temp = RELOCATE_OFFSET(RELOCATE_SEGMENTED(temp, gameEtcSeg), etc_parts_tbl[ETC_PART_INDEX_LWS]);
        etcLwsTbl[i] = temp;
    }

    switch (binCount) {
        case 1:
        case 2:
            etc_mode = 0;
            break;

        case 4:
            etc_mode = 1;
            break;
    }

    guOrtho(&etc_viewMtx, -SCREEN_WIDTH / 2, SCREEN_WIDTH / 2, -SCREEN_HEIGHT / 2, SCREEN_HEIGHT / 2, 1.0f, 2000.0f,
            1.0f);

    for (i = 0; i < binCount; i++) {
        s32 j;

        g_etc_work[i].x0 = game_state_data[i].unk_006;
        g_etc_work[i].y0 = game_state_data[i].unk_008;
        g_etc_work[i].xs = game_state_data[i].unk_00A * 8.0f;
        g_etc_work[i].ys = game_state_data[i].unk_00A * 17.0f;

        for (j = 0; j < G_ETC_WORK_VAL; j++) {
            g_etc_work[i].timer[j] = 0;

            g_etc_work[i].px[j] = g_etc_work[i].py[j] = 0.0f;

            g_etc_work[i].r[j] = g_etc_work[i].g[j] = g_etc_work[i].b[j] = g_etc_work[i].a[j] = 0xFF;
        }
    }

    attack_effect_idx = 0;
    for (i = 0; i < ARRAY_COUNT(attack_effect); i++) {
        attack_effect[i].time = 0;
    }

    attack_sprite_idx = 0;
    for (i = 0; i < ARRAY_COUNT(attack_sprite); i++) {
        attack_sprite[i].time = 0;
    }
}

/**
 * Original name: init_pause_disp
 */
void init_pause_disp(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(g_etc_work); i++) {
        s32 j;

        for (j = 0; j < G_ETC_WORK_VAL; j++) {
            g_etc_work[i].timer[j] = 0;
            g_etc_work[i].px[j] = g_etc_work[i].py[j] = 0.0f;
            g_etc_work[i].r[j] = g_etc_work[i].g[j] = g_etc_work[i].b[j] = g_etc_work[i].a[j] = 0xFF;
        }
    }
}

/**
 * Original name: disp_logo_setup
 */
void disp_logo_setup(Gfx **gfxP) {
    Gfx *gfx = *gfxP;

    init_objMtx();
    gSPMatrix(gfx++, OS_K0_TO_PHYSICAL(&etc_viewMtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gSPSegment(gfx++, 0x05, osVirtualToPhysical(etcLwsAddress));
    *gfxP = gfx;
}

/**
 * Original name: disp_count_logo
 */
s32 disp_count_logo(Gfx **gfxP, s32 player, s32 count) {
    Mtx mtx;
    Gfx *gfx = *gfxP;
    s32 x;
    s32 y;
    s32 ret;

    gSPDisplayList(gfx++, etc_setup);

    switch (binCount) {
        case 1:
            x = 0;
            y = 0;
            break;

        case 2:
            x = x2p[player];
            y = 0;
            break;

        default:
            x = x4p[player];
            y = 0;
            break;
    }

    MAKE_TRANSRATE_MATRIX(&mtx, x, y, -1000);
    ret = lws_anim(&gfx, &mtx, etcLwsTbl[ETC_LWS_INDEX_9], count, etcLwsAddress);

    *gfxP = gfx;
    return ret;
}

/**
 * Original name: disp_clear_logo
 */
void disp_clear_logo(Gfx **gfxP, s32 player, bool flg) {
    Gfx *gfx = *gfxP;
    Mtx mtx;
    s32 x;
    s32 y;
    struct_g_etc_work *pge;

    gSPDisplayList(gfx++, etc_setup);

    pge = &g_etc_work[player];

    switch (binCount) {
        case 1:
            x = -4;
            y = 0;
            break;

        case 2:
            x = x2p[player] - 4;
            y = 0;
            break;

        default:
            x = x4p[player] - 4;
            y = 0;
            break;
    }

    MAKE_TRANSRATE_MATRIX(&mtx, x, y, -1000);

    if (lws_anim(&gfx, &mtx, etcLwsTbl[ETC_LWS_INDEX_10], pge->timer[0], etcLwsAddress) == 1) {
        pge->timer[0] = 39;
    }
    pge->timer[0]++;

    if (flg) {
        if (lws_anim(&gfx, &mtx, etcLwsTbl[ETC_LWS_INDEX_11], pge->timer[1], etcLwsAddress) == 1) {
            pge->timer[1] = 59;
        }
        pge->timer[1]++;
    }

    *gfxP = gfx;
}

/**
 * Original name: disp_clear_logo
 */
void disp_allclear_logo(Gfx **gfxP, s32 player, bool flg) {
    Gfx *gfx = *gfxP;
    Mtx mtx;
    s32 x;
    s32 y;
    struct_g_etc_work *pge;

    gSPDisplayList(gfx++, etc_setup);

    pge = &g_etc_work[player];

    switch (binCount) {
        case 0x1:
            x = -4;
            y = 0;
            break;

        case 0x2:
            x = x2p[player] - 4;
            y = 0;
            break;

        default:
            x = x4p[player] - 4;
            y = 0;
            break;
    }

    MAKE_TRANSRATE_MATRIX(&mtx, x, y, -1000);

    if (lws_anim(&gfx, &mtx, etcLwsTbl[ETC_LWS_INDEX_13], pge->timer[1], etcLwsAddress) == 1) {
        pge->timer[1] = 0x27;
    }
    pge->timer[1]++;

    if (flg) {
        if (lws_anim(&gfx, &mtx, etcLwsTbl[ETC_LWS_INDEX_11], pge->timer[2], etcLwsAddress) == 1) {
            pge->timer[2] = 0x3B;
        }
        pge->timer[2]++;
    }

    *gfxP = gfx;
}

/**
 * Original name: disp_win_logo
 */
void disp_win_logo(Gfx **gfxP, s32 player) {
    Gfx *gfx = *gfxP;
    Mtx mtx;
    s32 x;
    s32 y;
    struct_g_etc_work *pge;

    gSPDisplayList(gfx++, etc_setup);

    pge = &g_etc_work[player];

    switch (binCount) {
        case 1:
            x = 0;
            y = 0;
            break;

        case 2:
            x = x2p[player];
            y = 0;
            break;

        default:
            x = x4p[player];
            y = 2;
            break;
    }

    MAKE_TRANSRATE_MATRIX(&mtx, x, y + logo_ofsY, -1000);

    if (binCount != 4) {
        if (lws_anim(&gfx, &mtx, etcLwsTbl[ETC_LWS_INDEX_0], pge->timer[0], etcLwsAddress) == 1) {
            pge->timer[0] = 0x3F;
        }
    } else {
        if (lws_anim(&gfx, &mtx, etcLwsTbl[ETC_LWS_INDEX_1], pge->timer[0], etcLwsAddress) == 1) {
            pge->timer[0] = 0x3F;
        }
    }
    pge->timer[0]++;

    *gfxP = gfx;
}

/**
 * Original name: disp_lose_logo
 */
void disp_lose_logo(Gfx **gfxP, s32 player) {
    Gfx *gfx = *gfxP;
    Mtx mtx;
    s32 x;
    s32 y;
    struct_g_etc_work *pge;

    gSPDisplayList(gfx++, etc_setup);

    pge = &g_etc_work[player];

    switch (binCount) {
        case 1:
            x = 0;
            y = 0;
            break;

        case 2:
            x = x2p[player];
            y = 0;
            break;

        default:
            x = x4p[player];
            y = 2;
            break;
    }

    MAKE_TRANSRATE_MATRIX(&mtx, x, y + logo_ofsY, -1000);

    if (binCount != 4) {
        if (lws_anim(&gfx, &mtx, etcLwsTbl[ETC_LWS_INDEX_2], pge->timer[0], etcLwsAddress) == 1) {
            pge->timer[0] = 0x37;
        }
    } else {
        if (lws_anim(&gfx, &mtx, etcLwsTbl[ETC_LWS_INDEX_3], pge->timer[0], etcLwsAddress) == 1) {
            pge->timer[0] = 0x37;
        }
    }
    pge->timer[0]++;

    *gfxP = gfx;
}

/**
 * Original name: disp_draw_logo
 */
void disp_draw_logo(Gfx **gfxP, s32 player) {
    Gfx *gfx = *gfxP;
    Mtx mtx;
    s32 x;
    s32 y;
    struct_g_etc_work *pge;

    gSPDisplayList(gfx++, etc_setup);

    pge = &g_etc_work[player];

    switch (binCount) {
        case 1:
            x = 0;
            y = 0;
            break;

        case 2:
            x = x2p[player];
            y = 0;
            break;

        default:
            x = x4p[player];
            y = 2;
            break;
    }

    MAKE_TRANSRATE_MATRIX(&mtx, x, y + logo_ofsY, -1000);

    if (binCount != 4) {
        if (lws_anim(&gfx, &mtx, etcLwsTbl[ETC_LWS_INDEX_4], pge->timer[0], etcLwsAddress) == 1) {
            pge->timer[0] = 15;
        }
    } else {
        if (lws_anim(&gfx, &mtx, etcLwsTbl[ETC_LWS_INDEX_5], pge->timer[0], etcLwsAddress) == 1) {
            pge->timer[0] = 15;
        }
    }
    pge->timer[0]++;

    *gfxP = gfx;
}

/**
 * Original name: disp_pause_logo
 */
EtcPartIndex disp_pause_logo(Gfx **gfxP, s32 player, s32 arg2 UNUSED, s32 cursor, s32 type) {
    Gfx *gfx = *gfxP;
    struct_g_etc_work *pge = &g_etc_work[player];
    GbiStat gbi;
    GbiStat gbia;
    Mtx mtx;
    s32 x;
    s32 y;
    s32 a;
    s32 pad[5] UNUSED;

    pge->px[7] = pge->x0 + (pge->xs / DOUBLE_LITERAL(2)) - DOUBLE_LITERAL(20);
    pge->py[7] = pge->y0 + 10.0f;

    pge->px[2] = pge->x0 + (pge->xs / DOUBLE_LITERAL(2)) - DOUBLE_LITERAL(31);

    if (pause_table[type][0] == ETC_PART_INDEX_GRAPHBIN_2) {
        pge->py[2] = (pge->y0 + pge->ys - 35) - 2;
    } else {
        pge->py[2] = (pge->y0 + pge->ys - 50) - 2;
    }

    gSPDisplayList(gfx++, etc_setup);

    switch (binCount) {
        case 1:
            x = 0;
            y = 0;
            break;

        case 2:
            x = x2p[player];
            y = 0;
            break;

        default:
            x = x4p[player];
            y = 8;
            break;
    }

    MAKE_TRANSRATE_MATRIX(&mtx, x, y, -1000);
    if (binCount != 4) {
        if (lws_anim(&gfx, &mtx, etcLwsTbl[ETC_LWS_INDEX_7], pge->timer[7], etcLwsAddress) == 1) {
            pge->timer[7] = 25;
        }
    } else {
        if (lws_anim(&gfx, &mtx, etcLwsTbl[ETC_LWS_INDEX_7], pge->timer[7], etcLwsAddress) == 1) {
            pge->timer[7] = 25;
        }
    }

    gSPDisplayList(gfx++, alpha_texture_init_dl);

    a = pge->timer[6] - 16;
    if ((cursor >= 0) && (a > 0)) {
        f32 fx;
        f32 fy;

        get_gbi_stat(&gbi, RELOCATE_OFFSET(etcTexAddress, etc_parts_tbl[pause_table[type][1]]));
        get_gbi_stat(&gbia, RELOCATE_OFFSET(etcTexAddress, etc_parts_tbl[pause_table[type][2]]));
        StretchAlphaTexBlock(&gfx, gbi.width, gbi.height, gbi.texture, gbi.width, gbia.texture, gbia.width, pge->px[2],
                             pge->py[2], gbi.width, gbi.height);

        if (pause_table[type][0] == ETC_PART_INDEX_GRAPHBIN_2) {
            switch (cursor) {
                case 0x0:
                    fx = pge->px[2];
                    fy = pge->py[2] + 0.0f + 1.0f;
                    break;

                case 0x1:
                    fx = pge->px[2];
                    fy = pge->py[2] + 16.0f - 2.0f;
                    break;
            }
        } else {
            switch (cursor) {
                case 0x0:
                    fx = pge->px[2];
                    fy = pge->py[2] + 0.0f - 1.0f;
                    break;

                case 0x1:
                    fx = pge->px[2];
                    fy = pge->py[2] + 16.0f - 1.0f;
                    break;

                case 0x2:
                    fx = pge->px[2];
                    fy = pge->py[2] + 31.0f - 1.0f;
                    break;
            }
        }

        if (pge->timer[5] & 0x10) {
            gSPDisplayList(gfx++, normal_texture_init_dl);
            get_gbi_stat(&gbi, RELOCATE_OFFSET(etcTexAddress, etc_parts_tbl[ETC_PART_INDEX_GRAPHBIN_3]));
            StretchTexBlock4(&gfx, gbi.width, gbi.height, gbi.tlut, gbi.texture, fx, fy, gbi.width, gbi.height);
        }
    }

    pge->timer[5]++;
    pge->timer[6]++;
    pge->timer[7]++;

    gSPDisplayList(gfx++, normal_texture_init_dl);

    *gfxP = gfx;

    return pause_table[type][cursor + 3];
}

/**
 * Original name: etc_continue_logo
 */
EtcPartIndex etc_continue_logo(Gfx **gfxP, s32 player, s32 cursor, s32 type) {
    Gfx *gfx = *gfxP;
    struct_g_etc_work *pge = &g_etc_work[player];
    GbiStat gbi;
    GbiStat gbia;
    f32 fx;
    f32 fy;

    if (cursor >= 0) {
        if (cont_bg_flg) {
            if (binCount == 2) {
                gSPDisplayList(gfx++, normal_texture_init_dl);
                gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
                gDPSetCombineLERP(gfx++, 0, 0, 0, PRIMITIVE, PRIMITIVE, 0, TEXEL0, 0, 0, 0, 0, PRIMITIVE, PRIMITIVE, 0,
                                  TEXEL0, 0);
                gDPSetTextureLUT(gfx++, G_TT_NONE);
                gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, 160);

                get_gbi_stat(&gbia, RELOCATE_OFFSET(etcTexAddress, etc_parts_tbl[cont_table[type][2]]));
                StretchTexBlock4i(&gfx, gbia.width, gbia.height, gbia.texture, pge->px[6] + 6.0f, pge->py[6] + 6.0f,
                                  gbia.width, gbia.height);
            }
        }

        gSPDisplayList(gfx++, alpha_texture_init_dl);

        get_gbi_stat(&gbi, RELOCATE_OFFSET(etcTexAddress, etc_parts_tbl[cont_table[type][1]]));
        get_gbi_stat(&gbia, RELOCATE_OFFSET(etcTexAddress, etc_parts_tbl[cont_table[type][2]]));
        StretchAlphaTexBlock(&gfx, gbi.width, gbi.height, gbi.texture, gbi.width, gbia.texture, gbia.width, pge->px[6],
                             pge->py[6], gbi.width, gbi.height);

        if (cont_table[type][0] == ETC_PART_INDEX_GRAPHBIN_2) {
            switch (cursor) {
                case 0x0:
                    fx = pge->px[6];
                    fy = pge->py[6] + 0.0f + 1.0f;
                    break;
                case 0x1:
                    fx = pge->px[6];
                    fy = pge->py[6] + 16.0f - 2.0f;
                    break;
            }
        } else {
            switch (cursor) {
                case 0x0:
                    fx = pge->px[6];
                    fy = pge->py[6] + 0.0f - 1.0f;
                    break;
                case 0x1:
                    fx = pge->px[6];
                    fy = pge->py[6] + 16.0f - 1.0f;
                    break;
                case 0x2:
                    fx = pge->px[6];
                    fy = pge->py[6] + 31.0f - 1.0f;
                    break;
            }
        }

        if (pge->timer[6] & 0x10) {
            gSPDisplayList(gfx++, normal_texture_init_dl);

            get_gbi_stat(&gbi, RELOCATE_OFFSET(etcTexAddress, etc_parts_tbl[ETC_PART_INDEX_GRAPHBIN_3]));
            StretchTexBlock4(&gfx, gbi.width, gbi.height, gbi.tlut, gbi.texture, fx, fy, gbi.width, gbi.height);
        }
    }

    pge->timer[6]++;

    gSPDisplayList(gfx++, normal_texture_init_dl);

    *gfxP = gfx;

    return cont_table[type][cursor + 3];
}

/**
 * Original name: disp_continue_logo
 */
EtcPartIndex disp_continue_logo(Gfx **gfxP, s32 player, s32 cursor, s32 type) {
    struct_g_etc_work *pge = &g_etc_work[player];

    cont_bg_flg = false;

    pge->px[6] = pge->x0 + pge->xs / DOUBLE_LITERAL(2) - DOUBLE_LITERAL(31);

    if (cont_table[type][0] == ETC_PART_INDEX_GRAPHBIN_2) {
        pge->py[6] = pge->y0 + pge->ys - 35.0f - 2.0f;
    } else {
        pge->py[6] = pge->y0 + pge->ys - 50.0f - 2.0f;
    }

    return etc_continue_logo(gfxP, player, cursor, type);
}

/**
 * Original name: disp_continue_logo_score
 */
EtcPartIndex disp_continue_logo_score(Gfx **gfxP, s32 player, s32 cursor, s32 type) {
    struct_g_etc_work *pge = &g_etc_work[player];

    cont_bg_flg = true;
    pge->px[6] = 129.0f;

    if (cont_table[type][0] == ETC_PART_INDEX_GRAPHBIN_2) {
        pge->py[6] = pge->y0 + pge->ys - 35.0f - 2.0f;
    } else {
        pge->py[6] = pge->y0 + pge->ys - 50.0f - 2.0f;
    }

    return etc_continue_logo(gfxP, player, cursor, type);
}

/**
 * Original name: disp_gameover_logo
 */
void disp_gameover_logo(Gfx **gfxP, s32 player) {
    Gfx *gfx = *gfxP;
    Mtx mtx;
    s32 x;
    s32 y;
    struct_g_etc_work *pge;

    gSPDisplayList(gfx++, etc_setup);

    pge = &g_etc_work[player];

    switch (binCount) {
        case 1:
            x = -2;
            y = 0;
            break;

        case 2:
            x = x2p[player] - 2;
            y = 0;
            break;

        default:
            x = x4p[player] - 2;
            y = 0;
            break;
    }

    MAKE_TRANSRATE_MATRIX(&mtx, x, y, -1000);

    if (lws_anim(&gfx, &mtx, etcLwsTbl[ETC_LWS_INDEX_8], pge->timer[1], etcLwsAddress) == 1) {
        pge->timer[1] = 57;
    }
    pge->timer[1]++;

    *gfxP = gfx;
}

/**
 * Original name: disp_timeover_logo
 */
void disp_timeover_logo(Gfx **gfxP, s32 player) {
    Gfx *gfx = *gfxP;
    Mtx mtx;
    s32 x;
    s32 y;
    struct_g_etc_work *pge;

    gSPDisplayList(gfx++, etc_setup);

    pge = &g_etc_work[player];

    switch (binCount) {
        case 1:
            x = -2;
            y = 0;
            break;

        case 2:
            x = x2p[player] - 2;
            y = 0;
            break;

        default:
            x = x4p[player] - 2;
            y = 0;
            break;
    }

    MAKE_TRANSRATE_MATRIX(&mtx, x, y, -1000);

    if (lws_anim(&gfx, &mtx, etcLwsTbl[ETC_LWS_INDEX_12], pge->timer[0], etcLwsAddress) == 1) {
        pge->timer[0] = 57;
    }
    pge->timer[0]++;

    *gfxP = gfx;
}

/**
 * Original name: disp_retire_logo
 */
void disp_retire_logo(Gfx **gfxP, s32 player) {
    Gfx *gfx = *gfxP;
    Mtx mtx;
    s32 x;
    s32 y;
    struct_g_etc_work *pge;

    gSPDisplayList(gfx++, etc_setup);

    pge = &g_etc_work[player];

    switch (binCount) {
        case 1:
            x = -2;
            y = 0;
            break;

        case 2:
            x = x2p[player];
            y = 0;
            break;

        default:
            x = x4p[player];
            y = 0;
            break;
    }

    MAKE_TRANSRATE_MATRIX(&mtx, x, y, -1000);

    if (lws_anim(&gfx, &mtx, etcLwsTbl[ETC_LWS_INDEX_6], pge->timer[2], etcLwsAddress) == 1) {
        pge->timer[2] = 139;
    }
    pge->timer[2]++;

    *gfxP = gfx;
}

/**
 * Original name: disp_timestop_logo
 */
void disp_timestop_logo(Gfx **gfxP, s32 player) {
    Gfx *gfx = *gfxP;
    struct_g_etc_work *pge = &g_etc_work[player];
    GbiStat gbi;

    get_gbi_stat(&gbi, RELOCATE_OFFSET(etcTexAddress, etc_parts_tbl[ETC_PART_INDEX_GRAPHBIN_11]));

    gSPDisplayList(gfx++, normal_texture_init_dl);
    gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gDPSetCombineLERP(gfx++, 0, 0, 0, 0, 0, 0, 0, TEXEL0, 0, 0, 0, 0, 0, 0, 0, TEXEL0);
    gDPSetTextureLUT(gfx++, G_TT_NONE);

    StretchTexBlock4i(&gfx, gbi.width, gbi.height, gbi.texture, 43.0f, 157.0f, gbi.width, gbi.height);
    get_gbi_stat(&gbi, RELOCATE_OFFSET(etcTexAddress, etc_parts_tbl[ETC_PART_INDEX_GRAPHBIN_10]));

    gSPDisplayList(gfx++, normal_texture_init_dl);

    StretchTexBlock4(&gfx, gbi.width, gbi.height, gbi.tlut, gbi.texture, 43.0f, 157.0f, gbi.width, gbi.height);
    if (pge->timer[4] & 0x10) {
        get_gbi_stat(&gbi, RELOCATE_OFFSET(etcTexAddress, etc_parts_tbl[ETC_PART_INDEX_GRAPHBIN_12]));
        StretchTexBlock4(&gfx, gbi.width, gbi.height, gbi.tlut, gbi.texture, 37.0f, 175.0f, gbi.width, gbi.height);
    }
    pge->timer[4]++;

    *gfxP = gfx;
}

/**
 * Original name: add_attack_effect
 */
void add_attack_effect(s32 player, s32 sx, s32 sy, s32 ex, s32 ey) {
    attack_effect[attack_effect_idx].player = player;
    attack_effect[attack_effect_idx].time = 48;
    attack_effect[attack_effect_idx].cnt = 0;
    attack_effect[attack_effect_idx].x = sx;
    attack_effect[attack_effect_idx].y = sy;
    attack_effect[attack_effect_idx].sx = sx;
    attack_effect[attack_effect_idx].sy = sy;
    attack_effect[attack_effect_idx].ex = ex;
    attack_effect[attack_effect_idx].ey = ey;
    attack_effect[attack_effect_idx].vx = sx;
    attack_effect[attack_effect_idx].vy = sy;

    attack_effect_idx++;
    if (attack_effect_idx >= ARRAY_COUNT(attack_effect)) {
        attack_effect_idx = 0;
    }
}

/**
 * Original name: disp_attack_effect
 */
void disp_attack_effect(Gfx **gfxP) {
    Gfx *gfx = *gfxP;
    f32 x;
    f32 y;
    f32 t;
    f32 scl;
    s32 tmp;
    s32 i;
    s32 alpha;
    u8 *texture;

    gSPDisplayList(gfx++, normal_texture_init_dl);
    gDPSetTextureLUT(gfx++, G_TT_NONE);
    gDPSetAlphaCompare(gfx++, G_AC_NONE);
    gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gDPSetCombineLERP(gfx++, ENVIRONMENT, PRIMITIVE, TEXEL0, PRIMITIVE, ENVIRONMENT, 0, TEXEL0, 0, ENVIRONMENT,
                      PRIMITIVE, TEXEL0, PRIMITIVE, ENVIRONMENT, 0, TEXEL0, 0);

    switch (binCount) {
        case 1:
        case 2:
            scl = 50.0f;
            break;

        case 4:
        default:
            scl = 30.0f;
            break;
    }

    tmp = -1;
    for (i = 0; i < ARRAY_COUNT(attack_effect); i++) {
        if (attack_effect[i].time <= 0) {
            continue;
        }

        attack_effect[i].time--;

        t = attack_effect[i].time / 48.0f;

        x = attack_effect[i].ex - t * (attack_effect[i].ex - attack_effect[i].sx);

        y = attack_effect[i].ey - t * (attack_effect[i].ey - attack_effect[i].sy);
        y -= scl * sinf(DEG_TO_RAD(t * DOUBLE_LITERAL(180)));

        attack_effect[i].x = x + DOUBLE_LITERAL(0.5);
        attack_effect[i].y = y + DOUBLE_LITERAL(0.5);

        alpha = 240;
        if (attack_effect[i].time > 40) {
            alpha = 48 - attack_effect[i].time;
            alpha = alpha * 30;
        }
        if (attack_effect[i].time < 8) {
            alpha = attack_effect[i].time * 30;
        }

        if (attack_effect[i].player != tmp) {
            gDPSetPrimColor(gfx++, 0, 0, col_prim_434[attack_effect[i].player].r,
                            col_prim_434[attack_effect[i].player].g, col_prim_434[attack_effect[i].player].b, 255);

            gDPSetEnvColor(gfx++, col_env_435[attack_effect[i].player].r, col_env_435[attack_effect[i].player].g,
                           col_env_435[attack_effect[i].player].b, alpha);

            tmp = attack_effect[i].player;
        }

        //! @bug ?
        //! Is the `+ 2` intentional?
        texture = attack_sprite_address[1][attack_effect[i].cnt + 2];
        StretchTexBlock4i(&gfx, ETC_ATTACK_SPRITES_WIDTH, ETC_ATTACK_SPRITES_HEIGHT, texture, x, y,
                          ETC_ATTACK_SPRITES_WIDTH, ETC_ATTACK_SPRITES_HEIGHT);

        attack_effect[i].cnt++;
        if (attack_effect[i].cnt >= 8) {
            attack_effect[i].cnt = 0;
        }

        if ((attack_effect[i].time % 4U) == 3) {
            attack_sprite[attack_sprite_idx].time = 16;
            attack_sprite[attack_sprite_idx].col = attack_effect[i].player;

            attack_sprite[attack_sprite_idx].no = rand() % 3;
            attack_sprite[attack_sprite_idx].x = attack_effect[i].x + (rand() % 4);
            attack_sprite[attack_sprite_idx].y = attack_effect[i].y + (rand() % 4);

            attack_sprite_idx++;
            if (attack_sprite_idx >= ARRAY_COUNT(attack_sprite)) {
                attack_sprite_idx = 0;
            }
        }
    }

    tmp = -1;

    for (i = 0; i < ARRAY_COUNT(attack_sprite); i++) {
        if (attack_sprite[i].time <= 0) {
            continue;
        }

        attack_sprite[i].time--;
        if (attack_sprite[i].col != tmp) {
            gDPSetPrimColor(gfx++, 0, 0, col_prim_434[attack_sprite[i].col].r, col_prim_434[attack_sprite[i].col].g,
                            col_prim_434[attack_sprite[i].col].b, 255);

            gDPSetEnvColor(gfx++, col_env_435[attack_sprite[i].col].r, col_env_435[attack_sprite[i].col].g,
                           col_env_435[attack_sprite[i].col].b, 240);

            tmp = attack_sprite[i].col;
        }

        texture = attack_sprite_address[0][attack_sprite[i].no * 4 + attack_sprite[i].time / 2];
        StretchTexBlock4i(&gfx, ETC_ATTACK_SPRITES_WIDTH, ETC_ATTACK_SPRITES_HEIGHT, texture, attack_sprite[i].x,
                          attack_sprite[i].y, ETC_ATTACK_SPRITES_WIDTH, ETC_ATTACK_SPRITES_HEIGHT);
    }

    *gfxP = gfx;
}

/**
 * Original filename: game_etc.c
 */

#include "game_etc.h"

#include "attributes.h"
#include "libc/assert.h"
#include "gcc/stdlib.h"

#include "macros_defines.h"

#include "dm_game_main.h"
#include "tex_func.h"
#include "main_story.h"
#include "lws.h"
#include "066840.h"

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

static s32 binCount;
static bool cont_bg_flg;
static void *etcTexAddress;
static void **etcLwsAddress;
static void *etcLwsTbl[14];
static u8 D_800E5408[0x8] UNUSED;
static s32 logo_ofsY;
static s32 etc_mode;
static struct_g_etc_work g_etc_work[MAXCONTROLLERS];
static u8 D_800E57D8[0x40] UNUSED;
static Mtx etc_viewMtx;

typedef enum EtcPartIndex {
    /*  0 */ ETC_PART_INDEX_GRAPHBIN_0,
    /*  1 */ ETC_PART_INDEX_GRAPHBIN_1,
    /*  2 */ ETC_PART_INDEX_GRAPHBIN_2,
    /*  3 */ ETC_PART_INDEX_GRAPHBIN_3,
    /*  4 */ ETC_PART_INDEX_GRAPHBIN_4,
    /*  5 */ ETC_PART_INDEX_GRAPHBIN_5,
    /*  6 */ ETC_PART_INDEX_GRAPHBIN_6,
    /*  7 */ ETC_PART_INDEX_GRAPHBIN_7,
    /*  8 */ ETC_PART_INDEX_GRAPHBIN_8,
    /*  9 */ ETC_PART_INDEX_GRAPHBIN_9,
    /* 10 */ ETC_PART_INDEX_GRAPHBIN_10,
    /* 11 */ ETC_PART_INDEX_GRAPHBIN_11,
    /* 12 */ ETC_PART_INDEX_GRAPHBIN_12,
    /* 13 */ ETC_PART_INDEX_GRAPHBIN_13,
    /* 14 */ ETC_PART_INDEX_LWS,
    /* 15 */ ETC_PART_INDEX_ATTACK_SPRITE,
    /* 16 */ ETC_PART_INDEX_MAX,
} EtcPartIndex;

s32 pause_table[][6] = {
    { ETC_PART_INDEX_GRAPHBIN_2, ETC_PART_INDEX_GRAPHBIN_8, ETC_PART_INDEX_GRAPHBIN_1, ETC_PART_INDEX_GRAPHBIN_0,
      ETC_PART_INDEX_GRAPHBIN_2, ETC_PART_INDEX_GRAPHBIN_2 },
    { ETC_PART_INDEX_GRAPHBIN_3, ETC_PART_INDEX_GRAPHBIN_7, ETC_PART_INDEX_GRAPHBIN_2, ETC_PART_INDEX_GRAPHBIN_0,
      ETC_PART_INDEX_GRAPHBIN_1, ETC_PART_INDEX_GRAPHBIN_2 },
};
s32 cont_table[][6] = {
    { ETC_PART_INDEX_GRAPHBIN_2, ETC_PART_INDEX_GRAPHBIN_0, ETC_PART_INDEX_GRAPHBIN_1, ETC_PART_INDEX_GRAPHBIN_0,
      ETC_PART_INDEX_GRAPHBIN_3, ETC_PART_INDEX_GRAPHBIN_3 },
    { ETC_PART_INDEX_GRAPHBIN_3, ETC_PART_INDEX_GRAPHBIN_6, ETC_PART_INDEX_GRAPHBIN_2, ETC_PART_INDEX_GRAPHBIN_0,
      ETC_PART_INDEX_GRAPHBIN_2, ETC_PART_INDEX_GRAPHBIN_3 },
    { ETC_PART_INDEX_GRAPHBIN_2, ETC_PART_INDEX_GRAPHBIN_4, ETC_PART_INDEX_GRAPHBIN_1, ETC_PART_INDEX_GRAPHBIN_0,
      ETC_PART_INDEX_GRAPHBIN_1, ETC_PART_INDEX_GRAPHBIN_1 },
    { ETC_PART_INDEX_GRAPHBIN_3, ETC_PART_INDEX_GRAPHBIN_9, ETC_PART_INDEX_GRAPHBIN_2, ETC_PART_INDEX_GRAPHBIN_0,
      ETC_PART_INDEX_GRAPHBIN_1, ETC_PART_INDEX_GRAPHBIN_3 },
};

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

s32 x2p[2] = { -0x5C, 0x5C };
s32 x4p[4] = { -0x6C, -0x24, 0x24, 0x6C };
Vp etc_vp = { {
    { 0x280, 0x1E0, 0x1FF, 0 },
    { 0x280, 0x1E0, 0x1FF, 0 },
} };
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
Color_RGB32 col_prim_434[] = {
    { 255, 0, 48 },
    { 64, 64, 255 },
    { 255, 200, 0 },
    { 0, 255, 0 },
};
Color_RGB32 col_env_435[] = {
    { 255, 192, 210 },
    { 220, 220, 255 },
    { 255, 255, 220 },
    { 210, 255, 210 },
};

void initEtcWork(void *gameEtcSeg, s32 count) {
    s32 i;

    if (evs_gamemode == ENUM_EVS_GAMEMODE_3) {
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

    guOrtho(&etc_viewMtx, -160.0f, 160.0f, -120.0f, 120.0f, 1.0f, 2000.0f, 1.0f);

    for (i = 0; i < binCount; i++) {
        s32 j;

        g_etc_work[i].unk_00 = game_state_data[i].unk_006;
        g_etc_work[i].unk_04 = game_state_data[i].unk_008;
        g_etc_work[i].unk_08 = game_state_data[i].unk_00A * 8.0f;
        g_etc_work[i].unk_0C = game_state_data[i].unk_00A * 17.0f;

        for (j = 0; j < G_ETC_WORK_VAL; j++) {
            g_etc_work[i].unk_10[j] = 0;

            g_etc_work[i].unk_30[j] = g_etc_work[i].unk_50[j] = 0.0f;

            g_etc_work[i].unk_70[j] = g_etc_work[i].unk_90[j] = g_etc_work[i].unk_B0[j] = g_etc_work[i].unk_D0[j] =
                0xFF;
        }
    }

    attack_effect_idx = 0;
    for (i = 0; i < ARRAY_COUNT(attack_effect); i++) {
        attack_effect[i].unk_20 = 0;
    }

    attack_sprite_idx = 0;
    for (i = 0; i < ARRAY_COUNT(attack_sprite); i++) {
        attack_sprite[i].unk_10 = 0;
    }
}

void init_pause_disp(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        s32 j;

        for (j = 0; j < G_ETC_WORK_VAL; j++) {
            g_etc_work[i].unk_10[j] = 0;
            g_etc_work[i].unk_30[j] = g_etc_work[i].unk_50[j] = 0.0f;
            g_etc_work[i].unk_70[j] = g_etc_work[i].unk_90[j] = g_etc_work[i].unk_B0[j] = g_etc_work[i].unk_D0[j] =
                0xFF;
        }
    }
}

void disp_logo_setup(Gfx **gfxP) {
    Gfx *gfx = *gfxP;

    init_objMtx();
    gSPMatrix(gfx++, OS_K0_TO_PHYSICAL(&etc_viewMtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gSPSegment(gfx++, 0x05, osVirtualToPhysical(etcLwsAddress));
    *gfxP = gfx;
}

UNK_TYPE disp_count_logo(Gfx **gfxP, s32 arg1, UNK_TYPE arg2) {
    Mtx mtx;
    Gfx *gfx = *gfxP;
    s32 var_a1;
    s32 var_a2;
    UNK_TYPE ret;

    gSPDisplayList(gfx++, etc_setup);

    switch (binCount) {
        case 1:
            var_a1 = 0;
            var_a2 = 0;
            break;

        case 2:
            var_a1 = x2p[arg1];
            var_a2 = 0;
            break;

        default:
            var_a1 = x4p[arg1];
            var_a2 = 0;
            break;
    }

    makeTransrateMatrix(&mtx, var_a1 << 15, var_a2 << 15, 0xFE0C << 16);
    ret = lws_anim(&gfx, &mtx, etcLwsTbl[ETC_LWS_INDEX_9], arg2, etcLwsAddress);

    *gfxP = gfx;
    return ret;
}

void disp_clear_logo(Gfx **gfxP, s32 arg1, s32 arg2) {
    Gfx *gfx = *gfxP;
    Mtx mtx;
    u32 x;
    u32 y;
    struct_g_etc_work *temp_s0;

    gSPDisplayList(gfx++, etc_setup);

    temp_s0 = &g_etc_work[arg1];

    switch (binCount) {
        case 0x1:
            x = -4;
            y = 0;
            break;

        case 0x2:
            x = x2p[arg1] - 4;
            y = 0;
            break;

        default:
            x = x4p[arg1] - 4;
            y = 0;
            break;
    }

    makeTransrateMatrix(&mtx, x << 0xF, y << 0xF, 0x1FC18 << 0xF);

    if (lws_anim(&gfx, &mtx, etcLwsTbl[ETC_LWS_INDEX_10], temp_s0->unk_10[0], etcLwsAddress) == 1) {
        temp_s0->unk_10[0] = 0x27;
    }
    temp_s0->unk_10[0]++;

    if (arg2 != 0) {
        if (lws_anim(&gfx, &mtx, etcLwsTbl[ETC_LWS_INDEX_11], temp_s0->unk_10[1], etcLwsAddress) == 1) {
            temp_s0->unk_10[1] = 0x3B;
        }
        temp_s0->unk_10[1]++;
    }

    *gfxP = gfx;
}

void disp_allclear_logo(Gfx **gfxP, s32 arg1, s32 arg2) {
    Gfx *gfx = *gfxP;
    Mtx mtx;
    u32 x;
    u32 y;
    struct_g_etc_work *temp_s0;

    gSPDisplayList(gfx++, etc_setup);

    temp_s0 = &g_etc_work[arg1];

    switch (binCount) {
        case 0x1:
            x = -4;
            y = 0;
            break;

        case 0x2:
            x = x2p[arg1] - 4;
            y = 0;
            break;

        default:
            x = x4p[arg1] - 4;
            y = 0;
            break;
    }

    makeTransrateMatrix(&mtx, x << 0xF, y << 0xF, 0x1FC18 << 0xF);

    if (lws_anim(&gfx, &mtx, etcLwsTbl[ETC_LWS_INDEX_13], temp_s0->unk_10[1], etcLwsAddress) == 1) {
        temp_s0->unk_10[1] = 0x27;
    }
    temp_s0->unk_10[1]++;

    if (arg2 != 0) {
        if (lws_anim(&gfx, &mtx, etcLwsTbl[ETC_LWS_INDEX_11], temp_s0->unk_10[2], etcLwsAddress) == 1) {
            temp_s0->unk_10[2] = 0x3B;
        }
        temp_s0->unk_10[2]++;
    }

    *gfxP = gfx;
}

void disp_win_logo(Gfx **gfxP, s32 arg1) {
    Gfx *gfx = *gfxP;
    Mtx mtx;
    u32 x;
    u32 y;
    struct_g_etc_work *temp_s0;

    gSPDisplayList(gfx++, etc_setup);

    temp_s0 = &g_etc_work[arg1];

    switch (binCount) {
        case 0x1:
            x = 0;
            y = 0;
            break;

        case 0x2:
            x = x2p[arg1];
            y = 0;
            break;

        default:
            x = x4p[arg1];
            y = 2;
            break;
    }

    makeTransrateMatrix(&mtx, x << 0xF, (y + logo_ofsY) << 0xF, 0x1FC18 << 0xF);

    if (binCount != 4) {
        if (lws_anim(&gfx, &mtx, etcLwsTbl[ETC_LWS_INDEX_0], temp_s0->unk_10[0], etcLwsAddress) == 1) {
            temp_s0->unk_10[0] = 0x3F;
        }
    } else {
        if (lws_anim(&gfx, &mtx, etcLwsTbl[ETC_LWS_INDEX_1], temp_s0->unk_10[0], etcLwsAddress) == 1) {
            temp_s0->unk_10[0] = 0x3F;
        }
    }
    temp_s0->unk_10[0]++;

    *gfxP = gfx;
}

void disp_lose_logo(Gfx **gfxP, s32 arg1) {
    Gfx *gfx = *gfxP;
    Mtx mtx;
    u32 x;
    u32 y;
    struct_g_etc_work *temp_s0;

    gSPDisplayList(gfx++, etc_setup);

    temp_s0 = &g_etc_work[arg1];

    switch (binCount) {
        case 0x1:
            x = 0;
            y = 0;
            break;

        case 0x2:
            x = x2p[arg1];
            y = 0;
            break;

        default:
            x = x4p[arg1];
            y = 2;
            break;
    }

    makeTransrateMatrix(&mtx, x << 0xF, (y + logo_ofsY) << 0xF, 0x1FC18 << 0xF);

    if (binCount != 4) {
        if (lws_anim(&gfx, &mtx, etcLwsTbl[ETC_LWS_INDEX_2], temp_s0->unk_10[0], etcLwsAddress) == 1) {
            temp_s0->unk_10[0] = 0x37;
        }
    } else {
        if (lws_anim(&gfx, &mtx, etcLwsTbl[ETC_LWS_INDEX_3], temp_s0->unk_10[0], etcLwsAddress) == 1) {
            temp_s0->unk_10[0] = 0x37;
        }
    }
    temp_s0->unk_10[0]++;

    *gfxP = gfx;
}

void disp_draw_logo(Gfx **gfxP, s32 arg1) {
    Gfx *gfx = *gfxP;
    Mtx mtx;
    u32 x;
    u32 y;
    struct_g_etc_work *temp_s0;

    gSPDisplayList(gfx++, etc_setup);

    temp_s0 = &g_etc_work[arg1];

    switch (binCount) {
        case 0x1:
            x = 0;
            y = 0;
            break;

        case 0x2:
            x = x2p[arg1];
            y = 0;
            break;

        default:
            x = x4p[arg1];
            y = 2;
            break;
    }

    makeTransrateMatrix(&mtx, x << 0xF, (y + logo_ofsY) << 0xF, 0x1FC18 << 0xF);

    if (binCount != 4) {
        if (lws_anim(&gfx, &mtx, etcLwsTbl[ETC_LWS_INDEX_4], temp_s0->unk_10[0], etcLwsAddress) == 1) {
            temp_s0->unk_10[0] = 0xF;
        }
    } else {
        if (lws_anim(&gfx, &mtx, etcLwsTbl[ETC_LWS_INDEX_5], temp_s0->unk_10[0], etcLwsAddress) == 1) {
            temp_s0->unk_10[0] = 0xF;
        }
    }
    temp_s0->unk_10[0]++;

    *gfxP = gfx;
}

s32 disp_pause_logo(Gfx **gfxP, s32 arg1, s32 arg2 UNUSED, s32 arg3, s32 arg4) {
    Gfx *gfx = *gfxP;
    struct_g_etc_work *temp_s1 = &g_etc_work[arg1];
    GbiStat sp38;
    GbiStat sp50;
    Mtx sp68;
    s32 var_a1;
    s32 var_a2;
    s32 temp;
    s32 pad[5] UNUSED;

    temp_s1->unk_30[7] = temp_s1->unk_00 + (temp_s1->unk_08 / 2.0) - 20.0;
    temp_s1->unk_50[7] = temp_s1->unk_04 + 10.0f;

    temp_s1->unk_30[2] = temp_s1->unk_00 + (temp_s1->unk_08 / 2.0) - 31.0;

    if (pause_table[arg4][0] == 2) {
        temp_s1->unk_50[2] = (temp_s1->unk_04 + temp_s1->unk_0C - 35) - 2;
    } else {
        temp_s1->unk_50[2] = (temp_s1->unk_04 + temp_s1->unk_0C - 50) - 2;
    }

    gSPDisplayList(gfx++, etc_setup);

    switch (binCount) {
        case 1:
            var_a1 = 0;
            var_a2 = 0;
            break;

        case 2:
            var_a1 = x2p[arg1];
            var_a2 = 0;
            break;

        default:
            // case 4:
            var_a1 = x4p[arg1];
            var_a2 = 8;
            break;
    }

    makeTransrateMatrix(&sp68, var_a1 << 0xF, var_a2 << 0xF, 0xFE0C0000);
    if (binCount != 4) {
        if (lws_anim(&gfx, &sp68, etcLwsTbl[ETC_LWS_INDEX_7], temp_s1->unk_10[7], etcLwsAddress) == 1) {
            temp_s1->unk_10[7] = 0x19;
        }
    } else {
        if (lws_anim(&gfx, &sp68, etcLwsTbl[ETC_LWS_INDEX_7], temp_s1->unk_10[7], etcLwsAddress) == 1) {
            temp_s1->unk_10[7] = 0x19;
        }
    }

    gSPDisplayList(gfx++, alpha_texture_init_dl);

    temp = temp_s1->unk_10[6] - 0x10;
    if ((arg3 >= 0) && (temp > 0)) {
        f32 var_fs0;
        f32 var_fs1;

        get_gbi_stat(&sp38, RELOCATE_OFFSET(etcTexAddress, etc_parts_tbl[pause_table[arg4][1]]));
        get_gbi_stat(&sp50, RELOCATE_OFFSET(etcTexAddress, etc_parts_tbl[pause_table[arg4][2]]));
        StretchAlphaTexBlock(&gfx, sp38.width, sp38.height, sp38.texture, sp38.width, sp50.texture, sp50.width,
                             temp_s1->unk_30[2], temp_s1->unk_50[2], sp38.width, sp38.height);

        if (pause_table[arg4][0] == 2) {
            switch (arg3) {
                case 0x0:
                    var_fs1 = temp_s1->unk_30[2];
                    var_fs0 = temp_s1->unk_50[2] + 0.0f + 1.0f;
                    break;

                case 0x1:
                    var_fs1 = temp_s1->unk_30[2];
                    var_fs0 = temp_s1->unk_50[2] + 16.0f - 2.0f;
                    break;
            }
        } else {
            switch (arg3) {
                case 0x0:
                    var_fs1 = temp_s1->unk_30[2];
                    var_fs0 = temp_s1->unk_50[2] + 0.0f - 1.0f;
                    break;

                case 0x1:
                    var_fs1 = temp_s1->unk_30[2];
                    var_fs0 = temp_s1->unk_50[2] + 16.0f - 1.0f;
                    break;

                case 0x2:
                    var_fs1 = temp_s1->unk_30[2];
                    var_fs0 = temp_s1->unk_50[2] + 31.0f - 1.0f;
                    break;
            }
        }

        if (temp_s1->unk_10[5] & 0x10) {
            gSPDisplayList(gfx++, normal_texture_init_dl);
            get_gbi_stat(&sp38, RELOCATE_OFFSET(etcTexAddress, etc_parts_tbl[ETC_PART_INDEX_GRAPHBIN_3]));
            StretchTexBlock4(&gfx, sp38.width, sp38.height, sp38.tlut, sp38.texture, var_fs1, var_fs0, sp38.width,
                             sp38.height);
        }
    }

    temp_s1->unk_10[5]++;
    temp_s1->unk_10[6]++;
    temp_s1->unk_10[7]++;

    gSPDisplayList(gfx++, normal_texture_init_dl);

    *gfxP = gfx;

    return pause_table[arg4][arg3 + 3];
}

s32 etc_continue_logo(Gfx **gfxP, s32 arg1, s32 arg2, s32 arg3) {
    Gfx *gfx = *gfxP;
    struct_g_etc_work *temp_s2 = &g_etc_work[arg1];
    GbiStat sp38;
    GbiStat sp50;
    f32 var_fs0;
    f32 var_fs1;

    if (arg2 >= 0) {
        if (cont_bg_flg) {
            if (binCount == 2) {
                gSPDisplayList(gfx++, normal_texture_init_dl);
                gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
                gDPSetCombineLERP(gfx++, 0, 0, 0, PRIMITIVE, PRIMITIVE, 0, TEXEL0, 0, 0, 0, 0, PRIMITIVE, PRIMITIVE, 0,
                                  TEXEL0, 0);
                gDPSetTextureLUT(gfx++, G_TT_NONE);
                gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, 160);

                get_gbi_stat(&sp50, RELOCATE_OFFSET(etcTexAddress, etc_parts_tbl[cont_table[arg3][2]]));
                StretchTexBlock4i(&gfx, sp50.width, sp50.height, sp50.texture, temp_s2->unk_30[6] + 6.0f,
                                  temp_s2->unk_50[6] + 6.0f, sp50.width, sp50.height);
            }
        }

        gSPDisplayList(gfx++, alpha_texture_init_dl);

        get_gbi_stat(&sp38, RELOCATE_OFFSET(etcTexAddress, etc_parts_tbl[cont_table[arg3][1]]));
        get_gbi_stat(&sp50, RELOCATE_OFFSET(etcTexAddress, etc_parts_tbl[cont_table[arg3][2]]));
        StretchAlphaTexBlock(&gfx, sp38.width, sp38.height, sp38.texture, sp38.width, sp50.texture, sp50.width,
                             temp_s2->unk_30[6], temp_s2->unk_50[6], sp38.width, sp38.height);

        if (cont_table[arg3][0] == 2) {
            switch (arg2) {
                case 0x0:
                    var_fs1 = temp_s2->unk_30[6];
                    var_fs0 = temp_s2->unk_50[6] + 0.0f + 1.0f;
                    break;
                case 0x1:
                    var_fs1 = temp_s2->unk_30[6];
                    var_fs0 = temp_s2->unk_50[6] + 16.0f - 2.0f;
                    break;
            }
        } else {
            switch (arg2) {
                case 0x0:
                    var_fs1 = temp_s2->unk_30[6];
                    var_fs0 = temp_s2->unk_50[6] + 0.0f - 1.0f;
                    break;
                case 0x1:
                    var_fs1 = temp_s2->unk_30[6];
                    var_fs0 = temp_s2->unk_50[6] + 16.0f - 1.0f;
                    break;
                case 0x2:
                    var_fs1 = temp_s2->unk_30[6];
                    var_fs0 = temp_s2->unk_50[6] + 31.0f - 1.0f;
                    break;
            }
        }

        if (temp_s2->unk_10[6] & 0x10) {
            gSPDisplayList(gfx++, normal_texture_init_dl);

            get_gbi_stat(&sp38, RELOCATE_OFFSET(etcTexAddress, etc_parts_tbl[ETC_PART_INDEX_GRAPHBIN_3]));
            StretchTexBlock4(&gfx, sp38.width, sp38.height, sp38.tlut, sp38.texture, var_fs1, var_fs0, sp38.width,
                             sp38.height);
        }
    }

    temp_s2->unk_10[6]++;

    gSPDisplayList(gfx++, normal_texture_init_dl);

    *gfxP = gfx;

    return cont_table[arg3][arg2 + 3];
}

s32 disp_continue_logo(Gfx **gfxP, s32 arg1, s32 arg2, s32 arg3) {
    struct_g_etc_work *temp_t0;

    cont_bg_flg = false;
    temp_t0 = &g_etc_work[arg1];

    temp_t0->unk_30[6] = temp_t0->unk_00 + temp_t0->unk_08 / 2.0 - 31;

    if (cont_table[arg3][0] == 2) {
        temp_t0->unk_50[6] = temp_t0->unk_04 + temp_t0->unk_0C - 35 - 2;
    } else {
        temp_t0->unk_50[6] = temp_t0->unk_04 + temp_t0->unk_0C - 50 - 2;
    }

    return etc_continue_logo(gfxP, arg1, arg2, arg3);
}

s32 disp_continue_logo_score(Gfx **gfxP, s32 arg1, s32 arg2, s32 arg3) {
    struct_g_etc_work *temp_t0;

    cont_bg_flg = true;
    temp_t0 = &g_etc_work[arg1];
    temp_t0->unk_30[6] = 129.0f;

    if (cont_table[arg3][0] == 2) {
        temp_t0->unk_50[6] = (temp_t0->unk_04 + temp_t0->unk_0C - 35) - 2;
    } else {
        temp_t0->unk_50[6] = (temp_t0->unk_04 + temp_t0->unk_0C - 50) - 2;
    }

    return etc_continue_logo(gfxP, arg1, arg2, arg3);
}

void disp_gameover_logo(Gfx **gfxP, s32 arg1) {
    Gfx *gfx = *gfxP;
    Mtx mtx;
    u32 x;
    u32 y;
    struct_g_etc_work *temp_s0;

    gSPDisplayList(gfx++, etc_setup);

    temp_s0 = &g_etc_work[arg1];

    switch (binCount) {
        case 0x1:
            x = -2;
            y = 0;
            break;

        case 0x2:
            x = x2p[arg1] - 2;
            y = 0;
            break;

        default:
            x = x4p[arg1] - 2;
            y = 0;
            break;
    }

    makeTransrateMatrix(&mtx, x << 0xF, y << 0xF, 0x1FC18 << 0xF);

    if (lws_anim(&gfx, &mtx, etcLwsTbl[ETC_LWS_INDEX_8], temp_s0->unk_10[1], etcLwsAddress) == 1) {
        temp_s0->unk_10[1] = 0x39;
    }
    temp_s0->unk_10[1]++;

    *gfxP = gfx;
}

void disp_timeover_logo(Gfx **gfxP, s32 arg1) {
    Gfx *gfx = *gfxP;
    Mtx mtx;
    u32 x;
    u32 y;
    struct_g_etc_work *temp_s0;

    gSPDisplayList(gfx++, etc_setup);

    temp_s0 = &g_etc_work[arg1];

    switch (binCount) {
        case 0x1:
            x = -2;
            y = 0;
            break;

        case 0x2:
            x = x2p[arg1] - 2;
            y = 0;
            break;

        default:
            x = x4p[arg1] - 2;
            y = 0;
            break;
    }

    makeTransrateMatrix(&mtx, x << 0xF, y << 0xF, 0x1FC18 << 0xF);

    if (lws_anim(&gfx, &mtx, etcLwsTbl[ETC_LWS_INDEX_12], temp_s0->unk_10[0], etcLwsAddress) == 1) {
        temp_s0->unk_10[0] = 0x39;
    }
    temp_s0->unk_10[0]++;

    *gfxP = gfx;
}

void disp_retire_logo(Gfx **gfxP, s32 arg1) {
    Gfx *gfx = *gfxP;
    Mtx mtx;
    u32 x;
    u32 y;
    struct_g_etc_work *temp_s0;

    gSPDisplayList(gfx++, etc_setup);

    temp_s0 = &g_etc_work[arg1];

    switch (binCount) {
        case 0x1:
            x = -2;
            y = 0;
            break;

        case 0x2:
            x = x2p[arg1];
            y = 0;
            break;

        default:
            x = x4p[arg1];
            y = 0;
            break;
    }

    makeTransrateMatrix(&mtx, x << 0xF, y << 0xF, 0x1FC18 << 0xF);

    if (lws_anim(&gfx, &mtx, etcLwsTbl[ETC_LWS_INDEX_6], temp_s0->unk_10[2], etcLwsAddress) == 1) {
        temp_s0->unk_10[2] = 0x8B;
    }
    temp_s0->unk_10[2]++;

    *gfxP = gfx;
}

void disp_timestop_logo(Gfx **gfxP, s32 arg1) {
    Gfx *gfx = *gfxP;
    struct_g_etc_work *temp_s3 = &g_etc_work[arg1];
    GbiStat sp30;

    get_gbi_stat(&sp30, RELOCATE_OFFSET(etcTexAddress, etc_parts_tbl[ETC_PART_INDEX_GRAPHBIN_11]));

    gSPDisplayList(gfx++, normal_texture_init_dl);
    gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gDPSetCombineLERP(gfx++, 0, 0, 0, 0, 0, 0, 0, TEXEL0, 0, 0, 0, 0, 0, 0, 0, TEXEL0);
    gDPSetTextureLUT(gfx++, G_TT_NONE);

    StretchTexBlock4i(&gfx, sp30.width, sp30.height, sp30.texture, 43.0f, 157.0f, sp30.width, sp30.height);
    get_gbi_stat(&sp30, RELOCATE_OFFSET(etcTexAddress, etc_parts_tbl[ETC_PART_INDEX_GRAPHBIN_10]));

    gSPDisplayList(gfx++, normal_texture_init_dl);

    StretchTexBlock4(&gfx, sp30.width, sp30.height, sp30.tlut, sp30.texture, 43.0f, 157.0f, sp30.width, sp30.height);
    if (temp_s3->unk_10[4] & 0x10) {
        get_gbi_stat(&sp30, RELOCATE_OFFSET(etcTexAddress, etc_parts_tbl[ETC_PART_INDEX_GRAPHBIN_12]));
        StretchTexBlock4(&gfx, sp30.width, sp30.height, sp30.tlut, sp30.texture, 37.0f, 175.0f, sp30.width,
                         sp30.height);
    }
    temp_s3->unk_10[4]++;

    *gfxP = gfx;
}

void add_attack_effect(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    attack_effect[attack_effect_idx].unk_28 = arg0;
    attack_effect[attack_effect_idx].unk_20 = 0x30;
    attack_effect[attack_effect_idx].unk_24 = 0;
    attack_effect[attack_effect_idx].unk_00 = arg1;
    attack_effect[attack_effect_idx].unk_04 = arg2;
    attack_effect[attack_effect_idx].unk_08 = arg1;
    attack_effect[attack_effect_idx].unk_0C = arg2;
    attack_effect[attack_effect_idx].unk_10 = arg3;
    attack_effect[attack_effect_idx].unk_14 = arg4;
    attack_effect[attack_effect_idx].unk_18 = arg1;
    attack_effect[attack_effect_idx].unk_1C = arg2;

    attack_effect_idx++;
    if (attack_effect_idx >= ARRAY_COUNT(attack_effect)) {
        attack_effect_idx = 0;
    }
}

void disp_attack_effect(Gfx **gfxP) {
    Gfx *gfx;
    f32 x;
    f32 y;
    f32 temp_ft0;
    f32 var_fs4;
    s32 var_s5;
    s32 i;
    s32 alpha;
    u8 *texture;

    gfx = *gfxP;

    gSPDisplayList(gfx++, normal_texture_init_dl);
    gDPSetTextureLUT(gfx++, G_TT_NONE);
    gDPSetAlphaCompare(gfx++, G_AC_NONE);
    gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gDPSetCombineLERP(gfx++, ENVIRONMENT, PRIMITIVE, TEXEL0, PRIMITIVE, ENVIRONMENT, 0, TEXEL0, 0, ENVIRONMENT,
                      PRIMITIVE, TEXEL0, PRIMITIVE, ENVIRONMENT, 0, TEXEL0, 0);

    switch (binCount) {
        case 1:
        case 2:
            var_fs4 = 50.0f;
            break;

        case 4:
        default:
            var_fs4 = 30.0f;
            break;
    }

    var_s5 = -1;
    for (i = 0; i < ARRAY_COUNT(attack_effect); i++) {
        if (attack_effect[i].unk_20 <= 0) {
            continue;
        }

        attack_effect[i].unk_20--;

        temp_ft0 = attack_effect[i].unk_20 / 48.0f;

        x = attack_effect[i].unk_10 - temp_ft0 * (attack_effect[i].unk_10 - attack_effect[i].unk_08);

        y = attack_effect[i].unk_14 - temp_ft0 * (attack_effect[i].unk_14 - attack_effect[i].unk_0C);
        y -= var_fs4 * sinf((temp_ft0 * 180.0 * M_PI) / 180.0);

        attack_effect[i].unk_00 = x + 0.5;
        attack_effect[i].unk_04 = y + 0.5;

        alpha = 240;
        if (attack_effect[i].unk_20 >= 0x29) {
            alpha = 48 - attack_effect[i].unk_20;
            alpha = alpha * 30;
        }
        if (attack_effect[i].unk_20 < 8) {
            alpha = attack_effect[i].unk_20 * 30;
        }

        if (attack_effect[i].unk_28 != var_s5) {
            gDPSetPrimColor(gfx++, 0, 0, col_prim_434[attack_effect[i].unk_28].r,
                            col_prim_434[attack_effect[i].unk_28].g, col_prim_434[attack_effect[i].unk_28].b, 255);

            gDPSetEnvColor(gfx++, col_env_435[attack_effect[i].unk_28].r, col_env_435[attack_effect[i].unk_28].g,
                           col_env_435[attack_effect[i].unk_28].b, alpha);

            var_s5 = attack_effect[i].unk_28;
        }

        //! @bug ?
        //! Is the `+ 2` intentional?
        texture = attack_sprite_address[1][attack_effect[i].unk_24 + 2];
        StretchTexBlock4i(&gfx, ETC_ATTACK_SPRITES_WIDTH, ETC_ATTACK_SPRITES_HEIGHT, texture, x, y,
                          ETC_ATTACK_SPRITES_WIDTH, ETC_ATTACK_SPRITES_HEIGHT);

        attack_effect[i].unk_24++;
        if (attack_effect[i].unk_24 >= 8) {
            attack_effect[i].unk_24 = 0;
        }

        if ((attack_effect[i].unk_20 & 3) == 3) {
            attack_sprite[attack_sprite_idx].unk_10 = 0x10;
            attack_sprite[attack_sprite_idx].unk_08 = attack_effect[i].unk_28;

            attack_sprite[attack_sprite_idx].unk_0C = rand() % 3;
            attack_sprite[attack_sprite_idx].x = attack_effect[i].unk_00 + (rand() % 4);
            attack_sprite[attack_sprite_idx].y = attack_effect[i].unk_04 + (rand() % 4);

            attack_sprite_idx++;
            if (attack_sprite_idx >= ARRAY_COUNT(attack_sprite)) {
                attack_sprite_idx = 0;
            }
        }
    }

    var_s5 = -1;

    for (i = 0; i < ARRAY_COUNT(attack_sprite); i++) {
        if (attack_sprite[i].unk_10 <= 0) {
            continue;
        }

        attack_sprite[i].unk_10--;
        if (attack_sprite[i].unk_08 != var_s5) {
            gDPSetPrimColor(gfx++, 0, 0, col_prim_434[attack_sprite[i].unk_08].r,
                            col_prim_434[attack_sprite[i].unk_08].g, col_prim_434[attack_sprite[i].unk_08].b, 255);

            gDPSetEnvColor(gfx++, col_env_435[attack_sprite[i].unk_08].r, col_env_435[attack_sprite[i].unk_08].g,
                           col_env_435[attack_sprite[i].unk_08].b, 240);

            var_s5 = attack_sprite[i].unk_08;
        }

        texture = attack_sprite_address[0][attack_sprite[i].unk_0C * 4 + attack_sprite[i].unk_10 / 2];
        StretchTexBlock4i(&gfx, ETC_ATTACK_SPRITES_WIDTH, ETC_ATTACK_SPRITES_HEIGHT, texture, attack_sprite[i].x,
                          attack_sprite[i].y, ETC_ATTACK_SPRITES_WIDTH, ETC_ATTACK_SPRITES_HEIGHT);
    }

    *gfxP = gfx;
}

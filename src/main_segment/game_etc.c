/**
 * Original filename: game_etc.c
 */

#include "game_etc.h"

#include "include_asm.h"
#include "macros_defines.h"
#include "unknown_structs.h"
#include "main_segment_variables.h"
#include "tex_func.h"
#include "main_story.h"
#include "lws.h"
#include "066840.h"

static s32 binCount;
static bool cont_bg_flg;
static void *etcTexAddress;
static void **etcLwsAddress;
static struct_etcLwsTbl etcLwsTbl;
static s32 logo_ofsY;
static s32 etc_mode;
static struct_g_etc_work g_etc_work[MAXCONTROLLERS];
static u8 D_800E57D8[0x40] UNUSED;
static Mtx etc_viewMtx;

s32 pause_table[][6] = {
    { 2, 8, 1, 0, 2, 2 },
    { 3, 7, 2, 0, 1, 2 },
};
s32 cont_table[][6] = {
    { 2, 0, 1, 0, 3, 3 },
    { 3, 6, 2, 0, 2, 3 },
    { 2, 4, 1, 0, 1, 1 },
    { 3, 9, 2, 0, 1, 3 },
};
// TODO: these are offsets within the asset file.
s32 etc_parts_tbl[] = {
    0,      0x1310, 0x1960, 0x21B0, 0x2620, 0x3930, 0x3F80, 0x5A90,
    0x75A0, 0x88B0, 0xA3C0, 0xA7D0, 0xABE0, 0,      0xAF58, 0x24198,
};
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

void initEtcWork(void *arg0, s32 arg1) {
    s32 i;

    if (evs_gamemode == ENUM_EVS_GAMEMODE_3) {
        logo_ofsY = 0x10;
    } else {
        logo_ofsY = 0;
    }

    binCount = arg1;
    etcTexAddress = arg0;
    etcLwsAddress = (void **)((uintptr_t)arg0 + etc_parts_tbl[0xE]);
    attack_sprite_address = (void *)(uintptr_t)arg0 + etc_parts_tbl[0xF];

    for (i = 0; i < 0xE; i++) {
        uintptr_t temp = (uintptr_t)etcLwsAddress[i];

        temp = (uintptr_t)RELOCATE_SEGMENTED(temp, arg0) + etc_parts_tbl[0xE];
        etcLwsTbl.unk_00[i] = (UNK_PTR)temp;
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
    ret = lws_anim(&gfx, &mtx, etcLwsTbl.unk_00[9], arg2, etcLwsAddress);

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

    if (lws_anim(&gfx, &mtx, etcLwsTbl.unk_00[0xA], temp_s0->unk_10[0], etcLwsAddress) == 1) {
        temp_s0->unk_10[0] = 0x27;
    }
    temp_s0->unk_10[0]++;

    if (arg2 != 0) {
        if (lws_anim(&gfx, &mtx, etcLwsTbl.unk_00[0xB], temp_s0->unk_10[1], etcLwsAddress) == 1) {
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

    if (lws_anim(&gfx, &mtx, etcLwsTbl.unk_00[0xD], temp_s0->unk_10[1], etcLwsAddress) == 1) {
        temp_s0->unk_10[1] = 0x27;
    }
    temp_s0->unk_10[1]++;

    if (arg2 != 0) {
        if (lws_anim(&gfx, &mtx, etcLwsTbl.unk_00[0xB], temp_s0->unk_10[2], etcLwsAddress) == 1) {
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
        if (lws_anim(&gfx, &mtx, etcLwsTbl.unk_00[0], temp_s0->unk_10[0], etcLwsAddress) == 1) {
            temp_s0->unk_10[0] = 0x3F;
        }
    } else {
        if (lws_anim(&gfx, &mtx, etcLwsTbl.unk_00[1], temp_s0->unk_10[0], etcLwsAddress) == 1) {
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
        if (lws_anim(&gfx, &mtx, etcLwsTbl.unk_00[2], temp_s0->unk_10[0], etcLwsAddress) == 1) {
            temp_s0->unk_10[0] = 0x37;
        }
    } else {
        if (lws_anim(&gfx, &mtx, etcLwsTbl.unk_00[3], temp_s0->unk_10[0], etcLwsAddress) == 1) {
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
        if (lws_anim(&gfx, &mtx, etcLwsTbl.unk_00[4], temp_s0->unk_10[0], etcLwsAddress) == 1) {
            temp_s0->unk_10[0] = 0xF;
        }
    } else {
        if (lws_anim(&gfx, &mtx, etcLwsTbl.unk_00[5], temp_s0->unk_10[0], etcLwsAddress) == 1) {
            temp_s0->unk_10[0] = 0xF;
        }
    }
    temp_s0->unk_10[0]++;

    *gfxP = gfx;
}

s32 disp_pause_logo(Gfx **gfxP, s32 arg1, s32 arg2 UNUSED, s32 arg3, s32 arg4) {
    Gfx *gfx = *gfxP;
    struct_g_etc_work *temp_s1 = &g_etc_work[arg1];
    struct_get_gbi_stat_arg0 sp38;
    struct_get_gbi_stat_arg0 sp50;
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
        if (lws_anim(&gfx, &sp68, etcLwsTbl.unk_00[7], temp_s1->unk_10[7], etcLwsAddress) == 1) {
            temp_s1->unk_10[7] = 0x19;
        }
    } else {
        if (lws_anim(&gfx, &sp68, etcLwsTbl.unk_00[7], temp_s1->unk_10[7], etcLwsAddress) == 1) {
            temp_s1->unk_10[7] = 0x19;
        }
    }

    gSPDisplayList(gfx++, alpha_texture_init_dl);

    temp = temp_s1->unk_10[6] - 0x10;
    if ((arg3 >= 0) && (temp > 0)) {
        f32 var_fs0;
        f32 var_fs1;

        get_gbi_stat(&sp38, (struct_wakuGraphic *)((uintptr_t)etcTexAddress + etc_parts_tbl[pause_table[arg4][1]]));
        get_gbi_stat(&sp50, (struct_wakuGraphic *)((uintptr_t)etcTexAddress + etc_parts_tbl[pause_table[arg4][2]]));
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
            get_gbi_stat(&sp38, (struct_wakuGraphic *)((uintptr_t)etcTexAddress + etc_parts_tbl[3]));
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
    struct_get_gbi_stat_arg0 sp38;
    struct_get_gbi_stat_arg0 sp50;
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

                get_gbi_stat(&sp50, etcTexAddress + etc_parts_tbl[cont_table[arg3][2]]);
                StretchTexBlock4i(&gfx, sp50.width, sp50.height, sp50.texture, temp_s2->unk_30[6] + 6.0f,
                                  temp_s2->unk_50[6] + 6.0f, sp50.width, sp50.height);
            }
        }

        gSPDisplayList(gfx++, alpha_texture_init_dl);

        get_gbi_stat(&sp38, etcTexAddress + etc_parts_tbl[cont_table[arg3][1]]);
        get_gbi_stat(&sp50, etcTexAddress + etc_parts_tbl[cont_table[arg3][2]]);
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

            get_gbi_stat(&sp38, (void *)((uintptr_t)etcTexAddress + etc_parts_tbl[3]));
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

    if (lws_anim(&gfx, &mtx, etcLwsTbl.unk_00[8], temp_s0->unk_10[1], etcLwsAddress) == 1) {
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

    if (lws_anim(&gfx, &mtx, etcLwsTbl.unk_00[0xC], temp_s0->unk_10[0], etcLwsAddress) == 1) {
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

    if (lws_anim(&gfx, &mtx, etcLwsTbl.unk_00[0x6], temp_s0->unk_10[2], etcLwsAddress) == 1) {
        temp_s0->unk_10[2] = 0x8B;
    }
    temp_s0->unk_10[2]++;

    *gfxP = gfx;
}

void disp_timestop_logo(Gfx **gfxP, s32 arg1) {
    Gfx *gfx = *gfxP;
    struct_g_etc_work *temp_s3 = &g_etc_work[arg1];
    struct_get_gbi_stat_arg0 sp30;

    get_gbi_stat(&sp30, etcTexAddress + etc_parts_tbl[0xB]);

    gSPDisplayList(gfx++, normal_texture_init_dl);
    gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gDPSetCombineLERP(gfx++, 0, 0, 0, 0, 0, 0, 0, TEXEL0, 0, 0, 0, 0, 0, 0, 0, TEXEL0);
    gDPSetTextureLUT(gfx++, G_TT_NONE);

    StretchTexBlock4i(&gfx, sp30.width, sp30.height, sp30.texture, 43.0f, 157.0f, sp30.width, sp30.height);
    get_gbi_stat(&sp30, etcTexAddress + etc_parts_tbl[0xA]);

    gSPDisplayList(gfx++, normal_texture_init_dl);

    StretchTexBlock4(&gfx, sp30.width, sp30.height, sp30.tlut, sp30.texture, 43.0f, 157.0f, sp30.width, sp30.height);
    if (temp_s3->unk_10[4] & 0x10) {
        get_gbi_stat(&sp30, etcTexAddress + etc_parts_tbl[0xC]);
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
    f32 temp_fs0;
    f32 temp_fs1;
    f32 temp_ft0;
    f32 var_fs4;
    s32 var_s5;
    s32 var_s6;
    s32 var_t1;
    void *temp;

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
    for (var_s6 = 0; var_s6 < 0x10; var_s6++) {
        if (attack_effect[var_s6].unk_20 <= 0) {
            continue;
        }

        attack_effect[var_s6].unk_20--;

        temp_ft0 = attack_effect[var_s6].unk_20 / 48.0f;

        temp_fs1 =
            attack_effect[var_s6].unk_10 - temp_ft0 * (attack_effect[var_s6].unk_10 - attack_effect[var_s6].unk_08);

        temp_fs0 =
            attack_effect[var_s6].unk_14 - temp_ft0 * (attack_effect[var_s6].unk_14 - attack_effect[var_s6].unk_0C);
        temp_fs0 -= var_fs4 * sinf(((temp_ft0 * 180.0 * M_PI) / 180.0));

        attack_effect[var_s6].unk_00 = temp_fs1 + 0.5;
        attack_effect[var_s6].unk_04 = temp_fs0 + 0.5;

        var_t1 = 0xF0;
        if (attack_effect[var_s6].unk_20 >= 0x29) {
            var_t1 = (0x30 - attack_effect[var_s6].unk_20);
            var_t1 = var_t1 * 0x1E;
        }
        if (attack_effect[var_s6].unk_20 < 8) {
            var_t1 = attack_effect[var_s6].unk_20 * 0x1E;
        }

        if (attack_effect[var_s6].unk_28 != var_s5) {
            gDPSetPrimColor(gfx++, 0, 0, col_prim_434[attack_effect[var_s6].unk_28].r,
                            col_prim_434[attack_effect[var_s6].unk_28].g, col_prim_434[attack_effect[var_s6].unk_28].b,
                            255);

            gDPSetEnvColor(gfx++, col_env_435[attack_effect[var_s6].unk_28].r,
                           col_env_435[attack_effect[var_s6].unk_28].g, col_env_435[attack_effect[var_s6].unk_28].b,
                           var_t1);

            var_s5 = attack_effect[var_s6].unk_28;
        }

        temp = (void *)((uintptr_t)attack_sprite_address + 0x1800 + attack_effect[var_s6].unk_24 * 0x200);
        StretchTexBlock4i(&gfx, 0x20, 0x20, temp, temp_fs1, temp_fs0, 32.0f, 32.0f);

        attack_effect[var_s6].unk_24++;
        if (attack_effect[var_s6].unk_24 >= 8) {
            attack_effect[var_s6].unk_24 = 0;
        }

        if ((attack_effect[var_s6].unk_20 & 3) == 3) {
            attack_sprite[attack_sprite_idx].unk_10 = 0x10;
            attack_sprite[attack_sprite_idx].unk_08 = attack_effect[var_s6].unk_28;

            attack_sprite[attack_sprite_idx].unk_0C = rand() % 3;
            attack_sprite[attack_sprite_idx].unk_00 = attack_effect[var_s6].unk_00 + (rand() % 4);
            attack_sprite[attack_sprite_idx].unk_04 = attack_effect[var_s6].unk_04 + (rand() % 4);

            attack_sprite_idx++;
            if (attack_sprite_idx >= 0x80) {
                attack_sprite_idx = 0;
            }
        }
    }

    var_s5 = -1;

    for (var_s6 = 0; var_s6 < 0x80; var_s6++) {
        if (attack_sprite[var_s6].unk_10 <= 0) {
            continue;
        }

        attack_sprite[var_s6].unk_10--;
        if (attack_sprite[var_s6].unk_08 != var_s5) {
            gDPSetPrimColor(gfx++, 0, 0, col_prim_434[attack_sprite[var_s6].unk_08].r,
                            col_prim_434[attack_sprite[var_s6].unk_08].g, col_prim_434[attack_sprite[var_s6].unk_08].b,
                            255);

            gDPSetEnvColor(gfx++, col_env_435[attack_sprite[var_s6].unk_08].r,
                           col_env_435[attack_sprite[var_s6].unk_08].g, col_env_435[attack_sprite[var_s6].unk_08].b,
                           240);

            var_s5 = attack_sprite[var_s6].unk_08;
        }

        temp = (void *)((uintptr_t)attack_sprite_address +
                        0x200 * (attack_sprite[var_s6].unk_0C * 4 + attack_sprite[var_s6].unk_10 / 2));
        StretchTexBlock4i(&gfx, 0x20, 0x20, temp, attack_sprite[var_s6].unk_00, attack_sprite[var_s6].unk_04, 32.0f,
                          32.0f);
    }

    *gfxP = gfx;
}

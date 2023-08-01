/**
 * Original filename: game_etc.c
 */

#include "game_etc.h"
#include "libultra.h"
#include "include_asm.h"
#include "macros_defines.h"
#include "unknown_structs.h"
#include "main_segment_functions.h"
#include "main_segment_variables.h"
#include "tex_func.h"
#include "main_story.h"

#if VERSION_US
#if 0
extern void *etcTexAddress;
extern s32 logo_ofsY;
extern s32 etc_mode;
extern ? g_etc_work;
extern ? B_800E541C;
extern ? B_800E5420;
extern ? B_800E5424;
extern ?32 B_800E5428;
extern ? B_800E54A8;
extern s32 attack_sprite_idx;
extern s32 attack_effect_idx;
extern ? B_800F3EA0;
extern void *attack_sprite_address;
extern ? B_800FB3C8;
extern s32 D_8008D0B8;
extern s32 D_8008D0BC;

void initEtcWork(void *arg0, s32 arg1) {
    ?32 *var_a0;
    ?32 *var_a1_2;
    ?32 *var_a2_2;
    ?32 *var_a3;
    ?32 *var_s0;
    ?32 *var_s1;
    ?32 *var_t1;
    ?32 *var_t2;
    ?32 *var_t8;
    ?32 *var_t9;
    ?32 *var_v1;
    s32 *var_a1;
    s32 temp_v1;
    s32 var_t0;
    s32 var_t3;
    s32 var_t5;
    s32 var_t5_2;
    s32 var_t6;
    s32 var_v0;
    s32 var_v0_2;
    s8 *var_t7;
    struct_etcLwsTbl *var_a2;

    if (evs_gamemode == ENUM_EVS_GAMEMODE_3) {
        logo_ofsY = 0x10;
        var_t5 = 0;
    } else {
        logo_ofsY = 0;
        var_t5 = 0;
    }
    var_a2 = &etcLwsTbl;
    binCount = arg1;
    etcTexAddress = arg0;
    var_a1 = arg0 + D_8008D0B8;
    etcLwsAddress = var_a1;
    attack_sprite_address = arg0 + D_8008D0BC;
    do {
        temp_v1 = *var_a1;
        var_a1 += 4;
        var_t5 += 1;
        *var_a2 = (void *) ((temp_v1 & 0xFFFFFF) + arg0 + D_8008D0B8);
        var_a2 += 4;
    } while (var_t5 < 0xE);
    if (binCount > 0) {
        if (binCount >= 3) {
            if (binCount != 4) {

            } else {
                etc_mode = 1;
            }
        } else {
            etc_mode = 0;
        }
    }
    guOrtho(&etc_viewMtx, -160.0f, 160.0f, -120.0f, 120.0f, 1.0f, 2000.0f, 1.0f);
    var_t5_2 = 0;
    if (binCount > 0) {
        var_s1 = &B_800E5428 + 0x60;
        var_s0 = &B_800E5428 + 0x40;
        var_t9 = &B_800E5428 + 0x20;
        var_t8 = &B_800E5428;
        var_t0 = 0;
        var_t7 = &game_state_data->unk_00A;
        var_t6 = 0;
        do {
            *(&g_etc_work + var_t0) = (f32) *(&game_state_data->unk_006 + var_t6);
            *(&B_800E541C + var_t0) = (f32) *(&game_state_data->unk_008 + var_t6);
            var_t3 = 0;
            var_t2 = var_s1;
            var_a1_2 = var_t9;
            *(&B_800E5420 + var_t0) = (f32) *var_t7 * 8.0f;
            var_a0 = var_s0;
            var_t1 = var_t0 + &B_800E54A8;
            var_a3 = var_t0 + (&B_800E54A8 + 0x20);
            var_a2_2 = var_t0 + (&B_800E54A8 + 0x40);
            var_v1 = var_t8;
            *(&B_800E5424 + var_t0) = (f32) *var_t7 * 17.0f;
loop_14:
            *var_v1 = 0;
            *var_a0 = 0;
            *var_a1_2 = 0;
            *var_a2_2 = 0xFF;
            *var_a3 = 0xFF;
            *var_t1 = 0xFF;
            *var_t2 = 0xFF;
            var_t2 += 4;
            var_t1 += 4;
            var_a3 += 4;
            var_a2_2 += 4;
            var_a1_2 += 4;
            var_a0 += 4;
            var_t3 += 1;
            var_v1 += 4;
            if (var_t3 < 8) {
                goto loop_14;
            }
            var_s1 += 0xF0;
            var_s0 += 0xF0;
            var_t9 += 0xF0;
            var_t8 += 0xF0;
            var_t0 += 0xF0;
            var_t7 += 0x3C4;
            var_t5_2 += 1;
            var_t6 += 0x3C4;
        } while (var_t5_2 < binCount);
    }
    attack_effect_idx = 0;
    var_v0 = 0x294;
    do {
        *(&B_800FB3C8 + var_v0) = 0;
        var_v0 -= 0x2C;
    } while (var_v0 >= 0);
    attack_sprite_idx = 0;
    var_v0_2 = 0x9EC;
    do {
        *(&B_800F3EA0 + var_v0_2) = 0;
        var_v0_2 -= 0x14;
    } while (var_v0_2 >= 0);
}
#else
INCLUDE_ASM("asm/us/nonmatchings/main_segment/game_etc", initEtcWork);
#endif
#endif

#if VERSION_CN
#ifdef NON_MATCHING
void initEtcWork(void *arg0, s32 arg1) {
    s32 var_t0;
    s32 var_t5;

    if (evs_gamemode == ENUM_EVS_GAMEMODE_3) {
        logo_ofsY = 0x10;
    } else {
        logo_ofsY = 0;
    }

    binCount = arg1;
    etcTexAddress = arg0;
    etcLwsAddress = arg0 + etc_parts_tbl[0xE];
    attack_sprite_address = arg0 + etc_parts_tbl[0xF];

    for (var_t0 = 0; var_t0 < 0xE; var_t0++) {
        etcLwsTbl.unk_00[var_t0] = ((uintptr_t)etcLwsAddress[var_t0] & 0xFFFFFF) + arg0 + etc_parts_tbl[0xE];
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

    for (var_t0 = 0; var_t0 < binCount; var_t0++) {
        g_etc_work[var_t0].unk_00 = game_state_data[var_t0].unk_006;
        g_etc_work[var_t0].unk_04 = game_state_data[var_t0].unk_008;
        g_etc_work[var_t0].unk_08 = game_state_data[var_t0].unk_00A * 8.0f;
        g_etc_work[var_t0].unk_0C = game_state_data[var_t0].unk_00A * 17.0f;

        var_t5 = 0;
        while (var_t5 < 8) {
            g_etc_work[var_t0].unk_10[var_t5] = 0;

            g_etc_work[var_t0].unk_30[var_t5] = g_etc_work[var_t0].unk_50[var_t5] = 0.0f;
            g_etc_work[var_t0].unk_70[var_t5] = g_etc_work[var_t0].unk_90[var_t5] = g_etc_work[var_t0].unk_B0[var_t5] =
                g_etc_work[var_t0].unk_D0[var_t5] = 0xFF;

            var_t5 += 1;
        }
    }

    attack_effect_idx = 0;
    for (var_t0 = 0; var_t0 < 0x10; var_t0++) {
        attack_effect[var_t0].unk_20 = 0;
    }

    attack_sprite_idx = 0;
    for (var_t0 = 0; var_t0 < 0x80; var_t0++) {
        attack_sprite[var_t0].unk_10 = 0;
    }
}
#else
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/game_etc", initEtcWork);
#endif
#endif

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

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/game_etc", disp_pause_logo);
#endif

#if VERSION_CN
#ifdef NON_EQUIVALENT
s32 disp_pause_logo(Gfx **gfxP, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    struct_get_gbi_stat_arg0 sp38;
    struct_get_gbi_stat_arg0 sp50;
    Mtx sp68;
    s32 pad[4];
    Gfx *gfx; // spC0
    s32 var_a1;
    s32 var_a2;
    struct_g_etc_work *temp_s1;

    gfx = *gfxP;

    temp_s1 = &g_etc_work[arg1];

    temp_s1->unk_30[7] = temp_s1->unk_00 + (temp_s1->unk_08 * 0.5) - 20;
    temp_s1->unk_30[2] = temp_s1->unk_00 + (temp_s1->unk_08 * 0.5) - 31;

    temp_s1->unk_50[7] = temp_s1->unk_04 + 10.0f;

    if (pause_table[arg4].unk_00[0] == 2) {
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
            var_a2 = 8;
            var_a1 = x4p[arg1];
            break;
    }

    makeTransrateMatrix(&sp68, var_a1 << 0xF, var_a2 << 0xF, 0xFE0C0000);
    if (lws_anim(&gfx, &sp68, etcLwsTbl.unk_00[7], temp_s1->unk_10[7], etcLwsAddress) == 1) {
        temp_s1->unk_10[7] = 0x19;
    }

    gSPDisplayList(gfx++, alpha_texture_init_dl);

    if (arg3 >= 0) {
        if (temp_s1->unk_10[6] - 0x10 > 0) {
            f32 var_fs0;
            f32 var_fs1;

            get_gbi_stat(&sp38, (uintptr_t)etcTexAddress + etc_parts_tbl[pause_table[arg4].unk_04]);
            get_gbi_stat(&sp50, (uintptr_t)etcTexAddress + etc_parts_tbl[pause_table[arg4].unk_08]);
            StretchAlphaTexBlock(&gfx, sp38.unk_04, sp38.unk_08, sp38.unk_10, sp38.unk_04, sp50.unk_10, sp50.unk_04,
                                 temp_s1->unk_30[2], temp_s1->unk_50[2], (f32)sp38.unk_04, (f32)sp38.unk_08);
            if (pause_table[arg4].unk_00[0] == 2) {
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
                get_gbi_stat(&sp38, (uintptr_t)etcTexAddress + etc_parts_tbl[3]);
                StretchTexBlock4(&gfx, sp38.unk_04, sp38.unk_08, sp38.unk_0C, sp38.unk_10, var_fs1, var_fs0,
                                 sp38.unk_04, sp38.unk_08);
            }
        }
    }

    temp_s1->unk_10[5]++;
    temp_s1->unk_10[6]++;
    temp_s1->unk_10[7]++;

    gSPDisplayList(gfx++, normal_texture_init_dl);

    *gfxP = gfx;
    return pause_table[arg4].unk_00[arg3 + 3];
}
#else
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/game_etc", disp_pause_logo);
#endif
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/game_etc", etc_continue_logo);
#endif

#if VERSION_CN
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

                get_gbi_stat(&sp50, etcTexAddress + etc_parts_tbl[cont_table[arg3].unk_08]);
                StretchTexBlock4i(&gfx, sp50.unk_04, sp50.unk_08, sp50.unk_10, temp_s2->unk_30[6] + 6.0f,
                                  temp_s2->unk_50[6] + 6.0f, sp50.unk_04, sp50.unk_08);
            }
        }

        gSPDisplayList(gfx++, alpha_texture_init_dl);

        get_gbi_stat(&sp38, etcTexAddress + etc_parts_tbl[cont_table[arg3].unk_04]);
        get_gbi_stat(&sp50, etcTexAddress + etc_parts_tbl[cont_table[arg3].unk_08]);
        StretchAlphaTexBlock(&gfx, sp38.unk_04, sp38.unk_08, sp38.unk_10, sp38.unk_04, sp50.unk_10, sp50.unk_04,
                             temp_s2->unk_30[6], temp_s2->unk_50[6], sp38.unk_04, sp38.unk_08);

        if (cont_table[arg3].unk_00[0] == 2) {
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
            StretchTexBlock4(&gfx, sp38.unk_04, sp38.unk_08, sp38.unk_0C, sp38.unk_10, var_fs1, var_fs0, sp38.unk_04,
                             sp38.unk_08);
        }
    }

    temp_s2->unk_10[6]++;

    gSPDisplayList(gfx++, normal_texture_init_dl);

    *gfxP = gfx;

    return cont_table[arg3].unk_00[arg2 + 3];
}
#endif

s32 disp_continue_logo(Gfx **gfxP, s32 arg1, s32 arg2, s32 arg3) {
    struct_g_etc_work *temp_t0;

    cont_bg_flg = false;
    temp_t0 = &g_etc_work[arg1];

#if VERSION_US
    temp_t0->unk_30[6] = temp_t0->unk_00 + temp_t0->unk_08 / 2.0 - 31;
#endif
#if VERSION_CN
    temp_t0->unk_30[6] = temp_t0->unk_00 + temp_t0->unk_08 * 0.5 - 31;
#endif

    if (cont_table[arg3].unk_00[0] == 2) {
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

    if (cont_table[arg3].unk_00[0] == 2) {
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

    StretchTexBlock4i(&gfx, sp30.unk_04, sp30.unk_08, sp30.unk_10, 43.0f, 157.0f, (f32)sp30.unk_04, (f32)sp30.unk_08);
    get_gbi_stat(&sp30, etcTexAddress + etc_parts_tbl[0xA]);

    gSPDisplayList(gfx++, normal_texture_init_dl);

    StretchTexBlock4(&gfx, sp30.unk_04, sp30.unk_08, sp30.unk_0C, sp30.unk_10, 43.0f, 157.0f, (f32)sp30.unk_04,
                     (f32)sp30.unk_08);
    if (temp_s3->unk_10[4] & 0x10) {
        get_gbi_stat(&sp30, etcTexAddress + etc_parts_tbl[0xC]);
        StretchTexBlock4(&gfx, sp30.unk_04, sp30.unk_08, sp30.unk_0C, sp30.unk_10, 37.0f, 175.0f, (f32)sp30.unk_04,
                         (f32)sp30.unk_08);
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

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/game_etc", disp_attack_effect);
#endif

#if VERSION_CN
#ifdef NON_EQUIVALENT
void disp_attack_effect(Gfx **gfxP) {
    Gfx *gfx;
    f32 temp_fs0;
    f32 temp_fs1;
    f32 temp_ft0;
    f32 var_fs4;
    s32 temp_v0_6;
    s32 temp_v0_7;
    s32 var_a1;
    s32 var_a2;
    s32 var_s0;
    s32 var_s5;
    s32 var_s6;
    s32 var_t1;

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

        temp_fs0 =
            attack_effect[var_s6].unk_14 - (temp_ft0 * (attack_effect[var_s6].unk_14 - attack_effect[var_s6].unk_0C));
        temp_fs1 =
            attack_effect[var_s6].unk_10 - (temp_ft0 * (attack_effect[var_s6].unk_10 - attack_effect[var_s6].unk_08));

        temp_fs0 -= (var_fs4 * sinf(((temp_ft0 * 180.0 * 3.141592653589793) / 180.0)));

        attack_effect[var_s6].unk_00 = temp_fs1 + 0.5;
        attack_effect[var_s6].unk_04 = temp_fs0 + 0.5;

        var_t1 = 0xF0;
        if (attack_effect[var_s6].unk_20 >= 0x29) {
            var_t1 = (0x30 - attack_effect[var_s6].unk_20) * 0x1E;
        }
        if (attack_effect[var_s6].unk_20 < 8) {
            var_t1 = attack_effect[var_s6].unk_20 * 0x1E;
        }

        if (attack_effect[var_s6].unk_28 != var_s5) {

            gDPSetPrimColor(gfx++, 0, 0, (u8)col_prim_434[attack_effect[var_s6].unk_28].r,
                            (u8)col_prim_434[attack_effect[var_s6].unk_28].g,
                            (u8)col_prim_434[attack_effect[var_s6].unk_28].b, 255);

            gDPSetEnvColor(gfx++, (u8)col_env_435[attack_effect[var_s6].unk_28].r,
                           (u8)col_env_435[attack_effect[var_s6].unk_28].g,
                           (u8)col_env_435[attack_effect[var_s6].unk_28].b, (var_t1 & 0xFF));

            var_s5 = attack_effect[var_s6].unk_28;
        }

        StretchTexBlock4i(&gfx, 0x20, 0x20, attack_sprite_address + ((attack_effect[var_s6].unk_24 << 9) + 0x1800),
                          temp_fs1, temp_fs0, 32.0f, 32.0f);

        attack_effect[var_s6].unk_24++;
        if (attack_effect[var_s6].unk_24 >= 8) {
            attack_effect[var_s6].unk_24 = 0;
        }

        if ((attack_effect[var_s6].unk_20 & 3) == 3) {
            attack_sprite[attack_sprite_idx].unk_10 = 0x10;
            attack_sprite[attack_sprite_idx].unk_08 = (s32)attack_effect[var_s6].unk_28;
            attack_sprite[attack_sprite_idx].unk_0C = (s32)(rand() % 3);

#if 0
            temp_v0_6 = rand();
            var_a1 = temp_v0_6;
            if (temp_v0_6 < 0) {
                var_a1 = temp_v0_6 + 3;
            }
            attack_sprite[attack_sprite_idx].unk_00 = attack_effect[var_s6].unk_20 + (temp_v0_6 - ((var_a1 >> 2) * 4));
#else
            attack_sprite[attack_sprite_idx].unk_00 = attack_effect[var_s6].unk_20 + (rand() % 4);
#endif

#if 0
            temp_v0_7 = rand();
            var_a2 = temp_v0_7;

            if (temp_v0_7 < 0) {
                var_a2 = temp_v0_7 + 3;
            }

            attack_sprite[attack_sprite_idx].unk_04 = attack_effect[var_s6].unk_04 + (temp_v0_7 - ((var_a2 >> 2) * 4));
#else
            attack_sprite[attack_sprite_idx].unk_04 = attack_effect[var_s6].unk_04 + (rand() % 4);
#endif

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

            gDPSetPrimColor(gfx++, 0, 0, (u8)col_prim_434[attack_sprite[var_s6].unk_08].r,
                            (u8)col_prim_434[attack_sprite[var_s6].unk_08].g,
                            (u8)col_prim_434[attack_sprite[var_s6].unk_08].b, 255);

            gDPSetEnvColor(gfx++, (u8)col_env_435[attack_sprite[var_s6].unk_08].r,
                           (u8)col_env_435[attack_sprite[var_s6].unk_08].g,
                           (u8)col_env_435[attack_sprite[var_s6].unk_08].b, 240);
            var_s5 = attack_sprite[var_s6].unk_08;
        }

        StretchTexBlock4i(&gfx, 0x20, 0x20,
                          attack_sprite_address +
                              (((attack_sprite[var_s6].unk_0C * 4) + ((s32)attack_sprite[var_s6].unk_10 / 2)) << 9),
                          (f32)attack_sprite[var_s6].unk_00, (f32)attack_sprite[var_s6].unk_04, 32.0f, 32.0f);
    }
    *gfxP = gfx;
}
#else
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/game_etc", disp_attack_effect);
#endif
#endif

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

#if VERSION_US
#if 0
extern void *B_800E53C8;
extern s32 logo_ofsY;
extern s32 etc_mode;
extern ? B_800E5418;
extern ? B_800E541C;
extern ? B_800E5420;
extern ? B_800E5424;
extern ?32 B_800E5428;
extern ? B_800E54A8;
extern s32 B_800EA284;
extern s32 B_800EF548;
extern ? B_800F3EA0;
extern void *B_800F748C;
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
    B_800E53C8 = arg0;
    var_a1 = arg0 + D_8008D0B8;
    etcLwsAddress = var_a1;
    B_800F748C = arg0 + D_8008D0BC;
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
            *(&B_800E5418 + var_t0) = (f32) *(&game_state_data->unk_006 + var_t6);
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
    B_800EF548 = 0;
    var_v0 = 0x294;
    do {
        *(&B_800FB3C8 + var_v0) = 0;
        var_v0 -= 0x2C;
    } while (var_v0 >= 0);
    B_800EA284 = 0;
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
#if 0
extern s32 attack_sprite_idx;
extern void *B_800CA288_cn;
extern void *etcTexAddress;
extern s32 *etcLwsAddress;
extern void *etcLwsTbl;
extern ? attack_sprite;
extern ? D_80097EC8_cn;
extern s32 etc_mode;
extern f32 g_etc_work;
extern s32 logo_ofsY;

void initEtcWork(void *arg0, s32 arg1) {
    s32 sp28;
    f32 *var_a2_2;
    f32 *var_a3;
    f32 *var_s0;
    f32 *var_s2;
    f32 *var_s3;
    f32 *var_t6;
    f32 temp_fv1;
    s16 *var_t8;
    s16 *var_t9;
    s32 *temp_v1;
    s32 *var_a0;
    s32 *var_a0_2;
    s32 *var_t1;
    s32 *var_t2;
    s32 *var_t3;
    s32 *var_t4;
    s32 *var_v1;
    s32 *var_v1_2;
    s32 temp_v0;
    s32 var_a1;
    s32 var_t0;
    s32 var_t0_2;
    s32 var_t0_3;
    s32 var_t0_4;
    s32 var_t5;
    s8 *var_s1;
    void **var_a2;

    if (evs_gamemode == ENUM_EVS_GAMEMODE_3) {
        logo_ofsY = 0x10;
        var_t0 = 0;
    } else {
        logo_ofsY = 0;
        var_t0 = 0;
    }
    var_a2 = &etcLwsTbl;
    binCount = arg1;
    etcTexAddress = arg0;
    temp_v1 = arg0 + D_80097EC8_cn.unk_0;
    var_a0 = temp_v1;
    etcLwsAddress = temp_v1;
    B_800CA288_cn = arg0 + D_80097EC8_cn.unk_4;
    do {
        temp_v0 = *var_a0;
        var_a0 += 4;
        var_t0 += 1;
        *var_a2 = (temp_v0 & 0xFFFFFF) + arg0 + D_80097EC8_cn.unk_0;
        var_a2 += 4;
    } while (var_t0 < 0xE);
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
    var_t0_2 = 0;
    if (binCount > 0) {
        var_a1 = 0;
        var_s3 = &g_etc_work + 0xC;
        var_s2 = &g_etc_work + 8;
        var_s1 = &game_state_data->unk_00A;
        var_s0 = &g_etc_work + 4;
        var_t9 = &game_state_data->unk_008;
        var_t6 = &g_etc_work;
        var_t8 = &game_state_data->unk_006;
        sp28 = binCount;
        do {
            var_t5 = 0;
            var_t4 = var_a1 + (&g_etc_work + 0x70);
            var_t3 = var_a1 + (&g_etc_work + 0x90);
            var_t2 = var_a1 + (&g_etc_work + 0xB0);
            var_t1 = var_a1 + (&g_etc_work + 0xD0);
            var_a3 = var_a1 + (&g_etc_work + 0x30);
            var_a2_2 = var_a1 + (&g_etc_work + 0x50);
            temp_fv1 = (f32) *var_s1;
            var_a0_2 = var_a1 + (&g_etc_work + 0x10);
            *var_t6 = (f32) *var_t8;
            *var_s0 = (f32) *var_t9;
            *var_s2 = temp_fv1 * 8.0f;
            *var_s3 = temp_fv1 * 17.0f;
loop_14:
            *var_a0_2 = 0;
            *var_a2_2 = 0.0f;
            *var_a3 = 0.0f;
            *var_t1 = 0xFF;
            *var_t2 = 0xFF;
            *var_t3 = 0xFF;
            *var_t4 = 0xFF;
            var_t4 += 4;
            var_t3 += 4;
            var_t2 += 4;
            var_t1 += 4;
            var_a3 += 4;
            var_a2_2 += 4;
            var_t5 += 1;
            var_a0_2 += 4;
            if (var_t5 < 8) {
                goto loop_14;
            }
            var_a1 += 0xF0;
            var_s3 += 0xF0;
            var_s2 += 0xF0;
            var_s1 += 0x3C4;
            var_s0 += 0xF0;
            var_t9 += 0x3C4;
            var_t6 += 0xF0;
            var_t0_2 += 1;
            var_t8 += 0x3C4;
        } while (var_t0_2 < sp28);
    }
    attack_effect_idx = 0;
    var_t0_3 = 0;
    var_v1 = &attack_effect->unk_20;
    do {
        *var_v1 = 0;
        var_t0_3 += 1;
        var_v1 += 0x2C;
    } while (var_t0_3 < 0x10);
    attack_sprite_idx = 0;
    var_t0_4 = 0;
    var_v1_2 = &attack_sprite + 0x10;
    do {
        *var_v1_2 = 0;
        var_t0_4 += 1;
        var_v1_2 += 0x14;
    } while (var_t0_4 < 0x80);
}
#else
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/game_etc", initEtcWork);
#endif
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/game_etc", func_8003ACB4);
#endif

#if VERSION_CN
void init_pause_disp(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        s32 j;

        for (j = 0; j < 8; j++) {
            g_etc_work[i].unk_10[j] = 0;
            g_etc_work[i].unk_30[j] = g_etc_work[i].unk_50[j] = 0.0f;
            g_etc_work[i].unk_70[j] = g_etc_work[i].unk_90[j] = g_etc_work[i].unk_B0[j] = g_etc_work[i].unk_D0[j] =
                0xFF;
        }
    }
}
#endif

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

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/game_etc", disp_clear_logo);
#endif

#if VERSION_CN
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
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/game_etc", func_8003B054);
#endif

#if VERSION_CN
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
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/game_etc", func_8003B1C4);
#endif

#if VERSION_CN
void disp_win_logo(Gfx **gfxP, s32 arg1) {
    Gfx *gfx = *gfxP;
    Mtx mtx;
    u32 x;
    u32 y;
    struct_g_etc_work *temp_s0;
    UNK_PTR var_a2;

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
        var_a2 = etcLwsTbl.unk_00[0];
    } else {
        var_a2 = etcLwsTbl.unk_00[1];
    }
    if (lws_anim(&gfx, &mtx, var_a2, temp_s0->unk_10[0], etcLwsAddress) == 1) {
        temp_s0->unk_10[0] = 0x3F;
    }
    temp_s0->unk_10[0]++;

    *gfxP = gfx;
}
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/game_etc", disp_lose_logo);
#endif

#if VERSION_CN
void disp_lose_logo(Gfx **gfxP, s32 arg1) {
    Gfx *gfx = *gfxP;
    Mtx mtx;
    u32 x;
    u32 y;
    struct_g_etc_work *temp_s0;
    UNK_PTR var_a2;

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
        var_a2 = etcLwsTbl.unk_00[2];
    } else {
        var_a2 = etcLwsTbl.unk_00[3];
    }
    if (lws_anim(&gfx, &mtx, var_a2, temp_s0->unk_10[0], etcLwsAddress) == 1) {
        temp_s0->unk_10[0] = 0x37;
    }
    temp_s0->unk_10[0]++;

    *gfxP = gfx;
}
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/game_etc", disp_draw_logo);
#endif

#if VERSION_CN
void disp_draw_logo(Gfx **gfxP, s32 arg1) {
    Gfx *gfx = *gfxP;
    Mtx mtx;
    u32 x;
    u32 y;
    struct_g_etc_work *temp_s0;
    UNK_PTR var_a2;

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
        var_a2 = etcLwsTbl.unk_00[4];
    } else {
        var_a2 = etcLwsTbl.unk_00[5];
    }
    if (lws_anim(&gfx, &mtx, var_a2, temp_s0->unk_10[0], etcLwsAddress) == 1) {
        temp_s0->unk_10[0] = 0xF;
    }
    temp_s0->unk_10[0]++;

    *gfxP = gfx;
}
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/game_etc", func_8003B59C);
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
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/game_etc", etc_continue_logo);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/game_etc", disp_continue_logo);
#endif

#if VERSION_CN
s32 disp_continue_logo(Gfx **gfxP, s32 arg1, s32 arg2, s32 arg3) {
    struct_g_etc_work *temp_t0;

    cont_bg_flg = 0;
    temp_t0 = &g_etc_work[arg1];
    temp_t0->unk_30[6] = temp_t0->unk_00 + temp_t0->unk_08 * 0.5 - 31;

    if (cont_table[arg3].unk_00 == 2) {
        temp_t0->unk_50[6] = temp_t0->unk_04 + temp_t0->unk_0C - 35 - 2;
    } else {
        temp_t0->unk_50[6] = temp_t0->unk_04 + temp_t0->unk_0C - 50 - 2;
    }

    return etc_continue_logo(gfxP, arg1, arg2, arg3);
}
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/game_etc", func_8003BFD8);
#endif

#if VERSION_CN
void disp_continue_logo_score(Gfx **gfxP, s32 arg1, s32 arg2, s32 arg3) {
    struct_g_etc_work *temp_t0;

    cont_bg_flg = 1;
    temp_t0 = &g_etc_work[arg1];
    temp_t0->unk_30[6] = 129.0f;

    if (cont_table[arg3].unk_00 == 2) {
        temp_t0->unk_50[6] = (temp_t0->unk_04 + temp_t0->unk_0C - 35) - 2;
    } else {
        temp_t0->unk_50[6] = (temp_t0->unk_04 + temp_t0->unk_0C - 50) - 2;
    }

    etc_continue_logo(gfxP, arg1, arg2, arg3);
}
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/game_etc", func_8003C094);
#endif

#if VERSION_CN
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
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/game_etc", func_8003C1A4);
#endif

#if VERSION_CN
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
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/game_etc", func_8003C2B4);
#endif

#if VERSION_CN
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
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/game_etc", disp_timestop_logo);
#endif

#if VERSION_CN
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
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/game_etc", add_attack_effect);
#endif

#if VERSION_CN
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
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/game_etc", disp_attack_effect);
#endif

#if VERSION_CN
#if 0
extern s32 B_800CA288_cn;
extern ? D_80097F90_cn;
extern ? D_80097F98_cn;
extern ? D_80097FC0_cn;
extern ? D_80097FC8_cn;

void disp_attack_effect(Gfx **gfxP) {
    Gfx *sp28;
    Gfx *temp_a0;
    Gfx *temp_a1;
    Gfx *temp_a3;
    Gfx *temp_a3_3;
    Gfx *temp_t0;
    Gfx *temp_t0_2;
    Gfx *temp_v0;
    Gfx *temp_v1;
    Gfx *temp_v1_2;
    f32 temp_fs0;
    f32 temp_fs0_2;
    f32 temp_fs1;
    f32 temp_ft0;
    f32 temp_ft1;
    f32 temp_ft2;
    f32 var_fs4;
    f64 temp_fv0;
    s32 *temp_a3_2;
    s32 *temp_fp;
    s32 *temp_s0;
    s32 *temp_s1;
    s32 *temp_s7;
    s32 *temp_t1;
    s32 *var_s1;
    s32 *var_s3;
    s32 temp_a0_2;
    s32 temp_a0_3;
    s32 temp_a0_4;
    s32 temp_v0_10;
    s32 temp_v0_11;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 temp_v0_5;
    s32 temp_v0_6;
    s32 temp_v0_7;
    s32 temp_v0_8;
    s32 temp_v0_9;
    s32 temp_v1_3;
    s32 var_a1;
    s32 var_a2;
    s32 var_s0;
    s32 var_s2;
    s32 var_s5;
    s32 var_s5_2;
    s32 var_s6;
    s32 var_s6_2;
    s32 var_t1;
    void *temp_v0_12;
    void *temp_v0_2;

    temp_a1 = *gfxP;
    sp28 = temp_a1 + 8;
    temp_a1->words.w0 = 0xDE000000;
    temp_a1->words.w1 = (u32) normal_texture_init_dl;
    temp_v1 = sp28;
    sp28 = temp_v1 + 8;
    temp_v1->words.w0 = 0xE3001001;
    temp_v1->words.w1 = 0;
    temp_a0 = sp28;
    sp28 = temp_a0 + 8;
    temp_a0->words.w0 = 0xE2001E01;
    temp_a0->words.w1 = 0;
    temp_v1_2 = sp28;
    temp_v0 = temp_v1_2 + 8;
    sp28 = temp_v0;
    temp_v1_2->words.w0 = 0xE200001C;
    temp_v1_2->words.w1 = 0x504240;
    temp_v0->words.w0 = 0xFC50D2A1;
    temp_v0->words.w1 = 0x33A5FEFF;
    sp28 = temp_v0 + 8;
    if ((binCount > 0) && (var_s5 = -1, ((binCount < 3) != 0))) {
        var_fs4 = 50.0f;
        var_s6 = 0;
    } else {
        var_fs4 = 30.0f;
        var_s5 = -1;
        var_s6 = 0;
    }
    var_s3 = &attack_effect->unk_20;
    var_s2 = 0;
    do {
        temp_a0_2 = *var_s3;
        if (temp_a0_2 > 0) {
            temp_a0_3 = temp_a0_2 - 1;
            temp_ft0 = (f32) temp_a0_3 / 48.0f;
            temp_v0_2 = &attack_effect->unk_20 + var_s2;
            *var_s3 = temp_a0_3;
            temp_ft2 = temp_v0_2->unk_-C;
            temp_ft1 = temp_v0_2->unk_-10;
            temp_fs0 = temp_ft2 - (temp_ft0 * (temp_ft2 - temp_v0_2->unk_-14));
            temp_fs1 = temp_ft1 - (temp_ft0 * (temp_ft1 - temp_v0_2->unk_-18));
            temp_fs0_2 = temp_fs0 - (var_fs4 * sinf((f32) (((f64) temp_ft0 * 180.0 * 3.141592653589793) / 180.0)));
            temp_s7 = var_s2 + (&attack_effect->unk_20 - 0x20);
            temp_fv0 = (f64) temp_fs0_2 + 0.5;
            temp_fp = var_s2 + (&attack_effect->unk_20 - 0x1C);
            *temp_s7 = (s32) ((f64) temp_fs1 + 0.5);
            *temp_fp = (s32) temp_fv0;
            temp_a0_4 = *var_s3;
            var_t1 = 0xF0;
            if (temp_a0_4 >= 0x29) {
                var_t1 = (0x30 - temp_a0_4) * 0x1E;
            }
            if (temp_a0_4 < 8) {
                var_t1 = temp_a0_4 * 0x1E;
            }
            temp_s1 = var_s2 + (&attack_effect->unk_20 + 8);
            if (*temp_s1 != var_s5) {
                temp_a3 = sp28;
                temp_a3->words.w0 = 0xFA000000;
                sp28 = temp_a3 + 8;
                temp_v0_3 = *temp_s1 * 0xC;
                temp_a3->words.w1 = ((temp_v0_3 + &D_80097F90_cn)->unk_3 << 0x18) | ((&D_80097F90_cn + temp_v0_3)->unk_7 << 0x10) | ((temp_v0_3 + &D_80097F98_cn)->unk_3 << 8) | 0xFF;
                temp_t0 = sp28;
                temp_t0->words.w0 = 0xFB000000;
                sp28 = temp_t0 + 8;
                temp_v0_4 = *temp_s1 * 0xC;
                temp_t0->words.w1 = ((temp_v0_4 + &D_80097FC0_cn)->unk_3 << 0x18) | ((&D_80097FC0_cn + temp_v0_4)->unk_7 << 0x10) | ((temp_v0_4 + &D_80097FC8_cn)->unk_3 << 8) | (var_t1 & 0xFF);
                var_s5 = *temp_s1;
            }
            temp_s0 = var_s2 + (&attack_effect->unk_20 + 4);
            StretchTexBlock4i(&sp28, 0x20, 0x20, B_800CA288_cn + ((*temp_s0 << 9) + 0x1800), temp_fs1, temp_fs0_2, 32.0f, 32.0f);
            temp_v0_5 = *temp_s0 + 1;
            *temp_s0 = temp_v0_5;
            if (temp_v0_5 >= 8) {
                *temp_s0 = 0;
            }
            if ((*var_s3 & 3) == 3) {
                temp_v1_3 = attack_sprite_idx * 0x14;
                *(temp_v1_3 + &attack_sprite->unk_10) = 0x10;
                (&attack_sprite->unk_10 + temp_v1_3)->unk_-8 = (s32) *temp_s1;
                (&attack_sprite->unk_10 + (attack_sprite_idx * 0x14))->unk_-4 = (s32) (rand() % 3);
                temp_v0_6 = rand();
                var_a1 = temp_v0_6;
                if (temp_v0_6 < 0) {
                    var_a1 = temp_v0_6 + 3;
                }
                attack_sprite[attack_sprite_idx].unk_00 = *temp_s7 + (temp_v0_6 - ((var_a1 >> 2) * 4));
                temp_v0_7 = rand();
                var_a2 = temp_v0_7;
                temp_a3_2 = (attack_sprite_idx * 0x14) + (&attack_sprite->unk_10 - 0xC);
                if (temp_v0_7 < 0) {
                    var_a2 = temp_v0_7 + 3;
                }
                temp_v0_8 = attack_sprite_idx + 1;
                attack_sprite_idx = temp_v0_8;
                *temp_a3_2 = *temp_fp + (temp_v0_7 - ((var_a2 >> 2) * 4));
                if (temp_v0_8 >= 0x80) {
                    attack_sprite_idx = 0;
                }
            }
        }
        var_s3 += 0x2C;
        var_s6 += 1;
        var_s2 += 0x2C;
    } while (var_s6 < 0x10);
    var_s5_2 = -1;
    var_s6_2 = 0;
    var_s1 = &attack_sprite->unk_10;
    var_s0 = 0;
    do {
        temp_v0_9 = *var_s1;
        if (temp_v0_9 > 0) {
            temp_t1 = var_s0 + (&attack_sprite->unk_10 - 8);
            *var_s1 = temp_v0_9 - 1;
            if (*temp_t1 != var_s5_2) {
                temp_a3_3 = sp28;
                temp_a3_3->words.w0 = 0xFA000000;
                sp28 += 8;
                temp_v0_10 = *temp_t1 * 0xC;
                temp_a3_3->words.w1 = ((temp_v0_10 + &D_80097F90_cn)->unk_3 << 0x18) | ((&D_80097F90_cn + temp_v0_10)->unk_7 << 0x10) | ((temp_v0_10 + (&D_80097F90_cn + 8))->unk_3 << 8) | 0xFF;
                temp_t0_2 = sp28;
                temp_t0_2->words.w0 = 0xFB000000;
                sp28 += 8;
                temp_v0_11 = *temp_t1 * 0xC;
                temp_t0_2->words.w1 = ((temp_v0_11 + &D_80097FC0_cn)->unk_3 << 0x18) | ((&D_80097FC0_cn + temp_v0_11)->unk_7 << 0x10) | ((temp_v0_11 + (&D_80097FC0_cn + 8))->unk_3 << 8) | 0xF0;
                var_s5_2 = *temp_t1;
            }
            temp_v0_12 = &attack_sprite->unk_10 + var_s0;
            StretchTexBlock4i(&sp28, 0x20, 0x20, B_800CA288_cn + (((temp_v0_12->unk_-4 * 4) + ((s32) *var_s1 / 2)) << 9), (f32) temp_v0_12->unk_-10, (f32) temp_v0_12->unk_-C, 32.0f, 32.0f);
        }
        var_s1 += 0x14;
        var_s6_2 += 1;
        var_s0 += 0x14;
    } while (var_s6_2 < 0x80);
    *gfxP = sp28;
}
#else
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/game_etc", disp_attack_effect);
#endif
#endif

/**
 * Original filename: game_etc.c
 */

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
    struct_800E53D0 *var_a2;

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
extern s32 B_800CA1D0_cn;
extern s32 attack_effect_idx;
extern void *B_800CA288_cn;
extern s32 binCount;
extern void *B_800FC048_cn;
extern s32 *B_800FC04C_cn;
extern void *B_800FC050_cn;
extern s32 logo_ofsY;
extern s32 etc_mode;
extern f32 g_etc_work;
extern ? B_800FC0A8_cn;
extern ? B_800FC0C8_cn;
extern ? B_800FC0E8_cn;
extern Mtx etc_viewMtx;
extern s32 B_8010B190_cn;
extern s32 B_80112640_cn;
extern ? D_80097EC8_cn;

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
    var_a2 = &B_800FC050_cn;
    binCount = arg1;
    B_800FC048_cn = arg0;
    temp_v1 = arg0 + D_80097EC8_cn.unk_0;
    var_a0 = temp_v1;
    B_800FC04C_cn = temp_v1;
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
            var_a3 = var_a1 + &B_800FC0C8_cn;
            var_a2_2 = var_a1 + &B_800FC0E8_cn;
            temp_fv1 = (f32) *var_s1;
            var_a0_2 = var_a1 + &B_800FC0A8_cn;
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
    var_v1 = &B_80112640_cn;
    do {
        *var_v1 = 0;
        var_t0_3 += 1;
        var_v1 += 0x2C;
    } while (var_t0_3 < 0x10);
    B_800CA1D0_cn = 0;
    var_t0_4 = 0;
    var_v1_2 = &B_8010B190_cn;
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

#if VERSION_US
void disp_logo_setup(Gfx **gfxP) {
    Gfx *gfx = *gfxP;

    init_objMtx();
    gSPMatrix(gfx++, OS_K0_TO_PHYSICAL(&etc_viewMtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gSPSegment(gfx++, 0x05, osVirtualToPhysical(etcLwsAddress));
    *gfxP = gfx;
}
#endif

#if VERSION_US
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
    ret = lws_anim(&gfx, &mtx, etcLwsTbl.unk_24, arg2, etcLwsAddress);

    *gfxP = gfx;
    return ret;
}
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/game_etc", func_8003AEE4);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/game_etc", func_8003B054);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/game_etc", func_8003B1C4);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/game_etc", func_8003B30C);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/game_etc", func_8003B454);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/game_etc", func_8003B59C);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/game_etc", func_8003BA98);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/game_etc", func_8003BEF8);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/game_etc", func_8003BFD8);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/game_etc", func_8003C094);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/game_etc", func_8003C1A4);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/game_etc", func_8003C2B4);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/game_etc", disp_timestop_logo);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/game_etc", func_8003C600);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/game_etc", func_8003C6F4);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/game_etc", func_8003DC5C_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/game_etc", func_8003DD28_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/game_etc", func_8003DDCC_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/game_etc", func_8003DEC4_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/game_etc", func_8003E06C_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/game_etc", func_8003E214_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/game_etc", func_8003E370_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/game_etc", func_8003E4CC_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/game_etc", func_8003E628_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/game_etc", func_8003EB68_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/game_etc", func_8003F038_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/game_etc", func_8003F120_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/game_etc", func_8003F1DC_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/game_etc", func_8003F30C_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/game_etc", func_8003F43C_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/game_etc", func_8003F568_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/game_etc", func_8003F820_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/game_etc", func_8003F90C_cn);
#endif

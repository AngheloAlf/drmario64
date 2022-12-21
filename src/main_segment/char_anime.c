/**
 * Original filename char_anime.c
 */

#include "ultra64.h"
#include "include_asm.h"
#include "macros_defines.h"
#include "unknown_structs.h"
#include "main_segment_functions.h"
#include "main_segment_variables.h"
#include "boot_functions.h"
#include "boot_variables.h"
#include "rom_offsets.h"

INCLUDE_RODATA("asm/nonmatchings/main_segment/char_anime", D_800B1A60);

INCLUDE_RODATA("asm/nonmatchings/main_segment/char_anime", D_800B1AB0);

INCLUDE_RODATA("asm/nonmatchings/main_segment/char_anime", D_800B1B00);

INCLUDE_RODATA("asm/nonmatchings/main_segment/char_anime", D_800B1B04);

void animeSeq_init(struct_800F3E50_unk_44C *arg0, struct_800F3E50_unk_44C_unk_0C *arg1, UNK_TYPE4 arg2) {
    arg0->unk_0C = arg1;
    arg0->unk_08 = -1;
    arg0->unk_10 = arg2;
    arg0->unk_14 = 0;
    arg0->unk_18 = -1;
    animeSeq_update(arg0, 0);
}

void func_8005E154(struct_800F3E50_unk_44C *arg0, UNK_TYPE4 arg1) {
    animeSeq_init(arg0, arg0->unk_0C, arg1);
}

#if 0
void animeSeq_update(struct_800F3E50_unk_44C *arg0, s32 arg1) {
    s32 temp_a0;
    s32 var_s2;
    s8 *temp_v1_2;
    u8 temp_s0;
    u8 temp_v0_2;
    u8 temp_v1;
    u8 *temp_a1;

    var_s2 = arg1;
    while (var_s2 >= 0) {
        temp_a0 = arg0->unk_14;
        temp_a1 = *((arg0->unk_10 * 4) + arg0->unk_0C) + temp_a0;
        temp_v1 = temp_a1[0];
        switch (temp_v1) {                      /* irregular */
            case 0xF2:
                arg0->unk_14 = 0;
                arg0->unk_08 = -1;
                arg0->unk_10 = (s32) temp_a1[1];
                break;
            case 0xFF:
                var_s2 = -1;
                break;
            case 0xF0:
                arg0->unk_14 = (s32) (temp_a0 + 2);

                arg0->unk_08++;
                arg0->unk_00[arg0->unk_08] = (s8) arg0->unk_14;
                //arg0->unk_00[arg0->unk_08].unk_4 = (u8) temp_a1[1];
                break;
            case 0xF1:
                temp_v1_2 = &arg0->unk_00[arg0->unk_08];
                //temp_v0_2 = temp_v1_2->unk_4;
                //if (temp_v0_2 != 0xFF) {
                //    temp_v1_2->unk_4 = (u8) (temp_v0_2 - 1);
                //}
                if (/*(arg0->unk_00[arg0->unk_08].unk_4 != 0) &&*/ (temp_s0 = temp_a1[1], (((rand() % 100) < (s32) temp_s0) != 0))) {
                    arg0->unk_14 = (s32) (u8) arg0->unk_00[arg0->unk_08];
                } else {
                    arg0->unk_14 = (s32) (arg0->unk_14 + 2);
                    arg0->unk_08 = (s32) (arg0->unk_08 - 1);
                }
                break;
            default:
                if (var_s2 > 0) {
                    arg0->unk_14 = (s32) (arg0->unk_14 + 1);
                }
                var_s2 -= 1;
                arg0->unk_18 = (s32) (temp_a1[0] - 1);
                break;
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/main_segment/char_anime", animeSeq_update);
#endif

bool animeSeq_isEnd(struct_800F3E50_unk_44C *arg0) {
    return arg0->unk_0C[arg0->unk_10].unk_0[arg0->unk_14] == 0xFF;
}

extern const UNK_TYPE4 D_800B1A60[];

UNK_TYPE4 animeState_getDataSize(s32 arg0) {
    return D_800B1A60[arg0];
}

INCLUDE_ASM("asm/nonmatchings/main_segment/char_anime", animeState_load);

void animeState_init(struct_800F3E50_unk_44C *arg0, struct_800F3E50_unk_44C_unk_0C *arg1, UNK_TYPE4 arg2, UNK_TYPE4 arg3, UNK_TYPE4 arg4, UNK_TYPE4 arg5) {
    animeSeq_init(arg0, arg1, 0);
    arg0->unk_1C = arg2;
    arg0->unk_20 = 0;
    arg0->unk_24 = arg3;
    arg0->unk_30 = 0xFF;
    arg0->unk_34 = 0xFF;
    arg0->unk_38 = 0xFF;
    arg0->unk_3C = 0xFF;
    arg0->unk_28 = arg4;
    arg0->unk_2C = arg5;
}

void animeState_set(struct_800F3E50_unk_44C *arg0, UNK_TYPE4 arg1) {
    arg0->unk_20 = 0;
    func_8005E154(arg0, arg1);
}

void animeState_update(struct_800F3E50_unk_44C *arg0) {
    animeSeq_update(arg0, arg0->unk_20 % 2U);
    arg0->unk_20++;
}

bool func_8005E4E0(struct_800F3E50_unk_44C *arg0) {
    return animeSeq_isEnd(arg0);
}

INCLUDE_ASM("asm/nonmatchings/main_segment/char_anime", animeState_initDL);

INCLUDE_ASM("asm/nonmatchings/main_segment/char_anime", animeState_initDL2);

void animeState_initIntensityDL(struct_800F3E50_unk_44C *arg0, Gfx **gfxP) {
    Gfx *gfx = *gfxP;

    gSPDisplayList(gfx++, normal_texture_init_dl);
    gDPSetTextureLUT(gfx++, G_TT_NONE);
    gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gDPSetCombineLERP(gfx++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0);
    gDPSetPrimColor(gfx++, 0, 0, arg0->unk_30, arg0->unk_34, arg0->unk_38, arg0->unk_3C);
    gDPSetEnvColor(gfx++, 0, 0, 0, 255);

    *gfxP = gfx;
}

INCLUDE_ASM("asm/nonmatchings/main_segment/char_anime", animeState_draw);

INCLUDE_ASM("asm/nonmatchings/main_segment/char_anime", func_8005E998);

INCLUDE_ASM("asm/nonmatchings/main_segment/char_anime", animeSmog_init);

INCLUDE_ASM("asm/nonmatchings/main_segment/char_anime", animeSmog_load);

void animeSmog_start(struct_800F3E50_unk_50C *arg0) {
    arg0->unk_120 = 0;
}

void animeSmog_stop(struct_800F3E50_unk_50C *arg0) {
    u32 i;

    for (i = 0; i < ARRAY_COUNT(arg0->unk_000); i++) {
        animeState_set(&arg0->unk_000[i], 2);
    }

    arg0->unk_120 = 0xB4;
}

void animeSmog_update(struct_800F3E50_unk_50C *arg0) {
    u32 i;

    for (i = 0; i < 4; i++) {
        animeState_update(&arg0->unk_000[i]);
        if ((arg0->unk_120 < 0xB4) && func_8005E4E0(&arg0->unk_000[i]) && (rand() % 16 == 0)) {
            animeState_set(&arg0->unk_000[i], 0);
            arg0->unk_100[i].unk_0 = (rand() % 20) - 10;
            arg0->unk_100[i].unk_4 = (rand() % 20) - 10;
        }
    }

    arg0->unk_120 = MIN_ALT(arg0->unk_120 + 1, 0xB4);
}

void animeSmog_draw(struct_800F3E50_unk_50C *arg0, Gfx **gfxP, f32 arg2, f32 arg3, f32 arg4, f32 arg5) {
    Gfx *gfx = *gfxP;
    u32 i;

    for (i = 0; i < ARRAY_COUNT(arg0->unk_000); i++) {
        animeState_initIntensityDL(&arg0->unk_000[i], &gfx);

        if (!func_8005E4E0(&arg0->unk_000[i])) {
            func_8005E998(&arg0->unk_000[i], &gfx, arg2 + arg0->unk_100[i].unk_0 * arg4, arg3 + arg0->unk_100[i].unk_4 * arg5, arg4, arg5);
        }
    }

    *gfxP = gfx;
}

INCLUDE_ASM("asm/nonmatchings/main_segment/char_anime", func_8005EE64);

INCLUDE_ASM("asm/nonmatchings/main_segment/char_anime", loadAnimeSeq);

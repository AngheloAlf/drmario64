/**
 * Original filename char_anime.c
 */

#include "char_anime.h"

#include "ultra64.h"
#include "include_asm.h"
#include "macros_defines.h"
#include "unknown_structs.h"
#include "main_segment_functions.h"
#include "main_segment_variables.h"
#include "boot_functions.h"
#include "boot_variables.h"
#include "rom_offsets.h"
#include "segment_symbols.h"

/**
 * Original name: static _size
 */
const size_t RO_800B1A60[] = {
    SEGMENT_DATA_SIZE_CONST(segment_anime_m),
    SEGMENT_DATA_SIZE_CONST(segment_anime_n),
    SEGMENT_DATA_SIZE_CONST(segment_anime_h),
    SEGMENT_DATA_SIZE_CONST(segment_anime_i),
    SEGMENT_DATA_SIZE_CONST(segment_anime_j),
    SEGMENT_DATA_SIZE_CONST(segment_anime_d),
    SEGMENT_DATA_SIZE_CONST(segment_anime_e),
    SEGMENT_DATA_SIZE_CONST(segment_anime_f),
    SEGMENT_DATA_SIZE_CONST(segment_anime_a),
    SEGMENT_DATA_SIZE_CONST(segment_anime_b),
    SEGMENT_DATA_SIZE_CONST(segment_anime_c),
    SEGMENT_DATA_SIZE_CONST(segment_anime_g),
    SEGMENT_DATA_SIZE_CONST(segment_anime_k),
    SEGMENT_DATA_SIZE_CONST(segment_anime_l),
    SEGMENT_DATA_SIZE_CONST(segment_anime_o),
    SEGMENT_DATA_SIZE_CONST(segment_anime_mario),
    SEGMENT_DATA_SIZE_CONST(segment_anime_virus_r),
    SEGMENT_DATA_SIZE_CONST(segment_anime_virus_y),
    SEGMENT_DATA_SIZE_CONST(segment_anime_virus_b),
    SEGMENT_DATA_SIZE_CONST(segment_anime_smog),
};

/**
 * Original name: static _addrTbl
 */
const RomDataTblIndex RO_800B1AB0[] = {
    ROMDATATBL_ANIME_M,
    ROMDATATBL_ANIME_N,
    ROMDATATBL_ANIME_H,
    ROMDATATBL_ANIME_I,
    ROMDATATBL_ANIME_J,
    ROMDATATBL_ANIME_D,
    ROMDATATBL_ANIME_E,
    ROMDATATBL_ANIME_F,
    ROMDATATBL_ANIME_A,
    ROMDATATBL_ANIME_B,
    ROMDATATBL_ANIME_C,
    ROMDATATBL_ANIME_G,
    ROMDATATBL_ANIME_K,
    ROMDATATBL_ANIME_L,
    ROMDATATBL_ANIME_O,
    ROMDATATBL_ANIME_MARIO,
    ROMDATATBL_ANIME_VIRUS_R,
    ROMDATATBL_ANIME_VIRUS_Y,
    ROMDATATBL_ANIME_VIRUS_B,
    ROMDATATBL_ANIME_SMOG,
};

/**
 * Original name: static _centerTbl
 */
const struct_800B1B00 RO_800B1B00[] = {
    { 0x10, 0x2B },
    { 0x19, 0x2C },
    { 0x10, 0x29 },
    { 0x16, 0x28 },
    { 0x1A, 0x33 },
    { 0x18, 0x28 },
    { 0x18, 0x32 },
    { 0x13, 0x28 },
    { 0x20, 0x32 },
    { 0x12, 0x2F },
    { 0x20, 0x3E },
    { 0x23, 0x3C },
    { 0x14, 0x2F },
    { 0x1E, 0x31 },
    { 0x10, 0x2B },
    { 0x20, 0x40 },
    { 0x10, 0x10 },
    { 0x10, 0x10 },
    { 0x10, 0x10 },
    { 0x10, 0x10 },
};

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

void animeSeq_update(struct_800F3E50_unk_44C *arg0, s32 arg1) {
    u8 *temp_a1;

    while (arg1 >= 0) {
        temp_a1 = &arg0->unk_0C[arg0->unk_10].unk_0[arg0->unk_14];

        switch (temp_a1[0]) {
            case 0xF0:
                arg0->unk_14 += 2;
                arg0->unk_08++;
                arg0->unk_00[arg0->unk_08] = arg0->unk_14;
                arg0->unk_04[arg0->unk_08] = temp_a1[1];
                break;

            case 0xF1:
                if (arg0->unk_04[arg0->unk_08] != 0xFF) {
                    arg0->unk_04[arg0->unk_08]--;
                }

                if ((arg0->unk_04[arg0->unk_08] != 0) && (temp_a1[1] > (rand() % 100))) {
                    arg0->unk_14 = arg0->unk_00[arg0->unk_08];
                } else {
                    arg0->unk_14 += 2;
                    arg0->unk_08--;
                }
                break;

            case 0xF2:
                arg0->unk_14 = 0;
                arg0->unk_10 = temp_a1[1];
                arg0->unk_08 = -1;
                break;

            case 0xFF:
                arg1 = -1;
                break;

            default:
                if (arg1 > 0) {
                    arg0->unk_14++;
                }
                arg1--;
                arg0->unk_18 = temp_a1[0] - 1;
                break;
        }
    }
}

bool animeSeq_isEnd(struct_800F3E50_unk_44C *arg0) {
    return arg0->unk_0C[arg0->unk_10].unk_0[arg0->unk_14] == 0xFF;
}

size_t animeState_getDataSize(s32 arg0) {
    return RO_800B1A60[arg0];
}

void animeState_load(struct_800F3E50_unk_44C *arg0, UNK_PTR *arg1, s32 arg2) {
    struct_800F3E50_unk_44C_unk_1C *sp18;
    struct_800F3E50_unk_44C_unk_0C *sp1C;
    RomDataTblIndex index = RO_800B1AB0[arg2];

    loadAnimeSeq(arg1, &sp18, &sp1C, _romDataTbl[index].start, _romDataTbl[index].end);
    animeState_init(arg0, sp1C, sp18, RO_800B1B00[arg2].unk_0, RO_800B1B00[arg2].unk_4, arg2);
}

void animeState_init(struct_800F3E50_unk_44C *arg0, struct_800F3E50_unk_44C_unk_0C *arg1,
                     struct_800F3E50_unk_44C_unk_1C *arg2, UNK_TYPE4 arg3, UNK_TYPE4 arg4, UNK_TYPE4 arg5) {
    animeSeq_init(arg0, arg1, 0);
    arg0->unk_1C = arg2;
    arg0->unk_20 = 0;
    arg0->unk_24.unk_0 = arg3;
    arg0->unk_30 = 0xFF;
    arg0->unk_34 = 0xFF;
    arg0->unk_38 = 0xFF;
    arg0->unk_3C = 0xFF;
    arg0->unk_24.unk_4 = arg4;
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

void animeState_initDL(struct_800F3E50_unk_44C *arg0, Gfx **gfxP) {
    Gfx *gfx = *gfxP;

    gSPDisplayList(gfx++, normal_texture_init_dl);
    gDPSetCombineMode(gfx++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
    gDPSetPrimColor(gfx++, 0, 0, arg0->unk_30, arg0->unk_34, arg0->unk_38, arg0->unk_3C);

    if (arg0->unk_3C < 0xFF) {
        gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    }

    *gfxP = gfx;
}

void animeState_initDL2(struct_800F3E50_unk_44C *arg0, Gfx **gfxP) {
    Gfx *gfx = *gfxP;

    gSPDisplayList(gfx++, normal_texture_init_dl);
    gDPSetCombineLERP(gfx++, TEXEL0, ENVIRONMENT, PRIMITIVE, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, TEXEL0, ENVIRONMENT,
                      PRIMITIVE, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0);
    gDPSetPrimColor(gfx++, 0, 0, arg0->unk_30, arg0->unk_34, arg0->unk_38, arg0->unk_3C);
    gDPSetEnvColor(gfx++, 0, 0, 0, 255);
    if (arg0->unk_3C < 0xFF) {
        gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    }
    *gfxP = gfx;
}

void animeState_initIntensityDL(struct_800F3E50_unk_44C *arg0, Gfx **gfxP) {
    Gfx *gfx = *gfxP;

    gSPDisplayList(gfx++, normal_texture_init_dl);
    gDPSetTextureLUT(gfx++, G_TT_NONE);
    gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gDPSetCombineLERP(gfx++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, PRIMITIVE,
                      ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0);
    gDPSetPrimColor(gfx++, 0, 0, arg0->unk_30, arg0->unk_34, arg0->unk_38, arg0->unk_3C);
    gDPSetEnvColor(gfx++, 0, 0, 0, 255);

    *gfxP = gfx;
}

INCLUDE_ASM("asm/nonmatchings/main_segment/char_anime", animeState_draw);

#ifdef NON_MATCHING
// float regalloc
void func_8005E998(struct_800F3E50_unk_44C *arg0, Gfx **gfxP, f32 arg2, f32 arg3, f32 arg4, f32 arg5) {
    Gfx *gfx = *gfxP;

    if (arg0->unk_18 >= 0) {
        f32 var_f0;
        f32 var_f0_2;
        struct_800F3E50_unk_44C_unk_1C *temp_a3 = &arg0->unk_1C[arg0->unk_18];

        if (arg4 < 0.0f) {
            var_f0 = arg2 - (arg0->unk_24.unk_0 - temp_a3->unk_4->unk_0) * arg4;
        } else {
            var_f0 = arg2 - arg0->unk_24.unk_0 * arg4;
        }
        if (arg5 < 0.0f) {
            var_f0_2 = arg3 - (arg0->unk_24.unk_4 - temp_a3->unk_4->unk_2) * arg5;
        } else {
            var_f0_2 = arg3 - arg0->unk_24.unk_4 * arg5;
        }
        func_80044E08(&gfx, temp_a3->unk_4->unk_0, temp_a3->unk_4->unk_2, temp_a3->unk_0->unk_4, 0, 0,
                      temp_a3->unk_4->unk_0, temp_a3->unk_4->unk_2, var_f0, var_f0_2, temp_a3->unk_4->unk_0 * arg4,
                      temp_a3->unk_4->unk_2 * arg5);
        *gfxP = gfx;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/main_segment/char_anime", func_8005E998);
#endif

void animeSmog_init(struct_800F3E50_unk_50C *arg0, struct_800F3E50_unk_50C *arg1) {
    s32 i;

    for (i = 0; i < ARRAY_COUNTU(arg0->unk_000); i++) {
        animeState_init(&arg0->unk_000[i], arg1->unk_000[0].unk_0C, arg1->unk_000[0].unk_1C, arg1->unk_000[0].unk_24.unk_0,
                        arg1->unk_000[0].unk_24.unk_4, 19);
        animeState_set(&arg0->unk_000[i], 2);
        arg0->unk_100[i].unk_4 = 0;
        arg0->unk_100[i].unk_0 = 0;
    }
    arg0->unk_120 = 0xB4;
}

void animeSmog_load(struct_800F3E50_unk_50C *arg0, UNK_PTR *arg1) {
    animeState_load(arg0->unk_000, arg1, 19);
    animeSmog_init(arg0, arg0);
}

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
            func_8005E998(&arg0->unk_000[i], &gfx, arg2 + arg0->unk_100[i].unk_0 * arg4,
                          arg3 + arg0->unk_100[i].unk_4 * arg5, arg4, arg5);
        }
    }

    *gfxP = gfx;
}

INCLUDE_ASM("asm/nonmatchings/main_segment/char_anime", func_8005EE64);

INCLUDE_ASM("asm/nonmatchings/main_segment/char_anime", loadAnimeSeq);

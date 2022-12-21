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
    SEGMENT_DATA_SIZE_CONST(segment_anime_m),       SEGMENT_DATA_SIZE_CONST(segment_anime_n),
    SEGMENT_DATA_SIZE_CONST(segment_anime_h),       SEGMENT_DATA_SIZE_CONST(segment_anime_i),
    SEGMENT_DATA_SIZE_CONST(segment_anime_j),       SEGMENT_DATA_SIZE_CONST(segment_anime_d),
    SEGMENT_DATA_SIZE_CONST(segment_anime_e),       SEGMENT_DATA_SIZE_CONST(segment_anime_f),
    SEGMENT_DATA_SIZE_CONST(segment_anime_a),       SEGMENT_DATA_SIZE_CONST(segment_anime_b),
    SEGMENT_DATA_SIZE_CONST(segment_anime_c),       SEGMENT_DATA_SIZE_CONST(segment_anime_g),
    SEGMENT_DATA_SIZE_CONST(segment_anime_k),       SEGMENT_DATA_SIZE_CONST(segment_anime_l),
    SEGMENT_DATA_SIZE_CONST(segment_anime_o),       SEGMENT_DATA_SIZE_CONST(segment_anime_mario),
    SEGMENT_DATA_SIZE_CONST(segment_anime_virus_r), SEGMENT_DATA_SIZE_CONST(segment_anime_virus_y),
    SEGMENT_DATA_SIZE_CONST(segment_anime_virus_b), SEGMENT_DATA_SIZE_CONST(segment_anime_smog),
};

/**
 * Original name: static _addrTbl
 */
const RomDataTblIndex RO_800B1AB0[] = {
    ROMDATATBL_ANIME_M,       ROMDATATBL_ANIME_N,       ROMDATATBL_ANIME_H,       ROMDATATBL_ANIME_I,
    ROMDATATBL_ANIME_J,       ROMDATATBL_ANIME_D,       ROMDATATBL_ANIME_E,       ROMDATATBL_ANIME_F,
    ROMDATATBL_ANIME_A,       ROMDATATBL_ANIME_B,       ROMDATATBL_ANIME_C,       ROMDATATBL_ANIME_G,
    ROMDATATBL_ANIME_K,       ROMDATATBL_ANIME_L,       ROMDATATBL_ANIME_O,       ROMDATATBL_ANIME_MARIO,
    ROMDATATBL_ANIME_VIRUS_R, ROMDATATBL_ANIME_VIRUS_Y, ROMDATATBL_ANIME_VIRUS_B, ROMDATATBL_ANIME_SMOG,
};

/**
 * Original name: static _centerTbl
 */
const struct_800B1B00 RO_800B1B00[] = {
    { 0x10, 0x2B }, { 0x19, 0x2C }, { 0x10, 0x29 }, { 0x16, 0x28 }, { 0x1A, 0x33 }, { 0x18, 0x28 }, { 0x18, 0x32 },
    { 0x13, 0x28 }, { 0x20, 0x32 }, { 0x12, 0x2F }, { 0x20, 0x3E }, { 0x23, 0x3C }, { 0x14, 0x2F }, { 0x1E, 0x31 },
    { 0x10, 0x2B }, { 0x20, 0x40 }, { 0x10, 0x10 }, { 0x10, 0x10 }, { 0x10, 0x10 }, { 0x10, 0x10 },
};

/**
 * Original name: animeSeq_init
 */
void animeSeq_init(AnimeSeq *animeSeq, AnimeSeq_unk_0C *arg1, UNK_TYPE4 arg2) {
    animeSeq->unk_0C = arg1;
    animeSeq->unk_08 = -1;
    animeSeq->unk_10 = arg2;
    animeSeq->unk_14 = 0;
    animeSeq->unk_18 = -1;
    animeSeq_update(animeSeq, 0);
}

void func_8005E154(AnimeState *animeState, UNK_TYPE4 arg1) {
    animeSeq_init(&animeState->animeSeq, animeState->animeSeq.unk_0C, arg1);
}

/**
 * Original name: animeSeq_update
 */
void animeSeq_update(AnimeSeq *animeSeq, s32 arg1) {
    u8 *temp_a1;

    while (arg1 >= 0) {
        temp_a1 = &animeSeq->unk_0C[animeSeq->unk_10].unk_0[animeSeq->unk_14];

        switch (temp_a1[0]) {
            case 0xF0:
                animeSeq->unk_14 += 2;
                animeSeq->unk_08++;
                animeSeq->unk_00[animeSeq->unk_08] = animeSeq->unk_14;
                animeSeq->unk_04[animeSeq->unk_08] = temp_a1[1];
                break;

            case 0xF1:
                if (animeSeq->unk_04[animeSeq->unk_08] != 0xFF) {
                    animeSeq->unk_04[animeSeq->unk_08]--;
                }

                if ((animeSeq->unk_04[animeSeq->unk_08] != 0) && (temp_a1[1] > (rand() % 100))) {
                    animeSeq->unk_14 = animeSeq->unk_00[animeSeq->unk_08];
                } else {
                    animeSeq->unk_14 += 2;
                    animeSeq->unk_08--;
                }
                break;

            case 0xF2:
                animeSeq->unk_14 = 0;
                animeSeq->unk_10 = temp_a1[1];
                animeSeq->unk_08 = -1;
                break;

            case 0xFF:
                arg1 = -1;
                break;

            default:
                if (arg1 > 0) {
                    animeSeq->unk_14++;
                }
                arg1--;
                animeSeq->unk_18 = temp_a1[0] - 1;
                break;
        }
    }
}

/**
 * Original name: animeSeq_isEnd
 */
bool animeSeq_isEnd(AnimeSeq *animeSeq) {
    return animeSeq->unk_0C[animeSeq->unk_10].unk_0[animeSeq->unk_14] == 0xFF;
}

/**
 * Original name: animeState_getDataSize
 */
size_t animeState_getDataSize(s32 arg0) {
    return RO_800B1A60[arg0];
}

/**
 * Original name: animeState_load
 */
void animeState_load(AnimeState *animeState, UNK_PTR *arg1, s32 arg2) {
    AnimeState_unk_1C *sp18;
    AnimeSeq_unk_0C *sp1C;
    RomDataTblIndex index = RO_800B1AB0[arg2];

    loadAnimeSeq(arg1, &sp18, &sp1C, _romDataTbl[index].start, _romDataTbl[index].end);
    animeState_init(animeState, sp1C, sp18, RO_800B1B00[arg2].unk_0, RO_800B1B00[arg2].unk_4, arg2);
}

/**
 * Original name: animeState_init
 */
void animeState_init(AnimeState *animeState, AnimeSeq_unk_0C *arg1, AnimeState_unk_1C *arg2, UNK_TYPE4 arg3,
                     UNK_TYPE4 arg4, UNK_TYPE4 arg5) {
    animeSeq_init(&animeState->animeSeq, arg1, 0);
    animeState->unk_1C = arg2;
    animeState->unk_20 = 0;
    animeState->unk_24.unk_0 = arg3;
    animeState->unk_30 = 0xFF;
    animeState->unk_34 = 0xFF;
    animeState->unk_38 = 0xFF;
    animeState->unk_3C = 0xFF;
    animeState->unk_24.unk_4 = arg4;
    animeState->unk_2C = arg5;
}

/**
 * Original name: animeState_set
 */
void animeState_set(AnimeState *animeState, UNK_TYPE4 arg1) {
    animeState->unk_20 = 0;
    func_8005E154(animeState, arg1);
}

/**
 * Original name: animeState_update
 */
void animeState_update(AnimeState *animeState) {
    animeSeq_update(&animeState->animeSeq, animeState->unk_20 % 2U);
    animeState->unk_20++;
}

bool func_8005E4E0(AnimeState *animeState) {
    return animeSeq_isEnd(&animeState->animeSeq);
}

/**
 * Original name: animeState_initDL
 */
void animeState_initDL(AnimeState *animeState, Gfx **gfxP) {
    Gfx *gfx = *gfxP;

    gSPDisplayList(gfx++, normal_texture_init_dl);
    gDPSetCombineMode(gfx++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
    gDPSetPrimColor(gfx++, 0, 0, animeState->unk_30, animeState->unk_34, animeState->unk_38, animeState->unk_3C);

    if (animeState->unk_3C < 0xFF) {
        gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    }

    *gfxP = gfx;
}

/**
 * Original name: animeState_initDL2
 */
void animeState_initDL2(AnimeState *animeState, Gfx **gfxP) {
    Gfx *gfx = *gfxP;

    gSPDisplayList(gfx++, normal_texture_init_dl);
    gDPSetCombineLERP(gfx++, TEXEL0, ENVIRONMENT, PRIMITIVE, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, TEXEL0, ENVIRONMENT,
                      PRIMITIVE, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0);
    gDPSetPrimColor(gfx++, 0, 0, animeState->unk_30, animeState->unk_34, animeState->unk_38, animeState->unk_3C);
    gDPSetEnvColor(gfx++, 0, 0, 0, 255);
    if (animeState->unk_3C < 0xFF) {
        gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    }
    *gfxP = gfx;
}

/**
 * Original name: animeState_initIntensityDL
 */
void animeState_initIntensityDL(AnimeState *animeState, Gfx **gfxP) {
    Gfx *gfx = *gfxP;

    gSPDisplayList(gfx++, normal_texture_init_dl);
    gDPSetTextureLUT(gfx++, G_TT_NONE);
    gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gDPSetCombineLERP(gfx++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, PRIMITIVE,
                      ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0);
    gDPSetPrimColor(gfx++, 0, 0, animeState->unk_30, animeState->unk_34, animeState->unk_38, animeState->unk_3C);
    gDPSetEnvColor(gfx++, 0, 0, 0, 255);

    *gfxP = gfx;
}

/**
 * Original name: animeState_draw
 */
INCLUDE_ASM("asm/nonmatchings/main_segment/char_anime", animeState_draw);

#ifdef NON_MATCHING
// float regalloc
void func_8005E998(AnimeState *animeState, Gfx **gfxP, f32 arg2, f32 arg3, f32 arg4, f32 arg5) {
    Gfx *gfx = *gfxP;

    if (animeState->animeSeq.unk_18 >= 0) {
        f32 var_f0;
        f32 var_f0_2;
        AnimeState_unk_1C *temp_a3 = &animeState->unk_1C[animeState->animeSeq.unk_18];

        if (arg4 < 0.0f) {
            var_f0 = arg2 - (animeState->unk_24.unk_0 - temp_a3->unk_4->unk_0) * arg4;
        } else {
            var_f0 = arg2 - animeState->unk_24.unk_0 * arg4;
        }
        if (arg5 < 0.0f) {
            var_f0_2 = arg3 - (animeState->unk_24.unk_4 - temp_a3->unk_4->unk_2) * arg5;
        } else {
            var_f0_2 = arg3 - animeState->unk_24.unk_4 * arg5;
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

/**
 * Original name: animeSmog_init
 */
void animeSmog_init(AnimeSmog *animeSmog, AnimeSmog *orig) {
    s32 i;

    for (i = 0; i < ARRAY_COUNTU(animeSmog->unk_000); i++) {
        animeState_init(&animeSmog->unk_000[i], orig->unk_000[0].animeSeq.unk_0C, orig->unk_000[0].unk_1C,
                        orig->unk_000[0].unk_24.unk_0, orig->unk_000[0].unk_24.unk_4, 19);
        animeState_set(&animeSmog->unk_000[i], 2);
        animeSmog->unk_100[i].unk_4 = 0;
        animeSmog->unk_100[i].unk_0 = 0;
    }
    animeSmog->unk_120 = 0xB4;
}

/**
 * Original name: animeSmog_load
 */
void animeSmog_load(AnimeSmog *animeSmog, UNK_PTR *arg1) {
    animeState_load(animeSmog->unk_000, arg1, 19);
    animeSmog_init(animeSmog, animeSmog);
}

/**
 * Original name: animeSmog_start
 */
void animeSmog_start(AnimeSmog *animeSmog) {
    animeSmog->unk_120 = 0;
}

/**
 * Original name: animeSmog_stop
 */
void animeSmog_stop(AnimeSmog *animeSmog) {
    u32 i;

    for (i = 0; i < ARRAY_COUNT(animeSmog->unk_000); i++) {
        animeState_set(&animeSmog->unk_000[i], 2);
    }

    animeSmog->unk_120 = 0xB4;
}

/**
 * Original name: animeSmog_update
 */
void animeSmog_update(AnimeSmog *animeSmog) {
    u32 i;

    for (i = 0; i < 4; i++) {
        animeState_update(&animeSmog->unk_000[i]);
        if ((animeSmog->unk_120 < 0xB4) && func_8005E4E0(&animeSmog->unk_000[i]) && (rand() % 16 == 0)) {
            animeState_set(&animeSmog->unk_000[i], 0);
            animeSmog->unk_100[i].unk_0 = (rand() % 20) - 10;
            animeSmog->unk_100[i].unk_4 = (rand() % 20) - 10;
        }
    }

    animeSmog->unk_120 = MIN_ALT(animeSmog->unk_120 + 1, 0xB4);
}

/**
 * Original name: animeSmog_draw
 */
void animeSmog_draw(AnimeSmog *animeSmog, Gfx **gfxP, f32 arg2, f32 arg3, f32 arg4, f32 arg5) {
    Gfx *gfx = *gfxP;
    u32 i;

    for (i = 0; i < ARRAY_COUNT(animeSmog->unk_000); i++) {
        animeState_initIntensityDL(&animeSmog->unk_000[i], &gfx);

        if (!func_8005E4E0(&animeSmog->unk_000[i])) {
            func_8005E998(&animeSmog->unk_000[i], &gfx, arg2 + animeSmog->unk_100[i].unk_0 * arg4,
                          arg3 + animeSmog->unk_100[i].unk_4 * arg5, arg4, arg5);
        }
    }

    *gfxP = gfx;
}

INCLUDE_ASM("asm/nonmatchings/main_segment/char_anime", func_8005EE64);

/**
 * Original name: loadAnimeSeq
 */
INCLUDE_ASM("asm/nonmatchings/main_segment/char_anime", loadAnimeSeq);

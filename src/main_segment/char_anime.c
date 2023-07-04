/**
 * Original filename char_anime.c
 */

#include "char_anime.h"

#include "libultra.h"
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
const size_t _size_122[CHARANIMEMODE_MAX] = {
    SEGMENT_DATA_SIZE_CONST(segment_anime_m),       // CHARANIMEMODE_M
    SEGMENT_DATA_SIZE_CONST(segment_anime_n),       // CHARANIMEMODE_N
    SEGMENT_DATA_SIZE_CONST(segment_anime_h),       // CHARANIMEMODE_H
    SEGMENT_DATA_SIZE_CONST(segment_anime_i),       // CHARANIMEMODE_I
    SEGMENT_DATA_SIZE_CONST(segment_anime_j),       // CHARANIMEMODE_J
    SEGMENT_DATA_SIZE_CONST(segment_anime_d),       // CHARANIMEMODE_D
    SEGMENT_DATA_SIZE_CONST(segment_anime_e),       // CHARANIMEMODE_E
    SEGMENT_DATA_SIZE_CONST(segment_anime_f),       // CHARANIMEMODE_F
    SEGMENT_DATA_SIZE_CONST(segment_anime_a),       // CHARANIMEMODE_A
    SEGMENT_DATA_SIZE_CONST(segment_anime_b),       // CHARANIMEMODE_B
    SEGMENT_DATA_SIZE_CONST(segment_anime_c),       // CHARANIMEMODE_C
    SEGMENT_DATA_SIZE_CONST(segment_anime_g),       // CHARANIMEMODE_G
    SEGMENT_DATA_SIZE_CONST(segment_anime_k),       // CHARANIMEMODE_K
    SEGMENT_DATA_SIZE_CONST(segment_anime_l),       // CHARANIMEMODE_L
    SEGMENT_DATA_SIZE_CONST(segment_anime_o),       // CHARANIMEMODE_O
    SEGMENT_DATA_SIZE_CONST(segment_anime_mario),   // CHARANIMEMODE_MARIO
    SEGMENT_DATA_SIZE_CONST(segment_anime_virus_r), // CHARANIMEMODE_VIRUS_R
    SEGMENT_DATA_SIZE_CONST(segment_anime_virus_y), // CHARANIMEMODE_VIRUS_Y
    SEGMENT_DATA_SIZE_CONST(segment_anime_virus_b), // CHARANIMEMODE_VIRUS_B
    SEGMENT_DATA_SIZE_CONST(segment_anime_smog),    // CHARANIMEMODE_SMOG
};

/**
 * Original name: static _addrTbl
 */
const RomDataTblIndex _addrTbl_124[CHARANIMEMODE_MAX] = {
    ROMDATATBL_ANIME_M,       // CHARANIMEMODE_M
    ROMDATATBL_ANIME_N,       // CHARANIMEMODE_N
    ROMDATATBL_ANIME_H,       // CHARANIMEMODE_H
    ROMDATATBL_ANIME_I,       // CHARANIMEMODE_I
    ROMDATATBL_ANIME_J,       // CHARANIMEMODE_J
    ROMDATATBL_ANIME_D,       // CHARANIMEMODE_D
    ROMDATATBL_ANIME_E,       // CHARANIMEMODE_E
    ROMDATATBL_ANIME_F,       // CHARANIMEMODE_F
    ROMDATATBL_ANIME_A,       // CHARANIMEMODE_A
    ROMDATATBL_ANIME_B,       // CHARANIMEMODE_B
    ROMDATATBL_ANIME_C,       // CHARANIMEMODE_C
    ROMDATATBL_ANIME_G,       // CHARANIMEMODE_G
    ROMDATATBL_ANIME_K,       // CHARANIMEMODE_K
    ROMDATATBL_ANIME_L,       // CHARANIMEMODE_L
    ROMDATATBL_ANIME_O,       // CHARANIMEMODE_O
    ROMDATATBL_ANIME_MARIO,   // CHARANIMEMODE_MARIO
    ROMDATATBL_ANIME_VIRUS_R, // CHARANIMEMODE_VIRUS_R
    ROMDATATBL_ANIME_VIRUS_Y, // CHARANIMEMODE_VIRUS_Y
    ROMDATATBL_ANIME_VIRUS_B, // CHARANIMEMODE_VIRUS_B
    ROMDATATBL_ANIME_SMOG,    // CHARANIMEMODE_SMOG
};

/**
 * Original name: static _centerTbl
 */
const struct_800B1B00 _centerTbl_125[CHARANIMEMODE_MAX] = {
    { 0x10, 0x2B }, // CHARANIMEMODE_M
    { 0x19, 0x2C }, // CHARANIMEMODE_N
    { 0x10, 0x29 }, // CHARANIMEMODE_H
    { 0x16, 0x28 }, // CHARANIMEMODE_I
    { 0x1A, 0x33 }, // CHARANIMEMODE_J
    { 0x18, 0x28 }, // CHARANIMEMODE_D
    { 0x18, 0x32 }, // CHARANIMEMODE_E
    { 0x13, 0x28 }, // CHARANIMEMODE_F
    { 0x20, 0x32 }, // CHARANIMEMODE_A
    { 0x12, 0x2F }, // CHARANIMEMODE_B
    { 0x20, 0x3E }, // CHARANIMEMODE_C
    { 0x23, 0x3C }, // CHARANIMEMODE_G
    { 0x14, 0x2F }, // CHARANIMEMODE_K
    { 0x1E, 0x31 }, // CHARANIMEMODE_L
    { 0x10, 0x2B }, // CHARANIMEMODE_O
    { 0x20, 0x40 }, // CHARANIMEMODE_MARIO
    { 0x10, 0x10 }, // CHARANIMEMODE_VIRUS_R
    { 0x10, 0x10 }, // CHARANIMEMODE_VIRUS_Y
    { 0x10, 0x10 }, // CHARANIMEMODE_VIRUS_B
    { 0x10, 0x10 }, // CHARANIMEMODE_SMOG
};

/**
 * Original name: animeSeq_init
 */
#if VERSION_US
void animeSeq_init(AnimeSeq *animeSeq, AnimeSeq_unk_0C *arg1, UNK_TYPE4 arg2) {
    animeSeq->unk_0C = arg1;
    animeSeq->unk_08 = -1;
    animeSeq->unk_10 = arg2;
    animeSeq->unk_14 = 0;
    animeSeq->unk_18 = -1;
    animeSeq_update(animeSeq, 0);
}
#endif

#if VERSION_US
void func_8005E154(AnimeState *animeState, UNK_TYPE4 arg1) {
    animeSeq_init(&animeState->animeSeq, animeState->animeSeq.unk_0C, arg1);
}
#endif

/**
 * Original name: animeSeq_update
 */
#if VERSION_US
void animeSeq_update(AnimeSeq *animeSeq, s32 arg1) {

    while (arg1 >= 0) {
        u8 *temp_a1 = &animeSeq->unk_0C[animeSeq->unk_10].unk_0[animeSeq->unk_14];

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
#endif

/**
 * Original name: animeSeq_isEnd
 */
#if VERSION_US
bool animeSeq_isEnd(AnimeSeq *animeSeq) {
    return animeSeq->unk_0C[animeSeq->unk_10].unk_0[animeSeq->unk_14] == 0xFF;
}
#endif

/**
 * Original name: animeState_getDataSize
 */
#if VERSION_US
size_t animeState_getDataSize(CharAnimeMode animeMode) {
    return _size_122[animeMode];
}
#endif

/**
 * Original name: animeState_load
 */
#if VERSION_US
void animeState_load(AnimeState *animeState, UNK_PTR *arg1, CharAnimeMode animeMode) {
    AnimeState_unk_1C *sp18;
    AnimeSeq_unk_0C *sp1C;
    RomDataTblIndex index = _addrTbl_124[animeMode];

    loadAnimeSeq(arg1, &sp18, &sp1C, _romDataTbl[index].start, _romDataTbl[index].end);
    animeState_init(animeState, sp1C, sp18, _centerTbl_125[animeMode].unk_0, _centerTbl_125[animeMode].unk_4,
                    animeMode);
}
#endif

/**
 * Original name: animeState_init
 */
#if VERSION_US
void animeState_init(AnimeState *animeState, AnimeSeq_unk_0C *arg1, AnimeState_unk_1C *arg2, UNK_TYPE4 arg3,
                     UNK_TYPE4 arg4, CharAnimeMode animeMode) {
    animeSeq_init(&animeState->animeSeq, arg1, 0);
    animeState->unk_1C = arg2;
    animeState->unk_20 = 0;
    animeState->unk_24.unk_0 = arg3;
    animeState->unk_24.unk_4 = arg4;
    animeState->animeMode = animeMode;
    animeState->primColorR = 255;
    animeState->primColorG = 255;
    animeState->primColorB = 255;
    animeState->primColorA = 255;
}
#endif

/**
 * Original name: animeState_set
 */
#if VERSION_US
void animeState_set(AnimeState *animeState, UNK_TYPE4 arg1) {
    animeState->unk_20 = 0;
    func_8005E154(animeState, arg1);
}
#endif

/**
 * Original name: animeState_update
 */
#if VERSION_US
void animeState_update(AnimeState *animeState) {
    animeSeq_update(&animeState->animeSeq, animeState->unk_20 % 2U);
    animeState->unk_20++;
}
#endif

#if VERSION_US
bool animeState_isEnd(AnimeState *animeState) {
    return animeSeq_isEnd(&animeState->animeSeq);
}
#endif

/**
 * Original name: animeState_initDL
 */
#if VERSION_US
void animeState_initDL(AnimeState *animeState, Gfx **gfxP) {
    Gfx *gfx = *gfxP;

    gSPDisplayList(gfx++, normal_texture_init_dl);
    gDPSetCombineMode(gfx++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
    gDPSetPrimColor(gfx++, 0, 0, animeState->primColorR, animeState->primColorG, animeState->primColorB,
                    animeState->primColorA);

    if (animeState->primColorA < 255) {
        gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    }

    *gfxP = gfx;
}
#endif

/**
 * Original name: animeState_initDL2
 */
#if VERSION_US
void animeState_initDL2(AnimeState *animeState, Gfx **gfxP) {
    Gfx *gfx = *gfxP;

    gSPDisplayList(gfx++, normal_texture_init_dl);
    gDPSetCombineLERP(gfx++, TEXEL0, ENVIRONMENT, PRIMITIVE, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, TEXEL0, ENVIRONMENT,
                      PRIMITIVE, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0);
    gDPSetPrimColor(gfx++, 0, 0, animeState->primColorR, animeState->primColorG, animeState->primColorB,
                    animeState->primColorA);
    gDPSetEnvColor(gfx++, 0, 0, 0, 255);
    if (animeState->primColorA < 255) {
        gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    }
    *gfxP = gfx;
}
#endif

/**
 * Original name: animeState_initIntensityDL
 */
#if VERSION_US
void animeState_initIntensityDL(AnimeState *animeState, Gfx **gfxP) {
    Gfx *gfx = *gfxP;

    gSPDisplayList(gfx++, normal_texture_init_dl);
    gDPSetTextureLUT(gfx++, G_TT_NONE);
    gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gDPSetCombineLERP(gfx++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, PRIMITIVE,
                      ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0);
    gDPSetPrimColor(gfx++, 0, 0, animeState->primColorR, animeState->primColorG, animeState->primColorB,
                    animeState->primColorA);
    gDPSetEnvColor(gfx++, 0, 0, 0, 255);

    *gfxP = gfx;
}
#endif

/**
 * Original name: animeState_draw
 */
#if VERSION_US
void animeState_draw(AnimeState *animeState, Gfx **gfxP, f32 arg2, f32 arg3, f32 arg4, f32 arg5) {
    Gfx *gfx = *gfxP;
    AnimeState_unk_1C *temp_a3;
    AnimeState_unk_1C *temp_t0;
    f32 temp_ft0;
    f32 var_fv0_2;

    if (animeState->animeSeq.unk_18 < 0) {
        return;
    }

    temp_t0 = animeState->unk_1C;
    temp_a3 = &temp_t0[animeState->animeSeq.unk_18];
    if (arg4 < 0.0f) {
        temp_ft0 = arg2 - (animeState->unk_24.unk_0 - temp_a3->unk_4->unk_0) * arg4;
    } else {
        temp_ft0 = arg2 - animeState->unk_24.unk_0 * arg4;
    }

    if (arg5 < 0.0f) {
        var_fv0_2 = (animeState->unk_24.unk_4 - temp_a3->unk_4->unk_2) * arg5;
    } else {
        var_fv0_2 = animeState->unk_24.unk_4 * arg5;
    }

    arg3 -= var_fv0_2;
    if (animeState->animeMode == CHARANIMEMODE_MARIO) {
        arg3 -= (temp_a3->unk_4->unk_2 - 0x40) * arg5;
    }

    switch (temp_a3->unk_4->unk_4) {
        case 0x4:
            StretchTexTile4(&gfx, temp_a3->unk_4->unk_0, temp_a3->unk_4->unk_2, temp_t0[0].unk_0->unk_0,
                            temp_a3->unk_0->unk_4, 0, 0, temp_a3->unk_4->unk_0, temp_a3->unk_4->unk_2, temp_ft0, arg3,
                            temp_a3->unk_4->unk_0 * arg4, temp_a3->unk_4->unk_2 * arg5);
            break;

        case 0x8:
            StretchTexTile8(&gfx, temp_a3->unk_4->unk_0, temp_a3->unk_4->unk_2, temp_t0[0].unk_0->unk_0,
                            temp_a3->unk_0->unk_4, 0, 0, temp_a3->unk_4->unk_0, temp_a3->unk_4->unk_2, temp_ft0, arg3,
                            temp_a3->unk_4->unk_0 * arg4, temp_a3->unk_4->unk_2 * arg5);
            break;
    }

    *gfxP = gfx;
}
#endif

#if VERSION_US
#ifdef NON_MATCHING
// float regalloc
void StretchTexTile4i(AnimeState *animeState, Gfx **gfxP, f32 arg2, f32 arg3, f32 arg4, f32 arg5) {
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
INCLUDE_ASM("asm/us/nonmatchings/main_segment/char_anime", StretchTexTile4i);
#endif
#endif

/**
 * Original name: animeSmog_init
 */
#if VERSION_US
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
#endif

/**
 * Original name: animeSmog_load
 */
#if VERSION_US
void animeSmog_load(AnimeSmog *animeSmog, UNK_PTR *arg1) {
    animeState_load(animeSmog->unk_000, arg1, CHARANIMEMODE_SMOG);
    animeSmog_init(animeSmog, animeSmog);
}
#endif

/**
 * Original name: animeSmog_start
 */
#if VERSION_US
void animeSmog_start(AnimeSmog *animeSmog) {
    animeSmog->unk_120 = 0;
}
#endif

/**
 * Original name: animeSmog_stop
 */
#if VERSION_US
void animeSmog_stop(AnimeSmog *animeSmog) {
    u32 i;

    for (i = 0; i < ARRAY_COUNT(animeSmog->unk_000); i++) {
        animeState_set(&animeSmog->unk_000[i], 2);
    }

    animeSmog->unk_120 = 0xB4;
}
#endif

/**
 * Original name: animeSmog_update
 */
#if VERSION_US
void animeSmog_update(AnimeSmog *animeSmog) {
    u32 i;

    for (i = 0; i < 4; i++) {
        animeState_update(&animeSmog->unk_000[i]);
        if ((animeSmog->unk_120 < 0xB4) && animeState_isEnd(&animeSmog->unk_000[i]) && (rand() % 16 == 0)) {
            animeState_set(&animeSmog->unk_000[i], 0);
            animeSmog->unk_100[i].unk_0 = (rand() % 20) - 10;
            animeSmog->unk_100[i].unk_4 = (rand() % 20) - 10;
        }
    }

    animeSmog->unk_120 = MIN(0xB4, animeSmog->unk_120 + 1);
}
#endif

/**
 * Original name: animeSmog_draw
 */
#if VERSION_US
void animeSmog_draw(AnimeSmog *animeSmog, Gfx **gfxP, f32 arg2, f32 arg3, f32 arg4, f32 arg5) {
    Gfx *gfx = *gfxP;
    u32 i;

    for (i = 0; i < ARRAY_COUNT(animeSmog->unk_000); i++) {
        animeState_initIntensityDL(&animeSmog->unk_000[i], &gfx);

        if (!animeState_isEnd(&animeSmog->unk_000[i])) {
            StretchTexTile4i(&animeSmog->unk_000[i], &gfx, arg2 + animeSmog->unk_100[i].unk_0 * arg4,
                             arg3 + animeSmog->unk_100[i].unk_4 * arg5, arg4, arg5);
        }
    }

    *gfxP = gfx;
}
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/char_anime", func_8005EE64);
#endif

/**
 * Original name: loadAnimeSeq
 */
#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/char_anime", loadAnimeSeq);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/char_anime", func_800644B0_cn);
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/char_anime", func_800644F4_cn);
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/char_anime", func_80064524_cn);
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/char_anime", func_800646F0_cn);
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/char_anime", func_8006471C_cn);
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/char_anime", animeState_load);
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/char_anime", func_800647F0_cn);
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/char_anime", animeState_set);
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/char_anime", animeState_update);
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/char_anime", func_800648F4_cn);
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/char_anime", func_8006491C_cn);
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/char_anime", func_800649D0_cn);
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/char_anime", func_80064A9C_cn);
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/char_anime", func_80064B8C_cn);
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/char_anime", func_80064DC0_cn);
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/char_anime", animeSmog_init);
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/char_anime", animeSmog_load);
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/char_anime", func_8006503C_cn);
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/char_anime", animeSmog_stop);
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/char_anime", animeSmog_update);
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/char_anime", func_80065230_cn);
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/char_anime", func_80065364_cn);
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/char_anime", func_80065390_cn);
#endif

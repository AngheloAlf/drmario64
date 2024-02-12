/**
 * Original filename: aiset.c
 *
 * List of known original function names:
 * - aifMakeBlkWork
 * - aifMakeFlagSet
 * - aifGameInit
 * - aifFirstInit
 * - aifMake
 * - aifMake2
 * - aiHiruSideLineEraser
 * - aifEraseLineCore
 * - aifRensaCheckCore
 * - aifRensaCheck
 * - aifSearchLineCore
 * - aifMiniPointK3
 * - aifMiniAloneCapNumber
 * - aifMiniAloneCapNumberW
 * - flash_virus
 * - search_Vflash
 * - aifSearchLineMS
 * - aiHiruAllPriSet
 * - aiSetCharacter
 * - aifFieldCopy
 * - aifPlaceSearch
 * - aifMoveCheck
 * - aifTRecur
 * - aifTRecurUP
 * - aifYRecur
 * - aifYRecurUP
 * - aifReMoveCheck
 * - aifKeyMake
 * - aifKeyOut
 * - search_flash_3
 * - flash_special
 * - aiCOM_MissTake
 */

#include "aiset.h"
#include "libultra.h"
#include "include_asm.h"
#include "macros_defines.h"
#include "unknown_structs.h"
#include "boot_functions.h"
#include "boot_variables.h"
#include "main_segment_variables.h"
#include "gamemap.h"
#include "main1x.h"
#include "vr_init.h"

// no original name :c
void func_8002EB00(struct_game_state_data *gameStateDataRef) {
    gameStateDataRef->unk_3BC = gameStateDataRef->unk_178.unk_0[0];
    gameStateDataRef->unk_3BD = gameStateDataRef->unk_178.unk_2[0];
    gameStateDataRef->unk_3C1 = gameStateDataRef->unk_02F;
    gameStateDataRef->unk_3C0 = gameStateDataRef->unk_02D;
    gameStateDataRef->unk_3BE[0] = gameStateDataRef->unk_178.unk_6[0];
    gameStateDataRef->unk_3BE[1] = gameStateDataRef->unk_178.unk_6[1];
    gameStateDataRef->unk_299[2] = gameStateDataRef->unk_025;
    gameStateDataRef->unk_299[1] = gameStateDataRef->unk_026;
    gameStateDataRef->unk_299[0] = gameStateDataRef->unk_014 == 0x12;
    gameStateDataRef->unk_298 = gameStateDataRef->unk_04B;

    if (gameStateDataRef->unk_298 == 0) {
        game_state_data[0].unk_04E = game_state_data[1].unk_04E;
    }
}

/**
 * Original name: aifMakeBlkWork
 */
void aifMakeBlkWork(struct_game_state_data *gameStateDataRef) {
    s32 column;
    s32 row;

    for (column = 0; column < GAME_MAP_COLUMNS; column++) {
        gameStateDataRef->unk_29C[0][column][0] = 10;
        gameStateDataRef->unk_29C[0][column][1] = 3;
    }

    for (row = 1; row < GAME_MAP_ROWS; row++) {
        for (column = 0; column < GAME_MAP_COLUMNS; column++) {
            s32 index = GAME_MAP_GET_INDEX(row - 1, column);

            if (game_map_data[gameStateDataRef->unk_298][index].unk_4[0] != 0) {
                gameStateDataRef->unk_29C[row][column][0] =
                    capsGCnv_122[game_map_data[gameStateDataRef->unk_298][index].unk_2];
                gameStateDataRef->unk_29C[row][column][1] =
                    capsCCnv_123[game_map_data[gameStateDataRef->unk_298][index].unk_3];
            } else {
                gameStateDataRef->unk_29C[row][column][0] = 10;
                gameStateDataRef->unk_29C[row][column][1] = 3;
            }
        }
    }

    if (gameStateDataRef->unk_178.unk_2[0] != 0) {
        gameStateDataRef->unk_29C[gameStateDataRef->unk_178.unk_2[0] - 1][gameStateDataRef->unk_178.unk_0[0]][0] = 10;
        gameStateDataRef->unk_29C[gameStateDataRef->unk_178.unk_2[0] - 1][gameStateDataRef->unk_178.unk_0[0]][1] = 3;
        gameStateDataRef->unk_29C[gameStateDataRef->unk_178.unk_2[1] - 1][gameStateDataRef->unk_178.unk_0[1]][0] = 10;
        gameStateDataRef->unk_29C[gameStateDataRef->unk_178.unk_2[1] - 1][gameStateDataRef->unk_178.unk_0[1]][1] = 3;
    }
}

/**
 * Original name: aifMakeFlagSet
 */
void aifMakeFlagSet(struct_game_state_data *gameStateDataRef) {
    gameStateDataRef->unk_23D = 0;
    gameStateDataRef->unk_241 = 0;
    gameStateDataRef->unk_237 = 0;
    gameStateDataRef->unk_238 = 0;
    gameStateDataRef->unk_239 = 0;
}

/**
 * Original name: aifGameInit
 */

void aifGameInit(void) {
    s32 i;

    fool_mode = 0;
    s_hard_mode = 0;
    MissRate = 0;
    PlayTime = 0;
    for (i = 0; i < ARRAY_COUNT(game_state_data); i++) {
        s32 j;

        game_state_data[i].unk_23D = 1;
        game_state_data[i].unk_23E = 1;
        game_state_data[i].unk_292 = 0;
        game_state_data[i].unk_294 = 0x64;

        for (j = 0; j < 0x10; j++) {
            game_state_data[i].unk_242[j] = 0;
            game_state_data[i].unk_272[j] = 0;
        }
    }
}

#if VERSION_US || VERSION_CN
/**
 * Original name: aifFirstInit
 */
void aifFirstInit(void) {
    s32 i;

    for (i = 0; i < AI_PARAM_LEN2; i++) {
        s32 j;

        for (j = 0; j < AI_PARAM_LEN1; j++) {
            ai_param[j][i] = ai_param_org[j][i];
        }
    }

    for (i = 0; i < AI_CHAR_DATA_LEN; i++) {
        ai_char_data[i] = ai_char_data_org[i];
    }

    aifGameInit();
}
#endif

/**
 * Original name: aifMake
 */
#if VERSION_US || VERSION_CN
void aifMake(struct_game_state_data *gameStateDataRef) {
    pGameState = gameStateDataRef;

    if (gameStateDataRef->unk_23D == 0) {
        func_8002EB00(gameStateDataRef);
        aifMakeBlkWork(gameStateDataRef);

        aiGoalX = gameStateDataRef->unk_3BC + 1;

        aiGoalY = gameStateDataRef->unk_3BD;
        if (aiGoalY == 0) {
            aiGoalY++;
        }

        aipn = gameStateDataRef->unk_298;
        gameStateDataRef->unk_23C = gameStateDataRef->unk_04E;
        if (FallSpeed[gameStateDataRef->unk_3C0] > aiSlideFSpeed[aiSelSpeed][gameStateDataRef->unk_23C]) {
            aiMoveSF = 1;
        } else {
            aiMoveSF = 0;
        }

        aifFieldCopy(gameStateDataRef);
        aifPlaceSearch();
        aifMoveCheck();
        delpos_cnt = 0;

        if (evs_gamemode == ENUM_EVS_GAMEMODE_1) {
            s32 var_v1;

            flash_special();
            last_flash = 0;

            for (var_v1 = 0; var_v1 < pGameState->unk_164; var_v1++) {
                if (pGameState->unk_0D4.unk_00[var_v1].unk_8 >= 0) {
                    last_flash++;
                }
            }
        }

        aiSetCharacter(gameStateDataRef);
        aiHiruAllPriSet(gameStateDataRef);
        aiHiruSideLineEraser(gameStateDataRef);
        aifReMoveCheck();
        aifKeyMake(gameStateDataRef);
        gameStateDataRef->unk_234 = 0;
        gameStateDataRef->unk_23D = 1;
    }
}
#endif

#if VERSION_US || VERSION_CN
/**
 * Original name: aifMake2
 */
bool aifMake2(struct_game_state_data *gameStateDataRef, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    if (gameStateDataRef->unk_23D != 0) {
        return false;
    }

    func_8002EB00(gameStateDataRef);
    aifMakeBlkWork(gameStateDataRef);

    MissRate = 0;
    aiGoalX = gameStateDataRef->unk_3BC + 1;

    aiGoalY = gameStateDataRef->unk_3BD;
    if (aiGoalY == 0) {
        aiGoalY++;
    }

    aipn = gameStateDataRef->unk_298;
    gameStateDataRef->unk_23C = gameStateDataRef->unk_04E;

    if (FallSpeed[gameStateDataRef->unk_3C0] > aiSlideFSpeed[aiSelSpeed][gameStateDataRef->unk_23C]) {
        aiMoveSF = 1;
    } else {
        aiMoveSF = 0;
    }

    aifFieldCopy(gameStateDataRef);

    aiFlag[0].unk_01 = arg3 == 0;
    aiFlag[0].unk_02 = arg1 + 1;
    aiFlag[0].unk_03 = arg2;
    aiFlag[0].unk_04 = arg4 != 0;

    aiFlagCnt = 1;
    decide = 0;
    aifReMoveCheck();
    aifKeyMake(gameStateDataRef);
    gameStateDataRef->unk_234 = 0;
    gameStateDataRef->unk_23D = 1;

    return true;
}
#endif

#if VERSION_US
/**
 * Original name: aiHiruSideLineEraser
 */
INCLUDE_ASM("asm/us/nonmatchings/main_segment/aiset", aiHiruSideLineEraser);
#endif

extern u8 aiLinePri[];

#if VERSION_CN
#if 0
void aiHiruSideLineEraser(struct_game_state_data *gameStateDataRef) {
    s32 sp8[2];
    s32 sp10[2];
    s32 sp18[2];
    u8 sp20[UNK_SIZE];
    u8 sp30[UNK_SIZE];
    u8 sp40[UNK_SIZE];
    u8 sp50[UNK_SIZE];
    u8 sp60[UNK_SIZE];
    s32 sp68;
    s32 sp80;
    s32 *temp_v0_7;
    s32 temp_a0_3;
    s32 temp_s3;
    s32 temp_t4;
    s32 temp_v0_10;
    s32 var_a3;
    s32 var_a3_2;
    s32 var_a3_3;
    s32 var_a3_4;
    s32 var_s1;
    s32 var_s1_2;
    s32 var_t0;
    s32 var_t0_3;
    s32 var_t1;
    s32 var_t1_3;
    s32 var_t2_2;
    s32 var_t3_2;
    s32 var_t8_2;
    struct_aiFlag *temp_v0;
    u8 *var_v0_6;
    u8 *var_v0_7;
    u8 temp_a1_2;
    u8 temp_a2_2;
    u8 temp_a3;
    u8 temp_t5;
    u8 temp_v0_8;
    u8 var_a1;
    u8 var_t6_2;
    u8 var_v0_3;

    temp_v0 = &aiFlag[decide];
    if (((u8) temp_v0->unk_0C[8] != 0) || ((u8) temp_v0->unk_0C[0x12] != 0)) {
        return;
    }

    var_s1 = 0;

    sp80 = 1;
    sp68 = 0;

    for (var_a3 = 0; var_a3 < 8; var_a3++) {
        sp50[var_a3] = 0x11;
        sp30[var_a3] = 0x11;
        sp20[var_a3] = 0x11;
        sp40[var_a3] = 0;
    }

    for (var_a3_2 = 0; var_a3_2 < 8; var_a3_2++) {
        var_t0 = 0;
        var_t1 = 0;

        for (var_a1 = 0x10; var_a1 >= 2; var_a1--) {
            if (gameStateDataRef->unk_29C[var_a1][var_a3_2][0] == 0xA) {
                var_t1 += 1;
            } else if ((gameStateDataRef->unk_29C[var_a1][var_a3_2][0] >= 3) && (gameStateDataRef->unk_29C[var_a1][var_a3_2][0] <= 7)) {
                if (var_t0 == 0) {
                    sp40[var_a3_2] = var_a1;
                    if ((var_t1 >= 3) || (((gameStateDataRef->unk_29C[var_a1+2][var_a3_2][0] == 0xA) || (gameStateDataRef->unk_29C[var_a1+2][var_a3_2][1] == gameStateDataRef->unk_29C[var_a1][var_a3_2][1])) && (gameStateDataRef->unk_29C[var_a1+3][var_a3_2][1] == gameStateDataRef->unk_29C[var_a1][var_a3_2][1]))) {
                        sp20[var_a3_2] = var_a1;
                    } else if ((var_a3_2 == 2) || (var_a3_2 == 3) || (var_a3_2 == 4) || (var_a3_2 == 5)) {
                        var_t0 = -1;
                        var_t1 = 0;
                        sp40[var_a3_2] = 0;
                        sp30[var_a3_2] = var_a1;
                        sp50[var_a3_2] = var_a1;
                    }
                    var_t0 += 1;
                }
            } else {
                if (var_t0 == 0) {
                    sp30[var_a3_2] = var_a1;
                    var_t1 = 0;
                }
                sp50[var_a3_2] = var_a1;
            }
        }

        if ((sp40[var_a3_2] != 0) && (sp50[var_a3_2] < 6U)) {
            sp80 = 0;
            if ((var_a3_2 == 2) || (var_a3_2 == 3) || (var_a3_2 == 4) || (var_a3_2 == 5)) {
                sp68 = 1;
                var_s1 = 0;
                break;
            }
        }

        if (sp40[var_a3_2] >= 0xEU) {
            var_s1 = 1;
        }
    }


    if ((var_s1 | sp80) != 0) {
        return;
    }

    for (var_a3_3 = 0; var_a3_3 < 8; var_a3_3++) {
        sp60[var_a3_3] = 1;
    }

    var_s1_2 = 0;

    sp18[1] = 1;
    sp18[0] = 1;
    sp80 = aiFlagCnt;

    for (var_t8_2 = 0; (var_t8_2 < 8) && (var_s1_2 == 0); var_t8_2++) {
        temp_a3 = aiLinePri[var_t8_2];
        temp_t5 = sp20[temp_a3];

        if (temp_t5 >= 0xE) {
            continue;
        }

        sp60[temp_a3] = 0;

        var_v0_3 = temp_a3;
        if ((s32) temp_a3 < 0) {
            var_v0_3 = temp_a3 + 3;
        }

        temp_v0_7 = &sp18[(var_v0_3 & 0x1FC)];
        if (*temp_v0_7 == 0) {
            continue;
        }

        *temp_v0_7 = 0;
        temp_v0_8 = sp30[temp_a3];
        temp_t4 = (s32) temp_a3 < 4;
        temp_s3 = temp_v0_8 - temp_t5;

        if (temp_t4 == 0) {
            var_t6_2 = temp_a3 - 1;
        } else {
            var_t6_2 = temp_a3;
        }

        var_t2_2 = sp80;

        sp10[1] = 0;
        sp10[0] = 0;
        sp8[1] = 0;
        sp8[0] = 0;

        for (var_t3_2 = 0; var_t3_2 < var_t2_2; var_t3_2++) {
            if ((aiFlag[var_t3_2].unk_00 != 1) || (aiFlag[var_t3_2].unk_03 != (temp_v0_8 - 1))) {
                continue;
            }

            if (aiFlag[var_t3_2].unk_01 == 0) {
                if ((aiFlag[var_t3_2].unk_02 - 1) == temp_a3) {
                    var_t2_2 = (s32) aiFlagCnt;
                    sp8[aiFlag[var_t3_2].unk_04] = var_t3_2+1;
                }
            } else if ((aiFlag[var_t3_2].unk_02 - 1) == var_t6_2) {
                var_t2_2 = (s32) aiFlagCnt;
                sp8[aiFlag[var_t3_2].unk_04 + 2] = var_t3_2+1;
            }
        }

        if ((sp8[0] + sp10[0] + sp8[1] + sp10[1]) == 0) {
            continue;
        }

        temp_a2_2 = gameStateDataRef->unk_29C[temp_t5][temp_a3][1];
        if (temp_s3 == 5) {
            if ((sp10[0] + sp10[1]) != 0) {
                var_s1_2 = sp10[0];
            }
            if ((sp8[0] + sp8[1]) != 0) {
                if (aiNext[0] != temp_a2_2) {
                    if (aiNext[1] == temp_a2_2) {
                        var_s1_2 = sp8[1];
                    }
                    var_t8_2 += 1;
                } else {
                    var_s1_2 = sp8[0];
                }
            }
        } else if (temp_s3 < 5) {
            if ((sp10[0] + sp10[1]) != 0) {
                if (aiNext[0] != temp_a2_2) {
                    if (aiNext[1] == temp_a2_2) {
                        var_s1_2 = sp10[1];
                        if (temp_t4 == 0) {
                            var_s1_2 = sp10[0];
                        }
                    }
                } else {
                    var_s1_2 = sp10[0];
                    if (temp_t4 == 0) {
                        var_s1_2 = sp10[1];
                    }
                }
            }

            if ((sp8[0] + sp8[1] != 0) && (aiNext[0] == aiNext[1])) {
                if (temp_a2_2 == aiNext[0]) {
                    var_s1_2 = sp8[0];
                }
            }
        } else {
            if (sp8[0] != 0) {
                var_s1_2 = sp8[0];
            }
        }
    }

    if (var_s1_2 != 0) {
        decide = var_s1_2 - 1;
        return;
    }

    if (sp68 != 0) {
        return;
    }

    var_t1_3 = -1;
    var_a3_4 = -0xF4241;
    var_t0_3 = 0;

    while (var_t0_3 < (s32) aiFlagCnt) {
        if (aiFlag[var_t0_3].unk_01 != 0) {
            temp_a1_2 = aiFlag[var_t0_3].unk_02;
            temp_a0_3 = temp_a1_2 - 1;
            var_v0_6 = &sp60 + temp_a1_2;
            if (sp60[temp_a0_3] == 0) {
                if (aiFlag[var_t0_3].unk_03 < sp20[temp_a0_3]) {
                    var_v0_6 = &sp60 + temp_a1_2;
                    goto block_101;
                }
            } else {
block_101:
                if (*var_v0_6 == 0) {
                    var_v0_7 = &sp20[temp_a1_2];
                    goto block_103;
                }
                goto block_106;
            }
        } else {
            temp_v0_10 = aiFlag[var_t0_3].unk_02 - 1;
            if (*(&sp60 + temp_v0_10) == 0) {
                var_v0_7 = &sp20[temp_v0_10];
block_103:
                if (aiFlag[var_t0_3].unk_03 >= (u8) *var_v0_7) {
                } else {
                    goto block_106;
                }
            } else {
block_106:
                if (var_a3_4 < aiFlag[var_t0_3].unk_08) {
                    var_a3_4 = aiFlag[var_t0_3].unk_08;
                    var_t1_3 = var_t0_3;
                }
            }
        }

        var_t0_3 += 1;
    }

    if (var_t1_3 != -1) {
        decide = (u8) var_t1_3;
    }
}
#else
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/aiset", aiHiruSideLineEraser);
#endif
#endif

#if VERSION_US
// no original name :c
INCLUDE_ASM("asm/us/nonmatchings/main_segment/aiset", func_8002F924);
#endif

extern u8 srh_466[][2];

#if VERSION_CN
void func_80031A54_cn(u8 arg0, u8 arg1) {
    if (aif_field[arg0][arg1].unk_1 != 4) {
        s8 temp_a0_2 = aif_field[arg0][arg1].unk_1;
        s8 temp_v0 = arg0 + srh_466[temp_a0_2][0];
        s8 temp_v1 = arg1 + srh_466[temp_a0_2][1];

        if ((temp_v0 > 0) && (temp_v0 < 17) && (temp_v1 >= 0) && (temp_v1 < 8)) {
            aif_field[temp_v0][temp_v1].unk_1 = 4;
        }
    }
}
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/aiset", aifEraseLineCore);
#endif

#define HEI_WEI_DATA_LEN 10

extern u8 hei_data[HEI_WEI_DATA_LEN];
extern u8 wid_data[HEI_WEI_DATA_LEN];

#if VERSION_CN
#ifdef NON_MATCHING
// regalloc at the bottom
s32 aifEraseLineCore(s32 arg0, s32 arg1) {
    s32 sp18 = 0;
    s32 sp1C = 0;
    s32 temp_s7 = aif_field[arg1][arg0].unk_0;
    s32 var_s0;

    if (hei_data[2] >= 4U) {
        sp18 = 1;

        for (var_s0 = arg1 - 1; (var_s0 > 0) && (var_s0 > arg1 - 4); var_s0--) {
            if (aif_field[var_s0][arg0].unk_0 == temp_s7) {
                if ((aif_field[var_s0][arg0].unk_1 > 4) && (aif_field[var_s0][arg0].unk_1 < 8)) {
                    hei_data[1]++;
                } else {
                    func_80031A54_cn(var_s0, arg0);
                }

                if (evs_gamemode == ENUM_EVS_GAMEMODE_1) {
                    if (flash_virus(arg0, var_s0) != 0) {
                        sp1C = 1;
                    }
                }

                aif_field[var_s0][arg0].unk_1 = 0xA;
                aif_field[var_s0][arg0].unk_0 = 3;
            } else {
                var_s0 = 0;
            }
        }

        for (var_s0 = arg1 + 1; (var_s0 < arg1 + 4) && (var_s0 < 0x11); var_s0++) {
            if (aif_field[var_s0][arg0].unk_0 == temp_s7) {
                if ((aif_field[var_s0][arg0].unk_1 > 4) && (aif_field[var_s0][arg0].unk_1 < 8)) {
                    hei_data[1]++;
                } else {
                    func_80031A54_cn(var_s0, arg0);
                }

                aif_field[var_s0][arg0].unk_1 = 0xA;
                aif_field[var_s0][arg0].unk_0 = 3;
            } else {
                var_s0 = 0x11;
            }
        }
    }

    if (wid_data[2] >= 4U) {
        sp18 = 1;

        for (var_s0 = arg0 - 1; (var_s0 > -1) && (var_s0 > arg0 - 4); var_s0--) {
            if (aif_field[arg1][var_s0].unk_0 == temp_s7) {
                if ((aif_field[arg1][var_s0].unk_1 > 4) && (aif_field[arg1][var_s0].unk_1 < 8)) {
                    wid_data[1]++;
                } else {
                    func_80031A54_cn(arg1, var_s0);
                }

                aif_field[arg1][var_s0].unk_1 = 0xA;
                aif_field[arg1][var_s0].unk_0 = 3;
            } else {
                var_s0 = -1;
            }
        }

        for (var_s0 = arg0 + 1; (var_s0 < arg0 + 4) && (var_s0 < 8); var_s0++) {
            if (aif_field[arg1][var_s0].unk_0 == temp_s7) {
                if ((aif_field[arg1][var_s0].unk_1 > 4) && (aif_field[arg1][var_s0].unk_1 < 8)) {
                    wid_data[1]++;
                } else {
                    func_80031A54_cn(arg1, var_s0);
                }

                if (evs_gamemode == ENUM_EVS_GAMEMODE_1) {
                    if (flash_virus(var_s0, arg1) != 0) {
                        sp1C = 1;
                    }
                }

                aif_field[arg1][var_s0].unk_1 = 0xA;
                aif_field[arg1][var_s0].unk_0 = 3;
            } else {
                var_s0 = 8;
            }
        }
    }

    if (sp18 != 0) {
        func_80031A54_cn(arg1, arg0);

        aif_field[arg1][arg0].unk_1 = 0xA;
        aif_field[arg1][arg0].unk_0 = 3;
    }

    return sp1C;
}
#else
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/aiset", aifEraseLineCore);
#endif
#endif

#if VERSION_US
/**
 * Original name: aifRensaCheckCore
 */
INCLUDE_ASM("asm/us/nonmatchings/main_segment/aiset", aifRensaCheckCore);
#endif

#if VERSION_CN
#if 0
? func_8002F924(s32, s32);                          /* extern */
extern ? D_800885D8;
extern u16 aiHiEraseCtr;

s32 aifRensaCheckCore(struct_game_state_data *gameStateDataRef, struct_aiFlag *aiFlagRef, u8 arg2, u8 arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9) {
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_a0_3;
    s32 temp_a0_4;
    s32 temp_s5;
    s32 temp_s5_2;
    s32 temp_t4;
    s32 temp_t6;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v1;
    s32 temp_v1_12;
    s32 temp_v1_17;
    s32 temp_v1_18;
    s32 temp_v1_19;
    s32 temp_v1_20;
    s32 temp_v1_21;
    s32 temp_v1_22;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 temp_v1_4;
    s32 temp_v1_6;
    s32 temp_v1_7;
    s32 var_a0;
    s32 var_a0_2;
    s32 var_a0_3;
    s32 var_a0_4;
    s32 var_a1;
    s32 var_a1_3;
    s32 var_a1_5;
    s32 var_a1_6;
    s32 var_a2;
    s32 var_a3;
    s32 var_a3_2;
    s32 var_s0;
    s32 var_s0_2;
    s32 var_s0_3;
    s32 var_s0_4;
    s32 var_s0_5;
    s32 var_s1;
    s32 var_s1_2;
    s32 var_s1_3;
    s32 var_s1_4;
    s32 var_s1_5;
    s32 var_s1_6;
    s32 var_s1_7;
    s32 var_s2;
    s32 var_s2_2;
    s32 var_s2_3;
    s32 var_s2_4;
    s32 var_s2_5;
    s32 var_s2_6;
    s32 var_s2_7;
    s32 var_s2_8;
    s32 var_s3;
    s32 var_s3_2;
    s32 var_s3_3;
    s32 var_s3_4;
    s32 var_s3_5;
    s32 var_s7;
    s32 var_t1;
    s32 var_t2;
    s32 var_t3;
    s32 var_t5;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v0_3;
    s32 var_v0_4;
    s32 var_v0_5;
    s32 var_v0_6;
    s32 var_v0_7;
    s32 var_v0_8;
    u32 temp_v1_10;
    u32 temp_v1_11;
    u32 temp_v1_13;
    u32 temp_v1_14;
    u32 temp_v1_15;
    u32 temp_v1_16;
    u32 temp_v1_5;
    u32 temp_v1_8;
    u32 var_v0_10;
    u32 var_v0_9;
    u8 temp_v1_9;
    void *var_a1_2;
    void *var_a1_4;

    var_s7 = 0;
    var_s1 = 0;
    var_s2 = 0;
    do {
        var_a1 = var_s1 * 2;
loop_2:
        *(aif_field + var_a1) = (gameStateDataRef + var_a1)->unk_29D;
        var_s2 += 1;
        (&aif_field[0][0].unk_1)[var_a1] = gameStateDataRef->unk_29C[0][0][var_a1];
        var_a1 += 0x10;
        if (var_s2 < 0x11) {
            goto loop_2;
        }
        var_s1 += 1;
        var_s2 = 0;
    } while (var_s1 < 8);
    aiHiEraseCtr = 0;
    var_s1_2 = 0;
    do {
        var_s2_2 = 1;
        var_a1_2 = &D_800885D8 + 8;
        var_a0 = (var_s1_2 * 2) + 0x10;
loop_6:
        if ((u8) (&aif_field[0][0].unk_1)[var_a0] < 8U) {
            aiHiEraseCtr += *(var_a1_2 + var_s1_2);
        }
        var_a1_2 += 8;
        var_s2_2 += 1;
        var_a0 += 0x10;
        if (var_s2_2 < 4) {
            goto loop_6;
        }
        var_s1_2 += 1;
    } while (var_s1_2 < 8);
    temp_v1 = arg3 & 0xFF;
    if (temp_v1 != 0) {
        temp_v0 = ((arg2 & 0xFF) * 2) + (temp_v1 * 0x10);
        (&aif_field[0][0].unk_1)[temp_v0] = arg5;
        *(aif_field + temp_v0) = arg4;
    }
    temp_v1_2 = arg7 & 0xFF;
    if (temp_v1_2 != 0) {
        temp_v0_2 = (arg6 * 2) + (temp_v1_2 * 0x10);
        (&aif_field[0][0].unk_1)[temp_v0_2] = arg9;
        *(aif_field + temp_v0_2) = arg8;
    }
    var_s2_3 = 1;
    var_s1_3 = 0;
    do {
        temp_s5 = var_s2_3 * 0x10;
        var_v0_2 = 0 * 2;
loop_16:
        temp_v1_3 = var_v0_2 + temp_s5;
        if ((&aif_field[0][0].unk_1)[temp_v1_3] != 0xA) {
            var_s3 = 1;
            if ((var_s1_3 + 1) < 8) {
                var_v0_3 = 1 & 0xFF;
loop_19:
                temp_v1_4 = ((var_s1_3 + var_v0_3) * 2) + temp_s5;
                if (((&aif_field[0][0].unk_1)[temp_v1_4] != 0xA) && (*(aif_field + temp_v1_4) == (*(aif_field + temp_v1_3) & 0xFF))) {
                    var_s3 += 1;
                    var_v0_3 = var_s3 & 0xFF;
                    if ((var_s1_3 + (var_s3 & 0xFF)) < 8) {
                        goto loop_19;
                    }
                }
            }
            temp_v1_5 = var_s3 & 0xFF;
            if (temp_v1_5 >= 4U) {
                var_s7 += temp_v1_5 >> 2;
                var_s0 = 0;
                if (temp_v1_5 != 0) {
                    var_a0_2 = var_s2_3 & 0xFF;
                    do {
                        func_8002F924(var_a0_2, (var_s0 + var_s1_3) & 0xFF);
                        (&aif_field[0][0].unk_1)[((var_s1_3 + (var_s0 & 0xFF)) * 2) + temp_s5] = 8;
                        var_s0 += 1;
                        var_a0_2 = var_s2_3 & 0xFF;
                    } while ((u32) (var_s0 & 0xFF) < temp_v1_5);
                }
            }
            var_s1_3 = var_s1_3 - 1 + (var_s3 & 0xFF);
        }
        var_s1_3 += 1;
        var_v0_2 = var_s1_3 * 2;
        if (var_s1_3 < 5) {
            goto loop_16;
        }
        var_s2_3 += 1;
        var_s1_3 = 0;
    } while (var_s2_3 < 0x11);
    var_s2_4 = 1;
    do {
        temp_s5_2 = var_s1_3 * 2;
        var_v0_4 = 1 * 0x10;
loop_31:
        temp_v1_6 = temp_s5_2 + var_v0_4;
        if ((&aif_field[0][0].unk_1)[temp_v1_6] != 0xA) {
            var_s3_2 = 1;
            if ((var_s2_4 + 1) < 0x11) {
                var_v0_5 = 1 & 0xFF;
loop_34:
                temp_v1_7 = temp_s5_2 + ((var_s2_4 + var_v0_5) * 0x10);
                if (((&aif_field[0][0].unk_1)[temp_v1_7] != 0xA) && (*(aif_field + temp_v1_7) == (*(aif_field + temp_v1_6) & 0xFF))) {
                    var_s3_2 += 1;
                    var_v0_5 = var_s3_2 & 0xFF;
                    if ((var_s2_4 + (var_s3_2 & 0xFF)) < 0x11) {
                        goto loop_34;
                    }
                }
            }
            temp_v1_8 = var_s3_2 & 0xFF;
            if (temp_v1_8 >= 4U) {
                var_s7 += temp_v1_8 >> 2;
                var_s0_2 = 0;
                if (temp_v1_8 != 0) {
                    var_a0_3 = var_s2_4;
                    do {
                        func_8002F924(var_a0_3 & 0xFF, var_s1_3 & 0xFF);
                        (&aif_field[0][0].unk_1)[temp_s5_2 + ((var_s2_4 + (var_s0_2 & 0xFF)) * 0x10)] = 8;
                        var_s0_2 += 1;
                        var_a0_3 = var_s0_2 + var_s2_4;
                    } while ((u32) (var_s0_2 & 0xFF) < temp_v1_8);
                }
            }
            var_s2_4 = var_s2_4 - 1 + (var_s3_2 & 0xFF);
        }
        var_s2_4 += 1;
        var_v0_4 = var_s2_4 * 0x10;
        if (var_s2_4 < 0xE) {
            goto loop_31;
        }
        var_s1_3 += 1;
        var_s2_4 = 1;
    } while (var_s1_3 < 8);
    var_s3_3 = 1;
    var_s2_5 = 0x10;
    var_s1_4 = 0xF0;
    var_t5 = 0x110;
    do {
        temp_t4 = var_s2_5 + 1;
        var_t1 = 0x10;
        temp_t6 = var_s2_5 * 0x10;
        var_a1_3 = temp_t6 + 0xE;
        var_a2 = 0xE;
        var_t3 = var_t5 + 0xE;
        var_t2 = var_s1_4 + 0xE;
loop_46:
        temp_v1_9 = (&aif_field[0][0].unk_1)[var_a1_3];
        if (temp_v1_9 != 2) {
            if ((s32) temp_v1_9 < 3) {
                if (temp_v1_9 != 1) {
                    var_t1 -= 2;
                } else if ((var_s2_5 != 0x10) && ((&aif_field[0][0].unk_1)[var_t3] == 0xA)) {
                    var_s0_3 = temp_t4;
                    temp_v1_10 = var_s0_3 & 0xFF;
                    var_s3_3 = 0;
                    if (temp_v1_10 < 0x11U) {
                        var_v0_6 = temp_v1_10 * 0x10;
loop_64:
                        if ((&aif_field[0][0].unk_1)[var_a2 + var_v0_6] == 0xA) {
                            var_s0_3 += 1;
                            temp_v1_11 = var_s0_3 & 0xFF;
                            var_v0_6 = temp_v1_11 * 0x10;
                            if (temp_v1_11 < 0x11U) {
                                goto loop_64;
                            }
                        }
                    }
                    temp_a0 = (var_s0_3 - 1) & 0xFF;
                    temp_v1_12 = var_a2 + (temp_a0 * 0x10);
                    (&aif_field[0][0].unk_1)[temp_v1_12] = (&aif_field[0][0].unk_1)[var_a1_3];
                    *(aif_field + temp_v1_12) = *(aif_field + var_a1_3);
                    (&aif_field[0][0].unk_1)[var_a1_3] = 0xA;
                    temp_a0_2 = var_a2 + ((temp_a0 - 1) * 0x10);
                    (&aif_field[0][0].unk_1)[temp_a0_2] = (&aif_field[0][0].unk_1)[var_t2];
                    *(aif_field + temp_a0_2) = *(aif_field + var_t2);
                    (&aif_field[0][0].unk_1)[var_t2] = 0xA;
                    var_t1 -= 2;
                } else {
                    goto block_77;
                }
                goto block_78;
            }
            if (temp_v1_9 != 4) {
                var_t1 -= 2;
                if (temp_v1_9 == 8) {
                    (&aif_field[0][0].unk_1)[var_a1_3] = 0xA;
                    var_a1_3 -= 2;
                } else {
                    goto block_78;
                }
            } else {
                if ((var_s2_5 != 0x10) && ((&aif_field[0][0].unk_1)[var_t3] == 0xA)) {
                    var_s0_4 = temp_t4;
                    temp_v1_13 = var_s0_4 & 0xFF;
                    var_s3_3 = 0;
                    if (temp_v1_13 < 0x11U) {
                        var_v0_7 = temp_v1_13 * 0x10;
loop_57:
                        if ((&aif_field[0][0].unk_1)[var_a2 + var_v0_7] == 0xA) {
                            var_s0_4 += 1;
                            temp_v1_14 = var_s0_4 & 0xFF;
                            var_v0_7 = temp_v1_14 * 0x10;
                            if (temp_v1_14 < 0x11U) {
                                goto loop_57;
                            }
                        }
                    }
                    temp_v0_3 = var_a2 + (((var_s0_4 - 1) & 0xFF) * 0x10);
                    (&aif_field[0][0].unk_1)[temp_v0_3] = (&aif_field[0][0].unk_1)[var_a1_3];
                    *(aif_field + temp_v0_3) = *(aif_field + var_a1_3);
                    (&aif_field[0][0].unk_1)[var_a1_3] = 0xA;
                    var_t1 -= 2;
                } else {
                    goto block_77;
                }
                goto block_78;
            }
        } else {
            if ((var_s2_5 != 0x10) && ((&aif_field[0][0].unk_1)[var_t3] == 0xA) && ((&aif_field[0][0].unk_1)[var_t1 + var_t5] == 0xA)) {
                var_s0_5 = temp_t4;
                temp_v1_15 = var_s0_5 & 0xFF;
                var_s3_3 = 0;
                if ((temp_v1_15 < 0x11U) && ((&aif_field[0][0].unk_1)[var_a2 + (temp_v1_15 * 0x10)] == 0xA)) {
                    var_v0_8 = temp_v1_15 * 0x10;
loop_73:
                    if ((&aif_field[0][0].unk_1)[var_t1 + var_v0_8] == 0xA) {
                        var_s0_5 += 1;
                        temp_v1_16 = var_s0_5 & 0xFF;
                        if (temp_v1_16 < 0x11U) {
                            var_v0_8 = temp_v1_16 * 0x10;
                            if ((&aif_field[0][0].unk_1)[var_a2 + (temp_v1_16 * 0x10)] == 0xA) {
                                goto loop_73;
                            }
                        }
                    }
                }
                temp_a0_3 = ((var_s0_5 - 1) & 0xFF) * 0x10;
                temp_v1_17 = var_a2 + temp_a0_3;
                (&aif_field[0][0].unk_1)[temp_v1_17] = (&aif_field[0][0].unk_1)[var_a1_3];
                *(aif_field + temp_v1_17) = *(aif_field + var_a1_3);
                temp_v1_18 = var_t1 + temp_t6;
                (&aif_field[0][0].unk_1)[var_a1_3] = 0xA;
                temp_a0_4 = var_t1 + temp_a0_3;
                (&aif_field[0][0].unk_1)[temp_a0_4] = (&aif_field[0][0].unk_1)[temp_v1_18];
                *(aif_field + temp_a0_4) = *(aif_field + temp_v1_18);
                (&aif_field[0][0].unk_1)[temp_v1_18] = 0xA;
            }
block_77:
            var_t1 -= 2;
block_78:
            var_a1_3 -= 2;
        }
        var_a2 -= 2;
        var_t3 -= 2;
        var_t2 -= 2;
        if (var_a2 >= 0) {
            goto loop_46;
        }
        var_s1_4 -= 0x10;
        var_s2_5 -= 1;
        var_t5 -= 0x10;
    } while (var_s2_5 > 0);
    var_s1_5 = 0;
    do {
        var_s2_6 = 1;
        var_a1_4 = &D_800885D8 + 8;
        var_a0_4 = (var_s1_5 * 2) + 0x10;
loop_83:
        if ((u8) (&aif_field[0][0].unk_1)[var_a0_4] < 8U) {
            aiHiEraseCtr -= *(var_a1_4 + var_s1_5);
        }
        var_a1_4 += 8;
        var_s2_6 += 1;
        var_a0_4 += 0x10;
        if (var_s2_6 < 4) {
            goto loop_83;
        }
        var_s1_5 += 1;
    } while (var_s1_5 < 8);
    if ((u32) (var_s7 & 0xFF) < 2U) {
        var_s2_7 = 1;
        var_a1_5 = 0x10;
loop_93:
        var_s1_6 = 0;
        var_a3 = var_a1_5;
loop_94:
        if ((&aif_field[0][0].unk_1)[var_a3] != 0xA) {
            temp_v1_19 = var_s1_6 + 1;
            var_s3_4 = 1;
            if (temp_v1_19 < 8) {
                var_v0_9 = 1 & 0xFF;
                if ((&aif_field[0][0].unk_1)[(temp_v1_19 * 2) + var_a1_5] != 0xA) {
loop_98:
                    var_v0_9 = var_s3_4 & 0xFF;
                    if (*(aif_field + (((var_s1_6 + var_v0_9) * 2) + var_a1_5)) == (*(aif_field + var_a3) & 0xFF)) {
                        var_s3_4 += 1;
                        temp_v1_20 = var_s1_6 + (var_s3_4 & 0xFF);
                        if ((temp_v1_20 >= 8) || (var_v0_9 = var_s3_4 & 0xFF, ((&aif_field[0][0].unk_1)[(temp_v1_20 * 2) + var_a1_5] == 0xA))) {
                            goto block_101;
                        }
                        goto loop_98;
                    }
                }
            } else {
block_101:
                var_v0_9 = var_s3_4 & 0xFF;
            }
            var_v0 = 1;
            if (var_v0_9 < 4U) {
                goto block_103;
            }
        } else {
block_103:
            var_s1_6 += 1;
            var_a3 += 2;
            if (var_s1_6 >= 5) {
                var_s2_7 += 1;
                var_a1_5 += 0x10;
                if (var_s2_7 >= 0x11) {
                    var_s1_7 = 0;
                    var_a1_6 = 0;
loop_106:
                    var_s2_8 = 1;
                    var_a3_2 = var_a1_6 + 0x10;
loop_107:
                    if ((&aif_field[0][0].unk_1)[var_a3_2] != 0xA) {
                        temp_v1_21 = var_s2_8 + 1;
                        var_s3_5 = 1;
                        if (temp_v1_21 < 0x11) {
                            var_v0_10 = 1 & 0xFF;
                            if ((&aif_field[0][0].unk_1)[var_a1_6 + (temp_v1_21 * 0x10)] != 0xA) {
loop_111:
                                var_v0_10 = var_s3_5 & 0xFF;
                                if (*(aif_field + (var_a1_6 + ((var_s2_8 + var_v0_10) * 0x10))) == (*(aif_field + var_a3_2) & 0xFF)) {
                                    var_s3_5 += 1;
                                    temp_v1_22 = var_s2_8 + (var_s3_5 & 0xFF);
                                    if ((temp_v1_22 >= 0x11) || (var_v0_10 = var_s3_5 & 0xFF, ((&aif_field[0][0].unk_1)[var_a1_6 + (temp_v1_22 * 0x10)] == 0xA))) {
                                        goto block_114;
                                    }
                                    goto loop_111;
                                }
                            }
                        } else {
block_114:
                            var_v0_10 = var_s3_5 & 0xFF;
                        }
                        var_v0 = 1;
                        if (var_v0_10 < 4U) {
                            goto block_116;
                        }
                    } else {
block_116:
                        var_s2_8 += 1;
                        var_a3_2 += 0x10;
                        if (var_s2_8 >= 0xE) {
                            var_s1_7 += 1;
                            var_a1_6 += 2;
                            if (var_s1_7 >= 8) {
                                var_v0 = 0;
                            } else {
                                goto loop_106;
                            }
                        } else {
                            goto loop_107;
                        }
                    }
                } else {
                    goto loop_93;
                }
            } else {
                goto loop_94;
            }
        }
        /* Duplicate return node #119. Try simplifying control flow for better match */
        return var_v0;
    }
    var_v0 = 1;
    if (var_s3_3 & 0xFF) {
        return 2;
    }
    return var_v0;
}
#else
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/aiset", aifRensaCheckCore);
#endif
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/aiset", aifRensaCheck);
#endif

#if VERSION_CN
s32 aifRensaCheck(struct_game_state_data *gameStateDataRef, struct_aiFlag *aiFlagRef) {
    u8 temp_a2 = aiFlagRef->unk_02 - 1;
    u8 temp_a3 = aiFlagRef->unk_03;
    u8 var_t2;
    u8 var_t4;
    u8 var_t5;
    u8 var_t0;
    u8 var_t3;
    u8 var_t1; //! @bug: sometimes not set

    if (aiFlagRef->unk_01 == 0) {
        s32 temp_v1;

        var_t5 = 1;
        var_t4 = temp_a2;
        temp_v1 = temp_a3 - 1;
        var_t3 = temp_a3 - 1;
        var_t2 = 0;
        if (aiFlagRef->unk_04 == 0) {
            var_t0 = aiNext[1];
            if (temp_v1 > 0) {
                var_t1 = aiNext[0];
            }
        } else {
            var_t0 = aiNext[0];
            if (temp_v1 > 0) {
                var_t1 = aiNext[1];
            }
        }
    } else {
        var_t5 = 2;
        var_t4 = temp_a2 + 1;
        var_t3 = temp_a3;
        var_t2 = 3;
        if (aiFlagRef->unk_04 == 0) {
            var_t0 = aiNext[0];
            var_t1 = aiNext[1];
        } else {
            var_t0 = aiNext[1];
            var_t1 = aiNext[0];
        }
    }

    return aifRensaCheckCore(gameStateDataRef, aiFlagRef, temp_a2, temp_a3, var_t0, var_t5, var_t4, var_t3, var_t1,
                             var_t2);
}
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/aiset", aifSearchLineCore);
#endif

extern u8 BadLineRate[][8];

#if VERSION_CN
bool aifSearchLineCore(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_s2 = aif_field[arg1][arg0].unk_0;
    s32 i;
    s32 j;
    s32 var_t3;
    bool var_t0_3;
    bool var_t4;

    for (j = 0; j < HEI_WEI_DATA_LEN; j++) {
        hei_data[j] = wid_data[j] = 0;
    }

    if (aif_field[arg1][arg0].unk_1 == 0xA) {
        return 0;
    }

    if (arg2 != 2) {
        var_t4 = true;

        for (i = arg1 - 1; (i > 0) && (i > arg1 - 4); i--) {
            if (aif_field[i][arg0].unk_0 != temp_s2) {
                if (aif_field[i][arg0].unk_0 != 3) {
                    i = 0;
                } else {
                    var_t4 = false;
                }
            } else {
                hei_data[3]++;
                if ((aif_field[i][arg0].unk_1 > 4) && (aif_field[i][arg0].unk_1 < 8)) {
                    hei_data[4]++;
                    if (i < 4) {
                        hei_data[8] += BadLineRate[i][arg0];
                    }
                } else if (i < 4) {
                    hei_data[7] += BadLineRate[i][arg0];
                }
                if (var_t4) {
                    hei_data[2]++;
                }
            }

            if (i > 0) {
                hei_data[5]++;
            }
        }

        for (i = arg1 + 1, var_t4 = true, var_t3 = 0; i < GAME_MAP_ROWS; i++, var_t3++) {
            if (aif_field[i][arg0].unk_0 != temp_s2) {
                if (aif_field[i][arg0].unk_0 != 3) {
                    i = 0x11;
                } else {
                    var_t4 = false;
                }
            } else {
                hei_data[3]++;

                if ((aif_field[i][arg0].unk_1 > 4) && (aif_field[i][arg0].unk_1 < 8)) {
                    if (var_t3 < 3) {
                        hei_data[4]++;
                        if (i < 4) {
                            hei_data[8] += BadLineRate[i][arg0];
                        }
                    }
                } else if (i < 4) {
                    hei_data[7] += BadLineRate[i][arg0];
                }

                if (var_t4) {
                    hei_data[2]++;
                }
                hei_data[5]++;
            }
        }

        hei_data[2]++;
        hei_data[3]++;
        hei_data[5]++;
    }

    if (arg2 != 1) {
        for (i = arg0 - 1, var_t3 = 1, var_t4 = true; (i >= 0) && (i > arg0 - 4); i--) {
            if (aif_field[arg1][i].unk_0 != temp_s2) {
                if (aif_field[arg1][i].unk_0 != 3) {
                    i = -1;
                } else {
                    var_t4 = false;
                    if (var_t3 != 0) {
                        var_t0_3 = false;

                        for (j = 0; j < aiFlagCnt; j++) {
                            if ((aiFlag[j].unk_00 == 1) && (aiFlag[j].unk_01 == 0) && ((aiFlag[j].unk_02 - 1) == i)) {
                                if ((aiFlag[j].unk_03 == arg1) || (aiFlag[j].unk_03 == (arg1 + 1))) {
                                    var_t0_3 = true;
                                    wid_data[5]++;
                                    j = aiFlagCnt;
                                }
                            }
                        }

                        if (!var_t0_3) {
                            var_t3 = 0;
                        }
                    }
                }
            } else {
                wid_data[3]++;
                if ((aif_field[arg1][i].unk_1 > 4) && (aif_field[arg1][i].unk_1 < 8)) {
                    wid_data[4]++;
                    if (arg1 < 4) {
                        wid_data[8] += BadLineRate[arg1][i];
                    }
                } else if (arg1 < 4) {
                    wid_data[7] += BadLineRate[arg1][i];
                }
                if (var_t4) {
                    wid_data[2]++;
                }
                if (var_t3 != 0) {
                    wid_data[5]++;
                }
            }
        }

        for (i = arg0 + 1, var_t3 = 1, var_t4 = true; (i < arg0 + 4) && (i < GAME_MAP_COLUMNS); i++) {
            if (aif_field[arg1][i].unk_0 != temp_s2) {
                if (aif_field[arg1][i].unk_0 != 3) {
                    i = 8;
                } else {
                    var_t4 = false;
                    if (var_t3 != 0) {
                        var_t0_3 = false;

                        for (j = 0; j < aiFlagCnt; j++) {
                            if ((aiFlag[j].unk_00 == 1) && (aiFlag[j].unk_01 == 0) && ((aiFlag[j].unk_02 - 1) == i)) {
                                if ((aiFlag[j].unk_03 == arg1) || (aiFlag[j].unk_03 == (arg1 + 1))) {
                                    var_t0_3 = true;
                                    wid_data[5] += 1;
                                    j = aiFlagCnt;
                                }
                            }
                        }

                        if (!var_t0_3) {
                            var_t3 = 0;
                        }
                    }
                }
            } else {
                wid_data[3] += 1;
                if ((aif_field[arg1][i].unk_1 > 4) && (aif_field[arg1][i].unk_1 < 8)) {
                    wid_data[4]++;
                    if (arg1 < 4) {
                        wid_data[8] += BadLineRate[arg1][i];
                    }
                } else if (arg1 < 4) {
                    wid_data[7] += BadLineRate[arg1][i];
                }

                if (var_t4) {
                    wid_data[2]++;
                }

                if (var_t3 != 0) {
                    wid_data[5]++;
                }
            }
        }

        wid_data[2]++;
        wid_data[3]++;
        wid_data[5]++;
    }

    var_t4 = false;
    if (hei_data[2] >= 4) {
        var_t4 = true;
        hei_data[0] = 1;
        if (hei_data[2] == 8) {
            hei_data[0] = 2;
        }
    }

    if (wid_data[2] >= 4) {
        var_t4 = true;
        wid_data[0] = 1;
        if (wid_data[2] == 8) {
            wid_data[0] = 2;
        }
    }

    if (var_t4) {
        if (hei_data[0] != 0) {
            if (wid_data[0] == 0) {
                wid_data[9] = 1;
            }
        } else {
            hei_data[9] = 1;
        }
    }

    return var_t4;
}
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/aiset", aifMiniPointK3);
#endif

extern s16 pri_point[];

extern s16 HeiLinesAllp[];
extern s16 WidLinesAllp[];

#if VERSION_CN
s32 aifMiniPointK3(u8 *arg0, u8 arg1, u8 *arg2, u8 arg3, u8 arg4, u8 arg5) {
    s32 var_t1 = 0;
    s32 i;

    if (arg0[0] != 0) {
        *arg2 += arg0[0];
        arg0[7] = 0;
        arg0[8] = 0;

        for (i = 1; i < 9; i++) {
            var_t1 += arg0[i] * pri_point[i];
        }
    } else if (arg0[9] == 0) {
        if (arg0[5] >= 4) {
            if (arg3) {
                if ((arg5 == 0) || (arg4 != 0) || (arg0[3] >= 3)) {
                    var_t1 = HeiLinesAllp[arg0[3]];
                }
            } else {
                if ((arg5 == 0) || (arg4 != 1) || (arg0[3] >= 3)) {
                    var_t1 = WidLinesAllp[arg0[3]];
                }
            }
            var_t1 += arg0[4] * pri_point[4];
        }
    }

    if (arg1 == 1) {
        var_t1 /= 3;
    }

    return var_t1;
}
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/aiset", aifMiniAloneCapNumber);
#endif

#if VERSION_CN
s32 aifMiniAloneCapNumber(u8 arg0, u8 arg1, u8 arg2, s32 arg3) {
    s32 var_t0 = 0;
    s32 temp = aif_field[arg1 + 1][arg0].unk_1;

    if ((((hei_data[2] == 1) || ((hei_data[2] != 0) && (hei_data[5] < 4))) &&
         ((wid_data[2] == 1) || ((wid_data[2] != 0) && (wid_data[5] < 4)))) ||
        ((arg3 == 1) && (hei_data[2] != 0) && (wid_data[2] != 0) &&
         ((hei_data[5] >= 4) ? hei_data[2] : 0) + ((wid_data[5] >= 4) ? wid_data[2] : 0) < 4)) {
        if (arg1 == 0x10) {
            var_t0 = 1;
        } else if (arg2 != 0) {
            if (temp >= 5) {
                var_t0 = 3;
            } else {
                var_t0 = 2;
            }
        } else {
            if (temp >= 5) {
                var_t0 = 5;
            } else {
                var_t0 = 4;
            }
        }
    }

    return var_t0;
}
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/aiset", aifMiniAloneCapNumberW);
#endif

#if VERSION_CN
s32 aifMiniAloneCapNumberW(u8 arg0, u8 arg1, u8 arg2, s32 arg3) {
    s32 var_v1 = 0;
    s32 temp = aif_field[arg1 + 1][arg0].unk_1;

    if ((wid_data[2] == 1) || ((arg3 == 1) && (wid_data[2] == 2))) {
        if (arg1 == 0x10) {
            var_v1 = 1;
        } else if (arg2 != 0) {
            if (temp >= 5) {
                var_v1 = 3;
            } else {
                var_v1 = 2;
            }
        } else {
            if (temp >= 5) {
                var_v1 = 5;
            } else {
                var_v1 = 4;
            }
        }
    }

    return var_v1;
}
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/aiset", flash_virus);
#endif

#if VERSION_CN
s32 flash_virus(s32 arg0, s32 arg1) {
    s32 i;

    for (i = 0; i < pGameState->unk_164; i++) {
        if ((pGameState->unk_0D4.unk_00[i].unk_8 >= 0) && (arg0 == pGameState->unk_0D4.unk_00[i].unk_0) &&
            (arg1 == pGameState->unk_0D4.unk_00[i].unk_4)) {
            return pGameState->unk_0D4.unk_00[i].unk_8;
        }
    }

    return -1;
}
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/aiset", search_Vflash);
#endif

#if VERSION_CN
bool search_Vflash(s32 arg0, s32 arg1, s32 arg2) {
    s32 i;

    for (i = arg1 + 1; i <= arg1 + 3; i++) {
        if (i >= GAME_MAP_ROWS) {
            return false;
        }

        if (aiFieldData[i][arg0].unk_0 != 3) {
            if (aiFieldData[i][arg0].unk_0 == arg2) {
                s32 j;

                for (j = 0; j < pGameState->unk_164; j++) {
                    if (pGameState->unk_0D4.unk_00[j].unk_8 >= 0) {
                        if (arg0 == pGameState->unk_0D4.unk_00[j].unk_0) {
                            return true;
                        }
                    }
                }
            }
            break;
        }
    }

    return false;
}
#endif

#if VERSION_US
// no original name :c
INCLUDE_ASM("asm/us/nonmatchings/main_segment/aiset", func_8003151C);
#endif

#if VERSION_CN
bool func_800336A4_cn(s32 arg0 UNUSED, s32 arg1) {
    s32 i;

    for (i = 0; i < pGameState->unk_164; i++) {
        if ((pGameState->unk_0D4.unk_00[i].unk_8 >= 0) && (arg1 == pGameState->unk_0D4.unk_00[i].unk_4)) {
            return true;
        }
    }

    return false;
}
#endif

#if VERSION_US
/**
 * Original name: aifSearchLineMS
 */
INCLUDE_ASM("asm/us/nonmatchings/main_segment/aiset", aifSearchLineMS);
#endif

#if VERSION_CN
#if 0
s32 aifEraseLineCore(s32, s32);                     /* extern */
s32 aifSearchLineCore(s32, s32, ?, s8 *);            /* extern */
s32 aifMiniPointK3(s8 *, u8, s8 *, ?, s32, s32);  /* extern */
s8 aifMiniAloneCapNumber(s32, s32, s32, s32);            /* extern */
s8 aifMiniAloneCapNumberW(s32, s32, s32, s32);            /* extern */
s32 flash_virus(s32, s32);                     /* extern */
s32 search_Vflash(s32, s32, s32, s8 *);          /* extern */
extern u8 aiWall;
extern s32 OnVirusP_org;
extern ? hei_data;
extern ? wid_data;
extern ? bad_point;
extern ? bad_point2;
extern ? EraseLinP;
extern f32 HeiEraseLinRate;
extern f32 WidEraseLinRate;
extern ? AloneCapP;
extern ? AloneCapWP;
extern s32 OnVirusP;
extern s16 LPriP;
extern ? WallRate;

s32 aifSearchLineMS(struct_aiFlag *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7) {
    ? sp20;
    s32 sp28;
    s32 sp2C;
    s32 sp30;
    u8 *sp34;
    s32 sp38;
    s32 sp3C;
    s32 sp40;
    s8 *sp44;
    s8 *sp48;
    ? var_a2_3;
    s16 temp_a0_8;
    s16 temp_v0_11;
    s16 temp_v1_5;
    s16 temp_v1_6;
    s32 temp_a0_3;
    s32 temp_a0_4;
    s32 temp_a0_6;
    s32 temp_a0_7;
    s32 temp_a1_3;
    s32 temp_a1_6;
    s32 temp_a3_2;
    s32 temp_fp_2;
    s32 temp_s0;
    s32 temp_s0_2;
    s32 temp_s0_3;
    s32 temp_s1;
    s32 temp_s1_2;
    s32 temp_s2;
    s32 temp_s2_2;
    s32 temp_s6;
    s32 temp_t8_3;
    s32 temp_v0_10;
    s32 temp_v0_2;
    s32 temp_v0_4;
    s32 temp_v0_5;
    s32 temp_v0_6;
    s32 temp_v0_7;
    s32 temp_v0_9;
    s32 temp_v1_7;
    s32 var_a0;
    s32 var_a1_2;
    s32 var_a2;
    s32 var_a2_2;
    s32 var_a2_4;
    s32 var_a2_5;
    s32 var_a2_6;
    s32 var_a2_7;
    s32 var_a2_8;
    s32 var_lo;
    s32 var_s0_2;
    s32 var_s0_3;
    s32 var_s0_4;
    s32 var_s1;
    s32 var_s1_10;
    s32 var_s1_2;
    s32 var_s1_3;
    s32 var_s1_4;
    s32 var_s1_5;
    s32 var_s1_6;
    s32 var_s1_7;
    s32 var_s1_8;
    s32 var_s1_9;
    s32 var_s2;
    s32 var_s4;
    s32 var_s4_2;
    s32 var_s7;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v0_3;
    s32 var_v0_4;
    s32 var_v0_5;
    s8 *temp_a0;
    s8 *temp_a1;
    s8 *temp_a1_2;
    s8 *temp_a1_4;
    s8 *temp_fp;
    s8 *temp_s1_3;
    s8 *temp_s5;
    s8 *temp_t8;
    s8 *temp_t8_2;
    s8 *temp_v0;
    s8 *temp_v1;
    s8 *temp_v1_2;
    s8 *temp_v1_4;
    s8 *var_a3;
    s8 var_s0;
    u8 *temp_a1_5;
    u8 *temp_a2;
    u8 *temp_a3;
    u8 *temp_s2_3;
    u8 *temp_t3;
    u8 *temp_v0_3;
    u8 *temp_v0_8;
    u8 *var_a0_2;
    u8 *var_a0_3;
    u8 *var_a1;
    u8 *var_a2_9;
    u8 *var_a3_2;
    u8 *var_v1;
    u8 *var_v1_10;
    u8 *var_v1_2;
    u8 *var_v1_3;
    u8 *var_v1_4;
    u8 *var_v1_5;
    u8 *var_v1_6;
    u8 *var_v1_7;
    u8 *var_v1_8;
    u8 *var_v1_9;
    u8 temp_a0_2;
    u8 temp_a0_5;
    u8 temp_a2_2;
    u8 temp_a2_3;
    u8 temp_v1_8;
    void *temp_v1_3;

    var_s4 = 0;
    var_a2 = 0;
    temp_t8 = &arg0->unk_0C[0x18];
    temp_s5 = &arg0->unk_0C[4];
    sp44 = temp_t8;
    temp_t8_2 = &arg0->unk_0C[0x22];
    var_s7 = arg5;
    temp_fp = &arg0->unk_0C[0xE];
    sp48 = temp_t8_2;
    sp30 = var_s7;
    do {
        temp_a1 = &temp_t8[var_a2];
        temp_a0 = &temp_s5[var_a2];
        temp_v1 = &temp_t8_2[var_a2];
        temp_v0 = &temp_fp[var_a2];
        var_a2 += 1;
        *temp_v0 = 0;
        *temp_v1 = 0;
        *temp_a0 = 0;
        *temp_a1 = 0;
    } while (var_a2 < 0xA);
    arg0->unk_0C[0x2D] = 0;
    arg0->unk_0C[0x2C] = 0;
    arg0->unk_3C[2] = 0;
    arg0->unk_0C[0x2F] = 0;
    arg0->unk_0C[0x2E] = 0;
    arg0->unk_3C[1] = 0;
    arg0->unk_3C[0] = 0;
    temp_v0_2 = aifSearchLineCore(arg1, arg2, 0, temp_fp);
    sp2C = 0;
    sp28 = temp_v0_2;
    if (aifEraseLineCore(arg1, arg2) != 0) {
        var_s4 = 1;
        arg0->unk_08 += 0x2710;
    }
    var_a2_2 = 0;
    if (sp28 == 0) {
        temp_s1 = arg1 & 0xFF;
        temp_s0 = arg2 & 0xFF;
        arg0->unk_0C[0x2E] = aifMiniAloneCapNumber(temp_s1, temp_s0, 0, arg7);
        arg0->unk_3C[0] = aifMiniAloneCapNumberW(temp_s1, temp_s0, 0, arg7);
        var_a2_2 = 0;
    }
    var_a3 = sp44;
    do {
        temp_v1_2 = &temp_s5[var_a2_2];
        temp_a1_2 = &var_a3[var_a2_2];
        temp_a0_2 = *(var_a2_2 + &hei_data);
        temp_v0_3 = var_a2_2 + &wid_data;
        var_a2_2 += 1;
        *temp_v1_2 = (s8) temp_a0_2;
        *temp_a1_2 = (s8) *temp_v0_3;
    } while (var_a2_2 < 0xA);
    temp_s2 = var_s7 * 0x10;
    temp_s6 = arg4 * 2;
    sp40 = temp_s6;
    sp34 = &aif_field[0][0].unk_1;
    if ((&aif_field[0][0].unk_1)[temp_s6 + temp_s2] != 0xA) {
        var_a2_3 = 0;
        if (arg7 != 0) {
            var_a2_3 = 1;
            if (arg0->unk_01 == 0) {
                var_a2_3 = 2;
            }
        }
        var_s0 = 0;
        temp_v0_4 = aifSearchLineCore(arg4, var_s7, var_a2_3, var_a3);
        sp2C = temp_v0_4;
        if (temp_v0_4 == 0) {
            if (sp28 != 0) {
                var_s1 = 0x10;
                if (var_s7 < 0x10) {
                    temp_t3 = &aif_field[0][0].unk_1 - 1;
                    var_a3_2 = temp_s6 + temp_t3 + 0x100;
                    temp_v1_3 = temp_s6 + &aif_field[0][0].unk_1;
                    var_a1 = temp_v1_3 + 0x100;
                    do {
                        if (*var_a1 == 4) {
                            var_a2_4 = var_s1 + 1;
                            temp_a0_3 = var_a2_4;
                            if (var_a2_4 < 0x11) {
                                var_v1 = (var_a2_4 * 0x10) + temp_v1_3;
loop_19:
                                if (*var_v1 == 0xA) {
                                    var_a2_4 += 1;
                                    var_v1 += 0x10;
                                    if (var_a2_4 < 0x11) {
                                        goto loop_19;
                                    }
                                }
                            }
                            if (var_a2_4 != temp_a0_3) {
                                temp_v0_5 = temp_s6 + ((var_a2_4 - 1) * 0x10);
                                (&aif_field[0][0].unk_1)[temp_v0_5] = 4;
                                temp_t3[temp_v0_5] = *var_a3_2;
                                *var_a1 = 0xA;
                                *var_a3_2 = 3;
                            }
                        }
                        var_a3_2 -= 0x10;
                        var_s1 -= 1;
                        var_a1 -= 0x10;
                    } while (var_s7 < var_s1);
                }
            }
            var_a2_5 = var_s7 + 1;
            temp_a1_3 = var_a2_5;
            if (var_a2_5 < 0x11) {
                var_v1_2 = (var_a2_5 * 0x10) + (temp_s6 + &aif_field[0][0].unk_1);
loop_26:
                if (*var_v1_2 == 0xA) {
                    var_a2_5 += 1;
                    var_v1_2 += 0x10;
                    if (var_a2_5 < 0x11) {
                        goto loop_26;
                    }
                }
            }
            temp_v0_6 = var_a2_5 - 1;
            if (var_a2_5 != temp_a1_3) {
                var_s7 = temp_v0_6;
                temp_v0_7 = temp_s6 + (temp_v0_6 * 0x10);
                temp_a0_4 = temp_s6 + temp_s2;
                temp_a2 = sp34 - 1;
                temp_a3 = &temp_a2[temp_a0_4];
                sp34[temp_v0_7] = 4;
                temp_a2[temp_v0_7] = *temp_a3;
                sp34[temp_a0_4] = 0xA;
                *temp_a3 = 3;
                var_s0 = 1;
                if (sp28 == 0) {
                    arg0->unk_3C[2] = 1;
                }
                sp2C = aifSearchLineCore(arg4, var_s7, 0, (s8 *) temp_a3);
            }
        }
        if (aifEraseLineCore(arg4, var_s7) != 0) {
            var_s4 = 1;
            arg0->unk_08 += 0x2710;
        }
        var_a2_6 = 0;
        if (sp2C == 0) {
            temp_s1_2 = var_s7 & 0xFF;
            temp_s0_2 = var_s0 & 0xFF;
            temp_s2_2 = arg4 & 0xFF;
            arg0->unk_0C[0x2F] = aifMiniAloneCapNumber(temp_s2_2, temp_s1_2, temp_s0_2, arg7);
            arg0->unk_3C[1] = aifMiniAloneCapNumberW(temp_s2_2, temp_s1_2, temp_s0_2, arg7);
            var_a2_6 = 0;
        }
        var_a3 = sp48;
        do {
            temp_v1_4 = &temp_fp[var_a2_6];
            temp_a1_4 = &var_a3[var_a2_6];
            temp_a0_5 = *(var_a2_6 + &hei_data);
            temp_v0_8 = var_a2_6 + &wid_data;
            var_a2_6 += 1;
            *temp_v1_4 = (s8) temp_a0_5;
            *temp_a1_4 = (s8) *temp_v0_8;
        } while (var_a2_6 < 0xA);
    }
    if (evs_gamemode == ENUM_EVS_GAMEMODE_1) {
        OnVirusP = OnVirusP_org + 0x7D0;
        if (var_s4 == 0) {
            if (arg7 != 0) {
                if (search_Vflash(arg1, arg2, arg3, var_a3) != 0) {
                    var_s4 = 1;
                }
                if (search_Vflash(arg4, var_s7, arg6) != 0) {
                    var_s4 = 1;
                }
                if (var_s4 != 0) {
                    var_v0_2 = arg0->unk_08 + 0xBB8;
                    goto block_58;
                }
            } else if (arg0->unk_01 == evs_gamemode) {
                if (search_Vflash(arg1, arg2, arg3, var_a3) != 0) {
                    var_s4 = 1;
                }
                if (search_Vflash(arg4, var_s7, arg6) != 0) {
                    var_s4 = 1;
                }
                if (var_s4 != 0) {
                    var_v0_2 = arg0->unk_08 + 0x3E8;
block_58:
                    arg0->unk_08 = var_v0_2;
                }
            }
        }
    }
    temp_s1_3 = &arg0->unk_0C[0x2C];
    temp_s0_3 = arg7 & 0xFF;
    temp_a2_2 = (u8) arg0->unk_3C[2];
    arg0->unk_08 += aifMiniPointK3(temp_s5, 0U, temp_s1_3, 1, (s32) arg0->unk_01, temp_s0_3);
    arg0->unk_08 += aifMiniPointK3(temp_fp, temp_a2_2, arg0 + (temp_a2_2 + 0x38), 1, (s32) arg0->unk_01, temp_s0_3);
    temp_a2_3 = (u8) arg0->unk_3C[2];
    arg0->unk_08 += aifMiniPointK3(sp44, 0U, temp_s1_3, 0, (s32) arg0->unk_01, temp_s0_3);
    temp_v0_9 = arg0->unk_08 + aifMiniPointK3(sp48, temp_a2_3, arg0 + (temp_a2_3 + 0x38), 0, (s32) arg0->unk_01, temp_s0_3);
    arg0->unk_08 = temp_v0_9;
    temp_v1_5 = *(&AloneCapP + ((u8) arg0->unk_0C[0x2E] * 2));
    if (temp_v1_5 != 0) {
        arg0->unk_08 = temp_v0_9 + temp_v1_5;
    }
    temp_v1_6 = *(((u8) arg0->unk_0C[0x2F] * 2) + &AloneCapP);
    if (temp_v1_6 != 0) {
        arg0->unk_08 += temp_v1_6;
    }
    if ((*(((u8) arg0->unk_0C[0x2E] * 2) + &AloneCapP) != 0) && (*(((u8) arg0->unk_0C[0x2F] * 2) + &AloneCapP) != 0)) {
        arg0->unk_08 -= (0x11 - arg2) * LPriP;
    }
    if (*(&AloneCapWP + ((u8) arg0->unk_3C[0] * 2)) != 0) {
        arg0->unk_08 += *(((u8) arg0->unk_0C[0x2E] * 2) + &AloneCapWP);
    }
    if (*(((u8) arg0->unk_3C[1] * 2) + &AloneCapWP) != 0) {
        arg0->unk_08 += *(((u8) arg0->unk_0C[0x2F] * 2) + &AloneCapWP);
    }
    temp_v1_7 = arg0->unk_08 + (s32) ((f32) *(&EraseLinP + (((u8) arg0->unk_0C[4] + (u8) arg0->unk_0C[0xE]) * 2)) * HeiEraseLinRate);
    arg0->unk_08 = temp_v1_7;
    arg0->unk_08 = temp_v1_7 + (s32) ((f32) *(&EraseLinP + (((u8) arg0->unk_0C[0x18] + (u8) arg0->unk_0C[0x22]) * 2)) * WidEraseLinRate);
    if ((OnVirusP != 0) && (temp_t8_3 = arg2 < 0x10, sp38 = temp_t8_3, (temp_t8_3 != 0))) {
        var_s0_2 = 1;
        var_s1_2 = arg2 - 1;
        temp_fp_2 = arg1 * 2;
        if (var_s1_2 >= 4) {
            var_v1_3 = (var_s1_2 * 0x10) + (temp_fp_2 + &aiFieldData[0][0].unk_1);
loop_74:
            var_s1_2 -= 1;
            if ((u32) (*var_v1_3 - 5) >= 3U) {
                var_v1_3 -= 0x10;
                if (var_s1_2 >= 4) {
                    goto loop_74;
                }
            } else {
                var_s0_2 = 0;
            }
        }
        if (var_s0_2 == 1) {
            var_s1_3 = arg2 + 1;
            var_s0_2 = 0;
            if (var_s1_3 < 0x11) {
                var_v1_4 = (var_s1_3 * 0x10) + (temp_fp_2 + &aiFieldData[0][0].unk_1);
loop_79:
                var_s1_3 += 1;
                if ((u32) (*var_v1_4 - 5) >= 3U) {
                    var_v1_4 += 0x10;
                    if (var_s1_3 < 0x11) {
                        goto loop_79;
                    }
                } else {
                    var_s0_2 = 1;
                }
            }
        }
        var_s2 = 1;
        var_s1_4 = sp30 - 1;
        sp3C = arg2 + 1;
        if (var_s1_4 >= 4) {
            var_v1_5 = (var_s1_4 * 0x10) + (temp_s6 + &aiFieldData[0][0].unk_1);
loop_84:
            var_s1_4 -= 1;
            if ((u32) (*var_v1_5 - 5) >= 3U) {
                var_v1_5 -= 0x10;
                if (var_s1_4 >= 4) {
                    goto loop_84;
                }
            } else {
                var_s2 = 0;
            }
        }
        if (var_s2 != 0) {
            var_s1_5 = sp30 + 1;
            var_s2 = 0;
            if (var_s1_5 < 0x11) {
                var_v1_6 = (var_s1_5 * 0x10) + (temp_s6 + &aiFieldData[0][0].unk_1);
loop_89:
                var_s1_5 += 1;
                if ((u32) (*var_v1_6 - 5) >= 3U) {
                    var_v1_6 += 0x10;
                    if (var_s1_5 < 0x11) {
                        goto loop_89;
                    }
                } else {
                    var_s2 = 1;
                }
            }
        }
        var_s4_2 = 0;
        if (evs_gamemode == ENUM_EVS_GAMEMODE_1) {
            if (var_s0_2 != 0) {
                var_s1_6 = sp3C;
                if (var_s1_6 < 0x11) {
                    do {
                        var_s1_6 += 1;
                        if (flash_virus(arg1, var_s1_6) != -1) {
                            var_s4_2 += OnVirusP;
                        }
                    } while (var_s1_6 < 0x11);
                }
            }
            if (var_s2 != 0) {
                var_s1_7 = sp30 + 1;
                if (var_s1_7 < 0x11) {
                    do {
                        var_s1_7 += 1;
                        if (flash_virus(arg4, var_s1_7) != -1) {
                            var_s4_2 += OnVirusP;
                        }
                    } while (var_s1_7 < 0x11);
                }
            }
        }
        if ((u8) (&aiFieldData[0][0].unk_1)[temp_fp_2 + (sp3C * 0x10)] < 8U) {
            if (var_s0_2 != 0) {
                temp_v1_8 = (u8) arg0->unk_0C[6];
                if (arg7 != 0) {
                    var_v0_3 = (s32) temp_v1_8 < 2;
                    if (arg0->unk_01 == 0) {
                        if ((s32) temp_v1_8 < 3) {
                            goto block_128;
                        }
                        goto block_113;
                    }
                    goto block_112;
                }
                var_v0_3 = (s32) temp_v1_8 < 2;
block_112:
                if (var_v0_3 == 0) {
block_113:
                    if ((u8) arg0->unk_0C[9] >= 4U) {
                        if (arg0->unk_01 == 0) {
                            if (arg7 != 0) {
                                arg0->unk_08 += (OnVirusP + var_s4_2) * 2;
                                goto block_173;
                            }
                            if (sp28 == 0) {
                                goto block_128;
                            }
                            goto block_175;
                        }
                        if (var_s2 == 0) {
                            var_v0_4 = arg0->unk_08 + (OnVirusP + var_s4_2);
                        } else {
                            if ((u8) arg0->unk_0C[0x11] < 2U) {
                                goto block_171;
                            }
                            if ((u8) arg0->unk_0C[0x13] >= 4U) {
                                var_v0_4 = arg0->unk_08 + (OnVirusP + var_s4_2);
                            } else {
                                goto block_171;
                            }
                        }
                        goto block_172;
                    }
                    goto block_128;
                }
block_128:
                arg0->unk_08 -= OnVirusP * 2;
                goto block_173;
            }
            if (var_s2 != 0) {
                if ((u8) arg0->unk_0C[0x11] < 2U) {
                    goto block_171;
                }
                if ((u8) arg0->unk_0C[0x13] < 4U) {
                    goto block_171;
                }
                if ((u8) arg0->unk_0C[6] < 3U) {
                    goto block_171;
                }
                if ((u8) arg0->unk_0C[9] >= 4U) {
                    var_v0_4 = arg0->unk_08 + (OnVirusP + var_s4_2);
                } else {
                    goto block_171;
                }
                goto block_172;
            }
            goto block_174;
        }
        if (var_s2 != 0) {
            if ((u8) arg0->unk_0C[0x10] < 2U) {
                goto block_171;
            }
            if ((u8) arg0->unk_0C[0x13] < 4U) {
                goto block_171;
            }
            if (var_s0_2 == 0) {
                var_v0_4 = arg0->unk_08 + (OnVirusP + var_s4_2);
            } else {
                if ((u8) arg0->unk_0C[7] < 2U) {
                    goto block_171;
                }
                if ((u8) arg0->unk_0C[9] >= 4U) {
                    var_v0_4 = arg0->unk_08 + (OnVirusP + var_s4_2);
                } else {
                    goto block_171;
                }
            }
            goto block_172;
        }
        if (var_s0_2 != 0) {
            if ((u8) arg0->unk_0C[7] < 2U) {
                goto block_171;
            }
            if ((u8) arg0->unk_0C[9] < 4U) {
                goto block_171;
            }
            if ((u8) arg0->unk_0C[0x10] < 3U) {
                goto block_171;
            }
            if ((u8) arg0->unk_0C[0x13] >= 4U) {
                var_v0_4 = arg0->unk_08 + (OnVirusP + var_s4_2);
            } else {
block_171:
                var_v0_4 = arg0->unk_08 - (OnVirusP * 2);
            }
block_172:
            arg0->unk_08 = var_v0_4;
block_173:
        }
block_174:
        if (sp28 != 0) {
block_175:
            var_a0 = 0;
            if (arg7 == 0) {
                if (arg0->unk_01 == 0) {
                    var_s0_3 = sp3C;
                    if (sp38 != 0) {
                        var_a1_2 = var_s0_3 < 0x11;
                        var_a2_7 = 0;
                        if (var_a1_2 != 0) {
                            temp_a0_6 = var_s0_3 * 0x10;
                            var_v1_7 = temp_a0_6 + (temp_s6 + (&aiFieldData[0][0].unk_1 - 1));
                            var_a0_2 = temp_a0_6 + (temp_s6 + &aiFieldData[0][0].unk_1);
loop_180:
                            if ((u8) *var_a0_2 < 8U) {
                                if (*var_v1_7 == arg3) {
                                    var_v1_7 += 0x10;
                                    var_s0_3 += 1;
                                    var_a1_2 = var_s0_3 < 0x11;
                                    var_a0_2 += 0x10;
                                    if (var_a1_2 != 0) {
                                        goto loop_180;
                                    }
                                } else {
                                    goto block_184;
                                }
                            } else {
block_184:
                                var_a2_7 = 1;
                            }
                        }
                        var_a2_8 = 0;
                        if (var_a2_7 != 0) {
                            var_s1_8 = var_s0_3;
                            if (var_a1_2 != 0) {
                                var_v1_8 = (var_s0_3 * 0x10) + (temp_s6 + &aiFieldData[0][0].unk_1);
loop_189:
                                var_s1_8 += 1;
                                if ((u32) (*var_v1_8 - 5) >= 3U) {
                                    var_v1_8 += 0x10;
                                    if (var_s1_8 < 0x11) {
                                        goto loop_189;
                                    }
                                } else {
                                    var_a2_8 = 1;
                                }
                            }
                            var_a0 = 0;
                            if (var_a2_8 != 0) {
                                var_s1_9 = var_s0_3;
                                if (var_a1_2 != 0) {
                                    temp_a0_7 = var_s0_3 * 0x10;
                                    var_v1_9 = temp_a0_7 + (temp_s6 + (&aiFieldData[0][0].unk_1 - 1));
                                    var_a0_3 = temp_a0_7 + (temp_s6 + &aiFieldData[0][0].unk_1);
loop_194:
                                    if ((u8) *var_a0_3 >= 8U) {
                                        var_v1_9 += 0x10;
                                        var_s1_9 += 1;
                                        var_a0_3 += 0x10;
                                        if (var_s1_9 < 0x11) {
                                            goto loop_194;
                                        }
                                    } else if (*var_v1_9 != arg6) {
                                        arg0->unk_08 -= OnVirusP * 2;
                                    } else {
                                        arg0->unk_08 += (OnVirusP + var_s4_2) * 4;
                                    }
                                    goto block_200;
                                }
                            }
                        } else {
                            goto block_200;
                        }
                    }
                }
            }
        } else {
            goto block_200;
        }
    } else {
block_200:
        var_a0 = 0;
    }
    var_a2_9 = &aif_field[0][0].unk_1;
    do {
        var_s1_10 = 1;
        var_v1_10 = var_a2_9 + 0x10;
loop_204:
        if (*var_v1_10 == 0xA) {
            var_s1_10 += 1;
            var_v1_10 += 0x10;
            if (var_s1_10 < 0x11) {
                goto loop_204;
            }
        } else {
            *(&sp20 + var_a0) = var_s1_10 - 1;
        }
        var_a0 += 1;
        var_a2_9 += 2;
    } while (var_a0 < 8);
    temp_s2_3 = &sp20 + arg4;
    var_s0_4 = 0;
    arg0->unk_C = 0;
    if ((u8) *temp_s2_3 < 4U) {
        if ((var_s7 < 5) && (var_s7 > 0) && (sp34[temp_s6 + (var_s7 * 0x10)] != 0xA)) {
            if (((u8) arg0->unk_0C[0x10] + *temp_s2_3) < 4) {
                var_s0_4 = 1;
                arg0->unk_C = (s32) ((s16) *(&bad_point + sp40) / (s32) ((var_s7 * 2) - 1));
            }
        }
    }
    temp_a1_5 = &sp20 + arg1;
    if (((u8) *temp_a1_5 < 4U) && (arg2 < 4) && (arg2 > 0) && ((arg7 == 0) || (arg0->unk_01 != 0))) {
        temp_a3_2 = arg1 * 2;
        if ((sp34[temp_a3_2 + (arg2 * 0x10)] != 0xA) && (((u8) arg0->unk_0C[6] + *temp_a1_5) < 4)) {
            if (var_s0_4 != 0) {
                var_v0_5 = arg0->unk_C + ((*(&bad_point2 + temp_a3_2) + *(&bad_point2 + temp_s6)) - ((s16) *(temp_s6 + &bad_point) / (s32) ((var_s7 * 2) - 1)));
            } else {
                var_v0_5 = arg0->unk_C + ((s16) *(temp_a3_2 + &bad_point) / (s32) ((arg2 * 2) - 1));
            }
            arg0->unk_C = var_v0_5;
        }
    }
    temp_a1_6 = arg0->unk_08 + arg0->unk_C;
    arg0->unk_08 = temp_a1_6;
    if (aiWall != 0) {
        temp_v0_10 = aiWall * 0x10;
        temp_a0_8 = *((arg1 * 2) + temp_v0_10 + &WallRate);
        temp_v0_11 = *(temp_s6 + temp_v0_10 + &WallRate);
        var_lo = temp_a1_6 * temp_a0_8;
        if (temp_v0_11 >= temp_a0_8) {
            var_lo = temp_a1_6 * temp_v0_11;
        }
        arg0->unk_08 = var_lo / 10;
    }
    var_v0 = 1;
    if (sp28 == 0) {
        var_v0 = 2;
        if (sp2C == 0) {
            var_v0 = 0;
        }
    }
    return var_v0;
}
#else
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/aiset", aifSearchLineMS);
#endif
#endif

#if VERSION_US
/**
 * Original name: aiHiruAllPriSet
 */
#if 0
u8 aifRensaCheckCore(struct_game_state_data *, u8 *, u32, u8, s32, s32, u32, s32, s32, s32); /* extern */
s32 aifSearchLineMS(u8 *, s32, u8, s32);              /* extern */
extern u16 aiHiErB;
extern u16 B_800F3E32;
extern u16 aiHiErY;
extern u16 aiHiErR;
extern u16 aiHiEraseCtr;
extern s16 D_8008856A;
extern s16 D_800885D2;
extern s16 D_800885D4;

void aiHiruAllPriSet(struct_game_state_data *gameStateDataRef) {
    struct_game_state_data *sp2C;
    s32 sp34;
    u8 sp3F;
    s8 sp47;                                        /* compiler-managed */
    u8 sp4F;
    u8 sp57;
    u8 sp5F;
    u8 sp67;
    u8 sp6F;
    s32 sp8C;
    s32 sp90;
    s32 temp_a0_3;
    s32 temp_a0_4;
    s32 temp_fp;
    s32 temp_s0;
    s32 temp_s0_11;
    s32 temp_s0_13;
    s32 temp_s0_14;
    s32 temp_s0_3;
    s32 temp_s0_5;
    s32 temp_s0_6;
    s32 temp_s0_8;
    s32 temp_s0_9;
    s32 temp_s1;
    s32 temp_s2;
    s32 temp_s2_2;
    s32 temp_s2_3;
    s32 temp_s4;
    s32 temp_s5_2;
    s32 temp_s5_3;
    s32 temp_t4;
    s32 temp_t4_3;
    s32 temp_t4_4;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 temp_v0_5;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 var_a0;
    s32 var_a1;
    s32 var_a1_2;
    s32 var_a2_2;
    s32 var_a3;
    s32 var_s0;
    s32 var_s0_2;
    s32 var_s0_3;
    s32 var_s1_2;
    s32 var_s1_3;
    s32 var_s2;
    s32 var_s2_2;
    s32 var_s2_3;
    s32 var_s4;
    s32 var_s4_2;
    s32 var_s5;
    s32 var_t1_2;
    s32 var_v0;
    s8 temp_a0_2;
    s8 var_t1;
    u32 temp_s1_2;
    u32 temp_s1_3;
    u32 temp_s1_4;
    u32 temp_s1_5;
    u32 temp_s1_6;
    u32 temp_s1_7;
    u32 temp_s2_4;
    u32 temp_s5;
    u32 temp_s6;
    u8 *temp_s3;
    u8 temp_a0;
    u8 temp_s0_10;
    u8 temp_s0_12;
    u8 temp_s0_2;
    u8 temp_s0_4;
    u8 temp_s0_7;
    u8 temp_t4_2;
    u8 var_a2;
    u8 var_s1;
    u8 var_v1;

    sp2C = gameStateDataRef;
    sp34 = 0;
    if ((s32) aiFlagCnt > 0) {
        sp8C = 0;
        do {
            if (aiFlag[sp8C].unk_0 != 0) {
                temp_s3 = &aiFlag[sp8C];
                bcopy(aiFieldData, &aif_field, 0x110);
                var_a2 = temp_s3->unk_3;
                temp_a0 = temp_s3->unk_2;
                temp_s4 = temp_a0 - 1;
                if (temp_s3->unk_1 == 0) {
                    var_s5 = temp_s4;
                    var_s2 = var_s5;
                    temp_a0_2 = var_a2 - 1;
                    sp3F = var_a2;
                    sp47 = temp_a0_2;
                    sp57 &= -(temp_a0_2 < 1);
                    if (temp_s3->unk_4 == 0) {
                        var_s1 = aiNext[1];
                        if (temp_a0_2 > 0) {
                            sp4F = *aiNext;
                        }
                    } else {
                        var_s1 = *aiNext;
                        if (temp_a0_2 > 0) {
                            sp4F = aiNext[1];
                        }
                    }
                    if (sp3F != 0) {
                        temp_v0 = ((var_s5 & 0xFF) * 2) + (sp3F * 0x10);
                        *(&B_800FAD41 + temp_v0) = 1;
                        *(&aif_field + temp_v0) = var_s1;
                    }
                    if ((u8) sp47 != 0) {
                        temp_v0_2 = ((var_s2 & 0xFF) * 2) + ((u8) sp47 * 0x10);
                        *(&B_800FAD41 + temp_v0_2) = sp57;
                        *(&aif_field + temp_v0_2) = sp4F;
                    }
                    temp_a0_3 = temp_s4 * 2;
                    if (*(&aif_field + (temp_a0_3 + ((var_a2 - 1) * 0x10))) == *(&aif_field + (temp_a0_3 + (var_a2 * 0x10)))) {

                    }
                    var_a1 = temp_s4;
                    var_a3 = var_s1 & 0xFF;
                    sp90 = (s32) 1;
                } else {
                    var_s5 = temp_s4;
                    if (*(&B_800FAD41 + ((temp_s4 * 2) + ((var_a2 + 1) * 0x10))) != 0xA) {
                        sp3F = var_a2;
                        var_t1 = 2;
                        var_s2 = (s32) temp_a0;
                        sp47 = sp3F;
                        sp57 = 3;
                        if (temp_s3->unk_4 == 0) {
                            var_s1 = *aiNext;
                            sp4F = aiNext[1];
                        } else {
                            var_s1 = aiNext[1];
                            sp4F = *aiNext;
                        }
                    } else {
                        var_s5 = (s32) temp_a0;
                        sp3F = var_a2;
                        var_t1 = 3;
                        var_s2 = temp_s4;
                        sp47 = sp3F;
                        sp57 = 2;
                        if (temp_s3->unk_4 == 0) {
                            var_s1 = aiNext[1];
                            sp4F = *aiNext;
                        } else {
                            var_s1 = *aiNext;
                            sp4F = aiNext[1];
                        }
                    }
                    var_a3 = var_s1 & 0xFF;
                    if (var_a3 == sp4F) {

                    }
                    var_a2 = sp3F;
                    if (var_a2 != 0) {
                        temp_v0_3 = ((var_s5 & 0xFF) * 2) + (var_a2 * 0x10);
                        *(&B_800FAD41 + temp_v0_3) = var_t1;
                        *(&aif_field + temp_v0_3) = var_s1;
                    }
                    if (sp47 != 0) {
                        temp_v0_4 = ((var_s2 & 0xFF) * 2) + (sp47 * 0x10);
                        *(&B_800FAD41 + temp_v0_4) = sp57;
                        *(&aif_field + temp_v0_4) = sp4F;
                    }
                    var_a1 = var_s5 & 0xFF;
                    sp90 = (s32) var_t1;
                }
                temp_v0_5 = aifSearchLineMS(temp_s3, var_a1, var_a2, var_a3);
                var_t1_2 = sp90;
                if ((temp_v0_5 != 0) && (D_800885D2 != 0)) {
                    if (temp_v0_5 == 2) {
                        temp_s0 = var_s5;
                        var_s5 = var_s2;
                        var_s2 = temp_s0;
                        temp_t4_2 = sp47;
                        sp47 = sp3F;
                        temp_s0_2 = var_s1;
                        var_s1 = sp4F;
                        sp4F = temp_s0_2;
                        temp_s0_3 = var_t1_2;
                        var_t1_2 = (s32) sp57;
                        sp3F = temp_t4_2;
                        sp57 = (u8) temp_s0_3;
                    }
                    temp_s6 = var_s5 & 0xFF;
                    temp_fp = var_s1 & 0xFF;
                    temp_s1 = var_t1_2 & 0xFF;
                    temp_s5 = var_s2 & 0xFF;
                    sp5F = aifRensaCheckCore(sp2C, temp_s3, temp_s6, sp3F, temp_fp, temp_s1, temp_s5, (s32) sp47, 0, (s32) sp57);
                    aiHiErR = aiHiEraseCtr;
                    sp67 = aifRensaCheckCore(sp2C, temp_s3, temp_s6, sp3F, temp_fp, temp_s1, temp_s5, (s32) sp47, 1, (s32) sp57);
                    aiHiErY = aiHiEraseCtr;
                    sp6F = aifRensaCheckCore(sp2C, temp_s3, temp_s6, sp3F, temp_fp, temp_s1, temp_s5, (s32) sp47, 2, (s32) sp57);
                    aiHiErB = aiHiEraseCtr;
                    var_s0 = 0;
                    if (temp_s6 == temp_s5) {
                        temp_s2 = var_s2 - 1;
                        if (sp47 < sp3F) {
                            temp_s1_2 = temp_s2 & 0xFF;
                            sp47 += 1;
                            temp_s5_2 = (u8) sp47 * 0x10;
                            if (sp2C->unk_29C[0][0][(temp_s1_2 * 2) + temp_s5_2] == 0xA) {
                                temp_s0_4 = aifRensaCheckCore(sp2C, temp_s3, temp_s6, sp3F, temp_fp, 3, temp_s1_2, (s32) (u8) sp47, 0, 2);
                                temp_s0_5 = temp_s0_4 | aifRensaCheckCore(sp2C, temp_s3, temp_s6, sp3F, temp_fp, 3, temp_s1_2, (s32) (u8) sp47, 1, 2);
                                var_s0 = temp_s0_5 | aifRensaCheckCore(sp2C, temp_s3, temp_s6, sp3F, temp_fp, 3, temp_s1_2, (s32) (u8) sp47, 2, 2);
                            }
                            temp_s1_3 = (temp_s2 + 2) & 0xFF;
                            sp57 = 3;
                            if (sp2C->unk_29C[0][0][(temp_s1_3 * 2) + temp_s5_2] == 0xA) {
                                temp_s0_6 = var_s0 | aifRensaCheckCore(sp2C, temp_s3, temp_s6, sp3F, temp_fp, 2, temp_s1_3, (s32) (u8) sp47, 0, 3);
                                var_s0_2 = temp_s0_6 | aifRensaCheckCore(sp2C, temp_s3, temp_s6, sp3F, temp_fp, 2, temp_s1_3, (s32) (u8) sp47, 1, 3);
                                goto block_53;
                            }
                        } else {
                            temp_s1_4 = temp_s2 & 0xFF;
                            sp47 = (u8) sp47 - 1;
                            temp_s5_3 = (u8) sp47 * 0x10;
                            if (sp2C->unk_29C[0][0][(temp_s1_4 * 2) + temp_s5_3] == 0xA) {
                                temp_s0_7 = aifRensaCheckCore(sp2C, temp_s3, temp_s6, sp3F, temp_fp, 3, temp_s1_4, (s32) (u8) sp47, 0, 2);
                                temp_s0_8 = temp_s0_7 | aifRensaCheckCore(sp2C, temp_s3, temp_s6, sp3F, temp_fp, 3, temp_s1_4, (s32) (u8) sp47, 1, 2);
                                var_s0 = temp_s0_8 | aifRensaCheckCore(sp2C, temp_s3, temp_s6, sp3F, temp_fp, 3, temp_s1_4, (s32) (u8) sp47, 2, 2);
                            }
                            temp_s1_5 = (temp_s2 + 2) & 0xFF;
                            sp57 = 3;
                            if (sp2C->unk_29C[0][0][(temp_s1_5 * 2) + temp_s5_3] == 0xA) {
                                temp_s0_9 = var_s0 | aifRensaCheckCore(sp2C, temp_s3, temp_s6, sp3F, temp_fp, 2, temp_s1_5, (s32) (u8) sp47, 0, 3);
                                var_s0_2 = temp_s0_9 | aifRensaCheckCore(sp2C, temp_s3, temp_s6, sp3F, temp_fp, 2, temp_s1_5, (s32) (u8) sp47, 1, 3);
                                goto block_53;
                            }
                        }
                    } else {
                        temp_v1 = sp47 * 0x10;
                        if (temp_s5 < temp_s6) {
                            temp_s2_2 = var_s2 + 2;
                            temp_s1_6 = temp_s2_2 & 0xFF;
                            if (sp2C->unk_29C[0][0][(temp_s1_6 * 2) + temp_v1] == 0xA) {
                                temp_s0_10 = aifRensaCheckCore(sp2C, temp_s3, temp_s6, sp3F, temp_fp, 2, temp_s1_6, (s32) sp47, 0, 3);
                                temp_s0_11 = temp_s0_10 | aifRensaCheckCore(sp2C, temp_s3, temp_s6, sp3F, temp_fp, 2, temp_s1_6, (s32) sp47, 1, 3);
                                var_s0 = temp_s0_11 | aifRensaCheckCore(sp2C, temp_s3, temp_s6, sp3F, temp_fp, 2, temp_s1_6, (s32) sp47, 2, 3);
                            }
                            var_s2_2 = temp_s2_2 - 1;
                        } else {
                            temp_s2_3 = var_s2 - 2;
                            temp_s1_7 = temp_s2_3 & 0xFF;
                            if (sp2C->unk_29C[0][0][(temp_s1_7 * 2) + temp_v1] == 0xA) {
                                temp_s0_12 = aifRensaCheckCore(sp2C, temp_s3, temp_s6, sp3F, temp_fp, 3, temp_s1_7, (s32) sp47, 0, 2);
                                temp_s0_13 = temp_s0_12 | aifRensaCheckCore(sp2C, temp_s3, temp_s6, sp3F, temp_fp, 3, temp_s1_7, (s32) sp47, 1, 2);
                                var_s0 = temp_s0_13 | aifRensaCheckCore(sp2C, temp_s3, temp_s6, sp3F, temp_fp, 3, temp_s1_7, (s32) sp47, 2, 2);
                            }
                            var_s2_2 = temp_s2_3 + 1;
                        }
                        temp_s2_4 = var_s2_2 & 0xFF;
                        sp47 = (u8) sp47 - 1;
                        sp57 = 0;
                        if (sp2C->unk_29C[0][0][(temp_s2_4 * 2) + ((u8) sp47 * 0x10)] == 0xA) {
                            temp_s0_14 = var_s0 | aifRensaCheckCore(sp2C, temp_s3, temp_s6, sp3F, temp_fp, 1, temp_s2_4, (s32) (u8) sp47, 0, 0);
                            var_s0_2 = temp_s0_14 | aifRensaCheckCore(sp2C, temp_s3, temp_s6, sp3F, temp_fp, 1, temp_s2_4, (s32) (u8) sp47, 1, 0);
block_53:
                            var_s0 = var_s0_2 | aifRensaCheckCore(sp2C, temp_s3, temp_s6, sp3F);
                        }
                    }
                    switch (sp4F) {                 /* irregular */
                        case 0x0:
                            var_a1_2 = temp_s3->unk_8 + ((s16) aiHiErR * D_8008856A);
                            temp_s3->unk_8 = var_a1_2;
                            if (sp5F != 0) {
                                if ((((sp67 != 0) | (sp6F != 0)) != 0) || (var_s0 & 0xFF)) {
                                    var_v0 = var_a1_2 + (D_800885D2 * sp5F);
                                } else {
                                    var_v0 = var_a1_2 + (D_800885D2 * sp5F);
                                }
                                goto block_88;
                            }
                            var_v1 = sp67;
block_68:
                            if ((((var_v1 != 0) | (sp6F != 0)) == 0) && !(var_s0 & 0xFF)) {
                                temp_s3->unk_8 = var_a1_2;
                            } else {
block_86:
                                if (sp3F >= 3U) {
                                    var_v0 = var_a1_2 + D_800885D4;
block_88:
                                    temp_s3->unk_8 = var_v0;
                                }
                            }
                            break;
                        case 0x1:
                            var_a1_2 = temp_s3->unk_8 + ((s16) aiHiErY * D_8008856A);
                            temp_s3->unk_8 = var_a1_2;
                            if (sp67 != 0) {
                                if ((((sp5F != 0) | (sp6F != 0)) != 0) || (var_s0 & 0xFF)) {
                                    var_v0 = var_a1_2 + (D_800885D2 * sp67);
                                } else {
                                    var_v0 = var_a1_2 + (D_800885D2 * sp67);
                                }
                                goto block_88;
                            }
                            var_v1 = sp5F;
                            goto block_68;
                        case 0x2:
                            var_a1_2 = temp_s3->unk_8 + ((s16) aiHiErB * D_8008856A);
                            temp_s3->unk_8 = var_a1_2;
                            if (sp6F != 0) {
                                if ((((sp67 != 0) | (sp5F != 0)) != 0) || (var_s0 & 0xFF)) {
                                    var_v0 = var_a1_2 + (D_800885D2 * sp6F);
                                } else {
                                    var_v0 = var_a1_2 + (D_800885D2 * sp6F);
                                }
                                goto block_88;
                            }
                            if (((sp67 != 0) | (sp5F != 0)) == 0) {
                                if (!(var_s0 & 0xFF)) {
                                    temp_s3->unk_8 = var_a1_2;
                                } else {
                                    goto block_86;
                                }
                            } else {
                                goto block_86;
                            }
                            break;
                    }
                }
            } else {
                (aiFlag + 8)[sp8C] = 0xFFF0BDC0;
            }
            sp8C += 0x40;
            temp_t4 = sp34 + 1;
            sp34 = temp_t4;
        } while (temp_t4 < (s32) aiFlagCnt);
    }
    if ((u8) sp2C->unk_23E != 0) {
        var_s4 = 0xFFF0BDBF;
        var_s0_3 = 0;
        sp34 = 0;
        if ((s32) aiFlagCnt > 0) {
            var_s1_2 = 0;
            do {
                var_a2_2 = 0;
                if (B_800F3E32 != 0) {
                    var_a2_2 = genrand((s32) B_800F3E32) & 0xFFFF;
                }
                temp_v1_2 = (aiFlag + 8)[var_s1_2] + var_a2_2;
                if (var_s4 < temp_v1_2) {
                    var_s4 = temp_v1_2;
                    var_s0_3 = sp34;
                }
                var_s1_2 += 0x40;
                temp_t4_3 = sp34 + 1;
                sp34 = temp_t4_3;
            } while (temp_t4_3 < (s32) aiFlagCnt);
        }
    } else {
        var_s2_3 = 0xFFF0BDBF;
        var_s4_2 = -0xF4241;
        var_s0_3 = 0;
        sp34 = 0;
        if ((s32) aiFlagCnt > 0) {
            var_s1_3 = 0;
            do {
                if (B_800F3E32 != 0) {
                    var_a0 = (B_800F3E32 + 0x64) & 0xFFFF;
                } else {
                    var_a0 = 0x64;
                }
                temp_a0_4 = (aiFlag + 8)[var_s1_3];
                temp_v1_3 = temp_a0_4 + (genrand(var_a0) & 0xFFFF);
                if (var_s2_3 < temp_v1_3) {
                    var_s2_3 = temp_v1_3;
                    if (var_s4_2 < temp_a0_4) {
                        var_s4_2 = temp_a0_4;
                    }
                    var_s0_3 = sp34;
                }
                if (*(aiFlag + 8 + (var_s0_3 << 6)) < var_s4_2) {
                    sp2C->unk_23E = 1;
                }
                var_s1_3 += 0x40;
                temp_t4_4 = sp34 + 1;
                sp34 = temp_t4_4;
            } while (temp_t4_4 < (s32) aiFlagCnt);
        }
    }
    decide = (s8) var_s0_3;
}
#else
INCLUDE_ASM("asm/us/nonmatchings/main_segment/aiset", aiHiruAllPriSet);
#endif
#endif

extern u16 aiHiErB;
extern u16 aiPriOfs;
extern u16 aiHiErY;
extern u16 aiHiErR;
extern u16 aiHiEraseCtr;
extern s16 D_8009337A_cn; // pri_point._14_2_
extern s16 RensaP;
extern s16 RensaMP;

#if VERSION_CN
#ifdef NON_EQUIVALENT
void aiHiruAllPriSet(struct_game_state_data *gameStateDataRef) {
    s32 sp30;
    s32 sp34;
    s32 sp38;
    s32 sp3C;
    s32 sp40;
    s32 sp44;
    s32 temp_a2_2;
    s32 temp_s0;
    s32 temp_s0_2;
    s32 temp_s0_3;
    s32 temp_s1;
    s32 temp_s1_2;
    s32 temp_s1_3;
    s32 temp_s1_4;
    s32 temp_s1_5;
    s32 temp_s1_6;
    s32 temp_s1_7;
    s32 temp_s3;
    s32 temp_s3_2;
    s32 temp_s3_3;
    s32 temp_t0;
    s32 temp_v0_5;
    s32 temp_v0_6;
    s32 temp_v1;
    s32 var_s0;
    s32 var_s0_2;
    s32 var_s0_3;
    s32 var_s1;
    s32 var_s2;
    s32 var_s2_2;
    s32 var_s3;
    s32 var_s3_2;
    s32 var_s6;
    s32 var_s7;
    s32 var_t1;
    s32 var_v0_3;
    u16 var_a0;
    u16 var_a2;
    u8 temp_s0_4;
    u8 temp_s0_5;
    u8 var_s4;
    u8 var_s5;
    u8 var_v0;
    u8 var_v0_2;

    for (sp30 = 0; sp30 < aiFlagCnt; sp30++) {
        if (aiFlag[sp30].unk_00 != 0) {
            struct_aiFlag *temp = &aiFlag[sp30];

            bcopy(aiFieldData, aif_field, 0x110);
            var_t1 = 0;

            temp_s0 = temp->unk_02 - 1;
            if (temp->unk_01 == 0) {
                var_s6 = temp_s0 & 0xFF;
                var_s7 = temp->unk_03 & 0xFF;
                var_s4 = 1;
                var_s1 = var_s6;
                temp_t0 = temp->unk_03 - 1;
                var_s3 = temp_t0 & 0xFF;

                if (temp_t0 > 0) {
                    sp38 = 0;
                }

                if (temp->unk_04 == 0) {
                    var_s5 = aiNext[1];
                    if (temp_t0 > 0) {
                        var_v0 = aiNext[0];
                        sp34 = (s32)var_v0;
                    }
                } else {
                    var_s5 = aiNext[0];
                    if (temp_t0 > 0) {
                        var_v0 = aiNext[1];
                        sp34 = (s32)var_v0;
                    }
                }

                if (var_s7 != 0) {
                    aif_field[var_s7][var_s6].unk_1 = 1;
                    aif_field[var_s7][var_s6].unk_0 = var_s5;
                }

                if (var_s3 != 0) {
                    aif_field[var_s3][var_s6].unk_1 = (u8)sp38;
                    aif_field[var_s3][var_s6].unk_0 = (u8)sp34;
                }

                if (aif_field[temp_t0][temp_s0].unk_0 == aif_field[temp->unk_03][temp_s0].unk_0) {
                    var_t1 = 1;
                }
                var_s2 = aifSearchLineMS(temp, temp_s0, temp->unk_03, (s32)var_s5, temp_s0, temp_t0, sp34, var_t1);
            } else {
                var_s6 = temp_s0 & 0xFF;
                if (aif_field[temp->unk_03 + 1][temp_s0].unk_1 != 0xA) {
                    var_s7 = temp->unk_03 & 0xFF;
                    var_s4 = 2;
                    var_s1 = temp->unk_02 & 0xFF;
                    var_s3 = var_s7;
                    sp38 = 3;
                    if (temp->unk_04 != 0) {
                        var_s5 = aiNext[1];
                        var_v0_2 = aiNext[0];
                    } else {
                        var_s5 = aiNext[0];
                        var_v0_2 = aiNext[1];
                    }
                } else {
                    var_s6 = temp->unk_02 & 0xFF;
                    var_s7 = temp->unk_03 & 0xFF;
                    var_s4 = 3;
                    var_s1 = temp_s0 & 0xFF;
                    var_s3 = var_s7;
                    sp38 = 2;
                    if (temp->unk_04 == 0) {
                        var_s5 = aiNext[1];
                        var_v0_2 = aiNext[0];
                    } else {
                        var_s5 = aiNext[0];
                        var_v0_2 = aiNext[1];
                    }
                }
                sp34 = (s32)var_v0_2;
                if (var_s5 == sp34) {
                    var_t1 = 1;
                }
                if (var_s7 != 0) {
                    aif_field[var_s7][var_s6].unk_1 = var_s4;
                    aif_field[var_s7][var_s6].unk_0 = var_s5;
                }
                if (var_s3 != 0) {
                    aif_field[var_s7][var_s1].unk_1 = (u8)sp38;
                    aif_field[var_s7][var_s1].unk_0 = (u8)sp34;
                }
                var_s2 = aifSearchLineMS(temp, var_s6, var_s7, (s32)var_s5, var_s1, var_s7, sp34, var_t1);
            }

            if (var_s2 != 0) {
                if (RensaP != 0) {
                    if (var_s2 == 2) {
                        temp_s0_2 = var_s6;
                        var_s6 = var_s1;
                        var_s1 = temp_s0_2;
                        temp_s0_3 = var_s7;
                        var_s7 = var_s3;
                        var_s3 = temp_s0_3;
                        temp_s0_4 = var_s5;
                        var_s5 = (u8)sp34;
                        sp34 = (s32)temp_s0_4;
                        temp_s0_5 = var_s4;
                        var_s4 = (u8)sp38;
                        sp38 = (s32)temp_s0_5;
                    }

                    sp3C = aifRensaCheckCore(gameStateDataRef, temp, (u8)var_s6, (u8)var_s7, (u8)(s32)var_s5,
                                             (u8)(s32)var_s4, (u8)var_s1, (u8)var_s3, (u8)0, (u8)sp38) &
                           0xFF;
                    aiHiErR = aiHiEraseCtr;
                    sp40 = aifRensaCheckCore(gameStateDataRef, temp, (u8)var_s6, (u8)var_s7, (u8)(s32)var_s5,
                                             (u8)(s32)var_s4, (u8)var_s1, (u8)var_s3, (u8)1, (u8)sp38) &
                           0xFF;
                    aiHiErY = aiHiEraseCtr;
                    sp44 = aifRensaCheckCore(gameStateDataRef, temp, (u8)var_s6, (u8)var_s7, (u8)(s32)var_s5,
                                             (u8)(s32)var_s4, (u8)var_s1, (u8)var_s3, (u8)2, (u8)sp38) &
                           0xFF;
                    aiHiErB = aiHiEraseCtr;

                    var_s0 = 0;
                    if (var_s6 == var_s1) {
                        temp_v0_5 = var_s6 - 1;
                        if ((u32)var_s3 < (u32)var_s7) {
                            temp_s1 = temp_v0_5 & 0xFF;
                            temp_s3 = (var_s3 + 1) & 0xFF;
                            if (gameStateDataRef->unk_29C[temp_s3][temp_s1][0] == 0xA) {
                                // var_s0 = (var_s0 | ?
                                var_s0 =
                                    aifRensaCheckCore(gameStateDataRef, temp, (u8)var_s6, (u8)var_s7, (u8)(s32)var_s5,
                                                      (u8)3, (u8)temp_s1, (u8)temp_s3, (u8)0, (u8)2) &
                                    0xFF;
                                var_s0 = (var_s0 | aifRensaCheckCore(gameStateDataRef, temp, (u8)var_s6, (u8)var_s7,
                                                                     (u8)(s32)var_s5, (u8)3, (u8)temp_s1, (u8)temp_s3,
                                                                     (u8)1, (u8)2)) &
                                         0xFF;
                                var_s0 = (var_s0 | aifRensaCheckCore(gameStateDataRef, temp, (u8)var_s6, (u8)var_s7,
                                                                     (u8)(s32)var_s5, (u8)3, (u8)temp_s1, (u8)temp_s3,
                                                                     (u8)2, (u8)2)) &
                                         0xFF;
                            }
                            temp_s1_2 = (temp_s1 + 2) & 0xFF;
                            sp38 = 3;
                            if (gameStateDataRef->unk_29C[temp_s3][temp_s1_2][0] == 0xA) {
                                var_s0 = (var_s0 | aifRensaCheckCore(gameStateDataRef, temp, (u8)var_s6, (u8)var_s7,
                                                                     (u8)(s32)var_s5, (u8)2, (u8)temp_s1_2, (u8)temp_s3,
                                                                     (u8)0, (u8)sp38)) &
                                         0xFF;
                                var_s0 = (var_s0 | aifRensaCheckCore(gameStateDataRef, temp, (u8)var_s6, (u8)var_s7,
                                                                     (u8)(s32)var_s5, (u8)2, (u8)temp_s1_2, (u8)temp_s3,
                                                                     (u8)1, (u8)sp38)) &
                                         0xFF;
                                var_s0 = (var_s0 | aifRensaCheckCore(gameStateDataRef, temp, (u8)var_s6, (u8)var_s7,
                                                                     (u8)(s32)var_s5, (u8)2, (u8)temp_s1_2, (u8)temp_s3,
                                                                     (u8)2, (u8)sp38)) &
                                         0xFF;
                            }
                        } else {
                            temp_s1_3 = temp_v0_5 & 0xFF;
                            temp_s3_2 = (var_s3 - 1) & 0xFF;
                            if (gameStateDataRef->unk_29C[temp_s3_2][temp_s1_3][0] == 0xA) {
                                // var_s0 = (var_s0 | ?
                                var_s0 =
                                    aifRensaCheckCore(gameStateDataRef, temp, (u8)var_s6, (u8)var_s7, (u8)(s32)var_s5,
                                                      (u8)3, (u8)temp_s1_3, (u8)temp_s3_2, (u8)0, (u8)2) &
                                    0xFF;
                                var_s0 = (var_s0 | aifRensaCheckCore(gameStateDataRef, temp, (u8)var_s6, (u8)var_s7,
                                                                     (u8)(s32)var_s5, (u8)3, (u8)temp_s1_3,
                                                                     (u8)temp_s3_2, (u8)1, (u8)2)) &
                                         0xFF;
                                var_s0 = (var_s0 | aifRensaCheckCore(gameStateDataRef, temp, (u8)var_s6, (u8)var_s7,
                                                                     (u8)(s32)var_s5, (u8)3, (u8)temp_s1_3,
                                                                     (u8)temp_s3_2, (u8)2, (u8)2)) &
                                         0xFF;
                            }
                            temp_s1_4 = (temp_s1_3 + 2) & 0xFF;
                            sp38 = 3;
                            if (gameStateDataRef->unk_29C[temp_s3_2][temp_s1_4][0] == 0xA) {
                                var_s0 = (var_s0 | aifRensaCheckCore(gameStateDataRef, temp, (u8)var_s6, (u8)var_s7,
                                                                     (u8)(s32)var_s5, (u8)2, (u8)temp_s1_4,
                                                                     (u8)temp_s3_2, (u8)0, (u8)sp38)) &
                                         0xFF;
                                var_s0 = (var_s0 | aifRensaCheckCore(gameStateDataRef, temp, (u8)var_s6, (u8)var_s7,
                                                                     (u8)(s32)var_s5, (u8)2, (u8)temp_s1_4,
                                                                     (u8)temp_s3_2, (u8)1, (u8)sp38)) &
                                         0xFF;
                                var_s0 = (var_s0 | aifRensaCheckCore(gameStateDataRef, temp, (u8)var_s6, (u8)var_s7,
                                                                     (u8)(s32)var_s5, (u8)2, (u8)temp_s1_4,
                                                                     (u8)temp_s3_2, (u8)2, (u8)sp38)) &
                                         0xFF;
                            }
                        }
                    } else {
                        if ((u32)var_s1 < (u32)var_s6) {
                            temp_s1_5 = (var_s1 + 2) & 0xFF;
                            sp38 = 3;
                            if (gameStateDataRef->unk_29C[var_s3][temp_s1_5][0] == 0xA) {
                                var_s0 =
                                    aifRensaCheckCore(gameStateDataRef, temp, (u8)var_s6, (u8)var_s7, (u8)(s32)var_s5,
                                                      (u8)2, (u8)temp_s1_5, (u8)var_s3, (u8)0, (u8)sp38) &
                                    0xFF;
                                var_s0 = (var_s0 | aifRensaCheckCore(gameStateDataRef, temp, (u8)var_s6, (u8)var_s7,
                                                                     (u8)(s32)var_s5, (u8)2, (u8)temp_s1_5, (u8)var_s3,
                                                                     (u8)1, (u8)sp38)) &
                                         0xFF;
                                var_s0 = (var_s0 | aifRensaCheckCore(gameStateDataRef, temp, (u8)var_s6, (u8)var_s7,
                                                                     (u8)(s32)var_s5, (u8)2, (u8)temp_s1_5, (u8)var_s3,
                                                                     (u8)2, (u8)sp38)) &
                                         0xFF;
                            }
                            var_v0_3 = temp_s1_5 - 1;
                        } else {
                            temp_s1_6 = (var_s1 - 2) & 0xFF;
                            if (gameStateDataRef->unk_29C[var_s3][temp_s1_6][0] == 0xA) {
                                var_s0 =
                                    aifRensaCheckCore(gameStateDataRef, temp, (u8)var_s6, (u8)var_s7, (u8)(s32)var_s5,
                                                      (u8)3, (u8)temp_s1_6, (u8)var_s3, (u8)0, (u8)2) &
                                    0xFF;
                                var_s0 = (var_s0 | aifRensaCheckCore(gameStateDataRef, temp, (u8)var_s6, (u8)var_s7,
                                                                     (u8)(s32)var_s5, (u8)3, (u8)temp_s1_6, (u8)var_s3,
                                                                     (u8)1, (u8)2)) &
                                         0xFF;
                                var_s0 = (var_s0 | aifRensaCheckCore(gameStateDataRef, temp, (u8)var_s6, (u8)var_s7,
                                                                     (u8)(s32)var_s5, (u8)3, (u8)temp_s1_6, (u8)var_s3,
                                                                     (u8)2, (u8)2)) &
                                         0xFF;
                            }
                            var_v0_3 = temp_s1_6 + 1;
                        }
                        temp_s1_7 = var_v0_3 & 0xFF;
                        temp_s3_3 = (var_s3 - 1) & 0xFF;
                        sp38 = 0;
                        if (gameStateDataRef->unk_29C[temp_s3_3][temp_s1_7][0] == 0xA) {
                            var_s0 = (var_s0 | aifRensaCheckCore(gameStateDataRef, temp, (u8)var_s6, (u8)var_s7,
                                                                 (u8)(s32)var_s5, (u8)1, (u8)temp_s1_7, (u8)temp_s3_3,
                                                                 (u8)0, (u8)0)) &
                                     0xFF;
                            var_s0 = (var_s0 | aifRensaCheckCore(gameStateDataRef, temp, (u8)var_s6, (u8)var_s7,
                                                                 (u8)(s32)var_s5, (u8)1, (u8)temp_s1_7, (u8)temp_s3_3,
                                                                 (u8)1, (u8)0)) &
                                     0xFF;
                            var_s0 = (var_s0 | aifRensaCheckCore(gameStateDataRef, temp, (u8)var_s6, (u8)var_s7,
                                                                 (u8)(s32)var_s5, (u8)1, (u8)temp_s1_7, (u8)temp_s3_3,
                                                                 (u8)2, (u8)0)) &
                                     0xFF;
                        }
                    }

                    switch (sp34) {
                        case 0:
                            temp->unk_08 += ((s16)aiHiErR * D_8009337A_cn);
                            if (sp3C != 0) {
                                if ((sp40 != 0) || (sp44 != 0) || (var_s0 != 0)) {
                                    temp->unk_08 += RensaP * sp3C;
                                } else {
                                    temp->unk_08 += RensaP * sp3C;
                                }
                            } else {
                                if ((sp40 == 0) && (sp44 == 0)) {
                                    if (var_s0 != 0) {
                                        if (var_s7 >= 3U) {
                                            temp->unk_08 += RensaMP;
                                        }
                                    }
                                } else {
                                    if (var_s7 >= 3U) {
                                        temp->unk_08 += RensaMP;
                                    }
                                }
                            }
                            break;

                        case 1:
                            temp->unk_08 += ((s16)aiHiErY * D_8009337A_cn);
                            if (sp40 != 0) {
                                if ((sp3C != 0) || (sp44 != 0) || (var_s0 != 0)) {
                                    temp->unk_08 += RensaP * sp40;
                                } else {
                                    temp->unk_08 += RensaP * sp40;
                                }
                            } else {
                                if ((sp3C == 0) && (sp44 == 0)) {
                                    if (var_s0 != 0) {
                                        if (var_s7 >= 3U) {
                                            temp->unk_08 += RensaMP;
                                        }
                                    }
                                } else {
                                    if (var_s7 >= 3U) {
                                        temp->unk_08 += RensaMP;
                                    }
                                }
                            }
                            break;

                        case 2:
                            temp->unk_08 += ((s16)aiHiErB * D_8009337A_cn);
                            if (sp44 != 0) {
                                if ((sp40 != 0) || (sp3C != 0) || (var_s0 != 0)) {
                                    temp->unk_08 += RensaP * sp44;
                                } else {
                                    temp->unk_08 += RensaP * sp44;
                                }
                            } else {
                                if ((sp40 == 0) && (sp3C == 0)) {
                                    if (var_s0 != 0) {
                                        if (var_s7 >= 3U) {
                                            temp->unk_08 += RensaMP;
                                        }
                                    }
                                } else {
                                    if (var_s7 >= 3U) {
                                        temp->unk_08 += RensaMP;
                                    }
                                }
                            }
                            break;
                    }
                }
            }
        } else {
            aiFlag[sp30].unk_08 = -0xF4240;
        }
    }

    if (gameStateDataRef->unk_23E != 0) {
        var_s0_2 = -0xF4241;
        var_s2_2 = 0;

        for (sp30 = 0; sp30 < aiFlagCnt; sp30++) {
            if (aiPriOfs != 0) {
                var_a2 = genrand(aiPriOfs);
            } else {
                var_a2 = 0;
            }
            temp_v0_6 = aiFlag[sp30].unk_08 + var_a2;
            if (var_s0_2 < temp_v0_6) {
                var_s0_2 = temp_v0_6;
                var_s2_2 = sp30;
            }
        }
    } else {
        var_s3_2 = -0xF4241;
        var_s0_3 = -0xF4241;
        var_s2_2 = 0;

        for (sp30 = 0; sp30 < aiFlagCnt; sp30++) {
            if (aiPriOfs != 0) {
                var_a0 = (aiPriOfs + 0x64) & 0xFFFF;
            } else {
                var_a0 = 0x64;
            }
            temp_v1 = aiFlag[sp30].unk_08;
            temp_a2_2 = temp_v1 + genrand(var_a0);
            if (var_s3_2 < temp_a2_2) {
                var_s3_2 = temp_a2_2;
                if (var_s0_3 < temp_v1) {
                    var_s0_3 = temp_v1;
                }
                var_s2_2 = sp30;
            }

            if (aiFlag[sp30].unk_08 < var_s0_3) {
                gameStateDataRef->unk_23E = 1;
            }
        }
    }

    decide = (u8)var_s2_2;
}
#else
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/aiset", aiHiruAllPriSet);
#endif
#endif

#if VERSION_US
/**
 * Original name: aiSetCharacter
 */
INCLUDE_ASM("asm/us/nonmatchings/main_segment/aiset", aiSetCharacter);
#endif

#if VERSION_CN
#if 0
extern s8 aiWall;
extern s16 aiPriOfs;
extern s32 OnVirusP_org;
extern ? D_80093374_cn;
extern ? D_8009337A_cn;
extern ? EraseLinP;
extern ? D_80093382_cn;
extern f32 HeiEraseLinRate;
extern f32 WidEraseLinRate;
extern ? D_800933A0_cn;
extern ? D_800933B4_cn;
extern ? D_800933C8_cn;
extern ? D_800933D2_cn;
extern s32 OnVirusP;
extern u16 RensaP;
extern u16 RensaMP;
extern u16 LPriP;

void aiSetCharacter(struct_game_state_data *gameStateDataRef) {
    s16 *temp_a0;
    s16 *temp_s4;
    s16 *var_v1_8;
    s16 temp_a0_2;
    s16 temp_v1_5;
    s16 var_v0_4;
    s32 temp_a0_3;
    s32 var_a1_2;
    s32 var_a1_3;
    s32 var_a1_4;
    s32 var_a1_5;
    s32 var_a1_6;
    s32 var_a1_7;
    s32 var_a2_3;
    s32 var_a3_4;
    s32 var_s0;
    s32 var_s0_2;
    s32 var_s0_3;
    s32 var_s0_4;
    s32 var_s0_5;
    s32 var_s0_6;
    s32 var_s3;
    s32 var_s5;
    s32 var_t1;
    s32 var_t1_2;
    s32 var_t1_3;
    s32 var_t1_4;
    s32 var_t1_5;
    s32 var_t3_2;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v0_6;
    s32 var_v0_7;
    s32 var_v1;
    s32 var_v1_2;
    s32 var_v1_3;
    s32 var_v1_4;
    s8 *var_a0_7;
    s8 temp_v1_2;
    s8 var_s6;
    s8 var_v1_7;
    struct_ai_char_data *temp_s2;
    struct_ai_param *temp_t1;
    u16 *var_a3_5;
    u16 temp_v0_4;
    u16 temp_v1_6;
    u16 temp_v1_7;
    u8 *temp_a1;
    u8 *temp_s3;
    u8 *temp_v0;
    u8 *temp_v0_3;
    u8 *var_a0;
    u8 *var_a0_2;
    u8 *var_a0_3;
    u8 *var_a0_4;
    u8 *var_a0_5;
    u8 *var_a0_6;
    u8 *var_a0_9;
    u8 *var_a1;
    u8 *var_a2;
    u8 *var_a2_2;
    u8 *var_a2_4;
    u8 *var_a2_5;
    u8 *var_a3;
    u8 *var_a3_2;
    u8 *var_a3_3;
    u8 *var_t0;
    u8 *var_t3;
    u8 *var_t4;
    u8 *var_t6;
    u8 *var_v0_5;
    u8 *var_v1_5;
    u8 temp_v0_2;
    u8 temp_v1;
    u8 temp_v1_3;
    u8 temp_v1_4;
    u8 var_a0_8;
    u8 var_s0_7;
    u8 var_t0_2;
    u8 var_v1_6;
    void *var_v0_3;

    var_s3 = 0;
    var_t1 = 2;
    var_t6 = &aiFieldData[0][0].unk_1 + 4;
    var_t4 = &aiFieldData[0][0].unk_1 + 0x14;
    var_t3 = &aiFieldData[0][0].unk_1 + 0x13;
loop_1:
    var_s0 = 0;
    var_v1 = 1;
    var_t0 = var_t3 + 0x10;
    var_a3 = var_t4 + 0x10;
    var_a0 = var_t6 + 0x10;
loop_2:
    if (var_s0 == 0) {
        if (*var_a0 != 0xA) {
            var_s0 = 1;
        }
        if (var_s0 == 0) {
            var_t0 += 0x10;
            goto block_14;
        }
        goto block_8;
    }
block_8:
    if (*var_a3 != 0xA) {
        if (*var_t0 == M2C_ERROR(/* Read from unset register $a1 */)) {
            var_t0 += 0x10;
block_14:
            var_a3 += 0x10;
            var_v1 += 1;
            var_a0 += 0x10;
            if (var_v1 < 4) {
                goto loop_2;
            }
        } else {
            goto block_12;
        }
    } else {
block_12:
        var_s0 = 2;
        if ((u32) (var_t1 - 3) >= 2U) {
            var_s0 = 0;
        }
    }
    if ((var_s0 == 0) || (var_s3 = var_s0 & 0xFF, (var_s0 != 2))) {
        var_t6 += 2;
        var_t4 += 2;
        var_t1 += 1;
        var_t3 += 2;
        if (var_t1 < 6) {
            goto loop_1;
        }
    }
    var_s6 = 0;
    var_t3_2 = 0x11;
    var_t0_2 = 0;
    var_t1_2 = 4;
    var_a2 = &aiFieldData[0][4].unk_1;
    var_a3_2 = var_a2;
loop_19:
    var_v1_2 = 1;
    var_a0_2 = var_a2 + 0x10;
loop_20:
    var_v0 = var_v1_2 < 4;
    if (*var_a0_2 == 0xA) {
        var_v1_2 += 1;
        var_a0_2 += 0x10;
        if (var_v1_2 >= 4) {
            var_v0 = var_v1_2 < 4;
        } else {
            goto loop_20;
        }
    }
    if (var_v0 == 0) {
        if (var_v1_2 < 0x11) {
            var_a0_3 = (var_v1_2 * 0x10) + var_a3_2;
            do {
                if ((*var_a0_3 != 0xA) && (var_v1_2 < var_t3_2)) {
                    var_t3_2 = var_v1_2 & 0xFF;
                }
                if ((u32) (*var_a0_3 - 5) < 3U) {
                    var_t0_2 += 1;
                }
                var_v1_2 += 1;
                var_a0_3 += 0x10;
            } while (var_v1_2 < 0x11);
        }
        var_a3_2 += 2;
        var_t1_2 += 1;
        var_a2 += 2;
        if (var_t1_2 < 8) {
            goto loop_19;
        }
    } else {
        var_s6 = 2;
    }
    var_t1_3 = 3;
    var_a2_2 = &aiFieldData[0][3].unk_1;
    var_a3_3 = var_a2_2;
loop_34:
    var_v1_3 = 1;
    var_a0_4 = var_a2_2 + 0x10;
loop_35:
    var_v0_2 = var_v1_3 < 4;
    if (*var_a0_4 == 0xA) {
        var_v1_3 += 1;
        var_a0_4 += 0x10;
        if (var_v1_3 >= 4) {
            var_v0_2 = var_v1_3 < 4;
        } else {
            goto loop_35;
        }
    }
    if (var_v0_2 != 0) {
        var_s6 |= 1;
        if ((M2C_ERROR(/* Read from unset register $a1 */) - var_t1_3) < 4) {
            var_s6 = 0;
            var_t0_2 = (u8) gameStateDataRef->unk_299[2];
        }
    } else {
        if (var_v1_3 < 0x11) {
            var_a0_5 = (var_v1_3 * 0x10) + var_a3_3;
            do {
                if ((*var_a0_5 != 0xA) && (var_v1_3 < var_t3_2)) {
                    var_t3_2 = var_v1_3 & 0xFF;
                }
                if ((u32) (*var_a0_5 - 5) < 3U) {
                    var_t0_2 += 1;
                }
                var_v1_3 += 1;
                var_a0_5 += 0x10;
            } while (var_v1_3 < 0x11);
        }
        var_a3_3 -= 2;
        var_t1_3 -= 1;
        var_a2_2 -= 2;
        if (var_t1_3 >= 0) {
            goto loop_34;
        }
    }
    var_a2_3 = 0;
    var_t1_4 = 0;
    var_a1 = &aiFieldData[0][0].unk_1;
    var_v1_4 = 0x11;
    do {
        var_a0_6 = var_a1 + 0x110;
loop_52:
        if ((u32) (*var_a0_6 - 5) >= 3U) {
            var_v1_4 -= 1;
            var_a0_6 -= 0x10;
            if (var_v1_4 < 4) {
                goto block_60;
            }
            goto loop_52;
        }
        if (var_a2_3 < var_v1_4) {
            var_a2_3 = var_v1_4 & 0xFF;
block_60:
            var_a1 += 2;
        } else {
            var_a1 += 2;
        }
        var_t1_4 += 1;
        var_v1_4 = 0x11;
    } while (var_t1_4 < 8);
    var_a3_4 = 1;
    if (evs_gamesel == ENUM_EVS_GAMESEL_3) {
        var_s0_2 = 0;
        if (evs_playcnt != 0) {
            var_a0_7 = &game_state_data->unk_299[2];
            do {
                if ((u8) *var_a0_7 < (u8) *(&game_state_data->unk_299[2] + (aipn * 0x3C4))) {
                    var_a3_4 = 0;
                }
                var_s0_2 += 1;
                var_a0_7 += 0x3C4;
            } while (var_s0_2 < (s32) evs_playcnt);
        }
    }
    var_a0_8 = (u8) gameStateDataRef->unk_04D;
    if ((aipn == 0) && (aiDebugP1 >= 0)) {
        var_a0_8 = (u8) aiDebugP1;
    }
    gameStateDataRef->unk_296 = 0;
    gameStateDataRef->unk_239 = (u8) gameStateDataRef->unk_239 & 1;
    gameStateDataRef->unk_292 &= 0xFB;
    aiPriOfs = 0;
    temp_s2 = &ai_char_data[var_a0_8];
    if ((u8) gameStateDataRef->unk_299[0] != 0) {
        var_s5 = 0;
        goto block_88;
    }
    var_s5 = 1;
    if (!((f64) aiRootP < 4.0)) {
        if ((((u8) gameStateDataRef->unk_299[2] < 7U) && (var_a3_4 != 0)) || ((s32) var_t0_2 < 3)) {
            var_s5 = 2;
            if ((var_t0_2 == 0) && (var_s5 = 3, ((var_t3_2 < (var_a2_3 - 4)) == 0))) {
                if ((u32) var_t3_2 >= 9U) {
                    var_s5 = 4;
                    goto block_88;
                }
                var_v0_3 = temp_s2 + 3;
            } else {
                goto block_88;
            }
        } else {
            if (var_s3 == 2) {
                var_s5 = 5;
            } else {
                var_s5 = 7;
                if (var_s3 == 1) {
                    var_s5 = 6;
                }
            }
            goto block_88;
        }
    } else {
block_88:
        var_v0_3 = temp_s2 + var_s5;
    }
    aiSelCom = var_v0_3->unk_4;
    aiSelSpeed = (s8) (u8) temp_s2->unk_01;
    if (evs_gamemode == ENUM_EVS_GAMEMODE_1) {
        if (last_flash >= 2) {
            aiSelCom = 0;
        } else {
            aiSelCom = 4;
        }
    }
    if ((s_hard_mode != 0) && (var_s5 == 7)) {
        switch (aiSelCom) {                         /* switch 3; irregular */
            case 0x0:                               /* switch 3 */
                aiSelCom = 2;
                break;
            case 0x1:                               /* switch 3 */
                aiSelCom = 3;
                break;
            case 0x4:                               /* switch 3 */
            case 0x5:                               /* switch 3 */
                aiSelCom = aiSelCom;
                break;
        }
    }
    var_s0_3 = 0;
    if (fool_mode == 1) {
        var_a1_2 = 0;
        if (framecont & 0x200) {
            do {
                temp_v0 = &gameStateDataRef->unk_242[var_a1_2];
                var_a1_2 += 1;
                *temp_v0 = 0;
            } while (var_a1_2 < 0x10);
            aiSelCom = 0;
            var_s0_3 = 0;
        }
    }
    temp_s3 = gameStateDataRef->unk_242;
    temp_s4 = gameStateDataRef->unk_272;
    do {
        var_t1_5 = 0;
        temp_a0 = &temp_s4[var_s0_3];
        if ((*temp_a0 + 1) < 0x3E8) {
            var_v0_4 = (u16) *temp_a0 + 1;
        } else {
            var_v0_4 = 0x3E7;
        }
        temp_a1 = &temp_s3[var_s0_3];
        *temp_a0 = var_v0_4;
        temp_v1 = *temp_a1;
        if (temp_v1 != 0) {
            if ((s32) temp_v1 >= 3) {
                if (((s32) temp_v1 < 0xA) && (temp_a0_2 = (gameStateDataRef + (var_s0_3 * 2))->unk_252, (temp_a0_2 != 0))) {
                    if (temp_s4[var_s0_3] >= temp_a0_2) {
                        goto block_119;
                    }
                }
            } else {
block_119:
                *temp_a1 = 0;
            }
        }
        if (temp_s3[var_s0_3] == 0) {
            temp_v1_2 = (u8) temp_s2->unk_0C[var_s0_3] - 1;
            switch (temp_v1_2) {                    /* switch 1 */
                case 0x1:                           /* switch 1 */
                    var_t1_5 = (temp_s2->unk_1C[var_s0_3] < genrand(0x64U)) ^ 1;
                    break;
                case 0x2:                           /* switch 1 */
                    temp_v1_3 = gameStateDataRef->unk_292;
                    if (temp_v1_3 & 1) {
                        var_t1_5 = 1;
                        gameStateDataRef->unk_292 = temp_v1_3 & 0xFE;
                    }
                    break;
                case 0x3:                           /* switch 1 */
                    var_a1_3 = 0;
                    if (evs_playcnt != 0) {
                        var_a2_4 = &game_state_data->unk_025;
loop_129:
                        var_a1_3 += 1;
                        if (var_a1_3 != aipn) {
                            if (((u8) game_state_data[aipn].unk_299[2] - *var_a2_4) >= temp_s2->unk_1C[var_s0_3]) {
                                var_t1_5 = 1;
                            } else {
                                goto block_133;
                            }
                        } else {
block_133:
                            var_a2_4 += 0x3C4;
                            if (var_a1_3 >= (s32) evs_playcnt) {

                            } else {
                                goto loop_129;
                            }
                        }
                    }
                    break;
                case 0x4:                           /* switch 1 */
                    var_a1_4 = 0;
                    if (evs_playcnt != 0) {
                        var_a2_5 = &game_state_data->unk_025;
loop_137:
                        var_a1_4 += 1;
                        if (var_a1_4 != aipn) {
                            if ((*var_a2_5 - (u8) game_state_data[aipn].unk_299[2]) >= temp_s2->unk_1C[var_s0_3]) {
                                var_t1_5 = 1;
                            } else {
                                goto block_141;
                            }
                        } else {
block_141:
                            var_a2_5 += 0x3C4;
                            if (var_a1_4 >= (s32) evs_playcnt) {

                            } else {
                                goto loop_137;
                            }
                        }
                    }
                    break;
                case 0x5:                           /* switch 1 */
                    var_a1_5 = 0;
                    if (evs_playcnt != 0) {
                        var_v1_5 = &game_state_data->unk_294;
loop_145:
                        var_a1_5 += 1;
                        if (var_a1_5 != aipn) {
                            if ((u8) *var_v1_5 < 5U) {
                                var_t1_5 = 1;
                            } else {
                                goto block_149;
                            }
                        } else {
block_149:
                            var_v1_5 += 0x3C4;
                            if (var_a1_5 >= (s32) evs_playcnt) {

                            } else {
                                goto loop_145;
                            }
                        }
                    }
                    break;
                case 0x6:                           /* switch 1 */
                    var_t1_5 = gameStateDataRef->unk_23C == 0;
                    break;
                case 0x7:                           /* switch 1 */
                    var_t1_5 = gameStateDataRef->unk_23C == 1;
                    break;
                case 0x8:                           /* switch 1 */
                    var_t1_5 = gameStateDataRef->unk_23C == 2;
                    break;
                case 0x9:                           /* switch 1 */
                    var_t1_5 = (temp_s2->unk_1C[var_s0_3] < (s32) (u8) gameStateDataRef->unk_299[2]) ^ 1;
                    break;
                case 0xA:                           /* switch 1 */
                    var_t1_5 = gameStateDataRef->unk_1CF != 0;
                    break;
                case 0x0:                           /* switch 1 */
                    var_t1_5 = 1;
                    break;
                case 0xB:                           /* switch 1 */
                    var_t1_5 = (dm_get_first_virus_count(evs_gamemode, gameStateDataRef) < temp_s2->unk_1C[var_s0_3]) ^ 1;
                    break;
            }
            if (var_t1_5 != 0) {
                temp_s3[var_s0_3] = (u8) temp_s2->unk_3C[var_s0_3];
                (gameStateDataRef + (var_s0_3 * 2))->unk_252 = (u16) temp_s2->unk_4C[var_s0_3];
                temp_s4[var_s0_3] = 0;
            }
        }
        var_s0_3 += 1;
    } while (var_s0_3 < 0x10);
    var_s0_4 = 0;
    var_v0_5 = temp_s3;
    do {
        temp_v1_4 = *var_v0_5;
        switch (temp_v1_4) {                        /* switch 2 */
            case 0x1:                               /* switch 2 */
                gameStateDataRef->unk_239 = (u8) gameStateDataRef->unk_239 | 2;
            default:                                /* switch 2 */
block_191:
                var_s0_4 += 1;
                break;
            case 0x3:                               /* switch 2 */
                gameStateDataRef->unk_292 |= 4;
                goto block_191;
            case 0x4:                               /* switch 2 */
                var_v1_6 = (u8) aiSelSpeed;
                if (aiSelSpeed < 5) {
                    var_v1_6 = 5;
                }
block_177:
                aiSelSpeed = (s8) var_v1_6;
                var_s0_4 += 1;
                break;
            case 0x5:                               /* switch 2 */
                var_v1_6 = (u8) aiSelSpeed;
                if (aiSelSpeed >= 2) {
                    var_v1_6 = 1;
                }
                goto block_177;
            case 0x6:                               /* switch 2 */
                aiSelSpeed = 6;
                var_s0_4 += 1;
                break;
            case 0x7:                               /* switch 2 */
                temp_v0_2 = (temp_s4[var_s0_4] / 5) + 1;
                var_v1_6 = temp_v0_2;
                aiSelSpeed = (s8) temp_v0_2;
                if ((s8) temp_v0_2 >= 7) {
                    var_v1_6 = 6;
                }
                goto block_177;
            case 0x8:                               /* switch 2 */
                var_v0_6 = aiSelCom + 1;
                if (var_v0_6 >= 4) {
                    var_v0_6 = 3;
                }
block_184:
                aiSelCom = (u8) var_v0_6;
                var_s0_4 += 1;
                break;
            case 0x9:                               /* switch 2 */
                var_v0_6 = aiSelCom - 1;
                if (var_v0_6 < 0) {
                    var_v0_6 = 0;
                }
                goto block_184;
            case 0xA:                               /* switch 2 */
                temp_v1_5 = (gameStateDataRef + (var_s0_4 * 2))->unk_252;
                temp_a0_3 = temp_v1_5 - 1;
                if (temp_v1_5 != 0) {
                    var_v0_7 = temp_a0_3;
                    if (temp_a0_3 < 0) {
                        var_v0_7 = temp_v1_5 + 0xE;
                    }
                    temp_s3[temp_a0_3 - ((var_v0_7 >> 4) * 0x10)] = 0;
                } else {
                    var_a1_6 = 0;
                    do {
                        temp_v0_3 = &temp_s3[var_a1_6];
                        var_a1_6 += 1;
                        *temp_v0_3 = 0;
                    } while (var_a1_6 < 0x10);
                }
                goto block_191;
        }
        var_v0_5 = &temp_s3[var_s0_4];
    } while (var_s0_4 < 0x10);
    var_s0_5 = 3;
    if (aiSelSpeed == 6) {
        var_s0_6 = 0;
        gameStateDataRef->unk_239 = (u8) gameStateDataRef->unk_239 & 0xFD;
        var_a0_9 = temp_s3;
        do {
            if (*var_a0_9 == 2) {
                *var_a0_9 = 0;
            }
            var_s0_6 += 1;
            var_a0_9 = &temp_s3[var_s0_6];
        } while (var_s0_6 < 0x10);
        var_s0_5 = 3;
    }
    var_a3_5 = &D_80093382_cn + 4;
    temp_t1 = &ai_param[aiSelCom][var_s5];
    temp_v0_4 = (u16) temp_t1->unk_04;
    D_80093374_cn.unk_0 = (u16) temp_t1->unk_00;
    D_80093374_cn.unk_-6 = (u16) temp_t1->unk_02;
    D_80093382_cn.unk_0 = temp_v0_4;
    D_80093382_cn.unk_2 = (s16) ((s32) ((s16) temp_v0_4 + temp_t1->unk_06) >> 1);
    do {
        *var_a3_5 = (u16) temp_t1->unk_06;
        var_s0_5 += 1;
        var_a3_5 += 2;
    } while (var_s0_5 < 9);
    LPriP = (u16) temp_t1->unk_0C;
    D_800933C8_cn.unk_0 = (u16) temp_t1->unk_0E;
    D_800933C8_cn.unk_2 = (u16) temp_t1->unk_10;
    D_800933C8_cn.unk_4 = (u16) temp_t1->unk_12;
    D_800933C8_cn.unk_6 = (u16) temp_t1->unk_14;
    D_800933D2_cn.unk_0 = (u16) temp_t1->unk_16;
    D_800933D2_cn.unk_2 = (u16) temp_t1->unk_18;
    D_800933D2_cn.unk_4 = (u16) temp_t1->unk_1A;
    D_800933D2_cn.unk_6 = (u16) temp_t1->unk_1C;
    D_800933D2_cn.unk_8 = (u16) temp_t1->unk_1E;
    OnVirusP = (s32) temp_t1->unk_20;
    RensaP = (u16) temp_t1->unk_22;
    RensaMP = (u16) temp_t1->unk_24;
    D_8009337A_cn.unk_0 = (u16) temp_t1->unk_26;
    HeiEraseLinRate = (f32) temp_t1->unk_08 * 0.01f;
    WidEraseLinRate = (f32) temp_t1->unk_0A * 0.01f;
    D_8009337A_cn.unk_2 = (u16) temp_t1->unk_28;
    var_v1_7 = var_s6;
    if (temp_t1->unk_2A == 0) {
        var_v1_7 = 0;
    }
    aiWall = var_v1_7;
    OnVirusP_org = OnVirusP;
    temp_v1_6 = (u16) temp_t1->unk_30;
    D_800933A0_cn.unk_0 = (u16) temp_t1->unk_2C;
    D_800933A0_cn.unk_2 = (u16) temp_t1->unk_2E;
    D_800933A0_cn.unk_4 = temp_v1_6;
    D_800933A0_cn.unk_6 = temp_v1_6;
    D_800933A0_cn.unk_8 = temp_v1_6;
    D_800933A0_cn.unk_A = temp_v1_6;
    D_800933A0_cn.unk_C = temp_v1_6;
    temp_v1_7 = (u16) temp_t1->unk_36;
    D_800933B4_cn.unk_0 = (u16) temp_t1->unk_32;
    D_800933B4_cn.unk_2 = (u16) temp_t1->unk_34;
    D_800933B4_cn.unk_4 = temp_v1_7;
    D_800933B4_cn.unk_6 = temp_v1_7;
    D_800933B4_cn.unk_8 = temp_v1_7;
    D_800933B4_cn.unk_A = temp_v1_7;
    D_800933B4_cn.unk_C = temp_v1_7;
    if (temp_s2->unk_00 != 0) {
        var_s0_7 = 0;
        if (evs_playcnt != 0) {
            do {
                if ((var_s0_7 != aipn) && (game_state_data[var_s0_7].unk_050[0].unk_0 != 0)) {
                    var_a1_7 = 2;
                    var_v1_8 = &EraseLinP + 4;
                    do {
                        if (*var_v1_8 > 0) {
                            *var_v1_8 = -(s16) (u16) *var_v1_8;
                        }
                        var_a1_7 += 1;
                        var_v1_8 += 2;
                    } while (var_a1_7 < 8);
                    var_s0_7 = evs_playcnt;
                }
                var_s0_7 += 1;
            } while ((s32) var_s0_7 < (s32) evs_playcnt);
        }
    }
}
#else
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/aiset", aiSetCharacter);
#endif
#endif

#if VERSION_US || VERSION_CN
/**
 * Original name: aifFieldCopy
 */
void aifFieldCopy(struct_game_state_data *gameStateDataRef) {
    s32 column;
    s32 row;

    aiNext[0] = gameStateDataRef->unk_3BE[0];
    aiNext[1] = gameStateDataRef->unk_3BE[1];

    for (column = 0; column < GAME_MAP_COLUMNS; column++) {
        for (row = 0; row < GAME_MAP_ROWS; row++) {
            aiRecurData[row][column + 1].unk_0 = aiFieldData[row][column].unk_0 =
                gameStateDataRef->unk_29C[row][column][1];
            aiRecurData[row][column + 1].unk_1 = aiFieldData[row][column].unk_1 =
                gameStateDataRef->unk_29C[row][column][0];
        }
    }

    for (column = 0; column < ARRAY_COUNT(*aiRecurData); column++) {
        aiRecurData[ARRAY_COUNTU(aiRecurData) - 1][column].unk_0 = 0xFF;
        aiRecurData[ARRAY_COUNTU(aiRecurData) - 1][column].unk_1 = 0xFF;
    }

    for (row = 0; row < ARRAY_COUNT(aiRecurData); row++) {
        aiRecurData[row][0].unk_0 = 0xFF;
        aiRecurData[row][0].unk_1 = 0xFF;
        aiRecurData[row][ARRAY_COUNTU(aiRecurData[row]) - 1].unk_0 = 0xFF;
        aiRecurData[row][ARRAY_COUNTU(aiRecurData[row]) - 1].unk_1 = 0xFF;
    }
}
#endif

// no original name :c
void func_80034310(void) {
    s32 column;

    for (column = 0; column < GAME_MAP_COLUMNS; column++) {
        s32 row;

        for (row = 0; row < GAME_MAP_ROWS; row++) {
            aiRecurData[row][column + 1].unk_0 = aiFieldData[row][column].unk_0;
            aiRecurData[row][column + 1].unk_1 = aiFieldData[row][column].unk_1;
        }
    }
}

#if VERSION_US
/**
 * Original name: aifPlaceSearch
 */
INCLUDE_ASM("asm/us/nonmatchings/main_segment/aiset", aifPlaceSearch);
#endif

extern u8 aiTEdgeCnt;
extern u8 aiYEdgeCnt;

#if VERSION_CN
void aifPlaceSearch(void) {
    s32 var_t4 = 0;
    s32 var_t5 = 0;
    u8 sp8[100][3];
    s32 row;
    s32 column;

    aiYEdgeCnt = 0;
    aiTEdgeCnt = 0;

    for (row = 1; row < ARRAY_COUNT(aiRecurData) - 1; row++) {
        for (column = 1; column < ARRAY_COUNT(aiRecurData[0]) - 1; column++) {
            if (aiRecurData[row][column].unk_0 != 3) {
                continue;
            }
            if (aiRecurData[row + 1][column].unk_0 == 3) {
                continue;
            }
            if (aiRecurData[row - 1][column].unk_0 != 3) {
                continue;
            }

            sp8[var_t4][0] = 0;
            sp8[var_t4][1] = column;
            sp8[var_t4][2] = row;

            var_t4++;
            var_t5++;
            aiTEdgeCnt++;
        }
    }

    for (row = 1; row < 0x11; row++) {
        for (column = 1; column < 8; column++) {
            if (aiRecurData[row][column].unk_0 != 3) {
                continue;
            }

            if ((aiRecurData[row + 1][column].unk_0 == 3) && (aiRecurData[row + 1][column + 1].unk_0 == 3)) {
                continue;
            }

            if (aiRecurData[row][column + 1].unk_0 != 3) {
                continue;
            }

            sp8[var_t5][0] = 1;
            sp8[var_t5][1] = column;
            sp8[var_t5][2] = row;
            var_t5++;
            aiYEdgeCnt++;
        }
    }

    var_t5 = 0;

    for (column = 0; column < aiTEdgeCnt; column++) {
        aiFlag[var_t5].unk_01 = 0;
        aiFlag[var_t5].unk_02 = sp8[column][1];
        aiFlag[var_t5].unk_03 = sp8[column][2];
        aiFlag[var_t5].unk_04 = 0;

        var_t5++;
    }

    if (aiNext[0] != aiNext[1]) {
        for (column = 0; column < aiTEdgeCnt; column++) {
            aiFlag[var_t5].unk_01 = 0;
            aiFlag[var_t5].unk_02 = sp8[column][1];
            aiFlag[var_t5].unk_03 = sp8[column][2];
            aiFlag[var_t5].unk_04 = 1;

            var_t5++;
        }
    }

    for (column = 0; column < aiYEdgeCnt; column++) {
        aiFlag[var_t5].unk_01 = 1;
        aiFlag[var_t5].unk_02 = sp8[aiTEdgeCnt + column][1];
        aiFlag[var_t5].unk_03 = sp8[aiTEdgeCnt + column][2];
        aiFlag[var_t5].unk_04 = 0;

        var_t5++;
    }

    if (aiNext[0] != aiNext[1]) {
        for (column = 0; column < aiYEdgeCnt; column++) {
            aiFlag[var_t5].unk_01 = 1;
            aiFlag[var_t5].unk_02 = sp8[aiTEdgeCnt + column][1];
            aiFlag[var_t5].unk_03 = sp8[aiTEdgeCnt + column][2];
            aiFlag[var_t5].unk_04 = 1;

            var_t5++;
        }
    }

    aiFlagCnt = var_t5;
}
#endif

#if VERSION_US
/**
 * Original name: aifMoveCheck
 */
INCLUDE_ASM("asm/us/nonmatchings/main_segment/aiset", aifMoveCheck);
#endif

void aifTRecur(u8 arg0, u8 arg1, u8 arg2);
void aifYRecur(u8 arg0, u8 arg1, u8 arg2);
extern f32 aiRootP;

extern u8 aiRollFinal;

extern u8 aiSelCom;

#if VERSION_CN
void aifMoveCheck(void) {
    s32 i;
    s32 j;
    s32 var_s7;
    s32 var_s6;

    for (j = 0; j < aiFlagCnt; j++) {
        aiFlag[j].unk_08 = 0;
    }

    var_s7 = 0;
    var_s6 = 0;

    for (i = 0; i < aiFlagCnt; i++) {
        for (j = 0; j < ARRAY_COUNT(aiRecurData[0]); j++) {
            aiRecurData[0][j].unk_0 = 0xF;
        }

        func_80034310();

        aiRootCnt = 0;
        aiRollFinal = 0;
        success = 0;

        if (aiFlag[i].unk_01 == 0) {
            aifTRecur(aiFlag[i].unk_02, aiFlag[i].unk_03, i);
        } else {
            aifYRecur(aiFlag[i].unk_02, aiFlag[i].unk_03, i);
        }

        aiFlag[i].unk_00 = success;
        if (success == 0) {
            if (aiSelCom >= 2) {
                aiRollFinal = 1;

                if (aiFlag[i].unk_01 == 0) {
                    if (aiFlag[i].unk_02 < 7U) {
                        if (aiRecurData[aiFlag[i].unk_03][aiFlag[i].unk_02 + 1].unk_1 == 0xA) {
                            aifYRecur(aiFlag[i].unk_02, aiFlag[i].unk_03, i);
                        }
                    }
                } else if (aiRecurData[aiFlag[i].unk_03 - 1][aiFlag[i].unk_02].unk_1 == 0xA) {
                    aifTRecur(aiFlag[i].unk_02, aiFlag[i].unk_03, i);
                } else if (aiRecurData[aiFlag[i].unk_03 - 1][aiFlag[i].unk_02 + 1].unk_1 == 0xA) {
                    if ((aiRecurData[aiFlag[i].unk_03][aiFlag[i].unk_02 + 2].unk_1 != 0xA) || (aiFlag[i].unk_02 == 6)) {
                        aifTRecur(aiFlag[i].unk_02 + 1, aiFlag[i].unk_03, i);
                    }
                }

                aiFlag[i].unk_00 = success;
            }
        }

        if (success != 0) {
            var_s6++;
            var_s7 += aiRootCnt;
        }
    }

    if (var_s6 != 0) {
        aiRootP = (f32)var_s7 / (f32)var_s6;
    } else {
        aiRootP = 0.0f;
    }
}
#endif

#if VERSION_US
#if 0
? aifTRecurUP(s32, s8, s32);                        /* extern */
extern u8 success;
extern u8 aiRootCnt;
extern ? aiRoot;

void aifTRecur(s8 arg0, s8 arg1, s32 arg2) {
    s32 temp_a0_2;
    s32 temp_a0_3;
    s32 temp_a0_4;
    s32 temp_a0_5;
    s32 temp_a1;
    s32 temp_a2;
    s8 temp_a0;
    s8 temp_a1_2;
    s8 temp_a1_3;

    *(aiRecurData + (((arg0 & 0xFF) * 2) + ((arg1 & 0xFF) * 0x14))) = 0xF;
    if (((arg0 & 0xFF) == (u16) aiGoalX) && ((arg1 & 0xFF) == (u16) aiGoalY)) {
        success = 1;
    }
    temp_a0 = arg0 & 0xFF;
    if (success != 1) {
        temp_a2 = temp_a0 * 2;
        temp_a1 = arg1 & 0xFF;
        if ((*(aiRecurData + (temp_a2 + ((temp_a1 - 1) * 0x14))) == 3) && ((&aiRecurData[0][0].unk_1)[temp_a2 + ((temp_a1 - 2) * 0x14)] == 0xA)) {
            aifTRecur(temp_a0, (arg1 - 1) & 0xFF, arg2 & 0xFF);
        }
        if (success != 1) {
            temp_a0_2 = ((arg0 & 0xFF) + 1) * 2;
            temp_a1_2 = arg1 & 0xFF;
            if ((*(aiRecurData + (temp_a0_2 + (temp_a1_2 * 0x14))) == 3) && ((&aiRecurData[0][0].unk_1)[temp_a0_2 + ((temp_a1_2 - 1) * 0x14)] == 0xA)) {
                temp_a0_3 = arg0 + 1;
                if ((u8) aiMoveSF != 0) {
                    aifTRecur(temp_a0_3 & 0xFF, temp_a1_2, arg2 & 0xFF);
                } else {
                    aifTRecurUP(temp_a0_3 & 0xFF, temp_a1_2, arg2 & 0xFF);
                }
            }
            if (success != 1) {
                temp_a0_4 = ((arg0 & 0xFF) - 1) * 2;
                temp_a1_3 = arg1 & 0xFF;
                if ((*(aiRecurData + (temp_a0_4 + (temp_a1_3 * 0x14))) == 3) && ((&aiRecurData[0][0].unk_1)[temp_a0_4 + ((temp_a1_3 - 1) * 0x14)] == 0xA)) {
                    temp_a0_5 = arg0 - 1;
                    if ((u8) aiMoveSF != 0) {
                        aifTRecur(temp_a0_5 & 0xFF, temp_a1_3, arg2 & 0xFF);
                    } else {
                        aifTRecurUP(temp_a0_5 & 0xFF, temp_a1_3, arg2 & 0xFF);
                    }
                }
                if (success == 1) {
                    goto block_20;
                }
            } else {
                goto block_20;
            }
        } else {
            goto block_20;
        }
    } else {
block_20:
        *(&aiRoot + (aiRootCnt * 2)) = arg0;
        *(&B_800F6C71 + (aiRootCnt * 2)) = arg1;
        aiRootCnt += 1;
    }
}
#else
INCLUDE_ASM("asm/us/nonmatchings/main_segment/aiset", aifTRecur);
#endif
#endif

#if VERSION_CN
void aifTRecur(u8 arg0, u8 arg1, u8 arg2) {
    aiRecurData[arg1][arg0].unk_0 = 0xF;

    if ((arg0 == aiGoalX) && (arg1 == aiGoalY)) {
        success = 1;
    }

    if (success != 1) {
        if ((aiRecurData[arg1 - 1][arg0].unk_0 == 3) && (aiRecurData[arg1 - 2][arg0].unk_1 == 0xA)) {
            aifTRecur(arg0, arg1 - 1, arg2);
        }
    }

    if (success != 1) {
        if ((aiRecurData[arg1][arg0 + 1].unk_0 == 3) && (aiRecurData[arg1 - 1][arg0 + 1].unk_1 == 0xA)) {
            if (aiMoveSF != 0) {
                aifTRecur(arg0 + 1, arg1, arg2);
            } else {
                aifTRecurUP(arg0 + 1, arg1, arg2);
            }
        }
    }

    if (success != 1) {
        if ((aiRecurData[arg1][arg0 - 1].unk_0 == 3) && (aiRecurData[arg1 - 1][arg0 - 1].unk_1 == 0xA)) {
            if (aiMoveSF != 0) {
                aifTRecur(arg0 - 1, arg1, arg2);
            } else {
                aifTRecurUP(arg0 - 1, arg1, arg2);
            }
        }
    }

    if (success == 1) {
        aiRoot[aiRootCnt][0] = arg0;
        aiRoot[aiRootCnt][1] = arg1;
        aiRootCnt++;
    }
}
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/aiset", aifTRecurUP);
#endif

#if VERSION_CN
void aifTRecurUP(u8 arg0, u8 arg1, u8 arg2) {
    if ((arg0 == aiGoalX) && (arg1 == aiGoalY)) {
        success = 1;
    }

    if (success != 1) {
        if ((aiRecurData[arg1 - 1][arg0].unk_0 == 3) && (aiRecurData[arg1 - 2][arg0].unk_1 == 0xA)) {
            aifTRecur(arg0, arg1 - 1, arg2);
        }
    }

    if (success == 1) {
        aiRoot[aiRootCnt][0] = arg0;
        aiRoot[aiRootCnt][1] = arg1;
        aiRootCnt++;
    }
}
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/aiset", aifYRecur);
#endif

#if VERSION_CN
void aifYRecur(u8 arg0, u8 arg1, u8 arg2) {
    aiRecurData[arg1][arg0].unk_0 = 0xF;

    if ((arg0 == aiGoalX) && (arg1 == aiGoalY)) {
        success = 1;
    }

    if (success != 1) {
        if ((aiRecurData[arg1 - 1][arg0].unk_0 == 3) && (aiRecurData[arg1 - 1][arg0 + 1].unk_1 == 0xA)) {
            aifYRecur(arg0, arg1 - 1, arg2);
        }
    }

    if (success != 1) {
        if ((aiRecurData[arg1][arg0 + 1].unk_0 == 3) && (aiRecurData[arg1][arg0 + 2].unk_1 == 0xA)) {
            if (aiMoveSF != 0) {
                aifYRecur(arg0 + 1, arg1, arg2);
            } else {
                aifYRecurUP(arg0 + 1, arg1, arg2);
            }
        }
    }

    if (success != 1) {
        if ((aiRecurData[arg1][arg0 - 1].unk_0 == 3) && (aiRecurData[arg1][arg0].unk_1 == 0xA)) {
            if (aiMoveSF != 0) {
                aifYRecur(arg0 - 1, arg1, arg2);
            } else {
                aifYRecurUP(arg0 - 1, arg1, arg2);
            }
        }
    }

    if (success == 1) {
        aiRoot[aiRootCnt][0] = arg0;
        aiRoot[aiRootCnt][1] = arg1;
        aiRootCnt++;
    }
}
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/aiset", aifYRecurUP);
#endif

#if VERSION_CN
void aifYRecurUP(u8 arg0, u8 arg1, u8 arg2) {
    if ((arg0 == aiGoalX) && (arg1 == aiGoalY)) {
        success = 1;
    }

    if (success != 1) {
        if ((aiRecurData[arg1 - 1][arg0].unk_0 == 3) && (aiRecurData[arg1 - 1][arg0 + 1].unk_1 == 0xA)) {
            aifYRecur(arg0, arg1 - 1, arg2);
        }
    }

    if (success == 1) {
        aiRoot[aiRootCnt][0] = arg0;
        aiRoot[aiRootCnt][1] = arg1;
        aiRootCnt += 1;
    }
}
#endif

#if VERSION_US
/**
 * Original name: aifReMoveCheck
 */
INCLUDE_ASM("asm/us/nonmatchings/main_segment/aiset", aifReMoveCheck);
#endif

#if VERSION_CN
void aifReMoveCheck(void) {
    s32 i;

    for (i = 0; i < 0x32; i++) {
        aiRoot[i][0] = 0;
        aiRoot[i][1] = 0;
    }

    aiRootCnt = 0;
    aiRollFinal = 0;
    aiMoveSF = 1;
    success = 0;

    func_80034310();

    if (aiFlag[decide].unk_01 == 0) {
        aifTRecur(aiFlag[decide].unk_02, aiFlag[decide].unk_03, decide);
    } else {
        aifYRecur(aiFlag[decide].unk_02, aiFlag[decide].unk_03, decide);
    }

    if (success == 0) {
        aiRollFinal = 1;
        func_80034310();

        if (aiFlag[decide].unk_01 == 0) {
            if (aiRecurData[aiFlag[decide].unk_03][aiFlag[decide].unk_02 + 1].unk_1 == 0xA) {
                aifYRecur(aiFlag[decide].unk_02, aiFlag[decide].unk_03, decide);
            }
        } else if (aiRecurData[aiFlag[decide].unk_03 - 1][aiFlag[decide].unk_02].unk_1 == 0xA) {
            aifTRecur(aiFlag[decide].unk_02, aiFlag[decide].unk_03, decide);
        } else if (aiRecurData[aiFlag[decide].unk_03 - 1][aiFlag[decide].unk_02 + 1].unk_1 == 0xA) {
            if ((aiRecurData[aiFlag[decide].unk_03][aiFlag[decide].unk_02 + 2].unk_1 != 0xA) ||
                (aiFlag[decide].unk_02 == 6)) {
                aifTRecur(aiFlag[decide].unk_02 + 1, aiFlag[decide].unk_03, decide);
            }
        }
    }

    aiRoot[aiRootCnt][0] = aiRoot[aiRootCnt - 1][0];
    aiRoot[aiRootCnt][1] = aiRoot[aiRootCnt - 1][1] + 1;
}
#endif

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/aiset", RO_800ACF10);
#endif

#if VERSION_US
/**
 * Original name: aifKeyMake
 */
#if 0
//s8 aifRensaCheck(struct_game_state_data *, s8 *, void *, s8 *); /* extern */
extern f32 aiRootP;
extern u8 aiRollFinal;
extern u8 aiVirusLevel[][3];
extern u8 aiRoot[][2];

extern s32 _aiFlag[UNK_SIZE][4][4];

void aifKeyMake(struct_game_state_data *gameStateDataRef) {
    s32 sp10[][2] = {{1,3},{0,2},};
    s32 (*var_a2)[4];
    s32 *var_a3;
    s32 temp_v1;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v1;
    s8 temp_v0_2;
    u8 temp_v0;
    s32 i;
    s32 j;

    i = 0;

    var_a2 = _aiFlag[(u8) decide];
    do {
        gameStateDataRef->unk_190[i][0] = var_a2[i][0];
        gameStateDataRef->unk_190[i][1] = var_a2[i][1];
        gameStateDataRef->unk_190[i][2] = var_a2[i][2];
        gameStateDataRef->unk_190[i][3] = var_a2[i][3];
        i++;
    } while (i < 4);

    i = 0;
    do {
        gameStateDataRef->unk_1D0[i][0] = aiRoot[i][0];
        gameStateDataRef->unk_1D0[i][1] = aiRoot[i][1];
        i += 1;
    } while (i < 0x64/2);

    gameStateDataRef->unk_23F = aiRoot[aiRootCnt - 1][0];
    gameStateDataRef->unk_240 = aiRoot[aiRootCnt - 1][1];
    // ??
    gameStateDataRef->unk_1D0[0][-1] = aifRensaCheck(gameStateDataRef, gameStateDataRef->unk_190[0]);

    temp_v1 = ((((sp10[(u8)gameStateDataRef->unk_184[0xD]][(u8)gameStateDataRef->unk_184[0x10]]) - ((u8) gameStateDataRef->unk_241 - 0x28)) + (u8) gameStateDataRef->unk_237) - aiRollFinal) + (u8) gameStateDataRef->unk_238;
    var_v0 = temp_v1;
    if (temp_v1 < 0) {
        var_v0 = temp_v1 + 3;
    }
    temp_v0_2 = temp_v1 - ((var_v0 >> 2) * 4);
    gameStateDataRef->unk_237 = temp_v0_2;
    gameStateDataRef->unk_241 = temp_v0_2;
    gameStateDataRef->unk_238 = (s8) aiRollFinal;
    gameStateDataRef->unk_235 = 2;
    gameStateDataRef->unk_236 = 1;
    gameStateDataRef->unk_293[0] = (s8) (u8) aiSelSpeed;

    //if (!(aiRootP > 100.0f)) {
    //    gameStateDataRef->unk_294 = aiRootP;
    //} else {
    //    gameStateDataRef->unk_294 = (s8) 100;
    //}

    gameStateDataRef->unk_294 = MIN(100, aiRootP);

    if ((u32) (genrand((s32) aiVirusLevel[aiSelSpeed][gameStateDataRef->unk_23C]) & 0xFF) >= 7U) {
        gameStateDataRef->unk_23A = 0;
    } else {
        gameStateDataRef->unk_23A = 1;
        gameStateDataRef->unk_23B = genrand(5);
    }
}
#else
INCLUDE_ASM("asm/us/nonmatchings/main_segment/aiset", aifKeyMake);
#endif
#endif

#if VERSION_CN
void aifKeyMake(struct_game_state_data *gameStateDataRef) {
    s32 sp18[2][2] = { { 1, 3 }, { 0, 2 } };
    s32 i;
    u8 temp;

    gameStateDataRef->unk_190 = aiFlag[decide];

    for (i = 0; i < AIROOT_LEN; i++) {
        gameStateDataRef->unk_1D0[i][0] = aiRoot[i][0];
        gameStateDataRef->unk_1D0[i][1] = aiRoot[i][1];
    }

    gameStateDataRef->unk_23F = aiRoot[aiRootCnt - 1][0];
    gameStateDataRef->unk_240 = aiRoot[aiRootCnt - 1][1];

    gameStateDataRef->unk_190.unk_3F = aifRensaCheck(gameStateDataRef, &gameStateDataRef->unk_190);

    gameStateDataRef->unk_237 =
        (0x28 + sp18[gameStateDataRef->unk_190.unk_01][gameStateDataRef->unk_190.unk_04] - gameStateDataRef->unk_241 +
         gameStateDataRef->unk_237 - aiRollFinal + gameStateDataRef->unk_238) %
        4;
    gameStateDataRef->unk_241 = gameStateDataRef->unk_237;
    gameStateDataRef->unk_238 = aiRollFinal;
    gameStateDataRef->unk_293 = aiSelSpeed;
    gameStateDataRef->unk_235 = 2;
    gameStateDataRef->unk_236 = 1;
    gameStateDataRef->unk_294 = (aiRootP > 100.0f) ? 100 : aiRootP;

    temp = genrand(aiVirusLevel[aiSelSpeed][gameStateDataRef->unk_23C]);
    if (temp >= 7U) {
        gameStateDataRef->unk_23A = 0;
    } else {
        gameStateDataRef->unk_23A = 1;
        gameStateDataRef->unk_23B = genrand(5);
    }
}
#endif

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/aiset", wave_tbl_2879);
#endif

#if VERSION_US
/**
 * Original name: aifKeyOut
 */
INCLUDE_ASM("asm/us/nonmatchings/main_segment/aiset", aifKeyOut);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/aiset", wave_tbl_2879);
#endif

extern const s32 wave_tbl_2879[];

#if VERSION_CN
#ifdef NON_EQUIVALENT
void aifKeyOut(struct_game_state_data *gameStateDataRef) {
    s32 temp_s3;
    s32 temp_t0_3;
    s32 var_a0;
    s32 var_s1;

    func_8002EB00(gameStateDataRef);

    joygam[gameStateDataRef->unk_298] = 0;
    if (gameStateDataRef->unk_23D == 0) {
        return;
    }

    if (gameStateDataRef->unk_3BD == 0) {
        return;
    }

    if (gameStateDataRef->unk_3BC == (gameStateDataRef->unk_1D0[gameStateDataRef->unk_234][0] - 1)) {
        if (gameStateDataRef->unk_3BD == gameStateDataRef[0].unk_1D0[gameStateDataRef->unk_234][0]) {
            gameStateDataRef->unk_234++;
        }
    }

    gameStateDataRef->unk_235--;

    var_s1 = gameStateDataRef->unk_1D0[gameStateDataRef->unk_234][0] - (gameStateDataRef->unk_3BC + 1);
    temp_s3 = gameStateDataRef->unk_1D0[gameStateDataRef->unk_234][1] - gameStateDataRef->unk_3BD;

    if ((temp_s3 != 0) && (gameStateDataRef->unk_3BD < gameStateDataRef->unk_240 - 3)) {
        for (var_a0 = 0; var_a0 < 0x10; var_a0++) {
            s32 temp;

            if (gameStateDataRef->unk_242[var_a0] != 2) {
                continue;
            }

            temp = wave_tbl_2879[(gameStateDataRef->unk_240 + gameStateDataRef->unk_3BD) & 7];
            temp_t0_3 = var_s1 + temp;

            if (gameStateDataRef
                    ->unk_29C[gameStateDataRef->unk_3BD + 1][gameStateDataRef->unk_3BC + temp_t0_3 - 1][0] == 0xA) {
                if (gameStateDataRef
                        ->unk_29C[gameStateDataRef->unk_3BD + 1][gameStateDataRef->unk_3BC + temp_t0_3][0] == 0xA) {
                    if (gameStateDataRef->unk_29C[gameStateDataRef->unk_3BD + 1]
                                                 [gameStateDataRef->unk_3BC + temp_t0_3 + 1][0] == 0xA) {
                        var_s1 = temp_t0_3;
                    }
                }
            }
            break;
        }
    }

    if ((gameStateDataRef->unk_235 == 0) && !(gameStateDataRef->unk_292 & 4)) {
        if (gameStateDataRef->unk_237 == 0) {
            if (gameStateDataRef->unk_239 & 2) {
                if (((genrand(5U) == 0) && (gameStateDataRef->unk_3BD < (gameStateDataRef->unk_240 - 3))) ||
                    (gameStateDataRef->unk_239 & 1)) {
                    gameStateDataRef->unk_237 += 2;
                    gameStateDataRef->unk_239 ^= 1;
                }
            }
        }

        if (gameStateDataRef->unk_237 != 0) {
            if (gameStateDataRef->unk_237 == 3) {
                joygam[gameStateDataRef->unk_298] = 0x4000;
                gameStateDataRef->unk_237 = 0;
            } else {
                joygam[gameStateDataRef->unk_298] = 0x8000;
                gameStateDataRef->unk_237--;
            }
            gameStateDataRef->unk_235 = 5;
        }

        if (temp_s3 < 0) {
            gameStateDataRef->unk_235 = 1;
            gameStateDataRef->unk_234++;
            if (gameStateDataRef->unk_240 < gameStateDataRef->unk_3BD) {
                gameStateDataRef->unk_23D = 0;
            }
        }

        if (var_s1 > 0) {
            joygam[gameStateDataRef->unk_298] |= 0x100;

            if (gameStateDataRef->unk_236 == 0) {
                gameStateDataRef->unk_235 = aiSlideFSpeed[gameStateDataRef->unk_293][gameStateDataRef->unk_23C];
            } else {
                gameStateDataRef->unk_235 = D_800884F0[gameStateDataRef->unk_293][gameStateDataRef->unk_23C];
            }

            gameStateDataRef->unk_236++;
        }

        if (var_s1 < 0) {
            joygam[gameStateDataRef->unk_298] |= 0x200;

            if (gameStateDataRef->unk_236 == 0) {
                gameStateDataRef->unk_235 = aiSlideFSpeed[gameStateDataRef->unk_293][gameStateDataRef->unk_23C];
            } else {
                gameStateDataRef->unk_235 = D_800884F0[gameStateDataRef->unk_293][gameStateDataRef->unk_23C];
            }

            gameStateDataRef->unk_236++;
        }

        if (temp_s3 > 0) {
            if (gameStateDataRef->unk_236 == 0) {
                if ((gameStateDataRef->unk_293 == 6) || (gameStateDataRef->unk_1D0[gameStateDataRef->unk_234][1] !=
                                                         gameStateDataRef->unk_1D0[gameStateDataRef->unk_234 + 1][1])) {
                    if ((gameStateDataRef->unk_293 - 5 >= 2U) && (gameStateDataRef->unk_3BD < 3U)) {
                        if ((gameStateDataRef->unk_293 >= 2U) && (gameStateDataRef->unk_3BD == 2) &&
                            ((FallSpeed[gameStateDataRef->unk_3C0] / 2) < gameStateDataRef->unk_3C1)) {
                            goto block_55;
                        }
                    } else {
                    block_55:
                        if ((evs_gamesel != ENUM_EVS_GAMESEL_3) || (gameStateDataRef->unk_190.unk_3F == 0) ||
                            (game_state_data[1 - aipn].unk_050[0].unk_0 == 0)) {
                            joygam[gameStateDataRef->unk_298] |= 0x400;
                        }
                    }

                    if ((gameStateDataRef->unk_23A == 1) && (gameStateDataRef->unk_234 > gameStateDataRef->unk_23B)) {
                        gameStateDataRef->unk_235++;
                    } else {
                        gameStateDataRef->unk_235 += D_800884C0[gameStateDataRef->unk_293][gameStateDataRef->unk_23C];
                    }
                } else {
                    gameStateDataRef->unk_235++;
                }
            } else {
                gameStateDataRef->unk_236 = 0;
                gameStateDataRef->unk_235 += aiSlideFSpeed[gameStateDataRef->unk_293][gameStateDataRef->unk_23C];
            }
        }
    }

    if ((gameStateDataRef->unk_3BC == (gameStateDataRef->unk_23F - 1)) &&
        (gameStateDataRef->unk_3BD == gameStateDataRef->unk_240) && (gameStateDataRef->unk_238 != 0)) {
        if ((joygam[gameStateDataRef->unk_298] != 0x8000) && (joygam[gameStateDataRef->unk_298] != 0x4000)) {
            joygam[gameStateDataRef->unk_298] = 0x8000;
            gameStateDataRef->unk_238 = 0;
        }
    }

    if (gameStateDataRef->unk_293 == 6) {
        gameStateDataRef->unk_235 = 1;
    }
}
#else
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/aiset", aifKeyOut);
#endif
#endif

extern s32 tbl_2973[];

#if VERSION_US || VERSION_CN
s32 search_flash_3(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s8 sp8[8];
    s8 sp10[8];
    s32 pad[2] UNUSED;
    s32 temp_t6;
    s32 temp_t8;
    s32 var_a0_2;
    s32 i;
    s32 var_t0;
    s32 var_t1;
    s32 temp;

    for (i = 0; i < pGameState->unk_164; i++) {
        if (pGameState->unk_0D4.unk_00[i].unk_8 != arg2) {
            continue;
        }

        temp_t6 = pGameState->unk_0D4.unk_00[i].unk_0;
        temp_t8 = pGameState->unk_0D4.unk_00[i].unk_4;
        if (arg1 == temp_t8) {
            temp = 0;
            for (var_t1 = 0; var_t1 < 8; var_t1++) {
                sp8[var_t1] = -1;
            }

            for (var_t1 = -3; var_t1 < 4; var_t1++) {
                if ((temp_t6 + var_t1 >= 0) && (temp_t6 + var_t1 < 8)) {
                    if (aiFieldData[temp_t8][temp_t6 + var_t1].unk_0 != arg2) {
                        if (aiFieldData[temp_t8][temp_t6 + var_t1].unk_0 == 3) {
                            sp8[temp] = 0;
                        } else {
                            sp8[temp] = -1;
                        }
                    } else {
                        sp8[temp] = 1;
                    }
                } else {
                    sp8[temp] = -1;
                }
                temp++;
            }

            if ((arg4 == 1) && (arg3 == 1)) {
                if ((sp8[0] == 0) && (sp8[1] == 0) && (sp8[2] == 1)) {
                    if (arg0 == temp_t6 - 3) {
                        return 0x2710;
                    }
                }

                if ((sp8[1] == 0) && (sp8[2] == 0) && (sp8[4] == 1)) {
                    if (arg0 == temp_t6 - 2) {
                        return 0x2710;
                    }
                }

                if ((sp8[0] == 1) && (sp8[1] == 0) && (sp8[2] == 0)) {
                    if (arg0 == temp_t6 - 2) {
                        return 0x2710;
                    }
                }

                if ((sp8[2] == 1) && (sp8[4] == 0) && (sp8[5] == 0)) {
                    if (arg0 == temp_t6 + 1) {
                        return 0x2710;
                    }
                }

                if ((sp8[4] == 0) && (sp8[5] == 0) && (sp8[6] == 1)) {
                    if (arg0 == temp_t6 + 1) {
                        return 0x2710;
                    }
                }

                if ((sp8[4] == 1) && (sp8[5] == 0) && (sp8[6] == 0)) {
                    if (arg0 == temp_t6 + 2) {
                        return 0x2710;
                    }
                }

                if ((sp8[1] == 0) && (sp8[2] == 0)) {
                    if (arg0 == temp_t6 - 2) {
                        return 0x1388;
                    }
                }

                if ((sp8[4] == 0) && (sp8[5] == 0)) {
                    if (arg0 == temp_t6 + 1) {
                        return 0x1388;
                    }
                }
            }

            for (var_t1 = 0; var_t1 < 7; var_t1++) {
                sp10[var_t1] = sp8[var_t1];
            }

            for (var_t1 = 0; var_t1 < 7; var_t1++) {
                if (sp8[var_t1] != 0) {
                    continue;
                }

                sp8[var_t1] = 1;
                var_t0 = 0;

                for (var_a0_2 = 0; var_a0_2 < 7; var_a0_2++) {
                    if (sp8[var_a0_2] != 1) {
                        var_t0 = 0;
                    } else {
                        var_t0 += 1;
                    }

                    if ((var_t0 >= 4) && (arg0 == temp_t6 + tbl_2973[var_t1])) {
                        return 0x1388;
                    }
                }

                sp8[var_t1] = 0;
            }
        }

        if (arg0 == temp_t6) {
            temp = 0;

            for (var_t1 = 0; var_t1 < 8; var_t1++) {
                sp8[var_t1] = -1;
            }

            for (var_t1 = -3; var_t1 < 4; var_t1++) {
                if ((temp_t8 + var_t1 >= 0) && (temp_t8 + var_t1 < 0x11)) {
                    if (aiFieldData[temp_t8 + var_t1][temp_t6].unk_0 != arg2) {
                        if (aiFieldData[temp_t8 + var_t1][temp_t6].unk_0 == 3) {
                            sp8[temp] = 0;
                        } else {
                            sp8[temp] = -1;
                        }
                    } else {
                        sp8[temp] = 1;
                    }
                } else {
                    sp8[temp] = -1;
                }
                temp++;
            }

            if ((arg4 == 1) && (arg3 == 0)) {
                if ((sp8[0] == 0) && (sp8[1] == 0) && (sp8[2] == 1)) {
                    if (arg1 == (temp_t8 - 2)) {
                        return 0x2710;
                    }
                }

                if ((sp8[1] == 0) && (sp8[2] == 0) && (sp8[4] == 1)) {
                    if (arg1 == (temp_t8 - 1)) {
                        return 0x2710;
                    }
                }

                if ((sp8[0] == 1) && (sp8[1] == 0) && (sp8[2] == 0)) {
                    if (arg1 == (temp_t8 - 1)) {
                        return 0x2710;
                    }
                }

                if ((sp8[2] == 1) && (sp8[4] == 0) && (sp8[5] == 0)) {
                    if (arg1 == temp_t8 + 2) {
                        return 0x2710;
                    }
                }

                if ((sp8[4] == 0) && (sp8[5] == 0) && (sp8[6] == 1)) {
                    if (arg1 == temp_t8 + 2) {
                        return 0x2710;
                    }
                }

                if ((sp8[4] == 1) && (sp8[5] == 0) && (sp8[6] == 0)) {
                    if (arg1 == temp_t8 + 3) {
                        return 0x2710;
                    }
                }

                if ((sp8[1] == 0) && (sp8[2] == 0)) {
                    if (arg1 == temp_t8 - 1) {
                        return 0x1388;
                    }
                }

                if ((sp8[4] == 0) && (sp8[5] == 0)) {
                    if (arg1 == temp_t8 + 2) {
                        return 0x1388;
                    }
                }
            }

            for (var_t1 = 0; var_t1 < 7; var_t1++) {
                sp10[var_t1] = sp8[var_t1];
            }

            for (var_t1 = 0; var_t1 < 7; var_t1++) {
                if (sp8[var_t1] != 0) {
                    continue;
                }

                sp8[var_t1] = 1;
                var_t0 = 0;

                for (var_a0_2 = 0; var_a0_2 < 7; var_a0_2++) {
                    if (sp8[var_a0_2] != 1) {
                        var_t0 = 0;
                    } else {
                        var_t0 += 1;
                    }

                    if (var_t0 < 4) {
                        continue;
                    }
                    if (arg1 == (temp_t8 + tbl_2973[var_t1])) {
                        return 0x1388;
                    }
                }

                sp8[var_t1] = 0;
            }
        }
    }

    return 0;
}
#endif

extern s32 delpos_tbl[];

#if VERSION_US || VERSION_CN
/**
 * Original name: flash_special
 */
s32 flash_special(void) {
    s32 sp20[2];
    s32 sp28[2];
    s32 sp30[2];
    s32 temp_v0;
    s32 var_s0;
    s32 i;

    delpos_cnt = 0;

    for (i = 0; i < aiFlagCnt; i++) {
        if (aiFlag[i].unk_00 != 1) {
            continue;
        }

        sp20[0] = aiFlag[i].unk_02 - 1;
        sp28[0] = aiFlag[i].unk_03;
        if (aiFlag[i].unk_01 == 0) {
            sp20[1] = sp20[0];
            sp28[1] = sp28[0] - 1;
            if (aiFlag[i].unk_04 == 0) {
                sp30[0] = aiNext[1];
                sp30[1] = aiNext[0];
            } else {
                sp30[0] = aiNext[0];
                sp30[1] = aiNext[1];
            }
        } else {
            sp20[1] = sp20[0] + 1;
            sp28[1] = sp28[0];
            if (aiFlag[i].unk_04 == 0) {
                sp30[0] = aiNext[0];
                sp30[1] = aiNext[1];
            } else {
                sp30[0] = aiNext[1];
                sp30[1] = aiNext[0];
            }
        }

        if (sp30[0] == sp30[1]) {
            var_s0 = 1;
        } else {
            var_s0 = 0;
        }

        temp_v0 = search_flash_3(sp20[0], sp28[0], sp30[0], aiFlag[i].unk_01, var_s0);
        if (temp_v0 > 0) {
            delpos_tbl[delpos_cnt] = i;
            delpos_cnt += 1;
            aiFlag[i].unk_08 += temp_v0;
        }

        temp_v0 = search_flash_3(sp20[1], sp28[1], sp30[1], aiFlag[i].unk_01, var_s0);
        if (temp_v0 > 0) {
            delpos_tbl[delpos_cnt] = i;
            delpos_cnt += 1;
            aiFlag[i].unk_08 += temp_v0;
        }
    }

    if (delpos_cnt > 0) {
        for (i = 0; i < aiFlagCnt; i++) {
            aiFlag[i].unk_00 = 0;
        }

        for (i = 0; i < delpos_cnt; i++) {
            aiFlag[delpos_tbl[i]].unk_00 = 1;
        }
    }

    return delpos_cnt;
}
#endif

/**
 * Original name: aiCOM_MissTake
 */
void aiCOM_MissTake(void) {
    PlayTime++;

    if (PlayTime > 18000) {
        MissRate = (PlayTime - 18000) / 720;
    } else {
        MissRate = 0;
    }
}

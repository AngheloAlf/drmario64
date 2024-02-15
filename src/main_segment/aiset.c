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
#include "dm_virus_init.h"
#include "nnsched.h"

extern f32 aiRootP;

extern u8 aiRollFinal;

extern u8 aiSelCom;

extern s16 EraseLinP[];

extern s16 AloneCapP[];
extern s16 AloneCapWP[];

extern f32 HeiEraseLinRate;
extern s16 LPriP;
extern s32 OnVirusP;
extern s32 OnVirusP_org;
extern f32 WidEraseLinRate;
extern u8 aiWall;

extern u8 aiLinePri[];

#define HEI_WEI_DATA_LEN 10

extern u8 hei_data[HEI_WEI_DATA_LEN];
extern u8 wid_data[HEI_WEI_DATA_LEN];

extern u16 aiHiErB;
extern u16 aiPriOfs;
extern u16 aiHiErY;
extern u16 aiHiErR;
extern u16 aiHiEraseCtr;
extern s16 D_8009337A_cn; // pri_point._14_2_
extern s16 RensaP;
extern s16 RensaMP;

extern u8 BadLineRate[][8];

// no original name :c
void func_8002EB00(struct_game_state_data *gameStateDataRef) {
    gameStateDataRef->unk_3BC = gameStateDataRef->unk_178.unk_0[0];
    gameStateDataRef->unk_3BD = gameStateDataRef->unk_178.unk_2[0];
    gameStateDataRef->unk_3C1 = gameStateDataRef->unk_02F;
    gameStateDataRef->unk_3C0 = gameStateDataRef->unk_02D;
    gameStateDataRef->unk_3BE[0] = gameStateDataRef->unk_178.unk_6[0];
    gameStateDataRef->unk_3BE[1] = gameStateDataRef->unk_178.unk_6[1];
    gameStateDataRef->unk_29B = gameStateDataRef->unk_025;
    gameStateDataRef->unk_29A = gameStateDataRef->unk_026;
    gameStateDataRef->unk_299 = gameStateDataRef->unk_014 == 0x12;
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

#if VERSION_US || VERSION_CN
/**
 * Original name: aiHiruSideLineEraser
 */
void aiHiruSideLineEraser(struct_game_state_data *gameStateDataRef) {
    s32 sp8[2];
    s32 sp10[2];
    s32 sp18[2];
    u8 sp20[0x10];
    u8 sp30[0x10];
    u8 sp40[0x10];
    u8 sp50[0x10];
    u8 sp60[0x8];
    s32 sp68;
    s32 sp80;
    s32 temp_s3;
    s32 var_a3;
    s32 var_s1;
    s32 var_t0;
    s32 var_t0_3;
    s32 var_t1;
    s32 var_t3_2;
    s32 var_t8_2;
    s32 temp_a2_2;
    s32 temp_t5;
    s32 temp_v0_8;
    s32 var_a1;
    s32 var_t6_2;

    if ((aiFlag[decide].unk_10[4] != 0) || (aiFlag[decide].unk_1A[4] != 0)) {
        return;
    }

    sp68 = 0;
    sp80 = 1;
    var_s1 = 0;

    for (var_a3 = 0; var_a3 < 8; var_a3++) {
        sp20[var_a3] = sp30[var_a3] = sp50[var_a3] = 0x11;
        sp40[var_a3] = 0;
    }

    for (var_a3 = 0; var_a3 < 8; var_a3++) {
        for (var_a1 = 0x10, var_t0 = 0, var_t1 = 0; var_a1 >= 2; var_a1--) {
            if (gameStateDataRef->unk_29C[var_a1][var_a3][0] == 0xA) {
                var_t1 += 1;
            } else if ((gameStateDataRef->unk_29C[var_a1][var_a3][0] >= 5) &&
                       (gameStateDataRef->unk_29C[var_a1][var_a3][0] <= 7)) {
                if (var_t0 == 0) {
                    sp40[var_a3] = var_a1;
                    if (var_t1 >= 3) {
                        sp20[var_a3] = var_a1;
                    } else {
                        temp_a2_2 = gameStateDataRef->unk_29C[var_a1][var_a3][1];
                        if (((gameStateDataRef->unk_29C[var_a1 + 2][var_a3][0] == 0xA) ||
                             (gameStateDataRef->unk_29C[var_a1 + 2][var_a3][1] == temp_a2_2)) &&
                            (gameStateDataRef->unk_29C[var_a1 + 3][var_a3][1] == temp_a2_2)) {
                            sp20[var_a3] = var_a1;
                        } else if ((var_a3 == 2) || (var_a3 == 3) || (var_a3 == 4) || (var_a3 == 5)) {
                            var_t0 = -1;
                            var_t1 = 0;
                            sp40[var_a3] = 0;
                            sp30[var_a3] = var_a1;
                            sp50[var_a3] = var_a1;
                        }
                    }
                    var_t0 += 1;
                }
            } else {
                if (var_t0 == 0) {
                    sp30[var_a3] = var_a1;
                    var_t1 = 0;
                }
                sp50[var_a3] = var_a1;
            }
        }

        if (sp40[var_a3] != 0) {
            if (sp50[var_a3] < 6U) {
                sp80 = 0;
                if ((var_a3 == 2) || (var_a3 == 3) || (var_a3 == 4) || (var_a3 == 5)) {
                    sp68 = 1;
                    var_s1 = 0;
                    break;
                }
            }
        }

        if (sp40[var_a3] >= 0xE) {
            var_s1 = 1;
        }
    }

    if (var_s1 | sp80) {
        return;
    }

    for (var_a3 = 0; var_a3 < 8; var_a3++) {
        sp60[var_a3] = 1;
    }

    sp18[0] = sp18[1] = 1;
    var_s1 = 0;

    for (var_t8_2 = 0; (var_t8_2 < 8) && (var_s1 == 0); var_t8_2++) {
        var_a3 = aiLinePri[var_t8_2];
        temp_t5 = sp20[var_a3];

        if (temp_t5 >= 0xE) {
            continue;
        }

        sp60[var_a3] = 0;
        if (sp18[var_a3 / 4] == 0) {
            continue;
        }

        sp18[var_a3 / 4] = 0;
        temp_v0_8 = sp30[var_a3];
        temp_s3 = temp_v0_8 - temp_t5;

        if (var_a3 >= 4) {
            var_t6_2 = var_a3 - 1;
        } else {
            var_t6_2 = var_a3;
        }

        for (var_t3_2 = 0, sp8[0] = sp8[1] = sp10[0] = sp10[1] = 0; var_t3_2 < aiFlagCnt; var_t3_2++) {
            if ((aiFlag[var_t3_2].unk_00 != 1) || (aiFlag[var_t3_2].unk_03 != temp_v0_8 - 1)) {
                continue;
            }

            if (aiFlag[var_t3_2].unk_01 == 0) {
                if (aiFlag[var_t3_2].unk_02 - 1 == var_a3) {
                    sp8[aiFlag[var_t3_2].unk_04] = var_t3_2 + 1;
                }
            } else if (aiFlag[var_t3_2].unk_02 - 1 == var_t6_2) {
                sp10[aiFlag[var_t3_2].unk_04] = var_t3_2 + 1;
            }
        }

        if ((sp8[0] + sp10[0] + sp8[1] + sp10[1]) == 0) {
            continue;
        }

        temp_a2_2 = gameStateDataRef->unk_29C[temp_t5][var_a3][1];
        if (temp_s3 == 5) {
            if ((sp10[0] + sp10[1]) != 0) {
                var_s1 = sp10[0];
            }

            if ((sp8[0] + sp8[1]) != 0) {
                if (aiNext[0] == temp_a2_2) {
                    var_s1 = sp8[0];
                } else if (aiNext[1] == temp_a2_2) {
                    var_s1 = sp8[1];
                }
            }
        } else if (temp_s3 < 5) {
            if ((sp10[0] + sp10[1]) != 0) {
                if (aiNext[0] == temp_a2_2) {
                    if (var_a3 < 4) {
                        var_s1 = sp10[0];
                    } else {
                        var_s1 = sp10[1];
                    }
                } else if (aiNext[1] == temp_a2_2) {
                    if (var_a3 < 4) {
                        var_s1 = sp10[1];
                    } else {
                        var_s1 = sp10[0];
                    }
                }
            }

            if (sp8[0] + sp8[1]) {
                if ((aiNext[0] == aiNext[1]) && (temp_a2_2 == aiNext[0])) {
                    var_s1 = sp8[0];
                }
            }
        } else {
            if (sp8[0] != 0) {
                var_s1 = sp8[0];
            }
        }
    }

    if (var_s1 != 0) {
        decide = var_s1 - 1;
        return;
    }

    if (sp68 != 0) {
        return;
    }

    var_t1 = -1;
    var_a3 = -1000001;

    for (var_t0_3 = 0; var_t0_3 < aiFlagCnt; var_t0_3++) {
        if (aiFlag[var_t0_3].unk_01 == 0) {
            if ((sp60[aiFlag[var_t0_3].unk_02 - 1] != 0) ||
                (sp20[aiFlag[var_t0_3].unk_02 - 1] > aiFlag[var_t0_3].unk_03)) {
                if (aiFlag[var_t0_3].unk_08 > var_a3) {
                    var_a3 = aiFlag[var_t0_3].unk_08;
                    var_t1 = var_t0_3;
                }
            }
        } else {
            if (((sp60[aiFlag[var_t0_3].unk_02 - 1] != 0) ||
                 (sp20[aiFlag[var_t0_3].unk_02 - 1] > aiFlag[var_t0_3].unk_03)) &&
                ((sp60[aiFlag[var_t0_3].unk_02] != 0) || (sp20[aiFlag[var_t0_3].unk_02] > aiFlag[var_t0_3].unk_03))) {
                if (aiFlag[var_t0_3].unk_08 > var_a3) {
                    var_a3 = aiFlag[var_t0_3].unk_08;
                    var_t1 = var_t0_3;
                }
            }
        }
    }

    if (var_t1 != -1) {
        decide = var_t1;
    }
}
#endif

extern u8 srh_466[][2];

#if VERSION_US || VERSION_CN
BAD_RETURN(s32) func_8002F924(u8 row, u8 col) {
    if (aif_field[row][col].unk_1 != 4) {
        s8 temp_a0_2 = aif_field[row][col].unk_1;
        s8 temp_v0 = row + srh_466[temp_a0_2][0];
        s8 temp_v1 = col + srh_466[temp_a0_2][1];

        if ((temp_v0 > 0) && (temp_v0 < 17) && (temp_v1 >= 0) && (temp_v1 < 8)) {
            aif_field[temp_v0][temp_v1].unk_1 = 4;
        }
    }
}
#endif

#if VERSION_US || VERSION_CN
/**
 * Original name: aifEraseLineCore
 */
bool aifEraseLineCore(s32 col, s32 row) {
    bool sp18 = false;
    bool sp1C = false;
    u8 temp_s7 = aif_field[row][col].unk_0;
    s32 i;

    if (hei_data[2] >= 4) {
        sp18 = true;

        for (i = row - 1; (i > 0) && (i > row - 4); i--) {
            if (aif_field[i][col].unk_0 == temp_s7) {
                if ((aif_field[i][col].unk_1 > 4) && (aif_field[i][col].unk_1 < 8)) {
                    hei_data[1]++;
                } else {
                    func_8002F924(i, col);
                }

                if (evs_gamemode == ENUM_EVS_GAMEMODE_1) {
                    if (flash_virus(col, i) != 0) {
                        sp1C = true;
                    }
                }

                aif_field[i][col].unk_1 = 0xA;
                aif_field[i][col].unk_0 = 3;
            } else {
                i = 0;
            }
        }

        for (i = row + 1; (i < row + 4) && (i < GAME_MAP_ROWS); i++) {
            if (aif_field[i][col].unk_0 == temp_s7) {
                if ((aif_field[i][col].unk_1 > 4) && (aif_field[i][col].unk_1 < 8)) {
                    hei_data[1]++;
                } else {
                    func_8002F924(i, col);
                }

                aif_field[i][col].unk_1 = 0xA;
                aif_field[i][col].unk_0 = 3;
            } else {
                i = GAME_MAP_ROWS;
            }
        }
    }

    if (wid_data[2] >= 4) {
        sp18 = true;

        for (i = col - 1; (i > -1) && (i > col - 4); i--) {
            if (aif_field[row][i].unk_0 == temp_s7) {
                if ((aif_field[row][i].unk_1 > 4) && (aif_field[row][i].unk_1 < 8)) {
                    wid_data[1]++;
                } else {
                    func_8002F924(row, i);
                }

                aif_field[row][i].unk_1 = 0xA;
                aif_field[row][i].unk_0 = 3;
            } else {
                i = -1;
            }
        }

        for (i = col + 1; (i < col + 4) && (i < GAME_MAP_COLUMNS); i++) {
            if (aif_field[row][i].unk_0 == temp_s7) {
                if ((aif_field[row][i].unk_1 > 4) && (aif_field[row][i].unk_1 < 8)) {
                    wid_data[1]++;
                } else {
                    func_8002F924(row, i);
                }

                if (evs_gamemode == ENUM_EVS_GAMEMODE_1) {
                    if (flash_virus(i, row) != 0) {
                        sp1C = true;
                    }
                }

                aif_field[row][i].unk_1 = 0xA;
                aif_field[row][i].unk_0 = 3;
            } else {
                i = GAME_MAP_COLUMNS;
            }
        }
    }

    if (sp18) {
        func_8002F924(row, col);

        aif_field[row][col].unk_1 = 0xA;
        aif_field[row][col].unk_0 = 3;
    }

    return sp1C;
}
#endif

#if VERSION_US || VERSION_CN
/**
 * Original name: aifRensaCheckCore
 */
s32 aifRensaCheckCore(struct_game_state_data *gameStateDataRef, struct_aiFlag *aiFlagRef UNUSED, u8 arg2, u8 arg3,
                      u8 arg4, u8 arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9) {
    u8 sp18 = 0;
    u8 var_s1;
    u8 var_s3;
    u8 temp;
    s32 row;
    s32 col;

    for (col = 0; col < GAME_MAP_COLUMNS; col++) {
        for (row = 0; row < GAME_MAP_ROWS; row++) {
            aif_field[row][col].unk_0 = gameStateDataRef->unk_29C[row][col][1];
            aif_field[row][col].unk_1 = gameStateDataRef->unk_29C[row][col][0];
        }
    }

    aiHiEraseCtr = 0;

    for (col = 0; col < GAME_MAP_COLUMNS; col++) {
        for (row = 1; row < 4; row++) {
            if (aif_field[row][col].unk_1 < 8U) {
                aiHiEraseCtr += BadLineRate[row][col];
            }
        }
    }

    if (arg3 != 0) {
        aif_field[arg3][arg2].unk_1 = arg5;
        aif_field[arg3][arg2].unk_0 = arg4;
    }

    if (arg7 != 0) {
        aif_field[arg7][arg6].unk_1 = arg9;
        aif_field[arg7][arg6].unk_0 = arg8;
    }

    for (row = 1; row < GAME_MAP_ROWS; row++) {
        for (col = 0; col < GAME_MAP_COLUMNS - 3; col++) {
            if (aif_field[row][col].unk_1 != 0xA) {
                temp = aif_field[row][col].unk_0;
                for (var_s3 = 1; col + var_s3 < 8; var_s3++) {
                    if ((aif_field[row][col + var_s3].unk_1 == 0xA) || (aif_field[row][col + var_s3].unk_0 != temp)) {
                        break;
                    }
                }

                if (var_s3 >= 4) {
                    sp18 += var_s3 / 4;

                    for (var_s1 = 0; var_s1 < var_s3; var_s1++) {
                        func_8002F924(row, col + var_s1);
                        aif_field[row][col + var_s1].unk_1 = 8;
                    }
                }
                col += var_s3 - 1;
            }
        }
    }

    for (col = 0; col < GAME_MAP_COLUMNS; col++) {
        for (row = 1; row < GAME_MAP_ROWS - 3; row++) {
            if (aif_field[row][col].unk_1 != 0xA) {
                temp = aif_field[row][col].unk_0;
                for (var_s3 = 1; row + var_s3 < GAME_MAP_ROWS; var_s3++) {
                    if ((aif_field[row + var_s3][col].unk_1 == 0xA) || (aif_field[row + var_s3][col].unk_0 != temp)) {
                        break;
                    }
                }

                if (var_s3 >= 4U) {
                    sp18 += var_s3 / 4;

                    for (var_s1 = 0; var_s1 < var_s3; var_s1++) {
                        func_8002F924(row + var_s1, col);
                        aif_field[row + var_s1][col].unk_1 = 8;
                    }
                }

                row += var_s3 - 1;
            }
        }
    }

    var_s3 = 1;

    for (row = GAME_MAP_ROWS - 1; row > 0; row--) {
        for (col = GAME_MAP_COLUMNS - 1; col >= 0; col--) {
            switch (aif_field[row][col].unk_1) {
                case 0x8:
                    aif_field[row][col].unk_1 = 0xA;
                    break;

                case 0x4:
                    if (row != GAME_MAP_ROWS - 1) {
                        if (aif_field[row + 1][col].unk_1 == 0xA) {
                            var_s3 = 0;

                            for (var_s1 = row + 1; var_s1 < GAME_MAP_ROWS; var_s1++) {
                                if (aif_field[var_s1][col].unk_1 != 0xA) {
                                    break;
                                }
                            }

                            var_s1--;
                            aif_field[var_s1][col].unk_1 = aif_field[row][col].unk_1;
                            aif_field[var_s1][col].unk_0 = aif_field[row][col].unk_0;
                            aif_field[row][col].unk_1 = 0xA;
                        }
                    }
                    break;

                case 1:
                    if (row != GAME_MAP_ROWS - 1) {
                        if (aif_field[row + 1][col].unk_1 == 0xA) {
                            var_s3 = 0;

                            for (var_s1 = row + 1; var_s1 < GAME_MAP_ROWS; var_s1++) {
                                if (aif_field[var_s1][col].unk_1 != 0xA) {
                                    break;
                                }
                            }

                            var_s1--;
                            aif_field[var_s1][col].unk_1 = aif_field[row][col].unk_1;
                            aif_field[var_s1][col].unk_0 = aif_field[row][col].unk_0;
                            aif_field[row][col].unk_1 = 0xA;

                            aif_field[var_s1 - 1][col].unk_1 = aif_field[row - 1][col].unk_1;
                            aif_field[var_s1 - 1][col].unk_0 = aif_field[row - 1][col].unk_0;
                            aif_field[row - 1][col].unk_1 = 0xA;
                        }
                    }
                    break;

                case 2:
                    if (row != GAME_MAP_ROWS - 1) {
                        if ((aif_field[row + 1][col].unk_1 == 0xA) &&
                            (aif_field[row + 1][col + 1].unk_1 == aif_field[row + 1][col].unk_1)) {
                            var_s3 = 0;

                            for (var_s1 = row + 1; (var_s1 < GAME_MAP_ROWS) && (aif_field[var_s1][col].unk_1 == 0xA) &&
                                                   (aif_field[var_s1][col + 1].unk_1 == 0xA);
                                 var_s1++) {
                                ;
                            }

                            var_s1--;
                            aif_field[var_s1][col].unk_1 = aif_field[row][col].unk_1;
                            aif_field[var_s1][col].unk_0 = aif_field[row][col].unk_0;
                            aif_field[row][col].unk_1 = 0xA;

                            aif_field[var_s1][col + 1].unk_1 = aif_field[row][col + 1].unk_1;
                            aif_field[var_s1][col + 1].unk_0 = aif_field[row][col + 1].unk_0;
                            aif_field[row][col + 1].unk_1 = 0xA;
                        }
                    }
                    break;
            }
        }
    }

    for (col = 0; col < GAME_MAP_COLUMNS; col++) {
        for (row = 1; row < 4; row++) {
            if (aif_field[row][col].unk_1 < 8U) {
                aiHiEraseCtr -= BadLineRate[row][col];
            }
        }
    }

    if (sp18 >= 2) {
        if (var_s3 != 0) {
            return 2;
        }
        return 1;
    }

    for (row = 1; row < GAME_MAP_ROWS; row++) {
        for (col = 0; col < GAME_MAP_COLUMNS - 3; col++) {
            if (aif_field[row][col].unk_1 != 0xA) {
                temp = aif_field[row][col].unk_0;
                for (var_s3 = 1; (col + var_s3 < GAME_MAP_COLUMNS) && (aif_field[row][col + var_s3].unk_1 != 0xA) &&
                                 (aif_field[row][col + var_s3].unk_0 == temp);
                     var_s3++) {
                    ;
                }

                if (var_s3 >= 4U) {
                    return 1;
                }
            }
        }
    }

    for (col = 0; col < GAME_MAP_COLUMNS; col++) {
        for (row = 1; row < GAME_MAP_ROWS - 3; row++) {
            if (aif_field[row][col].unk_1 != 0xA) {
                temp = aif_field[row][col].unk_0;
                for (var_s3 = 1; (row + var_s3 < GAME_MAP_ROWS) && (aif_field[row + var_s3][col].unk_1 != 0xA) &&
                                 (aif_field[row + var_s3][col].unk_0 == temp);
                     var_s3++) {
                    ;
                }

                if (var_s3 >= 4) {
                    return 1;
                }
            }
        }
    }

    return 0;
}
#endif

#if VERSION_US || VERSION_CN
/**
 * Original name: aifRensaCheck
 */
s32 aifRensaCheck(struct_game_state_data *gameStateDataRef, struct_aiFlag *aiFlagRef) {
    u8 temp_a2 = aiFlagRef->unk_02 - 1;
    u8 temp_a3 = aiFlagRef->unk_03;
    u8 var_t0;
    u8 var_t5;
    u8 var_t4;
    u8 var_t3;
    u8 var_t1; //! @bug: sometimes not set
    u8 var_t2;

    if (aiFlagRef->unk_01 == 0) {
        var_t5 = 1;
        var_t4 = temp_a2;
        var_t3 = temp_a3 - 1;
        var_t2 = 0;
        if (aiFlagRef->unk_04 == 0) {
            var_t0 = aiNext[1];
            if (temp_a3 - 1 > 0) {
                var_t1 = aiNext[0];
            }
        } else {
            var_t0 = aiNext[0];
            if (temp_a3 - 1 > 0) {
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

#if VERSION_CN
/**
 * Original name: aifSearchLineCore
 */
// TODO: I wonder if arg2 could be an enum
bool aifSearchLineCore(s32 arg0, s32 arg1, s32 arg2) {
    u8 temp_s2 = aif_field[arg1][arg0].unk_0;
    s32 i;
    s32 j;
    s32 var_t3;
    bool var_t0_3;
    bool var_t4;

    for (j = 0; j < HEI_WEI_DATA_LEN; j++) {
        hei_data[j] = wid_data[j] = 0;
    }

    if (aif_field[arg1][arg0].unk_1 == 0xA) {
        return false;
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

extern s16 pri_point[];

extern s16 HeiLinesAllp[];
extern s16 WidLinesAllp[];

#if VERSION_US || VERSION_CN
/**
 * Original name: aifMiniPointK3
 */
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

#if VERSION_US || VERSION_CN
/**
 * Original name: aifMiniAloneCapNumber
 */
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

#if VERSION_US || VERSION_CN
/**
 * Original name: aifMiniAloneCapNumberW
 */
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

#if VERSION_US || VERSION_CN
/**
 * Original name: flash_virus
 */
s32 flash_virus(s32 col, s32 row) {
    s32 i;

    for (i = 0; i < pGameState->unk_164; i++) {
        if ((pGameState->unk_0D4.unk_00[i].unk_8 >= 0) && (col == pGameState->unk_0D4.unk_00[i].unk_0) &&
            (row == pGameState->unk_0D4.unk_00[i].unk_4)) {
            return pGameState->unk_0D4.unk_00[i].unk_8;
        }
    }

    return -1;
}
#endif

#if VERSION_US || VERSION_CN
/**
 * Original name: search_Vflash
 */
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

#if VERSION_US || VERSION_CN
bool func_8003151C(s32 arg0 UNUSED, s32 arg1) {
    s32 i;

    for (i = 0; i < pGameState->unk_164; i++) {
        if ((pGameState->unk_0D4.unk_00[i].unk_8 >= 0) && (arg1 == pGameState->unk_0D4.unk_00[i].unk_4)) {
            return true;
        }
    }

    return false;
}
#endif

extern s16 WallRate[][8];
extern s16 bad_point[];
extern s16 bad_point2[];

#if VERSION_US || VERSION_CN
/**
 * Original name: aifSearchLineMS
 */
s32 aifSearchLineMS(struct_aiFlag *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7) {
    u8 sp20[8];
    bool sp28;
    bool sp2C;
    s32 temp;
    s32 sp30;
    s32 var_a0;
    s32 var_a2;
    s32 var_a2_2;
    s32 var_a2_3;
    s32 var_s0;
    s32 var_s1;
    s32 var_s2;
    s32 var_s4;

    var_s4 = 0;
    temp = arg2;
    sp30 = arg5;

    for (var_a2 = 0; var_a2 < STRUCT_AIFLAG_UNK_LEN; var_a2++) {
        arg0->unk_24[var_a2] = arg0->unk_10[var_a2] = arg0->unk_2E[var_a2] = arg0->unk_1A[var_a2] = 0;
    }

    arg0->unk_39 = 0;
    arg0->unk_38[0] = 0;
    arg0->unk_3E = 0;
    arg0->unk_3B = 0;
    arg0->unk_3A = 0;
    arg0->unk_3D = 0;
    arg0->unk_3C = 0;
    sp28 = aifSearchLineCore(arg1, arg2, 0);
    sp2C = false;

    if (aifEraseLineCore(arg1, arg2)) {
        var_s4 = 1;
        arg0->unk_08 += 0x2710;
    }

    if (sp28 == false) {
        arg0->unk_3A = aifMiniAloneCapNumber(arg1, arg2, 0, arg7);
        arg0->unk_3C = aifMiniAloneCapNumberW(arg1, arg2, 0, arg7);
    }

    for (var_a2_2 = 0; var_a2_2 < STRUCT_AIFLAG_UNK_LEN; var_a2_2++) {
        arg0->unk_10[var_a2_2] = hei_data[var_a2_2];
        arg0->unk_24[var_a2_2] = wid_data[var_a2_2];
    }

    if (aif_field[arg5][arg4].unk_1 != 0xA) {
        if (arg7 != 0) {
            if (arg0->unk_01 == 0) {
                var_a2_3 = 2;
            } else {
                var_a2_3 = 1;
            }
        } else {
            var_a2_3 = 0;
        }

        var_s0 = 0;
        sp2C = aifSearchLineCore(arg4, arg5, var_a2_3);
        if (sp2C == false) {
            if (sp28 != false) {
                for (var_s1 = 0x10; var_s1 > arg5; var_s1--) {
                    if (aif_field[var_s1][arg4].unk_1 == 4) {
                        for (var_a2_2 = var_s1 + 1; var_a2_2 < 0x11; var_a2_2++) {
                            if (aif_field[var_a2_2][arg4].unk_1 != 0xA) {
                                break;
                            }
                        }

                        if (var_a2_2 != var_s1 + 1) {
                            aif_field[var_a2_2 - 1][arg4].unk_1 = 4;
                            aif_field[var_a2_2 - 1][arg4].unk_0 = aif_field[var_s1][arg4].unk_0;
                            aif_field[var_s1][arg4].unk_1 = 0xA;
                            aif_field[var_s1][arg4].unk_0 = 3;
                        }
                    }
                }
            }

            for (var_a2_2 = arg5 + 1; (var_a2_2 < 0x11) && (aif_field[var_a2_2][arg4].unk_1 == 0xA); var_a2_2++) {
                ;
            }

            if (var_a2_2 != arg5 + 1) {
                aif_field[var_a2_2 - 1][arg4].unk_1 = 4;
                aif_field[var_a2_2 - 1][arg4].unk_0 = aif_field[arg5][arg4].unk_0;
                aif_field[arg5][arg4].unk_1 = 0xA;
                aif_field[arg5][arg4].unk_0 = 3;

                var_s0 = 1;
                arg5 = var_a2_2 - 1;
                if (sp28 == false) {
                    arg0->unk_3E = 1;
                }
                sp2C = aifSearchLineCore(arg4, arg5, 0);
            }
        }

        if (aifEraseLineCore(arg4, arg5)) {
            var_s4 = 1;
            arg0->unk_08 += 0x2710;
        }

        if (sp2C == false) {
            arg0->unk_3B = aifMiniAloneCapNumber(arg4, arg5, var_s0, arg7);
            arg0->unk_3D = aifMiniAloneCapNumberW(arg4, arg5, var_s0, arg7);
        }

        for (var_a2_2 = 0; var_a2_2 < 0xA; var_a2_2++) {
            arg0->unk_1A[var_a2_2] = hei_data[var_a2_2];
            arg0->unk_2E[var_a2_2] = wid_data[var_a2_2];
        }
    }

    if (evs_gamemode == ENUM_EVS_GAMEMODE_1) {
        OnVirusP = OnVirusP_org + 0x7D0;
        if (var_s4 == 0) {
            if (arg7 != 0) {
                if (search_Vflash(arg1, arg2, arg3) != false) {
                    var_s4 = 1;
                }
                if (search_Vflash(arg4, arg5, arg6) != false) {
                    var_s4 = 1;
                }
                if (var_s4 != 0) {
                    arg0->unk_08 += 0xBB8;
                }
            } else if (arg0->unk_01 == evs_gamemode) {
                if (search_Vflash(arg1, arg2, arg3) != false) {
                    var_s4 = 1;
                }
                if (search_Vflash(arg4, arg5, arg6) != false) {
                    var_s4 = 1;
                }
                if (var_s4 != 0) {
                    arg0->unk_08 += 0x3E8;
                }
            }
        }
    }

    arg0->unk_08 += aifMiniPointK3(arg0->unk_10, 0, &arg0->unk_38[0], 1, arg0->unk_01, arg7);
    arg0->unk_08 += aifMiniPointK3(arg0->unk_1A, arg0->unk_3E, &arg0->unk_38[arg0->unk_3E], 1, arg0->unk_01, arg7);
    arg0->unk_08 += aifMiniPointK3(arg0->unk_24, 0, &arg0->unk_38[0], 0, arg0->unk_01, arg7);
    arg0->unk_08 += aifMiniPointK3(arg0->unk_2E, arg0->unk_3E, &arg0->unk_38[arg0->unk_3E], 0, arg0->unk_01, arg7);

    if (AloneCapP[arg0->unk_3A] != 0) {
        arg0->unk_08 += AloneCapP[arg0->unk_3A];
    }
    if (AloneCapP[arg0->unk_3B] != 0) {
        arg0->unk_08 += AloneCapP[arg0->unk_3B];
    }
    if ((AloneCapP[arg0->unk_3A] != 0) && (AloneCapP[arg0->unk_3B] != 0)) {
        arg0->unk_08 -= (0x11 - temp) * LPriP;
    }
    if (AloneCapWP[arg0->unk_3C] != 0) {
        arg0->unk_08 += AloneCapWP[arg0->unk_3A];
    }
    if (AloneCapWP[arg0->unk_3D] != 0) {
        arg0->unk_08 += AloneCapWP[arg0->unk_3B];
    }

    arg0->unk_08 += (s32)(EraseLinP[arg0->unk_10[0] + arg0->unk_1A[0]] * HeiEraseLinRate);
    arg0->unk_08 += (s32)(EraseLinP[arg0->unk_24[0] + arg0->unk_2E[0]] * WidEraseLinRate);

    if ((OnVirusP != 0) && (temp < 0x10)) {
        var_s0 = 1;

        for (var_s1 = temp - 1; var_s1 >= 4; var_s1--) {
            if ((aiFieldData[var_s1][arg1].unk_1 >= 5) && (aiFieldData[var_s1][arg1].unk_1 <= 7)) {
                var_s0 = 0;
                break;
            }
        }

        if (var_s0 == 1) {
            var_s0 = 0;

            for (var_s1 = temp + 1; var_s1 < 0x11; var_s1 += 1) {
                if ((aiFieldData[var_s1][arg1].unk_1 >= 5) && (aiFieldData[var_s1][arg1].unk_1 <= 7)) {
                    var_s0 = 1;
                    break;
                }
            }
        }

        var_s2 = 1;
        for (var_s1 = sp30 - 1; var_s1 >= 4; var_s1--) {
            if ((aiFieldData[var_s1][arg4].unk_1 >= 5) && (aiFieldData[var_s1][arg4].unk_1 <= 7)) {
                var_s2 = 0;
                break;
            }
        }

        if (var_s2 != 0) {
            var_s2 = 0;
            for (var_s1 = sp30 + 1; var_s1 < 0x11; var_s1++) {
                if ((aiFieldData[var_s1][arg4].unk_1 >= 5) && (aiFieldData[var_s1][arg4].unk_1 <= 7)) {
                    var_s2 = 1;
                    break;
                }
            }
        }

        var_s4 = 0;
        if (evs_gamemode == ENUM_EVS_GAMEMODE_1) {
            if (var_s0 != 0) {
                for (var_s1 = temp + 1; var_s1 < 0x11; var_s1++) {
                    if (flash_virus(arg1, var_s1) != -1) {
                        var_s4 += OnVirusP;
                    }
                }
            }

            if (var_s2 != 0) {
                for (var_s1 = sp30 + 1; var_s1 < 0x11; var_s1++) {
                    if (flash_virus(arg4, var_s1) != -1) {
                        var_s4 += OnVirusP;
                    }
                }
            }
        }

        if (aiFieldData[arg2 + 1][arg1].unk_1 < 8U) {
            if (var_s0 != 0) {
                if ((arg0->unk_10[2] >= (((arg7 != 0) && (arg0->unk_01 == 0)) ? 3 : 2)) && (arg0->unk_10[5] >= 4)) {
                    if (arg0->unk_01 == 0) {
                        if (arg7 != 0) {
                            arg0->unk_08 += (OnVirusP + var_s4) * 2;
                        } else if (sp28 == false) {
                            arg0->unk_08 -= OnVirusP * 2;
                        }
                    } else {
                        if (var_s2 != 0) {
                            if ((arg0->unk_1A[3] >= 2) && (arg0->unk_1A[5] >= 4)) {
                                arg0->unk_08 += OnVirusP + var_s4;
                            } else {
                                arg0->unk_08 -= OnVirusP * 2;
                            }
                        } else {
                            arg0->unk_08 += OnVirusP + var_s4;
                        }
                    }
                } else {
                    arg0->unk_08 -= OnVirusP * 2;
                }
            } else if (var_s2 != 0) {
                if ((arg0->unk_1A[3] >= 2) && (arg0->unk_1A[5] >= 4)) {
                    if ((arg0->unk_10[2] >= 3) && (arg0->unk_10[5] >= 4)) {
                        arg0->unk_08 += OnVirusP + var_s4;
                    } else {
                        arg0->unk_08 -= OnVirusP * 2;
                    }
                } else {
                    arg0->unk_08 -= OnVirusP * 2;
                }
            }
        } else if (var_s2 != 0) {
            if ((arg0->unk_1A[2] >= 2) && (arg0->unk_1A[5] >= 4)) {
                if (var_s0 != 0) {
                    if ((arg0->unk_10[3] >= 2) && (arg0->unk_10[5] >= 4)) {
                        arg0->unk_08 += OnVirusP + var_s4;
                    } else {
                        arg0->unk_08 -= OnVirusP * 2;
                    }
                } else {
                    arg0->unk_08 += OnVirusP + var_s4;
                }
            } else {
                arg0->unk_08 -= OnVirusP * 2;
            }
        } else if (var_s0 != 0) {
            if ((arg0->unk_10[3] >= 2) && (arg0->unk_10[5] >= 4)) {
                if ((arg0->unk_1A[2] >= 3) && (arg0->unk_1A[5] >= 4)) {
                    arg0->unk_08 += OnVirusP + var_s4;
                } else {
                    arg0->unk_08 -= OnVirusP * 2;
                }
            } else {
                arg0->unk_08 -= OnVirusP * 2;
            }
        }

        if ((sp28 != false) && (arg7 == 0) && (arg0->unk_01 == 0) && (temp < 0x10)) {
            var_a2_2 = 0;

            for (var_s0 = temp + 1; var_s0 < 0x11; var_s0++) {
                if ((aiFieldData[var_s0][arg4].unk_1 >= 8U) || (aiFieldData[var_s0][arg4].unk_0 != arg3)) {
                    var_a2_2 = 1;
                    break;
                }
            }

            if (var_a2_2 != 0) {
                var_a2_2 = 0;
                for (var_s1 = var_s0; var_s1 < 0x11; var_s1++) {
                    if ((aiFieldData[var_s1][arg4].unk_1 >= 5) && (aiFieldData[var_s1][arg4].unk_1 <= 7)) {
                        var_a2_2 = 1;
                        break;
                    }
                }
            }

            if (var_a2_2 != 0) {
                for (var_s1 = var_s0; var_s1 < 0x11; var_s1++) {
                    if (aiFieldData[var_s1][arg4].unk_1 < 8) {
                        if (aiFieldData[var_s1][arg4].unk_0 == arg6) {
                            arg0->unk_08 += (OnVirusP + var_s4) * 4;
                        } else {
                            arg0->unk_08 -= OnVirusP * 2;
                        }
                        break;
                    }
                }
            }
        }
    }

    for (var_a0 = 0; var_a0 < 8; var_a0++) {
        for (var_s1 = 1; var_s1 < 0x11; var_s1++) {
            if (aif_field[var_s1][var_a0].unk_1 != 0xA) {
                sp20[var_a0] = var_s1 - 1;
                break;
            }
        }
    }

    arg0->unk_0C = 0;
    var_s0 = 0;
    if ((sp20[arg4] < 4U) && (arg5 < 5) && (arg5 > 0)) {
        if (aif_field[arg5][arg4].unk_1 != 0xA) {
            if (arg0->unk_1A[2] + sp20[arg4] < 4) {
                arg0->unk_0C += (bad_point[arg4] / (arg5 * 2 - 1));
                var_s0 = 1;
            }
        }
    }

    if ((sp20[arg1] < 4U) && (arg2 < 4) && (arg2 > 0) && ((arg7 == 0) || (arg0->unk_01 != 0))) {
        if ((aif_field[arg2][arg1].unk_1 != 0xA) && ((arg0->unk_10[2] + sp20[arg1]) < 4)) {
            if (var_s0 != 0) {
                arg0->unk_0C += bad_point2[arg1] + bad_point2[arg4] - (bad_point[arg4] / (arg5 * 2 - 1));
            } else {
                arg0->unk_0C += bad_point[arg1] / (arg2 * 2 - 1);
            }
        }
    }

    arg0->unk_08 += arg0->unk_0C;
    if (aiWall != 0) {
        if (WallRate[aiWall][arg1] > WallRate[aiWall][arg4]) {
            arg0->unk_08 = arg0->unk_08 * WallRate[aiWall][arg1] / 10;
        } else {
            arg0->unk_08 = arg0->unk_08 * WallRate[aiWall][arg4] / 10;
        }
    }

    if (sp28) {
        return 1;
    }
    if (sp2C) {
        return 2;
    }
    return 0;
}
#endif

#if VERSION_US
/**
 * Original name: aiHiruAllPriSet
 */
#if 0
u8 aifRensaCheckCore(struct_game_state_data *, u8 *, u32, u8, s32, s32, u32, s32, s32, s32); /* extern */
s32 aifSearchLineMS(u8 *, s32, u8, s32);              /* extern */
extern u16 aiHiErB;
extern u16 aiPriOfs;
extern u16 aiHiErY;
extern u16 aiHiErR;
extern u16 aiHiEraseCtr;
extern s16 D_8008856A;
extern s16 RensaP;
extern s16 RensaMP;

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
                if ((temp_v0_5 != 0) && (RensaP != 0)) {
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
                                    var_v0 = var_a1_2 + (RensaP * sp5F);
                                } else {
                                    var_v0 = var_a1_2 + (RensaP * sp5F);
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
                                    var_v0 = var_a1_2 + RensaMP;
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
                                    var_v0 = var_a1_2 + (RensaP * sp67);
                                } else {
                                    var_v0 = var_a1_2 + (RensaP * sp67);
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
                                    var_v0 = var_a1_2 + (RensaP * sp6F);
                                } else {
                                    var_v0 = var_a1_2 + (RensaP * sp6F);
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
                if (aiPriOfs != 0) {
                    var_a2_2 = genrand((s32) aiPriOfs) & 0xFFFF;
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
                if (aiPriOfs != 0) {
                    var_a0 = (aiPriOfs + 0x64) & 0xFFFF;
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

#if VERSION_US || VERSION_CN
/**
 * Original name: aiSetCharacter
 */
void aiSetCharacter(struct_game_state_data *gameStateDataRef) {
    u8 var_a0_8;
    s32 var_a1_2;
    u8 var_a2_3;
    u8 var_a3_4;
    s32 var_s0;
    struct_ai_char_data *temp_s2;
    u8 var_s3;
    s32 var_s5;
    u8 var_s6;
    s32 var_t0_2;
    struct_ai_param *temp_t1;
    u8 var_t3_2;
    s32 var_v1;
    s32 var_t1;
    struct_ai_param(*temp)[AI_PARAM_LEN2];

    {
        s32 dummy = gameStateDataRef->unk_29A;

        if (dummy < 0x18) {
            dummy = 1;
        }
    }

    var_s3 = 0;

    for (var_t1 = 2; var_t1 < 6; var_t1++) {
        var_s0 = 0;

        for (var_v1 = 1; var_v1 < 4; var_v1++) {
            if (var_s0 == 0) {
                if (aiFieldData[var_v1][var_t1].unk_1 != 0xA) {
                    var_s0 = 1;
                    var_a1_2 = aiFieldData[var_v1][var_t1].unk_0;
                }
            }

            if (var_s0 != 0) {
                if ((aiFieldData[var_v1 + 1][var_t1].unk_1 == 0xA) ||
                    (aiFieldData[var_v1 + 1][var_t1].unk_0 != var_a1_2)) {
                    if ((var_t1 == 3) || (var_t1 == 4)) {
                        var_s0 = 2;
                    } else {
                        var_s0 = 0;
                    }
                    break;
                }
            }
        }

        if (var_s0 != 0) {
            var_s3 = var_s0;
            if (var_s0 == 2) {
                break;
            }
        }
    }

    var_s6 = 0;
    var_t3_2 = 0x11;
    var_t0_2 = 0;

    for (var_t1 = 4; var_t1 < 8; var_t1++) {
        for (var_v1 = 1; var_v1 < 4; var_v1++) {
            if (aiFieldData[var_v1][var_t1].unk_1 != 0xA) {
                break;
            }
        }

        if (var_v1 < 4) {
            var_s6 |= 2;
            var_a1_2 = var_t1;
            break;
        }

        for (; var_v1 < 0x11; var_v1++) {
            if ((aiFieldData[var_v1][var_t1].unk_1 != 0xA) && (var_v1 < var_t3_2)) {
                var_t3_2 = var_v1;
            }
            if ((aiFieldData[var_v1][var_t1].unk_1 >= 5) && (aiFieldData[var_v1][var_t1].unk_1 <= 7)) {
                var_t0_2 += 1;
            }
        }
    }

    for (var_t1 = 3; var_t1 >= 0; var_t1--) {
        for (var_v1 = 1; var_v1 < 4; var_v1++) {
            if (aiFieldData[var_v1][var_t1].unk_1 != 0xA) {
                break;
            }
        }

        if (var_v1 < 4) {
            var_s6 |= 1;
            if ((var_a1_2 - var_t1) < 4) {
                var_s6 = 0;
                var_t0_2 = gameStateDataRef->unk_29B;
            }
            break;
        }

        for (; var_v1 < 0x11; var_v1++) {
            if ((aiFieldData[var_v1][var_t1].unk_1 != 0xA) && (var_v1 < var_t3_2)) {
                var_t3_2 = var_v1;
            }
            if ((aiFieldData[var_v1][var_t1].unk_1 >= 5) && (aiFieldData[var_v1][var_t1].unk_1 <= 7)) {
                var_t0_2 += 1;
            }
        }
    }

    var_a2_3 = 0;

    for (var_t1 = 0; var_t1 < 8; var_t1++) {
        for (var_v1 = 0x11; var_v1 >= 4; var_v1--) {
            if ((aiFieldData[var_v1][var_t1].unk_1 >= 5) && (aiFieldData[var_v1][var_t1].unk_1 <= 7)) {
                if (var_a2_3 < var_v1) {
                    var_a2_3 = var_v1;
                }
                break;
            }
        }
    }

    var_a3_4 = 1;
    if (evs_gamesel == ENUM_EVS_GAMESEL_3) {
        for (var_s0 = 0; var_s0 < evs_playcnt; var_s0++) {
            if (game_state_data[var_s0].unk_29B < game_state_data[aipn].unk_29B) {
                var_a3_4 = 0;
            }
        }
    }

    //! FAKE?
    temp = ai_param;

    var_a0_8 = gameStateDataRef->unk_04D;
    if ((aipn == 0) && (aiDebugP1 >= 0)) {
        var_a0_8 = aiDebugP1;
    }
    temp_s2 = &ai_char_data[var_a0_8];

    gameStateDataRef->unk_296 = 0;
    gameStateDataRef->unk_239 &= ~0xFE;
    gameStateDataRef->unk_292 &= ~4;
    aiPriOfs = 0;

    if (gameStateDataRef->unk_299 != 0) {
        var_s5 = 0;
    } else if (aiRootP < 4.0) {
        var_s5 = 1;
    } else if (((gameStateDataRef->unk_29B < 7) && (var_a3_4 != 0)) || (var_t0_2 < 3)) {
        if ((var_t0_2 != 0) || (var_t3_2 < var_a2_3 - 4) || (var_t3_2 < 9)) {
            if (var_t0_2 != 0) {
                var_s5 = 2;
            } else {
                var_s5 = 3;
            }
        } else {
            var_s5 = 4;
        }
    } else {
        if (var_s3 == 2) {
            var_s5 = 5;
        } else {
            if (var_s3 == 1) {
                var_s5 = 6;
            } else {
                var_s5 = 7;
            }
        }
    }

    aiSelCom = temp_s2->unk_04[var_s5];
    aiSelSpeed = temp_s2->unk_01;

    if (evs_gamemode == ENUM_EVS_GAMEMODE_1) {
        if (last_flash > 1) {
            aiSelCom = 0;
        } else {
            aiSelCom = 4;
        }
    }

    if (s_hard_mode != 0) {
        if (var_s5 == 7) {
            switch (aiSelCom) {
                case 0x0:
                    aiSelCom = 2;
                    break;

                case 0x1:
                    aiSelCom = 3;
                    break;

                case 0x4:
                    aiSelCom = 4;
                    break;

                case 0x5:
                    aiSelCom = 5;
                    break;
            }
        }
    }

    if ((fool_mode == 1) && (framecont & 0x200)) {
        for (var_a1_2 = 0; var_a1_2 < 0x10; var_a1_2++) {
            gameStateDataRef->unk_242[var_a1_2] = 0;
        }

        aiSelCom = 0;
    }

    for (var_s0 = 0; var_s0 < 0x10; var_s0++) {
        s32 var_t1_5; // bool
        var_t1_5 = 0;

        gameStateDataRef->unk_272[var_s0] = MIN(0x3E7, gameStateDataRef->unk_272[var_s0] + 1);

        switch (gameStateDataRef->unk_242[var_s0]) {
            case 1:
            case 2:
                gameStateDataRef->unk_242[var_s0] = 0;
                break;

            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
                if (gameStateDataRef->unk_252[var_s0] != 0) {
                    if (gameStateDataRef->unk_272[var_s0] >= gameStateDataRef->unk_252[var_s0]) {
                        gameStateDataRef->unk_242[var_s0] = 0;
                    }
                }
                break;
        }

        if (gameStateDataRef->unk_242[var_s0] == 0) {
            switch (temp_s2->unk_0C[var_s0]) {
                case 0x2:
                    var_t1_5 = genrand(0x64U) <= temp_s2->unk_1C[var_s0];
                    break;

                case 0x3:
                    if (gameStateDataRef->unk_292 & 1) {
                        var_t1_5 = 1;
                        gameStateDataRef->unk_292 &= ~1;
                    }
                    break;

                case 0x4:
                    for (var_a1_2 = 0; var_a1_2 < evs_playcnt; var_a1_2++) {
                        if (var_a1_2 == aipn) {
                            continue;
                        }
                        if ((game_state_data[aipn].unk_29B - game_state_data[var_a1_2].unk_025) >=
                            temp_s2->unk_1C[var_s0]) {
                            var_t1_5 = 1;
                            break;
                        }
                    }
                    break;

                case 0x5:
                    for (var_a1_2 = 0; var_a1_2 < evs_playcnt; var_a1_2++) {
                        if (var_a1_2 == aipn) {
                            continue;
                        }
                        if ((game_state_data[var_a1_2].unk_025 - game_state_data[aipn].unk_29B) >=
                            temp_s2->unk_1C[var_s0]) {
                            var_t1_5 = 1;
                            break;
                        }
                    }
                    break;

                case 0x6:
                    for (var_a1_2 = 0; var_a1_2 < evs_playcnt; var_a1_2++) {
                        if (var_a1_2 == aipn) {
                            continue;
                        }
                        if (game_state_data[var_a1_2].unk_294 < 5U) {
                            var_t1_5 = 1;
                            break;
                        }
                    }
                    break;

                case 0x7:
                    var_t1_5 = gameStateDataRef->unk_23C == 0;
                    break;

                case 0x8:
                    var_t1_5 = gameStateDataRef->unk_23C == 1;
                    break;

                case 0x9:
                    var_t1_5 = gameStateDataRef->unk_23C == 2;
                    break;

                case 0xA:
                    var_t1_5 = gameStateDataRef->unk_29B <= temp_s2->unk_1C[var_s0];
                    break;

                case 0xB:
                    var_t1_5 = gameStateDataRef->unk_190.unk_3F != 0;
                    break;

                case 0x1:
                    var_t1_5 = 1;
                    break;

                case 0xC:
                    var_t1_5 = dm_get_first_virus_count(evs_gamemode, gameStateDataRef) >= temp_s2->unk_1C[var_s0];
                    break;
            }

            if (var_t1_5 != 0) {
                gameStateDataRef->unk_242[var_s0] = temp_s2->unk_3C[var_s0];
                gameStateDataRef->unk_252[var_s0] = temp_s2->unk_4C[var_s0];
                gameStateDataRef->unk_272[var_s0] = 0;
            }
        }
    }

    for (var_s0 = 0; var_s0 < 0x10; var_s0++) {
        switch (gameStateDataRef->unk_242[var_s0]) {
            case 0x1:
                gameStateDataRef->unk_239 |= 2;
                break;

            case 0x3:
                gameStateDataRef->unk_292 |= 4;
                break;

            case 0x4:
                aiSelSpeed = MAX(aiSelSpeed, 5);
                break;

            case 0x5:
                aiSelSpeed = MIN(aiSelSpeed, 1);
                break;

            case 0x6:
                aiSelSpeed = 6;
                break;

            case 0x7:
                aiSelSpeed = (gameStateDataRef->unk_272[var_s0] / 5) + 1;
                aiSelSpeed = MIN(aiSelSpeed, 6);
                break;

            case 0x8:
                aiSelCom = MIN(aiSelCom + 1, 3);
                break;

            case 0x9:
                aiSelCom = MAX(aiSelCom - 1, 0);
                break;

            case 0xA:
                if (gameStateDataRef->unk_252[var_s0] != 0) {
                    gameStateDataRef->unk_242[(gameStateDataRef->unk_252[var_s0] - 1) % 0x10] = 0;
                } else {
                    for (var_a1_2 = 0; var_a1_2 < 0x10; var_a1_2++) {
                        gameStateDataRef->unk_242[var_a1_2] = 0;
                    }
                }
                break;
        }
    }

    if (aiSelSpeed == 6) {
        gameStateDataRef->unk_239 &= ~0x2;
        for (var_s0 = 0; var_s0 < 0x10; var_s0++) {
            if (gameStateDataRef->unk_242[var_s0] == 2) {
                gameStateDataRef->unk_242[var_s0] = 0;
            }
        }
    }

    temp_t1 = &temp[aiSelCom][var_s5];

    pri_point[4] = temp_t1->unk_00;
    pri_point[1] = temp_t1->unk_02;
    EraseLinP[1] = temp_t1->unk_04;
    EraseLinP[2] = (temp_t1->unk_04 + temp_t1->unk_06) >> 1;

    for (var_s0 = 3; var_s0 < 9; var_s0++) {
        EraseLinP[var_s0] = temp_t1->unk_06;
    }
    HeiEraseLinRate = temp_t1->unk_08 * 0.01f;
    WidEraseLinRate = temp_t1->unk_0A * 0.01f;

    LPriP = temp_t1->unk_0C;

    AloneCapP[2] = temp_t1->unk_0E;
    AloneCapP[3] = temp_t1->unk_10;
    AloneCapP[4] = temp_t1->unk_12;
    AloneCapP[5] = temp_t1->unk_14;

    AloneCapWP[1] = temp_t1->unk_16;
    AloneCapWP[2] = temp_t1->unk_18;
    AloneCapWP[3] = temp_t1->unk_1A;
    AloneCapWP[4] = temp_t1->unk_1C;
    AloneCapWP[5] = temp_t1->unk_1E;

    OnVirusP = temp_t1->unk_20;
    RensaP = temp_t1->unk_22;
    RensaMP = temp_t1->unk_24;

    pri_point[7] = temp_t1->unk_26;
    pri_point[8] = temp_t1->unk_28;

    aiWall = (temp_t1->unk_2A != 0) ? var_s6 : 0;
    OnVirusP_org = OnVirusP;

    HeiLinesAllp[2] = temp_t1->unk_2C;
    HeiLinesAllp[3] = temp_t1->unk_2E;
    HeiLinesAllp[4] = temp_t1->unk_30;
    HeiLinesAllp[5] = temp_t1->unk_30;
    HeiLinesAllp[6] = temp_t1->unk_30;
    HeiLinesAllp[7] = temp_t1->unk_30;
    HeiLinesAllp[8] = temp_t1->unk_30;

    WidLinesAllp[2] = temp_t1->unk_32;
    WidLinesAllp[3] = temp_t1->unk_34;
    WidLinesAllp[4] = temp_t1->unk_36;
    WidLinesAllp[5] = temp_t1->unk_36;
    WidLinesAllp[6] = temp_t1->unk_36;
    WidLinesAllp[7] = temp_t1->unk_36;
    WidLinesAllp[8] = temp_t1->unk_36;

    if (temp_s2->unk_00 != 0) {
        for (var_s0 = 0; var_s0 < evs_playcnt; var_s0++) {
            if (var_s0 == aipn) {
                continue;
            }

            if (game_state_data[var_s0].unk_050[0].unk_0 == 0) {
                continue;
            }

            for (var_a1_2 = 2; var_a1_2 < 8; var_a1_2++) {
                if (EraseLinP[var_a1_2] > 0) {
                    EraseLinP[var_a1_2] = -EraseLinP[var_a1_2];
                }
            }
            var_s0 = evs_playcnt;
        }
    }
}
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

extern u8 aiTEdgeCnt;
extern u8 aiYEdgeCnt;

#if VERSION_US || VERSION_CN
/**
 * Original name: aifPlaceSearch
 */
void aifPlaceSearch(void) {
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

            sp8[var_t5][0] = 0;
            sp8[var_t5][1] = column;
            sp8[var_t5][2] = row;

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

void aifTRecur(u8 arg0, u8 arg1, u8 arg2);
void aifYRecur(u8 arg0, u8 arg1, u8 arg2);

#if VERSION_US || VERSION_CN
/**
 * Original name: aifMoveCheck
 */
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

#if VERSION_US || VERSION_CN
/**
 * Original name: aifTRecur
 */
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

#if VERSION_US || VERSION_CN
/**
 * Original name: aifTRecurUP
 */
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

#if VERSION_US || VERSION_CN
/**
 * Original name: aifYRecur
 */
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

#if VERSION_US || VERSION_CN
/**
 * Original name: aifYRecurUP
 */
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

#if VERSION_US || VERSION_CN
/**
 * Original name: aifReMoveCheck
 */
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

#if VERSION_US || VERSION_CN
/**
 * Original name: aifKeyMake
 */
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
    s32 var_t0;
    s32 temp;
    s32 i;
    s32 j;
    s32 k;

    for (i = 0; i < pGameState->unk_164; i++) {
        if (pGameState->unk_0D4.unk_00[i].unk_8 != arg2) {
            continue;
        }

        temp_t6 = pGameState->unk_0D4.unk_00[i].unk_0;
        temp_t8 = pGameState->unk_0D4.unk_00[i].unk_4;

        if (arg1 == temp_t8) {
            temp = 0;
            for (j = 0; j < 8; j++) {
                sp8[j] = -1;
            }

            for (j = -3; j < 4; j++) {
                if ((temp_t6 + j >= 0) && (temp_t6 + j < GAME_MAP_COLUMNS)) {
                    if (aiFieldData[temp_t8][temp_t6 + j].unk_0 != arg2) {
                        if (aiFieldData[temp_t8][temp_t6 + j].unk_0 == 3) {
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

            for (j = 0; j < 7; j++) {
                sp10[j] = sp8[j];
            }

            for (j = 0; j < 7; j++) {
                if (sp8[j] != 0) {
                    continue;
                }

                sp8[j] = 1;
                var_t0 = 0;

                for (k = 0; k < 7; k++) {
                    if (sp8[k] != 1) {
                        var_t0 = 0;
                    } else {
                        var_t0 += 1;
                    }

                    if ((var_t0 >= 4) && (arg0 == temp_t6 + tbl_2973[j])) {
                        return 0x1388;
                    }
                }

                sp8[j] = 0;
            }
        }

        if (arg0 == temp_t6) {
            temp = 0;

            for (j = 0; j < 8; j++) {
                sp8[j] = -1;
            }

            for (j = -3; j < 4; j++) {
                if ((temp_t8 + j >= 0) && (temp_t8 + j < GAME_MAP_ROWS)) {
                    if (aiFieldData[temp_t8 + j][temp_t6].unk_0 != arg2) {
                        if (aiFieldData[temp_t8 + j][temp_t6].unk_0 == 3) {
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

            for (j = 0; j < 7; j++) {
                sp10[j] = sp8[j];
            }

            for (j = 0; j < 7; j++) {
                if (sp8[j] != 0) {
                    continue;
                }

                sp8[j] = 1;
                var_t0 = 0;

                for (k = 0; k < 7; k++) {
                    if (sp8[k] != 1) {
                        var_t0 = 0;
                    } else {
                        var_t0 += 1;
                    }

                    if (var_t0 < 4) {
                        continue;
                    }
                    if (arg1 == (temp_t8 + tbl_2973[j])) {
                        return 0x1388;
                    }
                }

                sp8[j] = 0;
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

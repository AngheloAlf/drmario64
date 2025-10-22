/**
 * Original filename: main1x.c
 */

#include "main1x.h"

#include "gcc/stdlib.h"

#include "macros_defines.h"

#include "aiset.h"
#include "dm_game_main.h"
#include "main_story.h"
#include "record.h"
#include "vr_init.h"

/**
 * Original name: Original name: evs_playmax
 */
u8 evs_playmax;

/**
 * Original name: evs_gamesel
 */
enum_evs_gamesel evs_gamesel;

/**
 * Original name: evs_default_name
 */
s32 evs_default_name[8];

/**
 * Original name: evs_cfg_4p
 */
struct_evs_cfg_4p evs_cfg_4p;

/**
 * Original name: evs_select_name_no
 */
u8 evs_select_name_no[2];

/**
 * Original name: evs_game_time
 */
u32 evs_game_time;

/**
 * Original name: evs_stereo
 */
u8 evs_stereo = 1;

/**
 * Original name: evs_seqence
 */
u8 evs_seqence = 1;

/**
 * Original name: evs_seqnumb
 */
u8 evs_seqnumb = 0;

/**
 * Original name: evs_playcnt
 */
u8 evs_playcnt = 1;

/**
 * Original name: evs_keyrept
 */
u8 evs_keyrept[2] = { 0xC, 6 };

/**
 * Original name: evs_gamespeed
 */
u8 evs_gamespeed = 1;

/**
 * Original name: evs_score_flag
 */
u8 evs_score_flag = 1;

/**
 * Original name: evs_story_flg
 */
s8 evs_story_flg = 0;

/**
 * Original name: evs_story_nos
 */
s8 evs_story_no = 0;

/**
 * Original name: evs_story_level
 */
s8 evs_story_level = 1;

/**
 * Original name: evs_secret_flg
 */
u8 evs_secret_flg[2] = { 0, 0 };

/**
 * Original name: evs_one_game_flg
 */
u8 evs_one_game_flg = 0;

/**
 * Original name: evs_level_21
 */
u8 evs_level_21 = 0;

/**
 * Original name: evs_manual_no
 */
s8 evs_manual_no = EVS_MANUAL_NO_0;

/**
 * Original name: evs_high_score
 */
u32 evs_high_score = 0;

/**
 * Original name: evs_vs_count
 */
s32 evs_vs_count = 3;

/**
 * Original name: FlyingCnt
 */
u8 FlyingCnt[3] = { 0x28, 0x14, 0x14 };

/**
 * Original name: BonusWait
 */
u8 BonusWait[][3] = {
    { 2, 2, 3 },
    { 1, 1, 1 },
    { 1, 0, 1 },
};

u8 D_8008842C[] = { 0x01, 0x02, 0x02, 0x02 };

/**
 * Original name: GameSpeed
 */
s8 GameSpeed[] = { 0, 0xA, 0xF, 0x37 };

/**
 * Original name: FallSpeed
 */
u8 FallSpeed[0x38] = {
    0x27, 0x25, 0x23, 0x21, 0x1F, 0x1D, 0x1B, 0x19, 0x17, 0x15, 0x13, 0x12, 0x11, 0x10, 0xF, 0xE, 0xD, 0xC, 0xB,
    0xA,  9,    9,    8,    8,    7,    7,    6,    6,    5,    5,    5,    5,    5,    5,   5,   5,   5,   5,
    5,    5,    4,    4,    4,    4,    4,    3,    3,    3,    3,    3,    2,    2,    2,   2,   2,   1,
};

/**
 * Original name: Score1p
 */
u8 Score1p[3][6] = {
    { 1, 2, 4, 8, 0x10, 0x20 },
    { 2, 4, 8, 0x10, 0x20, 0x40 },
    { 3, 6, 0xC, 0x18, 0x30, 0x60 },
};

/**
 * Original name: main11
 */
enum_main_no main11(void) {
    enum_main_no ret = MAIN_TITLE;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(game_state_data); i++) {
        game_state_data[i].unk_026 = 0xA;
        game_state_data[i].unk_02C = 1;
        game_state_data[i].unk_090 = i;
        game_state_data[i].unk_04B = i;
        game_state_data[i].unk_04C = 0;
        game_state_data[i].unk_04D = i;
        game_state_data[i].unk_04E = 1;
        game_state_data[i].unk_16C = 1;
    }

    evs_select_name_no[0] = evs_select_name_no[1] = 8;

    switch (EepRom_Init()) {
        case EepRomErr_NotInit:
            EepRom_InitFirst(NULL, NULL);
            break;

        case EepRomErr_BadSum:
            ret = MAIN_CSUM_ERROR;
            break;

        default:
            break;
    }

    return ret;
}

/**
 * Original name: adjust_story_ai
 */
void adjust_story_ai(void) {
    s32 i;

    for (i = 0; i < evs_playcnt; i++) {
        struct_game_state_data *temp_a3 = &game_state_data[i];
        struct_ai_char_data *temp_a1 = &ai_char_data[i + 12];

        if (temp_a3->unk_04C != 1) {
            continue;
        }

        *temp_a1 = ai_char_data[temp_a3->unk_04D];

        temp_a3->unk_04D = i + 12;

        switch (evs_story_level) {
            case 0x0:
                switch (temp_a3->unk_090) {
                    case CHARANIMEMODE_M:
                    case CHARANIMEMODE_N:
                        if (evs_story_no == 1) {
                            *temp_a1 = ai_char_data[1];
                            temp_a1->speed = 1;
                        }
                        break;

                    case CHARANIMEMODE_K:
                        temp_a1->speed = 1;
                        temp_a1->unk_3C[0] = 0;
                        temp_a1->unk_3C[2] = 0;
                        break;

                    case CHARANIMEMODE_L:
                    case CHARANIMEMODE_O:
                        temp_a1->speed = 2;
                        temp_a1->unk_3C[0] = 0;
                        break;

                    case CHARANIMEMODE_C:
                        temp_a1->speed = 2;
                        break;

                    default:
                        break;
                }
                break;

            case 0x1:
                switch (temp_a3->unk_090) {
                    case CHARANIMEMODE_M:
                    case CHARANIMEMODE_N:
                        if (evs_story_no == 1) {
                            *temp_a1 = ai_char_data[1];
                            temp_a1->speed = 1;
                        } else {
                            temp_a1->speed = 1;
                            temp_a1->unk_3C[1] = 0;
                        }
                        break;

                    case CHARANIMEMODE_G:
                        temp_a1->speed = 1;
                        temp_a1->unk_3C[0] = 0;
                        temp_a1->unk_3C[1] = 0;
                        break;

                    case CHARANIMEMODE_K:
                        temp_a1->speed = 2;
                        temp_a1->unk_3C[0] = 0;
                        temp_a1->unk_3C[2] = 0;
                        break;

                    case CHARANIMEMODE_L:
                    case CHARANIMEMODE_O:
                        temp_a1->speed = 2;
                        temp_a1->unk_3C[0] = 0;
                        break;

                    case CHARANIMEMODE_A:
                        temp_a1->speed = 2;
                        break;

                    case CHARANIMEMODE_D:
                        temp_a1->speed = 1;
                        break;

                    case CHARANIMEMODE_F:
                        temp_a1->speed = 1;
                        break;

                    case CHARANIMEMODE_C:
                        temp_a1->speed = 1;
                        break;

                    case CHARANIMEMODE_E:
                        temp_a1->unk_3C[0] = 0;
                        break;

                    default:
                        break;
                }
                break;

            case 0x2:
                switch (temp_a3->unk_090) {
                    case CHARANIMEMODE_M:
                    case CHARANIMEMODE_N:
                        if (evs_story_no == 1) {
                            *temp_a1 = ai_char_data[1];
                            temp_a1->speed = 1;
                        } else {
                            temp_a1->speed = 2;
                            temp_a1->unk_3C[1] = 0;
                        }
                        break;

                    case CHARANIMEMODE_I:
                        temp_a1->speed = 2;
                        temp_a1->unk_3C[1] = 0;
                        break;

                    case CHARANIMEMODE_B:
                        temp_a1->speed = 2;
                        temp_a1->unk_3C[2] = 0;
                        break;

                    case CHARANIMEMODE_F:
                        temp_a1->speed = 3;
                        temp_a1->unk_3C[1] = 0;
                        break;

                    case CHARANIMEMODE_G:
                        temp_a1->speed = 2;
                        temp_a1->unk_3C[0] = 0;
                        temp_a1->unk_3C[1] = 0;
                        break;

                    case CHARANIMEMODE_K:
                        temp_a1->speed = 3;
                        temp_a1->unk_00 = 0;
                        temp_a1->unk_0C[2] = 2;
                        temp_a1->unk_1C[2] = 0xF;
                        temp_a1->unk_3C[2] = 2;
                        break;

                    case CHARANIMEMODE_H:
                    case CHARANIMEMODE_J:
                    case CHARANIMEMODE_L:
                    case CHARANIMEMODE_O:
                        temp_a1->speed = 3;
                        temp_a1->unk_3C[0] = 0;
                        break;

                    case CHARANIMEMODE_C:
                        temp_a1->speed = 2;
                        break;

                    case CHARANIMEMODE_A:
                        temp_a1->speed = 5;
                        break;

                    default:
                        break;
                }
                break;

            case 0x3:
                switch (temp_a3->unk_090) {
                    case CHARANIMEMODE_M:
                    case CHARANIMEMODE_N:
                        if (evs_story_no == 1) {
                            *temp_a1 = ai_char_data[1];
                            temp_a1->unk_3C[1] = 0;
                        }
                        temp_a1->speed = 1;
                        break;

                    case CHARANIMEMODE_I:
                        temp_a1->speed = 2;
                        temp_a1->unk_3C[1] = 0;
                        break;

                    case CHARANIMEMODE_B:
                        temp_a1->speed = 2;
                        break;

                    case CHARANIMEMODE_A:
                        temp_a1->speed = 5;
                        break;

                    case CHARANIMEMODE_D:
                        temp_a1->speed = 4;
                        break;

                    case CHARANIMEMODE_H:
                        temp_a1->speed = 3;
                        break;

                    case CHARANIMEMODE_J:
                        temp_a1->speed = 3;
                        break;

                    case CHARANIMEMODE_E:
                        temp_a1->speed = 3;
                        break;
                    case CHARANIMEMODE_F:
                        temp_a1->speed = 3;
                        break;

                    case CHARANIMEMODE_K:
                        temp_a1->speed = 5;
                        temp_a1->unk_3C[1] = 0;
                        break;

                    case CHARANIMEMODE_L:
                    case CHARANIMEMODE_O:
                        temp_a1->speed = 5;
                        temp_a1->unk_3C[0] = 6;
                        break;

                    default:
                        break;
                }
                break;

            default:
                break;
        }
    }
}

const u8 _seqTbl_224[] = {
    0x03, 0x02, 0x03, 0x02, 0x03, 0x02, 0x03, 0x02, 0x04, 0x02,
};

const u8 _demoSeqTbl_225[] = {
    0,
    1,
};

const u8 StoryVirLv_226[][10] = {
    { 0x00, 0x02, 0x03, 0x03, 0x04, 0x04, 0x05, 0x05, 0x06, 0x06 },
    { 0x00, 0x05, 0x06, 0x06, 0x07, 0x07, 0x08, 0x08, 0x09, 0x09 },
    { 0x00, 0x0B, 0x0C, 0x0C, 0x0D, 0x0D, 0x0E, 0x0E, 0x0F, 0x0F },
};

const u8 _charToAi_227[] = {
    0x00, // CHARANIMEMODE_M
    0x00, // CHARANIMEMODE_N
    0x03, // CHARANIMEMODE_H
    0x01, // CHARANIMEMODE_I
    0x03, // CHARANIMEMODE_J
    0x06, // CHARANIMEMODE_D
    0x07, // CHARANIMEMODE_E
    0x04, // CHARANIMEMODE_F
    0x05, // CHARANIMEMODE_A
    0x02, // CHARANIMEMODE_B
    0x08, // CHARANIMEMODE_C
    0x09, // CHARANIMEMODE_G
    0x0A, // CHARANIMEMODE_K
    0x0B, // CHARANIMEMODE_L
    0x0B, // CHARANIMEMODE_O
};

const s8 _stageToChar_tbl_228[][10] = {
    { CHARANIMEMODE_M, CHARANIMEMODE_N, CHARANIMEMODE_I, CHARANIMEMODE_B, CHARANIMEMODE_H, CHARANIMEMODE_F,
      CHARANIMEMODE_D, CHARANIMEMODE_C, CHARANIMEMODE_K, CHARANIMEMODE_L },

    { CHARANIMEMODE_M, CHARANIMEMODE_M, CHARANIMEMODE_I, CHARANIMEMODE_B, CHARANIMEMODE_J, CHARANIMEMODE_A,
      CHARANIMEMODE_E, CHARANIMEMODE_C, CHARANIMEMODE_K, CHARANIMEMODE_O },
};

const s8 _story4PChar_tbl_229[][4] = {
    { CHARANIMEMODE_M, CHARANIMEMODE_N, CHARANIMEMODE_G, CHARANIMEMODE_C },

    { CHARANIMEMODE_N, CHARANIMEMODE_M, CHARANIMEMODE_G, CHARANIMEMODE_C },
};

const u8 _team_flg_230[][4] = {
    { 0x00, 0x01, 0x02, 0x03 },
    { 0x00, 0x01, 0x02, 0x03 },
    { 0x00, 0x01, 0x02, 0x03 },
};

const u8 GameSize_231[ENUM_EVS_GAMESEL_MAX] = {
    0x01, // ENUM_EVS_GAMESEL_0
    0x02, // ENUM_EVS_GAMESEL_1
    0x04, // ENUM_EVS_GAMESEL_2
    0x02, // ENUM_EVS_GAMESEL_3
    0x01, // ENUM_EVS_GAMESEL_4
    0x02, // ENUM_EVS_GAMESEL_5
    0x04, // ENUM_EVS_GAMESEL_6
};

/**
 * Original name: main12
 */
enum_main_no main12(void) {
    struct_game_state_data *var_a2;
    enum_main_no ret;
    s32 i;
    s32 var_a1_3;
    s32 j;

    evs_playcnt = GameSize_231[evs_gamesel];

    switch (evs_gamesel) {
        case ENUM_EVS_GAMESEL_0:
            game_state_data[0].unk_04C = 0;
            evs_story_flg = 0;
            ret = MAIN_GAME;
            break;

        case ENUM_EVS_GAMESEL_1:
            ret = MAIN_GAME;
            evs_story_flg = 0;
            for (i = 0; i < 2; i++) {
                game_state_data[i].unk_04C = 0;
            }
            break;

        case ENUM_EVS_GAMESEL_2:
            for (i = 0; i < 4; i++) {
                game_state_data[i].unk_04D = _charToAi_227[game_state_data[i].unk_090];
            }
            ret = MAIN_GAME;
            break;

        case ENUM_EVS_GAMESEL_3:
            if (evs_story_flg != 0) {
                s32 temp_s2 = ((s32)story_proc_no >= 0xC);

                for (i = 0; i < 4; i++) {
                    var_a2 = &game_state_data[i];
                    j = MIN(ARRAY_COUNT(StoryVirLv_226) - 1, evs_story_level);

                    var_a2->unk_026 = StoryVirLv_226[j][evs_story_no];
                    var_a2->unk_02C = 1;
                    var_a2->unk_090 = _stageToChar_tbl_228[temp_s2][evs_story_no];
                    var_a2->unk_04C = 1;
                    var_a2->unk_04E = j;
                    var_a2->unk_04D = _charToAi_227[var_a2->unk_090];
                    var_a2->unk_04F = _team_flg_230[j][i];
                    var_a2->unk_16C = j;
                }

                if ((evs_story_level > 0) && (evs_story_no == 7)) {
                    evs_gamesel = ENUM_EVS_GAMESEL_2;
                    evs_playcnt = 4;

                    for (i = 0; i < 4; i++) {
                        var_a2 = &game_state_data[i];

                        var_a2->unk_090 = _story4PChar_tbl_229[temp_s2][i];
                        var_a2->unk_04D = _charToAi_227[var_a2->unk_090];
                        if (evs_story_level < 3) {
                            var_a2->unk_04E = 0;
                        }
                    }

                    game_state_data[0].unk_04C = 0;
                } else {
                    evs_playcnt = 2;
                    game_state_data[0].unk_090 = temp_s2;
                    game_state_data[0].unk_04C = 0;
                }

                adjust_story_ai();
                evs_seqence = 1;
                evs_seqnumb = _seqTbl_224[evs_story_no];
            } else {
                game_state_data[0].unk_04C = 0;
                game_state_data[1].unk_04C = 1;
                game_state_data[1].unk_04D = _charToAi_227[game_state_data[1].unk_090];
            }

            ret = MAIN_GAME;
            break;

        case ENUM_EVS_GAMESEL_4:
            evs_playcnt = 1;
            evs_game_time = 0;
            evs_one_game_flg = 0;
            game_state_data[0].unk_000 = 0;
            game_state_data[0].unk_04B = 0;
            game_state_data[0].unk_04C = 1;
            game_state_data[0].unk_04E = 1;
            game_state_data[0].unk_026 = 0xA;
            game_state_data[0].unk_02C = 1;
            game_state_data[0].unk_090 = CHARANIMEMODE_M;
            evs_seqence = 1;
            game_state_data[0].unk_04D = _charToAi_227[0];
            evs_seqnumb = _demoSeqTbl_225[rand() & 2];
            ret = MAIN_GAME;
            break;

        case ENUM_EVS_GAMESEL_5:
            evs_playcnt = 2;
            evs_story_flg = 0;
            evs_one_game_flg = 0;

            for (i = 0; i < 2; i++) {
                evs_select_name_no[i] = 8;

                do {
                    game_state_data[i].unk_090 = genrand(0xD);
                    var_a1_3 = 0;

                    for (j = 0; j < 2; j++) {
                        if ((i != j) && (game_state_data[i].unk_090 == game_state_data[j].unk_090)) {
                            var_a1_3++;
                        }
                    }

                } while (var_a1_3 != 0);

                game_state_data[i].unk_000 = CHARANIMEMODE_M;
                game_state_data[i].unk_04B = i;
                game_state_data[i].unk_04C = 1;
                game_state_data[i].unk_04D = _charToAi_227[game_state_data[i].unk_090];
                game_state_data[i].unk_04E = 1;
                game_state_data[i].unk_026 = 0xA;
                game_state_data[i].unk_02C = 1;
            }

            evs_seqence = 1;
            evs_seqnumb = _demoSeqTbl_225[rand() & 2];
            ret = MAIN_GAME;
            break;

        case ENUM_EVS_GAMESEL_6:
            evs_playcnt = 4;
            evs_story_flg = 0;
            evs_one_game_flg = 0;

            for (i = 0; i < 4; i++) {
                do {
                    game_state_data[i].unk_090 = genrand(0xD);
                    var_a1_3 = 0;

                    for (j = 0; j < 4; j++) {
                        if ((i != j) && (game_state_data[i].unk_090 == game_state_data[j].unk_090)) {
                            var_a1_3++;
                        }
                    }
                } while (var_a1_3 != 0);

                game_state_data[i].unk_000 = CHARANIMEMODE_M;
                game_state_data[i].unk_04B = i;
                game_state_data[i].unk_04C = 1;
                game_state_data[i].unk_04D = _charToAi_227[game_state_data[i].unk_090];
                game_state_data[i].unk_04E = 1;
                game_state_data[i].unk_04F = i;
                game_state_data[i].unk_026 = 0xA;
                game_state_data[i].unk_02C = 1;
            }

            evs_seqence = 1;
            evs_seqnumb = _demoSeqTbl_225[rand() & 2];
            ret = MAIN_GAME;
            break;

        default:
            UNREACHABLE;
            break;
    }

    return ret;
}

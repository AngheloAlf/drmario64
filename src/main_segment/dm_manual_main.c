/**
 * Original filename: dm_manual_main.c
 */

#include "dm_manual_main.h"
#include "libultra.h"
#include "include_asm.h"
#include "macros_defines.h"
#include "unknown_structs.h"
#include "main_segment_variables.h"
#include "boot_functions.h"
#include "boot_variables.h"
#include "audio/sound.h"
#include "graphic.h"
#include "msgwnd.h"
#include "joy.h"
#include "main1x.h"
#include "tex_func.h"
#include "main_story.h"
#include "nnsched.h"
#include "static.h"
#include "dm_virus_init.h"
#include "util.h"

#if VERSION_US || VERSION_GW || CC_CHECK
#include "aiset.h"
#endif

#if VERSION_US || VERSION_CN
void func_80071EF0(struct_800F4890_unk_034 *arg0, s32 arg1, s32 arg2) {
    arg0->unk_00 = arg1;
    arg0->unk_04 = arg2;
    arg0->messageWnd.unk_28 = arg1 + 8;
    arg0->messageWnd.unk_2C = arg2 + 8;
}
#endif

#if VERSION_US || VERSION_CN
void func_80071F0C(void) {
}
#endif

#if VERSION_US || VERSION_CN

#if VERSION_US
#define FUNC_80071F14_UNK_48 0xD
#endif
#if VERSION_CN
#define FUNC_80071F14_UNK_48 0xE
#endif

void func_80071F14(struct_800F4890_unk_034 *arg0, UNK_PTR *arg1) {
    arg0->unk_08 = 0;
    arg0->unk_0C = -0.0625f;
    msgWnd_init(&arg0->messageWnd, arg1, 0xD, 4, 0x20, 0x20);
    arg0->messageWnd.unk_30 = 0xA;
    arg0->messageWnd.unk_34 = 0xC;
    arg0->messageWnd.unk_3C = 5;
    arg0->messageWnd.unk_48 = FUNC_80071F14_UNK_48;
    arg0->messageWnd.unk_54 = 1.0f / 6.0f;
    func_80071EF0(arg0, 0x20, 0x20);
}
#endif

#if VERSION_US || VERSION_CN
void func_80071FA0(struct_800F4890_unk_034 *arg0) {
    arg0->unk_08 = CLAMP(arg0->unk_08 + arg0->unk_0C, 0.0f, 1.0f);

    if (arg0->unk_08 == 1.0) {
        msgWnd_update(&arg0->messageWnd);
    }
}
#endif

#if VERSION_US || VERSION_CN
void tutolWnd_draw(struct_800F4890_unk_034 *arg0, Gfx **gfxP) {
    Gfx *gfx = *gfxP;
    s32 alpha = arg0->unk_08 * 255;
    TiTexData *temp_a1;

    if (alpha == 0) {
        return;
    }

    gSPDisplayList(gfx++, normal_texture_init_dl);
    gDPSetCombineMode(gfx++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);

    if (alpha < 0xFF) {
        gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    }

    gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, alpha);

    temp_a1 = &_texAll[8];
    tiStretchTexBlock(&gfx, temp_a1, 0, arg0->unk_00, arg0->unk_04, temp_a1->unk_4[0], temp_a1->unk_4[1]);

    if (arg0->unk_08 != 0.0f) {
        arg0->messageWnd.unk_74 = alpha;
        msgWnd_draw(&arg0->messageWnd, &gfx);
    }

    *gfxP = gfx;
}
#endif

#if VERSION_US || VERSION_CN
void func_800721A0(struct_800F4890_unk_034 *arg0) {
    msgWnd_clear(&arg0->messageWnd);
}
#endif

#if VERSION_US || VERSION_CN
void func_800721BC(struct_800F4890_unk_034 *arg0, const char *arg1) {
    msgWnd_addStr(&arg0->messageWnd, arg1);
}
#endif

#if VERSION_US || VERSION_CN
void func_800721D8(struct_800F4890_unk_034 *arg0) {
    if (arg0->unk_0C < 0.0f) {
        arg0->unk_0C = -arg0->unk_0C;
    }
}
#endif

#if VERSION_US || VERSION_CN
void func_80072204(struct_800F4890_unk_034 *arg0) {
    if (arg0->unk_0C > 0.0f) {
        arg0->unk_0C = -arg0->unk_0C;
    }
}
#endif

#if VERSION_US || VERSION_CN
bool func_80072230(struct_800F4890_unk_034 *arg0) {
    return msgWnd_isEnd(&arg0->messageWnd);
}
#endif

#if VERSION_US || VERSION_CN
bool func_8007224C(struct_800F4890_unk_034 *arg0) {
    return msgWnd_isSpeaking(&arg0->messageWnd);
}
#endif

#if VERSION_US || VERSION_CN
void func_80072268(struct_800F4890_unk_0E8 *arg0, s32 arg1, s32 arg2) {
    arg0->unk_0 = arg1;
    arg0->unk_1 = 1;
    arg0->unk_2 = arg2;
    arg0->unk_3[0] = 1;
}
#endif

#if VERSION_US || VERSION_CN
const s32 RO_800B2408[] = { 0xC8, 0x28 };
#endif

#if VERSION_US || VERSION_CN
const s32 RO_800B2410[] = { 0x6C, 0x28 };
#endif

#if VERSION_US || VERSION_CN
const s32 RO_800B2418[] = { 0x24, 0x28 };
#endif

#if VERSION_US || VERSION_CN
const s32 RO_800B2420[] = { 0xB4, 0x28 };
#endif

#if VERSION_US || VERSION_CN
const s32 RO_800B2428[] = { 0xD8, 0x70 };
#endif

#if VERSION_US || VERSION_CN
const s32 RO_800B2430[] = { 0x7C, 0x70 };
#endif

#if VERSION_US || VERSION_CN
const s32 RO_800B2438[] = { 0x34, 0x70 };
#endif

#if VERSION_US || VERSION_CN
const s32 RO_800B2440[] = { 0xC4, 0x70 };
#endif

#if VERSION_US || VERSION_CN
const u8 virus_1_1[][3] = {
    { 1, 1, 0x10 }, { 2, 2, 0xD }, { 2, 2, 0xE }, { 0, 5, 0xF }, { 0, 1, 6 }, { 0, 5, 6 },
    { 2, 0, 6 },    { 2, 4, 6 },   { 1, 2, 6 },   { 1, 3, 6 },   { 1, 6, 6 }, { 1, 7, 6 },
};
#endif

#if VERSION_US || VERSION_CN
const u8 RO_800B246C[] = { 0x12, 0x20, 0, 0x10, 0x21 };
#endif

#if VERSION_US || VERSION_CN
const u8 RO_800B2474[] = { 0x21, 0x10, 0x20, 0, 0x21 };
#endif

#if VERSION_US || VERSION_CN
const u8 position_1_1[][4] = {
    { 3, 5, 1, 0 },
    { 3, 3, 0, 0 },
    { 3, 2, 0, 0 },
    { 3, 1, 0, 0 },
};
#endif

#if VERSION_US || VERSION_CN
const u8 virus_2_1[][3] = {
    { 0, 0, 0xE }, { 0, 2, 0xA }, { 0, 2, 0xB }, { 0, 5, 8 },    { 0, 5, 9 },    { 0, 6, 0xC }, { 0, 6, 0xE },
    { 2, 3, 0xE }, { 2, 4, 7 },   { 2, 4, 8 },   { 2, 5, 0xB },  { 2, 5, 0xC },  { 2, 5, 0xE }, { 2, 5, 0xF },
    { 1, 1, 7 },   { 1, 1, 0xA }, { 1, 1, 0xB }, { 1, 1, 0x10 }, { 1, 2, 0x10 }, { 1, 7, 0xF },
};
#endif

#if VERSION_US || VERSION_CN
const u8 capsel_2_1[] = {
    0x21, 0x02, 0x10, 0x12, 0x21, 0x00, 0x01, 0x20, 0x21, 0x12, 0x10, 0x10,
};
#endif

#if VERSION_US || VERSION_CN
const u8 position_2_1[][4] = {
    { 4, 6, 0, 0 },   { 4, 5, 0, 1 }, { 7, 0xE, 1, 0 }, { 6, 0xB, 0, 1 }, { 5, 0xD, 0, 0 },
    { 0, 0xD, 1, 0 }, { 0, 9, 0, 0 }, { 3, 0xD, 1, 0 }, { 2, 9, 0, 1 },   { 1, 8, 0, 0 },
};
#endif

#if VERSION_US || VERSION_CN
const u8 virus_3_1[][3] = {
    { 0, 0, 0xC }, { 0, 1, 0xD }, { 0, 1, 0xF }, { 0, 4, 0xF }, { 0, 6, 0xD },  { 0, 6, 8 },    { 0, 7, 0x10 },
    { 2, 3, 8 },   { 2, 3, 9 },   { 2, 3, 0xB }, { 2, 3, 0xC }, { 2, 7, 0xE },  { 2, 7, 0xF },  { 1, 1, 0x10 },
    { 1, 2, 8 },   { 1, 2, 0xC }, { 1, 4, 0xD }, { 1, 4, 0xE }, { 1, 4, 0x10 }, { 1, 5, 0x10 },
};
#endif

#if VERSION_US || VERSION_CN
const u8 capsel_3_1[] = {
    0x12, 0x22, 0x12, 0, 0x10, 2, 0x21, 0, 0x12, 1, 0,
};
#endif

#if VERSION_US || VERSION_CN
const u8 position_3_1[][4] = {
    { 4, 0xC, 0, 0 }, { 3, 0xA, 0, 0 }, { 1, 0xB, 0, 1 }, { 1, 0xA, 1, 0 },  { 2, 0xA, 1, 0 },
    { 6, 0xC, 0, 0 }, { 6, 0xB, 0, 1 }, { 6, 0xA, 1, 0 }, { 2, 0x10, 1, 1 }, { 3, 0x10, 1, 0 },
};
#endif

#if VERSION_US || VERSION_CN
const u8 virus_4_1[][3] = {
    { 0, 0, 0xD }, { 0, 2, 7 },   { 0, 5, 0xA }, { 0, 5, 0xB }, { 0, 7, 0x10 }, { 2, 2, 0xE },
    { 2, 2, 0xF }, { 2, 3, 0xA }, { 2, 3, 0xD }, { 2, 5, 8 },   { 1, 1, 0xD },  { 1, 4, 8 },
    { 1, 4, 9 },   { 1, 5, 0xE }, { 1, 5, 0xF }, { 1, 6, 0xA },
};
#endif

#if VERSION_US || VERSION_CN
const u8 capsel_4_1[] = {
    0x10, 0x11, 0x20, 1, 0x12, 0x20, 1, 0x10, 0, 0x20, 0, 0x21, 1, 0x20, 0x22, 0, 0x10,
};
#endif

#if VERSION_US || VERSION_CN
const u8 position_4_1[][4] = {
    { 4, 7, 1, 0 },   { 5, 7, 0, 1 },   { 5, 6, 1, 0 },   { 5, 8, 0, 0 },   { 5, 7, 0, 1 },   { 3, 0xC, 1, 0 },
    { 0, 0xC, 0, 0 }, { 1, 0xB, 1, 0 }, { 0, 0xB, 1, 0 }, { 2, 0xD, 1, 0 }, { 7, 0xF, 1, 0 }, { 6, 0xD, 0, 0 },
    { 2, 6, 0, 0 },   { 3, 5, 1, 0 },   { 3, 3, 0, 0 },   { 2, 5, 1, 0 },
};
#endif

#include "build/src/main_segment/dm_manual_main.msg.inc"

#if VERSION_US || VERSION_CN
void dm_manual_attack_capsel_down(void) {
    struct_watchManual *watchManualP = watchManual;
    s32 i;
    bool playSound = false;

    for (i = 0; i < 4; i++) {
        watchManualP->unk_174[i]++;
        if (watchManualP->unk_174[i] >= 0xE) {
            s32 j;

            watchManualP->unk_174[i] = 0;

            for (j = 0; j < 4; j++) {
                if (watchManualP->unk_0E8[i][j].unk_3[0] == 0) {
                    continue;
                }

                if (get_map_info(game_map_data[i], watchManualP->unk_0E8[i][j].unk_0,
                                 watchManualP->unk_0E8[i][j].unk_1 + 1)) {
                    set_map(game_map_data[i], watchManualP->unk_0E8[i][j].unk_0, watchManualP->unk_0E8[i][j].unk_1, 4,
                            watchManualP->unk_0E8[i][j].unk_2);
                    watchManualP->unk_0E8[i][j].unk_3[0] = 0;
                } else {
                    playSound = true;

                    if (watchManualP->unk_0E8[i][j].unk_1 < 0x10) {
                        watchManualP->unk_0E8[i][j].unk_1++;
                    }

                    if (watchManualP->unk_0E8[i][j].unk_1 == 0x10) {
                        set_map(game_map_data[i], watchManualP->unk_0E8[i][j].unk_0, 0x10, 4,
                                watchManualP->unk_0E8[i][j].unk_2);
                        watchManualP->unk_0E8[i][j].unk_3[0] = 0;
                    }
                }
            }
        }
    }

    if (playSound) {
        dm_snd_play(SND_INDEX_55);
    }
}
#endif

#if VERSION_US || VERSION_CN
void func_800723EC(struct_game_state_data *gameStateDataP, GameMapCell *mapCells, s32 arg2 UNUSED) {
    if ((gameStateDataP->unk_014 != 1) && (gameStateDataP->unk_014 != 0xD)) {
        dm_black_up(gameStateDataP, mapCells);
    }
}
#endif

#if VERSION_US || VERSION_CN
void dm_manual_update_virus_anime(struct_game_state_data *arg0) {
    s32 i;

    for (i = 0; i < 3; i++) {
        animeState_update(get_virus_anime_state(i));
        animeSmog_update(get_virus_smog_state(i));
    }

    dm_calc_big_virus_pos(arg0);
}
#endif

#if VERSION_US || VERSION_CN
s32 dm_manual_main_cnt(struct_game_state_data *gameStateData, GameMapCell *mapCells, u8 arg2, s32 arg3 UNUSED) {
    struct_watchManual *temp_s3 = watchManual;
    s32 i;
    s32 var_s0_3;

    switch (gameStateData->unk_00C) {
        case 0x1:
        case 0x2:
            return 3;

        case 0x4:
            dm_capsel_down(gameStateData, mapCells);
            break;

        case 0x5:
            if (dm_check_game_over(gameStateData, mapCells)) {
                gameStateData->unk_014 = 4;
                gameStateData->unk_00C = 0xB;
                return -1;
            }

            if (dm_h_erase_chack(mapCells) || dm_w_erase_chack(mapCells)) {
                if (gameStateData->unk_049 == 0) {
                    gameStateData->unk_00C = 6;
                } else {
                    gameStateData->unk_00C = 0x15;
                }
                gameStateData->unk_02F = 0;
            } else if (gameStateData->unk_049 == 0) {
                gameStateData->unk_00C = 9;
            } else {
                gameStateData->unk_00C = 0x16;
            }
            break;

        case 0x6:
            gameStateData->unk_02F++;
            if (gameStateData->unk_02F >= 0x12U) {
                gameStateData->unk_02F = 0;
                gameStateData->unk_00C = 7;
                dm_h_erase_chack_set(gameStateData, mapCells);
                dm_w_erase_chack_set(gameStateData, mapCells);
                dm_h_ball_chack(mapCells);
                dm_w_ball_chack(mapCells);
                gameStateData->unk_025 =
                    get_virus_color_count(mapCells, &temp_s3->unk_148[0], &temp_s3->unk_148[1], &temp_s3->unk_148[2]);

                switch (evs_manual_no) {
                    case EVS_MANUAL_NO_0:
                    case EVS_MANUAL_NO_3:
                        for (i = 0; i < ARRAY_COUNT(temp_s3->unk_14C); i++) {
                            if (temp_s3->unk_148[i] == 0) {
                                if (temp_s3->unk_14C[i].unk_0 == 0) {
                                    temp_s3->unk_14C[i].unk_0 = 1;
                                    animeState_set(get_virus_anime_state(i), 4);
                                    animeSmog_start(get_virus_smog_state(i));
                                    if (gameStateData->unk_025 != 0) {
                                        dm_snd_play(SND_INDEX_74);
                                    }
                                }
                            } else if (gameStateData->unk_03C[3] & (0x10 << i)) {
                                animeState_set(get_virus_anime_state(i), 2);
                                dm_snd_play(SND_INDEX_74);
                            }
                        }
                        break;

                    default:
                        break;
                }

                gameStateData->unk_03C[3] &= 0xF;

                if (gameStateData->unk_025 == 0) {
                    dm_make_score(gameStateData);
                    gameStateData->unk_014 = 3;
                    gameStateData->unk_00C = 0xA;
                    return 6;
                }
                if (((gameStateData->unk_025 != 0) && (gameStateData->unk_025 < 4U)) && (temp_s3->unk_170 == 0)) {
                    temp_s3->unk_170 = 1;
                    dm_snd_play(SND_INDEX_80);
                    dm_seq_play_in_game((evs_seqnumb * 2) | 1);
                }

                gameStateData->unk_039++;
                if (gameStateData->unk_03C[3] & 8) {
                    gameStateData->unk_03C[3] &= ~8;
                    dm_snd_play(SND_INDEX_56);
                } else {
                    dm_snd_play(SND_INDEX_61);
                }
            }
            break;

        case 0x7:
            dm_capsel_erase_anime(gameStateData, mapCells);
            break;

        case 0x8:
            go_down(gameStateData, mapCells, 0xE);
            break;

        case 0x9:
            dm_attack_se(gameStateData, arg2);
            dm_warning_h_line(gameStateData, mapCells);
            aifMakeFlagSet(gameStateData);
            dm_set_capsel(gameStateData);
            dm_capsel_speed_up(gameStateData);
            gameStateData->unk_03A = 0;
            gameStateData->unk_039 = 0;
            gameStateData->unk_037 = 0;

            for (i = 0; i < ARRAY_COUNT(gameStateData->unk_03C); i++) {
                gameStateData->unk_03C[i] = 0;
            }

            gameStateData->unk_00C = 4;
            break;

        case 0xA:
            temp_s3->unk_02C++;
            if (temp_s3->unk_02C > 120) {
                temp_s3->unk_02C = 0;
                return 1;
            }
            break;

        case 0xB:
        case 0xD:
        case 0xF:
        case 0x11:
            temp_s3->unk_02C++;
            if (temp_s3->unk_02C > 120) {
                temp_s3->unk_02C = 0;
                return 0x64;
            }
            break;

        case 0x15:
            gameStateData->unk_02F++;
            if (gameStateData->unk_02F >= 0x12U) {
                gameStateData->unk_02F = 0;
                gameStateData->unk_00C = 7;
                dm_h_erase_chack_set(gameStateData, mapCells);
                dm_w_erase_chack_set(gameStateData, mapCells);
                dm_h_ball_chack(mapCells);
                dm_w_ball_chack(mapCells);

                gameStateData->unk_039 += 1;
                if (gameStateData->unk_03C[3] & 8) {
                    gameStateData->unk_03C[3] &= ~8;
                } else {
                    dm_snd_play(SND_INDEX_61);
                }
            }
            break;

        case 0x16:
            dm_attack_se(gameStateData, arg2);
            dm_warning_h_line(gameStateData, mapCells);

            var_s0_3 = true;
            // reading i non initialized
            if ((game_state_data[i].unk_04A != 0) && dm_broken_set(gameStateData, mapCells)) {
                gameStateData->unk_00C = 8;
                var_s0_3 = false;
            }
            if (var_s0_3) {
                dm_set_capsel(gameStateData);
                dm_capsel_speed_up(gameStateData);
                gameStateData->unk_03A = 0;
                gameStateData->unk_039 = 0;
                gameStateData->unk_037 = 0;

                for (i = 0; i < ARRAY_COUNT(gameStateData->unk_03C); i++) {
                    gameStateData->unk_03C[i] = 0;
                }

                gameStateData->unk_00C = 4;
            }
            break;

        default:
            break;
    }

    return 0;
}
#endif

#if VERSION_US || VERSION_CN
void dm_manual_make_key(struct_game_state_data *gameStateData, GameMapCell *mapCells) {
    struct_watchManual *temp_s2 = watchManual;
    struct_game_state_data_unk_178 *temp_s4 = &gameStateData->unk_178;
    u16 key;

    aifKeyOut(gameStateData);

    key = joygam[gameStateData->unk_04B];

    if (key & B_BUTTON) {
        rotate_capsel(mapCells, temp_s4, -1);
        temp_s2->unk_01C[3] = 8;
    } else if (key & CONT_A) {
        rotate_capsel(mapCells, temp_s4, 1);
        temp_s2->unk_01C[2] = 8;
    }

    if (key & L_JPAD) {
        translate_capsel(mapCells, gameStateData, -1, main_joy[gameStateData->unk_04B]);
        temp_s2->unk_01C[0] = 8;
    } else if (key & R_JPAD) {
        translate_capsel(mapCells, gameStateData, 1, main_joy[gameStateData->unk_04B]);
        temp_s2->unk_01C[1] = 8;
    }

    gameStateData->unk_030 = 1;
    if ((key & D_JPAD) && (temp_s4->unk_2[0] > 0)) {
        s32 temp_v1;

        temp_v1 = FallSpeed[gameStateData->unk_02D];
        temp_v1 = (temp_v1 >> 1) + (temp_v1 & 1);
        gameStateData->unk_030 = temp_v1;
    }
}
#endif

#if VERSION_US || VERSION_CN
bool dm_manual_1_main(void) {
    struct_watchManual *temp_s2 = watchManual;
    bool var_s6 = true;
    GameMapCell *mapCells = game_map_data[0];
    struct_game_state_data *gameStateDataP = game_state_data;
    struct_game_state_data_unk_178 *unk_178 = &gameStateDataP->unk_178;
    s32 var_s5;
    s32 var_s1;

    for (var_s1 = 0; var_s1 < ARRAY_COUNTU(temp_s2->unk_01C); var_s1++) {
        if (temp_s2->unk_01C[var_s1] != -0x14) {
            temp_s2->unk_01C[var_s1]--;
        }
    }

    if (temp_s2->unk_16C != 0) {
        var_s5 = dm_manual_main_cnt(gameStateDataP, mapCells, 0, 0);
        dm_manual_make_key(gameStateDataP, mapCells);
    }

    func_800723EC(gameStateDataP, mapCells, 0);

    dm_virus_anime(gameStateDataP, mapCells);
    dm_manual_update_virus_anime(gameStateDataP);
    dm_warning_h_line_se();

    switch (temp_s2->unk_164) {
        case 0x0:
            func_80071EF0(&temp_s2->unk_034, RO_800B2408[0], RO_800B2408[1]);
            temp_s2->unk_000 = 1;
            temp_s2->unk_004 = RO_800B2428[0];
            temp_s2->unk_008 = RO_800B2428[1];

            func_80072204(&temp_s2->unk_034);

            temp_s2->unk_164++;

            for (var_s1 = 0; var_s1 < ARRAY_COUNTU(RO_800B246C); var_s1++) {
                CapsMagazine[var_s1 + 1] = RO_800B246C[var_s1];
            }

            gameStateDataP->unk_032 = 1;
            dm_set_capsel(gameStateDataP);
            break;

        case 0x1:
            set_virus(mapCells, virus_1_1[gameStateDataP->unk_025][1], virus_1_1[gameStateDataP->unk_025][2],
                      virus_1_1[gameStateDataP->unk_025][0],
                      virus_anime_table[virus_1_1[gameStateDataP->unk_025][0]][gameStateDataP->unk_027]);

            gameStateDataP->unk_025++;
            if (gameStateDataP->unk_025 >= 4U) {
                temp_s2->unk_164 = 0xA;
            }
            break;

        case 0xA:
            func_800721D8(&temp_s2->unk_034);
            func_800721BC(&temp_s2->unk_034, mes_1_1);
            temp_s2->unk_164 = 0x30A;
            temp_s2->unk_168 = 0x14;
            break;

        case 0x14:
            func_800721A0(&temp_s2->unk_034);
            func_800721BC(&temp_s2->unk_034, mes_1_2);
            temp_s2->unk_164 = 0x30A;
            temp_s2->unk_168 = 0x1E;
            break;

        case 0x1E:
            func_800721A0(&temp_s2->unk_034);
            func_800721BC(&temp_s2->unk_034, mes_1_3);
            temp_s2->unk_164 = 0x30A;
            temp_s2->unk_168 = 0x28;

            break;

        case 0x28:
            func_800721A0(&temp_s2->unk_034);
            func_800721BC(&temp_s2->unk_034, mes_1_4);
            temp_s2->unk_164 = 0x30A;
            temp_s2->unk_168 = 0x29;
            break;

        case 0x29:
            temp_s2->unk_16C = 1;
            gameStateDataP->unk_00C = 4;
            aifMake2(gameStateDataP, 3, 0xC, 0, 0);
            temp_s2->unk_164++;
            break;

        case 0x2A:
            gameStateDataP->unk_030 = 1;

            switch (unk_178->unk_2[0]) {
                case 0x4:
                    if (unk_178->unk_2[0] == unk_178->unk_2[1]) {
                        rotate_capsel(mapCells, unk_178, -1);
                        temp_s2->unk_01C[3] = 8;
                    }
                    break;

                case 0x6:
                    if (unk_178->unk_2[0] != unk_178->unk_2[1]) {
                        rotate_capsel(mapCells, unk_178, -1);
                        temp_s2->unk_01C[3] = 8;
                    }
                    break;

                case 0x8:
                    if (unk_178->unk_2[0] == unk_178->unk_2[1]) {
                        rotate_capsel(mapCells, unk_178, 1);
                        temp_s2->unk_01C[2] = 8;
                    }
                    break;

                case 0xA:
                    if (unk_178->unk_2[0] != unk_178->unk_2[1]) {
                        rotate_capsel(mapCells, unk_178, 1);
                        temp_s2->unk_01C[2] = 8;
                    }
                    break;

                case 0xC:
                    aifMakeFlagSet(gameStateDataP);
                    aifMake2(gameStateDataP, 4, 0xE, 0, 0);
                    temp_s2->unk_164++;
                    break;
            }
            break;

        case 0x2B:
            if (gameStateDataP->unk_23D == 0) {
                temp_s2->unk_164 = 0x32;
            }
            break;

        case 0x32:
            temp_s2->unk_16C = 0;
            func_800721A0(&temp_s2->unk_034);
            func_800721BC(&temp_s2->unk_034, mes_1_5);
            temp_s2->unk_164 = 0x30A;
            temp_s2->unk_168 = 0x33;
            break;

        case 0x33:
            temp_s2->unk_16C = 1;
            aifMake2(gameStateDataP, 2, 0xC, 1, 0);
            temp_s2->unk_164++;
            break;

        case 0x34:
            if (gameStateDataP->unk_23D == 0) {
                aifMake2(gameStateDataP, 5, 0xD, 1, 0);
                temp_s2->unk_164++;
            }
            break;

        case 0x35:
            if (gameStateDataP->unk_23D == 0) {
                temp_s2->unk_164 = 0x3C;
            }
            break;

        case 0x3C:
            temp_s2->unk_16C = 0;
            func_800721A0(&temp_s2->unk_034);
            func_800721BC(&temp_s2->unk_034, mes_1_6);
            temp_s2->unk_164 = 0x30A;
            temp_s2->unk_168 = 0x3D;
            break;

        case 0x3D:
            temp_s2->unk_16C = 1;
            aifMake2(gameStateDataP, 2, 0x10, 0, 0);
            temp_s2->unk_164++;
            break;

        case 0x3E:
            if (var_s5 == 6) {
                dm_seq_play(SEQ_INDEX_14);
                temp_s2->unk_014 = 0;
                temp_s2->unk_018 = 0x78;
                temp_s2->unk_164++;
            }
            break;

        case 0x3F:
            if (var_s5 == 1) {
                clear_map_all(mapCells);
                temp_s2->unk_164++;

                gameStateDataP->unk_026 = 0xF;
                _dm_virus_init(0, gameStateDataP, virus_map_data[0], virus_map_disp_order, 1);

                for (var_s1 = 0; var_s1 < 3; var_s1++) {
                    animeState_set(get_virus_anime_state(var_s1), 0);
                    animeSmog_stop(get_virus_smog_state(var_s1));
                }

                for (var_s1 = 0; var_s1 < ARRAY_COUNTU(RO_800B2474); var_s1++) {
                    CapsMagazine[var_s1 + 1] = RO_800B2474[var_s1];
                }

                gameStateDataP->unk_032 = 1;
                dm_set_capsel(gameStateDataP);

                gameStateDataP->unk_00C = 1;
                gameStateDataP->unk_014 = 2;
                gameStateDataP->unk_025 = 0;
            }
            break;

        case 0x40:
            var_s1 = virus_map_disp_order->unk_00[gameStateDataP->unk_025];

            set_virus(mapCells, virus_map_data[0][var_s1].unk_1, virus_map_data[0][var_s1].unk_2,
                      virus_map_data[0][var_s1].unk_0,
                      virus_anime_table[virus_map_data[0][var_s1].unk_0][gameStateDataP->unk_027]);

            gameStateDataP->unk_025++;

            if (gameStateDataP->unk_025 >= dm_get_first_virus_count(evs_gamemode, gameStateDataP)) {
                temp_s2->unk_164 = 0x46;
            }
            break;

        case 0x46:
            func_800721A0(&temp_s2->unk_034);
            func_800721BC(&temp_s2->unk_034, mes_1_7);
            temp_s2->unk_164 = 0x30A;
            temp_s2->unk_168 = 0x47;

            break;

        case 0x47:
            temp_s2->unk_16C = 1;
            gameStateDataP->unk_00C = 4;
            aifMakeFlagSet(gameStateDataP);
            temp_s2->unk_164++;
            break;

        case 0x48: /* switch 1 */
            var_s1 = gameStateDataP->unk_032 - 2;
            if (var_s1 < 4U) {
                aifMake2(gameStateDataP, position_1_1[var_s1][0], position_1_1[var_s1][1], position_1_1[var_s1][2],
                         position_1_1[var_s1][3]);
            } else {
                temp_s2->unk_164++;
            }
            break;

        case 0x49:
            if (var_s5 == -1) {
                dm_seq_play(SEQ_INDEX_17);
                temp_s2->unk_164++;
            }
            break;

        case 0x4A:
            if (var_s5 == 0x64) {
                temp_s2->unk_164 = 0x50;
            }
            break;

        case 0x50:
            func_800721A0(&temp_s2->unk_034);
            func_800721BC(&temp_s2->unk_034, mes_1_8);
            temp_s2->unk_164 = 0x30A;
            temp_s2->unk_168 = 0x30C;
            break;

        case 0x30A:
            if (func_80072230(&temp_s2->unk_034)) {
                temp_s2->unk_164 = temp_s2->unk_168;
            }
            break;

        case 0x30C:
            var_s6 = false;
            break;
    }

    return var_s6;
}
#endif

#if VERSION_US || VERSION_CN
bool dm_manual_2_main(void) {
    struct_watchManual *watchManualP = watchManual;
    struct_game_state_data *gameStateDataP = game_state_data;
    GameMapCell *mapCells = game_map_data[0];
    bool ret = true;
    s32 i;

    if (watchManualP->unk_16C != 0) {
        dm_manual_main_cnt(gameStateDataP, game_map_data[0], 0, 1);
        dm_manual_main_cnt(&gameStateDataP[1], game_map_data[1], 1, 1);
        dm_manual_make_key(gameStateDataP, game_map_data[0]);
    }

    func_800723EC(gameStateDataP, game_map_data[0], 0);
    dm_manual_attack_capsel_down();

    for (i = 0; i < 2; i++) {
        dm_virus_anime(&gameStateDataP[i], game_map_data[i]);
    }

    dm_warning_h_line_se();

    switch (watchManualP->unk_164) {
        case 0x0:
            func_80071EF0(&watchManualP->unk_034, RO_800B2410[0], RO_800B2410[1]);
            watchManualP->unk_000 = 1;
            watchManualP->unk_004 = RO_800B2430[0];
            watchManualP->unk_008 = RO_800B2430[1];
            func_80072204(&watchManualP->unk_034);
            watchManualP->unk_164 = 1;

            for (i = 0; i < ARRAY_COUNTU(capsel_2_1); i++) {
                CapsMagazine[i + 1] = capsel_2_1[i];
            }
            gameStateDataP->unk_032 = 1;
            dm_set_capsel(gameStateDataP);
            break;

        case 0x1:
            set_virus(mapCells, virus_2_1[gameStateDataP->unk_025][1], virus_2_1[gameStateDataP->unk_025][2],
                      virus_2_1[gameStateDataP->unk_025][0],
                      virus_anime_table[virus_2_1[gameStateDataP->unk_025][0]][gameStateDataP->unk_027]);

            gameStateDataP->unk_025++;
            if (gameStateDataP->unk_025 >= 0x14U) {
                watchManualP->unk_164 = 0xA;
            }
            break;

        case 0xA:
            func_800721D8(&watchManualP->unk_034);
            func_800721BC(&watchManualP->unk_034, mes_2_1);
            watchManualP->unk_164 = 0x30A;
            watchManualP->unk_168 = 0x14;
            break;

        case 0x14:
            func_800721A0(&watchManualP->unk_034);
            func_800721BC(&watchManualP->unk_034, mes_2_2);
            watchManualP->unk_164 = 0x30A;
            watchManualP->unk_168 = 0x1E;
            break;

        case 0x1E:
            func_800721A0(&watchManualP->unk_034);
            func_800721BC(&watchManualP->unk_034, mes_2_3);
            watchManualP->unk_164 = 0x30A;
            watchManualP->unk_168 = 0x28;
            break;

        case 0x28:
            func_800721A0(&watchManualP->unk_034);
            func_800721BC(&watchManualP->unk_034, mes_2_4);
            watchManualP->unk_164 = 0x30A;
            watchManualP->unk_168 = 0x32;
            break;

        case 0x32:
            func_800721A0(&watchManualP->unk_034);
            func_800721BC(&watchManualP->unk_034, mes_2_5);
            watchManualP->unk_164 = 0x30A;
            watchManualP->unk_168 = 0x3C;
            break;

        case 0x3C:
            func_800721A0(&watchManualP->unk_034);
            func_800721BC(&watchManualP->unk_034, mes_2_6);
            watchManualP->unk_164 = 0x30A;
            watchManualP->unk_168 = 0x3D;
            break;

        case 0x3D:
            gameStateDataP->unk_00C = 4;
            watchManualP->unk_164 = 0x309;
            watchManualP->unk_168 = 0x46;
            break;

        case 0x46:
            func_800721A0(&watchManualP->unk_034);
            func_800721BC(&watchManualP->unk_034, mes_2_7);
            watchManualP->unk_164 = 0x30A;
            watchManualP->unk_168 = 0x47;
            break;

        case 0x47:
            watchManualP->unk_164 = 0x309;
            watchManualP->unk_168 = 0x50;
            break;

        case 0x50:
            watchManualP->unk_164 = 0x309;
            watchManualP->unk_168 = 0x51;
            break;

        case 0x51:
            func_800721A0(&watchManualP->unk_034);
            func_800721BC(&watchManualP->unk_034, mes_2_8);
            watchManualP->unk_164 = 0x30A;
            watchManualP->unk_168 = 0x5A;
            break;

        case 0x5A:
            func_800721A0(&watchManualP->unk_034);
            func_800721BC(&watchManualP->unk_034, mes_2_9);
            watchManualP->unk_164 = 0x30A;
            watchManualP->unk_168 = 0x30C;
            break;

        case 0x309:
            watchManualP->unk_16C = 1;
            i = gameStateDataP->unk_032 - 2;
            if (i < ARRAY_COUNTU(position_2_1)) {
                aifMake2(gameStateDataP, position_2_1[i][0], position_2_1[i][1], position_2_1[i][2],
                         position_2_1[i][3]);
            }

            switch (watchManualP->unk_030) {
                case 0:
                    if (i == 2) {
                        func_80072268(watchManualP->unk_0E8[1], 2, 2);
                        func_80072268(&watchManualP->unk_0E8[1][1], 6, 0);
                        watchManualP->unk_174[1] = 0;
                        watchManualP->unk_164 = 0x30B;
                        watchManualP->unk_030 += 1;
                    }
                    break;

                case 1:
                    if (i == 5) {
                        func_80072268(watchManualP->unk_0E8[1], 2, 2);
                        func_80072268(&watchManualP->unk_0E8[1][1], 4, 0);

                        func_80072268(&watchManualP->unk_0E8[1][2], 6, 1);
                        watchManualP->unk_174[1] = 0;
                        watchManualP->unk_164 = 0x30B;
                        watchManualP->unk_030 += 1;
                    }
                    break;

                case 2:
                    if (i == 0xA) {
                        func_80072268(watchManualP->unk_0E8[1], 1, 0);
                        func_80072268(&watchManualP->unk_0E8[1][1], 3, 1);
                        func_80072268(&watchManualP->unk_0E8[1][2], 5, 0);
                        func_80072268(&watchManualP->unk_0E8[1][3], 7, 2);
                        watchManualP->unk_174[1] = 0;
                        watchManualP->unk_164 = 0x30B;
                        watchManualP->unk_030 += 1;
                    }
                    break;
            }
            break;

        case 0x30A:
            watchManualP->unk_16C = 0;
            if (func_80072230(&watchManualP->unk_034)) {
                watchManualP->unk_164 = watchManualP->unk_168;
            }
            break;

        case 0x30B:
            watchManualP->unk_16C = 0;
            if (watchManualP->unk_0E8[1][1].unk_3[0] == 0) {
                watchManualP->unk_164 = watchManualP->unk_168;
            }
            break;

        case 0x30C:
            ret = false;
            break;

        default:
            break;
    }

    return ret;
}
#endif

#if VERSION_US || VERSION_CN
bool dm_manual_3_main(void) {
    struct_game_state_data *gameStateData = game_state_data;
    GameMapCell *mapCells = game_map_data[0];
    struct_watchManual *temp_s2 = watchManual;
    bool ret = true;
    s32 i;

    if (temp_s2->unk_16C != 0) {
        dm_manual_main_cnt(gameStateData, mapCells, 0, 2);

        for (i = 1; i < 3; i++) {
            dm_manual_main_cnt(&gameStateData[i], game_map_data[i], i, 2);
        }

        dm_manual_make_key(gameStateData, mapCells);
    }

    func_800723EC(gameStateData, mapCells, 0);
    dm_manual_attack_capsel_down();

    for (i = 0; i < 4; i++) {
        dm_virus_anime(&game_state_data[i], game_map_data[i]);
    }

    dm_warning_h_line_se();

    switch (temp_s2->unk_164) {
        case 0x0:
            func_80071EF0(&temp_s2->unk_034, RO_800B2420[0], RO_800B2420[1]);
            temp_s2->unk_000 = 1;
            temp_s2->unk_004 = RO_800B2440[0];
            temp_s2->unk_008 = RO_800B2440[1];
            func_80072204(&temp_s2->unk_034);
            temp_s2->unk_164 = (u32)1;

            for (i = 0; i < ARRAY_COUNTU(capsel_3_1); i++) {
                CapsMagazine[i + 1] = capsel_3_1[i];
            }

            gameStateData->unk_032 = 1;
            dm_set_capsel(gameStateData);
            break;

        case 0x1:
            set_virus(mapCells, virus_3_1[gameStateData->unk_025][1], virus_3_1[gameStateData->unk_025][2],
                      virus_3_1[gameStateData->unk_025][0],
                      virus_anime_table[virus_3_1[gameStateData->unk_025][0]][gameStateData->unk_027]);

            gameStateData->unk_025++;
            if (gameStateData->unk_025 >= 0x14U) {
                temp_s2->unk_164 = 0xA;
            }
            break;

        case 0xA:
            func_800721D8(&temp_s2->unk_034);
            func_800721BC(&temp_s2->unk_034, mes_3_1);
            temp_s2->unk_164 = 0x30A;
            temp_s2->unk_168 = 0x14;
            break;

        case 0x14:
            func_800721A0(&temp_s2->unk_034);
            func_800721BC(&temp_s2->unk_034, mes_3_2);
            temp_s2->unk_164 = 0x30A;
            temp_s2->unk_168 = 0x1E;
            break;

        case 0x1E:
            func_800721A0(&temp_s2->unk_034);
            func_800721BC(&temp_s2->unk_034, mes_3_3);
            temp_s2->unk_164 = 0x30A;
            temp_s2->unk_168 = 0x28;
            break;

        case 0x28:
            func_800721A0(&temp_s2->unk_034);
            func_800721BC(&temp_s2->unk_034, mes_3_4);
            temp_s2->unk_164 = 0x30A;
            temp_s2->unk_168 = 0x32;
            break;

        case 0x32:
            func_800721A0(&temp_s2->unk_034);
            func_800721BC(&temp_s2->unk_034, mes_3_5);
            temp_s2->unk_164 = 0x30A;
            temp_s2->unk_168 = 0x3C;
            break;

        case 0x3C:
            func_800721A0(&temp_s2->unk_034);
            func_800721BC(&temp_s2->unk_034, mes_3_6);
            temp_s2->unk_164 = 0x30A;
            temp_s2->unk_168 = 0x3D;
            break;

        case 0x3D:
            gameStateData->unk_00C = 4;
            temp_s2->unk_164 = 0x309;
            temp_s2->unk_168 = 0x46;
            break;

        case 0x46:
            func_800721A0(&temp_s2->unk_034);
            func_800721BC(&temp_s2->unk_034, mes_3_7);
            temp_s2->unk_164 = 0x30A;
            temp_s2->unk_168 = 0x47;
            break;

        case 0x47:
            temp_s2->unk_164 = 0x309;
            temp_s2->unk_168 = 0x50;
            break;

        case 0x50:
            func_800721A0(&temp_s2->unk_034);
            func_800721BC(&temp_s2->unk_034, mes_3_8);
            temp_s2->unk_164 = 0x30A;
            temp_s2->unk_168 = 0x51;
            break;

        case 0x51:
            temp_s2->unk_164 = 0x309;
            temp_s2->unk_168 = 0x5A;
            break;

        case 0x5A:
            func_800721A0(&temp_s2->unk_034);
            func_800721BC(&temp_s2->unk_034, mes_3_9);
            temp_s2->unk_164 = 0x30A;
            temp_s2->unk_168 = 0x5B;
            break;

        case 0x5B:
            temp_s2->unk_164 = 0x309;
            temp_s2->unk_168 = 0x64;
            break;

        case 0x64:
            func_800721A0(&temp_s2->unk_034);
            func_800721BC(&temp_s2->unk_034, mes_3_10);
            temp_s2->unk_164 = 0x30A;
            temp_s2->unk_168 = 0x6E;
            break;

        case 0x6E:
            func_800721A0(&temp_s2->unk_034);
            func_800721BC(&temp_s2->unk_034, mes_3_11);
            temp_s2->unk_164 = 0x30A;
            temp_s2->unk_168 = 0x78;
            break;

        case 0x78:
            func_800721A0(&temp_s2->unk_034);
            func_800721BC(&temp_s2->unk_034, mes_3_12);
            temp_s2->unk_164 = 0x30A;
            temp_s2->unk_168 = 0x82;
            break;

        case 0x82:
            func_800721A0(&temp_s2->unk_034);
            func_800721BC(&temp_s2->unk_034, mes_3_13);
            temp_s2->unk_164 = 0x30A;
            temp_s2->unk_168 = 0x8C;
            break;

        case 0x8C:
            func_800721A0(&temp_s2->unk_034);
            func_800721BC(&temp_s2->unk_034, mes_3_14);
            temp_s2->unk_164 = 0x30A;
            temp_s2->unk_168 = 0x96;
            break;

        case 0x96:
            func_800721A0(&temp_s2->unk_034);
            func_800721BC(&temp_s2->unk_034, mes_3_15);
            temp_s2->unk_164 = 0x30A;
            temp_s2->unk_168 = 0x30C;
            break;

        case 0x309:
            temp_s2->unk_16C = 1;
            i = gameStateData->unk_032 - 2;
            if (i < ARRAY_COUNTU(position_3_1)) {
                aifMake2(gameStateData, position_3_1[i][0], position_3_1[i][1], position_3_1[i][2], position_3_1[i][3]);
            }

            switch (temp_s2->unk_030) {
                case 0x0:
                    if (i == 2) {
                        func_80072268(temp_s2->unk_0E8[1], 2, 2);
                        func_80072268(&temp_s2->unk_0E8[1][1], 6, 1);
                        temp_s2->unk_174[1] = 0;
                        temp_s2->unk_164 = 0x30B;
                        temp_s2->unk_030 += 1;
                    }
                    break;

                case 0x1:
                    if (i == 5) {
                        func_80072268(temp_s2->unk_0E8[2], 2, 0);
                        func_80072268(&temp_s2->unk_0E8[2][1], 6, 1);
                        temp_s2->unk_174[2] = 0;

                        temp_s2->unk_164 = 0x30B;
                        temp_s2->unk_030 += 1;
                        temp_s2->unk_034.unk_0C = -temp_s2->unk_034.unk_0C;
                    }
                    break;

                case 0x2:
                    if (i == 8) {
                        func_80072268(temp_s2->unk_0E8[3], 2, 0);
                        func_80072268(&temp_s2->unk_0E8[3][1], 6, 2);
                        temp_s2->unk_174[3] = 0;
                        temp_s2->unk_164 = 0x30B;
                        temp_s2->unk_030 += 1;
                        temp_s2->unk_034.unk_0C = -temp_s2->unk_034.unk_0C;
                    }
                    break;

                case 0x3:
                    if (i == 0xA) {
                        func_80072268(temp_s2->unk_0E8[2], 2, 0);
                        func_80072268(&temp_s2->unk_0E8[2][1], 6, 1);
                        temp_s2->unk_174[2] = 0;
                        func_80072268(temp_s2->unk_0E8[3], 2, 0);
                        func_80072268(&temp_s2->unk_0E8[3][1], 6, 1);
                        temp_s2->unk_174[3] = 0;
                        temp_s2->unk_164 = 0x30B;
                        temp_s2->unk_030 += 1;
                        temp_s2->unk_034.unk_0C = -temp_s2->unk_034.unk_0C;
                    }
                    break;

                default:
                    break;
            }
            break;

        case 0x30A:
            temp_s2->unk_16C = 0;
            if (func_80072230(&temp_s2->unk_034)) {
                temp_s2->unk_164 = temp_s2->unk_168;
            }
            break;

        case 0x30B:
            temp_s2->unk_16C = 0;
            if ((temp_s2->unk_0E8[1][1].unk_3[0] == 0) && (temp_s2->unk_0E8[2][1].unk_3[0] == 0) &&
                (temp_s2->unk_0E8[3][1].unk_3[0] == 0)) {
                if (temp_s2->unk_000 < 0) {
                    if (temp_s2->unk_034.unk_0C > 0.0f) {
                        temp_s2->unk_034.unk_0C = -temp_s2->unk_034.unk_0C;
                    } else if (temp_s2->unk_034.unk_08 == 0.0f) {
                        func_80071EF0(&temp_s2->unk_034, RO_800B2420[0], RO_800B2420[1]);
                        temp_s2->unk_034.unk_0C = -temp_s2->unk_034.unk_0C;
                        temp_s2->unk_000 = -temp_s2->unk_000;
                        temp_s2->unk_004 = RO_800B2440[0];
                        temp_s2->unk_008 = RO_800B2440[1];
                    }
                } else {
                    temp_s2->unk_164 = temp_s2->unk_168;
                }
            } else {
                if ((temp_s2->unk_034.unk_0C < 0.0f) && (temp_s2->unk_034.unk_08 == 0.0f)) {
                    func_80071EF0(&temp_s2->unk_034, RO_800B2418[0], RO_800B2418[1]);
                    temp_s2->unk_034.unk_0C = -temp_s2->unk_034.unk_0C;
                    temp_s2->unk_000 = -temp_s2->unk_000;
                    temp_s2->unk_004 = RO_800B2438[0];
                    temp_s2->unk_008 = RO_800B2438[1];
                }
            }
            break;

        case 0x30C:
            ret = false;
            break;

        default:
            break;
    }

    return ret;
}
#endif

#if VERSION_US || VERSION_CN
bool dm_manual_4_main(void) {
    struct_watchManual *temp_s2 = watchManual;
    bool ret = true;
    struct_game_state_data *gameStateData = game_state_data;
    GameMapCell *mapCells = game_map_data[0];
    bool var_v0_2;
    s32 i;

    for (i = 0; i < ARRAY_COUNTU(temp_s2->unk_01C); i++) {
        if (temp_s2->unk_01C[i] != -0x14) {
            temp_s2->unk_01C[i]--;
        }
    }

    if (temp_s2->unk_16C != 0) {
        dm_manual_main_cnt(gameStateData, mapCells, 0, 0);
        dm_manual_make_key(gameStateData, mapCells);
    }
    func_800723EC(gameStateData, mapCells, 0);
    dm_virus_anime(gameStateData, mapCells);
    dm_manual_update_virus_anime(gameStateData);
    dm_warning_h_line_se();

    switch (temp_s2->unk_164) {
        case 0x0:
            func_80071EF0(&temp_s2->unk_034, RO_800B2408[0], RO_800B2408[1]);
            temp_s2->unk_000 = 1;
            temp_s2->unk_004 = RO_800B2428[0];
            temp_s2->unk_008 = RO_800B2428[1];
            func_80072204(&temp_s2->unk_034);
            temp_s2->unk_164 = 1;

            for (i = 0; i < ARRAY_COUNTU(capsel_4_1); i++) {
                CapsMagazine[i + 1] = capsel_4_1[i];
            }

            gameStateData->unk_032 = 1;
            dm_set_capsel(gameStateData);
            break;

        case 0x1:
            set_virus(mapCells, virus_4_1[gameStateData->unk_025][1], virus_4_1[gameStateData->unk_025][2],
                      virus_4_1[gameStateData->unk_025][0],
                      virus_anime_table[virus_4_1[gameStateData->unk_025][0]][gameStateData->unk_027]);
            gameStateData->unk_025++;
            if (gameStateData->unk_025 >= 0x10U) {
                temp_s2->unk_164 = 0xA;
            }
            break;

        case 0xA:
            func_800721D8(&temp_s2->unk_034);
            func_800721BC(&temp_s2->unk_034, mes_4_1);
            temp_s2->unk_164 = 0x30A;
            temp_s2->unk_168 = 0x14;
            break;

        case 0x14:
            func_800721A0(&temp_s2->unk_034);
            func_800721BC(&temp_s2->unk_034, mes_4_2);
            temp_s2->unk_164 = 0x30A;
            temp_s2->unk_168 = 0x15;
            break;

        case 0x15:
            gameStateData->unk_00C = 4;
            temp_s2->unk_164 = 0x309;
            temp_s2->unk_168 = 0x1E;
            break;

        case 0x1E:
            func_800721A0(&temp_s2->unk_034);
            func_800721BC(&temp_s2->unk_034, mes_4_3);
            temp_s2->unk_164 = 0x30A;
            temp_s2->unk_168 = 0x28;
            break;

        case 0x28:
            func_800721A0(&temp_s2->unk_034);
            func_800721BC(&temp_s2->unk_034, mes_4_4);
            temp_s2->unk_164 = 0x30A;
            temp_s2->unk_168 = 0x29;
            break;

        case 0x29:
            temp_s2->unk_164 = 0x309;
            temp_s2->unk_168 = 0x32;
            break;

        case 0x32:
            func_800721A0(&temp_s2->unk_034);
            func_800721BC(&temp_s2->unk_034, mes_4_5);
            temp_s2->unk_164 = 0x30A;
            temp_s2->unk_168 = 0x33;
            break;

        case 0x33:
            temp_s2->unk_164 = 0x309;
            temp_s2->unk_168 = 0x3C;
            break;

        case 0x3C:
            func_800721A0(&temp_s2->unk_034);
            func_800721BC(&temp_s2->unk_034, mes_4_6);
            temp_s2->unk_164 = 0x30A;
            temp_s2->unk_168 = 0x3D;
            break;

        case 0x3D:
            temp_s2->unk_164 = 0x309;
            temp_s2->unk_168 = 0x46;
            break;

        case 0x46:
            func_800721A0(&temp_s2->unk_034);
            func_800721BC(&temp_s2->unk_034, mes_4_7);
            temp_s2->unk_164 = 0x30A;
            temp_s2->unk_168 = 0x47;
            break;

        case 0x47:
            temp_s2->unk_164 = 0x309;
            temp_s2->unk_168 = 0x50;
            break;

        case 0x50:
            func_800721A0(&temp_s2->unk_034);
            func_800721BC(&temp_s2->unk_034, mes_4_8);
            temp_s2->unk_164 = 0x30A;
            temp_s2->unk_168 = 0x51;
            break;

        case 0x51:
            temp_s2->unk_164 = 0x309;
            temp_s2->unk_168 = 0x5A;
            break;

        case 0x5A:
            func_800721A0(&temp_s2->unk_034);
            func_800721BC(&temp_s2->unk_034, mes_4_9);
            temp_s2->unk_164 = 0x30A;
            temp_s2->unk_168 = 0x64;
            break;

        case 0x64:
            func_800721A0(&temp_s2->unk_034);
            func_800721BC(&temp_s2->unk_034, mes_4_10);
            temp_s2->unk_164 = 0x30A;
            temp_s2->unk_168 = 0x30C;
            break;

        case 0x309:
            temp_s2->unk_16C = 1;
            i = gameStateData->unk_032 - 2;
            if (i < ARRAY_COUNTU(position_4_1)) {
                aifMake2(gameStateData, position_4_1[i][0], position_4_1[i][1], position_4_1[i][2], position_4_1[i][3]);
            }

            switch (temp_s2->unk_030) {
                case 0x0:
                    var_v0_2 = i == 3;
                    break;
                case 0x1:
                    var_v0_2 = i == 5;
                    break;
                case 0x2:
                    var_v0_2 = i == 0xA;
                    break;
                case 0x3:
                    var_v0_2 = i == 0xC;
                    break;
                case 0x4:
                    var_v0_2 = i == 0xF;
                    break;
                case 0x5:
                    var_v0_2 = i == 0x10;
                    break;
                default:
                    var_v0_2 = false;
                    break;
            }

            if (var_v0_2) {
                temp_s2->unk_164 = temp_s2->unk_168;
                temp_s2->unk_030++;
            }
            break;

        case 0x30A:
            temp_s2->unk_16C = 0;
            if (func_80072230(&temp_s2->unk_034)) {
                temp_s2->unk_164 = temp_s2->unk_168;
            }
            break;

        case 0x30C:
            ret = false;
            break;

        default:
            break;
    }

    return ret;
}
#endif

#if VERSION_US || VERSION_CN
ASM_RODATA;

const s32 _tex_884[][2] = {
    { 0, 2 },
    { 1, 3 },
};

const s32 _pos_885[][2] = {
    { 0, 0 },
    { 0, 0xC },
};
#endif

#if VERSION_US || VERSION_CN
void draw_AB_guide(s32 arg0, s32 arg1) {
    s32 i;

    gSPDisplayList(gGfxHead++, alpha_texture_init_dl);
    gDPSetCombineLERP(gGfxHead++, TEXEL0, 0, PRIMITIVE, 0, TEXEL1, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0,
                      COMBINED);
    gDPSetPrimColor(gGfxHead++, 0, 0, 255, 255, 255, 255);

    for (i = 0; i < 2U; i++) {
        TiTexData *temp_a3 = &_texAll[_tex_884[i][0]];
        TiTexData *temp_a0 = &_texAll[_tex_884[i][1]];
        s32 var_t0;

        var_t0 = MIN(temp_a3->unk_4[0], temp_a0->unk_4[0]);

        StretchAlphaTexTile(&gGfxHead, var_t0, temp_a3->unk_4[1], temp_a3->unk_0->tex, temp_a3->unk_4[0],
                            temp_a0->unk_0->tex, temp_a0->unk_4[0], 0, 0, var_t0, temp_a3->unk_4[1],
                            arg0 + _pos_885[i][0], arg1 + _pos_885[i][1], var_t0, temp_a3->unk_4[1]);
    }
}
#endif

#if VERSION_US || VERSION_CN
const s32 RO_800B3150[] = {
    0, 1, 2, 3, 2, 1,
};

// unused
void func_80074B08(Gfx **gfxP, Mtx **mtxP, Vtx **vtxP, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    struct_watchManual *temp_s0 = watchManual;
    Gfx *gfx = *gfxP;
    Mtx *mtx = *mtxP;
    Vtx *vtx = *vtxP;
    f32 sp48[4][4];
    TiTexData *temp_s4;
    TiTexData *temp_s1;
    s32 var_s1;
    s32 var_s0;
    s32 var_s3;
    f32 temp;

    guOrtho(mtx, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 1.0f, 10.0f, 1.0f);
    gSPMatrix(gfx++, mtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    mtx++;

    guTranslate(mtx, 0.0f, 0.0f, -5.0f);
    gSPMatrix(gfx++, mtx, G_MTX_NOPUSH | G_MTX_MUL | G_MTX_PROJECTION);
    mtx++;

    temp = WrapF(0.0f, 1.0f, temp_s0->unk_184 * (1 / 128.0)) * M_PI * 2.0;
    guRotateRPYF(sp48, 0.0f, (1 - arg5) * 0x5A,
                 sinf(temp) * 4.0f * arg5);

    var_s1 = WrapI(0, ARRAY_COUNT(RO_800B3150), ((temp_s0->unk_184 & 0x7F) * 3) >> 2);
    if (func_8007224C(&temp_s0->unk_034) == false) {
        var_s1 = 0;
    }

    temp_s4 = &_texKaSa[RO_800B3150[var_s1] + 1];
    temp_s1 = &_texKaSa[0];

    var_s0 = MIN(temp_s4->unk_4[0], temp_s1->unk_4[0]);
    var_s3 = MIN(temp_s4->unk_4[1], temp_s1->unk_4[1]);

    gSPDisplayList(gfx++, alpha_texture_init_dl);
    gSPClearGeometryMode(gfx++, G_ZBUFFER | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN |
                                    G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH | G_CLIPPING);
    gDPSetCombineLERP(gfx++, TEXEL0, 0, PRIMITIVE, 0, TEXEL1, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED);
    gDPSetTexturePersp(gfx++, G_TP_NONE);
    gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, arg6);

    if (arg5 <= 0) {
        sp48[3][0] = arg3 + var_s0;
    } else {
        sp48[3][0] = arg3;
    }
    sp48[3][1] = arg4;

    guMtxF2L(sp48, mtx);
    gSPMatrix(gfx++, mtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    mtx++;

    RectAlphaTexTile(&gfx, &vtx, var_s0, var_s3, temp_s4->unk_0->tex, temp_s4->unk_4[0], temp_s1->unk_0->tex,
                     temp_s1->unk_4[0], 0, 0, var_s0, var_s3, 0.0f, 0.0f, var_s0, var_s3);

    *vtxP = vtx;
    *mtxP = mtx;
    *gfxP = gfx;
}
#endif

#if VERSION_US || VERSION_CN
const s32 _posContPanel[] = { 0x0000000A, 0x0000000E };
#endif

#if VERSION_US || VERSION_CN
ASM_TEXT;

void func_80074EF0(struct_game_state_data *gameStateData, struct_800F4890_unk_0E8 *arg1, s32 arg2) {
    s32 i;

    for (i = 0; i < 3; i++) {
        s32 j;

        load_TexPal(dm_game_get_capsel_pal(arg2, i)->unk_0->tlut);

        for (j = 0; j < 4; j++) {
            if ((arg1[j].unk_3[0] != 0) && (arg1[j].unk_2 == i)) {
                draw_Tex(gameStateData->unk_006 + (arg1[j].unk_0 * gameStateData->unk_00A),
                         gameStateData->unk_008 + (arg1[j].unk_1 * gameStateData->unk_00A), gameStateData->unk_00A,
                         gameStateData->unk_00A, 0, gameStateData->unk_00A * 4);
            }
        }
    }
}
#endif

#if VERSION_US || VERSION_CN
/**
 * Original name: _posCircle_924
 */
const s32 _posCircle_924[STRUCT_WATCHGAME_MANUAL_UNK_LEN2][2] = {
#if VERSION_US
    { 0xD, 0x14 },
    { 0x1C, 0x15 },
    { 0x46, 0x20 },
    { 0x3E, 0x1A },
#else
    { 0x16, 0x2E },
    { 0x1F, 0x2A },
    { 0x34, 0x1B },
    { 0x2B, 0x19 },
#endif
};

/**
 * Original name: _posFinger_925
 */
const s32 _posFinger_925[STRUCT_WATCHGAME_MANUAL_UNK_LEN2][2] = {
#if VERSION_US
    { 0xD, 6 },
    { 0x1C, 7 },
    { 0x46, 0x12 },
    { 0x3E, 0xC },
#else
    { 0x16, 0x20 },
    { 0x1F, 0x1C },
    { 0x34, 0xD },
    { 0x2B, 0xB },
#endif
};

/**
 * Original name: disp_cont
 */
void disp_cont(void) {
    struct_watchManual *watchManualP = watchManual;
    s32 i;

    for (i = 0; i < ARRAY_COUNTU(watchManualP->unk_01C); i++) {
        TiTexData *temp_t1;
        TiTexData *temp_a1;
        const s32 *temp_t2;
        s32 var_t0;

        if (watchManualP->unk_01C[i] == -0x14) {
            continue;
        }

        gSPDisplayList(gGfxHead++, normal_texture_init_dl);

        gDPSetCombineLERP(gGfxHead++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, PRIMITIVE, TEXEL0, 0,
                          PRIMITIVE, 0);
        gDPSetRenderMode(gGfxHead++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
        gDPSetPrimColor(gGfxHead++, 0, 0, 255, 0, 0, 255);
        gDPSetTextureLUT(gGfxHead++, G_TT_NONE);

        temp_t2 = _posCircle_924[i];
        temp_t1 = &_texAll[6];
        StretchTexBlock4i(&gGfxHead, temp_t1->unk_4[0], temp_t1->unk_4[1], temp_t1->unk_0->tex,
                          _posContPanel[0] + temp_t2[0], _posContPanel[1] + temp_t2[1], temp_t1->unk_4[0],
                          temp_t1->unk_4[1]);

        gSPDisplayList(gGfxHead++, alpha_texture_init_dl);

        temp_t1 = &_texAll[4];
        temp_a1 = &_texAll[5];

        temp_t2 = _posFinger_925[i];
        var_t0 = MIN(temp_t1->unk_4[0], temp_a1->unk_4[0]);

        StretchAlphaTexBlock(&gGfxHead, var_t0, temp_t1->unk_4[1], temp_t1->unk_0->tex, temp_t1->unk_4[0],
                             temp_a1->unk_0->tex, temp_a1->unk_4[0], _posContPanel[0] + temp_t2[0],
                             _posContPanel[1] + temp_t2[1] - MIN(4, ABS(watchManualP->unk_01C[i])), var_t0,
                             temp_t1->unk_4[1]);
    }
}
#endif

#if VERSION_US || VERSION_CN
void dm_manual_draw_fg(Mtx **mtxP, Vtx **vtxP) {
    struct_watchManual *temp_s4 = watchManual;
    s32 i;
    TiTexData *temp;

    switch (evs_manual_no) {
        case EVS_MANUAL_NO_0:
        case EVS_MANUAL_NO_3:
            gSPDisplayList(gGfxHead++, normal_texture_init_dl);

            temp = &_texAll[7];
            tiStretchTexBlock(&gGfxHead, temp, 0, _posContPanel[0], _posContPanel[1], temp->unk_4[0], temp->unk_4[1]);
            dm_draw_big_virus(&gGfxHead);
            break;

        default:
            break;
    }

    switch (evs_manual_no) {
        case EVS_MANUAL_NO_1:
            dm_calc_bottle_2p();
            dm_draw_bottle_2p(&gGfxHead);

            for (i = 0; i < 2; i++) {
                dm_game_graphic_p(&game_state_data[i], i, game_map_data[i]);
                func_80074EF0(&game_state_data[i], temp_s4->unk_0E8[i], 0);
            }
            break;

        case EVS_MANUAL_NO_2:
            for (i = 0; i < 4; i++) {
                dm_game_graphic_p(&game_state_data[i], i, game_map_data[i]);
                func_80074EF0(&game_state_data[i], temp_s4->unk_0E8[i], 1);
            }
            break;

        case EVS_MANUAL_NO_0:
        case EVS_MANUAL_NO_3:
            dm_game_graphic_p(game_state_data, 0, game_map_data[0]);
            disp_cont();
            break;
    }

    dm_draw_KaSaMaRu(&gGfxHead, mtxP, vtxP, func_8007224C(&temp_s4->unk_034), temp_s4->unk_004, temp_s4->unk_008,
                     temp_s4->unk_000, (s32)(temp_s4->unk_034.unk_08 * 255));
    switch (evs_manual_no) {
        case EVS_MANUAL_NO_0:
        case EVS_MANUAL_NO_3:
            if (main_old == MAIN_NO_3) {
                push_any_key_draw(0xDC, 0xD2);
            } else {
                draw_AB_guide(0xC8, 0xCA);
            }
            break;

        case EVS_MANUAL_NO_1:
            if (main_old == MAIN_NO_3) {
                push_any_key_draw(0x80, 0xD2);
            } else {
                draw_AB_guide(0x6E, 0xCA);
            }
            break;

        case EVS_MANUAL_NO_2:
            if (main_old == MAIN_NO_3) {
                push_any_key_draw(0xE6, 0xD2);
            } else {
                draw_AB_guide(0x6E, 0xCA);
            }
            break;
    }

    tutolWnd_draw(&temp_s4->unk_034, &gGfxHead);
}
#endif

#if VERSION_US || VERSION_CN
const u16 map_x_table_1036[][4] = {
    { 0x76, 0x76, 0x76, 0x76 },
    { 0x1C, 0xD4, 0x1C, 0xD4 },
    { 0x14, 0x5C, 0xA4, 0xEC },
};
const u8 _seqTbl_1037[] = { 2, 3 };
const u8 map_y_table_1038[] = { 0x2E, 0x2E };
const u8 size_table_1039[] = { 0xA, 8 };

void dm_manual_all_init(void) {
    struct_watchManual *temp_s4;
    RomOffsetPair *tbl;
    void **heap;
    s32 i;
    s32 j;
    s32 k;

    evs_seqnumb = _seqTbl_1037[evs_manual_no % ARRAY_COUNTU(_seqTbl_1037)];
    evs_seqence = 1;

    switch (evs_manual_no) {
        case EVS_MANUAL_NO_0:
        case EVS_MANUAL_NO_3:
            evs_gamesel = ENUM_EVS_GAMESEL_0;
            evs_playcnt = 1;
            break;

        case EVS_MANUAL_NO_1:
        case EVS_MANUAL_NO_4:
            evs_gamesel = ENUM_EVS_GAMESEL_1;
            evs_playcnt = 2;
            break;

        case EVS_MANUAL_NO_2:
        case EVS_MANUAL_NO_5:
            evs_gamesel = ENUM_EVS_GAMESEL_2;
            evs_playcnt = 4;
            break;
    }

    evs_gamemode = ENUM_EVS_GAMEMODE_0;
    story_proc_no = STORY_PROC_NO_1;

    dm_game_init_heap();
    heap = dm_game_heap_top();
    watchManual = ALIGN_PTR(*heap);
    temp_s4 = watchManual;
    bzero(temp_s4, sizeof(struct_watchManual));
    *heap = watchManual + 1;

    tbl = _romDataTbl;
    _texAll = tiLoadTexData(heap, tbl[ROMDATATBL_TUTORIAL_KASA].start, tbl[ROMDATATBL_TUTORIAL_KASA].end);
    _texKaSa = tiLoadTexData(heap, tbl[ROMDATATBL_MENU_KASA].start, tbl[ROMDATATBL_MENU_KASA].end);

    func_80071F14(&temp_s4->unk_034, heap);
    func_800721D8(&temp_s4->unk_034);

    dm_game_init_static();
    dm_game_init_snap_bg();
    dm_game_init(false);

    temp_s4->unk_00C = 0xFF;
    temp_s4->unk_010 = -8;
    temp_s4->unk_170 = 0;

    for (i = 0; i < ARRAY_COUNTU(temp_s4->unk_01C); i++) {
        temp_s4->unk_01C[i] = -0x14;
    }

    temp_s4->unk_02C = 0;
    temp_s4->unk_014 = 0;
    temp_s4->unk_018 = 0;
    temp_s4->unk_184 = 0;

    j = 0;
    for (i = 0; i < STRUCT_WATCHGAME_MANUAL_UNK_LEN; i++) {
        temp_s4->unk_14C[i].unk_0 = 0;
        temp_s4->unk_14C[i].unk_4 = 0;

        temp_s4->unk_0C4[i].unk_8 = j;
        temp_s4->unk_0C4[i].unk_0 = sinf(temp_s4->unk_0C4[i].unk_8 * 3.141592654 / 180.0) * 20.0f + 45.0f;
        temp_s4->unk_0C4[i].unk_4 = cosf(temp_s4->unk_0C4[i].unk_8 * 3.141592654 / 180.0) * -20.0f + 155.0f;

        j += 0x78;
    }

    switch (evs_manual_no) {
        case EVS_MANUAL_NO_0:
        case EVS_MANUAL_NO_3:
            k = 0;
            j = 0;
            break;

        case EVS_MANUAL_NO_1:
        case EVS_MANUAL_NO_4:
            k = 0;
            j = 1;
            break;

        case EVS_MANUAL_NO_2:
        case EVS_MANUAL_NO_5:
            k = 1;
            j = 2;
            break;
    }

    for (i = 0; i < ARRAY_COUNT(game_state_data); i++) {
        struct_game_state_data *ptr = &game_state_data[i];

        ptr->unk_006 = map_x_table_1036[j][i];
        ptr->unk_008 = map_y_table_1038[k];
        ptr->unk_00A = size_table_1039[k];
    }

    for (i = 0; i < ARRAY_COUNT(game_state_data); i++) {
        struct_game_state_data *ptr = &game_state_data[i];

        ptr->unk_02C = 1;
        ptr->unk_02D = GameSpeed[ptr->unk_02C];
        ptr->unk_04D = 0;
        ptr->unk_04E = 2;

        switch (evs_manual_no) {
            case EVS_MANUAL_NO_2:
            case EVS_MANUAL_NO_5:
                ptr->unk_02B = 0xC;
                ptr->unk_02A = 0;
                break;

            default:
                ptr->unk_02B = 8;
                ptr->unk_02A = 2;
                break;
        }

        temp_s4->unk_174[i] = 0;

        for (j = 0; j < ARRAY_COUNTU(temp_s4->unk_0E8[i]); j++) {
            struct_800F4890_unk_0E8 *temp2 = &temp_s4->unk_0E8[i][j];

            temp2->unk_0 = 0;
            temp2->unk_1 = 0;
            temp2->unk_2 = 0;

            for (k = 0; k < ARRAY_COUNTU(temp2->unk_3); k++) {
                temp2->unk_3[k] = 0;
            }
        }
    }

    temp_s4->unk_164 = 0;
    temp_s4->unk_168 = 0;
    temp_s4->unk_16C = 0;
    temp_s4->unk_030 = 0;
}
#endif

#if VERSION_US || VERSION_CN
/**
 * Original name: dm_manual_main
 */
enum_main_no dm_manual_main(NNSched *sc) {
    OSMesgQueue scMQ;
    OSMesg scMsgBuf[NN_SC_MAX_MESGS];
    NNScClient scClient;
    s32 temp_v1_2;
    s32 var_a0;
    s32 i;
    bool var_s3 = true;
    bool var_s4 = false;
    struct_watchManual *temp_s2;

    osCreateMesgQueue(&scMQ, scMsgBuf, ARRAY_COUNT(scMsgBuf));
    nnScAddClient(sc, &scClient, &scMQ);

    dm_manual_all_init();

    temp_s2 = watchManual;

    for (i = 0; i < ARRAY_COUNT(game_state_data); i++) {
        aifMakeFlagSet(&game_state_data[i]);
    }

    while (!var_s4) {
        joyProcCore();
        osRecvMesg(&scMQ, NULL, OS_MESG_BLOCK);

#ifdef NN_SC_PERF
        if (D_80092F10_cn) {
            graphic_no = GRAPHIC_NO_0;
            dm_audio_update();
            continue;
        }
#endif
        func_80071FA0(&temp_s2->unk_034);
        dm_effect_make();

        var_s4 = false;
        temp_s2->unk_184++;

        if (temp_s2->unk_010 > 0) {
            var_s4 = temp_s2->unk_00C == 0xFF;
        }

        temp_v1_2 = temp_s2->unk_00C + temp_s2->unk_010;
        temp_v1_2 = CLAMP(temp_v1_2, 0, 255);
        temp_s2->unk_00C = temp_v1_2;

        switch (evs_manual_no) {
            case EVS_MANUAL_NO_0:
                var_s3 = dm_manual_1_main();
                break;

            case EVS_MANUAL_NO_1:
                var_s3 = dm_manual_2_main();
                break;

            case EVS_MANUAL_NO_2:
                var_s3 = dm_manual_3_main();
                break;

            case EVS_MANUAL_NO_3:
                var_s3 = dm_manual_4_main();
                break;
        }

        dm_seq_set_volume(0x60);
        dm_audio_update();

        if (temp_s2->unk_018 != 0) {
            temp_s2->unk_014++;
            if (temp_s2->unk_014 >= temp_s2->unk_018) {
                temp_s2->unk_014 = 0;
                temp_s2->unk_018 = 0;
                dm_seq_play_in_game(evs_seqnumb * 2);
            }
        }
        if (temp_s2->unk_00C == 0) {
            var_a0 = B_BUTTON;
            if (main_old == MAIN_NO_3) {
                var_a0 = ANY_BUTTON;
            }
            if (gControllerPressedButtons[main_joy[0]] & var_a0) {
                var_s3 = false;
            }
        }

        if (!var_s3) {
            if (temp_s2->unk_010 < 0) {
                temp_s2->unk_010 = -temp_s2->unk_010;
            }
        }

        graphic_no = GRAPHIC_NO_3;
    }

    dm_audio_stop();
    graphic_no = GRAPHIC_NO_0;

    while (!dm_audio_is_stopped() || (pendingGFX != 0)) {
        osRecvMesg(&scMQ, NULL, OS_MESG_BLOCK);
        dm_audio_update();
    }

    nnScRemoveClient(sc, &scClient);

    if (main_old == MAIN_NO_3) {
        return MAIN_NO_3;
    } else if (main_old == MAIN_NO_6) {
        return MAIN_NO_6;
    }

#ifdef PRESERVE_UB
    return MAIN_NO_3;
#endif
}
#endif

#if VERSION_US || VERSION_CN
void dm_manual_graphic(void) {
    Mtx *mtx;
    Vtx *vtx;
    OSScTask *ptr;
    s32 color;
    s32 alpha;
    struct_watchManual *temp_s1 = watchManual;

    gGfxHead = gGfxGlist[gfx_gtask_no];
    ptr = &B_800FAE80[gfx_gtask_no];

    mtx = dm_get_mtx_buf();
    vtx = dm_get_vtx_buf();

    gSPSegment(gGfxHead++, 0x00, NULL);
    F3RCPinitRtn();
    F3ClearFZRtn(false);

    gDPSetScissor(gGfxHead++, G_SC_NON_INTERLACE, 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1);

    dm_game_draw_snap_bg(&gGfxHead, &mtx, &vtx, 0);
    dm_manual_draw_fg(&mtx, &vtx);

    color = 255;
    alpha = CLAMP((temp_s1->unk_00C - 127) * 1.2 + 127, 0, 255);
    if (alpha > 0) {
        FillRectRGBA(&gGfxHead, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, color, color, color, alpha);
    }

    gDPFullSync(gGfxHead++);
    gSPEndDisplayList(gGfxHead++);

    osWritebackDCacheAll();
    gfxTaskStart(ptr, gGfxGlist[gfx_gtask_no], (gGfxHead - gGfxGlist[gfx_gtask_no]) * sizeof(Gfx), 0, OS_SC_SWAPBUFFER);
}
#endif

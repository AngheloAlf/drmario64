/**
 * Original filename: dm_game_main.c
 */

#include "dm_game_main.h"

#include "include_asm.h"
#include "macros_defines.h"
#include "unknown_structs.h"
#include "main_segment_variables.h"
#include "boot_functions.h"
#include "boot_variables.h"
#include "util.h"
#include "gcc/memory.h"
#include "rom_offsets.h"
#include "buffers.h"
#include "audio/sound.h"
#include "graphic.h"
#include "aiset.h"
#include "replay.h"
#include "game_etc.h"
#include "record.h"
#include "vr_init.h"
#include "main1x.h"
#include "028820.h"
#include "tex_func.h"
#include "main_story.h"
#include "debug_menu.h"
#include "aiset.h"
#include "nnsched.h"
#include "static.h"
#include "dm_virus_init.h"
#include "calc.h"
#include "066580.h"
#include "libc/assert.h"

#if VERSION_US || CC_CHECK
// The compiler needs to not see the declared functions to match the cn version
#include "joy.h"
#endif
#if VERSION_CN && !CC_CHECK
void joyCursorFastSet(u16 mask, u8 index);
#endif

#ifdef NN_SC_PERF
extern s32 D_800BEF08_cn;
#endif

#if VERSION_US || VERSION_CN
s32 func_800601F0(struct_game_state_data *gameStateDataRef, s32 arg1) {
    s32 var_a3 = 0;
    s32 var_a2;

    for (var_a2 = gameStateDataRef->unk_038; var_a2 < gameStateDataRef->unk_037; var_a2++) {
        s32 var_v1 = MIN(var_a2, ARRAY_COUNT(Score1p[arg1]) - 1);

        var_a3 += Score1p[arg1][var_v1] * 100;
    }

    gameStateDataRef->unk_038 = gameStateDataRef->unk_037;
    return var_a3;
}
#endif

#if VERSION_US || VERSION_CN
void func_80060270(struct_game_state_data *gameStateDataRef, s32 arg1) {
    gameStateDataRef->unk_000 += arg1;
    if (gameStateDataRef->unk_000 > 9999900) {
        gameStateDataRef->unk_000 = 9999900;
    }

    if (evs_high_score < gameStateDataRef->unk_000) {
        evs_high_score = gameStateDataRef->unk_000;
    }
}
#endif

#if VERSION_US || VERSION_CN
s32 dm_make_score(struct_game_state_data *gameStateDataRef) {
    s32 temp_v0;
    s32 temp;

    if (evs_story_flg != 0) {
        if (evs_story_level < 3) {
            temp = evs_story_level;
        } else {
            temp = 2;
        }
    } else {
        switch (evs_gamesel) {
            case ENUM_EVS_GAMESEL_0:
                temp = gameStateDataRef->unk_02C;
                break;

            case ENUM_EVS_GAMESEL_1:
                temp = gameStateDataRef->unk_02C;
                break;

            case ENUM_EVS_GAMESEL_2:
                temp = gameStateDataRef->unk_02C;
                break;

            case ENUM_EVS_GAMESEL_3:
                temp = gameStateDataRef->unk_02C;
                break;

            case ENUM_EVS_GAMESEL_4:
                temp = gameStateDataRef->unk_02C;
                break;

            case ENUM_EVS_GAMESEL_5:
                temp = gameStateDataRef->unk_02C;
                break;

            case ENUM_EVS_GAMESEL_6:
                temp = gameStateDataRef->unk_02C;
                break;

            default:
                break;
        }
    }

    temp_v0 = func_800601F0(gameStateDataRef, temp);
    func_80060270(gameStateDataRef, temp_v0);
    return temp_v0;
}
#endif

extern s8 dm_chaine_se_table_vs_178[];    // sndindex
extern s8 dm_chaine_se_table_4p_179[][3]; // sndindex

#if VERSION_US || VERSION_CN
void dm_attack_se(struct_game_state_data *gameStateData, s32 arg1) {
    s32 i;

    if (gameStateData->unk_03A < 2) {
        return;
    }

    switch (evs_gamesel) {
        case ENUM_EVS_GAMESEL_0:
            dm_snd_play_in_game(SND_INDEX_59);
            break;

        case ENUM_EVS_GAMESEL_1:
        case ENUM_EVS_GAMESEL_3:
            dm_snd_play_in_game(dm_chaine_se_table_vs_178[arg1]);
            break;

        case ENUM_EVS_GAMESEL_2:
            for (i = 0; i < ARRAY_COUNT(dm_chaine_se_table_4p_179[arg1]); i++) {
                if ((gameStateData->unk_03C[3] >> i) & 1) {
                    dm_snd_play_in_game(dm_chaine_se_table_4p_179[arg1][i]);
                }
            }
            break;

        default:
            break;
    }
}
#endif

#if VERSION_US || VERSION_CN
void dm_warning_h_line(struct_game_state_data *gameStateData, GameMapCell *mapCells) {
    bool var_s2 = false;
    s32 rowPlusOne;

    for (rowPlusOne = 1; rowPlusOne < 4; rowPlusOne++) {
        s32 column;

        for (column = 0; column < GAME_MAP_COLUMNS; column++) {
            if (get_map_info(mapCells, column, rowPlusOne) == true) {
                var_s2 = true;
                break;
            }
        }

        if (var_s2) {
            break;
        }
    }

    if (var_s2) {
        if (gameStateData->unk_044 == 0) {
            gameStateData->unk_044 = 1;
        }
    } else {
        gameStateData->unk_044 = 0;
    }
}
#endif

#if VERSION_US || VERSION_CN
s32 set_down_flg(GameMapCell *mapCells) {
    s32 sp10[2];
    s32 var_s4;
    s32 var_s7;
    s32 var_v1;
    s32 var_s1;

    for (var_s4 = 0; var_s4 < (GAME_MAP_ROWS - 2) * GAME_MAP_COLUMNS; var_s4++) {
        mapCells[var_s4].unk_4[1] = 1;
    }

    for (var_s7 = GAME_MAP_ROWS - 3; var_s7 >= 0; var_s7--) {
        for (var_s4 = 0; var_s4 < GAME_MAP_COLUMNS; var_s4++) {
            s32 index = GAME_MAP_GET_INDEX(var_s7, var_s4);

            if ((mapCells + index)->unk_4[0] != 0) {
                if ((mapCells + index)->unk_4[4] < 0) {
                    if (((mapCells + index)->unk_2 == 2) || ((mapCells + index)->unk_2 == 3)) {
                        if ((mapCells + index)->unk_2 == 2) {
                            for (var_s1 = 0; var_s1 < 2U; var_s1++) {
                                sp10[var_s1] = 1;
                                if (get_map_info(mapCells, (mapCells + index + var_s1)->unk_0,
                                                 (mapCells + index + var_s1)->unk_1 + 1) == 1) {
                                    if ((mapCells + index + var_s1 + GAME_MAP_COLUMNS)->unk_4[1] != 1) {
                                        sp10[var_s1] = 0;
                                    }
                                }
                            }

                            if ((sp10[0] == 0) || (sp10[1] == 0)) {
                                for (var_s1 = 0; var_s1 < 2U; var_s1++) {
                                    (mapCells + index + var_s1)->unk_4[1] = 0;
                                }
                            }
                        } else if ((mapCells + index)->unk_2 == 3) {
                            for (var_s1 = 0; var_s1 < 2U; var_s1++) {
                                sp10[var_s1] = 1;
                                if (get_map_info(mapCells, (mapCells + index - var_s1)->unk_0,
                                                 (mapCells + index - var_s1)->unk_1 + 1) == 1) {
                                    if ((mapCells + index - var_s1 + GAME_MAP_COLUMNS)->unk_4[1] != 1) {
                                        sp10[var_s1] = 0;
                                    }
                                }
                            }

                            if ((sp10[0] == 0) || (sp10[1] == 0)) {
                                for (var_s1 = 0; var_s1 < 2U; var_s1++) {
                                    (mapCells + index - var_s1)->unk_4[1] = 0;
                                }
                            }
                        }
                    } else if (get_map_info(mapCells, (mapCells + index)->unk_0, (mapCells + index)->unk_1 + 1) == 1) {
                        if ((mapCells + index + GAME_MAP_COLUMNS)->unk_4[1] != 1) {
                            (mapCells + index)->unk_4[1] = 0;
                        }
                    }
                } else {
                    (mapCells + index)->unk_4[1] = 0;
                }
            } else {
                (mapCells + index)->unk_4[1] = 0;
            }
        }
    }

    for (var_s4 = var_v1 = 0; var_s4 < (GAME_MAP_ROWS - 1) * GAME_MAP_COLUMNS; var_s4++) {
        if (mapCells[var_s4].unk_4[0] != 0) {
            if (mapCells[var_s4].unk_4[1] != 0) {
                var_v1++;
            }
        }
    }

    return var_v1;
}
#endif

#if VERSION_US || VERSION_CN
void go_down(struct_game_state_data *gameStateData, GameMapCell *mapCells, s32 arg2) {
    bool var_a0 = false;
    s32 row;
    s32 j;

    gameStateData->unk_036++;
    if (gameStateData->unk_036 < arg2) {
        return;
    }

    gameStateData->unk_036 = 0;

    for (row = GAME_MAP_ROWS - 1; row >= 0; row--) {
        for (j = 0; j < GAME_MAP_COLUMNS; j++) {
            s32 index = GAME_MAP_GET_INDEX(row, j);

            if (mapCells[index].unk_4[1] != 0) {
                set_map(mapCells, mapCells[index].unk_0, mapCells[index].unk_1 + 1, mapCells[index].unk_2,
                        mapCells[index].unk_3);
                clear_map(mapCells, mapCells[index].unk_0, mapCells[index].unk_1);
                var_a0 = true;
            }
        }
    }

    if (var_a0) {
        dm_snd_play_in_game(SND_INDEX_55);
    }

    if ((gameStateData->unk_049 != 0) && (gameStateData->unk_01C == 0x12)) {
        for (j = 0; j < (GAME_MAP_ROWS - 1) * GAME_MAP_COLUMNS; j++) {
            if ((mapCells[j].unk_4[0] != 0) && (mapCells[j].unk_4[1] == 0) && (mapCells[j].unk_3 < 3)) {
                mapCells[j].unk_3 += 3;
            }
        }
    }

    if (set_down_flg(mapCells) == 0) {
        if (dm_h_erase_chack(mapCells) || dm_w_erase_chack(mapCells)) {
            if (gameStateData->unk_049 == 0) {
                gameStateData->unk_00C = GAMESTATEDATA_UNK_00C_6;
            } else {
                gameStateData->unk_00C = GAMESTATEDATA_UNK_00C_15;
            }
            gameStateData->unk_02F = 0;
        } else {
            if (gameStateData->unk_049 == 0) {
                gameStateData->unk_00C = GAMESTATEDATA_UNK_00C_9;
            } else {
                gameStateData->unk_00C = GAMESTATEDATA_UNK_00C_16;
            }
        }
    }
}
#endif

#if VERSION_US || VERSION_CN
void erase_anime(GameMapCell *mapCells) {
    s32 i;

    for (i = 0; i < (GAME_MAP_ROWS - 1) * GAME_MAP_COLUMNS; i++) {
        GameMapCell *cell = &mapCells[i];

        if ((cell->unk_4[0] != 0) && (cell->unk_4[2] != 0)) {
            cell->unk_2++;

            if (cell->unk_4[4] >= 0) {
                if (cell->unk_2 >= 0xF) {
                    clear_map(mapCells, cell->unk_0, cell->unk_1);
                }
            } else {
                if (cell->unk_2 >= 7) {
                    clear_map(mapCells, cell->unk_0, cell->unk_1);
                }
            }
        }
    }
}
#endif

#if VERSION_US || VERSION_CN
/**
 * Original name: rotate_table_399
 */
const s32 rotate_table_399[] = {
    0x00000001,
    0x00000003,
    0x00000004,
    0x00000002,
};

/**
 * Original name: rotate_mtx_400
 */
const s32 rotate_mtx_400[] = {
    0x00000002, 0x00000000, 0x00000003, 0x00000001, 0x00000002, 0x00000000,
};
#endif

#if VERSION_US || VERSION_CN
/**
 * Original name: throw_rotate_capsel
 */
void throw_rotate_capsel(struct_game_state_data_unk_178 *arg0) {
    s32 i;
    s32 var_t0;
    s32 temp_a2;

    if (arg0->unk_0[0] == arg0->unk_0[1]) {
        arg0->unk_0[1]++;
        arg0->unk_2[1]++;

        temp_a2 = arg0->unk_6[0];
        arg0->unk_6[0] = arg0->unk_6[1];
        arg0->unk_6[1] = temp_a2;

        var_t0 = 1;
    } else {
        arg0->unk_0[1]--;
        arg0->unk_2[1]--;
        var_t0 = -1;
    }

    for (i = 0; i < ARRAY_COUNT(arg0->unk_4); i++) {
        temp_a2 = rotate_table_399[arg0->unk_4[i]];
        temp_a2 += var_t0;

        arg0->unk_4[i] = rotate_mtx_400[temp_a2];
    }
}
#endif

#if VERSION_US || VERSION_CN
void translate_capsel(GameMapCell *mapCells, struct_game_state_data *arg1, s32 arg2, s32 arg3) {
    s32 var_s1 = 0;
    struct_game_state_data_unk_178 *temp_s5 = &arg1->unk_178;

    if ((temp_s5->unk_2[0] <= 0) || (temp_s5->unk_8 == 0)) {
        return;
    }

    if (arg2 == 1) {
        if (temp_s5->unk_0[0] == temp_s5->unk_0[1]) {
            if ((temp_s5->unk_0[1] < 7) && (get_map_info(mapCells, temp_s5->unk_0[1] + 1, temp_s5->unk_2[0]) != arg2)) {
                if (temp_s5->unk_2[1] == 0) {
                    var_s1 = 1;
                } else if (get_map_info(mapCells, temp_s5->unk_0[0] + 1, temp_s5->unk_2[1]) != arg2) {
                    var_s1 = 1;
                }
            }
        } else if (temp_s5->unk_0[1] < 7) {
            if (get_map_info(mapCells, temp_s5->unk_0[1] + 1, temp_s5->unk_2[0]) != arg2) {
                var_s1 = 1;
            }
        }
    } else if (arg2 == -1) {
        if (temp_s5->unk_0[0] == temp_s5->unk_0[1]) {
            if ((temp_s5->unk_0[0] > 0) && (get_map_info(mapCells, temp_s5->unk_0[0] - 1, temp_s5->unk_2[0]) != 1)) {
                if (temp_s5->unk_2[1] == 0) {
                    var_s1 = -1;
                } else if (get_map_info(mapCells, temp_s5->unk_0[0] - 1, temp_s5->unk_2[1]) != 1) {
                    var_s1 = -1;
                }
            }
        } else if (temp_s5->unk_0[0] > 0) {
            if (get_map_info(mapCells, temp_s5->unk_0[0] - 1, temp_s5->unk_2[0]) != 1) {
                var_s1 = -1;
            }
        }
    }

    if (var_s1 != 0) {
        dm_snd_play_in_game(SND_INDEX_65);
        arg1->unk_034 = 0;
        temp_s5->unk_0[0] += var_s1;
        temp_s5->unk_0[1] += var_s1;
    } else {
        if (arg1->unk_034 == 0) {
            arg1->unk_034 = 1;
            dm_snd_play_in_game(SND_INDEX_65);
        }

        if (arg2 == 1) {
            joyCursorFastSet(0x100, arg3);
        } else if (arg2 == -1) {
            joyCursorFastSet(0x200, arg3);
        }
    }
}
#endif

#if VERSION_US || VERSION_CN
void rotate_capsel(GameMapCell *mapCells, struct_game_state_data_unk_178 *arg1, s32 arg2) {
    s32 var_s1 = 0;
    s32 temp;

    if ((arg1->unk_2[0] <= 0) || (arg1->unk_8 == 0)) {
        return;
    }

    if (arg1->unk_0[0] == arg1->unk_0[1]) {
        if ((arg1->unk_0[0] == 7) || (get_map_info(mapCells, arg1->unk_0[0] + 1, arg1->unk_2[0]) == 1)) {
            if ((arg1->unk_0[0] != 0) && (get_map_info(mapCells, arg1->unk_0[0] - 1, arg1->unk_2[0]) != 1)) {
                arg1->unk_0[0]--;
                var_s1 = 1;
            }
        } else {
            arg1->unk_0[1]++;
            var_s1 = 1;
        }

        if (var_s1 != 0) {
            arg1->unk_2[1]++;
            if (arg2 == -1) {
                temp = arg1->unk_6[0];
                arg1->unk_6[0] = arg1->unk_6[1];
                arg1->unk_6[1] = temp;
            }
        }
    } else {
        if (arg1->unk_2[0] == 1) {
            arg1->unk_0[1]--;
            var_s1 = -1;
        } else if (get_map_info(mapCells, arg1->unk_0[0], arg1->unk_2[0] - 1) == 1) {
            if (get_map_info(mapCells, arg1->unk_0[0] + 1, arg1->unk_2[0] - 1) != 1) {
                arg1->unk_0[0]++;
                var_s1 = -1;
            }
        } else {
            arg1->unk_0[1]--;
            var_s1 = -1;
        }

        if (var_s1 != 0) {
            arg1->unk_2[1]--;
            if (arg2 == 1) {
                temp = arg1->unk_6[0];
                arg1->unk_6[0] = arg1->unk_6[1];
                arg1->unk_6[1] = temp;
            }
        }
    }

    if (var_s1 != 0) {
        s32 i;

        dm_snd_play_in_game(SND_INDEX_67);

        for (i = 0; i < ARRAY_COUNTU(arg1->unk_4); i++) {
            temp = rotate_table_474[arg1->unk_4[i]];
            temp += var_s1;
            arg1->unk_4[i] = rotate_mtx_475[temp];
        }
    }
}
#endif

#define CAPSMAGAZINE_GET_A(mag) (((mag) >> 4) % 3)
#define CAPSMAGAZINE_GET_B(mag) ((mag) % 3)

#if VERSION_US || VERSION_CN
void dm_make_magazine(void) {
    u8 sp18[2];
    s32 i;

    CapsMagazine[0] = random(0xFFFF) % ARRAY_COUNT(CapsMagazine);

    sp18[0] = CAPSMAGAZINE_GET_A(CapsMagazine[0]);
    sp18[1] = CAPSMAGAZINE_GET_B(CapsMagazine[0]);

    i = 1;
    while (i < ARRAY_COUNT(CapsMagazine)) {
        u8 sp20[2];

        CapsMagazine[i] = random(0xFFFF) % ARRAY_COUNT(CapsMagazine);

        sp20[0] = CAPSMAGAZINE_GET_A(CapsMagazine[i]);
        sp20[1] = CAPSMAGAZINE_GET_B(CapsMagazine[i]);

        if ((sp20[0] != sp18[0]) || sp20[1] != sp18[1]) {
            i++;
            sp18[0] = sp20[0];
            sp18[1] = sp20[1];
        }
    }
}
#endif

#if VERSION_US || VERSION_CN
void func_80060F60(struct_game_state_data_unk_178 *arg0, s32 arg1, s32 arg2) {
    arg0->unk_0[0] = 3;
    arg0->unk_0[1] = 4;
    arg0->unk_2[1] = 0;
    arg0->unk_2[0] = 0;
    arg0->unk_4[0] = 2;
    arg0->unk_4[1] = 3;
    arg0->unk_6[0] = arg1;
    arg0->unk_6[1] = arg2;
    arg0->unk_8 = 1;
    arg0->unk_A = 0;
    arg0->unk_9 = 0;
}
#endif

#if VERSION_US || VERSION_CN
void func_80060FA0(struct_game_state_data_unk_178 *arg0, s32 arg1, s32 arg2) {
    func_80060F60(arg0, arg1, arg2);
    arg0->unk_9 = 1;
}
#endif

#if VERSION_US || VERSION_CN
void dm_set_capsel(struct_game_state_data *arg0) {
    arg0->unk_034 = 0;

    func_80060FA0(&arg0->unk_178, CAPSMAGAZINE_GET_A(CapsMagazine[arg0->unk_032]),
                  CAPSMAGAZINE_GET_B(CapsMagazine[arg0->unk_032]));
    arg0->unk_033 = arg0->unk_032;

    arg0->unk_032++;
    if (arg0->unk_032 >= 0xFE) {
        arg0->unk_032 = 1;
    }

    func_80060F60(&arg0->unk_184, CAPSMAGAZINE_GET_A(CapsMagazine[arg0->unk_032]),
                  CAPSMAGAZINE_GET_B(CapsMagazine[arg0->unk_032]));
}
#endif

#if VERSION_US || VERSION_CN
const u8 _speed_561[] = {
    0x0F,
    0x14,
    0x19,
};
#endif

#if VERSION_US || VERSION_CN
void dm_capsel_speed_up(struct_game_state_data *gameStateDataRef) {
    gameStateDataRef->unk_02E++;
    if (gameStateDataRef->unk_02E >= 0xA) {
        u8 temp;

        dm_snd_play_in_game(SND_INDEX_58);
        gameStateDataRef->unk_02E = 0;

        gameStateDataRef->unk_02D++;
        temp = GameSpeed[3];
        if (temp < gameStateDataRef->unk_02D) {
            gameStateDataRef->unk_02D = temp;
        }
    }

    if (evs_gamemode == ENUM_EVS_GAMEMODE_2) {
        gameStateDataRef->unk_02D = MIN(_speed_561[gameStateDataRef->unk_16C], gameStateDataRef->unk_02D);
    }
}
#endif

#if VERSION_US || VERSION_CN
bool dm_check_game_over(struct_game_state_data *gameStateDataRef, GameMapCell *mapCells UNUSED) {
    if (gameStateDataRef->unk_020 == 4) {
        return true;
    }
    return false;
}
#endif

#if VERSION_US || VERSION_CN
s32 update_flash_virus_count(struct_game_state_data *arg0, GameMapCell *mapCells, s32 arg2) {
    s32 ret = 0;
    s32 i;

    for (i = 0; i < arg0->unk_164; i++) {
        s32 index = GAME_MAP_GET_INDEX_ALT(arg0->unk_0D4[i][1], arg0->unk_0D4[i][0]);

        if (((mapCells[index].unk_4[0] == 0) || (mapCells[index].unk_4[2] != 0) || (mapCells[index].unk_4[4] < 0))) {
            if (arg2 != 0) {
                arg0->unk_0D4[i][2] = -1;
            }
        } else {
            ret++;
        }
    }

    return ret;
}
#endif

#if VERSION_US || VERSION_CN
s32 func_8006121C(struct_game_state_data *gameStateDataRef, GameMapCell *mapCells, UNK_TYPE arg2) {
    if (evs_gamemode == ENUM_EVS_GAMEMODE_1) {
        gameStateDataRef->unk_025 = update_flash_virus_count(gameStateDataRef, mapCells, arg2);
    } else {
        gameStateDataRef->unk_025 = get_virus_count(mapCells);
    }

    return gameStateDataRef->unk_025;
}
#endif

#if VERSION_US || VERSION_CN
void dm_set_virus(struct_game_state_data *gameStateDataRef, GameMapCell *mapCells, struct_virus_map_data *virusMapData,
                  u8 virusMapDispOrder[VIRUS_MAP_DISP_ORDER_LEN]) {
    s32 temp_v0;

    if (gameStateDataRef->unk_014 != GAMESTATEDATA_UNK_014_2) {
        return;
    }

    temp_v0 = dm_get_first_virus_count(evs_gamemode, gameStateDataRef);

    if (gameStateDataRef->unk_024 < temp_v0) {
        while (gameStateDataRef->unk_024 < temp_v0) {
            if (!(virusMapDispOrder[gameStateDataRef->unk_024] & 0x80)) {
                break;
            }
            gameStateDataRef->unk_024++;
        }

        if (gameStateDataRef->unk_024 < temp_v0) {
            u8 *temp_a0 = &virusMapDispOrder[gameStateDataRef->unk_024];
            u8 cellIndex = *temp_a0;

            *temp_a0 |= 0x80;

            set_virus(mapCells, virusMapData[cellIndex].unk_1, virusMapData[cellIndex].unk_2,
                      virusMapData[cellIndex].unk_0,
                      virus_anime_table[virusMapData[cellIndex].unk_0][gameStateDataRef->unk_027]);
            if (gameStateDataRef->unk_01C == 0x12) {
                mapCells[cellIndex].unk_3 += 3;
            }
        }
    }

    if (gameStateDataRef->unk_024 >= temp_v0) {
        gameStateDataRef->unk_014 = GAMESTATEDATA_UNK_014_1;
        gameStateDataRef->unk_00C = GAMESTATEDATA_UNK_00C_2;
    }

    func_8006121C(gameStateDataRef, mapCells, 0);
}
#endif

#if VERSION_US || VERSION_CN
void dm_virus_anime(struct_game_state_data *arg0, GameMapCell *mapCells) {
    s32 index;

    arg0->unk_029++;
    if (arg0->unk_02B >= arg0->unk_029) {
        return;
    }

    arg0->unk_029 = 0;

    arg0->unk_027 += arg0->unk_028;
    if (arg0->unk_02A < arg0->unk_027) {
        arg0->unk_028 = -1;
    } else if (arg0->unk_027 == 0) {
        arg0->unk_028 = 1;
    }

    for (index = 0; index < (GAME_MAP_ROWS - 1) * GAME_MAP_COLUMNS; index++) {
        if ((mapCells[index].unk_4[0] != 0) && (mapCells[index].unk_4[2] == 0)) {
            if (mapCells[index].unk_4[4] >= 0) {
                mapCells[index].unk_2 = virus_anime_table[mapCells[index].unk_4[4]][arg0->unk_027];
            }
        }
    }
}
#endif

#if VERSION_US || VERSION_CN
void dm_capsel_erase_anime(struct_game_state_data *gameStateDataRef, GameMapCell *mapCells) {
    gameStateDataRef->unk_036++;

    if (gameStateDataRef->unk_036 == 10) {
        erase_anime(mapCells);
        gameStateDataRef->unk_035++;
    } else if (gameStateDataRef->unk_036 > 26) {
        erase_anime(mapCells);
        set_down_flg(mapCells);
        gameStateDataRef->unk_035 = 0;
        gameStateDataRef->unk_00C = GAMESTATEDATA_UNK_00C_8;
        gameStateDataRef->unk_036 = 14;
    }
}
#endif

#if VERSION_US || VERSION_CN
void dm_make_erase_h_line(struct_game_state_data *arg0, GameMapCell *mapCells, s32 rowStart, s32 count, s32 column) {
    s32 row;

    for (row = rowStart; row < rowStart + count + 1; row++) {
        s32 index = GAME_MAP_GET_INDEX(row, column);

        if (mapCells[index].unk_4[2] == 1) {
            continue;
        }

        mapCells[index].unk_4[2] = 1;

        if (mapCells[index].unk_4[4] < 0) {
            mapCells[index].unk_2 = 5;
        } else {
            mapCells[index].unk_2 = 0xD;
            arg0->unk_037 += 1;
            arg0->unk_03C[3] |= 8;
            arg0->unk_03C[3] |= (0x10 << mapCells[index].unk_4[3]);
        }
    }
}
#endif

#if VERSION_US || VERSION_CN
bool dm_h_erase_chack(GameMapCell *mapCells) {
    s32 column;

    for (column = 0; column < GAME_MAP_COLUMNS; column++) {
        s32 row;
        s32 val = 0xF;
        s32 var_a1 = 0;
        s32 var_a3 = -1;

        for (row = 0; row < GAME_MAP_ROWS - 1; row++) {
            if (mapCells[GAME_MAP_GET_INDEX(row, column)].unk_4[0] != 0) {
                if (mapCells[GAME_MAP_GET_INDEX(row, column)].unk_4[3] != var_a3) {
                    if (var_a1 < 3) {
                        if (row >= 0xD) {
                            break;
                        }
                        var_a3 = mapCells[GAME_MAP_GET_INDEX(row, column)].unk_4[3];
                        var_a1 = 0;
                    } else {
                        return true;
                    }
                } else {
                    var_a1++;
                    if (row == val) {
                        if (var_a1 >= 3) {
                            return true;
                        }
                    }
                }
            } else if (var_a1 >= 3) {
                return true;
            } else if (row < 13) {
                var_a1 = 0;
                var_a3 = -1;
            } else {
                break;
            }
        }
    }

    return false;
}
#endif

#if VERSION_US || VERSION_CN
void dm_h_erase_chack_set(struct_game_state_data *gameStateDataRef, GameMapCell *mapCells) {
    s32 column;

    for (column = 0; column < GAME_MAP_COLUMNS; column++) {
        s32 var_s1 = 0;
        s32 var_s5 = -1;
        s32 var_s2 = -1;
        s32 var_fp = 0;
        s32 row;

        for (row = 0; row < GAME_MAP_ROWS - 1; row++) {
            if (mapCells[GAME_MAP_GET_INDEX(row, column)].unk_4[0] != 0) {
                if (mapCells[GAME_MAP_GET_INDEX(row, column)].unk_4[3] != var_s2) {
                    if (var_s1 >= 3) {
                        dm_make_erase_h_line(gameStateDataRef, mapCells, var_s5, var_s1, column);
                        if (gameStateDataRef->unk_039 == 0) {
                            gameStateDataRef->unk_03C[3] |= (1 << var_s2);
                        }
                        gameStateDataRef->unk_03C[var_s2]++;
                        gameStateDataRef->unk_03A++;
                    }

                    if (row < 0xD) {
                        var_s5 = row;
                        var_s2 = mapCells[GAME_MAP_GET_INDEX(row, column)].unk_4[3];
                        var_s1 = 0;
                    } else {
                        var_fp = 1;
                    }
                } else {
                    var_s1++;
                    if (row == 15) {
                        if (var_s1 >= 3) {
                            dm_make_erase_h_line(gameStateDataRef, mapCells, var_s5, var_s1, column);
                            if (gameStateDataRef->unk_039 == 0) {
                                gameStateDataRef->unk_03C[3] |= (1 << var_s2);
                            }
                            gameStateDataRef->unk_03C[var_s2]++;
                            gameStateDataRef->unk_03A++;
                        }
                    }
                }
            } else {
                if (var_s1 >= 3) {
                    dm_make_erase_h_line(gameStateDataRef, mapCells, var_s5, var_s1, column);
                    if (gameStateDataRef->unk_039 == 0) {
                        gameStateDataRef->unk_03C[3] |= (1 << var_s2);
                    }
                    gameStateDataRef->unk_03C[var_s2]++;
                    gameStateDataRef->unk_03A++;
                }

                if (row >= 13) {
                    var_fp = 1;
                } else {
                    var_s1 = 0;
                    var_s5 = -1;
                    var_s2 = -1;
                }
            }

            if (var_fp != 0) {
                break;
            }
        }
    }
}
#endif

#if VERSION_US || VERSION_CN
void dm_make_erase_w_line(struct_game_state_data *arg0, GameMapCell *mapCells, s32 columnStart, s32 count, s32 row) {
    s32 column = columnStart;
    u32 columnEnd = column + count + 1;

    for (; column < columnEnd; column++) {
        s32 index = GAME_MAP_GET_INDEX(row, column);

        if (mapCells[index].unk_4[2] != 1) {
            mapCells[index].unk_4[2] = 1;

            if (mapCells[index].unk_4[4] < 0) {
                mapCells[index].unk_2 = 5;
            } else {
                mapCells[index].unk_2 = 0xD;
                arg0->unk_037 += 1;
                arg0->unk_03C[3] |= 8;
                arg0->unk_03C[3] |= (0x10 << mapCells[index].unk_4[3]);
            }
        }
    }
}
#endif

#if VERSION_US || VERSION_CN
bool dm_w_erase_chack(GameMapCell *mapCells) {
    s32 row;

    for (row = 0; row < GAME_MAP_ROWS - 1; row++) {
        s32 var_a1 = 0;
        s32 var_a3 = -1;
        s32 column;

        for (column = 0; column < GAME_MAP_COLUMNS; column++) {
            if (mapCells[GAME_MAP_GET_INDEX(row, column)].unk_4[0] != 0) {
                if (mapCells[GAME_MAP_GET_INDEX(row, column)].unk_4[3] != var_a3) {
                    if (var_a1 >= 3) {
                        return true;
                    } else if (column < 5) {
                        var_a3 = mapCells[GAME_MAP_GET_INDEX(row, column)].unk_4[3];
                        var_a1 = 0;
                    } else {
                        break;
                    }
                } else {
                    var_a1++;
                    if (column == 7) {
                        if (var_a1 >= 3) {
                            return true;
                        }
                    }
                }
            } else if (var_a1 >= 3) {
                return true;
            } else if (column < 5) {
                var_a1 = 0;
                var_a3 = -1;
            } else {
                break;
            }
        }
    }
    return false;
}
#endif

#if VERSION_US || VERSION_CN
void dm_w_erase_chack_set(struct_game_state_data *arg0, GameMapCell *mapCells) {
    s32 row;

    for (row = 0; row < GAME_MAP_ROWS - 1; row++) {
        s32 column;
        s32 var_s1 = 0;
        s32 var_s6 = -1;
        s32 var_s3 = -1;
        bool var_fp = false;

        for (column = 0; column < GAME_MAP_COLUMNS; column++) {
            s32 index = GAME_MAP_GET_INDEX(row, column);
            if (mapCells[index].unk_4[0] != 0) {
                if (mapCells[index].unk_4[3] != var_s3) {
                    if (var_s1 >= 3) {
                        dm_make_erase_w_line(arg0, mapCells, var_s6, var_s1, row);
                        if (arg0->unk_039 == 0) {
                            arg0->unk_03C[3] |= 1 << var_s3;
                        }
                        arg0->unk_03C[var_s3]++;
                        arg0->unk_03A++;
                    }
                    if (column >= 5) {
                        var_fp = true;
                    } else {
                        var_s6 = column;
                        var_s3 = mapCells[index].unk_4[3];
                        var_s1 = 0;
                    }
                } else {
                    var_s1++;
                    if (column == 7) {
                        if (var_s1 >= 3) {
                            dm_make_erase_w_line(arg0, mapCells, var_s6, var_s1, row);
                            if (arg0->unk_039 == 0) {
                                arg0->unk_03C[3] |= 1 << var_s3;
                            }
                            arg0->unk_03C[var_s3]++;
                            arg0->unk_03A++;
                        }
                    }
                }
            } else {
                if (var_s1 >= 3) {
                    dm_make_erase_w_line(arg0, mapCells, var_s6, var_s1, row);
                    if (arg0->unk_039 == 0) {
                        arg0->unk_03C[3] |= 1 << var_s3;
                    }
                    arg0->unk_03C[var_s3]++;
                    arg0->unk_03A++;
                }

                if (column >= 5) {
                    var_fp = true;
                } else {
                    var_s1 = 0;
                    var_s6 = -1;
                    var_s3 = -1;
                }
            }

            if (var_fp) {
                break;
            }
        }
    }
}
#endif

#if VERSION_US || VERSION_CN
void dm_h_ball_chack(GameMapCell *mapCells) {
    u32 column;

    for (column = 0; column < GAME_MAP_COLUMNS; column++) {
        u32 row;

        for (row = 0; row < GAME_MAP_ROWS - 1; row++) {
            s32 index = GAME_MAP_GET_INDEX(row, column);
            s32 temp;

            if (mapCells[index].unk_4[0] == 0) {
                continue;
            }

            if (mapCells[index].unk_2 == 0) {
                temp = GAME_MAP_GET_INDEX(row + 1, column);
                if (mapCells[temp].unk_2 != 1) {
                    mapCells[index].unk_2 = 4;
                }
            } else if (mapCells[index].unk_2 == 1) {
                if (mapCells[index].unk_1 == 1) {
                    mapCells[index].unk_2 = 4;
                } else {
                    temp = GAME_MAP_GET_INDEX(row - 1, column);
                    if (mapCells[temp].unk_2 != 0) {
                        mapCells[index].unk_2 = 4;
                    }
                }
            }
        }
    }
}
#endif

#if VERSION_US || VERSION_CN
void dm_w_ball_chack(GameMapCell *mapCells) {
    u32 row;

    for (row = 0; row < GAME_MAP_ROWS - 1; row++) {
        u32 column;

        for (column = 0; column < GAME_MAP_COLUMNS; column++) {
            if (mapCells[GAME_MAP_GET_INDEX(row, column)].unk_4[0] != 0) {
                if (mapCells[GAME_MAP_GET_INDEX(row, column)].unk_2 == 2) {
                    if (mapCells[GAME_MAP_GET_INDEX(row, column + 1)].unk_2 != 3) {
                        mapCells[GAME_MAP_GET_INDEX(row, column)].unk_2 = 4;
                    }
                } else if ((mapCells[GAME_MAP_GET_INDEX(row, column)].unk_2 == 3) &&
                           (mapCells[GAME_MAP_GET_INDEX(row, column - 1)].unk_2 != 2)) {
                    mapCells[GAME_MAP_GET_INDEX(row, column)].unk_2 = 4;
                }
            }
        }
    }
}
#endif

#if VERSION_US || VERSION_CN
bool dm_black_up(struct_game_state_data *gameStateDataP, GameMapCell *mapCells) {
    if ((gameStateDataP->unk_048 != 0) && (gameStateDataP->unk_049 == 0)) {
        gameStateDataP->unk_036++;
        if (gameStateDataP->unk_036 >= 6U) {
            u8 temp;
            u8 column;

            gameStateDataP->unk_036 = 0;
            temp = ((gameStateDataP->unk_040 - 1) * GAME_MAP_COLUMNS);

            for (column = 0; column < GAME_MAP_COLUMNS; column++) {
                // hate this
                if ((mapCells + temp + column)->unk_4[0] != 0) {
                    (mapCells + temp + column)->unk_3 += 3;
                }
            }

            gameStateDataP->unk_040--;
            if (gameStateDataP->unk_040 == 0) {
                gameStateDataP->unk_049 = 1;
                return true;
            }
        }
    }

    return false;
}
#endif

#if VERSION_US || VERSION_CN
bool dm_broken_set(struct_game_state_data *gameStateData, GameMapCell *mapCells) {
    struct_game_state_data_unk_050 sp20[ARRAY_COUNTU(gameStateData->unk_050)];
    s32 pad[0x18] UNUSED;
    bool ret = false;
    s32 var_s0;
    s32 var_s1;

    if (gameStateData->unk_050[0].unk_0 != 0) {
        if (gameStateData->unk_03B < gameStateData->unk_03A) {
            gameStateData->unk_03B = gameStateData->unk_03A;
        }

        gameStateData->unk_03A = 0;
        gameStateData->unk_039 = 0;
        gameStateData->unk_037 = 0;
        gameStateData->unk_038 = 0;

        for (var_s0 = 0; var_s0 < 4U; var_s0++) {
            gameStateData->unk_03C[var_s0] = 0;
        }

        for (var_s0 = 0, var_s1 = 7; var_s0 < 0x10U; var_s0 += 2, var_s1--) {
            u32 temp_v0_2 = gameStateData->unk_050[0].unk_0 & (3 << var_s0);

            if (temp_v0_2 != 0) {
                set_map(mapCells, var_s1, 1, 4, (temp_v0_2 >> var_s0) - 1);
            }
        }

        dm_h_ball_chack(mapCells);
        dm_w_ball_chack(mapCells);
        set_down_flg(mapCells);

        for (var_s0 = 0; var_s0 < ARRAY_COUNTU(gameStateData->unk_050); var_s0++) {
            sp20[var_s0].unk_0 = gameStateData->unk_050[var_s0].unk_0;
            sp20[var_s0].unk_2 = gameStateData->unk_050[var_s0].unk_2;
            gameStateData->unk_050[var_s0].unk_0 = 0;
            gameStateData->unk_050[var_s0].unk_2 = 0;
        }

        for (var_s0 = 0, var_s1 = 1; var_s0 < ARRAY_COUNTU(gameStateData->unk_050) - 1; var_s0++, var_s1++) {
            gameStateData->unk_050[var_s0].unk_0 = sp20[var_s1].unk_0;
            gameStateData->unk_050[var_s0].unk_2 = sp20[var_s1].unk_2;
        }

        ret = true;
    }

    return ret;
}
#endif

#if VERSION_US || VERSION_CN
void dm_calc_erase_score_pos(struct_game_state_data *arg0, GameMapCell *mapCells, dm_calc_erase_score_pos_arg2 *arg2) {
    s32 row;
    s32 var_t2 = 0;

    arg2->unk_4 = 0;
    arg2->unk_0 = 0;

    for (row = 0; row < GAME_MAP_ROWS - 1; row++) {
        s32 column;

        for (column = 0; column < GAME_MAP_COLUMNS; column++) {
            GameMapCell *cell = &mapCells[GAME_MAP_GET_INDEX_ALT(row, column)];

            if (cell->unk_4[2] != 0) {
                arg2->unk_0 += cell->unk_0;
                arg2->unk_4 += cell->unk_1;
                var_t2++;
            }
        }
    }

    if (var_t2 > 0) {
        arg2->unk_0 = arg2->unk_0 * arg0->unk_00A / var_t2;
        arg2->unk_4 = arg2->unk_4 * arg0->unk_00A / var_t2;
    }
}
#endif

#if VERSION_US || VERSION_CN
bool dm_calc_capsel_pos(struct_game_state_data *gameStateDataRef, s32 arg1[2], s32 arg2[2]) {
    struct_game_state_data_unk_178 *temp_s1 = &gameStateDataRef->unk_178;
    s32 var_t0;
    s32 what = 0x24;

    if (temp_s1->unk_8 == 0) {
        return false;
    }

    if (gameStateDataRef->unk_00C == GAMESTATEDATA_UNK_00C_3) {
        f32 temp_ft3;
        f32 temp_ft2;
        f32 var_fa0;
        s32 var_a0;
        s32 var_s2;
        f32 a;
        f32 b;

        if (gameStateDataRef->unk_02C == 0) {
            var_a0 = gameStateDataRef->unk_02F >> 2;
        } else {
            var_a0 = gameStateDataRef->unk_02F >> 1;
        }

        var_a0 = var_a0 % 4;
        var_a0 += 4;

        var_s2 = 0;
        if ((var_a0 == 5) || (var_a0 == 7)) {
            var_s2 = 5;
        }

        if (gameStateDataRef->unk_178.unk_0[0] == gameStateDataRef->unk_178.unk_0[1]) {
            if ((var_a0 == 4) || (var_a0 == 6)) {
                throw_rotate_capsel(&gameStateDataRef->unk_178);
            }
        } else {
            if ((var_a0 == 5) || (var_a0 == 7)) {
                throw_rotate_capsel(&gameStateDataRef->unk_178);
            }
        }

        if (gameStateDataRef->unk_02F < (FlyingCnt[gameStateDataRef->unk_02C] / 3)) {
            var_fa0 = (what / (FlyingCnt[gameStateDataRef->unk_02C] / 3)) * gameStateDataRef->unk_02F;
        } else if (gameStateDataRef->unk_02F < ((FlyingCnt[gameStateDataRef->unk_02C] / 3) * 2)) {
            var_fa0 = what;
        } else {
            var_fa0 = ((FlyingCnt[gameStateDataRef->unk_02C] * 2) / 3);
            var_fa0 = gameStateDataRef->unk_02F - var_fa0;
            var_fa0 = what - (2.0f * var_fa0);
        }

        temp_ft3 = gameStateDataRef->unk_006 + gameStateDataRef->unk_00A * temp_s1->unk_0[0];
        temp_ft2 = gameStateDataRef->unk_008 + gameStateDataRef->unk_00A * (temp_s1->unk_2[0] - 1);

        a = temp_ft3 + ((218.0f - temp_ft3) / (FlyingCnt[gameStateDataRef->unk_02C] - 1)) *
                           (FlyingCnt[gameStateDataRef->unk_02C] - gameStateDataRef->unk_02F);
        b = temp_ft2 + ((52.0f - temp_ft2) / (FlyingCnt[gameStateDataRef->unk_02C] - 1)) *
                           (FlyingCnt[gameStateDataRef->unk_02C] - gameStateDataRef->unk_02F);

        for (var_t0 = 0; var_t0 < 2; var_t0++) {
            arg1[var_t0] = (u32)a + var_s2 + gameStateDataRef->unk_00A * (temp_s1->unk_0[var_t0] - 3);
            arg2[var_t0] =
                (u32)b + var_s2 - (u16)(u32)var_fa0 + 1 + gameStateDataRef->unk_00A * (temp_s1->unk_2[var_t0] + 1);
        }
    } else if (temp_s1->unk_2[0] <= 0) {
        for (var_t0 = 0; var_t0 < 2; var_t0++) {
            arg1[var_t0] = gameStateDataRef->unk_006 + gameStateDataRef->unk_00A * temp_s1->unk_0[var_t0];
            arg2[var_t0] = gameStateDataRef->unk_008 + gameStateDataRef->unk_00A * temp_s1->unk_2[var_t0] - 0xA;
        }
    } else {
        for (var_t0 = 0; var_t0 < 2; var_t0++) {
            arg1[var_t0] = gameStateDataRef->unk_006 + gameStateDataRef->unk_00A * temp_s1->unk_0[var_t0];
            arg2[var_t0] = gameStateDataRef->unk_008 + gameStateDataRef->unk_00A * temp_s1->unk_2[var_t0] + 1;
        }
    }

    return true;
}
#endif

#if VERSION_US || VERSION_CN
void dm_draw_capsel_by_gfx(struct_game_state_data *gameStateData, s32 *arg1, s32 *arg2) {
    struct_game_state_data_unk_178 *temp_s1 = &gameStateData->unk_178;
    s32 var_s3;
    TiTexData *temp_v0;
    s32 i;

    gSPDisplayList(gGfxHead++, normal_texture_init_dl);

    if (gameStateData->unk_00A == 0xA) {
        var_s3 = 0;
    } else {
        var_s3 = 1;
    }

    temp_v0 = dm_game_get_capsel_tex(var_s3);

    load_TexBlock_4b(temp_v0->texs[1], temp_v0->info[0], temp_v0->info[1]);

    for (i = 0; i < 2; i++) {
        load_TexPal(dm_game_get_capsel_pal(var_s3, temp_s1->unk_6[i])->texs[0]);
        draw_Tex(arg1[i], arg2[i], gameStateData->unk_00A, gameStateData->unk_00A, 0,
                 temp_s1->unk_4[i] * gameStateData->unk_00A);
    }
}
#endif

#if VERSION_US || VERSION_CN
const u8 _retryMenu_itemCount[] = {
    2, 3, 2, 3, 2, 3,
};
#endif

#if VERSION_US || VERSION_CN
/**
 * Original name: dm_draw_capsel_by_cpu_tentative
 *
 * Draw the falling pill.
 *
 * Does this by drawing directly to the framebuffer instead of using the gfx microcode.
 */
void dm_draw_capsel_by_cpu_tentative(struct_game_state_data *gameStateDataRef, s32 arg1[2], s32 arg2[2]) {
    struct_game_state_data_unk_178 *temp_s6 = &gameStateDataRef->unk_178;
    TiTexData *tex_data;
    s32 var_s1;
    s32 var_s5;

    if (gameStateDataRef->unk_00A == 0xA) {
        var_s5 = 0;
    } else {
        var_s5 = 1;
    }

    for (var_s1 = 0; var_s1 < 2; var_s1++) {
        u8 *ci4_texture;
        u16 *fb;
        u16 *tlut;
        s32 var_t4;
        s32 temp_t1;
        s32 temp_a3_2;

        if ((arg2[var_s1] < 0) || ((arg2[var_s1] + gameStateDataRef->unk_00A) > SCREEN_HEIGHT)) {
            continue;
        }

        if ((arg1[var_s1] < 0) || ((arg1[var_s1] + gameStateDataRef->unk_00A) > SCREEN_WIDTH)) {
            continue;
        }

        tex_data = dm_game_get_capsel_pal(var_s5, temp_s6->unk_6[var_s1]);
        tlut = tex_data->texs[0];

        tex_data = dm_game_get_capsel_tex(var_s5);

        ci4_texture = tex_data->texs[1];
        ci4_texture += (temp_s6->unk_4[var_s1] * gameStateDataRef->unk_00A * tex_data->info[0]) >> 1;

        temp_a3_2 = (tex_data->info[0] - gameStateDataRef->unk_00A) >> 1;

        fb = &gFramebuffers[gCurrentFramebufferIndex ^ 1][arg2[var_s1] * SCREEN_WIDTH + arg1[var_s1]];
        temp_t1 = SCREEN_WIDTH - gameStateDataRef->unk_00A;

        for (var_t4 = 0; var_t4 < gameStateDataRef->unk_00A; var_t4++) {
            s32 var_a2;

            for (var_a2 = 0; var_a2 < gameStateDataRef->unk_00A; var_a2 += 2) {
                s32 pixel_pair = *ci4_texture;
                s32 index;

                // Manually draw each CI4 pixel
                index = pixel_pair >> 4;
                if (index != 0) {
                    fb[0] = tlut[index];
                }

                index = pixel_pair & 0xF;
                if (index != 0) {
                    fb[1] = tlut[index];
                }

                ci4_texture += 1;
                fb += 2;
            }

            ci4_texture += temp_a3_2;
            fb += temp_t1;
        }
    }
}
#endif

#if VERSION_US || VERSION_CN
UNK_PTR *dm_game_heap_top(void) {
    return &heapTop;
}
#endif

#if VERSION_US || VERSION_CN
AnimeState *get_virus_anime_state(s32 arg0) {
    struct_watchGame *ptr = watchGame;

    return &ptr->animeStates[arg0];
}
#endif

#if VERSION_US || VERSION_CN
AnimeSmog *get_virus_smog_state(s32 arg0) {
    struct_watchGame *ptr = watchGame;

    return &ptr->animeSmogs[arg0];
}
#endif

#if VERSION_US || VERSION_CN
Mtx *dm_get_mtx_buf(void) {
    return gameGeom->mtxBuf[gfx_gtask_no];
}
#endif

#if VERSION_US || VERSION_CN
Vtx *dm_get_vtx_buf(void) {
    return gameGeom->vtxBuf[gfx_gtask_no];
}
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", func_800601F0);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", func_80060270);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", dm_make_score);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", dm_attack_se);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", dm_warning_h_line);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", set_down_flg);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", go_down);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", erase_anime);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", throw_rotate_capsel);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", translate_capsel);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", rotate_capsel);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", dm_make_magazine);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", func_80060F60);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", func_80060FA0);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", dm_set_capsel);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", dm_capsel_speed_up);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", dm_check_game_over);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", update_flash_virus_count);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", func_8006121C);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", dm_set_virus);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", dm_virus_anime);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", dm_capsel_erase_anime);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", dm_make_erase_h_line);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", dm_h_erase_chack);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", dm_h_erase_chack_set);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", dm_make_erase_w_line);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", dm_w_erase_chack);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", dm_w_erase_chack_set);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", dm_h_ball_chack);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", dm_w_ball_chack);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", dm_black_up);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", dm_broken_set);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", dm_calc_erase_score_pos);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", dm_calc_capsel_pos);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", dm_draw_capsel_by_gfx);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", dm_draw_capsel_by_cpu_tentative);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", dm_game_heap_top);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", get_virus_anime_state);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", get_virus_smog_state);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", dm_get_mtx_buf);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", dm_get_vtx_buf);
#endif

#if VERSION_US || VERSION_CN
void func_80062920(void) {
    struct_watchGame *ptr = watchGame;
    s32 i;

    for (i = 0; i < evs_playcnt; i++) {
        ptr->unk_888[i] = 0;
    }

    initEtcWork(ptr->unk_884, evs_playcnt);
}
#endif

#if VERSION_US || VERSION_CN
void func_80062978(s32 index, s32 arg1) {
    watchGame->unk_888[index] = arg1;
}
#endif

#if VERSION_US || VERSION_CN
void func_80062990(s32 arg0) {
    func_80062978(arg0, 0xB4);
}
#endif

#if VERSION_US || VERSION_CN
void func_800629AC(s32 arg0) {
    func_80062978(arg0, 0xB4);
}
#endif

#if VERSION_US || VERSION_CN
void func_800629C8(s32 arg0) {
    func_80062978(arg0, 0xB4);
}
#endif

#if VERSION_US || VERSION_CN
void func_800629E4(s32 arg0) {
    func_80062978(arg0, 0xB4);
    init_pause_disp();
}
#endif

#if VERSION_US || VERSION_CN
void func_80062A08(s32 index) {
    func_80062978(index, 0xB4);
}
#endif

#if VERSION_US || VERSION_CN
void func_80062A24(s32 index) {
    func_80062978(index, 0xB4);
}
#endif

#if VERSION_US || VERSION_CN
void func_80062A40(s32 arg0) {
    func_80062978(arg0, 0xB4);
}
#endif

#if VERSION_US || VERSION_CN
bool func_80062A5C(s32 arg0) {
    struct_watchGame *ptr = watchGame;

    if (ptr->unk_888[arg0] != 0) {
        ptr->unk_888[arg0] -= 1;
    }
    return ptr->unk_888[arg0] != 0;
}
#endif

#if VERSION_US || VERSION_CN
bool func_80062A8C(s32 arg0) {
    return func_80062A5C(arg0);
}
#endif

#if VERSION_US || VERSION_CN
bool func_80062AA8(s32 arg0) {
    return func_80062A5C(arg0);
}
#endif

#if VERSION_US || VERSION_CN
bool func_80062AC4(s32 arg0) {
    return func_80062A5C(arg0);
}
#endif

#if VERSION_US || VERSION_CN
void func_80062AE0(s32 arg0) {
    func_80062A5C(arg0);
}
#endif

#if VERSION_US || VERSION_CN
bool func_80062AFC(s32 arg0) {
    return func_80062A5C(arg0);
}
#endif

#if VERSION_US || VERSION_CN
bool func_80062B18(s32 arg0) {
    return func_80062A5C(arg0);
}
#endif

#if VERSION_US || VERSION_CN
bool func_80062B34(s32 arg0) {
    return func_80062A5C(arg0);
}
#endif

#if VERSION_US || VERSION_CN
void func_80062B50(struct_watchGame_unk_9D0 *arg0, UNK_TYPE arg1, UNK_TYPE arg2, UNK_TYPE arg3, UNK_TYPE arg4,
                   UNK_TYPE arg5, UNK_TYPE arg6) {
    arg0->unk_00 = arg1;
    arg0->unk_04 = arg2;
    arg0->unk_08 = 0;
    arg0->unk_0C = 0;
    arg0->unk_14 = arg3;
    arg0->unk_24 = 0;
    arg0->unk_18 = arg4;
    arg0->unk_1C = arg5;
    arg0->unk_20 = arg6;
}
#endif

#if VERSION_US || VERSION_CN
void func_80062B84(struct_watchGame_unk_9D0 *arg0) {
    func_80062B50(arg0, 0, 0, 0, 0, 0, 0);
    arg0->unk_28 = 0;
}
#endif

#if VERSION_US || VERSION_CN
bool func_80062BC4(struct_watchGame_unk_9D0 *arg0) {
    return arg0->unk_08 == 0x63;
}
#endif

#if VERSION_US || VERSION_CN
bool timeAttackResult_update(struct_watchGame_unk_9D0 *arg0, s32 arg1) {
    bool v1 = true;

    switch (arg0->unk_08) {
        case 0:
            if (arg0->unk_0C >= 0x78) {
                arg0->unk_08 = 0xA;
                arg0->unk_0C = 0;
                arg0->unk_10 = 0;
            } else {
                arg0->unk_0C++;
            }
            break;

        case 0xA:
            if (arg0->unk_14 == 0) {
                arg0->unk_08 = 0x14;
                arg0->unk_0C = 0;
            } else {
                s32 var_v0_2 = MIN(6, arg0->unk_14);
                s32 var_a0_2;

                arg0->unk_14 = arg0->unk_14 - var_v0_2;
                if (arg1 != 0) {
                    if (arg0->unk_14 == 0) {
                        dm_snd_play_in_game(SND_INDEX_78);
                    } else if (arg0->unk_10 == ((arg0->unk_10 / 10) * 0xA)) {
                        dm_snd_play_in_game(SND_INDEX_63);
                    }
                }

                var_a0_2 = _n_1199[arg0->unk_00];
                if (arg0->unk_10 >= 0xC8) {
                    var_a0_2 *= 3;
                } else if (arg0->unk_10 >= 0x64) {
                    var_a0_2 *= 2;
                }

                if (arg0->unk_04 != 0) {
                    u32 var_v1 = arg0->unk_20 + var_a0_2;

                    var_v1 = MIN(9999900, var_v1);
                    arg0->unk_20 = var_v1;
                    arg0->unk_24 += var_a0_2;
                }

                arg0->unk_10++;
            }

            arg0->unk_0C++;
            break;

        case 0x14:
            if (arg0->unk_0C < 0x3C) {
                arg0->unk_0C++;
            } else {
                arg0->unk_08 = 0x63;
                arg0->unk_0C = 0;
            }
            break;

        case 0x63:
            v1 = !func_80062BC4(arg0);
            break;
    }

    return v1;
}
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", func_80062920);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", func_80062978);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", func_80062990);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", func_800629AC);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", func_800629C8);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", func_800629E4);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", func_80062A08);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", func_80062A24);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", func_80062A40);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", func_80062A5C);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", func_80062A8C);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", func_80062AA8);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", func_80062AC4);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", func_80062AE0);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", func_80062AFC);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", func_80062B18);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", func_80062B34);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", func_80062B50);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", func_80062B84);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", func_80062BC4);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", timeAttackResult_update);
#endif

#if VERSION_US || VERSION_CN
void func_80062DA4(struct_watchGame_unk_9D0 *arg0) {
    while (timeAttackResult_update(arg0, 0)) {}
}
#endif

#if VERSION_US || VERSION_CN
s32 func_80062DD8(struct_watchGame_unk_9D0 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    func_80062B50(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
    func_80062DA4(arg0);
    arg0->unk_28 = arg0->unk_20;
    func_80062B50(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
    return arg0->unk_28;
}
#endif

#if VERSION_US || VERSION_CN
void func_80062E84(struct_watchGame_unk_0B8 *arg0) {
    s32 i;

    for (i = 0; i < ARRAY_COUNTU(arg0->unk_00); i++) {
        arg0->unk_00[i].unk_00 = 0;
        arg0->unk_00[i].unk_04 = 0;
        arg0->unk_00[i].unk_08 = 0;
        arg0->unk_00[i].unk_0C = 0;
        arg0->unk_00[i].unk_10 = 1.0f;
    }

    arg0->unk_A0 = 0;
}
#endif

#if VERSION_US || VERSION_CN
const f32 _big_virus_def_wait[] = { 12.5f, 10.0f, 7.5f };

const f32 _big_virus_min_wait[3] = { 5.0f, 4.5f, 4.0f };

const f32 _big_virus_max_wait[3] = { 12.5f, 10.0f, 7.5f };

const Color_RGB8 _scoreNumsColor[] = {
    { 255, 255, 255 }, { 255, 255, 255 }, { 255, 255, 255 }, { 255, 255, 255 }, { 255, 255, 255 }, { 255, 255, 255 },
};

#include "dm_game_main.msg.inc"

const s32 _posStP4StarX[4] = { 0xCD, 0xE6, 0xFF, 0x118 };

const s32 _posStStar[2][2] = {
    { 0x80, 0x48 },
    { 0xAC, 0x48 },
};

const s32 RO_800B1D28[2] = { 0x27, 0x5F };

const s32 _posP2StarX[2] = { 0x80, 0xAC };

const s32 _posP2StarY[3][3] = { { 0x48, -1, -1 }, { 0x50, 0x40, -1 }, { 0x58, 0x48, 0x38 } };

const s32 _posP4Bottle[4][2] = {
    { 0x10, 0x25 },
    { 0x58, 0x25 },
    { 0xA0, 0x25 },
    { 0xE8, 0x25 },
};

const s32 RO_800B1D7C[2] = { 4, 3 };

const s32 _posP4CharBase[4][2] = {
    { 0x10, 0xBA },
    { 0x58, 0xBA },
    { 0xA0, 0xBA },
    { 0xE8, 0xBA },
};

const s32 _posP4TeamStarX[3][2][3] = {
    { { 0x2D, -1, -1 }, { 0xBF, -1, -1 } },
    { { 0x22, 0x39, -1 }, { 0xB3, 0xCA, -1 } },
    { { 0x16, 0x2D, 0x44 }, { 0xA7, 0xBE, 0xD6 } },
};

const s32 _posP4CharStarX[3][4][3] = {
    {
        { 0x29, -1, -1 },
        { 0x71, -1, -1 },
        { 0xB9, -1, -1 },
        { 0x101, -1, -1 },
    },
    {
        { 0x1E, 0x35, -1 },
        { 0x66, 0x7D, -1 },
        { 0xAE, 0xC5, -1 },
        { 0xF6, 0x10D, -1 },
    },
    {
        { 0x12, 0x2A, 0x41 },
        { 0x5A, 0x72, 0x89 },
        { 0xA2, 0xBA, 0xD1 },
        { 0xEA, 0x102, 0x119 },
    },
};

const s32 _posP4StockCap[2][2] = {
    { 0x5F, 0x18 },
    { 0xF0, 0x18 },
};

const s32 _posP2VirusNum[2][2] = {
    { 0x8A, 0xD2 },
    { 0xB6, 0xD2 },
};

const s32 _posP2CharFrm[2][2] = {
    { 0x8A, 0x95 },
    { 0xB5, 0x95 },
};
#endif

#if VERSION_US || VERSION_CN
void func_80062EC0(struct_watchGame_unk_0B8 *arg0) {
    f32 val = 0.025f;
    s32 i;
    s32 var_s0;

    for (i = 0, var_s0 = arg0->unk_A0; i < ARRAY_COUNTU(arg0->unk_00);
         var_s0 = (var_s0 + 1) % ARRAY_COUNTU(arg0->unk_00), i++) {
        struct_watchGame_unk_0B8_unk_00 *temp_s1 = &arg0->unk_00[var_s0];
        struct_watchGame_unk_0B8_unk_00 *new_var = &arg0->unk_00[WrapI(0, ARRAY_COUNTU(arg0->unk_00), var_s0 - 1)];

        if (new_var->unk_10 > 0.2) {
            temp_s1->unk_10 = MIN(1.0f, temp_s1->unk_10 + val);
        }
    }
}
#endif

#if VERSION_US || VERSION_CN
void scoreNums_set(struct_watchGame_unk_0B8 *arg0, u32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 temp = CLAMP(arg2 - 1, 0, 5);
    s32 sp18[16];
    s32 var_a2;
    s32 var_s0;

    var_a2 = 0;
    while (arg1 != 0) {
        sp18[var_a2] = arg1 % 10;
        arg1 /= 10;
        var_a2 += 1;
    }

    arg3 -= ((var_a2 * 7) + 1) / 2;
    arg4 -= 6;

    for (var_s0 = var_a2 - 1; var_s0 >= 0; var_s0--) {
        struct_watchGame_unk_0B8_unk_00 *temp_v0;

        temp_v0 = &arg0->unk_00[arg0->unk_A0];
        temp_v0->unk_00 = arg3;
        arg3 += 7;
        temp_v0->unk_04 = arg4;
        temp_v0->unk_08 = sp18[var_s0];
        temp_v0->unk_0C = temp;
        temp_v0->unk_10 = 0.0f;
        arg0->unk_A0 = WrapI(0, 8, arg0->unk_A0 + 1);
    }
}
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", func_80062DA4);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", func_80062DD8);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", func_80062E84);
#endif

#if VERSION_GW
INCLUDE_RODATA("asm/gw/nonmatchings/main_segment/dm_game_main", RO_800B2AAC_gw);
#endif

#if VERSION_GW
INCLUDE_RODATA("asm/gw/nonmatchings/main_segment/dm_game_main", RO_800B2ABC_gw);
#endif

#if VERSION_GW
INCLUDE_RODATA("asm/gw/nonmatchings/main_segment/dm_game_main", RO_800B2AD4_gw);
#endif

#if VERSION_GW
INCLUDE_RODATA("asm/gw/nonmatchings/main_segment/dm_game_main", RO_800B2AD8_gw);
#endif

#if VERSION_GW
INCLUDE_RODATA("asm/gw/nonmatchings/main_segment/dm_game_main", RO_FLT_800B2AE0_gw);
#endif

#if VERSION_GW
INCLUDE_RODATA("asm/gw/nonmatchings/main_segment/dm_game_main", RO_FLT_800B2AEC_gw);
#endif

#if VERSION_GW
INCLUDE_RODATA("asm/gw/nonmatchings/main_segment/dm_game_main", RO_FLT_800B2AF8_gw);
#endif

#if VERSION_GW
INCLUDE_RODATA("asm/gw/nonmatchings/main_segment/dm_game_main", RO_800B2B04_gw);
#endif

#if VERSION_GW
INCLUDE_RODATA("asm/gw/nonmatchings/main_segment/dm_game_main", RO_STR_800B2B18_gw);
#endif

#if VERSION_GW
INCLUDE_RODATA("asm/gw/nonmatchings/main_segment/dm_game_main", RO_800B2B68_gw);
#endif

#if VERSION_GW
INCLUDE_RODATA("asm/gw/nonmatchings/main_segment/dm_game_main", RO_800B2B78_gw);
#endif

#if VERSION_GW
INCLUDE_RODATA("asm/gw/nonmatchings/main_segment/dm_game_main", RO_800B2B7C_gw);
#endif

#if VERSION_GW
INCLUDE_RODATA("asm/gw/nonmatchings/main_segment/dm_game_main", RO_800B2B88_gw);
#endif

#if VERSION_GW
INCLUDE_RODATA("asm/gw/nonmatchings/main_segment/dm_game_main", RO_800B2B8C_gw);
#endif

#if VERSION_GW
INCLUDE_RODATA("asm/gw/nonmatchings/main_segment/dm_game_main", RO_800B2B90_gw);
#endif

#if VERSION_GW
INCLUDE_RODATA("asm/gw/nonmatchings/main_segment/dm_game_main", RO_800B2BBC_gw);
#endif

#if VERSION_GW
INCLUDE_RODATA("asm/gw/nonmatchings/main_segment/dm_game_main", RO_800B2BC0_gw);
#endif

#if VERSION_GW
INCLUDE_RODATA("asm/gw/nonmatchings/main_segment/dm_game_main", RO_800B2BDC_gw);
#endif

#if VERSION_GW
INCLUDE_RODATA("asm/gw/nonmatchings/main_segment/dm_game_main", RO_800B2BE0_gw);
#endif

#if VERSION_GW
INCLUDE_RODATA("asm/gw/nonmatchings/main_segment/dm_game_main", RO_800B2BE4_gw);
#endif

#if VERSION_GW
INCLUDE_RODATA("asm/gw/nonmatchings/main_segment/dm_game_main", RO_800B2BE8_gw);
#endif

#if VERSION_GW
INCLUDE_RODATA("asm/gw/nonmatchings/main_segment/dm_game_main", RO_800B2BEC_gw);
#endif

#if VERSION_GW
INCLUDE_RODATA("asm/gw/nonmatchings/main_segment/dm_game_main", RO_800B2C1C_gw);
#endif

#if VERSION_GW
INCLUDE_RODATA("asm/gw/nonmatchings/main_segment/dm_game_main", RO_800B2CDC_gw);
#endif

#if VERSION_GW
INCLUDE_RODATA("asm/gw/nonmatchings/main_segment/dm_game_main", RO_FLT_800B2CE0_gw);
#endif

#if VERSION_GW
INCLUDE_RODATA("asm/gw/nonmatchings/main_segment/dm_game_main", RO_800B2CEC_gw);
#endif

#if VERSION_GW
INCLUDE_RODATA("asm/gw/nonmatchings/main_segment/dm_game_main", RO_800B2CF0_gw);
#endif

#if VERSION_GW
INCLUDE_RODATA("asm/gw/nonmatchings/main_segment/dm_game_main", RO_FLT_800B2CFC_gw);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", func_80062EC0);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", scoreNums_set);
#endif

#if VERSION_US || VERSION_CN
void backup_game_state(s32 index) {
    struct_gameBackup *ptr = gameBackup[index];
    s32 i;

    ptr->unk_0000 = *watchGame;

    for (i = 0; i < ARRAY_COUNTU(ptr->unk_0B60); i++) {
        ptr->unk_0B60[i] = game_state_data[i];
    }

    for (i = 0; i < ARRAY_COUNTU(ptr->unk_1A70); i++) {
        s32 j;

        for (j = 0; j < ARRAY_COUNTU(game_map_data[i]); j++) {
            ptr->unk_1A70[i][j] = game_map_data[i][j];
        }
    }

    ptr->highScore = evs_high_score;
    ptr->gameTime = evs_game_time;
}
#endif

#if VERSION_US || VERSION_CN
void resume_game_state(s32 index) {
    struct_gameBackup *ptr = gameBackup[index];
    s32 i;

    *watchGame = ptr->unk_0000;

    for (i = 0; i < ARRAY_COUNTU(ptr->unk_0B60); i++) {
        game_state_data[i] = ptr->unk_0B60[i];
    }

    for (i = 0; i < ARRAY_COUNTU(ptr->unk_1A70); i++) {
        s32 j;

        for (j = 0; j < ARRAY_COUNTU(game_map_data[i]); j++) {
            game_map_data[i][j] = ptr->unk_1A70[i][j];
        }
    }

    evs_high_score = ptr->highScore;
    evs_game_time = ptr->gameTime;
}
#endif

#if VERSION_US || VERSION_CN
void func_80063378(void) {
    struct_watchGame *watchGameRef = watchGame;

    if (watchGameRef->unk_000 == 0) {
        backup_game_state(1);
    }

    resume_game_state(0);
    watchGameRef->unk_000 = 1;
}
#endif

#if VERSION_US || VERSION_CN
void func_800633C0(void) {
    struct_watchGame *watchGameRef = watchGame;

    if (watchGameRef->unk_000 != 0) {
        resume_game_state(1);
        watchGameRef->unk_000 = 0;
    }
}
#endif

#if VERSION_US || VERSION_CN
void func_800633FC(void) {
    if (watchGame->unk_000 != 0) {
        replay_play_init();
    } else {
        replay_record_init(evs_playcnt);
    }
}
#endif

#if VERSION_US || VERSION_CN
void dm_warning_h_line_se(void) {
    struct_watchGame *watchGameP = watchGame;
    s32 var_a0 = 0;
    s32 i;

    for (i = 0; i < evs_playcnt; i++) {
        if (game_state_data[i].unk_020 == 1) {
            if (game_state_data[i].unk_044 != 0) {
                var_a0++;
            }
        }
    }

    if (var_a0 == 0) {
        watchGameP->unk_428 = 0;
    } else {
        watchGameP->unk_428++;

        if (watchGameP->unk_428 == 1) {
            dm_snd_play_in_game(SND_INDEX_79);
        } else if (watchGameP->unk_428 >= 300) {
            watchGameP->unk_428 = 0;
        }
    }
}
#endif

#if VERSION_US || VERSION_CN
void dm_play_count_down_se(void) {
    s32 i;

    if (evs_gamemode != ENUM_EVS_GAMEMODE_3) {
        return;
    }

    for (i = 0; i < evs_playcnt; i++) {
        if (game_state_data[i].unk_020 == 1) {
            break;
        }
    }

    if (i != evs_playcnt) {
        s32 diff = i = 10800 - evs_game_time;
        s32 temp2;
        s32 temp1;

        //! FAKE
        temp2 = diff / 60;
        i = diff % 60;
        temp1 = i;

        if ((temp1 == 0) && (temp2 > 0) && (temp2 < 0xB)) {
            dm_snd_play_in_game(SND_INDEX_72);
        }
    }
}
#endif

#if VERSION_US || VERSION_CN
/**
 * Original name: black_color_1384
 */
const s32 black_color_1384[] = { 0, 3 };

/**
 * Original name: dm_capsel_down
 */
void dm_capsel_down(struct_game_state_data *gameStateData, GameMapCell *mapCells) {
    struct_watchGame *watchGameP = watchGame;
    struct_game_state_data_unk_178 *temp_s2 = &gameStateData->unk_178;
    s32 var_s0_2;
    s32 var_s1_2;

    if (temp_s2->unk_2[0] > 0) {
        var_s0_2 = FallSpeed[gameStateData->unk_02D];
        if ((temp_s2->unk_2[0] < 4) && (temp_s2->unk_2[0] > 0)) {
            var_s0_2 += BonusWait[temp_s2->unk_2[0] - 1][gameStateData->unk_02C];
        }
        var_s1_2 = 0;
        if (get_map_info(mapCells, gameStateData->unk_178.unk_0[0], temp_s2->unk_2[0] + 1) != 0) {
            var_s1_2 = watchGameP->unk_898;
        }
        gameStateData->unk_031 = var_s0_2 + var_s1_2;
    } else {
        gameStateData->unk_031 = 0x1E;
    }

    gameStateData->unk_02F = gameStateData->unk_02F + gameStateData->unk_030;
    if (gameStateData->unk_02F < gameStateData->unk_031) {
        return;
    }

    gameStateData->unk_02F = 0;
    if (temp_s2->unk_8 == 0) {
        return;
    }

    if (temp_s2->unk_2[0] > 0) {
        if (temp_s2->unk_0[0] == temp_s2->unk_0[1]) {
            if (get_map_info(mapCells, temp_s2->unk_0[0], temp_s2->unk_2[0] + 1) != 0) {
                temp_s2->unk_9 = 0;
            }
        } else {
            for (var_s1_2 = 0; var_s1_2 < ARRAY_COUNTU(temp_s2->unk_0); var_s1_2++) {
                if (get_map_info(mapCells, temp_s2->unk_0[var_s1_2], temp_s2->unk_2[var_s1_2] + 1) != 0) {
                    temp_s2->unk_9 = 0;
                    break;
                }
            }
        }
    }

    for (var_s0_2 = 0; var_s0_2 < ARRAY_COUNTU(temp_s2->unk_2); var_s0_2++) {
        if (temp_s2->unk_2[var_s0_2] == 0x10) {
            temp_s2->unk_9 = 0;
            break;
        }
    }

    if (temp_s2->unk_9 != 0) {
        for (var_s0_2 = 0; var_s0_2 < ARRAY_COUNTU(temp_s2->unk_2); var_s0_2++) {
            if (temp_s2->unk_2[var_s0_2] < 0x10) {
                temp_s2->unk_2[var_s0_2]++;
            }
        }

        for (var_s0_2 = 0; var_s0_2 < ARRAY_COUNTU(temp_s2->unk_0); var_s0_2++) {
            if (get_map_info(mapCells, temp_s2->unk_0[var_s0_2], temp_s2->unk_2[var_s0_2]) != 0) {
                gameStateData->unk_020 = 4;
                gameStateData->unk_184.unk_8 = 0;
                temp_s2->unk_9 = 0;
                break;
            }
        }

        if (temp_s2->unk_9 != 0) {
            return;
        }
    }

    dm_snd_play_in_game(SND_INDEX_66);
    gameStateData->unk_00C = GAMESTATEDATA_UNK_00C_5;
    temp_s2->unk_8 = 0;

    for (var_s0_2 = 0; var_s0_2 < ARRAY_COUNTU(temp_s2->unk_2); var_s0_2++) {
        if (temp_s2->unk_2[var_s0_2] != 0) {
            set_map(mapCells, temp_s2->unk_0[var_s0_2], temp_s2->unk_2[var_s0_2], temp_s2->unk_4[var_s0_2],
                    temp_s2->unk_6[var_s0_2] + black_color_1384[gameStateData->unk_049]);
        }
    }
}
#endif

#if VERSION_US || VERSION_CN
s32 func_80063844(u32 arg0) {
    s32 var_v1 = 0;

    if (arg0 >= 4) {
        var_v1 = 0x55 << random(2);
    } else if (arg0 >= 3) {
        var_v1 = 0x15 << random(4);
    } else if (arg0 >= 2) {
        var_v1 = 0x11 << random(4);
    }
    return var_v1;
}
#endif

#if VERSION_US || VERSION_CN
s32 dm_set_attack_2p(struct_game_state_data *gameStateDataRef) {
    s32 temp_v0;
    s32 var_s0;
    s32 var_s2;
    s32 var_t1;
    struct_game_state_data *temp_s3;
    s32 var_a0;
    s32 i;

    if (gameStateDataRef->unk_03A < 2U) {
        return 0;
    }

    temp_s3 = &game_state_data[gameStateDataRef->unk_04B ^ 1];

    var_a0 = MIN(4, gameStateDataRef->unk_03A);

    for (i = 0; i < 1; i++) {
        if (temp_s3->unk_050[i].unk_0 != 0) {
            var_s2 = 0;
            for (var_s0 = 0; var_s0 < 8; var_s0++) {
                if (temp_s3->unk_050[i].unk_0 & (3 << (var_s0 << 1))) {
                    var_s2 |= 1 << var_s0;
                    var_t1 = var_s0 & 1;
                }
            }

            for (var_s0 = 0; var_s0 < 8; var_s0++) {
                if ((var_s0 & 1) == var_t1) {
                    var_s2 ^= 1 << var_s0;
                }
            }

            if (var_s2 == 0) {
                continue;
            }

        } else {
            var_s2 = func_80063844(var_a0);
        }

        temp_s3->unk_050[i].unk_2 = gameStateDataRef->unk_04B;

        for (var_s0 = 0; var_s0 < 8; var_s0++) {
            if (!((var_s2 >> var_s0) & 1)) {
                continue;
            }

            while ((gameStateDataRef->unk_03C[0] != 0) || (gameStateDataRef->unk_03C[1] != 0) ||
                   (gameStateDataRef->unk_03C[2] != 0)) {
                temp_v0 = random(3);
                if (gameStateDataRef->unk_03C[temp_v0] != 0) {
                    gameStateDataRef->unk_03C[temp_v0] -= 1;
                    temp_s3->unk_050[i].unk_0 |= (temp_v0 + 1) << (var_s0 << 1);
                    break;
                }
            }
        }

        break;
    }

    return 1;
}
#endif

#if VERSION_US || VERSION_CN
/**
 * Original name: attack_table_1531
 */
const char attack_table_1531[][3] = {
    { 3, 2, 1 },
    { 0, 3, 2 },
    { 1, 0, 3 },
    { 2, 1, 0 },
};

/**
 * Original name: dm_set_attack_4p
 */
s32 dm_set_attack_4p(struct_game_state_data *gameStateDataRef) {
    struct_watchGame *watchGameP = watchGame;
    struct_game_state_data *temp_s1;
    s32 sp20[3];
    s32 sp30[3];
    s32 sp40;
    s32 sp44;
    s32 temp_v0_3;
    s32 var_a1_2;
    s32 var_fp;
    s32 var_s1_2;
    s32 var_s0;
    s32 var_s6;

    if (gameStateDataRef->unk_03A < 2U) {
        return 0;
    }

    for (var_s6 = 0; var_s6 < 3U; var_s6++) {
        sp30[var_s6] = 0;
    }

    var_fp = 0;

    sp44 = 0;
    sp40 = 0;
    for (var_s6 = 0; var_s6 < 3; var_s6++) {
        if (!((gameStateDataRef->unk_03C[3] >> var_s6) & 1)) {
            continue;
        }

        temp_s1 = &game_state_data[attack_table_1531[gameStateDataRef->unk_04B][var_s6]];
        if (temp_s1->unk_04F == gameStateDataRef->unk_04F) {
            if (temp_s1->unk_048 != 0) {
                continue;
            }
            sp44 |= 1 << attack_table_1531[gameStateDataRef->unk_04B][var_s6];
        } else {
            if (!((temp_s1->unk_048 == 0) || ((temp_s1->unk_01C == 0x12) && (temp_s1->unk_04A != 0)))) {
                continue;
            }
            sp40 |= 1 << attack_table_1531[gameStateDataRef->unk_04B][var_s6];
        }

        if (var_fp > 0) {
            continue;
        }

        var_fp = 4;
        if (gameStateDataRef->unk_03A < 5U) {
            var_fp = (s32)gameStateDataRef->unk_03A;
        }

        for (var_s0 = 0; var_s0 < ARRAY_COUNTU(watchGameP->unk_8DC[gameStateDataRef->unk_04F]); var_s0++) {
            if (var_fp >= 4) {
                break;
            }

            if (watchGameP->unk_8DC[gameStateDataRef->unk_04F][var_s0] != -1) {
                gameStateDataRef->unk_03C[watchGameP->unk_8DC[gameStateDataRef->unk_04F][var_s0]] += 1;
                watchGameP->unk_8DC[gameStateDataRef->unk_04F][var_s0] = -1;
                var_fp += 1;
            }
        }

        for (var_s0 = 0; var_s0 < var_fp;) {
            if ((gameStateDataRef->unk_03C[0] + gameStateDataRef->unk_03C[1] + gameStateDataRef->unk_03C[2]) <= 0) {
                break;
            }
            temp_v0_3 = random(3);
            if (gameStateDataRef->unk_03C[temp_v0_3] != 0) {
                gameStateDataRef->unk_03C[temp_v0_3]--;
                sp30[temp_v0_3] += 1;
                var_s0 += 1;
            }
        }
    }

    if ((sp40 + sp44) == 0) {
        return 0;
    }

    for (var_s6 = 0; var_s6 < 4; var_s6++) {
        if (!((sp40 >> var_s6) & 1)) {
            continue;
        }

        temp_s1 = &game_state_data[var_s6];

        add_attack_effect(gameStateDataRef->unk_04B, _posP4CharBase[gameStateDataRef->unk_04B][0],
                          _posP4CharBase[gameStateDataRef->unk_04B][1], _posP4CharBase[temp_s1->unk_04B][0],
                          _posP4CharBase[temp_s1->unk_04B][1]);

        for (var_s0 = 0; var_s0 < ARRAY_COUNTU(sp20); var_s0++) {
            sp20[var_s0] = sp30[var_s0];
        }

        for (var_s0 = 0; var_s0 < 0x10; var_s0++) {
            if (temp_s1->unk_050[var_s0].unk_0 != 0) {
                continue;
            }

            var_a1_2 = func_80063844(var_fp);

            temp_s1->unk_050[var_s0].unk_2 = gameStateDataRef->unk_04B;
            for (var_s1_2 = 0; var_s1_2 < 8; var_s1_2++) {
                if (!((var_a1_2 >> var_s1_2) & 1)) {
                    continue;
                }

                while ((sp20[0] + sp20[1] + sp20[2]) > 0) {
                    temp_v0_3 = random(3);
                    if (sp20[temp_v0_3] > 0) {
                        sp20[temp_v0_3]--;
                        temp_s1->unk_050[var_s0].unk_0 |= (temp_v0_3 + 1) << (var_s1_2 * 2);
                        break;
                    }
                }
            }
        }
    }

    var_s0 = 0;

    for (var_s6 = 0; var_s6 < 4; var_s6++) {
        if (watchGameP->unk_8DC[gameStateDataRef->unk_04F][var_s6] == -1) {
            continue;
        }

        watchGameP->unk_8DC[gameStateDataRef->unk_04F][var_s0] = watchGameP->unk_8DC[gameStateDataRef->unk_04F][var_s6];
        var_s0 += 1;
    }

    for (; var_s0 < 4; var_s0++) {
        watchGameP->unk_8DC[gameStateDataRef->unk_04F][var_s0] = -1;
    }

    for (var_s6 = 0; var_s6 < 4; var_s6++) {
        if (!((sp44 >> var_s6) & 1)) {
            continue;
        }

        for (var_s0 = 0; var_s0 < 3U; var_s0++) {
            sp20[var_s0] = sp30[var_s0];
        }

        temp_v0_3 = 0;
        for (var_s0 = 0; var_s0 < 4; var_s0++) {
            if (watchGameP->unk_8DC[gameStateDataRef->unk_04F][var_s0] != -1) {
                continue;
            }

            for (; temp_v0_3 < 3; temp_v0_3++) {
                if (sp20[temp_v0_3] > 0) {
                    sp20[temp_v0_3]--;
                    watchGameP->unk_8DC[gameStateDataRef->unk_04F][var_s0] = temp_v0_3;
                    break;
                }
            }
        }
    }

    return 1;
}
#endif

#if VERSION_US || VERSION_CN
void func_80063FF4(void) {
    s32 i;
    s32 var_a3;

    switch (evs_gamesel) {
        case ENUM_EVS_GAMESEL_0:
        case ENUM_EVS_GAMESEL_3:
            var_a3 = 1;
            break;

        case ENUM_EVS_GAMESEL_1:
            var_a3 = 2;
            break;

        default:
            var_a3 = 0;
            break;
    }

    for (i = 0; i < var_a3; i++) {
        struct_evs_mem_data *ptr = &evs_mem_data[evs_select_name_no[i]];

        visible_fall_point[i] = (ptr->unk_00 & 2) ? 1 : 0;
    }
}
#endif

#if VERSION_US || VERSION_CN
void save_visible_fall_point_flag(void) {
    s32 i;
    s32 var_t0;

    switch (evs_gamesel) {
        case ENUM_EVS_GAMESEL_0:
        case ENUM_EVS_GAMESEL_3:
            var_t0 = 1;
            break;

        case ENUM_EVS_GAMESEL_1:
            var_t0 = 2;
            break;

        default:
            var_t0 = 0;
            break;
    }

    for (i = 0; i < var_t0; i++) {
        struct_evs_mem_data *temp_a1 = &evs_mem_data[evs_select_name_no[i]];

        temp_a1->unk_00 &= ~2;
        if (visible_fall_point[i] != 0) {
            temp_a1->unk_00 |= 2;
        }
    }
}
#endif

#if VERSION_US || VERSION_CN
void retryMenu_init(s32 arg0, s32 arg1) {
    struct_watchGame *watchGameP = watchGame;

    watchGameP->unk_348[arg0] = arg1;
    watchGameP->unk_358[arg0] = 0;
    watchGameP->unk_368[arg0] = -1;

    switch (watchGameP->unk_348[arg0]) {
        case 2:
        case 3:
        case 4:
        case 5:
            watchGameP->unk_358[arg0]++;
            break;
    }
}
#endif

#if VERSION_US || VERSION_CN
void func_8006417C(s32 arg0) {
    retryMenu_init(arg0, 0);
}
#endif

#if VERSION_US || VERSION_CN
s32 retryMenu_input(s32 arg0) {
    s32 direction = 0;
    SndIndex soundIndex = SND_INDEX_INVALID;
    s32 ret = -1;
    struct_watchGame *temp_s4 = watchGame;
    u16 curButton = joycur[main_joy[arg0]];
    u16 pressedButton = gControllerPressedButtons[main_joy[arg0]];
    s32 temp_v0;

    temp_s4->unk_358[arg0] = WrapI(0, _retryMenu_itemCount[temp_s4->unk_348[arg0]], temp_s4->unk_358[arg0]);

    if (curButton & U_JPAD) {
        direction--;
    }
    if (curButton & D_JPAD) {
        direction++;
    }

    temp_v0 = WrapI(0, _retryMenu_itemCount[temp_s4->unk_348[arg0]], temp_s4->unk_358[arg0] + direction);
    if (temp_v0 != temp_s4->unk_358[arg0]) {
        temp_s4->unk_358[arg0] = temp_v0;
        soundIndex = SND_INDEX_64;
    } else if (pressedButton & (A_BUTTON | START_BUTTON)) {
        ret = temp_s4->unk_368[arg0];
    }

    if (soundIndex > SND_INDEX_INVALID) {
        dm_snd_play_in_game(soundIndex);
    }

    return ret;
}
#endif

#if VERSION_US || VERSION_CN
void func_80064298(s32 arg0, Gfx **gfxP, s32 arg2) {
    struct_watchGame *watchGameP = watchGame;
    Gfx *gfx = *gfxP;

    if (watchGameP->unk_348[arg0] < 2) {
        if (watchGameP->unk_348[arg0] >= 0) {
            watchGameP->unk_368[arg0] =
                disp_pause_logo(&gfx, arg0, 0, (arg2 != 0) ? watchGameP->unk_358[arg0] : -1, watchGameP->unk_348[arg0]);
        }
    }

    *gfxP = gfx;
}
#endif

#if VERSION_US || VERSION_CN
void func_8006431C(s32 arg0, Gfx **gfxP) {
    struct_watchGame *watchGameP = watchGame;
    Gfx *gfx = *gfxP;

    if (watchGameP->unk_348[arg0] < 6) {
        if (watchGameP->unk_348[arg0] >= 2) {
            if ((evs_gamesel == ENUM_EVS_GAMESEL_1) && (evs_gamemode == ENUM_EVS_GAMEMODE_3)) {
                watchGameP->unk_368[arg0] =
                    disp_continue_logo_score(&gfx, arg0, watchGameP->unk_358[arg0], watchGameP->unk_348[arg0] - 2);
            } else {
                watchGameP->unk_368[arg0] =
                    disp_continue_logo(&gfx, arg0, watchGameP->unk_358[arg0], watchGameP->unk_348[arg0] - 2);
            }
        }
    }

    *gfxP = gfx;
}
#endif

#if VERSION_US || VERSION_CN
void set_bottom_up_virus(struct_game_state_data *arg0, GameMapCell *mapCells) {
    u8 sp20[GAME_MAP_COLUMNS];
    s32 col;
    s32 cellIndex;
    s32 var_s2;
    s32 cellEnd;

    for (col = 0; col < 1 * GAME_MAP_COLUMNS; col++) {
        sp20[col] = 0;
    }

    cellEnd = (GAME_MAP_ROWS - 1) * GAME_MAP_COLUMNS;
    cellIndex = (GAME_MAP_ROWS - 2) * GAME_MAP_COLUMNS;
    col = 0;

    for (; cellIndex < cellEnd; cellIndex++, col++) {
        if (mapCells[cellIndex].unk_4[0] == 0) {
            continue;
        }

        if (mapCells[cellIndex].unk_4[4] >= 0) {
            continue;
        }

        sp20[col] = 1;
    }

    var_s2 = 0;

    for (col = 0; col < GAME_MAP_COLUMNS; col++) {
        if (random(100) < 75) {
            sp20[col] = 1;
        }
        if (sp20[col] != 0) {
            var_s2 += 1;
        }
    }

    if (var_s2 == 0) {
        sp20[random(8)] = 1;
    }

    cellEnd += 1 * GAME_MAP_COLUMNS;
    col = 0;

    for (; cellIndex < cellEnd; cellIndex++, col++) {
        s32 sp28[4];
        s32 sp38[4];
        s32 sp48[4];
        s32 temp_v0_2;

        if (sp20[col] == 0) {
            continue;
        }

        sp28[0] = sp28[1] = sp28[2] = 0;

        sp38[0] = 1;
        sp38[1] = col > 1;

        sp48[0] = cellIndex - GAME_MAP_COLUMNS * 2;
        sp48[1] = cellIndex - 2;

        for (var_s2 = 0; var_s2 < 2; var_s2++) {
            if (sp38[var_s2] == 0) {
                continue;
            }

            if (mapCells[sp48[var_s2]].unk_4[0] != 0) {
                sp28[mapCells[sp48[var_s2]].unk_4[3]] += 1;
            }
        }

        if ((sp28[0] != 0) && (sp28[1] != 0) && (sp28[2] != 0)) {
            continue;
        }

        do {
            temp_v0_2 = random(3);
        } while (sp28[temp_v0_2] != 0);

        set_virus(mapCells, col, GAME_MAP_ROWS, temp_v0_2, virus_anime_table[temp_v0_2][arg0->unk_027]);
    }
}
#endif

#if VERSION_US || VERSION_CN
bool bottom_up_bottle_items(GameMapCell *mapCells) {
    s32 i;
    bool ret = false;
    s32 column;
    GameMapCell *cell;
    s32 var;

    for (i = 0; i < GAME_MAP_COLUMNS; i++) {
        if (mapCells[i].unk_4[0] != 0) {
            ret = true;
        }
    }

    var = (GAME_MAP_ROWS - 1) * GAME_MAP_COLUMNS;
    for (i = 0, cell = &mapCells[GAME_MAP_GET_INDEX(1, 0)]; i < var; i++, cell++) {
        mapCells[i] = *cell;
        mapCells[i].unk_1--;
    }

    var += GAME_MAP_COLUMNS;
    for (column = 0; i < var; i++, column++) {
        bzero(&mapCells[i], sizeof(GameMapCell));
        mapCells[i].unk_0 = column;
        mapCells[i].unk_1 = 0x11;
    }

    return ret;
}
#endif

#if VERSION_US || VERSION_CN
/**
 * Original name: _bonus_1884
 */
const s32 _bonus_1884[6] = { 0x1E, 0x78, 0x96, 0xB4, 0xD2, 0xF0 };

/**
 * Original name: add_taiQ_bonus_wait
 */
void add_taiQ_bonus_wait(struct_game_state_data *arg0) {
    struct_watchGame *watchGameP = watchGame;
    s32 var_a0;
    s32 i;

    if (evs_gamemode != ENUM_EVS_GAMEMODE_2) {
        return;
    }

    if (arg0->unk_03A < 2) {
        return;
    }

    watchGameP->unk_3C8 += (arg0->unk_03A - 1) * 0.25;
    watchGameP->unk_3C8 = MIN(watchGameP->unk_3C8, _big_virus_max_wait[arg0->unk_16C]);

    var_a0 = _bonus_1884[0] * (arg0->unk_037 + arg0->unk_03A);
    for (i = 1; i < arg0->unk_039; i++) {
        var_a0 += _bonus_1884[MIN(i, ARRAY_COUNTU(_bonus_1884) - 1)];
    }
    watchGameP->unk_410 += var_a0;
}
#endif

#if VERSION_US || VERSION_CN
bool func_80064848(void) {
    s32 i;

    for (i = 0; i < evs_playcnt; i++) {
        u32 temp_v0 = game_state_data[i].unk_020;

        if ((temp_v0 != 5) && (temp_v0 != 8) && (temp_v0 != 0xB)) {
            break;
        }
    }

    return (i ^ evs_playcnt) == 0;
}
#endif

#if VERSION_US || VERSION_CN
void dm_game_eep_write_callback(void *arg0) {
    struct_watchGame *watchGameP = arg0;
    RecordWritingMessage *recMessage = &watchGameP->recMessage;
    s32 temp_s0;

    RecWritingMsg_setStr(recMessage, _mesWriting_dmgamemain);
    temp_s0 = (SCREEN_WIDTH - msgWnd_getWidth(&recMessage->messageWnd)) / 2;
    RecWritingMsg_setPos(recMessage, temp_s0, SCREEN_HEIGHT - 0x20 - msgWnd_getHeight(&recMessage->messageWnd));
    RecWritingMsg_start(recMessage);
    setSleepTimer(500);
}
#endif

#if VERSION_US || VERSION_CN
void func_80064940(void *arg0 UNUSED) {
    struct_watchGame *watchGameP = watchGame;

    if (watchGameP->unk_3B0 != 0) {
        EepRomStatus status = EepRom_WriteAll(dm_game_eep_write_callback, watchGameP);

        watchGameP->unk_3B0 = 0;
        EepRom_DumpErrMes(status);
    }
}
#endif

#if VERSION_US || VERSION_CN
bool func_8006498C(s32 storyLevel, s32 storyNumber, s32 arg2) {
    bool var_v1 = false;

    if (storyNumber < 8) {
        var_v1 = true;
    } else if (storyNumber == 8) {
        if (storyLevel >= 3) {
            var_v1 = true;
        } else if ((storyLevel > 0) && (arg2 == 0)) {
            var_v1 = true;
        }
    }

    return var_v1;
}
#endif

#if VERSION_US || VERSION_CN
void dm_save_all(void) {
    struct_game_state_data *game_state_ptr = &game_state_data[0];
    struct_watchGame *watchGameP = watchGame;
    s32 i;
    s32 var_s1_2;

    if ((watchGameP->unk_000 != 0) || (watchGameP->unk_3B0 != 0)) {
        return;
    }

    switch (evs_gamesel) {
        case ENUM_EVS_GAMESEL_2:
            if (evs_story_flg != 0) {
                s32 temp_arg5 = evs_story_no;

                if (game_state_ptr->unk_020 == 5) {
                    temp_arg5++;
                }

                dm_story_sort_set(evs_select_name_no[0], (s32)story_proc_no >= STORY_PROC_NO_12, evs_story_level,
                                  game_state_ptr->unk_000, evs_game_time, temp_arg5, evs_one_game_flg);
                watchGameP->unk_3B0 = 1;
            }
            break;

        case ENUM_EVS_GAMESEL_1:
            for (i = 0; i < 2; i++) {
                switch (evs_gamemode) {
                    case ENUM_EVS_GAMEMODE_0:
                        dm_vsman_set(evs_select_name_no[i], watchGameP->unk_8AC[i], watchGameP->unk_8AC[i ^ 1]);
                        break;
                    case ENUM_EVS_GAMEMODE_1:
                        dm_vm_fl_set(evs_select_name_no[i], watchGameP->unk_8AC[i], watchGameP->unk_8AC[i ^ 1]);
                        break;
                    case ENUM_EVS_GAMEMODE_3:
                        dm_vm_ta_set(evs_select_name_no[i], watchGameP->unk_8AC[i], watchGameP->unk_8AC[i ^ 1]);
                        break;

                    default:
                        break;
                }
            }

            watchGameP->unk_3B0 = 1;
            watchGameP->unk_8AC[1] = 0;
            watchGameP->unk_8AC[0] = 0;
            break;

        case ENUM_EVS_GAMESEL_3:
            if (evs_story_flg == 0) {
                switch (evs_gamemode) {
                    case ENUM_EVS_GAMEMODE_0:
                        dm_vscom_set(evs_select_name_no[0], watchGameP->unk_8AC[0], watchGameP->unk_8AC[1]);
                        break;

                    case ENUM_EVS_GAMEMODE_1:
                        dm_vc_fl_set(evs_select_name_no[0], watchGameP->unk_8AC[0], watchGameP->unk_8AC[1]);
                        break;

                    default:
                        break;
                }
                watchGameP->unk_3B0 = 1;
                watchGameP->unk_8AC[1] = 0;
                watchGameP->unk_8AC[0] = 0;
            } else {
                struct_evs_mem_data *temp_a0 = &evs_mem_data[evs_select_name_no[0]];
                struct_evs_mem_data_unk_B4 *temp = &temp_a0->unk_B4;
                s32 var_s0_2 = evs_story_no;
                s32 temp_s1 = (s32)story_proc_no >= STORY_PROC_NO_12;

                temp->unk_02 = CLAMP(var_s0_2 - 1, 0, 7);

                if (game_state_ptr->unk_020 == 5) {
                    if ((var_s0_2 == 9) && (game_state_ptr->unk_004 == 0)) {
                        evs_secret_flg[temp_s1] = 1;
                    }
                    if (func_8006498C(evs_story_level, var_s0_2, game_state_ptr->unk_004)) {
                        var_s0_2++;
                    } else if (var_s0_2 == 9) {
                        var_s0_2++;
                    }
                }

                dm_story_sort_set(evs_select_name_no[0], temp_s1, evs_story_level, game_state_ptr->unk_000,
                                  evs_game_time, var_s0_2, evs_one_game_flg);

                watchGameP->unk_3B0 = 1;
            }
            break;

        case ENUM_EVS_GAMESEL_0:
            switch (evs_gamemode) {
                case ENUM_EVS_GAMEMODE_0:
                    var_s1_2 = game_state_ptr->unk_026;
                    if (game_state_ptr->unk_020 == 5) {
                        if (var_s1_2 >= 0x15) {
                            evs_level_21 = 1;
                        }
                        if (var_s1_2 < 0x63) {
                            var_s1_2++;
                        }
                    }

                    dm_level_sort_set(evs_select_name_no[0], game_state_ptr->unk_02C, game_state_ptr->unk_000,
                                      var_s1_2);

                    evs_mem_data[evs_select_name_no[0]].unk_B4.unk_04 = MIN(0x15, var_s1_2);
                    break;

                case ENUM_EVS_GAMEMODE_2:
                    dm_taiQ_sort_set(evs_select_name_no[0], game_state_ptr->unk_16C, game_state_ptr->unk_000,
                                     evs_game_time);
                    break;

                case ENUM_EVS_GAMEMODE_3:
                    dm_timeAt_sort_set(evs_select_name_no[0], game_state_ptr->unk_16C, game_state_ptr->unk_000,
                                       evs_game_time, game_state_ptr->unk_170);
                    break;

                default:
                    break;
            }
            watchGameP->unk_3B0 = 1;
            break;

        default:
            break;
    }

    func_80040B10(func_80064940, NULL);
}
#endif

#if VERSION_US || VERSION_CN
void dm_query_pause_player(struct_game_state_data *arg0) {
    struct_watchGame *watchGameP = watchGame;
    u16 btn = gControllerPressedButtons[main_joy[arg0->unk_04B]];

    if (watchGameP->unk_9C4 >= 0) {
        return;
    }

    switch (arg0->unk_020) {
        case 0x1:
        case 0xD:
            break;

        case 0x8:
            if (watchGameP->unk_000 == 0) {
                return;
            }

            if (arg0->unk_014 != GAMESTATEDATA_UNK_014_11) {
                return;
            }
            break;

        default:
            return;
    }

    if ((arg0->unk_014 != GAMESTATEDATA_UNK_014_2) && (arg0->unk_04C == 0)) {
        if (watchGameP->unk_000 == 0) {
            if (btn & START_BUTTON) {
                watchGameP->unk_9C0 = 1;
                watchGameP->unk_9C4 = arg0->unk_04B;
            }
        } else if (btn & ANY_BUTTON) {
            watchGameP->unk_9C4 = arg0->unk_04B;
        }
    }
}
#endif

#if VERSION_US || VERSION_CN
// TODO: enum return type?
s32 dm_game_main_cnt_1P(struct_game_state_data *gameStateData, GameMapCell *mapCells, s32 arg2) {
    struct_watchGame *watchGameP = watchGame;
    dm_calc_erase_score_pos_arg2 sp28;
    s32 var_s1;
    u8 *var_t2;
    s32 var_s2;
    int var_s0;

    dm_query_pause_player(gameStateData);
    animeState_update(&gameStateData->unk_094);
    func_80062EC0(&watchGameP->unk_0B8[arg2]);
    if ((evs_gamemode == ENUM_EVS_GAMEMODE_3) && (evs_game_time >= 10800) && (gameStateData->unk_020 == 1)) {
        return -1;
    }

    switch (gameStateData->unk_00C) {
        case GAMESTATEDATA_UNK_00C_1:
            dm_set_virus(gameStateData, mapCells, virus_map_data[arg2], virus_map_disp_order[arg2]);
            return 3;

        case GAMESTATEDATA_UNK_00C_2:
            return 3;

        case GAMESTATEDATA_UNK_00C_3:
            gameStateData->unk_02F++;

            if (gameStateData->unk_02F == FlyingCnt[gameStateData->unk_02C]) {
                func_80060FA0(&gameStateData->unk_178, (CapsMagazine[gameStateData->unk_033] >> 4) % 3,
                              CapsMagazine[gameStateData->unk_033] % 3);
                gameStateData->unk_00C = GAMESTATEDATA_UNK_00C_4;
                gameStateData->unk_02F = 0x1E;
                dm_capsel_down(gameStateData, mapCells);
            }
            break;

        case GAMESTATEDATA_UNK_00C_5:
            if (dm_check_game_over(gameStateData, mapCells)) {
                for (var_s0 = 0; var_s0 < 3; var_s0++) {
                    if (watchGameP->animeStates[var_s0].animeSeq.unk_10 != 4) {
                        animeState_set(&watchGameP->animeStates[var_s0], 3);
                    }
                }

                if (evs_gamemode == ENUM_EVS_GAMEMODE_2) {
                    watchGameP->unk_410 = 0;
                }
                return -1;
            }

            if (dm_h_erase_chack(mapCells) || dm_w_erase_chack(mapCells)) {
                gameStateData->unk_00C = GAMESTATEDATA_UNK_00C_6;
                gameStateData->unk_02F = 0;
            } else {
                gameStateData->unk_00C = GAMESTATEDATA_UNK_00C_9;
            }
            break;

        case GAMESTATEDATA_UNK_00C_6:
            gameStateData->unk_02F++;

            if (gameStateData->unk_02F >= 0x12) {
                gameStateData->unk_02F = 0;
                gameStateData->unk_00C = GAMESTATEDATA_UNK_00C_7;
                dm_h_erase_chack_set(gameStateData, mapCells);
                dm_w_erase_chack_set(gameStateData, mapCells);
                dm_h_ball_chack(mapCells);
                dm_w_ball_chack(mapCells);

                var_s0 = gameStateData->unk_025;
                var_s0 -= get_virus_color_count(mapCells, watchGameP->unk_418, &watchGameP->unk_418[1],
                                                &watchGameP->unk_418[2]);
                gameStateData->unk_025 -= var_s0;

                gameStateData->unk_170 += var_s0;

                for (var_s0 = 0; var_s0 < 3; var_s0++) {
                    if (watchGameP->unk_418[var_s0] == 0) {
                        if (watchGameP->unk_400[var_s0] == 0) {
                            watchGameP->unk_400[var_s0] = 1;
                            animeState_set(&watchGameP->animeStates[var_s0], 4);
                            animeSmog_start(&watchGameP->animeSmogs[var_s0]);
                            if (gameStateData->unk_025 != 0) {
                                dm_snd_play_in_game(SND_INDEX_74);
                                dm_snd_play_in_game(SND_INDEX_57);
                            }
                        }
                    } else {
                        if (gameStateData->unk_03C[3] & (0x10 << var_s0)) {
                            if (watchGameP->unk_410 == 0) {
                                animeState_set(&watchGameP->animeStates[var_s0], 2);
                                dm_snd_play_in_game(SND_INDEX_74);
                            }
                        }
                    }
                }

                gameStateData->unk_03C[3] &= 0xF;

                dm_calc_erase_score_pos(gameStateData, mapCells, &sp28);
                scoreNums_set(&watchGameP->unk_0B8[arg2], dm_make_score(gameStateData), gameStateData->unk_037,
                              gameStateData->unk_006 + gameStateData->unk_00A / 2 + sp28.unk_0,
                              gameStateData->unk_008 + gameStateData->unk_00A / 2 + sp28.unk_4);

                if ((gameStateData->unk_025 == 0) && (evs_gamemode != ENUM_EVS_GAMEMODE_2)) {
                    gameStateData->unk_014 = GAMESTATEDATA_UNK_014_3;
                    gameStateData->unk_00C = GAMESTATEDATA_UNK_00C_A;
                    if (gameStateData->unk_03B < gameStateData->unk_03A) {
                        gameStateData->unk_03B = gameStateData->unk_03A;
                    }
                    return 6;
                }

                if ((gameStateData->unk_025 < 4U) && (evs_gamemode != ENUM_EVS_GAMEMODE_2)) {
                    if (watchGameP->unk_3C0 == 0) {
                        watchGameP->unk_3C0 = 1;
                        dm_snd_play_in_game(SND_INDEX_80);
                    }
                    if (watchGameP->unk_3B4 == 0) {
                        watchGameP->unk_3B4 = 1;
                        watchGameP->unk_3B8 = 1;
                    }
                }

                gameStateData->unk_039 += 1;
                if (gameStateData->unk_03A < 2) {
                    if (gameStateData->unk_03C[3] & 8) {
                        gameStateData->unk_03C[3] &= (u8)~0x8;
                        dm_snd_play_in_game(SND_INDEX_56);
                    } else {
                        dm_snd_play_in_game(SND_INDEX_61);
                    }
                } else {
                    if (gameStateData->unk_03C[3] & 8) {
                        gameStateData->unk_03C[3] &= (u8)~0x8;
                    }

                    var_s0 = MIN(2, gameStateData->unk_03A - 2);
                    dm_snd_play_in_game(_charSE_tbl[gameStateData->unk_090] + var_s0);
                }
            }
            break;

        case GAMESTATEDATA_UNK_00C_7:
            dm_capsel_erase_anime(gameStateData, mapCells);
            break;

        case GAMESTATEDATA_UNK_00C_8:
            go_down(gameStateData, mapCells, 0xE);
            break;

        case GAMESTATEDATA_UNK_00C_9:
            add_taiQ_bonus_wait(gameStateData);

            if ((watchGameP->unk_9BC != 0) && (watchGameP->unk_410 == 0)) {
                gameStateData->unk_168 = 0;
                gameStateData->unk_00C = GAMESTATEDATA_UNK_00C_C;
                set_bottom_up_virus(gameStateData, mapCells);
                dm_snd_play_in_game(SND_INDEX_101);
            } else {
                if (gameStateData->unk_039 > 1) {
                    gameStateData->unk_174 = MIN(0x63, gameStateData->unk_174 + gameStateData->unk_039 - 1);
                }

                dm_warning_h_line(gameStateData, mapCells);
                dm_set_capsel(gameStateData);
                dm_capsel_speed_up(gameStateData);
                dm_attack_se(gameStateData, arg2);
                animeState_set(&gameStateData->unk_094, 1);

                if ((gameStateData->unk_04C == 1) ||
                    (((gameStateData->unk_04C != 1) && (arg2 == 0)) && (aiDebugP1 >= 0))) {
                    aifMakeFlagSet(gameStateData);
                }

                if (gameStateData->unk_03B < gameStateData->unk_03A) {
                    gameStateData->unk_03B = gameStateData->unk_03A;
                }

                gameStateData->unk_00C = GAMESTATEDATA_UNK_00C_3;
                gameStateData->unk_02F = 0;
                gameStateData->unk_031 = 0;
                gameStateData->unk_03A = 0;
                gameStateData->unk_039 = 0;
                gameStateData->unk_037 = 0;
                gameStateData->unk_038 = 0;

                for (var_s0 = 0; var_s0 < 4; var_s0++) {
                    gameStateData->unk_03C[var_s0] = 0;
                }
            }
            break;

        case GAMESTATEDATA_UNK_00C_C:
            gameStateData->unk_168++;
            if (gameStateData->unk_168 >= gameStateData->unk_00A) {
                gameStateData->unk_168 = 0;
                watchGameP->unk_9BC = 0;

                watchGameP->unk_3C8 = MAX(_big_virus_min_wait[gameStateData->unk_16C], watchGameP->unk_3C8 - 0.5);

                gameStateData->unk_00C = GAMESTATEDATA_UNK_00C_8;
                if (bottom_up_bottle_items(mapCells)) {
                    return -1;
                }

                gameStateData->unk_025 = get_virus_color_count(mapCells, watchGameP->unk_418, &watchGameP->unk_418[1],
                                                               &watchGameP->unk_418[2]);

                for (var_s0 = 0; var_s0 < 3; var_s0++) {
                    if ((watchGameP->unk_418[var_s0] != 0) && (watchGameP->unk_400[var_s0] != 0)) {
                        animeState_set(&watchGameP->animeStates[var_s0], 0);
                        animeSmog_start(&watchGameP->animeSmogs[var_s0]);
                        watchGameP->unk_400[var_s0] = 0;
                    } else if (watchGameP->animeStates[var_s0].animeSeq.unk_10 == 3) {
                        animeState_set(&watchGameP->animeStates[var_s0], 0);
                    }
                }
            }
            break;

        case GAMESTATEDATA_UNK_00C_1A:
        case GAMESTATEDATA_UNK_00C_1C:
            if (gameStateData->unk_00C == GAMESTATEDATA_UNK_00C_1A) {
                if (func_80062B18(arg2)) {
                    break;
                }
            } else {
                if (func_80062AFC(arg2)) {
                    break;
                }
            }

            if (gControllerPressedButtons[main_joy[arg2]] & ANY_BUTTON) {
                switch (gameStateData->unk_00C) {
                    case GAMESTATEDATA_UNK_00C_1A:
                        gameStateData->unk_014 = GAMESTATEDATA_UNK_014_14;
                        gameStateData->unk_00C = GAMESTATEDATA_UNK_00C_1B;
                        break;

                    case GAMESTATEDATA_UNK_00C_1C:
                        gameStateData->unk_014 = GAMESTATEDATA_UNK_014_16;
                        gameStateData->unk_00C = GAMESTATEDATA_UNK_00C_1D;
                        break;

                    default:
                        break;
                }
            }
            break;

        case GAMESTATEDATA_UNK_00C_1B:
        case GAMESTATEDATA_UNK_00C_1D:
            if (gControllerPressedButtons[main_joy[arg2]] & ANY_BUTTON) {
                func_80062DA4(&watchGameP->unk_9D0[arg2]);
            }

            timeAttackResult_update(&watchGameP->unk_9D0[arg2], 1);

            func_80060270(gameStateData, watchGameP->unk_9D0[arg2].unk_24);
            watchGameP->unk_9D0[arg2].unk_24 = 0;
            if (func_80062BC4(&watchGameP->unk_9D0[arg2])) {
                switch (gameStateData->unk_00C) {
                    case GAMESTATEDATA_UNK_00C_1B:
                        gameStateData->unk_014 = GAMESTATEDATA_UNK_014_3;
                        gameStateData->unk_00C = GAMESTATEDATA_UNK_00C_A;
                        break;

                    case GAMESTATEDATA_UNK_00C_1D:
                        gameStateData->unk_014 = GAMESTATEDATA_UNK_014_4;
                        gameStateData->unk_00C = GAMESTATEDATA_UNK_00C_B;
                        break;

                    default:
                        break;
                }
            }
            break;

        case GAMESTATEDATA_UNK_00C_A:
        case GAMESTATEDATA_UNK_00C_B:
            if (gameStateData->unk_00C == GAMESTATEDATA_UNK_00C_A) {
                if (func_80062B18(arg2)) {
                    break;
                }
            } else {
                if (func_80062AFC(arg2)) {
                    break;
                }
            }

            var_s0 = (Z_TRIG | L_JPAD | L_TRIG | R_TRIG);
            if ((watchGameP->unk_AA8 < 0) && CHECK_FLAG_ALL(gControllerHoldButtons[main_joy[0]], var_s0)) {
                switch (evs_gamemode) {
                    case ENUM_EVS_GAMEMODE_0:
                        var_s1 = 0;
                        var_s2 = gameStateData->unk_026;
                        break;

                    case ENUM_EVS_GAMEMODE_3:
                        var_s1 = 1;
                        var_s2 = gameStateData->unk_16C;
                        break;

                    case ENUM_EVS_GAMEMODE_2:
                        var_s1 = 2;
                        var_s2 = gameStateData->unk_16C;
                        break;

                    default:
                        break;
                }

                if (evs_select_name_no[0] == 8) {
                    var_t2 = D_800A7360;
                } else {
                    var_t2 = evs_mem_data[evs_select_name_no[0]].unk_01;
                }

                if (watchGameP->unk_AAC[0] == 0) {
                    func_8007E760(watchGameP->unk_AAC, var_s1, var_s2, gameStateData->unk_02C,
                                  gameStateData->unk_000 / 10, evs_game_time / 6, var_t2);
                    watchGameP->unk_AAC[ARRAY_COUNT(watchGameP->unk_AAC) - 2] = 0x7E;
                    watchGameP->unk_AAC[ARRAY_COUNT(watchGameP->unk_AAC) - 1] = 0x7A;
                }
                msgWnd_clear(&watchGameP->unk_A28);
                msgWnd_addStr(&watchGameP->unk_A28, _mesPassword);
                msgWnd_addStr(&watchGameP->unk_A28, watchGameP->unk_AAC);
                msgWnd_skip(&watchGameP->unk_A28);
                watchGameP->unk_AA8 = -watchGameP->unk_AA8;
            } else {
                if ((gControllerPressedButtons[main_joy[0]] != 0) && (watchGameP->unk_AA8 > 0)) {
                    watchGameP->unk_AA8 = -watchGameP->unk_AA8;
                }

                switch (retryMenu_input(arg2)) {
                    case 0:
                        func_80063378();
                        dm_snd_play_in_game(SND_INDEX_62);
                        return 9;

                    case 1:
                        func_800633C0();
                        dm_snd_play_in_game(SND_INDEX_62);
                        return 1;

                    case 0x2: /* switch 3 */
                        func_800633C0();
                        if (gameStateData->unk_004 < 0x3E7U) {
                            gameStateData->unk_004++;
                        }

                        if ((gameStateData->unk_026 >= 0x16U) && (watchGameP->unk_378 > 0)) {
                            watchGameP->unk_378--;
                            dm_snd_play_in_game(SND_INDEX_78);
                        } else {
                            dm_snd_play_in_game(SND_INDEX_62);
                        }
                        return 2;

                    case 0x3: /* switch 3 */
                        dm_snd_play_in_game(SND_INDEX_62);
                        return 0x64;
                }
            }
            break;

        case GAMESTATEDATA_UNK_00C_18:
            switch (retryMenu_input(arg2)) {
                case 0:
                    if (watchGameP->unk_9C4 < 0) {
                        watchGameP->unk_9C4 = arg2;
                    }
                    dm_snd_play_in_game(SND_INDEX_62);
                    break;

                case 1:
                    if (gameStateData->unk_004 < 0x3E7U) {
                        gameStateData->unk_004 = gameStateData->unk_004 + 1;
                    }

                    if ((gameStateData->unk_026 >= 0x16U) && (watchGameP->unk_378 > 0)) {
                        watchGameP->unk_378--;
                        dm_snd_play_in_game(SND_INDEX_78);
                    } else {
                        dm_snd_play_in_game(SND_INDEX_62);
                    }
                    return 2;

                case 2:
                    dm_snd_play_in_game(SND_INDEX_62);
                    return 0x64;
            }
            break;

        default:
            break;
    }

    return 0;
}
#endif

#if VERSION_US || VERSION_CN
// return enum?
s32 dm_game_main_cnt(struct_game_state_data *gameStateDataRef, GameMapCell *mapCells, s32 index) {
    struct_watchGame *temp_s1 = watchGame;
    dm_calc_erase_score_pos_arg2 sp20;
    s32 button = gControllerPressedButtons[main_joy[index]];
    s32 i;
    s32 j;
    bool var_s6;

    dm_query_pause_player(gameStateDataRef);

    animeState_update(&gameStateDataRef->unk_094);

    func_80062EC0(&temp_s1->unk_0B8[index]);

    if ((gameStateDataRef->unk_020 != 1) && (gameStateDataRef->unk_020 != 0xD)) {
        dm_black_up(gameStateDataRef, mapCells);
    }

    if ((evs_gamemode == ENUM_EVS_GAMEMODE_3) && (evs_game_time >= 10800) && (gameStateDataRef->unk_020 == 1)) {
        return -1;
    }

    switch (gameStateDataRef->unk_00C) {
        case GAMESTATEDATA_UNK_00C_1:
            dm_set_virus(gameStateDataRef, mapCells, virus_map_data[index], virus_map_disp_order[index]);
            return 3;

        case GAMESTATEDATA_UNK_00C_2:
            return 3;

        case GAMESTATEDATA_UNK_00C_5:
            if (dm_check_game_over(gameStateDataRef, mapCells)) {
                return -1;
            }

            if (dm_h_erase_chack(mapCells) || dm_w_erase_chack(mapCells)) {
                if (gameStateDataRef->unk_049 == 0) {
                    gameStateDataRef->unk_00C = GAMESTATEDATA_UNK_00C_6;
                } else {
                    gameStateDataRef->unk_00C = GAMESTATEDATA_UNK_00C_15;
                }

                gameStateDataRef->unk_02F = 0;
            } else if (gameStateDataRef->unk_049 == 0) {
                gameStateDataRef->unk_00C = GAMESTATEDATA_UNK_00C_9;
            } else {
                gameStateDataRef->unk_00C = GAMESTATEDATA_UNK_00C_16;
            }
            break;

        case GAMESTATEDATA_UNK_00C_6:
            gameStateDataRef->unk_02F++;
            if (gameStateDataRef->unk_02F >= 0x12) {
                s32 temp_s4_2;

                gameStateDataRef->unk_00C = GAMESTATEDATA_UNK_00C_7;
                gameStateDataRef->unk_02F = 0;
                dm_h_erase_chack_set(gameStateDataRef, mapCells);
                dm_w_erase_chack_set(gameStateDataRef, mapCells);
                dm_h_ball_chack(mapCells);
                dm_w_ball_chack(mapCells);

                temp_s4_2 = gameStateDataRef->unk_025;
                temp_s4_2 -= func_8006121C(gameStateDataRef, mapCells, 1);
                gameStateDataRef->unk_170 += temp_s4_2;

                dm_calc_erase_score_pos(gameStateDataRef, mapCells, &sp20);

                scoreNums_set(&temp_s1->unk_0B8[index], dm_make_score(gameStateDataRef), gameStateDataRef->unk_037,
                              gameStateDataRef->unk_006 + gameStateDataRef->unk_00A / 2 + sp20.unk_0,
                              gameStateDataRef->unk_008 + gameStateDataRef->unk_00A / 2 + sp20.unk_4);

                if (gameStateDataRef->unk_025 == 0) {
                    if (gameStateDataRef->unk_03B < gameStateDataRef->unk_03A) {
                        gameStateDataRef->unk_03B = gameStateDataRef->unk_03A;
                    }
                    return 6;
                }
                if (temp_s1->unk_3BC >= gameStateDataRef->unk_025) {
                    if (temp_s1->unk_3C0 == 0) {
                        temp_s1->unk_3C0 = 1;
                        dm_snd_play_in_game(SND_INDEX_80);
                    }
                    if (temp_s1->unk_3B4 == 0) {
                        temp_s1->unk_3B4 = 1;
                        temp_s1->unk_3B8 = 1;
                    }
                }
                gameStateDataRef->unk_039 += 1;

                switch (evs_gamesel) {
                    case ENUM_EVS_GAMESEL_1:
                    case ENUM_EVS_GAMESEL_3:
                    case ENUM_EVS_GAMESEL_5:
                        if (gameStateDataRef->unk_03A < 2) {
                            if (gameStateDataRef->unk_03C[3] & 8) {
                                gameStateDataRef->unk_03C[3] &= ~8;
                                if ((evs_gamemode == ENUM_EVS_GAMEMODE_1) && (temp_s4_2 != 0)) {
                                    dm_snd_play_in_game(SND_INDEX_102);
                                } else {
                                    dm_snd_play_in_game(SND_INDEX_56);
                                }
                            } else {
                                dm_snd_play_in_game(SND_INDEX_61);
                            }
                        } else {
                            s32 temp_v0_3 = gameStateDataRef->unk_03A - 2;

                            if (temp_v0_3 <= 2) {
                                j = temp_v0_3;
                            } else {
                                j = 2;
                            }

                            dm_snd_play_in_game(_charSE_tbl[gameStateDataRef->unk_090] + j);

                            if (gameStateDataRef->unk_03C[3] & 8) {
                                gameStateDataRef->unk_03C[3] &= ~8;
                            }
                        }
                        break;

                    case ENUM_EVS_GAMESEL_2:
                    case ENUM_EVS_GAMESEL_6:
                        if (gameStateDataRef->unk_03C[3] & 8) {
                            gameStateDataRef->unk_03C[3] &= ~8;
                            if ((evs_gamemode == ENUM_EVS_GAMEMODE_1) && (temp_s4_2 != 0)) {
                                dm_snd_play_in_game(SND_INDEX_102);
                            } else {
                                dm_snd_play_in_game(SND_INDEX_56);
                            }
                        } else {
                            dm_snd_play_in_game(SND_INDEX_61);
                        }
                        break;

                    default:
                        break;
                }
            }
            break;

        case GAMESTATEDATA_UNK_00C_7:
            dm_capsel_erase_anime(gameStateDataRef, mapCells);
            break;

        case GAMESTATEDATA_UNK_00C_8:
            go_down(gameStateDataRef, mapCells, 0xE);
            break;

        case GAMESTATEDATA_UNK_00C_9:
            var_s6 = true;

            if (gameStateDataRef->unk_039 > 1) {
                gameStateDataRef->unk_174 = MIN(0x63, gameStateDataRef->unk_174 + gameStateDataRef->unk_039 - 1);
            }

            dm_attack_se(gameStateDataRef, index);
            dm_warning_h_line(gameStateDataRef, mapCells);
            switch (evs_gamesel) {
                case ENUM_EVS_GAMESEL_1:
                case ENUM_EVS_GAMESEL_3:
                case ENUM_EVS_GAMESEL_5:
                    if (evs_gamemode != ENUM_EVS_GAMEMODE_3) {
                        i = dm_set_attack_2p(gameStateDataRef);
                        if (i != 0) {
                            animeState_set(&gameStateDataRef->unk_094, 1);
                        }

                        if (dm_broken_set(gameStateDataRef, mapCells)) {
                            animeState_set(&gameStateDataRef->unk_094, 2);
                            var_s6 = false;
                            dm_snd_play_in_game(_charSE_tbl[gameStateDataRef->unk_090] + 3);
                            gameStateDataRef->unk_00C = GAMESTATEDATA_UNK_00C_8;
                            if (gameStateDataRef->unk_292 & 1) {
                                gameStateDataRef->unk_292 |= 2;
                            } else {
                                gameStateDataRef->unk_292 |= 1;
                            }
                        }
                    }
                    break;

                case ENUM_EVS_GAMESEL_2:
                case ENUM_EVS_GAMESEL_6:
                    i = dm_set_attack_4p(gameStateDataRef);
                    if (i != 0) {
                        animeState_set(&gameStateDataRef->unk_094, 1);
                    }

                    if (dm_broken_set(gameStateDataRef, mapCells)) {
                        animeState_set(&gameStateDataRef->unk_094, 2);
                        var_s6 = false;
                        gameStateDataRef->unk_00C = GAMESTATEDATA_UNK_00C_8;
                        if (gameStateDataRef->unk_292 & 1) {
                            gameStateDataRef->unk_292 |= 2;
                        } else {
                            gameStateDataRef->unk_292 |= 1;
                        }
                    }
                    break;

                default:
                    break;
            }

            if (var_s6) {
                dm_set_capsel(gameStateDataRef);
                dm_capsel_speed_up(gameStateDataRef);
                if (gameStateDataRef->unk_03B < gameStateDataRef->unk_03A) {
                    gameStateDataRef->unk_03B = gameStateDataRef->unk_03A;
                }

                gameStateDataRef->unk_03A = 0;
                gameStateDataRef->unk_039 = 0;
                gameStateDataRef->unk_037 = 0;
                gameStateDataRef->unk_038 = 0;

                for (i = 0; i < ARRAY_COUNT(gameStateDataRef->unk_03C); i++) {
                    gameStateDataRef->unk_03C[i] = 0;
                }

                gameStateDataRef->unk_00C = GAMESTATEDATA_UNK_00C_4;
                if ((gameStateDataRef->unk_04C == 1) ||
                    (((gameStateDataRef->unk_04C != 1) && (index == 0)) && (aiDebugP1 >= 0))) {
                    aifMakeFlagSet(gameStateDataRef);
                }
            }
            break;

        case GAMESTATEDATA_UNK_00C_1A:
            func_80062B18(index);
            break;

        case GAMESTATEDATA_UNK_00C_1C:
            func_80062AFC(index);
            break;

        case GAMESTATEDATA_UNK_00C_1E:
            func_80062B34(index);
            break;

        case GAMESTATEDATA_UNK_00C_1B:
        case GAMESTATEDATA_UNK_00C_1D:
        case GAMESTATEDATA_UNK_00C_1F:
            if (gControllerPressedButtons[main_joy[index]] & ANY_BUTTON) {
                func_80062DA4(&temp_s1->unk_9D0[index]);
            }

            timeAttackResult_update(&temp_s1->unk_9D0[index], 1);
            func_80060270(gameStateDataRef, temp_s1->unk_9D0[index].unk_24);
            temp_s1->unk_9D0[index].unk_24 = 0;
            break;

        case GAMESTATEDATA_UNK_00C_E:
        case GAMESTATEDATA_UNK_00C_10:
        case GAMESTATEDATA_UNK_00C_12:
            if (gameStateDataRef->unk_00C == GAMESTATEDATA_UNK_00C_E) {
                if (func_80062A8C(index) != 0) {
                    break;
                }
            } else if (gameStateDataRef->unk_00C == GAMESTATEDATA_UNK_00C_10) {
                if (func_80062AA8(index) != 0) {
                    break;
                }
            } else if (gameStateDataRef->unk_00C == GAMESTATEDATA_UNK_00C_12) {
                if (func_80062AC4(index) != 0) {
                    break;
                }
            }

            switch (retryMenu_input(index)) {
                case 0:
                    func_80063378();
                    dm_snd_play_in_game(SND_INDEX_62);
                    return 9;

                case 1:
                    func_800633C0();
                    dm_snd_play_in_game(SND_INDEX_62);
                    return 0x64;

                case 2:
                    func_800633C0();
                    if (gameStateDataRef->unk_004 < 999) {
                        gameStateDataRef->unk_004++;
                    }
                    dm_snd_play_in_game(SND_INDEX_62);
                    return 2;

                case 3:
                    dm_snd_play_in_game(SND_INDEX_62);
                    return -2;
            }
            break;

        case GAMESTATEDATA_UNK_00C_D:
            func_80062A8C(index);
            break;

        case GAMESTATEDATA_UNK_00C_F:
            func_80062AA8(index);
            break;

        case GAMESTATEDATA_UNK_00C_11:
            func_80062AC4(index);
            break;

        case GAMESTATEDATA_UNK_00C_13:
            if ((button & START_BUTTON) && (temp_s1->unk_000 == 0)) {
                return 7;
            }
            break;

        case GAMESTATEDATA_UNK_00C_14:
            gameStateDataRef->unk_049 = 1;
            clear_map_all(mapCells);
            gameStateDataRef->unk_025 = 0;
            gameStateDataRef->unk_024 = 0;
            gameStateDataRef->unk_02B = 0xC;
            gameStateDataRef->unk_044 = 0;
            gameStateDataRef->unk_02D = GameSpeed[gameStateDataRef->unk_02C];
            gameStateDataRef->unk_031 = 0;
            gameStateDataRef->unk_030 = 1;
            gameStateDataRef->unk_032 = 1;
            gameStateDataRef->unk_02F = 0;
            gameStateDataRef->unk_02E = 0;
            dm_set_capsel(gameStateDataRef);
            gameStateDataRef->unk_035 = 0;
            gameStateDataRef->unk_036 = 0;
            gameStateDataRef->unk_037 = 0;
            gameStateDataRef->unk_038 = 0;
            gameStateDataRef->unk_03A = 0;
            gameStateDataRef->unk_039 = 0;

            for (i = 0; i < ARRAY_COUNT(gameStateDataRef->unk_03C); i++) {
                gameStateDataRef->unk_03C[i] = 0;
            }

            for (i = 0; i < ARRAY_COUNT(gameStateDataRef->unk_050); i++) {
                gameStateDataRef->unk_050[i].unk_0 = 0;
                gameStateDataRef->unk_050[i].unk_2 = 0;
            }

            gameStateDataRef->unk_00C = GAMESTATEDATA_UNK_00C_1;
            gameStateDataRef->unk_014 = GAMESTATEDATA_UNK_014_2;

            for (i = 0; i < ARRAY_COUNTU(virus_map_disp_order[index]); i++) {
                virus_map_disp_order[index][i] &= ~0x80;
            }

            for (i = 0; i < gameStateDataRef->unk_164; i++) {
                gameStateDataRef->unk_0D4[i][2] = gameStateDataRef->unk_140.unk_00[i];
            }
            break;

        case GAMESTATEDATA_UNK_00C_15:
            gameStateDataRef->unk_02F++;
            if (gameStateDataRef->unk_02F >= 0x12) {
                gameStateDataRef->unk_02F = 0;
                gameStateDataRef->unk_00C = GAMESTATEDATA_UNK_00C_7;
                dm_h_erase_chack_set(gameStateDataRef, mapCells);
                dm_w_erase_chack_set(gameStateDataRef, mapCells);
                dm_h_ball_chack(mapCells);
                dm_w_ball_chack(mapCells);

                gameStateDataRef->unk_039++;
                func_8006121C(gameStateDataRef, mapCells, 1);

                if (gameStateDataRef->unk_03C[3] & 8) {
                    gameStateDataRef->unk_03C[3] &= ~8;
                    dm_snd_play_in_game(SND_INDEX_56);
                } else {
                    dm_snd_play_in_game(SND_INDEX_61);
                }
            }
            break;

        case GAMESTATEDATA_UNK_00C_16:
            dm_warning_h_line(gameStateDataRef, mapCells);

            var_s6 = true;
            if (gameStateDataRef->unk_04A != 0) {
                dm_attack_se(gameStateDataRef, index);
                dm_set_attack_4p(gameStateDataRef);
                animeState_set(&gameStateDataRef->unk_094, 1);
                if (dm_broken_set(gameStateDataRef, mapCells)) {
                    gameStateDataRef->unk_00C = GAMESTATEDATA_UNK_00C_8;
                    var_s6 = false;
                }
            } else {
                for (j = 0; j < 0x10; j++) {
                    gameStateDataRef->unk_050[j].unk_0 = 0;
                    gameStateDataRef->unk_050[j].unk_2 = 0;
                }
            }

            if (var_s6) {
                dm_set_capsel(gameStateDataRef);
                dm_capsel_speed_up(gameStateDataRef);
                gameStateDataRef->unk_03A = 0;
                gameStateDataRef->unk_039 = 0;
                gameStateDataRef->unk_037 = 0;
                gameStateDataRef->unk_038 = 0;

                for (i = 0; i < ARRAY_COUNT(gameStateDataRef->unk_03C); i++) {
                    gameStateDataRef->unk_03C[i] = 0;
                }
                gameStateDataRef->unk_00C = GAMESTATEDATA_UNK_00C_4;
            }
            break;

        case GAMESTATEDATA_UNK_00C_18:
            switch (retryMenu_input(index)) {
                case 0:
                    if (temp_s1->unk_9C4 < 0) {
                        temp_s1->unk_9C4 = index;
                    }
                    dm_snd_play_in_game(SND_INDEX_62);
                    break;

                case 1:
                    if (gameStateDataRef->unk_004 < 999) {
                        gameStateDataRef->unk_004++;
                    }
                    dm_snd_play_in_game(SND_INDEX_62);
                    return 2;
                    break;

                case 2:
                    dm_snd_play_in_game(SND_INDEX_62);
                    return -2;
                    break;
            }
            break;

        default:
            break;
    }

    return 0;
}
#endif

#if VERSION_US || VERSION_CN
void dm_set_pause_on(struct_game_state_data *gameStateData, s32 arg1) {
    struct_watchGame *temp_s3 = watchGame;
    s32 temp_s1 = gameStateData->unk_04B;

    func_800629E4(temp_s1);

    gameStateData->unk_020 = 0xD;
    gameStateData->unk_018 = gameStateData->unk_014;
    gameStateData->unk_010 = gameStateData->unk_00C;

    if (evs_gamesel == ENUM_EVS_GAMESEL_0) {
        gameStateData->unk_00C = GAMESTATEDATA_UNK_00C_18;
        gameStateData->unk_014 = GAMESTATEDATA_UNK_014_E;
        if ((gameStateData->unk_026 < 0x16) || (temp_s3->unk_378 > 0)) {
            retryMenu_init(0, 1);
        } else {
            retryMenu_init(0, 0);
        }
    } else if (temp_s1 == arg1) {
        gameStateData->unk_00C = GAMESTATEDATA_UNK_00C_18;
        gameStateData->unk_014 = GAMESTATEDATA_UNK_014_E;
        if (evs_story_flg != 0) {
            gameStateData->unk_014 = GAMESTATEDATA_UNK_014_F;
            if (evs_story_no == 9) {
                retryMenu_init(temp_s1, 1);
            } else {
                retryMenu_init(temp_s1, 1);
            }
        } else {
            retryMenu_init(temp_s1, 1);
        }
    } else {
        func_8006417C(temp_s1);
        gameStateData->unk_014 = GAMESTATEDATA_UNK_014_D;
        gameStateData->unk_00C = GAMESTATEDATA_UNK_00C_17;
    }
}
#endif

#if VERSION_US || VERSION_CN
void func_80066808(struct_game_state_data *gameStateData) {
    gameStateData->unk_020 = 1;
    gameStateData->unk_014 = gameStateData->unk_018;
    gameStateData->unk_00C = gameStateData->unk_010;
    if (gameStateData->unk_00C == GAMESTATEDATA_UNK_00C_13) {
        gameStateData->unk_020 = 8;
    }
}
#endif

#if VERSION_US || VERSION_CN
void dm_set_pause_and_volume(struct_game_state_data **gameStateDataP, s32 arg1) {
    struct_watchGame *watchGameP = watchGame;
    s32 var_s2 = watchGameP->unk_9C4;
    struct_game_state_data *temp_a1;
    SndIndex var_s4;
    s32 i;

    if (watchGameP->unk_9C0 != 0) {
        var_s4 = SND_INDEX_60;
    } else {
        var_s4 = SND_INDEX_INVALID;
    }

    watchGameP->unk_9C4 = -1;
    watchGameP->unk_9C0 = 0;
    if (var_s2 < 0) {
        return;
    }

    temp_a1 = gameStateDataP[var_s2];
    if (temp_a1->unk_020 == 1) {
        dm_seq_set_volume(0x40);
        if (watchGameP->unk_000 == 0) {
            for (i = 0; i < arg1; i++) {
                dm_set_pause_on(gameStateDataP[i], var_s2);
            }
        } else {
            resume_game_state(1);
        }
        var_s2 = -1;
    } else if (temp_a1->unk_020 == 0xD) {
        dm_seq_set_volume(0x80);
        for (i = 0; i < arg1; i++) {
            func_80066808(gameStateDataP[i]);
        }
        var_s2 = -1;
    } else if ((watchGameP->unk_000 != 0) && (temp_a1->unk_014 == GAMESTATEDATA_UNK_014_11)) {
        dm_seq_set_volume(0x40);
        resume_game_state(1);
    }

    if ((var_s2 < 0) && (var_s4 > SND_INDEX_INVALID)) {
        dm_snd_play_in_game(var_s4);
    }
}
#endif

#if VERSION_US || VERSION_CN
void func_800669A0(struct_game_state_data *arg0) {
    struct_game_state_data *sp10 = arg0;

    dm_set_pause_and_volume(&sp10, 1);
}
#endif

#if VERSION_US || VERSION_CN
const s16 _tbl_2997[3][2] = {
    { 0x1E, 4 },
    { 0x3C, 6 },
    { 0x78, 0xC },
};

const s16 _clr_3004[2] = { 0xFF, 0x7F };

void dm_calc_big_virus_pos(struct_game_state_data *arg0) {
    struct_watchGame *watchGameP = watchGame;
    s32 i;
    s32 var_s1;

    for (i = 0; i < ARRAY_COUNT(watchGameP->unk_3F4); i++) {
        AnimeState *temp = &watchGameP->animeStates[i];
        f32 var_fv0 = 1.0f;

        if ((temp->animeSeq.unk_10 == 4) && (temp->unk_20 >= 0x5AU)) {
            var_fv0 = -1.0f;
        }

        watchGameP->unk_3F4[i] = CLAMP(watchGameP->unk_3F4[i] + (var_fv0 / 60.0), 0, 1);
    }

    do {
        s32 var_a2 = 0x7F;

        for (i = 0; i < ARRAY_COUNTU(_tbl_2997); i++) {
            if (watchGameP->unk_410 < _tbl_2997[i][0]) {
                var_a2 = _clr_3004[(watchGameP->unk_410 / _tbl_2997[i][1]) % ARRAY_COUNTU(_clr_3004)];
                break;
            }
        }

        for (i = 0; i < ARRAY_COUNT(watchGameP->animeStates); i++) {
            AnimeState *temp = &watchGameP->animeStates[i];

            temp->primColor[0] = temp->primColor[1] = temp->primColor[2] = var_a2;
        }

        watchGameP->unk_414 += 1;
    } while (0);

    if (arg0->unk_020 != 1) {
        return;
    }

    if (watchGameP->unk_410 > 0) {
        if (watchGameP->unk_40C != 0) {
            watchGameP->unk_410 = 0;
            watchGameP->unk_40C = 0;
        } else {
            watchGameP->unk_410--;
        }
    }

    var_s1 = 0;
    for (i = 0; i < ARRAY_COUNT(watchGameP->animeStates); i++) {
        AnimeState *temp = &watchGameP->animeStates[i];

        switch (temp->animeSeq.unk_10) {
            case 0x4:
                if ((evs_gamemode != ENUM_EVS_GAMEMODE_2) && !animeSeq_isEnd(&temp->animeSeq)) {
                    var_s1 += 1;
                }
                break;

            case 0x2:
                if (evs_gamemode != ENUM_EVS_GAMEMODE_2) {
                    var_s1 += 1;
                }
                break;

            case 0x3:
                if (arg0->unk_020 != 1) {
                    var_s1 += 1;
                }
                break;

            case 0:
                break;
        }
    }

    if (watchGameP->unk_410 > 0) {
        var_s1 += 1;
    }

    if (var_s1 == 0) {
        if (watchGameP->unk_3C4 != 0) {
            s32 var_s6 = -1;
            s32 var_s5 = 0;

            for (i = 0; i < ARRAY_COUNT(watchGameP->unk_3E8); i++) {
                AnimeState *temp = &watchGameP->animeStates[i];

                if (watchGameP->unk_400[i] == 0) {
                    if (var_s6 < watchGameP->unk_3E8[i]) {
                        var_s6 = watchGameP->unk_3E8[i];
                    }
                } else if (animeSeq_isEnd(&temp->animeSeq)) {
                    var_s5 += 1;
                }
            }

            if ((evs_gamemode == ENUM_EVS_GAMEMODE_2) && (var_s5 == 3)) {
                for (i = 0; i < ARRAY_COUNT(watchGameP->unk_3E8); i++) {
                    watchGameP->unk_3E8[i] = i * 0x78 + 1;
                }
                watchGameP->unk_9BC = 1;
            } else if (watchGameP->unk_40C != 0) {
                watchGameP->unk_3CC = watchGameP->unk_3C8 * (0x168 - var_s6);
            } else if (watchGameP->unk_3CC < watchGameP->unk_3C8) {
                watchGameP->unk_3CC += 1.0f;
            }
        }
    }

    if (watchGameP->unk_3CC >= watchGameP->unk_3C8) {
        s32 var_v1_4 = watchGameP->unk_3CC / watchGameP->unk_3C8;

        var_v1_4 = MIN(var_v1_4, 4);

        watchGameP->unk_3CC -= watchGameP->unk_3C8 * var_v1_4;
        for (i = 0; i < ARRAY_COUNT(watchGameP->unk_3E8); i++) {
            watchGameP->unk_3E8[i] += var_v1_4;
            if (watchGameP->unk_3E8[i] >= 360.0f) {
                watchGameP->unk_3E8[i] -= 360.0f;
                if ((watchGameP->unk_400[i] == 0) && (evs_gamemode == ENUM_EVS_GAMEMODE_2)) {
                    watchGameP->unk_9BC = 1;
                    watchGameP->unk_3CC = 0;
                    animeState_set(&watchGameP->animeStates[i], 3);
                }
            }
        }
    }

    for (i = 0; i < ARRAY_COUNT(watchGameP->unk_3E8); i++) {
        watchGameP->unk_3D0[i][0] = sinf((watchGameP->unk_3E8[i] * 3.141592654) / 180.0) * 20.0f + 61.0f;
        watchGameP->unk_3D0[i][1] = cosf((watchGameP->unk_3E8[i] * 3.141592654) / 180.0) * -20.0f + 171.0f;
    }
}
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", backup_game_state);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", resume_game_state);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", func_80063378);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", func_800633C0);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", func_800633FC);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", dm_warning_h_line_se);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", dm_play_count_down_se);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", dm_capsel_down);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", func_80063844);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", dm_set_attack_2p);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", dm_set_attack_4p);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", func_80063FF4);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", save_visible_fall_point_flag);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", retryMenu_init);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", func_8006417C);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", retryMenu_input);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", func_80064298);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", func_8006431C);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", set_bottom_up_virus);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", bottom_up_bottle_items);
#endif

#if VERSION_GW
INCLUDE_RODATA("asm/gw/nonmatchings/main_segment/dm_game_main", RO_800B2D18_gw);
#endif

#if VERSION_GW
INCLUDE_RODATA("asm/gw/nonmatchings/main_segment/dm_game_main", RO_800B2D20_gw);
#endif

#if VERSION_GW
INCLUDE_RODATA("asm/gw/nonmatchings/main_segment/dm_game_main", RO_800B2D2C_gw);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", add_taiQ_bonus_wait);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", func_80064848);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", dm_game_eep_write_callback);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", func_80064940);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", func_8006498C);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", dm_save_all);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", dm_query_pause_player);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", dm_game_main_cnt_1P);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", dm_game_main_cnt);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", dm_set_pause_on);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", func_80066808);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", dm_set_pause_and_volume);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", func_800669A0);
#endif

#if VERSION_GW
INCLUDE_RODATA("asm/gw/nonmatchings/main_segment/dm_game_main", RO_800B2E80_gw);
#endif

#if VERSION_GW
INCLUDE_RODATA("asm/gw/nonmatchings/main_segment/dm_game_main", RO_800B2E8C_gw);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", dm_calc_big_virus_pos);
#endif

#if VERSION_US || VERSION_CN
s32 dm_game_main_1p(void) {
    s32 temp_s3;
    struct_watchGame *watchGameP = watchGame;
    struct_game_state_data *gameStateData = &game_state_data[0];

    func_800669A0(gameStateData);
    temp_s3 = dm_game_main_cnt_1P(gameStateData, game_map_data[0], 0);
    dm_warning_h_line_se();
    if (watchGameP->unk_410 == 0) {
        s32 var_s2;

        for (var_s2 = 0; var_s2 < 3; var_s2++) {
            animeState_update(&watchGameP->animeStates[var_s2]);
            animeSmog_update(&watchGameP->animeSmogs[var_s2]);
        }
    }

    dm_calc_big_virus_pos(gameStateData);
    dm_play_count_down_se();

    if (temp_s3 == 3) {
        if (watchGameP->unk_3AC < 0) {
            if (gameStateData->unk_00C == GAMESTATEDATA_UNK_00C_2) {
                watchGameP->unk_3C4 = 1;
                gameStateData->unk_00C = GAMESTATEDATA_UNK_00C_3;
                animeState_set(&gameStateData->unk_094, 1);
                func_800633FC();
            }
        }
    } else if (temp_s3 == 6) {
        s32 temp_s1;

        func_80062A24(gameStateData->unk_04B);
        dm_seq_play_in_game(SEQ_INDEX_14);
        watchGameP->unk_3C4 = 0;
        gameStateData->unk_020 = 5;

        switch (evs_gamemode) {
            case ENUM_EVS_GAMEMODE_3: {
                //! FAKE
                s32 temp_v0;

                gameStateData->unk_014 = GAMESTATEDATA_UNK_014_13;
                gameStateData->unk_00C = GAMESTATEDATA_UNK_00C_1A;

                func_80062DD8(&watchGameP->unk_9D0[0], gameStateData->unk_16C, 1,
                              MAX(0, temp_v0 = 0x2A30 - evs_game_time), gameStateData->unk_174, gameStateData->unk_170,
                              gameStateData->unk_000);
            } break;

            default:
                gameStateData->unk_014 = GAMESTATEDATA_UNK_014_3;
                gameStateData->unk_00C = GAMESTATEDATA_UNK_00C_A;
                break;
        }

        switch (evs_gamemode) {
            case ENUM_EVS_GAMEMODE_3:
                retryMenu_init(0, 3);
                break;

            case ENUM_EVS_GAMEMODE_0:
                retryMenu_init(0, 5);
                break;

            default:
                break;
        }

        animeState_set(&gameStateData->unk_094, 3);

        switch (evs_gamemode) {
            case ENUM_EVS_GAMEMODE_3:
                temp_s1 = game_state_data[0].unk_000;
                game_state_data[0].unk_000 = watchGameP->unk_9D0[0].unk_28;
                dm_save_all();
                game_state_data[0].unk_000 = temp_s1;
                break;

            case ENUM_EVS_GAMEMODE_0:
                dm_save_all();
                break;

            default:
                break;
        }
    } else if (temp_s3 == -1) {
        func_80062A08(gameStateData->unk_04B);
        animeState_set(&gameStateData->unk_094, 4);
        dm_seq_play_in_game(SEQ_INDEX_17);
        gameStateData->unk_02B = 1;
        gameStateData->unk_020 = 8;
        if (evs_gamemode == ENUM_EVS_GAMEMODE_3) {
            gameStateData->unk_014 = GAMESTATEDATA_UNK_014_15;
            gameStateData->unk_00C = GAMESTATEDATA_UNK_00C_1C;

            func_80062DD8(&watchGameP->unk_9D0[0], gameStateData->unk_16C, 0, 0, gameStateData->unk_174,
                          gameStateData->unk_170, gameStateData->unk_000);
            watchGameP->unk_3C4 = 0;
        } else {
            gameStateData->unk_014 = GAMESTATEDATA_UNK_014_4;
            gameStateData->unk_00C = GAMESTATEDATA_UNK_00C_B;
            watchGameP->unk_3C4 = 0;
        }

        if ((gameStateData->unk_026 < 0x16U) || ((watchGameP->unk_378 > 0))) {
            retryMenu_init(0U, 3);
        } else {
            retryMenu_init(0U, 2);
        }

        dm_save_all();
    } else {
        if (temp_s3 == 1) {
            return 1;
        }
        if (temp_s3 == 2) {
            return 2;
        }
        if (temp_s3 == 9) {
            return 9;
        }
        if (temp_s3 == 0x64) {
            return -1;
        }
        if (temp_s3 == -2) {
            return -2;
        }
    }
    return 0;
}
#endif

#if VERSION_US || VERSION_CN
s32 dm_add_win_2p(struct_game_state_data *gameStateDataRef) {
    struct_watchGame *watchGameP = watchGame;
    s32 temp_a3 = gameStateDataRef->unk_04B;
    SeqIndex var_t1 = SEQ_INDEX_17;
    s32 var_a3;
    s32 var_s0;
    s32 var_t3;

    watchGameP->unk_89C[temp_a3]++;

    if (evs_story_flg != 0) {
        var_t3 = _posStStar[temp_a3][0];
        var_a3 = _posStStar[temp_a3][1];

        var_s0 = 1;

        if (gameStateDataRef->unk_04C == 0) {
            var_t1 = SEQ_INDEX_14;
        }
    } else {
        var_t3 = _posP2StarX[temp_a3];
        var_a3 = _posP2StarY[evs_vs_count - 1][watchGameP->unk_89C[temp_a3] - 1];

        var_s0 = watchGameP->unk_89C[temp_a3] == evs_vs_count;

        if (var_s0 != 0) {
            watchGameP->unk_8B4[temp_a3] = MIN(0x63, watchGameP->unk_8B4[temp_a3] + 1);
            watchGameP->unk_8AC[temp_a3] = MIN(0x3E7, watchGameP->unk_8AC[temp_a3] + 1);
        }

        if ((evs_gamesel != ENUM_EVS_GAMESEL_3) || (gameStateDataRef->unk_04C == 0)) {
            if (var_s0 != 0) {
                var_t1 = SEQ_INDEX_15;
            } else {
                var_t1 = SEQ_INDEX_14;
            }
        }
    }

    watchGameP->unk_00C[watchGameP->unk_06C] = var_t3;
    watchGameP->unk_03C[watchGameP->unk_06C] = var_a3;
    watchGameP->unk_06C += 1;
    dm_seq_play_in_game(var_t1);
    return var_s0;
}
#endif

#if VERSION_US || VERSION_CN
s32 dm_set_win_2p(struct_game_state_data *gameStateDataRef, s32 arg1, s32 arg2) {
    s32 temp_s1 = gameStateDataRef->unk_04B;

    gameStateDataRef->unk_020 = 5;
    func_80062990(temp_s1);
    animeState_set(&gameStateDataRef->unk_094, 3);
    dm_snd_play_in_game(_charSE_tbl[gameStateDataRef->unk_090] + 4);

    if ((arg2 == 0) && (gameStateDataRef->unk_04C == 0)) {
        arg2 = 1;

        gameStateDataRef->unk_014 = GAMESTATEDATA_UNK_014_6;
        gameStateDataRef->unk_00C = GAMESTATEDATA_UNK_00C_E;
        if (evs_story_flg == 0) {
            if (arg1 != 0) {
                retryMenu_init(temp_s1, 3);
            } else {
                retryMenu_init(temp_s1, 5);
            }
        } else {
            gameStateDataRef->unk_014 = GAMESTATEDATA_UNK_014_7;
            retryMenu_init(temp_s1, 5);
        }
    } else {
        gameStateDataRef->unk_014 = GAMESTATEDATA_UNK_014_5;
        gameStateDataRef->unk_00C = GAMESTATEDATA_UNK_00C_D;
    }

    return arg2;
}
#endif

#if VERSION_US || VERSION_CN
s32 dm_set_lose_2p(struct_game_state_data *gameStateDataRef, s32 arg1, s32 arg2) {
    s32 temp_s1 = gameStateDataRef->unk_04B;

    gameStateDataRef->unk_020 = 8;
    animeState_set(&gameStateDataRef->unk_094, 4);
    func_800629AC(temp_s1);

    if ((arg2 == 0) && (gameStateDataRef->unk_04C == 0)) {
        arg2 = 1;

        gameStateDataRef->unk_014 = GAMESTATEDATA_UNK_014_9;
        gameStateDataRef->unk_00C = GAMESTATEDATA_UNK_00C_10;

        if (evs_story_flg != 0) {
            gameStateDataRef->unk_014 = GAMESTATEDATA_UNK_014_A;
            if (evs_story_no != 9) {
                retryMenu_init(temp_s1, 3);
            } else {
                retryMenu_init(temp_s1, 3);
            }
        } else {
            if (arg1 != 0) {
                retryMenu_init(temp_s1, 3);
            } else {
                retryMenu_init(temp_s1, 5);
            }
        }
    } else {

        gameStateDataRef->unk_014 = GAMESTATEDATA_UNK_014_8;
        gameStateDataRef->unk_00C = GAMESTATEDATA_UNK_00C_F;
    }

    return arg2;
}
#endif

#if VERSION_US || VERSION_CN
s32 func_800675C8(struct_game_state_data *gameStateDataRef, s32 arg1) {
    s32 temp_s2 = gameStateDataRef->unk_04B;

    gameStateDataRef->unk_020 = 0xB;
    func_800629C8(temp_s2);
    animeState_set(&gameStateDataRef->unk_094, 4);
    if ((arg1 == 0) && (gameStateDataRef->unk_04C == 0)) {
        arg1 = 1;

        gameStateDataRef->unk_014 = GAMESTATEDATA_UNK_014_C;
        gameStateDataRef->unk_00C = GAMESTATEDATA_UNK_00C_12;
        retryMenu_init(temp_s2, 5);
    } else {
        gameStateDataRef->unk_014 = GAMESTATEDATA_UNK_014_B;
        gameStateDataRef->unk_00C = GAMESTATEDATA_UNK_00C_11;
    }

    return arg1;
}
#endif

#if VERSION_US || VERSION_CN
s32 dm_set_time_attack_result_2p(struct_game_state_data **gameStateDataRefP) {
    struct_watchGame *watchGameP = watchGame;
    u32 sp18[2];
    s32 i;
    s32 var_s5 = 0;
    s32 var_s3 = 0;

    sp18[0] = watchGameP->unk_9D0[0].unk_28;
    sp18[1] = watchGameP->unk_9D0[1].unk_28;

    for (i = 0; i < 2; i++) {
        if (sp18[i] > sp18[i ^ 1]) {
            var_s5 = dm_add_win_2p(gameStateDataRefP[i]);
        }
    }

    for (i = 0; i < 2; i++) {
        if (sp18[i] > sp18[i ^ 1]) {
            var_s3 = dm_set_win_2p(gameStateDataRefP[i], var_s5, var_s3);
        }
    }

    for (i = 0; i < 2; i++) {
        if (sp18[i] < sp18[i ^ 1]) {
            var_s3 = dm_set_lose_2p(gameStateDataRefP[i], var_s5, var_s3);
        }
    }

    for (i = 0; i < 2; i++) {
        if (sp18[i] == sp18[i ^ 1]) {
            var_s3 = func_800675C8(gameStateDataRefP[i], var_s3);
            dm_seq_play_in_game(SEQ_INDEX_17);
        }
    }

    return var_s5;
}
#endif

#if VERSION_US || VERSION_CN
s32 dm_game_main_2p(void) {
    struct_watchGame *watchGameP = watchGame;
    s32 var_s4 = 0;
    s32 var_s6 = 0;
    s32 var_fp;
    s32 sp40;
    struct_game_state_data *sp28[2];
    GameMapCell *sp30[2];
    s32 sp38[2];
    s32 var_s1_4;
    s32 var_s2_2;
    s32 i;

    sp40 = 0;
    var_fp = 0;

    for (i = 0; i < 2; i++) {
        sp28[i] = &game_state_data[i];
        sp30[i] = &game_map_data[i][0];
    }

    dm_set_pause_and_volume(sp28, 2);

    for (i = 0; i < 2; i++) {
        sp38[i] = dm_game_main_cnt(sp28[i], sp30[i], i);
    }

    dm_warning_h_line_se();
    dm_play_count_down_se();

    if ((sp38[0] == 3) && (sp38[1] == sp38[0])) {
        if (watchGameP->unk_3AC < 0) {
            for (i = 0; i < 2; i++) {
                if (sp28[i]->unk_00C != GAMESTATEDATA_UNK_00C_2) {
                    break;
                }
            }

            if (i == 2) {
                watchGameP->unk_3C4 = 1;

                for (i = 0; i < 2; i++) {
                    sp28[i]->unk_00C = GAMESTATEDATA_UNK_00C_4;
                    if ((sp28[i]->unk_04C == 1) || ((sp28[i]->unk_04C != 1) && (i == 0) && (aiDebugP1 >= 0))) {
                        aifMakeFlagSet(sp28[i]);
                    }
                }

                func_800633FC();
            }
        }
    } else {
        for (i = 0; i < 2; i++) {
            if (sp38[i] == 0x6) {
                if (evs_gamemode == ENUM_EVS_GAMEMODE_3) {
                    func_80062A24(i);

                    sp28[i]->unk_00C = GAMESTATEDATA_UNK_00C_1A;
                    sp28[i]->unk_014 = GAMESTATEDATA_UNK_014_13;
                    sp28[i]->unk_020 = 0x13;

                    func_80062DD8(&watchGameP->unk_9D0[i], sp28[i]->unk_16C, 1,
                                  0 > 0x2A30 - (s32)evs_game_time ? 0 : 0x2A30 - evs_game_time, sp28[i]->unk_174,
                                  sp28[i]->unk_170, sp28[i]->unk_000);
                    _dm_seq_play_in_game(1, SEQ_INDEX_16);
                } else {
                    var_fp += 1;
                    sp28[i]->unk_020 = 5;
                }
            } else if (sp38[i] == -0x1) {
                if (evs_gamemode == ENUM_EVS_GAMEMODE_3) {
                    if (evs_game_time >= 0x2A30U) {
                        func_80062A08(i);
                        sp28[i]->unk_00C = GAMESTATEDATA_UNK_00C_1C;
                        sp28[i]->unk_014 = GAMESTATEDATA_UNK_014_15;
                        sp28[i]->unk_020 = 0x15;
                    } else {
                        func_80062A40(i);
                        sp28[i]->unk_00C = GAMESTATEDATA_UNK_00C_1E;
                        sp28[i]->unk_014 = GAMESTATEDATA_UNK_014_17;
                        sp28[i]->unk_020 = 0x17;
                    }

                    func_80062DD8(&watchGameP->unk_9D0[i], sp28[i]->unk_16C, 0, 0, sp28[i]->unk_174, sp28[i]->unk_170,
                                  sp28[i]->unk_000);
                    _dm_seq_play_in_game(1, SEQ_INDEX_18);
                } else {
                    sp40 += 1;
                    sp28[i]->unk_020 = 8;
                }

                sp28[i]->unk_02B = 1;
                sp28[i]->unk_040 = 0x10;
                sp28[i]->unk_048 = 1;
            } else if (sp38[i] == 2) {
                return 2;
            } else if (sp38[i] == 9) {
                return 9;
            } else if (sp38[i] == 0x64) {
                return -1;
            } else if (sp38[i] == -0x2) {
                return -2;
            }
        }

        var_s2_2 = 0;
        var_s1_4 = 0;

        for (i = 0; i < 2; i++) {
            switch (sp28[i]->unk_014) {
                case GAMESTATEDATA_UNK_014_13:
                case GAMESTATEDATA_UNK_014_15:
                case GAMESTATEDATA_UNK_014_17:
                    if (watchGameP->unk_888[i] == 0) {
                        var_s1_4 += 1;
                    }
                    break;

                case GAMESTATEDATA_UNK_014_14:
                case GAMESTATEDATA_UNK_014_16:
                case GAMESTATEDATA_UNK_014_18:
                    if (func_80062BC4(&watchGameP->unk_9D0[i])) {
                        var_s2_2 += 1;
                    }
                    break;

                default:
                    break;
            }
        }

        if (var_s1_4 == 2) {
            for (i = 0; i < 2; i++) {
                switch (sp28[i]->unk_014) {
                    case GAMESTATEDATA_UNK_014_13:
                        sp28[i]->unk_020 = 0x14;
                        sp28[i]->unk_014 = GAMESTATEDATA_UNK_014_14;
                        sp28[i]->unk_00C = GAMESTATEDATA_UNK_00C_1B;
                        break;

                    case GAMESTATEDATA_UNK_014_15:
                        sp28[i]->unk_020 = 0x16;
                        sp28[i]->unk_014 = GAMESTATEDATA_UNK_014_16;
                        sp28[i]->unk_00C = GAMESTATEDATA_UNK_00C_1D;
                        break;

                    case GAMESTATEDATA_UNK_014_17:
                        sp28[i]->unk_020 = 0x18;
                        sp28[i]->unk_014 = GAMESTATEDATA_UNK_014_18;
                        sp28[i]->unk_00C = GAMESTATEDATA_UNK_00C_1F;
                        break;

                    default:
                        break;
                }
            }
        } else if (var_s2_2 == 2) {
            var_s6 = dm_set_time_attack_result_2p(sp28);
        } else if ((var_fp == 2) || (sp40 == 2)) {
            for (i = 0; i < 2; i++) {
                var_s4 = func_800675C8(sp28[i], var_s4);
            }
            dm_seq_play_in_game(SEQ_INDEX_17);
        } else if (var_fp != 0) {
            for (i = 0; i < 2; i++) {
                if (sp28[i]->unk_020 == 5) {
                    var_s6 = dm_add_win_2p(sp28[i]);
                }
            }

            for (i = 0; i < 2; i++) {
                if (sp28[i]->unk_020 == 5) {
                    var_s4 = dm_set_win_2p(sp28[i], var_s6, var_s4);
                }
            }

            for (i = 0; i < 2; i++) {
                if (sp28[i]->unk_020 != 5) {
                    var_s4 = dm_set_lose_2p(sp28[i], var_s6, var_s4);
                }
            }
        } else if (sp40 != 0) {

            for (i = 0; i < 2; i++) {
                if (sp28[i]->unk_020 != 8) {
                    var_s6 = dm_add_win_2p(sp28[i]);
                }
            }

            for (i = 0; i < 2; i++) {
                if (sp28[i]->unk_020 != 8) {
                    var_s4 = dm_set_win_2p(sp28[i], var_s6, var_s4);
                }
            }

            for (i = 0; i < 2; i++) {
                if (sp28[i]->unk_020 == 8) {
                    var_s4 = dm_set_lose_2p(sp28[i], var_s6, var_s4);
                }
            }
        }

        if (var_s6 != 0) {
            dm_save_all();
        }
    }
    return 0;
}
#endif

#if VERSION_US || VERSION_CN
s32 dm_game_main_4p(void) {
    struct_watchGame *temp_s4 = watchGame;

    struct_game_state_data *sp18[4];
    GameMapCell *sp28[4];
    s32 sp38[4];
    s32 sp48;
    s32 sp4C;

    s32 var_s0;
    s32 var_s2_2;
    s32 var_s3_2;
    SeqIndex var_s5;
    s32 var_s6;
    s32 var_s7;

    s32 var_a1_3;
    s32 var_a1_4;

    s32 var_a2_2;
    s32 temp_a2_2;
    s32 temp_a2_3;

    s32 temp_a3;

    s32 var_t3;
    s32 var_t4;

    for (var_s0 = 0; var_s0 < 4; var_s0++) {
        sp18[var_s0] = &game_state_data[var_s0];
        sp28[var_s0] = game_map_data[var_s0];
    }

    dm_set_pause_and_volume(sp18, 4);

    for (var_s0 = 0; var_s0 < 4; var_s0++) {
        sp38[var_s0] = dm_game_main_cnt(sp18[var_s0], sp28[var_s0], var_s0);
    }

    dm_warning_h_line_se();

    if ((sp38[0] == 3) && (sp38[1] == sp38[0]) && (sp38[2] == sp38[1]) && (sp38[3] == sp38[2])) {
        if (temp_s4->unk_3AC < 0) {
            for (var_s0 = 0; var_s0 < 4; var_s0++) {
                if (sp18[var_s0]->unk_00C != GAMESTATEDATA_UNK_00C_2) {
                    break;
                }
            }

            if (var_s0 == 4) {
                temp_s4->unk_3C4 = 1;

                for (var_s0 = 0; var_s0 < 4; var_s0++) {
                    sp18[var_s0]->unk_00C = GAMESTATEDATA_UNK_00C_4;
                    if ((sp18[var_s0]->unk_04C == 1) ||
                        ((sp18[var_s0]->unk_04C != 1) && (var_s0 == 0) && (aiDebugP1 >= 0))) {
                        aifMakeFlagSet(sp18[var_s0]);
                    }
                }
                func_800633FC();
            }
        }

        return 0;
    }

    var_s2_2 = 0;
    var_s3_2 = 0;
    var_t4 = 0;
    var_t3 = 0;

    for (var_s0 = 0; var_s0 < 4; var_s0++) {
        if ((sp38[var_s0] == 3) && (sp18[var_s0]->unk_01C == 0x12)) {
            if (sp18[var_s0]->unk_00C == GAMESTATEDATA_UNK_00C_2) {
                sp18[var_s0]->unk_00C = GAMESTATEDATA_UNK_00C_4;
            }
        } else if (sp38[var_s0] == 0x6) {
            var_t3 += 1;
            sp18[var_s0]->unk_020 = 5;
        } else if (sp38[var_s0] == -1) {
            if (sp18[var_s0]->unk_048 == 0) {
                sp18[var_s0]->unk_014 = GAMESTATEDATA_UNK_014_10;
                sp18[var_s0]->unk_01C = 0x10U;
                sp18[var_s0]->unk_020 = 8;
                sp18[var_s0]->unk_040 = 0x10U;
                sp18[var_s0]->unk_048 = 1;
                var_t4 += 1;
                if (sp18[var_s0]->unk_04C == 1) {
                    sp18[var_s0]->unk_00C = GAMESTATEDATA_UNK_00C_19;
                } else {
                    sp18[var_s0]->unk_014 = GAMESTATEDATA_UNK_014_11;
                    sp18[var_s0]->unk_00C = GAMESTATEDATA_UNK_00C_13;
                }
            } else {
                sp18[var_s0]->unk_014 = GAMESTATEDATA_UNK_014_11;
                sp18[var_s0]->unk_00C = GAMESTATEDATA_UNK_00C_13;
            }
            sp18[var_s0]->unk_02B = 4;
        } else if (sp38[var_s0] == 2) {
            return 2;
        } else if (sp38[var_s0] == 0x9) {
            return 9;
        } else if (sp38[var_s0] == 0x64) {
            return -1;
        } else if (sp38[var_s0] == -2) {
            return -2;
        } else if (sp38[var_s0] == 7) {
            sp18[var_s0]->unk_020 = 1;
            sp18[var_s0]->unk_04A = 0;
            sp18[var_s0]->unk_01C = 0x12;
            sp18[var_s0]->unk_00C = GAMESTATEDATA_UNK_00C_14;
        } else if (sp38[var_s0] == 8) {
            sp18[var_s0]->unk_020 = 1;
            sp18[var_s0]->unk_04A = 1;
            sp18[var_s0]->unk_01C = 0x12;
            sp18[var_s0]->unk_00C = GAMESTATEDATA_UNK_00C_14;
        }
    }

    if (var_t3 != 0) {
        var_a1_3 = 0;

        for (var_s0 = 0; var_s0 < 4; var_s0++) {
            if (sp18[var_s0]->unk_020 == 5) {
                var_a1_3 |= 1 << var_s0;
                var_s6 = sp18[var_s0]->unk_04F;
            }
        }

        if ((temp_s4->unk_8C0 == 0) && (var_t3 > 1)) {
            for (var_s0 = 0; var_s0 < 4; var_s0++) {
                var_s2_2 = func_800675C8(sp18[var_s0], var_s2_2);
            }
            var_s5 = SEQ_INDEX_17;
        } else if ((temp_s4->unk_8C0 != 0) && (var_a1_3 & temp_s4->unk_8C4) && (var_a1_3 & temp_s4->unk_8C8)) {
            for (var_s0 = 0; var_s0 < 4; var_s0++) {
                var_s2_2 = func_800675C8(sp18[var_s0], var_s2_2);
            }
            var_s5 = SEQ_INDEX_17;
        } else {
            var_s5 = SEQ_INDEX_14;
            for (var_s0 = 0; var_s0 < 4; var_s0++) {
                if (sp18[var_s0]->unk_020 != 5) {
                    continue;
                }

                temp_a2_2 = sp18[var_s0]->unk_04F;
                temp_a3 = temp_s4->unk_89C[temp_a2_2];
                if (evs_story_flg != 0) {
                    temp_s4->unk_00C[temp_s4->unk_06C] = _posStP4StarX[var_s0];
                    temp_s4->unk_03C[temp_s4->unk_06C] = 0xD;
                } else if (temp_s4->unk_8C0 != 0) {
                    temp_s4->unk_00C[temp_s4->unk_06C] = _posP4TeamStarX[evs_vs_count - 1][temp_a2_2][temp_a3];
                    temp_s4->unk_03C[temp_s4->unk_06C] = 0xD;
                } else {
                    temp_s4->unk_00C[temp_s4->unk_06C] = _posP4CharStarX[evs_vs_count - 1][temp_a2_2][temp_a3];
                    temp_s4->unk_03C[temp_s4->unk_06C] = 0xD;
                }

                temp_s4->unk_06C += 1;

                temp_s4->unk_89C[temp_a2_2]++;
                if (evs_story_flg != 0) {
                    var_s3_2 = 1;
                } else if (temp_s4->unk_89C[temp_a2_2] == evs_vs_count) {
                    var_s3_2 = 1;
                    var_s5 = SEQ_INDEX_15;
                }
            }

            for (var_s0 = 0; var_s0 < 4; var_s0++) {
                if (sp18[var_s0]->unk_04F != var_s6) {
                    continue;
                }

                if ((evs_story_flg != 0) && (sp18[var_s0]->unk_04C == 0)) {
                    var_s5 = SEQ_INDEX_14;
                }
                var_s2_2 = dm_set_win_2p(sp18[var_s0], var_s3_2, var_s2_2);
            }

            for (var_s0 = 0; var_s0 < 4; var_s0++) {
                if (sp18[var_s0]->unk_04F != var_s6) {
                    if ((evs_story_flg != 0) && (sp18[var_s0]->unk_04C == 0)) {
                        var_s5 = SEQ_INDEX_17;
                    }
                    var_s2_2 = dm_set_lose_2p(sp18[var_s0], var_s3_2, var_s2_2);
                }
            }
        }

        dm_seq_play_in_game(var_s5);
    } else if (var_t4 != 0) {
        var_s7 = 0;
        var_a2_2 = 0;
        var_a1_4 = 0;

        for (var_s0 = 0; var_s0 < 4; var_s0++) {
            if (sp18[var_s0]->unk_048 != 0) {
                var_a2_2 += 1;
                var_a1_4 |= 1 << var_s0;
            }
        }

        if (var_a2_2 == 4) {
            for (var_s0 = 0; var_s0 < 4; var_s0++) {
                var_s2_2 = func_800675C8(sp18[var_s0], var_s2_2);
            }
            dm_seq_play_in_game(SEQ_INDEX_17);
        } else if ((evs_story_flg != 0) && (var_a1_4 & 1)) {
            var_s3_2 = 1;

            var_s2_2 = dm_set_lose_2p(sp18[0], var_s3_2, var_s2_2);
            for (var_s0 = 1; var_s0 < 4; var_s0++) {
                var_s2_2 = dm_set_win_2p(sp18[var_s0], var_s3_2, var_s2_2);
            }
            dm_seq_play_in_game(SEQ_INDEX_17);
        } else if ((temp_s4->unk_8C0 == 0) && (var_a2_2 == 3)) {
            s32 temp;

            var_s7 = 1;
            var_s5 = SEQ_INDEX_14;

            for (var_s0 = 0; var_s0 < 4; var_s0++) {
                if (sp18[var_s0]->unk_048 == 0) {
                    temp_a2_3 = sp18[var_s0]->unk_04F;
                    temp = temp_s4->unk_89C[temp_a2_3];

                    if (evs_story_flg != 0) {
                        temp_s4->unk_00C[temp_s4->unk_06C] = _posStP4StarX[var_s0];
                        temp_s4->unk_03C[temp_s4->unk_06C] = 0xD;
                    } else {
                        temp_s4->unk_00C[temp_s4->unk_06C] = _posP4CharStarX[evs_vs_count - 1][temp_a2_3][temp];
                        temp_s4->unk_03C[temp_s4->unk_06C] = 0xD;
                    }

                    temp_s4->unk_06C += 1;
                    temp_s4->unk_89C[temp_a2_3]++;
                    var_s6 = temp_a2_3;
                    if (evs_story_flg != 0) {
                        if (sp18[var_s0]->unk_04C != 0) {
                            var_s5 = SEQ_INDEX_17;
                        }
                        var_s3_2 = 1;
                    } else if (temp_s4->unk_89C[temp_a2_3] == evs_vs_count) {
                        var_s3_2 = 1;
                        var_s5 = SEQ_INDEX_15;
                    }
                    break;
                }
            }
        } else if (temp_s4->unk_8C0 != 0) {
            if ((var_a1_4 & temp_s4->unk_8C4) == temp_s4->unk_8C4) {
                sp48 = 1;
                var_s6 = 1;
                var_s7 = 1;
                sp4C = temp_s4->unk_89C[1];
                temp_s4->unk_89C[1]++;
            } else if ((var_a1_4 & temp_s4->unk_8C8) == temp_s4->unk_8C8) {
                sp48 = 0;
                var_s6 = 0;
                var_s7 = 1;
                sp4C = temp_s4->unk_89C[0];
                temp_s4->unk_89C[0]++;
            }

            if (var_s7 != 0) {
                temp_s4->unk_00C[temp_s4->unk_06C] = _posP4TeamStarX[evs_vs_count - 1][sp48][sp4C];
                temp_s4->unk_03C[temp_s4->unk_06C] = 0xD;
                temp_s4->unk_06C += 1;

                var_s5 = SEQ_INDEX_14;
                for (var_s0 = 0; var_s0 < 4; var_s0++) {
                    if (temp_s4->unk_89C[var_s0] == evs_vs_count) {
                        var_s3_2 = 1;
                        var_s5 = SEQ_INDEX_15;
                        break;
                    }
                }
            }
        }

        if (var_s7 != 0) {
            for (var_s0 = 0; var_s0 < 4; var_s0++) {
                if (sp18[var_s0]->unk_04F == var_s6) {
                    var_s2_2 = dm_set_win_2p(sp18[var_s0], var_s3_2, var_s2_2);
                }
            }

            for (var_s0 = 0; var_s0 < 4; var_s0++) {
                if (sp18[var_s0]->unk_04F != var_s6) {
                    var_s2_2 = dm_set_lose_2p(sp18[var_s0], var_s3_2, var_s2_2);
                }
            }
            dm_seq_play_in_game(var_s5);
        }
    }

    if (var_s3_2 != 0) {
        dm_save_all();
    }

    return 0;
}
#endif

#if VERSION_US || VERSION_CN
bool dm_game_demo_1p(void) {
    struct_watchGame *watchGameP = watchGame;
    s32 temp_s4 = dm_game_main_cnt_1P(game_state_data, game_map_data[0], 0);
    s32 i;

    dm_warning_h_line_se();

    for (i = 0; i < 3; i++) {
        AnimeState *animeState = &watchGameP->animeStates[i];
        AnimeSmog *animeSmog = &watchGameP->animeSmogs[i];

        animeState_update(animeState);
        animeSmog_update(animeSmog);
    }

    dm_calc_big_virus_pos(game_state_data);

    if ((temp_s4 == 3) && (watchGameP->unk_3AC < 0)) {
        game_state_data[0].unk_00C = GAMESTATEDATA_UNK_00C_3;
        animeState_set(&game_state_data[0].unk_094, 1);
        if ((game_state_data[0].unk_04C == 1) || (aiDebugP1 >= 0)) {
            aifMakeFlagSet(game_state_data);
        }

        watchGameP->unk_3C4 = 1;
    }

    if (watchGameP->unk_41C != 0) {
        watchGameP->unk_41C--;

        if (gControllerPressedButtons[main_joy[0]] & ANY_BUTTON) {
            watchGameP->unk_41C = 0;
        }

        if (watchGameP->unk_41C == 0) {
            return true;
        }
    }

    return false;
}
#endif

#if VERSION_US || VERSION_CN
bool dm_game_demo_2p(void) {
    struct_watchGame *watchGameP = watchGame;
    s32 sp10[2];
    s32 i;

    for (i = 0; i < ARRAY_COUNT(sp10); i++) {
        sp10[i] = dm_game_main_cnt(&game_state_data[i], game_map_data[i], i);
    }

    dm_warning_h_line_se();

    if ((sp10[0] == 3) && (sp10[1] == sp10[0]) && (watchGameP->unk_3AC < 0)) {
        for (i = 0; i < ARRAY_COUNT(sp10); i++) {
            game_state_data[i].unk_00C = GAMESTATEDATA_UNK_00C_4;

            if (((&game_state_data[i])->unk_04C == 1) ||
                (((&game_state_data[i])->unk_04C != 1) && (i == 0) && (aiDebugP1 >= 0))) {
                aifMakeFlagSet(&game_state_data[i]);
            }
        }

        watchGameP->unk_3C4 = 1;
    }

    if (watchGameP->unk_41C != 0) {
        watchGameP->unk_41C--;
        if (gControllerPressedButtons[main_joy[0]] & ANY_BUTTON) {
            watchGameP->unk_41C = 0;
        }

        if (watchGameP->unk_41C == 0) {
            return true;
        }
    }

    return false;
}
#endif

#if VERSION_US || VERSION_CN
bool dm_game_demo_4p(void) {
    struct_watchGame *watchGameP = watchGame;
    s32 sp10[4];
    s32 i;

    for (i = 0; i < ARRAY_COUNT(sp10); i++) {
        sp10[i] = dm_game_main_cnt(&game_state_data[i], game_map_data[i], i);
    }

    dm_warning_h_line_se();

    if ((sp10[0] == 3) && (sp10[1] == sp10[0]) && (sp10[2] == sp10[1]) && (sp10[3] == sp10[2]) &&
        (watchGameP->unk_3AC < 0)) {
        for (i = 0; i < ARRAY_COUNT(sp10); i++) {
            game_state_data[i].unk_00C = GAMESTATEDATA_UNK_00C_4;

            if (((&game_state_data[i])->unk_04C == 1) ||
                ((((&game_state_data[i])->unk_04C != 1) && (i == 0)) && (aiDebugP1 >= 0))) {
                aifMakeFlagSet(&game_state_data[i]);
            }
        }

        watchGameP->unk_3C4 = 1;
    }

    if (watchGameP->unk_41C != 0) {
        watchGameP->unk_41C--;

        if (gControllerPressedButtons[main_joy[0]] & ANY_BUTTON) {
            watchGameP->unk_41C = 0;
        }

        if (watchGameP->unk_41C == 0) {
            return true;
        }
    }

    return false;
}
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", dm_game_main_1p);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", dm_add_win_2p);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", dm_set_win_2p);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", dm_set_lose_2p);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", func_800675C8);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", dm_set_time_attack_result_2p);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", dm_game_main_2p);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", dm_game_main_4p);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", dm_game_demo_1p);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", dm_game_demo_2p);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", dm_game_demo_4p);
#endif

#if VERSION_US || VERSION_CN
const s32 cap_tex_4162[2] = { 8, 2 };

TiTexData *dm_game_get_capsel_tex(s32 arg0) {
    return &watchGame->unk_444[cap_tex_4162[arg0]];
}
#endif

#if VERSION_US || VERSION_CN
const u32 cap_pal_4164[][6] = {
    { 8, 10, 6, 9, 11, 7 },
    { 2, 4, 0, 3, 5, 1 },
};
#endif

#if VERSION_US || VERSION_CN
TiTexData *dm_game_get_capsel_pal(s32 arg0, s32 arg1) {
    return &watchGame->unk_444[cap_pal_4164[arg0][arg1]];
}
#endif

#if VERSION_US || VERSION_CN
void scoreNums_draw(struct_watchGame_unk_0B8 *arg0, Gfx **gfxP) {
    struct_watchGame *watchGameP = watchGame;
    Gfx *gfx = *gfxP;
    TiTexData *temp_s4 = &watchGameP->unk_430[0x11];
    TiTexData *temp_s2 = &watchGameP->unk_430[0x16];
    s32 var_s3 = MIN(temp_s4->info[0], temp_s2->info[0]);
    s32 temp_s0 = temp_s4->info[1] / 12;
    s32 i;

    gSPDisplayList(gfx++, alpha_texture_init_dl);

    gDPSetCombineLERP(gfx++, TEXEL0, 0, PRIMITIVE, 0, TEXEL1, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED);

    for (i = 0; i < 8U; i++) {
        struct_watchGame_unk_0B8_unk_00 *temp_t3 = &arg0->unk_00[WrapI(0, 8, arg0->unk_A0 + i)];
        f32 temp_ft0 = temp_t3->unk_10;
        f32 var_fv0_2;
        s32 alpha;

        if (temp_ft0 == 1.0) {
            continue;
        }

        if (temp_ft0 < 0.2) {
            alpha = temp_ft0 * 1275.0f;
        } else if (temp_ft0 < 0.8) {
            alpha = 255;
        } else {
            alpha = (1.0f - temp_ft0) * 1275.0f;
        }

        if (temp_ft0 > 0.5) {
            var_fv0_2 = 1.0f;
        } else {
            var_fv0_2 = (temp_ft0 * 4.0) - 1.0;
        }

        var_fv0_2 = (1.0 - (var_fv0_2 * var_fv0_2)) * 8.0;

        gDPSetPrimColor(gfx++, 0, 0, _scoreNumsColor[temp_t3->unk_0C].r, _scoreNumsColor[temp_t3->unk_0C].g,
                        _scoreNumsColor[temp_t3->unk_0C].b, alpha);

        StretchAlphaTexBlock(
            &gfx, var_s3, temp_s0, (u8 *)temp_s4->texs[1] + (temp_s4->info[0] * temp_s0 * temp_t3->unk_08 * 2),
            temp_s4->info[0], (u8 *)temp_s2->texs[1] + (temp_s2->info[0] * temp_s0 * temp_t3->unk_08 / 2),
            temp_s2->info[0], temp_t3->unk_00, temp_t3->unk_04 - var_fv0_2, var_s3, temp_s0);
    }

    *gfxP = gfx;
}
#endif

#if VERSION_US || VERSION_CN
void func_80069160(struct_watchGame_unk_070 *arg0, UNK_TYPE *arg1, UNK_TYPE *arg2) {
    s32 i;

    arg0->unk_00 = arg1;
    arg0->unk_04 = arg2;

    for (i = 0; i < ARRAY_COUNTU(arg0->unk_08); i++) {
        arg0->unk_08[i] = 0;
    }
}
#endif

#if VERSION_US || VERSION_CN
void func_80069188(struct_watchGame_unk_070 *arg0, s32 arg1) {
    s32 i;

    for (i = 0; i < arg1; i++) {
        s32 temp_a2 = arg0->unk_08[i];

        if (temp_a2 < 0x30) {
            arg0->unk_08[i] = temp_a2 + 1;
        } else {
            arg0->unk_08[i] = WrapI(0x30, 0x6C, temp_a2 + 1);
        }
    }
}
#endif

#if VERSION_US || VERSION_CN
void starForce_draw(struct_watchGame_unk_070 *arg0, Gfx **gfxP, s32 arg2) {
    struct_watchGame *watchGameP = watchGame;
    Gfx *gfx = *gfxP;
    TiTexData *temp_s0;
    TiTexData *temp_s5;
    s32 i;
    s32 var_a3;

    gSPDisplayList(gfx++, alpha_texture_init_dl);
    gDPSetCombineLERP(gfx++, TEXEL0, 0, PRIMITIVE, 0, TEXEL1, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED);

    temp_s0 = &watchGameP->unk_430[0x10];
    temp_s5 = &watchGameP->unk_430[0x15];

    for (i = 0; i < arg2; i++) {
        if (arg0->unk_08[i] < 0x30) {
            gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, 255);

            tiStretchAlphaTexItem(&gfx, temp_s0, temp_s5, 0, 0x10, 0, (f32)arg0->unk_00[i], (f32)arg0->unk_04[i],
                                  (f32)temp_s0->info[0], (f32)((u16)temp_s0->info[1] >> 4));
        }

        var_a3 = MIN(255, arg0->unk_08[i] * 8);

        gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, var_a3);

        var_a3 = MAX(0, arg0->unk_08[i] - 0x30) >> 2;
        tiStretchAlphaTexItem(&gfx, temp_s0, temp_s5, 0, 0x10, var_a3 + 1, (f32)arg0->unk_00[i], (f32)arg0->unk_04[i],
                              (f32)temp_s0->info[0], (f32)((u16)temp_s0->info[1] >> 4));
    }

    gSPDisplayList(gfx++, normal_texture_init_dl);
    gDPSetCombineMode(gfx++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
    gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gDPSetPrimColor(gfx++, 0, 0, 255, 255, 200, 255);
    gDPSetTextureLUT(gfx++, G_TT_NONE);

    for (i = 0; i < arg2; i++) {
        var_a3 = arg0->unk_08[i] >> 2;
        if (var_a3 >= 0xC) {
            continue;
        }
        temp_s0 = &watchGameP->unk_430[var_a3];
        StretchTexTile4i(&gfx, temp_s0->info[0], temp_s0->info[1], temp_s0->texs[1], 0, 0, temp_s0->info[0],
                         temp_s0->info[1], arg0->unk_00[i], arg0->unk_04[i], temp_s0->info[0], temp_s0->info[1]);
    }

    *gfxP = gfx;
}
#endif

#if VERSION_US || VERSION_CN
void func_800695A8(Gfx **gfxP, s32 arg1, s32 arg2, s32 arg3) {
    struct_watchGame *watchGameP = watchGame;
    Gfx *gfx = *gfxP;
    TiTexData *temp_a1 = &watchGameP->unk_430[0x10];
    TiTexData *temp = &watchGameP->unk_430[0x15];

    if (arg3 == 0) {
        gSPDisplayList(gfx++, alpha_texture_init_dl);
    }
    tiStretchAlphaTexItem(&gfx, temp_a1, temp, arg3, 0x10, 0, arg1, arg2, temp_a1->info[0], temp_a1->info[1] >> 4);

    *gfxP = gfx;
}
#endif

#if VERSION_US || VERSION_CN
const u8 _tbl_4274[4][4] = { { 0, 5, 8, 0xA }, { 0, 1, 6, 9 }, { 0, 1, 2, 4 }, { 0, 1, 2, 3 } };

void draw_4p_attack_guide_panel(Gfx **gfxP, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    struct_watchGame *watchGameP = watchGame;
    Gfx *gfx = *gfxP;
    TiTexData *temp_t1;
    TiTexData *temp;
    s32 var_a1;

    gSPDisplayList(gfx++, normal_texture_init_dl);

    temp_t1 = &watchGameP->unk_440[9];
    tiStretchTexItem(&gfx, temp_t1, 0, 4, arg2, arg3, arg4, temp_t1->info[0], temp_t1->info[1] / 4);

    gSPDisplayList(gfx++, alpha_texture_init_dl);

    for (var_a1 = 0; var_a1 < 3; var_a1++) {
        f32 temp_fs0 = arg3 + 0x24;
        f32 temp_fv1 = arg4 + 5 + var_a1 * 0xD;
        s32 temp_a2 = game_state_data[arg2].unk_04F;
        s32 temp2 = game_state_data[(arg2 + 1 + var_a1) % 4].unk_04F;

        if (temp_a2 == temp2) {
            temp_t1 = &watchGameP->unk_440[temp_a2 + 0x10];
            temp = &watchGameP->unk_440[0x18];
            StretchAlphaTexBlock(&gfx, temp_t1->info[0], temp_t1->info[1], temp_t1->texs[1], temp_t1->info[0],
                                 temp->texs[1], temp->info[0], temp_fs0, temp_fv1 + 1.0f, temp_t1->info[0],
                                 temp_t1->info[1]);
        } else {
            s32 temp3;

            temp_t1 = &watchGameP->unk_440[0xA];
            temp = &watchGameP->unk_440[0x12];

            temp3 = _tbl_4274[arg1 - 1][(arg2 + var_a1 + 1) % ARRAY_COUNT(_tbl_4274[0])];
            tiStretchAlphaTexItem(&gfx, temp_t1, temp, 0, 0xB, temp3, temp_fs0, temp_fv1, temp_t1->info[0],
                                  temp_t1->info[1] / 11);
        }
    }

    *gfxP = gfx;
}
#endif

#if VERSION_US || VERSION_CN
void dm_map_draw(GameMapCell *mapCells, u8 arg1, s16 arg2, s16 arg3, s8 arg4) {
    s32 i;

    for (i = 0; i < GAME_MAP_ROWS * GAME_MAP_COLUMNS; i++) {
        GameMapCell *cell = &mapCells[i];

        if ((cell->unk_4[0] != 0) && (cell->unk_3 == arg1)) {

            gSPTextureRectangle(gGfxHead++, (cell->unk_0 * arg4 + arg2) << 2, ((cell->unk_1 * arg4) + arg3) << 2,
                                (cell->unk_0 * arg4 + arg2 + arg4) << 2, (cell->unk_1 * arg4 + arg3 + arg4) << 2,
                                G_TX_RENDERTILE, 0, (cell->unk_2 * arg4) << 5, 0x0400, 0x0400);
        }
    }
}
#endif

#if VERSION_US || VERSION_CN
void func_80069ACC(GameMapCell *mapCells, struct_game_state_data_unk_178 *arg1, s32 arg2[2]) {
    s32 var_s3 = 0x10;
    s32 i;
    int row;

    for (i = 0; i < 2; i++) {
        row = MAX(1, arg1->unk_2[i]);

        for (; row < GAME_MAP_ROWS; row++) {
            if (get_map_info(mapCells, arg1->unk_0[i], row) != 0) {
                var_s3 = MIN(var_s3, row - 1);
                break;
            }
        }
    }

    arg2[0] = var_s3 - (arg1->unk_2[0] < arg1->unk_2[1] ? 1 : 0);
    arg2[1] = var_s3 - (arg1->unk_2[0] > arg1->unk_2[1] ? 1 : 0);
}
#endif

#if VERSION_US || VERSION_CN
const char _tbl_4345[] = { 9, 0, 1, 2, 3, 4, 5, 6, 7, 8 };

void draw_virus_number(Gfx **gfxP, u32 arg1, s32 arg2, s32 arg3, f32 arg4, f32 arg5 UNUSED) {
    struct_watchGame *watchGameP = watchGame;
    TiTexData *temp_s5 = &watchGameP->unk_430[0xD];
    TiTexData *temp_s3 = &watchGameP->unk_430[0x12];
    s32 var_t1 = 0;
    s32 var_s6 = MIN(temp_s5->info[0], temp_s3->info[0]);
    s32 temp_s1 = temp_s5->info[1] / 10;
    s32 sp38[16];
    s32 temp_fs0;
    s32 var_s0;
    s32 var_s4;

    do {
        sp38[var_t1] = arg1 % 10;
        arg1 /= 10;
        var_t1 += 1;
    } while (arg1 != 0);

    var_s4 = var_t1 * -7;
    temp_fs0 = temp_s1 / -2;
    for (var_s0 = var_t1 - 1; var_s0 >= 0; var_s0--) {
        StretchAlphaTexBlock(
            gfxP, var_s6, temp_s1, temp_s5->texs[1] + (temp_s5->info[0] * temp_s1 * _tbl_4345[sp38[var_s0]] * 2),
            temp_s5->info[0], temp_s3->texs[1] + (temp_s3->info[0] * temp_s1 * _tbl_4345[sp38[var_s0]]) / 2,
            temp_s3->info[0], arg2 + (var_s4 * arg4), arg3 + temp_fs0 * arg4, var_s6 * arg4, temp_s1 * arg4);
        var_s4 += 0xE;
    }
}
#endif

#if VERSION_US || VERSION_CN
const s32 _tex_4374[] = { 3, 4, 5 };
const s32 _row_4375[] = { 0xD, 0xC, 0xC };
#endif

#if VERSION_US || VERSION_CN
void draw_count_number(Gfx **gfxP, s32 arg1, s32 arg2, u32 arg3, s32 arg4, s32 arg5) {
    struct_watchGame *watchGameP = watchGame;
    TiTexData *temp_a1 = watchGameP->unk_438;
    TiTexData *temp_s5 = &temp_a1[_tex_4374[arg1]];
    TiTexData *temp_s2 = &temp_a1[7];
    s32 var_s7 = MIN(temp_s5->info[0], temp_s2->info[0]);
    s32 temp_s6 = temp_s5->info[1] / _row_4375[arg1];
    s32 sp38[16];
    s32 i;

    for (i = 0; i < arg2; i++) {
        sp38[i] = arg3 % 10;
        arg3 /= 10;
    }

    switch (arg2) {
        case -1:
            sp38[0] = 0xA;
            arg2 = 1;
            break;

        case -2:
            sp38[0] = 0xB;
            arg2 = 1;
            break;

        case -3:
            sp38[0] = 0xC;
            arg2 = 1;
            break;
    }

    for (i = arg2 - 1; i >= 0; i--) {
        StretchAlphaTexBlock(gfxP, var_s7, temp_s6, temp_s5->texs[1] + temp_s5->info[0] * temp_s6 * sp38[i] * 2,
                             temp_s5->info[0], temp_s2->texs[1] + temp_s2->info[0] * temp_s6 * sp38[i] / 2,
                             temp_s2->info[0], arg4, arg5, var_s7, temp_s6);
        arg4 += 9;
    }
}
#endif

#if VERSION_US || VERSION_CN
const u8 _pos_4415[] = { 0, 0x11, 0x1A };
const s8 _col_4416[] = { 2, -3, 2 };
static_assert(ARRAY_COUNT(_pos_4415) == 3, "");
static_assert(ARRAY_COUNT(_pos_4415) == ARRAY_COUNT(_col_4416), "");

void func_8006A098(Gfx **gfxP, u32 arg1, s32 arg2, s32 arg3) {
    s32 sp20[3];
    s32 i;

    sp20[1] = 0;
    sp20[2] = (arg1 / 60) % 60;
    sp20[0] = ((arg1 / 60) / 60) % 100;
    for (i = 0; i < 3; i++) {
        draw_count_number(gfxP, 0, _col_4416[i], sp20[i], arg2 + _pos_4415[i], arg3);
    }
}
#endif

#if VERSION_US || VERSION_CN
const u8 _pos_4426[] = { 0, 6, 13, 28, 35 };
const s8 _col_4427[] = { 1, -3, 2, -3, 1 };
static_assert(ARRAY_COUNT(_pos_4426) == 5, "");
static_assert(ARRAY_COUNT(_pos_4426) == ARRAY_COUNT(_col_4427), "");

void draw_time2(Gfx **gfxP, u32 arg1, s32 arg2, s32 arg3) {
    s32 sp20[5];
    s32 i;

    sp20[3] = 0;
    sp20[1] = 0;
    sp20[4] = (arg1 / 6) % 10;
    sp20[2] = ((arg1 / 6) / 10) % 60;
    sp20[0] = (((arg1 / 6) / 10) / 60) % 60;
    for (i = 0; i < 5; i++) {
        draw_count_number(gfxP, 0, _col_4427[i], sp20[i], arg2 + _pos_4426[i], arg3);
    }
}
#endif

#if VERSION_US || VERSION_CN
void push_any_key_draw(s32 arg0, s32 arg1) {
    struct_watchGame *watchGameP = watchGame;
    s32 alpha;
    s32 var_a1_2;
    TiTexData *temp_a3;
    TiTexData *temp1;
    TiTexData *temp2;

    alpha = sins((watchGameP->unk_424 << 10) & 0xFC00) * ((f32)0xFF / 0x8000) + 127;
    alpha = CLAMP(alpha, 0, 255);

    gSPDisplayList(gGfxHead++, alpha_texture_init_dl);
    gDPSetCombineLERP(gGfxHead++, TEXEL0, 0, PRIMITIVE, 0, TEXEL1, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0,
                      COMBINED);
    gDPSetPrimColor(gGfxHead++, 0, 0, 255, 255, 255, alpha);

    temp_a3 = watchGameP->unk_430;
    temp1 = &temp_a3[0x17];
    temp2 = &temp_a3[0x18];

    var_a1_2 = MIN(temp1->info[0], temp2->info[0]);

    StretchAlphaTexTile(&gGfxHead, var_a1_2, temp1->info[1], temp1->texs[1], temp1->info[0], temp2->texs[1],
                        temp2->info[0], 0, 0, var_a1_2, temp1->info[1], arg0, arg1, var_a1_2, temp1->info[1]);
}
#endif

#if VERSION_US || VERSION_CN
const s32 _tex_4459[3][2] = { { 0xE, 0x13 }, { 0x1B, 0x1C }, { 0x19, 0x1A } };

void draw_demo_logo(Gfx **gfxP, s32 arg1, s32 arg2) {
    struct_watchGame *watchGameP = watchGame;
    Gfx *gfx = *gfxP;
    s32 alpha[3];
    s32 i;

    alpha[0] = sins((watchGameP->unk_424 << 0xA) & 0xFC00) * (255.0f / 0x8000) + 127;
    alpha[0] = CLAMP(alpha[0], 0, 255);
    alpha[1] = 255 - alpha[0];
    alpha[2] = 255;

    gSPDisplayList(gfx++, alpha_texture_init_dl);
    gDPSetCombineLERP(gfx++, TEXEL0, 0, PRIMITIVE, 0, TEXEL1, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED);

    for (i = 0; i < ARRAY_COUNTU(alpha); i++) {
        TiTexData *temp_t0;
        TiTexData *temp_t2;
        s32 var_a3;
        s32 var_t1;

        if (i == 2) {
            arg1 = 0xE;
            arg2 = 0x12;
        }

        temp_t0 = &watchGameP->unk_430[_tex_4459[i][0]];
        temp_t2 = &watchGameP->unk_430[_tex_4459[i][1]];

        var_a3 = MIN(temp_t0->info[0], temp_t2->info[0]);
        var_t1 = MIN(temp_t0->info[1], temp_t2->info[1]);

        gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, alpha[i]);
        StretchAlphaTexTile(&gfx, var_a3, var_t1, temp_t0->texs[1], temp_t0->info[0], temp_t2->texs[1],
                            temp_t2->info[0], 0, 0, var_a3, var_t1, arg1, arg2, var_a3, var_t1);
    }

    *gfxP = gfx;
}
#endif

#if VERSION_US || VERSION_CN
const s32 RO_800B2134[2][2] = { { 0x17, 0x18 }, { 0xF, 0x14 } };

void draw_replay_logo(Gfx **gfxP, s32 arg1, s32 arg2) {
    struct_watchGame *watchGameP = watchGame;
    Gfx *gfx = *gfxP;
    s32 alpha[2];
    s32 i;

    alpha[0] = sins((watchGameP->unk_424 << 0xA) & 0xFC00) * (255.0f / 0x8000) + 127;
    alpha[0] = CLAMP(alpha[0], 0, 255);
    alpha[1] = 255 - alpha[0];

    gSPDisplayList(gfx++, alpha_texture_init_dl);
    gDPSetCombineLERP(gfx++, TEXEL0, 0, PRIMITIVE, 0, TEXEL1, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED);

    for (i = 0; i < ARRAY_COUNTU(alpha); i++) {
        TiTexData *temp_t0 = &watchGameP->unk_430[RO_800B2134[i][0]];
        TiTexData *temp_t3 = &watchGameP->unk_430[RO_800B2134[i][1]];
        s32 var_t2 = MIN(temp_t0->info[0], temp_t3->info[0]);
        s32 var_t1 = MIN(temp_t0->info[1], temp_t3->info[1]);

        gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, alpha[i]);
        StretchAlphaTexTile(&gfx, var_t2, var_t1, temp_t0->texs[1], temp_t0->info[0], temp_t3->texs[1],
                            temp_t3->info[0], 0, 0, var_t2, var_t1, arg1, arg2, var_t2, var_t1);
    }

    *gfxP = gfx;
}
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", dm_game_get_capsel_tex);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", dm_game_get_capsel_pal);
#endif

#if VERSION_GW
INCLUDE_RODATA("asm/gw/nonmatchings/main_segment/dm_game_main", RO_800B2EC8_gw);
#endif

#if VERSION_GW
INCLUDE_RODATA("asm/gw/nonmatchings/main_segment/dm_game_main", RO_800B2ED0_gw);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", scoreNums_draw);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", func_80069160);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", func_80069188);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", starForce_draw);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", func_800695A8);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", draw_4p_attack_guide_panel);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", dm_map_draw);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", func_80069ACC);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", draw_virus_number);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", draw_count_number);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", func_8006A098);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", draw_time2);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", push_any_key_draw);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", draw_demo_logo);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", draw_replay_logo);
#endif

#if VERSION_US || VERSION_CN
void func_8006A938(s32 arg0) {
    struct_watchGame *watchGameP = watchGame;
    s32 i;

    watchGame->unk_99C = arg0;
    for (i = 0; i < 4; i++) {
        if (i < arg0) {
            watchGameP->unk_9A0[i] = 0;
        } else {
            watchGameP->unk_9A0[i] = -1;
        }
    }
}
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", func_8006B528_gw);
#endif

#if VERSION_US || VERSION_CN
void _disp_coin_logo(Gfx **gfxP, s32 arg1) {
    struct_watchGame *watchGameP = watchGame;
    Gfx *gfx = *gfxP;
    s32 i;
    TiTexData *temp_s2;
    s32 temp_s5;

    if (watchGameP->unk_99C < arg1) {
        for (i = watchGameP->unk_99C; i < arg1; i++) {
            if (watchGameP->unk_9A0[i] == 0) {
                watchGameP->unk_9A0[i] = 0;
                watchGameP->unk_99C += 1;
            } else if (watchGameP->unk_9A0[i] < 0) {
                watchGameP->unk_9A0[i] = 0x1E;
            } else {
                watchGameP->unk_9A0[i] = watchGameP->unk_9A0[i] - 1;
            }
        }
    } else if (arg1 < watchGameP->unk_99C) {
        for (i = watchGameP->unk_99C - 1; i >= arg1; i--) {
            if (watchGameP->unk_9A0[i] >= 0x1E) {
                watchGameP->unk_99C -= 1;
                watchGameP->unk_9A0[i] = -1;
            } else {
                watchGameP->unk_9A0[i] = watchGameP->unk_9A0[i] + 1;
            }
        }
        arg1 = watchGameP->unk_99C;
    }

    gSPDisplayList(gfx++, normal_texture_init_dl);

    gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);

    gDPSetCombineLERP(gfx++, 0, 0, 0, TEXEL0, PRIMITIVE, 0, TEXEL0, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, TEXEL0, 0);

    temp_s2 = &watchGameP->unk_434[0x15];

    temp_s5 = temp_s2->info[0] >> 2;
    for (i = 0; i < arg1; i++) {
        f32 var_s4 = 0xED + i * 0x10;
        f32 temp_ft0 = watchGameP->unk_9A0[i] - 0xF;
        s32 alpha;

        temp_ft0 = SQ(temp_ft0) * 0.125 + 81.0 - 28.125;
        alpha = 255 - watchGameP->unk_9A0[i] * 0xFF / 30;

        gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, alpha);

        StretchTexTile4(&gfx, temp_s2->info[0], temp_s2->info[1], temp_s2->texs[0], temp_s2->texs[1],
                        temp_s5 * ((watchGameP->unk_9A0[i] >> 1) & 3), 0, temp_s5, temp_s2->info[1], var_s4, temp_ft0,
                        temp_s5, temp_s2->info[1]);
    }

    *gfxP = gfx;
}
#endif

#if VERSION_GW
INCLUDE_RODATA("asm/gw/nonmatchings/main_segment/dm_game_main", RO_DBL_800B2F28_gw);
#endif

#if VERSION_GW
INCLUDE_RODATA("asm/gw/nonmatchings/main_segment/dm_game_main", RO_800B2F2C_gw);
#endif

#if VERSION_GW
INCLUDE_RODATA("asm/gw/nonmatchings/main_segment/dm_game_main", RO_800B2F40_gw);
#endif

#if VERSION_GW
INCLUDE_RODATA("asm/gw/nonmatchings/main_segment/dm_game_main", RO_800B2F4C_gw);
#endif

#if VERSION_GW
INCLUDE_RODATA("asm/gw/nonmatchings/main_segment/dm_game_main", RO_800B2F58_gw);
#endif

#if VERSION_GW
INCLUDE_RODATA("asm/gw/nonmatchings/main_segment/dm_game_main", RO_800B2F64_gw);
#endif

#if VERSION_GW
INCLUDE_RODATA("asm/gw/nonmatchings/main_segment/dm_game_main", RO_800B2F68_gw);
#endif

#if VERSION_GW
INCLUDE_RODATA("asm/gw/nonmatchings/main_segment/dm_game_main", RO_800B2F6C_gw);
#endif

#if VERSION_GW
INCLUDE_RODATA("asm/gw/nonmatchings/main_segment/dm_game_main", RO_800B2F74_gw);
#endif

#if VERSION_GW
INCLUDE_RODATA("asm/gw/nonmatchings/main_segment/dm_game_main", RO_800B2F7C_gw);
#endif

#if VERSION_GW
INCLUDE_RODATA("asm/gw/nonmatchings/main_segment/dm_game_main", RO_800B2F80_gw);
#endif

#if VERSION_GW
INCLUDE_RODATA("asm/gw/nonmatchings/main_segment/dm_game_main", RO_800B2F94_gw);
#endif

#if VERSION_GW
INCLUDE_RODATA("asm/gw/nonmatchings/main_segment/dm_game_main", RO_800B2F98_gw);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", _disp_coin_logo);
#endif

void draw_flash_virus_light(Gfx **gfxP, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

extern u8 tbl_4589[];
extern Color_RGBA8 col_4590[];

#if VERSION_US || VERSION_CN
void draw_flash_virus_light(Gfx **gfxP, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    struct_watchGame *watchGameP = watchGame;
    Gfx *gfx = *gfxP;
    TiTexData *temp = &watchGameP->unk_444[tbl_4589[(watchGameP->unk_424 >> 1) & 3] + 0xC];

    if (arg1 == 0) {
        gSPDisplayList(gfx++, normal_texture_init_dl);
        gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
        gDPSetCombineLERP(gfx++, ENVIRONMENT, PRIMITIVE, TEXEL0, PRIMITIVE, ENVIRONMENT, 0, TEXEL0, 0, ENVIRONMENT,
                          PRIMITIVE, TEXEL0, PRIMITIVE, ENVIRONMENT, 0, TEXEL0, 0);
        gDPSetTextureLUT(gfx++, G_TT_NONE);
        gDPSetEnvColor(gfx++, 255, 255, 255, 255);
    }

    gDPSetPrimColor(gfx++, 0, 0, col_4590[arg4].r, col_4590[arg4].g, col_4590[arg4].b, col_4590[arg4].a);

    tiStretchTexBlock(&gfx, temp, arg1, (f32)arg2, (f32)arg3, 20.0f, 20.0f);
    *gfxP = gfx;
}
#endif

#if VERSION_US || VERSION_CN
void draw_flash_virus_lights(Gfx **gfxP, struct_game_state_data *gameStateDataRef, GameMapCell *mapCells UNUSED) {
    s32 var_t1 = 0;
    s32 var_s5;
    s32 var_s6;
    s32 i;

    switch (gameStateDataRef->unk_00A) {
        case 0x8:
            var_s6 = -6;
            var_s5 = -6;
            break;

        case 0xA:
            var_s6 = -5;
            var_s5 = -5;
            break;

            // var_s6 and var_s5 are undefined
    }

    for (i = 0; i < gameStateDataRef->unk_164; i++) {
        if (gameStateDataRef->unk_0D4[i][2] < 0) {
            continue;
        }

        draw_flash_virus_light(
            gfxP, var_t1,
            var_s5 + gameStateDataRef->unk_006 + (gameStateDataRef->unk_00A * gameStateDataRef->unk_0D4[i][0]),
            var_s6 + gameStateDataRef->unk_008 + (gameStateDataRef->unk_00A * (gameStateDataRef->unk_0D4[i][1] + 1)),
            gameStateDataRef->unk_0D4[i][2]);
        var_t1 = 1;
    }
}
#endif

void func_8006AEFC(struct_watchGame_unk_9D0 *arg0, Gfx **gfxP, s32 arg2, s32 arg3);

#if VERSION_US || VERSION_CN
void func_8006AEFC(struct_watchGame_unk_9D0 *arg0, Gfx **gfxP, s32 arg2, s32 arg3) {
    struct_watchGame *watchGameP = watchGame;
    Gfx *gfx = *gfxP;
    TiTexData *temp_t3;
    TiTexData *temp;

    gSPDisplayList(gfx++, alpha_texture_init_dl);

    temp_t3 = &watchGameP->unk_438[8];
    temp = &watchGameP->unk_438[9];

    StretchAlphaTexTile(&gfx, temp_t3->info[0], (s32)temp_t3->info[1], temp_t3->texs[1], temp_t3->info[0],
                        temp->texs[1], (s32)temp->info[0], 0, 0, (s32)temp_t3->info[0], (s32)temp_t3->info[1],
                        (f32)arg2, (f32)arg3, (f32)temp_t3->info[0], (f32)temp_t3->info[1]);
    draw_time2(&gfx, arg0->unk_14 + 5, arg2 + 0x12, arg3 + 0xE);
    draw_count_number(&gfx, 0, 2, (u32)arg0->unk_18, arg2 + 0x1F, arg3 + 0x23);
    draw_count_number(&gfx, 0, 2, (u32)arg0->unk_1C, arg2 + 0x1F, arg3 + 0x38);
    draw_count_number(&gfx, 0, 7, (u32)arg0->unk_20, arg2 + 9, arg3 + 0x50);

    *gfxP = gfx;
}
#endif

#if VERSION_US || VERSION_CN
void draw_story_board(Gfx **gfxP, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    struct_watchGame *temp_s1 = watchGame;
    Gfx *gfx = *gfxP;

    gSPDisplayList(gfx++, alpha_texture_init_dl);

    if (arg3 != 0) {
        TiTexData *temp_t3 = &temp_s1->unk_43C[0x12];
        TiTexData *temp_t1 = &temp_s1->unk_43C[0x13];

        StretchAlphaTexBlock(&gfx, temp_t3->info[0], temp_t1->info[1], temp_t3->texs[1], temp_t3->info[0],
                             temp_t1->texs[1], temp_t1->info[0], arg1 + 0x78, arg2 + 0xB, temp_t3->info[0],
                             temp_t3->info[1]);

        temp_t3 = &temp_s1->unk_43C[9];
        tiStretchAlphaTexItem(&gfx, temp_t3, &temp_s1->unk_43C[2], 0, 4, evs_story_level, arg1 + 0x8E, arg2 + 0x36,
                              temp_t3->info[0], temp_t3->info[1] >> 2);
    }

    if (arg4 != 0) {
        draw_count_number(&gfx, 0, 7, game_state_data->unk_000, arg1 + 0x81, arg2 + 0x19);
    }

    *gfxP = gfx;
}
#endif

#if VERSION_US || VERSION_CN
const s32 _x_4663[2] = { 0x63, 0xB8 };
const s32 _x_4670[2] = { 0x71, 0xBD };
const s32 _x_4676[2] = { 0x6C, 0xB8 };
const s32 _x_4693[2] = { 0x5E, 0xA2 };

void draw_vsmode_board(Gfx **gfxP, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    struct_watchGame *temp_s6 = watchGame;
    Gfx *gfx = *gfxP;
    s32 pad[3] UNUSED;
    TiTexData *temp_s1;
    TiTexData *temp_s5;
    s32 i;

    gSPDisplayList(gfx++, alpha_texture_init_dl);

    if (arg3 != 0) {
        switch (evs_gamemode) {
            case ENUM_EVS_GAMEMODE_1:
            case ENUM_EVS_GAMEMODE_3:
                temp_s1 = &temp_s6->unk_43C[0x10];
                temp_s5 = &temp_s6->unk_43C[0x11];
                StretchAlphaTexBlock(&gfx, temp_s1->info[0], temp_s1->info[1], temp_s1->texs[1], temp_s1->info[0],
                                     temp_s5->texs[1], temp_s5->info[0], arg1 + 0x5F, arg2 + 9, temp_s1->info[0],
                                     temp_s1->info[1]);

                temp_s1 = &temp_s6->unk_43C[9];
                temp_s5 = &temp_s6->unk_43C[2];
                for (i = 0; i < 2; i++) {
                    tiStretchAlphaTexItem(&gfx, temp_s1, temp_s5, 0, 4, game_state_data[i].unk_16C, arg1 + _x_4663[i],
                                          arg2 + 0xB, temp_s1->info[0], temp_s1->info[1] >> 2);
                }
                break;

            default:
                temp_s1 = &temp_s6->unk_43C[0x14];
                temp_s5 = &temp_s6->unk_43C[0x15];
                StretchAlphaTexBlock(&gfx, temp_s1->info[0], temp_s1->info[1], temp_s1->texs[1], temp_s1->info[0],
                                     temp_s5->texs[1], temp_s5->info[0], arg1 + 0x68, arg2 + 9, temp_s1->info[0],
                                     temp_s1->info[1]);

                for (i = 0; i < 2; i++) {
                    draw_count_number(&gfx, 0, 2, game_state_data[i].unk_026, arg1 + _x_4670[i], arg2 + 0xB);
                }
                break;
        }

        temp_s1 = &temp_s6->unk_43C[0xD];
        temp_s5 = &temp_s6->unk_43C[6];
        StretchAlphaTexBlock(&gfx, temp_s1->info[0], temp_s1->info[1], temp_s1->texs[1], temp_s1->info[0],
                             temp_s5->texs[1], temp_s5->info[0], arg1 + 0x68, (arg2 + 0x19), temp_s1->info[0],
                             temp_s1->info[1]);

        temp_s1 = &temp_s6->unk_43C[0xC];
        temp_s5 = &temp_s6->unk_43C[5];
        for (i = 0; i < 2; i++) {
            tiStretchAlphaTexItem(&gfx, temp_s1, temp_s5, 0, 3, 2 - game_state_data[i].unk_02C, arg1 + _x_4676[i],
                                  arg2 + 0x1B, temp_s1->info[0], temp_s1->info[1] / 3);
        }
    }

    if (evs_gamesel == ENUM_EVS_GAMESEL_3) {
        if (arg3 != 0) {
            temp_s1 = &temp_s6->unk_43C[0xA];
            temp_s5 = &temp_s6->unk_43C[3];
            StretchAlphaTexBlock(&gfx, temp_s1->info[0], temp_s1->info[1], temp_s1->texs[1], temp_s1->info[0],
                                 temp_s5->texs[1], temp_s5->info[0], arg1 + 0x70, arg2 + 0x29, temp_s1->info[0],
                                 temp_s1->info[1]);
        }

        if (arg4 != 0) {
            draw_count_number(&gfx, 0, 7, game_state_data->unk_000, arg1 + 0x90, arg2 + 0x2A);
        }
    } else {
        if (arg3 != 0) {
            temp_s1 = &temp_s6->unk_43C[0xB];
            temp_s5 = &temp_s6->unk_43C[4];
            StretchAlphaTexBlock(&gfx, temp_s1->info[0], temp_s1->info[1], temp_s1->texs[1], temp_s1->info[0],
                                 temp_s5->texs[1], temp_s5->info[0], arg1 + 0x58, arg2 + 0x29, temp_s1->info[0],
                                 temp_s1->info[1]);
        }

        if (arg4 != 0) {
            for (i = 0; i < 2; i++) {
                draw_count_number(&gfx, i + 1, 7, game_state_data[i].unk_000, arg1 + _x_4693[i], arg2 + 0x2A);
            }
        }
    }
    *gfxP = gfx;
}
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", func_8006B850_gw);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", func_8006B9F4_gw);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", func_8006BAEC_gw);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", draw_story_board);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", draw_vsmode_board);
#endif

#if VERSION_US || VERSION_CN
const s32 _rect_4752[][4] = {
    { 0, 0, 0x60, 0x14 }, { 0, 0x14, 0x60, 0x14 }, { 0, 0x28, 8, 0xA0 }, { 0x58, 0x28, 8, 0xA0 }, { 0, 0xC8, 0x60, 8 },
};

void _draw_bottle_10(Gfx **gfxP, const s32 *arg1, const s32 *arg2, s32 arg3) {
    struct_watchGame *watchGameP = watchGame;
    Gfx *gfx = *gfxP;
    TiTexData *temp_s6;
    s32 i;
    s32 j;

    gSPDisplayList(gfx++, normal_texture_init_dl);
    gDPSetCombineMode(gfx++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
    gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, 192);

    temp_s6 = &watchGameP->unk_438[1];
    for (i = 0; i < temp_s6->info[1]; i += 0x2A) {
        for (j = 0; j < arg3; j++) {
            s32 var_t1;

            var_t1 = MIN(0x2A, temp_s6->info[1] - i);
            tiStretchTexTile(&gfx, temp_s6, j, 0, i, temp_s6->info[0], var_t1, arg1[j], arg2[j] + i, temp_s6->info[0],
                             var_t1);
        }
    }

    gSPDisplayList(gfx++, normal_texture_init_dl);

    temp_s6 = &watchGameP->unk_438[0];
    for (i = 0; i < ARRAY_COUNTU(_rect_4752); i++) {
        for (j = 0; j < arg3; j++) {
            tiStretchTexTile(&gfx, temp_s6, j, _rect_4752[i][0], _rect_4752[i][1], _rect_4752[i][2], _rect_4752[i][3],
                             arg1[j] + _rect_4752[i][0], arg2[j] + _rect_4752[i][1], _rect_4752[i][2],
                             _rect_4752[i][3]);
        }
    }

    *gfxP = gfx;
}
#endif

#if VERSION_US || VERSION_CN
void dm_calc_bottle_2p(void) {
    s32 i = (0x14 - watchGame->unk_394) * 8;
    s32 sp8[2] = { 0x1C - i, i + 0xD4 };

    for (i = 0; i < ARRAY_COUNT(sp8); i++) {
        struct_game_state_data *temp = &game_state_data[i];

        temp->unk_006 = sp8[i];
        temp->unk_008 = 0x2E;
    }
}
#endif

#if VERSION_US || VERSION_CN
void dm_draw_bottle_2p(Gfx **gfxP) {
    struct_watchGame *watchGameP = watchGame;
    Gfx *sp30 = *gfxP;
    s32 var_a0 = (0x14 - watchGameP->unk_394) * 8;
    s32 arr[2] UNUSED = { -var_a0, var_a0 };
    s32 sp20[2];
    s32 sp28[2];

    for (var_a0 = 0; var_a0 < 2; var_a0++) {
        struct_game_state_data *temp = &game_state_data[var_a0];

        sp20[var_a0] = temp->unk_006 - 8;
        sp28[var_a0] = temp->unk_008 - 0x1E;
    }

    _draw_bottle_10(&sp30, sp20, sp28, 2);

    *gfxP = sp30;
}
#endif

#if VERSION_US || VERSION_CN
void dm_draw_big_virus(Gfx **gfxP) {
    struct_watchGame *watchGameP = watchGame;
    Gfx *gfx = *gfxP;
    s32 i;

    for (i = 0; i < ANIMES_COUNT; i++) {
        animeState_initDL2(&watchGameP->animeStates[i], &gfx);
        animeState_draw(&watchGameP->animeStates[i], &gfx, watchGameP->unk_3D0[i][0], watchGameP->unk_3D0[i][1],
                        watchGameP->unk_3F4[i], watchGameP->unk_3F4[i]);
        animeSmog_draw(&watchGameP->animeSmogs[i], &gfx, watchGameP->unk_3D0[i][0], watchGameP->unk_3D0[i][1],
                       watchGameP->unk_3F4[i], watchGameP->unk_3F4[i]);
    }

    *gfxP = gfx;
}
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", func_8006C4D0_gw);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", dm_calc_bottle_2p);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", dm_draw_bottle_2p);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", dm_draw_big_virus);
#endif

#if VERSION_US || VERSION_CN
const s32 _pat_4838[6] = { 0, 1, 2, 3, 2, 1 };

void dm_draw_KaSaMaRu(Gfx **gfxP, Mtx **mtxP, Vtx **vtxP, bool messageIsSpeaking, s32 arg4, s32 arg5, s32 arg6,
                      u32 alpha) {
    struct_watchGame *watchGameP = watchGame;
    Gfx *gfx = *gfxP;
    Mtx *mtx = *mtxP;
    Vtx *vtx = *vtxP;
    f32 sp48[4][4];
    TiTexData *temp_a2;
    TiTexData *temp_s4;
    s32 var_v0;
    s32 var_s0;
    s32 var_s3;

    guOrtho(mtx, 0.0f, 320.0f, 240.0f, 0.0f, 1.0f, 10.0f, 1.0f);
    gSPMatrix(gfx++, mtx++, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);

    guTranslate(mtx, 0.0f, 0.0f, -5.0f);
    gSPMatrix(gfx++, mtx++, G_MTX_NOPUSH | G_MTX_MUL | G_MTX_PROJECTION);

    guRotateRPYF(sp48, 0.0f, (1 - arg6) * 0x5A,
                 sinf(2.0 * (WrapF(0.0f, 1.0f, watchGameP->unk_424 * (1.0 / 128.0)) * M_PI)) * 4.0f * arg6);

    var_v0 = WrapI(0, ARRAY_COUNT(_pat_4838), ((watchGameP->unk_424 % 128U) * 9) >> 4);

    if (messageIsSpeaking == false) {
        var_v0 = 0;
    }

    temp_s4 = &watchGameP->unk_448[_pat_4838[var_v0] + 1];
    temp_a2 = &watchGameP->unk_448[0];

    var_s0 = MIN(temp_s4->info[0], temp_a2->info[0]);
    var_s3 = MIN(temp_s4->info[1], temp_a2->info[1]);

    gSPDisplayList(gfx++, alpha_texture_init_dl);
    gSPClearGeometryMode(gfx++, G_ZBUFFER | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN |
                                    G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH | G_CLIPPING);
    gDPSetCombineLERP(gfx++, TEXEL0, 0, PRIMITIVE, 0, TEXEL1, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED);
    gDPSetTexturePersp(gfx++, G_TP_NONE);
    gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, alpha);

    if (arg6 <= 0) {
        sp48[3][0] = arg4 + var_s0;
    } else {
        sp48[3][0] = arg4;
    }
    sp48[3][1] = arg5;

    guMtxF2L(sp48, mtx);
    gSPMatrix(gfx++, mtx++, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    RectAlphaTexTile(&gfx, &vtx, var_s0, var_s3, temp_s4->texs[1], temp_s4->info[0], temp_a2->texs[1], temp_a2->info[0],
                     0, 0, var_s0, var_s3, 0.0f, 0.0f, var_s0, var_s3);

    *vtxP = vtx;
    *mtxP = mtx;
    *gfxP = gfx;
}
#endif

#if VERSION_US || VERSION_CN
void dm_game_graphic_common(struct_game_state_data *gameStateData, s32 arg1, GameMapCell *mapCells) {
    s32 sp28[2];
    TiTexData *temp_v0;
    s32 temp_s6;
    s32 i;

    temp_s6 = 0;
    if (gameStateData->unk_00A == 8) {
        temp_s6 = 1;
    }

    gSPDisplayList(gGfxHead++, normal_texture_init_dl);

    // Draw the pills and virus on the bottle.
    // Does not draw the falling pills nor the next pill.
    temp_v0 = dm_game_get_capsel_tex(temp_s6);
    load_TexTile_4b(temp_v0->texs[1], temp_v0->info[0], temp_v0->info[1], 0, 0, temp_v0->info[0] - 1,
                    temp_v0->info[1] - 1);
    gfxSetScissor(&gGfxHead, GFXSETSCISSOR_INTERLACE_NO, gameStateData->unk_006,
                  gameStateData->unk_008 + gameStateData->unk_00A, gameStateData->unk_00A * 8,
                  gameStateData->unk_00A * 0x10);
    for (i = 0; i < 6; i++) {
        temp_v0 = dm_game_get_capsel_pal(temp_s6, i);
        load_TexPal(temp_v0->texs[0]);
        dm_map_draw(mapCells, i, gameStateData->unk_006, gameStateData->unk_008 - gameStateData->unk_168,
                    gameStateData->unk_00A);
    }

#if VERSION_CN || VERSION_GW
    gDPPipeSync(gGfxHead++);
#endif

    gfxSetScissor(&gGfxHead, GFXSETSCISSOR_INTERLACE_NO, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    if ((gameStateData->unk_04C != 1) && ((gameStateData->unk_04C == 1) || (arg1 != 0) || (aiDebugP1 < 0))) {
        struct_game_state_data_unk_178 *temp;

        if ((visible_fall_point[arg1] == 0) || (gameStateData->unk_00C != GAMESTATEDATA_UNK_00C_4)) {
            return;
        }

        if ((gameStateData->unk_178.unk_2[0] <= 0) || (gameStateData->unk_178.unk_8 == 0)) {
            return;
        }

        temp = &gameStateData->unk_178;

        func_80069ACC(mapCells, temp, sp28);

        gDPSetRenderMode(gGfxHead++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
        gDPSetCombineMode(gGfxHead++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
        gDPSetPrimColor(gGfxHead++, 0, 0, 96, 96, 96, 150);

        for (i = 0; i < 2; i++) {
            s32 temp_t0_2;
            s32 temp_a1_2;
            s32 temp_a2;

            temp_v0 = dm_game_get_capsel_pal(temp_s6, temp->unk_6[i]);
            load_TexPal(temp_v0->texs[0]);
            temp_t0_2 = gameStateData->unk_00A;
            temp_a1_2 = (temp->unk_0[i] * temp_t0_2) + gameStateData->unk_006;
            temp_a2 = (sp28[i] * temp_t0_2) + gameStateData->unk_008;

            gSPTextureRectangle(gGfxHead++, (temp_a1_2 * 4), (temp_a2 * 4), ((temp_a1_2 + temp_t0_2) * 4),
                                ((temp_a2 + temp_t0_2) * 4), G_TX_RENDERTILE, 0x0000, (temp->unk_4[i] * temp_t0_2 << 5),
                                0x0400, 0x0400);
        }

        gDPSetPrimColor(gGfxHead++, 0, 0, 255, 255, 255, 255);
        gDPSetRenderMode(gGfxHead++, G_RM_TEX_EDGE, G_RM_TEX_EDGE2);
    }
}
#endif

#if VERSION_US || VERSION_CN
void dm_game_graphic_p(struct_game_state_data *gameStateData, s32 arg1, GameMapCell *mapCells) {
    struct_watchGame *watchGameP = watchGame;
    s32 sp20[2];
    s32 sp28[2];
    s32 temp_s6;
    s32 i;

    if (gameStateData->unk_020 == 0xD) {
        return;
    }

    temp_s6 = gameStateData->unk_00A == 8;

    dm_game_graphic_common(gameStateData, arg1, mapCells);

    gSPDisplayList(gGfxHead++, normal_texture_init_dl);

    if (dm_calc_capsel_pos(gameStateData, sp20, sp28)) {
        if ((watchGameP->unk_420 != 0) || (gameStateData->unk_178.unk_2[0] <= 0) ||
            ((gameStateData->unk_014 != GAMESTATEDATA_UNK_014_D) &&
             (gameStateData->unk_014 != GAMESTATEDATA_UNK_014_1))) {
            dm_draw_capsel_by_gfx(gameStateData, sp20, sp28);
        }
    }

    if ((gameStateData->unk_184.unk_8 == 0) || (gameStateData->unk_178.unk_2[0] <= 0)) {
        return;
    }

    for (i = 0; i < 2; i++) {
        load_TexPal(dm_game_get_capsel_pal(temp_s6, gameStateData->unk_184.unk_6[i])->texs[0]);
        draw_Tex(gameStateData->unk_184.unk_0[i] * gameStateData->unk_00A + gameStateData->unk_006,
                 (gameStateData->unk_184.unk_2[i] * gameStateData->unk_00A + gameStateData->unk_008) - 0xA,
                 gameStateData->unk_00A, gameStateData->unk_00A, 0,
                 gameStateData->unk_184.unk_4[i] * gameStateData->unk_00A);
    }
}
#endif

#if VERSION_US || VERSION_CN
void dm_game_graphic_1p(struct_game_state_data *gameStateDataRef, s32 arg1, GameMapCell *mapCells) {
    struct_watchGame *temp_s2 = watchGame;
    s32 sp20[2];
    s32 sp28[2];
    s32 i;

    if (gameStateDataRef->unk_020 == 0xD) {
        return;
    }

    dm_game_graphic_common(gameStateDataRef, arg1, mapCells);

    gSPDisplayList(gGfxHead++, normal_texture_init_dl);

    if (dm_calc_capsel_pos(gameStateDataRef, sp20, sp28)) {
        i = 0;
        if ((gameStateDataRef->unk_00C == GAMESTATEDATA_UNK_00C_1) ||
            (gameStateDataRef->unk_00C == GAMESTATEDATA_UNK_00C_2)) {
            i++;
            sp20[1] -= sp20[0];
            sp28[1] -= sp28[0];
            sp20[0] = 0xDA;
            sp28[0] = 0x34;
            sp20[1] += sp20[0];
            sp28[1] += sp28[0];
        } else if (temp_s2->unk_420 != 0) {
            i++;
        }

        if (i != 0) {
            dm_draw_capsel_by_gfx(gameStateDataRef, sp20, sp28);
        }
    }

    if ((gameStateDataRef->unk_184.unk_8 == 0) || (gameStateDataRef->unk_178.unk_2[0] <= 0) ||
        (gameStateDataRef->unk_020 != 1)) {
        return;
    }

    for (i = 0; i < 2; i++) {
        TiTexData *temp = dm_game_get_capsel_pal(0, gameStateDataRef->unk_184.unk_6[i]);

        load_TexPal(temp->texs[0]);
        draw_Tex(0xDA + i * 0xA, 0x34, 0xA, 0xA, 0, gameStateDataRef->unk_184.unk_4[i] * 0xA);
    }
}
#endif

#if VERSION_US || VERSION_CN
void dm_game_graphic_effect(struct_game_state_data *gameStateDataRef, s32 arg1, s32 arg2 UNUSED) {
    struct_watchGame *temp_s4 = watchGame;
    s32 temp_fv0;
    s32 temp_lo;
    s32 temp_s0_2;
    s32 var_v0_4;
    TiTexData *temp_s1;
    TiTexData *other;

    switch (gameStateDataRef->unk_014) {
        case GAMESTATEDATA_UNK_014_0:
            break;

        case GAMESTATEDATA_UNK_014_1:
        case GAMESTATEDATA_UNK_014_5:
        case GAMESTATEDATA_UNK_014_6:
        case GAMESTATEDATA_UNK_014_7:
        case GAMESTATEDATA_UNK_014_8:
        case GAMESTATEDATA_UNK_014_9:
        case GAMESTATEDATA_UNK_014_A:
        case GAMESTATEDATA_UNK_014_B:
        case GAMESTATEDATA_UNK_014_C:
            switch (evs_gamemode) {
                case ENUM_EVS_GAMEMODE_1:
                    draw_flash_virus_lights(&gGfxHead, gameStateDataRef, game_map_data[arg1]);
                    break;

                default:
                    break;
            }
            break;

        default:
            break;
    }

    if (evs_score_flag != 0) {
        scoreNums_draw(&temp_s4->unk_0B8[arg1], &gGfxHead);
    }

    if ((gameStateDataRef->unk_01C == 0x12) && (gameStateDataRef->unk_020 == 1)) {
        temp_s1 = &temp_s4->unk_440[0x1D];
        other = &temp_s4->unk_440[0x1E];

        gSPDisplayList(gGfxHead++, alpha_texture_init_dl);

        gDPSetCombineLERP(gGfxHead++, TEXEL0, 0, PRIMITIVE, 0, TEXEL1, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0,
                          COMBINED);

        temp_fv0 = ((f32)sins(((s16)temp_s4->unk_424 << 9) & 0xFE00) * 0.0038757324f) + 127.0f;

        gDPSetPrimColor(gGfxHead++, 0, 0, 255, 255, 255, temp_fv0);

        temp_fv0 = ((f32)sins(((s16)temp_s4->unk_424 << 0xA) & 0xFC00) * 0.00015258789f);
        StretchAlphaTexBlock(&gGfxHead, temp_s1->info[0], temp_s1->info[1], temp_s1->texs[1], temp_s1->info[0],
                             other->texs[1], other->info[0], gameStateDataRef->unk_006,
                             (gameStateDataRef->unk_008 + temp_fv0 + 0xA0), temp_s1->info[0], temp_s1->info[1]);
    }

    switch (gameStateDataRef->unk_014) {
        case GAMESTATEDATA_UNK_014_3:
            switch (evs_gamemode) {
                case ENUM_EVS_GAMEMODE_3:
                    break;

                case ENUM_EVS_GAMEMODE_2:
                    disp_clear_logo(&gGfxHead, arg1, 0);
                    break;

                default:
                    disp_clear_logo(&gGfxHead, arg1, 1);
                    break;
            }
            break;

        default:
            break;
    }

    switch (gameStateDataRef->unk_014) {
        case 0x13:
            disp_allclear_logo(&gGfxHead, arg1, 0);
            break;

        default:
            break;
    }

    switch (gameStateDataRef->unk_014) {
        case GAMESTATEDATA_UNK_014_15:
            goto block_28;
            break;

        case GAMESTATEDATA_UNK_014_4:
            if (evs_gamemode != ENUM_EVS_GAMEMODE_3) {
            block_28:
                switch (evs_gamemode) {
                    case ENUM_EVS_GAMEMODE_3:
                        if (evs_game_time >= 0x2A30U) {
                            disp_timeover_logo(&gGfxHead, arg1);
                        } else {
                            disp_gameover_logo(&gGfxHead, arg1);
                        }
                        break;

                    default:
                        disp_gameover_logo(&gGfxHead, arg1);
                        break;
                }
            }
            break;

        default:
            break;
    }

    switch (gameStateDataRef->unk_014) {
        case GAMESTATEDATA_UNK_014_10:
        case GAMESTATEDATA_UNK_014_11:
            if (temp_s4->unk_000 == 0) {
                if (gameStateDataRef->unk_04C == 0) {
                    temp_fv0 = sins(((s16)temp_s4->unk_424 << 0xA) & 0xFC00) * 0.0038757324f + 127.0f;
                    temp_s1 = &temp_s4->unk_440[0x1B];
                    other = &temp_s4->unk_440[0x1C];

                    gSPDisplayList(gGfxHead++, alpha_texture_init_dl);

                    gDPSetCombineLERP(gGfxHead++, TEXEL0, 0, PRIMITIVE, 0, TEXEL1, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED,
                                      0, 0, 0, COMBINED);

                    gDPSetPrimColor(gGfxHead++, 0, 0, 255, 255, 255, temp_fv0);

                    StretchAlphaTexBlock(&gGfxHead, temp_s1->info[0], temp_s1->info[1], temp_s1->texs[1],
                                         temp_s1->info[0], other->texs[1], other->info[0],
                                         (f32)gameStateDataRef->unk_006, (f32)(gameStateDataRef->unk_008 + 0x5C),
                                         (f32)temp_s1->info[0], (f32)temp_s1->info[1]);
                }
            }
            disp_retire_logo(&gGfxHead, arg1);
            break;

        case GAMESTATEDATA_UNK_014_17:
            disp_retire_logo(&gGfxHead, arg1);
            break;

        default:
            break;
    }

    switch (gameStateDataRef->unk_014) {
        case GAMESTATEDATA_UNK_014_3:
        case GAMESTATEDATA_UNK_014_4:
        case GAMESTATEDATA_UNK_014_5:
        case GAMESTATEDATA_UNK_014_6:
        case GAMESTATEDATA_UNK_014_7:
        case GAMESTATEDATA_UNK_014_8:
        case GAMESTATEDATA_UNK_014_9:
        case GAMESTATEDATA_UNK_014_A:
        case GAMESTATEDATA_UNK_014_B:
        case GAMESTATEDATA_UNK_014_C:
        case GAMESTATEDATA_UNK_014_14:
        case GAMESTATEDATA_UNK_014_16:
        case GAMESTATEDATA_UNK_014_18:
            if (evs_gamemode == ENUM_EVS_GAMEMODE_3) {
                if (evs_gamesel == ENUM_EVS_GAMESEL_0) {
                    var_v0_4 = 0xA;
                } else {
                    var_v0_4 = 0x4A;
                }
                func_8006AEFC(&temp_s4->unk_9D0[arg1], &gGfxHead, gameStateDataRef->unk_006,
                              gameStateDataRef->unk_008 + var_v0_4);
            }
            break;

        case GAMESTATEDATA_UNK_014_D:
        case GAMESTATEDATA_UNK_014_E:
        case GAMESTATEDATA_UNK_014_F:
        case GAMESTATEDATA_UNK_014_10:
        case GAMESTATEDATA_UNK_014_11:
        case GAMESTATEDATA_UNK_014_12:
        case GAMESTATEDATA_UNK_014_13:
        case GAMESTATEDATA_UNK_014_15:
        case GAMESTATEDATA_UNK_014_17:
            break;

        default:
            break;
    }

    switch (gameStateDataRef->unk_014) {
        case GAMESTATEDATA_UNK_014_5:
        case GAMESTATEDATA_UNK_014_6:
        case GAMESTATEDATA_UNK_014_7:
            disp_win_logo(&gGfxHead, arg1);
            break;

        default:
            break;
    }

    switch (gameStateDataRef->unk_014) {
        case GAMESTATEDATA_UNK_014_8:
        case GAMESTATEDATA_UNK_014_9:
        case GAMESTATEDATA_UNK_014_A:
            disp_lose_logo(&gGfxHead, arg1);
            break;

        default:
            break;
    }

    switch (gameStateDataRef->unk_014) {
        case GAMESTATEDATA_UNK_014_B:
        case GAMESTATEDATA_UNK_014_C:
            disp_draw_logo(&gGfxHead, arg1);
            break;

        default:
            break;
    }

    switch (gameStateDataRef->unk_014) {
        case GAMESTATEDATA_UNK_014_1:
        case GAMESTATEDATA_UNK_014_2:
            temp_lo = temp_s4->unk_3AC / (s32)evs_playcnt;
            temp_s0_2 = (temp_s4->unk_3AC / (s32)evs_playcnt) / 48;

            if (temp_s4->unk_3AC >= 0) {
                if (disp_count_logo(&gGfxHead, arg1, temp_lo) != 0) {
                    temp_s4->unk_3AC = -1;
                    if (arg1 == 0) {
                        dm_snd_play_in_game(SND_INDEX_73);
                    }
                } else {
                    if ((arg1 == 0) && ((temp_s0_2 * 0x30) == (temp_lo - 0x14))) {
                        if (temp_s0_2 < 3) {
                            dm_snd_play_in_game(SND_INDEX_72);
                        }
                    }
                    temp_s4->unk_3AC += 1;
                }
            }
            break;

        default:
            break;
    }

    switch (gameStateDataRef->unk_014) {
        case GAMESTATEDATA_UNK_014_13:
        case GAMESTATEDATA_UNK_014_15:
            if ((evs_gamesel == ENUM_EVS_GAMESEL_0) && (evs_gamemode == ENUM_EVS_GAMEMODE_3) &&
                (temp_s4->unk_888[arg1] == 0)) {
                push_any_key_draw(gameStateDataRef->unk_006 + 8, gameStateDataRef->unk_008 + 0xA0);
            }
            break;

        default:
            break;
    }

    switch (gameStateDataRef->unk_014) {
        case GAMESTATEDATA_UNK_014_D:
            func_80064298(arg1, &gGfxHead, 0);
            break;

        case GAMESTATEDATA_UNK_014_E:
        case GAMESTATEDATA_UNK_014_F:
            func_80064298(arg1, &gGfxHead, 1);
            break;

        default:
            break;
    }

    switch (gameStateDataRef->unk_014) {
        case GAMESTATEDATA_UNK_014_D:
        case GAMESTATEDATA_UNK_014_E:
        case GAMESTATEDATA_UNK_014_F:
            switch (evs_gamesel) {
                case ENUM_EVS_GAMESEL_2:
                    draw_4p_attack_guide_panel(&gGfxHead, temp_s4->unk_8BC, arg1, (s32)gameStateDataRef->unk_006,
                                               gameStateDataRef->unk_008 - 0x24);
                    break;

                default:
                    break;
            }
            break;

        default:
            break;
    }

    switch (gameStateDataRef->unk_014) {
        case GAMESTATEDATA_UNK_014_3:
        case GAMESTATEDATA_UNK_014_4:
        case GAMESTATEDATA_UNK_014_6:
        case GAMESTATEDATA_UNK_014_7:
        case GAMESTATEDATA_UNK_014_9:
        case GAMESTATEDATA_UNK_014_A:
        case GAMESTATEDATA_UNK_014_C:
            if (temp_s4->unk_888[arg1] == 0) {
                func_8006431C(arg1, &gGfxHead);
            }
            break;

        default:
            break;
    }

    gfxSetScissor(&gGfxHead, GFXSETSCISSOR_INTERLACE_NO, 0, 0, 0x140, 0xF0);
}
#endif

#if VERSION_GW
INCLUDE_RODATA("asm/gw/nonmatchings/main_segment/dm_game_main", RO_800B2FC0_gw);
#endif

#if VERSION_GW
INCLUDE_RODATA("asm/gw/nonmatchings/main_segment/dm_game_main", RO_800B2FC8_gw);
#endif

#if VERSION_GW
INCLUDE_RODATA("asm/gw/nonmatchings/main_segment/dm_game_main", RO_800B2FD0_gw);
#endif

#if VERSION_GW
INCLUDE_RODATA("asm/gw/nonmatchings/main_segment/dm_game_main", RO_800B2FD8_gw);
#endif

#if VERSION_GW
INCLUDE_RODATA("asm/gw/nonmatchings/main_segment/dm_game_main", RO_800B2FE0_gw);
#endif

#if VERSION_GW
INCLUDE_RODATA("asm/gw/nonmatchings/main_segment/dm_game_main", RO_800B2FE4_gw);
#endif

#if VERSION_GW
INCLUDE_RODATA("asm/gw/nonmatchings/main_segment/dm_game_main", RO_800B2FE8_gw);
#endif

#if VERSION_GW
INCLUDE_RODATA("asm/gw/nonmatchings/main_segment/dm_game_main", RO_800B2FEC_gw);
#endif

#if VERSION_GW
INCLUDE_RODATA("asm/gw/nonmatchings/main_segment/dm_game_main", RO_800B3030_gw);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", dm_draw_KaSaMaRu);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", dm_game_graphic_common);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", dm_game_graphic_p);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", dm_game_graphic_1p);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", dm_game_graphic_effect);
#endif

#if VERSION_US || VERSION_CN
void func_8006D0E8(void) {
    s32 i;

    for (i = 0; i < MAXCONTROLLERS; i++) {
        joyflg[i] = (0x8000 | 0x4000 | 0x800 | 0x400 | 0x200 | 0x100 | 0x8 | 0x4 | 0x2 | 0x1);
        joygmf[i] = 1;
        joygam[i] = 0;
    }

    joycur1 = evs_keyrept[0];
    joycur2 = evs_keyrept[1];
}
#endif

#if VERSION_US || VERSION_CN
void dm_make_key(void) {
    s32 var_t3;
    s32 i;

    switch (evs_gamesel) {
        case ENUM_EVS_GAMESEL_0:
        case ENUM_EVS_GAMESEL_3:
            var_t3 = 1;
            break;

        case ENUM_EVS_GAMESEL_1:
            var_t3 = 2;
            break;

        default:
            var_t3 = 4;
            break;
    }

    for (i = 0; i < var_t3; i++) {
        if (game_state_data[i].unk_04C == 0) {
            if (joygmf[main_joy[i]] != 0) {
                u16 pressedButton = gControllerPressedButtons[main_joy[i]];
                u16 curButton = joycur[main_joy[i]];

                joygam[i] = (pressedButton & (A_BUTTON | B_BUTTON)) | (curButton & (L_JPAD | R_JPAD)) |
                            (pressedButton & (L_TRIG | R_TRIG));
                if (!(gControllerHoldButtons[main_joy[i]] & (L_JPAD | R_JPAD))) {
                    joygam[i] |= (gControllerHoldButtons[main_joy[i]] & D_JPAD);
                }
            }
        }
    }
}
#endif

#if VERSION_US || VERSION_CN
void key_control_main(struct_game_state_data *gameStateDataRef, GameMapCell *mapCells, s32 arg2, s32 arg3) {
    struct_watchGame *temp_s5 = watchGame;
    s32 sp18[2];
    s32 sp20[2];

    func_80063FF4();

    if ((gameStateDataRef->unk_04C != 1) && ((gameStateDataRef->unk_04C == 1) || (arg2 != 0) || (aiDebugP1 < 0))) {
        if (gControllerPressedButtons[arg3] & (U_CBUTTONS | L_CBUTTONS | R_CBUTTONS | D_CBUTTONS)) {
            visible_fall_point[arg2] = !visible_fall_point[arg2];
        }
    }

    save_visible_fall_point_flag();

    if (gameStateDataRef->unk_00C == GAMESTATEDATA_UNK_00C_3) {
        if ((temp_s5->unk_420 == 0) && dm_calc_capsel_pos(gameStateDataRef, sp18, sp20)) {
            dm_draw_capsel_by_cpu_tentative(gameStateDataRef, sp18, sp20);
        }

        if (gameStateDataRef->unk_04C == 0) {
            if (gControllerHoldButtons[arg3] & R_JPAD) {
                joyCursorFastSet(R_JPAD, arg3);
            }
            if (gControllerHoldButtons[arg3] & L_JPAD) {
                joyCursorFastSet(L_JPAD, arg3);
            }
        }
    } else if (gameStateDataRef->unk_00C == GAMESTATEDATA_UNK_00C_4) {
        if (gameStateDataRef->unk_020 == 1) {
            struct_game_state_data_unk_178 *temp_s0_2;

            if ((gameStateDataRef->unk_04C == 1) ||
                ((gameStateDataRef->unk_04C != 1) && (arg2 == 0) && (aiDebugP1 >= 0))) {
                u16 temp_s1_2 = joygam[arg2];

                aifKeyOut(gameStateDataRef);
                if (temp_s5->unk_000 != 0) {
                    joygam[arg2] = temp_s1_2;
                }
            }

            temp_s0_2 = &gameStateDataRef->unk_178;
            if (joygam[arg2] & B_BUTTON) {
                rotate_capsel(mapCells, temp_s0_2, -1);
            } else if (joygam[arg2] & A_BUTTON) {
                rotate_capsel(mapCells, temp_s0_2, 1);
            }

            if (joygam[arg2] & L_JPAD) {
                translate_capsel(mapCells, gameStateDataRef, -1, arg3);
            } else if (joygam[arg2] & R_JPAD) {
                translate_capsel(mapCells, gameStateDataRef, 1, arg3);
            }

            gameStateDataRef->unk_030 = 1;
            if ((joygam[arg2] & D_JPAD) && (temp_s0_2->unk_2[0] > 0)) {
                s32 val = FallSpeed[gameStateDataRef->unk_02D];

                val = (val >> 1) + (val & 1);

                gameStateDataRef->unk_030 = val;
            }
        } else if (gameStateDataRef->unk_04C == 0) {
            if (gControllerHoldButtons[arg3] & R_JPAD) {
                joyCursorFastSet(R_JPAD, arg3);
            }
            if (gControllerHoldButtons[arg3] & L_JPAD) {
                joyCursorFastSet(L_JPAD, arg3);
            }
        }

        if (temp_s5->unk_420 == 0) {
            if (dm_calc_capsel_pos(gameStateDataRef, sp18, sp20)) {
                dm_draw_capsel_by_cpu_tentative(gameStateDataRef, sp18, sp20);
            }
        }
        dm_capsel_down(gameStateDataRef, mapCells);
        temp_s5->unk_37C[arg2] = 2;
    } else {
        if (temp_s5->unk_37C[arg2] != 0) {
            s32 temp_s3 = gameStateDataRef->unk_178.unk_8;

            gameStateDataRef->unk_178.unk_8 = 1;
            if (temp_s5->unk_420 == 0) {
                if (dm_calc_capsel_pos(gameStateDataRef, sp18, sp20)) {
                    dm_draw_capsel_by_cpu_tentative(gameStateDataRef, sp18, sp20);
                }
            }
            gameStateDataRef->unk_178.unk_8 = temp_s3;
            temp_s5->unk_37C[arg2] -= 1;
        }

        if (gameStateDataRef->unk_04C == 0) {
            joyCursorFastSet(R_JPAD, arg3);
            joyCursorFastSet(L_JPAD, arg3);
        }
    }
}
#endif

#if VERSION_US || VERSION_CN
/**
 * Original name: make_ai_main
 */
void make_ai_main(void) {
    s32 i;
    struct_game_state_data *ptr;

    if (D_800A6FC4 == 0) {
        return;
    }

    switch (evs_gamesel) {
        case ENUM_EVS_GAMESEL_1:
        case ENUM_EVS_GAMESEL_3:
        case ENUM_EVS_GAMESEL_5:
            for (i = 0; i < 2; i++) {
                ptr = &game_state_data[i];

                if (((ptr->unk_04C == 1) || (((ptr->unk_04C != 1) && (i == 0)) && (aiDebugP1 >= 0))) &&
                    (game_state_data[i].unk_020 == 1)) {
                    aifMake(&game_state_data[i]);
                }
            }
            break;

        case ENUM_EVS_GAMESEL_2:
        case ENUM_EVS_GAMESEL_6:
            for (i = 0; i < 4; i++) {
                ptr = &game_state_data[i];

                if (((ptr->unk_04C == 1) || (((ptr->unk_04C != 1) && (i == 0)) && (aiDebugP1 >= 0))) &&
                    (game_state_data[i].unk_020 == 1)) {
                    aifMake(&game_state_data[i]);
                }
            }
            break;

        case ENUM_EVS_GAMESEL_0:
        case ENUM_EVS_GAMESEL_4:
            if ((game_state_data->unk_04C == 1) || (aiDebugP1 >= 0)) {
                aifMake(&game_state_data[0]);
            }
            break;

        default:
            break;
    }
}
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", func_8006DCF8_gw);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", func_8006DD60_gw);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", func_8006DE64_gw);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", make_ai_main);
#endif

#if VERSION_US || VERSION_CN
void dm_effect_make(void) {
    struct_watchGame *watchGameP = watchGame;
    s32 i;

    watchGameP->unk_424++;
    watchGameP->unk_394 = CLAMP(watchGameP->unk_394 + watchGameP->unk_398, 0, 20);

    for (i = 0; i < evs_playcnt; i++) {
        if (game_state_data[i].unk_020 == 1) {
            if ((watchGameP->unk_3C4 != 0) && (evs_game_time < 0x57E04)) {
                evs_game_time++;
            }
            break;
        }
    }
}
#endif

#if VERSION_US || VERSION_CN
void dm_game_init_heap(void) {
    s32 i;

    heapTop = Heap_bufferp;

    BUFFER_CALLOC(&watchGame, heapTop, sizeof(struct_watchGame));

    for (i = 0; i < ARRAY_COUNTU(gameBackup); i++) {
        BUFFER_MALLOC(&gameBackup[i], heapTop, sizeof(struct_gameBackup));
    }

    BUFFER_MALLOC(&gameGeom, heapTop, sizeof(struct_gameGeom));
}
#endif

#if VERSION_US || VERSION_CN
const u16 map_x_table_5383[][4] = {
    { 0x76, 0x76, 0x76, 0x76 },
    { 0x1C, 0xD4, 0x1C, 0xD4 },
    { 0x14, 0x5C, 0xA4, 0xEC },
};
const u8 map_y_table_5384[] = { 0x2E, 0x2E };
const u8 size_table_5385[] = { 0xA, 8 };
#endif

#if VERSION_US || VERSION_CN
void dm_game_init(bool arg0) {
    struct_watchGame *watchGameP = watchGame;
    s32 i;
    s32 j;
    s32 var_s4;
    struct_game_state_data *temp_s0_3;
    struct_game_state_data *var_s0_2;

    if (!arg0 || (watchGameP->unk_000 == 0)) {
        watchGameP->unk_000 = 0;
        watchGameP->unk_004 = (genrand(0xFFFF) + osGetTime()) * 0x10001;
        watchGameP->unk_008 = irandom() + osGetTime();
    }

    sgenrand(watchGameP->unk_004);
    randomseed(watchGameP->unk_008);

    if (!arg0) {
        for (i = 0; i < ARRAY_COUNTU(watchGameP->unk_00C); i++) {
            watchGameP->unk_03C[i] = 0;
            watchGameP->unk_00C[i] = 0;
        }

        watchGameP->unk_06C = 0;
        func_80069160(&watchGameP->unk_070, watchGameP->unk_00C, watchGameP->unk_03C);

        // Redundant condition
        if (!arg0) {
            watchGameP->unk_378 = 0;
        }
    }

    for (i = 0; i < ARRAY_COUNTU(watchGameP->unk_0B8); i++) {
        func_80062E84(&watchGameP->unk_0B8[i]);
    }

    for (i = 0; i < ARRAY_COUNTU(watchGameP->unk_37C); i++) {
        watchGameP->unk_37C[i] = 0;
    }

    watchGameP->unk_38C = 0x1E;
    watchGameP->unk_390 = -1;

    for (i = 0; i < ARRAY_COUNTU(watchGameP->unk_39C); i++) {
        watchGameP->unk_39C[i] = 1;
    }

    watchGameP->unk_3AC = 0;
    watchGameP->unk_3B8 = 0;
    watchGameP->unk_3B4 = 0;
    watchGameP->unk_3C0 = 0;
    watchGameP->unk_3BC = (evs_gamemode == ENUM_EVS_GAMEMODE_1) ? 1 : 3;
    watchGameP->unk_3C4 = main_no != MAIN_NO_5;

    for (i = 0; i < ARRAY_COUNTU(watchGameP->unk_400); i++) {
        watchGameP->unk_400[i] = 0;
        watchGameP->unk_3E8[i] = 1 + i * 120;
        watchGameP->unk_3F4[i] = 1.0f;
    }

    watchGameP->unk_3CC = 0;
    watchGameP->unk_40C = 0;
    watchGameP->unk_410 = 0;
    watchGameP->unk_414 = 0;
    watchGameP->unk_3C8 = 10.0f;

    switch (evs_gamemode) {
        case ENUM_EVS_GAMEMODE_2:
            watchGameP->unk_3C8 = _big_virus_def_wait[game_state_data[0].unk_16C];
            break;

        default:
            break;
    }

    for (i = 0; i < ARRAY_COUNTU(watchGameP->unk_418); i++) {
        watchGameP->unk_418[i] = 0;
    }

    switch (evs_gamesel) {
        case ENUM_EVS_GAMESEL_4:
        case ENUM_EVS_GAMESEL_5:
        case ENUM_EVS_GAMESEL_6:
            watchGameP->unk_41C = 0x708;
            watchGameP->unk_420 = 1;
            break;

        default:
            watchGameP->unk_41C = 0;
            watchGameP->unk_420 = 0;
            break;
    }

    watchGameP->unk_424 = 0;
    watchGameP->unk_428 = 0;

    if (!arg0) {
        for (i = 0; i < ARRAY_COUNT(watchGameP->unk_89C); i++) {
            watchGameP->unk_89C[i] = 0;
        }
    }

    switch (evs_gamemode) {
        case ENUM_EVS_GAMEMODE_2:
        case ENUM_EVS_GAMEMODE_3:
            evs_game_time = 0;
            break;

        default:
            break;
    }

    dm_seq_play_in_game(evs_seqnumb * 2);
    dm_make_magazine();

    for (i = 0; i < ARRAY_COUNT(watchGameP->unk_8DC); i++) {
        for (j = 0; j < ARRAY_COUNT(watchGameP->unk_8DC[i]); j++) {
            watchGameP->unk_8DC[i][j] = -1;
        }
    }

    watchGameP->unk_9BC = 0;
    watchGameP->unk_9C0 = 0;
    watchGameP->unk_9C4 = -1;
    watchGameP->unk_9C8 = -1;
    watchGameP->unk_9CC = -1;
    watchGameP->unk_A28.alpha = 0;
    watchGameP->unk_AA8 = -0x10;
    bzero(watchGameP->unk_AAC, sizeof(watchGameP->unk_AAC));

    switch (evs_gamesel) {
        case ENUM_EVS_GAMESEL_0:
        case ENUM_EVS_GAMESEL_4:
            var_s4 = 0;
            j = 0;
            break;

        case ENUM_EVS_GAMESEL_1:
        case ENUM_EVS_GAMESEL_3:
        case ENUM_EVS_GAMESEL_5:
            var_s4 = 0;
            j = 1;
            break;

        case ENUM_EVS_GAMESEL_2:
        case ENUM_EVS_GAMESEL_6:
            var_s4 = 1;
            j = 2;
            break;

        default:
            break;
    }

    temp_s0_3 = game_state_data;
    for (i = 0; i < ARRAY_COUNT(game_state_data); i++) {
        temp_s0_3[i].unk_006 = map_x_table_5383[j][i];
        temp_s0_3[i].unk_008 = map_y_table_5384[var_s4];
        temp_s0_3[i].unk_00A = size_table_5385[var_s4];
    }

    for (i = 0; i < ARRAY_COUNT(game_state_data); i++) {
        temp_s0_3 = &game_state_data[i];

        temp_s0_3->unk_04B = i;
        temp_s0_3->unk_00C = GAMESTATEDATA_UNK_00C_1;
        temp_s0_3->unk_014 = GAMESTATEDATA_UNK_014_2;
        temp_s0_3->unk_01C = 1;
        temp_s0_3->unk_020 = 1;
        temp_s0_3->unk_025 = 0;
        temp_s0_3->unk_024 = 0;
        temp_s0_3->unk_044 = 0;
        temp_s0_3->unk_048 = 0;
        temp_s0_3->unk_049 = 0;
        temp_s0_3->unk_04A = 0;
        temp_s0_3->unk_02D = GameSpeed[temp_s0_3->unk_02C];
        temp_s0_3->unk_031 = 0;
        temp_s0_3->unk_030 = 1;
        temp_s0_3->unk_032 = 1;
        temp_s0_3->unk_02E = 0;
        temp_s0_3->unk_02F = 0;
        temp_s0_3->unk_034 = 0;
        dm_set_capsel(temp_s0_3);
        temp_s0_3->unk_027 = 0;
        temp_s0_3->unk_029 = 0;
        temp_s0_3->unk_028 = 1;
        temp_s0_3->unk_035 = 0;
        temp_s0_3->unk_036 = 0;
        temp_s0_3->unk_037 = 0;
        temp_s0_3->unk_038 = 0;
        temp_s0_3->unk_03A = 0;
        temp_s0_3->unk_039 = 0;
        temp_s0_3->unk_168 = 0;
        temp_s0_3->unk_170 = 0;
        temp_s0_3->unk_174 = 0;

        switch (evs_gamesel) {
            case ENUM_EVS_GAMESEL_2:
            case ENUM_EVS_GAMESEL_6:
                temp_s0_3->unk_02B = 0xC;
                temp_s0_3->unk_02A = 0;
                break;

            default:
                temp_s0_3->unk_02B = 8;
                temp_s0_3->unk_02A = 2;
                break;
        }

        for (j = 0; j < ARRAY_COUNT(temp_s0_3->unk_03C); j++) {
            temp_s0_3->unk_03C[j] = 0;
        }

        for (j = 0; j < ARRAY_COUNT(temp_s0_3->unk_050); j++) {
            temp_s0_3->unk_050[j].unk_0 = 0;
            temp_s0_3->unk_050[j].unk_2 = 0;
        }

        init_map_all(game_map_data[i]);
    }

    var_s0_2 = game_state_data;
    for (i = 0; i < evs_playcnt; i++) {
        dm_virus_init(evs_gamemode, &var_s0_2[i], virus_map_data[i], virus_map_disp_order[i]);
        if (evs_gamemode == ENUM_EVS_GAMEMODE_1) {
            make_flash_virus_pos(&var_s0_2[i], virus_map_data[i], virus_map_disp_order[i]);
        } else {
            game_state_data[i].unk_164 = 0;
        }
    }

    for (i = 0; i < evs_playcnt - 1; i++) {
        for (j = i + 1; j < evs_playcnt; j++) {
            if (game_state_data[i].unk_026 == game_state_data[j].unk_026) {
                dm_virus_map_copy(virus_map_data[i], virus_map_data[j], virus_map_disp_order[i],
                                  virus_map_disp_order[j]);
                if (evs_gamemode == ENUM_EVS_GAMEMODE_1) {
                    game_state_data[j].unk_164 = game_state_data[i].unk_164;
                    bcopy(&game_state_data[i].unk_0D4, &game_state_data[j].unk_0D4, sizeof(game_state_data[j].unk_0D4));
                    bcopy(&game_state_data[i].unk_140, &game_state_data[j].unk_140,
                          sizeof(struct_game_state_data_unk_140));
                }
                break;
            }
        }
    }

    func_80062920();
    aifGameInit();
    s_hard_mode = 0;
    fool_mode = 0;

    if (evs_story_level == 3) {
        if (evs_story_no == 7) {
            fool_mode = 1;
        } else {
            s_hard_mode = 1;
        }
    }
}
#endif

/**
 * Original name: dm_game_init_static
 */
#if VERSION_US || VERSION_CN
void dm_game_init_static(void) {
    RomOffsetPair *romTableP = _romDataTbl;
    struct_watchGame *watchGameP = watchGame;
    s32 pad[2] UNUSED;
    s32 var_v0;
    s32 i;
    struct_evs_mem_data *temp_a3;
    RomOffset start;
    RomOffset end;
    TiTexData *result;
    RomOffset temp_a0;
    s8 temp;

#if VERSION_US
    start = romTableP[ROMDATATBL_GAME_AL].start;

    watchGameP->unk_3B0 = 0;

    //! FAKE
    watchGameP->unk_878 = var_v0 = 0x7F;
#endif
#if VERSION_CN
    watchGameP->unk_3B0 = 0;

    //! FAKE
    watchGameP->unk_878 = var_v0 = 0x7F;

    start = romTableP[ROMDATATBL_GAME_AL].start;
#endif
    end = romTableP[ROMDATATBL_GAME_AL].end;

    result = tiLoadTexData(&heapTop, start, end);

#if VERSION_US
    start = romTableP[ROMDATATBL_GAME_ITEM].start;
    watchGameP->unk_430 = result;
#endif
#if VERSION_CN
    watchGameP->unk_430 = result;
    start = romTableP[ROMDATATBL_GAME_ITEM].start;
#endif

    end = romTableP[ROMDATATBL_GAME_ITEM].end;
    watchGameP->unk_444 = tiLoadTexData(&heapTop, start, end);

    if (main_no != MAIN_NO_5) {
        watchGameP->unk_448 =
            tiLoadTexData(&heapTop, romTableP[ROMDATATBL_MENU_KASA].start, romTableP[ROMDATATBL_MENU_KASA].end);
    }

#if VERSION_US
    temp_a0 = _romDataTbl[ROMDATATBL_GAME_ETC].start;
    watchGameP->unk_884 = heapTop;
#endif
#if VERSION_CN
    watchGameP->unk_884 = heapTop;
    temp_a0 = _romDataTbl[ROMDATATBL_GAME_ETC].start;
#endif
    heapTop = DecompressRomToRam(temp_a0, heapTop, romTableP[ROMDATATBL_GAME_ETC].end - temp_a0);

    for (i = 0; i < ARRAY_COUNT(watchGameP->unk_8AC); i++) {
        watchGameP->unk_8AC[i] = 0;
    }

    watchGameP->unk_394 = 0;
    watchGameP->unk_398 = 1;
    watchGameP->unk_898 = 2;
    func_8006A938(0);
    watchGameP->unk_9AC = 0;
    watchGameP->unk_9B0 = 0;
    watchGameP->unk_9B4 = 0;
    watchGameP->unk_9B8 = 0;

    replay_record_init_buffer(&heapTop);
    replay_record_init(evs_playcnt);

    temp = 0;
    for (i = 0; i < ARRAY_COUNTU(watchGameP->unk_9D0); i++) {
        func_80062B84(&watchGameP->unk_9D0[i]);
    }

#if VERSION_US
    msgWnd_init2(&watchGameP->unk_A28, &heapTop, 0x100, 0xA, 5, temp, 0);
#endif
#if VERSION_CN
    //! FAKE
    msgWnd_init2(&watchGameP->unk_A28, &heapTop, 0x100, 0xA, var_v0 = 5, temp, 0);
#endif

    watchGameP->unk_A28.xPos = (s32)(SCREEN_WIDTH - (watchGameP->unk_A28.unk_3C * 20)) >> 1;
    watchGameP->unk_A28.yPos = (s32)(SCREEN_HEIGHT - (watchGameP->unk_A28.unk_48 * 2)) >> 1;
    RecWritingMsg_init(&watchGameP->recMessage, &heapTop);

    switch (evs_gamesel) {
        case ENUM_EVS_GAMESEL_4:
            evs_high_score = 56600;
            break;

        case ENUM_EVS_GAMESEL_0:
            temp_a3 = &evs_mem_data[evs_select_name_no[0]];
            if (evs_select_name_no[0] == 8) {
                evs_high_score = 56600;
            } else {
                switch (evs_gamemode) {
                    case ENUM_EVS_GAMEMODE_0:
                        evs_high_score = temp_a3->unk_4C[game_state_data[0].unk_02C].unk_0;
                        break;

                    case ENUM_EVS_GAMEMODE_2:
                        evs_high_score = temp_a3->unk_64[game_state_data[0].unk_16C].unk_0;
                        break;

                    case ENUM_EVS_GAMEMODE_3:
                        evs_high_score = temp_a3->unk_7C[game_state_data[0].unk_16C].unk_0;
                        break;

                    default:
                        break;
                }
            }
            break;

        case ENUM_EVS_GAMESEL_1:
        case ENUM_EVS_GAMESEL_2:
        case ENUM_EVS_GAMESEL_3:
        case ENUM_EVS_GAMESEL_5:
        case ENUM_EVS_GAMESEL_6:
            if (evs_story_flg == 0) {
                evs_high_score = 0;
            }
            break;

        default:
            return;
    }

    switch (evs_gamesel) {
        case ENUM_EVS_GAMESEL_0:
        case ENUM_EVS_GAMESEL_4:
            watchGameP->unk_898 = 1;
            animeState_load(&game_state_data[0].unk_094, &heapTop, CHARANIMEMODE_MARIO);
            animeState_set(&game_state_data[0].unk_094, 2);
            watchGameP->unk_438 =
                tiLoadTexData(&heapTop, romTableP[ROMDATATBL_GAME_P1].start, romTableP[ROMDATATBL_GAME_P1].end);
            watchGameP->unk_434 =
                tiLoadTexData(&heapTop, romTableP[ROMDATATBL_GAME_LS].start, romTableP[ROMDATATBL_GAME_LS].end);

            for (i = 0; i < ARRAY_COUNT(watchGameP->animeStates); i++) {
                animeState_load(&watchGameP->animeStates[i], &heapTop, i + CHARANIMEMODE_VIRUS_R);
            }

            animeSmog_load(&watchGameP->animeSmogs[0], &heapTop);
            for (i = 1; i < ARRAY_COUNT(watchGameP->animeSmogs); i++) {
                animeSmog_init(&watchGameP->animeSmogs[i], &watchGameP->animeSmogs[0]);
            }

            msgWnd_init2(&watchGameP->messageWnd, &heapTop, 0x1000, 0x14, 0xF, 0x28, 0xF);
            watchGameP->messageWnd.unk_24 = 1;
            msgWnd_addStr(&watchGameP->messageWnd, st_staffroll_txt);
            msgWnd_skip(&watchGameP->messageWnd);
            watchGameP->messageWnd.unk_20 = 1;
            watchGameP->messageWnd.unk_1C = 0;
            heapTop = init_coffee_break(heapTop, game_state_data[0].unk_02C);
            break;

        case ENUM_EVS_GAMESEL_1:
        case ENUM_EVS_GAMESEL_3:
        case ENUM_EVS_GAMESEL_5:
            for (i = 0; i < 2; i++) {
                animeState_load(&game_state_data[i].unk_094, &heapTop, game_state_data[i].unk_090);
            }

            if (evs_story_flg == 0) {
                for (i = 0; i < ARRAY_COUNT(watchGameP->unk_8B4); i++) {
                    watchGameP->unk_8B4[i] = 0;
                }

                switch (evs_gamesel) {
                    case ENUM_EVS_GAMESEL_1:
                        for (i = 0; i < ARRAY_COUNT(watchGameP->unk_8B4); i++) {
                            watchGameP->unk_8B4[i] = evs_mem_data[evs_select_name_no[i]].unk_A8[0];
                        }
                        break;

                    default:
                        break;
                }
            }

            watchGameP->unk_438 =
                tiLoadTexData(&heapTop, romTableP[ROMDATATBL_GAME_P1].start, romTableP[ROMDATATBL_GAME_P1].end);
            watchGameP->unk_43C =
                tiLoadTexData(&heapTop, romTableP[ROMDATATBL_GAME_P2].start, romTableP[ROMDATATBL_GAME_P2].end);
            break;

        case ENUM_EVS_GAMESEL_2:
        case ENUM_EVS_GAMESEL_6:
            watchGameP->unk_438 =
                tiLoadTexData(&heapTop, romTableP[ROMDATATBL_GAME_P1].start, romTableP[ROMDATATBL_GAME_P1].end);
            watchGameP->unk_440 =
                tiLoadTexData(&heapTop, romTableP[ROMDATATBL_GAME_P4].start, romTableP[ROMDATATBL_GAME_P4].end);

            for (i = 0; i < ARRAY_COUNT(game_state_data); i++) {
                animeState_load(&game_state_data[i].unk_094, &heapTop, game_state_data[i].unk_090);
            }

            for (i = 0; i < ARRAY_COUNT(watchGameP->unk_8CC); i++) {
                watchGameP->unk_8CC[i] = 0;
            }

            for (i = 0; i < ARRAY_COUNT(watchGameP->unk_8CC); i++) {
                watchGameP->unk_8CC[game_state_data[i].unk_04F]++;
            }

            watchGameP->unk_8BC = 0;

            for (i = 0; i < ARRAY_COUNT(game_state_data); i++) {
                if (game_state_data[i].unk_04C == 0) {
                    watchGameP->unk_8BC++;
                }
            }

            if (watchGameP->unk_8CC[0] == 1) {
                if (watchGameP->unk_8CC[1] == watchGameP->unk_8CC[0]) {
                    if (watchGameP->unk_8CC[2] == watchGameP->unk_8CC[1]) {
                        if (watchGameP->unk_8CC[3] == watchGameP->unk_8CC[2]) {
                            watchGameP->unk_8C0 = 0;
                            return;
                        }
                    }
                }
            }

            watchGameP->unk_8C0 = 1;
            watchGameP->unk_8C8 = 0;
            watchGameP->unk_8C4 = 0;

            for (i = 0; i < ARRAY_COUNT(game_state_data); i++) {
                if (game_state_data[i].unk_04F == 0) {
                    watchGameP->unk_8C4 |= (1 << i);
                }
            }

            for (i = 0; i < ARRAY_COUNT(game_state_data); i++) {
                if (game_state_data[i].unk_04F == 1) {
                    watchGameP->unk_8C8 |= (1 << i);
                }
            }
            break;

        default:
            break;
    }
}
#endif

#if VERSION_US || VERSION_CN
void dm_game_init_snap_bg(void) {
    struct_watchGame *watchGameP = watchGame;

    BUFFER_MALLOC64(&watchGameP->unk_87C, heapTop, sizeof(u16) * 0x13380);
    watchGameP->unk_880 = 0;

    switch (evs_gamesel) {
        case ENUM_EVS_GAMESEL_0:
        case ENUM_EVS_GAMESEL_4:
            break;

        default:
            heapTop = story_bg_init((BgRomDataIndex)story_proc_no, heapTop);
            break;
    }
}
#endif

#if VERSION_US || VERSION_CN
const s16 _bgPos_5792[7][2] = {
    { 0, 0 }, { 0x50, 0 }, { 0xA0, 0 }, { 0xF0, 0 }, { 0x78, 0x78 }, { 0xC8, 0x78 }, { 0x118, 0x78 },
};

#define UNK_SNAP_BG_LEN 3

const s16 _panelPos_5793[3][2] = { { 0xD4, 0x67 }, { 0xD4, 0x91 }, { 0xD4, 0xBB } };
static_assert(ARRAY_COUNT(_panelPos_5793) == UNK_SNAP_BG_LEN, "");

const char _bgTex_5794[3] = { 0xF, 0x10, 0x11 };
static_assert(ARRAY_COUNT(_bgTex_5794) == UNK_SNAP_BG_LEN, "");

const char _magTex_5795[3] = { 0x12, 0x13, 0x14 };
static_assert(ARRAY_COUNT(_magTex_5795) == UNK_SNAP_BG_LEN, "");

const char _scrTex_5796[3] = { 6, 6, 8 };
static_assert(ARRAY_COUNT(_scrTex_5796) == UNK_SNAP_BG_LEN, "");

const char _panelTex_5797[4][3] = {
    { 0xE, 0xC, 0xD },
    { 0xB, 0xC, 0xD },
    { 0xB, 0xC, 0xD },
    { 0, 0, 0 },
};
static_assert(ARRAY_COUNT(_panelTex_5797[0]) == UNK_SNAP_BG_LEN, "");

const s32 tbl_5867[2][2] = { { 0xC, 0x14 }, { 0xD, 0x15 } };

void dm_game_draw_snap_bg(Gfx **gfxP, Mtx **mtxP UNUSED, Vtx **vtxP UNUSED, s32 arg3) {
    struct_watchGame *temp_s7 = watchGame;
    Gfx *gfx = *gfxP;
    TiTexData *temp_s1;
    TiTexData *temp_s2;
    s32 var_s6;
    s32 var_s0_2;
    s32 i;

    if (temp_s7->unk_880 != 0) {
        gDPSetColorImage(gfx++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 328, osVirtualToPhysical(temp_s7->unk_87C));
    }

    switch (evs_gamesel) {
        case ENUM_EVS_GAMESEL_0:
        case ENUM_EVS_GAMESEL_4:
            switch (evs_gamemode) {
                case ENUM_EVS_GAMEMODE_0:
                    var_s6 = 0;
                    break;

                case ENUM_EVS_GAMEMODE_2:
                    var_s6 = 1;
                    break;

                case ENUM_EVS_GAMEMODE_3:
                    var_s6 = 2;
                    break;

                default:
                    break;
            }

            gSPDisplayList(gfx++, normal_texture_init_dl);

            temp_s1 = &temp_s7->unk_434[_bgTex_5794[var_s6]];

            for (i = 0; i < ARRAY_COUNTU(_bgPos_5792); i++) {
                tiStretchTexTile(&gfx, temp_s1, 0, 0, 0, temp_s1->info[0], temp_s1->info[1], _bgPos_5792[i][0],
                                 _bgPos_5792[i][1], temp_s1->info[0], temp_s1->info[1]);
            }

            temp_s1 = &temp_s7->unk_434[_magTex_5795[var_s6]];
            tiStretchTexTile(&gfx, temp_s1, 0, 0, 0, temp_s1->info[0], temp_s1->info[1], 0.0f, 120.0f, temp_s1->info[0],
                             temp_s1->info[1]);

            if (arg3 != 0) {
                gSPDisplayList(gfx++, alpha_texture_init_dl);

                temp_s1 = &temp_s7->unk_434[9];
                temp_s2 = &temp_s7->unk_434[2];

                var_s0_2 = MIN(temp_s1->info[0], temp_s2->info[0]);

                StretchAlphaTexTile(&gfx, var_s0_2, temp_s1->info[1], temp_s1->texs[1], temp_s1->info[0],
                                    temp_s2->texs[1], *temp_s2->info, 0, 0, var_s0_2, temp_s1->info[1], 202.0f, 12.0f,
                                    var_s0_2, temp_s1->info[1]);

                temp_s1 = &temp_s7->unk_434[_scrTex_5796[var_s6]];
                temp_s2 = &temp_s7->unk_434[1];

                var_s0_2 = MIN(temp_s1->info[0], temp_s2->info[0]);

                StretchAlphaTexTile(&gfx, var_s0_2, temp_s1->info[1], temp_s1->texs[1], temp_s1->info[0],
                                    temp_s2->texs[1], temp_s2->info[0], 0, 0, var_s0_2, temp_s1->info[1], 11.0f, 17.0f,
                                    var_s0_2, temp_s1->info[1]);

                temp_s2 = &temp_s7->unk_434[4];

                for (i = 0; i < ARRAY_COUNTU(_panelTex_5797[var_s6]); i++) {
                    temp_s1 = &temp_s7->unk_434[_panelTex_5797[var_s6][i]];

                    var_s0_2 = MIN(temp_s1->info[0], temp_s2->info[0]);

                    StretchAlphaTexTile(&gfx, var_s0_2, temp_s1->info[1], temp_s1->texs[1], temp_s1->info[0],
                                        temp_s2->texs[1], temp_s2->info[0], 0, 0, var_s0_2, temp_s1->info[1],
                                        _panelPos_5793[i][0], _panelPos_5793[i][1], var_s0_2, temp_s1->info[1]);
                }

                switch (evs_gamemode) {
                    case ENUM_EVS_GAMEMODE_2:
                    case ENUM_EVS_GAMEMODE_3:
                        temp_s1 = &temp_s7->unk_434[0xA];
                        temp_s2 = &temp_s7->unk_434[3];
                        tiStretchAlphaTexItem(&gfx, temp_s1, temp_s2, 0, 3, game_state_data->unk_16C, 232.0f, 120.0f,
                                              48.0f, 16.0f);
                        break;

                    default:
                        break;
                }

                temp_s1 = &temp_s7->unk_434[5];
                temp_s2 = &temp_s7->unk_434[0];
                tiStretchAlphaTexItem(&gfx, temp_s1, temp_s2, 0, 3, game_state_data->unk_02C, 232.0f, 162.0f, 48.0f,
                                      16.0f);
            }

            gSPDisplayList(gfx++, normal_texture_init_dl);

            gDPSetCombineMode(gfx++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
            gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
            gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, 96);

            temp_s1 = &temp_s7->unk_438[1];

            for (i = 0; i < 2; i++) {
                tiStretchTexBlock(&gfx, temp_s1, 0, 110.0f, 16.0f, temp_s1->info[0], temp_s1->info[1]);
            }

            temp_s1 = &temp_s7->unk_438[0];
            for (i = 0; i < 2; i++) {
                tiCopyTexBlock(&gfx, temp_s1, 0, 0x6E, 0x10);
            }
            break;

        case ENUM_EVS_GAMESEL_2:
        case ENUM_EVS_GAMESEL_6:
            story_bg_proc(&gfx);

            gSPDisplayList(gfx++, normal_texture_init_dl);

            gDPSetCombineMode(gfx++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
            gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
            gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, 192);

            temp_s1 = &temp_s7->unk_440[1];

            for (i = 0; i < 4; i++) {
                tiStretchTexBlock(&gfx, temp_s1, 0, _posP4Bottle[i][0] + RO_800B1D7C[0],
                                  _posP4Bottle[i][1] + RO_800B1D7C[1], temp_s1->info[0], temp_s1->info[1]);
            }

            temp_s1 = &temp_s7->unk_440[0];

            for (i = 0; i < 4; i++) {
                tiCopyTexBlock(&gfx, temp_s1, 0, _posP4Bottle[i][0], _posP4Bottle[i][1]);
            }

            if (arg3 != 0) {
                gSPDisplayList(gfx++, normal_texture_init_dl);

                temp_s1 = &temp_s7->unk_440[8];
                for (i = 0; i < 4; i++) {
                    tiStretchTexBlock(&gfx, temp_s1, 0, _posP4CharBase[i][0], _posP4CharBase[i][1], temp_s1->info[0],
                                      temp_s1->info[1]);
                }

                gSPDisplayList(gfx++, alpha_texture_init_dl);

                if ((evs_story_flg != 0) || (temp_s7->unk_8C0 == 0)) {
                    if (evs_gamemode == ENUM_EVS_GAMEMODE_1) {
                        temp_s1 = &temp_s7->unk_440[0xB];
                        temp_s2 = &temp_s7->unk_440[0x13];
                    } else {
                        temp_s1 = &temp_s7->unk_440[0x19];
                        temp_s2 = &temp_s7->unk_440[0x1A];
                    }

                    var_s0_2 = MIN(temp_s1->info[0], temp_s2->info[0]);

                    for (i = 0; i < 4; i++) {
                        StretchAlphaTexBlock(&gfx, var_s0_2, temp_s1->info[1], temp_s1->texs[1], temp_s1->info[0],
                                             temp_s2->texs[1], temp_s2->info[0], _posP4CharBase[i][0] + 0x19,
                                             _posP4CharBase[i][1], var_s0_2, temp_s1->info[1]);
                    }
                }

                if (evs_story_flg != 0) {
                    temp_s1 = &temp_s7->unk_440[0xF];
                    temp_s2 = &temp_s7->unk_440[0x17];

                    var_s0_2 = MIN(temp_s1->info[0], temp_s2->info[0]);

                    StretchAlphaTexBlock(&gfx, var_s0_2, temp_s1->info[1], temp_s1->texs[1], temp_s1->info[0],
                                         temp_s2->texs[1], temp_s1->info[0], 16.0f, 11.0f, var_s0_2, temp_s1->info[1]);
                } else if (temp_s7->unk_8C0 != 0) {
                    for (i = 0; i < 4; i++) {
                        s32 temp_v0_9;

                        temp_v0_9 = game_state_data[i].unk_04F != 0;
                        temp_s1 = &temp_s7->unk_440[tbl_5867[temp_v0_9][0]];
                        temp_s2 = &temp_s7->unk_440[tbl_5867[temp_v0_9][1]];

                        var_s0_2 = MIN(temp_s1->info[0], temp_s2->info[0]);

                        StretchAlphaTexBlock(&gfx, var_s0_2, temp_s1->info[1], temp_s1->texs[1], temp_s1->info[0],
                                             temp_s2->texs[1], temp_s1->info[0], _posP4CharBase[i][0] + 0x19,
                                             _posP4CharBase[i][1], var_s0_2, temp_s1->info[1]);
                    }

                    //! FAKE:
                    temp_s1 = temp_s7->unk_440 + 2 + evs_vs_count - 1;

                    CopyTexBlock8(&gfx, temp_s1->texs[0], temp_s1->texs[1], 0x10, 8, temp_s1->info[0],
                                  temp_s1->info[1]);
                } else {
                    //! FAKE:
                    temp_s1 = temp_s7->unk_440 + 5 + evs_vs_count - 1;

                    CopyTexBlock8(&gfx, temp_s1->texs[0], temp_s1->texs[1], 0x10, 0xB, temp_s1->info[0],
                                  temp_s1->info[1]);
                }
            }
            break;

        case ENUM_EVS_GAMESEL_1:
        case ENUM_EVS_GAMESEL_3:
        case ENUM_EVS_GAMESEL_5:
            story_bg_proc(&gfx);
            if (arg3 != 0) {
                gSPDisplayList(gfx++, alpha_texture_init_dl);

                if (evs_story_flg != 0) {
                    temp_s1 = &temp_s7->unk_43C[8];
                } else {
                    temp_s1 = &temp_s7->unk_43C[0xE];
                }
                temp_s2 = &temp_s7->unk_43C[0];

                StretchAlphaTexBlock(&gfx, temp_s1->info[0], temp_s1->info[1], temp_s1->texs[1], temp_s1->info[0],
                                     temp_s2->texs[1], temp_s2->info[0], 114.0f, 150.0f, temp_s1->info[0],
                                     temp_s1->info[1]);
                if (evs_story_flg != 0) {
                    draw_count_number(&gfx, 0, 1, evs_story_no, 0xB0, 0x98);
                }
            }
            break;

        default:
            break;
    }

    *gfxP = gfx;
}
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", dm_effect_make);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", dm_game_init_heap);
#endif

#if VERSION_GW
INCLUDE_RODATA("asm/gw/nonmatchings/main_segment/dm_game_main", RO_800B30F4_gw);
#endif

#if VERSION_GW
INCLUDE_RODATA("asm/gw/nonmatchings/main_segment/dm_game_main", RO_800B310C_gw);
#endif

#if VERSION_GW
INCLUDE_RODATA("asm/gw/nonmatchings/main_segment/dm_game_main", RO_800B3110_gw);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", dm_game_init);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", dm_game_init_static);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", dm_game_init_snap_bg);
#endif

#if VERSION_GW
INCLUDE_RODATA("asm/gw/nonmatchings/main_segment/dm_game_main", RO_800B3174_gw);
#endif

#if VERSION_GW
INCLUDE_RODATA("asm/gw/nonmatchings/main_segment/dm_game_main", RO_800B3190_gw);
#endif

#if VERSION_GW
INCLUDE_RODATA("asm/gw/nonmatchings/main_segment/dm_game_main", RO_800B319C_gw);
#endif

#if VERSION_GW
INCLUDE_RODATA("asm/gw/nonmatchings/main_segment/dm_game_main", RO_800B31A0_gw);
#endif

#if VERSION_GW
INCLUDE_RODATA("asm/gw/nonmatchings/main_segment/dm_game_main", RO_800B31A4_gw);
#endif

#if VERSION_GW
INCLUDE_RODATA("asm/gw/nonmatchings/main_segment/dm_game_main", RO_800B31A8_gw);
#endif

#if VERSION_GW
INCLUDE_RODATA("asm/gw/nonmatchings/main_segment/dm_game_main", RO_800B31B4_gw);
#endif

#if VERSION_GW
INCLUDE_RODATA("asm/gw/nonmatchings/main_segment/dm_game_main", RO_800B31B8_gw);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", dm_game_draw_snap_bg);
#endif

#if VERSION_US || VERSION_CN
void func_8006F628(Gfx **gfxP) {
    Gfx *gfx = *gfxP;

    CopyTexBlock16(&gfx, watchGame->unk_87C, 0, 0, 0x148, 0xF0);
    *gfxP = gfx;
}
#endif

#if VERSION_US || VERSION_CN
enum_main_no dm_game_main(NNSched *sc) {
    OSMesgQueue scMQ;
    OSMesg scMsgBuf[NN_SC_MAX_MESGS];
    NNScClient scClient;
    enum_main_no ret;
    bool var_s2 = true;
    s32 var_s4;
    struct_watchGame *watchGameP;

    func_8006D0E8();

    osCreateMesgQueue(&scMQ, scMsgBuf, ARRAY_COUNT(scMsgBuf));
    nnScAddClient(sc, &scClient, &scMQ);
    func_80040A64();

    dm_game_init_heap();
    watchGameP = watchGame;
    dm_game_init_static();
    dm_game_init_snap_bg();
    watchGameP->unk_880 = 1;
    dm_game_init(false);
    backup_game_state(0);
    D_800A6FC4 = 1;
    gGfxHead = gGfxGlist[gfx_gtask_no];

    while (var_s2 || (watchGameP->unk_38C != 0x1E)) {
        s16 *sp50;

        osRecvMesg(&scMQ, (OSMesg *)&sp50, OS_MESG_BLOCK);

#ifdef NN_SC_PERF
        if (D_80092F10_cn) {
            joyProcCore();
            graphic_no = GRAPHIC_NO_0;
            dm_audio_update();

            continue;
        }
#endif

        if (!MQ_IS_EMPTY(&scMQ)) {
            D_80088105 = 1;
        }

        if (*sp50 != 1) {
            continue;
        }

        if (!var_s2) {
            if (watchGameP->unk_390 < 0) {
                watchGameP->unk_390 = -watchGameP->unk_390;
            }
        } else {
            u16 temp_s1;
            s32 i;

#ifdef NN_SC_PERF
            if (gControllerPressedButtons[main_joy[0]] & Z_TRIG) {
                D_80088105 = 0;
                D_800BEF08_cn ^= 1;
            }
            func_8002BC30_cn(ENUM_8002BA98_CN_ARG0_1);
#endif

            temp_s1 = gControllerPressedButtons[0];

            for (i = 0; var_s2 && (i < evs_gamespeed); i++) {
                if (i != 0) {
                    gControllerPressedButtons[0] = 0;
                }
                var_s4 = dm_game_main2();
                var_s2 = var_s4 == 0;
            }

            gControllerPressedButtons[0] = temp_s1;

#ifdef NN_SC_PERF
            func_8002BD04_cn();
#endif

            if (watchGameP->unk_420 != 0) {
                dm_seq_set_volume(0x40);
            }

            dm_audio_update();
            dm_game_graphic_onDoneSawp();

#ifdef NN_SC_PERF
            if (D_80092F10_cn) {
                graphic_no = GRAPHIC_NO_0;
                continue;
            }
#endif
            graphic_no = GRAPHIC_NO_4;
        }
    }

    D_800A6FC4 = 0;
    watchGameP->unk_878 = 0xF;

    while (watchGameP->unk_878 != 0) {
        osRecvMesg(&scMQ, NULL, OS_MESG_BLOCK);
        dm_audio_update();
    }

    graphic_no = GRAPHIC_NO_0;
    memset(gFramebuffers[gCurrentFramebufferIndex ^ 1], 0xFF, sizeof(gFramebuffers[gCurrentFramebufferIndex ^ 1]));
    dm_audio_stop();

    while (!dm_audio_is_stopped() || (pendingGFX != 0)) {
        osRecvMesg(&scMQ, NULL, OS_MESG_BLOCK);
        dm_audio_update();
    }

    ret = dm_game_main3(var_s4);
    while (func_80040BA4() != 0) {
        osRecvMesg(&scMQ, NULL, OS_MESG_BLOCK);
    }

    func_80040AE4();
    nnScRemoveClient(sc, &scClient);

    return ret;
}
#endif

#if VERSION_US || VERSION_CN
s32 dm_game_main2(void) {
    struct_watchGame *temp_s3 = watchGame;
    s32 var_s1 = 0;
    s32 var_s4_2;
    s32 var_s0;

    if (temp_s3->unk_3B8 != 0) {
        dm_seq_play_in_game((evs_seqnumb * 2) + 1);
        temp_s3->unk_3B8 = 0;
    }

    dm_effect_make();
    RecWritingMsg_calc(&temp_s3->recMessage);

    switch (evs_gamesel) {
        case ENUM_EVS_GAMESEL_0:
            if (temp_s3->unk_9AC > 0) {
                if (gControllerHoldButtons[main_joy[0]] & (A_BUTTON | B_BUTTON)) {
                    temp_s3->messageWnd.unk_5C = 1.0f / 8.0f;
                } else {
                    temp_s3->messageWnd.unk_5C = 1.0f / 60.0f;
                }
                msgWnd_update(&temp_s3->messageWnd);

                switch (temp_s3->unk_9AC) {
                    case 0x1:
                        if (!(gControllerPressedButtons[main_joy[0]] & START_BUTTON)) {
                            if (!msgWnd_isScroll(&temp_s3->messageWnd)) {
                                temp_s3->unk_9AC = 2;
                            }
                        } else {
                            temp_s3->unk_9AC = 0;
                        }
                        break;

                    case 0x2:
                        if (temp_s3->unk_9B0 < 0x168) {
                            temp_s3->unk_9B0++;
                        } else if (gControllerPressedButtons[main_joy[0]] & ANY_BUTTON) {
                            temp_s3->unk_9AC = 0;
                        }
                        break;
                }
                if (temp_s3->unk_9AC == 0) {
                    dm_seq_play_in_game(evs_seqnumb * 2);
                }
                var_s4_2 = 0;
            }

            if (temp_s3->unk_9AC <= 0) {
                var_s4_2 = dm_game_main_1p();

                switch (var_s4_2) {
                    case 1:
                        var_s0 = game_state_data[0].unk_026;
                        if ((var_s0 == 0x15) || (var_s0 == 0x18) ||
                            ((var_s0 >= 0x1E) && (var_s0 == ((var_s0 / 5) * 5)))) {
                            temp_s3->unk_9AC = 1;
                            if (var_s0 >= 0x1E) {
                                if (var_s0 < 0x28) {
                                    temp_s3->unk_9B4 = 1;
                                } else {
                                    temp_s3->unk_9B4 = 2;
                                }
                            } else {
                                temp_s3->unk_9B4 = 0;
                            }

                            if (var_s0 < 0x1E) {
                                temp_s3->unk_9B8 = (var_s0 - 0x15) / 3;
                            } else {
                                temp_s3->unk_9B8 = (var_s0 / 5) & 1;
                            }
                        }

                        if (temp_s3->unk_9AC == 1) {
                            temp_s3->unk_9B0 = 0;
                            init_coffee_break_cnt();
                            msgWnd_clear(&temp_s3->messageWnd);
                            msgWnd_addStr(&temp_s3->messageWnd, st_staffroll_txt);
                            msgWnd_skip(&temp_s3->messageWnd);
                        }

                        if (game_state_data[0].unk_026 < 0x63U) {
                            game_state_data[0].unk_026++;
                        }
                        break;

                    case 2:
                        game_state_data[0].unk_000 = 0;
                        break;

                    case 9:
                        var_s4_2 = 0;
                        dm_game_init(true);
                        break;
                }

                switch (var_s4_2) {
                    case 1:
                    case 2:
                        var_s4_2 = 0;
                        dm_game_init(true);
                        animeState_set(&game_state_data[0].unk_094, 2);

                        for (var_s0 = 0; var_s0 < 3; var_s0++) {
                            animeState_set(&temp_s3->animeStates[var_s0], 0);
                            animeSmog_stop(&temp_s3->animeSmogs[var_s0]);
                        }

                        var_s0 = temp_s3->unk_9AC;
                        temp_s3->unk_9AC = 0;
                        backup_game_state(0);
                        temp_s3->unk_9AC = var_s0;
                        if (temp_s3->unk_9AC > 0) {
                            dm_seq_play_in_game(SEQ_INDEX_23);
                        }
                        break;
                }
            }
            break;

        case ENUM_EVS_GAMESEL_1:
        case ENUM_EVS_GAMESEL_3:
            var_s4_2 = dm_game_main_2p();

            for (var_s0 = 0; var_s0 < 2; var_s0++) {
                if (evs_story_flg != 0) {
                    if (temp_s3->unk_89C[var_s0] > 0) {
                        var_s1 = 1;
                    }
                } else if (temp_s3->unk_89C[var_s0] == evs_vs_count) {
                    var_s1 = 1;
                }
            }

            switch (var_s4_2) {
                case -1:
                    if (var_s1 == 0) {
                        var_s4_2 = 0;
                        switch (evs_gamemode) {
                            case ENUM_EVS_GAMEMODE_3:
                                for (var_s0 = 0; var_s0 < 2; var_s0++) {
                                    game_state_data[var_s0].unk_000 = 0;
                                }
                                break;

                            default:
                                break;
                        }

                        dm_game_init(true);

                        for (var_s0 = 0; var_s0 < 2; var_s0++) {
                            animeState_set(&game_state_data[var_s0].unk_094, 0);
                        }

                        backup_game_state(0);
                    }
                    break;

                case 2:
                    var_s4_2 = 0;
                    for (var_s0 = 0; var_s0 < 2; var_s0++) {
                        game_state_data[var_s0].unk_000 = 0;
                    }

                    dm_game_init(false);

                    for (var_s0 = 0; var_s0 < 2; var_s0++) {
                        animeState_set(&game_state_data[var_s0].unk_094, 0);
                    }

                    backup_game_state(0);
                    break;

                case 9:
                    var_s4_2 = 0;
                    dm_game_init(true);
                    break;

                default:
                    break;
            }
            break;

        case ENUM_EVS_GAMESEL_2:
            var_s4_2 = dm_game_main_4p();

            for (var_s0 = 0; var_s0 < 4; var_s0++) {
                if (evs_story_flg != 0) {
                    if (temp_s3->unk_89C[var_s0] > 0) {
                        var_s1 = 1;
                    }
                } else if (temp_s3->unk_89C[var_s0] == evs_vs_count) {
                    var_s1 = 1;
                }
            }

            switch (var_s4_2) {
                case -1:
                    if (var_s1 == 0) {
                        var_s4_2 = 0;
                        dm_game_init(true);
                        for (var_s0 = 0; var_s0 < 4; var_s0++) {
                            animeState_set(&game_state_data[var_s0].unk_094, 0);
                        }
                        backup_game_state(0);
                    }
                    break;

                case 2:
                    var_s4_2 = 0;
                    for (var_s0 = 0; var_s0 < 2; var_s0++) {
                        game_state_data[var_s0].unk_000 = 0;
                    }

                    dm_game_init(false);

                    var_s0 = 0;
                    for (var_s0 = 0; var_s0 < 4; var_s0++) {
                        animeState_set(&game_state_data[var_s0].unk_094, 0);
                    }

                    backup_game_state(0);
                    break;

                case 9:
                    var_s4_2 = 0;
                    dm_game_init(true);
                    break;
            }
            break;

        case ENUM_EVS_GAMESEL_4:
            var_s4_2 = dm_game_demo_1p();
            break;

        case ENUM_EVS_GAMESEL_5:
            var_s4_2 = dm_game_demo_2p();
            break;

        case ENUM_EVS_GAMESEL_6:
            var_s4_2 = dm_game_demo_4p();
            break;

        default:
            UNREACHABLE;
            break;
    }

    return var_s4_2;
}
#endif

#if VERSION_US || VERSION_CN
/**
 * Original name: dm_game_main3
 */
enum_main_no dm_game_main3(s32 arg0) {
    enum_main_no var_a1;

    switch (evs_gamesel) {
        case ENUM_EVS_GAMESEL_0:
        case ENUM_EVS_GAMESEL_1:
            var_a1 = MAIN_NO_6;
            break;

        case ENUM_EVS_GAMESEL_2:
            if (evs_story_flg != 0) {
                evs_gamesel = ENUM_EVS_GAMESEL_3;
                if ((game_state_data[0].unk_020 == 5) && (arg0 != -2)) {
                    story_proc_no++;
                    var_a1 = MAIN_NO_2;
                } else {
                    var_a1 = MAIN_NO_6;
                }
            } else {
                var_a1 = MAIN_NO_6;
            }
            break;

        case ENUM_EVS_GAMESEL_3:
            if (evs_story_flg != 0) {
                if ((game_state_data[0].unk_020 == 5) && (arg0 != -2)) {
                    if (func_8006498C(evs_story_level, evs_story_no, game_state_data[0].unk_004)) {
                        story_proc_no++;
                    } else {
                        story_proc_no += 2;
                    }
                    var_a1 = MAIN_NO_2;
                } else if (evs_story_no == 9) {
                    var_a1 = MAIN_NO_6;
                } else {
                    var_a1 = MAIN_NO_6;
                }

                if ((story_proc_no - STORY_PROC_NO_10 < STORY_PROC_NO_12 - STORY_PROC_NO_10) ||
                    (story_proc_no == STORY_PROC_NO_22) || (story_proc_no == STORY_PROC_NO_23)) {
                    switch (evs_story_level) {
                        case 0:
                            if (game_state_data[0].unk_004 != 0) {
                                EndingLastMessage = _mesEasyCont;
                            } else {
                                EndingLastMessage = _mesEasyNoCont;
                            }
                            break;

                        case 1:
                            if (game_state_data[0].unk_004 != 0) {
                                EndingLastMessage = _mesNormalCont;
                            } else {
                                EndingLastMessage = _mesNormalNoCont;
                            }
                            break;

                        case 0x2:
                            if (game_state_data[0].unk_004 != 0) {
                                EndingLastMessage = _mesHardCont;
                            } else {
                                EndingLastMessage = _mesHardNoCont;
                            }
                            break;

                        case 0x3:
                            if (game_state_data[0].unk_004 != 0) {
                                EndingLastMessage = _mesSHardCont;
                            } else {
                                EndingLastMessage = _mesSHardNoCont;
                            }
                            break;

                        default:
                            break;
                    }
                }
            } else {
                var_a1 = MAIN_NO_6;
            }
            break;

        case ENUM_EVS_GAMESEL_4:
        case ENUM_EVS_GAMESEL_5:
        case ENUM_EVS_GAMESEL_6:
            var_a1 = MAIN_NO_3;
            break;

        default:
            UNREACHABLE;
            break;
    }

    return var_a1;
}
#endif

#if VERSION_US || VERSION_CN
void dm_game_graphic(void) {
    struct_watchGame *watchGameP = watchGame;

    if (watchGameP->unk_878 != 0x7F) {
        osSetThreadPri(NULL, 0xF);
        watchGameP->unk_878 = 0;
        return;
    }

    RecWritingMsg_draw(&watchGameP->recMessage, &gGfxHead);

    gDPFullSync(gGfxHead++);
    gSPEndDisplayList(gGfxHead++);

    osWritebackDCacheAll();

    gfxTaskStart(&B_800FAE80[gfx_gtask_no], gGfxGlist[gfx_gtask_no], (gGfxHead - gGfxGlist[gfx_gtask_no]) * sizeof(Gfx),
                 0, (watchGameP->unk_880 == 0) ? OS_SC_SWAPBUFFER : 0);
    osSetThreadPri(NULL, 0xF);
    dm_game_graphic2();
    osSetThreadPri(NULL, 0x7F);
}
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", func_8006F628);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", dm_game_main);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", dm_game_main2);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", dm_game_main3);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", dm_game_graphic);
#endif

#if VERSION_US || VERSION_CN
const s32 _x_6416[] = { 0x77, 0xB6 };
static_assert(ARRAY_COUNT(watchGame->unk_8B4) == ARRAY_COUNT(_x_6416), "");

const s32 dir_6435[2] = { -1, 1 };

const s32 color2index_6470[] = { 1, 0, 2 };

void dm_game_graphic2(void) {
    struct_watchGame *temp_s7 = watchGame;
    s32 temp_s2_2 = (game_state_data[0].unk_00C == GAMESTATEDATA_UNK_00C_20) ||
                    (game_state_data[0].unk_00C == GAMESTATEDATA_UNK_00C_21);
    Mtx *mtx;
    Vtx *vtx;
    s32 i;
    s32 j;
    s32 var_s4_2;
    TiTexData *var_t2;
    TiTexData *var_s6;

    gGfxHead = gGfxGlist[gfx_gtask_no];
    mtx = dm_get_mtx_buf();
    vtx = dm_get_vtx_buf();

    gSPSegment(gGfxHead++, 0x00, NULL);

    F3RCPinitRtn();
    gfxSetScissor(&gGfxHead, GFXSETSCISSOR_INTERLACE_NO, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    F3ClearFZRtn(temp_s2_2);
    if (temp_s2_2 == 0) {
        if (temp_s7->unk_394 < 0x14) {
            dm_game_draw_snap_bg(&gGfxHead, &mtx, &vtx, 1);
        } else if (temp_s7->unk_9AC == 0) {
            func_8006F628(&gGfxHead);
        }
    }

    switch (evs_gamesel) {
        case ENUM_EVS_GAMESEL_1:
        case ENUM_EVS_GAMESEL_3:
        case ENUM_EVS_GAMESEL_5: {
            s32 temp_s4 = temp_s7->unk_394;
            s32 temp_s0 = temp_s7->unk_394 < 0x14;
            s32 temp_s1 = temp_s7->unk_880 == 0;

            if (temp_s2_2 == 0) {
                if (temp_s7->unk_880 != 0) {
                    temp_s7->unk_394 = 0x14;
                }
                dm_calc_bottle_2p();
                if (temp_s0 != 0) {
                    dm_draw_bottle_2p(&gGfxHead);
                }

                i = (0x14 - temp_s7->unk_394) * 6;
                if (evs_story_flg != 0) {
                    draw_story_board(&gGfxHead, 0, -i, temp_s0, temp_s1);
                } else {
                    draw_vsmode_board(&gGfxHead, 0, -i, temp_s0, temp_s1);
                }
                temp_s7->unk_394 = temp_s4;
            }
        } break;

        default:
            break;
    }

    switch (evs_gamesel) {
        case ENUM_EVS_GAMESEL_1:
        case ENUM_EVS_GAMESEL_2:
        case ENUM_EVS_GAMESEL_3:
        case ENUM_EVS_GAMESEL_5:
        case ENUM_EVS_GAMESEL_6:
            if ((temp_s2_2 == 0) && (temp_s7->unk_880 == 0)) {
                for (i = 0; i < evs_playcnt; i++) {
                    dm_virus_anime(&game_state_data[i], game_map_data[i]);
                    dm_game_graphic_p(&game_state_data[i], i, game_map_data[i]);
                }
            }
            break;

        default:
            break;
    }

    switch (evs_gamesel) {
        case ENUM_EVS_GAMESEL_0:
        case ENUM_EVS_GAMESEL_4:
            if ((temp_s2_2 == 0) && (temp_s7->unk_880 == 0)) {
                disp_logo_setup(&gGfxHead);

                if (temp_s7->unk_9AC > 0) {
                    draw_coffee_break(&gGfxHead, temp_s7->unk_9B4, temp_s7->unk_9B8, temp_s7->unk_9AC > 1);
                    msgWnd_draw(&temp_s7->messageWnd, &gGfxHead);
                    if (temp_s7->unk_9B0 == 0x168) {
                        push_any_key_draw(0x80, 0xC0);
                    }
                } else {
                    animeState_initDL(&game_state_data[0].unk_094, &gGfxHead);
                    animeState_draw(&game_state_data[0].unk_094, &gGfxHead, 250.0f, 84.0f, 1.0f, 1.0f);

                    dm_virus_anime(&game_state_data[0], game_map_data[0]);
                    dm_game_graphic_1p(&game_state_data[0], 0, game_map_data[0]);
                    _disp_coin_logo(&gGfxHead, temp_s7->unk_378);

                    gSPDisplayList(gGfxHead++, alpha_texture_init_dl);

                    draw_count_number(&gGfxHead, 0, 7, evs_high_score, 0x1D, 0x27);
                    draw_count_number(&gGfxHead, 0, 7, game_state_data[0].unk_000, 0x1D, 0x43);

                    gSPDisplayList(gGfxHead++, alpha_texture_init_dl);

                    switch (evs_gamemode) {
                        case ENUM_EVS_GAMEMODE_0:
                            draw_virus_number(&gGfxHead, game_state_data[0].unk_026, 0xFE, 0x7E, 1.0f, 1.0f);
                            break;

                        default:
                            break;
                    }

                    switch (evs_gamemode) {
                        case ENUM_EVS_GAMEMODE_2:
                        case ENUM_EVS_GAMEMODE_0:
                            func_8006A098(&gGfxHead, evs_game_time, RO_800B1D28[0], RO_800B1D28[1]);
                            break;

                        case ENUM_EVS_GAMEMODE_3:
                            i = 0x2A30 - evs_game_time;
                            if (i < 0) {
                                i = 0;
                            }
                            i += 5;
                            draw_time2(&gGfxHead, i, RO_800B1D28[0], RO_800B1D28[1]);
                            break;

                        default:
                            break;
                    }

                    switch (evs_gamemode) {
                        case ENUM_EVS_GAMEMODE_2:
                            i = game_state_data[0].unk_170;
                            break;

                        default:
                            i = game_state_data[0].unk_025;
                            break;
                    }

                    draw_virus_number(&gGfxHead, i, 0xFE, 0xD2, 1.0f, 1.0f);
                    dm_draw_big_virus(&gGfxHead);
                    dm_game_graphic_effect(&game_state_data[0], 0, 0);
                    if (temp_s7->unk_410 != 0) {
                        disp_timestop_logo(&gGfxHead, 0);
                    }
                }
            }
            break;

        case ENUM_EVS_GAMESEL_1:
        case ENUM_EVS_GAMESEL_3:
        case ENUM_EVS_GAMESEL_5:
            if ((temp_s2_2 == 0) && (temp_s7->unk_880 == 0)) {
                disp_logo_setup(&gGfxHead);

                gSPDisplayList(gGfxHead++, alpha_texture_init_dl);

                for (i = 0; i < 2; i++) {
                    draw_virus_number(&gGfxHead, game_state_data[i].unk_025, _posP2VirusNum[i][0], _posP2VirusNum[i][1],
                                      1.0f, 1.0f);
                }

                switch (evs_gamemode) {
                    case ENUM_EVS_GAMEMODE_3:
                        i = 0x2A30 - evs_game_time;
                        if (i < 0) {
                            i = 0;
                        }
                        i += 5;
                        draw_time2(&gGfxHead, i, 0x9A, 0xA7);
                        break;

                    default:
                        func_8006A098(&gGfxHead, evs_game_time, 0x9A, 0xA7);
                        break;
                }

                if (evs_story_flg != 0) {
                    for (i = var_s4_2 = 0; i < 2U; i++) {
                        if (temp_s7->unk_89C[i] == 0) {
                            func_800695A8(&gGfxHead, _posStStar[i][0], _posStStar[i][1], var_s4_2);
                            var_s4_2++;
                        }
                    }
                } else {
                    for (i = 0; i < ARRAY_COUNT(watchGame->unk_8B4); i++) {
                        draw_count_number(&gGfxHead, 0, 2, temp_s7->unk_8B4[i], _x_6416[i], 0x98);
                    }

                    for (i = var_s4_2 = 0; i < 2; i++) {
                        for (j = temp_s7->unk_89C[i]; j < evs_vs_count; j++) {
                            func_800695A8(&gGfxHead, _posP2StarX[i], _posP2StarY[evs_vs_count - 1][j], var_s4_2);
                            var_s4_2++;
                        }
                    }
                }

                switch (evs_gamemode) {
                    case ENUM_EVS_GAMEMODE_1:
                        var_s6 = &temp_s7->unk_43C[7];
                        break;

                    default:
                        var_s6 = &temp_s7->unk_43C[0xF];
                        break;
                }
                var_t2 = &temp_s7->unk_43C[1];

                StretchAlphaTexBlock(&gGfxHead, var_s6->info[0], var_s6->info[1], var_s6->texs[1], var_s6->info[0],
                                     var_t2->texs[1], var_t2->info[0], 131.0f, 181.0f, var_s6->info[0],
                                     var_s6->info[1]);

                func_80069188(&temp_s7->unk_070, temp_s7->unk_06C);
                starForce_draw(&temp_s7->unk_070, &gGfxHead, temp_s7->unk_06C);

                for (i = 0; i < 2; i++) {
                    animeState_initDL(&game_state_data[i].unk_094, &gGfxHead);
                    animeState_draw(&game_state_data[i].unk_094, &gGfxHead, _posP2CharFrm[i][0], _posP2CharFrm[i][1],
                                    dir_6435[i], 1.0f);
                }

                for (i = 0; i < 2; i++) {
                    dm_game_graphic_effect(&game_state_data[i], i, 0);
                }

                gSPDisplayList(gGfxHead++, alpha_texture_init_dl);
            }
            break;

        case ENUM_EVS_GAMESEL_2:
        case ENUM_EVS_GAMESEL_6:
            if ((temp_s2_2 == 0) && (temp_s7->unk_880 == 0)) {
                for (i = 0; i < 4; i++) {
                    animeState_initDL(&game_state_data[i].unk_094, &gGfxHead);
                    animeState_draw(&game_state_data[i].unk_094, &gGfxHead, _posP4CharBase[i][0] + 0x14,
                                    _posP4CharBase[i][1] + 0x28, 1.0f, 1.0f);
                }

                disp_logo_setup(&gGfxHead);

                gSPDisplayList(gGfxHead++, alpha_texture_init_dl);

                for (i = 0; i < 4; i++) {
                    draw_virus_number(&gGfxHead, game_state_data[i].unk_025, _posP4CharBase[i][0] + 0x32,
                                      _posP4CharBase[i][1] + 0x1D, 1.0f, 1.0f);
                }

                if (evs_story_flg != 0) {
                    func_8006A098(&gGfxHead, evs_game_time, 0x3B, 0x12);

                    for (i = var_s4_2 = 0; i < 4U; i++) {
                        if (temp_s7->unk_89C[i] == 0) {
                            func_800695A8(&gGfxHead, _posStP4StarX[i], 0xD, var_s4_2);
                            var_s4_2++;
                        }
                    }
                } else if (temp_s7->unk_8C0 != 0) {
                    s32 a;
                    s32 b;
                    s32 temp_s5;
                    s32 temp_s2_4;
                    s32 temp_a3_10;

                    var_s6 = &temp_s7->unk_440[0xE];
                    var_t2 = &temp_s7->unk_440[0x16];

                    temp_s5 = var_s6->info[0] >> 1;
                    temp_s2_4 = var_s6->info[1] / 3;

                    for (i = 0; i < 2; i++) {
                        for (j = 0; j < 4; j++) {
                            temp_a3_10 = temp_s7->unk_8DC[i][j];
                            if (temp_a3_10 < 0) {
                                continue;
                            }

                            a = temp_s5 * i;
                            b = temp_s2_4 * color2index_6470[temp_a3_10];

                            StretchAlphaTexTile(&gGfxHead, var_s6->info[0], var_s6->info[1], var_s6->texs[1],
                                                var_s6->info[0], var_t2->texs[1], var_t2->info[0], a, b, temp_s5,
                                                temp_s2_4, _posP4StockCap[i][0] + j * 9, _posP4StockCap[i][1], temp_s5,
                                                temp_s2_4);
                        }
                    }

                    for (i = var_s4_2 = 0; i < 2; i++) {
                        for (j = temp_s7->unk_89C[i]; j < evs_vs_count; j++) {
                            func_800695A8(&gGfxHead, _posP4TeamStarX[evs_vs_count - 1][i][j], 0xD, var_s4_2);
                            var_s4_2++;
                        }
                    }
                } else {
                    for (i = var_s4_2 = 0; i < 4; i++) {
                        for (j = temp_s7->unk_89C[i]; j < evs_vs_count; j++) {
                            func_800695A8(&gGfxHead, _posP4CharStarX[evs_vs_count - 1][i][j], 0xD, var_s4_2);
                            var_s4_2++;
                        }
                    }
                }

                func_80069188(&temp_s7->unk_070, temp_s7->unk_06C);
                starForce_draw(&temp_s7->unk_070, &gGfxHead, temp_s7->unk_06C);

                for (i = 0; i < 4; i++) {
                    dm_game_graphic_effect(&game_state_data[i], i, 1);
                }
                disp_attack_effect(&gGfxHead);
            }
            break;

        default:
            break;
    }

    if (temp_s7->unk_880 == 0) {
        switch (game_state_data[0].unk_00C) {
            case GAMESTATEDATA_UNK_00C_21:
                DebugMenu_8003FD0C(&gGfxHead);
                DebugMenu_8003FB00();
                break;

            case GAMESTATEDATA_UNK_00C_20:
                DebugMenu_800409A0();
                DebugMenu_800409DC(&gGfxHead);
                break;

            default:
                break;
        }

        switch (evs_gamesel) {
            case ENUM_EVS_GAMESEL_4:
            case ENUM_EVS_GAMESEL_5:
            case ENUM_EVS_GAMESEL_6:
                draw_demo_logo(&gGfxHead, 0x6A, 0xAA);

#if VERSION_CN || VERSION_GW
                gDPPipeSync(gGfxHead++);
#endif
                break;

            default:
                break;
        }

        if ((temp_s7->unk_000 != 0) && !func_80064848()) {
            s32 sp50;
            s32 sp54;

            switch (evs_gamesel) {
                case ENUM_EVS_GAMESEL_0:
                case ENUM_EVS_GAMESEL_2:
                    sp50 = 0x1E;
                    sp54 = 0x14;
                    break;

                case ENUM_EVS_GAMESEL_1:
                case ENUM_EVS_GAMESEL_3:
                    sp50 = 0x80;
                    sp54 = 0x90;
                    break;

                default:
                    break;
            }

            draw_replay_logo(&gGfxHead, sp50, sp54);

            //! FAKE
            j = temp_s7->unk_89C[i];
        }

        if (temp_s7->unk_A28.alpha > 0) {
            var_s6 = &temp_s7->unk_430[0xC];

            gSPDisplayList(gGfxHead++, normal_texture_init_dl);
            gDPSetCombineLERP(gGfxHead++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, PRIMITIVE, TEXEL0, 0,
                              PRIMITIVE, 0);
            gDPSetRenderMode(gGfxHead++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
            gDPSetPrimColor(gGfxHead++, 0, 0, 255, 255, 200, temp_s7->unk_A28.alpha);
            gDPSetTextureLUT(gGfxHead++, G_TT_NONE);

            gDPLoadTextureBlock_4b(gGfxHead++, var_s6->texs[1], G_IM_FMT_I, var_s6->info[0], var_s6->info[1], 0,
                                   G_TX_NOMIRROR, G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

            drawCursorPattern(&gGfxHead, var_s6->info[0], var_s6->info[1], 0x10, 0x10, temp_s7->unk_A28.xPos - 6,
                              temp_s7->unk_A28.yPos - 6, (temp_s7->unk_A28.unk_3C * 0x14) + 0xC,
                              (temp_s7->unk_A28.unk_48 * 3) + 0xC);

            msgWnd_update(&temp_s7->unk_A28);
            msgWnd_draw(&temp_s7->unk_A28, &gGfxHead);
        }

        temp_s7->unk_A28.alpha = CLAMP(temp_s7->unk_A28.alpha + temp_s7->unk_AA8, 0, 0xFF);

        temp_s7->unk_38C = CLAMP(temp_s7->unk_38C + temp_s7->unk_390, 0, 0x1E);

        curtain_proc(&gGfxHead, temp_s7->unk_38C);
    }

#ifdef NN_SC_PERF
    if (temp_s7->unk_880 == 0) {
        if (D_800BEF08_cn != 0) {
            func_8002BD7C_cn(&gGfxHead, 0x20, 0xB4);
        }
    }
#endif

    if (temp_s7->unk_880 != 0) {
        temp_s7->unk_880 = 0;
    }
}
#endif

#if VERSION_GW
INCLUDE_RODATA("asm/gw/nonmatchings/main_segment/dm_game_main", RO_800B3224_gw);
#endif

#if VERSION_GW
INCLUDE_RODATA("asm/gw/nonmatchings/main_segment/dm_game_main", RO_FLT_800B322C_gw);
#endif

#if VERSION_GW
INCLUDE_RODATA("asm/gw/nonmatchings/main_segment/dm_game_main", RO_800B3234_gw);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", dm_game_graphic2);
#endif

#if VERSION_US || VERSION_CN
void dm_game_graphic_onDoneSawp(void) {
    struct_watchGame *watchGameP = watchGame;
    s32 microseconds;
    s32 i;
    s32 j;

#ifdef NN_SC_PERF
    func_8002BA98_cn(ENUM_8002BA98_CN_ARG0_13, 0);
#endif

    microseconds = 13500;
    microseconds -= OS_CYCLES_TO_USEC(osGetTime());

    if (microseconds > 50) {
        OSMesgQueue sp28;
        OSTimer sp40;
        OSMesg sp60[1];

        osCreateMesgQueue(&sp28, sp60, ARRAY_COUNT(sp60));
        osSetTimer(&sp40, OS_USEC_TO_CYCLES(microseconds), 0, &sp28, NULL);
        osRecvMesg(&sp28, NULL, OS_MESG_BLOCK);
    }

    if (watchGameP->unk_3B0 != 0) {
        for (i = 0; i < MAXCONTROLLERS; i++) {
            joycur[i] = 0;
            gControllerPressedButtons[i] = 0;
            gControllerPrevHoldButtons[i] = 0;
            gControllerHoldButtons[i] = 0;
        }
    } else {
        joyProcCore();
    }

#ifdef NN_SC_PERF
    func_8002BA98_cn(ENUM_8002BA98_CN_ARG0_0, 0);
#endif

    for (j = 0; j < evs_gamespeed; j++) {
        bool var_s3 = false;
        bool temp_s1 = func_80064848();

        dm_make_key();

        for (i = 0; i < evs_playcnt; i++) {
            if (game_state_data[i].unk_020 == 0xD) {
                var_s3 = true;
                break;
            }
        }

        if (!var_s3 && (watchGameP->unk_3C4 != 0)) {
            aiCOM_MissTake();
        }

        if ((watchGameP->unk_000 != 0) && !var_s3 && !temp_s1 && (watchGameP->unk_3C4 != 0)) {
            for (i = 0; i < evs_playcnt; i++) {
                joygam[i] = replay_play(i);
            }

            for (i = 0; i < evs_playcnt; i++) {
                if (joygam[i] & START_BUTTON) {
                    break;
                }
            }

            if (i < evs_playcnt) {
                dm_seq_set_volume(0x40);
                resume_game_state(1);
            }
        }

        watchGameP->unk_40C = (evs_gamemode == ENUM_EVS_GAMEMODE_2) && (joygam[0] & (L_TRIG | R_TRIG));

        switch (evs_gamesel) {
            case ENUM_EVS_GAMESEL_0:
                key_control_main(&game_state_data[0], game_map_data[0], 0, main_joy[0]);
                break;

            case ENUM_EVS_GAMESEL_1:
            case ENUM_EVS_GAMESEL_3:
                for (i = 0; i < 2; i++) {
                    key_control_main(&game_state_data[i], game_map_data[i], i, main_joy[i]);
                }
                break;

            default:
                for (i = 0; i < 4; i++) {
                    key_control_main(&game_state_data[i], game_map_data[i], i, main_joy[i]);
                }
                break;
        }

        if ((watchGameP->unk_000 == 0) && !var_s3) {
            for (i = 0; i < evs_playcnt; i++) {
                replay_record(i, joygam[i]);
            }
        }
    }

#ifdef NN_SC_PERF
    func_8002BA98_cn(ENUM_8002BA98_CN_ARG0_13, 0);
#endif
}
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", func_80072310_gw);
#endif

void func_80071A44(void) {
}

/**
 * Original name: main_techmes
 */
#if VERSION_US || VERSION_CN
enum_main_no main_techmes(NNSched *sc) {
    struct_watchGame *watchGameP;
    bool keepRunning = true;
    OSMesgQueue scMQ;
    OSMesg scMsgBuff[NN_SC_MAX_MESGS];
    NNScClient scClient;
    u8 sequenceBackup;

    osCreateMesgQueue(&scMQ, scMsgBuff, ARRAY_COUNT(scMsgBuff));
    nnScAddClient(sc, &scClient, &scMQ);

    dm_game_init_heap();
    watchGameP = watchGame;

    dm_game_init_static();

    heapTop = init_menu_bg(heapTop, false);
    msgWnd_init2(&watchGameP->messageWnd, &heapTop, 0x1000, 0x12, 0x10, 0x34, 0x22);
    msgWnd_addStr(&watchGameP->messageWnd, EndingLastMessage);
    watchGameP->messageWnd.unk_20 = 1;
    watchGameP->messageWnd.unk_24 = 1;

    sequenceBackup = evs_seqence;
    evs_seqence = 0;
    dm_game_init(false);
    evs_seqence = sequenceBackup;

    dm_seq_play_in_game(SEQ_INDEX_23);

    while (keepRunning) {
        osRecvMesg(&scMQ, NULL, OS_MESG_BLOCK);
        joyProcCore();

#ifdef NN_SC_PERF
        if (D_80092F10_cn) {
            graphic_no = GRAPHIC_NO_0;
            dm_audio_update();
            continue;
        }
#endif

        switch (watchGameP->unk_9AC) {
            case 0x0:
                if (watchGameP->unk_9B0 == 0xFF) {
                    watchGameP->unk_9AC = 1;
                } else {
                    watchGameP->unk_9B0 = MIN(0xFF, watchGameP->unk_9B0 + 4);
                }
                break;

            case 0x1:
                if (msgWnd_isEnd(&watchGameP->messageWnd)) {
                    watchGameP->unk_9AC++;
                } else {
                    msgWnd_update(&watchGameP->messageWnd);
                }
                break;

            case 0x2:
                if (gControllerPressedButtons[main_joy[0]] & ANY_BUTTON) {
                    watchGameP->unk_9AC = 3;
                }
                break;

            case 0x3:
                if (watchGameP->unk_9B0 == 0) {
                    keepRunning = false;
                } else {
                    watchGameP->unk_9B0 = MAX(0, watchGameP->unk_9B0 - 4);
                }
                break;
        }

        dm_audio_update();
        graphic_no = GRAPHIC_NO_6;
    }

    graphic_no = GRAPHIC_NO_0;
    dm_audio_stop();

    while (!dm_audio_is_stopped() || (pendingGFX != 0)) {
        osRecvMesg(&scMQ, NULL, OS_MESG_BLOCK);
        dm_audio_update();
    }

    nnScRemoveClient(sc, &scClient);

    return MAIN_NO_3;
}
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", main_techmes);
#endif

#if VERSION_US || VERSION_CN
void graphic_techmes(void) {
    struct_watchGame *watchGameP = watchGame;
    Mtx *mtx;
    Vtx *vtx;

    gGfxHead = gGfxGlist[gfx_gtask_no];
    mtx = dm_get_mtx_buf();
    vtx = dm_get_vtx_buf();
    F3RCPinitRtn();
    F3ClearFZRtn(false);

    gDPSetEnvColor(gGfxHead++, 0, 0, 0, 255);
    gDPSetPrimColor(gGfxHead++, 0, 0, 255, 255, 255, 255);

    draw_menu_bg(&gGfxHead, 0, -0x78);

    dm_draw_KaSaMaRu(&gGfxHead, &mtx, &vtx, msgWnd_isSpeaking(&watchGameP->messageWnd), 0xC8, 0x80, 1, 0xFF);
    msgWnd_draw(&watchGameP->messageWnd, &gGfxHead);
    if (watchGameP->unk_9AC == 2) {
        push_any_key_draw(128, 192);
    }

    FillRectRGBA(&gGfxHead, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, 0, 255 - watchGameP->unk_9B0);

    watchGameP->unk_424++;

    gDPFullSync(gGfxHead++);
    gSPEndDisplayList(gGfxHead++);

    osWritebackDCacheAll();
    gfxTaskStart(&B_800FAE80[gfx_gtask_no], gGfxGlist[gfx_gtask_no], (gGfxHead - gGfxGlist[gfx_gtask_no]) * sizeof(Gfx),
                 0, OS_SC_SWAPBUFFER);
}
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/dm_game_main", graphic_techmes);
#endif

/**
 * Original filename: dm_game_main.c
 */

#include "dm_game_main.h"
#include "libultra.h"
#include "include_asm.h"
#include "macros_defines.h"
#include "unknown_structs.h"
#include "main_segment_functions.h"
#include "main_segment_variables.h"
#include "boot_functions.h"
#include "boot_variables.h"
#include "util.h"
#include "gcc/memory.h"
#include "rom_offsets.h"
#include "buffers.h"
#include "audio/audio_stuff.h"
#include "graphic.h"
#include "aif.h"
#include "replay.h"
#include "game_etc.h"
#include "record.h"
#include "vr_init.h"
#include "main1x.h"
#include "028820.h"
#include "tex_func.h"
#include "main_story.h"

#if VERSION_US || CC_CHECK
// The compiler needs to not see the declared functions to match the cn version
#include "joy.h"
#endif
#if VERSION_CN && !CC_CHECK
void joyCursorFastSet(u16 mask, u8 index);
#endif

// TODO: Just to avoid warnings when building GW
#if VERSION_US || VERSION_CN

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", func_800601F0);
#endif

#if VERSION_CN
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

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", func_80060270);
#endif

#if VERSION_CN
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
UNK_TYPE dm_make_score(struct_game_state_data *gameStateDataRef) {
    UNK_TYPE temp_v0;
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

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/dm_game_main", RO_800B1C4C);
#endif

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/dm_game_main", RO_800B1C5C);
#endif

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/dm_game_main", RO_800B1C74);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/dm_game_main", rotate_table_399);
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/dm_game_main", rotate_mtx_400);
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/dm_game_main", _speed_561);
#endif

#if VERSION_US || VERSION_CN
const u8 _retryMenu_itemCount[] = {
    2, 3, 2, 3, 2, 3,
};
#endif

const f32 _big_virus_def_wait[] = { 12.5f, 10.0f, 7.5f };

extern const f32 _big_virus_min_wait[];
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/dm_game_main", _big_virus_min_wait);
#endif

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/dm_game_main", RO_800B1C98);
#endif

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/dm_game_main", RO_800B1CA4);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/dm_game_main", RO_800C82BC_cn);
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/dm_game_main", RO_800C82C8_cn);
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/dm_game_main", RO_800C82D4_cn);
#endif

ASM_RODATA;

// clang-format off
/**
 * Original name: _mesWriting
 */
const char _mesWriting[] =
#if VERSION_US
    "Now saving." MSG_NEWLINE
    "Do not turn power off."
#endif
#if VERSION_CN
    "存储中" MSG_NEWLINE
    "请勿关闭电源."
#endif
    MSG_END;

const char STR_800B1CE0[] =
#if VERSION_US
    "Now deleting." MSG_NEWLINE
    "Do not turn power off."
#endif
#if VERSION_CN
    "删除中" MSG_NEWLINE
    "请勿关闭电源."
#endif
    MSG_END;
// clang-format on

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/dm_game_main", RO_800B1D08);
#endif

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/dm_game_main", RO_800B1D18);
#endif

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/dm_game_main", RO_800B1D28);
#endif

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/dm_game_main", RO_800B1D2C);
#endif

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/dm_game_main", RO_800B1D5C);
#endif

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/dm_game_main", RO_800B1D60);
#endif

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/dm_game_main", RO_800B1D7C);
#endif

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/dm_game_main", RO_800B1D80);
#endif

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/dm_game_main", RO_800B1D84);
#endif

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/dm_game_main", _posP4TeamStarX);
#endif

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/dm_game_main", _posP4CharStarX);
#endif

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/dm_game_main", RO_800B1E7C);
#endif

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/dm_game_main", RO_800B1E8C);
#endif

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/dm_game_main", RO_800B1E9C);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", dm_attack_se);
#endif

extern s8 dm_chaine_se_table_vs_178[];    // sndindex
extern s8 dm_chaine_se_table_4p_179[][3]; // sndindex

#if VERSION_CN
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

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", dm_warning_h_line);
#endif

#if VERSION_CN
void dm_warning_h_line(struct_game_state_data *gameStateData, GameMapGrid *mapGrid) {
    bool var_s2 = false;
    s32 rowPlusOne;

    for (rowPlusOne = 1; rowPlusOne < 4; rowPlusOne++) {
        s32 column;

        for (column = 0; column < GAME_MAP_COLUMNS; column++) {
            if (get_map_info(mapGrid, column, rowPlusOne) == true) {
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

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", set_down_flg);
#endif

#if VERSION_CN
#if 0
s32 set_down_flg(GameMapGrid *mapGrid) {
    enum bool sp10[2];
    GameMapCell *var_s0;
    GameMapCell *var_v0;
    GameMapCell *var_v1_2;
    GameMapCell *var_v1_3;
    GameMapGrid *var_a0;
    enum bool temp_v0;
    s32 var_s4;
    s32 var_s7;
    s32 var_v1;
    u32 var_s1;

    var_v0 = mapGrid->cells;
    for (var_s4 = 0x77; var_s4 >= 0; var_s4--) {
        var_v0[var_s4].unk_4[1] = 1;
    }

    for (var_s7 = 0xE; var_s7 >= 0; var_s7--) {
        for (var_s4 = 0; var_s4 < 8; var_s4++) {
            s32 temp_s3;

            temp_s3 = (var_s7 * 8) + var_s4;
            var_s0 = mapGrid->cells;
            if ((var_s0[temp_s3].unk_4[0] != 0) && (var_s0[temp_s3].unk_4[4] < 0)) {
                if ((u32) (var_s0[temp_s3].unk_2 - 2) < 2U) {
                    if ((s8) var_s0[temp_s3].unk_2 == 2) {
                        var_s1 = 0;
                        while (var_s1 < 2U) {
                            sp10[var_s1] = true;
                            if ((get_map_info(mapGrid, (s32) var_s0[temp_s3+var_s1].unk_0, var_s0[temp_s3+var_s1].unk_1 + 1) == true)
                            && (var_s0[temp_s3 +var_s1+ 8].unk_4[1] != (s8) true)
                            ) {
                                sp10[var_s1] = false;
                            }
                            var_s1 += 1;
                        }

                        if ((sp10[0] == false) || (sp10[1] == 0)) {
                            var_s1 = 0;
                            var_v1_2 = &mapGrid->cells[temp_s3];
                            while (var_s1 < 2U) {
                                var_v1_2->unk_4[1] = 0;
                                var_s1 += 1;
                                var_v1_2 += 0xA;
                            }
                        }
                    } else if ((s8) var_s0[temp_s3].unk_2 == 3) {
                        var_s1 = 0;
                        while (var_s1 < 2U) {
                            sp10[var_s1] = true;
                            if ((get_map_info(mapGrid, (s32) var_s0[temp_s3-var_s1].unk_0, var_s0[temp_s3-var_s1].unk_1 + 1) == true)
                            && (var_s0[temp_s3-var_s1 + 8].unk_4[1] != (s8) true)
                            ) {
                                sp10[var_s1] = false;
                            }
                            var_s1 += 1;
                        }

                        if ((sp10[0] == false) || (sp10[1] == 0)) {
                            var_s1 = 0;
                            var_v1_3 = mapGrid->cells;
                            while (var_s1 < 2U) {
                                var_v1_3[temp_s3-var_s1].unk_4[1] = 0;
                                var_s1 += 1;
                            }
                        }
                    }
                } else {
                    if ((get_map_info(mapGrid, (s32) var_s0[temp_s3].unk_0, var_s0[temp_s3].unk_1 + 1) == true) && (var_s0[temp_s3 + 8].unk_4[1] != true)) {
                        var_s0[temp_s3].unk_4[1] = 0;
                    }
                }
            } else {
                var_s0[temp_s3].unk_4[1] = 0;
            }
        }

    }

    var_v1 = 0;
    var_a0 = mapGrid;
    for (var_s4 = 0; var_s4 < 0x80; var_s4 += 1) {
        if (var_a0->cells[var_s4].unk_4[0] != 0) {
            var_v1 += var_a0->cells[var_s4].unk_4[1] != 0;
        }
    }

    return var_v1;
}
#else
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", set_down_flg);
#endif
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", go_down);
#endif

#if VERSION_CN
void go_down(struct_game_state_data *gameStateData, GameMapGrid *mapGrid, s32 arg2) {
    GameMapCell *cells = mapGrid->cells;
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

            if (cells[index].unk_4[1] != 0) {
                set_map(mapGrid, cells[index].unk_0, cells[index].unk_1 + 1, cells[index].unk_2, cells[index].unk_3);
                clear_map(mapGrid, cells[index].unk_0, cells[index].unk_1);
                var_a0 = true;
            }
        }
    }

    if (var_a0) {
        dm_snd_play_in_game(SND_INDEX_55);
    }

    if ((gameStateData->unk_049 != 0) && (gameStateData->unk_01C == 0x12)) {
        for (j = 0; j < (GAME_MAP_ROWS - 1) * GAME_MAP_COLUMNS; j++) {
            if ((mapGrid->cells[j].unk_4[0] != 0) && (mapGrid->cells[j].unk_4[1] == 0) &&
                (mapGrid->cells[j].unk_3 < 3)) {
                mapGrid->cells[j].unk_3 += 3;
            }
        }
    }

    if (set_down_flg(mapGrid) == 0) {
        if (dm_h_erase_chack(mapGrid) || dm_w_erase_chack(mapGrid)) {
            gameStateData->unk_00C = (gameStateData->unk_049 == 0) ? 6 : 0x15;
            gameStateData->unk_02F = 0;
        } else {
            gameStateData->unk_00C = (gameStateData->unk_049 == 0) ? 9 : 0x16;
        }
    }
}
#endif

#if VERSION_US
void erase_anime(GameMapGrid *mapGrid) {
    s32 i;

    for (i = 0; i < (GAME_MAP_ROWS - 1) * GAME_MAP_COLUMNS; i++) {
        GameMapCell *cell = &mapGrid->cells[i];

        if ((cell->unk_4[0] != 0) && (cell->unk_4[2] != 0)) {
            cell->unk_2++;

            if (cell->unk_4[4] >= 0) {
                if (cell->unk_2 >= 0xF) {
                    clear_map(mapGrid, cell->unk_0, cell->unk_1);
                }
            } else {
                if (cell->unk_2 >= 7) {
                    clear_map(mapGrid, cell->unk_0, cell->unk_1);
                }
            }
        }
    }
}
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", erase_anime);
#endif

void throw_rotate_capsel(struct_game_state_data_unk_178 *arg0);

extern const s32 rotate_mtx_400[];
extern const s32 rotate_table_399[];

#if VERSION_CN
void throw_rotate_capsel(struct_game_state_data_unk_178 *arg0) {
    s32 i;
    s32 var_t0;
    s32 temp_a2;
    s32 v0;

    if (arg0->unk_0[0] == arg0->unk_0[1]) {
        v0 = arg0->unk_7;
        temp_a2 = arg0->unk_6;

        var_t0 = 1;
        arg0->unk_0[1]++;
        arg0->unk_2[1]++;
        arg0->unk_6 = v0;
        arg0->unk_7 = temp_a2;
    } else {
        var_t0 = -1;
        arg0->unk_0[1]--;
        arg0->unk_2[1]--;
    }

    for (i = 0; i < ARRAY_COUNT(arg0->unk_4); i++) {
        temp_a2 = rotate_table_399[arg0->unk_4[i]];
        temp_a2 += var_t0;

        arg0->unk_4[i] = rotate_mtx_400[temp_a2];
    }
}
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", translate_capsel);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", rotate_capsel);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", func_800609B8);
#endif

#if VERSION_US
void translate_capsel(GameMapGrid *mapGrid, struct_game_state_data *arg1, s32 arg2, s32 arg3) {
    s32 var_s1 = 0;
    struct_game_state_data_unk_178 *temp_s5 = &arg1->unk_178;

    if ((arg1->unk_178.unk_2[0] <= 0) || (arg1->unk_178.unk_8 == 0)) {
        return;
    }

    if (arg2 == 1) {
        if (arg1->unk_178.unk_0[0] == arg1->unk_178.unk_0[1]) {
            if ((arg1->unk_178.unk_0[1] < 7) &&
                (get_map_info(mapGrid, arg1->unk_178.unk_0[1] + 1, arg1->unk_178.unk_2[0]) != arg2)) {
                if (arg1->unk_178.unk_2[1] == 0) {
                    var_s1 = 1;
                } else {
                    if (get_map_info(mapGrid, arg1->unk_178.unk_0[0] + 1, arg1->unk_178.unk_2[1]) != arg2) {
                        var_s1 = 1;
                    }
                }
            }
        } else if (arg1->unk_178.unk_0[1] < 7) {
            if (get_map_info(mapGrid, arg1->unk_178.unk_0[1] + 1, arg1->unk_178.unk_2[0]) != arg2) {
                var_s1 = 1;
            }
        }
    } else if (arg2 == -1) {
        if (arg1->unk_178.unk_0[0] == arg1->unk_178.unk_0[1]) {
            if ((arg1->unk_178.unk_0[0] > 0) &&
                (get_map_info(mapGrid, arg1->unk_178.unk_0[0] - 1, arg1->unk_178.unk_2[0]) != true)) {
                if (arg1->unk_178.unk_2[1] != 0) {
                    if (get_map_info(mapGrid, arg1->unk_178.unk_0[0] - 1, arg1->unk_178.unk_2[1]) != true) {
                        var_s1 = -1;
                    }
                } else {
                    var_s1 = -1;
                }
            }
        } else if (arg1->unk_178.unk_0[0] > 0) {
            if (get_map_info(mapGrid, arg1->unk_178.unk_0[0] - 1, arg1->unk_178.unk_2[0]) != true) {
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

#if VERSION_US
#ifdef NON_MATCHING
void rotate_capsel(GameMapGrid *mapGrid, struct_game_state_data_unk_178 *arg1, s32 arg2) {
    s32 var_s1 = 0;

    if ((arg1->unk_2 <= 0) || (arg1->unk_8 == 0)) {
        return;
    }

    if (arg1->unk_0[0] == arg1->unk_0[1]) {
        if ((arg1->unk_0[0] == 7) || (get_map_info(mapGrid, arg1->unk_0[0] + 1, arg1->unk_2[0]) == true)) {
            if ((arg1->unk_0[0] != 0) && (get_map_info(mapGrid, arg1->unk_0[0] - 1, arg1->unk_2[0]) != true)) {
                var_s1 = 1;
                arg1->unk_0[0]--;
            }
        } else {
            var_s1 = 1;
            arg1->unk_0[1]++;
        }

        if (var_s1 != 0) {
            arg1->unk_2[1]++;

            if (arg2 == -1) {
                s32 temp_a0;

                temp_a0 = arg1->unk_6;
                arg1->unk_6 = arg1->unk_7;
                arg1->unk_7 = temp_a0;
            }
        }
    } else {
        if (arg1->unk_2[0] == 1) {
            arg1->unk_0[1]--;
            var_s1 = -1;
        } else {
            if (get_map_info(mapGrid, arg1->unk_0[0], arg1->unk_2[0] - 1) == true) {
                if (get_map_info(mapGrid, arg1->unk_0[0] + 1, arg1->unk_2[0] - 1) != true) {
                    var_s1 = -1;
                    arg1->unk_0[0]++;
                }
            } else {
                arg1->unk_0[1]--;
                var_s1 = -1;
            }
        }

        if (var_s1 != 0) {
            arg1->unk_2[1]--;

            if (arg2 == 1) {
                s32 temp_a0;

                temp_a0 = arg1->unk_6;
                arg1->unk_6 = arg1->unk_7;
                arg1->unk_7 = temp_a0;
            }
        }
    }

    if (var_s1 != 0) {
        u32 var_a1;

        dm_snd_play_in_game(SND_INDEX_67);

        for (var_a1 = 0; var_a1 < ARRAY_COUNTU(arg1->unk_4); var_a1++) {
            arg1->unk_4[var_a1] = rotate_mtx_475[rotate_table_474[arg1->unk_4[var_a1]] + var_s1];
        }
    }
}
#else
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", rotate_capsel);
#endif
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", dm_make_magazine);
#endif

#define CAPSMAGAZINE_GET_A(mag) (((mag) >> 4) % 3)
#define CAPSMAGAZINE_GET_B(mag) ((mag) % 3)

#if VERSION_CN
void dm_make_magazine(void) {
    u8 sp18[2];
    s32 i = 0;

    CapsMagazine[i] = random(0xFFFF) % 256;

    sp18[0] = CAPSMAGAZINE_GET_A(CapsMagazine[i]);
    sp18[1] = CAPSMAGAZINE_GET_B(CapsMagazine[i]);

    i++;
    while (i < ARRAY_COUNT(CapsMagazine)) {
        u8 sp20[2];

        CapsMagazine[i] = random(0xFFFF) % 256;

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

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", func_80060F60);
#endif

#if VERSION_CN
void func_80060F60(struct_game_state_data_unk_178 *arg0, s32 arg1, s32 arg2) {
    arg0->unk_0[0] = 3;
    arg0->unk_0[1] = 4;
    arg0->unk_2[1] = 0;
    arg0->unk_2[0] = 0;
    arg0->unk_4[0] = 2;
    arg0->unk_4[1] = 3;
    arg0->unk_6 = arg1;
    arg0->unk_7 = arg2;
    arg0->unk_8 = 1;
    arg0->unk_A = 0;
    arg0->unk_9 = 0;
}
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", func_80060FA0);
#endif

#if VERSION_CN
void func_80060FA0(struct_game_state_data_unk_178 *arg0, s32 arg1, s32 arg2) {
    func_80060F60(arg0, arg1, arg2);
    arg0->unk_9 = 1;
}
#endif

#if VERSION_US
#if 0
void dm_set_capsel(struct_game_state_data *arg0) {
    u8 *temp_a2;
    u8 *temp_a2_3;
    u8 temp_a2_2;
    u8 temp_a2_4;

    arg0->unk_034 = 0;
    temp_a2 = &CapsMagazine[arg0->unk_032];
    temp_a2_2 = *temp_a2;
    func_80060FA0(&arg0->unk_178, ((temp_a2_2 >> 4) - ((*temp_a2 / 48) * 3)) & 0xFF, (*temp_a2 % 3) & 0xFF, MULTU_HI(temp_a2_2, 0xAAAAAAAB));

    arg0->unk_033 = arg0->unk_032;
    arg0->unk_032++;
    if (arg0->unk_032 >= 0xFEU) {
        arg0->unk_032 = 1;
    }
    temp_a2_3 = &CapsMagazine[arg0->unk_032];
    temp_a2_4 = *temp_a2_3;
    func_80060F60(&arg0->unk_17C[8], ((temp_a2_4 >> 4) - ((*temp_a2_3 / 48) * 3)) & 0xFF, (*temp_a2_3 % 3) & 0xFF, MULTU_HI(temp_a2_4, 0xAAAAAAAB));
}
#else
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", dm_set_capsel);
#endif
#endif

#if VERSION_CN
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

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", dm_capsel_speed_up);
#endif

extern u8 _speed_561[];

#if VERSION_CN
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
bool dm_check_game_over(struct_game_state_data *gameStateDataRef, GameMapGrid *mapGrid UNUSED) {
    if (gameStateDataRef->unk_020 == 4) {
        return true;
    }
    return false;
}
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", update_flash_virus_count);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", update_flash_virus_count);
#endif

#if VERSION_US || VERSION_CN
u8 func_8006121C(struct_game_state_data *gameStateDataRef, GameMapGrid *mapGrid, UNK_TYPE arg2) {
    if (evs_gamemode == ENUM_EVS_GAMEMODE_1) {
        gameStateDataRef->unk_025 = update_flash_virus_count(gameStateDataRef, mapGrid, arg2);
    } else {
        gameStateDataRef->unk_025 = get_virus_count(mapGrid);
    }

    return gameStateDataRef->unk_025;
}
#endif

#if VERSION_US || VERSION_CN
void dm_set_virus(struct_game_state_data *gameStateDataRef, GameMapGrid *mapGrid, struct_virus_map_data *virusMapData,
                  struct_virus_map_disp_order *virusMapDispOrder) {
    s32 temp_v0;

    if (gameStateDataRef->unk_014 != 2) {
        return;
    }

    temp_v0 = dm_get_first_virus_count(evs_gamemode, gameStateDataRef);

    if (gameStateDataRef->unk_024 < temp_v0) {
        while (gameStateDataRef->unk_024 < temp_v0) {
            if (!(virusMapDispOrder->unk_00[gameStateDataRef->unk_024] & 0x80)) {
                break;
            }
            gameStateDataRef->unk_024++;
        }

        if (gameStateDataRef->unk_024 < temp_v0) {
            struct_virus_map_data_unk_000 *temp_v0_3 = virusMapData->unk_000;
            GameMapCell *cells = mapGrid->cells;
            u8 *temp_a0 = &virusMapDispOrder->unk_00[gameStateDataRef->unk_024];
            u8 cellIndex = *temp_a0;

            *temp_a0 |= 0x80;

            set_virus(mapGrid, temp_v0_3[cellIndex].unk_1, temp_v0_3[cellIndex].unk_2, temp_v0_3[cellIndex].unk_0,
                      virus_anime_table[temp_v0_3[cellIndex].unk_0][gameStateDataRef->unk_027]);
            if (gameStateDataRef->unk_01C == 0x12) {
                cells[cellIndex].unk_3 += 3;
            }
        }
    }

    if (gameStateDataRef->unk_024 >= temp_v0) {
        gameStateDataRef->unk_014 = 1;
        gameStateDataRef->unk_00C = 2;
    }

    func_8006121C(gameStateDataRef, mapGrid, 0);
}
#endif

#if VERSION_US
void dm_virus_anime(struct_game_state_data *arg0, GameMapGrid *mapGrid) {
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
        if ((mapGrid->cells[index].unk_4[0] != 0) && (mapGrid->cells[index].unk_4[2] == 0)) {
            if (mapGrid->cells[index].unk_4[4] >= 0) {
                mapGrid->cells[index].unk_2 = virus_anime_table[mapGrid->cells[index].unk_4[4]][arg0->unk_027];
            }
        }
    }
}
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", dm_virus_anime);
#endif

#if VERSION_US || VERSION_CN
void dm_capsel_erase_anime(struct_game_state_data *gameStateDataRef, GameMapGrid *mapGrid) {
    gameStateDataRef->unk_036++;

    if (gameStateDataRef->unk_036 == 10) {
        erase_anime(mapGrid);
        gameStateDataRef->unk_035++;
    } else if (gameStateDataRef->unk_036 > 26) {
        erase_anime(mapGrid);
        set_down_flg(mapGrid);
        gameStateDataRef->unk_035 = 0;
        gameStateDataRef->unk_00C = 8;
        gameStateDataRef->unk_036 = 14;
    }
}
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", dm_make_erase_h_line);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", dm_make_erase_h_line);
#endif

#if VERSION_US || VERSION_CN
bool dm_h_erase_chack(GameMapGrid *mapGrid) {
    s32 column;

    for (column = 0; column < GAME_MAP_COLUMNS; column++) {
        s32 row;
        s32 val = 0xF;
        s32 var_a1 = 0;
        s32 var_a3 = -1;
        GameMapCell *cells = mapGrid->cells;

        for (row = 0; row < GAME_MAP_ROWS - 1; row++) {
            if (cells[GAME_MAP_GET_INDEX(row, column)].unk_4[0] != 0) {
                if (cells[GAME_MAP_GET_INDEX(row, column)].unk_4[3] != var_a3) {
                    if (var_a1 < 3) {
                        if (row >= 0xD) {
                            break;
                        }
                        var_a3 = cells[GAME_MAP_GET_INDEX(row, column)].unk_4[3];
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
void dm_h_erase_chack_set(struct_game_state_data *gameStateDataRef, GameMapGrid *mapGrid) {
    s32 column;

    for (column = 0; column < GAME_MAP_COLUMNS; column++) {
        s32 var_s1 = 0;
        s32 var_s5 = -1;
        s32 var_s2 = -1;
        s32 var_fp = 0;
        s32 row;

        for (row = 0; row < GAME_MAP_ROWS - 1; row++) {
            GameMapCell *cells = mapGrid->cells;

            if (cells[GAME_MAP_GET_INDEX(row, column)].unk_4[0] != 0) {
                if (cells[GAME_MAP_GET_INDEX(row, column)].unk_4[3] != var_s2) {
                    if (var_s1 >= 3) {
                        dm_make_erase_h_line(gameStateDataRef, mapGrid, var_s5, var_s1, column);
                        if (gameStateDataRef->unk_039 == 0) {
                            gameStateDataRef->unk_03C[3] |= (1 << var_s2);
                        }
                        gameStateDataRef->unk_03C[var_s2]++;
                        gameStateDataRef->unk_03A++;
                    }

                    if (row < 0xD) {
                        cells = mapGrid->cells;

                        var_s5 = row;
                        var_s2 = cells[GAME_MAP_GET_INDEX(row, column)].unk_4[3];
                        var_s1 = 0;
                    } else {
                        var_fp = 1;
                    }
                } else {
                    var_s1++;
                    if (row == 15) {
                        if (var_s1 >= 3) {
                            dm_make_erase_h_line(gameStateDataRef, mapGrid, var_s5, var_s1, column);
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
                    dm_make_erase_h_line(gameStateDataRef, mapGrid, var_s5, var_s1, column);
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

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", dm_make_erase_w_line);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", dm_make_erase_w_line);
#endif

#if VERSION_US || VERSION_CN
bool dm_w_erase_chack(GameMapGrid *mapGrid) {
    s32 row;

    for (row = 0; row < GAME_MAP_ROWS - 1; row++) {
        s32 var_a1 = 0;
        s32 var_a3 = -1;
        s32 column;

        for (column = 0; column < GAME_MAP_COLUMNS; column++) {
            GameMapCell *cells = mapGrid->cells;

            if (cells[GAME_MAP_GET_INDEX(row, column)].unk_4[0] != 0) {
                if (cells[GAME_MAP_GET_INDEX(row, column)].unk_4[3] != var_a3) {
                    if (var_a1 >= 3) {
                        return true;
                    } else if (column < 5) {
                        var_a3 = cells[GAME_MAP_GET_INDEX(row, column)].unk_4[3];
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
void dm_w_erase_chack_set(struct_game_state_data *arg0, GameMapGrid *mapGrid) {
    s32 row;

    for (row = 0; row < GAME_MAP_ROWS - 1; row++) {
        s32 column;
        s32 var_s1 = 0;
        s32 var_s6 = -1;
        s32 var_s3 = -1;
        bool var_fp = false;

        for (column = 0; column < GAME_MAP_COLUMNS; column++) {
            s32 index = GAME_MAP_GET_INDEX(row, column);
            GameMapCell *cells = mapGrid->cells;

            if (cells[index].unk_4[0] != 0) {
                if (cells[index].unk_4[3] != var_s3) {
                    if (var_s1 >= 3) {
                        dm_make_erase_w_line(arg0, mapGrid, var_s6, var_s1, row);
                        if (arg0->unk_039 == 0) {
                            arg0->unk_03C[3] |= 1 << var_s3;
                        }
                        arg0->unk_03C[var_s3]++;
                        arg0->unk_03A++;
                    }
                    if (column >= 5) {
                        var_fp = true;
                    } else {
                        cells = mapGrid->cells;

                        var_s6 = column;
                        var_s3 = cells[index].unk_4[3];
                        var_s1 = 0;
                    }
                } else {
                    var_s1++;
                    if (column == 7) {
                        if (var_s1 >= 3) {
                            dm_make_erase_w_line(arg0, mapGrid, var_s6, var_s1, row);
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
                    dm_make_erase_w_line(arg0, mapGrid, var_s6, var_s1, row);
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

#if VERSION_US
#ifdef NON_MATCHING
void dm_h_ball_chack(GameMapGrid *mapGrid) {
    u32 column;

    for (column = 0; column < GAME_MAP_COLUMNS; column++) {
        u32 row;

        for (row = 0; row < GAME_MAP_ROWS - 1; row++) {
            GameMapCell *cells = mapGrid->cells;

            if (cells[GAME_MAP_GET_INDEX(row, column)].unk_4[0] != 0) {
                if (cells[GAME_MAP_GET_INDEX(row, column)].unk_2 == 0) {
                    if (mapGrid->cells[GAME_MAP_GET_INDEX(row + 1, column)].unk_2 != 1) {
                        cells[GAME_MAP_GET_INDEX(row, column)].unk_2 = 4;
                    }
                } else if (cells[GAME_MAP_GET_INDEX(row, column)].unk_2 == 1) {
                    if ((cells[GAME_MAP_GET_INDEX(row, column)].unk_1 ==
                         cells[GAME_MAP_GET_INDEX(row, column)].unk_2) ||
                        (mapGrid->cells[GAME_MAP_GET_INDEX(row - 1, column)].unk_2 != 0)) {
                        cells[GAME_MAP_GET_INDEX(row, column)].unk_2 = 4;
                    }
                }
            }
        }
    }
}
#else
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", dm_h_ball_chack);
#endif
#endif

#if VERSION_CN
#ifdef NON_EQUIVALENT
void dm_h_ball_chack(GameMapGrid *mapGrid) {
    s32 var_a2;

    for (var_a2 = 0; var_a2 < 8U; var_a2++) {
        GameMapCell *cells;
        s32 var_t0;
        s32 var_t1;
        s32 var_t2;

        cells = mapGrid->cells;
        var_t1 = -8;
        var_t0 = 8;

        for (var_t2 = 0; var_t2 < 0x10U; var_t2++) {
            s32 cellIndex = var_t2 * 8 + var_a2; // GAME_MAP_GET_INDEX(var_t2, var_a2);

            if (cells[cellIndex].unk_4[0] != 0) {
                if (cells[cellIndex].unk_2 == 0) {
                    if (cells[var_t0 + var_a2].unk_2 != 1) {
                        cells[cellIndex].unk_2 = 4;
                    }
                } else if (cells[cellIndex].unk_2 == 1) {
                    if ((cells[cellIndex].unk_1 == cells[cellIndex].unk_2) || (cells[var_t1 + var_a2].unk_2 != 0)) {
                        cells[cellIndex].unk_2 = 4;
                    }
                }
            }

            var_t1 += 8;
            var_t0 += 8;
        }
    }
}
#else
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", dm_h_ball_chack);
#endif
#endif

#if VERSION_US || VERSION_CN
void dm_w_ball_chack(GameMapGrid *mapGrid) {
    u32 row;

    for (row = 0; row < GAME_MAP_ROWS - 1; row++) {
        u32 column;

        for (column = 0; column < GAME_MAP_COLUMNS; column++) {
            GameMapCell *cells = mapGrid->cells;

            if (cells[GAME_MAP_GET_INDEX(row, column)].unk_4[0] != 0) {
                if (cells[GAME_MAP_GET_INDEX(row, column)].unk_2 == 2) {
                    if (cells[GAME_MAP_GET_INDEX(row, column + 1)].unk_2 != 3) {
                        cells[GAME_MAP_GET_INDEX(row, column)].unk_2 = 4;
                    }
                } else if ((cells[GAME_MAP_GET_INDEX(row, column)].unk_2 == 3) &&
                           (cells[GAME_MAP_GET_INDEX(row, column - 1)].unk_2 != 2)) {
                    cells[GAME_MAP_GET_INDEX(row, column)].unk_2 = 4;
                }
            }
        }
    }
}
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", dm_black_up);
#endif

#if VERSION_CN
#ifdef NON_EQUIVALENT
// should be equivalent, but I'm not sure
bool dm_black_up(struct_game_state_data *gameStateDataP, GameMapGrid *mapGrid) {
    GameMapCell *temp_a2;
    temp_a2 = &mapGrid->cells;

    if ((gameStateDataP->unk_048 != 0) && (gameStateDataP->unk_049 == 0)) {
        gameStateDataP->unk_036++;
        if (gameStateDataP->unk_036 >= 6U) {
            u8 temp = (u8)((gameStateDataP->unk_040 - 1) * 8);
            s32 var_a3;

            gameStateDataP->unk_036 = 0;

            for (var_a3 = 0; var_a3 < 8U; var_a3++) {
                s32 index = temp + var_a3;

                if (temp_a2[index].unk_4[0] != 0) {
                    temp_a2[index].unk_3 += 3;
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
#else
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", dm_black_up);
#endif
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", dm_broken_set);
#endif

#if VERSION_CN
#ifdef NON_EQUIVALENT
bool dm_broken_set(struct_game_state_data *gameStateData, GameMapGrid *mapGrid) {
    struct_game_state_data_unk_050 sp20[0x10];
    struct_game_state_data_unk_050 *ptr;
    enum bool var_v1;
    s32 var_s1;
    u16 *temp_t3;
    u16 *var_a0;
    u16 *var_a1;
    u16 *var_a1_2;
    u16 *var_a2;
    u16 *var_a2_2;
    u16 *var_a3;
    u16 *var_a3_2;
    u16 *var_t0;
    u16 temp_v0_3;
    u16 temp_v0_4;
    u16 temp_v1_2;
    u16 temp_v1_3;
    u32 temp_v0_2;
    u32 var_s0;
    u8 *temp_v0;
    u8 temp_v1;

    u16 *temp;

    var_v1 = false;
    if (gameStateData->unk_050[0].unk_0 == 0) {
        temp_v1 = gameStateData->unk_03A;
        if (gameStateData->unk_03B < temp_v1) {
            gameStateData->unk_03B = temp_v1;
        }

        gameStateData->unk_03A = 0;
        gameStateData->unk_039 = 0;
        gameStateData->unk_037 = 0;
        gameStateData->unk_038 = 0;

        for (var_s0 = 0; var_s0 < 4U; var_s0++) {
            gameStateData->unk_03C[var_s0] = 0;
        }

        for (var_s0 = 0, var_s1 = 7; var_s0 < 0x10U; var_s0 += 2, var_s1--) {
            temp_v0_2 = gameStateData->unk_050[0].unk_0 & (3 << var_s0);
            if (temp_v0_2 != 0) {
                set_map(mapGrid, var_s1, 1, 4, (temp_v0_2 >> var_s0) - 1);
            }
        }

        dm_h_ball_chack(mapGrid);
        dm_w_ball_chack(mapGrid);
        set_down_flg(mapGrid);

        for (var_s0 = 0; var_s0 < 0x10U; var_s0++) {
            sp20[var_s0].unk_0 = gameStateData->unk_050[var_s0].unk_0;
            sp20[var_s0].unk_2 = gameStateData->unk_050[var_s0].unk_2;
            gameStateData->unk_050[var_s0].unk_0 = 0;
            gameStateData->unk_050[var_s0].unk_2 = 0;
        }

        ptr = &sp20[1];
        for (var_s0 = 0; var_s0 < 0xFU; var_s0++) {
            gameStateData->unk_050[var_s0].unk_0 = ptr[var_s0].unk_0;
            gameStateData->unk_050[var_s0].unk_2 = ptr[var_s0].unk_2;
        }

        var_v1 = true;
    }
    return var_v1;
}
#else
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", dm_broken_set);
#endif
#endif

#if VERSION_US || VERSION_CN
void dm_calc_erase_score_pos(struct_game_state_data *arg0, GameMapGrid *mapGrid, dm_calc_erase_score_pos_arg2 *arg2) {
    s32 row;
    s32 var_t2 = 0;

    arg2->unk_4 = 0;
    arg2->unk_0 = 0;

    for (row = 0; row < GAME_MAP_ROWS - 1; row++) {
        s32 column;

        for (column = 0; column < GAME_MAP_COLUMNS; column++) {
            GameMapCell *cell = &mapGrid->cells[GAME_MAP_GET_INDEX_ALT(row, column)];

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

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", func_800620FC);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", func_8006258C);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", func_800626A4);
#endif

// bool?
s32 dm_calc_capsel_pos(struct_game_state_data *gameStateDataRef, s32 arg1[2], s32 arg2[2]);

#if VERSION_CN
#ifdef NON_EQUIVALENT
// maybe equivalent
s32 dm_calc_capsel_pos(struct_game_state_data *gameStateDataRef, s32 arg1[2], s32 arg2[2]) {
    f32 temp_ft2;
    f32 temp_ft3;
    f32 var_fa0;
    s32 var_t0;
    s32 var_a0;
    u8 temp_a1;
    u8 temp_a3;
    struct_game_state_data_unk_178 *temp_s1;
    s32 var_s2;
    u32 var_v0;

    s32 what = 0x24;

    temp_s1 = &gameStateDataRef->unk_178;
    if (temp_s1->unk_8 == 0) {
        return 0;
    }

    if (gameStateDataRef->unk_00C == 3) {
        temp_a1 = gameStateDataRef->unk_02F;
        if (gameStateDataRef->unk_02C == 0) {
            var_a0 = temp_a1 >> 2;
        } else {
            var_a0 = temp_a1 >> 1;
        }

        if (var_a0 < 0) {
            var_v0 = var_a0 + 3;
        } else {
            var_v0 = var_a0;
        }

        var_a0 = (var_a0 - (((s32)var_v0 >> 2) * 4)) + 4;

        var_s2 = 0;
        if ((var_a0 == 5) || (var_a0 == 7)) {
            var_s2 = 5;
        }

        if (gameStateDataRef->unk_178.unk_0[0] == gameStateDataRef->unk_178.unk_0[1]) {
            switch (var_a0) {
                case 4:
                case 6:
                    throw_rotate_capsel(temp_s1);
                    break;
            }
        } else {
            switch (var_a0) {
                case 5:
                case 7:
                    throw_rotate_capsel(temp_s1);
                    break;
            }
        }

        temp_a3 = gameStateDataRef->unk_02F;

        if (gameStateDataRef->unk_02F < (FlyingCnt[gameStateDataRef->unk_02C] / 3)) {
            var_fa0 = ((what / (FlyingCnt[gameStateDataRef->unk_02C] / 3)) * gameStateDataRef->unk_02F);
        } else if (gameStateDataRef->unk_02F < ((FlyingCnt[gameStateDataRef->unk_02C] / 3) * 2)) {
            var_fa0 = what;
        } else {
            f32 temp = gameStateDataRef->unk_02F;

            temp -= ((FlyingCnt[gameStateDataRef->unk_02C] * 2) / 3);
            var_fa0 = (2.0f * temp);
            var_fa0 = what - var_fa0;
        }

        temp_ft3 = (f32)(gameStateDataRef->unk_006 + (gameStateDataRef->unk_00A * temp_s1->unk_0[0]));
        temp_ft2 = (f32)(gameStateDataRef->unk_008 + (gameStateDataRef->unk_00A * (temp_s1->unk_2[0] - 1)));
        temp_ft3 += ((218.0f - temp_ft3) / (FlyingCnt[gameStateDataRef->unk_02C] - 1)) *
                    (FlyingCnt[gameStateDataRef->unk_02C] - temp_a3);
        temp_ft2 += ((52.0f - temp_ft2) / (FlyingCnt[gameStateDataRef->unk_02C] - 1)) *
                    (FlyingCnt[gameStateDataRef->unk_02C] - temp_a3);

        for (var_t0 = 0; var_t0 < 2; var_t0++) {
            arg1[var_t0] = (u32)temp_ft3 + var_s2 + (gameStateDataRef->unk_00A * (temp_s1->unk_0[var_t0] - 3));
            arg2[var_t0] = (((u32)temp_ft2 + var_s2) - (u16)var_fa0) +
                           (gameStateDataRef->unk_00A * (temp_s1->unk_2[var_t0] + 1) + 1);
        }
    } else if (temp_s1->unk_2[0] <= 0) {
        for (var_t0 = 0; var_t0 < 2; var_t0++) {
            arg1[var_t0] = gameStateDataRef->unk_006 + (gameStateDataRef->unk_00A * temp_s1->unk_0[var_t0]);
            arg2[var_t0] =
                (gameStateDataRef->unk_008 + gameStateDataRef->unk_00A * gameStateDataRef->unk_178.unk_2[var_t0]) - 0xA;
        }
    } else {
        for (var_t0 = 0; var_t0 < 2; var_t0++) {
            arg1[var_t0] = gameStateDataRef->unk_006 + (gameStateDataRef->unk_00A * temp_s1->unk_0[var_t0]);
            arg2[var_t0] =
                gameStateDataRef->unk_008 + gameStateDataRef->unk_00A * gameStateDataRef->unk_178.unk_2[var_t0] + 1;
        }
    }

    return 1;
}
#else
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", dm_calc_capsel_pos);
#endif
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", func_80069034_cn);
#endif

void dm_draw_capsel_by_cpu_tentative(struct_game_state_data *gameStateDataRef, s32 arg1[2], s32 arg2[2]);

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", dm_draw_capsel_by_cpu_tentative);
#endif

#if VERSION_US
UNK_PTR *dm_game_heap_top(void) {
    return &heapTop;
}
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", dm_game_heap_top);
#endif

#if VERSION_US
AnimeState *get_virus_anime_state(s32 arg0) {
    return &watchGame->animeStates[arg0];
}
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", func_800693E8_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", func_80069400_cn);
#endif

#if VERSION_US
AnimeSmog *get_virus_smog_state(s32 arg0) {
    struct_watchGame *ptr = watchGame;

    return &ptr->animeSmogs[arg0];
}
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", dm_get_mtx_buf);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", dm_get_vtx_buf);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", func_80062920);
#endif

#if VERSION_CN
Mtx *dm_get_mtx_buf(void) {
    return gameGeom->mtxBuf[gfx_gtask_no];
}
#endif

#if VERSION_CN
Vtx *dm_get_vtx_buf(void) {
    return gameGeom->vtxBuf[gfx_gtask_no];
}
#endif

#if VERSION_CN
void func_80062920(void) {
    struct_watchGame *ptr = watchGame;
    s32 i;

    for (i = 0; i < evs_playcnt; i++) {
        ptr->unk_888[i] = 0;
    }

    initEtcWork(ptr->unk_884, evs_playcnt);
}
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", func_800694C8_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", func_800694E0_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", func_8006950C_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", func_80069538_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", func_80069564_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", func_800695A0_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", func_800695CC_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", func_800695F8_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", func_80069624_cn);
#endif

#if VERSION_US
void func_80062978(s32 index, s32 arg1) {
    watchGame->unk_888[index] = arg1;
}
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", func_80062990);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", func_800629AC);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", func_800629C8);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", func_800629E4);
#endif

#if VERSION_US
void func_80062A08(s32 index) {
    func_80062978(index, 0xB4);
}
#endif

#if VERSION_US
void func_80062A24(s32 index) {
    func_80062978(index, 0xB4);
}
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", func_80062A40);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", func_80062A5C);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", func_80062A8C);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", func_80062A8C);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", func_80062AA8);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", func_80062AA8);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", func_80062AC4);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", func_80062AC4);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", func_80062AE0);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", func_800696CC_cn);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", func_80062AFC);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", func_80062AFC);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", func_80062B18);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", func_80062B18);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", func_80062B34);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", func_80062B34);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", func_80062B50);
#endif

#if VERSION_CN
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

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", func_80062B84);
#endif

#if VERSION_CN
void func_80062B84(struct_watchGame_unk_9D0 *arg0) {
    func_80062B50(arg0, 0, 0, 0, 0, 0, 0);
    arg0->unk_28 = 0;
}
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", func_80062BC4);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", func_800697F0_cn);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", timeAttackResult_update);
#endif

s32 func_800697F0_cn(struct_watchGame_unk_9D0 *arg0);
extern UNK_TYPE4 _n_1199[];

#if VERSION_CN
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
                s32 var_v0_2;
                s32 var_a0_2;

                if (arg0->unk_14 > 6) {
                    var_v0_2 = 6;
                } else {
                    var_v0_2 = arg0->unk_14;
                }

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
                    u32 var_v1;

                    var_v1 = arg0->unk_20 + var_a0_2;
                    if (var_v1 > 0x98961C) {
                        var_v1 = 0x98961C;
                    }
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
            v1 = func_800697F0_cn(arg0) == 0;
            break;
    }

    return v1;
}
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", func_80062DA4);
#endif

#if VERSION_CN
void func_80062DA4(struct_watchGame_unk_9D0 *arg0) {
    while (timeAttackResult_update(arg0, 0)) {}
}
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", func_80062DD8);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", func_80069A2C_cn);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", func_80062E84);
#endif

#if VERSION_CN
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

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/dm_game_main", RO_800C8318_cn);
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/dm_game_main", RO_800C8328_cn);
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/dm_game_main", RO_800C832C_cn);
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/dm_game_main", RO_800C8338_cn);
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/dm_game_main", RO_800C8340_cn);
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/dm_game_main", RO_800C8348_cn);
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/dm_game_main", RO_800C836C_cn);
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/dm_game_main", RO_800C838C_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/dm_game_main", _posP4CharBase);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/dm_game_main", RO_800C83B4_cn);
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/dm_game_main", RO_800C83FC_cn);
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/dm_game_main", RO_800C848C_cn);
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/dm_game_main", RO_800C849C_cn);
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/dm_game_main", RO_800C84AC_cn);
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

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/dm_game_main", RO_800B1EB8);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", scoreNums_set);
#endif

#if VERSION_CN
#ifdef NON_EQUIVALENT
void scoreNums_set(struct_watchGame_unk_0B8 *arg0, u32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 sp18[0x10];
    s32 var_a2;
    s32 var_s0;
    s32 var_s2;
    struct_watchGame_unk_0B8_unk_00 *temp_v0;

    arg2 = CLAMP(arg2 - 1, 0, 5);

    var_a2 = 0;
    while (arg1 != 0) {
        sp18[arg1] = arg1 % 10;
        arg1 /= 0xA;
        var_a2 += 1;
    }

    var_s2 = arg3 - (((var_a2 * 7) + 1) / 2);
    for (var_s0 = var_a2 - 1; var_s0 >= 0; var_s0--) {
        temp_v0 = &arg0->unk_00[arg0->unk_A0];
        temp_v0->unk_00 = var_s2;
        var_s2 += 7;
        temp_v0->unk_04 = arg4 - 6;
        temp_v0->unk_08 = sp18[var_s0];
        temp_v0->unk_0C = arg2;
        temp_v0->unk_10 = 0.0f;
        arg0->unk_A0 = WrapI(0, 8, arg0->unk_A0 + 1);
    }
}
#else
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", scoreNums_set);
#endif
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", backup_game_state);
#endif

#if VERSION_CN
void backup_game_state(s32 index) {
    struct_gameBackup *ptr = gameBackup[index];
    s32 i;

    ptr->unk_0000 = *watchGame;

    for (i = 0; i < ARRAY_COUNTU(ptr->unk_0B60); i++) {
        ptr->unk_0B60[i] = game_state_data[i];
    }

    for (i = 0; i < ARRAY_COUNTU(ptr->unk_1A70); i++) {
        s32 j;

        for (j = 0; j < ARRAY_COUNTU(game_map_data[i].cells); j++) {
            ptr->unk_1A70[i].cells[j] = game_map_data[i].cells[j];
        }
    }

    ptr->highScore = evs_high_score;
    ptr->gameTime = evs_game_time;
}
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", resume_game_state);
#endif

#if VERSION_CN
void resume_game_state(s32 index) {
    struct_gameBackup *ptr = gameBackup[index];
    s32 i;

    *watchGame = ptr->unk_0000;

    for (i = 0; i < ARRAY_COUNTU(ptr->unk_0B60); i++) {
        game_state_data[i] = ptr->unk_0B60[i];
    }

    for (i = 0; i < ARRAY_COUNTU(ptr->unk_1A70); i++) {
        s32 j;

        for (j = 0; j < ARRAY_COUNTU(game_map_data[i].cells); j++) {
            game_map_data[i].cells[j] = ptr->unk_1A70[i].cells[j];
        }
    }

    evs_high_score = ptr->highScore;
    evs_game_time = ptr->gameTime;
}
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", func_80063378);
#endif

#if VERSION_CN
void func_80063378(void) {
    struct_watchGame *watchGameRef = watchGame;

    if (watchGameRef->unk_000 == 0) {
        backup_game_state(1);
    }

    resume_game_state(0);
    watchGameRef->unk_000 = 1;
}
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", func_800633C0);
#endif

#if VERSION_CN
void func_800633C0(void) {
    struct_watchGame *watchGameRef = watchGame;

    if (watchGameRef->unk_000 != 0) {
        resume_game_state(1);
        watchGameRef->unk_000 = 0;
    }
}
#endif

#if VERSION_US
void func_800633FC(void) {
    if (watchGame->unk_000 != 0) {
        replay_play_init();
    } else {
        replay_record_init(evs_playcnt);
    }
}
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", func_8006A0C8_cn);
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

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", func_8006A1E0_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", dm_capsel_down);
#endif

#if VERSION_US
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

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", dm_capsel_down);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", func_80063844);
#endif

#if VERSION_CN
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

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", dm_set_attack_2p);
#endif

#if VERSION_CN
#ifdef NON_MATCHING
s32 dm_set_attack_2p(struct_game_state_data *gameStateDataRef) {
    s32 temp_v0;
    s32 var_s0;
    s32 var_s2;
    s32 var_t1;
    s32 var_v1;
    struct_game_state_data *temp_s3;
    u8 var_a0;

    if (gameStateDataRef->unk_03A < 2U) {
        return 0;
    }

    temp_s3 = &game_state_data[gameStateDataRef->unk_04B ^ 1];
    if (gameStateDataRef->unk_03A < 5U) {
        var_a0 = gameStateDataRef->unk_03A;
    } else {
        var_a0 = 4;
    }

    var_v1 = 0;
    while (1) {
        if (temp_s3->unk_050[var_v1].unk_0 != 0) {
            var_s2 = 0;
            for (var_s0 = 0; var_s0 < 8; var_s0++) {
                if (temp_s3->unk_050[var_v1].unk_0 & (3 << (var_s0 * 2))) {
                    var_s2 |= 1 << var_s0;
                    var_t1 = var_s0 & 1;
                }
            }

            for (var_s0 = 0; var_s0 < 8; var_s0++) {
                if ((var_s0 & 1) == var_t1) {
                    var_s2 ^= 1 << var_s0;
                }
            }

            if (var_s2 != 0) {
                break;
            }

            var_v1++;
            if (var_v1 > 0) {
                return 1;
            }
        } else {
            var_s2 = func_80063844(var_a0);
            break;
        }
    }

    temp_s3->unk_050[var_v1].unk_2 = gameStateDataRef->unk_04B;

    for (var_s0 = 0; var_s0 < 8; var_s0++) {
        if (((var_s2 >> var_s0) & 1)) {
            while (*(u32 *)gameStateDataRef->unk_03C & ~0xFF) {
                temp_v0 = random(3);
                if (gameStateDataRef->unk_03C[temp_v0] != 0) {
                    gameStateDataRef->unk_03C[temp_v0] -= 1;
                    temp_s3->unk_050[var_v1].unk_2 |= (temp_v0 + 1) << (var_s0 * 2);
                    break;
                }
            }
        }
    }

    return 1;
}

#else
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", dm_set_attack_2p);
#endif
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", dm_set_attack_4p);
#endif

#if VERSION_CN
#if 0
s32 func_80063844(s32, s32 *);
s32 random(?, s32 *);
extern ? _posP4CharBase;
extern ? attack_table_1531;

s32 dm_set_attack_4p(void *arg0) {
    s32 sp20;
    s32 sp40;
    s32 sp44;
    s32 sp48;
    s32 *sp50;
    void *sp54;
    s32 *sp58;
    ? var_v0;
    s16 *var_s7;
    s32 *temp_a0_3;
    s32 *temp_t3;
    s32 *temp_v1_3;
    s32 *var_a0;
    s32 *var_a0_2;
    s32 *var_a1_2;
    s32 *var_a1_3;
    s32 *var_a1_4;
    s32 *var_t3;
    s32 *var_v1;
    s32 temp_a0_2;
    s32 temp_a0_5;
    s32 temp_a0_6;
    s32 temp_a1;
    s32 temp_v0_2;
    s32 temp_v0_4;
    s32 temp_v0_5;
    s32 temp_v0_6;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 temp_v1_4;
    s32 temp_v1_5;
    s32 temp_v1_6;
    s32 var_a0_3;
    s32 var_fp;
    s32 var_s0_2;
    s32 var_s0_4;
    s32 var_s0_5;
    s32 var_s0_7;
    s32 var_s1;
    s32 var_s1_2;
    s32 var_s6_2;
    s32 var_s6_3;
    s32 var_s6_4;
    s32 var_s6_5;
    s32 var_v0_2;
    s32 var_v0_3;
    s8 temp_a2;
    struct_game_state_data *temp_s1;
    struct_watchGame *temp_s4;
    u16 *var_s5;
    u32 var_s0;
    u32 var_s0_3;
    u32 var_s0_6;
    u32 var_s6;
    u8 *temp_a0;
    u8 temp_a0_4;
    u8 temp_v0;
    u8 temp_v0_3;
    u8 var_a1;
    void *temp_s1_2;
    void *temp_s3;
    void *temp_t6;
    void *var_t2;

    var_t2 = arg0;
    temp_s4 = watchGame;
    var_v0 = 0;
    if ((u8) var_t2->unk_3A >= 2U) {
        var_s6 = 0;
        var_v1 = &sp30[0];
        do {
            *var_v1 = 0;
            var_s6 += 1;
            var_v1 += 4;
        } while (var_s6 < 3U);
        var_fp = 0;
        var_s6_2 = 0;
        sp44 = 0;
        sp40 = 0;
        do {
            if (((s32) var_t2->unk_3F >> var_s6_2) & 1) {
                temp_a2 = *(&attack_table_1531 + (var_s6_2 + (var_t2->unk_4B * 3)));
                temp_s1 = &game_state_data[temp_a2];
                var_a1 = temp_s1->unk_04F;
                temp_v0 = temp_s1->unk_048;
                if (var_a1 == var_t2->unk_4F) {
                    if (temp_v0 == 0) {
                        sp44 |= 1 << temp_a2;
                        goto block_12;
                    }
                } else if ((temp_v0 == 0) || ((temp_s1->unk_01C == 0x12) && (temp_s1->unk_04A != 0))) {
                    sp40 |= 1 << temp_a2;
block_12:
                    if (var_fp <= 0) {
                        var_fp = 4;
                        if ((u8) var_t2->unk_3A < 5U) {
                            var_fp = (s32) var_t2->unk_3A;
                        }
                        var_s0 = 0;
                        var_v0_2 = var_fp < 4;
loop_16:
                        temp_t3 = temp_s4->unk_8DC[0];
                        if (var_v0_2 != 0) {
                            var_a1 = var_s0 * 4;
                            temp_v0_2 = *(temp_t3 + (var_a1 + (var_t2->unk_4F * 0x10)));
                            var_s0 += 1;
                            if (temp_v0_2 != -1) {
                                temp_a0 = var_t2 + 0x3C + temp_v0_2;
                                *temp_a0 += 1;
                                var_fp += 1;
                                *(temp_t3 + (var_a1 + (var_t2->unk_4F * 0x10))) = -1;
                            }
                            var_v0_2 = var_fp < 4;
                            if (var_s0 < 4U) {
                                goto loop_16;
                            }
                        }
                        var_s0_2 = 0;
                        var_s1 = var_fp > 0;
                        if (var_s1 != 0) {
                            temp_s3 = var_t2 + 0x3C;
loop_22:
                            if ((var_t2->unk_3C + var_t2->unk_3D + var_t2->unk_3E) > 0) {
                                sp54 = var_t2;
                                temp_a0_2 = random(3, (s32 *) var_a1);
                                var_a1 = (u8) (temp_s3 + temp_a0_2);
                                temp_v0_3 = *var_a1;
                                if (temp_v0_3 != 0) {
                                    var_s0_2 += 1;
                                    var_s1 = var_s0_2 < var_fp;
                                    temp_a0_3 = &(&sp30[0])[temp_a0_2];
                                    *var_a1 = (u8) (temp_v0_3 - 1);
                                    *temp_a0_3 += 1;
                                }
                                if (var_s1 != 0) {
                                    goto loop_22;
                                }
                            }
                        }
                    }
                }
            }
            var_s6_2 += 1;
        } while (var_s6_2 < 3);
        var_s6_3 = 0;
        if ((sp40 + sp44) == 0) {
            return 0;
        }
        var_t3 = temp_s4->unk_8DC[0];
        sp48 = 0;
        do {
            if ((sp40 >> var_s6_3) & 1) {
                temp_a0_4 = var_t2->unk_4B;
                temp_s1_2 = sp48 + game_state_data;
                temp_v1 = temp_a0_4 * 8;
                temp_t6 = &_posP4CharBase + 4;
                temp_v0_4 = temp_s1_2->unk_4B * 8;
                var_s0_3 = 0;
                sp54 = var_t2;
                sp58 = var_t3;
                add_attack_effect((s32) temp_a0_4, *(temp_v1 + &_posP4CharBase), *(temp_v1 + temp_t6), *(temp_v0_4 + &_posP4CharBase), *(temp_v0_4 + temp_t6));
                var_a1_2 = &sp20;
                var_a0 = &sp30[0];
                do {
                    temp_v1_2 = *var_a0;
                    var_a0 += 4;
                    var_s0_3 += 1;
                    *var_a1_2 = temp_v1_2;
                    var_a1_2 += 4;
                } while (var_s0_3 < 3U);
                var_s0_4 = 0;
                var_s5 = temp_s1_2 + 0x50;
                var_s7 = temp_s1_2 + 0x52;
                do {
                    if (*var_s5 == 0) {
                        sp54 = var_t2;
                        sp58 = var_t3;
                        var_a1_2 = func_80063844(var_fp, var_a1_2);
                        var_s1_2 = 0;
                        *var_s7 = (s16) var_t2->unk_4B;
                        var_v0_3 = (s32) var_a1_2 >> 0;
                        do {
                            if ((var_v0_3 & 1) && ((sp20 + sp24 + sp28) > 0)) {
loop_39:
                                sp50 = var_a1_2;
                                sp54 = var_t2;
                                sp58 = var_t3;
                                temp_a0_5 = random(3, var_a1_2);
                                temp_v1_3 = &(&sp20)[temp_a0_5];
                                temp_v0_5 = *temp_v1_3;
                                if (temp_v0_5 > 0) {
                                    *temp_v1_3 = temp_v0_5 - 1;
                                    *var_s5 |= (temp_a0_5 + 1) << (var_s1_2 * 2);
                                } else if ((sp20 + sp24 + sp28) > 0) {
                                    goto loop_39;
                                }
                            }
                            var_s1_2 += 1;
                            var_v0_3 = (s32) var_a1_2 >> var_s1_2;
                        } while (var_s1_2 < 8);
                    }
                    var_s5 += 4;
                    var_s0_4 += 1;
                    var_s7 += 4;
                } while (var_s0_4 < 0x10);
            }
            var_s6_3 += 1;
            sp48 += 0x3C4;
        } while (var_s6_3 < 4);
        var_s0_5 = 0;
        var_s6_4 = 0;
        do {
            temp_v1_4 = var_t2->unk_4F * 0x10;
            temp_a0_6 = *(var_t3 + ((var_s6_4 * 4) + temp_v1_4));
            var_s6_4 += 1;
            if (temp_a0_6 != -1) {
                *(var_t3 + ((var_s0_5 * 4) + temp_v1_4)) = temp_a0_6;
                var_s0_5 += 1;
            }
        } while (var_s6_4 < 4);
        if (var_s0_5 < 4) {
            do {
                temp_v0_6 = var_s0_5 * 4;
                var_s0_5 += 1;
                *(var_t3 + (temp_v0_6 + (var_t2->unk_4F * 0x10))) = -1;
            } while (var_s0_5 < 4);
        }
        var_s6_5 = 0;
        do {
            if ((sp44 >> var_s6_5) & 1) {
                var_s0_6 = 0;
                var_a1_3 = &sp20;
                var_a0_2 = &sp30[0];
                do {
                    temp_v1_5 = *var_a0_2;
                    var_a0_2 += 4;
                    var_s0_6 += 1;
                    *var_a1_3 = temp_v1_5;
                    var_a1_3 += 4;
                } while (var_s0_6 < 3U);
                var_a0_3 = 0;
                var_s0_7 = 0;
                do {
                    temp_a1 = var_s0_7 * 4;
                    if ((*(var_t3 + (temp_a1 + (var_t2->unk_4F * 0x10))) == -1) && (var_a0_3 < 3)) {
                        var_a1_4 = &(&sp20)[var_a0_3];
loop_60:
                        temp_v1_6 = *var_a1_4;
                        if (temp_v1_6 <= 0) {
                            var_a0_3 += 1;
                            var_a1_4 += 4;
                            if (var_a0_3 < 3) {
                                goto loop_60;
                            }
                        } else {
                            *var_a1_4 = temp_v1_6 - 1;
                            *(var_t3 + (temp_a1 + (var_t2->unk_4F * 0x10))) = var_a0_3;
                        }
                    }
                    var_s0_7 += 1;
                } while (var_s0_7 < 4);
            }
            var_s6_5 += 1;
        } while (var_s6_5 < 4);
        var_v0 = 1;
        /* Duplicate return node #68. Try simplifying control flow for better match */
        return var_v0;
    }
    return var_v0;
}
#else
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", dm_set_attack_4p);
#endif
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", func_80063FF4);
#endif

void func_8006AE60_cn(void);
#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", func_8006AE60_cn);
#endif

void save_visible_fall_point_flag(void);
#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", save_visible_fall_point_flag);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", func_8006AF8C_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", func_8006AFE8_cn);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", func_8006408C);
#endif

#if VERSION_US
void func_80064130(s32 arg0, s32 arg1) {
    watchGame->unk_348[arg0] = arg1;
    watchGame->unk_358[arg0] = 0;
    watchGame->unk_368[arg0] = -1;

    switch (watchGame->unk_348[arg0]) {
        case 2:
        case 3:
        case 4:
        case 5:
            watchGame->unk_358[arg0]++;
            break;
    }
}
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", func_8006417C);
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

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", func_80064298);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", func_8006B184_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", func_8006B238_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", func_8006B328_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", func_8006B5A0_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", func_8006B6D8_cn);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", func_8006431C);
#endif

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/dm_game_main", RO_800B1EC0);
#endif

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/dm_game_main", RO_800B1ECC);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", set_bottom_up_virus);
#endif

#if VERSION_US
bool bottom_up_bottle_items(GameMapGrid *mapGrid) {
    s32 i;
    bool ret = false;
    s32 column;
    GameMapCell *cell;
    s32 var;

    for (i = 0; i < GAME_MAP_COLUMNS; i++) {
        if (mapGrid->cells[i].unk_4[0] != 0) {
            ret = true;
        }
    }

    var = (GAME_MAP_ROWS - 1) * GAME_MAP_COLUMNS;
    for (i = 0, cell = &mapGrid->cells[GAME_MAP_GET_INDEX(1, 0)]; i < var; i++, cell++) {
        mapGrid->cells[i] = *cell;
        mapGrid->cells[i].unk_1--;
    }

    var += GAME_MAP_COLUMNS;
    for (column = 0; i < var; i++, column++) {
        bzero(&mapGrid->cells[i], sizeof(GameMapCell));
        mapGrid->cells[i].unk_0 = column;
        mapGrid->cells[i].unk_1 = 0x11;
    }

    return ret;
}
#endif

#if VERSION_US
#ifdef NON_EQUIVALENT
extern s32 D_800B1ECC[];
extern f32 RO_800B1C98[];

void add_taiQ_bonus_wait(struct_game_state_data *arg0) {
    s32 var_a0;
    s32 i;
    struct_watchGame *watchGameP = watchGame;
    s32 *ptr2;

    if (evs_gamemode != ENUM_EVS_GAMEMODE_2) {
        return;
    }

    if (arg0->unk_03A < 2) {
        return;
    }

    watchGameP->unk_3C8 += (arg0->unk_03A - 1) * 0.25;
    watchGameP->unk_3C8 = MIN(watchGameP->unk_3C8, RO_800B1C98[arg0->unk_16C]);

    ptr2 = D_800B1ECC;
    var_a0 = ptr2[0] * (arg0->unk_037 + arg0->unk_03A);

    for (i = 1; i < arg0->unk_039; i++) {
        s32 *var_v0_2;

        if (i < 5U) {
            var_v0_2 = &ptr2[i];
        } else {
            var_v0_2 = &ptr2[5];
        }

        var_a0 += *var_v0_2;
    }

    watchGameP->unk_410 += var_a0;
}
#else
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", add_taiQ_bonus_wait);
#endif
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", countLeadingZeros);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", countLeadingZeros);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", dm_game_eep_write_callback);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", func_8006B830_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", func_8006B8FC_cn);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", func_80064940);
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

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", func_8006B99C_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/dm_game_main", RO_800C84C8_cn);
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/dm_game_main", attack_table_1531);
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/dm_game_main", RO_800C84DC_cn);
#endif

#if VERSION_US
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
                s32 var_s0_2 = evs_story_no;
                s32 temp_s1 = (s32)story_proc_no >= STORY_PROC_NO_12;

                temp_a0->unk_B4.unk_02 = CLAMP(var_s0_2 - 1, 0, 7);

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

            if (arg0->unk_014 != 0x11) {
                return;
            }
            break;

        default:
            return;
    }

    if ((arg0->unk_014 != 2) && (arg0->unk_04C == 0)) {
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

#if VERSION_US
#ifdef NON_EQUIVALENT
// regalloc
s32 dm_game_main_cnt_1P(struct_game_state_data *arg0, GameMapGrid *mapGrid, s32 arg2) {
    struct_watchGame *temp_s3 = watchGame;
    dm_calc_erase_score_pos_arg2 sp20;
    s32 var_a0_2;
    u8 *var_t0;
    s32 var_s0;
    s32 var_s1;
    s32 var_s4;
    s32 var_v0_2;

    dm_query_pause_player(arg0);
    animeState_update(&arg0->unk_094);
    func_80062EC0(&temp_s3->unk_0B8[arg2]);

    if (((evs_gamemode == ENUM_EVS_GAMEMODE_3) && (evs_game_time >= 10800) && (arg0->unk_020 == 1))) {
        return -1;
    }

    switch (arg0->unk_00C) {
        case 0x1:
            dm_set_virus(arg0, mapGrid, &virus_map_data[arg2], &virus_map_disp_order[arg2]);
            return 3;

        case 0x2:
            return 3;

        case 0x3:
            arg0->unk_02F++;
            if (arg0->unk_02F == FlyingCnt[arg0->unk_02C]) {
                func_80060FA0(&arg0->unk_178, ((CapsMagazine[arg0->unk_033] / 16) % 3),
                              (CapsMagazine[arg0->unk_033] % 3));
                arg0->unk_00C = 4;
                arg0->unk_02F = 0x1E;
                dm_capsel_down(arg0, mapGrid);
            }
            break;

        case 0x5:
            if (dm_check_game_over(arg0, mapGrid)) {
                for (var_s0 = 0; var_s0 < 3; var_s0++) {
                    if (temp_s3->animeStates[var_s0].animeSeq.unk_10 != 4) {
                        animeState_set(&temp_s3->animeStates[var_s0], 3);
                    }
                }

                if (evs_gamemode == ENUM_EVS_GAMEMODE_2) {
                    temp_s3->unk_410 = 0;
                }
                return -1;
            }

            if (dm_h_erase_chack(mapGrid) || dm_w_erase_chack(mapGrid)) {
                arg0->unk_00C = 6;
                arg0->unk_02F = 0;
            } else {
                arg0->unk_00C = 9;
            }
            break;

        case 0x6:
            arg0->unk_02F++;
            if (arg0->unk_02F >= 0x12U) {
                arg0->unk_02F = 0;
                arg0->unk_00C = 7;
                dm_h_erase_chack_set(arg0, mapGrid);
                dm_w_erase_chack_set(arg0, mapGrid);
                dm_h_ball_chack(mapGrid);
                dm_w_ball_chack(mapGrid);
                var_s0 = arg0->unk_025;
                var_s0 -=
                    get_virus_color_count(mapGrid, &temp_s3->unk_418[0], &temp_s3->unk_418[1], &temp_s3->unk_418[2]);
                arg0->unk_025 -= var_s0;
                arg0->unk_170 += var_s0;

                for (var_s0 = 0; var_s0 < 3; var_s0++) {
                    if (temp_s3->unk_418[var_s0] == 0) {
                        if (temp_s3->unk_400[var_s0] == 0) {
                            temp_s3->unk_400[var_s0] = 1;
                            animeState_set(&temp_s3->animeStates[var_s0], 4);
                            animeSmog_start(&temp_s3->animeSmogs[var_s0]);
                            if (arg0->unk_025 != 0) {
                                dm_snd_play_in_game(SND_INDEX_74);
                                dm_snd_play_in_game(SND_INDEX_57);
                            }
                        }
                    } else if ((arg0->unk_03C[3] & (0x10 << var_s0))) {
                        if (temp_s3->unk_410 == 0) {
                            animeState_set(&temp_s3->animeStates[var_s0], 2);
                            dm_snd_play_in_game(SND_INDEX_74);
                        }
                    }
                }

                arg0->unk_03C[3] &= ~0xF0;
                dm_calc_erase_score_pos(arg0, mapGrid, &sp20);
                scoreNums_set(&temp_s3->unk_0B8[arg2], dm_make_score(arg0), arg0->unk_037,
                              arg0->unk_006 + arg0->unk_00A / 2 + sp20.unk_0,
                              arg0->unk_008 + arg0->unk_00A / 2 + sp20.unk_4);
                if (arg0->unk_025 == 0) {
                    if (evs_gamemode != ENUM_EVS_GAMEMODE_2) {
                        arg0->unk_014 = 3;
                        arg0->unk_00C = 0xA;
                        if (arg0->unk_03B < arg0->unk_03A) {
                            arg0->unk_03B = arg0->unk_03A;
                        }
                        return 6;
                    }
                }

                if ((arg0->unk_025 < 4U) && (evs_gamemode != ENUM_EVS_GAMEMODE_2)) {
                    if (temp_s3->unk_3C0 == 0) {
                        temp_s3->unk_3C0 = 1;
                        dm_snd_play_in_game(SND_INDEX_80);
                    }
                    if (temp_s3->unk_3B4 == 0) {
                        temp_s3->unk_3B4 = 1;
                        temp_s3->unk_3B8 = 1;
                    }
                }
                arg0->unk_039 += 1;
                if ((u8)arg0->unk_03A < 2U) {
                    if (arg0->unk_03C[3] & 8) {
                        arg0->unk_03C[3] &= (u8)~0x8;
                        dm_snd_play_in_game(SND_INDEX_56);
                    } else {
                        dm_snd_play_in_game(SND_INDEX_61);
                    }
                } else {
                    if (arg0->unk_03C[3] & 8) {
                        arg0->unk_03C[3] &= ~0x8;
                    }

                    var_s0 = 2;
                    if (arg0->unk_03A - 2 <= 2) {
                        var_s0 = arg0->unk_03A - 2;
                    }
                    // var_s0 = (arg0->unk_03A - 2 <= 2) ? arg0->unk_03A - 2 : 2;

                    dm_snd_play_in_game(_charSE_tbl[arg0->unk_090] + var_s0);
                }
            }
            break;

        case 0x7:
            dm_capsel_erase_anime(arg0, mapGrid);
            break;

        case 0x8:
            go_down(arg0, mapGrid, 0xE);
            break;

        case 0x9:
            add_taiQ_bonus_wait(arg0);
            if ((temp_s3->unk_9BC != 0) && (temp_s3->unk_410 == 0)) {
                arg0->unk_168 = 0;
                arg0->unk_00C = 0xC;
                set_bottom_up_virus(arg0, mapGrid);
                dm_snd_play_in_game(SND_INDEX_101);
            } else {
                if (arg0->unk_039 >= 2U) {
                    var_a0_2 = 0x63;
                    if ((arg0->unk_174 + arg0->unk_039) - 1 < 0x64) {
                        var_a0_2 = (arg0->unk_174 + arg0->unk_039) - 1;
                    }
                    arg0->unk_174 = var_a0_2;
                }

                dm_warning_h_line(arg0, mapGrid);
                dm_set_capsel(arg0);
                dm_capsel_speed_up(arg0);
                dm_attack_se(arg0, arg2);
                animeState_set(&arg0->unk_094, 1);

                if ((arg0->unk_04C == 1) || (((arg0->unk_04C != 1) & (arg2 == 0)) && (aiDebugP1 >= 0))) {
                    aifMakeFlagSet(arg0);
                }

                if (arg0->unk_03B < arg0->unk_03A) {
                    arg0->unk_03B = arg0->unk_03A;
                }
                arg0->unk_00C = 3;
                arg0->unk_02F = 0;
                arg0->unk_031 = 0;
                arg0->unk_03A = 0;
                arg0->unk_039 = 0;
                arg0->unk_037 = 0;
                arg0->unk_038 = 0;

                for (var_s0 = 0; var_s0 < 4; var_s0++) {
                    arg0->unk_03C[var_s0] = 0;
                }
            }
            break;

        case 0xC:
            arg0->unk_168++;
            if (arg0->unk_168 >= arg0->unk_00A) {
                arg0->unk_168 = 0;
                temp_s3->unk_9BC = 0;

                // temp_fv1 = temp_s3->unk_3C8 - 0.5;
                // temp_ft0 = _big_virus_min_wait[arg0->unk_16C];

                // var_fv0 = temp_ft0;
                // if (temp_ft0 < temp_fv1) {
                //    var_fv0 = (f32)temp_fv1;
                //}
                // temp_s3->unk_3C8 = var_fv0;
                // temp_s3->unk_3C8 = (temp_ft0 < temp_fv1) ? temp_fv1 : temp_ft0;
                // temp_s3->unk_3C8 = (_big_virus_min_wait[arg0->unk_16C] < temp_s3->unk_3C8 - 0.5) ? temp_s3->unk_3C8 -
                // 0.5 : _big_virus_min_wait[arg0->unk_16C];
                temp_s3->unk_3C8 = MAX(_big_virus_min_wait[arg0->unk_16C], temp_s3->unk_3C8 - 0.5);

                arg0->unk_00C = 8;
                if (bottom_up_bottle_items(mapGrid)) {
                    return -1;
                }
                arg0->unk_025 = get_virus_color_count(mapGrid, (u8 *)temp_s3->unk_418, (u8 *)&temp_s3->unk_418[1],
                                                      (u8 *)&temp_s3->unk_418[2]);

                for (var_s0 = 0; var_s0 < 3; var_s0++) {
                    if (((u8)temp_s3->unk_418[var_s0] != 0) && (temp_s3->unk_400[var_s0] != 0)) {
                        animeState_set(&temp_s3->animeStates[var_s0], 0);
                        animeSmog_start(&temp_s3->animeSmogs[var_s0]);
                        temp_s3->unk_400[var_s0] = 0;
                    } else if (temp_s3->animeStates[var_s0].animeSeq.unk_10 == 3) {
                        animeState_set(&temp_s3->animeStates[var_s0], 0);
                    }
                }
            }
            break;

        case 0x1A:
        case 0x1C:
            if (arg0->unk_00C == 0x1A) {
                var_v0_2 = func_80062B18(arg2);
            } else {
                var_v0_2 = func_80062AFC(arg2);
            }
            if (var_v0_2 == 0) {
                // ANY_BUTTON
                if (gControllerPressedButtons[main_joy[arg2]] & 0xFF3F) {
                    switch (arg0->unk_00C) {
                        case 0x1A:
                            arg0->unk_014 = 0x14;
                            arg0->unk_00C = 0x1B;
                            break;
                        case 0x1C:
                            arg0->unk_014 = 0x16;
                            arg0->unk_00C = 0x1D;
                            break;
                        default:
                            break;
                    }
                }
            }
            break;

        case 0x1B:
        case 0x1D:
            // ANY_BUTTON
            if (gControllerPressedButtons[main_joy[arg2]] & 0xFF3F) {
                func_80062DA4(&temp_s3->unk_9D0[arg2]);
            }

            timeAttackResult_update(&temp_s3->unk_9D0[arg2], 1);
            func_80060270(arg0, temp_s3->unk_9D0[arg2].unk_24);
            temp_s3->unk_9D0[arg2].unk_24 = 0;
            if (func_80062BC4(&temp_s3->unk_9D0[arg2])) {
                switch (arg0->unk_00C) {
                    case 0x1B:
                        arg0->unk_014 = 3;
                        arg0->unk_00C = 0xA;
                        break;

                    case 0x1D:
                        arg0->unk_014 = 4;
                        arg0->unk_00C = 0xB;
                        break;

                    default:
                        break;
                }
            }
            break;

        case 0xA:
        case 0xB:
            if (arg0->unk_00C == 0xA) {
                var_v0_2 = func_80062B18(arg2);
            } else {
                var_v0_2 = func_80062AFC(arg2);
            }
            if (var_v0_2 == 0) {
                // (Z_TRIG | L_JPAD | L_TRIG | R_TRIG)
                if ((temp_s3->unk_AA8 < 0) && ((gControllerHoldButtons[main_joy[0]] & 0x2230) == 0x2230)) {
                    switch (evs_gamemode) {
                        case ENUM_EVS_GAMEMODE_0:
                            var_s1 = arg0->unk_026;
                            var_s4 = 0;
                            break;

                        case ENUM_EVS_GAMEMODE_3:
                            var_s4 = 1;
                            var_s1 = arg0->unk_16C;
                            break;

                        case ENUM_EVS_GAMEMODE_2:
                            var_s4 = 2;
                            var_s1 = arg0->unk_16C;
                            break;

                        default:
                            break;
                    }

                    if (evs_select_name_no[0] == 8) {
                        var_t0 = &D_800A7360;
                    } else {
                        var_t0 = evs_mem_data[evs_select_name_no[0]].unk_01;
                    }

                    if (temp_s3->unk_AAC[0] == '\0') {
                        func_8007E760(temp_s3->unk_AAC, var_s4, var_s1, arg0->unk_02C, arg0->unk_000 / 10,
                                      (evs_game_time / 6), var_t0);
                        temp_s3->unk_AAC[ARRAY_COUNT(temp_s3->unk_AAC) - 2] = '~';
                        temp_s3->unk_AAC[ARRAY_COUNT(temp_s3->unk_AAC) - 1] = 'z';
                    }
                    msgWnd_clear(&temp_s3->unk_A28);
                    msgWnd_addStr(&temp_s3->unk_A28, _mesPassword);
                    msgWnd_addStr(&temp_s3->unk_A28, temp_s3->unk_AAC);
                    msgWnd_skip(&temp_s3->unk_A28);
                    temp_s3->unk_AA8 = -temp_s3->unk_AA8;
                } else {
                    if (gControllerPressedButtons[main_joy[0]] != 0) {
                        if (temp_s3->unk_AA8 > 0) {
                            temp_s3->unk_AA8 = -temp_s3->unk_AA8;
                        }
                    }

                    switch (retryMenu_input(arg2)) { /* switch 3; irregular */
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
                            if (arg0->unk_004 < 0x3E7U) {
                                arg0->unk_004++;
                            }

                            if ((arg0->unk_026 >= 0x16U) && (temp_s3->unk_378 > 0)) {
                                temp_s3->unk_378--;
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
            }
            break;

        case 0x18:
            switch (retryMenu_input(arg2)) {

                case 0:
                    if (temp_s3->unk_9C4 < 0) {
                        temp_s3->unk_9C4 = arg2;
                    }
                    dm_snd_play_in_game(SND_INDEX_62);
                    break;

                case 1:
                    if (arg0->unk_004 < 0x3E7U) {
                        arg0->unk_004++;
                    }

                    if (((u8)arg0->unk_026 >= 0x16U) && (temp_s3->unk_378 > 0)) {
                        temp_s3->unk_378--;
                        dm_snd_play_in_game(SND_INDEX_78);
                    } else {
                        dm_snd_play_in_game(SND_INDEX_62);
                    }
                    return 2;

                case 2:
                    dm_snd_play_in_game(SND_INDEX_62);
                    return 0x64;

                default:
                    break;
            }
            break;

        default:
            break;
    }

    return 0;
}
#else
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", dm_game_main_cnt_1P);
#endif
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", dm_game_main_cnt_1P);
#endif

#if VERSION_US
#if 0
s32 dm_set_attack_4p(struct_game_state_data *);     /* extern */
s32 func_80062A8C(s32);                             /* extern */
s32 func_80062AA8(s32);                             /* extern */
s32 func_80062AC4(s32);                             /* extern */
? func_80062B34(s32);                               /* extern */
s32 dm_set_attack_2p(struct_game_state_data *);        /* extern */

s32 dm_game_main_cnt(struct_game_state_data *arg0, GameMapGrid *mapGrid, s32 index) {
    dm_calc_erase_score_pos_arg2 sp18;
    s32 temp_s4_3;
    s32 temp_v0_2;
    s32 temp_v0_4;
    s32 temp_v0_5;
    s32 temp_v0_7;
    s32 temp_v1;
    s32 temp_v1_10;
    s32 temp_v1_14;
    s32 temp_v1_5;
    s32 var_a0;
    s32 var_a1;
    s32 var_a1_3;
    s32 var_s3;
    s32 var_s3_2;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v0_5;
    s32 var_v1;
    s32 var_v1_2;
    s32 var_v1_3;
    s32 var_v1_5;
    s32 var_v1_7;
    s8 var_v0_3;
    struct_game_state_data *var_a0_2;
    struct_game_state_data *var_a0_3;
    struct_game_state_data *var_a1_2;
    struct_game_state_data *var_v1_6;
    struct_virus_map_disp_order *temp_a0_2;
    struct_virus_map_disp_order *var_v1_4;
    struct_watchGame *temp_s3;
    u16 temp_s4;
    u16 temp_v1_15;
    u32 temp_v0;
    u8 temp_a0;
    u8 temp_s4_2;
    u8 temp_v0_3;
    u8 temp_v0_6;
    u8 temp_v1_11;
    u8 temp_v1_12;
    u8 temp_v1_13;
    u8 temp_v1_16;
    u8 temp_v1_2;
    u8 temp_v1_3;
    u8 temp_v1_4;
    u8 temp_v1_6;
    u8 temp_v1_7;
    u8 temp_v1_8;
    u8 temp_v1_9;
    void *var_v0_4;
    void *var_v0_6;
    void *var_v0_7;

    temp_s3 = watchGame;
    temp_s4 = gControllerPressedButtons[main_joy[index]];
    dm_query_pause_player(arg0);
    animeState_update(&arg0->unk_094);
    func_80062EC0(&temp_s3->unk_0B8[index]);
    temp_v0 = arg0->unk_020;
    if ((temp_v0 != 1) & (temp_v0 != 0xD)) {
        dm_black_up(arg0, mapGrid);
    }
    if ((evs_gamemode != ENUM_EVS_GAMEMODE_3) || ((u32) evs_game_time < 0x2A30U) || (var_v0 = -1, (arg0->unk_020 != 1))) {
        temp_v0_2 = arg0->unk_00C;
        switch (temp_v0_2) {                        /* switch 1 */
            case 0x1:                               /* switch 1 */
                dm_set_virus(arg0, mapGrid, &virus_map_data[index], &virus_map_disp_order[index]);
                /* fallthrough */
            case 0x2:                               /* switch 1 */
                return 3;
            case 0x5:                               /* switch 1 */
                var_v0 = -1;
                if (dm_check_game_over(arg0, mapGrid) == false) {
                    if ((dm_h_erase_chack(mapGrid) != false) || (dm_w_erase_chack(mapGrid) != false)) {
                        var_v0_2 = 0x15;
                        if (arg0->unk_049 == 0) {
                            var_v0_2 = 6;
                        }
                        arg0->unk_00C = var_v0_2;
                        arg0->unk_02F = 0;
                    } else if (arg0->unk_049 == 0) {
                        arg0->unk_00C = 9;
                    } else {
                        arg0->unk_00C = 0x16;
                    }
                default:                            /* switch 1 */
                default:                            /* switch 2 */
block_141:
                    var_v0 = 0;
                }
                /* Duplicate return node #142. Try simplifying control flow for better match */
                return var_v0;
            case 0x6:                               /* switch 1 */
                temp_v0_3 = arg0->unk_02F + 1;
                arg0->unk_02F = temp_v0_3;
                var_v0 = 0;
                if ((u32) (temp_v0_3 & 0xFF) >= 0x12U) {
                    arg0->unk_00C = 7;
                    arg0->unk_02F = 0;
                    dm_h_erase_chack_set(arg0, mapGrid);
                    dm_w_erase_chack_set(arg0, mapGrid);
                    dm_h_ball_chack(mapGrid);
                    dm_w_ball_chack(mapGrid);
                    temp_s4_2 = arg0->unk_025;
                    temp_s4_3 = temp_s4_2 - func_8006121C(arg0, mapGrid, 1);
                    arg0->unk_170 += temp_s4_3;
                    dm_calc_erase_score_pos(arg0, mapGrid, &sp18);
                    temp_v1 = (s8) (u8) arg0->unk_00A / 2;
                    scoreNums_set(&temp_s3->unk_0B8[index], dm_make_score(arg0), arg0->unk_037, arg0->unk_006 + temp_v1 + (s32) sp18, arg0->unk_008 + temp_v1 + sp18.unk_4);
                    temp_v1_2 = arg0->unk_025;
                    if (temp_v1_2 == 0) {
                        temp_v1_3 = arg0->unk_03A;
                        if (arg0->unk_03B < temp_v1_3) {
                            arg0->unk_03B = (s8) temp_v1_3;
                        }
                        return 6;
                    }
                    if (temp_s3->unk_3BC >= (s32) temp_v1_2) {
                        if (temp_s3->unk_3C0 == 0) {
                            temp_s3->unk_3C0 = 1;
                            dm_snd_play_in_game(SND_INDEX_80);
                        }
                        if (temp_s3->unk_3B4 == 0) {
                            temp_s3->unk_3B4 = 1;
                            temp_s3->unk_3B8 = 1;
                        }
                    }
                    arg0->unk_039 += 1;
                    switch (evs_gamesel) {          /* switch 2 */
                        case ENUM_EVS_GAMESEL_1:    /* switch 2 */
                        case ENUM_EVS_GAMESEL_3:    /* switch 2 */
                        case ENUM_EVS_GAMESEL_5:    /* switch 2 */
                            temp_v1_4 = arg0->unk_03A;
                            temp_v1_5 = temp_v1_4 - 2;
                            if (temp_v1_4 < 2U) {
                                temp_v1_6 = arg0->unk_03C[3];
                                if (temp_v1_6 & 8) {
                                    arg0->unk_03C[3] = temp_v1_6 & 0xF7;
                                    if ((evs_gamemode == ENUM_EVS_GAMEMODE_1) & (temp_s4_3 != 0)) {
block_40:
                                        dm_snd_play_in_game(SND_INDEX_102);
                                        return 0;
                                    }
block_115:
                                    dm_snd_play_in_game(SND_INDEX_56);
                                    return 0;
                                }
block_116:
                                dm_snd_play_in_game(SND_INDEX_61);
                                return 0;
                            }
                            var_a1 = 2;
                            if (temp_v1_5 < 3) {
                                var_a1 = temp_v1_5;
                            }
                            dm_snd_play_in_game(_charSE_tbl[arg0->unk_090] + var_a1);
                            temp_v1_7 = arg0->unk_03C[3];
                            if (temp_v1_7 & 8) {
                                arg0->unk_03C[3] = temp_v1_7 & 0xF7;
                            }
                            goto block_141;
                        case ENUM_EVS_GAMESEL_2:    /* switch 2 */
                        case ENUM_EVS_GAMESEL_6:    /* switch 2 */
                            temp_v1_8 = arg0->unk_03C[3];
                            if (temp_v1_8 & 8) {
                                arg0->unk_03C[3] = temp_v1_8 & 0xF7;
                                if ((evs_gamemode == ENUM_EVS_GAMEMODE_1) & (temp_s4_3 != 0)) {
                                    goto block_40;
                                }
                                goto block_115;
                            }
                            goto block_116;
                    }
                } else {
                    /* Duplicate return node #142. Try simplifying control flow for better match */
                    return var_v0;
                }
                break;
            case 0x7:                               /* switch 1 */
                dm_capsel_erase_anime(arg0, mapGrid);
                return 0;
            case 0x8:                               /* switch 1 */
                go_down(arg0, mapGrid, 0xE);
                return 0;
            case 0x9:                               /* switch 1 */
                temp_v1_9 = arg0->unk_039;
                var_s3 = 1;
                if (temp_v1_9 >= 2U) {
                    temp_v1_10 = (arg0->unk_174 + temp_v1_9) - 1;
                    var_a0 = 0x63;
                    if (temp_v1_10 < 0x64) {
                        var_a0 = temp_v1_10;
                    }
                    arg0->unk_174 = var_a0;
                }
                dm_attack_se(arg0, index);
                dm_warning_h_line(arg0, mapGrid);
                switch (evs_gamesel) {              /* switch 3 */
                    case ENUM_EVS_GAMESEL_1:        /* switch 3 */
                    case ENUM_EVS_GAMESEL_3:        /* switch 3 */
                    case ENUM_EVS_GAMESEL_5:        /* switch 3 */
                        if (evs_gamemode != ENUM_EVS_GAMEMODE_3) {
                            if (dm_set_attack_2p(arg0) != 0) {
                                animeState_set(&arg0->unk_094, 1);
                            }
                            if (dm_broken_set(arg0, mapGrid) != false) {
                                animeState_set(&arg0->unk_094, 2);
                                dm_snd_play_in_game(_charSE_tbl[arg0->unk_090] + 3);
                                temp_v1_11 = (u8) arg0->unk_292;
                                arg0->unk_00C = 8;
                                var_s3 = 0;
                                if (temp_v1_11 & 1) {
                                    var_v0_3 = temp_v1_11 | 2;
                                } else {
block_60:
                                    var_v0_3 = (u8) arg0->unk_292 | 1;
                                }
block_61:
                                arg0->unk_292 = var_v0_3;
                            }
                        }
                        break;
                    case ENUM_EVS_GAMESEL_2:        /* switch 3 */
                    case ENUM_EVS_GAMESEL_6:        /* switch 3 */
                        if (dm_set_attack_4p(arg0) != 0) {
                            animeState_set(&arg0->unk_094, 1);
                        }
                        if (dm_broken_set(arg0, mapGrid) != false) {
                            animeState_set(&arg0->unk_094, 2);
                            temp_v1_12 = (u8) arg0->unk_292;
                            arg0->unk_00C = 8;
                            var_s3 = 0;
                            if (temp_v1_12 & 1) {
                                var_v0_3 = temp_v1_12 | 2;
                            } else {
                                goto block_60;
                            }
                            goto block_61;
                        }
                        break;
                }
                var_v0 = 0;
                if (var_s3 != 0) {
                    dm_set_capsel(arg0);
                    dm_capsel_speed_up(arg0);
                    temp_v1_13 = arg0->unk_03A;
                    if (arg0->unk_03B < temp_v1_13) {
                        arg0->unk_03B = (s8) temp_v1_13;
                    }
                    var_v1 = 3;
                    var_v0_4 = arg0 + 3;
                    arg0->unk_03A = 0;
                    arg0->unk_039 = 0;
                    arg0->unk_037 = 0;
                    arg0->unk_038 = 0;
                    do {
                        var_v0_4->unk_3C = 0;
                        var_v1 -= 1;
                        var_v0_4 -= 1;
                    } while (var_v1 >= 0);
                    temp_a0 = arg0->unk_04C;
                    arg0->unk_00C = 4;
                    if ((temp_a0 == 1) || ((var_v0 = 0, (((temp_a0 != 1) & (index == 0)) != 0)) && (var_v0 = 0, (aiDebugP1 >= 0)))) {
                        aifMakeFlagSet(arg0);
                        return 0;
                    }
                    /* Duplicate return node #142. Try simplifying control flow for better match */
                    return var_v0;
                }
                /* Duplicate return node #142. Try simplifying control flow for better match */
                return var_v0;
            case 0x1A:                              /* switch 1 */
                func_80062B18(index);
                return 0;
            case 0x1C:                              /* switch 1 */
                func_80062AFC(index);
                return 0;
            case 0x1E:                              /* switch 1 */
                func_80062B34(index);
                return 0;
            case 0x1B:                              /* switch 1 */
            case 0x1D:                              /* switch 1 */
            case 0x1F:                              /* switch 1 */
                if (gControllerPressedButtons[main_joy[index]] & 0xFF3F) {
                    func_80062DA4(&temp_s3->unk_9D0[index]);
                }
                timeAttackResult_update(&temp_s3->unk_9D0[index], 1);
                func_80060270(arg0, temp_s3->unk_9D0[index].unk_24);
                temp_s3->unk_9D0[index].unk_24 = 0;
                goto block_141;
            case 0xE:                               /* switch 1 */
            case 0x10:                              /* switch 1 */
            case 0x12:                              /* switch 1 */
                temp_v1_14 = arg0->unk_00C;
                switch (temp_v1_14) {               /* switch 4; irregular */
                    case 0xE:                       /* switch 4 */
                        var_v0_5 = func_80062A8C(index);
block_83:
                        var_v0 = 0;
                        if (var_v0_5 == 0) {
                        default:                    /* switch 4 */
                            temp_v0_4 = retryMenu_input(index);
                            if (temp_v0_4 != 1) {
                                if (temp_v0_4 >= 2) {
                                    switch (temp_v0_4) { /* switch 5; irregular */
                                        case 0x2:   /* switch 5 */
                                            func_800633C0();
block_137:
                                            temp_v1_15 = arg0->unk_004;
                                            if (temp_v1_15 < 0x3E7U) {
                                                arg0->unk_004 = temp_v1_15 + 1;
                                            }
                                            dm_snd_play_in_game(SND_INDEX_62);
                                            return 2;
                                        case 0x3:   /* switch 5 */
block_140:
                                            dm_snd_play_in_game(SND_INDEX_62);
                                            return -2;
                                        default:    /* switch 5 */
                                            return 0;
                                    }
                                } else {
                                    if (temp_v0_4 != 0) {
                                        return 0;
                                    }
                                    func_80063378();
                                    dm_snd_play_in_game(SND_INDEX_62);
                                    return 9;
                                }
                            } else {
                                func_800633C0();
                                dm_snd_play_in_game(SND_INDEX_62);
                                return 0x64;
                            }
                        } else {
                            /* Duplicate return node #142. Try simplifying control flow for better match */
                            return var_v0;
                        }
                        break;
                    case 0x10:                      /* switch 4 */
                        var_v0_5 = func_80062AA8(index);
                        goto block_83;
                    case 0x12:                      /* switch 4 */
                        var_v0_5 = func_80062AC4(index);
                        goto block_83;
                }
                break;
            case 0xD:                               /* switch 1 */
                func_80062A8C(index);
                return 0;
            case 0xF:                               /* switch 1 */
                func_80062AA8(index);
                return 0;
            case 0x11:                              /* switch 1 */
                func_80062AC4(index);
                return 0;
            case 0x13:                              /* switch 1 */
                var_v0 = 0;
                if (temp_s4 & 0x1000) {
                    var_v0 = 0;
                    if (temp_s3->unk_000 == 0) {
                        return 7;
                    }
                }
                /* Duplicate return node #142. Try simplifying control flow for better match */
                return var_v0;
            case 0x14:                              /* switch 1 */
                arg0->unk_049 = 1;
                clear_map_all(mapGrid);
                arg0->unk_025 = 0;
                arg0->unk_024 = 0;
                arg0->unk_02B = 0xC;
                arg0->unk_044 = 0;
                arg0->unk_031 = 0;
                arg0->unk_030 = 1;
                arg0->unk_032 = 1;
                arg0->unk_02F = 0;
                arg0->unk_02E = 0;
                arg0->unk_02D = (u8) GameSpeed[arg0->unk_02C];
                dm_set_capsel(arg0);
                var_v1_2 = 3;
                var_v0_6 = arg0 + 3;
                arg0->unk_035 = 0;
                arg0->unk_036 = 0;
                arg0->unk_037 = 0;
                arg0->unk_038 = 0;
                arg0->unk_03A = 0;
                arg0->unk_039 = 0;
                do {
                    var_v0_6->unk_3C = 0;
                    var_v1_2 -= 1;
                    var_v0_6 -= 1;
                } while (var_v1_2 >= 0);
                var_v1_3 = 0;
                var_a0_2 = arg0;
                do {
                    var_a0_2->unk_050[0][0] = 0;
                    var_a0_2->unk_050[0][1] = 0;
                    var_v1_3 += 1;
                    var_a0_2 += 4;
                } while (var_v1_3 < 0x10);
                var_v1_4 = &virus_map_disp_order[index];
                temp_a0_2 = var_v1_4 + 0x60;
                arg0->unk_00C = 1;
                arg0->unk_014 = 2;
                do {
                    var_v1_4->unk_00[0] &= 0x7F;
                    var_v1_4 += 1;
                } while ((u32) var_v1_4 < (u32) temp_a0_2);
                var_v1_5 = 0;
                if (arg0->unk_164 > 0) {
                    var_a1_2 = arg0;
                    var_a0_3 = arg0;
                    do {
                        temp_v0_5 = var_a1_2->unk_140;
                        var_a1_2 += 4;
                        var_a0_3->unk_0D4.unk_00[0].unk_8 = temp_v0_5;
                        var_v1_5 += 1;
                        var_a0_3 += 0xC;
                    } while (var_v1_5 < arg0->unk_164);
                    return 0;
                }
                goto block_141;
            case 0x15:                              /* switch 1 */
                temp_v0_6 = arg0->unk_02F + 1;
                arg0->unk_02F = temp_v0_6;
                var_v0 = 0;
                if ((u32) (temp_v0_6 & 0xFF) >= 0x12U) {
                    arg0->unk_02F = 0;
                    arg0->unk_00C = 7;
                    dm_h_erase_chack_set(arg0, mapGrid);
                    dm_w_erase_chack_set(arg0, mapGrid);
                    dm_h_ball_chack(mapGrid);
                    dm_w_ball_chack(mapGrid);
                    arg0->unk_039 += 1;
                    func_8006121C(arg0, mapGrid, 1);
                    temp_v1_16 = arg0->unk_03C[3];
                    if (temp_v1_16 & 8) {
                        arg0->unk_03C[3] = temp_v1_16 & 0xF7;
                        goto block_115;
                    }
                    goto block_116;
                }
                /* Duplicate return node #142. Try simplifying control flow for better match */
                return var_v0;
            case 0x16:                              /* switch 1 */
                dm_warning_h_line(arg0, mapGrid);
                var_s3_2 = 1;
                if (arg0->unk_04A != 0) {
                    dm_attack_se(arg0, index);
                    dm_set_attack_4p(arg0);
                    animeState_set(&arg0->unk_094, 1);
                    if (dm_broken_set(arg0, mapGrid) != false) {
                        arg0->unk_00C = 8;
                        var_s3_2 = 0;
                    }
                } else {
                    var_a1_3 = 0;
                    var_v1_6 = arg0;
                    do {
                        var_v1_6->unk_050[0][0] = 0;
                        var_v1_6->unk_050[0][1] = 0;
                        var_a1_3 += 1;
                        var_v1_6 += 4;
                    } while (var_a1_3 < 0x10);
                }
                if (var_s3_2 != 0) {
                    dm_set_capsel(arg0);
                    dm_capsel_speed_up(arg0);
                    var_v1_7 = 3;
                    var_v0_7 = arg0 + 3;
                    arg0->unk_03A = 0;
                    arg0->unk_039 = 0;
                    arg0->unk_037 = 0;
                    arg0->unk_038 = 0;
                    do {
                        var_v0_7->unk_3C = 0;
                        var_v1_7 -= 1;
                        var_v0_7 -= 1;
                    } while (var_v1_7 >= 0);
                    arg0->unk_00C = 4;
                }
                goto block_141;
            case 0x18:                              /* switch 1 */
                temp_v0_7 = retryMenu_input(index);
                if (temp_v0_7 != 1) {
                    if (temp_v0_7 >= 2) {
                        if (temp_v0_7 != 2) {
                            return 0;
                        }
                        goto block_140;
                    }
                    if (temp_v0_7 != 0) {
                        return 0;
                    }
                    if (temp_s3->unk_9C4 < 0) {
                        temp_s3->unk_9C4 = index;
                    }
                    dm_snd_play_in_game(SND_INDEX_62);
                    return 0;
                }
                goto block_137;
        }
    } else {
        return var_v0;
    }
}
#else
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", dm_game_main_cnt);
#endif
#endif

#if VERSION_CN
s32 dm_game_main_cnt(struct_game_state_data *gameStateDataRef, GameMapGrid *mapGrid, s32 index) {
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
        dm_black_up(gameStateDataRef, mapGrid);
    }

    if ((evs_gamemode == ENUM_EVS_GAMEMODE_3) && (evs_game_time >= 10800) && (gameStateDataRef->unk_020 == 1)) {
        return -1;
    }

    switch (gameStateDataRef->unk_00C) {
        case 0x1:
            dm_set_virus(gameStateDataRef, mapGrid, &virus_map_data[index], &virus_map_disp_order[index]);
            return 3;

        case 0x2:
            return 3;

        case 0x5:
            if (dm_check_game_over(gameStateDataRef, mapGrid)) {
                return -1;
            }

            if (dm_h_erase_chack(mapGrid) || dm_w_erase_chack(mapGrid)) {
                gameStateDataRef->unk_00C = (gameStateDataRef->unk_049 == 0) ? 6 : 0x15;
                gameStateDataRef->unk_02F = 0;
            } else if (gameStateDataRef->unk_049 == 0) {
                gameStateDataRef->unk_00C = 9;
            } else {
                gameStateDataRef->unk_00C = 0x16;
            }
            break;

        case 0x6:
            gameStateDataRef->unk_02F++;
            if (gameStateDataRef->unk_02F >= 0x12) {
                s32 temp_s4_2;

                gameStateDataRef->unk_00C = 7;
                gameStateDataRef->unk_02F = 0;
                dm_h_erase_chack_set(gameStateDataRef, mapGrid);
                dm_w_erase_chack_set(gameStateDataRef, mapGrid);
                dm_h_ball_chack(mapGrid);
                dm_w_ball_chack(mapGrid);

                temp_s4_2 = gameStateDataRef->unk_025;
                temp_s4_2 -= func_8006121C(gameStateDataRef, mapGrid, 1);
                gameStateDataRef->unk_170 += temp_s4_2;

                dm_calc_erase_score_pos(gameStateDataRef, mapGrid, &sp20);

                scoreNums_set(&temp_s1->unk_0B8[index], dm_make_score(gameStateDataRef), gameStateDataRef->unk_037,
                              gameStateDataRef->unk_006 + gameStateDataRef->unk_00A / 2 + (s32)sp20.unk_0,
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

                            if (temp_v0_3 >= 3) {
                                j = 2;
                            } else {
                                j = temp_v0_3;
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

        case 0x7:
            dm_capsel_erase_anime(gameStateDataRef, mapGrid);
            break;

        case 0x8:
            go_down(gameStateDataRef, mapGrid, 0xE);
            break;

        case 0x9:
            var_s6 = true;

            if (gameStateDataRef->unk_039 >= 2) {
                gameStateDataRef->unk_174 = MIN((gameStateDataRef->unk_174 + gameStateDataRef->unk_039) - 1, 0x63);
            }

            dm_attack_se(gameStateDataRef, index);
            dm_warning_h_line(gameStateDataRef, mapGrid);
            switch (evs_gamesel) {
                case ENUM_EVS_GAMESEL_1:
                case ENUM_EVS_GAMESEL_3:
                case ENUM_EVS_GAMESEL_5:
                    if (evs_gamemode != ENUM_EVS_GAMEMODE_3) {
                        if (dm_set_attack_2p(gameStateDataRef) != 0) {
                            animeState_set(&gameStateDataRef->unk_094, 1);
                        }

                        if (dm_broken_set(gameStateDataRef, mapGrid)) {
                            animeState_set(&gameStateDataRef->unk_094, 2);
                            var_s6 = false;
                            dm_snd_play_in_game(_charSE_tbl[gameStateDataRef->unk_090] + 3);
                            gameStateDataRef->unk_00C = 8;
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
                    if (dm_set_attack_4p(gameStateDataRef) != 0) {
                        animeState_set(&gameStateDataRef->unk_094, 1);
                    }

                    if (dm_broken_set(gameStateDataRef, mapGrid)) {
                        animeState_set(&gameStateDataRef->unk_094, 2);
                        var_s6 = false;
                        gameStateDataRef->unk_00C = 8;
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

                gameStateDataRef->unk_00C = 4;
                if ((gameStateDataRef->unk_04C == 1) || ((index == 0) && (aiDebugP1 >= 0))) {
                    aifMakeFlagSet(gameStateDataRef);
                }
            }
            break;

        case 0x1A:
            func_80062B18(index);
            break;

        case 0x1C:
            func_80062AFC(index);
            break;

        case 0x1E:
            func_80062B34(index);
            break;

        case 0x1B:
        case 0x1D:
        case 0x1F:
            if (gControllerPressedButtons[main_joy[index]] & ANY_BUTTON) {
                func_80062DA4(&temp_s1->unk_9D0[index]);
            }

            timeAttackResult_update(&temp_s1->unk_9D0[index], 1);
            func_80060270(gameStateDataRef, temp_s1->unk_9D0[index].unk_24);
            temp_s1->unk_9D0[index].unk_24 = 0;
            break;

        case 0xE:
        case 0x10:
        case 0x12:
            if (gameStateDataRef->unk_00C == 0xE) {
                if (func_80062A8C(index) != 0) {
                    break;
                }
            } else if (gameStateDataRef->unk_00C == 0x10) {
                if (func_80062AA8(index) != 0) {
                    break;
                }
            } else if (gameStateDataRef->unk_00C == 0x12) {
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

        case 0xD:
            func_80062A8C(index);
            break;

        case 0xF:
            func_80062AA8(index);
            break;

        case 0x11:
            func_80062AC4(index);
            break;

        case 0x13:
            if ((button & START_BUTTON) && (temp_s1->unk_000 == 0)) {
                return 7;
            }
            break;

        case 0x14:
            gameStateDataRef->unk_049 = 1;
            clear_map_all(mapGrid);
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

            gameStateDataRef->unk_00C = 1;
            gameStateDataRef->unk_014 = 2;

            for (i = 0; i < ARRAY_COUNTU(virus_map_disp_order[index].unk_00); i++) {
                virus_map_disp_order[index].unk_00[i] &= ~0x80;
            }

            for (i = 0; i < gameStateDataRef->unk_164; i++) {
                gameStateDataRef->unk_0D4.unk_00[i].unk_8 = gameStateDataRef->unk_140.unk_00[i];
            }
            break;

        case 0x15:
            gameStateDataRef->unk_02F++;
            if (gameStateDataRef->unk_02F >= 0x12) {
                gameStateDataRef->unk_02F = 0;
                gameStateDataRef->unk_00C = 7;
                dm_h_erase_chack_set(gameStateDataRef, mapGrid);
                dm_w_erase_chack_set(gameStateDataRef, mapGrid);
                dm_h_ball_chack(mapGrid);
                dm_w_ball_chack(mapGrid);

                gameStateDataRef->unk_039++;
                func_8006121C(gameStateDataRef, mapGrid, 1);

                if (gameStateDataRef->unk_03C[3] & 8) {
                    gameStateDataRef->unk_03C[3] &= ~8;
                    dm_snd_play_in_game(SND_INDEX_56);
                } else {
                    dm_snd_play_in_game(SND_INDEX_61);
                }
            }
            break;

        case 0x16:
            dm_warning_h_line(gameStateDataRef, mapGrid);

            var_s6 = true;
            if (gameStateDataRef->unk_04A != 0) {
                dm_attack_se(gameStateDataRef, index);
                dm_set_attack_4p(gameStateDataRef);
                animeState_set(&gameStateDataRef->unk_094, 1);
                if (dm_broken_set(gameStateDataRef, mapGrid)) {
                    gameStateDataRef->unk_00C = 8;
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
                gameStateDataRef->unk_00C = 4;
            }
            break;

        case 0x18:
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
    }

    return 0;
}
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", func_8006DDBC_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", func_8006DF08_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", func_8006DF3C_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", func_8006E0E8_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/dm_game_main", RO_800C8620_cn);
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/dm_game_main", RO_800C862C_cn);
#endif

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/dm_game_main", RO_800B2020);
#endif

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/dm_game_main", RO_800B202C);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", func_800666FC);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", func_80066808);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", dm_set_pause_and_volume);
#endif

#if VERSION_US
void func_800669A0(struct_game_state_data *arg0) {
    struct_game_state_data *sp10 = arg0;

    dm_set_pause_and_volume(&sp10, 1);
}
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", dm_calc_big_virus_pos);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", dm_calc_big_virus_pos);
#endif

#if VERSION_US
s32 dm_game_main_1p(void) {
    s32 temp_s3;
    struct_watchGame *watchGameP = watchGame;
    struct_game_state_data *temp = game_state_data;

    func_800669A0(temp);
    temp_s3 = dm_game_main_cnt_1P(temp, game_map_data, 0);
    dm_warning_h_line_se();
    if (watchGameP->unk_410 == 0) {
        s32 var_s2;

        for (var_s2 = 0; var_s2 < 3; var_s2++) {
            animeState_update(&watchGameP->animeStates[var_s2]);
            animeSmog_update(&watchGameP->animeSmogs[var_s2]);
        }
    }

    dm_calc_big_virus_pos(temp);
    dm_play_count_down_se();

    if (temp_s3 == 3) {
        if (watchGameP->unk_3AC < 0) {
            if (temp->unk_00C == 2) {
                watchGameP->unk_3C4 = 1;
                temp->unk_00C = temp_s3;
                animeState_set(&temp->unk_094, 1);
                func_800633FC();
            }
        }
    } else if (temp_s3 == 6) {
        s32 temp_s1;

        func_80062A24(temp->unk_04B);
        dm_seq_play_in_game(SEQ_INDEX_14);
        watchGameP->unk_3C4 = 0;
        temp->unk_020 = 5;

        if (evs_gamemode == ENUM_EVS_GAMEMODE_3) {
            s32 temp_v0;

            temp->unk_014 = 0x13;
            temp->unk_00C = 0x1A;

            temp_v0 = (0x2A30 - evs_game_time);
            func_80062DD8(&watchGameP->unk_9D0, temp->unk_16C, 1, temp_v0 & (~temp_v0 >> 0x1F), temp->unk_174,
                          temp->unk_170, temp->unk_000);
        } else {
            temp->unk_014 = 3;
            temp->unk_00C = 0xA;
        }

        switch (evs_gamemode) {
            case ENUM_EVS_GAMEMODE_3:
                func_80064130(0U, 3);
                break;

            case ENUM_EVS_GAMEMODE_0:
                func_80064130(0U, 5);
                break;

            default:
                break;
        }

        animeState_set(&temp->unk_094, 3);

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
        func_80062A08(temp->unk_04B);
        animeState_set(&temp->unk_094, 4);
        dm_seq_play_in_game(SEQ_INDEX_17);
        temp->unk_02B = 1;
        temp->unk_020 = 8;
        if (evs_gamemode == ENUM_EVS_GAMEMODE_3) {
            temp->unk_014 = 0x15;
            temp->unk_00C = 0x1C;

            func_80062DD8(&watchGameP->unk_9D0, temp->unk_16C, 0, 0, temp->unk_174, temp->unk_170, temp->unk_000);
            watchGameP->unk_3C4 = 0;
        } else {
            temp->unk_014 = 4;
            temp->unk_00C = 0xB;
            watchGameP->unk_3C4 = 0;
        }

        if ((temp->unk_026 < 0x16U) || ((watchGameP->unk_378 > 0))) {
            func_80064130(0U, 3);
        } else {
            func_80064130(0U, 2);
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

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", dm_game_main_1p);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", func_8006729C);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", func_800673FC);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", func_800674EC);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", func_800675C8);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", func_80067668);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", func_8006EB00_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", func_8006EC80_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", func_8006EDB0_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", func_8006EEC8_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", func_8006EF8C_cn);
#endif

#if VERSION_US
#if 0
// ? func_80062A40(s32);
// s32 func_80062BC4(void *);
// s32 func_8006729C(struct_game_state_data *);
// s32 func_800673FC(struct_game_state_data *, s32, s32);
// s32 func_800674EC(struct_game_state_data *, s32, s32);
// s32 func_800675C8(struct_game_state_data *, s32);
// s32 func_80067668(struct_game_state_data **);

s32 dm_game_main_2p(void) {
    struct_game_state_data *sp20;
    s32 sp3C;
    s32 sp44;
    s32 temp_a2;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 var_fp;
    s32 var_s1;
    s32 var_s1_10;
    s32 var_s1_11;
    s32 var_s1_12;
    s32 var_s1_13;
    s32 var_s1_2;
    s32 var_s1_3;
    s32 var_s1_4;
    s32 var_s1_5;
    s32 var_s1_6;
    s32 var_s1_7;
    s32 var_s1_8;
    s32 var_s1_9;
    s32 var_s2;
    s32 var_s3;
    s32 var_s4;
    s32 var_s5;
    s32 var_s6;
    s32 var_v0;
    GameMapGrid *var_a1;
    struct_watchGame *temp_s7;
    struct_watchGame *var_s2_2;
    struct_game_state_data **var_a1_2;
    struct_game_state_data **var_s0;
    struct_game_state_data **var_s0_10;
    struct_game_state_data **var_s0_11;
    struct_game_state_data **var_s0_2;
    struct_game_state_data **var_s0_3;
    struct_game_state_data **var_s0_4;
    struct_game_state_data **var_s0_5;
    struct_game_state_data **var_s0_6;
    struct_game_state_data **var_s0_7;
    struct_game_state_data **var_s0_8;
    struct_game_state_data **var_s0_9;
    struct_game_state_data **var_v1;
    struct_game_state_data **var_v1_2;
    struct_game_state_data *temp_a0;
    struct_game_state_data *temp_a0_2;
    struct_game_state_data *temp_a0_3;
    struct_game_state_data *temp_a0_4;
    struct_game_state_data *temp_a0_5;
    struct_game_state_data *temp_a0_6;
    struct_game_state_data *temp_a0_7;
    struct_game_state_data *temp_a0_8;
    struct_game_state_data *temp_a0_9;
    struct_game_state_data *temp_t0;
    struct_game_state_data *temp_v1_3;
    struct_game_state_data *var_a0;
    u8 temp_v0_3;

    temp_s7 = watchGame;
    var_s6 = 0;
    var_fp = 0;
    var_s1 = 0;
    var_a1 = game_map_data;
    var_v1 = &sp20;
    var_a0 = game_state_data;
    sp44 = 0;
    sp3C = 0;
    do {
        var_v1->unk_8 = var_a1;
        var_a1 += 0x550;
        var_v1->unk_0 = var_a0;
        var_v1 += 4;
        var_s1 += 1;
        var_a0 += 0x3C4;
    } while (var_s1 < 2);
    dm_set_pause_and_volume(&sp20, 2);
    var_s1_2 = 0;
    var_s0 = &sp20;
    do {
        temp_a2 = var_s1_2;
        var_s1_2 += 1;
        var_s0->unk_10 = dm_game_main_cnt(var_s0->unk_0, var_s0->unk_8, temp_a2);
        var_s0 += 4;
    } while (var_s1_2 < 2);
    dm_warning_h_line_se();
    dm_play_count_down_se();
    if (sp30 != 3) {
        var_s1_3 = 0;
        goto block_26;
    }
    if (sp34 != sp30) {
        var_s1_3 = 0;
block_26:
        var_s0_2 = &sp20;
        var_s2 = 0x9D0;
loop_27:
        temp_v1 = var_s0_2->unk_10;
        switch (temp_v1) {                          /* switch 1; irregular */
            case 0x6:                               /* switch 1 */
                if (evs_gamemode == ENUM_EVS_GAMEMODE_3) {
                    func_80062A24(var_s1_3);
                    var_s0_2->unk_0->unk_00C = 0x1A;
                    var_s0_2->unk_0->unk_014 = 0x13;
                    var_s0_2->unk_0->unk_020 = (u32) 0x13;
                    temp_t0 = var_s0_2->unk_0;
                    temp_v0 = 0x2A30 - evs_game_time;
                    func_80062DD8(temp_s7 + var_s2, temp_t0->unk_16C, 1, temp_v0 & ((s32) ~temp_v0 >> 0x1F), temp_t0->unk_174, var_s0_2->unk_0->unk_170, var_s0_2->unk_0->unk_000);
                    _dm_seq_play_in_game(1, SEQ_INDEX_16);
                    var_s0_2 += 4;
                } else {
                    sp3C += 1;
                    var_s0_2->unk_0->unk_020 = 5;
block_43:
                    var_s0_2 += 4;
                }
                var_s1_3 += 1;
                var_s2 += 0x2C;
                if (var_s1_3 >= 2) {
                    var_s5 = 0;
                    var_s4 = 0;
                    var_s1_4 = 0;
                    var_s3 = 0x9D0;
                    var_s2_2 = temp_s7;
                    var_s0_3 = &sp20;
                    do {
                        temp_v0_2 = (*var_s0_3)->unk_014;
                        switch (temp_v0_2) {
                            case 0x13:
                            case 0x15:
                            case 0x17:
                                var_s4 += var_s2_2->unk_888 == 0;
                                break;
                            case 0x14:
                            case 0x16:
                            case 0x18:
                                var_s5 += func_80062BC4(temp_s7 + var_s3) != 0;
                                break;
                        }
                        var_s3 += 0x2C;
                        var_s2_2 += 4;
                        var_s1_4 += 1;
                        var_s0_3 += 4;
                    } while (var_s1_4 < 2);
                    var_s1_5 = 0;
                    if (var_s4 == 2) {
                        var_a1_2 = &sp20;
                        do {
                            temp_a0 = *var_a1_2;
                            temp_v1_2 = temp_a0->unk_014;
                            if (temp_v1_2 != 0x15) {
                                if ((u32) temp_v1_2 < 0x16U) {
                                    if (temp_v1_2 == 0x13) {
                                        temp_a0->unk_020 = 0x14;
                                        (*var_a1_2)->unk_014 = (s32) 0x14U;
                                        (*var_a1_2)->unk_00C = 0x1B;
                                        goto block_66;
                                    }
                                    var_s1_5 += 1;
                                } else {
                                    if (temp_v1_2 == 0x17) {
                                        temp_a0->unk_020 = 0x18;
                                        (*var_a1_2)->unk_014 = (s32) 0x18U;
                                        (*var_a1_2)->unk_00C = 0x1F;
                                        goto block_66;
                                    }
                                    var_s1_5 += 1;
                                }
                            } else {
                                temp_a0->unk_020 = 0x16;
                                (*var_a1_2)->unk_014 = (s32) 0x16U;
                                (*var_a1_2)->unk_00C = 0x1D;
block_66:
                                var_s1_5 += 1;
                            }
                            var_a1_2 += 4;
                        } while (var_s1_5 < 2);
                    } else if (var_s5 == 2) {
                        var_fp = func_80067668(&sp20);
                    } else {
                        var_s1_6 = 0;
                        if (((sp3C == 2) | (sp44 == 2)) != 0) {
                            var_s0_4 = &sp20;
                            do {
                                temp_a0_2 = *var_s0_4;
                                var_s0_4 += 4;
                                var_s1_6 += 1;
                                var_s6 = func_800675C8(temp_a0_2, var_s6);
                            } while (var_s1_6 < 2);
                            dm_seq_play_in_game(SEQ_INDEX_17);
                        } else if (sp3C != 0) {
                            var_s0_5 = &sp20;
                            do {
                                temp_a0_3 = *var_s0_5;
                                var_s1_6 += 1;
                                if (temp_a0_3->unk_020 == 5) {
                                    var_fp = func_8006729C(temp_a0_3);
                                }
                                var_s0_5 += 4;
                            } while (var_s1_6 < 2);
                            var_s1_7 = 0;
                            var_s0_6 = &sp20;
                            do {
                                temp_a0_4 = *var_s0_6;
                                if (temp_a0_4->unk_020 == 5) {
                                    var_s6 = func_800673FC(temp_a0_4, var_fp, var_s6);
                                }
                                var_s1_7 += 1;
                                var_s0_6 += 4;
                            } while (var_s1_7 < 2);
                            var_s1_8 = 0;
                            var_s0_7 = &sp20;
                            do {
                                temp_a0_5 = *var_s0_7;
                                if (temp_a0_5->unk_020 != 5) {
                                    var_s6 = func_800674EC(temp_a0_5, var_fp, var_s6);
                                }
                                var_s1_8 += 1;
                                var_s0_7 += 4;
                            } while (var_s1_8 < 2);
                        } else if (sp44 != 0) {
                            var_s1_9 = 0;
                            var_s0_8 = &sp20;
                            do {
                                temp_a0_6 = *var_s0_8;
                                var_s1_9 += 1;
                                if (temp_a0_6->unk_020 != 8) {
                                    var_fp = func_8006729C(temp_a0_6);
                                }
                                var_s0_8 += 4;
                            } while (var_s1_9 < 2);
                            var_s1_10 = 0;
                            var_s0_9 = &sp20;
                            do {
                                temp_a0_7 = *var_s0_9;
                                if (temp_a0_7->unk_020 != 8) {
                                    var_s6 = func_800673FC(temp_a0_7, var_fp, var_s6);
                                }
                                var_s1_10 += 1;
                                var_s0_9 += 4;
                            } while (var_s1_10 < 2);
                            var_s1_11 = 0;
                            var_s0_10 = &sp20;
                            do {
                                temp_a0_8 = *var_s0_10;
                                if (temp_a0_8->unk_020 == 8) {
                                    var_s6 = func_800674EC(temp_a0_8, var_fp, var_s6);
                                }
                                var_s1_11 += 1;
                                var_s0_10 += 4;
                            } while (var_s1_11 < 2);
                        }
                    }
                    var_v0 = 0;
                    if (var_fp != 0) {
                        dm_save_all();
                        var_v0 = 0;
                    }
                    /* Duplicate return node #107. Try simplifying control flow for better match */
                    return var_v0;
                }
                goto loop_27;
            case 0x-1:                              /* switch 1 */
                if (evs_gamemode == ENUM_EVS_GAMEMODE_3) {
                    if ((u32) evs_game_time >= 0x2A30U) {
                        func_80062A08(var_s1_3);
                        var_s0_2->unk_0->unk_00C = 0x1C;
                        var_s0_2->unk_0->unk_014 = 0x15;
                        var_s0_2->unk_0->unk_020 = (u32) 0x15;
                    } else {
                        func_80062A40(var_s1_3);
                        var_s0_2->unk_0->unk_00C = 0x1E;
                        var_s0_2->unk_0->unk_014 = 0x17;
                        var_s0_2->unk_0->unk_020 = (u32) 0x17;
                    }
                    temp_v1_3 = var_s0_2->unk_0;
                    func_80062DD8(temp_s7 + var_s2, temp_v1_3->unk_16C, 0, 0, temp_v1_3->unk_174, var_s0_2->unk_0->unk_170, var_s0_2->unk_0->unk_000);
                    _dm_seq_play_in_game(1, SEQ_INDEX_18);
                } else {
                    sp44 += 1;
                    var_s0_2->unk_0->unk_020 = 8;
                }
                var_s0_2->unk_0->unk_028[3] = 1;
                var_s0_2->unk_0->unk_040[0] = 0x10;
                var_s0_2->unk_0->unk_048[0] = 1;
                goto block_43;
            default:                                /* switch 1 */
                var_v0 = -2;
                if (temp_v1 != 0x64) {
                    if (temp_v1 != -2) {
                        goto block_43;
                    }
                    /* Duplicate return node #107. Try simplifying control flow for better match */
                    return var_v0;
                }
                return -1;
            case 0x2:                               /* switch 1 */
                return 2;
            case 0x9:                               /* switch 1 */
                return 9;
        }
    } else {
        var_v0 = 0;
        if (temp_s7->unk_3AC < 0) {
            var_s1_12 = 0;
            var_v1_2 = &sp20;
loop_12:
            if ((*var_v1_2)->unk_00C == 2) {
                var_s1_12 += 1;
                var_v1_2 += 4;
                if (var_s1_12 < 2) {
                    goto loop_12;
                }
            }
            var_v0 = 0;
            if (var_s1_12 == 2) {
                temp_s7->unk_3C4 = 1;
                var_s1_13 = 0;
                var_s0_11 = &sp20;
                do {
                    (*var_s0_11)->unk_00C = 4;
                    temp_a0_9 = *var_s0_11;
                    temp_v0_3 = temp_a0_9->unk_04C;
                    if (temp_v0_3 != 1) {
                        if (!((temp_v0_3 != 1) & (var_s1_13 == 0))) {
                            var_s1_13 += 1;
                        } else if (aiDebugP1 < 0) {
                            var_s1_13 += 1;
                        } else {
                            goto block_23;
                        }
                    } else {
block_23:
                        var_s1_13 += 1;
                        aifMakeFlagSet(temp_a0_9);
                    }
                    var_s0_11 += 4;
                } while (var_s1_13 < 2);
                func_800633FC();
                return 0;
            }
            /* Duplicate return node #107. Try simplifying control flow for better match */
            return var_v0;
        }
        return var_v0;
    }
}
#else
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", dm_game_main_2p);
#endif
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", dm_game_main_2p);
#endif

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/dm_game_main", RO_800B2068);
#endif

#if VERSION_US
const u32 cap_pal_4164[][6] = {
    { 8, 10, 6, 9, 11, 7 },
    { 2, 4, 0, 3, 5, 1 },
};
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", dm_game_main_4p);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", dm_game_main_4p);
#endif

#if VERSION_US || VERSION_CN
bool dm_game_demo_1p(void) {
    struct_watchGame *watchGameP = watchGame;
    s32 temp_s4 = dm_game_main_cnt_1P(game_state_data, game_map_data, 0);
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
        game_state_data[0].unk_00C = temp_s4;
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

#if VERSION_US
bool dm_game_demo_2p(void) {
    struct_watchGame *watchGameP = watchGame;
    s32 sp10[2];
    s32 i;

    for (i = 0; i < ARRAY_COUNT(sp10); i++) {
        sp10[i] = dm_game_main_cnt(&game_state_data[i], &game_map_data[i], i);
    }

    dm_warning_h_line_se();
    if ((sp10[0] == 3) && (sp10[1] == sp10[0]) && (watchGameP->unk_3AC < 0)) {
        for (i = 0; i < ARRAY_COUNT(sp10); i++) {
            s32 temp;
            struct_game_state_data *temp2 = &game_state_data[i];

            game_state_data[i].unk_00C = 4;
            temp = temp2->unk_04C;

            if ((temp == 1) || (((temp != 1) && (i == 0)) && (aiDebugP1 >= 0))) {
                aifMakeFlagSet(temp2);
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

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", dm_game_demo_2p);
#endif

#if VERSION_CN
#if 0
//? dm_warning_h_line_se();
s32 dm_game_main_cnt(struct_game_state_data *, GameMapGrid *, s32);
extern s8 aiDebugP1;

enum bool dm_game_demo_4p(void) {
    s32 sp18;
    GameMapGrid *var_s2;
    s32 *var_s1_2;
    s32 *var_s2_2;
    s32 *var_s3;
    s32 *var_s3_2;
    s32 temp_v0;
    s32 var_s0;
    s32 var_s0_2;
    struct_game_state_data *var_s1;
    struct_watchGame *temp_s4;

    temp_s4 = watchGame;
    var_s0 = 0;
    var_s3 = &sp18;
    var_s2 = game_map_data;
    var_s1 = game_state_data;
    do {
        *var_s3 = dm_game_main_cnt(var_s1, var_s2, var_s0);
        var_s3 += 4;
        var_s2 += 0x550;
        var_s0 += 1;
        var_s1 += 0x3C4;
    } while (var_s0 < 4);
    dm_warning_h_line_se();
    if ((sp18 == 3) && (sp1C == sp18) && (sp20 == sp1C) && (sp24 == sp20) && (temp_s4->unk_3AC < 0)) {
        var_s0_2 = 0;
        var_s3_2 = &game_state_data[0].unk_00C + 0x40;
        var_s2_2 = &game_state_data[0].unk_00C - 0xC;
        var_s1_2 = &game_state_data[0].unk_00C;
        do {
            *var_s1_2 = 4;
            if (*var_s3_2 != 1) {
                if ((var_s0_2 == 0) && (aiDebugP1 >= 0)) {
                    goto block_12;
                }
            } else {
block_12:
                aifMakeFlagSet((struct_game_state_data *) var_s2_2);
            }
            var_s3_2 += 0x3C4;
            var_s2_2 += 0x3C4;
            var_s0_2 += 1;
            var_s1_2 += 0x3C4;
        } while (var_s0_2 < 4);
        temp_s4->unk_3C4 = 1;
    }
    temp_v0 = temp_s4->unk_41C;
    if (temp_v0 != 0) {
        temp_s4->unk_41C = temp_v0 - 1;
        if (gControllerPressedButtons[*main_joy] & 0xFF3F) {
            temp_s4->unk_41C = 0;
        }
        if (temp_s4->unk_41C == 0) {
            return true;
        }
        /* Duplicate return node #21. Try simplifying control flow for better match */
        return false;
    }
    return false;
}
#else
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", dm_game_demo_4p);
#endif
#endif

#if VERSION_US
bool dm_game_demo_4p(void) {
    struct_watchGame *watchGameP = watchGame;
    s32 sp10[4];
    s32 i;

    for (i = 0; i < ARRAY_COUNT(sp10); i++) {
        sp10[i] = dm_game_main_cnt(&game_state_data[i], &game_map_data[i], i);
    }

    dm_warning_h_line_se();
    if ((sp10[0] == 3) && (sp10[1] == sp10[0]) && (sp10[2] == sp10[1]) && (sp10[3] == sp10[2]) &&
        (watchGameP->unk_3AC < 0)) {
        for (i = 0; i < ARRAY_COUNT(sp10); i++) {
            struct_game_state_data *temp2 = &game_state_data[i];

            game_state_data[i].unk_00C = 4;

            if ((temp2->unk_04C == 1) || (((temp2->unk_04C != 1) && (i == 0)) && (aiDebugP1 >= 0))) {
                aifMakeFlagSet(temp2);
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

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", func_80068DC0);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", func_800709FC_cn);
#endif

#if VERSION_US
TiTexDataEntry_unk_0 **dm_game_get_capsel_pal(s32 arg0, s32 arg1) {
    return &watchGame->unk_444->unk_00[cap_pal_4164[arg0][arg1]].unk_0;
}
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", dm_game_get_capsel_pal);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", func_80068E24);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/dm_game_main", RO_800C8658_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/dm_game_main", RO_800C8660_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", func_80070A5C_cn);
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

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/dm_game_main", RO_800B20D0);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", func_80069188);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", starForce_draw);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", func_800695A8);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", func_8006967C);
#endif

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/dm_game_main", RO_800B20E0);
#endif

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/dm_game_main", RO_800B20EC);
#endif

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/dm_game_main", RO_800B20F8);
#endif

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/dm_game_main", RO_800B2104);
#endif

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/dm_game_main", RO_800B2108);
#endif

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/dm_game_main", RO_800B210C);
#endif

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/dm_game_main", RO_800B2114);
#endif

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/dm_game_main", RO_800B211C);
#endif

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/dm_game_main", RO_800B2120);
#endif

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/dm_game_main", RO_800B2134);
#endif

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/dm_game_main", RO_800B2138);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", func_80069990);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", func_80069ACC);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", draw_virus_number);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", draw_count_number);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", func_8006A098);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", func_8006A198);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", func_80070DE4_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", func_80070E64_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", func_8007125C_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", func_80071330_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", func_80071660_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", func_800717F0_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", func_80071904_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", func_80071B58_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", func_80071DD4_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", func_80071EF8_cn);
#endif

void push_any_key_draw(s32 arg0, s32 arg1) {
    struct_watchGame *watchGameP = watchGame;
    s32 alpha;
    s32 var_a1_2;
    TiTexData *temp_a3;
    TiTexDataEntry *temp1;
    TiTexDataEntry *temp2;

    alpha = sins((watchGameP->unk_424 << 10) & 0xFC00) * ((f32)0xFF / 0x8000) + 127;
    alpha = CLAMP(alpha, 0, 255);

    gSPDisplayList(gGfxHead++, alpha_texture_init_dl);
    gDPSetCombineLERP(gGfxHead++, TEXEL0, 0, PRIMITIVE, 0, TEXEL1, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0,
                      COMBINED);
    gDPSetPrimColor(gGfxHead++, 0, 0, 255, 255, 255, alpha);

    temp_a3 = watchGameP->unk_430;
    temp1 = &temp_a3->unk_00[0x17];
    temp2 = &temp_a3->unk_00[0x18];

    var_a1_2 = MIN(temp1->unk_4[0], temp2->unk_4[0]);

    StretchAlphaTexTile(&gGfxHead, var_a1_2, temp1->unk_4[1], temp1->unk_0->unk_4, temp1->unk_4[0], temp2->unk_0->unk_4,
                        temp2->unk_4[0], 0, 0, var_a1_2, temp1->unk_4[1], arg0, arg1, var_a1_2, temp1->unk_4[1]);
}

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", func_8006A480);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", func_80072214_cn);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", func_8006A6E8);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", func_80072490_cn);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", func_8006A938);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", func_8006A938);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", func_8006A978);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", func_8006AC60);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", func_8006AE04);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", func_8006AEFC);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", draw_story_board);
#endif

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/dm_game_main", RO_800B2160);
#endif

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/dm_game_main", RO_800B2168);
#endif

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/dm_game_main", RO_800B2170);
#endif

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/dm_game_main", RO_800B2178);
#endif

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/dm_game_main", RO_800B2180);
#endif

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/dm_game_main", RO_800B2184);
#endif

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/dm_game_main", RO_800B2188);
#endif

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/dm_game_main", RO_800B218C);
#endif

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/dm_game_main", RO_800B21D0);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", draw_vsmode_board);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", func_8006B8E0);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/dm_game_main", RO_800C86A0_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/dm_game_main", RO_800C86B0_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/dm_game_main", RO_800C86BC_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/dm_game_main", RO_800C86C8_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/dm_game_main", RO_800C86D4_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/dm_game_main", RO_800C86D8_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/dm_game_main", RO_800C86DC_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/dm_game_main", RO_800C86E4_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/dm_game_main", RO_800C86EC_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/dm_game_main", RO_800C8704_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", func_80072734_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", func_80072A34_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", func_80072BF0_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", func_80072D18_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", func_80072F04_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", func_800730F0_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", func_8007376C_cn);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", dm_calc_bottle_2p);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", dm_calc_bottle_2p);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", dm_draw_bottle_2p);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", dm_draw_bottle_2p);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", dm_draw_big_virus);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", dm_draw_big_virus);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/dm_game_main", RO_800C8728_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/dm_game_main", RO_800C8730_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/dm_game_main", RO_800C8738_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/dm_game_main", RO_800C8740_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/dm_game_main", RO_800C8748_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/dm_game_main", RO_800C8798_cn);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", dm_draw_KaSaMaRu);
#endif

#if VERSION_CN
#if 0
? RectAlphaTexTile(Gfx **, s32 *, s32, s32, s32, s32, void *, s32, s32, s32, s32, s32, s32, s32, f32, f32);
extern ? RO_800C8798_cn;

void dm_draw_KaSaMaRu(Gfx **gfxP, s32 *arg1, s32 *arg2, enum bool messageIsSpeaking, s32 arg4, s32 arg5, s32 arg6, u32 arg7) {
    f32 sp78;
    f32 sp7C;
    Gfx *sp88;
    s32 sp8C;
    Gfx *temp_a0;
    Gfx *temp_a0_3;
    Gfx *temp_a0_4;
    Gfx *temp_a0_5;
    Gfx *temp_a1;
    Gfx *temp_a1_2;
    Gfx *temp_t0;
    Gfx *temp_v1;
    Mtx *temp_s1_2;
    Mtx *temp_s1_3;
    TiTexData *temp_s2_2;
    s32 temp_s1;
    s32 var_v0;
    struct_watchGame *temp_s2;
    u16 *temp_a0_2;
    u16 *temp_a2;
    u16 var_s0;
    u16 var_s3;
    void *temp_a3;
    void *temp_s4;

    temp_s1 = *arg1;
    temp_s2 = watchGame;
    sp88 = *gfxP;
    sp8C = *arg2;
    guOrtho((Mtx *) temp_s1, 0.0f, 320.0f, 240.0f, 0.0f, 1.0f, 10.0f, 1.0f);
    temp_t0 = sp88;
    temp_t0->words.w1 = (u32) temp_s1;
    temp_s1_2 = temp_s1 + 0x40;
    sp88 = temp_t0 + 8;
    temp_t0->words.w0 = 0xDA380007;
    guTranslate(temp_s1_2, 0.0f, 0.0f, -5.0f);
    temp_a0 = sp88;
    sp88 = temp_a0 + 8;
    temp_a0->words.w0 = 0xDA380005;
    temp_a0->words.w1 = (u32) temp_s1_2;
    guRotateRPYF((f32 (*)[4]) &sp48[0], 0.0f, (f32) ((1 - arg6) * 0x5A), sinf((f32) (2.0 * ((f64) WrapF(0.0f, 1.0f, (f32) ((f64) temp_s2->unk_424 * 0.0078125)) * 3.141592653589793))) * 4.0f * (f32) arg6);
    var_v0 = WrapI(0, 6, (s32) ((u32) ((temp_s2->unk_424 & 0x7F) * 9) >> 4));
    temp_s1_3 = temp_s1_2 + 0x40;
    if (messageIsSpeaking == false) {
        var_v0 = 0;
    }
    temp_s2_2 = temp_s2->unk_448;
    temp_s4 = temp_s2_2 + ((*(&RO_800C8798_cn + (var_v0 * 4)) * 8) + 8);
    temp_a3 = temp_s4->unk_4;
    temp_a2 = temp_s2_2->unk_00[0].unk_4;
    if ((u16) temp_a3->unk_0 < (u16) temp_a2->unk_0) {
        var_s0 = temp_a3->unk_0;
    } else {
        var_s0 = temp_a2->unk_0;
    }
    temp_a0_2 = temp_s2_2->unk_00[0].unk_4;
    if ((u16) temp_a3->unk_2 >= (u16) temp_a0_2->unk_2) {
        var_s3 = temp_a0_2->unk_2;
    } else {
        var_s3 = temp_a3->unk_2;
    }
    temp_a0_3 = sp88;
    sp88 = temp_a0_3 + 8;
    temp_a0_3->words.w0 = 0xDE000000;
    temp_a0_3->words.w1 = (u32) alpha_texture_init_dl;
    temp_v1 = sp88;
    sp88 = temp_v1 + 8;
    temp_v1->words.w0 = 0xD940F9FA;
    temp_v1->words.w1 = 0;
    temp_a1 = sp88;
    sp88 = temp_a1 + 8;
    temp_a1->words.w0 = 0xFC11A7FF;
    temp_a1->words.w1 = -0x1C8U;
    temp_a0_4 = sp88;
    sp88 = temp_a0_4 + 8;
    temp_a0_4->words.w0 = 0xE3000C00;
    temp_a0_4->words.w1 = 0;
    temp_a1_2 = sp88;
    sp88 = temp_a1_2 + 8;
    temp_a1_2->words.w0 = 0xFA000000;
    temp_a1_2->words.w1 = arg7 | ~0xFF;
    if (arg6 <= 0) {
        sp78 = (f32) (arg4 + var_s0);
    } else {
        sp78 = (f32) arg4;
    }
    sp7C = (f32) arg5;
    guMtxF2L((f32 (*)[4]) &sp48[0], temp_s1_3);
    temp_a0_5 = sp88;
    sp88 = temp_a0_5 + 8;
    temp_a0_5->words.w0 = 0xDA380003;
    temp_a0_5->words.w1 = (u32) temp_s1_3;
    RectAlphaTexTile(&sp88, &sp8C, (s32) var_s0, (s32) var_s3, temp_s4->unk_0->unk_4, (s32) temp_s4->unk_4->unk_0, temp_s2_2->unk_00[0].unk_0->unk_4, (s32) temp_s2_2->unk_00[0].unk_4->unk_0, 0, 0, (s32) var_s0, (s32) var_s3, 0, 0, (f32) var_s0, (f32) var_s3);
    *arg2 = sp8C;
    *arg1 = (s32) (temp_s1_3 + 0x40);
    *gfxP = sp88;
}
#else
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", dm_draw_KaSaMaRu);
#endif
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", func_8006C1D0);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", func_80074138_cn);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", dm_game_graphic_p);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", dm_game_graphic_p);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", dm_game_graphic_1p);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", dm_game_graphic_effect);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", func_800747A8_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", func_80074998_cn);
#endif

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

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", dm_make_key);
#endif

#if VERSION_CN
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

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", key_control_main);
#endif

// bool?
extern UNK_TYPE4 visible_fall_point[];

#if VERSION_CN
void key_control_main(struct_game_state_data *gameStateDataRef, GameMapGrid *mapGrid, s32 arg2, s32 arg3) {
    struct_watchGame *temp_s5 = watchGame;
    s32 sp18[2];
    s32 sp20[2];

    func_8006AE60_cn();

    if (gameStateDataRef->unk_04C != 1) {
        if ((arg2 != 0) || (aiDebugP1 < 0)) {
            if (gControllerPressedButtons[arg3] & (U_CBUTTONS | L_CBUTTONS | R_CBUTTONS | D_CBUTTONS)) {
                visible_fall_point[arg2] = !visible_fall_point[arg2];
            }
        }
    }

    save_visible_fall_point_flag();

    if (gameStateDataRef->unk_00C == 3) {
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
    } else if (gameStateDataRef->unk_00C == 4) {
        if (gameStateDataRef->unk_020 == 1) {
            struct_game_state_data_unk_178 *temp_s0_2;

            if ((gameStateDataRef->unk_04C == 1) || ((arg2 == 0) && (aiDebugP1 >= 0))) {
                u16 temp_s1_2 = joygam[arg2];

                aifKeyOut(gameStateDataRef);
                if (temp_s5->unk_000 != 0) {
                    joygam[arg2] = temp_s1_2;
                }
            }

            temp_s0_2 = &gameStateDataRef->unk_178;
            if (joygam[arg2] & B_BUTTON) {
                rotate_capsel(mapGrid, temp_s0_2, -1);
            } else if (joygam[arg2] & A_BUTTON) {
                rotate_capsel(mapGrid, temp_s0_2, 1);
            }

            if (joygam[arg2] & L_JPAD) {
                translate_capsel(mapGrid, gameStateDataRef, -1, arg3);
            } else if (joygam[arg2] & R_JPAD) {
                translate_capsel(mapGrid, gameStateDataRef, 1, arg3);
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
        dm_capsel_down(gameStateDataRef, mapGrid);
        temp_s5->unk_37C[arg2] = 2;
    } else {
        if (temp_s5->unk_37C[arg2] != 0) {
            s8 temp_s3 = gameStateDataRef->unk_178.unk_8;

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

void func_8006D620(void) {
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

void dm_game_init_heap(void) {
    s32 i;

    heapTop = Heap_bufferp;

    BUFFER_CALLOC(&watchGame, heapTop, sizeof(struct_watchGame));

    for (i = 0; i < ARRAY_COUNTU(gameBackup); i++) {
        BUFFER_MALLOC(&gameBackup[i], heapTop, sizeof(struct_gameBackup));
    }

    BUFFER_MALLOC(&gameGeom, heapTop, sizeof(struct_gameGeom));
}

const u16 map_x_table_5383[][4] = {
    { 0x76, 0x76, 0x76, 0x76 },
    { 0x1C, 0xD4, 0x1C, 0xD4 },
    { 0x14, 0x5C, 0xA4, 0xEC },
};
const u8 map_y_table_5384[] = { 0x2E, 0x2E };
const u8 size_table_5385[] = { 0xA, 8 };

void dm_game_init(bool arg0) {
    struct_watchGame *watchGameP = watchGame;
    s32 i;
    s32 j;
    s32 var_s4;
    struct_game_state_data *temp_s0_3;
    struct_game_state_data *var_s0_2;
    struct_virus_map_data *var_s1_5;
    struct_virus_map_disp_order *var_s3;

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
    watchGameP->unk_A28.unk_74 = 0;
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
        temp_s0_3->unk_00C = 1;
        temp_s0_3->unk_014 = 2;
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

        init_map_all(&game_map_data[i]);
    }

    var_s3 = virus_map_disp_order;
    var_s1_5 = virus_map_data;
    var_s0_2 = game_state_data;
    for (i = 0; i < evs_playcnt; i++) {
        dm_virus_init(evs_gamemode, &var_s0_2[i], &var_s1_5[i], &var_s3[i]);
        if (evs_gamemode == ENUM_EVS_GAMEMODE_1) {
            make_flash_virus_pos(&var_s0_2[i], &var_s1_5[i], &var_s3[i]);
        } else {
            game_state_data[i].unk_164 = 0;
        }
    }

    for (i = 0; i < evs_playcnt - 1; i++) {
        for (j = i + 1; j < evs_playcnt; j++) {
            if (game_state_data[i].unk_026 == game_state_data[j].unk_026) {
                dm_virus_map_copy(&virus_map_data[i], &virus_map_data[j], &virus_map_disp_order[i],
                                  &virus_map_disp_order[j]);
                if (evs_gamemode == ENUM_EVS_GAMEMODE_1) {
                    game_state_data[j].unk_164 = game_state_data[i].unk_164;
                    bcopy(&game_state_data[i].unk_0D4, &game_state_data[j].unk_0D4, sizeof(struct_80123700_unk_0D4));
                    bcopy(&game_state_data[i].unk_140, &game_state_data[j].unk_140, sizeof(struct_80123700_unk_140));
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

/**
 * Original name: dm_game_init_static
 */
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

    // TODO: SCREEN_WIDTH and SCREEN_HEIGHT ?
    watchGameP->unk_A28.unk_28 = (s32)(0x140 - (watchGameP->unk_A28.unk_3C * 0x14)) >> 1;
    watchGameP->unk_A28.unk_2C = (s32)(0xF0 - (watchGameP->unk_A28.unk_48 * 2)) >> 1;
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

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/dm_game_main", RO_800B2314);
#endif

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/dm_game_main", RO_800B2330);
#endif

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/dm_game_main", RO_800B233C);
#endif

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/dm_game_main", RO_800B2340);
#endif

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/dm_game_main", RO_800B2344);
#endif

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/dm_game_main", RO_800B2348);
#endif

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/dm_game_main", RO_800B2354);
#endif

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/dm_game_main", RO_800B2358);
#endif

ASM_TEXT;

void dm_game_init_snap_bg(void) {
    struct_watchGame *watchGameP = watchGame;

    BUFFER_MALLOC64(&watchGameP->unk_87C, heapTop, sizeof(struct_watchGame_unk_87C));
    watchGameP->unk_880 = 0;

    switch (evs_gamesel) {
        case ENUM_EVS_GAMESEL_0:
        case ENUM_EVS_GAMESEL_4:
            break;

        default:
            heapTop = func_80077170((BgRomDataIndex)story_proc_no, heapTop);
            break;
    }
}

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/dm_game_main", RO_800C88D4_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/dm_game_main", RO_800C88F0_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/dm_game_main", RO_800C88FC_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/dm_game_main", RO_800C8900_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/dm_game_main", RO_800C8904_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/dm_game_main", RO_800C8908_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/dm_game_main", RO_800C8914_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/dm_game_main", RO_800C8918_cn);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", dm_game_draw_snap_bg);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", dm_game_draw_snap_bg);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", func_8006F628);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", func_80077EC4_cn);
#endif

enum_main_no dm_game_main(struct_800EB670 *arg0) {
    OSMesgQueue sp10;
    OSMesg sp28[8];
    struct_800FAF98_unk_64 sp48;
    enum_main_no ret;
    bool var_s2 = true;
    s32 var_s4;
    struct_watchGame *watchGameP;

    func_8006D0E8();

    osCreateMesgQueue(&sp10, sp28, ARRAY_COUNT(sp28));
    func_8002A184(arg0, &sp48, &sp10);
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

        osRecvMesg(&sp10, (OSMesg *)&sp50, OS_MESG_BLOCK);

#if VERSION_CN
        if (D_80092F10_cn) {
            joyProcCore();
            graphic_no = GRAPHIC_NO_0;
            dm_audio_update();

            continue;
        }
#endif

        if (sp10.validCount != 0) {
            D_80088104[1] = 1;
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

#if VERSION_CN
            if (gControllerPressedButtons[main_joy[0]] & Z_TRIG) {
                D_80088104[1] = 0;
                D_800BEF08_cn ^= 1;
            }
            func_8002BC30_cn(1);
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

#if VERSION_CN
            func_8002BD04_cn();
#endif

            if (watchGameP->unk_420 != 0) {
                dm_seq_set_volume(0x40);
            }

            dm_audio_update();
            dm_game_graphic_onDoneSawp();

#if VERSION_US
            graphic_no = GRAPHIC_NO_4;
#endif
#if VERSION_CN
            if (D_80092F10_cn) {
                graphic_no = GRAPHIC_NO_0;
            } else {
                graphic_no = GRAPHIC_NO_4;
            }
#endif
        }
    }

    D_800A6FC4 = 0;
    watchGameP->unk_878 = 0xF;

    while (watchGameP->unk_878 != 0) {
        osRecvMesg(&sp10, NULL, OS_MESG_BLOCK);
        dm_audio_update();
    }

    graphic_no = GRAPHIC_NO_0;
    memset(gFramebuffers[gCurrentFramebufferIndex ^ 1], 0xFF, sizeof(gFramebuffers[gCurrentFramebufferIndex ^ 1]));
    dm_audio_stop();

    while (!dm_audio_is_stopped() || (pendingGFX != 0)) {
        osRecvMesg(&sp10, NULL, OS_MESG_BLOCK);
        dm_audio_update();
    }

    ret = dm_game_main3(var_s4);
    while (func_80040BA4() != 0) {
        osRecvMesg(&sp10, NULL, OS_MESG_BLOCK);
    }

    func_80040AE4();
    func_8002A1DC(arg0, &sp48);

    return ret;
}

#if VERSION_US
#if 0
// enum bool dm_game_main_2p();
// enum bool dm_game_main_4p();

s32 dm_game_main2(void) {
    s32 temp_s0_4;
    s32 var_s4_2;
    s32 var_s4_3;
    s32 var_v0;
    s32 var_s0;
    s32 var_s1;
    s32 var_v0_3;
    s32 var_v0_7;
    struct_watchGame *temp_s3;
    s32 temp_s0_2;

    // var_s4_2 = saved_reg_s4;
    temp_s3 = watchGame;
    var_s1 = 0;
    if (temp_s3->unk_3B8 != 0) {
        dm_seq_play_in_game((evs_seqnumb * 2) + 1);
        temp_s3->unk_3B8 = 0;
    }
    dm_effect_make();
    RecWritingMsg_calc(&temp_s3->recMessage);

    switch (evs_gamesel) {
        case ENUM_EVS_GAMESEL_0:
            if (temp_s3->unk_9AC > 0) {
                if (gControllerHoldButtons[*main_joy] & 0xC000) {
                    temp_s3->messageWnd.unk_5C = 0.125f;
                } else {
                    temp_s3->messageWnd.unk_5C = 0.016666668f;
                }
                msgWnd_update(&temp_s3->messageWnd);

                switch (temp_s3->unk_9AC) { /* switch 1; irregular */
                    case 1:     /* switch 1 */
                        if (!(gControllerPressedButtons[*main_joy] & 0x1000)) {
                            if (msgWnd_isScroll(&temp_s3->messageWnd) == false) {
                                temp_s3->unk_9AC = 2;
                            }
                        } else {
                            temp_s3->unk_9AC = 0;
                        }
                        break;

                    case 0x2: /* switch 1 */
                        if (temp_s3->unk_9B0 < 0x168) {
                            temp_s3->unk_9B0++;
                        } else if (gControllerPressedButtons[*main_joy] & 0xFF3F) {
                            temp_s3->unk_9AC = 0;
                        }
                        break;
                }

                if (temp_s3->unk_9AC == 0) {
                    dm_seq_play_in_game(evs_seqnumb * 2);
                }
                var_s4_2 = 0;
                if (temp_s3->unk_9AC > 0) {
                    // goto block_105;
                    return var_s4_2;
                }
            }
            var_s4_2 = dm_game_main_1p();
            switch (var_s4_2) {
                case 1:
                    temp_s0_2 = game_state_data[0].unk_026;

                    if ((((temp_s0_2 == 0x15) | (temp_s0_2 == 0x18)) != 0) ||
                        ((temp_s0_2 >= 0x1E) &&
                         (temp_s0_2 == ((temp_s0_2 / 5) * 5)))) {
                        temp_s3->unk_9AC = var_s4_2;
                        if (temp_s0_2 >= 0x1E) {
                            if ((s32)temp_s0_2 >= 0x28) {
                                temp_s3->unk_9B4 = 2;
                            } else {
                                temp_s3->unk_9B4 = var_s4_2;
                            }
                        } else {
                            temp_s3->unk_9B4 = false;
                        }
                        if ((s32)temp_s0_2 < 0x1E) {
                            temp_s3->unk_9B8 = (temp_s0_2 - 0x15) / 3;
                        } else {
                            temp_s3->unk_9B8 = (temp_s0_2 / 5) & 1;
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

                default:
                    break;
            }

            var_s4_2 = var_s4_2;
            switch (var_s4_2) {
                case 1:
                case 2:
                var_s4_2 = 0;
                    dm_game_init(true);
                    animeState_set(&game_state_data[0].unk_094, 2);
                    var_s0 = 0;
                    do {
                        animeState_set(&temp_s3->animeStates[var_s0], 0);
                        animeSmog_stop(&temp_s3->animeSmogs[var_s0]);
                        var_s0 += 1;
                    } while (var_s0 < 3);
                    temp_s0_4 = temp_s3->unk_9AC;
                    temp_s3->unk_9AC = false;
                    backup_game_state(0);
                    temp_s3->unk_9AC = temp_s0_4;
                    if (temp_s3->unk_9AC > 0) {
                        dm_seq_play_in_game(SEQ_INDEX_23);
                        //return false;
                    }
                    break;
            }
            break;

        case ENUM_EVS_GAMESEL_1:
        case ENUM_EVS_GAMESEL_3:
            var_s0 = 0;
            var_s4_2 = dm_game_main_2p();
            do {
                if (evs_story_flg != 0) {
                    if (temp_s3->unk_89C[var_s0] > 0) {
                        var_s1 = 1;
                    }
                } else if (temp_s3->unk_89C[var_s0] == evs_vs_count) {
                    var_s1 = 1;
                }
                var_s0 += 1;
            } while (var_s0 < 2);

            switch (var_s4_2) {
                case -1:
                    //var_v0 = var_s4_2;
                    if (var_s1 == 0) {
                        if (evs_gamemode == ENUM_EVS_GAMEMODE_3) {
                            var_s0 = 0;
                            while (var_s0 < 2) {
                                (game_state_data + var_s0)->unk_000 = 0;
                                var_s0++;
                            }
                        }
                        dm_game_init(true);
                        var_s0 = 0;
                        do {
                            animeState_set(&game_state_data[var_s0].unk_094, 0);
                            var_s0 += 1;
                        } while (var_s0 < 2);
                        backup_game_state(0);
                        var_s4_2 = 0;
                        //return false;
                    }
                    /* Duplicate return node #106. Try simplifying control flow for better match */
                    //return var_v0;
                    break;

                case 2:
                    var_s0 = 0;
                    while (var_s0 < 2) {
                        (game_state_data + var_s0)->unk_000 = 0;
                        var_s0++;
                    }
                    dm_game_init(false);
                    var_s0 = 0;
                    do {
                        animeState_set(&game_state_data[var_s0].unk_094, 0);
                        var_s0 += 1;
                    } while (var_s0 < 2);
                    backup_game_state(0);
                    var_s4_2 = 0;
                    //return false;
                    break;

                case 9:
                    dm_game_init(true);
                    var_s4_2 = 0;
                    //return false;
                    break;

                default:
                    //return var_s4_2;
                    //var_s4_2 = 0;
                    break;
            }
            break;

        case ENUM_EVS_GAMESEL_2:
            var_s0 = 0;
            var_s4_2 = dm_game_main_4p();
            do {
                if (evs_story_flg != 0) {
                    if (temp_s3->unk_89C[var_s0] > 0) {
                        var_s1 = 1;
                    }
                } else if (temp_s3->unk_89C[var_s0] == evs_vs_count) {
                    var_s1 = 1;
                }
                var_s0 += 1;
            } while (var_s0 < 4);

            switch (var_s4_2) {
                case -1:
                    var_v0 = var_s4_2;
                    if (var_s1 == 0) {
                        dm_game_init(true);
                        var_s0 = 0;
                        do {
                            animeState_set(&game_state_data[var_s0].unk_094, 0);
                            var_s0 += 1;
                        } while (var_s0 < 4);
                        backup_game_state(0);
                        //return false;
                        var_s4_2 = 0;
                    }
                    /* Duplicate return node #106. Try simplifying control flow for better match */
                    //return var_v0;
                    break;

                case 2:
                    var_s0 = 0;
                    while (var_s0 < 2) {
                        (game_state_data + var_s0)->unk_000 = 0;
                        var_s0++;
                    }
                    dm_game_init(false);
                    var_s0 = 0;
                    do {
                        animeState_set(&game_state_data[var_s0].unk_094, 0);
                        var_s0 += 1;
                    } while (var_s0 < 4);
                    backup_game_state(0);
                    var_s4_2 = false;
                    break;

                case 9:
                    backup_game_state(0);
                    var_s4_2 = 0;
                    break;
                    //return false;

                default:
                    //return var_s4_2;
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
            break;
    }

block_105:
    return var_s4_2;
}
#else
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", dm_game_main2);
#endif
#endif

#if VERSION_CN
#ifdef NON_MATCHING
// regalloc
s32 dm_game_main2(void) {
    s32 var_s4_2;
    s32 var_s0;
    s32 var_s1;
    struct_watchGame *temp_s3;

    // var_s4_2 = saved_reg_s4;
    temp_s3 = watchGame;
    var_s1 = 0;
    if (temp_s3->unk_3B8 != 0) {
        dm_seq_play_in_game((evs_seqnumb * 2) + 1);
        temp_s3->unk_3B8 = 0;
    }

    dm_effect_make();
    RecWritingMsg_calc(&temp_s3->recMessage);

    switch (evs_gamesel) {
        case ENUM_EVS_GAMESEL_0:
            if (temp_s3->unk_9AC > 0) {
                if (gControllerHoldButtons[main_joy[0]] & 0xC000) {
                    temp_s3->messageWnd.unk_5C = 0.125f;
                } else {
                    temp_s3->messageWnd.unk_5C = 0.016666668f;
                }
                msgWnd_update(&temp_s3->messageWnd);

                switch (temp_s3->unk_9AC) {
                    case 0x1:
                        if (!(gControllerPressedButtons[main_joy[0]] & 0x1000)) {
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
                        } else if (gControllerPressedButtons[main_joy[0]] & 0xFF3F) {
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
                var_s1 = var_s4_2 < 3;

                switch (var_s4_2) {
                        // case 0: // ?
                        //    break;

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
                        var_s1 = 1;
                        break;

                    case 9:
                        var_s4_2 = 0;
                        dm_game_init(true);
                        var_s1 = 1;
                        break;

                    default:
                        break;
                }

                // ?
                if ((var_s1 != 0) && (var_s4_2 > 0)) {
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
                    dm_game_init(true);
                    var_s4_2 = 0;
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
                    dm_game_init(true);
                    var_s4_2 = 0;
                    break;

                default:
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
#else
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", dm_game_main2);
#endif
#endif

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

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/dm_game_main", RO_800B23C4);
#endif

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/dm_game_main", RO_800B23CC);
#endif

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/dm_game_main", RO_800B23D4);
#endif

extern const s32 RO_800B1D08[];
extern const s32 RO_800B1D18[][2];
extern const s32 RO_800B1D28;
extern const s32 RO_800B1D2C[][3];
extern const s32 RO_800B1D84[][2];
extern const s32 _posP4TeamStarX[][2][3];
extern const s32 _posP4CharStarX[][4][3];

extern const s32 RO_800B1E7C[][2];
extern const s32 RO_800B1E8C[][2];
extern const s32 RO_800B1E9C[][2];
extern const s32 RO_800B23C4[];
extern const s32 RO_800B23CC[];
extern const s32 RO_800B23D4[];

#if VERSION_US
#if 0

#define HELP                      \
    do {                          \
        *(vu32 *)0x1234 = 0x4567; \
    } while (0)

void dm_game_graphic2(void) {
    s32 sp6C;
    s32 sp68;
    struct_watchGame *sp64;
    TiTexDataEntry *sp60;
    s32 sp54;
    s32 sp4C;
    Vtx *sp44;
    Mtx *sp40;
    Gfx *temp_a0_2;
    Gfx *temp_v0_2;
    Gfx *temp_v1_10;
    Gfx *temp_v1_13;
    Gfx *temp_v1_15;
    Gfx *temp_v1_3;
    Gfx *temp_v1_4;
    Gfx *temp_v1_7;
    TiTexData *temp_a0_5;
    TiTexData *temp_a1;
    TiTexData *temp_v1_12;
    TiTexDataEntry *temp_s7;
    TiTexDataEntry *temp_s7_2;
    TiTexDataEntry *var_s7;
    TiTexDataEntry *var_t1;
    s32 temp_a3;
    s32 temp_s0;
    s32 temp_s1;
    s32 temp_s1_3;
    s32 temp_s2;
    u16 temp_s4;
    s32 temp_s5;
    s32 temp_v1_16;
    s32 temp_v1_8;
    s32 temp_v1_9;
    s32 var_a0;
    s32 var_a1;
    s32 var_a3;
    s32 var_s0_5;
    s32 var_s1;
    s32 var_s1_2;
    s32 var_s2_2;
    s32 var_s2_3;
    s32 var_s2_5;
    s32 var_s2_7;
    s32 var_t3;
    s32 var_t4;
    s32 var_t5;
    s32 var_v0;
    s32 var_v1;
    struct_watchGame *temp_fp;
    u16 temp_a1_7;
    u16 temp_a2;
    u16 *temp_a1_2;
    u16 *temp_a1_6;
    u16 *temp_t0;
    u16 *temp_v0_5;
    u32 temp_a0;
    u32 temp_s6_2;
    s32 temp_s3;

    temp_fp = watchGame;

    gGfxHead = gGfxGlist[gfx_gtask_no];

    temp_s3 = game_state_data->unk_00C == 0x20 || game_state_data->unk_00C == 0x21;
    sp40 = dm_get_mtx_buf();
    sp44 = dm_get_vtx_buf();

    gSPSegment(gGfxHead++, 0x00, 0x00000000);

    F3RCPinitRtn();
    gfxSetScissor(&gGfxHead, 2, 0, 0, 0x140, 0xF0);
    F3ClearFZRtn(temp_s3);
    if (temp_s3 == 0) {
        if (temp_fp->unk_394 < 0x14) {
            dm_game_draw_snap_bg(&gGfxHead, &sp40, &sp44, 1);
        } else if (temp_fp->unk_9AC == 0) {
            func_8006F628(&gGfxHead);
        }
    }

    switch (evs_gamesel) {
        case ENUM_EVS_GAMESEL_1:
        case ENUM_EVS_GAMESEL_3:
        case ENUM_EVS_GAMESEL_5:
            temp_s5 = temp_fp->unk_394;
            temp_s0 = temp_s5 < 0x14;
            temp_s2 = temp_fp->unk_880 == 0;
            if (temp_s3 == 0) {
                if (temp_fp->unk_880 != 0) {
                    temp_fp->unk_394 = 0x14;
                }
                dm_calc_bottle_2p();
                if (temp_s0 != 0) {
                    dm_draw_bottle_2p(&gGfxHead);
                }
                temp_s1 = (0x14 - temp_fp->unk_394) * 6;
                if (evs_story_flg != 0) {
                    draw_story_board(&gGfxHead, 0, -temp_s1, temp_s0, temp_s2);
                } else {
                    draw_vsmode_board(&gGfxHead, 0, -temp_s1, temp_s0, temp_s2);
                }

                temp_fp->unk_394 = temp_s5;
            }
            break;
    }

    switch (evs_gamesel) {
        case ENUM_EVS_GAMESEL_1:
        case ENUM_EVS_GAMESEL_2:
        case ENUM_EVS_GAMESEL_3:
        case ENUM_EVS_GAMESEL_5:
        case ENUM_EVS_GAMESEL_6:
            if ((temp_s3 == 0) && (temp_fp->unk_880 == 0)) {
                for (var_s1 = 0; var_s1 < evs_playcnt; var_s1++) {
                    dm_virus_anime(&game_state_data[var_s1], &game_map_data[var_s1]);
                    dm_game_graphic_p(&game_state_data[var_s1], var_s1, &game_map_data[var_s1]);
                }
            }
            break;
    }

    switch (evs_gamesel) {
        case ENUM_EVS_GAMESEL_0:
        case ENUM_EVS_GAMESEL_4:
            if (temp_s3 == 0) {
                if (temp_fp->unk_880 != 0) {
                    temp_fp->unk_880 = 0;
                    return;
                }

                disp_logo_setup(&gGfxHead);
                temp_a3 = temp_fp->unk_9AC;
                if (temp_a3 > 0) {
                    draw_coffee_break(&gGfxHead, temp_fp->unk_9B4, temp_fp->unk_9B8, temp_a3 >= 2);
                    msgWnd_draw(&temp_fp->messageWnd, &gGfxHead);
                    if (temp_fp->unk_9B0 == 0x168) {
                        push_any_key_draw(0x80, 0xC0);
                    }
                } else {
                    animeState_initDL(&game_state_data->unk_094, &gGfxHead);
                    animeState_draw(&game_state_data->unk_094, &gGfxHead, 250.0f, 84.0f, 1.0f, 1.0f);

                    dm_virus_anime(&game_state_data[0], game_map_data);
                    dm_game_graphic_1p(&game_state_data[0], 0, game_map_data);
                    func_8006A978(&gGfxHead, temp_fp->unk_378);

                    gSPDisplayList(gGfxHead++, alpha_texture_init_dl);

                    draw_count_number(&gGfxHead, 0, 7, evs_high_score, 0x1D, 0x27);
                    draw_count_number(&gGfxHead, 0, 7, game_state_data->unk_000, 0x1D, 0x43);

                    gSPDisplayList(gGfxHead++, alpha_texture_init_dl);

                    if (evs_gamemode == ENUM_EVS_GAMEMODE_0) {
                        draw_virus_number(&gGfxHead, game_state_data->unk_026, 0xFE, 0x7E, 1.0f, 1.0f);
                    }

                    switch (evs_gamemode) {       /* switch 2; irregular */
                        case ENUM_EVS_GAMEMODE_2: /* switch 2 */
                        case ENUM_EVS_GAMEMODE_0: /* switch 2 */
                            func_8006A098(&gGfxHead, evs_game_time, RO_800B1D28, RO_800B1D2C[0][0]);
                            break;
                        case ENUM_EVS_GAMEMODE_3: /* switch 2 */
                            temp_s1_3 = 0x2A30 - evs_game_time;
                            func_8006A198(&gGfxHead, MAX(temp_s1_3, 0) + 5, RO_800B1D28,
                                          RO_800B1D2C[0][0]);
                            break;
                    }

                    switch (evs_gamemode) {
                        case ENUM_EVS_GAMEMODE_2:
                            var_s1_2 = game_state_data->unk_170;
                            break;

                        default:
                            var_s1_2 = game_state_data->unk_025;
                            break;
                    }

                    draw_virus_number(&gGfxHead, var_s1_2, 0xFE, 0xD2, 1.0f, 1.0f);
                    dm_draw_big_virus(&gGfxHead);
                    dm_game_graphic_effect(game_state_data, 0, 0);
                    if (temp_fp->unk_410 != 0) {
                        disp_timestop_logo(&gGfxHead, 0);
                    }
                }
            }
            break;

        case ENUM_EVS_GAMESEL_1:
        case ENUM_EVS_GAMESEL_3:
        case ENUM_EVS_GAMESEL_5:
            if (temp_s3 == 0) {
                if (temp_fp->unk_880 != 0) {
                    temp_fp->unk_880 = 0;
                    return;
                }

                disp_logo_setup(&gGfxHead);

                gSPDisplayList(gGfxHead++, alpha_texture_init_dl);

                for (var_s1 = 0; var_s1 < 2; var_s1++) {
                    draw_virus_number(&gGfxHead, game_state_data[var_s1].unk_025, RO_800B1E8C[var_s1][0],
                                      RO_800B1E8C[var_s1][1], 1.0f, 1.0f);
                }

                if (evs_gamemode == ENUM_EVS_GAMEMODE_3) {
                    temp_s1_3 = 0x2A30 - evs_game_time;
                    func_8006A198(&gGfxHead, MAX(temp_s1_3, 0) + 5, 0x9A, 0xA7);
                } else {
                    func_8006A098(&gGfxHead, evs_game_time, 0x9A, 0xA7);
                }

                if (evs_story_flg != 0) {
                    var_s2_3 = 0;
                    for (var_s1 = 0; var_s1 < 2U; var_s1++) {
                        if (temp_fp->unk_89C[var_s1] == 0) {
                            func_800695A8(&gGfxHead, RO_800B1D18[var_s1][0], RO_800B1D18[var_s1][1], var_s2_3++);
                        }
                    }
                } else {
                    for (var_s1 = 0; var_s1 < 2; var_s1++) {
                        draw_count_number(&gGfxHead, 0, 2, temp_fp->unk_8B4[var_s1], RO_800B23C4[var_s1], 0x98);
                    }

                    var_s2_3 = 0;
                    for (var_s1 = 0; var_s1 < 2; var_s1++) {
                        for (var_s0_5 = temp_fp->unk_89C[var_s1]; var_s0_5 < evs_vs_count; var_s0_5++) {
                            func_800695A8(&gGfxHead, RO_800B1D2C[0][var_s1],
                                          RO_800B1D2C[evs_vs_count][var_s0_5], var_s2_3++);
                        }
                    }
                }

                if (evs_gamemode == ENUM_EVS_GAMEMODE_1) {
                    var_s7 = &temp_fp->unk_43C->unk_00[7];
                } else {
                    var_s7 = &temp_fp->unk_43C->unk_00[0xF];
                }

                temp_v0_5 = var_s7->unk_4;
                temp_v1_12 = temp_fp->unk_43C;

                StretchAlphaTexBlock(&gGfxHead, temp_v0_5[0], temp_v0_5[1], var_s7->unk_0->unk_4, temp_v0_5[0],
                                     temp_v1_12->unk_00[1].unk_0->unk_4, temp_v1_12->unk_00[1].unk_4[0], 131.0f,
                                     181.0f, var_s7->unk_4[0], var_s7->unk_4[1]);

                func_80069188(&temp_fp->unk_070, temp_fp->unk_06C);
                starForce_draw(&temp_fp->unk_070, &gGfxHead, temp_fp->unk_06C);

                for (var_s1 = 0; var_s1 < 2; var_s1++) {
                    animeState_initDL(&game_state_data[var_s1].unk_094, &gGfxHead);

                    animeState_draw(&game_state_data[var_s1].unk_094, &gGfxHead, RO_800B1E9C[var_s1][0],
                                    RO_800B1E9C[var_s1][1], RO_800B23CC[var_s1], 1.0f);
                }

                for (var_s1 = 0; var_s1 < 2; var_s1++) {
                    dm_game_graphic_effect(&game_state_data[var_s1], var_s1, 0);
                }

                gSPDisplayList(gGfxHead++, alpha_texture_init_dl);
            }
            break;

        case ENUM_EVS_GAMESEL_2:
        case ENUM_EVS_GAMESEL_6:
            if (temp_s3 == 0) {
                if (temp_fp->unk_880 != 0) {
                    temp_fp->unk_880 = 0;
                    return;
                }

                for (var_s1 = 0; var_s1 < 4; var_s1++) {
                    animeState_initDL(&game_state_data[var_s1].unk_094, &gGfxHead);
                    animeState_draw(&game_state_data[var_s1].unk_094, &gGfxHead, RO_800B1D84[var_s1][0] + 0x14,
                                    RO_800B1D84[var_s1][1] + 0x28, 1.0f, 1.0f);
                }

                disp_logo_setup(&gGfxHead);

                gSPDisplayList(gGfxHead++, alpha_texture_init_dl);
                for (var_s1 = 0; var_s1 < 4; var_s1++) {
                    draw_virus_number(&gGfxHead, game_state_data[var_s1].unk_025, RO_800B1D84[var_s1][0] + 0x32,
                                      RO_800B1D84[var_s1][1] + 0x1D, 1.0f, 1.0f);
                }

                if (evs_story_flg != 0) {
                    func_8006A098(&gGfxHead, evs_game_time, 0x3B, 0x12);

                    var_s2_3 = 0;
                    for (var_s1 = 0; var_s1 < 4U; var_s1++) {
                        if (temp_fp->unk_89C[var_s1] == 0) {
                            func_800695A8(&gGfxHead, RO_800B1D08[var_s1], 0xD, var_s2_3++);
                        }
                    }
                } else if (temp_fp->unk_8C0 != 0) {
                    temp_a0_5 = temp_fp->unk_440;
                    temp_a1_6 = temp_a0_5->unk_00[0xE].unk_4;
                    var_t3 = 0;
                    temp_s7_2 = &temp_a0_5->unk_00[0xE];
                    var_t1 = &temp_a0_5->unk_00[0x16];

                    temp_s6_2 = (u16)temp_a1_6[0] >> 1;
                    temp_s4 = temp_a1_6[1] / 3;

                    for (var_s1 = 0; var_s1 < 2; var_s1++) {
                        for (var_s0_5 = 0; var_s0_5 < 4; var_s0_5++) {
                            temp_v1_16 = temp_fp->unk_8DC[var_s1][var_s0_5];
                            if (temp_v1_16 >= 0) {
                        //HELP;
                                StretchAlphaTexTile(&gGfxHead, temp_s7_2->unk_4[0], temp_s7_2->unk_4[1],
                                                    temp_s7_2->unk_0->unk_4, temp_s7_2->unk_4[0], var_t1->unk_0->unk_4,
                                                    var_t1->unk_4[0], var_t3,
                                                    temp_s4 * RO_800B23D4[temp_v1_16], temp_s6_2,
                                                    temp_s4, RO_800B1E7C[var_s1][0] + var_s0_5 * 9,
                                                    RO_800B1E7C[var_s1][1], temp_s6_2, temp_s4);
                            }
                        }

                        var_t3 += temp_s6_2;
                    }

                    var_s2_3 = 0;

                    for (var_s1 = 0; var_s1 < 2; var_s1++) {
                        for (var_s0_5 = temp_fp->unk_89C[var_s1]; var_s0_5 < evs_vs_count; var_s0_5++) {
                            func_800695A8(
                                &gGfxHead,
                                _posP4TeamStarX[evs_vs_count][var_s1][var_s0_5], 0xD, var_s2_3++);
                        }
                    }
                } else {
                    var_s2_3 = 0;

                    for (var_s1 = 0; var_s1 < 4; var_s1++) {
                        for (var_s0_5 = temp_fp->unk_89C[var_s1]; var_s0_5 < evs_vs_count; var_s0_5++) {
                            func_800695A8(
                                &gGfxHead,
                                _posP4CharStarX[evs_vs_count][var_s1][var_s0_5], 0xD, var_s2_3++);
                        }
                    }
                }

                func_80069188(&temp_fp->unk_070, temp_fp->unk_06C);
                starForce_draw(&temp_fp->unk_070, &gGfxHead, temp_fp->unk_06C);

                for (var_s1 = 0; var_s1 < 4; var_s1++) {
                    dm_game_graphic_effect(&game_state_data[var_s1], var_s1, 1);
                }

                disp_attack_effect(&gGfxHead);
            }
            break;
    }

    if (temp_fp->unk_880 != 0) {
        temp_fp->unk_880 = 0;
        return;
    }

    switch (game_state_data->unk_00C) {
        case 0x21:
            DebugMenu_8003FD0C(&gGfxHead);
            DebugMenu_8003FB00();
            break;
        case 0x20:
            DebugMenu_800409A0();
            DebugMenu_800409DC(&gGfxHead);
            break;
    }

    switch (evs_gamesel) {
        case ENUM_EVS_GAMESEL_4:
        case ENUM_EVS_GAMESEL_5:
        case ENUM_EVS_GAMESEL_6:
            func_8006A480(&gGfxHead, 0x6A, 0xAA);
            break;
    }

    if ((temp_fp->unk_000 != 0) && (countLeadingZeros() == 0)) {
        switch (evs_gamesel) {       /* switch 1; irregular */
            case ENUM_EVS_GAMESEL_0: /* switch 1 */
            case ENUM_EVS_GAMESEL_2: /* switch 1 */
                sp4C = 0x1E;
                var_t5 = 0x14;

                sp54 = var_t5;
                break;
            case ENUM_EVS_GAMESEL_1: /* switch 1 */
            case ENUM_EVS_GAMESEL_3: /* switch 1 */
                sp4C = 0x80;
                var_t5 = 0x90;
                sp54 = var_t5;
                break;
        }

        func_8006A6E8(&gGfxHead, sp4C, sp54);
    }

    if (temp_fp->unk_A28.unk_74 > 0) {
        temp_a1 = temp_fp->unk_430;

        gSPDisplayList(gGfxHead++, normal_texture_init_dl);
        gDPSetCombineLERP(gGfxHead++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0);
        gDPSetRenderMode(gGfxHead++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
        gDPSetPrimColor(gGfxHead++, 0, 0, 255, 255, 200, temp_fp->unk_A28.unk_74);
        gDPSetTextureLUT(gGfxHead++, G_TT_NONE);

#if 0
        temp_v0_2->words.w0 = 0xDE000000;
        temp_v0_2->words.w1 = (u32)normal_texture_init_dl;
        gGfxHead = temp_v0_2 + 0x10;
        gGfxHead = temp_v0_2 + 0x18;
        gGfxHead = temp_v0_2 + 0x20;
        temp_v0_2->unk_8 = 0xFCFF97FF;
        temp_v0_2->unk_C = 0xFF2DFEFF;
        temp_v0_2->unk_10 = 0xE200001C;
        temp_v0_2->unk_14 = 0x00504240;
        temp_v0_2->unk_18 = 0xFA000000;
        temp_v0_2->unk_1C = (s32) (temp_fp->unk_A9F | ~0x37FF);
        temp_v0_2->unk_20 = 0xE3001001;
        temp_v0_2->unk_24 = 0;
#endif
#if 0
        temp_v0_2->unk_28 = 0xFD900000;
        temp_v0_2->unk_2C = (void* ) temp_a1->unk_00[0xC].unk_0->unk_4;
        temp_v0_2->unk_30 = 0xF5900000;
        temp_v0_2->unk_34 = 0x07000000;
        temp_v0_2->unk_38 = 0xE6000000;
        temp_v0_2->unk_3C = 0;
        temp_v0_2->unk_40 = 0xF3000000;
#endif
        temp_t0 = temp_a1->unk_00[0xC].unk_4;
        var_a3 = 0x800;
        //gGfxHead = temp_v0_2 + 0x28;
        //gGfxHead = temp_v0_2 + 0x30;
        //gGfxHead = temp_v0_2 + 0x38;
        //gGfxHead = temp_v0_2 + 0x40;
        //gGfxHead = temp_v0_2 + 0x48;

        temp_a2 = temp_t0[0];

        temp_s7 = &temp_a1->unk_00[0xC];
        temp_a0 = temp_a2 >> 4;
        if (temp_a0 != 0) {
            var_a3 = temp_a0 + 0x7FF;
        }

        var_v1 = ((s32) ((temp_a2 * temp_t0[1]) + 3) >> 2) - 1;

        if (var_v1 >= 0x800) {
            var_v1 = 0x7FF;
        }
        if (temp_a0 != 0) {
            var_v0 = (var_a3 / (s32)temp_a0) & 0xFFF;
        } else {
            var_v0 = var_a3 & 0xFFF;
        }
#if 0
        temp_a0_2 = gGfxHead;
        temp_v0_2->unk_44 = ((var_v1 & 0xFFF) << 0xC) | 0x07000000 | var_v0;
        temp_a0_2->words.w0 = 0xE7000000;
        temp_a0_2->words.w1 = 0;
        gGfxHead = temp_a0_2 + 8;
        gGfxHead = temp_a0_2 + 0x10;
        temp_a0_2->unk_8 = (s32) (((((s32) (((u16) temp_s7->unk_4->unk_0 >> 1) + 7) >> 3) & 0x1FF) << 9) | 0xF5800000);
        temp_a0_2->unk_C = 0;
        temp_a0_2->unk_10 = 0xF2000000;
#endif
#if 0
        temp_a0_2->unk_14 = (s32) (((((temp_a1_2->unk_0 - 1) * 4) & 0xFFF) << 0xC) | (((temp_a1_2->unk_2 - 1) * 4) & 0xFFF));
#endif
        temp_a1_2 = temp_s7->unk_4;
        gDPLoadTextureBlock_4b(gGfxHead++, temp_a1->unk_00[0xC].unk_0->unk_4, G_IM_FMT_I, temp_a1_2[0], temp_a1_2[1], 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

        //gGfxHead = temp_a0_2 + 0x18;
        drawCursorPattern(&gGfxHead, temp_s7->unk_4[0], temp_s7->unk_4[1], 0x10, 0x10, temp_fp->unk_A28.unk_28 - 6,
                          temp_fp->unk_A28.unk_2C - 6, (temp_fp->unk_A28.unk_3C * 0x14) + 0xC,
                          (temp_fp->unk_A28.unk_48 * 3) + 0xC);

        msgWnd_update(&temp_fp->unk_A28);
        msgWnd_draw(&temp_fp->unk_A28, &gGfxHead);
    }

    temp_v1_8 = temp_fp->unk_A28.unk_74 + temp_fp->unk_AA8;
    if (temp_v1_8 >= 0) {
        var_a0 = 0xFF;
        if (temp_v1_8 < 0x100) {
            var_a0 = temp_v1_8;
        }
    } else {
        var_a0 = 0;
    }
    temp_fp->unk_A28.unk_74 = var_a0;

    temp_v1_9 = temp_fp->unk_38C + temp_fp->unk_390;
    if (temp_v1_9 >= 0) {
        var_a1 = 0x1E;
        if (temp_v1_9 < 0x1F) {
            var_a1 = temp_v1_9;
        }
    } else {
        var_a1 = 0;
    }
    temp_fp->unk_38C = var_a1;

    func_80076CCC(&gGfxHead, temp_fp->unk_38C);

    if (temp_fp->unk_880 != 0) {
        temp_fp->unk_880 = 0;
        return;
    }
}
#else
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", dm_game_graphic2);
#endif
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/dm_game_main", RO_800C8984_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/dm_game_main", RO_800C898C_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/dm_game_main", RO_800C8994_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_game_main", dm_game_graphic2);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_game_main", dm_game_graphic_onDoneSawp);
#endif

#if VERSION_CN
void dm_game_graphic_onDoneSawp(void) {
    struct_watchGame *watchGameP = watchGame;
    s32 microseconds;
    s32 i;
    s32 j;

    func_8002BA98_cn(0xD, 0);

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

    func_8002BA98_cn(0, 0);

    for (j = 0; j < evs_gamespeed; j++) {
        bool var_s3 = false;
        bool temp_s1 = countLeadingZeros();

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
                key_control_main(&game_state_data[0], &game_map_data[0], 0, main_joy[0]);
                break;

            case ENUM_EVS_GAMESEL_1:
            case ENUM_EVS_GAMESEL_3:
                for (i = 0; i < 2; i++) {
                    key_control_main(&game_state_data[i], &game_map_data[i], i, main_joy[i]);
                }
                break;

            default:
                for (i = 0; i < 4; i++) {
                    key_control_main(&game_state_data[i], &game_map_data[i], i, main_joy[i]);
                }
                break;
        }

        if ((watchGameP->unk_000 == 0) && !var_s3) {
            for (i = 0; i < evs_playcnt; i++) {
                replay_record(i, joygam[i]);
            }
        }
    }

    func_8002BA98_cn(0xD, 0);
}
#endif

void func_80071A44(void) {
}

/**
 * Original name: main_techmes
 */
#if VERSION_US || VERSION_CN
enum_main_no main_techmes(struct_800EB670 *arg0) {
    struct_watchGame *watchGameP;
    bool var_s3 = true;
    OSMesgQueue sp20;
    OSMesg sp38[8];
    struct_800FAF98_unk_64 sp58;
    u8 temp_s1;

    osCreateMesgQueue(&sp20, sp38, ARRAY_COUNT(sp38));
    func_8002A184(arg0, &sp58, &sp20);
    dm_game_init_heap();
    watchGameP = watchGame;

    dm_game_init_static();

    heapTop = init_menu_bg(heapTop, false);
    msgWnd_init2(&watchGameP->messageWnd, &heapTop, 0x1000, 0x12, 0x10, 0x34, 0x22);
    msgWnd_addStr(&watchGameP->messageWnd, EndingLastMessage);
    watchGameP->messageWnd.unk_20 = 1;
    watchGameP->messageWnd.unk_24 = 1;

    temp_s1 = evs_seqence;
    evs_seqence = 0;
    dm_game_init(false);
    evs_seqence = temp_s1;

    dm_seq_play_in_game(SEQ_INDEX_23);

    while (var_s3) {
        osRecvMesg(&sp20, NULL, OS_MESG_BLOCK);
        joyProcCore();

#if VERSION_CN
        if (D_80092F10_cn) {
            graphic_no = GRAPHIC_NO_0;
            dm_audio_update();
        } else {
#endif
            switch (watchGameP->unk_9AC) {
                case 0x0:
                    if (watchGameP->unk_9B0 == 0xFF) {
                        watchGameP->unk_9AC = 1;
                    } else {
                        s32 temp_v1_3 = watchGameP->unk_9B0 + 4;
                        s32 var_a0;

                        if (temp_v1_3 <= 0xFF) {
                            var_a0 = temp_v1_3;
                        } else {
                            var_a0 = 0xFF;
                        }
                        watchGameP->unk_9B0 = var_a0;
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
                        var_s3 = false;
                    } else {
                        s32 var_v0;

                        var_v0 = watchGameP->unk_9B0 - 4;
                        if (var_v0 < 0) {
                            var_v0 = 0;
                        }
                        watchGameP->unk_9B0 = var_v0;
                    }
                    break;
            }

            dm_audio_update();
            graphic_no = GRAPHIC_NO_6;

#if VERSION_CN
        }
#endif
    }

    graphic_no = GRAPHIC_NO_0;
    dm_audio_stop();

    while (!dm_audio_is_stopped() || (pendingGFX != 0)) {
        osRecvMesg(&sp20, NULL, OS_MESG_BLOCK);
        dm_audio_update();
    }

    func_8002A1DC(arg0, &sp58);
    return MAIN_NO_3;
}
#endif

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

    dm_draw_KaSaMaRu(&gGfxHead, &mtx, &vtx, msgWnd_isSpeaking(&watchGameP->messageWnd), 0xC8, 0x80, 1, 0xFFU);
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

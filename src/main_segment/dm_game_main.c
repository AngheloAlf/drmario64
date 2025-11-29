/**
 * Original filename: dm_game_main.c
 */

#include "dm_game_main.h"

#include "defines.h"
#include "libc/stdbool.h"
#include "macros_defines.h"

#include "ultratypes.h"
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
#include "bg_tasks.h"
#include "tex_func.h"
#include "main_story.h"
#include "debug_menu.h"
#include "nnsched.h"
#include "static.h"
#include "dm_virus_init.h"
#include "calc.h"
#include "066580.h"
#include "libc/assert.h"
#include "dm_thread.h"

#if VERSION_US || VERSION_GW || CC_CHECK
#else
#define AVOID_JOY_FUNCTIONS 1
#endif
#include "joy.h"

#if VERSION_CN && !CC_CHECK
void joyCursorFastSet(u16 mask, u8 index);
#endif

typedef struct struct_gameGeom {
    /* 0x0000 */ Mtx mtxBuf[3][0x20];
    /* 0x1800 */ Vtx vtxBuf[3][0x80];
} struct_gameGeom; // size = 0x3000

/**
 * Original name: gameGeom
 */
struct struct_gameGeom *gameGeom;

/**
 * Original name: game_state_data
 */
struct_game_state_data game_state_data[4];

/**
 * Original name: game_map_data
 */
GameMapCell game_map_data[4][GAME_MAP_ROWS * GAME_MAP_COLUMNS];

/**
 * Original name: virus_map_data
 */
struct_virus_map_data virus_map_data[4][16 * 8]; // 16 << 3?

/**
 * Original name: virus_map_disp_order
 */
u8 virus_map_disp_order[4][VIRUS_MAP_DISP_ORDER_LEN];

typedef struct struct_watchGame_unk_070 {
    /* 0x00 */ UNK_TYPE *unk_00;
    /* 0x04 */ UNK_TYPE *unk_04;
    /* 0x08 */ s32 unk_08[0x10];
} struct_watchGame_unk_070; // size = 0x48

typedef struct ScoreNumsNumbers {
    /* 0x00 */ s32 pos[2]; /* Original name: pos */
    /* 0x08 */ s32 number; /* Original name: number */
    /* 0x0C */ s32 color;  /* Original name: color */
    /* 0x10 */ f32 time;   /* Original name: time */
} ScoreNumsNumbers;        // size = 0x14

typedef struct ScoreNums {
    /* 0x00 */ ScoreNumsNumbers numbers[8]; /* Original name: numbers */
    /* 0xA0 */ s32 index;                   /* Original name: index */
} ScoreNums;                                // size = 0xA4

typedef struct TimeAttackResult {
    /* 0x00 */ s32 level;                          /* Original name: level */
    /* 0x04 */ bool bonus;                         /* Original name: bonus */
    /* 0x08 */ s32 flow; /* Original name: flow */ // TODO: enum?
    /* 0x0C */ s32 frame;                          /* Original name: frame */
    /* 0x10 */ s32 cnt;                            /* Original name: cnt */
    /* 0x14 */ u32 time;                           /* Original name: time */
    /* 0x18 */ s32 combo;                          /* Original name: combo */
    /* 0x1C */ s32 virus;                          /* Original name: virus */
    /* 0x20 */ u32 score;                          /* Original name: score */
    /* 0x24 */ u32 scoreDelta;                     /* Original name: scoreDelta */
    /* 0x28 */ u32 result;                         /* Original name: result */
} TimeAttackResult;                                // size = 0x2C

// struct_dm_game_main_c_5535
typedef struct struct_watchGame {
    /* 0x000 */ UNK_TYPE4 unk_000;
    /* 0x004 */ s32 unk_004;
    /* 0x008 */ s32 unk_008;
    /* 0x00C */ s32 unk_00C[0xC];
    /* 0x03C */ s32 unk_03C[0xC];
    /* 0x06C */ s32 unk_06C;
    /* 0x070 */ struct_watchGame_unk_070 unk_070;
    /* 0x0B8 */ ScoreNums unk_0B8[4];
    /* 0x348 */ s32 unk_348[MAXCONTROLLERS];
    /* 0x358 */ s32 unk_358[MAXCONTROLLERS];
    /* 0x368 */ EtcPartIndex unk_368[MAXCONTROLLERS];
    /* 0x378 */ UNK_TYPE4 unk_378;
    /* 0x37C */ s32 unk_37C[4];
    /* 0x38C */ UNK_TYPE unk_38C;
    /* 0x390 */ UNK_TYPE unk_390;
    /* 0x394 */ s32 unk_394;
    /* 0x398 */ s32 unk_398;
    /* 0x39C */ s32 unk_39C[4];
    /* 0x3AC */ s32 unk_3AC;
    /* 0x3B0 */ s32 unk_3B0;
    /* 0x3B4 */ s32 unk_3B4;
    /* 0x3B8 */ s32 unk_3B8;
    /* 0x3BC */ s32 unk_3BC; // enum_evs_gamemode?
    /* 0x3C0 */ s32 unk_3C0;
    /* 0x3C4 */ s32 unk_3C4;
    /* 0x3C8 */ f32 unk_3C8;
    /* 0x3CC */ f32 unk_3CC;
    /* 0x3D0 */ f32 unk_3D0[ANIMES_COUNT][2];
    /* 0x3E8 */ f32 unk_3E8[3];
    /* 0x3F4 */ f32 unk_3F4[ANIMES_COUNT];
    /* 0x400 */ UNK_TYPE4 unk_400[3]; // bool?
    /* 0x40C */ s32 unk_40C;
    /* 0x410 */ UNK_TYPE unk_410;
    /* 0x414 */ s32 unk_414;
    /* 0x418 */ u8 unk_418[3];
    /* 0x41B */ UNK_TYPE1 pad_41B[1]; // pad?
    /* 0x41C */ s32 unk_41C;
    /* 0x420 */ s32 unk_420;
    /* 0x424 */ s32 unk_424;
    /* 0x428 */ UNK_TYPE4 unk_428;
    /* 0x42C */ UNK_TYPE1 unk_42C[0x4];
    /* 0x430 */ struct TiTexData *unk_430;
    /* 0x434 */ struct TiTexData *unk_434;
    /* 0x438 */ struct TiTexData *unk_438;
    /* 0x43C */ struct TiTexData *unk_43C;
    /* 0x440 */ struct TiTexData *unk_440;
    /* 0x444 */ struct TiTexData *unk_444;
    /* 0x448 */ struct TiTexData *unk_448;
    /* 0x44C */ SAnimeState animeStates[ANIMES_COUNT];
    /* 0x50C */ SAnimeSmog animeSmogs[ANIMES_COUNT];
    /* 0x878 */ UNK_TYPE unk_878;
    /* 0x87C */ TexturePtr unk_87C; // SnapBg?
    /* 0x880 */ s32 unk_880;
    /* 0x884 */ void *gameEtcSeg;
    /* 0x888 */ s32 effect_timer[4];
    /* 0x898 */ s32 unk_898;
    /* 0x89C */ s32 unk_89C[TEAMNUMBER_MAX]; // Indexed by TeamNumber/`struct_game_state_data::team_no`
    /* 0x8AC */ s32 unk_8AC[2];
    /* 0x8B4 */ s32 unk_8B4[2];
    /* 0x8BC */ s32 unk_8BC;
    /* 0x8C0 */ s32 unk_8C0;
    /* 0x8C4 */ s32 unk_8C4;
    /* 0x8C8 */ s32 unk_8C8;
    /* 0x8CC */ s32 unk_8CC[TEAMNUMBER_MAX];    // Indexed by TeamNumber/`struct_game_state_data::team_no`
    /* 0x8DC */ s32 unk_8DC[TEAMNUMBER_MAX][4]; // Outer indexed by TeamNumber/`struct_game_state_data::team_no`
    /* 0x91C */ MessageWnd messageWnd;
    /* 0x99C */ s32 unk_99C;
    /* 0x9A0 */ s32 unk_9A0[3];
    /* 0x9AC */ s32 unk_9AC; // TODO: func_8006A938 implies this member is part of unk_9A0, but it doesn't seem to make
                             // much sense to do so
    /* 0x9B0 */ s32 unk_9B0;
    /* 0x9B4 */ s32 unk_9B4;
    /* 0x9B8 */ s32 unk_9B8;
    /* 0x9BC */ s32 unk_9BC;
    /* 0x9C0 */ UNK_TYPE4 unk_9C0;
    /* 0x9C4 */ UNK_TYPE4 unk_9C4;
    /* 0x9C8 */ s32 unk_9C8;
    /* 0x9CC */ s32 unk_9CC;
    /* 0x9D0 */ TimeAttackResult unk_9D0[2];
    /* 0xA28 */ MessageWnd unk_A28;
    /* 0xAA8 */ s32 unk_AA8;
    /* 0xAAC */ unsigned char password[42];
    /* 0xAD8 */ RecordWritingMessage recMessage;
} struct_watchGame; // size = 0xB60

/**
 * Original name: watchGame
 */
struct_watchGame *watchGame;

/**
 * Original name: evs_gamemode
 */
enum_evs_gamemode evs_gamemode;

/**
 * Original name: CapsMagazine
 */
u8 CapsMagazine[0x100];

// GameStateBackup?
typedef struct struct_gameBackup {
    /* 0x0000 */ struct_watchGame game;
    /* 0x0B60 */ struct_game_state_data state[MAX_PLAYERS];
    /* 0x1A70 */ GameMapCell map[MAX_PLAYERS][GAME_MAP_ROWS * GAME_MAP_COLUMNS];
    /* 0x2FB0 */ s32 highScore;
    /* 0x2FB4 */ s32 gameTime;
} struct_gameBackup; // size = 0x2FB8

/**
 * Original name: gameBackup
 */
struct_gameBackup *gameBackup[2];

/**
 * Original name: heapTop
 */
static void *heapTop;

u8 virus_anime_table[3][4] = {
    { 7, 8, 0x10, 0x11 },
    { 9, 0xA, 0x12, 0x13 },
    { 0xB, 0xC, 0x14, 0x15 },
};
s8 dm_chaine_se_table_vs_178[4] = {
    SND_INDEX_59,
    SND_INDEX_75,
    SND_INDEX_0,
    SND_INDEX_0,
};
s8 dm_chaine_se_table_4p_179[4][3] = {
    { SND_INDEX_77, SND_INDEX_76, SND_INDEX_75 },
    { SND_INDEX_59, SND_INDEX_77, SND_INDEX_76 },
    { SND_INDEX_75, SND_INDEX_59, SND_INDEX_77 },
    { SND_INDEX_76, SND_INDEX_75, SND_INDEX_59 },
};
s32 rotate_table_474[4] = { 1, 3, 4, 2 };
s32 rotate_mtx_475[6] = { 2, 0, 3, 1, 2, 0 };
s32 D_800A6FC4 = 0;
bool visible_fall_point[4] = {
#if VERSION_US
    true,
    true,
    true,
    true,
#elif VERSION_GW || VERSION_CN
    false,
    false,
    false,
    false,
#else
#error ""
#endif
};

#ifdef NN_SC_PERF
s32 D_800BEF08_cn = 0;
#endif

/**
 * Original name: dm_calc_score
 */
u32 dm_calc_score(struct_game_state_data *state, s32 level) {
    u32 score = 0;
    s32 i;

    for (i = state->erase_virus_count_old; i < state->erase_virus_count; i++) {
        s32 var_v1 = MIN(i, ARRAY_COUNT(Score1p[level]) - 1);

        score += Score1p[level][var_v1] * 100;
    }

    state->erase_virus_count_old = state->erase_virus_count;
    return score;
}

/**
 * Original name: dm_add_score
 */
void dm_add_score(struct_game_state_data *state, u32 score) {
    state->game_score += score;
    if (state->game_score > 9999900) {
        state->game_score = 9999900;
    }

    if (evs_high_score < state->game_score) {
        evs_high_score = state->game_score;
    }
}

/**
 * Original name: dm_make_score
 */
u32 dm_make_score(struct_game_state_data *state) {
    s32 score;
    s32 level;

    if (evs_story_flg != 0) {
        if (evs_story_level < 3) {
            level = evs_story_level;
        } else {
            level = 2;
        }
    } else {
        switch (evs_gamesel) {
            case ENUM_EVS_GAMESEL_0:
                level = state->cap_def_speed;
                break;

            case ENUM_EVS_GAMESEL_1:
                level = state->cap_def_speed;
                break;

            case ENUM_EVS_GAMESEL_2:
                level = state->cap_def_speed;
                break;

            case ENUM_EVS_GAMESEL_3:
                level = state->cap_def_speed;
                break;

            case ENUM_EVS_GAMESEL_4:
                level = state->cap_def_speed;
                break;

            case ENUM_EVS_GAMESEL_5:
                level = state->cap_def_speed;
                break;

            case ENUM_EVS_GAMESEL_6:
                level = state->cap_def_speed;
                break;

            default:
                break;
        }
    }

    score = dm_calc_score(state, level);
    dm_add_score(state, score);
    return score;
}

/**
 * Original name: dm_attack_se
 */
void dm_attack_se(struct_game_state_data *state, s32 player_no) {
    s32 i;

    if (state->chain_line < 2) {
        return;
    }

    switch (evs_gamesel) {
        case ENUM_EVS_GAMESEL_0:
            dm_snd_play_in_game(SND_INDEX_59);
            break;

        case ENUM_EVS_GAMESEL_1:
        case ENUM_EVS_GAMESEL_3:
            dm_snd_play_in_game(dm_chaine_se_table_vs_178[player_no]);
            break;

        case ENUM_EVS_GAMESEL_2:
            for (i = 0; i < ARRAY_COUNT(dm_chaine_se_table_4p_179[player_no]); i++) {
                if ((state->chain_color[3] >> i) & 1) {
                    dm_snd_play_in_game(dm_chaine_se_table_4p_179[player_no][i]);
                }
            }
            break;

        default:
            break;
    }
}

/**
 * Original name: dm_warning_h_line
 */
void dm_warning_h_line(struct_game_state_data *state, GameMapCell *map) {
    bool flg = false;
    s32 row;

    for (row = 1; row < 4; row++) {
        s32 column;

        for (column = 0; column < GAME_MAP_COLUMNS; column++) {
            if (get_map_info(map, column, row) == true) {
                flg = true;
                break;
            }
        }

        if (flg) {
            break;
        }
    }

    if (flg) {
        if (!state->warning_se_flag) {
            state->warning_se_flag = true;
        }
    } else {
        state->warning_se_flag = false;
    }
}

/**
 * Original name: set_down_flg
 */
bool set_down_flg(GameMapCell *map) {
    bool flg[2];
    s32 i;
    s32 j;
    bool ret;
    u32 l;

    for (i = 0; i < (GAME_MAP_ROWS - 2) * GAME_MAP_COLUMNS; i++) {
        map[i].capsel_m_flg[1] = 1;
    }

    for (j = GAME_MAP_ROWS - 3; j >= 0; j--) {
        for (i = 0; i < GAME_MAP_COLUMNS; i++) {
            u32 index = GAME_MAP_GET_INDEX(j, i);

            if ((map + index)->capsel_m_flg[0] == 0) {
                (map + index)->capsel_m_flg[1] = 0;
                continue;
            }

            if ((map + index)->capsel_m_flg[4] >= 0) {
                (map + index)->capsel_m_flg[1] = 0;
                continue;
            }

            if (((map + index)->capsel_m_g == 2) || ((map + index)->capsel_m_g == 3)) {
                if ((map + index)->capsel_m_g == 2) {
                    for (l = 0; l < 2; l++) {
                        flg[l] = true;
                        if (get_map_info(map, (map + index + l)->pos_m_x, (map + index + l)->pos_m_y + 1) == 1) {
                            if ((map + index + l + GAME_MAP_COLUMNS)->capsel_m_flg[1] != 1) {
                                flg[l] = false;
                            }
                        }
                    }

                    if (!flg[0] || !flg[1]) {
                        for (l = 0; l < 2; l++) {
                            (map + index + l)->capsel_m_flg[1] = 0;
                        }
                    }
                } else if ((map + index)->capsel_m_g == 3) {
                    for (l = 0; l < 2; l++) {
                        flg[l] = true;
                        if (get_map_info(map, (map + index - l)->pos_m_x, (map + index - l)->pos_m_y + 1) == 1) {
                            if ((map + index - l + GAME_MAP_COLUMNS)->capsel_m_flg[1] != 1) {
                                flg[l] = false;
                            }
                        }
                    }

                    if (!flg[0] || !flg[1]) {
                        for (l = 0; l < 2; l++) {
                            (map + index - l)->capsel_m_flg[1] = 0;
                        }
                    }
                }
            } else if (get_map_info(map, (map + index)->pos_m_x, (map + index)->pos_m_y + 1) == 1) {
                if ((map + index + GAME_MAP_COLUMNS)->capsel_m_flg[1] != 1) {
                    (map + index)->capsel_m_flg[1] = 0;
                }
            }
        }
    }

    for (i = ret = 0; i < (GAME_MAP_ROWS - 1) * GAME_MAP_COLUMNS; i++) {
        if ((map[i].capsel_m_flg[0] != 0) && (map[i].capsel_m_flg[1] != 0)) {
            ret++;
        }
    }

    return ret;
}

/**
 * Original name: go_down
 */
void go_down(struct_game_state_data *state, GameMapCell *map, s32 cout) {
    bool se_flg = false;
    s32 i;
    s32 j;

    state->erase_anime_count++;
    if (state->erase_anime_count < cout) {
        return;
    }

    state->erase_anime_count = 0;

    for (i = GAME_MAP_ROWS - 1; i >= 0; i--) {
        for (j = 0; j < GAME_MAP_COLUMNS; j++) {
            s32 index = GAME_MAP_GET_INDEX(i, j);

            if (map[index].capsel_m_flg[1] != 0) {
                set_map(map, map[index].pos_m_x, map[index].pos_m_y + 1, map[index].capsel_m_g, map[index].capsel_m_p);
                clear_map(map, map[index].pos_m_x, map[index].pos_m_y);
                se_flg = true;
            }
        }
    }

    if (se_flg) {
        dm_snd_play_in_game(SND_INDEX_55);
    }

    if (state->flg_game_over && (state->cnd_training == dm_cnd_training)) {
        for (j = 0; j < (GAME_MAP_ROWS - 1) * GAME_MAP_COLUMNS; j++) {
            if ((map[j].capsel_m_flg[0] != 0) && (map[j].capsel_m_flg[1] == 0) && (map[j].capsel_m_p < 3)) {
                map[j].capsel_m_p += 3;
            }
        }
    }

    if (set_down_flg(map) == 0) {
        if (dm_h_erase_chack(map) || dm_w_erase_chack(map)) {
            if (!state->flg_game_over) {
                state->mode_now = dm_mode_erase_chack;
            } else {
                state->mode_now = dm_mode_tr_erase_chack;
            }
            state->cap_speed_count = 0;
        } else {
            if (!state->flg_game_over) {
                state->mode_now = dm_mode_cap_set;
            } else {
                state->mode_now = dm_mode_tr_cap_set;
            }
        }
    }
}

/**
 * Original name: erase_anime
 */
void erase_anime(GameMapCell *map) {
    s32 i;

    for (i = 0; i < (GAME_MAP_ROWS - 1) * GAME_MAP_COLUMNS; i++) {
        GameMapCell *cell = &map[i];

        if ((cell->capsel_m_flg[0] != 0) && (cell->capsel_m_flg[2] != 0)) {
            cell->capsel_m_g++;

            if (cell->capsel_m_flg[4] >= 0) {
                if (cell->capsel_m_g >= 0xF) {
                    clear_map(map, cell->pos_m_x, cell->pos_m_y);
                }
            } else {
                if (cell->capsel_m_g >= 7) {
                    clear_map(map, cell->pos_m_x, cell->pos_m_y);
                }
            }
        }
    }
}

/**
 * Original name: rotate_table_399
 */
const s32 rotate_table_399[] = {
    1,
    3,
    4,
    2,
};

/**
 * Original name: rotate_mtx_400
 */
const s32 rotate_mtx_400[] = {
    2, 0, 3, 1, 2, 0,
};

/**
 * Original name: throw_rotate_capsel
 */
void throw_rotate_capsel(struct_game_state_data_now_cap *cap) {
    s32 i;
    s32 vec;
    s32 save;

    if (cap->pos_x[0] == cap->pos_x[1]) {
        cap->pos_x[1]++;
        cap->pos_y[1]++;

        save = cap->capsel_p[0];
        cap->capsel_p[0] = cap->capsel_p[1];
        cap->capsel_p[1] = save;

        vec = 1;
    } else {
        cap->pos_x[1]--;
        cap->pos_y[1]--;
        vec = -1;
    }

    for (i = 0; i < ARRAY_COUNT(cap->casel_g); i++) {
        save = rotate_table_399[cap->casel_g[i]];
        save += vec;

        cap->casel_g[i] = rotate_mtx_400[save];
    }
}

/**
 * Original name: translate_capsel
 */
void translate_capsel(GameMapCell *map, struct_game_state_data *state, s32 move_vec, s32 joy_no) {
    s32 vec = 0;
    struct_game_state_data_now_cap *temp_s5 = &state->now_cap;

    if ((temp_s5->pos_y[0] <= 0) || (temp_s5->capsel_flg_0 == 0)) {
        return;
    }

    if (move_vec == 1) {
        if (temp_s5->pos_x[0] == temp_s5->pos_x[1]) {
            if ((temp_s5->pos_x[1] < 7) && (get_map_info(map, temp_s5->pos_x[1] + 1, temp_s5->pos_y[0]) != move_vec)) {
                if (temp_s5->pos_y[1] == 0) {
                    vec = 1;
                } else if (get_map_info(map, temp_s5->pos_x[0] + 1, temp_s5->pos_y[1]) != move_vec) {
                    vec = 1;
                }
            }
        } else if (temp_s5->pos_x[1] < 7) {
            if (get_map_info(map, temp_s5->pos_x[1] + 1, temp_s5->pos_y[0]) != move_vec) {
                vec = 1;
            }
        }
    } else if (move_vec == -1) {
        if (temp_s5->pos_x[0] == temp_s5->pos_x[1]) {
            if ((temp_s5->pos_x[0] > 0) && (get_map_info(map, temp_s5->pos_x[0] - 1, temp_s5->pos_y[0]) != 1)) {
                if (temp_s5->pos_y[1] == 0) {
                    vec = -1;
                } else if (get_map_info(map, temp_s5->pos_x[0] - 1, temp_s5->pos_y[1]) != 1) {
                    vec = -1;
                }
            }
        } else if (temp_s5->pos_x[0] > 0) {
            if (get_map_info(map, temp_s5->pos_x[0] - 1, temp_s5->pos_y[0]) != 1) {
                vec = -1;
            }
        }
    }

    if (vec != 0) {
        dm_snd_play_in_game(SND_INDEX_65);
        state->cap_move_se_flg = false;
        temp_s5->pos_x[0] += vec;
        temp_s5->pos_x[1] += vec;
    } else {
        if (!state->cap_move_se_flg) {
            state->cap_move_se_flg = true;
            dm_snd_play_in_game(SND_INDEX_65);
        }

        if (move_vec == 1) {
            joyCursorFastSet(R_JPAD, joy_no);
        } else if (move_vec == -1) {
            joyCursorFastSet(L_JPAD, joy_no);
        }
    }
}

/**
 * Original name: rotate_capsel
 */
void rotate_capsel(GameMapCell *map, struct_game_state_data_now_cap *cap, s32 move_vec) {
    s32 vec = 0;
    s32 save;

    if ((cap->pos_y[0] <= 0) || (cap->capsel_flg_0 == 0)) {
        return;
    }

    if (cap->pos_x[0] == cap->pos_x[1]) {
        if ((cap->pos_x[0] == 7) || (get_map_info(map, cap->pos_x[0] + 1, cap->pos_y[0]) == 1)) {
            if ((cap->pos_x[0] != 0) && (get_map_info(map, cap->pos_x[0] - 1, cap->pos_y[0]) != 1)) {
                cap->pos_x[0]--;
                vec = 1;
            }
        } else {
            cap->pos_x[1]++;
            vec = 1;
        }

        if (vec != 0) {
            cap->pos_y[1]++;
            if (move_vec == -1) {
                save = cap->capsel_p[0];
                cap->capsel_p[0] = cap->capsel_p[1];
                cap->capsel_p[1] = save;
            }
        }
    } else {
        if (cap->pos_y[0] == 1) {
            cap->pos_x[1]--;
            vec = -1;
        } else if (get_map_info(map, cap->pos_x[0], cap->pos_y[0] - 1) == 1) {
            if (get_map_info(map, cap->pos_x[0] + 1, cap->pos_y[0] - 1) != 1) {
                cap->pos_x[0]++;
                vec = -1;
            }
        } else {
            cap->pos_x[1]--;
            vec = -1;
        }

        if (vec != 0) {
            cap->pos_y[1]--;
            if (move_vec == 1) {
                save = cap->capsel_p[0];
                cap->capsel_p[0] = cap->capsel_p[1];
                cap->capsel_p[1] = save;
            }
        }
    }

    if (vec != 0) {
        s32 i;

        dm_snd_play_in_game(SND_INDEX_67);

        for (i = 0; i < ARRAY_COUNTU(cap->casel_g); i++) {
            save = rotate_table_474[cap->casel_g[i]];
            save += vec;
            cap->casel_g[i] = rotate_mtx_475[save];
        }
    }
}

#define CAPSMAGAZINE_GET_A(mag) (((mag) >> 4) % 3)
#define CAPSMAGAZINE_GET_B(mag) ((mag) % 3)

/**
 * Original name: dm_make_magazine
 */
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

/**
 * Original name: dm_init_capsel
 */
void dm_init_capsel(struct_game_state_data_now_cap *cap, u32 left_cap_col, u32 right_cap_col) {
    cap->pos_x[0] = 3;
    cap->pos_x[1] = 4;
    cap->pos_y[1] = 0;
    cap->pos_y[0] = 0;
    cap->casel_g[0] = 2;
    cap->casel_g[1] = 3;
    cap->capsel_p[0] = left_cap_col;
    cap->capsel_p[1] = right_cap_col;
    cap->capsel_flg_0 = 1;
    cap->capsel_flg_2 = 0;
    cap->capsel_flg_1 = 0;
}

/**
 * Original name: dm_init_capsel_go
 */
void dm_init_capsel_go(struct_game_state_data_now_cap *cap, s32 left_cap_col, s32 right_cap_col) {
    dm_init_capsel(cap, left_cap_col, right_cap_col);
    cap->capsel_flg_1 = 1;
}

/**
 * Original name: dm_set_capsel
 */
void dm_set_capsel(struct_game_state_data *state) {
    state->cap_move_se_flg = false;

    dm_init_capsel_go(&state->now_cap, CAPSMAGAZINE_GET_A(CapsMagazine[state->cap_magazine_cnt]),
                      CAPSMAGAZINE_GET_B(CapsMagazine[state->cap_magazine_cnt]));
    state->cap_magazine_save = state->cap_magazine_cnt;

    state->cap_magazine_cnt++;
    if (state->cap_magazine_cnt >= 254) {
        state->cap_magazine_cnt = 1;
    }

    dm_init_capsel(&state->next_cap, CAPSMAGAZINE_GET_A(CapsMagazine[state->cap_magazine_cnt]),
                   CAPSMAGAZINE_GET_B(CapsMagazine[state->cap_magazine_cnt]));
}

/**
 * Original name: _speed_561
 */
const u8 _speed_561[] = {
    0x0F,
    0x14,
    0x19,
};

/**
 * Original name: dm_capsel_speed_up
 */
void dm_capsel_speed_up(struct_game_state_data *state) {
    state->cap_count++;
    if (state->cap_count >= 10) {
        u8 temp;

        dm_snd_play_in_game(SND_INDEX_58);
        state->cap_count = 0;

        state->cap_speed++;
        temp = GameSpeed[3];
        if (temp < state->cap_speed) {
            state->cap_speed = temp;
        }
    }

    if (evs_gamemode == GMD_TaiQ) {
        state->cap_speed = MIN(_speed_561[state->game_level], state->cap_speed);
    }
}

/**
 * Original name: dm_check_game_over
 */
bool dm_check_game_over(struct_game_state_data *state, GameMapCell *map UNUSED) {
    return state->cnd_static == dm_cnd_game_over;
}

/**
 * Original name: update_flash_virus_count
 */
s32 update_flash_virus_count(struct_game_state_data *state, GameMapCell *map, bool flag) {
    s32 count = 0;
    s32 i;

    for (i = 0; i < state->flash_virus_count; i++) {
        s32 index = GAME_MAP_GET_INDEX_ALT(state->flash_virus_pos[i].row, state->flash_virus_pos[i].column);

        if (((map[index].capsel_m_flg[0] == 0) || (map[index].capsel_m_flg[2] != 0) ||
             (map[index].capsel_m_flg[4] < 0))) {
            if (flag) {
                state->flash_virus_pos[i].color = -1;
            }
        } else {
            count++;
        }
    }

    return count;
}

/**
 * Original name: dm_update_virus_count
 */
s32 dm_update_virus_count(struct_game_state_data *state, GameMapCell *map, bool flag) {
    if (evs_gamemode == GMD_FLASH) {
        state->virus_number = update_flash_virus_count(state, map, flag);
    } else {
        state->virus_number = get_virus_count(map);
    }

    return state->virus_number;
}

/**
 * Original name: dm_set_virus
 */
void dm_set_virus(struct_game_state_data *state, GameMapCell *map, struct_virus_map_data *v_map,
                  u8 order[VIRUS_MAP_DISP_ORDER_LEN]) {
    s32 virus_max;

    if (state->cnd_now != dm_cnd_init) {
        return;
    }

    virus_max = dm_get_first_virus_count(evs_gamemode, state);

    if (state->virus_order_number < virus_max) {
        while (state->virus_order_number < virus_max) {
            if (!(order[state->virus_order_number] & 0x80)) {
                break;
            }
            state->virus_order_number++;
        }

        if (state->virus_order_number < virus_max) {
            u8 cellIndex = order[state->virus_order_number];

            order[state->virus_order_number] |= 0x80;

            set_virus(map, v_map[cellIndex].x_pos, v_map[cellIndex].y_pos, v_map[cellIndex].virus_type,
                      virus_anime_table[v_map[cellIndex].virus_type][state->virus_anime]);
            if (state->cnd_training == dm_cnd_training) {
                map[cellIndex].capsel_m_p += 3;
            }
        }
    }

    if (state->virus_order_number >= virus_max) {
        state->cnd_now = dm_cnd_wait;
        state->mode_now = dm_mode_wait;
    }

    dm_update_virus_count(state, map, false);
}

/**
 * Original name: dm_virus_anime
 */
void dm_virus_anime(struct_game_state_data *state, GameMapCell *map) {
    s32 index;

    state->virus_anime_count++;
    if (state->virus_anime_spead >= state->virus_anime_count) {
        return;
    }

    state->virus_anime_count = 0;

    state->virus_anime += state->virus_anime_vec;
    if (state->virus_anime_max < state->virus_anime) {
        state->virus_anime_vec = -1;
    } else if (state->virus_anime == 0) {
        state->virus_anime_vec = 1;
    }

    for (index = 0; index < (GAME_MAP_ROWS - 1) * GAME_MAP_COLUMNS; index++) {
        if ((map[index].capsel_m_flg[0] != 0) && (map[index].capsel_m_flg[2] == 0)) {
            if (map[index].capsel_m_flg[4] >= 0) {
                map[index].capsel_m_g = virus_anime_table[map[index].capsel_m_flg[4]][state->virus_anime];
            }
        }
    }
}

/**
 * Original name: dm_capsel_erase_anime
 */
void dm_capsel_erase_anime(struct_game_state_data *state, GameMapCell *map) {
    state->erase_anime_count++;

    if (state->erase_anime_count == 10) {
        erase_anime(map);
        state->erase_anime++;
    } else if (state->erase_anime_count > 26) {
        erase_anime(map);
        set_down_flg(map);
        state->erase_anime = 0;
        state->mode_now = dm_mode_ball_down;
        state->erase_anime_count = 14;
    }
}

/**
 * Original name: dm_make_erase_h_line
 */
void dm_make_erase_h_line(struct_game_state_data *state, GameMapCell *map, s32 rowStart, s32 count, s32 column) {
    s32 row;

    for (row = rowStart; row < rowStart + count + 1; row++) {
        s32 index = GAME_MAP_GET_INDEX(row, column);

        if (map[index].capsel_m_flg[2] == 1) {
            continue;
        }

        map[index].capsel_m_flg[2] = 1;

        if (map[index].capsel_m_flg[4] < 0) {
            map[index].capsel_m_g = 5;
        } else {
            map[index].capsel_m_g = 0xD;
            state->erase_virus_count++;
            state->chain_color[3] |= 8;
            state->chain_color[3] |= (0x10 << map[index].capsel_m_flg[3]);
        }
    }
}

/**
 * Original name: dm_h_erase_chack
 */
bool dm_h_erase_chack(GameMapCell *map) {
    s32 column;

    for (column = 0; column < GAME_MAP_COLUMNS; column++) {
        s32 row;
        s32 val = 0xF;
        s32 var_a1 = 0;
        s32 var_a3 = -1;

        for (row = 0; row < GAME_MAP_ROWS - 1; row++) {
            if (map[GAME_MAP_GET_INDEX(row, column)].capsel_m_flg[0] != 0) {
                if (map[GAME_MAP_GET_INDEX(row, column)].capsel_m_flg[3] != var_a3) {
                    if (var_a1 < 3) {
                        if (row >= 0xD) {
                            break;
                        }
                        var_a3 = map[GAME_MAP_GET_INDEX(row, column)].capsel_m_flg[3];
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

/**
 * Original name: dm_h_erase_chack_set
 */
void dm_h_erase_chack_set(struct_game_state_data *state, GameMapCell *map) {
    s32 column;

    for (column = 0; column < GAME_MAP_COLUMNS; column++) {
        s32 var_s1 = 0;
        s32 var_s5 = -1;
        s32 var_s2 = -1;
        s32 var_fp = 0;
        s32 row;

        for (row = 0; row < GAME_MAP_ROWS - 1; row++) {
            if (map[GAME_MAP_GET_INDEX(row, column)].capsel_m_flg[0] != 0) {
                if (map[GAME_MAP_GET_INDEX(row, column)].capsel_m_flg[3] != var_s2) {
                    if (var_s1 >= 3) {
                        dm_make_erase_h_line(state, map, var_s5, var_s1, column);
                        if (state->chain_count == 0) {
                            state->chain_color[3] |= (1 << var_s2);
                        }
                        state->chain_color[var_s2]++;
                        state->chain_line++;
                    }

                    if (row < 0xD) {
                        var_s5 = row;
                        var_s2 = map[GAME_MAP_GET_INDEX(row, column)].capsel_m_flg[3];
                        var_s1 = 0;
                    } else {
                        var_fp = 1;
                    }
                } else {
                    var_s1++;
                    if (row == 15) {
                        if (var_s1 >= 3) {
                            dm_make_erase_h_line(state, map, var_s5, var_s1, column);
                            if (state->chain_count == 0) {
                                state->chain_color[3] |= (1 << var_s2);
                            }
                            state->chain_color[var_s2]++;
                            state->chain_line++;
                        }
                    }
                }
            } else {
                if (var_s1 >= 3) {
                    dm_make_erase_h_line(state, map, var_s5, var_s1, column);
                    if (state->chain_count == 0) {
                        state->chain_color[3] |= (1 << var_s2);
                    }
                    state->chain_color[var_s2]++;
                    state->chain_line++;
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

/**
 * Original name: dm_make_erase_w_line
 */
void dm_make_erase_w_line(struct_game_state_data *state, GameMapCell *map, s32 columnStart, s32 chain, s32 row) {
    s32 column = columnStart;
    u32 columnEnd = column + chain + 1;

    for (; column < columnEnd; column++) {
        s32 index = GAME_MAP_GET_INDEX(row, column);

        if (map[index].capsel_m_flg[2] != 1) {
            map[index].capsel_m_flg[2] = 1;

            if (map[index].capsel_m_flg[4] < 0) {
                map[index].capsel_m_g = 5;
            } else {
                map[index].capsel_m_g = 0xD;
                state->erase_virus_count++;
                state->chain_color[3] |= 8;
                state->chain_color[3] |= (0x10 << map[index].capsel_m_flg[3]);
            }
        }
    }
}

/**
 * Original name: dm_w_erase_chack
 */
bool dm_w_erase_chack(GameMapCell *map) {
    s32 row;

    for (row = 0; row < GAME_MAP_ROWS - 1; row++) {
        s32 var_a1 = 0;
        s32 var_a3 = -1;
        s32 column;

        for (column = 0; column < GAME_MAP_COLUMNS; column++) {
            if (map[GAME_MAP_GET_INDEX(row, column)].capsel_m_flg[0] != 0) {
                if (map[GAME_MAP_GET_INDEX(row, column)].capsel_m_flg[3] != var_a3) {
                    if (var_a1 >= 3) {
                        return true;
                    } else if (column < 5) {
                        var_a3 = map[GAME_MAP_GET_INDEX(row, column)].capsel_m_flg[3];
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

/**
 * Original name: dm_w_erase_chack_set
 */
void dm_w_erase_chack_set(struct_game_state_data *state, GameMapCell *map) {
    s32 row;

    for (row = 0; row < GAME_MAP_ROWS - 1; row++) {
        s32 column;
        s32 chain = 0;
        s32 chain_start = -1;
        s32 chain_col = -1;
        bool var_fp = false;

        for (column = 0; column < GAME_MAP_COLUMNS; column++) {
            u32 index = GAME_MAP_GET_INDEX(row, column);

            if (map[index].capsel_m_flg[0] != 0) {
                if (map[index].capsel_m_flg[3] != chain_col) {
                    if (chain >= 3) {
                        dm_make_erase_w_line(state, map, chain_start, chain, row);
                        if (state->chain_count == 0) {
                            state->chain_color[3] |= 1 << chain_col;
                        }
                        state->chain_color[chain_col]++;
                        state->chain_line++;
                    }
                    if (column >= 5) {
                        var_fp = true;
                    } else {
                        chain_start = column;
                        chain_col = map[index].capsel_m_flg[3];
                        chain = 0;
                    }
                } else {
                    chain++;
                    if (column == 7) {
                        if (chain >= 3) {
                            dm_make_erase_w_line(state, map, chain_start, chain, row);
                            if (state->chain_count == 0) {
                                state->chain_color[3] |= 1 << chain_col;
                            }
                            state->chain_color[chain_col]++;
                            state->chain_line++;
                        }
                    }
                }
            } else {
                if (chain >= 3) {
                    dm_make_erase_w_line(state, map, chain_start, chain, row);
                    if (state->chain_count == 0) {
                        state->chain_color[3] |= 1 << chain_col;
                    }
                    state->chain_color[chain_col]++;
                    state->chain_line++;
                }

                if (column >= 5) {
                    var_fp = true;
                } else {
                    chain = 0;
                    chain_start = -1;
                    chain_col = -1;
                }
            }

            if (var_fp) {
                break;
            }
        }
    }
}

/**
 * Original name: dm_h_ball_chack
 */
void dm_h_ball_chack(GameMapCell *map) {
    u32 column;

    for (column = 0; column < GAME_MAP_COLUMNS; column++) {
        u32 row;

        for (row = 0; row < GAME_MAP_ROWS - 1; row++) {
            s32 index = GAME_MAP_GET_INDEX(row, column);
            s32 temp;

            if (map[index].capsel_m_flg[0] == 0) {
                continue;
            }

            if (map[index].capsel_m_g == 0) {
                temp = GAME_MAP_GET_INDEX(row + 1, column);
                if (map[temp].capsel_m_g != 1) {
                    map[index].capsel_m_g = 4;
                }
            } else if (map[index].capsel_m_g == 1) {
                if (map[index].pos_m_y == 1) {
                    map[index].capsel_m_g = 4;
                } else {
                    temp = GAME_MAP_GET_INDEX(row - 1, column);
                    if (map[temp].capsel_m_g != 0) {
                        map[index].capsel_m_g = 4;
                    }
                }
            }
        }
    }
}

/**
 * Original name: dm_w_ball_chack
 */
void dm_w_ball_chack(GameMapCell *map) {
    u32 row;

    for (row = 0; row < GAME_MAP_ROWS - 1; row++) {
        u32 column;

        for (column = 0; column < GAME_MAP_COLUMNS; column++) {
            if (map[GAME_MAP_GET_INDEX(row, column)].capsel_m_flg[0] != 0) {
                if (map[GAME_MAP_GET_INDEX(row, column)].capsel_m_g == 2) {
                    if (map[GAME_MAP_GET_INDEX(row, column + 1)].capsel_m_g != 3) {
                        map[GAME_MAP_GET_INDEX(row, column)].capsel_m_g = 4;
                    }
                } else if ((map[GAME_MAP_GET_INDEX(row, column)].capsel_m_g == 3) &&
                           (map[GAME_MAP_GET_INDEX(row, column - 1)].capsel_m_g != 2)) {
                    map[GAME_MAP_GET_INDEX(row, column)].capsel_m_g = 4;
                }
            }
        }
    }
}

/**
 * Original name: dm_black_up
 */
bool dm_black_up(struct_game_state_data *state, GameMapCell *map) {
    if (state->flg_retire && !state->flg_game_over) {
        state->erase_anime_count++;
        if (state->erase_anime_count >= 6U) {
            u8 temp;
            u8 column;

            state->erase_anime_count = 0;
            temp = ((state->black_up_count - 1) * GAME_MAP_COLUMNS);

            for (column = 0; column < GAME_MAP_COLUMNS; column++) {
                // hate this
                if ((map + temp + column)->capsel_m_flg[0] != 0) {
                    (map + temp + column)->capsel_m_p += 3;
                }
            }

            state->black_up_count--;
            if (state->black_up_count == 0) {
                state->flg_game_over = true;
                return true;
            }
        }
    }

    return false;
}

/**
 * Original name: dm_broken_set
 */
bool dm_broken_set(struct_game_state_data *state, GameMapCell *map) {
    struct_game_state_data_cap_attack_work work[ARRAY_COUNTU(state->cap_attack_work)];
    s32 pad[0x18] UNUSED;
    bool ret = false;
    u32 i;
    u32 j;

    if (state->cap_attack_work[0].unk_0 != 0) {
        if (state->chain_line_max < state->chain_line) {
            state->chain_line_max = state->chain_line;
        }

        state->chain_line = 0;
        state->chain_count = 0;
        state->erase_virus_count = 0;
        state->erase_virus_count_old = 0;

        for (i = 0; i < ARRAY_COUNTU(state->chain_color); i++) {
            state->chain_color[i] = 0;
        }

        for (i = 0, j = 7; i < 0x10; i += 2, j--) {
            u32 chack = state->cap_attack_work[0].unk_0 & (3 << i);

            if (chack != 0) {
                set_map(map, j, 1, 4, (chack >> i) - 1);
            }
        }

        dm_h_ball_chack(map);
        dm_w_ball_chack(map);
        set_down_flg(map);

        for (i = 0; i < ARRAY_COUNTU(state->cap_attack_work); i++) {
            work[i].unk_0 = state->cap_attack_work[i].unk_0;
            work[i].unk_2 = state->cap_attack_work[i].unk_2;
            state->cap_attack_work[i].unk_0 = 0;
            state->cap_attack_work[i].unk_2 = 0;
        }

        for (i = 0, j = 1; i < ARRAY_COUNTU(state->cap_attack_work) - 1; i++, j++) {
            state->cap_attack_work[i].unk_0 = work[j].unk_0;
            state->cap_attack_work[i].unk_2 = work[j].unk_2;
        }

        ret = true;
    }

    return ret;
}

typedef struct dm_calc_erase_score_pos_arg2 {
    /* 0x0 */ s32 x;
    /* 0x4 */ s32 y;
} dm_calc_erase_score_pos_arg2; // size = 0x8

/**
 * Original name: dm_calc_erase_score_pos
 */
void dm_calc_erase_score_pos(struct_game_state_data *state, GameMapCell *map, dm_calc_erase_score_pos_arg2 *pos) {
    s32 row;
    s32 count = 0;

    pos->x = pos->y = 0;

    for (row = 0; row < GAME_MAP_ROWS - 1; row++) {
        s32 column;

        for (column = 0; column < GAME_MAP_COLUMNS; column++) {
            GameMapCell *cell = &map[GAME_MAP_GET_INDEX_ALT(row, column)];

            if (cell->capsel_m_flg[2] != 0) {
                pos->x += cell->pos_m_x;
                pos->y += cell->pos_m_y;
                count++;
            }
        }
    }

    if (count > 0) {
        pos->x = pos->x * state->map_item_size / count;
        pos->y = pos->y * state->map_item_size / count;
    }
}

/**
 * Original name: dm_calc_capsel_pos
 */
bool dm_calc_capsel_pos(struct_game_state_data *state, s32 xx[2], s32 yy[2]) {
    struct_game_state_data_now_cap *n_cap = &state->now_cap;
    s32 var_t0;
    s32 what = 0x24;

#if 0
    struct_dm_game_main_c_984 * n_cap; // r29
    float aa; // f7
    float bb; // f6
    float ee; // f1
    float ff; // f30
    float ii; // f3
    int gg; // r1+0x8
    int hh; // r28
#endif

    if (n_cap->capsel_flg_0 == 0) {
        return false;
    }

    if (state->mode_now == dm_mode_throw) {
        f32 temp_ft3;
        f32 temp_ft2;
        f32 var_fa0;
        s32 var_a0;
        s32 var_s2;
        f32 a;
        f32 b;

        if (state->cap_def_speed == 0) {
            var_a0 = state->cap_speed_count >> 2;
        } else {
            var_a0 = state->cap_speed_count >> 1;
        }

        var_a0 = var_a0 % 4;
        var_a0 += 4;

        var_s2 = 0;
        if ((var_a0 == 5) || (var_a0 == 7)) {
            var_s2 = 5;
        }

        if (state->now_cap.pos_x[0] == state->now_cap.pos_x[1]) {
            if ((var_a0 == 4) || (var_a0 == 6)) {
                throw_rotate_capsel(&state->now_cap);
            }
        } else {
            if ((var_a0 == 5) || (var_a0 == 7)) {
                throw_rotate_capsel(&state->now_cap);
            }
        }

        if (state->cap_speed_count < (FlyingCnt[state->cap_def_speed] / 3)) {
            var_fa0 = (what / (FlyingCnt[state->cap_def_speed] / 3)) * state->cap_speed_count;
        } else if (state->cap_speed_count < ((FlyingCnt[state->cap_def_speed] / 3) * 2)) {
            var_fa0 = what;
        } else {
            var_fa0 = ((FlyingCnt[state->cap_def_speed] * 2) / 3);
            var_fa0 = state->cap_speed_count - var_fa0;
            var_fa0 = what - (2.0f * var_fa0);
        }

        temp_ft3 = state->map_x + state->map_item_size * n_cap->pos_x[0];
        temp_ft2 = state->map_y + state->map_item_size * (n_cap->pos_y[0] - 1);

        a = temp_ft3 + ((218.0f - temp_ft3) / (FlyingCnt[state->cap_def_speed] - 1)) *
                           (FlyingCnt[state->cap_def_speed] - state->cap_speed_count);
        b = temp_ft2 + ((52.0f - temp_ft2) / (FlyingCnt[state->cap_def_speed] - 1)) *
                           (FlyingCnt[state->cap_def_speed] - state->cap_speed_count);

        for (var_t0 = 0; var_t0 < 2; var_t0++) {
            xx[var_t0] = (u32)a + var_s2 + state->map_item_size * (n_cap->pos_x[var_t0] - 3);
            yy[var_t0] = (u32)b + var_s2 - (u16)(u32)var_fa0 + 1 + state->map_item_size * (n_cap->pos_y[var_t0] + 1);
        }
    } else if (n_cap->pos_y[0] <= 0) {
        for (var_t0 = 0; var_t0 < 2; var_t0++) {
            xx[var_t0] = state->map_x + state->map_item_size * n_cap->pos_x[var_t0];
            yy[var_t0] = state->map_y + state->map_item_size * n_cap->pos_y[var_t0] - 0xA;
        }
    } else {
        for (var_t0 = 0; var_t0 < 2; var_t0++) {
            xx[var_t0] = state->map_x + state->map_item_size * n_cap->pos_x[var_t0];
            yy[var_t0] = state->map_y + state->map_item_size * n_cap->pos_y[var_t0] + 1;
        }
    }

    return true;
}

/**
 * Original name: dm_draw_capsel_by_gfx
 */
void dm_draw_capsel_by_gfx(struct_game_state_data *state, s32 *xx, s32 *yy) {
    struct_game_state_data_now_cap *cap = &state->now_cap;
    s32 type;
    TiTexData *tex;
    TiTexData *pal;
    s32 i;

    gSPDisplayList(gGfxHead++, normal_texture_init_dl);

    if (state->map_item_size == 0xA) {
        type = 0;
    } else {
        type = 1;
    }

    tex = dm_game_get_capsel_tex(type);

    load_TexBlock_4b(tex->texs[TI_TEX_TEX], tex->info[TI_INFO_IDX_WIDTH], tex->info[TI_INFO_IDX_HEIGHT]);

    for (i = 0; i < 2; i++) {
        pal = dm_game_get_capsel_pal(type, cap->capsel_p[i]);
        load_TexPal(pal->texs[TI_TEX_TLUT]);
        draw_Tex(xx[i], yy[i], state->map_item_size, state->map_item_size, 0, cap->casel_g[i] * state->map_item_size);
    }
}

/**
 * Original name: dm_draw_capsel_by_cpu_tentative
 *
 * Draw the falling pill.
 *
 * Does this by drawing directly to the framebuffer instead of using the gfx microcode.
 */
void dm_draw_capsel_by_cpu_tentative(struct_game_state_data *state, s32 xx[2], s32 yy[2]) {
    struct_game_state_data_now_cap *cap = &state->now_cap;
    TiTexData *tex_data;
    s32 var_s1;
    s32 var_s5;

    if (state->map_item_size == 0xA) {
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

        if ((yy[var_s1] < 0) || ((yy[var_s1] + state->map_item_size) > SCREEN_HEIGHT)) {
            continue;
        }

        if ((xx[var_s1] < 0) || ((xx[var_s1] + state->map_item_size) > SCREEN_WIDTH)) {
            continue;
        }

        tex_data = dm_game_get_capsel_pal(var_s5, cap->capsel_p[var_s1]);
        tlut = tex_data->texs[TI_TEX_TLUT];

        tex_data = dm_game_get_capsel_tex(var_s5);

        ci4_texture = tex_data->texs[TI_TEX_TEX];
        ci4_texture += (cap->casel_g[var_s1] * state->map_item_size * tex_data->info[TI_INFO_IDX_WIDTH]) >> 1;

        temp_a3_2 = (tex_data->info[TI_INFO_IDX_WIDTH] - state->map_item_size) >> 1;

        fb = &gFramebuffers[gCurrentFramebufferIndex ^ 1][yy[var_s1] * SCREEN_WIDTH + xx[var_s1]];
        temp_t1 = SCREEN_WIDTH - state->map_item_size;

        for (var_t4 = 0; var_t4 < state->map_item_size; var_t4++) {
            s32 var_a2;

            for (var_a2 = 0; var_a2 < state->map_item_size; var_a2 += 2) {
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

/**
 * Original name: dm_game_heap_top
 */
void **dm_game_heap_top(void) {
    return &heapTop;
}

/**
 * Original name: get_virus_anime_state
 */
SAnimeState *get_virus_anime_state(s32 index) {
    struct_watchGame *ptr = watchGame;

    return &ptr->animeStates[index];
}

/**
 * Original name: get_virus_smog_state
 */
SAnimeSmog *get_virus_smog_state(s32 index) {
    struct_watchGame *ptr = watchGame;

    return &ptr->animeSmogs[index];
}

/**
 * Original name: dm_get_mtx_buf
 */
Mtx *dm_get_mtx_buf(void) {
    return gameGeom->mtxBuf[gfx_gtask_no];
}

/**
 * Original name: dm_get_vtx_buf
 */
Vtx *dm_get_vtx_buf(void) {
    return gameGeom->vtxBuf[gfx_gtask_no];
}

/**
 * Original name: effectAll_init
 */
void effectAll_init(void) {
    struct_watchGame *st = watchGame;
    s32 i;

    for (i = 0; i < evs_playcnt; i++) {
        st->effect_timer[i] = 0;
    }

    initEtcWork(st->gameEtcSeg, evs_playcnt);
}

/**
 * Original name: _effectX_init
 */
void _effectX_init(s32 playerNo, s32 timer) {
    watchGame->effect_timer[playerNo] = timer;
}

/**
 * Original name: effectWin_init
 */
void effectWin_init(s32 playerNo) {
    _effectX_init(playerNo, 0xB4);
}

/**
 * Original name: effectLose_init
 */
void effectLose_init(s32 playerNo) {
    _effectX_init(playerNo, 0xB4);
}

/**
 * Original name: effectDraw_init
 */
void effectDraw_init(s32 playerNo) {
    _effectX_init(playerNo, 0xB4);
}

/**
 * Original name: effectPause_init
 */
void effectPause_init(s32 playerNo) {
    _effectX_init(playerNo, 0xB4);
    init_pause_disp();
}

/**
 * Original name: effectGameOver_init
 */
void effectGameOver_init(s32 playerNo) {
    _effectX_init(playerNo, 0xB4);
}

/**
 * Original name: effectNextStage_init
 */
void effectNextStage_init(s32 playerNo) {
    _effectX_init(playerNo, 0xB4);
}

/**
 * Original name: effectRetire_init
 */
void effectRetire_init(s32 playerNo) {
    _effectX_init(playerNo, 0xB4);
}

/**
 * Original name: _effectX_calc
 */
bool _effectX_calc(s32 playerNo) {
    struct_watchGame *st = watchGame;

    if (st->effect_timer[playerNo] != 0) {
        st->effect_timer[playerNo] -= 1;
    }
    return st->effect_timer[playerNo] != 0;
}

/**
 * Original name: effectWin_calc
 */
bool effectWin_calc(s32 playerNo) {
    return _effectX_calc(playerNo);
}

/**
 * Original name: effectLose_calc
 */
bool effectLose_calc(s32 playerNo) {
    return _effectX_calc(playerNo);
}

/**
 * Original name: effectDraw_calc
 */
bool effectDraw_calc(s32 playerNo) {
    return _effectX_calc(playerNo);
}

/**
 * Original name: effectPause_calc
 */
bool effectPause_calc(s32 playerNo) {
    return _effectX_calc(playerNo);
}

/**
 * Original name: effectGameOver_calc
 */
bool effectGameOver_calc(s32 playerNo) {
    return _effectX_calc(playerNo);
}

/**
 * Original name: effectNextStage_calc
 */
bool effectNextStage_calc(s32 playerNo) {
    return _effectX_calc(playerNo);
}

/**
 * Original name: effectRetire_calc
 */
bool effectRetire_calc(s32 playerNo) {
    return _effectX_calc(playerNo);
}

/**
 * Original name: timeAttackResult_set
 */
void timeAttackResult_set(TimeAttackResult *st, s32 level, bool bonus, s32 time, s32 combo, s32 virus, u32 score) {
    st->level = level;
    st->bonus = bonus;
    st->flow = 0;
    st->frame = 0;
    st->time = time;
    st->scoreDelta = 0;
    st->combo = combo;
    st->virus = virus;
    st->score = score;
}

/**
 * Original name: timeAttackResult_init
 */
void timeAttackResult_init(TimeAttackResult *st) {
    timeAttackResult_set(st, 0, false, 0, 0, 0, 0);
    st->result = 0;
}

/**
 * Original name: timeAttackResult_isEnd
 */
bool timeAttackResult_isEnd(TimeAttackResult *st) {
    return st->flow == 0x63;
}

/**
 * Original name: timeAttackResult_update
 */
bool timeAttackResult_update(TimeAttackResult *st, bool se) {
    bool res = true;

    switch (st->flow) {
        case 0:
            if (st->frame >= 0x78) {
                st->flow = 0xA;
                st->frame = 0;
                st->cnt = 0;
            } else {
                st->frame++;
            }
            break;

        case 0xA:
            if (st->time == 0) {
                st->flow = 0x14;
                st->frame = 0;
            } else {
                s32 var_v0_2 = MIN(6, st->time);
                s32 var_a0_2;

                st->time -= var_v0_2;
                if (se) {
                    if (st->time == 0) {
                        dm_snd_play_in_game(SND_INDEX_78);
                    } else if (st->cnt % 10 == 0) {
                        dm_snd_play_in_game(SND_INDEX_63);
                    }
                }

                var_a0_2 = _n_1199[st->level];
                if (st->cnt >= 0xC8) {
                    var_a0_2 *= 3;
                } else if (st->cnt >= 0x64) {
                    var_a0_2 *= 2;
                }

                if (st->bonus) {
                    u32 var_v1 = st->score + var_a0_2;

                    var_v1 = MIN(9999900, var_v1);
                    st->score = var_v1;
                    st->scoreDelta += var_a0_2;
                }

                st->cnt++;
            }

            st->frame++;
            break;

        case 0x14:
            if (st->frame < 0x3C) {
                st->frame++;
            } else {
                st->flow = 0x63;
                st->frame = 0;
            }
            break;

        case 0x63:
            res = !timeAttackResult_isEnd(st);
            break;
    }

    return res;
}

/**
 * Original name: timeAttackResult_skip
 */
void timeAttackResult_skip(TimeAttackResult *st) {
    while (timeAttackResult_update(st, false)) {}
}

/**
 * Original name: timeAttackResult_result
 */
u32 timeAttackResult_result(TimeAttackResult *st, s32 level, bool bonus, u32 time, s32 combo, s32 virus, u32 score) {
    timeAttackResult_set(st, level, bonus, time, combo, virus, score);
    timeAttackResult_skip(st);
    st->result = st->score;
    timeAttackResult_set(st, level, bonus, time, combo, virus, score);
    return st->result;
}

const u8 _retryMenu_itemCount[] = {
    2, 3, 2, 3, 2, 3,
};

const f32 _big_virus_def_wait[] = {
    12.5f,
    10.0f,
    7.5f,
};

const f32 _big_virus_min_wait[3] = {
    5.0f,
    4.5f,
    4.0f,
};

const f32 _big_virus_max_wait[3] = {
    12.5f,
    10.0f,
    7.5f,
};

const Color_RGB8 _scoreNumsColor[] = {
    { 255, 255, 255 }, { 255, 255, 255 }, { 255, 255, 255 }, { 255, 255, 255 }, { 255, 255, 255 }, { 255, 255, 255 },
};

#include "dm_game_main.msg.inc"

s32 _n_1199[] = { 0xA, 0x14, 0x1E };
u8 D_800A7360[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x11, 0, 0, 0, 0x22, 0, 0, 0, 0x33,
};
u8 tbl_4589[] = { 0, 1, 2, 1 };
Color_RGBA8 col_4590[] = {
    { 255, 0, 80, 255 },
    { 255, 200, 0, 255 },
    { 100, 100, 255, 255 },
};

const s32 _posStP4StarX[4] = {
    0xCD,
    0xE6,
    0xFF,
    0x118,
};

const s32 _posStStar[2][2] = {
    { 0x80, 0x48 },
    { 0xAC, 0x48 },
};

const s32 RO_800B1D28[2] = { 0x27, 0x5F };

const s32 _posP2StarX[2] = { 0x80, 0xAC };

const s32 _posP2StarY[3][3] = {
    { 0x48, -1, -1 },
    { 0x50, 0x40, -1 },
    { 0x58, 0x48, 0x38 },
};

const s32 _posP4Bottle[4][2] = {
    { 16, 37 },
    { 88, 37 },
    { 160, 37 },
    { 232, 37 },
};

const s32 RO_800B1D7C[2] = { 4, 3 };

const s32 _posP4CharBase[4][2] = {
    { 0x10, 0xBA },
    { 0x58, 0xBA },
    { 0xA0, 0xBA },
    { 0xE8, 0xBA },
};
static_assert(ARRAY_COUNT(_posP4CharBase) == MAX_PLAYERS, "");

const s32 _posP4TeamStarX[3][2][3] = {
    { { 0x2D, -1, -1 }, { 0xBF, -1, -1 } },
    { { 0x22, 0x39, -1 }, { 0xB3, 0xCA, -1 } },
    { { 0x16, 0x2D, 0x44 }, { 0xA7, 0xBE, 0xD6 } },
};

const s32 _posP4CharStarX[3][4][3] = {
    { { 0x29, -1, -1 }, { 0x71, -1, -1 }, { 0xB9, -1, -1 }, { 0x101, -1, -1 } },
    { { 0x1E, 0x35, -1 }, { 0x66, 0x7D, -1 }, { 0xAE, 0xC5, -1 }, { 0xF6, 0x10D, -1 } },
    { { 0x12, 0x2A, 0x41 }, { 0x5A, 0x72, 0x89 }, { 0xA2, 0xBA, 0xD1 }, { 0xEA, 0x102, 0x119 } },
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

/**
 * Original name: scoreNums_init
 */
void scoreNums_init(ScoreNums *st) {
    s32 i;

    for (i = 0; i < ARRAY_COUNTU(st->numbers); i++) {
        st->numbers[i].pos[0] = 0;
        st->numbers[i].pos[1] = 0;
        st->numbers[i].number = 0;
        st->numbers[i].color = 0;
        st->numbers[i].time = 1.0f;
    }

    st->index = 0;
}

/**
 * Original name: scoreNums_update
 */
void scoreNums_update(ScoreNums *st) {
    f32 val = 1.0f / 40;
    s32 i;
    s32 var_s0;

    for (i = 0, var_s0 = st->index; i < ARRAY_COUNTU(st->numbers);
         var_s0 = (var_s0 + 1) % ARRAY_COUNTU(st->numbers), i++) {
        ScoreNumsNumbers *num = &st->numbers[var_s0];
        ScoreNumsNumbers *pre = &st->numbers[WrapI(0, ARRAY_COUNTU(st->numbers), var_s0 - 1)];

        if (pre->time > DOUBLE_LITERAL(0.2)) {
            num->time = MIN(1.0f, num->time + val);
        }
    }
}

/**
 * Original name: scoreNums_set
 */
void scoreNums_set(ScoreNums *st, u32 score, s32 erase, s32 x, s32 y) {
    s32 color = CLAMP(erase - 1, 0, 5);
    s32 column[16];
    s32 columns;
    s32 i;

    columns = 0;
    while (score != 0) {
        column[columns] = score % 10;
        score /= 10;
        columns++;
    }

    x -= (columns * 7 + 1) / 2;
    y -= 6;

    for (i = columns - 1; i >= 0; i--) {
        ScoreNumsNumbers *num = &st->numbers[st->index];

        num->pos[0] = x;
        num->pos[1] = y;
        num->number = column[i];
        num->color = color;
        num->time = 0.0f;
        st->index = WrapI(0, ARRAY_COUNT(st->numbers), st->index + 1);
        x += 7;
    }
}

/**
 * Original name: backup_game_state
 */
void backup_game_state(s32 bufNo) {
    struct_gameBackup *bak = gameBackup[bufNo];
    s32 i;

    bak->game = *watchGame;

    for (i = 0; i < ARRAY_COUNTU(bak->state); i++) {
        bak->state[i] = game_state_data[i];
    }

    for (i = 0; i < ARRAY_COUNTU(bak->map); i++) {
        s32 j;

        for (j = 0; j < ARRAY_COUNTU(game_map_data[i]); j++) {
            bak->map[i][j] = game_map_data[i][j];
        }
    }

    bak->highScore = evs_high_score;
    bak->gameTime = evs_game_time;
}

/**
 * Original name: resume_game_state
 */
void resume_game_state(s32 bufNo) {
    struct_gameBackup *bak = gameBackup[bufNo];
    s32 i;

    *watchGame = bak->game;

    for (i = 0; i < ARRAY_COUNTU(bak->state); i++) {
        game_state_data[i] = bak->state[i];
    }

    for (i = 0; i < ARRAY_COUNTU(bak->map); i++) {
        s32 j;

        for (j = 0; j < ARRAY_COUNTU(game_map_data[i]); j++) {
            game_map_data[i][j] = bak->map[i][j];
        }
    }

    evs_high_score = bak->highScore;
    evs_game_time = bak->gameTime;
}

/**
 * Original name: set_replay_state
 */
void set_replay_state(void) {
    struct_watchGame *st = watchGame;

    if (st->unk_000 == 0) {
        backup_game_state(1);
    }

    resume_game_state(0);
    st->unk_000 = 1;
}

/**
 * Original name: reset_replay_state
 */
void reset_replay_state(void) {
    struct_watchGame *watchGameRef = watchGame;

    if (watchGameRef->unk_000 != 0) {
        resume_game_state(1);
        watchGameRef->unk_000 = 0;
    }
}

/**
 * Original name: start_replay_proc
 */
void start_replay_proc(void) {
    if (watchGame->unk_000 != 0) {
        replay_play_init();
    } else {
        replay_record_init(evs_playcnt);
    }
}

/**
 * Original name: dm_warning_h_line_se
 */
void dm_warning_h_line_se(void) {
    struct_watchGame *watchGameP = watchGame;
    s32 var_a0 = 0;
    s32 i;

    for (i = 0; i < evs_playcnt; i++) {
        if (game_state_data[i].cnd_static == dm_cnd_wait) {
            if (game_state_data[i].warning_se_flag) {
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

void dm_play_count_down_se(void) {
    s32 i;

    if (evs_gamemode != GMD_TIME_ATTACK) {
        return;
    }

    for (i = 0; i < evs_playcnt; i++) {
        if (game_state_data[i].cnd_static == dm_cnd_wait) {
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

/**
 * Original name: black_color_1384
 */
const s32 black_color_1384[] = { 0, 3 };
static_assert(ARRAY_COUNT(black_color_1384) == 2, "indexed by bool");

/**
 * Original name: dm_capsel_down
 */
void dm_capsel_down(struct_game_state_data *gameStateData, GameMapCell *mapCells) {
    struct_watchGame *watchGameP = watchGame;
    struct_game_state_data_now_cap *temp_s2 = &gameStateData->now_cap;
    s32 var_s0_2;
    s32 var_s1_2;

    if (temp_s2->pos_y[0] > 0) {
        var_s0_2 = FallSpeed[gameStateData->cap_speed];
        if ((temp_s2->pos_y[0] < 4) && (temp_s2->pos_y[0] > 0)) {
            var_s0_2 += BonusWait[temp_s2->pos_y[0] - 1][gameStateData->cap_def_speed];
        }
        var_s1_2 = 0;
        if (get_map_info(mapCells, gameStateData->now_cap.pos_x[0], temp_s2->pos_y[0] + 1) != 0) {
            var_s1_2 = watchGameP->unk_898;
        }
        gameStateData->cap_speed_max = var_s0_2 + var_s1_2;
    } else {
        gameStateData->cap_speed_max = 30;
    }

    gameStateData->cap_speed_count = gameStateData->cap_speed_count + gameStateData->cap_speed_vec;
    if (gameStateData->cap_speed_count < gameStateData->cap_speed_max) {
        return;
    }

    gameStateData->cap_speed_count = 0;
    if (temp_s2->capsel_flg_0 == 0) {
        return;
    }

    if (temp_s2->pos_y[0] > 0) {
        if (temp_s2->pos_x[0] == temp_s2->pos_x[1]) {
            if (get_map_info(mapCells, temp_s2->pos_x[0], temp_s2->pos_y[0] + 1) != 0) {
                temp_s2->capsel_flg_1 = 0;
            }
        } else {
            for (var_s1_2 = 0; var_s1_2 < ARRAY_COUNTU(temp_s2->pos_x); var_s1_2++) {
                if (get_map_info(mapCells, temp_s2->pos_x[var_s1_2], temp_s2->pos_y[var_s1_2] + 1) != 0) {
                    temp_s2->capsel_flg_1 = 0;
                    break;
                }
            }
        }
    }

    for (var_s0_2 = 0; var_s0_2 < ARRAY_COUNTU(temp_s2->pos_y); var_s0_2++) {
        if (temp_s2->pos_y[var_s0_2] == 0x10) {
            temp_s2->capsel_flg_1 = 0;
            break;
        }
    }

    if (temp_s2->capsel_flg_1 != 0) {
        for (var_s0_2 = 0; var_s0_2 < ARRAY_COUNTU(temp_s2->pos_y); var_s0_2++) {
            if (temp_s2->pos_y[var_s0_2] < 0x10) {
                temp_s2->pos_y[var_s0_2]++;
            }
        }

        for (var_s0_2 = 0; var_s0_2 < ARRAY_COUNTU(temp_s2->pos_x); var_s0_2++) {
            if (get_map_info(mapCells, temp_s2->pos_x[var_s0_2], temp_s2->pos_y[var_s0_2]) != 0) {
                gameStateData->cnd_static = dm_cnd_game_over;
                gameStateData->next_cap.capsel_flg_0 = 0;
                temp_s2->capsel_flg_1 = 0;
                break;
            }
        }

        if (temp_s2->capsel_flg_1 != 0) {
            return;
        }
    }

    dm_snd_play_in_game(SND_INDEX_66);
    gameStateData->mode_now = dm_mode_down_wait;
    temp_s2->capsel_flg_0 = 0;

    for (var_s0_2 = 0; var_s0_2 < ARRAY_COUNTU(temp_s2->pos_y); var_s0_2++) {
        if (temp_s2->pos_y[var_s0_2] != 0) {
            set_map(mapCells, temp_s2->pos_x[var_s0_2], temp_s2->pos_y[var_s0_2], temp_s2->casel_g[var_s0_2],
                    temp_s2->capsel_p[var_s0_2] + black_color_1384[gameStateData->flg_game_over]);
        }
    }
}

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

s32 dm_set_attack_2p(struct_game_state_data *gameStateDataRef) {
    s32 temp_v0;
    s32 var_s0;
    s32 var_s2;
    s32 var_t1;
    struct_game_state_data *temp_s3;
    s32 var_a0;
    s32 i;

    if (gameStateDataRef->chain_line < 2U) {
        return 0;
    }

    temp_s3 = &game_state_data[gameStateDataRef->player_no ^ 1];

    var_a0 = MIN(4, gameStateDataRef->chain_line);

    for (i = 0; i < 1; i++) {
        if (temp_s3->cap_attack_work[i].unk_0 != 0) {
            var_s2 = 0;
            for (var_s0 = 0; var_s0 < 8; var_s0++) {
                if (temp_s3->cap_attack_work[i].unk_0 & (3 << (var_s0 << 1))) {
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

        temp_s3->cap_attack_work[i].unk_2 = gameStateDataRef->player_no;

        for (var_s0 = 0; var_s0 < 8; var_s0++) {
            if (!((var_s2 >> var_s0) & 1)) {
                continue;
            }

            while ((gameStateDataRef->chain_color[0] != 0) || (gameStateDataRef->chain_color[1] != 0) ||
                   (gameStateDataRef->chain_color[2] != 0)) {
                temp_v0 = random(3);
                if (gameStateDataRef->chain_color[temp_v0] != 0) {
                    gameStateDataRef->chain_color[temp_v0] -= 1;
                    temp_s3->cap_attack_work[i].unk_0 |= (temp_v0 + 1) << (var_s0 << 1);
                    break;
                }
            }
        }

        break;
    }

    return 1;
}

/**
 * Original name: attack_table_1531
 */
const char attack_table_1531[][3] = {
    { 3, 2, 1 },
    { 0, 3, 2 },
    { 1, 0, 3 },
    { 2, 1, 0 },
};
static_assert(ARRAY_COUNT(attack_table_1531) == MAX_PLAYERS, "");

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

    if (gameStateDataRef->chain_line < 2U) {
        return 0;
    }

    for (var_s6 = 0; var_s6 < 3U; var_s6++) {
        sp30[var_s6] = 0;
    }

    var_fp = 0;

    sp44 = 0;
    sp40 = 0;
    for (var_s6 = 0; var_s6 < 3; var_s6++) {
        if (!((gameStateDataRef->chain_color[3] >> var_s6) & 1)) {
            continue;
        }

        temp_s1 = &game_state_data[attack_table_1531[gameStateDataRef->player_no][var_s6]];
        if (temp_s1->team_no == gameStateDataRef->team_no) {
            if (temp_s1->flg_retire) {
                continue;
            }
            sp44 |= 1 << attack_table_1531[gameStateDataRef->player_no][var_s6];
        } else {
            if (temp_s1->flg_retire && ((temp_s1->cnd_training != dm_cnd_training) || !temp_s1->flg_training)) {
                continue;
            }
            sp40 |= 1 << attack_table_1531[gameStateDataRef->player_no][var_s6];
        }

        if (var_fp > 0) {
            continue;
        }

        var_fp = 4;
        if (gameStateDataRef->chain_line < 5U) {
            var_fp = (s32)gameStateDataRef->chain_line;
        }

        for (var_s0 = 0; var_s0 < ARRAY_COUNTU(watchGameP->unk_8DC[gameStateDataRef->team_no]); var_s0++) {
            if (var_fp >= 4) {
                break;
            }

            if (watchGameP->unk_8DC[gameStateDataRef->team_no][var_s0] != -1) {
                gameStateDataRef->chain_color[watchGameP->unk_8DC[gameStateDataRef->team_no][var_s0]]++;
                watchGameP->unk_8DC[gameStateDataRef->team_no][var_s0] = -1;
                var_fp++;
            }
        }

        for (var_s0 = 0; var_s0 < var_fp;) {
            if ((gameStateDataRef->chain_color[0] + gameStateDataRef->chain_color[1] +
                 gameStateDataRef->chain_color[2]) <= 0) {
                break;
            }
            temp_v0_3 = random(3);
            if (gameStateDataRef->chain_color[temp_v0_3] != 0) {
                gameStateDataRef->chain_color[temp_v0_3]--;
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

        add_attack_effect(gameStateDataRef->player_no, _posP4CharBase[gameStateDataRef->player_no][0],
                          _posP4CharBase[gameStateDataRef->player_no][1], _posP4CharBase[temp_s1->player_no][0],
                          _posP4CharBase[temp_s1->player_no][1]);

        for (var_s0 = 0; var_s0 < ARRAY_COUNTU(sp20); var_s0++) {
            sp20[var_s0] = sp30[var_s0];
        }

        for (var_s0 = 0; var_s0 < 0x10; var_s0++) {
            if (temp_s1->cap_attack_work[var_s0].unk_0 != 0) {
                continue;
            }

            var_a1_2 = func_80063844(var_fp);

            temp_s1->cap_attack_work[var_s0].unk_2 = gameStateDataRef->player_no;
            for (var_s1_2 = 0; var_s1_2 < 8; var_s1_2++) {
                if (!((var_a1_2 >> var_s1_2) & 1)) {
                    continue;
                }

                while ((sp20[0] + sp20[1] + sp20[2]) > 0) {
                    temp_v0_3 = random(3);
                    if (sp20[temp_v0_3] > 0) {
                        sp20[temp_v0_3]--;
                        temp_s1->cap_attack_work[var_s0].unk_0 |= (temp_v0_3 + 1) << (var_s1_2 * 2);
                        break;
                    }
                }
            }
        }
    }

    var_s0 = 0;

    for (var_s6 = 0; var_s6 < ARRAY_COUNT(watchGameP->unk_8DC[gameStateDataRef->team_no]); var_s6++) {
        if (watchGameP->unk_8DC[gameStateDataRef->team_no][var_s6] == -1) {
            continue;
        }

        watchGameP->unk_8DC[gameStateDataRef->team_no][var_s0] = watchGameP->unk_8DC[gameStateDataRef->team_no][var_s6];
        var_s0 += 1;
    }

    for (; var_s0 < ARRAY_COUNT(watchGameP->unk_8DC[gameStateDataRef->team_no]); var_s0++) {
        watchGameP->unk_8DC[gameStateDataRef->team_no][var_s0] = -1;
    }

    for (var_s6 = 0; var_s6 < 4; var_s6++) {
        if (!((sp44 >> var_s6) & 1)) {
            continue;
        }

        for (var_s0 = 0; var_s0 < 3U; var_s0++) {
            sp20[var_s0] = sp30[var_s0];
        }

        temp_v0_3 = 0;
        for (var_s0 = 0; var_s0 < ARRAY_COUNT(watchGameP->unk_8DC[gameStateDataRef->team_no]); var_s0++) {
            if (watchGameP->unk_8DC[gameStateDataRef->team_no][var_s0] != -1) {
                continue;
            }

            for (; temp_v0_3 < 3; temp_v0_3++) {
                if (sp20[temp_v0_3] > 0) {
                    sp20[temp_v0_3]--;
                    watchGameP->unk_8DC[gameStateDataRef->team_no][var_s0] = temp_v0_3;
                    break;
                }
            }
        }
    }

    return 1;
}

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

        visible_fall_point[i] = (ptr->mem_use_flg & 2) ? 1 : 0;
    }
}

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

        temp_a1->mem_use_flg &= ~2;
        if (visible_fall_point[i] != 0) {
            temp_a1->mem_use_flg |= 2;
        }
    }
}

void retryMenu_init(s32 arg0, s32 arg1) {
    struct_watchGame *watchGameP = watchGame;

    watchGameP->unk_348[arg0] = arg1;
    watchGameP->unk_358[arg0] = 0;
    watchGameP->unk_368[arg0] = ETC_PART_INDEX_GRAPHBIN_INVALID;

    switch (watchGameP->unk_348[arg0]) {
        case 2:
        case 3:
        case 4:
        case 5:
            watchGameP->unk_358[arg0]++;
            break;
    }
}

void func_8006417C(s32 arg0) {
    retryMenu_init(arg0, 0);
}

EtcPartIndex retryMenu_input(s32 arg0) {
    s32 direction = 0;
    SndIndex soundIndex = SND_INDEX_INVALID;
    EtcPartIndex ret = ETC_PART_INDEX_GRAPHBIN_INVALID;
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

void func_8006431C(s32 arg0, Gfx **gfxP) {
    struct_watchGame *watchGameP = watchGame;
    Gfx *gfx = *gfxP;

    if (watchGameP->unk_348[arg0] < 6) {
        if (watchGameP->unk_348[arg0] >= 2) {
            if ((evs_gamesel == ENUM_EVS_GAMESEL_1) && (evs_gamemode == GMD_TIME_ATTACK)) {
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
        if (mapCells[cellIndex].capsel_m_flg[0] == 0) {
            continue;
        }

        if (mapCells[cellIndex].capsel_m_flg[4] >= 0) {
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

            if (mapCells[sp48[var_s2]].capsel_m_flg[0] != 0) {
                sp28[mapCells[sp48[var_s2]].capsel_m_flg[3]] += 1;
            }
        }

        if ((sp28[0] != 0) && (sp28[1] != 0) && (sp28[2] != 0)) {
            continue;
        }

        do {
            temp_v0_2 = random(3);
        } while (sp28[temp_v0_2] != 0);

        set_virus(mapCells, col, GAME_MAP_ROWS, temp_v0_2, virus_anime_table[temp_v0_2][arg0->virus_anime]);
    }
}

bool bottom_up_bottle_items(GameMapCell *mapCells) {
    s32 i;
    bool ret = false;
    s32 column;
    GameMapCell *cell;
    s32 var;

    for (i = 0; i < GAME_MAP_COLUMNS; i++) {
        if (mapCells[i].capsel_m_flg[0] != 0) {
            ret = true;
        }
    }

    var = (GAME_MAP_ROWS - 1) * GAME_MAP_COLUMNS;
    for (i = 0, cell = &mapCells[GAME_MAP_GET_INDEX(1, 0)]; i < var; i++, cell++) {
        mapCells[i] = *cell;
        mapCells[i].pos_m_y--;
    }

    var += GAME_MAP_COLUMNS;
    for (column = 0; i < var; i++, column++) {
        bzero(&mapCells[i], sizeof(GameMapCell));
        mapCells[i].pos_m_x = column;
        mapCells[i].pos_m_y = 0x11;
    }

    return ret;
}

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

    if (evs_gamemode != GMD_TaiQ) {
        return;
    }

    if (arg0->chain_line < 2) {
        return;
    }

    watchGameP->unk_3C8 += (arg0->chain_line - 1) * 0.25;
    watchGameP->unk_3C8 = MIN(watchGameP->unk_3C8, _big_virus_max_wait[arg0->game_level]);

    var_a0 = _bonus_1884[0] * (arg0->erase_virus_count + arg0->chain_line);
    for (i = 1; i < arg0->chain_count; i++) {
        var_a0 += _bonus_1884[MIN(i, ARRAY_COUNTU(_bonus_1884) - 1)];
    }
    watchGameP->unk_410 += var_a0;
}

bool func_80064848(void) {
    s32 i;

    for (i = 0; i < evs_playcnt; i++) {
        u32 temp_v0 = game_state_data[i].cnd_static;

        if ((temp_v0 != 5) && (temp_v0 != 8) && (temp_v0 != 0xB)) {
            break;
        }
    }

    return (i ^ evs_playcnt) == 0;
}

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

void func_80064940(void *arg0 UNUSED) {
    struct_watchGame *watchGameP = watchGame;

    if (watchGameP->unk_3B0 != 0) {
        EepRomErr status = EepRom_WriteAll(dm_game_eep_write_callback, watchGameP);

        watchGameP->unk_3B0 = 0;
        EepRom_DumpErrMes(status);
    }
}

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

                if (game_state_ptr->cnd_static == dm_cnd_win) {
                    temp_arg5++;
                }

                dm_story_sort_set(evs_select_name_no[0], (s32)story_proc_no >= BGROMDATA_INDEX12, evs_story_level,
                                  game_state_ptr->game_score, evs_game_time, temp_arg5, evs_one_game_flg);
                watchGameP->unk_3B0 = 1;
            }
            break;

        case ENUM_EVS_GAMESEL_1:
            for (i = 0; i < 2; i++) {
                switch (evs_gamemode) {
                    case GMD_NORMAL:
                        dm_vsman_set(evs_select_name_no[i], watchGameP->unk_8AC[i], watchGameP->unk_8AC[i ^ 1]);
                        break;
                    case GMD_FLASH:
                        dm_vm_fl_set(evs_select_name_no[i], watchGameP->unk_8AC[i], watchGameP->unk_8AC[i ^ 1]);
                        break;
                    case GMD_TIME_ATTACK:
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
                    case GMD_NORMAL:
                        dm_vscom_set(evs_select_name_no[0], watchGameP->unk_8AC[0], watchGameP->unk_8AC[1]);
                        break;

                    case GMD_FLASH:
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
                struct_evs_mem_data_config *temp = &temp_a0->config;
                s32 var_s0_2 = evs_story_no;
                s32 temp_s1 = (s32)story_proc_no >= BGROMDATA_INDEX12;

                temp->st_st = CLAMP(var_s0_2 - 1, 0, 7);

                if (game_state_ptr->cnd_static == dm_cnd_win) {
                    if ((var_s0_2 == 9) && (game_state_ptr->game_retry == 0)) {
                        evs_secret_flg[temp_s1] = 1;
                    }
                    if (func_8006498C(evs_story_level, var_s0_2, game_state_ptr->game_retry)) {
                        var_s0_2++;
                    } else if (var_s0_2 == 9) {
                        var_s0_2++;
                    }
                }

                dm_story_sort_set(evs_select_name_no[0], temp_s1, evs_story_level, game_state_ptr->game_score,
                                  evs_game_time, var_s0_2, evs_one_game_flg);

                watchGameP->unk_3B0 = 1;
            }
            break;

        case ENUM_EVS_GAMESEL_0:
            switch (evs_gamemode) {
                case GMD_NORMAL:
                    var_s1_2 = game_state_ptr->virus_level;
                    if (game_state_ptr->cnd_static == dm_cnd_win) {
                        if (var_s1_2 >= 0x15) {
                            evs_level_21 = 1;
                        }
                        if (var_s1_2 < 0x63) {
                            var_s1_2++;
                        }
                    }

                    dm_level_sort_set(evs_select_name_no[0], game_state_ptr->cap_def_speed, game_state_ptr->game_score,
                                      var_s1_2);

                    evs_mem_data[evs_select_name_no[0]].config.p1_lv = MIN(0x15, var_s1_2);
                    break;

                case GMD_TaiQ:
                    dm_taiQ_sort_set(evs_select_name_no[0], game_state_ptr->game_level, game_state_ptr->game_score,
                                     evs_game_time);
                    break;

                case GMD_TIME_ATTACK:
                    dm_timeAt_sort_set(evs_select_name_no[0], game_state_ptr->game_level, game_state_ptr->game_score,
                                       evs_game_time, game_state_ptr->total_erase_count);
                    break;

                default:
                    break;
            }
            watchGameP->unk_3B0 = 1;
            break;

        default:
            break;
    }

    BgTasksManager_SendTask(func_80064940, NULL);
}

void dm_query_pause_player(struct_game_state_data *arg0) {
    struct_watchGame *watchGameP = watchGame;
    u16 btn = gControllerPressedButtons[main_joy[arg0->player_no]];

    if (watchGameP->unk_9C4 >= 0) {
        return;
    }

    switch (arg0->cnd_static) {
        case dm_cnd_wait:
        case dm_cnd_pause:
            break;

        case dm_cnd_lose:
            if (watchGameP->unk_000 == 0) {
                return;
            }

            if (arg0->cnd_now != dm_cnd_tr_chack) {
                return;
            }
            break;

        default:
            return;
    }

    if ((arg0->cnd_now != dm_cnd_init) && (arg0->player_type == PLAYERTYPE_0)) {
        if (watchGameP->unk_000 == 0) {
            if (btn & START_BUTTON) {
                watchGameP->unk_9C0 = 1;
                watchGameP->unk_9C4 = arg0->player_no;
            }
        } else if (btn & ANY_BUTTON) {
            watchGameP->unk_9C4 = arg0->player_no;
        }
    }
}

// TODO: enum return type?
s32 dm_game_main_cnt_1P(struct_game_state_data *gameStateData, GameMapCell *mapCells, s32 arg2) {
    struct_watchGame *watchGameP = watchGame;
    dm_calc_erase_score_pos_arg2 sp28;
    s32 var_s1;
    u8 *var_t2;
    s32 var_s2;
    int var_s0;

    dm_query_pause_player(gameStateData);
    animeState_update(&gameStateData->anime);
    scoreNums_update(&watchGameP->unk_0B8[arg2]);
    if ((evs_gamemode == GMD_TIME_ATTACK) && (evs_game_time >= 10800) && (gameStateData->cnd_static == dm_cnd_wait)) {
        return -1;
    }

    switch (gameStateData->mode_now) {
        case dm_mode_init:
            dm_set_virus(gameStateData, mapCells, virus_map_data[arg2], virus_map_disp_order[arg2]);
            return 3;

        case dm_mode_wait:
            return 3;

        case dm_mode_throw:
            gameStateData->cap_speed_count++;

            if (gameStateData->cap_speed_count == FlyingCnt[gameStateData->cap_def_speed]) {
                dm_init_capsel_go(&gameStateData->now_cap, (CapsMagazine[gameStateData->cap_magazine_save] >> 4) % 3,
                                  CapsMagazine[gameStateData->cap_magazine_save] % 3);
                gameStateData->mode_now = dm_mode_down;
                gameStateData->cap_speed_count = 30;
                dm_capsel_down(gameStateData, mapCells);
            }
            break;

        case dm_mode_down_wait:
            if (dm_check_game_over(gameStateData, mapCells)) {
                for (var_s0 = 0; var_s0 < 3; var_s0++) {
                    if (watchGameP->animeStates[var_s0].animeSeq.animeNo != ANIMENO_4) {
                        animeState_set(&watchGameP->animeStates[var_s0], ANIMENO_3);
                    }
                }

                if (evs_gamemode == GMD_TaiQ) {
                    watchGameP->unk_410 = 0;
                }
                return -1;
            }

            if (dm_h_erase_chack(mapCells) || dm_w_erase_chack(mapCells)) {
                gameStateData->mode_now = dm_mode_erase_chack;
                gameStateData->cap_speed_count = 0;
            } else {
                gameStateData->mode_now = dm_mode_cap_set;
            }
            break;

        case dm_mode_erase_chack:
            gameStateData->cap_speed_count++;

            if (gameStateData->cap_speed_count >= 18) {
                gameStateData->cap_speed_count = 0;
                gameStateData->mode_now = dm_mode_erase_anime;
                dm_h_erase_chack_set(gameStateData, mapCells);
                dm_w_erase_chack_set(gameStateData, mapCells);
                dm_h_ball_chack(mapCells);
                dm_w_ball_chack(mapCells);

                var_s0 = gameStateData->virus_number;
                var_s0 -= get_virus_color_count(mapCells, watchGameP->unk_418, &watchGameP->unk_418[1],
                                                &watchGameP->unk_418[2]);
                gameStateData->virus_number -= var_s0;

                gameStateData->total_erase_count += var_s0;

                for (var_s0 = 0; var_s0 < 3; var_s0++) {
                    if (watchGameP->unk_418[var_s0] == 0) {
                        if (watchGameP->unk_400[var_s0] == 0) {
                            watchGameP->unk_400[var_s0] = 1;
                            animeState_set(&watchGameP->animeStates[var_s0], ANIMENO_4);
                            animeSmog_start(&watchGameP->animeSmogs[var_s0]);
                            if (gameStateData->virus_number != 0) {
                                dm_snd_play_in_game(SND_INDEX_74);
                                dm_snd_play_in_game(SND_INDEX_57);
                            }
                        }
                    } else {
                        if (gameStateData->chain_color[3] & (0x10 << var_s0)) {
                            if (watchGameP->unk_410 == 0) {
                                animeState_set(&watchGameP->animeStates[var_s0], ANIMENO_2);
                                dm_snd_play_in_game(SND_INDEX_74);
                            }
                        }
                    }
                }

                gameStateData->chain_color[3] &= 0xF;

                dm_calc_erase_score_pos(gameStateData, mapCells, &sp28);
                scoreNums_set(&watchGameP->unk_0B8[arg2], dm_make_score(gameStateData),
                              gameStateData->erase_virus_count,
                              gameStateData->map_x + gameStateData->map_item_size / 2 + sp28.x,
                              gameStateData->map_y + gameStateData->map_item_size / 2 + sp28.y);

                if ((gameStateData->virus_number == 0) && (evs_gamemode != GMD_TaiQ)) {
                    gameStateData->cnd_now = dm_cnd_stage_clear;
                    gameStateData->mode_now = dm_mode_stage_clear;
                    if (gameStateData->chain_line_max < gameStateData->chain_line) {
                        gameStateData->chain_line_max = gameStateData->chain_line;
                    }
                    return 6;
                }

                if ((gameStateData->virus_number < 4U) && (evs_gamemode != GMD_TaiQ)) {
                    if (watchGameP->unk_3C0 == 0) {
                        watchGameP->unk_3C0 = 1;
                        dm_snd_play_in_game(SND_INDEX_80);
                    }
                    if (watchGameP->unk_3B4 == 0) {
                        watchGameP->unk_3B4 = 1;
                        watchGameP->unk_3B8 = 1;
                    }
                }

                gameStateData->chain_count++;
                if (gameStateData->chain_line < 2) {
                    if (gameStateData->chain_color[3] & 8) {
                        gameStateData->chain_color[3] &= (u8)~0x8;
                        dm_snd_play_in_game(SND_INDEX_56);
                    } else {
                        dm_snd_play_in_game(SND_INDEX_61);
                    }
                } else {
                    if (gameStateData->chain_color[3] & 8) {
                        gameStateData->chain_color[3] &= (u8)~0x8;
                    }

                    var_s0 = MIN(2, gameStateData->chain_line - 2);
                    dm_snd_play_in_game(_charSE_tbl[gameStateData->charNo] + var_s0);
                }
            }
            break;

        case dm_mode_erase_anime:
            dm_capsel_erase_anime(gameStateData, mapCells);
            break;

        case dm_mode_ball_down:
            go_down(gameStateData, mapCells, 0xE);
            break;

        case dm_mode_cap_set:
            add_taiQ_bonus_wait(gameStateData);

            if ((watchGameP->unk_9BC != 0) && (watchGameP->unk_410 == 0)) {
                gameStateData->bottom_up_scroll = 0;
                gameStateData->mode_now = dm_mode_bottom_up;
                set_bottom_up_virus(gameStateData, mapCells);
                dm_snd_play_in_game(SND_INDEX_101);
            } else {
                if (gameStateData->chain_count > 1) {
                    gameStateData->total_chain_count =
                        MIN(99, gameStateData->total_chain_count + gameStateData->chain_count - 1);
                }

                dm_warning_h_line(gameStateData, mapCells);
                dm_set_capsel(gameStateData);
                dm_capsel_speed_up(gameStateData);
                dm_attack_se(gameStateData, arg2);
                animeState_set(&gameStateData->anime, ANIMENO_1);

                if ((gameStateData->player_type == PLAYERTYPE_1) ||
                    (((gameStateData->player_type != PLAYERTYPE_1) && (arg2 == 0)) && (aiDebugP1 >= 0))) {
                    aifMakeFlagSet(gameStateData);
                }

                if (gameStateData->chain_line_max < gameStateData->chain_line) {
                    gameStateData->chain_line_max = gameStateData->chain_line;
                }

                gameStateData->mode_now = dm_mode_throw;
                gameStateData->cap_speed_count = 0;
                gameStateData->cap_speed_max = 0;
                gameStateData->chain_line = 0;
                gameStateData->chain_count = 0;
                gameStateData->erase_virus_count = 0;
                gameStateData->erase_virus_count_old = 0;

                for (var_s0 = 0; var_s0 < ARRAY_COUNT(gameStateData->chain_color); var_s0++) {
                    gameStateData->chain_color[var_s0] = 0;
                }
            }
            break;

        case dm_mode_bottom_up:
            gameStateData->bottom_up_scroll++;
            if (gameStateData->bottom_up_scroll >= gameStateData->map_item_size) {
                gameStateData->bottom_up_scroll = 0;
                watchGameP->unk_9BC = 0;

                watchGameP->unk_3C8 =
                    MAX(_big_virus_min_wait[gameStateData->game_level], watchGameP->unk_3C8 - DOUBLE_LITERAL(0.5));

                gameStateData->mode_now = dm_mode_ball_down;
                if (bottom_up_bottle_items(mapCells)) {
                    return -1;
                }

                gameStateData->virus_number = get_virus_color_count(mapCells, watchGameP->unk_418,
                                                                    &watchGameP->unk_418[1], &watchGameP->unk_418[2]);

                for (var_s0 = 0; var_s0 < 3; var_s0++) {
                    if ((watchGameP->unk_418[var_s0] != 0) && (watchGameP->unk_400[var_s0] != 0)) {
                        animeState_set(&watchGameP->animeStates[var_s0], ANIMENO_0);
                        animeSmog_start(&watchGameP->animeSmogs[var_s0]);
                        watchGameP->unk_400[var_s0] = 0;
                    } else if (watchGameP->animeStates[var_s0].animeSeq.animeNo == ANIMENO_3) {
                        animeState_set(&watchGameP->animeStates[var_s0], ANIMENO_0);
                    }
                }
            }
            break;

        case dm_mode_clear_wait:
        case dm_mode_gover_wait:
            if (gameStateData->mode_now == dm_mode_clear_wait) {
                if (effectNextStage_calc(arg2)) {
                    break;
                }
            } else {
                if (effectGameOver_calc(arg2)) {
                    break;
                }
            }

            if (gControllerPressedButtons[main_joy[arg2]] & ANY_BUTTON) {
                switch (gameStateData->mode_now) {
                    case dm_mode_clear_wait:
                        gameStateData->cnd_now = dm_cnd_clear_result;
                        gameStateData->mode_now = dm_mode_clear_result;
                        break;

                    case dm_mode_gover_wait:
                        gameStateData->cnd_now = dm_cnd_gover_result;
                        gameStateData->mode_now = dm_mode_gover_result;
                        break;

                    default:
                        break;
                }
            }
            break;

        case dm_mode_clear_result:
        case dm_mode_gover_result:
            if (gControllerPressedButtons[main_joy[arg2]] & ANY_BUTTON) {
                timeAttackResult_skip(&watchGameP->unk_9D0[arg2]);
            }

            timeAttackResult_update(&watchGameP->unk_9D0[arg2], true);

            dm_add_score(gameStateData, watchGameP->unk_9D0[arg2].scoreDelta);
            watchGameP->unk_9D0[arg2].scoreDelta = 0;
            if (timeAttackResult_isEnd(&watchGameP->unk_9D0[arg2])) {
                switch (gameStateData->mode_now) {
                    case dm_mode_clear_result:
                        gameStateData->cnd_now = dm_cnd_stage_clear;
                        gameStateData->mode_now = dm_mode_stage_clear;
                        break;

                    case dm_mode_gover_result:
                        gameStateData->cnd_now = dm_cnd_game_over;
                        gameStateData->mode_now = dm_mode_game_over;
                        break;

                    default:
                        break;
                }
            }
            break;

        case dm_mode_stage_clear:
        case dm_mode_game_over:
            if (gameStateData->mode_now == dm_mode_stage_clear) {
                if (effectNextStage_calc(arg2)) {
                    break;
                }
            } else {
                if (effectGameOver_calc(arg2)) {
                    break;
                }
            }

            var_s0 = (Z_TRIG | L_JPAD | L_TRIG | R_TRIG);
            if ((watchGameP->unk_AA8 < 0) && CHECK_FLAG_ALL(gControllerHoldButtons[main_joy[0]], var_s0)) {
                switch (evs_gamemode) {
                    case GMD_NORMAL:
                        var_s1 = 0;
                        var_s2 = gameStateData->virus_level;
                        break;

                    case GMD_TIME_ATTACK:
                        var_s1 = 1;
                        var_s2 = gameStateData->game_level;
                        break;

                    case GMD_TaiQ:
                        var_s1 = 2;
                        var_s2 = gameStateData->game_level;
                        break;

                    default:
                        break;
                }

                if (evs_select_name_no[0] == 8) {
                    var_t2 = D_800A7360;
                } else {
                    var_t2 = evs_mem_data[evs_select_name_no[0]].mem_name;
                }

                if (watchGameP->password[0] == 0) {
                    func_8007E760(watchGameP->password, var_s1, var_s2, gameStateData->cap_def_speed,
                                  gameStateData->game_score / 10, evs_game_time / 6, var_t2);

                    // Write MSG_END
                    watchGameP->password[ARRAY_COUNT(watchGameP->password) - 2] = '~';
                    watchGameP->password[ARRAY_COUNT(watchGameP->password) - 1] = 'z';
                }
                msgWnd_clear(&watchGameP->unk_A28);
                msgWnd_addStr(&watchGameP->unk_A28, _mesPassword);
                msgWnd_addStr(&watchGameP->unk_A28, watchGameP->password);
                msgWnd_skip(&watchGameP->unk_A28);
                watchGameP->unk_AA8 = -watchGameP->unk_AA8;
            } else {
                if ((gControllerPressedButtons[main_joy[0]] != 0) && (watchGameP->unk_AA8 > 0)) {
                    watchGameP->unk_AA8 = -watchGameP->unk_AA8;
                }

                switch (retryMenu_input(arg2)) {
                    case ETC_PART_INDEX_GRAPHBIN_0:
                        set_replay_state();
                        dm_snd_play_in_game(SND_INDEX_62);
                        return 9;

                    case ETC_PART_INDEX_GRAPHBIN_1:
                        reset_replay_state();
                        dm_snd_play_in_game(SND_INDEX_62);
                        return 1;

                    case ETC_PART_INDEX_GRAPHBIN_2:
                        reset_replay_state();
                        if (gameStateData->game_retry < 0x3E7U) {
                            gameStateData->game_retry++;
                        }

                        if ((gameStateData->virus_level >= 0x16U) && (watchGameP->unk_378 > 0)) {
                            watchGameP->unk_378--;
                            dm_snd_play_in_game(SND_INDEX_78);
                        } else {
                            dm_snd_play_in_game(SND_INDEX_62);
                        }
                        return 2;

                    case ETC_PART_INDEX_GRAPHBIN_3:
                        dm_snd_play_in_game(SND_INDEX_62);
                        return 0x64;

                    default:
                        break;
                }
            }
            break;

        case dm_mode_pause_retry:
            switch (retryMenu_input(arg2)) {
                case ETC_PART_INDEX_GRAPHBIN_0:
                    if (watchGameP->unk_9C4 < 0) {
                        watchGameP->unk_9C4 = arg2;
                    }
                    dm_snd_play_in_game(SND_INDEX_62);
                    break;

                case ETC_PART_INDEX_GRAPHBIN_1:
                    if (gameStateData->game_retry < 0x3E7U) {
                        gameStateData->game_retry = gameStateData->game_retry + 1;
                    }

                    if ((gameStateData->virus_level >= 0x16U) && (watchGameP->unk_378 > 0)) {
                        watchGameP->unk_378--;
                        dm_snd_play_in_game(SND_INDEX_78);
                    } else {
                        dm_snd_play_in_game(SND_INDEX_62);
                    }
                    return 2;

                case ETC_PART_INDEX_GRAPHBIN_2:
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

// return enum?
s32 dm_game_main_cnt(struct_game_state_data *gameStateDataRef, GameMapCell *mapCells, s32 index) {
    struct_watchGame *temp_s1 = watchGame;
    dm_calc_erase_score_pos_arg2 sp20;
    s32 button = gControllerPressedButtons[main_joy[index]];
    s32 i;
    s32 j;
    bool var_s6;

    dm_query_pause_player(gameStateDataRef);

    animeState_update(&gameStateDataRef->anime);

    scoreNums_update(&temp_s1->unk_0B8[index]);

    if ((gameStateDataRef->cnd_static != dm_cnd_wait) && (gameStateDataRef->cnd_static != dm_cnd_pause)) {
        dm_black_up(gameStateDataRef, mapCells);
    }

    if ((evs_gamemode == GMD_TIME_ATTACK) && (evs_game_time >= 10800) &&
        (gameStateDataRef->cnd_static == dm_cnd_wait)) {
        return -1;
    }

    switch (gameStateDataRef->mode_now) {
        case dm_mode_init:
            dm_set_virus(gameStateDataRef, mapCells, virus_map_data[index], virus_map_disp_order[index]);
            return 3;

        case dm_mode_wait:
            return 3;

        case dm_mode_down_wait:
            if (dm_check_game_over(gameStateDataRef, mapCells)) {
                return -1;
            }

            if (dm_h_erase_chack(mapCells) || dm_w_erase_chack(mapCells)) {
                if (!gameStateDataRef->flg_game_over) {
                    gameStateDataRef->mode_now = dm_mode_erase_chack;
                } else {
                    gameStateDataRef->mode_now = dm_mode_tr_erase_chack;
                }

                gameStateDataRef->cap_speed_count = 0;
            } else if (!gameStateDataRef->flg_game_over) {
                gameStateDataRef->mode_now = dm_mode_cap_set;
            } else {
                gameStateDataRef->mode_now = dm_mode_tr_cap_set;
            }
            break;

        case dm_mode_erase_chack:
            gameStateDataRef->cap_speed_count++;
            if (gameStateDataRef->cap_speed_count >= 18) {
                s32 temp_s4_2;

                gameStateDataRef->mode_now = dm_mode_erase_anime;
                gameStateDataRef->cap_speed_count = 0;
                dm_h_erase_chack_set(gameStateDataRef, mapCells);
                dm_w_erase_chack_set(gameStateDataRef, mapCells);
                dm_h_ball_chack(mapCells);
                dm_w_ball_chack(mapCells);

                temp_s4_2 = gameStateDataRef->virus_number;
                temp_s4_2 -= dm_update_virus_count(gameStateDataRef, mapCells, true);
                gameStateDataRef->total_erase_count += temp_s4_2;

                dm_calc_erase_score_pos(gameStateDataRef, mapCells, &sp20);

                scoreNums_set(&temp_s1->unk_0B8[index], dm_make_score(gameStateDataRef),
                              gameStateDataRef->erase_virus_count,
                              gameStateDataRef->map_x + gameStateDataRef->map_item_size / 2 + sp20.x,
                              gameStateDataRef->map_y + gameStateDataRef->map_item_size / 2 + sp20.y);

                if (gameStateDataRef->virus_number == 0) {
                    if (gameStateDataRef->chain_line_max < gameStateDataRef->chain_line) {
                        gameStateDataRef->chain_line_max = gameStateDataRef->chain_line;
                    }
                    return 6;
                }
                if (temp_s1->unk_3BC >= gameStateDataRef->virus_number) {
                    if (temp_s1->unk_3C0 == 0) {
                        temp_s1->unk_3C0 = 1;
                        dm_snd_play_in_game(SND_INDEX_80);
                    }
                    if (temp_s1->unk_3B4 == 0) {
                        temp_s1->unk_3B4 = 1;
                        temp_s1->unk_3B8 = 1;
                    }
                }
                gameStateDataRef->chain_count++;

                switch (evs_gamesel) {
                    case ENUM_EVS_GAMESEL_1:
                    case ENUM_EVS_GAMESEL_3:
                    case ENUM_EVS_GAMESEL_5:
                        if (gameStateDataRef->chain_line < 2) {
                            if (gameStateDataRef->chain_color[3] & 8) {
                                gameStateDataRef->chain_color[3] &= ~8;
                                if ((evs_gamemode == GMD_FLASH) && (temp_s4_2 != 0)) {
                                    dm_snd_play_in_game(SND_INDEX_102);
                                } else {
                                    dm_snd_play_in_game(SND_INDEX_56);
                                }
                            } else {
                                dm_snd_play_in_game(SND_INDEX_61);
                            }
                        } else {
                            s32 temp_v0_3 = gameStateDataRef->chain_line - 2;

                            if (temp_v0_3 <= 2) {
                                j = temp_v0_3;
                            } else {
                                j = 2;
                            }

                            dm_snd_play_in_game(_charSE_tbl[gameStateDataRef->charNo] + j);

                            if (gameStateDataRef->chain_color[3] & 8) {
                                gameStateDataRef->chain_color[3] &= ~8;
                            }
                        }
                        break;

                    case ENUM_EVS_GAMESEL_2:
                    case ENUM_EVS_GAMESEL_6:
                        if (gameStateDataRef->chain_color[3] & 8) {
                            gameStateDataRef->chain_color[3] &= ~8;
                            if ((evs_gamemode == GMD_FLASH) && (temp_s4_2 != 0)) {
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

        case dm_mode_erase_anime:
            dm_capsel_erase_anime(gameStateDataRef, mapCells);
            break;

        case dm_mode_ball_down:
            go_down(gameStateDataRef, mapCells, 0xE);
            break;

        case dm_mode_cap_set:
            var_s6 = true;

            if (gameStateDataRef->chain_count > 1) {
                gameStateDataRef->total_chain_count =
                    MIN(99, gameStateDataRef->total_chain_count + gameStateDataRef->chain_count - 1);
            }

            dm_attack_se(gameStateDataRef, index);
            dm_warning_h_line(gameStateDataRef, mapCells);
            switch (evs_gamesel) {
                case ENUM_EVS_GAMESEL_1:
                case ENUM_EVS_GAMESEL_3:
                case ENUM_EVS_GAMESEL_5:
                    if (evs_gamemode != GMD_TIME_ATTACK) {
                        i = dm_set_attack_2p(gameStateDataRef);
                        if (i != 0) {
                            animeState_set(&gameStateDataRef->anime, ANIMENO_1);
                        }

                        if (dm_broken_set(gameStateDataRef, mapCells)) {
                            animeState_set(&gameStateDataRef->anime, ANIMENO_2);
                            var_s6 = false;
                            dm_snd_play_in_game(_charSE_tbl[gameStateDataRef->charNo] + 3);
                            gameStateDataRef->mode_now = dm_mode_ball_down;
                            if (gameStateDataRef->ai.aiState & 1) {
                                gameStateDataRef->ai.aiState |= 2;
                            } else {
                                gameStateDataRef->ai.aiState |= 1;
                            }
                        }
                    }
                    break;

                case ENUM_EVS_GAMESEL_2:
                case ENUM_EVS_GAMESEL_6:
                    i = dm_set_attack_4p(gameStateDataRef);
                    if (i != 0) {
                        animeState_set(&gameStateDataRef->anime, ANIMENO_1);
                    }

                    if (dm_broken_set(gameStateDataRef, mapCells)) {
                        animeState_set(&gameStateDataRef->anime, ANIMENO_2);
                        var_s6 = false;
                        gameStateDataRef->mode_now = dm_mode_ball_down;
                        if (gameStateDataRef->ai.aiState & 1) {
                            gameStateDataRef->ai.aiState |= 2;
                        } else {
                            gameStateDataRef->ai.aiState |= 1;
                        }
                    }
                    break;

                default:
                    break;
            }

            if (var_s6) {
                dm_set_capsel(gameStateDataRef);
                dm_capsel_speed_up(gameStateDataRef);
                if (gameStateDataRef->chain_line_max < gameStateDataRef->chain_line) {
                    gameStateDataRef->chain_line_max = gameStateDataRef->chain_line;
                }

                gameStateDataRef->chain_line = 0;
                gameStateDataRef->chain_count = 0;
                gameStateDataRef->erase_virus_count = 0;
                gameStateDataRef->erase_virus_count_old = 0;

                for (i = 0; i < ARRAY_COUNT(gameStateDataRef->chain_color); i++) {
                    gameStateDataRef->chain_color[i] = 0;
                }

                gameStateDataRef->mode_now = dm_mode_down;
                if ((gameStateDataRef->player_type == PLAYERTYPE_1) ||
                    (((gameStateDataRef->player_type != PLAYERTYPE_1) && (index == 0)) && (aiDebugP1 >= 0))) {
                    aifMakeFlagSet(gameStateDataRef);
                }
            }
            break;

        case dm_mode_clear_wait:
            effectNextStage_calc(index);
            break;

        case dm_mode_gover_wait:
            effectGameOver_calc(index);
            break;

        case dm_mode_retire_wait:
            effectRetire_calc(index);
            break;

        case dm_mode_clear_result:
        case dm_mode_gover_result:
        case dm_mode_retire_result:
            if (gControllerPressedButtons[main_joy[index]] & ANY_BUTTON) {
                timeAttackResult_skip(&temp_s1->unk_9D0[index]);
            }

            timeAttackResult_update(&temp_s1->unk_9D0[index], true);
            dm_add_score(gameStateDataRef, temp_s1->unk_9D0[index].scoreDelta);
            temp_s1->unk_9D0[index].scoreDelta = 0;
            break;

        case dm_mode_win_retry:
        case dm_mode_lose_retry:
        case dm_mode_draw_retry:
            if (gameStateDataRef->mode_now == dm_mode_win_retry) {
                if (effectWin_calc(index) != 0) {
                    break;
                }
            } else if (gameStateDataRef->mode_now == dm_mode_lose_retry) {
                if (effectLose_calc(index) != 0) {
                    break;
                }
            } else if (gameStateDataRef->mode_now == dm_mode_draw_retry) {
                if (effectDraw_calc(index) != 0) {
                    break;
                }
            }

            switch (retryMenu_input(index)) {
                case ETC_PART_INDEX_GRAPHBIN_0:
                    set_replay_state();
                    dm_snd_play_in_game(SND_INDEX_62);
                    return 9;

                case ETC_PART_INDEX_GRAPHBIN_1:
                    reset_replay_state();
                    dm_snd_play_in_game(SND_INDEX_62);
                    return 0x64;

                case ETC_PART_INDEX_GRAPHBIN_2:
                    reset_replay_state();
                    if (gameStateDataRef->game_retry < 999) {
                        gameStateDataRef->game_retry++;
                    }
                    dm_snd_play_in_game(SND_INDEX_62);
                    return 2;

                case ETC_PART_INDEX_GRAPHBIN_3:
                    dm_snd_play_in_game(SND_INDEX_62);
                    return -2;

                default:
                    break;
            }
            break;

        case dm_mode_win:
            effectWin_calc(index);
            break;

        case dm_mode_lose:
            effectLose_calc(index);
            break;

        case dm_mode_draw:
            effectDraw_calc(index);
            break;

        case dm_mode_tr_chaeck:
            if ((button & START_BUTTON) && (temp_s1->unk_000 == 0)) {
                return 7;
            }
            break;

        case dm_mode_training:
            gameStateDataRef->flg_game_over = true;
            clear_map_all(mapCells);
            gameStateDataRef->virus_number = 0;
            gameStateDataRef->virus_order_number = 0;
            gameStateDataRef->virus_anime_spead = 0xC;
            gameStateDataRef->warning_se_flag = false;
            gameStateDataRef->cap_speed = GameSpeed[gameStateDataRef->cap_def_speed];
            gameStateDataRef->cap_speed_max = 0;
            gameStateDataRef->cap_speed_vec = 1;
            gameStateDataRef->cap_magazine_cnt = 1;
            gameStateDataRef->cap_speed_count = 0;
            gameStateDataRef->cap_count = 0;
            dm_set_capsel(gameStateDataRef);
            gameStateDataRef->erase_anime = 0;
            gameStateDataRef->erase_anime_count = 0;
            gameStateDataRef->erase_virus_count = 0;
            gameStateDataRef->erase_virus_count_old = 0;
            gameStateDataRef->chain_line = 0;
            gameStateDataRef->chain_count = 0;

            for (i = 0; i < ARRAY_COUNT(gameStateDataRef->chain_color); i++) {
                gameStateDataRef->chain_color[i] = 0;
            }

            for (i = 0; i < ARRAY_COUNT(gameStateDataRef->cap_attack_work); i++) {
                gameStateDataRef->cap_attack_work[i].unk_0 = 0;
                gameStateDataRef->cap_attack_work[i].unk_2 = 0;
            }

            gameStateDataRef->mode_now = dm_mode_init;
            gameStateDataRef->cnd_now = dm_cnd_init;

            for (i = 0; i < ARRAY_COUNTU(virus_map_disp_order[index]); i++) {
                virus_map_disp_order[index][i] &= ~0x80;
            }

            for (i = 0; i < gameStateDataRef->flash_virus_count; i++) {
                gameStateDataRef->flash_virus_pos[i].color = gameStateDataRef->flash_virus_bak[i];
            }
            break;

        case dm_mode_tr_erase_chack:
            gameStateDataRef->cap_speed_count++;
            if (gameStateDataRef->cap_speed_count >= 18) {
                gameStateDataRef->cap_speed_count = 0;
                gameStateDataRef->mode_now = dm_mode_erase_anime;
                dm_h_erase_chack_set(gameStateDataRef, mapCells);
                dm_w_erase_chack_set(gameStateDataRef, mapCells);
                dm_h_ball_chack(mapCells);
                dm_w_ball_chack(mapCells);

                gameStateDataRef->chain_count++;
                dm_update_virus_count(gameStateDataRef, mapCells, true);

                if (gameStateDataRef->chain_color[3] & 8) {
                    gameStateDataRef->chain_color[3] &= ~8;
                    dm_snd_play_in_game(SND_INDEX_56);
                } else {
                    dm_snd_play_in_game(SND_INDEX_61);
                }
            }
            break;

        case dm_mode_tr_cap_set:
            dm_warning_h_line(gameStateDataRef, mapCells);

            var_s6 = true;
            if (gameStateDataRef->flg_training) {
                dm_attack_se(gameStateDataRef, index);
                dm_set_attack_4p(gameStateDataRef);
                animeState_set(&gameStateDataRef->anime, ANIMENO_1);
                if (dm_broken_set(gameStateDataRef, mapCells)) {
                    gameStateDataRef->mode_now = dm_mode_ball_down;
                    var_s6 = false;
                }
            } else {
                for (j = 0; j < 0x10; j++) {
                    gameStateDataRef->cap_attack_work[j].unk_0 = 0;
                    gameStateDataRef->cap_attack_work[j].unk_2 = 0;
                }
            }

            if (var_s6) {
                dm_set_capsel(gameStateDataRef);
                dm_capsel_speed_up(gameStateDataRef);
                gameStateDataRef->chain_line = 0;
                gameStateDataRef->chain_count = 0;
                gameStateDataRef->erase_virus_count = 0;
                gameStateDataRef->erase_virus_count_old = 0;

                for (i = 0; i < ARRAY_COUNT(gameStateDataRef->chain_color); i++) {
                    gameStateDataRef->chain_color[i] = 0;
                }
                gameStateDataRef->mode_now = dm_mode_down;
            }
            break;

        case dm_mode_pause_retry:
            switch (retryMenu_input(index)) {
                case ETC_PART_INDEX_GRAPHBIN_0:
                    if (temp_s1->unk_9C4 < 0) {
                        temp_s1->unk_9C4 = index;
                    }
                    dm_snd_play_in_game(SND_INDEX_62);
                    break;

                case ETC_PART_INDEX_GRAPHBIN_1:
                    if (gameStateDataRef->game_retry < 999) {
                        gameStateDataRef->game_retry++;
                    }
                    dm_snd_play_in_game(SND_INDEX_62);
                    return 2;

                case ETC_PART_INDEX_GRAPHBIN_2:
                    dm_snd_play_in_game(SND_INDEX_62);
                    return -2;

                default:
                    break;
            }
            break;

        default:
            break;
    }

    return 0;
}

void dm_set_pause_on(struct_game_state_data *gameStateData, s32 arg1) {
    struct_watchGame *temp_s3 = watchGame;
    s32 temp_s1 = gameStateData->player_no;

    effectPause_init(temp_s1);

    gameStateData->cnd_static = dm_cnd_pause;
    gameStateData->cnd_old = gameStateData->cnd_now;
    gameStateData->mode_old = gameStateData->mode_now;

    if (evs_gamesel == ENUM_EVS_GAMESEL_0) {
        gameStateData->mode_now = dm_mode_pause_retry;
        gameStateData->cnd_now = dm_cnd_pause_re;
        if ((gameStateData->virus_level < 0x16) || (temp_s3->unk_378 > 0)) {
            retryMenu_init(0, 1);
        } else {
            retryMenu_init(0, 0);
        }
    } else if (temp_s1 == arg1) {
        gameStateData->mode_now = dm_mode_pause_retry;
        gameStateData->cnd_now = dm_cnd_pause_re;
        if (evs_story_flg != 0) {
            gameStateData->cnd_now = dm_cnd_pause_re_sc;
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
        gameStateData->cnd_now = dm_cnd_pause;
        gameStateData->mode_now = dm_mode_pause;
    }
}

void func_80066808(struct_game_state_data *gameStateData) {
    gameStateData->cnd_static = dm_cnd_wait;
    gameStateData->cnd_now = gameStateData->cnd_old;
    gameStateData->mode_now = gameStateData->mode_old;
    if (gameStateData->mode_now == dm_mode_tr_chaeck) {
        gameStateData->cnd_static = dm_cnd_lose;
    }
}

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
    if (temp_a1->cnd_static == dm_cnd_wait) {
        dm_seq_set_volume(0x40);
        if (watchGameP->unk_000 == 0) {
            for (i = 0; i < arg1; i++) {
                dm_set_pause_on(gameStateDataP[i], var_s2);
            }
        } else {
            resume_game_state(1);
        }
        var_s2 = -1;
    } else if (temp_a1->cnd_static == dm_cnd_pause) {
        dm_seq_set_volume(0x80);
        for (i = 0; i < arg1; i++) {
            func_80066808(gameStateDataP[i]);
        }
        var_s2 = -1;
    } else if ((watchGameP->unk_000 != 0) && (temp_a1->cnd_now == dm_cnd_tr_chack)) {
        dm_seq_set_volume(0x40);
        resume_game_state(1);
    }

    if ((var_s2 < 0) && (var_s4 > SND_INDEX_INVALID)) {
        dm_snd_play_in_game(var_s4);
    }
}

void func_800669A0(struct_game_state_data *arg0) {
    struct_game_state_data *sp10 = arg0;

    dm_set_pause_and_volume(&sp10, 1);
}

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
        SAnimeState *temp = &watchGameP->animeStates[i];
        f32 var_fv0 = 1.0f;

        if ((temp->animeSeq.animeNo == ANIMENO_4) && (temp->frameCount >= 90)) {
            var_fv0 = -1.0f;
        }

        watchGameP->unk_3F4[i] = CLAMP(watchGameP->unk_3F4[i] + var_fv0 / DOUBLE_LITERAL(60), 0, 1);
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
            SAnimeState *temp = &watchGameP->animeStates[i];

            temp->primColor[0] = temp->primColor[1] = temp->primColor[2] = var_a2;
        }

        watchGameP->unk_414 += 1;
    } while (0);

    if (arg0->cnd_static != dm_cnd_wait) {
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
        SAnimeState *temp = &watchGameP->animeStates[i];

        switch ((s32)temp->animeSeq.animeNo) {
            case ANIMENO_4:
                if ((evs_gamemode != GMD_TaiQ) && !animeSeq_isEnd(&temp->animeSeq)) {
                    var_s1 += 1;
                }
                break;

            case ANIMENO_2:
                if (evs_gamemode != GMD_TaiQ) {
                    var_s1 += 1;
                }
                break;

            case ANIMENO_3:
                if (arg0->cnd_static != dm_cnd_wait) {
                    var_s1 += 1;
                }
                break;

            case ANIMENO_0:
            default:
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
                SAnimeState *temp = &watchGameP->animeStates[i];

                if (watchGameP->unk_400[i] == 0) {
                    if (var_s6 < watchGameP->unk_3E8[i]) {
                        var_s6 = watchGameP->unk_3E8[i];
                    }
                } else if (animeSeq_isEnd(&temp->animeSeq)) {
                    var_s5 += 1;
                }
            }

            if ((evs_gamemode == GMD_TaiQ) && (var_s5 == 3)) {
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
                if ((watchGameP->unk_400[i] == 0) && (evs_gamemode == GMD_TaiQ)) {
                    watchGameP->unk_9BC = 1;
                    watchGameP->unk_3CC = 0;
                    animeState_set(&watchGameP->animeStates[i], ANIMENO_3);
                }
            }
        }
    }

    for (i = 0; i < ARRAY_COUNT(watchGameP->unk_3E8); i++) {
        watchGameP->unk_3D0[i][0] = sinf(watchGameP->unk_3E8[i] * DOUBLE_LITERAL(PI_D) / 180) * 20.0f + 61.0f;
        watchGameP->unk_3D0[i][1] = cosf(watchGameP->unk_3E8[i] * DOUBLE_LITERAL(PI_D) / 180) * -20.0f + 171.0f;
    }
}

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
            if (gameStateData->mode_now == dm_mode_wait) {
                watchGameP->unk_3C4 = 1;
                gameStateData->mode_now = dm_mode_throw;
                animeState_set(&gameStateData->anime, ANIMENO_1);
                start_replay_proc();
            }
        }
    } else if (temp_s3 == 6) {
        s32 temp_s1;

        effectNextStage_init(gameStateData->player_no);
        dm_seq_play_in_game(SEQ_INDEX_14);
        watchGameP->unk_3C4 = 0;
        gameStateData->cnd_static = dm_cnd_win;

        switch (evs_gamemode) {
            case GMD_TIME_ATTACK: {
                //! FAKE
                s32 temp_v0;

                gameStateData->cnd_now = dm_cnd_clear_wait;
                gameStateData->mode_now = dm_mode_clear_wait;

                timeAttackResult_result(&watchGameP->unk_9D0[0], gameStateData->game_level, true,
                                        MAX(0, temp_v0 = 0x2A30 - evs_game_time), gameStateData->total_chain_count,
                                        gameStateData->total_erase_count, gameStateData->game_score);
            } break;

            default:
                gameStateData->cnd_now = dm_cnd_stage_clear;
                gameStateData->mode_now = dm_mode_stage_clear;
                break;
        }

        switch (evs_gamemode) {
            case GMD_TIME_ATTACK:
                retryMenu_init(0, 3);
                break;

            case GMD_NORMAL:
                retryMenu_init(0, 5);
                break;

            default:
                break;
        }

        animeState_set(&gameStateData->anime, ANIMENO_3);

        switch (evs_gamemode) {
            case GMD_TIME_ATTACK:
                temp_s1 = game_state_data[0].game_score;
                game_state_data[0].game_score = watchGameP->unk_9D0[0].result;
                dm_save_all();
                game_state_data[0].game_score = temp_s1;
                break;

            case GMD_NORMAL:
                dm_save_all();
                break;

            default:
                break;
        }
    } else if (temp_s3 == -1) {
        effectGameOver_init(gameStateData->player_no);
        animeState_set(&gameStateData->anime, ANIMENO_4);
        dm_seq_play_in_game(SEQ_INDEX_17);
        gameStateData->virus_anime_spead = 1;
        gameStateData->cnd_static = dm_cnd_lose;
        if (evs_gamemode == GMD_TIME_ATTACK) {
            gameStateData->cnd_now = dm_cnd_gover_wait;
            gameStateData->mode_now = dm_mode_gover_wait;

            timeAttackResult_result(&watchGameP->unk_9D0[0], gameStateData->game_level, false, 0,
                                    gameStateData->total_chain_count, gameStateData->total_erase_count,
                                    gameStateData->game_score);
            watchGameP->unk_3C4 = 0;
        } else {
            gameStateData->cnd_now = dm_cnd_game_over;
            gameStateData->mode_now = dm_mode_game_over;
            watchGameP->unk_3C4 = 0;
        }

        if ((gameStateData->virus_level < 0x16U) || ((watchGameP->unk_378 > 0))) {
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

s32 dm_add_win_2p(struct_game_state_data *gameStateDataRef) {
    struct_watchGame *watchGameP = watchGame;
    s32 temp_a3 = gameStateDataRef->player_no;
    SeqIndex var_t1 = SEQ_INDEX_17;
    s32 var_a3;
    s32 var_s0;
    s32 var_t3;

    watchGameP->unk_89C[temp_a3]++;

    if (evs_story_flg != 0) {
        var_t3 = _posStStar[temp_a3][0];
        var_a3 = _posStStar[temp_a3][1];

        var_s0 = 1;

        if (gameStateDataRef->player_type == PLAYERTYPE_0) {
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

        if ((evs_gamesel != ENUM_EVS_GAMESEL_3) || (gameStateDataRef->player_type == PLAYERTYPE_0)) {
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

s32 dm_set_win_2p(struct_game_state_data *gameStateDataRef, s32 arg1, s32 arg2) {
    s32 temp_s1 = gameStateDataRef->player_no;

    gameStateDataRef->cnd_static = dm_cnd_win;
    effectWin_init(temp_s1);
    animeState_set(&gameStateDataRef->anime, ANIMENO_3);
    dm_snd_play_in_game(_charSE_tbl[gameStateDataRef->charNo] + 4);

    if ((arg2 == 0) && (gameStateDataRef->player_type == PLAYERTYPE_0)) {
        arg2 = 1;

        gameStateDataRef->cnd_now = dm_cnd_win_retry;
        gameStateDataRef->mode_now = dm_mode_win_retry;
        if (evs_story_flg == 0) {
            if (arg1 != 0) {
                retryMenu_init(temp_s1, 3);
            } else {
                retryMenu_init(temp_s1, 5);
            }
        } else {
            gameStateDataRef->cnd_now = dm_cnd_win_retry_sc;
            retryMenu_init(temp_s1, 5);
        }
    } else {
        gameStateDataRef->cnd_now = dm_cnd_win;
        gameStateDataRef->mode_now = dm_mode_win;
    }

    return arg2;
}

s32 dm_set_lose_2p(struct_game_state_data *gameStateDataRef, s32 arg1, s32 arg2) {
    s32 temp_s1 = gameStateDataRef->player_no;

    gameStateDataRef->cnd_static = dm_cnd_lose;
    animeState_set(&gameStateDataRef->anime, ANIMENO_4);
    effectLose_init(temp_s1);

    if ((arg2 == 0) && (gameStateDataRef->player_type == PLAYERTYPE_0)) {
        arg2 = 1;

        gameStateDataRef->cnd_now = dm_cnd_lose_retry;
        gameStateDataRef->mode_now = dm_mode_lose_retry;

        if (evs_story_flg != 0) {
            gameStateDataRef->cnd_now = dm_cnd_lose_retry_sc;
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

        gameStateDataRef->cnd_now = dm_cnd_lose;
        gameStateDataRef->mode_now = dm_mode_lose;
    }

    return arg2;
}

s32 func_800675C8(struct_game_state_data *gameStateDataRef, s32 arg1) {
    s32 temp_s2 = gameStateDataRef->player_no;

    gameStateDataRef->cnd_static = dm_cnd_draw;
    effectDraw_init(temp_s2);
    animeState_set(&gameStateDataRef->anime, ANIMENO_4);
    if ((arg1 == 0) && (gameStateDataRef->player_type == PLAYERTYPE_0)) {
        arg1 = 1;

        gameStateDataRef->cnd_now = dm_cnd_draw_retry;
        gameStateDataRef->mode_now = dm_mode_draw_retry;
        retryMenu_init(temp_s2, 5);
    } else {
        gameStateDataRef->cnd_now = dm_cnd_draw;
        gameStateDataRef->mode_now = dm_mode_draw;
    }

    return arg1;
}

s32 dm_set_time_attack_result_2p(struct_game_state_data **gameStateDataRefP) {
    struct_watchGame *watchGameP = watchGame;
    u32 sp18[2];
    s32 i;
    s32 var_s5 = 0;
    s32 var_s3 = 0;

    sp18[0] = watchGameP->unk_9D0[0].result;
    sp18[1] = watchGameP->unk_9D0[1].result;

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
                if (sp28[i]->mode_now != dm_mode_wait) {
                    break;
                }
            }

            if (i == 2) {
                watchGameP->unk_3C4 = 1;

                for (i = 0; i < 2; i++) {
                    sp28[i]->mode_now = dm_mode_down;
                    if ((sp28[i]->player_type == 1) ||
                        ((sp28[i]->player_type != PLAYERTYPE_1) && (i == 0) && (aiDebugP1 >= 0))) {
                        aifMakeFlagSet(sp28[i]);
                    }
                }

                start_replay_proc();
            }
        }
    } else {
        for (i = 0; i < 2; i++) {
            if (sp38[i] == 0x6) {
                if (evs_gamemode == GMD_TIME_ATTACK) {
                    effectNextStage_init(i);

                    sp28[i]->mode_now = dm_mode_clear_wait;
                    sp28[i]->cnd_now = dm_cnd_clear_wait;
                    sp28[i]->cnd_static = dm_cnd_clear_wait;

                    timeAttackResult_result(&watchGameP->unk_9D0[i], sp28[i]->game_level, true,
                                            0 > 0x2A30 - (s32)evs_game_time ? 0 : 0x2A30 - evs_game_time,
                                            sp28[i]->total_chain_count, sp28[i]->total_erase_count,
                                            sp28[i]->game_score);
                    _dm_seq_play_in_game(1, SEQ_INDEX_16);
                } else {
                    var_fp += 1;
                    sp28[i]->cnd_static = dm_cnd_win;
                }
            } else if (sp38[i] == -0x1) {
                if (evs_gamemode == GMD_TIME_ATTACK) {
                    if (evs_game_time >= 0x2A30U) {
                        effectGameOver_init(i);
                        sp28[i]->mode_now = dm_mode_gover_wait;
                        sp28[i]->cnd_now = dm_cnd_gover_wait;
                        sp28[i]->cnd_static = dm_cnd_gover_wait;
                    } else {
                        effectRetire_init(i);
                        sp28[i]->mode_now = dm_mode_retire_wait;
                        sp28[i]->cnd_now = dm_cnd_retire_wait;
                        sp28[i]->cnd_static = dm_cnd_retire_wait;
                    }

                    timeAttackResult_result(&watchGameP->unk_9D0[i], sp28[i]->game_level, false, 0,
                                            sp28[i]->total_chain_count, sp28[i]->total_erase_count,
                                            sp28[i]->game_score);
                    _dm_seq_play_in_game(1, SEQ_INDEX_18);
                } else {
                    sp40 += 1;
                    sp28[i]->cnd_static = dm_cnd_lose;
                }

                sp28[i]->virus_anime_spead = 1;
                sp28[i]->black_up_count = 0x10;
                sp28[i]->flg_retire = true;
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
            switch (sp28[i]->cnd_now) {
                case dm_cnd_clear_wait:
                case dm_cnd_gover_wait:
                case dm_cnd_retire_wait:
                    if (watchGameP->effect_timer[i] == 0) {
                        var_s1_4 += 1;
                    }
                    break;

                case dm_cnd_clear_result:
                case dm_cnd_gover_result:
                case dm_cnd_retire_result:
                    if (timeAttackResult_isEnd(&watchGameP->unk_9D0[i])) {
                        var_s2_2 += 1;
                    }
                    break;

                default:
                    break;
            }
        }

        if (var_s1_4 == 2) {
            for (i = 0; i < 2; i++) {
                switch (sp28[i]->cnd_now) {
                    case dm_cnd_clear_wait:
                        sp28[i]->cnd_static = dm_cnd_clear_result;
                        sp28[i]->cnd_now = dm_cnd_clear_result;
                        sp28[i]->mode_now = dm_mode_clear_result;
                        break;

                    case dm_cnd_gover_wait:
                        sp28[i]->cnd_static = dm_cnd_gover_result;
                        sp28[i]->cnd_now = dm_cnd_gover_result;
                        sp28[i]->mode_now = dm_mode_gover_result;
                        break;

                    case dm_cnd_retire_wait:
                        sp28[i]->cnd_static = dm_cnd_retire_result;
                        sp28[i]->cnd_now = dm_cnd_retire_result;
                        sp28[i]->mode_now = dm_mode_retire_result;
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
                if (sp28[i]->cnd_static == dm_cnd_win) {
                    var_s6 = dm_add_win_2p(sp28[i]);
                }
            }

            for (i = 0; i < 2; i++) {
                if (sp28[i]->cnd_static == dm_cnd_win) {
                    var_s4 = dm_set_win_2p(sp28[i], var_s6, var_s4);
                }
            }

            for (i = 0; i < 2; i++) {
                if (sp28[i]->cnd_static != dm_cnd_win) {
                    var_s4 = dm_set_lose_2p(sp28[i], var_s6, var_s4);
                }
            }
        } else if (sp40 != 0) {

            for (i = 0; i < 2; i++) {
                if (sp28[i]->cnd_static != dm_cnd_lose) {
                    var_s6 = dm_add_win_2p(sp28[i]);
                }
            }

            for (i = 0; i < 2; i++) {
                if (sp28[i]->cnd_static != dm_cnd_lose) {
                    var_s4 = dm_set_win_2p(sp28[i], var_s6, var_s4);
                }
            }

            for (i = 0; i < 2; i++) {
                if (sp28[i]->cnd_static == dm_cnd_lose) {
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
    TeamNumber var_s6;
    s32 var_s7;

    s32 var_a1_3;
    s32 var_a1_4;

    s32 var_a2_2;
    TeamNumber temp_a2_2;
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
                if (sp18[var_s0]->mode_now != dm_mode_wait) {
                    break;
                }
            }

            if (var_s0 == 4) {
                temp_s4->unk_3C4 = 1;

                for (var_s0 = 0; var_s0 < 4; var_s0++) {
                    sp18[var_s0]->mode_now = dm_mode_down;
                    if ((sp18[var_s0]->player_type == PLAYERTYPE_1) ||
                        ((sp18[var_s0]->player_type != PLAYERTYPE_1) && (var_s0 == 0) && (aiDebugP1 >= 0))) {
                        aifMakeFlagSet(sp18[var_s0]);
                    }
                }
                start_replay_proc();
            }
        }

        return 0;
    }

    var_s2_2 = 0;
    var_s3_2 = 0;
    var_t4 = 0;
    var_t3 = 0;

    for (var_s0 = 0; var_s0 < 4; var_s0++) {
        if ((sp38[var_s0] == 3) && (sp18[var_s0]->cnd_training == dm_cnd_training)) {
            if (sp18[var_s0]->mode_now == dm_mode_wait) {
                sp18[var_s0]->mode_now = dm_mode_down;
            }
        } else if (sp38[var_s0] == 0x6) {
            var_t3 += 1;
            sp18[var_s0]->cnd_static = dm_cnd_win;
        } else if (sp38[var_s0] == -1) {
            if (!sp18[var_s0]->flg_retire) {
                sp18[var_s0]->cnd_now = dm_cnd_retire;
                sp18[var_s0]->cnd_training = dm_cnd_retire;
                sp18[var_s0]->cnd_static = dm_cnd_lose;
                sp18[var_s0]->black_up_count = 0x10;
                sp18[var_s0]->flg_retire = true;
                var_t4 += 1;
                if (sp18[var_s0]->player_type == PLAYERTYPE_1) {
                    sp18[var_s0]->mode_now = dm_mode_no_action;
                } else {
                    sp18[var_s0]->cnd_now = dm_cnd_tr_chack;
                    sp18[var_s0]->mode_now = dm_mode_tr_chaeck;
                }
            } else {
                sp18[var_s0]->cnd_now = dm_cnd_tr_chack;
                sp18[var_s0]->mode_now = dm_mode_tr_chaeck;
            }
            sp18[var_s0]->virus_anime_spead = 4;
        } else if (sp38[var_s0] == 2) {
            return 2;
        } else if (sp38[var_s0] == 0x9) {
            return 9;
        } else if (sp38[var_s0] == 0x64) {
            return -1;
        } else if (sp38[var_s0] == -2) {
            return -2;
        } else if (sp38[var_s0] == 7) {
            sp18[var_s0]->cnd_static = dm_cnd_wait;
            sp18[var_s0]->flg_training = false;
            sp18[var_s0]->cnd_training = dm_cnd_training;
            sp18[var_s0]->mode_now = dm_mode_training;
        } else if (sp38[var_s0] == 8) {
            sp18[var_s0]->cnd_static = dm_cnd_wait;
            sp18[var_s0]->flg_training = true;
            sp18[var_s0]->cnd_training = dm_cnd_training;
            sp18[var_s0]->mode_now = dm_mode_training;
        }
    }

    if (var_t3 != 0) {
        var_a1_3 = 0;

        for (var_s0 = 0; var_s0 < 4; var_s0++) {
            if (sp18[var_s0]->cnd_static == dm_cnd_win) {
                var_a1_3 |= 1 << var_s0;
                var_s6 = sp18[var_s0]->team_no;
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
                if (sp18[var_s0]->cnd_static != dm_cnd_win) {
                    continue;
                }

                temp_a2_2 = sp18[var_s0]->team_no;
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

                temp_s4->unk_06C++;

                temp_s4->unk_89C[temp_a2_2]++;
                if (evs_story_flg != 0) {
                    var_s3_2 = 1;
                } else if (temp_s4->unk_89C[temp_a2_2] == evs_vs_count) {
                    var_s3_2 = 1;
                    var_s5 = SEQ_INDEX_15;
                }
            }

            for (var_s0 = 0; var_s0 < ARRAY_COUNT(sp18); var_s0++) {
                if (sp18[var_s0]->team_no != var_s6) {
                    continue;
                }

                if ((evs_story_flg != 0) && (sp18[var_s0]->player_type == PLAYERTYPE_0)) {
                    var_s5 = SEQ_INDEX_14;
                }
                var_s2_2 = dm_set_win_2p(sp18[var_s0], var_s3_2, var_s2_2);
            }

            for (var_s0 = 0; var_s0 < ARRAY_COUNT(sp18); var_s0++) {
                if (sp18[var_s0]->team_no != var_s6) {
                    if ((evs_story_flg != 0) && (sp18[var_s0]->player_type == PLAYERTYPE_0)) {
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
            if (sp18[var_s0]->flg_retire) {
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
                if (!sp18[var_s0]->flg_retire) {
                    temp_a2_3 = sp18[var_s0]->team_no;
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
                        if (sp18[var_s0]->player_type != PLAYERTYPE_0) {
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
                if (sp18[var_s0]->team_no == var_s6) {
                    var_s2_2 = dm_set_win_2p(sp18[var_s0], var_s3_2, var_s2_2);
                }
            }

            for (var_s0 = 0; var_s0 < 4; var_s0++) {
                if (sp18[var_s0]->team_no != var_s6) {
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

bool dm_game_demo_1p(void) {
    struct_watchGame *watchGameP = watchGame;
    s32 temp_s4 = dm_game_main_cnt_1P(game_state_data, game_map_data[0], 0);
    s32 i;

    dm_warning_h_line_se();

    for (i = 0; i < 3; i++) {
        SAnimeState *animeState = &watchGameP->animeStates[i];
        SAnimeSmog *animeSmog = &watchGameP->animeSmogs[i];

        animeState_update(animeState);
        animeSmog_update(animeSmog);
    }

    dm_calc_big_virus_pos(game_state_data);

    if ((temp_s4 == 3) && (watchGameP->unk_3AC < 0)) {
        game_state_data[0].mode_now = dm_mode_throw;
        animeState_set(&game_state_data[0].anime, ANIMENO_1);
        if ((game_state_data[0].player_type == PLAYERTYPE_1) || (aiDebugP1 >= 0)) {
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
            game_state_data[i].mode_now = dm_mode_down;

            if (((&game_state_data[i])->player_type == PLAYERTYPE_1) ||
                (((&game_state_data[i])->player_type != PLAYERTYPE_1) && (i == 0) && (aiDebugP1 >= 0))) {
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
            game_state_data[i].mode_now = dm_mode_down;

            if (((&game_state_data[i])->player_type == PLAYERTYPE_1) ||
                ((((&game_state_data[i])->player_type != PLAYERTYPE_1) && (i == 0)) && (aiDebugP1 >= 0))) {
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

const s32 cap_tex_4162[2] = { 8, 2 };

TiTexData *dm_game_get_capsel_tex(s32 arg0) {
    return &watchGame->unk_444[cap_tex_4162[arg0]];
}

const u32 cap_pal_4164[][6] = {
    { 8, 10, 6, 9, 11, 7 },
    { 2, 4, 0, 3, 5, 1 },
};

TiTexData *dm_game_get_capsel_pal(s32 arg0, s32 arg1) {
    return &watchGame->unk_444[cap_pal_4164[arg0][arg1]];
}

void scoreNums_draw(ScoreNums *arg0, Gfx **gfxP) {
    struct_watchGame *watchGameP = watchGame;
    Gfx *gfx = *gfxP;
    TiTexData *temp_s4 = &watchGameP->unk_430[0x11];
    TiTexData *temp_s2 = &watchGameP->unk_430[0x16];
    s32 var_s3 = MIN(temp_s4->info[TI_INFO_IDX_WIDTH], temp_s2->info[TI_INFO_IDX_WIDTH]);
    s32 temp_s0 = temp_s4->info[TI_INFO_IDX_HEIGHT] / 12;
    s32 i;

    gSPDisplayList(gfx++, alpha_texture_init_dl);

    gDPSetCombineLERP(gfx++, TEXEL0, 0, PRIMITIVE, 0, TEXEL1, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED);

    for (i = 0; i < 8U; i++) {
        ScoreNumsNumbers *temp_t3 = &arg0->numbers[WrapI(0, 8, arg0->index + i)];
        f32 temp_ft0 = temp_t3->time;
        f32 var_fv0_2;
        s32 alpha;

        if (temp_ft0 == DOUBLE_LITERAL(1.0)) {
            continue;
        }

        if (temp_ft0 < DOUBLE_LITERAL(0.2)) {
            alpha = temp_ft0 * 1275.0f;
        } else if (temp_ft0 < DOUBLE_LITERAL(0.8)) {
            alpha = 255;
        } else {
            alpha = (1.0f - temp_ft0) * 1275.0f;
        }

        if (temp_ft0 > DOUBLE_LITERAL(0.5)) {
            var_fv0_2 = 1.0f;
        } else {
            var_fv0_2 = temp_ft0 * DOUBLE_LITERAL(4) - DOUBLE_LITERAL(1);
        }

        var_fv0_2 = (DOUBLE_LITERAL(1) - var_fv0_2 * var_fv0_2) * DOUBLE_LITERAL(8);

        gDPSetPrimColor(gfx++, 0, 0, _scoreNumsColor[temp_t3->color].r, _scoreNumsColor[temp_t3->color].g,
                        _scoreNumsColor[temp_t3->color].b, alpha);

        StretchAlphaTexBlock(
            &gfx, var_s3, temp_s0,
            (u16 *)temp_s4->texs[TI_TEX_TEX] + temp_s4->info[TI_INFO_IDX_WIDTH] * temp_s0 * temp_t3->number,
            temp_s4->info[TI_INFO_IDX_WIDTH],
            (u8 *)temp_s2->texs[TI_TEX_TEX] + (temp_s2->info[TI_INFO_IDX_WIDTH] * temp_s0 * temp_t3->number / 2),
            temp_s2->info[TI_INFO_IDX_WIDTH], temp_t3->pos[0], temp_t3->pos[1] - var_fv0_2, var_s3, temp_s0);
    }

    *gfxP = gfx;
}

void func_80069160(struct_watchGame_unk_070 *arg0, UNK_TYPE *arg1, UNK_TYPE *arg2) {
    s32 i;

    arg0->unk_00 = arg1;
    arg0->unk_04 = arg2;

    for (i = 0; i < ARRAY_COUNTU(arg0->unk_08); i++) {
        arg0->unk_08[i] = 0;
    }
}

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

            tiStretchAlphaTexItem(&gfx, temp_s0, temp_s5, false, 0x10, 0, arg0->unk_00[i], arg0->unk_04[i],
                                  temp_s0->info[TI_INFO_IDX_WIDTH], temp_s0->info[TI_INFO_IDX_HEIGHT] >> 4);
        }

        var_a3 = MIN(255, arg0->unk_08[i] * 8);

        gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, var_a3);

        var_a3 = MAX(0, arg0->unk_08[i] - 0x30) >> 2;
        tiStretchAlphaTexItem(&gfx, temp_s0, temp_s5, false, 0x10, var_a3 + 1, arg0->unk_00[i], arg0->unk_04[i],
                              temp_s0->info[TI_INFO_IDX_WIDTH], temp_s0->info[TI_INFO_IDX_HEIGHT] >> 4);
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
        StretchTexTile4i(&gfx, temp_s0->info[TI_INFO_IDX_WIDTH], temp_s0->info[TI_INFO_IDX_HEIGHT],
                         temp_s0->texs[TI_TEX_TEX], 0, 0, temp_s0->info[TI_INFO_IDX_WIDTH],
                         temp_s0->info[TI_INFO_IDX_HEIGHT], arg0->unk_00[i], arg0->unk_04[i],
                         temp_s0->info[TI_INFO_IDX_WIDTH], temp_s0->info[TI_INFO_IDX_HEIGHT]);
    }

    *gfxP = gfx;
}

void func_800695A8(Gfx **gfxP, s32 arg1, s32 arg2, bool cached) {
    struct_watchGame *watchGameP = watchGame;
    Gfx *gfx = *gfxP;
    TiTexData *temp_a1 = &watchGameP->unk_430[0x10];
    TiTexData *temp = &watchGameP->unk_430[0x15];

    if (!cached) {
        gSPDisplayList(gfx++, alpha_texture_init_dl);
    }
    tiStretchAlphaTexItem(&gfx, temp_a1, temp, cached, 0x10, 0, arg1, arg2, temp_a1->info[TI_INFO_IDX_WIDTH],
                          temp_a1->info[TI_INFO_IDX_HEIGHT] >> 4);

    *gfxP = gfx;
}

const u8 _tbl_4274[4][4] = { { 0, 5, 8, 0xA }, { 0, 1, 6, 9 }, { 0, 1, 2, 4 }, { 0, 1, 2, 3 } };

void draw_4p_attack_guide_panel(Gfx **gfxP, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    struct_watchGame *watchGameP = watchGame;
    Gfx *gfx = *gfxP;
    TiTexData *temp_t1;
    TiTexData *temp;
    s32 var_a1;

    gSPDisplayList(gfx++, normal_texture_init_dl);

    temp_t1 = &watchGameP->unk_440[9];
    tiStretchTexItem(&gfx, temp_t1, 0, 4, arg2, arg3, arg4, temp_t1->info[TI_INFO_IDX_WIDTH],
                     temp_t1->info[TI_INFO_IDX_HEIGHT] / 4);

    gSPDisplayList(gfx++, alpha_texture_init_dl);

    for (var_a1 = 0; var_a1 < 3; var_a1++) {
        f32 temp_fs0 = arg3 + 0x24;
        f32 temp_fv1 = arg4 + 5 + var_a1 * 0xD;
        TeamNumber temp_a2 = game_state_data[arg2].team_no;
        TeamNumber temp2 = game_state_data[(arg2 + 1 + var_a1) % 4].team_no;

        if (temp_a2 == temp2) {
            temp_t1 = &watchGameP->unk_440[temp_a2 + 0x10];
            temp = &watchGameP->unk_440[0x18];
            StretchAlphaTexBlock(&gfx, temp_t1->info[TI_INFO_IDX_WIDTH], temp_t1->info[TI_INFO_IDX_HEIGHT],
                                 temp_t1->texs[TI_TEX_TEX], temp_t1->info[TI_INFO_IDX_WIDTH], temp->texs[TI_TEX_TEX],
                                 temp->info[TI_INFO_IDX_WIDTH], temp_fs0, temp_fv1 + 1.0f,
                                 temp_t1->info[TI_INFO_IDX_WIDTH], temp_t1->info[TI_INFO_IDX_HEIGHT]);
        } else {
            s32 temp3;

            temp_t1 = &watchGameP->unk_440[0xA];
            temp = &watchGameP->unk_440[0x12];

            temp3 = _tbl_4274[arg1 - 1][(arg2 + var_a1 + 1) % ARRAY_COUNT(_tbl_4274[0])];
            tiStretchAlphaTexItem(&gfx, temp_t1, temp, false, 0xB, temp3, temp_fs0, temp_fv1,
                                  temp_t1->info[TI_INFO_IDX_WIDTH], temp_t1->info[TI_INFO_IDX_HEIGHT] / 11);
        }
    }

    *gfxP = gfx;
}

void dm_map_draw(GameMapCell *mapCells, u8 arg1, s16 arg2, s16 arg3, s8 arg4) {
    s32 i;

    for (i = 0; i < GAME_MAP_ROWS * GAME_MAP_COLUMNS; i++) {
        GameMapCell *cell = &mapCells[i];

        if ((cell->capsel_m_flg[0] != 0) && (cell->capsel_m_p == arg1)) {

            gSPTextureRectangle(gGfxHead++, (cell->pos_m_x * arg4 + arg2) << 2, ((cell->pos_m_y * arg4) + arg3) << 2,
                                (cell->pos_m_x * arg4 + arg2 + arg4) << 2, (cell->pos_m_y * arg4 + arg3 + arg4) << 2,
                                G_TX_RENDERTILE, 0, (cell->capsel_m_g * arg4) << 5, 1 << 10, 1 << 10);
        }
    }
}

void func_80069ACC(GameMapCell *mapCells, struct_game_state_data_now_cap *arg1, s32 arg2[2]) {
    s32 var_s3 = 0x10;
    s32 i;
    int row;

    for (i = 0; i < 2; i++) {
        row = MAX(1, arg1->pos_y[i]);

        for (; row < GAME_MAP_ROWS; row++) {
            if (get_map_info(mapCells, arg1->pos_x[i], row) != 0) {
                var_s3 = MIN(var_s3, row - 1);
                break;
            }
        }
    }

    arg2[0] = var_s3 - (arg1->pos_y[0] < arg1->pos_y[1] ? 1 : 0);
    arg2[1] = var_s3 - (arg1->pos_y[0] > arg1->pos_y[1] ? 1 : 0);
}

const char _tbl_4345[] = { 9, 0, 1, 2, 3, 4, 5, 6, 7, 8 };

void draw_virus_number(Gfx **gfxP, u32 arg1, s32 arg2, s32 arg3, f32 arg4, f32 arg5 UNUSED) {
    struct_watchGame *watchGameP = watchGame;
    TiTexData *temp_s5 = &watchGameP->unk_430[0xD];
    TiTexData *temp_s3 = &watchGameP->unk_430[0x12];
    s32 var_t1 = 0;
    s32 var_s6 = MIN(temp_s5->info[TI_INFO_IDX_WIDTH], temp_s3->info[TI_INFO_IDX_WIDTH]);
    s32 temp_s1 = temp_s5->info[TI_INFO_IDX_HEIGHT] / 10;
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
            gfxP, var_s6, temp_s1,
            temp_s5->texs[TI_TEX_TEX] + (temp_s5->info[TI_INFO_IDX_WIDTH] * temp_s1 * _tbl_4345[sp38[var_s0]] * 2),
            temp_s5->info[TI_INFO_IDX_WIDTH],
            temp_s3->texs[TI_TEX_TEX] + (temp_s3->info[TI_INFO_IDX_WIDTH] * temp_s1 * _tbl_4345[sp38[var_s0]]) / 2,
            temp_s3->info[TI_INFO_IDX_WIDTH], arg2 + (var_s4 * arg4), arg3 + temp_fs0 * arg4, var_s6 * arg4,
            temp_s1 * arg4);
        var_s4 += 0xE;
    }
}

const s32 _tex_4374[] = { 3, 4, 5 };
const s32 _row_4375[] = { 0xD, 0xC, 0xC };

void draw_count_number(Gfx **gfxP, s32 arg1, s32 arg2, u32 arg3, s32 arg4, s32 arg5) {
    struct_watchGame *watchGameP = watchGame;
    TiTexData *temp_a1 = watchGameP->unk_438;
    TiTexData *temp_s5 = &temp_a1[_tex_4374[arg1]];
    TiTexData *temp_s2 = &temp_a1[7];
    s32 var_s7 = MIN(temp_s5->info[TI_INFO_IDX_WIDTH], temp_s2->info[TI_INFO_IDX_WIDTH]);
    s32 temp_s6 = temp_s5->info[TI_INFO_IDX_HEIGHT] / _row_4375[arg1];
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
        StretchAlphaTexBlock(gfxP, var_s7, temp_s6,
                             temp_s5->texs[TI_TEX_TEX] + temp_s5->info[TI_INFO_IDX_WIDTH] * temp_s6 * sp38[i] * 2,
                             temp_s5->info[TI_INFO_IDX_WIDTH],
                             temp_s2->texs[TI_TEX_TEX] + temp_s2->info[TI_INFO_IDX_WIDTH] * temp_s6 * sp38[i] / 2,
                             temp_s2->info[TI_INFO_IDX_WIDTH], arg4, arg5, var_s7, temp_s6);
        arg4 += 9;
    }
}

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

void push_any_key_draw(s32 arg0, s32 arg1) {
    struct_watchGame *watchGameP = watchGame;
    s32 alpha;
    s32 var_a1_2;
    TiTexData *temp_a3;
    TiTexData *temp1;
    TiTexData *temp2;

    alpha = sins((watchGameP->unk_424 << 10) & 0xFC00) * ((f32)0xFF / 0x8000) + 0x7F;
    alpha = CLAMP(alpha, 0, 255);

    gSPDisplayList(gGfxHead++, alpha_texture_init_dl);
    gDPSetCombineLERP(gGfxHead++, TEXEL0, 0, PRIMITIVE, 0, TEXEL1, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0,
                      COMBINED);
    gDPSetPrimColor(gGfxHead++, 0, 0, 255, 255, 255, alpha);

    temp_a3 = watchGameP->unk_430;
    temp1 = &temp_a3[0x17];
    temp2 = &temp_a3[0x18];

    var_a1_2 = MIN(temp1->info[TI_INFO_IDX_WIDTH], temp2->info[TI_INFO_IDX_WIDTH]);

    StretchAlphaTexTile(&gGfxHead, var_a1_2, temp1->info[TI_INFO_IDX_HEIGHT], temp1->texs[TI_TEX_TEX],
                        temp1->info[TI_INFO_IDX_WIDTH], temp2->texs[TI_TEX_TEX], temp2->info[TI_INFO_IDX_WIDTH], 0, 0,
                        var_a1_2, temp1->info[TI_INFO_IDX_HEIGHT], arg0, arg1, var_a1_2,
                        temp1->info[TI_INFO_IDX_HEIGHT]);
}

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

        var_a3 = MIN(temp_t0->info[TI_INFO_IDX_WIDTH], temp_t2->info[TI_INFO_IDX_WIDTH]);
        var_t1 = MIN(temp_t0->info[TI_INFO_IDX_HEIGHT], temp_t2->info[TI_INFO_IDX_HEIGHT]);

        gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, alpha[i]);
        StretchAlphaTexTile(&gfx, var_a3, var_t1, temp_t0->texs[TI_TEX_TEX], temp_t0->info[TI_INFO_IDX_WIDTH],
                            temp_t2->texs[TI_TEX_TEX], temp_t2->info[TI_INFO_IDX_WIDTH], 0, 0, var_a3, var_t1, arg1,
                            arg2, var_a3, var_t1);
    }

    *gfxP = gfx;
}

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
        s32 var_t2 = MIN(temp_t0->info[TI_INFO_IDX_WIDTH], temp_t3->info[TI_INFO_IDX_WIDTH]);
        s32 var_t1 = MIN(temp_t0->info[TI_INFO_IDX_HEIGHT], temp_t3->info[TI_INFO_IDX_HEIGHT]);

        gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, alpha[i]);
        StretchAlphaTexTile(&gfx, var_t2, var_t1, temp_t0->texs[TI_TEX_TEX], temp_t0->info[TI_INFO_IDX_WIDTH],
                            temp_t3->texs[TI_TEX_TEX], temp_t3->info[TI_INFO_IDX_WIDTH], 0, 0, var_t2, var_t1, arg1,
                            arg2, var_t2, var_t1);
    }

    *gfxP = gfx;
}

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

    temp_s5 = temp_s2->info[TI_INFO_IDX_WIDTH] >> 2;
    for (i = 0; i < arg1; i++) {
        f32 var_s4 = 0xED + i * 0x10;
        f32 temp_ft0 = watchGameP->unk_9A0[i] - 0xF;
        s32 alpha;

        temp_ft0 = SQ(temp_ft0) * DOUBLE_LITERAL(0.125) + DOUBLE_LITERAL(81) - DOUBLE_LITERAL(28.125);
        alpha = 255 - watchGameP->unk_9A0[i] * 0xFF / 30;

        gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, alpha);

        StretchTexTile4(&gfx, temp_s2->info[TI_INFO_IDX_WIDTH], temp_s2->info[TI_INFO_IDX_HEIGHT],
                        temp_s2->texs[TI_TEX_TLUT], temp_s2->texs[TI_TEX_TEX],
                        temp_s5 * ((watchGameP->unk_9A0[i] >> 1) & 3), 0, temp_s5, temp_s2->info[TI_INFO_IDX_HEIGHT],
                        var_s4, temp_ft0, temp_s5, temp_s2->info[TI_INFO_IDX_HEIGHT]);
    }

    *gfxP = gfx;
}

void draw_flash_virus_light(Gfx **gfxP, bool cached, s32 arg2, s32 arg3, s32 arg4) {
    struct_watchGame *watchGameP = watchGame;
    Gfx *gfx = *gfxP;
    TiTexData *ti = &watchGameP->unk_444[tbl_4589[(watchGameP->unk_424 >> 1) % ARRAY_COUNTU(tbl_4589)] + 0xC];

    if (!cached) {
        gSPDisplayList(gfx++, normal_texture_init_dl);
        gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
        gDPSetCombineLERP(gfx++, ENVIRONMENT, PRIMITIVE, TEXEL0, PRIMITIVE, ENVIRONMENT, 0, TEXEL0, 0, ENVIRONMENT,
                          PRIMITIVE, TEXEL0, PRIMITIVE, ENVIRONMENT, 0, TEXEL0, 0);
        gDPSetTextureLUT(gfx++, G_TT_NONE);
        gDPSetEnvColor(gfx++, 255, 255, 255, 255);
    }

    gDPSetPrimColor(gfx++, 0, 0, col_4590[arg4].r, col_4590[arg4].g, col_4590[arg4].b, col_4590[arg4].a);

    tiStretchTexBlock(&gfx, ti, cached, arg2, arg3, 20.0f, 20.0f);
    *gfxP = gfx;
}

void draw_flash_virus_lights(Gfx **gfxP, struct_game_state_data *gameStateDataRef, GameMapCell *mapCells UNUSED) {
    bool cached = false;
    s32 var_s5;
    s32 var_s6;
    s32 i;

    switch (gameStateDataRef->map_item_size) {
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

    for (i = 0; i < gameStateDataRef->flash_virus_count; i++) {
        if (gameStateDataRef->flash_virus_pos[i].color < 0) {
            continue;
        }

        draw_flash_virus_light(gfxP, cached,
                               var_s5 + gameStateDataRef->map_x +
                                   (gameStateDataRef->map_item_size * gameStateDataRef->flash_virus_pos[i].column),
                               var_s6 + gameStateDataRef->map_y +
                                   (gameStateDataRef->map_item_size * (gameStateDataRef->flash_virus_pos[i].row + 1)),
                               gameStateDataRef->flash_virus_pos[i].color);
        cached = true;
    }
}

void func_8006AEFC(TimeAttackResult *arg0, Gfx **gfxP, s32 arg2, s32 arg3) {
    struct_watchGame *watchGameP = watchGame;
    Gfx *gfx = *gfxP;
    TiTexData *temp_t3;
    TiTexData *temp;

    gSPDisplayList(gfx++, alpha_texture_init_dl);

    temp_t3 = &watchGameP->unk_438[8];
    temp = &watchGameP->unk_438[9];

    StretchAlphaTexTile(&gfx, temp_t3->info[TI_INFO_IDX_WIDTH], (s32)temp_t3->info[TI_INFO_IDX_HEIGHT],
                        temp_t3->texs[TI_TEX_TEX], temp_t3->info[TI_INFO_IDX_WIDTH], temp->texs[TI_TEX_TEX],
                        (s32)temp->info[TI_INFO_IDX_WIDTH], 0, 0, (s32)temp_t3->info[TI_INFO_IDX_WIDTH],
                        (s32)temp_t3->info[TI_INFO_IDX_HEIGHT], (f32)arg2, (f32)arg3,
                        (f32)temp_t3->info[TI_INFO_IDX_WIDTH], (f32)temp_t3->info[TI_INFO_IDX_HEIGHT]);
    draw_time2(&gfx, arg0->time + 5, arg2 + 0x12, arg3 + 0xE);
    draw_count_number(&gfx, 0, 2, arg0->combo, arg2 + 0x1F, arg3 + 0x23);
    draw_count_number(&gfx, 0, 2, arg0->virus, arg2 + 0x1F, arg3 + 0x38);
    draw_count_number(&gfx, 0, 7, arg0->score, arg2 + 9, arg3 + 0x50);

    *gfxP = gfx;
}

void draw_story_board(Gfx **gfxP, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    struct_watchGame *temp_s1 = watchGame;
    Gfx *gfx = *gfxP;

    gSPDisplayList(gfx++, alpha_texture_init_dl);

    if (arg3 != 0) {
        TiTexData *temp_t3 = &temp_s1->unk_43C[0x12];
        TiTexData *temp_t1 = &temp_s1->unk_43C[0x13];

        StretchAlphaTexBlock(&gfx, temp_t3->info[TI_INFO_IDX_WIDTH], temp_t1->info[TI_INFO_IDX_HEIGHT],
                             temp_t3->texs[TI_TEX_TEX], temp_t3->info[TI_INFO_IDX_WIDTH], temp_t1->texs[TI_TEX_TEX],
                             temp_t1->info[TI_INFO_IDX_WIDTH], arg1 + 0x78, arg2 + 0xB,
                             temp_t3->info[TI_INFO_IDX_WIDTH], temp_t3->info[TI_INFO_IDX_HEIGHT]);

        temp_t3 = &temp_s1->unk_43C[9];
        tiStretchAlphaTexItem(&gfx, temp_t3, &temp_s1->unk_43C[2], false, 4, evs_story_level, arg1 + 0x8E, arg2 + 0x36,
                              temp_t3->info[TI_INFO_IDX_WIDTH], temp_t3->info[TI_INFO_IDX_HEIGHT] >> 2);
    }

    if (arg4 != 0) {
        draw_count_number(&gfx, 0, 7, game_state_data->game_score, arg1 + 0x81, arg2 + 0x19);
    }

    *gfxP = gfx;
}

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
            case GMD_FLASH:
            case GMD_TIME_ATTACK:
                temp_s1 = &temp_s6->unk_43C[0x10];
                temp_s5 = &temp_s6->unk_43C[0x11];
                StretchAlphaTexBlock(&gfx, temp_s1->info[TI_INFO_IDX_WIDTH], temp_s1->info[TI_INFO_IDX_HEIGHT],
                                     temp_s1->texs[TI_TEX_TEX], temp_s1->info[TI_INFO_IDX_WIDTH],
                                     temp_s5->texs[TI_TEX_TEX], temp_s5->info[TI_INFO_IDX_WIDTH], arg1 + 0x5F, arg2 + 9,
                                     temp_s1->info[TI_INFO_IDX_WIDTH], temp_s1->info[TI_INFO_IDX_HEIGHT]);

                temp_s1 = &temp_s6->unk_43C[9];
                temp_s5 = &temp_s6->unk_43C[2];
                for (i = 0; i < 2; i++) {
                    tiStretchAlphaTexItem(&gfx, temp_s1, temp_s5, false, 4, game_state_data[i].game_level,
                                          arg1 + _x_4663[i], arg2 + 0xB, temp_s1->info[TI_INFO_IDX_WIDTH],
                                          temp_s1->info[TI_INFO_IDX_HEIGHT] >> 2);
                }
                break;

            default:
                temp_s1 = &temp_s6->unk_43C[0x14];
                temp_s5 = &temp_s6->unk_43C[0x15];
                StretchAlphaTexBlock(&gfx, temp_s1->info[TI_INFO_IDX_WIDTH], temp_s1->info[TI_INFO_IDX_HEIGHT],
                                     temp_s1->texs[TI_TEX_TEX], temp_s1->info[TI_INFO_IDX_WIDTH],
                                     temp_s5->texs[TI_TEX_TEX], temp_s5->info[TI_INFO_IDX_WIDTH], arg1 + 0x68, arg2 + 9,
                                     temp_s1->info[TI_INFO_IDX_WIDTH], temp_s1->info[TI_INFO_IDX_HEIGHT]);

                for (i = 0; i < 2; i++) {
                    draw_count_number(&gfx, 0, 2, game_state_data[i].virus_level, arg1 + _x_4670[i], arg2 + 0xB);
                }
                break;
        }

        temp_s1 = &temp_s6->unk_43C[0xD];
        temp_s5 = &temp_s6->unk_43C[6];
        StretchAlphaTexBlock(&gfx, temp_s1->info[TI_INFO_IDX_WIDTH], temp_s1->info[TI_INFO_IDX_HEIGHT],
                             temp_s1->texs[TI_TEX_TEX], temp_s1->info[TI_INFO_IDX_WIDTH], temp_s5->texs[TI_TEX_TEX],
                             temp_s5->info[TI_INFO_IDX_WIDTH], arg1 + 0x68, (arg2 + 0x19),
                             temp_s1->info[TI_INFO_IDX_WIDTH], temp_s1->info[TI_INFO_IDX_HEIGHT]);

        temp_s1 = &temp_s6->unk_43C[0xC];
        temp_s5 = &temp_s6->unk_43C[5];
        for (i = 0; i < 2; i++) {
            tiStretchAlphaTexItem(&gfx, temp_s1, temp_s5, false, 3, 2 - game_state_data[i].cap_def_speed,
                                  arg1 + _x_4676[i], arg2 + 0x1B, temp_s1->info[TI_INFO_IDX_WIDTH],
                                  temp_s1->info[TI_INFO_IDX_HEIGHT] / 3);
        }
    }

    if (evs_gamesel == ENUM_EVS_GAMESEL_3) {
        if (arg3 != 0) {
            temp_s1 = &temp_s6->unk_43C[0xA];
            temp_s5 = &temp_s6->unk_43C[3];
            StretchAlphaTexBlock(&gfx, temp_s1->info[TI_INFO_IDX_WIDTH], temp_s1->info[TI_INFO_IDX_HEIGHT],
                                 temp_s1->texs[TI_TEX_TEX], temp_s1->info[TI_INFO_IDX_WIDTH], temp_s5->texs[TI_TEX_TEX],
                                 temp_s5->info[TI_INFO_IDX_WIDTH], arg1 + 0x70, arg2 + 0x29,
                                 temp_s1->info[TI_INFO_IDX_WIDTH], temp_s1->info[TI_INFO_IDX_HEIGHT]);
        }

        if (arg4 != 0) {
            draw_count_number(&gfx, 0, 7, game_state_data->game_score, arg1 + 0x90, arg2 + 0x2A);
        }
    } else {
        if (arg3 != 0) {
            temp_s1 = &temp_s6->unk_43C[0xB];
            temp_s5 = &temp_s6->unk_43C[4];
            StretchAlphaTexBlock(&gfx, temp_s1->info[TI_INFO_IDX_WIDTH], temp_s1->info[TI_INFO_IDX_HEIGHT],
                                 temp_s1->texs[TI_TEX_TEX], temp_s1->info[TI_INFO_IDX_WIDTH], temp_s5->texs[TI_TEX_TEX],
                                 temp_s5->info[TI_INFO_IDX_WIDTH], arg1 + 0x58, arg2 + 0x29,
                                 temp_s1->info[TI_INFO_IDX_WIDTH], temp_s1->info[TI_INFO_IDX_HEIGHT]);
        }

        if (arg4 != 0) {
            for (i = 0; i < 2; i++) {
                draw_count_number(&gfx, i + 1, 7, game_state_data[i].game_score, arg1 + _x_4693[i], arg2 + 0x2A);
            }
        }
    }
    *gfxP = gfx;
}

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
    for (i = 0; i < temp_s6->info[TI_INFO_IDX_HEIGHT]; i += 0x2A) {
        for (j = 0; j < arg3; j++) {
            s32 var_t1;

            var_t1 = MIN(0x2A, temp_s6->info[TI_INFO_IDX_HEIGHT] - i);
            tiStretchTexTile(&gfx, temp_s6, j, 0, i, temp_s6->info[TI_INFO_IDX_WIDTH], var_t1, arg1[j], arg2[j] + i,
                             temp_s6->info[TI_INFO_IDX_WIDTH], var_t1);
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

void dm_calc_bottle_2p(void) {
    s32 i = (0x14 - watchGame->unk_394) * 8;
    s32 sp8[2] = { 0x1C - i, i + 0xD4 };

    for (i = 0; i < ARRAY_COUNT(sp8); i++) {
        struct_game_state_data *temp = &game_state_data[i];

        temp->map_x = sp8[i];
        temp->map_y = 0x2E;
    }
}

void dm_draw_bottle_2p(Gfx **gfxP) {
    struct_watchGame *watchGameP = watchGame;
    Gfx *gfx = *gfxP;
    s32 var_a0 = (0x14 - watchGameP->unk_394) * 8;
    s32 arr[2] UNUSED = { -var_a0, var_a0 };
    s32 sp20[2];
    s32 sp28[2];

    for (var_a0 = 0; var_a0 < 2; var_a0++) {
        struct_game_state_data *temp = &game_state_data[var_a0];

        sp20[var_a0] = temp->map_x - 8;
        sp28[var_a0] = temp->map_y - 0x1E;
    }

    _draw_bottle_10(&gfx, sp20, sp28, 2);

    *gfxP = gfx;
}

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
    f32 angle;

    guOrtho(mtx, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 1.0f, 10.0f, 1.0f);
    gSPMatrix(gfx++, mtx++, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);

    guTranslate(mtx, 0.0f, 0.0f, -5.0f);
    gSPMatrix(gfx++, mtx++, G_MTX_NOPUSH | G_MTX_MUL | G_MTX_PROJECTION);

    angle = WrapF(0.0f, 1.0f, watchGameP->unk_424 * DOUBLE_LITERAL(1.0 / 128)) * DOUBLE_LITERAL(M_PI) * 2;
    guRotateRPYF(sp48, 0.0f, (1 - arg6) * 0x5A, sinf(angle) * 4.0f * arg6);

    var_v0 = WrapI(0, ARRAY_COUNT(_pat_4838), ((watchGameP->unk_424 % 128U) * 9) >> 4);

    if (messageIsSpeaking == false) {
        var_v0 = 0;
    }

    temp_s4 = &watchGameP->unk_448[_pat_4838[var_v0] + 1];
    temp_a2 = &watchGameP->unk_448[0];

    var_s0 = MIN(temp_s4->info[TI_INFO_IDX_WIDTH], temp_a2->info[TI_INFO_IDX_WIDTH]);
    var_s3 = MIN(temp_s4->info[TI_INFO_IDX_HEIGHT], temp_a2->info[TI_INFO_IDX_HEIGHT]);

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

    RectAlphaTexTile(&gfx, &vtx, var_s0, var_s3, temp_s4->texs[TI_TEX_TEX], temp_s4->info[TI_INFO_IDX_WIDTH],
                     temp_a2->texs[TI_TEX_TEX], temp_a2->info[TI_INFO_IDX_WIDTH], 0, 0, var_s0, var_s3, 0.0f, 0.0f,
                     var_s0, var_s3);

    *vtxP = vtx;
    *mtxP = mtx;
    *gfxP = gfx;
}

void dm_game_graphic_common(struct_game_state_data *gameStateData, s32 arg1, GameMapCell *mapCells) {
    s32 sp28[2];
    TiTexData *temp_v0;
    s32 temp_s6;
    s32 i;

    temp_s6 = 0;
    if (gameStateData->map_item_size == 8) {
        temp_s6 = 1;
    }

    gSPDisplayList(gGfxHead++, normal_texture_init_dl);

    // Draw the pills and virus on the bottle.
    // Does not draw the falling pills nor the next pill.
    temp_v0 = dm_game_get_capsel_tex(temp_s6);
    load_TexTile_4b(temp_v0->texs[TI_TEX_TEX], temp_v0->info[TI_INFO_IDX_WIDTH], temp_v0->info[TI_INFO_IDX_HEIGHT], 0,
                    0, temp_v0->info[TI_INFO_IDX_WIDTH] - 1, temp_v0->info[TI_INFO_IDX_HEIGHT] - 1);
    gfxSetScissor(&gGfxHead, GFXSETSCISSOR_INTERLACE_NO, gameStateData->map_x,
                  gameStateData->map_y + gameStateData->map_item_size, gameStateData->map_item_size * 8,
                  gameStateData->map_item_size * 0x10);
    for (i = 0; i < 6; i++) {
        temp_v0 = dm_game_get_capsel_pal(temp_s6, i);
        load_TexPal(temp_v0->texs[TI_TEX_TLUT]);
        dm_map_draw(mapCells, i, gameStateData->map_x, gameStateData->map_y - gameStateData->bottom_up_scroll,
                    gameStateData->map_item_size);
    }

#if VERSION_CN || VERSION_GW
    gDPPipeSync(gGfxHead++);
#endif

    gfxSetScissor(&gGfxHead, GFXSETSCISSOR_INTERLACE_NO, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    if ((gameStateData->player_type != PLAYERTYPE_1) &&
        ((gameStateData->player_type == PLAYERTYPE_1) || (arg1 != 0) || (aiDebugP1 < 0))) {
        struct_game_state_data_now_cap *temp;

        if ((visible_fall_point[arg1] == 0) || (gameStateData->mode_now != dm_mode_down)) {
            return;
        }

        if ((gameStateData->now_cap.pos_y[0] <= 0) || (gameStateData->now_cap.capsel_flg_0 == 0)) {
            return;
        }

        temp = &gameStateData->now_cap;

        func_80069ACC(mapCells, temp, sp28);

        gDPSetRenderMode(gGfxHead++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
        gDPSetCombineMode(gGfxHead++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
        gDPSetPrimColor(gGfxHead++, 0, 0, 96, 96, 96, 150);

        for (i = 0; i < 2; i++) {
            s32 temp_t0_2;
            s32 temp_a1_2;
            s32 temp_a2;

            temp_v0 = dm_game_get_capsel_pal(temp_s6, temp->capsel_p[i]);
            load_TexPal(temp_v0->texs[TI_TEX_TLUT]);
            temp_t0_2 = gameStateData->map_item_size;
            temp_a1_2 = (temp->pos_x[i] * temp_t0_2) + gameStateData->map_x;
            temp_a2 = (sp28[i] * temp_t0_2) + gameStateData->map_y;

            gSPTextureRectangle(gGfxHead++, (temp_a1_2 * 4), (temp_a2 * 4), ((temp_a1_2 + temp_t0_2) * 4),
                                ((temp_a2 + temp_t0_2) * 4), G_TX_RENDERTILE, 0x0000,
                                (temp->casel_g[i] * temp_t0_2 << 5), 1 << 10, 1 << 10);
        }

        gDPSetPrimColor(gGfxHead++, 0, 0, 255, 255, 255, 255);
        gDPSetRenderMode(gGfxHead++, G_RM_TEX_EDGE, G_RM_TEX_EDGE2);
    }
}

void dm_game_graphic_p(struct_game_state_data *gameStateData, s32 arg1, GameMapCell *mapCells) {
    struct_watchGame *watchGameP = watchGame;
    s32 sp20[2];
    s32 sp28[2];
    s32 temp_s6;
    s32 i;

    if (gameStateData->cnd_static == dm_cnd_pause) {
        return;
    }

    temp_s6 = gameStateData->map_item_size == 8;

    dm_game_graphic_common(gameStateData, arg1, mapCells);

    gSPDisplayList(gGfxHead++, normal_texture_init_dl);

    if (dm_calc_capsel_pos(gameStateData, sp20, sp28)) {
        if ((watchGameP->unk_420 != 0) || (gameStateData->now_cap.pos_y[0] <= 0) ||
            ((gameStateData->cnd_now != dm_cnd_pause) && (gameStateData->cnd_now != dm_cnd_wait))) {
            dm_draw_capsel_by_gfx(gameStateData, sp20, sp28);
        }
    }

    if ((gameStateData->next_cap.capsel_flg_0 == 0) || (gameStateData->now_cap.pos_y[0] <= 0)) {
        return;
    }

    for (i = 0; i < STRUCT_GAME_STATE_DATA_UNK_178_UNK_LEN; i++) {
        load_TexPal(dm_game_get_capsel_pal(temp_s6, gameStateData->next_cap.capsel_p[i])->texs[TI_TEX_TLUT]);
        draw_Tex(gameStateData->next_cap.pos_x[i] * gameStateData->map_item_size + gameStateData->map_x,
                 (gameStateData->next_cap.pos_y[i] * gameStateData->map_item_size + gameStateData->map_y) - 0xA,
                 gameStateData->map_item_size, gameStateData->map_item_size, 0,
                 gameStateData->next_cap.casel_g[i] * gameStateData->map_item_size);
    }
}

void dm_game_graphic_1p(struct_game_state_data *gameStateDataRef, s32 arg1, GameMapCell *mapCells) {
    struct_watchGame *temp_s2 = watchGame;
    s32 sp20[2];
    s32 sp28[2];
    s32 i;

    if (gameStateDataRef->cnd_static == dm_cnd_pause) {
        return;
    }

    dm_game_graphic_common(gameStateDataRef, arg1, mapCells);

    gSPDisplayList(gGfxHead++, normal_texture_init_dl);

    if (dm_calc_capsel_pos(gameStateDataRef, sp20, sp28)) {
        i = 0;
        if ((gameStateDataRef->mode_now == dm_mode_init) || (gameStateDataRef->mode_now == dm_mode_wait)) {
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

    if ((gameStateDataRef->next_cap.capsel_flg_0 == 0) || (gameStateDataRef->now_cap.pos_y[0] <= 0) ||
        (gameStateDataRef->cnd_static != dm_cnd_wait)) {
        return;
    }

    for (i = 0; i < 2; i++) {
        TiTexData *temp = dm_game_get_capsel_pal(0, gameStateDataRef->next_cap.capsel_p[i]);

        load_TexPal(temp->texs[TI_TEX_TLUT]);
        draw_Tex(0xDA + i * 0xA, 0x34, 0xA, 0xA, 0, gameStateDataRef->next_cap.casel_g[i] * 0xA);
    }
}

void dm_game_graphic_effect(struct_game_state_data *gameStateDataRef, s32 arg1, s32 arg2 UNUSED) {
    struct_watchGame *temp_s4 = watchGame;
    s32 temp_fv0;
    s32 temp_lo;
    s32 temp_s0_2;
    s32 var_v0_4;
    TiTexData *temp_s1;
    TiTexData *other;

    switch (gameStateDataRef->cnd_now) {
        case dm_cnd_null:
            break;

        case dm_cnd_wait:
        case dm_cnd_win:
        case dm_cnd_win_retry:
        case dm_cnd_win_retry_sc:
        case dm_cnd_lose:
        case dm_cnd_lose_retry:
        case dm_cnd_lose_retry_sc:
        case dm_cnd_draw:
        case dm_cnd_draw_retry:
            switch (evs_gamemode) {
                case GMD_FLASH:
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

    if ((gameStateDataRef->cnd_training == dm_cnd_training) && (gameStateDataRef->cnd_static == dm_cnd_wait)) {
        temp_s1 = &temp_s4->unk_440[0x1D];
        other = &temp_s4->unk_440[0x1E];

        gSPDisplayList(gGfxHead++, alpha_texture_init_dl);

        gDPSetCombineLERP(gGfxHead++, TEXEL0, 0, PRIMITIVE, 0, TEXEL1, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0,
                          COMBINED);

        temp_fv0 = ((f32)sins(((s16)temp_s4->unk_424 << 9) & 0xFE00) * 0.0038757324f) + 127.0f;

        gDPSetPrimColor(gGfxHead++, 0, 0, 255, 255, 255, temp_fv0);

        temp_fv0 = ((f32)sins(((s16)temp_s4->unk_424 << 0xA) & 0xFC00) * 0.00015258789f);
        StretchAlphaTexBlock(&gGfxHead, temp_s1->info[TI_INFO_IDX_WIDTH], temp_s1->info[TI_INFO_IDX_HEIGHT],
                             temp_s1->texs[TI_TEX_TEX], temp_s1->info[TI_INFO_IDX_WIDTH], other->texs[TI_TEX_TEX],
                             other->info[TI_INFO_IDX_WIDTH], gameStateDataRef->map_x,
                             (gameStateDataRef->map_y + temp_fv0 + 0xA0), temp_s1->info[TI_INFO_IDX_WIDTH],
                             temp_s1->info[TI_INFO_IDX_HEIGHT]);
    }

    switch (gameStateDataRef->cnd_now) {
        case dm_cnd_stage_clear:
            switch (evs_gamemode) {
                case GMD_TIME_ATTACK:
                    break;

                case GMD_TaiQ:
                    disp_clear_logo(&gGfxHead, arg1, false);
                    break;

                default:
                    disp_clear_logo(&gGfxHead, arg1, true);
                    break;
            }
            break;

        default:
            break;
    }

    switch (gameStateDataRef->cnd_now) {
        case dm_cnd_clear_wait:
            disp_allclear_logo(&gGfxHead, arg1, false);
            break;

        default:
            break;
    }

    switch (gameStateDataRef->cnd_now) {
        case dm_cnd_gover_wait:
            goto block_28;
            break;

        case dm_cnd_game_over:
            if (evs_gamemode != GMD_TIME_ATTACK) {
            block_28:
                switch (evs_gamemode) {
                    case GMD_TIME_ATTACK:
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

    switch (gameStateDataRef->cnd_now) {
        case dm_cnd_retire:
        case dm_cnd_tr_chack:
            if (temp_s4->unk_000 == 0) {
                if (gameStateDataRef->player_type == PLAYERTYPE_0) {
                    temp_fv0 = sins(((s16)temp_s4->unk_424 << 0xA) & 0xFC00) * ((f32)0x7F / 0x8000) + 0x7F;
                    temp_s1 = &temp_s4->unk_440[0x1B];
                    other = &temp_s4->unk_440[0x1C];

                    gSPDisplayList(gGfxHead++, alpha_texture_init_dl);

                    gDPSetCombineLERP(gGfxHead++, TEXEL0, 0, PRIMITIVE, 0, TEXEL1, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED,
                                      0, 0, 0, COMBINED);

                    gDPSetPrimColor(gGfxHead++, 0, 0, 255, 255, 255, temp_fv0);

                    StretchAlphaTexBlock(&gGfxHead, temp_s1->info[TI_INFO_IDX_WIDTH], temp_s1->info[TI_INFO_IDX_HEIGHT],
                                         temp_s1->texs[TI_TEX_TEX], temp_s1->info[TI_INFO_IDX_WIDTH],
                                         other->texs[TI_TEX_TEX], other->info[TI_INFO_IDX_WIDTH],
                                         (f32)gameStateDataRef->map_x, (f32)(gameStateDataRef->map_y + 0x5C),
                                         (f32)temp_s1->info[TI_INFO_IDX_WIDTH], (f32)temp_s1->info[TI_INFO_IDX_HEIGHT]);
                }
            }
            disp_retire_logo(&gGfxHead, arg1);
            break;

        case dm_cnd_retire_wait:
            disp_retire_logo(&gGfxHead, arg1);
            break;

        default:
            break;
    }

    switch (gameStateDataRef->cnd_now) {
        case dm_cnd_stage_clear:
        case dm_cnd_game_over:
        case dm_cnd_win:
        case dm_cnd_win_retry:
        case dm_cnd_win_retry_sc:
        case dm_cnd_lose:
        case dm_cnd_lose_retry:
        case dm_cnd_lose_retry_sc:
        case dm_cnd_draw:
        case dm_cnd_draw_retry:
        case dm_cnd_clear_result:
        case dm_cnd_gover_result:
        case dm_cnd_retire_result:
            if (evs_gamemode == GMD_TIME_ATTACK) {
                if (evs_gamesel == ENUM_EVS_GAMESEL_0) {
                    var_v0_4 = 0xA;
                } else {
                    var_v0_4 = 0x4A;
                }
                func_8006AEFC(&temp_s4->unk_9D0[arg1], &gGfxHead, gameStateDataRef->map_x,
                              gameStateDataRef->map_y + var_v0_4);
            }
            break;

        case dm_cnd_pause:
        case dm_cnd_pause_re:
        case dm_cnd_pause_re_sc:
        case dm_cnd_retire:
        case dm_cnd_tr_chack:
        case dm_cnd_training:
        case dm_cnd_clear_wait:
        case dm_cnd_gover_wait:
        case dm_cnd_retire_wait:
            break;

        default:
            break;
    }

    switch (gameStateDataRef->cnd_now) {
        case dm_cnd_win:
        case dm_cnd_win_retry:
        case dm_cnd_win_retry_sc:
            disp_win_logo(&gGfxHead, arg1);
            break;

        default:
            break;
    }

    switch (gameStateDataRef->cnd_now) {
        case dm_cnd_lose:
        case dm_cnd_lose_retry:
        case dm_cnd_lose_retry_sc:
            disp_lose_logo(&gGfxHead, arg1);
            break;

        default:
            break;
    }

    switch (gameStateDataRef->cnd_now) {
        case dm_cnd_draw:
        case dm_cnd_draw_retry:
            disp_draw_logo(&gGfxHead, arg1);
            break;

        default:
            break;
    }

    switch (gameStateDataRef->cnd_now) {
        case dm_cnd_wait:
        case dm_cnd_init:
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

    switch (gameStateDataRef->cnd_now) {
        case dm_cnd_clear_wait:
        case dm_cnd_gover_wait:
            if ((evs_gamesel == ENUM_EVS_GAMESEL_0) && (evs_gamemode == GMD_TIME_ATTACK) &&
                (temp_s4->effect_timer[arg1] == 0)) {
                push_any_key_draw(gameStateDataRef->map_x + 8, gameStateDataRef->map_y + 0xA0);
            }
            break;

        default:
            break;
    }

    switch (gameStateDataRef->cnd_now) {
        case dm_cnd_pause:
            func_80064298(arg1, &gGfxHead, 0);
            break;

        case dm_cnd_pause_re:
        case dm_cnd_pause_re_sc:
            func_80064298(arg1, &gGfxHead, 1);
            break;

        default:
            break;
    }

    switch (gameStateDataRef->cnd_now) {
        case dm_cnd_pause:
        case dm_cnd_pause_re:
        case dm_cnd_pause_re_sc:
            switch (evs_gamesel) {
                case ENUM_EVS_GAMESEL_2:
                    draw_4p_attack_guide_panel(&gGfxHead, temp_s4->unk_8BC, arg1, (s32)gameStateDataRef->map_x,
                                               gameStateDataRef->map_y - 0x24);
                    break;

                default:
                    break;
            }
            break;

        default:
            break;
    }

    switch (gameStateDataRef->cnd_now) {
        case dm_cnd_stage_clear:
        case dm_cnd_game_over:
        case dm_cnd_win_retry:
        case dm_cnd_win_retry_sc:
        case dm_cnd_lose_retry:
        case dm_cnd_lose_retry_sc:
        case dm_cnd_draw_retry:
            if (temp_s4->effect_timer[arg1] == 0) {
                func_8006431C(arg1, &gGfxHead);
            }
            break;

        default:
            break;
    }

    gfxSetScissor(&gGfxHead, GFXSETSCISSOR_INTERLACE_NO, 0, 0, 0x140, 0xF0);
}

void func_8006D0E8(void) {
    s32 i;

    for (i = 0; i < MAXCONTROLLERS; i++) {
        joyflg[i] = ANY_BUTTON & ~(Z_TRIG | START_BUTTON | L_TRIG | R_TRIG);
        joygmf[i] = 1;
        joygam[i] = 0;
    }

    joycur1 = evs_keyrept[0];
    joycur2 = evs_keyrept[1];
}

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
        if (game_state_data[i].player_type == PLAYERTYPE_0) {
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

void key_control_main(struct_game_state_data *gameStateDataRef, GameMapCell *mapCells, s32 arg2, s32 arg3) {
    struct_watchGame *temp_s5 = watchGame;
    s32 sp18[2];
    s32 sp20[2];

    func_80063FF4();

    if ((gameStateDataRef->player_type != PLAYERTYPE_1) &&
        ((gameStateDataRef->player_type == 1) || (arg2 != 0) || (aiDebugP1 < 0))) {
        if (gControllerPressedButtons[arg3] & (U_CBUTTONS | L_CBUTTONS | R_CBUTTONS | D_CBUTTONS)) {
            visible_fall_point[arg2] = !visible_fall_point[arg2];
        }
    }

    save_visible_fall_point_flag();

    if (gameStateDataRef->mode_now == dm_mode_throw) {
        if ((temp_s5->unk_420 == 0) && dm_calc_capsel_pos(gameStateDataRef, sp18, sp20)) {
            dm_draw_capsel_by_cpu_tentative(gameStateDataRef, sp18, sp20);
        }

        if (gameStateDataRef->player_type == PLAYERTYPE_0) {
            if (gControllerHoldButtons[arg3] & R_JPAD) {
                joyCursorFastSet(R_JPAD, arg3);
            }
            if (gControllerHoldButtons[arg3] & L_JPAD) {
                joyCursorFastSet(L_JPAD, arg3);
            }
        }
    } else if (gameStateDataRef->mode_now == dm_mode_down) {
        if (gameStateDataRef->cnd_static == dm_cnd_wait) {
            struct_game_state_data_now_cap *temp_s0_2;

            if ((gameStateDataRef->player_type == PLAYERTYPE_1) ||
                ((gameStateDataRef->player_type != PLAYERTYPE_1) && (arg2 == 0) && (aiDebugP1 >= 0))) {
                u16 temp_s1_2 = joygam[arg2];

                aifKeyOut(gameStateDataRef);
                if (temp_s5->unk_000 != 0) {
                    joygam[arg2] = temp_s1_2;
                }
            }

            temp_s0_2 = &gameStateDataRef->now_cap;
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

            gameStateDataRef->cap_speed_vec = 1;
            if ((joygam[arg2] & D_JPAD) && (temp_s0_2->pos_y[0] > 0)) {
                s32 val = FallSpeed[gameStateDataRef->cap_speed];

                val = (val >> 1) + (val & 1);

                gameStateDataRef->cap_speed_vec = val;
            }
        } else if (gameStateDataRef->player_type == PLAYERTYPE_0) {
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
            s32 temp_s3 = gameStateDataRef->now_cap.capsel_flg_0;

            gameStateDataRef->now_cap.capsel_flg_0 = 1;
            if (temp_s5->unk_420 == 0) {
                if (dm_calc_capsel_pos(gameStateDataRef, sp18, sp20)) {
                    dm_draw_capsel_by_cpu_tentative(gameStateDataRef, sp18, sp20);
                }
            }
            gameStateDataRef->now_cap.capsel_flg_0 = temp_s3;
            temp_s5->unk_37C[arg2] -= 1;
        }

        if (gameStateDataRef->player_type == PLAYERTYPE_0) {
            joyCursorFastSet(R_JPAD, arg3);
            joyCursorFastSet(L_JPAD, arg3);
        }
    }
}

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

                if (((ptr->player_type == PLAYERTYPE_1) ||
                     (((ptr->player_type != PLAYERTYPE_1) && (i == 0)) && (aiDebugP1 >= 0))) &&
                    (game_state_data[i].cnd_static == dm_cnd_wait)) {
                    aifMake(&game_state_data[i]);
                }
            }
            break;

        case ENUM_EVS_GAMESEL_2:
        case ENUM_EVS_GAMESEL_6:
            for (i = 0; i < 4; i++) {
                ptr = &game_state_data[i];

                if (((ptr->player_type == PLAYERTYPE_1) ||
                     (((ptr->player_type != PLAYERTYPE_1) && (i == 0)) && (aiDebugP1 >= 0))) &&
                    (game_state_data[i].cnd_static == dm_cnd_wait)) {
                    aifMake(&game_state_data[i]);
                }
            }
            break;

        case ENUM_EVS_GAMESEL_0:
        case ENUM_EVS_GAMESEL_4:
            if ((game_state_data->player_type == PLAYERTYPE_1) || (aiDebugP1 >= 0)) {
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
        if (game_state_data[i].cnd_static == dm_cnd_wait) {
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
        scoreNums_init(&watchGameP->unk_0B8[i]);
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
    watchGameP->unk_3BC = (evs_gamemode == GMD_FLASH) ? 1 : 3;
    watchGameP->unk_3C4 = main_no != MAIN_GAME;

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
        case GMD_TaiQ:
            watchGameP->unk_3C8 = _big_virus_def_wait[game_state_data[0].game_level];
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
        case GMD_TaiQ:
        case GMD_TIME_ATTACK:
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
    bzero(watchGameP->password, sizeof(watchGameP->password));

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
        temp_s0_3[i].map_x = map_x_table_5383[j][i];
        temp_s0_3[i].map_y = map_y_table_5384[var_s4];
        temp_s0_3[i].map_item_size = size_table_5385[var_s4];
    }

    for (i = 0; i < ARRAY_COUNT(game_state_data); i++) {
        temp_s0_3 = &game_state_data[i];

        temp_s0_3->player_no = i;
        temp_s0_3->mode_now = dm_mode_init;
        temp_s0_3->cnd_now = dm_cnd_init;
        temp_s0_3->cnd_training = dm_cnd_wait;
        temp_s0_3->cnd_static = dm_cnd_wait;
        temp_s0_3->virus_number = 0;
        temp_s0_3->virus_order_number = 0;
        temp_s0_3->warning_se_flag = false;
        temp_s0_3->flg_retire = false;
        temp_s0_3->flg_game_over = false;
        temp_s0_3->flg_training = false;
        temp_s0_3->cap_speed = GameSpeed[temp_s0_3->cap_def_speed];
        temp_s0_3->cap_speed_max = 0;
        temp_s0_3->cap_speed_vec = 1;
        temp_s0_3->cap_magazine_cnt = 1;
        temp_s0_3->cap_count = 0;
        temp_s0_3->cap_speed_count = 0;
        temp_s0_3->cap_move_se_flg = false;
        dm_set_capsel(temp_s0_3);
        temp_s0_3->virus_anime = 0;
        temp_s0_3->virus_anime_count = 0;
        temp_s0_3->virus_anime_vec = 1;
        temp_s0_3->erase_anime = 0;
        temp_s0_3->erase_anime_count = 0;
        temp_s0_3->erase_virus_count = 0;
        temp_s0_3->erase_virus_count_old = 0;
        temp_s0_3->chain_line = 0;
        temp_s0_3->chain_count = 0;
        temp_s0_3->bottom_up_scroll = 0;
        temp_s0_3->total_erase_count = 0;
        temp_s0_3->total_chain_count = 0;

        switch (evs_gamesel) {
            case ENUM_EVS_GAMESEL_2:
            case ENUM_EVS_GAMESEL_6:
                temp_s0_3->virus_anime_spead = 0xC;
                temp_s0_3->virus_anime_max = 0;
                break;

            default:
                temp_s0_3->virus_anime_spead = 8;
                temp_s0_3->virus_anime_max = 2;
                break;
        }

        for (j = 0; j < ARRAY_COUNT(temp_s0_3->chain_color); j++) {
            temp_s0_3->chain_color[j] = 0;
        }

        for (j = 0; j < ARRAY_COUNT(temp_s0_3->cap_attack_work); j++) {
            temp_s0_3->cap_attack_work[j].unk_0 = 0;
            temp_s0_3->cap_attack_work[j].unk_2 = 0;
        }

        init_map_all(game_map_data[i]);
    }

    var_s0_2 = game_state_data;
    for (i = 0; i < evs_playcnt; i++) {
        dm_virus_init(evs_gamemode, &var_s0_2[i], virus_map_data[i], virus_map_disp_order[i]);
        if (evs_gamemode == GMD_FLASH) {
            make_flash_virus_pos(&var_s0_2[i], virus_map_data[i], virus_map_disp_order[i]);
        } else {
            game_state_data[i].flash_virus_count = 0;
        }
    }

    for (i = 0; i < evs_playcnt - 1; i++) {
        for (j = i + 1; j < evs_playcnt; j++) {
            if (game_state_data[i].virus_level == game_state_data[j].virus_level) {
                dm_virus_map_copy(virus_map_data[i], virus_map_data[j], virus_map_disp_order[i],
                                  virus_map_disp_order[j]);
                if (evs_gamemode == GMD_FLASH) {
                    game_state_data[j].flash_virus_count = game_state_data[i].flash_virus_count;
                    bcopy(&game_state_data[i].flash_virus_pos, &game_state_data[j].flash_virus_pos,
                          sizeof(game_state_data[j].flash_virus_pos));
                    bcopy(&game_state_data[i].flash_virus_bak, &game_state_data[j].flash_virus_bak,
                          sizeof(game_state_data[i].flash_virus_bak));
                }
                break;
            }
        }
    }

    effectAll_init();
    aifGameInit();
    s_hard_mode = false;
    fool_mode = false;

    if (evs_story_level == 3) {
        if (evs_story_no == 7) {
            fool_mode = true;
        } else {
            s_hard_mode = true;
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

#if VERSION_US || VERSION_GW
    start = romTableP[ROMDATATBL_GAME_AL].start;

    watchGameP->unk_3B0 = 0;

    //! FAKE
    watchGameP->unk_878 = var_v0 = 0x7F;
#elif VERSION_CN
    watchGameP->unk_3B0 = 0;

    //! FAKE
    watchGameP->unk_878 = var_v0 = 0x7F;

    start = romTableP[ROMDATATBL_GAME_AL].start;
#else
#error ""
#endif
    end = romTableP[ROMDATATBL_GAME_AL].end;

    result = tiLoadTexData(&heapTop, start, end);

#if VERSION_US || VERSION_GW
    start = romTableP[ROMDATATBL_GAME_ITEM].start;
    watchGameP->unk_430 = result;
#elif VERSION_CN
    watchGameP->unk_430 = result;
    start = romTableP[ROMDATATBL_GAME_ITEM].start;
#else
#error ""
#endif

    end = romTableP[ROMDATATBL_GAME_ITEM].end;
    watchGameP->unk_444 = tiLoadTexData(&heapTop, start, end);

    if (main_no != MAIN_GAME) {
        watchGameP->unk_448 =
            tiLoadTexData(&heapTop, romTableP[ROMDATATBL_MENU_KASA].start, romTableP[ROMDATATBL_MENU_KASA].end);
    }

#if VERSION_US || VERSION_GW
    temp_a0 = _romDataTbl[ROMDATATBL_GAME_ETC].start;
    watchGameP->gameEtcSeg = heapTop;
#elif VERSION_CN
    watchGameP->gameEtcSeg = heapTop;
    temp_a0 = _romDataTbl[ROMDATATBL_GAME_ETC].start;
#else
#error ""
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
        timeAttackResult_init(&watchGameP->unk_9D0[i]);
    }

#if VERSION_US || VERSION_GW
    msgWnd_init2(&watchGameP->unk_A28, &heapTop, 0x100, 0xA, 5, temp, 0);
#elif VERSION_CN
    //! FAKE
    msgWnd_init2(&watchGameP->unk_A28, &heapTop, 0x100, 0xA, var_v0 = 5, temp, 0);
#else
#error ""
#endif

    watchGameP->unk_A28.posX = (s32)(SCREEN_WIDTH - (watchGameP->unk_A28.colStep * 20)) >> 1;
    watchGameP->unk_A28.posY = (s32)(SCREEN_HEIGHT - (watchGameP->unk_A28.rowStep * 2)) >> 1;
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
                    case GMD_NORMAL:
                        evs_high_score = temp_a3->level_data[game_state_data[0].cap_def_speed].score;
                        break;

                    case GMD_TaiQ:
                        evs_high_score = temp_a3->taiQ_data[game_state_data[0].game_level].score;
                        break;

                    case GMD_TIME_ATTACK:
                        evs_high_score = temp_a3->timeAt_data[game_state_data[0].game_level].score;
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
            animeState_load(&game_state_data[0].anime, &heapTop, CHARANIMEMODE_MARIO);
            animeState_set(&game_state_data[0].anime, ANIMENO_2);
            watchGameP->unk_438 =
                tiLoadTexData(&heapTop, romTableP[ROMDATATBL_GAME_P1].start, romTableP[ROMDATATBL_GAME_P1].end);
            watchGameP->unk_434 =
                tiLoadTexData(&heapTop, romTableP[ROMDATATBL_GAME_LS].start, romTableP[ROMDATATBL_GAME_LS].end);

            for (i = 0; i < ARRAY_COUNT(watchGameP->animeStates); i++) {
                animeState_load(&watchGameP->animeStates[i], &heapTop, i + CHARANIMEMODE_VIRUS_R);
            }

            animeSmog_load(&watchGameP->animeSmogs[0], &heapTop);
            for (i = 1; i < ARRAY_COUNT(watchGameP->animeSmogs); i++) {
                animeSmog_init(&watchGameP->animeSmogs[i], &watchGameP->animeSmogs[0].animeState[0]);
            }

            msgWnd_init2(&watchGameP->messageWnd, &heapTop, 0x1000, 0x14, 0xF, 0x28, 0xF);
            watchGameP->messageWnd.centering = true;
            msgWnd_addStr(&watchGameP->messageWnd, st_staffroll_txt);
            msgWnd_skip(&watchGameP->messageWnd);
            watchGameP->messageWnd.fontType = FONTTYPE_1;
            watchGameP->messageWnd.contFlags = 0;
            heapTop = init_coffee_break(heapTop, game_state_data[0].cap_def_speed);
            break;

        case ENUM_EVS_GAMESEL_1:
        case ENUM_EVS_GAMESEL_3:
        case ENUM_EVS_GAMESEL_5:
            for (i = 0; i < 2; i++) {
                animeState_load(&game_state_data[i].anime, &heapTop, game_state_data[i].charNo);
            }

            if (evs_story_flg == 0) {
                for (i = 0; i < ARRAY_COUNT(watchGameP->unk_8B4); i++) {
                    watchGameP->unk_8B4[i] = 0;
                }

                switch (evs_gamesel) {
                    case ENUM_EVS_GAMESEL_1:
                        for (i = 0; i < ARRAY_COUNT(watchGameP->unk_8B4); i++) {
                            watchGameP->unk_8B4[i] = evs_mem_data[evs_select_name_no[i]].vsman_data[0];
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
                animeState_load(&game_state_data[i].anime, &heapTop, game_state_data[i].charNo);
            }

            for (i = 0; i < ARRAY_COUNT(watchGameP->unk_8CC); i++) {
                watchGameP->unk_8CC[i] = 0;
            }

            for (i = 0; i < ARRAY_COUNT(watchGameP->unk_8CC); i++) {
                watchGameP->unk_8CC[game_state_data[i].team_no]++;
            }

            watchGameP->unk_8BC = 0;

            for (i = 0; i < ARRAY_COUNT(game_state_data); i++) {
                if (game_state_data[i].player_type == PLAYERTYPE_0) {
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
                if (game_state_data[i].team_no == TEAMNUMBER_0) {
                    watchGameP->unk_8C4 |= (1 << i);
                }
            }

            for (i = 0; i < ARRAY_COUNT(game_state_data); i++) {
                if (game_state_data[i].team_no == TEAMNUMBER_1) {
                    watchGameP->unk_8C8 |= (1 << i);
                }
            }
            break;

        default:
            break;
    }
}

void dm_game_init_snap_bg(void) {
    struct_watchGame *watchGameP = watchGame;

    BUFFER_MALLOC64(&watchGameP->unk_87C, heapTop, sizeof(u16) * ((SCREEN_WIDTH + 8) * SCREEN_HEIGHT));
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
        gDPSetColorImage(gfx++, G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WIDTH + 8, osVirtualToPhysical(temp_s7->unk_87C));
    }

    switch (evs_gamesel) {
        case ENUM_EVS_GAMESEL_0:
        case ENUM_EVS_GAMESEL_4:
            switch (evs_gamemode) {
                case GMD_NORMAL:
                    var_s6 = 0;
                    break;

                case GMD_TaiQ:
                    var_s6 = 1;
                    break;

                case GMD_TIME_ATTACK:
                    var_s6 = 2;
                    break;

                default:
                    break;
            }

            gSPDisplayList(gfx++, normal_texture_init_dl);

            temp_s1 = &temp_s7->unk_434[_bgTex_5794[var_s6]];

            for (i = 0; i < ARRAY_COUNTU(_bgPos_5792); i++) {
                tiStretchTexTile(&gfx, temp_s1, false, 0, 0, temp_s1->info[TI_INFO_IDX_WIDTH],
                                 temp_s1->info[TI_INFO_IDX_HEIGHT], _bgPos_5792[i][0], _bgPos_5792[i][1],
                                 temp_s1->info[TI_INFO_IDX_WIDTH], temp_s1->info[TI_INFO_IDX_HEIGHT]);
            }

            temp_s1 = &temp_s7->unk_434[_magTex_5795[var_s6]];
            tiStretchTexTile(&gfx, temp_s1, false, 0, 0, temp_s1->info[TI_INFO_IDX_WIDTH],
                             temp_s1->info[TI_INFO_IDX_HEIGHT], 0.0f, 120.0f, temp_s1->info[TI_INFO_IDX_WIDTH],
                             temp_s1->info[TI_INFO_IDX_HEIGHT]);

            if (arg3 != 0) {
                gSPDisplayList(gfx++, alpha_texture_init_dl);

                temp_s1 = &temp_s7->unk_434[9];
                temp_s2 = &temp_s7->unk_434[2];

                var_s0_2 = MIN(temp_s1->info[TI_INFO_IDX_WIDTH], temp_s2->info[TI_INFO_IDX_WIDTH]);

                StretchAlphaTexTile(&gfx, var_s0_2, temp_s1->info[TI_INFO_IDX_HEIGHT], temp_s1->texs[TI_TEX_TEX],
                                    temp_s1->info[TI_INFO_IDX_WIDTH], temp_s2->texs[TI_TEX_TEX], *temp_s2->info, 0, 0,
                                    var_s0_2, temp_s1->info[TI_INFO_IDX_HEIGHT], 202.0f, 12.0f, var_s0_2,
                                    temp_s1->info[TI_INFO_IDX_HEIGHT]);

                temp_s1 = &temp_s7->unk_434[_scrTex_5796[var_s6]];
                temp_s2 = &temp_s7->unk_434[1];

                var_s0_2 = MIN(temp_s1->info[TI_INFO_IDX_WIDTH], temp_s2->info[TI_INFO_IDX_WIDTH]);

                StretchAlphaTexTile(&gfx, var_s0_2, temp_s1->info[TI_INFO_IDX_HEIGHT], temp_s1->texs[TI_TEX_TEX],
                                    temp_s1->info[TI_INFO_IDX_WIDTH], temp_s2->texs[TI_TEX_TEX],
                                    temp_s2->info[TI_INFO_IDX_WIDTH], 0, 0, var_s0_2, temp_s1->info[TI_INFO_IDX_HEIGHT],
                                    11.0f, 17.0f, var_s0_2, temp_s1->info[TI_INFO_IDX_HEIGHT]);

                temp_s2 = &temp_s7->unk_434[4];

                for (i = 0; i < ARRAY_COUNTU(_panelTex_5797[var_s6]); i++) {
                    temp_s1 = &temp_s7->unk_434[_panelTex_5797[var_s6][i]];

                    var_s0_2 = MIN(temp_s1->info[TI_INFO_IDX_WIDTH], temp_s2->info[TI_INFO_IDX_WIDTH]);

                    StretchAlphaTexTile(&gfx, var_s0_2, temp_s1->info[TI_INFO_IDX_HEIGHT], temp_s1->texs[TI_TEX_TEX],
                                        temp_s1->info[TI_INFO_IDX_WIDTH], temp_s2->texs[TI_TEX_TEX],
                                        temp_s2->info[TI_INFO_IDX_WIDTH], 0, 0, var_s0_2,
                                        temp_s1->info[TI_INFO_IDX_HEIGHT], _panelPos_5793[i][0], _panelPos_5793[i][1],
                                        var_s0_2, temp_s1->info[TI_INFO_IDX_HEIGHT]);
                }

                switch (evs_gamemode) {
                    case GMD_TaiQ:
                    case GMD_TIME_ATTACK:
                        temp_s1 = &temp_s7->unk_434[0xA];
                        temp_s2 = &temp_s7->unk_434[3];
                        tiStretchAlphaTexItem(&gfx, temp_s1, temp_s2, false, 3, game_state_data->game_level, 232.0f,
                                              120.0f, 48.0f, 16.0f);
                        break;

                    default:
                        break;
                }

                temp_s1 = &temp_s7->unk_434[5];
                temp_s2 = &temp_s7->unk_434[0];
                tiStretchAlphaTexItem(&gfx, temp_s1, temp_s2, false, 3, game_state_data->cap_def_speed, 232.0f, 162.0f,
                                      48.0f, 16.0f);
            }

            gSPDisplayList(gfx++, normal_texture_init_dl);

            gDPSetCombineMode(gfx++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
            gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
            gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, 96);

            // Why draw twice?
            temp_s1 = &temp_s7->unk_438[1];
            for (i = 0; i < 2; i++) {
                tiStretchTexBlock(&gfx, temp_s1, false, 110.0f, 16.0f, temp_s1->info[TI_INFO_IDX_WIDTH],
                                  temp_s1->info[TI_INFO_IDX_HEIGHT]);
            }

            temp_s1 = &temp_s7->unk_438[0];
            for (i = 0; i < 2; i++) {
                tiCopyTexBlock(&gfx, temp_s1, false, 110, 16);
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
            for (i = 0; i < ARRAY_COUNT(_posP4Bottle); i++) {
                tiStretchTexBlock(&gfx, temp_s1, false, _posP4Bottle[i][0] + RO_800B1D7C[0],
                                  _posP4Bottle[i][1] + RO_800B1D7C[1], temp_s1->info[TI_INFO_IDX_WIDTH],
                                  temp_s1->info[TI_INFO_IDX_HEIGHT]);
            }

            temp_s1 = &temp_s7->unk_440[0];

            for (i = 0; i < ARRAY_COUNT(_posP4Bottle); i++) {
                tiCopyTexBlock(&gfx, temp_s1, false, _posP4Bottle[i][0], _posP4Bottle[i][1]);
            }

            if (arg3 != 0) {
                gSPDisplayList(gfx++, normal_texture_init_dl);

                temp_s1 = &temp_s7->unk_440[8];
                for (i = 0; i < ARRAY_COUNT(_posP4CharBase); i++) {
                    tiStretchTexBlock(&gfx, temp_s1, false, _posP4CharBase[i][0], _posP4CharBase[i][1],
                                      temp_s1->info[TI_INFO_IDX_WIDTH], temp_s1->info[TI_INFO_IDX_HEIGHT]);
                }

                gSPDisplayList(gfx++, alpha_texture_init_dl);

                if ((evs_story_flg != 0) || (temp_s7->unk_8C0 == 0)) {
                    if (evs_gamemode == GMD_FLASH) {
                        temp_s1 = &temp_s7->unk_440[0xB];
                        temp_s2 = &temp_s7->unk_440[0x13];
                    } else {
                        temp_s1 = &temp_s7->unk_440[0x19];
                        temp_s2 = &temp_s7->unk_440[0x1A];
                    }

                    var_s0_2 = MIN(temp_s1->info[TI_INFO_IDX_WIDTH], temp_s2->info[TI_INFO_IDX_WIDTH]);

                    for (i = 0; i < 4; i++) {
                        StretchAlphaTexBlock(&gfx, var_s0_2, temp_s1->info[TI_INFO_IDX_HEIGHT],
                                             temp_s1->texs[TI_TEX_TEX], temp_s1->info[TI_INFO_IDX_WIDTH],
                                             temp_s2->texs[TI_TEX_TEX], temp_s2->info[TI_INFO_IDX_WIDTH],
                                             _posP4CharBase[i][0] + 0x19, _posP4CharBase[i][1], var_s0_2,
                                             temp_s1->info[TI_INFO_IDX_HEIGHT]);
                    }
                }

                if (evs_story_flg != 0) {
                    temp_s1 = &temp_s7->unk_440[0xF];
                    temp_s2 = &temp_s7->unk_440[0x17];

                    var_s0_2 = MIN(temp_s1->info[TI_INFO_IDX_WIDTH], temp_s2->info[TI_INFO_IDX_WIDTH]);

                    StretchAlphaTexBlock(&gfx, var_s0_2, temp_s1->info[TI_INFO_IDX_HEIGHT], temp_s1->texs[TI_TEX_TEX],
                                         temp_s1->info[TI_INFO_IDX_WIDTH], temp_s2->texs[TI_TEX_TEX],
                                         temp_s1->info[TI_INFO_IDX_WIDTH], 16.0f, 11.0f, var_s0_2,
                                         temp_s1->info[TI_INFO_IDX_HEIGHT]);
                } else if (temp_s7->unk_8C0 != 0) {
                    for (i = 0; i < 4; i++) {
                        s32 temp_v0_9;

                        temp_v0_9 = game_state_data[i].team_no != TEAMNUMBER_0;
                        temp_s1 = &temp_s7->unk_440[tbl_5867[temp_v0_9][0]];
                        temp_s2 = &temp_s7->unk_440[tbl_5867[temp_v0_9][1]];

                        var_s0_2 = MIN(temp_s1->info[TI_INFO_IDX_WIDTH], temp_s2->info[TI_INFO_IDX_WIDTH]);

                        StretchAlphaTexBlock(&gfx, var_s0_2, temp_s1->info[TI_INFO_IDX_HEIGHT],
                                             temp_s1->texs[TI_TEX_TEX], temp_s1->info[TI_INFO_IDX_WIDTH],
                                             temp_s2->texs[TI_TEX_TEX], temp_s1->info[TI_INFO_IDX_WIDTH],
                                             _posP4CharBase[i][0] + 0x19, _posP4CharBase[i][1], var_s0_2,
                                             temp_s1->info[TI_INFO_IDX_HEIGHT]);
                    }

                    //! FAKE:
                    temp_s1 = temp_s7->unk_440 + 2 + evs_vs_count - 1;

                    CopyTexBlock8(&gfx, temp_s1->texs[TI_TEX_TLUT], temp_s1->texs[TI_TEX_TEX], 0x10, 8,
                                  temp_s1->info[TI_INFO_IDX_WIDTH], temp_s1->info[TI_INFO_IDX_HEIGHT]);
                } else {
                    //! FAKE:
                    temp_s1 = temp_s7->unk_440 + 5 + evs_vs_count - 1;

                    CopyTexBlock8(&gfx, temp_s1->texs[TI_TEX_TLUT], temp_s1->texs[TI_TEX_TEX], 0x10, 0xB,
                                  temp_s1->info[TI_INFO_IDX_WIDTH], temp_s1->info[TI_INFO_IDX_HEIGHT]);
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

                StretchAlphaTexBlock(&gfx, temp_s1->info[TI_INFO_IDX_WIDTH], temp_s1->info[TI_INFO_IDX_HEIGHT],
                                     temp_s1->texs[TI_TEX_TEX], temp_s1->info[TI_INFO_IDX_WIDTH],
                                     temp_s2->texs[TI_TEX_TEX], temp_s2->info[TI_INFO_IDX_WIDTH], 114.0f, 150.0f,
                                     temp_s1->info[TI_INFO_IDX_WIDTH], temp_s1->info[TI_INFO_IDX_HEIGHT]);
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

void func_8006F628(Gfx **gfxP) {
    Gfx *gfx = *gfxP;

    CopyTexBlock16(&gfx, watchGame->unk_87C, 0, 0, SCREEN_WIDTH + 8, SCREEN_HEIGHT);
    *gfxP = gfx;
}

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
    BgTasksManager_Init();

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

    while (BgTasksManager_GetRemainingTasks() != 0) {
        osRecvMesg(&scMQ, NULL, OS_MESG_BLOCK);
    }
    BgTasksManager_Destroy();

    nnScRemoveClient(sc, &scClient);

    return ret;
}

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
                    temp_s3->messageWnd.scrSpeed = 1.0f / 8.0f;
                } else {
                    temp_s3->messageWnd.scrSpeed = 1.0f / 60.0f;
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
                        var_s0 = game_state_data[0].virus_level;
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

                        if (game_state_data[0].virus_level < 0x63U) {
                            game_state_data[0].virus_level++;
                        }
                        break;

                    case 2:
                        game_state_data[0].game_score = 0;
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
                        animeState_set(&game_state_data[0].anime, ANIMENO_2);

                        for (var_s0 = 0; var_s0 < 3; var_s0++) {
                            animeState_set(&temp_s3->animeStates[var_s0], ANIMENO_0);
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
                            case GMD_TIME_ATTACK:
                                for (var_s0 = 0; var_s0 < 2; var_s0++) {
                                    game_state_data[var_s0].game_score = 0;
                                }
                                break;

                            default:
                                break;
                        }

                        dm_game_init(true);

                        for (var_s0 = 0; var_s0 < 2; var_s0++) {
                            animeState_set(&game_state_data[var_s0].anime, ANIMENO_0);
                        }

                        backup_game_state(0);
                    }
                    break;

                case 2:
                    var_s4_2 = 0;
                    for (var_s0 = 0; var_s0 < 2; var_s0++) {
                        game_state_data[var_s0].game_score = 0;
                    }

                    dm_game_init(false);

                    for (var_s0 = 0; var_s0 < 2; var_s0++) {
                        animeState_set(&game_state_data[var_s0].anime, ANIMENO_0);
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
                            animeState_set(&game_state_data[var_s0].anime, ANIMENO_0);
                        }
                        backup_game_state(0);
                    }
                    break;

                case 2:
                    var_s4_2 = 0;
                    for (var_s0 = 0; var_s0 < 2; var_s0++) {
                        game_state_data[var_s0].game_score = 0;
                    }

                    dm_game_init(false);

                    var_s0 = 0;
                    for (var_s0 = 0; var_s0 < 4; var_s0++) {
                        animeState_set(&game_state_data[var_s0].anime, ANIMENO_0);
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

/**
 * Original name: dm_game_main3
 */
enum_main_no dm_game_main3(s32 arg0) {
    enum_main_no var_a1;

    switch (evs_gamesel) {
        case ENUM_EVS_GAMESEL_0:
        case ENUM_EVS_GAMESEL_1:
            var_a1 = MAIN_MENU;
            break;

        case ENUM_EVS_GAMESEL_2:
            if (evs_story_flg != 0) {
                evs_gamesel = ENUM_EVS_GAMESEL_3;
                if ((game_state_data[0].cnd_static == dm_cnd_win) && (arg0 != -2)) {
                    story_proc_no++;
                    var_a1 = MAIN_STORY;
                } else {
                    var_a1 = MAIN_MENU;
                }
            } else {
                var_a1 = MAIN_MENU;
            }
            break;

        case ENUM_EVS_GAMESEL_3:
            if (evs_story_flg != 0) {
                if ((game_state_data[0].cnd_static == dm_cnd_win) && (arg0 != -2)) {
                    if (func_8006498C(evs_story_level, evs_story_no, game_state_data[0].game_retry)) {
                        story_proc_no++;
                    } else {
                        story_proc_no += 2;
                    }
                    var_a1 = MAIN_STORY;
                } else if (evs_story_no == 9) {
                    var_a1 = MAIN_MENU;
                } else {
                    var_a1 = MAIN_MENU;
                }

                if ((story_proc_no - BGROMDATA_INDEX10 < BGROMDATA_INDEX12 - BGROMDATA_INDEX10) ||
                    (story_proc_no == BGROMDATA_INDEX22) || (story_proc_no == BGROMDATA_INDEX23)) {
                    switch (evs_story_level) {
                        case 0:
                            if (game_state_data[0].game_retry != 0) {
                                EndingLastMessage = _mesEasyCont;
                            } else {
                                EndingLastMessage = _mesEasyNoCont;
                            }
                            break;

                        case 1:
                            if (game_state_data[0].game_retry != 0) {
                                EndingLastMessage = _mesNormalCont;
                            } else {
                                EndingLastMessage = _mesNormalNoCont;
                            }
                            break;

                        case 0x2:
                            if (game_state_data[0].game_retry != 0) {
                                EndingLastMessage = _mesHardCont;
                            } else {
                                EndingLastMessage = _mesHardNoCont;
                            }
                            break;

                        case 0x3:
                            if (game_state_data[0].game_retry != 0) {
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
                var_a1 = MAIN_MENU;
            }
            break;

        case ENUM_EVS_GAMESEL_4:
        case ENUM_EVS_GAMESEL_5:
        case ENUM_EVS_GAMESEL_6:
            var_a1 = MAIN_TITLE;
            break;

        default:
            UNREACHABLE;
            break;
    }

    return var_a1;
}

void dm_game_graphic(void) {
    struct_watchGame *watchGameP = watchGame;

    if (watchGameP->unk_878 != 0x7F) {
        osSetThreadPri(NULL, THREAD_PRI_GRAPHIC);
        watchGameP->unk_878 = 0;
        return;
    }

    RecWritingMsg_draw(&watchGameP->recMessage, &gGfxHead);

    gDPFullSync(gGfxHead++);
    gSPEndDisplayList(gGfxHead++);

    osWritebackDCacheAll();

    gfxTaskStart(&B_800FAE80[gfx_gtask_no], gGfxGlist[gfx_gtask_no], (gGfxHead - gGfxGlist[gfx_gtask_no]) * sizeof(Gfx),
                 0, (watchGameP->unk_880 == 0) ? OS_SC_SWAPBUFFER : 0);
    osSetThreadPri(NULL, THREAD_PRI_GRAPHIC);
    dm_game_graphic2();
    osSetThreadPri(NULL, OS_PRIORITY_APPMAX);
}

const s32 _x_6416[] = { 0x77, 0xB6 };
static_assert(ARRAY_COUNT(watchGame->unk_8B4) == ARRAY_COUNT(_x_6416), "");

const s32 dir_6435[2] = { -1, 1 };

const s32 color2index_6470[] = { 1, 0, 2 };

void dm_game_graphic2(void) {
    struct_watchGame *temp_s7 = watchGame;
    bool debugMenuEnabled =
        (game_state_data[0].mode_now == dm_mode_debug_config) || (game_state_data[0].mode_now == dm_mode_debug);
    Mtx *mtx;
    Vtx *vtx;
    s32 i;
    s32 j;
    s32 cached;
    TiTexData *var_t2;
    TiTexData *var_s6;

    gGfxHead = gGfxGlist[gfx_gtask_no];
    mtx = dm_get_mtx_buf();
    vtx = dm_get_vtx_buf();

    gSPSegment(gGfxHead++, 0x00, NULL);

    F3RCPinitRtn();
    gfxSetScissor(&gGfxHead, GFXSETSCISSOR_INTERLACE_NO, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    F3ClearFZRtn(debugMenuEnabled);
    if (!debugMenuEnabled) {
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

            if (!debugMenuEnabled) {
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
            if (!debugMenuEnabled && (temp_s7->unk_880 == 0)) {
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
            if (!debugMenuEnabled && (temp_s7->unk_880 == 0)) {
                disp_logo_setup(&gGfxHead);

                if (temp_s7->unk_9AC > 0) {
                    draw_coffee_break(&gGfxHead, temp_s7->unk_9B4, temp_s7->unk_9B8, temp_s7->unk_9AC > 1);
                    msgWnd_draw(&temp_s7->messageWnd, &gGfxHead);
                    if (temp_s7->unk_9B0 == 0x168) {
                        push_any_key_draw(0x80, 0xC0);
                    }
                } else {
                    animeState_initDL(&game_state_data[0].anime, &gGfxHead);
                    animeState_draw(&game_state_data[0].anime, &gGfxHead, 250.0f, 84.0f, 1.0f, 1.0f);

                    dm_virus_anime(&game_state_data[0], game_map_data[0]);
                    dm_game_graphic_1p(&game_state_data[0], 0, game_map_data[0]);
                    _disp_coin_logo(&gGfxHead, temp_s7->unk_378);

                    gSPDisplayList(gGfxHead++, alpha_texture_init_dl);

                    draw_count_number(&gGfxHead, 0, 7, evs_high_score, 0x1D, 0x27);
                    draw_count_number(&gGfxHead, 0, 7, game_state_data[0].game_score, 0x1D, 0x43);

                    gSPDisplayList(gGfxHead++, alpha_texture_init_dl);

                    switch (evs_gamemode) {
                        case GMD_NORMAL:
                            draw_virus_number(&gGfxHead, game_state_data[0].virus_level, 0xFE, 0x7E, 1.0f, 1.0f);
                            break;

                        default:
                            break;
                    }

                    switch (evs_gamemode) {
                        case GMD_TaiQ:
                        case GMD_NORMAL:
                            func_8006A098(&gGfxHead, evs_game_time, RO_800B1D28[0], RO_800B1D28[1]);
                            break;

                        case GMD_TIME_ATTACK:
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
                        case GMD_TaiQ:
                            i = game_state_data[0].total_erase_count;
                            break;

                        default:
                            i = game_state_data[0].virus_number;
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
            if (!debugMenuEnabled && (temp_s7->unk_880 == 0)) {
                disp_logo_setup(&gGfxHead);

                gSPDisplayList(gGfxHead++, alpha_texture_init_dl);

                for (i = 0; i < 2; i++) {
                    draw_virus_number(&gGfxHead, game_state_data[i].virus_number, _posP2VirusNum[i][0],
                                      _posP2VirusNum[i][1], 1.0f, 1.0f);
                }

                switch (evs_gamemode) {
                    case GMD_TIME_ATTACK:
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
                    for (i = cached = 0; i < 2U; i++) {
                        if (temp_s7->unk_89C[i] == 0) {
                            func_800695A8(&gGfxHead, _posStStar[i][0], _posStStar[i][1], cached);
                            cached++;
                        }
                    }
                } else {
                    for (i = 0; i < ARRAY_COUNT(watchGame->unk_8B4); i++) {
                        draw_count_number(&gGfxHead, 0, 2, temp_s7->unk_8B4[i], _x_6416[i], 0x98);
                    }

                    for (i = cached = 0; i < 2; i++) {
                        for (j = temp_s7->unk_89C[i]; j < evs_vs_count; j++) {
                            func_800695A8(&gGfxHead, _posP2StarX[i], _posP2StarY[evs_vs_count - 1][j], cached);
                            cached++;
                        }
                    }
                }

                switch (evs_gamemode) {
                    case GMD_FLASH:
                        var_s6 = &temp_s7->unk_43C[7];
                        break;

                    default:
                        var_s6 = &temp_s7->unk_43C[0xF];
                        break;
                }
                var_t2 = &temp_s7->unk_43C[1];

                StretchAlphaTexBlock(&gGfxHead, var_s6->info[TI_INFO_IDX_WIDTH], var_s6->info[TI_INFO_IDX_HEIGHT],
                                     var_s6->texs[TI_TEX_TEX], var_s6->info[TI_INFO_IDX_WIDTH],
                                     var_t2->texs[TI_TEX_TEX], var_t2->info[TI_INFO_IDX_WIDTH], 131.0f, 181.0f,
                                     var_s6->info[TI_INFO_IDX_WIDTH], var_s6->info[TI_INFO_IDX_HEIGHT]);

                func_80069188(&temp_s7->unk_070, temp_s7->unk_06C);
                starForce_draw(&temp_s7->unk_070, &gGfxHead, temp_s7->unk_06C);

                for (i = 0; i < 2; i++) {
                    animeState_initDL(&game_state_data[i].anime, &gGfxHead);
                    animeState_draw(&game_state_data[i].anime, &gGfxHead, _posP2CharFrm[i][0], _posP2CharFrm[i][1],
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
            if (!debugMenuEnabled && (temp_s7->unk_880 == 0)) {
                for (i = 0; i < 4; i++) {
                    animeState_initDL(&game_state_data[i].anime, &gGfxHead);
                    animeState_draw(&game_state_data[i].anime, &gGfxHead, _posP4CharBase[i][0] + 0x14,
                                    _posP4CharBase[i][1] + 0x28, 1.0f, 1.0f);
                }

                disp_logo_setup(&gGfxHead);

                gSPDisplayList(gGfxHead++, alpha_texture_init_dl);

                for (i = 0; i < 4; i++) {
                    draw_virus_number(&gGfxHead, game_state_data[i].virus_number, _posP4CharBase[i][0] + 0x32,
                                      _posP4CharBase[i][1] + 0x1D, 1.0f, 1.0f);
                }

                if (evs_story_flg != 0) {
                    func_8006A098(&gGfxHead, evs_game_time, 0x3B, 0x12);

                    for (i = cached = 0; i < 4U; i++) {
                        if (temp_s7->unk_89C[i] == 0) {
                            func_800695A8(&gGfxHead, _posStP4StarX[i], 0xD, cached);
                            cached++;
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

                    temp_s5 = var_s6->info[TI_INFO_IDX_WIDTH] >> 1;
                    temp_s2_4 = var_s6->info[TI_INFO_IDX_HEIGHT] / 3;

                    for (i = 0; i < 2; i++) {
                        for (j = 0; j < 4; j++) {
                            temp_a3_10 = temp_s7->unk_8DC[i][j];
                            if (temp_a3_10 < 0) {
                                continue;
                            }

                            a = temp_s5 * i;
                            b = temp_s2_4 * color2index_6470[temp_a3_10];

                            StretchAlphaTexTile(&gGfxHead, var_s6->info[TI_INFO_IDX_WIDTH],
                                                var_s6->info[TI_INFO_IDX_HEIGHT], var_s6->texs[TI_TEX_TEX],
                                                var_s6->info[TI_INFO_IDX_WIDTH], var_t2->texs[TI_TEX_TEX],
                                                var_t2->info[TI_INFO_IDX_WIDTH], a, b, temp_s5, temp_s2_4,
                                                _posP4StockCap[i][0] + j * 9, _posP4StockCap[i][1], temp_s5, temp_s2_4);
                        }
                    }

                    for (i = cached = 0; i < 2; i++) {
                        for (j = temp_s7->unk_89C[i]; j < evs_vs_count; j++) {
                            func_800695A8(&gGfxHead, _posP4TeamStarX[evs_vs_count - 1][i][j], 0xD, cached);
                            cached++;
                        }
                    }
                } else {
                    for (i = cached = 0; i < 4; i++) {
                        for (j = temp_s7->unk_89C[i]; j < evs_vs_count; j++) {
                            func_800695A8(&gGfxHead, _posP4CharStarX[evs_vs_count - 1][i][j], 0xD, cached);
                            cached++;
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
        switch (game_state_data[0].mode_now) {
            case dm_mode_debug:
                DebugMenu_Settings_Draw(&gGfxHead);
                DebugMenu_Settings_Update();
                break;

            case dm_mode_debug_config:
                DebugMenu_CharacterEdit_Update();
                DebugMenu_CharacterEdit_Draw(&gGfxHead);
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

            gDPLoadTextureBlock_4b(gGfxHead++, var_s6->texs[TI_TEX_TEX], G_IM_FMT_I, var_s6->info[TI_INFO_IDX_WIDTH],
                                   var_s6->info[TI_INFO_IDX_HEIGHT], 0, G_TX_NOMIRROR, G_TX_NOMIRROR, G_TX_NOMASK,
                                   G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

            drawCursorPattern(&gGfxHead, var_s6->info[TI_INFO_IDX_WIDTH], var_s6->info[TI_INFO_IDX_HEIGHT], 0x10, 0x10,
                              temp_s7->unk_A28.posX - 6, temp_s7->unk_A28.posY - 6,
                              (temp_s7->unk_A28.colStep * 0x14) + 0xC, (temp_s7->unk_A28.rowStep * 3) + 0xC);

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
            if (game_state_data[i].cnd_static == dm_cnd_pause) {
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

        watchGameP->unk_40C = (evs_gamemode == GMD_TaiQ) && (joygam[0] & (L_TRIG | R_TRIG));

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

void func_80071A44(void) {
}

/**
 * Original name: main_techmes
 */
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
    watchGameP->messageWnd.fontType = FONTTYPE_1;
    watchGameP->messageWnd.centering = true;

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

    return MAIN_TITLE;
}

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

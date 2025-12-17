/**
 * Original filename: dm_game_main.c
 */

#include "dm_game_main.h"

#include "defines.h"
#include "macros_defines.h"

#include "libc/assert.h"
#include "libc/stdbool.h"
#include "gcc/memory.h"

#include "066580.h"
#include "aiset.h"
#include "audio/sound.h"
#include "bg_tasks.h"
#include "buffers.h"
#include "calc.h"
#include "debug_menu.h"
#include "dm_main_cnt.h"
#include "dm_thread.h"
#include "dm_virus_init.h"
#include "game_etc.h"
#include "graphic.h"
#include "main1x.h"
#include "main_story.h"
#include "nnsched.h"
#include "record.h"
#include "replay.h"
#include "rom_offsets.h"
#include "static.h"
#include "tex_func.h"
#include "util.h"
#include "vr_init.h"

#if VERSION_US || VERSION_GW || CC_CHECK
#else
#define AVOID_JOY_FUNCTIONS 1
#endif
#include "joy.h"

#if VERSION_CN && !CC_CHECK
void joyCursorFastSet(u16 mask, u8 index);
#endif

// Maybe it is checking if player0 is non-human? or maybe debug related?
#define UNK_PLAYER0_CHECK2(state, player_no) \
    (((state)->player_type != PLAYERTYPE_1) && ((player_no) == 0) && (aiDebugP1 >= 0))

#define UNK_PLAYER0_CHECK(state, player_no) \
    (((state)->player_type == PLAYERTYPE_1) || UNK_PLAYER0_CHECK2(state, player_no))

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

typedef struct StarForce {
    /* 0x00 */ s32 *xtbl;       /* Original name: xtbl */
    /* 0x04 */ s32 *ytbl;       /* Original name: ytbl */
    /* 0x08 */ s32 frame[0x10]; /* Original name: frame */
} StarForce;                    // size = 0x48

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

typedef enum RetryType {
    /* 0x0 */ RETRYTYPE_0,
    /* 0x1 */ RETRYTYPE_1,
    /* 0x2 */ RETRYTYPE_2,
    /* 0x3 */ RETRYTYPE_3,
    /* 0x4 */ RETRYTYPE_4,
    /* 0x5 */ RETRYTYPE_5,
    /* 0x6 */ RETRYTYPE_MAX,
} RetryType;

#define STAR_POS_LEN 12U
#define FRAME_MOVEMENT_MAX 20

typedef struct struct_watchGame {
    /* 0x000 */ bool replayFlag;                                                 /* Original name: replayFlag */
    /* 0x004 */ s32 randSeed;                                                    /* Original name: randSeed */
    /* 0x008 */ s32 randSeed2;                                                   /* Original name: randSeed2 */
    /* 0x00C */ s32 star_pos_x[STAR_POS_LEN]; /* Original name: star_pos_x */    /* Indexed by star_count */
    /* 0x03C */ s32 star_pos_y[STAR_POS_LEN]; /* Original name: star_pos_y */    /* Indexed by star_count */
    /* 0x06C */ s32 star_count;                                                  /* Original name: star_count */
    /* 0x070 */ StarForce starForce;                                             /* Original name: starForce */
    /* 0x0B8 */ ScoreNums scoreNums[MAX_PLAYERS];                                /* Original name: scoreNums */
    /* 0x348 */ s32 retry_type[MAX_PLAYERS]; /* Original name: retry_type */     /* Type: RetryType */
    /* 0x358 */ s32 retry_select[MAX_PLAYERS]; /* Original name: retry_select */ // TODO: enum
    /* 0x368 */ EtcPartIndex retry_result[MAX_PLAYERS];                          /* Original name: retry_result */
    /* 0x378 */ s32 retry_coin;                                                  /* Original name: retry_coin */
    /* 0x37C */ s32 force_draw_capsel_count[MAX_PLAYERS]; /* Original name: force_draw_capsel_count */
    /* 0x38C */ s32 curtain_count;                        /* Original name: curtain_count */
    /* 0x390 */ s32 curtain_step;                         /* Original name: curtain_step */
    /* 0x394 */ s32 frame_move_count;                     /* Original name: frame_move_count */
    /* 0x398 */ s32 frame_move_step;                      /* Original name: frame_move_step */
    /* 0x39C */ s32 face_anime_count[4]; /* unused */     /* Original name: face_anime_count */
    /* 0x3AC */ s32 count_down_ctrl;                      /* Original name: count_down_ctrl */
    /* 0x3B0 */ bool eep_rom_flg;                         /* Original name: eep_rom_flg */
    /* 0x3B4 */ bool bgm_bpm_flg[2];                      /* Original name: bgm_bpm_flg */
    /* 0x3BC */ s32 last_3_se_cnt;                        /* Original name: last_3_se_cnt */
    /* 0x3C0 */ bool last_3_se_flg;                       /* Original name: last_3_se_flg */
    /* 0x3C4 */ bool started_game_flg;                    /* Original name: started_game_flg */
    /* 0x3C8 */ f32 big_virus_wait;                       /* Original name: big_virus_wait */
    /* 0x3CC */ f32 big_virus_timer;                      /* Original name: big_virus_timer */
    /* 0x3D0 */ f32 big_virus_pos[ANIMES_COUNT][2];       /* Original name: big_virus_pos */
    /* 0x3E8 */ f32 big_virus_rot[ANIMES_COUNT];          /* Original name: big_virus_rot */
    /* 0x3F4 */ f32 big_virus_scale[ANIMES_COUNT];        /* Original name: big_virus_scale */
    /* 0x400 */ bool big_virus_flg[ANIMES_COUNT];         /* Original name: big_virus_flg */
    /* 0x40C */ bool big_virus_no_wait;                   /* Original name: big_virus_no_wait */
    /* 0x410 */ s32 big_virus_stop_count;                 /* Original name: big_virus_stop_count */
    /* 0x414 */ s32 big_virus_blink_count; /* Original name: big_virus_blink_count */ /* unused */
    /* 0x418 */ u8 big_virus_count[ANIMES_COUNT];                        /* Original name: big_virus_count */
    /* 0x41C */ s32 demo_timer;                                          /* Original name: demo_timer */
    /* 0x420 */ bool demo_flag;                                          /* Original name: demo_flag */
    /* 0x424 */ s32 blink_count;                                         /* Original name: blink_count */
    /* 0x428 */ s32 warning_se_count;                                    /* Original name: warning_se_count */
    /* 0x42C */ UNUSED_MEMBER(void *objSeg); /* Original name: objSeg */ /* Completely unreferenced */
    /* 0x430 */ TiTexData *texAL; /* Original name: texAL */             // TODO: make enums to index these bunch
    /* 0x434 */ TiTexData *texLS;                                        /* Original name: texLS */
    /* 0x438 */ TiTexData *texP1;                                        /* Original name: texP1 */
    /* 0x43C */ TiTexData *texP2;                                        /* Original name: texP2 */
    /* 0x440 */ TiTexData *texP4;                                        /* Original name: texP4 */
    /* 0x444 */ TiTexData *texItem;                                      /* Original name: texItem */
    /* 0x448 */ TiTexData *texKaSa;                                      /* Original name: texKaSa */
    /* 0x44C */ SAnimeState virus_anime_state[ANIMES_COUNT];             /* Original name: virus_anime_state */
    /* 0x50C */ SAnimeSmog virus_smog_state[ANIMES_COUNT];               /* Original name: virus_smog_state */
    /* 0x878 */ s32 graphic_thread_pri;                                  /* Original name: graphic_thread_pri */
    /* 0x87C */ u16 *bg_snap_buf;                                        /* Original name: bg_snap_buf */
    /* 0x880 */ bool bg_snapping;                                        /* Original name: bg_snapping */
    /* 0x884 */ void *gameEtcSeg;                                        /* Original name: effect_data_buf */
    /* 0x888 */ s32 effect_timer[MAX_PLAYERS];                           /* Original name: effect_timer */
    /* 0x898 */ s32 touch_down_wait;                                     /* Original name: touch_down_wait */
    /* 0x89C */ s32 win_count[TEAMNUMBER_MAX];
    /* Original name: win_count */ /* Indexed by TeamNumber/`struct_game_state_data::team_no` */
    /* 0x8AC */ s32 vs_win_count[EVS_SELECT_NAME_NO_COUNT]; /* Original name: vs_win_count */
    /* 0x8B4 */ s32 vs_win_total[2];                        /* Original name: vs_win_total */
    /* 0x8BC */ s32 vs_4p_player_count;                     /* Original name: vs_4p_player_count */
    /* 0x8C0 */ bool vs_4p_team_flg;                        /* Original name: vs_4p_team_flg */
    /* 0x8C4 */ u32 vs_4p_team_bits[2];                     /* Original name: vs_4p_team_bits */
    /* 0x8CC */ s32 story_4p_name_num[TEAMNUMBER_MAX];
    /* Original name: story_4p_name_num */ // Indexed by TeamNumber/`struct_game_state_data::team_no`
    /* 0x8DC */ s32 story_4p_stock_cap[TEAMNUMBER_MAX][4];
    /* Original name: story_4p_stock_cap */ // Outer indexed by TeamNumber/`struct_game_state_data::team_no`
    /* 0x91C */ MessageWnd msgWnd;          /* Original name: msgWnd */
    /* 0x99C */ s32 coin_count;             /* Original name: coin_count */
    /* 0x9A0 */ s32 coin_time[3];           /* Original name: coin_time */
    /* 0x9AC */ s32 coffee_break_flow; /* Original name: coffee_break_flow */   // TODO: enum?
    /* 0x9B0 */ s32 coffee_break_timer;                                         /* Original name: coffee_break_timer */
    /* 0x9B4 */ s32 coffee_break_level; /* Original name: coffee_break_level */ // TODO: enum
    /* 0x9B8 */ s32 coffee_break_shard; /* Original name: coffee_break_shard */ // TODO: enum
    /* 0x9BC */ bool bottom_up_flag;                                            /* Original name: bottom_up_flag */
    /* 0x9C0 */ bool query_play_pause_se;                                       /* Original name: query_play_pause_se */
    /* 0x9C4 */ s32 query_pause_player_no;            /* Original name: query_pause_player_no */
    /* 0x9C8 */ s32 query_debug_player_no;            /* Original name: query_debug_player_no */
    /* 0x9CC */ s32 query_config_player_no;           /* Original name: query_config_player_no */
    /* 0x9D0 */ TimeAttackResult timeAttackResult[2]; /* Original name: timeAttackResult */
    /* 0xA28 */ MessageWnd passWnd;                   /* Original name: passWnd */
    /* 0xAA8 */ s32 passAlphaStep;                    /* Original name: passWnd */
    /* 0xAAC */ unsigned char passBuf[42];            /* Original name: passBuf */
    /* 0xAD8 */ RecordWritingMessage writingMsg;      /* Original name: writingMsg */
} struct_watchGame;                                   // size = 0xB60

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

typedef struct GameStateBackup {
    /* 0x0000 */ struct_watchGame game;                                          /* Original name: game */
    /* 0x0B60 */ struct_game_state_data state[MAX_PLAYERS];                      /* Original name: state */
    /* 0x1A70 */ GameMapCell map[MAX_PLAYERS][GAME_MAP_ROWS * GAME_MAP_COLUMNS]; /* Original name: map */
    /* 0x2FB0 */ s32 highScore;                                                  /* Original name: highScore */
    /* 0x2FB4 */ s32 gameTime;                                                   /* Original name: gameTime */
} GameStateBackup;                                                               // size = 0x2FB8

/**
 * Original name: gameBackup
 */
GameStateBackup *gameBackup[2];

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
bool dm_think_flg = false;
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
            case GSL_1PLAY:
                level = state->cap_def_speed;
                break;

            case GSL_2PLAY:
                level = state->cap_def_speed;
                break;

            case GSL_4PLAY:
                level = state->cap_def_speed;
                break;

            case GSL_VSCPU:
                level = state->cap_def_speed;
                break;

            case GSL_1DEMO:
                level = state->cap_def_speed;
                break;

            case GSL_2DEMO:
                level = state->cap_def_speed;
                break;

            case GSL_4DEMO:
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
        case GSL_1PLAY:
            dm_snd_play_in_game(SND_INDEX_59);
            break;

        case GSL_2PLAY:
        case GSL_VSCPU:
            dm_snd_play_in_game(dm_chaine_se_table_vs_178[player_no]);
            break;

        case GSL_4PLAY:
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
    if (state->cnd_static == dm_cnd_game_over) {
        return true;
    }
    return false;
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

    return &ptr->virus_anime_state[index];
}

/**
 * Original name: get_virus_smog_state
 */
SAnimeSmog *get_virus_smog_state(s32 index) {
    struct_watchGame *ptr = watchGame;

    return &ptr->virus_smog_state[index];
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
    2, // RETRYTYPE_0
    3, // RETRYTYPE_1
    2, // RETRYTYPE_2
    3, // RETRYTYPE_3
    2, // RETRYTYPE_4
    3, // RETRYTYPE_5
};
static_assert(ARRAY_COUNT(_retryMenu_itemCount) == RETRYTYPE_MAX, "");

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
        x += 7;
        num->pos[1] = y;
        num->number = column[i];
        num->color = color;
        num->time = 0.0f;
        st->index = WrapI(0, ARRAY_COUNT(st->numbers), st->index + 1);
    }
}

/**
 * Original name: backup_game_state
 */
void backup_game_state(s32 bufNo) {
    GameStateBackup *bak = gameBackup[bufNo];
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
    GameStateBackup *bak = gameBackup[bufNo];
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

    if (!st->replayFlag) {
        backup_game_state(1);
    }

    resume_game_state(0);
    st->replayFlag = true;
}

/**
 * Original name: reset_replay_state
 */
void reset_replay_state(void) {
    struct_watchGame *st = watchGame;

    if (st->replayFlag) {
        resume_game_state(1);
        st->replayFlag = false;
    }
}

/**
 * Original name: start_replay_proc
 */
void start_replay_proc(void) {
    if (watchGame->replayFlag) {
        replay_play_init();
    } else {
        replay_record_init(evs_playcnt);
    }
}

/**
 * Original name: dm_warning_h_line_se
 */
void dm_warning_h_line_se(void) {
    struct_watchGame *st = watchGame;
    s32 warning = 0;
    s32 i;

    for (i = 0; i < evs_playcnt; i++) {
        if (game_state_data[i].cnd_static == dm_cnd_wait) {
            if (game_state_data[i].warning_se_flag) {
                warning++;
            }
        }
    }

    if (warning == 0) {
        st->warning_se_count = 0;
    } else {
        st->warning_se_count++;

        if (st->warning_se_count == 1) {
            dm_snd_play_in_game(SND_INDEX_79);
        } else if (st->warning_se_count >= 300) {
            st->warning_se_count = 0;
        }
    }
}

/**
 * Original name: dm_play_count_down_se
 */
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
void dm_capsel_down(struct_game_state_data *state, GameMapCell *map) {
    struct_watchGame *st = watchGame;
    struct_game_state_data_now_cap *cap = &state->now_cap;
    s32 i;
    s32 j;

    if (cap->pos_y[0] > 0) {
        i = FallSpeed[state->cap_speed];
        if ((cap->pos_y[0] < 4) && (cap->pos_y[0] > 0)) {
            i += BonusWait[cap->pos_y[0] - 1][state->cap_def_speed];
        }
        j = 0;
        if (get_map_info(map, state->now_cap.pos_x[0], cap->pos_y[0] + 1) != 0) {
            j = st->touch_down_wait;
        }
        state->cap_speed_max = i + j;
    } else {
        state->cap_speed_max = 30;
    }

    state->cap_speed_count = state->cap_speed_count + state->cap_speed_vec;
    if (state->cap_speed_count < state->cap_speed_max) {
        return;
    }

    state->cap_speed_count = 0;
    if (cap->capsel_flg_0 == 0) {
        return;
    }

    if (cap->pos_y[0] > 0) {
        if (cap->pos_x[0] == cap->pos_x[1]) {
            if (get_map_info(map, cap->pos_x[0], cap->pos_y[0] + 1) != 0) {
                cap->capsel_flg_1 = 0;
            }
        } else {
            for (j = 0; j < ARRAY_COUNTU(cap->pos_x); j++) {
                if (get_map_info(map, cap->pos_x[j], cap->pos_y[j] + 1) != 0) {
                    cap->capsel_flg_1 = 0;
                    break;
                }
            }
        }
    }

    for (i = 0; i < ARRAY_COUNTU(cap->pos_y); i++) {
        if (cap->pos_y[i] == 0x10) {
            cap->capsel_flg_1 = 0;
            break;
        }
    }

    if (cap->capsel_flg_1 != 0) {
        for (i = 0; i < ARRAY_COUNTU(cap->pos_y); i++) {
            if (cap->pos_y[i] < 0x10) {
                cap->pos_y[i]++;
            }
        }

        for (i = 0; i < ARRAY_COUNTU(cap->pos_x); i++) {
            if (get_map_info(map, cap->pos_x[i], cap->pos_y[i]) != 0) {
                state->cnd_static = dm_cnd_game_over;
                state->next_cap.capsel_flg_0 = 0;
                cap->capsel_flg_1 = 0;
                break;
            }
        }

        if (cap->capsel_flg_1 != 0) {
            return;
        }
    }

    dm_snd_play_in_game(SND_INDEX_66);
    state->mode_now = dm_mode_down_wait;
    cap->capsel_flg_0 = 0;

    for (i = 0; i < ARRAY_COUNTU(cap->pos_y); i++) {
        if (cap->pos_y[i] != 0) {
            set_map(map, cap->pos_x[i], cap->pos_y[i], cap->casel_g[i],
                    cap->capsel_p[i] + black_color_1384[state->flg_game_over]);
        }
    }
}

/**
 * Original name: dm_capsel_down
 */
s32 dm_make_attack_pattern(u32 max) {
    s32 pattern = 0;

    if (max >= 4) {
        pattern = 0x55 << random(2);
    } else if (max >= 3) {
        pattern = 0x15 << random(4);
    } else if (max >= 2) {
        pattern = 0x11 << random(4);
    }
    return pattern;
}

/**
 * Original name: dm_set_attack_2p
 */
s32 dm_set_attack_2p(struct_game_state_data *state) {
    struct_game_state_data *enemy;
    s32 temp_v0;
    s32 var_s0;
    s32 pattern;
    s32 var_t1;
    s32 var_a0;
    s32 i;

#if 0
    int x; // r5
    int flag; // r6
    int c; // r1+0x8
#endif

    if (state->chain_line < 2) {
        return 0;
    }

    enemy = &game_state_data[state->player_no ^ 1];

    var_a0 = MIN(4, state->chain_line);

    for (i = 0; i < 1; i++) {
        if (enemy->cap_attack_work[i].unk_0 != 0) {
            pattern = 0;
            for (var_s0 = 0; var_s0 < 8; var_s0++) {
                if (enemy->cap_attack_work[i].unk_0 & (3 << (var_s0 << 1))) {
                    pattern |= 1 << var_s0;
                    var_t1 = var_s0 & 1;
                }
            }

            for (var_s0 = 0; var_s0 < 8; var_s0++) {
                if ((var_s0 & 1) == var_t1) {
                    pattern ^= 1 << var_s0;
                }
            }

            if (pattern == 0) {
                continue;
            }
        } else {
            pattern = dm_make_attack_pattern(var_a0);
        }

        enemy->cap_attack_work[i].unk_2 = state->player_no;

        for (var_s0 = 0; var_s0 < 8; var_s0++) {
            if (!((pattern >> var_s0) & 1)) {
                continue;
            }

            while ((state->chain_color[0] != 0) || (state->chain_color[1] != 0) || (state->chain_color[2] != 0)) {
                temp_v0 = random(3);
                if (state->chain_color[temp_v0] != 0) {
                    state->chain_color[temp_v0] -= 1;
                    enemy->cap_attack_work[i].unk_0 |= (temp_v0 + 1) << (var_s0 << 1);
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
s32 dm_set_attack_4p(struct_game_state_data *state) {
    struct_watchGame *st = watchGame;
    struct_game_state_data *enemy;
#define WORK_LEN 3U
    s32 work[WORK_LEN];
    s32 attackWork[WORK_LEN];
    s32 attackFlag;
    s32 stockFlag;
    s32 temp_v0_3;
    s32 var_a1_2;
    s32 chainCount;
    s32 var_s1_2;
    s32 j;
    s32 i;

#if 0
    int c; // r1+0x8
    int x; // r18
#endif

    if (state->chain_line < 2) {
        return 0;
    }

    for (i = 0; i < ARRAY_COUNTU(attackWork); i++) {
        attackWork[i] = 0;
    }

    chainCount = 0;

    stockFlag = 0;
    attackFlag = 0;
    for (i = 0; i < ARRAY_COUNT(attack_table_1531[0]); i++) {
        if (!((state->chain_color[3] >> i) & 1)) {
            continue;
        }

        enemy = &game_state_data[attack_table_1531[state->player_no][i]];
        if (enemy->team_no == state->team_no) {
            if (enemy->flg_retire) {
                continue;
            }
            stockFlag |= 1 << attack_table_1531[state->player_no][i];
        } else {
            if (enemy->flg_retire && ((enemy->cnd_training != dm_cnd_training) || !enemy->flg_training)) {
                continue;
            }
            attackFlag |= 1 << attack_table_1531[state->player_no][i];
        }

        if (chainCount > 0) {
            continue;
        }

        chainCount = MIN(4, state->chain_line);

        for (j = 0; j < ARRAY_COUNTU(st->story_4p_stock_cap[state->team_no]); j++) {
            if (chainCount >= 4) {
                break;
            }

            if (st->story_4p_stock_cap[state->team_no][j] != -1) {
                state->chain_color[st->story_4p_stock_cap[state->team_no][j]]++;
                st->story_4p_stock_cap[state->team_no][j] = -1;
                chainCount++;
            }
        }

        for (j = 0; j < chainCount;) {
            if ((state->chain_color[0] + state->chain_color[1] + state->chain_color[2]) <= 0) {
                break;
            }
            temp_v0_3 = random(WORK_LEN);
            if (state->chain_color[temp_v0_3] != 0) {
                state->chain_color[temp_v0_3]--;
                attackWork[temp_v0_3]++;
                j++;
            }
        }
    }

    if ((attackFlag + stockFlag) == 0) {
        return 0;
    }

    for (i = 0; i < ARRAY_COUNT(game_state_data); i++) {
        if (!((attackFlag >> i) & 1)) {
            continue;
        }

        enemy = &game_state_data[i];

        add_attack_effect(state->player_no, _posP4CharBase[state->player_no][0], _posP4CharBase[state->player_no][1],
                          _posP4CharBase[enemy->player_no][0], _posP4CharBase[enemy->player_no][1]);

        for (j = 0; j < ARRAY_COUNTU(work); j++) {
            work[j] = attackWork[j];
        }

        for (j = 0; j < ARRAY_COUNT(enemy->cap_attack_work); j++) {
            if (enemy->cap_attack_work[j].unk_0 != 0) {
                continue;
            }

            var_a1_2 = dm_make_attack_pattern(chainCount);

            enemy->cap_attack_work[j].unk_2 = state->player_no;
            for (var_s1_2 = 0; var_s1_2 < 8; var_s1_2++) {
                if (!((var_a1_2 >> var_s1_2) & 1)) {
                    continue;
                }

                while ((work[0] + work[1] + work[2]) > 0) {
                    temp_v0_3 = random(3);
                    if (work[temp_v0_3] > 0) {
                        work[temp_v0_3]--;
                        enemy->cap_attack_work[j].unk_0 |= (temp_v0_3 + 1) << (var_s1_2 * 2);
                        break;
                    }
                }
            }
        }
    }

    j = 0;

    for (i = 0; i < ARRAY_COUNT(st->story_4p_stock_cap[state->team_no]); i++) {
        if (st->story_4p_stock_cap[state->team_no][i] == -1) {
            continue;
        }

        st->story_4p_stock_cap[state->team_no][j] = st->story_4p_stock_cap[state->team_no][i];
        j += 1;
    }

    for (; j < ARRAY_COUNT(st->story_4p_stock_cap[state->team_no]); j++) {
        st->story_4p_stock_cap[state->team_no][j] = -1;
    }

    for (i = 0; i < 4; i++) {
        if (!((stockFlag >> i) & 1)) {
            continue;
        }

        for (j = 0; j < WORK_LEN; j++) {
            work[j] = attackWork[j];
        }

        temp_v0_3 = 0;
        for (j = 0; j < ARRAY_COUNT(st->story_4p_stock_cap[state->team_no]); j++) {
            if (st->story_4p_stock_cap[state->team_no][j] != -1) {
                continue;
            }

            for (; temp_v0_3 < ARRAY_COUNT(work); temp_v0_3++) {
                if (work[temp_v0_3] > 0) {
                    work[temp_v0_3]--;
                    st->story_4p_stock_cap[state->team_no][j] = temp_v0_3;
                    break;
                }
            }
        }
    }

    return 1;
#undef WORK_LEN
}

/**
 * Original name: load_visible_fall_point_flag
 */
void load_visible_fall_point_flag(void) {
    s32 i;
    s32 j;

    switch (evs_gamesel) {
        case GSL_1PLAY:
        case GSL_VSCPU:
            j = 1;
            break;

        case GSL_2PLAY:
            j = 2;
            break;

        default:
            j = 0;
            break;
    }

    for (i = 0; i < j; i++) {
        struct_evs_mem_data *ptr = &evs_mem_data[evs_select_name_no[i]];

        visible_fall_point[i] = (ptr->mem_use_flg & MEM_USE_FLG_2) ? 1 : 0;
    }
}

/**
 * Original name: save_visible_fall_point_flag
 */
void save_visible_fall_point_flag(void) {
    s32 i;
    s32 j;

    switch (evs_gamesel) {
        case GSL_1PLAY:
        case GSL_VSCPU:
            j = 1;
            break;

        case GSL_2PLAY:
            j = 2;
            break;

        default:
            j = 0;
            break;
    }

    for (i = 0; i < j; i++) {
        struct_evs_mem_data *mc = &evs_mem_data[evs_select_name_no[i]];

        mc->mem_use_flg &= ~MEM_USE_FLG_2;
        if (visible_fall_point[i] != 0) {
            mc->mem_use_flg |= MEM_USE_FLG_2;
        }
    }
}

/**
 * Original name: retryMenu_init
 */
void retryMenu_init(s32 playerNo, RetryType type) {
    struct_watchGame *st = watchGame;

    st->retry_type[playerNo] = type;
    st->retry_select[playerNo] = 0;
    st->retry_result[playerNo] = ETC_PART_INDEX_GRAPHBIN_INVALID;

    switch (st->retry_type[playerNo]) {
        case RETRYTYPE_2:
        case RETRYTYPE_3:
        case RETRYTYPE_4:
        case RETRYTYPE_5:
            st->retry_select[playerNo]++;
            break;

        default:
            break;
    }
}

/**
 * Original name: retryMenu_initPauseLogo
 */
void retryMenu_initPauseLogo(s32 playerNo) {
    retryMenu_init(playerNo, RETRYTYPE_0);
}

/**
 * Original name: retryMenu_input
 */
EtcPartIndex retryMenu_input(s32 playerNo) {
    struct_watchGame *st = watchGame;
    s32 direction = 0; //
    SndIndex sound = SND_INDEX_INVALID;
    EtcPartIndex result = ETC_PART_INDEX_GRAPHBIN_INVALID;
    u16 curButton = joycur[main_joy[playerNo]];                        //
    u16 pressedButton = gControllerPressedButtons[main_joy[playerNo]]; //
    s32 select;

#if 0
    int rep; // r27
    int trg; // r26
    int vy; // r25
#endif

    st->retry_select[playerNo] = WrapI(0, _retryMenu_itemCount[st->retry_type[playerNo]], st->retry_select[playerNo]);

    if (curButton & U_JPAD) {
        direction--;
    }
    if (curButton & D_JPAD) {
        direction++;
    }

    select = WrapI(0, _retryMenu_itemCount[st->retry_type[playerNo]], st->retry_select[playerNo] + direction);
    if (select != st->retry_select[playerNo]) {
        st->retry_select[playerNo] = select;
        sound = SND_INDEX_64;
    } else if (pressedButton & (A_BUTTON | START_BUTTON)) {
        result = st->retry_result[playerNo];
    }

    if (sound > SND_INDEX_INVALID) {
        dm_snd_play_in_game(sound);
    }

    return result;
}

/**
 * Original name: retryMenu_drawPause
 */
void retryMenu_drawPause(s32 playerNo, Gfx **gfxP, bool dispMenu) {
    struct_watchGame *st = watchGame;
    Gfx *gfx = *gfxP;

    if (st->retry_type[playerNo] <= RETRYTYPE_1) {
        if (st->retry_type[playerNo] >= RETRYTYPE_0) {
            st->retry_result[playerNo] = disp_pause_logo(&gfx, playerNo, 0, dispMenu ? st->retry_select[playerNo] : -1,
                                                         st->retry_type[playerNo] - RETRYTYPE_0);
        }
    }

    *gfxP = gfx;
}

/**
 * Original name: retryMenu_drawContinue
 */
void retryMenu_drawContinue(s32 playerNo, Gfx **gfxP) {
    struct_watchGame *st = watchGame;
    Gfx *gfx = *gfxP;

    if (st->retry_type[playerNo] <= RETRYTYPE_5) {
        if (st->retry_type[playerNo] >= RETRYTYPE_2) {
            if ((evs_gamesel == GSL_2PLAY) && (evs_gamemode == GMD_TIME_ATTACK)) {
                st->retry_result[playerNo] = disp_continue_logo_score(&gfx, playerNo, st->retry_select[playerNo],
                                                                      st->retry_type[playerNo] - RETRYTYPE_2);
            } else {
                st->retry_result[playerNo] = disp_continue_logo(&gfx, playerNo, st->retry_select[playerNo],
                                                                st->retry_type[playerNo] - RETRYTYPE_2);
            }
        }
    }

    *gfxP = gfx;
}

/**
 * Original name: set_bottom_up_virus
 */
void set_bottom_up_virus(struct_game_state_data *state, GameMapCell *map) {
    u8 work[GAME_MAP_COLUMNS];
    s32 col;
    s32 cellIndex;
    s32 var_s2;
    s32 cellEnd;
    s32 sp28[4];
    s32 sp38[4];
    s32 sp48[4];
    s32 temp_v0_2;

#if 0
    int i; // r29
    int j; // r30
    int x; // r1+0x8
    int endI; // r1+0x8
    int color; // r6
    int mask[3]; // r1+0x30
    int flag[3]; // r1+0x24
    int pos[3]; // r1+0x18
#endif

    for (col = 0; col < 1 * GAME_MAP_COLUMNS; col++) {
        work[col] = 0;
    }

    cellEnd = (GAME_MAP_ROWS - 1) * GAME_MAP_COLUMNS;
    cellIndex = (GAME_MAP_ROWS - 2) * GAME_MAP_COLUMNS;
    col = 0;

    for (; cellIndex < cellEnd; cellIndex++, col++) {
        if (map[cellIndex].capsel_m_flg[0] == 0) {
            continue;
        }

        if (map[cellIndex].capsel_m_flg[4] >= 0) {
            continue;
        }

        work[col] = 1;
    }

    var_s2 = 0;

    for (col = 0; col < GAME_MAP_COLUMNS; col++) {
        if (random(100) < 75) {
            work[col] = 1;
        }
        if (work[col] != 0) {
            var_s2 += 1;
        }
    }

    if (var_s2 == 0) {
        work[random(8)] = 1;
    }

    cellEnd += 1 * GAME_MAP_COLUMNS;
    col = 0;

    for (; cellIndex < cellEnd; cellIndex++, col++) {
        if (work[col] == 0) {
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

            if (map[sp48[var_s2]].capsel_m_flg[0] != 0) {
                sp28[map[sp48[var_s2]].capsel_m_flg[3]] += 1;
            }
        }

        if ((sp28[0] != 0) && (sp28[1] != 0) && (sp28[2] != 0)) {
            continue;
        }

        do {
            temp_v0_2 = random(3);
        } while (sp28[temp_v0_2] != 0);

        set_virus(map, col, GAME_MAP_ROWS, temp_v0_2, virus_anime_table[temp_v0_2][state->virus_anime]);
    }
}

/**
 * Original name: bottom_up_bottle_items
 */
bool bottom_up_bottle_items(GameMapCell *map) {
    s32 i;
    bool ret = false;
    s32 column;
    GameMapCell *cell;
    s32 size;

    for (i = 0; i < GAME_MAP_COLUMNS; i++) {
        if (map[i].capsel_m_flg[0] != 0) {
            ret = true;
        }
    }

    size = (GAME_MAP_ROWS - 1) * GAME_MAP_COLUMNS;
    for (i = 0, cell = &map[GAME_MAP_GET_INDEX(1, 0)]; i < size; i++, cell++) {
        map[i] = *cell;
        map[i].pos_m_y--;
    }

    size += GAME_MAP_COLUMNS;
    for (column = 0; i < size; i++, column++) {
        bzero(&map[i], sizeof(GameMapCell));
        map[i].pos_m_x = column;
        map[i].pos_m_y = GAME_MAP_ROWS;
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
void add_taiQ_bonus_wait(struct_game_state_data *state) {
    struct_watchGame *st = watchGame;
    s32 count;
    s32 i;

    if (evs_gamemode != GMD_TaiQ) {
        return;
    }

    if (state->chain_line < 2) {
        return;
    }

    st->big_virus_wait += DOUBLE_LITERAL(0.25) * (s32)(state->chain_line - 1);
    st->big_virus_wait = MIN(st->big_virus_wait, _big_virus_max_wait[state->game_level]);

    count = _bonus_1884[0] * (state->erase_virus_count + state->chain_line);
    for (i = 1; i < state->chain_count; i++) {
        count += _bonus_1884[MIN(i, ARRAY_COUNTU(_bonus_1884) - 1)];
    }
    st->big_virus_stop_count += count;
}

/**
 * Original name: dm_check_one_game_finish
 */
bool dm_check_one_game_finish(void) {
    s32 i;

    for (i = 0; i < evs_playcnt; i++) {
        EnumGameStateDataCnd cnd = game_state_data[i].cnd_static;

        if ((cnd != dm_cnd_win) && (cnd != dm_cnd_lose) && (cnd != dm_cnd_draw)) {
            break;
        }
    }

    return (i ^ evs_playcnt) == 0;
}

/**
 * Original name: dm_game_eep_write_callback
 */
void dm_game_eep_write_callback(void *args) {
    struct_watchGame *watchGameP = args;
    RecordWritingMessage *recMessage = &watchGameP->writingMsg;
    s32 x;
    s32 y;

    RecWritingMsg_setStr(recMessage, _mesWriting_dmgamemain);

    x = (SCREEN_WIDTH - msgWnd_getWidth(&recMessage->messageWnd)) / 2;
    y = SCREEN_HEIGHT - 0x20 - msgWnd_getHeight(&recMessage->messageWnd);
    RecWritingMsg_setPos(recMessage, x, y);

    RecWritingMsg_start(recMessage);
    setSleepTimer(500);
}

/**
 * Original name: dm_game_eep_write
 */
void dm_game_eep_write(void *arg0 UNUSED) {
    struct_watchGame *st = watchGame;

    if (st->eep_rom_flg) {
        EepRomErr status = EepRom_WriteAll(dm_game_eep_write_callback, st);

        st->eep_rom_flg = false;
        EepRom_DumpErrMes(status);
    }
}

/**
 * Original name: dm_query_next_stage
 */
bool dm_query_next_stage(s32 level, s32 stage, s32 retry) {
    bool next = false;

    if (stage < 8) {
        next = true;
    } else if (stage == 8) {
        if (level >= 3) {
            next = true;
        } else if ((level > 0) && (retry == 0)) {
            next = true;
        }
    }

    return next;
}

/**
 * Original name: dm_save_all
 */
void dm_save_all(void) {
    struct_game_state_data *state = &game_state_data[0];
    struct_watchGame *st = watchGame;
    s32 i;
    s32 level;

    if (st->replayFlag || st->eep_rom_flg) {
        return;
    }

    switch (evs_gamesel) {
        case GSL_4PLAY:
            if (evs_story_flg != 0) {
                s32 stage = evs_story_no;

                if (state->cnd_static == dm_cnd_win) {
                    stage++;
                }

                dm_story_sort_set(evs_select_name_no[0], (s32)story_proc_no >= BGROMDATA_INDEX12, evs_story_level,
                                  state->game_score, evs_game_time, stage, evs_one_game_flg);
                st->eep_rom_flg = true;
            }
            break;

        case GSL_2PLAY:
            for (i = 0; i < EVS_SELECT_NAME_NO_COUNT; i++) {
                switch (evs_gamemode) {
                    case GMD_NORMAL:
                        dm_vsman_set(evs_select_name_no[i], st->vs_win_count[i], st->vs_win_count[i ^ 1]);
                        break;
                    case GMD_FLASH:
                        dm_vm_fl_set(evs_select_name_no[i], st->vs_win_count[i], st->vs_win_count[i ^ 1]);
                        break;
                    case GMD_TIME_ATTACK:
                        dm_vm_ta_set(evs_select_name_no[i], st->vs_win_count[i], st->vs_win_count[i ^ 1]);
                        break;

                    default:
                        break;
                }
            }

            st->eep_rom_flg = true;
            st->vs_win_count[1] = 0;
            st->vs_win_count[0] = 0;
            break;

        case GSL_VSCPU:
            if (evs_story_flg == 0) {
                switch (evs_gamemode) {
                    case GMD_NORMAL:
                        dm_vscom_set(evs_select_name_no[0], st->vs_win_count[0], st->vs_win_count[1]);
                        break;

                    case GMD_FLASH:
                        dm_vc_fl_set(evs_select_name_no[0], st->vs_win_count[0], st->vs_win_count[1]);
                        break;

                    default:
                        break;
                }
                st->eep_rom_flg = true;
                st->vs_win_count[1] = 0;
                st->vs_win_count[0] = 0;
            } else {
                struct_evs_mem_data *temp_a0 = &evs_mem_data[evs_select_name_no[0]];
                struct_evs_mem_data_config *cfg = &temp_a0->config;
                s32 stage = evs_story_no;
                s32 charNo = (s32)story_proc_no >= BGROMDATA_INDEX12 ? 1 : 0;

                cfg->st_st = CLAMP(stage - 1, 0, 7);

                if (state->cnd_static == dm_cnd_win) {
                    if ((stage == 9) && (state->game_retry == 0)) {
                        evs_secret_flg[charNo] = 1;
                    }
                    if (dm_query_next_stage(evs_story_level, stage, state->game_retry)) {
                        stage++;
                    } else if (stage == 9) {
                        stage++;
                    }
                }

                dm_story_sort_set(evs_select_name_no[0], charNo, evs_story_level, state->game_score, evs_game_time,
                                  stage, evs_one_game_flg);

                st->eep_rom_flg = true;
            }
            break;

        case GSL_1PLAY:
            switch (evs_gamemode) {
                case GMD_NORMAL:
                    level = state->virus_level;
                    if (state->cnd_static == dm_cnd_win) {
                        if (level >= 21) {
                            evs_level_21 = 1;
                        }
                        if (level < 99) {
                            level++;
                        }
                    }

                    dm_level_sort_set(evs_select_name_no[0], state->cap_def_speed, state->game_score, level);

                    evs_mem_data[evs_select_name_no[0]].config.p1_lv = MIN(21, level);
                    break;

                case GMD_TaiQ:
                    dm_taiQ_sort_set(evs_select_name_no[0], state->game_level, state->game_score, evs_game_time);
                    break;

                case GMD_TIME_ATTACK:
                    dm_timeAt_sort_set(evs_select_name_no[0], state->game_level, state->game_score, evs_game_time,
                                       state->total_erase_count);
                    break;

                default:
                    break;
            }
            st->eep_rom_flg = true;
            break;

        default:
            break;
    }

    BgTasksManager_SendTask(dm_game_eep_write, NULL);
}

/**
 * Original name: dm_query_pause_player
 */
void dm_query_pause_player(struct_game_state_data *state) {
    struct_watchGame *st = watchGame;
    u16 btn = gControllerPressedButtons[main_joy[state->player_no]];

    if (st->query_pause_player_no >= 0) {
        return;
    }

    switch (state->cnd_static) {
        case dm_cnd_wait:
        case dm_cnd_pause:
            break;

        case dm_cnd_lose:
            if (!st->replayFlag) {
                return;
            }

            if (state->cnd_now != dm_cnd_tr_chack) {
                return;
            }
            break;

        default:
            return;
    }

    if ((state->cnd_now != dm_cnd_init) && (state->player_type == PLAYERTYPE_0)) {
        if (!st->replayFlag) {
            if (btn & START_BUTTON) {
                st->query_play_pause_se = true;
                st->query_pause_player_no = state->player_no;
            }
        } else if (btn & ANY_BUTTON) {
            st->query_pause_player_no = state->player_no;
        }
    }
}

/**
 * Original name: dm_game_main_cnt_1P
 */
DmMainCnt dm_game_main_cnt_1P(struct_game_state_data *state, GameMapCell *map, s32 player_no) {
    struct_watchGame *watchGameP = watchGame;
    dm_calc_erase_score_pos_arg2 pos;
    s32 var_s1;
    u8 *var_t2;
    s32 var_s2;
    s32 var_s0;

    dm_query_pause_player(state);
    animeState_update(&state->anime);
    scoreNums_update(&watchGameP->scoreNums[player_no]);
    if ((evs_gamemode == GMD_TIME_ATTACK) && (evs_game_time >= 10800) && (state->cnd_static == dm_cnd_wait)) {
        return dm_ret_game_over;
    }

    switch (state->mode_now) {
        case dm_mode_init:
            dm_set_virus(state, map, virus_map_data[player_no], virus_map_disp_order[player_no]);
            return dm_ret_virus_wait;

        case dm_mode_wait:
            return dm_ret_virus_wait;

        case dm_mode_throw:
            state->cap_speed_count++;

            if (state->cap_speed_count == FlyingCnt[state->cap_def_speed]) {
                dm_init_capsel_go(&state->now_cap, (CapsMagazine[state->cap_magazine_save] >> 4) % 3,
                                  CapsMagazine[state->cap_magazine_save] % 3);
                state->mode_now = dm_mode_down;
                state->cap_speed_count = 30;
                dm_capsel_down(state, map);
            }
            break;

        case dm_mode_down_wait:
            if (dm_check_game_over(state, map)) {
                for (var_s0 = 0; var_s0 < ANIMES_COUNT; var_s0++) {
                    if (watchGameP->virus_anime_state[var_s0].animeSeq.animeNo != ANIMENO_4) {
                        animeState_set(&watchGameP->virus_anime_state[var_s0], ANIMENO_3);
                    }
                }

                if (evs_gamemode == GMD_TaiQ) {
                    watchGameP->big_virus_stop_count = 0;
                }
                return dm_ret_game_over;
            }

            if (dm_h_erase_chack(map) || dm_w_erase_chack(map)) {
                state->mode_now = dm_mode_erase_chack;
                state->cap_speed_count = 0;
            } else {
                state->mode_now = dm_mode_cap_set;
            }
            break;

        case dm_mode_erase_chack:
            state->cap_speed_count++;

            if (state->cap_speed_count >= 18) {
                state->cap_speed_count = 0;
                state->mode_now = dm_mode_erase_anime;
                dm_h_erase_chack_set(state, map);
                dm_w_erase_chack_set(state, map);
                dm_h_ball_chack(map);
                dm_w_ball_chack(map);

                var_s0 = state->virus_number;
                var_s0 -= get_virus_color_count(map, &watchGameP->big_virus_count[0], &watchGameP->big_virus_count[1],
                                                &watchGameP->big_virus_count[2]);
                state->virus_number -= var_s0;

                state->total_erase_count += var_s0;

                for (var_s0 = 0; var_s0 < ANIMES_COUNT; var_s0++) {
                    if (watchGameP->big_virus_count[var_s0] == 0) {
                        if (!watchGameP->big_virus_flg[var_s0]) {
                            watchGameP->big_virus_flg[var_s0] = true;
                            animeState_set(&watchGameP->virus_anime_state[var_s0], ANIMENO_4);
                            animeSmog_start(&watchGameP->virus_smog_state[var_s0]);
                            if (state->virus_number != 0) {
                                dm_snd_play_in_game(SND_INDEX_74);
                                dm_snd_play_in_game(SND_INDEX_57);
                            }
                        }
                    } else {
                        if (state->chain_color[3] & (0x10 << var_s0)) {
                            if (watchGameP->big_virus_stop_count == 0) {
                                animeState_set(&watchGameP->virus_anime_state[var_s0], ANIMENO_2);
                                dm_snd_play_in_game(SND_INDEX_74);
                            }
                        }
                    }
                }

                state->chain_color[3] &= 0xF;

                dm_calc_erase_score_pos(state, map, &pos);
                scoreNums_set(&watchGameP->scoreNums[player_no], dm_make_score(state), state->erase_virus_count,
                              state->map_x + state->map_item_size / 2 + pos.x,
                              state->map_y + state->map_item_size / 2 + pos.y);

                if ((state->virus_number == 0) && (evs_gamemode != GMD_TaiQ)) {
                    state->cnd_now = dm_cnd_stage_clear;
                    state->mode_now = dm_mode_stage_clear;
                    if (state->chain_line_max < state->chain_line) {
                        state->chain_line_max = state->chain_line;
                    }
                    return dm_ret_clear;
                }

                if ((state->virus_number < 4U) && (evs_gamemode != GMD_TaiQ)) {
                    if (!watchGameP->last_3_se_flg) {
                        watchGameP->last_3_se_flg = true;
                        dm_snd_play_in_game(SND_INDEX_80);
                    }
                    if (!watchGameP->bgm_bpm_flg[0]) {
                        watchGameP->bgm_bpm_flg[0] = true;
                        watchGameP->bgm_bpm_flg[1] = true;
                    }
                }

                state->chain_count++;
                if (state->chain_line < 2) {
                    if (state->chain_color[3] & 8) {
                        state->chain_color[3] &= (u8)~0x8;
                        dm_snd_play_in_game(SND_INDEX_56);
                    } else {
                        dm_snd_play_in_game(SND_INDEX_61);
                    }
                } else {
                    if (state->chain_color[3] & 8) {
                        state->chain_color[3] &= (u8)~0x8;
                    }

                    var_s0 = MIN(2, (s32)state->chain_line - 2);
                    dm_snd_play_in_game(_charSE_tbl[state->charNo] + var_s0);
                }
            }
            break;

        case dm_mode_erase_anime:
            dm_capsel_erase_anime(state, map);
            break;

        case dm_mode_ball_down:
            go_down(state, map, 0xE);
            break;

        case dm_mode_cap_set:
            add_taiQ_bonus_wait(state);

            if (watchGameP->bottom_up_flag && (watchGameP->big_virus_stop_count == 0)) {
                state->bottom_up_scroll = 0;
                state->mode_now = dm_mode_bottom_up;
                set_bottom_up_virus(state, map);
                dm_snd_play_in_game(SND_INDEX_101);
            } else {
                if (state->chain_count > 1) {
                    state->total_chain_count = MIN(99, state->total_chain_count + state->chain_count - 1);
                }

                dm_warning_h_line(state, map);
                dm_set_capsel(state);
                dm_capsel_speed_up(state);
                dm_attack_se(state, player_no);
                animeState_set(&state->anime, ANIMENO_1);

                if (UNK_PLAYER0_CHECK(state, player_no)) {
                    aifMakeFlagSet(state);
                }

                if (state->chain_line_max < state->chain_line) {
                    state->chain_line_max = state->chain_line;
                }

                state->mode_now = dm_mode_throw;
                state->cap_speed_count = 0;
                state->cap_speed_max = 0;
                state->chain_line = 0;
                state->chain_count = 0;
                state->erase_virus_count = 0;
                state->erase_virus_count_old = 0;

                for (var_s0 = 0; var_s0 < ARRAY_COUNT(state->chain_color); var_s0++) {
                    state->chain_color[var_s0] = 0;
                }
            }
            break;

        case dm_mode_bottom_up:
            state->bottom_up_scroll++;
            if (state->bottom_up_scroll >= state->map_item_size) {
                state->bottom_up_scroll = 0;
                watchGameP->bottom_up_flag = false;

                watchGameP->big_virus_wait =
                    MAX(_big_virus_min_wait[state->game_level], watchGameP->big_virus_wait - DOUBLE_LITERAL(0.5));

                state->mode_now = dm_mode_ball_down;
                if (bottom_up_bottle_items(map)) {
                    return dm_ret_game_over;
                }

                state->virus_number = get_virus_color_count(
                    map, watchGameP->big_virus_count, &watchGameP->big_virus_count[1], &watchGameP->big_virus_count[2]);

                for (var_s0 = 0; var_s0 < ANIMES_COUNT; var_s0++) {
                    if ((watchGameP->big_virus_count[var_s0] != 0) && watchGameP->big_virus_flg[var_s0]) {
                        animeState_set(&watchGameP->virus_anime_state[var_s0], ANIMENO_0);
                        animeSmog_start(&watchGameP->virus_smog_state[var_s0]);
                        watchGameP->big_virus_flg[var_s0] = false;
                    } else if (watchGameP->virus_anime_state[var_s0].animeSeq.animeNo == ANIMENO_3) {
                        animeState_set(&watchGameP->virus_anime_state[var_s0], ANIMENO_0);
                    }
                }
            }
            break;

        case dm_mode_clear_wait:
        case dm_mode_gover_wait:
            if (state->mode_now == dm_mode_clear_wait) {
                if (effectNextStage_calc(player_no)) {
                    break;
                }
            } else {
                if (effectGameOver_calc(player_no)) {
                    break;
                }
            }

            if (gControllerPressedButtons[main_joy[player_no]] & ANY_BUTTON) {
                switch (state->mode_now) {
                    case dm_mode_clear_wait:
                        state->cnd_now = dm_cnd_clear_result;
                        state->mode_now = dm_mode_clear_result;
                        break;

                    case dm_mode_gover_wait:
                        state->cnd_now = dm_cnd_gover_result;
                        state->mode_now = dm_mode_gover_result;
                        break;

                    default:
                        break;
                }
            }
            break;

        case dm_mode_clear_result:
        case dm_mode_gover_result:
            if (gControllerPressedButtons[main_joy[player_no]] & ANY_BUTTON) {
                timeAttackResult_skip(&watchGameP->timeAttackResult[player_no]);
            }

            timeAttackResult_update(&watchGameP->timeAttackResult[player_no], true);

            dm_add_score(state, watchGameP->timeAttackResult[player_no].scoreDelta);
            watchGameP->timeAttackResult[player_no].scoreDelta = 0;
            if (timeAttackResult_isEnd(&watchGameP->timeAttackResult[player_no])) {
                switch (state->mode_now) {
                    case dm_mode_clear_result:
                        state->cnd_now = dm_cnd_stage_clear;
                        state->mode_now = dm_mode_stage_clear;
                        break;

                    case dm_mode_gover_result:
                        state->cnd_now = dm_cnd_game_over;
                        state->mode_now = dm_mode_game_over;
                        break;

                    default:
                        break;
                }
            }
            break;

        case dm_mode_stage_clear:
        case dm_mode_game_over:
            if (state->mode_now == dm_mode_stage_clear) {
                if (effectNextStage_calc(player_no)) {
                    break;
                }
            } else {
                if (effectGameOver_calc(player_no)) {
                    break;
                }
            }

            var_s0 = (Z_TRIG | L_JPAD | L_TRIG | R_TRIG);
            if ((watchGameP->passAlphaStep < 0) && CHECK_FLAG_ALL(gControllerHoldButtons[main_joy[0]], var_s0)) {
                switch (evs_gamemode) {
                    case GMD_NORMAL:
                        var_s1 = 0;
                        var_s2 = state->virus_level;
                        break;

                    case GMD_TIME_ATTACK:
                        var_s1 = 1;
                        var_s2 = state->game_level;
                        break;

                    case GMD_TaiQ:
                        var_s1 = 2;
                        var_s2 = state->game_level;
                        break;

                    default:
                        break;
                }

                if (evs_select_name_no[0] == 8) {
                    var_t2 = D_800A7360;
                } else {
                    var_t2 = evs_mem_data[evs_select_name_no[0]].mem_name;
                }

                if (watchGameP->passBuf[0] == '\0') {
                    func_8007E760(watchGameP->passBuf, var_s1, var_s2, state->cap_def_speed, state->game_score / 10,
                                  evs_game_time / 6, var_t2);

                    // Write MSG_END
                    watchGameP->passBuf[ARRAY_COUNT(watchGameP->passBuf) - 2] = '~';
                    watchGameP->passBuf[ARRAY_COUNT(watchGameP->passBuf) - 1] = 'z';
                }
                msgWnd_clear(&watchGameP->passWnd);
                msgWnd_addStr(&watchGameP->passWnd, _mesPassword);
                msgWnd_addStr(&watchGameP->passWnd, watchGameP->passBuf);
                msgWnd_skip(&watchGameP->passWnd);
                watchGameP->passAlphaStep = -watchGameP->passAlphaStep;
            } else {
                if ((gControllerPressedButtons[main_joy[0]] != 0) && (watchGameP->passAlphaStep > 0)) {
                    watchGameP->passAlphaStep = -watchGameP->passAlphaStep;
                }

                switch (retryMenu_input(player_no)) {
                    case ETC_PART_INDEX_GRAPHBIN_0:
                        set_replay_state();
                        dm_snd_play_in_game(SND_INDEX_62);
                        return dm_ret_replay;

                    case ETC_PART_INDEX_GRAPHBIN_1:
                        reset_replay_state();
                        dm_snd_play_in_game(SND_INDEX_62);
                        return dm_ret_next_stage;

                    case ETC_PART_INDEX_GRAPHBIN_2:
                        reset_replay_state();
                        if (state->game_retry < 999) {
                            state->game_retry++;
                        }

                        if ((state->virus_level > 21) && (watchGameP->retry_coin > 0)) {
                            watchGameP->retry_coin--;
                            dm_snd_play_in_game(SND_INDEX_78);
                        } else {
                            dm_snd_play_in_game(SND_INDEX_62);
                        }
                        return dm_ret_retry;

                    case ETC_PART_INDEX_GRAPHBIN_3:
                        dm_snd_play_in_game(SND_INDEX_62);
                        return dm_ret_end;

                    default:
                        break;
                }
            }
            break;

        case dm_mode_pause_retry:
            switch (retryMenu_input(player_no)) {
                case ETC_PART_INDEX_GRAPHBIN_0:
                    if (watchGameP->query_pause_player_no < 0) {
                        watchGameP->query_pause_player_no = player_no;
                    }
                    dm_snd_play_in_game(SND_INDEX_62);
                    break;

                case ETC_PART_INDEX_GRAPHBIN_1:
                    if (state->game_retry < 999) {
                        state->game_retry = state->game_retry + 1;
                    }

                    if ((state->virus_level > 21) && (watchGameP->retry_coin > 0)) {
                        watchGameP->retry_coin--;
                        dm_snd_play_in_game(SND_INDEX_78);
                    } else {
                        dm_snd_play_in_game(SND_INDEX_62);
                    }
                    return dm_ret_retry;

                case ETC_PART_INDEX_GRAPHBIN_2:
                    dm_snd_play_in_game(SND_INDEX_62);
                    return dm_ret_end;

                default:
                    break;
            }
            break;

        default:
            break;
    }

    return dm_ret_null;
}

/**
 * Original name: dm_game_main_cnt
 */
DmMainCnt dm_game_main_cnt(struct_game_state_data *state, GameMapCell *map, s32 player_no) {
    struct_watchGame *st = watchGame;
    dm_calc_erase_score_pos_arg2 pos;
    s32 trg = gControllerPressedButtons[main_joy[player_no]];
    s32 i;
    s32 j;
    bool var_s6;

    dm_query_pause_player(state);

    animeState_update(&state->anime);

    scoreNums_update(&st->scoreNums[player_no]);

    if ((state->cnd_static != dm_cnd_wait) && (state->cnd_static != dm_cnd_pause)) {
        dm_black_up(state, map);
    }

    if ((evs_gamemode == GMD_TIME_ATTACK) && (evs_game_time >= 10800) && (state->cnd_static == dm_cnd_wait)) {
        return dm_ret_game_over;
    }

    switch (state->mode_now) {
        case dm_mode_init:
            dm_set_virus(state, map, virus_map_data[player_no], virus_map_disp_order[player_no]);
            return dm_ret_virus_wait;

        case dm_mode_wait:
            return dm_ret_virus_wait;

        case dm_mode_down_wait:
            if (dm_check_game_over(state, map)) {
                return dm_ret_game_over;
            }

            if (dm_h_erase_chack(map) || dm_w_erase_chack(map)) {
                if (!state->flg_game_over) {
                    state->mode_now = dm_mode_erase_chack;
                } else {
                    state->mode_now = dm_mode_tr_erase_chack;
                }

                state->cap_speed_count = 0;
            } else if (!state->flg_game_over) {
                state->mode_now = dm_mode_cap_set;
            } else {
                state->mode_now = dm_mode_tr_cap_set;
            }
            break;

        case dm_mode_erase_chack:
            state->cap_speed_count++;
            if (state->cap_speed_count >= 18) {
                s32 temp_s4_2;

                state->mode_now = dm_mode_erase_anime;
                state->cap_speed_count = 0;
                dm_h_erase_chack_set(state, map);
                dm_w_erase_chack_set(state, map);
                dm_h_ball_chack(map);
                dm_w_ball_chack(map);

                temp_s4_2 = state->virus_number;
                temp_s4_2 -= dm_update_virus_count(state, map, true);
                state->total_erase_count += temp_s4_2;

                dm_calc_erase_score_pos(state, map, &pos);

                scoreNums_set(&st->scoreNums[player_no], dm_make_score(state), state->erase_virus_count,
                              state->map_x + state->map_item_size / 2 + pos.x,
                              state->map_y + state->map_item_size / 2 + pos.y);

                if (state->virus_number == 0) {
                    if (state->chain_line_max < state->chain_line) {
                        state->chain_line_max = state->chain_line;
                    }
                    return dm_ret_clear;
                }
                if (st->last_3_se_cnt >= state->virus_number) {
                    if (!st->last_3_se_flg) {
                        st->last_3_se_flg = true;
                        dm_snd_play_in_game(SND_INDEX_80);
                    }
                    if (!st->bgm_bpm_flg[0]) {
                        st->bgm_bpm_flg[0] = true;
                        st->bgm_bpm_flg[1] = true;
                    }
                }
                state->chain_count++;

                switch (evs_gamesel) {
                    case GSL_2PLAY:
                    case GSL_VSCPU:
                    case GSL_2DEMO:
                        if (state->chain_line < 2) {
                            if (state->chain_color[3] & 8) {
                                state->chain_color[3] &= ~8;
                                if ((evs_gamemode == GMD_FLASH) && (temp_s4_2 != 0)) {
                                    dm_snd_play_in_game(SND_INDEX_102);
                                } else {
                                    dm_snd_play_in_game(SND_INDEX_56);
                                }
                            } else {
                                dm_snd_play_in_game(SND_INDEX_61);
                            }
                        } else {
                            s32 temp_v0_3 = state->chain_line - 2;

                            if (temp_v0_3 <= 2) {
                                j = temp_v0_3;
                            } else {
                                j = 2;
                            }

                            dm_snd_play_in_game(_charSE_tbl[state->charNo] + j);

                            if (state->chain_color[3] & 8) {
                                state->chain_color[3] &= ~8;
                            }
                        }
                        break;

                    case GSL_4PLAY:
                    case GSL_4DEMO:
                        if (state->chain_color[3] & 8) {
                            state->chain_color[3] &= ~8;
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
            dm_capsel_erase_anime(state, map);
            break;

        case dm_mode_ball_down:
            go_down(state, map, 0xE);
            break;

        case dm_mode_cap_set:
            var_s6 = true;

            if (state->chain_count > 1) {
                state->total_chain_count = MIN(99, state->total_chain_count + state->chain_count - 1);
            }

            dm_attack_se(state, player_no);
            dm_warning_h_line(state, map);
            switch (evs_gamesel) {
                case GSL_2PLAY:
                case GSL_VSCPU:
                case GSL_2DEMO:
                    if (evs_gamemode != GMD_TIME_ATTACK) {
                        i = dm_set_attack_2p(state);
                        if (i != 0) {
                            animeState_set(&state->anime, ANIMENO_1);
                        }

                        if (dm_broken_set(state, map)) {
                            animeState_set(&state->anime, ANIMENO_2);
                            var_s6 = false;
                            dm_snd_play_in_game(_charSE_tbl[state->charNo] + 3);
                            state->mode_now = dm_mode_ball_down;
                            if (state->ai.aiState & 1) {
                                state->ai.aiState |= 2;
                            } else {
                                state->ai.aiState |= 1;
                            }
                        }
                    }
                    break;

                case GSL_4PLAY:
                case GSL_4DEMO:
                    i = dm_set_attack_4p(state);
                    if (i != 0) {
                        animeState_set(&state->anime, ANIMENO_1);
                    }

                    if (dm_broken_set(state, map)) {
                        animeState_set(&state->anime, ANIMENO_2);
                        var_s6 = false;
                        state->mode_now = dm_mode_ball_down;
                        if (state->ai.aiState & 1) {
                            state->ai.aiState |= 2;
                        } else {
                            state->ai.aiState |= 1;
                        }
                    }
                    break;

                default:
                    break;
            }

            if (var_s6) {
                dm_set_capsel(state);
                dm_capsel_speed_up(state);
                if (state->chain_line_max < state->chain_line) {
                    state->chain_line_max = state->chain_line;
                }

                state->chain_line = 0;
                state->chain_count = 0;
                state->erase_virus_count = 0;
                state->erase_virus_count_old = 0;

                for (i = 0; i < ARRAY_COUNT(state->chain_color); i++) {
                    state->chain_color[i] = 0;
                }

                state->mode_now = dm_mode_down;
                if (UNK_PLAYER0_CHECK(state, player_no)) {
                    aifMakeFlagSet(state);
                }
            }
            break;

        case dm_mode_clear_wait:
            effectNextStage_calc(player_no);
            break;

        case dm_mode_gover_wait:
            effectGameOver_calc(player_no);
            break;

        case dm_mode_retire_wait:
            effectRetire_calc(player_no);
            break;

        case dm_mode_clear_result:
        case dm_mode_gover_result:
        case dm_mode_retire_result:
            if (gControllerPressedButtons[main_joy[player_no]] & ANY_BUTTON) {
                timeAttackResult_skip(&st->timeAttackResult[player_no]);
            }

            timeAttackResult_update(&st->timeAttackResult[player_no], true);
            dm_add_score(state, st->timeAttackResult[player_no].scoreDelta);
            st->timeAttackResult[player_no].scoreDelta = 0;
            break;

        case dm_mode_win_retry:
        case dm_mode_lose_retry:
        case dm_mode_draw_retry:
            if (state->mode_now == dm_mode_win_retry) {
                if (effectWin_calc(player_no) != 0) {
                    break;
                }
            } else if (state->mode_now == dm_mode_lose_retry) {
                if (effectLose_calc(player_no) != 0) {
                    break;
                }
            } else if (state->mode_now == dm_mode_draw_retry) {
                if (effectDraw_calc(player_no) != 0) {
                    break;
                }
            }

            switch (retryMenu_input(player_no)) {
                case ETC_PART_INDEX_GRAPHBIN_0:
                    set_replay_state();
                    dm_snd_play_in_game(SND_INDEX_62);
                    return dm_ret_replay;

                case ETC_PART_INDEX_GRAPHBIN_1:
                    reset_replay_state();
                    dm_snd_play_in_game(SND_INDEX_62);
                    return dm_ret_end;

                case ETC_PART_INDEX_GRAPHBIN_2:
                    reset_replay_state();
                    if (state->game_retry < 999) {
                        state->game_retry++;
                    }
                    dm_snd_play_in_game(SND_INDEX_62);
                    return dm_ret_retry;

                case ETC_PART_INDEX_GRAPHBIN_3:
                    dm_snd_play_in_game(SND_INDEX_62);
                    return dm_ret_game_end;

                default:
                    break;
            }
            break;

        case dm_mode_win:
            effectWin_calc(player_no);
            break;

        case dm_mode_lose:
            effectLose_calc(player_no);
            break;

        case dm_mode_draw:
            effectDraw_calc(player_no);
            break;

        case dm_mode_tr_chaeck:
            if ((trg & START_BUTTON) && !st->replayFlag) {
                return dm_ret_tr_a;
            }
            break;

        case dm_mode_training:
            state->flg_game_over = true;
            clear_map_all(map);
            state->virus_number = 0;
            state->virus_order_number = 0;
            state->virus_anime_spead = 0xC;
            state->warning_se_flag = false;
            state->cap_speed = GameSpeed[state->cap_def_speed];
            state->cap_speed_max = 0;
            state->cap_speed_vec = 1;
            state->cap_magazine_cnt = 1;
            state->cap_speed_count = 0;
            state->cap_count = 0;
            dm_set_capsel(state);
            state->erase_anime = 0;
            state->erase_anime_count = 0;
            state->erase_virus_count = 0;
            state->erase_virus_count_old = 0;
            state->chain_line = 0;
            state->chain_count = 0;

            for (i = 0; i < ARRAY_COUNT(state->chain_color); i++) {
                state->chain_color[i] = 0;
            }

            for (i = 0; i < ARRAY_COUNT(state->cap_attack_work); i++) {
                state->cap_attack_work[i].unk_0 = 0;
                state->cap_attack_work[i].unk_2 = 0;
            }

            state->mode_now = dm_mode_init;
            state->cnd_now = dm_cnd_init;

            for (i = 0; i < ARRAY_COUNTU(virus_map_disp_order[player_no]); i++) {
                virus_map_disp_order[player_no][i] &= ~0x80;
            }

            for (i = 0; i < state->flash_virus_count; i++) {
                state->flash_virus_pos[i].color = state->flash_virus_bak[i];
            }
            break;

        case dm_mode_tr_erase_chack:
            state->cap_speed_count++;
            if (state->cap_speed_count >= 18) {
                state->cap_speed_count = 0;
                state->mode_now = dm_mode_erase_anime;
                dm_h_erase_chack_set(state, map);
                dm_w_erase_chack_set(state, map);
                dm_h_ball_chack(map);
                dm_w_ball_chack(map);

                state->chain_count++;
                dm_update_virus_count(state, map, true);

                if (state->chain_color[3] & 8) {
                    state->chain_color[3] &= ~8;
                    dm_snd_play_in_game(SND_INDEX_56);
                } else {
                    dm_snd_play_in_game(SND_INDEX_61);
                }
            }
            break;

        case dm_mode_tr_cap_set:
            dm_warning_h_line(state, map);

            var_s6 = true;
            if (state->flg_training) {
                dm_attack_se(state, player_no);
                dm_set_attack_4p(state);
                animeState_set(&state->anime, ANIMENO_1);
                if (dm_broken_set(state, map)) {
                    state->mode_now = dm_mode_ball_down;
                    var_s6 = false;
                }
            } else {
                for (j = 0; j < 0x10; j++) {
                    state->cap_attack_work[j].unk_0 = 0;
                    state->cap_attack_work[j].unk_2 = 0;
                }
            }

            if (var_s6) {
                dm_set_capsel(state);
                dm_capsel_speed_up(state);
                state->chain_line = 0;
                state->chain_count = 0;
                state->erase_virus_count = 0;
                state->erase_virus_count_old = 0;

                for (i = 0; i < ARRAY_COUNT(state->chain_color); i++) {
                    state->chain_color[i] = 0;
                }
                state->mode_now = dm_mode_down;
            }
            break;

        case dm_mode_pause_retry:
            switch (retryMenu_input(player_no)) {
                case ETC_PART_INDEX_GRAPHBIN_0:
                    if (st->query_pause_player_no < 0) {
                        st->query_pause_player_no = player_no;
                    }
                    dm_snd_play_in_game(SND_INDEX_62);
                    break;

                case ETC_PART_INDEX_GRAPHBIN_1:
                    if (state->game_retry < 999) {
                        state->game_retry++;
                    }
                    dm_snd_play_in_game(SND_INDEX_62);
                    return dm_ret_retry;

                case ETC_PART_INDEX_GRAPHBIN_2:
                    dm_snd_play_in_game(SND_INDEX_62);
                    return dm_ret_game_end;

                default:
                    break;
            }
            break;

        default:
            break;
    }

    return dm_ret_null;
}

/**
 * Original name: dm_set_pause_on
 */
void dm_set_pause_on(struct_game_state_data *state, s32 master) {
    struct_watchGame *st = watchGame;
    s32 p = state->player_no;

    effectPause_init(p);

    state->cnd_static = dm_cnd_pause;
    state->cnd_old = state->cnd_now;
    state->mode_old = state->mode_now;

    if (evs_gamesel == GSL_1PLAY) {
        state->mode_now = dm_mode_pause_retry;
        state->cnd_now = dm_cnd_pause_re;
        if ((state->virus_level < 0x16) || (st->retry_coin > 0)) {
            retryMenu_init(0, RETRYTYPE_1);
        } else {
            retryMenu_init(0, RETRYTYPE_0);
        }
    } else if (p == master) {
        state->mode_now = dm_mode_pause_retry;
        state->cnd_now = dm_cnd_pause_re;
        if (evs_story_flg != 0) {
            state->cnd_now = dm_cnd_pause_re_sc;
            if (evs_story_no == 9) {
                retryMenu_init(p, RETRYTYPE_1);
            } else {
                retryMenu_init(p, RETRYTYPE_1);
            }
        } else {
            retryMenu_init(p, RETRYTYPE_1);
        }
    } else {
        retryMenu_initPauseLogo(p);
        state->cnd_now = dm_cnd_pause;
        state->mode_now = dm_mode_pause;
    }
}

/**
 * Original name: dm_set_pause_off
 */
void dm_set_pause_off(struct_game_state_data *state) {
    state->cnd_static = dm_cnd_wait;
    state->cnd_now = state->cnd_old;
    state->mode_now = state->mode_old;
    if (state->mode_now == dm_mode_tr_chaeck) {
        state->cnd_static = dm_cnd_lose;
    }
}

/**
 * Original name: dm_set_pause_and_volume
 */
void dm_set_pause_and_volume(struct_game_state_data **state, s32 count) {
    struct_watchGame *st = watchGame;
    s32 var_s2 = st->query_pause_player_no;
    struct_game_state_data *temp_a1;
    SndIndex sound;
    s32 i;

    if (st->query_play_pause_se) {
        sound = SND_INDEX_60;
    } else {
        sound = SND_INDEX_INVALID;
    }

    st->query_pause_player_no = -1;
    st->query_play_pause_se = false;
    if (var_s2 < 0) {
        return;
    }

    temp_a1 = state[var_s2];
    if (temp_a1->cnd_static == dm_cnd_wait) {
        dm_seq_set_volume(0x40);
        if (!st->replayFlag) {
            for (i = 0; i < count; i++) {
                dm_set_pause_on(state[i], var_s2);
            }
        } else {
            resume_game_state(1);
        }
        var_s2 = -1;
    } else if (temp_a1->cnd_static == dm_cnd_pause) {
        dm_seq_set_volume(0x80);
        for (i = 0; i < count; i++) {
            dm_set_pause_off(state[i]);
        }
        var_s2 = -1;
    } else if (st->replayFlag && (temp_a1->cnd_now == dm_cnd_tr_chack)) {
        dm_seq_set_volume(0x40);
        resume_game_state(1);
    }

    if ((var_s2 < 0) && (sound > SND_INDEX_INVALID)) {
        dm_snd_play_in_game(sound);
    }
}

/**
 * Original name: dm_set_pause_and_volume_1p
 */
void dm_set_pause_and_volume_1p(struct_game_state_data *state) {
    struct_game_state_data *stateArray[1] = { state };

    dm_set_pause_and_volume(stateArray, ARRAY_COUNT(stateArray));
}

const s16 _tbl_2997[3][2] = {
    { 0x1E, 4 },
    { 0x3C, 6 },
    { 0x78, 0xC },
};

const s16 _clr_3004[2] = { 0xFF, 0x7F };

/**
 * Original name: dm_calc_big_virus_pos
 */
void dm_calc_big_virus_pos(struct_game_state_data *state) {
    struct_watchGame *st = watchGame;
    s32 i;
    s32 stopFlag;

    for (i = 0; i < ARRAY_COUNT(st->big_virus_scale); i++) {
        SAnimeState *ani = &st->virus_anime_state[i];
        f32 vec = 1.0f;

        if ((ani->animeSeq.animeNo == ANIMENO_4) && (ani->frameCount >= 90)) {
            vec = -1.0f;
        }

        st->big_virus_scale[i] = CLAMP(st->big_virus_scale[i] + vec / DOUBLE_LITERAL(60), 0, 1);
    }

    do {
        s32 color = 0x7F;

        for (i = 0; i < ARRAY_COUNTU(_tbl_2997); i++) {
            if (st->big_virus_stop_count < _tbl_2997[i][0]) {
                color = _clr_3004[(st->big_virus_stop_count / _tbl_2997[i][1]) % ARRAY_COUNTU(_clr_3004)];
                break;
            }
        }

        for (i = 0; i < ARRAY_COUNT(st->virus_anime_state); i++) {
            SAnimeState *temp = &st->virus_anime_state[i];

            temp->primColor[0] = temp->primColor[1] = temp->primColor[2] = color;
        }

        st->big_virus_blink_count++;
    } while (0);

    if (state->cnd_static != dm_cnd_wait) {
        return;
    }

    if (st->big_virus_stop_count > 0) {
        if (st->big_virus_no_wait) {
            st->big_virus_stop_count = 0;
            st->big_virus_no_wait = false;
        } else {
            st->big_virus_stop_count--;
        }
    }

    stopFlag = false;
    for (i = 0; i < ARRAY_COUNT(st->virus_anime_state); i++) {
        SAnimeState *anim = &st->virus_anime_state[i];

        switch ((s32)anim->animeSeq.animeNo) {
            case ANIMENO_4:
                if ((evs_gamemode != GMD_TaiQ) && !animeSeq_isEnd(&anim->animeSeq)) {
                    stopFlag++;
                }
                break;

            case ANIMENO_2:
                if (evs_gamemode != GMD_TaiQ) {
                    stopFlag++;
                }
                break;

            case ANIMENO_3:
                if (state->cnd_static != dm_cnd_wait) {
                    stopFlag++;
                }
                break;

            case ANIMENO_0:
            default:
                break;
        }
    }

    if (st->big_virus_stop_count > 0) {
        stopFlag++;
    }

    if (!stopFlag) {
        if (st->started_game_flg) {
            s32 var_s6 = -1;
            s32 var_s5 = 0;

            for (i = 0; i < ARRAY_COUNT(st->big_virus_rot); i++) {
                SAnimeState *temp = &st->virus_anime_state[i];

                if (!st->big_virus_flg[i]) {
                    if (var_s6 < st->big_virus_rot[i]) {
                        var_s6 = st->big_virus_rot[i];
                    }
                } else if (animeSeq_isEnd(&temp->animeSeq)) {
                    var_s5 += 1;
                }
            }

            if ((evs_gamemode == GMD_TaiQ) && (var_s5 == 3)) {
                for (i = 0; i < ARRAY_COUNT(st->big_virus_rot); i++) {
                    st->big_virus_rot[i] = i * (360 / ARRAY_COUNT(st->big_virus_rot)) + 1;
                }
                st->bottom_up_flag = true;
            } else if (st->big_virus_no_wait) {
                st->big_virus_timer = st->big_virus_wait * (0x168 - var_s6);
            } else if (st->big_virus_timer < st->big_virus_wait) {
                st->big_virus_timer += 1.0f;
            }
        }
    }

    if (st->big_virus_timer >= st->big_virus_wait) {
        s32 var_v1_4 = st->big_virus_timer / st->big_virus_wait;

        var_v1_4 = MIN(var_v1_4, 4);

        st->big_virus_timer -= st->big_virus_wait * var_v1_4;
        for (i = 0; i < ARRAY_COUNT(st->big_virus_rot); i++) {
            st->big_virus_rot[i] += var_v1_4;
            if (st->big_virus_rot[i] >= 360.0f) {
                st->big_virus_rot[i] -= 360.0f;
                if (!st->big_virus_flg[i] && (evs_gamemode == GMD_TaiQ)) {
                    st->bottom_up_flag = true;
                    st->big_virus_timer = 0;
                    animeState_set(&st->virus_anime_state[i], ANIMENO_3);
                }
            }
        }
    }

    for (i = 0; i < ARRAY_COUNT(st->big_virus_rot); i++) {
        st->big_virus_pos[i][0] = sinf(st->big_virus_rot[i] * DOUBLE_LITERAL(PI_D) / 180) * 20.0f + 61.0f;
        st->big_virus_pos[i][1] = cosf(st->big_virus_rot[i] * DOUBLE_LITERAL(PI_D) / 180) * -20.0f + 171.0f;
    }
}

/**
 * Original name: dm_game_main_1p
 */
DmMainCnt dm_game_main_1p(void) {
    DmMainCnt ret;
    struct_watchGame *st = watchGame;
    struct_game_state_data *state = &game_state_data[0];

    dm_set_pause_and_volume_1p(state);
    ret = dm_game_main_cnt_1P(state, game_map_data[0], 0);
    dm_warning_h_line_se();
    if (st->big_virus_stop_count == 0) {
        s32 i;

        for (i = 0; i < ANIMES_COUNT; i++) {
            animeState_update(&st->virus_anime_state[i]);
            animeSmog_update(&st->virus_smog_state[i]);
        }
    }

    dm_calc_big_virus_pos(state);
    dm_play_count_down_se();

    if (ret == dm_ret_virus_wait) {
        if (st->count_down_ctrl < 0) {
            if (state->mode_now == dm_mode_wait) {
                st->started_game_flg = true;
                state->mode_now = dm_mode_throw;
                animeState_set(&state->anime, ANIMENO_1);
                start_replay_proc();
            }
        }
    } else if (ret == dm_ret_clear) {
        u32 score;

        effectNextStage_init(state->player_no);
        dm_seq_play_in_game(SEQ_INDEX_14);
        st->started_game_flg = false;
        state->cnd_static = dm_cnd_win;

        switch (evs_gamemode) {
            case GMD_TIME_ATTACK: {
                //! FAKE
                s32 temp_v0;

                state->cnd_now = dm_cnd_clear_wait;
                state->mode_now = dm_mode_clear_wait;

                timeAttackResult_result(&st->timeAttackResult[0], state->game_level, true,
                                        MAX(0, temp_v0 = 0x2A30 - evs_game_time), state->total_chain_count,
                                        state->total_erase_count, state->game_score);
            } break;

            default:
                state->cnd_now = dm_cnd_stage_clear;
                state->mode_now = dm_mode_stage_clear;
                break;
        }

        switch (evs_gamemode) {
            case GMD_TIME_ATTACK:
                retryMenu_init(0, RETRYTYPE_3);
                break;

            case GMD_NORMAL:
                retryMenu_init(0, RETRYTYPE_5);
                break;

            default:
                break;
        }

        animeState_set(&state->anime, ANIMENO_3);

        switch (evs_gamemode) {
            case GMD_TIME_ATTACK:
                score = game_state_data[0].game_score;
                game_state_data[0].game_score = st->timeAttackResult[0].result;
                dm_save_all();
                game_state_data[0].game_score = score;
                break;

            case GMD_NORMAL:
                dm_save_all();
                break;

            default:
                break;
        }
    } else if (ret == dm_ret_game_over) {
        effectGameOver_init(state->player_no);
        animeState_set(&state->anime, ANIMENO_4);
        dm_seq_play_in_game(SEQ_INDEX_17);
        state->virus_anime_spead = 1;
        state->cnd_static = dm_cnd_lose;
        if (evs_gamemode == GMD_TIME_ATTACK) {
            state->cnd_now = dm_cnd_gover_wait;
            state->mode_now = dm_mode_gover_wait;

            timeAttackResult_result(&st->timeAttackResult[0], state->game_level, false, 0, state->total_chain_count,
                                    state->total_erase_count, state->game_score);
            st->started_game_flg = false;
        } else {
            state->cnd_now = dm_cnd_game_over;
            state->mode_now = dm_mode_game_over;
            st->started_game_flg = false;
        }

        if ((state->virus_level <= 21) || ((st->retry_coin > 0))) {
            retryMenu_init(0, RETRYTYPE_3);
        } else {
            retryMenu_init(0, RETRYTYPE_2);
        }

        dm_save_all();
    } else if (ret == dm_ret_next_stage) {
        return dm_ret_next_stage;
    } else if (ret == dm_ret_retry) {
        return dm_ret_retry;
    } else if (ret == dm_ret_replay) {
        return dm_ret_replay;
    } else if (ret == dm_ret_end) {
        return dm_ret_game_over;
    } else if (ret == dm_ret_game_end) {
        return dm_ret_game_end;
    }
    return dm_ret_null;
}

/**
 * Original name: dm_add_win_2p
 */
bool dm_add_win_2p(struct_game_state_data *state) {
    struct_watchGame *st = watchGame;
    s32 p = state->player_no;
    SeqIndex sound = SEQ_INDEX_17;
    bool finish;
    s32 y;
    s32 x;

    st->win_count[p]++;

    if (evs_story_flg != 0) {
        x = _posStStar[p][0];
        y = _posStStar[p][1];

        finish = true;

        if (state->player_type == PLAYERTYPE_0) {
            sound = SEQ_INDEX_14;
        }
    } else {
        x = _posP2StarX[p];
        y = _posP2StarY[evs_vs_count - 1][st->win_count[p] - 1];

        finish = st->win_count[p] == evs_vs_count;

        if (finish) {
            st->vs_win_total[p] = MIN(99, st->vs_win_total[p] + 1);
            st->vs_win_count[p] = MIN(999, st->vs_win_count[p] + 1);
        }

        if ((evs_gamesel != GSL_VSCPU) || (state->player_type == PLAYERTYPE_0)) {
            if (finish) {
                sound = SEQ_INDEX_15;
            } else {
                sound = SEQ_INDEX_14;
            }
        }
    }

    st->star_pos_x[st->star_count] = x;
    st->star_pos_y[st->star_count] = y;
    st->star_count++;
    dm_seq_play_in_game(sound);
    return finish;
}

/**
 * Original name: dm_set_win_2p
 */
bool dm_set_win_2p(struct_game_state_data *state, bool finish, bool menu) {
    s32 p = state->player_no;

    state->cnd_static = dm_cnd_win;
    effectWin_init(p);
    animeState_set(&state->anime, ANIMENO_3);
    dm_snd_play_in_game(_charSE_tbl[state->charNo] + 4);

    if (!menu && (state->player_type == PLAYERTYPE_0)) {
        menu = true;

        state->cnd_now = dm_cnd_win_retry;
        state->mode_now = dm_mode_win_retry;
        if (!evs_story_flg) {
            if (finish) {
                retryMenu_init(p, RETRYTYPE_3);
            } else {
                retryMenu_init(p, RETRYTYPE_5);
            }
        } else {
            state->cnd_now = dm_cnd_win_retry_sc;
            retryMenu_init(p, RETRYTYPE_5);
        }
    } else {
        state->cnd_now = dm_cnd_win;
        state->mode_now = dm_mode_win;
    }

    return menu;
}

/**
 * Original name: dm_set_lose_2p
 */
bool dm_set_lose_2p(struct_game_state_data *state, bool finish, bool menu) {
    s32 p = state->player_no;

    state->cnd_static = dm_cnd_lose;
    animeState_set(&state->anime, ANIMENO_4);
    effectLose_init(p);

    if (!menu && (state->player_type == PLAYERTYPE_0)) {
        menu = true;

        state->cnd_now = dm_cnd_lose_retry;
        state->mode_now = dm_mode_lose_retry;

        if (evs_story_flg) {
            state->cnd_now = dm_cnd_lose_retry_sc;
            if (evs_story_no != 9) {
                retryMenu_init(p, RETRYTYPE_3);
            } else {
                retryMenu_init(p, RETRYTYPE_3);
            }
        } else {
            if (finish) {
                retryMenu_init(p, RETRYTYPE_3);
            } else {
                retryMenu_init(p, RETRYTYPE_5);
            }
        }
    } else {
        state->cnd_now = dm_cnd_lose;
        state->mode_now = dm_mode_lose;
    }

    return menu;
}

/**
 * Original name: dm_set_draw_2p
 */
s32 dm_set_draw_2p(struct_game_state_data *state, bool menu) {
    s32 p = state->player_no;

    state->cnd_static = dm_cnd_draw;
    effectDraw_init(p);
    animeState_set(&state->anime, ANIMENO_4);
    if (!menu && (state->player_type == PLAYERTYPE_0)) {
        menu = true;

        state->cnd_now = dm_cnd_draw_retry;
        state->mode_now = dm_mode_draw_retry;
        retryMenu_init(p, RETRYTYPE_5);
    } else {
        state->cnd_now = dm_cnd_draw;
        state->mode_now = dm_mode_draw;
    }

    return menu;
}

/**
 * Original name: dm_set_time_attack_result_2p
 */
bool dm_set_time_attack_result_2p(struct_game_state_data **state) {
    struct_watchGame *st = watchGame;
    u32 result[2];
    s32 i;
    bool finish = false;
    bool menu = false;

    result[0] = st->timeAttackResult[0].result;
    result[1] = st->timeAttackResult[1].result;

    for (i = 0; i < 2; i++) {
        if (result[i] > result[i ^ 1]) {
            finish = dm_add_win_2p(state[i]);
        }
    }

    for (i = 0; i < 2; i++) {
        if (result[i] > result[i ^ 1]) {
            menu = dm_set_win_2p(state[i], finish, menu);
        }
    }

    for (i = 0; i < 2; i++) {
        if (result[i] < result[i ^ 1]) {
            menu = dm_set_lose_2p(state[i], finish, menu);
        }
    }

    for (i = 0; i < 2; i++) {
        if (result[i] == result[i ^ 1]) {
            menu = dm_set_draw_2p(state[i], menu);
            dm_seq_play_in_game(SEQ_INDEX_17);
        }
    }

    return finish;
}

/**
 * Original name: dm_game_main_2p
 */
DmMainCnt dm_game_main_2p(void) {
    struct_watchGame *st = watchGame;
    bool menu = false;
    bool finish = false;
    s32 var_fp;
    s32 sp40;
    struct_game_state_data *state[2];
    GameMapCell *map[2];
    DmMainCnt ret[2];
    s32 var_s1_4;
    s32 var_s2_2;
    s32 i;

#if 0
    int clear; // r1+0x48
    int gover; // r1+0x44
    int waitTA; // r3
    int resultTA; // r4
#endif

    sp40 = 0;
    var_fp = 0;

    for (i = 0; i < 2; i++) {
        state[i] = &game_state_data[i];
        map[i] = &game_map_data[i][0];
    }

    dm_set_pause_and_volume(state, 2);

    for (i = 0; i < 2; i++) {
        ret[i] = dm_game_main_cnt(state[i], map[i], i);
    }

    dm_warning_h_line_se();
    dm_play_count_down_se();

    if ((ret[0] == dm_ret_virus_wait) && (ret[1] == ret[0])) {
        if (st->count_down_ctrl < 0) {
            for (i = 0; i < 2; i++) {
                if (state[i]->mode_now != dm_mode_wait) {
                    break;
                }
            }

            if (i == 2) {
                st->started_game_flg = true;

                for (i = 0; i < 2; i++) {
                    state[i]->mode_now = dm_mode_down;
                    if (UNK_PLAYER0_CHECK(state[i], i)) {
                        aifMakeFlagSet(state[i]);
                    }
                }

                start_replay_proc();
            }
        }
    } else {
        for (i = 0; i < 2; i++) {
            if (ret[i] == dm_ret_clear) {
                if (evs_gamemode == GMD_TIME_ATTACK) {
                    effectNextStage_init(i);

                    state[i]->mode_now = dm_mode_clear_wait;
                    state[i]->cnd_now = dm_cnd_clear_wait;
                    state[i]->cnd_static = dm_cnd_clear_wait;

                    timeAttackResult_result(&st->timeAttackResult[i], state[i]->game_level, true,
                                            0 > 10800 - (s32)evs_game_time ? 0 : 10800 - evs_game_time,
                                            state[i]->total_chain_count, state[i]->total_erase_count,
                                            state[i]->game_score);
                    _dm_seq_play_in_game(1, SEQ_INDEX_16);
                } else {
                    var_fp++;
                    state[i]->cnd_static = dm_cnd_win;
                }
            } else if (ret[i] == dm_ret_game_over) {
                if (evs_gamemode == GMD_TIME_ATTACK) {
                    if (evs_game_time >= 10800) {
                        effectGameOver_init(i);
                        state[i]->mode_now = dm_mode_gover_wait;
                        state[i]->cnd_now = dm_cnd_gover_wait;
                        state[i]->cnd_static = dm_cnd_gover_wait;
                    } else {
                        effectRetire_init(i);
                        state[i]->mode_now = dm_mode_retire_wait;
                        state[i]->cnd_now = dm_cnd_retire_wait;
                        state[i]->cnd_static = dm_cnd_retire_wait;
                    }

                    timeAttackResult_result(&st->timeAttackResult[i], state[i]->game_level, false, 0,
                                            state[i]->total_chain_count, state[i]->total_erase_count,
                                            state[i]->game_score);
                    _dm_seq_play_in_game(1, SEQ_INDEX_18);
                } else {
                    sp40 += 1;
                    state[i]->cnd_static = dm_cnd_lose;
                }

                state[i]->virus_anime_spead = 1;
                state[i]->black_up_count = 0x10;
                state[i]->flg_retire = true;
            } else if (ret[i] == dm_ret_retry) {
                return dm_ret_retry;
            } else if (ret[i] == dm_ret_replay) {
                return dm_ret_replay;
            } else if (ret[i] == dm_ret_end) {
                return dm_ret_game_over;
            } else if (ret[i] == dm_ret_game_end) {
                return dm_ret_game_end;
            }
        }

        var_s2_2 = 0;
        var_s1_4 = 0;

        for (i = 0; i < 2; i++) {
            switch (state[i]->cnd_now) {
                case dm_cnd_clear_wait:
                case dm_cnd_gover_wait:
                case dm_cnd_retire_wait:
                    if (st->effect_timer[i] == 0) {
                        var_s1_4++;
                    }
                    break;

                case dm_cnd_clear_result:
                case dm_cnd_gover_result:
                case dm_cnd_retire_result:
                    if (timeAttackResult_isEnd(&st->timeAttackResult[i])) {
                        var_s2_2++;
                    }
                    break;

                default:
                    break;
            }
        }

        if (var_s1_4 == 2) {
            for (i = 0; i < 2; i++) {
                switch (state[i]->cnd_now) {
                    case dm_cnd_clear_wait:
                        state[i]->cnd_static = dm_cnd_clear_result;
                        state[i]->cnd_now = dm_cnd_clear_result;
                        state[i]->mode_now = dm_mode_clear_result;
                        break;

                    case dm_cnd_gover_wait:
                        state[i]->cnd_static = dm_cnd_gover_result;
                        state[i]->cnd_now = dm_cnd_gover_result;
                        state[i]->mode_now = dm_mode_gover_result;
                        break;

                    case dm_cnd_retire_wait:
                        state[i]->cnd_static = dm_cnd_retire_result;
                        state[i]->cnd_now = dm_cnd_retire_result;
                        state[i]->mode_now = dm_mode_retire_result;
                        break;

                    default:
                        break;
                }
            }
        } else if (var_s2_2 == 2) {
            finish = dm_set_time_attack_result_2p(state);
        } else if ((var_fp == 2) || (sp40 == 2)) {
            for (i = 0; i < 2; i++) {
                menu = dm_set_draw_2p(state[i], menu);
            }
            dm_seq_play_in_game(SEQ_INDEX_17);
        } else if (var_fp != 0) {
            for (i = 0; i < 2; i++) {
                if (state[i]->cnd_static == dm_cnd_win) {
                    finish = dm_add_win_2p(state[i]);
                }
            }

            for (i = 0; i < 2; i++) {
                if (state[i]->cnd_static == dm_cnd_win) {
                    menu = dm_set_win_2p(state[i], finish, menu);
                }
            }

            for (i = 0; i < 2; i++) {
                if (state[i]->cnd_static != dm_cnd_win) {
                    menu = dm_set_lose_2p(state[i], finish, menu);
                }
            }
        } else if (sp40 != 0) {

            for (i = 0; i < 2; i++) {
                if (state[i]->cnd_static != dm_cnd_lose) {
                    finish = dm_add_win_2p(state[i]);
                }
            }

            for (i = 0; i < 2; i++) {
                if (state[i]->cnd_static != dm_cnd_lose) {
                    menu = dm_set_win_2p(state[i], finish, menu);
                }
            }

            for (i = 0; i < 2; i++) {
                if (state[i]->cnd_static == dm_cnd_lose) {
                    menu = dm_set_lose_2p(state[i], finish, menu);
                }
            }
        }

        if (finish) {
            dm_save_all();
        }
    }

    return dm_ret_null;
}

/**
 * Original name: dm_game_main_4p
 */
DmMainCnt dm_game_main_4p(void) {
    struct_watchGame *st = watchGame;
    struct_game_state_data *state[4];
    GameMapCell *map[4];
    DmMainCnt ret[4];
    s32 i;
    bool finish;
    bool menu;

    s32 sp48;
    s32 sp4C;

    SeqIndex sound;
    TeamNumber var_s6;
    bool var_s7; // end?

    s32 var_a1_3;
    u32 var_a1_4;

    s32 var_a2_2;
    TeamNumber temp_a2_2;
    s32 temp_a2_3;

    s32 temp_a3;

    s32 var_t3;
    s32 var_t4;

#if 0
    int clear; // r4
    int gover; // r5
    // int sound; // r22
    int win_team; // r30
    int clearBit; // r8
    int team; // r1+0x8
    int win; // r12
    bool end; // r21
    int retire; // r7
    int retireBit; // r8
    int team; // r1+0x8
    int win; // r8
    int team; // r7
    int win; // r9
#endif

    for (i = 0; i < 4; i++) {
        state[i] = &game_state_data[i];
        map[i] = game_map_data[i];
    }

    dm_set_pause_and_volume(state, 4);

    for (i = 0; i < 4; i++) {
        ret[i] = dm_game_main_cnt(state[i], map[i], i);
    }

    dm_warning_h_line_se();

    if ((ret[0] == dm_ret_virus_wait) && (ret[1] == ret[0]) && (ret[2] == ret[1]) && (ret[3] == ret[2])) {
        if (st->count_down_ctrl < 0) {
            for (i = 0; i < 4; i++) {
                if (state[i]->mode_now != dm_mode_wait) {
                    break;
                }
            }

            if (i == 4) {
                st->started_game_flg = true;

                for (i = 0; i < 4; i++) {
                    state[i]->mode_now = dm_mode_down;
                    if (UNK_PLAYER0_CHECK(state[i], i)) {
                        aifMakeFlagSet(state[i]);
                    }
                }
                start_replay_proc();
            }
        }

        return dm_ret_null;
    }

    menu = false;
    finish = false;
    var_t4 = 0;
    var_t3 = 0;

    for (i = 0; i < 4; i++) {
        if ((ret[i] == dm_ret_virus_wait) && (state[i]->cnd_training == dm_cnd_training)) {
            if (state[i]->mode_now == dm_mode_wait) {
                state[i]->mode_now = dm_mode_down;
            }
        } else if (ret[i] == dm_ret_clear) {
            var_t3++;
            state[i]->cnd_static = dm_cnd_win;
        } else if (ret[i] == dm_ret_game_over) {
            if (!state[i]->flg_retire) {
                state[i]->cnd_now = dm_cnd_retire;
                state[i]->cnd_training = dm_cnd_retire;
                state[i]->cnd_static = dm_cnd_lose;
                state[i]->black_up_count = 0x10;
                state[i]->flg_retire = true;
                var_t4++;
                if (state[i]->player_type == PLAYERTYPE_1) {
                    state[i]->mode_now = dm_mode_no_action;
                } else {
                    state[i]->cnd_now = dm_cnd_tr_chack;
                    state[i]->mode_now = dm_mode_tr_chaeck;
                }
            } else {
                state[i]->cnd_now = dm_cnd_tr_chack;
                state[i]->mode_now = dm_mode_tr_chaeck;
            }
            state[i]->virus_anime_spead = 4;
        } else if (ret[i] == dm_ret_retry) {
            return dm_ret_retry;
        } else if (ret[i] == dm_ret_replay) {
            return dm_ret_replay;
        } else if (ret[i] == dm_ret_end) {
            return dm_ret_game_over;
        } else if (ret[i] == dm_ret_game_end) {
            return dm_ret_game_end;
        } else if (ret[i] == dm_ret_tr_a) {
            state[i]->cnd_static = dm_cnd_wait;
            state[i]->flg_training = false;
            state[i]->cnd_training = dm_cnd_training;
            state[i]->mode_now = dm_mode_training;
        } else if (ret[i] == dm_ret_tr_b) {
            state[i]->cnd_static = dm_cnd_wait;
            state[i]->flg_training = true;
            state[i]->cnd_training = dm_cnd_training;
            state[i]->mode_now = dm_mode_training;
        }
    }

    if (var_t3 != 0) {
        var_a1_3 = 0;

        for (i = 0; i < 4; i++) {
            if (state[i]->cnd_static == dm_cnd_win) {
                var_a1_3 |= 1 << i;
                var_s6 = state[i]->team_no;
            }
        }

        if (!st->vs_4p_team_flg && (var_t3 > 1)) {
            for (i = 0; i < 4; i++) {
                menu = dm_set_draw_2p(state[i], menu);
            }
            sound = SEQ_INDEX_17;
        } else if (st->vs_4p_team_flg && (var_a1_3 & st->vs_4p_team_bits[0]) && (var_a1_3 & st->vs_4p_team_bits[1])) {
            for (i = 0; i < 4; i++) {
                menu = dm_set_draw_2p(state[i], menu);
            }
            sound = SEQ_INDEX_17;
        } else {
            sound = SEQ_INDEX_14;

            for (i = 0; i < 4; i++) {
                if (state[i]->cnd_static != dm_cnd_win) {
                    continue;
                }

                temp_a2_2 = state[i]->team_no;
                temp_a3 = st->win_count[temp_a2_2];
                if (evs_story_flg != 0) {
                    st->star_pos_x[st->star_count] = _posStP4StarX[i];
                    st->star_pos_y[st->star_count] = 0xD;
                } else if (st->vs_4p_team_flg) {
                    st->star_pos_x[st->star_count] = _posP4TeamStarX[evs_vs_count - 1][temp_a2_2][temp_a3];
                    st->star_pos_y[st->star_count] = 0xD;
                } else {
                    st->star_pos_x[st->star_count] = _posP4CharStarX[evs_vs_count - 1][temp_a2_2][temp_a3];
                    st->star_pos_y[st->star_count] = 0xD;
                }

                st->star_count++;

                st->win_count[temp_a2_2]++;
                if (evs_story_flg != 0) {
                    finish = true;
                } else if (st->win_count[temp_a2_2] == evs_vs_count) {
                    finish = true;
                    sound = SEQ_INDEX_15;
                }
            }

            for (i = 0; i < ARRAY_COUNT(state); i++) {
                if (state[i]->team_no != var_s6) {
                    continue;
                }

                if ((evs_story_flg != 0) && (state[i]->player_type == PLAYERTYPE_0)) {
                    sound = SEQ_INDEX_14;
                }
                menu = dm_set_win_2p(state[i], finish, menu);
            }

            for (i = 0; i < ARRAY_COUNT(state); i++) {
                if (state[i]->team_no != var_s6) {
                    if (evs_story_flg && (state[i]->player_type == PLAYERTYPE_0)) {
                        sound = SEQ_INDEX_17;
                    }
                    menu = dm_set_lose_2p(state[i], finish, menu);
                }
            }
        }

        dm_seq_play_in_game(sound);
    } else if (var_t4 != 0) {
        var_s7 = false;
        var_a2_2 = 0;
        var_a1_4 = 0;

        for (i = 0; i < 4; i++) {
            if (state[i]->flg_retire) {
                var_a2_2++;
                var_a1_4 |= 1 << i;
            }
        }

        if (var_a2_2 == 4) {
            for (i = 0; i < 4; i++) {
                menu = dm_set_draw_2p(state[i], menu);
            }
            dm_seq_play_in_game(SEQ_INDEX_17);
        } else if ((evs_story_flg != 0) && (var_a1_4 & 1)) {
            finish = true;

            menu = dm_set_lose_2p(state[0], finish, menu);
            for (i = 1; i < 4; i++) {
                menu = dm_set_win_2p(state[i], finish, menu);
            }
            dm_seq_play_in_game(SEQ_INDEX_17);
        } else if (!st->vs_4p_team_flg && (var_a2_2 == 3)) {
            s32 temp;

            var_s7 = true;
            sound = SEQ_INDEX_14;

            for (i = 0; i < 4; i++) {
                if (!state[i]->flg_retire) {
                    temp_a2_3 = state[i]->team_no;
                    temp = st->win_count[temp_a2_3];

                    if (evs_story_flg) {
                        st->star_pos_x[st->star_count] = _posStP4StarX[i];
                        st->star_pos_y[st->star_count] = 0xD;
                    } else {
                        st->star_pos_x[st->star_count] = _posP4CharStarX[evs_vs_count - 1][temp_a2_3][temp];
                        st->star_pos_y[st->star_count] = 0xD;
                    }

                    st->star_count++;
                    st->win_count[temp_a2_3]++;
                    var_s6 = temp_a2_3;
                    if (evs_story_flg) {
                        if (state[i]->player_type != PLAYERTYPE_0) {
                            sound = SEQ_INDEX_17;
                        }
                        finish = true;
                    } else if (st->win_count[temp_a2_3] == evs_vs_count) {
                        finish = true;
                        sound = SEQ_INDEX_15;
                    }
                    break;
                }
            }
        } else if (st->vs_4p_team_flg) {
            if ((var_a1_4 & st->vs_4p_team_bits[0]) == st->vs_4p_team_bits[0]) {
                sp48 = 1;
                var_s6 = 1;
                var_s7 = true;
                sp4C = st->win_count[1];
                st->win_count[1]++;
            } else if ((var_a1_4 & st->vs_4p_team_bits[1]) == st->vs_4p_team_bits[1]) {
                sp48 = 0;
                var_s6 = 0;
                var_s7 = true;
                sp4C = st->win_count[0];
                st->win_count[0]++;
            }

            if (var_s7) {
                st->star_pos_x[st->star_count] = _posP4TeamStarX[evs_vs_count - 1][sp48][sp4C];
                st->star_pos_y[st->star_count] = 0xD;
                st->star_count++;

                sound = SEQ_INDEX_14;
                for (i = 0; i < 4; i++) {
                    if (st->win_count[i] == evs_vs_count) {
                        finish = true;
                        sound = SEQ_INDEX_15;
                        break;
                    }
                }
            }
        }

        if (var_s7) {
            for (i = 0; i < 4; i++) {
                if (state[i]->team_no == var_s6) {
                    menu = dm_set_win_2p(state[i], finish, menu);
                }
            }

            for (i = 0; i < 4; i++) {
                if (state[i]->team_no != var_s6) {
                    menu = dm_set_lose_2p(state[i], finish, menu);
                }
            }
            dm_seq_play_in_game(sound);
        }
    }

    if (finish) {
        dm_save_all();
    }

    return dm_ret_null;
}

/**
 * Original name: dm_game_demo_1p
 */
DmMainCnt dm_game_demo_1p(void) {
    struct_watchGame *st = watchGame;
    DmMainCnt ret = dm_game_main_cnt_1P(game_state_data, game_map_data[0], 0);
    s32 i;

    dm_warning_h_line_se();

    for (i = 0; i < ANIMES_COUNT; i++) {
        SAnimeState *animeState = &st->virus_anime_state[i];
        SAnimeSmog *animeSmog = &st->virus_smog_state[i];

        animeState_update(animeState);
        animeSmog_update(animeSmog);
    }

    dm_calc_big_virus_pos(game_state_data);

    if ((ret == dm_ret_virus_wait) && (st->count_down_ctrl < 0)) {
        game_state_data[0].mode_now = dm_mode_throw;
        animeState_set(&game_state_data[0].anime, ANIMENO_1);
        if (UNK_PLAYER0_CHECK(&game_state_data[0], 0)) {
            aifMakeFlagSet(game_state_data);
        }

        st->started_game_flg = true;
    }

    if (st->demo_timer != 0) {
        st->demo_timer--;

        if (gControllerPressedButtons[main_joy[0]] & ANY_BUTTON) {
            st->demo_timer = 0;
        }

        if (st->demo_timer == 0) {
            return dm_ret_next_stage;
        }
    }

    return dm_ret_null;
}

/**
 * Original name: dm_game_demo_2p
 */
DmMainCnt dm_game_demo_2p(void) {
    struct_watchGame *st = watchGame;
    DmMainCnt ret[2];
    s32 i;

    for (i = 0; i < ARRAY_COUNT(ret); i++) {
        ret[i] = dm_game_main_cnt(&game_state_data[i], game_map_data[i], i);
    }

    dm_warning_h_line_se();

    if ((ret[0] == dm_ret_virus_wait) && (ret[1] == ret[0]) && (st->count_down_ctrl < 0)) {
        for (i = 0; i < ARRAY_COUNT(ret); i++) {
            game_state_data[i].mode_now = dm_mode_down;

            if (UNK_PLAYER0_CHECK(&game_state_data[i], i)) {
                aifMakeFlagSet(&game_state_data[i]);
            }
        }

        st->started_game_flg = true;
    }

    if (st->demo_timer != 0) {
        st->demo_timer--;
        if (gControllerPressedButtons[main_joy[0]] & ANY_BUTTON) {
            st->demo_timer = 0;
        }

        if (st->demo_timer == 0) {
            return dm_ret_next_stage;
        }
    }

    return dm_ret_null;
}

/**
 * Original name: dm_game_demo_4p
 */
DmMainCnt dm_game_demo_4p(void) {
    struct_watchGame *st = watchGame;
    DmMainCnt ret[4];
    s32 i;

    for (i = 0; i < ARRAY_COUNT(ret); i++) {
        ret[i] = dm_game_main_cnt(&game_state_data[i], game_map_data[i], i);
    }

    dm_warning_h_line_se();

    if ((ret[0] == dm_ret_virus_wait) && (ret[1] == ret[0]) && (ret[2] == ret[1]) && (ret[3] == ret[2]) &&
        (st->count_down_ctrl < 0)) {
        for (i = 0; i < ARRAY_COUNT(ret); i++) {
            game_state_data[i].mode_now = dm_mode_down;

            if (UNK_PLAYER0_CHECK(game_state_data + i, i)) {
                aifMakeFlagSet(&game_state_data[i]);
            }
        }

        st->started_game_flg = true;
    }

    if (st->demo_timer != 0) {
        st->demo_timer--;

        if (gControllerPressedButtons[main_joy[0]] & ANY_BUTTON) {
            st->demo_timer = 0;
        }

        if (st->demo_timer == 0) {
            return dm_ret_next_stage;
        }
    }

    return dm_ret_null;
}

const s32 cap_tex_4162[2] = { 8, 2 };

/**
 * Original name: dm_game_get_capsel_tex
 */
TiTexData *dm_game_get_capsel_tex(s32 sizeIndex) {
    return &watchGame->texItem[cap_tex_4162[sizeIndex]];
}

const s32 cap_pal_4164[][6] = {
    { 8, 10, 6, 9, 11, 7 },
    { 2, 4, 0, 3, 5, 1 },
};

/**
 * Original name: dm_game_get_capsel_pal
 */
TiTexData *dm_game_get_capsel_pal(s32 sizeIndex, s32 colorIndex) {
    return &watchGame->texItem[cap_pal_4164[sizeIndex][colorIndex]];
}

/**
 * Original name: scoreNums_draw
 */
void scoreNums_draw(ScoreNums *st, Gfx **gfxP) {
    Gfx *gfx = *gfxP;
    TiTexData *texC = &watchGame->texAL[0x11];
    TiTexData *texA = &watchGame->texAL[0x16];
    s32 width = MIN(texC->info[TI_INFO_IDX_WIDTH], texA->info[TI_INFO_IDX_WIDTH]);
    s32 height = texC->info[TI_INFO_IDX_HEIGHT] / 12;
    s32 i;

    gSPDisplayList(gfx++, alpha_texture_init_dl);

    gDPSetCombineLERP(gfx++, TEXEL0, 0, PRIMITIVE, 0, TEXEL1, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED);

    for (i = 0; i < ARRAY_COUNTU(st->numbers); i++) {
        ScoreNumsNumbers *num = &st->numbers[WrapI(0, 8, st->index + i)];
        f32 time = num->time;
        f32 bound;
        s32 alpha;

        if (time == DOUBLE_LITERAL(1.0)) {
            continue;
        }

        if (time < DOUBLE_LITERAL(0.2)) {
            alpha = time * 1275.0f;
        } else if (time < DOUBLE_LITERAL(0.8)) {
            alpha = 255;
        } else {
            alpha = (1.0f - time) * 1275.0f;
        }

        if (time > DOUBLE_LITERAL(0.5)) {
            bound = 1.0f;
        } else {
            bound = time * DOUBLE_LITERAL(4) - DOUBLE_LITERAL(1);
        }

        bound = (DOUBLE_LITERAL(1) - bound * bound) * DOUBLE_LITERAL(8);

        gDPSetPrimColor(gfx++, 0, 0, _scoreNumsColor[num->color].r, _scoreNumsColor[num->color].g,
                        _scoreNumsColor[num->color].b, alpha);

        StretchAlphaTexBlock(&gfx, width, height,
                             (u16 *)texC->texs[TI_TEX_TEX] + texC->info[TI_INFO_IDX_WIDTH] * height * num->number,
                             texC->info[TI_INFO_IDX_WIDTH],
                             (u8 *)texA->texs[TI_TEX_TEX] + (texA->info[TI_INFO_IDX_WIDTH] * height * num->number / 2),
                             texA->info[TI_INFO_IDX_WIDTH], num->pos[0], num->pos[1] - bound, width, height);
    }

    *gfxP = gfx;
}

/**
 * Original name: starForce_init
 */
void starForce_init(StarForce *star, s32 xx[], s32 yy[]) {
    s32 i;

    star->xtbl = xx;
    star->ytbl = yy;

    for (i = 0; i < ARRAY_COUNTU(star->frame); i++) {
        star->frame[i] = 0;
    }
}

/**
 * Original name: starForce_calc
 */
void starForce_calc(StarForce *star, s32 count) {
    s32 i;

    for (i = 0; i < count; i++) {
        s32 temp_a2 = star->frame[i];

        if (temp_a2 < 0x30) {
            star->frame[i] = temp_a2 + 1;
        } else {
            star->frame[i] = WrapI(0x30, 0x6C, temp_a2 + 1);
        }
    }
}

/**
 * Original name: starForce_draw
 */
void starForce_draw(StarForce *star, Gfx **gfxP, s32 count) {
    struct_watchGame *st = watchGame;
    Gfx *gfx = *gfxP;
    TiTexData *texC;
    TiTexData *texA;
    s32 i;
    s32 j;

    gSPDisplayList(gfx++, alpha_texture_init_dl);
    gDPSetCombineLERP(gfx++, TEXEL0, 0, PRIMITIVE, 0, TEXEL1, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED);

    texC = &st->texAL[0x10];
    texA = &st->texAL[0x15];

    for (i = 0; i < count; i++) {
        if (star->frame[i] < 0x30) {
            gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, 255);

            tiStretchAlphaTexItem(&gfx, texC, texA, false, 0x10, 0, star->xtbl[i], star->ytbl[i],
                                  texC->info[TI_INFO_IDX_WIDTH], texC->info[TI_INFO_IDX_HEIGHT] >> 4);
        }

        j = MIN(255, star->frame[i] * 8);

        gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, j);

        j = MAX(0, star->frame[i] - 0x30) >> 2;
        tiStretchAlphaTexItem(&gfx, texC, texA, false, 0x10, j + 1, star->xtbl[i], star->ytbl[i],
                              texC->info[TI_INFO_IDX_WIDTH], texC->info[TI_INFO_IDX_HEIGHT] >> 4);
    }

    gSPDisplayList(gfx++, normal_texture_init_dl);
    gDPSetCombineMode(gfx++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
    gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gDPSetPrimColor(gfx++, 0, 0, 255, 255, 200, 255);
    gDPSetTextureLUT(gfx++, G_TT_NONE);

    for (i = 0; i < count; i++) {
        j = star->frame[i] >> 2;
        if (j >= 0xC) {
            continue;
        }
        texC = &st->texAL[j];
        StretchTexTile4i(&gfx, texC->info[TI_INFO_IDX_WIDTH], texC->info[TI_INFO_IDX_HEIGHT], texC->texs[TI_TEX_TEX], 0,
                         0, texC->info[TI_INFO_IDX_WIDTH], texC->info[TI_INFO_IDX_HEIGHT], star->xtbl[i], star->ytbl[i],
                         texC->info[TI_INFO_IDX_WIDTH], texC->info[TI_INFO_IDX_HEIGHT]);
    }

    *gfxP = gfx;
}

/**
 * Original name: draw_star_base
 */
void draw_star_base(Gfx **gfxP, s32 x, s32 y, bool cached) {
    Gfx *gfx = *gfxP;
    TiTexData *texC = &watchGame->texAL[0x10];
    TiTexData *texA = &watchGame->texAL[0x15];

    if (!cached) {
        gSPDisplayList(gfx++, alpha_texture_init_dl);
    }
    tiStretchAlphaTexItem(&gfx, texC, texA, cached, 0x10, 0, x, y, texC->info[TI_INFO_IDX_WIDTH],
                          texC->info[TI_INFO_IDX_HEIGHT] >> 4);

    *gfxP = gfx;
}

const u8 _tbl_4274[4][4] = {
    { 0, 5, 8, 0xA },
    { 0, 1, 6, 9 },
    { 0, 1, 2, 4 },
    { 0, 1, 2, 3 },
};

/**
 * Original name: draw_4p_attack_guide_panel
 */
void draw_4p_attack_guide_panel(Gfx **gfxP, s32 playerCount, s32 playerNo, s32 x, s32 y) {
    struct_watchGame *st = watchGame;
    Gfx *gfx = *gfxP;
    TiTexData *texC;
    TiTexData *texA;
    s32 var_a1;

    gSPDisplayList(gfx++, normal_texture_init_dl);

    texC = &st->texP4[9];
    tiStretchTexItem(&gfx, texC, 0, 4, playerNo, x, y, texC->info[TI_INFO_IDX_WIDTH],
                     texC->info[TI_INFO_IDX_HEIGHT] / 4);

    gSPDisplayList(gfx++, alpha_texture_init_dl);

    for (var_a1 = 0; var_a1 < 3; var_a1++) {
        f32 xx = x + 0x24;
        f32 yy = y + 5 + var_a1 * 0xD;
        TeamNumber temp_a2 = game_state_data[playerNo].team_no;
        TeamNumber temp2 = game_state_data[(playerNo + 1 + var_a1) % 4].team_no;

        if (temp_a2 == temp2) {
            texC = &st->texP4[temp_a2 + 0x10];
            texA = &st->texP4[0x18];
            StretchAlphaTexBlock(&gfx, texC->info[TI_INFO_IDX_WIDTH], texC->info[TI_INFO_IDX_HEIGHT],
                                 texC->texs[TI_TEX_TEX], texC->info[TI_INFO_IDX_WIDTH], texA->texs[TI_TEX_TEX],
                                 texA->info[TI_INFO_IDX_WIDTH], xx, yy + 1.0f, texC->info[TI_INFO_IDX_WIDTH],
                                 texC->info[TI_INFO_IDX_HEIGHT]);
        } else {
            s32 a;

            texC = &st->texP4[0xA];
            texA = &st->texP4[0x12];

            a = _tbl_4274[playerCount - 1][(playerNo + var_a1 + 1) % ARRAY_COUNT(_tbl_4274[0])];
            tiStretchAlphaTexItem(&gfx, texC, texA, false, 0xB, a, xx, yy, texC->info[TI_INFO_IDX_WIDTH],
                                  texC->info[TI_INFO_IDX_HEIGHT] / 11);
        }
    }

    *gfxP = gfx;
}

/**
 * Original name: dm_map_draw
 */
void dm_map_draw(GameMapCell *mapCells, u8 col_no, s16 x_p, s16 y_p, s8 size) {
    s32 i;

    for (i = 0; i < GAME_MAP_ROWS * GAME_MAP_COLUMNS; i++) {
        GameMapCell *cell = &mapCells[i];

        if ((cell->capsel_m_flg[0] != 0) && (cell->capsel_m_p == col_no)) {

            gSPTextureRectangle(gGfxHead++, (cell->pos_m_x * size + x_p) << 2, ((cell->pos_m_y * size) + y_p) << 2,
                                (cell->pos_m_x * size + x_p + size) << 2, (cell->pos_m_y * size + y_p + size) << 2,
                                G_TX_RENDERTILE, 0, (cell->capsel_m_g * size) << 5, 1 << 10, 1 << 10);
        }
    }
}

/**
 * Original name: dm_find_fall_point
 */
void dm_find_fall_point(GameMapCell *map, struct_game_state_data_now_cap *cap, s32 fallPosY[2]) {
    s32 minY = 0x10;
    s32 i;
    int row;

    for (i = 0; i < 2; i++) {
        row = MAX(1, cap->pos_y[i]);

        for (; row < GAME_MAP_ROWS; row++) {
            if (get_map_info(map, cap->pos_x[i], row) != 0) {
                minY = MIN(minY, row - 1);
                break;
            }
        }
    }

    fallPosY[0] = minY - (cap->pos_y[0] < cap->pos_y[1] ? 1 : 0);
    fallPosY[1] = minY - (cap->pos_y[0] > cap->pos_y[1] ? 1 : 0);
}

const char _tbl_4345[] = { 9, 0, 1, 2, 3, 4, 5, 6, 7, 8 };

/**
 * Original name: draw_virus_number
 */
void draw_virus_number(Gfx **gfxP, u32 number, s32 x, s32 y, f32 sx, f32 arg5 UNUSED) {
    TiTexData *texC = &watchGame->texAL[0xD];
    TiTexData *texA = &watchGame->texAL[0x12];
    s32 var_t1 = 0;
    s32 width = MIN(texC->info[TI_INFO_IDX_WIDTH], texA->info[TI_INFO_IDX_WIDTH]);
    s32 height = texC->info[TI_INFO_IDX_HEIGHT] / 10;
    s32 tmp[16];
    s32 temp_fs0;
    s32 var_s0;
    s32 var_s4;

#if 0
    int i; // r26
    int xx; // r25
    int yy; // r1+0x8
    int column; // r3
#endif

    do {
        tmp[var_t1] = number % 10;
        number /= 10;
        var_t1 += 1;
    } while (number != 0);

    var_s4 = var_t1 * -7;
    temp_fs0 = height / -2;
    for (var_s0 = var_t1 - 1; var_s0 >= 0; var_s0--) {
        StretchAlphaTexBlock(
            gfxP, width, height,
            texC->texs[TI_TEX_TEX] + (texC->info[TI_INFO_IDX_WIDTH] * height * _tbl_4345[tmp[var_s0]] * 2),
            texC->info[TI_INFO_IDX_WIDTH],
            texA->texs[TI_TEX_TEX] + (texA->info[TI_INFO_IDX_WIDTH] * height * _tbl_4345[tmp[var_s0]]) / 2,
            texA->info[TI_INFO_IDX_WIDTH], x + (var_s4 * sx), y + temp_fs0 * sx, width * sx, height * sx);
        var_s4 += 0xE;
    }
}

const s32 _tex_4374[] = { 3, 4, 5 };
const s32 _row_4375[] = { 0xD, 0xC, 0xC };

/**
 * Original name: draw_count_number
 */
void draw_count_number(Gfx **gfxP, s32 color, s32 column, u32 number, s32 x, s32 y) {
    TiTexData *texC = &watchGame->texP1[_tex_4374[color]];
    TiTexData *texA = &watchGame->texP1[7];
    s32 width = MIN(texC->info[TI_INFO_IDX_WIDTH], texA->info[TI_INFO_IDX_WIDTH]);
    s32 height = texC->info[TI_INFO_IDX_HEIGHT] / _row_4375[color];
    s32 tmp[16];
    s32 i;

    for (i = 0; i < column; i++) {
        tmp[i] = number % 10;
        number /= 10;
    }

    switch (column) {
        case -1:
            tmp[0] = 0xA;
            column = 1;
            break;

        case -2:
            tmp[0] = 0xB;
            column = 1;
            break;

        case -3:
            tmp[0] = 0xC;
            column = 1;
            break;
    }

    for (i = column - 1; i >= 0; i--) {
        StretchAlphaTexBlock(
            gfxP, width, height, texC->texs[TI_TEX_TEX] + texC->info[TI_INFO_IDX_WIDTH] * height * tmp[i] * 2,
            texC->info[TI_INFO_IDX_WIDTH], texA->texs[TI_TEX_TEX] + texA->info[TI_INFO_IDX_WIDTH] * height * tmp[i] / 2,
            texA->info[TI_INFO_IDX_WIDTH], x, y, width, height);
        x += 9;
    }
}

const u8 _pos_4415[] = { 0, 0x11, 0x1A };
const s8 _col_4416[] = { 2, -3, 2 };
static_assert(ARRAY_COUNT(_pos_4415) == 3, "");
static_assert(ARRAY_COUNT(_pos_4415) == ARRAY_COUNT(_col_4416), "");

/**
 * Original name: draw_time
 */
void draw_time(Gfx **gfxP, u32 time, s32 x, s32 y) {
    s32 t[3];
    s32 i;

    t[1] = 0;
    t[2] = (time / 60) % 60;
    t[0] = ((time / 60) / 60) % 100;
    for (i = 0; i < 3; i++) {
        draw_count_number(gfxP, 0, _col_4416[i], t[i], x + _pos_4415[i], y);
    }
}

const u8 _pos_4426[] = { 0, 6, 13, 28, 35 };
const s8 _col_4427[] = { 1, -3, 2, -3, 1 };
static_assert(ARRAY_COUNT(_pos_4426) == 5, "");
static_assert(ARRAY_COUNT(_pos_4426) == ARRAY_COUNT(_col_4427), "");

/**
 * Original name: draw_time2
 */
void draw_time2(Gfx **gfxP, u32 time, s32 x, s32 y) {
    s32 sp20[5];
    s32 i;

    sp20[3] = 0;
    sp20[1] = 0;
    sp20[4] = (time / 6) % 10;
    sp20[2] = ((time / 6) / 10) % 60;
    sp20[0] = (((time / 6) / 10) / 60) % 60;
    for (i = 0; i < 5; i++) {
        draw_count_number(gfxP, 0, _col_4427[i], sp20[i], x + _pos_4426[i], y);
    }
}

/**
 * Original name: push_any_key_draw
 */
void push_any_key_draw(s32 x_pos, s32 y_pos) {
    struct_watchGame *st = watchGame;
    TiTexData *texC;
    TiTexData *texA;
    s32 alpha;
    s32 width;

    alpha = sins((st->blink_count << 10) & 0xFC00) * (255.0f / 0x8000) + 127;
    alpha = CLAMP(alpha, 0, 255);

    gSPDisplayList(gGfxHead++, alpha_texture_init_dl);
    gDPSetCombineLERP(gGfxHead++, TEXEL0, 0, PRIMITIVE, 0, TEXEL1, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0,
                      COMBINED);
    gDPSetPrimColor(gGfxHead++, 0, 0, 255, 255, 255, alpha);

    texC = &st->texAL[0x17];
    texA = &st->texAL[0x18];

    width = MIN(texC->info[TI_INFO_IDX_WIDTH], texA->info[TI_INFO_IDX_WIDTH]);

    StretchAlphaTexTile(&gGfxHead, width, texC->info[TI_INFO_IDX_HEIGHT], texC->texs[TI_TEX_TEX],
                        texC->info[TI_INFO_IDX_WIDTH], texA->texs[TI_TEX_TEX], texA->info[TI_INFO_IDX_WIDTH], 0, 0,
                        width, texC->info[TI_INFO_IDX_HEIGHT], x_pos, y_pos, width, texC->info[TI_INFO_IDX_HEIGHT]);
}

const s32 _tex_4459[3][2] = { { 0xE, 0x13 }, { 0x1B, 0x1C }, { 0x19, 0x1A } };

/**
 * Original name: draw_demo_logo
 */
void draw_demo_logo(Gfx **gfxP, s32 x, s32 y) {
    struct_watchGame *st = watchGame;
    Gfx *gfx = *gfxP;
    s32 alpha[3];
    s32 i;

    alpha[0] = sins((st->blink_count << 10) & 0xFC00) * (255.0f / 0x8000) + 127;
    alpha[0] = CLAMP(alpha[0], 0, 255);
    alpha[1] = 255 - alpha[0];
    alpha[2] = 255;

    gSPDisplayList(gfx++, alpha_texture_init_dl);
    gDPSetCombineLERP(gfx++, TEXEL0, 0, PRIMITIVE, 0, TEXEL1, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED);

    for (i = 0; i < ARRAY_COUNTU(alpha); i++) {
        TiTexData *texC;
        TiTexData *texA;
        s32 width;
        s32 height;

        if (i == 2) {
            x = 0xE;
            y = 0x12;
        }

        texC = &st->texAL[_tex_4459[i][0]];
        texA = &st->texAL[_tex_4459[i][1]];

        width = MIN(texC->info[TI_INFO_IDX_WIDTH], texA->info[TI_INFO_IDX_WIDTH]);
        height = MIN(texC->info[TI_INFO_IDX_HEIGHT], texA->info[TI_INFO_IDX_HEIGHT]);

        gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, alpha[i]);
        StretchAlphaTexTile(&gfx, width, height, texC->texs[TI_TEX_TEX], texC->info[TI_INFO_IDX_WIDTH],
                            texA->texs[TI_TEX_TEX], texA->info[TI_INFO_IDX_WIDTH], 0, 0, width, height, x, y, width,
                            height);
    }

    *gfxP = gfx;
}

const s32 RO_800B2134[2][2] = { { 0x17, 0x18 }, { 0xF, 0x14 } };

/**
 * Original name: draw_replay_logo
 */
void draw_replay_logo(Gfx **gfxP, s32 x, s32 y) {
    struct_watchGame *st = watchGame;
    Gfx *gfx = *gfxP;
    s32 alpha[2];
    s32 i;

    alpha[0] = sins((st->blink_count << 10) & 0xFC00) * (255.0f / 0x8000) + 127;
    alpha[0] = CLAMP(alpha[0], 0, 255);
    alpha[1] = 255 - alpha[0];

    gSPDisplayList(gfx++, alpha_texture_init_dl);
    gDPSetCombineLERP(gfx++, TEXEL0, 0, PRIMITIVE, 0, TEXEL1, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED);

    for (i = 0; i < ARRAY_COUNTU(alpha); i++) {
        TiTexData *texC = &st->texAL[RO_800B2134[i][0]];
        TiTexData *texA = &st->texAL[RO_800B2134[i][1]];
        s32 width = MIN(texC->info[TI_INFO_IDX_WIDTH], texA->info[TI_INFO_IDX_WIDTH]);
        s32 height = MIN(texC->info[TI_INFO_IDX_HEIGHT], texA->info[TI_INFO_IDX_HEIGHT]);

        gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, alpha[i]);
        StretchAlphaTexTile(&gfx, width, height, texC->texs[TI_TEX_TEX], texC->info[TI_INFO_IDX_WIDTH],
                            texA->texs[TI_TEX_TEX], texA->info[TI_INFO_IDX_WIDTH], 0, 0, width, height, x, y, width,
                            height);
    }

    *gfxP = gfx;
}

/**
 * Original name: _init_coin_logo
 */
void _init_coin_logo(s32 count) {
    struct_watchGame *st = watchGame;
    s32 i;

    watchGame->coin_count = count;

    //! @bug: Iterating past the end of the array
    for (i = 0; i < 4; i++) {
        if (i < count) {
            st->coin_time[i] = 0;
        } else {
            st->coin_time[i] = -1;
        }
    }
}

/**
 * Original name: _disp_coin_logo
 */
void _disp_coin_logo(Gfx **gfxP, s32 count) {
    struct_watchGame *st = watchGame;
    Gfx *gfx = *gfxP;
    s32 i;
    TiTexData *texC;
    s32 tileW;

    if (st->coin_count < count) {
        for (i = st->coin_count; i < count; i++) {
            if (st->coin_time[i] == 0) {
                st->coin_time[i] = 0;
                st->coin_count += 1;
            } else if (st->coin_time[i] < 0) {
                st->coin_time[i] = 30;
            } else {
                st->coin_time[i] = st->coin_time[i] - 1;
            }
        }
    } else if (count < st->coin_count) {
        for (i = st->coin_count - 1; i >= count; i--) {
            if (st->coin_time[i] >= 30) {
                st->coin_count -= 1;
                st->coin_time[i] = -1;
            } else {
                st->coin_time[i] = st->coin_time[i] + 1;
            }
        }
        count = st->coin_count;
    }

    gSPDisplayList(gfx++, normal_texture_init_dl);

    gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);

    gDPSetCombineLERP(gfx++, 0, 0, 0, TEXEL0, PRIMITIVE, 0, TEXEL0, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, TEXEL0, 0);

    texC = &st->texLS[0x15];

    tileW = texC->info[TI_INFO_IDX_WIDTH] >> 2;
    for (i = 0; i < count; i++) {
        f32 fx = 0xED + i * 0x10;
        f32 fy = st->coin_time[i] - 15;
        s32 alpha;

        fy = SQ(fy) * DOUBLE_LITERAL(0.125) + DOUBLE_LITERAL(81) - DOUBLE_LITERAL(28.125);
        alpha = 255 - st->coin_time[i] * 0xFF / 30;

        gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, alpha);

        StretchTexTile4(&gfx, texC->info[TI_INFO_IDX_WIDTH], texC->info[TI_INFO_IDX_HEIGHT], texC->texs[TI_TEX_TLUT],
                        texC->texs[TI_TEX_TEX], tileW * ((st->coin_time[i] >> 1) & 3), 0, tileW,
                        texC->info[TI_INFO_IDX_HEIGHT], fx, fy, tileW, texC->info[TI_INFO_IDX_HEIGHT]);
    }

    *gfxP = gfx;
}

/**
 * Original name: draw_flash_virus_light
 */
void draw_flash_virus_light(Gfx **gfxP, bool cached, s32 x, s32 y, s32 color) {
    struct_watchGame *st = watchGame;
    Gfx *gfx = *gfxP;
    TiTexData *tex = &st->texItem[tbl_4589[(st->blink_count >> 1) % ARRAY_COUNTU(tbl_4589)] + 0xC];

    if (!cached) {
        gSPDisplayList(gfx++, normal_texture_init_dl);
        gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
        gDPSetCombineLERP(gfx++, ENVIRONMENT, PRIMITIVE, TEXEL0, PRIMITIVE, ENVIRONMENT, 0, TEXEL0, 0, ENVIRONMENT,
                          PRIMITIVE, TEXEL0, PRIMITIVE, ENVIRONMENT, 0, TEXEL0, 0);
        gDPSetTextureLUT(gfx++, G_TT_NONE);
        gDPSetEnvColor(gfx++, 255, 255, 255, 255);
    }

    gDPSetPrimColor(gfx++, 0, 0, col_4590[color].r, col_4590[color].g, col_4590[color].b, col_4590[color].a);

    tiStretchTexBlock(&gfx, tex, cached, x, y, 20.0f, 20.0f);
    *gfxP = gfx;
}

/**
 * Original name: draw_flash_virus_lights
 */
void draw_flash_virus_lights(Gfx **gfxP, struct_game_state_data *state, GameMapCell *map UNUSED) {
    bool cached = false;
    s32 dx;
    s32 dy;
    s32 i;

    switch (state->map_item_size) {
        case 0x8:
            dy = -6;
            dx = -6;
            break;

        case 0xA:
            dy = -5;
            dx = -5;
            break;

            // var_s6 and var_s5 are undefined
    }

    for (i = 0; i < state->flash_virus_count; i++) {
        if (state->flash_virus_pos[i].color < 0) {
            continue;
        }

        draw_flash_virus_light(gfxP, cached,
                               dx + state->map_x + (state->map_item_size * state->flash_virus_pos[i].column),
                               dy + state->map_y + (state->map_item_size * (state->flash_virus_pos[i].row + 1)),
                               state->flash_virus_pos[i].color);
        cached = true;
    }
}

/**
 * Original name: timeAttackResult_draw
 */
void timeAttackResult_draw(TimeAttackResult *st, Gfx **gfxP, s32 x, s32 y) {
    struct_watchGame *g = watchGame;
    Gfx *gfx = *gfxP;
    TiTexData *texC;
    TiTexData *texA;

    gSPDisplayList(gfx++, alpha_texture_init_dl);

    texC = &g->texP1[8];
    texA = &g->texP1[9];

    StretchAlphaTexTile(&gfx, texC->info[TI_INFO_IDX_WIDTH], texC->info[TI_INFO_IDX_HEIGHT], texC->texs[TI_TEX_TEX],
                        texC->info[TI_INFO_IDX_WIDTH], texA->texs[TI_TEX_TEX], texA->info[TI_INFO_IDX_WIDTH], 0, 0,
                        texC->info[TI_INFO_IDX_WIDTH], texC->info[TI_INFO_IDX_HEIGHT], x, y,
                        texC->info[TI_INFO_IDX_WIDTH], texC->info[TI_INFO_IDX_HEIGHT]);
    draw_time2(&gfx, st->time + 5, x + 0x12, y + 0xE);
    draw_count_number(&gfx, 0, 2, st->combo, x + 0x1F, y + 0x23);
    draw_count_number(&gfx, 0, 2, st->virus, x + 0x1F, y + 0x38);
    draw_count_number(&gfx, 0, 7, st->score, x + 9, y + 0x50);

    *gfxP = gfx;
}

/**
 * Original name: draw_story_board
 */
void draw_story_board(Gfx **gfxP, s32 x, s32 y, bool visBoard, bool visScore) {
    struct_watchGame *temp_s1 = watchGame;
    Gfx *gfx = *gfxP;

    gSPDisplayList(gfx++, alpha_texture_init_dl);

    if (visBoard) {
        TiTexData *texC = &temp_s1->texP2[0x12];
        TiTexData *texA = &temp_s1->texP2[0x13];

        StretchAlphaTexBlock(&gfx, texC->info[TI_INFO_IDX_WIDTH], texA->info[TI_INFO_IDX_HEIGHT],
                             texC->texs[TI_TEX_TEX], texC->info[TI_INFO_IDX_WIDTH], texA->texs[TI_TEX_TEX],
                             texA->info[TI_INFO_IDX_WIDTH], x + 0x78, y + 0xB, texC->info[TI_INFO_IDX_WIDTH],
                             texC->info[TI_INFO_IDX_HEIGHT]);

        texC = &temp_s1->texP2[9];
        tiStretchAlphaTexItem(&gfx, texC, &temp_s1->texP2[2], false, 4, evs_story_level, x + 0x8E, y + 0x36,
                              texC->info[TI_INFO_IDX_WIDTH], texC->info[TI_INFO_IDX_HEIGHT] >> 2);
    }

    if (visScore) {
        draw_count_number(&gfx, 0, 7, game_state_data->game_score, x + 0x81, y + 0x19);
    }

    *gfxP = gfx;
}

const s32 _x_4663[2] = { 0x63, 0xB8 };
const s32 _x_4670[2] = { 0x71, 0xBD };
const s32 _x_4676[2] = { 0x6C, 0xB8 };
const s32 _x_4693[2] = { 0x5E, 0xA2 };

/**
 * Original name: draw_vsmode_board
 */
void draw_vsmode_board(Gfx **gfxP, s32 x, s32 y, bool visBoard, bool visScore) {
    struct_watchGame *st = watchGame;
    Gfx *gfx = *gfxP;
    s32 pad[3] UNUSED;
    TiTexData *texC;
    TiTexData *texA;
    s32 i;

    gSPDisplayList(gfx++, alpha_texture_init_dl);

    if (visBoard) {
        switch (evs_gamemode) {
            case GMD_FLASH:
            case GMD_TIME_ATTACK:
                texC = &st->texP2[0x10];
                texA = &st->texP2[0x11];
                StretchAlphaTexBlock(&gfx, texC->info[TI_INFO_IDX_WIDTH], texC->info[TI_INFO_IDX_HEIGHT],
                                     texC->texs[TI_TEX_TEX], texC->info[TI_INFO_IDX_WIDTH], texA->texs[TI_TEX_TEX],
                                     texA->info[TI_INFO_IDX_WIDTH], x + 0x5F, y + 9, texC->info[TI_INFO_IDX_WIDTH],
                                     texC->info[TI_INFO_IDX_HEIGHT]);

                texC = &st->texP2[9];
                texA = &st->texP2[2];
                for (i = 0; i < 2; i++) {
                    tiStretchAlphaTexItem(&gfx, texC, texA, false, 4, game_state_data[i].game_level, x + _x_4663[i],
                                          y + 0xB, texC->info[TI_INFO_IDX_WIDTH], texC->info[TI_INFO_IDX_HEIGHT] >> 2);
                }
                break;

            default:
                texC = &st->texP2[0x14];
                texA = &st->texP2[0x15];
                StretchAlphaTexBlock(&gfx, texC->info[TI_INFO_IDX_WIDTH], texC->info[TI_INFO_IDX_HEIGHT],
                                     texC->texs[TI_TEX_TEX], texC->info[TI_INFO_IDX_WIDTH], texA->texs[TI_TEX_TEX],
                                     texA->info[TI_INFO_IDX_WIDTH], x + 0x68, y + 9, texC->info[TI_INFO_IDX_WIDTH],
                                     texC->info[TI_INFO_IDX_HEIGHT]);

                for (i = 0; i < 2; i++) {
                    draw_count_number(&gfx, 0, 2, game_state_data[i].virus_level, x + _x_4670[i], y + 0xB);
                }
                break;
        }

        texC = &st->texP2[0xD];
        texA = &st->texP2[6];
        StretchAlphaTexBlock(&gfx, texC->info[TI_INFO_IDX_WIDTH], texC->info[TI_INFO_IDX_HEIGHT],
                             texC->texs[TI_TEX_TEX], texC->info[TI_INFO_IDX_WIDTH], texA->texs[TI_TEX_TEX],
                             texA->info[TI_INFO_IDX_WIDTH], x + 0x68, (y + 0x19), texC->info[TI_INFO_IDX_WIDTH],
                             texC->info[TI_INFO_IDX_HEIGHT]);

        texC = &st->texP2[0xC];
        texA = &st->texP2[5];
        for (i = 0; i < 2; i++) {
            tiStretchAlphaTexItem(&gfx, texC, texA, false, 3, 2 - game_state_data[i].cap_def_speed, x + _x_4676[i],
                                  y + 0x1B, texC->info[TI_INFO_IDX_WIDTH], texC->info[TI_INFO_IDX_HEIGHT] / 3);
        }
    }

    if (evs_gamesel == GSL_VSCPU) {
        if (visBoard) {
            texC = &st->texP2[0xA];
            texA = &st->texP2[3];
            StretchAlphaTexBlock(&gfx, texC->info[TI_INFO_IDX_WIDTH], texC->info[TI_INFO_IDX_HEIGHT],
                                 texC->texs[TI_TEX_TEX], texC->info[TI_INFO_IDX_WIDTH], texA->texs[TI_TEX_TEX],
                                 texA->info[TI_INFO_IDX_WIDTH], x + 0x70, y + 0x29, texC->info[TI_INFO_IDX_WIDTH],
                                 texC->info[TI_INFO_IDX_HEIGHT]);
        }

        if (visScore) {
            draw_count_number(&gfx, 0, 7, game_state_data->game_score, x + 0x90, y + 0x2A);
        }
    } else {
        if (visBoard) {
            texC = &st->texP2[0xB];
            texA = &st->texP2[4];
            StretchAlphaTexBlock(&gfx, texC->info[TI_INFO_IDX_WIDTH], texC->info[TI_INFO_IDX_HEIGHT],
                                 texC->texs[TI_TEX_TEX], texC->info[TI_INFO_IDX_WIDTH], texA->texs[TI_TEX_TEX],
                                 texA->info[TI_INFO_IDX_WIDTH], x + 0x58, y + 0x29, texC->info[TI_INFO_IDX_WIDTH],
                                 texC->info[TI_INFO_IDX_HEIGHT]);
        }

        if (visScore) {
            for (i = 0; i < 2; i++) {
                draw_count_number(&gfx, i + 1, 7, game_state_data[i].game_score, x + _x_4693[i], y + 0x2A);
            }
        }
    }

    *gfxP = gfx;
}

const s32 _rect_4752[][4] = {
    { 0, 0, 0x60, 0x14 }, { 0, 0x14, 0x60, 0x14 }, { 0, 0x28, 8, 0xA0 }, { 0x58, 0x28, 8, 0xA0 }, { 0, 0xC8, 0x60, 8 },
};

/**
 * Original name: _draw_bottle_10
 */
void _draw_bottle_10(Gfx **gfxP, const s32 *xx, const s32 *yy, s32 count) {
    struct_watchGame *st = watchGame;
    Gfx *gfx = *gfxP;
    TiTexData *texC;
    s32 i;
    s32 j;

    gSPDisplayList(gfx++, normal_texture_init_dl);
    gDPSetCombineMode(gfx++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
    gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, 192);

    texC = &st->texP1[1];
    for (i = 0; i < texC->info[TI_INFO_IDX_HEIGHT]; i += 0x2A) {
        for (j = 0; j < count; j++) {
            s32 h;

            h = MIN(0x2A, texC->info[TI_INFO_IDX_HEIGHT] - i);
            tiStretchTexTile(&gfx, texC, j, 0, i, texC->info[TI_INFO_IDX_WIDTH], h, xx[j], yy[j] + i,
                             texC->info[TI_INFO_IDX_WIDTH], h);
        }
    }

    gSPDisplayList(gfx++, normal_texture_init_dl);

    texC = &st->texP1[0];
    for (i = 0; i < ARRAY_COUNTU(_rect_4752); i++) {
        for (j = 0; j < count; j++) {
            tiStretchTexTile(&gfx, texC, j, _rect_4752[i][0], _rect_4752[i][1], _rect_4752[i][2], _rect_4752[i][3],
                             xx[j] + _rect_4752[i][0], yy[j] + _rect_4752[i][1], _rect_4752[i][2], _rect_4752[i][3]);
        }
    }

    *gfxP = gfx;
}

/**
 * Original name: dm_calc_bottle_2p
 */
void dm_calc_bottle_2p(void) {
    s32 i = (FRAME_MOVEMENT_MAX - watchGame->frame_move_count) * 8;
    s32 mx[2] = { 0x1C - i, i + 0xD4 };

    for (i = 0; i < ARRAY_COUNT(mx); i++) {
        struct_game_state_data *state = &game_state_data[i];

        state->map_x = mx[i];
        state->map_y = 0x2E;
    }
}

/**
 * Original name: dm_draw_bottle_2p
 */
void dm_draw_bottle_2p(Gfx **gfxP) {
    struct_watchGame *st = watchGame;
    Gfx *gfx = *gfxP;
    s32 i = (FRAME_MOVEMENT_MAX - st->frame_move_count) * 8;
    s32 arr[2] UNUSED = { -i, i };
    s32 x[2];
    s32 y[2];

    for (i = 0; i < 2; i++) {
        struct_game_state_data *state = &game_state_data[i];

        x[i] = state->map_x - 8;
        y[i] = state->map_y - 0x1E;
    }

    _draw_bottle_10(&gfx, x, y, 2);

    *gfxP = gfx;
}

/**
 * Original name: dm_draw_big_virus
 */
void dm_draw_big_virus(Gfx **gfxP) {
    struct_watchGame *st = watchGame;
    Gfx *gfx = *gfxP;
    s32 i;

    for (i = 0; i < ANIMES_COUNT; i++) {
        animeState_initDL2(&st->virus_anime_state[i], &gfx);
        animeState_draw(&st->virus_anime_state[i], &gfx, st->big_virus_pos[i][0], st->big_virus_pos[i][1],
                        st->big_virus_scale[i], st->big_virus_scale[i]);
        animeSmog_draw(&st->virus_smog_state[i], &gfx, st->big_virus_pos[i][0], st->big_virus_pos[i][1],
                       st->big_virus_scale[i], st->big_virus_scale[i]);
    }

    *gfxP = gfx;
}

const s32 _pat_4838[6] = { 0, 1, 2, 3, 2, 1 };

/**
 * Original name: dm_draw_KaSaMaRu
 */
void dm_draw_KaSaMaRu(Gfx **gfxP, Mtx **mtxP, Vtx **vtxP, bool speaking, s32 x, s32 y, s32 dir, u32 alpha) {
    struct_watchGame *watchGameP = watchGame;
    Gfx *gfx = *gfxP;
    Mtx *mtx = *mtxP;
    Vtx *vtx = *vtxP;
    TiTexData *texC;
    TiTexData *texA;
    s32 i;
    s32 width;
    s32 height;
    f32 mf[4][4];
    f32 angle;

    guOrtho(mtx, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 1.0f, 10.0f, 1.0f);
    gSPMatrix(gfx++, mtx++, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);

    guTranslate(mtx, 0.0f, 0.0f, -5.0f);
    gSPMatrix(gfx++, mtx++, G_MTX_NOPUSH | G_MTX_MUL | G_MTX_PROJECTION);

    angle = WrapF(0.0f, 1.0f, watchGameP->blink_count * DOUBLE_LITERAL(1.0 / 128)) * DOUBLE_LITERAL(M_PI) * 2;
    guRotateRPYF(mf, 0.0f, (1 - dir) * 0x5A, sinf(angle) * 4.0f * dir);

    i = WrapI(0, ARRAY_COUNT(_pat_4838), ((watchGameP->blink_count % 128U) * 9) >> 4);

    if (!speaking) {
        i = 0;
    }

    texA = &watchGameP->texKaSa[_pat_4838[i] + 1];
    texC = &watchGameP->texKaSa[0];

    width = MIN(texA->info[TI_INFO_IDX_WIDTH], texC->info[TI_INFO_IDX_WIDTH]);
    height = MIN(texA->info[TI_INFO_IDX_HEIGHT], texC->info[TI_INFO_IDX_HEIGHT]);

    gSPDisplayList(gfx++, alpha_texture_init_dl);
    gSPClearGeometryMode(gfx++, G_ZBUFFER | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN |
                                    G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH | G_CLIPPING);
    gDPSetCombineLERP(gfx++, TEXEL0, 0, PRIMITIVE, 0, TEXEL1, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED);
    gDPSetTexturePersp(gfx++, G_TP_NONE);
    gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, alpha);

    if (dir <= 0) {
        mf[3][0] = x + width;
    } else {
        mf[3][0] = x;
    }
    mf[3][1] = y;

    guMtxF2L(mf, mtx);
    gSPMatrix(gfx++, mtx++, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    RectAlphaTexTile(&gfx, &vtx, width, height, texA->texs[TI_TEX_TEX], texA->info[TI_INFO_IDX_WIDTH],
                     texC->texs[TI_TEX_TEX], texC->info[TI_INFO_IDX_WIDTH], 0, 0, width, height, 0.0f, 0.0f, width,
                     height);

    *vtxP = vtx;
    *mtxP = mtx;
    *gfxP = gfx;
}

/**
 * Original name: dm_game_graphic_common
 */
void dm_game_graphic_common(struct_game_state_data *state, s32 player_no, GameMapCell *map) {
    TiTexData *tex;
    s32 size_flg;
    s32 i;

    size_flg = (state->map_item_size == 8) ? 1 : 0;

    gSPDisplayList(gGfxHead++, normal_texture_init_dl);

    // Draw the pills and virus on the bottle.
    // Does not draw the falling pills nor the next pill.
    tex = dm_game_get_capsel_tex(size_flg);
    load_TexTile_4b(tex->texs[TI_TEX_TEX], tex->info[TI_INFO_IDX_WIDTH], tex->info[TI_INFO_IDX_HEIGHT], 0, 0,
                    tex->info[TI_INFO_IDX_WIDTH] - 1, tex->info[TI_INFO_IDX_HEIGHT] - 1);
    gfxSetScissor(&gGfxHead, GFXSETSCISSOR_INTERLACE_NO, state->map_x, state->map_y + state->map_item_size,
                  state->map_item_size * 8, state->map_item_size * 0x10);
    for (i = 0; i < 6; i++) {
        tex = dm_game_get_capsel_pal(size_flg, i);
        load_TexPal(tex->texs[TI_TEX_TLUT]);
        dm_map_draw(map, i, state->map_x, state->map_y - state->bottom_up_scroll, state->map_item_size);
    }

#if VERSION_CN || VERSION_GW
    gDPPipeSync(gGfxHead++);
#endif

    gfxSetScissor(&gGfxHead, GFXSETSCISSOR_INTERLACE_NO, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    if (!UNK_PLAYER0_CHECK(state, player_no)) {
        s32 fallPosY[2];
        struct_game_state_data_now_cap *cap;

        if ((visible_fall_point[player_no] == 0) || (state->mode_now != dm_mode_down)) {
            return;
        }

        if ((state->now_cap.pos_y[0] <= 0) || (state->now_cap.capsel_flg_0 == 0)) {
            return;
        }

        cap = &state->now_cap;

        dm_find_fall_point(map, cap, fallPosY);

        gDPSetRenderMode(gGfxHead++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
        gDPSetCombineMode(gGfxHead++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
        gDPSetPrimColor(gGfxHead++, 0, 0, 96, 96, 96, 150);

        for (i = 0; i < 2; i++) {
            s32 x;
            s32 y;
            s32 size;

            tex = dm_game_get_capsel_pal(size_flg, cap->capsel_p[i]);
            load_TexPal(tex->texs[TI_TEX_TLUT]);
            size = state->map_item_size;
            x = cap->pos_x[i] * size + state->map_x;
            y = fallPosY[i] * size + state->map_y;

            gSPTextureRectangle(gGfxHead++, (x * 4), (y * 4), ((x + size) * 4), ((y + size) * 4), G_TX_RENDERTILE,
                                0x0000, (cap->casel_g[i] * size << 5), 1 << 10, 1 << 10);
        }

        gDPSetPrimColor(gGfxHead++, 0, 0, 255, 255, 255, 255);
        gDPSetRenderMode(gGfxHead++, G_RM_TEX_EDGE, G_RM_TEX_EDGE2);
    }
}

/**
 * Original name: dm_game_graphic_p
 */
void dm_game_graphic_p(struct_game_state_data *state, s32 player_no, GameMapCell *map) {
    struct_watchGame *st = watchGame;
    s32 xx[2];
    s32 yy[2];
    s32 size_flg;
    s32 i;

    if (state->cnd_static == dm_cnd_pause) {
        return;
    }

    size_flg = state->map_item_size == 8 ? 1 : 0;

    dm_game_graphic_common(state, player_no, map);

    gSPDisplayList(gGfxHead++, normal_texture_init_dl);

    if (dm_calc_capsel_pos(state, xx, yy)) {
        if (st->demo_flag || (state->now_cap.pos_y[0] <= 0) ||
            ((state->cnd_now != dm_cnd_pause) && (state->cnd_now != dm_cnd_wait))) {
            dm_draw_capsel_by_gfx(state, xx, yy);
        }
    }

    if ((state->next_cap.capsel_flg_0 == 0) || (state->now_cap.pos_y[0] <= 0)) {
        return;
    }

    for (i = 0; i < STRUCT_GAME_STATE_DATA_UNK_178_UNK_LEN; i++) {
        load_TexPal(dm_game_get_capsel_pal(size_flg, state->next_cap.capsel_p[i])->texs[TI_TEX_TLUT]);
        draw_Tex(state->next_cap.pos_x[i] * state->map_item_size + state->map_x,
                 (state->next_cap.pos_y[i] * state->map_item_size + state->map_y) - 0xA, state->map_item_size,
                 state->map_item_size, 0, state->next_cap.casel_g[i] * state->map_item_size);
    }
}

/**
 * Original name: dm_game_graphic_1p
 */
void dm_game_graphic_1p(struct_game_state_data *state, s32 player_no, GameMapCell *map) {
    struct_watchGame *st = watchGame;
    s32 xx[2];
    s32 yy[2];
    s32 i;

    if (state->cnd_static == dm_cnd_pause) {
        return;
    }

    dm_game_graphic_common(state, player_no, map);

    gSPDisplayList(gGfxHead++, normal_texture_init_dl);

    if (dm_calc_capsel_pos(state, xx, yy)) {
        i = 0;
        if ((state->mode_now == dm_mode_init) || (state->mode_now == dm_mode_wait)) {
            i++;
            xx[1] -= xx[0];
            yy[1] -= yy[0];
            xx[0] = 0xDA;
            yy[0] = 0x34;
            xx[1] += xx[0];
            yy[1] += yy[0];
        } else if (st->demo_flag) {
            i++;
        }

        if (i != 0) {
            dm_draw_capsel_by_gfx(state, xx, yy);
        }
    }

    if ((state->next_cap.capsel_flg_0 == 0) || (state->now_cap.pos_y[0] <= 0) || (state->cnd_static != dm_cnd_wait)) {
        return;
    }

    for (i = 0; i < 2; i++) {
        TiTexData *tex = dm_game_get_capsel_pal(0, state->next_cap.capsel_p[i]);

        load_TexPal(tex->texs[TI_TEX_TLUT]);
        draw_Tex(0xDA + i * 0xA, 0x34, 0xA, 0xA, 0, state->next_cap.casel_g[i] * 0xA);
    }
}

/**
 * Original name: dm_game_graphic_effect
 */
void dm_game_graphic_effect(struct_game_state_data *state, s32 player_no, s32 arg2 UNUSED) {
    struct_watchGame *st = watchGame;
    s32 temp_fv0;
    s32 temp_lo;
    s32 temp_s0_2;
    s32 var_v0_4;
    TiTexData *texC;
    TiTexData *texA;

    switch (state->cnd_now) {
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
                    draw_flash_virus_lights(&gGfxHead, state, game_map_data[player_no]);
                    break;

                default:
                    break;
            }
            break;

        default:
            break;
    }

    if (evs_score_flag != 0) {
        scoreNums_draw(&st->scoreNums[player_no], &gGfxHead);
    }

    if ((state->cnd_training == dm_cnd_training) && (state->cnd_static == dm_cnd_wait)) {
        texC = &st->texP4[0x1D];
        texA = &st->texP4[0x1E];

        gSPDisplayList(gGfxHead++, alpha_texture_init_dl);

        gDPSetCombineLERP(gGfxHead++, TEXEL0, 0, PRIMITIVE, 0, TEXEL1, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0,
                          COMBINED);

        temp_fv0 = ((s32)sins(((s16)st->blink_count << 9) & 0xFE00) * 0.0038757324f) + 127.0f;

        gDPSetPrimColor(gGfxHead++, 0, 0, 255, 255, 255, temp_fv0);

        temp_fv0 = ((s32)sins(((s16)st->blink_count << 10) & 0xFC00) * 0.00015258789f);
        StretchAlphaTexBlock(&gGfxHead, texC->info[TI_INFO_IDX_WIDTH], texC->info[TI_INFO_IDX_HEIGHT],
                             texC->texs[TI_TEX_TEX], texC->info[TI_INFO_IDX_WIDTH], texA->texs[TI_TEX_TEX],
                             texA->info[TI_INFO_IDX_WIDTH], state->map_x, (state->map_y + temp_fv0 + 0xA0),
                             texC->info[TI_INFO_IDX_WIDTH], texC->info[TI_INFO_IDX_HEIGHT]);
    }

    switch (state->cnd_now) {
        case dm_cnd_stage_clear:
            switch (evs_gamemode) {
                case GMD_TIME_ATTACK:
                    break;

                case GMD_TaiQ:
                    disp_clear_logo(&gGfxHead, player_no, false);
                    break;

                default:
                    disp_clear_logo(&gGfxHead, player_no, true);
                    break;
            }
            break;

        default:
            break;
    }

    switch (state->cnd_now) {
        case dm_cnd_clear_wait:
            disp_allclear_logo(&gGfxHead, player_no, false);
            break;

        default:
            break;
    }

    switch (state->cnd_now) {
        case dm_cnd_gover_wait:
            goto block_28;
            break;

        case dm_cnd_game_over:
            if (evs_gamemode != GMD_TIME_ATTACK) {
            block_28:
                switch (evs_gamemode) {
                    case GMD_TIME_ATTACK:
                        if (evs_game_time >= 0x2A30U) {
                            disp_timeover_logo(&gGfxHead, player_no);
                        } else {
                            disp_gameover_logo(&gGfxHead, player_no);
                        }
                        break;

                    default:
                        disp_gameover_logo(&gGfxHead, player_no);
                        break;
                }
            }
            break;

        default:
            break;
    }

    switch (state->cnd_now) {
        case dm_cnd_retire:
        case dm_cnd_tr_chack:
            if (!st->replayFlag) {
                if (state->player_type == PLAYERTYPE_0) {
                    temp_fv0 = sins(((s16)st->blink_count << 10) & 0xFC00) * ((f32)0x7F / 0x8000) + 0x7F;
                    texC = &st->texP4[0x1B];
                    texA = &st->texP4[0x1C];

                    gSPDisplayList(gGfxHead++, alpha_texture_init_dl);

                    gDPSetCombineLERP(gGfxHead++, TEXEL0, 0, PRIMITIVE, 0, TEXEL1, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED,
                                      0, 0, 0, COMBINED);

                    gDPSetPrimColor(gGfxHead++, 0, 0, 255, 255, 255, temp_fv0);

                    StretchAlphaTexBlock(&gGfxHead, texC->info[TI_INFO_IDX_WIDTH], texC->info[TI_INFO_IDX_HEIGHT],
                                         texC->texs[TI_TEX_TEX], texC->info[TI_INFO_IDX_WIDTH], texA->texs[TI_TEX_TEX],
                                         texA->info[TI_INFO_IDX_WIDTH], (f32)state->map_x, (f32)(state->map_y + 0x5C),
                                         (f32)texC->info[TI_INFO_IDX_WIDTH], (f32)texC->info[TI_INFO_IDX_HEIGHT]);
                }
            }
            disp_retire_logo(&gGfxHead, player_no);
            break;

        case dm_cnd_retire_wait:
            disp_retire_logo(&gGfxHead, player_no);
            break;

        default:
            break;
    }

    switch (state->cnd_now) {
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
                if (evs_gamesel == GSL_1PLAY) {
                    var_v0_4 = 0xA;
                } else {
                    var_v0_4 = 0x4A;
                }
                timeAttackResult_draw(&st->timeAttackResult[player_no], &gGfxHead, state->map_x,
                                      state->map_y + var_v0_4);
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

    switch (state->cnd_now) {
        case dm_cnd_win:
        case dm_cnd_win_retry:
        case dm_cnd_win_retry_sc:
            disp_win_logo(&gGfxHead, player_no);
            break;

        default:
            break;
    }

    switch (state->cnd_now) {
        case dm_cnd_lose:
        case dm_cnd_lose_retry:
        case dm_cnd_lose_retry_sc:
            disp_lose_logo(&gGfxHead, player_no);
            break;

        default:
            break;
    }

    switch (state->cnd_now) {
        case dm_cnd_draw:
        case dm_cnd_draw_retry:
            disp_draw_logo(&gGfxHead, player_no);
            break;

        default:
            break;
    }

    switch (state->cnd_now) {
        case dm_cnd_wait:
        case dm_cnd_init:
            temp_lo = st->count_down_ctrl / (s32)evs_playcnt;
            temp_s0_2 = (st->count_down_ctrl / (s32)evs_playcnt) / 48;

            if (st->count_down_ctrl >= 0) {
                if (disp_count_logo(&gGfxHead, player_no, temp_lo) != 0) {
                    st->count_down_ctrl = -1;
                    if (player_no == 0) {
                        dm_snd_play_in_game(SND_INDEX_73);
                    }
                } else {
                    if ((player_no == 0) && ((temp_s0_2 * 0x30) == (temp_lo - 0x14))) {
                        if (temp_s0_2 < 3) {
                            dm_snd_play_in_game(SND_INDEX_72);
                        }
                    }
                    st->count_down_ctrl++;
                }
            }
            break;

        default:
            break;
    }

    switch (state->cnd_now) {
        case dm_cnd_clear_wait:
        case dm_cnd_gover_wait:
            if ((evs_gamesel == GSL_1PLAY) && (evs_gamemode == GMD_TIME_ATTACK) && (st->effect_timer[player_no] == 0)) {
                push_any_key_draw(state->map_x + 8, state->map_y + 0xA0);
            }
            break;

        default:
            break;
    }

    switch (state->cnd_now) {
        case dm_cnd_pause:
            retryMenu_drawPause(player_no, &gGfxHead, false);
            break;

        case dm_cnd_pause_re:
        case dm_cnd_pause_re_sc:
            retryMenu_drawPause(player_no, &gGfxHead, true);
            break;

        default:
            break;
    }

    switch (state->cnd_now) {
        case dm_cnd_pause:
        case dm_cnd_pause_re:
        case dm_cnd_pause_re_sc:
            switch (evs_gamesel) {
                case GSL_4PLAY:
                    draw_4p_attack_guide_panel(&gGfxHead, st->vs_4p_player_count, player_no, (s32)state->map_x,
                                               state->map_y - 0x24);
                    break;

                default:
                    break;
            }
            break;

        default:
            break;
    }

    switch (state->cnd_now) {
        case dm_cnd_stage_clear:
        case dm_cnd_game_over:
        case dm_cnd_win_retry:
        case dm_cnd_win_retry_sc:
        case dm_cnd_lose_retry:
        case dm_cnd_lose_retry_sc:
        case dm_cnd_draw_retry:
            if (st->effect_timer[player_no] == 0) {
                retryMenu_drawContinue(player_no, &gGfxHead);
            }
            break;

        default:
            break;
    }

    gfxSetScissor(&gGfxHead, GFXSETSCISSOR_INTERLACE_NO, 0, 0, 0x140, 0xF0);
}

/**
 * Original name: dm_game_graphic_effect
 */
void key_cntrol_init(void) {
    s32 i;

    for (i = 0; i < MAXCONTROLLERS; i++) {
        joyflg[i] = ANY_BUTTON & ~(Z_TRIG | START_BUTTON | L_TRIG | R_TRIG);
        joygmf[i] = true;
        joygam[i] = 0;
    }

    joycur1 = evs_keyrept[0];
    joycur2 = evs_keyrept[1];
}

/**
 * Original name: dm_make_key
 */
void dm_make_key(void) {
    s32 count;
    s32 i;

    switch (evs_gamesel) {
        case GSL_1PLAY:
        case GSL_VSCPU:
            count = 1;
            break;

        case GSL_2PLAY:
            count = 2;
            break;

        default:
            count = 4;
            break;
    }

    for (i = 0; i < count; i++) {
        if (game_state_data[i].player_type == PLAYERTYPE_0) {
            if (joygmf[main_joy[i]]) {
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

/**
 * Original name: key_control_main
 */
void key_control_main(struct_game_state_data *state, GameMapCell *map, s32 player_no, s32 joy_no) {
    struct_watchGame *st = watchGame;
    s32 xx[2];
    s32 yy[2];

    load_visible_fall_point_flag();

    if (!UNK_PLAYER0_CHECK(state, player_no)) {
        if (gControllerPressedButtons[joy_no] & (U_CBUTTONS | L_CBUTTONS | R_CBUTTONS | D_CBUTTONS)) {
            visible_fall_point[player_no] = !visible_fall_point[player_no];
        }
    }

    save_visible_fall_point_flag();

    if (state->mode_now == dm_mode_throw) {
        if (!st->demo_flag && dm_calc_capsel_pos(state, xx, yy)) {
            dm_draw_capsel_by_cpu_tentative(state, xx, yy);
        }

        if (state->player_type == PLAYERTYPE_0) {
            if (gControllerHoldButtons[joy_no] & R_JPAD) {
                joyCursorFastSet(R_JPAD, joy_no);
            }
            if (gControllerHoldButtons[joy_no] & L_JPAD) {
                joyCursorFastSet(L_JPAD, joy_no);
            }
        }
    } else if (state->mode_now == dm_mode_down) {
        if (state->cnd_static == dm_cnd_wait) {
            struct_game_state_data_now_cap *cap;

            if (UNK_PLAYER0_CHECK(state, player_no)) {
                u16 temp_s1_2 = joygam[player_no];

                aifKeyOut(state);
                if (st->replayFlag) {
                    joygam[player_no] = temp_s1_2;
                }
            }

            cap = &state->now_cap;
            if (joygam[player_no] & B_BUTTON) {
                rotate_capsel(map, cap, -1);
            } else if (joygam[player_no] & A_BUTTON) {
                rotate_capsel(map, cap, 1);
            }

            if (joygam[player_no] & L_JPAD) {
                translate_capsel(map, state, -1, joy_no);
            } else if (joygam[player_no] & R_JPAD) {
                translate_capsel(map, state, 1, joy_no);
            }

            state->cap_speed_vec = 1;
            if ((joygam[player_no] & D_JPAD) && (cap->pos_y[0] > 0)) {
                s32 val = FallSpeed[state->cap_speed];

                val = (val >> 1) + (val & 1);

                state->cap_speed_vec = val;
            }
        } else if (state->player_type == PLAYERTYPE_0) {
            if (gControllerHoldButtons[joy_no] & R_JPAD) {
                joyCursorFastSet(R_JPAD, joy_no);
            }
            if (gControllerHoldButtons[joy_no] & L_JPAD) {
                joyCursorFastSet(L_JPAD, joy_no);
            }
        }

        if (!st->demo_flag) {
            if (dm_calc_capsel_pos(state, xx, yy)) {
                dm_draw_capsel_by_cpu_tentative(state, xx, yy);
            }
        }
        dm_capsel_down(state, map);
        st->force_draw_capsel_count[player_no] = 2;
    } else {
        if (st->force_draw_capsel_count[player_no] != 0) {
            s32 bak = state->now_cap.capsel_flg_0;

            state->now_cap.capsel_flg_0 = 1;
            if (!st->demo_flag) {
                if (dm_calc_capsel_pos(state, xx, yy)) {
                    dm_draw_capsel_by_cpu_tentative(state, xx, yy);
                }
            }
            state->now_cap.capsel_flg_0 = bak;
            st->force_draw_capsel_count[player_no]--;
        }

        if (state->player_type == PLAYERTYPE_0) {
            joyCursorFastSet(R_JPAD, joy_no);
            joyCursorFastSet(L_JPAD, joy_no);
        }
    }
}

/**
 * Original name: make_ai_main
 */
void make_ai_main(void) {
    s32 i;
    struct_game_state_data *ptr;

    if (!dm_think_flg) {
        return;
    }

    switch (evs_gamesel) {
        case GSL_2PLAY:
        case GSL_VSCPU:
        case GSL_2DEMO:
            for (i = 0; i < 2; i++) {
                ptr = &game_state_data[i];

                if (UNK_PLAYER0_CHECK(ptr, i) && (game_state_data[i].cnd_static == dm_cnd_wait)) {
                    aifMake(&game_state_data[i]);
                }
            }
            break;

        case GSL_4PLAY:
        case GSL_4DEMO:
            for (i = 0; i < 4; i++) {
                ptr = &game_state_data[i];

                if (UNK_PLAYER0_CHECK(ptr, i) && (game_state_data[i].cnd_static == dm_cnd_wait)) {
                    aifMake(&game_state_data[i]);
                }
            }
            break;

        case GSL_1PLAY:
        case GSL_1DEMO:
            if (UNK_PLAYER0_CHECK(game_state_data, 0)) {
                aifMake(&game_state_data[0]);
            }
            break;

        default:
            break;
    }
}

/**
 * Original name: dm_effect_make
 */
void dm_effect_make(void) {
    struct_watchGame *st = watchGame;
    s32 i;

    st->blink_count++;
    st->frame_move_count = CLAMP(st->frame_move_count + st->frame_move_step, 0, FRAME_MOVEMENT_MAX);

    for (i = 0; i < evs_playcnt; i++) {
        if (game_state_data[i].cnd_static == dm_cnd_wait) {
            if (st->started_game_flg && (evs_game_time < 5999 * 60)) {
                evs_game_time++;
            }
            break;
        }
    }
}

/**
 * Original name: dm_game_init_heap
 */
void dm_game_init_heap(void) {
    s32 i;

    heapTop = Heap_bufferp;

    BUFFER_CALLOC(&watchGame, heapTop, sizeof(struct_watchGame));

    for (i = 0; i < ARRAY_COUNTU(gameBackup); i++) {
        BUFFER_MALLOC(&gameBackup[i], heapTop, sizeof(GameStateBackup));
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

/**
 * Original name: dm_game_init
 */
void dm_game_init(bool reinit) {
    struct_watchGame *st = watchGame;
    s32 i;
    s32 j;
    s32 k;
    struct_game_state_data *temp_s0_3;
    struct_game_state_data *var_s0_2;

    if (!reinit || !st->replayFlag) {
        st->replayFlag = 0;
        st->randSeed = (genrand(0xFFFF) + osGetTime()) * 0x10001;
        st->randSeed2 = irandom() + osGetTime();
    }

    sgenrand(st->randSeed);
    randomseed(st->randSeed2);

    if (!reinit) {
        for (i = 0; i < STAR_POS_LEN; i++) {
            st->star_pos_y[i] = 0;
            st->star_pos_x[i] = 0;
        }

        st->star_count = 0;
        starForce_init(&st->starForce, st->star_pos_x, st->star_pos_y);

        // Redundant condition
        if (!reinit) {
            st->retry_coin = 0;
        }
    }

    for (i = 0; i < ARRAY_COUNTU(st->scoreNums); i++) {
        scoreNums_init(&st->scoreNums[i]);
    }

    for (i = 0; i < ARRAY_COUNTU(st->force_draw_capsel_count); i++) {
        st->force_draw_capsel_count[i] = 0;
    }

    st->curtain_count = CURTAIN_COUNT_VAL;
    st->curtain_step = -1;

    for (i = 0; i < ARRAY_COUNTU(st->face_anime_count); i++) {
        st->face_anime_count[i] = 1;
    }

    st->count_down_ctrl = 0;
    st->bgm_bpm_flg[1] = false;
    st->bgm_bpm_flg[0] = false;
    st->last_3_se_flg = false;
    st->last_3_se_cnt = (evs_gamemode == GMD_FLASH) ? 1 : 3;
    st->started_game_flg = main_no != MAIN_GAME;

    for (i = 0; i < ARRAY_COUNTU(st->big_virus_flg); i++) {
        st->big_virus_flg[i] = false;
        st->big_virus_rot[i] = 1 + i * (360 / ARRAY_COUNT(st->big_virus_rot));
        st->big_virus_scale[i] = 1.0f;
    }

    st->big_virus_timer = 0;
    st->big_virus_no_wait = false;
    st->big_virus_stop_count = 0;
    st->big_virus_blink_count = 0;
    st->big_virus_wait = 10.0f;

    switch (evs_gamemode) {
        case GMD_TaiQ:
            st->big_virus_wait = _big_virus_def_wait[game_state_data[0].game_level];
            break;

        default:
            break;
    }

    for (i = 0; i < ARRAY_COUNTU(st->big_virus_count); i++) {
        st->big_virus_count[i] = 0;
    }

    switch (evs_gamesel) {
        case GSL_1DEMO:
        case GSL_2DEMO:
        case GSL_4DEMO:
            st->demo_timer = 1800;
            st->demo_flag = true;
            break;

        default:
            st->demo_timer = 0;
            st->demo_flag = false;
            break;
    }

    st->blink_count = 0;
    st->warning_se_count = 0;

    if (!reinit) {
        for (i = 0; i < ARRAY_COUNT(st->win_count); i++) {
            st->win_count[i] = 0;
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

    for (i = 0; i < ARRAY_COUNT(st->story_4p_stock_cap); i++) {
        for (j = 0; j < ARRAY_COUNT(st->story_4p_stock_cap[i]); j++) {
            st->story_4p_stock_cap[i][j] = -1;
        }
    }

    st->bottom_up_flag = false;
    st->query_play_pause_se = false;
    st->query_pause_player_no = -1;
    st->query_debug_player_no = -1;
    st->query_config_player_no = -1;
    st->passWnd.alpha = 0;
    st->passAlphaStep = -0x10;
    bzero(st->passBuf, sizeof(st->passBuf));

    switch (evs_gamesel) {
        case GSL_1PLAY:
        case GSL_1DEMO:
            k = 0;
            j = 0;
            break;

        case GSL_2PLAY:
        case GSL_VSCPU:
        case GSL_2DEMO:
            k = 0;
            j = 1;
            break;

        case GSL_4PLAY:
        case GSL_4DEMO:
            k = 1;
            j = 2;
            break;

        default:
            break;
    }

    temp_s0_3 = game_state_data;
    for (i = 0; i < ARRAY_COUNT(game_state_data); i++) {
        temp_s0_3[i].map_x = map_x_table_5383[j][i];
        temp_s0_3[i].map_y = map_y_table_5384[k];
        temp_s0_3[i].map_item_size = size_table_5385[k];
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
            case GSL_4PLAY:
            case GSL_4DEMO:
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
    RomOffset(*romTableP)[2] = _romDataTbl;
    struct_watchGame *watchGameP = watchGame;
    s32 pad[2] UNUSED;
    s32 var_v0;
    s32 i;
    struct_evs_mem_data *temp_a3;
    TiTexData *result;
    s8 temp;

    watchGameP->eep_rom_flg = false;

    //! FAKE
    watchGameP->graphic_thread_pri = var_v0 = 0x7F;

    result = tiLoadTexData(&heapTop, romTableP[ROMDATATBL_GAME_AL][ROMTABLEPAIR_START],
                           romTableP[ROMDATATBL_GAME_AL][ROMTABLEPAIR_END]);

    watchGameP->texAL = result;
    watchGameP->texItem = tiLoadTexData(&heapTop, romTableP[ROMDATATBL_GAME_ITEM][ROMTABLEPAIR_START],
                                        romTableP[ROMDATATBL_GAME_ITEM][ROMTABLEPAIR_END]);

    if (main_no != MAIN_GAME) {
        watchGameP->texKaSa = tiLoadTexData(&heapTop, romTableP[ROMDATATBL_MENU_KASA][ROMTABLEPAIR_START],
                                            romTableP[ROMDATATBL_MENU_KASA][ROMTABLEPAIR_END]);
    }

    watchGameP->gameEtcSeg = heapTop;

    heapTop = DecompressRomToRam(romTableP[ROMDATATBL_GAME_ETC][ROMTABLEPAIR_START], heapTop,
                                 romTableP[ROMDATATBL_GAME_ETC][ROMTABLEPAIR_END] -
                                     romTableP[ROMDATATBL_GAME_ETC][ROMTABLEPAIR_START]);

    for (i = 0; i < ARRAY_COUNT(watchGameP->vs_win_count); i++) {
        watchGameP->vs_win_count[i] = 0;
    }

    watchGameP->frame_move_count = 0;
    watchGameP->frame_move_step = 1;
    watchGameP->touch_down_wait = 2;
    _init_coin_logo(0);
    watchGameP->coffee_break_flow = 0;
    watchGameP->coffee_break_timer = 0;
    watchGameP->coffee_break_level = 0;
    watchGameP->coffee_break_shard = 0;

    replay_record_init_buffer(&heapTop);
    replay_record_init(evs_playcnt);

    temp = 0;
    for (i = 0; i < ARRAY_COUNTU(watchGameP->timeAttackResult); i++) {
        timeAttackResult_init(&watchGameP->timeAttackResult[i]);
    }

#if VERSION_US || VERSION_GW
    msgWnd_init2(&watchGameP->passWnd, &heapTop, 0x100, 0xA, 5, temp, 0);
#elif VERSION_CN
    //! FAKE
    msgWnd_init2(&watchGameP->passWnd, &heapTop, 0x100, 0xA, var_v0 = 5, temp, 0);
#else
#error ""
#endif

    watchGameP->passWnd.posX = (SCREEN_WIDTH - 20 * watchGameP->passWnd.colStep) >> 1;
    watchGameP->passWnd.posY = (SCREEN_HEIGHT - 2 * watchGameP->passWnd.rowStep) >> 1;
    RecWritingMsg_init(&watchGameP->writingMsg, &heapTop);

    switch (evs_gamesel) {
        case GSL_1DEMO:
            evs_high_score = 56600;
            break;

        case GSL_1PLAY:
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

        case GSL_2PLAY:
        case GSL_4PLAY:
        case GSL_VSCPU:
        case GSL_2DEMO:
        case GSL_4DEMO:
            if (evs_story_flg == 0) {
                evs_high_score = 0;
            }
            break;

        default:
            return;
    }

    switch (evs_gamesel) {
        case GSL_1PLAY:
        case GSL_1DEMO:
            watchGameP->touch_down_wait = 1;
            animeState_load(&game_state_data[0].anime, &heapTop, CHARANIMEMODE_MARIO);
            animeState_set(&game_state_data[0].anime, ANIMENO_2);
            watchGameP->texP1 = tiLoadTexData(&heapTop, romTableP[ROMDATATBL_GAME_P1][ROMTABLEPAIR_START],
                                              romTableP[ROMDATATBL_GAME_P1][ROMTABLEPAIR_END]);
            watchGameP->texLS = tiLoadTexData(&heapTop, romTableP[ROMDATATBL_GAME_LS][ROMTABLEPAIR_START],
                                              romTableP[ROMDATATBL_GAME_LS][ROMTABLEPAIR_END]);

            for (i = 0; i < ARRAY_COUNT(watchGameP->virus_anime_state); i++) {
                animeState_load(&watchGameP->virus_anime_state[i], &heapTop, i + CHARANIMEMODE_VIRUS_R);
            }

            animeSmog_load(&watchGameP->virus_smog_state[0], &heapTop);
            for (i = 1; i < ARRAY_COUNT(watchGameP->virus_smog_state); i++) {
                animeSmog_init(&watchGameP->virus_smog_state[i], &watchGameP->virus_smog_state[0].animeState[0]);
            }

            msgWnd_init2(&watchGameP->msgWnd, &heapTop, 0x1000, 0x14, 0xF, 0x28, 0xF);
            watchGameP->msgWnd.centering = true;
            msgWnd_addStr(&watchGameP->msgWnd, st_staffroll_txt);
            msgWnd_skip(&watchGameP->msgWnd);
            watchGameP->msgWnd.fontType = FONTTYPE_1;
            watchGameP->msgWnd.contFlags = 0;
            heapTop = init_coffee_break(heapTop, game_state_data[0].cap_def_speed);
            break;

        case GSL_2PLAY:
        case GSL_VSCPU:
        case GSL_2DEMO:
            for (i = 0; i < 2; i++) {
                animeState_load(&game_state_data[i].anime, &heapTop, game_state_data[i].charNo);
            }

            if (evs_story_flg == 0) {
                for (i = 0; i < ARRAY_COUNT(watchGameP->vs_win_total); i++) {
                    watchGameP->vs_win_total[i] = 0;
                }

                switch (evs_gamesel) {
                    case GSL_2PLAY:
                        for (i = 0; i < ARRAY_COUNT(watchGameP->vs_win_total); i++) {
                            watchGameP->vs_win_total[i] = evs_mem_data[evs_select_name_no[i]].vsman_data[0];
                        }
                        break;

                    default:
                        break;
                }
            }

            watchGameP->texP1 = tiLoadTexData(&heapTop, romTableP[ROMDATATBL_GAME_P1][ROMTABLEPAIR_START],
                                              romTableP[ROMDATATBL_GAME_P1][ROMTABLEPAIR_END]);
            watchGameP->texP2 = tiLoadTexData(&heapTop, romTableP[ROMDATATBL_GAME_P2][ROMTABLEPAIR_START],
                                              romTableP[ROMDATATBL_GAME_P2][ROMTABLEPAIR_END]);
            break;

        case GSL_4PLAY:
        case GSL_4DEMO:
            watchGameP->texP1 = tiLoadTexData(&heapTop, romTableP[ROMDATATBL_GAME_P1][ROMTABLEPAIR_START],
                                              romTableP[ROMDATATBL_GAME_P1][ROMTABLEPAIR_END]);
            watchGameP->texP4 = tiLoadTexData(&heapTop, romTableP[ROMDATATBL_GAME_P4][ROMTABLEPAIR_START],
                                              romTableP[ROMDATATBL_GAME_P4][ROMTABLEPAIR_END]);

            for (i = 0; i < ARRAY_COUNT(game_state_data); i++) {
                animeState_load(&game_state_data[i].anime, &heapTop, game_state_data[i].charNo);
            }

            for (i = 0; i < ARRAY_COUNT(watchGameP->story_4p_name_num); i++) {
                watchGameP->story_4p_name_num[i] = 0;
            }

            for (i = 0; i < ARRAY_COUNT(watchGameP->story_4p_name_num); i++) {
                watchGameP->story_4p_name_num[game_state_data[i].team_no]++;
            }

            watchGameP->vs_4p_player_count = 0;

            for (i = 0; i < ARRAY_COUNT(game_state_data); i++) {
                if (game_state_data[i].player_type == PLAYERTYPE_0) {
                    watchGameP->vs_4p_player_count++;
                }
            }

            if (watchGameP->story_4p_name_num[0] == 1) {
                if (watchGameP->story_4p_name_num[1] == watchGameP->story_4p_name_num[0]) {
                    if (watchGameP->story_4p_name_num[2] == watchGameP->story_4p_name_num[1]) {
                        if (watchGameP->story_4p_name_num[3] == watchGameP->story_4p_name_num[2]) {
                            watchGameP->vs_4p_team_flg = false;
                            return;
                        }
                    }
                }
            }

            watchGameP->vs_4p_team_flg = true;
            watchGameP->vs_4p_team_bits[1] = 0;
            watchGameP->vs_4p_team_bits[0] = 0;

            for (i = 0; i < ARRAY_COUNT(game_state_data); i++) {
                if (game_state_data[i].team_no == TEAMNUMBER_0) {
                    watchGameP->vs_4p_team_bits[0] |= (1 << i);
                }
            }

            for (i = 0; i < ARRAY_COUNT(game_state_data); i++) {
                if (game_state_data[i].team_no == TEAMNUMBER_1) {
                    watchGameP->vs_4p_team_bits[1] |= (1 << i);
                }
            }
            break;

        default:
            break;
    }
}

void dm_game_init_snap_bg(void) {
    struct_watchGame *watchGameP = watchGame;

    BUFFER_MALLOC64(&watchGameP->bg_snap_buf, heapTop, sizeof(u16) * ((SCREEN_WIDTH + 8) * SCREEN_HEIGHT));
    watchGameP->bg_snapping = false;

    switch (evs_gamesel) {
        case GSL_1PLAY:
        case GSL_1DEMO:
            break;

        default:
            heapTop = story_bg_init(story_proc_no, heapTop);
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

    if (temp_s7->bg_snapping) {
        gDPSetColorImage(gfx++, G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WIDTH + 8,
                         osVirtualToPhysical(temp_s7->bg_snap_buf));
    }

    switch (evs_gamesel) {
        case GSL_1PLAY:
        case GSL_1DEMO:
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

            temp_s1 = &temp_s7->texLS[_bgTex_5794[var_s6]];

            for (i = 0; i < ARRAY_COUNTU(_bgPos_5792); i++) {
                tiStretchTexTile(&gfx, temp_s1, false, 0, 0, temp_s1->info[TI_INFO_IDX_WIDTH],
                                 temp_s1->info[TI_INFO_IDX_HEIGHT], _bgPos_5792[i][0], _bgPos_5792[i][1],
                                 temp_s1->info[TI_INFO_IDX_WIDTH], temp_s1->info[TI_INFO_IDX_HEIGHT]);
            }

            temp_s1 = &temp_s7->texLS[_magTex_5795[var_s6]];
            tiStretchTexTile(&gfx, temp_s1, false, 0, 0, temp_s1->info[TI_INFO_IDX_WIDTH],
                             temp_s1->info[TI_INFO_IDX_HEIGHT], 0.0f, 120.0f, temp_s1->info[TI_INFO_IDX_WIDTH],
                             temp_s1->info[TI_INFO_IDX_HEIGHT]);

            if (arg3 != 0) {
                gSPDisplayList(gfx++, alpha_texture_init_dl);

                temp_s1 = &temp_s7->texLS[9];
                temp_s2 = &temp_s7->texLS[2];

                var_s0_2 = MIN(temp_s1->info[TI_INFO_IDX_WIDTH], temp_s2->info[TI_INFO_IDX_WIDTH]);

                StretchAlphaTexTile(&gfx, var_s0_2, temp_s1->info[TI_INFO_IDX_HEIGHT], temp_s1->texs[TI_TEX_TEX],
                                    temp_s1->info[TI_INFO_IDX_WIDTH], temp_s2->texs[TI_TEX_TEX], *temp_s2->info, 0, 0,
                                    var_s0_2, temp_s1->info[TI_INFO_IDX_HEIGHT], 202.0f, 12.0f, var_s0_2,
                                    temp_s1->info[TI_INFO_IDX_HEIGHT]);

                temp_s1 = &temp_s7->texLS[_scrTex_5796[var_s6]];
                temp_s2 = &temp_s7->texLS[1];

                var_s0_2 = MIN(temp_s1->info[TI_INFO_IDX_WIDTH], temp_s2->info[TI_INFO_IDX_WIDTH]);

                StretchAlphaTexTile(&gfx, var_s0_2, temp_s1->info[TI_INFO_IDX_HEIGHT], temp_s1->texs[TI_TEX_TEX],
                                    temp_s1->info[TI_INFO_IDX_WIDTH], temp_s2->texs[TI_TEX_TEX],
                                    temp_s2->info[TI_INFO_IDX_WIDTH], 0, 0, var_s0_2, temp_s1->info[TI_INFO_IDX_HEIGHT],
                                    11.0f, 17.0f, var_s0_2, temp_s1->info[TI_INFO_IDX_HEIGHT]);

                temp_s2 = &temp_s7->texLS[4];

                for (i = 0; i < ARRAY_COUNTU(_panelTex_5797[var_s6]); i++) {
                    temp_s1 = &temp_s7->texLS[_panelTex_5797[var_s6][i]];

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
                        temp_s1 = &temp_s7->texLS[0xA];
                        temp_s2 = &temp_s7->texLS[3];
                        tiStretchAlphaTexItem(&gfx, temp_s1, temp_s2, false, 3, game_state_data->game_level, 232.0f,
                                              120.0f, 48.0f, 16.0f);
                        break;

                    default:
                        break;
                }

                temp_s1 = &temp_s7->texLS[5];
                temp_s2 = &temp_s7->texLS[0];
                tiStretchAlphaTexItem(&gfx, temp_s1, temp_s2, false, 3, game_state_data->cap_def_speed, 232.0f, 162.0f,
                                      48.0f, 16.0f);
            }

            gSPDisplayList(gfx++, normal_texture_init_dl);

            gDPSetCombineMode(gfx++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
            gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
            gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, 96);

            // Why draw twice?
            temp_s1 = &temp_s7->texP1[1];
            for (i = 0; i < 2; i++) {
                tiStretchTexBlock(&gfx, temp_s1, false, 110.0f, 16.0f, temp_s1->info[TI_INFO_IDX_WIDTH],
                                  temp_s1->info[TI_INFO_IDX_HEIGHT]);
            }

            temp_s1 = &temp_s7->texP1[0];
            for (i = 0; i < 2; i++) {
                tiCopyTexBlock(&gfx, temp_s1, false, 110, 16);
            }
            break;

        case GSL_4PLAY:
        case GSL_4DEMO:
            story_bg_proc(&gfx);

            gSPDisplayList(gfx++, normal_texture_init_dl);

            gDPSetCombineMode(gfx++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
            gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
            gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, 192);

            temp_s1 = &temp_s7->texP4[1];
            for (i = 0; i < ARRAY_COUNT(_posP4Bottle); i++) {
                tiStretchTexBlock(&gfx, temp_s1, false, _posP4Bottle[i][0] + RO_800B1D7C[0],
                                  _posP4Bottle[i][1] + RO_800B1D7C[1], temp_s1->info[TI_INFO_IDX_WIDTH],
                                  temp_s1->info[TI_INFO_IDX_HEIGHT]);
            }

            temp_s1 = &temp_s7->texP4[0];

            for (i = 0; i < ARRAY_COUNT(_posP4Bottle); i++) {
                tiCopyTexBlock(&gfx, temp_s1, false, _posP4Bottle[i][0], _posP4Bottle[i][1]);
            }

            if (arg3 != 0) {
                gSPDisplayList(gfx++, normal_texture_init_dl);

                temp_s1 = &temp_s7->texP4[8];
                for (i = 0; i < ARRAY_COUNT(_posP4CharBase); i++) {
                    tiStretchTexBlock(&gfx, temp_s1, false, _posP4CharBase[i][0], _posP4CharBase[i][1],
                                      temp_s1->info[TI_INFO_IDX_WIDTH], temp_s1->info[TI_INFO_IDX_HEIGHT]);
                }

                gSPDisplayList(gfx++, alpha_texture_init_dl);

                if ((evs_story_flg != 0) || !temp_s7->vs_4p_team_flg) {
                    if (evs_gamemode == GMD_FLASH) {
                        temp_s1 = &temp_s7->texP4[0xB];
                        temp_s2 = &temp_s7->texP4[0x13];
                    } else {
                        temp_s1 = &temp_s7->texP4[0x19];
                        temp_s2 = &temp_s7->texP4[0x1A];
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
                    temp_s1 = &temp_s7->texP4[0xF];
                    temp_s2 = &temp_s7->texP4[0x17];

                    var_s0_2 = MIN(temp_s1->info[TI_INFO_IDX_WIDTH], temp_s2->info[TI_INFO_IDX_WIDTH]);

                    StretchAlphaTexBlock(&gfx, var_s0_2, temp_s1->info[TI_INFO_IDX_HEIGHT], temp_s1->texs[TI_TEX_TEX],
                                         temp_s1->info[TI_INFO_IDX_WIDTH], temp_s2->texs[TI_TEX_TEX],
                                         temp_s1->info[TI_INFO_IDX_WIDTH], 16.0f, 11.0f, var_s0_2,
                                         temp_s1->info[TI_INFO_IDX_HEIGHT]);
                } else if (temp_s7->vs_4p_team_flg) {
                    for (i = 0; i < 4; i++) {
                        s32 temp_v0_9;

                        temp_v0_9 = game_state_data[i].team_no != TEAMNUMBER_0;
                        temp_s1 = &temp_s7->texP4[tbl_5867[temp_v0_9][0]];
                        temp_s2 = &temp_s7->texP4[tbl_5867[temp_v0_9][1]];

                        var_s0_2 = MIN(temp_s1->info[TI_INFO_IDX_WIDTH], temp_s2->info[TI_INFO_IDX_WIDTH]);

                        StretchAlphaTexBlock(&gfx, var_s0_2, temp_s1->info[TI_INFO_IDX_HEIGHT],
                                             temp_s1->texs[TI_TEX_TEX], temp_s1->info[TI_INFO_IDX_WIDTH],
                                             temp_s2->texs[TI_TEX_TEX], temp_s1->info[TI_INFO_IDX_WIDTH],
                                             _posP4CharBase[i][0] + 0x19, _posP4CharBase[i][1], var_s0_2,
                                             temp_s1->info[TI_INFO_IDX_HEIGHT]);
                    }

                    //! FAKE:
                    temp_s1 = temp_s7->texP4 + 2 + evs_vs_count - 1;

                    CopyTexBlock8(&gfx, temp_s1->texs[TI_TEX_TLUT], temp_s1->texs[TI_TEX_TEX], 0x10, 8,
                                  temp_s1->info[TI_INFO_IDX_WIDTH], temp_s1->info[TI_INFO_IDX_HEIGHT]);
                } else {
                    //! FAKE:
                    temp_s1 = temp_s7->texP4 + 5 + evs_vs_count - 1;

                    CopyTexBlock8(&gfx, temp_s1->texs[TI_TEX_TLUT], temp_s1->texs[TI_TEX_TEX], 0x10, 0xB,
                                  temp_s1->info[TI_INFO_IDX_WIDTH], temp_s1->info[TI_INFO_IDX_HEIGHT]);
                }
            }
            break;

        case GSL_2PLAY:
        case GSL_VSCPU:
        case GSL_2DEMO:
            story_bg_proc(&gfx);
            if (arg3 != 0) {
                gSPDisplayList(gfx++, alpha_texture_init_dl);

                if (evs_story_flg != 0) {
                    temp_s1 = &temp_s7->texP2[8];
                } else {
                    temp_s1 = &temp_s7->texP2[0xE];
                }
                temp_s2 = &temp_s7->texP2[0];

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

    CopyTexBlock16(&gfx, watchGame->bg_snap_buf, 0, 0, SCREEN_WIDTH + 8, SCREEN_HEIGHT);
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

    key_cntrol_init();

    osCreateMesgQueue(&scMQ, scMsgBuf, ARRAY_COUNT(scMsgBuf));
    nnScAddClient(sc, &scClient, &scMQ);
    BgTasksManager_Init();

    dm_game_init_heap();
    watchGameP = watchGame;
    dm_game_init_static();
    dm_game_init_snap_bg();
    watchGameP->bg_snapping = true;
    dm_game_init(false);
    backup_game_state(0);
    dm_think_flg = true;
    gGfxHead = gGfxGlist[gfx_gtask_no];

    while (var_s2 || (watchGameP->curtain_count != CURTAIN_COUNT_VAL)) {
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
            if (watchGameP->curtain_step < 0) {
                watchGameP->curtain_step = -watchGameP->curtain_step;
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

            if (watchGameP->demo_flag) {
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

    dm_think_flg = false;
    watchGameP->graphic_thread_pri = THREAD_PRI_GRAPHIC;

    while (watchGameP->graphic_thread_pri != 0) {
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
    DmMainCnt var_s4_2;
    s32 var_s0;

    if (temp_s3->bgm_bpm_flg[1]) {
        dm_seq_play_in_game((evs_seqnumb * 2) + 1);
        temp_s3->bgm_bpm_flg[1] = false;
    }

    dm_effect_make();
    RecWritingMsg_calc(&temp_s3->writingMsg);

    switch (evs_gamesel) {
        case GSL_1PLAY:
            if (temp_s3->coffee_break_flow > 0) {
                if (gControllerHoldButtons[main_joy[0]] & (A_BUTTON | B_BUTTON)) {
                    temp_s3->msgWnd.scrSpeed = 1.0f / 8.0f;
                } else {
                    temp_s3->msgWnd.scrSpeed = 1.0f / 60.0f;
                }
                msgWnd_update(&temp_s3->msgWnd);

                switch (temp_s3->coffee_break_flow) {
                    case 0x1:
                        if (!(gControllerPressedButtons[main_joy[0]] & START_BUTTON)) {
                            if (!msgWnd_isScroll(&temp_s3->msgWnd)) {
                                temp_s3->coffee_break_flow = 2;
                            }
                        } else {
                            temp_s3->coffee_break_flow = 0;
                        }
                        break;

                    case 0x2:
                        if (temp_s3->coffee_break_timer < 360) {
                            temp_s3->coffee_break_timer++;
                        } else if (gControllerPressedButtons[main_joy[0]] & ANY_BUTTON) {
                            temp_s3->coffee_break_flow = 0;
                        }
                        break;
                }
                if (temp_s3->coffee_break_flow == 0) {
                    dm_seq_play_in_game(evs_seqnumb * 2);
                }
                var_s4_2 = dm_ret_null;
            }

            if (temp_s3->coffee_break_flow <= 0) {
                var_s4_2 = dm_game_main_1p();

                switch (var_s4_2) {
                    case dm_ret_next_stage:
                        var_s0 = game_state_data[0].virus_level;
                        if ((var_s0 == 0x15) || (var_s0 == 0x18) ||
                            ((var_s0 >= 0x1E) && (var_s0 == ((var_s0 / 5) * 5)))) {
                            temp_s3->coffee_break_flow = 1;
                            if (var_s0 >= 0x1E) {
                                if (var_s0 < 0x28) {
                                    temp_s3->coffee_break_level = 1;
                                } else {
                                    temp_s3->coffee_break_level = 2;
                                }
                            } else {
                                temp_s3->coffee_break_level = 0;
                            }

                            if (var_s0 < 0x1E) {
                                temp_s3->coffee_break_shard = (var_s0 - 0x15) / 3;
                            } else {
                                temp_s3->coffee_break_shard = (var_s0 / 5) & 1;
                            }
                        }

                        if (temp_s3->coffee_break_flow == 1) {
                            temp_s3->coffee_break_timer = 0;
                            init_coffee_break_cnt();
                            msgWnd_clear(&temp_s3->msgWnd);
                            msgWnd_addStr(&temp_s3->msgWnd, st_staffroll_txt);
                            msgWnd_skip(&temp_s3->msgWnd);
                        }

                        if (game_state_data[0].virus_level < 0x63U) {
                            game_state_data[0].virus_level++;
                        }
                        break;

                    case dm_ret_retry:
                        game_state_data[0].game_score = 0;
                        break;

                    case dm_ret_replay:
                        var_s4_2 = dm_ret_null;
                        dm_game_init(true);
                        break;

                    default:
                        break;
                }

                switch (var_s4_2) {
                    case dm_ret_next_stage:
                    case dm_ret_retry:
                        var_s4_2 = dm_ret_null;
                        dm_game_init(true);
                        animeState_set(&game_state_data[0].anime, ANIMENO_2);

                        for (var_s0 = 0; var_s0 < ANIMES_COUNT; var_s0++) {
                            animeState_set(&temp_s3->virus_anime_state[var_s0], ANIMENO_0);
                            animeSmog_stop(&temp_s3->virus_smog_state[var_s0]);
                        }

                        var_s0 = temp_s3->coffee_break_flow;
                        temp_s3->coffee_break_flow = 0;
                        backup_game_state(0);
                        temp_s3->coffee_break_flow = var_s0;
                        if (temp_s3->coffee_break_flow > 0) {
                            dm_seq_play_in_game(SEQ_INDEX_23);
                        }
                        break;

                    default:
                        break;
                }
            }
            break;

        case GSL_2PLAY:
        case GSL_VSCPU:
            var_s4_2 = dm_game_main_2p();

            for (var_s0 = 0; var_s0 < 2; var_s0++) {
                if (evs_story_flg != 0) {
                    if (temp_s3->win_count[var_s0] > 0) {
                        var_s1 = 1;
                    }
                } else if (temp_s3->win_count[var_s0] == evs_vs_count) {
                    var_s1 = 1;
                }
            }

            switch (var_s4_2) {
                case dm_ret_game_over:
                    if (var_s1 == 0) {
                        var_s4_2 = dm_ret_null;
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

                case dm_ret_retry:
                    var_s4_2 = dm_ret_null;
                    for (var_s0 = 0; var_s0 < 2; var_s0++) {
                        game_state_data[var_s0].game_score = 0;
                    }

                    dm_game_init(false);

                    for (var_s0 = 0; var_s0 < 2; var_s0++) {
                        animeState_set(&game_state_data[var_s0].anime, ANIMENO_0);
                    }

                    backup_game_state(0);
                    break;

                case dm_ret_replay:
                    var_s4_2 = dm_ret_null;
                    dm_game_init(true);
                    break;

                default:
                    break;
            }
            break;

        case GSL_4PLAY:
            var_s4_2 = dm_game_main_4p();

            for (var_s0 = 0; var_s0 < 4; var_s0++) {
                if (evs_story_flg != 0) {
                    if (temp_s3->win_count[var_s0] > 0) {
                        var_s1 = 1;
                    }
                } else if (temp_s3->win_count[var_s0] == evs_vs_count) {
                    var_s1 = 1;
                }
            }

            switch (var_s4_2) {
                case dm_ret_game_over:
                    if (var_s1 == 0) {
                        var_s4_2 = dm_ret_null;
                        dm_game_init(true);
                        for (var_s0 = 0; var_s0 < 4; var_s0++) {
                            animeState_set(&game_state_data[var_s0].anime, ANIMENO_0);
                        }
                        backup_game_state(0);
                    }
                    break;

                case dm_ret_retry:
                    var_s4_2 = dm_ret_null;
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

                case dm_ret_replay:
                    var_s4_2 = dm_ret_null;
                    dm_game_init(true);
                    break;

                default:
                    break;
            }
            break;

        case GSL_1DEMO:
            var_s4_2 = dm_game_demo_1p();
            break;

        case GSL_2DEMO:
            var_s4_2 = dm_game_demo_2p();
            break;

        case GSL_4DEMO:
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
        case GSL_1PLAY:
        case GSL_2PLAY:
            var_a1 = MAIN_MENU;
            break;

        case GSL_4PLAY:
            if (evs_story_flg != 0) {
                evs_gamesel = GSL_VSCPU;
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

        case GSL_VSCPU:
            if (evs_story_flg != 0) {
                if ((game_state_data[0].cnd_static == dm_cnd_win) && (arg0 != -2)) {
                    if (dm_query_next_stage(evs_story_level, evs_story_no, game_state_data[0].game_retry)) {
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

        case GSL_1DEMO:
        case GSL_2DEMO:
        case GSL_4DEMO:
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

    if (watchGameP->graphic_thread_pri != 0x7F) {
        osSetThreadPri(NULL, THREAD_PRI_GRAPHIC);
        watchGameP->graphic_thread_pri = 0;
        return;
    }

    RecWritingMsg_draw(&watchGameP->writingMsg, &gGfxHead);

    gDPFullSync(gGfxHead++);
    gSPEndDisplayList(gGfxHead++);

    osWritebackDCacheAll();

    gfxTaskStart(&B_800FAE80[gfx_gtask_no], gGfxGlist[gfx_gtask_no], (gGfxHead - gGfxGlist[gfx_gtask_no]) * sizeof(Gfx),
                 0, !watchGameP->bg_snapping ? OS_SC_SWAPBUFFER : 0);
    osSetThreadPri(NULL, THREAD_PRI_GRAPHIC);
    dm_game_graphic2();
    osSetThreadPri(NULL, OS_PRIORITY_APPMAX);
}

const s32 _x_6416[] = { 0x77, 0xB6 };
static_assert(ARRAY_COUNT(watchGame->vs_win_total) == ARRAY_COUNT(_x_6416), "");

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
        if (temp_s7->frame_move_count < FRAME_MOVEMENT_MAX) {
            dm_game_draw_snap_bg(&gGfxHead, &mtx, &vtx, 1);
        } else if (temp_s7->coffee_break_flow == 0) {
            func_8006F628(&gGfxHead);
        }
    }

    switch (evs_gamesel) {
        case GSL_2PLAY:
        case GSL_VSCPU:
        case GSL_2DEMO: {
            s32 temp_s4 = temp_s7->frame_move_count;
            bool temp_s0 = temp_s7->frame_move_count < FRAME_MOVEMENT_MAX;
            bool temp_s1 = !temp_s7->bg_snapping;

            if (!debugMenuEnabled) {
                if (temp_s7->bg_snapping) {
                    temp_s7->frame_move_count = FRAME_MOVEMENT_MAX;
                }
                dm_calc_bottle_2p();
                if (temp_s0 != 0) {
                    dm_draw_bottle_2p(&gGfxHead);
                }

                i = (FRAME_MOVEMENT_MAX - temp_s7->frame_move_count) * 6;
                if (evs_story_flg != 0) {
                    draw_story_board(&gGfxHead, 0, -i, temp_s0, temp_s1);
                } else {
                    draw_vsmode_board(&gGfxHead, 0, -i, temp_s0, temp_s1);
                }
                temp_s7->frame_move_count = temp_s4;
            }
        } break;

        default:
            break;
    }

    switch (evs_gamesel) {
        case GSL_2PLAY:
        case GSL_4PLAY:
        case GSL_VSCPU:
        case GSL_2DEMO:
        case GSL_4DEMO:
            if (!debugMenuEnabled && !temp_s7->bg_snapping) {
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
        case GSL_1PLAY:
        case GSL_1DEMO:
            if (!debugMenuEnabled && !temp_s7->bg_snapping) {
                disp_logo_setup(&gGfxHead);

                if (temp_s7->coffee_break_flow > 0) {
                    draw_coffee_break(&gGfxHead, temp_s7->coffee_break_level, temp_s7->coffee_break_shard,
                                      temp_s7->coffee_break_flow > 1);
                    msgWnd_draw(&temp_s7->msgWnd, &gGfxHead);
                    if (temp_s7->coffee_break_timer == 360) {
                        push_any_key_draw(0x80, 0xC0);
                    }
                } else {
                    animeState_initDL(&game_state_data[0].anime, &gGfxHead);
                    animeState_draw(&game_state_data[0].anime, &gGfxHead, 250.0f, 84.0f, 1.0f, 1.0f);

                    dm_virus_anime(&game_state_data[0], game_map_data[0]);
                    dm_game_graphic_1p(&game_state_data[0], 0, game_map_data[0]);
                    _disp_coin_logo(&gGfxHead, temp_s7->retry_coin);

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
                            draw_time(&gGfxHead, evs_game_time, RO_800B1D28[0], RO_800B1D28[1]);
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
                    if (temp_s7->big_virus_stop_count != 0) {
                        disp_timestop_logo(&gGfxHead, 0);
                    }
                }
            }
            break;

        case GSL_2PLAY:
        case GSL_VSCPU:
        case GSL_2DEMO:
            if (!debugMenuEnabled && !temp_s7->bg_snapping) {
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
                        draw_time(&gGfxHead, evs_game_time, 0x9A, 0xA7);
                        break;
                }

                if (evs_story_flg != 0) {
                    for (i = cached = 0; i < 2U; i++) {
                        if (temp_s7->win_count[i] == 0) {
                            draw_star_base(&gGfxHead, _posStStar[i][0], _posStStar[i][1], cached);
                            cached++;
                        }
                    }
                } else {
                    for (i = 0; i < ARRAY_COUNT(watchGame->vs_win_total); i++) {
                        draw_count_number(&gGfxHead, 0, 2, temp_s7->vs_win_total[i], _x_6416[i], 0x98);
                    }

                    for (i = cached = 0; i < 2; i++) {
                        for (j = temp_s7->win_count[i]; j < evs_vs_count; j++) {
                            draw_star_base(&gGfxHead, _posP2StarX[i], _posP2StarY[evs_vs_count - 1][j], cached);
                            cached++;
                        }
                    }
                }

                switch (evs_gamemode) {
                    case GMD_FLASH:
                        var_s6 = &temp_s7->texP2[7];
                        break;

                    default:
                        var_s6 = &temp_s7->texP2[0xF];
                        break;
                }
                var_t2 = &temp_s7->texP2[1];

                StretchAlphaTexBlock(&gGfxHead, var_s6->info[TI_INFO_IDX_WIDTH], var_s6->info[TI_INFO_IDX_HEIGHT],
                                     var_s6->texs[TI_TEX_TEX], var_s6->info[TI_INFO_IDX_WIDTH],
                                     var_t2->texs[TI_TEX_TEX], var_t2->info[TI_INFO_IDX_WIDTH], 131.0f, 181.0f,
                                     var_s6->info[TI_INFO_IDX_WIDTH], var_s6->info[TI_INFO_IDX_HEIGHT]);

                starForce_calc(&temp_s7->starForce, temp_s7->star_count);
                starForce_draw(&temp_s7->starForce, &gGfxHead, temp_s7->star_count);

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

        case GSL_4PLAY:
        case GSL_4DEMO:
            if (!debugMenuEnabled && !temp_s7->bg_snapping) {
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
                    draw_time(&gGfxHead, evs_game_time, 0x3B, 0x12);

                    for (i = cached = 0; i < ARRAY_COUNTU(temp_s7->win_count); i++) {
                        if (temp_s7->win_count[i] == 0) {
                            draw_star_base(&gGfxHead, _posStP4StarX[i], 0xD, cached);
                            cached++;
                        }
                    }
                } else if (temp_s7->vs_4p_team_flg) {
                    s32 a;
                    s32 b;
                    s32 temp_s5;
                    s32 temp_s2_4;
                    s32 temp_a3_10;

                    var_s6 = &temp_s7->texP4[0xE];
                    var_t2 = &temp_s7->texP4[0x16];

                    temp_s5 = var_s6->info[TI_INFO_IDX_WIDTH] >> 1;
                    temp_s2_4 = var_s6->info[TI_INFO_IDX_HEIGHT] / 3;

                    for (i = 0; i < 2; i++) {
                        for (j = 0; j < 4; j++) {
                            temp_a3_10 = temp_s7->story_4p_stock_cap[i][j];
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
                        for (j = temp_s7->win_count[i]; j < evs_vs_count; j++) {
                            draw_star_base(&gGfxHead, _posP4TeamStarX[evs_vs_count - 1][i][j], 0xD, cached);
                            cached++;
                        }
                    }
                } else {
                    for (i = cached = 0; i < 4; i++) {
                        for (j = temp_s7->win_count[i]; j < evs_vs_count; j++) {
                            draw_star_base(&gGfxHead, _posP4CharStarX[evs_vs_count - 1][i][j], 0xD, cached);
                            cached++;
                        }
                    }
                }

                starForce_calc(&temp_s7->starForce, temp_s7->star_count);
                starForce_draw(&temp_s7->starForce, &gGfxHead, temp_s7->star_count);

                for (i = 0; i < 4; i++) {
                    dm_game_graphic_effect(&game_state_data[i], i, 1);
                }
                disp_attack_effect(&gGfxHead);
            }
            break;

        default:
            break;
    }

    if (!temp_s7->bg_snapping) {
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
            case GSL_1DEMO:
            case GSL_2DEMO:
            case GSL_4DEMO:
                draw_demo_logo(&gGfxHead, 0x6A, 0xAA);

#if VERSION_CN || VERSION_GW
                gDPPipeSync(gGfxHead++);
#endif
                break;

            default:
                break;
        }

        if (temp_s7->replayFlag && !dm_check_one_game_finish()) {
            s32 sp50;
            s32 sp54;

            switch (evs_gamesel) {
                case GSL_1PLAY:
                case GSL_4PLAY:
                    sp50 = 0x1E;
                    sp54 = 0x14;
                    break;

                case GSL_2PLAY:
                case GSL_VSCPU:
                    sp50 = 0x80;
                    sp54 = 0x90;
                    break;

                default:
                    break;
            }

            draw_replay_logo(&gGfxHead, sp50, sp54);

            //! FAKE
            j = temp_s7->win_count[i];
        }

        if (temp_s7->passWnd.alpha > 0) {
            var_s6 = &temp_s7->texAL[0xC];

            gSPDisplayList(gGfxHead++, normal_texture_init_dl);
            gDPSetCombineLERP(gGfxHead++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, PRIMITIVE, TEXEL0, 0,
                              PRIMITIVE, 0);
            gDPSetRenderMode(gGfxHead++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
            gDPSetPrimColor(gGfxHead++, 0, 0, 255, 255, 200, temp_s7->passWnd.alpha);
            gDPSetTextureLUT(gGfxHead++, G_TT_NONE);

            gDPLoadTextureBlock_4b(gGfxHead++, var_s6->texs[TI_TEX_TEX], G_IM_FMT_I, var_s6->info[TI_INFO_IDX_WIDTH],
                                   var_s6->info[TI_INFO_IDX_HEIGHT], 0, G_TX_NOMIRROR, G_TX_NOMIRROR, G_TX_NOMASK,
                                   G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

            drawCursorPattern(&gGfxHead, var_s6->info[TI_INFO_IDX_WIDTH], var_s6->info[TI_INFO_IDX_HEIGHT], 0x10, 0x10,
                              temp_s7->passWnd.posX - 6, temp_s7->passWnd.posY - 6,
                              (temp_s7->passWnd.colStep * 0x14) + 0xC, (temp_s7->passWnd.rowStep * 3) + 0xC);

            msgWnd_update(&temp_s7->passWnd);
            msgWnd_draw(&temp_s7->passWnd, &gGfxHead);
        }

        temp_s7->passWnd.alpha = CLAMP(temp_s7->passWnd.alpha + temp_s7->passAlphaStep, 0, 0xFF);

        temp_s7->curtain_count = CLAMP(temp_s7->curtain_count + temp_s7->curtain_step, 0, CURTAIN_COUNT_VAL);

        curtain_proc(&gGfxHead, temp_s7->curtain_count);
    }

#ifdef NN_SC_PERF
    if (!temp_s7->bg_snapping) {
        if (D_800BEF08_cn != 0) {
            func_8002BD7C_cn(&gGfxHead, 0x20, 0xB4);
        }
    }
#endif

    if (temp_s7->bg_snapping) {
        temp_s7->bg_snapping = false;
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

    if (watchGameP->eep_rom_flg) {
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
        bool temp_s1 = dm_check_one_game_finish();

        dm_make_key();

        for (i = 0; i < evs_playcnt; i++) {
            if (game_state_data[i].cnd_static == dm_cnd_pause) {
                var_s3 = true;
                break;
            }
        }

        if (!var_s3 && watchGameP->started_game_flg) {
            aiCOM_MissTake();
        }

        if (watchGameP->replayFlag && !var_s3 && !temp_s1 && watchGameP->started_game_flg) {
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

        watchGameP->big_virus_no_wait = (evs_gamemode == GMD_TaiQ) && (joygam[0] & (L_TRIG | R_TRIG));

        switch (evs_gamesel) {
            case GSL_1PLAY:
                key_control_main(&game_state_data[0], game_map_data[0], 0, main_joy[0]);
                break;

            case GSL_2PLAY:
            case GSL_VSCPU:
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

        if (!watchGameP->replayFlag && !var_s3) {
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
    msgWnd_init2(&watchGameP->msgWnd, &heapTop, 0x1000, 0x12, 0x10, 0x34, 0x22);
    msgWnd_addStr(&watchGameP->msgWnd, EndingLastMessage);
    watchGameP->msgWnd.fontType = FONTTYPE_1;
    watchGameP->msgWnd.centering = true;

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

        switch (watchGameP->coffee_break_flow) {
            case 0x0:
                if (watchGameP->coffee_break_timer == 255) {
                    watchGameP->coffee_break_flow = 1;
                } else {
                    watchGameP->coffee_break_timer = MIN(255, watchGameP->coffee_break_timer + 4);
                }
                break;

            case 0x1:
                if (msgWnd_isEnd(&watchGameP->msgWnd)) {
                    watchGameP->coffee_break_flow++;
                } else {
                    msgWnd_update(&watchGameP->msgWnd);
                }
                break;

            case 0x2:
                if (gControllerPressedButtons[main_joy[0]] & ANY_BUTTON) {
                    watchGameP->coffee_break_flow = 3;
                }
                break;

            case 0x3:
                if (watchGameP->coffee_break_timer == 0) {
                    keepRunning = false;
                } else {
                    watchGameP->coffee_break_timer = MAX(0, watchGameP->coffee_break_timer - 4);
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

    dm_draw_KaSaMaRu(&gGfxHead, &mtx, &vtx, msgWnd_isSpeaking(&watchGameP->msgWnd), 0xC8, 0x80, 1, 0xFF);
    msgWnd_draw(&watchGameP->msgWnd, &gGfxHead);
    if (watchGameP->coffee_break_flow == 2) {
        push_any_key_draw(128, 192);
    }

    FillRectRGBA(&gGfxHead, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, 0, 255 - watchGameP->coffee_break_timer);

    watchGameP->blink_count++;

    gDPFullSync(gGfxHead++);
    gSPEndDisplayList(gGfxHead++);

    osWritebackDCacheAll();
    gfxTaskStart(&B_800FAE80[gfx_gtask_no], gGfxGlist[gfx_gtask_no], (gGfxHead - gGfxGlist[gfx_gtask_no]) * sizeof(Gfx),
                 0, OS_SC_SWAPBUFFER);
}

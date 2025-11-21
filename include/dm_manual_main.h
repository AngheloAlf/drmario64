#ifndef DM_MANUAL_MAIN_H
#define DM_MANUAL_MAIN_H

#include "libultra.h"

#include "libc/stdbool.h"

#include "main.h"

struct struct_game_state_data;
struct GameMapCell;
struct NNSched;
struct struct_watchManual;

typedef enum DmManualMainCntRet {
    /*  -2 */ dm_ret_game_end = -2, /* Original name: dm_ret_game_end */
    /*  -1 */ dm_ret_game_over, /* Original name: dm_ret_game_over */
    /*   0 */ dm_ret_null, /* Original name: dm_ret_null */
    /*   1 */ dm_ret_next_stage, /* Original name: dm_ret_next_stage */
    /*   2 */ dm_ret_retry, /* Original name: dm_ret_retry */
    /*   3 */ dm_ret_virus_wait, /* Original name: dm_ret_virus_wait */
    /*   4 */ dm_ret_pause, /* Original name: dm_ret_pause */
    /*   5 */ dm_ret_black_up, /* Original name: dm_ret_black_up */
    /*   6 */ dm_ret_clear, /* Original name: dm_ret_clear */
    /*   7 */ dm_ret_tr_a, /* Original name: dm_ret_tr_a */
    /*   8 */ dm_ret_tr_b, /* Original name: dm_ret_tr_b */
    /*   9 */ dm_ret_replay, /* Original name: dm_ret_replay */
    /* 100 */ dm_ret_end = 100, /* Original name: dm_ret_end */
} DmManualMainCntRet;


void dm_manual_attack_capsel_down(void);
void dm_manual_effect_cnt(struct struct_game_state_data *state, struct GameMapCell *mapCells, s32 arg2);
void dm_manual_update_virus_anime(struct struct_game_state_data *state);
DmManualMainCntRet dm_manual_main_cnt(struct struct_game_state_data *state, struct GameMapCell *mapCells, u8 player_no,
                                      s32 arg3);
void dm_manual_make_key(struct struct_game_state_data *state, struct GameMapCell *mapCells);
bool dm_manual_1_main(void);
bool dm_manual_2_main(void);
bool dm_manual_3_main(void);
bool dm_manual_4_main(void);
void draw_AB_guide(s32 x_pos, s32 y_pos);
// void func_80074B08();

void disp_cont(void);
void dm_manual_draw_fg(Mtx **mtxP, Vtx **vtxP);
void dm_manual_all_init(void);
enum_main_no dm_manual_main(struct NNSched *sc);
void dm_manual_graphic(void);

// COMMON

extern struct struct_watchManual *watchManual;

#endif

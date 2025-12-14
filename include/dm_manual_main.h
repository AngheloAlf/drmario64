#ifndef DM_MANUAL_MAIN_H
#define DM_MANUAL_MAIN_H

#include "libultra.h"

#include "libc/stdbool.h"

#include "dm_main_cnt.h"
#include "main.h"

struct struct_game_state_data;
struct GameMapCell;
struct NNSched;
struct struct_watchManual;


void dm_manual_attack_capsel_down(void);
void dm_manual_effect_cnt(struct struct_game_state_data *state, struct GameMapCell *mapCells, s32 arg2);
void dm_manual_update_virus_anime(struct struct_game_state_data *state);
DmMainCnt dm_manual_main_cnt(struct struct_game_state_data *state, struct GameMapCell *mapCells, u8 player_no,
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

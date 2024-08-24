#ifndef DM_MANUAL_MAIN_H
#define DM_MANUAL_MAIN_H

#include "libultra.h"

#include "libc/stdbool.h"

#include "main.h"
#include "msgwnd.h"

struct struct_game_state_data;
struct GameMapCell;
struct NNSched;
struct struct_watchManual;

typedef struct struct_800F4890_unk_034 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ f32 unk_08; // alpha, 0.0f ~ 1.0f
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ MessageWnd messageWnd;
} struct_800F4890_unk_034; // size = 0x90

typedef struct struct_800F4890_unk_0E8 {
    /* 0x0 */ s8 unk_0;
    /* 0x0 */ s8 unk_1;
    /* 0x0 */ s8 unk_2;
    /* 0x0 */ s8 unk_3[3];
} struct_800F4890_unk_0E8; // size = 0x6


void func_80071EF0(struct struct_800F4890_unk_034 *arg0, s32 arg1, s32 arg2);
void func_80071F0C();
void func_80071F14(struct struct_800F4890_unk_034 *arg0, void **heapP);
void func_80071FA0(struct struct_800F4890_unk_034 *arg0);
void tutolWnd_draw(struct struct_800F4890_unk_034 *arg0, Gfx **gfxP);
void func_800721A0(struct struct_800F4890_unk_034 *arg0);
void func_800721BC(struct struct_800F4890_unk_034 *arg0, const char *arg1);
void func_800721D8(struct struct_800F4890_unk_034 *arg0);
void func_80072204(struct struct_800F4890_unk_034 *arg0);
bool func_80072230(struct struct_800F4890_unk_034 *arg0);
bool func_8007224C(struct struct_800F4890_unk_034 *arg0);
void func_80072268(struct struct_800F4890_unk_0E8 *arg0, s32 arg1, s32 arg2);
void dm_manual_attack_capsel_down(void);
void func_800723EC(struct struct_game_state_data *gameStateDataP, struct GameMapCell *mapCells, s32 arg2);
void dm_manual_update_virus_anime(struct struct_game_state_data *arg0);
s32 dm_manual_main_cnt(struct struct_game_state_data *gameStateData, struct GameMapCell *mapCells, u8 arg2, s32 arg3);
void dm_manual_make_key(struct struct_game_state_data *gameStateData, struct GameMapCell *mapCells);
bool dm_manual_1_main(void);
bool dm_manual_2_main(void);
bool dm_manual_3_main(void);
bool dm_manual_4_main(void);
void draw_AB_guide(s32 arg0, s32 arg1);
// void func_80074B08();
void func_80074EF0(struct struct_game_state_data *gameStateData, struct struct_800F4890_unk_0E8 *arg1, s32 arg2);
void disp_cont(void);
void dm_manual_draw_fg(Mtx **mtxP, Vtx **vtxP);
void dm_manual_all_init(void);
enum_main_no dm_manual_main(struct NNSched *sc);
void dm_manual_graphic(void);

// COMMON

extern struct struct_watchManual *watchManual;

#endif

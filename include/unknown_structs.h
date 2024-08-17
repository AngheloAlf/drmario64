#ifndef UNKNOWN_STRUCTS_H
#define UNKNOWN_STRUCTS_H

#include "version.h"
#include "libultra.h"
#include "libc/stdint.h"
#include "libc/stdbool.h"
#include "gcc/stdlib.h"
#include "other_types.h"
#include "color.h"
#include "unk.h"
#include "alignment.h"
#include "msgwnd.h"
#include "recwritingmsg.h"
#include "char_anime.h"
#include "gamemap.h"
#include "main.h"
#include "dm_game_main.h"



typedef struct struct_evs_cfg_4p {
    /* 0x00 */ u8 unk_00[5][4];
    /* 0x14 */ u8 unk_14;
    /* 0x15 */ u8 unk_15;
} struct_evs_cfg_4p; // size = 0x16

// GameStateBackup?
typedef struct struct_gameBackup {
    /* 0x0000 */ struct_watchGame unk_0000;
    /* 0x0B60 */ struct_game_state_data unk_0B60[4];
    /* 0x1A70 */ GameMapCell unk_1A70[4][GAME_MAP_ROWS * GAME_MAP_COLUMNS];
    /* 0x2FB0 */ s32 highScore;
    /* 0x2FB4 */ s32 gameTime;
} struct_gameBackup; // size = 0x2FB8

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

typedef struct struct_800F4890_unk_0C4 {
    /* 0x0 */ s32 unk_0;
    /* 0x4 */ s32 unk_4;
    /* 0x4 */ s32 unk_8;
} struct_800F4890_unk_0C4; // size = 0xC

typedef struct struct_800F4890_unk_14C {
    /* 0x0 */ s32 unk_0;
    /* 0x4 */ s32 unk_4;
} struct_800F4890_unk_14C; // size = 0x8

#define STRUCT_WATCHGAME_MANUAL_UNK_LEN 3
#define STRUCT_WATCHGAME_MANUAL_UNK_LEN2 4

typedef struct struct_watchManual {
    /* 0x000 */ s32 unk_000;
    /* 0x004 */ s32 unk_004;
    /* 0x008 */ s32 unk_008;
    /* 0x00C */ s32 unk_00C;
    /* 0x010 */ s32 unk_010;
    /* 0x014 */ s32 unk_014;
    /* 0x018 */ s32 unk_018;
    /* 0x01C */ s32 unk_01C[STRUCT_WATCHGAME_MANUAL_UNK_LEN2];
    /* 0x02C */ s32 unk_02C;
    /* 0x030 */ s32 unk_030;
    /* 0x034 */ struct_800F4890_unk_034 unk_034;
    /* 0x0C4 */ struct_800F4890_unk_0C4 unk_0C4[STRUCT_WATCHGAME_MANUAL_UNK_LEN];
    /* 0x0E8 */ struct_800F4890_unk_0E8 unk_0E8[4][4];
    /* 0x148 */ u8 unk_148[3];
    /* 0x14C */ struct_800F4890_unk_14C unk_14C[STRUCT_WATCHGAME_MANUAL_UNK_LEN];
    /* 0x164 */ u32 unk_164; // enum?
    /* 0x168 */ u32 unk_168;
    /* 0x16C */ s32 unk_16C;
    /* 0x170 */ s32 unk_170;
    /* 0x174 */ s32 unk_174[4];
    /* 0x184 */ s32 unk_184;
} struct_watchManual; // size = 0x188

typedef enum enum_evs_gamesel {
    /* 0 */ ENUM_EVS_GAMESEL_0,
    /* 1 */ ENUM_EVS_GAMESEL_1,
    /* 2 */ ENUM_EVS_GAMESEL_2,
    /* 3 */ ENUM_EVS_GAMESEL_3,
    /* 4 */ ENUM_EVS_GAMESEL_4,
    /* 5 */ ENUM_EVS_GAMESEL_5,
    /* 6 */ ENUM_EVS_GAMESEL_6,
    /* 7 */ ENUM_EVS_GAMESEL_MAX
} enum_evs_gamesel;

typedef enum enum_800E5930 {
    /* 0 */ ENUM_800E5930_0,
    /* 1 */ ENUM_800E5930_1,
    /* 2 */ ENUM_800E5930_2,
    /* 3 */ ENUM_800E5930_MAX
} enum_800E5930;

#endif

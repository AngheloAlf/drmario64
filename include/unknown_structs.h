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

typedef enum enum_800E5930 {
    /* 0 */ ENUM_800E5930_0,
    /* 1 */ ENUM_800E5930_1,
    /* 2 */ ENUM_800E5930_2,
    /* 3 */ ENUM_800E5930_MAX
} enum_800E5930;

#endif

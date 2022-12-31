#ifndef GAMEMAP_H
#define GAMEMAP_H

#include "ultra64.h"
#include "libc/stdint.h"
#include "libc/stdbool.h"

typedef struct GameMapCell {
    /* 0x0 */ s8 unk_0; // column?
    /* 0x1 */ s8 unk_1; // row?
    /* 0x2 */ s8 unk_2;
    /* 0x3 */ u8 unk_3;
    /* 0x4 */ s8 unk_4; // map_info?
    /* 0x5 */ s8 unk_5;
    /* 0x6 */ s8 unk_6;
    /* 0x7 */ s8 unk_7; // virus color?
    /* 0x8 */ s8 unk_8;
    /* 0x9 */ s8 unk_9;
} GameMapCell; // size = 0xA

#define GAME_MAP_ROWS 17
#define GAME_MAP_COLUMNS 8

#define GAME_MAP_GET_INDEX(row, column) ((row) * GAME_MAP_COLUMNS + (column))
#define GAME_MAP_GET_INDEX_ALT(row, column) ((column) + (row) * GAME_MAP_COLUMNS)

typedef struct GameMapGrid {
    /* 0x000 */ GameMapCell cells[GAME_MAP_ROWS * GAME_MAP_COLUMNS];
} GameMapGrid; // size = 0x550

extern GameMapGrid game_map_data[4];

#endif

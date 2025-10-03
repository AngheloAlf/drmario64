#ifndef GAMEMAP_H
#define GAMEMAP_H

#include "libultra.h"

typedef struct GameMapCell {
    /* 0x0 */ s8 pos_m_x; // column?
    /* 0x1 */ s8 pos_m_y; // row?
    /* 0x2 */ s8 capsel_m_g;
    /* 0x3 */ s8 capsel_m_p;
    /* 0x4 */ s8 capsel_m_flg[6]; // map_info?
} GameMapCell; // size = 0xA

/**
 * unk_4[0] // map_info?
 * unk_4[1]
 * unk_4[2]
 * unk_4[3] // virus color? top color?
 * unk_4[4]
 * unk_4[5]
 */


#define GAME_MAP_ROWS 17
#define GAME_MAP_COLUMNS 8

#define GAME_MAP_GET_INDEX(row, column) ((row) * GAME_MAP_COLUMNS + (column))
#define GAME_MAP_GET_INDEX_ALT(row, column) ((column) + (row) * GAME_MAP_COLUMNS)

#if GAME_MAP_COLUMNS == 8
#define GAME_MAP_GET_INDEX_ALT2(row, column) (((row) << 3) + (column))
#else
#define GAME_MAP_GET_INDEX_ALT2(row, column) GAME_MAP_GET_INDEX(row, column)
#endif

extern GameMapCell game_map_data[4][GAME_MAP_ROWS * GAME_MAP_COLUMNS];

#endif

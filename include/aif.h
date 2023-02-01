#ifndef AIF_H
#define AIF_H

#include "libultra.h"
#include "gamemap.h"

/**
 * Artificial intelligence field?
 */

typedef struct Unk_AIFEntry {
    /* 0x0 */ u8 unk_0;
    /* 0x1 */ u8 unk_1;
} Unk_AIFEntry; // size = 0x2

extern Unk_AIFEntry aiRecurData[GAME_MAP_ROWS+1][GAME_MAP_COLUMNS+2];
extern Unk_AIFEntry aiFieldData[GAME_MAP_ROWS][GAME_MAP_COLUMNS];


#endif
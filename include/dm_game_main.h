#ifndef DM_GAME_MAIN_H
#define DM_GAME_MAIN_H

#include "libultra.h"

typedef struct struct_gameGeom {
    /* 0x0000 */ Mtx mtxBuf[3][0x20];
    /* 0x1800 */ Vtx vtxBuf[3][0x80];
} struct_gameGeom; // size = 0x3000

extern struct_gameGeom *gameGeom;

#endif

#ifndef ROM_OFFSETS_H
#define ROM_OFFSETS_H

#include "libc/stdint.h"


typedef struct RomOffsetPair {
    /* 0x0 */ romoffset_t start;
    /* 0x4 */ romoffset_t end;
} RomOffsetPair; // size = 0x8


extern RomOffsetPair D_8000E740;
extern RomOffsetPair D_8000E748;
extern RomOffsetPair D_8000E750;
extern RomOffsetPair D_8000E758;
extern RomOffsetPair D_8000E760;
extern RomOffsetPair D_8000E768;
extern RomOffsetPair D_8000E770;
extern RomOffsetPair D_8000E778[];
extern RomOffsetPair D_8000E838[];
extern RomOffsetPair D_8000EA48;

#endif

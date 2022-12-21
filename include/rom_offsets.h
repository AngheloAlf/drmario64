#ifndef ROM_OFFSETS_H
#define ROM_OFFSETS_H

#include "libc/stdint.h"


typedef struct RomOffsetPair {
    /* 0x0 */ romoffset_t start;
    /* 0x4 */ romoffset_t end;
} RomOffsetPair; // size = 0x8


extern RomOffsetPair storyRomData[];
extern RomOffsetPair bgRomData[];
extern RomOffsetPair _romDataTbl[];

#endif

#ifndef WAKU_GRAPHICS_H
#define WAKU_GRAPHICS_H

#include "PR/ultratypes.h"

typedef struct GraphBinHeader {
    /* 0x000 */ char magic[0x8];
    /* 0x008 */ u16 width;
    /* 0x00A */ u16 height;
    /* 0x00C */ u16 unk_00C;
    /* 0x00E */ u8 unk_00E;
    /* 0x010 */ u16 tlut[0x100];
} GraphBinHeader; // size = 0x210

typedef struct GraphBin_320_160 {
    /* 0x000 */ GraphBinHeader header;
    /* 0x210 */ u8 texture[320 * 160];
} GraphBin_320_160; // size = 0xCA10

#endif

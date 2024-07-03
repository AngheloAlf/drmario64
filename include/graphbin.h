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

#define DECLARE_GRAPHBIN_u4(width, height) \
    typedef struct GraphBin_u4_ ## width ## _ ## height { \
        /* 0x000 */ GraphBinHeader header; \
        /* 0x210 */ u8 texture[width * height / 2]; \
    } GraphBin_u4_ ## width ## _ ## height

#define DECLARE_GRAPHBIN_u8(width, height) \
    typedef struct GraphBin_u8_ ## width ## _ ## height { \
        /* 0x000 */ GraphBinHeader header; \
        /* 0x210 */ u8 texture[width * height]; \
    } GraphBin_u8_ ## width ## _ ## height

#define DECLARE_GRAPHBIN_u16(width, height) \
    typedef struct GraphBin_u16_ ## width ## _ ## height { \
        /* 0x000 */ GraphBinHeader header; \
        /* 0x210 */ u16 texture[width * height]; \
    } GraphBin_u16_ ## width ## _ ## height

DECLARE_GRAPHBIN_u4(144, 16);
DECLARE_GRAPHBIN_u4(192, 42);
DECLARE_GRAPHBIN_u4(320, 20);

DECLARE_GRAPHBIN_u8(320, 80);
DECLARE_GRAPHBIN_u8(320, 160);
DECLARE_GRAPHBIN_u8(328, 240);

DECLARE_GRAPHBIN_u16(144, 16);
DECLARE_GRAPHBIN_u16(320, 20);

#endif

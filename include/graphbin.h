#ifndef GRAPHBIN_H
#define GRAPHBIN_H

#include "PR/ultratypes.h"

typedef struct GraphBinHeader {
    /* 0x000 */ char magic[0x8];
    /* 0x008 */ u16 width;
    /* 0x00A */ u16 height;
    /* 0x00C */ u16 unk_00C; // unused?
    /* 0x00E */ u8 siz;
    /* 0x010 */ u16 tlut[0x100];
} GraphBinHeader; // size = 0x210

typedef struct GraphBinGeneric {
    /* 0x000 */ GraphBinHeader header;
    /* 0x210 */ u8 texture[1]; // Placeholder. Allows to reference the texture member
} GraphBinGeneric;

#define DECLARE_STRUCT_GRAPHBIN_u4(width, height) \
    typedef struct GraphBin_u4_ ## width ## _ ## height { \
        /* 0x000 */ GraphBinHeader header; \
        /* 0x210 */ u8 texture[width * height / 2]; \
    } GraphBin_u4_ ## width ## _ ## height

#define DECLARE_STRUCT_GRAPHBIN_u8(width, height) \
    typedef struct GraphBin_u8_ ## width ## _ ## height { \
        /* 0x000 */ GraphBinHeader header; \
        /* 0x210 */ u8 texture[width * height]; \
    } GraphBin_u8_ ## width ## _ ## height

#define DECLARE_STRUCT_GRAPHBIN_u16(width, height) \
    typedef struct GraphBin_u16_ ## width ## _ ## height { \
        /* 0x000 */ GraphBinHeader header; \
        /* 0x210 */ u16 texture[width * height]; \
    } GraphBin_u16_ ## width ## _ ## height


#define DECLARE_VARIABLE_GRAPHBIN_u4(name, width, height) \
    extern GraphBin_u4_ ## width ## _ ## height name

#define DECLARE_VARIABLE_GRAPHBIN_u8(name, width, height) \
    extern GraphBin_u8_ ## width ## _ ## height name

#define DECLARE_VARIABLE_GRAPHBIN_u16(name, width, height) \
    extern GraphBin_u16_ ## width ## _ ## height name


#define GRAPHBIN_START_u4(name, width, height) \
    GraphBin_u4_ ## width ## _ ## height name = { \
        { \
            "GraphBin", \
            width, \
            height, \
            1, \
            4, \
            {

#define GRAPHBIN_START_u8(name, width, height) \
    GraphBin_u8_ ## width ## _ ## height name = { \
        { \
            "GraphBin", \
            width, \
            height, \
            1, \
            8, \
            {

#define GRAPHBIN_START_u16(name, width, height) \
    GraphBin_u16_ ## width ## _ ## height name = { \
        { \
            "GraphBin", \
            width, \
            height, \
            1, \
            16, \
            {

#define GRAPHBIN_MIDDLE() \
            }, \
        }, \
        {

#define GRAPHBIN_END() \
        }, \
    }

DECLARE_STRUCT_GRAPHBIN_u4(32, 32);
DECLARE_STRUCT_GRAPHBIN_u4(48, 15);
DECLARE_STRUCT_GRAPHBIN_u4(64, 19);
DECLARE_STRUCT_GRAPHBIN_u4(64, 34);
DECLARE_STRUCT_GRAPHBIN_u4(64, 50);
DECLARE_STRUCT_GRAPHBIN_u4(144, 16);
DECLARE_STRUCT_GRAPHBIN_u4(192, 42);
DECLARE_STRUCT_GRAPHBIN_u4(320, 20);

DECLARE_STRUCT_GRAPHBIN_u8(320, 80);
DECLARE_STRUCT_GRAPHBIN_u8(320, 160);
DECLARE_STRUCT_GRAPHBIN_u8(328, 240);

DECLARE_STRUCT_GRAPHBIN_u16(64, 34);
DECLARE_STRUCT_GRAPHBIN_u16(64, 50);
DECLARE_STRUCT_GRAPHBIN_u16(144, 16);
DECLARE_STRUCT_GRAPHBIN_u16(320, 20);

#endif

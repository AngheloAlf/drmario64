#ifndef COLOR_H
#define COLOR_H

#include "libultra.h"

typedef struct Color_RGB8 {
    /* 0x0 */ u8 r;
    /* 0x1 */ u8 g;
    /* 0x2 */ u8 b;
} Color_RGB8; // size = 0x3

typedef struct Color_RGBA8 {
    /* 0x0 */ u8 r;
    /* 0x1 */ u8 g;
    /* 0x2 */ u8 b;
    /* 0x3 */ u8 a;
} Color_RGBA8; // size = 0x4

typedef struct Color_RGB32 {
    /* 0x00 */ s32 r;
    /* 0x04 */ s32 g;
    /* 0x08 */ s32 b;
} Color_RGB32; // size = 0xC

typedef struct Color_RGBA32 {
    /* 0x00 */ s32 r;
    /* 0x04 */ s32 g;
    /* 0x08 */ s32 b;
    /* 0x0C */ s32 a;
} Color_RGBA32; // size = 0x10

typedef union Color_RGBAf32 {
    struct {
    /* 0x00 */ f32 r;
    /* 0x04 */ f32 g;
    /* 0x08 */ f32 b;
    /* 0x0C */ f32 a;
    } v;
    f32 arr[4];
} Color_RGBAf32; // size = 0x10

#endif

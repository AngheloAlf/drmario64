#ifndef COLOR_H
#define COLOR_H

#include "ultra64.h"

typedef struct Color_RGB8 {
    /* 0x0 */ u8 r;
    /* 0x1 */ u8 g;
    /* 0x2 */ u8 b;
} Color_RGB8; // size = 0x3


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


#define GET_COLOR_RGBA32_FROM_COLOR_RGBAF32(dst, src) \
    do { \
        Color_RGBA32 __temp; \
        __temp.r = CLAMP((src)->v.r, 0.0f, 1.0f) * 255; \
        __temp.g = CLAMP((src)->v.g, 0.0f, 1.0f) * 255; \
        __temp.b = CLAMP((src)->v.b, 0.0f, 1.0f) * 255; \
        __temp.a = CLAMP((src)->v.a, 0.0f, 1.0f) * 255; \
        *(dst) = __temp; \
    } while (0)

#endif

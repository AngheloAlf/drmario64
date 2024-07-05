#ifndef LWS_H
#define LWS_H

#include "libultra.h"
#include "unk.h"

typedef struct Lws_unk_10 {
    /* 0x00 */ Gfx *unk_00;
    /* 0x08 */ s32 unk_04;
    /* 0x04 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ u32 unk_10; // unused
    /* 0x14 */ u32 unk_14; // unused
} Lws_unk_10; // size = 0x18

typedef struct Lws_unk_14 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04; // unused
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ s16 unk_0E;
    /* 0x10 */ s16 unk_10;
    /* 0x12 */ s16 unk_12;
    /* 0x14 */ s16 unk_14;
    /* 0x16 */ s16 unk_16;
    /* 0x18 */ s16 unk_18;
} Lws_unk_14; // size = 0x1C

typedef struct Lws {
    /* 0x00 */ u32 unk_00; // unused
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ u32 unk_08; // unused
    /* 0x0C */ s32 count;
    /* 0x10 */ Lws_unk_10 *unk_10;
    /* 0x14 */ Lws_unk_14 *unk_14;
} Lws; // size >= 0x18

s32 lws_anim(Gfx **gfxP, Mtx *mtx, Lws *arg2, UNK_TYPE arg3, UNK_PTR arg4);

#endif

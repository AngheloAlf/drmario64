#ifndef LWS_H
#define LWS_H

#include "libultra.h"
#include "unk.h"

typedef struct struct_lws_scene_unk_10 {
    /* 0x0 */ Gfx *unk_00;
    /* 0x0 */ UNK_TYPE unk_04;
    /* 0x0 */ UNK_TYPE unk_08;
    /* 0x0 */ UNK_TYPE unk_0C;
    /* 0x10 */ UNK_TYPE1 unk_10[0x8];
} struct_lws_scene_unk_10; // size >= 0x18

typedef struct struct_lws_scene_unk_14 {
    /* 0x00 */ UNK_TYPE unk_00;
    /* 0x04 */ UNK_TYPE1 unk_04[0x4];
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ s16 unk_0E;
    /* 0x10 */ s16 unk_10;
    /* 0x12 */ s16 unk_12;
    /* 0x14 */ s16 unk_14;
    /* 0x16 */ s16 unk_16;
    /* 0x18 */ s16 unk_18;
    /* 0x1A */ UNK_TYPE1 unk_1A[0x2];
} struct_lws_scene_unk_14; // size >= 0x1C

typedef struct struct_lws_scene {
    /* 0x00 */ UNK_TYPE1 unk_00[0x4];
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ UNK_TYPE1 unk_08[0x4];
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ struct_lws_scene_unk_10 *unk_10;
    /* 0x14 */ struct_lws_scene_unk_14 *unk_14;
} struct_lws_scene; // size >= 0x18

UNK_TYPE lws_anim(Gfx **gfxP, Mtx *mtx, struct_lws_scene *arg2, UNK_TYPE arg3, UNK_PTR arg4);

#endif

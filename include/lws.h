#ifndef LWS_H
#define LWS_H

#include "libultra.h"

typedef struct LwsObj {
    /* 0x00 */ Gfx *dl;
    /* 0x08 */ s32 parent;
    /* 0x04 */ s32 key_count;
    /* 0x0C */ s32 key_index;
    /* 0x10 */ s16 px; // unused
    /* 0x12 */ s16 py; // unused
    /* 0x14 */ s16 pz; // unused
} LwsObj; // size = 0x18

typedef struct LwsKey {
    /* 0x00 */ s32 key_no;
    /* 0x04 */ s32 next; // unused
    /* 0x08 */ s16 lx;
    /* 0x0A */ s16 ly;
    /* 0x0C */ s16 lz;
    /* 0x0E */ s16 rx;
    /* 0x10 */ s16 ry;
    /* 0x12 */ s16 rz;
    /* 0x14 */ s16 sx;
    /* 0x16 */ s16 sy;
    /* 0x18 */ s16 sz;
} LwsKey; // size = 0x1C

typedef struct Lws {
    /* 0x00 */ s32 first_frame; // unused
    /* 0x04 */ s32 last_frame;
    /* 0x08 */ s32 frame_rate; // unused
    /* 0x0C */ s32 obj_count;
    /* 0x10 */ LwsObj *obj;
    /* 0x14 */ LwsKey *key;
} Lws; // size = 0x18

s32 lws_anim(Gfx **gfxP, Mtx *mtx, Lws *pSceneData, s32 frame, void *baseAddr);

#endif

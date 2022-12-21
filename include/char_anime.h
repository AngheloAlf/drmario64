#ifndef CHAR_ANIME_H
#define CHAR_ANIME_H

#include "ultra64.h"
#include "libc/stdint.h"
#include "libc/stdbool.h"
#include "unk.h"

typedef struct struct_800B1B00 {
    /* 0x0 */ UNK_TYPE4 unk_0;
    /* 0x4 */ UNK_TYPE4 unk_4;
} struct_800B1B00; // size = 0x8

// this struct may not exist
typedef struct struct_800F3E50_unk_44C_unk_0C {
    /* 0x0 */ u8 *unk_0;
} struct_800F3E50_unk_44C_unk_0C; // size >= 0x4

typedef struct struct_800F3E50_unk_44C_unk_1C_unk_4 {
    /* 0x0 */ u16 unk_0;
    /* 0x2 */ u16 unk_2;
} struct_800F3E50_unk_44C_unk_1C_unk_4; // size >= 0x4

typedef struct struct_800F3E50_unk_44C_unk_1C_unk_0 {
    /* 0x0 */ UNK_TYPE1 unk_0[0x4];
    /* 0x4 */ UNK_TYPE4 unk_4;
} struct_800F3E50_unk_44C_unk_1C_unk_0; // size >= 0x8

typedef struct struct_800F3E50_unk_44C_unk_1C {
    /* 0x0 */ struct_800F3E50_unk_44C_unk_1C_unk_0 *unk_0;
    /* 0x4 */ struct_800F3E50_unk_44C_unk_1C_unk_4 *unk_4;
} struct_800F3E50_unk_44C_unk_1C; // size = 0x8

// animeState?
typedef struct struct_800F3E50_unk_44C {
    /* 0x00 */ u8 unk_00[0x4];
    /* 0x04 */ u8 unk_04[0x4];
    /* 0x08 */ UNK_TYPE4 unk_08;
    /* 0x0C */ struct_800F3E50_unk_44C_unk_0C *unk_0C;
    /* 0x10 */ UNK_TYPE4 unk_10;
    /* 0x14 */ UNK_TYPE4 unk_14;
    /* 0x18 */ UNK_TYPE4 unk_18;
    /* 0x14 */ struct_800F3E50_unk_44C_unk_1C *unk_1C;
    /* 0x20 */ UNK_TYPE4 unk_20;
    /* 0x24 */ struct_800B1B00 unk_24;
    /* 0x24 */ UNK_TYPE4 unk_2C;
    /* 0x24 */ UNK_TYPE4 unk_30;
    /* 0x24 */ UNK_TYPE4 unk_34;
    /* 0x24 */ UNK_TYPE4 unk_38;
    /* 0x24 */ UNK_TYPE4 unk_3C;
} struct_800F3E50_unk_44C; // size = 0x40

typedef struct struct_800F3E50_unk_50C_unk_100 {
    /* 0x0 */ s32 unk_0;
    /* 0x4 */ s32 unk_4;
} struct_800F3E50_unk_50C_unk_100; // size = 0x8

typedef struct struct_800F3E50_unk_50C {
    /* 0x000 */ struct_800F3E50_unk_44C unk_000[4];
    /* 0x100 */ struct_800F3E50_unk_50C_unk_100 unk_100[4];
    /* 0x120 */ UNK_TYPE4 unk_120;
} struct_800F3E50_unk_50C; // size = 0x124

void animeSeq_init(struct_800F3E50_unk_44C *arg0, struct_800F3E50_unk_44C_unk_0C *arg1, UNK_TYPE4 arg2);
void func_8005E154(struct_800F3E50_unk_44C *arg0, UNK_TYPE4 arg1);
void animeSeq_update(struct_800F3E50_unk_44C *arg0, UNK_TYPE arg1);
bool animeSeq_isEnd(struct_800F3E50_unk_44C *arg0);
size_t animeState_getDataSize(s32 arg0);
void animeState_load(struct_800F3E50_unk_44C *arg0, UNK_PTR *arg1, UNK_TYPE arg2);
void animeState_init(struct_800F3E50_unk_44C *arg0, struct_800F3E50_unk_44C_unk_0C *arg1, struct_800F3E50_unk_44C_unk_1C *arg2, UNK_TYPE4 arg3, UNK_TYPE4 arg4, UNK_TYPE4 arg5);
void animeState_set(struct_800F3E50_unk_44C *arg0, UNK_TYPE4 arg1);
void animeState_update(struct_800F3E50_unk_44C *arg0);
bool func_8005E4E0(struct_800F3E50_unk_44C *arg0);
void animeState_initDL(struct_800F3E50_unk_44C *arg0, Gfx **gfxP);
void animeState_initDL2(struct_800F3E50_unk_44C *arg0, Gfx **gfxP);
void animeState_initIntensityDL(struct_800F3E50_unk_44C *arg0, Gfx **gfxP);
// void animeState_draw();
void func_8005E998(struct_800F3E50_unk_44C *arg0, Gfx **gfxP, f32 arg2, f32 arg3, f32 arg4, f32 arg5);
void animeSmog_init(struct_800F3E50_unk_50C *arg0, struct_800F3E50_unk_50C *arg1);
void animeSmog_load(struct_800F3E50_unk_50C *arg0, UNK_PTR *arg1);
// void animeSmog_start();
void animeSmog_stop(struct_800F3E50_unk_50C *arg0);
void animeSmog_update(struct_800F3E50_unk_50C *arg0);
// void animeSmog_draw();
// void func_8005EE64();
void loadAnimeSeq(UNK_PTR *arg0, struct_800F3E50_unk_44C_unk_1C **arg1, struct_800F3E50_unk_44C_unk_0C **arg2, romoffset_t romOffsetStart, romoffset_t romOffsetEnd);

#endif

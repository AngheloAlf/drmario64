#ifndef CHAR_ANIME_H
#define CHAR_ANIME_H

#include "ultra64.h"
#include "libc/stdint.h"
#include "libc/stdbool.h"
#include "unk.h"


typedef enum CharAnimeMode {
    /*  0 */ CHARANIMEMODE_M,
    /*  1 */ CHARANIMEMODE_N,
    /*  2 */ CHARANIMEMODE_H,
    /*  3 */ CHARANIMEMODE_I,
    /*  4 */ CHARANIMEMODE_J,
    /*  5 */ CHARANIMEMODE_D,
    /*  6 */ CHARANIMEMODE_E,
    /*  7 */ CHARANIMEMODE_F,
    /*  8 */ CHARANIMEMODE_A,
    /*  9 */ CHARANIMEMODE_B,
    /* 10 */ CHARANIMEMODE_C,
    /* 11 */ CHARANIMEMODE_G,
    /* 12 */ CHARANIMEMODE_K,
    /* 13 */ CHARANIMEMODE_L,
    /* 14 */ CHARANIMEMODE_O,
    /* 15 */ CHARANIMEMODE_MARIO,
    /* 16 */ CHARANIMEMODE_VIRUS_R,
    /* 17 */ CHARANIMEMODE_VIRUS_Y,
    /* 18 */ CHARANIMEMODE_VIRUS_B,
    /* 19 */ CHARANIMEMODE_SMOG,
    /* 20 */ CHARANIMEMODE_MAX
} CharAnimeMode;

typedef struct struct_800B1B00 {
    /* 0x0 */ UNK_TYPE4 unk_0;
    /* 0x4 */ UNK_TYPE4 unk_4;
} struct_800B1B00; // size = 0x8

// this struct may not exist
typedef struct AnimeSeq_unk_0C {
    /* 0x0 */ u8 *unk_0;
} AnimeSeq_unk_0C; // size >= 0x4

typedef struct AnimeState_unk_1C_unk_4 {
    /* 0x0 */ u16 unk_0;
    /* 0x2 */ u16 unk_2;
} AnimeState_unk_1C_unk_4; // size >= 0x4

typedef struct AnimeState_unk_1C_unk_0 {
    /* 0x0 */ UNK_TYPE1 unk_0[0x4];
    /* 0x4 */ UNK_TYPE4 unk_4;
} AnimeState_unk_1C_unk_0; // size >= 0x8

typedef struct AnimeState_unk_1C {
    /* 0x0 */ AnimeState_unk_1C_unk_0 *unk_0;
    /* 0x4 */ AnimeState_unk_1C_unk_4 *unk_4;
} AnimeState_unk_1C; // size = 0x8

typedef struct AnimeSeq {
    /* 0x00 */ u8 unk_00[0x4];
    /* 0x04 */ u8 unk_04[0x4];
    /* 0x08 */ UNK_TYPE4 unk_08;
    /* 0x0C */ AnimeSeq_unk_0C *unk_0C;
    /* 0x10 */ UNK_TYPE4 unk_10;
    /* 0x14 */ UNK_TYPE4 unk_14;
    /* 0x18 */ UNK_TYPE4 unk_18;
} AnimeSeq; // size = 0x1C

typedef struct AnimeState {
    /* 0x00 */ AnimeSeq animeSeq;
    /* 0x1C */ AnimeState_unk_1C *unk_1C;
    /* 0x20 */ UNK_TYPE4 unk_20;
    /* 0x24 */ struct_800B1B00 unk_24;
    /* 0x2C */ CharAnimeMode animeMode;
    /* 0x30 */ s32 primColorR;
    /* 0x34 */ s32 primColorG;
    /* 0x38 */ s32 primColorB;
    /* 0x3C */ s32 primColorA;
} AnimeState; // size = 0x40

typedef struct AnimeSmog_unk_100 {
    /* 0x0 */ s32 unk_0;
    /* 0x4 */ s32 unk_4;
} AnimeSmog_unk_100; // size = 0x8

typedef struct AnimeSmog {
    /* 0x000 */ AnimeState unk_000[4];
    /* 0x100 */ AnimeSmog_unk_100 unk_100[4];
    /* 0x120 */ UNK_TYPE4 unk_120;
} AnimeSmog; // size = 0x124

void animeSeq_init(AnimeSeq *animeSeq, AnimeSeq_unk_0C *arg1, UNK_TYPE4 arg2);
void func_8005E154(AnimeState *animeState, UNK_TYPE4 arg1);
void animeSeq_update(AnimeSeq *animeSeq, UNK_TYPE arg1);
bool animeSeq_isEnd(AnimeSeq *animeSeq);
size_t animeState_getDataSize(CharAnimeMode animeMode);
void animeState_load(AnimeState *animeState, UNK_PTR *arg1, CharAnimeMode animeMode);
void animeState_init(AnimeState *animeState, AnimeSeq_unk_0C *arg1, AnimeState_unk_1C *arg2, UNK_TYPE4 arg3,
                     UNK_TYPE4 arg4, CharAnimeMode animeMode);
void animeState_set(AnimeState *animeState, UNK_TYPE4 arg1);
void animeState_update(AnimeState *animeState);
bool animeState_isEnd(AnimeState *animeState);
void animeState_initDL(AnimeState *animeState, Gfx **gfxP);
void animeState_initDL2(AnimeState *animeState, Gfx **gfxP);
void animeState_initIntensityDL(AnimeState *animeState, Gfx **gfxP);
// void animeState_draw();
void func_8005E998(AnimeState *animeState, Gfx **gfxP, f32 arg2, f32 arg3, f32 arg4, f32 arg5);
void animeSmog_init(AnimeSmog *animeSmog, AnimeSmog *orig);
void animeSmog_load(AnimeSmog *animeSmog, UNK_PTR *arg1);
void animeSmog_start(AnimeSmog *animeSmog);
void animeSmog_stop(AnimeSmog *animeSmog);
void animeSmog_update(AnimeSmog *animeSmog);
void animeSmog_draw(AnimeSmog *animeSmog, Gfx **gfxP, f32 arg2, f32 arg3, f32 arg4, f32 arg5);
// void func_8005EE64();
void loadAnimeSeq(UNK_PTR *arg0, AnimeState_unk_1C **arg1, AnimeSeq_unk_0C **arg2, romoffset_t romOffsetStart, romoffset_t romOffsetEnd);

#endif

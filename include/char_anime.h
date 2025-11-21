#ifndef CHAR_ANIME_H
#define CHAR_ANIME_H

#include "libultra.h"
#include "libc/stdint.h"
#include "libc/stdbool.h"
#include "other_types.h"

struct TiTexData;

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

#define ANIME_METADATA_F0  0xF0
#define ANIME_METADATA_F1  0xF1
#define ANIME_METADATA_F2  0xF2
#define ANIME_METADATA_END 0xFF

#define ANIME_METADATA_CMD_F0(x)  ANIME_METADATA_F0, x
#define ANIME_METADATA_CMD_F1(x)  ANIME_METADATA_F1, x
#define ANIME_METADATA_CMD_F2(x)  ANIME_METADATA_F2, x

typedef struct AnimeHeader {
    /* 0x0 */ struct TiTexData *texData;
    /* 0x4 */ s32 *texDataLen;
    /* 0x8 */ u8 **metadata;
    /* 0xC */ s32 *metadataLen;
} AnimeHeader; // size = 0x10

typedef struct SAnimeStateCenter {
    /* 0x0 */ s32 cx;
    /* 0x4 */ s32 cy;
} SAnimeStateCenter; // size = 0x8

// Likely to be "animation number" or similar
typedef enum AnimeNo {
    /* 0 */ ANIMENO_0,
    /* 1 */ ANIMENO_1,
    /* 2 */ ANIMENO_2,
    /* 3 */ ANIMENO_3,
    /* 4 */ ANIMENO_4,
} AnimeNo;

/* Original name: SAnimeSeq */
typedef struct SAnimeSeq {
    /* 0x00 */ u8 labelStack[4]; /* Original name: labelStack */
    /* 0x04 */ u8 countStack[4]; /* Original name: countStack */
    /* 0x08 */ s32 stackDepth; /* Original name: stackDepth */
    /* 0x0C */ u8 **seqArray; /* Original name: seqArray */ // indexed by animeNo (AnimeNo) and seqCount
    /* 0x10 */ AnimeNo animeNo; /* Original name: animeNo */ // TODO: enum?
    /* 0x14 */ s32 seqCount; /* Original name: seqCount */
    /* 0x18 */ s32 textureNo; /* Original name: textureNo */
} SAnimeSeq; // size = 0x1C

/* Original name: SAnimeState */
typedef struct SAnimeState {
    /* 0x00 */ SAnimeSeq animeSeq; /* Original name: animeSeq */
    /* 0x1C */ struct TiTexData *texArray; /* Original name: texArray */
    /* 0x20 */ u32 frameCount; /* Original name: frameCount */
    /* 0x24 */ SAnimeStateCenter center; /* Original name: center */
    /* 0x2C */ CharAnimeMode animeMode; /* Original name: charNo */
    /* 0x30 */ s32 primColor[4]; /* Original name: color */
} SAnimeState; // size = 0x40

typedef struct SAnimeSmogPos {
    /* 0x0 */ s32 x;
    /* 0x4 */ s32 y;
} SAnimeSmogPos; // size = 0x8

// TODO: use MAXCONTROLLERS?
#define ANIMESMOG_COUNT 4U

/* Original name: SAnimeSmog */
typedef struct SAnimeSmog {
    /* 0x000 */ SAnimeState animeState[ANIMESMOG_COUNT]; /* Original name: animeState */
    /* 0x100 */ SAnimeSmogPos pos[ANIMESMOG_COUNT]; /* Original name: pos */
    /* 0x120 */ s32 frameCount; /* Original name: frameCount */
} SAnimeSmog; // size = 0x124

void animeSeq_init(SAnimeSeq *animeSeq, u8 **seqArray, AnimeNo animeNo);
void animeSeq_set(SAnimeSeq *animeSeq, AnimeNo animeNo);
void animeSeq_update(SAnimeSeq *animeSeq, s32 step);
bool animeSeq_isEnd(const SAnimeSeq *animeSeq);
size_t animeState_getDataSize(CharAnimeMode animeMode);
void animeState_load(SAnimeState *animeState, void **heap, CharAnimeMode animeMode);
void animeState_init(SAnimeState *animeState, u8 **seqArray, struct TiTexData *texArray, s32 cx, s32 cy, CharAnimeMode animeMode);
void animeState_set(SAnimeState *animeState, AnimeNo animeNo);
void animeState_update(SAnimeState *animeState);
bool animeState_isEnd(const SAnimeState *animeState);
void animeState_initDL(SAnimeState *animeState, Gfx **gfxP);
void animeState_initDL2(SAnimeState *animeState, Gfx **gfxP);
void animeState_initIntensityDL(SAnimeState *animeState, Gfx **gfxP);
void animeState_draw(SAnimeState *animeState, Gfx **gfxP, f32 x, f32 y, f32 sx, f32 sy);
void animeState_drawI(SAnimeState *animeState, Gfx **gfxP, f32 x, f32 y, f32 sx, f32 sy);
void animeSmog_init(SAnimeSmog *animeSmog, SAnimeState *state);
void animeSmog_load(SAnimeSmog *animeSmog, void **ptr);
void animeSmog_start(SAnimeSmog *animeSmog);
void animeSmog_stop(SAnimeSmog *animeSmog);
void animeSmog_update(SAnimeSmog *animeSmog);
void animeSmog_draw(SAnimeSmog *animeSmog, Gfx **gfxP, f32 x, f32 y, f32 sx, f32 sy);
// void mappingAnimeSeq();
void loadAnimeSeq(void **heapP, struct TiTexData **texDataDst, u8 ***metadataDst, RomOffset romOffsetStart, RomOffset romOffsetEnd);

#endif

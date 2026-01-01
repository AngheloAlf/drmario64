/**
 * Original filename char_anime.c
 */

#include "char_anime.h"

#include "alignment.h"
#include "libc/assert.h"
#include "libc/stdint.h"
#include "gcc/stdlib.h"
#include "macros_defines.h"

#include "boot_data.h"
#include "segment_symbols.h"
#include "util.h"
#include "tex_func.h"

/**
 * Original name: static _size
 */
const size_t _size_122[] = {
    SEGMENT_ROM_SIZE_CONST(segment_anime_m),       // CHARANIMEMODE_M
    SEGMENT_ROM_SIZE_CONST(segment_anime_n),       // CHARANIMEMODE_N
    SEGMENT_ROM_SIZE_CONST(segment_anime_h),       // CHARANIMEMODE_H
    SEGMENT_ROM_SIZE_CONST(segment_anime_i),       // CHARANIMEMODE_I
    SEGMENT_ROM_SIZE_CONST(segment_anime_j),       // CHARANIMEMODE_J
    SEGMENT_ROM_SIZE_CONST(segment_anime_d),       // CHARANIMEMODE_D
    SEGMENT_ROM_SIZE_CONST(segment_anime_e),       // CHARANIMEMODE_E
    SEGMENT_ROM_SIZE_CONST(segment_anime_f),       // CHARANIMEMODE_F
    SEGMENT_ROM_SIZE_CONST(segment_anime_a),       // CHARANIMEMODE_A
    SEGMENT_ROM_SIZE_CONST(segment_anime_b),       // CHARANIMEMODE_B
    SEGMENT_ROM_SIZE_CONST(segment_anime_c),       // CHARANIMEMODE_C
    SEGMENT_ROM_SIZE_CONST(segment_anime_g),       // CHARANIMEMODE_G
    SEGMENT_ROM_SIZE_CONST(segment_anime_k),       // CHARANIMEMODE_K
    SEGMENT_ROM_SIZE_CONST(segment_anime_l),       // CHARANIMEMODE_L
    SEGMENT_ROM_SIZE_CONST(segment_anime_o),       // CHARANIMEMODE_O
    SEGMENT_ROM_SIZE_CONST(segment_anime_mario),   // CHARANIMEMODE_MARIO
    SEGMENT_ROM_SIZE_CONST(segment_anime_virus_r), // CHARANIMEMODE_VIRUS_R
    SEGMENT_ROM_SIZE_CONST(segment_anime_virus_y), // CHARANIMEMODE_VIRUS_Y
    SEGMENT_ROM_SIZE_CONST(segment_anime_virus_b), // CHARANIMEMODE_VIRUS_B
    SEGMENT_ROM_SIZE_CONST(segment_anime_smog),    // CHARANIMEMODE_SMOG
};
static_assert(ARRAY_COUNT(_size_122) == CHARANIMEMODE_MAX, "");

/**
 * Original name: static _addrTbl
 */
const RomDataTblIndex _addrTbl_124[] = {
    ROMDATATBL_ANIME_M,       // CHARANIMEMODE_M
    ROMDATATBL_ANIME_N,       // CHARANIMEMODE_N
    ROMDATATBL_ANIME_H,       // CHARANIMEMODE_H
    ROMDATATBL_ANIME_I,       // CHARANIMEMODE_I
    ROMDATATBL_ANIME_J,       // CHARANIMEMODE_J
    ROMDATATBL_ANIME_D,       // CHARANIMEMODE_D
    ROMDATATBL_ANIME_E,       // CHARANIMEMODE_E
    ROMDATATBL_ANIME_F,       // CHARANIMEMODE_F
    ROMDATATBL_ANIME_A,       // CHARANIMEMODE_A
    ROMDATATBL_ANIME_B,       // CHARANIMEMODE_B
    ROMDATATBL_ANIME_C,       // CHARANIMEMODE_C
    ROMDATATBL_ANIME_G,       // CHARANIMEMODE_G
    ROMDATATBL_ANIME_K,       // CHARANIMEMODE_K
    ROMDATATBL_ANIME_L,       // CHARANIMEMODE_L
    ROMDATATBL_ANIME_O,       // CHARANIMEMODE_O
    ROMDATATBL_ANIME_MARIO,   // CHARANIMEMODE_MARIO
    ROMDATATBL_ANIME_VIRUS_R, // CHARANIMEMODE_VIRUS_R
    ROMDATATBL_ANIME_VIRUS_Y, // CHARANIMEMODE_VIRUS_Y
    ROMDATATBL_ANIME_VIRUS_B, // CHARANIMEMODE_VIRUS_B
    ROMDATATBL_ANIME_SMOG,    // CHARANIMEMODE_SMOG
};
static_assert(ARRAY_COUNT(_addrTbl_124) == CHARANIMEMODE_MAX, "");

/**
 * Original name: static _centerTbl
 */
const SAnimeStateCenter _centerTbl_125[] = {
    { 0x10, 0x2B }, // CHARANIMEMODE_M
    { 0x19, 0x2C }, // CHARANIMEMODE_N
    { 0x10, 0x29 }, // CHARANIMEMODE_H
    { 0x16, 0x28 }, // CHARANIMEMODE_I
    { 0x1A, 0x33 }, // CHARANIMEMODE_J
    { 0x18, 0x28 }, // CHARANIMEMODE_D
    { 0x18, 0x32 }, // CHARANIMEMODE_E
    { 0x13, 0x28 }, // CHARANIMEMODE_F
    { 0x20, 0x32 }, // CHARANIMEMODE_A
    { 0x12, 0x2F }, // CHARANIMEMODE_B
    { 0x20, 0x3E }, // CHARANIMEMODE_C
    { 0x23, 0x3C }, // CHARANIMEMODE_G
    { 0x14, 0x2F }, // CHARANIMEMODE_K
    { 0x1E, 0x31 }, // CHARANIMEMODE_L
    { 0x10, 0x2B }, // CHARANIMEMODE_O
    { 0x20, 0x40 }, // CHARANIMEMODE_MARIO
    { 0x10, 0x10 }, // CHARANIMEMODE_VIRUS_R
    { 0x10, 0x10 }, // CHARANIMEMODE_VIRUS_Y
    { 0x10, 0x10 }, // CHARANIMEMODE_VIRUS_B
    { 0x10, 0x10 }, // CHARANIMEMODE_SMOG
};
static_assert(ARRAY_COUNT(_centerTbl_125) == CHARANIMEMODE_MAX, "");

/**
 * Original name: animeSeq_init
 */
void animeSeq_init(SAnimeSeq *animeSeq, u8 **seqArray, AnimeNo animeNo) {
    animeSeq->seqArray = seqArray;
    animeSeq->stackDepth = -1;
    animeSeq->animeNo = animeNo;
    animeSeq->seqCount = 0;
    animeSeq->textureNo = -1;
    animeSeq_update(animeSeq, 0);
}

void animeSeq_set(SAnimeSeq *animeSeq, AnimeNo animeNo) {
    animeSeq_init(animeSeq, animeSeq->seqArray, animeNo);
}

/**
 * Original name: animeSeq_update
 */
void animeSeq_update(SAnimeSeq *animeSeq, s32 step) {
    while (step >= 0) {
        u8 *seqPtr = &animeSeq->seqArray[animeSeq->animeNo][animeSeq->seqCount];

        switch (seqPtr[0]) {
            case ANIME_METADATA_F0:
                animeSeq->seqCount += 2;
                animeSeq->stackDepth++;
                animeSeq->labelStack[animeSeq->stackDepth] = animeSeq->seqCount;
                animeSeq->countStack[animeSeq->stackDepth] = seqPtr[1];
                break;

            case ANIME_METADATA_F1:
                if (animeSeq->countStack[animeSeq->stackDepth] != 0xFF) {
                    animeSeq->countStack[animeSeq->stackDepth]--;
                }

                if ((animeSeq->countStack[animeSeq->stackDepth] != 0) && (seqPtr[1] > (rand() % 100))) {
                    animeSeq->seqCount = animeSeq->labelStack[animeSeq->stackDepth];
                } else {
                    animeSeq->seqCount += 2;
                    animeSeq->stackDepth--;
                }
                break;

            case ANIME_METADATA_F2:
                animeSeq->seqCount = 0;
                animeSeq->animeNo = seqPtr[1];
                animeSeq->stackDepth = -1;
                break;

            case ANIME_METADATA_END:
                step = -1;
                break;

            default:
                if (step > 0) {
                    animeSeq->seqCount++;
                }
                animeSeq->textureNo = seqPtr[0] - 1;
                step--;
                break;
        }
    }
}

/**
 * Original name: animeSeq_isEnd
 */
bool animeSeq_isEnd(const SAnimeSeq *animeSeq) {
    return animeSeq->seqArray[animeSeq->animeNo][animeSeq->seqCount] == ANIME_METADATA_END;
}

/**
 * Original name: animeState_getDataSize
 */
size_t animeState_getDataSize(CharAnimeMode animeMode) {
    return _size_122[animeMode];
}

/**
 * Original name: animeState_load
 */
void animeState_load(SAnimeState *animeState, void **heap, CharAnimeMode animeMode) {
    TiTexData *texArray;
    u8 **seqArray;
    RomDataTblIndex index = _addrTbl_124[animeMode];

    loadAnimeSeq(heap, &texArray, &seqArray, _romDataTbl[index][ROMTABLEPAIR_START],
                 _romDataTbl[index][ROMTABLEPAIR_END]);
    animeState_init(animeState, seqArray, texArray, _centerTbl_125[animeMode].cx, _centerTbl_125[animeMode].cy,
                    animeMode);
}

/**
 * Original name: animeState_init
 */
void animeState_init(SAnimeState *animeState, u8 **seqArray, TiTexData *texArray, s32 cx, s32 cy,
                     CharAnimeMode animeMode) {
    animeSeq_init(&animeState->animeSeq, seqArray, ANIMENO_0);
    animeState->texArray = texArray;
    animeState->frameCount = 0;
    animeState->center.cx = cx;
    animeState->center.cy = cy;
    animeState->animeMode = animeMode;
    animeState->primColor[0] = 255;
    animeState->primColor[1] = 255;
    animeState->primColor[2] = 255;
    animeState->primColor[3] = 255;
}

/**
 * Original name: animeState_set
 */
void animeState_set(SAnimeState *animeState, AnimeNo animeNo) {
    animeState->frameCount = 0;
    animeSeq_set(&animeState->animeSeq, animeNo);
}

/**
 * Original name: animeState_update
 */
void animeState_update(SAnimeState *animeState) {
    animeSeq_update(&animeState->animeSeq, animeState->frameCount % 2);
    animeState->frameCount++;
}

bool animeState_isEnd(const SAnimeState *animeState) {
    return animeSeq_isEnd(&animeState->animeSeq);
}

/**
 * Original name: animeState_initDL
 */
void animeState_initDL(SAnimeState *animeState, Gfx **gfxP) {
    Gfx *gfx = *gfxP;

    gSPDisplayList(gfx++, normal_texture_init_dl);
    gDPSetCombineMode(gfx++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
    gDPSetPrimColor(gfx++, 0, 0, animeState->primColor[0], animeState->primColor[1], animeState->primColor[2],
                    animeState->primColor[3]);

    if (animeState->primColor[3] < 255) {
        gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    }

    *gfxP = gfx;
}

/**
 * Original name: animeState_initDL2
 */
void animeState_initDL2(SAnimeState *animeState, Gfx **gfxP) {
    Gfx *gfx = *gfxP;

    gSPDisplayList(gfx++, normal_texture_init_dl);
    gDPSetCombineLERP(gfx++, TEXEL0, ENVIRONMENT, PRIMITIVE, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, TEXEL0, ENVIRONMENT,
                      PRIMITIVE, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0);
    gDPSetPrimColor(gfx++, 0, 0, animeState->primColor[0], animeState->primColor[1], animeState->primColor[2],
                    animeState->primColor[3]);
    gDPSetEnvColor(gfx++, 0, 0, 0, 255);
    if (animeState->primColor[3] < 255) {
        gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    }
    *gfxP = gfx;
}

/**
 * Original name: animeState_initIntensityDL
 */
void animeState_initIntensityDL(SAnimeState *animeState, Gfx **gfxP) {
    Gfx *gfx = *gfxP;

    gSPDisplayList(gfx++, normal_texture_init_dl);
    gDPSetTextureLUT(gfx++, G_TT_NONE);
    gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gDPSetCombineLERP(gfx++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, PRIMITIVE,
                      ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0);
    gDPSetPrimColor(gfx++, 0, 0, animeState->primColor[0], animeState->primColor[1], animeState->primColor[2],
                    animeState->primColor[3]);
    gDPSetEnvColor(gfx++, 0, 0, 0, 255);

    *gfxP = gfx;
}

/**
 * Original name: animeState_draw
 */
void animeState_draw(SAnimeState *animeState, Gfx **gfxP, f32 x, f32 y, f32 sx, f32 sy) {
    Gfx *gfx = *gfxP;
    TiTexData *texC;
    TiTexData *pal;

    if (animeState->animeSeq.textureNo < 0) {
        return;
    }

    pal = &animeState->texArray[0];
    texC = &animeState->texArray[animeState->animeSeq.textureNo];
    if (sx < 0.0f) {
        x = x - (animeState->center.cx - texC->info[TI_INFO_IDX_WIDTH]) * sx;
    } else {
        x = x - animeState->center.cx * sx;
    }

    if (sy < 0.0f) {
        y -= (animeState->center.cy - texC->info[TI_INFO_IDX_HEIGHT]) * sy;
    } else {
        y -= animeState->center.cy * sy;
    }

    if (animeState->animeMode == CHARANIMEMODE_MARIO) {
        y -= (texC->info[TI_INFO_IDX_HEIGHT] - 0x40) * sy;
    }

    switch (texC->info[TI_INFO_IDX_FORMAT]) {
        case TITEX_FORMAT_4:
            StretchTexTile4(&gfx, texC->info[TI_INFO_IDX_WIDTH], texC->info[TI_INFO_IDX_HEIGHT],
                            pal[0].texs[TI_TEX_TLUT], texC->texs[TI_TEX_TEX], 0, 0, texC->info[TI_INFO_IDX_WIDTH],
                            texC->info[TI_INFO_IDX_HEIGHT], x, y, texC->info[TI_INFO_IDX_WIDTH] * sx,
                            texC->info[TI_INFO_IDX_HEIGHT] * sy);
            break;

        case TITEX_FORMAT_8:
            StretchTexTile8(&gfx, texC->info[TI_INFO_IDX_WIDTH], texC->info[TI_INFO_IDX_HEIGHT],
                            pal[0].texs[TI_TEX_TLUT], texC->texs[TI_TEX_TEX], 0, 0, texC->info[TI_INFO_IDX_WIDTH],
                            texC->info[TI_INFO_IDX_HEIGHT], x, y, texC->info[TI_INFO_IDX_WIDTH] * sx,
                            texC->info[TI_INFO_IDX_HEIGHT] * sy);
            break;
    }

    *gfxP = gfx;
}

/**
 * Original name: animeState_drawI
 */
void animeState_drawI(SAnimeState *animeState, Gfx **gfxP, f32 x, f32 y, f32 sx, f32 sy) {
    Gfx *gfx = *gfxP;
    TiTexData *texC;

    if (animeState->animeSeq.textureNo < 0) {
        return;
    }

    texC = &animeState->texArray[animeState->animeSeq.textureNo];

    if (sx < 0.0f) {
        x -= (animeState->center.cx - texC->info[TI_INFO_IDX_WIDTH]) * sx;
    } else {
        x -= animeState->center.cx * sx;
    }

    if (sy < 0.0f) {
        y -= (animeState->center.cy - texC->info[TI_INFO_IDX_HEIGHT]) * sy;
    } else {
        y -= animeState->center.cy * sy;
    }

    StretchTexTile4i(&gfx, texC->info[TI_INFO_IDX_WIDTH], texC->info[TI_INFO_IDX_HEIGHT], texC->texs[TI_TEX_TEX], 0, 0,
                     texC->info[TI_INFO_IDX_WIDTH], texC->info[TI_INFO_IDX_HEIGHT], x, y,
                     texC->info[TI_INFO_IDX_WIDTH] * sx, texC->info[TI_INFO_IDX_HEIGHT] * sy);
    *gfxP = gfx;
}

/**
 * Original name: animeSmog_init
 */
void animeSmog_init(SAnimeSmog *animeSmog, SAnimeState *state) {
    s32 i;

    for (i = 0; i < ARRAY_COUNTU(animeSmog->animeState); i++) {
        animeState_init(&animeSmog->animeState[i], state->animeSeq.seqArray, state->texArray, state->center.cx,
                        state->center.cy, CHARANIMEMODE_SMOG);
        animeState_set(&animeSmog->animeState[i], ANIMENO_2);
        animeSmog->pos[i].y = 0;
        animeSmog->pos[i].x = 0;
    }
    animeSmog->frameCount = 180;
}

/**
 * Original name: animeSmog_load
 */
void animeSmog_load(SAnimeSmog *animeSmog, void **ptr) {
    animeState_load(animeSmog->animeState, ptr, CHARANIMEMODE_SMOG);
    animeSmog_init(animeSmog, &animeSmog->animeState[0]);
}

/**
 * Original name: animeSmog_start
 */
void animeSmog_start(SAnimeSmog *animeSmog) {
    animeSmog->frameCount = 0;
}

/**
 * Original name: animeSmog_stop
 */
void animeSmog_stop(SAnimeSmog *animeSmog) {
    u32 i;

    for (i = 0; i < ARRAY_COUNT(animeSmog->animeState); i++) {
        animeState_set(&animeSmog->animeState[i], ANIMENO_2);
    }

    animeSmog->frameCount = 180;
}

/**
 * Original name: animeSmog_update
 */
void animeSmog_update(SAnimeSmog *animeSmog) {
    s32 i;

    for (i = 0; i < ANIMESMOG_COUNT; i++) {
        animeState_update(&animeSmog->animeState[i]);
        if ((animeSmog->frameCount < 180) && animeState_isEnd(&animeSmog->animeState[i]) && (rand() % 16 == 0)) {
            animeState_set(&animeSmog->animeState[i], ANIMENO_0);
            animeSmog->pos[i].x = (rand() % 20) - 10;
            animeSmog->pos[i].y = (rand() % 20) - 10;
        }
    }

    animeSmog->frameCount = MIN(180, animeSmog->frameCount + 1);
}

/**
 * Original name: animeSmog_draw
 */
void animeSmog_draw(SAnimeSmog *animeSmog, Gfx **gfxP, f32 x, f32 y, f32 sx, f32 sy) {
    Gfx *gfx = *gfxP;
    u32 i;

    for (i = 0; i < ARRAY_COUNT(animeSmog->animeState); i++) {
        animeState_initIntensityDL(&animeSmog->animeState[i], &gfx);

        if (!animeState_isEnd(&animeSmog->animeState[i])) {
            animeState_drawI(&animeSmog->animeState[i], &gfx, x + animeSmog->pos[i].x * sx,
                             y + animeSmog->pos[i].y * sy, sx, sy);
        }
    }

    *gfxP = gfx;
}

/**
 * Original name: mappingAnimeSeq
 */
void mappingAnimeSeq(u8 **metadata, s32 len, uintptr_t addr) {
    s32 i;

    for (i = 0; i < len; i++) {
        metadata[i] = (void *)((uintptr_t)metadata[i] + addr);
    }
}

/**
 * Original name: loadAnimeSeq
 *
 * Loads an anime segment.
 *
 * The segment is loaded into the passed heap and the heap argument will be updated to point to the memory after the
 * used one.
 *
 * The data from the anime segment is placed into `texDataDst` and `metadataDst`
 */
void loadAnimeSeq(void **heapP, TiTexData **texDataDst, u8 ***metadataDst, RomOffset romOffsetStart,
                  RomOffset romOffsetEnd) {
    AnimeHeader *anime = ALIGN_PTR(*heapP);
    TiTexData *texData;
    s32 *texDataLen;
    u8 **metadata;
    s32 *metadataLen;

    *heapP = DecompressRomToRam(romOffsetStart, anime, romOffsetEnd - romOffsetStart);

    texData = (void *)((uintptr_t)anime->texData + (uintptr_t)anime);
    texDataLen = (void *)((uintptr_t)anime->texDataLen + (uintptr_t)anime);
    anime->texData = texData;
    anime->texDataLen = texDataLen;
    *texDataDst = texData;
    tiMappingAddr(texData, *texDataLen, (uintptr_t)anime);

    metadata = (void *)((uintptr_t)anime->metadata + (uintptr_t)anime);
    metadataLen = (void *)((uintptr_t)anime->metadataLen + (uintptr_t)anime);
    anime->metadata = metadata;
    anime->metadataLen = metadataLen;

    *metadataDst = metadata;
    mappingAnimeSeq(metadata, *metadataLen, (uintptr_t)anime);
}

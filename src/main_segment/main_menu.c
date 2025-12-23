/**
 * Original filename: main_menu.c
 */

#include "main_menu.h"

#include "libc/stdbool.h"
#include "libultra.h"

#include "macros_defines.h"
#include "util.h"
#include "rom_offsets.h"
#include "audio/sound.h"
#include "buffers.h"
#include "libc/assert.h"
#include "libc/ctype.h"
#include "graphic.h"
#include "record.h"
#include "main1x.h"
#include "bg_tasks.h"
#include "tex_func.h"
#include "main_story.h"
#include "nnsched.h"
#include "font.h"
#include "dm_virus_init.h"
#include "dm_thread.h"

#if VERSION_US || CC_CHECK
#else
#define AVOID_JOY_FUNCTIONS 1
#endif
#include "joy.h"

/**
 * Original name: watchMenu
 */
struct_watchMenu *watchMenu;
/**
 * Original name: _menuMain_lastDepth
 */
s32 _menuMain_lastDepth;
/**
 * Original name: _menuMain_lastSelect
 */
s32 _menuMain_lastSelect[8]; // probably an enum

/**
 * Original name: timeFunc_update
 */
f32 timeFunc_update(f32 time, f32 step) {
    time += step;

    if (time < 0.0f) {
        time = 0.0f;
    } else if (time > 1.0f) {
        time = 1.0f;
    }
    return time;
}

/**
 * Original name: timeFunc_loop
 */
f32 timeFunc_loop(f32 time, f32 step) {
    return WrapF(0.0f, 1.0f, time + step);
}

/**
 * Original name: coordFunc_curve
 */
f32 coordFunc_curve(f32 time) {
    if (time < DOUBLE_LITERAL(0.5)) {
        time = SQ(time);
    } else {
        time = DOUBLE_LITERAL(1) - time;
        time = DOUBLE_LITERAL(0.5) - SQ(time);
    }

    return 2.0f * time;
}

/**
 * Original name: transFunc_linear
 */
void transFunc_linear(SMenuItem *item) {
    f32 transTime = timeFunc_update(item->transTime, item->transStep);
    s32 i;

    item->transTime = transTime;
    for (i = 0; i < MENUITEM_DIM; i++) {
        item->trans[i] = item->transRange[0][i] + (item->transRange[1][i] - item->transRange[0][i]) * transTime;
    }
}

/**
 * Original name: transFunc_curve
 */
void transFunc_curve(SMenuItem *item) {
    f32 transTime = timeFunc_update(item->transTime, item->transStep);
    f32 coord = coordFunc_curve(transTime);
    s32 i;

    item->transTime = transTime;

    for (i = 0; i < ARRAY_COUNTU(item->trans); i++) {
        item->trans[i] = item->transRange[0][i] + ((item->transRange[1][i] - item->transRange[0][i]) * coord);
    }
}

/**
 * Original name: transFunc_finger
 */
void transFunc_finger(SMenuItem *item) {
    f32 transTime = timeFunc_loop(item->transTime, item->transStep);
    f32 temp_fv0_2 = (sinf(2 * DOUBLE_LITERAL(M_PI) * transTime) + DOUBLE_LITERAL(1)) * DOUBLE_LITERAL(0.5);
    s32 i;

    item->transTime = transTime;

    for (i = 0; i < ARRAY_COUNTU(item->trans); i++) {
        item->trans[i] = item->transRange[0][i] + (item->transRange[1][i] - item->transRange[0][i]) * temp_fv0_2;
    }
}

/**
 * Original name: scaleFunc_linear
 */
void scaleFunc_linear(SMenuItem *item) {
    f32 scaleTime = timeFunc_update(item->scaleTime, item->scaleStep);
    s32 i;

    item->scaleTime = scaleTime;
    for (i = 0; i < MENUITEM_DIM; i++) {
        item->scale[i] = item->scaleRange[0][i] + (item->scaleRange[1][i] - item->scaleRange[0][i]) * scaleTime;
    }
}

/**
 * Original name: scaleFunc_curve
 */
void scaleFunc_curve(SMenuItem *item) {
    f32 scaleTime = timeFunc_update(item->scaleTime, item->scaleStep);
    f32 coord = coordFunc_curve(scaleTime);
    s32 i;

    item->scaleTime = scaleTime;

    for (i = 0; i < ARRAY_COUNTU(item->scale); i++) {
        item->scale[i] = item->scaleRange[0][i] + (item->scaleRange[1][i] - item->scaleRange[0][i]) * coord;
    }
}

/**
 * Original name: colorFunc_linear
 */
void colorFunc_linear(SMenuItem *item) {
    f32 colorTime = timeFunc_update(item->colorTime, item->colorStep);
    s32 i;

    item->colorTime = colorTime;
    for (i = 0; i < MENUITEM_COLOR_COUNT; i++) {
        item->color[i] = item->colorRange[0][i] + (item->colorRange[1][i] - item->colorRange[0][i]) * colorTime;
    }
}

/**
 * Original name: colorFunc_curve
 */
void colorFunc_curve(SMenuItem *item) {
    f32 colorTime = timeFunc_update(item->colorTime, item->colorStep);
    f32 coord = coordFunc_curve(colorTime);
    s32 i;

    item->colorTime = colorTime;

    for (i = 0; i < MENUITEM_COLOR_COUNT; i++) {
        item->color[i] = item->colorRange[0][i] + ((item->colorRange[1][i] - item->colorRange[0][i]) * coord);
    }
}

/**
 * Original name: colorFunc_cursor
 */
void colorFunc_cursor(SMenuItem *item) {
    f32 time = timeFunc_loop(item->colorTime, item->colorStep);
    f32 coord = (sinf(2 * DOUBLE_LITERAL(M_PI) * time) + DOUBLE_LITERAL(1)) * DOUBLE_LITERAL(0.5);
    s32 i;

    item->colorTime = time;

    for (i = 0; i < MENUITEM_COLOR_COUNT; i++) {
        item->color[i] = item->colorRange[0][i] + (item->colorRange[1][i] - item->colorRange[0][i]) * coord;
    }
}

/**
 * Original name: color_251
 */
const f32 color_251[] = {
    0.5f,
    0.5f,
    0.5f,
    1.0f,
};

/**
 * Original name: menuItem_init
 */
void menuItem_init(SMenuItem *item, s32 x, s32 y) {
    u32 i;

    item->center[0] = 0.0f;
    item->center[1] = 0.0f;

    item->transFunc = transFunc_curve;

    item->transRange[1][0] = x;
    item->transRange[0][0] = x;
    item->trans[0] = x;

    item->transRange[1][1] = y;
    item->transRange[0][1] = y;
    item->trans[1] = y;

    item->scaleFunc = scaleFunc_curve;
    item->transTime = 1.0f;
    item->transStep = 0.125f;
    item->scaleTime = 1.0f;
    item->scaleStep = 0.125f;

    for (i = 0; i < MENUITEM_DIM; i++) {
        item->scale[i] = 1.0f;
        item->scaleRange[0][i] = 0.0f;
        item->scaleRange[1][i] = 1.0f;
    }

    item->colorFunc = colorFunc_curve;
    item->colorTime = 1.0f;
    item->colorStep = 0.125f;

    for (i = 0; i < MENUITEM_COLOR_COUNT; i++) {
        item->color[i] = 1.0f;
        item->colorRange[0][i] = color_251[i];
        item->colorRange[1][i] = 1.0f;
    }

    item->flags.localColor = false;
    item->flags.localAlpha = false;
}

/**
 * Original name: menuItem_updateTransScale
 */
void menuItem_updateTransScale(SMenuItem *item, SMenuItem *parent) {
    s32 i;

    item->transFunc(item);
    item->scaleFunc(item);

    if (parent == NULL) {
        return;
    }

    for (i = 0; i < MENUITEM_DIM; i++) {
        item->trans[i] = item->trans[i] * parent->scale[i] + parent->trans[i];

        item->scale[i] *= parent->scale[i];
        item->trans[i] -= item->center[i] * item->scale[i];
    }
}

/**
 * Original name: menuItem_updateColor
 */
void menuItem_updateColor(SMenuItem *item, SMenuItem *parent) {
    s32 i;

    item->colorFunc(item);

    if (parent == NULL) {
        return;
    }

    if (!item->flags.localColor) {
        for (i = 0; i < MENUITEM_COLOR_COUNT - 1; i++) {
            item->color[i] *= parent->color[i];
        }
    }

    if (!item->flags.localAlpha) {
        for (i = MENUITEM_COLOR_COUNT - 1; i < MENUITEM_COLOR_COUNT; i++) {
            item->color[i] *= parent->color[i];
        }
    }
}

/**
 * Original name: menuItem_update
 */
void menuItem_update(SMenuItem *item, SMenuItem *parent) {
    menuItem_updateTransScale(item, parent);
    menuItem_updateColor(item, parent);
}

/**
 * Original name: menuItem_updateN
 */
void menuItem_updateN(SMenuItem items[], s32 count, SMenuItem *parent) {
    s32 i;

    for (i = 0; i < count; i++) {
        menuItem_update(&items[i], parent);
    }
}

/**
 * Original name: menuItem_updateN
 */
void menuItem_setTransDir(SMenuItem *item, s32 dir) {
    if (((dir < 0) && (item->transStep > 0.0f)) || ((dir > 0) && (item->transStep < 0.0f))) {
        item->transStep = -item->transStep;
    }
}

void menuItem_setScaleDir(SMenuItem *item, s32 dir) {
    if (((dir < 0) && (item->scaleStep > 0.0f)) || ((dir > 0) && (item->scaleStep < 0.0f))) {
        item->scaleStep = -item->scaleStep;
    }
}

void menuItem_setColorDir(SMenuItem *item, s32 dir) {
    if (((dir < 0) && (item->colorStep > 0.0f)) || ((dir > 0) && (item->colorStep < 0.0f))) {
        item->colorStep = -item->colorStep;
    }
}

void menuItem_setTransLow(SMenuItem *item, f32 x, f32 y) {
    item->transRange[0][0] = x;
    item->transRange[0][1] = y;
}

void menuItem_setTransHi(SMenuItem *item, f32 x, f32 y) {
    item->transRange[1][0] = x;
    item->transRange[1][1] = y;
}

void menuItem_setScaleLow(SMenuItem *item, f32 x, f32 y) {
    item->scaleRange[0][0] = x;
    item->scaleRange[0][1] = y;
}

void menuItem_setScaleHi(SMenuItem *item, f32 x, f32 y) {
    item->scaleRange[1][0] = x;
    item->scaleRange[1][1] = y;
}

void menuItem_setColorLow(SMenuItem *item, f32 bright, f32 alpha) {
    item->colorRange[0][3] = alpha;
    item->colorRange[0][2] = bright;
    item->colorRange[0][1] = bright;
    item->colorRange[0][0] = bright;
}

void menuItem_setColorHi(SMenuItem *item, f32 bright, f32 alpha) {
    item->colorRange[1][3] = alpha;
    item->colorRange[1][2] = bright;
    item->colorRange[1][1] = bright;
    item->colorRange[1][0] = bright;
}

void menuItem_setColor_cursor(SMenuItem *item) {
    item->colorFunc = colorFunc_cursor;
    item->colorStep = 1.0f / 32.0f;
    menuItem_setColorLow(item, 0.5f, 1.0f);
    menuItem_setColorHi(item, 1.0f, 1.0f);
}

void menuItem_setColor_cursor2(SMenuItem *item, f32 red, f32 green, f32 blue) {
    f32 rgb[] = { red, green, blue };
    s32 i;

    item->colorStep = 1.0f / 32.0f;
    item->colorFunc = colorFunc_cursor;
    menuItem_setColorLow(item, 0.5f, 1.0f);
    menuItem_setColorHi(item, 1.0f, 1.0f);

    for (i = 0; i < ARRAY_COUNT(rgb); i++) {
        item->colorRange[0][i] *= rgb[i];
        item->colorRange[1][i] = item->colorRange[1][i] * rgb[i];
    }
}

void menuItem_setColor_fade(SMenuItem *item) {
    item->colorFunc = colorFunc_curve;
    item->colorStep = 0.125f;
    menuItem_setColorLow(item, 1.0f, 0.0f);
    menuItem_setColorHi(item, 1.0f, 1.0f);
}

void menuItem_setPrim(SMenuItem *item, Gfx **gfxP) {
    Gfx *gfx = *gfxP;
    Color_RGBA32 color = {
        CLAMP(item->color[0], 0.0f, 1.0f) * 255,
        CLAMP(item->color[1], 0.0f, 1.0f) * 255,
        CLAMP(item->color[2], 0.0f, 1.0f) * 255,
        CLAMP(item->color[3], 0.0f, 1.0f) * 255,
    };

    gDPSetPrimColor(gfx++, 0, 0, color.r, color.g, color.b, color.a);

    *gfxP = gfx;
}

/**
 * Original name: menuItem_outOfScreen
 */
bool menuItem_outOfScreen(SMenuItem *item, s32 width, s32 height) {
    if ((item->color[3] <= 0) || (item->trans[0] >= SCREEN_WIDTH) || (item->trans[1] >= SCREEN_HEIGHT) ||
        (item->trans[0] + width * item->scale[0] < 0) || (item->trans[1] + height * item->scale[1] < 0) ||
        (item->scale[0] == 0.0f) || (item->scale[1] == 0.0f)) {
        return true;
    }
    return false;
}

/**
 * Original name: menuItem_drawTex
 */
bool menuItem_drawTex(SMenuItem *item, Gfx **gfxP, TiTexData *tex, bool cached) {
    if (menuItem_outOfScreen(item, tex->info[TI_INFO_IDX_WIDTH], tex->info[TI_INFO_IDX_HEIGHT])) {
        return false;
    }

    menuItem_setPrim(item, gfxP);
    if (tex->info[TI_INFO_IDX_FLAGS] & TITEX_FLAGS_BLOCK) {
        tiStretchTexBlock(gfxP, tex, cached, item->trans[0], item->trans[1],
                          tex->info[TI_INFO_IDX_WIDTH] * item->scale[0],
                          tex->info[TI_INFO_IDX_HEIGHT] * item->scale[1]);
    } else {
        tiStretchTexTile(gfxP, tex, cached, 0, 0, tex->info[TI_INFO_IDX_WIDTH], tex->info[TI_INFO_IDX_HEIGHT],
                         item->trans[0], item->trans[1], tex->info[TI_INFO_IDX_WIDTH] * item->scale[0],
                         tex->info[TI_INFO_IDX_HEIGHT] * item->scale[1]);
    }
    return true;
}

/**
 * Original name: menuItem_drawTex2
 */
bool menuItem_drawTex2(SMenuItem *item, Gfx **gfxP, TiTexData *tex, bool cached, f32 x, f32 y, f32 sx, f32 sy) {
    f32 bak[4] = {
        item->trans[0],
        item->trans[1],
        item->scale[0],
        item->scale[1],
    };
    bool drawn;

    item->trans[0] += x;
    item->trans[1] += y;
    item->scale[0] *= sx;
    item->scale[1] *= sy;

    drawn = menuItem_drawTex(item, gfxP, tex, cached);

    item->trans[0] = bak[0];
    item->trans[1] = bak[1];
    item->scale[0] = bak[2];
    item->scale[1] = bak[3];

    return drawn;
}

/**
 * Original name: menuItem_drawAlphaTex
 */
bool menuItem_drawAlphaTex(SMenuItem *item, Gfx **gfxP, TiTexData *texC, TiTexData *texA, bool cached) {
    s32 width = MIN(texC->info[TI_INFO_IDX_WIDTH], texA->info[TI_INFO_IDX_WIDTH]);
    s32 height = MIN(texC->info[TI_INFO_IDX_HEIGHT], texA->info[TI_INFO_IDX_HEIGHT]);
    const Texture *sp48[2];

    if (menuItem_outOfScreen(item, width, height)) {
        return false;
    }

    menuItem_setPrim(item, gfxP);

    if (cached) {
        sp48[0] = NULL;
        sp48[1] = NULL;
    } else {
        sp48[0] = texC->texs[TI_TEX_TEX];
        sp48[1] = texA->texs[TI_TEX_TEX];
    }

    if ((texC->info[TI_INFO_IDX_FLAGS] & TITEX_FLAGS_BLOCK) && (texA->info[TI_INFO_IDX_FLAGS] & TITEX_FLAGS_BLOCK)) {
        StretchAlphaTexBlock(gfxP, width, height, sp48[0], texC->info[TI_INFO_IDX_WIDTH], sp48[1],
                             texA->info[TI_INFO_IDX_WIDTH], item->trans[0], item->trans[1], width * item->scale[0],
                             height * item->scale[1]);
    } else {
        StretchAlphaTexTile(gfxP, width, height, texC->texs[TI_TEX_TEX], texC->info[TI_INFO_IDX_WIDTH],
                            texA->texs[TI_TEX_TEX], texA->info[TI_INFO_IDX_WIDTH], 0, 0, width,
                            texC->info[TI_INFO_IDX_HEIGHT], item->trans[0], item->trans[1], width * item->scale[0],
                            height * item->scale[1]);
    }

    return true;
}

/**
 * Original name: menuItem_drawItem
 */
bool menuItem_drawItem(SMenuItem *item, Gfx **gfxP, TiTexData *tex, bool cached, s32 itemCount, s32 itemIndex) {
    s32 height = tex->info[TI_INFO_IDX_HEIGHT] / itemCount;

    if (menuItem_outOfScreen(item, tex->info[TI_INFO_IDX_WIDTH], height)) {
        return false;
    }

    menuItem_setPrim(item, gfxP);
    tiStretchTexItem(gfxP, tex, cached, itemCount, itemIndex, item->trans[0], item->trans[1],
                     tex->info[TI_INFO_IDX_WIDTH] * item->scale[0], height * item->scale[1]);
    return true;
}

/**
 * Original name: menuItem_drawItem2
 */
bool menuItem_drawItem2(SMenuItem *item, Gfx **gfxP, TiTexData *tex, bool cached, s32 itemCount, s32 itemIndex, f32 x,
                        f32 y, f32 sx, f32 sy) {
    f32 sp20[4] = {
        item->trans[0],
        item->trans[1],
        item->scale[0],
        item->scale[1],
    };
    s32 ret;

    item->trans[0] += x;
    item->trans[1] += y;
    item->scale[0] *= sx;
    item->scale[1] *= sy;
    ret = menuItem_drawItem(item, gfxP, tex, cached, itemCount, itemIndex);
    item->trans[0] = sp20[0];
    item->trans[1] = sp20[1];
    item->scale[0] = sp20[2];
    item->scale[1] = sp20[3];

    return ret;
}

bool menuItem_drawAlphaItem(SMenuItem *item, Gfx **gfxP, TiTexData *texC, TiTexData *texA, bool cached, s32 itemCount,
                            s32 itemIndex) {
    s32 width = MIN(texC->info[TI_INFO_IDX_WIDTH], texA->info[TI_INFO_IDX_WIDTH]);
    s32 height = MIN(texC->info[TI_INFO_IDX_HEIGHT], texA->info[TI_INFO_IDX_HEIGHT]) / itemCount;

    if (menuItem_outOfScreen(item, width, height)) {
        return false;
    }

    menuItem_setPrim(item, gfxP);
    tiStretchAlphaTexItem(gfxP, texC, texA, cached, itemCount, itemIndex, item->trans[0], item->trans[1],
                          width * item->scale[0], height * item->scale[1]);
    return true;
}

bool menuItem_drawAlphaItem2(SMenuItem *item, Gfx **gfxP, TiTexData *texC, TiTexData *texA, bool cached, s32 itemCount,
                             s32 itemIndex) {
    s32 width = MIN(texC->info[TI_INFO_IDX_WIDTH], texA->info[TI_INFO_IDX_WIDTH]);
    s32 height = MIN(texC->info[TI_INFO_IDX_HEIGHT] / itemCount, texA->info[TI_INFO_IDX_HEIGHT]);

    if (menuItem_outOfScreen(item, width, height)) {
        return false;
    }

    menuItem_setPrim(item, gfxP);
    tiStretchAlphaTexItem2(gfxP, texC, texA, cached, itemCount, itemIndex, item->trans[0], item->trans[1],
                           width * item->scale[0], height * item->scale[1]);
    return true;
}

/**
 * Original name: fade_normal_texture_init_dl
 */
const Gfx fade_normal_texture_init_dl[] = {
    gsSPDisplayList(normal_texture_init_dl),
    gsDPSetCombineLERP(TEXEL0, ENVIRONMENT, PRIMITIVE, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, TEXEL0, ENVIRONMENT,
                       PRIMITIVE, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0),
    gsSPEndDisplayList(),
};

/**
 * Original name: fade_alpha_texture_init_dl
 */
const Gfx fade_alpha_texture_init_dl[] = {
    gsSPDisplayList(alpha_texture_init_dl),
    gsDPSetCombineLERP(TEXEL0, ENVIRONMENT, PRIMITIVE, ENVIRONMENT, TEXEL1, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0,
                       COMBINED),
    gsSPEndDisplayList(),
};

/**
 * Original name: fade_intensity_texture_init_dl
 */
const Gfx fade_intensity_texture_init_dl[] = {
    gsSPDisplayList(normal_texture_init_dl),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, PRIMITIVE, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, PRIMITIVE, ENVIRONMENT,
                       PRIMITIVE, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetTextureLUT(G_TT_NONE),
    gsSPEndDisplayList(),
};

/**
 * Original name: fade_fillrect_init_dl
 */
const Gfx fade_fillrect_init_dl[] = {
    gsSPDisplayList(normal_texture_init_dl),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, PRIMITIVE, ENVIRONMENT, 0, 0, 0, PRIMITIVE, PRIMITIVE, ENVIRONMENT,
                       PRIMITIVE, ENVIRONMENT, 0, 0, 0, PRIMITIVE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetTextureLUT(G_TT_NONE),
    gsSPEndDisplayList(),
};

/**
 * Original name: fade_shadow_texture_init_dl
 */
const Gfx fade_shadow_texture_init_dl[] = {
    gsSPDisplayList(normal_texture_init_dl),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, PRIMITIVE, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, PRIMITIVE, ENVIRONMENT,
                       PRIMITIVE, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsSPEndDisplayList(),
};

// unused
// TODO: figure out if this is actually unused or not
const f32 FLT_800ADD00[] = {
    0.65f, 0.5f, 0.5f, 0.5f, 0.5f, 0.65f, 0.5f, 0.65f, 0.5f, 0.65f, 0.65f, 0.5f, 0.5f, 0.5f, 0.5f,
};

/**
 * Original name: _timeAttack_levelTable
 */
const u8 _timeAttack_levelTable[] = {
    0x06,
    0x09,
    0x0C,
    0x00,
};

#include "main_menu.msg.inc"

/**
 * Original name: _gameLvItemColor
 */
const u8 _gameLvItemColor[][MENUITEM_UNK_LEN3][MENUITEM_COLOR_COUNT] = {
    { { 0, 0, 0, 80 }, { 128, 160, 255, 200 } },
    { { 0, 0, 0, 80 }, { 255, 255, 64, 200 } },
    { { 0, 0, 0, 80 }, { 255, 144, 64, 200 } },
};
static_assert(ARRAY_COUNT(_gameLvItemColor) == MENUSPEEDITEM_UNK_LEN, "");

/**
 * Original name: _musicItemColor
 */
const u8 _musicItemColor[][MENUITEM_COLOR_COUNT] = {
    { 0, 0, 0, 80 },
    { 255, 160, 200, 200 },
};
static_assert(ARRAY_COUNT(_musicItemColor) == MENUITEM_UNK_LEN3, "");

/**
 * Original name: menuTitle_setTitle
 */
void menuTitle_setTitle(MenuTitle *title, MainMenuMode mode) {
    s32 titleNo = -1;

    switch (mode) {
        case MODE_MAIN:
        case MODE_PLAY1:
        case MODE_PLAY2:
        case MODE_PLAY4:
        case MODE_PLAY4_TYPE1:
        case MODE_PLAY4_TYPE2:
        case MODE_PLAY4_TYPE3:
        case MODE_PLAY4_TYPE4:
            titleNo = 0;
            break;

        case MODE_OPTION:
        case MODE_TUTORIAL:
        case MODE_CONT:
        case MODE_NAME_NS:
        case MODE_NAME:
        case MODE_NAME_NE:
        case MODE_NAME_NE2:
        case MODE_NAME_DEL_YN:
        case MODE_BACKUP:
        case MODE_BACKUP_YN:
        case MODE_MISC:
        case MODE_SOUND:
        case MODE_COUNT:
        case MODE_SCORE:
            titleNo = 1;
            break;

        case MODE_LVSEL_TA_NS:
        case MODE_LVSEL_TA_NE:
        case MODE_LVSEL_TA:
        case MODE_VSMAN_TA_NS:
        case MODE_VSMAN_TA_NE:
        case MODE_VSMAN_TA_CH:
        case MODE_VSMAN_TA:
            titleNo = 2;
            break;

        case MODE_PLAY4_TB_CH:
        case MODE_PLAY4_TB_LV:
            titleNo = 3;
            break;

        case MODE_RECORD_MS:
        case MODE_RECORD_PLAY1:
        case MODE_RECORD_ST:
        case MODE_RECORD_LS:
        case MODE_RECORD_LS_TQ:
        case MODE_RECORD_LS_TA:
        case MODE_RECORD_VC:
        case MODE_RECORD_VC_FL:
        case MODE_RECORD_PLAY2:
        case MODE_RECORD_VM:
        case MODE_RECORD_VM_FL:
        case MODE_RECORD_VM_TA:
            titleNo = 4;
            break;

        case MODE_LVSEL_NS:
        case MODE_LVSEL_NE:
        case MODE_LVSEL:
            titleNo = 5;
            break;

        case MODE_STORY_NS:
        case MODE_STORY_NE:
        case MODE_STORY:
            titleNo = 6;
            break;

        case MODE_PLAY4_CH:
        case MODE_PLAY4_LV:
            titleNo = 7;
            break;

        case MODE_VSCOM_NS:
        case MODE_VSCOM_NE:
        case MODE_VSCOM_CH:
        case MODE_VSCOM:
            titleNo = 8;
            break;

        case MODE_VSMAN_NS:
        case MODE_VSMAN_NE:
        case MODE_VSMAN_CH:
        case MODE_VSMAN:
            titleNo = 9;
            break;

        case MODE_VSCOM_FL_NS:
        case MODE_VSCOM_FL_NE:
        case MODE_VSCOM_FL_CH:
        case MODE_VSCOM_FL:
        case MODE_VSMAN_FL_NS:
        case MODE_VSMAN_FL_NE:
        case MODE_VSMAN_FL_CH:
        case MODE_VSMAN_FL:
        case MODE_PLAY4_FL_CH:
        case MODE_PLAY4_FL_LV:
            titleNo = 0xA;
            break;

        case MODE_LVSEL_TQ_NS:
        case MODE_LVSEL_TQ_NE:
        case MODE_LVSEL_TQ:
            titleNo = 0xB;
            break;

        default:
            break;
    }

    if (title->titleNo[title->current] != titleNo) {
        title->current = INC_WRAP(title->current, MENUTITLE_TLT_COUNT);
        title->miBase[title->current].colorTime = 0.0f;
        title->titleNo[title->current] = titleNo;
    }
}

/**
 * Original name: menuTitle_init
 */
void menuTitle_init(MenuTitle *title, struct_watchMenu *global, s32 x, s32 y) {
    s32 i;

    title->global = global;
    title->current = 0;
    title->titleNo[0] = -1;
    title->titleNo[1] = -1;

    for (i = 0; i < MENUTITLE_TLT_COUNT; i++) {
        menuItem_init(&title->miBase[i], x, y);
        menuItem_setColor_fade(&title->miBase[i]);
    }
}

/**
 * Original name: menuTitle_update
 */
void menuTitle_update(MenuTitle *title, SMenuItem *parent) {
    menuItem_updateN(title->miBase, MENUTITLE_TLT_COUNT, parent);
}

/**
 * Original name: menuTitle_draw
 */
void menuTitle_draw(MenuTitle *title, Gfx **gfxP) {
    Gfx *gfx = *gfxP;
    TiTexData *texC;
    s32 i;

    gSPDisplayList(gfx++, fade_normal_texture_init_dl);
    texC = _getTexCommon(title->global, 0xF);

    for (i = 0; i < MENUTITLE_TLT_COUNT; i++) {
        s32 j = INC_WRAP(title->current + i, MENUTITLE_TLT_COUNT);
        SMenuItem *item;

        if (title->titleNo[j] < 0) {
            continue;
        }

        item = &title->miBase[j];
        if (item->color[3] == 1.0f) {
            gDPSetRenderMode(gfx++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
        } else {
            gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
        }
        menuItem_drawItem(&title->miBase[j], &gfx, texC, 0, 0xC, title->titleNo[j]);
    }

    *gfxP = gfx;
}

/**
 * Original name: _menuCursor_cursor_4_pattern
 */
const s32 _menuCursor_cursor_4_pattern[] = {
    0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0,
};

/**
 * Original name: menuCursor_setFingerPos
 */
void menuCursor_setFingerPos(MenuCursor *cursor, s32 x, s32 y) {
    SMenuItem *item = &cursor->miFinger;

    item->transFunc = transFunc_finger;
    item->transStep = 1.0f / 32.0f;
    menuItem_setTransHi(item, x, y);
    menuItem_setTransLow(item, x - 8, y);
}

/**
 * Original name: menuCursor_setPlayerPos
 */
void menuCursor_setPlayerPos(MenuCursor *cursor, s32 x, s32 y) {
    menuItem_setTransHi(&cursor->miPlayer, x, y);
    menuItem_setTransLow(&cursor->miPlayer, x, y);
}

/**
 * Original name: _color_1040
 */
const f32 _color_1040[][3] = {
    { 1.0f, 0.3f, 0.3f },
    { 0.3f, 0.3f, 1.0f },
    { 1.0f, 1.0f, 0.0f },
    { 0.0f, 1.0f, 0.0f },
};

/**
 * Original name: menuCursor_init2
 */
void menuCursor_init2(MenuCursor *cursor, struct_watchMenu *global, CursorType type, s32 playerCount, s32 cpuCount,
                      s32 playerNo, s32 x, s32 y, s32 w, s32 h) {
    SMenuItem *item;
    s32 i;

    if ((type == CURSOR_ITEM) || (type == CURSOR_PANEL)) {
        type = CURSOR_THICK;
    }

    cursor->global = global;
    cursor->type = type;
    cursor->playerCount = playerCount;
    cursor->cpuCount = cpuCount;
    cursor->playerNo = playerNo;
    cursor->size[0] = w;
    cursor->size[1] = h;

    cursor->flags.cursor = true;
    cursor->flags.finger = false;
    cursor->flags.player = false;
    cursor->flags.blink = true;

    menuItem_init(&cursor->miBase, x, y);

    item = &cursor->miCursor;
    menuItem_init(item, 0, 0);
    menuItem_setColor_cursor2(item, _color_1040[playerNo % ARRAY_COUNTU(_color_1040)][0],
                              _color_1040[playerNo % ARRAY_COUNTU(_color_1040)][1],
                              _color_1040[playerNo % ARRAY_COUNTU(_color_1040)][2]);
    if (type == CURSOR_THICK) {
        for (i = 0; i < ARRAY_COUNTU(item->colorRange[0]); i++) {
            item->colorRange[0][i] = item->colorRange[1][i];
        }
    }

    menuItem_init(&cursor->miFinger, 0, 0);
    menuCursor_setFingerPos(cursor, -20, h - 14);

    menuItem_init(&cursor->miPlayer, 0, 0);
    menuCursor_setPlayerPos(cursor, -16, h - 22);
}

/**
 * Original name: menuCursor_init
 */
void menuCursor_init(MenuCursor *cursor, struct_watchMenu *global, CursorType type, s32 playerNo, s32 x, s32 y, s32 w,
                     s32 h) {
    menuCursor_init2(cursor, global, type, 4, 0, playerNo, x, y, w, h);
}

/**
 * Original name: menuCursor_update
 */
void menuCursor_update(MenuCursor *cursor, SMenuItem *parent) {
    SMenuItem *item;
    s32 i;

    menuItem_update(&cursor->miBase, parent);
    item = &cursor->miCursor;
    menuItem_update(item, &cursor->miBase);
    if (!cursor->flags.blink) {
        for (i = 0; i < MENUITEM_COLOR_COUNT; i++) {
            item->color[i] = item->colorRange[1][i] * parent->color[i];
        }
    }

    menuItem_update(&cursor->miFinger, &cursor->miBase);
    menuItem_update(&cursor->miPlayer, &cursor->miBase);
}

/**
 * Original name: _pnts_1106
 */
const s32 _pnts_1106[][8] = {
    { 0, 0, 1, 1, 0, 0, 2, 2 }, { 1, 0, 2, 1, 2, 0, 1, 2 }, { 2, 0, 3, 1, 1, 0, 0, 2 },
    { 0, 1, 1, 2, 0, 2, 2, 1 }, { 1, 1, 2, 2, 2, 2, 1, 1 }, { 2, 1, 3, 2, 1, 2, 0, 1 },
    { 0, 2, 1, 3, 0, 1, 2, 0 }, { 1, 2, 2, 3, 2, 1, 1, 0 }, { 2, 2, 3, 3, 1, 1, 0, 0 },
};

/**
 * Original name: menuCursor_draw1
 */
void menuCursor_draw1(MenuCursor *cursorArr[], s32 count, Gfx **gxfP) {
    Gfx *gfx = *gxfP;
    s32 i;

    gSPDisplayList(gfx++, fade_normal_texture_init_dl);
    gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gDPSetTextureLUT(gfx++, G_TT_NONE);

    for (i = 0; i < CURSOR_TYPE_SUM; i++) {
        s32 j;
        s32 sp6C;
        s32 k;
        bool cached;
        s32 var_s3;

        switch (i) {
            case CURSOR_ITEM:
                k = 8;
                var_s3 = 4;
                break;

            case CURSOR_PANEL:
                k = 6;
                var_s3 = 3;
                break;

            case CURSOR_WINDOW:
                k = 7;
                var_s3 = 0x10;
                break;

            case CURSOR_THICK:
                var_s3 = 0x10;
                sp6C = -1;
                break;

            case CURSOR_NEW_4P:
                k = 9;
                break;

            case CURSOR_NEW_MUSIC:
                k = 0xA;
                break;

            case CURSOR_NEW_SPEED:
                k = 0xB;
                break;

            case CURSOR_NEW_VIRUS_LV_L:
                k = 0xC;
                break;

            case CURSOR_NEW_VIRUS_LV_S:
                k = 0xD;
                break;
        }

        cached = false;

        for (j = 0; j < count; j++) {
            MenuCursor *cursor = cursorArr[j];
            SMenuItem *item = &cursor->miCursor;
            TiTexData *texC;
            s32 px[4];
            s32 py[4];
            s32 tx[3];
            s32 ty[3];
            s32 dx[3];
            s32 size;

            if (!cursor->flags.cursor) {
                continue;
            }

            if ((i != cursor->type) || menuItem_outOfScreen(item, cursor->size[0], cursor->size[1])) {
                continue;
            }

            if (i == CURSOR_THICK) {
                if (cursor->flags.blink) {
                    k = item->colorTime * (ARRAY_COUNT(_menuCursor_cursor_4_pattern) - 1);
                    k = _menuCursor_cursor_4_pattern[k] + 3;
                } else {
                    k = 3;
                }

                if (k != sp6C) {
                    sp6C = k;
                    cached = false;
                }
            }

            if (!cached) {
                texC = _getTexCommon(cursor->global, k);

                gDPLoadTextureBlock_4b(gfx++, texC->texs[TI_TEX_TEX], G_IM_FMT_I, texC->info[TI_INFO_IDX_WIDTH],
                                       texC->info[TI_INFO_IDX_HEIGHT], 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK,
                                       G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
                cached++;
            }

            menuItem_setPrim(item, &gfx);

            if (i == CURSOR_THICK) {
                size = cursor->size[0] + var_s3;
                px[0] = (item->trans[0] * 4.0f) - (f32)(var_s3 * 2);
            } else {
                size = cursor->size[0];
                px[0] = item->trans[0] * 4.0f;
            }

            k = MIN(var_s3, size / 2);

            px[3] = px[0] + (s32)(item->scale[0] * 4.0f * size);
            px[1] = px[0] + (s32)(item->scale[0] * 4.0f * k);
            px[2] = px[3] - (s32)(item->scale[0] * 4.0f * k);

            tx[0] = 0;
            tx[1] = (k - 1) << 5;
            tx[2] = k << 5;

            if (i == CURSOR_THICK) {
                size = cursor->size[1] + var_s3;
                py[0] = (item->trans[1] * 4.0f) - (f32)(var_s3 * 2);
            } else {
                size = cursor->size[1];
                py[0] = item->trans[1] * 4.0f;
            }

            k = MIN(var_s3, size / 2);

            py[3] = py[0] + (s32)(item->scale[1] * 4.0f * size);
            py[1] = py[0] + (s32)(item->scale[1] * 4.0f * k);
            py[2] = py[3] - (s32)(item->scale[1] * 4.0f * k);

            ty[0] = 0;
            ty[1] = (k - 1) << 5;
            ty[2] = k << 5;

            dx[0] = -0x400;
            dx[1] = 0;
            dx[2] = 0x400;

            if (i < CURSOR_NEW_4P) {
                for (k = 0; k < ARRAY_COUNTU(_pnts_1106); k++) {
                    // Cast the const away, needed for matching
                    s32 *pnts = (void *)_pnts_1106[k];

                    gSPScisTextureRectangle(gfx++, px[pnts[0]], py[pnts[1]], px[pnts[2]], py[pnts[3]], G_TX_RENDERTILE,
                                            tx[pnts[4]], ty[pnts[5]], dx[pnts[6]], dx[pnts[7]]);
                }
            } else {
                s32 x0 = item->trans[0];
                s32 y0 = item->trans[1];
                s32 x1 = x0 + texC->info[TI_INFO_IDX_WIDTH];
                s32 y1 = y0 + texC->info[TI_INFO_IDX_HEIGHT];

                gSPScisTextureRectangle(gfx++, x0 << 2, y0 << 2, x1 << 2, y1 << 2, G_TX_RENDERTILE, 0, 0, 1 << 10,
                                        1 << 10);
            }
        }
    }

    *gxfP = gfx;
}

/**
 * Original name: _type_1345
 */
const s32 _type_1345[][4] = {
    { 0, 4, 7, 9 },
    { 0, 1, 5, 8 },
    { 0, 1, 2, 6 },
    { 0, 1, 2, 3 },
};

/**
 * Original name: menuCursor_draw2
 */
void menuCursor_draw2(MenuCursor *cursorArr[], s32 count, Gfx **gxfP) {
    Gfx *gfx = *gxfP;
    MenuCursor *cursor;
    TiTexData *texC;
    TiTexData *texA;
    bool cached;
    s32 i;
    s32 j;

    gSPDisplayList(gfx++, fade_alpha_texture_init_dl);

    cached = false;
    for (i = 0; i < count; i++) {
        cursor = cursorArr[i];

        if (cursor->flags.finger) {
            texC = _getTexCommon(cursor->global, 1);
            texA = _getTexCommon(cursor->global, 0);
            cached += menuItem_drawAlphaTex(&cursor->miFinger, &gfx, texC, texA, cached);
        }
    }

    for (i = 0; cached = 0, i < 0xB; i++) {
        for (j = 0; j < count; j++) {
            s32 k;

            cursor = cursorArr[j];
            if ((cursor->playerNo == 1) && (cursor->playerCount == 1) && (cursor->cpuCount == 1)) {
                k = 10;
            } else {
                k = _type_1345[cursor->playerCount - 1][cursor->playerNo];
            }

            if (!cursor->flags.player || (i != k)) {
                continue;
            }

            texC = _getTexSetup(cursor->global, 8);
            texA = _getTexSetup(cursor->global, 1);
            cached += menuItem_drawAlphaItem(&cursor->miPlayer, &gfx, texC, texA, cached, 0xB, i);
        }
    }

    *gxfP = gfx;
}

/**
 * Original name: menuCursor_draw
 */
void menuCursor_draw(MenuCursor *cursorArr[], s32 count, Gfx **gxfP) {
    menuCursor_draw1(cursorArr, count, gxfP);
    menuCursor_draw2(cursorArr, count, gxfP);
}

/**
 * Original name: menuBottle_init
 */
void menuBottle_init(MenuBottle *bottle, struct_watchMenu *global, s32 x, s32 y) {
    bottle->global = global;
    bottle->level = 0;
    menuItem_init(&bottle->miBase, x, y);
    menuItem_init(&bottle->miVirus, 4, 16);
}

/**
 * Original name: menuBottle_update
 */
void menuBottle_update(MenuBottle *bottle, SMenuItem *parent) {
    menuItem_update(&bottle->miBase, parent);
    menuItem_update(&bottle->miVirus, &bottle->miBase);
}

// bitwise, maybe macroify?
/**
 * Original name: cap_pos_1442
 */
const u16 cap_pos_1442[0x16][0xD] = {
    { 0x0000, 0x0000, 0x0000, 0x0001, 0x0000, 0x0000, 0x0000, 0x0030, 0x0000, 0x1000, 0x0000, 0x0000, 0x0002 },
    { 0x0000, 0x0000, 0x0000, 0x0000, 0x00A0, 0x0040, 0x0100, 0x0000, 0x0000, 0x0300, 0x4002, 0x0C00, 0x0000 },
    { 0x0000, 0x0000, 0x0000, 0x0000, 0x0801, 0x00C0, 0x0000, 0x002C, 0x0010, 0x4000, 0x0C00, 0x2020, 0xC001 },
    { 0x0000, 0x0000, 0x0000, 0x8E03, 0x41C0, 0x0000, 0x0018, 0x010B, 0x0C00, 0x0004, 0x4000, 0x0020, 0x0000 },
    { 0x0000, 0x0000, 0x0000, 0x0401, 0x00B0, 0x0080, 0x0318, 0x0010, 0x0000, 0x6300, 0xC803, 0x1C20, 0x8001 },
    { 0x0000, 0x0000, 0x0000, 0x2410, 0x000C, 0x3803, 0x8058, 0x0006, 0xC434, 0x0803, 0x0002, 0x3010, 0x0B00 },
    { 0x0000, 0x0000, 0x0000, 0xC701, 0xCB60, 0x0080, 0x0217, 0x0310, 0x0030, 0x420C, 0xC802, 0x1810, 0x8001 },
    { 0x0000, 0x0000, 0x0000, 0x830A, 0x0A02, 0x50C1, 0x00C4, 0x0F00, 0x6313, 0xC201, 0x00C1, 0x1084, 0x8138 },
    { 0x0000, 0x0000, 0x0000, 0xF631, 0x8060, 0x0C80, 0xC2D6, 0x001F, 0x0C2C, 0x4E08, 0x8402, 0x1810, 0x4C01 },
    { 0x0000, 0x0000, 0x0000, 0xB124, 0x0DA0, 0x004D, 0x3070, 0x24C3, 0x9C09, 0x412C, 0x0360, 0x10B2, 0x2D8C },
    { 0x0000, 0x0000, 0x0000, 0x860D, 0x8E4F, 0x3C43, 0xC096, 0xC212, 0x0828, 0x490B, 0x8403, 0x141C, 0x4B0D },
    { 0x0000, 0x0000, 0x0000, 0x6008, 0xC90A, 0xF834, 0x4C5C, 0x178E, 0xD8C3, 0x20C8, 0xB252, 0xC361, 0x1427 },
    { 0x0000, 0x0000, 0x0000, 0xB63D, 0x4D4B, 0x2843, 0x8094, 0x8F1A, 0xF82B, 0x4934, 0x04C2, 0x141C, 0x7A3D },
    { 0x0000, 0x0000, 0x0000, 0x323A, 0x634D, 0x5B2F, 0xC424, 0x25C4, 0x9C79, 0xF282, 0x7182, 0xA16F, 0x270D },
    { 0x0000, 0x0000, 0x0000, 0xA539, 0x497A, 0x084F, 0xB094, 0xAF12, 0x6F2F, 0x7934, 0xC4C2, 0x17DB, 0x7A39 },
    { 0x0000, 0x0000, 0xDADA, 0x32CA, 0x270D, 0x5C3D, 0xC027, 0x2494, 0x18F9, 0xF86B, 0x6142, 0x61F2, 0xD63D },
    { 0x0000, 0x0000, 0x5F96, 0xA529, 0xC978, 0xF84C, 0xB094, 0xAF12, 0x6F2C, 0x7934, 0xC4B2, 0x17DB, 0x7AC9 },
    { 0x0000, 0x4BD8, 0xF6DA, 0x3DA5, 0x132C, 0x28D2, 0xC213, 0xD78F, 0x1BE4, 0xA17A, 0xA142, 0x52D3, 0xD63D },
    { 0x0000, 0x616B, 0x5F96, 0xD601, 0xC96B, 0xAC4E, 0xB094, 0xFAD3, 0x6F2B, 0x4D06, 0xC4B2, 0xD7DB, 0x72C9 },
    { 0x8524, 0xA16B, 0x5F9E, 0xD601, 0xC96B, 0xAC4E, 0xB094, 0x3AD3, 0x6F2F, 0x4D36, 0xC4B2, 0x17DB, 0x72C9 },
    { 0xB524, 0x616B, 0x5F9E, 0x1601, 0xF96B, 0xAC7E, 0x8094, 0xCAD3, 0x6F2B, 0x7D36, 0xF4BE, 0xD7DB, 0x4A09 },
    { 0xB536, 0x7D6B, 0x5F9F, 0x960D, 0xF97A, 0x6C7A, 0x8094, 0x829C, 0x6F2B, 0x7D25, 0xF4BE, 0xD7DA, 0x4AC9 },
};

/**
 * Original name: menuBottle_draw
 */
void menuBottle_draw(MenuBottle *bottle, Gfx **gxfP) {
    Gfx *gfx = *gxfP;
    s32 a3;

    gSPDisplayList(gfx++, fade_normal_texture_init_dl);

    //! @bug: reads unset $a2 register (us) / $a3 register (cn) variable
    if (a3 != 0) {
        SMenuItem *item = &bottle->miVirus;
        TiTexData *tex = _getTexLevel(bottle->global, 0);
        s32 ty;
        s32 i;

        gDPLoadTLUT_pal16(gfx++, 0, tex->texs[TI_TEX_TLUT]);
        gDPLoadTextureBlock_4b(gfx++, tex->texs[TI_TEX_TEX], G_IM_FMT_CI, tex->info[TI_INFO_IDX_WIDTH],
                               tex->info[TI_INFO_IDX_HEIGHT], 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK,
                               G_TX_NOLOD, G_TX_NOLOD);

        menuItem_setPrim(item, &gfx);

        ty = 0;
        for (i = 1; i < 4; i++) {
            const u16 *caps = &cap_pos_1442[bottle->level][2];
            s32 py = (s32)item->trans[1] * 4;
            s32 j;

            for (j = 2; j < ARRAY_COUNT(cap_pos_1442[bottle->level]); j++) {
                s32 px = (s32)item->trans[0] * 4;
                s32 cap = *caps;
                s32 k;

                for (k = 7; k >= 0; k--) {
                    if (((cap >> (k * 2)) & 3) == i) {
                        gSPScisTextureRectangle(gfx++, px, py, px + 0x14, py + 0x14, G_TX_RENDERTILE, 0, ty, 1 << 10,
                                                1 << 10);
                    }
                    px += 0x14;
                }

                py += 0x14;
                caps++;
            }

            ty += 0xA0;
        }
    }

    *gxfP = gfx;
}

/**
 * Original name: _lvGauge_step
 */
const f32 _lvGauge_step[] = {
    3.5f,
    3.5f,
    4.0f,
};

// TODO: make enum to index this array?
/**
 * Original name: _size_1542
 */
const s32 _size_1542[][2] = {
    { 6, 10 },
    { 6, 16 },
    { 7, 16 },
};
/**
 * Original name: _type_1543
 */
const CursorType _type_1543[] = {
    CURSOR_NEW_VIRUS_LV_S,
    CURSOR_NEW_VIRUS_LV_L,
    CURSOR_NEW_VIRUS_LV_L,
};

/**
 * Original name: menuLvGauge_init
 */
void menuLvGauge_init(SMenuLvGauge *lvGauge, struct_watchMenu *global, s32 size, s32 playerNo, s32 level, s32 x,
                      s32 y) {
    lvGauge->global = global;
    lvGauge->size = size;
    lvGauge->levelMax = 20;
    lvGauge->level = level;
    menuItem_init(&lvGauge->miBase, x, y);
    menuCursor_init(&lvGauge->cursor, global, _type_1543[size], playerNo, -2, -2, _size_1542[size][0],
                    _size_1542[size][1]);
}

/**
 * Original name: menuLvGauge_input
 */
void menuLvGauge_input(SMenuLvGauge *lvGauge, s32 playerNo) {
    u32 rep = _getKeyRep(lvGauge->global, playerNo);
    s32 vec = 0;
    s32 level;

    if (rep & L_JPAD) {
        vec--;
    }
    if (rep & R_JPAD) {
        vec++;
    }

    level = CLAMP(lvGauge->level + vec, 0, lvGauge->levelMax);

    if (level != lvGauge->level) {
        dm_snd_play(SND_INDEX_63);
        lvGauge->level = level;
    }
}

/**
 * Original name: menuLvGauge_update
 */
void menuLvGauge_update(SMenuLvGauge *lvGauge, SMenuItem *parent) {
    SMenuItem *item;

    menuItem_update(&lvGauge->miBase, parent);

    item = &lvGauge->cursor.miBase;
    item->transRange[1][0] = item->transRange[0][0] + _lvGauge_step[lvGauge->size] * lvGauge->level;

    menuCursor_update(&lvGauge->cursor, &lvGauge->miBase);
}

/**
 * Original name: menuLvGauge_draw1
 */
void menuLvGauge_draw1(SMenuLvGauge *lvGaugeArr[], s32 count, Gfx **gxfP) {
    Gfx *gfx = *gxfP;
    s32 i;

    gSPDisplayList(gfx++, fade_fillrect_init_dl);

    for (i = 0; i < count; i++) {
        SMenuLvGauge *lvGauge = lvGaugeArr[i];
        s32 x = lvGauge->miBase.trans[0] + _lvGauge_step[lvGauge->size] * (lvGauge->level + 1);
        s32 y = lvGauge->miBase.trans[1];
        s32 width = (20 - lvGauge->level) * _lvGauge_step[lvGauge->size];
        s32 height = lvGauge->cursor.size[1] - 3;

        if (lvGauge->size == 0) {
            y--;
            height++;
        }

        gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, 160);
        gDPScisFillRectangle(gfx++, x, y, x + width, y + height);

        if (lvGauge->levelMax > 20) {
            x = lvGauge->miBase.trans[0] + _lvGauge_step[lvGauge->size] * 21.0f;
            y = lvGauge->miBase.trans[1] - 1.0f;
            width = (lvGauge->levelMax - MAX(20, lvGauge->level)) * _lvGauge_step[lvGauge->size];
            height = lvGauge->cursor.size[1] - 1;

            gDPScisFillRectangle(gfx++, x, y, x + width, y + height);
        }
    }

    *gxfP = gfx;
}

/**
 * Original name: menuLvGauge_draw2
 */
void menuLvGauge_draw2(SMenuLvGauge *lvGaugeArr[], s32 count, Gfx **gxfP) {
    Gfx *gfx = *gxfP;
    MenuCursor *cursorArr[count];
    s32 i;

    for (i = 0; i < count; i++) {
        cursorArr[i] = &lvGaugeArr[i]->cursor;
    }

    menuCursor_draw(cursorArr, count, &gfx);

    *gxfP = gfx;
}

/**
 * Original name: menuLvGauge_draw
 */
void menuLvGauge_draw(SMenuLvGauge *lvGaugeArr[], s32 count, Gfx **gfxP) {
    menuLvGauge_draw1(lvGaugeArr, count, gfxP);
    menuLvGauge_draw2(lvGaugeArr, count, gfxP);
}

/**
 * Original name: menuYN_setFade
 */
void menuYN_setFade(MenuYN *yn, s32 dir, f32 time) {
    SMenuItem *item = &yn->miBase;

    menuItem_setColorDir(item, dir);
    item->colorTime = time;
}

void menuYN_setFadeDir(MenuYN *yn, s32 dir) {
    menuYN_setFade(yn, dir, yn->miBase.colorTime);
}

/**
 * Original name: _yn_1691
 */
const s32 _yn_1691[][2] = {
    { 14, 12 },
    { 14, 36 },
};

/**
 * Original name: menuYN_init
 */
void menuYN_init(MenuYN *yn, struct_watchMenu *global, s32 x, s32 y) {
    SMenuItem *item;
    s32 i;
    f32 a2;

    yn->global = global;
    yn->select = 0;
    menuItem_init(&yn->miBase, x, y);
    menuItem_setColor_fade(&yn->miBase);

    for (i = 0; i < ARRAY_COUNTU(yn->miYN); i++) {
        menuItem_init(&yn->miYN[i], _yn_1691[i][0], _yn_1691[i][1]);
    }

    menuCursor_init(&yn->cursor, global, CURSOR_ITEM, 0, -4, -4, 60, 20);
    yn->cursor.flags.finger = true;
    menuCursor_init(&yn->window, global, CURSOR_WINDOW, 0, 0, 0, 80, 60);

    item = &yn->window.miCursor;
    item->colorFunc = colorFunc_curve;

    a2 = 0.0f;

    item->colorRange[1][0] = a2;
    item->colorRange[0][0] = a2;
    item->colorRange[1][1] = a2;
    item->colorRange[0][1] = a2;
    item->colorRange[1][2] = a2;
    item->colorRange[0][2] = a2;
    item->colorRange[0][3] = a2;
    item->colorRange[1][3] = 32.0f / 51.0f;
    menuYN_setFade(yn, -1, a2);
}

/**
 * Original name: menuYN_input
 */
bool menuYN_input(MenuYN *yn, s32 playerNo) {
    u32 trg = _getKeyTrg(yn->global, playerNo);
    s32 sel = yn->select;

    if ((yn->miBase.colorStep < 0.0f) || (yn->miBase.colorTime < 1.0f)) {
        return false;
    }

    if (trg & U_JPAD) {
        sel--;
    }
    if (trg & D_JPAD) {
        sel++;
    }

    sel = WrapI(0, 2, sel);
    if (sel != yn->select) {
        yn->select = sel;
        dm_snd_play(SND_INDEX_64);
    }

    return true;
}

/**
 * Original name: menuYN_update
 */
void menuYN_update(MenuYN *yn, SMenuItem *parent) {
    menuItem_update(&yn->miBase, parent);
    menuItem_updateN(yn->miYN, ARRAY_COUNT(yn->miYN), &yn->miBase);
    menuCursor_update(&yn->cursor, &yn->miYN[yn->select]);
    menuCursor_update(&yn->window, &yn->miBase);
}

#include "main_menu_yn.msg.inc"

/**
 * Original name: menuYN_draw
 */
void menuYN_draw(MenuYN *yn, Gfx **gfxP) {
    SMenuItem *item = &yn->miBase;
    Gfx *gfx = *gfxP;
    MenuCursor *cursor;
    s32 i;

    if (menuItem_outOfScreen(item, 80, 60)) {
        return;
    }

    cursor = &yn->window;
    menuCursor_draw(&cursor, 1, &gfx);

    gSPDisplayList(gfx++, fade_intensity_texture_init_dl);
    gDPSetTextureFilter(gfx++, G_TF_BILERP);

    gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, item->color[3] * 255.0f);

    for (i = 0; i < ARRAY_COUNTU(_yn_1767); i++) {
        f32 x;
        s32 j;

        item = &yn->miYN[i];
        x = item->trans[0];

#if VERSION_US || VERSION_GW
        //! @bug: should be checking for nil character instead
        for (j = 0; j < _yn_1767[i][j]; j += 2)
#elif VERSION_CN
        for (j = 0; _yn_1767[i][j] != '\0'; j += 2)
#else
#error ""
#endif
        {
            fontXX_draw(&gfx, x, item->trans[1], 12.0f, 12.0f, &_yn_1767[i][j]);
            x += 20.0f;
        }
    }

    cursor = &yn->cursor;
    menuCursor_draw(&cursor, 1, &gfx);

    *gfxP = gfx;
}

/**
 * Original name: menuMes_setFade
 */
void menuMes_setFade(MenuMes *mes, s32 dir, f32 time) {
    menuItem_setColorDir(&mes->miBase, dir);
    mes->miBase.colorTime = time;
}

/**
 * Original name: menuMes_setFadeDir
 */
void menuMes_setFadeDir(MenuMes *mes, s32 dir) {
    menuMes_setFade(mes, dir, mes->miBase.colorTime);
}

/**
 * Original name: menuMes_init
 */
void menuMes_init(MenuMes *mes, struct_watchMenu *watchMenuRef, void **heapP, s32 col, s32 row, s32 x, s32 y) {
    MessageWnd *msgWnd;
    SMenuItem *item;
    void *heap = *heapP;
    f32 a2;

    mes->global = watchMenuRef;

    menuItem_init(&mes->miBase, x, y);
    menuItem_setColor_fade(&mes->miBase);

    msgWnd_init(&mes->msgWnd, heapP, col, row, x, y);

    //! FAKE: ?
    msgWnd = &mes->msgWnd;

    mes->msgWnd.centering = true;
    msgWnd->fntH = 0xC;
    mes->msgWnd.fntW = 0xC;
    mes->msgWnd.colStep = 6;
    mes->msgWnd.rowStep = 0xE;
    menuCursor_init(&mes->window, watchMenuRef, CURSOR_WINDOW, 0, -0x10, -0x10, mes->msgWnd.colStep * col * 2 + 0x20,
                    mes->msgWnd.rowStep * row + 0x20);

    item = &mes->window.miCursor;
    item->colorFunc = colorFunc_curve;

    a2 = 0.0f;
    item->colorRange[1][0] = a2;
    item->colorRange[0][0] = a2;
    item->colorRange[1][1] = a2;
    item->colorRange[0][1] = a2;
    item->colorRange[1][2] = a2;
    item->colorRange[0][2] = a2;
    item->colorRange[0][3] = a2;
    item->colorRange[1][3] = 0.627451f;
    menuMes_setFade(mes, -1, a2);

    *heapP = heap;
}

/**
 * Original name: menuMes_setStr
 */
void menuMes_setStr(MenuMes *mes, const char *str) {
    msgWnd_clear(&mes->msgWnd);
    msgWnd_addStr(&mes->msgWnd, str);
    msgWnd_skip(&mes->msgWnd);
}

/**
 * Original name: menuMes_update
 */
void menuMes_update(MenuMes *mes, SMenuItem *parent) {
    menuItem_update(&mes->miBase, parent);
    mes->msgWnd.posX = mes->miBase.trans[0];
    mes->msgWnd.posY = mes->miBase.trans[1];
    mes->msgWnd.alpha = mes->miBase.color[3] * 255.0f;
    msgWnd_update(&mes->msgWnd);
    menuCursor_update(&mes->window, &mes->miBase);
}

/**
 * Original name: menuMes_draw
 */
void menuMes_draw(MenuMes *mes, Gfx **gfxP) {
    MenuCursor *cursor;
    Gfx *gfx;
    MessageWnd *msgWnd = &mes->msgWnd;

    gfx = *gfxP;
    if (menuItem_outOfScreen(&mes->miBase, (msgWnd->colSize - 2) * msgWnd->colStep + msgWnd->fntW + 0xC,
                             (msgWnd->rowSize - 1) * msgWnd->rowStep + msgWnd->fntH + 0xC)) {
        return;
    }

    cursor = &mes->window;
    menuCursor_draw(&cursor, 1, &gfx);
    msgWnd_draw(msgWnd, &gfx);

    *gfxP = gfx;
}

/**
 * Original name: menuSpeedAsk_init
 */
void menuSpeedAsk_init(MenuSpeedAsk *speedAsk, struct_watchMenu *global, s32 size, s32 speed, s32 x, s32 y) {
    speedAsk->global = global;
    speedAsk->size = size;
    speedAsk->select = speed;
    menuItem_init(&speedAsk->miBase, x, y);
}

/**
 * Original name: menuSpeedAsk_update
 */
void menuSpeedAsk_update(MenuSpeedAsk *speedAsk, SMenuItem *parent) {
    menuItem_update(&speedAsk->miBase, parent);
}

// TODO: Make enum to index this?
/**
 * Original name: _tex_1865
 */
const s32 _tex_1865[][2] = {
    { 13, 6 },
    { 12, 5 },
    { 10, 3 },
    { 9, 2 },
};

/**
 * Original name: _row_1866
 */
const s32 _row_1866[] = {
    3,
    3,
    3,
    4,
};

/**
 * Original name: menuSpeedAsk_draw
 */
void menuSpeedAsk_draw(MenuSpeedAsk *speedAskArr[], s32 count, Gfx **gxfP) {
    Gfx *gfx = *gxfP;
    s32 i;

    gSPDisplayList(gfx++, fade_alpha_texture_init_dl);

    for (i = 0; i < ARRAY_COUNT(_row_1866); i++) {
        s32 j;
        bool cached;

        for (j = 0, cached = 0; j < _row_1866[i]; j++, cached = 0) {
            s32 k;

            for (k = 0; k < count; k++) {
                MenuSpeedAsk *speedAsk = speedAskArr[k];

                if ((i == speedAsk->size) && (j == speedAsk->select)) {
                    TiTexData *texC = _getTexSetup(speedAsk->global, _tex_1865[speedAsk->size][0]);
                    TiTexData *texA = _getTexSetup(speedAsk->global, _tex_1865[speedAsk->size][1]);

                    cached += menuItem_drawAlphaItem(&speedAsk->miBase, &gfx, texC, texA, cached, _row_1866[i], j);
                }
            }
        }
    }

    *gxfP = gfx;
}

// TODO: enum to index this?
/**
 * Original name: _type_1949
 */
CursorType _type_1949[] = {
    CURSOR_NEW_MUSIC,
    CURSOR_NEW_SPEED,
    CURSOR_NEW_MUSIC,
    CURSOR_NEW_SPEED,
};

// TODO: enum to index this?
/**
 * Original name: _size_1948
 */
const s32 _size_1948[][2] = {
    { 36, 16 },
    { 36, 24 },
    { 36, 16 },
    { 36, 24 },
};

// TODO: enum to index this?
/**
 * Original name: _pos_1959
 */
const s8 _pos_1959[][2] = {
    { -3, -2 },
    { -3, -3 },
    { -3, -2 },
    { -3, -3 },
};

/**
 * Original name: menuSpeedItem_init
 */
void menuSpeedItem_init(MenuSpeedItem *speedItem, struct_watchMenu *global, s32 size, s32 playerNo, s32 speed, s32 x,
                        s32 y, s32 step) {
    s32 i;

    speedItem->global = global;
    speedItem->size = size;
    speedItem->select = speed;
    speedItem->flags.blink = true;
    speedItem->flags.special = false;
    menuItem_init(&speedItem->miBase, x, y);

    for (i = 0; i < ARRAY_COUNTU(speedItem->miLabel); i++) {
        menuItem_init(&speedItem->miLabel[i], step * i, 0);
    }

    for (i = 0; i < MENUSPEEDITEM_UNK_LEN; i++) {
        SMenuItem *miMask = &speedItem->miMask[i];
        s32 j;

        menuItem_init(miMask, _pos_1959[size][0], _pos_1959[size][1]);

        miMask->colorFunc = colorFunc_cursor;
        miMask->colorStep = 1.0f / 32.0f;

        for (j = 0; j < MENUITEM_UNK_LEN3; j++) {
            s32 k;

            for (k = 0; k < MENUITEM_COLOR_COUNT; k++) {
                miMask->colorRange[j][k] = _gameLvItemColor[i][j][k] * (DOUBLE_LITERAL(1) / 0xFF);
            }
        }
    }

    menuCursor_init(&speedItem->cursor, global, _type_1949[size], playerNo, -1, -1, _size_1948[size][0],
                    _size_1948[size][1]);
}

/**
 * Original name: menuSpeedItem_input
 */
void menuSpeedItem_input(MenuSpeedItem *speedItem, s32 playerNo) {
    u32 rep = _getKeyRep(speedItem->global, playerNo);
    s32 select;
    s32 vec;

    vec = 0;
    if (rep & L_JPAD) {
        vec--;
    }
    if (rep & R_JPAD) {
        vec++;
    }

    select = CLAMP(speedItem->select + vec, 0, ARRAY_COUNTU(speedItem->miLabel) - 1);
    if (select != speedItem->select) {
        dm_snd_play(SND_INDEX_63);
        speedItem->select = select;
    }
}

/**
 * Original name: menuSpeedItem_update
 */
void menuSpeedItem_update(MenuSpeedItem *speedItem, SMenuItem *parent) {
    s32 i;

    menuItem_update(&speedItem->miBase, parent);
    menuItem_updateN(speedItem->miLabel, ARRAY_COUNT(speedItem->miLabel), &speedItem->miBase);

    for (i = 0; i < MENUSPEEDITEM_UNK_LEN; i++) {
        SMenuItem *miMask = &speedItem->miMask[i];
        f32 *color;
        s32 j;

        menuItem_update(miMask, &speedItem->miLabel[i]);

        if (i == speedItem->select) {
            if (!speedItem->flags.blink) {
                color = miMask->colorRange[1];
            } else {
                color = NULL;
            }

            for (j = 0; j < MENUITEM_COLOR_COUNT; j++) {
                miMask->colorRange[0][j] = _gameLvItemColor[i][1][j] * (DOUBLE_LITERAL(1) / 0x1FF);
            }
        } else {
            color = miMask->colorRange[0];

            for (j = 0; j < MENUITEM_COLOR_COUNT; j++) {
                miMask->colorRange[0][j] = _gameLvItemColor[i][0][j] * (DOUBLE_LITERAL(1) / 0xFF);
            }
        }

        if (color != NULL) {
            for (j = 0; j < MENUITEM_COLOR_COUNT; j++) {
                miMask->color[j] = color[j] * parent->color[j];
            }
        }
    }

    menuCursor_update(&speedItem->cursor, &speedItem->miLabel[speedItem->select]);
}

/**
 * Original name: menuSpeedItem_draw1
 */
void menuSpeedItem_draw1(MenuSpeedItem *speedItemArr[], s32 count, Gfx **gfxP) {
    Gfx *gfx = *gfxP;
    TiTexData *texC;
    MenuSpeedItem *speedItem;
    SMenuItem *item;
    bool cached;
    s32 index;
    s32 i;
    s32 j;

    gSPDisplayList(gfx++, fade_normal_texture_init_dl);

    cached = false;
    for (index = 0; index < count; index++) {
        speedItem = speedItemArr[index];
        item = &speedItem->miLabel[2];

        if ((speedItem->size == 3) && speedItem->flags.special) {
            texC = _getTexSetup(speedItem->global, 15);
            cached += menuItem_drawTex(item, &gfx, texC, cached);
        }
    }

    gSPDisplayList(gfx++, fade_intensity_texture_init_dl);

    cached = false;
    for (index = 0; index < count; index++) {
        speedItem = speedItemArr[index];
        item = &speedItem->miMask[2];

        if ((speedItem->size == 3) && speedItem->flags.special) {
            texC = _getTexSetup(speedItem->global, 23);
            cached += menuItem_drawTex(item, &gfx, texC, cached);
        }
    }

    for (i = 0; i < 4; i++) {
        for (j = 0; j < ARRAY_COUNTU(speedItem->miMask); j++) {
            cached = 0;
            if ((j == 2) && (speedItem->size == 3) && speedItem->flags.special) {
                continue;
            }

            for (index = 0; index < count; index++) {
                speedItem = speedItemArr[index];
                item = &speedItem->miMask[j];

                if (speedItem->size == i) {
                    switch (speedItem->size) {
                        case 0:
                            texC = _getTexP4(speedItem->global, j + 6);
                            break;

                        case 1:
                            texC = _getTexSetup(speedItem->global, j + 24);
                            break;

                        case 2:
                            texC = _getTexP4(speedItem->global, j + 3);
                            break;

                        case 3:
                            texC = _getTexSetup(speedItem->global, j + 20);
                            break;
                    }

                    cached += menuItem_drawTex(item, &gfx, texC, cached);
                }
            }
        }
    }

    *gfxP = gfx;
}

/**
 * Original name: menuSpeedItem_draw2
 */
void menuSpeedItem_draw2(MenuSpeedItem *speedItemArr[], s32 count, Gfx **gxfP) {
    Gfx *gfx = *gxfP;
    MenuCursor *cursorArr[count];
    s32 i;

    for (i = 0; i < count; i++) {
        cursorArr[i] = &speedItemArr[i]->cursor;
    }

    menuCursor_draw2(cursorArr, count, &gfx);

    *gxfP = gfx;
}

/**
 * Original name: menuSpeedItem_draw
 */
void menuSpeedItem_draw(MenuSpeedItem *speedItemArr[], s32 count, Gfx **gfxP) {
    menuSpeedItem_draw1(speedItemArr, count, gfxP);
    menuSpeedItem_draw2(speedItemArr, count, gfxP);
}

/**
 * Original name: menuMusicItem_init
 */
void menuMusicItem_init(MenuMusicItem *musicItem, struct_watchMenu *global, s32 musicNo, s32 x, s32 y) {
    s32 i;

    musicItem->global = global;
    musicItem->select = musicNo;
    musicItem->playNo = -1;
    musicItem->flags.blink = true;

    menuItem_init(&musicItem->miBase, x, y);

    for (i = 0; i < ARRAY_COUNTU(musicItem->miLabel); i++) {
        menuItem_init(&musicItem->miLabel[i], 39 * i, 0);
    }

    for (i = 0; i < ARRAY_COUNTU(musicItem->miMask); i++) {
        SMenuItem *item = &musicItem->miMask[i];
        s32 j;

        menuItem_init(item, -2, -2);
        item->colorFunc = colorFunc_cursor;
        item->colorStep = 1.0f / 32.0f;

        for (j = 0; j < MENUITEM_UNK_LEN3; j++) {
            s32 k;

            for (k = 0; k < ARRAY_COUNTU(_musicItemColor[j]); k++) {
                item->colorRange[j][k] = _musicItemColor[j][k] * (DOUBLE_LITERAL(1) / 255);
            }
        }
    }

    menuCursor_init(&musicItem->cursor, global, CURSOR_NEW_MUSIC, 0, -1, -1, 37, 16);
    musicItem->cursor.flags.cursor = false;
}

/**
 * Original name: _seq_2327
 */
const SeqIndex _seq_2327[] = {
    SEQ_INDEX_0,
    SEQ_INDEX_2,
    SEQ_INDEX_4,
    SEQ_INDEX_6,
};

/**
 * Original name: menuMusicItem_input
 */
void menuMusicItem_input(MenuMusicItem *musicItem, s32 playerNo) {
    u32 rep = _getKeyRep(musicItem->global, playerNo);
    s32 vec = 0;
    s32 select;

    if (musicItem->playNo != musicItem->select) {
        if (musicItem->select < ARRAY_COUNTU(_seq_2327)) {
            dm_seq_play_fade(_seq_2327[musicItem->select], 0x14);
        } else {
            dm_seq_stop();
        }
        musicItem->playNo = musicItem->select;
    }

    if (rep & L_JPAD) {
        vec--;
    }
    if (rep & R_JPAD) {
        vec++;
    }

    select = CLAMP(musicItem->select + vec, 0, ARRAY_COUNT(musicItem->miLabel) - 1);
    if (select != musicItem->select) {
        dm_snd_play(SND_INDEX_63);
        musicItem->select = select;
    }
}

/**
 * Original name: menuMusicItem_update
 */
void menuMusicItem_update(MenuMusicItem *musicItem, SMenuItem *parent) {
    s32 i;

    menuItem_update(&musicItem->miBase, parent);
    menuItem_updateN(musicItem->miLabel, ARRAY_COUNT(musicItem->miLabel), &musicItem->miBase);

    for (i = 0; i < MENUMUSICITEM_COUNT; i++) {
        SMenuItem *miMask = &musicItem->miMask[i];
        f32 *color;
        s32 j;

        menuItem_update(miMask, &musicItem->miLabel[i]);
        if (i == musicItem->select) {
            if (!musicItem->flags.blink) {
                color = miMask->colorRange[1];
            } else {
                color = NULL;
            }

            for (j = 0; j < ARRAY_COUNTU(_musicItemColor[1]); j++) {
                miMask->colorRange[0][j] = _musicItemColor[1][j] * (DOUBLE_LITERAL(1) / 0x1FF);
            }
        } else {
            color = miMask->colorRange[0];
            for (j = 0; j < ARRAY_COUNTU(_musicItemColor[0]); j++) {
                miMask->colorRange[0][j] = _musicItemColor[0][j] * (DOUBLE_LITERAL(1) / 0xFF);
            }
        }

        if (color != NULL) {
            for (j = 0; j < MENUITEM_COLOR_COUNT; j++) {
                miMask->color[j] = color[j] * parent->color[j];
            }
        }
    }

    menuCursor_update(&musicItem->cursor, &musicItem->miLabel[musicItem->select]);
}

/**
 * Original name: menuMusicItem_draw1
 */
void menuMusicItem_draw1(MenuMusicItem *musicItemArr[], s32 count, Gfx **gxfP) {
    Gfx *gfx = *gxfP;
    s32 i;
    s32 j;

    gSPDisplayList(gfx++, fade_intensity_texture_init_dl);

    for (j = 0; j < ARRAY_COUNTU((*musicItemArr)->miMask); j++) {
        bool cache = false;

        for (i = 0; i < count; i++) {
            MenuMusicItem *musicItem = musicItemArr[i];
            SMenuItem *miMask = &musicItem->miMask[j];

            cache += menuItem_drawTex(miMask, &gfx, _getTexSetup(musicItem->global, j + 0x1B), cache);
        }
    }

    *gxfP = gfx;
}

/**
 * Original name: menuMusicItem_draw2
 */
void menuMusicItem_draw2(MenuMusicItem *musicItemArr[], s32 count, Gfx **gxfP) {
    Gfx *gfx = *gxfP;
    MenuCursor *arr[count];
    s32 i;

    for (i = 0; i < count; i++) {
        MenuMusicItem *musicItem = musicItemArr[i];

        arr[i] = &musicItem->cursor;
    }

    menuCursor_draw(arr, count, &gfx);

    *gxfP = gfx;
}

/**
 * Original name: menuMusicItem_draw
 */
void menuMusicItem_draw(MenuMusicItem *musicItemArr[], s32 count, Gfx **gfxP) {
    menuMusicItem_draw1(musicItemArr, count, gfxP);
    menuMusicItem_draw2(musicItemArr, count, gfxP);
}

/**
 * Original name: menuNumber_init
 */
void menuNumber_init(MenuNumber *number, struct_watchMenu *global, s32 size, s32 column, s32 n, s32 x, s32 y) {
    number->global = global;
    number->size = size;
    number->column = column;
    number->number = n;
    number->flags.zero = true;
    bzero(number->columns, ARRAY_COUNTU(number->columns) * sizeof(char));
    menuItem_init(&number->miBase, x, y);
}

/**
 * Original name: menuNumber_update
 */
void menuNumber_update(MenuNumber *number, SMenuItem *parent) {
    s32 n = number->number;
    s32 i;

    for (i = number->column - 1; i >= 0; i--) {
        number->columns[i] = n % 10;
        n /= 10;
    }
    menuItem_update(&number->miBase, parent);
}

/**
 * Original name: _tbl_2516
 */
const s32 _tbl_2516[] = {
    9, 0, 1, 2, 3, 4, 5, 6, 7, 8,
};

/**
 * Original name: _step_2517
 */
const s32 _step_2517[] = {
    10,
    14,
};

/**
 * Original name: menuNumber_draw
 */
void menuNumber_draw(MenuNumber *numberArr[], s32 count, Gfx **gxfP) {
    Gfx *gfx = *gxfP;
    TiTexData *texC;
    TiTexData *texA;
    s32 j;
    s32 k;
    s32 i;
    s32 s;
    s32 width;
    s32 height;

    gSPDisplayList(gfx++, fade_alpha_texture_init_dl);

    for (i = 0; i < ARRAY_COUNT(_step_2517); i++) {
        bool cached;

        for (j = 0; cached = 0, j < ARRAY_COUNT(_tbl_2516); j++) {
            for (k = 0; k < count; k++) {
                MenuNumber *number = numberArr[k];
                SMenuItem *item = &number->miBase;
                bool zero = number->flags.zero;

                switch (number->size) {
                    case 0x0:
                        texC = _getTexSetup(number->global, 7);
                        texA = _getTexSetup(number->global, 0);
                        break;

                    case 0x1:
                        texC = _getTexGameAl(number->global, 0xD);
                        texA = _getTexGameAl(number->global, 0x12);
                        break;
                }

                width = MIN(texC->info[TI_INFO_IDX_WIDTH], texA->info[TI_INFO_IDX_WIDTH]);
                height = MIN(texC->info[TI_INFO_IDX_HEIGHT], texA->info[TI_INFO_IDX_HEIGHT]) / 10;

                if (menuItem_outOfScreen(item, width * number->column, height)) {
                    continue;
                }

                menuItem_setPrim(item, &gfx);

                for (s = 0; s < number->column; s++) {
                    if (!zero && (number->columns[s] == 0)) {
                        continue;
                    }

                    zero = true;
                    if ((i != number->size) || (j != number->columns[s])) {
                        continue;
                    }

                    tiStretchAlphaTexItem(&gfx, texC, texA, cached++, 0xA, _tbl_2516[j],
                                          item->trans[0] + (_step_2517[i] * item->scale[0] * s), item->trans[1],
                                          width * item->scale[0], height * item->scale[1]);
                }
            }
        }
    }

    *gxfP = gfx;
}

/**
 * Original name: menuComLvPanel_setFade
 */
void menuComLvPanel_setFade(MenuComLvPanel *comLvPanel, s32 dir, f32 time) {
    SMenuItem *item = &comLvPanel->miBase;

    menuItem_setColor_fade(item);
    menuItem_setColorDir(item, dir);
    item->colorTime = time;
}

/**
 * Original name: menuComLvPanel_setFadeDir
 */
void menuComLvPanel_setFadeDir(MenuComLvPanel *comLvPanel, s32 dir) {
    menuComLvPanel_setFade(comLvPanel, dir, comLvPanel->miBase.colorTime);
}

/**
 * Original name: menuComLvPanel_setPos
 */
void menuComLvPanel_setPos(MenuComLvPanel *comLvPanel, s32 x, s32 y) {
    SMenuItem *item = &comLvPanel->miBase;

    item->transRange[0][0] = item->transRange[1][0] = x;
    item->transRange[0][1] = item->transRange[1][1] = y;
}

/**
 * Original name: menuComLvPanel_init
 */
void menuComLvPanel_init(MenuComLvPanel *comLvPanel, struct_watchMenu *global, s32 level, s32 x, s32 y) {
    comLvPanel->global = global;
    comLvPanel->level = level;

    menuItem_init(&comLvPanel->miBase, x, y);
    menuItem_init(&comLvPanel->miStar, 0, 10);
}

/**
 * Original name: menuComLvPanel_update
 */
void menuComLvPanel_update(MenuComLvPanel *comLvPanel, SMenuItem *parent) {
    menuItem_update(&comLvPanel->miBase, parent);
    menuItem_update(&comLvPanel->miStar, &comLvPanel->miBase);
}

/**
 * Original name: menuComLvPanel_draw
 */
void menuComLvPanel_draw(MenuComLvPanel *comLvPanelArr[], s32 count, Gfx **gfxP) {
    Gfx *gfx = *gfxP;
    bool cached = false;
    MenuComLvPanel *comLvPanel;
    SMenuItem *item;
    TiTexData *texC;
    s32 j;
    s32 i;

    gSPDisplayList(gfx++, fade_normal_texture_init_dl);

    for (i = 0; i < count; i++) {
        comLvPanel = comLvPanelArr[i];
        texC = _getTexChar(comLvPanel->global, 6);
        item = &comLvPanel->miBase;

        if (menuItem_outOfScreen(item, texC->info[TI_INFO_IDX_WIDTH], texC->info[TI_INFO_IDX_HEIGHT])) {
            continue;
        }

        if (item->color[3] < 1.0f) {
            gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
        } else {
            gDPSetRenderMode(gfx++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
        }
        menuItem_setPrim(item, &gfx);

        tiStretchTexTile(&gfx, texC, cached, 0, 0, texC->info[TI_INFO_IDX_WIDTH], 0x14, item->trans[0],
                         item->trans[1], item->scale[0] * texC->info[TI_INFO_IDX_WIDTH], item->scale[1] * 20.0f);
        cached++;
    }

    cached = false;
    for (j = 7; j > 0; j--) {
        for (i = 0; i < count; i++) {
            comLvPanel = comLvPanelArr[i];
            if (j != comLvPanel->level) {
                continue;
            }

            texC = _getTexChar(comLvPanel->global, 6);
            item = &comLvPanel->miStar;
            if (menuItem_outOfScreen(&comLvPanel->miBase, texC->info[TI_INFO_IDX_WIDTH],
                                     texC->info[TI_INFO_IDX_HEIGHT])) {
                continue;
            }

            if (item->color[3] < 1.0f) {
                gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
            } else {
                gDPSetRenderMode(gfx++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
            }
            menuItem_setPrim(item, &gfx);
            tiStretchTexTile(&gfx, texC, cached, 0, 20, (texC->info[TI_INFO_IDX_WIDTH] * j) / 7, 10, item->trans[0],
                             item->trans[1], (item->scale[0] * texC->info[TI_INFO_IDX_WIDTH] * j) / 7.0f,
                             item->scale[1] * 10.0f);
        }
    }

    *gfxP = gfx;
}

const f32 RO_800AFBE0[] = {
    1.0f,
    0.0f,
    0.0f,
};

/**
 * Original name: menuCont_setFade
 */
void menuCont_setFade(MenuCont *cont, s32 arg1, f32 arg2) {
    SMenuItem *sp10[ARRAY_COUNTU(cont->unk_094) + ARRAY_COUNTU(cont->unk_364) + ARRAY_COUNTU(cont->unk_3F4) +
                    ARRAY_COUNTU(cont->unk_484)];
    s32 i;
    s32 j = 0;

    for (i = 0; i < ARRAY_COUNTU(cont->unk_094); i++) {
        sp10[j] = &cont->unk_094[i];
        j++;
    }

    for (i = 0; i < ARRAY_COUNTU(cont->unk_364); i++) {
        sp10[j] = &cont->unk_364[i];
        j++;
    }

    for (i = 0; i < ARRAY_COUNTU(cont->unk_3F4); i++) {
        sp10[j] = &cont->unk_3F4[i];
        j++;
    }

    for (i = 0; i < ARRAY_COUNTU(cont->unk_484); i++) {
        sp10[j] = &cont->unk_484[i];
        j++;
    }

    for (i = 0; i < j; i++) {
        SMenuItem *temp_s0 = sp10[i];

        menuItem_setColor_fade(temp_s0);
        temp_s0->colorStep = 0.05f;
        temp_s0->colorTime = arg2;
        menuItem_setColorDir(temp_s0, arg1);
    }

    for (i = 0; i < ARRAY_COUNTU(cont->unk_364); i++) {
        SMenuItem *var_v1_5 = &cont->unk_364[i];

        for (j = 0; j < ARRAY_COUNT(RO_800AFBE0); j++) {
            var_v1_5->colorRange[0][j] = var_v1_5->colorRange[1][j] = RO_800AFBE0[j];
        }
    }
}

void func_8004B2C8(MenuCont *cont, s32 arg1, s32 arg2) {
    SMenuItem *item = &cont->unk_004;

    item->transTime = arg2;
    item->transStep = 0.05f;
    item->transRange[0][0] = item->transRange[1][0] - 160.0f;
    menuItem_setTransDir(item, arg1);
}

/**
 * Original name: _posDesc_2860
 */
const s32 _posDesc_2860[][2] = {
    { 0xC8, -0x3E }, { 0x66, -0x24 }, { 0x66, 0xE }, { 0x66, 0x40 }, { 0, -0x2C },
};
static_assert(ARRAY_COUNT(_posDesc_2860) == MENUCONT_UNK_094_LEN, "");

/**
 * Original name: _posLine_2861
 */
const s32 _posLine_2861[][2] = {
    { 0xE, -0x29 },
};
static_assert(ARRAY_COUNT(_posLine_2861) == MENUCONT_UNK_364_LEN, "");

/**
 * Original name: menuCont_init
 */
void menuCont_init(MenuCont *cont, struct_watchMenu *watchMenuRef, s32 arg2, s32 arg3) {
    s32 i;

    cont->watchMenuRef = watchMenuRef;

    menuItem_init(&cont->unk_004, arg2, arg3);

    for (i = 0; i < ARRAY_COUNTU(cont->unk_094); i++) {
        menuItem_init(&cont->unk_094[i], _posDesc_2860[i][0], _posDesc_2860[i][1]);
        menuItem_setColor_fade(&cont->unk_094[i]);
    }

    for (i = 0; i < ARRAY_COUNTU(cont->unk_364); i++) {
        menuItem_init(&cont->unk_364[i], _posLine_2861[i][0], _posLine_2861[i][1]);
        menuItem_setColor_fade(&cont->unk_364[i]);
    }

    menuItem_init(&cont->unk_3F4[0], 14, 47);
    menuItem_init(&cont->unk_484[0], 214, 212);
    menuCont_setFade(cont, -1, 0.0f);
    func_8004B2C8(cont, -1, 0);
}

bool func_8004B43C(MenuCont *cont, s32 arg1 UNUSED) {
    SMenuItem *item = &cont->unk_004;

    return ((item->transStep > 0.0f) && (item->transTime == 1.0f));
}

void func_8004B488(MenuCont *cont, SMenuItem *parentItem) {
    menuItem_update(&cont->unk_004, parentItem);
    menuItem_updateN(cont->unk_094, ARRAY_COUNT(cont->unk_094), &cont->unk_004);
    menuItem_updateN(cont->unk_364, ARRAY_COUNT(cont->unk_364), &cont->unk_004);
    menuItem_update(cont->unk_3F4, parentItem);
    menuItem_update(cont->unk_484, parentItem);
}

/**
 * Original name: _line_2914
 */
const s32 _line_2914[] = {
    0,
};
static_assert(ARRAY_COUNT(_line_2914) == MENUCONT_UNK_364_LEN, "");

/**
 * Original name: _desc_2915
 */
const s32 _desc_2915[] = {
    1,
#ifdef PRESERVE_UB
    //! @bug: OoB access: reads index 1 of array `_desc_2915` which has only one element.
    //! This ends up being harmless since the accessed memory (`_panel_3220[0]`) happens to have the same contents
    //! of this array.
    1,
#endif
};

/**
 * Original name: menuCont_draw
 */
void menuCont_draw(MenuCont *cont, Gfx **gfxP) {
    Gfx *gfx = *gfxP;
    SMenuItem *item;
    TiTexData *temp_s3;
    TiTexData *temp;
    s32 i;

    gSPDisplayList(gfx++, fade_normal_texture_init_dl);

    item = &cont->unk_004;
    temp_s3 = _getTexTutol(cont->watchMenuRef, 7);
    menuItem_drawTex(item, &gfx, temp_s3, 0);

    gSPDisplayList(gfx++, fade_intensity_texture_init_dl);

    for (i = 0; i < ARRAY_COUNTU(cont->unk_364); i++) {
        item = &cont->unk_364[i];
        temp_s3 = _getTexCont(cont->watchMenuRef, _line_2914[i]);
        menuItem_drawTex(item, &gfx, temp_s3, 0);
    }

    gSPDisplayList(gfx++, fade_normal_texture_init_dl);
    gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);

    temp_s3 = _getTexCont(cont->watchMenuRef, 2);
    for (i = 0; i < ARRAY_COUNTU(cont->unk_094) - 1; i++) {
        item = &cont->unk_094[i];
        menuItem_drawItem(item, &gfx, temp_s3, 0, 4, i);
    }

    for (; i < ARRAY_COUNTU(cont->unk_094); i++) {
        item = &cont->unk_094[i];

        temp_s3 = _getTexCont(cont->watchMenuRef, _desc_2915[i - (ARRAY_COUNTU(cont->unk_094) - 2)]);

        menuItem_drawTex(item, &gfx, temp_s3, 0);
    }

    menuItem_drawItem(cont->unk_3F4, &gfx, _getTexCommon(cont->watchMenuRef, 0xE), 0, 0x2F, 0x13);

    gSPDisplayList(gfx++, fade_alpha_texture_init_dl);

    temp_s3 = _getTexTutol(cont->watchMenuRef, 1);
    temp = _getTexTutol(cont->watchMenuRef, 3);
    menuItem_drawAlphaTex(cont->unk_484, &gfx, temp_s3, temp, 0);

    *gfxP = gfx;
}

void func_8004B774(MenuMainPanel *mainPanel, s32 arg1, f32 arg2) {
    SMenuItem *item = &mainPanel->unk_028;

    item->transTime = arg2;
    item->transStep = 0.05f;
    // TODO: SCREEN_WIDTH?
    item->transRange[0][0] = item->transRange[1][0] - 320.0f;
    menuItem_setTransDir(item, arg1);
}

/**
 * Original name: menuMainPanel_init
 */
void menuMainPanel_init(MenuMainPanel *mainPanel, struct_watchMenu *watchMenuRef, s32 arg2, s32 arg3, const s32 *arg4,
                        s32 arg5, s32 arg6) {
    s32 i;

    mainPanel->watchMenuRef = watchMenuRef;
    mainPanel->unk_008 = arg2;
    mainPanel->unk_00C = WrapI(0, arg2, arg3);

    for (i = 0; i < ARRAY_COUNTU(mainPanel->unk_010); i++) {
        //! @bug OoB read. End condition should be arg2
        mainPanel->unk_010[i] = arg4[i];
    }

    menuItem_init(&mainPanel->unk_028, arg5, arg6);
    for (i = 0; i < arg2; i++) {
        menuItem_init(&mainPanel->unk_0B8[i], 0xB, 9 + i * 0x17);
    }

    menuCursor_init(&mainPanel->unk_418, watchMenuRef, CURSOR_ITEM, 0, 0, 0, 0x6A, 0x14);
    mainPanel->unk_418.flags.finger = true;
}

/**
 * Original name: menuMainPanel_input
 */
bool menuMainPanel_input(MenuMainPanel *mainPanel, s32 arg1) {
    u32 temp_a0 = _getKeyRep(mainPanel->watchMenuRef, arg1);
    s32 var_v1 = 0;
    s32 temp;

    if ((mainPanel->unk_028.transStep < 0.0f) || (mainPanel->unk_028.transTime < 1.0f)) {
        return false;
    }
    if (temp_a0 & U_JPAD) {
        var_v1--;
    }
    if (temp_a0 & D_JPAD) {
        var_v1++;
    }

#if VERSION_US
    temp = WrapI(0, mainPanel->unk_008, mainPanel->unk_00C + var_v1);
#elif VERSION_GW
    temp = mainPanel->unk_00C;
    do {
        temp = WrapI(0, mainPanel->unk_008, temp + var_v1);
    } while ((var_v1 != 0) && (mainPanel->unk_0B8[temp].unk_64 == 0.0f));
#elif VERSION_CN
    temp = mainPanel->unk_00C;
    temp = WrapI(0, mainPanel->unk_008, temp + var_v1);
#else
#error ""
#endif

    if (temp != mainPanel->unk_00C) {
        dm_snd_play(SND_INDEX_64);
        mainPanel->unk_00C = temp;
    }
    return true;
}

void func_8004B98C(MenuMainPanel *arg0, SMenuItem *parentItem) {
    menuItem_update(&arg0->unk_028, parentItem);
    menuItem_updateN(arg0->unk_0B8, arg0->unk_008, &arg0->unk_028);
    menuCursor_update(&arg0->unk_418, &arg0->unk_0B8[arg0->unk_00C]);
}

// TODO: enum?
/**
 * Original name: _panel_3220
 */
const s32 _panel_3220[] = {
    1, 2, 3, 4, 5,
};

/**
 * Original name: menuMainPanel_draw
 */
void menuMainPanel_draw(MenuMainPanel *arg0, Gfx **gfxP) {
    Gfx *gfx = *gfxP;
    MenuCursor *sp1C[1];
    TiTexData *temp_s4;
    s32 var_s0;

    gSPDisplayList(gfx++, fade_normal_texture_init_dl);

    temp_s4 = _getTexMain(arg0->watchMenuRef, _panel_3220[arg0->unk_008 - 2]);
    menuItem_drawTex(&arg0->unk_028, &gfx, temp_s4, 0);

    temp_s4 = _getTexCommon(arg0->watchMenuRef, 0xE);
    for (var_s0 = 0; var_s0 < arg0->unk_008; var_s0++) {
        menuItem_drawItem(&arg0->unk_0B8[var_s0], &gfx, temp_s4, 0, 0x2F, arg0->unk_010[var_s0]);
    }

    sp1C[0] = &arg0->unk_418;
    menuCursor_draw(sp1C, ARRAY_COUNT(sp1C), &gfx);

    *gfxP = gfx;
}

void func_8004BB14(MenuNameSelPanel *nameSelPanel, s32 arg1, f32 arg2) {
    SMenuItem *item = &nameSelPanel->unk_028;

    item->transTime = arg2;
    item->transStep = 0.05f;
    item->transRange[0][0] = item->transRange[1][0] - 320.0f;
    menuItem_setTransDir(item, arg1);
}

/**
 * Original name: menuNameSelPanel_clear
 */
void menuNameSelPanel_clear(MenuNameSelPanel *nameSelPanel, bool arg1, s32 arg2) {
    s32 var_a3;

    nameSelPanel->unk_004 = arg2;
    nameSelPanel->unk_008 = 0;

    if (evs_select_name_no[0] == evs_select_name_no[1]) {
        evs_select_name_no[1] = 8;
    }

    for (var_a3 = 0; var_a3 < EVS_SELECT_NAME_NO_COUNT; var_a3++) {
        nameSelPanel->unk_00C[var_a3] = 0;
        nameSelPanel->unk_014[var_a3] = evs_select_name_no[var_a3];
        nameSelPanel->unk_01C[var_a3] = (evs_select_name_no[var_a3] & 1);
    }

    nameSelPanel->unk_024.b.unk_31 = (arg1 != false);

    for (var_a3 = 0; var_a3 < ARRAY_COUNTU(nameSelPanel->unk_5C8); var_a3++) {
        nameSelPanel->unk_5C8[var_a3].flags.finger = true;
        nameSelPanel->unk_5C8[var_a3].flags.player = (nameSelPanel->unk_004 >= 2);
    }
}

/**
 * Original name: menuNameSelPanel_init
 */
void menuNameSelPanel_init(MenuNameSelPanel *nameSelPanel, struct_watchMenu *watchMenuRef, bool arg2, s32 arg3,
                           s32 arg4, s32 arg5) {
    s32 i;

    nameSelPanel->watchMenuRef = watchMenuRef;
    menuItem_init(&nameSelPanel->unk_028, arg4, arg5);

    for (i = 0; i < ARRAY_COUNTU(nameSelPanel->unk_0B8) - 1; i++) {
        menuItem_init(&nameSelPanel->unk_0B8[i], (i % 2) * 60 + 6, (i / 2) * 23 + 31);
    }

    menuItem_init(&nameSelPanel->unk_0B8[i], 0x24, 8);

    for (i = 0; i < ARRAY_COUNTU(nameSelPanel->unk_5C8); i++) {
        menuCursor_init(&nameSelPanel->unk_5C8[i], watchMenuRef, CURSOR_ITEM, i, 0, 0, 0x38, 0x14);

        if (i % 2U != 0) {
            SMenuItem *item;

            item = &nameSelPanel->unk_5C8[i].miCursor;
            item->colorTime = WrapF(0.0f, 1.0f, item->colorTime + DOUBLE_LITERAL(0.5));

            item = &nameSelPanel->unk_5C8[i].miFinger;
            item->transTime = WrapF(0.0f, 1.0f, item->transTime + DOUBLE_LITERAL(0.5));
            item->transRange[0][0] += nameSelPanel->unk_5C8[i].size[0] + 0x10;
            item->transRange[1][0] += nameSelPanel->unk_5C8[i].size[0] + 0x10;
            item->scaleRange[0][0] = -item->scaleRange[0][0];
            item->scaleRange[1][0] = -item->scaleRange[1][0];

            item = &nameSelPanel->unk_5C8[i].miPlayer;
            item->transTime = WrapF(0.0f, 1.0f, item->transTime + DOUBLE_LITERAL(0.5));
            item->transRange[0][0] += nameSelPanel->unk_5C8[i].size[0] + 0x10;
            item->transRange[1][0] += nameSelPanel->unk_5C8[i].size[0] + 0x10;
        }
    }

    menuNameSelPanel_clear(nameSelPanel, arg2, arg3);
}

bool func_8004BEB4(MenuNameSelPanel *nameSelPanel, s32 arg1, s32 arg2) {
    if (arg2 != 8) {
        s32 i;

        for (i = 0; i < nameSelPanel->unk_004; i++) {
            if (i == arg1) {
                continue;
            }
            if (nameSelPanel->unk_014[i] == 8) {
                continue;
            }

            if (nameSelPanel->unk_014[i] == arg2) {
                return true;
            }
        }
    }

    return false;
}

/**
 * Original name: menuNameSelPanel_input1
 */
void menuNameSelPanel_input1(MenuNameSelPanel *nameSelPanel, s32 arg1) {
    u32 keyRep = _getKeyRep(nameSelPanel->watchMenuRef, arg1);
    u32 keyTrg = _getKeyTrg(nameSelPanel->watchMenuRef, arg1);
    s32 var_a3;
    SndIndex soundIndex = SND_INDEX_INVALID;
    s32 var_s1 = nameSelPanel->unk_014[arg1];

    if (func_8004BEB4(nameSelPanel, arg1, var_s1)) {
        nameSelPanel->unk_014[arg1] = 8;
        var_s1 = 8;
    }

    if (nameSelPanel->unk_00C[arg1] == 0) {
        if (var_s1 == 8) {
            var_a3 = 0;
            if ((keyRep & L_JPAD)) {
                var_a3--;
            }
            if ((keyRep & R_JPAD)) {
                var_a3++;
            }

            nameSelPanel->unk_01C[arg1] = WrapI(0, 2, nameSelPanel->unk_01C[arg1] + var_a3);

            var_a3 = 0;
            if (keyRep & U_JPAD) {
                var_a3--;
            }
            if (keyRep & D_JPAD) {
                var_a3++;
            }

            if (var_a3 > 0) {
                var_s1 = nameSelPanel->unk_01C[arg1];

                while ((var_s1 < 8) && func_8004BEB4(nameSelPanel, arg1, var_s1)) {
                    var_s1 += 2;
                }
            } else if (var_a3 < 0) {
                var_s1 = nameSelPanel->unk_01C[arg1] + 6;
                while ((var_s1 > 0) && func_8004BEB4(nameSelPanel, arg1, var_s1)) {
                    var_s1 -= 2;
                }
            }

            if ((var_s1 < 0) || (var_s1 >= 8)) {
                var_s1 = 8;
            }
        } else {
            s32 var_s2 = var_s1 & 1;
            s32 var_s0 = var_s1 >> 1;
            s32 var_s4 = 0;
            s32 var_s1_2 = 0;

            if (keyRep & L_JPAD) {
                var_s1_2--;
            }
            if (keyRep & R_JPAD) {
                var_s1_2++;
            }

            if (keyRep & U_JPAD) {
                var_s4--;
            }
            if (keyRep & D_JPAD) {
                var_s4++;
            }

            if ((var_s1_2 != 0) || (var_s4 != 0)) {
                do {
                    var_s2 = WrapI(0, 2, var_s2 + var_s1_2);
                    var_s0 += var_s4;
                } while ((var_s0 >= 0) && (var_s0 < 4) && func_8004BEB4(nameSelPanel, arg1, var_s2 + (var_s0 * 2)));
            }

            if (var_s0 < 0 || var_s0 >= 4) {
                nameSelPanel->unk_01C[arg1] = var_s1 & 1;
                var_s1 = 8;
            } else {
                var_s1 = var_s2 + (var_s0 * 2);
            }
        }
    }

    if (var_s1 != nameSelPanel->unk_014[arg1]) {
        soundIndex = SND_INDEX_64;
        nameSelPanel->unk_014[arg1] = var_s1;
    }

    if (keyTrg & (A_BUTTON | START_BUTTON)) {
        var_a3 = MIN(1, nameSelPanel->unk_00C[arg1] + 1);

        if (var_a3 != nameSelPanel->unk_00C[arg1]) {
            if (nameSelPanel->unk_024.b.unk_31 || (nameSelPanel->unk_014[arg1] != 8)) {
                soundIndex = SND_INDEX_62;
            }

            nameSelPanel->unk_00C[arg1] = var_a3;
        }
    } else if (keyTrg & B_BUTTON) {
        var_a3 = MAX(-1, nameSelPanel->unk_00C[arg1] - 1);

        if (var_a3 != nameSelPanel->unk_00C[arg1]) {
            soundIndex = SND_INDEX_68;
            nameSelPanel->unk_00C[arg1] = var_a3;
        }
    }

    SND_PLAY_INDEX(soundIndex);
}

/**
 * Original name: menuNameSelPanel_input
 */
bool menuNameSelPanel_input(MenuNameSelPanel *nameSelPanel) {
    s32 var_s3 = 0;
    s32 i;

    if ((nameSelPanel->unk_028.transStep < 0.0f) || (nameSelPanel->unk_028.transTime < 1.0f)) {
        return false;
    }

    nameSelPanel->unk_008 = 0;

    for (i = 0; i < nameSelPanel->unk_004; i++) {
        menuNameSelPanel_input1(nameSelPanel, i);

        if (nameSelPanel->unk_00C[i] > 0) {
            var_s3++;
            continue;
        }

        if (nameSelPanel->unk_00C[i] < 0) {
            nameSelPanel->unk_00C[i] = 0;
            nameSelPanel->unk_008 = -1;
            return true;
        }
    }

    if (var_s3 == nameSelPanel->unk_004) {
        nameSelPanel->unk_008 = 1;
    }

    return true;
}

/**
 * Original name: menuNameSelPanel_update
 */
void menuNameSelPanel_update(MenuNameSelPanel *nameSelPanel, SMenuItem *parentItem) {
    s32 i;
    s32 j;

    menuItem_update(&nameSelPanel->unk_028, parentItem);
    menuItem_updateN(nameSelPanel->unk_0B8, ARRAY_COUNT(nameSelPanel->unk_0B8), &nameSelPanel->unk_028);

    for (i = 0; i < nameSelPanel->unk_004; i++) {
        nameSelPanel->unk_5C8[i].miCursor.colorRange[0][3] = 1.0f;
    }

    for (i = 0; i < (nameSelPanel->unk_004 - 1); i++) {
        for (j = i + 1; j < nameSelPanel->unk_004; j++) {
            if (nameSelPanel->unk_014[i] == nameSelPanel->unk_014[j]) {
                //! FAKE:

#if VERSION_CN
                SMenuItem *item = &nameSelPanel->unk_5C8[i].miCursor;
                SMenuItem *item2 = &nameSelPanel->unk_5C8[j].miCursor;

                item->colorRange[0][3] = 0.0f;
                item2->colorRange[0][3] = 0.0f;
#elif VERSION_US || VERSION_GW
                nameSelPanel->unk_5C8[i].miCursor.colorRange[0][3] = 0.0f;
                nameSelPanel->unk_5C8[j].miCursor.colorRange[0][3] = 0.0f;
#else
#error ""
#endif
            }
        }
    }

    for (i = 0; i < ARRAY_COUNTU(nameSelPanel->unk_5C8); i++) {
        menuCursor_update(&nameSelPanel->unk_5C8[i], &nameSelPanel->unk_0B8[nameSelPanel->unk_014[i]]);
        if (nameSelPanel->unk_00C[i] > 0) {
            SMenuItem *item = &nameSelPanel->unk_5C8[i].miCursor;

            for (j = 0; j < MENUITEM_COLOR_COUNT; j++) {
                item->color[j] = item->colorRange[1][j];
            }

            nameSelPanel->unk_5C8[i].flags.finger = false;
            nameSelPanel->unk_5C8[i].flags.blink = false;
        } else {
            nameSelPanel->unk_5C8[i].flags.finger = true;
            nameSelPanel->unk_5C8[i].flags.blink = true;
        }
    }
}

/**
 * Original name: _texEndOrGuest_3608
 */
const s32 _texEndOrGuest_3608[2] = {
    13,
    14,
};

/**
 * Original name: menuNameSelPanel_draw
 */
void menuNameSelPanel_draw(MenuNameSelPanel *nameSelPanel, Gfx **gfxP) {
    Gfx *gfx = *gfxP;
    MenuCursor *sp2C[nameSelPanel->unk_004];
    TiTexData *temp_s3;
    s32 var_s1;
    s32 i;
    s32 pad[2] UNUSED;

    gSPDisplayList(gfx++, fade_normal_texture_init_dl);

    temp_s3 = _getTexMain(nameSelPanel->watchMenuRef, 4);
    menuItem_drawTex(&nameSelPanel->unk_028, &gfx, temp_s3, 0);

    temp_s3 = _getTexMain(nameSelPanel->watchMenuRef, 7);

    var_s1 = 0;
    for (i = 0; i < ARRAY_COUNTU(nameSelPanel->unk_0B8) - 1; i++) {
        var_s1 += menuItem_drawTex(&nameSelPanel->unk_0B8[i], &gfx, temp_s3, var_s1);
    }

    temp_s3 = _getTexMain(nameSelPanel->watchMenuRef, _texEndOrGuest_3608[nameSelPanel->unk_024.b.unk_31]);
    menuItem_drawTex(&nameSelPanel->unk_0B8[i], &gfx, temp_s3, 0);

    gSPDisplayList(gfx++, fade_intensity_texture_init_dl);
    gDPSetTextureFilter(gfx++, G_TF_BILERP);

    for (i = 0; i < ARRAY_COUNTU(nameSelPanel->unk_0B8) - 1; i++) {
        SMenuItem *item = &nameSelPanel->unk_0B8[i];
        const u8 *temp;
        s32 j;

        if (menuItem_outOfScreen(item, 0xE, 0xE)) {
            continue;
        }

        // wtf
        if (evs_mem_data[i].mem_use_flg & MEM_USE_FLG_1) {
            temp = evs_mem_data[i].mem_name;
        } else {
            temp = evs_mem_data[i].mem_name;
        }

        j = item->color[3] * 255.0f;
        if (evs_mem_data[i].mem_use_flg & MEM_USE_FLG_1) {
            gDPSetPrimColor(gfx++, 0, 0, 1, 1, 1, j);
        } else {
            gDPSetPrimColor(gfx++, 0, 0, 160, 160, 160, 255);
        }

        for (j = 0; j < 4; j++) {
            fontXX_drawID(&gfx, item->trans[0] + 4.0f + j * 0xC, item->trans[1] + 4.0f, item->scale[0] * 12.0f,
                          item->scale[1] * 12.0f, temp[j]);
        }
    }

    for (i = 0; i < nameSelPanel->unk_004; i++) {
        sp2C[i] = &nameSelPanel->unk_5C8[i];
    }
    menuCursor_draw(sp2C, nameSelPanel->unk_004, &gfx);

    *gfxP = gfx;
}

void func_8004C820(MenuNameOpPanel *nameOpPanel, s32 arg1, f32 arg2) {
    SMenuItem *item = &nameOpPanel->unk_010;

    item->transTime = arg2;
    item->transStep = 0.05f;
    item->transRange[0][0] = item->transRange[1][0] - 320.0f;
    menuItem_setTransDir(item, arg1);
}

/**
 * Original name: _name_3803
 */
const u8 _name_3803[MENUNAMEOPPANEL_UNK_LEN] = { 0 };

/**
 * Original name: menuNameOpPanel_init
 */
void menuNameOpPanel_init(MenuNameOpPanel *nameOpPanel, struct_watchMenu *watchMenuRef, s32 arg2, s32 arg3,
                          const u8 *arg4, s32 xPos, s32 yPos) {
    s32 i;

    nameOpPanel->watchMenuRef = watchMenuRef;
    nameOpPanel->unk_004 = arg2;
    nameOpPanel->unk_008 = arg3;

    if (arg4 == NULL) {
        arg4 = _name_3803;
    }

    for (i = 0; i < MENUNAMEOPPANEL_UNK_LEN; i++) {
        nameOpPanel->unk_00C[i] = arg4[i];
    }

    menuItem_init(&nameOpPanel->unk_010, xPos, yPos);
    menuItem_init(&nameOpPanel->unk_0A0, 35, 8);

    for (i = 0; i < ARRAY_COUNTU(nameOpPanel->unk_130); i++) {
        menuItem_init(&nameOpPanel->unk_130[i], 11, 31 + 23 * i);
    }

    menuCursor_init(&nameOpPanel->unk_250, watchMenuRef, CURSOR_ITEM, 0, 0, 0, 0x69, 0x14);
    nameOpPanel->unk_250.flags.finger = true;
}

/**
 * Original name: menuNameOpPanel_input
 */
bool menuNameOpPanel_input(MenuNameOpPanel *nameOpPanel, s32 arg1) {
    u32 keyRep = _getKeyRep(nameOpPanel->watchMenuRef, arg1);
    s32 var_s0 = nameOpPanel->unk_008;

    if ((nameOpPanel->unk_010.transStep < 0.0f) || (nameOpPanel->unk_010.transTime < 1.0f)) {
        return false;
    }

    if (keyRep & U_JPAD) {
        var_s0--;
    }
    if (keyRep & D_JPAD) {
        var_s0++;
    }

    var_s0 = WrapI(0, 2, var_s0);
    if (var_s0 != nameOpPanel->unk_008) {
        dm_snd_play(SND_INDEX_64);
        nameOpPanel->unk_008 = var_s0;
    }
    return true;
}

void func_8004CA30(MenuNameOpPanel *nameOpPanel, SMenuItem *parentItem) {
    menuItem_update(&nameOpPanel->unk_010, parentItem);
    menuItem_update(&nameOpPanel->unk_0A0, &nameOpPanel->unk_010);
    menuItem_updateN(nameOpPanel->unk_130, ARRAY_COUNT(nameOpPanel->unk_130), &nameOpPanel->unk_010);
    menuCursor_update(&nameOpPanel->unk_250, &nameOpPanel->unk_130[nameOpPanel->unk_008]);
}

// TODO: enum?
/**
 * Original name: _panel_3859
 */
const s32 _panel_3859[][2] = {
    { 24, 25 },
    { 28, 25 },
};

/**
 * Original name: menuNameOpPanel_draw
 */
void menuNameOpPanel_draw(MenuNameOpPanel *nameOpPanel, Gfx **gfxP) {
    Gfx *gfx = *gfxP;
    MenuCursor *sp1C[1];
    SMenuItem *item;
    TiTexData *temp_s1;
    s32 i;

    gSPDisplayList(gfx++, fade_normal_texture_init_dl);

    temp_s1 = _getTexMain(nameOpPanel->watchMenuRef, 2);
    menuItem_drawTex(&nameOpPanel->unk_010, &gfx, temp_s1, 0);

    temp_s1 = _getTexCommon(nameOpPanel->watchMenuRef, 0xE);
    for (i = 0; i < ARRAY_COUNTU(nameOpPanel->unk_130); i++) {
        menuItem_drawItem(&nameOpPanel->unk_130[i], &gfx, temp_s1, 0, 0x2F, _panel_3859[nameOpPanel->unk_004][i]);
    }

    temp_s1 = _getTexMain(nameOpPanel->watchMenuRef, 7);
    menuItem_drawTex(&nameOpPanel->unk_0A0, &gfx, temp_s1, 0);

    gSPDisplayList(gfx++, fade_intensity_texture_init_dl);
    gDPSetTextureFilter(gfx++, G_TF_BILERP);
    gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, 255);

    item = &nameOpPanel->unk_0A0;
    for (i = 0; i < ARRAY_COUNTU(nameOpPanel->unk_00C); i++) {
        fontXX_drawID(&gfx, item->trans[0] + 4.0f + (i * 12), item->trans[1] + 4.0f, item->scale[0] * 12.0f,
                      item->scale[1] * 12.0f, nameOpPanel->unk_00C[i]);
    }

    sp1C[0] = &nameOpPanel->unk_250;
    menuCursor_draw(sp1C, ARRAY_COUNT(sp1C), &gfx);

    *gfxP = gfx;
}

void func_8004CCD0(MenuSndSelPanel *sndSelPanel, s32 arg1, f32 arg2) {
    SMenuItem *item = &sndSelPanel->unk_014;

    item->transTime = arg2;
    item->transStep = 0.05f;
    item->transRange[0][0] = item->transRange[1][0] - 320.0f;
    menuItem_setTransDir(item, arg1);
}

/**
 * Original name: _pos_4015
 */
const s32 _pos_4015[] = {
    64,
    64,
};
static_assert(ARRAY_COUNT(_pos_4015) == MENUSNDSELPANEL_UNK_2E4_LEN, "");

/**
 * Original name: _y_4020
 */
const s32 _y_4020[] = {
    22,
    44,
    98,
    120,
};
static_assert(ARRAY_COUNT(_y_4020) == MENUSNDSELPANEL_UNK_0A4_LEN, "");

/**
 * Original name: menuSndSelPanel_init
 */
void menuSndSelPanel_init(MenuSndSelPanel *sndSelPanel, struct_watchMenu *watchMenuRef, s32 arg2, s32 arg3, s32 arg4) {
    s32 i;

    sndSelPanel->watchMenuRef = watchMenuRef;
    sndSelPanel->unk_004 = arg2;
    sndSelPanel->unk_008 = 0;
    sndSelPanel->unk_00C = 0;
    sndSelPanel->unk_010 = SND_INDEX_0;

    menuItem_init(&sndSelPanel->unk_014, arg3, arg4);

    for (i = 0; i < ARRAY_COUNTU(sndSelPanel->unk_0A4); i++) {
        menuItem_init(&sndSelPanel->unk_0A4[i], 14, _y_4020[i]);
    }

    for (i = 0; i < ARRAY_COUNTU(sndSelPanel->unk_2E4); i++) {
        menuNumber_init(&sndSelPanel->unk_2E4[i], watchMenuRef, 0, i + 2, 0, _pos_4015[i], 4);
    }

    menuCursor_init(&sndSelPanel->unk_43C, watchMenuRef, CURSOR_ITEM, 0, 0, 0, 0x69, 0x14);
    sndSelPanel->unk_43C.flags.finger = true;
}

/**
 * Original name: _tbl_4036
 */
const u8 _tbl_4036[] = {
    SND_INDEX_0,
    SND_INDEX_1,
    SND_INDEX_2,
    SND_INDEX_3,
    SND_INDEX_4,
    SND_INDEX_5,
    SND_INDEX_6,
    SND_INDEX_7,
    SND_INDEX_8,
    SND_INDEX_9,
    SND_INDEX_10,
    SND_INDEX_11,
    SND_INDEX_12,
    SND_INDEX_13,
    SND_INDEX_14,
    SND_INDEX_15,
    SND_INDEX_16,
    SND_INDEX_17,
    SND_INDEX_18,
    SND_INDEX_19,
    SND_INDEX_20,
    SND_INDEX_21,
    SND_INDEX_22,
    SND_INDEX_23,
    SND_INDEX_24,
    SND_INDEX_25,
    SND_INDEX_26,
    SND_INDEX_27,
    SND_INDEX_28,
    SND_INDEX_29,
    SND_INDEX_30,
    SND_INDEX_31,
    SND_INDEX_32,
    SND_INDEX_33,
    SND_INDEX_34,
    SND_INDEX_35,
    SND_INDEX_36,
    SND_INDEX_37,
    SND_INDEX_38,
    SND_INDEX_39,
    SND_INDEX_40,
    SND_INDEX_41,
    SND_INDEX_42,
    SND_INDEX_43,
    SND_INDEX_44,
    SND_INDEX_45,
    SND_INDEX_46,
    SND_INDEX_47,
    SND_INDEX_48,
    SND_INDEX_49,
    SND_INDEX_50,
    SND_INDEX_51,
    SND_INDEX_52,
    SND_INDEX_53,
    SND_INDEX_54,
    SND_INDEX_55,
    SND_INDEX_56,
    SND_INDEX_57,
    SND_INDEX_58,
    SND_INDEX_59,
    SND_INDEX_60,
    SND_INDEX_61,
    SND_INDEX_62,
    SND_INDEX_63,
    SND_INDEX_64,
    SND_INDEX_65,
    SND_INDEX_66,
    SND_INDEX_67,
    SND_INDEX_68,
    // skips SND_INDEX_69
    SND_INDEX_70,
    SND_INDEX_71,
    SND_INDEX_72,
    SND_INDEX_73,
    SND_INDEX_74,
    SND_INDEX_75,
    SND_INDEX_76,
    SND_INDEX_77,
    SND_INDEX_78,
    SND_INDEX_79,
    SND_INDEX_80,
    SND_INDEX_81,
    SND_INDEX_82,
    SND_INDEX_83,
    SND_INDEX_84,
    SND_INDEX_85,
    SND_INDEX_86,
    SND_INDEX_87,
    SND_INDEX_88,
    SND_INDEX_89,
    SND_INDEX_90,
    SND_INDEX_91,
    SND_INDEX_92,
    SND_INDEX_93,
    SND_INDEX_94,
    SND_INDEX_95,
    SND_INDEX_96,
    SND_INDEX_97,
    SND_INDEX_98,
    SND_INDEX_99,
    SND_INDEX_100,
    SND_INDEX_101,
    SND_INDEX_102,
    SND_INDEX_103,
};

/**
 * Original name: menuSndSelPanel_input
 */
bool menuSndSelPanel_input(MenuSndSelPanel *sndSelPanel, s32 arg1) {
    SndIndex soundIndex = SND_INDEX_INVALID;
    u32 keyRep = _getKeyRep(sndSelPanel->watchMenuRef, arg1);
    s32 var_a3 = sndSelPanel->unk_004;

    if ((sndSelPanel->unk_014.transStep < 0.0f) || (sndSelPanel->unk_014.transTime < 1.0f)) {
        return false;
    }

    if (keyRep & U_JPAD) {
        var_a3--;
    }
    if (keyRep & D_JPAD) {
        var_a3++;
    }

    var_a3 = WrapI(0, 4, var_a3);
    if (var_a3 != sndSelPanel->unk_004) {
        soundIndex = SND_INDEX_64;
        sndSelPanel->unk_004 = var_a3;
    }

    var_a3 = 0;
    if (keyRep & L_JPAD) {
        var_a3--;
    }
    if (keyRep & R_JPAD) {
        var_a3++;
    }
    if (keyRep & L_TRIG) {
        var_a3 -= 10;
    }
    if (keyRep & R_TRIG) {
        var_a3 += 10;
    }

    if (var_a3 != 0) {
        if (sndSelPanel->unk_004 >= 2) {
            soundIndex = SND_INDEX_63;
            switch (sndSelPanel->unk_004) {
                case 0x2:
                    sndSelPanel->unk_008 = WrapI(0, 24, sndSelPanel->unk_008 + var_a3);
                    break;

                case 0x3:
                    sndSelPanel->unk_00C = WrapI(0, ARRAY_COUNT(_tbl_4036), sndSelPanel->unk_00C + var_a3);
                    sndSelPanel->unk_010 = _tbl_4036[sndSelPanel->unk_00C];
                    break;
            }
        }
    }

    SND_PLAY_INDEX(soundIndex);

    return true;
}

void func_8004CFB8(MenuSndSelPanel *sndSelPanel, SMenuItem *parentItem) {
    s32 i;

    sndSelPanel->unk_2E4[0].number = sndSelPanel->unk_008;
    sndSelPanel->unk_2E4[1].number = sndSelPanel->unk_00C;
    menuItem_update(&sndSelPanel->unk_014, parentItem);
    menuItem_updateN(sndSelPanel->unk_0A4, 4, &sndSelPanel->unk_014);

    for (i = 0; i < ARRAY_COUNT(sndSelPanel->unk_2E4); i++) {
        menuNumber_update(&sndSelPanel->unk_2E4[i], &sndSelPanel->unk_0A4[i + 2]);
    }

    menuCursor_update(&sndSelPanel->unk_43C, &sndSelPanel->unk_0A4[sndSelPanel->unk_004]);
}

/**
 * Original name: _panel_4108
 */
const s32 _panel_4108[] = {
    0x1A,
    0x1B,
    0x23,
    0x24,
};
static_assert(ARRAY_COUNT(_panel_4108) == MENUSNDSELPANEL_UNK_0A4_LEN, "");

/**
 * Original name: menuSndSelPanel_draw
 */
void menuSndSelPanel_draw(MenuSndSelPanel *sndSelPanel, Gfx **gfxP) {
    void *sp18[ARRAY_COUNT(sndSelPanel->unk_2E4)];
    s32 pad[2] UNUSED;
    Gfx *gfx = *gfxP;
    SMenuItem *item;
    s32 i;
    TiTexData *temp_v0;
    f32 temp_fs0;
    f32 temp_fs1;

    gSPDisplayList(gfx++, fade_normal_texture_init_dl);

    item = &sndSelPanel->unk_014;

    temp_fs0 = item->trans[0];
    temp_fs1 = item->trans[1];
    temp_v0 = _getTexMain(sndSelPanel->watchMenuRef, 0xB);

    menuItem_drawTex(item, &gfx, temp_v0, 0);
    item->trans[1] += 76.0f;
    menuItem_drawTex(item, &gfx, temp_v0, 0);
    item->trans[0] = temp_fs0 + 19.0f;
    item->trans[1] = temp_fs1 + 2.0f;
    temp_v0 = _getTexMain(sndSelPanel->watchMenuRef, 0xC);
    menuItem_drawTex(item, &gfx, temp_v0, 0);
    item->trans[0] = temp_fs0;
    item->trans[1] = temp_fs1;

    temp_v0 = _getTexCommon(sndSelPanel->watchMenuRef, 0xE);
    for (i = 0; i < ARRAY_COUNTU(sndSelPanel->unk_0A4); i++) {
        menuItem_drawItem(&sndSelPanel->unk_0A4[i], &gfx, temp_v0, 0, 0x2F, _panel_4108[i]);
    }

    for (i = 0; i < ARRAY_COUNTU(sndSelPanel->unk_2E4); i++) {
        sp18[i] = &sndSelPanel->unk_2E4[i];
    }
    menuNumber_draw((void *)sp18, ARRAY_COUNT(sp18), &gfx);

    sp18[0] = &sndSelPanel->unk_43C;
    menuCursor_draw((void *)sp18, 1, &gfx);

    *gfxP = gfx;
}

void func_8004D258(void *arg) {
    MenuPlay2Panel *play2Panel = arg;
    void *sp10 = play2Panel->unk_002C;

    animeState_load(&play2Panel->unk_0C90, &sp10, play2Panel->unk_0020);
    play2Panel->unk_0030.b.bit_30 = true;
}

// TODO: enum?
/**
 * Original name: _lvNumScale_4308
 */
const f32 _lvNumScale_4308[][2] = {
    { 1.0f, 1.0f },
    { 0.875f, 0.9375f },
};

/**
 * Original name: _player_4309
 */
const s32 _player_4309[][2] = {
    { 4, 4 },
    { 24, 60 },
};

/**
 * Original name: _lvNum_4310
 */
const s32 _lvNum_4310[][2] = {
    { 114, 7 },
    { 114, 7 },
};

/**
 * Original name: _lvGauge_4311
 */
const s32 _lvGauge_4311[][2] = {
    { 167, 12 },
    { 169, 14 },
};

/**
 * Original name: _speedAsk_4312
 */
const s32 _speedAsk_4312[][2] = {
    { 94, 24 },
    { 96, 41 },
};

/**
 * Original name: _speedAsk_4312
 */
const s32 _speedItem_4313[][2] = {
    { 142, 24 },
    { 143, 36 },
};

/**
 * Original name: _glvAsk_4314
 */
const s32 _glvAsk_4314[][2] = {
    { 94, 4 },
    { 96, 10 },
};

/**
 * Original name: _glvItem_4315
 */
const s32 _glvItem_4315[][2] = {
    { 142, 4 },
    { 143, 5 },
};

/**
 * Original name: _okY_4316
 */
const s32 _okY_4316[] = {
    19,
    28,
};

/**
 * Original name: _cursor_4317
 */
const s32 _cursor_4317[][2][4] = {
    { { 51, 0, 219, 23 }, { 51, 20, 219, 23 } },
    { { 51, 0, 219, 34 }, { 51, 31, 219, 34 } },
};

/**
 * Original name: menuPlay2Panel_init
 */
void menuPlay2Panel_init(MenuPlay2Panel *play2Panel, struct_watchMenu *watchMenuRef, void **heapP, s32 arg3, s32 arg4,
                         s32 arg5, s32 arg6, bool arg7, CharAnimeMode arg8, s32 arg9, s32 argA, s32 argB, s32 argC) {
    void *heap = *heapP;
    SMenuItem *item;
    s32 i;

    play2Panel->watchMenuRef = watchMenuRef;

    switch (_getMode(watchMenuRef)) {
        case MODE_VSCOM:
        case MODE_VSMAN:
        case MODE_PLAY4_LV:
        case MODE_PLAY4_TB_LV:
            play2Panel->unk_0004 = 0;
            play2Panel->unk_0008 = 0;
            play2Panel->unk_000C = 0;
            break;

        case MODE_VSCOM_FL:
        case MODE_VSMAN_FL:
        case MODE_PLAY4_FL_LV:
            play2Panel->unk_0004 = 1;
            play2Panel->unk_0008 = 0;
            play2Panel->unk_000C = 1;
            break;

        case MODE_VSMAN_TA:
            play2Panel->unk_0004 = 0;
            play2Panel->unk_0008 = 1;
            play2Panel->unk_000C = 1;
            break;

        default:
            break;
    }

    play2Panel->unk_0010 = arg3;
    play2Panel->unk_0014 = arg4;
    play2Panel->unk_0018 = arg5;
    play2Panel->unk_001C = arg6;
    play2Panel->unk_0020 = arg8;
    play2Panel->unk_0024 = 0;

    if (arg7) {
        play2Panel->unk_0028 = -1;
    } else {
        play2Panel->unk_0028 = 0;
    }

    play2Panel->unk_0030.b.bit_31 = arg7 != false;
    play2Panel->unk_0030.b.bit_30 = false;

    menuItem_init(&play2Panel->unk_0034, argB, argC);
    menuItem_init(&play2Panel->unk_00C4, _player_4309[arg3][0], _player_4309[arg3][1]);
    menuItem_init(&play2Panel->unk_0154, 0xA, 4);

    if (play2Panel->unk_000C != 0) {
        menuSpeedAsk_init(&play2Panel->unk_1220, watchMenuRef, 2, arg9, _glvAsk_4314[arg3][0], _glvAsk_4314[arg3][1]);
        menuSpeedItem_init(&play2Panel->unk_12BC, watchMenuRef, arg3 + 2, arg6, arg9, _glvItem_4315[arg3][0],
                           _glvItem_4315[arg3][1], 0x2A);
    } else {
        menuLvGauge_init(&play2Panel->unk_0290, watchMenuRef, arg3, arg6, arg9, _lvGauge_4311[arg3][0],
                         _lvGauge_4311[arg3][1]);
        menuNumber_init(&play2Panel->unk_01E4, watchMenuRef, arg3, 2, arg9, _lvNum_4310[arg3][0], _lvNum_4310[arg3][1]);

        item = &play2Panel->unk_01E4.miBase;
        menuItem_setScaleLow(item, _lvNumScale_4308[arg3][0], _lvNumScale_4308[arg3][1]);
        menuItem_setScaleHi(item, _lvNumScale_4308[arg3][0], _lvNumScale_4308[arg3][1]);
    }

    menuSpeedAsk_init(&play2Panel->unk_0590, watchMenuRef, 0, argA, _speedAsk_4312[arg3][0], _speedAsk_4312[arg3][1]);
    menuSpeedItem_init(&play2Panel->unk_062C, watchMenuRef, arg3, arg6, argA, _speedItem_4313[arg3][0],
                       _speedItem_4313[arg3][1], 0x2A);

    switch (arg3) {
        case 0:
            break;

        case 1:
            play2Panel->unk_002C = ALIGN_PTR(heap);
            heap = (void *)((uintptr_t)play2Panel->unk_002C + animeState_getDataSize(arg8));
            BgTasksManager_SendTask(func_8004D258, play2Panel);
            break;
    }

    menuItem_init(&play2Panel->unk_0CD0, 8, _okY_4316[arg3]);
    menuItem_setColor_fade(&play2Panel->unk_0CD0);
    menuItem_setColorDir(&play2Panel->unk_0CD0, -1);
    play2Panel->unk_0CD0.colorTime = 0.0f;

    for (i = 0; i < ARRAY_COUNTU(play2Panel->unk_0D60); i++) {
        menuCursor_init(&play2Panel->unk_0D60[i], watchMenuRef, CURSOR_PANEL, arg6, _cursor_4317[arg3][i][0],
                        _cursor_4317[arg3][i][1], _cursor_4317[arg3][i][2], _cursor_4317[arg3][i][3]);
    }

    *heapP = heap;
}

void menuPlay2Panel_copyConfig(MenuPlay2Panel *play2Panel, MenuPlay2Panel *arg1) {
    if (play2Panel == arg1) {
        return;
    }

    switch (arg1->unk_0024) {
        case 0:
            if (play2Panel->unk_000C != 0) {
                play2Panel->unk_12BC.select = arg1->unk_12BC.select;
            } else {
                play2Panel->unk_0290.level = arg1->unk_0290.level;
            }
            break;

        case 1:
            play2Panel->unk_062C.select = arg1->unk_062C.select;
            break;
    }
}

void menuPlay2Panel_copyCursor(MenuPlay2Panel *play2Panel, MenuPlay2Panel *other) {
    s32 i;

    if (play2Panel == other) {
        return;
    }

    for (i = 0; i < ARRAY_COUNTU(play2Panel->unk_0D60); i++) {
        play2Panel->unk_0D60[i].flags.cursor = false;
    }

    if (play2Panel->unk_000C != 0) {
        play2Panel->unk_12BC.cursor.flags.cursor = false;
        play2Panel->unk_12BC.cursor.flags.finger = false;
    } else {
        play2Panel->unk_0290.cursor.flags.cursor = false;
        play2Panel->unk_0290.cursor.flags.finger = false;
    }

    play2Panel->unk_062C.cursor.flags.cursor = false;
    play2Panel->unk_062C.cursor.flags.finger = false;

    switch (other->unk_0024) {
        case 0x0:
            if (play2Panel->unk_000C != 0) {
                play2Panel->unk_12BC.cursor.flags.finger = true;
            } else {
                play2Panel->unk_0290.cursor.flags.finger = true;
            }
            break;

        case 0x1:
            play2Panel->unk_062C.cursor.flags.finger = true;
            break;
    }
}

void menuPlay2Panel_input(MenuPlay2Panel *play2Panel, s32 arg1, s32 arg2, s32 arg3) {
    u32 keyRep = _getKeyRep(play2Panel->watchMenuRef, arg1);
    u32 keyTrg = _getKeyTrg(play2Panel->watchMenuRef, arg1);
    SndIndex soundIndex = SND_INDEX_INVALID;
    s32 var_a0 = 0;
    s32 var_v1;

    switch (play2Panel->unk_0028) {
        case -0x1:
            play2Panel->unk_0028 = 0;
            FALLTHROUGH;

        case 0x0:
            if ((keyRep & U_JPAD) || (keyTrg & B_BUTTON)) {
                var_a0--;
            }
            if ((keyRep & D_JPAD) || (keyTrg & (A_BUTTON | START_BUTTON))) {
                var_a0++;
            }

            var_v1 = CLAMP(play2Panel->unk_0024 + var_a0, 0, 1);

            if (var_v1 != play2Panel->unk_0024) {
                soundIndex = SND_INDEX_64;
                play2Panel->unk_0024 = var_v1;
            } else {
                switch (play2Panel->unk_0024) {
                    case 0:
                        if (play2Panel->unk_000C == 0) {
                            menuLvGauge_input(&play2Panel->unk_0290, arg1);
                        } else {
                            menuSpeedItem_input(&play2Panel->unk_12BC, arg1);
                        }
                        break;

                    case 1:
                        menuSpeedItem_input(&play2Panel->unk_062C, arg1);
                }
            }

            if (soundIndex <= SND_INDEX_INVALID) {
                switch (play2Panel->unk_0024) {
                    case 1:
                        if ((keyTrg & (A_BUTTON | START_BUTTON)) || ((keyRep & D_JPAD) && (arg3 == 0))) {
                            soundIndex = SND_INDEX_62;
                            play2Panel->unk_0028 += 1;
                        }
                        break;

                    case 0:
                        if ((keyTrg & B_BUTTON) || ((keyRep & U_JPAD) && (arg2 == 0))) {
                            soundIndex = SND_INDEX_68;
                            play2Panel->unk_0028 -= 1;
                        }
                        break;
                }
            }
            break;

        case 0x1:
            if ((keyTrg & B_BUTTON) || ((keyTrg & U_JPAD) && (arg2 == 0))) {
                play2Panel->unk_0028 = 0;
                soundIndex = SND_INDEX_68;
            }
            break;

        default:
            break;
    }

    SND_PLAY_INDEX(soundIndex);
}

void menuPlay2Panel_update(MenuPlay2Panel *play2Panel, SMenuItem *parentItem) {
    SMenuItem *item;
    s32 i;

    if (play2Panel->unk_000C != 0) {
        play2Panel->unk_1220.select = play2Panel->unk_12BC.select;
    } else {
        play2Panel->unk_01E4.number = play2Panel->unk_0290.level;
    }

    play2Panel->unk_0590.select = play2Panel->unk_062C.select;

    menuItem_update(&play2Panel->unk_0034, parentItem);
    menuItem_update(&play2Panel->unk_00C4, &play2Panel->unk_0034);
    menuItem_update(&play2Panel->unk_0154, &play2Panel->unk_0034);

    if (play2Panel->unk_000C != 0) {
        menuSpeedAsk_update(&play2Panel->unk_1220, &play2Panel->unk_0034);
        menuSpeedItem_update(&play2Panel->unk_12BC, &play2Panel->unk_0034);
    } else {
        menuNumber_update(&play2Panel->unk_01E4, &play2Panel->unk_0034);
        menuLvGauge_update(&play2Panel->unk_0290, &play2Panel->unk_0034);
    }

    menuSpeedAsk_update(&play2Panel->unk_0590, &play2Panel->unk_0034);
    menuSpeedItem_update(&play2Panel->unk_062C, &play2Panel->unk_0034);

    switch (play2Panel->unk_0010) {
        case 0:
            break;

        case 1:
            if (play2Panel->unk_0030.b.bit_30) {
                item = &play2Panel->unk_00C4;

                play2Panel->unk_0C90.primColor[0] = item->color[0] * 255.0f;
                play2Panel->unk_0C90.primColor[1] = item->color[1] * 255.0f;
                play2Panel->unk_0C90.primColor[2] = item->color[2] * 255.0f;
                play2Panel->unk_0C90.primColor[3] = item->color[3] * 255.0f;
                animeState_update(&play2Panel->unk_0C90);
            }
            break;
    }

    menuItem_update(&play2Panel->unk_0CD0, &play2Panel->unk_0034);

    if (play2Panel->unk_0028 == 1) {
        item = &play2Panel->unk_0CD0;

        for (i = 0; i < MENUITEM_COLOR_COUNT; i++) {
            item->color[i] = parentItem->color[i];
        }
    }

    for (i = 0; i < ARRAY_COUNTU(play2Panel->unk_0D60); i++) {
        menuCursor_update(&play2Panel->unk_0D60[i], &play2Panel->unk_0034);
    }

    menuItem_setColorDir(&play2Panel->unk_0034, (play2Panel->unk_0028 != 0) ? -1 : 1);

    i = 0;
    if ((play2Panel->unk_0028 == 0) && (play2Panel->unk_0024 == 0)) {
        i = 1;
    }

    play2Panel->unk_0D60[0].flags.cursor = i;

    if (play2Panel->unk_000C != 0) {
        play2Panel->unk_12BC.flags.blink = i;
        play2Panel->unk_12BC.cursor.flags.finger = i;
    } else {
        play2Panel->unk_0290.cursor.flags.finger = i;
        play2Panel->unk_0290.cursor.flags.cursor = i;
        play2Panel->unk_0290.cursor.flags.blink = i;
    }

    i = 0;
    if ((play2Panel->unk_0028 == 0) && (play2Panel->unk_0024 == 1)) {
        i = 1;
    }

    play2Panel->unk_062C.flags.blink = i;
    play2Panel->unk_0D60[1].flags.cursor = i;

    play2Panel->unk_062C.cursor.flags.finger = i;
}

const s32 _charTbl_4601[] = {
    0, 1, 2, 3, 7, 5, 8, 4, 9, 6, 0xA, 0xB, 0xC, 0xE, 0xD,
};

const s32 _type_4602[][4] = {
    { 0, 4, 7, 9 },
    { 0, 1, 5, 8 },
    { 0, 1, 2, 6 },
    { 0, 1, 2, 3 },
};

const s32 _texPanelP4_4617[] = {
    1,
    2,
};

const s32 _texPanelP2_4618[] = { 0, 1 };

void menuPlay2Panel_draw(MenuPlay2Panel *play2PanelArr[], s32 count, Gfx **gfxP) {
    Gfx *gfx = *gfxP;
    void *arr[8][count];
    s32 i;
    SMenuItem *temp_s1_2;
    MenuPlay2Panel *var_s2;
    TiTexData *var_s3;
    s32 var_s5;

    for (i = 0; i < count; i++) {
        var_s2 = play2PanelArr[i];

        arr[0][i] = &var_s2->unk_01E4;
        arr[1][i] = &var_s2->unk_0290;
        arr[2][i] = &var_s2->unk_0590;
        arr[3][i] = &var_s2->unk_062C;
        arr[4][i] = &var_s2->unk_1220;
        arr[5][i] = &var_s2->unk_12BC;
        arr[6][i] = &var_s2->unk_0D60[0];
        arr[7][i] = &var_s2->unk_0D60[1];
    }

    gSPDisplayList(gfx++, fade_normal_texture_init_dl);

    for (i = 0; i < count; i++) {
        var_s2 = play2PanelArr[i];

        switch (var_s2->unk_0010) {
            case 0:
                var_s3 = _getTexP4(var_s2->watchMenuRef, _texPanelP4_4617[var_s2->unk_000C != 0 ? 1 : 0]);
                break;

            case 1:
                var_s3 = _getTexP2(var_s2->watchMenuRef, _texPanelP2_4618[var_s2->unk_000C != 0 ? 1 : 0]);
                break;
        }

        menuItem_drawTex(&var_s2->unk_0034, &gfx, var_s3, 0);
    }

    menuSpeedAsk_draw((void *)arr[2], count, &gfx);
    menuSpeedItem_draw1((void *)arr[3], count, &gfx);
    if (var_s2->unk_000C != 0) {
        menuSpeedAsk_draw((void *)arr[4], count, &gfx);
        menuSpeedItem_draw1((void *)arr[5], count, &gfx);
    } else {
        menuNumber_draw((void *)arr[0], count, &gfx);
        menuLvGauge_draw1((void *)arr[1], count, &gfx);
    }

    menuCursor_draw((void *)arr[6], count, &gfx);
    menuCursor_draw((void *)arr[7], count, &gfx);

    gSPDisplayList(gfx++, fade_normal_texture_init_dl);

    for (i = 0; i < count; i++) {
        var_s2 = play2PanelArr[i];
        temp_s1_2 = &var_s2->unk_00C4;

        switch (var_s2->unk_0010) {
            case 0:
                var_s3 = _getTexP4(var_s2->watchMenuRef, 0);
                menuItem_drawItem(temp_s1_2, &gfx, var_s3, 0, 0xF, _charTbl_4601[var_s2->unk_0020]);
                break;

            case 1:
                if (var_s2->unk_0030.b.bit_30) {
                    menuItem_setPrim(temp_s1_2, &gfx);
                    animeState_draw(&var_s2->unk_0C90, &gfx, temp_s1_2->trans[0], temp_s1_2->trans[1], -1.0f, 1.0f);
                }
                break;
        }
    }

    for (i = 0; i < count; i++) {
        s32 var_v1_2;

        var_s2 = play2PanelArr[i];
        var_s3 = _getTexSetup(var_s2->watchMenuRef, 0x11);
        if ((var_s2->unk_001C == 1) && (var_s2->unk_0014 == var_s2->unk_001C) &&
            (var_s2->unk_0018 == var_s2->unk_0014)) {
            var_v1_2 = 0xA;
        } else {
            var_v1_2 = _type_4602[var_s2->unk_0014 - 1][var_s2->unk_001C];
        }
        menuItem_drawItem(&var_s2->unk_0154, &gfx, var_s3, 0, 0xB, var_v1_2);
    }

    gSPDisplayList(gfx++, fade_alpha_texture_init_dl);

    var_s5 = 0;
    for (i = 0; i < count; i++) {
        var_s2 = play2PanelArr[i];

        var_s3 = _getTexSetup(var_s2->watchMenuRef, 0xB);
        var_s5 += menuItem_drawAlphaTex(&var_s2->unk_0CD0, &gfx, var_s3, _getTexSetup(var_s2->watchMenuRef, 4), var_s5);
    }

    menuSpeedItem_draw2((void *)arr[3], count, &gfx);
    if (var_s2->unk_000C != 0) {
        menuSpeedItem_draw2((void *)arr[5], count, &gfx);
    } else {
        menuLvGauge_draw2((void *)arr[1], count, &gfx);
    }

    *gfxP = gfx;
}

void func_8004E270(MenuPlay2PanelSub *play2PanelSub, s32 arg1, f32 arg2) {
    SMenuItem *item = &play2PanelSub->unk_010;

    item->transTime = arg2;
    item->transStep = 0.05f;
    item->transRange[0][1] = item->transRange[1][1] - 240.0f;
    menuItem_setTransDir(item, arg1);
}

const u8 _bgDataNo_to_stageNo[][2] = {
    { 0, 1 }, { 0, 3 }, { 0, 0 }, { 1, 5 }, { 0, 5 }, { 0, 4 }, { 1, 4 }, { 0, 2 }, { 0, 6 }, { 0, 7 },
};

void func_8004E2B4(MenuPlay2PanelSub *play2PanelSub, s32 arg1, f32 arg2, f32 arg3) {
    SMenuItem *item;

    item = &play2PanelSub->unk_9EC;
    item->transTime = arg2;
    item->transStep = 0.05f;
    item->transRange[0][0] = item->transRange[1][0] + arg3;
    menuItem_setTransDir(item, arg1);
}

const s32 _bgCursor_4920[][2] = {
    { 0x83, 0x36 },
    { 0xEC, 0x36 },
};
static_assert(ARRAY_COUNT(_bgCursor_4920) == MENUPLAY2PANELSUB_UNK_17C, "");

const s32 _cursor_4921[][4] = {
    { 0, 0, 0x10E, 0x22 },
    { 0, 0x1F, 0x10E, 0x3C },
};
static_assert(ARRAY_COUNT(_cursor_4921) == MENUPLAY2PANELSUB_UNK_B9C, "");

void menuPlay2PanelSub_init(MenuPlay2PanelSub *play2PanelSub, struct_watchMenu *watchMenuRef, void **heapP UNUSED,
                            s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    SMenuItem *item;
    s32 i;

    play2PanelSub->watchMenuRef = watchMenuRef;
    play2PanelSub->unk_004 = 0;
    play2PanelSub->unk_008 = 0;
    play2PanelSub->unk_00C = -1;

    menuItem_init(&play2PanelSub->unk_010, arg5, arg6);
    menuMusicItem_init(&play2PanelSub->unk_0A0, watchMenuRef, arg4, 0x46, 9);

    menuNumber_init(&play2PanelSub->unk_940, watchMenuRef, 1, 2, arg3, 0x60, 0x28);

    item = &play2PanelSub->unk_940.miBase;
    menuItem_setScaleLow(item, 7.0f / 8.0f, 15.0f / 16.0f);
    menuItem_setScaleHi(item, 7.0f / 8.0f, 15.0f / 16.0f);

    menuItem_init(&play2PanelSub->unk_9EC, 0x9C, 0x30);

    for (i = 0; i < ARRAY_COUNTU(play2PanelSub->unk_A7C); i++) {
        menuItem_init(&play2PanelSub->unk_A7C[i], _bgCursor_4920[i][0], _bgCursor_4920[i][1]);
        menuItem_setColor_cursor(&play2PanelSub->unk_A7C[i]);
    }

    item = &play2PanelSub->unk_A7C[ARRAY_COUNTU(play2PanelSub->unk_A7C) - 1];
    item->scaleRange[0][0] = -item->scaleRange[0][0];
    item->scaleRange[1][0] = -item->scaleRange[1][0];

    for (i = 0; i < ARRAY_COUNTU(play2PanelSub->unk_B9C); i++) {
        menuCursor_init(&play2PanelSub->unk_B9C[i], watchMenuRef, CURSOR_ITEM, 0, _cursor_4921[i][0],
                        _cursor_4921[i][1], _cursor_4921[i][2], _cursor_4921[i][3]);
    }

    func_8004E270(play2PanelSub, -1, 0.0f);
}

bool menuPlay2PanelSub_input(MenuPlay2PanelSub *play2PanelSub, s32 arg1) {
    u32 keyRep = _getKeyRep(play2PanelSub->watchMenuRef, arg1);
    u32 keyTrg = _getKeyTrg(play2PanelSub->watchMenuRef, arg1);
    SndIndex soundIndex = SND_INDEX_INVALID;
    s32 var_s0;
    s32 var_v1;

    if ((play2PanelSub->unk_010.transStep < 0.0f) || (play2PanelSub->unk_010.transTime < 1.0f)) {
        return false;
    }

    switch (play2PanelSub->unk_008) {
        case -0x1:
            play2PanelSub->unk_008 = 0;
            FALLTHROUGH;

        case 0x0:
            var_s0 = 0;
            if ((keyRep & U_JPAD) || (keyTrg & B_BUTTON)) {
                var_s0--;
            }
            if ((keyRep & D_JPAD) || (keyTrg & (A_BUTTON | START_BUTTON))) {
                var_s0++;
            }

            var_v1 = CLAMP(play2PanelSub->unk_004 + var_s0, 0, 1);
            if (var_v1 != play2PanelSub->unk_004) {
                soundIndex = SND_INDEX_64;
                play2PanelSub->unk_004 = var_v1;
            } else {
                switch (var_v1) {
                    case 0x0:
                        menuMusicItem_input(&play2PanelSub->unk_0A0, arg1);
                        break;

                    case 0x1:
                        var_s0 = 0;
                        if (keyRep & L_JPAD) {
                            var_s0--;
                        }
                        if (keyRep & R_JPAD) {
                            var_s0++;
                        }

                        if (var_s0 != 0) {
                            play2PanelSub->unk_940.number = WrapI(1, 0xB, play2PanelSub->unk_940.number + var_s0);
                            if (var_s0 < 0) {
                                play2PanelSub->unk_00C = -1;
                            } else {
                                play2PanelSub->unk_00C = -2;
                            }

                            soundIndex = SND_INDEX_63;
                            func_8004E2B4(play2PanelSub, 1, 0.0f, var_s0 * 0x48);
                        }
                        break;
                }
            }

            if (soundIndex <= SND_INDEX_INVALID) {
                if ((keyTrg & (A_BUTTON | START_BUTTON)) && (play2PanelSub->unk_004 == 1)) {
                    soundIndex = SND_INDEX_62;
                    play2PanelSub->unk_008++;
                } else if ((keyTrg & B_BUTTON) && (play2PanelSub->unk_004 == 0)) {
                    soundIndex = SND_INDEX_68;
                    play2PanelSub->unk_008--;
                }
            }
            break;

        case 0x1:
            if (keyTrg & B_BUTTON) {
                soundIndex = SND_INDEX_68;
                play2PanelSub->unk_008 = 0;
            }
            break;
    }

    SND_PLAY_INDEX(soundIndex);

    return true;
}

void menuPlay2PanelSub_update(MenuPlay2PanelSub *play2PanelSub, SMenuItem *parentItem) {
    SMenuItem *temp_s0 = &play2PanelSub->unk_010;
    s32 i;

    menuItem_update(temp_s0, parentItem);
    if (play2PanelSub->unk_004 != 0) {
        play2PanelSub->unk_0A0.cursor.miBase.colorTime = 1.0f;
    }

    menuMusicItem_update(&play2PanelSub->unk_0A0, temp_s0);
    menuNumber_update(&play2PanelSub->unk_940, temp_s0);
    menuItem_update(&play2PanelSub->unk_9EC, temp_s0);
    menuItem_updateN(play2PanelSub->unk_A7C, 2, temp_s0);

    for (i = 0; i < ARRAY_COUNTU(play2PanelSub->unk_B9C); i++) {
        menuCursor_update(&play2PanelSub->unk_B9C[i], &play2PanelSub->unk_010);
    }

    i = play2PanelSub->unk_004 == 0;
    play2PanelSub->unk_B9C[0].flags.cursor = i;
    play2PanelSub->unk_0A0.cursor.flags.finger = i;
    play2PanelSub->unk_0A0.flags.blink = i;

    i = play2PanelSub->unk_004 == 1;
    play2PanelSub->unk_B9C[1].flags.cursor = i;

    if (play2PanelSub->unk_004 != 1) {
        for (i = 0; i < ARRAY_COUNTU(play2PanelSub->unk_A7C); i++) {
            SMenuItem *var_v1 = &play2PanelSub->unk_A7C[i];
            s32 j;

            for (j = 0; j < 3; j++) {
                var_v1->color[j] = var_v1->colorRange[1][j] * parentItem->color[j];
            }
        }
    }
}

void menuPlay2PanelSub_draw(MenuPlay2PanelSub *play2PanelSub, Gfx **gfxP) {
    Gfx *gfx = *gfxP;
    void *arr[2 * 4];
    SMenuItem *item;
    TiTexData *temp_s2;
    s32 var_s4;
    s32 i;
    f32 temp_fs0;

    gSPDisplayList(gfx++, fade_normal_texture_init_dl);

    temp_s2 = _getTexSetup(play2PanelSub->watchMenuRef, 0x12);
    menuItem_drawTex(&play2PanelSub->unk_010, &gfx, temp_s2, 0);

    for (i = 0; i < ARRAY_COUNTU(play2PanelSub->unk_B9C); i++) {
        arr[i] = &play2PanelSub->unk_B9C[i];
    }
    menuCursor_draw((void *)arr, ARRAY_COUNTU(play2PanelSub->unk_B9C), &gfx);

    arr[0] = &play2PanelSub->unk_0A0;
    menuMusicItem_draw((void *)arr, 1, &gfx);
    arr[0] = &play2PanelSub->unk_940;
    menuNumber_draw((void *)arr, 1, &gfx);

    gSPDisplayList(gfx++, fade_normal_texture_init_dl);

    item = &play2PanelSub->unk_9EC;
    menuItem_setPrim(item, &gfx);
    gfxSetScissor(&gfx, GFXSETSCISSOR_INTERLACE_NO, play2PanelSub->unk_010.trans[0] + item->transRange[1][0] - 16.0f,
                  play2PanelSub->unk_010.trans[1] + item->transRange[1][1], 0x68, 0x24);

    temp_s2 = _getTexSetup(play2PanelSub->watchMenuRef, 0xE);
    temp_fs0 = item->trans[0];
    item->trans[0] += (play2PanelSub->unk_00C * 0x48);

    item = &play2PanelSub->unk_9EC;
    for (i = 0; i < 4; i++) {
        menuItem_drawItem(item, &gfx, temp_s2, 0, 0xA,
                          WrapI(0, 0xA, (play2PanelSub->unk_940.number + play2PanelSub->unk_00C + i) - 1));
        item->trans[0] += 72.0f;
    }

    gDPSetScissor(gfx++, G_SC_NON_INTERLACE, 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1);
    item->trans[0] = temp_fs0;
    gSPDisplayList(gfx++, fade_normal_texture_init_dl);

    temp_s2 = _getTexSetup(play2PanelSub->watchMenuRef, 0x10);

    var_s4 = 0;
    for (i = 0; i < ARRAY_COUNTU(play2PanelSub->unk_A7C); i++) {
        var_s4 += menuItem_drawTex(&play2PanelSub->unk_A7C[i], &gfx, temp_s2, var_s4);
    }

    *gfxP = gfx;
}

MainMenuMode _menuMain_lastMode = MODE_MAIN;

const char *_tblMain_5279[] = {
    _mesP1,
    _mes2P,
    _mes4P,
    _mesOpt,
};

const char *_tblPlay1_5280[] = {
    _mesLv, _mesSt, _mesVsCom, _mesVcFlash, _mesLvTaiQ, _mesLvTimeAt,
};

const char *_tblPlay2_5281[] = {
    _mesVsMan,
    _mesVmFlash,
    _mesVmTimeAt,
};

const char *D_8008E7C0[] = {
    _mesVsNum,
    _mesVsNum,
    _mesVsNum,
    _mesVsNum,
};

const char *_tblBaTyp_5282[] = {
    _mesVs4P,
    _mes4PTag,
    _mes4PFlash,
};

const char *_tblOpt_5283[] = {
    _mesRec, _mesTutol, _mesName, _mesBak, _mesMisc,
};

const char *_tblTutol_5284[] = {
    _mesRule1, _mesRule2, _mesRule3, _mesRule4, _mesKotu,
};

const char *_tblSound_5285[] = {
    _mesStereo,
    _mesMono,
    _mesSound,
    _mesSound,
};

const char *_tblMisc_5286[] = {
    _mesSnd,
    _mesVsCnt,
    _mesScore,
};

const char *_loopTbl_5287[] = {
    _mesSt,       _mesLv,   _mesVsCom, _mesVcFlash, _mesLvTaiQ, _mesLvTimeAt, _mesVsMan,     _mesVmFlash,
    _mesVmTimeAt, _mesVs4P, _mes4PTag, _mes4PFlash, _mesSnd,    _mesNs1,      _mesNameErase, _mesDoErase,
};

bool menuMain_setMsgStr(MenuMain *menuMain, MainMenuMode mode, s32 arg2) {
    bool ret = false;
    const char **var_v1 = NULL;
    const char *var_s1 = NULL;
    s32 i;

    switch (mode) {
        case MODE_MAIN:
            var_v1 = _tblMain_5279;
            break;

        case MODE_PLAY1:
            var_v1 = _tblPlay1_5280;
            break;

        case MODE_PLAY2:
            var_v1 = _tblPlay2_5281;
            break;

        case MODE_PLAY4:
            var_s1 = _mesVsNum;
            break;

        case MODE_OPTION:
            var_v1 = _tblOpt_5283;
            break;

        case MODE_MISC:
            var_v1 = _tblMisc_5286;
            break;

        case MODE_SCORE:
            var_s1 = _mesScoreOnOff;
            break;

        case MODE_PLAY4_TYPE1:
        case MODE_PLAY4_TYPE2:
        case MODE_PLAY4_TYPE3:
        case MODE_PLAY4_TYPE4:
            var_v1 = _tblBaTyp_5282;
            break;

        case MODE_TUTORIAL:
            var_v1 = _tblTutol_5284;
            break;

        case MODE_SOUND:
            var_s1 = _tblSound_5285[menuMain->unk_1C64.unk_004];
            break;

        case MODE_RECORD_MS:
            var_s1 = _mesRecMs1;
            break;

        case MODE_RECORD_PLAY1:
        case MODE_RECORD_PLAY2:
            var_s1 = _mesRecMs2;
            break;

        case MODE_NAME:
            var_s1 = _mesNameSel;
            break;

        case MODE_NAME_DEL_YN:
            var_s1 = _mesNameErase;
            break;

        case MODE_NAME_DEL_MES:
            var_s1 = _mesNameErase2;
            break;

        case MODE_COUNT:
            var_s1 = _mesVsCnt2;
            break;

        case MODE_BACKUP:
        case MODE_BACKUP_YN:
            var_s1 = _mesDoErase;
            break;

        case MODE_BACKUP_MES:
            var_s1 = _mesDoErase1;
            break;

        case MODE_STORY_NS:
        case MODE_LVSEL_NS:
        case MODE_LVSEL_TQ_NS:
        case MODE_LVSEL_TA_NS:
        case MODE_VSCOM_NS:
        case MODE_VSCOM_FL_NS:
        case MODE_VSMAN_NS:
        case MODE_VSMAN_FL_NS:
        case MODE_VSMAN_TA_NS:
            var_s1 = _mesNs1;
            break;

        case MODE_NAME_NS:
            var_s1 = _mesNs2;
            break;

        default:
            break;
    }

    if (var_v1 != NULL) {
        var_s1 = var_v1[arg2];
    }

    for (i = 0; i < ARRAY_COUNTU(_loopTbl_5287); i++) {
        if ((var_s1 == _loopTbl_5287[i]) && msgWnd_isEnd(&menuMain->msgWnd)) {
            menuMain->unk_2304 = NULL;
        }
    }

    if (var_s1 != menuMain->unk_2304) {
        msgWnd_clear(&menuMain->msgWnd);
        if (var_s1 != NULL) {
            msgWnd_addStr(&menuMain->msgWnd, var_s1);
            ret = true;
        }
        menuMain->unk_2304 = var_s1;
    }

    return ret;
}

const s32 _root_5339[] = {
    0x00000000,
    0x00000001,
    0x00000002,
    0x00000003,
};
static_assert(ARRAY_COUNT(_root_5339) <= MENUMAINPANEL_UNK_LEN, "");

const s32 _play1_5340[] = {
    0x00000005, 0x00000004, 0x00000006, 0x0000001E, 0x0000001F, 0x00000020,
};
static_assert(ARRAY_COUNT(_play1_5340) <= MENUMAINPANEL_UNK_LEN, "");

const s32 _play2_5341[] = {
    0x0000001D,
    0x0000001E,
    0x00000020,
};
static_assert(ARRAY_COUNT(_play2_5341) <= MENUMAINPANEL_UNK_LEN, "");

const s32 _play4_5342[] = {
    0x00000009,
    0x0000000A,
    0x0000000B,
    0x0000000C,
};
static_assert(ARRAY_COUNT(_play4_5342) <= MENUMAINPANEL_UNK_LEN, "");

const s32 _play4type_5343[] = {
    0x00000025,
    0x00000026,
    0x0000001E,
};
static_assert(ARRAY_COUNT(_play4type_5343) <= MENUMAINPANEL_UNK_LEN, "");

const s32 _option_5344[] = {
    0x0000000D, 0x0000000E, 0x0000000F, 0x00000011, 0x0000002B,
};
static_assert(ARRAY_COUNT(_option_5344) <= MENUMAINPANEL_UNK_LEN, "");

const s32 _recMs_5345[] = {
    0x00000021,
    0x00000022,
};
static_assert(ARRAY_COUNT(_recMs_5345) <= MENUMAINPANEL_UNK_LEN, "");

const s32 _recMs1_5346[] = {
    0x00000005, 0x00000004, 0x00000006, 0x0000001E, 0x0000001F, 0x00000020,
};
static_assert(ARRAY_COUNT(_recMs1_5346) <= MENUMAINPANEL_UNK_LEN, "");

const s32 _recMs2_5347[] = {
    0x0000001D,
    0x0000001E,
    0x00000020,
};
static_assert(ARRAY_COUNT(_recMs2_5347) <= MENUMAINPANEL_UNK_LEN, "");

const s32 _tutorial_5348[] = {
    0x00000013, 0x00000014, 0x00000015, 0x00000016, 0x00000017,
};
static_assert(ARRAY_COUNT(_tutorial_5348) <= MENUMAINPANEL_UNK_LEN, "");

const s32 _count_5349[] = {
    0x00000028,
    0x00000029,
    0x0000002A,
};
static_assert(ARRAY_COUNT(_count_5349) <= MENUMAINPANEL_UNK_LEN, "");

const s32 _backup_5350[] = {
    0x0000001C,
    0x00000011,
};
static_assert(ARRAY_COUNT(_backup_5350) <= MENUMAINPANEL_UNK_LEN, "");

const s32 _misc_5351[] = {
    0x00000010,
    0x00000027,
    0x0000002C,
};
static_assert(ARRAY_COUNT(_misc_5351) <= MENUMAINPANEL_UNK_LEN, "");

const s32 _score_5352[] = {
    0x0000002D,
    0x0000002E,
};
static_assert(ARRAY_COUNT(_score_5352) <= MENUMAINPANEL_UNK_LEN, "");

void menuMain_initPanel(MenuMain *menuMain, MainMenuMode mode, s32 arg2, s32 arg3) {
    const s32 *ptr;
    s32 len;

    switch (mode) {
        case MODE_PLAY1:
            ptr = _play1_5340;
            len = ARRAY_COUNT(_play1_5340);
            break;

        case MODE_PLAY2:
            ptr = _play2_5341;
            len = ARRAY_COUNT(_play2_5341);
            break;

        case MODE_PLAY4:
            ptr = _play4_5342;
            len = ARRAY_COUNT(_play4_5342);
            break;

        case MODE_OPTION:
            ptr = _option_5344;
            len = ARRAY_COUNT(_option_5344);
            break;

        case MODE_PLAY4_TYPE1:
        case MODE_PLAY4_TYPE2:
        case MODE_PLAY4_TYPE3:
        case MODE_PLAY4_TYPE4:
            ptr = _play4type_5343;
            len = ARRAY_COUNT(_play4type_5343);
            break;

        case MODE_RECORD_MS:
            ptr = _recMs_5345;
            len = ARRAY_COUNT(_recMs_5345);
            break;

        case MODE_RECORD_PLAY1:
            ptr = _recMs1_5346;
            len = ARRAY_COUNT(_recMs1_5346);
            break;

        case MODE_RECORD_PLAY2:
            ptr = _recMs2_5347;
            len = ARRAY_COUNT(_recMs2_5347);
            break;

        case MODE_TUTORIAL:
            ptr = _tutorial_5348;
            len = ARRAY_COUNT(_tutorial_5348);
            break;

        case MODE_COUNT:
            ptr = _count_5349;
            len = ARRAY_COUNT(_count_5349);
            break;

        case MODE_BACKUP:
            ptr = _backup_5350;
            len = ARRAY_COUNT(_backup_5350);
            break;

        case MODE_MISC:
            ptr = _misc_5351;
            len = ARRAY_COUNT(_misc_5351);
            break;

        case MODE_SCORE:
            ptr = _score_5352;
            len = ARRAY_COUNT(_score_5352);
            break;

        case MODE_MAIN:
        default:
            ptr = _root_5339;
            len = ARRAY_COUNT(_root_5339);
            break;
    }

    menuMainPanel_init(&menuMain->unk_003C[arg2], menuMain->watchMenuRef, len, arg3, ptr, 0x19, 0x3A);

#if VERSION_GW
    switch (mode) {
        case MAINMENUMODE_MENUMAIN_0:
            menuItem_setColorDir(&menuMain->unk_003C[arg2].unk_0B8[1], -1);
            menuMain->unk_003C[arg2].unk_0B8[1].unk_64 = 0;
            menuItem_setColorDir(&menuMain->unk_003C[arg2].unk_0B8[2], -1);
            menuMain->unk_003C[arg2].unk_0B8[2].unk_64 = 0;
            break;

        case MAINMENUMODE_47:
            menuItem_setColorDir(&menuMain->unk_003C[arg2].unk_0B8[1], -1);
            menuMain->unk_003C[arg2].unk_0B8[1].unk_64 = 0;
            break;

        default:
            break;
    }
#endif
}

void menuMain_init(MenuMain *menuMain, struct_watchMenu *watchMenuRef, void **heapP) {
    SMenuItem *item;
    s32 i;

    menuMain->watchMenuRef = watchMenuRef;
    if (_getModeOld(watchMenuRef) == MODE_NAME_NE2) {
        menuMain->mode = _menuMain_lastMode = MODE_NAME_NS;
    } else {
        menuMain->mode = _menuMain_lastMode;
    }

    menuMain->unk_0008 = _menuMain_lastDepth;
    for (i = 0; i < ARRAY_COUNTU(_menuMain_lastSelect); i++) {
        menuMain->unk_000C[i] = _menuMain_lastSelect[i];
    }

    if (_getModeOld(watchMenuRef) == MODE_MAIN) {
        menuMain->unk_000C[0] = 0;
    }

    menuMain->unk_002C = 0;
    menuMain->unk_0030 = -1;
    menuMain->unk_0034 = 0xC;
    menuMain->unk_2304 = 0;
    menuMain->unk_2300 = 0;
    menuMain->unk_0038 = 0;

    for (i = 0; i < ARRAY_COUNTU(menuMain->unk_003C); i++) {
        menuMain_initPanel(menuMain, menuMain->mode, i, menuMain->unk_000C[menuMain->unk_0008]);
        func_8004B774(&menuMain->unk_003C[i], -1, 0);
    }

    i = 1;
    switch (menuMain->mode) {
        default:
            break;

        case MODE_VSMAN_NS:
        case MODE_VSMAN_FL_NS:
        case MODE_VSMAN_TA_NS:
            i = 2;
            break;
    }

    menuNameSelPanel_init(&menuMain->unk_0D2C, watchMenuRef, menuMain->mode != MODE_NAME_NS, i, 0x19, 0x3A);
    func_8004BB14(&menuMain->unk_0D2C, -1, 0.0f);

    menuNameOpPanel_init(&menuMain->unk_17B4, menuMain->watchMenuRef, 0, 0, NULL, 0x19, 0x3A);
    func_8004C820(&menuMain->unk_17B4, -1, 0.0f);

    menuSndSelPanel_init(&menuMain->unk_1C64, watchMenuRef, 0, 0x14, 0x3A);
    func_8004CCD0(&menuMain->unk_1C64, -1, 0.0f);

    switch (menuMain->mode) {
        case MODE_STORY_NS:
        case MODE_LVSEL_NS:
        case MODE_LVSEL_TQ_NS:
        case MODE_LVSEL_TA_NS:
        case MODE_VSCOM_NS:
        case MODE_VSCOM_FL_NS:
        case MODE_VSMAN_NS:
        case MODE_VSMAN_FL_NS:
        case MODE_VSMAN_TA_NS:
        case MODE_NAME_NS:
            func_8004BB14(&menuMain->unk_0D2C, 1, 0);
            break;

        default:
            func_8004B774(menuMain->unk_003C, 1, 0);
            break;
    }

    msgWnd_init(&menuMain->msgWnd, heapP, 12, 4, 156, 34);
    menuMain->msgWnd.contFlags = 0;

#if VERSION_CN
    menuMain->msgWnd.rowStep = 14;
#else
    menuMain->msgWnd.rowStep = 13;
#endif

    item = &menuMain->unk_2388;
    menuItem_init(item, 0x9E, 0x2F);
    item->transTime = 0.0f;
    item->transStep = 0.05f;
    item->transRange[0][0] += 320.0f;

    menuItem_init(&menuMain->unk_2418, 0xDC, 0x63);
    item = &menuMain->unk_2418;
    item->transStep = 0.05f;
    item->transTime = 0.0f;
    item->transRange[0][0] += 320.0f;

    menuItem_init(&menuMain->unk_2538, -0x44, 0x16);
    item = &menuMain->unk_2538;
    item->transStep = 0.05f;
    item->transTime = 0.0f;
    item->transRange[0][0] = 32.0f;
    item->transRange[0][1] = 54.0f;
    menuItem_setTransDir(item, -1);
    item->scaleStep = 0.05f;
    item->scaleTime = 0.0f;
    menuItem_setScaleDir(item, -1);
    item->colorRange[1][0] = 1.0f;
    item->colorRange[1][1] = 0.9411765f;
    item->colorRange[1][2] = 0.972549f;

    menuItem_init(&menuMain->unk_25C8, 6, 5);
    menuMain->unk_25C8.flags.localColor = true;

    menuItem_init(&menuMain->unk_24A8, 0x51, 0x11);

    menuCont_init(&menuMain->unk_2658, watchMenuRef, 0xE, 0x71);

    menuYN_init(&menuMain->unk_2B6C, watchMenuRef, 0x78, 0x8C);

    menuMes_init(&menuMain->unk_31E4, watchMenuRef, heapP, 0x11, 2, 0x40, 0xA6);
}

void func_8004F2D8(MenuMain *menuMain) {
    u32 keyTrg = _getKeyTrg(menuMain->watchMenuRef, 0);

    if ((keyTrg & B_BUTTON) && (menuMain->mode != MODE_MAIN)) {
        _setFadeDir(menuMain->watchMenuRef, -1);
        _setNextMain(menuMain->watchMenuRef, MAIN_MENU);
        dm_snd_play(SND_INDEX_68);
    }
}

const char *mes_5577[] = {
    _mesNoCont2,
    _mesNoCont3,
    _mesNoCont4,
};

void func_8004F33C(MenuMain *menuMain) {
    menuMain_update(menuMain);
}

const MainMenuMode tbl_5517[] = {
    MODE_PLAY1,
    MODE_PLAY2,
    MODE_PLAY4,
    MODE_OPTION,
};

const s32 _n_5535[] = { 1, 0, 2, 3, 4, 5 };

const MainMenuMode _mode_5538[] = {
    MODE_LVSEL_NS, MODE_STORY_NS, MODE_VSCOM_NS, MODE_VSCOM_FL_NS, MODE_LVSEL_TQ_NS, MODE_LVSEL_TA_NS,
};

const MainMenuMode mode_5557[] = {
    MODE_VSMAN_NS,
    MODE_VSMAN_FL_NS,
    MODE_VSMAN_TA_NS,
};

const char _mode_5570[] = {
    MODE_PLAY4_TYPE1,
    MODE_PLAY4_TYPE2,
    MODE_PLAY4_TYPE3,
    MODE_PLAY4_TYPE4,
};

const MainMenuMode _tbl_5598[][2] = {
    { MODE_STORY, MODE_OPTION },
    { MODE_STORY, MODE_NAME },
    { MODE_STORY_NE, MODE_NAME_NE },
};

const MainMenuMode _tblLS_5599[][3] = {
    { MODE_LVSEL, MODE_LVSEL_TQ, MODE_LVSEL_TA },
    { MODE_LVSEL, MODE_LVSEL_TQ, MODE_LVSEL_TA },
    { MODE_LVSEL_NE, MODE_LVSEL_TQ_NE, MODE_LVSEL_TA_NE },
};

const MainMenuMode _tblVM_5600[][3] = {
    { MODE_VSMAN_CH, MODE_VSMAN_FL_CH, MODE_VSMAN_TA_CH },
    { MODE_VSMAN_CH, MODE_VSMAN_FL_CH, MODE_VSMAN_TA_CH },
    { MODE_VSMAN_NE, MODE_VSMAN_FL_NE, MODE_VSMAN_TA_NE },
};

const MainMenuMode _tblVC_5601[][2] = {
    { MODE_VSCOM_CH, MODE_VSCOM_FL_CH },
    { MODE_VSCOM_CH, MODE_VSCOM_FL_CH },
    { MODE_VSCOM_NE, MODE_VSCOM_FL_NE },
};

const MainMenuMode tbl_5648[] = {
    MODE_RECORD_MS, MODE_TUTORIAL, MODE_NAME_NS, MODE_BACKUP, MODE_MISC,
};

const MainMenuMode tbl_5664[] = {
    MODE_SOUND,
    MODE_COUNT,
    MODE_SCORE,
};

const u8 _team_5687[][4] = {
    { TEAMNUMBER_0, TEAMNUMBER_1, TEAMNUMBER_2, TEAMNUMBER_3 },
    { TEAMNUMBER_0, TEAMNUMBER_0, TEAMNUMBER_1, TEAMNUMBER_1 },
    { TEAMNUMBER_0, TEAMNUMBER_1, TEAMNUMBER_2, TEAMNUMBER_3 },
};

const MainMenuMode _mode_5688[] = {
    MODE_PLAY4_CH,
    MODE_PLAY4_TB_CH,
    MODE_PLAY4_FL_CH,
};

const enum_evs_gamemode _game_5689[] = {
    GMD_NORMAL,
    GMD_NORMAL,
    GMD_FLASH,
};

const MainMenuMode _mode_5701[] = {
    MODE_RECORD_PLAY1,
    MODE_RECORD_PLAY2,
};

const MainMenuMode _mode1_5709[] = {
    MODE_RECORD_LS, MODE_RECORD_ST, MODE_RECORD_VC, MODE_RECORD_VC_FL, MODE_RECORD_LS_TQ, MODE_RECORD_LS_TA,
};

const MainMenuMode _mode2_5710[] = {
    MODE_RECORD_VM,
    MODE_RECORD_VM_FL,
    MODE_RECORD_VM_TA,
};

const MainMenuMode tbl_5735[] = {
    MODE_NAME_NE2,
    MODE_NAME_DEL_YN,
};

void menuMain_input(MenuMain *menuMain) {
    MenuMainPanel *sp20 = &menuMain->unk_003C[menuMain->unk_2300];
    u32 keyTrg = _getKeyTrg(menuMain->watchMenuRef, 0);
    SndIndex soundIndex;
    s32 sp18[2];
    s32 var_s2;
    s32 var_fp;
    s32 var_s3;
    s32 var_s7;
    s32 sp24;
    s32 sp28;
    s32 sp2C;
    s32 sp30;
    s32 sp34;
    s32 sp38;
    s32 i;

    if (_getMode(menuMain->watchMenuRef) == MODE_MAIN) {
        _setTitle(menuMain->watchMenuRef, menuMain->mode);
    }

    i = 0;

    switch (menuMain->mode) {
        case MODE_NAME_DEL_MES:
        case MODE_BACKUP_MES:
            i = 1;
            break;

        case MODE_NAME_DEL_YN:
        case MODE_BACKUP_YN:
            i = i || menuYN_input(&menuMain->unk_2B6C, 0);
            break;

        case MODE_SOUND:
            i = i || (menuSndSelPanel_input(&menuMain->unk_1C64, 0) != false);
            break;

        default:
            i = i || (menuMainPanel_input(sp20, 0) != false);
            i = i || (menuNameSelPanel_input(&menuMain->unk_0D2C) != false);
            i = i || (func_8004B43C(&menuMain->unk_2658, 0) != false);
            i = i || (menuNameOpPanel_input(&menuMain->unk_17B4, 0) != false);
            break;
    }

    if (i == 0) {
        return;
    }

    var_s3 = var_s7 = sp28 = sp2C = sp30 = var_fp = sp34 = sp24 = sp38 = 0;
    soundIndex = SND_INDEX_INVALID;

    switch (menuMain->mode) {
        case MODE_STORY_NS:
        case MODE_LVSEL_NS:
        case MODE_LVSEL_TQ_NS:
        case MODE_LVSEL_TA_NS:
        case MODE_VSCOM_NS:
        case MODE_VSCOM_FL_NS:
        case MODE_VSMAN_NS:
        case MODE_VSMAN_FL_NS:
        case MODE_VSMAN_TA_NS:
        case MODE_NAME_NS:
            var_s2 = 0;
            break;

        case MODE_CONT:
            var_s2 = 0;
            break;

        case MODE_NAME_DEL_MES:
        case MODE_BACKUP_MES:
            var_s2 = 0;
            break;

        case MODE_NAME:
            var_s2 = menuMain->unk_17B4.unk_008;
            break;

        case MODE_SOUND:
            var_s2 = menuMain->unk_1C64.unk_004;
            break;

        case MODE_NAME_DEL_YN:
        case MODE_BACKUP_YN:
            var_s2 = menuMain->unk_2B6C.select;
            break;

        default:
            var_s2 = menuMain->unk_000C[menuMain->unk_0008] = sp20->unk_00C;
            break;
    }

    switch (menuMain->mode) {
        case MODE_MAIN:
            if (keyTrg & (A_BUTTON | START_BUTTON)) {
                switch (tbl_5517[var_s2]) {
                    case MODE_PLAY2:
                        evs_playmax = joyResponseCheck();
                        if (evs_playmax < 2) {
                            menuMes_setStr(&menuMain->unk_31E4, _mesNoCont2);
                            sp34++;
                            soundIndex = SND_INDEX_71;
                        } else {
                            menuMain->mode = tbl_5517[var_s2];
                            menuMain->unk_0008++;
                            menuMain->unk_000C[menuMain->unk_0008] = 0;
                            var_s3++;
                            soundIndex = SND_INDEX_62;
                        }
                        break;

                    default:
                        menuMain->mode = tbl_5517[var_s2];
                        menuMain->unk_0008++;
                        menuMain->unk_000C[menuMain->unk_0008] = 0;
                        var_s3++;
                        soundIndex = SND_INDEX_62;
                        break;
                }

                if (sp34 == 0) {
                    sp34--;
                }
            } else if (keyTrg & B_BUTTON) {
                if (menuMain->unk_31E4.miBase.colorStep < 0.0f) {
                    _setFadeDir(menuMain->watchMenuRef, 1);
                    _setNextMain(menuMain->watchMenuRef, MAIN_TITLE);
                    soundIndex = SND_INDEX_68;
                }
                sp34--;
            } else if (keyTrg != 0) {
                sp34--;
            }
            break;

        case MODE_PLAY1:
            menuMain->unk_0030 = GMD_FLASH;
            menuMain->unk_002C = _n_5535[var_s2];

            if (keyTrg & (A_BUTTON | START_BUTTON)) {
                menuMain->unk_0030 = -1;
                menuMain->mode = _mode_5538[var_s2];

                switch (menuMain->mode) {
                    case MODE_VSCOM_FL_NS:
                        evs_gamemode = GMD_FLASH;
                        break;

                    case MODE_LVSEL_TQ_NS:
                        evs_gamemode = GMD_TaiQ;
                        break;

                    case MODE_LVSEL_TA_NS:
                        evs_gamemode = GMD_TIME_ATTACK;
                        break;

                    default:
                        evs_gamemode = GMD_NORMAL;
                        break;
                }

                switch (menuMain->mode) {
                    case MODE_STORY_NS:
                        evs_playcnt = 2;
                        evs_story_flg = 1;
                        evs_gamesel = GSL_VSCPU;

                        game_state_data[0].player_type = PLAYERTYPE_0;
                        game_state_data[1].player_type = PLAYERTYPE_1;
                        var_s7++;
                        break;

                    case MODE_LVSEL_NS:
                    case MODE_LVSEL_TQ_NS:
                    case MODE_LVSEL_TA_NS:
                        evs_playcnt = 1;
                        evs_story_flg = 0;
                        evs_gamesel = GSL_1PLAY;

                        game_state_data[0].player_no = 0;
                        game_state_data[0].player_type = PLAYERTYPE_0;
                        game_state_data[0].charNo = CHARANIMEMODE_M;
                        var_s7++;
                        break;

                    case MODE_VSCOM_NS:
                    case MODE_VSCOM_FL_NS:
                        evs_playcnt = 2;
                        evs_story_flg = 0;
                        evs_gamesel = GSL_VSCPU;

                        game_state_data[0].player_type = PLAYERTYPE_0;
                        game_state_data[1].player_type = PLAYERTYPE_1;
                        var_s7++;
                        break;

                    default:
                        break;
                }

                var_s3++;
                soundIndex = SND_INDEX_62;
            } else if (keyTrg & B_BUTTON) {
                menuMain->unk_0030 = -1;
                menuMain->mode = MODE_MAIN;
                menuMain->unk_0008--;
                var_s3++;
                soundIndex = SND_INDEX_68;
            }
            break;

        case MODE_PLAY2:
            menuMain->unk_002C = var_s2 + 6;
            menuMain->unk_0030 = GMD_FLASH;

            if (keyTrg & (A_BUTTON | START_BUTTON)) {
                menuMain->unk_0030 = -1;
                menuMain->mode = mode_5557[var_s2];
                evs_playcnt = 2;
                evs_story_flg = 0;
                evs_gamesel = GSL_2PLAY;

                game_state_data[0].player_type = PLAYERTYPE_0;
                game_state_data[1].player_type = PLAYERTYPE_0;

                var_s7++;
                var_s3++;
                soundIndex = SND_INDEX_62;

                switch (menuMain->mode) {
                    case MODE_VSMAN_NS:
                        evs_gamemode = GMD_NORMAL;
                        break;

                    case MODE_VSMAN_FL_NS:
                        evs_gamemode = GMD_FLASH;
                        break;

                    case MODE_VSMAN_TA_NS:
                        evs_gamemode = GMD_TIME_ATTACK;
                        break;

                    default:
                        break;
                }
            } else if (keyTrg & B_BUTTON) {
                menuMain->unk_0030 = -1;
                menuMain->mode = MODE_MAIN;
                menuMain->unk_0008--;
                var_s3++;
                soundIndex = SND_INDEX_68;
            }
            break;
        case MODE_PLAY4:
            menuMain->unk_002C = var_s2 + 0xC;
            menuMain->unk_0030 = GMD_FLASH;

            if (keyTrg & (A_BUTTON | START_BUTTON)) {
                evs_playmax = joyResponseCheck();

                if (var_s2 < evs_playmax) {
                    menuMain->mode = _mode_5570[var_s2];
                    menuMain->unk_0030 = -1;
                    menuMain->unk_0008++;
                    menuMain->unk_000C[menuMain->unk_0008] = 0;
                    evs_playcnt = 4;
                    evs_story_flg = 0;
                    evs_gamesel = GSL_4PLAY;
                    evs_gamemode = GMD_NORMAL;

                    for (i = 0; i < ARRAY_COUNT(game_state_data); i++) {
                        game_state_data[i].player_type = var_s2 < i ? PLAYERTYPE_1 : PLAYERTYPE_0;
                    }

                    var_s3++;
                    sp34--;
                    soundIndex = SND_INDEX_62;
                } else {
                    menuMes_setStr(&menuMain->unk_31E4, mes_5577[var_s2 - 1]);
                    sp34++;
                    soundIndex = SND_INDEX_71;
                }
            } else if (keyTrg & B_BUTTON) {
                if (menuMain->unk_31E4.miBase.colorStep < 0.0f) {
                    menuMain->unk_0030 = -1;
                    menuMain->mode = MODE_MAIN;
                    menuMain->unk_0008--;
                    var_s3++;
                    soundIndex = SND_INDEX_68;
                }
                sp34--;
            } else if (keyTrg != 0) {
                sp34--;
            }
            break;

        case MODE_STORY_NS:
        case MODE_LVSEL_NS:
        case MODE_LVSEL_TQ_NS:
        case MODE_LVSEL_TA_NS:
        case MODE_VSCOM_NS:
        case MODE_VSCOM_FL_NS:
        case MODE_VSMAN_NS:
        case MODE_VSMAN_FL_NS:
        case MODE_VSMAN_TA_NS:
        case MODE_NAME_NS:
            if (menuMain->unk_0D2C.unk_008 > 0) {
                MainMenuMode var_s6;
                s32 var_s4;

                for (i = 0; i < menuMain->unk_0D2C.unk_004; i++) {
                    evs_select_name_no[i] = menuMain->unk_0D2C.unk_014[i];
                }

                for (i = 0; i < ARRAY_COUNT(evs_select_name_no); i++) {
                    sp18[i] = 0;
                    if (evs_select_name_no[i] != 8) {
                        sp18[i] = 1;
                        if (!(evs_mem_data[evs_select_name_no[i]].mem_use_flg & MEM_USE_FLG_1)) {
                            sp18[i] = 2;
                        }
                    }
                }

                var_s4 = MAX(sp18[0], sp18[1]);

                switch (menuMain->mode) {
                    case MODE_STORY_NS:
                        var_s6 = _tbl_5598[var_s4][0];
                        break;

                    case MODE_NAME_NS:
                        var_s6 = _tbl_5598[var_s4][1];
                        break;

                    case MODE_LVSEL_NS:
                        var_s6 = _tblLS_5599[var_s4][0];
                        break;

                    case MODE_LVSEL_TQ_NS:
                        var_s6 = _tblLS_5599[var_s4][1];
                        break;

                    case MODE_LVSEL_TA_NS:
                        var_s6 = _tblLS_5599[var_s4][2];
                        break;

                    case MODE_VSMAN_NS:
                        var_s6 = _tblVM_5600[var_s4][0];
                        break;

                    case MODE_VSMAN_FL_NS:
                        var_s6 = _tblVM_5600[var_s4][1];
                        break;

                    case MODE_VSMAN_TA_NS:
                        var_s6 = _tblVM_5600[var_s4][2];
                        break;

                    case MODE_VSCOM_NS:
                        var_s6 = _tblVC_5601[var_s4][0];
                        break;

                    case MODE_VSCOM_FL_NS:
                        var_s6 = _tblVC_5601[var_s4][1];
                        break;

                    default:
                        break;
                }

                switch (var_s6) {
                    case MODE_OPTION:
                        menuMain->mode = MODE_OPTION;
                        var_s3++;
                        var_s7--;
                        soundIndex = SND_INDEX_68;
                        break;

                    case MODE_NAME:
                        menuMain->mode = MODE_NAME;
                        menuMain->unk_17B4.unk_008 = 0;
                        var_s7--;
                        sp24++;
                        soundIndex = SND_INDEX_62;
                        break;

                    default:
                        _setMode(menuMain->watchMenuRef, var_s6);
                        var_s3++;
                        var_s7--;
                        sp28--;
                        sp2C--;
                        soundIndex = SND_INDEX_62;
                        break;
                }

            } else if (menuMain->unk_0D2C.unk_008 < 0) {
                switch (menuMain->mode) {
                    case MODE_STORY_NS:
                    case MODE_LVSEL_NS:
                    case MODE_LVSEL_TQ_NS:
                    case MODE_LVSEL_TA_NS:
                    case MODE_VSCOM_NS:
                    case MODE_VSCOM_FL_NS:
                        menuMain->mode = MODE_PLAY1;
                        break;

                    case MODE_VSMAN_NS:
                    case MODE_VSMAN_FL_NS:
                    case MODE_VSMAN_TA_NS:
                        menuMain->mode = MODE_PLAY2;
                        break;

                    case MODE_NAME_NS:
                        menuMain->mode = MODE_OPTION;
                        break;

                    default:
                        break;
                }

                var_s3++;
                var_s7--;
                soundIndex = SND_INDEX_68;
            }
            break;

        case MODE_OPTION:
            if (keyTrg & (A_BUTTON | START_BUTTON)) {
                menuMain->mode = tbl_5648[var_s2];
                switch (menuMain->mode) {
                    case MODE_NAME_NS:
                        var_s3++;
                        var_s7++;
                        soundIndex = SND_INDEX_62;
                        break;

                    case MODE_RECORD_MS:
                    case MODE_TUTORIAL:
                    case MODE_BACKUP:
                    case MODE_MISC:
                        menuMain->unk_0008++;
                        menuMain->unk_000C[menuMain->unk_0008] = 0;
                        var_s3++;
                        soundIndex = SND_INDEX_62;
                        break;

                    default:
                        break;
                }

                switch (menuMain->mode) {
                    case MODE_RECORD_MS:
                        dm_seq_play_fade(SEQ_INDEX_13, 0x14);
                        break;

                    case MODE_COUNT:
                        menuMain->unk_000C[menuMain->unk_0008] = 3 - evs_vs_count;
                        break;

                    default:
                        break;
                }
            } else if (keyTrg & B_BUTTON) {
                menuMain->mode = MODE_MAIN;
                menuMain->unk_0008--;
                var_s3++;
                soundIndex = SND_INDEX_68;
            }
            break;

        case MODE_MISC:
            if (keyTrg & (A_BUTTON | START_BUTTON)) {
                menuMain->mode = tbl_5664[var_s2];

                // switch?
                switch (menuMain->mode) {
                    case MODE_SOUND:
                        menuMain->unk_1C64.unk_004 = evs_stereo == 0;
                        var_s3++;
                        sp38++;
                        soundIndex = SND_INDEX_62;
                        break;

                    case MODE_COUNT:
                    case MODE_SCORE:
                        menuMain->unk_0008++;
                        menuMain->unk_000C[menuMain->unk_0008] = 0;
                        var_s3++;
                        soundIndex = SND_INDEX_62;
                        break;

                    default:
                        break;
                }

                switch (menuMain->mode) {
                    case MODE_COUNT:
                        menuMain->unk_000C[menuMain->unk_0008] = 3 - evs_vs_count;
                        break;
                    case MODE_SCORE:
                        menuMain->unk_000C[menuMain->unk_0008] = evs_score_flag == 0;
                        break;

                    default:
                        break;
                }
            } else if (keyTrg & B_BUTTON) {
                _eepWritePlayer(menuMain->watchMenuRef);
                menuMain->mode = MODE_OPTION;
                menuMain->unk_0008--;
                var_s3++;
                soundIndex = SND_INDEX_68;
            }
            break;

        case MODE_SCORE:
            if (keyTrg & (A_BUTTON | START_BUTTON)) {
                evs_score_flag = var_s2 == 0;
                menuMain->mode = MODE_MISC;
                menuMain->unk_0008--;
                var_s3++;
                soundIndex = SND_INDEX_62;
            } else if (keyTrg & B_BUTTON) {
                menuMain->mode = MODE_MISC;
                menuMain->unk_0008--;
                var_s3++;
                soundIndex = SND_INDEX_68;
            }
            break;

        case MODE_PLAY4_TYPE1:
        case MODE_PLAY4_TYPE2:
        case MODE_PLAY4_TYPE3:
        case MODE_PLAY4_TYPE4:
            menuMain->unk_002C = var_s2 + 9;
            menuMain->unk_0030 = GMD_FLASH;
            if (keyTrg & (A_BUTTON | START_BUTTON)) {
                for (i = 0; i < ARRAY_COUNTU(_team_5687[var_s2]); i++) {
                    game_state_data[i].team_no = _team_5687[var_s2][i];
                }

                evs_gamemode = _game_5689[var_s2];
                var_s3++;
                sp28--;
                sp2C--;
                soundIndex = SND_INDEX_62;
                menuMain->unk_0030 = -1;
                _setMode(menuMain->watchMenuRef, _mode_5688[var_s2]);
            } else if (keyTrg & B_BUTTON) {
                menuMain->unk_0030 = -1;
                menuMain->mode = MODE_PLAY4;
                menuMain->unk_0008--;
                var_s3++;
                soundIndex = SND_INDEX_68;
            }
            break;

        case MODE_RECORD_MS:
            if (keyTrg & (A_BUTTON | START_BUTTON)) {
                menuMain->mode = _mode_5701[var_s2];
                menuMain->unk_0008++;
                menuMain->unk_000C[menuMain->unk_0008] = 0;
                var_s3++;
                soundIndex = SND_INDEX_62;
            } else if (keyTrg & B_BUTTON) {
                menuMain->mode = MODE_OPTION;
                menuMain->unk_0008--;
                var_s3++;
                soundIndex = SND_INDEX_68;
                dm_seq_play_fade(SEQ_INDEX_12, 0x14);
            }
            break;

        case MODE_RECORD_PLAY1:
        case MODE_RECORD_PLAY2:
            if (keyTrg & (A_BUTTON | START_BUTTON)) {
                const MainMenuMode *var_v0_3;

                if (menuMain->mode == MODE_RECORD_PLAY1) {
                    var_v0_3 = _mode1_5709;
                } else {
                    var_v0_3 = _mode2_5710;
                }
                _setMode(menuMain->watchMenuRef, var_v0_3[var_s2]);
                var_s3++;
                sp28--;
                sp2C--;
                soundIndex = SND_INDEX_62;
            } else if (keyTrg & B_BUTTON) {
                menuMain->mode = MODE_RECORD_MS;
                menuMain->unk_0008--;
                var_s3++;
                soundIndex = SND_INDEX_68;
            }
            break;

        case MODE_TUTORIAL:
            if (keyTrg & (A_BUTTON | START_BUTTON)) {
                if (var_s2 == 0) {
                    menuMain->mode = MODE_CONT;
                    var_s3++;
                    sp28--;
                    sp30++;
                    soundIndex = SND_INDEX_62;
                } else {
                    _setFadeDir(menuMain->watchMenuRef, 1);
                    _setNextMain(menuMain->watchMenuRef, MAIN_MANUAL);
                    evs_manual_no = var_s2 - 1;
                    soundIndex = SND_INDEX_62;
                }
            } else if (keyTrg & B_BUTTON) {
                menuMain->mode = MODE_OPTION;
                menuMain->unk_0008--;
                var_s3++;
                soundIndex = SND_INDEX_68;
            }
            break;

        case MODE_COUNT:
            if (keyTrg & (A_BUTTON | START_BUTTON)) {
                evs_vs_count = 3 - var_s2;
                menuMain->mode = MODE_MISC;
                menuMain->unk_0008--;
                var_s3++;
                sp38--;
                soundIndex = SND_INDEX_62;
            } else if (keyTrg & B_BUTTON) {
                menuMain->mode = MODE_MISC;
                menuMain->unk_0008--;
                var_s3++;
                soundIndex = SND_INDEX_68;
            }
            break;

        case MODE_CONT:
            menuCont_setFade(&menuMain->unk_2658, 1, menuMain->unk_2658.unk_3F4[0].colorTime);
            if (keyTrg & B_BUTTON) {
                menuMain->mode = MODE_TUTORIAL;
                var_s3++;
                sp28++;
                sp30--;
                soundIndex = SND_INDEX_68;
            }
            break;

        case MODE_NAME:
            if (keyTrg & (A_BUTTON | START_BUTTON)) {
                switch (tbl_5735[var_s2]) {
                    case MODE_NAME_NE2:
                        _setMode(menuMain->watchMenuRef, MODE_NAME_NE2);
                        var_s3++;
                        sp28--;
                        sp2C--;
                        sp24--;
                        soundIndex = SND_INDEX_62;
                        break;

                    case MODE_NAME_DEL_YN:
                        menuMain->mode = MODE_NAME_DEL_YN;
                        menuMain->unk_17B4.unk_250.flags.finger = false;
                        menuMain->unk_2B6C.select = 0;
                        var_fp++;
                        soundIndex = SND_INDEX_62;
                        break;

                    default:
                        break;
                }
            } else if (keyTrg & B_BUTTON) {
                menuMain->mode = MODE_NAME_NS;
                var_s7++;
                sp24--;
                soundIndex = SND_INDEX_68;
            }
            break;

        case MODE_SOUND:
            if (keyTrg & (A_BUTTON | START_BUTTON)) {
                switch (var_s2) {
                    case 0:
                    case 1:
                        evs_stereo = var_s2 == 0 ? true : false;
                        dm_audio_set_stereo(evs_stereo);
                        menuMain->mode = MODE_MISC;
                        var_s3++;
                        sp38--;
                        soundIndex = SND_INDEX_62;
                        if (menuMain->unk_0034 != SEQ_INDEX_12) {
                            dm_seq_play_fade(SEQ_INDEX_12, 0x14);
                            menuMain->unk_0034 = SEQ_INDEX_12;
                        }
                        break;

                    case 0x2:
                        dm_seq_play_fade(menuMain->unk_1C64.unk_008, 0x14);
                        menuMain->unk_0034 = menuMain->unk_1C64.unk_008;
                        break;

                    case 0x3:
                        dm_snd_play(menuMain->unk_1C64.unk_010);
                        break;
                }
            } else if (keyTrg & B_BUTTON) {
                menuMain->mode = MODE_MISC;
                var_s3++;
                sp38--;
                soundIndex = SND_INDEX_68;
                if (menuMain->unk_0034 != SEQ_INDEX_12) {
                    dm_seq_play_fade(SEQ_INDEX_12, 0x14);
                    menuMain->unk_0034 = SEQ_INDEX_12;
                }
            }
            break;

        case MODE_NAME_DEL_YN:
            menuMain->unk_2B6C.cursor.flags.finger = true;
            if (keyTrg & (A_BUTTON | START_BUTTON)) {
                switch (var_s2) {
                    case 0x0:
                        menuMain->mode = MODE_NAME_NS;
                        sp24--;
                        var_s7++;
                        var_fp--;
                        soundIndex = SND_INDEX_68;
                        break;

                    case 0x1:
                        dm_init_save_mem(&evs_mem_data[evs_select_name_no[0]]);
                        _eepErasePlayer(menuMain->watchMenuRef);
                        menuMain->mode = MODE_NAME_DEL_MES;
                        menuMain->unk_2B6C.cursor.flags.finger = false;
                        soundIndex = SND_INDEX_70;
                        break;
                }
            } else if (keyTrg & B_BUTTON) {
                menuMain->mode = MODE_NAME;
                menuMain->unk_17B4.unk_250.flags.finger = true;
                var_fp--;
            }
            break;

        case MODE_NAME_DEL_MES:
            if (keyTrg & ANY_BUTTON) {
                menuMain->mode = MODE_NAME_NS;
                sp24--;
                var_s7++;
                var_fp--;
                soundIndex = SND_INDEX_62;
            }
            break;
        case MODE_BACKUP:
            sp20->unk_418.flags.finger = true;
            if (keyTrg & (A_BUTTON | START_BUTTON)) {
                switch (var_s2) {
                    case 0x0:
                        menuMain->mode = MODE_OPTION;
                        menuMain->unk_0008--;
                        var_s3++;
                        soundIndex = SND_INDEX_68;
                        break;

                    case 0x1:
                        menuMain->mode = MODE_BACKUP_YN;
                        menuMain->unk_2B6C.select = 0;
                        sp20->unk_418.flags.finger = false;
                        var_fp++;
                        soundIndex = SND_INDEX_62;
                        break;
                }
            } else if (keyTrg & B_BUTTON) {
                menuMain->mode = MODE_OPTION;
                menuMain->unk_0008--;
                var_s3++;
                soundIndex = SND_INDEX_68;
            }
            break;

        case MODE_BACKUP_YN:
            menuMain->unk_2B6C.cursor.flags.finger = true;
            if (keyTrg & (A_BUTTON | START_BUTTON)) {
                switch (var_s2) {
                    case 0x0:
                        menuMain->mode = MODE_OPTION;
                        menuMain->unk_0008--;
                        var_fp--;
                        var_s3++;
                        soundIndex = SND_INDEX_68;
                        break;

                    case 0x1:
                        _eepEraseData(menuMain->watchMenuRef);
                        menuMain->mode = MODE_BACKUP_MES;
                        menuMain->unk_2B6C.cursor.flags.finger = false;
                        soundIndex = SND_INDEX_70;
                        break;
                }
            } else if (keyTrg & B_BUTTON) {
                menuMain->mode = MODE_BACKUP;
                var_fp--;
                soundIndex = SND_INDEX_68;
            }
            break;
        case MODE_BACKUP_MES:
            if (keyTrg & ANY_BUTTON) {
                menuMain->mode = MODE_OPTION;
                menuMain->unk_0008--;
                var_fp--;
                var_s3++;
                soundIndex = SND_INDEX_62;
            }
            break;

        default:
            break;
    }

    if (sp28 != 0) {
        menuItem_setTransDir(&menuMain->unk_2388, sp28);
    }
    if (sp2C != 0) {
        menuItem_setTransDir(&menuMain->unk_2418, sp2C);
    }
    if (var_fp != 0) {
        menuYN_setFadeDir(&menuMain->unk_2B6C, var_fp);
    }
    if (sp34 != 0) {
        menuMes_setFadeDir(&menuMain->unk_31E4, sp34);
    }
    if (sp30 < 0) {
        menuCont_setFade(&menuMain->unk_2658, -1, 1.0f);
        func_8004B2C8(&menuMain->unk_2658, -1, menuMain->unk_2658.unk_004.transTime);
    }
    if (sp24 < 0) {
        func_8004C820(&menuMain->unk_17B4, -1, 1.0f);
    }
    if (var_s7 < 0) {
        func_8004BB14(&menuMain->unk_0D2C, -1, menuMain->unk_0D2C.unk_028.transTime);
    }
    if (sp38 < 0) {
        func_8004CCD0(&menuMain->unk_1C64, -1, menuMain->unk_1C64.unk_014.transTime);
    }
    if (var_s3 != 0) {
        func_8004B774(sp20, -1, sp20->unk_028.transTime);
        menuMain->unk_2300 ^= 1;
        sp20 = &menuMain->unk_003C[menuMain->unk_2300];
    }

    if (menuMain->mode != _menuMain_lastMode) {
        if (sp30 > 0) {
            func_8004B2C8(&menuMain->unk_2658, 1, menuMain->unk_2658.unk_004.transTime);
        } else if (sp24 > 0) {
            bcopy(evs_mem_data[evs_select_name_no[0]].mem_name, menuMain->unk_17B4.unk_00C, MENUNAMEOPPANEL_UNK_LEN);
            func_8004C820(&menuMain->unk_17B4, 1, 0.0f);
        } else if (sp38 > 0) {
            func_8004CCD0(&menuMain->unk_1C64, 1, menuMain->unk_1C64.unk_014.transTime);
        } else if (var_s7 > 0) {
            s32 var_a2_8 = 1;
            f32 temp_fs0 = menuMain->unk_0D2C.unk_028.transTime;

            switch (menuMain->mode) {
                case MODE_VSMAN_NS:
                case MODE_VSMAN_FL_NS:
                case MODE_VSMAN_TA_NS:
                    var_a2_8 = 2;
                    break;

                default:
                    break;
            }

            menuNameSelPanel_clear(&menuMain->unk_0D2C, menuMain->mode != MODE_NAME_NS, var_a2_8);
            func_8004BB14(&menuMain->unk_0D2C, 1, temp_fs0);
        } else if (var_s3 != 0) {
            f32 temp_fs0_2 = sp20->unk_028.transTime;

            menuMain_initPanel(menuMain, menuMain->mode, menuMain->unk_2300, menuMain->unk_000C[menuMain->unk_0008]);
            func_8004B774(sp20, 1, temp_fs0_2);
        }
    }

    _menuMain_lastMode = menuMain->mode;
    _menuMain_lastDepth = menuMain->unk_0008;
    for (i = 0; i < ARRAY_COUNTU(_menuMain_lastSelect); i++) {
        _menuMain_lastSelect[i] = menuMain->unk_000C[i];
    }

    SND_PLAY_INDEX(soundIndex);
}

void menuMain_update(MenuMain *menuMain) {
    MenuMainPanel *temp_s5 = &menuMain->unk_003C[menuMain->unk_2300];
    SMenuItem *rootItem = _getRootItem(menuMain->watchMenuRef);
    SMenuItem *item;
    s32 i;

    for (i = 0; i < ARRAY_COUNTU(menuMain->unk_003C); i++) {
        func_8004B98C(&menuMain->unk_003C[i], rootItem);
    }

    menuNameSelPanel_update(&menuMain->unk_0D2C, rootItem);
    func_8004CA30(&menuMain->unk_17B4, rootItem);
    func_8004CFB8(&menuMain->unk_1C64, rootItem);
    menuItem_update(&menuMain->unk_2388, rootItem);

    item = &menuMain->unk_2388;
    menuMain->msgWnd.posX = item->trans[0] + item->scale[0] * 6;
    menuMain->msgWnd.posY = item->trans[1] + item->scale[1] * 6;

    if (!menuMain_setMsgStr(menuMain, menuMain->mode, menuMain->unk_000C[menuMain->unk_0008])) {
        msgWnd_update(&menuMain->msgWnd);
    }

    menuItem_update(&menuMain->unk_2418, rootItem);
    menuItem_setTransDir(&menuMain->unk_2538, menuMain->unk_0030);
    menuItem_setScaleDir(&menuMain->unk_2538, menuMain->unk_0030);
    menuItem_update(&menuMain->unk_2538, &menuMain->unk_2418);
    menuItem_update(&menuMain->unk_24A8, &menuMain->unk_2538);
    menuItem_update(&menuMain->unk_25C8, &menuMain->unk_2538);

    for (i = 0; i < ARRAY_COUNTU(menuMain->unk_25C8.color); i++) {
        menuMain->unk_25C8.color[i] = rootItem->color[i];
    }

    func_8004B488(&menuMain->unk_2658, rootItem);

    menuMain->unk_0038 = WrapF(0.0f, 1.0f, menuMain->unk_0038 + DOUBLE_LITERAL(1.0 / 128));

    menuYN_update(&menuMain->unk_2B6C, rootItem);
    menuMes_update(&menuMain->unk_31E4, rootItem);
    menuMain->unk_17B4.unk_250.flags.blink = true;
    temp_s5->unk_418.flags.blink = true;

    switch (menuMain->mode) {
        case MODE_NAME_DEL_YN:
        case MODE_NAME_DEL_MES:
            menuMain->unk_17B4.unk_250.flags.blink = false;
            break;

        case MODE_BACKUP_YN:
        case MODE_BACKUP_MES:
            temp_s5->unk_418.flags.blink = false;
            break;

        default:
            break;
    }

    switch (menuMain->mode) {
        case MODE_NAME_DEL_MES:
        case MODE_BACKUP_MES:
            menuMain->unk_2B6C.cursor.flags.blink = false;
            break;

        default:
            break;
    }
}

const s32 _pat_6137[] = {
    0, 1, 2, 3, 2, 1,
};

void menuMain_drawKaSaMaRu(MenuMain *menuMain, Gfx **gfxP) {
    Gfx *gfx = *gfxP;
    Mtx *mtx = *_getMtxPtr(menuMain->watchMenuRef);
    Vtx *vtx = *_getVtxPtr(menuMain->watchMenuRef);
    f32 temp_fs2 = menuMain->unk_2538.scaleTime * 3.0f;
    SMenuItem *item;
    s32 i;
    s32 var_s5;
    s32 var_s1_3;
    TiTexData *var_s3;
    TiTexData *temp_v0_2;
    f32 sp48[4][4];
    f32 sp88[3];
    s32 temp;

    for (i = 0; i < ARRAY_COUNTU(sp88); i++) {
        sp88[i] = WrapF(0.0f, 1.0f, menuMain->unk_0038 - (i * DOUBLE_LITERAL(0.125))) * DOUBLE_LITERAL(M_PI) * 2;
    }

    guOrtho(mtx, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 1.0f, 10.0f, 1.0f);

    gSPMatrix(gfx++, mtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);

    mtx++;

    guTranslate(mtx, 0.0f, 0.0f, -5.0f);

    gSPMatrix(gfx++, mtx, G_MTX_NOPUSH | G_MTX_MUL | G_MTX_PROJECTION);
    mtx++;

    gSPClearGeometryMode(gfx++, G_ZBUFFER | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN |
                                    G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH | G_CLIPPING);
    gDPSetTexturePersp(gfx++, G_TP_NONE);

    guRotateRPYF(sp48, 0.0f, 0.0f, sinf(sp88[0]) * (1.0f - menuMain->unk_2538.scaleTime) * 4.0f);

    i = WrapI(0, 6, menuMain->unk_0038 * 6.0f * 12.0f);
    if (!msgWnd_isSpeaking(&menuMain->msgWnd)) {
        i = 0;
    }

    item = &menuMain->unk_2418;

    var_s3 = _getTexKasa(menuMain->watchMenuRef, _pat_6137[i] + 1);
    temp_v0_2 = _getTexKasa(menuMain->watchMenuRef, 0);

    var_s5 = MIN(var_s3->info[TI_INFO_IDX_WIDTH], temp_v0_2->info[TI_INFO_IDX_WIDTH]);
    var_s1_3 = MIN(var_s3->info[TI_INFO_IDX_HEIGHT], temp_v0_2->info[TI_INFO_IDX_HEIGHT]);

    if (!menuItem_outOfScreen(item, var_s5, var_s1_3)) {
        gSPDisplayList(gfx++, fade_alpha_texture_init_dl);

        menuItem_setPrim(item, &gfx);
        sp48[3][0] = item->trans[0];
        sp48[3][1] = item->trans[1] + (sinf(sp88[0]) * temp_fs2);
        guMtxF2L(sp48, mtx);

        gSPMatrix(gfx++, mtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        mtx++;

        RectAlphaTexTile(&gfx, &vtx, var_s5, var_s1_3, var_s3->texs[TI_TEX_TEX], var_s3->info[TI_INFO_IDX_WIDTH],
                         temp_v0_2->texs[TI_TEX_TEX], temp_v0_2->info[TI_INFO_IDX_WIDTH], 0, 0, var_s5, var_s1_3, 0.0f,
                         0.0f, var_s5, var_s1_3);
    }

    item = &menuMain->unk_25C8;
    if (menuMain->unk_002C < 0xC) {
        var_s3 = _getTexMain(menuMain->watchMenuRef, 0);
        i = menuMain->unk_002C;
        temp = 12;
    } else {
#if VERSION_CN
        goto end;
#else
        var_s3 = _getTexMain(menuMain->watchMenuRef, 8);
        i = menuMain->unk_002C - 0xC;
        temp = 4;
#endif
    }

    var_s5 = var_s3->info[TI_INFO_IDX_WIDTH];
    var_s1_3 = var_s3->info[TI_INFO_IDX_HEIGHT] / temp;

    if (!menuItem_outOfScreen(item, var_s3->info[TI_INFO_IDX_WIDTH], var_s3->info[TI_INFO_IDX_HEIGHT])) {
        gSPDisplayList(gfx++, fade_normal_texture_init_dl);

        menuItem_setPrim(item, &gfx);
        sp48[3][0] = item->trans[0];
        sp48[3][1] = item->trans[1] + (sinf(sp88[2]) * temp_fs2);
        guMtxF2L(sp48, mtx);

        gSPMatrix(gfx++, mtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        mtx++;

        RectTexTile8(&gfx, &vtx, var_s3->info[TI_INFO_IDX_WIDTH], var_s3->info[TI_INFO_IDX_HEIGHT],
                     var_s3->texs[TI_TEX_TLUT], (u8 *)var_s3->texs[TI_TEX_TEX] + (var_s5 * var_s1_3 * i), 0, 0, var_s5,
                     var_s1_3, 0, 0, var_s5 * item->scale[0], var_s1_3 * item->scale[1]);
    }

    gSPDisplayList(gfx++, fade_intensity_texture_init_dl);

    for (i = 0; i < ARRAY_COUNT(sp88) - 1; i++) {
        s32 spA0;
        s32 var_fp;

        switch (i) {
            case 0:
                item = &menuMain->unk_24A8;
                var_s3 = _getTexMain(menuMain->watchMenuRef, 10);
                spA0 = 0;
                var_fp = 0;
                break;

            case 1:
                item = &menuMain->unk_2538;
                var_s3 = _getTexMain(menuMain->watchMenuRef, 9);
                spA0 = 0;
                var_fp = 0;
                break;
        }

        if (!menuItem_outOfScreen(item, var_s3->info[TI_INFO_IDX_WIDTH], var_s3->info[TI_INFO_IDX_HEIGHT])) {
            menuItem_setPrim(item, &gfx);
            sp48[3][0] = item->trans[0];
            sp48[3][1] = item->trans[1] + (sinf(sp88[i + 1]) * temp_fs2);
            guMtxF2L(sp48, mtx);

            gSPMatrix(gfx++, mtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            mtx++;

            RectTexTile4i(&gfx, &vtx, var_s3->info[TI_INFO_IDX_WIDTH], var_s3->info[TI_INFO_IDX_HEIGHT],
                          var_s3->texs[TI_TEX_TEX], 0, 0, var_s3->info[TI_INFO_IDX_WIDTH],
                          var_s3->info[TI_INFO_IDX_HEIGHT], 0, 0,
                          (var_s3->info[TI_INFO_IDX_WIDTH] + spA0) * item->scale[0],
                          (var_s3->info[TI_INFO_IDX_HEIGHT] + var_fp) * item->scale[1]);
        }
    }

#if VERSION_CN
end:
#endif

    *_getVtxPtr(menuMain->watchMenuRef) = vtx;
    *_getMtxPtr(menuMain->watchMenuRef) = mtx;

    *gfxP = gfx;
}

void menuMain_draw(MenuMain *menuMain, Gfx **gfxP) {
    Gfx *gfx = *gfxP;
    s32 i;

    gSPDisplayList(gfx++, fade_normal_texture_init_dl);

    menuItem_drawTex(&menuMain->unk_2388, &gfx, _getTexMain(menuMain->watchMenuRef, 6), 0);
    if (!menuItem_outOfScreen(&menuMain->unk_2388, menuMain->msgWnd.colStep * menuMain->msgWnd.colSize,
                              menuMain->msgWnd.rowStep * menuMain->msgWnd.rowSize)) {
        msgWnd_draw(&menuMain->msgWnd, &gfx);
    }

    menuNameOpPanel_draw(&menuMain->unk_17B4, &gfx);
    menuNameSelPanel_draw(&menuMain->unk_0D2C, &gfx);
    menuSndSelPanel_draw(&menuMain->unk_1C64, &gfx);

    for (i = 0; i < ARRAY_COUNTU(menuMain->unk_003C); i++) {
        menuMainPanel_draw(&menuMain->unk_003C[i], &gfx);
    }

    menuMain_drawKaSaMaRu(menuMain, &gfx);
    menuCont_draw(&menuMain->unk_2658, &gfx);
    menuYN_draw(&menuMain->unk_2B6C, &gfx);
    menuMes_draw(&menuMain->unk_31E4, &gfx);

    *gfxP = gfx;
}

const s32 _pos_6413[][9][2] = {
    {
        { 32, 20 },
        { 81, 7 },
        { 130, 23 },
        { 179, 17 },
        { 32, 20 },
        { 81, 20 },
        { 130, 23 },
        { 191, 14 },
        { 191, 14 },
    },
    {
        { 29, 19 },
        { 78, 6 },
        { 127, 22 },
        { 176, 16 },
        { 29, 19 },
        { 101, 2 },
        { 138, 20 },
        { 188, 13 },
        { 188, 13 },
    },
};

void func_800513F0(s32 arg0, s32 arg1, s32 arg2, s32 *xP, s32 *yP) {
    s32 var_v1 = 0;

    switch (arg2) {
        case 0:
            var_v1 = CLAMP(arg1, 1, 4);
            break;

        case 1:
            var_v1 = CLAMP(arg1, 5, 9);
            break;
    }

    var_v1--;

    *xP = _pos_6413[arg0][var_v1][0];
    *yP = _pos_6413[arg0][var_v1][1];
}

void func_80051480(MenuStory *menuStory, s32 arg1, f32 arg2) {
    SMenuItem *item = &menuStory->unk_0040;

    item->transTime = arg2;
    item->transStep = 0.05f;
    item->transRange[0][1] = item->transRange[1][1] - 240.0f;
    menuItem_setTransDir(item, arg1);
}

void func_800514C4(void *arg) {
    MenuStory *menuStory = arg;
    CharAnimeMode var_s0;

    for (var_s0 = 0; var_s0 < ARRAY_COUNTU(menuStory->unk_0038); var_s0++) {
        void *sp10 = menuStory->unk_0038[var_s0];

        animeState_load(&menuStory->unk_0280[var_s0], &sp10, var_s0);
    }

    menuStory->unk_0034 = true;
}

const s32 _posChar_6445[][2] = {
    { 0xA0, 0x2E },
    { 0xE6, 0x2E },
};
static_assert(ARRAY_COUNT(_posChar_6445) == MENUSTORY_UNK_LEN, "");

const s32 _posBgCursor_6446[][2] = {
    { -8, 0x11 },
    { 0xE8, 0x11 },
};
static_assert(ARRAY_COUNT(_posBgCursor_6446) == MENUSTORY_UNK_LEN_4, "");

const s32 _cursor_6447[][4] = {
    { 0, 0, 0x10E, 0x36 },
    { 0, 0x33, 0x10E, 0x24 },
    { 0, 0x54, 0x10E, 0x4E },
};
static_assert(ARRAY_COUNT(_cursor_6447) == MENUSTORY_UNK_LEN_3, "");

void menuStory_init(MenuStory *menuStory, struct_watchMenu *watchMenuRef, void **heapP) {
    void *heap = *heapP;
    struct_evs_mem_data *var_v1 = &evs_mem_data[evs_select_name_no[0]];
    struct_evs_mem_data_config *temp_s4 = &var_v1->config;
    s32 i;
    CharAnimeMode var_s1_3;
    SMenuItem *item;

    menuStory->watchMenuRef = watchMenuRef;

    for (i = 0; i < ARRAY_COUNTU(menuStory->unk_0004); i++) {
        menuStory->unk_0004[i][0] = var_v1->clear_stage[i][0] + 1;
        menuStory->unk_0004[i][1] = var_v1->clear_stage[i][1] + 1;
    }

    menuStory->unk_0024 = 0;
    menuStory->unk_0028[0] = temp_s4->st_no;
    menuStory->unk_0034 = false;
    menuItem_init(&menuStory->unk_0040, 0x19, 0x2F);
    menuStory->unk_0028[0] = temp_s4->st_no;
    menuItem_init(&menuStory->unk_00D0, 0x45, 0x12);

    for (i = 0; i < ARRAY_COUNTU(menuStory->unk_0160); i++) {
        menuItem_init(&menuStory->unk_0160[i], _posChar_6445[i][0], _posChar_6445[i][1]);
    }

    for (var_s1_3 = CHARANIMEMODE_M; var_s1_3 < ARRAY_COUNTU(menuStory->unk_0038); var_s1_3++) {
        size_t temp_v0_2;

        menuStory->unk_0038[var_s1_3] = ALIGN_PTR(heap);
        temp_v0_2 = animeState_getDataSize(var_s1_3);
        heap = menuStory->unk_0038[var_s1_3] + temp_v0_2;
    }

    BgTasksManager_SendTask(func_800514C4, menuStory);

    for (i = 0; i < ARRAY_COUNTU(menuStory->unk_0300); i++) {
        menuCursor_init(&menuStory->unk_0300[i], watchMenuRef, CURSOR_ITEM, 0, _posChar_6445[i][0] - 0x18,
                        _posChar_6445[i][1] - 0x2C, 0x30, 0x2F);
    }

    menuStory->unk_0028[1] = temp_s4->st_lv;
    menuSpeedAsk_init(&menuStory->unk_07C0, watchMenuRef, 3, temp_s4->st_lv, 0x45, 0x3D);
    menuSpeedItem_init(&menuStory->unk_085C, watchMenuRef, 3, 0, temp_s4->st_lv, 0x7D, 0x39, 0x34);
    menuStory->unk_085C.flags.special = temp_s4->st_sh != 0;

    menuStory->unk_0028[2] = temp_s4->st_st + 1;
    menuNumber_init(&menuStory->unk_0EC0, watchMenuRef, 1, 1, temp_s4->st_st + 1, 0x65, 0x5A);
    menuItem_init(&menuStory->unk_0F6C, 0x10, 0x6E);

    for (i = 0; i < ARRAY_COUNTU(menuStory->unk_0FFC); i++) {
        item = &menuStory->unk_0FFC[i];

        menuItem_init(item, 0, 0);
        menuItem_setColor_fade(item);
        item->colorStep = 0.05f;
    }

    for (i = 0; i < ARRAY_COUNTU(menuStory->unk_111C); i++) {
        menuItem_init(&menuStory->unk_111C[i], _posBgCursor_6446[i][0], _posBgCursor_6446[i][1]);
        menuItem_setColor_cursor(&menuStory->unk_111C[i]);
    }

    for (i = 0; i < ARRAY_COUNTU(menuStory->unk_123C); i++) {
        s32 x;
        s32 y;

        func_800513F0(menuStory->unk_0028[0], menuStory->unk_0028[2], i, &x, &y);
        menuItem_init(&menuStory->unk_123C[i], x, y);
    }

    item = &menuStory->unk_111C[0];
    item->scaleRange[0][0] = -item->scaleRange[0][0];
    item->scaleRange[1][0] = -item->scaleRange[1][0];

    for (i = 0; i < ARRAY_COUNTU(menuStory->unk_135C); i++) {
        menuCursor_init(&menuStory->unk_135C[i], watchMenuRef, CURSOR_PANEL, 0, _cursor_6447[i][0], _cursor_6447[i][1],
                        _cursor_6447[i][2], _cursor_6447[i][3]);
    }

    func_80051480(menuStory, 1, 0.0f);
    *heapP = heap;
}

void func_80051974(MenuStory *menuStory) {
    u32 keyTrg = _getKeyTrg(menuStory->watchMenuRef, 0);

    if (keyTrg & B_BUTTON) {
        _setFadeDir(menuStory->watchMenuRef, -1);
        _setNextMain(menuStory->watchMenuRef, MAIN_MENU);
        dm_snd_play(SND_INDEX_68);
    }
}

s32 func_800519CC(MenuStory *menuStory) {
    s32 var_v1 = menuStory->unk_085C.select;

    if (var_v1 == 2) {
        var_v1 += menuStory->unk_085C.flags.special;
    }
    return var_v1;
}

s32 func_800519EC(MenuStory *menuStory) {
    return menuStory->unk_0004[func_800519CC(menuStory)][menuStory->unk_0028[0]];
}

void menuStory_input(MenuStory *menuStory) {
    struct_evs_mem_data_config *temp_s5 = &evs_mem_data[evs_select_name_no[0]].config;
    u32 keyRep = _getKeyRep(menuStory->watchMenuRef, 0);
    u32 keyTrg = _getKeyTrg(menuStory->watchMenuRef, 0);
    SndIndex soundIndex = SND_INDEX_INVALID;
    bool var_s6 = false;
    s32 var_s0;
    s32 var_a1;
    long i;

    if (menuStory->unk_0040.transTime != DOUBLE_LITERAL(1)) {
        return;
    }

    var_s0 = 0;
    if ((keyRep & U_JPAD) || (keyTrg & B_BUTTON)) {
        var_s0--;
    }
    if ((keyRep & D_JPAD) || (keyTrg & (A_BUTTON | START_BUTTON))) {
        var_s0++;
    }

    var_a1 = CLAMP(menuStory->unk_0024 + var_s0, 0, 2U);

    if (var_a1 != menuStory->unk_0024) {
        soundIndex = SND_INDEX_64;
        menuStory->unk_0024 = var_a1;
    }

    if (keyTrg & 0x2000) {
        if (menuStory->unk_0024 == 1) {
            if (menuStory->unk_085C.select == 2) {
                if (!menuStory->unk_085C.flags.special) {
                    menuStory->unk_085C.flags.special = true;
                    var_s6 = true;
                } else {
                    menuStory->unk_085C.flags.special = false;
                    soundIndex = SND_INDEX_62;
                }
            }
        }
    }

    var_s0 = 0;
    if (keyRep & L_JPAD) {
        var_s0--;
    }
    if (keyRep & R_JPAD) {
        var_s0++;
    }

    switch (menuStory->unk_0024) {
        case 0x0:
            var_a1 = CLAMP(menuStory->unk_0028[menuStory->unk_0024] + var_s0, 0, 1);

            if (var_a1 != menuStory->unk_0028[menuStory->unk_0024]) {
                soundIndex = SND_INDEX_63;
                menuStory->unk_0028[menuStory->unk_0024] = var_a1;
            }
            break;

        case 0x1:
            menuSpeedItem_input(&menuStory->unk_085C, 0);
            menuStory->unk_0028[menuStory->unk_0024] = menuStory->unk_085C.select;
            break;

        case 0x2:
            i = func_800519EC(menuStory);
            var_a1 = CLAMP(menuStory->unk_0028[menuStory->unk_0024] + var_s0, 1, i);

            if (var_a1 != menuStory->unk_0028[menuStory->unk_0024]) {
                soundIndex = SND_INDEX_63;
                menuStory->unk_0028[menuStory->unk_0024] = var_a1;

                for (i = 0; i < ARRAY_COUNTU(menuStory->unk_123C); i++) {
                    SMenuItem *item = &menuStory->unk_123C[i];

                    item->transTime = 0.0f;
                    item->transRange[0][0] = item->transRange[1][0];
                    item->transRange[0][1] = item->transRange[1][1];
                }
            }
            break;
    }

    i = func_800519EC(menuStory);
    menuStory->unk_0028[2] = CLAMP(menuStory->unk_0028[2], 1, i);

    if (soundIndex <= SND_INDEX_INVALID) {
        if ((keyTrg & (A_BUTTON | START_BUTTON)) && (menuStory->unk_0024 == 2)) {
            _setFadeDir(menuStory->watchMenuRef, 1);
            _setNextMain(menuStory->watchMenuRef, MAIN_STORY);

            temp_s5->st_lv = menuStory->unk_085C.select;
            temp_s5->st_sh = menuStory->unk_085C.flags.special;
            temp_s5->st_st = menuStory->unk_0EC0.number - 1;
            temp_s5->st_no = menuStory->unk_0028[0];

            evs_story_level = func_800519CC(menuStory);

            evs_story_no = menuStory->unk_0EC0.number;

            i = (evs_story_no > 1) ? 1 : 0;
            game_state_data[0].game_retry = i;
            evs_one_game_flg = i;

            story_proc_no = menuStory->unk_0EC0.number;
            if (menuStory->unk_0028[0] == 1) {
                story_proc_no += 0xC;
            }

            evs_high_score = 0xDD18;
            evs_game_time = 0;

            if (evs_story_level < 3) {
                for (i = 0; i < 9; i++) {
                    evs_high_score = MAX(evs_high_score, evs_mem_data[i].story_data[evs_story_level].score);
                }
            }

            soundIndex = SND_INDEX_62;
        } else if ((keyTrg & B_BUTTON) && (menuStory->unk_0024 == 0)) {
            _setMode(menuStory->watchMenuRef, MODE_MAIN);
            func_80051480(menuStory, -1, 1.0f);
            soundIndex = SND_INDEX_68;
        }
    }

    if (var_s6) {
        dm_snd_play_strange_sound();
    } else {
        SND_PLAY_INDEX(soundIndex);
    }
}

// unused
const s32 RO_800B0A50[] = {
    0,
    6,
    2,
};

void menuStory_update(MenuStory *menuStory) {
    SMenuItem *rootItem = _getRootItem(menuStory->watchMenuRef);
    MenuCursor *cursor;
    SMenuItem *item;
    s32 i;
    s32 j;

    s32 sp20;
    s32 sp24;

    menuStory->unk_07C0.select = func_800519CC(menuStory);
    menuStory->unk_0EC0.number = menuStory->unk_0028[2];

    menuItem_update(&menuStory->unk_0040, rootItem);

    for (i = 0; i < ARRAY_COUNTU(menuStory->unk_0160); i++) {
        menuItem_setColorDir(&menuStory->unk_0160[i], (i == menuStory->unk_0028[0]) ? 1 : -1);
    }

    menuItem_update(&menuStory->unk_00D0, &menuStory->unk_0040);
    menuItem_updateN(menuStory->unk_0160, ARRAY_COUNTU(menuStory->unk_0160), &menuStory->unk_0040);

    for (i = 0; i < ARRAY_COUNTU(menuStory->unk_0280); i++) {
        if (!menuStory->unk_0034) {
            continue;
        }

        animeState_update(&menuStory->unk_0280[i]);

        for (j = 0; j < MENUITEM_COLOR_COUNT; j++) {
            menuStory->unk_0280[i].primColor[j] = menuStory->unk_0160[0].color[j] * 255.0f;
        }
    }

    for (i = 0; i < ARRAY_COUNTU(menuStory->unk_0300); i++) {
        cursor = &menuStory->unk_0300[i];

        menuCursor_update(cursor, &menuStory->unk_0040);
    }

    if (menuStory->unk_0024 != 1) {
        menuStory->unk_085C.cursor.miBase.colorTime = 1.0f;
    }

    menuSpeedAsk_update(&menuStory->unk_07C0, &menuStory->unk_0040);
    menuSpeedItem_update(&menuStory->unk_085C, &menuStory->unk_0040);
    menuNumber_update(&menuStory->unk_0EC0, &menuStory->unk_0040);

    menuItem_update(&menuStory->unk_0F6C, &menuStory->unk_0040);

    i = (menuStory->unk_0028[2] >= 5) ? -1 : 1;

    menuItem_setColorDir(&menuStory->unk_0FFC[0], i);
    menuItem_setColorDir(&menuStory->unk_0FFC[1], -i);
    menuItem_updateN(menuStory->unk_0FFC, ARRAY_COUNTU(menuStory->unk_0FFC), &menuStory->unk_0F6C);

    for (i = 0; i < MENUSTORY_UNK_LEN_2; i++) {
        func_800513F0(menuStory->unk_0028[0], menuStory->unk_0028[2], i, &sp20, &sp24);

        item = &menuStory->unk_123C[i];
        menuItem_setTransHi(item, sp20, sp24);
        menuItem_update(item, &menuStory->unk_0FFC[i]);
    }

    menuItem_updateN(menuStory->unk_111C, ARRAY_COUNTU(menuStory->unk_111C), &menuStory->unk_0F6C);

    item = menuStory->unk_111C;
    i = func_800519EC(menuStory);
    if ((menuStory->unk_0028[2] > 4) || (i < 5)) {
        item[1].color[3] = 0.0f;
    }
    if (menuStory->unk_0028[2] < 5) {
        item[0].color[3] = 0.0f;
    }

    for (i = 0; i < ARRAY_COUNTU(menuStory->unk_135C); i++) {
        cursor = &menuStory->unk_135C[i];

        menuCursor_update(cursor, &menuStory->unk_0040);
    }

    j = menuStory->unk_0024 == 0;
    for (i = 0; i < ARRAY_COUNTU(menuStory->unk_0300); i++) {
        menuStory->unk_135C[0].flags.cursor = j;
        menuStory->unk_0300[i].flags.blink = j;
        menuStory->unk_0300[menuStory->unk_0028[0]].flags.finger = j && (i == menuStory->unk_0028[0]);
    }

    j = menuStory->unk_0024 == 1;
    menuStory->unk_085C.flags.blink = j;
    menuStory->unk_135C[1].flags.cursor = j;
    menuStory->unk_085C.cursor.flags.finger = j;

    j = (menuStory->unk_0024 == 2);
    menuStory->unk_135C[2].flags.cursor = j;

    if (menuStory->unk_0024 == 2) {
        return;
    }

    for (i = 0; i < ARRAY_COUNTU(menuStory->unk_111C); i++) {
        //! @bug/typo? It seems likely that this should be &menuStory->unk_111C[i] instead
        item = menuStory->unk_111C;

        for (j = 0; j < MENUITEM_COLOR_COUNT - 1; j++) {
            item->color[j] = item->colorRange[1][j] * rootItem->color[j];
        }
    }
}

const s32 _map_6928[][2] = {
    { 2, 3 },
    { 2, 4 },
};

const s32 _cover_6929[][2] = {
    { 9, 0xA },
    { 9, 0xB },
};

const s32 _filter_6930[][2][9] = {
    {
        { 0x30, 0x61, 0x92, 0xC3, 0x3E7, 0x3E7, 0x3E7, 0x3E7, 0x3E7 },
        { 0, 0, 0, 0, 0x30, 0x61, 0x92, 0x3E7, 0x3E7 },
    },
    {
        { 0x30, 0x61, 0x92, 0xC3, 0x3E7, 0x3E7, 0x3E7, 0x3E7, 0x3E7 },
        { 0, 0, 0, 0, 0x30, 0x78, 0x9C, 0x3E7, 0x3E7 },
    },
};

const s32 _wchar_6931[] = {
    7,
    8,
};

void menuStory_draw(MenuStory *menuStory, Gfx **gfxP) {
    Gfx *gfx = *gfxP;
    SMenuItem *item;
    void *sp38[3];
    s32 pad[3] UNUSED;
    s32 var_s2_2;
    s32 i;
    TiTexData *temp_s1;
    TiTexData *temp_v0;

    gSPDisplayList(gfx++, fade_normal_texture_init_dl);

    temp_v0 = _getTexStory(menuStory->watchMenuRef, 6);
    menuItem_drawTex(&menuStory->unk_0040, &gfx, temp_v0, 0);

    for (i = 0; i < MENUSTORY_UNK_LEN; i++) {
        f32 temp_fs1;
        f32 temp_fs0;

        if (!menuStory->unk_0034) {
            continue;
        }

        item = &menuStory->unk_0160[i];

        temp_fs1 = item->trans[0];
        temp_fs0 = item->trans[1];
        item->trans[0] -= 26.0f;
        item->trans[1] -= 48.0f;

        if (!menuItem_outOfScreen(item, 0x40, 0x40)) {
            s32 temp_ft1 = item->colorTime * 255.0f;

            gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, temp_ft1);

            gSPDisplayList(gfx++, fade_intensity_texture_init_dl);

            temp_v0 = _getTexStory(menuStory->watchMenuRef, 0xC);
            tiStretchTexTile(&gfx, temp_v0, false, 0, 0, temp_v0->info[TI_INFO_IDX_WIDTH],
                             temp_v0->info[TI_INFO_IDX_HEIGHT], item->trans[0], item->trans[1],
                             temp_v0->info[TI_INFO_IDX_WIDTH], temp_v0->info[TI_INFO_IDX_HEIGHT]);

            item->trans[0] = temp_fs1 + 5.0f;
            item->trans[1] = temp_fs0 + 2.0f;

            gSPDisplayList(gfx++, fade_shadow_texture_init_dl);

            gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, temp_ft1 >> 1);

            animeState_draw(&menuStory->unk_0280[i], &gfx, item->trans[0], item->trans[1], 1.0f, 1.0f);
            item->trans[0] = temp_fs1;
            item->trans[1] = temp_fs0;

            gSPDisplayList(gfx++, fade_normal_texture_init_dl);

            menuItem_setPrim(item, &gfx);
            animeState_draw(&menuStory->unk_0280[i], &gfx, item->trans[0], item->trans[1], 1.0f, 1.0f);
        }

        item->trans[0] = temp_fs1;
        item->trans[1] = temp_fs0;
    }

    gSPDisplayList(gfx++, fade_normal_texture_init_dl);
    gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);

    for (i = 0; i < ARRAY_COUNTU(menuStory->unk_0FFC); i++) {
        temp_v0 = _getTexStory(menuStory->watchMenuRef, _map_6928[menuStory->unk_0028[0]][i]);
        menuItem_drawTex(&menuStory->unk_0FFC[i], &gfx, temp_v0, 0);
    }

    gSPDisplayList(gfx++, fade_intensity_texture_init_dl);

    for (i = 0; i < MENUSTORY_UNK_LEN_2; i++) {
        s32 temp_s2;
        s32 var_s0_2;
        s32 tempIndex;

        item = &menuStory->unk_0FFC[i];

        temp_v0 = _getTexStory(menuStory->watchMenuRef, _cover_6929[menuStory->unk_0028[0]][i]);

        tempIndex = func_800519EC(menuStory);

        var_s0_2 = _filter_6930[menuStory->unk_0028[0]][i][tempIndex - 1];
        var_s0_2 = MIN(var_s0_2, temp_v0->info[TI_INFO_IDX_WIDTH] - 1);

        temp_s2 = temp_v0->info[TI_INFO_IDX_WIDTH] - var_s0_2;
        if (!menuItem_outOfScreen(item, temp_s2, temp_v0->info[TI_INFO_IDX_HEIGHT])) {
            gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, item->color[3] * 127.0f);

            tiStretchTexTile(&gfx, temp_v0, false, var_s0_2, 0, temp_s2, temp_v0->info[TI_INFO_IDX_HEIGHT],
                             item->trans[0] + var_s0_2, item->trans[1], temp_s2, temp_v0->info[TI_INFO_IDX_HEIGHT]);
        }
    }

    gSPDisplayList(gfx++, fade_normal_texture_init_dl);
    gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);

    for (i = 0; i < ARRAY_COUNTU(menuStory->unk_123C); i++) {
        temp_v0 = _getTexStory(menuStory->watchMenuRef, _wchar_6931[menuStory->unk_0028[0]]);
        menuItem_drawTex(&menuStory->unk_123C[i], &gfx, temp_v0, 0);
    }

    gDPSetRenderMode(gfx++, G_RM_OPA_SURF, G_RM_OPA_SURF2);

    temp_v0 = _getTexStory(menuStory->watchMenuRef, 5);
    var_s2_2 = 0;
    for (i = 0; i < ARRAY_COUNTU(menuStory->unk_111C); i++) {
        var_s2_2 += menuItem_drawTex(&menuStory->unk_111C[i], &gfx, temp_v0, var_s2_2);
    }

    sp38[0] = &menuStory->unk_0EC0;
    menuNumber_draw((void *)sp38, 1, &gfx);

    sp38[0] = &menuStory->unk_07C0;
    menuSpeedAsk_draw((void *)sp38, 1, &gfx);

    sp38[0] = &menuStory->unk_085C;
    menuSpeedItem_draw1((void *)sp38, 1, &gfx);

    gSPDisplayList(gfx++, fade_alpha_texture_init_dl);

    temp_v0 = _getTexStory(menuStory->watchMenuRef, 1);
    temp_s1 = _getTexStory(menuStory->watchMenuRef, 0);
    menuItem_drawAlphaItem(&menuStory->unk_00D0, &gfx, temp_v0, temp_s1, false, 2, menuStory->unk_0028[0]);

    for (i = 0; i < ARRAY_COUNTU(menuStory->unk_135C); i++) {
        sp38[i] = &menuStory->unk_135C[i];
    }

    menuCursor_draw((void *)sp38, ARRAY_COUNTU(menuStory->unk_135C), &gfx);

    sp38[0] = &menuStory->unk_085C;
    menuSpeedItem_draw2((void *)sp38, 1, &gfx);

    *gfxP = gfx;
}

void func_800529FC(MenuLvSel *menuLvSel, s32 arg1, f32 arg2) {
    SMenuItem *item = &menuLvSel->unk_0008;

    item->transTime = arg2;
    item->transStep = 0.05f;
    item->transRange[0][1] = item->transRange[1][1] - 240.0f;
    menuItem_setTransDir(item, arg1);
}

const s32 _cursor_7325[][4] = {
    { 0, 0, 0x10E, 0x22 },
    { 0, 0x1F, 0x10E, 0x22 },
    { 0, 0x3E, 0x10E, 0x1E },
};
static_assert(ARRAY_COUNT(_cursor_7325) == MENULVSEL_UNK_162C_LEN, "");

void menuLvSel_init(MenuLvSel *menuLvSel, struct_watchMenu *watchMenuRef, void **heapP) {
    struct_evs_mem_data *temp_s0 = &evs_mem_data[evs_select_name_no[0]];
    void *heap = *heapP;
    struct_evs_mem_data_config *temp_s2 = &temp_s0->config;
    s32 i;

    menuLvSel->watchMenuRef = watchMenuRef;

    menuLvSel->unk_0004 = _getMode(watchMenuRef);
    menuLvSel->unk_256C = 0;
    menuLvSel->unk_2570 = 20;

    for (i = 0; i < ARRAY_COUNTU(temp_s0->level_data); i++) {
        menuLvSel->unk_2570 = MAX(menuLvSel->unk_2570, temp_s0->level_data[i].c_level);
    }

    menuLvSel->unk_2570 = MIN(21, menuLvSel->unk_2570);

    menuItem_init(&menuLvSel->unk_0008, 0x19, 0x2F);
    menuItem_init(menuLvSel->unk_0098, 0, 0);
    menuItem_init(&menuLvSel->unk_0098[1], 0, 0x5F);

    switch (menuLvSel->unk_0004) {
        case MODE_LVSEL_TQ:
            menuSpeedAsk_init(&menuLvSel->gameLvlIcon, watchMenuRef, 3, temp_s2->p1_tq_lv, 0x44, 9);
            menuSpeedItem_init(&menuLvSel->gameLvlSelector, watchMenuRef, 3, 0, temp_s2->p1_tq_lv, 0x82, 5, 0x2E);
            break;

        case MODE_LVSEL_TA:
            menuSpeedAsk_init(&menuLvSel->gameLvlIcon, watchMenuRef, 3, temp_s2->p1_ta_lv, 0x44, 9);
            menuSpeedItem_init(&menuLvSel->gameLvlSelector, watchMenuRef, 3, 0, temp_s2->p1_ta_lv, 0x82, 5, 0x2E);
            break;

        case MODE_LVSEL:
            if (temp_s2->p1_lv <= menuLvSel->unk_2570) {
                i = temp_s2->p1_lv;
            } else {
                i = menuLvSel->unk_2570;
            }

            menuNumber_init(&menuLvSel->virusLvlNumber, watchMenuRef, 1, 2, i, 0x59, 5);
            menuLvGauge_init(&menuLvSel->virusLvlGauge, watchMenuRef, 2, 0, i, 0x99, 0xF);
            menuItem_setColorLow(&menuLvSel->virusLvlGauge.miBase, 1.0f, 0.5f);
            menuLvSel->virusLvlGauge.levelMax = menuLvSel->unk_2570;
            break;

        default:
            break;
    }

    menuSpeedAsk_init(&menuLvSel->speedIcon, watchMenuRef, 1, temp_s2->p1_sp, 0x44, 0x28);
    menuSpeedItem_init(&menuLvSel->speedSelector, watchMenuRef, 1, 0, temp_s2->p1_sp, 0x82, 0x24, 0x2E);

    menuItem_setColorLow(&menuLvSel->speedSelector.miBase, 1.0f, 0.5f);
    menuMusicItem_init(&menuLvSel->musicSelector, watchMenuRef, temp_s2->p1_m, 0x46, 0x46);
    menuBottle_init(&menuLvSel->bottle, watchMenuRef, 0x19, 7);

    for (i = 0; i < ARRAY_COUNTU(menuLvSel->unk_162C); i++) {
        menuCursor_init(&menuLvSel->unk_162C[i], watchMenuRef, CURSOR_PANEL, 0, _cursor_7325[i][0], _cursor_7325[i][1],
                        _cursor_7325[i][2], _cursor_7325[i][3]);
    }

    menuItem_init(&menuLvSel->capsuleSpeedIcon, 0x56, 7);
    menuItem_init(&menuLvSel->musicIcon, 0x99, 8);
    func_800529FC(menuLvSel, 1, 0.0f);

    *heapP = heap;
}

// unused
const s32 RO_800B0B44[] = {
    3,
    1,
    4,
};

void func_80052DF0(MenuLvSel *menuLvSel) {
    u32 keyTrg = _getKeyTrg(menuLvSel->watchMenuRef, 0);

    if (keyTrg & B_BUTTON) {
        _setFadeDir(menuLvSel->watchMenuRef, -1);
        _setNextMain(menuLvSel->watchMenuRef, MAIN_MENU);
        dm_snd_play(SND_INDEX_68);
    }
}

void menuLvSel_input(MenuLvSel *menuLvSel) {
    struct_evs_mem_data_config *temp_s5 = &evs_mem_data[evs_select_name_no[0]].config;
    u32 keyRep = _getKeyRep(menuLvSel->watchMenuRef, 0);
    SndIndex sndIndex = SND_INDEX_INVALID;
    struct_game_state_data *gameStateData = &game_state_data[0];
    u32 keyTrg = _getKeyTrg(menuLvSel->watchMenuRef, 0);
    s32 var_a0;
    s32 var_v1;

    if ((menuLvSel->unk_0008.transStep < 0.0f) || (menuLvSel->unk_0008.transTime < 1.0f)) {
        return;
    }

    var_v1 = 0;
    if ((keyRep & U_JPAD) || (keyTrg & B_BUTTON)) {
        var_v1--;
    }
    if ((keyRep & D_JPAD) || (keyTrg & (A_BUTTON | START_BUTTON))) {
        var_v1++;
    }

    var_a0 = CLAMP(menuLvSel->unk_256C + var_v1, 0, 2);
    if (var_a0 != menuLvSel->unk_256C) {
        sndIndex = SND_INDEX_64;
        menuLvSel->unk_256C = var_a0;
    }

    switch (menuLvSel->unk_256C) {
        case 0x0:
            switch (menuLvSel->unk_0004) {
                case MODE_LVSEL_TQ:
                case MODE_LVSEL_TA:
                    menuSpeedItem_input(&menuLvSel->gameLvlSelector, 0);
                    break;

                case MODE_LVSEL:
                    menuLvGauge_input(&menuLvSel->virusLvlGauge, 0);
                    break;

                default:
                    break;
            }
            break;

        case 0x1:
            menuSpeedItem_input(&menuLvSel->speedSelector, 0);
            break;

        case 0x2:
            menuMusicItem_input(&menuLvSel->musicSelector, 0);
            break;
    }

    if (sndIndex >= SND_INDEX_INVALID + 1) {
        dm_snd_play(sndIndex);
        return;
    }

    if ((keyTrg & (A_BUTTON | START_BUTTON)) && (menuLvSel->unk_256C == 2)) {
        _setFadeDir(menuLvSel->watchMenuRef, 1);
        _setNextMain(menuLvSel->watchMenuRef, MAIN_12);

        switch (menuLvSel->unk_0004) {
            case MODE_LVSEL:
                gameStateData->virus_level = menuLvSel->virusLvlGauge.level;
                gameStateData->cap_def_speed = menuLvSel->speedSelector.select;
                temp_s5->p1_lv = menuLvSel->virusLvlGauge.level;
                break;

            case MODE_LVSEL_TQ:
                gameStateData->virus_level = 0xA;
                gameStateData->cap_def_speed = menuLvSel->speedSelector.select;
                gameStateData->game_level = menuLvSel->gameLvlSelector.select;
                temp_s5->p1_tq_lv = menuLvSel->gameLvlSelector.select;
                break;

            case MODE_LVSEL_TA:
                gameStateData->virus_level = _timeAttack_levelTable[menuLvSel->gameLvlSelector.select];
                gameStateData->cap_def_speed = menuLvSel->speedSelector.select;
                gameStateData->game_level = menuLvSel->gameLvlSelector.select;
                temp_s5->p1_ta_lv = menuLvSel->gameLvlSelector.select;
                break;

            default:
                break;
        }

        temp_s5->p1_sp = menuLvSel->speedSelector.select;
        temp_s5->p1_m = menuLvSel->musicSelector.select;

        evs_seqnumb = menuLvSel->musicSelector.select;
        evs_game_time = 0;
        evs_seqence = evs_seqnumb != 4;
        sndIndex = SND_INDEX_62;
    } else if ((keyTrg & B_BUTTON) && (menuLvSel->unk_256C == 0)) {
        _setMode(menuLvSel->watchMenuRef, MODE_MAIN);
        func_800529FC(menuLvSel, -1, 1.0f);
        if (menuLvSel->musicSelector.playNo >= 0) {
            dm_seq_play_fade(0xC, 0x14);
        }
        sndIndex = SND_INDEX_68;
    }

    if (sndIndex > SND_INDEX_INVALID) {
        dm_snd_play(sndIndex);
    }
}

void menuLvSel_update(MenuLvSel *menuLvSel) {
    SMenuItem *rootItem = _getRootItem(menuLvSel->watchMenuRef);
    s32 i;

    switch (menuLvSel->unk_0004) {
        case MODE_LVSEL_TQ:
            menuLvSel->bottle.level = menuLvSel->unk_0004;
            menuLvSel->gameLvlIcon.select = menuLvSel->gameLvlSelector.select;
            break;

        case MODE_LVSEL_TA:
            menuLvSel->gameLvlIcon.select = menuLvSel->gameLvlSelector.select;
            menuLvSel->bottle.level = _timeAttack_levelTable[menuLvSel->gameLvlSelector.select];
            break;

        case MODE_LVSEL:
            menuLvSel->virusLvlNumber.number = menuLvSel->virusLvlGauge.level;
            menuLvSel->bottle.level = menuLvSel->virusLvlGauge.level;
            break;

        default:
            break;
    }

    menuLvSel->speedIcon.select = menuLvSel->speedSelector.select;
    menuItem_update(&menuLvSel->unk_0008, rootItem);
    menuItem_updateN(menuLvSel->unk_0098, ARRAY_COUNT(menuLvSel->unk_0098), &menuLvSel->unk_0008);

    switch (menuLvSel->unk_0004) {
        case MODE_LVSEL_TQ:
        case MODE_LVSEL_TA:
            menuSpeedAsk_update(&menuLvSel->gameLvlIcon, &menuLvSel->unk_0008);
            menuSpeedItem_update(&menuLvSel->gameLvlSelector, &menuLvSel->unk_0008);
            break;

        case MODE_LVSEL:
            menuNumber_update(&menuLvSel->virusLvlNumber, &menuLvSel->unk_0008);
            menuLvGauge_update(&menuLvSel->virusLvlGauge, &menuLvSel->unk_0008);
            break;

        default:
            break;
    }

    menuSpeedAsk_update(&menuLvSel->speedIcon, &menuLvSel->unk_0008);
    menuSpeedItem_update(&menuLvSel->speedSelector, &menuLvSel->unk_0008);
    menuMusicItem_update(&menuLvSel->musicSelector, &menuLvSel->unk_0008);
    menuBottle_update(&menuLvSel->bottle, &menuLvSel->unk_0098[1]);

    for (i = 0; i < ARRAY_COUNTU(menuLvSel->unk_162C); i++) {
        menuCursor_update(&menuLvSel->unk_162C[i], &menuLvSel->unk_0098[0]);
    }

    menuItem_update(&menuLvSel->capsuleSpeedIcon, &menuLvSel->unk_0098[1]);
    menuItem_update(&menuLvSel->musicIcon, &menuLvSel->unk_0098[1]);

    i = menuLvSel->unk_256C == 0;
    switch (menuLvSel->unk_0004) {
        case MODE_LVSEL:
            menuLvSel->virusLvlGauge.cursor.flags.finger = i;
            menuLvSel->virusLvlGauge.cursor.flags.blink = i;
            break;

        case MODE_LVSEL_TQ:
        case MODE_LVSEL_TA:
            menuLvSel->gameLvlSelector.flags.blink = i;
            menuLvSel->gameLvlSelector.cursor.flags.finger = i;
            break;

        default:
            break;
    }
    menuLvSel->unk_162C[0].flags.cursor = i;

    i = menuLvSel->unk_256C == 1;
    menuLvSel->speedSelector.flags.blink = i;
    menuLvSel->speedSelector.cursor.flags.finger = i;
    menuLvSel->unk_162C[1].flags.cursor = i;

    i = menuLvSel->unk_256C == 2;
    menuLvSel->musicSelector.cursor.flags.finger = i;
    menuLvSel->musicSelector.flags.blink = i;
    menuLvSel->unk_162C[2].flags.cursor = i;
}

void menuLvSel_draw(MenuLvSel *menuLvSel, Gfx **gfxP) {
    void *arr[8];
    Gfx *gfx = *gfxP;
    s32 i;
    TiTexData *a2;

    gSPDisplayList(gfx++, fade_normal_texture_init_dl);

    switch (menuLvSel->unk_0004) {
        case MODE_LVSEL:
            a2 = _getTexLevel(menuLvSel->watchMenuRef, 4);
            break;

        case MODE_LVSEL_TQ:
        case MODE_LVSEL_TA:
            a2 = _getTexLevel(menuLvSel->watchMenuRef, 5);
            break;

        default:
            UNREACHABLE;
            break;
    }

    menuItem_drawTex(&menuLvSel->unk_0098[0], &gfx, a2, 0);
    menuItem_drawTex(&menuLvSel->unk_0098[1], &gfx, _getTexLevel(menuLvSel->watchMenuRef, 1), 0);
    if (menuLvSel->speedSelector.select > 0) {
        menuItem_drawItem(&menuLvSel->capsuleSpeedIcon, &gfx, _getTexLevel(menuLvSel->watchMenuRef, 3), 0, 2,
                          menuLvSel->speedSelector.select - 1);
    }
    if (menuLvSel->musicSelector.select < 4) {
        menuItem_drawItem(&menuLvSel->musicIcon, &gfx, _getTexLevel(menuLvSel->watchMenuRef, 2), 0, 4,
                          menuLvSel->musicSelector.select);
    }

    switch (menuLvSel->unk_0004) {
        case MODE_LVSEL:
            if (menuLvSel->unk_2570 >= 21) {
                f32 temp_fs0 = menuLvSel->unk_0098[0].trans[0];

                menuLvSel->unk_0098[0].trans[0] = temp_fs0 + 222.0f;
                menuItem_drawTex(&menuLvSel->unk_0098[0], &gfx, _getTexLevel(menuLvSel->watchMenuRef, 6), 0);
                menuLvSel->unk_0098[0].trans[0] = temp_fs0;
            }
            break;

        default:
            break;
    }

    arr[0] = &menuLvSel->musicSelector;
    menuMusicItem_draw1((MenuMusicItem **)&arr[0], 1, &gfx);
    arr[1] = &menuLvSel->speedIcon;
    arr[2] = &menuLvSel->speedSelector;
    menuSpeedAsk_draw((MenuSpeedAsk **)&arr[1], 1, &gfx);
    menuSpeedItem_draw1((MenuSpeedItem **)&arr[2], 1, &gfx);

    switch (menuLvSel->unk_0004) {
        case MODE_LVSEL_TQ:
        case MODE_LVSEL_TA:
            arr[3] = &menuLvSel->gameLvlIcon;
            arr[4] = &menuLvSel->gameLvlSelector;
            menuSpeedAsk_draw((MenuSpeedAsk **)&arr[3], 1, &gfx);
            menuSpeedItem_draw1((MenuSpeedItem **)&arr[4], 1, &gfx);
            break;

        case MODE_LVSEL:
            arr[3] = &menuLvSel->virusLvlNumber;
            arr[4] = &menuLvSel->virusLvlGauge;
            menuNumber_draw((void *)&arr[3], 1, &gfx);
            menuLvGauge_draw1((void *)&arr[4], 1, &gfx);
            break;

        default:
            break;
    }

    for (i = 0; i < ARRAY_COUNTU(menuLvSel->unk_162C); i++) {
        arr[5 + i] = &menuLvSel->unk_162C[i];
    }

    menuCursor_draw((MenuCursor **)&arr[5], ARRAY_COUNTU(menuLvSel->unk_162C), &gfx);

    menuMusicItem_draw2((MenuMusicItem **)&arr[0], 1, &gfx);
    menuSpeedItem_draw2((MenuSpeedItem **)&arr[2], 1, &gfx);

    switch (menuLvSel->unk_0004) {
        case MODE_LVSEL_TQ:
        case MODE_LVSEL_TA:
            menuSpeedItem_draw2((void *)&arr[4], 1, &gfx);
            break;

        case MODE_LVSEL:
            menuLvGauge_draw2((void *)&arr[4], 1, &gfx);
            break;

        default:
            break;
    }

    menuBottle_draw(&menuLvSel->bottle, &gfx);

    *gfxP = gfx;
}

void func_8005380C(MenuChSel *menuChSel, s32 arg1, f32 arg2) {
    SMenuItem *item = &menuChSel->unk_0074;

    item->transTime = arg2;
    item->transStep = 0.05f;
    item->transRange[0][1] = item->transRange[1][1] - 240.0f;
    menuItem_setTransDir(item, arg1);
}

const s32 _pos_7882[][2] = { { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 } };

void menuChSel_init(MenuChSel *menuChSel, struct_watchMenu *watchMenuRef, void **heapP UNUSED) {
    MainMenuMode mode = _getMode(watchMenuRef);
    s32 i;

    menuChSel->watchMenuRef = watchMenuRef;
    menuChSel->unk_0028 = -1;
    menuChSel->unk_002C = 0;
    menuChSel->unk_0030 = 0;
    menuChSel->unk_0034 = -1;
    menuChSel->unk_0038 = -1;

    switch (mode) {
        case MODE_VSCOM_CH:
        case MODE_VSCOM_FL_CH:
        case MODE_VSMAN_CH:
        case MODE_VSMAN_FL_CH:
        case MODE_VSMAN_TA_CH:
            menuChSel->unk_0004 = 2;
            break;

        case MODE_PLAY4_CH:
        case MODE_PLAY4_TB_CH:
        case MODE_PLAY4_FL_CH:
            menuChSel->unk_0004 = 4;
            break;

        default:
            break;
    }

    menuChSel->unk_003C = 0;
    menuChSel->unk_0060 = 0;
    menuItem_init(&menuChSel->unk_0104, 0xF9, 0x16);
    menuItem_setColor_fade(&menuChSel->unk_0104);

    menuChSel->unk_0104.colorTime = 0.0f;

    for (i = 0; i < menuChSel->unk_0004; i++) {
        s32 var_s3;
        struct_evs_mem_data_config *temp;

        if (game_state_data[i].player_type == PLAYERTYPE_0) {
            menuChSel->unk_0040[menuChSel->unk_003C] = i;
            menuChSel->unk_003C += 1;
            menuChSel->unk_0050[i] = 0;
        } else {
            menuChSel->unk_0064[menuChSel->unk_0060] = i;
            menuChSel->unk_0060 += 1;
            menuChSel->unk_0050[i] = 1;
        }

        switch (mode) {
            case MODE_VSCOM_CH:
            case MODE_VSCOM_FL_CH:
                temp = &evs_mem_data[evs_select_name_no[0]].config;
                var_s3 = temp->vc_no[i];
                break;

            case MODE_VSMAN_CH:
            case MODE_VSMAN_FL_CH:
            case MODE_VSMAN_TA_CH:
                temp = &evs_mem_data[evs_select_name_no[i]].config;
                var_s3 = temp->vm_no;
                break;

            case MODE_PLAY4_CH:
            case MODE_PLAY4_TB_CH:
            case MODE_PLAY4_FL_CH:
                var_s3 = evs_cfg_4p.p4_no[i];
                break;

            default:
                break;
        }

        menuChSel->unk_0008[i] = var_s3;
        menuChSel->unk_0018[i] = -1;
    }

    for (i = 0; i < menuChSel->unk_0004; i++) {
        MenuCursor *cursor = &menuChSel->unk_23CC[i];

        menuCursor_init2(cursor, watchMenuRef, CURSOR_ITEM, menuChSel->unk_003C, menuChSel->unk_0060, i, 0, 0, 0x2C,
                         0x2C);
        cursor->miPlayer.transRange[0][0] = cursor->miPlayer.transRange[1][0] = _pos_7882[i][0];
        cursor->miPlayer.transRange[0][1] = cursor->miPlayer.transRange[1][1] = _pos_7882[i][1];
    }

    menuItem_init(&menuChSel->unk_0074, 0x12, 0x2F);

    for (i = 0; i < MENUCH_SEL_UNK_LEN; i++) {
        menuItem_init(&menuChSel->unk_0194[i], ((i % 5) * 0x36) + 0xC, ((i / 5) * 0x35) + 0xC);
        menuItem_init(&menuChSel->unk_0A04[i], 3, 3);
        menuItem_setColorHi(&menuChSel->unk_0A04[i], 0.0f, 0.0f);
        menuItem_setColorLow(&menuChSel->unk_0A04[i], 0.0f, 0.5f);
    }

    for (i = 0; i < ARRAY_COUNTU(menuChSel->unk_1274); i++) {
        menuComLvPanel_init(&menuChSel->unk_1274[i], watchMenuRef, 0, -6, 0x1E);
        menuComLvPanel_setFade(&menuChSel->unk_1274[i], -1, 0.0f);
    }

    func_8005380C(menuChSel, 1, 0.0f);
}

bool menuChSel_checkSelected(MenuChSel *menuChSel, s32 arg1, s32 arg2, s32 arg3) {
    s32 i;

    for (i = 0; i < menuChSel->unk_0004; i++) {
        if ((i != arg1) && (menuChSel->unk_0008[i] == arg2)) {
            if (menuChSel->unk_0018[i] >= arg3) {
                return true;
            }
        }
    }

    return false;
}

bool func_80053C84(MenuChSel *menuChSel, s32 arg1, s32 arg2) {
    if (menuChSel_checkSelected(menuChSel, arg1, arg2, 0)) {
        return true;
    }

    if ((arg2 == 0xD) && (evs_secret_flg[1] == 0)) {
        return true;
    }

    if ((arg2 == 0xE) && (evs_secret_flg[0] == 0)) {
        return true;
    }

    return false;
}

void menuChSel_input1(MenuChSel *menuChSel, s32 arg1, s32 arg2) {
    u32 keyRep = _getKeyRep(menuChSel->watchMenuRef, arg2);
    u32 keyTrg = _getKeyTrg(menuChSel->watchMenuRef, arg2);
    SndIndex soundIndex = SND_INDEX_INVALID;
    u32 keyLvl = _getKeyLvl(menuChSel->watchMenuRef, arg2);
    s32 var_a0;

    switch (menuChSel->unk_0018[arg1]) {
        case -0x1:
            menuChSel->unk_0018[arg1] = 0;

            FALLTHROUGH;
        case 0x0:
            while (func_80053C84(menuChSel, arg1, menuChSel->unk_0008[arg1])) {
                menuChSel->unk_0008[arg1] = WrapI(0, 0xF, menuChSel->unk_0008[arg1] + 1);
            }

            if (keyTrg & (A_BUTTON | START_BUTTON)) {
                if ((keyLvl & L_TRIG) && (menuChSel->unk_0060 != 0)) {
                    var_a0 = 0;
                    if ((menuChSel->unk_002C == 0) || (menuChSel->unk_0030 != 1)) {
                        var_a0 = 1;
                    }
                    menuChSel->unk_002C = var_a0;
                    menuChSel->unk_0030 = 1;
                    soundIndex = SND_INDEX_62;
                } else {
                    menuChSel->unk_0018[arg1]++;
                    soundIndex = SND_INDEX_62;
                }
            } else if (keyTrg & B_BUTTON) {
                if ((keyLvl & L_TRIG) && (menuChSel->unk_0060 != 0)) {
                    var_a0 = 0;
                    if ((menuChSel->unk_002C == 0) || (menuChSel->unk_0030 != 2)) {
                        var_a0 = 1;
                    }
                    menuChSel->unk_002C = var_a0;
                    menuChSel->unk_0030 = 2;
                    soundIndex = SND_INDEX_62;
                } else {
                    menuChSel->unk_0018[arg1]--;
                    soundIndex = SND_INDEX_68;
                }
            } else {
                s32 var_a2 = menuChSel->unk_0008[arg1];
                s32 temp_s4_2 = 0;
                s32 temp_s6 = 0;

                if (keyRep & L_JPAD) {
                    temp_s6--;
                }
                if (keyRep & R_JPAD) {
                    temp_s6++;
                }

                if (keyRep & U_JPAD) {
                    temp_s4_2--;
                }
                if (keyRep & D_JPAD) {
                    temp_s4_2++;
                }

                if (((temp_s6 != 0) || (temp_s4_2 != 0))) {
                    s32 var_s2 = menuChSel->unk_0008[arg1] % 5;
                    s32 var_s1 = menuChSel->unk_0008[arg1] / 5;
                    s32 temp_s0;

                    do {
                        var_s2 = WrapI(0, 5, var_s2 + temp_s6);
                        var_s1 = WrapI(0, 3, var_s1 + temp_s4_2);
                        temp_s0 = var_s2 + (var_s1 * 5);
                    } while (func_80053C84(menuChSel, arg1, temp_s0));
                    var_a2 = temp_s0;
                }

                if (var_a2 != menuChSel->unk_0008[arg1]) {
                    menuChSel->unk_0008[arg1] = var_a2;
                    soundIndex = SND_INDEX_64;
                }
            }
            break;

        case 0x1:
            if (keyTrg & B_BUTTON) {
                menuChSel->unk_0018[arg1] = 0;
                soundIndex = SND_INDEX_68;
            }
            break;
    }

    SND_PLAY_INDEX(soundIndex);
}

void menuChSel_inputMan(MenuChSel *menuChSel) {
    s32 var_s3;
    s32 var_s4;
    s32 i;

    var_s3 = 0;
    var_s4 = 0;

    for (i = 0; i < menuChSel->unk_003C; i++) {
        menuChSel_input1(menuChSel, menuChSel->unk_0040[i], menuChSel->unk_0040[i]);

        switch (menuChSel->unk_0018[menuChSel->unk_0040[i]]) {
            case -0x1:
                var_s3 += 1;
                break;

            case 0x1:
                var_s4 += 1;
                break;
        }
    }

    if (var_s3 != 0) {
        _setMode(menuChSel->watchMenuRef, MODE_MAIN);
        func_8005380C(menuChSel, -1, 1.0f);
        menuChSel->unk_0028 -= 1;
    }

    if (var_s4 == menuChSel->unk_003C) {
        menuChSel->unk_0028 += 1;
    }
}

void menuChSel_inputCom(MenuChSel *menuChSel) {
    s32 temp_s2;
    s32 temp_s3;
    s32 i;
    s32 var_s5;

    var_s5 = 0;
    for (i = 0; i < menuChSel->unk_0060; i++) {
        temp_s2 = menuChSel->unk_0064[i];
        temp_s3 = menuChSel->unk_0008[temp_s2];
        if (menuChSel->unk_0018[temp_s2] == 1) {
            var_s5 = temp_s2;
            continue;
        }

        menuChSel_input1(menuChSel, temp_s2, 0);

        switch (menuChSel->unk_0018[temp_s2]) {
            case -0x1:
                menuChSel->unk_0034 = -1;
                menuChSel->unk_0038 = -1;
                menuChSel->unk_0018[var_s5]--;
                menuChSel->unk_0028--;
                break;
            case 0x0:
                menuChSel->unk_0034 = temp_s3;
                menuChSel->unk_0038 = temp_s2;
                break;
        }
        break;
    }

    if (i == menuChSel->unk_0060) {
        menuChSel->unk_0028++;
    }
}

const s32 _charTbl_8108[] = {
    0, 1, 3, 9, 2, 4, 7, 8, 5, 6, 0xA, 0xB, 0xC, 0xE, 0xD,
};

void menuChSel_input(MenuChSel *menuChSel) {
    MainMenuMode mode;
    struct_evs_mem_data_config *temp;
    s32 var_s2;
    s32 i;

    if ((menuChSel->unk_0074.transStep < 0.0f) || (menuChSel->unk_0074.transTime < 1.0f)) {
        return;
    }

    switch (menuChSel->unk_0028) {
        case -0x1:
            menuChSel->unk_0028 = 0;
            FALLTHROUGH;

        case 0x0:
            menuChSel_inputMan(menuChSel);
            break;

        case 0x1:
            menuChSel_inputCom(menuChSel);
            break;
    }

    if (menuChSel->unk_0028 < 2) {
        return;
    }

    var_s2 = THINKLEVEL_0;
    if (menuChSel->unk_002C != 0) {
        var_s2 = menuChSel->unk_0030;
    }

    switch (_getMode(menuChSel->watchMenuRef)) {
        case MODE_VSCOM_CH:
        case MODE_VSCOM_FL_CH:
            temp = &evs_mem_data[evs_select_name_no[0]].config;
            for (i = 0; i < menuChSel->unk_0004; i++) {
                temp->vc_no[i] = menuChSel->unk_0008[i];
            }
            break;

        case MODE_VSMAN_CH:
        case MODE_VSMAN_FL_CH:
        case MODE_VSMAN_TA_CH:
            if (evs_select_name_no[0] == evs_select_name_no[1]) {
                evs_mem_data[0].config.vm_no = 0;
            } else {
                for (i = 0; i < menuChSel->unk_0004; i++) {
                    temp = &evs_mem_data[evs_select_name_no[i]].config;

                    temp->vm_no = menuChSel->unk_0008[i];
                }
            }
            break;

        case MODE_PLAY4_CH:
        case MODE_PLAY4_TB_CH:
        case MODE_PLAY4_FL_CH:
            for (i = 0; i < menuChSel->unk_0004; i++) {
                evs_cfg_4p.p4_no[i] = menuChSel->unk_0008[i];
            }
            break;

        default:
            break;
    }

    switch (_getMode(menuChSel->watchMenuRef)) {
        case MODE_VSCOM_CH:
            mode = MODE_VSCOM;
            break;

        case MODE_VSCOM_FL_CH:
            mode = MODE_VSCOM_FL;
            break;

        case MODE_VSMAN_CH:
            mode = MODE_VSMAN;
            break;

        case MODE_VSMAN_FL_CH:
            mode = MODE_VSMAN_FL;
            break;

        case MODE_VSMAN_TA_CH:
            mode = MODE_VSMAN_TA;
            break;

        case MODE_PLAY4_CH:
            mode = MODE_PLAY4_LV;
            break;

        case MODE_PLAY4_TB_CH:
            mode = MODE_PLAY4_TB_LV;
            break;

        case MODE_PLAY4_FL_CH:
            mode = MODE_PLAY4_FL_LV;
            break;

        default:
            UNREACHABLE;
            break;
    }

    for (i = 0; i < menuChSel->unk_0004; i++) {
        struct_game_state_data *gameStateDataP = &game_state_data[i];

        gameStateDataP->charNo = _charTbl_8108[menuChSel->unk_0008[i]];
        gameStateDataP->think_level = var_s2;
    }

    _setMode(menuChSel->watchMenuRef, mode);
    func_8005380C(menuChSel, -1, 1.0f);
}

const u8 _star_8183[] = {
    4, 4, 1, 1, 2, 2, 2, 2, 3, 3, 3, 4, 5, 5, 5,
};
static_assert(ARRAY_COUNT(_star_8183) == MENUCH_SEL_UNK_LEN, "");

void menuChSel_update(MenuChSel *menuChSel) {
    SMenuItem *rootItem = _getRootItem(menuChSel->watchMenuRef);
    s32 i;
    s32 var_a0;

    menuItem_update(&menuChSel->unk_0074, rootItem);

    switch (menuChSel->unk_0028) {
        case 0:
        case 1:
            menuItem_setColorDir(&menuChSel->unk_0104, (menuChSel->unk_002C != 0) ? 1 : -1);
            break;

        default:
            menuItem_setColorDir(&menuChSel->unk_0104, -1);
            break;
    }

    menuItem_update(&menuChSel->unk_0104, rootItem);

    menuItem_updateN(menuChSel->unk_0194, ARRAY_COUNTU(menuChSel->unk_0194), &menuChSel->unk_0074);

    for (i = 0; i < MENUCH_SEL_UNK_LEN; i++) {
        if (menuChSel_checkSelected(menuChSel, -1, i, 1)) {
            menuItem_setColorDir(&menuChSel->unk_0A04[i], -1);
        } else {
            menuItem_setColorDir(&menuChSel->unk_0A04[i], 1);
        }

        menuItem_update(&menuChSel->unk_0A04[i], &menuChSel->unk_0194[i]);
    }

    for (i = 0; i < MENUCH_SEL_UNK_LEN; i++) {
        var_a0 = _star_8183[i];
        if (menuChSel->unk_002C != 0) {
            var_a0 += menuChSel->unk_0030;
        }

        menuChSel->unk_1274[i].level = var_a0;
        menuComLvPanel_setFadeDir(&menuChSel->unk_1274[i], (i == menuChSel->unk_0034) ? 1 : -1);
        menuComLvPanel_update(&menuChSel->unk_1274[i], &menuChSel->unk_0194[i]);
    }

    for (i = 0; i < menuChSel->unk_0004; i++) {
        MenuCursor *cursor = &menuChSel->unk_23CC[i];

        menuCursor_update(cursor, &menuChSel->unk_0194[menuChSel->unk_0008[i]]);

        switch (menuChSel->unk_0018[i]) {
            case -1:
                cursor->flags.cursor = false;
                cursor->flags.player = false;
                cursor->flags.blink = false;
                break;

            case 0:
                cursor->flags.cursor = true;
                cursor->flags.player = true;
                cursor->flags.blink = true;
                break;

            case 1:
                cursor->flags.cursor = true;
                cursor->flags.player = true;
                cursor->flags.blink = false;
                break;
        }
    }
}

const s32 _tex_8297[] = {
    4,
    3,
};
static_assert(ARRAY_COUNT(_tex_8297) == ARRAY_COUNT(evs_secret_flg), "");

const s32 _pos_8298[][2] = {
    { -4, 3 },
    { -2, 3 },
};
static_assert(ARRAY_COUNT(_pos_8298) == ARRAY_COUNT(evs_secret_flg), "");

void menuChSel_draw(MenuChSel *menuChSel, Gfx **gfxP) {
    Gfx *gfx = *gfxP;
    void *arr[MAX(ARRAY_COUNT(menuChSel->unk_23CC), ARRAY_COUNT(menuChSel->unk_1274))];
    SMenuItem *item;
    s32 i;

    gSPDisplayList(gfx++, fade_normal_texture_init_dl);
    menuItem_drawTex(&menuChSel->unk_0074, &gfx, _getTexChar(menuChSel->watchMenuRef, 5), 0);

    for (i = 0; i < ARRAY_COUNT(evs_secret_flg); i++) {
        if (evs_secret_flg[i]) {
            f32 temp_fs0;
            f32 temp_fs1;

            item = &menuChSel->unk_0194[14 - i];
            temp_fs0 = item->trans[0];
            temp_fs1 = item->trans[1];
            item->trans[0] += _pos_8298[i][0];
            item->trans[1] += _pos_8298[i][1];

            menuItem_drawTex(item, &gfx, _getTexChar(menuChSel->watchMenuRef, _tex_8297[i]), 0);
            item->trans[0] = temp_fs0;
            item->trans[1] = temp_fs1;
        }
    }

    gSPDisplayList(gfx++, fade_fillrect_init_dl);

    for (i = 0; i < ARRAY_COUNTU(menuChSel->unk_0A04); i++) {
        s32 x;
        s32 y;

        item = &menuChSel->unk_0A04[i];

        if (item->color[3] == 1.0f) {
            continue;
        }

        x = item->trans[0];
        y = item->trans[1];
        menuItem_setPrim(item, &gfx);

        gDPScisFillRectangle(gfx++, x, y, x + 38, y + 38);
    }

    for (i = 0; i < menuChSel->unk_0004; i++) {
        arr[i] = &menuChSel->unk_23CC[i];
    }

    menuCursor_draw((void *)arr, menuChSel->unk_0004, &gfx);

    for (i = 0; i < ARRAY_COUNTU(menuChSel->unk_1274); i++) {
        arr[i] = &menuChSel->unk_1274[i];
    }

    menuComLvPanel_draw((void *)arr, ARRAY_COUNTU(menuChSel->unk_1274), &gfx);

    gSPDisplayList(gfx++, fade_normal_texture_init_dl);
    gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);

    if (menuChSel->unk_0030 > 0) {
        menuItem_drawItem(&menuChSel->unk_0104, &gfx, _getTexChar(menuChSel->watchMenuRef, 2), 0, 2,
                          menuChSel->unk_0030 - 1);
    }

    *gfxP = gfx;
}

const s32 _moveTbl_8521[] = {
    0x140,
    -0x140,
};

void func_80054A94(MenuPlay2 *menuPlay2, s32 arg1, f32 arg2) {
    s32 i;

    for (i = 0; i < menuPlay2->unk_00C4; i++) {
        MenuPlay2Panel *temp_a0 = &menuPlay2->unk_00C8[i];
        SMenuItem *item = &temp_a0->unk_0034;

        item->transRange[0][0] = item->transRange[1][0] + _moveTbl_8521[i % ARRAY_COUNTU(_moveTbl_8521)];
        item->transStep = 0.05f;
        item->transTime = arg2;
        menuItem_setTransDir(item, arg1);
    }
}

const s32 _onaji_8534[][2] = {
    { 0xD8, 0x2D },
    { 0xD8, 0x23 },
};

const s32 _panel2_8535[][2] = {
    { 0x19, 0x3A },
    { 0x19, 0x80 },
};

const s32 _panel4_8536[][2] = {
    { 0x19, 0x30 },
    { 0x19, 0x5D },
    { 0x19, 0x8A },
    { 0x19, 0xB7 },
};

void menuPlay2_init(MenuPlay2 *menuPlay2, struct_watchMenu *watchMenuRef, void **heapP) {
    struct_evs_mem_data_config *temp_s0;
    struct_game_state_data *temp_s3_3;
    s32 sp44;
    s32 sp4C;
    s32 var_s5;
    s32 i;

    menuPlay2->watchMenuRef = watchMenuRef;
    menuPlay2->unk_0008 = -1;
    menuPlay2->unk_0004 = -1;

    switch (_getMode(menuPlay2->watchMenuRef)) {
        case MODE_VSMAN:
        case MODE_VSMAN_FL:
        case MODE_VSMAN_TA:
            temp_s0 = &evs_mem_data[evs_select_name_no[0]].config;
            sp4C = temp_s0->vm_m;
            sp44 = temp_s0->vm_st + 1;

            menuPlay2->unk_000C = 2;
            menuPlay2->unk_0010[0] = 0;
            menuPlay2->unk_0010[1] = 1;
            menuPlay2->unk_0020 = 0;
            menuPlay2->unk_00C4 = 2;

            for (i = 0; i < menuPlay2->unk_00C4; i++) {
                temp_s0 = &evs_mem_data[evs_select_name_no[i]].config;
                temp_s3_3 = &game_state_data[i];

                switch (_getMode(menuPlay2->watchMenuRef)) {
                    case MODE_VSMAN:
                        var_s5 = temp_s0->vm_lv;
                        break;

                    case MODE_VSMAN_FL:
                        var_s5 = temp_s0->vm_fl_lv;
                        break;

                    case MODE_VSMAN_TA:
                        var_s5 = temp_s0->vm_ta_lv;
                        break;

                    default:
                        break;
                }

                menuPlay2Panel_init(&menuPlay2->unk_00C8[i], watchMenuRef, heapP, 1, menuPlay2->unk_000C,
                                    menuPlay2->unk_0020, i, temp_s3_3->player_type == PLAYERTYPE_1, temp_s3_3->charNo,
                                    var_s5, temp_s0->vm_sp, _panel2_8535[i][0], _panel2_8535[i][1]);
            }
            break;

        case MODE_VSCOM:
        case MODE_VSCOM_FL:
            temp_s0 = &evs_mem_data[evs_select_name_no[0]].config;
            sp4C = temp_s0->vc_m;
            sp44 = temp_s0->vc_st + 1;

            menuPlay2->unk_000C = 1;
            menuPlay2->unk_0010[0] = 0;
            menuPlay2->unk_0020 = 1;
            menuPlay2->unk_0024[0] = 1;
            menuPlay2->unk_00C4 = 2;

            for (i = 0; i < menuPlay2->unk_00C4; i++) {
                temp_s3_3 = &game_state_data[i];

                switch (_getMode(menuPlay2->watchMenuRef)) {
                    case MODE_VSCOM:
                        var_s5 = temp_s0->vc_lv[i];
                        break;

                    case MODE_VSCOM_FL:
                        var_s5 = temp_s0->vc_fl_lv[i];
                        break;

                    default:
                        break;
                }

                menuPlay2Panel_init(&menuPlay2->unk_00C8[i], watchMenuRef, heapP, 1, menuPlay2->unk_000C,
                                    menuPlay2->unk_0020, i, temp_s3_3->player_type == PLAYERTYPE_1, temp_s3_3->charNo,
                                    var_s5, temp_s0->vc_sp[i], _panel2_8535[i][0], _panel2_8535[i][1]);
            }
            break;

        case MODE_PLAY4_LV:
        case MODE_PLAY4_TB_LV:
        case MODE_PLAY4_FL_LV:
            sp44 = evs_cfg_4p.p4_st + 1;
            sp4C = evs_cfg_4p.p4_m;

            menuPlay2->unk_000C = 0;
            menuPlay2->unk_0020 = 0;
            menuPlay2->unk_00C4 = 4;

            for (i = 0; i < menuPlay2->unk_00C4; i++) {
                temp_s3_3 = &game_state_data[i];

                if (temp_s3_3->player_type == PLAYERTYPE_1) {
                    menuPlay2->unk_0024[menuPlay2->unk_0020] = i;
                    menuPlay2->unk_0020 += 1;
                } else {
                    menuPlay2->unk_0010[menuPlay2->unk_000C] = i;
                    menuPlay2->unk_000C += 1;
                }
            }

            for (i = 0; i < menuPlay2->unk_00C4; i++) {
                temp_s3_3 = &game_state_data[i];
                switch (_getMode(menuPlay2->watchMenuRef)) {
                    case MODE_PLAY4_TB_LV:
                    case MODE_PLAY4_LV:
                        var_s5 = evs_cfg_4p.p4_lv[i];
                        break;

                    case MODE_PLAY4_FL_LV:
                        var_s5 = evs_cfg_4p.p4_fl_lv[i];
                        break;

                    default:
                        break;
                }

                menuPlay2Panel_init(&menuPlay2->unk_00C8[i], watchMenuRef, heapP, 0, menuPlay2->unk_000C,
                                    menuPlay2->unk_0020, i, temp_s3_3->player_type == PLAYERTYPE_1, temp_s3_3->charNo,
                                    var_s5, evs_cfg_4p.p4_sp[i], _panel4_8536[i][0], _panel4_8536[i][1]);
            }
            break;

        default:
            break;
    }

    i = menuPlay2->unk_00C4 / 2 - 1;
    menuItem_init(&menuPlay2->unk_0034, _onaji_8534[i][0], _onaji_8534[i][1]);
    menuItem_setColor_fade(&menuPlay2->unk_0034);
    menuPlay2->unk_0034.colorTime = 0.0f;

    menuPlay2PanelSub_init(&menuPlay2->unk_6548, watchMenuRef, heapP, sp44, sp4C, 0x19, 0x4B);
    func_80054A94(menuPlay2, 1, 0);
}

void func_800550F4(MenuPlay2 *menuPlay2) {
    u32 keyTrg = _getKeyTrg(menuPlay2->watchMenuRef, 0);

    if (keyTrg & B_BUTTON) {
        menuPlay2->unk_0004 = 2;
        menuPlay2->unk_6548.unk_008 = 0;
        _setFadeDir(menuPlay2->watchMenuRef, -1);
        _setNextMain(menuPlay2->watchMenuRef, MAIN_MENU);
        dm_snd_play(SND_INDEX_68);
    }
}

bool func_80055154(MenuPlay2 *play2, s32 arg1, s32 arg2) {
    MenuPlay2Panel *play2Panel = &play2->unk_00C8[arg1];
    u32 keyLvl = _getKeyLvl(play2->watchMenuRef, arg2);

    return (keyLvl & R_TRIG) && (play2Panel->unk_0028 == 0);
}

void func_800551BC(MenuPlay2 *menuPlay2, s32 index) {
    MenuPlay2Panel *temp_s3 = &menuPlay2->unk_00C8[index];
    s32 i;

    for (i = 0; i < menuPlay2->unk_00C4; i++) {
        MenuPlay2Panel *temp_a0 = &menuPlay2->unk_00C8[i];

        if (temp_a0->unk_0028 <= 0) {
            menuPlay2Panel_copyConfig(temp_a0, temp_s3);
        }
    }
}

void func_80055254(MenuPlay2 *menuPlay2, s32 arg1) {
    MenuPlay2Panel *temp_s3 = &menuPlay2->unk_00C8[arg1];
    s32 i;

    for (i = 0; i < menuPlay2->unk_00C4; i++) {
        MenuPlay2Panel *temp_a0 = &menuPlay2->unk_00C8[i];

        if (temp_a0->unk_0028 <= 0) {
            menuPlay2Panel_copyCursor(temp_a0, temp_s3);
        }
    }
}

void menuPlay2_inputMan(MenuPlay2 *play2) {
    MenuPlay2Panel *temp_s0;
    MainMenuMode var_s6;
    s32 temp_a1_4;
    s32 i;
    s32 var_s4;
    s32 var_s5;
    bool var_s7;

    if (play2->unk_0008 >= 0) {
        if (!func_80055154(play2, play2->unk_0008, play2->unk_0008)) {
            play2->unk_0008 = -1;
        }
    }

    if (play2->unk_0008 < 0) {
        for (i = 0; i < play2->unk_000C; i++) {
            if (func_80055154(play2, play2->unk_0010[i], play2->unk_0010[i])) {
                play2->unk_0008 = play2->unk_0010[i];
                break;
            }
        }
    }

    for (i = 0; i < play2->unk_000C; i++) {
        temp_a1_4 = play2->unk_0010[i];
        temp_s0 = &play2->unk_00C8[temp_a1_4];

        if (temp_a1_4 == 0) {
            if (temp_s0->unk_0028 == 1) {
                break;
            }
        } else if (temp_s0->unk_0028 != 1) {
            break;
        }
    }

    var_s7 = (i == play2->unk_000C) && (play2->unk_0020 != 0);
    var_s5 = 0;

    var_s4 = 0;
    for (i = 0; i < play2->unk_000C; i++) {
        temp_a1_4 = play2->unk_0010[i];
        temp_s0 = &play2->unk_00C8[temp_a1_4];
        if ((play2->unk_0008 < 0) || (play2->unk_0008 == temp_a1_4)) {
            s32 var_a3;

            var_a3 = 0;
            if (!var_s7 || (temp_a1_4 != 0)) {
                var_a3 = 1;
            }
            menuPlay2Panel_input(temp_s0, temp_a1_4, 1, var_a3);
        }

        switch (temp_s0->unk_0028) {
            case -0x1:
                var_s5 += 1;
                break;

            case 0x1:
                var_s4 += 1;
                break;
        }
    }

    if (var_s5 != 0) {
        switch (_getMode(play2->watchMenuRef)) {
            case MODE_VSMAN:
                var_s6 = MODE_VSMAN_CH;
                break;

            case MODE_VSMAN_FL:
                var_s6 = MODE_VSMAN_FL_CH;
                break;

            case MODE_VSMAN_TA:
                var_s6 = MODE_VSMAN_TA_CH;
                break;

            case MODE_VSCOM:
                var_s6 = MODE_VSCOM_CH;
                break;

            case MODE_VSCOM_FL:
                var_s6 = MODE_VSCOM_FL_CH;
                break;

            case MODE_PLAY4_LV:
                var_s6 = MODE_PLAY4_CH;
                break;

            case MODE_PLAY4_TB_LV:
                var_s6 = MODE_PLAY4_TB_CH;
                break;

            case MODE_PLAY4_FL_LV:
                var_s6 = MODE_PLAY4_FL_CH;
                break;

            default:
                break;
        }

        play2->unk_0004 -= 1;
        _setMode(play2->watchMenuRef, var_s6);
        func_80054A94(play2, -1, 1.0f);
    } else if (var_s4 == play2->unk_000C) {
        play2->unk_0004 += 1;
    }
}

void menuPlay2_inputCpu(MenuPlay2 *play2) {
    s32 var_s2 = 0;
    s32 i;

    play2->unk_0008 = -1;

    for (i = 0; i < play2->unk_0020; i++) {
        s32 temp_s0 = play2->unk_0024[i];
        MenuPlay2Panel *temp_s1 = &play2->unk_00C8[temp_s0];

        if (temp_s1->unk_0028 == 1) {
            var_s2 = temp_s0;
            continue;
        }

        if (func_80055154(play2, temp_s0, 0) != 0) {
            play2->unk_0008 = temp_s0;
        }

        menuPlay2Panel_input(temp_s1, 0, 0, i == (play2->unk_0020 - 1));
        if (temp_s1->unk_0028 == -1) {
            play2->unk_00C8[var_s2].unk_0028 = temp_s1->unk_0028;
            if (var_s2 == 0) {
                play2->unk_0004--;
            }
        }
        break;
    }

    if (i == play2->unk_0020) {
        play2->unk_0004++;
    }
}

void menuPlay2_input(MenuPlay2 *menuPlay2) {
    MenuPlay2Panel *play2Panel;
    struct_evs_mem_data_config *temp_a2;
    s32 i;

    if (menuPlay2->unk_00C8[0].unk_0034.transStep < 0.0f) {
        return;
    }

    if (menuPlay2->unk_00C8[0].unk_0034.transTime < 1.0f) {
        return;
    }

    if (menuPlay2->unk_0008 >= 0) {
        u32 keyTrg = _getKeyTrg(menuPlay2->watchMenuRef, menuPlay2->unk_0008);
        u32 keyLvl = _getKeyLvl(menuPlay2->watchMenuRef, menuPlay2->unk_0008);

        if ((keyLvl & R_TRIG) && (keyTrg & (A_BUTTON | START_BUTTON))) {
            for (i = 0; i < menuPlay2->unk_00C4; i++) {
                play2Panel = &menuPlay2->unk_00C8[i];

                play2Panel->unk_0028 = 1;
            }
            SND_PLAY_INDEX(SND_INDEX_62);
        }
    }

    switch (menuPlay2->unk_0004) {
        case -1:
            menuPlay2->unk_0004 = 0;
            FALLTHROUGH;

        case 0:
            func_8004E270(&menuPlay2->unk_6548, -1, menuPlay2->unk_6548.unk_010.transTime);
            menuPlay2_inputMan(menuPlay2);
            break;

        case 1:
            func_8004E270(&menuPlay2->unk_6548, -1, menuPlay2->unk_6548.unk_010.transTime);
            menuPlay2_inputCpu(menuPlay2);
            break;

        case 2:
            menuPlay2->unk_0008 = -1;
            func_8004E270(&menuPlay2->unk_6548, 1, menuPlay2->unk_6548.unk_010.transTime);
            if (menuPlay2PanelSub_input(&menuPlay2->unk_6548, 0)) {
                switch (menuPlay2->unk_6548.unk_008) {
                    case -1:
                        menuPlay2->unk_0004 -= 2;
                        for (i = 0; i < menuPlay2->unk_00C4; i++) {
                            menuPlay2->unk_00C8[i].unk_0028 = -1;
                            menuPlay2->unk_00C8[i].unk_0024 = 0;
                        }

                        if (menuPlay2->unk_6548.unk_0A0.playNo >= 0) {
                            dm_seq_play_fade(SEQ_INDEX_12, 0x14);
                            menuPlay2->unk_6548.unk_0A0.playNo = -1;
                        }
                        break;

                    case 1:
                        menuPlay2->unk_0004++;
                        break;
                }
            }
            break;
    }

    if (menuPlay2->unk_0004 < 3) {
        return;
    }

    switch (_getMode(menuPlay2->watchMenuRef)) {
        case MODE_VSMAN:
        case MODE_VSMAN_FL:
        case MODE_VSMAN_TA:
            for (i = 0; i < menuPlay2->unk_00C4; i++) {
                play2Panel = &menuPlay2->unk_00C8[i];
                temp_a2 = &evs_mem_data[evs_select_name_no[i]].config;

                if (play2Panel->unk_0004 != 0) {
                    temp_a2->vm_fl_lv = play2Panel->unk_12BC.select;
                } else if (play2Panel->unk_0008 != 0) {
                    temp_a2->vm_ta_lv = play2Panel->unk_12BC.select;
                } else {
                    temp_a2->vm_lv = play2Panel->unk_0290.level;
                }
                temp_a2->vm_sp = play2Panel->unk_062C.select;
                temp_a2->vm_st = menuPlay2->unk_6548.unk_940.number - 1;
                temp_a2->vm_m = menuPlay2->unk_6548.unk_0A0.select;
            }
            break;

        case MODE_VSCOM:
        case MODE_VSCOM_FL:
            temp_a2 = &evs_mem_data[evs_select_name_no[0]].config;

            for (i = 0; i < menuPlay2->unk_00C4; i++) {
                play2Panel = &menuPlay2->unk_00C8[i];

                if (play2Panel->unk_0004 != 0) {
                    temp_a2->vc_fl_lv[i] = play2Panel->unk_12BC.select;
                } else {
                    temp_a2->vc_lv[i] = play2Panel->unk_0290.level;
                }
                temp_a2->vc_sp[i] = play2Panel->unk_062C.select;
            }

            temp_a2->vc_st = menuPlay2->unk_6548.unk_940.number - 1;
            temp_a2->vc_m = menuPlay2->unk_6548.unk_0A0.select;
            break;

        default:
            break;

        case MODE_PLAY4_LV:
        case MODE_PLAY4_TB_LV:
        case MODE_PLAY4_FL_LV:
            for (i = 0; i < menuPlay2->unk_00C4; i++) {
                play2Panel = &menuPlay2->unk_00C8[i];

                if (play2Panel->unk_0004 != 0) {
                    evs_cfg_4p.p4_fl_lv[i] = play2Panel->unk_12BC.select;
                } else {
                    evs_cfg_4p.p4_lv[i] = play2Panel->unk_0290.level;
                }
                evs_cfg_4p.p4_sp[i] = play2Panel->unk_062C.select;
            }

            evs_cfg_4p.p4_st = menuPlay2->unk_6548.unk_940.number - 1;
            evs_cfg_4p.p4_m = menuPlay2->unk_6548.unk_0A0.select;
            break;
    }

    for (i = 0; i < menuPlay2->unk_00C4; i++) {
        struct_game_state_data *ptr = &game_state_data[i];
        play2Panel = &menuPlay2->unk_00C8[i];

        if (play2Panel->unk_0004 != 0) {
            ptr->virus_level = _timeAttack_levelTable[play2Panel->unk_12BC.select];
            ptr->game_level = play2Panel->unk_12BC.select;
        } else if (play2Panel->unk_0008 != 0) {
            ptr->virus_level = _timeAttack_levelTable[play2Panel->unk_12BC.select];
            ptr->game_level = play2Panel->unk_12BC.select;
        } else {
            ptr->virus_level = play2Panel->unk_0290.level;
        }
        ptr->cap_def_speed = play2Panel->unk_062C.select;
    }

    i = menuPlay2->unk_6548.unk_940.number - 1;

    story_proc_no = _bgDataNo_to_stageNo[i][1] + 1;
    story_proc_no += _bgDataNo_to_stageNo[i][0] * 0xC;
    evs_story_no = _bgDataNo_to_stageNo[i][1] + 1;

    evs_seqnumb = menuPlay2->unk_6548.unk_0A0.select;
    evs_seqence = evs_seqnumb != 4;
    evs_game_time = 0;

    _setFadeDir(menuPlay2->watchMenuRef, 1);
    _setNextMain(menuPlay2->watchMenuRef, MAIN_12);
}

void menuPlay2_update(MenuPlay2 *menuPlay2) {
    SMenuItem *rootItem = _getRootItem(menuPlay2->watchMenuRef);
    s32 i;

    switch (menuPlay2->unk_0004) {
        case 0:
        case 1:
            menuItem_setColorDir(&menuPlay2->unk_0034, 1);
            break;

        default:
            menuItem_setColorDir(&menuPlay2->unk_0034, -1);
            break;
    }

    if (menuPlay2->unk_0008 >= 0) {
        func_800551BC(menuPlay2, menuPlay2->unk_0008);
    }

    for (i = 0; i < menuPlay2->unk_00C4; i++) {
        menuPlay2Panel_update(&menuPlay2->unk_00C8[i], rootItem);
    }

    if (menuPlay2->unk_0008 >= 0) {
        func_80055254(menuPlay2, menuPlay2->unk_0008);
    }

    menuPlay2PanelSub_update(&menuPlay2->unk_6548, rootItem);
    menuItem_update(&menuPlay2->unk_0034, rootItem);
}

void menuPlay2_draw(MenuPlay2 *menuPlay2, Gfx **gfxP) {
    Gfx *gfx = *gfxP;
    SMenuItem *rootItem UNUSED = _getRootItem(menuPlay2->watchMenuRef);
    MenuPlay2Panel *arr[menuPlay2->unk_00C4];
    s32 i;

    for (i = 0; i < menuPlay2->unk_00C4; i++) {
        arr[i] = &menuPlay2->unk_00C8[i];
    }
    menuPlay2Panel_draw(arr, menuPlay2->unk_00C4, &gfx);

    menuPlay2PanelSub_draw(&menuPlay2->unk_6548, &gfx);

    gSPDisplayList(gfx++, fade_normal_texture_init_dl);
    gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);

    menuItem_drawTex(&menuPlay2->unk_0034, &gfx, _getTexSetup(menuPlay2->watchMenuRef, 0x13), 0);

    *gfxP = gfx;
}

void func_80055DFC(MenuNmEnt *menuNmEnt, s32 arg1, f32 arg2) {
    SMenuItem *item = &menuNmEnt->unk_003C;

    item->transTime = arg2;
    item->transStep = 0.05f;
    item->transRange[0][1] = item->transRange[1][1] - 240.0f;
    menuItem_setTransDir(item, arg1);
}

void menuNmEnt_init(MenuNmEnt *menuNmEnt, struct_watchMenu *watchMenuRef, void **heapP UNUSED) {
    s32 i;

    menuNmEnt->watchMenuRef = watchMenuRef;

    switch (_getMode(watchMenuRef)) {
        case MODE_VSMAN_NE:
        case MODE_VSMAN_FL_NE:
        case MODE_VSMAN_TA_NE:
            menuNmEnt->unk_0008 = 2;
            break;

        default:
            menuNmEnt->unk_0008 = 1;
            break;
    }

    for (i = 0; i < menuNmEnt->unk_0008; i++) {
        if (evs_select_name_no[i] != 8) {
            u8 *ptr = &evs_mem_data[evs_select_name_no[i]].mem_use_flg;

            if (_getMode(watchMenuRef) == MODE_NAME_NE2) {
                break;
            }
            if (!(*ptr & MEM_USE_FLG_1)) {
                break;
            }
        }
    }

    menuNmEnt->unk_0004 = i;

    for (i = 0; i < 2U; i++) {
        menuNmEnt->unk_000C[i] = -1;
        menuNmEnt->unk_0014[i] = 0;
        menuNmEnt->unk_001C[i][0] = 0;
        menuNmEnt->unk_001C[i][1] = 0;

        if ((_getMode(watchMenuRef) == MODE_NAME_NE2) && (evs_select_name_no[i] != 8)) {
            bcopy(evs_mem_data[evs_select_name_no[i]].mem_name, menuNmEnt->unk_002C[i], sizeof(menuNmEnt->unk_002C[i]));
        } else {
            s32 j;

            for (j = 0; j < ARRAY_COUNT(menuNmEnt->unk_002C[i]); j++) {
                menuNmEnt->unk_002C[i][j] = 0;
            }
        }

        menuNmEnt->unk_0034[i] = 0;
    }

    menuItem_init(&menuNmEnt->unk_003C, 29, 98);
    menuItem_init(&menuNmEnt->unk_00CC, 47, -47);
#if VERSION_US || VERSION_GW
    menuItem_init(&menuNmEnt->unk_015C, 100, 5);
#elif VERSION_CN
    menuItem_init(&menuNmEnt->unk_015C, 80, 7);
#else
#error ""
#endif
    menuItem_init(&menuNmEnt->unk_01EC, 20, 7);
    menuItem_init(&menuNmEnt->unk_027C, 0, 0);
    menuCursor_init(&menuNmEnt->unk_030C, watchMenuRef, CURSOR_ITEM, menuNmEnt->unk_0004, -2, -2, 0x10, 0x10);
    menuNmEnt->unk_030C.flags.finger = true;
    menuItem_init(&menuNmEnt->unk_056C, 59, 23);
    menuItem_init(&menuNmEnt->unk_05FC, 0, 16);
    func_80055DFC(menuNmEnt, 1, 0.0f);
}

void func_800560D4(MenuNmEnt *nmEnt) {
    menuNmEnt_update(nmEnt);
}

// This array has only 1 entry
const char *_nameEntry_charTable[] = {
    "ＡＢＣＤＥ__ａｂｃｄｅ__○×☆"
    "ＦＧＨＩＪ__ｆｇｈｉｊ__・．："
    "ＫＬＭＮＯ__ｋｌｍｎｏ__！？＆"
    "ＰＱＲＳＴ__ｐｑｒｓｔ__＊／％"
    "ＵＶＷＸＹ__ｕｖｗｘｙ__，’〜"
    "Ｚ__________ｚ________________"
    "０１２３４__５６７８９__303132"
    "________________________404142"
    "________________________505152",
};

void menuNmEnt_input(MenuNmEnt *menuNmEnt) {
    u32 keyRep = _getKeyRep(menuNmEnt->watchMenuRef, menuNmEnt->unk_0004);
    u32 keyTrg = _getKeyTrg(menuNmEnt->watchMenuRef, menuNmEnt->unk_0004);
    s32 i;
    s32 horizontal;
    s32 vertical;
    SndIndex soundIndex = SND_INDEX_INVALID;
    s32 sp20 = 0;
    s32 sp24 = menuNmEnt->unk_0004;

    if (menuNmEnt->unk_003C.transStep < 0.0f) {
        return;
    }
    if (menuNmEnt->unk_003C.transTime < 1.0f) {
        return;
    }

    vertical = 0;
    horizontal = 0;
    if (keyRep & L_JPAD) {
        horizontal--;
    }
    if (keyRep & R_JPAD) {
        horizontal++;
    }
    if (keyRep & U_JPAD) {
        vertical--;
    }
    if (keyRep & D_JPAD) {
        vertical++;
    }

    if ((horizontal != 0) || (vertical != 0)) {
        bool var_s7 = false;
        s32 var_s0 = menuNmEnt->unk_001C[sp24][0];
        s32 var_s1 = menuNmEnt->unk_001C[sp24][1];
        char *characterP;

        do {
#if VERSION_US || VERSION_GW
            // discard const
            characterP = (char *)&_nameEntry_charTable[menuNmEnt->unk_0014[sp24]][(var_s0 + var_s1 * 0xF) * 2];

            if (isdigit(characterP[0]) && (horizontal != 0)) {
                s32 temp_lo;
                s32 var_v0;

                temp_lo = horizontal * (characterP[1] - '0');
                if (horizontal > 0) {
                    var_v0 = 3 - temp_lo;
                } else {
                    var_v0 = -1 - temp_lo;
                }

                var_s0 = WrapI(0, 0xF, var_s0 + var_v0);
            } else {
                var_s0 = WrapI(0, 0xF, var_s0 + horizontal);
            }

#elif VERSION_CN
            var_s0 = WrapI(0, 0xF, var_s0 + horizontal);
#else
#error ""
#endif
            var_s1 = WrapI(0, 9, var_s1 + vertical);
            characterP = (char *)&_nameEntry_charTable[menuNmEnt->unk_0014[sp24]][((var_s0 + (var_s1 * 0xF)) * 2)];
        } while (characterP[0] == '_');

        if (characterP[0] & 0x80) {
            menuNmEnt->unk_000C[sp24] = -1;
            var_s7++;
        } else if (isdigit(characterP[0])) {
            menuNmEnt->unk_000C[sp24] = characterP[0] - '0';
            var_s0 += '0' - characterP[1];
            var_s7 = (var_s0 != menuNmEnt->unk_001C[sp24][0]) || (var_s1 != menuNmEnt->unk_001C[sp24][1]);
        }

        if (var_s7) {
            menuNmEnt->unk_001C[sp24][0] = var_s0;
            menuNmEnt->unk_001C[sp24][1] = var_s1;
            soundIndex = SND_INDEX_64;
        }
    }

    if ((keyTrg & START_BUTTON) && (menuNmEnt->unk_000C[sp24] != 5)) {
        menuNmEnt->unk_000C[sp24] = 5;
        menuNmEnt->unk_001C[sp24][0] = 0xC;
        menuNmEnt->unk_001C[sp24][1] = 8;
        soundIndex = SND_INDEX_62;
    } else if (keyTrg & (A_BUTTON | START_BUTTON)) {
        const char *characterP =
            &_nameEntry_charTable[menuNmEnt->unk_0014[sp24]]
                                 [(menuNmEnt->unk_001C[sp24][0] + (menuNmEnt->unk_001C[sp24][1] * 0xF)) * 2];

        switch (menuNmEnt->unk_000C[sp24]) {
            case -0x1:
                if (menuNmEnt->unk_0034[sp24] < 4) {
                    menuNmEnt->unk_002C[sp24][menuNmEnt->unk_0034[sp24]] = font2index(characterP);
                    menuNmEnt->unk_0034[sp24]++;
                    soundIndex = SND_INDEX_62;
                }

                if (menuNmEnt->unk_0034[sp24] == 4) {
                    menuNmEnt->unk_001C[sp24][0] = 0xC;
                    menuNmEnt->unk_001C[sp24][1] = 8;
                    menuNmEnt->unk_000C[sp24] = 5;
                }
                break;

            case 0x3:
                if (menuNmEnt->unk_0034[sp24] < 4) {
                    menuNmEnt->unk_002C[sp24][menuNmEnt->unk_0034[sp24]] = 0;
                    menuNmEnt->unk_0034[sp24]++;
                    soundIndex = SND_INDEX_62;
                }

                if (menuNmEnt->unk_0034[sp24] == 4) {
                    menuNmEnt->unk_001C[sp24][0] = 0xC;
                    menuNmEnt->unk_001C[sp24][1] = 8;
                    menuNmEnt->unk_000C[sp24] = 5;
                }
                break;

            case 0x4:
                if (menuNmEnt->unk_0034[sp24] > 0) {
                    menuNmEnt->unk_0034[sp24]--;
                    menuNmEnt->unk_002C[sp24][menuNmEnt->unk_0034[sp24]] = 0;
                    soundIndex = SND_INDEX_68;
                } else {
                    soundIndex = SND_INDEX_71;
                }
                break;

            case 0x5:
                for (i = 0; i < ARRAY_COUNT(menuNmEnt->unk_002C[sp24]); i++) {
                    if ((char)menuNmEnt->unk_002C[sp24][i] != 0) {
                        break;
                    }
                }

                if (i != ARRAY_COUNT(menuNmEnt->unk_002C[sp24])) {
                    sp20++;
                    soundIndex = SND_INDEX_62;
                } else {
                    soundIndex = SND_INDEX_71;
                }
                break;
        }
    } else if (keyTrg & B_BUTTON) {
        if (menuNmEnt->unk_0034[sp24] > 0) {
            menuNmEnt->unk_0034[sp24]--;
            menuNmEnt->unk_002C[sp24][menuNmEnt->unk_0034[sp24]] = 0;
        } else {
            sp20--;
        }
        soundIndex = SND_INDEX_68;
    }

    if (sp20 > 0) {
        struct_evs_mem_data *temp_s1_2 = &evs_mem_data[evs_select_name_no[sp24]];

        switch (_getMode(menuNmEnt->watchMenuRef)) {
            case MODE_NAME_NE2:
                break;

            default:
                dm_init_save_mem(temp_s1_2);
                break;
        }

        temp_s1_2->mem_use_flg |= MEM_USE_FLG_1;
        for (i = 0; i < ARRAY_COUNT(menuNmEnt->unk_002C[sp24]); i++) {
            temp_s1_2->mem_name[i] = menuNmEnt->unk_002C[sp24][i];
        }

        for (i = sp24 + 1; i < menuNmEnt->unk_0008; i++) {
            if (evs_select_name_no[i] != 8) {
                struct_evs_mem_data *ptr = &evs_mem_data[evs_select_name_no[i]];

                if (_getMode(menuNmEnt->watchMenuRef) == MODE_NAME_NE2) {
                    break;
                }
                if (!(ptr->mem_use_flg & MEM_USE_FLG_1)) {
                    break;
                }
            }
        }

        if (i >= menuNmEnt->unk_0008) {
            MainMenuMode sp30;

            _eepWritePlayer(menuNmEnt->watchMenuRef);

            switch (_getMode(menuNmEnt->watchMenuRef)) {
                case MODE_STORY_NE:
                    sp30 = MODE_STORY;
                    break;

                case MODE_LVSEL_NE:
                    sp30 = MODE_LVSEL;
                    break;

                case MODE_LVSEL_TQ_NE:
                    sp30 = MODE_LVSEL_TQ;
                    break;

                case MODE_LVSEL_TA_NE:
                    sp30 = MODE_LVSEL_TA;
                    break;

                case MODE_VSCOM_NE:
                    sp30 = MODE_VSCOM_CH;
                    break;

                case MODE_VSCOM_FL_NE:
                    sp30 = MODE_VSCOM_FL_CH;
                    break;

                case MODE_VSMAN_NE:
                    sp30 = MODE_VSMAN_CH;
                    break;

                case MODE_VSMAN_FL_NE:
                    sp30 = MODE_VSMAN_FL_CH;
                    break;

                case MODE_VSMAN_TA_NE:
                    sp30 = MODE_VSMAN_TA_CH;
                    break;

                case MODE_NAME_NE:
                case MODE_NAME_NE2:
                    sp30 = MODE_MAIN;
                    break;

                default:
                    break;
            }

            _setMode(menuNmEnt->watchMenuRef, sp30);
            func_80055DFC(menuNmEnt, -1, 1.0f);
        } else {
            menuNmEnt->unk_0004 = i;
        }
    } else if (sp20 < 0) {
        for (i = sp24 - 1; i >= 0; i--) {
            if (evs_select_name_no[i] != 8) {
                struct_evs_mem_data *ptr = &evs_mem_data[evs_select_name_no[i]];

                if (_getMode(menuNmEnt->watchMenuRef) == MODE_NAME_NE2) {
                    break;
                }
                if (!(ptr->mem_use_flg & MEM_USE_FLG_1)) {
                    break;
                }
            }
        }

        if (i < 0) {
            switch (_getMode(menuNmEnt->watchMenuRef)) {
                case MODE_NAME_NE2:
                    _setMode(menuNmEnt->watchMenuRef, MODE_MAIN);
                    break;

                default:
                    _setMode(menuNmEnt->watchMenuRef, MODE_MAIN);
                    break;
            }

            func_80055DFC(menuNmEnt, -1, 1.0f);
        } else {
            menuNmEnt->unk_0004 = i;
        }

        soundIndex = SND_INDEX_68;
    }

    SND_PLAY_INDEX(soundIndex);
}

void menuNmEnt_update(MenuNmEnt *menuNmEnt) {
    SMenuItem *rootItem = _getRootItem(menuNmEnt->watchMenuRef);

    menuItem_update(&menuNmEnt->unk_003C, rootItem);
    menuItem_update(&menuNmEnt->unk_00CC, &menuNmEnt->unk_003C);
    menuItem_update(&menuNmEnt->unk_015C, &menuNmEnt->unk_00CC);
    menuItem_update(&menuNmEnt->unk_01EC, &menuNmEnt->unk_003C);

    menuNmEnt->unk_030C.size[0] = (menuNmEnt->unk_000C[menuNmEnt->unk_0004] == -1) ? 0x10 : 0x32;
    menuNmEnt->unk_030C.playerNo = menuNmEnt->unk_0004;

    menuItem_setTransHi(&menuNmEnt->unk_027C, menuNmEnt->unk_001C[menuNmEnt->unk_0004][0] * 0xF,
                        menuNmEnt->unk_001C[menuNmEnt->unk_0004][1] * 0xD);
    menuItem_update(&menuNmEnt->unk_027C, &menuNmEnt->unk_01EC);
    menuCursor_update(&menuNmEnt->unk_030C, &menuNmEnt->unk_027C);
    menuItem_update(&menuNmEnt->unk_056C, &menuNmEnt->unk_00CC);
    menuNmEnt->unk_05FC.transRange[1][0] = menuNmEnt->unk_0034[menuNmEnt->unk_0004] * 0xD;
    menuItem_update(&menuNmEnt->unk_05FC, &menuNmEnt->unk_056C);
}

void menuNmEnt_draw(MenuNmEnt *menuNmEnt, Gfx **gfxP) {
    Gfx *gfx = *gfxP;
    MenuCursor *sp24[1];
    TiTexData *temp_s1;
    TiTexData *temp;
    s32 var_s0;
    s32 var_s1;
    s32 var_s3;
    s32 var_s4;
    const char *var_s2;

    gSPDisplayList(gfx++, fade_normal_texture_init_dl);

    temp_s1 = _getTexName(menuNmEnt->watchMenuRef, 3);
    menuItem_drawTex(&menuNmEnt->unk_00CC, &gfx, temp_s1, 0);
    if (menuNmEnt->unk_0004 == 1) {
        temp_s1 = _getTexName(menuNmEnt->watchMenuRef, 4);
        menuItem_drawTex(&menuNmEnt->unk_015C, &gfx, temp_s1, 0);
    }

    gSPDisplayList(gfx++, fade_normal_texture_init_dl);

    temp_s1 = _getTexName(menuNmEnt->watchMenuRef, 2);
    if (!menuItem_drawTex(&menuNmEnt->unk_003C, &gfx, temp_s1, 0)) {
        return;
    }

    gSPDisplayList(gfx++, fade_intensity_texture_init_dl);
    gDPSetTextureFilter(gfx++, G_TF_BILERP);
    gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, 255);

    // Draw keyboard
    var_s3 = menuNmEnt->unk_01EC.trans[1];
    var_s2 = _nameEntry_charTable[menuNmEnt->unk_0014[menuNmEnt->unk_0004]];
    for (var_s4 = 0; var_s4 < 9; var_s4++) {
        var_s0 = menuNmEnt->unk_01EC.trans[0];

        for (var_s1 = 0; var_s1 < 0xF; var_s1++) {
            if (*var_s2 & 0x80) {
                fontXX_draw(&gfx, var_s0, var_s3, 12.0f, 12.0f, var_s2);
            }
            var_s0 += 0xF;
            var_s2 += 2;
        }
        var_s3 += 0xD;
    }

    // Draw selected characters
    var_s0 = menuNmEnt->unk_056C.trans[0];
    var_s3 = menuNmEnt->unk_056C.trans[1];
    for (var_s4 = 0; var_s4 < 4; var_s4++) {
        fontXX_drawID(&gfx, var_s0, var_s3, 12.0f, 12.0f, (u8)menuNmEnt->unk_002C[menuNmEnt->unk_0004][var_s4]);
        var_s0 += 0xD;
    }

    gSPDisplayList(gfx++, fade_alpha_texture_init_dl);

    temp_s1 = _getTexName(menuNmEnt->watchMenuRef, 0);
    temp = _getTexName(menuNmEnt->watchMenuRef, 1);
    menuItem_drawAlphaTex(&menuNmEnt->unk_05FC, &gfx, temp_s1, temp, 0);

    sp24[0] = &menuNmEnt->unk_030C;
    menuCursor_draw(sp24, 1, &gfx);

    *gfxP = gfx;
}

void func_80056C84(MenuRankBase *menuRankBase, struct_watchMenu *watchMenuRef, s32 arg2, s32 arg3) {
    menuRankBase->watchMenuRef = watchMenuRef;
    menuItem_init(&menuRankBase->unk_04, arg2, arg3);
}

void func_80056CAC(MenuRankBase *arg0, SMenuItem *arg1) {
    menuItem_update(&arg0->unk_04, arg1);
}

void menuRankBase_draw(MenuRankBase *rankBaseArr[], s32 count, Gfx **gfxP) {
    Gfx *gfx = *gfxP;
    s32 i;

    gSPDisplayList(gfx++, fade_normal_texture_init_dl);

    for (i = 0; i < 2; i++) {
        s32 var_s3 = 0;
        s32 j;

        for (j = 0; j < count; j++) {
            MenuRankBase *temp_v0 = rankBaseArr[j];
            SMenuItem *item = &temp_v0->unk_04;
            f32 temp_fs0 = item->trans[1];
            TiTexData *temp;

            item->trans[1] = temp_fs0 + i * 8;
            temp = _getTexRank(temp_v0->watchMenuRef, 5);
            var_s3 += menuItem_drawItem(item, &gfx, temp, var_s3, 2, i);
            item->trans[1] = temp_fs0;
        }
    }

    *gfxP = gfx;
}

void func_80056DF0(MenuRankNum *menuRankNum, struct_watchMenu *watchMenuRef, s32 arg2, s32 arg3, s32 arg4) {
    menuRankNum->watchMenuRef = watchMenuRef;
    menuRankNum->unk_04 = arg2;
    menuItem_init(&menuRankNum->unk_08, arg3, arg4);
}

void func_80056E1C(MenuRankNum *arg0, SMenuItem *arg1) {
    menuItem_update(&arg0->unk_08, arg1);
}

void menuRankNum_draw(MenuRankNum *rankNumArr[], s32 count, Gfx **gfxP) {
    Gfx *gfx = *gfxP;
    s32 var_s6;
    bool var_s4;
    bool cached;

    for (var_s6 = -1; var_s4 = false, cached = false, var_s6 < 0xA; var_s6++) {
        s32 var_s7;

        for (var_s7 = 0; var_s7 < count; var_s7++) {
            MenuRankNum *rankNum = rankNumArr[var_s7];
            SMenuItem *item = &rankNum->unk_08;
            TiTexData *temp_s2;
            TiTexData *temp_v0_2;

            if (var_s6 != rankNum->unk_04) {
                continue;
            }

            if (var_s6 == -1) {
                if (!var_s4) {
                    var_s4 = true;
                    gSPDisplayList(gfx++, fade_normal_texture_init_dl);
                }

                temp_s2 = _getTexRank(rankNum->watchMenuRef, 6);
                cached += menuItem_drawTex(item, &gfx, temp_s2, cached);
            } else {
                f32 temp_fs1;
                f32 temp_fs0;

                if (!var_s4) {
                    var_s4 = true;
                    gSPDisplayList(gfx++, fade_alpha_texture_init_dl);
                }

                temp_s2 = _getTexGameP1(rankNum->watchMenuRef, 2);
                temp_v0_2 = _getTexGameP1(rankNum->watchMenuRef, 6);

                temp_fs1 = item->trans[0];
                temp_fs0 = item->trans[1];

                item->trans[0] += 2.0f;
                item->trans[1] += 2.0f;

                cached += menuItem_drawAlphaItem(item, &gfx, temp_s2, temp_v0_2, cached, 0xC, rankNum->unk_04 + 2);
                item->trans[0] = temp_fs1;
                item->trans[1] = temp_fs0;
            }
        }
    }

    *gfxP = gfx;
}

const u8 _color_9658[][3] = {
    { 255, 255, 255 }, // MENURANKFIG_COLOR_WHITE
    { 242, 96, 96 },   // MENURANKFIG_COLOR_RED
    { 0, 0, 255 },     // MENURANKFIG_COLOR_BLUE
    { 255, 255, 0 },   // MENURANKFIG_COLOR_YELLOW
    { 106, 243, 79 },  // MENURANKFIG_COLOR_GREEN
    { 255, 154, 83 },  // MENURANKFIG_COLOR_ORANGE
    { 255, 152, 195 }, // MENURANKFIG_COLOR_PINK
    { 74, 226, 227 },  // MENURANKFIG_COLOR_CYAN
};

static_assert(ARRAY_COUNT(_color_9658) == MENURANKFIG_COLOR_MAX, "");

void menuRankFig_init(MenuRankFig *menuRankFig, struct_watchMenu *watchMenuRef, u32 arg2, s32 arg3,
                      MenuRankFigColor color, s32 arg5, s32 arg6) {
    SMenuItem *item;
    const u8 *ptr;
    s32 i;

    menuRankFig->watchMenuRef = watchMenuRef;
    if (arg2 <= ARRAY_COUNTU(menuRankFig->unk_0C)) {
        menuRankFig->unk_04 = 7;
        menuRankFig->unk_08 = arg2;
    } else if (arg2 == 0x8) {
        menuRankFig->unk_04 = arg2;
        menuRankFig->unk_08 = 5;
    } else if (arg2 == 0x9) {
        menuRankFig->unk_04 = arg2;
        menuRankFig->unk_08 = 6;
    } else if (arg2 == 0xA) {
        menuRankFig->unk_04 = arg2;
        menuRankFig->unk_08 = 7;
    } else if (arg2 == 0xB) {
        menuRankFig->unk_04 = arg2;
        menuRankFig->unk_08 = 6;
    } else if (arg2 == 0xC) {
        menuRankFig->unk_04 = arg2;
        menuRankFig->unk_08 = 5;
    } else if (arg2 == 0xD) {
        menuRankFig->unk_04 = arg2;
        menuRankFig->unk_08 = 3;
    }

    menuRankFig->unk_34 = arg3;
    menuItem_init(&menuRankFig->unk_38, arg5, arg6);

    item = &menuRankFig->unk_38;
    ptr = _color_9658[color];
    for (i = 0; i < ARRAY_COUNT(_color_9658[color]); i++) {
        item->colorRange[0][i] = item->colorRange[1][i] = ptr[i] * (DOUBLE_LITERAL(1) / 255);
    }
}

void menuRankFig_update(MenuRankFig *rankFig, SMenuItem *arg1) {
    s32 var_t1 = rankFig->unk_34;
    s32 i;

    switch (rankFig->unk_04) {
        case 0x7:
            for (i = rankFig->unk_08 - 1; i >= 0; i--) {
                rankFig->unk_0C[i] = var_t1 % 10;
                var_t1 /= 10;
            }
            break;

        case 0x8:
            rankFig->unk_0C[4] = var_t1 % 10;
            var_t1 /= 10;
            rankFig->unk_0C[3] = var_t1 % 6;
            var_t1 /= 6;
            rankFig->unk_0C[2] = 0xF;
            rankFig->unk_0C[1] = var_t1 % 10;
            var_t1 /= 10;
            rankFig->unk_0C[0] = var_t1 % 10;
            break;

        case 0x9:
            rankFig->unk_0C[5] = 0x10;
            rankFig->unk_0C[3] = 0x11;
            rankFig->unk_0C[4] = var_t1 % 10;
            var_t1 /= 10;
            rankFig->unk_0C[2] = var_t1 % 10;
            var_t1 /= 10;
            rankFig->unk_0C[1] = var_t1 % 10;
            var_t1 /= 10;
            rankFig->unk_0C[0] = var_t1 % 10;
            break;

        case 0xA:
            rankFig->unk_0C[6] = var_t1 % 10;
            var_t1 /= 10;
            rankFig->unk_0C[5] = var_t1 % 10;
            rankFig->unk_0C[4] = 0xB;
            rankFig->unk_0C[3] = 0xC;
            rankFig->unk_0C[2] = 0x12;
            rankFig->unk_0C[1] = 0xC;
            rankFig->unk_0C[0] = 0xB;
            break;

        case 0xB:
            rankFig->unk_0C[5] = var_t1 % 10;
            var_t1 /= 10;
            rankFig->unk_0C[4] = 0xF;
            rankFig->unk_0C[3] = var_t1 % 10;
            var_t1 /= 10;
            rankFig->unk_0C[2] = var_t1 % 6;
            var_t1 /= 6;
            rankFig->unk_0C[1] = 0xF;
            rankFig->unk_0C[0] = var_t1 % 10;
            break;

        case 0xC:
            rankFig->unk_0C[0] = 0xA;
            rankFig->unk_0C[1] = 0xB;
            rankFig->unk_0C[2] = 0xC;
            rankFig->unk_0C[3] = 0xD;
            rankFig->unk_0C[4] = 0xE;
            break;

        case 0xD:
            rankFig->unk_0C[0] = 0xD;
            rankFig->unk_0C[1] = 0xB;
            rankFig->unk_0C[2] = 0xB;
            break;
    }

    menuItem_update(&rankFig->unk_38, arg1);
}

// shift-jis string
char _code_9711[] = "０１２３４５６７８９ＣＬＥＡＲ：％．Ｖ";

const s32 _posX_0_9712[] = {
    0x00000000, 0x00000009, 0x00000012, 0x0000001B, 0x00000024,
    0x0000002D, 0x00000036, 0x0000003F, 0x00000048, 0x00000051,
};

const s32 _posX_1_9713[] = {
    0x00000000, 0x00000009, 0x00000010, 0x00000017, 0x00000020,
};

const s32 _posX_2_9714[] = {
    0x00000000, 0x00000009, 0x00000012, 0x0000001B, 0x0000001F, 0x00000028,
};

const s32 _posX_4_9715[] = {
    0x00000000, 0x00000007, 0x0000000E, 0x00000017, 0x0000001E, 0x00000025,
};

const s32 *_posX_tbl_9716[] = {
    _posX_0_9712, _posX_1_9713, _posX_2_9714, _posX_0_9712, _posX_4_9715, _posX_0_9712, _posX_0_9712,
};

MainMenuMode _menuAll_lastMode = MODE_MAIN;

void menuRankFig_draw(MenuRankFig **rankFigArr, s32 count, Gfx **gfxP) {
    Gfx *gfx = *gfxP;
    f32 sp24 = 9.0f;
    s32 i;

    font16_initDL2(&gfx);

    gDPSetTextureFilter(gfx++, G_TF_BILERP);

    for (i = 0; i < 0x13U; i++) {
        s32 index = font2index(&_code_9711[i * 2]);
        s32 j;

        for (j = 0; j < count; j++) {
            MenuRankFig *rankFig = rankFigArr[j];
            SMenuItem *item = &rankFig->unk_38;
            s32 k;

            for (k = 0; k < rankFig->unk_08; k++) {
                if ((i != rankFig->unk_0C[k]) || menuItem_outOfScreen(item, sp24, 0xC)) {
                    continue;
                }

                menuItem_setPrim(item, &gfx);

#if VERSION_US || VERSION_GW
                if (fontXX_drawID2(&gfx, item->trans[0] + _posX_tbl_9716[rankFig->unk_04 - 7][k] * item->scale[0],
                                   item->trans[1], item->scale[0] * 9.0f, item->scale[1] * 12.0f, index)) {
                    index = -1;
                }
#elif VERSION_CN
                if ((rankFig->unk_08 >= 6) && (rankFig->unk_0C[0] == 0xB) && (rankFig->unk_0C[1] == 0xC) &&
                    (rankFig->unk_0C[2] == 0x12) && (rankFig->unk_0C[3] == 0xC) &&
                    (rankFig->unk_0C[4] == rankFig->unk_0C[0])) {
                    if (k < 5) {
                        continue;
                    }
                    fontXX_drawID2(&gfx, item->trans[0] + _posX_tbl_9716[rankFig->unk_04 - 7][k - 2] * item->scale[0],
                                   item->trans[1], item->scale[0] * sp24, item->scale[1] * 12.0f, index);
                } else {
                    fontXX_drawID2(&gfx, item->trans[0] + _posX_tbl_9716[rankFig->unk_04 - 7][k] * item->scale[0],
                                   item->trans[1], item->scale[0] * sp24, item->scale[1] * 12.0f, index);
                }
                index = -1;
#else
#error ""
#endif
            }
        }
    }

    *gfxP = gfx;
}

const u8 RO_800B1210[] = { 0x80, 0x80, 0x80 };

void menuRankName_init(MenuRankName *menuRankName, struct_watchMenu *watchMenuRef, u8 arg2[4], s32 arg3, s32 arg4) {
    SMenuItem *item;
    s32 i;

    menuRankName->watchMenuRef = watchMenuRef;
    for (i = 0; i < ARRAY_COUNTU(menuRankName->unk_04); i++) {
        menuRankName->unk_04[i] = arg2[i];
    }

    item = &menuRankName->unk_08;
    menuItem_init(item, arg3, arg4);

    for (i = 0; i < ARRAY_COUNT(RO_800B1210); i++) {
        item->colorRange[0][i] = item->colorRange[1][i] = RO_800B1210[i] * (DOUBLE_LITERAL(1) / 255);
    }
}

void func_80057724(MenuRankName *arg0, SMenuItem *arg1) {
    menuItem_update(&arg0->unk_08, arg1);
}

void menuRankName_draw(MenuRankName *rankNameArr[], s32 count, Gfx **gfxP) {
    Gfx *gfx = *gfxP;
    SMenuItem *temp_s1;
    MenuRankName *temp_s2;
    f32 var_fs0;
    s32 var_s0;
    s32 var_s4;
    f32 temp = 13.0f;

    font16_initDL2(&gfx);

    gDPSetTextureFilter(gfx++, G_TF_BILERP);

    for (var_s4 = 0; var_s4 < count; var_s4++) {
        temp_s2 = rankNameArr[var_s4];
        temp_s1 = &temp_s2->unk_08;

        //! FAKE: temp + 39
        if (menuItem_outOfScreen(temp_s1, temp + 39, 0xC)) {
            continue;
        }

        var_fs0 = temp_s1->trans[0];
        menuItem_setPrim(temp_s1, &gfx);

        for (var_s0 = 0; var_s0 < 4; var_s0++) {
            fontXX_drawID2(&gfx, var_fs0, temp_s1->trans[1], 12.0f, temp_s1->scale[1] * 12.0f, temp_s2->unk_04[var_s0]);
            var_fs0 += temp;
        }
    }

    *gfxP = gfx;
}

void func_80057898(MenuRankLabel *menuRankLabel, struct_watchMenu *watchMenuRef, s32 type, s32 id, s32 x, s32 y) {
    menuRankLabel->watchMenuRef = watchMenuRef;
    menuRankLabel->type = type;
    menuRankLabel->id = id;
    menuItem_init(&menuRankLabel->unk_0C, x, y);
}

void func_800578C8(MenuRankLabel *arg0, SMenuItem *arg1) {
    menuItem_update(&arg0->unk_0C, arg1);
}

const s32 _rows_9879[] = {
    9,
    2,
    6,
    7,
};

const s32 _tex_9880[] = {
    0,
    8,
    1,
};

const s32 _choice_9881[] = {
    4, 5, 6, 0x1D, 0x1E, 0x1F, 0x20,
};

void menuRankLabel_draw(MenuRankLabel *rankLabelArr[], s32 count, Gfx **gfxP) {
    Gfx *gfx = *gfxP;
    s32 i;
    s32 var_s5;

    gSPDisplayList(gfx++, fade_normal_texture_init_dl);

    for (i = 0; var_s5 = _rows_9879[i], i < ARRAY_COUNT(_rows_9879); i++) {
        s32 j;
        s32 var_s0;

        for (j = 0; var_s0 = 0, j < var_s5; j++) {
            s32 k;

            for (k = 0; k < count; k++) {
                MenuRankLabel *rankLabel = rankLabelArr[k];
                SMenuItem *item = &rankLabel->unk_0C;
                TiTexData *var_a2;

                if ((i != rankLabel->type) || (j != rankLabel->id)) {
                    continue;
                }

                switch (i) {
                    case 0:
                        var_a2 = _getTexRank(rankLabel->watchMenuRef, 7);
                        var_s0 += menuItem_drawItem(item, &gfx, var_a2, var_s0, var_s5, j);
                        break;

                    case 1:
                    case 2:
                        var_a2 = _getTexRank(rankLabel->watchMenuRef, _tex_9880[i]);
                        var_s0 += menuItem_drawItem(item, &gfx, var_a2, var_s0, var_s5, j);
                        break;

                    case 3:
                        var_a2 = _getTexCommon(rankLabel->watchMenuRef, 0xE);
                        var_s0 += menuItem_drawItem(item, &gfx, var_a2, var_s0, 0x2F, _choice_9881[j]);
                        break;
                }
            }
        }
    }

    *gfxP = gfx;
}

void func_80057AFC(MenuRankHeader *menuRankHeader, struct_watchMenu *watchMenuRef, const s32 *typeP, const s32 *idP,
                   const s32 *xP, const s32 *yP, s32 count, s32 arg7, s32 arg8) {
    s32 i;

    menuRankHeader->watchMenuRef = watchMenuRef;
    menuRankHeader->unk_04 = count;
    menuItem_init(&menuRankHeader->unk_08, arg7, arg8);

    for (i = 0; i < count; i++) {
        func_80057898(&menuRankHeader->unk_98[i], watchMenuRef, typeP[i], idP[i], xP[i], yP[i]);
    }
}

void func_80057BE8(MenuRankHeader *rankHeader, SMenuItem *arg1) {
    s32 i;

    menuItem_update(&rankHeader->unk_08, arg1);

    for (i = 0; i < rankHeader->unk_04; i++) {
        func_800578C8(&rankHeader->unk_98[i], &rankHeader->unk_08);
    }
}

void menuRankHeader_draw(MenuRankHeader *rankHeaderArr[], s32 count, Gfx **gfxP) {
    Gfx *gfx = *gfxP;
    s32 newCount = 0;
    MenuRankLabel *arr[count * 5];
    s32 i;

    for (i = 0; i < count; i++) {
        MenuRankHeader *rankHeader = rankHeaderArr[i];
        s32 j;

        for (j = 0; j < rankHeader->unk_04; j++) {
            arr[newCount] = &rankHeader->unk_98[j];
            newCount++;
        }
    }

    menuRankLabel_draw(arr, newCount, &gfx);

    *gfxP = gfx;
}

void func_80057D24(MenuRankPanel *menuRankPanel, struct_watchMenu *watchMenuRef, s32 arg2, u8 *arg3, u32 arg4, s32 arg5,
                   s32 arg6, s32 arg7, s32 arg8) {
    s32 var_a2;
    s32 var_v1;

    menuRankPanel->watchMenuRef = watchMenuRef;
    menuRankPanel->unk_004 = 0;

    func_80056C84(&menuRankPanel->unk_008, watchMenuRef, arg7, arg8);
    func_80056DF0(&menuRankPanel->unk_09C, watchMenuRef, arg2, 4, -1);
    menuRankName_init(&menuRankPanel->unk_134, watchMenuRef, arg3, 0x1A, 2);
    menuRankFig_init(&menuRankPanel->unk_1CC, watchMenuRef, 7, arg4, MENURANKFIG_COLOR_RED, 0x83, 2);
    menuRankFig_init(&menuRankPanel->unk_294, watchMenuRef, 8, arg5, MENURANKFIG_COLOR_BLUE, 0xCD, 2);
    var_v1 = 0x5A;
    if (arg6 < 0xA) {
        var_a2 = 1;
        var_v1 = 0x63;
    } else {
        var_a2 = 0xD;
    }
    menuRankFig_init(&menuRankPanel->unk_35C, watchMenuRef, var_a2, arg6, MENURANKFIG_COLOR_YELLOW, var_v1, 2);
}

void func_80057E68(MenuRankPanel *menuRankPanel, struct_watchMenu *watchMenuRef, s32 arg2, u8 *arg3, s32 arg4, s32 arg5,
                   s32 arg6, s32 arg7) {
    menuRankPanel->watchMenuRef = watchMenuRef;
    menuRankPanel->unk_004 = 1;

    func_80056C84(&menuRankPanel->unk_008, watchMenuRef, arg6, arg7);
    func_80056DF0(&menuRankPanel->unk_09C, watchMenuRef, arg2, 4, -1);
    menuRankName_init(&menuRankPanel->unk_134, watchMenuRef, arg3, 0x29, 2);
    menuRankFig_init(&menuRankPanel->unk_1CC, watchMenuRef, 0xAU, arg4, MENURANKFIG_COLOR_GREEN, 0x6A, 2);
    menuRankFig_init(&menuRankPanel->unk_294, watchMenuRef, 7U, arg5, MENURANKFIG_COLOR_RED, 0xB7, 2);
}

void func_80057F6C(MenuRankPanel *menuRankPanel, struct_watchMenu *watchMenuRef, s32 arg2, u8 *arg3, s32 arg4, s32 arg5,
                   s32 arg6, s32 arg7) {
    menuRankPanel->watchMenuRef = watchMenuRef;
    menuRankPanel->unk_004 = 2;

    func_80056C84(&menuRankPanel->unk_008, watchMenuRef, arg6, arg7);
    func_80056DF0(&menuRankPanel->unk_09C, watchMenuRef, arg2, 4, -1);
    menuRankName_init(&menuRankPanel->unk_134, watchMenuRef, arg3, 0x29, 2);
    menuRankFig_init(&menuRankPanel->unk_1CC, watchMenuRef, 8U, arg4, MENURANKFIG_COLOR_BLUE, 0x75, 2);
    menuRankFig_init(&menuRankPanel->unk_294, watchMenuRef, 7U, arg5, MENURANKFIG_COLOR_RED, 0xB7, 2);
}

void func_8005806C(MenuRankPanel *menuRankPanel, struct_watchMenu *watchMenuRef, s32 arg2, u8 *arg3, s32 arg4, s32 arg5,
                   s32 arg6, s32 arg7, s32 arg8, s32 arg9) {
    s32 var_a2;
    s32 var_v1;

    menuRankPanel->watchMenuRef = watchMenuRef;
    menuRankPanel->unk_004 = 3;

    func_80056C84(&menuRankPanel->unk_008, watchMenuRef, arg8, arg9);
    func_80056DF0(&menuRankPanel->unk_09C, watchMenuRef, arg2, 4, -1);
    menuRankName_init(&menuRankPanel->unk_134, watchMenuRef, arg3, 0x1A, 2);
    menuRankFig_init(&menuRankPanel->unk_1CC, watchMenuRef, 7U, arg4, MENURANKFIG_COLOR_RED, 0x53, 2);
    menuRankFig_init(&menuRankPanel->unk_294, watchMenuRef, 0xBU, arg5, MENURANKFIG_COLOR_BLUE, 0x99, 2);

    if (arg6 < dm_get_first_virus_count_in_new_mode(arg7)) {
        var_a2 = 2;
        var_v1 = 0xD9;
    } else {
        var_a2 = 0xD;
        var_v1 = 0xD5;
    }
    menuRankFig_init(&menuRankPanel->unk_35C, watchMenuRef, var_a2, arg6, MENURANKFIG_COLOR_RED, var_v1, 2);
}

void func_800581C8(MenuRankPanel *menuRankPanel, struct_watchMenu *watchMenuRef, s32 arg2, u8 *arg3, s32 arg4, s32 arg5,
                   s32 arg6, s32 arg7, s32 arg8) {
    menuRankPanel->watchMenuRef = watchMenuRef;
    menuRankPanel->unk_004 = 4;

    func_80056C84(&menuRankPanel->unk_008, watchMenuRef, arg7, arg8);
    func_80056DF0(&menuRankPanel->unk_09C, watchMenuRef, arg2, 4, -1);
    menuRankName_init(&menuRankPanel->unk_134, watchMenuRef, arg3, 0x1A, 2);
    menuRankFig_init(&menuRankPanel->unk_1CC, watchMenuRef, 9U, arg4, MENURANKFIG_COLOR_ORANGE, 0x5A, 2);
    menuRankFig_init(&menuRankPanel->unk_294, watchMenuRef, 2U, arg5, MENURANKFIG_COLOR_PINK, 0xA7, 2);
    menuRankFig_init(&menuRankPanel->unk_35C, watchMenuRef, 2U, arg6, MENURANKFIG_COLOR_CYAN, 0xD9, 2);
}

void menuRankPanel_update(MenuRankPanel *arg0, SMenuItem *arg1) {
    func_80056CAC(&arg0->unk_008, arg1);
    func_80056E1C(&arg0->unk_09C, &arg0->unk_008.unk_04);
    func_80057724(&arg0->unk_134, &arg0->unk_008.unk_04);

    switch (arg0->unk_004) {
        case 0x0:
            menuRankFig_update(&arg0->unk_1CC, &arg0->unk_008.unk_04);
            menuRankFig_update(&arg0->unk_294, &arg0->unk_008.unk_04);
            menuRankFig_update(&arg0->unk_35C, &arg0->unk_008.unk_04);
            break;

        case 0x1:
            menuRankFig_update(&arg0->unk_1CC, &arg0->unk_008.unk_04);
            menuRankFig_update(&arg0->unk_294, &arg0->unk_008.unk_04);
            break;

        case 0x2:
            menuRankFig_update(&arg0->unk_1CC, &arg0->unk_008.unk_04);
            menuRankFig_update(&arg0->unk_294, &arg0->unk_008.unk_04);
            break;

        case 0x3:
            menuRankFig_update(&arg0->unk_1CC, &arg0->unk_008.unk_04);
            menuRankFig_update(&arg0->unk_294, &arg0->unk_008.unk_04);
            menuRankFig_update(&arg0->unk_35C, &arg0->unk_008.unk_04);
            break;

        case 0x4:
            menuRankFig_update(&arg0->unk_1CC, &arg0->unk_008.unk_04);
            menuRankFig_update(&arg0->unk_294, &arg0->unk_008.unk_04);
            menuRankFig_update(&arg0->unk_35C, &arg0->unk_008.unk_04);
            break;
    }
}

void menuRankPanel_draw(MenuRankPanel **arg0, s32 count, Gfx **gfxP) {
    Gfx *gfx = *gfxP;
    void *sp10[count * 4];
    MenuRankPanel *temp_a2;
    s32 var_a1;
    s32 i;

    var_a1 = 0;
    for (i = 0; i < count; i++) {
        temp_a2 = arg0[i];

        sp10[var_a1++] = &temp_a2->unk_008;
    }
    menuRankBase_draw((void *)sp10, var_a1, &gfx);

    var_a1 = 0;
    for (i = 0; i < count; i++) {
        temp_a2 = arg0[i];

        sp10[var_a1++] = &temp_a2->unk_09C;
    }
    menuRankNum_draw((void *)sp10, var_a1, &gfx);

    var_a1 = 0;
    for (i = 0; i < count; i++) {
        temp_a2 = arg0[i];

        sp10[var_a1++] = &temp_a2->unk_134;
    }
    menuRankName_draw((void *)sp10, var_a1, &gfx);

    var_a1 = 0;
    for (i = 0; i < count; i++) {
        temp_a2 = arg0[i];

        switch (temp_a2->unk_004) {
            case 0x1:
                sp10[var_a1++] = &temp_a2->unk_1CC;
                sp10[var_a1++] = &temp_a2->unk_294;
                break;

            case 0x2:
                sp10[var_a1++] = &temp_a2->unk_294;
                sp10[var_a1++] = &temp_a2->unk_1CC;
                break;

            case 0x0:
            case 0x3:
            case 0x4:
                sp10[var_a1++] = &temp_a2->unk_1CC;
                sp10[var_a1++] = &temp_a2->unk_294;
                sp10[var_a1++] = &temp_a2->unk_35C;
                break;
        }
    }
    menuRankFig_draw((void *)sp10, var_a1, &gfx);

    *gfxP = gfx;
}

void menuRank_setNameBaseScale(MenuRank *menuRank, s32 arg1, f32 arg2) {
    SMenuItem *sp18[3];
    s32 i;

    sp18[0] = &menuRank->unk_032C;
    sp18[1] = &menuRank->unk_020C[0];
    sp18[2] = &menuRank->unk_020C[1];
    for (i = 0; i < ARRAY_COUNTU(sp18); i++) {
        SMenuItem *item = sp18[i];
        f32 temp = 8.0f;

        item->scaleRange[0][1] = 0.0f;
        item->transStep = 0.1f;
        item->scaleStep = 0.1f;
        item->transTime = arg2;
        item->scaleTime = arg2;
        item->transRange[0][0] = item->transRange[1][0];
        item->transRange[0][1] = item->transRange[1][1] + temp;
        item->scaleRange[0][0] = item->scaleRange[1][0];
        menuItem_setTransDir(item, arg1);
        menuItem_setScaleDir(item, arg1);
    }
}

void menuRank_setSlide(MenuRank *menuRank, s32 arg1, s32 arg2, f32 arg3, f32 arg4) {
    MenuRank_unk_590 *temp_s2 = &menuRank->unk_590[arg1];
    SMenuItem *item;
    s32 i;

    item = &temp_s2->unk_0004.unk_08;
    item->transRange[0][0] = item->transRange[1][0] + arg4;
    item->transRange[0][1] = item->transRange[1][1];
    item->transStep = 0.05f;
    item->transTime = arg3;
    menuItem_setTransDir(item, arg2);

    for (i = 0; i < temp_s2->unk_0000; i++) {
        item = &temp_s2->unk_3A8[i].unk_008.unk_04;

        item->transRange[0][0] = item->transRange[1][0] + arg4;
        item->transRange[0][1] = item->transRange[1][1];
        item->transStep = 0.05f;
        item->transTime = arg3;
        menuItem_setTransDir(item, arg2);
    }

    arg2 = (arg2 < 0) ? -1 : 1;

    for (i = 0; i < temp_s2->unk_0000; i++) {
        item = &temp_s2->unk_3A8[i].unk_008.unk_04;

        item->transStep -= arg2 * 0.05 * i / (temp_s2->unk_0000 * 2);
        menuItem_setTransDir(item, arg2);
    }
}

const s32 _pos_10346[] = {
    -0x140,
    0x140,
};

void menuRank_setFrame(MenuRank *menuRank, s32 arg1, s32 arg2, f32 arg3) {
    MenuRank_unk_590 *temp_fp = &menuRank->unk_590[arg1];
    SMenuItem *item;
    s32 i;

    item = &menuRank->unk_03BC.unk_0C;
    item->transRange[0][0] = item->transRange[1][0];
    item->transRange[0][1] = item->transRange[1][1] - 120.0f;
    item->transStep = 0.05f;
    item->transTime = arg3;
    menuItem_setTransDir(item, arg2);

    for (i = 0; i < ARRAY_COUNTU(menuRank->unk_020C); i++) {
        item = &menuRank->unk_020C[i];

        item->transRange[0][0] = item->transRange[1][0];
        item->transRange[0][1] = item->transRange[1][1] - 120.0f;
        item->transStep = 0.05f;
        item->transTime = arg3;
        menuItem_setTransDir(item, arg2);
    }

    item = &temp_fp->unk_0004.unk_08;
    item->transRange[0][0] = item->transRange[1][0];
    item->transRange[0][1] = item->transRange[1][1] - 120.0f;
    item->transStep = 0.05f;
    item->transTime = arg3;
    menuItem_setTransDir(item, arg2);

    item = &menuRank->unk_032C;
    item->transRange[0][0] = item->transRange[1][0];
    item->transRange[0][1] = item->transRange[1][1] - 120.0f;
    item->transStep = 0.05f;
    item->transTime = arg3;
    menuItem_setTransDir(item, arg2);

    for (i = 0; i < temp_fp->unk_0000; i++) {
        item = &temp_fp->unk_3A8[i].unk_008.unk_04;

        item->transRange[0][0] = item->transRange[1][0] + _pos_10346[i % ARRAY_COUNTU(_pos_10346)];
        item->transRange[0][1] = item->transRange[1][1];
        item->transStep = 0.05f;
        item->transTime = arg3;
        menuItem_setTransDir(item, arg2);
    }
}

void func_80058A24(MenuRank *menuRank, s32 arg1 UNUSED) {
    menuItem_init(&menuRank->unk_032C, 0xA4, 0x30);
    func_80057898(&menuRank->unk_0458, menuRank->watchMenuRef, 1, 1, 2, 2);
    func_80057898(&menuRank->unk_04F4, menuRank->watchMenuRef, 2, 1, 0x3E, 2);
}

const s32 _hedAllType_10392[] = {
    0,
    0,
    0,
    0,
};

const s32 _hedStoryId_10393[] = {
    0,
    3,
    1,
    2,
};
const s32 _hedStoryX_10394[] = {
    0x20,
    0x55,
    0x8F,
    0xCE,
};
const s32 _hedStoryY_10395[] = {
    0,
    0,
    0,
    0,
};
static_assert(ARRAY_COUNT(_hedStoryId_10393) == ARRAY_COUNT(_hedStoryX_10394), "");
static_assert(ARRAY_COUNT(_hedStoryId_10393) == ARRAY_COUNT(_hedStoryY_10395), "");

const s32 _hedLevelId_10396[] = {
    0,
    4,
    1,
};
const s32 _hedLevelX_10397[] = {
    0x2F,
    0x6E,
    0xC3,
};
const s32 _hedLevelY_10398[] = {
    0,
    0,
    0,
};
static_assert(ARRAY_COUNT(_hedLevelId_10396) == ARRAY_COUNT(_hedLevelX_10397), "");
static_assert(ARRAY_COUNT(_hedLevelId_10396) == ARRAY_COUNT(_hedLevelY_10398), "");

const s32 _hed1PTaiQId_10399[] = {
    0,
    2,
    1,
};
const s32 _hed1PTaiQX_10400[] = {
    0x2F,
    0x76,
    0xC3,
};
const s32 _hed1PTaiQY_10401[] = {
    0,
    0,
    0,
};
static_assert(ARRAY_COUNT(_hed1PTaiQId_10399) == ARRAY_COUNT(_hed1PTaiQX_10400), "");
static_assert(ARRAY_COUNT(_hed1PTaiQId_10399) == ARRAY_COUNT(_hed1PTaiQY_10401), "");

const s32 _hed1PTimeAtId_10402[] = {
    0,
    1,
    2,
    8,
};
const s32 _hed1PTimeAtX_10403[] = {
    0x20,
    0x5F,
    0x9C,
    0xCE,
};
const s32 _hed1PTimeAtY_10404[] = {
    0,
    0,
    0,
    0,
};
static_assert(ARRAY_COUNT(_hed1PTimeAtId_10402) == ARRAY_COUNT(_hed1PTimeAtX_10403), "");
static_assert(ARRAY_COUNT(_hed1PTimeAtId_10402) == ARRAY_COUNT(_hed1PTimeAtY_10404), "");

const s32 _hedVsId_10405[] = {
    0,
    5,
    6,
    7,
};
const s32 _hedVsX_10406[] = {
    0x20,
    0x5F,
    0x9C,
    0xCE,
};
const s32 _hedVsY_10407[] = {
    0,
    0,
    0,
    0,
};
static_assert(ARRAY_COUNT(_hedVsId_10405) == ARRAY_COUNT(_hedVsX_10406), "");
static_assert(ARRAY_COUNT(_hedVsId_10405) == ARRAY_COUNT(_hedVsY_10407), "");

// Make sure `_hedAllType_10392` has as many elements as the largest array of the bunch
static_assert(ARRAY_COUNT(_hedAllType_10392) >=
                  MAX(MAX(ARRAY_COUNT(_hedStoryId_10393), ARRAY_COUNT(_hedLevelId_10396)),
                      MAX(MAX(ARRAY_COUNT(_hed1PTaiQId_10399), ARRAY_COUNT(_hed1PTimeAtId_10402)),
                          ARRAY_COUNT(_hedVsId_10405))),
              "");

static_assert(ARRAY_COUNT(_hedAllType_10392) <= MENURANKHEADER_UNK_98, "");

void menuRank_setPanel(MenuRank *menuRank, s32 arg1, MainMenuMode arg2, s32 arg3) {
    MenuRank_unk_590 *temp_s3 = &menuRank->unk_590[arg1];
    SRankSortInfo *temp_s2 = &menuRank->unk_001C;
    const s32 *idP;
    const s32 *xP;
    const s32 *yP;
    s32 sp3C;
    s32 count;
    s32 i;

    temp_s3->unk_0000 = 8;

    switch (arg2) {
        case MODE_RECORD_ST:
            sp3C = 0;
            break;

        case MODE_RECORD_LS:
            sp3C = 1;
            break;

        case MODE_RECORD_VC:
            sp3C = 2;
            break;

        case MODE_RECORD_VM:
            sp3C = 3;
            break;

        case MODE_RECORD_VC_FL:
        case MODE_RECORD_VM_FL:
            sp3C = 4;
            break;

        case MODE_RECORD_LS_TQ:
            sp3C = 5;
            break;

        case MODE_RECORD_LS_TA:
        case MODE_RECORD_VM_TA:
            sp3C = 6;
            break;

        default:
            break;
    }

    switch (arg2) {
        case MODE_RECORD_ST:
            count = ARRAY_COUNT(_hedStoryId_10393);
            idP = _hedStoryId_10393;
            xP = _hedStoryX_10394;
            yP = _hedStoryY_10395;
            break;

        case MODE_RECORD_LS:
            count = ARRAY_COUNT(_hedLevelId_10396);
            idP = _hedLevelId_10396;
            xP = _hedLevelX_10397;
            yP = _hedLevelY_10398;
            break;

        case MODE_RECORD_LS_TQ:
            count = ARRAY_COUNT(_hed1PTaiQId_10399);
            idP = _hed1PTaiQId_10399;
            xP = _hed1PTaiQX_10400;
            yP = _hed1PTaiQY_10401;
            break;

        case MODE_RECORD_LS_TA:
            count = ARRAY_COUNT(_hed1PTimeAtId_10402);
            idP = _hed1PTimeAtId_10402;
            xP = _hed1PTimeAtX_10403;
            yP = _hed1PTimeAtY_10404;
            break;

        case MODE_RECORD_VC:
        case MODE_RECORD_VC_FL:
        case MODE_RECORD_VM:
        case MODE_RECORD_VM_FL:
        case MODE_RECORD_VM_TA:
            count = ARRAY_COUNT(_hedVsId_10405);
            idP = _hedVsId_10405;
            xP = _hedVsX_10406;
            yP = _hedVsY_10407;
            break;

        default:
            break;
    }

    func_80057898(&menuRank->unk_03BC, menuRank->watchMenuRef, 3, sp3C, 0x23, 0x30);
    func_80057AFC(&temp_s3->unk_0004, menuRank->watchMenuRef, _hedAllType_10392, idP, xP, yP, count, 0, -0x10);

    for (i = 0; i < temp_s3->unk_0000; i++) {
        struct_evs_mem_data *ptr;
        struct_evs_mem_data_story_data *temp_t0;
        struct_evs_mem_data_level_data *temp_t0_2;
        struct_evs_mem_data_taiQ_data *temp_t0_3;
        struct_evs_mem_data_timeAt_data *temp_t0_4;
        u16 *var_s4;
        s32 var_s1;
        u16 *var_s7;
        u8 *var_s6;

        switch (arg2) {
            case MODE_RECORD_ST:
                var_s1 = temp_s2->story_sort[arg3][i];
                ptr = &evs_mem_data[var_s1];
                temp_t0 = &ptr->story_data[arg3];
                func_80057D24(&temp_s3->unk_3A8[i], menuRank->watchMenuRef, temp_s2->story_rank[arg3][i], ptr->mem_name,
                              temp_t0->score, temp_t0->time, temp_t0->c_stage + 1, 0, i * 0x11);
                break;

            case MODE_RECORD_LS:
                var_s1 = temp_s2->level_sort[arg3][i];
                ptr = &evs_mem_data[var_s1];
                temp_t0_2 = &ptr->level_data[arg3];
                func_80057E68(&temp_s3->unk_3A8[i], menuRank->watchMenuRef, temp_s2->level_rank[arg3][i], ptr->mem_name,
                              (s32)temp_t0_2->c_level, temp_t0_2->score, 0, i * 0x11);
                break;

            case MODE_RECORD_LS_TQ:
                var_s1 = temp_s2->taiQ_sort[arg3][i];
                ptr = &evs_mem_data[var_s1];
                temp_t0_3 = &ptr->taiQ_data[arg3];
                func_80057F6C(&temp_s3->unk_3A8[i], menuRank->watchMenuRef, temp_s2->taiQ_rank[arg3][i], ptr->mem_name,
                              temp_t0_3->time, temp_t0_3->score, 0, i * 0x11);
                break;

            case MODE_RECORD_LS_TA:
                var_s1 = temp_s2->timeAt_sort[arg3][i];
                ptr = &evs_mem_data[var_s1];
                temp_t0_4 = &ptr->timeAt_data[arg3];
                func_8005806C(&temp_s3->unk_3A8[i], menuRank->watchMenuRef, temp_s2->timeAt_rank[arg3][i],
                              ptr->mem_name, temp_t0_4->score, temp_t0_4->time, temp_t0_4->erase, arg3, 0, i * 0x11);
                break;

            case MODE_RECORD_VC:
                var_s1 = temp_s2->vscom_sort[i];
                ptr = &evs_mem_data[var_s1];
                var_s7 = temp_s2->vscom_ave;
                var_s6 = temp_s2->vscom_rank;
                var_s4 = ptr->vscom_data;
                break;

            case MODE_RECORD_VC_FL:
                var_s1 = temp_s2->vc_fl_sort[i];
                ptr = &evs_mem_data[var_s1];
                var_s7 = temp_s2->vc_fl_ave;
                var_s6 = temp_s2->vc_fl_rank;
                var_s4 = ptr->vc_fl_data;
                break;

            case MODE_RECORD_VM:
                var_s1 = temp_s2->vsman_sort[i];
                ptr = &evs_mem_data[var_s1];
                var_s7 = temp_s2->vsman_ave;
                var_s6 = temp_s2->vsman_rank;
                var_s4 = ptr->vsman_data;
                break;

            case MODE_RECORD_VM_FL:
                var_s1 = temp_s2->vm_fl_sort[i];
                ptr = &evs_mem_data[var_s1];
                var_s7 = temp_s2->vm_fl_ave;
                var_s6 = temp_s2->vm_fl_rank;
                var_s4 = ptr->vm_fl_data;
                break;

            case MODE_RECORD_VM_TA:
                var_s1 = temp_s2->vm_ta_sort[i];
                ptr = &evs_mem_data[var_s1];
                var_s7 = temp_s2->vm_ta_ave;
                var_s6 = temp_s2->vm_ta_rank;
                var_s4 = ptr->vm_ta_data;
                break;

            default:
                break;
        }

        switch (arg2) {
            case MODE_RECORD_VC:
            case MODE_RECORD_VC_FL:
            case MODE_RECORD_VM:
            case MODE_RECORD_VM_FL:
            case MODE_RECORD_VM_TA:
                ptr = &evs_mem_data[var_s1];
                func_800581C8(&temp_s3->unk_3A8[i], menuRank->watchMenuRef, var_s6[i], ptr->mem_name, var_s7[var_s1],
                              var_s4[0], var_s4[1], 0, i * 0x11);
                break;

            default:
                break;
        }
    }

    func_80058A24(menuRank, arg1);
    menuRank->unk_04F4.id = arg3;
}

const s32 _lr_10544[][2] = {
    { 0x23, 0x1E },
    { 0xDD, 0x1E },
};

void menuRank_init(MenuRank *menuRank, struct_watchMenu *watchMenuRef, void **heapP UNUSED) {
    u32 i;

    menuRank->watchMenuRef = watchMenuRef;
    menuRank->unk_0004 = _getMode(watchMenuRef);
    switch (menuRank->unk_0004) {
        case 0x35:
        case 0x36:
        case 0x38:
        case 0x39:
        case 0x3A:
            menuRank->unk_0008 = 1;
            break;

        default:
            menuRank->unk_0008 = 0;
            break;
    }

    menuRank->unk_000C = 1;
    menuRank->unk_0010 = 1;
    menuRank->unk_0014 = 0;
    menuRank->unk_0018 = -1;
    menuItem_init(&menuRank->unk_017C, 0x23, 0x56);

    for (i = 0; i < 2U; i++) {
        menuItem_init(&menuRank->unk_020C[i], _lr_10544[i][0], _lr_10544[i][1]);
    }

    switch (menuRank->unk_0004) {
        case MODE_RECORD_ST:
            dm_data_mode_story_sort(&menuRank->unk_001C);
            break;

        case MODE_RECORD_LS:
            dm_data_mode_level_sort(&menuRank->unk_001C);
            break;

        case MODE_RECORD_LS_TQ:
            dm_data_mode_taiQ_sort(&menuRank->unk_001C);
            break;

        case MODE_RECORD_LS_TA:
            dm_data_mode_timeAt_sort(&menuRank->unk_001C);
            break;

        case MODE_RECORD_VC:
            dm_data_vscom_sort(&menuRank->unk_001C);
            break;

        case MODE_RECORD_VC_FL:
            dm_data_vc_fl_sort(&menuRank->unk_001C);
            break;

        case MODE_RECORD_VM:
            dm_data_vsman_sort(&menuRank->unk_001C);
            break;

        case MODE_RECORD_VM_FL:
            dm_data_vm_fl_sort(&menuRank->unk_001C);
            break;

        case MODE_RECORD_VM_TA:
            dm_data_vm_ta_sort(&menuRank->unk_001C);
            break;

        default:
            break;
    }

    menuRank_setPanel(menuRank, menuRank->unk_0014, menuRank->unk_0004, menuRank->unk_000C);
    menuRank_setFrame(menuRank, menuRank->unk_0014, 1, 0.0f);
}

void menuRank_input(MenuRank *menuRank) {
    MenuRank_unk_590 *temp_s0 = &menuRank->unk_590[menuRank->unk_0014];
    u32 pressedButton = _getKeyTrg(menuRank->watchMenuRef, 0);
    u32 keyRep UNUSED = _getKeyRep(menuRank->watchMenuRef, 0);
    s32 direction = 0;
    SndIndex sndIndex = SND_INDEX_INVALID;
    SMenuItem *item = &menuRank->unk_032C;

    if ((item->scaleTime == 0.0f) && (item->scaleStep < 0.0f)) {
        menuRank_setNameBaseScale(menuRank, 1, 0.0f);
    }

    item = &temp_s0->unk_3A8[0].unk_008.unk_04;
    if ((item->transTime < 1.0f) || (item->transStep < 0.0f) || (item->scaleTime < 1.0f) || (item->scaleStep < 0.0f)) {
        return;
    }

    if (menuRank->unk_0008 == 0) {
        if (pressedButton & (L_JPAD | L_TRIG)) {
            direction--;
        }
        if (pressedButton & (R_JPAD | R_TRIG)) {
            direction++;
        }
    }

    if (pressedButton & B_BUTTON) {
        menuRank_setFrame(menuRank, menuRank->unk_0014, -1, 1.0f);
        sndIndex = SND_INDEX_68;
        _setMode(menuRank->watchMenuRef, MODE_MAIN);
    } else if (direction != 0) {
        menuRank->unk_0010 = menuRank->unk_000C;

        menuRank->unk_000C = WrapI(0, 3, menuRank->unk_000C + direction);
        sndIndex = SND_INDEX_63;
        menuRank_setSlide(menuRank, menuRank->unk_0014, -1, 1.0f, -(direction * 0x140));
        menuRank->unk_0018 = menuRank->unk_0014;

        // TODO: Check if changing `& 1` to `% 2U` makes sense
        menuRank->unk_0014 = (menuRank->unk_0014 + 1) & 1;
        menuRank_setPanel(menuRank, menuRank->unk_0014, menuRank->unk_0004, menuRank->unk_000C);
        menuRank_setNameBaseScale(menuRank, -1, 1.0f);
        menuRank_setSlide(menuRank, menuRank->unk_0014, 1, 0.0f, direction * 0x140);
    }

    SND_PLAY_INDEX(sndIndex);
}

void menuRank_update(MenuRank *menuRank) {
    SMenuItem *rootItem = _getRootItem(menuRank->watchMenuRef);
    s32 i;

    menuItem_update(&menuRank->unk_017C, rootItem);
    menuItem_updateN(&menuRank->unk_020C[i], ARRAY_COUNT(menuRank->unk_020C), rootItem);

    menuItem_update(&menuRank->unk_032C, rootItem);

    func_800578C8(&menuRank->unk_03BC, rootItem);
    func_800578C8(&menuRank->unk_0458, &menuRank->unk_032C);
    func_800578C8(&menuRank->unk_04F4, &menuRank->unk_032C);

    for (i = 0; i < 2; i++) {
        s32 index;

        switch (i) {
            case 0:
                index = menuRank->unk_0018;
                break;

            case 1:
                index = menuRank->unk_0014;
                break;
        }

        if (index >= 0) {
            MenuRank_unk_590 *temp_s2 = &menuRank->unk_590[index];
            s32 j;

            func_80057BE8(&temp_s2->unk_0004, &menuRank->unk_017C);

            for (j = 0; j < temp_s2->unk_0000; j++) {
                menuRankPanel_update(&temp_s2->unk_3A8[j], &menuRank->unk_017C);
            }
        }
    }
}

// unused
const s32 RO_800B1430[] = {
    1,
    -1,
};

const s32 _dir_10660[] = {
    -1,
    1,
};

void menuRank_draw(MenuRank *menuRank, Gfx **gfxP) {
    void *sp18[16];
    Gfx *gfx = *gfxP;
    s32 i;
    s32 j;

    gSPDisplayList(gfx++, fade_normal_texture_init_dl);

    if (menuRank->unk_0008 == 0) {
        menuItem_drawTex(&menuRank->unk_032C, &gfx, _getTexRank(menuRank->watchMenuRef, 3), 0);
        sp18[0] = &menuRank->unk_0458;
        sp18[1] = &menuRank->unk_04F4;

        if (menuRank->unk_032C.scaleStep < 0.0f) {
            menuRank->unk_04F4.id = menuRank->unk_0010;
        } else {
            menuRank->unk_04F4.id = menuRank->unk_000C;
        }

        switch (menuRank->unk_0004) {
            case MODE_RECORD_LS:
                menuRank->unk_0458.id = 1;
                menuRank->unk_04F4.id = menuRank->unk_04F4.id + 3;
                break;

            default:
                menuRank->unk_0458.id = 0;
                break;
        }

        menuRankLabel_draw((void *)sp18, 2, &gfx);

        for (i = 0; i < ARRAY_COUNTU(menuRank->unk_020C); i++) {
            SMenuItem *temp_s0 = &menuRank->unk_020C[i];
            f32 temp_fs0 = temp_s0->trans[0];
            f32 temp_fs1 = temp_s0->trans[1];
            s32 var_v0 = (temp_s0->scaleStep < 0.0f) ? menuRank->unk_0010 : menuRank->unk_000C;

            j = WrapI(0, 3, var_v0 + _dir_10660[i]);
            if (menuRank->unk_0004 == MODE_RECORD_LS) {
                j += 3;
            }

            menuItem_drawItem(temp_s0, &gfx, _getTexRank(menuRank->watchMenuRef, 4), 0, 2, i);
            temp_s0->trans[0] += 12.0f;
            temp_s0->trans[1] += 2.0f;

            menuItem_drawItem(&menuRank->unk_020C[i], &gfx, _getTexRank(menuRank->watchMenuRef, 2), 0, 6, j);
            temp_s0->trans[0] = temp_fs0;
            temp_s0->trans[1] = temp_fs1;
        }
    }

    sp18[0] = &menuRank->unk_03BC;
    menuRankLabel_draw((void *)sp18, 1, &gfx);

    for (i = 0; i < 2; i++) {
        s32 var_s5;

        switch (i) {
            case 0:
                var_s5 = menuRank->unk_0018;
                break;
            case 1:
                var_s5 = menuRank->unk_0014;
                break;
        }

        if (var_s5 >= 0) {
            MenuRank_unk_590 *temp_s0_2 = &menuRank->unk_590[var_s5];

            sp18[0] = &temp_s0_2->unk_0004;
            menuRankHeader_draw((void *)&sp18, 1, &gfx);

            for (j = 0; j < temp_s0_2->unk_0000; j++) {
                sp18[j] = &temp_s0_2->unk_3A8[j];
            }

            menuRankPanel_draw((void *)sp18, temp_s0_2->unk_0000, &gfx);
        }
    }

    *gfxP = gfx;
}

void _eep_writingCallback(void *arg) {
    struct_watchMenu *a = arg;
    RecordWritingMessage *recMessage = &a->recMessage;
    s32 x = (0x140 - msgWnd_getWidth(&recMessage->messageWnd)) / 2;
    s32 y = 0xD0 - msgWnd_getHeight(&recMessage->messageWnd);

    RecWritingMsg_setPos(recMessage, x, y);
    RecWritingMsg_start(recMessage);
    setSleepTimer(500);
}

void func_80059A58(void *arg) {
    struct_watchMenu *a = arg;

    EepRom_WriteAll(_eep_writingCallback, a);
    a->unk_111D8--;
}

void func_80059AA4(void *arg) {
    struct_watchMenu *a = arg;

    EepRom_InitFirst(_eep_writingCallback, a);
    a->unk_111D8--;
}

void func_80059AF0(struct_watchMenu *arg0) {
    while ((arg0->unk_111D8 > 0) || !RecWritingMsg_isEnd(&arg0->recMessage)) {
        RecWritingMsg_calc(&arg0->recMessage);
        _waitRetrace(arg0);
    }
}

void _eepWritePlayer(struct_watchMenu *arg0) {
    RecWritingMsg_setStr(&arg0->recMessage, _mesWriting_mainmenu);
    arg0->unk_111D8++;
    BgTasksManager_SendTask(func_80059A58, arg0);
    func_80059AF0(arg0);
}

void _eepErasePlayer(struct_watchMenu *arg0) {
    RecWritingMsg_setStr(&arg0->recMessage, _mesDeleting_mainmenu);
    arg0->unk_111D8++;
    BgTasksManager_SendTask(func_80059A58, arg0);
    func_80059AF0(arg0);
}

void _eepEraseData(struct_watchMenu *arg0) {
    RecWritingMsg_setStr(&arg0->recMessage, _mesDeleting_mainmenu);
    arg0->unk_111D8++;
    BgTasksManager_SendTask(func_80059AA4, arg0);
    func_80059AF0(arg0);
}

void _waitRetrace(struct_watchMenu *watchMenuRef) {
    osRecvMesg(&watchMenuRef->scMQ, NULL, OS_MESG_BLOCK);
}

Mtx **_getMtxPtr(struct_watchMenu *watchMenuRef) {
    return &watchMenuRef->unk_02448[gfx_gtask_no];
}

Vtx **_getVtxPtr(struct_watchMenu *watchMenuRef) {
    return &watchMenuRef->unk_02454[gfx_gtask_no];
}

TiTexData *_getTexChar(struct_watchMenu *watchMenuRef, s32 index) {
    return &watchMenuRef->unk_02478[index];
}

TiTexData *_getTexCommon(struct_watchMenu *watchMenuRef, s32 arg1) {
    return &watchMenuRef->unk_0247C[arg1];
}

TiTexData *func_80059D14(struct_watchMenu *watchMenuRef, s32 arg1) {
    return &watchMenuRef->unk_02480[arg1];
}

TiTexData *_getTexLevel(struct_watchMenu *watchMenuRef, s32 index) {
    return &watchMenuRef->unk_02484[index];
}

TiTexData *_getTexMain(struct_watchMenu *watchMenuRef, s32 index) {
    return &watchMenuRef->unk_02488[index];
}

TiTexData *_getTexName(struct_watchMenu *arg0, s32 arg1) {
    return &arg0->unk_0248C[arg1];
}

TiTexData *_getTexP2(struct_watchMenu *watchMenuRef, s32 index) {
    return &watchMenuRef->unk_02490[index];
}

TiTexData *_getTexP4(struct_watchMenu *watchMenuRef, s32 index) {
    return &watchMenuRef->unk_02494[index];
}

TiTexData *_getTexRank(struct_watchMenu *watchMenuRef, s32 index) {
    return &watchMenuRef->unk_02498[index];
}

TiTexData *_getTexSetup(struct_watchMenu *watchMenuRef, s32 index) {
    return &watchMenuRef->unk_0249C[index];
}

TiTexData *_getTexStory(struct_watchMenu *arg0, s32 arg1) {
    return &arg0->unk_024A0[arg1];
}

TiTexData *_getTexGameAl(struct_watchMenu *arg0, s32 arg1) {
    return &arg0->unk_024A4[arg1];
}

TiTexData *_getTexGameP1(struct_watchMenu *arg0, s32 arg1) {
    return &arg0->unk_024A8[arg1];
}

TiTexData *_getTexCont(struct_watchMenu *watchMenuRef, s32 arg1) {
    return &watchMenuRef->unk_024AC[arg1];
}

TiTexData *_getTexTutol(struct_watchMenu *watchMenuRef, s32 arg1) {
    return &watchMenuRef->unk_024B0[arg1];
}

TiTexData *_getTexKasa(struct_watchMenu *watchMenuRef, s32 index) {
    return &watchMenuRef->unk_024B4[index];
}

SMenuItem *_getRootItem(struct_watchMenu *watchMenuRef) {
    return &watchMenuRef->unk_024B8[0];
}

u32 _getKeyLvl(struct_watchMenu *watchMenuRef UNUSED, s32 arg1) {
    return gControllerHoldButtons[main_joy[arg1]];
}

u32 _getKeyTrg(struct_watchMenu *watchMenuRef UNUSED, s32 arg1) {
    return gControllerPressedButtons[main_joy[arg1]];
}

u32 _getKeyRep(struct_watchMenu *watchMenuRef UNUSED, s32 arg1) {
    return joycur[main_joy[arg1]];
}

MainMenuMode _getMode(struct_watchMenu *watchMenuRef) {
    return watchMenuRef->unk_111CC;
}

MainMenuMode _getModeOld(struct_watchMenu *watchMenuRef) {
    return watchMenuRef->unk_111C8;
}

void _setMode(struct_watchMenu *watchMenuRef, MainMenuMode arg1) {
    watchMenuRef->unk_111D0 = arg1;
}

void _setNextMain(struct_watchMenu *watchMenuRef, enum_main_no arg1) {
    watchMenuRef->unk_111D4 = arg1;
}

void _setTitle(struct_watchMenu *watchMenuRef, MainMenuMode arg1) {
    menuTitle_setTitle(&watchMenuRef->unk_02548, arg1);
}

void _setFadeDir(struct_watchMenu *watchMenuRef, s32 arg1) {
    if (arg1 < 0) {
        if (watchMenuRef->unk_111E0 > 0.0f) {
            watchMenuRef->unk_111E0 = -watchMenuRef->unk_111E0;
        }
    } else {
        if (watchMenuRef->unk_111E0 < 0.0f) {
            watchMenuRef->unk_111E0 = -watchMenuRef->unk_111E0;
        }
    }
}

/**
 * Original name: menuAll_init
 */
void menuAll_init(struct_watchMenu *arg0, UNK_PTR *arg1, NNSched *sc) {
    UNK_PTR sp10 = *arg1;
    UNK_PTR temp_v0;
    s32 i;
    RomOffset(*pairArray)[ROMTABLEPAIR_MAX] = _romDataTbl;

    arg0->sched = sc;
    arg0->unk_02460 = sp10;

    osCreateMesgQueue(&arg0->scMQ, arg0->scMsgBuf, ARRAY_COUNT(arg0->scMsgBuf));
    nnScAddClient(sc, &arg0->scClient, &arg0->scMQ);

    for (i = 0; i < ARRAY_COUNT(arg0->unk_00048); i++) {
        arg0->unk_02448[i] = &arg0->unk_00048[i][0];
        arg0->unk_02454[i] = &arg0->unk_00C48[i][0];
    }

    sp10 = init_menu_bg(sp10, evs_level_21 != 0);

    arg0->unk_02478 = tiLoadTexData(&sp10, pairArray[ROMDATATBL_MENU_CHAR][ROMTABLEPAIR_START],
                                    pairArray[ROMDATATBL_MENU_CHAR][ROMTABLEPAIR_END]);
    arg0->unk_0247C = tiLoadTexData(&sp10, pairArray[ROMDATATBL_MENU_COMMON][ROMTABLEPAIR_START],
                                    pairArray[ROMDATATBL_MENU_COMMON][ROMTABLEPAIR_END]);
    arg0->unk_02484 = tiLoadTexData(&sp10, pairArray[ROMDATATBL_MENU_LEVEL][ROMTABLEPAIR_START],
                                    pairArray[ROMDATATBL_MENU_LEVEL][ROMTABLEPAIR_END]);
    arg0->unk_02488 = tiLoadTexData(&sp10, pairArray[ROMDATATBL_MENU_MAIN][ROMTABLEPAIR_START],
                                    pairArray[ROMDATATBL_MENU_MAIN][ROMTABLEPAIR_END]);
    arg0->unk_0248C = tiLoadTexData(&sp10, pairArray[ROMDATATBL_MENU_NAME][ROMTABLEPAIR_START],
                                    pairArray[ROMDATATBL_MENU_NAME][ROMTABLEPAIR_END]);
    arg0->unk_02490 = tiLoadTexData(&sp10, pairArray[ROMDATATBL_MENU_P2][ROMTABLEPAIR_START],
                                    pairArray[ROMDATATBL_MENU_P2][ROMTABLEPAIR_END]);
    arg0->unk_02494 = tiLoadTexData(&sp10, pairArray[ROMDATATBL_MENU_P4][ROMTABLEPAIR_START],
                                    pairArray[ROMDATATBL_MENU_P4][ROMTABLEPAIR_END]);
    arg0->unk_02498 = tiLoadTexData(&sp10, pairArray[ROMDATATBL_MENU_RANK][ROMTABLEPAIR_START],
                                    pairArray[ROMDATATBL_MENU_RANK][ROMTABLEPAIR_END]);
    arg0->unk_0249C = tiLoadTexData(&sp10, pairArray[ROMDATATBL_MENU_SETUP][ROMTABLEPAIR_START],
                                    pairArray[ROMDATATBL_MENU_SETUP][ROMTABLEPAIR_END]);
    arg0->unk_024A0 = tiLoadTexData(&sp10, pairArray[ROMDATATBL_MENU_STORY][ROMTABLEPAIR_START],
                                    pairArray[ROMDATATBL_MENU_STORY][ROMTABLEPAIR_END]);
    arg0->unk_024A4 = tiLoadTexData(&sp10, pairArray[ROMDATATBL_GAME_AL][ROMTABLEPAIR_START],
                                    pairArray[ROMDATATBL_GAME_AL][ROMTABLEPAIR_END]);
    arg0->unk_024A8 = tiLoadTexData(&sp10, pairArray[ROMDATATBL_GAME_P1][ROMTABLEPAIR_START],
                                    pairArray[ROMDATATBL_GAME_P1][ROMTABLEPAIR_END]);
    arg0->unk_024AC = tiLoadTexData(&sp10, pairArray[ROMDATATBL_MENU_CONT][ROMTABLEPAIR_START],
                                    pairArray[ROMDATATBL_MENU_CONT][ROMTABLEPAIR_END]);
    arg0->unk_024B0 = tiLoadTexData(&sp10, pairArray[ROMDATATBL_TUTORIAL_KASA][ROMTABLEPAIR_START],
                                    pairArray[ROMDATATBL_TUTORIAL_KASA][ROMTABLEPAIR_END]);
    arg0->unk_024B4 = tiLoadTexData(&sp10, pairArray[ROMDATATBL_MENU_KASA][ROMTABLEPAIR_START],
                                    pairArray[ROMDATATBL_MENU_KASA][ROMTABLEPAIR_END]);

    menuItem_init(&arg0->unk_024B8[0], 0, 0);
    menuTitle_init(&arg0->unk_02548, arg0, 0x70, 0x12);

    arg0->unk_111C0 = 0;
    arg0->unk_111C4 = -1;

    arg0->unk_111C8 = arg0->unk_111CC = arg0->unk_111D0 = _menuAll_lastMode;

    arg0->unk_111D4 = MAIN_MENU;

#ifdef NN_SC_PERF
    arg0->unk_cn_pad = 0;
#endif

    arg0->unk_111DC = 1.0f;

    arg0->unk_111D8 = 0;
    arg0->unk_111E4 = 1;
    arg0->unk_111E8 = 1;
    arg0->unk_111EC = 0;

    arg0->unk_111F0 = 0;
    arg0->unk_111F4 = 0x7F;
    arg0->unk_111E0 = -(1.0f / 30.0f);

    RecWritingMsg_init(&arg0->recMessage, &sp10);
    arg0->unk_02464 = 0x60000;

    for (i = 0; i < ARRAY_COUNTU(arg0->unk_02470); i++) {
        temp_v0 = ALIGN_PTR(sp10);
        arg0->unk_02468[i] = arg0->unk_02470[i] = temp_v0;
        sp10 = temp_v0 + arg0->unk_02464;
    }

    for (i = 0; i < ARRAY_COUNT(game_state_data); i++) {
        game_state_data[i].game_score = 0;
        game_state_data[i].game_retry = 0;
    }

    evs_one_game_flg = 0;
    *arg1 = sp10;
}

void func_8005A2AC(struct_watchMenu *arg0) {
    nnScRemoveClient(arg0->sched, &arg0->scClient);
    _menuAll_lastMode = arg0->unk_111CC;
}

void func_8005A2EC(struct_watchMenu *arg0) {
    s32 index = arg0->unk_111C0;

    switch (arg0->unk_111CC) {
        case MODE_MAIN:
            func_8004F2D8(&arg0->unk_02678[index].menuMain);
            break;

        case MODE_STORY:
            func_80051974(&arg0->unk_02678[index].menuStory);
            break;

        case MODE_LVSEL:
        case MODE_LVSEL_TQ:
        case MODE_LVSEL_TA:
            func_80052DF0(&arg0->unk_02678[index].menuLvSel);
            break;

        case MODE_VSCOM:
        case MODE_VSCOM_FL:
        case MODE_VSMAN:
        case MODE_VSMAN_FL:
        case MODE_VSMAN_TA:
        case MODE_PLAY4_LV:
        case MODE_PLAY4_TB_LV:
        case MODE_PLAY4_FL_LV:
            func_800550F4(&arg0->unk_02678[index].menuPlay2);
            break;

        default:
            break;
    }
}

void menuAll_changeMenu(struct_watchMenu *arg0) {
    s32 index = arg0->unk_111C0;

    arg0->unk_02470[index] = arg0->unk_02468[index];
    bzero(arg0->unk_02470[index], arg0->unk_02464);
    arg0->unk_111E4 = 1;
    arg0->unk_111E8 = 1;
    arg0->unk_111EC = 0;
    arg0->unk_111F0 = 0;

    if (arg0->unk_111CC != MODE_MAIN) {
        _setTitle(arg0, arg0->unk_111CC);
    }

    switch (arg0->unk_111CC) {
        case MODE_MAIN:
            menuMain_init(&arg0->unk_02678[index].menuMain, arg0, &arg0->unk_02470[index]);
            break;

        case MODE_STORY:
            menuStory_init(&arg0->unk_02678[index].menuStory, arg0, &arg0->unk_02470[index]);
            break;

        case MODE_LVSEL:
        case MODE_LVSEL_TQ:
        case MODE_LVSEL_TA:
            menuLvSel_init(&arg0->unk_02678[index].menuLvSel, arg0, &arg0->unk_02470[index]);
            break;

        case MODE_VSCOM:
        case MODE_VSCOM_FL:
        case MODE_VSMAN:
        case MODE_VSMAN_FL:
        case MODE_VSMAN_TA:
        case MODE_PLAY4_LV:
        case MODE_PLAY4_TB_LV:
        case MODE_PLAY4_FL_LV:
            menuPlay2_init(&arg0->unk_02678[index].menuPlay2, arg0, &arg0->unk_02470[index]);
            break;

        case MODE_VSCOM_CH:
        case MODE_VSCOM_FL_CH:
        case MODE_VSMAN_CH:
        case MODE_VSMAN_FL_CH:
        case MODE_VSMAN_TA_CH:
        case MODE_PLAY4_CH:
        case MODE_PLAY4_TB_CH:
        case MODE_PLAY4_FL_CH:
            menuChSel_init(&arg0->unk_02678[index].menuChSel, arg0, &arg0->unk_02470[index]);
            break;

        case MODE_STORY_NE:
        case MODE_LVSEL_NE:
        case MODE_LVSEL_TQ_NE:
        case MODE_LVSEL_TA_NE:
        case MODE_VSCOM_NE:
        case MODE_VSCOM_FL_NE:
        case MODE_VSMAN_NE:
        case MODE_VSMAN_FL_NE:
        case MODE_VSMAN_TA_NE:
        case MODE_NAME_NE:
        case MODE_NAME_NE2:
            menuNmEnt_init(&arg0->unk_02678[index].menuNmEnt, arg0, &arg0->unk_02470[index]);
            break;

        case MODE_RECORD_ST:
        case MODE_RECORD_LS:
        case MODE_RECORD_LS_TQ:
        case MODE_RECORD_LS_TA:
        case MODE_RECORD_VC:
        case MODE_RECORD_VC_FL:
        case MODE_RECORD_VM:
        case MODE_RECORD_VM_FL:
        case MODE_RECORD_VM_TA:
            menuRank_init(&arg0->unk_02678[index].menuRank, arg0, &arg0->unk_02470[index]);
            break;

        default:
            break;
    }
}

void menuAll_input(struct_watchMenu *arg0) {
    s32 index = arg0->unk_111C0;

    if ((arg0->unk_111E0 > 0.0f) && (arg0->unk_111DC > 0.0f)) {
        func_8005A2EC(arg0);
        return;
    }

    switch (arg0->unk_111CC) {
        case MODE_MAIN:
            menuMain_input(&arg0->unk_02678[index].menuMain);
            break;

        case MODE_STORY:
            menuStory_input(&arg0->unk_02678[index].menuStory);
            break;

        case MODE_LVSEL:
        case MODE_LVSEL_TQ:
        case MODE_LVSEL_TA:
            menuLvSel_input(&arg0->unk_02678[index].menuLvSel);
            break;

        case MODE_VSCOM:
        case MODE_VSCOM_FL:
        case MODE_VSMAN:
        case MODE_VSMAN_FL:
        case MODE_VSMAN_TA:
        case MODE_PLAY4_LV:
        case MODE_PLAY4_TB_LV:
        case MODE_PLAY4_FL_LV:
            menuPlay2_input(&arg0->unk_02678[index].menuPlay2);
            break;

        case MODE_VSCOM_CH:
        case MODE_VSCOM_FL_CH:
        case MODE_VSMAN_CH:
        case MODE_VSMAN_FL_CH:
        case MODE_VSMAN_TA_CH:
        case MODE_PLAY4_CH:
        case MODE_PLAY4_TB_CH:
        case MODE_PLAY4_FL_CH:
            menuChSel_input(&arg0->unk_02678[index].menuChSel);
            break;

        case MODE_STORY_NE:
        case MODE_LVSEL_NE:
        case MODE_LVSEL_TQ_NE:
        case MODE_LVSEL_TA_NE:
        case MODE_VSCOM_NE:
        case MODE_VSCOM_FL_NE:
        case MODE_VSMAN_NE:
        case MODE_VSMAN_FL_NE:
        case MODE_VSMAN_TA_NE:
        case MODE_NAME_NE:
        case MODE_NAME_NE2:
            menuNmEnt_input(&arg0->unk_02678[index].menuNmEnt);
            break;

        case MODE_RECORD_ST:
        case MODE_RECORD_LS:
        case MODE_RECORD_LS_TQ:
        case MODE_RECORD_LS_TA:
        case MODE_RECORD_VC:
        case MODE_RECORD_VC_FL:
        case MODE_RECORD_VM:
        case MODE_RECORD_VM_FL:
        case MODE_RECORD_VM_TA:
            menuRank_input(&arg0->unk_02678[index].menuRank);
            break;

        default:
            break;
    }
}

void menuAll_update(struct_watchMenu *arg0) {
#ifdef NN_SC_PERF
    s32 pad[2] UNUSED;
#endif
    SMenuItem *var_v1 = &arg0->unk_024B8[0];
    MainMenuMode var_a0;
    f32 temp_f2_2;
    s32 i;
    s32 var_v1_2;

    arg0->unk_111DC = CLAMP(arg0->unk_111DC + arg0->unk_111E0, 0.0f, 1.0f);

    temp_f2_2 = (arg0->unk_111DC - DOUBLE_LITERAL(0.5)) * DOUBLE_LITERAL(1.2) + DOUBLE_LITERAL(0.5);
    temp_f2_2 = DOUBLE_LITERAL(1) - CLAMP(temp_f2_2, 0.0f, 1.0f);

    for (i = 0; i < 3; i++) {
        var_v1->colorRange[1][i] = temp_f2_2;
        var_v1->colorRange[0][i] = temp_f2_2;
    }

#ifdef NN_SC_PERF
    if (_getKeyTrg(arg0, 0) & Z_TRIG) {
        arg0->unk_cn_pad = arg0->unk_cn_pad == 0;
    }
#endif

    menuItem_updateN(arg0->unk_024B8, ARRAY_COUNT(arg0->unk_024B8), NULL);
    menuTitle_update(&arg0->unk_02548, &arg0->unk_024B8[0]);

    for (i = 0; i < 2; i++) {
        if (i != 0) {
            var_v1_2 = arg0->unk_111C0;
        } else {
            var_v1_2 = arg0->unk_111C4;
        }
        if (var_v1_2 < 0) {
            continue;
        }

        if (i != 0) {
            var_a0 = arg0->unk_111CC;
        } else {
            var_a0 = arg0->unk_111C8;
        }

        switch (var_a0) {
            case MODE_MAIN:
                menuMain_update(&arg0->unk_02678[var_v1_2].menuMain);
                break;

            case MODE_STORY:
                menuStory_update(&arg0->unk_02678[var_v1_2].menuStory);
                break;

            case MODE_LVSEL:
            case MODE_LVSEL_TQ:
            case MODE_LVSEL_TA:
                menuLvSel_update(&arg0->unk_02678[var_v1_2].menuLvSel);
                break;

            case MODE_VSCOM:
            case MODE_VSCOM_FL:
            case MODE_VSMAN:
            case MODE_VSMAN_FL:
            case MODE_VSMAN_TA:
            case MODE_PLAY4_LV:
            case MODE_PLAY4_TB_LV:
            case MODE_PLAY4_FL_LV:
                menuPlay2_update(&arg0->unk_02678[var_v1_2].menuPlay2);
                break;

            case MODE_VSCOM_CH:
            case MODE_VSCOM_FL_CH:
            case MODE_VSMAN_CH:
            case MODE_VSMAN_FL_CH:
            case MODE_VSMAN_TA_CH:
            case MODE_PLAY4_CH:
            case MODE_PLAY4_TB_CH:
            case MODE_PLAY4_FL_CH:
                menuChSel_update(&arg0->unk_02678[var_v1_2].menuChSel);
                break;

            case MODE_STORY_NE:
            case MODE_LVSEL_NE:
            case MODE_LVSEL_TQ_NE:
            case MODE_LVSEL_TA_NE:
            case MODE_VSCOM_NE:
            case MODE_VSCOM_FL_NE:
            case MODE_VSMAN_NE:
            case MODE_VSMAN_FL_NE:
            case MODE_VSMAN_TA_NE:
            case MODE_NAME_NE:
            case MODE_NAME_NE2:
                menuNmEnt_update(&arg0->unk_02678[var_v1_2].menuNmEnt);
                break;

            case MODE_RECORD_ST:
            case MODE_RECORD_LS:
            case MODE_RECORD_LS_TQ:
            case MODE_RECORD_LS_TA:
            case MODE_RECORD_VC:
            case MODE_RECORD_VC_FL:
            case MODE_RECORD_VM:
            case MODE_RECORD_VM_FL:
            case MODE_RECORD_VM_TA:
                menuRank_update(&arg0->unk_02678[var_v1_2].menuRank);
                break;

            default:
                break;
        }
    }

    arg0->unk_111E4 = 0;
    arg0->unk_111EC++;
}

void menuAll_drawBg(struct_watchMenu *arg0, Gfx **gfxP) {
    Gfx *gfx = *gfxP;
    SMenuItem *temp_s4 = &arg0->unk_024B8[0];
    TiTexData *temp_s3;
    s32 i;
    bool cached;

    menuItem_setPrim(temp_s4, &gfx);
    draw_menu_bg(&gfx, temp_s4->trans[0] + 0.0f, -temp_s4->trans[1] - 120.0f);

    gSPDisplayList(gfx++, fade_normal_texture_init_dl);
    menuItem_setPrim(temp_s4, &gfx);

    cached = false;
    temp_s3 = _getTexCommon(arg0, 2);
    for (i = 0; i < 5; i++) {
        cached += menuItem_drawTex2(temp_s4, &gfx, temp_s3, cached, i << 6, 0, 1.0f, 1.0f);
    }

    for (; i < 10; i++) {
        cached += menuItem_drawTex2(temp_s4, &gfx, temp_s3, cached, (i - 5) << 6, 200.0f, 1.0f, -1.0f);
    }

    *gfxP = gfx;
}

void menuAll_draw(struct_watchMenu *arg0, Gfx **gfxP) {
    s32 color;
    s32 i;

    arg0->unk_02448[gfx_gtask_no] = &arg0->unk_00048[gfx_gtask_no][0];
    arg0->unk_02454[gfx_gtask_no] = &arg0->unk_00C48[gfx_gtask_no][0];

    color =
        (((arg0->unk_111DC - DOUBLE_LITERAL(0.5)) * DOUBLE_LITERAL(1.2)) + DOUBLE_LITERAL(0.5)) * DOUBLE_LITERAL(255);
    color = CLAMP(color, 0, 255);

    gDPSetEnvColor(gGfxHead++, color, color, color, 255);

    menuAll_drawBg(arg0, gfxP);
    menuTitle_draw(&arg0->unk_02548, &gGfxHead);

    for (i = 0; i < 2; i++) {
        MainMenuMode var_a0;
        s32 index;

        if (i != 0) {
            index = arg0->unk_111C0;
        } else {
            index = arg0->unk_111C4;
        }
        if (index < 0) {
            continue;
        }

        if (i != 0) {
            var_a0 = arg0->unk_111CC;
        } else {
            var_a0 = arg0->unk_111C8;
        }

        gDPSetEnvColor(gGfxHead++, color, color, color, 255);

        switch (var_a0) {
            case MODE_MAIN:
                menuMain_draw(&arg0->unk_02678[index].menuMain, gfxP);
                break;

            case MODE_STORY:
                menuStory_draw(&arg0->unk_02678[index].menuStory, gfxP);
                break;

            case MODE_LVSEL:
            case MODE_LVSEL_TQ:
            case MODE_LVSEL_TA:
                menuLvSel_draw(&arg0->unk_02678[index].menuLvSel, gfxP);
                break;

            case MODE_VSCOM:
            case MODE_VSCOM_FL:
            case MODE_VSMAN:
            case MODE_VSMAN_FL:
            case MODE_VSMAN_TA:
            case MODE_PLAY4_LV:
            case MODE_PLAY4_TB_LV:
            case MODE_PLAY4_FL_LV:
                menuPlay2_draw(&arg0->unk_02678[index].menuPlay2, gfxP);
                break;

            case MODE_VSCOM_CH:
            case MODE_VSCOM_FL_CH:
            case MODE_VSMAN_CH:
            case MODE_VSMAN_FL_CH:
            case MODE_VSMAN_TA_CH:
            case MODE_PLAY4_CH:
            case MODE_PLAY4_TB_CH:
            case MODE_PLAY4_FL_CH:
                menuChSel_draw(&arg0->unk_02678[index].menuChSel, gfxP);
                break;

            case MODE_STORY_NE:
            case MODE_LVSEL_NE:
            case MODE_LVSEL_TQ_NE:
            case MODE_LVSEL_TA_NE:
            case MODE_VSCOM_NE:
            case MODE_VSCOM_FL_NE:
            case MODE_VSMAN_NE:
            case MODE_VSMAN_FL_NE:
            case MODE_VSMAN_TA_NE:
            case MODE_NAME_NE:
            case MODE_NAME_NE2:
                menuNmEnt_draw(&arg0->unk_02678[index].menuNmEnt, gfxP);
                break;

            case MODE_RECORD_ST:
            case MODE_RECORD_LS:
            case MODE_RECORD_LS_TQ:
            case MODE_RECORD_LS_TA:
            case MODE_RECORD_VC:
            case MODE_RECORD_VC_FL:
            case MODE_RECORD_VM:
            case MODE_RECORD_VM_FL:
            case MODE_RECORD_VM_TA:
                menuRank_draw(&arg0->unk_02678[index].menuRank, gfxP);
                break;

            default:
                break;
        }
    }

    RecWritingMsg_draw(&arg0->recMessage, &gGfxHead);

    arg0->unk_111E8 = 0;
    arg0->unk_111F0++;
}

/**
 * Original name: main_menu
 */
enum_main_no main_menu(NNSched *sc) {
    UNK_PTR sp10 = Heap_bufferp;
    struct_watchMenu *ptr = ALIGN_PTR(Heap_bufferp);
    s32 i;

    if (main_old == MAIN_TITLE) {
        _menuAll_lastMode = MODE_MAIN;
        _menuMain_lastMode = MODE_MAIN;
        _menuMain_lastDepth = 0;
        _menuMain_lastSelect[0] = 0;
    }

    BgTasksManager_Init();
    sp10 = &ptr[1];
    bzero(ptr, sizeof(struct_watchMenu));
    watchMenu = ptr;
    menuAll_init(ptr, &sp10, sc);

    evs_playmax = joyResponseCheck();

    for (i = 0; i < ARRAY_COUNT(joyflg); i++) {
        joyflg[i] = U_JPAD | L_JPAD | R_JPAD | D_JPAD | L_TRIG | R_TRIG;
    }

    joycur1 = 0x18;
    joycur2 = 6;
    gGfxHead = gGfxGlist[gfx_gtask_no];
    dm_seq_play(SEQ_INDEX_12);

    while ((ptr->unk_111D4 == MAIN_MENU) || (ptr->unk_111DC < 1.0f)) {
        if (graphic_no == GRAPHIC_NO_0) {
            while ((pendingGFX != 0) || (BgTasksManager_GetRemainingTasks() != 0)) {
                _waitRetrace(ptr);
            }

            menuAll_changeMenu(ptr);
        }

        if (ptr->unk_111D8 > 0) {
            for (i = 0; i < MAXCONTROLLERS; i++) {
                joycur[i] = 0;
                gControllerPressedButtons[i] = 0;
                gControllerPrevHoldButtons[i] = 0;
                gControllerHoldButtons[i] = 0;
            }
        } else {
            joyProcCore();

#ifdef NN_SC_PERF
            while (D_80092F10_cn) {
                _waitRetrace(ptr);
                joyProcCore();
                graphic_no = GRAPHIC_NO_0;
                dm_audio_update();
            }
#endif
        }

        _waitRetrace(ptr);

#ifdef NN_SC_PERF
        func_8002BC30_cn(ENUM_8002BA98_CN_ARG0_1);
#endif

        menuAll_input(ptr);
        menuAll_update(ptr);
        dm_audio_update();

        if (ptr->unk_111CC != ptr->unk_111D0) {
            ptr->unk_111C8 = ptr->unk_111CC;
            ptr->unk_111CC = ptr->unk_111D0;
            ptr->unk_111C4 = ptr->unk_111C0;
            ptr->unk_111C0 ^= 1;
            graphic_no = GRAPHIC_NO_0;
        } else {
            graphic_no = GRAPHIC_NO_5;
        }

#ifdef NN_SC_PERF
        func_8002BD04_cn();
#endif
    }

    graphic_no = GRAPHIC_NO_5;

    while (ptr->unk_111F4 != 0xF) {
        osRecvMesg(&ptr->scMQ, NULL, OS_MESG_BLOCK);
        dm_audio_update();
    }

    graphic_no = GRAPHIC_NO_0;
    dm_seq_stop();

    while ((pendingGFX != 0) || !dm_seq_is_stopped() || (BgTasksManager_GetRemainingTasks() != 0)) {
        osRecvMesg(&ptr->scMQ, NULL, OS_MESG_BLOCK);
        dm_audio_update();
    }

    func_8005A2AC(ptr);
    BgTasksManager_Destroy();

    return ptr->unk_111D4;
}

void graphic_menu(void) {
    struct_watchMenu *ptr = watchMenu;

    if ((ptr->unk_111D4 != MAIN_MENU) && (ptr->unk_111DC == 1.0f)) {
        osSetThreadPri(NULL, THREAD_PRI_GRAPHIC);
        ptr->unk_111F4 = 0xF;
        return;
    }

    if (gGfxHead != gGfxGlist[gfx_gtask_no]) {
        gDPFullSync(gGfxHead++);
        gSPEndDisplayList(gGfxHead++);

        osWritebackDCacheAll();
        gfxTaskStart(&B_800FAE80[gfx_gtask_no], gGfxGlist[gfx_gtask_no],
                     (gGfxHead - gGfxGlist[gfx_gtask_no]) * sizeof(Gfx), 0, OS_SC_SWAPBUFFER);
        gGfxHead = gGfxGlist[gfx_gtask_no];
    }

    osSetThreadPri(NULL, THREAD_PRI_GRAPHIC);
    F3RCPinitRtn();
    F3ClearFZRtn(0);
    menuAll_draw(ptr, &gGfxHead);

#ifdef NN_SC_PERF
    if (ptr->unk_cn_pad != 0) {
        func_8002BD7C_cn(&gGfxHead, 0x20, 0xB4);
    }
#endif

    osSetThreadPri(NULL, OS_PRIORITY_APPMAX);
}

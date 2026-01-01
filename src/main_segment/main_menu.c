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
void menuMes_init(MenuMes *mes, struct_watchMenu *global, void **heapP, s32 col, s32 row, s32 x, s32 y) {
    MessageWnd *msgWnd;
    SMenuItem *item;
    void *heap = *heapP;
    f32 a2;

    mes->global = global;

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
    menuCursor_init(&mes->window, global, CURSOR_WINDOW, 0, -0x10, -0x10, mes->msgWnd.colStep * col * 2 + 0x20,
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

        tiStretchTexTile(&gfx, texC, cached, 0, 0, texC->info[TI_INFO_IDX_WIDTH], 0x14, item->trans[0], item->trans[1],
                         item->scale[0] * texC->info[TI_INFO_IDX_WIDTH], item->scale[1] * 20.0f);
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

/**
 * Original name: _color_2791
 */
const f32 _color_2791[] = {
    1.0f,
    0.0f,
    0.0f,
};

/**
 * Original name: menuCont_setFade
 */
void menuCont_setFade(MenuCont *cont, s32 dir, f32 time) {
    SMenuItem *list[ARRAY_COUNTU(cont->miDesc) + ARRAY_COUNTU(cont->miLine) + ARRAY_COUNTU(cont->miLabel) +
                    ARRAY_COUNTU(cont->miPushAnyKey)];
    s32 i;
    s32 j = 0;

    for (i = 0; i < ARRAY_COUNTU(cont->miDesc); i++) {
        list[j] = &cont->miDesc[i];
        j++;
    }

    for (i = 0; i < ARRAY_COUNTU(cont->miLine); i++) {
        list[j] = &cont->miLine[i];
        j++;
    }

    for (i = 0; i < ARRAY_COUNTU(cont->miLabel); i++) {
        list[j] = &cont->miLabel[i];
        j++;
    }

    for (i = 0; i < ARRAY_COUNTU(cont->miPushAnyKey); i++) {
        list[j] = &cont->miPushAnyKey[i];
        j++;
    }

    for (i = 0; i < j; i++) {
        SMenuItem *item = list[i];

        menuItem_setColor_fade(item);
        item->colorStep = 0.05f;
        item->colorTime = time;
        menuItem_setColorDir(item, dir);
    }

    for (i = 0; i < ARRAY_COUNTU(cont->miLine); i++) {
        SMenuItem *item = &cont->miLine[i];

        for (j = 0; j < ARRAY_COUNT(_color_2791); j++) {
            item->colorRange[0][j] = item->colorRange[1][j] = _color_2791[j];
        }
    }
}

void menuCont_setFrame(MenuCont *cont, s32 dir, s32 time) {
    SMenuItem *item = &cont->miBase;

    item->transTime = time;
    item->transStep = 0.05f;
    item->transRange[0][0] = item->transRange[1][0] - 160.0f;
    menuItem_setTransDir(item, dir);
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
void menuCont_init(MenuCont *cont, struct_watchMenu *global, s32 x, s32 y) {
    s32 i;

    cont->global = global;

    menuItem_init(&cont->miBase, x, y);

    for (i = 0; i < ARRAY_COUNTU(cont->miDesc); i++) {
        menuItem_init(&cont->miDesc[i], _posDesc_2860[i][0], _posDesc_2860[i][1]);
        menuItem_setColor_fade(&cont->miDesc[i]);
    }

    for (i = 0; i < ARRAY_COUNTU(cont->miLine); i++) {
        menuItem_init(&cont->miLine[i], _posLine_2861[i][0], _posLine_2861[i][1]);
        menuItem_setColor_fade(&cont->miLine[i]);
    }

    menuItem_init(&cont->miLabel[0], 14, 47);
    menuItem_init(&cont->miPushAnyKey[0], 214, 212);
    menuCont_setFade(cont, -1, 0.0f);
    menuCont_setFrame(cont, -1, 0);
}

/**
 * Original name: menuCont_input
 */
bool menuCont_input(MenuCont *cont, s32 playerNo UNUSED) {
    SMenuItem *item = &cont->miBase;

    return ((item->transStep > 0.0f) && (item->transTime == 1.0f));
}

/**
 * Original name: menuCont_update
 */
void menuCont_update(MenuCont *cont, SMenuItem *parent) {
    menuItem_update(&cont->miBase, parent);
    menuItem_updateN(cont->miDesc, ARRAY_COUNT(cont->miDesc), &cont->miBase);
    menuItem_updateN(cont->miLine, ARRAY_COUNT(cont->miLine), &cont->miBase);
    menuItem_update(cont->miLabel, parent);
    menuItem_update(cont->miPushAnyKey, parent);
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
    TiTexData *texC;
    TiTexData *texA;
    s32 i;

    gSPDisplayList(gfx++, fade_normal_texture_init_dl);

    item = &cont->miBase;
    texC = _getTexTutol(cont->global, 7);
    menuItem_drawTex(item, &gfx, texC, 0);

    gSPDisplayList(gfx++, fade_intensity_texture_init_dl);

    for (i = 0; i < ARRAY_COUNTU(cont->miLine); i++) {
        item = &cont->miLine[i];
        texC = _getTexCont(cont->global, _line_2914[i]);
        menuItem_drawTex(item, &gfx, texC, 0);
    }

    gSPDisplayList(gfx++, fade_normal_texture_init_dl);
    gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);

    texC = _getTexCont(cont->global, 2);
    for (i = 0; i < ARRAY_COUNTU(cont->miDesc) - 1; i++) {
        item = &cont->miDesc[i];
        menuItem_drawItem(item, &gfx, texC, 0, 4, i);
    }

    for (; i < ARRAY_COUNTU(cont->miDesc); i++) {
        item = &cont->miDesc[i];

        //! @bug: OoB access: See note in _desc_2915 for more info
        texC = _getTexCont(cont->global, _desc_2915[i - (ARRAY_COUNTU(cont->miDesc) - 2)]);

        menuItem_drawTex(item, &gfx, texC, 0);
    }

    menuItem_drawItem(cont->miLabel, &gfx, _getTexCommon(cont->global, 0xE), 0, 47, 19);

    gSPDisplayList(gfx++, fade_alpha_texture_init_dl);

    texC = _getTexTutol(cont->global, 1);
    texA = _getTexTutol(cont->global, 3);
    menuItem_drawAlphaTex(cont->miPushAnyKey, &gfx, texC, texA, 0);

    *gfxP = gfx;
}

/**
 * Original name: menuMainPanel_setFrame
 */
void menuMainPanel_setFrame(MenuMainPanel *mainPanel, s32 dir, f32 time) {
    SMenuItem *item = &mainPanel->miBase;

    item->transTime = time;
    item->transStep = 0.05f;
    item->transRange[0][0] = item->transRange[1][0] - SCREEN_WIDTH;
    menuItem_setTransDir(item, dir);
}

/**
 * Original name: menuMainPanel_init
 */
void menuMainPanel_init(MenuMainPanel *mainPanel, struct_watchMenu *global, s32 count, s32 select, const s32 *indexes,
                        s32 x, s32 y) {
    s32 i;

    mainPanel->global = global;
    mainPanel->count = count;
    mainPanel->select = WrapI(0, count, select);

    for (i = 0; i < ARRAY_COUNTU(mainPanel->indexes); i++) {
        //! @bug OoB read. End condition should be count
        mainPanel->indexes[i] = indexes[i];
    }

    menuItem_init(&mainPanel->miBase, x, y);
    for (i = 0; i < count; i++) {
        menuItem_init(&mainPanel->miPanel[i], 11, 9 + i * 23);
    }

    menuCursor_init(&mainPanel->cursor, global, CURSOR_ITEM, 0, 0, 0, 106, 20);
    mainPanel->cursor.flags.finger = true;
}

/**
 * Original name: menuMainPanel_input
 */
bool menuMainPanel_input(MenuMainPanel *mainPanel, s32 playerNo) {
    u32 rep = _getKeyRep(mainPanel->global, playerNo);
    s32 vec = 0;
    s32 select;

    if ((mainPanel->miBase.transStep < 0.0f) || (mainPanel->miBase.transTime < 1.0f)) {
        return false;
    }
    if (rep & U_JPAD) {
        vec--;
    }
    if (rep & D_JPAD) {
        vec++;
    }

#if VERSION_US
    select = WrapI(0, mainPanel->count, mainPanel->select + vec);
#elif VERSION_GW
    select = mainPanel->select;
    do {
        select = WrapI(0, mainPanel->count, select + vec);
    } while ((vec != 0) && (mainPanel->miPanel[select].colorTime == 0.0f));
#elif VERSION_CN
    select = mainPanel->select;
    select = WrapI(0, mainPanel->count, select + vec);
#else
#error ""
#endif

    if (select != mainPanel->select) {
        dm_snd_play(SND_INDEX_64);
        mainPanel->select = select;
    }
    return true;
}

/**
 * Original name: menuMainPanel_update
 */
void menuMainPanel_update(MenuMainPanel *mainPanel, SMenuItem *parent) {
    menuItem_update(&mainPanel->miBase, parent);
    menuItem_updateN(mainPanel->miPanel, mainPanel->count, &mainPanel->miBase);
    menuCursor_update(&mainPanel->cursor, &mainPanel->miPanel[mainPanel->select]);
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
void menuMainPanel_draw(MenuMainPanel *mainPanel, Gfx **gfxP) {
    Gfx *gfx = *gfxP;
    MenuCursor *list[1];
    TiTexData *texC;
    s32 i;

    gSPDisplayList(gfx++, fade_normal_texture_init_dl);

    texC = _getTexMain(mainPanel->global, _panel_3220[mainPanel->count - 2]);
    menuItem_drawTex(&mainPanel->miBase, &gfx, texC, 0);

    texC = _getTexCommon(mainPanel->global, 0xE);
    for (i = 0; i < mainPanel->count; i++) {
        menuItem_drawItem(&mainPanel->miPanel[i], &gfx, texC, 0, 0x2F, mainPanel->indexes[i]);
    }

    list[0] = &mainPanel->cursor;
    menuCursor_draw(list, ARRAY_COUNT(list), &gfx);

    *gfxP = gfx;
}

/**
 * Original name: menuNameSelPanel_setFrame
 */
void menuNameSelPanel_setFrame(MenuNameSelPanel *nameSelPanel, s32 dir, f32 time) {
    SMenuItem *item = &nameSelPanel->miBase;

    item->transTime = time;
    item->transStep = 0.05f;
    item->transRange[0][0] = item->transRange[1][0] - 320.0f;
    menuItem_setTransDir(item, dir);
}

/**
 * Original name: menuNameSelPanel_clear
 */
void menuNameSelPanel_clear(MenuNameSelPanel *nameSelPanel, bool guestFlag, s32 playerCount) {
    s32 i;

    nameSelPanel->playerCount = playerCount;
    nameSelPanel->flow = 0;

    if (evs_select_name_no[0] == evs_select_name_no[1]) {
        evs_select_name_no[1] = 8;
    }

    for (i = 0; i < EVS_SELECT_NAME_NO_COUNT; i++) {
        nameSelPanel->depth[i] = 0;
        nameSelPanel->select[i] = evs_select_name_no[i];
        nameSelPanel->column[i] = (evs_select_name_no[i] & 1);
    }

    nameSelPanel->flags.guest = (guestFlag != false);

    for (i = 0; i < ARRAY_COUNTU(nameSelPanel->cursor); i++) {
        nameSelPanel->cursor[i].flags.finger = true;
        nameSelPanel->cursor[i].flags.player = (nameSelPanel->playerCount >= 2);
    }
}

/**
 * Original name: menuNameSelPanel_init
 */
void menuNameSelPanel_init(MenuNameSelPanel *nameSelPanel, struct_watchMenu *global, bool guestFlag, s32 playerCount,
                           s32 x, s32 y) {
    s32 i;

    nameSelPanel->global = global;
    menuItem_init(&nameSelPanel->miBase, x, y);

    for (i = 0; i < ARRAY_COUNTU(nameSelPanel->miLabel) - 1; i++) {
        menuItem_init(&nameSelPanel->miLabel[i], (i % 2) * 60 + 6, (i / 2) * 23 + 31);
    }
    menuItem_init(&nameSelPanel->miLabel[i], 0x24, 8);

    for (i = 0; i < ARRAY_COUNTU(nameSelPanel->cursor); i++) {
        menuCursor_init(&nameSelPanel->cursor[i], global, CURSOR_ITEM, i, 0, 0, 56, 20);

        if (i % 2U != 0) {
            SMenuItem *item;

            item = &nameSelPanel->cursor[i].miCursor;
            item->colorTime = WrapF(0.0f, 1.0f, item->colorTime + DOUBLE_LITERAL(0.5));

            item = &nameSelPanel->cursor[i].miFinger;
            item->transTime = WrapF(0.0f, 1.0f, item->transTime + DOUBLE_LITERAL(0.5));
            item->transRange[0][0] += nameSelPanel->cursor[i].size[0] + 0x10;
            item->transRange[1][0] += nameSelPanel->cursor[i].size[0] + 0x10;
            item->scaleRange[0][0] = -item->scaleRange[0][0];
            item->scaleRange[1][0] = -item->scaleRange[1][0];

            item = &nameSelPanel->cursor[i].miPlayer;
            item->transTime = WrapF(0.0f, 1.0f, item->transTime + DOUBLE_LITERAL(0.5));
            item->transRange[0][0] += nameSelPanel->cursor[i].size[0] + 0x10;
            item->transRange[1][0] += nameSelPanel->cursor[i].size[0] + 0x10;
        }
    }

    menuNameSelPanel_clear(nameSelPanel, guestFlag, playerCount);
}

/**
 * Original name: menuNameSelPanel_checkSelected
 */
bool menuNameSelPanel_checkSelected(MenuNameSelPanel *nameSelPanel, s32 playerNo, s32 nameNo) {
    if (nameNo != 8) {
        s32 i;

        for (i = 0; i < nameSelPanel->playerCount; i++) {
            if (i == playerNo) {
                continue;
            }
            if (nameSelPanel->select[i] == 8) {
                continue;
            }

            if (nameSelPanel->select[i] == nameNo) {
                return true;
            }
        }
    }

    return false;
}

/**
 * Original name: menuNameSelPanel_input1
 */
void menuNameSelPanel_input1(MenuNameSelPanel *nameSelPanel, s32 playerNo) {
    u32 rep = _getKeyRep(nameSelPanel->global, playerNo);
    u32 trg = _getKeyTrg(nameSelPanel->global, playerNo);
    s32 vec;
    SndIndex sound = SND_INDEX_INVALID;
    s32 select = nameSelPanel->select[playerNo];

    if (menuNameSelPanel_checkSelected(nameSelPanel, playerNo, select)) {
        nameSelPanel->select[playerNo] = 8;
        select = 8;
    }

    if (nameSelPanel->depth[playerNo] == 0) {
        if (select == 8) {
            vec = 0;
            if ((rep & L_JPAD)) {
                vec--;
            }
            if ((rep & R_JPAD)) {
                vec++;
            }

            nameSelPanel->column[playerNo] = WrapI(0, 2, nameSelPanel->column[playerNo] + vec);

            vec = 0;
            if (rep & U_JPAD) {
                vec--;
            }
            if (rep & D_JPAD) {
                vec++;
            }

            if (vec > 0) {
                select = nameSelPanel->column[playerNo];

                while ((select < 8) && menuNameSelPanel_checkSelected(nameSelPanel, playerNo, select)) {
                    select += 2;
                }
            } else if (vec < 0) {
                select = nameSelPanel->column[playerNo] + 6;
                while ((select > 0) && menuNameSelPanel_checkSelected(nameSelPanel, playerNo, select)) {
                    select -= 2;
                }
            }

            if ((select < 0) || (select >= 8)) {
                select = 8;
            }
        } else {
            s32 ix = select & 1;
            s32 iy = select >> 1;
            s32 vy = 0;
            s32 vx = 0;

            if (rep & L_JPAD) {
                vx--;
            }
            if (rep & R_JPAD) {
                vx++;
            }

            if (rep & U_JPAD) {
                vy--;
            }
            if (rep & D_JPAD) {
                vy++;
            }

            if ((vx != 0) || (vy != 0)) {
                do {
                    ix = WrapI(0, 2, ix + vx);
                    iy += vy;
                } while ((iy >= 0) && (iy < 4) &&
                         menuNameSelPanel_checkSelected(nameSelPanel, playerNo, ix + (iy * 2)));
            }

            if (iy < 0 || iy >= 4) {
                nameSelPanel->column[playerNo] = select & 1;
                select = 8;
            } else {
                select = ix + (iy * 2);
            }
        }
    }

    if (select != nameSelPanel->select[playerNo]) {
        sound = SND_INDEX_64;
        nameSelPanel->select[playerNo] = select;
    }

    if (trg & (A_BUTTON | START_BUTTON)) {
        vec = MIN(1, nameSelPanel->depth[playerNo] + 1);

        if (vec != nameSelPanel->depth[playerNo]) {
            if (nameSelPanel->flags.guest || (nameSelPanel->select[playerNo] != 8)) {
                sound = SND_INDEX_62;
            }

            nameSelPanel->depth[playerNo] = vec;
        }
    } else if (trg & B_BUTTON) {
        vec = MAX(-1, nameSelPanel->depth[playerNo] - 1);

        if (vec != nameSelPanel->depth[playerNo]) {
            sound = SND_INDEX_68;
            nameSelPanel->depth[playerNo] = vec;
        }
    }

    SND_PLAY_INDEX(sound);
}

/**
 * Original name: menuNameSelPanel_input
 */
bool menuNameSelPanel_input(MenuNameSelPanel *nameSelPanel) {
    s32 ok = 0;
    s32 i;

    if ((nameSelPanel->miBase.transStep < 0.0f) || (nameSelPanel->miBase.transTime < 1.0f)) {
        return false;
    }

    nameSelPanel->flow = 0;

    for (i = 0; i < nameSelPanel->playerCount; i++) {
        menuNameSelPanel_input1(nameSelPanel, i);

        if (nameSelPanel->depth[i] > 0) {
            ok++;
            continue;
        }

        if (nameSelPanel->depth[i] < 0) {
            nameSelPanel->depth[i] = 0;
            nameSelPanel->flow = -1;
            return true;
        }
    }

    if (ok == nameSelPanel->playerCount) {
        nameSelPanel->flow = 1;
    }

    return true;
}

/**
 * Original name: menuNameSelPanel_update
 */
void menuNameSelPanel_update(MenuNameSelPanel *nameSelPanel, SMenuItem *parent) {
    s32 i;
    s32 j;

    menuItem_update(&nameSelPanel->miBase, parent);
    menuItem_updateN(nameSelPanel->miLabel, ARRAY_COUNT(nameSelPanel->miLabel), &nameSelPanel->miBase);

    for (i = 0; i < nameSelPanel->playerCount; i++) {
        nameSelPanel->cursor[i].miCursor.colorRange[0][3] = 1.0f;
    }

    for (i = 0; i < nameSelPanel->playerCount - 1; i++) {
        for (j = i + 1; j < nameSelPanel->playerCount; j++) {
            if (nameSelPanel->select[i] == nameSelPanel->select[j]) {
                //! FAKE:

#if VERSION_CN
                SMenuItem *item = &nameSelPanel->cursor[i].miCursor;
                SMenuItem *item2 = &nameSelPanel->cursor[j].miCursor;

                item->colorRange[0][3] = 0.0f;
                item2->colorRange[0][3] = 0.0f;
#elif VERSION_US || VERSION_GW
                nameSelPanel->cursor[i].miCursor.colorRange[0][3] = 0.0f;
                nameSelPanel->cursor[j].miCursor.colorRange[0][3] = 0.0f;
#else
#error ""
#endif
            }
        }
    }

    for (i = 0; i < ARRAY_COUNTU(nameSelPanel->cursor); i++) {
        menuCursor_update(&nameSelPanel->cursor[i], &nameSelPanel->miLabel[nameSelPanel->select[i]]);
        if (nameSelPanel->depth[i] > 0) {
            SMenuItem *item = &nameSelPanel->cursor[i].miCursor;

            for (j = 0; j < MENUITEM_COLOR_COUNT; j++) {
                item->color[j] = item->colorRange[1][j];
            }

            nameSelPanel->cursor[i].flags.finger = false;
            nameSelPanel->cursor[i].flags.blink = false;
        } else {
            nameSelPanel->cursor[i].flags.finger = true;
            nameSelPanel->cursor[i].flags.blink = true;
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
    MenuCursor *list[nameSelPanel->playerCount];
    TiTexData *texC;
    s32 cached;
    s32 i;
    s32 pad[2] UNUSED;

    gSPDisplayList(gfx++, fade_normal_texture_init_dl);

    texC = _getTexMain(nameSelPanel->global, 4);
    menuItem_drawTex(&nameSelPanel->miBase, &gfx, texC, 0);

    texC = _getTexMain(nameSelPanel->global, 7);

    cached = 0;
    for (i = 0; i < ARRAY_COUNTU(nameSelPanel->miLabel) - 1; i++) {
        cached += menuItem_drawTex(&nameSelPanel->miLabel[i], &gfx, texC, cached);
    }

    texC = _getTexMain(nameSelPanel->global, _texEndOrGuest_3608[nameSelPanel->flags.guest]);
    menuItem_drawTex(&nameSelPanel->miLabel[i], &gfx, texC, 0);

    gSPDisplayList(gfx++, fade_intensity_texture_init_dl);
    gDPSetTextureFilter(gfx++, G_TF_BILERP);

    for (i = 0; i < ARRAY_COUNTU(nameSelPanel->miLabel) - 1; i++) {
        SMenuItem *item = &nameSelPanel->miLabel[i];
        const u8 *name;
        s32 j;

        if (menuItem_outOfScreen(item, 0xE, 0xE)) {
            continue;
        }

        // wtf
        if (evs_mem_data[i].mem_use_flg & MEM_USE_FLG_1) {
            name = evs_mem_data[i].mem_name;
        } else {
            name = evs_mem_data[i].mem_name;
        }

        j = item->color[3] * 255.0f;
        if (evs_mem_data[i].mem_use_flg & MEM_USE_FLG_1) {
            gDPSetPrimColor(gfx++, 0, 0, 1, 1, 1, j);
        } else {
            gDPSetPrimColor(gfx++, 0, 0, 160, 160, 160, 255);
        }

        for (j = 0; j < MEM_NAME_LEN; j++) {
            fontXX_drawID(&gfx, item->trans[0] + 4.0f + j * 0xC, item->trans[1] + 4.0f, item->scale[0] * 12.0f,
                          item->scale[1] * 12.0f, name[j]);
        }
    }

    for (i = 0; i < nameSelPanel->playerCount; i++) {
        list[i] = &nameSelPanel->cursor[i];
    }
    menuCursor_draw(list, nameSelPanel->playerCount, &gfx);

    *gfxP = gfx;
}

/**
 * Original name: menuNameOpPanel_setFrame
 */
void menuNameOpPanel_setFrame(MenuNameOpPanel *nameOpPanel, s32 dir, f32 time) {
    SMenuItem *item = &nameOpPanel->miBase;

    item->transTime = time;
    item->transStep = 0.05f;
    item->transRange[0][0] = item->transRange[1][0] - 320.0f;
    menuItem_setTransDir(item, dir);
}

/**
 * Original name: _name_3803
 */
const u8 _name_3803[MENUNAMEOPPANEL_NAME_LEN] = { 0 };

/**
 * Original name: menuNameOpPanel_init
 */
void menuNameOpPanel_init(MenuNameOpPanel *nameOpPanel, struct_watchMenu *global, MenuNameOpPanelType type, s32 select,
                          const u8 *name, s32 x, s32 y) {
    s32 i;

    nameOpPanel->global = global;
    nameOpPanel->type = type;
    nameOpPanel->select = select;

    if (name == NULL) {
        name = _name_3803;
    }

    for (i = 0; i < MENUNAMEOPPANEL_NAME_LEN; i++) {
        nameOpPanel->name[i] = name[i];
    }

    menuItem_init(&nameOpPanel->miBase, x, y);
    menuItem_init(&nameOpPanel->miName, 35, 8);

    for (i = 0; i < ARRAY_COUNTU(nameOpPanel->miPanel); i++) {
        menuItem_init(&nameOpPanel->miPanel[i], 11, 31 + 23 * i);
    }

    menuCursor_init(&nameOpPanel->cursor, global, CURSOR_ITEM, 0, 0, 0, 105, 20);
    nameOpPanel->cursor.flags.finger = true;
}

/**
 * Original name: menuNameOpPanel_input
 */
bool menuNameOpPanel_input(MenuNameOpPanel *nameOpPanel, s32 playerNo) {
    u32 rep = _getKeyRep(nameOpPanel->global, playerNo);
    s32 vec = nameOpPanel->select;

    if ((nameOpPanel->miBase.transStep < 0.0f) || (nameOpPanel->miBase.transTime < 1.0f)) {
        return false;
    }

    if (rep & U_JPAD) {
        vec--;
    }
    if (rep & D_JPAD) {
        vec++;
    }

    vec = WrapI(0, 2, vec);
    if (vec != nameOpPanel->select) {
        dm_snd_play(SND_INDEX_64);
        nameOpPanel->select = vec;
    }
    return true;
}

/**
 * Original name: menuNameOpPanel_update
 */
void menuNameOpPanel_update(MenuNameOpPanel *nameOpPanel, SMenuItem *parent) {
    menuItem_update(&nameOpPanel->miBase, parent);
    menuItem_update(&nameOpPanel->miName, &nameOpPanel->miBase);
    menuItem_updateN(nameOpPanel->miPanel, ARRAY_COUNT(nameOpPanel->miPanel), &nameOpPanel->miBase);
    menuCursor_update(&nameOpPanel->cursor, &nameOpPanel->miPanel[nameOpPanel->select]);
}

/**
 * Original name: _panel_3859
 */
const s32 _panel_3859[][2] = {
    { 24, 25 }, // MENUNAMEOPPANELTYPE_0
    { 28, 25 }, // MENUNAMEOPPANELTYPE_1
};
static_assert(ARRAY_COUNT(_panel_3859) == MENUNAMEOPPANELTYPE_MAX, "");

/**
 * Original name: menuNameOpPanel_draw
 */
void menuNameOpPanel_draw(MenuNameOpPanel *nameOpPanel, Gfx **gfxP) {
    Gfx *gfx = *gfxP;
    MenuCursor *list[1];
    SMenuItem *item;
    TiTexData *texC;
    s32 i;

    gSPDisplayList(gfx++, fade_normal_texture_init_dl);

    texC = _getTexMain(nameOpPanel->global, 2);
    menuItem_drawTex(&nameOpPanel->miBase, &gfx, texC, 0);

    texC = _getTexCommon(nameOpPanel->global, 0xE);
    for (i = 0; i < ARRAY_COUNTU(nameOpPanel->miPanel); i++) {
        menuItem_drawItem(&nameOpPanel->miPanel[i], &gfx, texC, 0, 0x2F, _panel_3859[nameOpPanel->type][i]);
    }

    texC = _getTexMain(nameOpPanel->global, 7);
    menuItem_drawTex(&nameOpPanel->miName, &gfx, texC, 0);

    gSPDisplayList(gfx++, fade_intensity_texture_init_dl);
    gDPSetTextureFilter(gfx++, G_TF_BILERP);
    gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, 255);

    item = &nameOpPanel->miName;
    for (i = 0; i < ARRAY_COUNTU(nameOpPanel->name); i++) {
        fontXX_drawID(&gfx, item->trans[0] + 4.0f + (i * 12), item->trans[1] + 4.0f, item->scale[0] * 12.0f,
                      item->scale[1] * 12.0f, nameOpPanel->name[i]);
    }

    list[0] = &nameOpPanel->cursor;
    menuCursor_draw(list, ARRAY_COUNT(list), &gfx);

    *gfxP = gfx;
}

void menuSndSelPanel_setFrame(MenuSndSelPanel *sndSelPanel, s32 dir, f32 time) {
    SMenuItem *item = &sndSelPanel->miBase;

    item->transTime = time;
    item->transStep = 0.05f;
    item->transRange[0][0] = item->transRange[1][0] - 320.0f;
    menuItem_setTransDir(item, dir);
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
void menuSndSelPanel_init(MenuSndSelPanel *sndSelPanel, struct_watchMenu *global, s32 select, s32 x, s32 y) {
    s32 i;

    sndSelPanel->global = global;
    sndSelPanel->select = select;
    sndSelPanel->bgmNo = 0;
    sndSelPanel->sndId = 0;
    sndSelPanel->sndNo = SND_INDEX_0;

    menuItem_init(&sndSelPanel->miBase, x, y);

    for (i = 0; i < ARRAY_COUNTU(sndSelPanel->miPanel); i++) {
        menuItem_init(&sndSelPanel->miPanel[i], 14, _y_4020[i]);
    }

    for (i = 0; i < ARRAY_COUNTU(sndSelPanel->number); i++) {
        menuNumber_init(&sndSelPanel->number[i], global, 0, i + 2, 0, _pos_4015[i], 4);
    }

    menuCursor_init(&sndSelPanel->cursor, global, CURSOR_ITEM, 0, 0, 0, 105, 20);
    sndSelPanel->cursor.flags.finger = true;
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
bool menuSndSelPanel_input(MenuSndSelPanel *sndSelPanel, s32 playerNo) {
    SndIndex sound = SND_INDEX_INVALID;
    u32 rep = _getKeyRep(sndSelPanel->global, playerNo);
    s32 vec = sndSelPanel->select;

    if ((sndSelPanel->miBase.transStep < 0.0f) || (sndSelPanel->miBase.transTime < 1.0f)) {
        return false;
    }

    if (rep & U_JPAD) {
        vec--;
    }
    if (rep & D_JPAD) {
        vec++;
    }

    vec = WrapI(0, 4, vec);
    if (vec != sndSelPanel->select) {
        sound = SND_INDEX_64;
        sndSelPanel->select = vec;
    }

    vec = 0;
    if (rep & L_JPAD) {
        vec--;
    }
    if (rep & R_JPAD) {
        vec++;
    }
    if (rep & L_TRIG) {
        vec -= 10;
    }
    if (rep & R_TRIG) {
        vec += 10;
    }

    if (vec != 0) {
        if (sndSelPanel->select >= 2) {
            sound = SND_INDEX_63;
            switch (sndSelPanel->select) {
                case 0x2:
                    sndSelPanel->bgmNo = WrapI(0, 24, sndSelPanel->bgmNo + vec);
                    break;

                case 0x3:
                    sndSelPanel->sndId = WrapI(0, ARRAY_COUNT(_tbl_4036), sndSelPanel->sndId + vec);
                    sndSelPanel->sndNo = _tbl_4036[sndSelPanel->sndId];
                    break;
            }
        }
    }

    SND_PLAY_INDEX(sound);

    return true;
}

/**
 * Original name: menuSndSelPanel_update
 */
void menuSndSelPanel_update(MenuSndSelPanel *sndSelPanel, SMenuItem *parentItem) {
    s32 i;

    sndSelPanel->number[0].number = sndSelPanel->bgmNo;
    sndSelPanel->number[1].number = sndSelPanel->sndId;
    menuItem_update(&sndSelPanel->miBase, parentItem);
    menuItem_updateN(sndSelPanel->miPanel, ARRAY_COUNT(sndSelPanel->miPanel), &sndSelPanel->miBase);

    for (i = 0; i < ARRAY_COUNT(sndSelPanel->number); i++) {
        menuNumber_update(&sndSelPanel->number[i], &sndSelPanel->miPanel[i + 2]);
    }

    menuCursor_update(&sndSelPanel->cursor, &sndSelPanel->miPanel[sndSelPanel->select]);
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
    void *list[ARRAY_COUNT(sndSelPanel->number)];
    s32 pad[2] UNUSED;
    Gfx *gfx = *gfxP;
    SMenuItem *item;
    s32 i;
    TiTexData *texC;
    f32 x;
    f32 y;

    gSPDisplayList(gfx++, fade_normal_texture_init_dl);

    item = &sndSelPanel->miBase;

    x = item->trans[0];
    y = item->trans[1];
    texC = _getTexMain(sndSelPanel->global, 0xB);

    menuItem_drawTex(item, &gfx, texC, 0);
    item->trans[1] += 76.0f;
    menuItem_drawTex(item, &gfx, texC, 0);
    item->trans[0] = x + 19.0f;
    item->trans[1] = y + 2.0f;
    texC = _getTexMain(sndSelPanel->global, 0xC);
    menuItem_drawTex(item, &gfx, texC, 0);
    item->trans[0] = x;
    item->trans[1] = y;

    texC = _getTexCommon(sndSelPanel->global, 0xE);
    for (i = 0; i < ARRAY_COUNTU(sndSelPanel->miPanel); i++) {
        menuItem_drawItem(&sndSelPanel->miPanel[i], &gfx, texC, 0, 0x2F, _panel_4108[i]);
    }

    for (i = 0; i < ARRAY_COUNTU(sndSelPanel->number); i++) {
        list[i] = &sndSelPanel->number[i];
    }
    menuNumber_draw((void *)list, ARRAY_COUNT(list), &gfx);

    list[0] = &sndSelPanel->cursor;
    menuCursor_draw((void *)list, 1, &gfx);

    *gfxP = gfx;
}

/**
 * Original name: _menuPlay2Panel_loadAnime
 */
void _menuPlay2Panel_loadAnime(void *arg) {
    MenuPlay2Panel *play2Panel = arg;
    void *heap = play2Panel->animeAddr;

    animeState_load(&play2Panel->animeState, &heap, play2Panel->charNo);
    play2Panel->flags.loaded = true;
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
void menuPlay2Panel_init(MenuPlay2Panel *play2Panel, struct_watchMenu *global, void **heapP, s32 size, s32 playerCount,
                         s32 cpuCount, s32 playerNo, bool cpuFlag, CharAnimeMode charNo, s32 virusLevel, s32 gameSpeed,
                         s32 x, s32 y) {
    void *heap = *heapP;
    SMenuItem *item;
    s32 i;

    play2Panel->global = global;

    switch (_getMode(global)) {
        case MODE_VSCOM:
        case MODE_VSMAN:
        case MODE_PLAY4_LV:
        case MODE_PLAY4_TB_LV:
            play2Panel->flash = false;
            play2Panel->timeAt = false;
            play2Panel->FL_TA = false;
            break;

        case MODE_VSCOM_FL:
        case MODE_VSMAN_FL:
        case MODE_PLAY4_FL_LV:
            play2Panel->flash = true;
            play2Panel->timeAt = false;
            play2Panel->FL_TA = true;
            break;

        case MODE_VSMAN_TA:
            play2Panel->flash = false;
            play2Panel->timeAt = true;
            play2Panel->FL_TA = true;
            break;

        default:
            break;
    }

    play2Panel->size = size;
    play2Panel->playerCount = playerCount;
    play2Panel->cpuCount = cpuCount;
    play2Panel->playerNo = playerNo;
    play2Panel->charNo = charNo;
    play2Panel->depth = 0;

    if (cpuFlag) {
        play2Panel->flow = -1;
    } else {
        play2Panel->flow = 0;
    }

    play2Panel->flags.cpu = !!cpuFlag;
    play2Panel->flags.loaded = false;

    menuItem_init(&play2Panel->miBase, x, y);
    menuItem_init(&play2Panel->miPlayer, _player_4309[size][0], _player_4309[size][1]);
    menuItem_init(&play2Panel->miPlayerNo, 0xA, 4);

    if (play2Panel->FL_TA) {
        menuSpeedAsk_init(&play2Panel->glvAsk, global, 2, virusLevel, _glvAsk_4314[size][0], _glvAsk_4314[size][1]);
        menuSpeedItem_init(&play2Panel->glvItem, global, size + 2, playerNo, virusLevel, _glvItem_4315[size][0],
                           _glvItem_4315[size][1], 0x2A);
    } else {
        menuLvGauge_init(&play2Panel->lvGauge, global, size, playerNo, virusLevel, _lvGauge_4311[size][0],
                         _lvGauge_4311[size][1]);
        menuNumber_init(&play2Panel->lvNum, global, size, 2, virusLevel, _lvNum_4310[size][0], _lvNum_4310[size][1]);

        item = &play2Panel->lvNum.miBase;
        menuItem_setScaleLow(item, _lvNumScale_4308[size][0], _lvNumScale_4308[size][1]);
        menuItem_setScaleHi(item, _lvNumScale_4308[size][0], _lvNumScale_4308[size][1]);
    }

    menuSpeedAsk_init(&play2Panel->speedAsk, global, 0, gameSpeed, _speedAsk_4312[size][0], _speedAsk_4312[size][1]);
    menuSpeedItem_init(&play2Panel->speedItem, global, size, playerNo, gameSpeed, _speedItem_4313[size][0],
                       _speedItem_4313[size][1], 0x2A);

    switch (size) {
        case 0:
            break;

        case 1:
            play2Panel->animeAddr = ALIGN_PTR(heap);
            heap = (void *)((uintptr_t)play2Panel->animeAddr + animeState_getDataSize(charNo));
            BgTasksManager_SendTask(_menuPlay2Panel_loadAnime, play2Panel);
            break;
    }

    menuItem_init(&play2Panel->miOk, 8, _okY_4316[size]);
    menuItem_setColor_fade(&play2Panel->miOk);
    menuItem_setColorDir(&play2Panel->miOk, -1);
    play2Panel->miOk.colorTime = 0.0f;

    for (i = 0; i < ARRAY_COUNTU(play2Panel->cursor); i++) {
        menuCursor_init(&play2Panel->cursor[i], global, CURSOR_PANEL, playerNo, _cursor_4317[size][i][0],
                        _cursor_4317[size][i][1], _cursor_4317[size][i][2], _cursor_4317[size][i][3]);
    }

    *heapP = heap;
}

/**
 * Original name: menuPlay2Panel_copyConfig
 */
void menuPlay2Panel_copyConfig(MenuPlay2Panel *play2Panel, MenuPlay2Panel *from) {
    if (play2Panel == from) {
        return;
    }

    switch (from->depth) {
        case 0:
            if (play2Panel->FL_TA) {
                play2Panel->glvItem.select = from->glvItem.select;
            } else {
                play2Panel->lvGauge.level = from->lvGauge.level;
            }
            break;

        case 1:
            play2Panel->speedItem.select = from->speedItem.select;
            break;
    }
}

/**
 * Original name: menuPlay2Panel_copyCursor
 */
void menuPlay2Panel_copyCursor(MenuPlay2Panel *play2Panel, MenuPlay2Panel *from) {
    s32 i;

    if (play2Panel == from) {
        return;
    }

    for (i = 0; i < ARRAY_COUNTU(play2Panel->cursor); i++) {
        play2Panel->cursor[i].flags.cursor = false;
    }

    if (play2Panel->FL_TA) {
        play2Panel->glvItem.cursor.flags.cursor = false;
        play2Panel->glvItem.cursor.flags.finger = false;
    } else {
        play2Panel->lvGauge.cursor.flags.cursor = false;
        play2Panel->lvGauge.cursor.flags.finger = false;
    }

    play2Panel->speedItem.cursor.flags.cursor = false;
    play2Panel->speedItem.cursor.flags.finger = false;

    switch (from->depth) {
        case 0x0:
            if (play2Panel->FL_TA) {
                play2Panel->glvItem.cursor.flags.finger = true;
            } else {
                play2Panel->lvGauge.cursor.flags.finger = true;
            }
            break;

        case 0x1:
            play2Panel->speedItem.cursor.flags.finger = true;
            break;
    }
}

/**
 * Original name: menuPlay2Panel_input
 */
void menuPlay2Panel_input(MenuPlay2Panel *play2Panel, s32 playerNo, bool topFlag, bool bottomFlag) {
    u32 rep = _getKeyRep(play2Panel->global, playerNo);
    u32 trg = _getKeyTrg(play2Panel->global, playerNo);
    SndIndex sound = SND_INDEX_INVALID;
    s32 vec = 0;
    s32 depth;

    switch (play2Panel->flow) {
        case -1:
            play2Panel->flow = 0;
            FALLTHROUGH;

        case 0:
            if ((rep & U_JPAD) || (trg & B_BUTTON)) {
                vec--;
            }
            if ((rep & D_JPAD) || (trg & (A_BUTTON | START_BUTTON))) {
                vec++;
            }

            depth = CLAMP(play2Panel->depth + vec, 0, 1);

            if (depth != play2Panel->depth) {
                sound = SND_INDEX_64;
                play2Panel->depth = depth;
            } else {
                switch (play2Panel->depth) {
                    case 0:
                        if (!play2Panel->FL_TA) {
                            menuLvGauge_input(&play2Panel->lvGauge, playerNo);
                        } else {
                            menuSpeedItem_input(&play2Panel->glvItem, playerNo);
                        }
                        break;

                    case 1:
                        menuSpeedItem_input(&play2Panel->speedItem, playerNo);
                }
            }

            if (sound <= SND_INDEX_INVALID) {
                switch (play2Panel->depth) {
                    case 1:
                        if ((trg & (A_BUTTON | START_BUTTON)) || ((rep & D_JPAD) && !bottomFlag)) {
                            sound = SND_INDEX_62;
                            play2Panel->flow += 1;
                        }
                        break;

                    case 0:
                        if ((trg & B_BUTTON) || ((rep & U_JPAD) && !topFlag)) {
                            sound = SND_INDEX_68;
                            play2Panel->flow -= 1;
                        }
                        break;
                }
            }
            break;

        case 1:
            if ((trg & B_BUTTON) || ((trg & U_JPAD) && !topFlag)) {
                play2Panel->flow = 0;
                sound = SND_INDEX_68;
            }
            break;

        default:
            break;
    }

    SND_PLAY_INDEX(sound);
}

/**
 * Original name: menuPlay2Panel_update
 */
void menuPlay2Panel_update(MenuPlay2Panel *play2Panel, SMenuItem *parent) {
    SMenuItem *item;
    s32 i;

    if (play2Panel->FL_TA) {
        play2Panel->glvAsk.select = play2Panel->glvItem.select;
    } else {
        play2Panel->lvNum.number = play2Panel->lvGauge.level;
    }

    play2Panel->speedAsk.select = play2Panel->speedItem.select;

    menuItem_update(&play2Panel->miBase, parent);
    menuItem_update(&play2Panel->miPlayer, &play2Panel->miBase);
    menuItem_update(&play2Panel->miPlayerNo, &play2Panel->miBase);

    if (play2Panel->FL_TA) {
        menuSpeedAsk_update(&play2Panel->glvAsk, &play2Panel->miBase);
        menuSpeedItem_update(&play2Panel->glvItem, &play2Panel->miBase);
    } else {
        menuNumber_update(&play2Panel->lvNum, &play2Panel->miBase);
        menuLvGauge_update(&play2Panel->lvGauge, &play2Panel->miBase);
    }

    menuSpeedAsk_update(&play2Panel->speedAsk, &play2Panel->miBase);
    menuSpeedItem_update(&play2Panel->speedItem, &play2Panel->miBase);

    switch (play2Panel->size) {
        case 0:
            break;

        case 1:
            if (play2Panel->flags.loaded) {
                item = &play2Panel->miPlayer;

                play2Panel->animeState.primColor[0] = item->color[0] * 255.0f;
                play2Panel->animeState.primColor[1] = item->color[1] * 255.0f;
                play2Panel->animeState.primColor[2] = item->color[2] * 255.0f;
                play2Panel->animeState.primColor[3] = item->color[3] * 255.0f;
                animeState_update(&play2Panel->animeState);
            }
            break;
    }

    menuItem_update(&play2Panel->miOk, &play2Panel->miBase);

    if (play2Panel->flow == 1) {
        item = &play2Panel->miOk;

        for (i = 0; i < MENUITEM_COLOR_COUNT; i++) {
            item->color[i] = parent->color[i];
        }
    }

    for (i = 0; i < ARRAY_COUNTU(play2Panel->cursor); i++) {
        menuCursor_update(&play2Panel->cursor[i], &play2Panel->miBase);
    }

    menuItem_setColorDir(&play2Panel->miBase, (play2Panel->flow != 0) ? -1 : 1);

    i = 0;
    if ((play2Panel->flow == 0) && (play2Panel->depth == 0)) {
        i = 1;
    }

    play2Panel->cursor[0].flags.cursor = i;

    if (play2Panel->FL_TA) {
        play2Panel->glvItem.flags.blink = i;
        play2Panel->glvItem.cursor.flags.finger = i;
    } else {
        play2Panel->lvGauge.cursor.flags.finger = i;
        play2Panel->lvGauge.cursor.flags.cursor = i;
        play2Panel->lvGauge.cursor.flags.blink = i;
    }

    i = 0;
    if ((play2Panel->flow == 0) && (play2Panel->depth == 1)) {
        i = 1;
    }

    play2Panel->speedItem.flags.blink = i;
    play2Panel->cursor[1].flags.cursor = i;

    play2Panel->speedItem.cursor.flags.finger = i;
}

/**
 * Original name: _charTbl_4601
 */
const s32 _charTbl_4601[] = {
    0, 1, 2, 3, 7, 5, 8, 4, 9, 6, 0xA, 0xB, 0xC, 0xE, 0xD,
};

/**
 * Original name: _type_4602
 */
const s32 _type_4602[][4] = {
    { 0, 4, 7, 9 },
    { 0, 1, 5, 8 },
    { 0, 1, 2, 6 },
    { 0, 1, 2, 3 },
};

/**
 * Original name: _texPanelP4_4617
 */
const s32 _texPanelP4_4617[] = {
    1,
    2,
};

/**
 * Original name: _texPanelP2_4618
 */
const s32 _texPanelP2_4618[] = { 0, 1 };

/**
 * Original name: menuPlay2Panel_draw
 */
void menuPlay2Panel_draw(MenuPlay2Panel *play2PanelArr[], s32 count, Gfx **gfxP) {
    Gfx *gfx = *gfxP;
    void *arr[8][count];
    s32 i;
    SMenuItem *item;
    MenuPlay2Panel *play2Panel;
    TiTexData *texC;
    TiTexData *texA;
    s32 cached;

    for (i = 0; i < count; i++) {
        play2Panel = play2PanelArr[i];

        arr[0][i] = &play2Panel->lvNum;
        arr[1][i] = &play2Panel->lvGauge;
        arr[2][i] = &play2Panel->speedAsk;
        arr[3][i] = &play2Panel->speedItem;
        arr[4][i] = &play2Panel->glvAsk;
        arr[5][i] = &play2Panel->glvItem;
        arr[6][i] = &play2Panel->cursor[0];
        arr[7][i] = &play2Panel->cursor[1];
    }

    gSPDisplayList(gfx++, fade_normal_texture_init_dl);

    for (i = 0; i < count; i++) {
        play2Panel = play2PanelArr[i];

        switch (play2Panel->size) {
            case 0:
                texC = _getTexP4(play2Panel->global, _texPanelP4_4617[play2Panel->FL_TA ? 1 : 0]);
                break;

            case 1:
                texC = _getTexP2(play2Panel->global, _texPanelP2_4618[play2Panel->FL_TA ? 1 : 0]);
                break;
        }

        menuItem_drawTex(&play2Panel->miBase, &gfx, texC, 0);
    }

    menuSpeedAsk_draw((void *)arr[2], count, &gfx);
    menuSpeedItem_draw1((void *)arr[3], count, &gfx);
    if (play2Panel->FL_TA) {
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
        play2Panel = play2PanelArr[i];
        item = &play2Panel->miPlayer;

        switch (play2Panel->size) {
            case 0:
                texC = _getTexP4(play2Panel->global, 0);
                menuItem_drawItem(item, &gfx, texC, 0, 0xF, _charTbl_4601[play2Panel->charNo]);
                break;

            case 1:
                if (play2Panel->flags.loaded) {
                    menuItem_setPrim(item, &gfx);
                    animeState_draw(&play2Panel->animeState, &gfx, item->trans[0], item->trans[1], -1.0f, 1.0f);
                }
                break;
        }
    }

    for (i = 0; i < count; i++) {
        s32 itemIndex;

        play2Panel = play2PanelArr[i];
        texC = _getTexSetup(play2Panel->global, 0x11);
        if ((play2Panel->playerNo == 1) && (play2Panel->playerCount == play2Panel->playerNo) &&
            (play2Panel->cpuCount == play2Panel->playerCount)) {
            itemIndex = 0xA;
        } else {
            itemIndex = _type_4602[play2Panel->playerCount - 1][play2Panel->playerNo];
        }
        menuItem_drawItem(&play2Panel->miPlayerNo, &gfx, texC, 0, 0xB, itemIndex);
    }

    gSPDisplayList(gfx++, fade_alpha_texture_init_dl);

    cached = 0;
    for (i = 0; i < count; i++) {
        play2Panel = play2PanelArr[i];

        texC = _getTexSetup(play2Panel->global, 0xB);
        texA = _getTexSetup(play2Panel->global, 4);
        cached += menuItem_drawAlphaTex(&play2Panel->miOk, &gfx, texC, texA, cached);
    }

    menuSpeedItem_draw2((void *)arr[3], count, &gfx);
    if (play2Panel->FL_TA) {
        menuSpeedItem_draw2((void *)arr[5], count, &gfx);
    } else {
        menuLvGauge_draw2((void *)arr[1], count, &gfx);
    }

    *gfxP = gfx;
}

/**
 * Original name: menuPlay2PanelSub_setFrame
 */
void menuPlay2PanelSub_setFrame(MenuPlay2PanelSub *play2PanelSub, s32 dir, f32 time) {
    SMenuItem *item = &play2PanelSub->miBase;

    item->transTime = time;
    item->transStep = 0.05f;
    item->transRange[0][1] = item->transRange[1][1] - SCREEN_HEIGHT;
    menuItem_setTransDir(item, dir);
}

const u8 _bgDataNo_to_stageNo[][2] = {
    { 0, 1 }, { 0, 3 }, { 0, 0 }, { 1, 5 }, { 0, 5 }, { 0, 4 }, { 1, 4 }, { 0, 2 }, { 0, 6 }, { 0, 7 },
};

/**
 * Original name: menuPlay2PanelSub_setStageBgFrame
 */
void menuPlay2PanelSub_setStageBgFrame(MenuPlay2PanelSub *play2PanelSub, s32 dir, f32 time, f32 vec) {
    SMenuItem *item = &play2PanelSub->miStageBg;

    item->transTime = time;
    item->transStep = 0.05f;
    item->transRange[0][0] = item->transRange[1][0] + vec;
    menuItem_setTransDir(item, dir);
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

/**
 * Original name: menuPlay2PanelSub_init
 */
void menuPlay2PanelSub_init(MenuPlay2PanelSub *play2PanelSub, struct_watchMenu *global, void **heapP UNUSED,
                            s32 stageNo, s32 musicNo, s32 x, s32 y) {
    SMenuItem *item;
    s32 i;

    play2PanelSub->global = global;
    play2PanelSub->depth = 0;
    play2PanelSub->flow = 0;
    play2PanelSub->topBgGap = -1;

    menuItem_init(&play2PanelSub->miBase, x, y);
    menuMusicItem_init(&play2PanelSub->musicItem, global, musicNo, 0x46, 9);

    menuNumber_init(&play2PanelSub->stageNum, global, 1, 2, stageNo, 0x60, 0x28);

    item = &play2PanelSub->stageNum.miBase;
    menuItem_setScaleLow(item, 7.0f / 8.0f, 15.0f / 16.0f);
    menuItem_setScaleHi(item, 7.0f / 8.0f, 15.0f / 16.0f);

    menuItem_init(&play2PanelSub->miStageBg, 0x9C, 0x30);

    for (i = 0; i < ARRAY_COUNTU(play2PanelSub->miBgCursor); i++) {
        menuItem_init(&play2PanelSub->miBgCursor[i], _bgCursor_4920[i][0], _bgCursor_4920[i][1]);
        menuItem_setColor_cursor(&play2PanelSub->miBgCursor[i]);
    }

    item = &play2PanelSub->miBgCursor[ARRAY_COUNTU(play2PanelSub->miBgCursor) - 1];
    item->scaleRange[0][0] = -item->scaleRange[0][0];
    item->scaleRange[1][0] = -item->scaleRange[1][0];

    for (i = 0; i < ARRAY_COUNTU(play2PanelSub->cursor); i++) {
        menuCursor_init(&play2PanelSub->cursor[i], global, CURSOR_ITEM, 0, _cursor_4921[i][0], _cursor_4921[i][1],
                        _cursor_4921[i][2], _cursor_4921[i][3]);
    }

    menuPlay2PanelSub_setFrame(play2PanelSub, -1, 0.0f);
}

/**
 * Original name: menuPlay2PanelSub_input
 */
bool menuPlay2PanelSub_input(MenuPlay2PanelSub *play2PanelSub, s32 playerNo) {
    u32 rep = _getKeyRep(play2PanelSub->global, playerNo);
    u32 trg = _getKeyTrg(play2PanelSub->global, playerNo);
    SndIndex sound = SND_INDEX_INVALID;
    s32 vec;
    s32 depth;

    if ((play2PanelSub->miBase.transStep < 0.0f) || (play2PanelSub->miBase.transTime < 1.0f)) {
        return false;
    }

    switch (play2PanelSub->flow) {
        case -1:
            play2PanelSub->flow = 0;
            FALLTHROUGH;

        case 0:
            vec = 0;
            if ((rep & U_JPAD) || (trg & B_BUTTON)) {
                vec--;
            }
            if ((rep & D_JPAD) || (trg & (A_BUTTON | START_BUTTON))) {
                vec++;
            }

            depth = CLAMP(play2PanelSub->depth + vec, 0, 1);
            if (depth != play2PanelSub->depth) {
                sound = SND_INDEX_64;
                play2PanelSub->depth = depth;
            } else {
                switch (depth) {
                    case 0:
                        menuMusicItem_input(&play2PanelSub->musicItem, playerNo);
                        break;

                    case 1:
                        vec = 0;
                        if (rep & L_JPAD) {
                            vec--;
                        }
                        if (rep & R_JPAD) {
                            vec++;
                        }

                        if (vec != 0) {
                            play2PanelSub->stageNum.number = WrapI(1, 0xB, play2PanelSub->stageNum.number + vec);
                            if (vec < 0) {
                                play2PanelSub->topBgGap = -1;
                            } else {
                                play2PanelSub->topBgGap = -2;
                            }

                            sound = SND_INDEX_63;
                            menuPlay2PanelSub_setStageBgFrame(play2PanelSub, 1, 0.0f, vec * 72);
                        }
                        break;
                }
            }

            if (sound <= SND_INDEX_INVALID) {
                if ((trg & (A_BUTTON | START_BUTTON)) && (play2PanelSub->depth == 1)) {
                    sound = SND_INDEX_62;
                    play2PanelSub->flow++;
                } else if ((trg & B_BUTTON) && (play2PanelSub->depth == 0)) {
                    sound = SND_INDEX_68;
                    play2PanelSub->flow--;
                }
            }
            break;

        case 1:
            if (trg & B_BUTTON) {
                sound = SND_INDEX_68;
                play2PanelSub->flow = 0;
            }
            break;
    }

    SND_PLAY_INDEX(sound);

    return true;
}

/**
 * Original name: menuPlay2PanelSub_update
 */
void menuPlay2PanelSub_update(MenuPlay2PanelSub *play2PanelSub, SMenuItem *parent) {
    SMenuItem *item = &play2PanelSub->miBase;
    s32 i;

    menuItem_update(item, parent);
    if (play2PanelSub->depth != 0) {
        play2PanelSub->musicItem.cursor.miBase.colorTime = 1.0f;
    }

    menuMusicItem_update(&play2PanelSub->musicItem, item);
    menuNumber_update(&play2PanelSub->stageNum, item);
    menuItem_update(&play2PanelSub->miStageBg, item);
    menuItem_updateN(play2PanelSub->miBgCursor, ARRAY_COUNT(play2PanelSub->miBgCursor), item);

    for (i = 0; i < ARRAY_COUNTU(play2PanelSub->cursor); i++) {
        menuCursor_update(&play2PanelSub->cursor[i], &play2PanelSub->miBase);
    }

    i = play2PanelSub->depth == 0;
    play2PanelSub->cursor[0].flags.cursor = i;
    play2PanelSub->musicItem.cursor.flags.finger = i;
    play2PanelSub->musicItem.flags.blink = i;

    i = play2PanelSub->depth == 1;
    play2PanelSub->cursor[1].flags.cursor = i;

    if (play2PanelSub->depth != 1) {
        for (i = 0; i < ARRAY_COUNTU(play2PanelSub->miBgCursor); i++) {
            SMenuItem *miBgCursor = &play2PanelSub->miBgCursor[i];
            s32 j;

            for (j = 0; j < 3; j++) {
                miBgCursor->color[j] = miBgCursor->colorRange[1][j] * parent->color[j];
            }
        }
    }
}

/**
 * Original name: menuPlay2PanelSub_draw
 */
void menuPlay2PanelSub_draw(MenuPlay2PanelSub *play2PanelSub, Gfx **gfxP) {
    Gfx *gfx = *gfxP;
    void *arr[2 * 4];
    SMenuItem *item;
    TiTexData *texC;
    s32 cached;
    s32 i;
    f32 x;

    gSPDisplayList(gfx++, fade_normal_texture_init_dl);

    texC = _getTexSetup(play2PanelSub->global, 0x12);
    menuItem_drawTex(&play2PanelSub->miBase, &gfx, texC, 0);

    for (i = 0; i < ARRAY_COUNTU(play2PanelSub->cursor); i++) {
        arr[i] = &play2PanelSub->cursor[i];
    }
    menuCursor_draw((void *)arr, ARRAY_COUNTU(play2PanelSub->cursor), &gfx);

    arr[0] = &play2PanelSub->musicItem;
    menuMusicItem_draw((void *)arr, 1, &gfx);
    arr[0] = &play2PanelSub->stageNum;
    menuNumber_draw((void *)arr, 1, &gfx);

    gSPDisplayList(gfx++, fade_normal_texture_init_dl);

    item = &play2PanelSub->miStageBg;
    menuItem_setPrim(item, &gfx);
    gfxSetScissor(&gfx, GFXSETSCISSOR_INTERLACE_NO, play2PanelSub->miBase.trans[0] + item->transRange[1][0] - 16.0f,
                  play2PanelSub->miBase.trans[1] + item->transRange[1][1], 0x68, 0x24);

    texC = _getTexSetup(play2PanelSub->global, 0xE);
    x = item->trans[0];
    item->trans[0] += play2PanelSub->topBgGap * 0x48;

    item = &play2PanelSub->miStageBg;
    for (i = 0; i < 4; i++) {
        menuItem_drawItem(item, &gfx, texC, 0, 0xA,
                          WrapI(0, 0xA, play2PanelSub->stageNum.number + play2PanelSub->topBgGap + i - 1));
        item->trans[0] += 72.0f;
    }

    gDPSetScissor(gfx++, G_SC_NON_INTERLACE, 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1);
    item->trans[0] = x;
    gSPDisplayList(gfx++, fade_normal_texture_init_dl);

    texC = _getTexSetup(play2PanelSub->global, 0x10);

    cached = 0;
    for (i = 0; i < ARRAY_COUNTU(play2PanelSub->miBgCursor); i++) {
        cached += menuItem_drawTex(&play2PanelSub->miBgCursor[i], &gfx, texC, cached);
    }

    *gfxP = gfx;
}

/**
 * Original name: _menuMain_lastMode
 */
MainMenuMode _menuMain_lastMode = MODE_MAIN;

/**
 * Original name: _tblMain_5279
 */
const char *_tblMain_5279[] = {
    _mesP1,
    _mes2P,
    _mes4P,
    _mesOpt,
};

/**
 * Original name: _tblPlay1_5280
 */
const char *_tblPlay1_5280[] = {
    _mesLv, _mesSt, _mesVsCom, _mesVcFlash, _mesLvTaiQ, _mesLvTimeAt,
};

/**
 * Original name: _tblPlay2_5281
 */
const char *_tblPlay2_5281[] = {
    _mesVsMan,
    _mesVmFlash,
    _mesVmTimeAt,
};

const char *D_8008E7C0[] UNUSED = {
    _mesVsNum,
    _mesVsNum,
    _mesVsNum,
    _mesVsNum,
};

/**
 * Original name: _tblBaTyp_5282
 */
const char *_tblBaTyp_5282[] = {
    _mesVs4P,
    _mes4PTag,
    _mes4PFlash,
};

/**
 * Original name: _tblOpt_5283
 */
const char *_tblOpt_5283[] = {
    _mesRec, _mesTutol, _mesName, _mesBak, _mesMisc,
};

/**
 * Original name: _tblTutol_5284
 */
const char *_tblTutol_5284[] = {
    _mesRule1, _mesRule2, _mesRule3, _mesRule4, _mesKotu,
};

/**
 * Original name: _tblSound_5285
 */
const char *_tblSound_5285[] = {
    _mesStereo,
    _mesMono,
    _mesSound,
    _mesSound,
};

/**
 * Original name: _tblMisc_5286
 */
const char *_tblMisc_5286[] = {
    _mesSnd,
    _mesVsCnt,
    _mesScore,
};

/**
 * Original name: _loopTbl_5287
 */
const char *_loopTbl_5287[] = {
    _mesSt,       _mesLv,   _mesVsCom, _mesVcFlash, _mesLvTaiQ, _mesLvTimeAt, _mesVsMan,     _mesVmFlash,
    _mesVmTimeAt, _mesVs4P, _mes4PTag, _mes4PFlash, _mesSnd,    _mesNs1,      _mesNameErase, _mesDoErase,
};

/**
 * Original name: menuMain_setMsgStr
 */
bool menuMain_setMsgStr(MenuMain *mMain, MainMenuMode mode, s32 select) {
    bool res = false;
    const char **tbl = NULL;
    const char *mes = NULL;
    s32 i;

    switch (mode) {
        case MODE_MAIN:
            tbl = _tblMain_5279;
            break;

        case MODE_PLAY1:
            tbl = _tblPlay1_5280;
            break;

        case MODE_PLAY2:
            tbl = _tblPlay2_5281;
            break;

        case MODE_PLAY4:
            mes = _mesVsNum;
            break;

        case MODE_OPTION:
            tbl = _tblOpt_5283;
            break;

        case MODE_MISC:
            tbl = _tblMisc_5286;
            break;

        case MODE_SCORE:
            mes = _mesScoreOnOff;
            break;

        case MODE_PLAY4_TYPE1:
        case MODE_PLAY4_TYPE2:
        case MODE_PLAY4_TYPE3:
        case MODE_PLAY4_TYPE4:
            tbl = _tblBaTyp_5282;
            break;

        case MODE_TUTORIAL:
            tbl = _tblTutol_5284;
            break;

        case MODE_SOUND:
            mes = _tblSound_5285[mMain->sndSel.select];
            break;

        case MODE_RECORD_MS:
            mes = _mesRecMs1;
            break;

        case MODE_RECORD_PLAY1:
        case MODE_RECORD_PLAY2:
            mes = _mesRecMs2;
            break;

        case MODE_NAME:
            mes = _mesNameSel;
            break;

        case MODE_NAME_DEL_YN:
            mes = _mesNameErase;
            break;

        case MODE_NAME_DEL_MES:
            mes = _mesNameErase2;
            break;

        case MODE_COUNT:
            mes = _mesVsCnt2;
            break;

        case MODE_BACKUP:
        case MODE_BACKUP_YN:
            mes = _mesDoErase;
            break;

        case MODE_BACKUP_MES:
            mes = _mesDoErase1;
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
            mes = _mesNs1;
            break;

        case MODE_NAME_NS:
            mes = _mesNs2;
            break;

        default:
            break;
    }

    if (tbl != NULL) {
        mes = tbl[select];
    }

    for (i = 0; i < ARRAY_COUNTU(_loopTbl_5287); i++) {
        if ((mes == _loopTbl_5287[i]) && msgWnd_isEnd(&mMain->msgWnd)) {
            mMain->msgStr = NULL;
        }
    }

    if (mes != mMain->msgStr) {
        msgWnd_clear(&mMain->msgWnd);
        if (mes != NULL) {
            msgWnd_addStr(&mMain->msgWnd, mes);
            res = true;
        }
        mMain->msgStr = mes;
    }

    return res;
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

/**
 * Original name: menuMain_initPanel
 */
void menuMain_initPanel(MenuMain *mMain, MainMenuMode mode, s32 panelSw, s32 select) {
    const s32 *table;
    s32 count;

    switch (mode) {
        case MODE_PLAY1:
            table = _play1_5340;
            count = ARRAY_COUNT(_play1_5340);
            break;

        case MODE_PLAY2:
            table = _play2_5341;
            count = ARRAY_COUNT(_play2_5341);
            break;

        case MODE_PLAY4:
            table = _play4_5342;
            count = ARRAY_COUNT(_play4_5342);
            break;

        case MODE_OPTION:
            table = _option_5344;
            count = ARRAY_COUNT(_option_5344);
            break;

        case MODE_PLAY4_TYPE1:
        case MODE_PLAY4_TYPE2:
        case MODE_PLAY4_TYPE3:
        case MODE_PLAY4_TYPE4:
            table = _play4type_5343;
            count = ARRAY_COUNT(_play4type_5343);
            break;

        case MODE_RECORD_MS:
            table = _recMs_5345;
            count = ARRAY_COUNT(_recMs_5345);
            break;

        case MODE_RECORD_PLAY1:
            table = _recMs1_5346;
            count = ARRAY_COUNT(_recMs1_5346);
            break;

        case MODE_RECORD_PLAY2:
            table = _recMs2_5347;
            count = ARRAY_COUNT(_recMs2_5347);
            break;

        case MODE_TUTORIAL:
            table = _tutorial_5348;
            count = ARRAY_COUNT(_tutorial_5348);
            break;

        case MODE_COUNT:
            table = _count_5349;
            count = ARRAY_COUNT(_count_5349);
            break;

        case MODE_BACKUP:
            table = _backup_5350;
            count = ARRAY_COUNT(_backup_5350);
            break;

        case MODE_MISC:
            table = _misc_5351;
            count = ARRAY_COUNT(_misc_5351);
            break;

        case MODE_SCORE:
            table = _score_5352;
            count = ARRAY_COUNT(_score_5352);
            break;

        case MODE_MAIN:
        default:
            table = _root_5339;
            count = ARRAY_COUNT(_root_5339);
            break;
    }

    menuMainPanel_init(&mMain->panel[panelSw], mMain->global, count, select, table, 25, 58);

#if VERSION_GW
    switch (mode) {
        case MODE_MAIN:
            menuItem_setColorDir(&mMain->panel[panelSw].miPanel[1], -1);
            mMain->panel[panelSw].miPanel[1].colorTime = 0.0f;
            menuItem_setColorDir(&mMain->panel[panelSw].miPanel[2], -1);
            mMain->panel[panelSw].miPanel[2].colorTime = 0.0f;
            break;

        case MODE_RECORD_MS:
            menuItem_setColorDir(&mMain->panel[panelSw].miPanel[1], -1);
            mMain->panel[panelSw].miPanel[1].colorTime = 0.0f;
            break;

        default:
            break;
    }
#endif
}

/**
 * Original name: menuMain_initPanel
 */
void menuMain_init(MenuMain *mMain, struct_watchMenu *global, void **heapP) {
    SMenuItem *item;
    s32 i;

    mMain->global = global;
    if (_getModeOld(global) == MODE_NAME_NE2) {
        mMain->mode = _menuMain_lastMode = MODE_NAME_NS;
    } else {
        mMain->mode = _menuMain_lastMode;
    }

    mMain->depth = _menuMain_lastDepth;
    for (i = 0; i < ARRAY_COUNTU(_menuMain_lastSelect); i++) {
        mMain->select[i] = _menuMain_lastSelect[i];
    }

    if (_getModeOld(global) == MODE_MAIN) {
        mMain->select[0] = 0;
    }

    mMain->screenNo = 0;
    mMain->screenDir = -1;
    mMain->playSeqNo = SEQ_INDEX_12;
    mMain->msgStr = 0;
    mMain->current = 0;
    mMain->kasaCount = 0;

    for (i = 0; i < ARRAY_COUNTU(mMain->panel); i++) {
        menuMain_initPanel(mMain, mMain->mode, i, mMain->select[mMain->depth]);
        menuMainPanel_setFrame(&mMain->panel[i], -1, 0);
    }

    i = 1;
    switch (mMain->mode) {
        default:
            break;

        case MODE_VSMAN_NS:
        case MODE_VSMAN_FL_NS:
        case MODE_VSMAN_TA_NS:
            i = 2;
            break;
    }

    menuNameSelPanel_init(&mMain->nameSel, global, mMain->mode != MODE_NAME_NS, i, 0x19, 0x3A);
    menuNameSelPanel_setFrame(&mMain->nameSel, -1, 0.0f);

    menuNameOpPanel_init(&mMain->nameOp, mMain->global, MENUNAMEOPPANELTYPE_0, 0, NULL, 0x19, 0x3A);
    menuNameOpPanel_setFrame(&mMain->nameOp, -1, 0.0f);

    menuSndSelPanel_init(&mMain->sndSel, global, 0, 0x14, 0x3A);
    menuSndSelPanel_setFrame(&mMain->sndSel, -1, 0.0f);

    switch (mMain->mode) {
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
            menuNameSelPanel_setFrame(&mMain->nameSel, 1, 0);
            break;

        default:
            menuMainPanel_setFrame(mMain->panel, 1, 0);
            break;
    }

    msgWnd_init(&mMain->msgWnd, heapP, 12, 4, 156, 34);
    mMain->msgWnd.contFlags = 0;

#if VERSION_CN
    mMain->msgWnd.rowStep = 14;
#else
    mMain->msgWnd.rowStep = 13;
#endif

    item = &mMain->miMsgWnd;
    menuItem_init(item, 0x9E, 0x2F);
    item->transTime = 0.0f;
    item->transStep = 0.05f;
    item->transRange[0][0] += 320.0f;

    menuItem_init(&mMain->miKaSaMaRu, 0xDC, 0x63);
    item = &mMain->miKaSaMaRu;
    item->transStep = 0.05f;
    item->transTime = 0.0f;
    item->transRange[0][0] += 320.0f;

    menuItem_init(&mMain->miScrWnd, -0x44, 0x16);
    item = &mMain->miScrWnd;
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

    menuItem_init(&mMain->miScreen, 6, 5);
    mMain->miScreen.flags.localColor = true;

    menuItem_init(&mMain->miSmoke, 0x51, 0x11);

    menuCont_init(&mMain->cont, global, 0xE, 0x71);

    menuYN_init(&mMain->yesNo, global, 0x78, 0x8C);

    menuMes_init(&mMain->message, global, heapP, 0x11, 2, 0x40, 0xA6);
}

/**
 * Original name: menuMain_waitCancel
 */
void menuMain_waitCancel(MenuMain *mMain) {
    u32 trg = _getKeyTrg(mMain->global, 0);

    if ((trg & B_BUTTON) && (mMain->mode != MODE_MAIN)) {
        _setFadeDir(mMain->global, -1);
        _setNextMain(mMain->global, MAIN_MENU);
        dm_snd_play(SND_INDEX_68);
    }
}

const char *mes_5577[] = {
    _mesNoCont2,
    _mesNoCont3,
    _mesNoCont4,
};

/**
 * Original name: _menuMain_updateCallback
 */
void _menuMain_updateCallback(void *arg) {
    MenuMain *mMain = arg;

    menuMain_update(mMain);
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

/**
 * Original name: menuMain_input
 */
void menuMain_input(MenuMain *mMain) {
    MenuMainPanel *panel = &mMain->panel[mMain->current];
    u32 trg = _getKeyTrg(mMain->global, 0);
    s32 i;
    s32 select;
    SndIndex sound;
    s32 nameDir;
    s32 panelDir;
    s32 nameSelDir;
    s32 wndDir;
    s32 kasaDir;
    s32 contDir;
    s32 ynDir;
    s32 mesDir;
    s32 sndSelDir;
    s32 flow[2];

    if (_getMode(mMain->global) == MODE_MAIN) {
        _setTitle(mMain->global, mMain->mode);
    }

    i = 0;

    switch (mMain->mode) {
        case MODE_NAME_DEL_MES:
        case MODE_BACKUP_MES:
            i = 1;
            break;

        case MODE_NAME_DEL_YN:
        case MODE_BACKUP_YN:
            i = i || menuYN_input(&mMain->yesNo, 0);
            break;

        case MODE_SOUND:
            i = i || (menuSndSelPanel_input(&mMain->sndSel, 0) != false);
            break;

        default:
            i = i || menuMainPanel_input(panel, 0);
            i = i || menuNameSelPanel_input(&mMain->nameSel);
            i = i || menuCont_input(&mMain->cont, 0);
            i = i || menuNameOpPanel_input(&mMain->nameOp, 0);
            break;
    }

    if (i == 0) {
        return;
    }

    panelDir = nameSelDir = wndDir = kasaDir = contDir = ynDir = mesDir = nameDir = sndSelDir = 0;
    sound = SND_INDEX_INVALID;

    switch (mMain->mode) {
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
            select = 0;
            break;

        case MODE_CONT:
            select = 0;
            break;

        case MODE_NAME_DEL_MES:
        case MODE_BACKUP_MES:
            select = 0;
            break;

        case MODE_NAME:
            select = mMain->nameOp.select;
            break;

        case MODE_SOUND:
            select = mMain->sndSel.select;
            break;

        case MODE_NAME_DEL_YN:
        case MODE_BACKUP_YN:
            select = mMain->yesNo.select;
            break;

        default:
            select = mMain->select[mMain->depth] = panel->select;
            break;
    }

    switch (mMain->mode) {
        case MODE_MAIN:
            if (trg & (A_BUTTON | START_BUTTON)) {
                switch (tbl_5517[select]) {
                    case MODE_PLAY2:
                        evs_playmax = joyResponseCheck();
                        if (evs_playmax < 2) {
                            menuMes_setStr(&mMain->message, _mesNoCont2);
                            mesDir++;
                            sound = SND_INDEX_71;
                        } else {
                            mMain->mode = tbl_5517[select];
                            mMain->depth++;
                            mMain->select[mMain->depth] = 0;
                            panelDir++;
                            sound = SND_INDEX_62;
                        }
                        break;

                    default:
                        mMain->mode = tbl_5517[select];
                        mMain->depth++;
                        mMain->select[mMain->depth] = 0;
                        panelDir++;
                        sound = SND_INDEX_62;
                        break;
                }

                if (mesDir == 0) {
                    mesDir--;
                }
            } else if (trg & B_BUTTON) {
                if (mMain->message.miBase.colorStep < 0.0f) {
                    _setFadeDir(mMain->global, 1);
                    _setNextMain(mMain->global, MAIN_TITLE);
                    sound = SND_INDEX_68;
                }
                mesDir--;
            } else if (trg != 0) {
                mesDir--;
            }
            break;

        case MODE_PLAY1:
            mMain->screenDir = GMD_FLASH;
            mMain->screenNo = _n_5535[select];

            if (trg & (A_BUTTON | START_BUTTON)) {
                mMain->screenDir = -1;
                mMain->mode = _mode_5538[select];

                switch (mMain->mode) {
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

                switch (mMain->mode) {
                    case MODE_STORY_NS:
                        evs_playcnt = 2;
                        evs_story_flg = 1;
                        evs_gamesel = GSL_VSCPU;

                        game_state_data[0].player_type = PLAYERTYPE_0;
                        game_state_data[1].player_type = PLAYERTYPE_1;
                        nameSelDir++;
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
                        nameSelDir++;
                        break;

                    case MODE_VSCOM_NS:
                    case MODE_VSCOM_FL_NS:
                        evs_playcnt = 2;
                        evs_story_flg = 0;
                        evs_gamesel = GSL_VSCPU;

                        game_state_data[0].player_type = PLAYERTYPE_0;
                        game_state_data[1].player_type = PLAYERTYPE_1;
                        nameSelDir++;
                        break;

                    default:
                        break;
                }

                panelDir++;
                sound = SND_INDEX_62;
            } else if (trg & B_BUTTON) {
                mMain->screenDir = -1;
                mMain->mode = MODE_MAIN;
                mMain->depth--;
                panelDir++;
                sound = SND_INDEX_68;
            }
            break;

        case MODE_PLAY2:
            mMain->screenNo = select + 6;
            mMain->screenDir = GMD_FLASH;

            if (trg & (A_BUTTON | START_BUTTON)) {
                mMain->screenDir = -1;
                mMain->mode = mode_5557[select];
                evs_playcnt = 2;
                evs_story_flg = 0;
                evs_gamesel = GSL_2PLAY;

                game_state_data[0].player_type = PLAYERTYPE_0;
                game_state_data[1].player_type = PLAYERTYPE_0;

                nameSelDir++;
                panelDir++;
                sound = SND_INDEX_62;

                switch (mMain->mode) {
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
            } else if (trg & B_BUTTON) {
                mMain->screenDir = -1;
                mMain->mode = MODE_MAIN;
                mMain->depth--;
                panelDir++;
                sound = SND_INDEX_68;
            }
            break;

        case MODE_PLAY4:
            mMain->screenNo = select + 0xC;
            mMain->screenDir = GMD_FLASH;

            if (trg & (A_BUTTON | START_BUTTON)) {
                evs_playmax = joyResponseCheck();

                if (select < evs_playmax) {
                    mMain->mode = _mode_5570[select];
                    mMain->screenDir = -1;
                    mMain->depth++;
                    mMain->select[mMain->depth] = 0;
                    evs_playcnt = 4;
                    evs_story_flg = 0;
                    evs_gamesel = GSL_4PLAY;
                    evs_gamemode = GMD_NORMAL;

                    for (i = 0; i < ARRAY_COUNT(game_state_data); i++) {
                        game_state_data[i].player_type = select < i ? PLAYERTYPE_1 : PLAYERTYPE_0;
                    }

                    panelDir++;
                    mesDir--;
                    sound = SND_INDEX_62;
                } else {
                    menuMes_setStr(&mMain->message, mes_5577[select - 1]);
                    mesDir++;
                    sound = SND_INDEX_71;
                }
            } else if (trg & B_BUTTON) {
                if (mMain->message.miBase.colorStep < 0.0f) {
                    mMain->screenDir = -1;
                    mMain->mode = MODE_MAIN;
                    mMain->depth--;
                    panelDir++;
                    sound = SND_INDEX_68;
                }
                mesDir--;
            } else if (trg != 0) {
                mesDir--;
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
            if (mMain->nameSel.flow > 0) {
                MainMenuMode mode;
                s32 var_s4;

                for (i = 0; i < mMain->nameSel.playerCount; i++) {
                    evs_select_name_no[i] = mMain->nameSel.select[i];
                }

                for (i = 0; i < ARRAY_COUNT(evs_select_name_no); i++) {
                    flow[i] = 0;
                    if (evs_select_name_no[i] != 8) {
                        flow[i] = 1;
                        if (!(evs_mem_data[evs_select_name_no[i]].mem_use_flg & MEM_USE_FLG_1)) {
                            flow[i] = 2;
                        }
                    }
                }

                var_s4 = MAX(flow[0], flow[1]);

                switch (mMain->mode) {
                    case MODE_STORY_NS:
                        mode = _tbl_5598[var_s4][0];
                        break;

                    case MODE_NAME_NS:
                        mode = _tbl_5598[var_s4][1];
                        break;

                    case MODE_LVSEL_NS:
                        mode = _tblLS_5599[var_s4][0];
                        break;

                    case MODE_LVSEL_TQ_NS:
                        mode = _tblLS_5599[var_s4][1];
                        break;

                    case MODE_LVSEL_TA_NS:
                        mode = _tblLS_5599[var_s4][2];
                        break;

                    case MODE_VSMAN_NS:
                        mode = _tblVM_5600[var_s4][0];
                        break;

                    case MODE_VSMAN_FL_NS:
                        mode = _tblVM_5600[var_s4][1];
                        break;

                    case MODE_VSMAN_TA_NS:
                        mode = _tblVM_5600[var_s4][2];
                        break;

                    case MODE_VSCOM_NS:
                        mode = _tblVC_5601[var_s4][0];
                        break;

                    case MODE_VSCOM_FL_NS:
                        mode = _tblVC_5601[var_s4][1];
                        break;

                    default:
                        break;
                }

                switch (mode) {
                    case MODE_OPTION:
                        mMain->mode = MODE_OPTION;
                        panelDir++;
                        nameSelDir--;
                        sound = SND_INDEX_68;
                        break;

                    case MODE_NAME:
                        mMain->mode = MODE_NAME;
                        mMain->nameOp.select = 0;
                        nameSelDir--;
                        nameDir++;
                        sound = SND_INDEX_62;
                        break;

                    default:
                        _setMode(mMain->global, mode);
                        panelDir++;
                        nameSelDir--;
                        wndDir--;
                        kasaDir--;
                        sound = SND_INDEX_62;
                        break;
                }

            } else if (mMain->nameSel.flow < 0) {
                switch (mMain->mode) {
                    case MODE_STORY_NS:
                    case MODE_LVSEL_NS:
                    case MODE_LVSEL_TQ_NS:
                    case MODE_LVSEL_TA_NS:
                    case MODE_VSCOM_NS:
                    case MODE_VSCOM_FL_NS:
                        mMain->mode = MODE_PLAY1;
                        break;

                    case MODE_VSMAN_NS:
                    case MODE_VSMAN_FL_NS:
                    case MODE_VSMAN_TA_NS:
                        mMain->mode = MODE_PLAY2;
                        break;

                    case MODE_NAME_NS:
                        mMain->mode = MODE_OPTION;
                        break;

                    default:
                        break;
                }

                panelDir++;
                nameSelDir--;
                sound = SND_INDEX_68;
            }
            break;

        case MODE_OPTION:
            if (trg & (A_BUTTON | START_BUTTON)) {
                mMain->mode = tbl_5648[select];
                switch (mMain->mode) {
                    case MODE_NAME_NS:
                        panelDir++;
                        nameSelDir++;
                        sound = SND_INDEX_62;
                        break;

                    case MODE_RECORD_MS:
                    case MODE_TUTORIAL:
                    case MODE_BACKUP:
                    case MODE_MISC:
                        mMain->depth++;
                        mMain->select[mMain->depth] = 0;
                        panelDir++;
                        sound = SND_INDEX_62;
                        break;

                    default:
                        break;
                }

                switch (mMain->mode) {
                    case MODE_RECORD_MS:
                        dm_seq_play_fade(SEQ_INDEX_13, 0x14);
                        break;

                    case MODE_COUNT:
                        mMain->select[mMain->depth] = 3 - evs_vs_count;
                        break;

                    default:
                        break;
                }
            } else if (trg & B_BUTTON) {
                mMain->mode = MODE_MAIN;
                mMain->depth--;
                panelDir++;
                sound = SND_INDEX_68;
            }
            break;

        case MODE_MISC:
            if (trg & (A_BUTTON | START_BUTTON)) {
                mMain->mode = tbl_5664[select];

                // switch?
                switch (mMain->mode) {
                    case MODE_SOUND:
                        mMain->sndSel.select = evs_stereo == 0;
                        panelDir++;
                        sndSelDir++;
                        sound = SND_INDEX_62;
                        break;

                    case MODE_COUNT:
                    case MODE_SCORE:
                        mMain->depth++;
                        mMain->select[mMain->depth] = 0;
                        panelDir++;
                        sound = SND_INDEX_62;
                        break;

                    default:
                        break;
                }

                switch (mMain->mode) {
                    case MODE_COUNT:
                        mMain->select[mMain->depth] = 3 - evs_vs_count;
                        break;
                    case MODE_SCORE:
                        mMain->select[mMain->depth] = evs_score_flag == 0;
                        break;

                    default:
                        break;
                }
            } else if (trg & B_BUTTON) {
                _eepWritePlayer(mMain->global);
                mMain->mode = MODE_OPTION;
                mMain->depth--;
                panelDir++;
                sound = SND_INDEX_68;
            }
            break;

        case MODE_SCORE:
            if (trg & (A_BUTTON | START_BUTTON)) {
                evs_score_flag = select == 0;
                mMain->mode = MODE_MISC;
                mMain->depth--;
                panelDir++;
                sound = SND_INDEX_62;
            } else if (trg & B_BUTTON) {
                mMain->mode = MODE_MISC;
                mMain->depth--;
                panelDir++;
                sound = SND_INDEX_68;
            }
            break;

        case MODE_PLAY4_TYPE1:
        case MODE_PLAY4_TYPE2:
        case MODE_PLAY4_TYPE3:
        case MODE_PLAY4_TYPE4:
            mMain->screenNo = select + 9;
            mMain->screenDir = GMD_FLASH;
            if (trg & (A_BUTTON | START_BUTTON)) {
                for (i = 0; i < ARRAY_COUNTU(_team_5687[select]); i++) {
                    game_state_data[i].team_no = _team_5687[select][i];
                }

                evs_gamemode = _game_5689[select];
                panelDir++;
                wndDir--;
                kasaDir--;
                sound = SND_INDEX_62;
                mMain->screenDir = -1;
                _setMode(mMain->global, _mode_5688[select]);
            } else if (trg & B_BUTTON) {
                mMain->screenDir = -1;
                mMain->mode = MODE_PLAY4;
                mMain->depth--;
                panelDir++;
                sound = SND_INDEX_68;
            }
            break;

        case MODE_RECORD_MS:
            if (trg & (A_BUTTON | START_BUTTON)) {
                mMain->mode = _mode_5701[select];
                mMain->depth++;
                mMain->select[mMain->depth] = 0;
                panelDir++;
                sound = SND_INDEX_62;
            } else if (trg & B_BUTTON) {
                mMain->mode = MODE_OPTION;
                mMain->depth--;
                panelDir++;
                sound = SND_INDEX_68;
                dm_seq_play_fade(SEQ_INDEX_12, 0x14);
            }
            break;

        case MODE_RECORD_PLAY1:
        case MODE_RECORD_PLAY2:
            if (trg & (A_BUTTON | START_BUTTON)) {
                const MainMenuMode *modes;

                if (mMain->mode == MODE_RECORD_PLAY1) {
                    modes = _mode1_5709;
                } else {
                    modes = _mode2_5710;
                }
                _setMode(mMain->global, modes[select]);
                panelDir++;
                wndDir--;
                kasaDir--;
                sound = SND_INDEX_62;
            } else if (trg & B_BUTTON) {
                mMain->mode = MODE_RECORD_MS;
                mMain->depth--;
                panelDir++;
                sound = SND_INDEX_68;
            }
            break;

        case MODE_TUTORIAL:
            if (trg & (A_BUTTON | START_BUTTON)) {
                if (select == 0) {
                    mMain->mode = MODE_CONT;
                    panelDir++;
                    wndDir--;
                    contDir++;
                    sound = SND_INDEX_62;
                } else {
                    _setFadeDir(mMain->global, 1);
                    _setNextMain(mMain->global, MAIN_MANUAL);
                    evs_manual_no = select - 1;
                    sound = SND_INDEX_62;
                }
            } else if (trg & B_BUTTON) {
                mMain->mode = MODE_OPTION;
                mMain->depth--;
                panelDir++;
                sound = SND_INDEX_68;
            }
            break;

        case MODE_COUNT:
            if (trg & (A_BUTTON | START_BUTTON)) {
                evs_vs_count = 3 - select;
                mMain->mode = MODE_MISC;
                mMain->depth--;
                panelDir++;
                sndSelDir--;
                sound = SND_INDEX_62;
            } else if (trg & B_BUTTON) {
                mMain->mode = MODE_MISC;
                mMain->depth--;
                panelDir++;
                sound = SND_INDEX_68;
            }
            break;

        case MODE_CONT:
            menuCont_setFade(&mMain->cont, 1, mMain->cont.miLabel[0].colorTime);
            if (trg & B_BUTTON) {
                mMain->mode = MODE_TUTORIAL;
                panelDir++;
                wndDir++;
                contDir--;
                sound = SND_INDEX_68;
            }
            break;

        case MODE_NAME:
            if (trg & (A_BUTTON | START_BUTTON)) {
                switch (tbl_5735[select]) {
                    case MODE_NAME_NE2:
                        _setMode(mMain->global, MODE_NAME_NE2);
                        panelDir++;
                        wndDir--;
                        kasaDir--;
                        nameDir--;
                        sound = SND_INDEX_62;
                        break;

                    case MODE_NAME_DEL_YN:
                        mMain->mode = MODE_NAME_DEL_YN;
                        mMain->nameOp.cursor.flags.finger = false;
                        mMain->yesNo.select = 0;
                        ynDir++;
                        sound = SND_INDEX_62;
                        break;

                    default:
                        break;
                }
            } else if (trg & B_BUTTON) {
                mMain->mode = MODE_NAME_NS;
                nameSelDir++;
                nameDir--;
                sound = SND_INDEX_68;
            }
            break;

        case MODE_SOUND:
            if (trg & (A_BUTTON | START_BUTTON)) {
                switch (select) {
                    case 0:
                    case 1:
                        evs_stereo = select == 0 ? true : false;
                        dm_audio_set_stereo(evs_stereo);
                        mMain->mode = MODE_MISC;
                        panelDir++;
                        sndSelDir--;
                        sound = SND_INDEX_62;
                        if (mMain->playSeqNo != SEQ_INDEX_12) {
                            dm_seq_play_fade(SEQ_INDEX_12, 0x14);
                            mMain->playSeqNo = SEQ_INDEX_12;
                        }
                        break;

                    case 0x2:
                        dm_seq_play_fade(mMain->sndSel.bgmNo, 0x14);
                        mMain->playSeqNo = mMain->sndSel.bgmNo;
                        break;

                    case 0x3:
                        dm_snd_play(mMain->sndSel.sndNo);
                        break;
                }
            } else if (trg & B_BUTTON) {
                mMain->mode = MODE_MISC;
                panelDir++;
                sndSelDir--;
                sound = SND_INDEX_68;
                if (mMain->playSeqNo != SEQ_INDEX_12) {
                    dm_seq_play_fade(SEQ_INDEX_12, 0x14);
                    mMain->playSeqNo = SEQ_INDEX_12;
                }
            }
            break;

        case MODE_NAME_DEL_YN:
            mMain->yesNo.cursor.flags.finger = true;
            if (trg & (A_BUTTON | START_BUTTON)) {
                switch (select) {
                    case 0x0:
                        mMain->mode = MODE_NAME_NS;
                        nameDir--;
                        nameSelDir++;
                        ynDir--;
                        sound = SND_INDEX_68;
                        break;

                    case 0x1:
                        dm_init_save_mem(&evs_mem_data[evs_select_name_no[0]]);
                        _eepErasePlayer(mMain->global);
                        mMain->mode = MODE_NAME_DEL_MES;
                        mMain->yesNo.cursor.flags.finger = false;
                        sound = SND_INDEX_70;
                        break;
                }
            } else if (trg & B_BUTTON) {
                mMain->mode = MODE_NAME;
                mMain->nameOp.cursor.flags.finger = true;
                ynDir--;
            }
            break;

        case MODE_NAME_DEL_MES:
            if (trg & ANY_BUTTON) {
                mMain->mode = MODE_NAME_NS;
                nameDir--;
                nameSelDir++;
                ynDir--;
                sound = SND_INDEX_62;
            }
            break;

        case MODE_BACKUP:
            panel->cursor.flags.finger = true;
            if (trg & (A_BUTTON | START_BUTTON)) {
                switch (select) {
                    case 0x0:
                        mMain->mode = MODE_OPTION;
                        mMain->depth--;
                        panelDir++;
                        sound = SND_INDEX_68;
                        break;

                    case 0x1:
                        mMain->mode = MODE_BACKUP_YN;
                        mMain->yesNo.select = 0;
                        panel->cursor.flags.finger = false;
                        ynDir++;
                        sound = SND_INDEX_62;
                        break;
                }
            } else if (trg & B_BUTTON) {
                mMain->mode = MODE_OPTION;
                mMain->depth--;
                panelDir++;
                sound = SND_INDEX_68;
            }
            break;

        case MODE_BACKUP_YN:
            mMain->yesNo.cursor.flags.finger = true;
            if (trg & (A_BUTTON | START_BUTTON)) {
                switch (select) {
                    case 0x0:
                        mMain->mode = MODE_OPTION;
                        mMain->depth--;
                        ynDir--;
                        panelDir++;
                        sound = SND_INDEX_68;
                        break;

                    case 0x1:
                        _eepEraseData(mMain->global);
                        mMain->mode = MODE_BACKUP_MES;
                        mMain->yesNo.cursor.flags.finger = false;
                        sound = SND_INDEX_70;
                        break;
                }
            } else if (trg & B_BUTTON) {
                mMain->mode = MODE_BACKUP;
                ynDir--;
                sound = SND_INDEX_68;
            }
            break;
        case MODE_BACKUP_MES:
            if (trg & ANY_BUTTON) {
                mMain->mode = MODE_OPTION;
                mMain->depth--;
                ynDir--;
                panelDir++;
                sound = SND_INDEX_62;
            }
            break;

        default:
            break;
    }

    if (wndDir != 0) {
        menuItem_setTransDir(&mMain->miMsgWnd, wndDir);
    }
    if (kasaDir != 0) {
        menuItem_setTransDir(&mMain->miKaSaMaRu, kasaDir);
    }
    if (ynDir != 0) {
        menuYN_setFadeDir(&mMain->yesNo, ynDir);
    }
    if (mesDir != 0) {
        menuMes_setFadeDir(&mMain->message, mesDir);
    }
    if (contDir < 0) {
        menuCont_setFade(&mMain->cont, -1, 1.0f);
        menuCont_setFrame(&mMain->cont, -1, mMain->cont.miBase.transTime);
    }
    if (nameDir < 0) {
        menuNameOpPanel_setFrame(&mMain->nameOp, -1, 1.0f);
    }
    if (nameSelDir < 0) {
        menuNameSelPanel_setFrame(&mMain->nameSel, -1, mMain->nameSel.miBase.transTime);
    }
    if (sndSelDir < 0) {
        menuSndSelPanel_setFrame(&mMain->sndSel, -1, mMain->sndSel.miBase.transTime);
    }
    if (panelDir != 0) {
        menuMainPanel_setFrame(panel, -1, panel->miBase.transTime);
        mMain->current ^= 1;
        panel = &mMain->panel[mMain->current];
    }

    if (mMain->mode != _menuMain_lastMode) {
        if (contDir > 0) {
            menuCont_setFrame(&mMain->cont, 1, mMain->cont.miBase.transTime);
        } else if (nameDir > 0) {
            bcopy(evs_mem_data[evs_select_name_no[0]].mem_name, mMain->nameOp.name, MENUNAMEOPPANEL_NAME_LEN);
            menuNameOpPanel_setFrame(&mMain->nameOp, 1, 0.0f);
        } else if (sndSelDir > 0) {
            menuSndSelPanel_setFrame(&mMain->sndSel, 1, mMain->sndSel.miBase.transTime);
        } else if (nameSelDir > 0) {
            s32 playerCount = 1;
            f32 time = mMain->nameSel.miBase.transTime;

            switch (mMain->mode) {
                case MODE_VSMAN_NS:
                case MODE_VSMAN_FL_NS:
                case MODE_VSMAN_TA_NS:
                    playerCount = 2;
                    break;

                default:
                    break;
            }

            menuNameSelPanel_clear(&mMain->nameSel, mMain->mode != MODE_NAME_NS, playerCount);
            menuNameSelPanel_setFrame(&mMain->nameSel, 1, time);
        } else if (panelDir != 0) {
            f32 time = panel->miBase.transTime;

            menuMain_initPanel(mMain, mMain->mode, mMain->current, mMain->select[mMain->depth]);
            menuMainPanel_setFrame(panel, 1, time);
        }
    }

    _menuMain_lastMode = mMain->mode;
    _menuMain_lastDepth = mMain->depth;
    for (i = 0; i < ARRAY_COUNTU(_menuMain_lastSelect); i++) {
        _menuMain_lastSelect[i] = mMain->select[i];
    }

    SND_PLAY_INDEX(sound);
}

/**
 * Original name: menuMain_update
 */
void menuMain_update(MenuMain *mMain) {
    MenuMainPanel *panel = &mMain->panel[mMain->current];
    SMenuItem *miRoot = _getRootItem(mMain->global);
    SMenuItem *item;
    s32 i;

    for (i = 0; i < ARRAY_COUNTU(mMain->panel); i++) {
        menuMainPanel_update(&mMain->panel[i], miRoot);
    }

    menuNameSelPanel_update(&mMain->nameSel, miRoot);
    menuNameOpPanel_update(&mMain->nameOp, miRoot);
    menuSndSelPanel_update(&mMain->sndSel, miRoot);
    menuItem_update(&mMain->miMsgWnd, miRoot);

    item = &mMain->miMsgWnd;
    mMain->msgWnd.posX = item->trans[0] + item->scale[0] * 6;
    mMain->msgWnd.posY = item->trans[1] + item->scale[1] * 6;

    if (!menuMain_setMsgStr(mMain, mMain->mode, mMain->select[mMain->depth])) {
        msgWnd_update(&mMain->msgWnd);
    }

    menuItem_update(&mMain->miKaSaMaRu, miRoot);
    menuItem_setTransDir(&mMain->miScrWnd, mMain->screenDir);
    menuItem_setScaleDir(&mMain->miScrWnd, mMain->screenDir);
    menuItem_update(&mMain->miScrWnd, &mMain->miKaSaMaRu);
    menuItem_update(&mMain->miSmoke, &mMain->miScrWnd);
    menuItem_update(&mMain->miScreen, &mMain->miScrWnd);

    for (i = 0; i < ARRAY_COUNTU(mMain->miScreen.color); i++) {
        mMain->miScreen.color[i] = miRoot->color[i];
    }

    menuCont_update(&mMain->cont, miRoot);

    mMain->kasaCount = WrapF(0.0f, 1.0f, mMain->kasaCount + DOUBLE_LITERAL(1.0 / 128));

    menuYN_update(&mMain->yesNo, miRoot);
    menuMes_update(&mMain->message, miRoot);
    mMain->nameOp.cursor.flags.blink = true;
    panel->cursor.flags.blink = true;

    switch (mMain->mode) {
        case MODE_NAME_DEL_YN:
        case MODE_NAME_DEL_MES:
            mMain->nameOp.cursor.flags.blink = false;
            break;

        case MODE_BACKUP_YN:
        case MODE_BACKUP_MES:
            panel->cursor.flags.blink = false;
            break;

        default:
            break;
    }

    switch (mMain->mode) {
        case MODE_NAME_DEL_MES:
        case MODE_BACKUP_MES:
            mMain->yesNo.cursor.flags.blink = false;
            break;

        default:
            break;
    }
}

const s32 _pat_6137[] = {
    0, 1, 2, 3, 2, 1,
};

/**
 * Original name: menuMain_update
 */
void menuMain_drawKaSaMaRu(MenuMain *mMain, Gfx **gfxP) {
    Gfx *gfx = *gfxP;
    Mtx *mtx = *_getMtxPtr(mMain->global);
    Vtx *vtx = *_getVtxPtr(mMain->global);
    SMenuItem *item;
    TiTexData *texC;
    TiTexData *texA;
    s32 i;
    s32 width;
    s32 height;
    s32 size;
    f32 mfRot[4][4];
    f32 amp = mMain->miScrWnd.scaleTime * 3.0f;
    f32 angle[3];

    for (i = 0; i < ARRAY_COUNTU(angle); i++) {
        angle[i] = WrapF(0.0f, 1.0f, mMain->kasaCount - (i * DOUBLE_LITERAL(0.125))) * DOUBLE_LITERAL(M_PI) * 2;
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

    guRotateRPYF(mfRot, 0.0f, 0.0f, sinf(angle[0]) * (1.0f - mMain->miScrWnd.scaleTime) * 4.0f);

    i = WrapI(0, 6, mMain->kasaCount * 6.0f * 12.0f);
    if (!msgWnd_isSpeaking(&mMain->msgWnd)) {
        i = 0;
    }

    item = &mMain->miKaSaMaRu;

    texC = _getTexKasa(mMain->global, _pat_6137[i] + 1);
    texA = _getTexKasa(mMain->global, 0);

    width = MIN(texC->info[TI_INFO_IDX_WIDTH], texA->info[TI_INFO_IDX_WIDTH]);
    height = MIN(texC->info[TI_INFO_IDX_HEIGHT], texA->info[TI_INFO_IDX_HEIGHT]);

    if (!menuItem_outOfScreen(item, width, height)) {
        gSPDisplayList(gfx++, fade_alpha_texture_init_dl);

        menuItem_setPrim(item, &gfx);
        mfRot[3][0] = item->trans[0];
        mfRot[3][1] = item->trans[1] + (sinf(angle[0]) * amp);
        guMtxF2L(mfRot, mtx);

        gSPMatrix(gfx++, mtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        mtx++;

        RectAlphaTexTile(&gfx, &vtx, width, height, texC->texs[TI_TEX_TEX], texC->info[TI_INFO_IDX_WIDTH],
                         texA->texs[TI_TEX_TEX], texA->info[TI_INFO_IDX_WIDTH], 0, 0, width, height, 0.0f, 0.0f, width,
                         height);
    }

    item = &mMain->miScreen;
    if (mMain->screenNo < 0xC) {
        texC = _getTexMain(mMain->global, 0);
        i = mMain->screenNo;
        size = 12;
    } else {
#if VERSION_CN
        goto end;
#else
        texC = _getTexMain(mMain->global, 8);
        i = mMain->screenNo - 0xC;
        size = 4;
#endif
    }

    width = texC->info[TI_INFO_IDX_WIDTH];
    height = texC->info[TI_INFO_IDX_HEIGHT] / size;

    if (!menuItem_outOfScreen(item, texC->info[TI_INFO_IDX_WIDTH], texC->info[TI_INFO_IDX_HEIGHT])) {
        gSPDisplayList(gfx++, fade_normal_texture_init_dl);

        menuItem_setPrim(item, &gfx);
        mfRot[3][0] = item->trans[0];
        mfRot[3][1] = item->trans[1] + sinf(angle[2]) * amp;
        guMtxF2L(mfRot, mtx);

        gSPMatrix(gfx++, mtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        mtx++;

        RectTexTile8(&gfx, &vtx, texC->info[TI_INFO_IDX_WIDTH], texC->info[TI_INFO_IDX_HEIGHT], texC->texs[TI_TEX_TLUT],
                     (u8 *)texC->texs[TI_TEX_TEX] + (width * height * i), 0, 0, width, height, 0, 0,
                     width * item->scale[0], height * item->scale[1]);
    }

    gSPDisplayList(gfx++, fade_intensity_texture_init_dl);

    for (i = 0; i < ARRAY_COUNT(angle) - 1; i++) {
        s32 gapW;
        s32 gapH;

        switch (i) {
            case 0:
                item = &mMain->miSmoke;
                texC = _getTexMain(mMain->global, 10);
                gapW = 0;
                gapH = 0;
                break;

            case 1:
                item = &mMain->miScrWnd;
                texC = _getTexMain(mMain->global, 9);
                gapW = 0;
                gapH = 0;
                break;
        }

        if (!menuItem_outOfScreen(item, texC->info[TI_INFO_IDX_WIDTH], texC->info[TI_INFO_IDX_HEIGHT])) {
            menuItem_setPrim(item, &gfx);
            mfRot[3][0] = item->trans[0];
            mfRot[3][1] = item->trans[1] + (sinf(angle[i + 1]) * amp);
            guMtxF2L(mfRot, mtx);

            gSPMatrix(gfx++, mtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            mtx++;

            RectTexTile4i(&gfx, &vtx, texC->info[TI_INFO_IDX_WIDTH], texC->info[TI_INFO_IDX_HEIGHT],
                          texC->texs[TI_TEX_TEX], 0, 0, texC->info[TI_INFO_IDX_WIDTH], texC->info[TI_INFO_IDX_HEIGHT],
                          0, 0, (texC->info[TI_INFO_IDX_WIDTH] + gapW) * item->scale[0],
                          (texC->info[TI_INFO_IDX_HEIGHT] + gapH) * item->scale[1]);
        }
    }

#if VERSION_CN
end:
#endif

    *_getVtxPtr(mMain->global) = vtx;
    *_getMtxPtr(mMain->global) = mtx;

    *gfxP = gfx;
}

/**
 * Original name: menuMain_draw
 */
void menuMain_draw(MenuMain *mMain, Gfx **gfxP) {
    Gfx *gfx = *gfxP;
    TiTexData *texC;
    s32 i;

    gSPDisplayList(gfx++, fade_normal_texture_init_dl);

    texC = _getTexMain(mMain->global, 6);
    menuItem_drawTex(&mMain->miMsgWnd, &gfx, texC, 0);
    if (!menuItem_outOfScreen(&mMain->miMsgWnd, mMain->msgWnd.colStep * mMain->msgWnd.colSize,
                              mMain->msgWnd.rowStep * mMain->msgWnd.rowSize)) {
        msgWnd_draw(&mMain->msgWnd, &gfx);
    }

    menuNameOpPanel_draw(&mMain->nameOp, &gfx);
    menuNameSelPanel_draw(&mMain->nameSel, &gfx);
    menuSndSelPanel_draw(&mMain->sndSel, &gfx);

    for (i = 0; i < ARRAY_COUNTU(mMain->panel); i++) {
        menuMainPanel_draw(&mMain->panel[i], &gfx);
    }

    menuMain_drawKaSaMaRu(mMain, &gfx);
    menuCont_draw(&mMain->cont, &gfx);
    menuYN_draw(&mMain->yesNo, &gfx);
    menuMes_draw(&mMain->message, &gfx);

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

/**
 * Original name: menuStory_getCharPos
 */
void menuStory_getCharPos(s32 charNo, s32 stageNo, s32 plane, s32 *x, s32 *y) {
    s32 i = 0;

    switch (plane) {
        case 0:
            i = CLAMP(stageNo, 1, 4);
            break;

        case 1:
            i = CLAMP(stageNo, 5, 9);
            break;
    }

    i--;

    *x = _pos_6413[charNo][i][0];
    *y = _pos_6413[charNo][i][1];
}

/**
 * Original name: menuStory_setFrame
 */
void menuStory_setFrame(MenuStory *story, s32 dir, f32 time) {
    SMenuItem *item = &story->miBase;

    item->transTime = time;
    item->transStep = 0.05f;
    item->transRange[0][1] = item->transRange[1][1] - 240.0f;
    menuItem_setTransDir(item, dir);
}

/**
 * Original name: _menuStory_loadAnime
 */
void _menuStory_loadAnime(void *arg) {
    MenuStory *story = arg;
    CharAnimeMode i;

    for (i = 0; i < ARRAY_COUNTU(story->animeAddr); i++) {
        void *heap = story->animeAddr[i];

        animeState_load(&story->animeState[i], &heap, i);
    }

    story->loaded = true;
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

/**
 * Original name: menuStory_init
 */
void menuStory_init(MenuStory *story, struct_watchMenu *global, void **heapP) {
    void *heap = *heapP;
    struct_evs_mem_data *mc = &evs_mem_data[evs_select_name_no[0]];
    struct_evs_mem_data_config *cfg = &mc->config;
    s32 i;
    CharAnimeMode animeMode;
    SMenuItem *item;

    story->global = global;

    for (i = 0; i < ARRAY_COUNTU(story->stageMax); i++) {
        story->stageMax[i][0] = mc->clear_stage[i][0] + 1;
        story->stageMax[i][1] = mc->clear_stage[i][1] + 1;
    }

    story->depth = 0;
    story->select[0] = cfg->st_no;
    story->loaded = false;
    menuItem_init(&story->miBase, 25, 47);
    story->select[0] = cfg->st_no;
    menuItem_init(&story->miCharName, 69, 18);

    for (i = 0; i < ARRAY_COUNTU(story->miChar); i++) {
        menuItem_init(&story->miChar[i], _posChar_6445[i][0], _posChar_6445[i][1]);
    }

    for (animeMode = CHARANIMEMODE_M; animeMode < ARRAY_COUNTU(story->animeAddr); animeMode++) {
        size_t size;

        story->animeAddr[animeMode] = ALIGN_PTR(heap);
        size = animeState_getDataSize(animeMode);
        heap = story->animeAddr[animeMode] + size;
    }

    BgTasksManager_SendTask(_menuStory_loadAnime, story);

    for (i = 0; i < ARRAY_COUNTU(story->charCursor); i++) {
        menuCursor_init(&story->charCursor[i], global, CURSOR_ITEM, 0, _posChar_6445[i][0] - 0x18,
                        _posChar_6445[i][1] - 0x2C, 0x30, 0x2F);
    }

    story->select[1] = cfg->st_lv;
    menuSpeedAsk_init(&story->speedAsk, global, 3, cfg->st_lv, 0x45, 0x3D);
    menuSpeedItem_init(&story->speedItem, global, 3, 0, cfg->st_lv, 0x7D, 0x39, 0x34);
    story->speedItem.flags.special = cfg->st_sh != 0;

    story->select[2] = cfg->st_st + 1;
    menuNumber_init(&story->stageNum, global, 1, 1, cfg->st_st + 1, 0x65, 0x5A);
    menuItem_init(&story->miStageBase, 0x10, 0x6E);

    for (i = 0; i < ARRAY_COUNTU(story->miStageBg); i++) {
        item = &story->miStageBg[i];

        menuItem_init(item, 0, 0);
        menuItem_setColor_fade(item);
        item->colorStep = 0.05f;
    }

    for (i = 0; i < ARRAY_COUNTU(story->miBgCursor); i++) {
        menuItem_init(&story->miBgCursor[i], _posBgCursor_6446[i][0], _posBgCursor_6446[i][1]);
        menuItem_setColor_cursor(&story->miBgCursor[i]);
    }

    for (i = 0; i < ARRAY_COUNTU(story->miWalk); i++) {
        s32 x;
        s32 y;

        menuStory_getCharPos(story->select[0], story->select[2], i, &x, &y);
        menuItem_init(&story->miWalk[i], x, y);
    }

    item = &story->miBgCursor[0];
    item->scaleRange[0][0] = -item->scaleRange[0][0];
    item->scaleRange[1][0] = -item->scaleRange[1][0];

    for (i = 0; i < ARRAY_COUNTU(story->cursor); i++) {
        menuCursor_init(&story->cursor[i], global, CURSOR_PANEL, 0, _cursor_6447[i][0], _cursor_6447[i][1],
                        _cursor_6447[i][2], _cursor_6447[i][3]);
    }

    menuStory_setFrame(story, 1, 0.0f);
    *heapP = heap;
}

/**
 * Original name: menuStory_waitCancel
 */
void menuStory_waitCancel(MenuStory *story) {
    u32 trg = _getKeyTrg(story->global, 0);

    if (trg & B_BUTTON) {
        _setFadeDir(story->global, -1);
        _setNextMain(story->global, MAIN_MENU);
        dm_snd_play(SND_INDEX_68);
    }
}

/**
 * Original name: menuStory_getLevel
 */
s32 menuStory_getLevel(MenuStory *story) {
    s32 level = story->speedItem.select;

    if (level == 2) {
        level += story->speedItem.flags.special;
    }
    return level;
}

/**
 * Original name: menuStory_getStageMax
 */
s32 menuStory_getStageMax(MenuStory *story) {
    s32 level = menuStory_getLevel(story);

    return story->stageMax[level][story->select[0]];
}

/**
 * Original name: menuStory_input
 */
void menuStory_input(MenuStory *story) {
    struct_evs_mem_data_config *cfg = &evs_mem_data[evs_select_name_no[0]].config;
    u32 rep = _getKeyRep(story->global, 0);
    u32 trg = _getKeyTrg(story->global, 0);
    SndIndex sound = SND_INDEX_INVALID;
    bool special = false;
    s32 vec;
    s32 select;
    long i;

    if (story->miBase.transTime != DOUBLE_LITERAL(1)) {
        return;
    }

    vec = 0;
    if ((rep & U_JPAD) || (trg & B_BUTTON)) {
        vec--;
    }
    if ((rep & D_JPAD) || (trg & (A_BUTTON | START_BUTTON))) {
        vec++;
    }

    select = CLAMP(story->depth + vec, 0, 2U);

    if (select != story->depth) {
        sound = SND_INDEX_64;
        story->depth = select;
    }

    if (trg & Z_TRIG) {
        if (story->depth == 1) {
            if (story->speedItem.select == 2) {
                if (!story->speedItem.flags.special) {
                    story->speedItem.flags.special = true;
                    special = true;
                } else {
                    story->speedItem.flags.special = false;
                    sound = SND_INDEX_62;
                }
            }
        }
    }

    vec = 0;
    if (rep & L_JPAD) {
        vec--;
    }
    if (rep & R_JPAD) {
        vec++;
    }

    switch (story->depth) {
        case 0x0:
            select = CLAMP(story->select[story->depth] + vec, 0, 1);

            if (select != story->select[story->depth]) {
                sound = SND_INDEX_63;
                story->select[story->depth] = select;
            }
            break;

        case 0x1:
            menuSpeedItem_input(&story->speedItem, 0);
            story->select[story->depth] = story->speedItem.select;
            break;

        case 0x2:
            i = menuStory_getStageMax(story);
            select = CLAMP(story->select[story->depth] + vec, 1, i);

            if (select != story->select[story->depth]) {
                sound = SND_INDEX_63;
                story->select[story->depth] = select;

                for (i = 0; i < ARRAY_COUNTU(story->miWalk); i++) {
                    SMenuItem *item = &story->miWalk[i];

                    item->transTime = 0.0f;
                    item->transRange[0][0] = item->transRange[1][0];
                    item->transRange[0][1] = item->transRange[1][1];
                }
            }
            break;
    }

    i = menuStory_getStageMax(story);
    story->select[2] = CLAMP(story->select[2], 1, i);

    if (sound <= SND_INDEX_INVALID) {
        if ((trg & (A_BUTTON | START_BUTTON)) && (story->depth == 2)) {
            _setFadeDir(story->global, 1);
            _setNextMain(story->global, MAIN_STORY);

            cfg->st_lv = story->speedItem.select;
            cfg->st_sh = story->speedItem.flags.special;
            cfg->st_st = story->stageNum.number - 1;
            cfg->st_no = story->select[0];

            evs_story_level = menuStory_getLevel(story);

            evs_story_no = story->stageNum.number;

            i = (evs_story_no > 1) ? 1 : 0;
            game_state_data[0].game_retry = i;
            evs_one_game_flg = i;

            story_proc_no = story->stageNum.number;
            if (story->select[0] == 1) {
                story_proc_no += 0xC;
            }

            evs_high_score = 0xDD18;
            evs_game_time = 0;

            if (evs_story_level < 3) {
                for (i = 0; i < ARRAY_COUNT(evs_mem_data); i++) {
                    evs_high_score = MAX(evs_high_score, evs_mem_data[i].story_data[evs_story_level].score);
                }
            }

            sound = SND_INDEX_62;
        } else if ((trg & B_BUTTON) && (story->depth == 0)) {
            _setMode(story->global, MODE_MAIN);
            menuStory_setFrame(story, -1, 1.0f);
            sound = SND_INDEX_68;
        }
    }

    if (special) {
        dm_snd_play_strange_sound();
    } else {
        SND_PLAY_INDEX(sound);
    }
}

// unused
const s32 RO_800B0A50[] = {
    0,
    6,
    2,
};

/**
 * Original name: menuStory_update
 */
void menuStory_update(MenuStory *story) {
    SMenuItem *miRoot = _getRootItem(story->global);
    MenuCursor *cursor;
    SMenuItem *item;
    s32 i;
    s32 j;

    story->speedAsk.select = menuStory_getLevel(story);
    story->stageNum.number = story->select[2];

    menuItem_update(&story->miBase, miRoot);

    for (i = 0; i < ARRAY_COUNTU(story->miChar); i++) {
        menuItem_setColorDir(&story->miChar[i], (i == story->select[0]) ? 1 : -1);
    }

    menuItem_update(&story->miCharName, &story->miBase);
    menuItem_updateN(story->miChar, ARRAY_COUNTU(story->miChar), &story->miBase);

    for (i = 0; i < ARRAY_COUNTU(story->animeState); i++) {
        if (!story->loaded) {
            continue;
        }

        animeState_update(&story->animeState[i]);

        for (j = 0; j < MENUITEM_COLOR_COUNT; j++) {
            story->animeState[i].primColor[j] = story->miChar[0].color[j] * 255.0f;
        }
    }

    for (i = 0; i < ARRAY_COUNTU(story->charCursor); i++) {
        cursor = &story->charCursor[i];

        menuCursor_update(cursor, &story->miBase);
    }

    if (story->depth != 1) {
        story->speedItem.cursor.miBase.colorTime = 1.0f;
    }

    menuSpeedAsk_update(&story->speedAsk, &story->miBase);
    menuSpeedItem_update(&story->speedItem, &story->miBase);
    menuNumber_update(&story->stageNum, &story->miBase);

    menuItem_update(&story->miStageBase, &story->miBase);

    i = (story->select[2] >= 5) ? -1 : 1;

    menuItem_setColorDir(&story->miStageBg[0], i);
    menuItem_setColorDir(&story->miStageBg[1], -i);
    menuItem_updateN(story->miStageBg, ARRAY_COUNTU(story->miStageBg), &story->miStageBase);

    for (i = 0; i < MENUSTORY_UNK_LEN_2; i++) {
        s32 x;
        s32 y;

        menuStory_getCharPos(story->select[0], story->select[2], i, &x, &y);

        item = &story->miWalk[i];
        menuItem_setTransHi(item, x, y);
        menuItem_update(item, &story->miStageBg[i]);
    }

    menuItem_updateN(story->miBgCursor, ARRAY_COUNTU(story->miBgCursor), &story->miStageBase);

    item = story->miBgCursor;
    i = menuStory_getStageMax(story);
    if ((story->select[2] > 4) || (i < 5)) {
        item[1].color[3] = 0.0f;
    }
    if (story->select[2] < 5) {
        item[0].color[3] = 0.0f;
    }

    for (i = 0; i < ARRAY_COUNTU(story->cursor); i++) {
        cursor = &story->cursor[i];

        menuCursor_update(cursor, &story->miBase);
    }

    j = story->depth == 0;
    for (i = 0; i < ARRAY_COUNTU(story->charCursor); i++) {
        story->cursor[0].flags.cursor = j;
        story->charCursor[i].flags.blink = j;
        story->charCursor[story->select[0]].flags.finger = j && (i == story->select[0]);
    }

    j = story->depth == 1;
    story->speedItem.flags.blink = j;
    story->cursor[1].flags.cursor = j;
    story->speedItem.cursor.flags.finger = j;

    j = (story->depth == 2);
    story->cursor[2].flags.cursor = j;

    if (story->depth == 2) {
        return;
    }

    for (i = 0; i < ARRAY_COUNTU(story->miBgCursor); i++) {
        //! @bug/typo? It seems likely that this should be &story->miBgCursor[i] instead
        item = story->miBgCursor;

        for (j = 0; j < MENUITEM_COLOR_COUNT - 1; j++) {
            item->color[j] = item->colorRange[1][j] * miRoot->color[j];
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

/**
 * Original name: menuStory_draw
 */
void menuStory_draw(MenuStory *story, Gfx **gfxP) {
    Gfx *gfx = *gfxP;
    SMenuItem *item;
    void *list[3];
    s32 pad[3] UNUSED;
    s32 cached;
    s32 i;
    TiTexData *texC;
    TiTexData *texA;

    gSPDisplayList(gfx++, fade_normal_texture_init_dl);

    texC = _getTexStory(story->global, 6);
    menuItem_drawTex(&story->miBase, &gfx, texC, 0);

    for (i = 0; i < MENUSTORY_UNK_LEN; i++) {
        f32 x;
        f32 y;

        if (!story->loaded) {
            continue;
        }

        item = &story->miChar[i];

        x = item->trans[0];
        y = item->trans[1];
        item->trans[0] -= 26.0f;
        item->trans[1] -= 48.0f;

        if (!menuItem_outOfScreen(item, 0x40, 0x40)) {
            s32 alpha = item->colorTime * 255.0f;

            gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, alpha);

            gSPDisplayList(gfx++, fade_intensity_texture_init_dl);

            texC = _getTexStory(story->global, 0xC);
            tiStretchTexTile(&gfx, texC, false, 0, 0, texC->info[TI_INFO_IDX_WIDTH], texC->info[TI_INFO_IDX_HEIGHT],
                             item->trans[0], item->trans[1], texC->info[TI_INFO_IDX_WIDTH],
                             texC->info[TI_INFO_IDX_HEIGHT]);

            item->trans[0] = x + 5.0f;
            item->trans[1] = y + 2.0f;

            gSPDisplayList(gfx++, fade_shadow_texture_init_dl);

            gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, alpha >> 1);

            animeState_draw(&story->animeState[i], &gfx, item->trans[0], item->trans[1], 1.0f, 1.0f);
            item->trans[0] = x;
            item->trans[1] = y;

            gSPDisplayList(gfx++, fade_normal_texture_init_dl);

            menuItem_setPrim(item, &gfx);
            animeState_draw(&story->animeState[i], &gfx, item->trans[0], item->trans[1], 1.0f, 1.0f);
        }

        item->trans[0] = x;
        item->trans[1] = y;
    }

    gSPDisplayList(gfx++, fade_normal_texture_init_dl);
    gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);

    for (i = 0; i < ARRAY_COUNTU(story->miStageBg); i++) {
        texC = _getTexStory(story->global, _map_6928[story->select[0]][i]);
        menuItem_drawTex(&story->miStageBg[i], &gfx, texC, 0);
    }

    gSPDisplayList(gfx++, fade_intensity_texture_init_dl);

    for (i = 0; i < MENUSTORY_UNK_LEN_2; i++) {
        s32 x;
        s32 w;
        s32 tempIndex;

        item = &story->miStageBg[i];

        texC = _getTexStory(story->global, _cover_6929[story->select[0]][i]);

        tempIndex = menuStory_getStageMax(story);

        x = _filter_6930[story->select[0]][i][tempIndex - 1];
        x = MIN(x, texC->info[TI_INFO_IDX_WIDTH] - 1);

        w = texC->info[TI_INFO_IDX_WIDTH] - x;
        if (!menuItem_outOfScreen(item, w, texC->info[TI_INFO_IDX_HEIGHT])) {
            gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, item->color[3] * 127.0f);

            tiStretchTexTile(&gfx, texC, false, x, 0, w, texC->info[TI_INFO_IDX_HEIGHT], item->trans[0] + x,
                             item->trans[1], w, texC->info[TI_INFO_IDX_HEIGHT]);
        }
    }

    gSPDisplayList(gfx++, fade_normal_texture_init_dl);
    gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);

    for (i = 0; i < ARRAY_COUNTU(story->miWalk); i++) {
        texC = _getTexStory(story->global, _wchar_6931[story->select[0]]);
        menuItem_drawTex(&story->miWalk[i], &gfx, texC, 0);
    }

    gDPSetRenderMode(gfx++, G_RM_OPA_SURF, G_RM_OPA_SURF2);

    texC = _getTexStory(story->global, 5);
    cached = 0;
    for (i = 0; i < ARRAY_COUNTU(story->miBgCursor); i++) {
        cached += menuItem_drawTex(&story->miBgCursor[i], &gfx, texC, cached);
    }

    list[0] = &story->stageNum;
    menuNumber_draw((void *)list, 1, &gfx);

    list[0] = &story->speedAsk;
    menuSpeedAsk_draw((void *)list, 1, &gfx);

    list[0] = &story->speedItem;
    menuSpeedItem_draw1((void *)list, 1, &gfx);

    gSPDisplayList(gfx++, fade_alpha_texture_init_dl);

    texC = _getTexStory(story->global, 1);
    texA = _getTexStory(story->global, 0);
    menuItem_drawAlphaItem(&story->miCharName, &gfx, texC, texA, false, 2, story->select[0]);

    for (i = 0; i < ARRAY_COUNTU(story->cursor); i++) {
        list[i] = &story->cursor[i];
    }

    menuCursor_draw((void *)list, ARRAY_COUNTU(story->cursor), &gfx);

    list[0] = &story->speedItem;
    menuSpeedItem_draw2((void *)list, 1, &gfx);

    *gfxP = gfx;
}

/**
 * Original name: menuLvSel_setFrame
 */
void menuLvSel_setFrame(MenuLvSel *lvSel, s32 dir, f32 time) {
    SMenuItem *item = &lvSel->miBase;

    item->transTime = time;
    item->transStep = 0.05f;
    item->transRange[0][1] = item->transRange[1][1] - SCREEN_HEIGHT;
    menuItem_setTransDir(item, dir);
}

const s32 _cursor_7325[][4] = {
    { 0, 0, 0x10E, 0x22 },
    { 0, 0x1F, 0x10E, 0x22 },
    { 0, 0x3E, 0x10E, 0x1E },
};
static_assert(ARRAY_COUNT(_cursor_7325) == MENULVSEL_UNK_162C_LEN, "");

/**
 * Original name: menuLvSel_init
 */
void menuLvSel_init(MenuLvSel *lvSel, struct_watchMenu *global, void **heapP) {
    struct_evs_mem_data *mc = &evs_mem_data[evs_select_name_no[0]];
    void *heap = *heapP;
    struct_evs_mem_data_config *cfg = &mc->config;
    s32 i;

    lvSel->global = global;

    lvSel->mode = _getMode(global);
    lvSel->depth = 0;
    lvSel->levelMax = 20;

    for (i = 0; i < ARRAY_COUNTU(mc->level_data); i++) {
        lvSel->levelMax = MAX(lvSel->levelMax, mc->level_data[i].c_level);
    }

    lvSel->levelMax = MIN(21, lvSel->levelMax);

    menuItem_init(&lvSel->miBase, 0x19, 0x2F);
    menuItem_init(lvSel->miPanel, 0, 0);
    menuItem_init(&lvSel->miPanel[1], 0, 0x5F);

    switch (lvSel->mode) {
        case MODE_LVSEL_TQ:
            menuSpeedAsk_init(&lvSel->glvAsk, global, 3, cfg->p1_tq_lv, 0x44, 9);
            menuSpeedItem_init(&lvSel->glvItem, global, 3, 0, cfg->p1_tq_lv, 0x82, 5, 0x2E);
            break;

        case MODE_LVSEL_TA:
            menuSpeedAsk_init(&lvSel->glvAsk, global, 3, cfg->p1_ta_lv, 0x44, 9);
            menuSpeedItem_init(&lvSel->glvItem, global, 3, 0, cfg->p1_ta_lv, 0x82, 5, 0x2E);
            break;

        case MODE_LVSEL:
            if (cfg->p1_lv <= lvSel->levelMax) {
                i = cfg->p1_lv;
            } else {
                i = lvSel->levelMax;
            }

            menuNumber_init(&lvSel->lvNum, global, 1, 2, i, 0x59, 5);
            menuLvGauge_init(&lvSel->lvGauge, global, 2, 0, i, 0x99, 0xF);
            menuItem_setColorLow(&lvSel->lvGauge.miBase, 1.0f, 0.5f);
            lvSel->lvGauge.levelMax = lvSel->levelMax;
            break;

        default:
            break;
    }

    menuSpeedAsk_init(&lvSel->speedAsk, global, 1, cfg->p1_sp, 0x44, 0x28);
    menuSpeedItem_init(&lvSel->speedItem, global, 1, 0, cfg->p1_sp, 0x82, 0x24, 0x2E);

    menuItem_setColorLow(&lvSel->speedItem.miBase, 1.0f, 0.5f);
    menuMusicItem_init(&lvSel->musicItem, global, cfg->p1_m, 0x46, 0x46);
    menuBottle_init(&lvSel->bottle, global, 0x19, 7);

    for (i = 0; i < ARRAY_COUNTU(lvSel->cursor); i++) {
        menuCursor_init(&lvSel->cursor[i], global, CURSOR_PANEL, 0, _cursor_7325[i][0], _cursor_7325[i][1],
                        _cursor_7325[i][2], _cursor_7325[i][3]);
    }

    menuItem_init(&lvSel->miCapsule, 0x56, 7);
    menuItem_init(&lvSel->miMusic, 0x99, 8);
    menuLvSel_setFrame(lvSel, 1, 0.0f);

    *heapP = heap;
}

// unused
const s32 RO_800B0B44[] = {
    3,
    1,
    4,
};

/**
 * Original name: menuLvSel_waitCancel
 */
void menuLvSel_waitCancel(MenuLvSel *lvSel) {
    u32 trg = _getKeyTrg(lvSel->global, 0);

    if (trg & B_BUTTON) {
        _setFadeDir(lvSel->global, -1);
        _setNextMain(lvSel->global, MAIN_MENU);
        dm_snd_play(SND_INDEX_68);
    }
}

/**
 * Original name: menuLvSel_input
 */
void menuLvSel_input(MenuLvSel *lvSel) {
    struct_evs_mem_data_config *cfg = &evs_mem_data[evs_select_name_no[0]].config;
    u32 rep = _getKeyRep(lvSel->global, 0);
    SndIndex sound = SND_INDEX_INVALID;
    struct_game_state_data *state = &game_state_data[0];
    u32 trg = _getKeyTrg(lvSel->global, 0);
    s32 select;
    s32 vec;

    if ((lvSel->miBase.transStep < 0.0f) || (lvSel->miBase.transTime < 1.0f)) {
        return;
    }

    vec = 0;
    if ((rep & U_JPAD) || (trg & B_BUTTON)) {
        vec--;
    }
    if ((rep & D_JPAD) || (trg & (A_BUTTON | START_BUTTON))) {
        vec++;
    }

    select = CLAMP(lvSel->depth + vec, 0, 2);
    if (select != lvSel->depth) {
        sound = SND_INDEX_64;
        lvSel->depth = select;
    }

    switch (lvSel->depth) {
        case 0x0:
            switch (lvSel->mode) {
                case MODE_LVSEL_TQ:
                case MODE_LVSEL_TA:
                    menuSpeedItem_input(&lvSel->glvItem, 0);
                    break;

                case MODE_LVSEL:
                    menuLvGauge_input(&lvSel->lvGauge, 0);
                    break;

                default:
                    break;
            }
            break;

        case 0x1:
            menuSpeedItem_input(&lvSel->speedItem, 0);
            break;

        case 0x2:
            menuMusicItem_input(&lvSel->musicItem, 0);
            break;
    }

    if (sound >= SND_INDEX_INVALID + 1) {
        dm_snd_play(sound);
        return;
    }

    if ((trg & (A_BUTTON | START_BUTTON)) && (lvSel->depth == 2)) {
        _setFadeDir(lvSel->global, 1);
        _setNextMain(lvSel->global, MAIN_12);

        switch (lvSel->mode) {
            case MODE_LVSEL:
                state->virus_level = lvSel->lvGauge.level;
                state->cap_def_speed = lvSel->speedItem.select;
                cfg->p1_lv = lvSel->lvGauge.level;
                break;

            case MODE_LVSEL_TQ:
                state->virus_level = 0xA;
                state->cap_def_speed = lvSel->speedItem.select;
                state->game_level = lvSel->glvItem.select;
                cfg->p1_tq_lv = lvSel->glvItem.select;
                break;

            case MODE_LVSEL_TA:
                state->virus_level = _timeAttack_levelTable[lvSel->glvItem.select];
                state->cap_def_speed = lvSel->speedItem.select;
                state->game_level = lvSel->glvItem.select;
                cfg->p1_ta_lv = lvSel->glvItem.select;
                break;

            default:
                break;
        }

        cfg->p1_sp = lvSel->speedItem.select;
        cfg->p1_m = lvSel->musicItem.select;

        evs_seqnumb = lvSel->musicItem.select;
        evs_game_time = 0;
        evs_seqence = evs_seqnumb != 4;
        sound = SND_INDEX_62;
    } else if ((trg & B_BUTTON) && (lvSel->depth == 0)) {
        _setMode(lvSel->global, MODE_MAIN);
        menuLvSel_setFrame(lvSel, -1, 1.0f);
        if (lvSel->musicItem.playNo >= 0) {
            dm_seq_play_fade(0xC, 0x14);
        }
        sound = SND_INDEX_68;
    }

    SND_PLAY_INDEX(sound);
}

/**
 * Original name: menuLvSel_input
 */
void menuLvSel_update(MenuLvSel *lvSel) {
    SMenuItem *miRoot = _getRootItem(lvSel->global);
    s32 i;

    switch (lvSel->mode) {
        case MODE_LVSEL_TQ:
            lvSel->bottle.level = lvSel->mode;
            lvSel->glvAsk.select = lvSel->glvItem.select;
            break;

        case MODE_LVSEL_TA:
            lvSel->glvAsk.select = lvSel->glvItem.select;
            lvSel->bottle.level = _timeAttack_levelTable[lvSel->glvItem.select];
            break;

        case MODE_LVSEL:
            lvSel->lvNum.number = lvSel->lvGauge.level;
            lvSel->bottle.level = lvSel->lvGauge.level;
            break;

        default:
            break;
    }

    lvSel->speedAsk.select = lvSel->speedItem.select;
    menuItem_update(&lvSel->miBase, miRoot);
    menuItem_updateN(lvSel->miPanel, ARRAY_COUNT(lvSel->miPanel), &lvSel->miBase);

    switch (lvSel->mode) {
        case MODE_LVSEL_TQ:
        case MODE_LVSEL_TA:
            menuSpeedAsk_update(&lvSel->glvAsk, &lvSel->miBase);
            menuSpeedItem_update(&lvSel->glvItem, &lvSel->miBase);
            break;

        case MODE_LVSEL:
            menuNumber_update(&lvSel->lvNum, &lvSel->miBase);
            menuLvGauge_update(&lvSel->lvGauge, &lvSel->miBase);
            break;

        default:
            break;
    }

    menuSpeedAsk_update(&lvSel->speedAsk, &lvSel->miBase);
    menuSpeedItem_update(&lvSel->speedItem, &lvSel->miBase);
    menuMusicItem_update(&lvSel->musicItem, &lvSel->miBase);
    menuBottle_update(&lvSel->bottle, &lvSel->miPanel[1]);

    for (i = 0; i < ARRAY_COUNTU(lvSel->cursor); i++) {
        menuCursor_update(&lvSel->cursor[i], &lvSel->miPanel[0]);
    }

    menuItem_update(&lvSel->miCapsule, &lvSel->miPanel[1]);
    menuItem_update(&lvSel->miMusic, &lvSel->miPanel[1]);

    i = lvSel->depth == 0;
    switch (lvSel->mode) {
        case MODE_LVSEL:
            lvSel->lvGauge.cursor.flags.finger = i;
            lvSel->lvGauge.cursor.flags.blink = i;
            break;

        case MODE_LVSEL_TQ:
        case MODE_LVSEL_TA:
            lvSel->glvItem.flags.blink = i;
            lvSel->glvItem.cursor.flags.finger = i;
            break;

        default:
            break;
    }
    lvSel->cursor[0].flags.cursor = i;

    i = lvSel->depth == 1;
    lvSel->speedItem.flags.blink = i;
    lvSel->speedItem.cursor.flags.finger = i;
    lvSel->cursor[1].flags.cursor = i;

    i = lvSel->depth == 2;
    lvSel->musicItem.cursor.flags.finger = i;
    lvSel->musicItem.flags.blink = i;
    lvSel->cursor[2].flags.cursor = i;
}

/**
 * Original name: menuLvSel_input
 */
void menuLvSel_draw(MenuLvSel *lvSel, Gfx **gfxP) {
    void *list[8];
    Gfx *gfx = *gfxP;
    s32 i;
    TiTexData *texC;

    gSPDisplayList(gfx++, fade_normal_texture_init_dl);

    switch (lvSel->mode) {
        case MODE_LVSEL:
            texC = _getTexLevel(lvSel->global, 4);
            break;

        case MODE_LVSEL_TQ:
        case MODE_LVSEL_TA:
            texC = _getTexLevel(lvSel->global, 5);
            break;

        default:
            UNREACHABLE;
            break;
    }

    menuItem_drawTex(&lvSel->miPanel[0], &gfx, texC, 0);
    menuItem_drawTex(&lvSel->miPanel[1], &gfx, _getTexLevel(lvSel->global, 1), 0);
    if (lvSel->speedItem.select > 0) {
        menuItem_drawItem(&lvSel->miCapsule, &gfx, _getTexLevel(lvSel->global, 3), 0, 2, lvSel->speedItem.select - 1);
    }
    if (lvSel->musicItem.select < 4) {
        menuItem_drawItem(&lvSel->miMusic, &gfx, _getTexLevel(lvSel->global, 2), 0, 4, lvSel->musicItem.select);
    }

    switch (lvSel->mode) {
        case MODE_LVSEL:
            if (lvSel->levelMax >= 21) {
                f32 x = lvSel->miPanel[0].trans[0];

                lvSel->miPanel[0].trans[0] = x + 222.0f;
                menuItem_drawTex(&lvSel->miPanel[0], &gfx, _getTexLevel(lvSel->global, 6), 0);
                lvSel->miPanel[0].trans[0] = x;
            }
            break;

        default:
            break;
    }

    list[0] = &lvSel->musicItem;
    menuMusicItem_draw1((MenuMusicItem **)&list[0], 1, &gfx);
    list[1] = &lvSel->speedAsk;
    list[2] = &lvSel->speedItem;
    menuSpeedAsk_draw((MenuSpeedAsk **)&list[1], 1, &gfx);
    menuSpeedItem_draw1((MenuSpeedItem **)&list[2], 1, &gfx);

    switch (lvSel->mode) {
        case MODE_LVSEL_TQ:
        case MODE_LVSEL_TA:
            list[3] = &lvSel->glvAsk;
            list[4] = &lvSel->glvItem;
            menuSpeedAsk_draw((MenuSpeedAsk **)&list[3], 1, &gfx);
            menuSpeedItem_draw1((MenuSpeedItem **)&list[4], 1, &gfx);
            break;

        case MODE_LVSEL:
            list[3] = &lvSel->lvNum;
            list[4] = &lvSel->lvGauge;
            menuNumber_draw((void *)&list[3], 1, &gfx);
            menuLvGauge_draw1((void *)&list[4], 1, &gfx);
            break;

        default:
            break;
    }

    for (i = 0; i < ARRAY_COUNTU(lvSel->cursor); i++) {
        list[5 + i] = &lvSel->cursor[i];
    }

    menuCursor_draw((MenuCursor **)&list[5], ARRAY_COUNTU(lvSel->cursor), &gfx);

    menuMusicItem_draw2((MenuMusicItem **)&list[0], 1, &gfx);
    menuSpeedItem_draw2((MenuSpeedItem **)&list[2], 1, &gfx);

    switch (lvSel->mode) {
        case MODE_LVSEL_TQ:
        case MODE_LVSEL_TA:
            menuSpeedItem_draw2((void *)&list[4], 1, &gfx);
            break;

        case MODE_LVSEL:
            menuLvGauge_draw2((void *)&list[4], 1, &gfx);
            break;

        default:
            break;
    }

    menuBottle_draw(&lvSel->bottle, &gfx);

    *gfxP = gfx;
}

/**
 * Original name: menuChSel_setFrame
 */
void menuChSel_setFrame(MenuChSel *chSel, s32 dir, f32 time) {
    SMenuItem *item = &chSel->miBase;

    item->transTime = time;
    item->transStep = 0.05f;
    item->transRange[0][1] = item->transRange[1][1] - SCREEN_HEIGHT;
    menuItem_setTransDir(item, dir);
}

const s32 _pos_7882[][2] = {
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
};

/**
 * Original name: menuChSel_init
 */
void menuChSel_init(MenuChSel *chSel, struct_watchMenu *global, void **heapP UNUSED) {
    MainMenuMode mode = _getMode(global);
    s32 i;

    chSel->global = global;
    chSel->subDepth = -1;
    chSel->hardFlag = false;
    chSel->hardMode = 0;
    chSel->comLvId = -1;
    chSel->comLvPn = -1;

    switch (mode) {
        case MODE_VSCOM_CH:
        case MODE_VSCOM_FL_CH:
        case MODE_VSMAN_CH:
        case MODE_VSMAN_FL_CH:
        case MODE_VSMAN_TA_CH:
            chSel->allCount = 2;
            break;

        case MODE_PLAY4_CH:
        case MODE_PLAY4_TB_CH:
        case MODE_PLAY4_FL_CH:
            chSel->allCount = 4;
            break;

        default:
            break;
    }

    chSel->playerCount = 0;
    chSel->cpuCount = 0;
    menuItem_init(&chSel->miHard, 0xF9, 0x16);
    menuItem_setColor_fade(&chSel->miHard);

    chSel->miHard.colorTime = 0.0f;

    for (i = 0; i < chSel->allCount; i++) {
        s32 var_s3;
        struct_evs_mem_data_config *temp;

        if (game_state_data[i].player_type == PLAYERTYPE_0) {
            chSel->playerTable[chSel->playerCount] = i;
            chSel->playerCount += 1;
            chSel->cpuFlag[i] = 0;
        } else {
            chSel->cpuTable[chSel->cpuCount] = i;
            chSel->cpuCount += 1;
            chSel->cpuFlag[i] = 1;
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

        chSel->select[i] = var_s3;
        chSel->depth[i] = -1;
    }

    for (i = 0; i < chSel->allCount; i++) {
        MenuCursor *cursor = &chSel->cursor[i];

        menuCursor_init2(cursor, global, CURSOR_ITEM, chSel->playerCount, chSel->cpuCount, i, 0, 0, 0x2C, 0x2C);
        cursor->miPlayer.transRange[0][0] = cursor->miPlayer.transRange[1][0] = _pos_7882[i][0];
        cursor->miPlayer.transRange[0][1] = cursor->miPlayer.transRange[1][1] = _pos_7882[i][1];
    }

    menuItem_init(&chSel->miBase, 0x12, 0x2F);

    for (i = 0; i < MENUCH_SEL_UNK_LEN; i++) {
        menuItem_init(&chSel->miChar[i], ((i % 5) * 0x36) + 0xC, ((i / 5) * 0x35) + 0xC);
        menuItem_init(&chSel->miCharFilt[i], 3, 3);
        menuItem_setColorHi(&chSel->miCharFilt[i], 0.0f, 0.0f);
        menuItem_setColorLow(&chSel->miCharFilt[i], 0.0f, 0.5f);
    }

    for (i = 0; i < ARRAY_COUNTU(chSel->comLv); i++) {
        menuComLvPanel_init(&chSel->comLv[i], global, 0, -6, 0x1E);
        menuComLvPanel_setFade(&chSel->comLv[i], -1, 0.0f);
    }

    menuChSel_setFrame(chSel, 1, 0.0f);
}

/**
 * Original name: menuChSel_checkSelected
 */
bool menuChSel_checkSelected(MenuChSel *chSel, s32 playerNo, s32 charNo, s32 depth) {
    s32 i;

    for (i = 0; i < chSel->allCount; i++) {
        if ((i != playerNo) && (chSel->select[i] == charNo)) {
            if (chSel->depth[i] >= depth) {
                return true;
            }
        }
    }

    return false;
}

/**
 * Original name: menuChSel_checkMoveable
 */
bool menuChSel_checkMoveable(MenuChSel *chSel, s32 playerNo, s32 charNo) {
    if (menuChSel_checkSelected(chSel, playerNo, charNo, 0)) {
        return true;
    }

    if ((charNo == 0xD) && (evs_secret_flg[1] == 0)) {
        return true;
    }

    if ((charNo == 0xE) && (evs_secret_flg[0] == 0)) {
        return true;
    }

    return false;
}

/**
 * Original name: menuChSel_input1
 */
void menuChSel_input1(MenuChSel *chSel, s32 playerNo, s32 contNo) {
    u32 rep = _getKeyRep(chSel->global, contNo);
    u32 trg = _getKeyTrg(chSel->global, contNo);
    SndIndex sound = SND_INDEX_INVALID;
    u32 lvl = _getKeyLvl(chSel->global, contNo);

    switch (chSel->depth[playerNo]) {
        case -0x1:
            chSel->depth[playerNo] = 0;

            FALLTHROUGH;
        case 0x0:
            while (menuChSel_checkMoveable(chSel, playerNo, chSel->select[playerNo])) {
                chSel->select[playerNo] = WrapI(0, 0xF, chSel->select[playerNo] + 1);
            }

            if (trg & (A_BUTTON | START_BUTTON)) {
                if ((lvl & L_TRIG) && (chSel->cpuCount != 0)) {
                    chSel->hardFlag = (!chSel->hardFlag || (chSel->hardMode != 1));
                    chSel->hardMode = 1;
                    sound = SND_INDEX_62;
                } else {
                    chSel->depth[playerNo]++;
                    sound = SND_INDEX_62;
                }
            } else if (trg & B_BUTTON) {
                if ((lvl & L_TRIG) && (chSel->cpuCount != 0)) {
                    chSel->hardFlag = (!chSel->hardFlag || (chSel->hardMode != 2));
                    chSel->hardMode = 2;
                    sound = SND_INDEX_62;
                } else {
                    chSel->depth[playerNo]--;
                    sound = SND_INDEX_68;
                }
            } else {
                s32 var_a2 = chSel->select[playerNo];
                s32 dy = 0;
                s32 dx = 0;

                if (rep & L_JPAD) {
                    dx--;
                }
                if (rep & R_JPAD) {
                    dx++;
                }

                if (rep & U_JPAD) {
                    dy--;
                }
                if (rep & D_JPAD) {
                    dy++;
                }

                if (((dx != 0) || (dy != 0))) {
                    s32 var_s2 = chSel->select[playerNo] % 5;
                    s32 var_s1 = chSel->select[playerNo] / 5;
                    s32 temp_s0;

                    do {
                        var_s2 = WrapI(0, 5, var_s2 + dx);
                        var_s1 = WrapI(0, 3, var_s1 + dy);
                        temp_s0 = var_s2 + (var_s1 * 5);
                    } while (menuChSel_checkMoveable(chSel, playerNo, temp_s0));
                    var_a2 = temp_s0;
                }

                if (var_a2 != chSel->select[playerNo]) {
                    chSel->select[playerNo] = var_a2;
                    sound = SND_INDEX_64;
                }
            }
            break;

        case 0x1:
            if (trg & B_BUTTON) {
                chSel->depth[playerNo] = 0;
                sound = SND_INDEX_68;
            }
            break;
    }

    SND_PLAY_INDEX(sound);
}

/**
 * Original name: menuChSel_inputMan
 */
void menuChSel_inputMan(MenuChSel *chSel) {
    s32 cancel = 0;
    s32 ok = 0;
    s32 i;

    for (i = 0; i < chSel->playerCount; i++) {
        menuChSel_input1(chSel, chSel->playerTable[i], chSel->playerTable[i]);

        switch (chSel->depth[chSel->playerTable[i]]) {
            case -1:
                cancel++;
                break;

            case 1:
                ok++;
                break;
        }
    }

    if (cancel != 0) {
        _setMode(chSel->global, MODE_MAIN);
        menuChSel_setFrame(chSel, -1, 1.0f);
        chSel->subDepth -= 1;
    }

    if (ok == chSel->playerCount) {
        chSel->subDepth += 1;
    }
}

/**
 * Original name: menuChSel_inputCom
 */
void menuChSel_inputCom(MenuChSel *chSel) {
    s32 temp_s2;
    s32 temp_s3;
    s32 i;
    s32 var_s5;

#if 0
    int pre; // r28
    int playerNo; // r27
    int select; // r26
#endif

    var_s5 = 0;
    for (i = 0; i < chSel->cpuCount; i++) {
        temp_s2 = chSel->cpuTable[i];
        temp_s3 = chSel->select[temp_s2];
        if (chSel->depth[temp_s2] == 1) {
            var_s5 = temp_s2;
            continue;
        }

        menuChSel_input1(chSel, temp_s2, 0);

        switch (chSel->depth[temp_s2]) {
            case -1:
                chSel->comLvId = -1;
                chSel->comLvPn = -1;
                chSel->depth[var_s5]--;
                chSel->subDepth--;
                break;

            case 0:
                chSel->comLvId = temp_s3;
                chSel->comLvPn = temp_s2;
                break;
        }
        break;
    }

    if (i == chSel->cpuCount) {
        chSel->subDepth++;
    }
}

const s32 _charTbl_8108[] = {
    0, 1, 3, 9, 2, 4, 7, 8, 5, 6, 0xA, 0xB, 0xC, 0xE, 0xD,
};

/**
 * Original name: menuChSel_input
 */
void menuChSel_input(MenuChSel *chSel) {
    MainMenuMode mode;
    struct_evs_mem_data_config *cfg;
    s32 think_level;
    s32 i;

    if ((chSel->miBase.transStep < 0.0f) || (chSel->miBase.transTime < 1.0f)) {
        return;
    }

    switch (chSel->subDepth) {
        case -0x1:
            chSel->subDepth = 0;
            FALLTHROUGH;

        case 0x0:
            menuChSel_inputMan(chSel);
            break;

        case 0x1:
            menuChSel_inputCom(chSel);
            break;
    }

    if (chSel->subDepth < 2) {
        return;
    }

    think_level = THINKLEVEL_0;
    if (chSel->hardFlag) {
        think_level = chSel->hardMode;
    }

    switch (_getMode(chSel->global)) {
        case MODE_VSCOM_CH:
        case MODE_VSCOM_FL_CH:
            cfg = &evs_mem_data[evs_select_name_no[0]].config;
            for (i = 0; i < chSel->allCount; i++) {
                cfg->vc_no[i] = chSel->select[i];
            }
            break;

        case MODE_VSMAN_CH:
        case MODE_VSMAN_FL_CH:
        case MODE_VSMAN_TA_CH:
            if (evs_select_name_no[0] == evs_select_name_no[1]) {
                evs_mem_data[0].config.vm_no = 0;
            } else {
                for (i = 0; i < chSel->allCount; i++) {
                    cfg = &evs_mem_data[evs_select_name_no[i]].config;

                    cfg->vm_no = chSel->select[i];
                }
            }
            break;

        case MODE_PLAY4_CH:
        case MODE_PLAY4_TB_CH:
        case MODE_PLAY4_FL_CH:
            for (i = 0; i < chSel->allCount; i++) {
                evs_cfg_4p.p4_no[i] = chSel->select[i];
            }
            break;

        default:
            break;
    }

    switch (_getMode(chSel->global)) {
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

    for (i = 0; i < chSel->allCount; i++) {
        struct_game_state_data *state = &game_state_data[i];

        state->charNo = _charTbl_8108[chSel->select[i]];
        state->think_level = think_level;
    }

    _setMode(chSel->global, mode);
    menuChSel_setFrame(chSel, -1, 1.0f);
}

const u8 _star_8183[] = {
    4, 4, 1, 1, 2, 2, 2, 2, 3, 3, 3, 4, 5, 5, 5,
};
static_assert(ARRAY_COUNT(_star_8183) == MENUCH_SEL_UNK_LEN, "");

/**
 * Original name: menuChSel_update
 */
void menuChSel_update(MenuChSel *chSel) {
    SMenuItem *miRoot = _getRootItem(chSel->global);
    s32 i;
    s32 var_a0;

    menuItem_update(&chSel->miBase, miRoot);

    switch (chSel->subDepth) {
        case 0:
        case 1:
            menuItem_setColorDir(&chSel->miHard, chSel->hardFlag ? 1 : -1);
            break;

        default:
            menuItem_setColorDir(&chSel->miHard, -1);
            break;
    }

    menuItem_update(&chSel->miHard, miRoot);

    menuItem_updateN(chSel->miChar, ARRAY_COUNTU(chSel->miChar), &chSel->miBase);

    for (i = 0; i < MENUCH_SEL_UNK_LEN; i++) {
        if (menuChSel_checkSelected(chSel, -1, i, 1)) {
            menuItem_setColorDir(&chSel->miCharFilt[i], -1);
        } else {
            menuItem_setColorDir(&chSel->miCharFilt[i], 1);
        }

        menuItem_update(&chSel->miCharFilt[i], &chSel->miChar[i]);
    }

    for (i = 0; i < MENUCH_SEL_UNK_LEN; i++) {
        var_a0 = _star_8183[i];
        if (chSel->hardFlag) {
            var_a0 += chSel->hardMode;
        }

        chSel->comLv[i].level = var_a0;
        menuComLvPanel_setFadeDir(&chSel->comLv[i], (i == chSel->comLvId) ? 1 : -1);
        menuComLvPanel_update(&chSel->comLv[i], &chSel->miChar[i]);
    }

    for (i = 0; i < chSel->allCount; i++) {
        MenuCursor *cursor = &chSel->cursor[i];

        menuCursor_update(cursor, &chSel->miChar[chSel->select[i]]);

        switch (chSel->depth[i]) {
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

/**
 * Original name: menuChSel_draw
 */
void menuChSel_draw(MenuChSel *chSel, Gfx **gfxP) {
    Gfx *gfx = *gfxP;
    void *list[MAX(ARRAY_COUNT(chSel->cursor), ARRAY_COUNT(chSel->comLv))];
    TiTexData *texC;
    SMenuItem *item;
    s32 i;

    gSPDisplayList(gfx++, fade_normal_texture_init_dl);

    texC = _getTexChar(chSel->global, 5);
    menuItem_drawTex(&chSel->miBase, &gfx, texC, 0);

    for (i = 0; i < ARRAY_COUNT(evs_secret_flg); i++) {
        if (evs_secret_flg[i]) {
            f32 x;
            f32 y;

            item = &chSel->miChar[14 - i];
            x = item->trans[0];
            y = item->trans[1];
            item->trans[0] += _pos_8298[i][0];
            item->trans[1] += _pos_8298[i][1];

            texC = _getTexChar(chSel->global, _tex_8297[i]);
            menuItem_drawTex(item, &gfx, texC, 0);
            item->trans[0] = x;
            item->trans[1] = y;
        }
    }

    gSPDisplayList(gfx++, fade_fillrect_init_dl);

    for (i = 0; i < ARRAY_COUNTU(chSel->miCharFilt); i++) {
        s32 x;
        s32 y;

        item = &chSel->miCharFilt[i];

        if (item->color[3] == 1.0f) {
            continue;
        }

        x = item->trans[0];
        y = item->trans[1];
        menuItem_setPrim(item, &gfx);

        gDPScisFillRectangle(gfx++, x, y, x + 38, y + 38);
    }

    for (i = 0; i < chSel->allCount; i++) {
        list[i] = &chSel->cursor[i];
    }

    menuCursor_draw((void *)list, chSel->allCount, &gfx);

    for (i = 0; i < ARRAY_COUNTU(chSel->comLv); i++) {
        list[i] = &chSel->comLv[i];
    }

    menuComLvPanel_draw((void *)list, ARRAY_COUNTU(chSel->comLv), &gfx);

    gSPDisplayList(gfx++, fade_normal_texture_init_dl);
    gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);

    if (chSel->hardMode > 0) {
        texC = _getTexChar(chSel->global, 2);
        menuItem_drawItem(&chSel->miHard, &gfx, texC, 0, 2, chSel->hardMode - 1);
    }

    *gfxP = gfx;
}

const s32 _moveTbl_8521[] = {
    SCREEN_WIDTH,
    -SCREEN_WIDTH,
};

/**
 * Original name: menuPlay2_setFrame
 */
void menuPlay2_setFrame(MenuPlay2 *play2, s32 dir, f32 time) {
    s32 i;

    for (i = 0; i < play2->panelCount; i++) {
        MenuPlay2Panel *temp_a0 = &play2->panel[i];
        SMenuItem *item = &temp_a0->miBase;

        item->transRange[0][0] = item->transRange[1][0] + _moveTbl_8521[i % ARRAY_COUNTU(_moveTbl_8521)];
        item->transStep = 0.05f;
        item->transTime = time;
        menuItem_setTransDir(item, dir);
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

/**
 * Original name: menuPlay2_init
 */
void menuPlay2_init(MenuPlay2 *play2, struct_watchMenu *global, void **heapP) {
    struct_evs_mem_data_config *cfg;
    struct_game_state_data *state;
    s32 backNo;
    s32 musicNo;
    s32 virusLevel;
    s32 i;

    play2->global = global;
    play2->master = -1;
    play2->depth = -1;

    switch (_getMode(play2->global)) {
        case MODE_VSMAN:
        case MODE_VSMAN_FL:
        case MODE_VSMAN_TA:
            cfg = &evs_mem_data[evs_select_name_no[0]].config;
            musicNo = cfg->vm_m;
            backNo = cfg->vm_st + 1;

            play2->playerCount = 2;
            play2->playerTable[0] = 0;
            play2->playerTable[1] = 1;
            play2->cpuCount = 0;
            play2->panelCount = 2;

            for (i = 0; i < play2->panelCount; i++) {
                cfg = &evs_mem_data[evs_select_name_no[i]].config;
                state = &game_state_data[i];

                switch (_getMode(play2->global)) {
                    case MODE_VSMAN:
                        virusLevel = cfg->vm_lv;
                        break;

                    case MODE_VSMAN_FL:
                        virusLevel = cfg->vm_fl_lv;
                        break;

                    case MODE_VSMAN_TA:
                        virusLevel = cfg->vm_ta_lv;
                        break;

                    default:
                        break;
                }

                menuPlay2Panel_init(&play2->panel[i], global, heapP, 1, play2->playerCount, play2->cpuCount, i,
                                    state->player_type == PLAYERTYPE_1, state->charNo, virusLevel, cfg->vm_sp,
                                    _panel2_8535[i][0], _panel2_8535[i][1]);
            }
            break;

        case MODE_VSCOM:
        case MODE_VSCOM_FL:
            cfg = &evs_mem_data[evs_select_name_no[0]].config;
            musicNo = cfg->vc_m;
            backNo = cfg->vc_st + 1;

            play2->playerCount = 1;
            play2->playerTable[0] = 0;
            play2->cpuCount = 1;
            play2->cpuTable[0] = 1;
            play2->panelCount = 2;

            for (i = 0; i < play2->panelCount; i++) {
                state = &game_state_data[i];

                switch (_getMode(play2->global)) {
                    case MODE_VSCOM:
                        virusLevel = cfg->vc_lv[i];
                        break;

                    case MODE_VSCOM_FL:
                        virusLevel = cfg->vc_fl_lv[i];
                        break;

                    default:
                        break;
                }

                menuPlay2Panel_init(&play2->panel[i], global, heapP, 1, play2->playerCount, play2->cpuCount, i,
                                    state->player_type == PLAYERTYPE_1, state->charNo, virusLevel, cfg->vc_sp[i],
                                    _panel2_8535[i][0], _panel2_8535[i][1]);
            }
            break;

        case MODE_PLAY4_LV:
        case MODE_PLAY4_TB_LV:
        case MODE_PLAY4_FL_LV:
            backNo = evs_cfg_4p.p4_st + 1;
            musicNo = evs_cfg_4p.p4_m;

            play2->playerCount = 0;
            play2->cpuCount = 0;
            play2->panelCount = 4;

            for (i = 0; i < play2->panelCount; i++) {
                state = &game_state_data[i];

                if (state->player_type == PLAYERTYPE_1) {
                    play2->cpuTable[play2->cpuCount] = i;
                    play2->cpuCount += 1;
                } else {
                    play2->playerTable[play2->playerCount] = i;
                    play2->playerCount += 1;
                }
            }

            for (i = 0; i < play2->panelCount; i++) {
                state = &game_state_data[i];
                switch (_getMode(play2->global)) {
                    case MODE_PLAY4_TB_LV:
                    case MODE_PLAY4_LV:
                        virusLevel = evs_cfg_4p.p4_lv[i];
                        break;

                    case MODE_PLAY4_FL_LV:
                        virusLevel = evs_cfg_4p.p4_fl_lv[i];
                        break;

                    default:
                        break;
                }

                menuPlay2Panel_init(&play2->panel[i], global, heapP, 0, play2->playerCount, play2->cpuCount, i,
                                    state->player_type == PLAYERTYPE_1, state->charNo, virusLevel, evs_cfg_4p.p4_sp[i],
                                    _panel4_8536[i][0], _panel4_8536[i][1]);
            }
            break;

        default:
            break;
    }

    i = play2->panelCount / 2 - 1;
    menuItem_init(&play2->miONaJi, _onaji_8534[i][0], _onaji_8534[i][1]);
    menuItem_setColor_fade(&play2->miONaJi);
    play2->miONaJi.colorTime = 0.0f;

    menuPlay2PanelSub_init(&play2->panelSub, global, heapP, backNo, musicNo, 0x19, 0x4B);
    menuPlay2_setFrame(play2, 1, 0);
}

/**
 * Original name: menuPlay2_waitCancel
 */
void menuPlay2_waitCancel(MenuPlay2 *play2) {
    u32 trg = _getKeyTrg(play2->global, 0);

    if (trg & B_BUTTON) {
        play2->depth = 2;
        play2->panelSub.flow = 0;
        _setFadeDir(play2->global, -1);
        _setNextMain(play2->global, MAIN_MENU);
        dm_snd_play(SND_INDEX_68);
    }
}

/**
 * Original name: menuPlay2_checkInputMaster
 */
bool menuPlay2_checkInputMaster(MenuPlay2 *play2, s32 playerNo, s32 contNo) {
    MenuPlay2Panel *panel = &play2->panel[playerNo];
    u32 key = _getKeyLvl(play2->global, contNo);

    return (key & R_TRIG) && (panel->flow == 0);
}

/**
 * Original name: menuPlay2_applyMasterConfig
 */
void menuPlay2_applyMasterConfig(MenuPlay2 *play2, s32 playerNo) {
    MenuPlay2Panel *master = &play2->panel[playerNo];
    s32 i;

    for (i = 0; i < play2->panelCount; i++) {
        MenuPlay2Panel *panel = &play2->panel[i];

        if (panel->flow <= 0) {
            menuPlay2Panel_copyConfig(panel, master);
        }
    }
}

/**
 * Original name: menuPlay2_applyMasterConfig
 */
void menuPlay2_applyMasterCursor(MenuPlay2 *menuPlay2, s32 arg1) {
    MenuPlay2Panel *master = &menuPlay2->panel[arg1];
    s32 i;

    for (i = 0; i < menuPlay2->panelCount; i++) {
        MenuPlay2Panel *panel = &menuPlay2->panel[i];

        if (panel->flow <= 0) {
            menuPlay2Panel_copyCursor(panel, master);
        }
    }
}

/**
 * Original name: menuPlay2_inputMan
 */
void menuPlay2_inputMan(MenuPlay2 *play2) {
    MenuPlay2Panel *panel;
    MainMenuMode mode;
    s32 playerNo;
    s32 i;
    s32 ok;
    s32 cancel;
    bool var_s7;

    if (play2->master >= 0) {
        if (!menuPlay2_checkInputMaster(play2, play2->master, play2->master)) {
            play2->master = -1;
        }
    }

    if (play2->master < 0) {
        for (i = 0; i < play2->playerCount; i++) {
            if (menuPlay2_checkInputMaster(play2, play2->playerTable[i], play2->playerTable[i])) {
                play2->master = play2->playerTable[i];
                break;
            }
        }
    }

    for (i = 0; i < play2->playerCount; i++) {
        playerNo = play2->playerTable[i];
        panel = &play2->panel[playerNo];

        if (playerNo == 0) {
            if (panel->flow == 1) {
                break;
            }
        } else if (panel->flow != 1) {
            break;
        }
    }

    var_s7 = (i == play2->playerCount) && (play2->cpuCount != 0);
    cancel = 0;

    ok = 0;
    for (i = 0; i < play2->playerCount; i++) {
        playerNo = play2->playerTable[i];
        panel = &play2->panel[playerNo];
        if ((play2->master < 0) || (play2->master == playerNo)) {
            s32 bottomFlag = !var_s7 || (playerNo != 0);

            menuPlay2Panel_input(panel, playerNo, true, bottomFlag);
        }

        switch (panel->flow) {
            case -0x1:
                cancel++;
                break;

            case 0x1:
                ok++;
                break;
        }
    }

    if (cancel) {
        switch (_getMode(play2->global)) {
            case MODE_VSMAN:
                mode = MODE_VSMAN_CH;
                break;

            case MODE_VSMAN_FL:
                mode = MODE_VSMAN_FL_CH;
                break;

            case MODE_VSMAN_TA:
                mode = MODE_VSMAN_TA_CH;
                break;

            case MODE_VSCOM:
                mode = MODE_VSCOM_CH;
                break;

            case MODE_VSCOM_FL:
                mode = MODE_VSCOM_FL_CH;
                break;

            case MODE_PLAY4_LV:
                mode = MODE_PLAY4_CH;
                break;

            case MODE_PLAY4_TB_LV:
                mode = MODE_PLAY4_TB_CH;
                break;

            case MODE_PLAY4_FL_LV:
                mode = MODE_PLAY4_FL_CH;
                break;

            default:
                break;
        }

        play2->depth--;
        _setMode(play2->global, mode);
        menuPlay2_setFrame(play2, -1, 1.0f);
    } else if (ok == play2->playerCount) {
        play2->depth++;
    }
}

/**
 * Original name: menuPlay2_inputCpu
 */
void menuPlay2_inputCpu(MenuPlay2 *play2) {
    s32 pre = 0;
    s32 i;

    play2->master = -1;

    for (i = 0; i < play2->cpuCount; i++) {
        s32 playerNo = play2->cpuTable[i];
        MenuPlay2Panel *panel = &play2->panel[playerNo];

        if (panel->flow == 1) {
            pre = playerNo;
            continue;
        }

        if (menuPlay2_checkInputMaster(play2, playerNo, 0) != 0) {
            play2->master = playerNo;
        }

        menuPlay2Panel_input(panel, 0, false, i == (play2->cpuCount - 1));
        if (panel->flow == -1) {
            play2->panel[pre].flow = panel->flow;
            if (pre == 0) {
                play2->depth--;
            }
        }
        break;
    }

    if (i == play2->cpuCount) {
        play2->depth++;
    }
}

/**
 * Original name: menuPlay2_input
 */
void menuPlay2_input(MenuPlay2 *play2) {
    struct_evs_mem_data_config *cfg;
    MenuPlay2Panel *panel;
    s32 i;

    if (play2->panel[0].miBase.transStep < 0.0f) {
        return;
    }

    if (play2->panel[0].miBase.transTime < 1.0f) {
        return;
    }

    if (play2->master >= 0) {
        u32 trg = _getKeyTrg(play2->global, play2->master);
        u32 lvl = _getKeyLvl(play2->global, play2->master);

        if ((lvl & R_TRIG) && (trg & (A_BUTTON | START_BUTTON))) {
            for (i = 0; i < play2->panelCount; i++) {
                panel = &play2->panel[i];

                panel->flow = 1;
            }
            SND_PLAY_INDEX(SND_INDEX_62);
        }
    }

    switch (play2->depth) {
        case -1:
            play2->depth = 0;
            FALLTHROUGH;

        case 0:
            menuPlay2PanelSub_setFrame(&play2->panelSub, -1, play2->panelSub.miBase.transTime);
            menuPlay2_inputMan(play2);
            break;

        case 1:
            menuPlay2PanelSub_setFrame(&play2->panelSub, -1, play2->panelSub.miBase.transTime);
            menuPlay2_inputCpu(play2);
            break;

        case 2:
            play2->master = -1;
            menuPlay2PanelSub_setFrame(&play2->panelSub, 1, play2->panelSub.miBase.transTime);
            if (menuPlay2PanelSub_input(&play2->panelSub, 0)) {
                switch (play2->panelSub.flow) {
                    case -1:
                        play2->depth -= 2;
                        for (i = 0; i < play2->panelCount; i++) {
                            play2->panel[i].flow = -1;
                            play2->panel[i].depth = 0;
                        }

                        if (play2->panelSub.musicItem.playNo >= 0) {
                            dm_seq_play_fade(SEQ_INDEX_12, 0x14);
                            play2->panelSub.musicItem.playNo = -1;
                        }
                        break;

                    case 1:
                        play2->depth++;
                        break;
                }
            }
            break;
    }

    if (play2->depth < 3) {
        return;
    }

    switch (_getMode(play2->global)) {
        case MODE_VSMAN:
        case MODE_VSMAN_FL:
        case MODE_VSMAN_TA:
            for (i = 0; i < play2->panelCount; i++) {
                panel = &play2->panel[i];
                cfg = &evs_mem_data[evs_select_name_no[i]].config;

                if (panel->flash) {
                    cfg->vm_fl_lv = panel->glvItem.select;
                } else if (panel->timeAt) {
                    cfg->vm_ta_lv = panel->glvItem.select;
                } else {
                    cfg->vm_lv = panel->lvGauge.level;
                }
                cfg->vm_sp = panel->speedItem.select;
                cfg->vm_st = play2->panelSub.stageNum.number - 1;
                cfg->vm_m = play2->panelSub.musicItem.select;
            }
            break;

        case MODE_VSCOM:
        case MODE_VSCOM_FL:
            cfg = &evs_mem_data[evs_select_name_no[0]].config;

            for (i = 0; i < play2->panelCount; i++) {
                panel = &play2->panel[i];

                if (panel->flash) {
                    cfg->vc_fl_lv[i] = panel->glvItem.select;
                } else {
                    cfg->vc_lv[i] = panel->lvGauge.level;
                }
                cfg->vc_sp[i] = panel->speedItem.select;
            }

            cfg->vc_st = play2->panelSub.stageNum.number - 1;
            cfg->vc_m = play2->panelSub.musicItem.select;
            break;

        default:
            break;

        case MODE_PLAY4_LV:
        case MODE_PLAY4_TB_LV:
        case MODE_PLAY4_FL_LV:
            for (i = 0; i < play2->panelCount; i++) {
                panel = &play2->panel[i];

                if (panel->flash) {
                    evs_cfg_4p.p4_fl_lv[i] = panel->glvItem.select;
                } else {
                    evs_cfg_4p.p4_lv[i] = panel->lvGauge.level;
                }
                evs_cfg_4p.p4_sp[i] = panel->speedItem.select;
            }

            evs_cfg_4p.p4_st = play2->panelSub.stageNum.number - 1;
            evs_cfg_4p.p4_m = play2->panelSub.musicItem.select;
            break;
    }

    for (i = 0; i < play2->panelCount; i++) {
        struct_game_state_data *state = &game_state_data[i];

        panel = &play2->panel[i];

        if (panel->flash) {
            state->virus_level = _timeAttack_levelTable[panel->glvItem.select];
            state->game_level = panel->glvItem.select;
        } else if (panel->timeAt) {
            state->virus_level = _timeAttack_levelTable[panel->glvItem.select];
            state->game_level = panel->glvItem.select;
        } else {
            state->virus_level = panel->lvGauge.level;
        }
        state->cap_def_speed = panel->speedItem.select;
    }

    i = play2->panelSub.stageNum.number - 1;

    story_proc_no = _bgDataNo_to_stageNo[i][1] + 1;
    story_proc_no += _bgDataNo_to_stageNo[i][0] * 0xC;
    evs_story_no = _bgDataNo_to_stageNo[i][1] + 1;

    evs_seqnumb = play2->panelSub.musicItem.select;
    evs_seqence = evs_seqnumb != 4;
    evs_game_time = 0;

    _setFadeDir(play2->global, 1);
    _setNextMain(play2->global, MAIN_12);
}

/**
 * Original name: menuPlay2_update
 */
void menuPlay2_update(MenuPlay2 *play2) {
    SMenuItem *miRoot = _getRootItem(play2->global);
    s32 i;

    switch (play2->depth) {
        case 0:
        case 1:
            menuItem_setColorDir(&play2->miONaJi, 1);
            break;

        default:
            menuItem_setColorDir(&play2->miONaJi, -1);
            break;
    }

    if (play2->master >= 0) {
        menuPlay2_applyMasterConfig(play2, play2->master);
    }

    for (i = 0; i < play2->panelCount; i++) {
        menuPlay2Panel_update(&play2->panel[i], miRoot);
    }

    if (play2->master >= 0) {
        menuPlay2_applyMasterCursor(play2, play2->master);
    }

    menuPlay2PanelSub_update(&play2->panelSub, miRoot);
    menuItem_update(&play2->miONaJi, miRoot);
}

/**
 * Original name: menuPlay2_draw
 */
void menuPlay2_draw(MenuPlay2 *play2, Gfx **gfxP) {
    Gfx *gfx = *gfxP;
    SMenuItem *miRoot UNUSED = _getRootItem(play2->global);
    MenuPlay2Panel *list[play2->panelCount];
    TiTexData *texC;
    s32 i;

    for (i = 0; i < play2->panelCount; i++) {
        list[i] = &play2->panel[i];
    }
    menuPlay2Panel_draw(list, play2->panelCount, &gfx);

    menuPlay2PanelSub_draw(&play2->panelSub, &gfx);

    gSPDisplayList(gfx++, fade_normal_texture_init_dl);
    gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);

    texC = _getTexSetup(play2->global, 0x13);
    menuItem_drawTex(&play2->miONaJi, &gfx, texC, 0);

    *gfxP = gfx;
}

/**
 * Original name: menuNmEnt_setFrame
 */
void menuNmEnt_setFrame(MenuNmEnt *nmEnt, s32 dir, f32 time) {
    SMenuItem *item = &nmEnt->miBase;

    item->transTime = time;
    item->transStep = 0.05f;
    item->transRange[0][1] = item->transRange[1][1] - 240.0f;
    menuItem_setTransDir(item, dir);
}

/**
 * Original name: menuNmEnt_init
 */
void menuNmEnt_init(MenuNmEnt *nmEnt, struct_watchMenu *global, void **heapP UNUSED) {
    s32 i;

    nmEnt->global = global;

    switch (_getMode(global)) {
        case MODE_VSMAN_NE:
        case MODE_VSMAN_FL_NE:
        case MODE_VSMAN_TA_NE:
            nmEnt->playerCount = 2;
            break;

        default:
            nmEnt->playerCount = 1;
            break;
    }

    for (i = 0; i < nmEnt->playerCount; i++) {
        if (evs_select_name_no[i] != 8) {
            u8 *mc = &evs_mem_data[evs_select_name_no[i]].mem_use_flg;

            if (_getMode(global) == MODE_NAME_NE2) {
                break;
            }
            if (!(*mc & MEM_USE_FLG_1)) {
                break;
            }
        }
    }

    nmEnt->playerNo = i;

    for (i = 0; i < ARRAY_COUNTU(evs_select_name_no); i++) {
        nmEnt->flow[i] = -1;
        nmEnt->pageNo[i] = 0;
        nmEnt->curPos[i][0] = 0;
        nmEnt->curPos[i][1] = 0;

        if ((_getMode(global) == MODE_NAME_NE2) && (evs_select_name_no[i] != 8)) {
            bcopy(evs_mem_data[evs_select_name_no[i]].mem_name, nmEnt->name[i], sizeof(nmEnt->name[i]));
        } else {
            s32 j;

            for (j = 0; j < ARRAY_COUNT(nmEnt->name[i]); j++) {
                nmEnt->name[i][j] = 0;
            }
        }

        nmEnt->namePos[i] = 0;
    }

    menuItem_init(&nmEnt->miBase, 29, 98);
    menuItem_init(&nmEnt->miPanel, 47, -47);
#if VERSION_US || VERSION_GW
    menuItem_init(&nmEnt->miPlayerNo, 100, 5);
#elif VERSION_CN
    menuItem_init(&nmEnt->miPlayerNo, 80, 7);
#else
#error ""
#endif
    menuItem_init(&nmEnt->miTable, 20, 7);
    menuItem_init(&nmEnt->miCursor, 0, 0);
    menuCursor_init(&nmEnt->cursor, global, CURSOR_ITEM, nmEnt->playerNo, -2, -2, 0x10, 0x10);
    nmEnt->cursor.flags.finger = true;
    menuItem_init(&nmEnt->miName, 59, 23);
    menuItem_init(&nmEnt->miNamePos, 0, 16);
    menuNmEnt_setFrame(nmEnt, 1, 0.0f);
}

/**
 * Original name: _menuNmEnt_updateCallback
 */
void _menuNmEnt_updateCallback(void *arg) {
    MenuNmEnt *nmEnt = arg;

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

/**
 * Original name: menuNmEnt_input
 */
void menuNmEnt_input(MenuNmEnt *nmEnt) {
    u32 rep = _getKeyRep(nmEnt->global, nmEnt->playerNo);
    u32 trg = _getKeyTrg(nmEnt->global, nmEnt->playerNo);
    s32 i;
    s32 vx;
    s32 vy;
    SndIndex sound = SND_INDEX_INVALID;
    s32 sp20 = 0;
    s32 sp24 = nmEnt->playerNo;

    if (nmEnt->miBase.transStep < 0.0f) {
        return;
    }
    if (nmEnt->miBase.transTime < 1.0f) {
        return;
    }

    vy = 0;
    vx = 0;
    if (rep & L_JPAD) {
        vx--;
    }
    if (rep & R_JPAD) {
        vx++;
    }
    if (rep & U_JPAD) {
        vy--;
    }
    if (rep & D_JPAD) {
        vy++;
    }

    if ((vx != 0) || (vy != 0)) {
        bool flag = false;
        s32 var_s0 = nmEnt->curPos[sp24][0];
        s32 var_s1 = nmEnt->curPos[sp24][1];
        char *c;

        do {
#if VERSION_US || VERSION_GW
            // discard const
            c = (char *)&_nameEntry_charTable[nmEnt->pageNo[sp24]][(var_s0 + var_s1 * 0xF) * 2];

            if (isdigit(c[0]) && (vx != 0)) {
                s32 temp_lo;
                s32 var_v0;

                temp_lo = vx * (c[1] - '0');
                if (vx > 0) {
                    var_v0 = 3 - temp_lo;
                } else {
                    var_v0 = -1 - temp_lo;
                }

                var_s0 = WrapI(0, 0xF, var_s0 + var_v0);
            } else {
                var_s0 = WrapI(0, 0xF, var_s0 + vx);
            }

#elif VERSION_CN
            var_s0 = WrapI(0, 0xF, var_s0 + vx);
#else
#error ""
#endif
            var_s1 = WrapI(0, 9, var_s1 + vy);
            c = (char *)&_nameEntry_charTable[nmEnt->pageNo[sp24]][((var_s0 + (var_s1 * 0xF)) * 2)];
        } while (c[0] == '_');

        if (c[0] & 0x80) {
            nmEnt->flow[sp24] = -1;
            flag++;
        } else if (isdigit(c[0])) {
            nmEnt->flow[sp24] = c[0] - '0';
            var_s0 += '0' - c[1];
            flag = (var_s0 != nmEnt->curPos[sp24][0]) || (var_s1 != nmEnt->curPos[sp24][1]);
        }

        if (flag) {
            nmEnt->curPos[sp24][0] = var_s0;
            nmEnt->curPos[sp24][1] = var_s1;
            sound = SND_INDEX_64;
        }
    }

    if ((trg & START_BUTTON) && (nmEnt->flow[sp24] != 5)) {
        nmEnt->flow[sp24] = 5;
        nmEnt->curPos[sp24][0] = 0xC;
        nmEnt->curPos[sp24][1] = 8;
        sound = SND_INDEX_62;
    } else if (trg & (A_BUTTON | START_BUTTON)) {
        const char *c =
            &_nameEntry_charTable[nmEnt->pageNo[sp24]][(nmEnt->curPos[sp24][0] + (nmEnt->curPos[sp24][1] * 0xF)) * 2];

        switch (nmEnt->flow[sp24]) {
            case -0x1:
                if (nmEnt->namePos[sp24] < 4) {
                    nmEnt->name[sp24][nmEnt->namePos[sp24]] = font2index(c);
                    nmEnt->namePos[sp24]++;
                    sound = SND_INDEX_62;
                }

                if (nmEnt->namePos[sp24] == 4) {
                    nmEnt->curPos[sp24][0] = 0xC;
                    nmEnt->curPos[sp24][1] = 8;
                    nmEnt->flow[sp24] = 5;
                }
                break;

            case 0x3:
                if (nmEnt->namePos[sp24] < 4) {
                    nmEnt->name[sp24][nmEnt->namePos[sp24]] = 0;
                    nmEnt->namePos[sp24]++;
                    sound = SND_INDEX_62;
                }

                if (nmEnt->namePos[sp24] == 4) {
                    nmEnt->curPos[sp24][0] = 0xC;
                    nmEnt->curPos[sp24][1] = 8;
                    nmEnt->flow[sp24] = 5;
                }
                break;

            case 0x4:
                if (nmEnt->namePos[sp24] > 0) {
                    nmEnt->namePos[sp24]--;
                    nmEnt->name[sp24][nmEnt->namePos[sp24]] = 0;
                    sound = SND_INDEX_68;
                } else {
                    sound = SND_INDEX_71;
                }
                break;

            case 0x5:
                for (i = 0; i < ARRAY_COUNT(nmEnt->name[sp24]); i++) {
                    if ((char)nmEnt->name[sp24][i] != 0) {
                        break;
                    }
                }

                if (i != ARRAY_COUNT(nmEnt->name[sp24])) {
                    sp20++;
                    sound = SND_INDEX_62;
                } else {
                    sound = SND_INDEX_71;
                }
                break;
        }
    } else if (trg & B_BUTTON) {
        if (nmEnt->namePos[sp24] > 0) {
            nmEnt->namePos[sp24]--;
            nmEnt->name[sp24][nmEnt->namePos[sp24]] = 0;
        } else {
            sp20--;
        }
        sound = SND_INDEX_68;
    }

    if (sp20 > 0) {
        struct_evs_mem_data *mc = &evs_mem_data[evs_select_name_no[sp24]];

        switch (_getMode(nmEnt->global)) {
            case MODE_NAME_NE2:
                break;

            default:
                dm_init_save_mem(mc);
                break;
        }

        mc->mem_use_flg |= MEM_USE_FLG_1;
        for (i = 0; i < ARRAY_COUNT(nmEnt->name[sp24]); i++) {
            mc->mem_name[i] = nmEnt->name[sp24][i];
        }

        for (i = sp24 + 1; i < nmEnt->playerCount; i++) {
            if (evs_select_name_no[i] != 8) {
                struct_evs_mem_data *mc = &evs_mem_data[evs_select_name_no[i]];

                if (_getMode(nmEnt->global) == MODE_NAME_NE2) {
                    break;
                }
                if (!(mc->mem_use_flg & MEM_USE_FLG_1)) {
                    break;
                }
            }
        }

        if (i >= nmEnt->playerCount) {
            MainMenuMode mode;

            _eepWritePlayer(nmEnt->global);

            switch (_getMode(nmEnt->global)) {
                case MODE_STORY_NE:
                    mode = MODE_STORY;
                    break;

                case MODE_LVSEL_NE:
                    mode = MODE_LVSEL;
                    break;

                case MODE_LVSEL_TQ_NE:
                    mode = MODE_LVSEL_TQ;
                    break;

                case MODE_LVSEL_TA_NE:
                    mode = MODE_LVSEL_TA;
                    break;

                case MODE_VSCOM_NE:
                    mode = MODE_VSCOM_CH;
                    break;

                case MODE_VSCOM_FL_NE:
                    mode = MODE_VSCOM_FL_CH;
                    break;

                case MODE_VSMAN_NE:
                    mode = MODE_VSMAN_CH;
                    break;

                case MODE_VSMAN_FL_NE:
                    mode = MODE_VSMAN_FL_CH;
                    break;

                case MODE_VSMAN_TA_NE:
                    mode = MODE_VSMAN_TA_CH;
                    break;

                case MODE_NAME_NE:
                case MODE_NAME_NE2:
                    mode = MODE_MAIN;
                    break;

                default:
                    break;
            }

            _setMode(nmEnt->global, mode);
            menuNmEnt_setFrame(nmEnt, -1, 1.0f);
        } else {
            nmEnt->playerNo = i;
        }
    } else if (sp20 < 0) {
        for (i = sp24 - 1; i >= 0; i--) {
            if (evs_select_name_no[i] != 8) {
                struct_evs_mem_data *mc = &evs_mem_data[evs_select_name_no[i]];

                if (_getMode(nmEnt->global) == MODE_NAME_NE2) {
                    break;
                }
                if (!(mc->mem_use_flg & MEM_USE_FLG_1)) {
                    break;
                }
            }
        }

        if (i < 0) {
            switch (_getMode(nmEnt->global)) {
                case MODE_NAME_NE2:
                    _setMode(nmEnt->global, MODE_MAIN);
                    break;

                default:
                    _setMode(nmEnt->global, MODE_MAIN);
                    break;
            }

            menuNmEnt_setFrame(nmEnt, -1, 1.0f);
        } else {
            nmEnt->playerNo = i;
        }

        sound = SND_INDEX_68;
    }

    SND_PLAY_INDEX(sound);
}

/**
 * Original name: menuNmEnt_update
 */
void menuNmEnt_update(MenuNmEnt *nmEnt) {
    SMenuItem *miRoot = _getRootItem(nmEnt->global);

    menuItem_update(&nmEnt->miBase, miRoot);
    menuItem_update(&nmEnt->miPanel, &nmEnt->miBase);
    menuItem_update(&nmEnt->miPlayerNo, &nmEnt->miPanel);
    menuItem_update(&nmEnt->miTable, &nmEnt->miBase);

    nmEnt->cursor.size[0] = (nmEnt->flow[nmEnt->playerNo] == -1) ? 0x10 : 0x32;
    nmEnt->cursor.playerNo = nmEnt->playerNo;

    menuItem_setTransHi(&nmEnt->miCursor, nmEnt->curPos[nmEnt->playerNo][0] * 0xF,
                        nmEnt->curPos[nmEnt->playerNo][1] * 0xD);
    menuItem_update(&nmEnt->miCursor, &nmEnt->miTable);
    menuCursor_update(&nmEnt->cursor, &nmEnt->miCursor);
    menuItem_update(&nmEnt->miName, &nmEnt->miPanel);
    nmEnt->miNamePos.transRange[1][0] = nmEnt->namePos[nmEnt->playerNo] * 0xD;
    menuItem_update(&nmEnt->miNamePos, &nmEnt->miName);
}

/**
 * Original name: menuNmEnt_draw
 */
void menuNmEnt_draw(MenuNmEnt *nmEnt, Gfx **gfxP) {
    Gfx *gfx = *gfxP;
    MenuCursor *list[1];
    TiTexData *texC;
    TiTexData *texA;
    const char *tbl;
    s32 i;
    s32 j;
    s32 tx;
    s32 ty;

    gSPDisplayList(gfx++, fade_normal_texture_init_dl);

    texC = _getTexName(nmEnt->global, 3);
    menuItem_drawTex(&nmEnt->miPanel, &gfx, texC, 0);
    if (nmEnt->playerNo == 1) {
        texC = _getTexName(nmEnt->global, 4);
        menuItem_drawTex(&nmEnt->miPlayerNo, &gfx, texC, 0);
    }

    gSPDisplayList(gfx++, fade_normal_texture_init_dl);

    texC = _getTexName(nmEnt->global, 2);
    if (!menuItem_drawTex(&nmEnt->miBase, &gfx, texC, 0)) {
        return;
    }

    gSPDisplayList(gfx++, fade_intensity_texture_init_dl);
    gDPSetTextureFilter(gfx++, G_TF_BILERP);
    gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, 255);

    // Draw keyboard
    ty = nmEnt->miTable.trans[1];
    tbl = _nameEntry_charTable[nmEnt->pageNo[nmEnt->playerNo]];
    for (i = 0; i < 9; i++) {
        tx = nmEnt->miTable.trans[0];

        for (j = 0; j < 0xF; j++) {
            if (*tbl & 0x80) {
                fontXX_draw(&gfx, tx, ty, 12.0f, 12.0f, tbl);
            }
            tx += 0xF;
            tbl += 2;
        }
        ty += 0xD;
    }

    // Draw selected characters
    tx = nmEnt->miName.trans[0];
    ty = nmEnt->miName.trans[1];
    for (i = 0; i < 4; i++) {
        fontXX_drawID(&gfx, tx, ty, 12.0f, 12.0f, (u8)nmEnt->name[nmEnt->playerNo][i]);
        tx += 0xD;
    }

    gSPDisplayList(gfx++, fade_alpha_texture_init_dl);

    texC = _getTexName(nmEnt->global, 0);
    texA = _getTexName(nmEnt->global, 1);
    menuItem_drawAlphaTex(&nmEnt->miNamePos, &gfx, texC, texA, 0);

    list[0] = &nmEnt->cursor;
    menuCursor_draw(list, 1, &gfx);

    *gfxP = gfx;
}

/**
 * Original name: menuRankBase_init
 */
void menuRankBase_init(MenuRankBase *rankBase, struct_watchMenu *global, s32 x, s32 y) {
    rankBase->global = global;
    menuItem_init(&rankBase->miBase, x, y);
}

/**
 * Original name: menuRankBase_update
 */
void menuRankBase_update(MenuRankBase *rankBase, SMenuItem *parent) {
    menuItem_update(&rankBase->miBase, parent);
}

/**
 * Original name: menuRankBase_draw
 */
void menuRankBase_draw(MenuRankBase *rankBaseArr[], s32 count, Gfx **gfxP) {
    Gfx *gfx = *gfxP;
    s32 i;

    gSPDisplayList(gfx++, fade_normal_texture_init_dl);

    for (i = 0; i < 2; i++) {
        s32 cached = 0;
        s32 j;

        for (j = 0; j < count; j++) {
            MenuRankBase *rankBase = rankBaseArr[j];
            SMenuItem *item = &rankBase->miBase;
            f32 y = item->trans[1];
            TiTexData *texC;

            item->trans[1] = y + i * 8;
            texC = _getTexRank(rankBase->global, 5);
            cached += menuItem_drawItem(item, &gfx, texC, cached, 2, i);
            item->trans[1] = y;
        }
    }

    *gfxP = gfx;
}

/**
 * Original name: menuRankNum_init
 */
void menuRankNum_init(MenuRankNum *rankNum, struct_watchMenu *global, s32 number, s32 x, s32 y) {
    rankNum->global = global;
    rankNum->number = number;
    menuItem_init(&rankNum->miBase, x, y);
}

/**
 * Original name: menuRankNum_update
 */
void menuRankNum_update(MenuRankNum *rankNum, SMenuItem *parent) {
    menuItem_update(&rankNum->miBase, parent);
}

/**
 * Original name: menuRankNum_draw
 */
void menuRankNum_draw(MenuRankNum *rankNumArr[], s32 count, Gfx **gfxP) {
    Gfx *gfx = *gfxP;
    s32 i;
    bool init;
    bool cached;

    for (i = -1; init = false, cached = false, i < 10; i++) {
        s32 j;

        for (j = 0; j < count; j++) {
            MenuRankNum *rankNum = rankNumArr[j];
            SMenuItem *item = &rankNum->miBase;
            TiTexData *texC;
            TiTexData *texA;

            if (i != rankNum->number) {
                continue;
            }

            if (i == -1) {
                if (!init) {
                    init = true;
                    gSPDisplayList(gfx++, fade_normal_texture_init_dl);
                }

                texC = _getTexRank(rankNum->global, 6);
                cached += menuItem_drawTex(item, &gfx, texC, cached);
            } else {
                f32 x;
                f32 y;

                if (!init) {
                    init = true;
                    gSPDisplayList(gfx++, fade_alpha_texture_init_dl);
                }

                texC = _getTexGameP1(rankNum->global, 2);
                texA = _getTexGameP1(rankNum->global, 6);

                x = item->trans[0];
                y = item->trans[1];

                item->trans[0] += 2.0f;
                item->trans[1] += 2.0f;

                cached += menuItem_drawAlphaItem(item, &gfx, texC, texA, cached, 0xC, rankNum->number + 2);
                item->trans[0] = x;
                item->trans[1] = y;
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

/**
 * Original name: menuRankFig_init
 */
void menuRankFig_init(MenuRankFig *rankFig, struct_watchMenu *global, MenuRankFigType column, s32 number,
                      MenuRankFigColor color, s32 x, s32 y) {
    SMenuItem *item;
    const u8 *colorP;
    s32 i;

    rankFig->global = global;
    if (column <= RANK_FIG_NUMBER) {
        rankFig->type = RANK_FIG_NUMBER;
        rankFig->column = column;
    } else if (column == RANK_FIG_TIME) {
        rankFig->type = RANK_FIG_TIME;
        rankFig->column = RANK_FIG_TIME_MAX_COL;
    } else if (column == RANK_FIG_RATIO) {
        rankFig->type = RANK_FIG_RATIO;
        rankFig->column = RANK_FIG_RATIO_MAX_COL;
    } else if (column == RANK_FIG_LEVEL) {
        rankFig->type = RANK_FIG_LEVEL;
        rankFig->column = RANK_FIG_LEVEL_MAX_COL;
    } else if (column == RANK_FIG_TIME2) {
        rankFig->type = RANK_FIG_TIME2;
        rankFig->column = RANK_FIG_TIME2_MAX_COL;
    } else if (column == RANK_FIG_CLEAR) {
        rankFig->type = RANK_FIG_CLEAR;
        rankFig->column = RANK_FIG_CLEAR_MAX_COL;
    } else if (column == RANK_FIG_ALL) {
        rankFig->type = RANK_FIG_ALL;
        rankFig->column = RANK_FIG_ALL_MAX_COL;
    }

    rankFig->number = number;
    menuItem_init(&rankFig->miBase, x, y);

    item = &rankFig->miBase;
    colorP = _color_9658[color];
    for (i = 0; i < ARRAY_COUNT(_color_9658[color]); i++) {
        item->colorRange[0][i] = item->colorRange[1][i] = colorP[i] * (DOUBLE_LITERAL(1) / 255);
    }
}

/**
 * Original name: menuRankFig_update
 */
void menuRankFig_update(MenuRankFig *rankFig, SMenuItem *parent) {
    s32 n = rankFig->number;
    s32 i;

    switch (rankFig->type) {
        case RANK_FIG_NUMBER:
            for (i = rankFig->column - 1; i >= 0; i--) {
                rankFig->columns[i] = n % 10;
                n /= 10;
            }
            break;

        case RANK_FIG_TIME:
            rankFig->columns[4] = n % 10;
            n /= 10;
            rankFig->columns[3] = n % 6;
            n /= 6;
            rankFig->columns[2] = MENURANKFIGVALUE_COLON;
            rankFig->columns[1] = n % 10;
            n /= 10;
            rankFig->columns[0] = n % 10;
            break;

        case RANK_FIG_RATIO:
            rankFig->columns[5] = MENURANKFIGVALUE_PERCENTAGE;
            rankFig->columns[3] = MENURANKFIGVALUE_DOT;
            rankFig->columns[4] = n % 10;
            n /= 10;
            rankFig->columns[2] = n % 10;
            n /= 10;
            rankFig->columns[1] = n % 10;
            n /= 10;
            rankFig->columns[0] = n % 10;
            break;

        case RANK_FIG_LEVEL:
            rankFig->columns[6] = n % 10;
            n /= 10;
            rankFig->columns[5] = n % 10;
            rankFig->columns[4] = MENURANKFIGVALUE_L;
            rankFig->columns[3] = MENURANKFIGVALUE_E;
            rankFig->columns[2] = MENURANKFIGVALUE_V;
            rankFig->columns[1] = MENURANKFIGVALUE_E;
            rankFig->columns[0] = MENURANKFIGVALUE_L;
            break;

        case RANK_FIG_TIME2:
            rankFig->columns[5] = n % 10;
            n /= 10;
            rankFig->columns[4] = MENURANKFIGVALUE_COLON;
            rankFig->columns[3] = n % 10;
            n /= 10;
            rankFig->columns[2] = n % 6;
            n /= 6;
            rankFig->columns[1] = MENURANKFIGVALUE_COLON;
            rankFig->columns[0] = n % 10;
            break;

        case RANK_FIG_CLEAR:
            rankFig->columns[0] = MENURANKFIGVALUE_C;
            rankFig->columns[1] = MENURANKFIGVALUE_L;
            rankFig->columns[2] = MENURANKFIGVALUE_E;
            rankFig->columns[3] = MENURANKFIGVALUE_A;
            rankFig->columns[4] = MENURANKFIGVALUE_R;
            break;

        case RANK_FIG_ALL:
            rankFig->columns[0] = MENURANKFIGVALUE_A;
            rankFig->columns[1] = MENURANKFIGVALUE_L;
            rankFig->columns[2] = MENURANKFIGVALUE_L;
            break;

        default:
            break;
    }

    menuItem_update(&rankFig->miBase, parent);
}

// shift-jis string. Note this is a singular string
char _code_9711[] = {
    "０" /* MENURANKFIGVALUE_0 */
    "１" /* MENURANKFIGVALUE_1 */
    "２" /* MENURANKFIGVALUE_2 */
    "３" /* MENURANKFIGVALUE_3 */
    "４" /* MENURANKFIGVALUE_4 */
    "５" /* MENURANKFIGVALUE_5 */
    "６" /* MENURANKFIGVALUE_6 */
    "７" /* MENURANKFIGVALUE_7 */
    "８" /* MENURANKFIGVALUE_8 */
    "９" /* MENURANKFIGVALUE_9 */
    "Ｃ" /* MENURANKFIGVALUE_C */
    "Ｌ" /* MENURANKFIGVALUE_L */
    "Ｅ" /* MENURANKFIGVALUE_E */
    "Ａ" /* MENURANKFIGVALUE_A */
    "Ｒ" /* MENURANKFIGVALUE_R */
    "：" /* MENURANKFIGVALUE_COLON */
    "％" /* MENURANKFIGVALUE_PERCENTAGE */
    "．" /* MENURANKFIGVALUE_DOT */
    "Ｖ" /* MENURANKFIGVALUE_V */
};

const s32 _posX_0_9712[] = {
    0 * 9, 1 * 9, 2 * 9, 3 * 9, 4 * 9, 5 * 9, 6 * 9, 7 * 9, 8 * 9, 9 * 9,
};
static_assert(ARRAY_COUNT(_posX_0_9712) == MENURANKFIG_COLUMNS_MAX, "");
static_assert(ARRAY_COUNT(_posX_0_9712) >= RANK_FIG_NUMBER_MAX_COL, "");
static_assert(ARRAY_COUNT(_posX_0_9712) >= RANK_FIG_LEVEL_MAX_COL, "");
static_assert(ARRAY_COUNT(_posX_0_9712) >= RANK_FIG_CLEAR_MAX_COL, "");
static_assert(ARRAY_COUNT(_posX_0_9712) >= RANK_FIG_ALL_MAX_COL, "");

const s32 _posX_1_9713[] = {
    0 * 7, 1 * 7 + 2, 2 * 7 + 2, 3 * 7 + 2, 4 * 7 + 4,
};
static_assert(ARRAY_COUNT(_posX_1_9713) == RANK_FIG_TIME_MAX_COL, "");

const s32 _posX_2_9714[] = {
    0 * 9, 1 * 9, 2 * 9, 3 * 9, 4 * 9 - 5, 5 * 9 - 5,
};
static_assert(ARRAY_COUNT(_posX_2_9714) == RANK_FIG_RATIO_MAX_COL, "");

const s32 _posX_4_9715[] = {
    0 * 7, 1 * 7, 2 * 7, 3 * 7 + 2, 4 * 7 + 2, 5 * 7 + 2,
};
static_assert(ARRAY_COUNT(_posX_4_9715) == RANK_FIG_TIME2_MAX_COL, "");

const s32 *_posX_tbl_9716[] = {
    _posX_0_9712, /* RANK_FIG_NUMBER */
    _posX_1_9713, /* RANK_FIG_TIME */
    _posX_2_9714, /* RANK_FIG_RATIO */
    _posX_0_9712, /* RANK_FIG_LEVEL */
    _posX_4_9715, /* RANK_FIG_TIME2 */
    _posX_0_9712, /* RANK_FIG_CLEAR */
    _posX_0_9712, /* RANK_FIG_ALL */
};
static_assert(ARRAY_COUNT(_posX_tbl_9716) == RANK_FIG_SUM - RANK_FIG_NUMBER, "");

MainMenuMode _menuAll_lastMode = MODE_MAIN;

/**
 * Original name: menuRankFig_draw
 */
void menuRankFig_draw(MenuRankFig *rankFigArr[], s32 count, Gfx **gfxP) {
    Gfx *gfx = *gfxP;
    f32 step = 9.0f;
    MenuRankFigVal i;

    font16_initDL2(&gfx);

    gDPSetTextureFilter(gfx++, G_TF_BILERP);

    for (i = 0; i < MENURANKFIGVALUE_MAX; i++) {
        // shift-jis characters are 2 bytes wide (the non ascii ones)
        s32 code = font2index(&_code_9711[i * 2]);
        s32 j;

        for (j = 0; j < count; j++) {
            MenuRankFig *rankFig = rankFigArr[j];
            SMenuItem *item = &rankFig->miBase;
            s32 k;

            for (k = 0; k < rankFig->column; k++) {
                if ((i != rankFig->columns[k]) || menuItem_outOfScreen(item, step, 0xC)) {
                    continue;
                }

                menuItem_setPrim(item, &gfx);

#if VERSION_US || VERSION_GW
                if (fontXX_drawID2(&gfx,
                                   item->trans[0] + _posX_tbl_9716[rankFig->type - RANK_FIG_NUMBER][k] * item->scale[0],
                                   item->trans[1], item->scale[0] * step, item->scale[1] * 12.0f, code)) {
                    code = -1;
                }
#elif VERSION_CN
                if ((rankFig->column >= 6) && (rankFig->columns[0] == MENURANKFIGVALUE_L) &&
                    (rankFig->columns[1] == MENURANKFIGVALUE_E) && (rankFig->columns[2] == MENURANKFIGVALUE_V) &&
                    (rankFig->columns[3] == MENURANKFIGVALUE_E) && (rankFig->columns[4] == MENURANKFIGVALUE_L)) {
                    if (k < 5) {
                        continue;
                    }
                    fontXX_drawID2(
                        &gfx, item->trans[0] + _posX_tbl_9716[rankFig->type - RANK_FIG_NUMBER][k - 2] * item->scale[0],
                        item->trans[1], item->scale[0] * step, item->scale[1] * 12.0f, code);
                } else {
                    fontXX_drawID2(&gfx,
                                   item->trans[0] + _posX_tbl_9716[rankFig->type - RANK_FIG_NUMBER][k] * item->scale[0],
                                   item->trans[1], item->scale[0] * step, item->scale[1] * 12.0f, code);
                }
                code = -1;
#else
#error ""
#endif
            }
        }
    }

    *gfxP = gfx;
}

const u8 _color_9791[] = { 0x80, 0x80, 0x80 };

/**
 * Original name: menuRankName_init
 */
void menuRankName_init(MenuRankName *rankName, struct_watchMenu *global, const u8 name[4], s32 x, s32 y) {
    SMenuItem *item;
    s32 i;

    rankName->global = global;
    for (i = 0; i < ARRAY_COUNTU(rankName->name); i++) {
        rankName->name[i] = name[i];
    }

    item = &rankName->miBase;
    menuItem_init(item, x, y);

    for (i = 0; i < ARRAY_COUNT(_color_9791); i++) {
        item->colorRange[0][i] = item->colorRange[1][i] = _color_9791[i] * (DOUBLE_LITERAL(1) / 255);
    }
}

/**
 * Original name: menuRankName_update
 */
void menuRankName_update(MenuRankName *rankName, SMenuItem *parent) {
    menuItem_update(&rankName->miBase, parent);
}

/**
 * Original name: menuRankName_draw
 */
void menuRankName_draw(MenuRankName *rankNameArr[], s32 count, Gfx **gfxP) {
    Gfx *gfx = *gfxP;
    SMenuItem *item;
    MenuRankName *rankName;
    f32 x;
    s32 j;
    s32 i;
    f32 temp = 13.0f;

    font16_initDL2(&gfx);

    gDPSetTextureFilter(gfx++, G_TF_BILERP);

    for (i = 0; i < count; i++) {
        rankName = rankNameArr[i];
        item = &rankName->miBase;

        if (menuItem_outOfScreen(item, temp + 39, 0xC)) {
            continue;
        }

        x = item->trans[0];
        menuItem_setPrim(item, &gfx);

        for (j = 0; j < 4; j++) {
            fontXX_drawID2(&gfx, x, item->trans[1], 12.0f, item->scale[1] * 12.0f, rankName->name[j]);
            x += temp;
        }
    }

    *gfxP = gfx;
}

/**
 * Original name: menuRankLabel_init
 */
void menuRankLabel_init(MenuRankLabel *rankLabel, struct_watchMenu *global, s32 type, s32 index, s32 x, s32 y) {
    rankLabel->global = global;
    rankLabel->type = type;
    rankLabel->index = index;
    menuItem_init(&rankLabel->miBase, x, y);
}

/**
 * Original name: menuRankLabel_update
 */
void menuRankLabel_update(MenuRankLabel *rankLabel, SMenuItem *parent) {
    menuItem_update(&rankLabel->miBase, parent);
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

/**
 * Original name: menuRankLabel_update
 */
void menuRankLabel_draw(MenuRankLabel *rankLabelArr[], s32 count, Gfx **gfxP) {
    Gfx *gfx = *gfxP;
    s32 i;
    s32 rows;

    gSPDisplayList(gfx++, fade_normal_texture_init_dl);

    for (i = 0; rows = _rows_9879[i], i < ARRAY_COUNT(_rows_9879); i++) {
        s32 j;
        s32 cached;

        for (j = 0; cached = 0, j < rows; j++) {
            s32 k;

            for (k = 0; k < count; k++) {
                MenuRankLabel *rankLabel = rankLabelArr[k];
                SMenuItem *item = &rankLabel->miBase;
                TiTexData *texC;

                if ((i != rankLabel->type) || (j != rankLabel->index)) {
                    continue;
                }

                switch (i) {
                    case 0:
                        texC = _getTexRank(rankLabel->global, 7);
                        cached += menuItem_drawItem(item, &gfx, texC, cached, rows, j);
                        break;

                    case 1:
                    case 2:
                        texC = _getTexRank(rankLabel->global, _tex_9880[i]);
                        cached += menuItem_drawItem(item, &gfx, texC, cached, rows, j);
                        break;

                    case 3:
                        texC = _getTexCommon(rankLabel->global, 0xE);
                        cached += menuItem_drawItem(item, &gfx, texC, cached, 0x2F, _choice_9881[j]);
                        break;
                }
            }
        }
    }

    *gfxP = gfx;
}

/**
 * Original name: menuRankHeader_init
 */
void menuRankHeader_init(MenuRankHeader *rankHeader, struct_watchMenu *global, const s32 *labelType,
                         const s32 *labelIndex, const s32 *labelX, const s32 *labelY, s32 labelCount, s32 x, s32 y) {
    s32 i;

    rankHeader->global = global;
    rankHeader->labelCount = labelCount;
    menuItem_init(&rankHeader->miBase, x, y);

    for (i = 0; i < labelCount; i++) {
        menuRankLabel_init(&rankHeader->label[i], global, labelType[i], labelIndex[i], labelX[i], labelY[i]);
    }
}

/**
 * Original name: menuRankHeader_update
 */
void menuRankHeader_update(MenuRankHeader *rankHeader, SMenuItem *parent) {
    s32 i;

    menuItem_update(&rankHeader->miBase, parent);

    for (i = 0; i < rankHeader->labelCount; i++) {
        menuRankLabel_update(&rankHeader->label[i], &rankHeader->miBase);
    }
}

/**
 * Original name: menuRankHeader_draw
 */
void menuRankHeader_draw(MenuRankHeader *rankHeaderArr[], s32 count, Gfx **gfxP) {
    Gfx *gfx = *gfxP;
    s32 newCount = 0;
    MenuRankLabel *list[count * 5];
    s32 i;

    for (i = 0; i < count; i++) {
        MenuRankHeader *rankHeader = rankHeaderArr[i];
        s32 j;

        for (j = 0; j < rankHeader->labelCount; j++) {
            list[newCount] = &rankHeader->label[j];
            newCount++;
        }
    }

    menuRankLabel_draw(list, newCount, &gfx);

    *gfxP = gfx;
}

void func_80057D24(MenuRankPanel *menuRankPanel, struct_watchMenu *watchMenuRef, s32 arg2, const u8 arg3[4], u32 arg4,
                   s32 arg5, s32 arg6, s32 arg7, s32 arg8) {
    s32 var_a2;
    s32 var_v1;

    menuRankPanel->watchMenuRef = watchMenuRef;
    menuRankPanel->unk_004 = 0;

    menuRankBase_init(&menuRankPanel->unk_008, watchMenuRef, arg7, arg8);
    menuRankNum_init(&menuRankPanel->unk_09C, watchMenuRef, arg2, 4, -1);
    menuRankName_init(&menuRankPanel->unk_134, watchMenuRef, arg3, 0x1A, 2);
    menuRankFig_init(&menuRankPanel->unk_1CC, watchMenuRef, RANK_FIG_NUMBER, arg4, MENURANKFIG_COLOR_RED, 0x83, 2);
    menuRankFig_init(&menuRankPanel->unk_294, watchMenuRef, RANK_FIG_TIME, arg5, MENURANKFIG_COLOR_BLUE, 0xCD, 2);
    var_v1 = 0x5A;
    if (arg6 < 0xA) {
        var_a2 = 1;
        var_v1 = 0x63;
    } else {
        var_a2 = 0xD;
    }
    menuRankFig_init(&menuRankPanel->unk_35C, watchMenuRef, var_a2, arg6, MENURANKFIG_COLOR_YELLOW, var_v1, 2);
}

void func_80057E68(MenuRankPanel *menuRankPanel, struct_watchMenu *watchMenuRef, s32 arg2, const u8 arg3[4], s32 arg4,
                   s32 arg5, s32 arg6, s32 arg7) {
    menuRankPanel->watchMenuRef = watchMenuRef;
    menuRankPanel->unk_004 = 1;

    menuRankBase_init(&menuRankPanel->unk_008, watchMenuRef, arg6, arg7);
    menuRankNum_init(&menuRankPanel->unk_09C, watchMenuRef, arg2, 4, -1);
    menuRankName_init(&menuRankPanel->unk_134, watchMenuRef, arg3, 0x29, 2);
    menuRankFig_init(&menuRankPanel->unk_1CC, watchMenuRef, RANK_FIG_LEVEL, arg4, MENURANKFIG_COLOR_GREEN, 0x6A, 2);
    menuRankFig_init(&menuRankPanel->unk_294, watchMenuRef, RANK_FIG_NUMBER, arg5, MENURANKFIG_COLOR_RED, 0xB7, 2);
}

void func_80057F6C(MenuRankPanel *menuRankPanel, struct_watchMenu *watchMenuRef, s32 arg2, const u8 arg3[4], s32 arg4,
                   s32 arg5, s32 arg6, s32 arg7) {
    menuRankPanel->watchMenuRef = watchMenuRef;
    menuRankPanel->unk_004 = 2;

    menuRankBase_init(&menuRankPanel->unk_008, watchMenuRef, arg6, arg7);
    menuRankNum_init(&menuRankPanel->unk_09C, watchMenuRef, arg2, 4, -1);
    menuRankName_init(&menuRankPanel->unk_134, watchMenuRef, arg3, 0x29, 2);
    menuRankFig_init(&menuRankPanel->unk_1CC, watchMenuRef, RANK_FIG_TIME, arg4, MENURANKFIG_COLOR_BLUE, 0x75, 2);
    menuRankFig_init(&menuRankPanel->unk_294, watchMenuRef, RANK_FIG_NUMBER, arg5, MENURANKFIG_COLOR_RED, 0xB7, 2);
}

void func_8005806C(MenuRankPanel *menuRankPanel, struct_watchMenu *watchMenuRef, s32 arg2, const u8 arg3[4], s32 arg4,
                   s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9) {
    s32 var_a2;
    s32 var_v1;

    menuRankPanel->watchMenuRef = watchMenuRef;
    menuRankPanel->unk_004 = 3;

    menuRankBase_init(&menuRankPanel->unk_008, watchMenuRef, arg8, arg9);
    menuRankNum_init(&menuRankPanel->unk_09C, watchMenuRef, arg2, 4, -1);
    menuRankName_init(&menuRankPanel->unk_134, watchMenuRef, arg3, 0x1A, 2);
    menuRankFig_init(&menuRankPanel->unk_1CC, watchMenuRef, RANK_FIG_NUMBER, arg4, MENURANKFIG_COLOR_RED, 0x53, 2);
    menuRankFig_init(&menuRankPanel->unk_294, watchMenuRef, RANK_FIG_TIME2, arg5, MENURANKFIG_COLOR_BLUE, 0x99, 2);

    if (arg6 < dm_get_first_virus_count_in_new_mode(arg7)) {
        var_a2 = 2;
        var_v1 = 0xD9;
    } else {
        var_a2 = 0xD;
        var_v1 = 0xD5;
    }
    menuRankFig_init(&menuRankPanel->unk_35C, watchMenuRef, var_a2, arg6, MENURANKFIG_COLOR_RED, var_v1, 2);
}

void func_800581C8(MenuRankPanel *menuRankPanel, struct_watchMenu *watchMenuRef, s32 arg2, const u8 arg3[4], s32 arg4,
                   s32 arg5, s32 arg6, s32 arg7, s32 arg8) {
    menuRankPanel->watchMenuRef = watchMenuRef;
    menuRankPanel->unk_004 = 4;

    menuRankBase_init(&menuRankPanel->unk_008, watchMenuRef, arg7, arg8);
    menuRankNum_init(&menuRankPanel->unk_09C, watchMenuRef, arg2, 4, -1);
    menuRankName_init(&menuRankPanel->unk_134, watchMenuRef, arg3, 0x1A, 2);
    menuRankFig_init(&menuRankPanel->unk_1CC, watchMenuRef, RANK_FIG_RATIO, arg4, MENURANKFIG_COLOR_ORANGE, 0x5A, 2);
    menuRankFig_init(&menuRankPanel->unk_294, watchMenuRef, 2, arg5, MENURANKFIG_COLOR_PINK, 0xA7, 2);
    menuRankFig_init(&menuRankPanel->unk_35C, watchMenuRef, 2, arg6, MENURANKFIG_COLOR_CYAN, 0xD9, 2);
}

void menuRankPanel_update(MenuRankPanel *arg0, SMenuItem *arg1) {
    menuRankBase_update(&arg0->unk_008, arg1);
    menuRankNum_update(&arg0->unk_09C, &arg0->unk_008.miBase);
    menuRankName_update(&arg0->unk_134, &arg0->unk_008.miBase);

    switch (arg0->unk_004) {
        case 0x0:
            menuRankFig_update(&arg0->unk_1CC, &arg0->unk_008.miBase);
            menuRankFig_update(&arg0->unk_294, &arg0->unk_008.miBase);
            menuRankFig_update(&arg0->unk_35C, &arg0->unk_008.miBase);
            break;

        case 0x1:
            menuRankFig_update(&arg0->unk_1CC, &arg0->unk_008.miBase);
            menuRankFig_update(&arg0->unk_294, &arg0->unk_008.miBase);
            break;

        case 0x2:
            menuRankFig_update(&arg0->unk_1CC, &arg0->unk_008.miBase);
            menuRankFig_update(&arg0->unk_294, &arg0->unk_008.miBase);
            break;

        case 0x3:
            menuRankFig_update(&arg0->unk_1CC, &arg0->unk_008.miBase);
            menuRankFig_update(&arg0->unk_294, &arg0->unk_008.miBase);
            menuRankFig_update(&arg0->unk_35C, &arg0->unk_008.miBase);
            break;

        case 0x4:
            menuRankFig_update(&arg0->unk_1CC, &arg0->unk_008.miBase);
            menuRankFig_update(&arg0->unk_294, &arg0->unk_008.miBase);
            menuRankFig_update(&arg0->unk_35C, &arg0->unk_008.miBase);
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

    item = &temp_s2->unk_0004.miBase;
    item->transRange[0][0] = item->transRange[1][0] + arg4;
    item->transRange[0][1] = item->transRange[1][1];
    item->transStep = 0.05f;
    item->transTime = arg3;
    menuItem_setTransDir(item, arg2);

    for (i = 0; i < temp_s2->unk_0000; i++) {
        item = &temp_s2->unk_3A8[i].unk_008.miBase;

        item->transRange[0][0] = item->transRange[1][0] + arg4;
        item->transRange[0][1] = item->transRange[1][1];
        item->transStep = 0.05f;
        item->transTime = arg3;
        menuItem_setTransDir(item, arg2);
    }

    arg2 = (arg2 < 0) ? -1 : 1;

    for (i = 0; i < temp_s2->unk_0000; i++) {
        item = &temp_s2->unk_3A8[i].unk_008.miBase;

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

    item = &menuRank->unk_03BC.miBase;
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

    item = &temp_fp->unk_0004.miBase;
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
        item = &temp_fp->unk_3A8[i].unk_008.miBase;

        item->transRange[0][0] = item->transRange[1][0] + _pos_10346[i % ARRAY_COUNTU(_pos_10346)];
        item->transRange[0][1] = item->transRange[1][1];
        item->transStep = 0.05f;
        item->transTime = arg3;
        menuItem_setTransDir(item, arg2);
    }
}

void func_80058A24(MenuRank *menuRank, s32 arg1 UNUSED) {
    menuItem_init(&menuRank->unk_032C, 0xA4, 0x30);
    menuRankLabel_init(&menuRank->unk_0458, menuRank->watchMenuRef, 1, 1, 2, 2);
    menuRankLabel_init(&menuRank->unk_04F4, menuRank->watchMenuRef, 2, 1, 0x3E, 2);
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

    menuRankLabel_init(&menuRank->unk_03BC, menuRank->watchMenuRef, 3, sp3C, 0x23, 0x30);
    menuRankHeader_init(&temp_s3->unk_0004, menuRank->watchMenuRef, _hedAllType_10392, idP, xP, yP, count, 0, -0x10);

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
                              temp_t0_2->c_level, temp_t0_2->score, 0, i * 0x11);
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
    menuRank->unk_04F4.index = arg3;
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

    item = &temp_s0->unk_3A8[0].unk_008.miBase;
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

    menuRankLabel_update(&menuRank->unk_03BC, rootItem);
    menuRankLabel_update(&menuRank->unk_0458, &menuRank->unk_032C);
    menuRankLabel_update(&menuRank->unk_04F4, &menuRank->unk_032C);

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

            menuRankHeader_update(&temp_s2->unk_0004, &menuRank->unk_017C);

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
            menuRank->unk_04F4.index = menuRank->unk_0010;
        } else {
            menuRank->unk_04F4.index = menuRank->unk_000C;
        }

        switch (menuRank->unk_0004) {
            case MODE_RECORD_LS:
                menuRank->unk_0458.index = 1;
                menuRank->unk_04F4.index = menuRank->unk_04F4.index + 3;
                break;

            default:
                menuRank->unk_0458.index = 0;
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
            menuMain_waitCancel(&arg0->unk_02678[index].menuMain);
            break;

        case MODE_STORY:
            menuStory_waitCancel(&arg0->unk_02678[index].menuStory);
            break;

        case MODE_LVSEL:
        case MODE_LVSEL_TQ:
        case MODE_LVSEL_TA:
            menuLvSel_waitCancel(&arg0->unk_02678[index].menuLvSel);
            break;

        case MODE_VSCOM:
        case MODE_VSCOM_FL:
        case MODE_VSMAN:
        case MODE_VSMAN_FL:
        case MODE_VSMAN_TA:
        case MODE_PLAY4_LV:
        case MODE_PLAY4_TB_LV:
        case MODE_PLAY4_FL_LV:
            menuPlay2_waitCancel(&arg0->unk_02678[index].menuPlay2);
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

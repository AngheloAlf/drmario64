/**
 * Original filename: main_menu.c
 */

#include "main_menu.h"

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

f32 func_80045DD0(f32 arg0, f32 arg1) {
    arg0 += arg1;

    if (arg0 < 0.0f) {
        arg0 = 0.0f;
    } else if (arg0 > 1.0f) {
        arg0 = 1.0f;
    }
    return arg0;
}

f32 func_80045E18(f32 arg0, f32 arg1) {
    return WrapF(0.0f, 1.0f, arg0 + arg1);
}

f32 func_80045E48(f32 arg0) {
    if (arg0 < DOUBLE_LITERAL(0.5)) {
        arg0 = SQ(arg0);
    } else {
        arg0 = DOUBLE_LITERAL(1) - arg0;
        arg0 = DOUBLE_LITERAL(0.5) - SQ(arg0);
    }

    return 2.0f * arg0;
}

void func_80045E94(MenuItem *item) {
    f32 temp_fv0 = func_80045DD0(item->unk_14, item->unk_18);
    s32 i;

    item->unk_14 = temp_fv0;
    for (i = 0; i < MENUITEM_UNK_LEN2; i++) {
        item->pos[i] = item->unk_1C[i] + (item->unk_24[i] - item->unk_1C[i]) * temp_fv0;
    }
}

/**
 * Original name: transFunc_curve
 */
void transFunc_curve(MenuItem *item) {
    s32 i;
    f32 temp_ft0;
    f32 temp_fv0;

    temp_fv0 = func_80045DD0(item->unk_14, item->unk_18);
    temp_ft0 = func_80045E48(temp_fv0);
    item->unk_14 = temp_fv0;

    for (i = 0; i < ARRAY_COUNTU(item->pos); i++) {
        item->pos[i] = item->unk_1C[i] + ((item->unk_24[i] - item->unk_1C[i]) * temp_ft0);
    }
}

/**
 * Original name: transFunc_finger
 */
void transFunc_finger(MenuItem *item) {
    s32 i;
    f32 temp_fv0;
    f32 temp_fv0_2;

    temp_fv0 = func_80045E18(item->unk_14, item->unk_18);
    temp_fv0_2 = (sinf(2 * DOUBLE_LITERAL(M_PI) * temp_fv0) + DOUBLE_LITERAL(1)) * DOUBLE_LITERAL(0.5);
    item->unk_14 = temp_fv0;

    for (i = 0; i < ARRAY_COUNTU(item->pos); i++) {
        item->pos[i] = item->unk_1C[i] + (item->unk_24[i] - item->unk_1C[i]) * temp_fv0_2;
    }
}

void func_80046008(MenuItem *item) {
    f32 temp_fv0 = func_80045DD0(item->unk_38, item->unk_3C);
    s32 i;

    item->unk_38 = temp_fv0;
    for (i = 0; i < MENUITEM_UNK_LEN; i++) {
        item->unk_30[i] = item->unk_40[i] + (item->unk_48[i] - item->unk_40[i]) * temp_fv0;
    }
}

/**
 * Original name: scaleFunc_curve
 */
void scaleFunc_curve(MenuItem *item) {
    s32 i;
    f32 temp_ft0;
    f32 temp_fv0;

    temp_fv0 = func_80045DD0(item->unk_38, item->unk_3C);
    temp_ft0 = func_80045E48(temp_fv0);
    item->unk_38 = temp_fv0;

    for (i = 0; i < ARRAY_COUNTU(item->unk_30); i++) {
        item->unk_30[i] = item->unk_40[i] + (item->unk_48[i] - item->unk_40[i]) * temp_ft0;
    }
}

void func_800460DC(MenuItem *item) {
    f32 temp = func_80045DD0(item->unk_64, item->unk_68);
    s32 i;

    item->unk_64 = temp;
    for (i = 0; i < 4U; i++) {
        item->color.arr[i] = item->unk_6C[0][i] + (item->unk_6C[1][i] - item->unk_6C[0][i]) * temp;
    }
}

/**
 * Original name: colorFunc_curve
 */
void colorFunc_curve(MenuItem *item) {
    s32 i;
    f32 temp_ft0;
    f32 temp_fv0;

    temp_fv0 = func_80045DD0(item->unk_64, item->unk_68);
    temp_ft0 = func_80045E48(temp_fv0);
    item->unk_64 = temp_fv0;

    for (i = 0; i < ARRAY_COUNTU(item->color.arr); i++) {
        item->color.arr[i] = item->unk_6C[0][i] + ((item->unk_6C[1][i] - item->unk_6C[0][i]) * temp_ft0);
    }
}

/**
 * Original name: colorFunc_cursor
 */
void colorFunc_cursor(MenuItem *item) {
    s32 i;
    f32 temp_fv0;
    f32 temp_fv0_2;

    temp_fv0 = func_80045E18(item->unk_64, item->unk_68);
    temp_fv0_2 = (sinf(2 * DOUBLE_LITERAL(M_PI) * temp_fv0) + DOUBLE_LITERAL(1)) * DOUBLE_LITERAL(0.5);
    item->unk_64 = temp_fv0;

    for (i = 0; i < ARRAY_COUNTU(item->color.arr); i++) {
        item->color.arr[i] = item->unk_6C[0][i] + (item->unk_6C[1][i] - item->unk_6C[0][i]) * temp_fv0_2;
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
void menuItem_init(MenuItem *item, s32 xPos, s32 yPos) {
    u32 i;

    item->unk_00[0] = 0.0f;
    item->unk_00[1] = 0.0f;

    item->transCallback = transFunc_curve;

    item->unk_24[0] = xPos;
    item->unk_1C[0] = xPos;
    item->pos[0] = xPos;

    item->unk_24[1] = yPos;
    item->unk_1C[1] = yPos;
    item->pos[1] = yPos;

    item->scaleCallback = scaleFunc_curve;
    item->unk_14 = 1.0f;
    item->unk_18 = 0.125f;
    item->unk_38 = 1.0f;
    item->unk_3C = 0.125f;

    for (i = 0; i < 2U; i++) {
        item->unk_30[i] = 1.0f;
        item->unk_40[i] = 0.0f;
        item->unk_48[i] = 1.0f;
    }

    item->colorCallback = colorFunc_curve;
    item->unk_64 = 1.0f;
    item->unk_68 = 0.125f;

    for (i = 0; i < 4U; i++) {
        item->color.arr[i] = 1.0f;
        item->unk_6C[0][i] = color_251[i];
        item->unk_6C[1][i] = 1.0f;
    }

    item->unk_8C.b.unk_31 = false;
    item->unk_8C.b.unk_30 = false;
}

/**
 * Original name: menuItem_updateTransScale
 */
void menuItem_updateTransScale(MenuItem *item, MenuItem *parent) {
    u32 i;

    item->transCallback(item);
    item->scaleCallback(item);

    if (parent == NULL) {
        return;
    }

    for (i = 0; i < 2U; i++) {
        f32 temp_ft0;

        item->pos[i] = item->pos[i] * parent->unk_30[i] + parent->pos[i];

        temp_ft0 = item->unk_30[i] * parent->unk_30[i];
        item->unk_30[i] = temp_ft0;
        item->pos[i] = item->pos[i] - (item->unk_00[i] * temp_ft0);
    }
}

/**
 * Original name: menuItem_updateColor
 */
void menuItem_updateColor(MenuItem *item, MenuItem *parent) {
    s32 i;

    item->colorCallback(item);

    if (parent == NULL) {
        return;
    }

    if (!item->unk_8C.b.unk_31) {
        for (i = 0; i < 3U; i++) {
            item->color.arr[i] *= parent->color.arr[i];
        }
    }

    if (!item->unk_8C.b.unk_30) {
        for (i = 3; i < 4U; i++) {
            item->color.arr[i] *= parent->color.arr[i];
        }
    }
}

/**
 * menuItem_updateTransScaleColor?
 */
void func_800464BC(MenuItem *item, MenuItem *parent) {
    menuItem_updateTransScale(item, parent);
    menuItem_updateColor(item, parent);
}

void func_800464F8(MenuItem items[], s32 count, MenuItem *parent) {
    s32 i;

    for (i = 0; i < count; i++) {
        func_800464BC(&items[i], parent);
    }
}

void func_8004655C(MenuItem *item, s32 arg1) {
    if (((arg1 < 0) && (item->unk_18 > 0.0f)) || ((arg1 > 0) && (item->unk_18 < 0.0f))) {
        item->unk_18 = -item->unk_18;
    }
}

void func_800465B8(MenuItem *item, s32 arg1) {
    if (((arg1 < 0) && (item->unk_3C > 0.0f)) || ((arg1 > 0) && (item->unk_3C < 0.0f))) {
        item->unk_3C = -item->unk_3C;
    }
}

void func_80046614(MenuItem *item, s32 arg1) {
    if (((arg1 < 0) && (item->unk_68 > 0.0f)) || ((arg1 > 0) && (item->unk_68 < 0.0f))) {
        item->unk_68 = -item->unk_68;
    }
}

void func_80046670(MenuItem *item, f32 arg1, f32 arg2) {
    item->unk_1C[0] = arg1;
    item->unk_1C[1] = arg2;
}

void func_8004667C(MenuItem *item, f32 arg1, f32 arg2) {
    item->unk_24[0] = arg1;
    item->unk_24[1] = arg2;
}

void func_80046688(MenuItem *item, f32 arg1, f32 arg2) {
    item->unk_40[0] = arg1;
    item->unk_40[1] = arg2;
}

void func_80046694(MenuItem *item, f32 arg1, f32 arg2) {
    item->unk_48[0] = arg1;
    item->unk_48[1] = arg2;
}

void func_800466A0(MenuItem *item, f32 arg1, f32 arg2) {
    item->unk_6C[0][3] = arg2;
    item->unk_6C[0][2] = arg1;
    item->unk_6C[0][1] = arg1;
    item->unk_6C[0][0] = arg1;
}

void func_800466B8(MenuItem *item, f32 arg0, f32 arg1) {
    item->unk_6C[1][3] = arg1;
    item->unk_6C[1][2] = arg0;
    item->unk_6C[1][1] = arg0;
    item->unk_6C[1][0] = arg0;
}

void func_800466D0(MenuItem *item) {
    item->colorCallback = colorFunc_cursor;
    item->unk_68 = 1.0f / 32.0f;
    func_800466A0(item, 0.5f, 1.0f);
    func_800466B8(item, 1.0f, 1.0f);
}

void func_80046734(MenuItem *item, f32 arg0, f32 arg1, f32 arg2) {
    f32 sp10[] = { arg0, arg1, arg2 };
    s32 i;

    item->unk_68 = 1.0f / 32.0f;
    item->colorCallback = colorFunc_cursor;
    func_800466A0(item, 0.5f, 1.0f);
    func_800466B8(item, 1.0f, 1.0f);

    for (i = 0; i < ARRAY_COUNT(sp10); i++) {
        item->unk_6C[0][i] *= sp10[i];
        item->unk_6C[1][i] = item->unk_6C[1][i] * sp10[i];
    }
}

void func_800467E0(MenuItem *item) {
    item->colorCallback = colorFunc_curve;
    item->unk_68 = 0.125f;
    func_800466A0(item, 1.0f, 0.0f);
    func_800466B8(item, 1.0f, 1.0f);
}

void func_80046844(MenuItem *item, Gfx **gfxP) {
    Gfx *gfx = *gfxP;
    Color_RGBA32 color = {
        CLAMP(item->color.v.r, 0.0f, 1.0f) * 255,
        CLAMP(item->color.v.g, 0.0f, 1.0f) * 255,
        CLAMP(item->color.v.b, 0.0f, 1.0f) * 255,
        CLAMP(item->color.v.a, 0.0f, 1.0f) * 255,
    };

    gDPSetPrimColor(gfx++, 0, 0, color.r, color.g, color.b, color.a);

    *gfxP = gfx;
}

/**
 * Original name: menuItem_outOfScreen
 */
bool menuItem_outOfScreen(MenuItem *item, s32 arg1, s32 arg2) {
    if ((item->color.v.a <= 0) || (item->pos[0] >= SCREEN_WIDTH) || (item->pos[1] >= SCREEN_HEIGHT) ||
        (item->pos[0] + arg1 * item->unk_30[0] < 0) || (item->pos[1] + arg2 * item->unk_30[1] < 0) ||
        (item->unk_30[0] == 0.0f) || (item->unk_30[1] == 0.0f)) {
        return true;
    }
    return false;
}

/**
 * Original name: menuItem_drawTex
 */
bool menuItem_drawTex(MenuItem *item, Gfx **gfxP, TiTexData *arg2, bool cached) {
    if (menuItem_outOfScreen(item, arg2->info[TI_INFO_IDX_WIDTH], arg2->info[TI_INFO_IDX_HEIGHT])) {
        return false;
    }

    func_80046844(item, gfxP);
    if (arg2->info[TI_INFO_IDX_FLAGS] & TITEX_FLAGS_BLOCK) {
        tiStretchTexBlock(gfxP, arg2, cached, item->pos[0], item->pos[1],
                          arg2->info[TI_INFO_IDX_WIDTH] * item->unk_30[0],
                          arg2->info[TI_INFO_IDX_HEIGHT] * item->unk_30[1]);
    } else {
        tiStretchTexTile(gfxP, arg2, cached, 0, 0, arg2->info[TI_INFO_IDX_WIDTH], arg2->info[TI_INFO_IDX_HEIGHT],
                         item->pos[0], item->pos[1], arg2->info[TI_INFO_IDX_WIDTH] * item->unk_30[0],
                         arg2->info[TI_INFO_IDX_HEIGHT] * item->unk_30[1]);
    }
    return true;
}

bool func_80046C74(MenuItem *item, Gfx **gfxP, TiTexData *arg2, bool cached, f32 arg4, f32 arg5, f32 arg6, f32 arg7) {
    f32 sp28[4] = {
        item->pos[0],
        item->pos[1],
        item->unk_30[0],
        item->unk_30[1],
    };
    bool drawn;

    item->pos[0] += arg4;
    item->pos[1] += arg5;
    item->unk_30[0] *= arg6;
    item->unk_30[1] *= arg7;

    drawn = menuItem_drawTex(item, gfxP, arg2, cached);

    item->pos[0] = sp28[0];
    item->pos[1] = sp28[1];
    item->unk_30[0] = sp28[2];
    item->unk_30[1] = sp28[3];

    return drawn;
}

/**
 * Original name: menuItem_drawAlphaTex
 */
bool menuItem_drawAlphaTex(MenuItem *item, Gfx **gfxP, TiTexData *arg2, TiTexData *arg3, s32 arg4) {
    const Texture *sp48[2];
    s32 var_s0;
    s32 var_s1;

    var_s0 = MIN(arg2->info[TI_INFO_IDX_WIDTH], arg3->info[TI_INFO_IDX_WIDTH]);
    var_s1 = MIN(arg2->info[TI_INFO_IDX_HEIGHT], arg3->info[TI_INFO_IDX_HEIGHT]);

    if (menuItem_outOfScreen(item, var_s0, var_s1)) {
        return false;
    }

    func_80046844(item, gfxP);

    if (arg4 != 0) {
        sp48[0] = NULL;
        sp48[1] = NULL;
    } else {
        sp48[0] = arg2->texs[TI_TEX_TEX];
        sp48[1] = arg3->texs[TI_TEX_TEX];
    }

    if ((arg2->info[TI_INFO_IDX_FLAGS] & TITEX_FLAGS_BLOCK) && (arg3->info[TI_INFO_IDX_FLAGS] & TITEX_FLAGS_BLOCK)) {
        StretchAlphaTexBlock(gfxP, var_s0, var_s1, sp48[0], arg2->info[TI_INFO_IDX_WIDTH], sp48[1],
                             arg3->info[TI_INFO_IDX_WIDTH], item->pos[0], item->pos[1], var_s0 * item->unk_30[0],
                             var_s1 * item->unk_30[1]);
    } else {
        StretchAlphaTexTile(gfxP, var_s0, var_s1, arg2->texs[TI_TEX_TEX], arg2->info[TI_INFO_IDX_WIDTH],
                            arg3->texs[TI_TEX_TEX], arg3->info[TI_INFO_IDX_WIDTH], 0, 0, var_s0,
                            arg2->info[TI_INFO_IDX_HEIGHT], item->pos[0], item->pos[1], var_s0 * item->unk_30[0],
                            var_s1 * item->unk_30[1]);
    }

    return true;
}

s32 func_80046F58(MenuItem *item, Gfx **gfxP, TiTexData *arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 temp_lo = arg2->info[TI_INFO_IDX_HEIGHT] / arg4;

    if (menuItem_outOfScreen(item, arg2->info[TI_INFO_IDX_WIDTH], temp_lo)) {
        return 0;
    }

    func_80046844(item, gfxP);
    tiStretchTexItem(gfxP, arg2, arg3, arg4, arg5, item->pos[0], item->pos[1],
                     arg2->info[TI_INFO_IDX_WIDTH] * item->unk_30[0], temp_lo * item->unk_30[1]);
    return 1;
}

void func_80047074(MenuItem *item, Gfx **gfxP, TiTexData *arg2, s32 arg3, s32 arg4, s32 arg5, f32 arg6, f32 arg7,
                   f32 arg8, f32 arg9) {
    f32 sp20[4] = {
        item->pos[0],
        item->pos[1],
        item->unk_30[0],
        item->unk_30[1],
    };

    item->pos[0] += arg6;
    item->pos[1] += arg7;
    item->unk_30[0] *= arg8;
    item->unk_30[1] *= arg9;
    func_80046F58(item, gfxP, arg2, arg3, arg4, arg5);
    item->pos[0] = sp20[0];
    item->pos[1] = sp20[1];
    item->unk_30[0] = sp20[2];
    item->unk_30[1] = sp20[3];
}

bool func_8004714C(MenuItem *item, Gfx **gfxP, TiTexData *arg2, TiTexData *arg3, bool cached, s32 arg5, s32 arg6) {
    s32 var_s1 = MIN(arg2->info[TI_INFO_IDX_WIDTH], arg3->info[TI_INFO_IDX_WIDTH]);
    s32 temp_lo = MIN(arg2->info[TI_INFO_IDX_HEIGHT], arg3->info[TI_INFO_IDX_HEIGHT]) / arg5;

    if (menuItem_outOfScreen(item, var_s1, temp_lo)) {
        return false;
    }

    func_80046844(item, gfxP);
    tiStretchAlphaTexItem(gfxP, arg2, arg3, cached, arg5, arg6, item->pos[0], item->pos[1], var_s1 * item->unk_30[0],
                          temp_lo * item->unk_30[1]);
    return true;
}

bool func_800472D0(MenuItem *item, Gfx **gfxP, TiTexData *arg2, TiTexData *arg3, bool cached, s32 arg5, s32 arg6) {
    s32 var_s1 = MIN(arg2->info[TI_INFO_IDX_WIDTH], arg3->info[TI_INFO_IDX_WIDTH]);
    s32 var_s0 = MIN(arg2->info[TI_INFO_IDX_HEIGHT] / arg5, arg3->info[TI_INFO_IDX_HEIGHT]);

    if (menuItem_outOfScreen(item, var_s1, var_s0)) {
        return false;
    }

    func_80046844(item, gfxP);
    tiStretchAlphaTexItem2(gfxP, arg2, arg3, cached, arg5, arg6, item->pos[0], item->pos[1], var_s1 * item->unk_30[0],
                           var_s0 * item->unk_30[1]);
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
const u8 _gameLvItemColor[][MENUITEM_UNK_LEN3][MENUITEM_UNK_LEN4] = {
    { { 0, 0, 0, 80 }, { 128, 160, 255, 200 } },
    { { 0, 0, 0, 80 }, { 255, 255, 64, 200 } },
    { { 0, 0, 0, 80 }, { 255, 144, 64, 200 } },
};
static_assert(ARRAY_COUNT(_gameLvItemColor) == MENUSPEEDITEM_UNK_LEN, "");

/**
 * Original name: _musicItemColor
 */
const u8 _musicItemColor[][MENUITEM_UNK_LEN4] = {
    { 0, 0, 0, 80 },
    { 255, 160, 200, 200 },
};
static_assert(ARRAY_COUNT(_musicItemColor) == MENUITEM_UNK_LEN3, "");

/**
 * Original name: menuTitle_setTitle
 */
void menuTitle_setTitle(struct_watchMenu_unk_02548 *arg0, MainMenuMode arg1) {
    s32 var_a2 = -1;

    switch (arg1) {
        case MAINMENUMODE_MENUMAIN_0:
        case MAINMENUMODE_1:
        case MAINMENUMODE_22:
        case MAINMENUMODE_35:
        case MAINMENUMODE_36:
        case MAINMENUMODE_37:
        case MAINMENUMODE_38:
        case MAINMENUMODE_39:
            var_a2 = 0;
            break;

        case MAINMENUMODE_46:
        case MAINMENUMODE_59:
        case MAINMENUMODE_60:
        case MAINMENUMODE_61:
        case MAINMENUMODE_62:
        case MAINMENUMODE_MENUNMENT_63:
        case MAINMENUMODE_MENUNMENT_64:
        case MAINMENUMODE_65:
        case MAINMENUMODE_67:
        case MAINMENUMODE_68:
        case MAINMENUMODE_70:
        case MAINMENUMODE_71:
        case MAINMENUMODE_72:
        case MAINMENUMODE_73:
            var_a2 = 1;
            break;

        case MAINMENUMODE_11:
        case MAINMENUMODE_MENUNMENT_12:
        case MAINMENUMODE_MENULVSEL_13:
        case MAINMENUMODE_31:
        case MAINMENUMODE_MENUNMENT_32:
        case MAINMENUMODE_MENUCHSEL_33:
        case MAINMENUMODE_MENUPLAY2_34:
            var_a2 = 2;
            break;

        case MAINMENUMODE_MENUCHSEL_42:
        case MAINMENUMODE_MENUPLAY2_43:
            var_a2 = 3;
            break;

        case MAINMENUMODE_47:
        case MAINMENUMODE_48:
        case MAINMENUMODE_MENURANK_49:
        case MAINMENUMODE_MENURANK_50:
        case MAINMENUMODE_MENURANK_51:
        case MAINMENUMODE_MENURANK_52:
        case MAINMENUMODE_MENURANK_53:
        case MAINMENUMODE_MENURANK_54:
        case MAINMENUMODE_MENURANK_55:
        case MAINMENUMODE_MENURANK_56:
        case MAINMENUMODE_MENURANK_57:
        case MAINMENUMODE_MENURANK_58:
            var_a2 = 4;
            break;

        case MAINMENUMODE_5:
        case MAINMENUMODE_MENUNMENT_6:
        case MAINMENUMODE_MENULVSEL_7:
            var_a2 = 5;
            break;

        case MAINMENUMODE_2:
        case MAINMENUMODE_MENUNMENT_3:
        case MAINMENUMODE_MENUSTORY_4:
            var_a2 = 6;
            break;

        case MAINMENUMODE_MENUCHSEL_40:
        case MAINMENUMODE_MENUPLAY2_41:
            var_a2 = 7;
            break;

        case MAINMENUMODE_14:
        case MAINMENUMODE_MENUNMENT_15:
        case MAINMENUMODE_MENUCHSEL_16:
        case MAINMENUMODE_MENUPLAY2_17:
            var_a2 = 8;
            break;

        case MAINMENUMODE_23:
        case MAINMENUMODE_MENUNMENT_24:
        case MAINMENUMODE_MENUCHSEL_25:
        case MAINMENUMODE_MENUPLAY2_26:
            var_a2 = 9;
            break;

        case MAINMENUMODE_18:
        case MAINMENUMODE_MENUNMENT_19:
        case MAINMENUMODE_MENUCHSEL_20:
        case MAINMENUMODE_MENUPLAY2_21:
        case MAINMENUMODE_27:
        case MAINMENUMODE_MENUNMENT_28:
        case MAINMENUMODE_MENUCHSEL_29:
        case MAINMENUMODE_MENUPLAY2_30:
        case MAINMENUMODE_MENUCHSEL_44:
        case MAINMENUMODE_MENUPLAY2_45:
            var_a2 = 0xA;
            break;

        case MAINMENUMODE_8:
        case MAINMENUMODE_MENUNMENT_9:
        case MAINMENUMODE_MENULVSEL_10:
            var_a2 = 0xB;
            break;

        default:
            break;
    }

    if (arg0->unk_08[arg0->unk_04] != var_a2) {
        arg0->unk_04 = INC_WRAP(arg0->unk_04, ARRAY_COUNT(arg0->unk_08));
        arg0->unk_10[arg0->unk_04].unk_64 = 0.0f;
        arg0->unk_08[arg0->unk_04] = var_a2;
    }
}

void func_800474EC(struct_watchMenu_unk_02548 *arg0, struct_watchMenu *watchMenuRef, s32 arg2, s32 arg3) {
    s32 i;

    arg0->watchMenuRef = watchMenuRef;
    arg0->unk_04 = 0;
    arg0->unk_08[0] = -1;
    arg0->unk_08[1] = -1;

    for (i = 0; i < ARRAY_COUNTU(arg0->unk_10); i++) {
        menuItem_init(&arg0->unk_10[i], arg2, arg3);
        func_800467E0(&arg0->unk_10[i]);
    }
}

void func_80047584(struct_watchMenu_unk_02548 *arg0, MenuItem *item) {
    func_800464F8(arg0->unk_10, 2, item);
}

/**
 * Original name: menuTitle_draw
 */
void menuTitle_draw(struct_watchMenu_unk_02548 *arg0, Gfx **gfxP) {
    Gfx *gfx = *gfxP;
    s32 var_s0;
    TiTexData *temp_s6;

    gSPDisplayList(gfx++, fade_normal_texture_init_dl);
    temp_s6 = _getTexCommon(arg0->watchMenuRef, 0xF);

    for (var_s0 = 0; var_s0 < 2U; var_s0++) {
        s32 temp_a1 = (arg0->unk_04 + var_s0 + 1) % 2U;
        MenuItem *item;

        if (arg0->unk_08[temp_a1] < 0) {
            continue;
        }

        item = &arg0->unk_10[temp_a1];
        if (item->color.v.a == 1.0f) {
            gDPSetRenderMode(gfx++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
        } else {
            gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
        }
        func_80046F58(&arg0->unk_10[temp_a1], &gfx, temp_s6, 0, 0xC, arg0->unk_08[temp_a1]);
    }

    *gfxP = gfx;
}

/**
 * Original name: _menuCursor_cursor_4_pattern
 */
const s32 _menuCursor_cursor_4_pattern[] = {
    0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0,
};

void func_80047720(MenuCursor *cursor, s32 arg1, s32 arg2) {
    MenuItem *item = &cursor->unk_140;

    item->transCallback = transFunc_finger;
    item->unk_18 = 1.0f / 32.0f;
    func_8004667C(item, arg1, arg2);
    func_80046670(item, arg1 - 8, arg2);
}

void func_800477BC(MenuCursor *cursor, s32 arg1, s32 arg2) {
    func_8004667C(&cursor->unk_1D0, arg1, arg2);
    func_80046670(&cursor->unk_1D0, arg1, arg2);
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
void menuCursor_init2(MenuCursor *cursor, struct_watchMenu *watchMenuRef, u32 arg2, s32 arg3, s32 arg4, s32 arg5,
                      s32 arg6, s32 arg7, s32 arg8, s32 arg9) {
    MenuItem *item;
    s32 i;

    if (arg2 < 2U) {
        arg2 = 3;
    }

    cursor->watchMenuRef = watchMenuRef;
    cursor->unk_004 = arg2;
    cursor->unk_008 = arg3;
    cursor->unk_00C = arg4;
    cursor->unk_010 = arg5;
    cursor->unk_014 = arg8;
    cursor->unk_018 = arg9;

    cursor->unk_01C.b.unk_31 = true;
    cursor->unk_01C.b.unk_30 = false;
    cursor->unk_01C.b.unk_29 = false;
    cursor->unk_01C.b.unk_28 = true;

    menuItem_init(&cursor->unk_020, arg6, arg7);

    item = &cursor->unk_0B0;
    menuItem_init(item, 0, 0);
    func_80046734(item, _color_1040[arg5 % ARRAY_COUNTU(_color_1040)][0],
                  _color_1040[arg5 % ARRAY_COUNTU(_color_1040)][1], _color_1040[arg5 % ARRAY_COUNTU(_color_1040)][2]);
    if (arg2 == 3) {
        for (i = 0; i < ARRAY_COUNTU(item->unk_6C[0]); i++) {
            item->unk_6C[0][i] = item->unk_6C[1][i];
        }
    }

    menuItem_init(&cursor->unk_140, 0, 0);
    func_80047720(cursor, -0x14, arg9 - 0xE);

    menuItem_init(&cursor->unk_1D0, 0, 0);
    func_800477BC(cursor, -0x10, arg9 - 0x16);
}

void func_800479A8(MenuCursor *cursor, struct_watchMenu *watchMenuRef, u32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6,
                   s32 arg7) {
    menuCursor_init2(cursor, watchMenuRef, arg2, 4, 0, arg3, arg4, arg5, arg6, arg7);
}

/**
 * Original name: menuCursor_update
 */
void menuCursor_update(MenuCursor *cursor, MenuItem *arg1) {
    MenuItem *var_a0;
    s32 i;

    func_800464BC(&cursor->unk_020, arg1);
    var_a0 = &cursor->unk_0B0;
    func_800464BC(var_a0, &cursor->unk_020);
    if (!cursor->unk_01C.b.unk_28) {
        for (i = 0; i < 4U; i++) {
            var_a0->color.arr[i] = var_a0->unk_6C[1][i] * arg1->color.arr[i];
        }
    }

    func_800464BC(&cursor->unk_140, &cursor->unk_020);
    func_800464BC(&cursor->unk_1D0, &cursor->unk_020);
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
void menuCursor_draw1(MenuCursor **cursorArr, s32 count, Gfx **gxfP) {
    Gfx *gfx = *gxfP;
    s32 i;

    gSPDisplayList(gfx++, fade_normal_texture_init_dl);
    gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gDPSetTextureLUT(gfx++, G_TT_NONE);

    for (i = 0; i < 9; i++) {
        s32 j;
        s32 sp6C;
        s32 var_s0;
        s32 var_s7;
        s32 var_s3;

        switch (i) {
            case 0x0:
                var_s0 = 8;
                var_s3 = 4;
                break;

            case 0x1:
                var_s0 = 6;
                var_s3 = 3;
                break;

            case 0x2:
                var_s0 = 7;
                var_s3 = 0x10;
                break;

            case 0x3:
                var_s3 = 0x10;
                sp6C = -1;
                break;

            case 0x4:
                var_s0 = 9;
                break;

            case 0x5:
                var_s0 = 0xA;
                break;

            case 0x6:
                var_s0 = 0xB;
                break;

            case 0x7:
                var_s0 = 0xC;
                break;

            case 0x8:
                var_s0 = 0xD;
                break;
        }

        var_s7 = 0;

        for (j = 0; j < count; j++) {
            MenuCursor *cursor = cursorArr[j];
            MenuItem *item = &cursor->unk_0B0;
            TiTexData *var_s5;
            s32 var_a0;
            s32 sp18[4];
            s32 sp28[4];
            s32 sp38[3];
            s32 sp48[3];
            s32 sp58[3];

            if (!cursor->unk_01C.b.unk_31) {
                continue;
            }

            if ((i != cursor->unk_004) || menuItem_outOfScreen(item, cursor->unk_014, cursor->unk_018)) {
                continue;
            }

            if (i == 3) {
                if (cursor->unk_01C.b.unk_28) {
                    var_s0 = item->unk_64 * (ARRAY_COUNT(_menuCursor_cursor_4_pattern) - 1);
                    var_s0 = _menuCursor_cursor_4_pattern[var_s0] + 3;
                } else {
                    var_s0 = 3;
                }

                if (var_s0 != sp6C) {
                    sp6C = var_s0;
                    var_s7 = 0;
                }
            }

            if (var_s7 == 0) {
                var_s5 = _getTexCommon(cursor->watchMenuRef, var_s0);

                gDPLoadTextureBlock_4b(gfx++, var_s5->texs[TI_TEX_TEX], G_IM_FMT_I, var_s5->info[TI_INFO_IDX_WIDTH],
                                       var_s5->info[TI_INFO_IDX_HEIGHT], 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK,
                                       G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
                var_s7 += 1;
            }

            func_80046844(item, &gfx);

            if (i == 3) {
                var_a0 = cursor->unk_014 + var_s3;
                sp18[0] = (item->pos[0] * 4.0f) - (f32)(var_s3 * 2);
            } else {
                var_a0 = cursor->unk_014;
                sp18[0] = item->pos[0] * 4.0f;
            }

            var_s0 = MIN(var_s3, var_a0 / 2);

            sp18[3] = sp18[0] + (s32)(item->unk_30[0] * 4.0f * var_a0);
            sp18[1] = sp18[0] + (s32)(item->unk_30[0] * 4.0f * var_s0);
            sp18[2] = sp18[3] - (s32)(item->unk_30[0] * 4.0f * var_s0);

            sp38[0] = 0;
            sp38[1] = (var_s0 - 1) << 5;
            sp38[2] = var_s0 << 5;

            if (i == 3) {
                var_a0 = cursor->unk_018 + var_s3;
                sp28[0] = (item->pos[1] * 4.0f) - (f32)(var_s3 * 2);
            } else {
                var_a0 = cursor->unk_018;
                sp28[0] = item->pos[1] * 4.0f;
            }

            var_s0 = MIN(var_s3, var_a0 / 2);

            sp28[3] = sp28[0] + (s32)(item->unk_30[1] * 4.0f * var_a0);
            sp28[1] = sp28[0] + (s32)(item->unk_30[1] * 4.0f * var_s0);
            sp28[2] = sp28[3] - (s32)(item->unk_30[1] * 4.0f * var_s0);

            sp48[0] = 0;
            sp48[1] = (var_s0 - 1) << 5;
            sp48[2] = var_s0 << 5;

            sp58[0] = -0x400;
            sp58[1] = 0;
            sp58[2] = 0x400;

            if (i < 4) {
                for (var_s0 = 0; var_s0 < ARRAY_COUNTU(_pnts_1106); var_s0++) {
                    // Cast the const away, needed for matching
                    s32 *pnts = (void *)_pnts_1106[var_s0];

                    gSPScisTextureRectangle(gfx++, sp18[pnts[0]], sp28[pnts[1]], sp18[pnts[2]], sp28[pnts[3]],
                                            G_TX_RENDERTILE, sp38[pnts[4]], sp48[pnts[5]], sp58[pnts[6]],
                                            sp58[pnts[7]]);
                }
            } else {
                s32 a = item->pos[0];
                s32 b = item->pos[1];
                s32 c = a + var_s5->info[TI_INFO_IDX_WIDTH];
                s32 d = b + var_s5->info[TI_INFO_IDX_HEIGHT];

                gSPScisTextureRectangle(gfx++, a << 2, b << 2, c << 2, d << 2, G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);
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
/**
 * Original name: menuCursor_draw2
 */
void menuCursor_draw2(MenuCursor **cursorArr, s32 count, Gfx **gxfP) {
    Gfx *gfx = *gxfP;
    MenuCursor *temp_s0;
    TiTexData *temp_s1;
    TiTexData *temp;
    bool cached;
    s32 i;
    s32 j;

    gSPDisplayList(gfx++, fade_alpha_texture_init_dl);

    cached = false;
    for (i = 0; i < count; i++) {
        temp_s0 = cursorArr[i];

        if (temp_s0->unk_01C.b.unk_30) {
            temp_s1 = _getTexCommon(temp_s0->watchMenuRef, 1);
            temp = _getTexCommon(temp_s0->watchMenuRef, 0);
            cached += menuItem_drawAlphaTex(&temp_s0->unk_140, &gfx, temp_s1, temp, cached);
        }
    }

    for (i = 0; cached = 0, i < 0xB; i++) {
        for (j = 0; j < count; j++) {
            s32 var_v1;

            temp_s0 = cursorArr[j];
            if ((temp_s0->unk_010 == 1) && (temp_s0->unk_008 == 1) && (temp_s0->unk_00C == 1)) {
                var_v1 = 10;
            } else {
                var_v1 = _type_1345[temp_s0->unk_008 - 1][temp_s0->unk_010];
            }

            if (!temp_s0->unk_01C.b.unk_29 || (i != var_v1)) {
                continue;
            }

            temp_s1 = _getTexSetup(temp_s0->watchMenuRef, 8);
            temp = _getTexSetup(temp_s0->watchMenuRef, 1);
            cached += func_8004714C(&temp_s0->unk_1D0, &gfx, temp_s1, temp, cached, 0xB, i);
        }
    }

    *gxfP = gfx;
}

void func_80048634(MenuCursor *cursorArr[], s32 count, Gfx **gxfP) {
    menuCursor_draw1(cursorArr, count, gxfP);
    menuCursor_draw2(cursorArr, count, gxfP);
}

void func_80048680(MenuBottle *bottle, struct_watchMenu *watchMenuRef, s32 arg2, s32 arg3) {
    bottle->watchMenuRef = watchMenuRef;
    bottle->level = 0;
    menuItem_init(&bottle->unk_08, arg2, arg3);
    menuItem_init(&bottle->unk_98, 4, 0x10);
}

void func_800486C8(MenuBottle *bottle, MenuItem *arg1) {
    func_800464BC(&bottle->unk_08, arg1);
    func_800464BC(&bottle->unk_98, &bottle->unk_08);
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
        MenuItem *item = &bottle->unk_98;
        TiTexData *temp_t1 = _getTexLevel(bottle->watchMenuRef, 0);
        s32 var_t7;
        s32 i;

        gDPLoadTLUT_pal16(gfx++, 0, temp_t1->texs[TI_TEX_TLUT]);
        gDPLoadTextureBlock_4b(gfx++, temp_t1->texs[TI_TEX_TEX], G_IM_FMT_CI, temp_t1->info[TI_INFO_IDX_WIDTH],
                               temp_t1->info[TI_INFO_IDX_HEIGHT], 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK,
                               G_TX_NOLOD, G_TX_NOLOD);

        func_80046844(item, &gfx);

        var_t7 = 0;
        for (i = 1; i < 4; i++) {
            const u16 *ptr = &cap_pos_1442[bottle->level][2];
            s32 var_t0 = (s32)item->pos[1] * 4;
            s32 j;

            for (j = 2; j < ARRAY_COUNT(cap_pos_1442[bottle->level]); j++) {
                s32 var_t2 = (s32)item->pos[0] * 4;
                s32 temp = *ptr;
                s32 k;

                for (k = 7; k >= 0; k--) {
                    if (((temp >> (k * 2)) & 3) == i) {
                        gSPScisTextureRectangle(gfx++, var_t2, var_t0, var_t2 + 0x14, var_t0 + 0x14, G_TX_RENDERTILE, 0,
                                                var_t7, 1 << 10, 1 << 10);
                    }
                    var_t2 += 0x14;
                }

                var_t0 += 0x14;
                ptr++;
            }

            var_t7 += 0xA0;
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
const s32 _type_1543[] = {
    8,
    7,
    7,
};

void func_80048B8C(MenuLvGauge *lvGauge, struct_watchMenu *watchMenuRef, s32 arg2, s32 arg3, s32 arg4, s32 arg5,
                   s32 arg6) {
    lvGauge->watchMenuRef = watchMenuRef;
    lvGauge->unk_004 = arg2;
    lvGauge->unk_008 = 0x14;
    lvGauge->unk_00C = arg4;
    menuItem_init(&lvGauge->unk_010, arg5, arg6);
    func_800479A8(&lvGauge->unk_0A0, watchMenuRef, _type_1543[arg2], arg3, -2, -2, _size_1542[arg2][0],
                  _size_1542[arg2][1]);
}

void func_80048C48(MenuLvGauge *lvGauge, s32 arg1) {
    u32 keyRep = _getKeyRep(lvGauge->watchMenuRef, arg1);
    s32 var_a0 = 0;
    s32 var_s0;

    if (keyRep & L_JPAD) {
        var_a0--;
    }
    if (keyRep & R_JPAD) {
        var_a0++;
    }

    var_s0 = CLAMP(lvGauge->unk_00C + var_a0, 0, lvGauge->unk_008);

    if (var_s0 != lvGauge->unk_00C) {
        dm_snd_play(SND_INDEX_63);
        lvGauge->unk_00C = var_s0;
    }
}

void func_80048CC8(MenuLvGauge *arg0, MenuItem *arg1) {
    MenuItem *item;

    func_800464BC(&arg0->unk_010, arg1);

    item = &arg0->unk_0A0.unk_020;
    item->unk_24[0] = item->unk_1C[0] + (_lvGauge_step[arg0->unk_004] * arg0->unk_00C);

    menuCursor_update(&arg0->unk_0A0, &arg0->unk_010);
}

/**
 * Original name: menuLvGauge_draw1
 */
void menuLvGauge_draw1(MenuLvGauge **lvGaugeP, s32 count, Gfx **gxfP) {
    Gfx *gfx = *gxfP;
    s32 i;

    gSPDisplayList(gfx++, fade_fillrect_init_dl);

    for (i = 0; i < count; i++) {
        MenuLvGauge *temp_a3 = lvGaugeP[i];
        s32 x = temp_a3->unk_010.pos[0] + _lvGauge_step[temp_a3->unk_004] * (temp_a3->unk_00C + 1);
        s32 y = temp_a3->unk_010.pos[1];
        s32 width = (0x14 - temp_a3->unk_00C) * _lvGauge_step[temp_a3->unk_004];
        s32 height = temp_a3->unk_0A0.unk_018 - 3;

        if (temp_a3->unk_004 == 0) {
            y--;
            height++;
        }

        gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, 160);
        gDPScisFillRectangle(gfx++, x, y, x + width, y + height);

        if (temp_a3->unk_008 > 0x14) {
            x = temp_a3->unk_010.pos[0] + _lvGauge_step[temp_a3->unk_004] * 21.0f;
            y = temp_a3->unk_010.pos[1] - 1.0f;
            width = (temp_a3->unk_008 - MAX(0x14, temp_a3->unk_00C)) * _lvGauge_step[temp_a3->unk_004];
            height = temp_a3->unk_0A0.unk_018 - 1;

            gDPScisFillRectangle(gfx++, x, y, x + width, y + height);
        }
    }

    *gxfP = gfx;
}

void func_80048FA0(MenuLvGauge **lvGaugeP, s32 count, Gfx **gxfP) {
    Gfx *gfx = *gxfP;
    MenuCursor *sp10[count];
    s32 i;

    for (i = 0; i < count; i++) {
        sp10[i] = &lvGaugeP[i]->unk_0A0;
    }

    func_80048634(sp10, count, &gfx);

    *gxfP = gfx;
}

void func_80049034(MenuLvGauge *lvGaugeArr[], s32 count, Gfx **gfxP) {
    menuLvGauge_draw1(lvGaugeArr, count, gfxP);
    func_80048FA0(lvGaugeArr, count, gfxP);
}

void func_80049080(MenuYN *yn, s32 arg1, f32 arg2) {
    MenuItem *item = &yn->unk_008;

    func_80046614(item, arg1);
    item->unk_64 = arg2;
}

void func_800490B8(MenuYN *yn, s32 arg1) {
    func_80049080(yn, arg1, yn->unk_008.unk_64);
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
void menuYN_init(MenuYN *yn, struct_watchMenu *watchMenuRef, s32 arg2, s32 arg3) {
    MenuItem *item;
    s32 i;
    f32 a2;

    yn->watchMenuRef = watchMenuRef;
    yn->unk_004 = 0;
    menuItem_init(&yn->unk_008, arg2, arg3);
    func_800467E0(&yn->unk_008);

    for (i = 0; i < ARRAY_COUNTU(yn->unk_098); i++) {
        menuItem_init(&yn->unk_098[i], _yn_1691[i][0], _yn_1691[i][1]);
    }

    func_800479A8(&yn->unk_1B8, watchMenuRef, 0, 0, -4, -4, 0x3C, 0x14);
    yn->unk_1B8.unk_01C.b.unk_30 = true;
    func_800479A8(&yn->unk_418, watchMenuRef, 2, 0, 0, 0, 0x50, 0x3C);

    item = &yn->unk_418.unk_0B0;
    item->colorCallback = colorFunc_curve;

    a2 = 0.0f;

    item->unk_6C[1][0] = a2;
    item->unk_6C[0][0] = a2;
    item->unk_6C[1][1] = a2;
    item->unk_6C[0][1] = a2;
    item->unk_6C[1][2] = a2;
    item->unk_6C[0][2] = a2;
    item->unk_6C[0][3] = a2;
    item->unk_6C[1][3] = 32.0f / 51.0f;
    func_80049080(yn, -1, a2);
}

/**
 * Original name: menuYN_input
 */
bool menuYN_input(MenuYN *yn, s32 arg1) {
    u32 keyTrg = _getKeyTrg(yn->watchMenuRef, arg1);
    s32 var_a2 = yn->unk_004;

    if ((yn->unk_008.unk_68 < 0.0f) || (yn->unk_008.unk_64 < 1.0f)) {
        return false;
    }

    if (keyTrg & U_JPAD) {
        var_a2--;
    }
    if (keyTrg & D_JPAD) {
        var_a2++;
    }

    var_a2 = WrapI(0, 2, var_a2);
    if (var_a2 != yn->unk_004) {
        yn->unk_004 = var_a2;
        dm_snd_play(SND_INDEX_64);
    }

    return true;
}

void func_800492D8(MenuYN *yn, MenuItem *parentItem) {
    func_800464BC(&yn->unk_008, parentItem);
    func_800464F8(yn->unk_098, ARRAY_COUNT(yn->unk_098), &yn->unk_008);
    menuCursor_update(&yn->unk_1B8, &yn->unk_098[yn->unk_004]);
    menuCursor_update(&yn->unk_418, &yn->unk_008);
}

#include "main_menu_yn.msg.inc"

/**
 * Original name: menuYN_draw
 */
void menuYN_draw(MenuYN *yn, Gfx **gfxP) {
    MenuItem *item = &yn->unk_008;
    MenuCursor *sp18;
    Gfx *gfx = *gfxP;
    s32 i;

    if (menuItem_outOfScreen(item, 0x50, 0x3C)) {
        return;
    }

    sp18 = &yn->unk_418;
    func_80048634(&sp18, 1, &gfx);

    gSPDisplayList(gfx++, fade_intensity_texture_init_dl);
    gDPSetTextureFilter(gfx++, G_TF_BILERP);

    gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, item->color.v.a * 255.0f);

    for (i = 0; i < ARRAY_COUNTU(_yn_1767); i++) {
        f32 var_fs0;
        s32 j;

        item = &yn->unk_098[i];
        var_fs0 = item->pos[0];

#if VERSION_US || VERSION_GW
        //! @bug: should be checking for nil character instead
        for (j = 0; j < _yn_1767[i][j]; j += 2)
#elif VERSION_CN
        for (j = 0; _yn_1767[i][j] != '\0'; j += 2)
#else
#error ""
#endif
        {
            fontXX_draw(&gfx, var_fs0, item->pos[1], 12.0f, 12.0f, &_yn_1767[i][j]);
            var_fs0 += 20.0f;
        }
    }

    sp18 = &yn->unk_1B8;
    func_80048634(&sp18, 1, &gfx);

    *gfxP = gfx;
}

void func_80049540(MenuMes *mes, s32 arg1, f32 arg2) {
    func_80046614(&mes->unk_004, arg1);
    mes->unk_004.unk_64 = arg2;
}

void func_80049578(MenuMes *mes, s32 arg1) {
    func_80049540(mes, arg1, mes->unk_004.unk_64);
}

/**
 * Original name: menuMes_init
 */
void menuMes_init(MenuMes *mes, struct_watchMenu *watchMenuRef, void **heapP, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    MessageWnd *msgWnd;
    MenuItem *item;
    void *heap = *heapP;
    f32 a2;

    mes->watchMenuRef = watchMenuRef;

    menuItem_init(&mes->unk_004, arg5, arg6);
    func_800467E0(&mes->unk_004);

    msgWnd_init(&mes->unk_094, heapP, arg3, arg4, arg5, arg6);

    //! FAKE: ?
    msgWnd = &mes->unk_094;

    mes->unk_094.centering = true;
    msgWnd->fntH = 0xC;
    mes->unk_094.fntW = 0xC;
    mes->unk_094.colStep = 6;
    mes->unk_094.rowStep = 0xE;
    func_800479A8(&mes->unk_174, watchMenuRef, 2, 0, -0x10, -0x10, mes->unk_094.colStep * arg3 * 2 + 0x20,
                  mes->unk_094.rowStep * arg4 + 0x20);

    item = &mes->unk_174.unk_0B0;
    item->colorCallback = colorFunc_curve;

    a2 = 0.0f;
    item->unk_6C[1][0] = a2;
    item->unk_6C[0][0] = a2;
    item->unk_6C[1][1] = a2;
    item->unk_6C[0][1] = a2;
    item->unk_6C[1][2] = a2;
    item->unk_6C[0][2] = a2;
    item->unk_6C[0][3] = a2;
    item->unk_6C[1][3] = 0.627451f;
    func_80049540(mes, -1, a2);

    *heapP = heap;
}

void func_8004970C(MenuMes *mes, const char *arg1) {
    msgWnd_clear(&mes->unk_094);
    msgWnd_addStr(&mes->unk_094, arg1);
    msgWnd_skip(&mes->unk_094);
}

void func_80049754(MenuMes *mes, MenuItem *parentItem) {
    func_800464BC(&mes->unk_004, parentItem);
    mes->unk_094.posX = mes->unk_004.pos[0];
    mes->unk_094.posY = mes->unk_004.pos[1];
    mes->unk_094.alpha = mes->unk_004.color.v.a * 255.0f;
    msgWnd_update(&mes->unk_094);
    menuCursor_update(&mes->unk_174, &mes->unk_004);
}

void func_800497D0(MenuMes *mes, Gfx **gfxP) {
    MenuCursor *sp10;
    Gfx *gfx;
    MessageWnd *msgWnd = &mes->unk_094;

    gfx = *gfxP;
    if (menuItem_outOfScreen(&mes->unk_004, (msgWnd->colSize - 2) * msgWnd->colStep + msgWnd->fntW + 0xC,
                             (msgWnd->rowSize - 1) * msgWnd->rowStep + msgWnd->fntH + 0xC)) {
        return;
    }

    sp10 = &mes->unk_174;
    func_80048634(&sp10, 1, &gfx);
    msgWnd_draw(msgWnd, &gfx);

    *gfxP = gfx;
}

/* menuSpeedAsk_init? */
void func_80049894(MenuSpeedAsk *arg0, struct_watchMenu *watchMenuRef, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    arg0->watchMenuRef = watchMenuRef;
    arg0->unk_4 = arg2;
    arg0->unk_8 = arg3;
    menuItem_init(&arg0->unk_C, arg4, arg5);
}

void func_800498C4(MenuSpeedAsk *arg0, MenuItem *arg1) {
    func_800464BC(&arg0->unk_C, arg1);
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
                MenuSpeedAsk *menuSpeedAsk = speedAskArr[k];

                if ((i == menuSpeedAsk->unk_4) && (j == menuSpeedAsk->unk_8)) {
                    TiTexData *temp_s0 = _getTexSetup(menuSpeedAsk->watchMenuRef, _tex_1865[menuSpeedAsk->unk_4][0]);
                    TiTexData *a3 = _getTexSetup(menuSpeedAsk->watchMenuRef, _tex_1865[menuSpeedAsk->unk_4][1]);

                    cached += func_8004714C(&menuSpeedAsk->unk_C, &gfx, temp_s0, a3, cached, _row_1866[i], j);
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
s32 _type_1949[] = {
    5,
    6,
    5,
    6,
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
void menuSpeedItem_init(MenuSpeedItem *speedItem, struct_watchMenu *watchMenuRef, s32 arg2, s32 arg3, s32 arg4,
                        s32 arg5, s32 arg6, s32 arg7) {
    s32 i;

    speedItem->watchMenuRef = watchMenuRef;
    speedItem->unk_004 = arg2;
    speedItem->unk_008 = arg4;
    speedItem->unk_00C = 1;
    speedItem->unk_010 = 0;
    menuItem_init(&speedItem->unk_014, arg5, arg6);

    for (i = 0; i < ARRAY_COUNTU(speedItem->unk_0A4); i++) {
        menuItem_init(&speedItem->unk_0A4[i], arg7 * i, 0);
    }

    for (i = 0; i < MENUSPEEDITEM_UNK_LEN; i++) {
        MenuItem *item = &speedItem->unk_254[i];
        s32 j;

        menuItem_init(item, _pos_1959[arg2][0], _pos_1959[arg2][1]);

        item->colorCallback = colorFunc_cursor;
        item->unk_68 = 1.0f / 32.0f;

        for (j = 0; j < MENUITEM_UNK_LEN3; j++) {
            s32 k;

            for (k = 0; k < MENUITEM_UNK_LEN4; k++) {
                item->unk_6C[j][k] = _gameLvItemColor[i][j][k] * (DOUBLE_LITERAL(1) / 0xFF);
            }
        }
    }

    func_800479A8(&speedItem->unk_404, watchMenuRef, _type_1949[arg2], arg3, -1, -1, _size_1948[arg2][0],
                  _size_1948[arg2][1]);
}

void func_80049C54(MenuSpeedItem *speedItem, s32 arg1) {
    u32 keyRep = _getKeyRep(speedItem->watchMenuRef, arg1);
    s32 var_s0;
    s32 temp;

    temp = 0;
    if (keyRep & L_JPAD) {
        temp--;
    }
    if (keyRep & R_JPAD) {
        temp++;
    }

    var_s0 = CLAMP(speedItem->unk_008 + temp, 0, 2U);
    if (var_s0 != speedItem->unk_008) {
        dm_snd_play(SND_INDEX_63);
        speedItem->unk_008 = var_s0;
    }
}

/**
 * Original name: menuSpeedItem_update
 */
void menuSpeedItem_update(MenuSpeedItem *arg0, MenuItem *arg1) {
    s32 i;

    func_800464BC(&arg0->unk_014, arg1);
    func_800464F8(arg0->unk_0A4, ARRAY_COUNT(arg0->unk_0A4), &arg0->unk_014);

    for (i = 0; i < MENUSPEEDITEM_UNK_LEN; i++) {
        MenuItem *var_a0 = &arg0->unk_254[i];
        f32 *var_a2;
        u32 j;

        func_800464BC(var_a0, &arg0->unk_0A4[i]);

        if (i == arg0->unk_008) {
            if (arg0->unk_00C == 0) {
                var_a2 = var_a0->unk_6C[1];
            } else {
                var_a2 = NULL;
            }

            for (j = 0; j < MENUITEM_UNK_LEN4; j++) {
                var_a0->unk_6C[0][j] = _gameLvItemColor[i][1][j] * (DOUBLE_LITERAL(1) / 0x1FF);
            }
        } else {
            var_a2 = var_a0->unk_6C[0];

            for (j = 0; j < MENUITEM_UNK_LEN4; j++) {
                var_a0->unk_6C[0][j] = _gameLvItemColor[i][0][j] * (DOUBLE_LITERAL(1) / 0xFF);
            }
        }

        if (var_a2 != NULL) {
            for (j = 0; j < 4U; j++) {
                var_a0->color.arr[j] = var_a2[j] * arg1->color.arr[j];
            }
        }
    }

    menuCursor_update(&arg0->unk_404, &arg0->unk_0A4[arg0->unk_008]);
}

/**
 * Original name: menuSpeedItem_draw1
 */
void menuSpeedItem_draw1(MenuSpeedItem **speedItemP, s32 count, Gfx **gfxP) {
    Gfx *gfx = *gfxP;
    TiTexData *var_s7;
    MenuSpeedItem *speedItem;
    MenuItem *item;
    s32 var_s6;
    s32 index;
    s32 i;
    s32 j;

    gSPDisplayList(gfx++, fade_normal_texture_init_dl);

    var_s6 = 0;
    for (index = 0; index < count; index++) {
        speedItem = speedItemP[index];
        item = &speedItem->unk_0A4[2];

        if ((speedItem->unk_004 == 3) && (speedItem->unk_010 != 0)) {
            var_s7 = _getTexSetup(speedItem->watchMenuRef, 15);
            var_s6 += menuItem_drawTex(item, &gfx, var_s7, var_s6);
        }
    }

    gSPDisplayList(gfx++, fade_intensity_texture_init_dl);

    var_s6 = 0;
    for (index = 0; index < count; index++) {
        speedItem = speedItemP[index];
        item = &speedItem->unk_254[2];

        if ((speedItem->unk_004 == 3) && (speedItem->unk_010 != 0)) {
            var_s7 = _getTexSetup(speedItem->watchMenuRef, 23);
            var_s6 += menuItem_drawTex(item, &gfx, var_s7, var_s6);
        }
    }

    for (i = 0; i < 4; i++) {
        for (j = 0; j < ARRAY_COUNTU(speedItem->unk_254); j++) {
            var_s6 = 0;
            if ((j == 2) && (speedItem->unk_004 == 3) && (speedItem->unk_010 != 0)) {
                continue;
            }

            for (index = 0; index < count; index++) {
                speedItem = speedItemP[index];
                item = &speedItem->unk_254[j];

                if (speedItem->unk_004 == i) {
                    switch (speedItem->unk_004) {
                        case 0:
                            var_s7 = _getTexP4(speedItem->watchMenuRef, j + 6);
                            break;

                        case 1:
                            var_s7 = _getTexSetup(speedItem->watchMenuRef, j + 24);
                            break;

                        case 2:
                            var_s7 = _getTexP4(speedItem->watchMenuRef, j + 3);
                            break;

                        case 3:
                            var_s7 = _getTexSetup(speedItem->watchMenuRef, j + 20);
                            break;
                    }

                    var_s6 += menuItem_drawTex(item, &gfx, var_s7, var_s6);
                }
            }
        }
    }

    *gfxP = gfx;
}

void func_8004A160(MenuSpeedItem **speedItemP, s32 count, Gfx **gxfP) {
    Gfx *gfx = *gxfP;
    MenuCursor *sp10[count];
    s32 i;

    for (i = 0; i < count; i++) {
        sp10[i] = &speedItemP[i]->unk_404;
    }

    menuCursor_draw2(sp10, count, &gfx);

    *gxfP = gfx;
}

void func_8004A1F4(MenuSpeedItem *speedItemArr[], s32 count, Gfx **gfxP) {
    menuSpeedItem_draw1(speedItemArr, count, gfxP);
    func_8004A160(speedItemArr, count, gfxP);
}

/**
 * Original name: menuMusicItem_init
 */
void menuMusicItem_init(MenuMusicItem *musicItem, struct_watchMenu *watchMenuRef, s32 arg2, s32 arg3, s32 arg4) {
    s32 i;

    musicItem->watchMenuRef = watchMenuRef;
    musicItem->unk_004 = arg2;
    musicItem->unk_008 = -1;
    musicItem->unk_00C.b.unk_31 = true;

    menuItem_init(&musicItem->unk_010, arg3, arg4);

    for (i = 0; i < ARRAY_COUNTU(musicItem->unk_0A0); i++) {
        menuItem_init(&musicItem->unk_0A0[i], 0x27 * i, 0);
    }

    for (i = 0; i < ARRAY_COUNTU(musicItem->unk_370); i++) {
        MenuItem *item = &musicItem->unk_370[i];
        s32 j;

        menuItem_init(item, -2, -2);
        item->colorCallback = colorFunc_cursor;
        item->unk_68 = 1.0f / 32.0f;

        for (j = 0; j < 2U; j++) {
            s32 k;

            for (k = 0; k < ARRAY_COUNTU(_musicItemColor[j]); k++) {
                item->unk_6C[j][k] = _musicItemColor[j][k] * (DOUBLE_LITERAL(1) / 255);
            }
        }
    }

    func_800479A8(&musicItem->unk_640, watchMenuRef, 5, 0, -1, -1, 0x25, 0x10);
    musicItem->unk_640.unk_01C.b.unk_31 = 0;
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
void menuMusicItem_input(MenuMusicItem *menuMusicItem, s32 arg1) {
    u32 keyRep = _getKeyRep(menuMusicItem->watchMenuRef, arg1);
    s32 temp2 = menuMusicItem->unk_008;
    s32 temp_a0 = menuMusicItem->unk_004;
    s32 temp = 0;
    s32 var_s0;

    if (temp2 != temp_a0) {
        if (temp_a0 < ARRAY_COUNTU(_seq_2327)) {
            dm_seq_play_fade(_seq_2327[temp_a0], 0x14);
        } else {
            dm_seq_stop();
        }
        menuMusicItem->unk_008 = menuMusicItem->unk_004;
    }

    if (keyRep & L_JPAD) {
        temp--;
    }
    if (keyRep & R_JPAD) {
        temp++;
    }

    var_s0 = CLAMP(menuMusicItem->unk_004 + temp, 0, 4);
    if (var_s0 != menuMusicItem->unk_004) {
        dm_snd_play(SND_INDEX_63);
        menuMusicItem->unk_004 = var_s0;
    }
}

/**
 * Original name: menuMusicItem_update
 */
void menuMusicItem_update(MenuMusicItem *menuMusicItem, MenuItem *arg1) {
    s32 i;

    func_800464BC(&menuMusicItem->unk_010, arg1);
    func_800464F8(menuMusicItem->unk_0A0, ARRAY_COUNT(menuMusicItem->unk_0A0), &menuMusicItem->unk_010);

    for (i = 0; i < 5U; i++) {
        MenuItem *temp_s0_2 = &menuMusicItem->unk_370[i];
        f32 *var_a1;
        s32 j;

        func_800464BC(temp_s0_2, &menuMusicItem->unk_0A0[i]);
        if (i == menuMusicItem->unk_004) {
            if (!menuMusicItem->unk_00C.b.unk_31) {
                var_a1 = temp_s0_2->unk_6C[1];
            } else {
                var_a1 = NULL;
            }

            for (j = 0; j < ARRAY_COUNTU(_musicItemColor[1]); j++) {
                temp_s0_2->unk_6C[0][j] = _musicItemColor[1][j] * (DOUBLE_LITERAL(1) / 0x1FF);
            }
        } else {
            var_a1 = temp_s0_2->unk_6C[0];
            for (j = 0; j < ARRAY_COUNTU(_musicItemColor[0]); j++) {
                temp_s0_2->unk_6C[0][j] = _musicItemColor[0][j] * (DOUBLE_LITERAL(1) / 0xFF);
            }
        }

        if (var_a1 != NULL) {
            for (j = 0; j < 4U; j++) {
                temp_s0_2->color.arr[j] = var_a1[j] * arg1->color.arr[j];
            }
        }
    }

    menuCursor_update(&menuMusicItem->unk_640, &menuMusicItem->unk_0A0[menuMusicItem->unk_004]);
}

/**
 * Original name: menuMusicItem_draw1
 */
void menuMusicItem_draw1(MenuMusicItem *musicItemArr[], s32 count, Gfx **gxfP) {
    Gfx *gfx = *gxfP;
    s32 i;
    s32 j;

    gSPDisplayList(gfx++, fade_intensity_texture_init_dl);

    for (j = 0; j < ARRAY_COUNTU((*musicItemArr)->unk_370); j++) {
        s32 var_s3 = 0;

        for (i = 0; i < count; i++) {
            MenuMusicItem *musicItem = musicItemArr[i];
            MenuItem *item = &musicItem->unk_370[j];

            var_s3 += menuItem_drawTex(item, &gfx, _getTexSetup(musicItem->watchMenuRef, j + 0x1B), var_s3);
        }
    }

    *gxfP = gfx;
}

/**
 * Original name: menuMusicItem_draw2
 */
void menuMusicItem_draw2(MenuMusicItem **musicItemArr, s32 count, Gfx **gxfP) {
    Gfx *gfx = *gxfP;
    MenuCursor *arr[count];
    s32 i;

    for (i = 0; i < count; i++) {
        MenuMusicItem *musicItem = musicItemArr[i];

        arr[i] = &musicItem->unk_640;
    }

    func_80048634(arr, count, &gfx);

    *gxfP = gfx;
}

void func_8004A814(MenuMusicItem *musicItemArr[], s32 arg1, Gfx **gfxP) {
    menuMusicItem_draw1(musicItemArr, arg1, gfxP);
    menuMusicItem_draw2(musicItemArr, arg1, gfxP);
}

void func_8004A860(MenuNumber *arg0, struct_watchMenu *watchMenuRef, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    arg0->watchMenuRef = watchMenuRef;
    arg0->unk_04 = arg2;
    arg0->unk_08 = arg3;
    arg0->unk_0C = arg4;
    arg0->unk_10 |= 0x80000000;
    bzero(arg0->unk_14, ARRAY_COUNTU(arg0->unk_14) * sizeof(char));
    menuItem_init(&arg0->unk_1C, arg5, arg6);
}

/**
 * Original name: menuNumber_update
 */
void menuNumber_update(MenuNumber *menuNumber, MenuItem *item) {
    s32 var_a3 = menuNumber->unk_0C;
    s32 i;

    for (i = menuNumber->unk_08 - 1; i >= 0; i--) {
        menuNumber->unk_14[i] = var_a3 % 10;
        var_a3 /= 10;
    }
    func_800464BC(&menuNumber->unk_1C, item);
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
void menuNumber_draw(MenuNumber **numberP, s32 arg1, Gfx **gxfP) {
    Gfx *gfx = *gxfP;
    MenuNumber *temp_s0;
    MenuItem *temp_s3;
    TiTexData *sp34;
    TiTexData *var_t1;
    s32 var_fp;
    s32 temp_t4_2;
    s32 temp_t4;
    s32 var_s2;
    bool cached;
    s32 var_s5;
    s32 temp_s4;
    s32 sp40;

    gSPDisplayList(gfx++, fade_alpha_texture_init_dl);

    for (temp_t4 = 0; temp_t4 < ARRAY_COUNT(_step_2517); temp_t4++) {
        for (var_fp = 0; cached = 0, var_fp < ARRAY_COUNT(_tbl_2516); var_fp++) {
            for (temp_t4_2 = 0; temp_t4_2 < arg1; temp_t4_2++) {
                temp_s0 = numberP[temp_t4_2];
                temp_s3 = &temp_s0->unk_1C;
                sp40 = temp_s0->unk_10 >> 0x1F;

                switch (temp_s0->unk_04) {
                    case 0x0:
                        sp34 = _getTexSetup(temp_s0->watchMenuRef, 7);
                        var_t1 = _getTexSetup(temp_s0->watchMenuRef, 0);
                        break;

                    case 0x1:
                        sp34 = _getTexGameAl(temp_s0->watchMenuRef, 0xD);
                        var_t1 = _getTexGameAl(temp_s0->watchMenuRef, 0x12);
                        break;
                }

                var_s5 = MIN(sp34->info[TI_INFO_IDX_WIDTH], var_t1->info[TI_INFO_IDX_WIDTH]);
                temp_s4 = MIN(sp34->info[TI_INFO_IDX_HEIGHT], var_t1->info[TI_INFO_IDX_HEIGHT]) / 10;

                if (menuItem_outOfScreen(temp_s3, var_s5 * temp_s0->unk_08, temp_s4)) {
                    continue;
                }

                func_80046844(temp_s3, &gfx);

                for (var_s2 = 0; var_s2 < temp_s0->unk_08; var_s2++) {
                    if ((sp40 == 0) && (temp_s0->unk_14[var_s2] == 0)) {
                        continue;
                    }

                    sp40 = 1;
                    if ((temp_t4 != temp_s0->unk_04) || (var_fp != temp_s0->unk_14[var_s2])) {
                        continue;
                    }

                    tiStretchAlphaTexItem(&gfx, sp34, var_t1, cached++, 0xA, _tbl_2516[var_fp],
                                          temp_s3->pos[0] + (_step_2517[temp_t4] * temp_s3->unk_30[0] * var_s2),
                                          temp_s3->pos[1], var_s5 * temp_s3->unk_30[0], temp_s4 * temp_s3->unk_30[1]);
                }
            }
        }
    }

    *gxfP = gfx;
}

void func_8004AC98(MenuComLvPanel *comLvPanel, s32 arg1, f32 arg2) {
    MenuItem *item = &comLvPanel->unk_008;

    func_800467E0(item);
    func_80046614(item, arg1);
    item->unk_64 = arg2;
}

void func_8004ACF4(MenuComLvPanel *comLvPanel, s32 arg1) {
    func_8004AC98(comLvPanel, arg1, comLvPanel->unk_008.unk_64);
}

void func_8004AD10(MenuComLvPanel *comLvPanel, s32 arg1, s32 arg2) {
    MenuItem *item = &comLvPanel->unk_008;

    item->unk_1C[0] = item->unk_24[0] = arg1;
    item->unk_1C[1] = item->unk_24[1] = arg2;
}

void func_8004AD3C(MenuComLvPanel *arg0, struct_watchMenu *watchMenuRef, s32 arg2, s32 arg3, s32 arg4) {
    arg0->watchMenuRef = watchMenuRef;
    arg0->unk_004 = arg2;

    menuItem_init(&arg0->unk_008, arg3, arg4);
    menuItem_init(&arg0->unk_098, 0, 10);
}

void func_8004AD84(MenuComLvPanel *comLvPanel, MenuItem *parent) {
    func_800464BC(&comLvPanel->unk_008, parent);
    func_800464BC(&comLvPanel->unk_098, &comLvPanel->unk_008);
}

/**
 * Original name: menuComLvPanel_draw
 */
void menuComLvPanel_draw(MenuComLvPanel **comLvPanelP, s32 count, Gfx **gfxP) {
    Gfx *gfx = *gfxP;
    bool cached = false;
    MenuComLvPanel *comLvPanel;
    MenuItem *item;
    TiTexData *temp_v0;
    s32 j;
    s32 i;

    gSPDisplayList(gfx++, fade_normal_texture_init_dl);

    for (i = 0; i < count; i++) {
        comLvPanel = comLvPanelP[i];
        temp_v0 = _getTexChar(comLvPanel->watchMenuRef, 6);
        item = &comLvPanel->unk_008;

        if (menuItem_outOfScreen(item, temp_v0->info[TI_INFO_IDX_WIDTH], temp_v0->info[TI_INFO_IDX_HEIGHT])) {
            continue;
        }

        if (item->color.v.a < 1.0f) {
            gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
        } else {
            gDPSetRenderMode(gfx++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
        }
        func_80046844(item, &gfx);

        tiStretchTexTile(&gfx, temp_v0, cached, 0, 0, temp_v0->info[TI_INFO_IDX_WIDTH], 0x14, item->pos[0],
                         item->pos[1], item->unk_30[0] * temp_v0->info[TI_INFO_IDX_WIDTH], item->unk_30[1] * 20.0f);
        cached++;
    }

    cached = 0;
    for (j = 7; j > 0; j--) {
        for (i = 0; i < count; i++) {
            comLvPanel = comLvPanelP[i];
            if (j != comLvPanel->unk_004) {
                continue;
            }

            temp_v0 = _getTexChar(comLvPanel->watchMenuRef, 6);
            item = &comLvPanel->unk_098;
            if (menuItem_outOfScreen(&comLvPanel->unk_008, temp_v0->info[TI_INFO_IDX_WIDTH],
                                     temp_v0->info[TI_INFO_IDX_HEIGHT])) {
                continue;
            }

            if (item->color.v.a < 1.0f) {
                gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
            } else {
                gDPSetRenderMode(gfx++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
            }
            func_80046844(item, &gfx);
            tiStretchTexTile(&gfx, temp_v0, cached, 0, 0x14, (temp_v0->info[TI_INFO_IDX_WIDTH] * j) / 7, 0xA,
                             item->pos[0], item->pos[1],
                             (item->unk_30[0] * temp_v0->info[TI_INFO_IDX_WIDTH] * j) / 7.0f, item->unk_30[1] * 10.0f);
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
    MenuItem *sp10[ARRAY_COUNTU(cont->unk_094) + ARRAY_COUNTU(cont->unk_364) + ARRAY_COUNTU(cont->unk_3F4) +
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
        MenuItem *temp_s0 = sp10[i];

        func_800467E0(temp_s0);
        temp_s0->unk_68 = 0.05f;
        temp_s0->unk_64 = arg2;
        func_80046614(temp_s0, arg1);
    }

    for (i = 0; i < ARRAY_COUNTU(cont->unk_364); i++) {
        MenuItem *var_v1_5 = &cont->unk_364[i];

        for (j = 0; j < ARRAY_COUNT(RO_800AFBE0); j++) {
            var_v1_5->unk_6C[0][j] = var_v1_5->unk_6C[1][j] = RO_800AFBE0[j];
        }
    }
}

void func_8004B2C8(MenuCont *cont, s32 arg1, s32 arg2) {
    MenuItem *item = &cont->unk_004;

    item->unk_14 = arg2;
    item->unk_18 = 0.05f;
    item->unk_1C[0] = item->unk_24[0] - 160.0f;
    func_8004655C(item, arg1);
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
        func_800467E0(&cont->unk_094[i]);
    }

    for (i = 0; i < ARRAY_COUNTU(cont->unk_364); i++) {
        menuItem_init(&cont->unk_364[i], _posLine_2861[i][0], _posLine_2861[i][1]);
        func_800467E0(&cont->unk_364[i]);
    }

    menuItem_init(&cont->unk_3F4[0], 14, 47);
    menuItem_init(&cont->unk_484[0], 214, 212);
    menuCont_setFade(cont, -1, 0.0f);
    func_8004B2C8(cont, -1, 0);
}

bool func_8004B43C(MenuCont *cont, s32 arg1 UNUSED) {
    MenuItem *item = &cont->unk_004;

    return ((item->unk_18 > 0.0f) && (item->unk_14 == 1.0f));
}

void func_8004B488(MenuCont *cont, MenuItem *parentItem) {
    func_800464BC(&cont->unk_004, parentItem);
    func_800464F8(cont->unk_094, ARRAY_COUNT(cont->unk_094), &cont->unk_004);
    func_800464F8(cont->unk_364, ARRAY_COUNT(cont->unk_364), &cont->unk_004);
    func_800464BC(cont->unk_3F4, parentItem);
    func_800464BC(cont->unk_484, parentItem);
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
};

/**
 * Original name: menuCont_draw
 */
void menuCont_draw(MenuCont *cont, Gfx **gfxP) {
    Gfx *gfx = *gfxP;
    MenuItem *item;
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
        func_80046F58(item, &gfx, temp_s3, 0, 4, i);
    }

    for (; i < ARRAY_COUNTU(cont->unk_094); i++) {
        item = &cont->unk_094[i];

#ifndef PRESERVE_UB
        //! @bug: OoB access: reads index 1 of array `_desc_2915` which has only one element.
        //! This ends up being harmless since the accessed memory (`_panel_3220[0]`) happens to have the same contents
        //! of this array.
        temp_s3 = _getTexCont(cont->watchMenuRef, _desc_2915[i - (ARRAY_COUNTU(cont->unk_094) - 2)]);
#else
        //! This ensures the same array is being accessed even if the variables get reordered by the compiler.
        extern const s32 _panel_3220[];
        temp_s3 = _getTexCont(cont->watchMenuRef, _panel_3220[i - (ARRAY_COUNTU(cont->unk_094) - 1)]);
#endif

        menuItem_drawTex(item, &gfx, temp_s3, 0);
    }

    func_80046F58(cont->unk_3F4, &gfx, _getTexCommon(cont->watchMenuRef, 0xE), 0, 0x2F, 0x13);

    gSPDisplayList(gfx++, fade_alpha_texture_init_dl);

    temp_s3 = _getTexTutol(cont->watchMenuRef, 1);
    temp = _getTexTutol(cont->watchMenuRef, 3);
    menuItem_drawAlphaTex(cont->unk_484, &gfx, temp_s3, temp, 0);

    *gfxP = gfx;
}

void func_8004B774(MenuMainPanel *mainPanel, s32 arg1, f32 arg2) {
    MenuItem *item = &mainPanel->unk_028;

    item->unk_14 = arg2;
    item->unk_18 = 0.05f;
    // TODO: SCREEN_WIDTH?
    item->unk_1C[0] = item->unk_24[0] - 320.0f;
    func_8004655C(item, arg1);
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

    func_800479A8(&mainPanel->unk_418, watchMenuRef, 0, 0, 0, 0, 0x6A, 0x14);
    mainPanel->unk_418.unk_01C.b.unk_30 = 1;
}

/**
 * Original name: menuMainPanel_input
 */
bool menuMainPanel_input(MenuMainPanel *mainPanel, s32 arg1) {
    u32 temp_a0 = _getKeyRep(mainPanel->watchMenuRef, arg1);
    s32 var_v1 = 0;
    s32 temp;

    if ((mainPanel->unk_028.unk_18 < 0.0f) || (mainPanel->unk_028.unk_14 < 1.0f)) {
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

void func_8004B98C(MenuMainPanel *arg0, MenuItem *parentItem) {
    func_800464BC(&arg0->unk_028, parentItem);
    func_800464F8(arg0->unk_0B8, arg0->unk_008, &arg0->unk_028);
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
        func_80046F58(&arg0->unk_0B8[var_s0], &gfx, temp_s4, 0, 0x2F, arg0->unk_010[var_s0]);
    }

    sp1C[0] = &arg0->unk_418;
    func_80048634(sp1C, ARRAY_COUNT(sp1C), &gfx);

    *gfxP = gfx;
}

void func_8004BB14(MenuNameSelPanel *nameSelPanel, s32 arg1, f32 arg2) {
    MenuItem *item = &nameSelPanel->unk_028;

    item->unk_14 = arg2;
    item->unk_18 = 0.05f;
    item->unk_1C[0] = item->unk_24[0] - 320.0f;
    func_8004655C(item, arg1);
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

    for (var_a3 = 0; var_a3 < 2; var_a3++) {
        nameSelPanel->unk_00C[var_a3] = 0;
        nameSelPanel->unk_014[var_a3] = evs_select_name_no[var_a3];
        nameSelPanel->unk_01C[var_a3] = (evs_select_name_no[var_a3] & 1);
    }

    nameSelPanel->unk_024.b.unk_31 = (arg1 != false);

    for (var_a3 = 0; var_a3 < 2U; var_a3++) {
        nameSelPanel->unk_5C8[var_a3].unk_01C.b.unk_30 = true;
        nameSelPanel->unk_5C8[var_a3].unk_01C.b.unk_29 = (nameSelPanel->unk_004 >= 2);
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
        func_800479A8(&nameSelPanel->unk_5C8[i], watchMenuRef, 0, i, 0, 0, 0x38, 0x14);

        if (i % 2U != 0) {
            MenuItem *item;

            item = &nameSelPanel->unk_5C8[i].unk_0B0;
            item->unk_64 = WrapF(0.0f, 1.0f, item->unk_64 + DOUBLE_LITERAL(0.5));

            item = &nameSelPanel->unk_5C8[i].unk_140;
            item->unk_14 = WrapF(0.0f, 1.0f, item->unk_14 + DOUBLE_LITERAL(0.5));
            item->unk_1C[0] += nameSelPanel->unk_5C8[i].unk_014 + 0x10;
            item->unk_24[0] += nameSelPanel->unk_5C8[i].unk_014 + 0x10;
            item->unk_40[0] = -item->unk_40[0];
            item->unk_48[0] = -item->unk_48[0];

            item = &nameSelPanel->unk_5C8[i].unk_1D0;
            item->unk_14 = WrapF(0.0f, 1.0f, item->unk_14 + DOUBLE_LITERAL(0.5));
            item->unk_1C[0] += nameSelPanel->unk_5C8[i].unk_014 + 0x10;
            item->unk_24[0] += nameSelPanel->unk_5C8[i].unk_014 + 0x10;
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

    if ((nameSelPanel->unk_028.unk_18 < 0.0f) || (nameSelPanel->unk_028.unk_14 < 1.0f)) {
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
void menuNameSelPanel_update(MenuNameSelPanel *nameSelPanel, MenuItem *parentItem) {
    s32 i;
    s32 j;

    func_800464BC(&nameSelPanel->unk_028, parentItem);
    func_800464F8(nameSelPanel->unk_0B8, ARRAY_COUNT(nameSelPanel->unk_0B8), &nameSelPanel->unk_028);

    for (i = 0; i < nameSelPanel->unk_004; i++) {
        nameSelPanel->unk_5C8[i].unk_0B0.unk_6C[0][3] = 1.0f;
    }

    for (i = 0; i < (nameSelPanel->unk_004 - 1); i++) {
        for (j = i + 1; j < nameSelPanel->unk_004; j++) {
            if (nameSelPanel->unk_014[i] == nameSelPanel->unk_014[j]) {
                //! FAKE:

#if VERSION_CN
                MenuItem *item = &nameSelPanel->unk_5C8[i].unk_0B0;
                MenuItem *item2 = &nameSelPanel->unk_5C8[j].unk_0B0;

                item->unk_6C[0][3] = 0.0f;
                item2->unk_6C[0][3] = 0.0f;
#elif VERSION_US || VERSION_GW
                nameSelPanel->unk_5C8[i].unk_0B0.unk_6C[0][3] = 0.0f;
                nameSelPanel->unk_5C8[j].unk_0B0.unk_6C[0][3] = 0.0f;
#else
#error ""
#endif
            }
        }
    }

    for (i = 0; i < ARRAY_COUNTU(nameSelPanel->unk_5C8); i++) {
        menuCursor_update(&nameSelPanel->unk_5C8[i], &nameSelPanel->unk_0B8[nameSelPanel->unk_014[i]]);
        if (nameSelPanel->unk_00C[i] > 0) {
            MenuItem *item = &nameSelPanel->unk_5C8[i].unk_0B0;

            for (j = 0; j < ARRAY_COUNTU(item->color.arr); j++) {
                item->color.arr[j] = item->unk_6C[1][j];
            }

            nameSelPanel->unk_5C8[i].unk_01C.b.unk_30 = false;
            nameSelPanel->unk_5C8[i].unk_01C.b.unk_28 = false;
        } else {
            nameSelPanel->unk_5C8[i].unk_01C.b.unk_30 = true;
            nameSelPanel->unk_5C8[i].unk_01C.b.unk_28 = true;
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
        MenuItem *item = &nameSelPanel->unk_0B8[i];
        const u8 *temp;
        s32 j;

        if (menuItem_outOfScreen(item, 0xE, 0xE)) {
            continue;
        }

        // wtf
        if (evs_mem_data[i].mem_use_flg & 1) {
            temp = evs_mem_data[i].mem_name;
        } else {
            temp = evs_mem_data[i].mem_name;
        }

        j = item->color.v.a * 255.0f;
        if (evs_mem_data[i].mem_use_flg & 1) {
            gDPSetPrimColor(gfx++, 0, 0, 1, 1, 1, j);
        } else {
            gDPSetPrimColor(gfx++, 0, 0, 160, 160, 160, 255);
        }

        for (j = 0; j < 4; j++) {
            fontXX_drawID(&gfx, item->pos[0] + 4.0f + j * 0xC, item->pos[1] + 4.0f, item->unk_30[0] * 12.0f,
                          item->unk_30[1] * 12.0f, temp[j]);
        }
    }

    for (i = 0; i < nameSelPanel->unk_004; i++) {
        sp2C[i] = &nameSelPanel->unk_5C8[i];
    }
    func_80048634(sp2C, nameSelPanel->unk_004, &gfx);

    *gfxP = gfx;
}

void func_8004C820(MenuNameOpPanel *nameOpPanel, s32 arg1, f32 arg2) {
    MenuItem *item = &nameOpPanel->unk_010;

    item->unk_14 = arg2;
    item->unk_18 = 0.05f;
    item->unk_1C[0] = item->unk_24[0] - 320.0f;
    func_8004655C(item, arg1);
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

    func_800479A8(&nameOpPanel->unk_250, watchMenuRef, 0, 0, 0, 0, 0x69, 0x14);
    nameOpPanel->unk_250.unk_01C.b.unk_30 = true;
}

/**
 * Original name: menuNameOpPanel_input
 */
bool menuNameOpPanel_input(MenuNameOpPanel *nameOpPanel, s32 arg1) {
    u32 keyRep = _getKeyRep(nameOpPanel->watchMenuRef, arg1);
    s32 var_s0 = nameOpPanel->unk_008;

    if ((nameOpPanel->unk_010.unk_18 < 0.0f) || (nameOpPanel->unk_010.unk_14 < 1.0f)) {
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

void func_8004CA30(MenuNameOpPanel *nameOpPanel, MenuItem *parentItem) {
    func_800464BC(&nameOpPanel->unk_010, parentItem);
    func_800464BC(&nameOpPanel->unk_0A0, &nameOpPanel->unk_010);
    func_800464F8(nameOpPanel->unk_130, ARRAY_COUNT(nameOpPanel->unk_130), &nameOpPanel->unk_010);
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
    MenuItem *item;
    TiTexData *temp_s1;
    s32 i;

    gSPDisplayList(gfx++, fade_normal_texture_init_dl);

    temp_s1 = _getTexMain(nameOpPanel->watchMenuRef, 2);
    menuItem_drawTex(&nameOpPanel->unk_010, &gfx, temp_s1, 0);

    temp_s1 = _getTexCommon(nameOpPanel->watchMenuRef, 0xE);
    for (i = 0; i < ARRAY_COUNTU(nameOpPanel->unk_130); i++) {
        func_80046F58(&nameOpPanel->unk_130[i], &gfx, temp_s1, 0, 0x2F, _panel_3859[nameOpPanel->unk_004][i]);
    }

    temp_s1 = _getTexMain(nameOpPanel->watchMenuRef, 7);
    menuItem_drawTex(&nameOpPanel->unk_0A0, &gfx, temp_s1, 0);

    gSPDisplayList(gfx++, fade_intensity_texture_init_dl);
    gDPSetTextureFilter(gfx++, G_TF_BILERP);
    gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, 255);

    item = &nameOpPanel->unk_0A0;
    for (i = 0; i < ARRAY_COUNTU(nameOpPanel->unk_00C); i++) {
        fontXX_drawID(&gfx, item->pos[0] + 4.0f + (i * 12), item->pos[1] + 4.0f, item->unk_30[0] * 12.0f,
                      item->unk_30[1] * 12.0f, nameOpPanel->unk_00C[i]);
    }

    sp1C[0] = &nameOpPanel->unk_250;
    func_80048634(sp1C, ARRAY_COUNT(sp1C), &gfx);

    *gfxP = gfx;
}

void func_8004CCD0(MenuSndSelPanel *sndSelPanel, s32 arg1, f32 arg2) {
    MenuItem *item = &sndSelPanel->unk_014;

    item->unk_14 = arg2;
    item->unk_18 = 0.05f;
    item->unk_1C[0] = item->unk_24[0] - 320.0f;
    func_8004655C(item, arg1);
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
        func_8004A860(&sndSelPanel->unk_2E4[i], watchMenuRef, 0, i + 2, 0, _pos_4015[i], 4);
    }

    func_800479A8(&sndSelPanel->unk_43C, watchMenuRef, 0, 0, 0, 0, 0x69, 0x14);
    sndSelPanel->unk_43C.unk_01C.b.unk_30 = true;
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

    if ((sndSelPanel->unk_014.unk_18 < 0.0f) || (sndSelPanel->unk_014.unk_14 < 1.0f)) {
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

void func_8004CFB8(MenuSndSelPanel *sndSelPanel, MenuItem *parentItem) {
    s32 i;

    sndSelPanel->unk_2E4[0].unk_0C = sndSelPanel->unk_008;
    sndSelPanel->unk_2E4[1].unk_0C = sndSelPanel->unk_00C;
    func_800464BC(&sndSelPanel->unk_014, parentItem);
    func_800464F8(sndSelPanel->unk_0A4, 4, &sndSelPanel->unk_014);

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
    MenuItem *item;
    s32 i;
    TiTexData *temp_v0;
    f32 temp_fs0;
    f32 temp_fs1;

    gSPDisplayList(gfx++, fade_normal_texture_init_dl);

    item = &sndSelPanel->unk_014;

    temp_fs0 = item->pos[0];
    temp_fs1 = item->pos[1];
    temp_v0 = _getTexMain(sndSelPanel->watchMenuRef, 0xB);

    menuItem_drawTex(item, &gfx, temp_v0, 0);
    item->pos[1] += 76.0f;
    menuItem_drawTex(item, &gfx, temp_v0, 0);
    item->pos[0] = temp_fs0 + 19.0f;
    item->pos[1] = temp_fs1 + 2.0f;
    temp_v0 = _getTexMain(sndSelPanel->watchMenuRef, 0xC);
    menuItem_drawTex(item, &gfx, temp_v0, 0);
    item->pos[0] = temp_fs0;
    item->pos[1] = temp_fs1;

    temp_v0 = _getTexCommon(sndSelPanel->watchMenuRef, 0xE);
    for (i = 0; i < ARRAY_COUNTU(sndSelPanel->unk_0A4); i++) {
        func_80046F58(&sndSelPanel->unk_0A4[i], &gfx, temp_v0, 0, 0x2F, _panel_4108[i]);
    }

    for (i = 0; i < ARRAY_COUNTU(sndSelPanel->unk_2E4); i++) {
        sp18[i] = &sndSelPanel->unk_2E4[i];
    }
    menuNumber_draw((void *)sp18, ARRAY_COUNT(sp18), &gfx);

    sp18[0] = &sndSelPanel->unk_43C;
    func_80048634((void *)sp18, 1, &gfx);

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
    MenuItem *item;
    s32 i;

    play2Panel->watchMenuRef = watchMenuRef;

    switch (_getMode(watchMenuRef)) {
        case MAINMENUMODE_MENUPLAY2_17:
        case MAINMENUMODE_MENUPLAY2_26:
        case MAINMENUMODE_MENUPLAY2_41:
        case MAINMENUMODE_MENUPLAY2_43:
            play2Panel->unk_0004 = 0;
            play2Panel->unk_0008 = 0;
            play2Panel->unk_000C = 0;
            break;

        case MAINMENUMODE_MENUPLAY2_21:
        case MAINMENUMODE_MENUPLAY2_30:
        case MAINMENUMODE_MENUPLAY2_45:
            play2Panel->unk_0004 = 1;
            play2Panel->unk_0008 = 0;
            play2Panel->unk_000C = 1;
            break;

        case MAINMENUMODE_MENUPLAY2_34:
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
        func_80049894(&play2Panel->unk_1220, watchMenuRef, 2, arg9, _glvAsk_4314[arg3][0], _glvAsk_4314[arg3][1]);
        menuSpeedItem_init(&play2Panel->unk_12BC, watchMenuRef, arg3 + 2, arg6, arg9, _glvItem_4315[arg3][0],
                           _glvItem_4315[arg3][1], 0x2A);
    } else {
        func_80048B8C(&play2Panel->unk_0290, watchMenuRef, arg3, arg6, arg9, _lvGauge_4311[arg3][0],
                      _lvGauge_4311[arg3][1]);
        func_8004A860(&play2Panel->unk_01E4, watchMenuRef, arg3, 2, arg9, _lvNum_4310[arg3][0], _lvNum_4310[arg3][1]);

        item = &play2Panel->unk_01E4.unk_1C;
        func_80046688(item, _lvNumScale_4308[arg3][0], _lvNumScale_4308[arg3][1]);
        func_80046694(item, _lvNumScale_4308[arg3][0], _lvNumScale_4308[arg3][1]);
    }

    func_80049894(&play2Panel->unk_0590, watchMenuRef, 0, argA, _speedAsk_4312[arg3][0], _speedAsk_4312[arg3][1]);
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
    func_800467E0(&play2Panel->unk_0CD0);
    func_80046614(&play2Panel->unk_0CD0, -1);
    play2Panel->unk_0CD0.unk_64 = 0.0f;

    for (i = 0; i < ARRAY_COUNTU(play2Panel->unk_0D60); i++) {
        func_800479A8(&play2Panel->unk_0D60[i], watchMenuRef, 1, arg6, _cursor_4317[arg3][i][0],
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
                play2Panel->unk_12BC.unk_008 = arg1->unk_12BC.unk_008;
            } else {
                play2Panel->unk_0290.unk_00C = arg1->unk_0290.unk_00C;
            }
            break;

        case 1:
            play2Panel->unk_062C.unk_008 = arg1->unk_062C.unk_008;
            break;
    }
}

void menuPlay2Panel_copyCursor(MenuPlay2Panel *play2Panel, MenuPlay2Panel *other) {
    s32 i;

    if (play2Panel == other) {
        return;
    }

    for (i = 0; i < ARRAY_COUNTU(play2Panel->unk_0D60); i++) {
        play2Panel->unk_0D60[i].unk_01C.b.unk_31 = false;
    }

    if (play2Panel->unk_000C != 0) {
        play2Panel->unk_12BC.unk_404.unk_01C.b.unk_31 = false;
        play2Panel->unk_12BC.unk_404.unk_01C.b.unk_30 = false;
    } else {
        play2Panel->unk_0290.unk_0A0.unk_01C.b.unk_31 = false;
        play2Panel->unk_0290.unk_0A0.unk_01C.b.unk_30 = false;
    }

    play2Panel->unk_062C.unk_404.unk_01C.b.unk_31 = false;
    play2Panel->unk_062C.unk_404.unk_01C.b.unk_30 = false;

    switch (other->unk_0024) {
        case 0x0:
            if (play2Panel->unk_000C != 0) {
                play2Panel->unk_12BC.unk_404.unk_01C.b.unk_30 = true;
            } else {
                play2Panel->unk_0290.unk_0A0.unk_01C.b.unk_30 = true;
            }
            break;

        case 0x1:
            play2Panel->unk_062C.unk_404.unk_01C.b.unk_30 = true;
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
                            func_80048C48(&play2Panel->unk_0290, arg1);
                        } else {
                            func_80049C54(&play2Panel->unk_12BC, arg1);
                        }
                        break;

                    case 1:
                        func_80049C54(&play2Panel->unk_062C, arg1);
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

void menuPlay2Panel_update(MenuPlay2Panel *play2Panel, MenuItem *parentItem) {
    MenuItem *item;
    s32 i;

    if (play2Panel->unk_000C != 0) {
        play2Panel->unk_1220.unk_8 = play2Panel->unk_12BC.unk_008;
    } else {
        play2Panel->unk_01E4.unk_0C = play2Panel->unk_0290.unk_00C;
    }

    play2Panel->unk_0590.unk_8 = play2Panel->unk_062C.unk_008;

    func_800464BC(&play2Panel->unk_0034, parentItem);
    func_800464BC(&play2Panel->unk_00C4, &play2Panel->unk_0034);
    func_800464BC(&play2Panel->unk_0154, &play2Panel->unk_0034);

    if (play2Panel->unk_000C != 0) {
        func_800498C4(&play2Panel->unk_1220, &play2Panel->unk_0034);
        menuSpeedItem_update(&play2Panel->unk_12BC, &play2Panel->unk_0034);
    } else {
        menuNumber_update(&play2Panel->unk_01E4, &play2Panel->unk_0034);
        func_80048CC8(&play2Panel->unk_0290, &play2Panel->unk_0034);
    }

    func_800498C4(&play2Panel->unk_0590, &play2Panel->unk_0034);
    menuSpeedItem_update(&play2Panel->unk_062C, &play2Panel->unk_0034);

    switch (play2Panel->unk_0010) {
        case 0:
            break;

        case 1:
            if (play2Panel->unk_0030.b.bit_30) {
                item = &play2Panel->unk_00C4;

                play2Panel->unk_0C90.primColor[0] = item->color.arr[0] * 255.0f;
                play2Panel->unk_0C90.primColor[1] = item->color.arr[1] * 255.0f;
                play2Panel->unk_0C90.primColor[2] = item->color.arr[2] * 255.0f;
                play2Panel->unk_0C90.primColor[3] = item->color.arr[3] * 255.0f;
                animeState_update(&play2Panel->unk_0C90);
            }
            break;
    }

    func_800464BC(&play2Panel->unk_0CD0, &play2Panel->unk_0034);

    if (play2Panel->unk_0028 == 1) {
        item = &play2Panel->unk_0CD0;

        for (i = 0; i < ARRAY_COUNTU(item->color.arr); i++) {
            item->color.arr[i] = parentItem->color.arr[i];
        }
    }

    for (i = 0; i < ARRAY_COUNTU(play2Panel->unk_0D60); i++) {
        menuCursor_update(&play2Panel->unk_0D60[i], &play2Panel->unk_0034);
    }

    func_80046614(&play2Panel->unk_0034, (play2Panel->unk_0028 != 0) ? -1 : 1);

    i = 0;
    if ((play2Panel->unk_0028 == 0) && (play2Panel->unk_0024 == 0)) {
        i = 1;
    }

    play2Panel->unk_0D60[0].unk_01C.b.unk_31 = i;

    if (play2Panel->unk_000C != 0) {
        play2Panel->unk_12BC.unk_00C = i;
        play2Panel->unk_12BC.unk_404.unk_01C.b.unk_30 = i;
    } else {
        play2Panel->unk_0290.unk_0A0.unk_01C.b.unk_30 = i;
        play2Panel->unk_0290.unk_0A0.unk_01C.b.unk_31 = i;
        play2Panel->unk_0290.unk_0A0.unk_01C.b.unk_28 = i;
    }

    i = 0;
    if ((play2Panel->unk_0028 == 0) && (play2Panel->unk_0024 == 1)) {
        i = 1;
    }

    play2Panel->unk_062C.unk_00C = i;
    play2Panel->unk_0D60[1].unk_01C.b.unk_31 = i;

    play2Panel->unk_062C.unk_404.unk_01C.b.unk_30 = i;
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
    MenuItem *temp_s1_2;
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

    func_80048634((void *)arr[6], count, &gfx);
    func_80048634((void *)arr[7], count, &gfx);

    gSPDisplayList(gfx++, fade_normal_texture_init_dl);

    for (i = 0; i < count; i++) {
        var_s2 = play2PanelArr[i];
        temp_s1_2 = &var_s2->unk_00C4;

        switch (var_s2->unk_0010) {
            case 0:
                var_s3 = _getTexP4(var_s2->watchMenuRef, 0);
                func_80046F58(temp_s1_2, &gfx, var_s3, 0, 0xF, _charTbl_4601[var_s2->unk_0020]);
                break;

            case 1:
                if (var_s2->unk_0030.b.bit_30) {
                    func_80046844(temp_s1_2, &gfx);
                    animeState_draw(&var_s2->unk_0C90, &gfx, temp_s1_2->pos[0], temp_s1_2->pos[1], -1.0f, 1.0f);
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
        func_80046F58(&var_s2->unk_0154, &gfx, var_s3, 0, 0xB, var_v1_2);
    }

    gSPDisplayList(gfx++, fade_alpha_texture_init_dl);

    var_s5 = 0;
    for (i = 0; i < count; i++) {
        var_s2 = play2PanelArr[i];

        var_s3 = _getTexSetup(var_s2->watchMenuRef, 0xB);
        var_s5 += menuItem_drawAlphaTex(&var_s2->unk_0CD0, &gfx, var_s3, _getTexSetup(var_s2->watchMenuRef, 4), var_s5);
    }

    func_8004A160((void *)arr[3], count, &gfx);
    if (var_s2->unk_000C != 0) {
        func_8004A160((void *)arr[5], count, &gfx);
    } else {
        func_80048FA0((void *)arr[1], count, &gfx);
    }

    *gfxP = gfx;
}

void func_8004E270(MenuPlay2PanelSub *play2PanelSub, s32 arg1, f32 arg2) {
    MenuItem *item = &play2PanelSub->unk_010;

    item->unk_14 = arg2;
    item->unk_18 = 0.05f;
    item->unk_1C[1] = item->unk_24[1] - 240.0f;
    func_8004655C(item, arg1);
}

const u8 _bgDataNo_to_stageNo[][2] = {
    { 0, 1 }, { 0, 3 }, { 0, 0 }, { 1, 5 }, { 0, 5 }, { 0, 4 }, { 1, 4 }, { 0, 2 }, { 0, 6 }, { 0, 7 },
};

void func_8004E2B4(MenuPlay2PanelSub *play2PanelSub, s32 arg1, f32 arg2, f32 arg3) {
    MenuItem *item;

    item = &play2PanelSub->unk_9EC;
    item->unk_14 = arg2;
    item->unk_18 = 0.05f;
    item->unk_1C[0] = item->unk_24[0] + arg3;
    func_8004655C(item, arg1);
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
    MenuItem *item;
    s32 i;

    play2PanelSub->watchMenuRef = watchMenuRef;
    play2PanelSub->unk_004 = 0;
    play2PanelSub->unk_008 = 0;
    play2PanelSub->unk_00C = -1;

    menuItem_init(&play2PanelSub->unk_010, arg5, arg6);
    menuMusicItem_init(&play2PanelSub->unk_0A0, watchMenuRef, arg4, 0x46, 9);

    func_8004A860(&play2PanelSub->unk_940, watchMenuRef, 1, 2, arg3, 0x60, 0x28);

    item = &play2PanelSub->unk_940.unk_1C;
    func_80046688(item, 7.0f / 8.0f, 15.0f / 16.0f);
    func_80046694(item, 7.0f / 8.0f, 15.0f / 16.0f);

    menuItem_init(&play2PanelSub->unk_9EC, 0x9C, 0x30);

    for (i = 0; i < ARRAY_COUNTU(play2PanelSub->unk_A7C); i++) {
        menuItem_init(&play2PanelSub->unk_A7C[i], _bgCursor_4920[i][0], _bgCursor_4920[i][1]);
        func_800466D0(&play2PanelSub->unk_A7C[i]);
    }

    item = &play2PanelSub->unk_A7C[ARRAY_COUNTU(play2PanelSub->unk_A7C) - 1];
    item->unk_40[0] = -item->unk_40[0];
    item->unk_48[0] = -item->unk_48[0];

    for (i = 0; i < ARRAY_COUNTU(play2PanelSub->unk_B9C); i++) {
        func_800479A8(&play2PanelSub->unk_B9C[i], watchMenuRef, 0, 0, _cursor_4921[i][0], _cursor_4921[i][1],
                      _cursor_4921[i][2], _cursor_4921[i][3]);
    }

    func_8004E270(play2PanelSub, -1, 0.0f);
}

bool menuPlay2PanelSub_input(MenuPlay2PanelSub *play2PanelSub, s32 arg1) {
    u32 keyRep = _getKeyRep(play2PanelSub->watchMenuRef, arg1);
    u32 keyTrg = _getKeyTrg(play2PanelSub->watchMenuRef, arg1);
    SndIndex soundIndex = SND_INDEX_INVALID;
    s32 var_s0;
    s32 var_v1;

    if ((play2PanelSub->unk_010.unk_18 < 0.0f) || (play2PanelSub->unk_010.unk_14 < 1.0f)) {
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
                            play2PanelSub->unk_940.unk_0C = WrapI(1, 0xB, play2PanelSub->unk_940.unk_0C + var_s0);
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

void menuPlay2PanelSub_update(MenuPlay2PanelSub *play2PanelSub, MenuItem *parentItem) {
    MenuItem *temp_s0 = &play2PanelSub->unk_010;
    s32 i;

    func_800464BC(temp_s0, parentItem);
    if (play2PanelSub->unk_004 != 0) {
        play2PanelSub->unk_0A0.unk_640.unk_020.unk_64 = 1.0f;
    }

    menuMusicItem_update(&play2PanelSub->unk_0A0, temp_s0);
    menuNumber_update(&play2PanelSub->unk_940, temp_s0);
    func_800464BC(&play2PanelSub->unk_9EC, temp_s0);
    func_800464F8(play2PanelSub->unk_A7C, 2, temp_s0);

    for (i = 0; i < ARRAY_COUNTU(play2PanelSub->unk_B9C); i++) {
        menuCursor_update(&play2PanelSub->unk_B9C[i], &play2PanelSub->unk_010);
    }

    i = play2PanelSub->unk_004 == 0;
    play2PanelSub->unk_B9C[0].unk_01C.b.unk_31 = i;
    play2PanelSub->unk_0A0.unk_640.unk_01C.b.unk_30 = i;
    play2PanelSub->unk_0A0.unk_00C.b.unk_31 = i;

    i = play2PanelSub->unk_004 == 1;
    play2PanelSub->unk_B9C[1].unk_01C.b.unk_31 = i;

    if (play2PanelSub->unk_004 != 1) {
        for (i = 0; i < ARRAY_COUNTU(play2PanelSub->unk_A7C); i++) {
            MenuItem *var_v1 = &play2PanelSub->unk_A7C[i];
            s32 j;

            for (j = 0; j < 3; j++) {
                var_v1->color.arr[j] = var_v1->unk_6C[1][j] * parentItem->color.arr[j];
            }
        }
    }
}

void menuPlay2PanelSub_draw(MenuPlay2PanelSub *play2PanelSub, Gfx **gfxP) {
    Gfx *gfx = *gfxP;
    void *arr[2 * 4];
    MenuItem *item;
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
    func_80048634((void *)arr, ARRAY_COUNTU(play2PanelSub->unk_B9C), &gfx);

    arr[0] = &play2PanelSub->unk_0A0;
    func_8004A814((void *)arr, 1, &gfx);
    arr[0] = &play2PanelSub->unk_940;
    menuNumber_draw((void *)arr, 1, &gfx);

    gSPDisplayList(gfx++, fade_normal_texture_init_dl);

    item = &play2PanelSub->unk_9EC;
    func_80046844(item, &gfx);
    gfxSetScissor(&gfx, GFXSETSCISSOR_INTERLACE_NO, play2PanelSub->unk_010.pos[0] + item->unk_24[0] - 16.0f,
                  play2PanelSub->unk_010.pos[1] + item->unk_24[1], 0x68, 0x24);

    temp_s2 = _getTexSetup(play2PanelSub->watchMenuRef, 0xE);
    temp_fs0 = item->pos[0];
    item->pos[0] += (play2PanelSub->unk_00C * 0x48);

    item = &play2PanelSub->unk_9EC;
    for (i = 0; i < 4; i++) {
        func_80046F58(item, &gfx, temp_s2, 0, 0xA,
                      WrapI(0, 0xA, (play2PanelSub->unk_940.unk_0C + play2PanelSub->unk_00C + i) - 1));
        item->pos[0] += 72.0f;
    }

    gDPSetScissor(gfx++, G_SC_NON_INTERLACE, 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1);
    item->pos[0] = temp_fs0;
    gSPDisplayList(gfx++, fade_normal_texture_init_dl);

    temp_s2 = _getTexSetup(play2PanelSub->watchMenuRef, 0x10);

    var_s4 = 0;
    for (i = 0; i < ARRAY_COUNTU(play2PanelSub->unk_A7C); i++) {
        var_s4 += menuItem_drawTex(&play2PanelSub->unk_A7C[i], &gfx, temp_s2, var_s4);
    }

    *gfxP = gfx;
}

ASM_DATA;

MainMenuMode _menuMain_lastMode = MAINMENUMODE_MENUMAIN_0;

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
        case MAINMENUMODE_MENUMAIN_0:
            var_v1 = _tblMain_5279;
            break;

        case MAINMENUMODE_1:
            var_v1 = _tblPlay1_5280;
            break;

        case MAINMENUMODE_22:
            var_v1 = _tblPlay2_5281;
            break;

        case MAINMENUMODE_35:
            var_s1 = _mesVsNum;
            break;

        case MAINMENUMODE_46:
            var_v1 = _tblOpt_5283;
            break;

        case MAINMENUMODE_70:
            var_v1 = _tblMisc_5286;
            break;

        case MAINMENUMODE_73:
            var_s1 = _mesScoreOnOff;
            break;

        case MAINMENUMODE_36:
        case MAINMENUMODE_37:
        case MAINMENUMODE_38:
        case MAINMENUMODE_39:
            var_v1 = _tblBaTyp_5282;
            break;

        case MAINMENUMODE_59:
            var_v1 = _tblTutol_5284;
            break;

        case MAINMENUMODE_71:
            var_s1 = _tblSound_5285[menuMain->unk_1C64.unk_004];
            break;

        case MAINMENUMODE_47:
            var_s1 = _mesRecMs1;
            break;

        case MAINMENUMODE_48:
        case MAINMENUMODE_MENURANK_55:
            var_s1 = _mesRecMs2;
            break;

        case MAINMENUMODE_62:
            var_s1 = _mesNameSel;
            break;

        case MAINMENUMODE_65:
            var_s1 = _mesNameErase;
            break;

        case MAINMENUMODE_66:
            var_s1 = _mesNameErase2;
            break;

        case MAINMENUMODE_72:
            var_s1 = _mesVsCnt2;
            break;

        case MAINMENUMODE_67:
        case MAINMENUMODE_68:
            var_s1 = _mesDoErase;
            break;

        case MAINMENUMODE_69:
            var_s1 = _mesDoErase1;
            break;

        case MAINMENUMODE_2:
        case MAINMENUMODE_5:
        case MAINMENUMODE_8:
        case MAINMENUMODE_11:
        case MAINMENUMODE_14:
        case MAINMENUMODE_18:
        case MAINMENUMODE_23:
        case MAINMENUMODE_27:
        case MAINMENUMODE_31:
            var_s1 = _mesNs1;
            break;

        case MAINMENUMODE_61:
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
        case MAINMENUMODE_1:
            ptr = _play1_5340;
            len = ARRAY_COUNT(_play1_5340);
            break;

        case MAINMENUMODE_22:
            ptr = _play2_5341;
            len = ARRAY_COUNT(_play2_5341);
            break;

        case MAINMENUMODE_35:
            ptr = _play4_5342;
            len = ARRAY_COUNT(_play4_5342);
            break;

        case MAINMENUMODE_46:
            ptr = _option_5344;
            len = ARRAY_COUNT(_option_5344);
            break;

        case MAINMENUMODE_36:
        case MAINMENUMODE_37:
        case MAINMENUMODE_38:
        case MAINMENUMODE_39:
            ptr = _play4type_5343;
            len = ARRAY_COUNT(_play4type_5343);
            break;

        case MAINMENUMODE_47:
            ptr = _recMs_5345;
            len = ARRAY_COUNT(_recMs_5345);
            break;

        case MAINMENUMODE_48:
            ptr = _recMs1_5346;
            len = ARRAY_COUNT(_recMs1_5346);
            break;

        case MAINMENUMODE_MENURANK_55:
            ptr = _recMs2_5347;
            len = ARRAY_COUNT(_recMs2_5347);
            break;

        case MAINMENUMODE_59:
            ptr = _tutorial_5348;
            len = ARRAY_COUNT(_tutorial_5348);
            break;

        case MAINMENUMODE_72:
            ptr = _count_5349;
            len = ARRAY_COUNT(_count_5349);
            break;

        case MAINMENUMODE_67:
            ptr = _backup_5350;
            len = ARRAY_COUNT(_backup_5350);
            break;

        case MAINMENUMODE_70:
            ptr = _misc_5351;
            len = ARRAY_COUNT(_misc_5351);
            break;

        case MAINMENUMODE_73:
            ptr = _score_5352;
            len = ARRAY_COUNT(_score_5352);
            break;

        case MAINMENUMODE_MENUMAIN_0:
        default:
            ptr = _root_5339;
            len = ARRAY_COUNT(_root_5339);
            break;
    }

    menuMainPanel_init(&menuMain->unk_003C[arg2], menuMain->watchMenuRef, len, arg3, ptr, 0x19, 0x3A);

#if VERSION_GW
    switch (mode) {
        case MAINMENUMODE_MENUMAIN_0:
            func_80046614(&menuMain->unk_003C[arg2].unk_0B8[1], -1);
            menuMain->unk_003C[arg2].unk_0B8[1].unk_64 = 0;
            func_80046614(&menuMain->unk_003C[arg2].unk_0B8[2], -1);
            menuMain->unk_003C[arg2].unk_0B8[2].unk_64 = 0;
            break;

        case MAINMENUMODE_47:
            func_80046614(&menuMain->unk_003C[arg2].unk_0B8[1], -1);
            menuMain->unk_003C[arg2].unk_0B8[1].unk_64 = 0;
            break;

        default:
            break;
    }
#endif
}

void menuMain_init(MenuMain *menuMain, struct_watchMenu *watchMenuRef, void **heapP) {
    MenuItem *item;
    s32 i;

    menuMain->watchMenuRef = watchMenuRef;
    if (_getModeOld(watchMenuRef) == MAINMENUMODE_MENUNMENT_64) {
        menuMain->mode = _menuMain_lastMode = MAINMENUMODE_61;
    } else {
        menuMain->mode = _menuMain_lastMode;
    }

    menuMain->unk_0008 = _menuMain_lastDepth;
    for (i = 0; i < ARRAY_COUNTU(_menuMain_lastSelect); i++) {
        menuMain->unk_000C[i] = _menuMain_lastSelect[i];
    }

    if (_getModeOld(watchMenuRef) == MAINMENUMODE_MENUMAIN_0) {
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

        case MAINMENUMODE_23:
        case MAINMENUMODE_27:
        case MAINMENUMODE_31:
            i = 2;
            break;
    }

    menuNameSelPanel_init(&menuMain->unk_0D2C, watchMenuRef, menuMain->mode != MAINMENUMODE_61, i, 0x19, 0x3A);
    func_8004BB14(&menuMain->unk_0D2C, -1, 0.0f);

    menuNameOpPanel_init(&menuMain->unk_17B4, menuMain->watchMenuRef, 0, 0, NULL, 0x19, 0x3A);
    func_8004C820(&menuMain->unk_17B4, -1, 0.0f);

    menuSndSelPanel_init(&menuMain->unk_1C64, watchMenuRef, 0, 0x14, 0x3A);
    func_8004CCD0(&menuMain->unk_1C64, -1, 0.0f);

    switch (menuMain->mode) {
        case MAINMENUMODE_2:
        case MAINMENUMODE_5:
        case MAINMENUMODE_8:
        case MAINMENUMODE_11:
        case MAINMENUMODE_14:
        case MAINMENUMODE_18:
        case MAINMENUMODE_23:
        case MAINMENUMODE_27:
        case MAINMENUMODE_31:
        case MAINMENUMODE_61:
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
    item->unk_14 = 0.0f;
    item->unk_18 = 0.05f;
    item->unk_1C[0] += 320.0f;

    menuItem_init(&menuMain->unk_2418, 0xDC, 0x63);
    item = &menuMain->unk_2418;
    item->unk_18 = 0.05f;
    item->unk_14 = 0.0f;
    item->unk_1C[0] += 320.0f;

    menuItem_init(&menuMain->unk_2538, -0x44, 0x16);
    item = &menuMain->unk_2538;
    item->unk_18 = 0.05f;
    item->unk_14 = 0.0f;
    item->unk_1C[0] = 32.0f;
    item->unk_1C[1] = 54.0f;
    func_8004655C(item, -1);
    item->unk_3C = 0.05f;
    item->unk_38 = 0.0f;
    func_800465B8(item, -1);
    item->unk_6C[1][0] = 1.0f;
    item->unk_6C[1][1] = 0.9411765f;
    item->unk_6C[1][2] = 0.972549f;

    menuItem_init(&menuMain->unk_25C8, 6, 5);
    menuMain->unk_25C8.unk_8C.b.unk_31 = true;

    menuItem_init(&menuMain->unk_24A8, 0x51, 0x11);

    menuCont_init(&menuMain->unk_2658, watchMenuRef, 0xE, 0x71);

    menuYN_init(&menuMain->unk_2B6C, watchMenuRef, 0x78, 0x8C);

    menuMes_init(&menuMain->unk_31E4, watchMenuRef, heapP, 0x11, 2, 0x40, 0xA6);
}

void func_8004F2D8(MenuMain *menuMain) {
    u32 keyTrg = _getKeyTrg(menuMain->watchMenuRef, 0);

    if ((keyTrg & B_BUTTON) && (menuMain->mode != MAINMENUMODE_MENUMAIN_0)) {
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
    MAINMENUMODE_1,
    MAINMENUMODE_22,
    MAINMENUMODE_35,
    MAINMENUMODE_46,
};

const s32 _n_5535[] = { 1, 0, 2, 3, 4, 5 };

const MainMenuMode _mode_5538[] = {
    MAINMENUMODE_5, MAINMENUMODE_2, MAINMENUMODE_14, MAINMENUMODE_18, MAINMENUMODE_8, MAINMENUMODE_11,
};

const MainMenuMode mode_5557[] = {
    MAINMENUMODE_23,
    MAINMENUMODE_27,
    MAINMENUMODE_31,
};

const char _mode_5570[] = {
    MAINMENUMODE_36,
    MAINMENUMODE_37,
    MAINMENUMODE_38,
    MAINMENUMODE_39,
};

const MainMenuMode _tbl_5598[][2] = {
    { MAINMENUMODE_MENUSTORY_4, MAINMENUMODE_46 },
    { MAINMENUMODE_MENUSTORY_4, MAINMENUMODE_62 },
    { MAINMENUMODE_MENUNMENT_3, MAINMENUMODE_MENUNMENT_63 },
};

const MainMenuMode _tblLS_5599[][3] = {
    { MAINMENUMODE_MENULVSEL_7, MAINMENUMODE_MENULVSEL_10, MAINMENUMODE_MENULVSEL_13 },
    { MAINMENUMODE_MENULVSEL_7, MAINMENUMODE_MENULVSEL_10, MAINMENUMODE_MENULVSEL_13 },
    { MAINMENUMODE_MENUNMENT_6, MAINMENUMODE_MENUNMENT_9, MAINMENUMODE_MENUNMENT_12 },
};

const MainMenuMode _tblVM_5600[][3] = {
    { MAINMENUMODE_MENUCHSEL_25, MAINMENUMODE_MENUCHSEL_29, MAINMENUMODE_MENUCHSEL_33 },
    { MAINMENUMODE_MENUCHSEL_25, MAINMENUMODE_MENUCHSEL_29, MAINMENUMODE_MENUCHSEL_33 },
    { MAINMENUMODE_MENUNMENT_24, MAINMENUMODE_MENUNMENT_28, MAINMENUMODE_MENUNMENT_32 },
};

const MainMenuMode _tblVC_5601[][2] = {
    { MAINMENUMODE_MENUCHSEL_16, MAINMENUMODE_MENUCHSEL_20 },
    { MAINMENUMODE_MENUCHSEL_16, MAINMENUMODE_MENUCHSEL_20 },
    { MAINMENUMODE_MENUNMENT_15, MAINMENUMODE_MENUNMENT_19 },
};

const MainMenuMode tbl_5648[] = {
    MAINMENUMODE_47, MAINMENUMODE_59, MAINMENUMODE_61, MAINMENUMODE_67, MAINMENUMODE_70,
};

const MainMenuMode tbl_5664[] = {
    MAINMENUMODE_71,
    MAINMENUMODE_72,
    MAINMENUMODE_73,
};

const u8 _team_5687[][4] = {
    { TEAMNUMBER_0, TEAMNUMBER_1, TEAMNUMBER_2, TEAMNUMBER_3 },
    { TEAMNUMBER_0, TEAMNUMBER_0, TEAMNUMBER_1, TEAMNUMBER_1 },
    { TEAMNUMBER_0, TEAMNUMBER_1, TEAMNUMBER_2, TEAMNUMBER_3 },
};

const MainMenuMode _mode_5688[] = {
    MAINMENUMODE_MENUCHSEL_40,
    MAINMENUMODE_MENUCHSEL_42,
    MAINMENUMODE_MENUCHSEL_44,
};

const enum_evs_gamemode _game_5689[] = {
    GMD_NORMAL,
    GMD_NORMAL,
    GMD_FLASH,
};

const MainMenuMode _mode_5701[] = {
    MAINMENUMODE_48,
    MAINMENUMODE_MENURANK_55,
};

const MainMenuMode _mode1_5709[] = {
    MAINMENUMODE_MENURANK_50, MAINMENUMODE_MENURANK_49, MAINMENUMODE_MENURANK_53,
    MAINMENUMODE_MENURANK_54, MAINMENUMODE_MENURANK_51, MAINMENUMODE_MENURANK_52,
};

const MainMenuMode _mode2_5710[] = {
    MAINMENUMODE_MENURANK_56,
    MAINMENUMODE_MENURANK_57,
    MAINMENUMODE_MENURANK_58,
};

const MainMenuMode tbl_5735[] = {
    MAINMENUMODE_MENUNMENT_64,
    MAINMENUMODE_65,
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

    if (_getMode(menuMain->watchMenuRef) == MAINMENUMODE_MENUMAIN_0) {
        _setTitle(menuMain->watchMenuRef, menuMain->mode);
    }

    i = 0;

    switch (menuMain->mode) {
        case MAINMENUMODE_66:
        case MAINMENUMODE_69:
            i = 1;
            break;

        case MAINMENUMODE_65:
        case MAINMENUMODE_68:
            i = i || menuYN_input(&menuMain->unk_2B6C, 0);
            break;

        case MAINMENUMODE_71:
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
        case MAINMENUMODE_2:
        case MAINMENUMODE_5:
        case MAINMENUMODE_8:
        case MAINMENUMODE_11:
        case MAINMENUMODE_14:
        case MAINMENUMODE_18:
        case MAINMENUMODE_23:
        case MAINMENUMODE_27:
        case MAINMENUMODE_31:
        case MAINMENUMODE_61:
            var_s2 = 0;
            break;

        case MAINMENUMODE_60:
            var_s2 = 0;
            break;

        case MAINMENUMODE_66:
        case MAINMENUMODE_69:
            var_s2 = 0;
            break;

        case MAINMENUMODE_62:
            var_s2 = menuMain->unk_17B4.unk_008;
            break;

        case MAINMENUMODE_71:
            var_s2 = menuMain->unk_1C64.unk_004;
            break;

        case MAINMENUMODE_65:
        case MAINMENUMODE_68:
            var_s2 = menuMain->unk_2B6C.unk_004;
            break;

        default:
            var_s2 = menuMain->unk_000C[menuMain->unk_0008] = sp20->unk_00C;
            break;
    }

    switch (menuMain->mode) {
        case MAINMENUMODE_MENUMAIN_0:
            if (keyTrg & (A_BUTTON | START_BUTTON)) {
                switch (tbl_5517[var_s2]) {
                    case MAINMENUMODE_22:
                        evs_playmax = joyResponseCheck();
                        if (evs_playmax < 2) {
                            func_8004970C(&menuMain->unk_31E4, _mesNoCont2);
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
                if (menuMain->unk_31E4.unk_004.unk_68 < 0.0f) {
                    _setFadeDir(menuMain->watchMenuRef, 1);
                    _setNextMain(menuMain->watchMenuRef, MAIN_TITLE);
                    soundIndex = SND_INDEX_68;
                }
                sp34--;
            } else if (keyTrg != 0) {
                sp34--;
            }
            break;

        case MAINMENUMODE_1:
            menuMain->unk_0030 = GMD_FLASH;
            menuMain->unk_002C = _n_5535[var_s2];

            if (keyTrg & (A_BUTTON | START_BUTTON)) {
                menuMain->unk_0030 = -1;
                menuMain->mode = _mode_5538[var_s2];

                switch (menuMain->mode) {
                    case MAINMENUMODE_18:
                        evs_gamemode = GMD_FLASH;
                        break;

                    case MAINMENUMODE_8:
                        evs_gamemode = GMD_TaiQ;
                        break;

                    case MAINMENUMODE_11:
                        evs_gamemode = GMD_TIME_ATTACK;
                        break;

                    default:
                        evs_gamemode = GMD_NORMAL;
                        break;
                }

                switch (menuMain->mode) {
                    case MAINMENUMODE_2:
                        evs_playcnt = 2;
                        evs_story_flg = 1;
                        evs_gamesel = ENUM_EVS_GAMESEL_3;

                        game_state_data[0].player_type = PLAYERTYPE_0;
                        game_state_data[1].player_type = PLAYERTYPE_1;
                        var_s7++;
                        break;

                    case MAINMENUMODE_5:
                    case MAINMENUMODE_8:
                    case MAINMENUMODE_11:
                        evs_playcnt = 1;
                        evs_story_flg = 0;
                        evs_gamesel = ENUM_EVS_GAMESEL_0;

                        game_state_data[0].player_no = 0;
                        game_state_data[0].player_type = PLAYERTYPE_0;
                        game_state_data[0].charNo = CHARANIMEMODE_M;
                        var_s7++;
                        break;

                    case MAINMENUMODE_14:
                    case MAINMENUMODE_18:
                        evs_playcnt = 2;
                        evs_story_flg = 0;
                        evs_gamesel = ENUM_EVS_GAMESEL_3;

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
                menuMain->mode = MAINMENUMODE_MENUMAIN_0;
                menuMain->unk_0008--;
                var_s3++;
                soundIndex = SND_INDEX_68;
            }
            break;

        case MAINMENUMODE_22:
            menuMain->unk_002C = var_s2 + 6;
            menuMain->unk_0030 = GMD_FLASH;

            if (keyTrg & (A_BUTTON | START_BUTTON)) {
                menuMain->unk_0030 = -1;
                menuMain->mode = mode_5557[var_s2];
                evs_playcnt = 2;
                evs_story_flg = 0;
                evs_gamesel = ENUM_EVS_GAMESEL_1;

                game_state_data[0].player_type = PLAYERTYPE_0;
                game_state_data[1].player_type = PLAYERTYPE_0;

                var_s7++;
                var_s3++;
                soundIndex = SND_INDEX_62;

                switch (menuMain->mode) {
                    case MAINMENUMODE_23:
                        evs_gamemode = GMD_NORMAL;
                        break;

                    case MAINMENUMODE_27:
                        evs_gamemode = GMD_FLASH;
                        break;

                    case MAINMENUMODE_31:
                        evs_gamemode = GMD_TIME_ATTACK;
                        break;

                    default:
                        break;
                }
            } else if (keyTrg & B_BUTTON) {
                menuMain->unk_0030 = -1;
                menuMain->mode = MAINMENUMODE_MENUMAIN_0;
                menuMain->unk_0008--;
                var_s3++;
                soundIndex = SND_INDEX_68;
            }
            break;
        case MAINMENUMODE_35:
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
                    evs_gamesel = ENUM_EVS_GAMESEL_2;
                    evs_gamemode = GMD_NORMAL;

                    for (i = 0; i < ARRAY_COUNT(game_state_data); i++) {
                        game_state_data[i].player_type = var_s2 < i ? PLAYERTYPE_1 : PLAYERTYPE_0;
                    }

                    var_s3++;
                    sp34--;
                    soundIndex = SND_INDEX_62;
                } else {
                    func_8004970C(&menuMain->unk_31E4, mes_5577[var_s2 - 1]);
                    sp34++;
                    soundIndex = SND_INDEX_71;
                }
            } else if (keyTrg & B_BUTTON) {
                if (menuMain->unk_31E4.unk_004.unk_68 < 0.0f) {
                    menuMain->unk_0030 = -1;
                    menuMain->mode = MAINMENUMODE_MENUMAIN_0;
                    menuMain->unk_0008--;
                    var_s3++;
                    soundIndex = SND_INDEX_68;
                }
                sp34--;
            } else if (keyTrg != 0) {
                sp34--;
            }
            break;

        case MAINMENUMODE_2:
        case MAINMENUMODE_5:
        case MAINMENUMODE_8:
        case MAINMENUMODE_11:
        case MAINMENUMODE_14:
        case MAINMENUMODE_18:
        case MAINMENUMODE_23:
        case MAINMENUMODE_27:
        case MAINMENUMODE_31:
        case MAINMENUMODE_61:
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
                        if (!(evs_mem_data[evs_select_name_no[i]].mem_use_flg & 1)) {
                            sp18[i] = 2;
                        }
                    }
                }

                var_s4 = MAX(sp18[0], sp18[1]);

                switch (menuMain->mode) {
                    case MAINMENUMODE_2:
                        var_s6 = _tbl_5598[var_s4][0];
                        break;

                    case MAINMENUMODE_61:
                        var_s6 = _tbl_5598[var_s4][1];
                        break;

                    case MAINMENUMODE_5:
                        var_s6 = _tblLS_5599[var_s4][0];
                        break;

                    case MAINMENUMODE_8:
                        var_s6 = _tblLS_5599[var_s4][1];
                        break;

                    case MAINMENUMODE_11:
                        var_s6 = _tblLS_5599[var_s4][2];
                        break;

                    case MAINMENUMODE_23:
                        var_s6 = _tblVM_5600[var_s4][0];
                        break;

                    case MAINMENUMODE_27:
                        var_s6 = _tblVM_5600[var_s4][1];
                        break;

                    case MAINMENUMODE_31:
                        var_s6 = _tblVM_5600[var_s4][2];
                        break;

                    case MAINMENUMODE_14:
                        var_s6 = _tblVC_5601[var_s4][0];
                        break;

                    case MAINMENUMODE_18:
                        var_s6 = _tblVC_5601[var_s4][1];
                        break;

                    default:
                        break;
                }

                switch (var_s6) {
                    case MAINMENUMODE_46:
                        menuMain->mode = MAINMENUMODE_46;
                        var_s3++;
                        var_s7--;
                        soundIndex = SND_INDEX_68;
                        break;

                    case MAINMENUMODE_62:
                        menuMain->mode = MAINMENUMODE_62;
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
                    case MAINMENUMODE_2:
                    case MAINMENUMODE_5:
                    case MAINMENUMODE_8:
                    case MAINMENUMODE_11:
                    case MAINMENUMODE_14:
                    case MAINMENUMODE_18:
                        menuMain->mode = MAINMENUMODE_1;
                        break;

                    case MAINMENUMODE_23:
                    case MAINMENUMODE_27:
                    case MAINMENUMODE_31:
                        menuMain->mode = MAINMENUMODE_22;
                        break;

                    case MAINMENUMODE_61:
                        menuMain->mode = MAINMENUMODE_46;
                        break;

                    default:
                        break;
                }

                var_s3++;
                var_s7--;
                soundIndex = SND_INDEX_68;
            }
            break;

        case MAINMENUMODE_46:
            if (keyTrg & (A_BUTTON | START_BUTTON)) {
                menuMain->mode = tbl_5648[var_s2];
                switch (menuMain->mode) {
                    case MAINMENUMODE_61:
                        var_s3++;
                        var_s7++;
                        soundIndex = SND_INDEX_62;
                        break;

                    case MAINMENUMODE_47:
                    case MAINMENUMODE_59:
                    case MAINMENUMODE_67:
                    case MAINMENUMODE_70:
                        menuMain->unk_0008++;
                        menuMain->unk_000C[menuMain->unk_0008] = 0;
                        var_s3++;
                        soundIndex = SND_INDEX_62;
                        break;

                    default:
                        break;
                }

                switch (menuMain->mode) {
                    case MAINMENUMODE_47:
                        dm_seq_play_fade(SEQ_INDEX_13, 0x14);
                        break;

                    case MAINMENUMODE_72:
                        menuMain->unk_000C[menuMain->unk_0008] = 3 - evs_vs_count;
                        break;

                    default:
                        break;
                }
            } else if (keyTrg & B_BUTTON) {
                menuMain->mode = MAINMENUMODE_MENUMAIN_0;
                menuMain->unk_0008--;
                var_s3++;
                soundIndex = SND_INDEX_68;
            }
            break;

        case MAINMENUMODE_70:
            if (keyTrg & (A_BUTTON | START_BUTTON)) {
                menuMain->mode = tbl_5664[var_s2];

                // switch?
                switch (menuMain->mode) {
                    case MAINMENUMODE_71:
                        menuMain->unk_1C64.unk_004 = evs_stereo == 0;
                        var_s3++;
                        sp38++;
                        soundIndex = SND_INDEX_62;
                        break;

                    case MAINMENUMODE_72:
                    case MAINMENUMODE_73:
                        menuMain->unk_0008++;
                        menuMain->unk_000C[menuMain->unk_0008] = 0;
                        var_s3++;
                        soundIndex = SND_INDEX_62;
                        break;

                    default:
                        break;
                }

                switch (menuMain->mode) {
                    case MAINMENUMODE_72:
                        menuMain->unk_000C[menuMain->unk_0008] = 3 - evs_vs_count;
                        break;
                    case MAINMENUMODE_73:
                        menuMain->unk_000C[menuMain->unk_0008] = evs_score_flag == 0;
                        break;

                    default:
                        break;
                }
            } else if (keyTrg & B_BUTTON) {
                _eepWritePlayer(menuMain->watchMenuRef);
                menuMain->mode = MAINMENUMODE_46;
                menuMain->unk_0008--;
                var_s3++;
                soundIndex = SND_INDEX_68;
            }
            break;

        case MAINMENUMODE_73:
            if (keyTrg & (A_BUTTON | START_BUTTON)) {
                evs_score_flag = var_s2 == 0;
                menuMain->mode = MAINMENUMODE_70;
                menuMain->unk_0008--;
                var_s3++;
                soundIndex = SND_INDEX_62;
            } else if (keyTrg & B_BUTTON) {
                menuMain->mode = MAINMENUMODE_70;
                menuMain->unk_0008--;
                var_s3++;
                soundIndex = SND_INDEX_68;
            }
            break;

        case MAINMENUMODE_36:
        case MAINMENUMODE_37:
        case MAINMENUMODE_38:
        case MAINMENUMODE_39:
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
                menuMain->mode = MAINMENUMODE_35;
                menuMain->unk_0008--;
                var_s3++;
                soundIndex = SND_INDEX_68;
            }
            break;

        case MAINMENUMODE_47:
            if (keyTrg & (A_BUTTON | START_BUTTON)) {
                menuMain->mode = _mode_5701[var_s2];
                menuMain->unk_0008++;
                menuMain->unk_000C[menuMain->unk_0008] = 0;
                var_s3++;
                soundIndex = SND_INDEX_62;
            } else if (keyTrg & B_BUTTON) {
                menuMain->mode = MAINMENUMODE_46;
                menuMain->unk_0008--;
                var_s3++;
                soundIndex = SND_INDEX_68;
                dm_seq_play_fade(SEQ_INDEX_12, 0x14);
            }
            break;

        case MAINMENUMODE_48:
        case MAINMENUMODE_MENURANK_55:
            if (keyTrg & (A_BUTTON | START_BUTTON)) {
                const MainMenuMode *var_v0_3;

                if (menuMain->mode == MAINMENUMODE_48) {
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
                menuMain->mode = MAINMENUMODE_47;
                menuMain->unk_0008--;
                var_s3++;
                soundIndex = SND_INDEX_68;
            }
            break;

        case MAINMENUMODE_59:
            if (keyTrg & (A_BUTTON | START_BUTTON)) {
                if (var_s2 == 0) {
                    menuMain->mode = MAINMENUMODE_60;
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
                menuMain->mode = MAINMENUMODE_46;
                menuMain->unk_0008--;
                var_s3++;
                soundIndex = SND_INDEX_68;
            }
            break;

        case MAINMENUMODE_72:
            if (keyTrg & (A_BUTTON | START_BUTTON)) {
                evs_vs_count = 3 - var_s2;
                menuMain->mode = MAINMENUMODE_70;
                menuMain->unk_0008--;
                var_s3++;
                sp38--;
                soundIndex = SND_INDEX_62;
            } else if (keyTrg & B_BUTTON) {
                menuMain->mode = MAINMENUMODE_70;
                menuMain->unk_0008--;
                var_s3++;
                soundIndex = SND_INDEX_68;
            }
            break;

        case MAINMENUMODE_60:
            menuCont_setFade(&menuMain->unk_2658, 1, menuMain->unk_2658.unk_3F4[0].unk_64);
            if (keyTrg & B_BUTTON) {
                menuMain->mode = MAINMENUMODE_59;
                var_s3++;
                sp28++;
                sp30--;
                soundIndex = SND_INDEX_68;
            }
            break;

        case MAINMENUMODE_62:
            if (keyTrg & (A_BUTTON | START_BUTTON)) {
                switch (tbl_5735[var_s2]) {
                    case MAINMENUMODE_MENUNMENT_64:
                        _setMode(menuMain->watchMenuRef, MAINMENUMODE_MENUNMENT_64);
                        var_s3++;
                        sp28--;
                        sp2C--;
                        sp24--;
                        soundIndex = SND_INDEX_62;
                        break;

                    case MAINMENUMODE_65:
                        menuMain->mode = MAINMENUMODE_65;
                        menuMain->unk_17B4.unk_250.unk_01C.b.unk_30 = false;
                        menuMain->unk_2B6C.unk_004 = 0;
                        var_fp++;
                        soundIndex = SND_INDEX_62;
                        break;

                    default:
                        break;
                }
            } else if (keyTrg & B_BUTTON) {
                menuMain->mode = MAINMENUMODE_61;
                var_s7++;
                sp24--;
                soundIndex = SND_INDEX_68;
            }
            break;

        case MAINMENUMODE_71:
            if (keyTrg & (A_BUTTON | START_BUTTON)) {
                switch (var_s2) {
                    case 0:
                    case 1:
                        evs_stereo = var_s2 == 0 ? true : false;
                        dm_audio_set_stereo(evs_stereo);
                        menuMain->mode = MAINMENUMODE_70;
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
                menuMain->mode = MAINMENUMODE_70;
                var_s3++;
                sp38--;
                soundIndex = SND_INDEX_68;
                if (menuMain->unk_0034 != SEQ_INDEX_12) {
                    dm_seq_play_fade(SEQ_INDEX_12, 0x14);
                    menuMain->unk_0034 = SEQ_INDEX_12;
                }
            }
            break;

        case MAINMENUMODE_65:
            menuMain->unk_2B6C.unk_1B8.unk_01C.b.unk_30 = true;
            if (keyTrg & (A_BUTTON | START_BUTTON)) {
                switch (var_s2) {
                    case 0x0:
                        menuMain->mode = MAINMENUMODE_61;
                        sp24--;
                        var_s7++;
                        var_fp--;
                        soundIndex = SND_INDEX_68;
                        break;

                    case 0x1:
                        dm_init_save_mem(&evs_mem_data[evs_select_name_no[0]]);
                        _eepErasePlayer(menuMain->watchMenuRef);
                        menuMain->mode = MAINMENUMODE_66;
                        menuMain->unk_2B6C.unk_1B8.unk_01C.b.unk_30 = false;
                        soundIndex = SND_INDEX_70;
                        break;
                }
            } else if (keyTrg & B_BUTTON) {
                menuMain->mode = MAINMENUMODE_62;
                menuMain->unk_17B4.unk_250.unk_01C.b.unk_30 = true;
                var_fp--;
            }
            break;

        case MAINMENUMODE_66:
            if (keyTrg & ANY_BUTTON) {
                menuMain->mode = MAINMENUMODE_61;
                sp24--;
                var_s7++;
                var_fp--;
                soundIndex = SND_INDEX_62;
            }
            break;
        case MAINMENUMODE_67:
            sp20->unk_418.unk_01C.b.unk_30 = true;
            if (keyTrg & (A_BUTTON | START_BUTTON)) {
                switch (var_s2) {
                    case 0x0:
                        menuMain->mode = MAINMENUMODE_46;
                        menuMain->unk_0008--;
                        var_s3++;
                        soundIndex = SND_INDEX_68;
                        break;

                    case 0x1:
                        menuMain->mode = MAINMENUMODE_68;
                        menuMain->unk_2B6C.unk_004 = 0;
                        sp20->unk_418.unk_01C.b.unk_30 = false;
                        var_fp++;
                        soundIndex = SND_INDEX_62;
                        break;
                }
            } else if (keyTrg & B_BUTTON) {
                menuMain->mode = MAINMENUMODE_46;
                menuMain->unk_0008--;
                var_s3++;
                soundIndex = SND_INDEX_68;
            }
            break;

        case MAINMENUMODE_68:
            menuMain->unk_2B6C.unk_1B8.unk_01C.b.unk_30 = true;
            if (keyTrg & (A_BUTTON | START_BUTTON)) {
                switch (var_s2) {
                    case 0x0:
                        menuMain->mode = MAINMENUMODE_46;
                        menuMain->unk_0008--;
                        var_fp--;
                        var_s3++;
                        soundIndex = SND_INDEX_68;
                        break;

                    case 0x1:
                        _eepEraseData(menuMain->watchMenuRef);
                        menuMain->mode = MAINMENUMODE_69;
                        menuMain->unk_2B6C.unk_1B8.unk_01C.b.unk_30 = false;
                        soundIndex = SND_INDEX_70;
                        break;
                }
            } else if (keyTrg & B_BUTTON) {
                menuMain->mode = MAINMENUMODE_67;
                var_fp--;
                soundIndex = SND_INDEX_68;
            }
            break;
        case MAINMENUMODE_69:
            if (keyTrg & ANY_BUTTON) {
                menuMain->mode = MAINMENUMODE_46;
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
        func_8004655C(&menuMain->unk_2388, sp28);
    }
    if (sp2C != 0) {
        func_8004655C(&menuMain->unk_2418, sp2C);
    }
    if (var_fp != 0) {
        func_800490B8(&menuMain->unk_2B6C, var_fp);
    }
    if (sp34 != 0) {
        func_80049578(&menuMain->unk_31E4, sp34);
    }
    if (sp30 < 0) {
        menuCont_setFade(&menuMain->unk_2658, -1, 1.0f);
        func_8004B2C8(&menuMain->unk_2658, -1, menuMain->unk_2658.unk_004.unk_14);
    }
    if (sp24 < 0) {
        func_8004C820(&menuMain->unk_17B4, -1, 1.0f);
    }
    if (var_s7 < 0) {
        func_8004BB14(&menuMain->unk_0D2C, -1, menuMain->unk_0D2C.unk_028.unk_14);
    }
    if (sp38 < 0) {
        func_8004CCD0(&menuMain->unk_1C64, -1, menuMain->unk_1C64.unk_014.unk_14);
    }
    if (var_s3 != 0) {
        func_8004B774(sp20, -1, sp20->unk_028.unk_14);
        menuMain->unk_2300 ^= 1;
        sp20 = &menuMain->unk_003C[menuMain->unk_2300];
    }

    if (menuMain->mode != _menuMain_lastMode) {
        if (sp30 > 0) {
            func_8004B2C8(&menuMain->unk_2658, 1, menuMain->unk_2658.unk_004.unk_14);
        } else if (sp24 > 0) {
            bcopy(evs_mem_data[evs_select_name_no[0]].mem_name, menuMain->unk_17B4.unk_00C, MENUNAMEOPPANEL_UNK_LEN);
            func_8004C820(&menuMain->unk_17B4, 1, 0.0f);
        } else if (sp38 > 0) {
            func_8004CCD0(&menuMain->unk_1C64, 1, menuMain->unk_1C64.unk_014.unk_14);
        } else if (var_s7 > 0) {
            s32 var_a2_8 = 1;
            f32 temp_fs0 = menuMain->unk_0D2C.unk_028.unk_14;

            switch (menuMain->mode) {
                case MAINMENUMODE_23:
                case MAINMENUMODE_27:
                case MAINMENUMODE_31:
                    var_a2_8 = 2;
                    break;

                default:
                    break;
            }

            menuNameSelPanel_clear(&menuMain->unk_0D2C, menuMain->mode != MAINMENUMODE_61, var_a2_8);
            func_8004BB14(&menuMain->unk_0D2C, 1, temp_fs0);
        } else if (var_s3 != 0) {
            f32 temp_fs0_2 = sp20->unk_028.unk_14;

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
    MenuItem *rootItem = _getRootItem(menuMain->watchMenuRef);
    MenuItem *item;
    s32 i;

    for (i = 0; i < ARRAY_COUNTU(menuMain->unk_003C); i++) {
        func_8004B98C(&menuMain->unk_003C[i], rootItem);
    }

    menuNameSelPanel_update(&menuMain->unk_0D2C, rootItem);
    func_8004CA30(&menuMain->unk_17B4, rootItem);
    func_8004CFB8(&menuMain->unk_1C64, rootItem);
    func_800464BC(&menuMain->unk_2388, rootItem);

    item = &menuMain->unk_2388;
    menuMain->msgWnd.posX = item->pos[0] + item->unk_30[0] * 6;
    menuMain->msgWnd.posY = item->pos[1] + item->unk_30[1] * 6;

    if (!menuMain_setMsgStr(menuMain, menuMain->mode, menuMain->unk_000C[menuMain->unk_0008])) {
        msgWnd_update(&menuMain->msgWnd);
    }

    func_800464BC(&menuMain->unk_2418, rootItem);
    func_8004655C(&menuMain->unk_2538, menuMain->unk_0030);
    func_800465B8(&menuMain->unk_2538, menuMain->unk_0030);
    func_800464BC(&menuMain->unk_2538, &menuMain->unk_2418);
    func_800464BC(&menuMain->unk_24A8, &menuMain->unk_2538);
    func_800464BC(&menuMain->unk_25C8, &menuMain->unk_2538);

    for (i = 0; i < ARRAY_COUNTU(menuMain->unk_25C8.color.arr); i++) {
        menuMain->unk_25C8.color.arr[i] = rootItem->color.arr[i];
    }

    func_8004B488(&menuMain->unk_2658, rootItem);

    menuMain->unk_0038 = WrapF(0.0f, 1.0f, menuMain->unk_0038 + DOUBLE_LITERAL(1.0 / 128));

    func_800492D8(&menuMain->unk_2B6C, rootItem);
    func_80049754(&menuMain->unk_31E4, rootItem);
    menuMain->unk_17B4.unk_250.unk_01C.b.unk_28 = true;
    temp_s5->unk_418.unk_01C.b.unk_28 = true;

    switch (menuMain->mode) {
        case MAINMENUMODE_65:
        case MAINMENUMODE_66:
            menuMain->unk_17B4.unk_250.unk_01C.b.unk_28 = false;
            break;

        case MAINMENUMODE_68:
        case MAINMENUMODE_69:
            temp_s5->unk_418.unk_01C.b.unk_28 = false;
            break;

        default:
            break;
    }

    switch (menuMain->mode) {
        case MAINMENUMODE_66:
        case MAINMENUMODE_69:
            menuMain->unk_2B6C.unk_1B8.unk_01C.b.unk_28 = false;
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
    f32 temp_fs2 = menuMain->unk_2538.unk_38 * 3.0f;
    MenuItem *item;
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

    guRotateRPYF(sp48, 0.0f, 0.0f, sinf(sp88[0]) * (1.0f - menuMain->unk_2538.unk_38) * 4.0f);

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

        func_80046844(item, &gfx);
        sp48[3][0] = item->pos[0];
        sp48[3][1] = item->pos[1] + (sinf(sp88[0]) * temp_fs2);
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

        func_80046844(item, &gfx);
        sp48[3][0] = item->pos[0];
        sp48[3][1] = item->pos[1] + (sinf(sp88[2]) * temp_fs2);
        guMtxF2L(sp48, mtx);

        gSPMatrix(gfx++, mtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        mtx++;

        RectTexTile8(&gfx, &vtx, var_s3->info[TI_INFO_IDX_WIDTH], var_s3->info[TI_INFO_IDX_HEIGHT],
                     var_s3->texs[TI_TEX_TLUT], (u8 *)var_s3->texs[TI_TEX_TEX] + (var_s5 * var_s1_3 * i), 0, 0, var_s5,
                     var_s1_3, 0, 0, var_s5 * item->unk_30[0], var_s1_3 * item->unk_30[1]);
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
            func_80046844(item, &gfx);
            sp48[3][0] = item->pos[0];
            sp48[3][1] = item->pos[1] + (sinf(sp88[i + 1]) * temp_fs2);
            guMtxF2L(sp48, mtx);

            gSPMatrix(gfx++, mtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            mtx++;

            RectTexTile4i(&gfx, &vtx, var_s3->info[TI_INFO_IDX_WIDTH], var_s3->info[TI_INFO_IDX_HEIGHT],
                          var_s3->texs[TI_TEX_TEX], 0, 0, var_s3->info[TI_INFO_IDX_WIDTH],
                          var_s3->info[TI_INFO_IDX_HEIGHT], 0, 0,
                          (var_s3->info[TI_INFO_IDX_WIDTH] + spA0) * item->unk_30[0],
                          (var_s3->info[TI_INFO_IDX_HEIGHT] + var_fp) * item->unk_30[1]);
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
    func_800497D0(&menuMain->unk_31E4, &gfx);

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
    MenuItem *item = &menuStory->unk_0040;

    item->unk_14 = arg2;
    item->unk_18 = 0.05f;
    item->unk_1C[1] = item->unk_24[1] - 240.0f;
    func_8004655C(item, arg1);
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
static_assert(ARRAY_COUNT(_posChar_6445) == MENU_STORY_UNK_LEN, "");

const s32 _posBgCursor_6446[][2] = {
    { -8, 0x11 },
    { 0xE8, 0x11 },
};
static_assert(ARRAY_COUNT(_posBgCursor_6446) == MENU_STORY_UNK_LEN_4, "");

const s32 _cursor_6447[][4] = {
    { 0, 0, 0x10E, 0x36 },
    { 0, 0x33, 0x10E, 0x24 },
    { 0, 0x54, 0x10E, 0x4E },
};
static_assert(ARRAY_COUNT(_cursor_6447) == MENU_STORY_UNK_LEN_3, "");

void menuStory_init(MenuStory *menuStory, struct_watchMenu *watchMenuRef, void **heapP) {
    void *heap = *heapP;
    struct_evs_mem_data *var_v1 = &evs_mem_data[evs_select_name_no[0]];
    struct_evs_mem_data_config *temp_s4 = &var_v1->config;
    s32 i;
    CharAnimeMode var_s1_3;
    MenuItem *item;

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
        func_800479A8(&menuStory->unk_0300[i], watchMenuRef, 0, 0, _posChar_6445[i][0] - 0x18,
                      _posChar_6445[i][1] - 0x2C, 0x30, 0x2F);
    }

    menuStory->unk_0028[1] = temp_s4->st_lv;
    func_80049894(&menuStory->unk_07C0, watchMenuRef, 3, temp_s4->st_lv, 0x45, 0x3D);
    menuSpeedItem_init(&menuStory->unk_085C, watchMenuRef, 3, 0, temp_s4->st_lv, 0x7D, 0x39, 0x34);
    menuStory->unk_085C.unk_010 = temp_s4->st_sh != 0;

    menuStory->unk_0028[2] = temp_s4->st_st + 1;
    func_8004A860(&menuStory->unk_0EC0, watchMenuRef, 1, 1, temp_s4->st_st + 1, 0x65, 0x5A);
    menuItem_init(&menuStory->unk_0F6C, 0x10, 0x6E);

    for (i = 0; i < ARRAY_COUNTU(menuStory->unk_0FFC); i++) {
        item = &menuStory->unk_0FFC[i];

        menuItem_init(item, 0, 0);
        func_800467E0(item);
        item->unk_68 = 0.05f;
    }

    for (i = 0; i < ARRAY_COUNTU(menuStory->unk_111C); i++) {
        menuItem_init(&menuStory->unk_111C[i], _posBgCursor_6446[i][0], _posBgCursor_6446[i][1]);
        func_800466D0(&menuStory->unk_111C[i]);
    }

    for (i = 0; i < ARRAY_COUNTU(menuStory->unk_123C); i++) {
        s32 x;
        s32 y;

        func_800513F0(menuStory->unk_0028[0], menuStory->unk_0028[2], i, &x, &y);
        menuItem_init(&menuStory->unk_123C[i], x, y);
    }

    item = &menuStory->unk_111C[0];
    item->unk_40[0] = -item->unk_40[0];
    item->unk_48[0] = -item->unk_48[0];

    for (i = 0; i < ARRAY_COUNTU(menuStory->unk_135C); i++) {
        func_800479A8(&menuStory->unk_135C[i], watchMenuRef, 1, 0, _cursor_6447[i][0], _cursor_6447[i][1],
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
    s32 var_v1 = menuStory->unk_085C.unk_008;

    if (var_v1 == 2) {
        var_v1 += menuStory->unk_085C.unk_010;
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

    if (menuStory->unk_0040.unk_14 != DOUBLE_LITERAL(1)) {
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
            if (menuStory->unk_085C.unk_008 == 2) {
                if (menuStory->unk_085C.unk_010 == 0) {
                    menuStory->unk_085C.unk_010 = 1;
                    var_s6 = true;
                } else {
                    menuStory->unk_085C.unk_010 = 0;
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
            func_80049C54(&menuStory->unk_085C, 0);
            menuStory->unk_0028[menuStory->unk_0024] = menuStory->unk_085C.unk_008;
            break;

        case 0x2:
            i = func_800519EC(menuStory);
            var_a1 = CLAMP(menuStory->unk_0028[menuStory->unk_0024] + var_s0, 1, i);

            if (var_a1 != menuStory->unk_0028[menuStory->unk_0024]) {
                soundIndex = SND_INDEX_63;
                menuStory->unk_0028[menuStory->unk_0024] = var_a1;

                for (i = 0; i < ARRAY_COUNTU(menuStory->unk_123C); i++) {
                    MenuItem *item = &menuStory->unk_123C[i];

                    item->unk_14 = 0.0f;
                    item->unk_1C[0] = item->unk_24[0];
                    item->unk_1C[1] = item->unk_24[1];
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

            temp_s5->st_lv = menuStory->unk_085C.unk_008;
            temp_s5->st_sh = menuStory->unk_085C.unk_010;
            temp_s5->st_st = menuStory->unk_0EC0.unk_0C - 1;
            temp_s5->st_no = menuStory->unk_0028[0];

            evs_story_level = func_800519CC(menuStory);

            evs_story_no = menuStory->unk_0EC0.unk_0C;

            i = (evs_story_no > 1) ? 1 : 0;
            game_state_data[0].game_retry = i;
            evs_one_game_flg = i;

            story_proc_no = menuStory->unk_0EC0.unk_0C;
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
            _setMode(menuStory->watchMenuRef, MAINMENUMODE_MENUMAIN_0);
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
    MenuItem *rootItem = _getRootItem(menuStory->watchMenuRef);
    MenuCursor *cursor;
    MenuItem *item;
    s32 i;
    s32 j;

    s32 sp20;
    s32 sp24;

    menuStory->unk_07C0.unk_8 = func_800519CC(menuStory);
    menuStory->unk_0EC0.unk_0C = menuStory->unk_0028[2];

    func_800464BC(&menuStory->unk_0040, rootItem);

    for (i = 0; i < ARRAY_COUNTU(menuStory->unk_0160); i++) {
        func_80046614(&menuStory->unk_0160[i], (i == menuStory->unk_0028[0]) ? 1 : -1);
    }

    func_800464BC(&menuStory->unk_00D0, &menuStory->unk_0040);
    func_800464F8(menuStory->unk_0160, ARRAY_COUNTU(menuStory->unk_0160), &menuStory->unk_0040);

    for (i = 0; i < ARRAY_COUNTU(menuStory->unk_0280); i++) {
        if (!menuStory->unk_0034) {
            continue;
        }

        animeState_update(&menuStory->unk_0280[i]);

        for (j = 0; j < 4U; j++) {
            menuStory->unk_0280[i].primColor[j] = menuStory->unk_0160[0].color.arr[j] * 255.0f;
        }
    }

    for (i = 0; i < ARRAY_COUNTU(menuStory->unk_0300); i++) {
        cursor = &menuStory->unk_0300[i];

        menuCursor_update(cursor, &menuStory->unk_0040);
    }

    if (menuStory->unk_0024 != 1) {
        menuStory->unk_085C.unk_404.unk_020.unk_64 = 1.0f;
    }

    func_800498C4(&menuStory->unk_07C0, &menuStory->unk_0040);
    menuSpeedItem_update(&menuStory->unk_085C, &menuStory->unk_0040);
    menuNumber_update(&menuStory->unk_0EC0, &menuStory->unk_0040);

    func_800464BC(&menuStory->unk_0F6C, &menuStory->unk_0040);

    i = (menuStory->unk_0028[2] >= 5) ? -1 : 1;

    func_80046614(&menuStory->unk_0FFC[0], i);
    func_80046614(&menuStory->unk_0FFC[1], -i);
    func_800464F8(menuStory->unk_0FFC, ARRAY_COUNTU(menuStory->unk_0FFC), &menuStory->unk_0F6C);

    for (i = 0; i < MENU_STORY_UNK_LEN_2; i++) {
        func_800513F0(menuStory->unk_0028[0], menuStory->unk_0028[2], i, &sp20, &sp24);

        item = &menuStory->unk_123C[i];
        func_8004667C(item, sp20, sp24);
        func_800464BC(item, &menuStory->unk_0FFC[i]);
    }

    func_800464F8(menuStory->unk_111C, ARRAY_COUNTU(menuStory->unk_111C), &menuStory->unk_0F6C);

    item = menuStory->unk_111C;
    i = func_800519EC(menuStory);
    if ((menuStory->unk_0028[2] > 4) || (i < 5)) {
        item[1].color.v.a = 0.0f;
    }
    if (menuStory->unk_0028[2] < 5) {
        item[0].color.v.a = 0.0f;
    }

    for (i = 0; i < ARRAY_COUNTU(menuStory->unk_135C); i++) {
        cursor = &menuStory->unk_135C[i];

        menuCursor_update(cursor, &menuStory->unk_0040);
    }

    j = menuStory->unk_0024 == 0;
    for (i = 0; i < ARRAY_COUNTU(menuStory->unk_0300); i++) {
        menuStory->unk_135C[0].unk_01C.b.unk_31 = j;
        menuStory->unk_0300[i].unk_01C.b.unk_28 = j;
        menuStory->unk_0300[menuStory->unk_0028[0]].unk_01C.b.unk_30 = j && (i == menuStory->unk_0028[0]);
    }

    j = menuStory->unk_0024 == 1;
    menuStory->unk_085C.unk_00C = j;
    menuStory->unk_135C[1].unk_01C.b.unk_31 = j;
    menuStory->unk_085C.unk_404.unk_01C.b.unk_30 = j;

    j = (menuStory->unk_0024 == 2);
    menuStory->unk_135C[2].unk_01C.b.unk_31 = j;

    if (menuStory->unk_0024 == 2) {
        return;
    }

    for (i = 0; i < ARRAY_COUNTU(menuStory->unk_111C); i++) {
        //! @bug/typo? It seems likely that this should be &menuStory->unk_111C[i] instead
        item = menuStory->unk_111C;

        for (j = 0; j < 3U; j++) {
            item->color.arr[j] = item->unk_6C[1][j] * rootItem->color.arr[j];
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
    MenuItem *item;
    void *sp38[3];
    s32 pad[3] UNUSED;
    s32 var_s2_2;
    s32 i;
    TiTexData *temp_s1;
    TiTexData *temp_v0;

    gSPDisplayList(gfx++, fade_normal_texture_init_dl);

    temp_v0 = _getTexStory(menuStory->watchMenuRef, 6);
    menuItem_drawTex(&menuStory->unk_0040, &gfx, temp_v0, 0);

    for (i = 0; i < MENU_STORY_UNK_LEN; i++) {
        f32 temp_fs1;
        f32 temp_fs0;

        if (!menuStory->unk_0034) {
            continue;
        }

        item = &menuStory->unk_0160[i];

        temp_fs1 = item->pos[0];
        temp_fs0 = item->pos[1];
        item->pos[0] -= 26.0f;
        item->pos[1] -= 48.0f;

        if (!menuItem_outOfScreen(item, 0x40, 0x40)) {
            s32 temp_ft1 = item->unk_64 * 255.0f;

            gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, temp_ft1);

            gSPDisplayList(gfx++, fade_intensity_texture_init_dl);

            temp_v0 = _getTexStory(menuStory->watchMenuRef, 0xC);
            tiStretchTexTile(&gfx, temp_v0, false, 0, 0, temp_v0->info[TI_INFO_IDX_WIDTH],
                             temp_v0->info[TI_INFO_IDX_HEIGHT], item->pos[0], item->pos[1],
                             temp_v0->info[TI_INFO_IDX_WIDTH], temp_v0->info[TI_INFO_IDX_HEIGHT]);

            item->pos[0] = temp_fs1 + 5.0f;
            item->pos[1] = temp_fs0 + 2.0f;

            gSPDisplayList(gfx++, fade_shadow_texture_init_dl);

            gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, temp_ft1 >> 1);

            animeState_draw(&menuStory->unk_0280[i], &gfx, item->pos[0], item->pos[1], 1.0f, 1.0f);
            item->pos[0] = temp_fs1;
            item->pos[1] = temp_fs0;

            gSPDisplayList(gfx++, fade_normal_texture_init_dl);

            func_80046844(item, &gfx);
            animeState_draw(&menuStory->unk_0280[i], &gfx, item->pos[0], item->pos[1], 1.0f, 1.0f);
        }

        item->pos[0] = temp_fs1;
        item->pos[1] = temp_fs0;
    }

    gSPDisplayList(gfx++, fade_normal_texture_init_dl);
    gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);

    for (i = 0; i < ARRAY_COUNTU(menuStory->unk_0FFC); i++) {
        temp_v0 = _getTexStory(menuStory->watchMenuRef, _map_6928[menuStory->unk_0028[0]][i]);
        menuItem_drawTex(&menuStory->unk_0FFC[i], &gfx, temp_v0, 0);
    }

    gSPDisplayList(gfx++, fade_intensity_texture_init_dl);

    for (i = 0; i < MENU_STORY_UNK_LEN_2; i++) {
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
            gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, item->color.v.a * 127.0f);

            tiStretchTexTile(&gfx, temp_v0, false, var_s0_2, 0, temp_s2, temp_v0->info[TI_INFO_IDX_HEIGHT],
                             item->pos[0] + var_s0_2, item->pos[1], temp_s2, temp_v0->info[TI_INFO_IDX_HEIGHT]);
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
    func_8004714C(&menuStory->unk_00D0, &gfx, temp_v0, temp_s1, false, 2, menuStory->unk_0028[0]);

    for (i = 0; i < ARRAY_COUNTU(menuStory->unk_135C); i++) {
        sp38[i] = &menuStory->unk_135C[i];
    }

    func_80048634((void *)sp38, ARRAY_COUNTU(menuStory->unk_135C), &gfx);

    sp38[0] = &menuStory->unk_085C;
    func_8004A160((void *)sp38, 1, &gfx);

    *gfxP = gfx;
}

void func_800529FC(MenuLvSel *menuLvSel, s32 arg1, f32 arg2) {
    MenuItem *item = &menuLvSel->unk_0008;

    item->unk_14 = arg2;
    item->unk_18 = 0.05f;
    item->unk_1C[1] = item->unk_24[1] - 240.0f;
    func_8004655C(item, arg1);
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
        case MAINMENUMODE_MENULVSEL_10:
            func_80049894(&menuLvSel->gameLvlIcon, watchMenuRef, 3, temp_s2->p1_tq_lv, 0x44, 9);
            menuSpeedItem_init(&menuLvSel->gameLvlSelector, watchMenuRef, 3, 0, temp_s2->p1_tq_lv, 0x82, 5, 0x2E);
            break;

        case MAINMENUMODE_MENULVSEL_13:
            func_80049894(&menuLvSel->gameLvlIcon, watchMenuRef, 3, temp_s2->p1_ta_lv, 0x44, 9);
            menuSpeedItem_init(&menuLvSel->gameLvlSelector, watchMenuRef, 3, 0, temp_s2->p1_ta_lv, 0x82, 5, 0x2E);
            break;

        case MAINMENUMODE_MENULVSEL_7:
            if (temp_s2->p1_lv <= menuLvSel->unk_2570) {
                i = temp_s2->p1_lv;
            } else {
                i = menuLvSel->unk_2570;
            }

            func_8004A860(&menuLvSel->virusLvlNumber, watchMenuRef, 1, 2, i, 0x59, 5);
            func_80048B8C(&menuLvSel->virusLvlGauge, watchMenuRef, 2, 0, i, 0x99, 0xF);
            func_800466A0(&menuLvSel->virusLvlGauge.unk_010, 1.0f, 0.5f);
            menuLvSel->virusLvlGauge.unk_008 = menuLvSel->unk_2570;
            break;

        default:
            break;
    }

    func_80049894(&menuLvSel->speedIcon, watchMenuRef, 1, temp_s2->p1_sp, 0x44, 0x28);
    menuSpeedItem_init(&menuLvSel->speedSelector, watchMenuRef, 1, 0, temp_s2->p1_sp, 0x82, 0x24, 0x2E);

    func_800466A0(&menuLvSel->speedSelector.unk_014, 1.0f, 0.5f);
    menuMusicItem_init(&menuLvSel->musicSelector, watchMenuRef, temp_s2->p1_m, 0x46, 0x46);
    func_80048680(&menuLvSel->bottle, watchMenuRef, 0x19, 7);

    for (i = 0; i < ARRAY_COUNTU(menuLvSel->unk_162C); i++) {
        func_800479A8(&menuLvSel->unk_162C[i], watchMenuRef, 1, 0, _cursor_7325[i][0], _cursor_7325[i][1],
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

    if ((menuLvSel->unk_0008.unk_18 < 0.0f) || (menuLvSel->unk_0008.unk_14 < 1.0f)) {
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
                case MAINMENUMODE_MENULVSEL_10:
                case MAINMENUMODE_MENULVSEL_13:
                    func_80049C54(&menuLvSel->gameLvlSelector, 0);
                    break;

                case MAINMENUMODE_MENULVSEL_7:
                    func_80048C48(&menuLvSel->virusLvlGauge, 0);
                    break;

                default:
                    break;
            }
            break;

        case 0x1:
            func_80049C54(&menuLvSel->speedSelector, 0);
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
            case MAINMENUMODE_MENULVSEL_7:
                gameStateData->virus_level = menuLvSel->virusLvlGauge.unk_00C;
                gameStateData->cap_def_speed = menuLvSel->speedSelector.unk_008;
                temp_s5->p1_lv = menuLvSel->virusLvlGauge.unk_00C;
                break;

            case MAINMENUMODE_MENULVSEL_10:
                gameStateData->virus_level = 0xA;
                gameStateData->cap_def_speed = menuLvSel->speedSelector.unk_008;
                gameStateData->game_level = menuLvSel->gameLvlSelector.unk_008;
                temp_s5->p1_tq_lv = menuLvSel->gameLvlSelector.unk_008;
                break;

            case MAINMENUMODE_MENULVSEL_13:
                gameStateData->virus_level = _timeAttack_levelTable[menuLvSel->gameLvlSelector.unk_008];
                gameStateData->cap_def_speed = menuLvSel->speedSelector.unk_008;
                gameStateData->game_level = menuLvSel->gameLvlSelector.unk_008;
                temp_s5->p1_ta_lv = menuLvSel->gameLvlSelector.unk_008;
                break;

            default:
                break;
        }

        temp_s5->p1_sp = menuLvSel->speedSelector.unk_008;
        temp_s5->p1_m = menuLvSel->musicSelector.unk_004;

        evs_seqnumb = menuLvSel->musicSelector.unk_004;
        evs_game_time = 0;
        evs_seqence = evs_seqnumb != 4;
        sndIndex = SND_INDEX_62;
    } else if ((keyTrg & B_BUTTON) && (menuLvSel->unk_256C == 0)) {
        _setMode(menuLvSel->watchMenuRef, MAINMENUMODE_MENUMAIN_0);
        func_800529FC(menuLvSel, -1, 1.0f);
        if (menuLvSel->musicSelector.unk_008 >= 0) {
            dm_seq_play_fade(0xC, 0x14);
        }
        sndIndex = SND_INDEX_68;
    }

    if (sndIndex > SND_INDEX_INVALID) {
        dm_snd_play(sndIndex);
    }
}

void menuLvSel_update(MenuLvSel *menuLvSel) {
    MenuItem *rootItem = _getRootItem(menuLvSel->watchMenuRef);
    s32 i;

    switch (menuLvSel->unk_0004) {
        case MAINMENUMODE_MENULVSEL_10:
            menuLvSel->bottle.level = menuLvSel->unk_0004;
            menuLvSel->gameLvlIcon.unk_8 = menuLvSel->gameLvlSelector.unk_008;
            break;

        case MAINMENUMODE_MENULVSEL_13:
            menuLvSel->gameLvlIcon.unk_8 = menuLvSel->gameLvlSelector.unk_008;
            menuLvSel->bottle.level = _timeAttack_levelTable[menuLvSel->gameLvlSelector.unk_008];
            break;

        case MAINMENUMODE_MENULVSEL_7:
            menuLvSel->virusLvlNumber.unk_0C = menuLvSel->virusLvlGauge.unk_00C;
            menuLvSel->bottle.level = menuLvSel->virusLvlGauge.unk_00C;
            break;

        default:
            break;
    }

    menuLvSel->speedIcon.unk_8 = menuLvSel->speedSelector.unk_008;
    func_800464BC(&menuLvSel->unk_0008, rootItem);
    func_800464F8(menuLvSel->unk_0098, ARRAY_COUNT(menuLvSel->unk_0098), &menuLvSel->unk_0008);

    switch (menuLvSel->unk_0004) {
        case MAINMENUMODE_MENULVSEL_10:
        case MAINMENUMODE_MENULVSEL_13:
            func_800498C4(&menuLvSel->gameLvlIcon, &menuLvSel->unk_0008);
            menuSpeedItem_update(&menuLvSel->gameLvlSelector, &menuLvSel->unk_0008);
            break;

        case MAINMENUMODE_MENULVSEL_7:
            menuNumber_update(&menuLvSel->virusLvlNumber, &menuLvSel->unk_0008);
            func_80048CC8(&menuLvSel->virusLvlGauge, &menuLvSel->unk_0008);
            break;

        default:
            break;
    }

    func_800498C4(&menuLvSel->speedIcon, &menuLvSel->unk_0008);
    menuSpeedItem_update(&menuLvSel->speedSelector, &menuLvSel->unk_0008);
    menuMusicItem_update(&menuLvSel->musicSelector, &menuLvSel->unk_0008);
    func_800486C8(&menuLvSel->bottle, &menuLvSel->unk_0098[1]);

    for (i = 0; i < ARRAY_COUNTU(menuLvSel->unk_162C); i++) {
        menuCursor_update(&menuLvSel->unk_162C[i], &menuLvSel->unk_0098[0]);
    }

    func_800464BC(&menuLvSel->capsuleSpeedIcon, &menuLvSel->unk_0098[1]);
    func_800464BC(&menuLvSel->musicIcon, &menuLvSel->unk_0098[1]);

    i = menuLvSel->unk_256C == 0;
    switch (menuLvSel->unk_0004) {
        case MAINMENUMODE_MENULVSEL_7:
            menuLvSel->virusLvlGauge.unk_0A0.unk_01C.b.unk_30 = i;
            menuLvSel->virusLvlGauge.unk_0A0.unk_01C.b.unk_28 = i;
            break;

        case MAINMENUMODE_MENULVSEL_10:
        case MAINMENUMODE_MENULVSEL_13:
            menuLvSel->gameLvlSelector.unk_00C = i;
            menuLvSel->gameLvlSelector.unk_404.unk_01C.b.unk_30 = i;
            break;

        default:
            break;
    }
    menuLvSel->unk_162C[0].unk_01C.b.unk_31 = i;

    i = menuLvSel->unk_256C == 1;
    menuLvSel->speedSelector.unk_00C = i;
    menuLvSel->speedSelector.unk_404.unk_01C.b.unk_30 = i;
    menuLvSel->unk_162C[1].unk_01C.b.unk_31 = i;

    i = menuLvSel->unk_256C == 2;
    menuLvSel->musicSelector.unk_640.unk_01C.b.unk_30 = i;
    menuLvSel->musicSelector.unk_00C.b.unk_31 = i;
    menuLvSel->unk_162C[2].unk_01C.b.unk_31 = i;
}

void menuLvSel_draw(MenuLvSel *menuLvSel, Gfx **gfxP) {
    void *arr[8];
    Gfx *gfx = *gfxP;
    s32 i;
    TiTexData *a2;

    gSPDisplayList(gfx++, fade_normal_texture_init_dl);

    switch (menuLvSel->unk_0004) {
        case MAINMENUMODE_MENULVSEL_7:
            a2 = _getTexLevel(menuLvSel->watchMenuRef, 4);
            break;

        case MAINMENUMODE_MENULVSEL_10:
        case MAINMENUMODE_MENULVSEL_13:
            a2 = _getTexLevel(menuLvSel->watchMenuRef, 5);
            break;

        default:
            UNREACHABLE;
            break;
    }

    menuItem_drawTex(&menuLvSel->unk_0098[0], &gfx, a2, 0);
    menuItem_drawTex(&menuLvSel->unk_0098[1], &gfx, _getTexLevel(menuLvSel->watchMenuRef, 1), 0);
    if (menuLvSel->speedSelector.unk_008 > 0) {
        func_80046F58(&menuLvSel->capsuleSpeedIcon, &gfx, _getTexLevel(menuLvSel->watchMenuRef, 3), 0, 2,
                      menuLvSel->speedSelector.unk_008 - 1);
    }
    if (menuLvSel->musicSelector.unk_004 < 4) {
        func_80046F58(&menuLvSel->musicIcon, &gfx, _getTexLevel(menuLvSel->watchMenuRef, 2), 0, 4,
                      menuLvSel->musicSelector.unk_004);
    }

    switch (menuLvSel->unk_0004) {
        case MAINMENUMODE_MENULVSEL_7:
            if (menuLvSel->unk_2570 >= 21) {
                f32 temp_fs0 = menuLvSel->unk_0098[0].pos[0];

                menuLvSel->unk_0098[0].pos[0] = temp_fs0 + 222.0f;
                menuItem_drawTex(&menuLvSel->unk_0098[0], &gfx, _getTexLevel(menuLvSel->watchMenuRef, 6), 0);
                menuLvSel->unk_0098[0].pos[0] = temp_fs0;
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
        case MAINMENUMODE_MENULVSEL_10:
        case MAINMENUMODE_MENULVSEL_13:
            arr[3] = &menuLvSel->gameLvlIcon;
            arr[4] = &menuLvSel->gameLvlSelector;
            menuSpeedAsk_draw((MenuSpeedAsk **)&arr[3], 1, &gfx);
            menuSpeedItem_draw1((MenuSpeedItem **)&arr[4], 1, &gfx);
            break;

        case MAINMENUMODE_MENULVSEL_7:
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

    func_80048634((MenuCursor **)&arr[5], ARRAY_COUNTU(menuLvSel->unk_162C), &gfx);

    menuMusicItem_draw2((MenuMusicItem **)&arr[0], 1, &gfx);
    func_8004A160((MenuSpeedItem **)&arr[2], 1, &gfx);

    switch (menuLvSel->unk_0004) {
        case MAINMENUMODE_MENULVSEL_10:
        case MAINMENUMODE_MENULVSEL_13:
            func_8004A160((void *)&arr[4], 1, &gfx);
            break;

        case MAINMENUMODE_MENULVSEL_7:
            func_80048FA0((void *)&arr[4], 1, &gfx);
            break;

        default:
            break;
    }

    menuBottle_draw(&menuLvSel->bottle, &gfx);

    *gfxP = gfx;
}

void func_8005380C(MenuChSel *menuChSel, s32 arg1, f32 arg2) {
    MenuItem *item = &menuChSel->unk_0074;

    item->unk_14 = arg2;
    item->unk_18 = 0.05f;
    item->unk_1C[1] = item->unk_24[1] - 240.0f;
    func_8004655C(item, arg1);
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
        case MAINMENUMODE_MENUCHSEL_16:
        case MAINMENUMODE_MENUCHSEL_20:
        case MAINMENUMODE_MENUCHSEL_25:
        case MAINMENUMODE_MENUCHSEL_29:
        case MAINMENUMODE_MENUCHSEL_33:
            menuChSel->unk_0004 = 2;
            break;

        case MAINMENUMODE_MENUCHSEL_40:
        case MAINMENUMODE_MENUCHSEL_42:
        case MAINMENUMODE_MENUCHSEL_44:
            menuChSel->unk_0004 = 4;
            break;

        default:
            break;
    }

    menuChSel->unk_003C = 0;
    menuChSel->unk_0060 = 0;
    menuItem_init(&menuChSel->unk_0104, 0xF9, 0x16);
    func_800467E0(&menuChSel->unk_0104);

    menuChSel->unk_0104.unk_64 = 0.0f;

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
            case MAINMENUMODE_MENUCHSEL_16:
            case MAINMENUMODE_MENUCHSEL_20:
                temp = &evs_mem_data[evs_select_name_no[0]].config;
                var_s3 = temp->vc_no[i];
                break;

            case MAINMENUMODE_MENUCHSEL_25:
            case MAINMENUMODE_MENUCHSEL_29:
            case MAINMENUMODE_MENUCHSEL_33:
                temp = &evs_mem_data[evs_select_name_no[i]].config;
                var_s3 = temp->vm_no;
                break;

            case MAINMENUMODE_MENUCHSEL_40:
            case MAINMENUMODE_MENUCHSEL_42:
            case MAINMENUMODE_MENUCHSEL_44:
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

        menuCursor_init2(cursor, watchMenuRef, 0U, menuChSel->unk_003C, menuChSel->unk_0060, i, 0, 0, 0x2C, 0x2C);
        cursor->unk_1D0.unk_1C[0] = cursor->unk_1D0.unk_24[0] = _pos_7882[i][0];
        cursor->unk_1D0.unk_1C[1] = cursor->unk_1D0.unk_24[1] = _pos_7882[i][1];
    }

    menuItem_init(&menuChSel->unk_0074, 0x12, 0x2F);

    for (i = 0; i < MENU_CH_SEL_UNK_LEN; i++) {
        menuItem_init(&menuChSel->unk_0194[i], ((i % 5) * 0x36) + 0xC, ((i / 5) * 0x35) + 0xC);
        menuItem_init(&menuChSel->unk_0A04[i], 3, 3);
        func_800466B8(&menuChSel->unk_0A04[i], 0.0f, 0.0f);
        func_800466A0(&menuChSel->unk_0A04[i], 0.0f, 0.5f);
    }

    for (i = 0; i < ARRAY_COUNTU(menuChSel->unk_1274); i++) {
        func_8004AD3C(&menuChSel->unk_1274[i], watchMenuRef, 0, -6, 0x1E);
        func_8004AC98(&menuChSel->unk_1274[i], -1, 0.0f);
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
        _setMode(menuChSel->watchMenuRef, MAINMENUMODE_MENUMAIN_0);
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

    if ((menuChSel->unk_0074.unk_18 < 0.0f) || (menuChSel->unk_0074.unk_14 < 1.0f)) {
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
        case MAINMENUMODE_MENUCHSEL_16:
        case MAINMENUMODE_MENUCHSEL_20:
            temp = &evs_mem_data[evs_select_name_no[0]].config;
            for (i = 0; i < menuChSel->unk_0004; i++) {
                temp->vc_no[i] = menuChSel->unk_0008[i];
            }
            break;

        case MAINMENUMODE_MENUCHSEL_25:
        case MAINMENUMODE_MENUCHSEL_29:
        case MAINMENUMODE_MENUCHSEL_33:
            if (evs_select_name_no[0] == evs_select_name_no[1]) {
                evs_mem_data[0].config.vm_no = 0;
            } else {
                for (i = 0; i < menuChSel->unk_0004; i++) {
                    temp = &evs_mem_data[evs_select_name_no[i]].config;

                    temp->vm_no = menuChSel->unk_0008[i];
                }
            }
            break;

        case MAINMENUMODE_MENUCHSEL_40:
        case MAINMENUMODE_MENUCHSEL_42:
        case MAINMENUMODE_MENUCHSEL_44:
            for (i = 0; i < menuChSel->unk_0004; i++) {
                evs_cfg_4p.p4_no[i] = menuChSel->unk_0008[i];
            }
            break;

        default:
            break;
    }

    switch (_getMode(menuChSel->watchMenuRef)) {
        case MAINMENUMODE_MENUCHSEL_16:
            mode = MAINMENUMODE_MENUPLAY2_17;
            break;

        case MAINMENUMODE_MENUCHSEL_20:
            mode = MAINMENUMODE_MENUPLAY2_21;
            break;

        case MAINMENUMODE_MENUCHSEL_25:
            mode = MAINMENUMODE_MENUPLAY2_26;
            break;

        case MAINMENUMODE_MENUCHSEL_29:
            mode = MAINMENUMODE_MENUPLAY2_30;
            break;

        case MAINMENUMODE_MENUCHSEL_33:
            mode = MAINMENUMODE_MENUPLAY2_34;
            break;

        case MAINMENUMODE_MENUCHSEL_40:
            mode = MAINMENUMODE_MENUPLAY2_41;
            break;

        case MAINMENUMODE_MENUCHSEL_42:
            mode = MAINMENUMODE_MENUPLAY2_43;
            break;

        case MAINMENUMODE_MENUCHSEL_44:
            mode = MAINMENUMODE_MENUPLAY2_45;
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
static_assert(ARRAY_COUNT(_star_8183) == MENU_CH_SEL_UNK_LEN, "");

void menuChSel_update(MenuChSel *menuChSel) {
    MenuItem *rootItem = _getRootItem(menuChSel->watchMenuRef);
    s32 i;
    s32 var_a0;

    func_800464BC(&menuChSel->unk_0074, rootItem);

    switch (menuChSel->unk_0028) {
        case 0:
        case 1:
            func_80046614(&menuChSel->unk_0104, (menuChSel->unk_002C != 0) ? 1 : -1);
            break;

        default:
            func_80046614(&menuChSel->unk_0104, -1);
            break;
    }

    func_800464BC(&menuChSel->unk_0104, rootItem);

    func_800464F8(menuChSel->unk_0194, ARRAY_COUNTU(menuChSel->unk_0194), &menuChSel->unk_0074);

    for (i = 0; i < MENU_CH_SEL_UNK_LEN; i++) {
        if (menuChSel_checkSelected(menuChSel, -1, i, 1)) {
            func_80046614(&menuChSel->unk_0A04[i], -1);
        } else {
            func_80046614(&menuChSel->unk_0A04[i], 1);
        }

        func_800464BC(&menuChSel->unk_0A04[i], &menuChSel->unk_0194[i]);
    }

    for (i = 0; i < MENU_CH_SEL_UNK_LEN; i++) {
        var_a0 = _star_8183[i];
        if (menuChSel->unk_002C != 0) {
            var_a0 += menuChSel->unk_0030;
        }

        menuChSel->unk_1274[i].unk_004 = var_a0;
        func_8004ACF4(&menuChSel->unk_1274[i], (i == menuChSel->unk_0034) ? 1 : -1);
        func_8004AD84(&menuChSel->unk_1274[i], &menuChSel->unk_0194[i]);
    }

    for (i = 0; i < menuChSel->unk_0004; i++) {
        MenuCursor *cursor = &menuChSel->unk_23CC[i];

        menuCursor_update(cursor, &menuChSel->unk_0194[menuChSel->unk_0008[i]]);

        switch (menuChSel->unk_0018[i]) {
            case -1:
                cursor->unk_01C.b.unk_31 = false;
                cursor->unk_01C.b.unk_29 = false;
                cursor->unk_01C.b.unk_28 = false;
                break;

            case 0:
                cursor->unk_01C.b.unk_31 = true;
                cursor->unk_01C.b.unk_29 = true;
                cursor->unk_01C.b.unk_28 = true;
                break;

            case 1:
                cursor->unk_01C.b.unk_31 = true;
                cursor->unk_01C.b.unk_29 = true;
                cursor->unk_01C.b.unk_28 = false;
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
    MenuItem *item;
    s32 i;

    gSPDisplayList(gfx++, fade_normal_texture_init_dl);
    menuItem_drawTex(&menuChSel->unk_0074, &gfx, _getTexChar(menuChSel->watchMenuRef, 5), 0);

    for (i = 0; i < ARRAY_COUNT(evs_secret_flg); i++) {
        if (evs_secret_flg[i]) {
            f32 temp_fs0;
            f32 temp_fs1;

            item = &menuChSel->unk_0194[14 - i];
            temp_fs0 = item->pos[0];
            temp_fs1 = item->pos[1];
            item->pos[0] += _pos_8298[i][0];
            item->pos[1] += _pos_8298[i][1];

            menuItem_drawTex(item, &gfx, _getTexChar(menuChSel->watchMenuRef, _tex_8297[i]), 0);
            item->pos[0] = temp_fs0;
            item->pos[1] = temp_fs1;
        }
    }

    gSPDisplayList(gfx++, fade_fillrect_init_dl);

    for (i = 0; i < ARRAY_COUNTU(menuChSel->unk_0A04); i++) {
        s32 x;
        s32 y;

        item = &menuChSel->unk_0A04[i];

        if (item->color.v.a == 1.0f) {
            continue;
        }

        x = item->pos[0];
        y = item->pos[1];
        func_80046844(item, &gfx);

        gDPScisFillRectangle(gfx++, x, y, x + 38, y + 38);
    }

    for (i = 0; i < menuChSel->unk_0004; i++) {
        arr[i] = &menuChSel->unk_23CC[i];
    }

    func_80048634((void *)arr, menuChSel->unk_0004, &gfx);

    for (i = 0; i < ARRAY_COUNTU(menuChSel->unk_1274); i++) {
        arr[i] = &menuChSel->unk_1274[i];
    }

    menuComLvPanel_draw((void *)arr, ARRAY_COUNTU(menuChSel->unk_1274), &gfx);

    gSPDisplayList(gfx++, fade_normal_texture_init_dl);
    gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);

    if (menuChSel->unk_0030 > 0) {
        func_80046F58(&menuChSel->unk_0104, &gfx, _getTexChar(menuChSel->watchMenuRef, 2), 0, 2,
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
        MenuItem *item = &temp_a0->unk_0034;

        item->unk_1C[0] = item->unk_24[0] + _moveTbl_8521[i % ARRAY_COUNTU(_moveTbl_8521)];
        item->unk_18 = 0.05f;
        item->unk_14 = arg2;
        func_8004655C(item, arg1);
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
        case MAINMENUMODE_MENUPLAY2_26:
        case MAINMENUMODE_MENUPLAY2_30:
        case MAINMENUMODE_MENUPLAY2_34:
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
                    case MAINMENUMODE_MENUPLAY2_26:
                        var_s5 = temp_s0->vm_lv;
                        break;

                    case MAINMENUMODE_MENUPLAY2_30:
                        var_s5 = temp_s0->vm_fl_lv;
                        break;

                    case MAINMENUMODE_MENUPLAY2_34:
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

        case MAINMENUMODE_MENUPLAY2_17:
        case MAINMENUMODE_MENUPLAY2_21:
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
                    case MAINMENUMODE_MENUPLAY2_17:
                        var_s5 = temp_s0->vc_lv[i];
                        break;

                    case MAINMENUMODE_MENUPLAY2_21:
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

        case MAINMENUMODE_MENUPLAY2_41:
        case MAINMENUMODE_MENUPLAY2_43:
        case MAINMENUMODE_MENUPLAY2_45:
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
                    case MAINMENUMODE_MENUPLAY2_43:
                    case MAINMENUMODE_MENUPLAY2_41:
                        var_s5 = evs_cfg_4p.p4_lv[i];
                        break;

                    case MAINMENUMODE_MENUPLAY2_45:
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
    func_800467E0(&menuPlay2->unk_0034);
    menuPlay2->unk_0034.unk_64 = 0.0f;

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
            case MAINMENUMODE_MENUPLAY2_26:
                var_s6 = MAINMENUMODE_MENUCHSEL_25;
                break;

            case MAINMENUMODE_MENUPLAY2_30:
                var_s6 = MAINMENUMODE_MENUCHSEL_29;
                break;

            case MAINMENUMODE_MENUPLAY2_34:
                var_s6 = MAINMENUMODE_MENUCHSEL_33;
                break;

            case MAINMENUMODE_MENUPLAY2_17:
                var_s6 = MAINMENUMODE_MENUCHSEL_16;
                break;

            case MAINMENUMODE_MENUPLAY2_21:
                var_s6 = MAINMENUMODE_MENUCHSEL_20;
                break;

            case MAINMENUMODE_MENUPLAY2_41:
                var_s6 = MAINMENUMODE_MENUCHSEL_40;
                break;

            case MAINMENUMODE_MENUPLAY2_43:
                var_s6 = MAINMENUMODE_MENUCHSEL_42;
                break;

            case MAINMENUMODE_MENUPLAY2_45:
                var_s6 = MAINMENUMODE_MENUCHSEL_44;
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

    if (menuPlay2->unk_00C8[0].unk_0034.unk_18 < 0.0f) {
        return;
    }

    if (menuPlay2->unk_00C8[0].unk_0034.unk_14 < 1.0f) {
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
            func_8004E270(&menuPlay2->unk_6548, -1, menuPlay2->unk_6548.unk_010.unk_14);
            menuPlay2_inputMan(menuPlay2);
            break;

        case 1:
            func_8004E270(&menuPlay2->unk_6548, -1, menuPlay2->unk_6548.unk_010.unk_14);
            menuPlay2_inputCpu(menuPlay2);
            break;

        case 2:
            menuPlay2->unk_0008 = -1;
            func_8004E270(&menuPlay2->unk_6548, 1, menuPlay2->unk_6548.unk_010.unk_14);
            if (menuPlay2PanelSub_input(&menuPlay2->unk_6548, 0)) {
                switch (menuPlay2->unk_6548.unk_008) {
                    case -1:
                        menuPlay2->unk_0004 -= 2;
                        for (i = 0; i < menuPlay2->unk_00C4; i++) {
                            menuPlay2->unk_00C8[i].unk_0028 = -1;
                            menuPlay2->unk_00C8[i].unk_0024 = 0;
                        }

                        if (menuPlay2->unk_6548.unk_0A0.unk_008 >= 0) {
                            dm_seq_play_fade(SEQ_INDEX_12, 0x14);
                            menuPlay2->unk_6548.unk_0A0.unk_008 = -1;
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
        case MAINMENUMODE_MENUPLAY2_26:
        case MAINMENUMODE_MENUPLAY2_30:
        case MAINMENUMODE_MENUPLAY2_34:
            for (i = 0; i < menuPlay2->unk_00C4; i++) {
                play2Panel = &menuPlay2->unk_00C8[i];
                temp_a2 = &evs_mem_data[evs_select_name_no[i]].config;

                if (play2Panel->unk_0004 != 0) {
                    temp_a2->vm_fl_lv = play2Panel->unk_12BC.unk_008;
                } else if (play2Panel->unk_0008 != 0) {
                    temp_a2->vm_ta_lv = play2Panel->unk_12BC.unk_008;
                } else {
                    temp_a2->vm_lv = play2Panel->unk_0290.unk_00C;
                }
                temp_a2->vm_sp = play2Panel->unk_062C.unk_008;
                temp_a2->vm_st = menuPlay2->unk_6548.unk_940.unk_0C - 1;
                temp_a2->vm_m = menuPlay2->unk_6548.unk_0A0.unk_004;
            }
            break;

        case MAINMENUMODE_MENUPLAY2_17:
        case MAINMENUMODE_MENUPLAY2_21:
            temp_a2 = &evs_mem_data[evs_select_name_no[0]].config;

            for (i = 0; i < menuPlay2->unk_00C4; i++) {
                play2Panel = &menuPlay2->unk_00C8[i];

                if (play2Panel->unk_0004 != 0) {
                    temp_a2->vc_fl_lv[i] = play2Panel->unk_12BC.unk_008;
                } else {
                    temp_a2->vc_lv[i] = play2Panel->unk_0290.unk_00C;
                }
                temp_a2->vc_sp[i] = play2Panel->unk_062C.unk_008;
            }

            temp_a2->vc_st = menuPlay2->unk_6548.unk_940.unk_0C - 1;
            temp_a2->vc_m = menuPlay2->unk_6548.unk_0A0.unk_004;
            break;

        default:
            break;

        case MAINMENUMODE_MENUPLAY2_41:
        case MAINMENUMODE_MENUPLAY2_43:
        case MAINMENUMODE_MENUPLAY2_45:
            for (i = 0; i < menuPlay2->unk_00C4; i++) {
                play2Panel = &menuPlay2->unk_00C8[i];

                if (play2Panel->unk_0004 != 0) {
                    evs_cfg_4p.p4_fl_lv[i] = play2Panel->unk_12BC.unk_008;
                } else {
                    evs_cfg_4p.p4_lv[i] = play2Panel->unk_0290.unk_00C;
                }
                evs_cfg_4p.p4_sp[i] = play2Panel->unk_062C.unk_008;
            }

            evs_cfg_4p.p4_st = menuPlay2->unk_6548.unk_940.unk_0C - 1;
            evs_cfg_4p.p4_m = menuPlay2->unk_6548.unk_0A0.unk_004;
            break;
    }

    for (i = 0; i < menuPlay2->unk_00C4; i++) {
        struct_game_state_data *ptr = &game_state_data[i];
        play2Panel = &menuPlay2->unk_00C8[i];

        if (play2Panel->unk_0004 != 0) {
            ptr->virus_level = _timeAttack_levelTable[play2Panel->unk_12BC.unk_008];
            ptr->game_level = play2Panel->unk_12BC.unk_008;
        } else if (play2Panel->unk_0008 != 0) {
            ptr->virus_level = _timeAttack_levelTable[play2Panel->unk_12BC.unk_008];
            ptr->game_level = play2Panel->unk_12BC.unk_008;
        } else {
            ptr->virus_level = play2Panel->unk_0290.unk_00C;
        }
        ptr->cap_def_speed = play2Panel->unk_062C.unk_008;
    }

    i = menuPlay2->unk_6548.unk_940.unk_0C - 1;

    story_proc_no = _bgDataNo_to_stageNo[i][1] + 1;
    story_proc_no += _bgDataNo_to_stageNo[i][0] * 0xC;
    evs_story_no = _bgDataNo_to_stageNo[i][1] + 1;

    evs_seqnumb = menuPlay2->unk_6548.unk_0A0.unk_004;
    evs_seqence = evs_seqnumb != 4;
    evs_game_time = 0;

    _setFadeDir(menuPlay2->watchMenuRef, 1);
    _setNextMain(menuPlay2->watchMenuRef, MAIN_12);
}

void menuPlay2_update(MenuPlay2 *menuPlay2) {
    MenuItem *rootItem = _getRootItem(menuPlay2->watchMenuRef);
    s32 i;

    switch (menuPlay2->unk_0004) {
        case 0:
        case 1:
            func_80046614(&menuPlay2->unk_0034, 1);
            break;

        default:
            func_80046614(&menuPlay2->unk_0034, -1);
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
    func_800464BC(&menuPlay2->unk_0034, rootItem);
}

void menuPlay2_draw(MenuPlay2 *menuPlay2, Gfx **gfxP) {
    Gfx *gfx = *gfxP;
    MenuItem *rootItem UNUSED = _getRootItem(menuPlay2->watchMenuRef);
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
    MenuItem *item = &menuNmEnt->unk_003C;

    item->unk_14 = arg2;
    item->unk_18 = 0.05f;
    item->unk_1C[1] = item->unk_24[1] - 240.0f;
    func_8004655C(item, arg1);
}

void menuNmEnt_init(MenuNmEnt *menuNmEnt, struct_watchMenu *watchMenuRef, void **heapP UNUSED) {
    s32 i;

    menuNmEnt->watchMenuRef = watchMenuRef;

    switch (_getMode(watchMenuRef)) {
        case MAINMENUMODE_MENUNMENT_24:
        case MAINMENUMODE_MENUNMENT_28:
        case MAINMENUMODE_MENUNMENT_32:
            menuNmEnt->unk_0008 = 2;
            break;

        default:
            menuNmEnt->unk_0008 = 1;
            break;
    }

    for (i = 0; i < menuNmEnt->unk_0008; i++) {
        if (evs_select_name_no[i] != 8) {
            u8 *ptr = &evs_mem_data[evs_select_name_no[i]].mem_use_flg;

            if (_getMode(watchMenuRef) == MAINMENUMODE_MENUNMENT_64) {
                break;
            }
            if (!(*ptr & 1)) {
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

        if ((_getMode(watchMenuRef) == MAINMENUMODE_MENUNMENT_64) && (evs_select_name_no[i] != 8)) {
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
    func_800479A8(&menuNmEnt->unk_030C, watchMenuRef, 0, menuNmEnt->unk_0004, -2, -2, 0x10, 0x10);
    menuNmEnt->unk_030C.unk_01C.b.unk_30 = true;
    menuItem_init(&menuNmEnt->unk_056C, 59, 23);
    menuItem_init(&menuNmEnt->unk_05FC, 0, 16);
    func_80055DFC(menuNmEnt, 1, 0.0f);
}

void func_800560D4(MenuNmEnt *nmEnt) {
    menuNmEnt_update(nmEnt);
}

ASM_DATA;
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

    if (menuNmEnt->unk_003C.unk_18 < 0.0f) {
        return;
    }
    if (menuNmEnt->unk_003C.unk_14 < 1.0f) {
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
            case MAINMENUMODE_MENUNMENT_64:
                break;

            default:
                dm_init_save_mem(temp_s1_2);
                break;
        }

        temp_s1_2->mem_use_flg |= 1;
        for (i = 0; i < ARRAY_COUNT(menuNmEnt->unk_002C[sp24]); i++) {
            temp_s1_2->mem_name[i] = menuNmEnt->unk_002C[sp24][i];
        }

        for (i = sp24 + 1; i < menuNmEnt->unk_0008; i++) {
            if (evs_select_name_no[i] != 8) {
                struct_evs_mem_data *ptr = &evs_mem_data[evs_select_name_no[i]];

                if (_getMode(menuNmEnt->watchMenuRef) == MAINMENUMODE_MENUNMENT_64) {
                    break;
                }
                if (!(ptr->mem_use_flg & 1)) {
                    break;
                }
            }
        }

        if (i >= menuNmEnt->unk_0008) {
            MainMenuMode sp30;

            _eepWritePlayer(menuNmEnt->watchMenuRef);

            switch (_getMode(menuNmEnt->watchMenuRef)) {
                case MAINMENUMODE_MENUNMENT_3:
                    sp30 = MAINMENUMODE_MENUSTORY_4;
                    break;

                case MAINMENUMODE_MENUNMENT_6:
                    sp30 = MAINMENUMODE_MENULVSEL_7;
                    break;

                case MAINMENUMODE_MENUNMENT_9:
                    sp30 = MAINMENUMODE_MENULVSEL_10;
                    break;

                case MAINMENUMODE_MENUNMENT_12:
                    sp30 = MAINMENUMODE_MENULVSEL_13;
                    break;

                case MAINMENUMODE_MENUNMENT_15:
                    sp30 = MAINMENUMODE_MENUCHSEL_16;
                    break;

                case MAINMENUMODE_MENUNMENT_19:
                    sp30 = MAINMENUMODE_MENUCHSEL_20;
                    break;

                case MAINMENUMODE_MENUNMENT_24:
                    sp30 = MAINMENUMODE_MENUCHSEL_25;
                    break;

                case MAINMENUMODE_MENUNMENT_28:
                    sp30 = MAINMENUMODE_MENUCHSEL_29;
                    break;

                case MAINMENUMODE_MENUNMENT_32:
                    sp30 = MAINMENUMODE_MENUCHSEL_33;
                    break;

                case MAINMENUMODE_MENUNMENT_63:
                case MAINMENUMODE_MENUNMENT_64:
                    sp30 = MAINMENUMODE_MENUMAIN_0;
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

                if (_getMode(menuNmEnt->watchMenuRef) == MAINMENUMODE_MENUNMENT_64) {
                    break;
                }
                if (!(ptr->mem_use_flg & 1)) {
                    break;
                }
            }
        }

        if (i < 0) {
            switch (_getMode(menuNmEnt->watchMenuRef)) {
                case MAINMENUMODE_MENUNMENT_64:
                    _setMode(menuNmEnt->watchMenuRef, MAINMENUMODE_MENUMAIN_0);
                    break;

                default:
                    _setMode(menuNmEnt->watchMenuRef, MAINMENUMODE_MENUMAIN_0);
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
    MenuItem *rootItem = _getRootItem(menuNmEnt->watchMenuRef);

    func_800464BC(&menuNmEnt->unk_003C, rootItem);
    func_800464BC(&menuNmEnt->unk_00CC, &menuNmEnt->unk_003C);
    func_800464BC(&menuNmEnt->unk_015C, &menuNmEnt->unk_00CC);
    func_800464BC(&menuNmEnt->unk_01EC, &menuNmEnt->unk_003C);

    menuNmEnt->unk_030C.unk_014 = (menuNmEnt->unk_000C[menuNmEnt->unk_0004] == -1) ? 0x10 : 0x32;
    menuNmEnt->unk_030C.unk_010 = menuNmEnt->unk_0004;

    func_8004667C(&menuNmEnt->unk_027C, menuNmEnt->unk_001C[menuNmEnt->unk_0004][0] * 0xF,
                  menuNmEnt->unk_001C[menuNmEnt->unk_0004][1] * 0xD);
    func_800464BC(&menuNmEnt->unk_027C, &menuNmEnt->unk_01EC);
    menuCursor_update(&menuNmEnt->unk_030C, &menuNmEnt->unk_027C);
    func_800464BC(&menuNmEnt->unk_056C, &menuNmEnt->unk_00CC);
    menuNmEnt->unk_05FC.unk_24[0] = menuNmEnt->unk_0034[menuNmEnt->unk_0004] * 0xD;
    func_800464BC(&menuNmEnt->unk_05FC, &menuNmEnt->unk_056C);
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
    var_s3 = menuNmEnt->unk_01EC.pos[1];
    var_s2 = _nameEntry_charTable[menuNmEnt->unk_0014[menuNmEnt->unk_0004]];
    for (var_s4 = 0; var_s4 < 9; var_s4++) {
        var_s0 = menuNmEnt->unk_01EC.pos[0];

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
    var_s0 = menuNmEnt->unk_056C.pos[0];
    var_s3 = menuNmEnt->unk_056C.pos[1];
    for (var_s4 = 0; var_s4 < 4; var_s4++) {
        fontXX_drawID(&gfx, var_s0, var_s3, 12.0f, 12.0f, (u8)menuNmEnt->unk_002C[menuNmEnt->unk_0004][var_s4]);
        var_s0 += 0xD;
    }

    gSPDisplayList(gfx++, fade_alpha_texture_init_dl);

    temp_s1 = _getTexName(menuNmEnt->watchMenuRef, 0);
    temp = _getTexName(menuNmEnt->watchMenuRef, 1);
    menuItem_drawAlphaTex(&menuNmEnt->unk_05FC, &gfx, temp_s1, temp, 0);

    sp24[0] = &menuNmEnt->unk_030C;
    func_80048634(sp24, 1, &gfx);

    *gfxP = gfx;
}

void func_80056C84(MenuRankBase *menuRankBase, struct_watchMenu *watchMenuRef, s32 arg2, s32 arg3) {
    menuRankBase->watchMenuRef = watchMenuRef;
    menuItem_init(&menuRankBase->unk_04, arg2, arg3);
}

void func_80056CAC(MenuRankBase *arg0, MenuItem *arg1) {
    func_800464BC(&arg0->unk_04, arg1);
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
            MenuItem *item = &temp_v0->unk_04;
            f32 temp_fs0 = item->pos[1];
            TiTexData *temp;

            item->pos[1] = temp_fs0 + i * 8;
            temp = _getTexRank(temp_v0->watchMenuRef, 5);
            var_s3 += func_80046F58(item, &gfx, temp, var_s3, 2, i);
            item->pos[1] = temp_fs0;
        }
    }

    *gfxP = gfx;
}

void func_80056DF0(MenuRankNum *menuRankNum, struct_watchMenu *watchMenuRef, s32 arg2, s32 arg3, s32 arg4) {
    menuRankNum->watchMenuRef = watchMenuRef;
    menuRankNum->unk_04 = arg2;
    menuItem_init(&menuRankNum->unk_08, arg3, arg4);
}

void func_80056E1C(MenuRankNum *arg0, MenuItem *arg1) {
    func_800464BC(&arg0->unk_08, arg1);
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
            MenuItem *item = &rankNum->unk_08;
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

                temp_fs1 = item->pos[0];
                temp_fs0 = item->pos[1];

                item->pos[0] += 2.0f;
                item->pos[1] += 2.0f;

                cached += func_8004714C(item, &gfx, temp_s2, temp_v0_2, cached, 0xC, rankNum->unk_04 + 2);
                item->pos[0] = temp_fs1;
                item->pos[1] = temp_fs0;
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
    MenuItem *item;
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
        item->unk_6C[0][i] = item->unk_6C[1][i] = ptr[i] * (DOUBLE_LITERAL(1) / 255);
    }
}

void menuRankFig_update(MenuRankFig *rankFig, MenuItem *arg1) {
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

    func_800464BC(&rankFig->unk_38, arg1);
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

MainMenuMode _menuAll_lastMode = MAINMENUMODE_MENUMAIN_0;

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
            MenuItem *item = &rankFig->unk_38;
            s32 k;

            for (k = 0; k < rankFig->unk_08; k++) {
                if ((i != rankFig->unk_0C[k]) || menuItem_outOfScreen(item, sp24, 0xC)) {
                    continue;
                }

                func_80046844(item, &gfx);

#if VERSION_US || VERSION_GW
                if (fontXX_drawID2(&gfx, item->pos[0] + _posX_tbl_9716[rankFig->unk_04 - 7][k] * item->unk_30[0],
                                   item->pos[1], item->unk_30[0] * 9.0f, item->unk_30[1] * 12.0f, index)) {
                    index = -1;
                }
#elif VERSION_CN
                if ((rankFig->unk_08 >= 6) && (rankFig->unk_0C[0] == 0xB) && (rankFig->unk_0C[1] == 0xC) &&
                    (rankFig->unk_0C[2] == 0x12) && (rankFig->unk_0C[3] == 0xC) &&
                    (rankFig->unk_0C[4] == rankFig->unk_0C[0])) {
                    if (k < 5) {
                        continue;
                    }
                    fontXX_drawID2(&gfx, item->pos[0] + _posX_tbl_9716[rankFig->unk_04 - 7][k - 2] * item->unk_30[0],
                                   item->pos[1], item->unk_30[0] * sp24, item->unk_30[1] * 12.0f, index);
                } else {
                    fontXX_drawID2(&gfx, item->pos[0] + _posX_tbl_9716[rankFig->unk_04 - 7][k] * item->unk_30[0],
                                   item->pos[1], item->unk_30[0] * sp24, item->unk_30[1] * 12.0f, index);
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
    MenuItem *item;
    s32 i;

    menuRankName->watchMenuRef = watchMenuRef;
    for (i = 0; i < ARRAY_COUNTU(menuRankName->unk_04); i++) {
        menuRankName->unk_04[i] = arg2[i];
    }

    item = &menuRankName->unk_08;
    menuItem_init(item, arg3, arg4);

    for (i = 0; i < ARRAY_COUNT(RO_800B1210); i++) {
        item->unk_6C[0][i] = item->unk_6C[1][i] = RO_800B1210[i] * (DOUBLE_LITERAL(1) / 255);
    }
}

void func_80057724(MenuRankName *arg0, MenuItem *arg1) {
    func_800464BC(&arg0->unk_08, arg1);
}

void menuRankName_draw(MenuRankName *rankNameArr[], s32 count, Gfx **gfxP) {
    Gfx *gfx = *gfxP;
    MenuItem *temp_s1;
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

        var_fs0 = temp_s1->pos[0];
        func_80046844(temp_s1, &gfx);

        for (var_s0 = 0; var_s0 < 4; var_s0++) {
            fontXX_drawID2(&gfx, var_fs0, temp_s1->pos[1], 12.0f, temp_s1->unk_30[1] * 12.0f, temp_s2->unk_04[var_s0]);
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

void func_800578C8(MenuRankLabel *arg0, MenuItem *arg1) {
    func_800464BC(&arg0->unk_0C, arg1);
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
                MenuItem *item = &rankLabel->unk_0C;
                TiTexData *var_a2;

                if ((i != rankLabel->type) || (j != rankLabel->id)) {
                    continue;
                }

                switch (i) {
                    case 0:
                        var_a2 = _getTexRank(rankLabel->watchMenuRef, 7);
                        var_s0 += func_80046F58(item, &gfx, var_a2, var_s0, var_s5, j);
                        break;

                    case 1:
                    case 2:
                        var_a2 = _getTexRank(rankLabel->watchMenuRef, _tex_9880[i]);
                        var_s0 += func_80046F58(item, &gfx, var_a2, var_s0, var_s5, j);
                        break;

                    case 3:
                        var_a2 = _getTexCommon(rankLabel->watchMenuRef, 0xE);
                        var_s0 += func_80046F58(item, &gfx, var_a2, var_s0, 0x2F, _choice_9881[j]);
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

void func_80057BE8(MenuRankHeader *rankHeader, MenuItem *arg1) {
    s32 i;

    func_800464BC(&rankHeader->unk_08, arg1);

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

void menuRankPanel_update(MenuRankPanel *arg0, MenuItem *arg1) {
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
    MenuItem *sp18[3];
    s32 i;

    sp18[0] = &menuRank->unk_032C;
    sp18[1] = &menuRank->unk_020C[0];
    sp18[2] = &menuRank->unk_020C[1];
    for (i = 0; i < ARRAY_COUNTU(sp18); i++) {
        MenuItem *item = sp18[i];
        f32 temp = 8.0f;

        item->unk_40[1] = 0.0f;
        item->unk_18 = 0.1f;
        item->unk_3C = 0.1f;
        item->unk_14 = arg2;
        item->unk_38 = arg2;
        item->unk_1C[0] = item->unk_24[0];
        item->unk_1C[1] = item->unk_24[1] + temp;
        item->unk_40[0] = item->unk_48[0];
        func_8004655C(item, arg1);
        func_800465B8(item, arg1);
    }
}

void menuRank_setSlide(MenuRank *menuRank, s32 arg1, s32 arg2, f32 arg3, f32 arg4) {
    MenuRank_unk_590 *temp_s2 = &menuRank->unk_590[arg1];
    MenuItem *item;
    s32 i;

    item = &temp_s2->unk_0004.unk_08;
    item->unk_1C[0] = item->unk_24[0] + arg4;
    item->unk_1C[1] = item->unk_24[1];
    item->unk_18 = 0.05f;
    item->unk_14 = arg3;
    func_8004655C(item, arg2);

    for (i = 0; i < temp_s2->unk_0000; i++) {
        item = &temp_s2->unk_3A8[i].unk_008.unk_04;

        item->unk_1C[0] = item->unk_24[0] + arg4;
        item->unk_1C[1] = item->unk_24[1];
        item->unk_18 = 0.05f;
        item->unk_14 = arg3;
        func_8004655C(item, arg2);
    }

    arg2 = (arg2 < 0) ? -1 : 1;

    for (i = 0; i < temp_s2->unk_0000; i++) {
        item = &temp_s2->unk_3A8[i].unk_008.unk_04;

        item->unk_18 -= arg2 * 0.05 * i / (temp_s2->unk_0000 * 2);
        func_8004655C(item, arg2);
    }
}

const s32 _pos_10346[] = {
    -0x140,
    0x140,
};

void menuRank_setFrame(MenuRank *menuRank, s32 arg1, s32 arg2, f32 arg3) {
    MenuRank_unk_590 *temp_fp = &menuRank->unk_590[arg1];
    MenuItem *item;
    s32 i;

    item = &menuRank->unk_03BC.unk_0C;
    item->unk_1C[0] = item->unk_24[0];
    item->unk_1C[1] = item->unk_24[1] - 120.0f;
    item->unk_18 = 0.05f;
    item->unk_14 = arg3;
    func_8004655C(item, arg2);

    for (i = 0; i < ARRAY_COUNTU(menuRank->unk_020C); i++) {
        item = &menuRank->unk_020C[i];

        item->unk_1C[0] = item->unk_24[0];
        item->unk_1C[1] = item->unk_24[1] - 120.0f;
        item->unk_18 = 0.05f;
        item->unk_14 = arg3;
        func_8004655C(item, arg2);
    }

    item = &temp_fp->unk_0004.unk_08;
    item->unk_1C[0] = item->unk_24[0];
    item->unk_1C[1] = item->unk_24[1] - 120.0f;
    item->unk_18 = 0.05f;
    item->unk_14 = arg3;
    func_8004655C(item, arg2);

    item = &menuRank->unk_032C;
    item->unk_1C[0] = item->unk_24[0];
    item->unk_1C[1] = item->unk_24[1] - 120.0f;
    item->unk_18 = 0.05f;
    item->unk_14 = arg3;
    func_8004655C(item, arg2);

    for (i = 0; i < temp_fp->unk_0000; i++) {
        item = &temp_fp->unk_3A8[i].unk_008.unk_04;

        item->unk_1C[0] = item->unk_24[0] + _pos_10346[i % ARRAY_COUNTU(_pos_10346)];
        item->unk_1C[1] = item->unk_24[1];
        item->unk_18 = 0.05f;
        item->unk_14 = arg3;
        func_8004655C(item, arg2);
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

static_assert(ARRAY_COUNT(_hedAllType_10392) <= MENURAKHEADER_UNK_98, "");

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
        case MAINMENUMODE_MENURANK_49:
            sp3C = 0;
            break;

        case MAINMENUMODE_MENURANK_50:
            sp3C = 1;
            break;

        case MAINMENUMODE_MENURANK_53:
            sp3C = 2;
            break;

        case MAINMENUMODE_MENURANK_56:
            sp3C = 3;
            break;

        case MAINMENUMODE_MENURANK_54:
        case MAINMENUMODE_MENURANK_57:
            sp3C = 4;
            break;

        case MAINMENUMODE_MENURANK_51:
            sp3C = 5;
            break;

        case MAINMENUMODE_MENURANK_52:
        case MAINMENUMODE_MENURANK_58:
            sp3C = 6;
            break;

        default:
            break;
    }

    switch (arg2) {
        case MAINMENUMODE_MENURANK_49:
            count = ARRAY_COUNT(_hedStoryId_10393);
            idP = _hedStoryId_10393;
            xP = _hedStoryX_10394;
            yP = _hedStoryY_10395;
            break;

        case MAINMENUMODE_MENURANK_50:
            count = ARRAY_COUNT(_hedLevelId_10396);
            idP = _hedLevelId_10396;
            xP = _hedLevelX_10397;
            yP = _hedLevelY_10398;
            break;

        case MAINMENUMODE_MENURANK_51:
            count = ARRAY_COUNT(_hed1PTaiQId_10399);
            idP = _hed1PTaiQId_10399;
            xP = _hed1PTaiQX_10400;
            yP = _hed1PTaiQY_10401;
            break;

        case MAINMENUMODE_MENURANK_52:
            count = ARRAY_COUNT(_hed1PTimeAtId_10402);
            idP = _hed1PTimeAtId_10402;
            xP = _hed1PTimeAtX_10403;
            yP = _hed1PTimeAtY_10404;
            break;

        case MAINMENUMODE_MENURANK_53:
        case MAINMENUMODE_MENURANK_54:
        case MAINMENUMODE_MENURANK_56:
        case MAINMENUMODE_MENURANK_57:
        case MAINMENUMODE_MENURANK_58:
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
            case MAINMENUMODE_MENURANK_49:
                var_s1 = temp_s2->story_sort[arg3][i];
                ptr = &evs_mem_data[var_s1];
                temp_t0 = &ptr->story_data[arg3];
                func_80057D24(&temp_s3->unk_3A8[i], menuRank->watchMenuRef, temp_s2->story_rank[arg3][i], ptr->mem_name,
                              temp_t0->score, temp_t0->time, temp_t0->c_stage + 1, 0, i * 0x11);
                break;

            case MAINMENUMODE_MENURANK_50:
                var_s1 = temp_s2->level_sort[arg3][i];
                ptr = &evs_mem_data[var_s1];
                temp_t0_2 = &ptr->level_data[arg3];
                func_80057E68(&temp_s3->unk_3A8[i], menuRank->watchMenuRef, temp_s2->level_rank[arg3][i], ptr->mem_name,
                              (s32)temp_t0_2->c_level, temp_t0_2->score, 0, i * 0x11);
                break;

            case MAINMENUMODE_MENURANK_51:
                var_s1 = temp_s2->taiQ_sort[arg3][i];
                ptr = &evs_mem_data[var_s1];
                temp_t0_3 = &ptr->taiQ_data[arg3];
                func_80057F6C(&temp_s3->unk_3A8[i], menuRank->watchMenuRef, temp_s2->taiQ_rank[arg3][i], ptr->mem_name,
                              temp_t0_3->time, temp_t0_3->score, 0, i * 0x11);
                break;

            case MAINMENUMODE_MENURANK_52:
                var_s1 = temp_s2->timeAt_sort[arg3][i];
                ptr = &evs_mem_data[var_s1];
                temp_t0_4 = &ptr->timeAt_data[arg3];
                func_8005806C(&temp_s3->unk_3A8[i], menuRank->watchMenuRef, temp_s2->timeAt_rank[arg3][i],
                              ptr->mem_name, temp_t0_4->score, temp_t0_4->time, temp_t0_4->erase, arg3, 0, i * 0x11);
                break;

            case MAINMENUMODE_MENURANK_53:
                var_s1 = temp_s2->vscom_sort[i];
                ptr = &evs_mem_data[var_s1];
                var_s7 = temp_s2->vscom_ave;
                var_s6 = temp_s2->vscom_rank;
                var_s4 = ptr->vscom_data;
                break;

            case MAINMENUMODE_MENURANK_54:
                var_s1 = temp_s2->vc_fl_sort[i];
                ptr = &evs_mem_data[var_s1];
                var_s7 = temp_s2->vc_fl_ave;
                var_s6 = temp_s2->vc_fl_rank;
                var_s4 = ptr->vc_fl_data;
                break;

            case MAINMENUMODE_MENURANK_56:
                var_s1 = temp_s2->vsman_sort[i];
                ptr = &evs_mem_data[var_s1];
                var_s7 = temp_s2->vsman_ave;
                var_s6 = temp_s2->vsman_rank;
                var_s4 = ptr->vsman_data;
                break;

            case MAINMENUMODE_MENURANK_57:
                var_s1 = temp_s2->vm_fl_sort[i];
                ptr = &evs_mem_data[var_s1];
                var_s7 = temp_s2->vm_fl_ave;
                var_s6 = temp_s2->vm_fl_rank;
                var_s4 = ptr->vm_fl_data;
                break;

            case MAINMENUMODE_MENURANK_58:
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
            case MAINMENUMODE_MENURANK_53:
            case MAINMENUMODE_MENURANK_54:
            case MAINMENUMODE_MENURANK_56:
            case MAINMENUMODE_MENURANK_57:
            case MAINMENUMODE_MENURANK_58:
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
        case MAINMENUMODE_MENURANK_49:
            dm_data_mode_story_sort(&menuRank->unk_001C);
            break;

        case MAINMENUMODE_MENURANK_50:
            dm_data_mode_level_sort(&menuRank->unk_001C);
            break;

        case MAINMENUMODE_MENURANK_51:
            dm_data_mode_taiQ_sort(&menuRank->unk_001C);
            break;

        case MAINMENUMODE_MENURANK_52:
            dm_data_mode_timeAt_sort(&menuRank->unk_001C);
            break;

        case MAINMENUMODE_MENURANK_53:
            dm_data_vscom_sort(&menuRank->unk_001C);
            break;

        case MAINMENUMODE_MENURANK_54:
            dm_data_vc_fl_sort(&menuRank->unk_001C);
            break;

        case MAINMENUMODE_MENURANK_56:
            dm_data_vsman_sort(&menuRank->unk_001C);
            break;

        case MAINMENUMODE_MENURANK_57:
            dm_data_vm_fl_sort(&menuRank->unk_001C);
            break;

        case MAINMENUMODE_MENURANK_58:
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
    MenuItem *item = &menuRank->unk_032C;

    if ((item->unk_38 == 0.0f) && (item->unk_3C < 0.0f)) {
        menuRank_setNameBaseScale(menuRank, 1, 0.0f);
    }

    item = &temp_s0->unk_3A8[0].unk_008.unk_04;
    if ((item->unk_14 < 1.0f) || (item->unk_18 < 0.0f) || (item->unk_38 < 1.0f) || (item->unk_3C < 0.0f)) {
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
        _setMode(menuRank->watchMenuRef, MAINMENUMODE_MENUMAIN_0);
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
    MenuItem *rootItem = _getRootItem(menuRank->watchMenuRef);
    s32 i;

    func_800464BC(&menuRank->unk_017C, rootItem);
    func_800464F8(&menuRank->unk_020C[i], ARRAY_COUNT(menuRank->unk_020C), rootItem);

    func_800464BC(&menuRank->unk_032C, rootItem);

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

        if (menuRank->unk_032C.unk_3C < 0.0f) {
            menuRank->unk_04F4.id = menuRank->unk_0010;
        } else {
            menuRank->unk_04F4.id = menuRank->unk_000C;
        }

        switch (menuRank->unk_0004) {
            case MAINMENUMODE_MENURANK_50:
                menuRank->unk_0458.id = 1;
                menuRank->unk_04F4.id = menuRank->unk_04F4.id + 3;
                break;

            default:
                menuRank->unk_0458.id = 0;
                break;
        }

        menuRankLabel_draw((void *)sp18, 2, &gfx);

        for (i = 0; i < ARRAY_COUNTU(menuRank->unk_020C); i++) {
            MenuItem *temp_s0 = &menuRank->unk_020C[i];
            f32 temp_fs0 = temp_s0->pos[0];
            f32 temp_fs1 = temp_s0->pos[1];
            s32 var_v0 = (temp_s0->unk_3C < 0.0f) ? menuRank->unk_0010 : menuRank->unk_000C;

            j = WrapI(0, 3, var_v0 + _dir_10660[i]);
            if (menuRank->unk_0004 == MAINMENUMODE_MENURANK_50) {
                j += 3;
            }

            func_80046F58(temp_s0, &gfx, _getTexRank(menuRank->watchMenuRef, 4), 0, 2, i);
            temp_s0->pos[0] += 12.0f;
            temp_s0->pos[1] += 2.0f;

            func_80046F58(&menuRank->unk_020C[i], &gfx, _getTexRank(menuRank->watchMenuRef, 2), 0, 6, j);
            temp_s0->pos[0] = temp_fs0;
            temp_s0->pos[1] = temp_fs1;
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

MenuItem *_getRootItem(struct_watchMenu *watchMenuRef) {
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
    RomOffsetPair *pairArray = _romDataTbl;

    arg0->sched = sc;
    arg0->unk_02460 = sp10;

    osCreateMesgQueue(&arg0->scMQ, arg0->scMsgBuf, ARRAY_COUNT(arg0->scMsgBuf));
    nnScAddClient(sc, &arg0->scClient, &arg0->scMQ);

    for (i = 0; i < ARRAY_COUNT(arg0->unk_00048); i++) {
        arg0->unk_02448[i] = &arg0->unk_00048[i][0];
        arg0->unk_02454[i] = &arg0->unk_00C48[i][0];
    }

    sp10 = init_menu_bg(sp10, evs_level_21 != 0);

    arg0->unk_02478 = tiLoadTexData(&sp10, pairArray[ROMDATATBL_MENU_CHAR].start, pairArray[ROMDATATBL_MENU_CHAR].end);
    arg0->unk_0247C =
        tiLoadTexData(&sp10, pairArray[ROMDATATBL_MENU_COMMON].start, pairArray[ROMDATATBL_MENU_COMMON].end);
    arg0->unk_02484 =
        tiLoadTexData(&sp10, pairArray[ROMDATATBL_MENU_LEVEL].start, pairArray[ROMDATATBL_MENU_LEVEL].end);
    arg0->unk_02488 = tiLoadTexData(&sp10, pairArray[ROMDATATBL_MENU_MAIN].start, pairArray[ROMDATATBL_MENU_MAIN].end);
    arg0->unk_0248C = tiLoadTexData(&sp10, pairArray[ROMDATATBL_MENU_NAME].start, pairArray[ROMDATATBL_MENU_NAME].end);
    arg0->unk_02490 = tiLoadTexData(&sp10, pairArray[ROMDATATBL_MENU_P2].start, pairArray[ROMDATATBL_MENU_P2].end);
    arg0->unk_02494 = tiLoadTexData(&sp10, pairArray[ROMDATATBL_MENU_P4].start, pairArray[ROMDATATBL_MENU_P4].end);
    arg0->unk_02498 = tiLoadTexData(&sp10, pairArray[ROMDATATBL_MENU_RANK].start, pairArray[ROMDATATBL_MENU_RANK].end);
    arg0->unk_0249C =
        tiLoadTexData(&sp10, pairArray[ROMDATATBL_MENU_SETUP].start, pairArray[ROMDATATBL_MENU_SETUP].end);
    arg0->unk_024A0 =
        tiLoadTexData(&sp10, pairArray[ROMDATATBL_MENU_STORY].start, pairArray[ROMDATATBL_MENU_STORY].end);
    arg0->unk_024A4 = tiLoadTexData(&sp10, pairArray[ROMDATATBL_GAME_AL].start, pairArray[ROMDATATBL_GAME_AL].end);
    arg0->unk_024A8 = tiLoadTexData(&sp10, pairArray[ROMDATATBL_GAME_P1].start, pairArray[ROMDATATBL_GAME_P1].end);
    arg0->unk_024AC = tiLoadTexData(&sp10, pairArray[ROMDATATBL_MENU_CONT].start, pairArray[ROMDATATBL_MENU_CONT].end);
    arg0->unk_024B0 =
        tiLoadTexData(&sp10, pairArray[ROMDATATBL_TUTORIAL_KASA].start, pairArray[ROMDATATBL_TUTORIAL_KASA].end);
    arg0->unk_024B4 = tiLoadTexData(&sp10, pairArray[ROMDATATBL_MENU_KASA].start, pairArray[ROMDATATBL_MENU_KASA].end);

    menuItem_init(&arg0->unk_024B8[0], 0, 0);
    func_800474EC(&arg0->unk_02548, arg0, 0x70, 0x12);

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
        case MAINMENUMODE_MENUMAIN_0:
            func_8004F2D8(&arg0->unk_02678[index].menuMain);
            break;

        case MAINMENUMODE_MENUSTORY_4:
            func_80051974(&arg0->unk_02678[index].menuStory);
            break;

        case MAINMENUMODE_MENULVSEL_7:
        case MAINMENUMODE_MENULVSEL_10:
        case MAINMENUMODE_MENULVSEL_13:
            func_80052DF0(&arg0->unk_02678[index].menuLvSel);
            break;

        case MAINMENUMODE_MENUPLAY2_17:
        case MAINMENUMODE_MENUPLAY2_21:
        case MAINMENUMODE_MENUPLAY2_26:
        case MAINMENUMODE_MENUPLAY2_30:
        case MAINMENUMODE_MENUPLAY2_34:
        case MAINMENUMODE_MENUPLAY2_41:
        case MAINMENUMODE_MENUPLAY2_43:
        case MAINMENUMODE_MENUPLAY2_45:
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

    if (arg0->unk_111CC != MAINMENUMODE_MENUMAIN_0) {
        _setTitle(arg0, arg0->unk_111CC);
    }

    switch (arg0->unk_111CC) {
        case MAINMENUMODE_MENUMAIN_0:
            menuMain_init(&arg0->unk_02678[index].menuMain, arg0, &arg0->unk_02470[index]);
            break;

        case MAINMENUMODE_MENUSTORY_4:
            menuStory_init(&arg0->unk_02678[index].menuStory, arg0, &arg0->unk_02470[index]);
            break;

        case MAINMENUMODE_MENULVSEL_7:
        case MAINMENUMODE_MENULVSEL_10:
        case MAINMENUMODE_MENULVSEL_13:
            menuLvSel_init(&arg0->unk_02678[index].menuLvSel, arg0, &arg0->unk_02470[index]);
            break;

        case MAINMENUMODE_MENUPLAY2_17:
        case MAINMENUMODE_MENUPLAY2_21:
        case MAINMENUMODE_MENUPLAY2_26:
        case MAINMENUMODE_MENUPLAY2_30:
        case MAINMENUMODE_MENUPLAY2_34:
        case MAINMENUMODE_MENUPLAY2_41:
        case MAINMENUMODE_MENUPLAY2_43:
        case MAINMENUMODE_MENUPLAY2_45:
            menuPlay2_init(&arg0->unk_02678[index].menuPlay2, arg0, &arg0->unk_02470[index]);
            break;

        case MAINMENUMODE_MENUCHSEL_16:
        case MAINMENUMODE_MENUCHSEL_20:
        case MAINMENUMODE_MENUCHSEL_25:
        case MAINMENUMODE_MENUCHSEL_29:
        case MAINMENUMODE_MENUCHSEL_33:
        case MAINMENUMODE_MENUCHSEL_40:
        case MAINMENUMODE_MENUCHSEL_42:
        case MAINMENUMODE_MENUCHSEL_44:
            menuChSel_init(&arg0->unk_02678[index].menuChSel, arg0, &arg0->unk_02470[index]);
            break;

        case MAINMENUMODE_MENUNMENT_3:
        case MAINMENUMODE_MENUNMENT_6:
        case MAINMENUMODE_MENUNMENT_9:
        case MAINMENUMODE_MENUNMENT_12:
        case MAINMENUMODE_MENUNMENT_15:
        case MAINMENUMODE_MENUNMENT_19:
        case MAINMENUMODE_MENUNMENT_24:
        case MAINMENUMODE_MENUNMENT_28:
        case MAINMENUMODE_MENUNMENT_32:
        case MAINMENUMODE_MENUNMENT_63:
        case MAINMENUMODE_MENUNMENT_64:
            menuNmEnt_init(&arg0->unk_02678[index].menuNmEnt, arg0, &arg0->unk_02470[index]);
            break;

        case MAINMENUMODE_MENURANK_49:
        case MAINMENUMODE_MENURANK_50:
        case MAINMENUMODE_MENURANK_51:
        case MAINMENUMODE_MENURANK_52:
        case MAINMENUMODE_MENURANK_53:
        case MAINMENUMODE_MENURANK_54:
        case MAINMENUMODE_MENURANK_56:
        case MAINMENUMODE_MENURANK_57:
        case MAINMENUMODE_MENURANK_58:
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
        case MAINMENUMODE_MENUMAIN_0:
            menuMain_input(&arg0->unk_02678[index].menuMain);
            break;

        case MAINMENUMODE_MENUSTORY_4:
            menuStory_input(&arg0->unk_02678[index].menuStory);
            break;

        case MAINMENUMODE_MENULVSEL_7:
        case MAINMENUMODE_MENULVSEL_10:
        case MAINMENUMODE_MENULVSEL_13:
            menuLvSel_input(&arg0->unk_02678[index].menuLvSel);
            break;

        case MAINMENUMODE_MENUPLAY2_17:
        case MAINMENUMODE_MENUPLAY2_21:
        case MAINMENUMODE_MENUPLAY2_26:
        case MAINMENUMODE_MENUPLAY2_30:
        case MAINMENUMODE_MENUPLAY2_34:
        case MAINMENUMODE_MENUPLAY2_41:
        case MAINMENUMODE_MENUPLAY2_43:
        case MAINMENUMODE_MENUPLAY2_45:
            menuPlay2_input(&arg0->unk_02678[index].menuPlay2);
            break;

        case MAINMENUMODE_MENUCHSEL_16:
        case MAINMENUMODE_MENUCHSEL_20:
        case MAINMENUMODE_MENUCHSEL_25:
        case MAINMENUMODE_MENUCHSEL_29:
        case MAINMENUMODE_MENUCHSEL_33:
        case MAINMENUMODE_MENUCHSEL_40:
        case MAINMENUMODE_MENUCHSEL_42:
        case MAINMENUMODE_MENUCHSEL_44:
            menuChSel_input(&arg0->unk_02678[index].menuChSel);
            break;

        case MAINMENUMODE_MENUNMENT_3:
        case MAINMENUMODE_MENUNMENT_6:
        case MAINMENUMODE_MENUNMENT_9:
        case MAINMENUMODE_MENUNMENT_12:
        case MAINMENUMODE_MENUNMENT_15:
        case MAINMENUMODE_MENUNMENT_19:
        case MAINMENUMODE_MENUNMENT_24:
        case MAINMENUMODE_MENUNMENT_28:
        case MAINMENUMODE_MENUNMENT_32:
        case MAINMENUMODE_MENUNMENT_63:
        case MAINMENUMODE_MENUNMENT_64:
            menuNmEnt_input(&arg0->unk_02678[index].menuNmEnt);
            break;

        case MAINMENUMODE_MENURANK_49:
        case MAINMENUMODE_MENURANK_50:
        case MAINMENUMODE_MENURANK_51:
        case MAINMENUMODE_MENURANK_52:
        case MAINMENUMODE_MENURANK_53:
        case MAINMENUMODE_MENURANK_54:
        case MAINMENUMODE_MENURANK_56:
        case MAINMENUMODE_MENURANK_57:
        case MAINMENUMODE_MENURANK_58:
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
    MenuItem *var_v1 = &arg0->unk_024B8[0];
    MainMenuMode var_a0;
    f32 temp_f2_2;
    s32 i;
    s32 var_v1_2;

    arg0->unk_111DC = CLAMP(arg0->unk_111DC + arg0->unk_111E0, 0.0f, 1.0f);

    temp_f2_2 = (arg0->unk_111DC - DOUBLE_LITERAL(0.5)) * DOUBLE_LITERAL(1.2) + DOUBLE_LITERAL(0.5);
    temp_f2_2 = DOUBLE_LITERAL(1) - CLAMP(temp_f2_2, 0.0f, 1.0f);

    for (i = 0; i < 3; i++) {
        var_v1->unk_6C[1][i] = temp_f2_2;
        var_v1->unk_6C[0][i] = temp_f2_2;
    }

#ifdef NN_SC_PERF
    if (_getKeyTrg(arg0, 0) & Z_TRIG) {
        arg0->unk_cn_pad = arg0->unk_cn_pad == 0;
    }
#endif

    func_800464F8(arg0->unk_024B8, ARRAY_COUNT(arg0->unk_024B8), NULL);
    func_80047584(&arg0->unk_02548, &arg0->unk_024B8[0]);

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
            case MAINMENUMODE_MENUMAIN_0:
                menuMain_update(&arg0->unk_02678[var_v1_2].menuMain);
                break;

            case MAINMENUMODE_MENUSTORY_4:
                menuStory_update(&arg0->unk_02678[var_v1_2].menuStory);
                break;

            case MAINMENUMODE_MENULVSEL_7:
            case MAINMENUMODE_MENULVSEL_10:
            case MAINMENUMODE_MENULVSEL_13:
                menuLvSel_update(&arg0->unk_02678[var_v1_2].menuLvSel);
                break;

            case MAINMENUMODE_MENUPLAY2_17:
            case MAINMENUMODE_MENUPLAY2_21:
            case MAINMENUMODE_MENUPLAY2_26:
            case MAINMENUMODE_MENUPLAY2_30:
            case MAINMENUMODE_MENUPLAY2_34:
            case MAINMENUMODE_MENUPLAY2_41:
            case MAINMENUMODE_MENUPLAY2_43:
            case MAINMENUMODE_MENUPLAY2_45:
                menuPlay2_update(&arg0->unk_02678[var_v1_2].menuPlay2);
                break;

            case MAINMENUMODE_MENUCHSEL_16:
            case MAINMENUMODE_MENUCHSEL_20:
            case MAINMENUMODE_MENUCHSEL_25:
            case MAINMENUMODE_MENUCHSEL_29:
            case MAINMENUMODE_MENUCHSEL_33:
            case MAINMENUMODE_MENUCHSEL_40:
            case MAINMENUMODE_MENUCHSEL_42:
            case MAINMENUMODE_MENUCHSEL_44:
                menuChSel_update(&arg0->unk_02678[var_v1_2].menuChSel);
                break;

            case MAINMENUMODE_MENUNMENT_3:
            case MAINMENUMODE_MENUNMENT_6:
            case MAINMENUMODE_MENUNMENT_9:
            case MAINMENUMODE_MENUNMENT_12:
            case MAINMENUMODE_MENUNMENT_15:
            case MAINMENUMODE_MENUNMENT_19:
            case MAINMENUMODE_MENUNMENT_24:
            case MAINMENUMODE_MENUNMENT_28:
            case MAINMENUMODE_MENUNMENT_32:
            case MAINMENUMODE_MENUNMENT_63:
            case MAINMENUMODE_MENUNMENT_64:
                menuNmEnt_update(&arg0->unk_02678[var_v1_2].menuNmEnt);
                break;

            case MAINMENUMODE_MENURANK_49:
            case MAINMENUMODE_MENURANK_50:
            case MAINMENUMODE_MENURANK_51:
            case MAINMENUMODE_MENURANK_52:
            case MAINMENUMODE_MENURANK_53:
            case MAINMENUMODE_MENURANK_54:
            case MAINMENUMODE_MENURANK_56:
            case MAINMENUMODE_MENURANK_57:
            case MAINMENUMODE_MENURANK_58:
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
    MenuItem *temp_s4 = &arg0->unk_024B8[0];
    TiTexData *temp_s3;
    s32 i;
    bool cached;

    func_80046844(temp_s4, &gfx);
    draw_menu_bg(&gfx, temp_s4->pos[0] + 0.0f, -temp_s4->pos[1] - 120.0f);

    gSPDisplayList(gfx++, fade_normal_texture_init_dl);
    func_80046844(temp_s4, &gfx);

    cached = false;
    temp_s3 = _getTexCommon(arg0, 2);
    for (i = 0; i < 5; i++) {
        cached += func_80046C74(temp_s4, &gfx, temp_s3, cached, i << 6, 0, 1.0f, 1.0f);
    }

    for (; i < 10; i++) {
        cached += func_80046C74(temp_s4, &gfx, temp_s3, cached, (i - 5) << 6, 200.0f, 1.0f, -1.0f);
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
            case MAINMENUMODE_MENUMAIN_0:
                menuMain_draw(&arg0->unk_02678[index].menuMain, gfxP);
                break;

            case MAINMENUMODE_MENUSTORY_4:
                menuStory_draw(&arg0->unk_02678[index].menuStory, gfxP);
                break;

            case MAINMENUMODE_MENULVSEL_7:
            case MAINMENUMODE_MENULVSEL_10:
            case MAINMENUMODE_MENULVSEL_13:
                menuLvSel_draw(&arg0->unk_02678[index].menuLvSel, gfxP);
                break;

            case MAINMENUMODE_MENUPLAY2_17:
            case MAINMENUMODE_MENUPLAY2_21:
            case MAINMENUMODE_MENUPLAY2_26:
            case MAINMENUMODE_MENUPLAY2_30:
            case MAINMENUMODE_MENUPLAY2_34:
            case MAINMENUMODE_MENUPLAY2_41:
            case MAINMENUMODE_MENUPLAY2_43:
            case MAINMENUMODE_MENUPLAY2_45:
                menuPlay2_draw(&arg0->unk_02678[index].menuPlay2, gfxP);
                break;

            case MAINMENUMODE_MENUCHSEL_16:
            case MAINMENUMODE_MENUCHSEL_20:
            case MAINMENUMODE_MENUCHSEL_25:
            case MAINMENUMODE_MENUCHSEL_29:
            case MAINMENUMODE_MENUCHSEL_33:
            case MAINMENUMODE_MENUCHSEL_40:
            case MAINMENUMODE_MENUCHSEL_42:
            case MAINMENUMODE_MENUCHSEL_44:
                menuChSel_draw(&arg0->unk_02678[index].menuChSel, gfxP);
                break;

            case MAINMENUMODE_MENUNMENT_3:
            case MAINMENUMODE_MENUNMENT_6:
            case MAINMENUMODE_MENUNMENT_9:
            case MAINMENUMODE_MENUNMENT_12:
            case MAINMENUMODE_MENUNMENT_15:
            case MAINMENUMODE_MENUNMENT_19:
            case MAINMENUMODE_MENUNMENT_24:
            case MAINMENUMODE_MENUNMENT_28:
            case MAINMENUMODE_MENUNMENT_32:
            case MAINMENUMODE_MENUNMENT_63:
            case MAINMENUMODE_MENUNMENT_64:
                menuNmEnt_draw(&arg0->unk_02678[index].menuNmEnt, gfxP);
                break;

            case MAINMENUMODE_MENURANK_49:
            case MAINMENUMODE_MENURANK_50:
            case MAINMENUMODE_MENURANK_51:
            case MAINMENUMODE_MENURANK_52:
            case MAINMENUMODE_MENURANK_53:
            case MAINMENUMODE_MENURANK_54:
            case MAINMENUMODE_MENURANK_56:
            case MAINMENUMODE_MENURANK_57:
            case MAINMENUMODE_MENURANK_58:
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
        _menuAll_lastMode = MAINMENUMODE_MENUMAIN_0;
        _menuMain_lastMode = MAINMENUMODE_MENUMAIN_0;
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

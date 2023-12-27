/**
 * Original filename: main_menu.c
 */

#include "libultra.h"
#include "include_asm.h"
#include "macros_defines.h"
#include "unknown_structs.h"
#include "main_segment_functions.h"
#include "main_segment_variables.h"
#include "boot_functions.h"
#include "boot_variables.h"
#include "util.h"
#include "rom_offsets.h"
#include "audio/audio_stuff.h"
#include "buffers.h"
#include "libc/assert.h"
#include "libc/ctype.h"
#include "graphic.h"
#include "record.h"
#include "main1x.h"
#include "028820.h"
#include "tex_func.h"
#include "main_story.h"

#if VERSION_US || CC_CHECK
#include "joy.h"
#endif

#if VERSION_US
f32 func_80045DD0(f32 arg0, f32 arg1) {
    return CLAMP(arg0 + arg1, 0.0f, 1.0f);
}
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", func_80045DD0);
#endif

#if VERSION_US || VERSION_CN
f32 func_80045E18(f32 arg0, f32 arg1) {
    return WrapF(0.0f, 1.0f, arg0 + arg1);
}
#endif

#if VERSION_US || VERSION_CN
f32 func_80045E48(f32 arg0) {
    if (arg0 < 0.5) {
        arg0 = SQ(arg0);
    } else {
        arg0 = 1.0 - arg0;
        arg0 = 0.5 - SQ(arg0);
    }

    return 2.0f * arg0;
}
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/main_menu", func_80045E94);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", func_8004872C_cn);
#endif

#if VERSION_US || VERSION_CN
void transFunc_curve(MenuItem *item) {
    s32 i;
    f32 temp_ft0;
    f32 temp_fv0;

    temp_fv0 = func_80045DD0(item->unk_14, item->unk_18);
    temp_ft0 = func_80045E48(temp_fv0);
    item->unk_14 = temp_fv0;

    for (i = 0; i < ARRAY_COUNTU(item->unk_0C); i++) {
        item->unk_0C[i] = item->unk_1C[i] + ((item->unk_24[i] - item->unk_1C[i]) * temp_ft0);
    }
}
#endif

#if VERSION_US || VERSION_CN
void transFunc_finger(MenuItem *item) {
    s32 i;
    f32 temp_fv0;
    f32 temp_fv0_2;

    temp_fv0 = func_80045E18(item->unk_14, item->unk_18);
    temp_fv0_2 = (sinf(temp_fv0 * (2 * M_PI)) + 1.0) * 0.5;
    item->unk_14 = temp_fv0;

    for (i = 0; i < ARRAY_COUNTU(item->unk_0C); i++) {
        item->unk_0C[i] = item->unk_1C[i] + (item->unk_24[i] - item->unk_1C[i]) * temp_fv0_2;
    }
}
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/main_menu", func_80046008);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", func_8004892C_cn);
#endif

#if VERSION_US || VERSION_CN
void scaleFunc_curve(MenuItem *item) {
    s32 i;
    f32 temp_ft0;
    f32 temp_fv0;

    temp_fv0 = func_80045DD0(item->unk_38, item->unk_3C);
    temp_ft0 = func_80045E48(temp_fv0);
    item->unk_38 = temp_fv0;

    for (i = 0; i < ARRAY_COUNTU(item->unk_30); i++) {
        item->unk_30[i] = item->unk_40[i] + ((item->unk_48[i] - item->unk_40[i]) * temp_ft0);
    }
}
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/main_menu", func_800460DC);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", func_80048A54_cn);
#endif

#if VERSION_US || VERSION_CN
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
#endif

#if VERSION_US || VERSION_CN
void colorFunc_cursor(MenuItem *item) {
    s32 i;
    f32 temp_fv0;
    f32 temp_fv0_2;

    temp_fv0 = func_80045E18(item->unk_64, item->unk_68);
    temp_fv0_2 = (sinf(2 * M_PI * temp_fv0) + 1.0) * 0.5;
    item->unk_64 = temp_fv0;

    for (i = 0; i < ARRAY_COUNTU(item->color.arr); i++) {
        item->color.arr[i] = item->unk_6C[0][i] + (item->unk_6C[1][i] - item->unk_6C[0][i]) * temp_fv0_2;
    }
}
#endif

#if VERSION_US || VERSION_CN
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
    item->unk_0C[0] = xPos;

    item->unk_24[1] = yPos;
    item->unk_1C[1] = yPos;
    item->unk_0C[1] = yPos;

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
#endif

#if VERSION_US || VERSION_CN
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

        item->unk_0C[i] = item->unk_0C[i] * parent->unk_30[i] + parent->unk_0C[i];

        temp_ft0 = item->unk_30[i] * parent->unk_30[i];
        item->unk_30[i] = temp_ft0;
        item->unk_0C[i] = item->unk_0C[i] - (item->unk_00[i] * temp_ft0);
    }
}
#endif

#if VERSION_US || VERSION_CN
/**
 * Original name: menuItem_updateColor
 */
void menuItem_updateColor(MenuItem *item, MenuItem *parent) {
    u32 i;

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
#endif

#if VERSION_US || VERSION_CN
/**
 * menuItem_updateTransScaleColor?
 */
void func_800464BC(MenuItem *item, MenuItem *parent) {
    menuItem_updateTransScale(item, parent);
    menuItem_updateColor(item, parent);
}
#endif

#if VERSION_US || VERSION_CN
void func_800464F8(MenuItem items[], s32 count, MenuItem *parent) {
    s32 i;

    for (i = 0; i < count; i++) {
        func_800464BC(&items[i], parent);
    }
}
#endif

#if VERSION_US || VERSION_CN
void func_8004655C(MenuItem *item, s32 arg1) {
    if (((arg1 < 0) && (item->unk_18 > 0.0f)) || ((arg1 > 0) && (item->unk_18 < 0.0f))) {
        item->unk_18 = -item->unk_18;
    }
}
#endif

#if VERSION_US || VERSION_CN
void func_800465B8(MenuItem *item, s32 arg1) {
    if (((arg1 < 0) && (item->unk_3C > 0.0f)) || ((arg1 > 0) && (item->unk_3C < 0.0f))) {
        item->unk_3C = -item->unk_3C;
    }
}
#endif

#if VERSION_US || VERSION_CN
void func_80046614(MenuItem *item, s32 arg1) {
    if (((arg1 < 0) && (item->unk_68 > 0.0f)) || ((arg1 > 0) && (item->unk_68 < 0.0f))) {
        item->unk_68 = -item->unk_68;
    }
}
#endif

#if VERSION_US || VERSION_CN
void func_80046670(MenuItem *item, f32 arg1, f32 arg2) {
    item->unk_1C[0] = arg1;
    item->unk_1C[1] = arg2;
}
#endif

#if VERSION_US || VERSION_CN
void func_8004667C(MenuItem *item, f32 arg1, f32 arg2) {
    item->unk_24[0] = arg1;
    item->unk_24[1] = arg2;
}
#endif

#if VERSION_US
void func_80046688(MenuItem *item, f32 arg1, f32 arg2) {
    item->unk_40[0] = arg1;
    item->unk_40[1] = arg2;
}
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", func_800490DC_cn);
#endif

#if VERSION_US
void func_80046694(MenuItem *item, f32 arg1, f32 arg2) {
    item->unk_48[0] = arg1;
    item->unk_48[1] = arg2;
}
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", func_800490E8_cn);
#endif

#if VERSION_US || VERSION_CN
void func_800466A0(MenuItem *item, f32 arg1, f32 arg2) {
    item->unk_6C[0][3] = arg2;
    item->unk_6C[0][2] = arg1;
    item->unk_6C[0][1] = arg1;
    item->unk_6C[0][0] = arg1;
}
#endif

#if VERSION_US || VERSION_CN
void func_800466B8(MenuItem *item, f32 arg0, f32 arg1) {
    item->unk_6C[1][3] = arg1;
    item->unk_6C[1][2] = arg0;
    item->unk_6C[1][1] = arg0;
    item->unk_6C[1][0] = arg0;
}
#endif

#if VERSION_US || VERSION_CN
void func_800466D0(MenuItem *item) {
    item->colorCallback = colorFunc_cursor;
    item->unk_68 = 1.0f / 32.0f;
    func_800466A0(item, 0.5f, 1.0f);
    func_800466B8(item, 1.0f, 1.0f);
}
#endif

#if VERSION_US || VERSION_CN
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
#endif

#if VERSION_US || VERSION_CN
void func_800467E0(MenuItem *item) {
    item->colorCallback = colorFunc_curve;
    item->unk_68 = 0.125f;
    func_800466A0(item, 1.0f, 0.0f);
    func_800466B8(item, 1.0f, 1.0f);
}
#endif

#if VERSION_US || VERSION_CN
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
#endif

#if VERSION_US
bool menuItem_outOfScreen(MenuItem *item, s32 arg1, s32 arg2) {
    if (item->color.v.a <= 0) {
        return true;
    }

    if (item->unk_0C[0] >= SCREEN_WIDTH) {
        return true;
    }

    if ((item->unk_0C[1] >= SCREEN_HEIGHT)) {
        return true;
    }

    if (item->unk_0C[0] + arg1 * item->unk_30[0] < 0) {
        return true;
    }

    if (item->unk_0C[1] + arg2 * item->unk_30[1] < 0) {
        return true;
    }

    if (item->unk_30[0] == 0.0f) {
        return true;
    }

    if (item->unk_30[1] == 0.0f) {
        return true;
    }

    return false;
}
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", menuItem_outOfScreen);
#endif

#if VERSION_US || VERSION_CN
bool menuItem_drawTex(MenuItem *item, Gfx **gfxP, TiTexData *arg2, s32 arg3) {
    if (menuItem_outOfScreen(item, arg2->unk_4[0], arg2->unk_4[1])) {
        return false;
    }

    func_80046844(item, gfxP);
    if (arg2->unk_4[3] & 1) {
        tiStretchTexBlock(gfxP, arg2, arg3, item->unk_0C[0], item->unk_0C[1], arg2->unk_4[0] * item->unk_30[0],
                          arg2->unk_4[1] * item->unk_30[1]);
    } else {
        tiStretchTexTile(gfxP, arg2, arg3, 0, 0, arg2->unk_4[0], arg2->unk_4[1], item->unk_0C[0], item->unk_0C[1],
                         arg2->unk_4[0] * item->unk_30[0], arg2->unk_4[1] * item->unk_30[1]);
    }
    return true;
}
#endif

#if VERSION_US
#if 0
s32 func_80046C74(MenuItem *arg0, Gfx **gfxP, s32 arg2, s32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7) {
    f32 sp10;
    f32 sp14;
    f32 sp18;
    f32 sp1C;
    f32 sp20;
    f32 sp24;
    f32 sp28;
    f32 sp2C;
    s32 temp_v0;

    sp20 = arg0->unk_0C[0];
    sp24 = arg0->unk_0C[1];
    sp28 = arg0->unk_30[0];
    sp2C = arg0->unk_30[1];
    sp10 = sp20;
    sp14 = sp24;
    sp18 = sp28;
    sp1C = sp2C;
    arg0->unk_0C[1] += arg5;
    arg0->unk_0C[0] += arg4;
    arg0->unk_30[0] *= arg6;
    arg0->unk_30[1] *= arg7;
    temp_v0 = menuItem_drawTex(arg5, arg0);
    arg0->unk_0C[0] = sp10;
    arg0->unk_0C[1] = sp14;
    arg0->unk_30[0] = sp18;
    arg0->unk_30[1] = sp1C;
    return temp_v0;
}
#else
INCLUDE_ASM("asm/us/nonmatchings/main_segment/main_menu", func_80046C74);
#endif
#endif

#if VERSION_CN
bool func_80046C74(MenuItem *item, Gfx **gfxP, TiTexData *arg2, s32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7) {
    f32 sp28[4] = {
        item->unk_0C[0],
        item->unk_0C[1],
        item->unk_30[0],
        item->unk_30[1],
    };
    bool drawn;

    item->unk_0C[0] += arg4;
    item->unk_0C[1] += arg5;
    item->unk_30[0] *= arg6;
    item->unk_30[1] *= arg7;

    drawn = menuItem_drawTex(item, gfxP, arg2, arg3);

    item->unk_0C[0] = sp28[0];
    item->unk_0C[1] = sp28[1];
    item->unk_30[0] = sp28[2];
    item->unk_30[1] = sp28[3];

    return drawn;
}
#endif

#if VERSION_US
#ifdef NON_MATCHING
bool menuItem_drawAlphaTex(MenuItem *item, Gfx **gfxP, TiTexData *arg2, TiTexData *arg3, s32 arg4) {
    s32 var_s1 = MIN(arg2->unk_4[0], arg3->unk_4[0]);
    s32 var_s2 = MIN(arg2->unk_4[1], arg3->unk_4[1]);

    if (!menuItem_outOfScreen(item, var_s1, var_s2)) {
        TexturePtr sp40;
        TexturePtr sp44;

        func_80046844(item, gfxP);

        if (arg4 != 0) {
            sp40 = NULL;
            sp44 = NULL;
        } else {
            sp40 = arg2->unk_0->tex;
            sp44 = arg3->unk_0->tex;
        }

        if ((arg2->unk_4[3] & 1) && (arg3->unk_4[2] & 1)) {
            StretchAlphaTexBlock(gfxP, var_s1, var_s2, sp40, arg2->unk_4[0], sp44, arg3->unk_4[0], item->unk_0C[0],
                                 item->unk_0C[1], var_s1 * item->unk_30[0], var_s2 * item->unk_30[1]);
            return true;
        } else {
            StretchAlphaTexTile(gfxP, var_s1, var_s2, arg2->unk_0->tex, arg2->unk_4[0], arg3->unk_0->tex,
                                arg3->unk_4[0], 0, 0, var_s1, arg2->unk_4[1], item->unk_0C[0], item->unk_0C[1],
                                var_s1 * item->unk_30[0], var_s2 * item->unk_30[1]);
            return true;
        }
    }

    return false;
}
#else
INCLUDE_ASM("asm/us/nonmatchings/main_segment/main_menu", menuItem_drawAlphaTex);
#endif
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", func_80049754_cn);
#endif

#if VERSION_US || VERSION_CN
bool func_80046F58(MenuItem *item, Gfx **gfxP, TiTexData *arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 temp_lo = arg2->unk_4[1] / arg4;

    if (menuItem_outOfScreen(item, arg2->unk_4[0], temp_lo)) {
        return false;
    }

    func_80046844(item, gfxP);
    tiStretchTexItem(gfxP, arg2, arg3, arg4, arg5, item->unk_0C[0], item->unk_0C[1], arg2->unk_4[0] * item->unk_30[0],
                     temp_lo * item->unk_30[1]);
    return true;
}
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/main_menu", func_80047074);
#endif

#if VERSION_US
bool func_8004714C(MenuItem *item, Gfx **gxfP, TiTexData *arg2, TiTexData *arg3, s32 arg4, s32 arg5, s32 arg6) {
    s32 var_s2 = MIN(arg2->unk_4[0], arg3->unk_4[0]);
    s32 var_s1 = MIN(arg2->unk_4[1], arg3->unk_4[1]) / arg5;

    if (menuItem_outOfScreen(item, var_s2, var_s1)) {
        return false;
    }

    func_80046844(item, gxfP);
    tiStretchAlphaTexItem(gxfP, arg2, arg3, arg4, arg5, arg6, item->unk_0C[0], item->unk_0C[1],
                          var_s2 * item->unk_30[0], var_s1 * item->unk_30[1]);
    return true;
}
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/main_menu", func_800472D0);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", func_80049AB8_cn);
#endif

s32 func_80049B8C_cn(MenuItem *item, Gfx **gfxP, TiTexData *, TiTexData *, s32, s32, s32);
#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", func_80049B8C_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", func_80049D00_cn);
#endif

extern const Gfx fade_normal_texture_init_dl[];

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", fade_normal_texture_init_dl);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", fade_normal_texture_init_dl);
#endif

extern const Gfx fade_alpha_texture_init_dl[];
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", fade_alpha_texture_init_dl);
#endif

extern const Gfx fade_intensity_texture_init_dl[];
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", fade_intensity_texture_init_dl);
#endif

extern const Gfx fade_fillrect_init_dl[];
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", fade_fillrect_init_dl);
#endif

extern const Gfx fade_shadow_texture_init_dl[];
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", fade_shadow_texture_init_dl);
#endif

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", FLT_800ADD00);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", fade_alpha_texture_init_dl);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", fade_intensity_texture_init_dl);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", fade_fillrect_init_dl);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", RO_800C4B60_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", RO_800C4B80_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", _timeAttack_levelTable);
#endif

ASM_RODATA;

extern const u8 _timeAttack_levelTable[];

#if VERSION_US
const u8 _timeAttack_levelTable[] = {
    0x06,
    0x09,
    0x0C,
    0x00,
};
#endif

// clang-format off
const char _mesP1[] =
#if VERSION_US
    "This is the" MSG_NEWLINE
    "one-player mode."
#endif
#if VERSION_CN
    "这是单人游戏模式。"
#endif
    MSG_END;

const char _mes2P[] =
#if VERSION_US
    "This is the" MSG_NEWLINE
    "two-player mode."
#endif
#if VERSION_CN
    "这是双人游戏模式。"
#endif
    MSG_END;

const char _mes4P[] =
#if VERSION_US
    "This is the" MSG_NEWLINE
    "multiplayer mode" MSG_NEWLINE
    "for up to" MSG_NEWLINE
    "four players."
#endif
#if VERSION_CN
    "这是最多四人的多人" MSG_NEWLINE
    "游戏模式。"
#endif
    MSG_END;

const char _mesOpt[] =
#if VERSION_US
    "Various setups" MSG_NEWLINE
    "and options are" MSG_NEWLINE
    "available here."
#endif
#if VERSION_CN
    "这里有各种游戏设定" MSG_NEWLINE
    "和选项。"
#endif
    MSG_END;

const char _mesSt[] =
#if VERSION_US
    "The thrilling tale" MSG_NEWLINE
    "of Dr. Mario and" MSG_NEWLINE
    "the Cold Caper." MSG_W(2) MSG_H
    "Force your foe to" MSG_NEWLINE
    "retire by sending" MSG_NEWLINE
    "them garbage" MSG_W(2) MSG_H
    "or destroy all" MSG_NEWLINE
    "of your own" MSG_NEWLINE
    "viruses to win." MSG_W(2) MSG_H
    "One more thing!" MSG_NEWLINE
    "Press any C Button" MSG_NEWLINE
    "during game play" MSG_NEWLINE
    "to see where the" MSG_W(2) MSG_H
    "capsule will land." MSG_NEWLINE
    "Press the button" MSG_NEWLINE
    "again to turn the" MSG_NEWLINE
    "effect OFF." MSG_W(2) MSG_H
#endif
#if VERSION_CN
    "发生在马力欧医生和" MSG_NEWLINE
    "感冒狂人之间的精彩" MSG_NEWLINE
    "故事。" MSG_W(2) MSG_H
    "通过送给对手垃圾," MSG_NEWLINE
    "逼迫他们退出游戏。" MSG_W(2) MSG_H
    "或消灭自己所有的病" MSG_NEWLINE
    "毒来赢得胜利。 " MSG_W(2) MSG_H
    "再补充一点！" MSG_NEWLINE
    "游戏中可以按任意" MSG_NEWLINE
    "一个Ｃ键来观察药丸" MSG_NEWLINE
    "落下的位置，" MSG_W(2) MSG_H
    "再按一次可以取消这" MSG_NEWLINE
    "个效果。" MSG_W(2) MSG_H
#endif
    MSG_END;

const char _mesLv[] =
#if VERSION_US
    "Continue playing" MSG_NEWLINE
    "until you fail" MSG_NEWLINE
    "to clear a stage." MSG_W(2) MSG_H
    "Destroy all the" MSG_NEWLINE
    "viruses to clear" MSG_NEWLINE
    "a stage." MSG_W(2) MSG_H
    "The higher the" MSG_NEWLINE
    "level, the more" MSG_NEWLINE
    "viruses you have" MSG_NEWLINE
    "to destroy." MSG_W(2)
    MSG_H "One more thing!" MSG_NEWLINE
    "Press any C Button" MSG_NEWLINE
    "during game play" MSG_NEWLINE
    "to see where the" MSG_W(2) MSG_H
    "capsule will land." MSG_NEWLINE
    "Press the button" MSG_NEWLINE
    "again to turn the" MSG_NEWLINE
    "effect OFF." MSG_W(2) MSG_H
#endif
#if VERSION_CN
    "持续游戏直到在一局" MSG_NEWLINE
    "中失败。" MSG_W(2) MSG_H
    "消灭所有病毒才能过" MSG_NEWLINE
    "关。" MSG_W(2) MSG_H
    "游戏难度等级越高," MSG_NEWLINE
    "需要消灭的病毒就越" MSG_NEWLINE
    "多。" MSG_W(2) MSG_H
    "再补充一点！" MSG_NEWLINE
    "游戏中可以按任意" MSG_NEWLINE
    "一个Ｃ键来观察药丸" MSG_NEWLINE
    "落下的位置，" MSG_W(2) MSG_H
    "再按一次可以取消这" MSG_NEWLINE
    "个效果。" MSG_W(2) MSG_H
#endif
    MSG_END;

const char _mesVsCom[] =
#if VERSION_US
    "This is your" MSG_NEWLINE
    "chance to play" MSG_NEWLINE
    "against the" MSG_NEWLINE
    "computer." MSG_W(2) MSG_H
    "Play against" MSG_NEWLINE
    "any character" MSG_NEWLINE
    "you'd like." MSG_W(2) MSG_H
    "Force your foe to" MSG_NEWLINE
    "retire by sending" MSG_NEWLINE
    "them garbage" MSG_W(2) MSG_H
    "or destroy all" MSG_NEWLINE
    "of your own" MSG_NEWLINE
    "viruses to win." MSG_W(2) MSG_H
    "One more thing!" MSG_NEWLINE
    "Press any C Button" MSG_NEWLINE
    "during game play" MSG_NEWLINE
    "to see where the" MSG_W(2) MSG_H
    "capsule will land." MSG_NEWLINE
    "Press the button" MSG_NEWLINE
    "again to turn the" MSG_NEWLINE
    "effect OFF." MSG_W(2) MSG_H
#endif
#if VERSION_CN
    "这是你和电脑对抗的" MSG_NEWLINE
    "机会。" MSG_W(2) MSG_H
    "选定任意一个你喜欢" MSG_NEWLINE
    "的对手开始游戏。" MSG_W(2) MSG_H
    "通过送给对手垃圾, " MSG_NEWLINE
    "逼迫他们退出游戏。" MSG_W(2) MSG_H
    "或消灭自己所有的" MSG_NEWLINE
    "病毒来赢得胜利。 " MSG_W(2) MSG_H
    "再补充一点！" MSG_NEWLINE
    "游戏中可以按任意" MSG_NEWLINE
    "一个Ｃ键来观察药丸" MSG_NEWLINE
    "落下的位置，" MSG_W(2) MSG_H
    "再按一次可以取消这" MSG_NEWLINE
    "个效果。" MSG_W(2) MSG_H
#endif
    MSG_END;

const char _mesVcFlash[] =
#if VERSION_US
    "Clear levels by" MSG_NEWLINE
    "destroying the" MSG_NEWLINE
    "flashing viruses." MSG_W(2) MSG_H
    "Play against" MSG_NEWLINE
    "any character" MSG_NEWLINE
    "you'd like." MSG_W(2) MSG_H
    "Force your foe to" MSG_NEWLINE
    "retire by sending" MSG_NEWLINE
    "them garbage" MSG_W(2) MSG_H
    "or destroy all" MSG_NEWLINE
    "of your own" MSG_NEWLINE
    "viruses to win." MSG_W(2) MSG_H
    "One more thing!" MSG_NEWLINE
    "Press any C Button" MSG_NEWLINE
    "during game play" MSG_NEWLINE
    "to see where the" MSG_W(2) MSG_H
    "capsule will land." MSG_NEWLINE
    "Press the button" MSG_NEWLINE
    "again to turn the" MSG_NEWLINE
    "effect OFF." MSG_W(2) MSG_H
#endif
#if VERSION_CN
    "消灭所有的闪光病毒" MSG_NEWLINE
    "以取胜。" MSG_W(2) MSG_H
    "选定任意一个你喜欢" MSG_NEWLINE
    "的对手开始游戏。" MSG_W(2) MSG_H
    "通过送给对手垃圾, " MSG_NEWLINE
    "逼迫他们退出游戏" MSG_W(2) MSG_H
    "或消灭自己所有的病" MSG_NEWLINE
    "毒来赢得胜利。 " MSG_W(2) MSG_H
    "再补充一点！" MSG_NEWLINE
    "游戏中可以按任意" MSG_NEWLINE
    "一个Ｃ键来观察药丸" MSG_NEWLINE
    "落下的位置，" MSG_W(2) MSG_H
    "再按一次可以取消这" MSG_NEWLINE
    "个效果。" MSG_W(2) MSG_H
#endif
    MSG_END;

const char _mesLvTaiQ[] =
#if VERSION_US
    "Viruses multiply" MSG_NEWLINE
    "rapidly in this" MSG_NEWLINE
    "mode." MSG_W(2) MSG_H
    "Completing combos" MSG_NEWLINE
    "will slow down" MSG_NEWLINE
    "the speed of the" MSG_NEWLINE
    "virus growth." MSG_W(2) MSG_H
    "Destroy the" MSG_NEWLINE
    "viruses to keep" MSG_NEWLINE
    "the bottle clear." MSG_W(2) MSG_H
    "Press the L Button" MSG_NEWLINE
    "to speed up the" MSG_NEWLINE
    "multiplication" MSG_NEWLINE
    "of the viruses." MSG_W(2) MSG_H
    "One more thing!" MSG_NEWLINE
    "Press any C Button" MSG_NEWLINE
    "during game play" MSG_NEWLINE
    "to see where the" MSG_W(2) MSG_H
    "capsule will land." MSG_NEWLINE
    "Press the button" MSG_NEWLINE
    "again to turn the" MSG_NEWLINE
    "effect OFF." MSG_W(2) MSG_H
#endif
#if VERSION_CN
    "在这个模式中病毒会" MSG_NEWLINE
    "高速繁殖。" MSG_W(2) MSG_H
    "连消病毒可以降低" MSG_NEWLINE
    "它们的繁殖速度。" MSG_W(2) MSG_H
    "消灭病毒以保持瓶子" MSG_NEWLINE
    "清洁。" MSG_W(2) MSG_H
    "按L键可以加快病毒" MSG_NEWLINE
    "的繁殖。" MSG_W(2) MSG_H
    "再补充一点！" MSG_NEWLINE
    "游戏中可以按任意" MSG_NEWLINE
    "一个Ｃ键来观察药丸" MSG_NEWLINE
    "落下的位置，" MSG_W(2) MSG_H
    "再按一次可以取消这" MSG_NEWLINE
    "个效果。" MSG_W(2) MSG_H
#endif
    MSG_END;

const char _mesLvTimeAt[] =
#if VERSION_US
    "Try to get the" MSG_NEWLINE
    "highest score" MSG_NEWLINE
    "possible in a set" MSG_NEWLINE
    "amount of time." MSG_W(2) MSG_H
    "Aim for a high" MSG_NEWLINE
    "score by" MSG_NEWLINE
    "destroying many" MSG_NEWLINE
    "viruses at once." MSG_W(2) MSG_H
    "One more thing!" MSG_NEWLINE
    "Press any C Button" MSG_NEWLINE
    "during game play" MSG_NEWLINE
    "to see where the" MSG_W(2) MSG_H
    "capsule will land." MSG_NEWLINE
    "Press the button" MSG_NEWLINE
    "again to turn the" MSG_NEWLINE
    "effect OFF." MSG_W(2) MSG_H
#endif
#if VERSION_CN
    "尽力在限定时间内争" MSG_NEWLINE
    "取最高分。" MSG_W(2) MSG_H
    "同时消灭很多病毒可" MSG_NEWLINE
    "争取最高分。" MSG_W(2) MSG_H
    "再补充一点！" MSG_NEWLINE
    "游戏中可以按任意" MSG_NEWLINE
    "一个Ｃ键来观察药丸" MSG_NEWLINE
    "落下的位置，" MSG_W(2) MSG_H
    "再按一次可以取消这" MSG_NEWLINE
    "个效果。" MSG_W(2) MSG_H
#endif
    MSG_END;

const char _mesNs1[] =
#if VERSION_US
    "Please input" MSG_NEWLINE
    "your name." MSG_W(2) MSG_H
    "Please select NEW" MSG_NEWLINE
    "or GUEST if this" MSG_NEWLINE
    "is your first" MSG_NEWLINE
    "time playing." MSG_W(2) MSG_H
#endif
#if VERSION_CN
    "请输入你的名字。" MSG_W(2) MSG_H
    "如果是第一次游戏，" MSG_NEWLINE
    "请选择：" MSG_NEWLINE
    "新游戏或玩家。" MSG_W(2) MSG_H
#endif
    MSG_END;

const char _mesNs2[] =
#if VERSION_US
    "Please input" MSG_NEWLINE
    "your name."
#endif
#if VERSION_CN
    "请输入你的名字。"
#endif
    MSG_END;

const char _mesVsMan[] =
#if VERSION_US
    "Compete against" MSG_NEWLINE
    "another player." MSG_W(2) MSG_H
    "Force your foe to" MSG_NEWLINE
    "retire by sending" MSG_NEWLINE
    "them garbage" MSG_W(2) MSG_H
    "or destroy all" MSG_NEWLINE
    "of your own" MSG_NEWLINE
    "viruses to win." MSG_W(2) MSG_H
    "One more thing!" MSG_NEWLINE
    "Press any C Button" MSG_NEWLINE
    "during game play" MSG_NEWLINE
    "to see where the" MSG_W(2) MSG_H
    "capsule will land." MSG_NEWLINE
    "Press the button" MSG_NEWLINE
    "again to turn the" MSG_NEWLINE
    "effect OFF." MSG_W(2) MSG_H
#endif
#if VERSION_CN
    "和另外一个玩家比赛。" MSG_W(2) MSG_H
    "通过送给对手垃圾," MSG_NEWLINE
    "逼迫他们退出游戏" MSG_W(2) MSG_H
    "或消灭自己所有的病" MSG_NEWLINE
    "毒来赢得胜利。 " MSG_W(2) MSG_H
    "再补充一点！" MSG_NEWLINE
    "游戏中可以按任意" MSG_NEWLINE
    "一个Ｃ键来观察药丸" MSG_NEWLINE
    "落下的位置，" MSG_W(2) MSG_H
    "再按一次可以取消这" MSG_NEWLINE
    "个效果。" MSG_W(2) MSG_H
#endif
    MSG_END;

const char _mesVmFlash[] =
#if VERSION_US
    "Clear levels" MSG_NEWLINE
    "by destroying the" MSG_NEWLINE
    "flashing viruses." MSG_W(2) MSG_H
    "Clear combos to" MSG_NEWLINE
    "send garbage to" MSG_NEWLINE
    "your opponent." MSG_W(2) MSG_H
    "One more thing!" MSG_NEWLINE
    "Press any C Button" MSG_NEWLINE
    "during game play" MSG_NEWLINE
    "to see where the" MSG_W(2) MSG_H
    "capsule will land." MSG_NEWLINE
    "Press the button" MSG_NEWLINE
    "again to turn the" MSG_NEWLINE
    "effect OFF." MSG_W(2) MSG_H
#endif
#if VERSION_CN
    "消灭所有的闪光病毒" MSG_NEWLINE
    "以取胜。" MSG_W(2) MSG_H
    "完成连消能送给对手垃圾。" MSG_W(2) MSG_H
    "再补充一点！" MSG_NEWLINE
    "游戏中可以按任意" MSG_NEWLINE
    "一个Ｃ键来观察药丸" MSG_NEWLINE
    "落下的位置，" MSG_W(2) MSG_H
    "再按一次可以取消这" MSG_NEWLINE
    "个效果。" MSG_W(2) MSG_H
#endif
    MSG_END;

const char _mesVmTimeAt[] =
#if VERSION_US
    "Try to get the" MSG_NEWLINE
    "highest score" MSG_NEWLINE
    "possible in a set" MSG_NEWLINE
    "amount of time." MSG_W(2) MSG_H
    "Aim for a high" MSG_NEWLINE
    "score by" MSG_NEWLINE
    "destroying many" MSG_NEWLINE
    "viruses at once." MSG_W(2) MSG_H
    "One more thing!" MSG_NEWLINE
    "Press any C Button" MSG_NEWLINE
    "during game play" MSG_NEWLINE
    "to see where the" MSG_W(2) MSG_H
    "capsule will land." MSG_NEWLINE
    "Press the button" MSG_NEWLINE
    "again to turn the" MSG_NEWLINE
    "effect OFF." MSG_W(2) MSG_H
#endif
#if VERSION_CN
    "尽力在限定时间内取" MSG_NEWLINE
    "得最高分。" MSG_W(2) MSG_H
    "一次消灭多个病毒可" MSG_NEWLINE
    "得高分。" MSG_W(2) MSG_H
    "再补充一点！" MSG_NEWLINE
    "游戏中可以按任意" MSG_NEWLINE
    "一个Ｃ键来观察药丸" MSG_NEWLINE
    "落下的位置，" MSG_W(2) MSG_H
    "再按一次可以取消这" MSG_NEWLINE
    "个效果。" MSG_W(2) MSG_H
#endif
    MSG_END;

const char _mesVsNum[] =
#if VERSION_US
    "How many players?"
#endif
#if VERSION_CN
    "有多少玩家？"
#endif
    MSG_END;

const char _mesVs4P[] =
#if VERSION_US
    "A four-player" MSG_NEWLINE
    "free-for-all." MSG_W(2) MSG_H
    "Force your foes to" MSG_NEWLINE
    "retire by sending" MSG_NEWLINE
    "them garbage" MSG_W(2) MSG_H
    "or destroy all" MSG_NEWLINE
    "of your own" MSG_NEWLINE
    "viruses to win." MSG_W(2) MSG_H
    "The color of the" MSG_NEWLINE
    "combos you clear" MSG_NEWLINE
    "determines where" MSG_NEWLINE
    "your garbage goes." MSG_W(2) MSG_H
    "One more thing!" MSG_NEWLINE
    "Press any C Button" MSG_NEWLINE
    "during game play" MSG_NEWLINE
    "to see where the" MSG_W(2) MSG_H
    "capsule will land." MSG_NEWLINE
    "Press the button" MSG_NEWLINE
    "again to turn the" MSG_NEWLINE
    "effect OFF." MSG_W(2) MSG_H
#endif
#if VERSION_CN
    "四人自由比赛。" MSG_W(2) MSG_H
    "通过送给对手垃圾," MSG_NEWLINE
    "逼迫他们退出游戏" MSG_W(2) MSG_H
    "或消灭自己所有的病" MSG_NEWLINE
    "毒来赢得胜利。 " MSG_W(2) MSG_H
    "连消的颜色决定你的" MSG_NEWLINE
    "垃圾药丸送到哪里去。" MSG_W(2) MSG_H
    "再补充一点！" MSG_NEWLINE
    "游戏中可以按任意" MSG_NEWLINE
    "一个Ｃ键来观察药丸" MSG_NEWLINE
    "落下的位置，" MSG_W(2) MSG_H
    "再按一次可以取消这" MSG_NEWLINE
    "个效果。" MSG_W(2) MSG_H
#endif
    MSG_END;

const char _mes4PTag[] =
#if VERSION_US
    "A two-on-two" MSG_NEWLINE
    "battle mode." MSG_W(2) MSG_H
    "Force your foes to" MSG_NEWLINE
    "retire by sending" MSG_NEWLINE
    "them garbage" MSG_W(2) MSG_H
    "or destroy all" MSG_NEWLINE
    "of your own" MSG_NEWLINE
    "viruses to win." MSG_W(2) MSG_H
    "The color of the" MSG_NEWLINE
    "combos you clear" MSG_NEWLINE
    "determines where" MSG_NEWLINE
    "your garbage goes." MSG_W(2) MSG_H
    "Garbage sent to" MSG_NEWLINE
    "your partner is" MSG_NEWLINE
    "placed in your" MSG_W(2) MSG_H
    "team bank. This" MSG_NEWLINE
    "is then added" MSG_NEWLINE
    "to later garbage" MSG_W(2) MSG_H
    "that either you or" MSG_NEWLINE
    "your teammate sends" MSG_NEWLINE
    "to your foes." MSG_W(2) MSG_H
    "One more thing!" MSG_NEWLINE
    "Press any C Button" MSG_NEWLINE
    "during game play" MSG_NEWLINE
    "to see where the" MSG_W(2) MSG_H
    "capsule will land." MSG_NEWLINE
    "Press the button" MSG_NEWLINE
    "again to turn the" MSG_NEWLINE
    "effect OFF." MSG_W(2) MSG_H
#endif
#if VERSION_CN
    "二对二模式。" MSG_W(2) MSG_H
    "通过送给对手垃圾, " MSG_NEWLINE
    "逼迫他们退出游戏，" MSG_W(2) MSG_H
    "或消灭自己所有的病" MSG_NEWLINE
    "毒来赢得胜利。 " MSG_W(2) MSG_H
    "连消的颜色决定你的" MSG_NEWLINE
    "垃圾药丸送到哪里去。" MSG_W(2) MSG_H
    "送给同伴的垃圾药丸" MSG_NEWLINE
    "放置在你们" MSG_W(2) MSG_H
    "小型垃圾箱中，然后" MSG_NEWLINE
    "又加入到" MSG_W(2) MSG_H
    "你或你的同伴随后送" MSG_NEWLINE
    "给对手的垃圾中去。" MSG_W(2) MSG_H
    "再补充一点！" MSG_NEWLINE
    "游戏中可以按任意" MSG_NEWLINE
    "一个Ｃ键来观察药丸" MSG_NEWLINE
    "落下的位置，" MSG_W(2) MSG_H
    "再按一次可以取消这" MSG_NEWLINE
    "个效果。" MSG_W(2) MSG_H
#endif
    MSG_END;

const char _mes4PFlash[] =
#if VERSION_US
    "Clear levels" MSG_NEWLINE
    "by destroying the" MSG_NEWLINE
    "flashing viruses." MSG_W(2) MSG_H
    "You can fill your" MSG_NEWLINE
    "rivals' screens" MSG_NEWLINE
    "with garbage." MSG_W(2) MSG_H
    "The color of the" MSG_NEWLINE
    "combos you clear" MSG_NEWLINE
    "determines where" MSG_NEWLINE
    "your garbage goes." MSG_W(2) MSG_H
    "One more thing!" MSG_NEWLINE
    "Press any C Button" MSG_NEWLINE
    "during game play" MSG_NEWLINE
    "to see where the" MSG_W(2) MSG_H
    "capsule will land." MSG_NEWLINE
    "Press the button" MSG_NEWLINE
    "again to turn the" MSG_NEWLINE
    "effect OFF." MSG_W(2) MSG_H
#endif
#if VERSION_CN
    "消灭所有的闪光病毒" MSG_NEWLINE
    "以取胜。" MSG_W(2) MSG_H
    "你可以将对手的屏幕" MSG_NEWLINE
    "塞满垃圾。" MSG_W(2) MSG_H
    "连消的颜色决定你的" MSG_NEWLINE
    "垃圾药丸送到哪里去。" MSG_W(2) MSG_H
    "再补充一点！" MSG_NEWLINE
    "游戏中可以按任意" MSG_NEWLINE
    "一个Ｃ键来观察药丸" MSG_NEWLINE
    "落下的位置，" MSG_W(2) MSG_H
    "再按一次可以取消这" MSG_NEWLINE
    "个效果。" MSG_W(2) MSG_H
#endif
    MSG_END;

const char _mesRec[] =
#if VERSION_US
    "This is where" MSG_NEWLINE
    "you view" MSG_NEWLINE
    "game records."
#endif
#if VERSION_CN
    "在这里可以看游戏纪" MSG_NEWLINE
    "录。"
#endif
    MSG_END;

const char _mesTutol[] =
#if VERSION_US
    "This is where" MSG_NEWLINE
    "you study rules" MSG_NEWLINE
    "and techniques."
#endif
#if VERSION_CN
    "在这里可以学习游戏" MSG_NEWLINE
    "规则和技巧。"
#endif
    MSG_END;

const char _mesName[] =
#if VERSION_US
    "This is where" MSG_NEWLINE
    "you change or" MSG_NEWLINE
    "delete your name."
#endif
#if VERSION_CN
    "在这里可以更改或删" MSG_NEWLINE
    "除你的名字。"
#endif
    MSG_END;

const char _mesVsCnt[] =
#if VERSION_US
    "This is where you" MSG_NEWLINE
    "set the number of" MSG_NEWLINE
    "games in a match."
#endif
#if VERSION_CN
    "在这里可以设置一盘" MSG_NEWLINE
    "比赛的局数。"
#endif
    MSG_END;

const char _mesSnd[] =
#if VERSION_US
    "This is where you" MSG_NEWLINE
    "select the" MSG_NEWLINE
    "sound settings." MSG_W(2) MSG_H
    "You can also" MSG_NEWLINE
    "listen to game" MSG_NEWLINE
    "music and sounds." MSG_W(2) MSG_H
#endif
#if VERSION_CN
    "在这里可以进行声音" MSG_NEWLINE
    "设置。" MSG_W(2) MSG_H
    "你也可以欣赏游戏音" MSG_NEWLINE
    "乐和音效。" MSG_W(2) MSG_H
#endif
    MSG_END;

const char _mesBak[] =
#if VERSION_US
    "This is where" MSG_NEWLINE
    "you can delete" MSG_NEWLINE
    "all saved data."
#endif
#if VERSION_CN
    "在这里可以删除所有" MSG_NEWLINE
    "存档。"
#endif
    MSG_END;

const char _mesMisc[] =
#if VERSION_US
    "This is where you" MSG_NEWLINE
    "can set up other" MSG_NEWLINE
    "game items."
#endif
#if VERSION_CN
    "在这里可以设置其他" MSG_NEWLINE
    "游戏项目。"
#endif
    MSG_END;

const char _mesRecMs1[] =
#if VERSION_US
    "Which records do" MSG_NEWLINE
    "you want to view?"
#endif
#if VERSION_CN
    "你想看哪一条纪录？"
#endif
    MSG_END;

const char _mesRecMs2[] =
#if VERSION_US
    "Which mode" MSG_NEWLINE
    "records do you" MSG_NEWLINE
    "want to view?"
#endif
#if VERSION_CN
    "你想看哪个模式的" MSG_NEWLINE
    "纪录？"
#endif
    MSG_END;

const char _mesRule1[] =
#if VERSION_US
    "These are the" MSG_NEWLINE
    "button control" MSG_NEWLINE
    "explanations."
#endif
#if VERSION_CN
    "这些是控制键的" MSG_NEWLINE
    "讲解。"
#endif
    MSG_END;

const char _mesRule2[] =
#if VERSION_US
    "This is an" MSG_NEWLINE
    "explanation of" MSG_NEWLINE
    "basic game play."
#endif
#if VERSION_CN
    "这是游戏的基本" MSG_NEWLINE
    "讲解。"
#endif
    MSG_END;

const char _mesRule3[] =
#if VERSION_US
    "These are" MSG_NEWLINE
    "explanations of" MSG_NEWLINE
    "the two-player" MSG_NEWLINE
    "games."
#endif
#if VERSION_CN
    "这些是双人游戏的" MSG_NEWLINE
    "讲解。"
#endif
    MSG_END;

const char _mesRule4[] =
#if VERSION_US
    "These are" MSG_NEWLINE
    "explanations of" MSG_NEWLINE
    "the four-player" MSG_NEWLINE
    "games."
#endif
#if VERSION_CN
    "这些是四人游戏的" MSG_NEWLINE
    "讲解。"
#endif
    MSG_END;

const char _mesKotu[] =
#if VERSION_US
    "Let me give" MSG_NEWLINE
    "you some advice."
#endif
#if VERSION_CN
    "让我来给你一些" MSG_NEWLINE
    "提示。"
#endif
    MSG_END;

const char _mesNameSel[] =
#if VERSION_US
    "What are you" MSG_NEWLINE
    "going to do to" MSG_NEWLINE
    "that file name?"
#endif
#if VERSION_CN
    "你想对那个名字进行" MSG_NEWLINE
    "什么操作？"
#endif
    MSG_END;

const char _mesNameErase[] =
#if VERSION_US
    "Delete that file" MSG_NEWLINE
    "name, and you" MSG_NEWLINE
    "delete the game" MSG_NEWLINE
    "data, too." MSG_W(2) MSG_H
    "Do you really" MSG_NEWLINE
    "want to delete" MSG_NEWLINE
    "that file name?" MSG_W(2) MSG_H
#endif
#if VERSION_CN
    "如果你删除那个名字，" MSG_NEWLINE
    "那么就把相关的游戏" MSG_NEWLINE
    "数据也一同删掉了。" MSG_W(2) MSG_H
    "你真的想删除这个" MSG_NEWLINE
    "名字?" MSG_W(2) MSG_H
#endif
    MSG_END;

const char _mesNameErase2[] =
#if VERSION_US
    "The file name" MSG_NEWLINE
    "and game data" MSG_NEWLINE
    "have been deleted."
#endif
#if VERSION_CN
    "名字和游戏数据删除" MSG_NEWLINE
    "完毕。"
#endif
    MSG_END;

const char _mesVsCnt2[] =
#if VERSION_US
    "Select the number" MSG_NEWLINE
    "of games to play" MSG_NEWLINE
    "in a match."
#endif
#if VERSION_CN
    "选择一盘比赛中的" MSG_NEWLINE
    "局数。 "
#endif
    MSG_END;

const char _mesSound[] =
#if VERSION_US
    "Select with the" MSG_NEWLINE
    "+ Control Pad" MSG_NEWLINE
    "and confirm with" MSG_NEWLINE
    "the A Button."
#endif
#if VERSION_CN
    "用十字键选择，" MSG_NEWLINE
    "A键确定。"
#endif
    MSG_END;

const char _mesStereo[] =
#if VERSION_US
    "The music will" MSG_NEWLINE
    "play in stereo."
#endif
#if VERSION_CN
    "音乐以立体声播放。"
#endif
    MSG_END;

const char _mesMono[] =
#if VERSION_US
    "The music will" MSG_NEWLINE
    "play in mono."
#endif
#if VERSION_CN
    "音乐以单声道播放。"
#endif
    MSG_END;

const char _mesDoErase[] =
#if VERSION_US
    "Delete all saved" MSG_NEWLINE
    "game data at once." MSG_W(2) MSG_H
    "Do you really" MSG_NEWLINE
    "want to delete" MSG_NEWLINE
    "all of the" MSG_NEWLINE
    "saved game data?" MSG_W(2) MSG_H
#endif
#if VERSION_CN
    "删除所有的游戏数据。" MSG_W(2) MSG_H
    "你真的想删除所有的" MSG_NEWLINE
    "游戏数据吗？" MSG_W(2) MSG_H
#endif
    MSG_END;

const char _mesDoErase1[] =
#if VERSION_US
    "All of the" MSG_NEWLINE
    "saved game data" MSG_NEWLINE
    "has been deleted."
#endif
#if VERSION_CN
    "所有存储的游戏数据" MSG_NEWLINE
    "删除完毕。"
#endif
    MSG_END;

const char _mesNoCont2[] =
#if VERSION_US
    "Please power off and insert" MSG_NEWLINE
    "more controllers."
#endif
#if VERSION_CN
    "请关闭电源，插入更" MSG_NEWLINE
    "多共游机。"
#endif
    MSG_END;

const char _mesNoCont3[] =
#if VERSION_US
    "Please power off and insert" MSG_NEWLINE
    "more controllers."
#endif
#if VERSION_CN
    "请关闭电源，插入更" MSG_NEWLINE
    "多共游机。"
#endif
    MSG_END;

const char _mesNoCont4[] =
#if VERSION_US
    "Please power off and insert" MSG_NEWLINE
    "more controllers."
#endif
#if VERSION_CN
    "请关闭电源，插入更" MSG_NEWLINE
    "多共游机。"
#endif
    MSG_END;

const char _mesScore[] =
#if VERSION_US
    "You can turn the" MSG_NEWLINE
    "on-screen score" MSG_NEWLINE
    "display ON or OFF."
#endif
#if VERSION_CN
    "你可以打开或关闭屏" MSG_NEWLINE
    "幕上的得分显示。"
#endif
    MSG_END;

const char _mesScoreOnOff[] =
#if VERSION_US
    "Please choose a" MSG_NEWLINE
    "score display" MSG_NEWLINE
    "option."
#endif
#if VERSION_CN
    "请选择得分显示模式。"
#endif
    MSG_END;

const char STR_800AF4C4[] =
#if VERSION_US
    "Now saving." MSG_NEWLINE
    "Do not turn power off."
#endif
#if VERSION_CN
    "存储中" MSG_NEWLINE
    "请勿关闭电源."
#endif
    MSG_END;

const char STR_800AF4EC[] =
#if VERSION_US
    "Now deleting." MSG_NEWLINE
    "Do not turn power off."
#endif
#if VERSION_CN
    "删除中" MSG_NEWLINE
    "请勿关闭电源."
#endif
    MSG_END;
// clang-format on

extern const u8 _gameLvItemColor[][2][4];
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", _gameLvItemColor);
#endif

extern u8 _musicItemColor[][4];
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", _musicItemColor);
#endif

extern const u8 RO_800AF530[];
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", RO_800AF530);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", _gameLvItemColor);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", _musicItemColor);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", RO_800AF530);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/main_menu", func_80047420);
#endif

#if VERSION_CN
void func_80047420(struct_watchMenu_unk_02548 *arg0, MainMenuMode arg1) {
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
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/main_menu", func_800474EC);
#endif

#if VERSION_CN
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
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/main_menu", func_80047584);
#endif

#if VERSION_CN
void func_80047584(struct_watchMenu_unk_02548 *arg0, MenuItem *item) {
    func_800464F8(arg0->unk_10, 2, item);
}
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/main_menu", menuTitle_draw);
#endif

#if VERSION_CN
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
#endif

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", _menuCursor_cursor_4_pattern);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", RO_800C5CF8_cn);
#endif

#if VERSION_US || VERSION_CN
void func_80047720(MenuCursor *cursor, s32 arg1, s32 arg2) {
    MenuItem *item = &cursor->unk_140;

    item->transCallback = transFunc_finger;
    item->unk_18 = 1.0f / 32.0f;
    func_8004667C(item, arg1, arg2);
    func_80046670(item, arg1 - 8, arg2);
}
#endif

#if VERSION_US || VERSION_CN
void func_800477BC(MenuCursor *cursor, s32 arg1, s32 arg2) {
    func_8004667C(&cursor->unk_1D0, arg1, arg2);
    func_80046670(&cursor->unk_1D0, arg1, arg2);
}
#endif

#if VERSION_US
extern const f32 _color_1040[4][3];
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", _color_1040);
#endif

#if VERSION_CN
const f32 _color_1040[][3] = {
    { 1.0f, 0.3f, 0.3f },
    { 0.3f, 0.3f, 1.0f },
    { 1.0f, 1.0f, 0.0f },
    { 0.0f, 1.0f, 0.0f },
};
#endif

#if VERSION_US || VERSION_CN
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
#else
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", menuCursor_init2);
#endif

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", _pnts_1106);
#endif

#if VERSION_US || VERSION_CN
void func_800479A8(MenuCursor *cursor, struct_watchMenu *watchMenuRef, u32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6,
                   s32 arg7) {
    menuCursor_init2(cursor, watchMenuRef, arg2, 4, 0, arg3, arg4, arg5, arg6, arg7);
}
#endif

#if VERSION_US || VERSION_CN
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
#endif

#if VERSION_US
typedef struct struct__pnts_1106 {
    /* 0x00 */ UNK_TYPE4 unk_00;
    /* 0x04 */ UNK_TYPE4 unk_04;
    /* 0x08 */ UNK_TYPE4 unk_08;
    /* 0x0C */ UNK_TYPE4 unk_0C;
    /* 0x10 */ UNK_TYPE4 unk_10;
    /* 0x14 */ UNK_TYPE4 unk_14;
    /* 0x18 */ UNK_TYPE4 unk_18;
    /* 0x1C */ UNK_TYPE4 unk_1C;
} struct__pnts_1106; // size = 0x20

extern const struct__pnts_1106 _pnts_1106[];
extern const s32 _menuCursor_cursor_4_pattern[];

#if 0
// there's an unknown struct array in the stack
void menuCursor_draw1(MenuCursor **cursorArr, s32 count, Gfx **gxfP) {
    s32 sp10;
    s32 sp14;
    s32 sp18;
    s32 sp1C;
    s32 sp20;
    s32 sp24;
    s32 sp28;
    s32 sp2C;
    s32 sp30;
    s32 sp34;
    s32 sp38;
    s32 sp40;
    s32 sp44;
    s32 sp48;
    s32 sp50;
    s32 sp54;
    s32 sp58;
    Gfx *sp60;
    MenuCursor **sp6C;
    s32 sp74;
    Gfx **sp7C;
    s32 sp84;
    MenuCursor **spB4;
    Gfx *temp_a0;
    Gfx *temp_a0_3;
    Gfx *temp_a1_3;
    Gfx *temp_a3;
    Gfx *temp_a3_2;
    Gfx *temp_t0;
    Gfx *temp_t0_2;
    Gfx *temp_v0;
    Gfx *temp_v1;
    Gfx *temp_v1_7;
    MenuCursor **var_t4;
    MenuCursor *temp_s1;
    MenuItem *temp_s2;
    TiTexData *var_s6;
    f32 temp_fv1;
    f32 temp_fv1_2;
    s16 temp_a0_8;
    s16 temp_t3;
    s16 temp_v0_5;
    s16 temp_v1_5;
    s32 *temp_v0_2;
    s32 *temp_v0_3;
    s32 *temp_v0_4;
    s32 *temp_v1_4;
    s32 temp_a0_4;
    s32 temp_a0_5;
    s32 temp_a0_6;
    s32 temp_a0_7;
    s32 temp_a0_9;
    s32 temp_a1_2;
    s32 temp_a1_4;
    s32 temp_a2;
    s32 temp_a2_2;
    s32 temp_ft0;
    s32 temp_fv1_3;
    s32 temp_v0_6;
    s32 temp_v0_7;
    s32 temp_v0_9;
    s32 temp_v1_6;
    s32 var_a1;
    s32 var_a2;
    s32 var_fp;
    s32 var_s0;
    s32 var_s0_2;
    s32 var_s5;
    s32 var_s7;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v0_3;
    s32 var_v0_4;
    s32 var_v1;
    s32 var_v1_2;
    s32 var_v1_3;
    s32 var_v1_4;
    const struct__pnts_1106 *temp_t1;
    u16 *temp_a1;
    u16 *temp_v0_8;
    u16 *temp_v1_3;
    u16 temp_v1_2;
    u32 temp_a0_2;
    u32 var_a0;
    u32 var_s4;

    var_s0 = saved_reg_s0;
    var_s5 = saved_reg_s5;
    var_s6 = saved_reg_s6;
    sp74 = count;
    sp6C = cursorArr;
    sp7C = gxfP;
    var_s4 = 0;
    temp_v1 = *sp7C;
    sp60 = temp_v1 + 8;
#if 0
    temp_v1->words.w0 = 0xDE000000;
    temp_v1->words.w1 = (u32) fade_normal_texture_init_dl;
    sp60 = temp_v1 + 0x10;
    temp_v1->unk_8 = 0xE200001C;
    temp_v1->unk_C = 0x504240;
    sp60 = temp_v1 + 0x18;
    temp_v1->unk_10 = 0xE3001001;
    temp_v1->unk_14 = 0;
#endif
    var_v0 = 0U < 9U;
    do {
        if (var_v0 != 0) {
            switch (var_s4) {
                case 0x0:
                    var_s0 = 8;
                    var_s5 = 4;
                    break;
                case 0x1:
                    var_s0 = 6;
                    var_s5 = 3;
                    break;
                case 0x2:
                    var_s0 = 7;
                    var_s5 = 0x10;
                    break;
                case 0x3:
                    var_s5 = 0x10;
                    sp84 = -1;
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
        }
        var_s7 = 0;
        var_fp = 0;
        if (sp74 > 0) {
            spB4 = sp6C;
            do {
                temp_s1 = *spB4;
                temp_s2 = &temp_s1->unk_0B0;
                if ((s32) temp_s1->unk_01C.w < 0) {
                    var_t4 = spB4 + 4;
                    if (var_s4 == temp_s1->unk_004) {
                        if (menuItem_outOfScreen(temp_s2, temp_s1->unk_014, temp_s1->unk_018) == false) {
                            if (var_s4 == 3) {
                                if (!(temp_s1->unk_01C.w & 0x10000000)) {
                                    var_s0 = 3;
                                } else {
                                    var_s0 = _menuCursor_cursor_4_pattern[(s32) (temp_s1->unk_0B0.unk_64 * 29.0f)] + 3;
                                }
                                if (var_s0 != sp84) {
                                    sp84 = var_s0;
                                    var_s7 = 0;
                                }
                            }
                            if (var_s7 == 0) {
                                temp_a0 = sp60;
                                var_s6 = _getTexCommon(temp_s1->unk_000, var_s0);
#if 0
                                temp_a0->words.w0 = 0xFD900000;
                                temp_a0->unk_8 = 0xF5900000;
                                temp_a0->unk_10 = 0xE6000000;
                                temp_a0->unk_C = 0x07080200;
                                temp_a0->unk_14 = 0;
                                temp_a0->unk_18 = 0xF3000000;
                                temp_a0->words.w1 = (u32) var_s6->unk_0->unk_4;
#endif
                                temp_a1 = var_s6->unk_4;
                                sp60 = temp_a0 + 8;
                                sp60 = temp_a0 + 0x10;
                                temp_v0 = temp_a0 + 0x18;
                                sp60 = temp_v0;
                                sp60 = temp_a0 + 0x20;
#if 0
                                temp_v1_2 = temp_a1->unk_0;
#endif
                                var_a2 = 0x800;
                                temp_a0_2 = temp_v1_2 >> 4;
                                if (temp_a0_2 != 0) {
                                    var_a2 = temp_a0_2 + 0x7FF;
                                }
                                var_v1 = ((s32) ((temp_v1_2 * temp_a1[1]) + 3) >> 2) - 1;
                                if (var_v1 >= 0x800) {
                                    var_v1 = 0x7FF;
                                }
                                if (temp_a0_2 != 0) {
                                    var_v0_2 = (var_a2 / (s32) temp_a0_2) & 0xFFF;
                                } else {
                                    var_v0_2 = var_a2 & 0xFFF;
                                }
                                temp_a0_3 = sp60;
                                temp_v0->words.w1 = ((var_v1 & 0xFFF) << 0xC) | 0x07000000 | var_v0_2;
                                temp_a0_3->words.w0 = 0xE7000000;
                                temp_a0_3->words.w1 = 0;
                                sp60 = temp_a0_3 + 8;
                                sp60 = temp_a0_3 + 0x10;
#if 0
                                temp_a0_3->unk_C = 0x80200;
                                temp_a0_3->unk_10 = 0xF2000000;
                                temp_a0_3->unk_8 = (s32) (((((s32) (((u16) var_s6->unk_4->unk_0 >> 1) + 7) >> 3) & 0x1FF) << 9) | 0xF5800000);
#endif
                                temp_v1_3 = var_s6->unk_4;
                                sp60 = temp_a0_3 + 0x18;
                                var_s7 += 1;
#if 0
                                temp_a0_3->unk_14 = (s32) (((((temp_v1_3->unk_0 - 1) * 4) & 0xFFF) << 0xC) | (((temp_v1_3->unk_2 - 1) * 4) & 0xFFF));
#endif
                            }
                            func_80046844(temp_s2, &sp60);
                            if (var_s4 == 3) {
                                sp10 = (s32) ((temp_s2->unk_0C[0] * 4.0f) - (f32) (var_s5 * 2));
                                var_v1_2 = temp_s1->unk_014 + var_s5;
                            } else {
                                var_v1_2 = temp_s1->unk_014;
                                sp10 = (s32) (temp_s2->unk_0C[0] * 4.0f);
                            }
                            var_s0_2 = var_s5;
                            temp_a0_4 = var_v1_2 / 2;
                            if (temp_a0_4 < var_s0_2) {
                                var_s0_2 = temp_a0_4;
                            }
                            temp_a0_5 = sp10 + (s32) (temp_s2->unk_30[0] * 4.0f * (f32) var_v1_2);
                            sp1C = temp_a0_5;
                            temp_fv1 = (f32) var_s0_2;
                            sp14 = sp10 + (s32) (temp_s2->unk_30[0] * 4.0f * temp_fv1);
                            sp34 = (var_s0_2 - 1) << 5;
                            sp30 = 0;
                            sp38 = var_s0_2 << 5;
                            sp18 = temp_a0_5 - (s32) (temp_s2->unk_30[0] * 4.0f * temp_fv1);
                            if (var_s4 == 3) {
                                sp20 = (s32) ((temp_s2->unk_0C[1] * 4.0f) - (f32) (var_s5 * 2));
                                var_v1_3 = temp_s1->unk_018 + var_s5;
                            } else {
                                var_v1_3 = temp_s1->unk_018;
                                sp20 = (s32) (temp_s2->unk_0C[1] * 4.0f);
                            }
                            var_s0 = var_s5;
                            temp_a0_6 = var_v1_3 / 2;
                            if (temp_a0_6 < var_s0) {
                                var_s0 = temp_a0_6;
                            }
                            temp_a0_7 = sp20 + (s32) (temp_s2->unk_30[1] * 4.0f * (f32) var_v1_3);
                            sp2C = temp_a0_7;
                            temp_fv1_2 = (f32) var_s0;
                            sp24 = sp20 + (s32) (temp_s2->unk_30[1] * 4.0f * temp_fv1_2);
                            sp44 = (var_s0 - 1) << 5;
                            sp48 = var_s0 << 5;
                            sp50 = -0x400;
                            sp40 = 0;
                            sp54 = 0;
                            sp58 = 0x400;
                            sp28 = temp_a0_7 - (s32) (temp_s2->unk_30[1] * 4.0f * temp_fv1_2);
                            if ((s32) var_s4 < 4) {
                                var_s0 = 0;
                                do {
                                    temp_t1 = &_pnts_1106[var_s0];
                                    temp_a3 = sp60;
                                    temp_v0_2 = &(&sp10)[temp_t1->unk_08];
                                    temp_t0 = temp_a3 + 8;
                                    sp60 = temp_t0;
                                    temp_v0_3 = &(&sp10)[temp_t1->unk_0C];
                                    temp_a3->words.w0 = ((temp_v0_2->unk_0 & ((s32) ~temp_v0_2->unk_2 >> 0x1F) & 0xFFF) << 0xC) | ((temp_v0_3->unk_10 & ((s32) ~temp_v0_3->unk_12 >> 0x1F) & 0xFFF) | 0xE4000000);
                                    temp_v1_4 = &(&sp10)[temp_t1->unk_00];
                                    temp_v0_4 = &(&sp10)[temp_t1->unk_04];
                                    temp_a3->unk_8 = 0xE1000000;
                                    temp_a3->words.w1 = ((temp_v1_4->unk_0 & ((s32) ~temp_v1_4->unk_2 >> 0x1F) & 0xFFF) << 0xC) | (temp_v0_4->unk_10 & ((s32) ~temp_v0_4->unk_12 >> 0x1F) & 0xFFF);
                                    sp60 = temp_a3 + 0x10;
                                    temp_a2 = (&sp10)[temp_t1->unk_14].unk_30;
                                    temp_a0_8 = (&sp10)[temp_t1->unk_00].unk_2;
                                    temp_a1_2 = (&sp10)[temp_t1->unk_10].unk_20;
                                    if (temp_a0_8 >= 0) {
                                        var_a1 = temp_a1_2 << 0x10;
                                    } else {
                                        temp_v0_5 = (&sp10)[temp_t1->unk_18].unk_42;
                                        if (temp_v0_5 < 0) {
                                            var_v1_4 = (s32) (temp_a0_8 * temp_v0_5) >> 7;
                                            var_v0_3 = (s32) ~var_v1_4 >> 0x1F;
                                        } else {
                                            var_v1_4 = (s32) (temp_a0_8 * temp_v0_5) >> 7;
                                            var_v0_3 = -(var_v1_4 < 1);
                                        }
                                        var_a1 = (temp_a1_2 - (var_v1_4 & var_v0_3)) << 0x10;
                                    }
                                    temp_a0_9 = (&sp10)[temp_t1->unk_04].unk_10;
                                    var_v0_4 = temp_a2 & 0xFFFF;
                                    if (temp_a0_9 < 0) {
                                        temp_v1_5 = (&sp10)[temp_t1->unk_1C].unk_42;
                                        if (temp_v1_5 < 0) {
                                            temp_v0_6 = (s32) ((s16) temp_a0_9 * temp_v1_5) >> 7;
                                            var_v0_4 = (temp_a2 - (temp_v0_6 & ((s32) ~temp_v0_6 >> 0x1F))) & 0xFFFF;
                                        } else {
                                            temp_v0_7 = (s32) ((s16) temp_a0_9 * temp_v1_5) >> 7;
                                            var_v0_4 = (temp_a2 - (temp_v0_7 & -(temp_v0_7 < 1))) & 0xFFFF;
                                        }
                                    }
                                    temp_a1_3 = sp60;
                                    temp_t0->words.w1 = var_a1 | var_v0_4;
                                    temp_a1_3->words.w0 = 0xF1000000;
                                    var_s0 += 1;
                                    sp60 = temp_a1_3 + 8;
                                    temp_a1_3->words.w1 = ((&sp10)[temp_t1->unk_18].unk_42 << 0x10) | (&sp10)[temp_t1->unk_1C].unk_42;
                                } while ((u32) var_s0 < 9U);
                            } else {
                                temp_v0_8 = var_s6->unk_4;
                                temp_a3_2 = sp60;
                                temp_t0_2 = temp_a3_2 + 8;
                                temp_ft0 = (s32) temp_s2->unk_0C[0];
                                temp_fv1_3 = (s32) temp_s2->unk_0C[1];
                                sp60 = temp_t0_2;
                                temp_t3 = temp_ft0 * 4;
                                temp_a3_2->words.w1 = (((temp_ft0 * 4) & ((s32) ~temp_t3 >> 0x1F) & 0xFFC) << 0xC) | ((temp_fv1_3 * 4) & ((s32) ~(s16) (temp_fv1_3 * 4) >> 0x1F) & 0xFFC);
                                sp60 = temp_a3_2 + 0x10;
                                temp_a3_2->unk_8 = 0xE1000000;
                                temp_a1_4 = temp_ft0 + temp_v0_8->unk_0;
                                temp_a2_2 = temp_fv1_3 + temp_v0_8->unk_2;
                                temp_a3_2->words.w0 = (((temp_a1_4 * 4) & ((s32) ~(s16) (temp_a1_4 * 4) >> 0x1F) & 0xFFC) << 0xC) | (((temp_a2_2 * 4) & ((s32) ~(s16) (temp_a2_2 * 4) >> 0x1F) & 0xFFC) | 0xE4000000);
                                if (temp_t3 < 0) {
                                    temp_v1_6 = temp_t3 * 8;
                                    var_a0 = (temp_v1_6 & -(temp_v1_6 < 1)) * -0x10000;
                                } else {
                                    var_a0 = 0;
                                }
                                temp_t0_2->words.w1 = var_a0;
                                if (temp_fv1_3 & 0x20000000) {
                                    temp_v0_9 = (s32) (temp_fv1_3 << 0x12) >> 0xD;
                                    temp_t0_2->words.w1 = var_a0 | (-(temp_v0_9 & -(temp_v0_9 < 1)) & 0xFFFF);
                                }
                                temp_v1_7 = sp60;
                                sp60 = temp_v1_7 + 8;
                                temp_v1_7->words.w0 = 0xF1000000;
                                temp_v1_7->words.w1 = 0x04000400;
                            }
                        }
                        goto block_65;
                    }
                } else {
block_65:
                    var_t4 = spB4 + 4;
                }
                spB4 = var_t4;
                var_fp += 1;
            } while (var_fp < sp74);
        }
        var_s4 += 1;
        var_v0 = var_s4 < 9U;
    } while ((s32) var_s4 < 9);
    *sp7C = sp60;
}
#else
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", jtbl_800AF828);

/**
 * Original name: menuCursor_draw1
 */
INCLUDE_ASM("asm/us/nonmatchings/main_segment/main_menu", menuCursor_draw1);
#endif
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", RO_800C5DA0_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", menuCursor_draw1);
#endif

extern const s32 _type_1345[][4];
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", _type_1345);
#endif

/**
 * Original name: menuCursor_draw2
 */
#if VERSION_US
#ifdef NON_MATCHING
void menuCursor_draw2(MenuCursor *cursorArr[], s32 count, Gfx **gxfP) {
    Gfx *gfx = *gxfP;
    MenuCursor *temp_s0_2;
    TiTexData *temp_s1;
    s32 var_s2;
    s32 var_s3;
    s32 var_s4_2;
    s32 var_v0;

    gSPDisplayList(gfx++, fade_alpha_texture_init_dl);

    var_s3 = 0;

    for (var_s2 = 0; var_s2 < count; var_s2++) {
        temp_s0_2 = cursorArr[var_s2];
        if (temp_s0_2->unk_01C.b.unk_30) {
            temp_s1 = _getTexCommon(temp_s0_2->watchMenuRef, 1);
            var_s3 += menuItem_drawAlphaTex(&temp_s0_2->unk_140, &gfx, temp_s1,
                                            _getTexCommon(temp_s0_2->watchMenuRef, 0), var_s3);
        }
    }

    for (var_s2 = 0; var_s2 < 0xB; var_s2++) {
        var_s3 = 0;

        for (var_s4_2 = 0; var_s4_2 < count; var_s4_2++) {
            temp_s0_2 = cursorArr[var_s4_2];
            if ((temp_s0_2->unk_010 != 1) || (temp_s0_2->unk_008 != temp_s0_2->unk_010) ||
                (temp_s0_2->unk_00C != temp_s0_2->unk_008)) {
                var_v0 = _type_1345[temp_s0_2->unk_008 - 1][temp_s0_2->unk_010];
            } else {
                var_v0 = 0xA;
            }

            if (((!temp_s0_2->unk_01C.b.unk_29) | (var_s2 != var_v0)) == 0) {
                temp_s1 = _getTexSetup(temp_s0_2->watchMenuRef, 8);
                var_s3 += func_8004714C(&temp_s0_2->unk_1D0, &gfx, temp_s1, _getTexSetup(temp_s0_2->watchMenuRef, 1),
                                        var_s3, 0xB, var_s2);
            }
        }
    }

    *gxfP = gfx;
}
#else
INCLUDE_ASM("asm/us/nonmatchings/main_segment/main_menu", menuCursor_draw2);
#endif
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", menuCursor_draw2);
#endif

#if VERSION_US || VERSION_CN
void func_80048634(MenuCursor *cursorArr[], s32 count, Gfx **gxfP) {
    menuCursor_draw1(cursorArr, count, gxfP);
    menuCursor_draw2(cursorArr, count, gxfP);
}
#endif

#if VERSION_US
void func_80048680(MenuBottle *bottle, struct_watchMenu *watchMenuRef, s32 arg2, s32 arg3) {
    bottle->watchMenuRef = watchMenuRef;
    bottle->unk_004 = 0;
    menuItem_init(&bottle->unk_08, arg2, arg3);
    menuItem_init(&bottle->unk_98, 4, 0x10);
}
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", func_8004B230_cn);
#endif

#if VERSION_US || VERSION_CN
void func_800486C8(MenuBottle *bottle, MenuItem *arg1) {
    func_800464BC(&bottle->unk_08, arg1);
    func_800464BC(&bottle->unk_98, &bottle->unk_08);
}
#endif

extern const u16 cap_pos_1442[][0xD];
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", cap_pos_1442);
#endif

#if VERSION_US
#if 0
void menuBottle_draw(MenuBottle *bottle, Gfx **gxfP, s32 arg2) {
    Gfx *sp10;
    Gfx *temp_a0;
    Gfx *temp_a0_2;
    Gfx *temp_a1_2;
    Gfx *temp_a2_2;
    Gfx *temp_v1;
    Gfx *temp_v1_2;
    Gfx *temp_v1_5;
    MenuItem *temp_s1;
    TiTexData *temp_t0;
    s16 var_a2;
    s16 var_t0;
    s32 temp_fv1;
    s32 temp_fv1_2;
    s32 temp_v1_3;
    s32 temp_v1_4;
    s32 var_a0;
    s32 var_a1;
    s32 var_a3;
    s32 var_t1;
    s32 var_t2;
    s32 var_t3;
    s32 var_t5;
    s32 var_t6;
    s32 var_v0;
    s32 var_v1;
    u16 *temp_a3;
    u16 *temp_v0;
    u16 *var_t4;
    u16 temp_a1;
    u32 temp_a2;

    temp_v1 = *gxfP;
    sp10 = temp_v1 + 8;
    temp_v1->words.w0 = 0xDE000000;
    temp_v1->words.w1 = (u32) fade_normal_texture_init_dl;
    if (arg2 != 0) {
        temp_v1_2 = sp10;
        temp_t0 = _getTexLevel(bottle->unk_000, 0);
        temp_v1_2->words.w0 = 0xFD100000;
        sp10 = temp_v1_2 + 8;
#if 0
        temp_v1_2->unk_8 = 0xE8000000;
        temp_v1_2->unk_20 = 0xF0000000;
        temp_v1_2->unk_28 = 0xE7000000;
        temp_v1_2->unk_C = 0;
        temp_v1_2->unk_10 = 0xF5000100;
        temp_v1_2->unk_14 = 0x07000000;
        temp_v1_2->unk_18 = 0xE6000000;
        temp_v1_2->unk_1C = 0;
        temp_v1_2->unk_24 = 0x0703C000;
        temp_v1_2->unk_2C = 0;
        temp_v1_2->unk_30 = 0xFD500000;
#endif
        temp_v1_2->words.w1 = (u32) temp_t0->unk_0->unk_0;
        temp_a0 = temp_v1_2 + 0x48;
        sp10 = temp_v1_2 + 0x10;
        sp10 = temp_v1_2 + 0x18;
        sp10 = temp_v1_2 + 0x20;
        sp10 = temp_v1_2 + 0x28;
        sp10 = temp_v1_2 + 0x30;
        sp10 = temp_v1_2 + 0x38;
        sp10 = temp_v1_2 + 0x40;
        sp10 = temp_a0;
        sp10 = temp_v1_2 + 0x50;
#if 0
        temp_v1_2->unk_38 = 0xF5500000;
        temp_v1_2->unk_3C = 0x07080200;
        temp_v1_2->unk_40 = 0xE6000000;
        temp_v1_2->unk_44 = 0;
        temp_v1_2->unk_34 = (s32) temp_t0->unk_0->unk_4;
        temp_v1_2->unk_48 = 0xF3000000;
        temp_v0 = temp_t0->unk_4;
        temp_a1 = temp_v0->unk_0;
#endif
        temp_s1 = &bottle->unk_98;
        temp_a2 = temp_a1 >> 4;
        var_v1 = 0x800;
        if (temp_a2 != 0) {
            var_v1 = temp_a2 + 0x7FF;
        }
#if 0
        var_a1 = ((s32) ((temp_a1 * temp_v0->unk_2) + 3) >> 2) - 1;
#endif
        if (var_a1 >= 0x800) {
            var_a1 = 0x7FF;
        }
        if (temp_a2 != 0) {
            var_v0 = (var_v1 / (s32) temp_a2) & 0xFFF;
        } else {
            var_v0 = var_v1 & 0xFFF;
        }
        temp_a2_2 = sp10;
        temp_a0->words.w1 = ((var_a1 & 0xFFF) << 0xC) | 0x07000000 | var_v0;
        temp_a2_2->words.w0 = 0xE7000000;
        temp_a2_2->words.w1 = 0;
        sp10 = temp_a2_2 + 8;
        sp10 = temp_a2_2 + 0x10;
#if 0
        temp_a2_2->unk_C = 0x80200;
        temp_a2_2->unk_10 = 0xF2000000;
        temp_a2_2->unk_8 = (s32) (((((s32) (((u16) temp_t0->unk_4->unk_0 >> 1) + 7) >> 3) & 0x1FF) << 9) | 0xF5400000);
#endif
        temp_a3 = temp_t0->unk_4;
        sp10 = temp_a2_2 + 0x18;
#if 0
        temp_a2_2->unk_14 = (s32) (((((temp_a3->unk_0 - 1) * 4) & 0xFFF) << 0xC) | (((temp_a3->unk_2 - 1) * 4) & 0xFFF));
#endif
        func_80046844(temp_s1, &sp10);
        var_t3 = 0;
        var_t6 = 1;
        do {
            var_t5 = 2;
            var_t4 = (bottle->unk_004 * 0x1A) + D_800AF890;
            temp_fv1 = (s32) temp_s1->unk_0C[1];
            var_t0 = temp_fv1 * 4;
            var_t2 = (temp_fv1 << 0x12) + 0x140000;
loop_10:
            var_a3 = 7;
            temp_fv1_2 = (s32) temp_s1->unk_0C[0];
            var_a2 = temp_fv1_2 * 4;
            var_t1 = (temp_fv1_2 << 0x12) + 0x140000;
loop_11:
            if ((((s32) *var_t4 >> (var_a3 * 2)) & 3) == var_t6) {
                temp_a0_2 = sp10;
                temp_a1_2 = temp_a0_2 + 8;
                sp10 = temp_a1_2;
                temp_a0_2->words.w0 = (((var_a2 + 0x14) & ((s32) ~(var_t1 >> 0x10) >> 0x1F) & 0xFFF) << 0xC) | (((var_t0 + 0x14) & ((s32) ~(var_t2 >> 0x10) >> 0x1F) & 0xFFF) | 0xE4000000);
                temp_a0_2->words.w1 = ((var_a2 & ((s32) ~var_a2 >> 0x1F) & 0xFFF) << 0xC) | (var_t0 & ((s32) ~var_t0 >> 0x1F) & 0xFFF);
                sp10 = temp_a0_2 + 0x10;
#if 0
                temp_a0_2->unk_8 = 0xE1000000;
#endif
                if (var_a2 < 0) {
                    temp_v1_3 = var_a2 * 8;
                    var_a0 = (temp_v1_3 & -(temp_v1_3 < 1)) * -0x10000;
                } else {
                    var_a0 = 0;
                }
                if (var_t0 < 0) {
                    temp_v1_4 = (s32) (var_t0 << 0xA) >> 7;
                    temp_a1_2->words.w1 = var_a0 | ((var_t3 - (temp_v1_4 & -(temp_v1_4 < 1))) & 0xFFFF);
                } else {
                    temp_a1_2->words.w1 = var_a0 | (var_t3 & 0xFFFF);
                }
                temp_v1_5 = sp10;
                sp10 = temp_v1_5 + 8;
                temp_v1_5->words.w0 = 0xF1000000;
                temp_v1_5->words.w1 = 0x04000400;
            }
            var_t1 += 0x140000;
            var_a3 -= 1;
            var_a2 += 0x14;
            if (var_a3 >= 0) {
                goto loop_11;
            }
            var_t2 += 0x140000;
            var_t0 += 0x14;
            var_t5 += 1;
            var_t4 += 2;
            if (var_t5 < 0xD) {
                goto loop_10;
            }
            var_t6 += 1;
            var_t3 += 0xA0;
        } while (var_t6 < 4);
    }
    *gxfP = sp10;
}
#else
INCLUDE_ASM("asm/us/nonmatchings/main_segment/main_menu", menuBottle_draw);
#endif
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", menuBottle_draw);
#endif

extern const f32 _lvGauge_step[];
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", _lvGauge_step);
#endif

extern const s32 _size_1542[][2];
extern const s32 _type_1543[];

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", _size_1542);
#endif
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", _type_1543);
#endif

extern const s32 _yn_1691[][2];

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", _yn_1691);
#endif

#if VERSION_US
void func_80048B8C(MenuLvGauge *arg0, struct_watchMenu *watchMenuRef, s32 arg2, s32 arg3, s32 arg4, s32 arg5,
                   s32 arg6) {
    arg0->watchMenuRef = watchMenuRef;
    arg0->unk_004 = arg2;
    arg0->unk_008 = 0x14;
    arg0->unk_00C = arg4;
    menuItem_init(&arg0->unk_010, arg5, arg6);
    func_800479A8(&arg0->unk_0A0, watchMenuRef, _type_1543[arg2], arg3, -2, -2, _size_1542[arg2][0],
                  _size_1542[arg2][1]);
}
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", func_8004B7B4_cn);
#endif

#if VERSION_US
void func_80048C48(MenuLvGauge *arg0, s32 arg1) {
    u16 keyRep = _getKeyRep(arg0->watchMenuRef, arg1);
    s32 new_var; //! FAKE
    s32 temp_a0;
    s32 var_s0;
    s32 temp;

    temp = 0;
    if (keyRep & L_JPAD) {
        temp--;
    }
    if (keyRep & R_JPAD) {
        temp++;
    }

    temp_a0 = arg0->unk_00C + temp;
    if (temp_a0 >= 0) {
        new_var = arg0->unk_008;
        var_s0 = new_var;
        if (temp_a0 <= var_s0) {
            var_s0 = temp_a0;
        }
    } else {
        var_s0 = 0;
    }
    // var_s0 = CLAMP(arg0->unk_00C + temp, 0, arg0->unk_008);

    if (var_s0 != arg0->unk_00C) {
        dm_snd_play(SND_INDEX_63);
        new_var = var_s0;
        arg0->unk_00C = new_var;
    }
}
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", func_80048C48);
#endif

#if VERSION_US || VERSION_CN
void func_80048CC8(MenuLvGauge *arg0, MenuItem *arg1) {
    MenuItem *itemTemp;

    func_800464BC(&arg0->unk_010, arg1);

    itemTemp = &arg0->unk_0A0.unk_020;
    itemTemp->unk_24[0] = itemTemp->unk_1C[0] + (_lvGauge_step[arg0->unk_004] * arg0->unk_00C);

    menuCursor_update(&arg0->unk_0A0, &arg0->unk_010);
}
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/main_menu", menuLvGauge_draw1);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", menuLvGauge_draw1);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/main_menu", func_80048FA0);
#endif

#if VERSION_CN
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
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/main_menu", func_80049034);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", func_8004BCB4_cn);
#endif

#if VERSION_US || VERSION_CN
void func_80049080(MenuYN *yn, s32 arg1, f32 arg2) {
    MenuItem *item = &yn->unk_008;

    func_80046614(item, arg1);
    item->unk_64 = arg2;
}
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/main_menu", func_800490B8);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", func_8004BD64_cn);
#endif

#if VERSION_US || VERSION_CN
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
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/main_menu", func_80049224);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", func_8004BF44_cn);
#endif

#if VERSION_US || VERSION_CN
void func_800492D8(MenuYN *yn, MenuItem *parentItem) {
    func_800464BC(&yn->unk_008, parentItem);
    func_800464F8(yn->unk_098, ARRAY_COUNT(yn->unk_098), &yn->unk_008);
    menuCursor_update(&yn->unk_1B8, &yn->unk_098[yn->unk_004]);
    menuCursor_update(&yn->unk_418, &yn->unk_008);
}
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", RO_800C5EE4_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", RO_800C5F28_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", _lvGauge_step);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", RO_800C616C_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", RO_800C6170_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", RO_800C6184_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", _yn_1691);
#endif

ASM_DATA;

const char *_yn_1767[] = {
#if VERSION_US
    "Ｎｏ",   // No
    "Ｙｅｓ", // Yes
#endif
#if VERSION_CN
    "取消", // No
    "确定", // Yes
#endif
};

#if VERSION_US || VERSION_CN
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
        var_fs0 = item->unk_0C[0];

#if VERSION_US
        //! @bug: should be checking for nil character instead
        for (j = 0; j < _yn_1767[i][j]; j += 2) {
            fontXX_draw(&gfx, var_fs0, item->unk_0C[1], 12.0f, 12.0f, &_yn_1767[i][j]);
            var_fs0 += 20.0f;
        }
#endif
#if VERSION_CN
        for (j = 0; _yn_1767[i][j] != '\0'; j += 2) {
            fontXX_draw(&gfx, var_fs0, item->unk_0C[1], 12.0f, 12.0f, &_yn_1767[i][j]);
            var_fs0 += 20.0f;
        }
#endif
    }

    sp18 = &yn->unk_1B8;
    func_80048634(&sp18, 1, &gfx);

    *gfxP = gfx;
}
#endif

#if VERSION_US || VERSION_CN
void func_80049540(MenuMes *mes, s32 arg1, f32 arg2) {
    func_80046614(&mes->unk_004, arg1);
    mes->unk_004.unk_64 = arg2;
}
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/main_menu", func_80049578);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", func_8004C34C_cn);
#endif

#if VERSION_US || VERSION_CN
void menuMes_init(MenuMes *mes, struct_watchMenu *watchMenuRef, struct_watchMenu_unk_02470 **arg2, s32 arg3, s32 arg4,
                  s32 arg5, s32 arg6) {
    MessageWnd *msgWnd;
    MenuItem *item;
    struct_watchMenu_unk_02470 *temp_fp = *arg2;
    f32 a2;

    mes->watchMenuRef = watchMenuRef;

    menuItem_init(&mes->unk_004, arg5, arg6);
    func_800467E0(&mes->unk_004);

    msgWnd_init(&mes->unk_094, (void **)arg2, arg3, arg4, arg5, arg6);

    //! FAKE: ?
    msgWnd = &mes->unk_094;

    mes->unk_094.unk_24 = 1;
    msgWnd->unk_34 = 0xC;
    mes->unk_094.unk_30 = 0xC;
    mes->unk_094.unk_3C = 6;
    mes->unk_094.unk_48 = 0xE;
    func_800479A8(&mes->unk_174, watchMenuRef, 2, 0, -0x10, -0x10, mes->unk_094.unk_3C * arg3 * 2 + 0x20,
                  mes->unk_094.unk_48 * arg4 + 0x20);

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

    *arg2 = temp_fp;
}
#endif

#if VERSION_US || VERSION_CN
void func_8004970C(MenuMes *mes, const char *arg1) {
    msgWnd_clear(&mes->unk_094);
    msgWnd_addStr(&mes->unk_094, arg1);
    msgWnd_skip(&mes->unk_094);
}
#endif

#if VERSION_US || VERSION_CN
void func_80049754(MenuMes *mes, MenuItem *parentItem) {
    func_800464BC(&mes->unk_004, parentItem);
    mes->unk_094.unk_28 = mes->unk_004.unk_0C[0];
    mes->unk_094.unk_2C = mes->unk_004.unk_0C[1];
    mes->unk_094.unk_74 = mes->unk_004.color.v.a * 255.0f;
    msgWnd_update(&mes->unk_094);
    menuCursor_update(&mes->unk_174, &mes->unk_004);
}
#endif

#if VERSION_US || VERSION_CN
void func_800497D0(MenuMes *mes, Gfx **gfxP) {
    MenuCursor *sp10;
    Gfx *gfx;
    MessageWnd *msgWnd = &mes->unk_094;

    gfx = *gfxP;
    if (menuItem_outOfScreen(&mes->unk_004, (msgWnd->unk_38 - 2) * msgWnd->unk_3C + msgWnd->unk_30 + 0xC,
                             (msgWnd->unk_44 - 1) * msgWnd->unk_48 + msgWnd->unk_34 + 0xC)) {
        return;
    }

    sp10 = &mes->unk_174;
    func_80048634(&sp10, 1, &gfx);
    msgWnd_draw(msgWnd, &gfx);

    *gfxP = gfx;
}
#endif

#if VERSION_US || VERSION_CN
/* menuSpeedAsk_init? */
void func_80049894(MenuSpeedAsk *arg0, struct_watchMenu *watchMenuRef, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    arg0->watchMenuRef = watchMenuRef;
    arg0->unk_4 = arg2;
    arg0->unk_8 = arg3;
    menuItem_init(&arg0->unk_C, arg4, arg5);
}
#endif

#if VERSION_US || VERSION_CN
void func_800498C4(MenuSpeedAsk *arg0, MenuItem *arg1) {
    func_800464BC(&arg0->unk_C, arg1);
}
#endif

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", RO_800AFB18);
#endif
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", RO_800AFB1C);
#endif
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", RO_800AFB38);
#endif

extern const s32 _size_1948[][2];
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", _size_1948);
#endif

extern const s8 _pos_1959[][2];
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", _pos_1959);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/main_menu", menuSpeedAsk_draw);
#endif

extern const s32 _tex_1865[][2];
extern const s32 _row_1866[4];

#if VERSION_CN
void menuSpeedAsk_draw(MenuSpeedAsk **speedAskP, s32 count, Gfx **gxfP) {
    Gfx *gfx = *gxfP;
    s32 i;

    gSPDisplayList(gfx++, fade_alpha_texture_init_dl);

    for (i = 0; i < ARRAY_COUNT(_row_1866); i++) {
        s32 j;
        s32 var_s3;

        for (j = 0, var_s3 = 0; j < _row_1866[i]; j++, var_s3 = 0) {
            s32 k;

            for (k = 0; k < count; k++) {
                MenuSpeedAsk *menuSpeedAsk = speedAskP[k];

                if ((i == menuSpeedAsk->unk_4) && (j == menuSpeedAsk->unk_8)) {
                    TiTexData *temp_s0 = _getTexSetup(menuSpeedAsk->watchMenuRef, _tex_1865[menuSpeedAsk->unk_4][0]);
                    TiTexData *a3 = _getTexSetup(menuSpeedAsk->watchMenuRef, _tex_1865[menuSpeedAsk->unk_4][1]);

                    var_s3 += func_80049B8C_cn(&menuSpeedAsk->unk_C, &gfx, temp_s0, a3, var_s3, _row_1866[i], j);
                }
            }
        }
    }

    *gxfP = gfx;
}
#endif

#if VERSION_US || VERSION_CN
s32 _type_1949[] = {
    0x00000005,
    0x00000006,
    0x00000005,
    0x00000006,
};
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", _tex_1865);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", _row_1866);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", _size_1948);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", _pos_1959);
#endif

#if VERSION_US || VERSION_CN
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

    for (i = 0; i < ARRAY_COUNTU(speedItem->unk_254); i++) {
        MenuItem *item = &speedItem->unk_254[i];
        s32 j;

        menuItem_init(item, _pos_1959[arg2][0], _pos_1959[arg2][1]);

        item->colorCallback = colorFunc_cursor;
        item->unk_68 = 1.0f / 32.0f;

        for (j = 0; j < ARRAY_COUNTU(item->unk_6C); j++) {
            s32 k;

            for (k = 0; k < ARRAY_COUNTU(item->unk_6C[j]); k++) {
                item->unk_6C[j][k] = _gameLvItemColor[i][j][k] * (1.0 / 0xFF);
            }
        }
    }

    func_800479A8(&speedItem->unk_404, watchMenuRef, _type_1949[arg2], arg3, -1, -1, _size_1948[arg2][0],
                  _size_1948[arg2][1]);
}
#endif

#if VERSION_US || VERSION_CN
void func_80049C54(MenuSpeedItem *speedItem, s32 arg1) {
    u16 keyRep = _getKeyRep(speedItem->watchMenuRef, arg1);
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
#endif

#if VERSION_US || VERSION_CN
void menuSpeedItem_update(MenuSpeedItem *arg0, MenuItem *arg1) {
    s32 i;

    func_800464BC(&arg0->unk_014, arg1);
    func_800464F8(arg0->unk_0A4, ARRAY_COUNT(arg0->unk_0A4), &arg0->unk_014);

    for (i = 0; i < 3U; i++) {
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

            for (j = 0; j < 4U; j++) {
                var_a0->unk_6C[0][j] = _gameLvItemColor[i][1][j] * (1.0 / 0x1FF);
            }
        } else {
            var_a2 = var_a0->unk_6C[0];

            for (j = 0; j < 4U; j++) {
                var_a0->unk_6C[0][j] = _gameLvItemColor[i][0][j] * (1.0 / 0xFF);
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
#endif

#if VERSION_US || VERSION_CN
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
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/main_menu", func_8004A160);
#endif

#if VERSION_CN
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
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/main_menu", func_8004A1F4);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", func_8004D218_cn);
#endif

#if VERSION_US
void menuMusicItem_init(MenuMusicItem *arg0, struct_watchMenu *watchMenuRef, s32 arg2, s32 arg3, s32 arg4) {
    u32 i;

    arg0->watchMenuRef = watchMenuRef;
    arg0->unk_004 = arg2;
    arg0->unk_008 = -1;
    arg0->unk_00C.b.unk_31 = true;

    menuItem_init(&arg0->unk_010, arg3, arg4);

    for (i = 0; i < ARRAY_COUNTU(arg0->unk_0A0); i++) {
        menuItem_init(&arg0->unk_0A0[i], 0x27 * i, 0);
    }

    for (i = 0; i < 5U; i++) {
        MenuItem *var_s0_2 = &arg0->unk_370[i];
        u32 j;

        menuItem_init(var_s0_2, -2, -2);
        var_s0_2->colorCallback = colorFunc_cursor;
        var_s0_2->unk_68 = 1.0f / 32.0f;

        for (j = 0; j < 2U; j++) {
            u32 k;

            for (k = 0; k < 4U; k++) {
                var_s0_2->unk_6C[j][k] = _musicItemColor[j][k] * (1.0 / 255.0);
            }
        }
    }

    func_800479A8(&arg0->unk_640, watchMenuRef, 5, 0, -1, -1, 0x25, 0x10);
    arg0->unk_640.unk_01C.b.unk_31 = 0;
}
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", func_8004D280_cn);
#endif

extern const SeqIndex _seq_2327[4];
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", _seq_2327);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", _seq_2327);
#endif

#if VERSION_US || VERSION_CN
void menuMusicItem_input(MenuMusicItem *menuMusicItem, s32 arg1) {
    u16 keyRep = _getKeyRep(menuMusicItem->watchMenuRef, arg1);
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
#endif

#if VERSION_US || VERSION_CN
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

            for (j = 0; j < 4U; j++) {
                temp_s0_2->unk_6C[0][j] = RO_800AF530[j] * (1.0 / 0x1FF);
            }
        } else {
            var_a1 = temp_s0_2->unk_6C[0];
            for (j = 0; j < 4U; j++) {
                temp_s0_2->unk_6C[0][j] = _musicItemColor[0][j] * (1.0 / 0xFF);
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
#endif

#if VERSION_US || VERSION_CN
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
#endif

#if VERSION_US || VERSION_CN
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
#endif

#if VERSION_US
void func_8004A814(MenuMusicItem *musicItemArr[], s32 arg1, Gfx **gfxP) {
    menuMusicItem_draw1(musicItemArr, arg1, gfxP);
    menuMusicItem_draw2(musicItemArr, arg1, gfxP);
}
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", func_8004D918_cn);
#endif

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", RO_800AFBB0);
#endif
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", RO_800AFBD8);
#endif

#if VERSION_US || VERSION_CN
void func_8004A860(MenuNumber *arg0, struct_watchMenu *watchMenuRef, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    arg0->watchMenuRef = watchMenuRef;
    arg0->unk_04 = arg2;
    arg0->unk_08 = arg3;
    arg0->unk_0C = arg4;
    arg0->unk_10 |= 0x80000000;
    bzero(&arg0->unk_14, sizeof(MenuNumber_unk_14));
    menuItem_init(&arg0->unk_1C, arg5, arg6);
}
#endif

#if VERSION_US || VERSION_CN
void menuNumber_update(MenuNumber *menuNumber, MenuItem *item) {
    s32 var_a3 = menuNumber->unk_0C;
    s32 i;

    for (i = menuNumber->unk_08 - 1; i >= 0; i--) {
        menuNumber->unk_14.unk_0[i] = var_a3 % 10;
        var_a3 /= 10;
    }
    func_800464BC(&menuNumber->unk_1C, item);
}
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/main_menu", menuNumber_draw);
#endif

TiTexData *_getTexGameAl(struct_watchMenu *, s32 arg1);

extern const UNK_TYPE RO_800C6248_cn[];
extern const UNK_TYPE RO_800C6270_cn[];

#if VERSION_CN
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
    s32 var_s6;
    s32 var_s5;
    s32 temp_s4;
    s32 sp40;

    gSPDisplayList(gfx++, fade_alpha_texture_init_dl);

    for (temp_t4 = 0; temp_t4 < 2; temp_t4++) {
        //! FAKE? var_s6 asignment needs to be on the conditional part of the loop
        for (var_fp = 0; var_s6 = 0, var_fp < 0xA; var_fp++) {
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

                var_s5 = MIN(sp34->unk_4[0], var_t1->unk_4[0]);
                temp_s4 = MIN(sp34->unk_4[1], var_t1->unk_4[1]) / 10;

                if (menuItem_outOfScreen(temp_s3, var_s5 * temp_s0->unk_08, temp_s4)) {
                    continue;
                }

                func_80046844(temp_s3, &gfx);

                for (var_s2 = 0; var_s2 < temp_s0->unk_08; var_s2++) {
                    if ((sp40 == 0) && (temp_s0->unk_14.unk_0[var_s2] == 0)) {
                        continue;
                    }

                    sp40 = 1;
                    if ((temp_t4 != temp_s0->unk_04) || (var_fp != temp_s0->unk_14.unk_0[var_s2])) {
                        continue;
                    }

                    tiStretchAlphaTexItem(&gfx, sp34, var_t1, var_s6++, 0xA, RO_800C6248_cn[var_fp],
                                          temp_s3->unk_0C[0] + (RO_800C6270_cn[temp_t4] * temp_s3->unk_30[0] * var_s2),
                                          temp_s3->unk_0C[1], var_s5 * temp_s3->unk_30[0],
                                          temp_s4 * temp_s3->unk_30[1]);
                }
            }
        }
    }

    *gxfP = gfx;
}
#endif

#if VERSION_US
void func_8004AC98(MenuComLvPanel *comLvPanel, s32 arg1, f32 arg2) {
    func_800467E0(&comLvPanel->unk_008);
    func_80046614(&comLvPanel->unk_008, arg1);
    comLvPanel->unk_008.unk_64 = arg2;
}
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", func_8004DE20_cn);
#endif

#if VERSION_US
void func_8004ACF4(MenuComLvPanel *comLvPanel, s32 arg1) {
    func_8004AC98(comLvPanel, arg1, comLvPanel->unk_008.unk_64);
}
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", func_8004DE8C_cn);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/main_menu", func_8004AD10);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", func_8004DEB8_cn);
#endif

#if VERSION_US
void func_8004AD3C(MenuComLvPanel *arg0, struct_watchMenu *watchMenuRef, s32 arg2, s32 arg3, s32 arg4) {
    arg0->unk_004 = arg2;
    arg0->watchMenuRef = watchMenuRef;
    menuItem_init(&arg0->unk_008, arg3, arg4);
    menuItem_init(&arg0->unk_098, 0, 10);
}
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", func_8004DEE0_cn);
#endif

#if VERSION_US
void func_8004AD84(MenuComLvPanel *comLvPanel, MenuItem *parent) {
    func_800464BC(&comLvPanel->unk_008, parent);
    func_800464BC(&comLvPanel->unk_098, &comLvPanel->unk_008);
}
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", func_8004DF44_cn);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/main_menu", menuComLvPanel_draw);
#endif

#if VERSION_CN
void menuComLvPanel_draw(MenuComLvPanel **comLvPanelP, s32 count, Gfx **gfxP) {
    Gfx *gfx = *gfxP;
    s32 var_s6 = 0;
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

        if (menuItem_outOfScreen(item, temp_v0->unk_4[0], temp_v0->unk_4[1])) {
            continue;
        }

        if (item->color.v.a < 1.0f) {
            gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
        } else {
            gDPSetRenderMode(gfx++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
        }
        func_80046844(item, &gfx);

        tiStretchTexTile(&gfx, temp_v0, var_s6, 0, 0, temp_v0->unk_4[0], 0x14, item->unk_0C[0], item->unk_0C[1],
                         item->unk_30[0] * temp_v0->unk_4[0], item->unk_30[1] * 20.0f);
        var_s6++;
    }

    for (j = 7; j > 0; j--) {
        for (i = 0; i < count; i++) {
            comLvPanel = comLvPanelP[i];
            if (j != comLvPanel->unk_004) {
                continue;
            }

            temp_v0 = _getTexChar(comLvPanel->watchMenuRef, 6);
            item = &comLvPanel->unk_098;
            if (menuItem_outOfScreen(&comLvPanel->unk_008, temp_v0->unk_4[0], temp_v0->unk_4[1])) {
                continue;
            }

            if (item->color.v.a < 1.0f) {
                gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
            } else {
                gDPSetRenderMode(gfx++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
            }
            func_80046844(item, &gfx);
            tiStretchTexTile(&gfx, temp_v0, 0, 0, 0x14, (temp_v0->unk_4[0] * j) / 7, 0xA, item->unk_0C[0],
                             item->unk_0C[1], (item->unk_30[0] * temp_v0->unk_4[0] * j) / 7.0f,
                             item->unk_30[1] * 10.0f);
        }
    }

    *gfxP = gfx;
}
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", RO_800C6248_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", RO_800C6270_cn);
#endif

extern const f32 RO_800AFBE0[3];
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", RO_800AFBE0);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", RO_800AFBE0);
#endif

#if VERSION_US || VERSION_CN
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
#endif

extern const s32 _posDesc_2860[][2];
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", _posDesc_2860);
#endif

extern const s32 _posLine_2861[][2];
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", _posLine_2861);
#endif

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", _line_2914);
#endif

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", RO_800AFC20);
#endif

#if VERSION_US || VERSION_CN
void func_8004B2C8(MenuCont *cont, s32 arg1, s32 arg2) {
    MenuItem *item = &cont->unk_004;

    item->unk_14 = arg2;
    item->unk_18 = 0.05f;
    item->unk_1C[0] = item->unk_24[0] - 160.0f;
    func_8004655C(item, arg1);
}
#endif

#if VERSION_US || VERSION_CN
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
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/main_menu", func_8004B43C);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", func_8004E6DC_cn);
#endif

#if VERSION_US || VERSION_CN
void func_8004B488(MenuCont *cont, MenuItem *parentItem) {
    func_800464BC(&cont->unk_004, parentItem);
    func_800464F8(cont->unk_094, ARRAY_COUNT(cont->unk_094), &cont->unk_004);
    func_800464F8(cont->unk_364, ARRAY_COUNT(cont->unk_364), &cont->unk_004);
    func_800464BC(cont->unk_3F4, parentItem);
    func_800464BC(cont->unk_484, parentItem);
}
#endif

extern const s32 _panel_3220[];
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", _panel_3220);
#endif

#if VERSION_US
#if 0
//? menuItem_drawAlphaTex(MenuItem *, Gfx **, TiTexData *, TiTexData *, s32); /* extern */

void menuCont_draw(MenuCont *cont, Gfx **gfxP) {
    Gfx *gfx;
    Gfx *temp_v0;
    MenuItem *temp_s1;
    TiTexData *temp_s0;
    TiTexData *temp_s0_2;
    s32 *var_s3_2;
    s32 *var_s4;
    s32 temp_a1;
    s32 temp_a1_2;
    s32 var_s2;
    s32 var_s2_2;

    gfx = *gfxP;

    gSPDisplayList(gfx++, fade_normal_texture_init_dl);
    menuItem_drawTex(&cont->unk_004, &gfx, func_80059DD4(cont->watchMenuRef, 7), 0);

    gSPDisplayList(gfx++, fade_intensity_texture_init_dl);

    var_s2 = 0;
    do {
        temp_s1 = &cont->unk_364[var_s2];
        temp_a1 = _panel_3220[var_s2];
        menuItem_drawTex(temp_s1, &gfx, func_80059DC4(cont->watchMenuRef, temp_a1), 0);
        var_s2 += 1;
    } while (var_s2 < 1U);

    var_s2_2 = 0;

    gSPDisplayList(gfx++, fade_normal_texture_init_dl);
    gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);

    temp_s0 = func_80059DC4(cont->watchMenuRef, 2, 0xE200001C);
    do {
        func_80046F58(&cont->unk_094[var_s2_2], &gfx, temp_s0, 0, 4, var_s2_2);
        var_s2_2 += 1;
    } while ((u32) var_s2_2 < 4U);

    var_s3_2 = &(*_posLine_2861)[var_s2_2];

    while ((u32) var_s2_2 < 5U) {
        temp_a1_2 = *var_s3_2;
        var_s3_2 += 4;
        menuItem_drawTex(&cont->unk_094[var_s2_2], &gfx, func_80059DC4(cont->watchMenuRef, temp_a1_2), 0);
        var_s2_2 += 1;
    }

    func_80046F58(cont->unk_3F4, &gfx, _getTexCommon(cont->watchMenuRef, 0xE), 0, 0x2F, 0x13);

    gSPDisplayList(gfx++, fade_alpha_texture_init_dl);

    temp_s0_2 = func_80059DD4(cont->watchMenuRef, 1);
    menuItem_drawAlphaTex(cont->unk_484, &gfx, temp_s0_2, func_80059DD4(cont->watchMenuRef, 3), 0);
    *gfxP = gfx;
}
#else
INCLUDE_ASM("asm/us/nonmatchings/main_segment/main_menu", menuCont_draw);
#endif
#endif

//? func_80049754_cn(MenuItem *, Gfx **, TiTexData *, TiTexData *, s32); /* extern */
// TiTexData *func_8005FE70_cn(struct_watchMenu *, s32, Gfx *, u32); /* extern */
// TiTexData *func_8005FE80_cn(struct_watchMenu *, ?, Gfx *); /* extern */
extern const s32 RO_800C62B4_cn[];

#if VERSION_CN
#if 0
// Matches, but there's a fake symbol that I need to figure out, but I want to go to sleep

extern const s32 TODO_NEED_TO_FIGURE_OUT[];
void menuCont_draw(MenuCont *cont, Gfx **gfxP) {
    Gfx *gfx;
    MenuItem *var_s2;
    TiTexData *temp_s3;
    TiTexData *temp;
    s32 var_s1;

    gfx = *gfxP;
    gSPDisplayList(gfx++, fade_normal_texture_init_dl);

    var_s2 = &cont->unk_004;
    temp_s3 = func_8005FE80_cn(cont->watchMenuRef, 7);
    menuItem_drawTex(var_s2, &gfx, temp_s3, 0);

    gSPDisplayList(gfx++, fade_intensity_texture_init_dl);

    for (var_s1 = 0; var_s1 < 1U; var_s1++) {
        var_s2 = &cont->unk_364[var_s1];
        temp_s3 = func_8005FE70_cn(cont->watchMenuRef, RO_800C62B4_cn[var_s1]);
        menuItem_drawTex(var_s2, &gfx, temp_s3, 0);
    }

    gSPDisplayList(gfx++, fade_normal_texture_init_dl);
    gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);

    temp_s3 = func_8005FE70_cn(cont->watchMenuRef, 2);
    for (var_s1 = 0; var_s1 < 4U; var_s1++) {
        var_s2 = &cont->unk_094[var_s1];
        func_80046F58(var_s2, &gfx, temp_s3, 0, 4, var_s1);
    }

    for (; var_s1 < 5U; var_s1++) {
        var_s2 = &cont->unk_094[var_s1];
        temp_s3 = func_8005FE70_cn(cont->watchMenuRef, TODO_NEED_TO_FIGURE_OUT[var_s1-UNK_SIZE]);
        menuItem_drawTex(var_s2, &gfx, temp_s3, 0);
    }

    func_80046F58(cont->unk_3F4, &gfx, _getTexCommon(cont->watchMenuRef, 0xE), 0, 0x2F, 0x13);

    gSPDisplayList(gfx++, fade_alpha_texture_init_dl);

    temp_s3 = func_8005FE80_cn(cont->watchMenuRef, 1);
    temp = func_8005FE80_cn(cont->watchMenuRef, 3);
    func_80049754_cn(cont->unk_484, &gfx, temp_s3, temp, 0);

    *gfxP = gfx;
}
#else
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", menuCont_draw);
#endif
#endif

#if VERSION_US || VERSION_CN
void func_8004B774(MenuMainPanel *mainPanel, s32 arg1, f32 arg2) {
    MenuItem *item = &mainPanel->unk_028;

    item->unk_14 = arg2;
    item->unk_18 = 0.05f;
    // TODO: SCREEN_WIDTH?
    item->unk_1C[0] = item->unk_24[0] - 320.0f;
    func_8004655C(item, arg1);
}
#endif

#if VERSION_US || VERSION_CN
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
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/main_menu", func_8004B8CC);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", func_8004EC80_cn);
#endif

#if VERSION_US || VERSION_CN
void func_8004B98C(MenuMainPanel *arg0, MenuItem *parentItem) {
    func_800464BC(&arg0->unk_028, parentItem);
    func_800464F8(arg0->unk_0B8, arg0->unk_008, &arg0->unk_028);
    menuCursor_update(&arg0->unk_418, &arg0->unk_0B8[arg0->unk_00C]);
}
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", _posDesc_2860);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", _posLine_2861);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", RO_800C62B4_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", _panel_3220);
#endif

#if VERSION_US || VERSION_CN
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
#endif

#if VERSION_US || VERSION_CN
void func_8004BB14(MenuNameSelPanel *nameSelPanel, s32 arg1, f32 arg2) {
    MenuItem *item = &nameSelPanel->unk_028;

    item->unk_14 = arg2;
    item->unk_18 = 0.05f;
    item->unk_1C[0] = item->unk_24[0] - 320.0f;
    func_8004655C(item, arg1);
}
#endif

#if VERSION_US || VERSION_CN
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
#endif

#if VERSION_US || VERSION_CN
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
            item->unk_64 = WrapF(0.0f, 1.0f, item->unk_64 + 0.5);

            item = &nameSelPanel->unk_5C8[i].unk_140;
            item->unk_14 = WrapF(0.0f, 1.0f, item->unk_14 + 0.5);
            item->unk_1C[0] += nameSelPanel->unk_5C8[i].unk_014 + 0x10;
            item->unk_24[0] += nameSelPanel->unk_5C8[i].unk_014 + 0x10;
            item->unk_40[0] = -item->unk_40[0];
            item->unk_48[0] = -item->unk_48[0];

            item = &nameSelPanel->unk_5C8[i].unk_1D0;
            item->unk_14 = WrapF(0.0f, 1.0f, item->unk_14 + 0.5);
            item->unk_1C[0] += nameSelPanel->unk_5C8[i].unk_014 + 0x10;
            item->unk_24[0] += nameSelPanel->unk_5C8[i].unk_014 + 0x10;
        }
    }

    menuNameSelPanel_clear(nameSelPanel, arg2, arg3);
}
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/main_menu", func_8004BEB4);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", func_8004F374_cn);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/main_menu", func_8004BF10);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", func_8004F3D0_cn);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/main_menu", func_8004C1F0);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", func_8004F79C_cn);
#endif

#if VERSION_US || VERSION_CN
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
#endif

#if VERSION_US
                nameSelPanel->unk_5C8[i].unk_0B0.unk_6C[0][3] = 0;
                nameSelPanel->unk_5C8[j].unk_0B0.unk_6C[0][3] = 0;
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
#endif

extern const s32 _texEndOrGuest_3608[];
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", _texEndOrGuest_3608);
#endif

#if VERSION_US
#if 0
void menuNameSelPanel_draw(MenuNameSelPanel *nameSelPanel, Gfx **gfxP) {
    MenuCursor *sp18;
    Gfx **sp2C = gfxP;
    Gfx *gfx = *sp2C; // sp 20

    MenuItem *temp_s3;
    TiTexData *temp_s0;
    s32 var_s2;
    s32 var_s4;
    struct_evs_mem_data *evsMemData;
    //s32 v0 = nameSelPanel->unk_004;
    MenuCursor *sp34[nameSelPanel->unk_004];


    gSPDisplayList(gfx++, fade_normal_texture_init_dl);

    temp_s0 = _getTexMain(nameSelPanel->watchMenuRef, 4);
    menuItem_drawTex(&nameSelPanel->unk_028, &gfx, temp_s0, 0);
    temp_s0 = _getTexMain(nameSelPanel->watchMenuRef, 7);

    var_s2 = 0;
    var_s4 = 0;
    while (var_s4 < 8U) {
        var_s2 += menuItem_drawTex(&nameSelPanel->unk_0B8[var_s4], &gfx, temp_s0, var_s2);
        var_s4 += 1;
    }


    temp_s0 = _getTexMain(nameSelPanel->watchMenuRef, _texEndOrGuest_3608[nameSelPanel->unk_024.b.unk_31]);
    menuItem_drawTex(&nameSelPanel->unk_0B8[var_s4], &gfx, temp_s0, 0);

    gSPDisplayList(gfx++, fade_intensity_texture_init_dl);
    gDPSetTextureFilter(gfx++, G_TF_BILERP);

    var_s4 = 0;
    while (var_s4 < 8U) {
        temp_s3 = &nameSelPanel->unk_0B8[var_s4];

        if (menuItem_outOfScreen(temp_s3, 0xE, 0xE) == false) {
            u8 *var_s1_2;

            //var_s7 = &evs_mem_data->unk_00[1] - 1;
            evsMemData = evs_mem_data;

            if (evsMemData[var_s4].unk_00[0] & 1) {
                gDPSetPrimColor(gfx++, 0, 0, 1, 1, 1, (s32) (temp_s3->color.v.a * 255.0f));
            } else {
                gDPSetPrimColor(gfx++, 0, 0, 160, 160, 160, 255);
            }

            //var_s1_2 = &(&evs_mem_data->unk_00[1])[var_s6];
            var_s1_2 = &evsMemData[var_s4].unk_00[1];
            var_s2 = 0;
            do {
                //temp_v0_2 = evsMemData[var_s4].unk_00[var_s2+1];
                fontXX_drawID(&gfx, temp_s3->unk_0C[0] + 4.0f + var_s2*12, temp_s3->unk_0C[1] + 4.0f, temp_s3->unk_30[0] * 12.0f, temp_s3->unk_30[1] * 12.0f, var_s1_2[var_s2]);
                var_s2 += 1;
            } while (var_s2 < 4);
        }
        var_s4 += 1;
    }

    var_s4 = 0;
    while (var_s4 < nameSelPanel->unk_004) {
        sp34[var_s4] = &nameSelPanel->unk_5C8[var_s4];
        var_s4 += 1;
    }

    func_80048634(sp34, nameSelPanel->unk_004, &gfx);
    *sp2C = gfx;
}
#else
INCLUDE_ASM("asm/us/nonmatchings/main_segment/main_menu", menuNameSelPanel_draw);
#endif
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", menuNameSelPanel_draw);
#endif

#if VERSION_US || VERSION_CN
void func_8004C820(MenuNameOpPanel *nameOpPanel, s32 arg1, f32 arg2) {
    MenuItem *item = &nameOpPanel->unk_010;

    item->unk_14 = arg2;
    item->unk_18 = 0.05f;
    item->unk_1C[0] = item->unk_24[0] - 320.0f;
    func_8004655C(item, arg1);
}
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", RO_800C62D0_cn);
#endif

extern const u8 _name_3803[];
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", _name_3803);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", _name_3803);
#endif

#if VERSION_US || VERSION_CN
void menuNameOpPanel_init(MenuNameOpPanel *nameOpPanel, struct_watchMenu *watchMenuRef, s32 arg2, s32 arg3,
                          const u8 *arg4, s32 xPos, s32 yPos) {
    u32 i;

    nameOpPanel->watchMenuRef = watchMenuRef;
    nameOpPanel->unk_004 = arg2;
    nameOpPanel->unk_008 = arg3;

    if (arg4 == NULL) {
        arg4 = _name_3803;
    }

    for (i = 0; i < ARRAY_COUNTU(nameOpPanel->unk_00C); i++) {
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
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/main_menu", func_8004C974);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", func_800500B0_cn);
#endif

#if VERSION_US || VERSION_CN
void func_8004CA30(MenuNameOpPanel *nameOpPanel, MenuItem *parentItem) {
    func_800464BC(&nameOpPanel->unk_010, parentItem);
    func_800464BC(&nameOpPanel->unk_0A0, &nameOpPanel->unk_010);
    func_800464F8(nameOpPanel->unk_130, ARRAY_COUNT(nameOpPanel->unk_130), &nameOpPanel->unk_010);
    menuCursor_update(&nameOpPanel->unk_250, &nameOpPanel->unk_130[nameOpPanel->unk_008]);
}
#endif

extern const s32 _panel_3859[][2];
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", _panel_3859);
#endif

#if VERSION_US || VERSION_CN
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
        fontXX_drawID(&gfx, item->unk_0C[0] + 4.0f + (i * 12), item->unk_0C[1] + 4.0f, item->unk_30[0] * 12.0f,
                      item->unk_30[1] * 12.0f, nameOpPanel->unk_00C[i]);
    }

    sp1C[0] = &nameOpPanel->unk_250;
    func_80048634(sp1C, ARRAY_COUNT(sp1C), &gfx);

    *gfxP = gfx;
}
#endif

#if VERSION_US || VERSION_CN
void func_8004CCD0(MenuSndSelPanel *sndSelPanel, s32 arg1, f32 arg2) {
    MenuItem *item = &sndSelPanel->unk_014;

    item->unk_14 = arg2;
    item->unk_18 = 0.05f;
    item->unk_1C[0] = item->unk_24[0] - 320.0f;
    func_8004655C(item, arg1);
}
#endif

extern const s32 _pos_4015[];
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", _pos_4015);
#endif

extern const s32 _y_4020[];
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", _y_4020);
#endif

#if VERSION_US || VERSION_CN
void menuSndSelPanel_init(MenuSndSelPanel *sndSelPanel, struct_watchMenu *watchMenuRef, s32 arg2, s32 arg3, s32 arg4) {
    u32 i;

    sndSelPanel->watchMenuRef = watchMenuRef;
    sndSelPanel->unk_004 = arg2;
    sndSelPanel->unk_008 = 0;
    sndSelPanel->unk_00C = 0;
    sndSelPanel->unk_010 = 0;

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
#endif

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", RO_800AFC74);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/main_menu", func_8004CE48);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", func_80050670_cn);
#endif

#if VERSION_US || VERSION_CN
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
#endif

extern const s32 _panel_4108[];
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", _panel_4108);
#endif

#if VERSION_US || VERSION_CN
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

    temp_fs0 = item->unk_0C[0];
    temp_fs1 = item->unk_0C[1];
    temp_v0 = _getTexMain(sndSelPanel->watchMenuRef, 0xB);

    menuItem_drawTex(item, &gfx, temp_v0, 0);
    item->unk_0C[1] += 76.0f;
    menuItem_drawTex(item, &gfx, temp_v0, 0);
    item->unk_0C[0] = temp_fs0 + 19.0f;
    item->unk_0C[1] = temp_fs1 + 2.0f;
    temp_v0 = _getTexMain(sndSelPanel->watchMenuRef, 0xC);
    menuItem_drawTex(item, &gfx, temp_v0, 0);
    item->unk_0C[0] = temp_fs0;
    item->unk_0C[1] = temp_fs1;

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
#endif

#if VERSION_US
void func_8004D258(void *arg) {
    MenuPlay2Panel *play2Panel = arg;
    void *sp10 = play2Panel->unk_002C;

    animeState_load(&play2Panel->unk_0C90, &sp10, play2Panel->unk_0020);
    play2Panel->unk_0030.b.bit_30 = true;
}
#endif

extern const f32 _lvNumScale_4308[][2];
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", _lvNumScale_4308);
#endif

extern const s32 _player_4309[][2];
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", _player_4309);
#endif

extern const s32 _lvNum_4310[][2];
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", _lvNum_4310);
#endif

extern const s32 _lvGauge_4311[][2];
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", _lvGauge_4311);
#endif

extern const s32 _speedAsk_4312[][2];
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", _speedAsk_4312);
#endif

extern const s32 _speedItem_4313[][2];
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", _speedItem_4313);
#endif

extern const s32 _glvAsk_4314[][2];
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", _glvAsk_4314);
#endif

extern const s32 _glvItem_4315[][2];
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", _glvItem_4315);
#endif

extern const s32 _okY_4316[];
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", _okY_4316);
#endif

extern const s32 _cursor_4317[][4];
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", _cursor_4317);
#endif

#if VERSION_US
#ifdef NON_MATCHING
// swapped instructions
void menuPlay2Panel_init(MenuPlay2Panel *play2Panel, struct_watchMenu *watchMenuRef, struct_watchMenu_unk_02470 **arg2,
                         s32 arg3, s32 arg4, s32 arg5, s32 arg6, bool arg7, CharAnimeMode arg8, s32 arg9, s32 argA,
                         s32 argB, s32 argC) {
    struct_watchMenu_unk_02470 *var_s6 = *arg2;
    s32 var_s4;

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
        func_80046688(&play2Panel->unk_01E4.unk_1C, _lvNumScale_4308[arg3][0], _lvNumScale_4308[arg3][1]);
        func_80046694(&play2Panel->unk_01E4.unk_1C, _lvNumScale_4308[arg3][0], _lvNumScale_4308[arg3][1]);
    }

    func_80049894(&play2Panel->unk_0590, watchMenuRef, 0, argA, _speedAsk_4312[arg3][0], _speedAsk_4312[arg3][1]);
    menuSpeedItem_init(&play2Panel->unk_062C, watchMenuRef, arg3, arg6, argA, _speedItem_4313[arg3][0],
                       _speedItem_4313[arg3][1], 0x2A);
    switch (arg3) {
        case 0:
            break;

        case 1:
            play2Panel->unk_002C = ALIGN_PTR(var_s6);
            var_s6 = play2Panel->unk_002C + animeState_getDataSize(arg8);
            func_80040B10(func_8004D258, play2Panel);
            break;
    }

    menuItem_init(&play2Panel->unk_0CD0, 8, _okY_4316[arg3]);
    func_800467E0(&play2Panel->unk_0CD0);
    func_80046614(&play2Panel->unk_0CD0, -1);
    play2Panel->unk_0CD0.unk_64 = 0.0f;

    // I think this `*2` will always make an OoB read becase `_cursor_4317` isn't big enough
    arg3 *= 2;

    for (var_s4 = 0; var_s4 < 2U; arg3++, var_s4++) {
        func_800479A8(&play2Panel->unk_0D60[var_s4], watchMenuRef, 1, arg6, _cursor_4317[arg3][0],
                      _cursor_4317[arg3][1], _cursor_4317[arg3][2], _cursor_4317[arg3][3]);
    }

    *arg2 = var_s6;
}
#else
INCLUDE_ASM("asm/us/nonmatchings/main_segment/main_menu", menuPlay2Panel_init);
#endif
#endif

#if VERSION_US
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
#endif

#if VERSION_US
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
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/main_menu", func_8004D828);
#endif

#if VERSION_US
void menuPlay2Panel_update(MenuPlay2Panel *play2Panel, MenuItem *parentItem) {
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
        default:
        case 0:
            break;

        case 1:
            if (play2Panel->unk_0030.b.bit_30) {
                play2Panel->unk_0C90.primColor[0] = play2Panel->unk_00C4.color.v.r * 255;
                play2Panel->unk_0C90.primColor[1] = play2Panel->unk_00C4.color.v.g * 255;
                play2Panel->unk_0C90.primColor[2] = play2Panel->unk_00C4.color.v.b * 255;
                play2Panel->unk_0C90.primColor[3] = play2Panel->unk_00C4.color.v.a * 255;
                animeState_update(&play2Panel->unk_0C90);
            }
            break;
    }

    func_800464BC(&play2Panel->unk_0CD0, &play2Panel->unk_0034);

    if (play2Panel->unk_0028 == 1) {
        MenuItem *var_a0_2 = &play2Panel->unk_0CD0;

        for (i = 0; i < ARRAY_COUNTU(var_a0_2->color.arr); i++) {
            var_a0_2->color.arr[i] = parentItem->color.arr[i];
        }
    }

    for (i = 0; i < ARRAY_COUNTU(play2Panel->unk_0D60); i++) {
        menuCursor_update(&play2Panel->unk_0D60[i], &play2Panel->unk_0034);
    }

    func_80046614(&play2Panel->unk_0034, (play2Panel->unk_0028 != 0) ? -1 : 1);

    i = false;
    if (play2Panel->unk_0028 == 0) {
        i = play2Panel->unk_0024 == 0;
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

    i = false;
    if (play2Panel->unk_0028 == 0) {
        i = play2Panel->unk_0024 == 1;
    }

    play2Panel->unk_062C.unk_00C = i;
    play2Panel->unk_0D60[1].unk_01C.b.unk_31 = i;

    play2Panel->unk_062C.unk_404.unk_01C.b.unk_30 = i;
}
#endif

extern const s32 _charTbl_4601[];
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", _charTbl_4601);
#endif

extern const s32 _type_4602[][4];
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", _type_4602);
#endif

extern const s32 _texPanelP4_4617[];
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", _texPanelP4_4617);
#endif

extern const s32 _texPanelP2_4618[];
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", _texPanelP2_4618);
#endif

#if VERSION_US
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
                    animeState_draw(&var_s2->unk_0C90, &gfx, var_s2->unk_00C4.unk_0C[0], var_s2->unk_00C4.unk_0C[1],
                                    -1.0f, 1.0f);
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
#endif

#if VERSION_US
void func_8004E270(MenuPlay2PanelSub *play2PanelSub, s32 arg1, f32 arg2) {
    play2PanelSub->unk_010.unk_14 = arg2;
    play2PanelSub->unk_010.unk_18 = 0.05f;
    play2PanelSub->unk_010.unk_1C[1] = play2PanelSub->unk_010.unk_24[1] - 240.0f;
    func_8004655C(&play2PanelSub->unk_010, arg1);
}
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/main_menu", func_8004E2B4);
#endif

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", RO_800AFEB8);
#endif

extern const s32 _bgCursor_4920[][2];
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", _bgCursor_4920);
#endif

extern const s32 _cursor_4921[][4];
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", _cursor_4921);
#endif

#if VERSION_US
void menuPlay2PanelSub_init(MenuPlay2PanelSub *play2PanelSub, struct_watchMenu *watchMenuRef,
                            struct_watchMenu_unk_02470 **arg2 UNUSED, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    s32 i;

    play2PanelSub->watchMenuRef = watchMenuRef;
    play2PanelSub->unk_004 = 0;
    play2PanelSub->unk_008 = 0;
    play2PanelSub->unk_00C = -1;

    menuItem_init(&play2PanelSub->unk_010, arg5, arg6);
    menuMusicItem_init(&play2PanelSub->unk_0A0, watchMenuRef, arg4, 0x46, 9);

    func_8004A860(&play2PanelSub->unk_940, watchMenuRef, 1, 2, arg3, 0x60, 0x28);
    func_80046688(&play2PanelSub->unk_940.unk_1C, 0.875f, 0.9375f);
    func_80046694(&play2PanelSub->unk_940.unk_1C, 0.875f, 0.9375f);
    menuItem_init(&play2PanelSub->unk_9EC, 0x9C, 0x30);

    for (i = 0; i < ARRAY_COUNTU(play2PanelSub->unk_B9C); i++) {
        menuItem_init(&play2PanelSub->unk_A7C[i], _bgCursor_4920[i][0], _bgCursor_4920[i][1]);
        func_800466D0(&play2PanelSub->unk_A7C[i]);
    }

    play2PanelSub->unk_A7C[1].unk_40[0] = -play2PanelSub->unk_A7C[1].unk_40[0];
    play2PanelSub->unk_A7C[1].unk_48[0] = -play2PanelSub->unk_A7C[1].unk_48[0];

    for (i = 0; i < ARRAY_COUNTU(play2PanelSub->unk_B9C); i++) {
        func_800479A8(&play2PanelSub->unk_B9C[i], watchMenuRef, 0, 0, _cursor_4921[i][0], _cursor_4921[i][1],
                      _cursor_4921[i][2], _cursor_4921[i][3]);
    }

    func_8004E270(play2PanelSub, -1, 0.0f);
}
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/main_menu", func_8004E4F4);
#endif

#if VERSION_US
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
#endif

#if VERSION_US
void menuPlay2PanelSub_draw(MenuPlay2PanelSub *play2PanelSub, Gfx **gfxP) {
    Gfx *gfx = *gfxP;
    void *arr[2 * 4];
    MenuItem *temp_s1;
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

    func_80046844(&play2PanelSub->unk_9EC, &gfx);
    gfxSetScissor(&gfx, 2, play2PanelSub->unk_010.unk_0C[0] + play2PanelSub->unk_9EC.unk_24[0] - 16.0f,
                  play2PanelSub->unk_010.unk_0C[1] + play2PanelSub->unk_9EC.unk_24[1], 0x68, 0x24);

    temp_s2 = _getTexSetup(play2PanelSub->watchMenuRef, 0xE);
    temp_fs0 = play2PanelSub->unk_9EC.unk_0C[0];
    play2PanelSub->unk_9EC.unk_0C[0] += (play2PanelSub->unk_00C * 0x48);

    temp_s1 = &play2PanelSub->unk_9EC;
    for (i = 0; i < 4; i++) {
        func_80046F58(temp_s1, &gfx, temp_s2, 0, 0xA,
                      WrapI(0, 0xA, (play2PanelSub->unk_940.unk_0C + play2PanelSub->unk_00C + i) - 1));
        temp_s1->unk_0C[0] += 72.0f;
    }

    gDPSetScissor(gfx++, G_SC_NON_INTERLACE, 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1);
    temp_s1->unk_0C[0] = temp_fs0;
    gSPDisplayList(gfx++, fade_normal_texture_init_dl);

    temp_s2 = _getTexSetup(play2PanelSub->watchMenuRef, 0x10);

    var_s4 = 0;
    for (i = 0; i < ARRAY_COUNTU(play2PanelSub->unk_A7C); i++) {
        var_s4 += menuItem_drawTex(&play2PanelSub->unk_A7C[i], &gfx, temp_s2, var_s4);
    }

    *gfxP = gfx;
}
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", func_80050B48_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", _panel_3859);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", _pos_4015);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", _y_4020);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", RO_800C6304_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", _panel_4108);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", RO_800C637C_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", RO_800C638C_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", RO_800C639C_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", RO_800C63A0_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", RO_800C63AC_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", RO_800C63B0_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", RO_800C63BC_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", RO_800C63C0_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", RO_800C63CC_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", RO_800C63D0_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", RO_800C63DC_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", RO_800C63E0_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", RO_800C63EC_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", RO_800C63F0_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", RO_800C63FC_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", RO_800C6404_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", func_80050BA0_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", func_800510A8_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", func_800510F8_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", func_800511F0_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", func_80051440_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", func_800517C0_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", func_80051E48_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", func_80051E9C_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", func_80051EEC_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", func_80052178_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", func_80052420_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", func_800525F8_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", RO_800C64BC_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", RO_800C64F8_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", RO_800C6538_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", RO_800C6540_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", RO_800C6548_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", RO_800C655C_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", RO_800C656C_cn);
#endif

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
        if ((var_s1 == _loopTbl_5287[i]) && msgWnd_isEnd(&menuMain->unk_2308)) {
            menuMain->unk_2304 = NULL;
        }
    }

    if (var_s1 != menuMain->unk_2304) {
        msgWnd_clear(&menuMain->unk_2308);
        if (var_s1 != NULL) {
            msgWnd_addStr(&menuMain->unk_2308, var_s1);
            ret = true;
        }
        menuMain->unk_2304 = var_s1;
    }

    return ret;
}

#if VERSION_US || VERSION_CN
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
}
#endif

#if VERSION_US || VERSION_CN
void menuMain_init(MenuMain *menuMain, struct_watchMenu *watchMenuRef, struct_watchMenu_unk_02470 **arg2) {
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

    msgWnd_init(&menuMain->unk_2308, (void **)arg2, 0xC, 4, 0x9C, 0x22);
    menuMain->unk_2308.unk_1C = 0;

#if VERSION_CN
    menuMain->unk_2308.unk_48 = 0xE;
#else
    menuMain->unk_2308.unk_48 = 0xD;
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

    menuMes_init(&menuMain->unk_31E4, watchMenuRef, arg2, 0x11, 2, 0x40, 0xA6);
}
#endif

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", RO_800B0310);
#endif
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", RO_800B0320);
#endif
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", RO_800B0338);
#endif
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", RO_800B0350);
#endif
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", RO_800B035C);
#endif
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", RO_800B0360);
#endif
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", RO_800B0364);
#endif
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", RO_800B0378);
#endif
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", RO_800B037C);
#endif
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", RO_800B0380);
#endif
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", RO_800B039C);
#endif
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", RO_800B03A0);
#endif
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", RO_800B03A4);
#endif
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", RO_800B03C0);
#endif
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", RO_800B03C4);
#endif
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", RO_800B03D8);
#endif
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", RO_800B03EC);
#endif
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", RO_800B03F8);
#endif
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", RO_800B0404);
#endif
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", RO_800B0410);
#endif
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", RO_800B041C);
#endif
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", RO_800B0424);
#endif
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", RO_800B043C);
#endif
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", RO_800B0448);
#endif

#if VERSION_US || VERSION_CN
void func_8004F2D8(MenuMain *menuMain) {
    u16 keyTrg = _getKeyTrg(menuMain->watchMenuRef, 0);

    if ((keyTrg & B_BUTTON) && (menuMain->mode != MAINMENUMODE_MENUMAIN_0)) {
        _setFadeDir(menuMain->watchMenuRef, -1);
        _setNextMain(menuMain->watchMenuRef, MAIN_NO_6);
        dm_snd_play(SND_INDEX_68);
    }
}
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/main_menu", func_8004F33C);
#endif

const char *mes_5577[] = {
    _mesNoCont2,
    _mesNoCont3,
    _mesNoCont4,
};

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", func_800532BC_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", RO_800C69A0_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", RO_800C69B0_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", RO_800C69C8_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", RO_800C69E0_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", RO_800C69EC_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", RO_800C69F0_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", RO_800C69F4_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", RO_800C6A08_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", RO_800C6A0C_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", RO_800C6A10_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", RO_800C6A2C_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", RO_800C6A30_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", RO_800C6A34_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", RO_800C6A50_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", RO_800C6A54_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", RO_800C6A68_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", RO_800C6A7C_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", RO_800C6A88_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", RO_800C6A94_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", RO_800C6AA0_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", RO_800C6AAC_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", RO_800C6AB4_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", RO_800C6ACC_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", RO_800C6AD8_cn);
#endif

#if VERSION_US
#if 0
? func_800490B8(MenuYN *, s32);                     /* extern */
s32 func_80049224(MenuYN *, ?, s32);                /* extern */
? func_80049578(MenuMes *, s32);                    /* extern */
? func_8004970C(MenuMes *, s8 *, s32);              /* extern */
s32 func_8004B43C(MenuCont *, ?, s32);              /* extern */
s32 func_8004B8CC(MenuMainPanel *, ?, s32);         /* extern */
s32 func_8004C1F0(MenuNameSelPanel *);              /* extern */
s32 func_8004C974(MenuNameOpPanel *, ?, s32);       /* extern */
s32 func_8004CE48(MenuSndSelPanel *, ?, s32);       /* extern */
? func_80059B5C(struct_watchMenu *);                /* extern */
? func_80059BC8(struct_watchMenu *);                /* extern */
? func_80059C34(struct_watchMenu *);                /* extern */
extern ? RO_800B0310;
extern ? RO_800B0320;
extern ? RO_800B0338;
extern ? RO_800B0350;
extern ? RO_800B035C;
extern ? RO_800B0360;
extern ? RO_800B0364;
extern ? RO_800B0378;
extern ? RO_800B037C;
extern ? RO_800B0380;
extern ? RO_800B039C;
extern ? RO_800B03A0;
extern ? RO_800B03A4;
extern ? RO_800B03C0;
extern ? RO_800B03C4;
extern ? RO_800B03D8;
extern ? RO_800B03EC;
extern ? RO_800B03F8;
extern ? RO_800B0404;
extern ? RO_800B0410;
extern ? RO_800B041C;
extern ? RO_800B0424;
extern ? RO_800B043C;
extern ? RO_800B0448;
extern s8 _mesNoCont2;

void menuMain_input(MenuMain *menuMain) {
    s32 sp10;
    MenuMainPanel *sp1C;
    s32 sp24;
    s32 sp2C;
    s32 sp34;
    s32 sp3C;
    s32 sp44;
    ? *var_a1_4;
    MenuCont *temp_s0_2;
    MenuMain *var_a0_3;
    MenuMain *var_v1;
    MenuNameSelPanel *temp_s0_3;
    enum MainMenuMode temp_a0;
    enum MainMenuMode temp_a1;
    enum MainMenuMode temp_s0;
    enum MainMenuMode temp_v0;
    enum MainMenuMode temp_v0_10;
    enum MainMenuMode temp_v0_2;
    enum MainMenuMode temp_v0_5;
    enum MainMenuMode temp_v0_8;
    enum MainMenuMode temp_v0_9;
    enum MainMenuMode temp_v1;
    enum MainMenuMode temp_v1_3;
    enum MainMenuMode temp_v1_4;
    enum MainMenuMode temp_v1_6;
    enum MainMenuMode temp_v1_7;
    enum MainMenuMode temp_v1_8;
    enum MainMenuMode var_a1_3;
    enum MainMenuMode var_s5;
    enum MainMenuMode var_v0_3;
    enum MainMenuMode var_v0_4;
    enum MainMenuMode var_v0_5;
    enum MainMenuMode var_v1_3;
    enum SndIndex var_s4;
    f32 temp_fs0;
    f32 temp_fs0_2;
    s32 *var_a0;
    s32 *var_a1_5;
    s32 temp_v0_11;
    s32 temp_v0_12;
    s32 temp_v0_14;
    s32 temp_v0_15;
    s32 temp_v0_17;
    s32 temp_v0_4;
    s32 temp_v0_7;
    s32 temp_v1_2;
    s32 temp_v1_5;
    s32 temp_v1_9;
    s32 var_a1;
    s32 var_a2;
    s32 var_a2_10;
    s32 var_a2_2;
    s32 var_a2_3;
    s32 var_a2_4;
    s32 var_a2_5;
    s32 var_a2_6;
    s32 var_a2_7;
    s32 var_fp;
    s32 var_s0;
    s32 var_s3;
    s32 var_s6;
    s32 var_s7;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v1_2;
    s32 var_v1_4;
    s8 temp_v0_16;
    u16 temp_s2;
    u32 var_a2_8;
    u32 var_a2_9;
    u8 *var_a0_2;
    u8 *var_a1_2;
    u8 temp_v0_13;
    u8 temp_v0_3;
    u8 temp_v0_6;

    var_s5 = saved_reg_s5;
    sp1C = &menuMain->unk_003C[menuMain->unk_2300];
    temp_s2 = _getKeyTrg(menuMain->watchMenuRef, 0);
    if (_getMode(menuMain->watchMenuRef) == MAINMENUMODE_MENUMAIN_0) {
        menuTitle_setTitle(menuMain->watchMenuRef, menuMain->mode);
    }
    temp_v0 = menuMain->mode;
    switch (temp_v0) {
        case MAINMENUMODE_66:
        case MAINMENUMODE_69:
            var_a2 = 1;
            break;
        case MAINMENUMODE_65:
        case MAINMENUMODE_68:
            if (0 == 0) {
                var_v0 = func_80049224(&menuMain->unk_2B6C, 0, 0);
block_20:
                var_a2 = 0;
                if (var_v0 != 0) {
                    goto block_21;
                }
            } else {
block_21:
                var_a2 = 1;
            }
            break;
        case MAINMENUMODE_71:
            if (0 == 0) {
                var_v0 = func_8004CE48(&menuMain->unk_1C64, 0, 0);
                goto block_20;
            }
            goto block_21;
        default:
            if ((0 != 0) || (var_a2_2 = 0, (func_8004B8CC(sp1C, 0, 0) != 0))) {
                var_a2_2 = 1;
            }
            if ((var_a2_2 != 0) || (var_a2_3 = 0, (func_8004C1F0(&menuMain->unk_0D2C) != 0))) {
                var_a2_3 = 1;
            }
            if ((var_a2_3 != 0) || (var_a2_4 = 0, (func_8004B43C(&menuMain->unk_2658, 0, var_a2_3) != 0))) {
                var_a2_4 = 1;
            }
            if (var_a2_4 == 0) {
                var_v0 = func_8004C974(&menuMain->unk_17B4, 0, var_a2_4);
                goto block_20;
            }
            goto block_21;
    }
    var_s7 = 0;
    if (var_a2 != 0) {
        var_fp = 0;
        var_s6 = 0;
        sp44 = 0;
        sp24 = 0;
        sp3C = 0;
        sp34 = 0;
        sp2C = 0;
        temp_v0_2 = menuMain->mode;
        var_s3 = 0;
        var_s4 = SND_INDEX_INVALID;
        switch (temp_v0_2) {
            case MAINMENUMODE_2:
            case MAINMENUMODE_5:
            case MAINMENUMODE_8:
            case MAINMENUMODE_11:
            case MAINMENUMODE_14:
            case MAINMENUMODE_18:
            case MAINMENUMODE_23:
            case MAINMENUMODE_27:
            case MAINMENUMODE_31:
            case MAINMENUMODE_60:
            case MAINMENUMODE_61:
            case MAINMENUMODE_66:
            case MAINMENUMODE_69:
                var_s0 = 0;
                break;
            case MAINMENUMODE_62:
                var_s0 = menuMain->unk_17B4.unk_008;
                break;
            case MAINMENUMODE_71:
                var_s0 = menuMain->unk_1C64.unk_004;
                break;
            case MAINMENUMODE_65:
            case MAINMENUMODE_68:
                var_s0 = menuMain->unk_2B6C.unk_004;
                break;
            default:
                var_s0 = sp1C->unk_00C;
                menuMain->unk_000C[menuMain->unk_0008] = var_s0;
                break;
        }
        temp_v1 = menuMain->mode;
        switch (temp_v1) {
            case MAINMENUMODE_MENUMAIN_0:
                if (temp_s2 & 0x9000) {
                    temp_s0 = *(&RO_800B0310 + (var_s0 * 4));
                    if ((temp_s0 == MAINMENUMODE_22) && (temp_v0_3 = joyResponseCheck(), evs_playmax = temp_v0_3, (((u32) (temp_v0_3 & 0xFF) < 2U) != 0))) {
                        func_8004970C(&menuMain->unk_31E4, &_mesNoCont2);
                        var_s7 = 1;
                        var_s4 = SND_INDEX_71;
                    } else {
                        var_s3 = 1;
                        var_s4 = SND_INDEX_62;
                        menuMain->mode = temp_s0;
                        temp_v0_4 = menuMain->unk_0008 + 1;
                        menuMain->unk_0008 = temp_v0_4;
                        menuMain->unk_000C[temp_v0_4] = 0;
                    }
                    var_s7 -= var_s7 == 0;
                } else if (!(temp_s2 & 0x4000)) {
                    var_v0_2 = temp_s2 != 0;
block_87:
                    var_s7 = 0 - var_v0_2;
                } else if (!(menuMain->unk_31E4.unk_004.unk_68 < 0.0f)) {
                    var_s7 = -1;
                } else {
                    _setFadeDir(menuMain->watchMenuRef, 1);
                    var_s4 = SND_INDEX_68;
                    _setNextMain(menuMain->watchMenuRef, MAIN_NO_3);
                    var_s7 = -1;
                }
                break;
            case MAINMENUMODE_1:
                temp_v1_2 = var_s0 * 4;
                menuMain->unk_0030 = ENUM_EVS_GAMEMODE_1;
                menuMain->unk_002C = *(&RO_800B0320 + temp_v1_2);
                if (temp_s2 & 0x9000) {
                    temp_v1_3 = *(&RO_800B0338 + temp_v1_2);
                    menuMain->unk_0030 = -1;
                    menuMain->mode = temp_v1_3;
                    switch (temp_v1_3) {            /* switch 8; irregular */
                        case MAINMENUMODE_18:
                            evs_gamemode = ENUM_EVS_GAMEMODE_1;
                            break;
                        case MAINMENUMODE_8:
                            evs_gamemode = ENUM_EVS_GAMEMODE_2;
                            break;
                        case MAINMENUMODE_11:
                            evs_gamemode = ENUM_EVS_GAMEMODE_3;
                            break;
                        default:
                            evs_gamemode = ENUM_EVS_GAMEMODE_0;
                            break;
                    }
                    temp_v0_5 = menuMain->mode;
                    switch (temp_v0_5) {
                        case MAINMENUMODE_2:
                            evs_playcnt = 2;
                            evs_story_flg = 1;
                            evs_gamesel = ENUM_EVS_GAMESEL_3;
                            game_state_data->unk_04C = 0;
                            *(game_state_data + 0x410) = 1;
                            var_s6 = 1;
                            break;
                        case MAINMENUMODE_5:
                        case MAINMENUMODE_8:
                        case MAINMENUMODE_11:
                            evs_playcnt = 1;
                            evs_story_flg = 0;
                            evs_gamesel = ENUM_EVS_GAMESEL_0;
                            game_state_data->unk_04B = 0;
                            game_state_data->unk_04C = 0;
                            game_state_data->unk_090 = 0;
                            var_s6 = 1;
                            break;
                        case MAINMENUMODE_14:
                        case MAINMENUMODE_18:
                            var_s6 = 1;
                            evs_playcnt = 2;
                            evs_gamesel = ENUM_EVS_GAMESEL_3;
                            evs_story_flg = 0;
                            game_state_data->unk_04C = 0;
                            *(game_state_data + 0x410) = 1;
                            break;
                    }
                    var_s3 = 1;
                    var_s4 = SND_INDEX_62;
                } else if (temp_s2 & 0x4000) {
                    var_s3 = 1;
                    var_s4 = SND_INDEX_68;
                    menuMain->unk_0030 = -1;
                    menuMain->mode = MAINMENUMODE_MENUMAIN_0;
block_249:
                    menuMain->unk_0008 -= 1;
                }
                break;
            case MAINMENUMODE_22:
                menuMain->unk_002C = var_s0 + 6;
                menuMain->unk_0030 = ENUM_EVS_GAMEMODE_1;
                if (temp_s2 & 0x9000) {
                    var_s6 = 1;
                    var_s3 = 1;
                    menuMain->unk_0030 = -1;
                    menuMain->mode = *(&RO_800B0350 + (var_s0 * 4));
                    game_state_data->unk_04C = 0;
                    *(game_state_data + 0x410) = 0;
                    temp_v1_4 = menuMain->mode;
                    evs_playcnt = 2;
                    evs_story_flg = 0;
                    evs_gamesel = (enum enum_evs_gamesel) ENUM_EVS_GAMEMODE_1;
                    var_s4 = SND_INDEX_62;
                    switch (temp_v1_4) {            /* switch 9; irregular */
                        case MAINMENUMODE_23:
                            evs_gamemode = ENUM_EVS_GAMEMODE_0;
                            break;
                        case MAINMENUMODE_27:
                            evs_gamemode = ENUM_EVS_GAMEMODE_1;
                            break;
                        case MAINMENUMODE_31:
                            evs_gamemode = ENUM_EVS_GAMEMODE_3;
                            break;
                    }
                } else if (temp_s2 & 0x4000) {
                    var_s3 = 1;
                    var_s4 = SND_INDEX_68;
                    menuMain->unk_0030 = -1;
                    menuMain->mode = MAINMENUMODE_MENUMAIN_0;
                    goto block_249;
                }
                break;
            case MAINMENUMODE_35:
                menuMain->unk_002C = var_s0 + 0xC;
                menuMain->unk_0030 = ENUM_EVS_GAMEMODE_1;
                if (temp_s2 & 0x9000) {
                    temp_v0_6 = joyResponseCheck();
                    evs_playmax = temp_v0_6;
                    var_a2_5 = 0;
                    if (var_s0 < (temp_v0_6 & 0xFF)) {
                        var_a1 = 0;
                        menuMain->unk_0030 = -1;
                        evs_playcnt = 4;
                        evs_story_flg = 0;
                        evs_gamesel = ENUM_EVS_GAMESEL_2;
                        evs_gamemode = ENUM_EVS_GAMEMODE_0;
                        temp_v1_5 = menuMain->unk_0008 + 1;
                        menuMain->unk_0008 = temp_v1_5;
                        menuMain->mode = (enum MainMenuMode) *(&RO_800B035C + var_s0);
                        menuMain->unk_000C[temp_v1_5] = 0;
                        do {
                            (&game_state_data->unk_04C)[var_a1] = var_s0 < var_a2_5;
                            var_a2_5 += 1;
                            var_a1 += 0x3C4;
                        } while (var_a2_5 < 4);
                        var_s3 = 1;
                        var_s7 = -1;
                        var_s4 = SND_INDEX_62;
                    } else {
                        var_s7 = 1;
                        var_s4 = SND_INDEX_71;
                        func_8004970C(&menuMain->unk_31E4, (mes_5577 - 4)[var_s0], 0);
                    }
                } else {
                    if (!(temp_s2 & 0x4000)) {
                        var_v0_2 = temp_s2 != 0;
                        goto block_87;
                    }
                    if (menuMain->unk_31E4.unk_004.unk_68 < 0.0f) {
                        var_s3 = 1;
                        var_s4 = SND_INDEX_68;
                        menuMain->unk_0030 = -1;
                        menuMain->mode = MAINMENUMODE_MENUMAIN_0;
                        menuMain->unk_0008 -= 1;
                    }
                    var_s7 = -1;
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
                temp_v0_7 = menuMain->unk_0D2C.unk_008;
                if (temp_v0_7 > 0) {
                    var_a2_6 = 0;
                    if (menuMain->unk_0D2C.unk_004 > 0) {
                        var_v1 = menuMain;
                        do {
                            evs_select_name_no[var_a2_6] = (u8) var_v1->unk_0D2C.unk_014[0];
                            var_a2_6 += 1;
                            var_v1 += 4;
                        } while (var_a2_6 < menuMain->unk_0D2C.unk_004);
                    }
                    var_a2_7 = 0;
                    var_a0 = &sp10;
                    var_a1_2 = evs_select_name_no;
                    do {
                        *var_a0 = 0;
                        if (*var_a1_2 != 8) {
                            *var_a0 = 1;
                            if (!((u8) evs_mem_data[*var_a1_2].unk_00[0] & 1)) {
                                *var_a0 = 2;
                            }
                        }
                        var_a0 += 4;
                        var_a2_7 += 1;
                        var_a1_2 += 1;
                    } while (var_a2_7 < 2);
                    var_v1_2 = sp10;
                    if (var_v1_2 < sp14) {
                        var_v1_2 = sp14;
                    }
                    temp_v0_8 = menuMain->mode;
                    switch (temp_v0_8) {
                        case MAINMENUMODE_2:
                            var_s5 = *(&RO_800B0360 + (var_v1_2 * 8));
                            break;
                        case MAINMENUMODE_61:
                            var_s5 = *(&RO_800B0364 + (var_v1_2 * 8));
                            break;
                        case MAINMENUMODE_5:
                            var_s5 = *(&RO_800B0378 + (var_v1_2 * 0xC));
                            break;
                        case MAINMENUMODE_8:
                            var_s5 = *(&RO_800B037C + (var_v1_2 * 0xC));
                            break;
                        case MAINMENUMODE_11:
                            var_s5 = *(&RO_800B0380 + (var_v1_2 * 0xC));
                            break;
                        case MAINMENUMODE_23:
                            var_s5 = *(&RO_800B039C + (var_v1_2 * 0xC));
                            break;
                        case MAINMENUMODE_27:
                            var_s5 = *(&RO_800B03A0 + (var_v1_2 * 0xC));
                            break;
                        case MAINMENUMODE_31:
                            var_s5 = *(&RO_800B03A4 + (var_v1_2 * 0xC));
                            break;
                        case MAINMENUMODE_14:
                            var_s5 = *(&RO_800B03C0 + (var_v1_2 * 8));
                            break;
                        case MAINMENUMODE_18:
                            var_s5 = *(&RO_800B03C4 + (var_v1_2 * 8));
                            /* fallthrough */
                        default:
                            break;
                    }
                    if (var_s5 != MAINMENUMODE_46) {
                        if (var_s5 == MAINMENUMODE_62) {
                            var_s6 = -1;
                            var_s4 = SND_INDEX_62;
                            sp24 += 1;
                            menuMain->mode = var_s5;
                            menuMain->unk_17B4.unk_008 = 0;
                        } else {
                            var_a1_3 = var_s5;
                            var_s3 = 1;
                            sp2C -= 1;
                            var_s6 = -1;
block_170:
                            var_s4 = SND_INDEX_62;
                            sp34 -= 1;
                            _setMode(menuMain->watchMenuRef, var_a1_3);
                        }
                    } else {
                        menuMain->mode = var_s5;
                        goto block_127;
                    }
                } else if (temp_v0_7 < 0) {
                    temp_v0_9 = menuMain->mode;
                    switch (temp_v0_9) {
                        case MAINMENUMODE_2:
                        case MAINMENUMODE_5:
                        case MAINMENUMODE_8:
                        case MAINMENUMODE_11:
                        case MAINMENUMODE_14:
                        case MAINMENUMODE_18:
                            var_v0_3 = MAINMENUMODE_1;
block_126:
                            menuMain->mode = var_v0_3;
                            break;
                        case MAINMENUMODE_23:
                        case MAINMENUMODE_27:
                        case MAINMENUMODE_31:
                            var_v0_3 = MAINMENUMODE_22;
                            goto block_126;
                        case MAINMENUMODE_61:
                            var_v0_3 = MAINMENUMODE_46;
                            goto block_126;
                    }
block_127:
                    var_s3 = 1;
                    var_s6 = -1;
                    var_s4 = SND_INDEX_68;
                }
                break;
            case MAINMENUMODE_46:
                if (temp_s2 & 0x9000) {
                    temp_v0_10 = *(&RO_800B03D8 + (var_s0 * 4));
                    menuMain->mode = temp_v0_10;
                    switch (temp_v0_10) {
                        case MAINMENUMODE_61:
                            var_s3 = 1;
                            var_s6 = 1;
                            var_s4 = SND_INDEX_62;
                            break;
                        case MAINMENUMODE_47:
                        case MAINMENUMODE_59:
                        case MAINMENUMODE_67:
                        case MAINMENUMODE_70:
                            var_s3 = 1;
                            var_s4 = SND_INDEX_62;
                            temp_v0_11 = menuMain->unk_0008 + 1;
                            menuMain->unk_0008 = temp_v0_11;
                            menuMain->unk_000C[temp_v0_11] = 0;
                            break;
                    }
                    temp_v1_6 = menuMain->mode;
                    switch (temp_v1_6) {            /* switch 10; irregular */
                        case MAINMENUMODE_47:       /* switch 10 */
                            dm_seq_play_fade(SEQ_INDEX_13, 0x14);
                            break;
                        case MAINMENUMODE_72:       /* switch 10 */
                        case MAINMENUMODE_72:       /* switch 11 */
                            menuMain->unk_000C[menuMain->unk_0008] = 3 - evs_vs_count;
                            break;
                    }
                } else if (temp_s2 & 0x4000) {
                    var_s3 = 1;
                    var_s4 = SND_INDEX_68;
                    menuMain->mode = MAINMENUMODE_MENUMAIN_0;
block_185:
                    menuMain->unk_0008 -= 1;
                }
                break;
            case MAINMENUMODE_70:
                if (temp_s2 & 0x9000) {
                    temp_v1_7 = *(&RO_800B03EC + (var_s0 * 4));
                    menuMain->mode = temp_v1_7;
                    if (temp_v1_7 == MAINMENUMODE_71) {
                        var_s3 = 1;
                        var_s4 = SND_INDEX_62;
                        sp44 += 1;
                        menuMain->unk_1C64.unk_004 = (u8) evs_stereo == 0;
                    } else if (((u32) temp_v1_7 >= 0x47U) && ((u32) temp_v1_7 < 0x4AU)) {
                        var_s3 = 1;
                        var_s4 = SND_INDEX_62;
                        temp_v0_12 = menuMain->unk_0008 + 1;
                        menuMain->unk_0008 = temp_v0_12;
                        menuMain->unk_000C[temp_v0_12] = 0;
                    }
                    temp_v1_8 = menuMain->mode;
                    switch (temp_v1_8) {            /* switch 11; irregular */
                        case MAINMENUMODE_73:       /* switch 11 */
                            menuMain->unk_000C[menuMain->unk_0008] = (u8) evs_score_flag == 0;
                            break;
                    }
                } else if (temp_s2 & 0x4000) {
                    var_s3 = 1;
                    func_80059B5C(menuMain->watchMenuRef);
                    var_s4 = SND_INDEX_68;
block_247:
                    var_v0_4 = MAINMENUMODE_46;
block_248:
                    menuMain->mode = var_v0_4;
                    goto block_249;
                }
                break;
            case MAINMENUMODE_73:
                if (temp_s2 & 0x9000) {
                    var_s3 = 1;
                    evs_score_flag = var_s0 == 0;
                    var_s4 = SND_INDEX_62;
block_183:
                    var_v1_3 = MAINMENUMODE_70;
block_184:
                    menuMain->mode = var_v1_3;
                    goto block_185;
                }
                var_v0_4 = MAINMENUMODE_70;
                if (temp_s2 & 0x4000) {
                    var_s3 = 1;
                    var_s4 = SND_INDEX_68;
                    goto block_248;
                }
                break;
            case MAINMENUMODE_36:
            case MAINMENUMODE_37:
            case MAINMENUMODE_38:
            case MAINMENUMODE_39:
                menuMain->unk_002C = var_s0 + 9;
                menuMain->unk_0030 = ENUM_EVS_GAMEMODE_1;
                var_a2_8 = 0;
                if (temp_s2 & 0x9000) {
                    var_a0_2 = (var_s0 * 4) + &RO_800B03F8;
                    var_v1_4 = 0;
                    do {
                        temp_v0_13 = *var_a0_2;
                        var_a0_2 += 1;
                        var_a2_8 += 1;
                        (&game_state_data->unk_04F)[var_v1_4] = temp_v0_13;
                        var_v1_4 += 0x3C4;
                    } while (var_a2_8 < 4U);
                    temp_v0_14 = var_s0 * 4;
                    sp2C -= 1;
                    var_s3 = 1;
                    sp34 -= 1;
                    var_s4 = SND_INDEX_62;
                    evs_gamemode = *(&RO_800B0410 + temp_v0_14);
                    menuMain->unk_0030 = -1;
                    _setMode(menuMain->watchMenuRef, *(&RO_800B0404 + temp_v0_14));
                } else if (temp_s2 & 0x4000) {
                    var_s3 = 1;
                    var_s4 = SND_INDEX_68;
                    menuMain->unk_0030 = -1;
                    var_v1_3 = MAINMENUMODE_35;
                    goto block_184;
                }
                break;
            case MAINMENUMODE_47:
                if (temp_s2 & 0x9000) {
                    var_s3 = 1;
                    var_s4 = SND_INDEX_62;
                    temp_v0_15 = menuMain->unk_0008 + 1;
                    menuMain->unk_0008 = temp_v0_15;
                    menuMain->mode = *(&RO_800B041C + (var_s0 * 4));
                    menuMain->unk_000C[temp_v0_15] = 0;
                } else if (temp_s2 & 0x4000) {
                    var_s3 = 1;
                    var_s4 = SND_INDEX_68;
                    menuMain->mode = MAINMENUMODE_46;
                    menuMain->unk_0008 -= 1;
                    dm_seq_play_fade(SEQ_INDEX_13, 0x14);
                }
                break;
            case MAINMENUMODE_48:
            case MAINMENUMODE_MENURANK_55:
                if (temp_s2 & 0x9000) {
                    var_a1_4 = &RO_800B043C;
                    if (menuMain->mode == MAINMENUMODE_48) {
                        var_a1_4 = &RO_800B0424;
                    }
                    var_a1_3 = *((var_s0 * 4) + var_a1_4);
                    sp2C -= 1;
                    var_s3 = 1;
                    goto block_170;
                }
                var_v0_4 = MAINMENUMODE_47;
                if (temp_s2 & 0x4000) {
                    var_s3 = 1;
                    var_s4 = SND_INDEX_68;
                    goto block_248;
                }
                break;
            case MAINMENUMODE_59:
                if (!(temp_s2 & 0x9000)) {
                    if (temp_s2 & 0x4000) {
                        var_s3 = 1;
                        var_s4 = SND_INDEX_68;
                        goto block_247;
                    }
                } else if (var_s0 == 0) {
                    menuMain->mode = MAINMENUMODE_60;
                    sp2C -= 1;
                    var_s3 = 1;
                    var_s4 = SND_INDEX_62;
                    sp3C += 1;
                } else {
                    _setFadeDir(menuMain->watchMenuRef, 1);
                    var_s4 = SND_INDEX_62;
                    _setNextMain(menuMain->watchMenuRef, MAIN_NO_4);
                    evs_manual_no = var_s0 - 1;
                }
                break;
            case MAINMENUMODE_72:
                if (temp_s2 & 0x9000) {
                    var_s3 = 1;
                    var_s4 = SND_INDEX_62;
                    sp44 -= 1;
                    evs_vs_count = 3 - var_s0;
                    goto block_183;
                }
                var_v0_4 = MAINMENUMODE_70;
                if (temp_s2 & 0x4000) {
                    var_s3 = 1;
                    var_s4 = SND_INDEX_68;
                    goto block_248;
                }
                break;
            case MAINMENUMODE_60:
                menuCont_setFade(&menuMain->unk_2658, 1, menuMain->unk_2658.unk_3F4[0].unk_64);
                if (temp_s2 & 0x4000) {
                    menuMain->mode = MAINMENUMODE_59;
                    sp2C += 1;
                    var_s3 = 1;
                    var_s4 = SND_INDEX_68;
                    sp3C -= 1;
                }
                break;
            case MAINMENUMODE_62:
                if (temp_s2 & 0x9000) {
                    temp_a0 = *(&RO_800B0448 + (var_s0 * 4));
                    switch (temp_a0) {              /* switch 12; irregular */
                        case MAINMENUMODE_MENUNMENT_64: /* switch 12 */
                            sp2C -= 1;
                            sp34 -= 1;
                            var_s3 = 1;
                            var_s4 = SND_INDEX_62;
                            sp24 -= 1;
                            _setMode(menuMain->watchMenuRef, MAINMENUMODE_MENUNMENT_64);
                            break;
                        case MAINMENUMODE_65:       /* switch 12 */
                            var_fp = 1;
                            var_s4 = SND_INDEX_62;
                            menuMain->mode = temp_a0;
                            menuMain->unk_2B6C.unk_004 = 0;
                            menuMain->unk_17B4.unk_250.unk_01C.w &= 0xBFFFFFFF;
                            break;
                    }
                } else if (temp_s2 & 0x4000) {
                    menuMain->mode = MAINMENUMODE_61;
                    var_s6 = 1;
                    var_s4 = SND_INDEX_68;
block_223:
                    sp24 -= 1;
                }
                break;
            case MAINMENUMODE_71:
                if (temp_s2 & 0x9000) {
                    switch (var_s0) {               /* switch 13; irregular */
                        default:                    /* switch 13 */
                            temp_v0_16 = var_s0 == 0;
                            if (var_s0 >= 0) {
                                evs_stereo = temp_v0_16;
                                dm_audio_set_stereo((enum bool) temp_v0_16);
                                var_s3 = 1;
                                var_s4 = SND_INDEX_62;
                                goto block_209;
                            }
                            break;
                        case 0x2:                   /* switch 13 */
                            dm_seq_play_fade(menuMain->unk_1C64.unk_008, 0x14);
                            menuMain->unk_0034 = menuMain->unk_1C64.unk_008;
                            break;
                        case 0x3:                   /* switch 13 */
                            dm_snd_play(menuMain->unk_1C64.unk_010);
                            break;
                    }
                } else if (temp_s2 & 0x4000) {
                    var_s3 = 1;
                    var_s4 = SND_INDEX_68;
block_209:
                    sp44 -= 1;
                    menuMain->mode = MAINMENUMODE_70;
                    if (menuMain->unk_0034 != 0xC) {
                        dm_seq_play_fade(0xC, 0x14); // SEQ_INDEX_12
                        menuMain->unk_0034 = 0xC;
                    }
                }
                break;
            case MAINMENUMODE_65:
                menuMain->unk_2B6C.unk_1B8.unk_01C.w |= 0x40000000;
                if (!(temp_s2 & 0x9000)) {
                    if (temp_s2 & 0x4000) {
                        var_fp = -1;
                        menuMain->mode = MAINMENUMODE_62;
                        menuMain->unk_17B4.unk_250.unk_01C.w |= 0x40000000;
                    }
                } else {
                    switch (var_s0) {               /* switch 14; irregular */
                        case 0x0:                   /* switch 14 */
                            menuMain->mode = MAINMENUMODE_61;
                            var_s6 = 1;
                            var_fp = -1;
                            var_s4 = SND_INDEX_68;
                            goto block_223;
                        case 0x1:                   /* switch 14 */
                            dm_init_save_mem(&evs_mem_data[*evs_select_name_no]);
                            var_s4 = SND_INDEX_70;
                            func_80059BC8(menuMain->watchMenuRef);
                            var_v0_5 = MAINMENUMODE_66;
block_242:
                            menuMain->mode = var_v0_5;
                            menuMain->unk_2B6C.unk_1B8.unk_01C.w &= 0xBFFFFFFF;
                            break;
                    }
                }
                break;
            case MAINMENUMODE_66:
                if (temp_s2 & 0xFF3F) {
                    menuMain->mode = MAINMENUMODE_61;
                    var_s6 = 1;
                    var_fp = -1;
                    var_s4 = SND_INDEX_62;
                    goto block_223;
                }
                break;
            case MAINMENUMODE_67:
                sp1C->unk_418.unk_01C.w |= 0x40000000;
                if (!(temp_s2 & 0x9000)) {
                    if (temp_s2 & 0x4000) {
                        var_s3 = 1;
                        var_s4 = SND_INDEX_68;
                        goto block_247;
                    }
                } else {
                    switch (var_s0) {               /* switch 15; irregular */
                        case 0x0:                   /* switch 15 */
                            var_s3 = 1;
                            var_s4 = SND_INDEX_68;
                            goto block_247;
                        case 0x1:                   /* switch 15 */
                            menuMain->mode = MAINMENUMODE_68;
                            menuMain->unk_2B6C.unk_004 = 0;
                            var_fp = 1;
                            var_s4 = SND_INDEX_62;
                            sp1C->unk_418.unk_01C.w &= 0xBFFFFFFF;
                            break;
                    }
                }
                break;
            case MAINMENUMODE_68:
                menuMain->unk_2B6C.unk_1B8.unk_01C.w |= 0x40000000;
                if (!(temp_s2 & 0x9000)) {
                    if (temp_s2 & 0x4000) {
                        menuMain->mode = MAINMENUMODE_67;
                        var_fp = -1;
                        var_s4 = SND_INDEX_68;
                    }
                } else {
                    switch (var_s0) {               /* switch 16; irregular */
                        case 0x0:                   /* switch 16 */
                            var_fp = -1;
                            var_s3 = 1;
                            var_s4 = SND_INDEX_68;
                            goto block_247;
                        case 0x1:                   /* switch 16 */
                            var_s4 = SND_INDEX_70;
                            func_80059C34(menuMain->watchMenuRef);
                            var_v0_5 = MAINMENUMODE_69;
                            goto block_242;
                    }
                }
                break;
            case MAINMENUMODE_69:
                if (temp_s2 & 0xFF3F) {
                    var_fp = -1;
                    var_s3 = 1;
                    var_s4 = SND_INDEX_62;
                    goto block_247;
                }
                break;
        }
        if (sp2C != 0) {
            func_8004655C(&menuMain->unk_2388, sp2C);
        }
        if (sp34 != 0) {
            func_8004655C(&menuMain->unk_2418, sp34);
        }
        if (var_fp != 0) {
            func_800490B8(&menuMain->unk_2B6C, var_fp);
        }
        if (var_s7 != 0) {
            func_80049578(&menuMain->unk_31E4, var_s7);
        }
        temp_s0_2 = &menuMain->unk_2658;
        if (sp3C < 0) {
            menuCont_setFade(temp_s0_2, -1, 1.0f);
            func_8004B2C8(temp_s0_2, -1, (s32) menuMain->unk_2658.unk_004.unk_14);
        }
        if (sp24 < 0) {
            func_8004C820(&menuMain->unk_17B4, -1, 1.0f);
        }
        if (var_s6 < 0) {
            func_8004BB14(&menuMain->unk_0D2C, -1, menuMain->unk_0D2C.unk_028.unk_14);
        }
        if (sp44 < 0) {
            func_8004CCD0(&menuMain->unk_1C64, -1, menuMain->unk_1C64.unk_014.unk_14);
        }
        if (var_s3 != 0) {
            func_8004B774(sp1C, -1, sp1C->unk_028.unk_14);
            temp_v1_9 = menuMain->unk_2300 ^ 1;
            sp1C = &menuMain->unk_003C[temp_v1_9];
            menuMain->unk_2300 = temp_v1_9;
        }
        temp_a1 = menuMain->mode;
        var_a2_9 = 0;
        if (temp_a1 != _menuMain_lastMode) {
            if (sp3C > 0) {
                func_8004B2C8(&menuMain->unk_2658, 1, (s32) menuMain->unk_2658.unk_004.unk_14);
                var_a2_9 = 0;
            } else if (sp24 > 0) {
                bcopy((*evs_select_name_no * 0xD0) + &evs_mem_data->unk_00[1], menuMain->unk_17B4.unk_00C, 4);
                func_8004C820(&menuMain->unk_17B4, 1, 0.0f);
                var_a2_9 = 0;
            } else if (sp44 > 0) {
                func_8004CCD0(&menuMain->unk_1C64, 1, menuMain->unk_1C64.unk_014.unk_14);
                var_a2_9 = 0;
            } else if (var_s6 > 0) {
                temp_fs0 = menuMain->unk_0D2C.unk_028.unk_14;
                var_a2_10 = 1;
                if (temp_a1 != MAINMENUMODE_27) {
                    if ((u32) temp_a1 < 0x1CU) {
                        if (temp_a1 != MAINMENUMODE_23) {

                        } else {
                            goto block_281;
                        }
                    } else if (temp_a1 == MAINMENUMODE_31) {
                        goto block_281;
                    }
                } else {
block_281:
                    var_a2_10 = 2;
                }
                temp_s0_3 = &menuMain->unk_0D2C;
                menuNameSelPanel_clear(temp_s0_3, menuMain->mode != MAINMENUMODE_61, var_a2_10);
                func_8004BB14(temp_s0_3, 1, temp_fs0);
                var_a2_9 = 0;
            } else {
                var_a2_9 = 0;
                if (var_s3 != 0) {
                    temp_fs0_2 = sp1C->unk_028.unk_14;
                    menuMain_initPanel(menuMain, temp_a1, menuMain->unk_2300, menuMain->unk_000C[menuMain->unk_0008]);
                    func_8004B774(sp1C, 1, temp_fs0_2);
                    var_a2_9 = 0;
                }
            }
        }
        var_a1_5 = _menuMain_lastSelect;
        var_a0_3 = menuMain;
        _menuMain_lastMode = menuMain->mode;
        _menuMain_lastDepth = menuMain->unk_0008;
        do {
            temp_v0_17 = var_a0_3->unk_000C[0];
            var_a0_3 += 4;
            var_a2_9 += 1;
            *var_a1_5 = temp_v0_17;
            var_a1_5 += 4;
        } while (var_a2_9 < 8U);
        if (var_s4 >= 0) {
            dm_snd_play(var_s4);
        }
    }
}
#else
INCLUDE_ASM("asm/us/nonmatchings/main_segment/main_menu", menuMain_input);
#endif
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", menuMain_input);
#endif

#if VERSION_US || VERSION_CN
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
    menuMain->unk_2308.unk_28 = item->unk_0C[0] + item->unk_30[0] * 6;
    menuMain->unk_2308.unk_2C = item->unk_0C[1] + item->unk_30[1] * 6;

    if (!menuMain_setMsgStr(menuMain, menuMain->mode, menuMain->unk_000C[menuMain->unk_0008])) {
        msgWnd_update(&menuMain->unk_2308);
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

    menuMain->unk_0038 = WrapF(0.0f, 1.0f, menuMain->unk_0038 + 0.0078125);

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
#endif

extern const s32 _pat_6137[];
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", _pat_6137);
#endif

#if VERSION_US
#if 0
//? RectAlphaTexTile(Gfx **, s32 *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32, f32, f32, f32); /* extern */
//? RectTexTile8(Gfx **, s32 *, u16, u16, void *, s32, s32, s32, s32, s32, s32, s32, f32, f32); /* extern */
//? RectTexTile4i(Gfx **, s32 *, u16, u16, s32, s32, s32, s32, s32, s32, s32, f32, f32); /* extern */

void menuMain_drawKaSaMaRu(MenuMain *menuMain, Gfx **gfxP) {
    f32 sp70;
    f32 sp74;
    f32 sp84;
    Gfx *sp90;
    s32 sp94;
    Gfx **sp9C;
    s32 spA4;
    Gfx *temp_v0;
    Gfx *temp_v1;
    Gfx *temp_v1_4;
    Gfx *temp_v1_5;
    Gfx *temp_v1_6;
    MenuItem *temp_s2;
    MenuItem *var_s2;
    Mtx *temp_s5;
    Mtx *temp_s5_2;
    Mtx *var_s5;
    TiTexData *var_s3;
    f32 *var_s0;
    f32 *var_s0_2;
    f32 temp_a2;
    f32 temp_fs2;
    s32 temp_lo;
    s32 temp_s1;
    s32 var_a1;
    s32 var_a3;
    s32 var_fp;
    s32 var_s1_2;
    s32 var_s1_3;
    u16 *temp_a1_2;
    u16 *temp_v0_3;
    u16 *temp_v0_4;
    u16 *temp_v1_7;
    u16 temp_a2_2;
    u16 temp_s6;
    u16 temp_v1_2;
    u16 temp_v1_3;
    u16 var_s6;
    u16 var_s7;
    u32 var_s1;
    void *temp_a0;
    void *temp_a1;
    void *temp_s3;
    void *temp_v0_2;

    var_fp = saved_reg_fp;
    sp9C = gfxP;
    var_s1 = 0;
    sp90 = *gfxP;
    temp_s5 = *_getMtxPtr(menuMain->watchMenuRef);
    var_s0 = &sp40[0];
    temp_fs2 = menuMain->unk_2538.unk_38 * 3.0f;
    sp94 = *_getVtxPtr(menuMain->watchMenuRef);
    do {
        temp_a2 = (f32) ((f64) menuMain->unk_0038 - ((f64) var_s1 * 0.125));
        var_s1 += 1;
        var_s0->unk_40 = (f32) (2.0 * ((f64) WrapF(0.0f, 1.0f, temp_a2) * 3.141592653589793));
        var_s0 += 4;
    } while (var_s1 < 3U);
    guOrtho(temp_s5, 0.0f, 320.0f, 240.0f, 0.0f, 1.0f, 10.0f, 1.0f);
    temp_v1 = sp90;
    temp_v1->words.w1 = (u32) temp_s5;
    temp_s5_2 = temp_s5 + 0x40;
    temp_v0 = temp_v1 + 8;
    sp90 = temp_v0;
    temp_v1->words.w0 = 0xDA380007;
    guTranslate(temp_s5_2, 0.0f, 0.0f, -5.0f);
    temp_v0->words.w0 = 0xDA380005;
    temp_v0->words.w1 = (u32) temp_s5_2;
    temp_v0->unk_8 = 0xD940F9FA;
    temp_v0->unk_C = 0;
    temp_v0->unk_10 = 0xE3000C00;
    temp_v0->unk_14 = 0;
    sp90 = temp_v0 + 8;
    sp90 = temp_v0 + 0x10;
    sp90 = temp_v0 + 0x18;
    guRotateRPYF((f32 (*)[4]) &sp40[0], 0.0f, 0.0f, sinf(sp80) * (1.0f - menuMain->unk_2538.unk_38) * 4.0f);
    temp_s1 = WrapI(0, 6, (s32) (menuMain->unk_0038 * 6.0f * 12.0f));
    temp_s3 = _getTexKasa(menuMain->watchMenuRef, *(_pat_6137 + ((temp_s1 & -(msgWnd_isSpeaking(&menuMain->unk_2308) != false)) * 4)) + 1);
    temp_v0_2 = _getTexKasa(menuMain->watchMenuRef, 0);
    temp_a1 = temp_v0_2->unk_4;
    temp_a0 = temp_s3->unk_4;
    temp_s2 = &menuMain->unk_2418;
    temp_v1_2 = temp_a0->unk_0;
    var_s6 = temp_a1->unk_0;
    var_s5 = temp_s5_2 + 0x40;
    if (temp_v1_2 < var_s6) {
        var_s6 = temp_v1_2;
    }
    temp_v1_3 = temp_a0->unk_2;
    var_s7 = temp_a1->unk_2;
    if (temp_v1_3 < var_s7) {
        var_s7 = temp_v1_3;
    }
    if (menuItem_outOfScreen(temp_s2, (s32) var_s6, (s32) var_s7) == false) {
        temp_v1_4 = sp90;
        sp90 = temp_v1_4 + 8;
        temp_v1_4->words.w0 = 0xDE000000;
        temp_v1_4->words.w1 = (u32) fade_alpha_texture_init_dl;
        func_80046844(temp_s2, &sp90);
        sp70 = menuMain->unk_2418.unk_0C[0];
        sp74 = menuMain->unk_2418.unk_0C[1] + (sinf(sp80) * temp_fs2);
        guMtxF2L((f32 (*)[4]) &sp40[0], var_s5);
        sp90->words.w0 = 0xDA380003;
        sp90->words.w1 = (u32) var_s5;
        sp90 += 8;
        var_s5 += 0x40;
        RectAlphaTexTile(&sp90, &sp94, (s32) var_s6, (s32) var_s7, temp_s3->unk_0->unk_4, (s32) temp_s3->unk_4->unk_0, temp_v0_2->unk_0->unk_4, (s32) temp_v0_2->unk_4->unk_0, 0, 0, (s32) var_s6, (s32) var_s7, 0.0f, 0.0f, (f32) var_s6, (f32) var_s7);
    }
    var_s2 = &menuMain->unk_25C8;
    if (menuMain->unk_002C < 0xC) {
        var_s3 = _getTexMain(menuMain->watchMenuRef, 0);
        var_s1_2 = menuMain->unk_002C;
        var_a3 = 0xC;
    } else {
        var_s3 = _getTexMain(menuMain->watchMenuRef, 8);
        var_a3 = 4;
        var_s1_2 = menuMain->unk_002C - 0xC;
    }
    temp_v0_3 = var_s3->unk_4;
    temp_s6 = temp_v0_3->unk_0;
    temp_a2_2 = temp_v0_3->unk_2;
    temp_lo = (s32) temp_a2_2 / var_a3;
    if (menuItem_outOfScreen(var_s2, (s32) temp_s6, (s32) temp_a2_2) == false) {
        temp_v1_5 = sp90;
        sp90 = temp_v1_5 + 8;
        temp_v1_5->words.w0 = 0xDE000000;
        temp_v1_5->words.w1 = (u32) fade_normal_texture_init_dl;
        func_80046844(var_s2, &sp90);
        sp70 = var_s2->unk_0C[0];
        sp74 = var_s2->unk_0C[1] + (sinf(sp88) * temp_fs2);
        guMtxF2L((f32 (*)[4]) &sp40[0], var_s5);
        sp90->words.w0 = 0xDA380003;
        sp90->words.w1 = (u32) var_s5;
        temp_a1_2 = var_s3->unk_4;
        sp90 += 8;
        var_s5 += 0x40;
        RectTexTile8(&sp90, &sp94, temp_a1_2->unk_0, temp_a1_2->unk_2, var_s3->unk_0->unk_0, var_s3->unk_0->unk_4 + (temp_s6 * temp_lo * var_s1_2), 0, 0, (s32) temp_s6, temp_lo, 0, 0, (f32) temp_s6 * var_s2->unk_30[0], (f32) temp_lo * var_s2->unk_30[1]);
    }
    var_s1_3 = 0;
    temp_v1_6 = sp90;
    var_s0_2 = &sp84;
    sp90 = temp_v1_6 + 8;
    temp_v1_6->words.w0 = 0xDE000000;
    temp_v1_6->words.w1 = (u32) fade_intensity_texture_init_dl;
    do {
        switch (var_s1_3) {                         /* irregular */
            case 0x1:
                var_s2 = &menuMain->unk_2538;
                var_a1 = 9;
block_21:
                var_fp = 0;
                spA4 = 0;
                var_s3 = _getTexMain(menuMain->watchMenuRef, var_a1);
                break;
            case 0x0:
                var_s2 = &menuMain->unk_24A8;
                var_a1 = 0xA;
                goto block_21;
        }
        temp_v0_4 = var_s3->unk_4;
        if (menuItem_outOfScreen(var_s2, (s32) temp_v0_4->unk_0, (s32) temp_v0_4->unk_2) != false) {
            var_s1_3 += 1;
        } else {
            func_80046844(var_s2, &sp90);
            sp70 = var_s2->unk_0C[0];
            var_s1_3 += 1;
            sp74 = var_s2->unk_0C[1] + (sinf(*var_s0_2) * temp_fs2);
            guMtxF2L((f32 (*)[4]) &sp40[0], var_s5);
            sp90->words.w0 = 0xDA380003;
            sp90->words.w1 = (u32) var_s5;
            temp_v1_7 = var_s3->unk_4;
            sp90 += 8;
            var_s5 += 0x40;
            RectTexTile4i(&sp90, &sp94, temp_v1_7->unk_0, temp_v1_7->unk_2, var_s3->unk_0->unk_4, 0, 0, (s32) var_s3->unk_4->unk_0, (s32) var_s3->unk_4->unk_2, 0, 0, (f32) (var_s3->unk_4->unk_0 + spA4) * var_s2->unk_30[0], (f32) (var_s3->unk_4->unk_2 + var_fp) * var_s2->unk_30[1]);
        }
        var_s0_2 += 4;
    } while (var_s1_3 < 2);
    *_getVtxPtr(menuMain->watchMenuRef) = sp94;
    *_getMtxPtr(menuMain->watchMenuRef) = var_s5;
    *sp9C = sp90;
}
#else
INCLUDE_ASM("asm/us/nonmatchings/main_segment/main_menu", menuMain_drawKaSaMaRu);
#endif
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", RO_800C6FC8_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", menuMain_drawKaSaMaRu);
#endif

#if VERSION_US || VERSION_CN
void menuMain_draw(MenuMain *menuMain, Gfx **gfxP) {
    Gfx *gfx = *gfxP;
    s32 i;

    gSPDisplayList(gfx++, fade_normal_texture_init_dl);

    menuItem_drawTex(&menuMain->unk_2388, &gfx, _getTexMain(menuMain->watchMenuRef, 6), 0);
    if (!menuItem_outOfScreen(&menuMain->unk_2388, menuMain->unk_2308.unk_3C * menuMain->unk_2308.unk_38,
                              menuMain->unk_2308.unk_48 * menuMain->unk_2308.unk_44)) {
        msgWnd_draw(&menuMain->unk_2308, &gfx);
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
#endif

extern const s32 _pos_6413[][9][2];

#if VERSION_US
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
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", _pos_6413);
#endif

#if VERSION_US || VERSION_CN
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
#endif

#if VERSION_US || VERSION_CN
void func_80051480(MenuStory *menuStory, s32 arg1, f32 arg2) {
    MenuItem *item = &menuStory->unk_0040;

    item->unk_14 = arg2;
    item->unk_18 = 0.05f;
    item->unk_1C[1] = item->unk_24[1] - 240.0f;
    func_8004655C(item, arg1);
}
#endif

#if VERSION_US || VERSION_CN
void func_800514C4(void *arg) {
    MenuStory *menuStory = arg;
    CharAnimeMode var_s0;

    for (var_s0 = CHARANIMEMODE_M; var_s0 < ARRAY_COUNTU(menuStory->unk_0038); var_s0++) {
        void *sp10 = menuStory->unk_0038[var_s0];

        animeState_load(&menuStory->unk_0280[var_s0], &sp10, var_s0);
    }

    menuStory->unk_0034 = true;
}
#endif

extern const s32 _posChar_6445[][2];
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", _posChar_6445);
#endif

extern const s32 _posBgCursor_6446[][2];
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", _posBgCursor_6446);
#endif

extern const s32 _cursor_6447[][4];
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", _cursor_6447);
#endif

#if VERSION_US || VERSION_CN
void menuStory_init(MenuStory *menuStory, struct_watchMenu *watchMenuRef, struct_watchMenu_unk_02470 **arg2) {
    struct_watchMenu_unk_02470 *var_fp = *arg2;
    struct_evs_mem_data *var_v1 = &evs_mem_data[evs_select_name_no[0]];
    struct_evs_mem_data_unk_B4 *temp_s4 = &var_v1->unk_B4;
    s32 i;
    CharAnimeMode var_s1_3;
    MenuItem *item;

    menuStory->watchMenuRef = watchMenuRef;

    for (i = 0; i < ARRAY_COUNTU(menuStory->unk_0004); i++) {
        menuStory->unk_0004[i][0] = var_v1->unk_08[i][0] + 1;
        menuStory->unk_0004[i][1] = var_v1->unk_08[i][1] + 1;
    }

    menuStory->unk_0024 = 0;
    menuStory->unk_0028[0] = temp_s4->unk_03;
    menuStory->unk_0034 = false;
    menuItem_init(&menuStory->unk_0040, 0x19, 0x2F);
    menuStory->unk_0028[0] = temp_s4->unk_03;
    menuItem_init(&menuStory->unk_00D0, 0x45, 0x12);

    for (i = 0; i < ARRAY_COUNTU(menuStory->unk_0160); i++) {
        menuItem_init(&menuStory->unk_0160[i], _posChar_6445[i][0], _posChar_6445[i][1]);
    }

    for (var_s1_3 = CHARANIMEMODE_M; var_s1_3 < ARRAY_COUNTU(menuStory->unk_0038); var_s1_3++) {
        size_t temp_v0_2;

        menuStory->unk_0038[var_s1_3] = ALIGN_PTR(var_fp);
        temp_v0_2 = animeState_getDataSize(var_s1_3);
        var_fp = menuStory->unk_0038[var_s1_3] + temp_v0_2;
    }

    func_80040B10(func_800514C4, menuStory);

    for (i = 0; i < ARRAY_COUNTU(menuStory->unk_0300); i++) {
        func_800479A8(&menuStory->unk_0300[i], watchMenuRef, 0, 0, _posChar_6445[i][0] - 0x18,
                      _posChar_6445[i][1] - 0x2C, 0x30, 0x2F);
    }

    menuStory->unk_0028[1] = temp_s4->unk_00;
    func_80049894(&menuStory->unk_07C0, watchMenuRef, 3, temp_s4->unk_00, 0x45, 0x3D);
    menuSpeedItem_init(&menuStory->unk_085C, watchMenuRef, 3, 0, temp_s4->unk_00, 0x7D, 0x39, 0x34);
    menuStory->unk_085C.unk_010 = temp_s4->unk_01 != 0;

    menuStory->unk_0028[2] = temp_s4->unk_02 + 1;
    func_8004A860(&menuStory->unk_0EC0, watchMenuRef, 1, 1, temp_s4->unk_02 + 1, 0x65, 0x5A);
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
    *arg2 = var_fp;
}
#endif

#if VERSION_US || VERSION_CN
void func_80051974(MenuStory *menuStory) {
    u16 keyTrg = _getKeyTrg(menuStory->watchMenuRef, 0);

    if (keyTrg & B_BUTTON) {
        _setFadeDir(menuStory->watchMenuRef, -1);
        _setNextMain(menuStory->watchMenuRef, MAIN_NO_6);
        dm_snd_play(SND_INDEX_68);
    }
}
#endif

s32 func_800519CC(MenuStory *menuStory);

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/main_menu", func_800519CC);
#endif

#if VERSION_CN
s32 func_800519CC(MenuStory *menuStory) {
    s32 var_v1;

    var_v1 = menuStory->unk_085C.unk_008;
    if (var_v1 == 2) {
        var_v1 = menuStory->unk_085C.unk_010 + 2;
    }
    return var_v1;
}
#endif

s32 func_800519EC(MenuStory *menuStory);

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/main_menu", func_800519EC);
#endif

#if VERSION_CN
s32 func_800519EC(MenuStory *menuStory) {
    return menuStory->unk_0004[func_800519CC(menuStory)][menuStory->unk_0028[0]];
}
#endif

#if VERSION_US || VERSION_CN
void menuStory_input(MenuStory *menuStory) {
    struct_evs_mem_data_unk_B4 *temp_s5 = &evs_mem_data[evs_select_name_no[0]].unk_B4;
    u16 temp_s2 = _getKeyRep(menuStory->watchMenuRef, 0);
    u16 temp_s4 = _getKeyTrg(menuStory->watchMenuRef, 0);
    SndIndex var_s3 = SND_INDEX_INVALID;
    bool var_s6 = false;
    s32 var_s0;
    s32 var_a1;
    long i;

    if (menuStory->unk_0040.unk_14 != 1.0) {
        return;
    }

    var_s0 = 0;
    if ((temp_s2 & 0x800) || (temp_s4 & 0x4000)) {
        var_s0--;
    }
    if ((temp_s2 & 0x400) || (temp_s4 & 0x9000)) {
        var_s0++;
    }

    var_a1 = CLAMP(menuStory->unk_0024 + var_s0, 0, 2U);

    if (var_a1 != menuStory->unk_0024) {
        var_s3 = SND_INDEX_64;
        menuStory->unk_0024 = var_a1;
    }

    if (temp_s4 & 0x2000) {
        if (menuStory->unk_0024 == 1) {
            if (menuStory->unk_085C.unk_008 == 2) {
                if (menuStory->unk_085C.unk_010 == 0) {
                    menuStory->unk_085C.unk_010 = 1;
                    var_s6 = true;
                } else {
                    menuStory->unk_085C.unk_010 = 0;
                    var_s3 = SND_INDEX_62;
                }
            }
        }
    }

    var_s0 = 0;
    if (temp_s2 & 0x200) {
        var_s0--;
    }
    if (temp_s2 & 0x100) {
        var_s0++;
    }

    switch (menuStory->unk_0024) {
        case 0x0:
            var_a1 = CLAMP(menuStory->unk_0028[menuStory->unk_0024] + var_s0, 0, 1);

            if (var_a1 != menuStory->unk_0028[menuStory->unk_0024]) {
                var_s3 = SND_INDEX_63;
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
                var_s3 = SND_INDEX_63;
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

    if (var_s3 < 0) {
        if ((temp_s4 & 0x9000) && (menuStory->unk_0024 == 2)) {
            _setFadeDir(menuStory->watchMenuRef, 1);
            _setNextMain(menuStory->watchMenuRef, MAIN_NO_2);

            temp_s5->unk_00 = menuStory->unk_085C.unk_008;
            temp_s5->unk_01 = menuStory->unk_085C.unk_010;
            temp_s5->unk_02 = menuStory->unk_0EC0.unk_0C - 1;
            temp_s5->unk_03 = menuStory->unk_0028[0];

            evs_story_level = func_800519CC(menuStory);

            evs_story_no = menuStory->unk_0EC0.unk_0C;

            i = (evs_story_no > 1) ? 1 : 0;
            game_state_data[0].unk_004 = i;
            evs_one_game_flg = i;

            story_proc_no = menuStory->unk_0EC0.unk_0C;
            if (menuStory->unk_0028[0] == 1) {
                story_proc_no += 0xC;
            }

            evs_high_score = 0xDD18;
            evs_game_time = 0;

            if (evs_story_level < 3) {
                for (i = 0; i < 9; i++) {
                    evs_high_score = MAX(evs_high_score, evs_mem_data[i].unk_28[evs_story_level].unk_0);
                }
            }

            var_s3 = SND_INDEX_62;
        } else if ((temp_s4 & 0x4000) && (menuStory->unk_0024 == 0)) {
            _setMode(menuStory->watchMenuRef, MAINMENUMODE_MENUMAIN_0);
            func_80051480(menuStory, -1, 1.0f);
            var_s3 = SND_INDEX_68;
        }
    }

    if (var_s6) {
        dm_snd_play_strange_sound();
    } else if (var_s3 >= 0) {
        dm_snd_play(var_s3);
    }
}
#endif

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", RO_800B0A50);
#endif
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", RO_800B0A5C);
#endif
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", RO_800B0A6C);
#endif
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", RO_800B0A7C);
#endif
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", RO_800B0B0C);
#endif

extern const s32 _cursor_7325[][4];
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", _cursor_7325);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/main_menu", menuStory_update);
#endif

#if VERSION_CN
#if 0
void menuStory_update(MenuStory *menuStory) {
    s32 sp20;
    s32 sp24;
    AnimeState *var_s0_2;
    Color_RGBAf32 *var_a0_2;
    Color_RGBAf32 *var_a2_2;
    MenuCursor *var_s0_3;
    MenuCursor *var_s0_5;
    MenuItem *temp_s0;
    MenuItem *temp_s2;
    MenuItem *temp_s4;
    MenuItem *temp_s5;
    MenuItem *temp_s7;
    MenuItem *var_s0;
    MenuItem *var_s0_4;
    MenuItem *var_s2;
    enum bool temp_t1_2;
    f32 *var_v1_3;
    f32 temp_fv0;
    f32 temp_fv0_2;
    s32 *var_a0;
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_a2;
    s32 temp_s1;
    s32 temp_t0;
    s32 temp_t1;
    s32 var_a1;
    s32 var_s1_4;
    s32 var_s1_5;
    s32 var_v0;
    s32 var_v1_2;
    u32 var_s1;
    u32 var_s1_2;
    u32 var_s1_3;
    u32 var_s1_6;
    u32 var_s1_7;
    u32 var_s1_8;
    u32 var_t1;
    u32 var_t1_2;
    union _anonymous *var_a2;

    temp_s7 = _getRootItem(menuStory->watchMenuRef);
    menuStory->unk_07C0.unk_8 = func_800519CC(menuStory);
    menuStory->unk_0EC0.unk_0C = menuStory->unk_0028[2];

    temp_s4 = &menuStory->unk_0040;
    func_800464BC(temp_s4, temp_s7);

    for (var_s1 = 0; var_s1 < 2U; var_s1++) {
        var_a1 = -1;
        if (var_s1 == menuStory->unk_0028[0]) {
            var_a1 = 1;
        }
        func_80046614(&menuStory->unk_0160[var_s1], var_a1);
    }

    func_800464BC(&menuStory->unk_00D0, temp_s4);
    func_800464F8(menuStory->unk_0160, 2, temp_s4);

    for (var_s1_2 = 0; var_s1_2 < 2U; var_s1_2++) {
        var_s0_2 = &menuStory->unk_0280[var_s1_2];

        if (menuStory->unk_0034 != false) {
            animeState_update(var_s0_2);

            for (var_t1 = 0; var_t1 < 4U; var_t1++) {
                var_s0_2->primColor[var_t1] = menuStory->unk_0160[0].color.arr[var_t1] * 255.0f;
            }
        }
    }

    for (var_s1_3 = 0; var_s1_3 < 2U; var_s1_3++) {
        menuCursor_update(&menuStory->unk_0300[var_s1_3], temp_s4);
    }

    if (menuStory->unk_0024 != 1) {
        menuStory->unk_085C.unk_404.unk_020.unk_64 = 1.0f;
    }

    func_800498C4(&menuStory->unk_07C0, temp_s4);
    menuSpeedItem_update(&menuStory->unk_085C, temp_s4);
    menuNumber_update(&menuStory->unk_0EC0, temp_s4);
    temp_s5 = &menuStory->unk_0F6C;
    func_800464BC(temp_s5, temp_s4);
    var_s1_4 = 1;
    if (menuStory->unk_0028[2] >= 5) {
        var_s1_4 = -1;
    }

    // fake?
    temp_s0 = menuStory->unk_0FFC;
    func_80046614(temp_s0, var_s1_4);
    func_80046614(&menuStory->unk_0FFC[1], -var_s1_4);
    func_800464F8(temp_s0, 2, temp_s5);

    for (var_s1_5 = 0; var_s1_5 < 2U; var_s1_5++) {
        var_s0_4 = &menuStory->unk_123C[var_s1_5];
        var_s2 = &menuStory->unk_0FFC[var_s1_5];

        func_800513F0(menuStory->unk_0028[0], menuStory->unk_0028[2], var_s1_5, &sp20, &sp24);
        func_8004667C(var_s0_4, (f32) sp20, (f32) sp24);
        func_800464BC(var_s0_4, var_s2);
    }

    temp_s2 = menuStory->unk_111C;
    func_800464F8(temp_s2, 2, temp_s5);

    temp_s1 = func_800519EC(menuStory);
    if ((menuStory->unk_0028[2] >= 5) || ((temp_s1 < 5) != 0)) {
        temp_s2[1].color.v.a = 0;
    }
    if (menuStory->unk_0028[2] < 5) {
        temp_s2->color.v.a = 0.0f;
    }

    for (var_s1_6 = 0; var_s1_6 < 3U; var_s1_6++) {
        menuCursor_update(&menuStory->unk_135C[var_s1_6], temp_s4);
    }

    temp_t1 = menuStory->unk_0024 == 0;
    for (var_s1_7 = 0; var_s1_7 < 2U; var_s1_7++) {
        menuStory->unk_135C[0].unk_01C.b.unk_31 = temp_t1;
        menuStory->unk_0300[var_s1_7].unk_01C.b.unk_28 = temp_t1;
        temp_a0_2 = menuStory->unk_0028[0];
        var_v1_2 = 0;
        if (temp_t1 != 0) {
            var_v1_2 = var_s1_7 == temp_a0_2;
        }
        menuStory->unk_0300[temp_a0_2].unk_01C.b.unk_30 = var_v1_2;
    }

    temp_t0 = menuStory->unk_0024;
    temp_t1_2 = temp_t0 == 1;
    menuStory->unk_085C.unk_00C = temp_t1_2;
    menuStory->unk_135C[1].unk_01C.w = (menuStory->unk_135C[1].unk_01C.w & 0x7FFFFFFF) | (temp_t1_2 << 0x1F);
    menuStory->unk_085C.unk_404.unk_01C.w = (menuStory->unk_085C.unk_404.unk_01C.w & 0xBFFFFFFF) | (temp_t1_2 << 0x1E);
    menuStory->unk_135C[2].unk_01C.w = (menuStory->unk_135C[2].unk_01C.w & 0x7FFFFFFF) | ((temp_t0 == 2) << 0x1F);
    if (temp_t0 != 2) {
        for (var_s1_8 = 0; var_s1_8 < 2U; var_s1_8++) {
            for (var_t1_2 = 0; var_t1_2 < 3U; var_t1_2++) {
                temp_s2->color.arr[var_t1_2] = temp_s2->unk_6C[1][var_t1_2] * temp_s7->color.arr[var_t1_2];
            }
        }
    }
}
#else
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", menuStory_update);
#endif
#endif

#if VERSION_US
#if 0
? animeState_draw(void *, Gfx **, f32, f32, f32, f32);
? tiStretchTexTile(Gfx **, void *, ?, s32, s32, s32, s32, f32, f32, f32, f32);
? func_8004714C(MenuItem *, Gfx **, void *, void *, s32, s32, s32);
? func_80048634(MenuSpeedItem **, ?, Gfx **);
? func_8004A160(MenuSpeedItem **, ?, Gfx **);
s32 func_800519EC(MenuStory *);
void *func_80059D94(struct_watchMenu *, s32);
s32 menuItem_drawTex(MenuItem *, Gfx **, void *, s32);
s32 menuItem_outOfScreen(MenuItem *, s32, u16);
? menuNumber_draw(MenuNumber **, ?, Gfx **);
? menuSpeedAsk_draw(MenuNumber **, ?, Gfx **);
? menuSpeedItem_draw1(MenuSpeedAsk **, ?, Gfx **);
extern ? D_800B0A5C;
extern ? D_800B0A6C;
extern ? D_800B0A7C;
extern ? D_800B0B0C;
extern ? fade_shadow_texture_init_dl;

void menuStory_draw(MenuStory *menuStory, Gfx **gfxP) {
    MenuNumber *sp30;                               /* compiler-managed */
    Gfx *sp50;
    Gfx **sp5C;
    Gfx *temp_a0;
    Gfx *temp_v1;
    Gfx *temp_v1_2;
    Gfx *temp_v1_3;
    Gfx *temp_v1_4;
    Gfx *temp_v1_5;
    Gfx *temp_v1_6;
    Gfx *temp_v1_8;
    MenuItem *temp_s2;
    MenuItem *temp_s2_2;
    MenuSpeedItem **var_a0;
    f32 temp_fs0;
    f32 temp_fs1;
    f32 temp_fv1;
    s32 temp_a1;
    s32 temp_fv0;
    s32 temp_s3;
    s32 temp_v1_7;
    s32 var_s0;
    s32 var_s0_2;
    s32 var_s0_3;
    s32 var_s0_4;
    s32 var_s2;
    s32 var_s6;
    s32 var_s6_2;
    s32 var_s7;
    s32 var_s7_2;
    s32 var_v1;
    u16 temp_a1_2;
    u32 var_s4;
    u32 var_s4_2;
    u32 var_s4_3;
    u32 var_s4_4;
    u32 var_s4_5;
    u32 var_s4_6;
    u32 var_v0;
    void *temp_a2;
    void *temp_s0;
    void *temp_s1;
    void *temp_s1_2;
    void *temp_s1_3;
    void *temp_v0;

    sp5C = gfxP;
    var_s4 = 0;
    temp_v1 = *sp5C;
    var_s7 = 0x280;
    temp_v1->words.w0 = 0xDE000000;
    temp_v1->words.w1 = (u32) fade_normal_texture_init_dl;
    var_s6 = 0x160;
    sp50 = temp_v1 + 8;
    menuItem_drawTex(&menuStory->unk_0040, &sp50, func_80059D94(menuStory->watchMenuRef, 6), 0);
    do {
        temp_s2 = menuStory + var_s6;
        if (menuStory->unk_34 != 0) {
            temp_fs0 = temp_s2->unk_0C[0];
            temp_fs1 = temp_s2->unk_0C[1];
            temp_s2->unk_0C[0] = temp_fs0 - 26.0f;
            temp_s2->unk_0C[1] -= 48.0f;
            if (menuItem_outOfScreen(temp_s2, 0x40, 0x40U) == 0) {
                sp50->words.w0 = 0xFA000000;
                sp50->unk_8 = 0xDE000000U;
                sp50->unk_C = fade_intensity_texture_init_dl;
                temp_fv0 = (s32) (temp_s2->unk_64 * 255.0f);
                sp50->words.w1 = temp_fv0 | ~0xFF;
                temp_v1_2 = sp50 + 0x10;
                sp50 += 8;
                sp50 = temp_v1_2;
                temp_v0 = func_80059D94(menuStory->watchMenuRef, 0xC);
                tiStretchTexTile(&sp50, temp_v0, 0, 0, 0, (s32) temp_v0->unk_4->unk_0, (s32) temp_v0->unk_4->unk_2, temp_s2->unk_0C[0], temp_s2->unk_0C[1], (f32) temp_v0->unk_4->unk_0, (f32) temp_v0->unk_4->unk_2);
                temp_v1_3 = sp50;
                sp50 = temp_v1_3 + 8;
                sp50 = temp_v1_3 + 0x10;
                temp_s2->unk_0C[0] = temp_fs0 + 5.0f;
                temp_s2->unk_0C[1] = temp_fs1 + 2.0f;
                temp_v1_3->words.w0 = 0xDE000000;
                temp_v1_3->words.w1 = (u32) &fade_shadow_texture_init_dl;
                temp_v1_3->unk_8 = 0xFA000000;
                temp_v1_3->unk_C = (s32) ((temp_fv0 >> 1) & 0xFF);
                temp_s0 = menuStory + var_s7;
                animeState_draw(temp_s0, &sp50, temp_s2->unk_0C[0], temp_s2->unk_0C[1], 1.0f, 1.0f);
                temp_v1_4 = sp50;
                temp_s2->unk_0C[0] = temp_fs0;
                temp_s2->unk_0C[1] = temp_fs1;
                sp50 = temp_v1_4 + 8;
                temp_v1_4->words.w0 = 0xDE000000;
                temp_v1_4->words.w1 = (u32) fade_normal_texture_init_dl;
                func_80046844(temp_s2, &sp50);
                animeState_draw(temp_s0, &sp50, temp_s2->unk_0C[0], temp_s2->unk_0C[1], 1.0f, 1.0f);
            }
            temp_s2->unk_0C[0] = temp_fs0;
            temp_s2->unk_0C[1] = temp_fs1;
        }
        var_s7 += 0x40;
        var_s4 += 1;
        var_s6 += 0x90;
    } while (var_s4 < 2U);
    var_s4_2 = 0;
    temp_v1_5 = sp50;
    var_s0 = 0xFFC;
    sp50 = temp_v1_5 + 8;
    temp_v1_5->words.w0 = 0xDE000000;
    temp_v1_5->words.w1 = (u32) fade_normal_texture_init_dl;
    sp50 = temp_v1_5 + 0x10;
    temp_v1_5->unk_8 = 0xE200001C;
    temp_v1_5->unk_C = 0x504240;
    do {
        temp_a1 = *((var_s4_2 * 4) + ((menuStory->unk_28 * 8) + &D_800B0A5C));
        var_s4_2 += 1;
        menuItem_drawTex(menuStory + var_s0, &sp50, func_80059D94(menuStory->watchMenuRef, temp_a1), 0);
        var_s0 += 0x90;
    } while (var_s4_2 < 2U);
    var_s4_3 = 0;
    temp_v1_6 = sp50;
    var_s7_2 = 0;
    var_s6_2 = 0xFFC;
    sp50 = temp_v1_6 + 8;
    temp_v1_6->words.w0 = 0xDE000000;
    temp_v1_6->words.w1 = (u32) fade_intensity_texture_init_dl;
    do {
        temp_s2_2 = menuStory + var_s6_2;
        temp_s1 = func_80059D94(menuStory->watchMenuRef, *((var_s4_3 * 4) + ((menuStory->unk_28 * 8) + &D_800B0A6C)));
        temp_a2 = temp_s1->unk_4;
        temp_a1_2 = temp_a2->unk_0;
        var_s0_2 = ((func_800519EC(menuStory) * 4) + (var_s7_2 + ((menuStory->unk_28 * 0x48) + &D_800B0A7C)))->unk_-4;
        temp_v1_7 = temp_a1_2 - 1;
        if (temp_v1_7 < var_s0_2) {
            var_s0_2 = temp_v1_7;
        }
        temp_s3 = temp_a1_2 - var_s0_2;
        if (menuItem_outOfScreen(temp_s2_2, temp_s3, temp_a2->unk_2) == 0) {
            temp_a0 = sp50;
            temp_a0->words.w0 = 0xFA000000;
            temp_fv1 = temp_s2_2->color.v.a * 127.0f;
            sp50 = temp_a0 + 8;
            if (!(temp_fv1 >= 2.1474836e9f)) {
                var_v0 = (s32) temp_fv1 & 0xFF;
            } else {
                var_v0 = ((s32) (temp_fv1 - 2.1474836e9f) | 0x80000000) & 0xFF;
            }
            temp_a0->words.w1 = var_v0;
            tiStretchTexTile(&sp50, temp_s1, 0, var_s0_2, 0, temp_s3, (s32) temp_s1->unk_4->unk_2, temp_s2_2->unk_0C[0] + (f32) var_s0_2, temp_s2_2->unk_0C[1], (f32) temp_s3, (f32) temp_s1->unk_4->unk_2);
        }
        var_s7_2 += 0x24;
        var_s4_3 += 1;
        var_s6_2 += 0x90;
    } while (var_s4_3 < 2U);
    var_s4_4 = 0;
    temp_v1_8 = sp50;
    var_s0_3 = 0x123C;
    sp50 = temp_v1_8 + 8;
    temp_v1_8->words.w0 = 0xDE000000;
    temp_v1_8->words.w1 = (u32) fade_normal_texture_init_dl;
    sp50 = temp_v1_8 + 0x10;
    temp_v1_8->unk_8 = 0xE200001C;
    temp_v1_8->unk_C = 0x504240;
    do {
        var_s4_4 += 1;
        menuItem_drawTex(menuStory + var_s0_3, &sp50, func_80059D94(menuStory->watchMenuRef, *((menuStory->unk_28 * 4) + &D_800B0B0C)), 0);
        var_s0_3 += 0x90;
    } while (var_s4_4 < 2U);
    var_s2 = 0;
    var_s4_5 = 0;
    sp50->words.w0 = 0xE200001C;
    sp50->words.w1 = 0x0F0A4000;
    var_s0_4 = 0x111C;
    sp50 += 8;
    temp_s1_2 = func_80059D94(menuStory->watchMenuRef, 5);
    do {
        var_s2 += menuItem_drawTex(menuStory + var_s0_4, &sp50, temp_s1_2, var_s2);
        var_s4_5 += 1;
        var_s0_4 += 0x90;
    } while (var_s4_5 < 2U);
    sp30 = &menuStory->unk_0EC0;
    menuNumber_draw(&sp30, 1, &sp50);
    sp30 = &menuStory->unk_07C0;
    menuSpeedAsk_draw(&sp30, 1, &sp50);
    sp30 = &menuStory->unk_085C;
    menuSpeedItem_draw1(&sp30, 1, &sp50);
    sp50->words.w0 = 0xDE000000;
    sp50->words.w1 = (u32) fade_alpha_texture_init_dl;
    var_s4_6 = 0;
    sp50 += 8;
    temp_s1_3 = func_80059D94(menuStory->watchMenuRef, 1);
    func_8004714C(&menuStory->unk_00D0, &sp50, temp_s1_3, func_80059D94(menuStory->watchMenuRef, 0), 0, 2, menuStory->unk_28);
    var_a0 = &sp30;
    var_v1 = 0x135C;
    do {
        *var_a0 = menuStory + var_v1;
        var_a0 += 4;
        var_s4_6 += 1;
        var_v1 += 0x260;
    } while (var_s4_6 < 3U);
    func_80048634(&sp30, 3, &sp50);
    sp30 = &menuStory->unk_085C;
    func_8004A160(&sp30, 1, &sp50);
    *sp5C = sp50;
}
#else
INCLUDE_ASM("asm/us/nonmatchings/main_segment/main_menu", menuStory_draw);
#endif
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", menuStory_draw);
#endif

#if VERSION_US || VERSION_CN
void func_800529FC(MenuLvSel *menuLvSel, s32 arg1, f32 arg2) {
    MenuItem *item = &menuLvSel->unk_0008;

    item->unk_14 = arg2;
    item->unk_18 = 0.05f;
    item->unk_1C[1] = item->unk_24[1] - 240.0f;
    func_8004655C(item, arg1);
}
#endif

#if VERSION_US
#ifdef NON_MATCHING
void menuLvSel_init(MenuLvSel *menuLvSel, struct_watchMenu *watchMenuRef, struct_watchMenu_unk_02470 **arg2) {
    s32 temp = evs_select_name_no[0];
    struct_evs_mem_data *var_s0;
    struct_evs_mem_data_unk_B4 *temp_s5;
    struct_watchMenu_unk_02470 *temp_s7 = *arg2;
    s32 var_s2;

    menuLvSel->watchMenuRef = watchMenuRef;
    var_s0 = &evs_mem_data[temp];
    temp_s5 = &var_s0->unk_B4;
    menuLvSel->unk_0004 = _getMode(watchMenuRef);
    menuLvSel->unk_256C = 0;
    menuLvSel->unk_2570 = 0x14;

    for (var_s2 = 0; var_s2 < 3U; var_s2++) {
        menuLvSel->unk_2570 = MAX(menuLvSel->unk_2570, var_s0->unk_4C[var_s2].unk_4);
    }

    menuLvSel->unk_2570 = MIN(0x15, menuLvSel->unk_2570);

    menuItem_init(&menuLvSel->unk_0008, 0x19, 0x2F);
    menuItem_init(&menuLvSel->unk_0098[0], 0, 0);
    menuItem_init(&menuLvSel->unk_0098[1], 0, 0x5F);

    switch (menuLvSel->unk_0004) {
        case MAINMENUMODE_MENULVSEL_10:
            func_80049894(&menuLvSel->gameLvlIcon, watchMenuRef, 3, temp_s5->unk_08, 0x44, 9);
            menuSpeedItem_init(&menuLvSel->gameLvlSelector, watchMenuRef, 3, 0, temp_s5->unk_08, 0x82, 5, 0x2E);
            break;

        case MAINMENUMODE_MENULVSEL_13:
            func_80049894(&menuLvSel->gameLvlIcon, watchMenuRef, 3, temp_s5->unk_07, 0x44, 9);
            menuSpeedItem_init(&menuLvSel->gameLvlSelector, watchMenuRef, 3, 0, temp_s5->unk_07, 0x82, 5, 0x2E);
            break;

        case MAINMENUMODE_MENULVSEL_7:
            var_s2 = menuLvSel->unk_2570;
            if (var_s2 >= temp_s5->unk_04) {
                var_s2 = temp_s5->unk_04;
            }
            // var_s2 = MIN(menuLvSel->unk_2570, temp_s5->unk_04);
            func_8004A860(&menuLvSel->virusLvlNumber, watchMenuRef, 1, 2, var_s2, 0x59, 5);
            func_80048B8C(&menuLvSel->virusLvlGauge, watchMenuRef, 2, 0, var_s2, 0x99, 0xF);
            func_800466A0(&menuLvSel->virusLvlGauge.unk_010, 1.0f, 0.5f);
            menuLvSel->virusLvlGauge.unk_008 = menuLvSel->unk_2570;
            break;

        default:
            break;
    }

    func_80049894(&menuLvSel->speedIcon, watchMenuRef, 1, temp_s5->unk_05, 0x44, 0x28);
    menuSpeedItem_init(&menuLvSel->speedSelector, watchMenuRef, 1, 0, temp_s5->unk_05, 0x82, 0x24, 0x2E);

    func_800466A0(&menuLvSel->speedSelector.unk_014, 1.0f, 0.5f);
    menuMusicItem_init(&menuLvSel->musicSelector, watchMenuRef, temp_s5->unk_06, 0x46, 0x46);
    func_80048680(&menuLvSel->bottle, watchMenuRef, 0x19, 7);

    for (var_s2 = 0; var_s2 < 3U; var_s2++) {
        func_800479A8(&menuLvSel->unk_162C[var_s2], watchMenuRef, 1, 0, _cursor_7325[var_s2][0],
                      _cursor_7325[var_s2][1], _cursor_7325[var_s2][2], _cursor_7325[var_s2][3]);
    }

    menuItem_init(&menuLvSel->capsuleSpeedIcon, 0x56, 7);
    menuItem_init(&menuLvSel->musicIcon, 0x99, 8);

    func_800529FC(menuLvSel, 1, 0.0f);
    *arg2 = temp_s7;
}
#else
INCLUDE_ASM("asm/us/nonmatchings/main_segment/main_menu", menuLvSel_init);
#endif
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", menuLvSel_init);
#endif

#if VERSION_US || VERSION_CN
void func_80052DF0(MenuLvSel *menuLvSel) {
    u16 keyTrg = _getKeyTrg(menuLvSel->watchMenuRef, 0);

    if (keyTrg & B_BUTTON) {
        _setFadeDir(menuLvSel->watchMenuRef, -1);
        _setNextMain(menuLvSel->watchMenuRef, MAIN_NO_6);
        dm_snd_play(SND_INDEX_68);
    }
}
#endif

#if VERSION_US || VERSION_CN
void menuLvSel_input(MenuLvSel *menuLvSel) {
    struct_evs_mem_data_unk_B4 *temp_s5 = &evs_mem_data[evs_select_name_no[0]].unk_B4;
    u16 keyRep = _getKeyRep(menuLvSel->watchMenuRef, 0);
    SndIndex sndIndex = SND_INDEX_INVALID;
    struct_game_state_data *gameStateData = &game_state_data[0];
    u16 keyTrg = _getKeyTrg(menuLvSel->watchMenuRef, 0);
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
        _setNextMain(menuLvSel->watchMenuRef, MAIN_NO_1);

        switch (menuLvSel->unk_0004) {
            case MAINMENUMODE_MENULVSEL_7:
                gameStateData->unk_026 = menuLvSel->virusLvlGauge.unk_00C;
                gameStateData->unk_02C = menuLvSel->speedSelector.unk_008;
                temp_s5->unk_04 = menuLvSel->virusLvlGauge.unk_00C;
                break;

            case MAINMENUMODE_MENULVSEL_10:
                gameStateData->unk_026 = 0xA;
                gameStateData->unk_02C = menuLvSel->speedSelector.unk_008;
                gameStateData->unk_16C = menuLvSel->gameLvlSelector.unk_008;
                temp_s5->unk_08 = menuLvSel->gameLvlSelector.unk_008;
                break;

            case MAINMENUMODE_MENULVSEL_13:
                gameStateData->unk_026 = _timeAttack_levelTable[menuLvSel->gameLvlSelector.unk_008];
                gameStateData->unk_02C = menuLvSel->speedSelector.unk_008;
                gameStateData->unk_16C = menuLvSel->gameLvlSelector.unk_008;
                temp_s5->unk_07 = menuLvSel->gameLvlSelector.unk_008;
                break;

            default:
                break;
        }

        temp_s5->unk_05 = menuLvSel->speedSelector.unk_008;
        temp_s5->unk_06 = menuLvSel->musicSelector.unk_004;

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
#endif

#if VERSION_US || VERSION_CN
void menuLvSel_update(MenuLvSel *menuLvSel) {
    MenuItem *rootItem = _getRootItem(menuLvSel->watchMenuRef);
    s32 i;

    switch (menuLvSel->unk_0004) {
        case MAINMENUMODE_MENULVSEL_10:
            menuLvSel->bottle.unk_004 = menuLvSel->unk_0004;
            menuLvSel->gameLvlIcon.unk_8 = menuLvSel->gameLvlSelector.unk_008;
            break;

        case MAINMENUMODE_MENULVSEL_13:
            menuLvSel->gameLvlIcon.unk_8 = menuLvSel->gameLvlSelector.unk_008;
            menuLvSel->bottle.unk_004 = _timeAttack_levelTable[menuLvSel->gameLvlSelector.unk_008];
            break;

        case MAINMENUMODE_MENULVSEL_7:
            menuLvSel->virusLvlNumber.unk_0C = menuLvSel->virusLvlGauge.unk_00C;
            menuLvSel->bottle.unk_004 = menuLvSel->virusLvlGauge.unk_00C;
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
#endif

#if VERSION_US || VERSION_CN
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
            if (menuLvSel->unk_2570 >= 0x15) {
                f32 temp_fs0 = menuLvSel->unk_0098[0].unk_0C[0];

                menuLvSel->unk_0098[0].unk_0C[0] = temp_fs0 + 222.0f;
                menuItem_drawTex(&menuLvSel->unk_0098[0], &gfx, _getTexLevel(menuLvSel->watchMenuRef, 6), 0);
                menuLvSel->unk_0098[0].unk_0C[0] = temp_fs0;
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
#endif

#if VERSION_US
void func_8005380C(MenuChSel *menuChSel, s32 arg1, f32 arg2) {
    menuChSel->unk_0074.unk_14 = arg2;
    menuChSel->unk_0074.unk_18 = 0.05f;
    menuChSel->unk_0074.unk_1C[1] = menuChSel->unk_0074.unk_24[1] - 240.0f;
    func_8004655C(&menuChSel->unk_0074, arg1);
}
#endif

extern const s32 _pos_7882[][2];
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", _pos_7882);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", func_8005380C);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", _posChar_6445);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", _posBgCursor_6446);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", _cursor_6447);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", RO_800C70D4_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", RO_800C70E4_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", RO_800C70F4_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", RO_800C7184_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", RO_800C718C_cn);
#endif

#if VERSION_US
#ifdef NON_MATCHING
void menuChSel_init(MenuChSel *menuChSel, struct_watchMenu *watchMenuRef, struct_watchMenu_unk_02470 **arg2 UNUSED) {
    MainMenuMode temp_s4 = _getMode(watchMenuRef);
    s32 var_s1;

    menuChSel->unk_0028 = -1;
    menuChSel->unk_0034 = -1;
    menuChSel->unk_0038 = -1;
    menuChSel->watchMenuRef = watchMenuRef;
    menuChSel->unk_002C = 0;
    menuChSel->unk_0030 = 0;

    switch (temp_s4) {
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

    for (var_s1 = 0; var_s1 < menuChSel->unk_0004; var_s1++) {
        s32 var_s3;

        if (game_state_data[var_s1].unk_04C == 0) {
            menuChSel->unk_0040[menuChSel->unk_003C] = var_s1;
            menuChSel->unk_003C += 1;
            menuChSel->unk_0050[var_s1] = 0;
        } else {
            menuChSel->unk_0064[menuChSel->unk_0060] = var_s1;
            menuChSel->unk_0060 += 1;
            menuChSel->unk_0050[var_s1] = 1;
        }

        switch (temp_s4) {
            case MAINMENUMODE_MENUCHSEL_16:
            case MAINMENUMODE_MENUCHSEL_20:
                var_s3 = evs_mem_data[evs_select_name_no[0]].unk_B4.unk_0F[var_s1];
                break;

            case MAINMENUMODE_MENUCHSEL_25:
            case MAINMENUMODE_MENUCHSEL_29:
            case MAINMENUMODE_MENUCHSEL_33:
                var_s3 = evs_mem_data[evs_select_name_no[var_s1]].unk_B4.unk_17;
                break;

            case MAINMENUMODE_MENUCHSEL_40:
            case MAINMENUMODE_MENUCHSEL_42:
            case MAINMENUMODE_MENUCHSEL_44:
                var_s3 = evs_cfg_4p.unk_00[3][var_s1];
                break;

            default:
                UNREACHABLE;
                break;
        }

        menuChSel->unk_0008[var_s1] = var_s3;
        menuChSel->unk_0018[var_s1] = -1;
    }

    for (var_s1 = 0; var_s1 < menuChSel->unk_0004; var_s1++) {
        MenuCursor *temp_s0_2 = &menuChSel->unk_23CC[var_s1];

        menuCursor_init2(temp_s0_2, watchMenuRef, 0, menuChSel->unk_003C, menuChSel->unk_0060, var_s1, 0, 0, 0x2C,
                         0x2C);
        temp_s0_2->unk_1D0.unk_24[0] = _pos_7882[var_s1][0];
        temp_s0_2->unk_1D0.unk_1C[0] = _pos_7882[var_s1][0];
        temp_s0_2->unk_1D0.unk_24[1] = _pos_7882[var_s1][1];
        temp_s0_2->unk_1D0.unk_1C[1] = _pos_7882[var_s1][1];
    }

    menuItem_init(&menuChSel->unk_0074, 18, 47);

    for (var_s1 = 0; var_s1 < 0xFU; var_s1++) {
        menuItem_init(&menuChSel->unk_0194[var_s1], ((var_s1 % 5) * 54) + 12, ((var_s1 / 5) * 53) + 12);
        menuItem_init(&menuChSel->unk_0A04[var_s1], 3, 3);
        func_800466B8(&menuChSel->unk_0A04[var_s1], 0.0f, 0.0f);
        func_800466A0(&menuChSel->unk_0A04[var_s1], 0.0f, 0.5f);
    }

    for (var_s1 = 0; var_s1 < 0xFU; var_s1++) {
        func_8004AD3C(&menuChSel->unk_1274[var_s1], watchMenuRef, 0, -6, 30);
        func_8004AC98(&menuChSel->unk_1274[var_s1], -1, 0.0f);
    }

    func_8005380C(menuChSel, 1, 0.0f);
}
#else
INCLUDE_ASM("asm/us/nonmatchings/main_segment/main_menu", menuChSel_init);
#endif
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", menuChSel_init);
#endif

#if VERSION_US
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
#endif

#if VERSION_US
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
#endif

#if VERSION_US
void menuChSel_input1(MenuChSel *menuChSel, s32 arg1, s32 arg2) {
    u16 keyRep = _getKeyRep(menuChSel->watchMenuRef, arg2);
    u16 keyTrg = _getKeyTrg(menuChSel->watchMenuRef, arg2);
    SndIndex soundIndex = SND_INDEX_INVALID;
    u16 keyLvl = _getKeyLvl(menuChSel->watchMenuRef, arg2);

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
                    menuChSel->unk_002C = ((menuChSel->unk_002C == 0) || (menuChSel->unk_0030 != 1));
                    menuChSel->unk_0030 = 1;
                    soundIndex = SND_INDEX_62;
                } else {
                    menuChSel->unk_0018[arg1]++;
                    soundIndex = SND_INDEX_62;
                }
            } else if (keyTrg & B_BUTTON) {
                if ((keyLvl & L_TRIG) && (menuChSel->unk_0060 != 0)) {
                    menuChSel->unk_002C = ((menuChSel->unk_002C == 0) || (menuChSel->unk_0030 != 2));
                    menuChSel->unk_0030 = 2;
                    soundIndex = SND_INDEX_62;
                } else {
                    menuChSel->unk_0018[arg1]--;
                    soundIndex = SND_INDEX_68;
                }
            } else {
                s32 var_a2 = menuChSel->unk_0008[arg1];
                s32 temp_s4_2;
                s32 temp_s6;

                temp_s6 = 0;
                if (keyRep & L_JPAD) {
                    temp_s6--;
                }
                if (keyRep & R_JPAD) {
                    temp_s6++;
                }

                temp_s4_2 = 0;
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
#endif

#if VERSION_US
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
#endif

#if VERSION_US
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
#endif

extern const s32 _charTbl_8108[];
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", _charTbl_8108);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", func_800589E0_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", func_80058A3C_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", func_80058AB8_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", menuChSel_inputMan);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", menuChSel_inputCom);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", _charTbl_8108);
#endif

#if VERSION_US || VERSION_CN
void menuChSel_input(MenuChSel *menuChSel) {
    MainMenuMode mode;
    struct_evs_mem_data_unk_B4 *temp;
    s32 var_s2;
    s32 i;

    if ((menuChSel->unk_0074.unk_18 < 0.0f) || (menuChSel->unk_0074.unk_14 < 1.0f)) {
        return;
    }

    switch (menuChSel->unk_0028) {
        case -0x1:
            menuChSel->unk_0028 = 0;
#if VERSION_US
            menuChSel_inputMan(menuChSel);
            break;
#endif
#if VERSION_CN
            FALLTHROUGH;
#endif

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

    var_s2 = 0;
    if (menuChSel->unk_002C != 0) {
        var_s2 = menuChSel->unk_0030;
    }

    switch (_getMode(menuChSel->watchMenuRef)) {
        case MAINMENUMODE_MENUCHSEL_16:
        case MAINMENUMODE_MENUCHSEL_20:
            temp = &evs_mem_data[evs_select_name_no[0]].unk_B4;
            for (i = 0; i < menuChSel->unk_0004; i++) {
                temp->unk_0F[i] = menuChSel->unk_0008[i];
            }
            break;

        case MAINMENUMODE_MENUCHSEL_25:
        case MAINMENUMODE_MENUCHSEL_29:
        case MAINMENUMODE_MENUCHSEL_33:
            if (evs_select_name_no[0] == evs_select_name_no[1]) {
                evs_mem_data[0].unk_B4.unk_17 = 0;
            } else {
                for (i = 0; i < menuChSel->unk_0004; i++) {
                    temp = &evs_mem_data[evs_select_name_no[i]].unk_B4;

                    temp->unk_17 = menuChSel->unk_0008[i];
                }
            }
            break;

        case MAINMENUMODE_MENUCHSEL_40:
        case MAINMENUMODE_MENUCHSEL_42:
        case MAINMENUMODE_MENUCHSEL_44:
            for (i = 0; i < menuChSel->unk_0004; i++) {
                evs_cfg_4p.unk_00[3][i] = menuChSel->unk_0008[i];
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

        gameStateDataP->unk_090 = _charTbl_8108[menuChSel->unk_0008[i]];
        gameStateDataP->unk_04E = var_s2;
    }

    _setMode(menuChSel->watchMenuRef, mode);
    func_8005380C(menuChSel, -1, 1.0f);
}
#endif

extern const u8 RO_800B0D84[];
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", RO_800B0D84);
#endif

#if VERSION_US
#ifdef NON_EQUIVALENT
void menuChSel_update(MenuChSel *menuChSel) {
    MenuCursor *temp_s0_2;
    MenuItem *temp_v0;
    s32 temp_v1;
    s32 var_a1;
    s32 var_s2;
    s32 var_v1;

    temp_v0 = _getRootItem(menuChSel->watchMenuRef);
    func_800464BC(&menuChSel->unk_0074, temp_v0);

    // temp_v1 = menuChSel->unk_0028;
    // if ((temp_v1 < 2) && (temp_v1 >= 0)) {
    //    var_a1 = -(menuChSel->unk_002C == 0) | 1;
    //} else {
    //    var_a1 = -1;
    //}

    switch (menuChSel->unk_0028) {
        case 0:
        case 1:
            var_a1 = (menuChSel->unk_002C == 0) ? -1 : 1;
            break;

        default:
            var_a1 = -1;
            break;
    }

    func_80046614(&menuChSel->unk_0104, var_a1);
    func_800464BC(&menuChSel->unk_0104, temp_v0);
    func_800464F8(menuChSel->unk_0194, 0xF, &menuChSel->unk_0074);

    for (var_s2 = 0; var_s2 < 0xFU; var_s2++) {
        if (menuChSel_checkSelected(menuChSel, -1, var_s2, 1)) {
            var_a1 = -1;
        } else {
            var_a1 = 1;
        }

        func_80046614(&menuChSel->unk_0A04[var_s2], var_a1);
        func_800464BC(&menuChSel->unk_0A04[var_s2], &menuChSel->unk_0194[var_s2]);
    }

    for (var_s2 = 0; var_s2 < 0xFU; var_s2++) {
        var_v1 = RO_800B0D84[var_s2];
        if (menuChSel->unk_002C != 0) {
            var_v1 += menuChSel->unk_0030;
        }
        menuChSel->unk_1274[var_s2].unk_004 = var_v1;

        func_8004ACF4(&menuChSel->unk_1274[var_s2], var_s2 != menuChSel->unk_0034 ? -1 : 1);
        func_8004AD84(&menuChSel->unk_1274[var_s2], &menuChSel->unk_0194[var_s2]);
    }

    for (var_s2 = 0; var_s2 < menuChSel->unk_0004; var_s2++) {
        temp_s0_2 = &menuChSel->unk_23CC[var_s2];
        menuCursor_update(temp_s0_2, &menuChSel->unk_0194[menuChSel->unk_0008[var_s2]]);

        switch (menuChSel->unk_0018[var_s2]) {
            case -1:
                temp_s0_2->unk_01C.b.unk_31 = false;
                temp_s0_2->unk_01C.b.unk_29 = false;
                temp_s0_2->unk_01C.b.unk_28 = false;
                break;

            case 0:
                temp_s0_2->unk_01C.b.unk_31 = true;
                temp_s0_2->unk_01C.b.unk_29 = true;
                temp_s0_2->unk_01C.b.unk_28 = true;
                break;

            case 1:
                temp_s0_2->unk_01C.b.unk_31 = true;
                temp_s0_2->unk_01C.b.unk_29 = true;
                temp_s0_2->unk_01C.b.unk_28 = false;
                break;
        }
    }
}
#else
INCLUDE_ASM("asm/us/nonmatchings/main_segment/main_menu", menuChSel_update);
#endif
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", menuChSel_update);
#endif

extern const s32 _tex_8297[];
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", _tex_8297);
#endif

extern const s32 _pos_8298[][2];
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", _pos_8298);
#endif

#if VERSION_US || VERSION_CN
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
            temp_fs0 = item->unk_0C[0];
            temp_fs1 = item->unk_0C[1];
            item->unk_0C[0] += _pos_8298[i][0];
            item->unk_0C[1] += _pos_8298[i][1];

            menuItem_drawTex(item, &gfx, _getTexChar(menuChSel->watchMenuRef, _tex_8297[i]), 0);
            item->unk_0C[0] = temp_fs0;
            item->unk_0C[1] = temp_fs1;
        }
    }

    gSPDisplayList(gfx++, fade_fillrect_init_dl);

    for (i = 0; i < ARRAY_COUNTU(menuChSel->unk_0A04); i++) {
        s32 temp_s0_3;
        s32 temp_s1;

        item = &menuChSel->unk_0A04[i];

        if (item->color.v.a == 1.0f) {
            continue;
        }

        temp_s0_3 = item->unk_0C[0];
        temp_s1 = item->unk_0C[1];
        func_80046844(item, &gfx);

        gDPScisFillRectangle(gfx++, temp_s0_3, temp_s1, temp_s0_3 + 38, temp_s1 + 38);
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
#endif

#if VERSION_US
const s32 _moveTbl_8521[] = {
    0x140,
    -0x140,
};
#endif

#if VERSION_US
void func_80054A94(MenuPlay2 *menuPlay2, s32 arg1, f32 arg2) {
    s32 i;

    for (i = 0; i < menuPlay2->unk_00C4; i++) {
        MenuPlay2Panel *temp_a0 = &menuPlay2->unk_00C8[i];

        temp_a0->unk_0034.unk_1C[0] = temp_a0->unk_0034.unk_24[0] + _moveTbl_8521[i % ARRAY_COUNTU(_moveTbl_8521)];
        temp_a0->unk_0034.unk_18 = 0.05f;
        temp_a0->unk_0034.unk_14 = arg2;
        func_8004655C(&temp_a0->unk_0034, arg1);
    }
}
#endif

extern const s32 _onaji_8534[][2];
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", _onaji_8534);
#endif

extern const s32 _panel2_8535[][2];
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", _panel2_8535);
#endif

extern const s32 _panel4_8536[][2];
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", _panel4_8536);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", func_80059AB0_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", RO_800C73FC_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", _tex_8297);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", _pos_8298);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", RO_800C7424_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", RO_800C742C_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", RO_800C743C_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", RO_800C744C_cn);
#endif

#if VERSION_US
void menuPlay2_init(MenuPlay2 *menuPlay2, struct_watchMenu *watchMenuRef, struct_watchMenu_unk_02470 **arg2) {
    struct_evs_mem_data_unk_B4 *temp_s0;
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
            temp_s0 = &evs_mem_data[evs_select_name_no[0]].unk_B4;
            sp4C = temp_s0->unk_19;
            sp44 = temp_s0->unk_18 + 1;

            menuPlay2->unk_000C = 2;
            menuPlay2->unk_0010[0] = 0;
            menuPlay2->unk_0010[1] = 1;
            menuPlay2->unk_0020 = 0;
            menuPlay2->unk_00C4 = 2;

            for (i = 0; i < menuPlay2->unk_00C4; i++) {
                temp_s0 = &evs_mem_data[evs_select_name_no[i]].unk_B4;
                temp_s3_3 = &game_state_data[i];

                switch (_getMode(menuPlay2->watchMenuRef)) {
                    case MAINMENUMODE_MENUPLAY2_26:
                        var_s5 = temp_s0->unk_15;
                        break;

                    case MAINMENUMODE_MENUPLAY2_30:
                        var_s5 = temp_s0->unk_13;
                        break;

                    case MAINMENUMODE_MENUPLAY2_34:
                        var_s5 = temp_s0->unk_14;
                        break;

                    default:
                        break;
                }

                menuPlay2Panel_init(&menuPlay2->unk_00C8[i], watchMenuRef, arg2, 1, menuPlay2->unk_000C,
                                    menuPlay2->unk_0020, i, temp_s3_3->unk_04C == 1, temp_s3_3->unk_090, var_s5,
                                    temp_s0->unk_16, _panel2_8535[i][0], _panel2_8535[i][1]);
            }
            break;

        case MAINMENUMODE_MENUPLAY2_17:
        case MAINMENUMODE_MENUPLAY2_21:
            temp_s0 = &evs_mem_data[evs_select_name_no[0]].unk_B4;
            sp4C = temp_s0->unk_12;
            sp44 = temp_s0->unk_11 + 1;

            menuPlay2->unk_000C = 1;
            menuPlay2->unk_0020 = 1;
            menuPlay2->unk_0024[0] = 1;
            menuPlay2->unk_0010[0] = 0;
            menuPlay2->unk_00C4 = 2;

            for (i = 0; i < menuPlay2->unk_00C4; i++) {
                temp_s3_3 = &game_state_data[i];

                switch (_getMode(menuPlay2->watchMenuRef)) {
                    case MAINMENUMODE_MENUPLAY2_17:
                        var_s5 = temp_s0->unk_0B[i];
                        break;

                    case MAINMENUMODE_MENUPLAY2_21:
                        var_s5 = temp_s0->unk_09[i];
                        break;

                    default:
                        break;
                }

                menuPlay2Panel_init(&menuPlay2->unk_00C8[i], watchMenuRef, arg2, 1, menuPlay2->unk_000C,
                                    menuPlay2->unk_0020, i, temp_s3_3->unk_04C == 1, temp_s3_3->unk_090, var_s5,
                                    temp_s0->unk_0D[i], _panel2_8535[i][0], _panel2_8535[i][1]);
            }
            break;

        case MAINMENUMODE_MENUPLAY2_41:
        case MAINMENUMODE_MENUPLAY2_43:
        case MAINMENUMODE_MENUPLAY2_45:
            sp4C = evs_cfg_4p.unk_15;
            sp44 = evs_cfg_4p.unk_14 + 1;

            menuPlay2->unk_000C = 0;
            menuPlay2->unk_0020 = 0;
            menuPlay2->unk_00C4 = 4;

            for (i = 0; i < menuPlay2->unk_00C4; i++) {
                temp_s3_3 = &game_state_data[i];

                if (temp_s3_3->unk_04C == 1) {
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
                        var_s5 = evs_cfg_4p.unk_00[1][i];
                        break;

                    case MAINMENUMODE_MENUPLAY2_45:
                        var_s5 = evs_cfg_4p.unk_00[2][i];
                        break;

                    default:
                        break;
                }

                menuPlay2Panel_init(&menuPlay2->unk_00C8[i], watchMenuRef, arg2, 0, menuPlay2->unk_000C,
                                    menuPlay2->unk_0020, i, temp_s3_3->unk_04C == 1, temp_s3_3->unk_090, var_s5,
                                    evs_cfg_4p.unk_00[4][i], _panel4_8536[i][0], _panel4_8536[i][1]);
            }
            break;

        default:
            break;
    }

    i = menuPlay2->unk_00C4 / 2 - 1;
    menuItem_init(&menuPlay2->unk_0034, _onaji_8534[i][0], _onaji_8534[i][1]);
    func_800467E0(&menuPlay2->unk_0034);
    menuPlay2->unk_0034.unk_64 = 0.0f;

    menuPlay2PanelSub_init(&menuPlay2->unk_6548, watchMenuRef, arg2, sp44, sp4C, 0x19, 0x4B);
    func_80054A94(menuPlay2, 1, 0);
}
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", menuPlay2_init);
#endif

#if VERSION_US || VERSION_CN
void func_800550F4(MenuPlay2 *menuPlay2) {
    u16 keyTrg = _getKeyTrg(menuPlay2->watchMenuRef, 0);

    if (keyTrg & B_BUTTON) {
        menuPlay2->unk_0004 = 2;
        menuPlay2->unk_6548.unk_008 = 0;
        _setFadeDir(menuPlay2->watchMenuRef, -1);
        _setNextMain(menuPlay2->watchMenuRef, MAIN_NO_6);
        dm_snd_play(SND_INDEX_68);
    }
}
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/main_menu", func_80055154);
#endif

#if VERSION_US
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
#endif

#if VERSION_US
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
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/main_menu", func_800552EC);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/main_menu", func_80055598);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", func_8005A29C_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", func_8005A310_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", func_8005A3C4_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", func_8005A478_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", func_8005A77C_cn);
#endif

#if VERSION_US
#if 0
s32 func_8004E4F4(MenuPlay2PanelSub *, ?);          /* extern */
? func_800552EC(MenuPlay2 *);                       /* extern */
? func_80055598(MenuPlay2 *);                       /* extern */
extern ? RO_800AFEB8;

void menuPlay2_input(MenuPlay2 *menuPlay2) {
    MenuPlay2 *var_v1_2;
    MenuPlay2PanelSub *temp_s0_2;
    enum MainMenuMode temp_v0_2;
    enum enum_story_proc_no temp_v1_5;
    s32 temp_a1;
    s32 temp_v0;
    s32 temp_v0_3;
    s32 temp_v1;
    s32 temp_v1_4;
    s32 var_a1;
    s32 var_a1_3;
    s32 var_a2;
    s32 var_a2_2;
    s32 var_a2_3;
    s32 var_a2_4;
    s32 var_a2_5;
    s32 var_a2_6;
    s32 var_a3;
    s32 var_v1;
    s32 var_v1_3;
    struct_game_state_data *var_v1_4;
    u16 temp_s0;
    u8 temp_a2;
    void *temp_a0;
    void *temp_a0_2;
    void *temp_a0_3;
    void *temp_a0_4;
    void *temp_v1_2;
    void *temp_v1_3;
    void *var_a1_2;

    if (!(menuPlay2->unk_00C8[0].unk_0034.unk_18 < 0.0f) && !(menuPlay2->unk_00C8[0].unk_0034.unk_14 < 1.0f)) {
        temp_a1 = menuPlay2->unk_0008;
        if (temp_a1 >= 0) {
            temp_s0 = _getKeyTrg(menuPlay2->watchMenuRef, temp_a1);
            if ((_getKeyLvl(menuPlay2->watchMenuRef, menuPlay2->unk_0008) & 0x10) && (temp_s0 & 0x9000)) {
                var_a2 = 0;
                if (menuPlay2->unk_00C4 > 0) {
                    var_v1 = 0xC8;
                    do {
                        (menuPlay2 + var_v1)->unk_28 = 1;
                        var_a2 += 1;
                        var_v1 += 0x1920;
                    } while (var_a2 < menuPlay2->unk_00C4);
                }
                dm_snd_play(SND_INDEX_62);
            }
        }
        temp_v1 = menuPlay2->unk_0004;
        switch (temp_v1) {                          /* switch 1; irregular */
            case 0x-1:        
                menuPlay2->unk_0004 = 0;
            case 0x0:         
                func_8004E270(&menuPlay2->unk_6548, -1, (bitwise s32) menuPlay2->unk_6548.unk_010.unk_14);
                func_800552EC(menuPlay2);
                break;
            default:          
                temp_s0_2 = &menuPlay2->unk_6548;
                if (temp_v1 != 2) {

                } else {
                    menuPlay2->unk_0008 = -1;
                    func_8004E270(temp_s0_2, 1, (bitwise s32) menuPlay2->unk_6548.unk_010.unk_14);
                    if (func_8004E4F4(temp_s0_2, 0) != 0) {
                        temp_v0 = menuPlay2->unk_6548.unk_008;
                        var_a2_2 = 0;
                        switch (temp_v0) {          /* switch 2; irregular */
                            case 0x-1:         
                                menuPlay2->unk_0004 -= 2;
                                if (menuPlay2->unk_00C4 > 0) {
                                    var_v1_2 = menuPlay2;
                                    do {
                                        var_v1_2->unk_00C8[0].unk_0028 = -1;
                                        var_v1_2->unk_00C8[0].unk_0024 = 0;
                                        var_a2_2 += 1;
                                        var_v1_2 += 0x1920;
                                    } while (var_a2_2 < menuPlay2->unk_00C4);
                                }
                                if (menuPlay2->unk_6548.unk_0A0.unk_008 >= 0) {
                                    dm_seq_play_fade(SEQ_INDEX_12, 0x14);
                                    menuPlay2->unk_6548.unk_0A0.unk_008 = -1;
                                }
                                break;
                            case 0x1:          
                                menuPlay2->unk_0004 += 1;
                                break;
                        }
                    }
                }
                break;
            case 0x1:         
                func_8004E270(&menuPlay2->unk_6548, -1, (bitwise s32) menuPlay2->unk_6548.unk_010.unk_14);
                func_80055598(menuPlay2);
                break;
        }
        if (menuPlay2->unk_0004 >= 3) {
            temp_v0_2 = _getMode(menuPlay2->watchMenuRef);
            switch (temp_v0_2) {
                case MAINMENUMODE_MENUPLAY2_26:
                case MAINMENUMODE_MENUPLAY2_30:
                case MAINMENUMODE_MENUPLAY2_34:
                    var_a2_3 = 0;
                    if (menuPlay2->unk_00C4 > 0) {
                        var_a1 = 0xC8;
                        do {
                            temp_a0 = menuPlay2 + var_a1;
                            temp_v1_2 = (evs_select_name_no[var_a2_3] * 0xD0) + &evs_mem_data->unk_B4;
                            if (temp_a0->unk_4 != 0) {
                                temp_v1_2->unk_13 = (s8) temp_a0->unk_12C4;
                            } else if (temp_a0->unk_8 != 0) {
                                temp_v1_2->unk_14 = (s8) temp_a0->unk_12C4;
                            } else {
                                temp_v1_2->unk_15 = (s8) temp_a0->unk_29C;
                            }
                            temp_v1_2->unk_16 = (s8) temp_a0->unk_634;
                            temp_v1_2->unk_18 = (s8) (menuPlay2->unk_6548.unk_940.unk_0C - 1);
                            temp_v1_2->unk_19 = (s8) menuPlay2->unk_6548.unk_0A0.unk_004;
                            var_a2_3 += 1;
                            var_a1 += 0x1920;
                        } while (var_a2_3 < menuPlay2->unk_00C4);
                    default:
                    }
                    break;
                case MAINMENUMODE_MENUPLAY2_17:
                case MAINMENUMODE_MENUPLAY2_21:
                    var_a2_4 = 0;
                    temp_v1_3 = (*evs_select_name_no * 0xD0) + &evs_mem_data->unk_B4;
                    if (menuPlay2->unk_00C4 > 0) {
                        var_a1_2 = temp_v1_3;
                        var_a3 = 0xC8;
                        do {
                            temp_a0_2 = menuPlay2 + var_a3;
                            if (temp_a0_2->unk_4 != 0) {
                                var_a1_2->unk_9 = (s8) temp_a0_2->unk_12C4;
                            } else {
                                var_a1_2->unk_B = (s8) temp_a0_2->unk_29C;
                            }
                            var_a3 += 0x1920;
                            var_a1_2->unk_D = (s8) temp_a0_2->unk_634;
                            var_a2_4 += 1;
                            var_a1_2 += 1;
                        } while (var_a2_4 < menuPlay2->unk_00C4);
                    }
                    temp_v1_3->unk_11 = (s8) (menuPlay2->unk_6548.unk_940.unk_0C - 1);
                    temp_v1_3->unk_12 = (s8) menuPlay2->unk_6548.unk_0A0.unk_004;
                    break;
                case MAINMENUMODE_MENUPLAY2_41:
                case MAINMENUMODE_MENUPLAY2_43:
                case MAINMENUMODE_MENUPLAY2_45:
                    var_a2_5 = 0;
                    if (menuPlay2->unk_00C4 > 0) {
                        var_v1_3 = 0xC8;
                        do {
                            temp_a0_3 = menuPlay2 + var_v1_3;
                            if (temp_a0_3->unk_4 != 0) {
                                evs_cfg_4p.unk_00[2][var_a2_5] = (u8) temp_a0_3->unk_12C4;
                            } else {
                                evs_cfg_4p.unk_00[1][var_a2_5] = (u8) temp_a0_3->unk_29C;
                            }
                            evs_cfg_4p.unk_00[4][var_a2_5] = (u8) temp_a0_3->unk_634;
                            var_a2_5 += 1;
                            var_v1_3 += 0x1920;
                        } while (var_a2_5 < menuPlay2->unk_00C4);
                    }
                    evs_cfg_4p.unk_14 = menuPlay2->unk_6548.unk_940.unk_0C - 1;
                    evs_cfg_4p.unk_15 = (u8) menuPlay2->unk_6548.unk_0A0.unk_004;
                    break;
            }
            var_a2_6 = 0;
            if (menuPlay2->unk_00C4 > 0) {
                var_a1_3 = 0xC8;
                var_v1_4 = game_state_data;
                do {
                    temp_a0_4 = menuPlay2 + var_a1_3;
                    if ((temp_a0_4->unk_4 != 0) || (temp_a0_4->unk_8 != 0)) {
                        var_v1_4->unk_026 = _timeAttack_levelTable[temp_a0_4->unk_12C4];
                        var_v1_4->unk_16C = temp_a0_4->unk_12C4;
                    } else {
                        var_v1_4->unk_026 = (u8) temp_a0_4->unk_29C;
                    }
                    var_a1_3 += 0x1920;
                    var_v1_4->unk_02C = (u8) temp_a0_4->unk_634;
                    var_a2_6 += 1;
                    var_v1_4 += 0x3C4;
                } while (var_a2_6 < menuPlay2->unk_00C4);
            }
            temp_v0_3 = menuPlay2->unk_6548.unk_0A0.unk_004;
            temp_v1_4 = (menuPlay2->unk_6548.unk_940.unk_0C - 1) * 2;
            temp_a2 = *(&RO_800AFEB8 + 1 + temp_v1_4);
            evs_game_time = 0;
            evs_seqnumb = (u8) temp_v0_3;
            evs_seqence = (temp_v0_3 & 0xFF) != 4;
            temp_v1_5 = temp_a2 + 1;
            story_proc_no = temp_v1_5;
            story_proc_no = temp_v1_5 + (*(&RO_800AFEB8 + temp_v1_4) * 0xC);
            evs_story_no = temp_a2 + 1;
            _setFadeDir(menuPlay2->watchMenuRef, 1);
            _setNextMain(menuPlay2->watchMenuRef, MAIN_NO_1);
        }
    }
}
#else
INCLUDE_ASM("asm/us/nonmatchings/main_segment/main_menu", menuPlay2_input);
#endif
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", menuPlay2_input);
#endif

#if VERSION_US
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
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", menuPlay2_update);
#endif

#if VERSION_US
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
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", menuPlay2_draw);
#endif

#if VERSION_US
void func_80055DFC(MenuNmEnt *menuNmEnt, s32 arg1, f32 arg2) {
    menuNmEnt->unk_003C.unk_14 = arg2;
    menuNmEnt->unk_003C.unk_18 = 0.05f;
    menuNmEnt->unk_003C.unk_1C[1] = menuNmEnt->unk_003C.unk_24[1] - 240.0f;
    func_8004655C(&menuNmEnt->unk_003C, arg1);
}
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", func_8005B1B4_cn);
#endif

#if VERSION_US
void menuNmEnt_init(MenuNmEnt *menuNmEnt, struct_watchMenu *watchMenuRef, struct_watchMenu_unk_02470 **arg2 UNUSED) {
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
            u8 *ptr = &evs_mem_data[evs_select_name_no[i]].unk_00;

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
            bcopy(evs_mem_data[evs_select_name_no[i]].unk_01, menuNmEnt->unk_002C[i], sizeof(menuNmEnt->unk_002C[i]));
            menuNmEnt->unk_0034[i] = 0;
        } else {
            s32 j;

            for (j = 0; j < ARRAY_COUNT(menuNmEnt->unk_002C[i]); j++) {
                menuNmEnt->unk_002C[i][j] = 0;
            }

            menuNmEnt->unk_0034[i] = 0;
        }
    }

    menuItem_init(&menuNmEnt->unk_003C, 29, 98);
    menuItem_init(&menuNmEnt->unk_00CC, 47, -47);
    menuItem_init(&menuNmEnt->unk_015C, 100, 5);
    menuItem_init(&menuNmEnt->unk_01EC, 20, 7);
    menuItem_init(&menuNmEnt->unk_027C, 0, 0);
    func_800479A8(&menuNmEnt->unk_030C, watchMenuRef, 0, menuNmEnt->unk_0004, -2, -2, 0x10, 0x10);
    menuNmEnt->unk_030C.unk_01C.b.unk_30 = true;
    menuItem_init(&menuNmEnt->unk_056C, 59, 23);
    menuItem_init(&menuNmEnt->unk_05FC, 0, 16);
    func_80055DFC(menuNmEnt, 1, 0.0f);
}
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", menuNmEnt_init);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/main_menu", func_800560D4);
#endif

extern const u8 RO_800B0F5C[];
#if VERSION_US
const u8 RO_800B0F5C[] = {
    0x82, 0x60, 0x82, 0x61, 0x82, 0x62, 0x82, 0x63, 0x82, 0x64, 0x5F, 0x5F, 0x82, 0x81, 0x82, 0x82, 0x82, 0x83, 0x82,
    0x84, 0x82, 0x85, 0x5F, 0x5F, 0x81, 0x9B, 0x81, 0x7E, 0x81, 0x99, 0x82, 0x65, 0x82, 0x66, 0x82, 0x67, 0x82, 0x68,
    0x82, 0x69, 0x5F, 0x5F, 0x82, 0x86, 0x82, 0x87, 0x82, 0x88, 0x82, 0x89, 0x82, 0x8A, 0x5F, 0x5F, 0x81, 0x45, 0x81,
    0x44, 0x81, 0x46, 0x82, 0x6A, 0x82, 0x6B, 0x82, 0x6C, 0x82, 0x6D, 0x82, 0x6E, 0x5F, 0x5F, 0x82, 0x8B, 0x82, 0x8C,
    0x82, 0x8D, 0x82, 0x8E, 0x82, 0x8F, 0x5F, 0x5F, 0x81, 0x49, 0x81, 0x48, 0x81, 0x95, 0x82, 0x6F, 0x82, 0x70, 0x82,
    0x71, 0x82, 0x72, 0x82, 0x73, 0x5F, 0x5F, 0x82, 0x90, 0x82, 0x91, 0x82, 0x92, 0x82, 0x93, 0x82, 0x94, 0x5F, 0x5F,
    0x81, 0x96, 0x81, 0x5E, 0x81, 0x93, 0x82, 0x74, 0x82, 0x75, 0x82, 0x76, 0x82, 0x77, 0x82, 0x78, 0x5F, 0x5F, 0x82,
    0x95, 0x82, 0x96, 0x82, 0x97, 0x82, 0x98, 0x82, 0x99, 0x5F, 0x5F, 0x81, 0x43, 0x81, 0x66, 0x81, 0x60, 0x82, 0x79,
    0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x82, 0x9A, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F,
    0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x82, 0x4F, 0x82, 0x50, 0x82, 0x51, 0x82, 0x52, 0x82, 0x53,
    0x5F, 0x5F, 0x82, 0x54, 0x82, 0x55, 0x82, 0x56, 0x82, 0x57, 0x82, 0x58, 0x5F, 0x5F, 0x33, 0x30, 0x33, 0x31, 0x33,
    0x32, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F,
    0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x34, 0x30, 0x34, 0x31, 0x34, 0x32, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F,
    0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x35, 0x30,
    0x35, 0x31, 0x35, 0x32, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
#endif

ASM_DATA;
const u8 *_nameEntry_charTable[] = {
    RO_800B0F5C,
};

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", func_8005B56C_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", RO_800B0F5C);
#endif

#if VERSION_US
#if 0
? func_80055DFC(MenuNmEnt *, ?, ?);                 /* extern */
? func_80059B5C(struct_watchMenu *);                /* extern */
extern ? _nameEntry_charTable;

void menuNmEnt_input(MenuNmEnt *menuNmEnt) {
    s32 sp14;
    s32 sp1C;
    enum MainMenuMode sp24;
    enum MainMenuMode temp_v0_7;
    enum SndIndex var_fp;
    s32 temp_a1_4;
    s32 temp_lo;
    s32 temp_s3;
    s32 temp_s4;
    s32 temp_s6;
    s32 temp_v1;
    s32 temp_v1_3;
    s32 temp_v1_4;
    s32 temp_v1_5;
    s32 temp_v1_6;
    s32 temp_v1_7;
    s32 var_a2;
    s32 var_s0;
    s32 var_s0_2;
    s32 var_s0_3;
    s32 var_s0_4;
    s32 var_s0_5;
    s32 var_s1;
    s32 var_s7;
    s32 var_v0;
    s8 *temp_v0_6;
    struct_evs_mem_data *temp_s1_2;
    u16 temp_s0;
    u16 temp_v0;
    u8 *var_a0;
    u8 *var_a0_2;
    u8 temp_a0;
    u8 temp_v1_8;
    u8 temp_v1_9;
    void *temp_a1;
    void *temp_a1_2;
    void *temp_a1_3;
    void *temp_s0_2;
    void *temp_s1;
    void *temp_s5;
    void *temp_v0_2;
    void *temp_v0_3;
    void *temp_v0_4;
    void *temp_v0_5;
    void *temp_v1_2;

    var_fp = SND_INDEX_INVALID;
    temp_s0 = _getKeyRep(menuNmEnt->unk_0, menuNmEnt->unk_4);
    temp_v0 = _getKeyTrg(menuNmEnt->unk_0, menuNmEnt->unk_4);
    sp1C = 0;
    sp14 = (s32) temp_v0;
    temp_s4 = menuNmEnt->unk_4;
    if (!(menuNmEnt->unk_54 < 0.0f) && !(menuNmEnt->unk_50 < 1.0f)) {
        temp_s3 = ((temp_s0 & 0x100) != 0) - ((temp_s0 & 0x200) != 0);
        temp_s6 = ((temp_s0 & 0x400) != 0) - ((temp_s0 & 0x800) != 0);
        var_s7 = 0;
        if (((temp_s3 != 0) | (temp_s6 != 0)) != 0) {
            temp_v0_2 = menuNmEnt + (temp_s4 * 8);
            var_s0 = temp_v0_2->unk_1C;
            var_s1 = temp_v0_2->unk_20;
            temp_s5 = (temp_s4 * 4) + menuNmEnt;
            do {
                temp_a1 = *((temp_s5->unk_14 * 4) + &_nameEntry_charTable) + ((var_s0 + (var_s1 * 0xF)) * 2);
                if (((u8) *(&__ctype_map + temp_a1->unk_0) >> 3) & 1 & (temp_s3 != 0)) {
                    temp_lo = temp_s3 * (temp_a1->unk_1 - 0x30);
                    if (temp_s3 > 0) {
                        var_v0 = 3 - temp_lo;
                    } else {
                        var_v0 = ~temp_lo;
                    }
                    var_a2 = var_s0 + var_v0;
                } else {
                    var_a2 = var_s0 + temp_s3;
                }
                var_s0 = WrapI(0, 0xF, var_a2);
                var_s1 = WrapI(0, 9, var_s1 + temp_s6);
                temp_a1_2 = *((temp_s5->unk_14 * 4) + &_nameEntry_charTable) + ((var_s0 + (var_s1 * 0xF)) * 2);
                temp_a0 = temp_a1_2->unk_0;
                temp_v1 = temp_a0 & 0xFF;
            } while (temp_v1 == 0x5F);
            if (temp_a0 & 0x80) {
                ((temp_s4 * 4) + menuNmEnt)->unk_C = -1;
                var_s7 = 1;
            } else if ((*(&__ctype_map + temp_v1) & 8) && ((((temp_s4 * 4) + menuNmEnt)->unk_C = (s32) (temp_v1 - 0x30), temp_a1_3 = menuNmEnt + (temp_s4 * 8), var_s0 = (var_s0 + 0x30) - temp_a1_2->unk_1, var_s7 = 0, (var_s0 != temp_a1_3->unk_1C)) || (var_s1 != temp_a1_3->unk_20))) {
                var_s7 = 1;
            }
            if (var_s7 != 0) {
                var_fp = SND_INDEX_64;
                temp_v0_3 = menuNmEnt + (temp_s4 * 8);
                temp_v0_3->unk_1C = var_s0;
                temp_v0_3->unk_20 = var_s1;
            }
        }
        if ((sp14 & 0x1000) && (temp_v1_2 = (temp_s4 * 4) + menuNmEnt, (temp_v1_2->unk_C != 5))) {
            var_fp = SND_INDEX_62;
            temp_v0_4 = menuNmEnt + (temp_s4 * 8);
            temp_v1_2->unk_C = 5;
            temp_v0_4->unk_1C = 0xC;
            temp_v0_4->unk_20 = 8;
        } else if (sp14 & 0x9000) {
            temp_s1 = (temp_s4 * 4) + menuNmEnt;
            temp_s0_2 = menuNmEnt + (temp_s4 * 8);
            temp_a1_4 = temp_s1->unk_C;
            switch (temp_a1_4) {                    /* switch 1; irregular */
                default:
                    var_s0_2 = 0;
                    if (temp_a1_4 != 5) {

                    } else {
                        var_a0 = temp_s1 + 0x2C;
loop_41:
                        if (*var_a0 == 0) {
                            var_s0_2 += 1;
                            var_a0 += 1;
                            if (var_s0_2 >= 4) {

                            } else {
                                goto loop_41;
                            }
                        }
                        var_fp = SND_INDEX_62;
                        if (var_s0_2 != 4) {
                            sp1C += 1;
                        } else {
block_46:
                            var_fp = SND_INDEX_71;
                        }
                    }
                    break;
                case 0x-1:
                    if (temp_s1->unk_34 < 4) {
                        *(temp_s1 + 0x2C + temp_s1->unk_34) = font2index(*(&_nameEntry_charTable + (temp_s1->unk_14 * 4)) + ((temp_s0_2->unk_1C + (temp_s0_2->unk_20 * 0xF)) * 2));
block_34:
                        var_fp = SND_INDEX_62;
                        temp_s1->unk_34 = (s32) (temp_s1->unk_34 + 1);
                    }
block_36:
                    if (temp_s1->unk_34 == 4) {
                        temp_s0_2->unk_1C = 0xC;
                        temp_s0_2->unk_20 = 8;
                        temp_s1->unk_C = 5;
                    }
                    break;
                case 0x3:
                    temp_v1_3 = temp_s1->unk_34;
                    if (temp_v1_3 < 4) {
                        *(temp_s1 + 0x2C + temp_v1_3) = 0;
                        goto block_34;
                    }
                    goto block_36;
                case 0x4:
                    temp_v1_4 = temp_s1->unk_34;
                    var_fp = SND_INDEX_68;
                    if (temp_v1_4 > 0) {
                        temp_v1_5 = temp_v1_4 - 1;
                        temp_s1->unk_34 = temp_v1_5;
                        *(temp_s1 + 0x2C + temp_v1_5) = 0;
                    } else {
                        goto block_46;
                    }
                    break;
            }
        } else if (sp14 & 0x4000) {
            temp_v0_5 = (temp_s4 * 4) + menuNmEnt;
            temp_v1_6 = temp_v0_5->unk_34;
            temp_v1_7 = temp_v1_6 - 1;
            if (temp_v1_6 > 0) {
                temp_v0_5->unk_34 = temp_v1_7;
                *(temp_v0_5 + 0x2C + temp_v1_7) = 0;
            } else {
                sp1C -= 1;
            }
            var_fp = SND_INDEX_68;
        }
        if (sp1C > 0) {
            temp_s1_2 = &evs_mem_data[evs_select_name_no[temp_s4]];
            var_s0_3 = 0;
            if (_getMode(menuNmEnt->unk_0) != MAINMENUMODE_MENUNMENT_64) {
                dm_init_save_mem(temp_s1_2);
                var_s0_3 = 0;
            }
            var_a0_2 = (temp_s4 * 4) + menuNmEnt + 0x2C;
            temp_s1_2->unk_00[0] = (u8) temp_s1_2->unk_00[0] | 1;
            do {
                temp_v0_6 = &temp_s1_2->unk_00[var_s0_3];
                var_s0_3 += 1;
                temp_v0_6->unk_1 = (u8) *var_a0_2;
                var_a0_2 += 1;
            } while (var_s0_3 < 4);
            var_s0_4 = temp_s4 + 1;
            if (var_s0_4 < menuNmEnt->unk_8) {
loop_59:
                temp_v1_8 = evs_select_name_no[var_s0_4];
                if ((temp_v1_8 == 8) || ((_getMode(menuNmEnt->unk_0) != MAINMENUMODE_MENUNMENT_64) && ((u8) evs_mem_data[temp_v1_8].unk_00[0] & 1))) {
                    var_s0_4 += 1;
                    if (var_s0_4 < menuNmEnt->unk_8) {
                        goto loop_59;
                    }
                }
                if (var_s0_4 < menuNmEnt->unk_8) {
                    menuNmEnt->unk_4 = var_s0_4;
                } else {
                    goto block_66;
                }
            } else {
block_66:
                func_80059B5C(menuNmEnt->unk_0);
                temp_v0_7 = _getMode(menuNmEnt->unk_0);
                switch (temp_v0_7) {
                    case MAINMENUMODE_MENUNMENT_3:
                        sp24 = MAINMENUMODE_MENUSTORY_4;
                        break;
                    case MAINMENUMODE_MENUNMENT_6:
                        sp24 = MAINMENUMODE_MENULVSEL_7;
                        break;
                    case MAINMENUMODE_MENUNMENT_9:
                        sp24 = MAINMENUMODE_MENULVSEL_10;
                        break;
                    case MAINMENUMODE_MENUNMENT_12:
                        sp24 = MAINMENUMODE_MENULVSEL_13;
                        break;
                    case MAINMENUMODE_MENUNMENT_15:
                        sp24 = MAINMENUMODE_MENUCHSEL_16;
                        break;
                    case MAINMENUMODE_MENUNMENT_19:
                        sp24 = MAINMENUMODE_MENUCHSEL_20;
                        break;
                    case MAINMENUMODE_MENUNMENT_24:
                        sp24 = MAINMENUMODE_MENUCHSEL_25;
                        break;
                    case MAINMENUMODE_MENUNMENT_28:
                        sp24 = MAINMENUMODE_MENUCHSEL_29;
                        break;
                    case MAINMENUMODE_MENUNMENT_32:
                        sp24 = MAINMENUMODE_MENUCHSEL_33;
                        break;
                    case MAINMENUMODE_MENUNMENT_63:
                    case MAINMENUMODE_MENUNMENT_64:
                        sp24 = MAINMENUMODE_MENUMAIN_0;
                        break;
                }
                _setMode(menuNmEnt->unk_0, sp24);
                func_80055DFC(menuNmEnt, -1, 0x3F800000);
            }
        } else {
            var_s0_5 = temp_s4 - 1;
            if (sp1C < 0) {
                if (var_s0_5 >= 0) {
loop_82:
                    temp_v1_9 = evs_select_name_no[var_s0_5];
                    if ((temp_v1_9 == 8) || ((_getMode(menuNmEnt->unk_0) != MAINMENUMODE_MENUNMENT_64) && ((u8) evs_mem_data[temp_v1_9].unk_00[0] & 1))) {
                        var_s0_5 -= 1;
                        if (var_s0_5 >= 0) {
                            goto loop_82;
                        }
                    }
                    if (var_s0_5 >= 0) {
                        menuNmEnt->unk_4 = var_s0_5;
                        var_fp = SND_INDEX_68;
                    } else {
                        goto block_89;
                    }
                } else {
block_89:
                    var_fp = SND_INDEX_68;
                    _getMode(menuNmEnt->unk_0);
                    _setMode(menuNmEnt->unk_0, MAINMENUMODE_MENUMAIN_0);
                    func_80055DFC(menuNmEnt, -1, 0x3F800000);
                }
            }
        }
        if (var_fp >= 0) {
            dm_snd_play(var_fp);
        }
    }
}
#else
INCLUDE_ASM("asm/us/nonmatchings/main_segment/main_menu", menuNmEnt_input);
#endif
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", menuNmEnt_input);
#endif

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", RO_800B1168);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/main_menu", menuNmEnt_update);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", menuNmEnt_update);
#endif

#if VERSION_US
#if 0
s32 menuItem_drawTex(s8 *, Gfx **, s32, ?);
? menuItem_drawAlphaTex(f32 *, Gfx **, s32, s32, s32);
? func_80048634(f32 **, ?, Gfx **);
s32 _getTexName(struct_watchMenu *, ?);

void menuNmEnt_draw(MenuRank *menuRank, Gfx **gfxP) {
    Gfx *sp18;
    f32 *sp1C;
    Gfx *temp_v0;
    Gfx *temp_v1;
    f32 temp_a1;
    s32 temp_s0;
    s32 temp_s4;
    s32 var_s0;
    s32 var_s0_2;
    s32 var_s1;
    s32 var_s3;
    s32 var_s3_2;
    s32 var_s4;
    s8 *var_s2;
    u8 temp_v0_2;

    temp_v0 = *gfxP;
    temp_v0->words.w0 = 0xDE000000;
    temp_v0->words.w1 = (u32) fade_normal_texture_init_dl;
    sp18 = temp_v0 + 8;
    menuItem_drawTex(&arg0->unk_0020[0xAC], &sp18, _getTexName(arg0->unk_0000, 3), 0);
    if (arg0->unk_0004 == 1) {
        menuItem_drawTex(&arg0->unk_0020[0x13C], &sp18, _getTexName(arg0->unk_0000, 4), 0);
    }
    sp18->words.w0 = 0xDE000000;
    sp18->words.w1 = (u32) fade_normal_texture_init_dl;
    sp18 += 8;
    if (menuItem_drawTex(&arg0->unk_0020[0x1C], &sp18, _getTexName(arg0->unk_0000, 2), 0) != 0) {
        temp_v1 = sp18;
        temp_v1->words.w1 = (u32) &fade_intensity_texture_init_dl;
        temp_v1->unk_C = 0x2000;
        temp_v1->unk_10 = 0xFA000000;
        temp_v1->words.w0 = 0xDE000000;
        temp_v1->unk_8 = 0xE3001201;
        temp_v1->unk_14 = 0xFF;
        var_s3 = 0;
        sp18 = temp_v1 + 8;
        sp18 = temp_v1 + 0x10;
        var_s4 = (s32) arg0->unk_017C.unk_7C[1];
        sp18 = temp_v1 + 0x18;
        var_s2 = *(&_nameEntry_charTable + (((arg0->unk_0004 * 4) + arg0)->unk_14 * 4));

        do {
            var_s1 = 0;
            var_s0 = (s32) arg0->unk_017C.unk_7C[0];
loop_5:
            if (*var_s2 & 0x80) {
                fontXX_draw(&sp18, (f32) var_s0, (f32) var_s4, 12.0f, 12.0f, var_s2);
            }
            var_s0 += 0xF;
            var_s1 += 1;
            var_s2 += 2;
            if (var_s1 < 0xF) {
                goto loop_5;
            }
            var_s3 += 1;
            var_s4 += 0xD;
        } while (var_s3 < 9);

        var_s3_2 = 0;
        var_s0_2 = (s32) arg0->unk_04F4.unk_0C.unk_6C[3];
        temp_s4 = (s32) arg0->unk_04F4.unk_0C.unk_7C[0];
        do {
            temp_a1 = (f32) var_s0_2;
            temp_v0_2 = ((arg0->unk_0004 * 4) + arg0 + var_s3_2)->unk_2C;
            var_s0_2 += 0xD;
            var_s3_2 += 1;
            fontXX_drawID(&sp18, temp_a1, (f32) temp_s4, 12.0f, 12.0f, (s32) temp_v0_2);
        } while (var_s3_2 < 4);

        sp18->words.w0 = 0xDE000000;
        sp18->words.w1 = (u32) &fade_alpha_texture_init_dl;
        sp18 += 8;
        temp_s0 = _getTexName(arg0->unk_0000, 0);
        menuItem_drawAlphaTex(&arg0->unk_590[0].unk_0004.unk_08.unk_54[3], &sp18, temp_s0, _getTexName(arg0->unk_0000, 1), 0);
        sp1C = &arg0->unk_020C[1].unk_6C[1];
        func_80048634(&sp1C, 1, &sp18);
        *gfxP = sp18;
    }
}
#else
INCLUDE_ASM("asm/us/nonmatchings/main_segment/main_menu", menuNmEnt_draw);
#endif
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", menuNmEnt_draw);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/main_menu", func_80056C84);
#endif

#if VERSION_US
void func_80056CAC(MenuRankBase *arg0, MenuItem *arg1) {
    func_800464BC(&arg0->unk_04, arg1);
}
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/main_menu", menuRankBase_draw);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/main_menu", func_80056DF0);
#endif

#if VERSION_US
void func_80056E1C(MenuRankNum *arg0, MenuItem *arg1) {
    func_800464BC(&arg0->unk_08, arg1);
}
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/main_menu", menuRankNum_draw);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/main_menu", func_80057014);
#endif

#if VERSION_US
#ifdef NON_EQUIVALENT
void menuRankFig_update(MenuRankFig *arg0, MenuItem *arg1) {
    s32 var_a0;
    s32 var_t0;

    var_t0 = arg0->unk_34;
    switch (arg0->unk_04) {
        case 0x7:
            for (var_a0 = arg0->unk_08 - 1; var_a0 >= 0; var_a0--) {
                arg0->unk_0C[var_a0] = (var_t0 % 10);
                var_t0 /= 10;
            }
            break;

        case 0x8:
            arg0->unk_1C = var_t0 % 10;
            arg0->unk_18 = (var_t0 / 10) % 6;
            arg0->unk_14 = 0xF;
            arg0->unk_10 = ((var_t0 / 10) / 6) % 10;
            arg0->unk_0C[0] = (((var_t0 / 10) / 6) / 10) % 10;
            break;

        case 0x9:
            arg0->unk_20 = 0x10;
            arg0->unk_1C = var_t0 % 10;
            arg0->unk_18 = 0x11;
            arg0->unk_14 = (var_t0 / 10) % 10;
            arg0->unk_10 = ((var_t0 / 10) / 10) % 10;
            arg0->unk_0C[0] = (((var_t0 / 10) / 10) / 10) % 10;
            break;

        case 0xA:
            arg0->unk_24 = var_t0 % 10;
            arg0->unk_20 = (var_t0 / 10) % 10;
            arg0->unk_1C = 0xB;
            arg0->unk_18 = 0xC;
            arg0->unk_14 = 0x12;
            arg0->unk_10 = 0xC;
            arg0->unk_0C[0] = 0xB;
            break;

        case 0xB:
            arg0->unk_20 = var_t0 % 10;
            arg0->unk_1C = 0xF;
            arg0->unk_18 = (var_t0 / 10) % 10;
            arg0->unk_14 = ((var_t0 / 10) / 10) % 6;
            arg0->unk_10 = 0xF;
            arg0->unk_0C[0] = (((var_t0 / 10) / 10) / 6) % 10;
            break;

        case 0xC:
            arg0->unk_0C[0] = 0xA;
            arg0->unk_10 = 0xB;
            arg0->unk_14 = 0xC;
            arg0->unk_18 = 0xD;
            arg0->unk_1C = 0xE;
            break;

        case 0xD:
            arg0->unk_0C[0] = 0xD;
            arg0->unk_10 = 0xB;
            arg0->unk_14 = 0xB;
            break;

        default:
            break;
    }

    func_800464BC(&arg0->unk_38, arg1);
}
#else
INCLUDE_ASM("asm/us/nonmatchings/main_segment/main_menu", menuRankFig_update);
#endif
#endif

ASM_DATA;
char _code_9711[] = {
    0x82, 0x4F, 0x82, 0x50, 0x82, 0x51, 0x82, 0x52, 0x82, 0x53, 0x82, 0x54, 0x82, 0x55,
    0x82, 0x56, 0x82, 0x57, 0x82, 0x58, 0x82, 0x62, 0x82, 0x6B, 0x82, 0x64, 0x82, 0x60,
    0x82, 0x71, 0x81, 0x46, 0x81, 0x93, 0x81, 0x44, 0x82, 0x75, 0x00, 0x00,
};

extern const s32 _posX_0_9712[];
#if VERSION_US
const s32 _posX_0_9712[] = {
    0x00000000, 0x00000009, 0x00000012, 0x0000001B, 0x00000024,
    0x0000002D, 0x00000036, 0x0000003F, 0x00000048, 0x00000051,
};
#endif

extern const s32 _posX_1_9713[];
#if VERSION_US
const s32 _posX_1_9713[] = {
    0x00000000, 0x00000009, 0x00000010, 0x00000017, 0x00000020,
};
#endif

extern const s32 _posX_2_9714[];
#if VERSION_US
const s32 _posX_2_9714[] = {
    0x00000000, 0x00000009, 0x00000012, 0x0000001B, 0x0000001F, 0x00000028,
};
#endif

extern const s32 _posX_4_9715[];
#if VERSION_US
const s32 _posX_4_9715[] = {
    0x00000000, 0x00000007, 0x0000000E, 0x00000017, 0x0000001E, 0x00000025,
};
#endif

const s32 *_posX_tbl_9716[] = {
    _posX_0_9712, _posX_1_9713, _posX_2_9714, _posX_0_9712, _posX_4_9715, _posX_0_9712, _posX_0_9712,
};

MainMenuMode _menuAll_lastMode = MAINMENUMODE_MENUMAIN_0;

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", RO_800B1210);
#endif

#if VERSION_US
void menuRankFig_draw(MenuRankFig **arg0, s32 count, Gfx **gfxP) {
    Gfx *gfx = *gfxP;
    s32 i;

    font16_initDL2(&gfx);

    gDPSetTextureFilter(gfx++, G_TF_BILERP);

    for (i = 0; i < 0x13U; i++) {
        s32 index = font2index(&_code_9711[i * 2]);
        s32 j;

        for (j = 0; j < count; j++) {
            MenuRankFig *temp_s2 = arg0[j];
            MenuItem *item = &temp_s2->unk_38;
            s32 k;

            for (k = 0; k < temp_s2->unk_08; k++) {
                if ((i == temp_s2->unk_0C[k]) && !menuItem_outOfScreen(item, 9, 0xC)) {
                    f32 temp_ft1;

                    func_80046844(item, &gfx);
                    temp_ft1 = item->unk_30[0];
                    if (fontXX_drawID2(&gfx, item->unk_0C[0] + (_posX_tbl_9716[temp_s2->unk_04 - 7][k] * temp_ft1),
                                       item->unk_0C[1], temp_ft1 * 9.0f, item->unk_30[1] * 12.0f, index)) {
                        index = -1;
                    }
                }
            }
        }
    }

    *gfxP = gfx;
}
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/main_menu", func_8005768C);
#endif

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", RO_800B1220);
#endif
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", RO_800B1230);
#endif
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", RO_800B123C);
#endif

ASM_TEXT;

#if VERSION_US
void func_80057724(MenuRankName *arg0, MenuItem *arg1) {
    func_800464BC(&arg0->unk_08, arg1);
}
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/main_menu", menuRankName_draw);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/main_menu", func_80057898);
#endif

#if VERSION_US
void func_800578C8(MenuRankLabel *arg0, MenuItem *arg1) {
    func_800464BC(&arg0->unk_0C, arg1);
}
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/main_menu", menuRankLabel_draw);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/main_menu", func_80057AFC);
#endif

#if VERSION_US
void func_80057BE8(MenuRankHeader *arg0, MenuItem *arg1) {
    s32 i;

    func_800464BC(&arg0->unk_08, arg1);

    for (i = 0; i < arg0->unk_04; i++) {
        func_800578C8(&arg0->unk_98[i], &arg0->unk_08);
    }
}
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/main_menu", menuRankHeader_draw);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/main_menu", func_80057D24);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/main_menu", func_80057E68);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/main_menu", func_80057F6C);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/main_menu", func_8005806C);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/main_menu", func_800581C8);
#endif

#if VERSION_US
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
#endif

#if VERSION_US
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
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/main_menu", func_800585BC);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/main_menu", func_800586A4);
#endif

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", RO_800B1290);
#endif
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", RO_800B1298);
#endif
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", RO_800B12A8);
#endif
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", RO_800B12B8);
#endif
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", RO_800B12C8);
#endif
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", RO_800B12D8);
#endif
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", RO_800B12E4);
#endif
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", RO_800B12F0);
#endif
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", RO_800B12FC);
#endif
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", RO_800B1308);
#endif
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", RO_800B1314);
#endif

void func_8005C348_cn(MenuRankBase *menuRankBase, struct_watchMenu *watchMenuRef, s32 arg2, s32 arg3);
#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", func_8005C348_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", func_8005C380_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", func_8005C3AC_cn);
#endif

void func_8005C4F0_cn(MenuRankNum *menuRankNum, struct_watchMenu *watchMenuRef, s32 arg2, s32 arg3, s32 arg4);
#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", func_8005C4F0_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", func_8005C52C_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", func_8005C558_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", RO_800C77E0_cn);
#endif

void menuRankFig_init(MenuRankFig *menuRankFig, struct_watchMenu *watchMenuRef, u32 arg2, s32 arg3, s32 arg4, s32 arg5,
                      s32 arg6);
#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", menuRankFig_init);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", func_8005C8B0_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", func_8005CC68_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", _posX_0_9712);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", _posX_1_9713);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", _posX_2_9714);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", _posX_4_9715);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", RO_800C7888_cn);
#endif

void menuRankName_init(MenuRankName *menuRankName, struct_watchMenu *watchMenuRef, u8 *arg2, s32 arg3, s32 arg4);
#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", menuRankName_init);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", func_8005D004_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", func_8005D030_cn);
#endif

#if VERSION_CN
void func_8005D1BC_cn(MenuRankLabel *menuRankLabel, struct_watchMenu *watchMenuRef, s32 arg2, s32 arg3, s32 arg4,
                      s32 arg5) {
    menuRankLabel->watchMenuRef = watchMenuRef;
    menuRankLabel->unk_04 = arg2;
    menuRankLabel->unk_08 = arg3;
    menuItem_init(&menuRankLabel->unk_0C, arg4, arg5);
}
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", func_8005D1FC_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", func_8005D228_cn);
#endif

#if VERSION_CN
void func_8005D468_cn(MenuRankHeader *menuRankHeader, struct_watchMenu *watchMenuRef, const s32 *arg2, const s32 *arg3,
                      const s32 *arg4, const s32 *arg5, s32 arg6, s32 arg7, s32 arg8) {
    s32 i;

    menuRankHeader->watchMenuRef = watchMenuRef;
    menuRankHeader->unk_04 = arg6;
    menuItem_init(&menuRankHeader->unk_08, arg7, arg8);

    for (i = 0; i < arg6; i++) {
        func_8005D1BC_cn(&menuRankHeader->unk_98[i], watchMenuRef, arg2[i], arg3[i], arg4[i], arg5[i]);
    }
}
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", func_8005D564_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", func_8005D5F4_cn);
#endif

#if VERSION_CN
void func_8005D6D0_cn(MenuRankPanel *menuRankPanel, struct_watchMenu *watchMenuRef, s32 arg2, u8 *arg3, u32 arg4,
                      s32 arg5, s32 arg6, s32 arg7, s32 arg8) {
    s32 var_a2;
    s32 var_v1;

    menuRankPanel->watchMenuRef = watchMenuRef;
    menuRankPanel->unk_004 = 0;

    func_8005C348_cn(&menuRankPanel->unk_008, watchMenuRef, arg7, arg8);
    func_8005C4F0_cn(&menuRankPanel->unk_09C, watchMenuRef, arg2, 4, -1);
    menuRankName_init(&menuRankPanel->unk_134, watchMenuRef, arg3, 0x1A, 2);
    menuRankFig_init(&menuRankPanel->unk_1CC, watchMenuRef, 7, arg4, 1, 0x83, 2);
    menuRankFig_init(&menuRankPanel->unk_294, watchMenuRef, 8, arg5, 2, 0xCD, 2);
    var_v1 = 0x5A;
    if (arg6 < 0xA) {
        var_a2 = 1;
        var_v1 = 0x63;
    } else {
        var_a2 = 0xD;
    }
    menuRankFig_init(&menuRankPanel->unk_35C, watchMenuRef, var_a2, arg6, 3, var_v1, 2);
}
#endif

#if VERSION_CN
void func_8005D860_cn(MenuRankPanel *menuRankPanel, struct_watchMenu *watchMenuRef, s32 arg2, u8 *arg3, s32 arg4,
                      s32 arg5, s32 arg6, s32 arg7) {
    menuRankPanel->watchMenuRef = watchMenuRef;
    menuRankPanel->unk_004 = 1;

    func_8005C348_cn(&menuRankPanel->unk_008, watchMenuRef, arg6, arg7);
    func_8005C4F0_cn(&menuRankPanel->unk_09C, watchMenuRef, arg2, 4, -1);
    menuRankName_init(&menuRankPanel->unk_134, watchMenuRef, arg3, 0x29, 2);
    menuRankFig_init(&menuRankPanel->unk_1CC, watchMenuRef, 0xAU, arg4, 4, 0x6A, 2);
    menuRankFig_init(&menuRankPanel->unk_294, watchMenuRef, 7U, arg5, 1, 0xB7, 2);
}
#endif

#if VERSION_CN
void func_8005D9A4_cn(MenuRankPanel *menuRankPanel, struct_watchMenu *watchMenuRef, s32 arg2, u8 *arg3, s32 arg4,
                      s32 arg5, s32 arg6, s32 arg7) {
    menuRankPanel->watchMenuRef = watchMenuRef;
    menuRankPanel->unk_004 = 2;

    func_8005C348_cn(&menuRankPanel->unk_008, watchMenuRef, arg6, arg7);
    func_8005C4F0_cn(&menuRankPanel->unk_09C, watchMenuRef, arg2, 4, -1);
    menuRankName_init(&menuRankPanel->unk_134, watchMenuRef, arg3, 0x29, 2);
    menuRankFig_init(&menuRankPanel->unk_1CC, watchMenuRef, 8U, arg4, 2, 0x75, 2);
    menuRankFig_init(&menuRankPanel->unk_294, watchMenuRef, 7U, arg5, 1, 0xB7, 2);
}
#endif

#if VERSION_CN
void func_8005DAE4_cn(MenuRankPanel *menuRankPanel, struct_watchMenu *watchMenuRef, s32 arg2, u8 *arg3, s32 arg4,
                      s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9) {
    s32 var_a2;
    s32 var_v1;

    menuRankPanel->watchMenuRef = watchMenuRef;
    menuRankPanel->unk_004 = 3;

    func_8005C348_cn(&menuRankPanel->unk_008, watchMenuRef, arg8, arg9);
    func_8005C4F0_cn(&menuRankPanel->unk_09C, watchMenuRef, arg2, 4, -1);
    menuRankName_init(&menuRankPanel->unk_134, watchMenuRef, arg3, 0x1A, 2);
    menuRankFig_init(&menuRankPanel->unk_1CC, watchMenuRef, 7U, arg4, 1, 0x53, 2);
    menuRankFig_init(&menuRankPanel->unk_294, watchMenuRef, 0xBU, arg5, 2, 0x99, 2);

    if (arg6 < dm_get_first_virus_count_in_new_mode(arg7)) {
        var_a2 = 2;
        var_v1 = 0xD9;
    } else {
        var_a2 = 0xD;
        var_v1 = 0xD5;
    }
    menuRankFig_init(&menuRankPanel->unk_35C, watchMenuRef, var_a2, arg6, 1, var_v1, 2);
}
#endif

#if VERSION_CN
void func_8005DC98_cn(MenuRankPanel *menuRankPanel, struct_watchMenu *watchMenuRef, s32 arg2, u8 *arg3, s32 arg4,
                      s32 arg5, s32 arg6, s32 arg7, s32 arg8) {
    menuRankPanel->watchMenuRef = watchMenuRef;
    menuRankPanel->unk_004 = 4;

    func_8005C348_cn(&menuRankPanel->unk_008, watchMenuRef, arg7, arg8);
    func_8005C4F0_cn(&menuRankPanel->unk_09C, watchMenuRef, arg2, 4, -1);
    menuRankName_init(&menuRankPanel->unk_134, watchMenuRef, arg3, 0x1A, 2);
    menuRankFig_init(&menuRankPanel->unk_1CC, watchMenuRef, 9U, arg4, 5, 0x5A, 2);
    menuRankFig_init(&menuRankPanel->unk_294, watchMenuRef, 2U, arg5, 6, 0xA7, 2);
    menuRankFig_init(&menuRankPanel->unk_35C, watchMenuRef, 2U, arg6, 7, 0xD9, 2);
}
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", RO_800C7898_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", RO_800C78A8_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", RO_800C78B4_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", func_8005DE18_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", func_8005DF38_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", func_8005E1A0_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", func_8005E2A0_cn);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/main_menu", menuRank_setFrame);
#endif

extern const s32 RO_800C7908_cn[2];

#if VERSION_CN
const s32 RO_800C7908_cn[] = {
    -0x140,
    0x140,
};
#endif

#if VERSION_CN
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

        item->unk_1C[0] = item->unk_24[0] + RO_800C7908_cn[i % ARRAY_COUNTU(RO_800C7908_cn)];
        item->unk_1C[1] = item->unk_24[1];
        item->unk_18 = 0.05f;
        item->unk_14 = arg3;
        func_8004655C(item, arg2);
    }
}
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/main_menu", func_80058A24);
#endif

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", RO_800B1320);
#endif
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", RO_800B1330);
#endif
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", RO_800B1340);
#endif
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", RO_800B1350);
#endif
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", RO_800B1360);
#endif
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", RO_800B1370);
#endif

#if VERSION_CN
void func_8005E76C_cn(MenuRank *menuRank, s32 arg1 UNUSED) {
    menuItem_init(&menuRank->unk_032C, 0xA4, 0x30);
    func_8005D1BC_cn(&menuRank->unk_0458, menuRank->watchMenuRef, 1, 1, 2, 2);
    func_8005D1BC_cn(&menuRank->unk_04F4, menuRank->watchMenuRef, 2, 1, 0x3E, 2);
}
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", _hedAllType_10392);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", _hedStoryId_10393);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", _hedStoryX_10394);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", _hedStoryY_10395);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", _hedLevelId_10396);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", _hedLevelX_10397);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", _hedLevelY_10398);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", _hed1PTaiQId_10399);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", _hed1PTaiQX_10400);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", _hed1PTaiQY_10401);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", _hed1PTimeAtId_10402);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", _hed1PTimeAtX_10403);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", _hed1PTimeAtY_10404);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", _hedVsId_10405);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", _hedVsX_10406);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", _hedVsY_10407);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/main_menu", menuRank_setPanel);
#endif

extern const UNK_TYPE _hedAllType_10392;
extern const UNK_TYPE _hedStoryId_10393;
extern const UNK_TYPE _hedStoryX_10394;
extern const UNK_TYPE _hedStoryY_10395;
extern const UNK_TYPE _hedLevelId_10396;
extern const UNK_TYPE _hedLevelX_10397;
extern const UNK_TYPE _hedLevelY_10398;
extern const UNK_TYPE _hed1PTaiQId_10399;
extern const UNK_TYPE _hed1PTaiQX_10400;
extern const UNK_TYPE _hed1PTaiQY_10401;
extern const UNK_TYPE _hed1PTimeAtId_10402;
extern const UNK_TYPE _hed1PTimeAtX_10403;
extern const UNK_TYPE _hed1PTimeAtY_10404;
extern const UNK_TYPE _hedVsId_10405;
extern const UNK_TYPE _hedVsX_10406;
extern const UNK_TYPE _hedVsY_10407;

#if VERSION_CN
void menuRank_setPanel(MenuRank *menuRank, s32 arg1, MainMenuMode arg2, s32 arg3) {
    MenuRank_unk_590 *temp_s3 = &menuRank->unk_590[arg1];
    MenuRank_unk_001C *temp_s2 = &menuRank->unk_001C;
    const UNK_TYPE *sp30;
    const UNK_TYPE *sp34;
    const UNK_TYPE *sp38;
    s32 sp3C;
    s32 sp40;
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
            sp40 = 4;
            sp30 = &_hedStoryId_10393;
            sp34 = &_hedStoryX_10394;
            sp38 = &_hedStoryY_10395;
            break;

        case MAINMENUMODE_MENURANK_50:
            sp40 = 3;
            sp30 = &_hedLevelId_10396;
            sp34 = &_hedLevelX_10397;
            sp38 = &_hedLevelY_10398;
            break;

        case MAINMENUMODE_MENURANK_51:
            sp40 = 3;
            sp30 = &_hed1PTaiQId_10399;
            sp34 = &_hed1PTaiQX_10400;
            sp38 = &_hed1PTaiQY_10401;
            break;

        case MAINMENUMODE_MENURANK_52:
            sp40 = 4;
            sp30 = &_hed1PTimeAtId_10402;
            sp34 = &_hed1PTimeAtX_10403;
            sp38 = &_hed1PTimeAtY_10404;
            break;

        case MAINMENUMODE_MENURANK_53:
        case MAINMENUMODE_MENURANK_54:
        case MAINMENUMODE_MENURANK_56:
        case MAINMENUMODE_MENURANK_57:
        case MAINMENUMODE_MENURANK_58:
            sp40 = 4;
            sp30 = &_hedVsId_10405;
            sp34 = &_hedVsX_10406;
            sp38 = &_hedVsY_10407;
            break;

        default:
            break;
    }

    func_8005D1BC_cn(&menuRank->unk_03BC, menuRank->watchMenuRef, 3, sp3C, 0x23, 0x30);
    func_8005D468_cn(&temp_s3->unk_0004, menuRank->watchMenuRef, &_hedAllType_10392, sp30, sp34, sp38, sp40, 0, -0x10);

    for (i = 0; i < temp_s3->unk_0000; i++) {
        struct_evs_mem_data *ptr;
        struct_evs_mem_data_unk_28 *temp_t0;
        struct_evs_mem_data_unk_4C *temp_t0_2;
        struct_evs_mem_data_unk_64 *temp_t0_3;
        struct_evs_mem_data_unk_7C *temp_t0_4;
        u16 *var_s7;
        u8 *var_s6;
        s32 var_s1;
        u16 *var_s4;

        switch (arg2) {
            case MAINMENUMODE_MENURANK_49:
                var_s1 = temp_s2->unk_000[arg3][i];
                ptr = &evs_mem_data[var_s1];
                temp_t0 = &ptr->unk_28[arg3];
                func_8005D6D0_cn(&temp_s3->unk_3A8[i], menuRank->watchMenuRef, temp_s2->unk_018[arg3][i], ptr->unk_01,
                                 temp_t0->unk_0, temp_t0->unk_4, temp_t0->unk_8 + 1, 0, i * 0x11);
                break;

            case MAINMENUMODE_MENURANK_50:
                var_s1 = temp_s2->unk_030[arg3][i];
                ptr = &evs_mem_data[var_s1];
                temp_t0_2 = &ptr->unk_4C[arg3];
                func_8005D860_cn(&temp_s3->unk_3A8[i], menuRank->watchMenuRef, temp_s2->unk_048[arg3][i], ptr->unk_01,
                                 (s32)temp_t0_2->unk_4, temp_t0_2->unk_0, 0, i * 0x11);
                break;

            case MAINMENUMODE_MENURANK_51:
                var_s1 = temp_s2->unk_060[arg3][i];
                ptr = &evs_mem_data[var_s1];
                temp_t0_3 = &ptr->unk_64[arg3];
                func_8005D9A4_cn(&temp_s3->unk_3A8[i], menuRank->watchMenuRef, temp_s2->unk_078[arg3][i], ptr->unk_01,
                                 temp_t0_3->unk_4, temp_t0_3->unk_0, 0, i * 0x11);
                break;

            case MAINMENUMODE_MENURANK_52:
                var_s1 = temp_s2->unk_090[arg3][i];
                ptr = &evs_mem_data[var_s1];
                temp_t0_4 = &ptr->unk_7C[arg3];
                func_8005DAE4_cn(&temp_s3->unk_3A8[i], menuRank->watchMenuRef, temp_s2->unk_0A8[arg3][i], ptr->unk_01,
                                 temp_t0_4->unk_0, temp_t0_4->unk_4, temp_t0_4->unk_8, arg3, 0, i * 0x11);
                break;

            case MAINMENUMODE_MENURANK_53:
                var_s1 = temp_s2->unk_0C0[i];
                ptr = &evs_mem_data[var_s1];
                var_s7 = temp_s2->unk_0D0;
                var_s6 = temp_s2->unk_0C8;
                var_s4 = ptr->unk_A0;
                break;

            case MAINMENUMODE_MENURANK_54:
                var_s1 = temp_s2->unk_0E0[i];
                ptr = &evs_mem_data[var_s1];
                var_s7 = temp_s2->unk_0F0;
                var_s6 = temp_s2->unk_0E8;
                var_s4 = ptr->unk_A4;
                break;

            case MAINMENUMODE_MENURANK_56:
                var_s1 = temp_s2->unk_100[i];
                ptr = &evs_mem_data[var_s1];
                var_s7 = temp_s2->unk_110;
                var_s6 = temp_s2->unk_108;
                var_s4 = ptr->unk_A8;
                break;

            case MAINMENUMODE_MENURANK_57:
                var_s1 = temp_s2->unk_120[i];
                ptr = &evs_mem_data[var_s1];
                var_s7 = temp_s2->unk_130;
                var_s6 = temp_s2->unk_128;
                var_s4 = ptr->unk_AC;
                break;

            case MAINMENUMODE_MENURANK_58:
                var_s1 = temp_s2->unk_140[i];
                ptr = &evs_mem_data[var_s1];
                var_s7 = temp_s2->unk_150;
                var_s6 = temp_s2->unk_148;
                var_s4 = ptr->unk_B0;
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
                func_8005DC98_cn(&temp_s3->unk_3A8[i], menuRank->watchMenuRef, var_s6[i], ptr->unk_01, var_s7[var_s1],
                                 var_s4[0], var_s4[1], 0, i * 0x11);
                break;

            default:
                break;
        }
    }

    func_8005E76C_cn(menuRank, arg1);
    menuRank->unk_04F4.unk_08 = arg3;
}
#endif

#if VERSION_US || VERSION_CN
const s32 _lr_10544[][2] = {
    { 0x23, 0x1E },
    { 0xDD, 0x1E },
};
#endif

#if VERSION_US || VERSION_CN
void menuRank_init(MenuRank *menuRank, struct_watchMenu *watchMenuRef, struct_watchMenu_unk_02470 **arg2 UNUSED) {
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
#endif

#if VERSION_US
void menuRank_input(MenuRank *menuRank) {
    MenuRank_unk_590 *temp_s0 = &menuRank->unk_590[menuRank->unk_0014];
    u16 pressedButton = _getKeyTrg(menuRank->watchMenuRef, 0);
    s32 direction;
    SndIndex sndIndex;

    _getKeyRep(menuRank->watchMenuRef, 0);
    direction = 0;
    sndIndex = SND_INDEX_INVALID;
    if ((menuRank->unk_032C.unk_38 == 0.0f) && (menuRank->unk_032C.unk_3C < 0.0f)) {
        func_800585BC(menuRank, 1, 0.0f);
    }

    if (!(temp_s0->unk_3A8[0].unk_008.unk_04.unk_14 < 1.0f) && !(temp_s0->unk_3A8[0].unk_008.unk_04.unk_18 < 0.0f) &&
        !(temp_s0->unk_3A8[0].unk_008.unk_04.unk_38 < 1.0f) && !(temp_s0->unk_3A8[0].unk_008.unk_04.unk_3C < 0.0f)) {
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
            func_800586A4(menuRank, menuRank->unk_0014, -1, 1.0f, -(direction * 0x140));
            menuRank->unk_0018 = menuRank->unk_0014;
            menuRank->unk_0014 = (menuRank->unk_0014 + 1) & 1;
            menuRank_setPanel(menuRank, menuRank->unk_0014, menuRank->unk_0004, menuRank->unk_000C);
            func_800585BC(menuRank, -1, 1.0f);
            func_800586A4(menuRank, menuRank->unk_0014, 1, 0.0f, direction * 0x140);
        }

        if (sndIndex > SND_INDEX_INVALID) {
            dm_snd_play(sndIndex);
        }
    }
}
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", menuRank_input);
#endif

#if VERSION_US
void menuRank_update(MenuRank *menuRank) {
    MenuItem *temp_v0 = _getRootItem(menuRank->watchMenuRef);
    s32 i;

    func_800464BC(&menuRank->unk_017C, temp_v0);
    func_800464F8(&menuRank->unk_020C[i], ARRAY_COUNT(menuRank->unk_020C), temp_v0);

    func_800464BC(&menuRank->unk_032C, temp_v0);

    func_800578C8(&menuRank->unk_03BC, temp_v0);
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
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", menuRank_update);
#endif

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", RO_800B1430);
#endif

extern s32 _dir_10660[];
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/main_menu", _dir_10660);
#endif

#if VERSION_US
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
            menuRank->unk_04F4.unk_08 = menuRank->unk_0010;
        } else {
            menuRank->unk_04F4.unk_08 = menuRank->unk_000C;
        }

        switch (menuRank->unk_0004) {
            case MAINMENUMODE_MENURANK_50:
                menuRank->unk_0458.unk_08 = 1;
                menuRank->unk_04F4.unk_08 = menuRank->unk_04F4.unk_08 + 3;
                break;

            default:
                menuRank->unk_0458.unk_08 = 0;
                break;
        }

        menuRankLabel_draw((void *)sp18, 2, &gfx);

        for (i = 0; i < ARRAY_COUNTU(menuRank->unk_020C); i++) {
            MenuItem *temp_s0 = &menuRank->unk_020C[i];
            f32 temp_fs0 = temp_s0->unk_0C[0];
            f32 temp_fs1 = temp_s0->unk_0C[1];
            s32 var_v0 = (temp_s0->unk_3C < 0.0f) ? menuRank->unk_0010 : menuRank->unk_000C;

            j = WrapI(0, 3, var_v0 + _dir_10660[i]);
            if (menuRank->unk_0004 == MAINMENUMODE_MENURANK_50) {
                j += 3;
            }

            func_80046F58(temp_s0, &gfx, _getTexRank(menuRank->watchMenuRef, 4), 0, 2, i);
            temp_s0->unk_0C[0] += 12.0f;
            temp_s0->unk_0C[1] += 2.0f;

            func_80046F58(&menuRank->unk_020C[i], &gfx, _getTexRank(menuRank->watchMenuRef, 2), 0, 6, j);
            temp_s0->unk_0C[0] = temp_fs0;
            temp_s0->unk_0C[1] = temp_fs1;
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
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", menuRank_draw);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/main_menu", func_800599E0);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/main_menu", func_80059A58);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/main_menu", func_80059AA4);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/main_menu", func_80059AF0);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/main_menu", func_80059B5C);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/main_menu", func_80059BC8);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/main_menu", func_80059C34);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", func_8005F988_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", func_8005FA40_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", func_8005FA9C_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", func_8005FAF8_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", func_8005FB80_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", func_8005FC14_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", func_8005FCA8_cn);
#endif

/* drMarioRetrace? */
#if VERSION_US || VERSION_CN
void func_80059CA0(struct_watchMenu *watchMenuRef) {
    osRecvMesg(&watchMenuRef->unk_0000C, NULL, OS_MESG_BLOCK);
}
#endif

#if VERSION_US
Mtx **_getMtxPtr(struct_watchMenu *watchMenuRef) {
    return &watchMenuRef->unk_02448[gfx_gtask_no];
}
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", func_8005FD70_cn);
#endif

#if VERSION_US
Vtx **_getVtxPtr(struct_watchMenu *watchMenuRef) {
    return &watchMenuRef->unk_02454[gfx_gtask_no];
}
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", func_8005FD88_cn);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/main_menu", _getTexChar);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", _getTexChar);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/main_menu", _getTexCommon);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", _getTexCommon);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/main_menu", func_80059D14);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", func_8005FDC0_cn);
#endif

#if VERSION_US
TiTexData *_getTexLevel(struct_watchMenu *watchMenuRef, s32 index) {
    return &watchMenuRef->unk_02484[index];
}
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", _getTexLevel);
#endif

#if VERSION_US
TiTexData *_getTexMain(struct_watchMenu *watchMenuRef, s32 index) {
    return &watchMenuRef->unk_02488[index];
}
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", _getTexMain);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/main_menu", _getTexName);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", func_8005FDF0_cn);
#endif

#if VERSION_US
TiTexData *_getTexP2(struct_watchMenu *watchMenuRef, s32 index) {
    return &watchMenuRef->unk_02490[index];
}
#endif

#if VERSION_US
TiTexData *_getTexP4(struct_watchMenu *watchMenuRef, s32 index) {
    return &watchMenuRef->unk_02494[index];
}
#endif

#if VERSION_US
TiTexData *_getTexRank(struct_watchMenu *watchMenuRef, s32 index) {
    return &watchMenuRef->unk_02498[index];
}
#endif

#if VERSION_US
TiTexData *_getTexSetup(struct_watchMenu *watchMenuRef, s32 index) {
    return &watchMenuRef->unk_0249C[index];
}
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/main_menu", func_80059D94);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/main_menu", func_80059DA4);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/main_menu", func_80059DB4);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/main_menu", func_80059DC4);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/main_menu", func_80059DD4);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", func_8005FE00_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", _getTexP4);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", func_8005FE20_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", _getTexSetup);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", func_8005FE40_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", _getTexGameAl);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", func_8005FE60_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", func_8005FE70_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", func_8005FE80_cn);
#endif

#if VERSION_US
TiTexData *_getTexKasa(struct_watchMenu *watchMenuRef, s32 index) {
    return &watchMenuRef->unk_024B4[index];
}
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", func_8005FE90_cn);
#endif

#if VERSION_US
MenuItem *_getRootItem(struct_watchMenu *watchMenuRef) {
    return &watchMenuRef->unk_024B8[0];
}
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", _getRootItem);
#endif

#if VERSION_US
u16 _getKeyLvl(struct_watchMenu *watchMenuRef UNUSED, s32 arg1) {
    return gControllerHoldButtons[main_joy[arg1]];
}
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", func_8005FEA8_cn);
#endif

#if VERSION_US
u16 _getKeyTrg(struct_watchMenu *watchMenuRef UNUSED, s32 arg1) {
    return gControllerPressedButtons[main_joy[arg1]];
}
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", _getKeyTrg);
#endif

#if VERSION_US
u16 _getKeyRep(struct_watchMenu *watchMenuRef UNUSED, s32 arg1) {
    return joycur[main_joy[arg1]];
}
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", _getKeyRep);
#endif

#if VERSION_US
MainMenuMode _getMode(struct_watchMenu *watchMenuRef) {
    return watchMenuRef->unk_111CC;
}
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", _getMode);
#endif

#if VERSION_US || VERSION_CN
MainMenuMode _getModeOld(struct_watchMenu *watchMenuRef) {
    return watchMenuRef->unk_111C8;
}
#endif

#if VERSION_US
void _setMode(struct_watchMenu *watchMenuRef, MainMenuMode arg1) {
    watchMenuRef->unk_111D0 = arg1;
}
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu", _setMode);
#endif

#if VERSION_US || VERSION_CN
void _setNextMain(struct_watchMenu *watchMenuRef, enum_main_no arg1) {
    watchMenuRef->unk_111D4 = arg1;
}
#endif

#if VERSION_US || VERSION_CN
void menuTitle_setTitle(struct_watchMenu *watchMenuRef, MainMenuMode arg1) {
    func_80047420(&watchMenuRef->unk_02548, arg1);
}
#endif

#if VERSION_US || VERSION_CN
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
#endif

/**
 * Original name: menuAll_init
 */
#if VERSION_US || VERSION_CN
void menuAll_init(struct_watchMenu *arg0, UNK_PTR *arg1, struct_800EB670 *arg2) {
    UNK_PTR sp10 = *arg1;
    UNK_PTR temp_v0;
    s32 i;
    RomOffsetPair *pairArray = _romDataTbl;

    arg0->unk_00000 = arg2;
    arg0->unk_02460 = sp10;

    osCreateMesgQueue(&arg0->unk_0000C, arg0->unk_00024, ARRAY_COUNT(arg0->unk_00024));
    func_8002A184(arg2, &arg0->unk_00004, &arg0->unk_0000C);

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

    arg0->unk_111D4 = MAIN_NO_6;

#if VERSION_CN
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
    arg0->unk_02464 = sizeof(struct_watchMenu_unk_02470);

    for (i = 0; i < ARRAY_COUNTU(arg0->unk_02470); i++) {
        temp_v0 = ALIGN_PTR(sp10);
        arg0->unk_02468[i] = arg0->unk_02470[i] = temp_v0;
        sp10 = temp_v0 + arg0->unk_02464;
    }

    for (i = 0; i < ARRAY_COUNT(game_state_data); i++) {
        game_state_data[i].unk_000 = 0;
        game_state_data[i].unk_004 = 0;
    }

    evs_one_game_flg = 0;
    *arg1 = sp10;
}
#endif

#if VERSION_US || VERSION_CN
void func_8005A2AC(struct_watchMenu *arg0) {
    func_8002A1DC(arg0->unk_00000, &arg0->unk_00004);
    _menuAll_lastMode = arg0->unk_111CC;
}
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", RO_800C7AA8_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu", RO_800C7AB0_cn);
#endif

#if VERSION_US || VERSION_CN
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
#endif

#if VERSION_US || VERSION_CN
void menuAll_changeMenu(struct_watchMenu *arg0) {
    s32 index = arg0->unk_111C0;

    arg0->unk_02470[index] = arg0->unk_02468[index];
    bzero(arg0->unk_02470[index], arg0->unk_02464);
    arg0->unk_111E4 = 1;
    arg0->unk_111E8 = 1;
    arg0->unk_111EC = 0;
    arg0->unk_111F0 = 0;

    if (arg0->unk_111CC != MAINMENUMODE_MENUMAIN_0) {
        menuTitle_setTitle(arg0, arg0->unk_111CC);
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
#endif

#if VERSION_US || VERSION_CN
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
#endif

#if VERSION_US || VERSION_CN
void menuAll_update(struct_watchMenu *arg0) {
#if VERSION_CN
    s32 pad[2] UNUSED;
#endif
    MenuItem *var_v1 = &arg0->unk_024B8[0];
    MainMenuMode var_a0;
    f32 temp_f2_2;
    s32 i;
    s32 var_v1_2;

    arg0->unk_111DC = CLAMP(arg0->unk_111DC + arg0->unk_111E0, 0.0f, 1.0f);

    temp_f2_2 = (arg0->unk_111DC - 0.5) * 1.2 + 0.5;
    temp_f2_2 = 1.0 - CLAMP(temp_f2_2, 0.0f, 1.0f);

    for (i = 0; i < 3; i++) {
        var_v1->unk_6C[1][i] = temp_f2_2;
        var_v1->unk_6C[0][i] = temp_f2_2;
    }

#if VERSION_CN
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
#endif

#if VERSION_US || VERSION_CN
void menuAll_drawBg(struct_watchMenu *arg0, Gfx **gfxP) {
    Gfx *gfx = *gfxP;
    MenuItem *temp_s4 = &arg0->unk_024B8[0];
    TiTexData *temp_s3;
    s32 i;
    s32 var_s2;

    func_80046844(temp_s4, &gfx);
    draw_menu_bg(&gfx, temp_s4->unk_0C[0] + 0.0f, -temp_s4->unk_0C[1] - 120.0f);

    gSPDisplayList(gfx++, fade_normal_texture_init_dl);
    func_80046844(temp_s4, &gfx);

    var_s2 = 0;
    temp_s3 = _getTexCommon(arg0, 2);
    for (i = 0; i < 5; i++) {
        var_s2 += func_80046C74(temp_s4, &gfx, temp_s3, var_s2, i << 6, 0, 1.0f, 1.0f);
    }

    for (; i < 10; i++) {
        var_s2 += func_80046C74(temp_s4, &gfx, temp_s3, var_s2, (i - 5) << 6, 200.0f, 1.0f, -1.0f);
    }

    *gfxP = gfx;
}
#endif

#if VERSION_US || VERSION_CN
void menuAll_draw(struct_watchMenu *arg0, Gfx **gfxP) {
    s32 color;
    s32 i;

    arg0->unk_02448[gfx_gtask_no] = &arg0->unk_00048[gfx_gtask_no][0];
    arg0->unk_02454[gfx_gtask_no] = &arg0->unk_00C48[gfx_gtask_no][0];

    color = (((arg0->unk_111DC - 0.5) * 1.2) + 0.5) * 255.0;
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
#endif

#if VERSION_US || VERSION_CN
/**
 * Original name: main_menu
 */
enum_main_no main_menu(struct_800EB670 *arg0) {
    UNK_PTR sp10 = Heap_bufferp;
    struct_watchMenu *ptr = ALIGN_PTR(Heap_bufferp);
    s32 i;

    if (main_old == MAIN_NO_3) {
        _menuAll_lastMode = MAINMENUMODE_MENUMAIN_0;
        _menuMain_lastMode = MAINMENUMODE_MENUMAIN_0;
        _menuMain_lastDepth = 0;
        _menuMain_lastSelect[0] = 0;
    }

    func_80040A64();
    sp10 = &ptr[1];
    bzero(ptr, sizeof(struct_watchMenu));
    watchMenu = ptr;
    menuAll_init(ptr, &sp10, arg0);

    evs_playmax = joyResponseCheck();

    for (i = 0; i < ARRAY_COUNT(joyflg); i++) {
        joyflg[i] = U_JPAD | L_JPAD | R_JPAD | D_JPAD | L_TRIG | R_TRIG;
    }

    joycur1 = 0x18;
    joycur2 = 6;
    gGfxHead = gGfxGlist[gfx_gtask_no];
    dm_seq_play(SEQ_INDEX_12);

    while ((ptr->unk_111D4 == MAIN_NO_6) || (ptr->unk_111DC < 1.0f)) {
        if (graphic_no == GRAPHIC_NO_0) {
            while ((pendingGFX != 0) || (func_80040BA4() != 0)) {
                func_80059CA0(ptr);
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

#if VERSION_CN
            while (D_80092F10_cn) {
                func_80059CA0(ptr);
                joyProcCore();
                graphic_no = GRAPHIC_NO_0;
                dm_audio_update();
            }
#endif
        }

        func_80059CA0(ptr);
#if VERSION_CN
        func_8002BC30_cn(1);
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

#if VERSION_CN
        func_8002BD04_cn();
#endif
    }

    graphic_no = GRAPHIC_NO_5;

    while (ptr->unk_111F4 != 0xF) {
        osRecvMesg(&ptr->unk_0000C, NULL, OS_MESG_BLOCK);
        dm_audio_update();
    }

    graphic_no = GRAPHIC_NO_0;
    dm_seq_stop();

    while ((pendingGFX != 0) || !func_8002B178() || (func_80040BA4() != 0)) {
        osRecvMesg(&ptr->unk_0000C, NULL, OS_MESG_BLOCK);
        dm_audio_update();
    }

    func_8005A2AC(ptr);
    func_80040AE4();

    return ptr->unk_111D4;
}
#endif

#if VERSION_US || VERSION_CN
void graphic_menu(void) {
    struct_watchMenu *ptr = watchMenu;

    if ((ptr->unk_111D4 != MAIN_NO_6) && (ptr->unk_111DC == 1.0f)) {
        osSetThreadPri(NULL, 0xF);
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

    osSetThreadPri(NULL, 0xF);
    F3RCPinitRtn();
    F3ClearFZRtn(0);
    menuAll_draw(ptr, &gGfxHead);

#if VERSION_CN
    if (ptr->unk_cn_pad != 0) {
        func_8002BD7C_cn(&gGfxHead, 0x20, 0xB4);
    }
#endif

    osSetThreadPri(NULL, 0x7F);
}
#endif

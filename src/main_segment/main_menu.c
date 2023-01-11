/**
 * Original filename: main_menu.c
 */

#include "ultra64.h"
#include "include_asm.h"
#include "macros_defines.h"
#include "unknown_structs.h"
#include "main_segment_functions.h"
#include "main_segment_variables.h"
#include "boot_functions.h"
#include "boot_variables.h"
#include "rom_offsets.h"
#include "audio/audio_stuff.h"
#include "buffers.h"
#include "libc/assert.h"

f32 func_80045DD0(f32 arg0, f32 arg1) {
    return CLAMP(arg0 + arg1, 0.0f, 1.0f);
}

f32 func_80045E18(f32 arg0, f32 arg1) {
    return WrapF(0.0f, 1.0f, arg0 + arg1);
}

f32 func_80045E48(f32 arg0) {
    if (arg0 < 0.5) {
        arg0 = SQ(arg0);
    } else {
        arg0 = 1.0 - arg0;
        arg0 = 0.5 - SQ(arg0);
    }

    return 2.0f * arg0;
}

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80045E94);

void transFunc_curve(MenuItem *item) {
    u32 i;
    f32 temp_ft0;
    f32 temp_fv0;

    temp_fv0 = func_80045DD0(item->unk_14, item->unk_18);
    temp_ft0 = func_80045E48(temp_fv0);
    item->unk_14 = temp_fv0;

    for (i = 0; i < 2U; i++) {
        item->unk_0C[i] = item->unk_1C[i] + ((item->unk_24[i] - item->unk_1C[i]) * temp_ft0);
    }
}

void transFunc_finger(MenuItem *item) {
    u32 i;
    f32 temp_fv0;
    f32 temp_fv0_2;

    temp_fv0 = func_80045E18(item->unk_14, item->unk_18);
    temp_fv0_2 = (sinf(temp_fv0 * (2 * M_PI)) + 1.0) * 0.5;
    item->unk_14 = temp_fv0;

    for (i = 0; i < 2U; i++) {
        item->unk_0C[i] = item->unk_1C[i] + (item->unk_24[i] - item->unk_1C[i]) * temp_fv0_2;
    }
}

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80046008);

void scaleFunc_curve(MenuItem *arg0) {
    u32 i;
    f32 temp_ft0;
    f32 temp_fv0;

    temp_fv0 = func_80045DD0(arg0->unk_38, arg0->unk_3C);
    temp_ft0 = func_80045E48(temp_fv0);
    arg0->unk_38 = temp_fv0;

    for (i = 0; i < 2U; i++) {
        arg0->unk_30[i] = arg0->unk_40[i] + ((arg0->unk_48[i] - arg0->unk_40[i]) * temp_ft0);
    }
}

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_800460DC);

void colorFunc_curve(MenuItem *arg0) {
    u32 i;
    f32 temp_ft0;
    f32 temp_fv0;

    temp_fv0 = func_80045DD0(arg0->unk_64, arg0->unk_68);
    temp_ft0 = func_80045E48(temp_fv0);
    arg0->unk_64 = temp_fv0;

    for (i = 0; i < 4U; i++) {
        arg0->color.arr[i] = arg0->unk_6C[0][i] + ((arg0->unk_6C[1][i] - arg0->unk_6C[0][i]) * temp_ft0);
    }
}

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", colorFunc_cursor);

const f32 color_251[] = {
    0.5f,
    0.5f,
    0.5f,
    1.0f,
};

INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", fade_normal_texture_init_dl);

extern const Gfx fade_alpha_texture_init_dl[];
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", fade_alpha_texture_init_dl);

extern const Gfx fade_intensity_texture_init_dl[];
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", fade_intensity_texture_init_dl);

extern const Gfx fade_fillrect_init_dl[];
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", fade_fillrect_init_dl);

extern const Gfx fade_shadow_texture_init_dl[];
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", fade_shadow_texture_init_dl);

INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800ADD00);

ASM_RODATA;

const u8 _timeAttack_levelTable[] = {
    0x06,
    0x09,
    0x0C,
    0x00,
};

INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", STR_800ADD40);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", STR_800ADD60);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", STR_800ADD80);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", STR_800ADDBC);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", STR_800ADDF0);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", STR_800ADF2C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", STR_800AE070);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", STR_800AE1D8);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", STR_800AE33C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", STR_800AE4C8);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", STR_800AE5E8);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", STR_800AE650);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", STR_800AE66C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", STR_800AE794);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", STR_800AE898);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", STR_800AE9B8);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", STR_800AE9CC);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", STR_800AEB3C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", STR_800AED50);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", STR_800AEEA4);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", STR_800AEED0);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", STR_800AEF04);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", STR_800AEF38);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", STR_800AEF74);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", STR_800AEFE0);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", STR_800AF014);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", STR_800AF048);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", STR_800AF070);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", STR_800AF09C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", STR_800AF0CC);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", STR_800AF0FC);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", STR_800AF134);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", STR_800AF16C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", STR_800AF18C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", STR_800AF1BC);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", STR_800AF234);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", STR_800AF268);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", STR_800AF29C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", STR_800AF2E0);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", STR_800AF304);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", STR_800AF324);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", STR_800AF390);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", STR_800AF3C4);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", STR_800AF3F8);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", STR_800AF42C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", STR_800AF460);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", STR_800AF498);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", STR_800AF4C4);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", STR_800AF4EC);

extern const u8 _gameLvItemColor[][2][4];
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", _gameLvItemColor);

extern u8 _musicItemColor[][4];
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", _musicItemColor);

extern const u8 RO_800AF530[];
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800AF530);

ASM_TEXT;

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
        item->unk_6C[0][i] = color_251[i];
        item->color.arr[i] = 1.0f;
        item->unk_6C[1][i] = 1.0f;
    }

    item->unk_8C &= ~0x80000000;
    item->unk_8C &= ~0x40000000;
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

        item->unk_0C[i] = item->unk_0C[i] * parent->unk_30[i] + parent->unk_0C[i];

        temp_ft0 = item->unk_30[i] * parent->unk_30[i];
        item->unk_30[i] = temp_ft0;
        item->unk_0C[i] = item->unk_0C[i] - (item->unk_00[i] * temp_ft0);
    }
}

/**
 * Original name: menuItem_updateColor
 */
void menuItem_updateColor(MenuItem *item, MenuItem *parent) {
    u32 i;

    item->colorCallback(item);

    if (parent == NULL) {
        return;
    }

    if (!(item->unk_8C & 0x80000000)) {
        for (i = 0; i < 3U; i++) {
            item->color.arr[i] *= parent->color.arr[i];
        }
    }

    if (!(item->unk_8C & 0x40000000)) {
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

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80046614);

void func_80046670(MenuItem *item, f32 arg1, f32 arg2) {
    item->unk_1C[0] = arg1;
    item->unk_1C[1] = arg2;
}

void func_8004667C(MenuItem *item, f32 arg1, f32 arg2) {
    item->unk_24[0] = arg1;
    item->unk_24[1] = arg2;
}

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80046688);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80046694);

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

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_800466D0);

void func_80046734(MenuItem *item, f32 arg0, f32 arg1, f32 arg2) {
    f32 sp10[] = { arg0, arg1, arg2 };
    s32 i;

    item->unk_68 = 0.03125f;
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
    Color_RGBA32 color;

    GET_COLOR_RGBA32_FROM_COLOR_RGBAF32(&color, &item->color);

    gDPSetPrimColor(gfx++, 0, 0, color.r, color.g, color.b, color.a);

    *gfxP = gfx;
}

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

bool menuItem_drawTex(MenuItem *item, Gfx **gfxP, TiTexDataEntry *arg2, s32 arg3) {
    if (menuItem_outOfScreen(item, arg2->unk_4[0], arg2->unk_4[1])) {
        return false;
    }

    func_80046844(item, gfxP);
    if (arg2->unk_4[3] & 1) {
        tiStretchTexBlock(gfxP, &arg2->unk_0, arg3, item->unk_0C[0], item->unk_0C[1], arg2->unk_4[0] * item->unk_30[0],
                          arg2->unk_4[1] * item->unk_30[1]);
    } else {
        tiStretchTexTile(gfxP, arg2, arg3, 0, 0, arg2->unk_4[0], arg2->unk_4[1], item->unk_0C[0], item->unk_0C[1],
                         arg2->unk_4[0] * item->unk_30[0], arg2->unk_4[1] * item->unk_30[1]);
    }
    return true;
}

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
INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80046C74);
#endif

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", menuItem_drawAlphaTex);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80046F58);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80047074);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004714C);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_800472D0);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80047420);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_800474EC);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80047584);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", menuTitle_draw);

INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", _menuCursor_cursor_4_pattern);

extern f32 _color_1040[][3];
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", _color_1040);

INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", _pnts_1106);

void func_80047720(MenuCursor *cursor, s32 arg1, s32 arg2) {
    cursor->unk_140.transCallback = transFunc_finger;
    cursor->unk_140.unk_18 = 0.03125f;
    func_8004667C(&cursor->unk_140, arg1, arg2);
    func_80046670(&cursor->unk_140, arg1 - 8, arg2);
}

void func_800477BC(MenuCursor *cursor, s32 arg1, s32 arg2) {
    func_8004667C(&cursor->unk_1D0, arg1, arg2);
    func_80046670(&cursor->unk_1D0, arg1, arg2);
}

void menuCursor_init2(MenuCursor *cursor, struct_watchMenu *arg1, u32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6,
                      s32 arg7, s32 arg8, s32 arg9) {
    MenuItem *temp_s1;
    u32 i;

    if (arg2 < 2U) {
        arg2 = 3;
    }

    cursor->unk_000 = arg1;
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

    temp_s1 = &cursor->unk_0B0;
    menuItem_init(temp_s1, 0, 0);
    func_80046734(temp_s1, _color_1040[arg5 % 4U][0], _color_1040[arg5 % 4U][1], _color_1040[arg5 % 4U][2]);
    if (arg2 == 3) {
        for (i = 0; i < ARRAY_COUNTU(*temp_s1->unk_6C); i++) {
            temp_s1->unk_6C[0][i] = temp_s1->unk_6C[1][i];
        }
    }

    menuItem_init(&cursor->unk_140, 0, 0);
    func_80047720(cursor, -0x14, arg9 - 0xE);

    menuItem_init(&cursor->unk_1D0, 0, 0);
    func_800477BC(cursor, -0x10, arg9 - 0x16);
}

void func_800479A8(MenuCursor *cursor, struct_watchMenu *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6,
                   s32 arg7) {
    menuCursor_init2(cursor, arg1, arg2, 4, 0, arg3, arg4, arg5, arg6, arg7);
}

void menuCursor_update(MenuCursor *cursor, MenuItem *arg1) {
    MenuItem *var_a0;
    u32 i;

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

#if 0
extern ? _menuCursor_cursor_4_pattern;
extern ? _pnts_1106;

void menuCursor_draw1(void **arg0, s32 arg1, Gfx **arg2) {
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
    void **sp6C;
    s32 sp74;
    Gfx **sp7C;
    s32 sp84;
    void **spB4;
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
    MenuItem *temp_s2;
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
    s32 var_s6;
    s32 var_s7;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v0_3;
    s32 var_v0_4;
    s32 var_v1;
    s32 var_v1_2;
    s32 var_v1_3;
    s32 var_v1_4;
    u16 temp_v1_2;
    u32 temp_a0_2;
    u32 var_a0;
    u32 var_s4;
    void **var_t4;
    void *temp_a1;
    void *temp_s1;
    void *temp_t1;
    void *temp_v0_8;
    void *temp_v1_3;

    var_s0 = saved_reg_s0;
    var_s5 = saved_reg_s5;
    var_s6 = saved_reg_s6;
    sp74 = arg1;
    sp6C = arg0;
    sp7C = arg2;
    var_s4 = 0;
    temp_v1 = *sp7C;
    sp60 = temp_v1 + 8;
    temp_v1->words.w0 = 0xDE000000;
    temp_v1->words.w1 = (u32) fade_normal_texture_init_dl;
    sp60 = temp_v1 + 0x10;
    temp_v1->unk_8 = 0xE200001C;
    temp_v1->unk_C = 0x504240;
    sp60 = temp_v1 + 0x18;
    temp_v1->unk_10 = 0xE3001001;
    temp_v1->unk_14 = 0;
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
                temp_s2 = temp_s1 + 0xB0;
                if (temp_s1->unk_1C < 0) {
                    var_t4 = spB4 + 4;
                    if (var_s4 == temp_s1->unk_4) {
                        if (menuItem_outOfScreen(temp_s2, temp_s1->unk_14, temp_s1->unk_18) == false) {
                            if (var_s4 == 3) {
                                if (!(temp_s1->unk_1C & 0x10000000)) {
                                    var_s0 = 3;
                                } else {
                                    var_s0 = *(&_menuCursor_cursor_4_pattern + ((s32) (temp_s1->unk_114 * 29.0f) * 4)) + 3;
                                }
                                if (var_s0 != sp84) {
                                    sp84 = var_s0;
                                    var_s7 = 0;
                                }
                            }
                            if (var_s7 == 0) {
                                temp_a0 = sp60;
                                var_s6 = _getTexCommon(temp_s1->unk_0, var_s0);
                                temp_a0->words.w0 = 0xFD900000;
                                temp_a0->unk_8 = 0xF5900000;
                                temp_a0->unk_10 = 0xE6000000;
                                temp_a0->unk_C = 0x07080200;
                                temp_a0->unk_14 = 0;
                                temp_a0->unk_18 = 0xF3000000;
                                temp_a0->words.w1 = var_s6->unk_0->unk_4;
                                temp_a1 = var_s6->unk_4;
                                sp60 = temp_a0 + 8;
                                sp60 = temp_a0 + 0x10;
                                temp_v0 = temp_a0 + 0x18;
                                sp60 = temp_v0;
                                sp60 = temp_a0 + 0x20;
                                temp_v1_2 = temp_a1->unk_0;
                                var_a2 = 0x800;
                                temp_a0_2 = temp_v1_2 >> 4;
                                if (temp_a0_2 != 0) {
                                    var_a2 = temp_a0_2 + 0x7FF;
                                }
                                var_v1 = ((s32) ((temp_v1_2 * temp_a1->unk_2) + 3) >> 2) - 1;
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
                                temp_a0_3->unk_C = 0x80200;
                                temp_a0_3->unk_10 = 0xF2000000;
                                temp_a0_3->unk_8 = (s32) (((((s32) (((u16) var_s6->unk_4->unk_0 >> 1) + 7) >> 3) & 0x1FF) << 9) | 0xF5800000);
                                temp_v1_3 = var_s6->unk_4;
                                sp60 = temp_a0_3 + 0x18;
                                var_s7 += 1;
                                temp_a0_3->unk_14 = (s32) (((((temp_v1_3->unk_0 - 1) * 4) & 0xFFF) << 0xC) | (((temp_v1_3->unk_2 - 1) * 4) & 0xFFF));
                            }
                            func_80046844(temp_s2, &sp60);
                            if (var_s4 == 3) {
                                sp10 = (s32) ((temp_s2->unk_0C[0] * 4.0f) - (f32) (var_s5 * 2));
                                var_v1_2 = temp_s1->unk_14 + var_s5;
                            } else {
                                var_v1_2 = temp_s1->unk_14;
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
                                var_v1_3 = temp_s1->unk_18 + var_s5;
                            } else {
                                var_v1_3 = temp_s1->unk_18;
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
                                    temp_t1 = (var_s0 << 5) + &_pnts_1106;
                                    temp_a3 = sp60;
                                    temp_v0_2 = &(&sp10)[temp_t1->unk_8];
                                    temp_t0 = temp_a3 + 8;
                                    sp60 = temp_t0;
                                    temp_v0_3 = &(&sp10)[temp_t1->unk_C];
                                    temp_a3->words.w0 = ((temp_v0_2->unk_0 & ((s32) ~temp_v0_2->unk_2 >> 0x1F) & 0xFFF) << 0xC) | ((temp_v0_3->unk_10 & ((s32) ~temp_v0_3->unk_12 >> 0x1F) & 0xFFF) | 0xE4000000);
                                    temp_v1_4 = &(&sp10)[temp_t1->unk_0];
                                    temp_v0_4 = &(&sp10)[temp_t1->unk_4];
                                    temp_a3->unk_8 = 0xE1000000;
                                    temp_a3->words.w1 = ((temp_v1_4->unk_0 & ((s32) ~temp_v1_4->unk_2 >> 0x1F) & 0xFFF) << 0xC) | (temp_v0_4->unk_10 & ((s32) ~temp_v0_4->unk_12 >> 0x1F) & 0xFFF);
                                    sp60 = temp_a3 + 0x10;
                                    temp_a2 = (&sp10)[temp_t1->unk_14].unk_30;
                                    temp_a0_8 = (&sp10)[temp_t1->unk_0].unk_2;
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
                                    temp_a0_9 = (&sp10)[temp_t1->unk_4].unk_10;
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
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", jtbl_800AF828);

/**
 * Original name: menuCursor_draw1
 */
INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", menuCursor_draw1);
#endif

INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", _type_1345);

/**
 * Original name: menuCursor_draw2
 */
#if 0
s32 func_8004714C(void *, void **, TiTexDataEntry *, TiTexDataEntry *, s32, s32, s32);
s32 menuItem_drawAlphaTex(void *, void **, s32, s32, s32);
extern ? D_800AF83C;

void menuCursor_draw2(void **arg0, s32 arg1, void **arg2) {
    void *sp20;
    void **sp2C;
    TiTexDataEntry *temp_s1_2;
    s32 temp_s1;
    s32 temp_v0;
    s32 temp_v1_2;
    s32 var_s2;
    s32 var_s3;
    s32 var_s4_2;
    s32 var_v0;
    void **var_s4;
    void **var_s5;
    void *temp_s0;
    void *temp_s0_2;
    void *temp_v1;

    sp2C = arg2;
    temp_v1 = *arg2;
    var_s3 = 0;
    var_s2 = 0;
    sp20 = temp_v1 + 8;
    temp_v1->unk_0 = 0xDE000000;
    temp_v1->unk_4 = fade_alpha_texture_init_dl;
    if (arg1 > 0) {
        var_s4 = arg0;
        do {
            temp_s0 = *var_s4;
            if (temp_s0->unk_1C & 0x40000000) {
                temp_s1 = _getTexCommon(temp_s0->unk_0, 1);
                var_s3 += menuItem_drawAlphaTex(temp_s0 + 0x140, &sp20, temp_s1, _getTexCommon(temp_s0->unk_0, 0), var_s3);
            }
            var_s2 += 1;
            var_s4 += 4;
        } while (var_s2 < arg1);
        var_s2 = 0;
        var_s3 = 0;
    }
    do {
        var_s4_2 = 0;
        if (arg1 > 0) {
            var_s5 = arg0;
            do {
                temp_s0_2 = *var_s5;
                temp_v0 = temp_s0_2->unk_10;
                if ((temp_v0 != 1) || (temp_v1_2 = temp_s0_2->unk_8, (temp_v1_2 != temp_v0)) || (var_v0 = 0xA, (temp_s0_2->unk_C != temp_v1_2))) {
                    var_v0 = *((temp_s0_2->unk_10 * 4) + ((temp_s0_2->unk_8 * 0x10) + &D_800AF83C));
                }
                if ((((((u32) temp_s0_2->unk_1C >> 0x1D) ^ 1) & 1) | (var_s2 != var_v0)) == 0) {
                    temp_s1_2 = _getTexSetup(temp_s0_2->unk_0, 8);
                    var_s3 += func_8004714C(temp_s0_2 + 0x1D0, &sp20, temp_s1_2, _getTexSetup(temp_s0_2->unk_0, 1), var_s3, 0xB, var_s2);
                }
                var_s4_2 += 1;
                var_s5 += 4;
            } while (var_s4_2 < arg1);
        }
        var_s2 += 1;
        var_s3 = 0;
    } while (var_s2 < 0xB);
    *sp2C = sp20;
}
#else
INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", menuCursor_draw2);
#endif

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80048634);

void func_80048680(MenuBottle *arg0, struct_watchMenu *arg1, s32 arg2, s32 arg3) {
    arg0->unk_000 = arg1;
    arg0->unk_004 = 0;
    menuItem_init(&arg0->unk_08, arg2, arg3);
    menuItem_init(&arg0->unk_98, 4, 0x10);
}

void func_800486C8(MenuBottle *arg0, MenuItem *arg1) {
    func_800464BC(&arg0->unk_08, arg1);
    func_800464BC(&arg0->unk_98, &arg0->unk_08);
}

extern u16 cap_pos_1442[][0xD];

INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", cap_pos_1442);

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
    TiTexDataEntry *temp_t0;
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
INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", menuBottle_draw);
#endif

extern const f32 _lvGauge_step[];
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", _lvGauge_step);

extern const s32 _size_1542[][2];
extern const s32 _type_1543[];

INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", _size_1542);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", _type_1543);

extern s32 _yn_1691[][2];
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", _yn_1691);

ASM_TEXT;

void func_80048B8C(MenuLvGauge *arg0, struct_watchMenu *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    arg0->unk_000 = arg1;
    arg0->unk_004 = arg2;
    arg0->unk_008 = 0x14;
    arg0->unk_00C = arg4;
    menuItem_init(&arg0->unk_010, arg5, arg6);
    func_800479A8(&arg0->unk_0A0, arg1, _type_1543[arg2], arg3, -2, -2, _size_1542[arg2][0], _size_1542[arg2][1]);
}

void func_80048C48(MenuLvGauge *arg0, s32 arg1) {
    u16 keyRep = _getKeyRep(arg0->unk_000, arg1);
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

void func_80048CC8(MenuLvGauge *arg0, MenuItem *arg1) {
    func_800464BC(&arg0->unk_010, arg1);

    arg0->unk_0A0.unk_020.unk_24[0] = arg0->unk_0A0.unk_020.unk_1C[0] + (_lvGauge_step[arg0->unk_004] * arg0->unk_00C);

    menuCursor_update(&arg0->unk_0A0, &arg0->unk_010);
}

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", menuLvGauge_draw1);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80048FA0);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80049034);

void func_80049080(MenuYN *yn, s32 arg1, f32 arg2) {
    func_80046614(&yn->unk_008, arg1);
    yn->unk_008.unk_64 = arg2;
}

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_800490B8);

void menuYN_init(MenuYN *yn, struct_watchMenu *watchMenuRef, s32 arg2, s32 arg3) {
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
    yn->unk_418.unk_0B0.colorCallback = colorFunc_curve;

    a2 = 0.0f;

    yn->unk_418.unk_0B0.unk_6C[1][0] = a2;
    yn->unk_418.unk_0B0.unk_6C[0][0] = a2;
    yn->unk_418.unk_0B0.unk_6C[1][1] = a2;
    yn->unk_418.unk_0B0.unk_6C[0][1] = a2;
    yn->unk_418.unk_0B0.unk_6C[1][2] = a2;
    yn->unk_418.unk_0B0.unk_6C[0][2] = a2;
    yn->unk_418.unk_0B0.unk_6C[0][3] = a2;
    yn->unk_418.unk_0B0.unk_6C[1][3] = 0.627451f;
    func_80049080(yn, -1, a2);
}

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80049224);

void func_800492D8(MenuYN *yn, MenuItem *parentItem) {
    func_800464BC(&yn->unk_008, parentItem);
    func_800464F8(yn->unk_098, ARRAY_COUNT(yn->unk_098), &yn->unk_008);
    menuCursor_update(&yn->unk_1B8, &yn->unk_098[yn->unk_004]);
    menuCursor_update(&yn->unk_418, &yn->unk_008);
}

void menuYN_draw(MenuYN *yn, Gfx **gfxP) {
    MenuItem *item = &yn->unk_008;
    MenuCursor *sp18;
    Gfx *gfx;
    s32 i;

    gfx = *gfxP;
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

        for (j = 0; j < _yn_1767[i][j]; j += 2) {
            fontXX_draw(&gfx, var_fs0, item->unk_0C[1], 12.0f, 12.0f, &_yn_1767[i][j]);
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

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80049578);

void menuMes_init(MenuMes *mes, struct_watchMenu *watchMenuRef, struct_watchMenu_unk_02470 **arg2, s32 arg3, s32 arg4,
                  s32 arg5, s32 arg6) {
    struct_watchMenu_unk_02470 *temp_fp = *arg2;
    f32 a2;

    mes->watchMenuRef = watchMenuRef;
    menuItem_init(&mes->unk_004, arg5, arg6);
    func_800467E0(&mes->unk_004);
    msgWnd_init(&mes->unk_094, (void **)arg2, arg3, arg4, arg5, arg6);
    mes->unk_094.unk_24 = 1;
    mes->unk_094.unk_34 = 0xC;
    mes->unk_094.unk_30 = 0xC;
    mes->unk_094.unk_3C = 6;
    mes->unk_094.unk_48 = 0xE;
    func_800479A8(&mes->unk_174, watchMenuRef, 2, 0, -0x10, -0x10, mes->unk_094.unk_3C * arg3 * 2 + 0x20,
                  mes->unk_094.unk_48 * arg4 + 0x20);
    mes->unk_174.unk_0B0.colorCallback = colorFunc_curve;

    a2 = 0.0f;
    mes->unk_174.unk_0B0.unk_6C[1][0] = a2;
    mes->unk_174.unk_0B0.unk_6C[0][0] = a2;
    mes->unk_174.unk_0B0.unk_6C[1][1] = a2;
    mes->unk_174.unk_0B0.unk_6C[0][1] = a2;
    mes->unk_174.unk_0B0.unk_6C[1][2] = a2;
    mes->unk_174.unk_0B0.unk_6C[0][2] = a2;
    mes->unk_174.unk_0B0.unk_6C[0][3] = a2;
    mes->unk_174.unk_0B0.unk_6C[1][3] = 0.627451f;
    func_80049540(mes, -1, a2);
    *arg2 = temp_fp;
}

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004970C);

void func_80049754(MenuMes *mes, MenuItem *parentItem) {
    func_800464BC(&mes->unk_004, parentItem);
    mes->unk_094.unk_28 = mes->unk_004.unk_0C[0];
    mes->unk_094.unk_2C = mes->unk_004.unk_0C[1];
    mes->unk_094.unk_74 = mes->unk_004.color.v.a * 255.0f;
    msgWnd_update(&mes->unk_094);
    menuCursor_update(&mes->unk_174, &mes->unk_004);
}

void func_800497D0(MenuMes *mes, Gfx **gfxP) {
    MenuCursor *sp10;
    Gfx *gfx;
    MessageWnd *msgWnd = &mes->unk_094;

    gfx = *gfxP;
    if (menuItem_outOfScreen(&mes->unk_004,
                             ((mes->unk_094.unk_38 - 2) * mes->unk_094.unk_3C) + mes->unk_094.unk_30 + 0xC,
                             ((mes->unk_094.unk_44 - 1) * mes->unk_094.unk_48) + mes->unk_094.unk_34 + 0xC)) {
        return;
    }

    sp10 = &mes->unk_174;
    func_80048634(&sp10, 1, &gfx);
    msgWnd_draw(msgWnd, &gfx);

    *gfxP = gfx;
}

void func_80049894(MenuSpeedAsk *arg0, struct_watchMenu *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    arg0->unk_0 = arg1;
    arg0->unk_4 = arg2;
    arg0->unk_8 = arg3;
    menuItem_init(&arg0->unk_C, arg4, arg5);
}

void func_800498C4(MenuSpeedAsk *arg0, MenuItem *arg1) {
    func_800464BC(&arg0->unk_C, arg1);
}

const char D_800AFB08[] = "Ｙｅｓ";
const char D_800AFB10[] = "Ｎｏ";

INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800AFB18);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800AFB1C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800AFB38);

extern s32 _size_1948[][2];
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", _size_1948);

extern s8 _pos_1959[][2];
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", _pos_1959);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", menuSpeedAsk_draw);

void menuSpeedItem_init(MenuSpeedItem *arg0, struct_watchMenu *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6,
                        s32 arg7) {
    s32 i;
    s8 temp_s6;
    s8 temp_s7;
    s32 temp1;
    s32 temp2;

    arg0->unk_000 = arg1;
    arg0->unk_004 = arg2;
    arg0->unk_00C = 1;
    arg0->unk_010 = 0;
    arg0->unk_008 = arg4;
    menuItem_init(&arg0->unk_014, arg5, arg6);

    for (i = 0; i < ARRAY_COUNTU(arg0->unk_0A4); i++) {
        menuItem_init(&arg0->unk_0A4[i], arg7 * i, 0);
    }

    temp_s7 = _pos_1959[arg2][0];
    temp_s6 = _pos_1959[arg2][1];

    for (i = 0; i < ARRAY_COUNTU(arg0->unk_254); i++) {
        MenuItem *item = &arg0->unk_254[i];
        s32 j;

        menuItem_init(item, temp_s7, temp_s6);

        item->colorCallback = colorFunc_cursor;
        item->unk_68 = 0.03125f;

        for (j = 0; j < ARRAY_COUNTU(item->unk_6C); j++) {
            s32 k;

            for (k = 0; k < ARRAY_COUNTU(item->unk_6C[j]); k++) {
                item->unk_6C[j][k] = _gameLvItemColor[i][j][k] * (1.0 / 0xFF);
            }
        }
    }

    temp1 = _size_1948[arg2][0];
    temp2 = _size_1948[arg2][1];
    func_800479A8(&arg0->unk_404, arg1, _type_1949[arg2], arg3, -1, -1, temp1, temp2);
}

void func_80049C54(MenuSpeedItem *arg0, s32 arg1) {
    u16 keyRep = _getKeyRep(arg0->unk_000, arg1);
    s32 var_s0;
    s32 temp;

    temp = 0;
    if (keyRep & L_JPAD) {
        temp--;
    }
    if (keyRep & R_JPAD) {
        temp++;
    }

    var_s0 = CLAMP(arg0->unk_008 + temp, 0, 2U);
    if (var_s0 != arg0->unk_008) {
        dm_snd_play(SND_INDEX_63);
        arg0->unk_008 = var_s0;
    }
}

void menuSpeedItem_update(MenuSpeedItem *arg0, MenuItem *arg1) {
    u32 i;

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

void menuSpeedItem_draw1(MenuSpeedItem **speedItemP, s32 count, Gfx **gfxP) {
    Gfx *gfx = *gfxP;
    TiTexDataEntry *var_s7;
    MenuSpeedItem *speedItem;
    MenuItem *item;
    s32 var_s6;
    s32 index;
    s32 i;
    u32 j;

    gSPDisplayList(gfx++, fade_normal_texture_init_dl);

    var_s6 = 0;
    for (index = 0; index < count; index++) {
        speedItem = speedItemP[index];
        item = &speedItem->unk_0A4[2];

        if ((speedItem->unk_004 == 3) && (speedItem->unk_010 != 0)) {
            var_s7 = _getTexSetup(speedItem->unk_000, 15);
            var_s6 += menuItem_drawTex(item, &gfx, var_s7, var_s6);
        }
    }

    gSPDisplayList(gfx++, fade_intensity_texture_init_dl);

    var_s6 = 0;
    for (index = 0; index < count; index++) {
        speedItem = speedItemP[index];
        item = &speedItem->unk_254[2];

        if ((speedItem->unk_004 == 3) && (speedItem->unk_010 != 0)) {
            var_s7 = _getTexSetup(speedItem->unk_000, 23);
            var_s6 += menuItem_drawTex(item, &gfx, var_s7, var_s6);
        }
    }

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 3U; j++) {
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
                            var_s7 = _getTexP4(speedItem->unk_000, j + 6);
                            break;

                        case 1:
                            var_s7 = _getTexSetup(speedItem->unk_000, j + 24);
                            break;

                        case 2:
                            var_s7 = _getTexP4(speedItem->unk_000, j + 3);
                            break;

                        case 3:
                            var_s7 = _getTexSetup(speedItem->unk_000, j + 20);
                            break;
                    }

                    var_s6 += menuItem_drawTex(item, &gfx, var_s7, var_s6);
                }
            }
        }
    }

    *gfxP = gfx;
}

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004A160);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004A1F4);

void menuMusicItem_init(MenuMusicItem *arg0, struct_watchMenu *arg1, s32 arg2, s32 arg3, s32 arg4) {
    u32 i;

    arg0->unk_000 = arg1;
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
        var_s0_2->unk_68 = 0.03125f;

        for (j = 0; j < 2U; j++) {
            u32 k;

            for (k = 0; k < 4U; k++) {
                var_s0_2->unk_6C[j][k] = _musicItemColor[j][k] * (1.0 / 255.0);
            }
        }
    }

    func_800479A8(&arg0->unk_640, arg1, 5, 0, -1, -1, 0x25, 0x10);
    arg0->unk_640.unk_01C.b.unk_31 = 0;
}

extern const s32 _seq_2327[];
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", _seq_2327);

void menuMusicItem_input(MenuMusicItem *arg0, s32 arg1) {
    s32 temp_a0;
    s32 var_s0;
    u16 temp_s2;
    s32 temp;
    s32 temp2;

    temp_s2 = _getKeyRep(arg0->unk_000, arg1);
    temp2 = arg0->unk_008;
    temp_a0 = arg0->unk_004;
    temp = 0;
    if (temp2 != temp_a0) {
        if (temp_a0 < 4U) {
            dm_seq_play_fade((_seq_2327[temp_a0]), 0x14);
        } else {
            dm_seq_stop();
        }
        arg0->unk_008 = arg0->unk_004;
    }

    if (temp_s2 & 0x200) {
        temp--;
    }
    if (temp_s2 & 0x100) {
        temp++;
    }

    var_s0 = CLAMP(arg0->unk_004 + temp, 0, 4);
    if (var_s0 != arg0->unk_004) {
        dm_snd_play(SND_INDEX_63);
        arg0->unk_004 = var_s0;
    }
}

void menuMusicItem_update(MenuMusicItem *arg0, MenuItem *arg1) {
    u32 i;

    func_800464BC(&arg0->unk_010, arg1);
    func_800464F8(arg0->unk_0A0, ARRAY_COUNT(arg0->unk_0A0), &arg0->unk_010);

    for (i = 0; i < 5U; i++) {
        MenuItem *temp_s0_2 = &arg0->unk_370[i];
        f32 *var_a1;
        u32 j;

        func_800464BC(temp_s0_2, &arg0->unk_0A0[i]);
        if (i == arg0->unk_004) {
            if (!arg0->unk_00C.b.unk_31) {
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

    menuCursor_update(&arg0->unk_640, &arg0->unk_0A0[arg0->unk_004]);
}

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", menuMusicItem_draw1);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004A780);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004A814);

INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800AFBB0);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800AFBD8);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800AFBE0);

extern const s32 _posDesc_2860[][2];
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", _posDesc_2860);

extern const s32 _posLine_2861[][2];
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", _posLine_2861);

INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", _line_2914);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800AFC20);

extern const s32 _panel_3220[];
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", _panel_3220);

ASM_TEXT;

void func_8004A860(MenuNumber *arg0, struct_watchMenu *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    arg0->unk_00 = arg1;
    arg0->unk_04 = arg2;
    arg0->unk_08 = arg3;
    arg0->unk_0C = arg4;
    arg0->unk_10 |= 0x80000000;
    bzero(&arg0->unk_14, sizeof(MenuNumber_unk_14));
    menuItem_init(&arg0->unk_1C, arg5, arg6);
}

void menuNumber_update(MenuNumber *arg0, MenuItem *arg1) {
    s32 var_a3 = arg0->unk_0C;
    s32 i;

    for (i = arg0->unk_08 - 1; i >= 0; i--) {
        arg0->unk_14.unk_0[i] = var_a3 % 10;
        var_a3 /= 0xA;
    }
    func_800464BC(&arg0->unk_1C, arg1);
}

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", menuNumber_draw);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004AC98);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004ACF4);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004AD10);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004AD3C);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004AD84);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004ADC4);

extern const f32 RO_800AFBE0[3];

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
            var_v1_5->unk_6C[1][j] = RO_800AFBE0[j];
            var_v1_5->unk_6C[0][j] = RO_800AFBE0[j];
        }
    }
}

void func_8004B2C8(MenuCont *cont, s32 arg1, s32 arg2) {
    cont->unk_004.unk_14 = arg2;
    cont->unk_004.unk_18 = 0.05f;
    cont->unk_004.unk_1C[0] = cont->unk_004.unk_24[0] - 160.0f;
    func_8004655C(&cont->unk_004, arg1);
}

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

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004B43C);

void func_8004B488(MenuCont *cont, MenuItem *parentItem) {
    func_800464BC(&cont->unk_004, parentItem);
    func_800464F8(cont->unk_094, ARRAY_COUNT(cont->unk_094), &cont->unk_004);
    func_800464F8(cont->unk_364, ARRAY_COUNT(cont->unk_364), &cont->unk_004);
    func_800464BC(cont->unk_3F4, parentItem);
    func_800464BC(cont->unk_484, parentItem);
}

#if 0
//? menuItem_drawAlphaTex(MenuItem *, Gfx **, TiTexDataEntry *, TiTexDataEntry *, s32); /* extern */

void menuCont_draw(MenuCont *cont, Gfx **gfxP) {
    Gfx *gfx;
    Gfx *temp_v0;
    MenuItem *temp_s1;
    TiTexDataEntry *temp_s0;
    TiTexDataEntry *temp_s0_2;
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
INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", menuCont_draw);
#endif

void func_8004B774(MenuMainPanel *arg0, s32 arg1, f32 arg2) {
    arg0->unk_028.unk_14 = arg2;
    arg0->unk_028.unk_18 = 0.05f;
    // TODO: SCREEN_WIDTH?
    arg0->unk_028.unk_1C[0] = arg0->unk_028.unk_24[0] - 320.0f;
    func_8004655C(&arg0->unk_028, arg1);
}

void menuMainPanel_init(MenuMainPanel *arg0, struct_watchMenu *watchMenuRef, s32 arg2, s32 arg3, const s32 *arg4,
                        s32 arg5, s32 arg6) {
    s32 i;

    arg0->watchMenuRef = watchMenuRef;
    arg0->unk_008 = arg2;
    arg0->unk_00C = WrapI(0, arg2, arg3);

    for (i = 0; i < ARRAY_COUNTU(arg0->unk_010); i++) {
        arg0->unk_010[i] = arg4[i];
    }

    menuItem_init(&arg0->unk_028, arg5, arg6);
    for (i = 0; i < arg2; i++) {
        menuItem_init(&arg0->unk_0B8[i], 0xB, 9 + i * 0x17);
    }

    func_800479A8(&arg0->unk_418, watchMenuRef, 0, 0, 0, 0, 0x6A, 0x14);
    arg0->unk_418.unk_01C.b.unk_30 = 1;
}

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004B8CC);

void func_8004B98C(MenuMainPanel *arg0, MenuItem *parentItem) {
    func_800464BC(&arg0->unk_028, parentItem);
    func_800464F8(arg0->unk_0B8, arg0->unk_008, &arg0->unk_028);
    menuCursor_update(&arg0->unk_418, &arg0->unk_0B8[arg0->unk_00C]);
}

void menuMainPanel_draw(MenuMainPanel *arg0, Gfx **gfxP) {
    Gfx *gfx = *gfxP;
    MenuCursor *sp1C[1];
    TiTexDataEntry *temp_s4;
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
    nameSelPanel->unk_028.unk_14 = arg2;
    nameSelPanel->unk_028.unk_18 = 0.05f;
    nameSelPanel->unk_028.unk_1C[0] = nameSelPanel->unk_028.unk_24[0] - 320.0f;
    func_8004655C(&nameSelPanel->unk_028, arg1);
}

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

void menuNameSelPanel_init(MenuNameSelPanel *nameSelPanel, struct_watchMenu *watchMenuRef, bool arg2, s32 arg3,
                           s32 arg4, s32 arg5) {
    s32 i;

    nameSelPanel->watchMenuRef = watchMenuRef;
    menuItem_init(&nameSelPanel->unk_028, arg4, arg5);

    for (i = 0; i < ARRAY_COUNTU(nameSelPanel->unk_0B8) - 1; i++) {
        menuItem_init(&nameSelPanel->unk_0B8[i], ((i % 2) * 60) + 6, ((i / 2) * 23) + 31);
    }
    menuItem_init(&nameSelPanel->unk_0B8[i], 0x24, 8);

    for (i = 0; i < ARRAY_COUNTU(nameSelPanel->unk_5C8); i++) {
        MenuCursor *temp_s0 = &nameSelPanel->unk_5C8[i];

        func_800479A8(temp_s0, watchMenuRef, 0, i, 0, 0, 0x38, 0x14);
        if (i % 2U != 0) {
            temp_s0->unk_0B0.unk_64 = WrapF(0.0f, 1.0f, temp_s0->unk_0B0.unk_64 + 0.5);
            temp_s0->unk_140.unk_14 = WrapF(0.0f, 1.0f, temp_s0->unk_140.unk_14 + 0.5);

            temp_s0->unk_140.unk_1C[0] += nameSelPanel->unk_5C8[i].unk_014 + 0x10;
            temp_s0->unk_140.unk_24[0] += nameSelPanel->unk_5C8[i].unk_014 + 0x10;

            temp_s0->unk_140.unk_40[0] = -temp_s0->unk_140.unk_40[0];
            temp_s0->unk_140.unk_48[0] = -temp_s0->unk_140.unk_48[0];

            temp_s0->unk_1D0.unk_14 = WrapF(0.0f, 1.0f, temp_s0->unk_1D0.unk_14 + 0.5);
            temp_s0->unk_1D0.unk_1C[0] += nameSelPanel->unk_5C8[i].unk_014 + 0x10;
            temp_s0->unk_1D0.unk_24[0] += nameSelPanel->unk_5C8[i].unk_014 + 0x10;
        }
    }

    menuNameSelPanel_clear(nameSelPanel, arg2, arg3);
}

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004BEB4);

extern const s32 _texEndOrGuest_3608[];
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", _texEndOrGuest_3608);

extern const u8 RO_800AFC48[];
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800AFC48);

extern const s32 _panel_3859[][2];
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", _panel_3859);

extern const s32 _pos_4015[];
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", _pos_4015);

extern const s32 _y_4020[];
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", _y_4020);

INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800AFC74);

extern const s32 _panel_4108[];
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", _panel_4108);

INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800AFCEC);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800AFCF0);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800AFCFC);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800AFD00);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800AFD0C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800AFD10);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800AFD1C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800AFD20);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800AFD2C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800AFD30);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800AFD3C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800AFD40);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800AFD4C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800AFD50);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800AFD5C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800AFD60);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800AFD6C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800AFD74);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800AFD78);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800AFD7C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800AFD80);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004BF10);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004C1F0);

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
                nameSelPanel->unk_5C8[i].unk_0B0.unk_6C[0][3] = 0.0f;
                nameSelPanel->unk_5C8[j].unk_0B0.unk_6C[0][3] = 0.0f;
            }
        }
    }

    for (i = 0; i < ARRAY_COUNTU(nameSelPanel->unk_5C8); i++) {
        MenuCursor *cursor = &nameSelPanel->unk_5C8[i];

        menuCursor_update(cursor, &nameSelPanel->unk_0B8[nameSelPanel->unk_014[i]]);
        if (nameSelPanel->unk_00C[i] > 0) {
            MenuItem *item = &cursor->unk_0B0;

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

#if 0
void menuNameSelPanel_draw(MenuNameSelPanel *nameSelPanel, Gfx **gfxP) {
    MenuCursor *sp18;
    Gfx **sp2C = gfxP;
    Gfx *gfx = *sp2C; // sp 20

    MenuItem *temp_s3;
    TiTexDataEntry *temp_s0;
    s32 var_s2;
    s32 var_s4;
    struct_800EF560 *evsMemData;
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
INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", menuNameSelPanel_draw);
#endif

void func_8004C820(MenuNameOpPanel *nameOpPanel, s32 arg1, f32 arg2) {
    nameOpPanel->unk_010.unk_14 = arg2;
    nameOpPanel->unk_010.unk_18 = 0.05f;
    nameOpPanel->unk_010.unk_1C[0] = nameOpPanel->unk_010.unk_24[0] - 320.0f;
    func_8004655C(&nameOpPanel->unk_010, arg1);
}

void menuNameOpPanel_init(MenuNameOpPanel *nameOpPanel, struct_watchMenu *watchMenuRef, s32 arg2, s32 arg3,
                          const u8 *arg4, s32 xPos, s32 yPos) {
    u32 i;

    nameOpPanel->watchMenuRef = watchMenuRef;
    nameOpPanel->unk_004 = arg2;
    nameOpPanel->unk_008 = arg3;

    if (arg4 == NULL) {
        arg4 = RO_800AFC48;
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

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004C974);

void func_8004CA30(MenuNameOpPanel *nameOpPanel, MenuItem *parentItem) {
    func_800464BC(&nameOpPanel->unk_010, parentItem);
    func_800464BC(&nameOpPanel->unk_0A0, &nameOpPanel->unk_010);
    func_800464F8(nameOpPanel->unk_130, ARRAY_COUNT(nameOpPanel->unk_130), &nameOpPanel->unk_010);
    menuCursor_update(&nameOpPanel->unk_250, &nameOpPanel->unk_130[nameOpPanel->unk_008]);
}

void menuNameOpPanel_draw(MenuNameOpPanel *nameOpPanel, Gfx **gfxP) {
    Gfx *gfx = *gfxP;
    MenuCursor *sp1C[1];
    MenuItem *temp_v0_3;
    TiTexDataEntry *temp_s1;
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

    temp_v0_3 = &nameOpPanel->unk_0A0;
    for (i = 0; i < ARRAY_COUNTU(nameOpPanel->unk_00C); i++) {
        fontXX_drawID(&gfx, temp_v0_3->unk_0C[0] + 4.0f + (i * 12), temp_v0_3->unk_0C[1] + 4.0f,
                      temp_v0_3->unk_30[0] * 12.0f, temp_v0_3->unk_30[1] * 12.0f, nameOpPanel->unk_00C[i]);
    }

    sp1C[0] = &nameOpPanel->unk_250;
    func_80048634(sp1C, ARRAY_COUNT(sp1C), &gfx);

    *gfxP = gfx;
}

void func_8004CCD0(MenuSndSelPanel *sndSelPanel, s32 arg1, f32 arg2) {
    sndSelPanel->unk_014.unk_14 = arg2;
    sndSelPanel->unk_014.unk_18 = 0.05f;
    sndSelPanel->unk_014.unk_1C[0] = sndSelPanel->unk_014.unk_24[0] - 320.0f;
    func_8004655C(&sndSelPanel->unk_014, arg1);
}

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

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004CE48);

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

void menuSndSelPanel_draw(MenuSndSelPanel *sndSelPanel, Gfx **gfxP) {
    void *sp18[ARRAY_COUNT(sndSelPanel->unk_2E4)];
    s32 pad[2] UNUSED;
    Gfx *gfx = *gfxP;
    s32 i;
    TiTexDataEntry *temp_v0;
    f32 temp_fs0;
    f32 temp_fs1;

    gSPDisplayList(gfx++, fade_normal_texture_init_dl);

    temp_fs0 = sndSelPanel->unk_014.unk_0C[0];
    temp_fs1 = sndSelPanel->unk_014.unk_0C[1];
    temp_v0 = _getTexMain(sndSelPanel->watchMenuRef, 0xB);

    menuItem_drawTex(&sndSelPanel->unk_014, &gfx, temp_v0, 0);
    sndSelPanel->unk_014.unk_0C[1] += 76.0f;
    menuItem_drawTex(&sndSelPanel->unk_014, &gfx, temp_v0, 0);
    sndSelPanel->unk_014.unk_0C[0] = temp_fs0 + 19.0f;
    sndSelPanel->unk_014.unk_0C[1] = temp_fs1 + 2.0f;
    temp_v0 = _getTexMain(sndSelPanel->watchMenuRef, 0xC);
    menuItem_drawTex(&sndSelPanel->unk_014, &gfx, temp_v0, 0);
    sndSelPanel->unk_014.unk_0C[0] = temp_fs0;
    sndSelPanel->unk_014.unk_0C[1] = temp_fs1;

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

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004D258);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004D2A0);

INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800AFE2C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800AFE58);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800AFEA8);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800AFEB0);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800AFEB8);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800AFECC);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800AFED0);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800AFEDC);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800AFEE0);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800AFEE4);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800AFEE8);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004D6DC);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004D734);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004D828);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004DA40);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004DD14);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004E270);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004E2B4);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004E2F4);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004E4F4);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004E764);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004E8E0);

extern char *D_8008E78C[];
extern char *D_8008E79C[];
extern char *D_8008E7B4[];
extern char *D_8008E7D0[];
extern char *D_8008E7DC[];
extern char *D_8008E7F0[];
extern char *D_8008E804[];
extern char *D_8008E814[];
extern char *D_8008E820[];
extern const char STR_800AE5E8[];
extern const char STR_800AE650[];
extern const char STR_800AE9B8[];
extern const char STR_800AF048[];
extern const char STR_800AF070[];
extern const char STR_800AF18C[];
extern const char STR_800AF1BC[];
extern const char STR_800AF234[];
extern const char STR_800AF268[];
extern const char STR_800AF324[];
extern const char STR_800AF390[];
extern const char STR_800AF498[];

bool menuMain_setMsgStr(MenuMain *menuMain, MainMenuMode mode, s32 arg2) {
    bool var_s4 = false;
    char **var_v1 = NULL;
    const char *var_s1 = NULL;
    s32 var_s2;

    switch (mode) {
        case MAINMENUMODE_MENUMAIN_0:
            var_v1 = D_8008E78C;
            break;

        case MAINMENUMODE_1:
            var_v1 = D_8008E79C;
            break;

        case MAINMENUMODE_22:
            var_v1 = D_8008E7B4;
            break;

        case MAINMENUMODE_35:
            var_s1 = STR_800AE9B8;
            break;

        case MAINMENUMODE_46:
            var_v1 = D_8008E7DC;
            break;

        case MAINMENUMODE_70:
            var_v1 = D_8008E814;
            break;

        case MAINMENUMODE_73:
            var_s1 = STR_800AF498;
            break;

        case MAINMENUMODE_36:
        case MAINMENUMODE_37:
        case MAINMENUMODE_38:
        case MAINMENUMODE_39:
            var_v1 = D_8008E7D0;
            break;

        case MAINMENUMODE_59:
            var_v1 = D_8008E7F0;
            break;

        case MAINMENUMODE_71:
            var_s1 = D_8008E804[menuMain->unk_1C64.unk_004];
            break;

        case MAINMENUMODE_47:
            var_s1 = STR_800AF048;
            break;

        case MAINMENUMODE_48:
        case MAINMENUMODE_MENURANK_55:
            var_s1 = STR_800AF070;
            break;

        case MAINMENUMODE_62:
            var_s1 = STR_800AF18C;
            break;

        case MAINMENUMODE_65:
            var_s1 = STR_800AF1BC;
            break;

        case MAINMENUMODE_66:
            var_s1 = STR_800AF234;
            break;

        case MAINMENUMODE_72:
            var_s1 = STR_800AF268;
            break;

        case MAINMENUMODE_67:
        case MAINMENUMODE_68:
            var_s1 = STR_800AF324;
            break;

        case MAINMENUMODE_69:
            var_s1 = STR_800AF390;
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
            var_s1 = STR_800AE5E8;
            break;

        case MAINMENUMODE_61:
            var_s1 = STR_800AE650;
            break;

        default:
            break;
    }

    if (var_v1 != NULL) {
        var_s1 = var_v1[arg2];
    }

    for (var_s2 = 0; var_s2 < 0x10U; var_s2++) {
        if ((var_s1 == D_8008E820[var_s2]) && msgWnd_isEnd(&menuMain->unk_2308)) {
            menuMain->unk_2304 = 0;
        }
    }

    if (var_s1 != menuMain->unk_2304) {
        msgWnd_clear(&menuMain->unk_2308);
        if (var_s1 != NULL) {
            msgWnd_addStr(&menuMain->unk_2308, var_s1);
            var_s4 = true;
        }
        menuMain->unk_2304 = var_s1;
    }

    return var_s4;
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
}

void menuMain_init(MenuMain *menuMain, struct_watchMenu *watchMenuRef, struct_watchMenu_unk_02470 **arg2) {
    u32 i;

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

    menuMain->unk_0030 = -1;
    menuMain->unk_002C = 0;
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
    menuMain->unk_2308.unk_48 = 0xD;

    menuItem_init(&menuMain->unk_2388, 0x9E, 0x2F);
    menuMain->unk_2388.unk_14 = 0.0f;
    menuMain->unk_2388.unk_18 = 0.05f;
    menuMain->unk_2388.unk_1C[0] += 320.0f;

    menuItem_init(&menuMain->unk_2418, 0xDC, 0x63);
    menuMain->unk_2418.unk_18 = 0.05f;
    menuMain->unk_2418.unk_14 = 0.0f;
    menuMain->unk_2418.unk_1C[0] += 320.0f;

    menuItem_init(&menuMain->unk_2538, -0x44, 0x16);
    menuMain->unk_2538.unk_18 = 0.05f;
    menuMain->unk_2538.unk_14 = 0.0f;
    menuMain->unk_2538.unk_1C[0] = 32.0f;
    menuMain->unk_2538.unk_1C[1] = 54.0f;

    func_8004655C(&menuMain->unk_2538, -1);
    menuMain->unk_2538.unk_3C = 0.05f;
    menuMain->unk_2538.unk_38 = 0.0f;
    func_800465B8(&menuMain->unk_2538, -1);
    menuMain->unk_2538.unk_6C[1][0] = 1.0f;
    menuMain->unk_2538.unk_6C[1][1] = 0.9411765f;
    menuMain->unk_2538.unk_6C[1][2] = 0.972549f;

    menuItem_init(&menuMain->unk_25C8, 6, 5);
    menuMain->unk_25C8.unk_8C |= 0x80000000;

    menuItem_init(&menuMain->unk_24A8, 0x51, 0x11);

    menuCont_init(&menuMain->unk_2658, watchMenuRef, 0xE, 0x71);

    menuYN_init(&menuMain->unk_2B6C, watchMenuRef, 0x78, 0x8C);

    menuMes_init(&menuMain->unk_31E4, watchMenuRef, arg2, 0x11, 2, 0x40, 0xA6);
}

INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800B0310);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800B0320);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800B0338);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800B0350);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800B035C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800B0360);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800B0364);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800B0378);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800B037C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800B0380);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800B039C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800B03A0);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800B03A4);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800B03C0);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800B03C4);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800B03D8);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800B03EC);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800B03F8);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800B0404);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800B0410);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800B041C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800B0424);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800B043C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800B0448);

void func_8004F2D8(MenuMain *menuMain) {
    u16 keyTrg = _getKeyTrg(menuMain->watchMenuRef, 0);

    if ((keyTrg & B_BUTTON) && (menuMain->mode != MAINMENUMODE_MENUMAIN_0)) {
        _setFadeDir(menuMain->watchMenuRef, -1);
        _setNextMain(menuMain->watchMenuRef, MAIN_NO_6);
        dm_snd_play(SND_INDEX_68);
    }
}

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004F33C);

extern char *D_8008E85C[];

#if 0
? func_800490B8(MenuYN *, s32);
s32 func_80049224(MenuYN *, ?, s32);
? func_80049578(MenuMes *, s32);
? func_8004970C(MenuMes *, ? *, s32);
s32 func_8004B43C(MenuCont *, ?, s32);
s32 func_8004B8CC(MenuMainPanel *, ?, s32);
s32 func_8004C1F0(MenuNameSelPanel *);
s32 func_8004C974(MenuNameOpPanel *, ?, s32);
s32 func_8004CE48(MenuSndSelPanel *, ?, s32);
? func_80059B5C(struct_watchMenu *);
? func_80059BC8(struct_watchMenu *);
? func_80059C34(struct_watchMenu *);
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
extern ? STR_800AF3C4;

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
    switch (temp_v0) {                              /* switch 1 */
        case MAINMENUMODE_66:                       /* switch 1 */
        case MAINMENUMODE_69:                       /* switch 1 */
            var_a2 = 1;
            break;
        case MAINMENUMODE_65:                       /* switch 1 */
        case MAINMENUMODE_68:                       /* switch 1 */
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
        case MAINMENUMODE_71:                       /* switch 1 */
            if (0 == 0) {
                var_v0 = func_8004CE48(&menuMain->unk_1C64, 0, 0);
                goto block_20;
            }
            goto block_21;
        default:                                    /* switch 1 */
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
        switch (temp_v0_2) {                        /* switch 2 */
            case MAINMENUMODE_2:                    /* switch 2 */
            case MAINMENUMODE_5:                    /* switch 2 */
            case MAINMENUMODE_8:                    /* switch 2 */
            case MAINMENUMODE_11:                   /* switch 2 */
            case MAINMENUMODE_14:                   /* switch 2 */
            case MAINMENUMODE_18:                   /* switch 2 */
            case MAINMENUMODE_23:                   /* switch 2 */
            case MAINMENUMODE_27:                   /* switch 2 */
            case MAINMENUMODE_31:                   /* switch 2 */
            case MAINMENUMODE_60:                   /* switch 2 */
            case MAINMENUMODE_61:                   /* switch 2 */
            case MAINMENUMODE_66:                   /* switch 2 */
            case MAINMENUMODE_69:                   /* switch 2 */
                var_s0 = 0;
                break;
            case MAINMENUMODE_62:                   /* switch 2 */
                var_s0 = menuMain->unk_17B4.unk_008;
                break;
            case MAINMENUMODE_71:                   /* switch 2 */
                var_s0 = menuMain->unk_1C64.unk_004;
                break;
            case MAINMENUMODE_65:                   /* switch 2 */
            case MAINMENUMODE_68:                   /* switch 2 */
                var_s0 = menuMain->unk_2B6C.unk_004;
                break;
            default:                                /* switch 2 */
                var_s0 = sp1C->unk_00C;
                menuMain->unk_000C[menuMain->unk_0008] = var_s0;
                break;
        }
        temp_v1 = menuMain->mode;
        switch (temp_v1) {                          /* switch 3 */
            case MAINMENUMODE_MENUMAIN_0:           /* switch 3 */
                if (temp_s2 & 0x9000) {
                    temp_s0 = *(&RO_800B0310 + (var_s0 * 4));
                    if ((temp_s0 == MAINMENUMODE_22) && (temp_v0_3 = joyResponseCheck(), evs_playmax = temp_v0_3, (((u32) (temp_v0_3 & 0xFF) < 2U) != 0))) {
                        func_8004970C(&menuMain->unk_31E4, &STR_800AF3C4);
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
            case MAINMENUMODE_1:                    /* switch 3 */
                temp_v1_2 = var_s0 * 4;
                menuMain->unk_0030 = ENUM_EVS_GAMEMODE_1;
                menuMain->unk_002C = *(&RO_800B0320 + temp_v1_2);
                if (temp_s2 & 0x9000) {
                    temp_v1_3 = *(&RO_800B0338 + temp_v1_2);
                    menuMain->unk_0030 = -1;
                    menuMain->mode = temp_v1_3;
                    switch (temp_v1_3) {            /* switch 8; irregular */
                        case MAINMENUMODE_18:       /* switch 8 */
                            evs_gamemode = ENUM_EVS_GAMEMODE_1;
                            break;
                        case MAINMENUMODE_8:        /* switch 8 */
                            evs_gamemode = ENUM_EVS_GAMEMODE_2;
                            break;
                        case MAINMENUMODE_11:       /* switch 8 */
                            evs_gamemode = ENUM_EVS_GAMEMODE_3;
                            break;
                        default:                    /* switch 8 */
                            evs_gamemode = ENUM_EVS_GAMEMODE_0;
                            break;
                    }
                    temp_v0_5 = menuMain->mode;
                    switch (temp_v0_5) {            /* switch 4 */
                        case MAINMENUMODE_2:        /* switch 4 */
                            evs_playcnt = 2;
                            evs_story_flg = 1;
                            evs_gamesel = ENUM_EVS_GAMESEL_3;
                            game_state_data->unk_04C = 0;
                            *(game_state_data + 0x410) = 1;
                            var_s6 = 1;
                            break;
                        case MAINMENUMODE_5:        /* switch 4 */
                        case MAINMENUMODE_8:        /* switch 4 */
                        case MAINMENUMODE_11:       /* switch 4 */
                            evs_playcnt = 1;
                            evs_story_flg = 0;
                            evs_gamesel = ENUM_EVS_GAMESEL_0;
                            game_state_data->unk_04B = 0;
                            game_state_data->unk_04C = 0;
                            game_state_data->unk_090 = 0;
                            var_s6 = 1;
                            break;
                        case MAINMENUMODE_14:       /* switch 4 */
                        case MAINMENUMODE_18:       /* switch 4 */
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
            case MAINMENUMODE_22:                   /* switch 3 */
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
                        case MAINMENUMODE_23:       /* switch 9 */
                            evs_gamemode = ENUM_EVS_GAMEMODE_0;
                            break;
                        case MAINMENUMODE_27:       /* switch 9 */
                            evs_gamemode = ENUM_EVS_GAMEMODE_1;
                            break;
                        case MAINMENUMODE_31:       /* switch 9 */
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
            case MAINMENUMODE_35:                   /* switch 3 */
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
                        func_8004970C(&menuMain->unk_31E4, *(&D_8008E85C + (var_s0 * 4)), 0);
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
            case MAINMENUMODE_2:                    /* switch 3 */
            case MAINMENUMODE_5:                    /* switch 3 */
            case MAINMENUMODE_8:                    /* switch 3 */
            case MAINMENUMODE_11:                   /* switch 3 */
            case MAINMENUMODE_14:                   /* switch 3 */
            case MAINMENUMODE_18:                   /* switch 3 */
            case MAINMENUMODE_23:                   /* switch 3 */
            case MAINMENUMODE_27:                   /* switch 3 */
            case MAINMENUMODE_31:                   /* switch 3 */
            case MAINMENUMODE_61:                   /* switch 3 */
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
                    switch (temp_v0_8) {            /* switch 5 */
                        case MAINMENUMODE_2:        /* switch 5 */
                            var_s5 = *(&RO_800B0360 + (var_v1_2 * 8));
                            break;
                        case MAINMENUMODE_61:       /* switch 5 */
                            var_s5 = *(&RO_800B0364 + (var_v1_2 * 8));
                            break;
                        case MAINMENUMODE_5:        /* switch 5 */
                            var_s5 = *(&RO_800B0378 + (var_v1_2 * 0xC));
                            break;
                        case MAINMENUMODE_8:        /* switch 5 */
                            var_s5 = *(&RO_800B037C + (var_v1_2 * 0xC));
                            break;
                        case MAINMENUMODE_11:       /* switch 5 */
                            var_s5 = *(&RO_800B0380 + (var_v1_2 * 0xC));
                            break;
                        case MAINMENUMODE_23:       /* switch 5 */
                            var_s5 = *(&RO_800B039C + (var_v1_2 * 0xC));
                            break;
                        case MAINMENUMODE_27:       /* switch 5 */
                            var_s5 = *(&RO_800B03A0 + (var_v1_2 * 0xC));
                            break;
                        case MAINMENUMODE_31:       /* switch 5 */
                            var_s5 = *(&RO_800B03A4 + (var_v1_2 * 0xC));
                            break;
                        case MAINMENUMODE_14:       /* switch 5 */
                            var_s5 = *(&RO_800B03C0 + (var_v1_2 * 8));
                            break;
                        case MAINMENUMODE_18:       /* switch 5 */
                            var_s5 = *(&RO_800B03C4 + (var_v1_2 * 8));
                            /* fallthrough */
                        default:                    /* switch 5 */
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
                    switch (temp_v0_9) {            /* switch 6 */
                        case MAINMENUMODE_2:        /* switch 6 */
                        case MAINMENUMODE_5:        /* switch 6 */
                        case MAINMENUMODE_8:        /* switch 6 */
                        case MAINMENUMODE_11:       /* switch 6 */
                        case MAINMENUMODE_14:       /* switch 6 */
                        case MAINMENUMODE_18:       /* switch 6 */
                            var_v0_3 = MAINMENUMODE_1;
block_126:
                            menuMain->mode = var_v0_3;
                            break;
                        case MAINMENUMODE_23:       /* switch 6 */
                        case MAINMENUMODE_27:       /* switch 6 */
                        case MAINMENUMODE_31:       /* switch 6 */
                            var_v0_3 = MAINMENUMODE_22;
                            goto block_126;
                        case MAINMENUMODE_61:       /* switch 6 */
                            var_v0_3 = MAINMENUMODE_46;
                            goto block_126;
                    }
block_127:
                    var_s3 = 1;
                    var_s6 = -1;
                    var_s4 = SND_INDEX_68;
                }
                break;
            case MAINMENUMODE_46:                   /* switch 3 */
                if (temp_s2 & 0x9000) {
                    temp_v0_10 = *(&RO_800B03D8 + (var_s0 * 4));
                    menuMain->mode = temp_v0_10;
                    switch (temp_v0_10) {           /* switch 7 */
                        case MAINMENUMODE_61:       /* switch 7 */
                            var_s3 = 1;
                            var_s6 = 1;
                            var_s4 = SND_INDEX_62;
                            break;
                        case MAINMENUMODE_47:       /* switch 7 */
                        case MAINMENUMODE_59:       /* switch 7 */
                        case MAINMENUMODE_67:       /* switch 7 */
                        case MAINMENUMODE_70:       /* switch 7 */
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
                            dm_seq_play_fade(0xD, 0x14);
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
            case MAINMENUMODE_70:                   /* switch 3 */
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
            case MAINMENUMODE_73:                   /* switch 3 */
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
            case MAINMENUMODE_36:                   /* switch 3 */
            case MAINMENUMODE_37:                   /* switch 3 */
            case MAINMENUMODE_38:                   /* switch 3 */
            case MAINMENUMODE_39:                   /* switch 3 */
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
            case MAINMENUMODE_47:                   /* switch 3 */
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
                    dm_seq_play_fade(0xC, 0x14);
                }
                break;
            case MAINMENUMODE_48:                   /* switch 3 */
            case MAINMENUMODE_MENURANK_55:          /* switch 3 */
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
            case MAINMENUMODE_59:                   /* switch 3 */
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
            case MAINMENUMODE_72:                   /* switch 3 */
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
            case MAINMENUMODE_60:                   /* switch 3 */
                menuCont_setFade(&menuMain->unk_2658, 1, menuMain->unk_2658.unk_3F4[0].unk_64);
                if (temp_s2 & 0x4000) {
                    menuMain->mode = MAINMENUMODE_59;
                    sp2C += 1;
                    var_s3 = 1;
                    var_s4 = SND_INDEX_68;
                    sp3C -= 1;
                }
                break;
            case MAINMENUMODE_62:                   /* switch 3 */
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
            case MAINMENUMODE_71:                   /* switch 3 */
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
                        dm_seq_play_fade(0xC, 0x14);
                        menuMain->unk_0034 = 0xC;
                    }
                }
                break;
            case MAINMENUMODE_65:                   /* switch 3 */
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
            case MAINMENUMODE_66:                   /* switch 3 */
                if (temp_s2 & 0xFF3F) {
                    menuMain->mode = MAINMENUMODE_61;
                    var_s6 = 1;
                    var_fp = -1;
                    var_s4 = SND_INDEX_62;
                    goto block_223;
                }
                break;
            case MAINMENUMODE_67:                   /* switch 3 */
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
            case MAINMENUMODE_68:                   /* switch 3 */
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
            case MAINMENUMODE_69:                   /* switch 3 */
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
INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", menuMain_input);
#endif

void menuMain_update(MenuMain *menuMain) {
    MenuMainPanel *temp_s5 = &menuMain->unk_003C[menuMain->unk_2300];
    MenuItem *rootItem = _getRootItem(menuMain->watchMenuRef);
    s32 i;

    for (i = 0; i < ARRAY_COUNTU(menuMain->unk_003C); i++) {
        func_8004B98C(&menuMain->unk_003C[i], rootItem);
    }

    menuNameSelPanel_update(&menuMain->unk_0D2C, rootItem);
    func_8004CA30(&menuMain->unk_17B4, rootItem);
    func_8004CFB8(&menuMain->unk_1C64, rootItem);
    func_800464BC(&menuMain->unk_2388, rootItem);

    menuMain->unk_2308.unk_28 = menuMain->unk_2388.unk_0C[0] + menuMain->unk_2388.unk_30[0] * 6;
    menuMain->unk_2308.unk_2C = menuMain->unk_2388.unk_0C[1] + menuMain->unk_2388.unk_30[1] * 6;

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

extern const s32 _pat_6137[];
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", _pat_6137);

#if 0
//? func_80043F18(Gfx **, s32 *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32, f32, f32, f32); /* extern */
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
    TiTexDataEntry *var_s3;
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
        func_80043F18(&sp90, &sp94, (s32) var_s6, (s32) var_s7, temp_s3->unk_0->unk_4, (s32) temp_s3->unk_4->unk_0, temp_v0_2->unk_0->unk_4, (s32) temp_v0_2->unk_4->unk_0, 0, 0, (s32) var_s6, (s32) var_s7, 0.0f, 0.0f, (f32) var_s6, (f32) var_s7);
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
INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", menuMain_drawKaSaMaRu);
#endif

INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800B0968);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800B096C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800B09F8);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800B09FC);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800B0A08);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800B0A0C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800B0A18);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800B0A1C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800B0A20);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800B0A24);

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

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_800513F0);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80051480);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_800514C4);

#if 0
? func_800466D0(s8 *);
? func_800467E0(s8 *);
? func_800513F0(s32, s32, u32, s32 *, s32 *);
? func_80051480(MenuStory *, ?, ?);
void func_800514C4(s32);
extern ? D_800B09F8;
extern ? D_800B09FC;
extern ? D_800B0A08;
extern ? D_800B0A0C;
extern ? D_800B0A18;
extern ? D_800B0A1C;
extern ? D_800B0A20;
extern ? D_800B0A24;

void menuStory_init(MenuStory *menuStory, struct_watchMenu *arg1, struct_watchMenu_unk_02470 **arg2) {
    s32 sp20;
    s32 sp24;
    struct_watchMenu_unk_02470 **sp2C;
    MenuCursor *temp_a0;
    MenuCursor *var_a0_3;
    MenuItem *temp_a0_2;
    MenuItem *temp_a0_3;
    MenuItem *temp_s0;
    MenuItem *temp_s0_2;
    MenuItem *var_a0_2;
    MenuStory *temp_s3;
    MenuStory *var_a0;
    MenuStory *var_s0_2;
    enum CharAnimeMode var_s1_3;
    s32 temp_a1;
    s32 temp_a1_2;
    s32 temp_a2;
    s32 temp_a2_2;
    s32 temp_t0;
    s32 temp_t1;
    s32 temp_v0;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 var_s0;
    s32 var_s0_3;
    s32 var_s0_4;
    s32 var_s0_5;
    s32 var_s1_6;
    s32 var_s2;
    s32 var_s2_2;
    s32 var_s2_4;
    struct_800EF560 *var_v1;
    struct_800EF560_unk_B4 *temp_s4;
    struct_watchMenu_unk_02470 *var_fp;
    u32 temp_a2_3;
    u32 temp_v0_2;
    u32 var_s1;
    u32 var_s1_2;
    u32 var_s1_4;
    u32 var_s1_5;
    u32 var_s1_7;
    u32 var_s1_8;
    u32 var_s2_3;

    var_a0 = menuStory;
    temp_s3 = var_a0;
    sp2C = arg2;
    var_fp = *arg2;
    var_s1 = 0;
    temp_s3->watchMenuRef = arg1;
    var_v1 = &evs_mem_data[*evs_select_name_no];
    temp_s4 = &var_v1->unk_B4;
    do {
        var_a0->unk_4 = (s32) (var_v1->unk_08[0][0] + 1);
        temp_v0 = var_v1->unk_08[0][1];
        var_s1 += 1;
        var_v1 += 8;
        var_a0->unk_8 = (s32) (temp_v0 + 1);
        var_a0 += 8;
    } while (var_s1 < 4U);
    temp_s3->unk_24 = 0;
    var_s1_2 = 0x160;
    var_s0 = 0;
    temp_s3->unk_34 = 0;
    temp_s3->unk_28 = (s32) (u8) temp_s4->unk_03;
    menuItem_init(&temp_s3->unk_0040, 0x19, 0x2F);
    temp_s3->unk_28 = (s32) (u8) temp_s4->unk_03;
    menuItem_init(&temp_s3->unk_00D0, 0x45, 0x12);
    var_a0_2 = temp_s3->unk_0160;
    do {
        temp_a1 = *(&D_800B09F8 + var_s0);
        temp_a2 = *(&D_800B09FC + var_s0);
        var_s1_2 += 0x90;
        var_s0 += 8;
        menuItem_init(var_a0_2, temp_a1, temp_a2);
        var_a0_2 = temp_s3 + var_s1_2;
    } while (var_s1_2 < 0x280U);

    var_s1_3 = CHARANIMEMODE_M;
    var_s0_2 = temp_s3;
    do {
        var_s0_2->unk_38 = (s32) ((s32) &var_fp->unk_00000[0xF] & ~0xF);
        temp_v0_2 = animeState_getDataSize(var_s1_3);
        var_s1_3 += 1;
        var_fp = var_s0_2->unk_38 + temp_v0_2;
        var_s0_2 += 4;
    } while ((u32) var_s1_3 < 2U);

    func_80040B10(func_800514C4, (s32) temp_s3);
    var_s1_4 = 0;
    var_s0_3 = 0;
    var_s2 = 0x300;
    do {
        temp_a0 = temp_s3 + var_s2;
        temp_v0_3 = *(&D_800B09F8 + var_s0_3);
        temp_v1 = *(&D_800B09FC + var_s0_3);
        var_s0_3 += 8;
        var_s2 += 0x260;
        var_s1_4 += 1;
        func_800479A8(temp_a0, arg1, 0, 0, temp_v0_3 - 0x18, temp_v1 - 0x2C, 0x30, 0x2F);
    } while (var_s1_4 < 2U);
    temp_s3->unk_2C = (s32) (u8) temp_s4->unk_00;
    var_s1_5 = 0;
    func_80049894(&temp_s3->unk_07C0, arg1, 3, (s32) (u8) temp_s4->unk_00, 0x45, 0x3D);
    menuSpeedItem_init(&temp_s3->unk_085C, arg1, 3, 0, (s32) (u8) temp_s4->unk_00, 0x7D, 0x39, 0x34);
    var_s2_2 = 0xFFC;
    temp_s3->unk_085C.unk_010 = (u8) temp_s4->unk_01 != 0;
    temp_s3->unk_30 = (s32) ((u8) temp_s4->unk_02 + 1);
    func_8004A860(&temp_s3->unk_0EC0, arg1, 1, 1, (u8) temp_s4->unk_02 + 1, 0x65, 0x5A);
    menuItem_init(&temp_s3->unk_0F6C, 0x10, 0x6E);
    do {
        temp_s0 = temp_s3 + var_s2_2;
        menuItem_init(temp_s0, 0, 0);
        func_800467E0(temp_s0);
        temp_s0->unk_68 = 0.05f;
        var_s1_5 += 1;
        var_s2_2 += 0x90;
    } while (var_s1_5 < 2U);
    var_s2_3 = 0x111C;
    var_s1_6 = 0;
    do {
        temp_s0_2 = temp_s3 + var_s2_3;
        temp_a0_2 = temp_s0_2;
        temp_a1_2 = *(&D_800B0A08 + var_s1_6);
        temp_a2_2 = *(&D_800B0A0C + var_s1_6);
        var_s2_3 += 0x90;
        var_s1_6 += 8;
        menuItem_init(temp_a0_2, temp_a1_2, temp_a2_2);
        func_800466D0(temp_s0_2);
    } while (var_s2_3 < 0x123CU);
    var_s1_7 = 0;
    var_s0_4 = 0x123C;
    do {
        temp_a2_3 = var_s1_7;
        var_s1_7 += 1;
        func_800513F0(temp_s3->unk_28, temp_s3->unk_30, temp_a2_3, &sp20, &sp24);
        temp_a0_3 = temp_s3 + var_s0_4;
        var_s0_4 += 0x90;
        menuItem_init(temp_a0_3, sp20, sp24);
    } while (var_s1_7 < 2U);
    var_s1_8 = 0;
    var_s0_5 = 0;
    var_s2_4 = 0x135C;
    temp_s3->unk_111C[0].unk_40[0] = -temp_s3->unk_111C[0].unk_40[0];
    temp_s3->unk_111C[0].unk_48[0] = -temp_s3->unk_111C[0].unk_48[0];
    var_a0_3 = temp_s3->unk_135C;
    do {
        temp_v0_4 = *(&D_800B0A18 + var_s0_5);
        temp_v1_2 = *(&D_800B0A1C + var_s0_5);
        temp_t0 = *(&D_800B0A20 + var_s0_5);
        temp_t1 = *(&D_800B0A24 + var_s0_5);
        var_s0_5 += 0x10;
        var_s2_4 += 0x260;
        var_s1_8 += 1;
        func_800479A8(var_a0_3, arg1, 1, 0, temp_v0_4, temp_v1_2, temp_t0, temp_t1);
        var_a0_3 = temp_s3 + var_s2_4;
    } while (var_s1_8 < 3U);
    func_80051480(temp_s3, 1, 0);
    *sp2C = var_fp;
}
#else
INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", menuStory_init);
#endif

void func_80051974(MenuStory *menuStory) {
    u16 keyTrg = _getKeyTrg(menuStory->watchMenuRef, 0);

    if (keyTrg & B_BUTTON) {
        _setFadeDir(menuStory->watchMenuRef, -1);
        _setNextMain(menuStory->watchMenuRef, MAIN_NO_6);
        dm_snd_play(SND_INDEX_68);
    }
}

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_800519CC);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_800519EC);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", menuStory_input);

INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800B0A50);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800B0A5C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800B0A6C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800B0A7C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800B0B0C);

extern const s32 _cursor_7325[][4];
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", _cursor_7325);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", menuStory_update);

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
INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", menuStory_draw);
#endif

void func_800529FC(MenuLvSel *menuLvSel, s32 arg1, f32 arg2) {
    menuLvSel->unk_0008.unk_14 = arg2;
    menuLvSel->unk_0008.unk_18 = 0.05f;
    menuLvSel->unk_0008.unk_1C[1] = menuLvSel->unk_0008.unk_24[1] - 240.0f;
    func_8004655C(&menuLvSel->unk_0008, arg1);
}

#ifdef NON_MATCHING
void menuLvSel_init(MenuLvSel *menuLvSel, struct_watchMenu *arg1, struct_watchMenu_unk_02470 **arg2) {
    s32 temp = evs_select_name_no[0];
    struct_800EF560 *var_s0;
    struct_800EF560_unk_B4 *temp_s5;
    struct_watchMenu_unk_02470 *temp_s7 = *arg2;
    s32 var_s2;

    menuLvSel->unk_0000 = arg1;
    var_s0 = &evs_mem_data[temp];
    temp_s5 = &var_s0->unk_B4;
    menuLvSel->unk_0004 = _getMode(arg1);
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
            func_80049894(&menuLvSel->gameLvlIcon, arg1, 3, temp_s5->unk_08, 0x44, 9);
            menuSpeedItem_init(&menuLvSel->gameLvlSelector, arg1, 3, 0, temp_s5->unk_08, 0x82, 5, 0x2E);
            break;

        case MAINMENUMODE_MENULVSEL_13:
            func_80049894(&menuLvSel->gameLvlIcon, arg1, 3, temp_s5->unk_07, 0x44, 9);
            menuSpeedItem_init(&menuLvSel->gameLvlSelector, arg1, 3, 0, temp_s5->unk_07, 0x82, 5, 0x2E);
            break;

        case MAINMENUMODE_MENULVSEL_7:
            var_s2 = menuLvSel->unk_2570;
            if (var_s2 >= temp_s5->unk_04) {
                var_s2 = temp_s5->unk_04;
            }
            // var_s2 = MIN(menuLvSel->unk_2570, temp_s5->unk_04);
            func_8004A860(&menuLvSel->virusLvlNumber, arg1, 1, 2, var_s2, 0x59, 5);
            func_80048B8C(&menuLvSel->virusLvlGauge, arg1, 2, 0, var_s2, 0x99, 0xF);
            func_800466A0(&menuLvSel->virusLvlGauge.unk_010, 1.0f, 0.5f);
            menuLvSel->virusLvlGauge.unk_008 = menuLvSel->unk_2570;
            break;

        default:
            break;
    }

    func_80049894(&menuLvSel->speedIcon, arg1, 1, temp_s5->unk_05, 0x44, 0x28);
    menuSpeedItem_init(&menuLvSel->speedSelector, arg1, 1, 0, temp_s5->unk_05, 0x82, 0x24, 0x2E);

    func_800466A0(&menuLvSel->speedSelector.unk_014, 1.0f, 0.5f);
    menuMusicItem_init(&menuLvSel->musicSelector, arg1, temp_s5->unk_06, 0x46, 0x46);
    func_80048680(&menuLvSel->bottle, arg1, 0x19, 7);

    for (var_s2 = 0; var_s2 < 3U; var_s2++) {
        func_800479A8(&menuLvSel->unk_162C[var_s2], arg1, 1, 0, _cursor_7325[var_s2][0], _cursor_7325[var_s2][1],
                      _cursor_7325[var_s2][2], _cursor_7325[var_s2][3]);
    }

    menuItem_init(&menuLvSel->capsuleSpeedIcon, 0x56, 7);
    menuItem_init(&menuLvSel->musicIcon, 0x99, 8);

    func_800529FC(menuLvSel, 1, 0.0f);
    *arg2 = temp_s7;
}
#else
INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", menuLvSel_init);
#endif

void func_80052DF0(MenuLvSel *menuLvSel) {
    u16 keyTrg = _getKeyTrg(menuLvSel->unk_0000, 0);

    if (keyTrg & B_BUTTON) {
        _setFadeDir(menuLvSel->unk_0000, -1);
        _setNextMain(menuLvSel->unk_0000, MAIN_NO_6);
        dm_snd_play(SND_INDEX_68);
    }
}

void menuLvSel_input(MenuLvSel *menuLvSel) {
    struct_800EF560_unk_B4 *temp_s5 = &evs_mem_data[evs_select_name_no[0]].unk_B4;
    u16 keyRep = _getKeyRep(menuLvSel->unk_0000, 0);
    SndIndex sndIndex = SND_INDEX_INVALID;
    u16 keyTrg = _getKeyTrg(menuLvSel->unk_0000, 0);
    struct_game_state_data *gameStateData = game_state_data;
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

    if (sndIndex <= SND_INDEX_INVALID) {
        if ((keyTrg & (A_BUTTON | START_BUTTON)) && (menuLvSel->unk_256C == 2)) {
            _setFadeDir(menuLvSel->unk_0000, 1);
            _setNextMain(menuLvSel->unk_0000, MAIN_NO_1);

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
            evs_game_time = 0;
            evs_seqnumb = menuLvSel->musicSelector.unk_004;
            evs_seqence = evs_seqnumb != 4;
            sndIndex = SND_INDEX_62;
        } else if ((keyTrg & B_BUTTON) && (menuLvSel->unk_256C == 0)) {
            _setMode(menuLvSel->unk_0000, MAINMENUMODE_MENUMAIN_0);
            func_800529FC(menuLvSel, -1, 1.0f);
            if (menuLvSel->musicSelector.unk_008 >= 0) {
                dm_seq_play_fade(0xC, 0x14);
            }
            sndIndex = SND_INDEX_68;
        }

        if (sndIndex <= SND_INDEX_INVALID) {
            return;
        }
    }

    dm_snd_play(sndIndex);
}

void menuLvSel_update(MenuLvSel *menuLvSel) {
    MenuItem *rootItem = _getRootItem(menuLvSel->unk_0000);
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

void menuLvSel_draw(MenuLvSel *menuLvSel, Gfx **gfxP) {
    // struct required to force everything to go properly into the stack
    struct {
        MenuMusicItem *sp18[1];
        MenuSpeedAsk *sp1C[1];
        MenuSpeedItem *sp20[1];
        void *sp24[1];
        void *sp28[1];
        MenuCursor *sp2C[3];
    } dumb;
    Gfx *gfx = *gfxP;
    f32 temp_fs0;
    u32 i;
    TiTexDataEntry *a2;

    gSPDisplayList(gfx++, fade_normal_texture_init_dl);

    switch (menuLvSel->unk_0004) {
        case MAINMENUMODE_MENULVSEL_7:
            a2 = _getTexLevel(menuLvSel->unk_0000, 4);
            break;

        case MAINMENUMODE_MENULVSEL_10:
        case MAINMENUMODE_MENULVSEL_13:
            a2 = _getTexLevel(menuLvSel->unk_0000, 5);
            break;

        default:
            break;
    }

    menuItem_drawTex(&menuLvSel->unk_0098[0], &gfx, a2, 0);
    menuItem_drawTex(&menuLvSel->unk_0098[1], &gfx, _getTexLevel(menuLvSel->unk_0000, 1), 0);
    if (menuLvSel->speedSelector.unk_008 > 0) {
        func_80046F58(&menuLvSel->capsuleSpeedIcon, &gfx, _getTexLevel(menuLvSel->unk_0000, 3), 0, 2,
                      menuLvSel->speedSelector.unk_008 - 1);
    }
    if (menuLvSel->musicSelector.unk_004 < 4) {
        func_80046F58(&menuLvSel->musicIcon, &gfx, _getTexLevel(menuLvSel->unk_0000, 2), 0, 4,
                      menuLvSel->musicSelector.unk_004);
    }

    switch (menuLvSel->unk_0004) {
        case MAINMENUMODE_MENULVSEL_7:
            if (menuLvSel->unk_2570 >= 0x15) {
                temp_fs0 = menuLvSel->unk_0098[0].unk_0C[0];
                menuLvSel->unk_0098[0].unk_0C[0] = temp_fs0 + 222.0f;
                menuItem_drawTex(&menuLvSel->unk_0098[0], &gfx, _getTexLevel(menuLvSel->unk_0000, 6), 0);
                menuLvSel->unk_0098[0].unk_0C[0] = temp_fs0;
            }
            break;

        default:
            break;
    }

    dumb.sp18[0] = &menuLvSel->musicSelector;
    menuMusicItem_draw1(dumb.sp18, ARRAY_COUNTU(dumb.sp18), &gfx);
    dumb.sp1C[0] = &menuLvSel->speedIcon;
    dumb.sp20[0] = &menuLvSel->speedSelector;
    menuSpeedAsk_draw(dumb.sp1C, ARRAY_COUNTU(dumb.sp1C), &gfx);
    menuSpeedItem_draw1(dumb.sp20, ARRAY_COUNTU(dumb.sp20), &gfx);

    switch (menuLvSel->unk_0004) {
        case MAINMENUMODE_MENULVSEL_10:
        case MAINMENUMODE_MENULVSEL_13:
            dumb.sp24[0] = &menuLvSel->gameLvlIcon;
            dumb.sp28[0] = &menuLvSel->gameLvlSelector;
            menuSpeedAsk_draw((void *)dumb.sp24, ARRAY_COUNTU(dumb.sp24), &gfx);
            menuSpeedItem_draw1((void *)dumb.sp28, ARRAY_COUNTU(dumb.sp28), &gfx);
            break;

        case MAINMENUMODE_MENULVSEL_7:
            dumb.sp24[0] = &menuLvSel->virusLvlNumber;
            dumb.sp28[0] = &menuLvSel->virusLvlGauge;
            menuNumber_draw((void *)dumb.sp24, ARRAY_COUNTU(dumb.sp24), &gfx);
            menuLvGauge_draw1((void *)dumb.sp28, ARRAY_COUNTU(dumb.sp28), &gfx);
            break;

        default:
            break;
    }

    for (i = 0; i < ARRAY_COUNTU(dumb.sp2C); i++) {
        dumb.sp2C[i] = &menuLvSel->unk_162C[i];
    }

    func_80048634(dumb.sp2C, ARRAY_COUNTU(dumb.sp2C), &gfx);

    func_8004A780(dumb.sp18, ARRAY_COUNTU(dumb.sp18), &gfx);
    func_8004A160(dumb.sp20, ARRAY_COUNTU(dumb.sp20), &gfx);

    switch (menuLvSel->unk_0004) {
        case MAINMENUMODE_MENULVSEL_10:
        case MAINMENUMODE_MENULVSEL_13:
            func_8004A160((void *)dumb.sp28, 1, &gfx);
            break;

        case MAINMENUMODE_MENULVSEL_7:
            func_80048FA0((void *)dumb.sp28, 1, &gfx);
            break;

        default:
            break;
    }

    menuBottle_draw(&menuLvSel->bottle, &gfx);
    *gfxP = gfx;
}

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8005380C);

INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800B0B50);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800B0B54);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", menuChSel_init);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80053C2C);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80053C84);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80053CEC);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80053FBC);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_800540B8);

INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800B0C5C);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", menuChSel_input);

INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800B0D84);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800B0D94);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800B0D9C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800B0DA0);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800B0DAC);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800B0DB4);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800B0DB8);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800B0DC4);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800B0DC8);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800B0DD4);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800B0DD8);

#if 0
? func_80046614(s8 *, s32);
? func_8004ACF4(void *, s32);
? func_8004AD84(void *, void *);
s32 func_80053C2C(MenuRank *, ?, u32, ?);
? menuCursor_update(void *, void *);
extern ? D_800B0D84;

void menuChSel_update(MenuRank *menuRank) {
    s32 temp_v1;
    s32 temp_v1_2;
    s32 var_a1;
    s32 var_a1_2;
    s32 var_s0;
    s32 var_s2_3;
    s32 var_s3;
    s32 var_s4;
    s32 var_s4_2;
    s32 var_s5;
    s32 var_v0;
    MenuItem *temp_v0;
    MenuRank *var_s3_2;
    MenuRank *var_s3_3;
    u32 var_s2;
    u32 var_s2_2;
    u8 var_v1;
    void *temp_a0;
    void *temp_s0;
    void *temp_s0_2;

    temp_v0 = _getRootItem(arg0->unk_0000);
    func_800464BC((MenuItem *) &arg0->unk_0020[0x54], temp_v0);

    temp_v1 = arg0->unk_28;
    if ((temp_v1 < 2) && (temp_v1 >= 0)) {
        var_a1 = -(arg0->unk_2C == 0) | 1;
    } else {
        var_a1 = -1;
    }
    var_s2 = 0;
    func_80046614(&arg0->unk_0020[0xE4], var_a1);
    func_800464BC((MenuItem *) &arg0->unk_0020[0xE4], temp_v0);
    func_800464F8((MenuItem *) &arg0->unk_017C.unk_18, 0xF, (MenuItem *) &arg0->unk_0020[0x54]);
    var_s3 = 0x194;
    var_s0 = 0xA04;
    do {
        if (func_80053C2C(arg0, -1, var_s2, 1) != 0) {
            var_a1_2 = -1;
        } else {
            var_a1_2 = 1;
        }
        var_s2 += 1;
        func_80046614(arg0 + var_s0, var_a1_2);
        func_800464BC(arg0 + var_s0, arg0 + var_s3);
        var_s3 += 0x90;
        var_s0 += 0x90;
    } while (var_s2 < 0xFU);
    var_s2_2 = 0;
    var_s5 = 0x194;
    var_s4 = 0x1274;
    var_s3_2 = arg0;
    do {
        var_v1 = *(&D_800B0D84 + var_s2_2);
        temp_s0 = arg0 + var_s4;
        if (arg0->unk_2C != 0) {
            var_v1 += arg0->unk_30;
        }
        temp_a0 = temp_s0;
        var_s3_2->unk_1278 = (s32) var_v1;
        var_s4 += 0x128;
        var_s3_2 += 0x128;
        func_8004ACF4(temp_a0, -(var_s2_2 != arg0->unk_34) | 1);
        func_8004AD84(temp_s0, arg0 + var_s5);
        var_s2_2 += 1;
        var_s5 += 0x90;
    } while (var_s2_2 < 0xFU);
    var_s2_3 = 0;
    if ((s32) arg0->unk_0004 > 0) {
        var_s3_3 = arg0;
        var_s4_2 = 0x23CC;
        do {
            temp_s0_2 = arg0 + var_s4_2;
            menuCursor_update(temp_s0_2, arg0 + ((var_s3_3->unk_0008 * 0x90) + 0x194));
            temp_v1_2 = var_s3_3->unk_0018;
            if (temp_v1_2 == 0) {
                var_v0 = temp_s0_2->unk_1C | 0x80000000 | 0x20000000 | 0x10000000;
                goto block_26;
            }
            if (temp_v1_2 <= 0) {
                if (temp_v1_2 != -1) {
                    var_s3_3 += 4;
                } else {
                    temp_s0_2->unk_1C = (s32) (temp_s0_2->unk_1C & 0x7FFFFFFF & 0xDFFFFFFF & 0xEFFFFFFF);
                    goto block_27;
                }
            } else if (temp_v1_2 != 1) {
                var_s3_3 += 4;
            } else {
                var_v0 = (temp_s0_2->unk_1C | 0x80000000 | 0x20000000) & 0xEFFFFFFF;
block_26:
                temp_s0_2->unk_1C = var_v0;
block_27:
                var_s3_3 += 4;
            }
            var_s2_3 += 1;
            var_s4_2 += 0x260;
        } while (var_s2_3 < (s32) arg0->unk_0004);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", menuChSel_update);
#endif

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", menuChSel_draw);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80054A94);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", menuPlay2_init);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_800550F4);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80055154);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_800551BC);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80055254);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_800552EC);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80055598);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", menuPlay2_input);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", menuPlay2_update);

INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800B0F5C);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", menuPlay2_draw);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80055DFC);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", menuNmEnt_init);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_800560D4);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", menuNmEnt_input);

INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800B1168);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", menuNmEnt_update);

extern u8 **D_8008E86C;
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
        var_s2 = *(&D_8008E86C + (((arg0->unk_0004 * 4) + arg0)->unk_14 * 4));

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
INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", menuNmEnt_draw);
#endif

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80056C84);

void func_80056CAC(MenuRankBase *arg0, MenuItem *arg1) {
    func_800464BC(&arg0->unk_04, arg1);
}

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", menuRankBase_draw);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80056DF0);

void func_80056E1C(MenuRankNum *arg0, MenuItem *arg1) {
    func_800464BC(&arg0->unk_08, arg1);
}

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", menuRankNum_draw);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80057014);

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
INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", menuRankFig_update);
#endif

INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", _posX_0_9712);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", _posX_1_9713);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", _posX_2_9714);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", _posX_4_9715);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800B1210);

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

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8005768C);

INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800B1220);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800B1230);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800B123C);

ASM_TEXT;

void func_80057724(MenuRankName *arg0, MenuItem *arg1) {
    func_800464BC(&arg0->unk_08, arg1);
}

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", menuRankName_draw);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80057898);

void func_800578C8(MenuRankLabel *arg0, MenuItem *arg1) {
    func_800464BC(&arg0->unk_0C, arg1);
}

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", menuRankLabel_draw);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80057AFC);

void func_80057BE8(MenuRankHeader *arg0, MenuItem *arg1) {
    s32 i;

    func_800464BC(&arg0->unk_08, arg1);

    for (i = 0; i < arg0->unk_04; i++) {
        func_800578C8(&arg0->unk_98[i], &arg0->unk_08);
    }
}

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", menuRankHeader_draw);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80057D24);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80057E68);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80057F6C);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8005806C);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_800581C8);

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

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_800585BC);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_800586A4);

INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800B1290);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800B1298);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800B12A8);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800B12B8);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800B12C8);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800B12D8);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800B12E4);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800B12F0);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800B12FC);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800B1308);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800B1314);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", menuRank_setFrame);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80058A24);

INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800B1320);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800B1330);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800B1340);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800B1350);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800B1360);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800B1370);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", menuRank_setPanel);

const s32 _lr_10544[][2] = {
    { 0x23, 0x1E },
    { 0xDD, 0x1E },
};

void menuRank_init(MenuRank *menuRank, struct_watchMenu *arg1, struct_watchMenu_unk_02470 **arg2 UNUSED) {
    u32 i;

    menuRank->unk_0000 = (struct_watchMenu *)arg1;
    menuRank->unk_0004 = _getMode(arg1);
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
    u16 pressedButton = _getKeyTrg(menuRank->unk_0000, 0);
    s32 direction;
    SndIndex sndIndex;

    _getKeyRep(menuRank->unk_0000, 0);
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
            _setMode(menuRank->unk_0000, MAINMENUMODE_MENUMAIN_0);
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

void menuRank_update(MenuRank *menuRank) {
    MenuItem *temp_v0 = _getRootItem(menuRank->unk_0000);
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

INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800B1430);

extern s32 _dir_10660[];
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", _dir_10660);

void menuRank_draw(MenuRank *menuRank, Gfx **gfxP) {
    void *sp18[16];
    Gfx *gfx = *gfxP;
    s32 i;
    s32 j;

    gSPDisplayList(gfx++, fade_normal_texture_init_dl);

    if (menuRank->unk_0008 == 0) {
        menuItem_drawTex(&menuRank->unk_032C, &gfx, _getTexRank(menuRank->unk_0000, 3), 0);
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

            func_80046F58(temp_s0, &gfx, _getTexRank(menuRank->unk_0000, 4), 0, 2, i);
            temp_s0->unk_0C[0] += 12.0f;
            temp_s0->unk_0C[1] += 2.0f;

            func_80046F58(&menuRank->unk_020C[i], &gfx, _getTexRank(menuRank->unk_0000, 2), 0, 6, j);
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

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_800599E0);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80059A58);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80059AA4);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80059AF0);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80059B5C);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80059BC8);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80059C34);

/* drMarioRetrace? */
void func_80059CA0(struct_watchMenu *arg0) {
    osRecvMesg(&arg0->unk_0000C, NULL, OS_MESG_BLOCK);
}

Mtx **_getMtxPtr(struct_watchMenu *watchMenuRef) {
    return &watchMenuRef->unk_02448[gfx_gtask_no];
}

Vtx **_getVtxPtr(struct_watchMenu *watchMenuRef) {
    return &watchMenuRef->unk_02454[gfx_gtask_no];
}

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80059CF4);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", _getTexCommon);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80059D14);

TiTexDataEntry *_getTexLevel(struct_watchMenu *watchMenuRef, s32 index) {
    return &watchMenuRef->unk_02484->unk_00[index];
}

TiTexDataEntry *_getTexMain(struct_watchMenu *watchMenuRef, s32 index) {
    return &watchMenuRef->unk_02488->unk_00[index];
}

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", _getTexName);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80059D54);

TiTexDataEntry *_getTexP4(struct_watchMenu *watchMenuRef, s32 index) {
    return &watchMenuRef->unk_02494->unk_00[index];
}

TiTexDataEntry *_getTexRank(struct_watchMenu *watchMenuRef, s32 index) {
    return &watchMenuRef->unk_02498->unk_00[index];
}

TiTexDataEntry *_getTexSetup(struct_watchMenu *watchMenuRef, s32 index) {
    return &watchMenuRef->unk_0249C->unk_00[index];
}

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80059D94);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80059DA4);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80059DB4);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80059DC4);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80059DD4);

TiTexDataEntry *_getTexKasa(struct_watchMenu *watchMenuRef, s32 index) {
    return &watchMenuRef->unk_024B4->unk_00[index];
}

MenuItem *_getRootItem(struct_watchMenu *arg0) {
    return &arg0->unk_024B8[0];
}

u16 func_80059DFC(struct_watchMenu *arg0 UNUSED, s32 arg1) {
    return gControllerHoldButtons[main_joy[arg1]];
}

u16 _getKeyTrg(struct_watchMenu *arg0 UNUSED, s32 arg1) {
    return gControllerPressedButtons[main_joy[arg1]];
}

u16 _getKeyRep(struct_watchMenu *arg0 UNUSED, s32 arg1) {
    return joycur[main_joy[arg1]];
}

MainMenuMode _getMode(struct_watchMenu *arg0) {
    return arg0->unk_111CC;
}

MainMenuMode _getModeOld(struct_watchMenu *watchMenuRef) {
    return watchMenuRef->unk_111C8;
}

void _setMode(struct_watchMenu *arg0, MainMenuMode arg1) {
    arg0->unk_111D0 = arg1;
}

void _setNextMain(struct_watchMenu *arg0, enum_main_no arg1) {
    arg0->unk_111D4 = arg1;
}

void menuTitle_setTitle(struct_watchMenu *arg0, MainMenuMode arg1) {
    func_80047420(&arg0->unk_02548, arg1);
}

void _setFadeDir(struct_watchMenu *arg0, s32 arg1) {
    if (arg1 < 0) {
        if (arg0->unk_111E0 > 0.0f) {
            arg0->unk_111E0 = -arg0->unk_111E0;
        }
    } else {
        if (arg0->unk_111E0 < 0.0f) {
            arg0->unk_111E0 = -arg0->unk_111E0;
        }
    }
}

/**
 * Original name: menuAll_init
 */
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

    arg0->unk_111D0 = _menuAll_lastMode;
    arg0->unk_111CC = _menuAll_lastMode;
    arg0->unk_111C8 = _menuAll_lastMode;
    arg0->unk_111DC = 1.0f;
    arg0->unk_111C0 = 0;
    arg0->unk_111D8 = 0;
    arg0->unk_111EC = 0;
    arg0->unk_111F0 = 0;
    arg0->unk_111C4 = -1;
    arg0->unk_111D4 = MAIN_NO_6;
    arg0->unk_111E4 = 1;
    arg0->unk_111E0 = -(1.0f / 30.0f);
    arg0->unk_111E8 = 1;
    arg0->unk_111F4 = 0x7F;

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

void func_8005A2AC(struct_watchMenu *arg0) {
    func_8002A1DC(arg0->unk_00000, &arg0->unk_00004);
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
    MenuItem *var_v1 = &arg0->unk_024B8[0];
    MainMenuMode var_a0;
    f32 temp_f2_2;
    f32 var_f2;
    s32 i;
    s32 var_v1_2;

    arg0->unk_111DC = CLAMP(arg0->unk_111DC + arg0->unk_111E0, 0.0f, 1.0f);

    temp_f2_2 = (arg0->unk_111DC - 0.5) * 1.2 + 0.5;
    if (temp_f2_2 < 0.0f) {
        var_f2 = 1.0f;
    } else if (temp_f2_2 > 1.0f) {
        var_f2 = 0.0f;
    } else {
        var_f2 = 1.0 - temp_f2_2;
    }

    temp_f2_2 = var_f2;
    for (i = 0; i < 3; i++) {
        var_v1->unk_6C[1][i] = temp_f2_2;
        var_v1->unk_6C[0][i] = temp_f2_2;
    }

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
    TiTexDataEntry *temp_s3;
    s32 i;
    s32 var_s2;

    func_80046844(temp_s4, &gfx);
    draw_menu_bg(&gfx, arg0->unk_024B8[0].unk_0C[0] + 0.0f, -arg0->unk_024B8[0].unk_0C[1] - 120.0f);

    gSPDisplayList(gfx++, fade_normal_texture_init_dl);
    func_80046844(temp_s4, &gfx);

    var_s2 = 0;
    temp_s3 = _getTexCommon(arg0, 2);
    for (i = 0; i < 5; i++) {
        var_s2 += func_80046C74(temp_s4, &gfx, temp_s3, var_s2, (i << 6), 0, 1.0f, 1.0f);
    }

    for (; i < 10; i++) {
        var_s2 += func_80046C74(temp_s4, &gfx, temp_s3, var_s2, (i - 5) << 6, 200.0f, 1.0f, -1.0f);
    }

    *gfxP = gfx;
}

void menuAll_draw(struct_watchMenu *arg0, Gfx **gfxP) {
    u8 color;
    s32 i;

    arg0->unk_02448[gfx_gtask_no] = &arg0->unk_00048[gfx_gtask_no][0];
    arg0->unk_02454[gfx_gtask_no] = &arg0->unk_00C48[gfx_gtask_no][0];

    color = CLAMP((s32)((((arg0->unk_111DC - 0.5) * 1.2) + 0.5) * 255.0), 0, 255);

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
enum_main_no main_menu(struct_800EB670 *arg0) {
    UNK_PTR sp10 = Heap_bufferp;
    struct_watchMenu *ptr = ALIGN_PTR(Heap_bufferp);
    s32 i;
    u16 value;

    if (main_old == MAIN_NO_3) {
        _menuAll_lastMode = MAINMENUMODE_MENUMAIN_0;
        _menuMain_lastMode = 0;
        _menuMain_lastDepth = 0;
        _menuMain_lastSelect[0] = 0;
    }
    func_80040A64();
    sp10 = &ptr[1];
    bzero(ptr, sizeof(struct_watchMenu));
    watchMenu = ptr;
    menuAll_init(ptr, &sp10, arg0);

    evs_playmax = joyResponseCheck();

    value = 0xF30;
    for (i = ARRAY_COUNT(joyflg) - 1; i >= 0; i--) {
        joyflg[i] = value;
    }

    joycur1 = 0x18;
    joycur2 = 6;
    gGfxHead = gGfxGlist[gfx_gtask_no];
    dm_seq_play(0xC);

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
        }

        func_80059CA0(ptr);
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
    osSetThreadPri(NULL, 0x7F);
}

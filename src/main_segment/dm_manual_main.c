/**
 * Original filename: dm_manual_main.c
 */

#include "dm_manual_main.h"
#include "libultra.h"
#include "include_asm.h"
#include "macros_defines.h"
#include "unknown_structs.h"
#include "main_segment_functions.h"
#include "main_segment_variables.h"
#include "boot_functions.h"
#include "boot_variables.h"
#include "audio/audio_stuff.h"
#include "graphic.h"
#include "msgwnd.h"
#include "aif.h"
#include "joy.h"
#include "main1x.h"
#include "tex_func.h"
#include "main_story.h"

#if VERSION_US
void func_80071EF0(struct_800F4890_unk_034 *arg0, s32 arg1, s32 arg2) {
    arg0->unk_00 = arg1;
    arg0->unk_04 = arg2;
    arg0->messageWnd.unk_28 = arg1 + 8;
    arg0->messageWnd.unk_2C = arg2 + 8;
}
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_manual_main", func_8007B0F0_cn);
#endif

#if VERSION_US || VERSION_CN
void func_80071F0C(void) {
}
#endif

#if VERSION_US
void func_80071F14(struct_800F4890_unk_034 *arg0, UNK_PTR *arg1) {
    arg0->unk_08 = 0;
    arg0->unk_0C = -0.0625f;
    msgWnd_init(&arg0->messageWnd, arg1, 0xD, 4, 0x20, 0x20);
    arg0->messageWnd.unk_30 = 0xA;
    arg0->messageWnd.unk_34 = 0xC;
    arg0->messageWnd.unk_3C = 5;
    arg0->messageWnd.unk_48 = 0xD;
    arg0->messageWnd.unk_54 = 1.0f / 6.0f;
    func_80071EF0(arg0, 0x20, 0x20);
}
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_manual_main", func_80071F14);
#endif

#if VERSION_US || VERSION_CN
void func_80071FA0(struct_800F4890_unk_034 *arg0) {
    arg0->unk_08 = CLAMP(arg0->unk_08 + arg0->unk_0C, 0.0f, 1.0f);

    if (arg0->unk_08 == 1.0) {
        msgWnd_update(&arg0->messageWnd);
    }
}
#endif

#if VERSION_US || VERSION_CN
void tutolWnd_draw(struct_800F4890_unk_034 *arg0, Gfx **gfxP) {
    Gfx *gfx = *gfxP;
    s32 alpha = arg0->unk_08 * 255;
    TiTexDataEntry *temp_a1;

    if (alpha == 0) {
        return;
    }

    gSPDisplayList(gfx++, normal_texture_init_dl);
    gDPSetCombineMode(gfx++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);

    if (alpha < 0xFF) {
        gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    }

    gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, alpha);

    temp_a1 = &_texAll->unk_00[8];
    tiStretchTexBlock(&gfx, temp_a1, 0, arg0->unk_00, arg0->unk_04, temp_a1->unk_4[0], temp_a1->unk_4[1]);

    if (arg0->unk_08 != 0.0f) {
        arg0->messageWnd.unk_74 = alpha;
        msgWnd_draw(&arg0->messageWnd, &gfx);
    }

    *gfxP = gfx;
}
#endif

#if VERSION_US
void func_800721A0(struct_800F4890_unk_034 *arg0) {
    msgWnd_clear(&arg0->messageWnd);
}
#endif

#if VERSION_US
void func_800721BC(struct_800F4890_unk_034 *arg0, const char *arg1) {
    msgWnd_addStr(&arg0->messageWnd, arg1);
}
#endif

#if VERSION_US
void func_800721D8(struct_800F4890_unk_034 *arg0) {
    if (arg0->unk_0C < 0.0f) {
        arg0->unk_0C = -arg0->unk_0C;
    }
}
#endif

#if VERSION_US
void func_80072204(struct_800F4890_unk_034 *arg0) {
    if (arg0->unk_0C > 0.0f) {
        arg0->unk_0C = -arg0->unk_0C;
    }
}
#endif

#if VERSION_US
bool func_80072230(struct_800F4890_unk_034 *arg0) {
    return msgWnd_isEnd(&arg0->messageWnd);
}
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_manual_main", func_8007B3C4_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_manual_main", func_8007B3F0_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_manual_main", func_800721D8);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_manual_main", func_8007B440_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_manual_main", func_8007B464_cn);
#endif

#if VERSION_US || VERSION_CN
bool func_8007224C(struct_800F4890_unk_034 *arg0) {
    return msgWnd_isSpeaking(&arg0->messageWnd);
}
#endif

#if VERSION_US
void func_80072268(struct_800F4890_unk_0E8 *arg0, s32 arg1, s32 arg2) {
    arg0->unk_0 = arg1;
    arg0->unk_1 = 1;
    arg0->unk_2 = arg2;
    arg0->unk_3[0] = 1;
}
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_manual_main", func_8007B4BC_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_manual_main", func_8007B4D4_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_manual_main", func_8007B6C4_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_manual_main", func_8007B704_cn);
#endif

#if VERSION_US
const s32 RO_800B2408 = 0xC8;
const s32 RO_800B240C = 0x28;
const s32 RO_800B2410 = 0x6C;
const s32 RO_800B2414 = 0x28;
const s32 RO_800B2418 = 0x24;
const s32 RO_800B241C = 0x28;
const s32 RO_800B2420 = 0xB4;
const s32 RO_800B2424 = 0x28;
const s32 RO_800B2428 = 0xD8;
const s32 RO_800B242C = 0x70;
const s32 RO_800B2430 = 0x7C;
const s32 RO_800B2434 = 0x70;
const s32 RO_800B2438 = 0x34;
const s32 RO_800B243C = 0x70;
const s32 RO_800B2440 = 0xC4;
const s32 RO_800B2444 = 0x70;
#endif

#if VERSION_US
const u8 virus_1_1[][3] = {
    { 1, 1, 0x10 }, { 2, 2, 0xD }, { 2, 2, 0xE }, { 0, 5, 0xF }, { 0, 1, 6 }, { 0, 5, 6 },
    { 2, 0, 6 },    { 2, 4, 6 },   { 1, 2, 6 },   { 1, 3, 6 },   { 1, 6, 6 }, { 1, 7, 6 },
};
#endif

#if VERSION_US
const u8 RO_800B246C[] = { 0x12, 0x20, 0, 0x10, 0x21 };
#endif
#if VERSION_US
const u8 RO_800B2474[] = { 0x21, 0x10, 0x20, 0, 0x21 };
#endif

#if VERSION_US
const u8 position_1_1[][4] = {
    { 3, 5, 1, 0 },
    { 3, 3, 0, 0 },
    { 3, 2, 0, 0 },
    { 3, 1, 0, 0 },
};
#endif

#if VERSION_US
const u8 virus_2_1[][3] = {
    { 0, 0, 0xE }, { 0, 2, 0xA }, { 0, 2, 0xB }, { 0, 5, 8 },    { 0, 5, 9 },    { 0, 6, 0xC }, { 0, 6, 0xE },
    { 2, 3, 0xE }, { 2, 4, 7 },   { 2, 4, 8 },   { 2, 5, 0xB },  { 2, 5, 0xC },  { 2, 5, 0xE }, { 2, 5, 0xF },
    { 1, 1, 7 },   { 1, 1, 0xA }, { 1, 1, 0xB }, { 1, 1, 0x10 }, { 1, 2, 0x10 }, { 1, 7, 0xF },
};
#endif

#if VERSION_US
const u8 capsel_2_1[] = {
    0x21, 0x02, 0x10, 0x12, 0x21, 0x00, 0x01, 0x20, 0x21, 0x12, 0x10, 0x10,
};
#endif

#if VERSION_US
const u8 position_2_1[][4] = {
    { 4, 6, 0, 0 },   { 4, 5, 0, 1 }, { 7, 0xE, 1, 0 }, { 6, 0xB, 0, 1 }, { 5, 0xD, 0, 0 },
    { 0, 0xD, 1, 0 }, { 0, 9, 0, 0 }, { 3, 0xD, 1, 0 }, { 2, 9, 0, 1 },   { 1, 8, 0, 0 },
};
#endif

#if VERSION_US
const u8 virus_3_1[][3] = {
    { 0, 0, 0xC }, { 0, 1, 0xD }, { 0, 1, 0xF }, { 0, 4, 0xF }, { 0, 6, 0xD },  { 0, 6, 8 },    { 0, 7, 0x10 },
    { 2, 3, 8 },   { 2, 3, 9 },   { 2, 3, 0xB }, { 2, 3, 0xC }, { 2, 7, 0xE },  { 2, 7, 0xF },  { 1, 1, 0x10 },
    { 1, 2, 8 },   { 1, 2, 0xC }, { 1, 4, 0xD }, { 1, 4, 0xE }, { 1, 4, 0x10 }, { 1, 5, 0x10 },
};
#endif

#if VERSION_US
const u8 RO_800B2538[] = {
    0x12, 0x22, 0x12, 0, 0x10, 2, 0x21, 0, 0x12, 1, 0,
};
#endif

#if VERSION_US
const u8 position_3_1[][4] = {
    { 4, 0xC, 0, 0 }, { 3, 0xA, 0, 0 }, { 1, 0xB, 0, 1 }, { 1, 0xA, 1, 0 },  { 2, 0xA, 1, 0 },
    { 6, 0xC, 0, 0 }, { 6, 0xB, 0, 1 }, { 6, 0xA, 1, 0 }, { 2, 0x10, 1, 1 }, { 3, 0x10, 1, 0 },
};
#endif

#if VERSION_US
const u8 virus_4_1[][3] = {
    { 0, 0, 0xD }, { 0, 2, 7 },   { 0, 5, 0xA }, { 0, 5, 0xB }, { 0, 7, 0x10 }, { 2, 2, 0xE },
    { 2, 2, 0xF }, { 2, 3, 0xA }, { 2, 3, 0xD }, { 2, 5, 8 },   { 1, 1, 0xD },  { 1, 4, 8 },
    { 1, 4, 9 },   { 1, 5, 0xE }, { 1, 5, 0xF }, { 1, 6, 0xA },
};
#endif

#if VERSION_US
const u8 RO_800B259C[] = {
    0x10, 0x11, 0x20, 1, 0x12, 0x20, 1, 0x10, 0, 0x20, 0, 0x21, 1, 0x20, 0x22, 0, 0x10,
};
#endif

#if VERSION_US
const u8 position_4_1[][4] = {
    { 4, 7, 1, 0 },   { 5, 7, 0, 1 },   { 5, 6, 1, 0 },   { 5, 8, 0, 0 },   { 5, 7, 0, 1 },   { 3, 0xC, 1, 0 },
    { 0, 0xC, 0, 0 }, { 1, 0xB, 1, 0 }, { 0, 0xB, 1, 0 }, { 2, 0xD, 1, 0 }, { 7, 0xF, 1, 0 }, { 6, 0xD, 0, 0 },
    { 2, 6, 0, 0 },   { 3, 5, 1, 0 },   { 3, 3, 0, 0 },   { 2, 5, 1, 0 },
};
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/dm_manual_main", RO_800C89C0_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/dm_manual_main", RO_800C89C8_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/dm_manual_main", RO_800C89D0_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/dm_manual_main", RO_800C89D8_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/dm_manual_main", RO_800C89E0_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/dm_manual_main", RO_800C89E8_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/dm_manual_main", RO_800C89F0_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/dm_manual_main", RO_800C89F8_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/dm_manual_main", RO_800C8A00_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/dm_manual_main", RO_800C8A24_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/dm_manual_main", RO_800C8A2C_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/dm_manual_main", RO_800C8A34_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/dm_manual_main", RO_800C8A44_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/dm_manual_main", RO_800C8A80_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/dm_manual_main", RO_800C8A8C_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/dm_manual_main", RO_800C8AB4_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/dm_manual_main", RO_800C8AF0_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/dm_manual_main", RO_800C8AFC_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/dm_manual_main", RO_800C8B24_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/dm_manual_main", RO_800C8B54_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/dm_manual_main", RO_800C8B68_cn);
#endif

// clang-format off
const char mes_1_1[] = MSG_COLOR(WHITE)
#if VERSION_US
    "Hello, everyone!" MSG_NEWLINE
    "I'm Paragoom."
#endif
#if VERSION_CN
    "大家好！" MSG_NEWLINE
    "我是帕拉贡。"
#endif
    MSG_W(2) MSG_END;

const char mes_1_2[] = MSG_COLOR(WHITE)
#if VERSION_US
    "I'm here to tell" MSG_NEWLINE
    "you how to play" MSG_NEWLINE
    "Dr. Mario. Please" MSG_NEWLINE
    "pay attention."
#endif
#if VERSION_CN
    "我在这里告诉你" MSG_NEWLINE
    "如何玩马力欧医" MSG_NEWLINE
    "生。" MSG_NEWLINE
    "请注意! "
#endif
    MSG_W(2) MSG_END;

const char mes_1_3[] = MSG_COLOR(WHITE)
#if VERSION_US
    "It's all about" MSG_NEWLINE
    "vitamins! Toss 'em" MSG_NEWLINE
    "into the bottle to" MSG_NEWLINE
    "destroy viruses."
#endif
#if VERSION_CN
    "这个游戏是把维" MSG_NEWLINE
    "生素药丸扔进瓶" MSG_NEWLINE
    "子消灭病毒。" MSG_W(2)
    MSG_END
    "这个游戏是把维" MSG_NEWLINE
    "生素药丸扔进瓶" MSG_NEWLINE
    "子消灭病毒。"
#endif
    MSG_W(2) MSG_END;

const char mes_1_4[] = MSG_COLOR(WHITE)
#if VERSION_US
    "Press the A and" MSG_NEWLINE
    "B Buttons to" MSG_NEWLINE
    "rotate capsules."
#endif
#if VERSION_CN
    "按Ａ和Ｂ键旋转" MSG_NEWLINE
    "药丸。"
#endif
    MSG_W(2) MSG_END;

const char mes_1_5[] = MSG_COLOR(WHITE)
#if VERSION_US
    "Clear vitamins by" MSG_NEWLINE
    "making four or" MSG_NEWLINE
    "more matching" MSG_NEWLINE
    "columns or rows."
#endif
#if VERSION_CN
    "纵向或横向排列" MSG_NEWLINE
    "四个或以上同色" MSG_NEWLINE
    "药丸可以消除它" MSG_NEWLINE
    "们。"
#endif
    MSG_W(2) MSG_END;

const char mes_1_6[] = MSG_COLOR(WHITE)
#if VERSION_US
    "Clear a stage by" MSG_NEWLINE
    "destroying all" MSG_NEWLINE
    "of the viruses" MSG_NEWLINE
    "in the bottle."
#endif
#if VERSION_CN
    "消灭瓶中所有病" MSG_NEWLINE
    "毒就可以过关。"
#endif
    MSG_W(2) MSG_END;

const char mes_1_7[] = MSG_COLOR(WHITE)
#if VERSION_US
    "If the bottle gets" MSG_NEWLINE
    "filled all the way" MSG_NEWLINE
    "to the top, your" MSG_NEWLINE
    "game will be over."
#endif
#if VERSION_CN
    "如果瓶子装满的" MSG_NEWLINE
    "话，游戏就结束" MSG_NEWLINE
    "了。"
#endif
    MSG_W(2) MSG_END;

const char mes_1_8[] = MSG_COLOR(WHITE)
#if VERSION_US
    "That's all" MSG_NEWLINE
    "for now. I'll" MSG_NEWLINE
    "see you later!"
#endif
#if VERSION_CN
    "就先到这里吧，" MSG_NEWLINE
    "等会儿见！"
#endif
    MSG_W(2) MSG_END;

const char mes_2_1[] = MSG_COLOR(WHITE)
#if VERSION_US
    "Now I'll tell" MSG_NEWLINE
    "you about the" MSG_NEWLINE
    "Two-Player Vs." MSG_NEWLINE
    "game rules!"
#endif
#if VERSION_CN
    "现在让我向你介" MSG_NEWLINE
    "绍二人对战的游" MSG_NEWLINE
    "戏规则。"
#endif
    MSG_W(2) MSG_END;

const char mes_2_2[] = MSG_COLOR(WHITE)
#if VERSION_US
    "Destroy all the" MSG_NEWLINE
    "viruses faster" MSG_NEWLINE
    "than your rival" MSG_NEWLINE
    "does to win."
#endif
#if VERSION_CN
    "要赢得比赛，就" MSG_NEWLINE
    "要比对手更快地" MSG_NEWLINE
    "消灭病毒。"
#endif
    MSG_W(2) MSG_END;

const char mes_2_3[] = MSG_COLOR(WHITE)
#if VERSION_US
    "If your bottle" MSG_NEWLINE
    "fills up all the" MSG_NEWLINE
    "way to the top," MSG_NEWLINE
    "you'll lose."
#endif
#if VERSION_CN
    "如果你的瓶子装" MSG_NEWLINE
    "满到瓶口的话，" MSG_NEWLINE
    "你就输了。"
#endif
    MSG_W(2) MSG_END;

const char mes_2_4[] = MSG_COLOR(WHITE)
#if VERSION_US
    "Clear combos" MSG_NEWLINE
    "to send garbage" MSG_NEWLINE
    "to your opponent."
#endif
#if VERSION_CN
    "完成连消可以把" MSG_NEWLINE
    "垃圾送给对手。"
#endif
    MSG_W(2) MSG_END;

const char mes_2_5[] = MSG_COLOR(WHITE)
#if VERSION_US
    "The more combos" MSG_NEWLINE
    "you clear, the" MSG_NEWLINE
    "more garbage" MSG_NEWLINE
    "you'll send!"
#endif
#if VERSION_CN
    "连消次数越多," MSG_NEWLINE
    "送出去的垃圾就" MSG_NEWLINE
    "越多！"
#endif
    MSG_W(2) MSG_END;

const char mes_2_6[] = MSG_COLOR(WHITE)
#if VERSION_US
    "Clear two combos" MSG_NEWLINE
    "to send two" MSG_NEWLINE
    "pieces of garbage."
#endif
#if VERSION_CN
    "完成两次连消送" MSG_NEWLINE
    "出两个垃圾。"
#endif
    MSG_W(2) MSG_END;

const char mes_2_7[] = MSG_COLOR(WHITE)
#if VERSION_US
    "Clear three combos" MSG_NEWLINE
    "for three pieces," MSG_NEWLINE
    "four combos for" MSG_NEWLINE
    "four pieces."
#endif
#if VERSION_CN
    "完成三次连消送" MSG_NEWLINE
    "出三个垃圾。完" MSG_NEWLINE
    "成四次连消送出" MSG_NEWLINE
    "四个垃圾。"
#endif
    MSG_W(2) MSG_END;

const char mes_2_8[] = MSG_COLOR(WHITE)
#if VERSION_US
    "But four pieces" MSG_NEWLINE
    "is the most you" MSG_NEWLINE
    "can send at one" MSG_NEWLINE
    "time."
#endif
#if VERSION_CN
    "一次最多送出四" MSG_NEWLINE
    "个垃圾。"
#endif
    MSG_W(2) MSG_END;

const char mes_2_9[] = MSG_COLOR(WHITE)
#if VERSION_US
    "That's all" MSG_NEWLINE
    "for now! I'll" MSG_NEWLINE
    "see you later!"
#endif
#if VERSION_CN
    "就先到这里吧，" MSG_NEWLINE
    "等会儿见！"
#endif
    MSG_W(2) MSG_END;

const char mes_3_1[] = MSG_COLOR(WHITE)
#if VERSION_US
    "Now I'll tell" MSG_NEWLINE
    "you about the" MSG_NEWLINE
    "Four-Player Vs." MSG_NEWLINE
    "game rules!"
#endif
#if VERSION_CN
    "现在让我向你介" MSG_NEWLINE
    "绍四人对战的游" MSG_NEWLINE
    "戏规则。"
#endif
    MSG_W(2) MSG_END;

const char mes_3_2[] = MSG_COLOR(WHITE)
#if VERSION_US
    "Destroy all the" MSG_NEWLINE
    "viruses faster" MSG_NEWLINE
    "than your foes" MSG_NEWLINE
    "do to win."
#endif
#if VERSION_CN
    "要赢得比赛，就" MSG_NEWLINE
    "要比对手更快地" MSG_NEWLINE
    "消灭病毒。"
#endif
    MSG_W(2) MSG_END;

const char mes_3_3[] = MSG_COLOR(WHITE)
#if VERSION_US
    "If your bottle" MSG_NEWLINE
    "fills up all the" MSG_NEWLINE
    "way to the top," MSG_NEWLINE
    "you'll lose."
#endif
#if VERSION_CN
    "如果你的瓶子装" MSG_NEWLINE
    "满到瓶口的话，" MSG_NEWLINE
    "你就输了。"
#endif
    MSG_W(2) MSG_END;

const char mes_3_4[] = MSG_COLOR(WHITE)
#if VERSION_US
    "Clear combos" MSG_NEWLINE
    "to send garbage" MSG_NEWLINE
    "to your foes."
#endif
#if VERSION_CN
    "完成连消可以把" MSG_NEWLINE
    "垃圾送给对手。"
#endif
    MSG_W(2) MSG_END;

const char mes_3_5[] = MSG_COLOR(WHITE)
#if VERSION_US
    "The color of the" MSG_NEWLINE
    "combo you clear" MSG_NEWLINE
    "determines where" MSG_NEWLINE
    "your garbage goes."
#endif
#if VERSION_CN
    "连消的颜色决定" MSG_NEWLINE
    "你的垃圾会送到" MSG_NEWLINE
    "哪里去。"
#endif
    MSG_W(2) MSG_END;

const char mes_3_6[] = MSG_COLOR(WHITE)
#if VERSION_US
    "If the combo is" MSG_NEWLINE
    "blue, the player" MSG_NEWLINE
    "on your right gets" MSG_NEWLINE
    "your garbage."
#endif
#if VERSION_CN
    "如果是蓝色，在" MSG_NEWLINE
    "你右边的玩家会" MSG_NEWLINE
    "收到垃圾。"
#endif
    MSG_W(2) MSG_END;

const char mes_3_7[] = MSG_COLOR(WHITE)
#if VERSION_US
    "If the combo is" MSG_NEWLINE
    "yellow, it goes to" MSG_NEWLINE
    "the second player" MSG_NEWLINE
    "on your right."
#endif
#if VERSION_CN
    "如果是黄色，在" MSG_NEWLINE
    "你右边的第二个" MSG_NEWLINE
    "玩家会收到垃圾。"
#endif
    MSG_W(2) MSG_END;

const char mes_3_8[] = MSG_COLOR(WHITE)
#if VERSION_US
    "If the combo is" MSG_NEWLINE
    "red, it goes to" MSG_NEWLINE
    "the third player" MSG_NEWLINE
    "on your right."
#endif
#if VERSION_CN
    "如果是红色，在" MSG_NEWLINE
    "你右边的第三个" MSG_NEWLINE
    "玩家会收到垃圾。"
#endif
    MSG_W(2) MSG_END;

const char mes_3_9[] = MSG_COLOR(WHITE)
#if VERSION_US
    "Clear two colors" MSG_NEWLINE
    "at the same time" MSG_NEWLINE
    "to send garbage" MSG_NEWLINE
    "to two players."
#endif
#if VERSION_CN
    "一次消掉两种颜" MSG_NEWLINE
    "色可以让两个玩" MSG_NEWLINE
    "家收到垃圾。"
#endif
    MSG_W(2) MSG_END;

const char mes_3_10[] = MSG_COLOR(WHITE)
#if VERSION_US
    "If no one is on" MSG_NEWLINE
    "your right, your" MSG_NEWLINE
    "garbage goes" MSG_NEWLINE
    "to the far left."
#endif
#if VERSION_CN
    "如果在你右边的" MSG_NEWLINE
    "没有人你送出的" MSG_NEWLINE
    "垃圾就到最左边。"
#endif
    MSG_W(2) MSG_END;

const char mes_3_11[] = MSG_COLOR(WHITE)
#if VERSION_US
    "When playing" MSG_NEWLINE
    "Team Battle, the" MSG_NEWLINE
    "garbage you send"
#endif
#if VERSION_CN
    "在分组对战模式" MSG_NEWLINE
    "下，你送给同伴" MSG_NEWLINE
    "的垃圾。"
#endif
    MSG_W(2) MSG_END;

const char mes_3_12[] = MSG_COLOR(WHITE)
#if VERSION_US
    "to your partner" MSG_NEWLINE
    "goes into" MSG_NEWLINE
    "your bank."
#endif
#if VERSION_CN
    "会送到你们的" MSG_NEWLINE
    "储备箱，"
#endif
    MSG_W(2) MSG_END;

const char mes_3_13[] = MSG_COLOR(WHITE)
#if VERSION_US
    "The garbage in" MSG_NEWLINE
    "your bank is" MSG_NEWLINE
    "automatically" MSG_NEWLINE
    "added to the next"
#endif
#if VERSION_CN
    "储备箱中的垃圾" MSG_NEWLINE
    "会自动加到"
#endif
    MSG_W(2) MSG_END;

const char mes_3_14[] = MSG_COLOR(WHITE)
#if VERSION_US
    "time either you" MSG_NEWLINE
    "or your teammate" MSG_NEWLINE
    "sends garbage to" MSG_NEWLINE
    "your opponents."
#endif
#if VERSION_CN
    "下一次你或你的" MSG_NEWLINE
    "同伴送给对手的" MSG_NEWLINE
    "垃圾中。"
#endif
    MSG_W(2) MSG_END;

const char mes_3_15[] = MSG_COLOR(WHITE)
#if VERSION_US
    "That's all" MSG_NEWLINE
    "for now! I'll" MSG_NEWLINE
    "see you later!"
#endif
#if VERSION_CN
    "就先到这里吧，" MSG_NEWLINE
    "等会儿见！"
#endif
    MSG_W(2) MSG_END;

const char mes_4_1[] = MSG_COLOR(WHITE)
#if VERSION_US
    "Now it's time" MSG_NEWLINE
    "for me to give" MSG_NEWLINE
    "you some advice."
#endif
#if VERSION_CN
    "现在我要给你一" MSG_NEWLINE
    "些提示。"
#endif
    MSG_W(2) MSG_END;

const char mes_4_2[] = MSG_COLOR(WHITE)
#if VERSION_US
    "At first, it's" MSG_NEWLINE
    "easier to match" MSG_NEWLINE
    "colors in a" MSG_NEWLINE
    "vertical row."
#endif
#if VERSION_CN
    "首先，纵向拼出" MSG_NEWLINE
    "同色药丸更容易。"
#endif
    MSG_W(2) MSG_END;

const char mes_4_3[] = MSG_COLOR(WHITE)
#if VERSION_US
    "But when you get" MSG_NEWLINE
    "better, try to" MSG_NEWLINE
    "match colors" MSG_NEWLINE
    "horizontally, too."
#endif
#if VERSION_CN
    "但当你的技巧熟" MSG_NEWLINE
    "练后，尽量也横" MSG_NEWLINE
    "向拼色。"
#endif
    MSG_W(2) MSG_END;

const char mes_4_4[] = MSG_COLOR(WHITE)
#if VERSION_US
    "A special melody" MSG_NEWLINE
    "plays when you've" MSG_NEWLINE
    "cleared a combo."
#endif
#if VERSION_CN
    "你完成连消时，" MSG_NEWLINE
    "会播放一段特别" MSG_NEWLINE
    "的旋律。"
#endif
    MSG_W(2) MSG_END;

const char mes_4_5[] = MSG_COLOR(WHITE)
#if VERSION_US
    "Don't forget!" MSG_NEWLINE
    "Vitamins begin to" MSG_NEWLINE
    "fall faster with" MSG_NEWLINE
    "every tenth one."
#endif
#if VERSION_CN
    "别忘了！每过十" MSG_NEWLINE
    "个药丸下落的速" MSG_NEWLINE
    "度会加快。"
#endif
    MSG_W(2) MSG_END;

const char mes_4_6[] = MSG_COLOR(WHITE)
#if VERSION_US
    "The music speeds" MSG_NEWLINE
    "up when few" MSG_NEWLINE
    "viruses remain."
#endif
#if VERSION_CN
    "当剩下的病毒不" MSG_NEWLINE
    "多时，音乐的速" MSG_NEWLINE
    "度会加快。"
#endif
    MSG_W(2) MSG_END;

const char mes_4_7[] = MSG_COLOR(WHITE)
#if VERSION_US
    "When your bottle" MSG_NEWLINE
    "begins to fill" MSG_NEWLINE
    "up, warning music" MSG_NEWLINE
    "will begin."
#endif
#if VERSION_CN
    "当你的瓶子快要" MSG_NEWLINE
    "装满时，会开始" MSG_NEWLINE
    "出现警告音乐。"
#endif
    MSG_W(2) MSG_END;

const char mes_4_8[] = MSG_COLOR(WHITE)
#if VERSION_US
    "Danger!" MSG_NEWLINE
    "You'd better" MSG_NEWLINE
    "hurry up!"
#endif
#if VERSION_CN
    "危险！" MSG_NEWLINE
    "你最好加快速度！"
#endif
    MSG_W(2) MSG_END;

const char mes_4_9[] = MSG_COLOR(WHITE)
#if VERSION_US
    "That's it." MSG_NEWLINE
    "Now get going!"
#endif
#if VERSION_CN
    "我要说的都说了。" MSG_NEWLINE
    "现在开始游戏吧！"
#endif
    MSG_W(2) MSG_END;

const char mes_4_10[] = MSG_COLOR(WHITE)
#if VERSION_US
    "See you later!" MSG_NEWLINE
    "Bye-bye!"
#endif
#if VERSION_CN
    "后会有期！" MSG_NEWLINE
    "再见！"
#endif
    MSG_W(2) MSG_END;
// clang-format on

#if VERSION_US
void dm_manual_attack_capsel_down(void) {
    struct_watchManual *watchManualP = watchManual;
    GameMapGrid *mapGrid = game_map_data;
    bool playSound = false;
    s32 i;

    for (i = 0; i < 4; i++) {
        watchManualP->unk_174[i]++;
        if (watchManualP->unk_174[i] >= 0xE) {
            s32 j;

            watchManualP->unk_174[i] = 0;

            for (j = 0; j < 4; j++) {
                if (watchManualP->unk_0E8[i][j].unk_3[0] == 0) {
                    continue;
                }

                if (get_map_info(&mapGrid[i], watchManualP->unk_0E8[i][j].unk_0,
                                 watchManualP->unk_0E8[i][j].unk_1 + 1)) {
                    set_map(&mapGrid[i], watchManualP->unk_0E8[i][j].unk_0, watchManualP->unk_0E8[i][j].unk_1, 4,
                            watchManualP->unk_0E8[i][j].unk_2);
                    watchManualP->unk_0E8[i][j].unk_3[0] = 0;
                } else {
                    playSound = true;

                    if (watchManualP->unk_0E8[i][j].unk_1 < 0x10) {
                        watchManualP->unk_0E8[i][j].unk_1++;
                    }

                    if (watchManualP->unk_0E8[i][j].unk_1 == 0x10) {
                        set_map(&mapGrid[i], watchManualP->unk_0E8[i][j].unk_0, 0x10, 4,
                                watchManualP->unk_0E8[i][j].unk_2);
                        watchManualP->unk_0E8[i][j].unk_3[0] = 0;
                    }
                }
            }
        }
    }

    if (playSound) {
        dm_snd_play(SND_INDEX_55);
    }
}
#endif

#if VERSION_US
void func_800723EC(struct_game_state_data *gameStateDataP, GameMapGrid *mapGrid, s32 arg2 UNUSED) {
    if ((gameStateDataP->unk_014 != 1) & (gameStateDataP->unk_014 != 0xD)) {
        dm_black_up(gameStateDataP, mapGrid);
    }
}
#endif

#if VERSION_US
void dm_manual_update_virus_anime(struct_game_state_data *arg0) {
    s32 i;

    for (i = 0; i < 3; i++) {
        animeState_update(get_virus_anime_state(i));
        animeSmog_update(get_virus_smog_state(i));
    }

    dm_calc_big_virus_pos(arg0);
}
#endif

#if VERSION_US
s32 dm_manual_main_cnt(struct_game_state_data *gameStateData, GameMapGrid *mapGrid, u8 arg2, s32 arg3 UNUSED) {
    struct_watchManual *temp_s3 = watchManual;
    s32 i;
    s32 var_s0_3;

    switch (gameStateData->unk_00C) {
        case 0x1:
        case 0x2:
            return 3;

        case 0x4:
            dm_capsel_down(gameStateData, mapGrid);
            break;

        case 0x5:
            if (dm_check_game_over(gameStateData, mapGrid)) {
                gameStateData->unk_014 = 4;
                gameStateData->unk_00C = 0xB;
                return -1;
            }

            if (dm_h_erase_chack(mapGrid) || dm_w_erase_chack(mapGrid)) {
                if (gameStateData->unk_049 == 0) {
                    gameStateData->unk_00C = 6;
                } else {
                    gameStateData->unk_00C = 0x15;
                }
                gameStateData->unk_02F = 0;
            } else if (gameStateData->unk_049 == 0) {
                gameStateData->unk_00C = 9;
            } else {
                gameStateData->unk_00C = 0x16;
            }
            break;

        case 0x6:
            gameStateData->unk_02F++;
            if (gameStateData->unk_02F >= 0x12U) {
                gameStateData->unk_02F = 0;
                gameStateData->unk_00C = 7;
                dm_h_erase_chack_set(gameStateData, mapGrid);
                dm_w_erase_chack_set(gameStateData, mapGrid);
                dm_h_ball_chack(mapGrid);
                dm_w_ball_chack(mapGrid);
                gameStateData->unk_025 =
                    get_virus_color_count(mapGrid, &temp_s3->unk_148[0], &temp_s3->unk_148[1], &temp_s3->unk_148[2]);

                switch (evs_manual_no) {
                    case EVS_MANUAL_NO_0:
                    case EVS_MANUAL_NO_3:
                        for (i = 0; i < ARRAY_COUNT(temp_s3->unk_14C); i++) {
                            if (temp_s3->unk_148[i] == 0) {
                                if (temp_s3->unk_14C[i].unk_0 == 0) {
                                    temp_s3->unk_14C[i].unk_0 = 1;
                                    animeState_set(get_virus_anime_state(i), 4);
                                    animeSmog_start(get_virus_smog_state(i));
                                    if (gameStateData->unk_025 != 0) {
                                        dm_snd_play(SND_INDEX_74);
                                    }
                                }
                            } else if (gameStateData->unk_03C[3] & (0x10 << i)) {
                                animeState_set(get_virus_anime_state(i), 2);
                                dm_snd_play(SND_INDEX_74);
                            }
                        }
                        break;

                    default:
                        break;
                }

                gameStateData->unk_03C[3] &= 0xF;

                if (gameStateData->unk_025 == 0) {
                    dm_make_score(gameStateData);
                    gameStateData->unk_014 = 3;
                    gameStateData->unk_00C = 0xA;
                    return 6;
                }
                if (((gameStateData->unk_025 != 0) && (gameStateData->unk_025 < 4U)) && (temp_s3->unk_170 == 0)) {
                    temp_s3->unk_170 = 1;
                    dm_snd_play(SND_INDEX_80);
                    dm_seq_play_in_game((evs_seqnumb * 2) | 1);
                }

                gameStateData->unk_039++;
                if (gameStateData->unk_03C[3] & 8) {
                    gameStateData->unk_03C[3] &= ~8;
                    dm_snd_play(SND_INDEX_56);
                } else {
                    dm_snd_play(SND_INDEX_61);
                }
            }
            break;

        case 0x7:
            dm_capsel_erase_anime(gameStateData, mapGrid);
            break;

        case 0x8:
            go_down(gameStateData, mapGrid, 0xE);
            break;

        case 0x9:
            dm_attack_se(gameStateData, arg2);
            dm_warning_h_line(gameStateData, mapGrid);
            aifMakeFlagSet(gameStateData);
            dm_set_capsel(gameStateData);
            dm_capsel_speed_up(gameStateData);
            gameStateData->unk_03A = 0;
            gameStateData->unk_039 = 0;
            gameStateData->unk_037 = 0;

            for (i = 0; i < ARRAY_COUNT(gameStateData->unk_03C); i++) {
                gameStateData->unk_03C[i] = 0;
            }

            gameStateData->unk_00C = 4;
            break;

        case 0xA:
            temp_s3->unk_02C++;
            if (temp_s3->unk_02C > 120) {
                temp_s3->unk_02C = 0;
                return 1;
            }
            break;

        case 0xB:
        case 0xD:
        case 0xF:
        case 0x11:
            temp_s3->unk_02C++;
            if (temp_s3->unk_02C > 120) {
                temp_s3->unk_02C = 0;
                return 0x64;
            }
            break;

        case 0x15:
            gameStateData->unk_02F++;
            if (gameStateData->unk_02F >= 0x12U) {
                gameStateData->unk_02F = 0;
                gameStateData->unk_00C = 7;
                dm_h_erase_chack_set(gameStateData, mapGrid);
                dm_w_erase_chack_set(gameStateData, mapGrid);
                dm_h_ball_chack(mapGrid);
                dm_w_ball_chack(mapGrid);

                gameStateData->unk_039 += 1;
                if (gameStateData->unk_03C[3] & 8) {
                    gameStateData->unk_03C[3] &= ~8;
                } else {
                    dm_snd_play(SND_INDEX_61);
                }
            }
            break;

        case 0x16:
            dm_attack_se(gameStateData, arg2);
            dm_warning_h_line(gameStateData, mapGrid);

            var_s0_3 = true;
            // reading i non initialized
            if ((game_state_data[i].unk_04A != 0) && dm_broken_set(gameStateData, mapGrid)) {
                gameStateData->unk_00C = 8;
                var_s0_3 = false;
            }
            if (var_s0_3) {
                dm_set_capsel(gameStateData);
                dm_capsel_speed_up(gameStateData);
                gameStateData->unk_03A = 0;
                gameStateData->unk_039 = 0;
                gameStateData->unk_037 = 0;

                for (i = 0; i < ARRAY_COUNT(gameStateData->unk_03C); i++) {
                    gameStateData->unk_03C[i] = 0;
                }

                gameStateData->unk_00C = 4;
            }
            break;

        default:
            break;
    }

    return 0;
}
#endif

#if VERSION_US
#ifdef NON_MATCHING
// regalloc
void dm_manual_make_key(struct_game_state_data *arg0, GameMapGrid *mapGrid) {
    struct_watchManual *temp_s3 = watchManual;
    struct_game_state_data_unk_178 *temp_s4;
    u16 temp_s2;
    s32 temp_v0;

    aifKeyOut(arg0);

    temp_s2 = joygam[arg0->unk_04B];
    temp_s4 = &arg0->unk_178;

    if (temp_s2 & 0x4000) {
        rotate_capsel(mapGrid, temp_s4, -1);
        temp_s3->unk_01C[3] = 8;
    } else if (temp_s2 & 0x8000) {
        rotate_capsel(mapGrid, temp_s4, 1);
        temp_s3->unk_01C[2] = 8;
    }

    if (temp_s2 & 0x200) {
        translate_capsel(mapGrid, arg0, -1, main_joy[arg0->unk_04B]);
        temp_s3->unk_01C[0] = 8;
    } else if (temp_s2 & 0x100) {
        translate_capsel(mapGrid, arg0, 1, main_joy[arg0->unk_04B]);
        temp_s3->unk_01C[1] = 8;
    }

    arg0->unk_030 = 1;
    if ((temp_s2 & 0x400) && (temp_s4->unk_2 > 0)) {
        temp_v0 = FallSpeed[arg0->unk_02D];
        arg0->unk_030 = (temp_v0 >> 1) + (temp_v0 & 1);
    }
}
#else
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_manual_main", dm_manual_make_key);
#endif
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_manual_main", func_8007B7A8_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_manual_main", func_8007BE38_cn);
#endif

#if VERSION_US
#ifdef NON_MATCHING
bool dm_manual_1_main(void) {
    struct_watchManual *temp_s1 = watchManual;
    struct_game_state_data *gameStateDataP = game_state_data;
    bool var_s6 = true;
    GameMapGrid *mapGrid = game_map_data;
    s32 var_s5;
    u32 temp_s0_4;
    s32 var_s0;

    struct_game_state_data_unk_178 *unk_178 = &gameStateDataP->unk_178;

    // var_s5 = saved_reg_s5;

    for (var_s0 = 0; var_s0 < ARRAY_COUNTU(temp_s1->unk_01C); var_s0++) {
        if (temp_s1->unk_01C[var_s0] != -0x14) {
            temp_s1->unk_01C[var_s0]--;
        }
    }

    if (temp_s1->unk_16C != 0) {
        var_s5 = dm_manual_main_cnt(gameStateDataP, mapGrid, 0, 0);
        dm_manual_make_key(gameStateDataP, mapGrid);
    }

    func_800723EC(gameStateDataP, mapGrid, 0);
    dm_virus_anime(gameStateDataP, mapGrid);
    dm_manual_update_virus_anime(gameStateDataP);
    dm_warning_h_line_se();

    switch (temp_s1->unk_164) {
        case 0x0:
            func_80071EF0(&temp_s1->unk_034, RO_800B2408, RO_800B240C);
            temp_s1->unk_000 = 1;
            temp_s1->unk_004 = RO_800B2428;
            temp_s1->unk_008 = RO_800B242C;
            func_80072204(&temp_s1->unk_034);
            temp_s1->unk_164 += 1;

            for (var_s0 = 0; var_s0 < ARRAY_COUNTU(RO_800B246C); var_s0++) {
                CapsMagazine[var_s0 + 1] = RO_800B246C[var_s0];
            }

            gameStateDataP->unk_032 = 1;
            dm_set_capsel(gameStateDataP);
            break;

        case 0x1:
            set_virus(mapGrid, virus_1_1[gameStateDataP->unk_025][1], virus_1_1[gameStateDataP->unk_025][2],
                      virus_1_1[gameStateDataP->unk_025][0],
                      virus_anime_table[virus_1_1[gameStateDataP->unk_025][0]][gameStateDataP->unk_027]);

            gameStateDataP->unk_025++;
            if (gameStateDataP->unk_025 >= 4U) {
                temp_s1->unk_164 = 0xA;
            }
            break;

        case 0xA:
            func_800721D8(&temp_s1->unk_034);
            func_800721BC(&temp_s1->unk_034, mes_1_1);
            temp_s1->unk_164 = 0x30A;
            temp_s1->unk_168 = 0x14;
            break;

        case 0x14:
            func_800721A0(&temp_s1->unk_034);
            func_800721BC(&temp_s1->unk_034, mes_1_2);
            temp_s1->unk_164 = 0x30A;
            temp_s1->unk_168 = 0x1E;
            break;

        case 0x1E:
            func_800721A0(&temp_s1->unk_034);
            func_800721BC(&temp_s1->unk_034, mes_1_3);
            temp_s1->unk_164 = 0x30A;
            temp_s1->unk_168 = 0x28;
            break;

        case 0x28U:
            func_800721A0(&temp_s1->unk_034);
            func_800721BC(&temp_s1->unk_034, mes_1_4);
            temp_s1->unk_164 = 0x30A;
            temp_s1->unk_168 = 0x29;
            break;

        case 0x29:
            temp_s1->unk_16C = 1;
            gameStateDataP->unk_00C = 4;
            aifMake2(gameStateDataP, 3, 0xC, 0, 0);
            temp_s1->unk_164 += 1;
            break;

        case 0x2A:
            gameStateDataP->unk_030 = 1;

            switch (unk_178->unk_2[0]) {
                case 0x4:
                    if (unk_178->unk_2[0] == unk_178->unk_2[1]) {
                        rotate_capsel(mapGrid, unk_178, -1);
                        temp_s1->unk_01C[3] = 8;
                    }
                    break;

                case 0x6:
                    if (unk_178->unk_2[0] != unk_178->unk_2[1]) {
                        rotate_capsel(mapGrid, unk_178, -1);
                        temp_s1->unk_01C[3] = 8;
                    }
                    break;

                case 0x8:
                    if (unk_178->unk_2[0] == unk_178->unk_2[1]) {
                        rotate_capsel(mapGrid, unk_178, 1);
                        temp_s1->unk_01C[2] = 8;
                    }
                    break;

                case 0xA:
                    if (unk_178->unk_2[0] != unk_178->unk_2[1]) {
                        rotate_capsel(mapGrid, unk_178, 1);
                        temp_s1->unk_01C[2] = 8;
                    }
                    break;

                case 0xC:
                    aifMakeFlagSet(gameStateDataP);
                    aifMake2(gameStateDataP, 4, 0xE, 0, 0);
                    temp_s1->unk_164 += 1;
                    break;
            }
            break;

        case 0x2B:
            if (gameStateDataP->unk_23D == 0) {
                temp_s1->unk_164 = 0x32;
            }
            break;

        case 0x32:
            temp_s1->unk_16C = 0;
            func_800721A0(&temp_s1->unk_034);
            func_800721BC(&temp_s1->unk_034, mes_1_5);
            temp_s1->unk_164 = 0x30A;
            temp_s1->unk_168 = 0x33;
            break;

        case 0x33:
            temp_s1->unk_16C = 1;
            aifMake2(gameStateDataP, 2, 0xC, 1, 0);
            temp_s1->unk_164 += 1;
            break;

        case 0x34:
            if (gameStateDataP->unk_23D == 0) {
                aifMake2(gameStateDataP, 5, 0xD, 1, 0);
                temp_s1->unk_164 += 1;
            }
            break;

        case 0x35:
            if (gameStateDataP->unk_23D == 0) {
                temp_s1->unk_164 = 0x3C;
            }
            break;

        case 0x3C:
            temp_s1->unk_16C = 0;
            func_800721A0(&temp_s1->unk_034);
            func_800721BC(&temp_s1->unk_034, mes_1_6);
            temp_s1->unk_164 = 0x30A;
            temp_s1->unk_168 = 0x3D;
            break;

        case 0x3D:
            temp_s1->unk_16C = 1;
            aifMake2(gameStateDataP, 2, 0x10, 0, 0);
            temp_s1->unk_164 += 1;
            break;

        case 0x3E:
            if (var_s5 == 6) {
                dm_seq_play(SEQ_INDEX_14);
                temp_s1->unk_014 = 0;
                temp_s1->unk_018 = 0x78;
                temp_s1->unk_164 += 1;
            }
            break;

        case 0x3F:
            if (var_s5 == 1) {
                clear_map_all(mapGrid);
                temp_s1->unk_164 += 1;
                gameStateDataP->unk_026 = 0xF;
                _dm_virus_init(0, gameStateDataP, &virus_map_data[0], virus_map_disp_order, var_s5);

                for (var_s0 = 0; var_s0 < 3; var_s0++) {
                    animeState_set(get_virus_anime_state(var_s0), 0);
                    animeSmog_stop(get_virus_smog_state(var_s0));
                }

                for (var_s0 = 0; var_s0 < ARRAY_COUNTU(RO_800B2474); var_s0++) {
                    CapsMagazine[var_s0 + 1] = RO_800B2474[var_s0];
                }

                gameStateDataP->unk_032 = 1;
                dm_set_capsel(gameStateDataP);
                gameStateDataP->unk_00C = 1;
                gameStateDataP->unk_014 = 2;
                gameStateDataP->unk_025 = 0;
            }
            break;

        case 0x40:

        {
            s32 index = virus_map_disp_order->unk_00[gameStateDataP->unk_025];

            set_virus(mapGrid, virus_map_data[0].unk_000[index].unk_1, virus_map_data[0].unk_000[index].unk_2,
                      virus_map_data[0].unk_000[index].unk_0,
                      virus_anime_table[virus_map_data[0].unk_000[index].unk_0][gameStateDataP->unk_027]);
        }

            gameStateDataP->unk_025++;
            if (gameStateDataP->unk_025 >= dm_get_first_virus_count(evs_gamemode, gameStateDataP)) {
                temp_s1->unk_164 = 0x46;
            }
            break;

        case 0x46:
            func_800721A0(&temp_s1->unk_034);
            func_800721BC(&temp_s1->unk_034, mes_1_7);
            temp_s1->unk_164 = 0x30A;
            temp_s1->unk_168 = 0x47;
            break;

        case 0x47:
            temp_s1->unk_16C = 1;
            gameStateDataP->unk_00C = 4;
            aifMakeFlagSet(gameStateDataP);
            temp_s1->unk_164 += 1;
            break;

        case 0x48:
            temp_s0_4 = gameStateDataP->unk_032 - 2;
            if (temp_s0_4 < ARRAY_COUNTU(position_1_1)) {
                aifMake2(gameStateDataP, position_1_1[temp_s0_4][0], position_1_1[temp_s0_4][1],
                         position_1_1[temp_s0_4][2], position_1_1[temp_s0_4][3]);
            } else {
                temp_s1->unk_164 = 0x49;
            }
            break;

        case 0x49:
            if (var_s5 == -1) {
                dm_seq_play(SEQ_INDEX_17);
                temp_s1->unk_164 += 1;
            }
            break;

        case 0x4A:
            if (var_s5 == 0x64) {
                temp_s1->unk_164 = 0x50;
            }
            break;

        case 0x50:
            func_800721A0(&temp_s1->unk_034);
            func_800721BC(&temp_s1->unk_034, mes_1_8);
            temp_s1->unk_164 = 0x30A;
            temp_s1->unk_168 = 0x30C;
            break;

        case 0x30A:
            if (func_80072230(&temp_s1->unk_034)) {
                temp_s1->unk_164 = temp_s1->unk_168;
            }
            break;

        case 0x30C:
            var_s6 = false;
            break;
    }

    return var_s6;
}
#else
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_manual_main", dm_manual_1_main);
#endif
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_manual_main", dm_manual_1_main);
#endif

#if VERSION_US
bool dm_manual_2_main(void) {
    struct_watchManual *watchManualP = watchManual;
    struct_game_state_data *gameStateDataP = game_state_data;
    GameMapGrid *mapGrid = game_map_data;
    bool ret = true;
    s32 i;

    if (watchManualP->unk_16C != 0) {
        dm_manual_main_cnt(gameStateDataP, &mapGrid[0], 0, 1);
        dm_manual_main_cnt(&gameStateDataP[1], &mapGrid[1], 1, 1);
        dm_manual_make_key(gameStateDataP, mapGrid);
    }

    func_800723EC(gameStateDataP, mapGrid, 0);
    dm_manual_attack_capsel_down();

    for (i = 0; i < 2; i++) {
        dm_virus_anime(&gameStateDataP[i], &mapGrid[i]);
    }

    dm_warning_h_line_se();

    switch (watchManualP->unk_164) {
        case 0x0:
            func_80071EF0(&watchManualP->unk_034, RO_800B2410, RO_800B2414);
            watchManualP->unk_000 = 1;
            watchManualP->unk_004 = RO_800B2430;
            watchManualP->unk_008 = RO_800B2434;
            func_80072204(&watchManualP->unk_034);
            watchManualP->unk_164 = 1;

            for (i = 0; i < ARRAY_COUNTU(capsel_2_1); i++) {
                CapsMagazine[i + 1] = capsel_2_1[i];
            }
            gameStateDataP->unk_032 = 1;
            dm_set_capsel(gameStateDataP);
            break;

        case 0x1:
            set_virus(mapGrid, virus_2_1[gameStateDataP->unk_025][1], virus_2_1[gameStateDataP->unk_025][2],
                      virus_2_1[gameStateDataP->unk_025][0],
                      virus_anime_table[virus_2_1[gameStateDataP->unk_025][0]][gameStateDataP->unk_027]);

            gameStateDataP->unk_025++;
            if (gameStateDataP->unk_025 >= 0x14U) {
                watchManualP->unk_164 = 0xA;
            }
            break;

        case 0xA:
            func_800721D8(&watchManualP->unk_034);
            func_800721BC(&watchManualP->unk_034, mes_2_1);
            watchManualP->unk_164 = 0x30A;
            watchManualP->unk_168 = 0x14;
            break;

        case 0x14:
            func_800721A0(&watchManualP->unk_034);
            func_800721BC(&watchManualP->unk_034, mes_2_2);
            watchManualP->unk_164 = 0x30A;
            watchManualP->unk_168 = 0x1E;
            break;

        case 0x1E:
            func_800721A0(&watchManualP->unk_034);
            func_800721BC(&watchManualP->unk_034, mes_2_3);
            watchManualP->unk_164 = 0x30A;
            watchManualP->unk_168 = 0x28;
            break;

        case 0x28:
            func_800721A0(&watchManualP->unk_034);
            func_800721BC(&watchManualP->unk_034, mes_2_4);
            watchManualP->unk_164 = 0x30A;
            watchManualP->unk_168 = 0x32;
            break;

        case 0x32:
            func_800721A0(&watchManualP->unk_034);
            func_800721BC(&watchManualP->unk_034, mes_2_5);
            watchManualP->unk_164 = 0x30A;
            watchManualP->unk_168 = 0x3C;
            break;

        case 0x3C:
            func_800721A0(&watchManualP->unk_034);
            func_800721BC(&watchManualP->unk_034, mes_2_6);
            watchManualP->unk_164 = 0x30A;
            watchManualP->unk_168 = 0x3D;
            break;

        case 0x3D:
            gameStateDataP->unk_00C = 4;
            watchManualP->unk_164 = 0x309;
            watchManualP->unk_168 = 0x46;
            break;

        case 0x46:
            func_800721A0(&watchManualP->unk_034);
            func_800721BC(&watchManualP->unk_034, mes_2_7);
            watchManualP->unk_164 = 0x30A;
            watchManualP->unk_168 = 0x47;
            break;

        case 0x47:
            watchManualP->unk_164 = 0x309;
            watchManualP->unk_168 = 0x50;
            break;

        case 0x50:
            watchManualP->unk_164 = 0x309;
            watchManualP->unk_168 = 0x51;
            break;

        case 0x51:
            func_800721A0(&watchManualP->unk_034);
            func_800721BC(&watchManualP->unk_034, mes_2_8);
            watchManualP->unk_164 = 0x30A;
            watchManualP->unk_168 = 0x5A;
            break;

        case 0x5A:
            func_800721A0(&watchManualP->unk_034);
            func_800721BC(&watchManualP->unk_034, mes_2_9);
            watchManualP->unk_164 = 0x30A;
            watchManualP->unk_168 = 0x30C;
            break;

        case 0x309:
            watchManualP->unk_16C = 1;
            i = gameStateDataP->unk_032 - 2;
            if (i < ARRAY_COUNTU(position_2_1)) {
                aifMake2(gameStateDataP, position_2_1[i][0], position_2_1[i][1], position_2_1[i][2],
                         position_2_1[i][3]);
            }

            switch (watchManualP->unk_030) {
                case 0:
                    if (i == 2) {
                        func_80072268(watchManualP->unk_0E8[1], 2, 2);
                        func_80072268(&watchManualP->unk_0E8[1][1], 6, 0);
                        watchManualP->unk_174[1] = 0;
                        watchManualP->unk_164 = 0x30B;
                        watchManualP->unk_030 += 1;
                    }
                    break;

                case 1:
                    if (i == 5) {
                        func_80072268(watchManualP->unk_0E8[1], 2, 2);
                        func_80072268(&watchManualP->unk_0E8[1][1], 4, 0);

                        func_80072268(&watchManualP->unk_0E8[1][2], 6, 1);
                        watchManualP->unk_174[1] = 0;
                        watchManualP->unk_164 = 0x30B;
                        watchManualP->unk_030 += 1;
                    }
                    break;

                case 2:
                    if (i == 0xA) {
                        func_80072268(watchManualP->unk_0E8[1], 1, 0);
                        func_80072268(&watchManualP->unk_0E8[1][1], 3, 1);
                        func_80072268(&watchManualP->unk_0E8[1][2], 5, 0);
                        func_80072268(&watchManualP->unk_0E8[1][3], 7, 2);
                        watchManualP->unk_174[1] = 0;
                        watchManualP->unk_164 = 0x30B;
                        watchManualP->unk_030 += 1;
                    }
                    break;
            }
            break;

        case 0x30A:
            watchManualP->unk_16C = 0;
            if (func_80072230(&watchManualP->unk_034)) {
                watchManualP->unk_164 = watchManualP->unk_168;
            }
            break;

        case 0x30B:
            watchManualP->unk_16C = 0;
            if (watchManualP->unk_0E8[1][1].unk_3[0] == 0) {
                watchManualP->unk_164 = watchManualP->unk_168;
            }
            break;

        case 0x30C:
            ret = false;
            break;

        default:
            break;
    }

    return ret;
}
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_manual_main", dm_manual_2_main);
#endif

#if VERSION_US
bool dm_manual_3_main(void) {
    struct_game_state_data *gameStateData = game_state_data;
    GameMapGrid *mapGrid = game_map_data;
    struct_watchManual *temp_s2 = watchManual;
    bool ret = true;
    s32 i;

    if (temp_s2->unk_16C != 0) {
        dm_manual_main_cnt(gameStateData, mapGrid, 0, 2);

        for (i = 1; i < 3; i++) {
            dm_manual_main_cnt(&gameStateData[i], &mapGrid[i], i, 2);
        }

        dm_manual_make_key(gameStateData, mapGrid);
    }

    func_800723EC(gameStateData, mapGrid, 0);
    dm_manual_attack_capsel_down();

    for (i = 0; i < 4; i++) {
        dm_virus_anime(&game_state_data[i], &game_map_data[i]);
    }

    dm_warning_h_line_se();

    switch (temp_s2->unk_164) {
        case 0x0:
            func_80071EF0(&temp_s2->unk_034, RO_800B2420, RO_800B2424);
            temp_s2->unk_000 = 1;
            temp_s2->unk_004 = RO_800B2440;
            temp_s2->unk_008 = RO_800B2444;
            func_80072204(&temp_s2->unk_034);
            temp_s2->unk_164 = (u32)1;

            for (i = 0; i < ARRAY_COUNTU(RO_800B2538); i++) {
                CapsMagazine[i + 1] = RO_800B2538[i];
            }

            gameStateData->unk_032 = 1;
            dm_set_capsel(gameStateData);
            break;

        case 0x1:
            set_virus(mapGrid, virus_3_1[gameStateData->unk_025][1], virus_3_1[gameStateData->unk_025][2],
                      virus_3_1[gameStateData->unk_025][0],
                      virus_anime_table[virus_3_1[gameStateData->unk_025][0]][gameStateData->unk_027]);

            gameStateData->unk_025++;
            if (gameStateData->unk_025 >= 0x14U) {
                temp_s2->unk_164 = 0xA;
            }
            break;

        case 0xA:
            func_800721D8(&temp_s2->unk_034);
            func_800721BC(&temp_s2->unk_034, mes_3_1);
            temp_s2->unk_164 = 0x30A;
            temp_s2->unk_168 = 0x14;
            break;

        case 0x14:
            func_800721A0(&temp_s2->unk_034);
            func_800721BC(&temp_s2->unk_034, mes_3_2);
            temp_s2->unk_164 = 0x30A;
            temp_s2->unk_168 = 0x1E;
            break;

        case 0x1E:
            func_800721A0(&temp_s2->unk_034);
            func_800721BC(&temp_s2->unk_034, mes_3_3);
            temp_s2->unk_164 = 0x30A;
            temp_s2->unk_168 = 0x28;
            break;

        case 0x28:
            func_800721A0(&temp_s2->unk_034);
            func_800721BC(&temp_s2->unk_034, mes_3_4);
            temp_s2->unk_164 = 0x30A;
            temp_s2->unk_168 = 0x32;
            break;

        case 0x32:
            func_800721A0(&temp_s2->unk_034);
            func_800721BC(&temp_s2->unk_034, mes_3_5);
            temp_s2->unk_164 = 0x30A;
            temp_s2->unk_168 = 0x3C;
            break;

        case 0x3C:
            func_800721A0(&temp_s2->unk_034);
            func_800721BC(&temp_s2->unk_034, mes_3_6);
            temp_s2->unk_164 = 0x30A;
            temp_s2->unk_168 = 0x3D;
            break;

        case 0x3D:
            gameStateData->unk_00C = 4;
            temp_s2->unk_164 = 0x309;
            temp_s2->unk_168 = 0x46;
            break;

        case 0x46:
            func_800721A0(&temp_s2->unk_034);
            func_800721BC(&temp_s2->unk_034, mes_3_7);
            temp_s2->unk_164 = 0x30A;
            temp_s2->unk_168 = 0x47;
            break;

        case 0x47:
            temp_s2->unk_164 = 0x309;
            temp_s2->unk_168 = 0x50;
            break;

        case 0x50:
            func_800721A0(&temp_s2->unk_034);
            func_800721BC(&temp_s2->unk_034, mes_3_8);
            temp_s2->unk_164 = 0x30A;
            temp_s2->unk_168 = 0x51;
            break;

        case 0x51:
            temp_s2->unk_164 = 0x309;
            temp_s2->unk_168 = 0x5A;
            break;

        case 0x5A:
            func_800721A0(&temp_s2->unk_034);
            func_800721BC(&temp_s2->unk_034, mes_3_9);
            temp_s2->unk_164 = 0x30A;
            temp_s2->unk_168 = 0x5B;
            break;

        case 0x5B:
            temp_s2->unk_164 = 0x309;
            temp_s2->unk_168 = 0x64;
            break;

        case 0x64:
            func_800721A0(&temp_s2->unk_034);
            func_800721BC(&temp_s2->unk_034, mes_3_10);
            temp_s2->unk_164 = 0x30A;
            temp_s2->unk_168 = 0x6E;
            break;

        case 0x6E:
            func_800721A0(&temp_s2->unk_034);
            func_800721BC(&temp_s2->unk_034, mes_3_11);
            temp_s2->unk_164 = 0x30A;
            temp_s2->unk_168 = 0x78;
            break;

        case 0x78:
            func_800721A0(&temp_s2->unk_034);
            func_800721BC(&temp_s2->unk_034, mes_3_12);
            temp_s2->unk_164 = 0x30A;
            temp_s2->unk_168 = 0x82;
            break;

        case 0x82:
            func_800721A0(&temp_s2->unk_034);
            func_800721BC(&temp_s2->unk_034, mes_3_13);
            temp_s2->unk_164 = 0x30A;
            temp_s2->unk_168 = 0x8C;
            break;

        case 0x8C:
            func_800721A0(&temp_s2->unk_034);
            func_800721BC(&temp_s2->unk_034, mes_3_14);
            temp_s2->unk_164 = 0x30A;
            temp_s2->unk_168 = 0x96;
            break;

        case 0x96:
            func_800721A0(&temp_s2->unk_034);
            func_800721BC(&temp_s2->unk_034, mes_3_15);
            temp_s2->unk_164 = 0x30A;
            temp_s2->unk_168 = 0x30C;
            break;

        case 0x309:
            temp_s2->unk_16C = 1;
            i = gameStateData->unk_032 - 2;
            if (i < ARRAY_COUNTU(position_3_1)) {
                aifMake2(gameStateData, position_3_1[i][0], position_3_1[i][1], position_3_1[i][2], position_3_1[i][3]);
            }

            switch (temp_s2->unk_030) {
                case 0x0:
                    if (i == 2) {
                        func_80072268(temp_s2->unk_0E8[1], 2, 2);
                        func_80072268(&temp_s2->unk_0E8[1][1], 6, 1);
                        temp_s2->unk_174[1] = 0;
                        temp_s2->unk_164 = 0x30B;
                        temp_s2->unk_030 += 1;
                    }
                    break;

                case 0x1:
                    if (i == 5) {
                        func_80072268(temp_s2->unk_0E8[2], 2, 0);
                        func_80072268(&temp_s2->unk_0E8[2][1], 6, 1);
                        temp_s2->unk_174[2] = 0;

                        temp_s2->unk_164 = 0x30B;
                        temp_s2->unk_030 += 1;
                        temp_s2->unk_034.unk_0C = -temp_s2->unk_034.unk_0C;
                    }
                    break;

                case 0x2:
                    if (i == 8) {
                        func_80072268(temp_s2->unk_0E8[3], 2, 0);
                        func_80072268(&temp_s2->unk_0E8[3][1], 6, 2);
                        temp_s2->unk_174[3] = 0;
                        temp_s2->unk_164 = 0x30B;
                        temp_s2->unk_030 += 1;
                        temp_s2->unk_034.unk_0C = -temp_s2->unk_034.unk_0C;
                    }
                    break;

                case 0x3:
                    if (i == 0xA) {
                        func_80072268(temp_s2->unk_0E8[2], 2, 0);
                        func_80072268(&temp_s2->unk_0E8[2][1], 6, 1);
                        temp_s2->unk_174[2] = 0;
                        func_80072268(temp_s2->unk_0E8[3], 2, 0);
                        func_80072268(&temp_s2->unk_0E8[3][1], 6, 1);
                        temp_s2->unk_174[3] = 0;
                        temp_s2->unk_164 = 0x30B;
                        temp_s2->unk_030 += 1;
                        temp_s2->unk_034.unk_0C = -temp_s2->unk_034.unk_0C;
                    }
                    break;

                default:
                    break;
            }
            break;

        case 0x30A:
            temp_s2->unk_16C = 0;
            if (func_80072230(&temp_s2->unk_034)) {
                temp_s2->unk_164 = temp_s2->unk_168;
            }
            break;

        case 0x30B:
            temp_s2->unk_16C = 0;
            if ((temp_s2->unk_0E8[1][1].unk_3[0] == 0) && (temp_s2->unk_0E8[2][1].unk_3[0] == 0) &&
                (temp_s2->unk_0E8[3][1].unk_3[0] == 0)) {
                if (temp_s2->unk_000 < 0) {
                    if (temp_s2->unk_034.unk_0C > 0.0f) {
                        temp_s2->unk_034.unk_0C = -temp_s2->unk_034.unk_0C;
                    } else if (temp_s2->unk_034.unk_08 == 0.0f) {
                        func_80071EF0(&temp_s2->unk_034, RO_800B2420, RO_800B2424);
                        temp_s2->unk_034.unk_0C = -temp_s2->unk_034.unk_0C;
                        temp_s2->unk_000 = -temp_s2->unk_000;
                        temp_s2->unk_004 = RO_800B2440;
                        temp_s2->unk_008 = RO_800B2444;
                    }
                } else {
                    temp_s2->unk_164 = temp_s2->unk_168;
                }
            } else {
                if ((temp_s2->unk_034.unk_0C < 0.0f) && (temp_s2->unk_034.unk_08 == 0.0f)) {
                    func_80071EF0(&temp_s2->unk_034, RO_800B2418, RO_800B241C);
                    temp_s2->unk_034.unk_0C = -temp_s2->unk_034.unk_0C;
                    temp_s2->unk_000 = -temp_s2->unk_000;
                    temp_s2->unk_004 = RO_800B2438;
                    temp_s2->unk_008 = RO_800B243C;
                }
            }
            break;

        case 0x30C:
            ret = false;
            break;

        default:
            break;
    }

    return ret;
}
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_manual_main", dm_manual_3_main);
#endif

#if VERSION_US
bool dm_manual_4_main(void) {
    struct_watchManual *temp_s2 = watchManual;
    bool ret = true;
    struct_game_state_data *gameStateData = game_state_data;
    GameMapGrid *mapGrid = game_map_data;
    bool var_v0_2;
    s32 i;

    for (i = 0; i < ARRAY_COUNTU(temp_s2->unk_01C); i++) {
        if (temp_s2->unk_01C[i] != -0x14) {
            temp_s2->unk_01C[i]--;
        }
    }

    if (temp_s2->unk_16C != 0) {
        dm_manual_main_cnt(gameStateData, mapGrid, 0, 0);
        dm_manual_make_key(gameStateData, mapGrid);
    }
    func_800723EC(gameStateData, mapGrid, 0);
    dm_virus_anime(gameStateData, mapGrid);
    dm_manual_update_virus_anime(gameStateData);
    dm_warning_h_line_se();

    switch (temp_s2->unk_164) {
        case 0x0:
            func_80071EF0(&temp_s2->unk_034, RO_800B2408, RO_800B240C);
            temp_s2->unk_000 = 1;
            temp_s2->unk_004 = RO_800B2428;
            temp_s2->unk_008 = RO_800B242C;
            func_80072204(&temp_s2->unk_034);
            temp_s2->unk_164 = 1;

            for (i = 0; i < ARRAY_COUNTU(RO_800B259C); i++) {
                CapsMagazine[i + 1] = RO_800B259C[i];
            }

            gameStateData->unk_032 = 1;
            dm_set_capsel(gameStateData);
            break;

        case 0x1:
            set_virus(mapGrid, virus_4_1[gameStateData->unk_025][1], virus_4_1[gameStateData->unk_025][2],
                      virus_4_1[gameStateData->unk_025][0],
                      virus_anime_table[virus_4_1[gameStateData->unk_025][0]][gameStateData->unk_027]);
            gameStateData->unk_025++;
            if (gameStateData->unk_025 >= 0x10U) {
                temp_s2->unk_164 = 0xA;
            }
            break;

        case 0xA:
            func_800721D8(&temp_s2->unk_034);
            func_800721BC(&temp_s2->unk_034, mes_4_1);
            temp_s2->unk_164 = 0x30A;
            temp_s2->unk_168 = 0x14;
            break;

        case 0x14:
            func_800721A0(&temp_s2->unk_034);
            func_800721BC(&temp_s2->unk_034, mes_4_2);
            temp_s2->unk_164 = 0x30A;
            temp_s2->unk_168 = 0x15;
            break;

        case 0x15:
            gameStateData->unk_00C = 4;
            temp_s2->unk_164 = 0x309;
            temp_s2->unk_168 = 0x1E;
            break;

        case 0x1E:
            func_800721A0(&temp_s2->unk_034);
            func_800721BC(&temp_s2->unk_034, mes_4_3);
            temp_s2->unk_164 = 0x30A;
            temp_s2->unk_168 = 0x28;
            break;

        case 0x28:
            func_800721A0(&temp_s2->unk_034);
            func_800721BC(&temp_s2->unk_034, mes_4_4);
            temp_s2->unk_164 = 0x30A;
            temp_s2->unk_168 = 0x29;
            break;

        case 0x29:
            temp_s2->unk_164 = 0x309;
            temp_s2->unk_168 = 0x32;
            break;

        case 0x32:
            func_800721A0(&temp_s2->unk_034);
            func_800721BC(&temp_s2->unk_034, mes_4_5);
            temp_s2->unk_164 = 0x30A;
            temp_s2->unk_168 = 0x33;
            break;

        case 0x33:
            temp_s2->unk_164 = 0x309;
            temp_s2->unk_168 = 0x3C;
            break;

        case 0x3C:
            func_800721A0(&temp_s2->unk_034);
            func_800721BC(&temp_s2->unk_034, mes_4_6);
            temp_s2->unk_164 = 0x30A;
            temp_s2->unk_168 = 0x3D;
            break;

        case 0x3D:
            temp_s2->unk_164 = 0x309;
            temp_s2->unk_168 = 0x46;
            break;

        case 0x46:
            func_800721A0(&temp_s2->unk_034);
            func_800721BC(&temp_s2->unk_034, mes_4_7);
            temp_s2->unk_164 = 0x30A;
            temp_s2->unk_168 = 0x47;
            break;

        case 0x47:
            temp_s2->unk_164 = 0x309;
            temp_s2->unk_168 = 0x50;
            break;

        case 0x50:
            func_800721A0(&temp_s2->unk_034);
            func_800721BC(&temp_s2->unk_034, mes_4_8);
            temp_s2->unk_164 = 0x30A;
            temp_s2->unk_168 = 0x51;
            break;

        case 0x51:
            temp_s2->unk_164 = 0x309;
            temp_s2->unk_168 = 0x5A;
            break;

        case 0x5A:
            func_800721A0(&temp_s2->unk_034);
            func_800721BC(&temp_s2->unk_034, mes_4_9);
            temp_s2->unk_164 = 0x30A;
            temp_s2->unk_168 = 0x64;
            break;

        case 0x64:
            func_800721A0(&temp_s2->unk_034);
            func_800721BC(&temp_s2->unk_034, mes_4_10);
            temp_s2->unk_164 = 0x30A;
            temp_s2->unk_168 = 0x30C;
            break;

        case 0x309:
            temp_s2->unk_16C = 1;
            i = gameStateData->unk_032 - 2;
            if (i < ARRAY_COUNTU(position_4_1)) {
                aifMake2(gameStateData, position_4_1[i][0], position_4_1[i][1], position_4_1[i][2], position_4_1[i][3]);
            }

            switch (temp_s2->unk_030) {
                case 0x0:
                    var_v0_2 = i == 3;
                    break;
                case 0x1:
                    var_v0_2 = i == 5;
                    break;
                case 0x2:
                    var_v0_2 = i == 0xA;
                    break;
                case 0x3:
                    var_v0_2 = i == 0xC;
                    break;
                case 0x4:
                    var_v0_2 = i == 0xF;
                    break;
                case 0x5:
                    var_v0_2 = i == 0x10;
                    break;
                default:
                    var_v0_2 = false;
                    break;
            }

            if (var_v0_2) {
                temp_s2->unk_164 = temp_s2->unk_168;
                temp_s2->unk_030++;
            }
            break;

        case 0x30A:
            temp_s2->unk_16C = 0;
            if (func_80072230(&temp_s2->unk_034)) {
                temp_s2->unk_164 = temp_s2->unk_168;
            }
            break;

        case 0x30C:
            ret = false;
            break;

        default:
            break;
    }

    return ret;
}
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_manual_main", dm_manual_4_main);
#endif

#if VERSION_US || VERSION_CN
ASM_RODATA;

const s32 _tex_884[][2] = {
    { 0, 2 },
    { 1, 3 },
};

const s32 _pos_885[][2] = {
    { 0, 0 },
    { 0, 0xC },
};
#endif

#if VERSION_US || VERSION_CN
void draw_AB_guide(s32 arg0, s32 arg1) {
    s32 i;

    gSPDisplayList(gGfxHead++, alpha_texture_init_dl);
    gDPSetCombineLERP(gGfxHead++, TEXEL0, 0, PRIMITIVE, 0, TEXEL1, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0,
                      COMBINED);
    gDPSetPrimColor(gGfxHead++, 0, 0, 255, 255, 255, 255);

    for (i = 0; i < 2U; i++) {
        TiTexDataEntry *temp_a3 = &_texAll->unk_00[_tex_884[i][0]];
        TiTexDataEntry *temp_a0 = &_texAll->unk_00[_tex_884[i][1]];
        s32 var_t0;

        var_t0 = MIN(temp_a3->unk_4[0], temp_a0->unk_4[0]);

        StretchAlphaTexTile(&gGfxHead, var_t0, temp_a3->unk_4[1], temp_a3->unk_0->unk_4, temp_a3->unk_4[0],
                            temp_a0->unk_0->unk_4, temp_a0->unk_4[0], 0, 0, var_t0, temp_a3->unk_4[1],
                            arg0 + _pos_885[i][0], arg1 + _pos_885[i][1], var_t0, temp_a3->unk_4[1]);
    }
}
#endif

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/dm_manual_main", RO_800B3150);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_manual_main", func_80074B08);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/dm_manual_main", RO_800C9408_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_manual_main", func_8007E774_cn);
#endif

typedef struct struct__posContPanel {
    /* 0x0 */ s32 unk_0;
    /* 0x4 */ s32 unk_4;
} struct__posContPanel;

extern const struct__posContPanel _posContPanel;
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/dm_manual_main", _posContPanel);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/dm_manual_main", _posContPanel);
#endif

extern const s32 _posCircle_924[][2];
extern const s32 _posFinger_925[][2];
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/dm_manual_main", _posCircle_924);
#endif
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/dm_manual_main", _posFinger_925);
#endif

#if VERSION_US || VERSION_CN
ASM_TEXT;

void func_80074EF0(struct_game_state_data *gameStateData, struct_800F4890_unk_0E8 *arg1, s32 arg2) {
    s32 i;

    for (i = 0; i < 3; i++) {
        s32 j;

        load_TexPal((*dm_game_get_capsel_pal(arg2, i))->unk_0);

        for (j = 0; j < 4; j++) {
            if ((arg1[j].unk_3[0] != 0) && (arg1[j].unk_2 == i)) {
                draw_Tex(gameStateData->unk_006 + (arg1[j].unk_0 * gameStateData->unk_00A),
                         gameStateData->unk_008 + (arg1[j].unk_1 * gameStateData->unk_00A), gameStateData->unk_00A,
                         gameStateData->unk_00A, 0, gameStateData->unk_00A * 4);
            }
        }
    }
}
#endif

#if VERSION_US
#ifdef NON_EQUIVALENT
#define ABS(x) (((x) < 0) ? -(x) : (x))

// disaster
void disp_cont(void) {
    s32 temp_s1;
    s32 temp_s2;
    s32 var_v0;
    s32 var_v1;
    struct_watchManual *temp_s3 = watchManual;
    s32 var_a1;
    s32 var_s4;
    s32 temp_a0;
    TiTexData *new_var;
    TiTexDataEntry *new_var2;
    // Gfx **gfxP = &gGfxHead;
    s32 *new_var3;

    for (var_s4 = 0; var_s4 < 4U; var_s4++) {

        if (temp_s3->unk_01C[var_s4] != -0x14) {
            s32 temp_arg4;
            s32 temp_arg5;
            s32 temp;
            s32 *_posFinger_ptr;
            TiTexDataEntry *temp_4;
            TiTexDataEntry *temp_5;

            // temp_s1 = _posContPanel[0];
            // temp_s2 = _posContPanel[1];

            gSPDisplayList(gGfxHead++, normal_texture_init_dl);
            gDPSetCombineLERP(gGfxHead++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, PRIMITIVE, TEXEL0, 0,
                              PRIMITIVE, 0);
            gDPSetRenderMode(gGfxHead++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
            gDPSetPrimColor(gGfxHead++, 0, 0, 255, 0, 0, 255);
            gDPSetTextureLUT(gGfxHead++, G_TT_NONE);

            new_var3 = _posCircle_924[var_s4];
            temp_arg4 = _posContPanel.unk_0 + new_var3[0];
            temp_arg5 = _posContPanel.unk_4 + new_var3[1];
            // temp_arg4 = _posContPanel.unk_0 + _posCircle_924[var_s4][0];
            // temp_arg5 = _posContPanel.unk_4 + _posCircle_924[var_s4][1];

            StretchTexBlock4i(&gGfxHead, _texAll->unk_00[6].unk_4[0], _texAll->unk_00[6].unk_4[1],
                              _texAll->unk_00[6].unk_0->unk_4, temp_arg4, temp_arg5, _texAll->unk_00[6].unk_4[0],
                              _texAll->unk_00[6].unk_4[1]);

            gSPDisplayList(gGfxHead++, alpha_texture_init_dl);

            new_var2 = _texAll->unk_00;

            temp_4 = &new_var2[4];
            temp_5 = &new_var2[5];

            // var_v1 = temp_s3->unk_01C[var_s4];
            // if (var_v1 < 0) {
            //    var_v1 = -var_v1;
            //}
            // var_v1 = (temp_s3->unk_01C[var_s4] < 0) ? -temp_s3->unk_01C[var_s4] : temp_s3->unk_01C[var_s4];
            var_v1 = ABS(temp_s3->unk_01C[var_s4]);

            _posFinger_ptr = _posFinger_925[var_s4];

            // var_a1 = _texAll->unk_00[5].unk_4[0];
            // if (_texAll->unk_00[4].unk_4[0] < var_a1) {
            //    var_a1 = _texAll->unk_00[4].unk_4[0];
            //}
            var_a1 = MIN(temp_4->unk_4[0], temp_5->unk_4[0]);
            // var_a1 = (new_var2[4].unk_4[0] < new_var2[5].unk_4[0]) ? (new_var2[4].unk_4[0]) : (new_var2[5].unk_4[0]);

            // temp_a0 = _posContPanel[1] + _posFinger_925[var_s4][1];
            // var_v0 = temp_a0 - var_v1;
            // if (var_v1 > 4) {
            //    var_v0 = temp_a0 - 4;
            //}
            // var_v0 = temp_a0 - MAX(var_v1, 4);
            // var_v0 = (_posContPanel.unk_4 + _posFinger_925[var_s4][1]) - MAX(var_v1, 4);

            StretchAlphaTexBlock(&gGfxHead, var_a1, temp_4->unk_4[1], temp_4->unk_0->unk_4, var_v1,
                                 temp_5->unk_0->unk_4, temp_5->unk_4[0], (_posContPanel.unk_0 + _posFinger_ptr[0]),
                                 (_posContPanel.unk_4 + _posFinger_ptr[1]) - MAX(var_v1, 4), var_a1, temp_4->unk_4[1]);
        }
    }
}

#else
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_manual_main", disp_cont);
#endif
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_manual_main", disp_cont);
#endif

#if VERSION_US || VERSION_CN
void dm_manual_draw_fg(Mtx **mtxP, Vtx **vtxP) {
    struct_watchManual *temp_s4 = watchManual;
    s32 i;
    TiTexDataEntry *temp;

    switch (evs_manual_no) {
        case EVS_MANUAL_NO_0:
        case EVS_MANUAL_NO_3:
            gSPDisplayList(gGfxHead++, normal_texture_init_dl);

            temp = &_texAll->unk_00[7];
            tiStretchTexBlock(&gGfxHead, temp, 0, _posContPanel.unk_0, _posContPanel.unk_4, temp->unk_4[0],
                              temp->unk_4[1]);
            dm_draw_big_virus(&gGfxHead);
            break;

        default:
            break;
    }

    switch (evs_manual_no) {
        case EVS_MANUAL_NO_1:
            dm_calc_bottle_2p();
            dm_draw_bottle_2p(&gGfxHead);

            for (i = 0; i < 2; i++) {
                dm_game_graphic_p(&game_state_data[i], i, &game_map_data[i]);
                func_80074EF0(&game_state_data[i], temp_s4->unk_0E8[i], 0);
            }
            break;

        case EVS_MANUAL_NO_2:
            for (i = 0; i < 4; i++) {
                dm_game_graphic_p(&game_state_data[i], i, &game_map_data[i]);
                func_80074EF0(&game_state_data[i], temp_s4->unk_0E8[i], 1);
            }
            break;

        case EVS_MANUAL_NO_0:
        case EVS_MANUAL_NO_3:
            dm_game_graphic_p(game_state_data, 0, game_map_data);
            disp_cont();
            break;
    }

    dm_draw_KaSaMaRu(&gGfxHead, mtxP, vtxP, func_8007224C(&temp_s4->unk_034), temp_s4->unk_004, temp_s4->unk_008,
                     temp_s4->unk_000, (s32)(temp_s4->unk_034.unk_08 * 255));
    switch (evs_manual_no) {
        case EVS_MANUAL_NO_0:
        case EVS_MANUAL_NO_3:
            if (main_old == MAIN_NO_3) {
                push_any_key_draw(0xDC, 0xD2);
            } else {
                draw_AB_guide(0xC8, 0xCA);
            }
            break;

        case EVS_MANUAL_NO_1:
            if (main_old == MAIN_NO_3) {
                push_any_key_draw(0x80, 0xD2);
            } else {
                draw_AB_guide(0x6E, 0xCA);
            }
            break;

        case EVS_MANUAL_NO_2:
            if (main_old == MAIN_NO_3) {
                push_any_key_draw(0xE6, 0xD2);
            } else {
                draw_AB_guide(0x6E, 0xCA);
            }
            break;
    }

    tutolWnd_draw(&temp_s4->unk_034, &gGfxHead);
}
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/dm_manual_main", RO_800C9430_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/dm_manual_main", RO_800C9450_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/dm_manual_main", RO_800C9470_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/dm_manual_main", _seqTbl_1037);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/dm_manual_main", RO_800C948C_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/dm_manual_main", RO_800C9490_cn);
#endif

#if VERSION_US
const u16 map_x_table_1036[][4] = {
    { 0x76, 0x76, 0x76, 0x76 },
    { 0x1C, 0xD4, 0x1C, 0xD4 },
    { 0x14, 0x5C, 0xA4, 0xEC },
};
const u8 _seqTbl_1037[] = { 2, 3 };
const u8 map_y_table_1038[] = { 0x2E, 0x2E };
const u8 size_table_1039[] = { 0xA, 8 };

void dm_manual_all_init(void) {
    struct_watchManual *temp_v0_2;
    s32 j;
    s32 i;
    s32 k;
    struct_game_state_data *var_a0_2;
    void **headTopPtr;

    evs_seqnumb = _seqTbl_1037[evs_manual_no % ARRAY_COUNTU(_seqTbl_1037)];
    evs_seqence = 1;

    switch (evs_manual_no) {
        case EVS_MANUAL_NO_0:
        case EVS_MANUAL_NO_3:
            evs_gamesel = ENUM_EVS_GAMESEL_0;
            evs_playcnt = 1;
            break;

        case EVS_MANUAL_NO_1:
        case EVS_MANUAL_NO_4:
            evs_gamesel = ENUM_EVS_GAMESEL_1;
            evs_playcnt = 2;
            break;

        case EVS_MANUAL_NO_2:
        case EVS_MANUAL_NO_5:
            evs_gamesel = ENUM_EVS_GAMESEL_2;
            evs_playcnt = 4;
            break;
    }

    evs_gamemode = ENUM_EVS_GAMEMODE_0;
    story_proc_no = STORY_PROC_NO_1;

    dm_game_init_heap();
    headTopPtr = dm_game_heap_top();
    watchManual = ALIGN_PTR(*headTopPtr);

    temp_v0_2 = watchManual;
    bzero(temp_v0_2, sizeof(struct_watchManual));

    *headTopPtr = &watchManual[1];

    _texAll = tiLoadTexData(headTopPtr, _romDataTbl[ROMDATATBL_TUTORIAL_KASA].start,
                            _romDataTbl[ROMDATATBL_TUTORIAL_KASA].end);
    _texKaSa =
        tiLoadTexData(headTopPtr, _romDataTbl[ROMDATATBL_MENU_KASA].start, _romDataTbl[ROMDATATBL_MENU_KASA].end);

    func_80071F14(&temp_v0_2->unk_034, headTopPtr);
    func_800721D8(&temp_v0_2->unk_034);

    dm_game_init_static();
    dm_game_init_snap_bg();
    dm_game_init(false);
    temp_v0_2->unk_00C = 0xFF;
    temp_v0_2->unk_010 = -8;
    temp_v0_2->unk_170 = 0;

    for (i = 0; i < ARRAY_COUNTU(temp_v0_2->unk_01C); i++) {
        temp_v0_2->unk_01C[i] = -0x14;
    }

    temp_v0_2->unk_02C = 0;
    temp_v0_2->unk_014 = 0;
    temp_v0_2->unk_018 = 0;
    temp_v0_2->unk_184 = 0;

    j = 0;
    for (i = 0; i < 3; i++) {
        temp_v0_2->unk_14C[i].unk_0 = 0;
        temp_v0_2->unk_14C[i].unk_4 = 0;
        temp_v0_2->unk_0C4[i].unk_8 = j;
        temp_v0_2->unk_0C4[i].unk_0 = (sinf(temp_v0_2->unk_0C4[i].unk_8 * 3.141592654 / 180) * 20) + 45;
        temp_v0_2->unk_0C4[i].unk_4 = (cosf(temp_v0_2->unk_0C4[i].unk_8 * 3.141592654 / 180) * -20) + 155;

        j += 120;
    }

    switch (evs_manual_no) {
        case EVS_MANUAL_NO_0:
        case EVS_MANUAL_NO_3:
            k = 0;
            j = 0;
            break;

        case EVS_MANUAL_NO_1:
        case EVS_MANUAL_NO_4:
            k = 0;
            j = 1;
            break;

        case EVS_MANUAL_NO_2:
        case EVS_MANUAL_NO_5:
            k = 1;
            j = 2;
            break;
    }

    var_a0_2 = game_state_data;
    for (i = 0; i < ARRAY_COUNT(game_state_data); i++) {
        var_a0_2[i].unk_008 = map_y_table_1038[k];
        var_a0_2[i].unk_00A = size_table_1039[k];
        var_a0_2[i].unk_006 = map_x_table_1036[j][i];
    }

    var_a0_2 = game_state_data;
    for (i = 0; i < ARRAY_COUNT(game_state_data); i++) {
        s8 *gamespeed_ptr = GameSpeed;
        struct_800F4890_unk_0E8 *temp;

        var_a0_2[i].unk_02C = 1;
        var_a0_2[i].unk_02D = gamespeed_ptr[1];
        var_a0_2[i].unk_04D = 0;
        var_a0_2[i].unk_04E = 2;

        switch (evs_manual_no) {
            case EVS_MANUAL_NO_2:
            case EVS_MANUAL_NO_5:
                var_a0_2[i].unk_02B = 0xC;
                var_a0_2[i].unk_02A = 0;
                break;

            default:
                var_a0_2[i].unk_02B = 8;
                var_a0_2[i].unk_02A = 2;
                break;
        }

        temp_v0_2->unk_174[i] = 0;

        temp = temp_v0_2->unk_0E8[i];
        for (j = 0; j < ARRAY_COUNTU(temp_v0_2->unk_0E8[i]); j++) {
            struct_800F4890_unk_0E8 *temp2 = &temp[j];

            temp2->unk_0 = 0;
            temp2->unk_1 = 0;
            temp2->unk_2 = 0;

            for (k = 0; k < ARRAY_COUNTU(temp2->unk_3); k++) {
                temp2->unk_3[k] = 0;
            }
        }
    }

    temp_v0_2->unk_164 = 0;
    temp_v0_2->unk_168 = 0;
    temp_v0_2->unk_16C = 0;
    temp_v0_2->unk_030 = 0;
}
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_manual_main", dm_manual_all_init);
#endif

#if VERSION_US
#ifdef NON_MATCHING
/**
 * Original name: dm_manual_main
 */
enum_main_no dm_manual_main(struct_800EB670 *arg0) {
    OSMesgQueue sp10;
    OSMesg sp28[8];
    struct_800FAF98_unk_64 sp48;
    enum_main_no var_v0;
    s32 i;
    bool var_s3 = true;
    bool var_s4 = false;
    struct_watchManual *temp_s2;

    osCreateMesgQueue(&sp10, sp28, ARRAY_COUNT(sp28));
    func_8002A184(arg0, &sp48, &sp10);
    dm_manual_all_init();

    temp_s2 = watchManual;
    for (i = 0; i < ARRAY_COUNT(game_state_data); i++) {
        aifMakeFlagSet(&game_state_data[i]);
    }

    while (!var_s4) {
        joyProcCore();
        osRecvMesg(&sp10, NULL, OS_MESG_BLOCK);
        func_80071FA0(&temp_s2->unk_034);
        dm_effect_make();

        temp_s2->unk_184++;
        if (temp_s2->unk_010 > 0) {
            var_s4 = temp_s2->unk_00C == 0xFF;
        }

        temp_s2->unk_00C = CLAMP(temp_s2->unk_00C + temp_s2->unk_010, 0, 0xFF);
        switch (evs_manual_no) {
            case EVS_MANUAL_NO_0:
                var_s3 = dm_manual_1_main();
                break;

            case EVS_MANUAL_NO_1:
                var_s3 = dm_manual_2_main();
                break;

            case EVS_MANUAL_NO_2:
                var_s3 = dm_manual_3_main();
                break;

            case EVS_MANUAL_NO_3:
                var_s3 = dm_manual_4_main();
                break;
        }
        dm_seq_set_volume(0x60);
        dm_audio_update();
        if (temp_s2->unk_018 != 0) {
            temp_s2->unk_014++;
            if (temp_s2->unk_014 >= temp_s2->unk_018) {
                temp_s2->unk_014 = 0;
                temp_s2->unk_018 = 0;
                dm_seq_play_in_game(evs_seqnumb * 2);
            }
        }

        if (temp_s2->unk_00C == 0) {
            s32 buttonMask = (main_old == MAIN_NO_3) ? ANY_BUTTON : B_BUTTON;

            if (var_s3 && (gControllerPressedButtons[main_joy[0]] & buttonMask)) {
                var_s3 = true;
            } else {
                var_s3 = false;
            }
        }

        if (!var_s3) {
            if (temp_s2->unk_010 < 0) {
                temp_s2->unk_010 = -temp_s2->unk_010;
            }
        }

        graphic_no = GRAPHIC_NO_3;
    }

    dm_audio_stop();
    graphic_no = GRAPHIC_NO_0;

    while (!dm_audio_is_stopped() || (pendingGFX != 0)) {
        osRecvMesg(&sp10, NULL, OS_MESG_BLOCK);
        dm_audio_update();
    }

    func_8002A1DC(arg0, &sp48);

    var_v0 = MAIN_NO_3;
    if (main_old != MAIN_NO_3) {
        var_v0 = MAIN_NO_6;
    }
    return var_v0;
}
#else
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_manual_main", dm_manual_main);
#endif
#endif

#if VERSION_CN
enum_main_no dm_manual_main(struct_800EB670 *arg0) {
    OSMesgQueue sp18;
    OSMesg sp30[8];
    struct_800FAF98_unk_64 sp50;
    s32 temp_v1_2;
    s32 var_a0;
    s32 i;
    bool var_s3;
    bool var_s4;
    struct_watchManual *temp_s2;

    var_s3 = true;
    var_s4 = false;

    osCreateMesgQueue(&sp18, sp30, ARRAY_COUNT(sp30));
    func_8002A184(arg0, &sp50, &sp18);
    dm_manual_all_init();

    temp_s2 = watchManual;

    for (i = 0; i < ARRAY_COUNT(game_state_data); i++) {
        aifMakeFlagSet(&game_state_data[i]);
    }

    while (!var_s4) {
        joyProcCore();
        osRecvMesg(&sp18, NULL, OS_MESG_BLOCK);

        if (D_80092F10_cn) {
            graphic_no = GRAPHIC_NO_0;
            dm_audio_update();
        } else {
            func_80071FA0(&temp_s2->unk_034);
            dm_effect_make();

            var_s4 = false;
            temp_s2->unk_184++;

            if (temp_s2->unk_010 > 0) {
                var_s4 = temp_s2->unk_00C == 0xFF;
            }

            temp_v1_2 = temp_s2->unk_00C + temp_s2->unk_010;
            temp_v1_2 = CLAMP(temp_v1_2, 0, 255);
            temp_s2->unk_00C = temp_v1_2;

            switch (evs_manual_no) {
                case EVS_MANUAL_NO_0:
                    var_s3 = dm_manual_1_main();
                    break;

                case EVS_MANUAL_NO_1:
                    var_s3 = dm_manual_2_main();
                    break;

                case EVS_MANUAL_NO_2:
                    var_s3 = dm_manual_3_main();
                    break;

                case EVS_MANUAL_NO_3:
                    var_s3 = dm_manual_4_main();
                    break;
            }

            dm_seq_set_volume(0x60);
            dm_audio_update();

            if (temp_s2->unk_018 != 0) {
                temp_s2->unk_014++;
                if (temp_s2->unk_014 >= temp_s2->unk_018) {
                    temp_s2->unk_014 = 0;
                    temp_s2->unk_018 = 0;
                    dm_seq_play_in_game(evs_seqnumb * 2);
                }
            }
            if (temp_s2->unk_00C == 0) {
                var_a0 = B_BUTTON;
                if (main_old == MAIN_NO_3) {
                    var_a0 = ANY_BUTTON;
                }
                if (gControllerPressedButtons[main_joy[0]] & var_a0) {
                    var_s3 = false;
                }
            }

            if (!var_s3) {
                if (temp_s2->unk_010 < 0) {
                    temp_s2->unk_010 = -temp_s2->unk_010;
                }
            }

            graphic_no = GRAPHIC_NO_3;
        }
    }

    dm_audio_stop();
    graphic_no = GRAPHIC_NO_0;

    while (!dm_audio_is_stopped() || (pendingGFX != 0)) {
        osRecvMesg(&sp18, NULL, OS_MESG_BLOCK);
        dm_audio_update();
    }

    func_8002A1DC(arg0, &sp50);

    if (main_old != MAIN_NO_3) {
        return MAIN_NO_6;
    }

    return MAIN_NO_3;
}
#endif

#if VERSION_US || VERSION_CN
void dm_manual_graphic(void) {
    Mtx *mtx;
    Vtx *vtx;
    OSScTask *ptr;
    s32 color;
    s32 alpha;
    struct_watchManual *temp_s1 = watchManual;

    gGfxHead = gGfxGlist[gfx_gtask_no];
    ptr = &B_800FAE80[gfx_gtask_no];

    mtx = dm_get_mtx_buf();
    vtx = dm_get_vtx_buf();

    gSPSegment(gGfxHead++, 0x00, NULL);
    F3RCPinitRtn();
    F3ClearFZRtn(false);

    gDPSetScissor(gGfxHead++, G_SC_NON_INTERLACE, 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1);

    dm_game_draw_snap_bg(&gGfxHead, &mtx, &vtx, 0);
    dm_manual_draw_fg(&mtx, &vtx);

    color = 255;
    alpha = CLAMP((temp_s1->unk_00C - 127) * 1.2 + 127, 0, 255);
    if (alpha > 0) {
        FillRectRGBA(&gGfxHead, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, color, color, color, alpha);
    }

    gDPFullSync(gGfxHead++);
    gSPEndDisplayList(gGfxHead++);

    osWritebackDCacheAll();
    gfxTaskStart(ptr, gGfxGlist[gfx_gtask_no], (gGfxHead - gGfxGlist[gfx_gtask_no]) * sizeof(Gfx), 0, OS_SC_SWAPBUFFER);
}
#endif

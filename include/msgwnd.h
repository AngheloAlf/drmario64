#ifndef MSGWND_H
#define MSGWND_H

#include "libultra.h"
#include "libc/stdint.h"
#include "libc/stdbool.h"
#include "unk.h"


typedef struct MessageWnd {
    /* 0x00 */ void *unk_00;
    /* 0x04 */ void *unk_04;
    /* 0x08 */ UNK_TYPE unk_08;
    /* 0x0C */ char *unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ UNK_TYPE unk_14;
    /* 0x18 */ UNK_TYPE unk_18;
    /* 0x1C */ UNK_TYPE unk_1C;
    /* 0x20 */ s32 unk_20;
    /* 0x24 */ s32 unk_24;
    /* 0x28 */ UNK_TYPE unk_28;
    /* 0x2C */ UNK_TYPE unk_2C;
    /* 0x30 */ UNK_TYPE unk_30;
    /* 0x34 */ UNK_TYPE unk_34;
    /* 0x38 */ UNK_TYPE unk_38;
    /* 0x3C */ UNK_TYPE unk_3C;
    /* 0x40 */ UNK_TYPE unk_40;
    /* 0x44 */ UNK_TYPE unk_44;
    /* 0x48 */ UNK_TYPE unk_48;
    /* 0x4C */ UNK_TYPE unk_4C;
    /* 0x50 */ f32 unk_50;
    /* 0x54 */ f32 unk_54;
    /* 0x58 */ UNK_TYPE unk_58;
    /* 0x5C */ f32 unk_5C;
    /* 0x60 */ bool hasEnded;
    /* 0x64 */ bool isSpeaking;
    /* 0x68 */ UNK_TYPE unk_68;
    /* 0x6C */ UNK_TYPE unk_6C;
    /* 0x70 */ UNK_TYPE unk_70;
    /* 0x74 */ UNK_TYPE unk_74; // alpha
    /* 0x78 */ UNK_TYPE unk_78;
    /* 0x7C */ UNK_TYPE unk_7C;
} MessageWnd; // size = 0x80


bool func_8005CF20(s32 arg0, u32 buttonMask);
void msgWnd_init(MessageWnd *messageWnd, UNK_PTR *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
void msgWnd_init2(MessageWnd *messageWnd, UNK_PTR *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
void msgWnd_clear(MessageWnd *messageWnd);
void msgWnd_layout(MessageWnd *messageWnd, UNK_PTR arg1);
void msgWnd_addStr(MessageWnd *messageWnd, const char *arg1);
// void func_8005D3F8();
void msgWnd_update(MessageWnd *messageWnd);
void msgWnd_draw(MessageWnd *messageWnd, Gfx **gfxP);
bool msgWnd_isEnd(MessageWnd *messageWnd);
void msgWnd_skip(MessageWnd *messageWnd);
bool msgWnd_isSpeaking(MessageWnd *messageWnd);
bool msgWnd_isScroll(MessageWnd *messageWnd);
s32 msgWnd_getWidth(MessageWnd *messageWnd);
s32 msgWnd_getHeight(MessageWnd *messageWnd);

#define MSGWND_COLOR_BLACK   0
#define MSGWND_COLOR_BLUE    1
#define MSGWND_COLOR_GREEN   2
#define MSGWND_COLOR_CYAN    3
#define MSGWND_COLOR_ORANGE  4
#define MSGWND_COLOR_MAGENTA 5
#define MSGWND_COLOR_ORANGE2 6
#define MSGWND_COLOR_WHITE   7

#define MSGWND_COLOR_EXPAND0(color) #color
#define MSGWND_COLOR_EXPAND1(color) MSGWND_COLOR_EXPAND0(color)
#define MSGWND_COLOR(color)  MSGWND_COLOR_EXPAND1(MSGWND_COLOR_##color)

#define MSG_W(time) "~w" #time
#define MSG_H "~h"
#define MSG_M "~m"
#define MSG_NEWLINE "~n"
#define MSG_END "~z"
#define MSG_COLOR(color) "~" MSGWND_COLOR(color)

#endif

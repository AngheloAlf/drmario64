#ifndef MSGWND_H
#define MSGWND_H

#include "libultra.h"
#include "libc/stdint.h"
#include "libc/stdbool.h"
#include "unk.h"


typedef struct MessageWnd_unk_04 {
    /* 0x0 */ s32 unk_0;
    /* 0x4 */ s32 unk_4;
    /* 0x8 */ s32 unk_8;
    /* 0xC */ s32 color;
} MessageWnd_unk_04; // size = 0x10

typedef struct MessageWnd {
    /* 0x00 */ void *heap;
    /* 0x04 */ MessageWnd_unk_04 *unk_04;
    /* 0x08 */ UNK_TYPE unk_08;
    /* 0x0C */ unsigned char *unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ UNK_TYPE unk_14;
    /* 0x18 */ UNK_TYPE unk_18;
    /* 0x1C */ UNK_TYPE unk_1C;
    /* 0x20 */ s32 unk_20;
    /* 0x24 */ s32 unk_24;
    /* 0x28 */ s32 xPos;
    /* 0x2C */ s32 yPos;
    /* 0x30 */ UNK_TYPE unk_30;
    /* 0x34 */ UNK_TYPE unk_34;
    /* 0x38 */ UNK_TYPE unk_38;
    /* 0x3C */ UNK_TYPE unk_3C;
    /* 0x40 */ s32 column;
    /* 0x44 */ UNK_TYPE unk_44;
    /* 0x48 */ UNK_TYPE unk_48;
    /* 0x4C */ s32 line;
    /* 0x50 */ f32 unk_50;
    /* 0x54 */ f32 unk_54;
    /* 0x58 */ f32 unk_58;
    /* 0x5C */ f32 unk_5C;
    /* 0x60 */ bool hasEnded;
    /* 0x64 */ bool isSpeaking;
    /* 0x68 */ s32 color;
    /* 0x6C */ bool unk_6C;
    /* 0x70 */ s32 timer;
    /* 0x74 */ s32 alpha;
    /* 0x78 */ bool unk_78;
    /* 0x7C */ s32 unk_7C;
} MessageWnd; // size = 0x80


bool func_8005CF20(s32 arg0, u32 buttonMask);
void msgWnd_init(MessageWnd *messageWnd, void **heapP, s32 arg2, s32 arg3, s32 xPos, s32 yPos);
void msgWnd_init2(MessageWnd *messageWnd, void **heapP, s32 arg2, s32 arg3, s32 arg4, s32 xPos, s32 yPos);
void msgWnd_clear(MessageWnd *messageWnd);
void msgWnd_layout(MessageWnd *messageWnd);
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
#define MSGWND_COLOR_EXPAND2(color) MSGWND_COLOR_EXPAND1(MSGWND_COLOR_##color)

#define MSG_WAIT(time) "~w" #time
#define MSG_H "~h"
#define MSG_M "~m"
#define MSG_NEWLINE "~n"
#define MSG_END "~z"
#define MSG_COLOR(color) "~" MSGWND_COLOR_EXPAND2(color)

#endif

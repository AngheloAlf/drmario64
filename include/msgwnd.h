#ifndef MSGWND_H
#define MSGWND_H

#include "libultra.h"
#include "libc/stdint.h"
#include "libc/stdbool.h"

#include "font.h"


typedef struct MessageWndLayout {
    /* 0x0 */ s32 top; /* Original name: top */
    /* 0x4 */ s32 end; /* Original name: end */
    /* 0x8 */ s32 width; /* Original name: width */
    /* 0xC */ s32 color; /* Original name: color */
} MessageWndLayout; // size = 0x10

typedef struct MessageWnd {
    /* 0x00 */ void *heap; /* Original name: heap */
    /* 0x04 */ MessageWndLayout *layout; /* Original name: layout */
    /* 0x08 */ s32 layoutSize; /* Original name: layoutSize */
    /* 0x0C */ unsigned char *msgBuf; /* Original name: msgBuf */
    /* 0x10 */ s32 msgBufSize; /* Original name: msgBufSize */
    /* 0x14 */ s32 msgBufTop; /* Original name: msgBufTop */
    /* 0x18 */ s32 msgBufNow; /* Original name: msgBufNow */
    /* 0x1C */ s32 contFlags; /* Original name: contFlags */
    /* 0x20 */ FontType fontType; /* Original name: fontType */
    /* 0x24 */ bool centering; /* Original name: centering */
    /* 0x28 */ s32 posX; /* Original name: posX */
    /* 0x2C */ s32 posY; /* Original name: posY */
    /* 0x30 */ s32 fntW; /* Original name: fntW */
    /* 0x34 */ s32 fntH; /* Original name: fntH */
    /* 0x38 */ s32 colSize; /* Original name: colSize */
    /* 0x3C */ s32 colStep; /* Original name: colStep */
    /* 0x40 */ s32 colNow; /* Original name: colNow */
    /* 0x44 */ s32 rowSize; /* Original name: rowSize */
    /* 0x48 */ s32 rowStep; /* Original name: rowStep */
    /* 0x4C */ s32 rowNow; /* Original name: rowNow */
    /* 0x50 */ f32 msgCount; /* Original name: msgCount */
    /* 0x54 */ f32 msgSpeed; /* Original name: msgSpeed */
    /* 0x58 */ f32 scrCount; /* Original name: scrCount */
    /* 0x5C */ f32 scrSpeed; /* Original name: scrSpeed */
    /* 0x60 */ bool msgIsEnd; /* Original name: msgIsEnd */
    /* 0x64 */ bool isSpeak; /* Original name: isSpeak */
    /* 0x68 */ s32 topColor; /* Original name: topColor */
    /* 0x6C */ bool keyWait; /* Original name: keyWait */
    /* 0x70 */ s32 countWait; /* Original name: countWait */
    /* 0x74 */ s32 alpha; /* Original name: alpha */
    /* 0x78 */ bool scisFlag; /* Original name: scisFlag */
    /* 0x7C */ s32 grapCount; /* Original name: grapCount */
} MessageWnd; // size = 0x80

void msgWnd_init(MessageWnd *messageWnd, void **heapP, s32 cols, s32 rows, s32 xPos, s32 yPos);
void msgWnd_init2(MessageWnd *messageWnd, void **heapP, s32 bufSize, s32 cols, s32 rows, s32 xPos, s32 yPos);
void msgWnd_clear(MessageWnd *messageWnd);
void msgWnd_layout(MessageWnd *messageWnd);
void msgWnd_addStr(MessageWnd *messageWnd, const char *str);
void msgWnd_update(MessageWnd *messageWnd);
void msgWnd_draw(MessageWnd *messageWnd, Gfx **gfxP);

bool msgWnd_isEnd(const MessageWnd *messageWnd);
void msgWnd_skip(MessageWnd *messageWnd);
bool msgWnd_isSpeaking(const MessageWnd *messageWnd);
bool msgWnd_isScroll(const MessageWnd *messageWnd);
s32 msgWnd_getWidth(const MessageWnd *messageWnd);
s32 msgWnd_getHeight(const MessageWnd *messageWnd);

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

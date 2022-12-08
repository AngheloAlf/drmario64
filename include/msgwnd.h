#ifndef MSGWND_H
#define MSGWND_H

#include "ultra64.h"
#include "libc/stdint.h"
#include "libc/stdbool.h"
#include "unk.h"


typedef struct MessageWnd {
    /* 0x00 */ UNK_TYPE1 unk_00[0x0C];
    /* 0x0C */ char *unk_0C;
    /* 0x10 */ UNK_TYPE unk_10;
    /* 0x14 */ UNK_TYPE unk_14;
    /* 0x18 */ UNK_TYPE unk_18;
    /* 0x1C */ UNK_TYPE1 unk_1C[0x4];
    /* 0x20 */ s32 unk_20;
    /* 0x24 */ s32 unk_24;
    /* 0x38 */ UNK_TYPE1 unk_28[0x38];
    /* 0x60 */ UNK_TYPE unk_60;
    /* 0x64 */ UNK_TYPE1 unk_64[0x1C];
} MessageWnd; // size = 0x80

// This struct probably is MessageWnd
typedef struct struct_8005D78C_arg0 {
    /* 0x0 */ UNK_TYPE1 unk_0[1];
} struct_8005D78C_arg0; // size = ?



bool func_8005CF20(s32 arg0, u32 buttonMask);
void msgWnd_init(MessageWnd *messageWnd, UNK_PTR *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
void msgWnd_init2(MessageWnd *messageWnd, UNK_PTR *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
void msgWnd_clear(MessageWnd *messageWnd);
// void msgWnd_layout();
void msgWnd_addStr(MessageWnd *messageWnd, const char *arg1);
// void func_8005D3F8();
void msgWnd_update(MessageWnd *messageWnd);
void msgWnd_draw(struct_8005D78C_arg0 *, Gfx **gfxP);
bool msgWnd_isEnd(MessageWnd *messageWnd);
void msgWnd_skip(MessageWnd *messageWnd);
// void msgWnd_isSpeaking();
// void msgWnd_isScroll();
// void msgWnd_getWidth();
// void msgWnd_getHeight();

#endif

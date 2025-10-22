#ifndef RECWRITINGMSG_H
#define RECWRITINGMSG_H

#include "msgwnd.h"

typedef struct RecordWritingMessage {
    /* 0x00 */ MessageWnd messageWnd;
    /* 0x80 */ s32 unk_80;
    /* 0x84 */ s32 unk_84;
} RecordWritingMessage; // size = 0x88

void RecWritingMsg_init(RecordWritingMessage *recMessage, void **heap);
void RecWritingMsg_setStr(RecordWritingMessage *recMessage, const char *str);
void RecWritingMsg_calc(RecordWritingMessage *recMessage);
void RecWritingMsg_draw(RecordWritingMessage *recMessage, Gfx **gfxP);
void RecWritingMsg_start(RecordWritingMessage *recMessage);
void RecWritingMsg_end(RecordWritingMessage *recMessage);
bool RecWritingMsg_isEnd(const RecordWritingMessage *recMessage);
void RecWritingMsg_setPos(RecordWritingMessage *recMessage, s32 x, s32 y);

#endif

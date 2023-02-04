#ifndef REPLAY_H
#define REPLAY_H

#include "libultra.h"
#include "libc/stdbool.h"
#include "unk.h"


#define REPLAY_TOTAL_BUFF_SIZE 0x10000

extern u8 *rec_buff;
extern u8 *pRecBuff[];
extern u16 oldCont[];

extern s32 RecPos[];
extern s32 PlayPos[];
extern s32 WaitTime[];

extern s32 max_rec;
extern s32 replay_player;

void replay_record_init_buffer(void **arg0);
void replay_record_init(s32 arg0);
bool replay_record(s32 arg0, u32 arg1);
void replay_play_init(void);
u16 replay_play(s32 arg0);

#endif

#ifndef REPLAY_H
#define REPLAY_H

#include "libultra.h"
#include "libc/stdbool.h"

void replay_record_init_buffer(void **arg0);
void replay_record_init(s32 arg0);
bool replay_record(s32 arg0, u32 arg1);
void replay_play_init(void);
u16 replay_play(s32 arg0);

#endif

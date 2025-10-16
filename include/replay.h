#ifndef REPLAY_H
#define REPLAY_H

#include "libultra.h"
#include "libc/stdbool.h"

void replay_record_init_buffer(void **heap);
void replay_record_init(s32 player);
bool replay_record(s32 player, u16 pad);
void replay_play_init(void);
u16 replay_play(s32 player);

#endif

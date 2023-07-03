#ifndef JOY_H
#define JOY_H

#include "libultra.h"

s32 joyInit(s32 arg0);
void joyProcCore(void);
void joyCursorFastSet(u16 mask, u8 index);
s32 joyResponseCheck();

#endif

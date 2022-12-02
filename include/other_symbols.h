#ifndef OTHER_SYMBOLS_H
#define OTHER_SYMBOLS_H

#include "ultra64.h"
#include "libc/stdint.h"
#include "unknown_structs.h"
#include "unk.h"
#include "alignment.h"


extern struct_80124610 D_80124610;
extern struct_80205000 D_80205000;

#define SCREEN_WIDTH  320
#define SCREEN_HEIGHT 240

extern u16 gFramebuffers[2][SCREEN_HEIGHT * SCREEN_WIDTH];

#endif

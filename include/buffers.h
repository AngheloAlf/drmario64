#ifndef BUFFERS_H
#define BUFFERS_H

#include "libultra.h"
#include "unknown_structs.h"
#include "alignment.h"
#include "macros_defines.h"

/**
 * Original name: Heap_bufferp
 */
extern u8 Heap_bufferp[];

extern u8 D_80205000[];

extern u16 gFramebuffers[2][SCREEN_HEIGHT * SCREEN_WIDTH];

#endif

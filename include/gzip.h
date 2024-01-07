#ifndef GZIP_H
#define GZIP_H

#include "libultra.h"
#include "libc/stdint.h"
#include "libc/stdbool.h"
#include "other_types.h"
#include "unk.h"

s32 inflate(void);

size_t expand_gzip(RomOffset segmentRom, void *dstAddr, size_t segmentSize);

s32 fill_inbuf(s32 arg0);
void flush_window(void);

/**
 * Original name: insize
 */
extern u32 insize;
/**
 * Original name: inbuf
 */
extern u8 inbuf[0x2000];

/**
 * Original name: inptr
 */
extern u32 inptr;

/**
 * Original name: outcnt
 */
extern size_t outcnt;

/**
 * Original name: window
 */
extern u8 window[0x8000];

#endif

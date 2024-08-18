#ifndef GZIP_H
#define GZIP_H

#include "libultra.h"
#include "libc/stdint.h"
#include "libc/stdbool.h"
#include "other_types.h"

typedef struct GzipFileDescriptor {
    /* 0x0 */ void *addr;
    /* 0x4 */ size_t size;
} GzipFileDescriptor; // size == 0x8

s32 inflate(void);

size_t expand_gzip(RomOffset segmentRom, void *dstAddr, size_t segmentSize);

s32 fill_inbuf(s32 arg0);
void flush_window(void);

#define INBUFSIZ 0x2000
#define WSIZE 0x8000

extern u8 inbuf[INBUFSIZ];

extern u32 insize;

extern u32 inptr;

extern size_t outcnt;

extern u8 window[WSIZE];

#if DECLARE_COMMON_SYMS
// inflate
extern u32 bk;
extern u32 bb;
extern u32 hufts;

// unzip
extern GzipFileDescriptor ofd;
extern GzipFileDescriptor ifd;
extern s32 bytes_in;
extern s32 bytes_out;
#endif

#endif

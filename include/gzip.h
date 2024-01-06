#ifndef GZIP_H
#define GZIP_H

#include "libultra.h"
#include "libc/stdint.h"
#include "libc/stdbool.h"
#include "other_types.h"
#include "unk.h"

typedef struct struct_80029C04 {
    RomOffset segmentRom;
    size_t segmentSize;
} struct_80029C04;

typedef struct struct_8001D7F8 {
    /* 0x0 */ u8 *unk_0; // dstAddr
    /* 0x4 */ size_t unk_4; // uncompressedSize
} struct_8001D7F8; // size >= 0x8


void *func_80000720(s32 arg0);
void func_8000075C(void);
// void func_80000778();
UNK_TYPE func_80000D0C(UNK_PTR arg0);
// void func_80000D48();
s32 func_80001260(void);
s32 func_80001480(void);
s32 func_80001620(void);
s32 inflate_block(s32 *arg0);
s32 inflate(void);

size_t expand_gzip(RomOffset segmentRom, void *dstAddr, size_t segmentSize);
size_t auRomDataRead(struct_80029C04 *arg0, u8 *arg1, size_t blockSize);
size_t data_write(struct_8001D7F8 *arg0, u8 *arg1, size_t arg2);
UNK_TYPE unzip(void);
u32 updcrc(u8 *arg0, size_t arg1);
void clear_bufs(void);
s32 fill_inbuf(s32 arg0);
void func_800022A8(struct_8001D7F8 *arg0, u8 *arg1, size_t arg2);
void flush_window(void);

/**
 * Original name: ofd
 */
extern struct_8001D7F8 ofd;

extern u32 insize; // maybe volatile?
extern u8 inbuf[0x2000];

extern s32 bytes_in;
extern s32 bytes_out;

extern UNK_TYPE gzip_malloc_tmp;
/**
 * Original name: gzip_mem_buff
 */
extern UNK_TYPE gzip_mem_buff[];
/**
 * Original name: gzip_malloc_addr
 */
extern UNK_TYPE *gzip_malloc_addr;

/**
 * Original name: bk
 */
extern u32 bk;
extern u32 bb;
/**
 * Original name: hufts
 */
extern u32 hufts;
/**
 * Original name: inptr
 */
extern u32 inptr;

extern size_t outcnt;

extern struct_80029C04 ifd; /* Original name ifd */

extern s32 crc_32_tab[]; /* Original name: crc_32_tab */
extern u32 crc_132; /* Original name: crc static symbol */

extern u8 window[0x8000];

#endif

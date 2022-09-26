#ifndef DMA_TABLE_H
#define DMA_TABLE_H

#include "libc/stdint.h"

typedef void (*SegmentEntryFunc)(void* arg);

typedef struct DmaTableEntry {
    /* 0x00 */ uintptr_t vram;
    /* 0x04 */ SegmentEntryFunc entry;
    /* 0x08 */ uintptr_t bssStart;
    /* 0x0C */ uintptr_t bssEnd;
} DmaTableEntry; // size = 0x10

extern DmaTableEntry gDmaTable[];

#endif

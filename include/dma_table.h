#ifndef DMA_TABLE_H
#define DMA_TABLE_H

#include "libc/stdint.h"

typedef void (*SegmentEntryFunc)(void* arg);

typedef struct DmaTableEntry {
    /* 0x00 */ void* vram;
    /* 0x04 */ SegmentEntryFunc entry;
    /* 0x08 */ void* bssStart;
    /* 0x0C */ void* bssEnd;
} DmaTableEntry; // size = 0x10

extern DmaTableEntry gMainSegmentDmaInfo;

#endif

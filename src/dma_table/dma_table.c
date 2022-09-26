#include "dma_table.h"
#include "segment_symbols.h"

// I have no reason to believe this is an array, but why not?

DmaTableEntry gDmaTable[] = {
    { SEGMENT_START(code), (void*)SEGMENT_START(code), 0x800B3640, 0x80124610 },
};

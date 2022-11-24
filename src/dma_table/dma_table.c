#include "dma_table.h"
#include "segment_symbols.h"

void func_80029C50(void* arg);

// I have no reason to believe this is an array, but why not?

DmaTableEntry gDmaTable[] = {
    { SEGMENT_START(main_segment), func_80029C50, SEGMENT_BSS_START(main_segment), SEGMENT_BSS_END(main_segment) },
};

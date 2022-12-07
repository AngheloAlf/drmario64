#include "dma_table.h"
#include "segment_symbols.h"

void mainproc(void *arg);

// I have no reason to believe this is an array, but why not?

DmaTableEntry gDmaTable[] = {
    { SEGMENT_VRAM_START(main_segment), mainproc, SEGMENT_BSS_START(main_segment), SEGMENT_BSS_END(main_segment) },
};

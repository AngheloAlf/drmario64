#include "dma_table.h"
#include "segment_symbols.h"
#include "main.h"

DmaTableEntry gMainSegmentDmaInfo = {
    SEGMENT_VRAM_START(main_segment),
    mainproc,
    SEGMENT_BSS_START(main_segment),
    SEGMENT_BSS_END(main_segment),
};

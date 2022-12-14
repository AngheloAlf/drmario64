#include "ultra64.h"
#include "include_asm.h"
#include "boot_functions.h"
#include "boot_variables.h"
#include "dma_table.h"
#include "segment_symbols.h"

extern OSMesg B_8001F8C0[];

void LoadMainSegment(void *arg0) {
    DmaDataRomToRam(SEGMENT_ROM_START(dma_table), gDmaTable, SEGMENT_ROM_SIZE(dma_table));
    DecompressRomToRam(SEGMENT_ROM_START(main_segment), gDmaTable[0].vram, SEGMENT_ROM_SIZE(main_segment));

    bzero(gDmaTable[0].bssStart, gDmaTable[0].bssEnd - gDmaTable[0].bssStart);
    gDmaTable[0].entry(arg0);
}

void func_80000580(void *arg0) {
    osCreatePiManager(150, &B_80029C08, B_8001F8C0, 50);
    osCreateThread(&B_80011010, 3, LoadMainSegment, arg0, STACK_TOP(B_800131C0), 10);
    osStartThread(&B_80011010);

    while (1) {
        D_8000E190();
    }
}

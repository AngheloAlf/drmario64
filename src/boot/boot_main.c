#include "ultra64.h"
#include "boot_functions.h"
#include "boot_variables.h"
#include "dma_table.h"
#include "segment_symbols.h"

void func_80000460(void) {
}

void (*D_8000E190)() = func_80000460;

void func_80000468(void) {
    osStopThread(&B_80011010);
}

void func_80000488(void *arg0) {
    D_8000E190 = arg0;
}

void bootproc(void) {
    osInitialize();
    // TODO: STACK_TOP
    osCreateThread(&B_80010E60, 1, func_80000580, NULL, &B_800131C0, 1);
    osStartThread(&B_80010E60);
}

void LoadMainSegment(void *arg0) {
    romoffset_t mainSegmentStart;

    DmaDataRomToRam(SEGMENT_ROM_START(dma_table), gDmaTable, SEGMENT_ROM_SIZE(dma_table));

    mainSegmentStart = SEGMENT_ROM_START(main_segment);

#if VERSION_CN
    do {
#endif
        DecompressRomToRam(mainSegmentStart, gDmaTable[0].vram, SEGMENT_ROM_SIZE(main_segment));

        bzero(gDmaTable[0].bssStart, gDmaTable[0].bssEnd - gDmaTable[0].bssStart);
#if VERSION_CN
    } while (0);
#endif

    gDmaTable[0].entry(arg0);
}

extern OSMesg B_8001F8C0[];

void func_80000580(void *arg0) {
    osCreatePiManager(150, &B_80029C08, B_8001F8C0, 50);
    osCreateThread(&B_80011010, 3, LoadMainSegment, arg0, STACK_TOP(B_800131C0), 10);
    osStartThread(&B_80011010);

    while (1) {
        D_8000E190();
    }
}

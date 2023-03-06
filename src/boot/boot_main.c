#include "libultra.h"
#include "boot_functions.h"
#include "boot_variables.h"
#include "dma_table.h"
#include "segment_symbols.h"
#include "macros_defines.h"
#include "dm_thread.h"

void Idle_Nop(void) {
}

void (*D_8000E190)() = Idle_Nop;

void func_80000468(void) {
    osStopThread(&B_80011010);
}

void func_80000488(void (*arg0)()) {
    D_8000E190 = arg0;
}

void bootproc(void) {
    osInitialize();
    osCreateThread(&B_80010E60, THREAD_ID_IDLE_BOOT, Idle_ThreadEntry, NULL, STACK_TOP(B_800111C0),
                   THREAD_PRI_IDLE_BOOT);
    osStartThread(&B_80010E60);
}

void Main_ThreadEntry(void *arg0) {
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

extern OSMesg B_8001F8C0[50];

void Idle_ThreadEntry(void *arg0) {
    osCreatePiManager(OS_PRIORITY_PIMGR, &B_80029C08, B_8001F8C0, ARRAY_COUNT(B_8001F8C0));
    osCreateThread(&B_80011010, THREAD_ID_MAIN, Main_ThreadEntry, arg0, STACK_TOP(B_800131C0), THREAD_PRI_MAIN);
    osStartThread(&B_80011010);

    while (1) {
        D_8000E190();
    }
}

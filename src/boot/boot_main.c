#include "boot_main.h"

#include "libc/stdbool.h"

#include "libultra.h"
#include "dma_table.h"
#include "segment_symbols.h"
#include "macros_defines.h"
#include "dmadata.h"
#include "dm_thread.h"
#include "util.h"

void Idle_ThreadEntry(void *arg);

static OSThread sIdleThread;
static OSThread sMainThread;
static STACK(sIdleStack, 0x2000);
static STACK(sMainStack, 0x2000);
STACK(gBootThreadStack, BOOT_STACK_SIZE);

void Idle_Nop(void) {
}

void (*D_8000E190)(void) = Idle_Nop;

void Main_StopThread(void) {
    osStopThread(&sMainThread);
}

void func_80000488(void (*arg0)()) {
    D_8000E190 = arg0;
}

void bootproc(void) {
    osInitialize();
    osCreateThread(&sIdleThread, THREAD_ID_IDLE, Idle_ThreadEntry, NULL, STACK_TOP(sIdleStack), THREAD_PRI_IDLE_BOOT);
    osStartThread(&sIdleThread);
}

void Main_ThreadEntry(void *arg) {
    RomOffset mainSegmentStart;

    DmaData_RomToRam(SEGMENT_ROM_START(dma_table), &gMainSegmentDmaInfo, SEGMENT_ROM_SIZE(dma_table));

    mainSegmentStart = SEGMENT_ROM_START(main_segment);

#if VERSION_CN
    do {
#endif
        DecompressRomToRam(mainSegmentStart, gMainSegmentDmaInfo.vram, SEGMENT_ROM_SIZE(main_segment));

        bzero(gMainSegmentDmaInfo.bssStart, gMainSegmentDmaInfo.bssEnd - gMainSegmentDmaInfo.bssStart);
#if VERSION_CN
    } while (0);
#endif

    gMainSegmentDmaInfo.entry(arg);
}

OSMesg sPiMgrCmdBuff[SPIMGRCMDBUFF_LEN];
OSMesgQueue sPiMgrCmdQueue;

void Idle_ThreadEntry(void *arg) {
    osCreatePiManager(OS_PRIORITY_PIMGR, &sPiMgrCmdQueue, sPiMgrCmdBuff, ARRAY_COUNT(sPiMgrCmdBuff));
    osCreateThread(&sMainThread, THREAD_ID_MAIN, Main_ThreadEntry, arg, STACK_TOP(sMainStack), THREAD_PRI_MAIN);
    osStartThread(&sMainThread);

    while (true) {
        D_8000E190();
    }
}

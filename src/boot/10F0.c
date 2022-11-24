#include "ultra64.h"
#include "include_asm.h"
#include "boot_functions.h"
#include "boot_variables.h"
#include "dma_table.h"
#include "segment_symbols.h"

extern OSMesg B_8001F8C0[];

void func_800004F0(void *arg0) {
    func_80000620(SEGMENT_ROM_START(dma_table), gDmaTable, SEGMENT_ROM_SIZE(dma_table));
    func_80002380(SEGMENT_ROM_START(code_compressed), gDmaTable[0].vram, SEGMENT_ROM_SIZE(code_compressed));

    bzero(gDmaTable[0].bssStart, gDmaTable[0].bssEnd - gDmaTable[0].bssStart);
    gDmaTable[0].entry(arg0);
}

void func_80000580(void* arg0) {
    osCreatePiManager(150, &B_80029C08, B_8001F8C0, 50);
    osCreateThread(&B_80011010, 3, func_800004F0, arg0, STACK_TOP(B_800131C0), 10);
    osStartThread(&B_80011010);

    while (1) {
        (*D_8000E190)();
    }
}

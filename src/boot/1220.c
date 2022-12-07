#include "ultra64.h"
#include "include_asm.h"
#include "macros_defines.h"
#include "boot_functions.h"
#include "boot_variables.h"

s8 D_8000E1A0 = true;

void *DmaDataRomToRam(romoffset_t segmentRom, void *segmentVram, size_t segmentSize) {
    size_t remainingSize;
    romoffset_t currentRom;
    uintptr_t currentVram;

    if (D_8000E1A0) {
        osCreateMesgQueue(&B_800151C0, B_800151D8, ARRAY_COUNT(B_800151D8));
        D_8000E1A0 = false;
    }

    osInvalDCache(segmentVram, segmentSize);

    remainingSize = segmentSize;
    currentRom = segmentRom;
    currentVram = (uintptr_t)segmentVram;

    while (remainingSize > 0) {
        OSIoMesg mb;
        size_t blkSize = remainingSize;

        if (remainingSize > 0x2000) {
            blkSize = 0x2000;
        }

        osPiStartDma(&mb, OS_MESG_PRI_NORMAL, OS_READ, currentRom, (void *)currentVram, blkSize, &B_800151C0);
        currentRom += blkSize;
        currentVram += blkSize;
        remainingSize -= blkSize;
        osRecvMesg(&B_800151C0, NULL, OS_MESG_BLOCK);
    }

    return (void *)((uintptr_t)segmentVram + segmentSize);
}

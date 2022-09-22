#include "ultra64.h"
#include "include_asm.h"
#include "macros.h"
#include "libc/stdint.h"
#include "libc/stdbool.h"

extern OSMesgQueue B_800151C0;
extern OSMesg B_800151D8[1];
extern s8 D_8000E1A0;

void *func_80000620(romoffset_t segmentRom, void *segmentVram, size_t segmentSize) {
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
    currentVram = segmentVram;

    while (remainingSize > 0) {
        OSIoMesg mb;
        size_t blkSize = remainingSize;

        if (remainingSize > 0x2000) {
            blkSize = 0x2000;
        }

        osPiStartDma(&mb, OS_MESG_PRI_NORMAL, OS_READ, currentRom, currentVram, blkSize, &B_800151C0);
        currentRom += blkSize;
        currentVram += blkSize;
        remainingSize -= blkSize;
        osRecvMesg(&B_800151C0, NULL, OS_MESG_BLOCK);
    }

    return (uintptr_t)segmentVram + segmentSize;
}

INCLUDE_ASM("boot/1220", func_80000720);

INCLUDE_ASM("boot/1220", func_8000075C);

INCLUDE_ASM("boot/1220", func_80000778);

INCLUDE_ASM("boot/1220", func_80000D0C);

INCLUDE_ASM("boot/1220", func_80000D48);

INCLUDE_ASM("boot/1220", func_80001260);

INCLUDE_ASM("boot/1220", func_80001480);

INCLUDE_ASM("boot/1220", func_80001620);

INCLUDE_ASM("boot/1220", func_80001D4C);

INCLUDE_ASM("boot/1220", func_80001EB4);

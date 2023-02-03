#include "libultra.h"
#include "include_asm.h"
#include "macros_defines.h"
#include "boot_functions.h"
#include "boot_variables.h"

#if VERSION_CN
OSPiHandle *D_8000EC40_cn = NULL;

OSPiHandle *func_80000690_cn(void) {
    if (D_8000EC40_cn == NULL) {
        D_8000EC40_cn = osCartRomInit();
    }

    return D_8000EC40_cn;
}

bool D_8000EC44_cn = false;
#endif

#if VERSION_US
s8 D_8000E1A0 = true;
#endif

void *DmaDataRomToRam(romoffset_t segmentRom, void *segmentVram, size_t segmentSize) {
    size_t remainingSize;
    romoffset_t currentRom;
    uintptr_t currentVram;

#if VERSION_US
    if (D_8000E1A0)
#endif
#if VERSION_CN
        if (!D_8000EC44_cn)
#endif
        {
            osCreateMesgQueue(&B_800151C0, B_800151D8, ARRAY_COUNT(B_800151D8));
#if VERSION_US
            D_8000E1A0 = false;
#endif
#if VERSION_CN
            D_8000EC44_cn = true;
#endif
        }

    osInvalDCache(segmentVram, segmentSize);

    remainingSize = segmentSize;
    currentRom = segmentRom;
    currentVram = (uintptr_t)segmentVram;

    while (remainingSize > 0) {
        size_t blkSize = MIN(remainingSize, 0x2000);
        OSIoMesg mb;

#if VERSION_US
        osPiStartDma(&mb, OS_MESG_PRI_NORMAL, OS_READ, currentRom, (void *)currentVram, blkSize, &B_800151C0);
#endif

#if VERSION_CN
        mb.hdr.pri = 0;
        mb.hdr.retQueue = &B_800151C0;
        mb.dramAddr = (void *)currentVram;
        mb.devAddr = currentRom;
        mb.size = blkSize;
        osEPiStartDma(func_80000690_cn(), &mb, OS_READ);
#endif

        currentRom += blkSize;
        currentVram += blkSize;
        remainingSize -= blkSize;
        osRecvMesg(&B_800151C0, NULL, OS_MESG_BLOCK);
    }

    return (void *)((uintptr_t)segmentVram + segmentSize);
}

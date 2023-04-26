#include "libultra.h"
#include "macros_defines.h"
#include "boot_functions.h"
#include "boot_variables.h"

#if VERSION_CN || VERSION_GW
OSPiHandle *D_8000EC40_cn = NULL;

OSPiHandle *DmaData_80000690_cn(void) {
    if (D_8000EC40_cn == NULL) {
        D_8000EC40_cn = osCartRomInit();
    }

    return D_8000EC40_cn;
}
#endif

#if VERSION_CN || VERSION_GW
bool sDmaDataIsInitialized = false;

#define DMADATA_IS_INITIALIZED (sDmaDataIsInitialized)
#define DMADATA_SET_INITIALIZED sDmaDataIsInitialized = true

#define DMADATA_COPY_BLOCK(mb, currentRom, currentVram, blkSize) \
    (mb)->hdr.pri = OS_MESG_PRI_NORMAL;                          \
    (mb)->hdr.retQueue = &B_800151C0;                            \
    (mb)->dramAddr = (void *)currentVram;                        \
    (mb)->devAddr = currentRom;                                  \
    (mb)->size = blkSize;                                        \
    osEPiStartDma(DmaData_80000690_cn(), mb, OS_READ)
#endif

#if VERSION_US
s8 sDmaDataNeedsInitialization = true;

#define DMADATA_IS_INITIALIZED !sDmaDataNeedsInitialization
#define DMADATA_SET_INITIALIZED sDmaDataNeedsInitialization = false

#define DMADATA_COPY_BLOCK(mb, currentRom, currentVram, blkSize) \
    osPiStartDma(mb, OS_MESG_PRI_NORMAL, OS_READ, currentRom, (void *)currentVram, blkSize, &B_800151C0)
#endif

void *DmaData_RomToRam(romoffset_t segmentRom, void *segmentVram, size_t segmentSize) {
    size_t remainingSize;
    romoffset_t currentRom;
    uintptr_t currentVram;

    if (!DMADATA_IS_INITIALIZED) {
        osCreateMesgQueue(&B_800151C0, B_800151D8, ARRAY_COUNT(B_800151D8));

        DMADATA_SET_INITIALIZED;
    }

    osInvalDCache(segmentVram, segmentSize);

    remainingSize = segmentSize;
    currentRom = segmentRom;
    currentVram = (uintptr_t)segmentVram;

    while (remainingSize > 0) {
        size_t blkSize = MIN(remainingSize, 0x2000);
        OSIoMesg mb;

        DMADATA_COPY_BLOCK(&mb, currentRom, currentVram, blkSize);

        currentRom += blkSize;
        currentVram += blkSize;
        remainingSize -= blkSize;
        osRecvMesg(&B_800151C0, NULL, OS_MESG_BLOCK);
    }

    return (void *)((uintptr_t)segmentVram + segmentSize);
}

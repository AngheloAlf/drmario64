#ifndef DMADATA_H
#define DMADATA_H

#include "libultra.h"
#include "other_types.h"

#if VERSION_CN
OSPiHandle *DmaData_80000690_cn(void);
#endif

void *DmaData_RomToRam(RomOffset segmentRom, void *segmentVram, size_t segmentSize);

#if VERSION_US
#define DMADATA_COPY_BLOCK(mb, currentRom, currentVram, blkSize, mq) \
    osPiStartDma(mb, OS_MESG_PRI_NORMAL, OS_READ, currentRom, (void *)currentVram, blkSize, mq)
#elif VERSION_CN || VERSION_GW
#define DMADATA_COPY_BLOCK(mb, currentRom, currentVram, blkSize, mq) \
    (mb)->hdr.pri = OS_MESG_PRI_NORMAL;                              \
    (mb)->hdr.retQueue = mq;                                         \
    (mb)->dramAddr = (void *)currentVram;                            \
    (mb)->devAddr = currentRom;                                      \
    (mb)->size = blkSize;                                            \
    osEPiStartDma(DmaData_80000690_cn(), mb, OS_READ)
#endif

#endif

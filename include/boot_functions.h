#ifndef BOOT_FUNCTIONS
#define BOOT_FUNCTIONS

#include "libultra.h"
#include "libc/stdint.h"
#include "unknown_structs.h"
#include "unk.h"


void Main_StopThread(void);
void func_80000488(void (*arg0)());

void *DmaData_RomToRam(RomOffset segmentRom, void *segmentVram, size_t segmentSize);

#if VERSION_CN
OSPiHandle *DmaData_80000690_cn(void);
#endif

#ifdef M2CTX
u64 __udivdi3(u64, u64);
#endif

#endif

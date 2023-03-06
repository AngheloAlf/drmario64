#ifndef BOOT_FUNCTIONS
#define BOOT_FUNCTIONS

#include "libultra.h"
#include "libc/stdint.h"
#include "unknown_structs.h"
#include "unk.h"


void Main_StopThread(void);
void func_80000488(void (*arg0)());

void *DmaDataRomToRam(romoffset_t segmentRom, void *segmentVram, size_t segmentSize);

void *DecompressRomToRam(romoffset_t segmentRom, void *dstAddr, size_t segmentSize);
s32 WrapI(s32 start, s32 end, s32 value);
f32 WrapF(f32 start, f32 end, f32 value);

#if VERSION_CN
OSPiHandle *func_80000690_cn(void);
#endif

#ifdef M2CTX
u64 __udivdi3(u64, u64);
#endif

#endif

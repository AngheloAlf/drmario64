#ifndef BOOT_FUNCTIONS
#define BOOT_FUNCTIONS

#include "ultra64.h"
#include "libc/stdint.h"
#include "unknown_structs.h"
#include "unk.h"


void func_80000460(void);
void func_80000468(void);
void func_80000488(void* arg0);
void bootproc(void);

void LoadMainSegment(void *arg0);
void func_80000580(void* arg0);

void *DmaDataRomToRam(romoffset_t segmentRom, void *segmentVram, size_t segmentSize);

void *DecompressRomToRam(romoffset_t segmentRom, void *dstAddr, size_t segmentSize);
s32 WrapI(s32 start, s32 end, s32 value);
f32 WrapF(f32 start, f32 end, f32 value);

#endif

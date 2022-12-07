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
s32 WrapI(s32 arg0, s32 arg1, s32 arg2);
f32 WrapF(f32 arg0, f32 arg1, f32 arg2);

#endif

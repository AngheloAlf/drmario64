#ifndef UTIL_H
#define UTIL_H

#include "libultra.h"
#include "other_types.h"

void *DecompressRomToRam(RomOffset segmentRom, void *dstAddr, size_t segmentSize);
s32 WrapI(s32 start, s32 end, s32 value);
f32 WrapF(f32 start, f32 end, f32 value);

#endif

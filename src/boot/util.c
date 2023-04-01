#include "libultra.h"
#include "macros_defines.h"
#include "boot_functions.h"
#include "boot_variables.h"
#include "libc/math.h"
#include "gzip.h"

/**
 * Original name: ExpandGZip
 */
void *DecompressRomToRam(romoffset_t segmentRom, void *dstAddr, size_t segmentSize) {
#ifndef UNCOMPRESSED_ROM
    return (void *)ALIGN8((uintptr_t)dstAddr + expand_gzip(segmentRom, dstAddr, segmentSize));
#else
    // The simplest way to allow booting a ROM with uncompressed segments is to just DMA the segment instead of actually
    // decompressing it
    return (void *)ALIGN8((uintptr_t)DmaData_RomToRam(segmentRom, dstAddr, segmentSize));
#endif
}

/**
 * Original name: WrapI
 */
s32 WrapI(s32 start, s32 end, s32 value) {
    s32 size = end - start;

    value = (value - start) % size;
    if (value < 0) {
        value += size;
    }
    return value + start;
}

/**
 * Original name: WrapF
 */
f32 WrapF(f32 start, f32 end, f32 value) {
    if ((start <= value) && (value < end)) {
        return value;
    } else {
        f32 size = end - start;

        value = fmod(value - start, size);
        if (value < 0.0f) {
            value += size;
        }
        value = value + start;
        return value;
    }
}

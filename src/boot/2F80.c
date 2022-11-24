#include "ultra64.h"
#include "include_asm.h"
#include "boot_functions.h"
#include "boot_variables.h"

void *func_80002380(romoffset_t segmentRom, void *dstAddr, romoffset_t segmentSize) {
    return (void *)ALIGN8((uintptr_t)dstAddr + func_80001F90(segmentRom, dstAddr, segmentSize));
}

INCLUDE_ASM("asm/nonmatchings/boot/2F80", func_800023B4);

INCLUDE_ASM("asm/nonmatchings/boot/2F80", func_80002400);

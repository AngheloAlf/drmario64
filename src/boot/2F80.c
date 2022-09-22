#include "ultra64.h"
#include "include_asm.h"
#include "boot_functions.h"
#include "boot_variables.h"

void *func_80002380(romoffset_t segmentRom, UNK_TYPE arg1, romoffset_t segmentSize) {
    return ALIGN8(arg1 + func_80001F90(segmentRom, arg1, segmentSize));
}

INCLUDE_ASM("boot/2F80", func_800023B4);

INCLUDE_ASM("boot/2F80", func_80002400);

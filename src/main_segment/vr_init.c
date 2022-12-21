/**
 * Original filename: vr_init.c
 */

#include "ultra64.h"
#include "include_asm.h"
#include "macros_defines.h"
#include "unknown_structs.h"
#include "main_segment_functions.h"
#include "main_segment_variables.h"

void sgenrand(u32 arg0) {
    mt[0] = arg0;

    for (mti = 1; mti < ARRAY_COUNT(mt); mti++) {
        mt[mti] = mt[mti - 1] * 69069;
    }
}

INCLUDE_ASM("asm/nonmatchings/main_segment/vr_init", genrand);

/**
 * Original filename: vr_init.c
 */

#include "libultra.h"
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

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/vr_init", genrand);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/vr_init", genrand);
#endif

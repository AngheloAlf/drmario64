#include "ultra64.h"
#include "include_asm.h"
#include "macros_defines.h"
#include "unknown_structs.h"
#include "main_segment_functions.h"
#include "main_segment_variables.h"


void func_8002E830(u32 arg0) {
    B_800E4640[0] = arg0;
    D_80088480 = 1;

    while (D_80088480 < ARRAY_COUNT(B_800E4640)) {
        B_800E4640[D_80088480] = B_800E4640[D_80088480 - 1] * 69069;
        D_80088480++;
    }
}

INCLUDE_ASM("asm/nonmatchings/main_segment/004BE0", func_8002E8B0);

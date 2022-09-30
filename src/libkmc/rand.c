#include "ultra64.h"
#include "include_asm.h"
#include "gcc/stdlib.h"
#include "macros_defines.h"

s32 sRandNext BSS;

int rand() {
    sRandNext = sRandNext * 1103515245 + 12345;

    return ((u32)((sRandNext + 1)>>16) % (RAND_MAX + 1));
}

void srand(unsigned seed) {
   sRandNext = seed;
}

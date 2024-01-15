#include "libultra.h"
#include "include_asm.h"
#include "gcc/stdlib.h"
#include "macros_defines.h"
#include "attributes.h"

static s32 sRandNext;

/**
 * Original name: rand
 */
int rand() {
    sRandNext = sRandNext * 1103515245 + 12345;

    return ((u32)((sRandNext + 1) >> 16) % (RAND_MAX + 1));
}

/**
 * Original name: srand
 */
void srand(unsigned seed) {
    sRandNext = seed;
}

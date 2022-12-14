/**
 * Original filename: calc.c
 */

#include "ultra64.h"
#include "include_asm.h"
#include "macros_defines.h"
#include "unknown_structs.h"
#include "main_segment_functions.h"
#include "main_segment_variables.h"

//f32 func_8007BC20(f32 arg0) {
//    return sinf(arg0) / cosf(arg0);
//}
INCLUDE_ASM("asm/nonmatchings/main_segment/calc", func_8007BC20);

INCLUDE_ASM("asm/nonmatchings/main_segment/calc", func_8007BC54);

INCLUDE_ASM("asm/nonmatchings/main_segment/calc", func_8007BD30);

INCLUDE_ASM("asm/nonmatchings/main_segment/calc", func_8007BEEC);

INCLUDE_ASM("asm/nonmatchings/main_segment/calc", func_8007BFE0);

INCLUDE_ASM("asm/nonmatchings/main_segment/calc", func_8007C0C4);

INCLUDE_ASM("asm/nonmatchings/main_segment/calc", func_8007C244);

INCLUDE_ASM("asm/nonmatchings/main_segment/calc", func_8007C480);

/**
 * Original name: angleF2S
 */
s16 angleF2S(f32 arg0) {
    return (f32)(arg0 * (0x10000 / 360.0));
}

INCLUDE_ASM("asm/nonmatchings/main_segment/calc", func_8007C4D8);

INCLUDE_ASM("asm/nonmatchings/main_segment/calc", func_8007C540);

INCLUDE_ASM("asm/nonmatchings/main_segment/calc", func_8007C5A8);

INCLUDE_ASM("asm/nonmatchings/main_segment/calc", func_8007C624);

INCLUDE_ASM("asm/nonmatchings/main_segment/calc", func_8007C6D8);

INCLUDE_ASM("asm/nonmatchings/main_segment/calc", func_8007C780);

INCLUDE_ASM("asm/nonmatchings/main_segment/calc", func_8007C7E8);

INCLUDE_ASM("asm/nonmatchings/main_segment/calc", func_8007C894);

INCLUDE_ASM("asm/nonmatchings/main_segment/calc", func_8007C9C8);

INCLUDE_ASM("asm/nonmatchings/main_segment/calc", func_8007CAFC);

INCLUDE_ASM("asm/nonmatchings/main_segment/calc", func_8007CBE4);

INCLUDE_ASM("asm/nonmatchings/main_segment/calc", func_8007CC68);

INCLUDE_ASM("asm/nonmatchings/main_segment/calc", func_8007CCFC);

INCLUDE_ASM("asm/nonmatchings/main_segment/calc", func_8007CD78);

INCLUDE_ASM("asm/nonmatchings/main_segment/calc", func_8007CFB4);

INCLUDE_ASM("asm/nonmatchings/main_segment/calc", randomize00);

INCLUDE_ASM("asm/nonmatchings/main_segment/calc", randomseed);

/**
 * Original name: irandom
 */
u16 irandom(void) {
    randomindex++;

    if (randomindex > ARRAY_COUNT(randomtable)) {
        randomize00();
        randomindex = 0;
    }
    return randomtable[randomindex];
}

INCLUDE_ASM("asm/nonmatchings/main_segment/calc", random);

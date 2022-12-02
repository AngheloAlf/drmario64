#include "ultra64.h"
#include "include_asm.h"
#include "macros_defines.h"
#include "unknown_structs.h"
#include "unk.h"
#include "main_segment_functions.h"
#include "main_segment_variables.h"


INCLUDE_RODATA("asm/nonmatchings/main_segment/031BA0", RO_800B1950);

s32 func_8005B7F0(const char *arg0) {
    s32 var_v1;

    if (arg0[0] < 0x80) {
        var_v1 = 1;
        if (arg0[0] == '~') {
            if (arg0[1] == 'z') {
                var_v1 = 0;
            } else {
                var_v1 = (-(arg0[1] == 'w') & 3) | 2;
            }
        }
    } else {
        var_v1 = 2;
        if ((char)(arg0[0] + 0x5F) < 0x3F) {
            var_v1 = 1;
        }
    }
    return var_v1;
}

s32 func_8005B858(const char *arg0) {
    s32 temp_v0;
    s32 var_s0 = 0;

    do {
        temp_v0 = func_8005B7F0(arg0 + var_s0);
        var_s0 += temp_v0;
    } while (temp_v0 != 0);
    return var_s0;
}

INCLUDE_ASM("asm/nonmatchings/main_segment/031BA0", func_8005B898);

u16 func_8005B8D8(u8 arg0) {
    return D_800A6D90[arg0];
}

INCLUDE_ASM("asm/nonmatchings/main_segment/031BA0", func_8005B8F0);

INCLUDE_ASM("asm/nonmatchings/main_segment/031BA0", func_8005B940);

INCLUDE_ASM("asm/nonmatchings/main_segment/031BA0", func_8005B974);

INCLUDE_ASM("asm/nonmatchings/main_segment/031BA0", func_8005B998);

INCLUDE_ASM("asm/nonmatchings/main_segment/031BA0", func_8005BAAC);

INCLUDE_ASM("asm/nonmatchings/main_segment/031BA0", func_8005BB24);

INCLUDE_ASM("asm/nonmatchings/main_segment/031BA0", func_8005BEA0);

INCLUDE_ASM("asm/nonmatchings/main_segment/031BA0", func_8005BF18);

INCLUDE_ASM("asm/nonmatchings/main_segment/031BA0", func_8005C4BC);

INCLUDE_ASM("asm/nonmatchings/main_segment/031BA0", func_8005C548);

INCLUDE_ASM("asm/nonmatchings/main_segment/031BA0", func_8005C90C);

INCLUDE_ASM("asm/nonmatchings/main_segment/031BA0", func_8005C998);

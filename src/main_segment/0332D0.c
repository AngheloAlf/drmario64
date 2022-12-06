#include "ultra64.h"
#include "include_asm.h"
#include "macros_defines.h"
#include "unknown_structs.h"
#include "unk.h"
#include "main_segment_functions.h"
#include "main_segment_variables.h"
#include "gcc/memory.h"

INCLUDE_RODATA("asm/nonmatchings/main_segment/0332D0", RO_800B1990);

bool func_8005CF20(s32 arg0, u32 buttonMask) {
    s32 i = 0;

    while (i < 4) {
        if ((arg0 >> i) & 1) {
            if (B_800FAF88[B_800EBD16[i]] & buttonMask) {
                break;
            }
        }
        i++;
    }
    return i < 4;
}

INCLUDE_ASM("asm/nonmatchings/main_segment/0332D0", func_8005CF78);

INCLUDE_ASM("asm/nonmatchings/main_segment/0332D0", func_8005CFD4);

INCLUDE_ASM("asm/nonmatchings/main_segment/0332D0", func_8005D09C);

INCLUDE_ASM("asm/nonmatchings/main_segment/0332D0", func_8005D0EC);

#ifdef NON_MATCHING
void func_8005D0EC(void *, void *); /* extern */

void func_8005D314(struct_800E5A70 *arg0, const char *arg1) {
    s32 temp_a1;
    s32 temp_s1;
    s32 var_s2;
    char *temp_a1_2;

    temp_s1 = func_8005B858(arg0->unk_0C + arg0->unk_14);

    var_s2 = func_8005B858(arg1);
    if (arg0->unk_10 < (temp_s1 + var_s2 + 2)) {
        var_s2 = (arg0->unk_10 - temp_s1) - 2;
    }

    memmove(arg0->unk_0C, arg0->unk_0C + arg0->unk_14, temp_s1);

    arg0->unk_18 -= arg0->unk_14;
    arg0->unk_14 = 0;
    memmove(arg0->unk_0C + temp_s1, (void *)arg1, var_s2);
    temp_a1 = temp_s1 + var_s2;
    arg0->unk_0C[temp_a1] = 0x7E;
    temp_a1_2 = temp_a1 + arg0->unk_0C;
    temp_a1_2[1] = 0x7A;
    arg0->unk_60 = 0;
    func_8005D0EC(arg0, temp_a1_2);
}
#else
INCLUDE_ASM("asm/nonmatchings/main_segment/0332D0", func_8005D314);
#endif

INCLUDE_ASM("asm/nonmatchings/main_segment/0332D0", func_8005D3F8);

INCLUDE_ASM("asm/nonmatchings/main_segment/0332D0", func_8005D428);

INCLUDE_RODATA("asm/nonmatchings/main_segment/0332D0", D_800B1A54);

INCLUDE_ASM("asm/nonmatchings/main_segment/0332D0", func_8005D78C);

INCLUDE_ASM("asm/nonmatchings/main_segment/0332D0", func_8005E0B4);

INCLUDE_ASM("asm/nonmatchings/main_segment/0332D0", func_8005E0BC);

INCLUDE_ASM("asm/nonmatchings/main_segment/0332D0", func_8005E0D0);

INCLUDE_ASM("asm/nonmatchings/main_segment/0332D0", func_8005E0D8);

INCLUDE_ASM("asm/nonmatchings/main_segment/0332D0", func_8005E0EC);

INCLUDE_ASM("asm/nonmatchings/main_segment/0332D0", func_8005E104);

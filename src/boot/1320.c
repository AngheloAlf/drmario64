#include "ultra64.h"
#include "include_asm.h"
#include "macros_defines.h"
#include "boot_functions.h"
#include "boot_variables.h"

extern UNK_TYPE D_8000E324;
extern UNK_TYPE B_800151E0[];
extern UNK_TYPE *D_8000E320;

void *func_80000720(s32 arg0) {
    D_8000E324 += arg0;

    if (D_8000E324 <= 0x4000) {
        void *var_v0 = D_8000E320;

        D_8000E320 = var_v0 + arg0;
        return var_v0;
    }

    return NULL;
}

void func_8000075C(void) {
    D_8000E324 = 0;
    D_8000E320 = B_800151E0;
}

INCLUDE_ASM("asm/nonmatchings/boot/1320", func_80000778);

#ifdef NON_MATCHING
UNK_TYPE func_80000D0C(void *arg0) {
    void *temp_a0;
    void *temp_s0;

    while (arg0 != NULL) {
        temp_a0 = arg0 - 8;
        // temp_s0 = temp_a0->unk_4;
        temp_s0 = (void *)((s32 *)temp_a0)[1];
        func_8000075C();
        arg0 = temp_s0;
    }
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/boot/1320", func_80000D0C);
#endif

INCLUDE_ASM("asm/nonmatchings/boot/1320", func_80000D48);

INCLUDE_ASM("asm/nonmatchings/boot/1320", func_80001260);

INCLUDE_ASM("asm/nonmatchings/boot/1320", func_80001480);

INCLUDE_ASM("asm/nonmatchings/boot/1320", func_80001620);

INCLUDE_ASM("asm/nonmatchings/boot/1320", func_80001D4C);

extern u32 B_8001D640;
extern u32 B_8001F998;
extern u32 B_8001F9A8;
extern u32 B_80029BE0;

s32 func_80001EB4(void) {
    s32 sp10;
    s32 ret;
    u32 var_s0 = 0;

    B_8001F990 = 0;
    B_8001D640 = 0;
    B_8001F998 = 0;
    D_8000E324 = 0;
    D_8000E320 = B_800151E0;

    while (true) {
        B_8001F9A8 = 0;
        ret = func_80001D4C(&sp10);
        if (ret != 0) {
            break;
        }

        if (var_s0 < B_8001F9A8) {
            var_s0 = B_8001F9A8;
        }

        if (sp10 != 0) {
            while (B_8001D640 >= 8) {
                B_8001D640 -= 8;
                B_80029BE0 -= 1;
            }

            func_80002300();
            ret = 0;
            break;
        }
    }

    return ret;
}

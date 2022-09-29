#include "ultra64.h"
#include "include_asm.h"
#include "gu/guint.h"


INCLUDE_ASM("asm/nonmatchings/boot_O1/E3E0", func_8000D7E0);

f64 func_8000D868(f64 arg0, f64 arg1) {
    if (arg1 == 0.0) {
        return 0.0;
    }

    return arg0 - (func_8000D7E0(arg0 / arg1) * arg1);
}

INCLUDE_ASM("asm/nonmatchings/boot_O1/E3E0", func_8000D8C4);

INCLUDE_ASM("asm/nonmatchings/boot_O1/E3E0", func_8000D940);

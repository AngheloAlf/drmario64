#include "ultra64.h"
#include "include_asm.h"
#include "boot_functions.h"


INCLUDE_ASM("asm/nonmatchings/boot_O1/E3E0", func_8000D7E0);

f64 func_8000D868(f64 arg0, f64 arg1) {
    if (arg1 == 0.0) {
        return 0.0;
    }

    return arg0 - (func_8000D7E0(arg0 / arg1) * arg1);
}

f64 func_8000D8C4(f64 arg0) {
    f64 temp_f2 = func_8000D7E0(arg0);
    s32 var_v0;
    s32 var_v1;

    var_v0 = 1;
    if (!(arg0 >= 0.0)) {
        var_v0 = 0;
    }

    var_v1 = 1;
    if (temp_f2 == arg0) {
        var_v1 = 0;
    }

    if (var_v0 & var_v1) {
        return temp_f2 + 1.0;
    } else {
        return temp_f2;
    }
}

f64 func_8000D940(f64 arg0) {
    f64 temp_f2 = func_8000D7E0(arg0);
    s32 var_v0;
    s32 var_v1;

    var_v0 = 1;
    if (!(arg0 < 0.0)) {
        var_v0 = 0;
    }
    var_v1 = 1;
    if (temp_f2 == arg0) {
        var_v1 = 0;
    }

    if (var_v0 & var_v1) {
        return temp_f2 - 1.0;
    } else {
        return temp_f2;
    }
}

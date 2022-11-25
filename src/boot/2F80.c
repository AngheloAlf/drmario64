#include "ultra64.h"
#include "include_asm.h"
#include "boot_functions.h"
#include "boot_variables.h"
#include "libc/math.h"

void *DecompressRomToRam(romoffset_t segmentRom, void *dstAddr, romoffset_t segmentSize) {
    return (void *)ALIGN8((uintptr_t)dstAddr + func_80001F90(segmentRom, dstAddr, segmentSize));
}

s32 func_800023B4(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_a1 = arg1 - arg0;
    s32 var_v0;

    var_v0 = (arg2 - arg0) % temp_a1;
    if (var_v0 < 0) {
        var_v0 += temp_a1;
    }
    return var_v0 + arg0;
}

f32 func_80002400(f32 arg0, f32 arg1, f32 arg2) {
    f32 var_f0_2;
    s32 var_v0;
    s32 var_v1;

    var_v0 = (arg0 <= arg2);
    var_v1 = (arg2 < arg1);

    if (!(var_v0 & var_v1)) {
        var_f0_2 = fmod(arg2 - arg0, arg1 - arg0);
        if (var_f0_2 < 0.0f) {
            var_f0_2 += arg1 - arg0;
        }
        arg2 = var_f0_2 + arg0;
    }
    return arg2;
}

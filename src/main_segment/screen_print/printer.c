// TODO: remove when ultralib repo has this definition
#define _MIPS_SIM_ABI64 3

#include "screen_print/printer.h"
#include "include_asm.h"
#include "macros_defines.h"

s32 Printer_8003CDA0(struct_8008E364 *arg0, ...) {
    s32 ret;
    va_list args;

    va_start(args, arg0);

    ret = arg0->unk_0->unk_0(arg0, args);

    va_end(args);

    return ret;
}

s32 Printer_8003CDD4(struct_8008E364 *arg0) {
    return arg0->unk_0->unk_4();
}

s32 Printer_8003CDF8(struct_8008E364 *arg0, char *arg1, size_t arg2) {
    return arg0->unk_0->unk_8(arg0, arg1, arg2);
}

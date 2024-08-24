// TODO: remove when ultralib repo has this definition
#define _MIPS_SIM_ABI64 3

#include "screen_print/printer.h"

#include "macros_defines.h"

s32 Printer_Open(Printer *printer, ...) {
    s32 ret;
    va_list args;

    va_start(args, printer);

    ret = printer->callbacks->open(printer, args);

    va_end(args);

    return ret;
}

s32 Printer_Close(Printer *printer) {
    return printer->callbacks->close();
}

s32 Printer_PutChars(Printer *printer, const char *chars, size_t length) {
    return printer->callbacks->putChars(printer, chars, length);
}

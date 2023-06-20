#ifndef LIBC_STDARG_H
#define LIBC_STDARG_H

#if __IS_OLD_COMP__
#include "gcc/stdarg.h"
#else
#define va_list __builtin_va_list
#define va_start __builtin_va_start
#define va_arg __builtin_va_arg
#define va_end __builtin_va_end
#endif

#endif

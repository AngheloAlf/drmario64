#ifndef LIBC_STDARG_H
#define LIBC_STDARG_H

#if defined(SPLAT) || defined(M2CTX) || defined(PERMUTER)
#define va_list char*
#define va_start(__AP, __LASTARG)
#define va_arg(__AP, __type) 0
#define va_end(__AP)
#elif __IS_OLD_COMP__
#include "gcc/stdarg.h"
#else
#define va_list __builtin_va_list
#define va_start __builtin_va_start
#define va_arg __builtin_va_arg
#define va_end __builtin_va_end
#endif

#endif

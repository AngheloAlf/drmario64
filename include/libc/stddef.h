#ifndef STDDEF_H
#define STDDEF_H

#include "version.h"

#ifndef NULL
#define NULL ((void *)0)
#endif

#ifndef _SIZE_T
    #define _SIZE_T
    #ifdef __SIZE_TYPE__
        typedef __SIZE_TYPE__ size_t;
    #else
        #if (_MIPS_SZLONG == 32)
            typedef unsigned int size_t;
        #else
            typedef unsigned long size_t;
        #endif
    #endif
#endif

#ifndef _PTRDIFF_T
    #define _PTRDIFF_T
    #ifdef __PTRDIFF_TYPE__
        typedef __PTRDIFF_TYPE__ ptrdiff_t;
    #else
        #if (_MIPS_SZLONG == 32)
            typedef int ptrdiff_t;
        #else
            typedef long ptrdiff_t;
        #endif
    #endif
#endif

#ifndef offsetof
    #if defined(__GNUC__) && !__IS_OLD_COMP__
    #define offsetof(structure, member) __builtin_offsetof (structure, member)
    #else
    #define offsetof(structure, member) ((size_t)&(((structure*)0)->member))
    #endif
#endif

#endif

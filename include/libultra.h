#ifndef LIBULTRA_H
#define LIBULTRA_H

#include "version.h"

#include "lib/ultralib/include/ultra64.h"
#include "lib/ultralib/src/audio/synthInternals.h"
#include "lib/ultralib/src/gu/guint.h"
// TODO: include different libultra headers depending on version
#if VERSION_US
//#include "lib/ultralib/include/ultra64.h"
//#include "lib/ultralib/src/audio/synthInternals.h"
#endif
#if VERSION_CN

#endif

#ifdef MODERN_GCC
#include "libc/stdint.h"

#undef OS_K0_TO_PHYSICAL
#define	OS_K0_TO_PHYSICAL(x)	(u32)((((uintptr_t)(x))-0x80000000))
#undef OS_K1_TO_PHYSICAL
#define	OS_K1_TO_PHYSICAL(x)	(u32)((((uintptr_t)(x))-0xa0000000))
#endif

#endif

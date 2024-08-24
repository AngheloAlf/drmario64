#ifndef LIBULTRA_H
#define LIBULTRA_H

#include "version.h"
#include "attributes.h"

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


// hardcoded addresses
// we manually set the DATA attribute to tell compilers building code with a
// non-zero -G value to not generate %gp_rel references to them

extern s32 osRomType DATA;
extern void *osRomBase DATA;
extern s32 osTvType DATA;
extern s32 osResetType DATA;
extern s32 osCicId DATA;
extern s32 osVersion DATA;
extern u32 osMemSize DATA;
extern u64 osClockRate DATA;
extern OSIntMask __OSGlobalIntMask DATA;


#ifdef MODERN_GCC
#include "libc/stdint.h"

#undef OS_K0_TO_PHYSICAL
#define OS_K0_TO_PHYSICAL(x) (u32)((((uintptr_t)(x))-0x80000000))
#undef OS_K1_TO_PHYSICAL
#define OS_K1_TO_PHYSICAL(x) (u32)((((uintptr_t)(x))-0xa0000000))
#endif

#endif

#ifndef BOOT_FUNCTIONS
#define BOOT_FUNCTIONS

#include "libultra.h"
#include "libc/stdint.h"
#include "unknown_structs.h"
#include "unk.h"


void Main_StopThread(void);
void func_80000488(void (*arg0)());

#ifdef M2CTX
u64 __udivdi3(u64, u64);
#endif

#endif

#ifndef STACK_H
#define STACK_H

#include "alignment.h"

#ifndef STACK_ALIGNMENT
#if VERSION_US || VERSION_GW || MODDING
#define STACK_ALIGNMENT 16
#else // VERSION_GW
#define STACK_ALIGNMENT 8
#endif
#endif

#define STACK(stack, size) \
    u64 stack[ALIGN8(size) / sizeof(u64)] ALIGNED(STACK_ALIGNMENT)

#define STACK8(stack, size) \
    u64 stack[ALIGN8(size) / sizeof(u64)] ALIGNED(8)

#define STACK_TOP(stack) \
    ((u64*)((u8*)(stack) + sizeof(stack)))

#define HEAP(heap, size) \
    u64 heap[ALIGN8(size) / sizeof(u64)] ALIGNED(16)

#endif

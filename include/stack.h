#ifndef STACK_H
#define STACK_H

#include "alignment.h"

#if VERSION_CN
#define STACK_ALIGNMENT 8
#else
#define STACK_ALIGNMENT 16
#endif

#define STACK(stack, size) \
    u64 stack[ALIGN8(size) / sizeof(u64)] ALIGNED(STACK_ALIGNMENT)

#define STACK_TOP(stack) \
    ((u64*)((u8*)(stack) + sizeof(stack)))

#define HEAP(heap, size) \
    u64 heap[ALIGN8(size) / sizeof(u64)] ALIGNED(16)

#endif

#ifndef ALIGNMENT_H
#define ALIGNMENT_H

#define ALIGN4(val) (((val) + 3) & ~3)
#define ALIGN8(val) (((val) + 7) & ~7)
#define ALIGN16(val) (((val) + 0xF) & ~0xF)
#define ALIGN32(val) (((val) + 0x1F) & ~0x1F)
#define ALIGN64(val) (((val) + 0x3F) & ~0x3F)
#define ALIGN128(val) (((val) + 0x7F) & ~0x7F)
#define ALIGN256(val) (((val) + 0xFF) & ~0xFF)

#define ALIGN_PTR(ptr) ((void*)ALIGN16((uintptr_t)(ptr)))

#ifdef __GNUC__
#define ALIGNED8 __attribute__ ((aligned (8)))
#else
#define ALIGNED8
#endif

#ifdef __sgi /* IDO compiler */
#define ALIGNOF(x) __builtin_alignof(x)
#elif (__STDC_VERSION__ >= 201112L) /* C11 */
#define ALIGNOF(x) _Alignof(x)
#else /* __GNUC__ */
#define ALIGNOF(x) __alignof__(x)
#endif

#define ALIGN_MASK(n) (~((n) - 1))

#define ALIGNOF_MASK(x) ALIGN_MASK(ALIGNOF(x))


#define STACK(stack, size) \
    u64 stack[ALIGN8(size) / sizeof(u64)]

#define STACK_TOP(stack) \
    ((u8*)(stack) + sizeof(stack))

#endif

#include "libultra.h"
#include "gcc/memory.h"
#include "libkmc/kmclib.h"

/* backward copy */

void *_memmover(REG5 void *dest, REG1 void *src, REG4 size_t n) {
    REG2 char *d;
#if FAST_SPEED /* { */
    REG3 size_t n1;

    d = (char *)dest + n;
    src = (s8 *)src + n;

    if (((s8 *)src - (s8 *)d) & BUS_ERR_ALLIGN) {
        while (n--) {
            d -= sizeof(s8);
            src -= sizeof(s8);
            *((s8 *)d) = *((s8 *)src);
        }
        return dest;
    }

    if (n == 0) {
        return dest;
    }

    if ((s32)d & sizeof(s8)) {
        d -= sizeof(s8);
        src -= sizeof(s8);
        *((s8 *)d) = *((s8 *)src); /* ALLIGN 16bit */
        n -= sizeof(s8);
    }

    if (n >= 2) {
        if ((s32)d & sizeof(s16)) {
            d -= sizeof(s16);
            src -= sizeof(s16);
            *((s16 *)d) = *(((s16 *)src)); /* ALLIGN 32bit */
            n -= sizeof(s16);
        }
    }

    n1 = n / sizeof(s32);
    while (n1--) {
        d -= sizeof(s32);
        src -= sizeof(s32);
        *((s32 *)d) = *(((s32 *)src)); /* 32bit copy */
    }

    if ((s32)n & sizeof(s16)) {
        d -= sizeof(s16);
        src -= sizeof(s16);
        *((s16 *)d) = *(((s16 *)src));
    }

    if ((s32)n & 1) {
        d -= sizeof(s8);
        src -= sizeof(s8);
        *((s8 *)d) = *((s8 *)src);
    }

#else  /* }{ */
    d = (char *)dest + n;
    src = (s8 *)src + n;
    while (n--) {
        d -= sizeof(s8);
        src -= sizeof(s8);
        *((s8 *)d) = *((s8 *)src);
    }
#endif /* } */
    return dest;
}

void *memmove(void *dest, void *src, size_t n) {
    if (dest <= src) {
        memcpy(dest, src, n);
    } else {
        _memmover(dest, src, n);
    }

    return dest;
}

void movmem(void *src, void *dest, unsigned length) {
    memmove(dest, src, length);
}

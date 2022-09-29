#include "ultra64.h"
#include "include_asm.h"
#include "libkmc/kmclib.h"

void *memset(REG5 void *dest, int ch, REG4 size_t n) {
    REG2 char *d;

#if FAST_SPEED /* { */
    REG1 u32 c;
    REG3 size_t n1;

    if (n==0) {
        return dest;
    }

    c = (ch & 0xFF);
    c |= c<<8;
    c |= c<<16;

    d = dest;
    if ((s32)d & sizeof(s8)) {
        *((s8 *)d) = (s8)c;        /* ALLIGN 16bit */
        d += sizeof(s8);
        n -= sizeof(s8);
    }

    if (n >= 2) {
        if ((int)d & sizeof(s16)) {
            *((s16 *)d) = (s16)c;        /* ALLIGN 32bit */
            d += sizeof(s16);
            n -= sizeof(s16);
        }
    }

    n1 = n / sizeof(s32);
    while (n1--) {
        *((s32 *)d) = (s32)c;        /* 32bit set */
        d += sizeof(s32);
    }

    if (n & sizeof(s16)) {
        *((s16 *)d) = (s16)c;
        d += sizeof(s16);
    }

    if (n & sizeof(s8)) {
        *(s8 *)d = (s8)c;
        d += sizeof(s8);
    }

#else /* }{ */
    d=dest;
    while(n--) {
        *(s8 *)d = ch;
        d += sizeof(s8);
    }
#endif /* } */
    return dest;
}

void setmem(void *dest, size_t n, int c) {
    memset(dest, c, n);
}

#include "ultra64.h"
#include "libkmc/kmclib.h"
#include "libc/stdbool.h"

char *strcpy(char *dest, const char *src) {
#if FAST_SPEED
    char *d = dest;
    u32 data;

    if ((src - d) & BUS_ERR_ALLIGN) {
        while ((*d++ = *src++) != '\0') {
            ;
        }
        return dest;
    }

    while ((int)d & 3) { /* ALLIGN 32bit */
        if ((*(d)++ = *(src)++) == '\0') {
            return dest;
        }
    }

    while (true) {
        data = *((s32 *)src); /* 32bit copy */
        src += sizeof(s32);
        if ((data & 0xFF000000) == 0) {
            *d = 0;
            return dest;
        }
        if ((data & 0xFF0000) == 0) {
            *(s16 *)d = data >> 16;
            return dest;
        }
        if ((data & 0xFF00) == 0) {
            *((s16 *)d) = data >> 16;
            d += sizeof(s16);
            *d = '\0';
            return dest;
        }

        *((s32 *)d) = data;
        d += sizeof(s32);

        if ((data & 0xff) == 0) {
            return dest;
        }
    }
#else
    char *d = dest;

    while ((*(d)++ = *(src)++) != '\0') {
        ;
    }

    return dest;
#endif
}
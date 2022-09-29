#include "ultra64.h"
#include "include_asm.h"
#include "gcc/memory.h"
#include "libkmc/kmclib.h"

// TODO: try to match this function with C compliant code

/* backward copy */
void *_memmover(REG5 char *dest, REG1 char *src, REG4 size_t n) {
    REG2 char *d;
#if FAST_SPEED /* { */
    REG3 size_t n1;

    d=(char *)dest+n;
    (char *)src +=n;
    if (((char *)src - (char *)d)&BUS_ERR_ALLIGN) {
	while(n--) {
            *(--((BYTE *)d)) = *(--((BYTE *)src));
        }
	return dest;
    }

    if (n==0) return dest;
    if ((int)d&1) {
    	*(--(BYTE *)d) = *(--(BYTE *)src);	/* ALLIGN 16bit */
        --n;
    }
    if (n>=2) {
	if ((int)d&2) {
	    *(--(WORD *)d) = *(--((WORD *)src));		/* ALLIGN 32bit */
	    n -= 2;
	}
    }
    n1 = n>>2;
    while(n1--) {
        *--((DWORD *)d) = *--((DWORD *)src);		/* 32bit copy */
    }
    if ((int)n&2) *--((WORD *)d) = *--((WORD *)src);
    if ((int)n&1) *--(BYTE *)d = *--(BYTE *)src;
#else /* }{ */
    d=(char *)dest+n;
    (char *)src += n;
    while(n--) {
        *--((BYTE *)d) = *--((BYTE *)src);
    }
#endif /* } */
    return dest;
}

//void *_memmover(void *dest, void *src, size_t n);

void *memmove(void *dest, void *src, size_t n) {
    if (dest <= src) {
        memcpy(dest, src, n);
    } else {
        _memmover(dest, src, n);
    }

    return dest;
}

void movmem(void *src, void * dest, unsigned length) {
    memmove(dest, src, length);
}

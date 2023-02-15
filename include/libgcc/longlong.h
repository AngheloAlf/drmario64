#ifndef LIBGCC_LONGLONG_H
#define LIBGCC_LONGLONG_H

#include "mips.h"

#define BITS_PER_UNIT 8

#define __BITS4 (SI_TYPE_SIZE / 4)
#define __ll_B (1L << (SI_TYPE_SIZE / 2))
#define __ll_lowpart(t) ((USItype)(t) % __ll_B)
#define __ll_highpart(t) ((USItype)(t) / __ll_B)

typedef unsigned int UQItype __attribute__((mode(QI)));
typedef int SItype __attribute__((mode(SI)));
typedef unsigned int USItype __attribute__((mode(SI)));
typedef int DItype __attribute__((mode(DI)));
typedef unsigned int UDItype __attribute__((mode(DI)));

typedef float SFtype __attribute__((mode(SF)));
typedef float DFtype __attribute__((mode(DF)));

#if LONG_DOUBLE_TYPE_SIZE == 96
typedef float XFtype __attribute__((mode(XF)));
#endif
#if LONG_DOUBLE_TYPE_SIZE == 128
typedef float TFtype __attribute__((mode(TF)));
#endif

typedef int word_type __attribute__((mode(__word__)));

#define SI_TYPE_SIZE (sizeof(SItype) * BITS_PER_UNIT)

/* DIstructs are pairs of SItype values in the order determined by
   LIBGCC2_WORDS_BIG_ENDIAN.  */

#if LIBGCC2_WORDS_BIG_ENDIAN
struct DIstruct {
    SItype high, low;
};
#else
struct DIstruct {
    SItype low, high;
};
#endif

/* We need this union to unpack/pack DImode values, since we don't have
   any arithmetic yet.  Incoming DImode parameters are stored into the
   `ll' field, and the unpacked result is read from the struct `s'.  */

typedef union {
    struct DIstruct s;
    DItype ll;
} DIunion;

/* Define auxiliary asm macros.

   1) umul_ppmm(high_prod, low_prod, multipler, multiplicand)
   multiplies two USItype integers MULTIPLER and MULTIPLICAND,
   and generates a two-part USItype product in HIGH_PROD and
   LOW_PROD.

   2) __umulsidi3(a,b) multiplies two USItype integers A and B,
   and returns a UDItype product.  This is just a variant of umul_ppmm.

   3) udiv_qrnnd(quotient, remainder, high_numerator, low_numerator,
   denominator) divides a two-word unsigned integer, composed by the
   integers HIGH_NUMERATOR and LOW_NUMERATOR, by DENOMINATOR and
   places the quotient in QUOTIENT and the remainder in REMAINDER.
   HIGH_NUMERATOR must be less than DENOMINATOR for correct operation.
   If, in addition, the most significant bit of DENOMINATOR must be 1,
   then the pre-processor symbol UDIV_NEEDS_NORMALIZATION is defined to 1.

   4) sdiv_qrnnd(quotient, remainder, high_numerator, low_numerator,
   denominator).  Like udiv_qrnnd but the numbers are signed.  The
   quotient is rounded towards 0.

   5) count_leading_zeros(count, x) counts the number of zero-bits from
   the msb to the first non-zero bit.  This is the number of steps X
   needs to be shifted left to set the msb.  Undefined for X == 0.

   6) add_ssaaaa(high_sum, low_sum, high_addend_1, low_addend_1,
   high_addend_2, low_addend_2) adds two two-word unsigned integers,
   composed by HIGH_ADDEND_1 and LOW_ADDEND_1, and HIGH_ADDEND_2 and
   LOW_ADDEND_2 respectively.  The result is placed in HIGH_SUM and
   LOW_SUM.  Overflow (i.e. carry out) is not stored anywhere, and is
   lost.

   7) sub_ddmmss(high_difference, low_difference, high_minuend,
   low_minuend, high_subtrahend, low_subtrahend) subtracts two
   two-word unsigned integers, composed by HIGH_MINUEND_1 and
   LOW_MINUEND_1, and HIGH_SUBTRAHEND_2 and LOW_SUBTRAHEND_2
   respectively.  The result is placed in HIGH_DIFFERENCE and
   LOW_DIFFERENCE.  Overflow (i.e. carry out) is not stored anywhere,
   and is lost.

   If any of these macros are left undefined for a particular CPU,
   C macros are used.  */

#if defined(__GNUC__) && !defined(NO_ASM)

#if defined(__mips__)
#ifndef umul_ppmm
#define umul_ppmm(w1, w0, u, v) \
    __asm__("multu %2,%3" : "=l"((USItype)(w0)), "=h"((USItype)(w1)) : "d"((USItype)(u)), "d"((USItype)(v)))
#define UMUL_TIME 10
#define UDIV_TIME 100
#endif
#endif /* __mips__ */

#endif /* __GNUC__ */

/* If this machine has no inline assembler, use C macros.  */

#if !defined(add_ssaaaa)
#define add_ssaaaa(sh, sl, ah, al, bh, bl) \
    do {                                   \
        USItype __x;                       \
        __x = (al) + (bl);                 \
        (sh) = (ah) + (bh) + (__x < (al)); \
        (sl) = __x;                        \
    } while (0)
#endif

#if !defined(sub_ddmmss)
#define sub_ddmmss(sh, sl, ah, al, bh, bl) \
    do {                                   \
        USItype __x;                       \
        __x = (al) - (bl);                 \
        (sh) = (ah) - (bh) - (__x > (al)); \
        (sl) = __x;                        \
    } while (0)
#endif

#if !defined(umul_ppmm)
#define umul_ppmm(w1, w0, u, v)                                           \
    do {                                                                  \
        USItype __x0, __x1, __x2, __x3;                                   \
        USItype __ul, __vl, __uh, __vh;                                   \
                                                                          \
        __ul = __ll_lowpart(u);                                           \
        __uh = __ll_highpart(u);                                          \
        __vl = __ll_lowpart(v);                                           \
        __vh = __ll_highpart(v);                                          \
                                                                          \
        __x0 = (USItype)__ul * __vl;                                      \
        __x1 = (USItype)__ul * __vh;                                      \
        __x2 = (USItype)__uh * __vl;                                      \
        __x3 = (USItype)__uh * __vh;                                      \
                                                                          \
        __x1 += __ll_highpart(__x0); /* this can't give carry */          \
        __x1 += __x2;                /* but this indeed can */            \
        if (__x1 < __x2)             /* did we get it? */                 \
            __x3 += __ll_B;          /* yes, add it in the proper pos. */ \
                                                                          \
        (w1) = __x3 + __ll_highpart(__x1);                                \
        (w0) = __ll_lowpart(__x1) * __ll_B + __ll_lowpart(__x0);          \
    } while (0)
#endif

#if !defined(__umulsidi3)
#define __umulsidi3(u, v)                       \
    ({                                          \
        DIunion __w;                            \
        umul_ppmm(__w.s.high, __w.s.low, u, v); \
        __w.ll;                                 \
    })
#endif

/* Define this unconditionally, so it can be used for debugging.  */
#define __udiv_qrnnd_c(q, r, n1, n0, d)                                         \
    do {                                                                        \
        USItype __d1, __d0, __q1, __q0;                                         \
        USItype __r1, __r0, __m;                                                \
        __d1 = __ll_highpart(d);                                                \
        __d0 = __ll_lowpart(d);                                                 \
                                                                                \
        __r1 = (n1) % __d1;                                                     \
        __q1 = (n1) / __d1;                                                     \
        __m = (USItype)__q1 * __d0;                                             \
        __r1 = __r1 * __ll_B | __ll_highpart(n0);                               \
        if (__r1 < __m) {                                                       \
            __q1--, __r1 += (d);                                                \
            if (__r1 >= (d)) /* i.e. we didn't get carry when adding to __r1 */ \
                if (__r1 < __m)                                                 \
                    __q1--, __r1 += (d);                                        \
        }                                                                       \
        __r1 -= __m;                                                            \
                                                                                \
        __r0 = __r1 % __d1;                                                     \
        __q0 = __r1 / __d1;                                                     \
        __m = (USItype)__q0 * __d0;                                             \
        __r0 = __r0 * __ll_B | __ll_lowpart(n0);                                \
        if (__r0 < __m) {                                                       \
            __q0--, __r0 += (d);                                                \
            if (__r0 >= (d))                                                    \
                if (__r0 < __m)                                                 \
                    __q0--, __r0 += (d);                                        \
        }                                                                       \
        __r0 -= __m;                                                            \
                                                                                \
        (q) = (USItype)__q1 * __ll_B | __q0;                                    \
        (r) = __r0;                                                             \
    } while (0)

/* If the processor has no udiv_qrnnd but sdiv_qrnnd, go through
   __udiv_w_sdiv (defined in libgcc or elsewhere).  */
#if !defined(udiv_qrnnd) && defined(sdiv_qrnnd)
#define udiv_qrnnd(q, r, nh, nl, d)           \
    do {                                      \
        USItype __r;                          \
        (q) = __udiv_w_sdiv(&__r, nh, nl, d); \
        (r) = __r;                            \
    } while (0)
#endif

/* If udiv_qrnnd was not defined for this processor, use __udiv_qrnnd_c.  */
#if !defined(udiv_qrnnd)
#define UDIV_NEEDS_NORMALIZATION 1
#define udiv_qrnnd __udiv_qrnnd_c
#endif

#if !defined(count_leading_zeros)
extern const UQItype __clz_tab[];
#define count_leading_zeros(count, x)                                                     \
    do {                                                                                  \
        USItype __xr = (x);                                                               \
        USItype __a;                                                                      \
                                                                                          \
        if (SI_TYPE_SIZE <= 32) {                                                         \
            __a = __xr < ((USItype)1 << 2 * __BITS4)                                      \
                      ? (__xr < ((USItype)1 << __BITS4) ? 0 : __BITS4)                    \
                      : (__xr < ((USItype)1 << 3 * __BITS4) ? 2 * __BITS4 : 3 * __BITS4); \
        } else {                                                                          \
            for (__a = SI_TYPE_SIZE - 8; __a > 0; __a -= 8)                               \
                if (((__xr >> __a) & 0xff) != 0)                                          \
                    break;                                                                \
        }                                                                                 \
                                                                                          \
        (count) = SI_TYPE_SIZE - (__clz_tab[__xr >> __a] + __a);                          \
    } while (0)
#endif

#ifndef UDIV_NEEDS_NORMALIZATION
#define UDIV_NEEDS_NORMALIZATION 0
#endif

#endif

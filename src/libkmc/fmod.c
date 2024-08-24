#include "libultra.h"

#include "libc/math.h"
#include "libkmc/explog.h"

/**
 * convert to an integer
 */
f64 __fint(f64 x) {
    DFLOAT d;
    s32 exp;

    d.df = x;
    exp = ((d.ui[EXP_INDEX] >> 20) & 0x7FF) - 0x3FF; /* get exp */

    if (exp < 0) {
        return 0.0; /* x<1 */
    }

    d.ull &= ((long long)0x8000000000000000LL) >> (exp + 11);
    return d.df;
}

/**
 * x % y
 */
f64 fmod(f64 x, f64 y) {
    f64 i;

    if (y == 0.0) {
        return 0.0;
    }

    i = __fint(x / y);
    return x - (i * y);
}

f64 ceil(f64 x) {
    f64 i = __fint(x);

    if ((x >= 0.0) && (i != x)) {
        return i + 1.0;
    }

    return i;
}

f64 floor(f64 x) {
    f64 i = __fint(x);

    if ((x < 0.0) && (i != x)) {
        return i - 1.0;
    }

    return i;
}

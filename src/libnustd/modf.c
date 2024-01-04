#include "libc/math.h"

f64 modf(f64 x, f64 *ipart) {
    s32 temp = x;

    *ipart = temp;
    return x - *ipart;
}

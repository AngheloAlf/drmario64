#include "libc/math.h"

f64 fmod(f64 x, f64 y) {
    s32 temp;

    if (y == 0.0) {
        return 0.0;
    }

    temp = (x / y);
    return x - (temp * y);
}

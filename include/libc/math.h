#ifndef MATH_H
#define MATH_H

#include "ultra64.h"

f64 __fint(f64 arg0);
f64 fmod(f64 arg0, f64 arg1);
f64 ceil(f64 arg0);
f64 floor(f64 arg0);

f64 modf(f64 x, f64 *ipart);

#endif

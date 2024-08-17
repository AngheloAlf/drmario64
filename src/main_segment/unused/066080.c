#include "066080.h"

void func_8007E260(f32 arg0[3], f32 arg1[3], f32 arg2[3]) {
    f32 sp8[3];

    sp8[0] = (arg1[1] * arg2[2]) - (arg1[2] * arg2[1]);
    sp8[1] = (arg1[2] * arg2[0]) - (arg1[0] * arg2[2]);
    sp8[2] = (arg1[0] * arg2[1]) - (arg1[1] * arg2[0]);
    arg0[0] = sp8[0];
    arg0[1] = sp8[1];
    arg0[2] = sp8[2];
}

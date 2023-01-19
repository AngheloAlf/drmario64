#include "libultra.h"
#include "include_asm.h"
#include "libkmc/explog.h"

f64 modf(f64 x, f64 *ipart) {
    s32 exp;
    s32 msk_byte;
    DFLOAT *ip = (DFLOAT *)ipart;

    ip->df = x;
    exp = ((ip->ui[EXP_INDEX] >> 20) & 0x7FF) - 0x3FF;

    if (exp < 0) {
        ip->df = 0;
        return x;
    } else if (exp >= 52) {
        ip->df = x;
        return 0.0;
    } else {
        exp += 12;
        msk_byte = (exp >> 3);
        ip->ub[msk_byte] &= 0xFF << (8 - (exp & 0x7));

        while (msk_byte < 7) {
            ip->ub[++msk_byte] = 0;
        }

        return x - ip->df;
    }
}

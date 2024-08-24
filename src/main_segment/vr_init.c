/**
 * Original filename: vr_init.c
 */

#include "vr_init.h"

#include "macros_defines.h"

/**
 * Original name: mt
 */
static u32 mt[0x270];

/**
 * Original name: mti
 */
s32 mti = ARRAY_COUNT(mt) + 1;

/**
 * Original name: static mag01
 */
s32 mag01_108[] = {
    0x00000000,
    0x9908B0DF,
};

/**
 * Original name: sgenrand
 */
void sgenrand(u32 arg0) {
    mt[0] = arg0;

    for (mti = 1; mti < ARRAY_COUNT(mt); mti++) {
        mt[mti] = mt[mti - 1] * 69069;
    }
}

/**
 * Original name: genrand
 */
u16 genrand(u16 arg0) {
    u32 s4 = arg0;
    u32 temp_t0;

    do {
        s32 var_a3;
        u32 var_a2;

        if (mti >= ARRAY_COUNT(mt)) {
            s32 var_t1;

            if (mti == ARRAY_COUNT(mt) + 1) {
                sgenrand(0x1105);
            }

            for (var_t1 = 0; var_t1 < 0xE3; var_t1++) {
                temp_t0 = ((mt[var_t1] & 0x80000000) | (mt[var_t1 + 1] & 0x7FFFFFFF));
                mt[var_t1] = mt[var_t1 + 1 + 0x18C] ^ (temp_t0 >> 1) ^ mag01_108[temp_t0 & 1];
            }

            for (; var_t1 < ARRAY_COUNT(mt) - 1; var_t1++) {
                temp_t0 = (mt[var_t1] & 0x80000000) | (mt[var_t1 + 1] & 0x7FFFFFFF);
                mt[var_t1] = mt[var_t1 + 1 - 0xE4] ^ (temp_t0 >> 1) ^ mag01_108[temp_t0 & 1];
            }

            temp_t0 = (mt[ARRAY_COUNT(mt) - 1] & 0x80000000) | (mt[0] & 0x7FFFFFFF);
            mt[ARRAY_COUNT(mt) - 1] = mt[0x18C] ^ (temp_t0 >> 1) ^ mag01_108[temp_t0 & 1];
            mti = 0;
        }

        temp_t0 = mt[mti++];
        temp_t0 ^= (temp_t0 >> 0xB);
        temp_t0 ^= ((temp_t0 << 7) & 0x9D2C5680);
        temp_t0 ^= ((temp_t0 << 0xF) & 0xEFC60000);
        temp_t0 ^= (temp_t0 >> 0x12);

        var_a2 = s4;

        var_a3 = 0;
        do {
            var_a2 >>= 1;
            var_a3++;
        } while (var_a2 != 0);

        while (var_a3 != 0) {
            var_a2 <<= 1;
            var_a2++;
            var_a3--;
        }

        temp_t0 &= var_a2;
    } while (temp_t0 >= s4);

    return temp_t0;
}

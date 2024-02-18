#include "066580.h"

#include "include_asm.h"
#include "macros_defines.h"
#include "unknown_structs.h"
#include "main_segment_variables.h"
#include "nnsched.h"

extern u16 D_800AB170[];
extern u8 D_800AB1B4[];
extern u8 D_800AB1D4[];
extern s32 D_800AB1EC[];
extern u32 D_800AB1FC[];
extern u32 D_800AB20C[];
extern u32 D_800AB21C[];
extern u32 D_800AB29C[];

u8 *func_8007E760(char *dst, u8 arg1, u8 arg2, u8 arg3, u32 arg4, u16 arg5, u8 arg6[4]) {
    s32 temp_t0;
    u8 temp_t1;
    u8 temp_t6_2;
    s32 var_s2;
    u32 var_t8;
    u32 var_t5;
    u32 var_t4;
    s32 temp_t9;
    u8 *var_s1;
    u16 *temp;
    u16 *temp2;

    temp_t1 = framecont & 0x1F;
    temp_t6_2 = (framecont >> 5) & 0x1F;

    temp_t0 = arg1 + arg2 + arg3;
    temp_t0 += arg4 & 0x3FF;
    temp_t0 += (arg4 >> 0xA) & 0x3FF;
    temp_t0 += arg5 & 0xFF;
    temp_t0 += arg5 >> 8;
    temp_t0 += arg6[0] + arg6[1] + arg6[2] + arg6[3];
    temp_t0 &= 0x3FF;

    var_t8 = temp_t0 & 3;
    var_t8 <<= 0x14;
    var_t8 |= arg4 & 0xFFFFF;
    var_t8 <<= 8;
    var_t8 |= arg6[0];

    var_t5 = arg6[3];
    var_t5 <<= 8;
    var_t5 |= arg6[2];
    var_t5 <<= 8;
    var_t5 |= arg6[1];
    var_t5 <<= 6;
    var_t5 |= arg2 & 0x3F;

    var_t4 = temp_t0;
    var_t4 &= 0x3FC;
    var_t4 |= arg3 & 3;
    var_t4 <<= 2;
    var_t4 |= arg1 & 3;
    var_t4 <<= 2;
    var_t4 |= arg2 >> 6;
    var_t4 <<= 0x10;
    var_t4 |= arg5;

    var_t8 ^= D_800AB1EC[temp_t0 & 3];
    var_t5 ^= D_800AB1FC[temp_t0 & 3];
    var_t4 ^= D_800AB20C[temp_t0 & 3];

    var_t8 ^= D_800AB21C[temp_t1];
    var_t5 ^= D_800AB21C[temp_t1];
    var_t4 ^= D_800AB21C[temp_t1];

    var_t8 ^= D_800AB29C[temp_t6_2];
    var_t5 ^= D_800AB29C[temp_t6_2];
    var_t4 ^= D_800AB29C[temp_t6_2];

    temp = D_800AB170;
    temp2 = (u16*)dst;
    var_s1 = D_800AB1D4;

    temp_t9 = temp_t1;
    *temp2++ = temp[temp_t9];
    *var_s1++ = D_800AB1B4[temp_t9];

    for (var_s2 = 0; var_s2 < 6; var_s2++) {
        temp_t9 = var_t8 & 0x1F;
        var_t8 >>= 5;
        *temp2++ = temp[temp_t9];
        *var_s1++ = D_800AB1B4[temp_t9];
    }

    for (var_s2 = 0; var_s2 < 6; var_s2++) {
        temp_t9 = var_t5 & 0x1F;
        var_t5 >>= 5;
        *temp2++ = temp[temp_t9];
        *var_s1++ = D_800AB1B4[temp_t9];
    }

    for (var_s2 = 0; var_s2 < 6; var_s2++) {
        temp_t9 = var_t4 & 0x1F;
        var_t4 >>= 5;
        *temp2++ = temp[temp_t9];
        *var_s1++ = D_800AB1B4[temp_t9];
    }

    temp_t9 = temp_t6_2;
    *temp2++ = temp[temp_t9];
    *var_s1++ = D_800AB1B4[temp_t9];

    return D_800AB1D4;
}

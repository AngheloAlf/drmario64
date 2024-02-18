#include "066580.h"

#include "include_asm.h"
#include "macros_defines.h"
#include "unknown_structs.h"
#include "main_segment_variables.h"
#include "nnsched.h"

#if VERSION_US
#if 0
extern u16 D_800AB170[];
extern u8 D_800AB1B4[];
extern u8 D_800AB1D4;
extern s32 D_800AB1EC[];
extern s32 D_800AB1FC[];
extern s32 D_800AB20C[];
extern s32 D_800AB21C[];
extern s32 D_800AB29C[];

u8 *func_8007E760(char *dst, u8 arg1, u8 arg2, u8 arg3, s32 arg4, u16 arg5, u8 *arg6) {
    s32 temp_a0;
    s32 temp_a0_3;
    s32 temp_s3;
    s32 temp_t8;
    s32 temp_t8_2;
    s32 temp_t8_3;
    s32 temp_t8_4;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 var_s1;
    s32 var_s1_2;
    s32 var_s1_3;
    s8 *var_t9;
    u16 temp_v0;
    u16 temp_v0_2;
    u16 temp_v0_3;
    u32 temp_t1;
    u32 var_t0;
    u32 var_t2;
    u32 var_t7;
    u8 *var_s0;
    u8 temp_a0_2;
    u8 temp_t2;
    u8 temp_t3;
    u8 temp_t4;

    var_s1 = 0;
    temp_s3 = ((u32) framecont >> 5) & 0x1F;
    temp_t1 = (s32) arg5 & 0xFFFF;
    temp_a0 = framecont & 0x1F;
    temp_t2 = arg6[0];
    temp_t4 = arg6[1];
    temp_t3 = arg6[2];
    temp_a0_2 = arg6[3];
    temp_v1 = ((arg1 & 0xFF) + arg2 + (arg3 & 0xFF) + (arg4 & 0x3FF) + (((u32) arg4 >> 0xA) & 0x3FF) + ((s32) arg5 & 0xFF) + (temp_t1 >> 8) + (temp_t2 + temp_t4 + temp_t3 + temp_a0_2)) & 0x3FF;
    temp_v1_2 = temp_v1 & 3;
    temp_v1_3 = D_800AB21C[temp_a0];
    temp_a0_3 = D_800AB29C[temp_s3];
    *dst = (u16) D_800AB170[temp_a0];
    var_t9 = dst + 2;
    var_t7 = (((((temp_v1 & 3) << 0x14) | (arg4 & 0xFFFFF)) << 8) | temp_t2) ^ D_800AB1EC[temp_v1_2] ^ temp_v1_3 ^ temp_a0_3;
    var_t2 = ((((((temp_a0_2 << 8) | temp_t3) << 8) | temp_t4) << 6) | (arg2 & 0x3F)) ^ D_800AB1FC[temp_v1_2] ^ temp_v1_3 ^ temp_a0_3;
    var_t0 = ((((((((temp_v1 & 0x3FC) | (arg3 & 3)) * 4) | (arg1 & 3)) * 4) | (arg2 >> 6)) << 0x10) | temp_t1) ^ D_800AB20C[temp_v1_2] ^ temp_v1_3 ^ temp_a0_3;
    D_800AB1D4 = D_800AB1B4[temp_a0];
    var_s0 = &D_800AB1D4 + 1;
    do {
        temp_t8 = var_t7 & 0x1F;
        temp_v0 = D_800AB170[temp_t8];
        var_t7 = var_t7 >> 5;
        *var_t9 = temp_v0;
        var_s1 += 1;
        var_t9 += 2;
        *var_s0 = D_800AB1B4[temp_t8];
        var_s0 += 1;
    } while (var_s1 < 6);
    var_s1_2 = 0;
    do {
        temp_t8_2 = var_t2 & 0x1F;
        temp_v0_2 = D_800AB170[temp_t8_2];
        var_t2 = var_t2 >> 5;
        *var_t9 = temp_v0_2;
        var_s1_2 += 1;
        var_t9 += 2;
        *var_s0 = D_800AB1B4[temp_t8_2];
        var_s0 += 1;
    } while (var_s1_2 < 6);
    var_s1_3 = 0;
    do {
        temp_t8_3 = var_t0 & 0x1F;
        temp_v0_3 = D_800AB170[temp_t8_3];
        var_t0 = var_t0 >> 5;
        *var_t9 = temp_v0_3;
        var_s1_3 += 1;
        var_t9 += 2;
        *var_s0 = D_800AB1B4[temp_t8_3];
        var_s0 += 1;
    } while (var_s1_3 < 6);
    temp_t8_4 = temp_s3 & 0xFF;
    *var_t9 = (u16) D_800AB170[temp_t8_4];
    *var_s0 = D_800AB1B4[temp_t8_4];
    return &D_800AB1D4;
}
#else
INCLUDE_ASM("asm/us/nonmatchings/main_segment/066580", func_8007E760);
#endif
#endif

#if VERSION_CN
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

    var_t4 = temp_t0 & 0x3FC;
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
#endif

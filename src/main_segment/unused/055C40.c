#include "libultra.h"
#include "include_asm.h"
#include "macros_defines.h"
#include "unknown_structs.h"
#include "unk.h"

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/unused/055C40", func_8007F890);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/unused/055C40", func_8007F890);
#endif

#if VERSION_CN
#ifdef NON_EQUIVALENT
void func_8007F890(s32 *arg0, u32 *arg1) {
    u32 val = 0x10001;
    s32 temp_t5_2;
    s32 temp_t6;
    s32 temp_t7;
    s32 var_a2;
    s32 var_t2;
    s32 var_t3;
    s32 var_t4;
    s32 var_v0;
    s32 var_v1;
    u32 temp_t5;
    u32 var_a3;

    for (var_v0 = 0xF0; var_v0 != 0; var_v0--) {
        var_a2 = 1;
        var_t2 = 0;
        var_t3 = 0;
        var_t4 = 0;

        for (var_v1 = 0xA0; var_v1 != 0; var_v1--) {
            var_a3 = *arg1;
            arg1 += 1;
            temp_t5 = var_a3 >> 0x10;
            temp_t5_2 = temp_t5 & 0x3E;
            temp_t6 = (var_a3 >> 0x16) & 0x1F;
            temp_t7 = (var_a3 >> 0x1B) & 0x1F;
            if ((temp_t5 & 1) != var_a2) {
                var_a2 ^= 1;
                var_a3 = (var_a3 & 0xFFFF) |
                         ((((u32)(var_t4 + temp_t7) >> 1) << 0x1B) | (((u32)(var_t3 + temp_t6) >> 1) << 0x16) |
                          (((u32)(var_t2 + temp_t5_2) >> 1) << 0x10));
            }
            var_t2 = var_a3 & 0x3E;
            var_t3 = (var_a3 >> 6) & 0x1F;
            var_t4 = (var_a3 >> 0xB) & 0x1F;
            if ((var_a3 & 1) != var_a2) {
                var_a2 ^= 1;
                var_a3 =
                    (var_a3 & 0xFFFF0000) | ((((u32)(temp_t7 + var_t4) >> 1) << 0xB) |
                                             ((u32)(temp_t5_2 + var_t2) >> 1) | (((u32)(temp_t6 + var_t3) >> 1) << 6));
            }
            *arg0 = var_a3 | val;
            arg0 += 1;
        }

        arg0 += 4;
    }
}
#else
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/unused/055C40", func_8007F890);
#endif
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/unused/055C40", func_8007F990);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/unused/055C40", func_8007F990);
#endif

#if VERSION_CN
#ifdef NON_MATCHING
void func_8007F990(u32 *arg0, u32 *arg1) {
    u32 val = 0x10001;
    s32 var_t8;
    s32 var_t9;

    for (var_t8 = 0xF0; var_t8 != 0; var_t8--) {
        for (var_t9 = 0xA0; var_t9 != 0; var_t9--) {
            *arg0 = *arg1 | val;
            arg1 += 1;
            arg0 += 1;
        }

        arg0 += 4;
    }
}
#else
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/unused/055C40", func_8007F990);
#endif
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/unused/055C40", func_8007F9D0);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/unused/055C40", func_8007F9D0);
#endif

#if VERSION_CN
#ifdef NON_MATCHING
void func_8007F9D0(u32 *arg0, u32 *arg1) {
    u32 val = 0x10001;
    s32 var_t8;

    for (var_t8 = 0x9600; var_t8 != 0; var_t8--) {
        *arg0++ = *arg1++ | val;
    }
}
#else
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/unused/055C40", func_8007F9D0);
#endif
#endif

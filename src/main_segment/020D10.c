#include "020D10.h"

#include "include_asm.h"
#include "macros_defines.h"
#include "unknown_structs.h"
#include "main_segment_variables.h"

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/020D10", RO_800ACFB0);
#endif

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/020D10", RO_800ACFC8);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/020D10", func_80038EF0);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/020D10", func_8003901C);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/020D10", func_800393DC);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/020D10", func_800394A0);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/020D10", func_8003974C);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/020D10", func_80039BE0);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/020D10", func_80039D08);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/020D10", func_80039E14);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/020D10", func_80039F74);
#endif

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/020D10", RO_800AD080);
#endif

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/020D10", RO_800AD098);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/020D10", func_8003A1B4);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/020D10", func_8003A26C);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/020D10", func_8003A618);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/020D10", func_8003A7E4);
#endif

#if VERSION_US
void *func_8003A89C(void *arg0, s32 arg1) {
    D_8008CFE0 = arg1;

    switch (D_8008CFE0) {
        case 0x1:
            arg0 = func_80039E14(arg0);
            break;

        case 0x2:
            arg0 = func_8003A26C(arg0);
            break;
    }
    return arg0;
}
#endif

#if VERSION_US
s32 func_8003A8F4(void) {
    s32 var_v1 = 0;

    switch (D_8008CFE0) {
        case 0x1:
            var_v1 = func_80039F74();
            break;

        case 0x2:
            var_v1 = func_8003A618();
            break;
    }
    return var_v1;
}
#endif

#if VERSION_US
void func_8003A950(Gfx **gfxP) {
    switch (D_8008CFE0) {
        case 0x1:
            func_8003A1B4(gfxP);
            break;

        case 0x2:
            func_8003A7E4(gfxP);
            break;
    }
}
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/020D10_cn", func_8003BB50_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/020D10_cn", func_8003BCD8_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/020D10_cn", func_8003C0A4_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/020D10_cn", func_8003C168_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/020D10_cn", func_8003C414_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/020D10_cn", func_8003C978_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/020D10_cn", func_8003CAAC_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/020D10_cn", func_8003CC74_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/020D10_cn", func_8003CE2C_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/020D10_cn", func_8003D098_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/020D10_cn", func_8003D154_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/020D10_cn", func_8003D548_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/020D10_cn", func_8003D718_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/020D10_cn", func_8003D7D4_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/020D10_cn", func_8003D840_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/020D10_cn", func_8003D8B0_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/020D10_cn", RO_800C4080_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/020D10_cn", RO_800C4098_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/020D10_cn", RO_800C4150_cn);
#endif

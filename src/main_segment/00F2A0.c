#include "ultra64.h"
#include "include_asm.h"
#include "macros_defines.h"
#include "unknown_structs.h"
#include "main_segment_functions.h"
#include "main_segment_variables.h"

INCLUDE_RODATA("asm/nonmatchings/main_segment/00F2A0", D_800ACFB0);

INCLUDE_RODATA("asm/nonmatchings/main_segment/00F2A0", D_800ACFC8);

INCLUDE_ASM("asm/nonmatchings/main_segment/00F2A0", func_80038EF0);

INCLUDE_ASM("asm/nonmatchings/main_segment/00F2A0", func_8003901C);

INCLUDE_ASM("asm/nonmatchings/main_segment/00F2A0", func_800393DC);

INCLUDE_ASM("asm/nonmatchings/main_segment/00F2A0", func_800394A0);

INCLUDE_ASM("asm/nonmatchings/main_segment/00F2A0", func_8003974C);

INCLUDE_ASM("asm/nonmatchings/main_segment/00F2A0", func_80039BE0);

INCLUDE_ASM("asm/nonmatchings/main_segment/00F2A0", func_80039D08);

INCLUDE_ASM("asm/nonmatchings/main_segment/00F2A0", func_80039E14);

INCLUDE_ASM("asm/nonmatchings/main_segment/00F2A0", func_80039F74);

INCLUDE_RODATA("asm/nonmatchings/main_segment/00F2A0", RO_800AD080);

INCLUDE_RODATA("asm/nonmatchings/main_segment/00F2A0", D_800AD098);

INCLUDE_ASM("asm/nonmatchings/main_segment/00F2A0", func_8003A1B4);

INCLUDE_ASM("asm/nonmatchings/main_segment/00F2A0", func_8003A26C);

INCLUDE_ASM("asm/nonmatchings/main_segment/00F2A0", func_8003A618);

INCLUDE_ASM("asm/nonmatchings/main_segment/00F2A0", func_8003A7E4);

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

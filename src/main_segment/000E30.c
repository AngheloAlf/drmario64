#include "ultra64.h"
#include "libc/stdbool.h"
#include "include_asm.h"
#include "unk.h"
#include "macros_defines.h"
#include "main_segment_functions.h"
#include "main_segment_variables.h"


INCLUDE_ASM("asm/nonmatchings/main_segment/000E30", func_8002AA80);

INCLUDE_ASM("asm/nonmatchings/main_segment/000E30", func_8002AAD8);

INCLUDE_ASM("asm/nonmatchings/main_segment/000E30", func_8002AAE8);

INCLUDE_ASM("asm/nonmatchings/main_segment/000E30", func_8002AB28);

INCLUDE_ASM("asm/nonmatchings/main_segment/000E30", func_8002ABC0);

INCLUDE_ASM("asm/nonmatchings/main_segment/000E30", func_8002AC64);

INCLUDE_ASM("asm/nonmatchings/main_segment/000E30", func_8002ACE0);

INCLUDE_ASM("asm/nonmatchings/main_segment/000E30", func_8002AD38);

INCLUDE_ASM("asm/nonmatchings/main_segment/000E30", func_8002AE58);

INCLUDE_ASM("asm/nonmatchings/main_segment/000E30", func_8002AF7C);

INCLUDE_ASM("asm/nonmatchings/main_segment/000E30", func_8002AFA4);

INCLUDE_ASM("asm/nonmatchings/main_segment/000E30", func_8002AFC4);

INCLUDE_ASM("asm/nonmatchings/main_segment/000E30", func_8002AFE4);

INCLUDE_ASM("asm/nonmatchings/main_segment/000E30", func_8002B000);

INCLUDE_ASM("asm/nonmatchings/main_segment/000E30", func_8002B028);

INCLUDE_ASM("asm/nonmatchings/main_segment/000E30", func_8002B078);

INCLUDE_ASM("asm/nonmatchings/main_segment/000E30", func_8002B098);

INCLUDE_ASM("asm/nonmatchings/main_segment/000E30", func_8002B0E4);

INCLUDE_ASM("asm/nonmatchings/main_segment/000E30", func_8002B100);

INCLUDE_ASM("asm/nonmatchings/main_segment/000E30", func_8002B13C);

INCLUDE_ASM("asm/nonmatchings/main_segment/000E30", func_8002B15C);

INCLUDE_ASM("asm/nonmatchings/main_segment/000E30", func_8002B178);

INCLUDE_ASM("asm/nonmatchings/main_segment/000E30", func_8002B194);

INCLUDE_ASM("asm/nonmatchings/main_segment/000E30", func_8002B1B4);

INCLUDE_ASM("asm/nonmatchings/main_segment/000E30", func_8002B344);

INCLUDE_ASM("asm/nonmatchings/main_segment/000E30", func_8002B370);

INCLUDE_ASM("asm/nonmatchings/main_segment/000E30", func_8002B394);

void func_8002B490(s32 *arg0 UNUSED) {
    B_800ED430 = 2;
    B_800E9BB6 = 4;
    D_80088124 = 0;
    B_800FAD2C = 0;
}

INCLUDE_ASM("asm/nonmatchings/main_segment/000E30", func_8002B4BC);

INCLUDE_ASM("asm/nonmatchings/main_segment/000E30", func_8002B5E4);

INCLUDE_ASM("asm/nonmatchings/main_segment/000E30", func_8002B710);

INCLUDE_ASM("asm/nonmatchings/main_segment/000E30", func_8002B728);

INCLUDE_ASM("asm/nonmatchings/main_segment/000E30", func_8002B754);

void func_8002B7A8(struct_800EB670 *arg0) {
    osCreateThread(&B_800EBD20, 5, (StartThreadFunc)func_8002B4BC, arg0, STACK_TOP(B_800F1E30), 0xF);
    osStartThread(&B_800EBD20);
}

INCLUDE_ASM("asm/nonmatchings/main_segment/000E30", func_8002B800);

INCLUDE_ASM("asm/nonmatchings/main_segment/000E30", func_8002B834);

INCLUDE_ASM("asm/nonmatchings/main_segment/000E30", func_8002B9D8);

INCLUDE_ASM("asm/nonmatchings/main_segment/000E30", func_8002BAB8);

INCLUDE_ASM("asm/nonmatchings/main_segment/000E30", func_8002BBD8);

INCLUDE_ASM("asm/nonmatchings/main_segment/000E30", func_8002BC58);

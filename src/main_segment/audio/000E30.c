#include "audio/audio_stuff.h"

#include "include_asm.h"
#include "macros_defines.h"
#include "unknown_structs.h"
#include "unk.h"
#include "boot_functions.h"
#include "boot_variables.h"
#include "main_segment_functions.h"
#include "main_segment_variables.h"


INCLUDE_ASM("asm/nonmatchings/main_segment/audio/000E30", func_8002AA80);

INCLUDE_ASM("asm/nonmatchings/main_segment/audio/000E30", func_8002AAD8);

INCLUDE_ASM("asm/nonmatchings/main_segment/audio/000E30", func_8002AAE8);

INCLUDE_ASM("asm/nonmatchings/main_segment/audio/000E30", func_8002AB28);

INCLUDE_ASM("asm/nonmatchings/main_segment/audio/000E30", func_8002ABC0);

INCLUDE_ASM("asm/nonmatchings/main_segment/audio/000E30", func_8002AC64);

INCLUDE_ASM("asm/nonmatchings/main_segment/audio/000E30", func_8002ACE0);

void func_8002AD38(struct_800EB670 *arg0) {
    s32 i;
    struct_800FACE0 *ptr = &B_800FACE0;
    romoffset_t *temp;
    UNK_TYPE val = -1;

    for (i = ARRAY_COUNT(ptr->unk_00)-1; i >= 0; i--) {
        ptr->unk_00[i] = val;
    }

    for (i = 0; i < ARRAY_COUNT(ptr->unk_08); i++) {
        func_8002AAD8(&ptr->unk_08[i], i);
    }

    temp = &gRomOffset_N64PtrTables_End;
    func_8002D170(arg0, &B_800B3640, 0x31000, *temp - gRomOffset_N64PtrTables_Start, func_8002AA80(), 2, D_8000E84C - D_8000E848, 4, 0x32);

    func_8002D3B0(gRomOffset_N64PtrTables_Start, *temp - gRomOffset_N64PtrTables_Start, (void*)gRomOffset_N64WaveTables_Start);
    func_8002D6A4(D_8000E848, D_8000E84C - D_8000E848);
}

INCLUDE_ASM("asm/nonmatchings/main_segment/audio/000E30", func_8002AE58);

INCLUDE_ASM("asm/nonmatchings/main_segment/audio/000E30", func_8002AF7C);

INCLUDE_ASM("asm/nonmatchings/main_segment/audio/000E30", func_8002AFA4);

INCLUDE_ASM("asm/nonmatchings/main_segment/audio/000E30", func_8002AFC4);

INCLUDE_ASM("asm/nonmatchings/main_segment/audio/000E30", func_8002AFE4);

INCLUDE_ASM("asm/nonmatchings/main_segment/audio/000E30", func_8002B000);

INCLUDE_ASM("asm/nonmatchings/main_segment/audio/000E30", func_8002B028);

INCLUDE_ASM("asm/nonmatchings/main_segment/audio/000E30", func_8002B078);

INCLUDE_ASM("asm/nonmatchings/main_segment/audio/000E30", func_8002B098);

INCLUDE_ASM("asm/nonmatchings/main_segment/audio/000E30", func_8002B0E4);

INCLUDE_ASM("asm/nonmatchings/main_segment/audio/000E30", func_8002B100);

INCLUDE_ASM("asm/nonmatchings/main_segment/audio/000E30", func_8002B13C);

INCLUDE_ASM("asm/nonmatchings/main_segment/audio/000E30", func_8002B15C);

INCLUDE_ASM("asm/nonmatchings/main_segment/audio/000E30", func_8002B178);

INCLUDE_ASM("asm/nonmatchings/main_segment/audio/000E30", func_8002B194);

INCLUDE_ASM("asm/nonmatchings/main_segment/audio/000E30", func_8002B1B4);

INCLUDE_ASM("asm/nonmatchings/main_segment/audio/000E30", func_8002B344);

INCLUDE_ASM("asm/nonmatchings/main_segment/audio/000E30", func_8002B370);

INCLUDE_ASM("asm/nonmatchings/main_segment/audio/000E30", func_8002B394);

void func_8002B490(s32 *arg0 UNUSED) {
    B_800ED430 = 2;
    B_800E9BB6 = 4;
    D_80088124 = 0;
    B_800FAD2C = 0;
}

INCLUDE_ASM("asm/nonmatchings/main_segment/audio/000E30", func_8002B4BC);

INCLUDE_ASM("asm/nonmatchings/main_segment/audio/000E30", func_8002B5E4);

INCLUDE_ASM("asm/nonmatchings/main_segment/audio/000E30", func_8002B710);

INCLUDE_ASM("asm/nonmatchings/main_segment/audio/000E30", func_8002B728);

INCLUDE_ASM("asm/nonmatchings/main_segment/audio/000E30", func_8002B754);

void func_8002B7A8(struct_800EB670 *arg0) {
    osCreateThread(&B_800EBD20, 5, (StartThreadFunc)func_8002B4BC, arg0, STACK_TOP(B_800F1E30), 0xF);
    osStartThread(&B_800EBD20);
}

INCLUDE_ASM("asm/nonmatchings/main_segment/audio/000E30", func_8002B800);

INCLUDE_ASM("asm/nonmatchings/main_segment/audio/000E30", func_8002B834);

INCLUDE_ASM("asm/nonmatchings/main_segment/audio/000E30", func_8002B9D8);

INCLUDE_ASM("asm/nonmatchings/main_segment/audio/000E30", func_8002BAB8);

INCLUDE_ASM("asm/nonmatchings/main_segment/audio/000E30", func_8002BBD8);

INCLUDE_ASM("asm/nonmatchings/main_segment/audio/000E30", func_8002BC58);

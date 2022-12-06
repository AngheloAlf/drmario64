#include "ultra64.h"
#include "include_asm.h"
#include "macros_defines.h"
#include "unknown_structs.h"
#include "main_segment_functions.h"
#include "main_segment_variables.h"
#include "rom_offsets.h"

INCLUDE_RODATA("asm/nonmatchings/main_segment/02FD90", D_800B1430);
INCLUDE_RODATA("asm/nonmatchings/main_segment/02FD90", D_800B1438);

INCLUDE_ASM("asm/nonmatchings/main_segment/02FD90", func_800599E0);

INCLUDE_ASM("asm/nonmatchings/main_segment/02FD90", func_80059A58);

INCLUDE_ASM("asm/nonmatchings/main_segment/02FD90", func_80059AA4);

INCLUDE_ASM("asm/nonmatchings/main_segment/02FD90", func_80059AF0);

INCLUDE_ASM("asm/nonmatchings/main_segment/02FD90", func_80059B5C);

INCLUDE_ASM("asm/nonmatchings/main_segment/02FD90", func_80059BC8);

INCLUDE_ASM("asm/nonmatchings/main_segment/02FD90", func_80059C34);

void func_80059CA0(struct_800F3E5C *arg0) {
    osRecvMesg(&arg0->unk_0000C, NULL, OS_MESG_BLOCK);
}

INCLUDE_ASM("asm/nonmatchings/main_segment/02FD90", func_80059CC4);

INCLUDE_ASM("asm/nonmatchings/main_segment/02FD90", func_80059CDC);

INCLUDE_ASM("asm/nonmatchings/main_segment/02FD90", func_80059CF4);

INCLUDE_ASM("asm/nonmatchings/main_segment/02FD90", func_80059D04);

INCLUDE_ASM("asm/nonmatchings/main_segment/02FD90", func_80059D14);

INCLUDE_ASM("asm/nonmatchings/main_segment/02FD90", func_80059D24);

INCLUDE_ASM("asm/nonmatchings/main_segment/02FD90", func_80059D34);

INCLUDE_ASM("asm/nonmatchings/main_segment/02FD90", func_80059D44);

INCLUDE_ASM("asm/nonmatchings/main_segment/02FD90", func_80059D54);

INCLUDE_ASM("asm/nonmatchings/main_segment/02FD90", func_80059D64);

INCLUDE_ASM("asm/nonmatchings/main_segment/02FD90", func_80059D74);

INCLUDE_ASM("asm/nonmatchings/main_segment/02FD90", func_80059D84);

INCLUDE_ASM("asm/nonmatchings/main_segment/02FD90", func_80059D94);

INCLUDE_ASM("asm/nonmatchings/main_segment/02FD90", func_80059DA4);

INCLUDE_ASM("asm/nonmatchings/main_segment/02FD90", func_80059DB4);

INCLUDE_ASM("asm/nonmatchings/main_segment/02FD90", func_80059DC4);

INCLUDE_ASM("asm/nonmatchings/main_segment/02FD90", func_80059DD4);

INCLUDE_ASM("asm/nonmatchings/main_segment/02FD90", func_80059DE4);

INCLUDE_ASM("asm/nonmatchings/main_segment/02FD90", func_80059DF4);

INCLUDE_ASM("asm/nonmatchings/main_segment/02FD90", func_80059DFC);

INCLUDE_ASM("asm/nonmatchings/main_segment/02FD90", func_80059E1C);

INCLUDE_ASM("asm/nonmatchings/main_segment/02FD90", func_80059E3C);

INCLUDE_ASM("asm/nonmatchings/main_segment/02FD90", func_80059E5C);

INCLUDE_ASM("asm/nonmatchings/main_segment/02FD90", func_80059E6C);

INCLUDE_ASM("asm/nonmatchings/main_segment/02FD90", func_80059E7C);

INCLUDE_ASM("asm/nonmatchings/main_segment/02FD90", func_80059E8C);

INCLUDE_ASM("asm/nonmatchings/main_segment/02FD90", func_80059E9C);

INCLUDE_ASM("asm/nonmatchings/main_segment/02FD90", func_80059EB8);

void func_80059F1C(struct_800F3E5C *arg0, UNK_PTR *arg1, struct_800EB670 *arg2) {
    UNK_PTR sp10 = *arg1;
    UNK_PTR temp_v0;
    s32 i;
    RomOffsetPair *pairArray = D_8000E838;

    arg0->unk_00000 = arg2;
    arg0->unk_02460 = sp10;
    osCreateMesgQueue(&arg0->unk_0000C, arg0->unk_00024, ARRAY_COUNT(arg0->unk_00024));
    func_8002A184(arg2, &arg0->unk_00004, &arg0->unk_0000C);

    for (i = 0; i < ARRAY_COUNT(arg0->unk_00048); i++) {
        arg0->unk_02448[i] = &arg0->unk_00048[i];
        arg0->unk_02454[i] = &arg0->unk_00C48[i];
    }

    sp10 = func_80077D68(sp10, D_8008840F != 0);
    arg0->unk_02478 = func_80045098(&sp10, pairArray[0x36].start, pairArray[0x36].end);
    arg0->unk_0247C = func_80045098(&sp10, pairArray[0x37].start, pairArray[0x37].end);
    arg0->unk_02484 = func_80045098(&sp10, pairArray[0x38].start, pairArray[0x38].end);
    arg0->unk_02488 = func_80045098(&sp10, pairArray[0x39].start, pairArray[0x39].end);
    arg0->unk_0248C = func_80045098(&sp10, pairArray[0x3A].start, pairArray[0x3A].end);
    arg0->unk_02490 = func_80045098(&sp10, pairArray[0x3B].start, pairArray[0x3B].end);
    arg0->unk_02494 = func_80045098(&sp10, pairArray[0x3C].start, pairArray[0x3C].end);
    arg0->unk_02498 = func_80045098(&sp10, pairArray[0x3D].start, pairArray[0x3D].end);
    arg0->unk_0249C = func_80045098(&sp10, pairArray[0x3E].start, pairArray[0x3E].end);
    arg0->unk_024A0 = func_80045098(&sp10, pairArray[0x3F].start, pairArray[0x3F].end);
    arg0->unk_024A4 = func_80045098(&sp10, pairArray[0x2F].start, pairArray[0x2F].end);
    arg0->unk_024A8 = func_80045098(&sp10, pairArray[0x30].start, pairArray[0x30].end);
    arg0->unk_024AC = func_80045098(&sp10, pairArray[0x40].start, pairArray[0x40].end);
    arg0->unk_024B0 = func_80045098(&sp10, pairArray[0x42].start, pairArray[0x42].end);
    arg0->unk_024B4 = func_80045098(&sp10, pairArray[0x41].start, pairArray[0x41].end);

    func_80046250(&arg0->unk_024B8, 0, 0);
    func_800474EC(&arg0->unk_02548, arg0, 0x70, 0x12);

    arg0->unk_111D0 = D_8008E8B4;
    arg0->unk_111CC = D_8008E8B4;
    arg0->unk_111C8 = D_8008E8B4;
    arg0->unk_111DC = 1.0f;
    arg0->unk_111C0 = 0;
    arg0->unk_111D8 = 0;
    arg0->unk_111EC = 0;
    arg0->unk_111F0 = 0;
    arg0->unk_111C4 = -1;
    arg0->unk_111D4 = ENUM_800EBCF0_6;
    arg0->unk_111E4 = 1;
    arg0->unk_111E0 = -(1.0f / 30.0f);
    arg0->unk_111E8 = 1;
    arg0->unk_111F4 = 0x7F;

    func_80038BE0(&arg0->unk_111F8, &sp10);
    arg0->unk_02464 = 0x60000;

    for (i = 0; i < ARRAY_COUNTU(arg0->unk_02470); i++) {
        temp_v0 = ALIGN_PTR(sp10);
        arg0->unk_02470[i] = temp_v0;
        arg0->unk_02468[i] = temp_v0;
        sp10 = temp_v0 + arg0->unk_02464;
    }

    for (i = 0; i < ARRAY_COUNT(B_80123700); i++) {
        B_80123700[i].unk_000 = 0;
        B_80123700[i].unk_004 = 0;
    }

    D_8008840E = 0;
    *arg1 = sp10;
}

void func_8005A2AC(struct_800F3E5C *arg0) {
    func_8002A1DC(arg0->unk_00000, &arg0->unk_00004);
    D_8008E8B4 = arg0->unk_111CC;
}

INCLUDE_ASM("asm/nonmatchings/main_segment/02FD90", func_8005A2EC);

INCLUDE_ASM("asm/nonmatchings/main_segment/02FD90", func_8005A434);

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

#if 0
//? func_80038BE0(s8 *, void **);                     /* extern */
//s32 func_80045098(void **, s32, s32);               /* extern */
//? func_80046250(s8 *, ?, ?);                        /* extern */
//? func_800474EC(s8 *, struct_800F3E5C *, ?, ?);     /* extern */
extern s8 D_8008840E;

void func_80059F1C(struct_800F3E5C *arg0, void **arg1, struct_800EB670 *arg2) {
    void *sp10;
    s32 temp_v0_3;
    s32 var_a1;
    s32 var_a1_3;
    s32 var_a2;
    s32 var_a3;
    s32 var_v1;
    struct_800F3E5C *var_a0_2;
    u32 var_a1_2;
    void *temp_v0;
    void *temp_v0_2;
    void *temp_v1;
    RomOffsetPair *pairArray = D_8000E838;

    temp_v0 = *arg1;
    arg0->unk_00000 = arg2;
    sp10 = temp_v0;
    arg0->unk_02460 = temp_v0;
    osCreateMesgQueue(&arg0->unk_0000C, arg0->unk_00024, ARRAY_COUNT(arg0->unk_00024));
    func_8002A184(arg2, &arg0->unk_00004, &arg0->unk_0000C);
    var_a1 = 0;
    var_a3 = 0xC48;
    var_a2 = 0x48;
    do {
        temp_v1 = arg0 + var_a3;
        var_a3 += 0x800;
        temp_v0_2 = arg0 + var_a2;
        var_a2 += 0x400;
        arg0->unk_02448[var_a1] = temp_v0_2;
        arg0->unk_02454[var_a1] = temp_v1;
        var_a1 += 1;
    } while (var_a1 < 3);
    sp10 = func_80077D68(sp10, D_8008840F != 0);
    arg0->unk_02478 = func_80045098(&sp10, pairArray[0x1B0/8].start, pairArray[(0x1B4-4)/8].end);
    arg0->unk_0247C = func_80045098(&sp10, pairArray[0x1B8/8].start, pairArray[(0x1BC-4)/8].end);
    arg0->unk_02484 = func_80045098(&sp10, pairArray[0x1C0/8].start, pairArray[(0x1C4-4)/8].end);
    arg0->unk_02488 = func_80045098(&sp10, pairArray[0x1C8/8].start, pairArray[(0x1CC-4)/8].end);
    arg0->unk_0248C = func_80045098(&sp10, pairArray[0x1D0/8].start, pairArray[(0x1D4-4)/8].end);
    arg0->unk_02490 = func_80045098(&sp10, pairArray[0x1D8/8].start, pairArray[(0x1DC-4)/8].end);
    arg0->unk_02494 = func_80045098(&sp10, pairArray[0x1E0/8].start, pairArray[(0x1E4-4)/8].end);
    arg0->unk_02498 = func_80045098(&sp10, pairArray[0x1E8/8].start, pairArray[(0x1EC-4)/8].end);
    arg0->unk_0249C = func_80045098(&sp10, pairArray[0x1F0/8].start, pairArray[(0x1F4-4)/8].end);
    arg0->unk_024A0 = func_80045098(&sp10, pairArray[0x1F8/8].start, pairArray[(0x1FC-4)/8].end);
    arg0->unk_024A4 = func_80045098(&sp10, pairArray[0x178/8].start, pairArray[(0x17C-4)/8].end);
    arg0->unk_024A8 = func_80045098(&sp10, pairArray[0x180/8].start, pairArray[(0x184-4)/8].end);
    arg0->unk_024AC = func_80045098(&sp10, pairArray[0x200/8].start, pairArray[(0x204-4)/8].end);
    arg0->unk_024B0 = func_80045098(&sp10, pairArray[0x210/8].start, pairArray[(0x214-4)/8].end);
    arg0->unk_024B4 = func_80045098(&sp10, pairArray[0x208/8].start, pairArray[(0x20C-4)/8].end);
    func_80046250(&arg0->unk_024B8, 0, 0);
    func_800474EC(&arg0->unk_02548, arg0, 0x70, 0x12);
    arg0->unk_111C4 = -1;
    arg0->unk_111D4 = ENUM_800EBCF0_6;
    arg0->unk_111E4 = 1;
    arg0->unk_111E8 = 1;
    arg0->unk_111C0 = 0;
    arg0->unk_111D8 = 0;
    arg0->unk_111EC = 0;
    arg0->unk_111F0 = 0;
    arg0->unk_111F4 = 0x7F;
    arg0->unk_111D0 = (s32) D_8008E8B4;
    arg0->unk_111CC = D_8008E8B4;
    arg0->unk_111C8 = D_8008E8B4;
    arg0->unk_111DC = 1.0f;
    arg0->unk_111E0 = -0.033333335f;
    func_80038BE0(arg0->unk_111F8, &sp10);
    var_a1_2 = 0;
    arg0->unk_02464 = 0x60000;
    do {
        temp_v0_3 = (s32) (sp10 + 0xF) & ~0xF;
        arg0->unk_02470[var_a1_2] = temp_v0_3;
        arg0->unk_02468[var_a1_2] = temp_v0_3;
        var_a1_2 += 1;
        sp10 = temp_v0_3 + arg0->unk_02464;
    } while (var_a1_2 < 2U);
    var_a1_3 = 0;
    do {
        B_80123700[var_a1_3].unk_000 = 0;
        B_80123700[var_a1_3].unk_004 = 0;
        var_a1_3 += 1;
    } while (var_a1_3 < 4);
    D_8008840E = 0;
    *arg1 = sp10;
}
#else
INCLUDE_ASM("asm/nonmatchings/main_segment/02FD90", func_80059F1C);
#endif

void func_8005A2AC(struct_800F3E5C *arg0) {
    func_8002A1DC(arg0->unk_00000, &arg0->unk_00004);
    D_8008E8B4 = arg0->unk_111CC;
}

INCLUDE_ASM("asm/nonmatchings/main_segment/02FD90", func_8005A2EC);

INCLUDE_ASM("asm/nonmatchings/main_segment/02FD90", func_8005A434);

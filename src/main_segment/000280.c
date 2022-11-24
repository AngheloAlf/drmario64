#include "ultra64.h"
#include "include_asm.h"
#include "unk.h"
#include "main_segment_functions.h"
#include "main_segment_variables.h"


void func_80029ED0(struct_800EB670* arg0, u8 arg1, u8 arg2) {
    arg0->unk_678 = 1;
    arg0->unk_000 = 1;
    arg0->unk_66C = 0;
    arg0->unk_670 = 0;
    arg0->unk_674 = 0;
    arg0->unk_668 = 0;
    arg0->unk_002 = 3;
    osCreateMesgQueue(&arg0->unk_074, (void** ) &arg0->unk_08C, 8);
    osCreateMesgQueue(&arg0->unk_0AC, (void** ) &arg0->unk_0C4, 8);
    osCreateMesgQueue(&arg0->unk_0E4, (void** ) &arg0->unk_0FC, 8);
    osCreateMesgQueue(&arg0->unk_03C, (void** ) &arg0->unk_054, 8);
    osCreateMesgQueue(&arg0->unk_004, (void** ) &arg0->unk_01C, 8);
    osCreateMesgQueue(&arg0->unk_11C, (void** ) &arg0->unk_134, 8);
    osCreateViManager(0xFE);
    osViSetMode(&osViModeTable[arg1]);
    osViBlack(1U);
    osViSetEvent(&arg0->unk_074, (OSMesg)0x29A, arg2);
    osSetEventMesg(OS_EVENT_SP, &arg0->unk_0AC, (OSMesg)0x29B);
    osSetEventMesg(OS_EVENT_DP, &arg0->unk_0E4, (OSMesg)0x29C);
    osSetEventMesg(OS_EVENT_PRENMI, &arg0->unk_074, (OSMesg)0x29D);
    osCreateThread(&arg0->unk_158, 0x13, func_8002A0DC, arg0, &B_800F1CE0, 0x78);
    osStartThread(&arg0->unk_158);
    osCreateThread(&arg0->unk_308, 0x12, func_8002A2B8, arg0, &B_800FACE0, 0x6E);
    osStartThread(&arg0->unk_308);
    osCreateThread(&arg0->unk_4B8, 0x11, func_8002A4D8, arg0, &B_800EF440, 0x64);
    osStartThread(&arg0->unk_4B8);
}

INCLUDE_ASM("asm/nonmatchings/main_segment/000280", func_8002A0CC);

INCLUDE_ASM("asm/nonmatchings/main_segment/000280", func_8002A0D4);

INCLUDE_ASM("asm/nonmatchings/main_segment/000280", func_8002A0DC);

INCLUDE_ASM("asm/nonmatchings/main_segment/000280", func_8002A184);

INCLUDE_ASM("asm/nonmatchings/main_segment/000280", func_8002A1DC);

INCLUDE_ASM("asm/nonmatchings/main_segment/000280", func_8002A26C);

INCLUDE_ASM("asm/nonmatchings/main_segment/000280", func_8002A2B8);

INCLUDE_ASM("asm/nonmatchings/main_segment/000280", func_8002A3F4);

INCLUDE_ASM("asm/nonmatchings/main_segment/000280", func_8002A4D8);

INCLUDE_ASM("asm/nonmatchings/main_segment/000280", func_8002A51C);

#include "ultra64.h"
#include "include_asm.h"
#include "unk.h"


//INCLUDE_ASM("asm/nonmatchings/main_segment/000280", func_80029ED0);
#define UNK_TYPE s32
#define UNK_TYPE1 s8

typedef struct struct_800EB670 {
    /* 0x000 */ s16 unk_000;
    /* 0x002 */ s16 unk_002;
    /* 0x004 */ OSMesgQueue unk_004;
    /* 0x01C */ UNK_TYPE unk_01C;
    /* 0x020 */ UNK_TYPE1 unk_020[0x1C];
    /* 0x03C */ OSMesgQueue unk_03C;
    /* 0x054 */ UNK_TYPE unk_054;
    /* 0x058 */ UNK_TYPE1 unk_058[0x1C];
    /* 0x074 */ OSMesgQueue unk_074;
    /* 0x08C */ UNK_TYPE unk_08C;
    /* 0x090 */ UNK_TYPE1 unk_090[0x1C];
    /* 0x0AC */ OSMesgQueue unk_0AC;
    /* 0x0C4 */ UNK_TYPE unk_0C4;
    /* 0x0C8 */ UNK_TYPE1 unk_0C8[0x1C];
    /* 0x0E4 */ OSMesgQueue unk_0E4;
    /* 0x0FC */ UNK_TYPE unk_0FC;
    /* 0x100 */ UNK_TYPE1 unk_100[0x1C];
    /* 0x11C */ OSMesgQueue unk_11C;
    /* 0x134 */ UNK_TYPE unk_134;
    /* 0x138 */ UNK_TYPE1 unk_138[0x20];
    /* 0x158 */ OSThread unk_158;
    /* 0x308 */ OSThread unk_308;
    /* 0x4B8 */ OSThread unk_4B8;
    /* 0x668 */ UNK_TYPE unk_668;
    /* 0x66C */ UNK_TYPE unk_66C;
    /* 0x670 */ UNK_TYPE unk_670;
    /* 0x674 */ UNK_TYPE unk_674;
    /* 0x678 */ UNK_TYPE unk_678;
} struct_800EB670; // size >= 0x67C


void func_8002A0DC(void*);                             /* extern */
void func_8002A2B8(void*);                             /* extern */
void func_8002A4D8(void*);                             /* extern */
extern UNK_TYPE D_800EF440;
extern UNK_TYPE D_800F1CE0;
extern UNK_TYPE D_800FACE0;


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
    osViSetEvent(&arg0->unk_074, (void* )0x29A, arg2);
    osSetEventMesg(4U, &arg0->unk_0AC, (void* )0x29B);
    osSetEventMesg(9U, &arg0->unk_0E4, (void* )0x29C);
    osSetEventMesg(0xEU, &arg0->unk_074, (void* )0x29D);
    osCreateThread(&arg0->unk_158, 0x13, func_8002A0DC, arg0, &D_800F1CE0, 0x78);
    osStartThread(&arg0->unk_158);
    osCreateThread(&arg0->unk_308, 0x12, func_8002A2B8, arg0, &D_800FACE0, 0x6E);
    osStartThread(&arg0->unk_308);
    osCreateThread(&arg0->unk_4B8, 0x11, func_8002A4D8, arg0, &D_800EF440, 0x64);
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

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

void func_8002AAD8(struct_800FACE0_unk_08 *arg0, s32 arg1) {
    arg0->unk_0 = 0;
    arg0->unk_4 = arg1;
    arg0->unk_8 = 0;
}

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
    func_8002D170(arg0, &B_800B3640, 0x31000, *temp - gRomOffset_N64PtrTables_Start, func_8002AA80(), 2, D_8000E84C - D_8000E848, 4, 50);

    func_8002D3B0(gRomOffset_N64PtrTables_Start, *temp - gRomOffset_N64PtrTables_Start, (void*)gRomOffset_N64WaveTables_Start);
    func_8002D6A4(D_8000E848, D_8000E84C - D_8000E848);
}

INCLUDE_ASM("asm/nonmatchings/main_segment/audio/000E30", func_8002AE58);


void func_8002AF7C(void) {
    func_8002B0E4();
    MusStop(MUSFLAG_EFFECTS | MUSFLAG_SONGS, 0);
}

s32 func_8002AFA4(void) {
    return MusAsk(MUSFLAG_EFFECTS | MUSFLAG_SONGS) == 0;
}

INCLUDE_ASM("asm/nonmatchings/main_segment/audio/000E30", func_8002AFC4);

INCLUDE_ASM("asm/nonmatchings/main_segment/audio/000E30", func_8002AFE4);

INCLUDE_ASM("asm/nonmatchings/main_segment/audio/000E30", func_8002B000);

INCLUDE_ASM("asm/nonmatchings/main_segment/audio/000E30", func_8002B028);

INCLUDE_ASM("asm/nonmatchings/main_segment/audio/000E30", func_8002B078);

INCLUDE_ASM("asm/nonmatchings/main_segment/audio/000E30", func_8002B098);

void func_8002B0E4(void) {
    func_8002B100(0);
}

void func_8002B100(s32 arg0) {
    func_8002D554(arg0, 0);
    B_800FACE0.unk_00[arg0] = -1;
}

s32 func_8002B13C(s32 arg0) {
    return func_8002B15C(0, arg0);
}

s32 func_8002B15C(s32 arg0, s32 arg1) {
    return func_8002D58C(arg0, arg1);
}

bool func_8002B178(void) {
    return func_8002B194(0);
}

bool func_8002B194(s32 arg0) {
    return func_8002D51C(arg0) == 0;
}

INCLUDE_ASM("asm/nonmatchings/main_segment/audio/000E30", func_8002B1B4);

void func_8002B344(s32 arg0) {
    if (D_80088406 < 6) {
        func_8002B1B4(arg0);
    }
}

s32 func_8002B370(void) {
    return MusFxBankNumberOfEffects(func_8002D710());
}

INCLUDE_ASM("asm/nonmatchings/main_segment/audio/000E30", func_8002B394);

void func_8002B490(UNK_PTR arg0 UNUSED) {
    B_800ED430 = 2;
    B_800E9BB6 = 4;
    D_80088124 = 0;
    B_800FAD2C = 0;
}

void func_8002B4BC(struct_800EB670 *arg0) {
    s16 *sp10 = NULL;

    D_80088128 = 0;
    osCreateMesgQueue(&B_800F4898, B_800EBED0, ARRAY_COUNT(B_800EBED0));
    func_8002A184(arg0, &B_800F48B0, &B_800F4898);
    B_800FAF94 = func_8002A0D4(arg0);

    while (true) {
        osRecvMesg(&B_800F4898, (OSMesg*)&sp10, OS_MESG_BLOCK);

        switch (*sp10) {
            case 1:
                func_8002B5E4();
                break;

            case 2:
                func_8002B710();
                break;

            case 4:
                func_8002B728();
                break;

            case 3:
                func_8002B754();
                break;
        }
    }
}

void func_8002B5E4(void) {
    switch (D_80088124) {
        case 0:
            break;

        case 1:
            if (D_80088128 < 2) {
                func_8007AEF4();
            }
            break;

        case 2:
            if (D_80088128 < 2) {
                func_8007636C();
            }
            break;

        case 3:
            if (D_80088128 < 2) {
                func_80075CF8();
            }
            break;

        case 4:
            if (D_80088128 == 0) {
                func_8007023C();
            }
            break;

        case 5:
            if (D_80088128 < 2) {
                func_8005B658();
            }
            break;

        case 6:
            if (D_80088128 < 2) {
                func_80071CE0();
            }
            break;

        case 7:
            if (D_80088128 < 2) {
                func_800767DC();
            }
            break;
    }
}

void func_8002B710(void) {
    D_80088128 -= 1;
}

void func_8002B728(void) {
    if (D_80088124 == 4) {
        func_80071A44();
    }
}

void func_8002B754(void) {
    osViSetYScale(1.0f);
    D_80088128 += 2;
    osViBlack(true);
    func_80000468();
    MusStop(MUSFLAG_EFFECTS | MUSFLAG_SONGS, 0);
}

void func_8002B7A8(struct_800EB670 *arg0) {
    osCreateThread(&B_800EBD20, 5, (StartThreadFunc)func_8002B4BC, arg0, STACK_TOP(B_800F1E30), 0xF);
    osStartThread(&B_800EBD20);
}

s16 func_8002B800(void) {
    s16 *sp10 = NULL;

    osRecvMesg(&B_800F4898, (OSMesg*) &sp10, OS_MESG_BLOCK);
    return *sp10;
}

INCLUDE_ASM("asm/nonmatchings/main_segment/audio/000E30", func_8002B834);

INCLUDE_ASM("asm/nonmatchings/main_segment/audio/000E30", func_8002B9D8);

INCLUDE_ASM("asm/nonmatchings/main_segment/audio/000E30", func_8002BAB8);

INCLUDE_ASM("asm/nonmatchings/main_segment/audio/000E30", func_8002BBD8);

INCLUDE_ASM("asm/nonmatchings/main_segment/audio/000E30", func_8002BC58);

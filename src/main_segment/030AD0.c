#include "ultra64.h"
#include "include_asm.h"
#include "macros_defines.h"
#include "unknown_structs.h"
#include "main_segment_functions.h"
#include "main_segment_variables.h"
#include "audio/audio_stuff.h"
#include "buffers.h"

INCLUDE_ASM("asm/nonmatchings/main_segment/030AD0", func_8005A720);

INCLUDE_ASM("asm/nonmatchings/main_segment/030AD0", func_8005A974);

INCLUDE_ASM("asm/nonmatchings/main_segment/030AD0", func_8005AD30);

INCLUDE_ASM("asm/nonmatchings/main_segment/030AD0", func_8005AEF4);

#if 0
extern s32 B_800EB4F4;
extern s32 B_800EFCB0;
//extern s16 B_800F6CD8[4];
extern s32 D_8008E788;

enum_800EBCF0 func_8005B2D4(struct_800EB670 *arg0) {
    UNK_PTR sp10;
    OSMesgQueue *var_a0_3;
    OSMesgQueue *var_a0_4;
    s16 *var_a0;
    s32 temp_a1;
    struct_800F3E5C *temp_s0;
    s32 temp_v0;
    s32 var_v1;
    s32 var_v1_2;
    u16 *var_a0_2;
    u16 *var_a1;
    u16 *var_a2;
    u16 *var_a3;

    sp10 = D_80124610;
    temp_s0 = ALIGN_PTR(D_80124610);
    if (B_800EB4F0 == ENUM_800EBCF0_3) {
        D_8008E8B4 = 0;
        D_8008E788 = 0;
        B_800EB4F4 = 0;
        B_800EFCB0 = 0;
    }
    func_80040A64();
    sp10 = &temp_s0[1];
    bzero(temp_s0, sizeof(struct_800F3E5C));
    B_800F3E5C = temp_s0;
    func_80059F1C(temp_s0, &sp10, arg0);

    B_800F1CE0 = func_8002A954();

    for (var_v1 = 3; var_v1 >= 0; var_v1--) {
        B_800F6CD8[var_v1] = 0xF30;
    }

    B_800EF554 = 0x18;
    B_800F1E20 = 6;
    B_800EBCF4 = B_800FB670[B_800FAD2C];
    func_8002AFC4(0xC);

    while ((temp_s0->unk_111D4 == ENUM_800EBCF0_6) || (temp_s0->unk_111DC < 1.0f)) {
        if (D_80088124 == 0) {
            while ((D_80088128 != 0) || (func_80040BA4() != 0)) {
                func_80059CA0(temp_s0);
            }

            func_8005A434(temp_s0);
        }

        if (temp_s0->unk_111D8 > 0) {
            for (var_v1_2 = 0; var_v1_2 < 4; var_v1_2++) {
                B_800F48C4[var_v1_2] = 0;
                gControllerPressedButtons[var_v1_2] = 0;
                gControllerPrevHoldButtons[var_v1_2] = 0;
                gControllerHoldButtons[var_v1_2] = 0;
            } 
        } else {
            func_8002A700();
        }
        func_80059CA0(temp_s0);
        func_8005A720(temp_s0);
        func_8005A974(temp_s0);
        func_8002AE58();

        if (temp_s0->unk_111CC == temp_s0->unk_111D0) {
            D_80088124 = 5;
        } else {
            temp_s0->unk_111C8 = temp_s0->unk_111CC;
            D_80088124 = 0;
            temp_s0->unk_111CC = temp_s0->unk_111D0;
            temp_s0->unk_111C4 = temp_s0->unk_111C0;
            temp_s0->unk_111C0 ^= 1;
        }
    }

    D_80088124 = 5;

    while (temp_s0->unk_111F4 != 0xF) {
        osRecvMesg(&temp_s0->unk_0000C, NULL, 1);
        func_8002AE58();
    }

    D_80088124 = 0;
    func_8002B0E4();

    while ((D_80088128 != 0) || !func_8002B178() || (func_80040BA4() != 0)) {
        osRecvMesg(&temp_s0->unk_0000C, NULL, 1);
        func_8002AE58();
    }

    func_8005A2AC(temp_s0);
    func_80040AE4();
    return temp_s0->unk_111D4;
}
#else
INCLUDE_ASM("asm/nonmatchings/main_segment/030AD0", func_8005B2D4);
#endif

INCLUDE_ASM("asm/nonmatchings/main_segment/030AD0", func_8005B658);

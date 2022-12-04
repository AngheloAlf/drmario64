#include "ultra64.h"
#include "include_asm.h"
#include "macros_defines.h"
#include "unknown_structs.h"
#include "main_segment_functions.h"
#include "main_segment_variables.h"
#include "audio/audio_stuff.h"


INCLUDE_RODATA("asm/nonmatchings/main_segment/04B9A0", D_800B31C0);
INCLUDE_RODATA("asm/nonmatchings/main_segment/04B9A0", D_800B31D8);
INCLUDE_RODATA("asm/nonmatchings/main_segment/04B9A0", D_800B31DC);
INCLUDE_RODATA("asm/nonmatchings/main_segment/04B9A0", D_800B31E0);

INCLUDE_ASM("asm/nonmatchings/main_segment/04B9A0", func_800755F0);

#ifdef NON_MATCHING
enum_800EBCF0 func_80075A2C(struct_800EB670 *arg0) {
    OSMesgQueue sp10;
    OSMesg sp28[8];
    struct_800FAF98_unk_64 sp48;
    enum_800EBCF0 var_v0;
    s32 temp_v0_2;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 var_a0;
    s32 i;
    s32 var_s3 = 1;
    s32 var_s4 = 0;
    struct_80123700 *var_s0;
    struct_800F4890 *temp_s2;

    osCreateMesgQueue(&sp10, sp28, ARRAY_COUNT(sp28));
    func_8002A184(arg0, &sp48, &sp10);
    func_800755F0();

    temp_s2 = B_800F4890;
    for (i = 0; i < ARRAY_COUNT(B_80123700); i++) {
        func_8002ED14(&B_80123700[i]);
    }

    while (var_s4 == 0) {
        func_8002A700();
        osRecvMesg(&sp10, NULL, 1);
        func_80071FA0(&temp_s2->unk_034);
        func_8006D7B0();

        temp_s2->unk_184++;
        if (temp_s2->unk_010 > 0) {
            var_s4 = temp_s2->unk_00C == 0xFF;
        }

        temp_s2->unk_00C = CLAMP(temp_s2->unk_00C + temp_s2->unk_010, 0, 0xFF);
        switch (D_80088410) {
            case 0x0:
                var_s3 = func_80072AB4();
                break;
            case 0x1:
                var_s3 = func_800733AC();
                break;
            case 0x2:
                var_s3 = func_800739D8();
                break;
            case 0x3:
                var_s3 = func_80074330();
                break;
        }
        func_8002B13C(0x60);
        func_8002AE58();
        if (temp_s2->unk_018 != 0) {
            temp_s2->unk_014++;
            if (temp_s2->unk_014 >= temp_s2->unk_018) {
                temp_s2->unk_014 = 0;
                temp_s2->unk_018 = 0;
                func_8002B078(D_80088402 * 2);
            }
        }
        if (temp_s2->unk_00C == 0) {
            s32 temp = ((-(B_800EB4F0 == ENUM_800EBCF0_3) & 0xFF3F) | 0x4000);

            var_s3 &= -((B_800FAF88[B_800EBD16[0]] & temp) == 0);
        }

        if (var_s3 == 0) {
            if (temp_s2->unk_010 < 0) {
                temp_s2->unk_010 = -temp_s2->unk_010;
            }
        }
        D_80088124 = 3;
    }

    func_8002AF7C();
    D_80088124 = 0;

    while ((func_8002AFA4() == 0) || (D_80088128 != 0)) {
        osRecvMesg(&sp10, NULL, 1);
        func_8002AE58();
    }

    func_8002A1DC(arg0, &sp48);

    var_v0 = ENUM_800EBCF0_3;
    if (B_800EB4F0 != ENUM_800EBCF0_3) {
        var_v0 = ENUM_800EBCF0_6;
    }
    return var_v0;
}
#else
INCLUDE_ASM("asm/nonmatchings/main_segment/04B9A0", func_80075A2C);
#endif

INCLUDE_ASM("asm/nonmatchings/main_segment/04B9A0", func_80075CF8);

/**
 * Originally part of char_anime.c
 */

#include "ultra64.h"
#include "include_asm.h"
#include "macros_defines.h"
#include "unknown_structs.h"
#include "main_segment_functions.h"
#include "main_segment_variables.h"
#include "boot_functions.h"
#include "boot_variables.h"
#include "rom_offsets.h"

INCLUDE_RODATA("asm/nonmatchings/main_segment/char_anime/0344D0", D_800B1A60);

INCLUDE_RODATA("asm/nonmatchings/main_segment/char_anime/0344D0", D_800B1AB0);

INCLUDE_RODATA("asm/nonmatchings/main_segment/char_anime/0344D0", D_800B1B00);

INCLUDE_RODATA("asm/nonmatchings/main_segment/char_anime/0344D0", D_800B1B04);

void animeSeq_init(struct_800F3E50_unk_44C *arg0, UNK_TYPE4 *arg1, UNK_TYPE4 arg2) {
    arg0->unk_0C = arg1;
    arg0->unk_08 = -1;
    arg0->unk_10 = arg2;
    arg0->unk_14 = 0;
    arg0->unk_18 = -1;
    animeSeq_update(arg0, 0);
}

void func_8005E154(struct_800F3E50_unk_44C *arg0, UNK_TYPE4 arg1) {
    animeSeq_init(arg0, arg0->unk_0C, arg1);
}

#if 0
void animeSeq_update(struct_800F3E50_unk_44C *arg0, s32 arg1) {
    s32 temp_a0;
    s32 var_s2;
    s8 *temp_v1_2;
    u8 temp_s0;
    u8 temp_v0_2;
    u8 temp_v1;
    u8 *temp_a1;

    var_s2 = arg1;
    while (var_s2 >= 0) {
        temp_a0 = arg0->unk_14;
        temp_a1 = *((arg0->unk_10 * 4) + arg0->unk_0C) + temp_a0;
        temp_v1 = temp_a1[0];
        switch (temp_v1) {                      /* irregular */
            case 0xF2:
                arg0->unk_14 = 0;
                arg0->unk_08 = -1;
                arg0->unk_10 = (s32) temp_a1[1];
                break;
            case 0xFF:
                var_s2 = -1;
                break;
            case 0xF0:
                arg0->unk_14 = (s32) (temp_a0 + 2);

                arg0->unk_08++;
                arg0->unk_00[arg0->unk_08] = (s8) arg0->unk_14;
                //arg0->unk_00[arg0->unk_08].unk_4 = (u8) temp_a1[1];
                break;
            case 0xF1:
                temp_v1_2 = &arg0->unk_00[arg0->unk_08];
                //temp_v0_2 = temp_v1_2->unk_4;
                //if (temp_v0_2 != 0xFF) {
                //    temp_v1_2->unk_4 = (u8) (temp_v0_2 - 1);
                //}
                if (/*(arg0->unk_00[arg0->unk_08].unk_4 != 0) &&*/ (temp_s0 = temp_a1[1], (((rand() % 100) < (s32) temp_s0) != 0))) {
                    arg0->unk_14 = (s32) (u8) arg0->unk_00[arg0->unk_08];
                } else {
                    arg0->unk_14 = (s32) (arg0->unk_14 + 2);
                    arg0->unk_08 = (s32) (arg0->unk_08 - 1);
                }
                break;
            default:
                if (var_s2 > 0) {
                    arg0->unk_14 = (s32) (arg0->unk_14 + 1);
                }
                var_s2 -= 1;
                arg0->unk_18 = (s32) (temp_a1[0] - 1);
                break;
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/main_segment/char_anime/0344D0", animeSeq_update);
#endif

INCLUDE_ASM("asm/nonmatchings/main_segment/char_anime/0344D0", func_8005E32C);

INCLUDE_ASM("asm/nonmatchings/main_segment/char_anime/0344D0", func_8005E358);

INCLUDE_ASM("asm/nonmatchings/main_segment/char_anime/0344D0", func_8005E36C);

INCLUDE_ASM("asm/nonmatchings/main_segment/char_anime/0344D0", func_8005E40C);

void animeState_set(struct_800F3E50_unk_44C *arg0, UNK_TYPE4 arg1) {
    arg0->unk_20 = 0;
    func_8005E154(arg0, arg1);
}

void animeState_update(struct_800F3E50_unk_44C *arg0) {
    animeSeq_update(arg0, arg0->unk_20 % 2U);
    arg0->unk_20++;
}

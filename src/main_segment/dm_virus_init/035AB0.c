/**
 * Originally part of dm_virus_init.c
 */

#include "ultra64.h"
#include "include_asm.h"
#include "macros_defines.h"
#include "unknown_structs.h"
#include "unk.h"
#include "boot_functions.h"
#include "boot_variables.h"
#include "main_segment_functions.h"
#include "main_segment_variables.h"

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_virus_init/035AB0", D_800B1BA0);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_virus_init/035AB0", D_800B1BBC);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_virus_init/035AB0", D_800B1BC8);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_virus_init/035AB0", D_800B1BCC);

#if 0
extern u8 D_800B1BCC[];
extern u8 D_800B1BA0[];

void _dm_virus_init(u32 arg0, struct_80123700 *arg1, struct_virus_map_data *arg2, struct_virus_map_disp_order *arg3, s32 arg4) {
    u16 sp10[4];
    u16 sp14;
    struct_80123700 *sp24;
    struct_virus_map_data *sp2C;
    struct_virus_map_disp_order *sp34;
    u16 sp3E;
    u8 sp47;
    u8 sp4F;
    u8 sp57;
    u8 sp5F;
    s32 sp6C;
    s16 temp_a0;
    s16 temp_a0_3;
    s16 var_s0;
    s16 var_s0_2;
    s16 var_s0_3;
    s32 temp_a0_2;
    s32 temp_s0_2;
    s32 temp_s2;
    s32 temp_v0;
    s32 temp_v0_4;
    u16 temp_v0_6;
    u16 var_fp;
    s16 var_s0_4;
    u16 var_s3;
    u16 var_s4;
    u8 var_s6;
    u8 var_v0_5;
    s8 temp_v1_4;
    u16 *temp_v0_7;
    u16 temp_a3;
    u8 *var_v0;
    u8 temp_v1_2;
    u8 temp_v1_3;
    u8 thingy;

    //var_s6 = saved_reg_s6;
    sp24 = arg1;
    sp2C = arg2;
    sp34 = arg3;

loop_1:

    for (var_s0 = 0; var_s0 < ARRAY_COUNT(sp2C->unk_000); var_s0++) {
        sp2C->unk_000[var_s0].unk_0 = -1;
        sp2C->unk_000[var_s0].unk_1 = 0;
        sp2C->unk_000[var_s0].unk_2 = 0;
    }

    for (var_s0_2 = 0; var_s0_2 < ARRAY_COUNT(sp34->unk_00); var_s0_2++) {
        sp34->unk_00[var_s0_2] = -1;
    }

    if ((arg0 == 1) || (arg0 == 3)) {
        temp_v1_2 = D_800B1BCC[sp24->unk_16C];
        var_v0 = temp_v1_2 + D_800B1BA0;
        if (temp_v1_2 >= 0x18U) {
            var_v0 = D_800B1BA0 + 0x17;
        }
    } else {
        var_v0 = sp24->unk_026 + D_800B1BA0;
        if (sp24->unk_026 >= 0x18U) {
            var_v0 = D_800B1BA0 + 0x17;
        }
    }

    sp5F = *var_v0;
    sp4F = func_8005F698(arg0, sp24);

    for (var_s0_3 = 0; var_s0_3 < 4; var_s0_3++) {
        sp10[var_s0_3] = (sp4F / 3) & 0xFF;
    }

    temp_a0_2 = (sp4F % 3) & 0xFF;

    var_s0_4 = 0;
    while (var_s0_4 < temp_a0_2) {
        temp_v0_4 = random(3);
        temp_a3 = sp10[temp_v0_4];
        if (sp10[(temp_v0_4 + 1) % 3] >= temp_a3) {
            if (sp10[(temp_v0_4 + 2) % 3] >= temp_a3) {
                sp10[temp_v0_4]++;
                var_s0_4++;
            }
        }
    }

    sp57 = 0;
    if (arg4 == 1) {
        sp47 = 2;
        sp57 = 1;
        temp_v1_4 = (sp5F * 8) + 3;
        sp14 -= 1;
        sp2C->unk_000[temp_v1_4].unk_0 = 2U;
        sp2C->unk_000[temp_v1_4].unk_1 = 3;
        sp2C->unk_000[temp_v1_4].unk_2 = (s8) (sp5F + 1);
        sp34->unk_00[0] = temp_v1_4;
    }

    sp6C = sp5F < 0x10U;
    while (sp57 < sp4F) {
        sp3E = 0;
        var_fp = 0;

    //loop_24:;
        do {
            do  {
                temp_v0_6 = random(3);
            } while (sp10[temp_v0_6] == 0);

            sp47 = temp_v0_6;
            var_fp += 1;
            if (var_fp == 2) {
                sp3E += 1;
                var_fp = 0;
                if (sp3E >= 3U) {
                    goto loop_1;
                }

                for (var_s4 = 0; var_s4 < 8; var_s4++) {
                    var_s3 = 0x10;
                    if (sp6C != 0) {

                        // loop_30:
                        while (true) {
                            var_s6 = 0;
                            thingy = func_8005F310(sp2C, var_s4, var_s3);
                            if (thingy || (var_s6 = dm_check_color(sp2C, var_s4, var_s3, sp47), (var_s6 == 0)) || (var_s6 = dm_check_color_2(sp2C, var_s4, var_s3, sp47), (var_s6 == 0))) {
                                var_s3 -= 1;
                                if (sp5F >= var_s3) {
                                    //goto block_34;
                                    break;
                                }
                                //goto loop_30;
                            } else {
                                break;
                            }
                            //else {
                            //    goto block_43;
                            //}
                        }
                    }
    //block_34:;
                }
            } else {

                do {
                    var_s4 = random(8);
                    do {
                        var_s3 = random(0x11);
                    } while (var_s3 < (sp5F + 1));
                    thingy = func_8005F310(sp2C, var_s4, temp_s0_2);
                } while (thingy);

                var_s6 = dm_check_color(sp2C, var_s4, temp_s0_2, sp47);
                if (var_s6 == 0) {
                    //goto loop_24;
                    continue;
                }
                var_s6 = dm_check_color_2(sp2C, var_s4, temp_s0_2, sp47);
            }

        } while (var_s6 == 0);

    //block_43:
        temp_v0_7 = &sp10[temp_v0_6];
        temp_a0_3 = var_s4 + ((var_s3 - 1) * 8);
        sp10[temp_v0_6] -= 1;
        sp2C->unk_000[temp_a0_3].unk_0 = sp47;
        sp2C->unk_000[temp_a0_3].unk_1 = (s8) var_s4;
        sp2C->unk_000[temp_a0_3].unk_2 = (s8) var_s3;
        sp34->unk_00[sp57] = (s8) temp_a0_3;
        sp57 += 1;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/main_segment/dm_virus_init/035AB0", _dm_virus_init);
#endif

void dm_virus_init(u32 arg0, struct_80123700 *arg1, struct_virus_map_data *arg2, struct_virus_map_disp_order *arg3) {
    _dm_virus_init(arg0, arg1, arg2, arg3, 0);
}

void func_8005FC6C(struct_8005FC6C_arg0 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    bzero(arg0, sizeof(struct_8005FC6C_arg0));
    arg0->unk_000 = arg1;
    arg0->unk_004 = arg2;
    arg0->unk_008 = arg3;
}

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_virus_init/035AB0", _makeFlash_checkOrdre);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_virus_init/035AB0", func_8005FE68);

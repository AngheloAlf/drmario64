/**
 * Original filename: record.c
 */

#include "libultra.h"
#include "include_asm.h"
#include "macros_defines.h"
#include "unknown_structs.h"
#include "boot_functions.h"
#include "boot_variables.h"
#include "main_segment_functions.h"
#include "main_segment_variables.h"
#include "audio/audio_stuff.h"
#include "recwritingmsg.h"

const char eeprom_header[4] = "DM64";

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/record", RO_800ACF44);
#endif

extern const char _defName[];
/**
 * Original name: static _defName
 */
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/record", _defName);
#endif

#if VERSION_US
void func_800365B0(struct_800365B0_arg0 *arg0, UNK_PTR arg1, s32 arg2) {
    arg0->unk_00 = arg1;
    arg0->unk_04 = arg2;
    arg0->unk_08 = 0;
    arg0->unk_0C = 0;
    arg0->unk_10 = 0;
}
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/record", func_800365C8);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/record", func_8003661C);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/record", func_800366A4);
#endif

#if VERSION_US
/**
 * Original name: dm_init_config_save
 */
void dm_init_config_save(struct_800EF560_unk_B4 *arg0) {
    arg0->unk_00 = 1;
    arg0->unk_01 = 0;
    arg0->unk_02 = 0;
    arg0->unk_03 = 0;
    arg0->unk_04 = 0xA;
    arg0->unk_05 = 1;
    arg0->unk_06 = 0;
    arg0->unk_07 = 1;
    arg0->unk_08 = 1;
    arg0->unk_09[0] = 1;
    arg0->unk_09[1] = 1;
    arg0->unk_0B[0] = 0xA;
    arg0->unk_0B[1] = 0xA;
    arg0->unk_0D[0] = 1;
    arg0->unk_0D[1] = 1;
    arg0->unk_0F[0] = 0;
    arg0->unk_0F[1] = 1;
    arg0->unk_11 = 0;
    arg0->unk_12 = 0;
    arg0->unk_13 = 1;
    arg0->unk_14 = 1;
    arg0->unk_15 = 0xA;
    arg0->unk_16 = 1;
    arg0->unk_17 = 0;
    arg0->unk_18 = 0;
    arg0->unk_19 = 0;
}

void func_8003678C(struct_800F7470 *arg0) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(*arg0->unk_00); i++) {
        arg0->unk_00[0][i] = i % 2;
        arg0->unk_00[1][i] = 0xA;
        arg0->unk_00[2][i] = 1;
        arg0->unk_00[3][i] = i;
        arg0->unk_00[4][i] = 1;
    }

    arg0->unk_14 = 0;
    arg0->unk_15 = 0;
}
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/record", func_800367E0);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/record", func_800367F0);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/record", func_800367FC);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/record", func_80036808);
#endif

#if 0
//? dm_init_config_save(s8 *);                              /* extern */
//? func_800367E0(s8 *);                              /* extern */
//? func_800367F0(s8 *);                              /* extern */
//? func_800367FC(s8 *);                              /* extern */
//? func_80036808(s8 *);                              /* extern */

void dm_init_save_mem(struct_800EF560 *arg0) {
    s32 *var_a0_2;
    s32 var_s0_2;
    s32 var_s1;
    s32 var_s1_2;
    s32 var_s1_3;
    s32 var_s1_4;
    s8 *temp_v0;
    s8 *var_v1;
    struct_800EF560 *var_a1;
    struct_800EF560 *var_v1_2;
    struct_800EF560 *var_v1_3;
    struct_800EF560 *var_v1_4;
    struct_800EF560 *var_v1_5;
    struct_800EF560 *var_v1_6;
    u32 var_a0;
    u32 var_s0;
    u32 var_s0_10;
    u32 var_s0_11;
    u32 var_s0_3;
    u32 var_s0_4;
    u32 var_s0_5;
    u32 var_s0_6;
    u32 var_s0_7;
    u32 var_s0_8;
    u32 var_s0_9;

    var_s0 = 0;
    var_a1 = arg0;
    arg0->unk_00[0] = 0;
    do {
        var_a0 = 0;
        var_v1 = &var_a1->unk_00[8];
loop_2:
        *var_v1 = 0;
        var_a0 += 1;
        var_v1 += 4;
        if (var_a0 < 2U) {
            goto loop_2;
        }
        var_s0 += 1;
        var_a1 += 8;
    } while (var_s0 < 4U);
    var_s0_2 = 0;
    var_a0_2 = evs_default_name;
    do {
        temp_v0 = &arg0->unk_00[var_s0_2];
        var_s0_2 += 1;
        temp_v0->unk_1 = (s8) *var_a0_2;
        var_a0_2 += 4;
    } while (var_s0_2 < 4);
    var_s0_3 = 0;
    var_s1 = 0x28;
    do {
        func_800367E0(&arg0->unk_00[var_s1]);
        var_s0_3 += 1;
        var_s1 += 0xC;
    } while (var_s0_3 < 3U);
    var_s0_4 = 0;
    var_s1_2 = 0x4C;
    do {
        func_800367F0(&arg0->unk_00[var_s1_2]);
        var_s0_4 += 1;
        var_s1_2 += 8;
    } while (var_s0_4 < 3U);
    var_s0_5 = 0;
    var_s1_3 = 0x64;
    do {
        func_800367FC(&arg0->unk_00[var_s1_3]);
        var_s0_5 += 1;
        var_s1_3 += 8;
    } while (var_s0_5 < 3U);
    var_s0_6 = 0;
    var_s1_4 = 0x7C;
    do {
        func_80036808(&arg0->unk_00[var_s1_4]);
        var_s0_6 += 1;
        var_s1_4 += 0xC;
    } while (var_s0_6 < 3U);
    var_s0_7 = 0;
    var_v1_2 = arg0;
    do {
        var_v1_2->unk_A0 = 0;
        var_s0_7 += 1;
        var_v1_2 += 2;
    } while (var_s0_7 < 2U);
    var_s0_8 = 0;
    var_v1_3 = arg0;
    do {
        var_v1_3->unk_A4 = 0;
        var_s0_8 += 1;
        var_v1_3 += 2;
    } while (var_s0_8 < 2U);
    var_s0_9 = 0;
    var_v1_4 = arg0;
    do {
        var_v1_4->unk_A8 = 0;
        var_s0_9 += 1;
        var_v1_4 += 2;
    } while (var_s0_9 < 2U);
    var_s0_10 = 0;
    var_v1_5 = arg0;
    do {
        var_v1_5->unk_AC = 0;
        var_s0_10 += 1;
        var_v1_5 += 2;
    } while (var_s0_10 < 2U);
    var_s0_11 = 0;
    var_v1_6 = arg0;
    do {
        var_v1_6->unk_B0 = 0;
        var_s0_11 += 1;
        var_v1_6 += 2;
    } while (var_s0_11 < 2U);
    dm_init_config_save(&arg0->unk_00[0xB4]);
}
#endif
#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/record", dm_init_save_mem);
#endif

#if VERSION_US
/**
 * Original name: dm_init_system_mem
 */
void dm_init_system_mem(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        evs_default_name[i] = font2index(&_defName[i * 2]);
    }

    evs_stereo = true;
    dm_audio_set_stereo(evs_stereo);
    evs_gamesel = ENUM_EVS_GAMESEL_0;
    evs_secret_flg[1] = 0;
    evs_secret_flg[0] = 0;
    evs_level_21 = 0;
    evs_vs_count = 3;
    evs_score_flag = 1;
}
#endif

#if VERSION_US
#ifdef NON_EQUIVALENT
//#if 1
// maybe equivalent
void dm_story_sort_set(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    s32 temp_t0;
    s32 temp_t1;
    s32 temp_v1;
    s32 var_t2;
    s32 var_v1;
    struct_800EF560_unk_28 *temp_a0;
    struct_800EF560 *temp_t3;
    s32 var_v0;

    arg4 = arg4 / 60;
    temp_t3 = &evs_mem_data[arg0];

    var_t2 = MIN(0x176F, arg4);

    // temp_v1 = arg5 - 1;
    // temp_t1 = temp_v1 & (~temp_v1 >> 0x1F);
    temp_t1 = MAX(arg5 - 1, 0);

    if (arg6 == 0 && (arg2 < 3)) {
        temp_a0 = &temp_t3->unk_28[arg2];
        var_v0 = temp_a0->unk_8;
        var_v1 = temp_t1;
        if (var_v0 == temp_t1) {
            var_v0 = temp_a0->unk_0;
            var_v1 = arg3;
            if (var_v0 == arg3) {
                var_v0 = var_t2;
                var_v0 = var_t2;
                var_v1 = temp_a0->unk_4;
            }
        }
        if (var_v0 < var_v1) {
            temp_a0->unk_0 = arg3;
            temp_a0->unk_4 = var_t2;
            temp_a0->unk_8 = temp_t1;
        }
    }

    temp_t3->unk_08[arg2][arg1] = MAX(temp_t3->unk_08[arg2][arg1], temp_t1);
    temp_t3->unk_08[arg2][arg1] = MIN(temp_t3->unk_08[arg2][arg1], 7);
}
#else
INCLUDE_ASM("asm/us/nonmatchings/main_segment/record", dm_story_sort_set);
#endif
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/record", dm_level_sort_set);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/record", dm_taiQ_sort_set);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/record", dm_timeAt_sort_set);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/record", dm_vscom_set);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/record", dm_vc_fl_set);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/record", dm_vsman_set);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/record", dm_vm_fl_set);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/record", dm_vm_ta_set);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/record", func_80036EC8);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/record", func_80036F1C);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/record", func_80036F70);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/record", func_80037068);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/record", dm_data_mode_story_sort);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/record", dm_data_mode_level_sort);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/record", dm_data_mode_taiQ_sort);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/record", dm_data_mode_timeAt_sort);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/record", func_80037378);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/record", func_800373C8);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/record", func_80037418);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/record", func_80037468);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/record", func_800374B8);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/record", dm_data_vscom_sort);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/record", dm_data_vc_fl_sort);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/record", dm_data_vsman_sort);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/record", dm_data_vm_fl_sort);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/record", dm_data_vm_ta_sort);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/record", func_8003779C);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/record", func_80037808);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/record", func_800378B0);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/record", func_80037950);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/record", func_800379D4);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/record", func_80037A5C);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/record", func_80037B74);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/record", func_80037C7C);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/record", func_80037D40);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/record", func_80037DF0);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/record", func_80037EB4);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/record", func_80037F64);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/record", func_80038038);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/record", func_800380F0);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/record", func_80038168);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/record", func_800381DC);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/record", func_80038254);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/record", func_800382C8);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/record", func_80038340);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/record", func_800383B4);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/record", func_8003842C);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/record", func_800384A0);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/record", func_80038518);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/record", func_8003858C);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/record", func_800386AC);
#endif

#if VERSION_US
/**
 * Original name: EepRom_Init
 */
s32 EepRom_Init(void) {
    EepRom_InitVars();
    if ((u32)(osEepromProbe(&B_800F3E38) - 1) >= 2) {
        func_80038BD0(1);
        return 1;
    }
    return EepRom_ReadAll();
}

/**
 * Original name: EepRom_InitFirst
 */
s32 EepRom_InitFirst(s32 arg0, s32 arg1) {
    EepRom_InitVars();
    if (((u32)(osEepromProbe(&B_800F3E38) - 1) >= 2)) {
        func_80038BD0(1);
        return 1;
    }
    return EepRom_WriteAll(arg0, arg1);
}

void EepRom_InitVars(void) {
    s32 i;

    dm_init_system_mem();
    func_8003678C(&evs_cfg_4p);

    for (i = 0; i < ARRAY_COUNT(evs_mem_data); i++) {
        dm_init_save_mem(&evs_mem_data[i]);
    }
}
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/record", func_80038938);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/record", func_800389A8);
#endif

#if VERSION_US
s32 EepRom_ReadAll(void) {
    struct_800365B0_arg0 sp10;
    char sp28[4];
    s32 temp_s0;
    UNK_PTR temp_v0;

    temp_v0 = func_80038938(1);
    if (temp_v0 == NULL) {
        func_80038BD0(3);
        return 3;
    }

    func_800365B0(&sp10, temp_v0, 0x200);
    temp_s0 = func_800386AC(&sp10, sp28);

    if (bcmp(sp28, eeprom_header, sizeof(eeprom_header)) != 0) {
        return 2;
    }
    if (temp_s0 == 0) {
        return 0;
    }
    return 5;
}
#endif

#if VERSION_US
#if 0
//? func_800365C8(? *, ? *, ?);                       /* extern */
//? func_8003858C(? *);                               /* extern */
//s32 func_800389A8(void *, ? *, ?, s32, s32);        /* extern */

s32 EepRom_WriteAll(s32 arg0, s32 arg1) {
    ? sp18;
    ? sp30;
    void *temp_v0;

    temp_v0 = func_80038938(1);
    if (temp_v0 == NULL) {
        func_80038BD0(3);
        return 3;
    }
    func_800365C8(&sp18, &sp30, 0x200);
    func_8003858C(&sp18);
    if (func_800389A8(temp_v0, &sp30, 0x200, arg0, arg1) == 0) {
        bcopy(&sp30, temp_v0, 0x200);
        return 0;
    }
    func_80038BD0(4);
    return 4;
}
#else
INCLUDE_ASM("asm/us/nonmatchings/main_segment/record", EepRom_WriteAll);
#endif
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/record", func_80038A80_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/record", func_80038A98_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/record", func_80038B08_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/record", func_80038B8C_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/record", func_80038BF8_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/record", func_80038C6C_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/record", func_80038CE0_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/record", func_80038CF0_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/record", func_80038CFC_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/record", func_80038D08_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/record", func_80038D18_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/record", func_80038F04_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/record", func_80038FCC_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/record", func_800390D4_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/record", func_80039130_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/record", func_800391B8_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/record", func_80039254_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/record", func_800392B0_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/record", func_8003930C_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/record", func_80039368_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/record", func_800393C4_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/record", func_80039420_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/record", func_80039480_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/record", func_800394DC_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/record", func_800395DC_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/record", func_800397F4_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/record", func_80039850_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/record", func_800398AC_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/record", func_80039908_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/record", RO_800C4014_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/record", RO_800C4018_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/record", func_80039964_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/record", func_800399B0_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/record", func_800399FC_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/record", func_80039A48_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/record", func_80039A94_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/record", func_80039CF0_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/record", func_80039D1C_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/record", func_80039D48_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/record", func_80039D74_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/record", func_80039DA0_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/record", func_80039DCC_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/record", func_80039E38_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/record", func_80039F34_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/record", func_8003A034_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/record", func_8003A0DC_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/record", func_8003A184_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/record", func_8003A2D8_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/record", func_8003A424_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/record", func_8003A4F4_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/record", func_8003A5BC_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/record", func_8003A68C_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/record", func_8003A754_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/record", func_8003A850_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/record", func_8003A93C_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/record", func_8003A9C0_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/record", func_8003AA44_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/record", func_8003AAC8_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/record", func_8003AB4C_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/record", func_8003ABD0_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/record", func_8003AC54_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/record", func_8003ACD8_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/record", func_8003AD5C_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/record", func_8003ADE0_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/record", func_8003AE64_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/record", func_8003B044_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/record", EepRom_Init);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/record", EepRom_InitFirst);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/record", func_8003B390_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/record", func_8003B410_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/record", func_8003B488_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/record", func_8003B5A0_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/record", EepRom_WriteAll);
#endif

void func_80038BD0(UNK_TYPE arg0 UNUSED) {
}

/**
 * Original name: EepRom_DumpDataSize
 */
void EepRom_DumpDataSize(void) {
}

#if VERSION_US
void RecWritingMsg_init(RecordWritingMessage *recMessage, UNK_PTR *arg1) {
    msgWnd_init(&recMessage->messageWnd, arg1, 0x18, 2, 0, 0);
    recMessage->messageWnd.unk_24 = 1;
    RecWritingMsg_setPos(recMessage, 0, 0);
    recMessage->unk_84 = 0x78;
    recMessage->unk_80 = 0x78;
}

void RecWritingMsg_setStr(RecordWritingMessage *recMessage, const char *arg1) {
    msgWnd_clear(&recMessage->messageWnd);
    msgWnd_addStr(&recMessage->messageWnd, arg1);
    msgWnd_skip(&recMessage->messageWnd);
}

void RecWritingMsg_calc(RecordWritingMessage *recMessage) {
    if (RecWritingMsg_isEnd(recMessage)) {
        return;
    }

    msgWnd_update(&recMessage->messageWnd);
    recMessage->unk_84++;
}

#if VERSION_US
#if 0
//extern u16 D_800897A0;
//extern u16 D_800897A2;
//extern UNK_TYPE D_800897A8;
//extern UNK_TYPE D_800899A8;
void RecWritingMsg_draw(RecordWritingMessage *recMessage, Gfx **gfxP) {
    Gfx *gfx;
    s32 temp_s0;
    s32 temp_v0;
    u32 temp_a1;

    if (RecWritingMsg_isEnd(recMessage)) {
        return;
    }

    gfx = *gfxP;
    temp_s0 = msgWnd_getWidth(&recMessage->messageWnd);
    temp_v0 = msgWnd_getHeight(&recMessage->messageWnd);

    //gfx->words.w0 = 0xDE000000;
    //gfx->words.w1 = (u32) normal_texture_init_dl;
    //gfx += 8;
    gSPDisplayList(gfx++, normal_texture_init_dl);

    temp_a1 = D_800897A0 - temp_s0;
    StretchTexTile8(&gfx, D_800897A0, D_800897A2, &D_800897A8, &D_800899A8, 0, 0, (s32) D_800897A0, (s32) D_800897A2, (f32) (recMessage->messageWnd.unk_28 - ((s32) (temp_a1 + (temp_a1 >> 0x1F)) >> 1)), (f32) (recMessage->messageWnd.unk_2C - ((s32) (D_800897A2 - temp_v0) / 2)), (f32) D_800897A0, (f32) D_800897A2);
    msgWnd_draw(&recMessage->messageWnd, &gfx);
    *gfxP = gfx;
}
#else
INCLUDE_ASM("asm/us/nonmatchings/main_segment/record", RecWritingMsg_draw);
#endif
#endif

void RecWritingMsg_start(RecordWritingMessage *recMessage) {
    recMessage->unk_84 = 0;
}

void RecWritingMsg_end(RecordWritingMessage *recMessage) {
    recMessage->unk_84 = recMessage->unk_80;
}

bool RecWritingMsg_isEnd(RecordWritingMessage *recMessage) {
    return (recMessage->unk_84 >= recMessage->unk_80);
}

void RecWritingMsg_setPos(RecordWritingMessage *recMessage, s32 arg1, s32 arg2) {
    recMessage->messageWnd.unk_28 = arg1;
    recMessage->messageWnd.unk_2C = arg2;
}
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/record", setSleepTimer);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/record", RecWritingMsg_init);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/record", func_8003B7F8_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/record", RecWritingMsg_calc);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/record", func_8003B8C0_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/record", func_8003BA50_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/record", func_8003BA58_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/record", func_8003BA64_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/record", func_8003BA78_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/record", func_8003BA84_cn);
#endif

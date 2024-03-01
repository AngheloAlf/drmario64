/**
 * Original filename: record.c
 */

#include "record.h"
#include "include_asm.h"
#include "macros_defines.h"
#include "unknown_structs.h"
#include "boot_functions.h"
#include "boot_variables.h"
#include "main_segment_variables.h"
#include "recwritingmsg.h"
#include "main_menu.h"
#include "main1x.h"
#include "tex_func.h"
#include "libc/assert.h"
#include "font.h"

#if VERSION_US || CC_CHECK
#include "audio/sound.h"
#endif

#if VERSION_US
#define MESS_PANEL_TEX_WIDTH 200
#define MESS_PANEL_TEX_HEIGHT 69

struct_mess_panel_tex_size mess_panel_tex_size = { MESS_PANEL_TEX_WIDTH, MESS_PANEL_TEX_HEIGHT, 8, 1 };

u16 mess_panel_lut[] ALIGNED8 = {
#include "main_segment/record/mess_panel_tex.palette.inc"
};

u8 mess_panel_tex[] ALIGNED8 = {
#include "main_segment/record/mess_panel_tex.ci8.inc"
};

static_assert(sizeof(mess_panel_tex) == MESS_PANEL_TEX_WIDTH * MESS_PANEL_TEX_HEIGHT * sizeof(u8),
              "Texture does not have the expected resolution");

bool _cached_1332 = false;
#endif

/**
 * Original name: eeprom_header
 */
const CHAR_SIGNED char eeprom_header[4] = "DM64";

/**
 * Original name: eeprom_header_bits
 */
const CHAR_SIGNED char eeprom_header_bits[4] = {
    7, // ceil(log2('D'))
    7, // ceil(log2('M'))
    6, // ceil(log2('6'))
    6, // ceil(log2('4'))
};

#if CC_CHECK
#define DEFNAME_LEN
#else
#define DEFNAME_LEN 4 * 2
#endif

/**
 * Original name: static _defName
 */
const char _defName[DEFNAME_LEN] =
#if VERSION_US || VERSION_GW
    "ＮＥＷ　"
#elif VERSION_CN
    "　　　　"
#endif
    ;

void func_800365B0(struct_800365B0_arg0 *arg0, u8 *buffer, size_t size) {
    arg0->buffer = buffer;
    arg0->size = size;
    arg0->unk_08 = 0;
    arg0->unk_0C = 0;
    arg0->unk_10 = 0;
}

void func_800365C8(struct_800365B0_arg0 *arg0, u8 *buffer, size_t size) {
    bzero(buffer, size);
    func_800365B0(arg0, buffer, size);
}

/**
 * Original name: BitField_PutBit
 */
void BitField_PutBit(struct_800365B0_arg0 *arg0, s32 arg1, u32 arg2) {
    s32 i;

    arg0->unk_10 += arg2 & ((1 << arg1) - 1);
    for (i = arg1 - 1; i >= 0; i--) {
        arg0->buffer[arg0->unk_08] |= (((arg2 >> i) & 1) << arg0->unk_0C);

        arg0->unk_0C++;
        arg0->unk_08 += arg0->unk_0C >> 3;
        arg0->unk_0C &= 7;
    }
}

/**
 * Original name: BitField_GetBit
 */
s32 BitField_GetBit(struct_800365B0_arg0 *arg0, s32 arg1) {
    s32 var_t1 = 0;
    s32 i;

    for (i = arg1 - 1; i >= 0; i--) {
        var_t1 |= ((arg0->buffer[arg0->unk_08] >> arg0->unk_0C) & 1) << i;
        arg0->unk_0C++;
        arg0->unk_08 += arg0->unk_0C >> 3;
        arg0->unk_0C &= 7;
    }

    arg0->unk_10 += var_t1;
    return var_t1;
}

/**
 * Original name: dm_init_config_save
 */
void dm_init_config_save(struct_evs_mem_data_unk_B4 *arg0) {
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

void func_8003678C(struct_evs_cfg_4p *arg0) {
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

void func_800367E0(struct_evs_mem_data_unk_28 *arg0) {
    arg0->unk_0 = 0;
    arg0->unk_4 = 0;
    arg0->unk_8 = 0;
}

void func_800367F0(struct_evs_mem_data_unk_4C *arg0) {
    arg0->unk_0 = 0;
    arg0->unk_4 = 0;
}

void func_800367FC(struct_evs_mem_data_unk_64 *arg0) {
    arg0->unk_0 = 0;
    arg0->unk_4 = 0;
}

void func_80036808(struct_evs_mem_data_unk_7C *arg0) {
    arg0->unk_0 = 0;
    arg0->unk_4 = 0;
    arg0->unk_8 = 0;
}

/**
 * Original name: dm_init_save_mem
 */
void dm_init_save_mem(struct_evs_mem_data *arg0) {
    s32 i;
    s32 j;

    arg0->unk_00 = 0;

    for (i = 0; i < ARRAY_COUNTU(arg0->unk_08); i++) {
        for (j = 0; j < ARRAY_COUNTU(arg0->unk_08[i]); j++) {
            arg0->unk_08[i][j] = 0;
        }
    }

    for (i = 0; i < ARRAY_COUNT(arg0->unk_01); i++) {
        arg0->unk_01[i] = evs_default_name[i];
    }

    for (i = 0; i < ARRAY_COUNTU(arg0->unk_28); i++) {
        func_800367E0(&arg0->unk_28[i]);
    }

    for (i = 0; i < ARRAY_COUNTU(arg0->unk_4C); i++) {
        func_800367F0(&arg0->unk_4C[i]);
    }

    for (i = 0; i < ARRAY_COUNTU(arg0->unk_64); i++) {
        func_800367FC(&arg0->unk_64[i]);
    }

    for (i = 0; i < ARRAY_COUNTU(arg0->unk_7C); i++) {
        func_80036808(&arg0->unk_7C[i]);
    }

    for (i = 0; i < ARRAY_COUNTU(arg0->unk_A0); i++) {
        arg0->unk_A0[i] = 0;
    }

    for (i = 0; i < ARRAY_COUNTU(arg0->unk_A4); i++) {
        arg0->unk_A4[i] = 0;
    }

    for (i = 0; i < ARRAY_COUNTU(arg0->unk_A8); i++) {
        arg0->unk_A8[i] = 0;
    }

    for (i = 0; i < ARRAY_COUNTU(arg0->unk_AC); i++) {
        arg0->unk_AC[i] = 0;
    }

    for (i = 0; i < ARRAY_COUNTU(arg0->unk_B0); i++) {
        arg0->unk_B0[i] = 0;
    }

    dm_init_config_save(&arg0->unk_B4);
}

/**
 * Original name: dm_init_system_mem
 */
void dm_init_system_mem(void) {
    s32 i;
    s32 temp;

    for (i = 0; i < 4; i++) {
        evs_default_name[i] = font2index(&_defName[i * 2]);
    }

    evs_stereo = true;
    temp = 1;
    dm_audio_set_stereo(evs_stereo);
    evs_gamesel = ENUM_EVS_GAMESEL_0;
    evs_secret_flg[temp] = 0;
    evs_secret_flg[0] = 0;
    evs_level_21 = 0;
    evs_vs_count = 3;
    evs_score_flag = 1;
}

/**
 * Original name: dm_story_sort_set
 */
void dm_story_sort_set(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    struct_evs_mem_data *temp_t3 = &evs_mem_data[arg0];

    arg4 = arg4 / 60;
    arg4 = MIN(0x176F, arg4);

    arg5 = MAX(0, arg5 - 1);

    if ((arg6 == 0) && (arg2 < 3)) {
        struct_evs_mem_data_unk_28 *temp_t1 = &temp_t3->unk_28[arg2];
        s32 var_v0_2 = temp_t1->unk_8;
        s32 var_t0 = arg5;

        if (var_v0_2 == arg5) {
            var_v0_2 = temp_t1->unk_0;
            var_t0 = arg3;
            if (var_v0_2 == arg3) {
                var_v0_2 = arg4;
                var_t0 = temp_t1->unk_4;
            }
        }

        if (var_v0_2 < var_t0) {
            temp_t1->unk_0 = arg3;
            temp_t1->unk_4 = arg4;
            temp_t1->unk_8 = arg5;
        }
    }

    temp_t3->unk_08[arg2][arg1] = MAX(temp_t3->unk_08[arg2][arg1], arg5);
    temp_t3->unk_08[arg2][arg1] = MIN(temp_t3->unk_08[arg2][arg1], 7);
}

/**
 * Original name: dm_level_sort_set
 */
void dm_level_sort_set(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    struct_evs_mem_data *ptr = &evs_mem_data[arg0];
    struct_evs_mem_data_unk_4C *temp_a0;
    s32 var_v0;
    s32 var_v1;

    temp_a0 = &ptr->unk_4C[arg1];
    var_v0 = temp_a0->unk_4;
    var_v1 = arg3;

    //! FAKE: ?
    do {
        if (temp_a0->unk_4 == arg3) {
            var_v0 = temp_a0->unk_0;
            var_v1 = arg2;
        }
    } while (0);

    if (var_v0 < var_v1) {
        temp_a0->unk_0 = arg2;
        temp_a0->unk_4 = arg3;
    }
}

/**
 * Original name: dm_taiQ_sort_set
 */
void dm_taiQ_sort_set(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    struct_evs_mem_data *ptr;
    struct_evs_mem_data_unk_64 *temp_a1;
    s32 var_a0;
    s32 var_v0;

    ptr = &evs_mem_data[arg0];
    temp_a1 = &ptr->unk_64[arg1];

    arg3 = arg3 / 60;
    arg3 = MIN(5999, arg3);

    var_v0 = temp_a1->unk_0;
    var_a0 = arg2;

    if (var_v0 == var_a0) {
        var_v0 = temp_a1->unk_4;
        var_a0 = arg3;
    }

    if (var_v0 < var_a0) {
        temp_a1->unk_0 = arg2;
        temp_a1->unk_4 = arg3;
    }
}

/**
 * Original name: dm_timeAt_sort_set
 */
void dm_timeAt_sort_set(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    struct_evs_mem_data *ptr;
    s32 var_a1;
    s32 var_v0;
    struct_evs_mem_data_unk_7C *temp_v1;

    ptr = &evs_mem_data[arg0];
    temp_v1 = &ptr->unk_7C[arg1];

    arg3 = arg3 / 6;
    arg3 = MIN(1800, arg3);

    var_v0 = temp_v1->unk_0;
    var_a1 = arg2;

    if (var_v0 == var_a1) {
        var_a1 = temp_v1->unk_4;
        var_v0 = arg3;
        if (var_v0 == var_a1) {
            var_v0 = temp_v1->unk_8;
            var_a1 = arg4;
        }
    }

    if (var_v0 < var_a1) {
        temp_v1->unk_0 = arg2;
        temp_v1->unk_4 = arg3;
        temp_v1->unk_8 = arg4;
    }
}

/**
 * Original name: dm_vscom_set
 */
void dm_vscom_set(s32 arg0, s32 arg1, s32 arg2) {
    struct_evs_mem_data *temp_a3 = &evs_mem_data[arg0];

    temp_a3->unk_A0[0] = MIN(0x63, temp_a3->unk_A0[0] + arg1);
    temp_a3->unk_A0[1] = MIN(0x63, temp_a3->unk_A0[1] + arg2);
}

/**
 * Original name: dm_vc_fl_set
 */
void dm_vc_fl_set(s32 arg0, s32 arg1, s32 arg2) {
    struct_evs_mem_data *temp_a3 = &evs_mem_data[arg0];

    temp_a3->unk_A4[0] = MIN(0x63, temp_a3->unk_A4[0] + arg1);
    temp_a3->unk_A4[1] = MIN(0x63, temp_a3->unk_A4[1] + arg2);
}

/**
 * Original name: dm_vsman_set
 */
void dm_vsman_set(s32 arg0, s32 arg1, s32 arg2) {
    struct_evs_mem_data *temp_a3 = &evs_mem_data[arg0];

    temp_a3->unk_A8[0] = MIN(0x63, temp_a3->unk_A8[0] + arg1);
    temp_a3->unk_A8[1] = MIN(0x63, temp_a3->unk_A8[1] + arg2);
}

/**
 * Original name: dm_vm_fl_set
 */
void dm_vm_fl_set(s32 arg0, s32 arg1, s32 arg2) {
    struct_evs_mem_data *temp_a3 = &evs_mem_data[arg0];

    temp_a3->unk_AC[0] = MIN(0x63, temp_a3->unk_AC[0] + arg1);
    temp_a3->unk_AC[1] = MIN(0x63, temp_a3->unk_AC[1] + arg2);
}

/**
 * Original name: dm_vm_ta_set
 */
void dm_vm_ta_set(s32 arg0, s32 arg1, s32 arg2) {
    struct_evs_mem_data *temp_a3 = &evs_mem_data[arg0];

    temp_a3->unk_B0[0] = MIN(0x63, temp_a3->unk_B0[0] + arg1);
    temp_a3->unk_B0[1] = MIN(0x63, temp_a3->unk_B0[1] + arg2);
}

// Maybe arg1 is an enum?
u8 *func_80036EC8(MenuRank_unk_001C *arg0, u32 arg1, s32 arg2) {
    u8 *ret;

    switch (arg1) {
        case 0x0:
            ret = arg0->unk_000[arg2];
            break;

        case 0x1:
            ret = arg0->unk_030[arg2];
            break;

        case 0x2:
            ret = arg0->unk_060[arg2];
            break;

        case 0x3:
            ret = arg0->unk_090[arg2];
            break;
    }

    return ret;
}

u8 *func_80036F1C(MenuRank_unk_001C *arg0, u32 arg1, s32 arg2) {
    u8 *ret;

    switch (arg1) {
        case 0x0:
            ret = arg0->unk_018[arg2];
            break;

        case 0x1:
            ret = arg0->unk_048[arg2];
            break;

        case 0x2:
            ret = arg0->unk_078[arg2];
            break;

        case 0x3:
            ret = arg0->unk_0A8[arg2];
            break;
    }

    return ret;
}

/**
 * Original name: _get1PLess
 */
bool _get1PLess(struct_evs_mem_data *arg0, struct_evs_mem_data *arg1, u32 arg2, s32 arg3) {
    s32 var_t0;
    s32 var_v1;

    switch (arg2) {
        case 0x0: {
            struct_evs_mem_data_unk_28 *temp_a0;
            struct_evs_mem_data_unk_28 *temp_a1;

            temp_a0 = &arg0->unk_28[arg3];
            temp_a1 = &arg1->unk_28[arg3];
            var_t0 = temp_a0->unk_8;
            var_v1 = temp_a1->unk_8;
            if (var_t0 == var_v1) {
                var_t0 = temp_a0->unk_0;
                var_v1 = temp_a1->unk_0;
                if (var_t0 == var_v1) {
                    var_t0 = temp_a1->unk_4;
                    var_v1 = temp_a0->unk_4;
                }
            }
        } break;

        case 0x1: {

            struct_evs_mem_data_unk_4C *temp_0;
            struct_evs_mem_data_unk_4C *temp_1;

            temp_0 = &arg0->unk_4C[arg3];
            temp_1 = &arg1->unk_4C[arg3];
            var_t0 = temp_0->unk_4;
            var_v1 = temp_1->unk_4;
            if (var_t0 == var_v1) {
                var_t0 = temp_0->unk_0;
                var_v1 = temp_1->unk_0;
            }
        } break;

        case 0x2: {
            struct_evs_mem_data_unk_64 *var_a0;
            struct_evs_mem_data_unk_64 *var_a1;
            var_a0 = &arg0->unk_64[arg3];
            var_a1 = &arg1->unk_64[arg3];
            var_t0 = var_a0->unk_4;
            var_v1 = var_a1->unk_4;
            if (var_t0 == var_v1) {
                var_t0 = var_a0->unk_0;
                var_v1 = var_a1->unk_0;
            }
        } break;

        case 0x3: {
            struct_evs_mem_data_unk_7C *temp_a0_2;
            struct_evs_mem_data_unk_7C *temp_a1_2;
            temp_a0_2 = &arg0->unk_7C[arg3];
            temp_a1_2 = &arg1->unk_7C[arg3];
            var_t0 = temp_a0_2->unk_0;
            var_v1 = temp_a1_2->unk_0;
            if (var_t0 == var_v1) {
                var_t0 = temp_a1_2->unk_4;
                var_v1 = temp_a0_2->unk_4;
                if (var_t0 == var_v1) {
                    var_t0 = temp_a0_2->unk_8;
                    var_v1 = temp_a1_2->unk_8;
                }
            }
        } break;
    }

    return var_t0 < var_v1;
}

// TODO: arg1 enum?
/**
 * Original name: _sort1PMode
 */
void _sort1PMode(MenuRank_unk_001C *arg0, u32 arg1, s32 arg2) {
    struct_evs_mem_data *ptr = evs_mem_data;
    u8 *temp_s6 = func_80036EC8(arg0, arg1, arg2);
    u8 *sp18 = func_80036F1C(arg0, arg1, arg2);
    s32 i;
    s32 var_s1;

    for (i = 0; i < 8; i++) {
        temp_s6[i] = i;
    }

    i = 0;
    while (i < 7) {
        s32 j;

        for (j = i + 1; j < 8; j++) {
            s32 temp_s1 = ptr[temp_s6[i]].unk_00 & 1;
            s32 temp_s0 = ptr[temp_s6[j]].unk_00 & 1;

            if (_get1PLess(&ptr[temp_s6[i]], &ptr[temp_s6[j]], arg1, arg2) || (temp_s1 < temp_s0)) {
                u8 temp_v1_2 = temp_s6[i];

                temp_s6[i] = temp_s6[j];
                temp_s6[j] = temp_v1_2;
            }
        }

        i++;
    }

    sp18[0] = var_s1 = 1;
    for (i = 1; i < 8; i++) {
        if (_get1PLess(&ptr[temp_s6[i]], &ptr[temp_s6[i - 1]], arg1, arg2)) {
            var_s1 += 1;
        }
        sp18[i] = var_s1;
    }
}

/**
 * Original name: dm_data_mode_story_sort
 */
void dm_data_mode_story_sort(MenuRank_unk_001C *arg0) {
    s32 i;

    for (i = 0; i < 3; i++) {
        _sort1PMode(arg0, 0, i);
    }
}

/**
 * Original name: dm_data_mode_level_sort
 */
void dm_data_mode_level_sort(MenuRank_unk_001C *arg0) {
    s32 i;

    for (i = 0; i < 3; i++) {
        _sort1PMode(arg0, 1, i);
    }
}

/**
 * Original name: dm_data_mode_taiQ_sort
 */
void dm_data_mode_taiQ_sort(MenuRank_unk_001C *arg0) {
    s32 i;

    for (i = 0; i < 3; i++) {
        _sort1PMode(arg0, 2, i);
    }
}

/**
 * Original name: dm_data_mode_timeAt_sort
 */
void dm_data_mode_timeAt_sort(MenuRank_unk_001C *arg0) {
    s32 i;

    for (i = 0; i < 3; i++) {
        _sort1PMode(arg0, 3, i);
    }
}

u16 *func_80037378(struct_evs_mem_data *arg0, u32 arg1) {
    u16 *var_v1;

    switch (arg1) {
        case 0x0:
            var_v1 = arg0->unk_A0;
            break;

        case 0x1:
            var_v1 = arg0->unk_A4;
            break;

        case 0x2:
            var_v1 = arg0->unk_A8;
            break;

        case 0x3:
            var_v1 = arg0->unk_AC;
            break;

        case 0x4:
            var_v1 = arg0->unk_B0;
            break;
    }

    return var_v1;
}

u8 *func_800373C8(MenuRank_unk_001C *arg0, u32 arg1) {
    u8 *var_v1;

    switch (arg1) {
        case 0x0:
            var_v1 = arg0->unk_0C0;
            break;

        case 0x1:
            var_v1 = arg0->unk_0E0;
            break;

        case 0x2:
            var_v1 = arg0->unk_100;
            break;

        case 0x3:
            var_v1 = arg0->unk_120;
            break;

        case 0x4:
            var_v1 = arg0->unk_140;
            break;
    }

    return var_v1;
}

u8 *func_80037418(MenuRank_unk_001C *arg0, u32 arg1) {
    u8 *var_v1;

    switch (arg1) {
        case 0x0:
            var_v1 = arg0->unk_0C8;
            break;

        case 0x1:
            var_v1 = arg0->unk_0E8;
            break;

        case 0x2:
            var_v1 = arg0->unk_108;
            break;

        case 0x3:
            var_v1 = arg0->unk_128;
            break;

        case 0x4:
            var_v1 = arg0->unk_148;
            break;
    }

    return var_v1;
}

u16 *func_80037468(MenuRank_unk_001C *arg0, u32 arg1) {
    u16 *var_v1;

    switch (arg1) {
        case 0x0:
            var_v1 = arg0->unk_0D0;
            break;
        case 0x1:
            var_v1 = arg0->unk_0F0;
            break;
        case 0x2:
            var_v1 = arg0->unk_110;
            break;
        case 0x3:
            var_v1 = arg0->unk_130;
            break;
        case 0x4:
            var_v1 = arg0->unk_150;
            break;
    }

    return var_v1;
}

// TODO: arg1 enum?
/**
 * Original name: _sortVsMode
 */
void _sortVsMode(MenuRank_unk_001C *arg0, u32 arg1) {
    struct_evs_mem_data *ptr = evs_mem_data;
    u8 *temp_s4 = func_800373C8(arg0, arg1);
    u8 *temp_s7 = func_80037418(arg0, arg1);
    u16 *temp_v0 = func_80037468(arg0, arg1);
    s32 i;
    s32 var_a0;
    u16 var_a1;

    for (i = 0; i < 8; i++) {
        u16 *temp_a1 = func_80037378(&ptr[i], arg1);

        temp_s4[i] = i;
        if ((temp_a1[0] != 0) || (temp_a1[1] != 0)) {
            temp_v0[i] = (temp_a1[0] * 0x3E8) / (temp_a1[0] + temp_a1[1]);
        } else {
            temp_v0[i] = 0;
        }
    }

    for (i = 0; i < 7; i++) {
        s32 j;

        for (j = i + 1; j < 8; j++) {
            u8 temp_t1 = temp_s4[i];
            u8 temp_t0 = temp_s4[j];
            s32 temp_a0;
            s32 temp_a1_2;

            temp_a0 = temp_v0[temp_t1];
            temp_a1_2 = temp_v0[temp_t0];
            if (temp_a0 == temp_a1_2) {
                temp_a0 = ptr[temp_t1].unk_00 & 1;
                temp_a1_2 = ptr[temp_t0].unk_00 & 1;
            }

            if (temp_a0 < temp_a1_2) {
                temp_s4[i] = temp_t0;
                temp_s4[j] = temp_t1;
            }
        }
    }

    var_a1 = temp_v0[temp_s4[0]];

    temp_s7[0] = var_a0 = 1;
    for (i = 1; i < 8; i++) {
        u16 temp_v0_2;

        temp_v0_2 = temp_v0[temp_s4[i]];
        if (temp_v0_2 != var_a1) {
            var_a1 = temp_v0_2;
            var_a0++;
        }

        temp_s7[i] = var_a0;
    }
}

/**
 * Original name: dm_data_vscom_sort
 */
void dm_data_vscom_sort(MenuRank_unk_001C *arg0) {
    _sortVsMode(arg0, 0);
}

/**
 * Original name: dm_data_vc_fl_sort
 */
void dm_data_vc_fl_sort(MenuRank_unk_001C *arg0) {
    _sortVsMode(arg0, 1);
}

/**
 * Original name: dm_data_vsman_sort
 */
void dm_data_vsman_sort(MenuRank_unk_001C *arg0) {
    _sortVsMode(arg0, 2);
}

/**
 * Original name: dm_data_vm_fl_sort
 */
void dm_data_vm_fl_sort(MenuRank_unk_001C *arg0) {
    _sortVsMode(arg0, 3);
}

/**
 * Original name: dm_data_vm_ta_sort
 */
void dm_data_vm_ta_sort(MenuRank_unk_001C *arg0) {
    _sortVsMode(arg0, 4);
}

void func_8003779C(u8 arg0[4], s32 *arg1, s32 *arg2) {
    s32 var_t1 = 0;
    s32 var_t0 = 0;
    s32 i;

    for (i = 0; i < 4; i++) {
        if (arg0[i] != 0) {
            var_t0 = i;
            break;
        }
    }

    for (; i < 4; i++) {
        if (arg0[i] != 0) {
            var_t1 = i + 1;
        }
    }

    *arg1 = var_t0;
    *arg2 = var_t1 - var_t0;
}

void func_80037808(struct_800365B0_arg0 *arg0) {
    BitField_PutBit(arg0, 1, evs_stereo != 0);
    BitField_PutBit(arg0, 1, evs_secret_flg[0] != 0);
    BitField_PutBit(arg0, 1, evs_secret_flg[1] != 0);
    BitField_PutBit(arg0, 1, evs_level_21 != 0);
    BitField_PutBit(arg0, 2, evs_vs_count);
    BitField_PutBit(arg0, 1, evs_score_flag != 0);
}

void func_800378B0(struct_800365B0_arg0 *arg0) {
    evs_stereo = BitField_GetBit(arg0, 1);
    evs_secret_flg[0] = BitField_GetBit(arg0, 1);
    evs_secret_flg[1] = BitField_GetBit(arg0, 1);
    evs_level_21 = BitField_GetBit(arg0, 1);
    evs_vs_count = BitField_GetBit(arg0, 2);
    evs_score_flag = BitField_GetBit(arg0, 1);
    dm_audio_set_stereo(evs_stereo);
}

void func_80037950(struct_800365B0_arg0 *arg0, s32 arg1) {
    struct_evs_mem_data *temp_v1 = &evs_mem_data[arg1];
    s32 i;

    BitField_PutBit(arg0, 2, temp_v1->unk_00);

    for (i = 0; i < ARRAY_COUNTU(temp_v1->unk_01); i++) {
        BitField_PutBit(arg0, 8, temp_v1->unk_01[i]);
    }
}

void func_800379D4(struct_800365B0_arg0 *arg0, s32 arg1) {
    struct_evs_mem_data *temp_s0 = &evs_mem_data[arg1];
    s32 i;

    temp_s0->unk_00 = BitField_GetBit(arg0, 2);
    for (i = 0; i < ARRAY_COUNTU(temp_s0->unk_01); i++) {
        temp_s0->unk_01[i] = BitField_GetBit(arg0, 8);
    }
}

/**
 * Original name: RecStory_Compress
 */
void RecStory_Compress(struct_800365B0_arg0 *arg0, s32 arg1) {
    struct_evs_mem_data *temp_s4 = &evs_mem_data[arg1];
    s32 i;

    for (i = 0; i < ARRAY_COUNTU(temp_s4->unk_08); i++) {
        s32 j;

        for (j = 0; j < ARRAY_COUNTU(temp_s4->unk_08[i]); j++) {
            BitField_PutBit(arg0, 3, temp_s4->unk_08[i][j]);
        }
    }

    for (i = 0; i < ARRAY_COUNTU(temp_s4->unk_28); i++) {
        struct_evs_mem_data_unk_28 *temp = &temp_s4->unk_28[i];

        BitField_PutBit(arg0, 0x11, temp->unk_0 / 0x64U);
        BitField_PutBit(arg0, 0xD, temp->unk_4);
        BitField_PutBit(arg0, 4, temp->unk_8);
    }
}

/**
 * Original name: RecStory_Extract
 */
void RecStory_Extract(struct_800365B0_arg0 *arg0, s32 arg1) {
    struct_evs_mem_data *temp_s4 = &evs_mem_data[arg1];
    s32 i;

    for (i = 0; i < ARRAY_COUNTU(temp_s4->unk_08); i++) {
        s32 j;

        for (j = 0; j < ARRAY_COUNTU(temp_s4->unk_08[i]); j++) {
            temp_s4->unk_08[i][j] = BitField_GetBit(arg0, 3);
        }
    }

    for (i = 0; i < ARRAY_COUNTU(temp_s4->unk_28); i++) {
        struct_evs_mem_data_unk_28 *temp_s0;

        temp_s0 = &temp_s4->unk_28[i];
        temp_s0->unk_0 = BitField_GetBit(arg0, 0x11) * 0x64;
        temp_s0->unk_4 = BitField_GetBit(arg0, 0xD);
        temp_s0->unk_8 = BitField_GetBit(arg0, 4);
    }
}

void func_80037C7C(struct_800365B0_arg0 *arg0, s32 arg1) {
    struct_evs_mem_data *temp_v0 = &evs_mem_data[arg1];
    s32 i;

    for (i = 0; i < ARRAY_COUNTU(temp_v0->unk_4C); i++) {
        struct_evs_mem_data_unk_4C *temp = &temp_v0->unk_4C[i];

        BitField_PutBit(arg0, 0x11, temp->unk_0 / 0x64U);
        BitField_PutBit(arg0, 7, temp->unk_4);
    }
}

void func_80037D40(struct_800365B0_arg0 *arg0, s32 arg1) {
    struct_evs_mem_data *temp_v0 = &evs_mem_data[arg1];
    s32 i;

    for (i = 0; i < ARRAY_COUNTU(temp_v0->unk_4C); i++) {
        struct_evs_mem_data_unk_4C *temp = &temp_v0->unk_4C[i];

        temp->unk_0 = BitField_GetBit(arg0, 0x11) * 0x64;
        temp->unk_4 = BitField_GetBit(arg0, 7);
    }
}

void func_80037DF0(struct_800365B0_arg0 *arg0, s32 arg1) {
    struct_evs_mem_data *temp_v0 = &evs_mem_data[arg1];
    s32 i;

    for (i = 0; i < ARRAY_COUNTU(temp_v0->unk_64); i++) {
        struct_evs_mem_data_unk_64 *temp = &temp_v0->unk_64[i];

        BitField_PutBit(arg0, 0x11, temp->unk_0 / 0x64U);
        BitField_PutBit(arg0, 0xD, temp->unk_4);
    }
}

void func_80037EB4(struct_800365B0_arg0 *arg0, s32 arg1) {
    struct_evs_mem_data *temp_v0 = &evs_mem_data[arg1];
    s32 i;

    for (i = 0; i < ARRAY_COUNTU(temp_v0->unk_64); i++) {
        struct_evs_mem_data_unk_64 *temp = &temp_v0->unk_64[i];

        temp->unk_0 = BitField_GetBit(arg0, 0x11) * 0x64;
        temp->unk_4 = BitField_GetBit(arg0, 0xD);
    }
}

void func_80037F64(struct_800365B0_arg0 *arg0, s32 arg1) {
    struct_evs_mem_data *temp_v0 = &evs_mem_data[arg1];
    s32 i;

    for (i = 0; i < ARRAY_COUNTU(temp_v0->unk_7C); i++) {
        struct_evs_mem_data_unk_7C *temp = &temp_v0->unk_7C[i];

        BitField_PutBit(arg0, 0x10, temp->unk_0 / 0xAU);
        BitField_PutBit(arg0, 0xB, temp->unk_4);
        BitField_PutBit(arg0, 6, temp->unk_8);
    }
}

void func_80038038(struct_800365B0_arg0 *arg0, s32 arg1) {
    struct_evs_mem_data *temp_v0 = &evs_mem_data[arg1];
    s32 i;

    for (i = 0; i < ARRAY_COUNTU(temp_v0->unk_7C); i++) {
        struct_evs_mem_data_unk_7C *temp = &temp_v0->unk_7C[i];

        temp->unk_0 = BitField_GetBit(arg0, 0x10) * 0xA;
        temp->unk_4 = BitField_GetBit(arg0, 0xB);
        temp->unk_8 = BitField_GetBit(arg0, 6);
    }
}

void func_800380F0(struct_800365B0_arg0 *arg0, s32 arg1) {
    struct_evs_mem_data *temp_v0 = &evs_mem_data[arg1];
    s32 i;

    for (i = 0; i < ARRAY_COUNTU(temp_v0->unk_A0); i++) {
        BitField_PutBit(arg0, 7, temp_v0->unk_A0[i]);
    }
}

void func_80038168(struct_800365B0_arg0 *arg0, s32 arg1) {
    struct_evs_mem_data *temp_v0 = &evs_mem_data[arg1];
    s32 i;

    for (i = 0; i < ARRAY_COUNTU(temp_v0->unk_A0); i++) {
        temp_v0->unk_A0[i] = BitField_GetBit(arg0, 7);
    }
}

void func_800381DC(struct_800365B0_arg0 *arg0, s32 arg1) {
    struct_evs_mem_data *temp_v0 = &evs_mem_data[arg1];
    s32 i;

    for (i = 0; i < ARRAY_COUNTU(temp_v0->unk_A4); i++) {
        BitField_PutBit(arg0, 7, temp_v0->unk_A4[i]);
    }
}

void func_80038254(struct_800365B0_arg0 *arg0, s32 arg1) {
    struct_evs_mem_data *temp_v0 = &evs_mem_data[arg1];
    s32 i;

    for (i = 0; i < ARRAY_COUNTU(temp_v0->unk_A4); i++) {
        temp_v0->unk_A4[i] = BitField_GetBit(arg0, 7);
    }
}

void func_800382C8(struct_800365B0_arg0 *arg0, s32 arg1) {
    struct_evs_mem_data *temp_v0 = &evs_mem_data[arg1];
    s32 i;

    for (i = 0; i < ARRAY_COUNTU(temp_v0->unk_A8); i++) {
        BitField_PutBit(arg0, 7, temp_v0->unk_A8[i]);
    }
}

void func_80038340(struct_800365B0_arg0 *arg0, s32 arg1) {
    struct_evs_mem_data *temp_v0 = &evs_mem_data[arg1];
    s32 i;

    for (i = 0; i < ARRAY_COUNTU(temp_v0->unk_A8); i++) {
        temp_v0->unk_A8[i] = BitField_GetBit(arg0, 7);
    }
}

void func_800383B4(struct_800365B0_arg0 *arg0, s32 arg1) {
    struct_evs_mem_data *temp_v0 = &evs_mem_data[arg1];
    s32 i;

    for (i = 0; i < ARRAY_COUNTU(temp_v0->unk_AC); i++) {
        BitField_PutBit(arg0, 7, temp_v0->unk_AC[i]);
    }
}

void func_8003842C(struct_800365B0_arg0 *arg0, s32 arg1) {
    struct_evs_mem_data *temp_v0 = &evs_mem_data[arg1];
    s32 i;

    for (i = 0; i < ARRAY_COUNTU(temp_v0->unk_AC); i++) {
        temp_v0->unk_AC[i] = BitField_GetBit(arg0, 7);
    }
}

void func_800384A0(struct_800365B0_arg0 *arg0, s32 arg1) {
    struct_evs_mem_data *temp_v0 = &evs_mem_data[arg1];
    s32 i;

    for (i = 0; i < ARRAY_COUNTU(temp_v0->unk_B0); i++) {
        BitField_PutBit(arg0, 7, temp_v0->unk_B0[i]);
    }
}

void func_80038518(struct_800365B0_arg0 *arg0, s32 arg1) {
    struct_evs_mem_data *temp_v0 = &evs_mem_data[arg1];
    s32 i;

    for (i = 0; i < ARRAY_COUNTU(temp_v0->unk_B0); i++) {
        temp_v0->unk_B0[i] = BitField_GetBit(arg0, 7);
    }
}

/**
 * Original name: RecAll_Compress
 */
void RecAll_Compress(struct_800365B0_arg0 *arg0) {
    s32 i;

    arg0->unk_10 = 0;
    func_80037808(arg0);
    BitField_PutBit(arg0, 4, arg0->unk_10);

    for (i = 0; i < 8; i++) {
        arg0->unk_10 = 0;
        func_80037950(arg0, i);
        RecStory_Compress(arg0, i);
        func_80037C7C(arg0, i);
        func_80037DF0(arg0, i);
        func_80037F64(arg0, i);
        func_800380F0(arg0, i);
        func_800381DC(arg0, i);
        func_800382C8(arg0, i);
        func_800383B4(arg0, i);
        func_800384A0(arg0, i);
        BitField_PutBit(arg0, 8, arg0->unk_10);
    }

    arg0->unk_08 = 0x1F8;
    arg0->unk_0C = 0;

    for (i = 0; i < 4U; i++) {
        BitField_PutBit(arg0, eeprom_header_bits[i], eeprom_header[i]);
    }
}

/**
 * Original name: RecAll_Extract
 */
s32 RecAll_Extract(struct_800365B0_arg0 *arg0, char arg1[4]) {
    s32 var_s4 = 0;
    s32 i;
    s32 temp;

    arg0->unk_10 = 0;
    func_800378B0(arg0);

    temp = arg0->unk_10 & 0xF;
    if (temp != BitField_GetBit(arg0, 4)) {
        dm_init_system_mem();
        var_s4++;
    }

    for (i = 0; i < 8; i++) {
        arg0->unk_10 = 0;
        func_800379D4(arg0, i);
        RecStory_Extract(arg0, i);
        func_80037D40(arg0, i);
        func_80037EB4(arg0, i);
        func_80038038(arg0, i);
        func_80038168(arg0, i);
        func_80038254(arg0, i);
        func_80038340(arg0, i);
        func_8003842C(arg0, i);
        func_80038518(arg0, i);

        temp = arg0->unk_10 & 0xFF;
        if (temp != BitField_GetBit(arg0, 8)) {
            dm_init_save_mem(&evs_mem_data[i]);
            var_s4++;
        }
    }

    arg0->unk_08 = 0x1F8;
    arg0->unk_0C = 0;

    for (i = 0; i < 4U; i++) {
        arg1[i] = BitField_GetBit(arg0, eeprom_header_bits[i]);
    }

    return var_s4;
}

/**
 * Original name: EepRom_Init
 */
EepRomStatus EepRom_Init(void) {
    s32 temp;

    EepRom_InitVars();
    temp = osEepromProbe(&B_800F3E38);
    if ((temp != 1) && (temp != 2)) {
        EepRom_DumpErrMes(EEPROM_STATUS_1);
        return EEPROM_STATUS_1;
    }

    return EepRom_ReadAll();
}

/**
 * Original name: EepRom_InitFirst
 */
EepRomStatus EepRom_InitFirst(EepRom_WriteDif_arg3 arg0, void *arg1) {
    s32 temp;

    EepRom_InitVars();
    temp = osEepromProbe(&B_800F3E38);
    if ((temp != 1) && (temp != 2)) {
        EepRom_DumpErrMes(EEPROM_STATUS_1);
        return EEPROM_STATUS_1;
    }

    return EepRom_WriteAll(arg0, arg1);
}

/**
 * Original name: EepRom_InitVars
 */
void EepRom_InitVars(void) {
    s32 i;

    dm_init_system_mem();
    func_8003678C(&evs_cfg_4p);

    for (i = 0; i < ARRAY_COUNT(evs_mem_data); i++) {
        dm_init_save_mem(&evs_mem_data[i]);
    }
}

u8 *func_80038938(bool arg0) {
    if (!_cached_1332 || arg0) {
        _cached_1332 = !osEepromLongRead(&B_800F3E38, 0, _cache_1333, sizeof(_cache_1333));
    }

    return _cached_1332 ? _cache_1333 : NULL;
}

/**
 * Original name: EepRom_WriteDif
 */
EepRomStatus EepRom_WriteDif(u8 *arg0, u8 *arg1, size_t size, EepRom_WriteDif_arg3 arg3, void *arg4) {
    u8 *var_s2 = arg0;
    u8 *var_s1 = arg1;
    s32 i;

    for (i = 0; i < (s32)size; i += 8) {
        if (bcmp(var_s2, var_s1, 8) != 0) {
            if (arg3 != NULL) {
                arg3(arg4);
                arg3 = NULL;
            }

            if (osEepromLongWrite(&B_800F3E38, i / 8, var_s1, 8) != 0) {
                EepRom_DumpErrMes(EEPROM_STATUS_4);
                return EEPROM_STATUS_4;
            }
        }
        var_s2 += 8;
        var_s1 += 8;
    }

    return EEPROM_STATUS_0;
}

/**
 * Original name: EepRom_ReadAll
 */
EepRomStatus EepRom_ReadAll(void) {
    struct_800365B0_arg0 sp10;
    char sp28[4];
    s32 temp_s0;
    u8 *temp_v0 = func_80038938(true);

    if (temp_v0 == NULL) {
        EepRom_DumpErrMes(EEPROM_STATUS_3);
        return EEPROM_STATUS_3;
    }

    func_800365B0(&sp10, temp_v0, 0x200);
    temp_s0 = RecAll_Extract(&sp10, sp28);

    if (bcmp(sp28, eeprom_header, sizeof(eeprom_header)) != 0) {
        return EEPROM_STATUS_2;
    }
    if (temp_s0 == 0) {
        return EEPROM_STATUS_0;
    }
    return EEPROM_STATUS_5;
}

/**
 * Original name: EepRom_WriteAll
 */
EepRomStatus EepRom_WriteAll(EepRom_WriteDif_arg3 arg0, void *arg1) {
    struct_800365B0_arg0 sp20;
    u8 sp38[0x200];
    u8 *__dest = func_80038938(true);

    if (__dest == NULL) {
        EepRom_DumpErrMes(EEPROM_STATUS_3);
        return EEPROM_STATUS_3;
    }

    func_800365C8(&sp20, sp38, sizeof(sp38));
    RecAll_Compress(&sp20);
    if (EepRom_WriteDif(__dest, sp38, sizeof(sp38), arg0, arg1) != EEPROM_STATUS_0) {
        EepRom_DumpErrMes(EEPROM_STATUS_4);
        return EEPROM_STATUS_4;
    }

    bcopy(sp38, __dest, sizeof(sp38));
    return EEPROM_STATUS_0;
}

/**
 * Original name: EepRom_DumpErrMes
 */
void EepRom_DumpErrMes(EepRomStatus status UNUSED) {
}

/**
 * Original name: EepRom_DumpDataSize
 */
void EepRom_DumpDataSize(void) {
}

/**
 * Original name: RecWritingMsg_init
 */
void RecWritingMsg_init(RecordWritingMessage *recMessage, UNK_PTR *arg1) {
    msgWnd_init(&recMessage->messageWnd, arg1, 0x18, 2, 0, 0);
    recMessage->messageWnd.unk_24 = 1;
    RecWritingMsg_setPos(recMessage, 0, 0);
    recMessage->unk_84 = 0x78;
    recMessage->unk_80 = 0x78;
}

/**
 * Original name: RecWritingMsg_setStr
 */
void RecWritingMsg_setStr(RecordWritingMessage *recMessage, const char *arg1) {
    msgWnd_clear(&recMessage->messageWnd);
    msgWnd_addStr(&recMessage->messageWnd, arg1);
    msgWnd_skip(&recMessage->messageWnd);
}

/**
 * Original name: RecWritingMsg_calc
 */
void RecWritingMsg_calc(RecordWritingMessage *recMessage) {
    if (RecWritingMsg_isEnd(recMessage)) {
        return;
    }

    msgWnd_update(&recMessage->messageWnd);
    recMessage->unk_84++;
}

/**
 * Original name: RecWritingMsg_draw
 */
void RecWritingMsg_draw(RecordWritingMessage *recMessage, Gfx **gfxP) {
    Gfx *gfx;
    s32 width;
    s32 height;

    if (RecWritingMsg_isEnd(recMessage)) {
        return;
    }

    gfx = *gfxP;

    width = msgWnd_getWidth(&recMessage->messageWnd);
    height = msgWnd_getHeight(&recMessage->messageWnd);
    gSPDisplayList(gfx++, normal_texture_init_dl);

    StretchTexTile8(&gfx, mess_panel_tex_size.width, mess_panel_tex_size.height, mess_panel_lut, mess_panel_tex, 0, 0,
                    mess_panel_tex_size.width, mess_panel_tex_size.height,
                    recMessage->messageWnd.xPos - ((mess_panel_tex_size.width - width) / 2),
                    recMessage->messageWnd.yPos - ((mess_panel_tex_size.height - height) / 2),
                    mess_panel_tex_size.width, mess_panel_tex_size.height);
    msgWnd_draw(&recMessage->messageWnd, &gfx);

    *gfxP = gfx;
}

/**
 * Original name: RecWritingMsg_start
 */
void RecWritingMsg_start(RecordWritingMessage *recMessage) {
    recMessage->unk_84 = 0;
}

/**
 * Original name: RecWritingMsg_end
 */
void RecWritingMsg_end(RecordWritingMessage *recMessage) {
    recMessage->unk_84 = recMessage->unk_80;
}

/**
 * Original name: RecWritingMsg_isEnd
 */
bool RecWritingMsg_isEnd(RecordWritingMessage *recMessage) {
    return recMessage->unk_84 >= recMessage->unk_80;
}

/**
 * Original name: RecWritingMsg_setPos
 */
void RecWritingMsg_setPos(RecordWritingMessage *recMessage, s32 arg1, s32 arg2) {
    recMessage->messageWnd.xPos = arg1;
    recMessage->messageWnd.yPos = arg2;
}

/**
 * Original name: setSleepTimer
 */
void setSleepTimer(s32 milliseconds) {
    OSMesgQueue mq;
    OSTimer timer;
    OSMesg msg[1];

    osCreateMesgQueue(&mq, msg, ARRAY_COUNT(msg));
    osSetTimer(&timer, OS_USEC_TO_CYCLES(milliseconds * 1000), 0, &mq, NULL);
    osRecvMesg(&mq, NULL, OS_MESG_BLOCK);
}

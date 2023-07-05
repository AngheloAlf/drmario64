/**
 * Original filename: dm_virus_init.c
 */

#include "gamemap.h"

#include "libultra.h"
#include "include_asm.h"
#include "macros_defines.h"
#include "unknown_structs.h"
#include "boot_functions.h"
#include "boot_variables.h"
#include "main_segment_functions.h"
#include "main_segment_variables.h"

#if VERSION_US
void init_map_all(GameMapGrid *mapGrid) {
    s32 row;

    bzero(mapGrid, sizeof(GameMapGrid));

    for (row = 0; row < GAME_MAP_ROWS; row++) {
        s32 column;

        for (column = 0; column < GAME_MAP_COLUMNS; column++) {
            GameMapCell *cells = mapGrid->cells;

            cells[GAME_MAP_GET_INDEX(row, column)].unk_0 = column;
            cells[GAME_MAP_GET_INDEX(row, column)].unk_1 = row + 1;
        }
    }
}
#endif

#if VERSION_US
#ifdef NON_EQUIVALENT
// not sure if equivalent
void clear_map(GameMapGrid *mapGrid, s32 column, s32 row) {
    s32 index = GAME_MAP_GET_INDEX(row - 1, column);
    GameMapCell *temp_v0 = mapGrid->cells;
    s32 var_v1;

    temp_v0[index].unk_3 = 0;
    temp_v0[index].unk_2 = 0;

    for (var_v1 = 0; var_v1 < ARRAY_COUNTU(temp_v0->unk_4); var_v1++) {
        temp_v0[index].unk_4[var_v1] = 0;
    }
}
#else
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_virus_init", clear_map);
#endif
#endif

#if VERSION_US
void clear_map_all(GameMapGrid *mapGrid) {
    s32 row;

    for (row = 0; row < GAME_MAP_ROWS; row++) {
        s32 column;

        for (column = 0; column < GAME_MAP_COLUMNS; column++) {
            clear_map(mapGrid, column, row);
        }
    }
}
#endif

#if VERSION_US
bool get_map_info(GameMapGrid *mapGrid, s32 column, s32 rowPlusOne) {
    GameMapCell *cells = mapGrid->cells;
    s32 index = GAME_MAP_GET_INDEX(rowPlusOne - 1, column);

    return cells[index].unk_4[0] != 0;
}
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_virus_init", func_8005F09C);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_virus_init", func_8005F0E4);
#endif

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/dm_virus_init", RO_800B1BA0);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/dm_virus_init", RO_800B1BA0);
#endif

#if VERSION_US
s32 get_virus_color_count(GameMapGrid *mapGrid, u8 *arg1, u8 *arg2, u8 *arg3) {
    s32 sp0[3] = { 0, 0, 0 };
    GameMapCell *cells = mapGrid->cells;
    s32 i;
    s32 count = 0;

    for (i = 0; i < (GAME_MAP_ROWS - 1) * GAME_MAP_COLUMNS; i++) {
        if (cells[i].unk_4[0] != 0) {
            if ((cells[i].unk_4[2] == 0) && (cells[i].unk_4[4] >= 0)) {
                sp0[cells[i].unk_4[3]]++;
                count++;
            }
        }
    }

    *arg1 = sp0[0];
    *arg2 = sp0[1];
    *arg3 = sp0[2];

    return count;
}
#endif

#if VERSION_US
s32 get_virus_count(GameMapGrid *mapGrid) {
    u8 sp10;
    u8 sp11;
    u8 sp12;

    return get_virus_color_count(mapGrid, &sp10, &sp11, &sp12);
}
#endif

#if VERSION_US
void set_map(GameMapGrid *mapGrid, s32 column, s32 rowPlusOne, s32 arg3, s32 arg4) {
    GameMapCell *cells = mapGrid->cells;
    s32 index;
    s32 var_t0;

    var_t0 = arg4;
    if (var_t0 >= 3) {
        var_t0 -= 3;
    }

    index = GAME_MAP_GET_INDEX(rowPlusOne - 1, column);

    cells[index].unk_2 = arg3;
    cells[index].unk_3 = arg4;
    cells[index].unk_4[0] = 1;
    cells[index].unk_4[1] = 0;
    cells[index].unk_4[2] = 0;
    cells[index].unk_4[4] = -1;
    cells[index].unk_4[3] = var_t0;
}
#endif

#if VERSION_US
void set_virus(GameMapGrid *mapGrid, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    GameMapCell *cells;
    s32 var_t0;
    s32 temp;

    var_t0 = arg3;
    if (var_t0 >= 3) {
        var_t0 -= 3;
    }

    temp = (arg2 - 1) * 8;
    cells = mapGrid->cells;

    cells[temp + arg1].unk_2 = arg4;
    cells[temp + arg1].unk_3 = arg3;
    cells[temp + arg1].unk_4[0] = 1;
    cells[temp + arg1].unk_4[1] = 0;
    cells[temp + arg1].unk_4[2] = 0;
    cells[temp + arg1].unk_4[4] = arg3;
    cells[temp + arg1].unk_4[3] = var_t0;
}
#endif

#if VERSION_US
u16 func_8005F2B0(void) {
    u16 temp_v0 = random(6);
    u16 var_v0;

    if (temp_v0 == 0) {
        var_v0 = random(5);
    } else if (temp_v0 < 3) {
        var_v0 = random(5) + 5;
    } else {
        var_v0 = random(7) + 10;
    }
    return var_v0;
}
#endif

#if VERSION_US
u32 func_8005F310(struct_virus_map_data *arg0, s32 arg1, s32 arg2) {
    struct_virus_map_data_unk_000 *ptr = arg0->unk_000;
    u8 index = ((arg2 - 1) * 8) + arg1;
    u32 value = (u32)ptr[index].unk_0;

    return (~value) >> 31;
}
#endif

#if VERSION_US
#ifdef NON_MATCHING
bool dm_check_color(struct_virus_map_data *arg0, u16 arg1, s32 arg2, u8 arg3) {
    struct {
        u8 unk_0;
        u8 unk_1;
    } dumb;
    // u8 sp0;
    // s8 sp1;
    u8 temp_t0;
    u16 new_var;
    struct_virus_map_data_unk_000 *temp_v1 = arg0->unk_000;
    temp_t0 = arg1 + ((arg2 - 1) * 8);
    if ((arg1 & 0xFFFF) >= 2U) {
        if (temp_v1[temp_t0 - 1].unk_0 == arg3) {
            if (temp_v1[temp_t0 - 2].unk_0 == temp_v1[temp_t0 - 1].unk_0) {
                return false;
            }
        }
    }

    if ((arg1 != 0) & (arg1 != 7)) {
        if (temp_v1[temp_t0 - 1].unk_0 == arg3) {
            if (temp_v1[temp_t0 + 1].unk_0 == temp_v1[temp_t0 - 1].unk_0) {
                return false;
            }
        }
    }

    if (arg1 < 6U) {
        if (temp_v1[temp_t0 + 1].unk_0 == arg3) {
            if (temp_v1[temp_t0 + 2].unk_0 == temp_v1[temp_t0 + 1].unk_0) {
                return false;
            }
        }
    }

    new_var = arg1;
    dumb.unk_0 = (arg2 * 8) + arg1;
    dumb.unk_1 = ((arg2 + 1) * 8) + arg1;
    if ((arg2 & 0xFFFF) < 0xFU) {
        if (temp_v1[dumb.unk_0].unk_0 == arg3) {
            if (temp_v1[dumb.unk_1].unk_0 == temp_v1[dumb.unk_0].unk_0) {
                return false;
            }
        }
    }

    dumb.unk_1 = arg1 + ((arg2 - 2) * 8);
    if (((arg2 - 4) & 0xFFFF) < 0xCU) {
        if (temp_v1[dumb.unk_0].unk_0 == arg3) {
            if (temp_v1[dumb.unk_1].unk_0 == temp_v1[dumb.unk_0].unk_0) {
                return false;
            }
        }
    }

    dumb.unk_0 = ((arg2 - 2) * 8) + arg1;
    dumb.unk_1 = ((arg2 - 3) * 8) + new_var;
    if ((arg2 & 0xFFFF) >= 6U) {
        if (temp_v1[dumb.unk_0].unk_0 == arg3) {
            if (temp_v1[dumb.unk_1].unk_0 == temp_v1[dumb.unk_0].unk_0) {
                return false;
            }
        }
    }
    return true;
}
#else
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_virus_init", dm_check_color);
#endif
#endif

#if VERSION_US
bool dm_check_color_2(struct_virus_map_data *arg0, u16 arg1, s32 arg2, u8 arg3) {
    struct_virus_map_data_unk_000 *ptr = arg0->unk_000;
    u8 temp_t0;

    temp_t0 = (arg1 + ((arg2 - 1) * 8));
    if (arg1 >= 2U) {
        if (ptr[temp_t0 - 2].unk_0 == arg3) {
            return false;
        }
    }

    if (arg1 < 6U) {
        if (ptr[temp_t0 + 2].unk_0 == arg3) {
            return false;
        }
    }

    temp_t0 = (arg1 + ((arg2 - 3) * 8));
    if ((arg2 & 0xFFFF) >= 6U) {
        if (ptr[temp_t0].unk_0 == arg3) {
            return false;
        }
    }

    temp_t0 = (arg1 + ((arg2 + 1) * 8));
    if ((arg2 & 0xFFFF) < 0xFU) {
        if (ptr[temp_t0].unk_0 == arg3) {
            return false;
        }
    }

    return true;
}
#endif

#if VERSION_US
void dm_virus_map_copy(struct_virus_map_data *virusMapSrc, struct_virus_map_data *virusMapDst,
                       struct_virus_map_disp_order *virusDispOrderSrc, struct_virus_map_disp_order *virusDispOrderDst) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(virusMapDst->unk_000); i++) {
        virusMapDst->unk_000[i].unk_0 = -1;
        virusMapDst->unk_000[i].unk_2 = 0;
        virusMapDst->unk_000[i].unk_1 = 0;
        virusMapDst->unk_000[i].unk_0 = virusMapSrc->unk_000[i].unk_0;
        virusMapDst->unk_000[i].unk_1 = virusMapSrc->unk_000[i].unk_1;
        virusMapDst->unk_000[i].unk_2 = virusMapSrc->unk_000[i].unk_2;
    }

    for (i = 0; i < ARRAY_COUNT(virusDispOrderDst->unk_00); i++) {
        virusDispOrderDst->unk_00[i] = virusDispOrderSrc->unk_00[i];
    }
}
#endif

#if VERSION_US
s32 dm_get_first_virus_count(enum_evs_gamemode evsGamemode, struct_game_state_data *arg1) {
    s32 ret;

    switch (evsGamemode) {
        case ENUM_EVS_GAMEMODE_1:
        case ENUM_EVS_GAMEMODE_3:
            ret = dm_get_first_virus_count_in_new_mode(arg1->unk_16C);
            break;

        default:
            if (arg1->unk_026 <= 0x17) {
                ret = arg1->unk_026;
            } else {
                ret = 0x17;
            }
            ret = (ret + 1) * 4;
            break;
    }

    return ret;
}
#endif

extern const u8 _n_343[];

/**
 * Original name: _n_343
 */
#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/dm_virus_init", _n_343);
#endif
#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/dm_virus_init", _n_343);
#endif

#if VERSION_US
/**
 * Original name: dm_get_first_virus_count_in_new_mode
 */
s32 dm_get_first_virus_count_in_new_mode(s32 arg0) {
    return _n_343[arg0];
}
#endif

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/dm_virus_init", RO_800B1BCC);
#endif
#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/dm_virus_init", RO_800B1BCC);
#endif

#if VERSION_US
#if 0
extern u8 D_800B1BCC[];
extern u8 D_800B1BA0[];

void _dm_virus_init(u32 arg0, struct_game_state_data *arg1, struct_virus_map_data *arg2, struct_virus_map_disp_order *arg3, s32 arg4) {
    u16 sp10[4];
    u16 sp14;
    struct_game_state_data *sp24;
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
    sp4F = dm_get_first_virus_count(arg0, sp24);

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
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_virus_init", _dm_virus_init);
#endif
#endif

#if VERSION_US
void dm_virus_init(u32 arg0, struct_game_state_data *arg1, struct_virus_map_data *arg2,
                   struct_virus_map_disp_order *arg3) {
    _dm_virus_init(arg0, arg1, arg2, arg3, 0);
}
#endif

#if VERSION_US
void func_8005FC6C(struct_8005FC6C_arg0 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    bzero(arg0, sizeof(struct_8005FC6C_arg0));
    arg0->unk_000 = arg1;
    arg0->unk_004 = arg2;
    arg0->unk_008 = arg3;
}
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_virus_init", _makeFlash_checkOrdre);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_virus_init", func_8005FE68);
#endif

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/dm_virus_init", RO_800B1BD0);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/dm_virus_init", RO_800B1BD0);
#endif

struct _m2c_stack_make_flash_virus_pos {
    /* 0x000 */ char pad_0[0x10];
    /* 0x010 */ struct_8005FC6C_arg0 sp10;
    /* 0x304 */ char pad_304[8];
    /* 0x30C */ void *sp30C;
    /* 0x310 */ char pad_310[0x30];
}; /* size = 0x340 */

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/dm_virus_init", make_flash_virus_pos);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_virus_init", init_map_all);
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_virus_init", clear_map);
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_virus_init", clear_map_all);
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_virus_init", get_map_info);
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_virus_init", func_800655EC_cn);
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_virus_init", func_80065638_cn);
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_virus_init", func_800656A0_cn);
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_virus_init", func_800657A0_cn);
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_virus_init", set_map);
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_virus_init", func_8006582C_cn);
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_virus_init", func_80065880_cn);
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_virus_init", func_80065910_cn);
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_virus_init", func_80065950_cn);
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_virus_init", func_80065B20_cn);
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_virus_init", dm_virus_map_copy);
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_virus_init", func_80065C78_cn);
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_virus_init", dm_get_first_virus_count_in_new_mode);
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_virus_init", func_80065CEC_cn);
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_virus_init", dm_virus_init);
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_virus_init", func_80066298_cn);
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_virus_init", func_80066300_cn);
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_virus_init", func_800664DC_cn);
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/dm_virus_init", make_flash_virus_pos);
#endif

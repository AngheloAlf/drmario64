/**
 * Original filename: dm_virus_init.c
 */

#include "dm_virus_init.h"

#include "libultra.h"
#include "include_asm.h"
#include "macros_defines.h"
#include "unknown_structs.h"
#include "boot_functions.h"
#include "boot_variables.h"
#include "main_segment_variables.h"
#include "calc.h"

#if VERSION_US || VERSION_CN
void init_map_all(GameMapCell *mapCells) {
    s32 row;

    bzero(mapCells, sizeof(GameMapCell) * GAME_MAP_ROWS * GAME_MAP_COLUMNS);

    for (row = 0; row < GAME_MAP_ROWS; row++) {
        s32 column;

        for (column = 0; column < GAME_MAP_COLUMNS; column++) {
            mapCells[GAME_MAP_GET_INDEX(row, column)].unk_0 = column;
            mapCells[GAME_MAP_GET_INDEX(row, column)].unk_1 = row + 1;
        }
    }
}
#endif

#if VERSION_US || VERSION_CN
void clear_map(GameMapCell *mapCells, s32 column, s32 row) {
    s32 index = GAME_MAP_GET_INDEX(row - 1, column);
    s32 i;

    mapCells[index].unk_3 = 0;
    mapCells[index].unk_2 = 0;

    for (i = 0; i < ARRAY_COUNTU(mapCells->unk_4); i++) {
        mapCells[index].unk_4[i] = 0;
    }
}
#endif

#if VERSION_US || VERSION_CN
void clear_map_all(GameMapCell *mapCells) {
    s32 row;

    for (row = 0; row < GAME_MAP_ROWS; row++) {
        s32 column;

        for (column = 0; column < GAME_MAP_COLUMNS; column++) {
            clear_map(mapCells, column, row);
        }
    }
}
#endif

#if VERSION_US || VERSION_CN
s32 get_map_info(GameMapCell *mapCells, s32 column, s32 rowPlusOne) {
    s32 index = GAME_MAP_GET_INDEX(rowPlusOne - 1, column);

    if (mapCells[index].unk_4[0] != 0) {
        return 1;
    }

    return 0;
}
#endif

#if VERSION_US || VERSION_CN
s32 func_8005F09C(GameMapCell *mapCells, s32 arg1) {
    s32 var_v1;

    mapCells += arg1;

    for (var_v1 = 0; var_v1 < 0x10; var_v1++) {
        if (mapCells->unk_4[0] != 0) {
            break;
        }
        mapCells += 8;
    }

    return (var_v1 < 0x10) ? mapCells->unk_4[3] : -1;
}
#endif

#if VERSION_US || VERSION_CN
void func_8005F0E4(GameMapCell *mapCells, s32 arg1[8]) {
    s32 i;

    for (i = 0; i < 8; i++) {
        arg1[i] = func_8005F09C(mapCells, i);
    }
}
#endif

/**
 * Original name: limit_table
 */
const u8 limit_table[] = {
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 5, 5, 4, 4, 3, 3, 3, 3, 3, 3, 0, 0, 0,
};

#if VERSION_US || VERSION_CN
/**
 * Original name: get_virus_color_count
 */
s32 get_virus_color_count(GameMapCell *mapCells, u8 *arg1, u8 *arg2, u8 *arg3) {
    s32 sp0[3] = { 0, 0, 0 };
    s32 i;
    s32 count = 0;

    for (i = 0; i < (GAME_MAP_ROWS - 1) * GAME_MAP_COLUMNS; i++) {
        if (mapCells[i].unk_4[0] != 0) {
            if ((mapCells[i].unk_4[2] == 0) && (mapCells[i].unk_4[4] >= 0)) {
                sp0[mapCells[i].unk_4[3]]++;
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

#if VERSION_US || VERSION_CN
s32 get_virus_count(GameMapCell *mapCells) {
    u8 sp10;
    u8 sp11;
    u8 sp12;

    return get_virus_color_count(mapCells, &sp10, &sp11, &sp12);
}
#endif

#if VERSION_US || VERSION_CN
void set_map(GameMapCell *mapCells, s32 column, s32 rowPlusOne, s32 arg3, s32 arg4) {
    s32 index;
    s32 var_t0;

    var_t0 = arg4;
    if (var_t0 >= 3) {
        var_t0 -= 3;
    }

    index = GAME_MAP_GET_INDEX(rowPlusOne - 1, column);

    mapCells[index].unk_2 = arg3;
    mapCells[index].unk_3 = arg4;
    mapCells[index].unk_4[0] = 1;
    mapCells[index].unk_4[1] = 0;
    mapCells[index].unk_4[2] = 0;
    mapCells[index].unk_4[4] = -1;
    mapCells[index].unk_4[3] = var_t0;
}
#endif

#if VERSION_US || VERSION_CN
void set_virus(GameMapCell *mapCells, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 var_t0;
    s32 temp;

    var_t0 = arg3;
    if (var_t0 >= 3) {
        var_t0 -= 3;
    }

    temp = GAME_MAP_GET_INDEX(arg2 - 1, arg1);

    mapCells[temp].unk_2 = arg4;
    mapCells[temp].unk_3 = arg3;
    mapCells[temp].unk_4[0] = 1;
    mapCells[temp].unk_4[1] = 0;
    mapCells[temp].unk_4[2] = 0;
    mapCells[temp].unk_4[4] = arg3;
    mapCells[temp].unk_4[3] = var_t0;
}
#endif

#if VERSION_US || VERSION_CN
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

#if VERSION_US || VERSION_CN
u8 func_8005F310(struct_virus_map_data *virusMapData, u16 arg1, u16 arg2) {
    u8 temp = ((arg2 - 1) << 3) + arg1;

    if (virusMapData[temp].unk_0 < 0) {
        return false;
    }
    return true;
}
#endif

#if VERSION_US || VERSION_CN
u8 dm_check_color(struct_virus_map_data *virusMapData, u16 arg1, u16 arg2, u8 arg3) {
    u8 temp_a0 = ((arg2 - 1) << 3) + arg1;
    u8 sp8[2];

    if ((arg1 >= 2U) && (virusMapData[temp_a0 - 1].unk_0 == arg3) && (virusMapData[temp_a0 - 2].unk_0 == arg3)) {
        return false;
    }

    if ((arg1 != 0) && (arg1 != 7)) {
        if ((virusMapData[temp_a0 - 1].unk_0 == arg3) && (virusMapData[temp_a0 + 1].unk_0 == arg3)) {
            return false;
        }
    }

    if (((arg1 < 6) && (virusMapData[temp_a0 + 1].unk_0 == arg3) && (virusMapData[temp_a0 + 2].unk_0 == arg3))) {
        return false;
    }

    sp8[0] = (arg2 << 3) + arg1;
    sp8[1] = ((arg2 + 1) << 3) + arg1;
    if (arg2 < 0xFU) {
        if ((virusMapData[sp8[0]].unk_0 == arg3) && (virusMapData[sp8[1]].unk_0 == arg3)) {
            return false;
        }
    }

    sp8[1] = ((arg2 - 2) << 3) + arg1;
    if ((arg2 > 0x3) && (arg2 < 0x10)) {
        if ((virusMapData[sp8[0]].unk_0 == arg3) && (virusMapData[sp8[1]].unk_0 == arg3)) {
            return false;
        }
    }

    sp8[0] = ((arg2 - 2) << 3) + arg1;
    sp8[1] = ((arg2 - 3) << 3) + arg1;
    if (arg2 > 5) {
        if ((virusMapData[sp8[0]].unk_0 == arg3) && (virusMapData[sp8[1]].unk_0 == arg3)) {
            return false;
        }
    }

    return true;
}
#endif

#if VERSION_US || VERSION_CN
u8 dm_check_color_2(struct_virus_map_data *virusMapData, u16 arg1, u16 arg2, u8 arg3) {
    u8 temp_t0;

    temp_t0 = ((arg2 - 1) << 3) + arg1;
    if (arg1 >= 2U) {
        if (virusMapData[temp_t0 - 2].unk_0 == arg3) {
            return false;
        }
    }

    if (arg1 < 6U) {
        if (virusMapData[temp_t0 + 2].unk_0 == arg3) {
            return false;
        }
    }

    temp_t0 = ((arg2 - 3) << 3) + arg1;
    if (arg2 >= 6U) {
        if (virusMapData[temp_t0].unk_0 == arg3) {
            return false;
        }
    }

    temp_t0 = ((arg2 + 1) << 3) + arg1;
    if (arg2 < 0xF) {
        if (virusMapData[temp_t0].unk_0 == arg3) {
            return false;
        }
    }

    return true;
}
#endif

#if VERSION_US || VERSION_CN
void dm_virus_map_copy(struct_virus_map_data *virusMapSrc, struct_virus_map_data *virusMapDst,
                       struct_virus_map_disp_order *virusDispOrderSrc, struct_virus_map_disp_order *virusDispOrderDst) {
    s32 i;

    for (i = 0; i < 16 * 8; i++) {
        virusMapDst[i].unk_0 = -1;
        virusMapDst[i].unk_2 = 0;
        virusMapDst[i].unk_1 = 0;
        virusMapDst[i].unk_0 = virusMapSrc[i].unk_0;
        virusMapDst[i].unk_1 = virusMapSrc[i].unk_1;
        virusMapDst[i].unk_2 = virusMapSrc[i].unk_2;
    }

    for (i = 0; i < ARRAY_COUNT(virusDispOrderDst->unk_00); i++) {
        virusDispOrderDst->unk_00[i] = virusDispOrderSrc->unk_00[i];
    }
}
#endif

#if VERSION_US || VERSION_CN
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

/**
 * Original name: _n_343
 */
const u8 _n_343[] = {
    0x1E,
    0x28,
    0x32,
    0x00,
};

#if VERSION_US || VERSION_CN
/**
 * Original name: dm_get_first_virus_count_in_new_mode
 */
s32 dm_get_first_virus_count_in_new_mode(s32 arg0) {
    return _n_343[arg0];
}
#endif

const u8 _l_359[] = {
    0x06,
    0x09,
    0x0C,
    0x00,
};

#if VERSION_US || VERSION_CN
void _dm_virus_init(enum_evs_gamemode arg0, struct_game_state_data *arg1, struct_virus_map_data *virusMapData,
                    struct_virus_map_disp_order *arg3, s32 arg4) {
    u8 *ptr = arg3->unk_00;
    s16 var_s0;
    s16 temp_s2;
    u16 sp18[4];
    u16 var_s0_2;
    u16 var_s1;
    u16 var_s5_2;
    u16 var_s7;
    u8 temp_s3;
    u8 sp20;
    u8 var_s4;
    u8 sp24;
    u8 sp28;

    // TODO: fake label?
loop_1:

    for (var_s0 = 0; var_s0 < 0x80; var_s0++) {
        virusMapData[var_s0].unk_0 = -1;
        virusMapData[var_s0].unk_2 = 0;
        virusMapData[var_s0].unk_1 = 0;
    }

    for (var_s0 = 0; var_s0 < 0x60; var_s0++) {
        ptr[var_s0] = 0xFF;
    }

    switch (arg0) {
        case ENUM_EVS_GAMEMODE_1:
        case ENUM_EVS_GAMEMODE_3:
            sp28 = limit_table[(_l_359[arg1->unk_16C] <= 0x17) ? _l_359[arg1->unk_16C] : 0x17];
            break;

        default:
            sp28 = limit_table[(arg1->unk_026 <= 0x17) ? arg1->unk_026 : 0x17];
            break;
    }

    sp20 = dm_get_first_virus_count(arg0, arg1);

    for (var_s0 = 0; var_s0 < 4; var_s0++) {
        sp18[var_s0] = sp20 / 3;
    }

    var_s0 = 0;
    temp_s2 = (sp20 % 3);
    while (var_s0 < temp_s2) {
        s32 temp_v0_3;

        temp_v0_3 = random(3);

        if ((sp18[temp_v0_3] <= sp18[(temp_v0_3 + 1) % 3]) && (sp18[temp_v0_3] <= sp18[(temp_v0_3 + 2) % 3])) {
            sp18[temp_v0_3]++;
            var_s0++;
        }
    }

    sp24 = 0;
    if (arg4 == 1) {
        var_s1 = 3;
        var_s0_2 = sp28 + 1;
        temp_s2 = 2;
        temp_s3 = 2;

        sp18[temp_s2] -= 1;

        temp_s2 = ((var_s0_2 - 1) << 3) + var_s1;
        virusMapData[temp_s2].unk_0 = temp_s3;
        virusMapData[temp_s2].unk_1 = var_s1;
        virusMapData[temp_s2].unk_2 = var_s0_2;

        ptr[sp24] = temp_s2;

        sp24 = 1;
    }

    for (; sp24 < sp20; sp24++) {
        var_s7 = 0;
        var_s5_2 = 0;

        do {

            do {
                temp_s2 = random(3);
            } while (sp18[temp_s2] == 0);
            temp_s3 = temp_s2;

            if (var_s5_2++ == 2) {
                var_s7++;
                if (var_s7 > 2) {
                    goto loop_1;
                }

                var_s5_2 = 0;

                for (var_s1 = 0; var_s1 < 8; var_s1++) {
                    for (var_s0_2 = 0x10; var_s0_2 > sp28; var_s0_2--) {
                        var_s4 = 0;

                        if (func_8005F310(virusMapData, var_s1, var_s0_2) != 0) {
                            continue;
                        }

                        var_s4 = dm_check_color(virusMapData, var_s1, var_s0_2, temp_s3);
                        if (var_s4 == 0) {
                            continue;
                        }

                        var_s4 = dm_check_color_2(virusMapData, var_s1, var_s0_2, temp_s3);
                        if (var_s4 == 0) {
                            continue;
                        }

                        goto label;
                    }
                }

            //! FAKE ?
            label:;
            } else {

                do {
                    var_s1 = random(8);
                    do {
                        var_s0_2 = random(0x11);
                    } while (var_s0_2 < (sp28 + 1));
                } while (func_8005F310(virusMapData, var_s1, var_s0_2) != 0);

                var_s4 = dm_check_color(virusMapData, var_s1, var_s0_2, temp_s3);
                if (var_s4 != 0) {
                    var_s4 = dm_check_color_2(virusMapData, var_s1, var_s0_2, temp_s3);
                }
            }

        } while (var_s4 == 0);

        sp18[temp_s2]--;

        temp_s2 = ((var_s0_2 - 1) << 3) + var_s1;
        virusMapData[temp_s2].unk_0 = temp_s3;
        virusMapData[temp_s2].unk_1 = var_s1;
        virusMapData[temp_s2].unk_2 = var_s0_2;

        ptr[sp24] = temp_s2;
    }
}
#endif

#if VERSION_US || VERSION_CN
void dm_virus_init(enum_evs_gamemode arg0, struct_game_state_data *arg1, struct_virus_map_data *virusMapData,
                   struct_virus_map_disp_order *arg3) {
    _dm_virus_init(arg0, arg1, virusMapData, arg3, 0);
}
#endif

const s32 _n_564[][5] = {
    { 1, 0, 2, 0x60, 0x60 },
    { 1, 1, 1, 0x60, 0x60 },
    { 1, 2, 0, 0x60, 0x60 },
};

#if VERSION_US || VERSION_CN
void func_8005FC6C(struct_8005FC6C_arg0 *arg0, struct_virus_map_data *virusMapData,
                   struct_virus_map_disp_order *virusMapDispOrder, s32 virusCount) {
    bzero(arg0, sizeof(struct_8005FC6C_arg0));
    arg0->virusMapData = virusMapData;
    arg0->virusMapDispOrder = virusMapDispOrder->unk_00;
    arg0->virusCount = virusCount;
}
#endif

#if VERSION_US || VERSION_CN
void _makeFlash_checkOrdre(struct_8005FC6C_arg0 *arg0) {
    s32 var_t2 = -1;
    s32 i;
    s32 temp;
    s32 temp_a1;
    s32 temp_a2;
    s32 temp2;

    for (i = 0; i < arg0->virusCount; i++) {
        temp_a2 = arg0->virusMapDispOrder[i];

        switch (arg0->virusMapData[temp_a2].unk_1) {
            case 0:
            case 7:
                break;

            default:
                var_t2 = MAX(var_t2, arg0->virusMapData[temp_a2].unk_2);
                break;
        }
    }

    var_t2 = MIN(var_t2, 0xE);
    temp = var_t2 - 3;

    for (i = 0; i < arg0->virusCount; i++) {
        temp_a2 = arg0->virusMapDispOrder[i];
        temp_a1 = arg0->virusMapData[temp_a2].unk_0;

        switch (arg0->virusMapData[temp_a2].unk_1) {
            case 0:
            case 7:
                arg0->unk_288[temp_a1][arg0->unk_2E8[temp_a1]++] = temp_a2;
                break;

            default:
                temp2 = arg0->virusMapData[temp_a2].unk_2;

                if (temp2 >= var_t2) {
                    arg0->unk_0D8[temp_a1][arg0->unk_138[temp_a1]++] = temp_a2;
                } else if (temp2 >= temp) {
                    arg0->unk_144[temp_a1][arg0->unk_1A4[temp_a1]++] = temp_a2;
                } else {
                    arg0->unk_1B0[temp_a1][arg0->unk_210[temp_a1]++] = temp_a2;
                }
                arg0->unk_21C[temp_a1][arg0->unk_27C[temp_a1]++] = temp_a2;
                break;
        }
    }
}
#endif

#if VERSION_US || VERSION_CN
s32 func_8005FE68(struct_8005FC6C_arg0 *arg0, u8 arg1[UNK_SIZE][0x20], s32 *arg2, s32 arg3) {
    u8 *temp_a1 = arg1[arg3];
    s32 temp_a2 = arg2[arg3];
    s32 i;

    if (temp_a2 == 0) {
        return -1;
    }

    for (i = 0; i < temp_a2; i++) {
        if (arg0->unk_00C[temp_a1[i]] == 0) {
            arg0->unk_00C[temp_a1[i]] = 1;
            arg0->unk_06C[arg3][arg0->unk_0CC[arg3]++] = temp_a1[i];
            return temp_a1[i];
        }
    }
    return -1;
}
#endif

#if VERSION_US || VERSION_CN
s32 make_flash_virus_pos(struct_game_state_data *gameStateDataRef, struct_virus_map_data *virusMapData,
                         struct_virus_map_disp_order *virusMapDispOrder) {
    struct_8005FC6C_arg0 sp18;
    struct_8005FC6C_arg0 *ptr = &sp18;
    s32 var_fp;
    s32 var_s0;
    s32 var_s1;
    s32 var_s4;
    s32 var_v1;
    s32 *var_s6;
    u8(*var_s7)[0x20];
    s32 var_s3;

    gameStateDataRef->unk_164 = 3;
    var_fp = 3;
    func_8005FC6C(ptr, virusMapData, virusMapDispOrder,
                  dm_get_first_virus_count(ENUM_EVS_GAMEMODE_1, gameStateDataRef));
    _makeFlash_checkOrdre(ptr);
    var_s0 = random(3);

    for (var_s3 = 0; var_s3 < 5; var_s3++) {
        var_s4 = MIN(var_fp, _n_564[gameStateDataRef->unk_16C][var_s3]);

        switch (var_s3) {
            case 0:
                var_s7 = ptr->unk_0D8;
                var_s6 = ptr->unk_138;
                break;

            case 1:
                var_s7 = ptr->unk_144;
                var_s6 = ptr->unk_1A4;
                break;

            case 2:
                var_s7 = ptr->unk_1B0;
                var_s6 = ptr->unk_210;
                break;

            case 3:
                var_s7 = ptr->unk_21C;
                var_s6 = ptr->unk_27C;
                break;

            case 4:
                var_s7 = ptr->unk_288;
                var_s6 = ptr->unk_2E8;
                break;
        }

        var_s1 = 0;

        while ((var_s1 < 3) && (var_s4 > 0)) {
            var_s0 = (var_s0 + 1) % 3;

            if ((ptr->unk_0CC[var_s0] <= ptr->unk_0CC[(var_s0 + 1) % 3]) &&
                (ptr->unk_0CC[var_s0] <= ptr->unk_0CC[(var_s0 + 2) % 3])) {
                var_v1 = func_8005FE68(ptr, var_s7, var_s6, var_s0);
            } else {
                var_v1 = -1;
            }

            var_s1 += 1;
            if (var_v1 >= 0) {
                var_fp -= 1;
                var_s4 -= 1;
                var_s1 = 0;
            }
        }
    }

    var_s3 = 0;
    for (var_s0 = 0; var_s0 < 3; var_s0++) {
        for (var_s1 = 0; var_s1 < ptr->unk_0CC[var_s0]; var_s1++) {
            var_v1 = ptr->unk_06C[var_s0][var_s1];
            gameStateDataRef->unk_0D4.unk_00[var_s3].unk_0 = var_v1 & 7;
            gameStateDataRef->unk_0D4.unk_00[var_s3].unk_4 = (var_v1 >> 3) & 0xF;
            gameStateDataRef->unk_0D4.unk_00[var_s3].unk_8 = var_s0;
            gameStateDataRef->unk_140.unk_00[var_s3] = var_s0;
            var_s3 += 1;
        }
    }

    return ptr->unk_0CC[0] + ptr->unk_0CC[1] + ptr->unk_0CC[2];
}
#endif

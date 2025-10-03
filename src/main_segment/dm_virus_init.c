/**
 * Original filename: dm_virus_init.c
 */

#include "dm_virus_init.h"

#include "libultra.h"

#include "macros_defines.h"
#include "calc.h"

/**
 * Original name: init_map_all
 */
void init_map_all(GameMapCell *mapCells) {
    s32 row;

    bzero(mapCells, sizeof(GameMapCell) * GAME_MAP_ROWS * GAME_MAP_COLUMNS);

    for (row = 0; row < GAME_MAP_ROWS; row++) {
        s32 column;

        for (column = 0; column < GAME_MAP_COLUMNS; column++) {
            mapCells[GAME_MAP_GET_INDEX(row, column)].pos_m_x = column;
            mapCells[GAME_MAP_GET_INDEX(row, column)].pos_m_y = row + 1;
        }
    }
}

/**
 * Original name: clear_map
 */
void clear_map(GameMapCell *mapCells, s32 column, s32 row) {
    s32 index = GAME_MAP_GET_INDEX(row - 1, column);
    s32 i;

    mapCells[index].capsel_m_p = 0;
    mapCells[index].capsel_m_g = 0;

    for (i = 0; i < ARRAY_COUNTU(mapCells->capsel_m_flg); i++) {
        mapCells[index].capsel_m_flg[i] = 0;
    }
}

/**
 * Original name: clear_map_all
 */
void clear_map_all(GameMapCell *mapCells) {
    s32 row;

    for (row = 0; row < GAME_MAP_ROWS; row++) {
        s32 column;

        for (column = 0; column < GAME_MAP_COLUMNS; column++) {
            clear_map(mapCells, column, row);
        }
    }
}

/**
 * Original name: get_map_info
 */
s32 get_map_info(GameMapCell *mapCells, s32 column, s32 rowPlusOne) {
    s32 index = GAME_MAP_GET_INDEX(rowPlusOne - 1, column);

    if (mapCells[index].capsel_m_flg[0] != 0) {
        return 1;
    }

    return 0;
}

/**
 * Original name: get_map_top_color
 */
s32 get_map_top_color(GameMapCell *mapCells, s32 y_pos) {
    s32 y;

    mapCells += y_pos;

    for (y = 0; y < GAME_MAP_ROWS - 1; y++) {
        if (mapCells->capsel_m_flg[0] != 0) {
            break;
        }
        mapCells += GAME_MAP_COLUMNS;
    }

    return (y < GAME_MAP_ROWS - 1) ? mapCells->capsel_m_flg[3] : -1;
}

/**
 * Original name: get_map_top_colors
 */
void get_map_top_colors(GameMapCell *mapCells, s32 colors[GAME_MAP_COLUMNS]) {
    s32 i;

    for (i = 0; i < GAME_MAP_COLUMNS; i++) {
        colors[i] = get_map_top_color(mapCells, i);
    }
}

/**
 * Original name: limit_table
 */
const u8 limit_table[] = {
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 5, 5, 4, 4, 3, 3, 3, 3, 3, 3,
};

/**
 * Original name: get_virus_color_count
 */
s32 get_virus_color_count(GameMapCell *mapCells, u8 *red, u8 *yellow, u8 *blue) {
    s32 color[3] = { 0, 0, 0 };
    s32 i;
    s32 count = 0;

    for (i = 0; i < (GAME_MAP_ROWS - 1) * GAME_MAP_COLUMNS; i++) {
        if (mapCells[i].capsel_m_flg[0] != 0) {
            if ((mapCells[i].capsel_m_flg[2] == 0) && (mapCells[i].capsel_m_flg[4] >= 0)) {
                color[mapCells[i].capsel_m_flg[3]]++;
                count++;
            }
        }
    }

    *red = color[0];
    *yellow = color[1];
    *blue = color[2];

    return count;
}

s32 get_virus_count(GameMapCell *mapCells) {
    u8 ryb[3];

    return get_virus_color_count(mapCells, &ryb[0], &ryb[1], &ryb[2]);
}

void set_map(GameMapCell *mapCells, s32 x_pos, s32 rowPlusOne, s32 item, s32 pal) {
    s32 index;
    s32 pal_save = pal;

    if (pal_save >= 3) {
        pal_save -= 3;
    }

    index = GAME_MAP_GET_INDEX(rowPlusOne - 1, x_pos);

    mapCells[index].capsel_m_g = item;
    mapCells[index].capsel_m_p = pal;
    mapCells[index].capsel_m_flg[0] = 1;
    mapCells[index].capsel_m_flg[1] = 0;
    mapCells[index].capsel_m_flg[2] = 0;
    mapCells[index].capsel_m_flg[4] = -1;
    mapCells[index].capsel_m_flg[3] = pal_save;
}

void set_virus(GameMapCell *mapCells, s32 x_pos, s32 y_pos, s32 virus, s32 virus_anime_no) {
    s32 index;
    s32 pal_save = virus;

    if (pal_save >= 3) {
        pal_save -= 3;
    }

    index = GAME_MAP_GET_INDEX(y_pos - 1, x_pos);

    mapCells[index].capsel_m_g = virus_anime_no;
    mapCells[index].capsel_m_p = virus;
    mapCells[index].capsel_m_flg[0] = 1;
    mapCells[index].capsel_m_flg[1] = 0;
    mapCells[index].capsel_m_flg[2] = 0;
    mapCells[index].capsel_m_flg[4] = virus;
    mapCells[index].capsel_m_flg[3] = pal_save;
}

u16 y_point_set(void) {
    u16 rnd_weight = random(6);
    u16 rnd_cnt;

    if (rnd_weight == 0) {
        rnd_cnt = random(5);
    } else if (rnd_weight < 3) {
        rnd_cnt = random(5) + 5;
    } else {
        rnd_cnt = random(7) + 10;
    }
    return rnd_cnt;
}

u8 dm_virus_check(struct_virus_map_data *virusMapData, u16 x_pos, u16 y_pos) {
    u8 temp = GAME_MAP_GET_INDEX_ALT2(y_pos - 1, x_pos);

    if (virusMapData[temp].virus_type < 0) {
        return false;
    }
    return true;
}

u8 dm_check_color(struct_virus_map_data *virusMapData, u16 x_pos, u16 y_pos, u8 check_color) {
    u8 p = GAME_MAP_GET_INDEX_ALT2(y_pos - 1, x_pos);
    u8 sp8[2];

    if ((x_pos >= 2) && (virusMapData[p - 1].virus_type == check_color) &&
        (virusMapData[p - 2].virus_type == check_color)) {
        return false;
    }

    if ((x_pos != 0) && (x_pos != GAME_MAP_COLUMNS - 1)) {
        if ((virusMapData[p - 1].virus_type == check_color) && (virusMapData[p + 1].virus_type == check_color)) {
            return false;
        }
    }

    if (((x_pos < 6) && (virusMapData[p + 1].virus_type == check_color) &&
         (virusMapData[p + 2].virus_type == check_color))) {
        return false;
    }

    sp8[0] = GAME_MAP_GET_INDEX_ALT2(y_pos, x_pos);
    sp8[1] = GAME_MAP_GET_INDEX_ALT2(y_pos + 1, x_pos);
    if (y_pos < GAME_MAP_ROWS - 2) {
        if ((virusMapData[sp8[0]].virus_type == check_color) && (virusMapData[sp8[1]].virus_type == check_color)) {
            return false;
        }
    }

    sp8[1] = GAME_MAP_GET_INDEX_ALT2(y_pos - 2, x_pos);
    if ((y_pos > 0x3) && (y_pos < GAME_MAP_ROWS - 1)) {
        if ((virusMapData[sp8[0]].virus_type == check_color) && (virusMapData[sp8[1]].virus_type == check_color)) {
            return false;
        }
    }

    sp8[0] = GAME_MAP_GET_INDEX_ALT2(y_pos - 2, x_pos);
    sp8[1] = GAME_MAP_GET_INDEX_ALT2(y_pos - 3, x_pos);
    if (y_pos > 5) {
        if ((virusMapData[sp8[0]].virus_type == check_color) && (virusMapData[sp8[1]].virus_type == check_color)) {
            return false;
        }
    }

    return true;
}

u8 dm_check_color_2(struct_virus_map_data *virusMapData, u16 x_pos, u16 y_pos, u8 check_color) {
    u8 p = GAME_MAP_GET_INDEX_ALT2(y_pos - 1, x_pos);

    if (x_pos >= 2) {
        if (virusMapData[p - 2].virus_type == check_color) {
            return false;
        }
    }

    if (x_pos < 6) {
        if (virusMapData[p + 2].virus_type == check_color) {
            return false;
        }
    }

    p = GAME_MAP_GET_INDEX_ALT2(y_pos - 3, x_pos);
    if (y_pos >= 6) {
        if (virusMapData[p].virus_type == check_color) {
            return false;
        }
    }

    p = GAME_MAP_GET_INDEX_ALT2(y_pos + 1, x_pos);
    if (y_pos < GAME_MAP_ROWS - 2) {
        if (virusMapData[p].virus_type == check_color) {
            return false;
        }
    }

    return true;
}

void dm_virus_map_copy(struct_virus_map_data *virusMapSrc, struct_virus_map_data *virusMapDst,
                       u8 virusDispOrderSrc[VIRUS_MAP_DISP_ORDER_LEN], u8 virusDispOrderDst[VIRUS_MAP_DISP_ORDER_LEN]) {
    s32 i;

    for (i = 0; i < (GAME_MAP_ROWS - 1) * GAME_MAP_COLUMNS; i++) {
        virusMapDst[i].virus_type = -1;
        virusMapDst[i].y_pos = 0;
        virusMapDst[i].x_pos = 0;
        virusMapDst[i].virus_type = virusMapSrc[i].virus_type;
        virusMapDst[i].x_pos = virusMapSrc[i].x_pos;
        virusMapDst[i].y_pos = virusMapSrc[i].y_pos;
    }

    for (i = 0; i < VIRUS_MAP_DISP_ORDER_LEN; i++) {
        virusDispOrderDst[i] = virusDispOrderSrc[i];
    }
}

s32 dm_get_first_virus_count(enum_evs_gamemode evsGamemode, struct_game_state_data *state) {
    s32 ret;

    switch (evsGamemode) {
        case GMD_FLASH:
        case GMD_TIME_ATTACK:
            ret = dm_get_first_virus_count_in_new_mode(state->unk_16C);
            break;

        default:
            if (state->unk_026 <= 0x17) {
                ret = state->unk_026;
            } else {
                ret = 0x17;
            }
            ret = (ret + 1) * 4;
            break;
    }

    return ret;
}

/**
 * Original name: _n_343
 */
const u8 _n_343[] = {
    0x1E,
    0x28,
    0x32,
    0x00,
};

/**
 * Original name: dm_get_first_virus_count_in_new_mode
 */
s32 dm_get_first_virus_count_in_new_mode(s32 level) {
    return _n_343[level];
}

const u8 _l_359[] = {
    0x06,
    0x09,
    0x0C,
    0x00,
};

/**
 * Original name: _dm_virus_init
 */
void _dm_virus_init(enum_evs_gamemode mode, struct_game_state_data *state, struct_virus_map_data *virusMapData,
                    u8 order[VIRUS_MAP_DISP_ORDER_LEN], s32 special) {
    s16 var_s0;
    s16 temp_s2;
    u16 virus_color[4];
    u16 var_s0_2;
    u16 var_s1;
    u16 var_s5_2;
    u16 var_s7;
    u8 temp_s3;
    u8 sp20;
    u8 var_s4;
    u8 sp24;
    u8 sp28;

#if 0
    signed short i; // r4
    signed short j; // r18
    unsigned short virus_color[4]; // r1+0x44
    unsigned short cont_count; // r21
    unsigned short dead_count; // r20
    unsigned short x_set; // r30
    unsigned short y_set; // r31
    unsigned char color_set; // r4
    unsigned char virus_work; // r1+0x8
    unsigned char virus_max; // r15
    unsigned char virus_count; // r18
    unsigned char limit_line; // r21
    unsigned char set_flg; // r28
    int a; // r24
    int c; // r1+0x8
#endif

    // TODO: fake label?
loop_1:

    for (var_s0 = 0; var_s0 < (GAME_MAP_ROWS - 1) * GAME_MAP_COLUMNS; var_s0++) {
        virusMapData[var_s0].virus_type = -1;
        virusMapData[var_s0].y_pos = 0;
        virusMapData[var_s0].x_pos = 0;
    }

    for (var_s0 = 0; var_s0 < VIRUS_MAP_DISP_ORDER_LEN; var_s0++) {
        order[var_s0] = 0xFF;
    }

    switch (mode) {
        case GMD_FLASH:
        case GMD_TIME_ATTACK:
            sp28 = limit_table[(_l_359[state->unk_16C] < ARRAY_COUNT(limit_table) - 1) ? _l_359[state->unk_16C]
                                                                                       : ARRAY_COUNT(limit_table) - 2];
            break;

        default:
            sp28 = limit_table[(state->unk_026 < ARRAY_COUNT(limit_table) - 1) ? state->unk_026
                                                                               : ARRAY_COUNT(limit_table) - 2];
            break;
    }

    sp20 = dm_get_first_virus_count(mode, state);

    for (var_s0 = 0; var_s0 < ARRAY_COUNT(virus_color); var_s0++) {
        virus_color[var_s0] = sp20 / 3;
    }

    var_s0 = 0;
    temp_s2 = (sp20 % 3);
    while (var_s0 < temp_s2) {
        s32 temp_v0_3 = random(3);

        if ((virus_color[temp_v0_3] <= virus_color[(temp_v0_3 + 1) % 3]) &&
            (virus_color[temp_v0_3] <= virus_color[(temp_v0_3 + 2) % 3])) {
            virus_color[temp_v0_3]++;
            var_s0++;
        }
    }

    sp24 = 0;
    if (special == 1) {
        var_s1 = 3;
        var_s0_2 = sp28 + 1;
        temp_s2 = 2;
        temp_s3 = 2;

        virus_color[temp_s2] -= 1;

        temp_s2 = GAME_MAP_GET_INDEX_ALT2(var_s0_2 - 1, var_s1);
        virusMapData[temp_s2].virus_type = temp_s3;
        virusMapData[temp_s2].x_pos = var_s1;
        virusMapData[temp_s2].y_pos = var_s0_2;

        order[sp24] = temp_s2;

        sp24 = 1;
    }

    for (; sp24 < sp20; sp24++) {
        var_s7 = 0;
        var_s5_2 = 0;

        do {

            do {
                temp_s2 = random(3);
            } while (virus_color[temp_s2] == 0);
            temp_s3 = temp_s2;

            if (var_s5_2++ == 2) {
                var_s7++;
                if (var_s7 > 2) {
                    goto loop_1;
                }

                var_s5_2 = 0;

                for (var_s1 = 0; var_s1 < GAME_MAP_COLUMNS; var_s1++) {
                    for (var_s0_2 = GAME_MAP_ROWS - 1; var_s0_2 > sp28; var_s0_2--) {
                        var_s4 = 0;

                        if (dm_virus_check(virusMapData, var_s1, var_s0_2) != 0) {
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
                } while (dm_virus_check(virusMapData, var_s1, var_s0_2) != 0);

                var_s4 = dm_check_color(virusMapData, var_s1, var_s0_2, temp_s3);
                if (var_s4 != 0) {
                    var_s4 = dm_check_color_2(virusMapData, var_s1, var_s0_2, temp_s3);
                }
            }

        } while (var_s4 == 0);

        virus_color[temp_s2]--;

        temp_s2 = GAME_MAP_GET_INDEX_ALT2(var_s0_2 - 1, var_s1);
        virusMapData[temp_s2].virus_type = temp_s3;
        virusMapData[temp_s2].x_pos = var_s1;
        virusMapData[temp_s2].y_pos = var_s0_2;

        order[sp24] = temp_s2;
    }
}

/**
 * Original name: dm_virus_init
 */
void dm_virus_init(enum_evs_gamemode mode, struct_game_state_data *state, struct_virus_map_data *virusMapData,
                   u8 order[VIRUS_MAP_DISP_ORDER_LEN]) {
    _dm_virus_init(mode, state, virusMapData, order, 0);
}

const s32 _n_564[][5] = {
    { 1, 0, 2, 0x60, 0x60 },
    { 1, 1, 1, 0x60, 0x60 },
    { 1, 2, 0, 0x60, 0x60 },
};

/**
 * Original name: _makeFlash_init
 */
void _makeFlash_init(struct_8005FC6C_arg0 *st, struct_virus_map_data *virusMapData,
                     u8 virusMapDispOrder[VIRUS_MAP_DISP_ORDER_LEN], s32 virusCount) {
    bzero(st, sizeof(struct_8005FC6C_arg0));
    st->virusMapData = virusMapData;
    st->virusMapDispOrder = virusMapDispOrder;
    st->virusCount = virusCount;
}

/**
 * Original name: _makeFlash_checkOrdre
 */
void _makeFlash_checkOrdre(struct_8005FC6C_arg0 *st) {
    s32 var_t2 = -1;
    s32 i;
    s32 temp;
    s32 temp_a1;
    s32 temp_a2;
    s32 temp2;

#if 0
    int i; // r7
    int c; // r6
    int o; // r1+0x0
    int y; // r1+0x0
    int under; // r8
    int under2; // r7
#endif

    for (i = 0; i < st->virusCount; i++) {
        temp_a2 = st->virusMapDispOrder[i];

        switch (st->virusMapData[temp_a2].x_pos) {
            case 0:
            case GAME_MAP_COLUMNS - 1:
                break;

            default:
                var_t2 = MAX(var_t2, st->virusMapData[temp_a2].y_pos);
                break;
        }
    }

    var_t2 = MIN(var_t2, GAME_MAP_ROWS - 3);
    temp = var_t2 - 3;

    for (i = 0; i < st->virusCount; i++) {
        temp_a2 = st->virusMapDispOrder[i];
        temp_a1 = st->virusMapData[temp_a2].virus_type;

        switch (st->virusMapData[temp_a2].x_pos) {
            case 0:
            case GAME_MAP_COLUMNS - 1:
                st->sideBuf[temp_a1][st->sideCnt[temp_a1]++] = temp_a2;
                break;

            default:
                temp2 = st->virusMapData[temp_a2].y_pos;

                if (temp2 >= var_t2) {
                    st->underBuf[temp_a1][st->underCnt[temp_a1]++] = temp_a2;
                } else if (temp2 >= temp) {
                    st->under2Buf[temp_a1][st->under2Cnt[temp_a1]++] = temp_a2;
                } else {
                    st->under3Buf[temp_a1][st->under3Cnt[temp_a1]++] = temp_a2;
                }
                st->centerBuf[temp_a1][st->centerCnt[temp_a1]++] = temp_a2;
                break;
        }
    }
}

/**
 * Original name: _makeFlash_checkOrdre
 */
s32 _makeFlash_decide(struct_8005FC6C_arg0 *st, u8 buf[3][0x20], s32 cnt[3], s32 color) {
    u8 *order = buf[color];
    s32 count = cnt[color];
    s32 i;

    if (count == 0) {
        return -1;
    }

    for (i = 0; i < count; i++) {
        if (!st->selected[order[i]]) {
            st->selected[order[i]] = true;
            st->decideBuf[color][st->decideCnt[color]++] = order[i];
            return order[i];
        }
    }
    return -1;
}

s32 make_flash_virus_pos(struct_game_state_data *state, struct_virus_map_data *virusMapData,
                         u8 virusMapDispOrder[VIRUS_MAP_DISP_ORDER_LEN]) {
    struct_8005FC6C_arg0 watchMakeFlash;
    struct_8005FC6C_arg0 *st = &watchMakeFlash;
    s32 var_fp;
    s32 color;
    s32 var_s1;
    s32 var_s4;
    s32 var_v1;
    s32 *cnt;
    u8(*buf)[0x20];
    s32 var_s3;

#if 0
    int i; // r8
    int j; // r9
    int pos; // r6
    int color; // r3
    int count; // r30
    int * cnt; // r28
    unsigned char (* buf)[32]; // r29
    int k; // r10
#endif

    state->unk_164 = 3;
    var_fp = 3;
    _makeFlash_init(st, virusMapData, virusMapDispOrder, dm_get_first_virus_count(GMD_FLASH, state));
    _makeFlash_checkOrdre(st);
    color = random(3);

    for (var_s3 = 0; var_s3 < ARRAY_COUNT(_n_564[state->unk_16C]); var_s3++) {
        var_s4 = MIN(var_fp, _n_564[state->unk_16C][var_s3]);

        switch (var_s3) {
            case 0:
                buf = st->underBuf;
                cnt = st->underCnt;
                break;

            case 1:
                buf = st->under2Buf;
                cnt = st->under2Cnt;
                break;

            case 2:
                buf = st->under3Buf;
                cnt = st->under3Cnt;
                break;

            case 3:
                buf = st->centerBuf;
                cnt = st->centerCnt;
                break;

            case 4:
                buf = st->sideBuf;
                cnt = st->sideCnt;
                break;
        }

        var_s1 = 0;

        while ((var_s1 < 3) && (var_s4 > 0)) {
            color = (color + 1) % 3;

            if ((st->decideCnt[color] <= st->decideCnt[(color + 1) % 3]) &&
                (st->decideCnt[color] <= st->decideCnt[(color + 2) % 3])) {
                var_v1 = _makeFlash_decide(st, buf, cnt, color);
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
    for (color = 0; color < 3; color++) {
        for (var_s1 = 0; var_s1 < st->decideCnt[color]; var_s1++) {
            var_v1 = st->decideBuf[color][var_s1];
            state->unk_0D4[var_s3][0] = var_v1 & 7;
            state->unk_0D4[var_s3][1] = (var_v1 >> 3) & 0xF;
            state->unk_0D4[var_s3][2] = color;
            state->unk_140.unk_00[var_s3] = color;
            var_s3 += 1;
        }
    }

    return st->decideCnt[0] + st->decideCnt[1] + st->decideCnt[2];
}

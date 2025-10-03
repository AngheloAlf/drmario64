#ifndef DM_VIRUS_INIT_H
#define DM_VIRUS_INIT_H

#include "libultra.h"
#include "libc/stdbool.h"

#include "defines.h"
#include "dm_game_main.h"
#include "gamemap.h"

#define VIRUS_NUM 3

typedef struct struct_virus_map_data {
    /* 0x0 */ s8 virus_type; // TODO: enum?
    /* 0x1 */ u8 x_pos;
    /* 0x2 */ u8 y_pos;
} struct_virus_map_data; // size = 0x3

extern struct_virus_map_data virus_map_data[MAX_PLAYERS][(GAME_MAP_ROWS-1)*GAME_MAP_COLUMNS];
#define VIRUS_MAP_DISP_ORDER_LEN 0x60
extern u8 virus_map_disp_order[MAX_PLAYERS][VIRUS_MAP_DISP_ORDER_LEN];

void init_map_all(GameMapCell *mapCells);
void clear_map(GameMapCell *mapCells, s32 column, s32 row);
void clear_map_all(GameMapCell *mapCells);
s32 get_map_info(GameMapCell *mapCells, s32 column, s32 rowPlusOne); // TODO: enum?
s32 get_virus_color_count(GameMapCell *mapCells, u8 *arg1, u8 *arg2, u8 *arg3);
s32 get_virus_count(GameMapCell *mapCells);
void set_map(GameMapCell *mapCells, s32 column, s32 rowPlusOne, s32 arg3, s32 arg4);
void set_virus(GameMapCell *mapCells, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
u8 dm_check_color(struct_virus_map_data *virusMapData, u16 arg1, u16 arg2, u8 arg3);
u8 dm_check_color_2(struct_virus_map_data *virusMapData, u16 arg1, u16 arg2, u8 arg3);
void dm_virus_map_copy(struct_virus_map_data *virusMapSrc, struct_virus_map_data *virusMapDst, u8 virusDispOrderSrc[VIRUS_MAP_DISP_ORDER_LEN], u8 virusDispOrderDst[VIRUS_MAP_DISP_ORDER_LEN]);
s32 dm_get_first_virus_count(enum_evs_gamemode evsGamemode, struct_game_state_data *arg1);
s32 dm_get_first_virus_count_in_new_mode(s32 arg0);
void _dm_virus_init(enum_evs_gamemode arg0, struct_game_state_data *arg1, struct_virus_map_data *virusMapData, u8 arg3[VIRUS_MAP_DISP_ORDER_LEN], s32 arg4);
void dm_virus_init(enum_evs_gamemode arg0, struct_game_state_data *arg1, struct_virus_map_data *virusMapData, u8 arg3[VIRUS_MAP_DISP_ORDER_LEN]);
s32 make_flash_virus_pos(struct_game_state_data *gameStateDataRef, struct_virus_map_data *virusMapData, u8 virusMapDispOrder[VIRUS_MAP_DISP_ORDER_LEN]);

#endif

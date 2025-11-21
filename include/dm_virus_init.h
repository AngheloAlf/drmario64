#ifndef DM_VIRUS_INIT_H
#define DM_VIRUS_INIT_H

#include "libultra.h"
#include "libc/stdbool.h"

#include "macros_defines.h"

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
s32 get_map_info(const GameMapCell *mapCells, s32 column, s32 row); // TODO: enum?
s32 get_virus_color_count(const GameMapCell *mapCells, u8 *red, u8 *yellow, u8 *blue);
s32 get_virus_count(const GameMapCell *mapCells);
void set_map(GameMapCell *mapCells, s32 x_pos, s32 rowPlusOne, s32 item, s32 pal);
void set_virus(GameMapCell *mapCells, s32 x_pos, s32 y_pos, s32 virus, s32 virus_anime_no);
u8 dm_check_color(const struct_virus_map_data *virusMapData, u16 x_pos, u16 y_pos, u8 check_color);
u8 dm_check_color_2(const struct_virus_map_data *virusMapData, u16 x_pos, u16 y_pos, u8 check_color);
void dm_virus_map_copy(CONST_ARG struct_virus_map_data *virusMapSrc, struct_virus_map_data *virusMapDst, const u8 virusDispOrderSrc[VIRUS_MAP_DISP_ORDER_LEN], u8 virusDispOrderDst[VIRUS_MAP_DISP_ORDER_LEN]);
s32 dm_get_first_virus_count(enum_evs_gamemode evsGamemode, const struct_game_state_data *state);
s32 dm_get_first_virus_count_in_new_mode(s32 level);
void _dm_virus_init(enum_evs_gamemode mode, const struct_game_state_data *state, struct_virus_map_data *virusMapData,
                    u8 order[VIRUS_MAP_DISP_ORDER_LEN], s32 special);
void dm_virus_init(enum_evs_gamemode mode, const struct_game_state_data *state, struct_virus_map_data *virusMapData,
                   u8 order[VIRUS_MAP_DISP_ORDER_LEN]);
s32 make_flash_virus_pos(struct_game_state_data *state, const struct_virus_map_data *virusMapData,
                         const u8 virusMapDispOrder[VIRUS_MAP_DISP_ORDER_LEN]);

#endif

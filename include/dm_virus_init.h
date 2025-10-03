#ifndef DM_VIRUS_INIT_H
#define DM_VIRUS_INIT_H

#include "libultra.h"
#include "libc/stdbool.h"
#include "gamemap.h"
#include "dm_game_main.h"
#include "unk.h"

typedef struct struct_virus_map_data {
    /* 0x0 */ s8 virus_type;
    /* 0x1 */ u8 x_pos;
    /* 0x2 */ u8 y_pos;
} struct_virus_map_data; // size = 0x3

typedef struct struct_8005FC6C_arg0 {
    /* 0x000 */ struct struct_virus_map_data *virusMapData;
    /* 0x004 */ u8 *virusMapDispOrder;
    /* 0x008 */ s32 virusCount;
    /* 0x00C */ u8 selected[0x60]; // VIRUS_MAP_DISP_ORDER_LEN
    /* 0x06C */ u8 decideBuf[3][0x20];
    /* 0x0CC */ s32 decideCnt[3];
    /* 0x0D8 */ u8 underBuf[3][0x20];
    /* 0x138 */ s32 underCnt[3];
    /* 0x144 */ u8 under2Buf[3][0x20];
    /* 0x1A4 */ s32 under2Cnt[3];
    /* 0x1B0 */ u8 under3Buf[3][0x20];
    /* 0x210 */ s32 under3Cnt[3];
    /* 0x21C */ u8 centerBuf[3][0x20];
    /* 0x27C */ s32 centerCnt[3];
    /* 0x288 */ u8 sideBuf[3][0x20];
    /* 0x2E8 */ s32 sideCnt[3];
} struct_8005FC6C_arg0; // size = 0x2F4

extern struct_virus_map_data virus_map_data[4][16*8]; // 16 << 3?
#define VIRUS_MAP_DISP_ORDER_LEN 0x60
extern u8 virus_map_disp_order[4][VIRUS_MAP_DISP_ORDER_LEN];

void init_map_all(GameMapCell *mapCells);
void clear_map(GameMapCell *mapCells, s32 column, s32 row);
void clear_map_all(GameMapCell *mapCells);
s32 get_map_info(GameMapCell *mapCells, s32 column, s32 rowPlusOne); // TODO: cleanup bool comparisons
// void get_map_top_color();
// void get_map_top_colors();
s32 get_virus_color_count(GameMapCell *mapCells, u8 *arg1, u8 *arg2, u8 *arg3);
s32 get_virus_count(GameMapCell *mapCells);
void set_map(GameMapCell *mapCells, s32 column, s32 rowPlusOne, s32 arg3, s32 arg4);
void set_virus(GameMapCell *mapCells, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
u16 func_8005F2B0(void);
u8 dm_virus_check(struct_virus_map_data *virusMapData, u16 arg1, u16 arg2);
u8 dm_check_color(struct_virus_map_data *virusMapData, u16 arg1, u16 arg2, u8 arg3);
u8 dm_check_color_2(struct_virus_map_data *virusMapData, u16 arg1, u16 arg2, u8 arg3);
void dm_virus_map_copy(struct_virus_map_data *virusMapSrc, struct_virus_map_data *virusMapDst, u8 virusDispOrderSrc[VIRUS_MAP_DISP_ORDER_LEN], u8 virusDispOrderDst[VIRUS_MAP_DISP_ORDER_LEN]);
s32 dm_get_first_virus_count(enum_evs_gamemode evsGamemode, struct_game_state_data *arg1);
s32 dm_get_first_virus_count_in_new_mode(s32 arg0);
void _dm_virus_init(enum_evs_gamemode arg0, struct_game_state_data *arg1, struct_virus_map_data *virusMapData, u8 arg3[VIRUS_MAP_DISP_ORDER_LEN], UNK_TYPE arg4);
void dm_virus_init(enum_evs_gamemode arg0, struct_game_state_data *arg1, struct_virus_map_data *virusMapData, u8 arg3[VIRUS_MAP_DISP_ORDER_LEN]);
void _makeFlash_init(struct_8005FC6C_arg0 *arg0, struct_virus_map_data *virusMapData, u8 virusMapDispOrder[VIRUS_MAP_DISP_ORDER_LEN], s32 virusCount);
void _makeFlash_checkOrdre(struct_8005FC6C_arg0 *arg0);
// void _makeFlash_decide();
s32 make_flash_virus_pos(struct_game_state_data *gameStateDataRef, struct_virus_map_data *virusMapData, u8 virusMapDispOrder[VIRUS_MAP_DISP_ORDER_LEN]);

#endif

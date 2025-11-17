#ifndef GAME_ETC_H
#define GAME_ETC_H

#include "libultra.h"
#include "libc/stdbool.h"

typedef enum EtcPartIndex {
    /* -1 */ ETC_PART_INDEX_GRAPHBIN_INVALID = -1,
    /*  0 */ ETC_PART_INDEX_GRAPHBIN_0,
    /*  1 */ ETC_PART_INDEX_GRAPHBIN_1,
    /*  2 */ ETC_PART_INDEX_GRAPHBIN_2,
    /*  3 */ ETC_PART_INDEX_GRAPHBIN_3,
    /*  4 */ ETC_PART_INDEX_GRAPHBIN_4,
    /*  5 */ ETC_PART_INDEX_GRAPHBIN_5,
    /*  6 */ ETC_PART_INDEX_GRAPHBIN_6,
    /*  7 */ ETC_PART_INDEX_GRAPHBIN_7,
    /*  8 */ ETC_PART_INDEX_GRAPHBIN_8,
    /*  9 */ ETC_PART_INDEX_GRAPHBIN_9,
    /* 10 */ ETC_PART_INDEX_GRAPHBIN_10,
    /* 11 */ ETC_PART_INDEX_GRAPHBIN_11,
    /* 12 */ ETC_PART_INDEX_GRAPHBIN_12,
    /* 13 */ ETC_PART_INDEX_GRAPHBIN_13,
    /* 14 */ ETC_PART_INDEX_LWS,
    /* 15 */ ETC_PART_INDEX_ATTACK_SPRITE,
    /* 16 */ ETC_PART_INDEX_MAX,
} EtcPartIndex;

typedef struct struct_attack_effect {
    /* 0x00 */ s32 x; /* Original name: x */
    /* 0x04 */ s32 y; /* Original name: y */
    /* 0x08 */ f32 sx; /* Original name: sx */
    /* 0x0C */ f32 sy; /* Original name: sy */
    /* 0x10 */ f32 ex; /* Original name: ex */
    /* 0x14 */ f32 ey; /* Original name: ey */
    /* 0x18 */ f32 vx; /* Original name: vx */
    /* 0x1C */ f32 vy; /* Original name: vy */
    /* 0x20 */ s32 time; /* Original name: time */
    /* 0x24 */ s32 cnt; /* Original name: cnt */
    /* 0x28 */ s32 player; /* Original name: player */
} struct_attack_effect; // size = 0x2C

typedef struct struct_attack_sprite {
    /* 0x00 */ s32 x; /* Original name: x */
    /* 0x04 */ s32 y; /* Original name: y */
    /* 0x08 */ s32 col; /* Original name: col */
    /* 0x0C */ s32 no; /* Original name: no */
    /* 0x10 */ s32 time; /* Original name: time */
} struct_attack_sprite; // size = 0x14


// COMMON

extern s32 attack_effect_idx;
extern struct_attack_effect attack_effect[0x10];

extern s32 attack_sprite_idx;
extern struct_attack_sprite attack_sprite[0x80];

extern u8 (*attack_sprite_address)[10][32*32/2];

void initEtcWork(void *gameEtcSeg, s32 count);
void init_pause_disp(void);
void disp_logo_setup(Gfx **gfxP);
s32 disp_count_logo(Gfx **gfxP, s32 player, s32 count);
void disp_clear_logo(Gfx **gfxP, s32 player, bool flg);
void disp_allclear_logo(Gfx **gfxP, s32 player, bool flg);
void disp_win_logo(Gfx **gfxP, s32 player);
void disp_lose_logo(Gfx **gfxP, s32 player);
void disp_draw_logo(Gfx **gfxP, s32 player);
EtcPartIndex disp_pause_logo(Gfx **gfxP, s32 player, s32 arg2, s32 cursor, s32 type);
EtcPartIndex etc_continue_logo(Gfx **gfxP, s32 player, s32 cursor, s32 type);
EtcPartIndex disp_continue_logo(Gfx **gfxP, s32 player, s32 cursor, s32 type);
EtcPartIndex disp_continue_logo_score(Gfx **gfxP, s32 player, s32 cursor, s32 type);
void disp_gameover_logo(Gfx **gfxP, s32 player);
void disp_timeover_logo(Gfx **gfxP, s32 player);
void disp_retire_logo(Gfx **gfxP, s32 player);
void disp_timestop_logo(Gfx **gfxP, s32 player);
void add_attack_effect(s32 player, s32 sx, s32 sy, s32 ex, s32 ey);
void disp_attack_effect(Gfx **gfxP);

#endif

#ifndef GAME_ETC_H
#define GAME_ETC_H

#include "libultra.h"
#include "libc/stdbool.h"
#include "libc/stdint.h"
#include "color.h"
#include "unk.h"

typedef struct struct_attack_effect {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ f32 unk_14;
    /* 0x18 */ f32 unk_18;
    /* 0x1C */ f32 unk_1C;
    /* 0x20 */ s32 unk_20;
    /* 0x24 */ s32 unk_24;
    /* 0x28 */ s32 unk_28;
} struct_attack_effect; // size = 0x2C

typedef struct struct_attack_sprite {
    /* 0x00 */ s32 x;
    /* 0x04 */ s32 y;
    /* 0x08 */ UNK_TYPE4 unk_08;
    /* 0x0C */ UNK_TYPE4 unk_0C;
    /* 0x10 */ UNK_TYPE4 unk_10;
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
UNK_TYPE disp_count_logo(Gfx **gfxP, s32 arg1, UNK_TYPE arg2);
void disp_clear_logo(Gfx **gfxP, s32 arg1, s32 arg2); // arg2 maybe bool?
void disp_allclear_logo(Gfx **gfxP, s32 arg1, s32 arg2);
void disp_win_logo(Gfx **gfxP, s32 arg1);
void disp_lose_logo(Gfx **gfxP, s32 arg1);
void disp_draw_logo(Gfx **gfxP, s32 arg1);
s32 disp_pause_logo(Gfx **gfxP, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
s32 etc_continue_logo(Gfx **gfxP, s32 arg1, s32 arg2, s32 arg3);
s32 disp_continue_logo(Gfx **gfxP, s32 arg1, s32 arg2, s32 arg3);
s32 disp_continue_logo_score(Gfx **gfxP, s32 arg1, s32 arg2, s32 arg3);
void disp_gameover_logo(Gfx **gfxP, s32 arg1);
void disp_timeover_logo(Gfx **gfxP, s32 arg1);
void disp_retire_logo(Gfx **gfxP, s32 arg1);
void disp_timestop_logo(Gfx **gfxP, s32 arg1);
void add_attack_effect(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void disp_attack_effect(Gfx **gfxP);

#endif

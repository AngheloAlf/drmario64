#ifndef GAME_ETC_H
#define GAME_ETC_H

#include "libultra.h"
#include "libc/stdint.h"
#include "unk.h"

typedef struct struct_etcLwsTbl {
    /* 0x00 */ UNK_PTR unk_00[0xE];
    /* 0x38 */ UNK_TYPE1 unk_38[0x8];
} struct_etcLwsTbl; // size = 0x40

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
    /* 0x00 */ UNK_TYPE4 unk_00;
    /* 0x04 */ UNK_TYPE4 unk_04;
    /* 0x08 */ UNK_TYPE4 unk_08;
    /* 0x0C */ UNK_TYPE4 unk_0C;
    /* 0x10 */ UNK_TYPE4 unk_10;
} struct_attack_sprite; // size = 0x14

typedef struct struct_g_etc_work {
    /* 0x00 */ f32 unk_00;
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ s32 unk_10[8];
    /* 0x30 */ f32 unk_30[8];
    /* 0x50 */ f32 unk_50[8];
    /* 0x70 */ s32 unk_70[8];
    /* 0x70 */ s32 unk_90[8];
    /* 0x70 */ s32 unk_B0[8];
    /* 0x70 */ s32 unk_D0[8];
} struct_g_etc_work; // size = 0xF0

typedef struct struct_cont_table {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ UNK_TYPE1 unk_04[0x14];
} struct_cont_table; // size = 0x18

typedef struct struct_pause_table {
    /* 0x00 */ s32 unk_00[UNK_SIZE];
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ UNK_TYPE1 unk_0C[0xC];
} struct_pause_table; // size = 0x18

extern s32 logo_ofsY;

extern UNK_PTR etcLwsAddress;
extern struct_etcLwsTbl etcLwsTbl;

extern s32 attack_effect_idx;
extern struct_attack_effect attack_effect[0x10];

extern s32 attack_sprite_idx;
extern struct_attack_sprite attack_sprite[0x80];

extern struct_g_etc_work g_etc_work[];

extern struct_cont_table cont_table[];
extern s32 cont_bg_flg;

extern struct_pause_table pause_table[];

extern UNK_TYPE4 etc_parts_tbl[];

extern UNK_PTR etcTexAddress;

void initEtcWork(UNK_PTR arg0, s32 arg1);
// void func_8003ACB4();
void disp_logo_setup(Gfx **gfxP);
UNK_TYPE disp_count_logo(Gfx **gfxP, s32 arg1, UNK_TYPE arg2);
void disp_clear_logo(Gfx **gfxP, s32 arg1, s32 arg2); // arg2 maybe bool?
// void func_8003B054();
// void func_8003B1C4();
void disp_lose_logo(Gfx **gfxP, s32 arg1);
// void disp_draw_logo();
// void func_8003B59C();
s32 etc_continue_logo(Gfx **gfxP, s32 arg1, s32 arg2, s32 arg3);
s32 disp_continue_logo(Gfx **gfxP, s32 arg1, s32 arg2, s32 arg3);
// void func_8003BFD8();
// void func_8003C094();
// void func_8003C1A4();
// void func_8003C2B4();
// void disp_timestop_logo();
// void add_attack_effect();
void disp_attack_effect(Gfx **gfxP);

#endif

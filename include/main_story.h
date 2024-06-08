#ifndef MAIN_STORY_H
#define MAIN_STORY_H

#include "libultra.h"
#include "unk.h"
#include "libc/stdbool.h"
#include "rom_offsets.h"

struct NNSched;

// Maybe same enum as `BgRomDataIndex`
typedef enum enum_story_proc_no {
    /*  0 */ STORY_PROC_NO_0,
    /*  1 */ STORY_PROC_NO_1,
    /*  2 */ STORY_PROC_NO_2,
    /*  3 */ STORY_PROC_NO_3,
    /*  4 */ STORY_PROC_NO_4,
    /*  5 */ STORY_PROC_NO_5,
    /*  6 */ STORY_PROC_NO_6,
    /*  7 */ STORY_PROC_NO_7,
    /*  8 */ STORY_PROC_NO_8,
    /*  9 */ STORY_PROC_NO_9,
    /* 10 */ STORY_PROC_NO_10,
    /* 11 */ STORY_PROC_NO_11,
    /* 12 */ STORY_PROC_NO_12,
    /* 13 */ STORY_PROC_NO_13,
    /* 14 */ STORY_PROC_NO_14,
    /* 15 */ STORY_PROC_NO_15,
    /* 16 */ STORY_PROC_NO_16,
    /* 17 */ STORY_PROC_NO_17,
    /* 18 */ STORY_PROC_NO_18,
    /* 19 */ STORY_PROC_NO_19,
    /* 20 */ STORY_PROC_NO_20,
    /* 21 */ STORY_PROC_NO_21,
    /* 22 */ STORY_PROC_NO_22,
    /* 23 */ STORY_PROC_NO_23,
    /* 24 */ STORY_PROC_NO_24
} enum_story_proc_no;

// GraphBin?
// I wonder if this is a real struct or not
typedef struct struct_wakuGraphic {
    /* 0x000 */ UNK_TYPE1 unk_000[0x8];
    /* 0x008 */ u16 unk_008;
    /* 0x00A */ u16 unk_00A;
    /* 0x00C */ UNK_TYPE2 unk_00C;
    /* 0x00E */ u8 unk_00E;
    /* 0x00F */ UNK_TYPE1 unk_00F[0x1];
    /* 0x010 */ u16 unk_010;
    /* 0x012 */ UNK_TYPE1 unk_012[0x2];
    /* 0x014 */ UNK_TYPE1 unk_014[0x1FC];
    /* 0x210 */ u8 unk_210;
} struct_wakuGraphic; // size >= 0x212

typedef struct struct_get_gbi_stat_arg0 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 width;
    /* 0x08 */ s32 height;
    /* 0x0C */ u16 *tlut;
    /* 0x10 */ u8 *texture; // ci
    /* 0x14 */ UNK_TYPE1 unk_14[0x4];
} struct_get_gbi_stat_arg0; // size = 0x18


typedef struct struct_mes_data {
    /* 0x0 */ s32 unk_0;
    /* 0x4 */ const char *unk_4;
} struct_mes_data; // size = 0x8


void story_zoomfade(Gfx **gfxP, s32 arg1);
void get_gbi_stat(struct_get_gbi_stat_arg0 *arg0, struct_wakuGraphic *arg1);
void curtain_proc(Gfx **gfxP, s32 arg1);
void curtain_proc_org(Gfx **gfxP, s32 arg1);
void func_800770E8(Gfx **gfxP, struct_wakuGraphic *arg1);
void *story_bg_init(BgRomDataIndex index, void *dstAddr);
void story_bg_proc(Gfx **gfxP);
void func_800773F0(void);
void func_8007744C(void);
void func_8007746C(void);
bool func_800774C4(void);
void story_spot(Gfx **gfxP, s32 arg1, s32 arg2, s32 arg3, UNK_PTR tex);
void func_800777E8(Gfx **gfxP, s32 arg1, s32 arg2, s32 arg3);
void *init_coffee_break(void *dstAddr, UNK_TYPE arg1);
void init_coffee_break_cnt(void);
void draw_coffee_break(Gfx **gfxP, s32 arg1, s32 arg2, s32 arg3);
void *init_menu_bg(void *dstAddr, bool arg1);
void draw_menu_bg(Gfx **gfxP, s32 arg1, s32 arg2);
void *init_title(void *dstAddr, bool arg1);
s32 demo_title(Gfx **gfxP, bool arg1);
// void func_80078648();
void func_8007865C(void);
void story_st_new_op(Gfx **gfxP, s32 arg1);
void story_st_new(Gfx **gfxP, s32 arg1, s32 arg2);
void story_st_new2_f(Gfx **gfxP, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void story_st_new2(Gfx **gfxP, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void story_m_end(Gfx **gfxP, s32 arg1, s32 arg2);
void story_st_new_w9(Gfx **gfxP, s32 arg1, s32 arg2);
void story_w_end(Gfx **gfxP, s32 arg1);
void func_8007A9DC(void);
void main_story(struct NNSched *sc);
void init_objMtx(void);
void graphic_story(void);
// void func_8007B62C();


// .data

// extern UNK_TYPE curtain_alpha_00_tex;
// extern UNK_TYPE curtain_00_tex;
extern u8 changestar_tex[];
extern UNK_TYPE title_bmp_tbl[3];
extern void *mess_heap;
extern char st_staffroll_txt[];
// extern UNK_TYPE D_800A923C;
// extern UNK_TYPE D_800A9278;
// extern UNK_TYPE D_800A92C0;
// extern UNK_TYPE D_800A92D8;
// extern UNK_TYPE D_800A9314;
// extern UNK_TYPE D_800A935C;
// extern UNK_TYPE D_800A9390;
// extern UNK_TYPE D_800A93B0;
// extern UNK_TYPE D_800A93F0;
// extern UNK_TYPE D_800A9418;
// extern UNK_TYPE D_800A9444;
// extern UNK_TYPE D_800A9484;
// extern UNK_TYPE D_800A94D4;
// extern UNK_TYPE D_800A9520;
// extern UNK_TYPE D_800A9558;
// extern UNK_TYPE D_800A959C;
// extern UNK_TYPE D_800A95D4;
// extern UNK_TYPE D_800A95EC;
// extern UNK_TYPE D_800A962C;
// extern UNK_TYPE D_800A965C;
// extern UNK_TYPE D_800A96A0;
// extern UNK_TYPE D_800A96D8;
// extern UNK_TYPE D_800A9720;
// extern UNK_TYPE D_800A9764;
// extern UNK_TYPE D_800A97AC;
// extern UNK_TYPE D_800A97EC;
// extern UNK_TYPE D_800A9838;
// extern UNK_TYPE D_800A9878;
// extern UNK_TYPE D_800A9890;
// extern UNK_TYPE D_800A98D4;
// extern UNK_TYPE D_800A9918;
// extern UNK_TYPE D_800A9930;
// extern UNK_TYPE D_800A9974;
// extern UNK_TYPE D_800A99B0;
// extern UNK_TYPE D_800A99EC;
// extern UNK_TYPE D_800A9A18;
// extern UNK_TYPE D_800A9A50;
// extern UNK_TYPE D_800A9A94;
// extern UNK_TYPE D_800A9ACC;
// extern UNK_TYPE D_800A9AF4;
// extern UNK_TYPE D_800A9B30;
// extern UNK_TYPE D_800A9B6C;
// extern UNK_TYPE D_800A9BB8;
// extern UNK_TYPE D_800A9BE0;
// extern UNK_TYPE D_800A9C18;
// extern UNK_TYPE D_800A9C58;
// extern UNK_TYPE D_800A9C74;
// extern UNK_TYPE D_800A9CA0;
// extern UNK_TYPE D_800A9CF0;
// extern UNK_TYPE D_800A9D20;
// extern UNK_TYPE D_800A9D5C;
// extern UNK_TYPE D_800A9DA0;
// extern UNK_TYPE D_800A9DDC;
// extern UNK_TYPE D_800A9DFC;
// extern UNK_TYPE D_800A9E44;
// extern UNK_TYPE D_800A9E7C;
// extern UNK_TYPE D_800A9EB8;
// extern UNK_TYPE D_800A9ED4;
// extern UNK_TYPE D_800A9EFC;
// extern UNK_TYPE D_800A9F48;
// extern UNK_TYPE D_800A9F7C;
// extern UNK_TYPE D_800A9FB4;
// extern UNK_TYPE D_800A9FD4;
// extern UNK_TYPE D_800AA014;
// extern UNK_TYPE D_800AA040;
// extern UNK_TYPE D_800AA07C;
// extern UNK_TYPE D_800AA09C;
// extern UNK_TYPE D_800AA0C4;
// extern UNK_TYPE D_800AA104;
// extern UNK_TYPE D_800AA130;
// extern UNK_TYPE D_800AA168;
// extern UNK_TYPE D_800AA194;
// extern UNK_TYPE D_800AA1BC;
// extern UNK_TYPE D_800AA200;
// extern UNK_TYPE D_800AA238;
// extern UNK_TYPE D_800AA26C;
// extern UNK_TYPE D_800AA29C;
// extern UNK_TYPE D_800AA2C4;
// extern UNK_TYPE D_800AA300;
// extern UNK_TYPE D_800AA318;
// extern UNK_TYPE D_800AA334;
// extern UNK_TYPE D_800AA354;
// extern UNK_TYPE D_800AA398;
// extern UNK_TYPE D_800AA3DC;
// extern UNK_TYPE D_800AA41C;
// extern UNK_TYPE D_800AA454;
// extern UNK_TYPE D_800AA474;
// extern UNK_TYPE D_800AA494;
// extern UNK_TYPE D_800AA4DC;
// extern UNK_TYPE D_800AA4EC;
// extern UNK_TYPE D_800AA528;
// extern UNK_TYPE D_800AA538;
// extern UNK_TYPE D_800AA570;
// extern UNK_TYPE D_800AA5AC;
// extern UNK_TYPE D_800AA5C4;
// extern UNK_TYPE D_800AA604;
// extern UNK_TYPE D_800AA63C;
// extern UNK_TYPE D_800AA668;
// extern UNK_TYPE D_800AA688;
// extern UNK_TYPE D_800AA6CC;
// extern UNK_TYPE D_800AA714;
// extern UNK_TYPE D_800AA758;
// extern UNK_TYPE D_800AA778;
// extern UNK_TYPE D_800AA7C4;
// extern UNK_TYPE D_800AA808;
// extern UNK_TYPE D_800AA844;
// extern UNK_TYPE D_800AA864;
// extern UNK_TYPE D_800AA894;
// extern UNK_TYPE D_800AA8CC;
// extern UNK_TYPE D_800AA8F0;
// extern UNK_TYPE D_800AA928;
// extern UNK_TYPE D_800AA96C;
// extern UNK_TYPE D_800AA9A8;
// extern UNK_TYPE D_800AA9E0;
// extern UNK_TYPE D_800AAA10;
// extern UNK_TYPE D_800AAA4C;
// extern UNK_TYPE D_800AAA80;
// extern UNK_TYPE D_800AAAA0;
// extern UNK_TYPE D_800AAAE0;
// extern UNK_TYPE D_800AAB18;
// extern UNK_TYPE D_800AAB5C;
// extern UNK_TYPE D_800AAB7C;
// extern UNK_TYPE D_800AABB4;
// extern UNK_TYPE D_800AABC8;
// extern UNK_TYPE D_800AABE0;
// extern UNK_TYPE D_800AAC10;
// extern UNK_TYPE D_800AAC5C;
// extern UNK_TYPE mes_data;
// extern UNK_TYPE D_800AAC7C;
// extern UNK_TYPE D_800AAC80;
// extern UNK_TYPE D_800AAC84;
// extern UNK_TYPE D_800AACCC;
// extern UNK_TYPE D_800AACD0;
// extern UNK_TYPE D_800AACD4;
extern enum_story_proc_no story_proc_no; /* Original name: story_proc_no */
extern char STR_800AACF0[];
extern char *EndingLastMessage; /* Original name: EndingLastMessage */
extern s32 story_time_cnt;
extern s32 story_seq_step; // TODO: enum?
extern s32 story_zoom;
extern s32 story_curtain;
extern s32 story_spot_cnt;
extern UNK_TYPE4 story_kay_wait;
extern s32 story_message_on;
extern UNK_TYPE4 story_message_start;
extern s32 story_doing;
extern s32 bgtime; /* Original name: bgtime */
extern s32 mes_time;
extern u8 *story_read_buf;
extern void *story_buffer;
extern void *story_z_buffer;
extern s32 objMtx_FF;
// extern UNK_TYPE D_800AAD48;
// extern UNK_TYPE D_800AAD4C;
// extern UNK_TYPE D_800AAD50;
extern Vp D_800AAD58;
extern Gfx story_setup[];
// extern SeqIndex snd_tbl_838[];



#endif

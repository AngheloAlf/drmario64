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
    /* 24 */ STORY_PROC_NO_24 // TODO: MAX?
} enum_story_proc_no;

// GraphBin?
// I wonder if this is a real struct or not
typedef struct struct_wakuGraphic {
    /* 0x000 */ UNK_TYPE1 unk_000[0x8];
    /* 0x008 */ u16 width;
    /* 0x00A */ u16 height;
    /* 0x00C */ UNK_TYPE1 unk_00C[0x2];
    /* 0x00E */ u8 unk_00E;
    /* 0x00F */ UNK_TYPE1 unk_00F[0x1];
    /* 0x010 */ u16 tlut[0x100];
    /* 0x210 */ u8 texture[UNK_SIZE];
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

extern u8 D_800A73A0[];
extern Gfx D_800A73B8[];
extern u8 curtain_alpha_00_tex[];
extern u16 curtain_00_tex[];
extern u8 changestar_tex[];
extern void *mess_heap;
extern char st_staffroll_txt[];
extern struct_mes_data *mes_data[];
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
extern Vp D_800AAD58;
extern Gfx story_setup[];

#endif

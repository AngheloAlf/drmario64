#ifndef MAIN_STORY_H
#define MAIN_STORY_H

#include "libultra.h"
#include "libc/stdbool.h"
#include "rom_offsets.h"
#include "macros_defines.h"

struct NNSched;
struct GraphBinGeneric;

typedef struct GbiStat {
    /* 0x00 */ s32 siz; /* Original name: type */
    /* 0x04 */ s32 width; /* Original name: x */
    /* 0x08 */ s32 height; /* Original name: y */
    /* 0x0C */ const u16 *tlut; /* Original name: lut_addr */
    /* 0x10 */ const Texture *texture; /* Original name: tex_addr */
} GbiStat; // size = 0x14

void story_zoomfade(Gfx **gfxP, s32 count);
void get_gbi_stat(GbiStat *gbi, CONST_ARG struct GraphBinGeneric *graphBin);
void curtain_proc(Gfx **gfxP, s32 count);
void curtain_proc_org(Gfx **gfxP, s32 count);
void waku_disp(Gfx **gfxP, struct GraphBinGeneric *graphBin);
void *story_bg_init(BgRomDataIndex index, void *dstAddr);
void story_bg_proc(Gfx **gfxP);
void story_st_start(void);
void story_st_end(void);
void story_st_clear(void);
bool story_st_meswait(void);
void story_spot(Gfx **gfxP, s32 x, s32 y, s32 count, const u8 tex[]);
void star_spot(Gfx **gfxP, s32 x, s32 y, s32 count);
void *init_coffee_break(void *dstAddr, s32 arg1);
void init_coffee_break_cnt(void);
void draw_coffee_break(Gfx **gfxP, s32 arg1, s32 arg2, s32 arg3);
void *init_menu_bg(void *dstAddr, bool flg);
void draw_menu_bg(Gfx **gfxP, s32 x, s32 y);
void *init_title(void *dstAddr, bool flg);
s32 demo_title(Gfx **gfxP, bool flg21);
// void main_open();
void st_message_proc(void);

void read_graphic_data(void);
void main_story(struct NNSched *sc);
void init_objMtx(void);
void graphic_story(void);
// void draw_ending_mess_bg();


// .data

extern u8 D_800A73A0[];
extern Gfx D_800A73B8[];
extern u8 curtain_alpha_00_tex[];
extern u16 curtain_00_tex[];
extern u8 changestar_tex[];
extern void *mess_heap;
extern char st_staffroll_txt[];

extern BgRomDataIndex story_proc_no;
extern char STR_800AACF0[];
extern char *EndingLastMessage; /* Original name: EndingLastMessage */
extern s32 story_time_cnt;
extern s32 story_seq_step; // TODO: enum?
extern s32 story_zoom;
extern s32 story_curtain;
extern s32 story_spot_cnt;
extern s32 story_kay_wait;
extern s32 story_message_on;
extern s32 story_message_start;
extern s32 story_doing;
extern s32 bgtime; /* Original name: bgtime */
extern s32 mes_time;
extern u8 *story_read_buf;
extern void *story_buffer;
extern void *story_z_buffer;
extern s32 objMtx_FF;
extern Vp D_800AAD58;
extern Gfx story_setup[];

// COMMON
extern Mtx *pObjectMtx;

#endif

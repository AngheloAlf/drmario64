#ifndef MAIN_STORY_H
#define MAIN_STORY_H

#include "libultra.h"
#include "unk.h"
#include "libc/stdbool.h"
#include "rom_offsets.h"

struct NNSched;
struct GraphBinGeneric;

typedef struct GbiStat {
    /* 0x00 */ s32 siz;
    /* 0x04 */ s32 width;
    /* 0x08 */ s32 height;
    /* 0x0C */ u16 *tlut;
    /* 0x10 */ u8 *texture; // ci // TexturePtr?
} GbiStat; // size = 0x14


typedef struct struct_mes_data {
    /* 0x0 */ s32 unk_0;
    /* 0x4 */ const char *unk_4;
} struct_mes_data; // size = 0x8


void story_zoomfade(Gfx **gfxP, s32 arg1);
void get_gbi_stat(GbiStat *arg0, struct GraphBinGeneric *graphBin);
void curtain_proc(Gfx **gfxP, s32 arg1);
void curtain_proc_org(Gfx **gfxP, s32 arg1);
void func_800770E8(Gfx **gfxP, struct GraphBinGeneric *graphBin);
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
extern BgRomDataIndex story_proc_no;
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

// COMMON
extern Mtx *pObjectMtx;

#endif

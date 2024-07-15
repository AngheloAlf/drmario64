#ifndef SEGMENT_SYMBOLS_H
#define SEGMENT_SYMBOLS_H

#include "libultra.h"
#include "libc/stdint.h"

#define DECLARE_VRAM_SEGMENT(name) \
    extern u32 name ## _VRAM[]; \
    extern u32 name ## _VRAM_END[]

#define DECLARE_ROM_SEGMENT(name) \
    extern u32 name ## _ROM_START[]; \
    extern u32 name ## _ROM_END[]; \
    extern u32 name ## _ROM_SIZE[]

#define DECLARE_BSS_SEGMENT(name)   \
    extern u32 name ## _BSS_START[]; \
    extern u32 name ## _BSS_END[]

#define DECLARE_SEGMENT(name) \
    DECLARE_VRAM_SEGMENT(name); \
    DECLARE_ROM_SEGMENT(name); \
    DECLARE_BSS_SEGMENT(name)

#define SEGMENT_VRAM_START(segment) (segment ## _VRAM)
#define SEGMENT_VRAM_END(segment)   (segment ## _VRAM_END)
#define SEGMENT_VRAM_SIZE(segment)  ((uintptr_t)SEGMENT_VRAM_END(segment) - (uintptr_t)SEGMENT_VRAM_START(segment))

#define SEGMENT_ROM_START(segment) ((RomOffset)segment ## _ROM_START)
#define SEGMENT_ROM_END(segment)   ((RomOffset)segment ## _ROM_END)
#define SEGMENT_ROM_SIZE(segment)  (SEGMENT_ROM_END(segment) - SEGMENT_ROM_START(segment))
#define SEGMENT_ROM_SIZE_CONST(segment) ((RomOffset)segment ## _ROM_SIZE)

#define SEGMENT_BSS_START(segment) (segment ## _BSS_START)
#define SEGMENT_BSS_END(segment)   (segment ## _BSS_END)
#define SEGMENT_BSS_SIZE(segment)  ((uintptr_t)SEGMENT_BSS_END(segment) - (uintptr_t)SEGMENT_BSS_START(segment))

DECLARE_SEGMENT(header);

DECLARE_SEGMENT(ipl3);

DECLARE_SEGMENT(entry);

DECLARE_SEGMENT(boot);

DECLARE_SEGMENT(dma_table);

DECLARE_SEGMENT(main_segment);

DECLARE_SEGMENT(n64_wave_tables);
DECLARE_SEGMENT(n64_ptr_tables_v2);
DECLARE_SEGMENT(fxbank);

DECLARE_SEGMENT(segment_172D60);
DECLARE_SEGMENT(segment_1750C0);
DECLARE_SEGMENT(segment_177420);
DECLARE_SEGMENT(segment_179620);
DECLARE_SEGMENT(segment_17B790);
DECLARE_SEGMENT(segment_17C1E0);
DECLARE_SEGMENT(segment_17D130);
DECLARE_SEGMENT(segment_17E090);
DECLARE_SEGMENT(segment_181840);
DECLARE_SEGMENT(segment_184FF0);
DECLARE_SEGMENT(segment_186FF0);
DECLARE_SEGMENT(segment_188FF0);
DECLARE_SEGMENT(segment_189D40);
DECLARE_SEGMENT(segment_18CB40);
DECLARE_SEGMENT(segment_18DB90);
DECLARE_SEGMENT(segment_18F160);
DECLARE_SEGMENT(segment_1906E0);
DECLARE_SEGMENT(segment_1911D0);
DECLARE_SEGMENT(segment_1936C0);
DECLARE_SEGMENT(segment_1937F0);
DECLARE_SEGMENT(segment_194070);
DECLARE_SEGMENT(segment_194150);
DECLARE_SEGMENT(segment_194910);
DECLARE_SEGMENT(segment_195290);


DECLARE_SEGMENT(segment_game_etc);
DECLARE_SEGMENT(segment_menu_bg);
DECLARE_SEGMENT(segment_menu_bg2);
DECLARE_SEGMENT(segment_coffee01);
DECLARE_SEGMENT(segment_title_all);
DECLARE_SEGMENT(segment_title_bmp);
DECLARE_SEGMENT(segment_waku);
DECLARE_SEGMENT(segment_waku2);
DECLARE_SEGMENT(segment_story_bg01);
DECLARE_SEGMENT(segment_story_bg02);
DECLARE_SEGMENT(segment_story_bg03);
DECLARE_SEGMENT(segment_story_bg04);
DECLARE_SEGMENT(segment_story_bg05);
DECLARE_SEGMENT(segment_story_bg07);
DECLARE_SEGMENT(segment_story_bg08);
DECLARE_SEGMENT(segment_story_bg09);
DECLARE_SEGMENT(segment_story_bg10);
DECLARE_SEGMENT(segment_story_bg11);


DECLARE_SEGMENT(segment_menu_char);
DECLARE_SEGMENT(segment_menu_common);
DECLARE_SEGMENT(segment_menu_level);
DECLARE_SEGMENT(segment_menu_main);
DECLARE_SEGMENT(segment_menu_name);
DECLARE_SEGMENT(segment_menu_p2);
DECLARE_SEGMENT(segment_menu_p4);
DECLARE_SEGMENT(segment_menu_rank);
DECLARE_SEGMENT(segment_menu_setup);
DECLARE_SEGMENT(segment_menu_story);
DECLARE_SEGMENT(segment_menu_cont);


DECLARE_SEGMENT(segment_menu_kasa);
DECLARE_SEGMENT(segment_game_al);

DECLARE_SEGMENT(segment_game_p1);
DECLARE_SEGMENT(segment_game_p2);
DECLARE_SEGMENT(segment_game_p4);
DECLARE_SEGMENT(segment_game_ls);


DECLARE_SEGMENT(segment_game_item);


DECLARE_SEGMENT(segment_anime_a);
DECLARE_SEGMENT(segment_anime_b);
DECLARE_SEGMENT(segment_anime_c);
DECLARE_SEGMENT(segment_anime_d);
DECLARE_SEGMENT(segment_anime_e);
DECLARE_SEGMENT(segment_anime_f);
DECLARE_SEGMENT(segment_anime_g);
DECLARE_SEGMENT(segment_anime_h);
DECLARE_SEGMENT(segment_anime_i);
DECLARE_SEGMENT(segment_anime_j);
DECLARE_SEGMENT(segment_anime_k);
DECLARE_SEGMENT(segment_anime_l);
DECLARE_SEGMENT(segment_anime_m);
DECLARE_SEGMENT(segment_anime_n);
DECLARE_SEGMENT(segment_anime_o);
DECLARE_SEGMENT(segment_anime_mario);
DECLARE_SEGMENT(segment_anime_virus_b);
DECLARE_SEGMENT(segment_anime_virus_r);
DECLARE_SEGMENT(segment_anime_virus_y);
DECLARE_SEGMENT(segment_anime_smog);


DECLARE_SEGMENT(segment_tutorial_data);



#endif

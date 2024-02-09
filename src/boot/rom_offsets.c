#include "rom_offsets.h"

#include "libc/assert.h"
#include "segment_symbols.h"
#include "macros_defines.h"

/**
 * Original name: storyRomData
 */
RomOffsetPair storyRomData[] = {
    { SEGMENT_ROM_START(segment_coffee01), SEGMENT_ROM_END(segment_coffee01) },   // STORYROMDATA_COFFEE_01
    { SEGMENT_ROM_START(segment_menu_bg), SEGMENT_ROM_END(segment_menu_bg) },     // STORYROMDATA_MENU_BG
    { SEGMENT_ROM_START(segment_menu_bg2), SEGMENT_ROM_END(segment_menu_bg2) },   // STORYROMDATA_MENU_BG2
    { SEGMENT_ROM_START(segment_waku), SEGMENT_ROM_END(segment_waku) },           // STORYROMDATA_WAKU
    { SEGMENT_ROM_START(segment_waku2), SEGMENT_ROM_END(segment_waku2) },         // STORYROMDATA_WAKU2
    { SEGMENT_ROM_START(segment_title_all), SEGMENT_ROM_END(segment_title_all) }, // STORYROMDATA_TITLE_ALL
    { SEGMENT_ROM_START(segment_title_bmp), SEGMENT_ROM_END(segment_title_bmp) }, // STORYROMDATA_TITLE_BMP
};

static_assert(ARRAY_COUNT(storyRomData) == STORYROMDATA_MAX, "");

/**
 * Original name: bgRomData
 */
RomOffsetPair bgRomData[] = {
    { 0x00000000, 0x00000000 },                                                     // BGROMDATA_INDEX0
    { SEGMENT_ROM_START(segment_story_bg03), SEGMENT_ROM_END(segment_story_bg03) }, // BGROMDATA_INDEX1
    { SEGMENT_ROM_START(segment_story_bg01), SEGMENT_ROM_END(segment_story_bg01) }, // BGROMDATA_INDEX2
    { SEGMENT_ROM_START(segment_story_bg09), SEGMENT_ROM_END(segment_story_bg09) }, // BGROMDATA_INDEX3
    { SEGMENT_ROM_START(segment_story_bg02), SEGMENT_ROM_END(segment_story_bg02) }, // BGROMDATA_INDEX4
    { SEGMENT_ROM_START(segment_story_bg07), SEGMENT_ROM_END(segment_story_bg07) }, // BGROMDATA_INDEX5
    { SEGMENT_ROM_START(segment_story_bg05), SEGMENT_ROM_END(segment_story_bg05) }, // BGROMDATA_INDEX6
    { SEGMENT_ROM_START(segment_story_bg10), SEGMENT_ROM_END(segment_story_bg10) }, // BGROMDATA_INDEX7
    { SEGMENT_ROM_START(segment_story_bg11), SEGMENT_ROM_END(segment_story_bg11) }, // BGROMDATA_INDEX8
    { SEGMENT_ROM_START(segment_story_bg11), SEGMENT_ROM_END(segment_story_bg11) }, // BGROMDATA_INDEX9
    { SEGMENT_ROM_START(segment_story_bg11), SEGMENT_ROM_END(segment_story_bg11) }, // BGROMDATA_INDEX10
    { 0x00000000, 0x00000000 },                                                     // BGROMDATA_INDEX11
    { 0x00000000, 0x00000000 },                                                     // BGROMDATA_INDEX12
    { SEGMENT_ROM_START(segment_story_bg03), SEGMENT_ROM_END(segment_story_bg03) }, // BGROMDATA_INDEX13
    { SEGMENT_ROM_START(segment_story_bg01), SEGMENT_ROM_END(segment_story_bg01) }, // BGROMDATA_INDEX14
    { SEGMENT_ROM_START(segment_story_bg09), SEGMENT_ROM_END(segment_story_bg09) }, // BGROMDATA_INDEX15
    { SEGMENT_ROM_START(segment_story_bg02), SEGMENT_ROM_END(segment_story_bg02) }, // BGROMDATA_INDEX16
    { SEGMENT_ROM_START(segment_story_bg08), SEGMENT_ROM_END(segment_story_bg08) }, // BGROMDATA_INDEX17
    { SEGMENT_ROM_START(segment_story_bg04), SEGMENT_ROM_END(segment_story_bg04) }, // BGROMDATA_INDEX18
    { SEGMENT_ROM_START(segment_story_bg10), SEGMENT_ROM_END(segment_story_bg10) }, // BGROMDATA_INDEX19
    { SEGMENT_ROM_START(segment_story_bg11), SEGMENT_ROM_END(segment_story_bg11) }, // BGROMDATA_INDEX20
    { SEGMENT_ROM_START(segment_story_bg11), SEGMENT_ROM_END(segment_story_bg11) }, // BGROMDATA_INDEX21
    { SEGMENT_ROM_START(segment_story_bg11), SEGMENT_ROM_END(segment_story_bg11) }, // BGROMDATA_INDEX22
    { 0x00000000, 0x00000000 },                                                     // BGROMDATA_INDEX23
};

static_assert(ARRAY_COUNT(bgRomData) == BGROMDATA_MAX, "");

/**
 * Original name: _romDataTbl
 */
RomOffsetPair _romDataTbl[] = {
    { SEGMENT_ROM_START(n64_wave_tables), SEGMENT_ROM_END(n64_wave_tables) },             // ROMDATATBL_N64_WAVE_TABLES
    { SEGMENT_ROM_START(n64_ptr_tables_v2), SEGMENT_ROM_END(n64_ptr_tables_v2) },         // ROMDATATBL_N64_PTR_TABLES
    { SEGMENT_ROM_START(segment_172130), SEGMENT_ROM_END(segment_172130) },               // ROMDATATBL_INDEX2
    { SEGMENT_ROM_START(segment_172D60), SEGMENT_ROM_END(segment_172D60) },               // ROMDATATBL_INDEX3
    { SEGMENT_ROM_START(segment_177420), SEGMENT_ROM_END(segment_177420) },               // ROMDATATBL_INDEX4
    { SEGMENT_ROM_START(segment_17C1E0), SEGMENT_ROM_END(segment_17C1E0) },               // ROMDATATBL_INDEX5
    { SEGMENT_ROM_START(segment_17E090), SEGMENT_ROM_END(segment_17E090) },               // ROMDATATBL_INDEX6
    { SEGMENT_ROM_START(segment_184FF0), SEGMENT_ROM_END(segment_184FF0) },               // ROMDATATBL_INDEX7
    { SEGMENT_ROM_START(segment_1750C0), SEGMENT_ROM_END(segment_1750C0) },               // ROMDATATBL_INDEX8
    { SEGMENT_ROM_START(segment_179620), SEGMENT_ROM_END(segment_179620) },               // ROMDATATBL_INDEX9
    { SEGMENT_ROM_START(segment_17D130), SEGMENT_ROM_END(segment_17D130) },               // ROMDATATBL_INDEX10
    { SEGMENT_ROM_START(segment_181840), SEGMENT_ROM_END(segment_181840) },               // ROMDATATBL_INDEX11
    { SEGMENT_ROM_START(segment_186FF0), SEGMENT_ROM_END(segment_186FF0) },               // ROMDATATBL_INDEX12
    { SEGMENT_ROM_START(segment_188FF0), SEGMENT_ROM_END(segment_188FF0) },               // ROMDATATBL_INDEX13
    { SEGMENT_ROM_START(segment_189D40), SEGMENT_ROM_END(segment_189D40) },               // ROMDATATBL_INDEX14
    { SEGMENT_ROM_START(segment_17B790), SEGMENT_ROM_END(segment_17B790) },               // ROMDATATBL_INDEX15
    { SEGMENT_ROM_START(segment_18CB40), SEGMENT_ROM_END(segment_18CB40) },               // ROMDATATBL_INDEX16
    { SEGMENT_ROM_START(segment_18F160), SEGMENT_ROM_END(segment_18F160) },               // ROMDATATBL_INDEX17
    { SEGMENT_ROM_START(segment_1906E0), SEGMENT_ROM_END(segment_1906E0) },               // ROMDATATBL_INDEX18
    { SEGMENT_ROM_START(segment_1911D0), SEGMENT_ROM_END(segment_1911D0) },               // ROMDATATBL_INDEX19
    { SEGMENT_ROM_START(segment_1936C0), SEGMENT_ROM_END(segment_1936C0) },               // ROMDATATBL_INDEX20
    { SEGMENT_ROM_START(segment_1937F0), SEGMENT_ROM_END(segment_1937F0) },               // ROMDATATBL_INDEX21
    { SEGMENT_ROM_START(segment_194070), SEGMENT_ROM_END(segment_194070) },               // ROMDATATBL_INDEX22
    { SEGMENT_ROM_START(segment_194150), SEGMENT_ROM_END(segment_194150) },               // ROMDATATBL_INDEX23
    { SEGMENT_ROM_START(segment_194910), SEGMENT_ROM_END(segment_194910) },               // ROMDATATBL_INDEX24
    { SEGMENT_ROM_START(segment_195290), SEGMENT_ROM_END(segment_195290) },               // ROMDATATBL_INDEX25
    { SEGMENT_ROM_START(segment_18DB90), SEGMENT_ROM_END(segment_18DB90) },               // ROMDATATBL_INDEX26
    { SEGMENT_ROM_START(segment_anime_a), SEGMENT_ROM_END(segment_anime_a) },             // ROMDATATBL_ANIME_A
    { SEGMENT_ROM_START(segment_anime_b), SEGMENT_ROM_END(segment_anime_b) },             // ROMDATATBL_ANIME_B
    { SEGMENT_ROM_START(segment_anime_c), SEGMENT_ROM_END(segment_anime_c) },             // ROMDATATBL_ANIME_C
    { SEGMENT_ROM_START(segment_anime_d), SEGMENT_ROM_END(segment_anime_d) },             // ROMDATATBL_ANIME_D
    { SEGMENT_ROM_START(segment_anime_e), SEGMENT_ROM_END(segment_anime_e) },             // ROMDATATBL_ANIME_E
    { SEGMENT_ROM_START(segment_anime_f), SEGMENT_ROM_END(segment_anime_f) },             // ROMDATATBL_ANIME_F
    { SEGMENT_ROM_START(segment_anime_g), SEGMENT_ROM_END(segment_anime_g) },             // ROMDATATBL_ANIME_G
    { SEGMENT_ROM_START(segment_anime_h), SEGMENT_ROM_END(segment_anime_h) },             // ROMDATATBL_ANIME_H
    { SEGMENT_ROM_START(segment_anime_i), SEGMENT_ROM_END(segment_anime_i) },             // ROMDATATBL_ANIME_I
    { SEGMENT_ROM_START(segment_anime_j), SEGMENT_ROM_END(segment_anime_j) },             // ROMDATATBL_ANIME_J
    { SEGMENT_ROM_START(segment_anime_k), SEGMENT_ROM_END(segment_anime_k) },             // ROMDATATBL_ANIME_K
    { SEGMENT_ROM_START(segment_anime_l), SEGMENT_ROM_END(segment_anime_l) },             // ROMDATATBL_ANIME_L
    { SEGMENT_ROM_START(segment_anime_m), SEGMENT_ROM_END(segment_anime_m) },             // ROMDATATBL_ANIME_M
    { SEGMENT_ROM_START(segment_anime_n), SEGMENT_ROM_END(segment_anime_n) },             // ROMDATATBL_ANIME_N
    { SEGMENT_ROM_START(segment_anime_o), SEGMENT_ROM_END(segment_anime_o) },             // ROMDATATBL_ANIME_O
    { SEGMENT_ROM_START(segment_anime_mario), SEGMENT_ROM_END(segment_anime_mario) },     // ROMDATATBL_ANIME_MARIO
    { SEGMENT_ROM_START(segment_anime_virus_b), SEGMENT_ROM_END(segment_anime_virus_b) }, // ROMDATATBL_ANIME_VIRUS_B
    { SEGMENT_ROM_START(segment_anime_virus_r), SEGMENT_ROM_END(segment_anime_virus_r) }, // ROMDATATBL_ANIME_VIRUS_R
    { SEGMENT_ROM_START(segment_anime_virus_y), SEGMENT_ROM_END(segment_anime_virus_y) }, // ROMDATATBL_ANIME_VIRUS_Y
    { SEGMENT_ROM_START(segment_anime_smog), SEGMENT_ROM_END(segment_anime_smog) },       // ROMDATATBL_ANIME_SMOG
    { SEGMENT_ROM_START(segment_game_al), SEGMENT_ROM_END(segment_game_al) },             // ROMDATATBL_GAME_AL
    { SEGMENT_ROM_START(segment_game_p1), SEGMENT_ROM_END(segment_game_p1) },             // ROMDATATBL_GAME_P1
    { SEGMENT_ROM_START(segment_game_p2), SEGMENT_ROM_END(segment_game_p2) },             // ROMDATATBL_GAME_P2
    { SEGMENT_ROM_START(segment_game_p4), SEGMENT_ROM_END(segment_game_p4) },             // ROMDATATBL_GAME_P4
    { SEGMENT_ROM_START(segment_game_ls), SEGMENT_ROM_END(segment_game_ls) },             // ROMDATATBL_GAME_LS
    { SEGMENT_ROM_START(segment_game_item), SEGMENT_ROM_END(segment_game_item) },         // ROMDATATBL_GAME_ITEM
    { SEGMENT_ROM_START(segment_game_etc), SEGMENT_ROM_END(segment_game_etc) },           // ROMDATATBL_GAME_ETC
    { SEGMENT_ROM_START(segment_menu_char), SEGMENT_ROM_END(segment_menu_char) },         // ROMDATATBL_MENU_CHAR
    { SEGMENT_ROM_START(segment_menu_common), SEGMENT_ROM_END(segment_menu_common) },     // ROMDATATBL_MENU_COMMON
    { SEGMENT_ROM_START(segment_menu_level), SEGMENT_ROM_END(segment_menu_level) },       // ROMDATATBL_MENU_LEVEL
    { SEGMENT_ROM_START(segment_menu_main), SEGMENT_ROM_END(segment_menu_main) },         // ROMDATATBL_MENU_MAIN
    { SEGMENT_ROM_START(segment_menu_name), SEGMENT_ROM_END(segment_menu_name) },         // ROMDATATBL_MENU_NAME
    { SEGMENT_ROM_START(segment_menu_p2), SEGMENT_ROM_END(segment_menu_p2) },             // ROMDATATBL_MENU_P2
    { SEGMENT_ROM_START(segment_menu_p4), SEGMENT_ROM_END(segment_menu_p4) },             // ROMDATATBL_MENU_P4
    { SEGMENT_ROM_START(segment_menu_rank), SEGMENT_ROM_END(segment_menu_rank) },         // ROMDATATBL_MENU_RANK
    { SEGMENT_ROM_START(segment_menu_setup), SEGMENT_ROM_END(segment_menu_setup) },       // ROMDATATBL_MENU_SETUP
    { SEGMENT_ROM_START(segment_menu_story), SEGMENT_ROM_END(segment_menu_story) },       // ROMDATATBL_MENU_STORY
    { SEGMENT_ROM_START(segment_menu_cont), SEGMENT_ROM_END(segment_menu_cont) },         // ROMDATATBL_MENU_CONT
    { SEGMENT_ROM_START(segment_menu_kasa), SEGMENT_ROM_END(segment_menu_kasa) },         // ROMDATATBL_MENU_KASA
    { SEGMENT_ROM_START(segment_tutorial_data), SEGMENT_ROM_END(segment_tutorial_data) }, // ROMDATATBL_TUTORIAL_KASA
};

static_assert(ARRAY_COUNT(_romDataTbl) == ROMDATATBL_MAX, "");

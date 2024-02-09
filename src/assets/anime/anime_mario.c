#include "tex_func.h"
#include "char_anime.h"

#include "libc/assert.h"
#include "macros_defines.h"
#include "alignment.h"

extern TiTexData anime_mario_titexdata[];
extern s32 anime_mario_titexdata_len;
extern u8 *anime_mario_metadata[];
extern s32 anime_mario_metadata_len;

AnimeHeader anime_mario_header = {
    anime_mario_titexdata,
    &anime_mario_titexdata_len,
    anime_mario_metadata,
    &anime_mario_metadata_len,
};

/* titexdata_00 */

#define anime_mario_titexdata_00_texs_tex_width 64
#define anime_mario_titexdata_00_texs_tex_height 64
extern u8 anime_mario_titexdata_00_texs_tex[];
extern u16 anime_mario_titexdata_00_texs_tlut[];

TiTexDataTextures anime_mario_titexdata_00_texs = {
    anime_mario_titexdata_00_texs_tlut,
    anime_mario_titexdata_00_texs_tex,
};

u16 anime_mario_titexdata_00_info[] = {
    anime_mario_titexdata_00_texs_tex_width, anime_mario_titexdata_00_texs_tex_height, TITEX_FORMAT_8, TITEX_FLAGS_BLOCK,
};

u16 anime_mario_titexdata_00_texs_tlut[] ALIGNED(8) = {
#include "assets/anime/anime_mario/anime_mario_titexdata_00_texs_tlut.rgba16.inc"
};

u8 anime_mario_titexdata_00_texs_tex[] ALIGNED(8) = {
#include "assets/anime/anime_mario/anime_mario_titexdata_00_texs_tex.i8.inc"
};

static_assert(ARRAY_COUNT(anime_mario_titexdata_00_texs_tlut) == 16 * 16, "The dimensions of `anime_mario_titexdata_00_texs_tlut` does not match the size of the actual tlut");
static_assert(ARRAY_COUNT(anime_mario_titexdata_00_texs_tex) == anime_mario_titexdata_00_texs_tex_width * anime_mario_titexdata_00_texs_tex_height, "The dimensions of `anime_mario_titexdata_00_texs_tex` does not match the size of the actual texture");

/* titexdata_01 */

#define anime_mario_titexdata_01_texs_tex_width 64
#define anime_mario_titexdata_01_texs_tex_height 64
extern u8 anime_mario_titexdata_01_texs_tex[];

TiTexDataTextures anime_mario_titexdata_01_texs = {
    NULL,
    anime_mario_titexdata_01_texs_tex,
};

u16 anime_mario_titexdata_01_info[] = {
    anime_mario_titexdata_01_texs_tex_width, anime_mario_titexdata_01_texs_tex_height, TITEX_FORMAT_8, TITEX_FLAGS_BLOCK,
};

u8 anime_mario_titexdata_01_texs_tex[] ALIGNED(8) = {
#include "assets/anime/anime_mario/anime_mario_titexdata_01_texs_tex.i8.inc"
};

static_assert(ARRAY_COUNT(anime_mario_titexdata_01_texs_tex) == anime_mario_titexdata_01_texs_tex_width * anime_mario_titexdata_01_texs_tex_height, "The dimensions of `anime_mario_titexdata_01_texs_tex` does not match the size of the actual texture");

/* titexdata_02 */

#define anime_mario_titexdata_02_texs_tex_width 64
#define anime_mario_titexdata_02_texs_tex_height 64
extern u8 anime_mario_titexdata_02_texs_tex[];

TiTexDataTextures anime_mario_titexdata_02_texs = {
    NULL,
    anime_mario_titexdata_02_texs_tex,
};

u16 anime_mario_titexdata_02_info[] = {
    anime_mario_titexdata_02_texs_tex_width, anime_mario_titexdata_02_texs_tex_height, TITEX_FORMAT_8, TITEX_FLAGS_BLOCK,
};

u8 anime_mario_titexdata_02_texs_tex[] ALIGNED(8) = {
#include "assets/anime/anime_mario/anime_mario_titexdata_02_texs_tex.i8.inc"
};

static_assert(ARRAY_COUNT(anime_mario_titexdata_02_texs_tex) == anime_mario_titexdata_02_texs_tex_width * anime_mario_titexdata_02_texs_tex_height, "The dimensions of `anime_mario_titexdata_02_texs_tex` does not match the size of the actual texture");

/* titexdata_03 */

#define anime_mario_titexdata_03_texs_tex_width 64
#define anime_mario_titexdata_03_texs_tex_height 64
extern u8 anime_mario_titexdata_03_texs_tex[];

TiTexDataTextures anime_mario_titexdata_03_texs = {
    NULL,
    anime_mario_titexdata_03_texs_tex,
};

u16 anime_mario_titexdata_03_info[] = {
    anime_mario_titexdata_03_texs_tex_width, anime_mario_titexdata_03_texs_tex_height, TITEX_FORMAT_8, TITEX_FLAGS_BLOCK,
};

u8 anime_mario_titexdata_03_texs_tex[] ALIGNED(8) = {
#include "assets/anime/anime_mario/anime_mario_titexdata_03_texs_tex.i8.inc"
};

static_assert(ARRAY_COUNT(anime_mario_titexdata_03_texs_tex) == anime_mario_titexdata_03_texs_tex_width * anime_mario_titexdata_03_texs_tex_height, "The dimensions of `anime_mario_titexdata_03_texs_tex` does not match the size of the actual texture");

/* titexdata_04 */

#define anime_mario_titexdata_04_texs_tex_width 64
#define anime_mario_titexdata_04_texs_tex_height 64
extern u8 anime_mario_titexdata_04_texs_tex[];

TiTexDataTextures anime_mario_titexdata_04_texs = {
    NULL,
    anime_mario_titexdata_04_texs_tex,
};

u16 anime_mario_titexdata_04_info[] = {
    anime_mario_titexdata_04_texs_tex_width, anime_mario_titexdata_04_texs_tex_height, TITEX_FORMAT_8, TITEX_FLAGS_BLOCK,
};

u8 anime_mario_titexdata_04_texs_tex[] ALIGNED(8) = {
#include "assets/anime/anime_mario/anime_mario_titexdata_04_texs_tex.i8.inc"
};

static_assert(ARRAY_COUNT(anime_mario_titexdata_04_texs_tex) == anime_mario_titexdata_04_texs_tex_width * anime_mario_titexdata_04_texs_tex_height, "The dimensions of `anime_mario_titexdata_04_texs_tex` does not match the size of the actual texture");

/* titexdata_05 */

#define anime_mario_titexdata_05_texs_tex_width 64
#define anime_mario_titexdata_05_texs_tex_height 64
extern u8 anime_mario_titexdata_05_texs_tex[];

TiTexDataTextures anime_mario_titexdata_05_texs = {
    NULL,
    anime_mario_titexdata_05_texs_tex,
};

u16 anime_mario_titexdata_05_info[] = {
    anime_mario_titexdata_05_texs_tex_width, anime_mario_titexdata_05_texs_tex_height, TITEX_FORMAT_8, TITEX_FLAGS_BLOCK,
};

u8 anime_mario_titexdata_05_texs_tex[] ALIGNED(8) = {
#include "assets/anime/anime_mario/anime_mario_titexdata_05_texs_tex.i8.inc"
};

static_assert(ARRAY_COUNT(anime_mario_titexdata_05_texs_tex) == anime_mario_titexdata_05_texs_tex_width * anime_mario_titexdata_05_texs_tex_height, "The dimensions of `anime_mario_titexdata_05_texs_tex` does not match the size of the actual texture");

/* titexdata_11 */

#define anime_mario_titexdata_11_texs_tex_width 64
#define anime_mario_titexdata_11_texs_tex_height 64
extern u8 anime_mario_titexdata_11_texs_tex[];

TiTexDataTextures anime_mario_titexdata_11_texs = {
    NULL,
    anime_mario_titexdata_11_texs_tex,
};

u16 anime_mario_titexdata_11_info[] = {
    anime_mario_titexdata_11_texs_tex_width, anime_mario_titexdata_11_texs_tex_height, TITEX_FORMAT_8, TITEX_FLAGS_BLOCK,
};

u8 anime_mario_titexdata_11_texs_tex[] ALIGNED(8) = {
#include "assets/anime/anime_mario/anime_mario_titexdata_11_texs_tex.i8.inc"
};

static_assert(ARRAY_COUNT(anime_mario_titexdata_11_texs_tex) == anime_mario_titexdata_11_texs_tex_width * anime_mario_titexdata_11_texs_tex_height, "The dimensions of `anime_mario_titexdata_11_texs_tex` does not match the size of the actual texture");

/* titexdata_12 */

#define anime_mario_titexdata_12_texs_tex_width 64
#define anime_mario_titexdata_12_texs_tex_height 64
extern u8 anime_mario_titexdata_12_texs_tex[];

TiTexDataTextures anime_mario_titexdata_12_texs = {
    NULL,
    anime_mario_titexdata_12_texs_tex,
};

u16 anime_mario_titexdata_12_info[] = {
    anime_mario_titexdata_12_texs_tex_width, anime_mario_titexdata_12_texs_tex_height, TITEX_FORMAT_8, TITEX_FLAGS_BLOCK,
};

u8 anime_mario_titexdata_12_texs_tex[] ALIGNED(8) = {
#include "assets/anime/anime_mario/anime_mario_titexdata_12_texs_tex.i8.inc"
};

static_assert(ARRAY_COUNT(anime_mario_titexdata_12_texs_tex) == anime_mario_titexdata_12_texs_tex_width * anime_mario_titexdata_12_texs_tex_height, "The dimensions of `anime_mario_titexdata_12_texs_tex` does not match the size of the actual texture");

/* titexdata_13 */

#define anime_mario_titexdata_13_texs_tex_width 64
#define anime_mario_titexdata_13_texs_tex_height 64
extern u8 anime_mario_titexdata_13_texs_tex[];

TiTexDataTextures anime_mario_titexdata_13_texs = {
    NULL,
    anime_mario_titexdata_13_texs_tex,
};

u16 anime_mario_titexdata_13_info[] = {
    anime_mario_titexdata_13_texs_tex_width, anime_mario_titexdata_13_texs_tex_height, TITEX_FORMAT_8, TITEX_FLAGS_BLOCK,
};

u8 anime_mario_titexdata_13_texs_tex[] ALIGNED(8) = {
#include "assets/anime/anime_mario/anime_mario_titexdata_13_texs_tex.i8.inc"
};

static_assert(ARRAY_COUNT(anime_mario_titexdata_13_texs_tex) == anime_mario_titexdata_13_texs_tex_width * anime_mario_titexdata_13_texs_tex_height, "The dimensions of `anime_mario_titexdata_13_texs_tex` does not match the size of the actual texture");

/* titexdata_14 */

#define anime_mario_titexdata_14_texs_tex_width 64
#define anime_mario_titexdata_14_texs_tex_height 64
extern u8 anime_mario_titexdata_14_texs_tex[];

TiTexDataTextures anime_mario_titexdata_14_texs = {
    NULL,
    anime_mario_titexdata_14_texs_tex,
};

u16 anime_mario_titexdata_14_info[] = {
    anime_mario_titexdata_14_texs_tex_width, anime_mario_titexdata_14_texs_tex_height, TITEX_FORMAT_8, TITEX_FLAGS_BLOCK,
};

u8 anime_mario_titexdata_14_texs_tex[] ALIGNED(8) = {
#include "assets/anime/anime_mario/anime_mario_titexdata_14_texs_tex.i8.inc"
};

static_assert(ARRAY_COUNT(anime_mario_titexdata_14_texs_tex) == anime_mario_titexdata_14_texs_tex_width * anime_mario_titexdata_14_texs_tex_height, "The dimensions of `anime_mario_titexdata_14_texs_tex` does not match the size of the actual texture");

/* titexdata_15 */

#define anime_mario_titexdata_15_texs_tex_width 64
#define anime_mario_titexdata_15_texs_tex_height 64
extern u8 anime_mario_titexdata_15_texs_tex[];

TiTexDataTextures anime_mario_titexdata_15_texs = {
    NULL,
    anime_mario_titexdata_15_texs_tex,
};

u16 anime_mario_titexdata_15_info[] = {
    anime_mario_titexdata_15_texs_tex_width, anime_mario_titexdata_15_texs_tex_height, TITEX_FORMAT_8, TITEX_FLAGS_BLOCK,
};

u8 anime_mario_titexdata_15_texs_tex[] ALIGNED(8) = {
#include "assets/anime/anime_mario/anime_mario_titexdata_15_texs_tex.i8.inc"
};

static_assert(ARRAY_COUNT(anime_mario_titexdata_15_texs_tex) == anime_mario_titexdata_15_texs_tex_width * anime_mario_titexdata_15_texs_tex_height, "The dimensions of `anime_mario_titexdata_15_texs_tex` does not match the size of the actual texture");

/* titexdata_16 */

#define anime_mario_titexdata_16_texs_tex_width 64
#define anime_mario_titexdata_16_texs_tex_height 64
extern u8 anime_mario_titexdata_16_texs_tex[];

TiTexDataTextures anime_mario_titexdata_16_texs = {
    NULL,
    anime_mario_titexdata_16_texs_tex,
};

u16 anime_mario_titexdata_16_info[] = {
    anime_mario_titexdata_16_texs_tex_width, anime_mario_titexdata_16_texs_tex_height, TITEX_FORMAT_8, TITEX_FLAGS_BLOCK,
};

u8 anime_mario_titexdata_16_texs_tex[] ALIGNED(8) = {
#include "assets/anime/anime_mario/anime_mario_titexdata_16_texs_tex.i8.inc"
};

static_assert(ARRAY_COUNT(anime_mario_titexdata_16_texs_tex) == anime_mario_titexdata_16_texs_tex_width * anime_mario_titexdata_16_texs_tex_height, "The dimensions of `anime_mario_titexdata_16_texs_tex` does not match the size of the actual texture");

/* titexdata_17 */

#define anime_mario_titexdata_17_texs_tex_width 64
#define anime_mario_titexdata_17_texs_tex_height 64
extern u8 anime_mario_titexdata_17_texs_tex[];

TiTexDataTextures anime_mario_titexdata_17_texs = {
    NULL,
    anime_mario_titexdata_17_texs_tex,
};

u16 anime_mario_titexdata_17_info[] = {
    anime_mario_titexdata_17_texs_tex_width, anime_mario_titexdata_17_texs_tex_height, TITEX_FORMAT_8, TITEX_FLAGS_BLOCK,
};

u8 anime_mario_titexdata_17_texs_tex[] ALIGNED(8) = {
#include "assets/anime/anime_mario/anime_mario_titexdata_17_texs_tex.i8.inc"
};

static_assert(ARRAY_COUNT(anime_mario_titexdata_17_texs_tex) == anime_mario_titexdata_17_texs_tex_width * anime_mario_titexdata_17_texs_tex_height, "The dimensions of `anime_mario_titexdata_17_texs_tex` does not match the size of the actual texture");

/* titexdata_18 */

#define anime_mario_titexdata_18_texs_tex_width 64
#define anime_mario_titexdata_18_texs_tex_height 64
extern u8 anime_mario_titexdata_18_texs_tex[];

TiTexDataTextures anime_mario_titexdata_18_texs = {
    NULL,
    anime_mario_titexdata_18_texs_tex,
};

u16 anime_mario_titexdata_18_info[] = {
    anime_mario_titexdata_18_texs_tex_width, anime_mario_titexdata_18_texs_tex_height, TITEX_FORMAT_8, TITEX_FLAGS_BLOCK,
};

u8 anime_mario_titexdata_18_texs_tex[] ALIGNED(8) = {
#include "assets/anime/anime_mario/anime_mario_titexdata_18_texs_tex.i8.inc"
};

static_assert(ARRAY_COUNT(anime_mario_titexdata_18_texs_tex) == anime_mario_titexdata_18_texs_tex_width * anime_mario_titexdata_18_texs_tex_height, "The dimensions of `anime_mario_titexdata_18_texs_tex` does not match the size of the actual texture");

/* titexdata_19 */

#define anime_mario_titexdata_19_texs_tex_width 64
#define anime_mario_titexdata_19_texs_tex_height 64
extern u8 anime_mario_titexdata_19_texs_tex[];

TiTexDataTextures anime_mario_titexdata_19_texs = {
    NULL,
    anime_mario_titexdata_19_texs_tex,
};

u16 anime_mario_titexdata_19_info[] = {
    anime_mario_titexdata_19_texs_tex_width, anime_mario_titexdata_19_texs_tex_height, TITEX_FORMAT_8, TITEX_FLAGS_BLOCK,
};

u8 anime_mario_titexdata_19_texs_tex[] ALIGNED(8) = {
#include "assets/anime/anime_mario/anime_mario_titexdata_19_texs_tex.i8.inc"
};

static_assert(ARRAY_COUNT(anime_mario_titexdata_19_texs_tex) == anime_mario_titexdata_19_texs_tex_width * anime_mario_titexdata_19_texs_tex_height, "The dimensions of `anime_mario_titexdata_19_texs_tex` does not match the size of the actual texture");

/* titexdata_20 */

#define anime_mario_titexdata_20_texs_tex_width 64
#define anime_mario_titexdata_20_texs_tex_height 64
extern u8 anime_mario_titexdata_20_texs_tex[];

TiTexDataTextures anime_mario_titexdata_20_texs = {
    NULL,
    anime_mario_titexdata_20_texs_tex,
};

u16 anime_mario_titexdata_20_info[] = {
    anime_mario_titexdata_20_texs_tex_width, anime_mario_titexdata_20_texs_tex_height, TITEX_FORMAT_8, TITEX_FLAGS_BLOCK,
};

u8 anime_mario_titexdata_20_texs_tex[] ALIGNED(8) = {
#include "assets/anime/anime_mario/anime_mario_titexdata_20_texs_tex.i8.inc"
};

static_assert(ARRAY_COUNT(anime_mario_titexdata_20_texs_tex) == anime_mario_titexdata_20_texs_tex_width * anime_mario_titexdata_20_texs_tex_height, "The dimensions of `anime_mario_titexdata_20_texs_tex` does not match the size of the actual texture");

/* titexdata_21 */

#define anime_mario_titexdata_21_texs_tex_width 64
#define anime_mario_titexdata_21_texs_tex_height 64
extern u8 anime_mario_titexdata_21_texs_tex[];

TiTexDataTextures anime_mario_titexdata_21_texs = {
    NULL,
    anime_mario_titexdata_21_texs_tex,
};

u16 anime_mario_titexdata_21_info[] = {
    anime_mario_titexdata_21_texs_tex_width, anime_mario_titexdata_21_texs_tex_height, TITEX_FORMAT_8, TITEX_FLAGS_BLOCK,
};

u8 anime_mario_titexdata_21_texs_tex[] ALIGNED(8) = {
#include "assets/anime/anime_mario/anime_mario_titexdata_21_texs_tex.i8.inc"
};

static_assert(ARRAY_COUNT(anime_mario_titexdata_21_texs_tex) == anime_mario_titexdata_21_texs_tex_width * anime_mario_titexdata_21_texs_tex_height, "The dimensions of `anime_mario_titexdata_21_texs_tex` does not match the size of the actual texture");

/* titexdata_22 */

#define anime_mario_titexdata_22_texs_tex_width 64
#define anime_mario_titexdata_22_texs_tex_height 64
extern u8 anime_mario_titexdata_22_texs_tex[];

TiTexDataTextures anime_mario_titexdata_22_texs = {
    NULL,
    anime_mario_titexdata_22_texs_tex,
};

u16 anime_mario_titexdata_22_info[] = {
    anime_mario_titexdata_22_texs_tex_width, anime_mario_titexdata_22_texs_tex_height, TITEX_FORMAT_8, TITEX_FLAGS_BLOCK,
};

u8 anime_mario_titexdata_22_texs_tex[] ALIGNED(8) = {
#include "assets/anime/anime_mario/anime_mario_titexdata_22_texs_tex.i8.inc"
};

static_assert(ARRAY_COUNT(anime_mario_titexdata_22_texs_tex) == anime_mario_titexdata_22_texs_tex_width * anime_mario_titexdata_22_texs_tex_height, "The dimensions of `anime_mario_titexdata_22_texs_tex` does not match the size of the actual texture");

/* titexdata_23 */

#define anime_mario_titexdata_23_texs_tex_width 64
#define anime_mario_titexdata_23_texs_tex_height 64
extern u8 anime_mario_titexdata_23_texs_tex[];

TiTexDataTextures anime_mario_titexdata_23_texs = {
    NULL,
    anime_mario_titexdata_23_texs_tex,
};

u16 anime_mario_titexdata_23_info[] = {
    anime_mario_titexdata_23_texs_tex_width, anime_mario_titexdata_23_texs_tex_height, TITEX_FORMAT_8, TITEX_FLAGS_BLOCK,
};

u8 anime_mario_titexdata_23_texs_tex[] ALIGNED(8) = {
#include "assets/anime/anime_mario/anime_mario_titexdata_23_texs_tex.i8.inc"
};

static_assert(ARRAY_COUNT(anime_mario_titexdata_23_texs_tex) == anime_mario_titexdata_23_texs_tex_width * anime_mario_titexdata_23_texs_tex_height, "The dimensions of `anime_mario_titexdata_23_texs_tex` does not match the size of the actual texture");

/* titexdata_24 */

#define anime_mario_titexdata_24_texs_tex_width 64
#define anime_mario_titexdata_24_texs_tex_height 64
extern u8 anime_mario_titexdata_24_texs_tex[];

TiTexDataTextures anime_mario_titexdata_24_texs = {
    NULL,
    anime_mario_titexdata_24_texs_tex,
};

u16 anime_mario_titexdata_24_info[] = {
    anime_mario_titexdata_24_texs_tex_width, anime_mario_titexdata_24_texs_tex_height, TITEX_FORMAT_8, TITEX_FLAGS_BLOCK,
};

u8 anime_mario_titexdata_24_texs_tex[] ALIGNED(8) = {
#include "assets/anime/anime_mario/anime_mario_titexdata_24_texs_tex.i8.inc"
};

static_assert(ARRAY_COUNT(anime_mario_titexdata_24_texs_tex) == anime_mario_titexdata_24_texs_tex_width * anime_mario_titexdata_24_texs_tex_height, "The dimensions of `anime_mario_titexdata_24_texs_tex` does not match the size of the actual texture");

/* titexdata_25 */

#define anime_mario_titexdata_25_texs_tex_width 64
#define anime_mario_titexdata_25_texs_tex_height 64
extern u8 anime_mario_titexdata_25_texs_tex[];

TiTexDataTextures anime_mario_titexdata_25_texs = {
    NULL,
    anime_mario_titexdata_25_texs_tex,
};

u16 anime_mario_titexdata_25_info[] = {
    anime_mario_titexdata_25_texs_tex_width, anime_mario_titexdata_25_texs_tex_height, TITEX_FORMAT_8, TITEX_FLAGS_BLOCK,
};

u8 anime_mario_titexdata_25_texs_tex[] ALIGNED(8) = {
#include "assets/anime/anime_mario/anime_mario_titexdata_25_texs_tex.i8.inc"
};

static_assert(ARRAY_COUNT(anime_mario_titexdata_25_texs_tex) == anime_mario_titexdata_25_texs_tex_width * anime_mario_titexdata_25_texs_tex_height, "The dimensions of `anime_mario_titexdata_25_texs_tex` does not match the size of the actual texture");

/* titexdata_26 */

#define anime_mario_titexdata_26_texs_tex_width 64
#define anime_mario_titexdata_26_texs_tex_height 64
extern u8 anime_mario_titexdata_26_texs_tex[];

TiTexDataTextures anime_mario_titexdata_26_texs = {
    NULL,
    anime_mario_titexdata_26_texs_tex,
};

u16 anime_mario_titexdata_26_info[] = {
    anime_mario_titexdata_26_texs_tex_width, anime_mario_titexdata_26_texs_tex_height, TITEX_FORMAT_8, TITEX_FLAGS_BLOCK,
};

u8 anime_mario_titexdata_26_texs_tex[] ALIGNED(8) = {
#include "assets/anime/anime_mario/anime_mario_titexdata_26_texs_tex.i8.inc"
};

static_assert(ARRAY_COUNT(anime_mario_titexdata_26_texs_tex) == anime_mario_titexdata_26_texs_tex_width * anime_mario_titexdata_26_texs_tex_height, "The dimensions of `anime_mario_titexdata_26_texs_tex` does not match the size of the actual texture");

/* titexdata_27 */

#define anime_mario_titexdata_27_texs_tex_width 64
#define anime_mario_titexdata_27_texs_tex_height 64
extern u8 anime_mario_titexdata_27_texs_tex[];

TiTexDataTextures anime_mario_titexdata_27_texs = {
    NULL,
    anime_mario_titexdata_27_texs_tex,
};

u16 anime_mario_titexdata_27_info[] = {
    anime_mario_titexdata_27_texs_tex_width, anime_mario_titexdata_27_texs_tex_height, TITEX_FORMAT_8, TITEX_FLAGS_BLOCK,
};

u8 anime_mario_titexdata_27_texs_tex[] ALIGNED(8) = {
#include "assets/anime/anime_mario/anime_mario_titexdata_27_texs_tex.i8.inc"
};

static_assert(ARRAY_COUNT(anime_mario_titexdata_27_texs_tex) == anime_mario_titexdata_27_texs_tex_width * anime_mario_titexdata_27_texs_tex_height, "The dimensions of `anime_mario_titexdata_27_texs_tex` does not match the size of the actual texture");

/* titexdata_28 */

#define anime_mario_titexdata_28_texs_tex_width 64
#define anime_mario_titexdata_28_texs_tex_height 64
extern u8 anime_mario_titexdata_28_texs_tex[];

TiTexDataTextures anime_mario_titexdata_28_texs = {
    NULL,
    anime_mario_titexdata_28_texs_tex,
};

u16 anime_mario_titexdata_28_info[] = {
    anime_mario_titexdata_28_texs_tex_width, anime_mario_titexdata_28_texs_tex_height, TITEX_FORMAT_8, TITEX_FLAGS_BLOCK,
};

u8 anime_mario_titexdata_28_texs_tex[] ALIGNED(8) = {
#include "assets/anime/anime_mario/anime_mario_titexdata_28_texs_tex.i8.inc"
};

static_assert(ARRAY_COUNT(anime_mario_titexdata_28_texs_tex) == anime_mario_titexdata_28_texs_tex_width * anime_mario_titexdata_28_texs_tex_height, "The dimensions of `anime_mario_titexdata_28_texs_tex` does not match the size of the actual texture");

/* titexdata_29 */

#define anime_mario_titexdata_29_texs_tex_width 64
#define anime_mario_titexdata_29_texs_tex_height 64
extern u8 anime_mario_titexdata_29_texs_tex[];

TiTexDataTextures anime_mario_titexdata_29_texs = {
    NULL,
    anime_mario_titexdata_29_texs_tex,
};

u16 anime_mario_titexdata_29_info[] = {
    anime_mario_titexdata_29_texs_tex_width, anime_mario_titexdata_29_texs_tex_height, TITEX_FORMAT_8, TITEX_FLAGS_BLOCK,
};

u8 anime_mario_titexdata_29_texs_tex[] ALIGNED(8) = {
#include "assets/anime/anime_mario/anime_mario_titexdata_29_texs_tex.i8.inc"
};

static_assert(ARRAY_COUNT(anime_mario_titexdata_29_texs_tex) == anime_mario_titexdata_29_texs_tex_width * anime_mario_titexdata_29_texs_tex_height, "The dimensions of `anime_mario_titexdata_29_texs_tex` does not match the size of the actual texture");

/* titexdata_30 */

#define anime_mario_titexdata_30_texs_tex_width 64
#define anime_mario_titexdata_30_texs_tex_height 64
extern u8 anime_mario_titexdata_30_texs_tex[];

TiTexDataTextures anime_mario_titexdata_30_texs = {
    NULL,
    anime_mario_titexdata_30_texs_tex,
};

u16 anime_mario_titexdata_30_info[] = {
    anime_mario_titexdata_30_texs_tex_width, anime_mario_titexdata_30_texs_tex_height, TITEX_FORMAT_8, TITEX_FLAGS_BLOCK,
};

u8 anime_mario_titexdata_30_texs_tex[] ALIGNED(8) = {
#include "assets/anime/anime_mario/anime_mario_titexdata_30_texs_tex.i8.inc"
};

static_assert(ARRAY_COUNT(anime_mario_titexdata_30_texs_tex) == anime_mario_titexdata_30_texs_tex_width * anime_mario_titexdata_30_texs_tex_height, "The dimensions of `anime_mario_titexdata_30_texs_tex` does not match the size of the actual texture");

/* titexdata_31 */

#define anime_mario_titexdata_31_texs_tex_width 64
#define anime_mario_titexdata_31_texs_tex_height 64
extern u8 anime_mario_titexdata_31_texs_tex[];

TiTexDataTextures anime_mario_titexdata_31_texs = {
    NULL,
    anime_mario_titexdata_31_texs_tex,
};

u16 anime_mario_titexdata_31_info[] = {
    anime_mario_titexdata_31_texs_tex_width, anime_mario_titexdata_31_texs_tex_height, TITEX_FORMAT_8, TITEX_FLAGS_BLOCK,
};

u8 anime_mario_titexdata_31_texs_tex[] ALIGNED(8) = {
#include "assets/anime/anime_mario/anime_mario_titexdata_31_texs_tex.i8.inc"
};

static_assert(ARRAY_COUNT(anime_mario_titexdata_31_texs_tex) == anime_mario_titexdata_31_texs_tex_width * anime_mario_titexdata_31_texs_tex_height, "The dimensions of `anime_mario_titexdata_31_texs_tex` does not match the size of the actual texture");

/* titexdata_32 */

#define anime_mario_titexdata_32_texs_tex_width 64
#define anime_mario_titexdata_32_texs_tex_height 64
extern u8 anime_mario_titexdata_32_texs_tex[];

TiTexDataTextures anime_mario_titexdata_32_texs = {
    NULL,
    anime_mario_titexdata_32_texs_tex,
};

u16 anime_mario_titexdata_32_info[] = {
    anime_mario_titexdata_32_texs_tex_width, anime_mario_titexdata_32_texs_tex_height, TITEX_FORMAT_8, TITEX_FLAGS_BLOCK,
};

u8 anime_mario_titexdata_32_texs_tex[] ALIGNED(8) = {
#include "assets/anime/anime_mario/anime_mario_titexdata_32_texs_tex.i8.inc"
};

static_assert(ARRAY_COUNT(anime_mario_titexdata_32_texs_tex) == anime_mario_titexdata_32_texs_tex_width * anime_mario_titexdata_32_texs_tex_height, "The dimensions of `anime_mario_titexdata_32_texs_tex` does not match the size of the actual texture");

/* titexdata_33 */

#define anime_mario_titexdata_33_texs_tex_width 64
#define anime_mario_titexdata_33_texs_tex_height 64
extern u8 anime_mario_titexdata_33_texs_tex[];

TiTexDataTextures anime_mario_titexdata_33_texs = {
    NULL,
    anime_mario_titexdata_33_texs_tex,
};

u16 anime_mario_titexdata_33_info[] = {
    anime_mario_titexdata_33_texs_tex_width, anime_mario_titexdata_33_texs_tex_height, TITEX_FORMAT_8, TITEX_FLAGS_BLOCK,
};

u8 anime_mario_titexdata_33_texs_tex[] ALIGNED(8) = {
#include "assets/anime/anime_mario/anime_mario_titexdata_33_texs_tex.i8.inc"
};

static_assert(ARRAY_COUNT(anime_mario_titexdata_33_texs_tex) == anime_mario_titexdata_33_texs_tex_width * anime_mario_titexdata_33_texs_tex_height, "The dimensions of `anime_mario_titexdata_33_texs_tex` does not match the size of the actual texture");

/* titexdata_34 */

#define anime_mario_titexdata_34_texs_tex_width 64
#define anime_mario_titexdata_34_texs_tex_height 64
extern u8 anime_mario_titexdata_34_texs_tex[];

TiTexDataTextures anime_mario_titexdata_34_texs = {
    NULL,
    anime_mario_titexdata_34_texs_tex,
};

u16 anime_mario_titexdata_34_info[] = {
    anime_mario_titexdata_34_texs_tex_width, anime_mario_titexdata_34_texs_tex_height, TITEX_FORMAT_8, TITEX_FLAGS_BLOCK,
};

u8 anime_mario_titexdata_34_texs_tex[] ALIGNED(8) = {
#include "assets/anime/anime_mario/anime_mario_titexdata_34_texs_tex.i8.inc"
};

static_assert(ARRAY_COUNT(anime_mario_titexdata_34_texs_tex) == anime_mario_titexdata_34_texs_tex_width * anime_mario_titexdata_34_texs_tex_height, "The dimensions of `anime_mario_titexdata_34_texs_tex` does not match the size of the actual texture");

/* titexdata_35 */

#define anime_mario_titexdata_35_texs_tex_width 64
#define anime_mario_titexdata_35_texs_tex_height 64
extern u8 anime_mario_titexdata_35_texs_tex[];

TiTexDataTextures anime_mario_titexdata_35_texs = {
    NULL,
    anime_mario_titexdata_35_texs_tex,
};

u16 anime_mario_titexdata_35_info[] = {
    anime_mario_titexdata_35_texs_tex_width, anime_mario_titexdata_35_texs_tex_height, TITEX_FORMAT_8, TITEX_FLAGS_BLOCK,
};

u8 anime_mario_titexdata_35_texs_tex[] ALIGNED(8) = {
#include "assets/anime/anime_mario/anime_mario_titexdata_35_texs_tex.i8.inc"
};

static_assert(ARRAY_COUNT(anime_mario_titexdata_35_texs_tex) == anime_mario_titexdata_35_texs_tex_width * anime_mario_titexdata_35_texs_tex_height, "The dimensions of `anime_mario_titexdata_35_texs_tex` does not match the size of the actual texture");

/* titexdata_36 */

#define anime_mario_titexdata_36_texs_tex_width 64
#define anime_mario_titexdata_36_texs_tex_height 64
extern u8 anime_mario_titexdata_36_texs_tex[];

TiTexDataTextures anime_mario_titexdata_36_texs = {
    NULL,
    anime_mario_titexdata_36_texs_tex,
};

u16 anime_mario_titexdata_36_info[] = {
    anime_mario_titexdata_36_texs_tex_width, anime_mario_titexdata_36_texs_tex_height, TITEX_FORMAT_8, TITEX_FLAGS_BLOCK,
};

u8 anime_mario_titexdata_36_texs_tex[] ALIGNED(8) = {
#include "assets/anime/anime_mario/anime_mario_titexdata_36_texs_tex.i8.inc"
};

static_assert(ARRAY_COUNT(anime_mario_titexdata_36_texs_tex) == anime_mario_titexdata_36_texs_tex_width * anime_mario_titexdata_36_texs_tex_height, "The dimensions of `anime_mario_titexdata_36_texs_tex` does not match the size of the actual texture");

/* titexdata_37 */

#define anime_mario_titexdata_37_texs_tex_width 64
#define anime_mario_titexdata_37_texs_tex_height 64
extern u8 anime_mario_titexdata_37_texs_tex[];

TiTexDataTextures anime_mario_titexdata_37_texs = {
    NULL,
    anime_mario_titexdata_37_texs_tex,
};

u16 anime_mario_titexdata_37_info[] = {
    anime_mario_titexdata_37_texs_tex_width, anime_mario_titexdata_37_texs_tex_height, TITEX_FORMAT_8, TITEX_FLAGS_BLOCK,
};

u8 anime_mario_titexdata_37_texs_tex[] ALIGNED(8) = {
#include "assets/anime/anime_mario/anime_mario_titexdata_37_texs_tex.i8.inc"
};

static_assert(ARRAY_COUNT(anime_mario_titexdata_37_texs_tex) == anime_mario_titexdata_37_texs_tex_width * anime_mario_titexdata_37_texs_tex_height, "The dimensions of `anime_mario_titexdata_37_texs_tex` does not match the size of the actual texture");

/* titexdata_38 */

#define anime_mario_titexdata_38_texs_tex_width 64
#define anime_mario_titexdata_38_texs_tex_height 64
extern u8 anime_mario_titexdata_38_texs_tex[];

TiTexDataTextures anime_mario_titexdata_38_texs = {
    NULL,
    anime_mario_titexdata_38_texs_tex,
};

u16 anime_mario_titexdata_38_info[] = {
    anime_mario_titexdata_38_texs_tex_width, anime_mario_titexdata_38_texs_tex_height, TITEX_FORMAT_8, TITEX_FLAGS_BLOCK,
};

u8 anime_mario_titexdata_38_texs_tex[] ALIGNED(8) = {
#include "assets/anime/anime_mario/anime_mario_titexdata_38_texs_tex.i8.inc"
};

static_assert(ARRAY_COUNT(anime_mario_titexdata_38_texs_tex) == anime_mario_titexdata_38_texs_tex_width * anime_mario_titexdata_38_texs_tex_height, "The dimensions of `anime_mario_titexdata_38_texs_tex` does not match the size of the actual texture");

/* titexdata_39 */

#define anime_mario_titexdata_39_texs_tex_width 64
#define anime_mario_titexdata_39_texs_tex_height 64
extern u8 anime_mario_titexdata_39_texs_tex[];

TiTexDataTextures anime_mario_titexdata_39_texs = {
    NULL,
    anime_mario_titexdata_39_texs_tex,
};

u16 anime_mario_titexdata_39_info[] = {
    anime_mario_titexdata_39_texs_tex_width, anime_mario_titexdata_39_texs_tex_height, TITEX_FORMAT_8, TITEX_FLAGS_BLOCK,
};

u8 anime_mario_titexdata_39_texs_tex[] ALIGNED(8) = {
#include "assets/anime/anime_mario/anime_mario_titexdata_39_texs_tex.i8.inc"
};

static_assert(ARRAY_COUNT(anime_mario_titexdata_39_texs_tex) == anime_mario_titexdata_39_texs_tex_width * anime_mario_titexdata_39_texs_tex_height, "The dimensions of `anime_mario_titexdata_39_texs_tex` does not match the size of the actual texture");

/* titexdata_40 */

#define anime_mario_titexdata_40_texs_tex_width 64
#define anime_mario_titexdata_40_texs_tex_height 64
extern u8 anime_mario_titexdata_40_texs_tex[];

TiTexDataTextures anime_mario_titexdata_40_texs = {
    NULL,
    anime_mario_titexdata_40_texs_tex,
};

u16 anime_mario_titexdata_40_info[] = {
    anime_mario_titexdata_40_texs_tex_width, anime_mario_titexdata_40_texs_tex_height, TITEX_FORMAT_8, TITEX_FLAGS_BLOCK,
};

u8 anime_mario_titexdata_40_texs_tex[] ALIGNED(8) = {
#include "assets/anime/anime_mario/anime_mario_titexdata_40_texs_tex.i8.inc"
};

static_assert(ARRAY_COUNT(anime_mario_titexdata_40_texs_tex) == anime_mario_titexdata_40_texs_tex_width * anime_mario_titexdata_40_texs_tex_height, "The dimensions of `anime_mario_titexdata_40_texs_tex` does not match the size of the actual texture");

/* titexdata_41 */

#define anime_mario_titexdata_41_texs_tex_width 64
#define anime_mario_titexdata_41_texs_tex_height 64
extern u8 anime_mario_titexdata_41_texs_tex[];

TiTexDataTextures anime_mario_titexdata_41_texs = {
    NULL,
    anime_mario_titexdata_41_texs_tex,
};

u16 anime_mario_titexdata_41_info[] = {
    anime_mario_titexdata_41_texs_tex_width, anime_mario_titexdata_41_texs_tex_height, TITEX_FORMAT_8, TITEX_FLAGS_BLOCK,
};

u8 anime_mario_titexdata_41_texs_tex[] ALIGNED(8) = {
#include "assets/anime/anime_mario/anime_mario_titexdata_41_texs_tex.i8.inc"
};

static_assert(ARRAY_COUNT(anime_mario_titexdata_41_texs_tex) == anime_mario_titexdata_41_texs_tex_width * anime_mario_titexdata_41_texs_tex_height, "The dimensions of `anime_mario_titexdata_41_texs_tex` does not match the size of the actual texture");

/* titexdata_42 */

#define anime_mario_titexdata_42_texs_tex_width 64
#define anime_mario_titexdata_42_texs_tex_height 64
extern u8 anime_mario_titexdata_42_texs_tex[];

TiTexDataTextures anime_mario_titexdata_42_texs = {
    NULL,
    anime_mario_titexdata_42_texs_tex,
};

u16 anime_mario_titexdata_42_info[] = {
    anime_mario_titexdata_42_texs_tex_width, anime_mario_titexdata_42_texs_tex_height, TITEX_FORMAT_8, TITEX_FLAGS_BLOCK,
};

u8 anime_mario_titexdata_42_texs_tex[] ALIGNED(8) = {
#include "assets/anime/anime_mario/anime_mario_titexdata_42_texs_tex.i8.inc"
};

static_assert(ARRAY_COUNT(anime_mario_titexdata_42_texs_tex) == anime_mario_titexdata_42_texs_tex_width * anime_mario_titexdata_42_texs_tex_height, "The dimensions of `anime_mario_titexdata_42_texs_tex` does not match the size of the actual texture");

/* titexdata_43 */

#define anime_mario_titexdata_43_texs_tex_width 64
#define anime_mario_titexdata_43_texs_tex_height 64
extern u8 anime_mario_titexdata_43_texs_tex[];

TiTexDataTextures anime_mario_titexdata_43_texs = {
    NULL,
    anime_mario_titexdata_43_texs_tex,
};

u16 anime_mario_titexdata_43_info[] = {
    anime_mario_titexdata_43_texs_tex_width, anime_mario_titexdata_43_texs_tex_height, TITEX_FORMAT_8, TITEX_FLAGS_BLOCK,
};

u8 anime_mario_titexdata_43_texs_tex[] ALIGNED(8) = {
#include "assets/anime/anime_mario/anime_mario_titexdata_43_texs_tex.i8.inc"
};

static_assert(ARRAY_COUNT(anime_mario_titexdata_43_texs_tex) == anime_mario_titexdata_43_texs_tex_width * anime_mario_titexdata_43_texs_tex_height, "The dimensions of `anime_mario_titexdata_43_texs_tex` does not match the size of the actual texture");

/* titexdata_44 */

#define anime_mario_titexdata_44_texs_tex_width 64
#define anime_mario_titexdata_44_texs_tex_height 64
extern u8 anime_mario_titexdata_44_texs_tex[];

TiTexDataTextures anime_mario_titexdata_44_texs = {
    NULL,
    anime_mario_titexdata_44_texs_tex,
};

u16 anime_mario_titexdata_44_info[] = {
    anime_mario_titexdata_44_texs_tex_width, anime_mario_titexdata_44_texs_tex_height, TITEX_FORMAT_8, TITEX_FLAGS_BLOCK,
};

u8 anime_mario_titexdata_44_texs_tex[] ALIGNED(8) = {
#include "assets/anime/anime_mario/anime_mario_titexdata_44_texs_tex.i8.inc"
};

static_assert(ARRAY_COUNT(anime_mario_titexdata_44_texs_tex) == anime_mario_titexdata_44_texs_tex_width * anime_mario_titexdata_44_texs_tex_height, "The dimensions of `anime_mario_titexdata_44_texs_tex` does not match the size of the actual texture");

/* titexdata_45 */

#define anime_mario_titexdata_45_texs_tex_width 64
#define anime_mario_titexdata_45_texs_tex_height 64
extern u8 anime_mario_titexdata_45_texs_tex[];

TiTexDataTextures anime_mario_titexdata_45_texs = {
    NULL,
    anime_mario_titexdata_45_texs_tex,
};

u16 anime_mario_titexdata_45_info[] = {
    anime_mario_titexdata_45_texs_tex_width, anime_mario_titexdata_45_texs_tex_height, TITEX_FORMAT_8, TITEX_FLAGS_BLOCK,
};

u8 anime_mario_titexdata_45_texs_tex[] ALIGNED(8) = {
#include "assets/anime/anime_mario/anime_mario_titexdata_45_texs_tex.i8.inc"
};

static_assert(ARRAY_COUNT(anime_mario_titexdata_45_texs_tex) == anime_mario_titexdata_45_texs_tex_width * anime_mario_titexdata_45_texs_tex_height, "The dimensions of `anime_mario_titexdata_45_texs_tex` does not match the size of the actual texture");

/* titexdata_47 */

#define anime_mario_titexdata_47_texs_tex_width 64
#define anime_mario_titexdata_47_texs_tex_height 64
extern u8 anime_mario_titexdata_47_texs_tex[];

TiTexDataTextures anime_mario_titexdata_47_texs = {
    NULL,
    anime_mario_titexdata_47_texs_tex,
};

u16 anime_mario_titexdata_47_info[] = {
    anime_mario_titexdata_47_texs_tex_width, anime_mario_titexdata_47_texs_tex_height, TITEX_FORMAT_8, TITEX_FLAGS_BLOCK,
};

u8 anime_mario_titexdata_47_texs_tex[] ALIGNED(8) = {
#include "assets/anime/anime_mario/anime_mario_titexdata_47_texs_tex.i8.inc"
};

static_assert(ARRAY_COUNT(anime_mario_titexdata_47_texs_tex) == anime_mario_titexdata_47_texs_tex_width * anime_mario_titexdata_47_texs_tex_height, "The dimensions of `anime_mario_titexdata_47_texs_tex` does not match the size of the actual texture");

/* titexdata_48 */

#define anime_mario_titexdata_48_texs_tex_width 64
#define anime_mario_titexdata_48_texs_tex_height 64
extern u8 anime_mario_titexdata_48_texs_tex[];

TiTexDataTextures anime_mario_titexdata_48_texs = {
    NULL,
    anime_mario_titexdata_48_texs_tex,
};

u16 anime_mario_titexdata_48_info[] = {
    anime_mario_titexdata_48_texs_tex_width, anime_mario_titexdata_48_texs_tex_height, TITEX_FORMAT_8, TITEX_FLAGS_BLOCK,
};

u8 anime_mario_titexdata_48_texs_tex[] ALIGNED(8) = {
#include "assets/anime/anime_mario/anime_mario_titexdata_48_texs_tex.i8.inc"
};

static_assert(ARRAY_COUNT(anime_mario_titexdata_48_texs_tex) == anime_mario_titexdata_48_texs_tex_width * anime_mario_titexdata_48_texs_tex_height, "The dimensions of `anime_mario_titexdata_48_texs_tex` does not match the size of the actual texture");

/* titexdata_51 */

#define anime_mario_titexdata_51_texs_tex_width 64
#define anime_mario_titexdata_51_texs_tex_height 64
extern u8 anime_mario_titexdata_51_texs_tex[];

TiTexDataTextures anime_mario_titexdata_51_texs = {
    NULL,
    anime_mario_titexdata_51_texs_tex,
};

u16 anime_mario_titexdata_51_info[] = {
    anime_mario_titexdata_51_texs_tex_width, anime_mario_titexdata_51_texs_tex_height, TITEX_FORMAT_8, TITEX_FLAGS_BLOCK,
};

u8 anime_mario_titexdata_51_texs_tex[] ALIGNED(8) = {
#include "assets/anime/anime_mario/anime_mario_titexdata_51_texs_tex.i8.inc"
};

static_assert(ARRAY_COUNT(anime_mario_titexdata_51_texs_tex) == anime_mario_titexdata_51_texs_tex_width * anime_mario_titexdata_51_texs_tex_height, "The dimensions of `anime_mario_titexdata_51_texs_tex` does not match the size of the actual texture");

/* titexdata_52 */

#define anime_mario_titexdata_52_texs_tex_width 64
#define anime_mario_titexdata_52_texs_tex_height 64
extern u8 anime_mario_titexdata_52_texs_tex[];

TiTexDataTextures anime_mario_titexdata_52_texs = {
    NULL,
    anime_mario_titexdata_52_texs_tex,
};

u16 anime_mario_titexdata_52_info[] = {
    anime_mario_titexdata_52_texs_tex_width, anime_mario_titexdata_52_texs_tex_height, TITEX_FORMAT_8, TITEX_FLAGS_BLOCK,
};

u8 anime_mario_titexdata_52_texs_tex[] ALIGNED(8) = {
#include "assets/anime/anime_mario/anime_mario_titexdata_52_texs_tex.i8.inc"
};

static_assert(ARRAY_COUNT(anime_mario_titexdata_52_texs_tex) == anime_mario_titexdata_52_texs_tex_width * anime_mario_titexdata_52_texs_tex_height, "The dimensions of `anime_mario_titexdata_52_texs_tex` does not match the size of the actual texture");

TiTexData anime_mario_titexdata[] = {
    { &anime_mario_titexdata_00_texs, anime_mario_titexdata_00_info },
    { &anime_mario_titexdata_01_texs, anime_mario_titexdata_01_info },
    { &anime_mario_titexdata_02_texs, anime_mario_titexdata_02_info },
    { &anime_mario_titexdata_03_texs, anime_mario_titexdata_03_info },
    { &anime_mario_titexdata_04_texs, anime_mario_titexdata_04_info },
    { &anime_mario_titexdata_05_texs, anime_mario_titexdata_05_info },
    { NULL, NULL },
    { NULL, NULL },
    { NULL, NULL },
    { NULL, NULL },
    { NULL, NULL },
    { &anime_mario_titexdata_11_texs, anime_mario_titexdata_11_info },
    { &anime_mario_titexdata_12_texs, anime_mario_titexdata_12_info },
    { &anime_mario_titexdata_13_texs, anime_mario_titexdata_13_info },
    { &anime_mario_titexdata_14_texs, anime_mario_titexdata_14_info },
    { &anime_mario_titexdata_15_texs, anime_mario_titexdata_15_info },
    { &anime_mario_titexdata_16_texs, anime_mario_titexdata_16_info },
    { &anime_mario_titexdata_17_texs, anime_mario_titexdata_17_info },
    { &anime_mario_titexdata_18_texs, anime_mario_titexdata_18_info },
    { &anime_mario_titexdata_19_texs, anime_mario_titexdata_19_info },
    { &anime_mario_titexdata_20_texs, anime_mario_titexdata_20_info },
    { &anime_mario_titexdata_21_texs, anime_mario_titexdata_21_info },
    { &anime_mario_titexdata_22_texs, anime_mario_titexdata_22_info },
    { &anime_mario_titexdata_23_texs, anime_mario_titexdata_23_info },
    { &anime_mario_titexdata_24_texs, anime_mario_titexdata_24_info },
    { &anime_mario_titexdata_25_texs, anime_mario_titexdata_25_info },
    { &anime_mario_titexdata_26_texs, anime_mario_titexdata_26_info },
    { &anime_mario_titexdata_27_texs, anime_mario_titexdata_27_info },
    { &anime_mario_titexdata_28_texs, anime_mario_titexdata_28_info },
    { &anime_mario_titexdata_29_texs, anime_mario_titexdata_29_info },
    { &anime_mario_titexdata_30_texs, anime_mario_titexdata_30_info },
    { &anime_mario_titexdata_31_texs, anime_mario_titexdata_31_info },
    { &anime_mario_titexdata_32_texs, anime_mario_titexdata_32_info },
    { &anime_mario_titexdata_33_texs, anime_mario_titexdata_33_info },
    { &anime_mario_titexdata_34_texs, anime_mario_titexdata_34_info },
    { &anime_mario_titexdata_35_texs, anime_mario_titexdata_35_info },
    { &anime_mario_titexdata_36_texs, anime_mario_titexdata_36_info },
    { &anime_mario_titexdata_37_texs, anime_mario_titexdata_37_info },
    { &anime_mario_titexdata_38_texs, anime_mario_titexdata_38_info },
    { &anime_mario_titexdata_39_texs, anime_mario_titexdata_39_info },
    { &anime_mario_titexdata_40_texs, anime_mario_titexdata_40_info },
    { &anime_mario_titexdata_41_texs, anime_mario_titexdata_41_info },
    { &anime_mario_titexdata_42_texs, anime_mario_titexdata_42_info },
    { &anime_mario_titexdata_43_texs, anime_mario_titexdata_43_info },
    { &anime_mario_titexdata_44_texs, anime_mario_titexdata_44_info },
    { &anime_mario_titexdata_45_texs, anime_mario_titexdata_45_info },
    { NULL, NULL },
    { &anime_mario_titexdata_47_texs, anime_mario_titexdata_47_info },
    { &anime_mario_titexdata_48_texs, anime_mario_titexdata_48_info },
    { NULL, NULL },
    { NULL, NULL },
    { &anime_mario_titexdata_51_texs, anime_mario_titexdata_51_info },
    { &anime_mario_titexdata_52_texs, anime_mario_titexdata_52_info },
};

s32 anime_mario_titexdata_len = ARRAY_COUNT(anime_mario_titexdata);

u8 anime_mario_metadata_00[] = {
    ANIME_METADATA_CMD_F0(0xFF), 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x02, 0x02, 0x03, 0x03, 0x04, 0x04, 0x05, 0x05, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x05, 0x05, 0x04, 0x04, 0x03, 0x03, 0x02, 0x02, ANIME_METADATA_CMD_F1(0x64), 0x00, 0x00, 
};

u8 anime_mario_metadata_01[] = {
    0x31, 0x35, 0x35, 0x35, 0x35, 0x34, 0x34, 0x34, 0x31, 0x31, 0x31, ANIME_METADATA_CMD_F2(0x00), 0x00, 0x00, 0x00, 
};

u8 anime_mario_metadata_02[] = {
    ANIME_METADATA_CMD_F0(0xFF), 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x02, 0x02, 0x03, 0x03, 0x04, 0x04, 0x05, 0x05, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x05, 0x05, 0x04, 0x04, 0x03, 0x03, 0x02, 0x02, ANIME_METADATA_CMD_F1(0x64), 0x00, 0x00, 
};

u8 anime_mario_metadata_03[] = {
    ANIME_METADATA_CMD_F0(0xFF), 0x0C, 0x0C, 0x0D, 0x0D, 0x0E, 0x0E, 0x0F, 0x0F, 0x10, 0x10, 0x11, 0x11, 0x12, 0x12, 0x12, 0x13, 0x13, 0x13, 0x14, 0x14, 0x14, 0x14, 0x15, 0x15, 0x15, 0x15, 0x16, 0x16, 0x17, 0x17, ANIME_METADATA_CMD_F0(0x0A), 0x18, 0x18, 0x18, 0x18, ANIME_METADATA_CMD_F1(0x64), ANIME_METADATA_CMD_F1(0x64), 0x00, 0x00, 
};

u8 anime_mario_metadata_04[] = {
    0x03, 0x03, 0x03, 0x19, 0x19, 0x19, 0x1A, 0x1A, 0x1A, 0x1B, 0x1B, 0x1B, 0x1C, 0x1C, 0x1C, 0x1D, 0x1D, 0x1D, 0x1E, 0x1E, 0x1E, 0x1F, 0x1F, 0x1F, 0x20, 0x20, 0x20, 0x21, 0x21, 0x21, 0x22, 0x22, 0x22, 0x23, 0x23, 0x23, 0x24, 0x24, 0x24, 0x25, 0x25, 0x25, 0x26, 0x26, 0x26, 0x27, 0x27, 0x27, 0x28, 0x28, 0x28, 0x29, 0x29, 0x29, 0x29, 0x29, 0x29, 0x29, 0x29, 0x29, 0x2A, 0x2A, 0x2A, 0x2B, 0x2B, 0x2B, ANIME_METADATA_CMD_F0(0xFF), 0x2C, 0x2C, 0x2C, 0x2D, 0x2D, ANIME_METADATA_CMD_F0(0x0C), 0x2E, 0x2E, 0x2E, 0x2E, 0x2E, ANIME_METADATA_CMD_F1(0x64), 0x2D, 0x2D, 0x2D, ANIME_METADATA_CMD_F1(0x64), 0x00, };

u8 *anime_mario_metadata[] = {
    anime_mario_metadata_00,
    anime_mario_metadata_01,
    anime_mario_metadata_02,
    anime_mario_metadata_03,
    anime_mario_metadata_04,
};

s32 anime_mario_metadata_len = ARRAY_COUNT(anime_mario_metadata);

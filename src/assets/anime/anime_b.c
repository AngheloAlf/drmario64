#include "tex_func.h"
#include "char_anime.h"

#include "libc/assert.h"
#include "macros_defines.h"
#include "alignment.h"

extern TiTexData anime_b_titexdata[];
extern s32 anime_b_titexdata_len;
extern u8 *anime_b_metadata[];
extern s32 anime_b_metadata_len;

AnimeHeader anime_b_header = {
    anime_b_titexdata,
    &anime_b_titexdata_len,
    anime_b_metadata,
    &anime_b_metadata_len,
};

/* titexdata_00 */

#define anime_b_titexdata_00_texs_tex_width 40
#define anime_b_titexdata_00_texs_tex_height 48
extern u8 anime_b_titexdata_00_texs_tex[];
extern u16 anime_b_titexdata_00_texs_tlut[];

TexturePtr anime_b_titexdata_00_texs[2] = {
    anime_b_titexdata_00_texs_tlut,
    anime_b_titexdata_00_texs_tex,
};

u16 anime_b_titexdata_00_info[] = {
    anime_b_titexdata_00_texs_tex_width,
    anime_b_titexdata_00_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_TILE,
};

u16 anime_b_titexdata_00_texs_tlut[] ALIGNED(8) = {
#include "assets/anime/anime_b/anime_b_titexdata_00_texs_tex.palette.inc"
};

u8 anime_b_titexdata_00_texs_tex[] ALIGNED(8) = {
#include "assets/anime/anime_b/anime_b_titexdata_00_texs_tex.ci4.inc"
};

static_assert(ARRAY_COUNT(anime_b_titexdata_00_texs_tlut) == 4 * 4,
              "The dimensions of `anime_b_titexdata_00_texs_tlut` does not match the size of the actual tlut");
static_assert(ARRAY_COUNT(anime_b_titexdata_00_texs_tex) ==
                  anime_b_titexdata_00_texs_tex_width * anime_b_titexdata_00_texs_tex_height / 2,
              "The dimensions of `anime_b_titexdata_00_texs_tex` does not match the size of the actual texture");

/* titexdata_01 */

#define anime_b_titexdata_01_texs_tex_width 40
#define anime_b_titexdata_01_texs_tex_height 48
extern u8 anime_b_titexdata_01_texs_tex[];

TexturePtr anime_b_titexdata_01_texs[2] = {
    NULL,
    anime_b_titexdata_01_texs_tex,
};

u16 anime_b_titexdata_01_info[] = {
    anime_b_titexdata_01_texs_tex_width,
    anime_b_titexdata_01_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_TILE,
};

u8 anime_b_titexdata_01_texs_tex[] ALIGNED(8) = {
#include "assets/anime/anime_b/anime_b_titexdata_01_texs_tex.i4.inc"
};

static_assert(ARRAY_COUNT(anime_b_titexdata_01_texs_tex) ==
                  anime_b_titexdata_01_texs_tex_width * anime_b_titexdata_01_texs_tex_height / 2,
              "The dimensions of `anime_b_titexdata_01_texs_tex` does not match the size of the actual texture");

/* titexdata_02 */

#define anime_b_titexdata_02_texs_tex_width 40
#define anime_b_titexdata_02_texs_tex_height 48
extern u8 anime_b_titexdata_02_texs_tex[];

TexturePtr anime_b_titexdata_02_texs[2] = {
    NULL,
    anime_b_titexdata_02_texs_tex,
};

u16 anime_b_titexdata_02_info[] = {
    anime_b_titexdata_02_texs_tex_width,
    anime_b_titexdata_02_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_TILE,
};

u8 anime_b_titexdata_02_texs_tex[] ALIGNED(8) = {
#include "assets/anime/anime_b/anime_b_titexdata_02_texs_tex.i4.inc"
};

static_assert(ARRAY_COUNT(anime_b_titexdata_02_texs_tex) ==
                  anime_b_titexdata_02_texs_tex_width * anime_b_titexdata_02_texs_tex_height / 2,
              "The dimensions of `anime_b_titexdata_02_texs_tex` does not match the size of the actual texture");

/* titexdata_03 */

#define anime_b_titexdata_03_texs_tex_width 40
#define anime_b_titexdata_03_texs_tex_height 48
extern u8 anime_b_titexdata_03_texs_tex[];

TexturePtr anime_b_titexdata_03_texs[2] = {
    NULL,
    anime_b_titexdata_03_texs_tex,
};

u16 anime_b_titexdata_03_info[] = {
    anime_b_titexdata_03_texs_tex_width,
    anime_b_titexdata_03_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_TILE,
};

u8 anime_b_titexdata_03_texs_tex[] ALIGNED(8) = {
#include "assets/anime/anime_b/anime_b_titexdata_03_texs_tex.i4.inc"
};

static_assert(ARRAY_COUNT(anime_b_titexdata_03_texs_tex) ==
                  anime_b_titexdata_03_texs_tex_width * anime_b_titexdata_03_texs_tex_height / 2,
              "The dimensions of `anime_b_titexdata_03_texs_tex` does not match the size of the actual texture");

/* titexdata_04 */

#define anime_b_titexdata_04_texs_tex_width 40
#define anime_b_titexdata_04_texs_tex_height 48
extern u8 anime_b_titexdata_04_texs_tex[];

TexturePtr anime_b_titexdata_04_texs[2] = {
    NULL,
    anime_b_titexdata_04_texs_tex,
};

u16 anime_b_titexdata_04_info[] = {
    anime_b_titexdata_04_texs_tex_width,
    anime_b_titexdata_04_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_TILE,
};

u8 anime_b_titexdata_04_texs_tex[] ALIGNED(8) = {
#include "assets/anime/anime_b/anime_b_titexdata_04_texs_tex.i4.inc"
};

static_assert(ARRAY_COUNT(anime_b_titexdata_04_texs_tex) ==
                  anime_b_titexdata_04_texs_tex_width * anime_b_titexdata_04_texs_tex_height / 2,
              "The dimensions of `anime_b_titexdata_04_texs_tex` does not match the size of the actual texture");

/* titexdata_05 */

#define anime_b_titexdata_05_texs_tex_width 40
#define anime_b_titexdata_05_texs_tex_height 48
extern u8 anime_b_titexdata_05_texs_tex[];

TexturePtr anime_b_titexdata_05_texs[2] = {
    NULL,
    anime_b_titexdata_05_texs_tex,
};

u16 anime_b_titexdata_05_info[] = {
    anime_b_titexdata_05_texs_tex_width,
    anime_b_titexdata_05_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_TILE,
};

u8 anime_b_titexdata_05_texs_tex[] ALIGNED(8) = {
#include "assets/anime/anime_b/anime_b_titexdata_05_texs_tex.i4.inc"
};

static_assert(ARRAY_COUNT(anime_b_titexdata_05_texs_tex) ==
                  anime_b_titexdata_05_texs_tex_width * anime_b_titexdata_05_texs_tex_height / 2,
              "The dimensions of `anime_b_titexdata_05_texs_tex` does not match the size of the actual texture");

/* titexdata_06 */

#define anime_b_titexdata_06_texs_tex_width 40
#define anime_b_titexdata_06_texs_tex_height 48
extern u8 anime_b_titexdata_06_texs_tex[];

TexturePtr anime_b_titexdata_06_texs[2] = {
    NULL,
    anime_b_titexdata_06_texs_tex,
};

u16 anime_b_titexdata_06_info[] = {
    anime_b_titexdata_06_texs_tex_width,
    anime_b_titexdata_06_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_TILE,
};

u8 anime_b_titexdata_06_texs_tex[] ALIGNED(8) = {
#include "assets/anime/anime_b/anime_b_titexdata_06_texs_tex.i4.inc"
};

static_assert(ARRAY_COUNT(anime_b_titexdata_06_texs_tex) ==
                  anime_b_titexdata_06_texs_tex_width * anime_b_titexdata_06_texs_tex_height / 2,
              "The dimensions of `anime_b_titexdata_06_texs_tex` does not match the size of the actual texture");

/* titexdata_07 */

#define anime_b_titexdata_07_texs_tex_width 40
#define anime_b_titexdata_07_texs_tex_height 48
extern u8 anime_b_titexdata_07_texs_tex[];

TexturePtr anime_b_titexdata_07_texs[2] = {
    NULL,
    anime_b_titexdata_07_texs_tex,
};

u16 anime_b_titexdata_07_info[] = {
    anime_b_titexdata_07_texs_tex_width,
    anime_b_titexdata_07_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_TILE,
};

u8 anime_b_titexdata_07_texs_tex[] ALIGNED(8) = {
#include "assets/anime/anime_b/anime_b_titexdata_07_texs_tex.i4.inc"
};

static_assert(ARRAY_COUNT(anime_b_titexdata_07_texs_tex) ==
                  anime_b_titexdata_07_texs_tex_width * anime_b_titexdata_07_texs_tex_height / 2,
              "The dimensions of `anime_b_titexdata_07_texs_tex` does not match the size of the actual texture");

/* titexdata_08 */

#define anime_b_titexdata_08_texs_tex_width 40
#define anime_b_titexdata_08_texs_tex_height 48
extern u8 anime_b_titexdata_08_texs_tex[];

TexturePtr anime_b_titexdata_08_texs[2] = {
    NULL,
    anime_b_titexdata_08_texs_tex,
};

u16 anime_b_titexdata_08_info[] = {
    anime_b_titexdata_08_texs_tex_width,
    anime_b_titexdata_08_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_TILE,
};

u8 anime_b_titexdata_08_texs_tex[] ALIGNED(8) = {
#include "assets/anime/anime_b/anime_b_titexdata_08_texs_tex.i4.inc"
};

static_assert(ARRAY_COUNT(anime_b_titexdata_08_texs_tex) ==
                  anime_b_titexdata_08_texs_tex_width * anime_b_titexdata_08_texs_tex_height / 2,
              "The dimensions of `anime_b_titexdata_08_texs_tex` does not match the size of the actual texture");

/* titexdata_09 */

#define anime_b_titexdata_09_texs_tex_width 40
#define anime_b_titexdata_09_texs_tex_height 48
extern u8 anime_b_titexdata_09_texs_tex[];

TexturePtr anime_b_titexdata_09_texs[2] = {
    NULL,
    anime_b_titexdata_09_texs_tex,
};

u16 anime_b_titexdata_09_info[] = {
    anime_b_titexdata_09_texs_tex_width,
    anime_b_titexdata_09_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_TILE,
};

u8 anime_b_titexdata_09_texs_tex[] ALIGNED(8) = {
#include "assets/anime/anime_b/anime_b_titexdata_09_texs_tex.i4.inc"
};

static_assert(ARRAY_COUNT(anime_b_titexdata_09_texs_tex) ==
                  anime_b_titexdata_09_texs_tex_width * anime_b_titexdata_09_texs_tex_height / 2,
              "The dimensions of `anime_b_titexdata_09_texs_tex` does not match the size of the actual texture");

/* titexdata_10 */

#define anime_b_titexdata_10_texs_tex_width 40
#define anime_b_titexdata_10_texs_tex_height 48
extern u8 anime_b_titexdata_10_texs_tex[];

TexturePtr anime_b_titexdata_10_texs[2] = {
    NULL,
    anime_b_titexdata_10_texs_tex,
};

u16 anime_b_titexdata_10_info[] = {
    anime_b_titexdata_10_texs_tex_width,
    anime_b_titexdata_10_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_TILE,
};

u8 anime_b_titexdata_10_texs_tex[] ALIGNED(8) = {
#include "assets/anime/anime_b/anime_b_titexdata_10_texs_tex.i4.inc"
};

static_assert(ARRAY_COUNT(anime_b_titexdata_10_texs_tex) ==
                  anime_b_titexdata_10_texs_tex_width * anime_b_titexdata_10_texs_tex_height / 2,
              "The dimensions of `anime_b_titexdata_10_texs_tex` does not match the size of the actual texture");

/* titexdata_11 */

#define anime_b_titexdata_11_texs_tex_width 40
#define anime_b_titexdata_11_texs_tex_height 48
extern u8 anime_b_titexdata_11_texs_tex[];

TexturePtr anime_b_titexdata_11_texs[2] = {
    NULL,
    anime_b_titexdata_11_texs_tex,
};

u16 anime_b_titexdata_11_info[] = {
    anime_b_titexdata_11_texs_tex_width,
    anime_b_titexdata_11_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_TILE,
};

u8 anime_b_titexdata_11_texs_tex[] ALIGNED(8) = {
#include "assets/anime/anime_b/anime_b_titexdata_11_texs_tex.i4.inc"
};

static_assert(ARRAY_COUNT(anime_b_titexdata_11_texs_tex) ==
                  anime_b_titexdata_11_texs_tex_width * anime_b_titexdata_11_texs_tex_height / 2,
              "The dimensions of `anime_b_titexdata_11_texs_tex` does not match the size of the actual texture");

/* titexdata_12 */

#define anime_b_titexdata_12_texs_tex_width 40
#define anime_b_titexdata_12_texs_tex_height 48
extern u8 anime_b_titexdata_12_texs_tex[];

TexturePtr anime_b_titexdata_12_texs[2] = {
    NULL,
    anime_b_titexdata_12_texs_tex,
};

u16 anime_b_titexdata_12_info[] = {
    anime_b_titexdata_12_texs_tex_width,
    anime_b_titexdata_12_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_TILE,
};

u8 anime_b_titexdata_12_texs_tex[] ALIGNED(8) = {
#include "assets/anime/anime_b/anime_b_titexdata_12_texs_tex.i4.inc"
};

static_assert(ARRAY_COUNT(anime_b_titexdata_12_texs_tex) ==
                  anime_b_titexdata_12_texs_tex_width * anime_b_titexdata_12_texs_tex_height / 2,
              "The dimensions of `anime_b_titexdata_12_texs_tex` does not match the size of the actual texture");

/* titexdata_13 */

#define anime_b_titexdata_13_texs_tex_width 40
#define anime_b_titexdata_13_texs_tex_height 48
extern u8 anime_b_titexdata_13_texs_tex[];

TexturePtr anime_b_titexdata_13_texs[2] = {
    NULL,
    anime_b_titexdata_13_texs_tex,
};

u16 anime_b_titexdata_13_info[] = {
    anime_b_titexdata_13_texs_tex_width,
    anime_b_titexdata_13_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_TILE,
};

u8 anime_b_titexdata_13_texs_tex[] ALIGNED(8) = {
#include "assets/anime/anime_b/anime_b_titexdata_13_texs_tex.i4.inc"
};

static_assert(ARRAY_COUNT(anime_b_titexdata_13_texs_tex) ==
                  anime_b_titexdata_13_texs_tex_width * anime_b_titexdata_13_texs_tex_height / 2,
              "The dimensions of `anime_b_titexdata_13_texs_tex` does not match the size of the actual texture");

/* titexdata_14 */

#define anime_b_titexdata_14_texs_tex_width 40
#define anime_b_titexdata_14_texs_tex_height 48
extern u8 anime_b_titexdata_14_texs_tex[];

TexturePtr anime_b_titexdata_14_texs[2] = {
    NULL,
    anime_b_titexdata_14_texs_tex,
};

u16 anime_b_titexdata_14_info[] = {
    anime_b_titexdata_14_texs_tex_width,
    anime_b_titexdata_14_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_TILE,
};

u8 anime_b_titexdata_14_texs_tex[] ALIGNED(8) = {
#include "assets/anime/anime_b/anime_b_titexdata_14_texs_tex.i4.inc"
};

static_assert(ARRAY_COUNT(anime_b_titexdata_14_texs_tex) ==
                  anime_b_titexdata_14_texs_tex_width * anime_b_titexdata_14_texs_tex_height / 2,
              "The dimensions of `anime_b_titexdata_14_texs_tex` does not match the size of the actual texture");

/* titexdata_15 */

#define anime_b_titexdata_15_texs_tex_width 40
#define anime_b_titexdata_15_texs_tex_height 48
extern u8 anime_b_titexdata_15_texs_tex[];

TexturePtr anime_b_titexdata_15_texs[2] = {
    NULL,
    anime_b_titexdata_15_texs_tex,
};

u16 anime_b_titexdata_15_info[] = {
    anime_b_titexdata_15_texs_tex_width,
    anime_b_titexdata_15_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_TILE,
};

u8 anime_b_titexdata_15_texs_tex[] ALIGNED(8) = {
#include "assets/anime/anime_b/anime_b_titexdata_15_texs_tex.i4.inc"
};

static_assert(ARRAY_COUNT(anime_b_titexdata_15_texs_tex) ==
                  anime_b_titexdata_15_texs_tex_width * anime_b_titexdata_15_texs_tex_height / 2,
              "The dimensions of `anime_b_titexdata_15_texs_tex` does not match the size of the actual texture");

/* titexdata_16 */

#define anime_b_titexdata_16_texs_tex_width 40
#define anime_b_titexdata_16_texs_tex_height 48
extern u8 anime_b_titexdata_16_texs_tex[];

TexturePtr anime_b_titexdata_16_texs[2] = {
    NULL,
    anime_b_titexdata_16_texs_tex,
};

u16 anime_b_titexdata_16_info[] = {
    anime_b_titexdata_16_texs_tex_width,
    anime_b_titexdata_16_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_TILE,
};

u8 anime_b_titexdata_16_texs_tex[] ALIGNED(8) = {
#include "assets/anime/anime_b/anime_b_titexdata_16_texs_tex.i4.inc"
};

static_assert(ARRAY_COUNT(anime_b_titexdata_16_texs_tex) ==
                  anime_b_titexdata_16_texs_tex_width * anime_b_titexdata_16_texs_tex_height / 2,
              "The dimensions of `anime_b_titexdata_16_texs_tex` does not match the size of the actual texture");

/* titexdata_17 */

#define anime_b_titexdata_17_texs_tex_width 40
#define anime_b_titexdata_17_texs_tex_height 48
extern u8 anime_b_titexdata_17_texs_tex[];

TexturePtr anime_b_titexdata_17_texs[2] = {
    NULL,
    anime_b_titexdata_17_texs_tex,
};

u16 anime_b_titexdata_17_info[] = {
    anime_b_titexdata_17_texs_tex_width,
    anime_b_titexdata_17_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_TILE,
};

u8 anime_b_titexdata_17_texs_tex[] ALIGNED(8) = {
#include "assets/anime/anime_b/anime_b_titexdata_17_texs_tex.i4.inc"
};

static_assert(ARRAY_COUNT(anime_b_titexdata_17_texs_tex) ==
                  anime_b_titexdata_17_texs_tex_width * anime_b_titexdata_17_texs_tex_height / 2,
              "The dimensions of `anime_b_titexdata_17_texs_tex` does not match the size of the actual texture");

/* titexdata_18 */

#define anime_b_titexdata_18_texs_tex_width 40
#define anime_b_titexdata_18_texs_tex_height 48
extern u8 anime_b_titexdata_18_texs_tex[];

TexturePtr anime_b_titexdata_18_texs[2] = {
    NULL,
    anime_b_titexdata_18_texs_tex,
};

u16 anime_b_titexdata_18_info[] = {
    anime_b_titexdata_18_texs_tex_width,
    anime_b_titexdata_18_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_TILE,
};

u8 anime_b_titexdata_18_texs_tex[] ALIGNED(8) = {
#include "assets/anime/anime_b/anime_b_titexdata_18_texs_tex.i4.inc"
};

static_assert(ARRAY_COUNT(anime_b_titexdata_18_texs_tex) ==
                  anime_b_titexdata_18_texs_tex_width * anime_b_titexdata_18_texs_tex_height / 2,
              "The dimensions of `anime_b_titexdata_18_texs_tex` does not match the size of the actual texture");

/* titexdata_19 */

#define anime_b_titexdata_19_texs_tex_width 40
#define anime_b_titexdata_19_texs_tex_height 48
extern u8 anime_b_titexdata_19_texs_tex[];

TexturePtr anime_b_titexdata_19_texs[2] = {
    NULL,
    anime_b_titexdata_19_texs_tex,
};

u16 anime_b_titexdata_19_info[] = {
    anime_b_titexdata_19_texs_tex_width,
    anime_b_titexdata_19_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_TILE,
};

u8 anime_b_titexdata_19_texs_tex[] ALIGNED(8) = {
#include "assets/anime/anime_b/anime_b_titexdata_19_texs_tex.i4.inc"
};

static_assert(ARRAY_COUNT(anime_b_titexdata_19_texs_tex) ==
                  anime_b_titexdata_19_texs_tex_width * anime_b_titexdata_19_texs_tex_height / 2,
              "The dimensions of `anime_b_titexdata_19_texs_tex` does not match the size of the actual texture");

/* titexdata_20 */

#define anime_b_titexdata_20_texs_tex_width 40
#define anime_b_titexdata_20_texs_tex_height 48
extern u8 anime_b_titexdata_20_texs_tex[];

TexturePtr anime_b_titexdata_20_texs[2] = {
    NULL,
    anime_b_titexdata_20_texs_tex,
};

u16 anime_b_titexdata_20_info[] = {
    anime_b_titexdata_20_texs_tex_width,
    anime_b_titexdata_20_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_TILE,
};

u8 anime_b_titexdata_20_texs_tex[] ALIGNED(8) = {
#include "assets/anime/anime_b/anime_b_titexdata_20_texs_tex.i4.inc"
};

static_assert(ARRAY_COUNT(anime_b_titexdata_20_texs_tex) ==
                  anime_b_titexdata_20_texs_tex_width * anime_b_titexdata_20_texs_tex_height / 2,
              "The dimensions of `anime_b_titexdata_20_texs_tex` does not match the size of the actual texture");

/* titexdata_21 */

#define anime_b_titexdata_21_texs_tex_width 40
#define anime_b_titexdata_21_texs_tex_height 48
extern u8 anime_b_titexdata_21_texs_tex[];

TexturePtr anime_b_titexdata_21_texs[2] = {
    NULL,
    anime_b_titexdata_21_texs_tex,
};

u16 anime_b_titexdata_21_info[] = {
    anime_b_titexdata_21_texs_tex_width,
    anime_b_titexdata_21_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_TILE,
};

u8 anime_b_titexdata_21_texs_tex[] ALIGNED(8) = {
#include "assets/anime/anime_b/anime_b_titexdata_21_texs_tex.i4.inc"
};

static_assert(ARRAY_COUNT(anime_b_titexdata_21_texs_tex) ==
                  anime_b_titexdata_21_texs_tex_width * anime_b_titexdata_21_texs_tex_height / 2,
              "The dimensions of `anime_b_titexdata_21_texs_tex` does not match the size of the actual texture");

/* titexdata_22 */

#define anime_b_titexdata_22_texs_tex_width 40
#define anime_b_titexdata_22_texs_tex_height 48
extern u8 anime_b_titexdata_22_texs_tex[];

TexturePtr anime_b_titexdata_22_texs[2] = {
    NULL,
    anime_b_titexdata_22_texs_tex,
};

u16 anime_b_titexdata_22_info[] = {
    anime_b_titexdata_22_texs_tex_width,
    anime_b_titexdata_22_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_TILE,
};

u8 anime_b_titexdata_22_texs_tex[] ALIGNED(8) = {
#include "assets/anime/anime_b/anime_b_titexdata_22_texs_tex.i4.inc"
};

static_assert(ARRAY_COUNT(anime_b_titexdata_22_texs_tex) ==
                  anime_b_titexdata_22_texs_tex_width * anime_b_titexdata_22_texs_tex_height / 2,
              "The dimensions of `anime_b_titexdata_22_texs_tex` does not match the size of the actual texture");

/* titexdata_23 */

#define anime_b_titexdata_23_texs_tex_width 40
#define anime_b_titexdata_23_texs_tex_height 48
extern u8 anime_b_titexdata_23_texs_tex[];

TexturePtr anime_b_titexdata_23_texs[2] = {
    NULL,
    anime_b_titexdata_23_texs_tex,
};

u16 anime_b_titexdata_23_info[] = {
    anime_b_titexdata_23_texs_tex_width,
    anime_b_titexdata_23_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_TILE,
};

u8 anime_b_titexdata_23_texs_tex[] ALIGNED(8) = {
#include "assets/anime/anime_b/anime_b_titexdata_23_texs_tex.i4.inc"
};

static_assert(ARRAY_COUNT(anime_b_titexdata_23_texs_tex) ==
                  anime_b_titexdata_23_texs_tex_width * anime_b_titexdata_23_texs_tex_height / 2,
              "The dimensions of `anime_b_titexdata_23_texs_tex` does not match the size of the actual texture");

/* titexdata_24 */

#define anime_b_titexdata_24_texs_tex_width 40
#define anime_b_titexdata_24_texs_tex_height 48
extern u8 anime_b_titexdata_24_texs_tex[];

TexturePtr anime_b_titexdata_24_texs[2] = {
    NULL,
    anime_b_titexdata_24_texs_tex,
};

u16 anime_b_titexdata_24_info[] = {
    anime_b_titexdata_24_texs_tex_width,
    anime_b_titexdata_24_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_TILE,
};

u8 anime_b_titexdata_24_texs_tex[] ALIGNED(8) = {
#include "assets/anime/anime_b/anime_b_titexdata_24_texs_tex.i4.inc"
};

static_assert(ARRAY_COUNT(anime_b_titexdata_24_texs_tex) ==
                  anime_b_titexdata_24_texs_tex_width * anime_b_titexdata_24_texs_tex_height / 2,
              "The dimensions of `anime_b_titexdata_24_texs_tex` does not match the size of the actual texture");

TiTexData anime_b_titexdata[] = {
    { anime_b_titexdata_00_texs, anime_b_titexdata_00_info }, { anime_b_titexdata_01_texs, anime_b_titexdata_01_info },
    { anime_b_titexdata_02_texs, anime_b_titexdata_02_info }, { anime_b_titexdata_03_texs, anime_b_titexdata_03_info },
    { anime_b_titexdata_04_texs, anime_b_titexdata_04_info }, { anime_b_titexdata_05_texs, anime_b_titexdata_05_info },
    { anime_b_titexdata_06_texs, anime_b_titexdata_06_info }, { anime_b_titexdata_07_texs, anime_b_titexdata_07_info },
    { anime_b_titexdata_08_texs, anime_b_titexdata_08_info }, { anime_b_titexdata_09_texs, anime_b_titexdata_09_info },
    { anime_b_titexdata_10_texs, anime_b_titexdata_10_info }, { anime_b_titexdata_11_texs, anime_b_titexdata_11_info },
    { anime_b_titexdata_12_texs, anime_b_titexdata_12_info }, { anime_b_titexdata_13_texs, anime_b_titexdata_13_info },
    { anime_b_titexdata_14_texs, anime_b_titexdata_14_info }, { anime_b_titexdata_15_texs, anime_b_titexdata_15_info },
    { anime_b_titexdata_16_texs, anime_b_titexdata_16_info }, { anime_b_titexdata_17_texs, anime_b_titexdata_17_info },
    { anime_b_titexdata_18_texs, anime_b_titexdata_18_info }, { anime_b_titexdata_19_texs, anime_b_titexdata_19_info },
    { anime_b_titexdata_20_texs, anime_b_titexdata_20_info }, { anime_b_titexdata_21_texs, anime_b_titexdata_21_info },
    { anime_b_titexdata_22_texs, anime_b_titexdata_22_info }, { anime_b_titexdata_23_texs, anime_b_titexdata_23_info },
    { anime_b_titexdata_24_texs, anime_b_titexdata_24_info },
};

s32 anime_b_titexdata_len = ARRAY_COUNT(anime_b_titexdata);

u8 anime_b_metadata_00[] = {
    ANIME_METADATA_CMD_F0(0xFF),
    0x01,
    0x01,
    0x02,
    0x02,
    0x03,
    0x03,
    0x04,
    0x04,
    0x05,
    0x05,
    0x06,
    0x06,
    0x07,
    0x07,
    0x08,
    0x08,
    0x07,
    0x07,
    0x06,
    0x06,
    0x05,
    0x05,
    0x04,
    0x04,
    0x03,
    0x03,
    0x02,
    0x02,
    ANIME_METADATA_CMD_F1(0x64),
};

u8 anime_b_metadata_01[] = {
    0x04,
    0x04,
    0x04,
    0x09,
    0x09,
    0x09,
    0x0A,
    0x0A,
    0x0A,
    0x0B,
    0x0B,
    0x0B,
    0x0B,
    0x0B,
    0x0B,
    0x0C,
    0x0C,
    0x0D,
    0x0D,
    0x0B,
    0x0B,
    0x0C,
    0x0C,
    0x0D,
    0x0D,
    0x0B,
    0x0B,
    0x0C,
    0x0C,
    0x0D,
    0x0D,
    0x0B,
    0x0B,
    0x0B,
    0x0A,
    0x0A,
    0x0A,
    0x09,
    0x09,
    0x09,
    ANIME_METADATA_CMD_F2(ANIMENO_0),
};

u8 anime_b_metadata_02[] = {
    0x04,
    0x04,
    0x04,
    ANIME_METADATA_CMD_F0(0x03),
    0x0E,
    0x0E,
    0x0F,
    0x0F,
    0x10,
    0x10,
    0x11,
    0x11,
    0x12,
    0x12,
    ANIME_METADATA_CMD_F1(0x64),
    ANIME_METADATA_CMD_F2(ANIMENO_0),
};

u8 anime_b_metadata_03[] = {
    0x04, 0x04, 0x04, 0x13, 0x13, 0x13, ANIME_METADATA_CMD_F0(0xFF), 0x14, 0x14, 0x14,
    0x15, 0x15, 0x15, 0x16, 0x16, 0x16, ANIME_METADATA_CMD_F1(0x64),
};

u8 anime_b_metadata_04[] = {
    0x17, 0x17, 0x17,
    0x18, 0x18, 0x18,
    0x18, 0x18, 0x18,
    0x18, 0x18, 0x18,
    0x19, 0x19, ANIME_METADATA_CMD_F0(0xFF),
    0x18, 0x18, 0x18,
    0x18, 0x18, 0x19,
    0x19, 0x18, 0x18,
    0x19, 0x19, ANIME_METADATA_CMD_F1(0x64),
};

u8 *anime_b_metadata[] = {
    anime_b_metadata_00, anime_b_metadata_01, anime_b_metadata_02, anime_b_metadata_03, anime_b_metadata_04,
};

s32 anime_b_metadata_len = ARRAY_COUNT(anime_b_metadata);

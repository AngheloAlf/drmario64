#include "tex_func.h"
#include "char_anime.h"

#include "libc/assert.h"
#include "macros_defines.h"
#include "alignment.h"

extern TiTexData anime_smog_titexdata[];
extern s32 anime_smog_titexdata_len;
extern u8 *anime_smog_metadata[];
extern s32 anime_smog_metadata_len;

AnimeHeader anime_smog_header = {
    anime_smog_titexdata,
    &anime_smog_titexdata_len,
    anime_smog_metadata,
    &anime_smog_metadata_len,
};

/* titexdata_00 */

#define anime_smog_titexdata_00_texs_tex_width 32
#define anime_smog_titexdata_00_texs_tex_height 32
extern u8 anime_smog_titexdata_00_texs_tex[];

TexturePtr anime_smog_titexdata_00_texs[2] = {
    NULL,
    anime_smog_titexdata_00_texs_tex,
};

u16 anime_smog_titexdata_00_info[] = {
    anime_smog_titexdata_00_texs_tex_width,
    anime_smog_titexdata_00_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 anime_smog_titexdata_00_texs_tex[] ALIGNED(8) = {
#include "assets/anime/anime_smog/anime_smog_titexdata_00_texs_tex.i4.inc"
};

static_assert(ARRAY_COUNT(anime_smog_titexdata_00_texs_tex) ==
                  anime_smog_titexdata_00_texs_tex_width * anime_smog_titexdata_00_texs_tex_height / 2,
              "The dimensions of `anime_smog_titexdata_00_texs_tex` does not match the size of the actual texture");

/* titexdata_01 */

#define anime_smog_titexdata_01_texs_tex_width 32
#define anime_smog_titexdata_01_texs_tex_height 32
extern u8 anime_smog_titexdata_01_texs_tex[];

TexturePtr anime_smog_titexdata_01_texs[2] = {
    NULL,
    anime_smog_titexdata_01_texs_tex,
};

u16 anime_smog_titexdata_01_info[] = {
    anime_smog_titexdata_01_texs_tex_width,
    anime_smog_titexdata_01_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 anime_smog_titexdata_01_texs_tex[] ALIGNED(8) = {
#include "assets/anime/anime_smog/anime_smog_titexdata_01_texs_tex.i4.inc"
};

static_assert(ARRAY_COUNT(anime_smog_titexdata_01_texs_tex) ==
                  anime_smog_titexdata_01_texs_tex_width * anime_smog_titexdata_01_texs_tex_height / 2,
              "The dimensions of `anime_smog_titexdata_01_texs_tex` does not match the size of the actual texture");

/* titexdata_02 */

#define anime_smog_titexdata_02_texs_tex_width 32
#define anime_smog_titexdata_02_texs_tex_height 32
extern u8 anime_smog_titexdata_02_texs_tex[];

TexturePtr anime_smog_titexdata_02_texs[2] = {
    NULL,
    anime_smog_titexdata_02_texs_tex,
};

u16 anime_smog_titexdata_02_info[] = {
    anime_smog_titexdata_02_texs_tex_width,
    anime_smog_titexdata_02_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 anime_smog_titexdata_02_texs_tex[] ALIGNED(8) = {
#include "assets/anime/anime_smog/anime_smog_titexdata_02_texs_tex.i4.inc"
};

static_assert(ARRAY_COUNT(anime_smog_titexdata_02_texs_tex) ==
                  anime_smog_titexdata_02_texs_tex_width * anime_smog_titexdata_02_texs_tex_height / 2,
              "The dimensions of `anime_smog_titexdata_02_texs_tex` does not match the size of the actual texture");

/* titexdata_03 */

#define anime_smog_titexdata_03_texs_tex_width 32
#define anime_smog_titexdata_03_texs_tex_height 32
extern u8 anime_smog_titexdata_03_texs_tex[];

TexturePtr anime_smog_titexdata_03_texs[2] = {
    NULL,
    anime_smog_titexdata_03_texs_tex,
};

u16 anime_smog_titexdata_03_info[] = {
    anime_smog_titexdata_03_texs_tex_width,
    anime_smog_titexdata_03_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 anime_smog_titexdata_03_texs_tex[] ALIGNED(8) = {
#include "assets/anime/anime_smog/anime_smog_titexdata_03_texs_tex.i4.inc"
};

static_assert(ARRAY_COUNT(anime_smog_titexdata_03_texs_tex) ==
                  anime_smog_titexdata_03_texs_tex_width * anime_smog_titexdata_03_texs_tex_height / 2,
              "The dimensions of `anime_smog_titexdata_03_texs_tex` does not match the size of the actual texture");

/* titexdata_04 */

#define anime_smog_titexdata_04_texs_tex_width 32
#define anime_smog_titexdata_04_texs_tex_height 32
extern u8 anime_smog_titexdata_04_texs_tex[];

TexturePtr anime_smog_titexdata_04_texs[2] = {
    NULL,
    anime_smog_titexdata_04_texs_tex,
};

u16 anime_smog_titexdata_04_info[] = {
    anime_smog_titexdata_04_texs_tex_width,
    anime_smog_titexdata_04_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 anime_smog_titexdata_04_texs_tex[] ALIGNED(8) = {
#include "assets/anime/anime_smog/anime_smog_titexdata_04_texs_tex.i4.inc"
};

static_assert(ARRAY_COUNT(anime_smog_titexdata_04_texs_tex) ==
                  anime_smog_titexdata_04_texs_tex_width * anime_smog_titexdata_04_texs_tex_height / 2,
              "The dimensions of `anime_smog_titexdata_04_texs_tex` does not match the size of the actual texture");

/* titexdata_05 */

#define anime_smog_titexdata_05_texs_tex_width 32
#define anime_smog_titexdata_05_texs_tex_height 32
extern u8 anime_smog_titexdata_05_texs_tex[];

TexturePtr anime_smog_titexdata_05_texs[2] = {
    NULL,
    anime_smog_titexdata_05_texs_tex,
};

u16 anime_smog_titexdata_05_info[] = {
    anime_smog_titexdata_05_texs_tex_width,
    anime_smog_titexdata_05_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 anime_smog_titexdata_05_texs_tex[] ALIGNED(8) = {
#include "assets/anime/anime_smog/anime_smog_titexdata_05_texs_tex.i4.inc"
};

static_assert(ARRAY_COUNT(anime_smog_titexdata_05_texs_tex) ==
                  anime_smog_titexdata_05_texs_tex_width * anime_smog_titexdata_05_texs_tex_height / 2,
              "The dimensions of `anime_smog_titexdata_05_texs_tex` does not match the size of the actual texture");

/* titexdata_06 */

#define anime_smog_titexdata_06_texs_tex_width 32
#define anime_smog_titexdata_06_texs_tex_height 32
extern u8 anime_smog_titexdata_06_texs_tex[];

TexturePtr anime_smog_titexdata_06_texs[2] = {
    NULL,
    anime_smog_titexdata_06_texs_tex,
};

u16 anime_smog_titexdata_06_info[] = {
    anime_smog_titexdata_06_texs_tex_width,
    anime_smog_titexdata_06_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 anime_smog_titexdata_06_texs_tex[] ALIGNED(8) = {
#include "assets/anime/anime_smog/anime_smog_titexdata_06_texs_tex.i4.inc"
};

static_assert(ARRAY_COUNT(anime_smog_titexdata_06_texs_tex) ==
                  anime_smog_titexdata_06_texs_tex_width * anime_smog_titexdata_06_texs_tex_height / 2,
              "The dimensions of `anime_smog_titexdata_06_texs_tex` does not match the size of the actual texture");

/* titexdata_07 */

#define anime_smog_titexdata_07_texs_tex_width 32
#define anime_smog_titexdata_07_texs_tex_height 32
extern u8 anime_smog_titexdata_07_texs_tex[];

TexturePtr anime_smog_titexdata_07_texs[2] = {
    NULL,
    anime_smog_titexdata_07_texs_tex,
};

u16 anime_smog_titexdata_07_info[] = {
    anime_smog_titexdata_07_texs_tex_width,
    anime_smog_titexdata_07_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 anime_smog_titexdata_07_texs_tex[] ALIGNED(8) = {
#include "assets/anime/anime_smog/anime_smog_titexdata_07_texs_tex.i4.inc"
};

static_assert(ARRAY_COUNT(anime_smog_titexdata_07_texs_tex) ==
                  anime_smog_titexdata_07_texs_tex_width * anime_smog_titexdata_07_texs_tex_height / 2,
              "The dimensions of `anime_smog_titexdata_07_texs_tex` does not match the size of the actual texture");

/* titexdata_08 */

#define anime_smog_titexdata_08_texs_tex_width 32
#define anime_smog_titexdata_08_texs_tex_height 32
extern u8 anime_smog_titexdata_08_texs_tex[];

TexturePtr anime_smog_titexdata_08_texs[2] = {
    NULL,
    anime_smog_titexdata_08_texs_tex,
};

u16 anime_smog_titexdata_08_info[] = {
    anime_smog_titexdata_08_texs_tex_width,
    anime_smog_titexdata_08_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 anime_smog_titexdata_08_texs_tex[] ALIGNED(8) = {
#include "assets/anime/anime_smog/anime_smog_titexdata_08_texs_tex.i4.inc"
};

static_assert(ARRAY_COUNT(anime_smog_titexdata_08_texs_tex) ==
                  anime_smog_titexdata_08_texs_tex_width * anime_smog_titexdata_08_texs_tex_height / 2,
              "The dimensions of `anime_smog_titexdata_08_texs_tex` does not match the size of the actual texture");

TiTexData anime_smog_titexdata[] = {
    { anime_smog_titexdata_00_texs, anime_smog_titexdata_00_info },
    { anime_smog_titexdata_01_texs, anime_smog_titexdata_01_info },
    { anime_smog_titexdata_02_texs, anime_smog_titexdata_02_info },
    { anime_smog_titexdata_03_texs, anime_smog_titexdata_03_info },
    { anime_smog_titexdata_04_texs, anime_smog_titexdata_04_info },
    { anime_smog_titexdata_05_texs, anime_smog_titexdata_05_info },
    { anime_smog_titexdata_06_texs, anime_smog_titexdata_06_info },
    { anime_smog_titexdata_07_texs, anime_smog_titexdata_07_info },
    { anime_smog_titexdata_08_texs, anime_smog_titexdata_08_info },
};

s32 anime_smog_titexdata_len = ARRAY_COUNT(anime_smog_titexdata);

u8 anime_smog_metadata_00[] = {
    0x01,
    0x01,
    0x01,
    0x02,
    0x02,
    0x02,
    0x03,
    0x03,
    0x03,
    0x04,
    0x04,
    0x04,
    0x05,
    0x05,
    0x05,
    0x06,
    0x06,
    0x06,
    0x07,
    0x07,
    0x07,
    0x08,
    0x08,
    0x08,
    0x09,
    0x09,
    0x09,
    0x00,
    ANIME_METADATA_END,
};

u8 anime_smog_metadata_01[] = {
    0x00,
    ANIME_METADATA_END,
};

u8 anime_smog_metadata_02[] = {
    0x00,
    ANIME_METADATA_END,
};

u8 anime_smog_metadata_03[] = {
    0x00,
    ANIME_METADATA_END,
};

u8 anime_smog_metadata_04[] = {
    0x00,
    ANIME_METADATA_END,
};

u8 *anime_smog_metadata[] = {
    anime_smog_metadata_00, anime_smog_metadata_01, anime_smog_metadata_02,
    anime_smog_metadata_03, anime_smog_metadata_04,
};

s32 anime_smog_metadata_len = ARRAY_COUNT(anime_smog_metadata);

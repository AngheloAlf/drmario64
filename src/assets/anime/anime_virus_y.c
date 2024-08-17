#include "tex_func.h"
#include "char_anime.h"

#include "libc/assert.h"
#include "macros_defines.h"
#include "alignment.h"

extern TiTexData anime_virus_y_titexdata[];
extern s32 anime_virus_y_titexdata_len;
extern u8 *anime_virus_y_metadata[];
extern s32 anime_virus_y_metadata_len;

AnimeHeader anime_virus_y_header = {
    anime_virus_y_titexdata,
    &anime_virus_y_titexdata_len,
    anime_virus_y_metadata,
    &anime_virus_y_metadata_len,
};

/* titexdata_00 */

#define anime_virus_y_titexdata_00_texs_tex_width 32
#define anime_virus_y_titexdata_00_texs_tex_height 32
extern u8 anime_virus_y_titexdata_00_texs_tex[];
extern u16 anime_virus_y_titexdata_00_texs_tlut[];

TexturePtr anime_virus_y_titexdata_00_texs[2] = {
    anime_virus_y_titexdata_00_texs_tlut,
    anime_virus_y_titexdata_00_texs_tex,
};

u16 anime_virus_y_titexdata_00_info[] = {
    anime_virus_y_titexdata_00_texs_tex_width,
    anime_virus_y_titexdata_00_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u16 anime_virus_y_titexdata_00_texs_tlut[] ALIGNED(8) = {
#include "assets/anime/anime_virus_y/anime_virus_y_titexdata_00_texs_tex.palette.inc"
};

u8 anime_virus_y_titexdata_00_texs_tex[] ALIGNED(8) = {
#include "assets/anime/anime_virus_y/anime_virus_y_titexdata_00_texs_tex.ci4.inc"
};

static_assert(ARRAY_COUNT(anime_virus_y_titexdata_00_texs_tlut) == 4 * 4,
              "The dimensions of `anime_virus_y_titexdata_00_texs_tlut` does not match the size of the actual tlut");
static_assert(ARRAY_COUNT(anime_virus_y_titexdata_00_texs_tex) ==
                  anime_virus_y_titexdata_00_texs_tex_width * anime_virus_y_titexdata_00_texs_tex_height / 2,
              "The dimensions of `anime_virus_y_titexdata_00_texs_tex` does not match the size of the actual texture");

/* titexdata_01 */

#define anime_virus_y_titexdata_01_texs_tex_width 32
#define anime_virus_y_titexdata_01_texs_tex_height 32
extern u8 anime_virus_y_titexdata_01_texs_tex[];

TexturePtr anime_virus_y_titexdata_01_texs[2] = {
    NULL,
    anime_virus_y_titexdata_01_texs_tex,
};

u16 anime_virus_y_titexdata_01_info[] = {
    anime_virus_y_titexdata_01_texs_tex_width,
    anime_virus_y_titexdata_01_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 anime_virus_y_titexdata_01_texs_tex[] ALIGNED(8) = {
#include "assets/anime/anime_virus_y/anime_virus_y_titexdata_01_texs_tex.i4.inc"
};

static_assert(ARRAY_COUNT(anime_virus_y_titexdata_01_texs_tex) ==
                  anime_virus_y_titexdata_01_texs_tex_width * anime_virus_y_titexdata_01_texs_tex_height / 2,
              "The dimensions of `anime_virus_y_titexdata_01_texs_tex` does not match the size of the actual texture");

/* titexdata_02 */

#define anime_virus_y_titexdata_02_texs_tex_width 32
#define anime_virus_y_titexdata_02_texs_tex_height 32
extern u8 anime_virus_y_titexdata_02_texs_tex[];

TexturePtr anime_virus_y_titexdata_02_texs[2] = {
    NULL,
    anime_virus_y_titexdata_02_texs_tex,
};

u16 anime_virus_y_titexdata_02_info[] = {
    anime_virus_y_titexdata_02_texs_tex_width,
    anime_virus_y_titexdata_02_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 anime_virus_y_titexdata_02_texs_tex[] ALIGNED(8) = {
#include "assets/anime/anime_virus_y/anime_virus_y_titexdata_02_texs_tex.i4.inc"
};

static_assert(ARRAY_COUNT(anime_virus_y_titexdata_02_texs_tex) ==
                  anime_virus_y_titexdata_02_texs_tex_width * anime_virus_y_titexdata_02_texs_tex_height / 2,
              "The dimensions of `anime_virus_y_titexdata_02_texs_tex` does not match the size of the actual texture");

/* titexdata_03 */

#define anime_virus_y_titexdata_03_texs_tex_width 32
#define anime_virus_y_titexdata_03_texs_tex_height 32
extern u8 anime_virus_y_titexdata_03_texs_tex[];

TexturePtr anime_virus_y_titexdata_03_texs[2] = {
    NULL,
    anime_virus_y_titexdata_03_texs_tex,
};

u16 anime_virus_y_titexdata_03_info[] = {
    anime_virus_y_titexdata_03_texs_tex_width,
    anime_virus_y_titexdata_03_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 anime_virus_y_titexdata_03_texs_tex[] ALIGNED(8) = {
#include "assets/anime/anime_virus_y/anime_virus_y_titexdata_03_texs_tex.i4.inc"
};

static_assert(ARRAY_COUNT(anime_virus_y_titexdata_03_texs_tex) ==
                  anime_virus_y_titexdata_03_texs_tex_width * anime_virus_y_titexdata_03_texs_tex_height / 2,
              "The dimensions of `anime_virus_y_titexdata_03_texs_tex` does not match the size of the actual texture");

/* titexdata_04 */

#define anime_virus_y_titexdata_04_texs_tex_width 32
#define anime_virus_y_titexdata_04_texs_tex_height 32
extern u8 anime_virus_y_titexdata_04_texs_tex[];

TexturePtr anime_virus_y_titexdata_04_texs[2] = {
    NULL,
    anime_virus_y_titexdata_04_texs_tex,
};

u16 anime_virus_y_titexdata_04_info[] = {
    anime_virus_y_titexdata_04_texs_tex_width,
    anime_virus_y_titexdata_04_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 anime_virus_y_titexdata_04_texs_tex[] ALIGNED(8) = {
#include "assets/anime/anime_virus_y/anime_virus_y_titexdata_04_texs_tex.i4.inc"
};

static_assert(ARRAY_COUNT(anime_virus_y_titexdata_04_texs_tex) ==
                  anime_virus_y_titexdata_04_texs_tex_width * anime_virus_y_titexdata_04_texs_tex_height / 2,
              "The dimensions of `anime_virus_y_titexdata_04_texs_tex` does not match the size of the actual texture");

/* titexdata_05 */

#define anime_virus_y_titexdata_05_texs_tex_width 32
#define anime_virus_y_titexdata_05_texs_tex_height 32
extern u8 anime_virus_y_titexdata_05_texs_tex[];

TexturePtr anime_virus_y_titexdata_05_texs[2] = {
    NULL,
    anime_virus_y_titexdata_05_texs_tex,
};

u16 anime_virus_y_titexdata_05_info[] = {
    anime_virus_y_titexdata_05_texs_tex_width,
    anime_virus_y_titexdata_05_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 anime_virus_y_titexdata_05_texs_tex[] ALIGNED(8) = {
#include "assets/anime/anime_virus_y/anime_virus_y_titexdata_05_texs_tex.i4.inc"
};

static_assert(ARRAY_COUNT(anime_virus_y_titexdata_05_texs_tex) ==
                  anime_virus_y_titexdata_05_texs_tex_width * anime_virus_y_titexdata_05_texs_tex_height / 2,
              "The dimensions of `anime_virus_y_titexdata_05_texs_tex` does not match the size of the actual texture");

/* titexdata_06 */

#define anime_virus_y_titexdata_06_texs_tex_width 32
#define anime_virus_y_titexdata_06_texs_tex_height 32
extern u8 anime_virus_y_titexdata_06_texs_tex[];

TexturePtr anime_virus_y_titexdata_06_texs[2] = {
    NULL,
    anime_virus_y_titexdata_06_texs_tex,
};

u16 anime_virus_y_titexdata_06_info[] = {
    anime_virus_y_titexdata_06_texs_tex_width,
    anime_virus_y_titexdata_06_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 anime_virus_y_titexdata_06_texs_tex[] ALIGNED(8) = {
#include "assets/anime/anime_virus_y/anime_virus_y_titexdata_06_texs_tex.i4.inc"
};

static_assert(ARRAY_COUNT(anime_virus_y_titexdata_06_texs_tex) ==
                  anime_virus_y_titexdata_06_texs_tex_width * anime_virus_y_titexdata_06_texs_tex_height / 2,
              "The dimensions of `anime_virus_y_titexdata_06_texs_tex` does not match the size of the actual texture");

/* titexdata_07 */

#define anime_virus_y_titexdata_07_texs_tex_width 32
#define anime_virus_y_titexdata_07_texs_tex_height 32
extern u8 anime_virus_y_titexdata_07_texs_tex[];

TexturePtr anime_virus_y_titexdata_07_texs[2] = {
    NULL,
    anime_virus_y_titexdata_07_texs_tex,
};

u16 anime_virus_y_titexdata_07_info[] = {
    anime_virus_y_titexdata_07_texs_tex_width,
    anime_virus_y_titexdata_07_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 anime_virus_y_titexdata_07_texs_tex[] ALIGNED(8) = {
#include "assets/anime/anime_virus_y/anime_virus_y_titexdata_07_texs_tex.i4.inc"
};

static_assert(ARRAY_COUNT(anime_virus_y_titexdata_07_texs_tex) ==
                  anime_virus_y_titexdata_07_texs_tex_width * anime_virus_y_titexdata_07_texs_tex_height / 2,
              "The dimensions of `anime_virus_y_titexdata_07_texs_tex` does not match the size of the actual texture");

/* titexdata_08 */

#define anime_virus_y_titexdata_08_texs_tex_width 32
#define anime_virus_y_titexdata_08_texs_tex_height 32
extern u8 anime_virus_y_titexdata_08_texs_tex[];

TexturePtr anime_virus_y_titexdata_08_texs[2] = {
    NULL,
    anime_virus_y_titexdata_08_texs_tex,
};

u16 anime_virus_y_titexdata_08_info[] = {
    anime_virus_y_titexdata_08_texs_tex_width,
    anime_virus_y_titexdata_08_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 anime_virus_y_titexdata_08_texs_tex[] ALIGNED(8) = {
#include "assets/anime/anime_virus_y/anime_virus_y_titexdata_08_texs_tex.i4.inc"
};

static_assert(ARRAY_COUNT(anime_virus_y_titexdata_08_texs_tex) ==
                  anime_virus_y_titexdata_08_texs_tex_width * anime_virus_y_titexdata_08_texs_tex_height / 2,
              "The dimensions of `anime_virus_y_titexdata_08_texs_tex` does not match the size of the actual texture");

/* titexdata_09 */

#define anime_virus_y_titexdata_09_texs_tex_width 32
#define anime_virus_y_titexdata_09_texs_tex_height 32
extern u8 anime_virus_y_titexdata_09_texs_tex[];

TexturePtr anime_virus_y_titexdata_09_texs[2] = {
    NULL,
    anime_virus_y_titexdata_09_texs_tex,
};

u16 anime_virus_y_titexdata_09_info[] = {
    anime_virus_y_titexdata_09_texs_tex_width,
    anime_virus_y_titexdata_09_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 anime_virus_y_titexdata_09_texs_tex[] ALIGNED(8) = {
#include "assets/anime/anime_virus_y/anime_virus_y_titexdata_09_texs_tex.i4.inc"
};

static_assert(ARRAY_COUNT(anime_virus_y_titexdata_09_texs_tex) ==
                  anime_virus_y_titexdata_09_texs_tex_width * anime_virus_y_titexdata_09_texs_tex_height / 2,
              "The dimensions of `anime_virus_y_titexdata_09_texs_tex` does not match the size of the actual texture");

TiTexData anime_virus_y_titexdata[] = {
    { anime_virus_y_titexdata_00_texs, anime_virus_y_titexdata_00_info },
    { anime_virus_y_titexdata_01_texs, anime_virus_y_titexdata_01_info },
    { anime_virus_y_titexdata_02_texs, anime_virus_y_titexdata_02_info },
    { anime_virus_y_titexdata_03_texs, anime_virus_y_titexdata_03_info },
    { anime_virus_y_titexdata_04_texs, anime_virus_y_titexdata_04_info },
    { anime_virus_y_titexdata_05_texs, anime_virus_y_titexdata_05_info },
    { anime_virus_y_titexdata_06_texs, anime_virus_y_titexdata_06_info },
    { anime_virus_y_titexdata_07_texs, anime_virus_y_titexdata_07_info },
    { anime_virus_y_titexdata_08_texs, anime_virus_y_titexdata_08_info },
    { anime_virus_y_titexdata_09_texs, anime_virus_y_titexdata_09_info },
};

s32 anime_virus_y_titexdata_len = ARRAY_COUNT(anime_virus_y_titexdata);

u8 anime_virus_y_metadata_00[] = {
    ANIME_METADATA_CMD_F0(0xFF), 0x05, 0x05, 0x05, 0x05, 0x06, 0x06, 0x06, 0x06, 0x07, 0x07, 0x07, 0x07,
    ANIME_METADATA_CMD_F1(0x64),
};

u8 anime_virus_y_metadata_01[] = {
    ANIME_METADATA_CMD_F2(0x00),
    0x00,
    0x00,
};

u8 anime_virus_y_metadata_02[] = {
    0x01,
    0x01,
    0x01,
    0x01,
    0x02,
    0x02,
    0x02,
    0x02,
    ANIME_METADATA_CMD_F0(0x0A),
    0x03,
    0x03,
    0x03,
    0x03,
    0x04,
    0x04,
    0x04,
    0x04,
    ANIME_METADATA_CMD_F1(0x64),
    ANIME_METADATA_CMD_F2(0x00),
    0x00,
    0x00,
};

u8 anime_virus_y_metadata_03[] = {
    ANIME_METADATA_CMD_F0(0xFF),
    0x08,
    0x08,
    0x08,
    0x08,
    0x09,
    0x09,
    0x09,
    0x09,
    0x0A,
    0x0A,
    0x0A,
    0x0A,
    0x0A,
    0x0A,
    0x0A,
    0x0A,
    0x09,
    0x09,
    0x09,
    0x09,
    ANIME_METADATA_CMD_F1(0x64),
};

u8 anime_virus_y_metadata_04[] = {
    0x01,
    0x01,
    0x01,
    0x01,
    0x02,
    0x02,
    0x02,
    0x02,
    ANIME_METADATA_CMD_F0(0x0A),
    0x03,
    0x03,
    0x03,
    0x03,
    0x04,
    0x04,
    0x04,
    0x04,
    ANIME_METADATA_CMD_F1(0x64),
    0x00,
    ANIME_METADATA_END,
};

u8 *anime_virus_y_metadata[] = {
    anime_virus_y_metadata_00, anime_virus_y_metadata_01, anime_virus_y_metadata_02,
    anime_virus_y_metadata_03, anime_virus_y_metadata_04,
};

s32 anime_virus_y_metadata_len = ARRAY_COUNT(anime_virus_y_metadata);

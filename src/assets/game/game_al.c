#include "tex_func.h"

#include "libc/assert.h"
#include "macros_defines.h"
#include "alignment.h"

extern TiTexData game_al_titexdata[];
extern s32 game_al_titexdata_len;

TiTexDataHeader game_al_header = {
    game_al_titexdata,
    &game_al_titexdata_len,
};

/* titexdata_00 */

extern u8 game_al_titexdata_00_texs_tex[];

TiTexDataTextures game_al_titexdata_00_texs = {
    NULL,
    game_al_titexdata_00_texs_tex,
};

#define game_al_titexdata_00_texs_tex_width 32
#define game_al_titexdata_00_texs_tex_height 32

u16 game_al_titexdata_00_info[] = {
    game_al_titexdata_00_texs_tex_width, game_al_titexdata_00_texs_tex_height, TITEX_FORMAT_4, TITEX_FLAGS_BLOCK,
};

u8 game_al_titexdata_00_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_al/game_al_titexdata_00_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(game_al_titexdata_00_texs_tex) == game_al_titexdata_00_texs_tex_width * game_al_titexdata_00_texs_tex_height / 2, "The dimensions of `game_al_titexdata_00_texs_tex` does not match the size of the actual texture");

/* titexdata_01 */

extern u8 game_al_titexdata_01_texs_tex[];

TiTexDataTextures game_al_titexdata_01_texs = {
    NULL,
    game_al_titexdata_01_texs_tex,
};

#define game_al_titexdata_01_texs_tex_width 32
#define game_al_titexdata_01_texs_tex_height 32

u16 game_al_titexdata_01_info[] = {
    game_al_titexdata_01_texs_tex_width, game_al_titexdata_01_texs_tex_height, TITEX_FORMAT_4, TITEX_FLAGS_BLOCK,
};

u8 game_al_titexdata_01_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_al/game_al_titexdata_01_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(game_al_titexdata_01_texs_tex) == game_al_titexdata_01_texs_tex_width * game_al_titexdata_01_texs_tex_height / 2, "The dimensions of `game_al_titexdata_01_texs_tex` does not match the size of the actual texture");

/* titexdata_02 */

extern u8 game_al_titexdata_02_texs_tex[];

TiTexDataTextures game_al_titexdata_02_texs = {
    NULL,
    game_al_titexdata_02_texs_tex,
};

#define game_al_titexdata_02_texs_tex_width 32
#define game_al_titexdata_02_texs_tex_height 32

u16 game_al_titexdata_02_info[] = {
    game_al_titexdata_02_texs_tex_width, game_al_titexdata_02_texs_tex_height, TITEX_FORMAT_4, TITEX_FLAGS_BLOCK,
};

u8 game_al_titexdata_02_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_al/game_al_titexdata_02_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(game_al_titexdata_02_texs_tex) == game_al_titexdata_02_texs_tex_width * game_al_titexdata_02_texs_tex_height / 2, "The dimensions of `game_al_titexdata_02_texs_tex` does not match the size of the actual texture");

/* titexdata_03 */

extern u8 game_al_titexdata_03_texs_tex[];

TiTexDataTextures game_al_titexdata_03_texs = {
    NULL,
    game_al_titexdata_03_texs_tex,
};

#define game_al_titexdata_03_texs_tex_width 32
#define game_al_titexdata_03_texs_tex_height 32

u16 game_al_titexdata_03_info[] = {
    game_al_titexdata_03_texs_tex_width, game_al_titexdata_03_texs_tex_height, TITEX_FORMAT_4, TITEX_FLAGS_BLOCK,
};

u8 game_al_titexdata_03_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_al/game_al_titexdata_03_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(game_al_titexdata_03_texs_tex) == game_al_titexdata_03_texs_tex_width * game_al_titexdata_03_texs_tex_height / 2, "The dimensions of `game_al_titexdata_03_texs_tex` does not match the size of the actual texture");

/* titexdata_04 */

extern u8 game_al_titexdata_04_texs_tex[];

TiTexDataTextures game_al_titexdata_04_texs = {
    NULL,
    game_al_titexdata_04_texs_tex,
};

#define game_al_titexdata_04_texs_tex_width 32
#define game_al_titexdata_04_texs_tex_height 32

u16 game_al_titexdata_04_info[] = {
    game_al_titexdata_04_texs_tex_width, game_al_titexdata_04_texs_tex_height, TITEX_FORMAT_4, TITEX_FLAGS_BLOCK,
};

u8 game_al_titexdata_04_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_al/game_al_titexdata_04_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(game_al_titexdata_04_texs_tex) == game_al_titexdata_04_texs_tex_width * game_al_titexdata_04_texs_tex_height / 2, "The dimensions of `game_al_titexdata_04_texs_tex` does not match the size of the actual texture");

/* titexdata_05 */

extern u8 game_al_titexdata_05_texs_tex[];

TiTexDataTextures game_al_titexdata_05_texs = {
    NULL,
    game_al_titexdata_05_texs_tex,
};

#define game_al_titexdata_05_texs_tex_width 32
#define game_al_titexdata_05_texs_tex_height 32

u16 game_al_titexdata_05_info[] = {
    game_al_titexdata_05_texs_tex_width, game_al_titexdata_05_texs_tex_height, TITEX_FORMAT_4, TITEX_FLAGS_BLOCK,
};

u8 game_al_titexdata_05_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_al/game_al_titexdata_05_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(game_al_titexdata_05_texs_tex) == game_al_titexdata_05_texs_tex_width * game_al_titexdata_05_texs_tex_height / 2, "The dimensions of `game_al_titexdata_05_texs_tex` does not match the size of the actual texture");

/* titexdata_06 */

extern u8 game_al_titexdata_06_texs_tex[];

TiTexDataTextures game_al_titexdata_06_texs = {
    NULL,
    game_al_titexdata_06_texs_tex,
};

#define game_al_titexdata_06_texs_tex_width 32
#define game_al_titexdata_06_texs_tex_height 32

u16 game_al_titexdata_06_info[] = {
    game_al_titexdata_06_texs_tex_width, game_al_titexdata_06_texs_tex_height, TITEX_FORMAT_4, TITEX_FLAGS_BLOCK,
};

u8 game_al_titexdata_06_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_al/game_al_titexdata_06_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(game_al_titexdata_06_texs_tex) == game_al_titexdata_06_texs_tex_width * game_al_titexdata_06_texs_tex_height / 2, "The dimensions of `game_al_titexdata_06_texs_tex` does not match the size of the actual texture");

/* titexdata_07 */

extern u8 game_al_titexdata_07_texs_tex[];

TiTexDataTextures game_al_titexdata_07_texs = {
    NULL,
    game_al_titexdata_07_texs_tex,
};

#define game_al_titexdata_07_texs_tex_width 32
#define game_al_titexdata_07_texs_tex_height 32

u16 game_al_titexdata_07_info[] = {
    game_al_titexdata_07_texs_tex_width, game_al_titexdata_07_texs_tex_height, TITEX_FORMAT_4, TITEX_FLAGS_BLOCK,
};

u8 game_al_titexdata_07_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_al/game_al_titexdata_07_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(game_al_titexdata_07_texs_tex) == game_al_titexdata_07_texs_tex_width * game_al_titexdata_07_texs_tex_height / 2, "The dimensions of `game_al_titexdata_07_texs_tex` does not match the size of the actual texture");

/* titexdata_08 */

extern u8 game_al_titexdata_08_texs_tex[];

TiTexDataTextures game_al_titexdata_08_texs = {
    NULL,
    game_al_titexdata_08_texs_tex,
};

#define game_al_titexdata_08_texs_tex_width 32
#define game_al_titexdata_08_texs_tex_height 32

u16 game_al_titexdata_08_info[] = {
    game_al_titexdata_08_texs_tex_width, game_al_titexdata_08_texs_tex_height, TITEX_FORMAT_4, TITEX_FLAGS_BLOCK,
};

u8 game_al_titexdata_08_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_al/game_al_titexdata_08_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(game_al_titexdata_08_texs_tex) == game_al_titexdata_08_texs_tex_width * game_al_titexdata_08_texs_tex_height / 2, "The dimensions of `game_al_titexdata_08_texs_tex` does not match the size of the actual texture");

/* titexdata_09 */

extern u8 game_al_titexdata_09_texs_tex[];

TiTexDataTextures game_al_titexdata_09_texs = {
    NULL,
    game_al_titexdata_09_texs_tex,
};

#define game_al_titexdata_09_texs_tex_width 32
#define game_al_titexdata_09_texs_tex_height 32

u16 game_al_titexdata_09_info[] = {
    game_al_titexdata_09_texs_tex_width, game_al_titexdata_09_texs_tex_height, TITEX_FORMAT_4, TITEX_FLAGS_BLOCK,
};

u8 game_al_titexdata_09_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_al/game_al_titexdata_09_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(game_al_titexdata_09_texs_tex) == game_al_titexdata_09_texs_tex_width * game_al_titexdata_09_texs_tex_height / 2, "The dimensions of `game_al_titexdata_09_texs_tex` does not match the size of the actual texture");

/* titexdata_10 */

extern u8 game_al_titexdata_10_texs_tex[];

TiTexDataTextures game_al_titexdata_10_texs = {
    NULL,
    game_al_titexdata_10_texs_tex,
};

#define game_al_titexdata_10_texs_tex_width 32
#define game_al_titexdata_10_texs_tex_height 32

u16 game_al_titexdata_10_info[] = {
    game_al_titexdata_10_texs_tex_width, game_al_titexdata_10_texs_tex_height, TITEX_FORMAT_4, TITEX_FLAGS_BLOCK,
};

u8 game_al_titexdata_10_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_al/game_al_titexdata_10_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(game_al_titexdata_10_texs_tex) == game_al_titexdata_10_texs_tex_width * game_al_titexdata_10_texs_tex_height / 2, "The dimensions of `game_al_titexdata_10_texs_tex` does not match the size of the actual texture");

/* titexdata_11 */

extern u8 game_al_titexdata_11_texs_tex[];

TiTexDataTextures game_al_titexdata_11_texs = {
    NULL,
    game_al_titexdata_11_texs_tex,
};

#define game_al_titexdata_11_texs_tex_width 32
#define game_al_titexdata_11_texs_tex_height 32

u16 game_al_titexdata_11_info[] = {
    game_al_titexdata_11_texs_tex_width, game_al_titexdata_11_texs_tex_height, TITEX_FORMAT_4, TITEX_FLAGS_BLOCK,
};

u8 game_al_titexdata_11_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_al/game_al_titexdata_11_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(game_al_titexdata_11_texs_tex) == game_al_titexdata_11_texs_tex_width * game_al_titexdata_11_texs_tex_height / 2, "The dimensions of `game_al_titexdata_11_texs_tex` does not match the size of the actual texture");

/* titexdata_12 */

extern u8 game_al_titexdata_12_texs_tex[];

TiTexDataTextures game_al_titexdata_12_texs = {
    NULL,
    game_al_titexdata_12_texs_tex,
};

#define game_al_titexdata_12_texs_tex_width 16
#define game_al_titexdata_12_texs_tex_height 16

u16 game_al_titexdata_12_info[] = {
    game_al_titexdata_12_texs_tex_width, game_al_titexdata_12_texs_tex_height, TITEX_FORMAT_4, TITEX_FLAGS_BLOCK,
};

u8 game_al_titexdata_12_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_al/game_al_titexdata_12_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(game_al_titexdata_12_texs_tex) == game_al_titexdata_12_texs_tex_width * game_al_titexdata_12_texs_tex_height / 2, "The dimensions of `game_al_titexdata_12_texs_tex` does not match the size of the actual texture");

/* titexdata_13 */

extern u16 game_al_titexdata_13_texs_tex[];

TiTexDataTextures game_al_titexdata_13_texs = {
    NULL,
    game_al_titexdata_13_texs_tex,
};

#define game_al_titexdata_13_texs_tex_width 16
#define game_al_titexdata_13_texs_tex_height 200

u16 game_al_titexdata_13_info[] = {
    game_al_titexdata_13_texs_tex_width, game_al_titexdata_13_texs_tex_height, TITEX_FORMAT_16, TITEX_FLAGS_BLOCK,
};

u16 game_al_titexdata_13_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_al/game_al_titexdata_13_texs_tex.rgba16.inc"
};
static_assert(ARRAY_COUNT(game_al_titexdata_13_texs_tex) == game_al_titexdata_13_texs_tex_width * game_al_titexdata_13_texs_tex_height, "The dimensions of `game_al_titexdata_13_texs_tex` does not match the size of the actual texture");

/* titexdata_14 */

extern u16 game_al_titexdata_14_texs_tex[];

TiTexDataTextures game_al_titexdata_14_texs = {
    NULL,
    game_al_titexdata_14_texs_tex,
};

#define game_al_titexdata_14_texs_tex_width 108
#define game_al_titexdata_14_texs_tex_height 13

u16 game_al_titexdata_14_info[] = {
    game_al_titexdata_14_texs_tex_width, game_al_titexdata_14_texs_tex_height, TITEX_FORMAT_16, TITEX_FLAGS_BLOCK,
};

u16 game_al_titexdata_14_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_al/game_al_titexdata_14_texs_tex.rgba16.inc"
};
static_assert(ARRAY_COUNT(game_al_titexdata_14_texs_tex) == game_al_titexdata_14_texs_tex_width * game_al_titexdata_14_texs_tex_height, "The dimensions of `game_al_titexdata_14_texs_tex` does not match the size of the actual texture");

/* titexdata_15 */

extern u16 game_al_titexdata_15_texs_tex[];

TiTexDataTextures game_al_titexdata_15_texs = {
    NULL,
    game_al_titexdata_15_texs_tex,
};

#define game_al_titexdata_15_texs_tex_width 64
#define game_al_titexdata_15_texs_tex_height 15

u16 game_al_titexdata_15_info[] = {
    game_al_titexdata_15_texs_tex_width, game_al_titexdata_15_texs_tex_height, TITEX_FORMAT_16, TITEX_FLAGS_BLOCK,
};

u16 game_al_titexdata_15_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_al/game_al_titexdata_15_texs_tex.rgba16.inc"
};
static_assert(ARRAY_COUNT(game_al_titexdata_15_texs_tex) == game_al_titexdata_15_texs_tex_width * game_al_titexdata_15_texs_tex_height, "The dimensions of `game_al_titexdata_15_texs_tex` does not match the size of the actual texture");

/* titexdata_16 */

extern u16 game_al_titexdata_16_texs_tex[];

TiTexDataTextures game_al_titexdata_16_texs = {
    NULL,
    game_al_titexdata_16_texs_tex,
};

#define game_al_titexdata_16_texs_tex_width 24
#define game_al_titexdata_16_texs_tex_height 320

u16 game_al_titexdata_16_info[] = {
    game_al_titexdata_16_texs_tex_width, game_al_titexdata_16_texs_tex_height, TITEX_FORMAT_16, TITEX_FLAGS_BLOCK,
};

u16 game_al_titexdata_16_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_al/game_al_titexdata_16_texs_tex.rgba16.inc"
};
static_assert(ARRAY_COUNT(game_al_titexdata_16_texs_tex) == game_al_titexdata_16_texs_tex_width * game_al_titexdata_16_texs_tex_height, "The dimensions of `game_al_titexdata_16_texs_tex` does not match the size of the actual texture");

/* titexdata_17 */

extern u16 game_al_titexdata_17_texs_tex[];

TiTexDataTextures game_al_titexdata_17_texs = {
    NULL,
    game_al_titexdata_17_texs_tex,
};

#define game_al_titexdata_17_texs_tex_width 16
#define game_al_titexdata_17_texs_tex_height 144

u16 game_al_titexdata_17_info[] = {
    game_al_titexdata_17_texs_tex_width, game_al_titexdata_17_texs_tex_height, TITEX_FORMAT_16, TITEX_FLAGS_BLOCK,
};

u16 game_al_titexdata_17_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_al/game_al_titexdata_17_texs_tex.rgba16.inc"
};
static_assert(ARRAY_COUNT(game_al_titexdata_17_texs_tex) == game_al_titexdata_17_texs_tex_width * game_al_titexdata_17_texs_tex_height, "The dimensions of `game_al_titexdata_17_texs_tex` does not match the size of the actual texture");

/* titexdata_18 */

extern u8 game_al_titexdata_18_texs_tex[];

TiTexDataTextures game_al_titexdata_18_texs = {
    NULL,
    game_al_titexdata_18_texs_tex,
};

#define game_al_titexdata_18_texs_tex_width 16
#define game_al_titexdata_18_texs_tex_height 200

u16 game_al_titexdata_18_info[] = {
    game_al_titexdata_18_texs_tex_width, game_al_titexdata_18_texs_tex_height, TITEX_FORMAT_4, TITEX_FLAGS_BLOCK,
};

u8 game_al_titexdata_18_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_al/game_al_titexdata_18_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(game_al_titexdata_18_texs_tex) == game_al_titexdata_18_texs_tex_width * game_al_titexdata_18_texs_tex_height / 2, "The dimensions of `game_al_titexdata_18_texs_tex` does not match the size of the actual texture");

/* titexdata_19 */

extern u8 game_al_titexdata_19_texs_tex[];

TiTexDataTextures game_al_titexdata_19_texs = {
    NULL,
    game_al_titexdata_19_texs_tex,
};

#define game_al_titexdata_19_texs_tex_width 108
#define game_al_titexdata_19_texs_tex_height 13

u16 game_al_titexdata_19_info[] = {
    game_al_titexdata_19_texs_tex_width, game_al_titexdata_19_texs_tex_height, TITEX_FORMAT_4, TITEX_FLAGS_TILE,
};

u8 game_al_titexdata_19_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_al/game_al_titexdata_19_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(game_al_titexdata_19_texs_tex) == game_al_titexdata_19_texs_tex_width * game_al_titexdata_19_texs_tex_height / 2, "The dimensions of `game_al_titexdata_19_texs_tex` does not match the size of the actual texture");

/* titexdata_20 */

extern u8 game_al_titexdata_20_texs_tex[];

TiTexDataTextures game_al_titexdata_20_texs = {
    NULL,
    game_al_titexdata_20_texs_tex,
};

#define game_al_titexdata_20_texs_tex_width 64
#define game_al_titexdata_20_texs_tex_height 15

u16 game_al_titexdata_20_info[] = {
    game_al_titexdata_20_texs_tex_width, game_al_titexdata_20_texs_tex_height, TITEX_FORMAT_4, TITEX_FLAGS_BLOCK,
};

u8 game_al_titexdata_20_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_al/game_al_titexdata_20_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(game_al_titexdata_20_texs_tex) == game_al_titexdata_20_texs_tex_width * game_al_titexdata_20_texs_tex_height / 2, "The dimensions of `game_al_titexdata_20_texs_tex` does not match the size of the actual texture");

/* titexdata_21 */

extern u8 game_al_titexdata_21_texs_tex[];

TiTexDataTextures game_al_titexdata_21_texs = {
    NULL,
    game_al_titexdata_21_texs_tex,
};

#define game_al_titexdata_21_texs_tex_width 32
#define game_al_titexdata_21_texs_tex_height 320

u16 game_al_titexdata_21_info[] = {
    game_al_titexdata_21_texs_tex_width, game_al_titexdata_21_texs_tex_height, TITEX_FORMAT_4, TITEX_FLAGS_BLOCK,
};

u8 game_al_titexdata_21_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_al/game_al_titexdata_21_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(game_al_titexdata_21_texs_tex) == game_al_titexdata_21_texs_tex_width * game_al_titexdata_21_texs_tex_height / 2, "The dimensions of `game_al_titexdata_21_texs_tex` does not match the size of the actual texture");

/* titexdata_22 */

extern u8 game_al_titexdata_22_texs_tex[];

TiTexDataTextures game_al_titexdata_22_texs = {
    NULL,
    game_al_titexdata_22_texs_tex,
};

#define game_al_titexdata_22_texs_tex_width 16
#define game_al_titexdata_22_texs_tex_height 144

u16 game_al_titexdata_22_info[] = {
    game_al_titexdata_22_texs_tex_width, game_al_titexdata_22_texs_tex_height, TITEX_FORMAT_4, TITEX_FLAGS_BLOCK,
};

u8 game_al_titexdata_22_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_al/game_al_titexdata_22_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(game_al_titexdata_22_texs_tex) == game_al_titexdata_22_texs_tex_width * game_al_titexdata_22_texs_tex_height / 2, "The dimensions of `game_al_titexdata_22_texs_tex` does not match the size of the actual texture");

/* titexdata_23 */

extern u16 game_al_titexdata_23_texs_tex[];

TiTexDataTextures game_al_titexdata_23_texs = {
    NULL,
    game_al_titexdata_23_texs_tex,
};

#define game_al_titexdata_23_texs_tex_width 64
#define game_al_titexdata_23_texs_tex_height 11

u16 game_al_titexdata_23_info[] = {
    game_al_titexdata_23_texs_tex_width, game_al_titexdata_23_texs_tex_height, TITEX_FORMAT_16, TITEX_FLAGS_BLOCK,
};

u16 game_al_titexdata_23_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_al/game_al_titexdata_23_texs_tex.rgba16.inc"
};
static_assert(ARRAY_COUNT(game_al_titexdata_23_texs_tex) == game_al_titexdata_23_texs_tex_width * game_al_titexdata_23_texs_tex_height, "The dimensions of `game_al_titexdata_23_texs_tex` does not match the size of the actual texture");

/* titexdata_24 */

extern u8 game_al_titexdata_24_texs_tex[];

TiTexDataTextures game_al_titexdata_24_texs = {
    NULL,
    game_al_titexdata_24_texs_tex,
};

#define game_al_titexdata_24_texs_tex_width 64
#define game_al_titexdata_24_texs_tex_height 11

u16 game_al_titexdata_24_info[] = {
    game_al_titexdata_24_texs_tex_width, game_al_titexdata_24_texs_tex_height, TITEX_FORMAT_4, TITEX_FLAGS_BLOCK,
};

u8 game_al_titexdata_24_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_al/game_al_titexdata_24_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(game_al_titexdata_24_texs_tex) == game_al_titexdata_24_texs_tex_width * game_al_titexdata_24_texs_tex_height / 2, "The dimensions of `game_al_titexdata_24_texs_tex` does not match the size of the actual texture");

/* titexdata_25 */

extern u16 game_al_titexdata_25_texs_tex[];

TiTexDataTextures game_al_titexdata_25_texs = {
    NULL,
    game_al_titexdata_25_texs_tex,
};

#define game_al_titexdata_25_texs_tex_width 128
#define game_al_titexdata_25_texs_tex_height 32

u16 game_al_titexdata_25_info[] = {
    game_al_titexdata_25_texs_tex_width, game_al_titexdata_25_texs_tex_height, TITEX_FORMAT_16, TITEX_FLAGS_BLOCK,
};

u16 game_al_titexdata_25_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_al/game_al_titexdata_25_texs_tex.rgba16.inc"
};
static_assert(ARRAY_COUNT(game_al_titexdata_25_texs_tex) == game_al_titexdata_25_texs_tex_width * game_al_titexdata_25_texs_tex_height, "The dimensions of `game_al_titexdata_25_texs_tex` does not match the size of the actual texture");

/* titexdata_26 */

extern u8 game_al_titexdata_26_texs_tex[];

TiTexDataTextures game_al_titexdata_26_texs = {
    NULL,
    game_al_titexdata_26_texs_tex,
};

#define game_al_titexdata_26_texs_tex_width 128
#define game_al_titexdata_26_texs_tex_height 32

u16 game_al_titexdata_26_info[] = {
    game_al_titexdata_26_texs_tex_width, game_al_titexdata_26_texs_tex_height, TITEX_FORMAT_4, TITEX_FLAGS_BLOCK,
};

u8 game_al_titexdata_26_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_al/game_al_titexdata_26_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(game_al_titexdata_26_texs_tex) == game_al_titexdata_26_texs_tex_width * game_al_titexdata_26_texs_tex_height / 2, "The dimensions of `game_al_titexdata_26_texs_tex` does not match the size of the actual texture");

/* titexdata_27 */

extern u16 game_al_titexdata_27_texs_tex[];

TiTexDataTextures game_al_titexdata_27_texs = {
    NULL,
    game_al_titexdata_27_texs_tex,
};

#define game_al_titexdata_27_texs_tex_width 108
#define game_al_titexdata_27_texs_tex_height 13

u16 game_al_titexdata_27_info[] = {
    game_al_titexdata_27_texs_tex_width, game_al_titexdata_27_texs_tex_height, TITEX_FORMAT_16, TITEX_FLAGS_BLOCK,
};

u16 game_al_titexdata_27_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_al/game_al_titexdata_27_texs_tex.rgba16.inc"
};
static_assert(ARRAY_COUNT(game_al_titexdata_27_texs_tex) == game_al_titexdata_27_texs_tex_width * game_al_titexdata_27_texs_tex_height, "The dimensions of `game_al_titexdata_27_texs_tex` does not match the size of the actual texture");

/* titexdata_28 */

extern u8 game_al_titexdata_28_texs_tex[];

TiTexDataTextures game_al_titexdata_28_texs = {
    NULL,
    game_al_titexdata_28_texs_tex,
};

#define game_al_titexdata_28_texs_tex_width 108
#define game_al_titexdata_28_texs_tex_height 13

u16 game_al_titexdata_28_info[] = {
    game_al_titexdata_28_texs_tex_width, game_al_titexdata_28_texs_tex_height, TITEX_FORMAT_4, TITEX_FLAGS_TILE,
};

u8 game_al_titexdata_28_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_al/game_al_titexdata_28_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(game_al_titexdata_28_texs_tex) == game_al_titexdata_28_texs_tex_width * game_al_titexdata_28_texs_tex_height / 2, "The dimensions of `game_al_titexdata_28_texs_tex` does not match the size of the actual texture");

TiTexData game_al_titexdata[] = {
    { &game_al_titexdata_00_texs, game_al_titexdata_00_info },
    { &game_al_titexdata_01_texs, game_al_titexdata_01_info },
    { &game_al_titexdata_02_texs, game_al_titexdata_02_info },
    { &game_al_titexdata_03_texs, game_al_titexdata_03_info },
    { &game_al_titexdata_04_texs, game_al_titexdata_04_info },
    { &game_al_titexdata_05_texs, game_al_titexdata_05_info },
    { &game_al_titexdata_06_texs, game_al_titexdata_06_info },
    { &game_al_titexdata_07_texs, game_al_titexdata_07_info },
    { &game_al_titexdata_08_texs, game_al_titexdata_08_info },
    { &game_al_titexdata_09_texs, game_al_titexdata_09_info },
    { &game_al_titexdata_10_texs, game_al_titexdata_10_info },
    { &game_al_titexdata_11_texs, game_al_titexdata_11_info },
    { &game_al_titexdata_12_texs, game_al_titexdata_12_info },
    { &game_al_titexdata_13_texs, game_al_titexdata_13_info },
    { &game_al_titexdata_14_texs, game_al_titexdata_14_info },
    { &game_al_titexdata_15_texs, game_al_titexdata_15_info },
    { &game_al_titexdata_16_texs, game_al_titexdata_16_info },
    { &game_al_titexdata_17_texs, game_al_titexdata_17_info },
    { &game_al_titexdata_18_texs, game_al_titexdata_18_info },
    { &game_al_titexdata_19_texs, game_al_titexdata_19_info },
    { &game_al_titexdata_20_texs, game_al_titexdata_20_info },
    { &game_al_titexdata_21_texs, game_al_titexdata_21_info },
    { &game_al_titexdata_22_texs, game_al_titexdata_22_info },
    { &game_al_titexdata_23_texs, game_al_titexdata_23_info },
    { &game_al_titexdata_24_texs, game_al_titexdata_24_info },
    { &game_al_titexdata_25_texs, game_al_titexdata_25_info },
    { &game_al_titexdata_26_texs, game_al_titexdata_26_info },
    { &game_al_titexdata_27_texs, game_al_titexdata_27_info },
    { &game_al_titexdata_28_texs, game_al_titexdata_28_info },
};

s32 game_al_titexdata_len = ARRAY_COUNT(game_al_titexdata);

#include "tex_func.h"

#include "libc/assert.h"
#include "macros_defines.h"
#include "alignment.h"

extern TiTexData game_p2_titexdata[];
extern s32 game_p2_titexdata_len;

TiTexDataHeader game_p2_header = {
    game_p2_titexdata,
    &game_p2_titexdata_len,
};

#if VERSION_US || VERSION_GW

/* titexdata_00 */

extern u8 game_p2_titexdata_00_texs_tex[];

TiTexDataTextures game_p2_titexdata_00_texs = {
    NULL,
    game_p2_titexdata_00_texs_tex,
};

#define game_p2_titexdata_00_texs_tex_width 128
#define game_p2_titexdata_00_texs_tex_height 33

u16 game_p2_titexdata_00_info[] = {
    game_p2_titexdata_00_texs_tex_width,
    game_p2_titexdata_00_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 game_p2_titexdata_00_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_p2/game_p2_titexdata_00_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(game_p2_titexdata_00_texs_tex) ==
                  game_p2_titexdata_00_texs_tex_width * game_p2_titexdata_00_texs_tex_height / 2,
              "The dimensions of `game_p2_titexdata_00_texs_tex` does not match the size of the actual texture");

/* titexdata_01 */

extern u8 game_p2_titexdata_01_texs_tex[];

TiTexDataTextures game_p2_titexdata_01_texs = {
    NULL,
    game_p2_titexdata_01_texs_tex,
};

#define game_p2_titexdata_01_texs_tex_width 64
#define game_p2_titexdata_01_texs_tex_height 18

u16 game_p2_titexdata_01_info[] = {
    game_p2_titexdata_01_texs_tex_width,
    game_p2_titexdata_01_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 game_p2_titexdata_01_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_p2/game_p2_titexdata_01_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(game_p2_titexdata_01_texs_tex) ==
                  game_p2_titexdata_01_texs_tex_width * game_p2_titexdata_01_texs_tex_height / 2,
              "The dimensions of `game_p2_titexdata_01_texs_tex` does not match the size of the actual texture");

/* titexdata_02 */

extern u8 game_p2_titexdata_02_texs_tex[];

TiTexDataTextures game_p2_titexdata_02_texs = {
    NULL,
    game_p2_titexdata_02_texs_tex,
};

#define game_p2_titexdata_02_texs_tex_width 48
#define game_p2_titexdata_02_texs_tex_height 44

u16 game_p2_titexdata_02_info[] = {
    game_p2_titexdata_02_texs_tex_width,
    game_p2_titexdata_02_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 game_p2_titexdata_02_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_p2/game_p2_titexdata_02_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(game_p2_titexdata_02_texs_tex) ==
                  game_p2_titexdata_02_texs_tex_width * game_p2_titexdata_02_texs_tex_height / 2,
              "The dimensions of `game_p2_titexdata_02_texs_tex` does not match the size of the actual texture");

/* titexdata_03 */

extern u8 game_p2_titexdata_03_texs_tex[];

TiTexDataTextures game_p2_titexdata_03_texs = {
    NULL,
    game_p2_titexdata_03_texs_tex,
};

#define game_p2_titexdata_03_texs_tex_width 128
#define game_p2_titexdata_03_texs_tex_height 13

u16 game_p2_titexdata_03_info[] = {
    game_p2_titexdata_03_texs_tex_width,
    game_p2_titexdata_03_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 game_p2_titexdata_03_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_p2/game_p2_titexdata_03_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(game_p2_titexdata_03_texs_tex) ==
                  game_p2_titexdata_03_texs_tex_width * game_p2_titexdata_03_texs_tex_height / 2,
              "The dimensions of `game_p2_titexdata_03_texs_tex` does not match the size of the actual texture");

/* titexdata_04 */

extern u8 game_p2_titexdata_04_texs_tex[];

TiTexDataTextures game_p2_titexdata_04_texs = {
    NULL,
    game_p2_titexdata_04_texs_tex,
};

#define game_p2_titexdata_04_texs_tex_width 144
#define game_p2_titexdata_04_texs_tex_height 13

u16 game_p2_titexdata_04_info[] = {
    game_p2_titexdata_04_texs_tex_width,
    game_p2_titexdata_04_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 game_p2_titexdata_04_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_p2/game_p2_titexdata_04_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(game_p2_titexdata_04_texs_tex) ==
                  game_p2_titexdata_04_texs_tex_width * game_p2_titexdata_04_texs_tex_height / 2,
              "The dimensions of `game_p2_titexdata_04_texs_tex` does not match the size of the actual texture");

/* titexdata_05 */

extern u8 game_p2_titexdata_05_texs_tex[];

TiTexDataTextures game_p2_titexdata_05_texs = {
    NULL,
    game_p2_titexdata_05_texs_tex,
};

#define game_p2_titexdata_05_texs_tex_width 32
#define game_p2_titexdata_05_texs_tex_height 33

u16 game_p2_titexdata_05_info[] = {
    game_p2_titexdata_05_texs_tex_width,
    game_p2_titexdata_05_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 game_p2_titexdata_05_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_p2/game_p2_titexdata_05_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(game_p2_titexdata_05_texs_tex) ==
                  game_p2_titexdata_05_texs_tex_width * game_p2_titexdata_05_texs_tex_height / 2,
              "The dimensions of `game_p2_titexdata_05_texs_tex` does not match the size of the actual texture");

#elif VERSION_CN

/* titexdata_00 */

extern u8 game_p2_titexdata_00_texs_tex[];

TiTexDataTextures game_p2_titexdata_00_texs = {
    NULL,
    game_p2_titexdata_00_texs_tex,
};

#define game_p2_titexdata_00_texs_tex_width 48
#define game_p2_titexdata_00_texs_tex_height 44

u16 game_p2_titexdata_00_info[] = {
    game_p2_titexdata_00_texs_tex_width,
    game_p2_titexdata_00_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 game_p2_titexdata_00_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_p2/game_p2_titexdata_00_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(game_p2_titexdata_00_texs_tex) ==
                  game_p2_titexdata_00_texs_tex_width * game_p2_titexdata_00_texs_tex_height / 2,
              "The dimensions of `game_p2_titexdata_00_texs_tex` does not match the size of the actual texture");

/* titexdata_01 */

extern u8 game_p2_titexdata_01_texs_tex[];

TiTexDataTextures game_p2_titexdata_01_texs = {
    NULL,
    game_p2_titexdata_01_texs_tex,
};

#define game_p2_titexdata_01_texs_tex_width 32
#define game_p2_titexdata_01_texs_tex_height 33

u16 game_p2_titexdata_01_info[] = {
    game_p2_titexdata_01_texs_tex_width,
    game_p2_titexdata_01_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 game_p2_titexdata_01_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_p2/game_p2_titexdata_01_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(game_p2_titexdata_01_texs_tex) ==
                  game_p2_titexdata_01_texs_tex_width * game_p2_titexdata_01_texs_tex_height / 2,
              "The dimensions of `game_p2_titexdata_01_texs_tex` does not match the size of the actual texture");

/* titexdata_02 */

extern u8 game_p2_titexdata_02_texs_tex[];

TiTexDataTextures game_p2_titexdata_02_texs = {
    NULL,
    game_p2_titexdata_02_texs_tex,
};

#define game_p2_titexdata_02_texs_tex_width 128
#define game_p2_titexdata_02_texs_tex_height 33

u16 game_p2_titexdata_02_info[] = {
    game_p2_titexdata_02_texs_tex_width,
    game_p2_titexdata_02_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 game_p2_titexdata_02_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_p2/game_p2_titexdata_02_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(game_p2_titexdata_02_texs_tex) ==
                  game_p2_titexdata_02_texs_tex_width * game_p2_titexdata_02_texs_tex_height / 2,
              "The dimensions of `game_p2_titexdata_02_texs_tex` does not match the size of the actual texture");

/* titexdata_03 */

extern u8 game_p2_titexdata_03_texs_tex[];

TiTexDataTextures game_p2_titexdata_03_texs = {
    NULL,
    game_p2_titexdata_03_texs_tex,
};

#define game_p2_titexdata_03_texs_tex_width 64
#define game_p2_titexdata_03_texs_tex_height 18

u16 game_p2_titexdata_03_info[] = {
    game_p2_titexdata_03_texs_tex_width,
    game_p2_titexdata_03_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 game_p2_titexdata_03_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_p2/game_p2_titexdata_03_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(game_p2_titexdata_03_texs_tex) ==
                  game_p2_titexdata_03_texs_tex_width * game_p2_titexdata_03_texs_tex_height / 2,
              "The dimensions of `game_p2_titexdata_03_texs_tex` does not match the size of the actual texture");

/* titexdata_04 */

extern u8 game_p2_titexdata_04_texs_tex[];

TiTexDataTextures game_p2_titexdata_04_texs = {
    NULL,
    game_p2_titexdata_04_texs_tex,
};

#define game_p2_titexdata_04_texs_tex_width 128
#define game_p2_titexdata_04_texs_tex_height 13

u16 game_p2_titexdata_04_info[] = {
    game_p2_titexdata_04_texs_tex_width,
    game_p2_titexdata_04_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 game_p2_titexdata_04_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_p2/game_p2_titexdata_04_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(game_p2_titexdata_04_texs_tex) ==
                  game_p2_titexdata_04_texs_tex_width * game_p2_titexdata_04_texs_tex_height / 2,
              "The dimensions of `game_p2_titexdata_04_texs_tex` does not match the size of the actual texture");

/* titexdata_05 */

extern u8 game_p2_titexdata_05_texs_tex[];

TiTexDataTextures game_p2_titexdata_05_texs = {
    NULL,
    game_p2_titexdata_05_texs_tex,
};

#define game_p2_titexdata_05_texs_tex_width 144
#define game_p2_titexdata_05_texs_tex_height 13

u16 game_p2_titexdata_05_info[] = {
    game_p2_titexdata_05_texs_tex_width,
    game_p2_titexdata_05_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 game_p2_titexdata_05_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_p2/game_p2_titexdata_05_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(game_p2_titexdata_05_texs_tex) ==
                  game_p2_titexdata_05_texs_tex_width * game_p2_titexdata_05_texs_tex_height / 2,
              "The dimensions of `game_p2_titexdata_05_texs_tex` does not match the size of the actual texture");

#endif

/* titexdata_06 */

extern u8 game_p2_titexdata_06_texs_tex[];

TiTexDataTextures game_p2_titexdata_06_texs = {
    NULL,
    game_p2_titexdata_06_texs_tex,
};

#define game_p2_titexdata_06_texs_tex_width 128
#define game_p2_titexdata_06_texs_tex_height 15

u16 game_p2_titexdata_06_info[] = {
    game_p2_titexdata_06_texs_tex_width,
    game_p2_titexdata_06_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 game_p2_titexdata_06_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_p2/game_p2_titexdata_06_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(game_p2_titexdata_06_texs_tex) ==
                  game_p2_titexdata_06_texs_tex_width * game_p2_titexdata_06_texs_tex_height / 2,
              "The dimensions of `game_p2_titexdata_06_texs_tex` does not match the size of the actual texture");

/* titexdata_07 */

extern u16 game_p2_titexdata_07_texs_tex[];

TiTexDataTextures game_p2_titexdata_07_texs = {
    NULL,
    game_p2_titexdata_07_texs_tex,
};

#define game_p2_titexdata_07_texs_tex_width 64
#define game_p2_titexdata_07_texs_tex_height 18

u16 game_p2_titexdata_07_info[] = {
    game_p2_titexdata_07_texs_tex_width,
    game_p2_titexdata_07_texs_tex_height,
    TITEX_FORMAT_16,
    TITEX_FLAGS_BLOCK,
};

u16 game_p2_titexdata_07_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_p2/game_p2_titexdata_07_texs_tex.rgba16.inc"
};
static_assert(ARRAY_COUNT(game_p2_titexdata_07_texs_tex) ==
                  game_p2_titexdata_07_texs_tex_width * game_p2_titexdata_07_texs_tex_height,
              "The dimensions of `game_p2_titexdata_07_texs_tex` does not match the size of the actual texture");

/* titexdata_08 */

extern u16 game_p2_titexdata_08_texs_tex[];

TiTexDataTextures game_p2_titexdata_08_texs = {
    NULL,
    game_p2_titexdata_08_texs_tex,
};

#define game_p2_titexdata_08_texs_tex_width 128
#define game_p2_titexdata_08_texs_tex_height 33

u16 game_p2_titexdata_08_info[] = {
    game_p2_titexdata_08_texs_tex_width,
    game_p2_titexdata_08_texs_tex_height,
    TITEX_FORMAT_16,
    TITEX_FLAGS_BLOCK,
};

u16 game_p2_titexdata_08_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_p2/game_p2_titexdata_08_texs_tex.rgba16.inc"
};
static_assert(ARRAY_COUNT(game_p2_titexdata_08_texs_tex) ==
                  game_p2_titexdata_08_texs_tex_width * game_p2_titexdata_08_texs_tex_height,
              "The dimensions of `game_p2_titexdata_08_texs_tex` does not match the size of the actual texture");

/* titexdata_09 */

extern u16 game_p2_titexdata_09_texs_tex[];

TiTexDataTextures game_p2_titexdata_09_texs = {
    NULL,
    game_p2_titexdata_09_texs_tex,
};

#define game_p2_titexdata_09_texs_tex_width 48
#define game_p2_titexdata_09_texs_tex_height 44

u16 game_p2_titexdata_09_info[] = {
    game_p2_titexdata_09_texs_tex_width,
    game_p2_titexdata_09_texs_tex_height,
    TITEX_FORMAT_16,
    TITEX_FLAGS_BLOCK,
};

u16 game_p2_titexdata_09_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_p2/game_p2_titexdata_09_texs_tex.rgba16.inc"
};
static_assert(ARRAY_COUNT(game_p2_titexdata_09_texs_tex) ==
                  game_p2_titexdata_09_texs_tex_width * game_p2_titexdata_09_texs_tex_height,
              "The dimensions of `game_p2_titexdata_09_texs_tex` does not match the size of the actual texture");

/* titexdata_10 */

extern u16 game_p2_titexdata_10_texs_tex[];

TiTexDataTextures game_p2_titexdata_10_texs = {
    NULL,
    game_p2_titexdata_10_texs_tex,
};

#define game_p2_titexdata_10_texs_tex_width 128
#define game_p2_titexdata_10_texs_tex_height 13

u16 game_p2_titexdata_10_info[] = {
    game_p2_titexdata_10_texs_tex_width,
    game_p2_titexdata_10_texs_tex_height,
    TITEX_FORMAT_16,
    TITEX_FLAGS_BLOCK,
};

u16 game_p2_titexdata_10_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_p2/game_p2_titexdata_10_texs_tex.rgba16.inc"
};
static_assert(ARRAY_COUNT(game_p2_titexdata_10_texs_tex) ==
                  game_p2_titexdata_10_texs_tex_width * game_p2_titexdata_10_texs_tex_height,
              "The dimensions of `game_p2_titexdata_10_texs_tex` does not match the size of the actual texture");

#if VERSION_US || VERSION_GW

/* titexdata_11 */

extern u16 game_p2_titexdata_11_texs_tex[];

TiTexDataTextures game_p2_titexdata_11_texs = {
    NULL,
    game_p2_titexdata_11_texs_tex,
};

#define game_p2_titexdata_11_texs_tex_width 144
#define game_p2_titexdata_11_texs_tex_height 13

u16 game_p2_titexdata_11_info[] = {
    game_p2_titexdata_11_texs_tex_width,
    game_p2_titexdata_11_texs_tex_height,
    TITEX_FORMAT_16,
    TITEX_FLAGS_BLOCK,
};

u16 game_p2_titexdata_11_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_p2/game_p2_titexdata_11_texs_tex.rgba16.inc"
};
static_assert(ARRAY_COUNT(game_p2_titexdata_11_texs_tex) ==
                  game_p2_titexdata_11_texs_tex_width * game_p2_titexdata_11_texs_tex_height,
              "The dimensions of `game_p2_titexdata_11_texs_tex` does not match the size of the actual texture");

#elif VERSION_CN

/* titexdata_11 */

extern u16 game_p2_titexdata_11_texs_tex[];

TiTexDataTextures game_p2_titexdata_11_texs = {
    NULL,
    game_p2_titexdata_11_texs_tex,
};

#define game_p2_titexdata_11_texs_tex_width 144
#define game_p2_titexdata_11_texs_tex_height 10

u16 game_p2_titexdata_11_info[] = {
    game_p2_titexdata_11_texs_tex_width,
    game_p2_titexdata_11_texs_tex_height,
    TITEX_FORMAT_16,
    TITEX_FLAGS_BLOCK,
};

u16 game_p2_titexdata_11_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_p2/game_p2_titexdata_11_texs_tex.rgba16.inc"
};
static_assert(ARRAY_COUNT(game_p2_titexdata_11_texs_tex) ==
                  game_p2_titexdata_11_texs_tex_width * game_p2_titexdata_11_texs_tex_height,
              "The dimensions of `game_p2_titexdata_11_texs_tex` does not match the size of the actual texture");

#endif

/* titexdata_12 */

extern u16 game_p2_titexdata_12_texs_tex[];

TiTexDataTextures game_p2_titexdata_12_texs = {
    NULL,
    game_p2_titexdata_12_texs_tex,
};

#define game_p2_titexdata_12_texs_tex_width 32
#define game_p2_titexdata_12_texs_tex_height 33

u16 game_p2_titexdata_12_info[] = {
    game_p2_titexdata_12_texs_tex_width,
    game_p2_titexdata_12_texs_tex_height,
    TITEX_FORMAT_16,
    TITEX_FLAGS_BLOCK,
};

u16 game_p2_titexdata_12_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_p2/game_p2_titexdata_12_texs_tex.rgba16.inc"
};
static_assert(ARRAY_COUNT(game_p2_titexdata_12_texs_tex) ==
                  game_p2_titexdata_12_texs_tex_width * game_p2_titexdata_12_texs_tex_height,
              "The dimensions of `game_p2_titexdata_12_texs_tex` does not match the size of the actual texture");

/* titexdata_13 */

extern u16 game_p2_titexdata_13_texs_tex[];

TiTexDataTextures game_p2_titexdata_13_texs = {
    NULL,
    game_p2_titexdata_13_texs_tex,
};

#define game_p2_titexdata_13_texs_tex_width 128
#define game_p2_titexdata_13_texs_tex_height 15

u16 game_p2_titexdata_13_info[] = {
    game_p2_titexdata_13_texs_tex_width,
    game_p2_titexdata_13_texs_tex_height,
    TITEX_FORMAT_16,
    TITEX_FLAGS_BLOCK,
};

u16 game_p2_titexdata_13_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_p2/game_p2_titexdata_13_texs_tex.rgba16.inc"
};
static_assert(ARRAY_COUNT(game_p2_titexdata_13_texs_tex) ==
                  game_p2_titexdata_13_texs_tex_width * game_p2_titexdata_13_texs_tex_height,
              "The dimensions of `game_p2_titexdata_13_texs_tex` does not match the size of the actual texture");

/* titexdata_14 */

extern u16 game_p2_titexdata_14_texs_tex[];

TiTexDataTextures game_p2_titexdata_14_texs = {
    NULL,
    game_p2_titexdata_14_texs_tex,
};

#define game_p2_titexdata_14_texs_tex_width 128
#define game_p2_titexdata_14_texs_tex_height 33

u16 game_p2_titexdata_14_info[] = {
    game_p2_titexdata_14_texs_tex_width,
    game_p2_titexdata_14_texs_tex_height,
    TITEX_FORMAT_16,
    TITEX_FLAGS_BLOCK,
};

u16 game_p2_titexdata_14_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_p2/game_p2_titexdata_14_texs_tex.rgba16.inc"
};
static_assert(ARRAY_COUNT(game_p2_titexdata_14_texs_tex) ==
                  game_p2_titexdata_14_texs_tex_width * game_p2_titexdata_14_texs_tex_height,
              "The dimensions of `game_p2_titexdata_14_texs_tex` does not match the size of the actual texture");

/* titexdata_15 */

extern u16 game_p2_titexdata_15_texs_tex[];

TiTexDataTextures game_p2_titexdata_15_texs = {
    NULL,
    game_p2_titexdata_15_texs_tex,
};

#define game_p2_titexdata_15_texs_tex_width 64
#define game_p2_titexdata_15_texs_tex_height 18

u16 game_p2_titexdata_15_info[] = {
    game_p2_titexdata_15_texs_tex_width,
    game_p2_titexdata_15_texs_tex_height,
    TITEX_FORMAT_16,
    TITEX_FLAGS_BLOCK,
};

u16 game_p2_titexdata_15_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_p2/game_p2_titexdata_15_texs_tex.rgba16.inc"
};
static_assert(ARRAY_COUNT(game_p2_titexdata_15_texs_tex) ==
                  game_p2_titexdata_15_texs_tex_width * game_p2_titexdata_15_texs_tex_height,
              "The dimensions of `game_p2_titexdata_15_texs_tex` does not match the size of the actual texture");

/* titexdata_16 */

extern u16 game_p2_titexdata_16_texs_tex[];

TiTexDataTextures game_p2_titexdata_16_texs = {
    NULL,
    game_p2_titexdata_16_texs_tex,
};

#define game_p2_titexdata_16_texs_tex_width 144
#define game_p2_titexdata_16_texs_tex_height 15

u16 game_p2_titexdata_16_info[] = {
    game_p2_titexdata_16_texs_tex_width,
    game_p2_titexdata_16_texs_tex_height,
    TITEX_FORMAT_16,
    TITEX_FLAGS_BLOCK,
};

u16 game_p2_titexdata_16_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_p2/game_p2_titexdata_16_texs_tex.rgba16.inc"
};
static_assert(ARRAY_COUNT(game_p2_titexdata_16_texs_tex) ==
                  game_p2_titexdata_16_texs_tex_width * game_p2_titexdata_16_texs_tex_height,
              "The dimensions of `game_p2_titexdata_16_texs_tex` does not match the size of the actual texture");

/* titexdata_17 */

extern u8 game_p2_titexdata_17_texs_tex[];

TiTexDataTextures game_p2_titexdata_17_texs = {
    NULL,
    game_p2_titexdata_17_texs_tex,
};

#define game_p2_titexdata_17_texs_tex_width 144
#define game_p2_titexdata_17_texs_tex_height 15

u16 game_p2_titexdata_17_info[] = {
    game_p2_titexdata_17_texs_tex_width,
    game_p2_titexdata_17_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 game_p2_titexdata_17_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_p2/game_p2_titexdata_17_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(game_p2_titexdata_17_texs_tex) ==
                  game_p2_titexdata_17_texs_tex_width * game_p2_titexdata_17_texs_tex_height / 2,
              "The dimensions of `game_p2_titexdata_17_texs_tex` does not match the size of the actual texture");

/* titexdata_18 */

extern u16 game_p2_titexdata_18_texs_tex[];

TiTexDataTextures game_p2_titexdata_18_texs = {
    NULL,
    game_p2_titexdata_18_texs_tex,
};

#define game_p2_titexdata_18_texs_tex_width 128
#define game_p2_titexdata_18_texs_tex_height 56

u16 game_p2_titexdata_18_info[] = {
    game_p2_titexdata_18_texs_tex_width,
    game_p2_titexdata_18_texs_tex_height,
    TITEX_FORMAT_16,
    TITEX_FLAGS_BLOCK,
};

u16 game_p2_titexdata_18_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_p2/game_p2_titexdata_18_texs_tex.rgba16.inc"
};
static_assert(ARRAY_COUNT(game_p2_titexdata_18_texs_tex) ==
                  game_p2_titexdata_18_texs_tex_width * game_p2_titexdata_18_texs_tex_height,
              "The dimensions of `game_p2_titexdata_18_texs_tex` does not match the size of the actual texture");

/* titexdata_19 */

extern u8 game_p2_titexdata_19_texs_tex[];

TiTexDataTextures game_p2_titexdata_19_texs = {
    NULL,
    game_p2_titexdata_19_texs_tex,
};

#define game_p2_titexdata_19_texs_tex_width 128
#define game_p2_titexdata_19_texs_tex_height 56

u16 game_p2_titexdata_19_info[] = {
    game_p2_titexdata_19_texs_tex_width,
    game_p2_titexdata_19_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 game_p2_titexdata_19_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_p2/game_p2_titexdata_19_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(game_p2_titexdata_19_texs_tex) ==
                  game_p2_titexdata_19_texs_tex_width * game_p2_titexdata_19_texs_tex_height / 2,
              "The dimensions of `game_p2_titexdata_19_texs_tex` does not match the size of the actual texture");

/* titexdata_20 */

extern u16 game_p2_titexdata_20_texs_tex[];

TiTexDataTextures game_p2_titexdata_20_texs = {
    NULL,
    game_p2_titexdata_20_texs_tex,
};

#define game_p2_titexdata_20_texs_tex_width 128
#define game_p2_titexdata_20_texs_tex_height 15

u16 game_p2_titexdata_20_info[] = {
    game_p2_titexdata_20_texs_tex_width,
    game_p2_titexdata_20_texs_tex_height,
    TITEX_FORMAT_16,
    TITEX_FLAGS_BLOCK,
};

u16 game_p2_titexdata_20_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_p2/game_p2_titexdata_20_texs_tex.rgba16.inc"
};
static_assert(ARRAY_COUNT(game_p2_titexdata_20_texs_tex) ==
                  game_p2_titexdata_20_texs_tex_width * game_p2_titexdata_20_texs_tex_height,
              "The dimensions of `game_p2_titexdata_20_texs_tex` does not match the size of the actual texture");

/* titexdata_21 */

extern u8 game_p2_titexdata_21_texs_tex[];

TiTexDataTextures game_p2_titexdata_21_texs = {
    NULL,
    game_p2_titexdata_21_texs_tex,
};

#define game_p2_titexdata_21_texs_tex_width 128
#define game_p2_titexdata_21_texs_tex_height 15

u16 game_p2_titexdata_21_info[] = {
    game_p2_titexdata_21_texs_tex_width,
    game_p2_titexdata_21_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 game_p2_titexdata_21_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_p2/game_p2_titexdata_21_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(game_p2_titexdata_21_texs_tex) ==
                  game_p2_titexdata_21_texs_tex_width * game_p2_titexdata_21_texs_tex_height / 2,
              "The dimensions of `game_p2_titexdata_21_texs_tex` does not match the size of the actual texture");

TiTexData game_p2_titexdata[] = {
#if VERSION_US || VERSION_GW
    { &game_p2_titexdata_00_texs, game_p2_titexdata_00_info },
    { &game_p2_titexdata_01_texs, game_p2_titexdata_01_info },
#endif
    { &game_p2_titexdata_02_texs, game_p2_titexdata_02_info },
    { &game_p2_titexdata_03_texs, game_p2_titexdata_03_info },
#if VERSION_CN
    { &game_p2_titexdata_00_texs, game_p2_titexdata_00_info },
#endif
    { &game_p2_titexdata_04_texs, game_p2_titexdata_04_info },
    { &game_p2_titexdata_05_texs, game_p2_titexdata_05_info },
#if VERSION_CN
    { &game_p2_titexdata_01_texs, game_p2_titexdata_01_info },
#endif
    { &game_p2_titexdata_06_texs, game_p2_titexdata_06_info },
    { &game_p2_titexdata_07_texs, game_p2_titexdata_07_info },
    { &game_p2_titexdata_08_texs, game_p2_titexdata_08_info },
    { &game_p2_titexdata_09_texs, game_p2_titexdata_09_info },
    { &game_p2_titexdata_10_texs, game_p2_titexdata_10_info },
    { &game_p2_titexdata_11_texs, game_p2_titexdata_11_info },
    { &game_p2_titexdata_12_texs, game_p2_titexdata_12_info },
    { &game_p2_titexdata_13_texs, game_p2_titexdata_13_info },
    { &game_p2_titexdata_14_texs, game_p2_titexdata_14_info },
    { &game_p2_titexdata_15_texs, game_p2_titexdata_15_info },
    { &game_p2_titexdata_16_texs, game_p2_titexdata_16_info },
    { &game_p2_titexdata_17_texs, game_p2_titexdata_17_info },
    { &game_p2_titexdata_18_texs, game_p2_titexdata_18_info },
    { &game_p2_titexdata_19_texs, game_p2_titexdata_19_info },
    { &game_p2_titexdata_20_texs, game_p2_titexdata_20_info },
    { &game_p2_titexdata_21_texs, game_p2_titexdata_21_info },
};

s32 game_p2_titexdata_len = ARRAY_COUNT(game_p2_titexdata);

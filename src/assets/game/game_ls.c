#include "tex_func.h"

#include "libc/assert.h"
#include "macros_defines.h"
#include "alignment.h"

extern TiTexData game_ls_titexdata[];
extern s32 game_ls_titexdata_len;

TiTexDataHeader game_ls_header = {
    game_ls_titexdata,
    &game_ls_titexdata_len,
};

/* titexdata_00 */

extern u8 game_ls_titexdata_00_texs_tex[];

TiTexDataTextures game_ls_titexdata_00_texs = {
    NULL,
    game_ls_titexdata_00_texs_tex,
};

#define game_ls_titexdata_00_texs_tex_width 48
#define game_ls_titexdata_00_texs_tex_height 48

u16 game_ls_titexdata_00_info[] = {
    game_ls_titexdata_00_texs_tex_width,
    game_ls_titexdata_00_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 game_ls_titexdata_00_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_ls/game_ls_titexdata_00_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(game_ls_titexdata_00_texs_tex) ==
                  game_ls_titexdata_00_texs_tex_width * game_ls_titexdata_00_texs_tex_height / 2,
              "The dimensions of `game_ls_titexdata_00_texs_tex` does not match the size of the actual texture");

#if VERSION_US || VERSION_GW

/* titexdata_01 */

extern u8 game_ls_titexdata_01_texs_tex[];

TiTexDataTextures game_ls_titexdata_01_texs = {
    NULL,
    game_ls_titexdata_01_texs_tex,
};

#define game_ls_titexdata_01_texs_tex_width 96
#define game_ls_titexdata_01_texs_tex_height 108

u16 game_ls_titexdata_01_info[] = {
    game_ls_titexdata_01_texs_tex_width,
    game_ls_titexdata_01_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 game_ls_titexdata_01_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_ls/game_ls_titexdata_01_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(game_ls_titexdata_01_texs_tex) ==
                  game_ls_titexdata_01_texs_tex_width * game_ls_titexdata_01_texs_tex_height / 2,
              "The dimensions of `game_ls_titexdata_01_texs_tex` does not match the size of the actual texture");

/* titexdata_02 */

extern u8 game_ls_titexdata_02_texs_tex[];

TiTexDataTextures game_ls_titexdata_02_texs = {
    NULL,
    game_ls_titexdata_02_texs_tex,
};

#define game_ls_titexdata_02_texs_tex_width 100
#define game_ls_titexdata_02_texs_tex_height 88

u16 game_ls_titexdata_02_info[] = {
    game_ls_titexdata_02_texs_tex_width,
    game_ls_titexdata_02_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_TILE,
};

u8 game_ls_titexdata_02_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_ls/game_ls_titexdata_02_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(game_ls_titexdata_02_texs_tex) ==
                  game_ls_titexdata_02_texs_tex_width * game_ls_titexdata_02_texs_tex_height / 2,
              "The dimensions of `game_ls_titexdata_02_texs_tex` does not match the size of the actual texture");

/* titexdata_03 */

extern u8 game_ls_titexdata_03_texs_tex[];

TiTexDataTextures game_ls_titexdata_03_texs = {
    NULL,
    game_ls_titexdata_03_texs_tex,
};

#define game_ls_titexdata_03_texs_tex_width 48
#define game_ls_titexdata_03_texs_tex_height 48

u16 game_ls_titexdata_03_info[] = {
    game_ls_titexdata_03_texs_tex_width,
    game_ls_titexdata_03_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 game_ls_titexdata_03_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_ls/game_ls_titexdata_03_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(game_ls_titexdata_03_texs_tex) ==
                  game_ls_titexdata_03_texs_tex_width * game_ls_titexdata_03_texs_tex_height / 2,
              "The dimensions of `game_ls_titexdata_03_texs_tex` does not match the size of the actual texture");

#elif VERSION_CN

/* titexdata_01 */

extern u8 game_ls_titexdata_01_texs_tex[];

TiTexDataTextures game_ls_titexdata_01_texs = {
    NULL,
    game_ls_titexdata_01_texs_tex,
};

#define game_ls_titexdata_01_texs_tex_width 48
#define game_ls_titexdata_01_texs_tex_height 48

u16 game_ls_titexdata_01_info[] = {
    game_ls_titexdata_01_texs_tex_width,
    game_ls_titexdata_01_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 game_ls_titexdata_01_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_ls/game_ls_titexdata_01_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(game_ls_titexdata_01_texs_tex) ==
                  game_ls_titexdata_01_texs_tex_width * game_ls_titexdata_01_texs_tex_height / 2,
              "The dimensions of `game_ls_titexdata_01_texs_tex` does not match the size of the actual texture");

/* titexdata_02 */

extern u8 game_ls_titexdata_02_texs_tex[];

TiTexDataTextures game_ls_titexdata_02_texs = {
    NULL,
    game_ls_titexdata_02_texs_tex,
};

#define game_ls_titexdata_02_texs_tex_width 96
#define game_ls_titexdata_02_texs_tex_height 108

u16 game_ls_titexdata_02_info[] = {
    game_ls_titexdata_02_texs_tex_width,
    game_ls_titexdata_02_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 game_ls_titexdata_02_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_ls/game_ls_titexdata_02_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(game_ls_titexdata_02_texs_tex) ==
                  game_ls_titexdata_02_texs_tex_width * game_ls_titexdata_02_texs_tex_height / 2,
              "The dimensions of `game_ls_titexdata_02_texs_tex` does not match the size of the actual texture");

/* titexdata_03 */

extern u8 game_ls_titexdata_03_texs_tex[];

TiTexDataTextures game_ls_titexdata_03_texs = {
    NULL,
    game_ls_titexdata_03_texs_tex,
};

#define game_ls_titexdata_03_texs_tex_width 100
#define game_ls_titexdata_03_texs_tex_height 88

u16 game_ls_titexdata_03_info[] = {
    game_ls_titexdata_03_texs_tex_width,
    game_ls_titexdata_03_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_TILE,
};

u8 game_ls_titexdata_03_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_ls/game_ls_titexdata_03_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(game_ls_titexdata_03_texs_tex) ==
                  game_ls_titexdata_03_texs_tex_width * game_ls_titexdata_03_texs_tex_height / 2,
              "The dimensions of `game_ls_titexdata_03_texs_tex` does not match the size of the actual texture");

#endif

/* titexdata_04 */

extern u8 game_ls_titexdata_04_texs_tex[];

TiTexDataTextures game_ls_titexdata_04_texs = {
    NULL,
    game_ls_titexdata_04_texs_tex,
};

#define game_ls_titexdata_04_texs_tex_width 84
#define game_ls_titexdata_04_texs_tex_height 46

u16 game_ls_titexdata_04_info[] = {
    game_ls_titexdata_04_texs_tex_width,
    game_ls_titexdata_04_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_TILE,
};

u8 game_ls_titexdata_04_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_ls/game_ls_titexdata_04_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(game_ls_titexdata_04_texs_tex) ==
                  game_ls_titexdata_04_texs_tex_width * game_ls_titexdata_04_texs_tex_height / 2,
              "The dimensions of `game_ls_titexdata_04_texs_tex` does not match the size of the actual texture");

u8 game_ls_titexdata_04_14_pad[0x4] = { 0 };

/* titexdata_05 */

extern u16 game_ls_titexdata_05_texs_tex[];

TiTexDataTextures game_ls_titexdata_05_texs = {
    NULL,
    game_ls_titexdata_05_texs_tex,
};

#define game_ls_titexdata_05_texs_tex_width 48
#define game_ls_titexdata_05_texs_tex_height 48

u16 game_ls_titexdata_05_info[] = {
    game_ls_titexdata_05_texs_tex_width,
    game_ls_titexdata_05_texs_tex_height,
    TITEX_FORMAT_16,
    TITEX_FLAGS_BLOCK,
};

u16 game_ls_titexdata_05_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_ls/game_ls_titexdata_05_texs_tex.rgba16.inc"
};
static_assert(ARRAY_COUNT(game_ls_titexdata_05_texs_tex) ==
                  game_ls_titexdata_05_texs_tex_width * game_ls_titexdata_05_texs_tex_height,
              "The dimensions of `game_ls_titexdata_05_texs_tex` does not match the size of the actual texture");

/* titexdata_06 */

extern u16 game_ls_titexdata_06_texs_tex[];

TiTexDataTextures game_ls_titexdata_06_texs = {
    NULL,
    game_ls_titexdata_06_texs_tex,
};

#define game_ls_titexdata_06_texs_tex_width 96
#define game_ls_titexdata_06_texs_tex_height 108

u16 game_ls_titexdata_06_info[] = {
    game_ls_titexdata_06_texs_tex_width,
    game_ls_titexdata_06_texs_tex_height,
    TITEX_FORMAT_16,
    TITEX_FLAGS_TILE,
};

u16 game_ls_titexdata_06_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_ls/game_ls_titexdata_06_texs_tex.rgba16.inc"
};
static_assert(ARRAY_COUNT(game_ls_titexdata_06_texs_tex) ==
                  game_ls_titexdata_06_texs_tex_width * game_ls_titexdata_06_texs_tex_height,
              "The dimensions of `game_ls_titexdata_06_texs_tex` does not match the size of the actual texture");

/* titexdata_07 */

extern u16 game_ls_titexdata_07_texs_tex[];

TiTexDataTextures game_ls_titexdata_07_texs = {
    NULL,
    game_ls_titexdata_07_texs_tex,
};

#define game_ls_titexdata_07_texs_tex_width 96
#define game_ls_titexdata_07_texs_tex_height 108

u16 game_ls_titexdata_07_info[] = {
    game_ls_titexdata_07_texs_tex_width,
    game_ls_titexdata_07_texs_tex_height,
    TITEX_FORMAT_16,
    TITEX_FLAGS_TILE,
};

u16 game_ls_titexdata_07_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_ls/game_ls_titexdata_07_texs_tex.rgba16.inc"
};
static_assert(ARRAY_COUNT(game_ls_titexdata_07_texs_tex) ==
                  game_ls_titexdata_07_texs_tex_width * game_ls_titexdata_07_texs_tex_height,
              "The dimensions of `game_ls_titexdata_07_texs_tex` does not match the size of the actual texture");

/* titexdata_08 */

extern u16 game_ls_titexdata_08_texs_tex[];

TiTexDataTextures game_ls_titexdata_08_texs = {
    NULL,
    game_ls_titexdata_08_texs_tex,
};

#define game_ls_titexdata_08_texs_tex_width 96
#define game_ls_titexdata_08_texs_tex_height 108

u16 game_ls_titexdata_08_info[] = {
    game_ls_titexdata_08_texs_tex_width,
    game_ls_titexdata_08_texs_tex_height,
    TITEX_FORMAT_16,
    TITEX_FLAGS_TILE,
};

u16 game_ls_titexdata_08_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_ls/game_ls_titexdata_08_texs_tex.rgba16.inc"
};
static_assert(ARRAY_COUNT(game_ls_titexdata_08_texs_tex) ==
                  game_ls_titexdata_08_texs_tex_width * game_ls_titexdata_08_texs_tex_height,
              "The dimensions of `game_ls_titexdata_08_texs_tex` does not match the size of the actual texture");

#if VERSION_US || VERSION_GW

/* titexdata_09 */

extern u16 game_ls_titexdata_09_texs_tex[];

TiTexDataTextures game_ls_titexdata_09_texs = {
    NULL,
    game_ls_titexdata_09_texs_tex,
};

#define game_ls_titexdata_09_texs_tex_width 100
#define game_ls_titexdata_09_texs_tex_height 88

u16 game_ls_titexdata_09_info[] = {
    game_ls_titexdata_09_texs_tex_width,
    game_ls_titexdata_09_texs_tex_height,
    TITEX_FORMAT_16,
    TITEX_FLAGS_BLOCK,
};

u16 game_ls_titexdata_09_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_ls/game_ls_titexdata_09_texs_tex.rgba16.inc"
};
static_assert(ARRAY_COUNT(game_ls_titexdata_09_texs_tex) ==
                  game_ls_titexdata_09_texs_tex_width * game_ls_titexdata_09_texs_tex_height,
              "The dimensions of `game_ls_titexdata_09_texs_tex` does not match the size of the actual texture");

/* titexdata_10 */

extern u16 game_ls_titexdata_10_texs_tex[];

TiTexDataTextures game_ls_titexdata_10_texs = {
    NULL,
    game_ls_titexdata_10_texs_tex,
};

#define game_ls_titexdata_10_texs_tex_width 48
#define game_ls_titexdata_10_texs_tex_height 48

u16 game_ls_titexdata_10_info[] = {
    game_ls_titexdata_10_texs_tex_width,
    game_ls_titexdata_10_texs_tex_height,
    TITEX_FORMAT_16,
    TITEX_FLAGS_BLOCK,
};

u16 game_ls_titexdata_10_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_ls/game_ls_titexdata_10_texs_tex.rgba16.inc"
};
static_assert(ARRAY_COUNT(game_ls_titexdata_10_texs_tex) ==
                  game_ls_titexdata_10_texs_tex_width * game_ls_titexdata_10_texs_tex_height,
              "The dimensions of `game_ls_titexdata_10_texs_tex` does not match the size of the actual texture");

/* titexdata_11 */

extern u16 game_ls_titexdata_11_texs_tex[];

TiTexDataTextures game_ls_titexdata_11_texs = {
    NULL,
    game_ls_titexdata_11_texs_tex,
};

#define game_ls_titexdata_11_texs_tex_width 84
#define game_ls_titexdata_11_texs_tex_height 46

u16 game_ls_titexdata_11_info[] = {
    game_ls_titexdata_11_texs_tex_width,
    game_ls_titexdata_11_texs_tex_height,
    TITEX_FORMAT_16,
    TITEX_FLAGS_TILE,
};

u16 game_ls_titexdata_11_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_ls/game_ls_titexdata_11_texs_tex.rgba16.inc"
};
static_assert(ARRAY_COUNT(game_ls_titexdata_11_texs_tex) ==
                  game_ls_titexdata_11_texs_tex_width * game_ls_titexdata_11_texs_tex_height,
              "The dimensions of `game_ls_titexdata_11_texs_tex` does not match the size of the actual texture");

/* titexdata_12 */

extern u16 game_ls_titexdata_12_texs_tex[];

TiTexDataTextures game_ls_titexdata_12_texs = {
    NULL,
    game_ls_titexdata_12_texs_tex,
};

#define game_ls_titexdata_12_texs_tex_width 84
#define game_ls_titexdata_12_texs_tex_height 46

u16 game_ls_titexdata_12_info[] = {
    game_ls_titexdata_12_texs_tex_width,
    game_ls_titexdata_12_texs_tex_height,
    TITEX_FORMAT_16,
    TITEX_FLAGS_TILE,
};

u16 game_ls_titexdata_12_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_ls/game_ls_titexdata_12_texs_tex.rgba16.inc"
};
static_assert(ARRAY_COUNT(game_ls_titexdata_12_texs_tex) ==
                  game_ls_titexdata_12_texs_tex_width * game_ls_titexdata_12_texs_tex_height,
              "The dimensions of `game_ls_titexdata_12_texs_tex` does not match the size of the actual texture");

#elif VERSION_CN

/* titexdata_09 */

extern u16 game_ls_titexdata_09_texs_tex[];

TiTexDataTextures game_ls_titexdata_09_texs = {
    NULL,
    game_ls_titexdata_09_texs_tex,
};

#define game_ls_titexdata_09_texs_tex_width 48
#define game_ls_titexdata_09_texs_tex_height 48

u16 game_ls_titexdata_09_info[] = {
    game_ls_titexdata_09_texs_tex_width,
    game_ls_titexdata_09_texs_tex_height,
    TITEX_FORMAT_16,
    TITEX_FLAGS_BLOCK,
};

u16 game_ls_titexdata_09_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_ls/game_ls_titexdata_09_texs_tex.rgba16.inc"
};
static_assert(ARRAY_COUNT(game_ls_titexdata_09_texs_tex) ==
                  game_ls_titexdata_09_texs_tex_width * game_ls_titexdata_09_texs_tex_height,
              "The dimensions of `game_ls_titexdata_09_texs_tex` does not match the size of the actual texture");

/* titexdata_10 */

extern u16 game_ls_titexdata_10_texs_tex[];

TiTexDataTextures game_ls_titexdata_10_texs = {
    NULL,
    game_ls_titexdata_10_texs_tex,
};

#define game_ls_titexdata_10_texs_tex_width 84
#define game_ls_titexdata_10_texs_tex_height 46

u16 game_ls_titexdata_10_info[] = {
    game_ls_titexdata_10_texs_tex_width,
    game_ls_titexdata_10_texs_tex_height,
    TITEX_FORMAT_16,
    TITEX_FLAGS_TILE,
};

u16 game_ls_titexdata_10_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_ls/game_ls_titexdata_10_texs_tex.rgba16.inc"
};
static_assert(ARRAY_COUNT(game_ls_titexdata_10_texs_tex) ==
                  game_ls_titexdata_10_texs_tex_width * game_ls_titexdata_10_texs_tex_height,
              "The dimensions of `game_ls_titexdata_10_texs_tex` does not match the size of the actual texture");

/* titexdata_11 */

extern u16 game_ls_titexdata_11_texs_tex[];

TiTexDataTextures game_ls_titexdata_11_texs = {
    NULL,
    game_ls_titexdata_11_texs_tex,
};

#define game_ls_titexdata_11_texs_tex_width 84
#define game_ls_titexdata_11_texs_tex_height 46

u16 game_ls_titexdata_11_info[] = {
    game_ls_titexdata_11_texs_tex_width,
    game_ls_titexdata_11_texs_tex_height,
    TITEX_FORMAT_16,
    TITEX_FLAGS_TILE,
};

u16 game_ls_titexdata_11_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_ls/game_ls_titexdata_11_texs_tex.rgba16.inc"
};
static_assert(ARRAY_COUNT(game_ls_titexdata_11_texs_tex) ==
                  game_ls_titexdata_11_texs_tex_width * game_ls_titexdata_11_texs_tex_height,
              "The dimensions of `game_ls_titexdata_11_texs_tex` does not match the size of the actual texture");

/* titexdata_12 */

extern u16 game_ls_titexdata_12_texs_tex[];

TiTexDataTextures game_ls_titexdata_12_texs = {
    NULL,
    game_ls_titexdata_12_texs_tex,
};

#define game_ls_titexdata_12_texs_tex_width 100
#define game_ls_titexdata_12_texs_tex_height 88

u16 game_ls_titexdata_12_info[] = {
    game_ls_titexdata_12_texs_tex_width,
    game_ls_titexdata_12_texs_tex_height,
    TITEX_FORMAT_16,
    TITEX_FLAGS_BLOCK,
};

u16 game_ls_titexdata_12_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_ls/game_ls_titexdata_12_texs_tex.rgba16.inc"
};
static_assert(ARRAY_COUNT(game_ls_titexdata_12_texs_tex) ==
                  game_ls_titexdata_12_texs_tex_width * game_ls_titexdata_12_texs_tex_height,
              "The dimensions of `game_ls_titexdata_12_texs_tex` does not match the size of the actual texture");

#endif

/* titexdata_13 */

extern u16 game_ls_titexdata_13_texs_tex[];

TiTexDataTextures game_ls_titexdata_13_texs = {
    NULL,
    game_ls_titexdata_13_texs_tex,
};

#define game_ls_titexdata_13_texs_tex_width 84
#define game_ls_titexdata_13_texs_tex_height 46

u16 game_ls_titexdata_13_info[] = {
    game_ls_titexdata_13_texs_tex_width,
    game_ls_titexdata_13_texs_tex_height,
    TITEX_FORMAT_16,
    TITEX_FLAGS_TILE,
};

u16 game_ls_titexdata_13_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_ls/game_ls_titexdata_13_texs_tex.rgba16.inc"
};
static_assert(ARRAY_COUNT(game_ls_titexdata_13_texs_tex) ==
                  game_ls_titexdata_13_texs_tex_width * game_ls_titexdata_13_texs_tex_height,
              "The dimensions of `game_ls_titexdata_13_texs_tex` does not match the size of the actual texture");

/* titexdata_14 */

extern u16 game_ls_titexdata_14_texs_tex[];

TiTexDataTextures game_ls_titexdata_14_texs = {
    NULL,
    game_ls_titexdata_14_texs_tex,
};

#define game_ls_titexdata_14_texs_tex_width 84
#define game_ls_titexdata_14_texs_tex_height 46

u16 game_ls_titexdata_14_info[] = {
    game_ls_titexdata_14_texs_tex_width,
    game_ls_titexdata_14_texs_tex_height,
    TITEX_FORMAT_16,
    TITEX_FLAGS_TILE,
};

u16 game_ls_titexdata_14_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_ls/game_ls_titexdata_14_texs_tex.rgba16.inc"
};
static_assert(ARRAY_COUNT(game_ls_titexdata_14_texs_tex) ==
                  game_ls_titexdata_14_texs_tex_width * game_ls_titexdata_14_texs_tex_height,
              "The dimensions of `game_ls_titexdata_14_texs_tex` does not match the size of the actual texture");

/* titexdata_15 */

extern u16 game_ls_titexdata_15_texs_tlut[];
extern u8 game_ls_titexdata_15_texs_tex[];

TiTexDataTextures game_ls_titexdata_15_texs = {
    game_ls_titexdata_15_texs_tlut,
    game_ls_titexdata_15_texs_tex,
};

#define game_ls_titexdata_15_texs_tex_width 80
#define game_ls_titexdata_15_texs_tex_height 120

u16 game_ls_titexdata_15_info[] = {
    game_ls_titexdata_15_texs_tex_width,
    game_ls_titexdata_15_texs_tex_height,
    TITEX_FORMAT_8,
    TITEX_FLAGS_BLOCK,
};

u16 game_ls_titexdata_15_texs_tlut[] ALIGNED(8) = {
#include "assets/game/game_ls/game_ls_titexdata_15_texs_tex.palette.inc"
};
static_assert(ARRAY_COUNT(game_ls_titexdata_15_texs_tlut) == 16 * 16,
              "The dimensions of `game_ls_titexdata_15_texs_tlut` does not match the size of the actual tlut");

u8 game_ls_titexdata_15_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_ls/game_ls_titexdata_15_texs_tex.ci8.inc"
};
static_assert(ARRAY_COUNT(game_ls_titexdata_15_texs_tex) ==
                  game_ls_titexdata_15_texs_tex_width * game_ls_titexdata_15_texs_tex_height,
              "The dimensions of `game_ls_titexdata_15_texs_tex` does not match the size of the actual texture");

/* titexdata_16 */

extern u16 game_ls_titexdata_16_texs_tlut[];
extern u8 game_ls_titexdata_16_texs_tex[];

TiTexDataTextures game_ls_titexdata_16_texs = {
    game_ls_titexdata_16_texs_tlut,
    game_ls_titexdata_16_texs_tex,
};

#define game_ls_titexdata_16_texs_tex_width 80
#define game_ls_titexdata_16_texs_tex_height 120

u16 game_ls_titexdata_16_info[] = {
    game_ls_titexdata_16_texs_tex_width,
    game_ls_titexdata_16_texs_tex_height,
    TITEX_FORMAT_8,
    TITEX_FLAGS_BLOCK,
};

u16 game_ls_titexdata_16_texs_tlut[] ALIGNED(8) = {
#include "assets/game/game_ls/game_ls_titexdata_16_texs_tex.palette.inc"
};
static_assert(ARRAY_COUNT(game_ls_titexdata_16_texs_tlut) == 16 * 16,
              "The dimensions of `game_ls_titexdata_16_texs_tlut` does not match the size of the actual tlut");

u8 game_ls_titexdata_16_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_ls/game_ls_titexdata_16_texs_tex.ci8.inc"
};
static_assert(ARRAY_COUNT(game_ls_titexdata_16_texs_tex) ==
                  game_ls_titexdata_16_texs_tex_width * game_ls_titexdata_16_texs_tex_height,
              "The dimensions of `game_ls_titexdata_16_texs_tex` does not match the size of the actual texture");

/* titexdata_17 */

extern u16 game_ls_titexdata_17_texs_tlut[];
extern u8 game_ls_titexdata_17_texs_tex[];

TiTexDataTextures game_ls_titexdata_17_texs = {
    game_ls_titexdata_17_texs_tlut,
    game_ls_titexdata_17_texs_tex,
};

#define game_ls_titexdata_17_texs_tex_width 80
#define game_ls_titexdata_17_texs_tex_height 120

u16 game_ls_titexdata_17_info[] = {
    game_ls_titexdata_17_texs_tex_width,
    game_ls_titexdata_17_texs_tex_height,
    TITEX_FORMAT_8,
    TITEX_FLAGS_BLOCK,
};

u16 game_ls_titexdata_17_texs_tlut[] ALIGNED(8) = {
#include "assets/game/game_ls/game_ls_titexdata_17_texs_tex.palette.inc"
};
static_assert(ARRAY_COUNT(game_ls_titexdata_17_texs_tlut) == 16 * 16,
              "The dimensions of `game_ls_titexdata_17_texs_tlut` does not match the size of the actual tlut");

u8 game_ls_titexdata_17_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_ls/game_ls_titexdata_17_texs_tex.ci8.inc"
};
static_assert(ARRAY_COUNT(game_ls_titexdata_17_texs_tex) ==
                  game_ls_titexdata_17_texs_tex_width * game_ls_titexdata_17_texs_tex_height,
              "The dimensions of `game_ls_titexdata_17_texs_tex` does not match the size of the actual texture");

/* titexdata_18 */

extern u16 game_ls_titexdata_18_texs_tlut[];
extern u8 game_ls_titexdata_18_texs_tex[];

TiTexDataTextures game_ls_titexdata_18_texs = {
    game_ls_titexdata_18_texs_tlut,
    game_ls_titexdata_18_texs_tex,
};

#define game_ls_titexdata_18_texs_tex_width 120
#define game_ls_titexdata_18_texs_tex_height 120

u16 game_ls_titexdata_18_info[] = {
    game_ls_titexdata_18_texs_tex_width,
    game_ls_titexdata_18_texs_tex_height,
    TITEX_FORMAT_8,
    TITEX_FLAGS_TILE,
};

u16 game_ls_titexdata_18_texs_tlut[] ALIGNED(8) = {
#include "assets/game/game_ls/game_ls_titexdata_18_texs_tex.palette.inc"
};
static_assert(ARRAY_COUNT(game_ls_titexdata_18_texs_tlut) == 16 * 16,
              "The dimensions of `game_ls_titexdata_18_texs_tlut` does not match the size of the actual tlut");

u8 game_ls_titexdata_18_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_ls/game_ls_titexdata_18_texs_tex.ci8.inc"
};
static_assert(ARRAY_COUNT(game_ls_titexdata_18_texs_tex) ==
                  game_ls_titexdata_18_texs_tex_width * game_ls_titexdata_18_texs_tex_height,
              "The dimensions of `game_ls_titexdata_18_texs_tex` does not match the size of the actual texture");

/* titexdata_19 */

extern u16 game_ls_titexdata_19_texs_tlut[];
extern u8 game_ls_titexdata_19_texs_tex[];

TiTexDataTextures game_ls_titexdata_19_texs = {
    game_ls_titexdata_19_texs_tlut,
    game_ls_titexdata_19_texs_tex,
};

#define game_ls_titexdata_19_texs_tex_width 120
#define game_ls_titexdata_19_texs_tex_height 120

u16 game_ls_titexdata_19_info[] = {
    game_ls_titexdata_19_texs_tex_width,
    game_ls_titexdata_19_texs_tex_height,
    TITEX_FORMAT_8,
    TITEX_FLAGS_TILE,
};

u16 game_ls_titexdata_19_texs_tlut[] ALIGNED(8) = {
#include "assets/game/game_ls/game_ls_titexdata_19_texs_tex.palette.inc"
};
static_assert(ARRAY_COUNT(game_ls_titexdata_19_texs_tlut) == 16 * 16,
              "The dimensions of `game_ls_titexdata_19_texs_tlut` does not match the size of the actual tlut");

u8 game_ls_titexdata_19_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_ls/game_ls_titexdata_19_texs_tex.ci8.inc"
};
static_assert(ARRAY_COUNT(game_ls_titexdata_19_texs_tex) ==
                  game_ls_titexdata_19_texs_tex_width * game_ls_titexdata_19_texs_tex_height,
              "The dimensions of `game_ls_titexdata_19_texs_tex` does not match the size of the actual texture");

/* titexdata_20 */

extern u16 game_ls_titexdata_20_texs_tlut[];
extern u8 game_ls_titexdata_20_texs_tex[];

TiTexDataTextures game_ls_titexdata_20_texs = {
    game_ls_titexdata_20_texs_tlut,
    game_ls_titexdata_20_texs_tex,
};

#define game_ls_titexdata_20_texs_tex_width 120
#define game_ls_titexdata_20_texs_tex_height 120

u16 game_ls_titexdata_20_info[] = {
    game_ls_titexdata_20_texs_tex_width,
    game_ls_titexdata_20_texs_tex_height,
    TITEX_FORMAT_8,
    TITEX_FLAGS_TILE,
};

u16 game_ls_titexdata_20_texs_tlut[] ALIGNED(8) = {
#include "assets/game/game_ls/game_ls_titexdata_20_texs_tex.palette.inc"
};
static_assert(ARRAY_COUNT(game_ls_titexdata_20_texs_tlut) == 16 * 16,
              "The dimensions of `game_ls_titexdata_20_texs_tlut` does not match the size of the actual tlut");

u8 game_ls_titexdata_20_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_ls/game_ls_titexdata_20_texs_tex.ci8.inc"
};
static_assert(ARRAY_COUNT(game_ls_titexdata_20_texs_tex) ==
                  game_ls_titexdata_20_texs_tex_width * game_ls_titexdata_20_texs_tex_height,
              "The dimensions of `game_ls_titexdata_20_texs_tex` does not match the size of the actual texture");

/* titexdata_21 */

extern u16 game_ls_titexdata_21_texs_tlut[];
extern u8 game_ls_titexdata_21_texs_tex[];

TiTexDataTextures game_ls_titexdata_21_texs = {
    game_ls_titexdata_21_texs_tlut,
    game_ls_titexdata_21_texs_tex,
};

#define game_ls_titexdata_21_texs_tex_width 64
#define game_ls_titexdata_21_texs_tex_height 16

u16 game_ls_titexdata_21_info[] = {
    game_ls_titexdata_21_texs_tex_width,
    game_ls_titexdata_21_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u16 game_ls_titexdata_21_texs_tlut[] ALIGNED(8) = {
#include "assets/game/game_ls/game_ls_titexdata_21_texs_tex.palette.inc"
};
static_assert(ARRAY_COUNT(game_ls_titexdata_21_texs_tlut) == 4 * 4,
              "The dimensions of `game_ls_titexdata_21_texs_tlut` does not match the size of the actual tlut");

u8 game_ls_titexdata_21_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_ls/game_ls_titexdata_21_texs_tex.ci4.inc"
};
static_assert(ARRAY_COUNT(game_ls_titexdata_21_texs_tex) ==
                  game_ls_titexdata_21_texs_tex_width * game_ls_titexdata_21_texs_tex_height / 2,
              "The dimensions of `game_ls_titexdata_21_texs_tex` does not match the size of the actual texture");

TiTexData game_ls_titexdata[] = {
    { &game_ls_titexdata_00_texs, game_ls_titexdata_00_info },
#if VERSION_US || VERSION_GW
    { &game_ls_titexdata_01_texs, game_ls_titexdata_01_info },
#endif
    { &game_ls_titexdata_02_texs, game_ls_titexdata_02_info },
    { &game_ls_titexdata_03_texs, game_ls_titexdata_03_info },
#if VERSION_CN
    { &game_ls_titexdata_01_texs, game_ls_titexdata_01_info },
#endif
    { &game_ls_titexdata_04_texs, game_ls_titexdata_04_info },
    { &game_ls_titexdata_05_texs, game_ls_titexdata_05_info },
    { &game_ls_titexdata_06_texs, game_ls_titexdata_06_info },
    { &game_ls_titexdata_07_texs, game_ls_titexdata_07_info },
    { &game_ls_titexdata_08_texs, game_ls_titexdata_08_info },
#if VERSION_CN
    { &game_ls_titexdata_12_texs, game_ls_titexdata_12_info },
#endif
    { &game_ls_titexdata_09_texs, game_ls_titexdata_09_info },
    { &game_ls_titexdata_10_texs, game_ls_titexdata_10_info },
    { &game_ls_titexdata_11_texs, game_ls_titexdata_11_info },
#if VERSION_US || VERSION_GW
    { &game_ls_titexdata_12_texs, game_ls_titexdata_12_info },
#endif
    { &game_ls_titexdata_13_texs, game_ls_titexdata_13_info },
    { &game_ls_titexdata_14_texs, game_ls_titexdata_14_info },
    { &game_ls_titexdata_15_texs, game_ls_titexdata_15_info },
    { &game_ls_titexdata_16_texs, game_ls_titexdata_16_info },
    { &game_ls_titexdata_17_texs, game_ls_titexdata_17_info },
    { &game_ls_titexdata_18_texs, game_ls_titexdata_18_info },
    { &game_ls_titexdata_19_texs, game_ls_titexdata_19_info },
    { &game_ls_titexdata_20_texs, game_ls_titexdata_20_info },
    { &game_ls_titexdata_21_texs, game_ls_titexdata_21_info },
};

s32 game_ls_titexdata_len = ARRAY_COUNT(game_ls_titexdata);

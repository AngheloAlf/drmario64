#include "tex_func.h"

#include "libc/assert.h"
#include "macros_defines.h"
#include "alignment.h"

extern TiTexData game_p4_titexdata[];
extern s32 game_p4_titexdata_len;

TiTexDataHeader game_p4_header = {
    game_p4_titexdata,
    &game_p4_titexdata_len,
};

/* titexdata_00 */

extern u16 game_p4_titexdata_00_texs_tlut[];
extern u8 game_p4_titexdata_00_texs_tex[];

TiTexDataTextures game_p4_titexdata_00_texs = {
    game_p4_titexdata_00_texs_tlut,
    game_p4_titexdata_00_texs_tex,
};

#define game_p4_titexdata_00_texs_tex_width 80
#define game_p4_titexdata_00_texs_tex_height 149

u16 game_p4_titexdata_00_info[] = {
    game_p4_titexdata_00_texs_tex_width,
    game_p4_titexdata_00_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u16 game_p4_titexdata_00_texs_tlut[] ALIGNED(8) = {
#include "assets/game/game_p4/game_p4_titexdata_00_texs_tex.palette.inc"
};
static_assert(ARRAY_COUNT(game_p4_titexdata_00_texs_tlut) == 4 * 4,
              "The dimensions of `game_p4_titexdata_00_texs_tlut` does not match the size of the actual tlut");

u8 game_p4_titexdata_00_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_p4/game_p4_titexdata_00_texs_tex.ci4.inc"
};
static_assert(ARRAY_COUNT(game_p4_titexdata_00_texs_tex) ==
                  game_p4_titexdata_00_texs_tex_width * game_p4_titexdata_00_texs_tex_height / 2,
              "The dimensions of `game_p4_titexdata_00_texs_tex` does not match the size of the actual texture");

/* titexdata_01 */

extern u16 game_p4_titexdata_01_texs_tlut[];
extern u8 game_p4_titexdata_01_texs_tex[];

TiTexDataTextures game_p4_titexdata_01_texs = {
    game_p4_titexdata_01_texs_tlut,
    game_p4_titexdata_01_texs_tex,
};

#define game_p4_titexdata_01_texs_tex_width 64
#define game_p4_titexdata_01_texs_tex_height 142

u16 game_p4_titexdata_01_info[] = {
    game_p4_titexdata_01_texs_tex_width,
    game_p4_titexdata_01_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u16 game_p4_titexdata_01_texs_tlut[] ALIGNED(8) = {
#include "assets/game/game_p4/game_p4_titexdata_01_texs_tex.palette.inc"
};
static_assert(ARRAY_COUNT(game_p4_titexdata_01_texs_tlut) == 4 * 4,
              "The dimensions of `game_p4_titexdata_01_texs_tlut` does not match the size of the actual tlut");

u8 game_p4_titexdata_01_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_p4/game_p4_titexdata_01_texs_tex.ci4.inc"
};
static_assert(ARRAY_COUNT(game_p4_titexdata_01_texs_tex) ==
                  game_p4_titexdata_01_texs_tex_width * game_p4_titexdata_01_texs_tex_height / 2,
              "The dimensions of `game_p4_titexdata_01_texs_tex` does not match the size of the actual texture");

/* titexdata_02 */

extern u16 game_p4_titexdata_02_texs_tlut[];
extern u8 game_p4_titexdata_02_texs_tex[];

TiTexDataTextures game_p4_titexdata_02_texs = {
    game_p4_titexdata_02_texs_tlut,
    game_p4_titexdata_02_texs_tex,
};

#define game_p4_titexdata_02_texs_tex_width 304
#define game_p4_titexdata_02_texs_tex_height 30

u16 game_p4_titexdata_02_info[] = {
    game_p4_titexdata_02_texs_tex_width,
    game_p4_titexdata_02_texs_tex_height,
    TITEX_FORMAT_8,
    TITEX_FLAGS_BLOCK,
};

u16 game_p4_titexdata_02_texs_tlut[] ALIGNED(8) = {
#include "assets/game/game_p4/game_p4_titexdata_02_texs_tex.palette.inc"
};
static_assert(ARRAY_COUNT(game_p4_titexdata_02_texs_tlut) == 16 * 16,
              "The dimensions of `game_p4_titexdata_02_texs_tlut` does not match the size of the actual tlut");

u8 game_p4_titexdata_02_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_p4/game_p4_titexdata_02_texs_tex.ci8.inc"
};
static_assert(ARRAY_COUNT(game_p4_titexdata_02_texs_tex) ==
                  game_p4_titexdata_02_texs_tex_width * game_p4_titexdata_02_texs_tex_height,
              "The dimensions of `game_p4_titexdata_02_texs_tex` does not match the size of the actual texture");

/* titexdata_03 */

extern u16 game_p4_titexdata_03_texs_tlut[];
extern u8 game_p4_titexdata_03_texs_tex[];

TiTexDataTextures game_p4_titexdata_03_texs = {
    game_p4_titexdata_03_texs_tlut,
    game_p4_titexdata_03_texs_tex,
};

#define game_p4_titexdata_03_texs_tex_width 304
#define game_p4_titexdata_03_texs_tex_height 30

u16 game_p4_titexdata_03_info[] = {
    game_p4_titexdata_03_texs_tex_width,
    game_p4_titexdata_03_texs_tex_height,
    TITEX_FORMAT_8,
    TITEX_FLAGS_BLOCK,
};

u16 game_p4_titexdata_03_texs_tlut[] ALIGNED(8) = {
#include "assets/game/game_p4/game_p4_titexdata_03_texs_tex.palette.inc"
};
static_assert(ARRAY_COUNT(game_p4_titexdata_03_texs_tlut) == 16 * 16,
              "The dimensions of `game_p4_titexdata_03_texs_tlut` does not match the size of the actual tlut");

u8 game_p4_titexdata_03_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_p4/game_p4_titexdata_03_texs_tex.ci8.inc"
};
static_assert(ARRAY_COUNT(game_p4_titexdata_03_texs_tex) ==
                  game_p4_titexdata_03_texs_tex_width * game_p4_titexdata_03_texs_tex_height,
              "The dimensions of `game_p4_titexdata_03_texs_tex` does not match the size of the actual texture");

/* titexdata_04 */

extern u16 game_p4_titexdata_04_texs_tlut[];
extern u8 game_p4_titexdata_04_texs_tex[];

TiTexDataTextures game_p4_titexdata_04_texs = {
    game_p4_titexdata_04_texs_tlut,
    game_p4_titexdata_04_texs_tex,
};

#define game_p4_titexdata_04_texs_tex_width 304
#define game_p4_titexdata_04_texs_tex_height 30

u16 game_p4_titexdata_04_info[] = {
    game_p4_titexdata_04_texs_tex_width,
    game_p4_titexdata_04_texs_tex_height,
    TITEX_FORMAT_8,
    TITEX_FLAGS_BLOCK,
};

u16 game_p4_titexdata_04_texs_tlut[] ALIGNED(8) = {
#include "assets/game/game_p4/game_p4_titexdata_04_texs_tex.palette.inc"
};
static_assert(ARRAY_COUNT(game_p4_titexdata_04_texs_tlut) == 16 * 16,
              "The dimensions of `game_p4_titexdata_04_texs_tlut` does not match the size of the actual tlut");

u8 game_p4_titexdata_04_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_p4/game_p4_titexdata_04_texs_tex.ci8.inc"
};
static_assert(ARRAY_COUNT(game_p4_titexdata_04_texs_tex) ==
                  game_p4_titexdata_04_texs_tex_width * game_p4_titexdata_04_texs_tex_height,
              "The dimensions of `game_p4_titexdata_04_texs_tex` does not match the size of the actual texture");

/* titexdata_05 */

extern u16 game_p4_titexdata_05_texs_tlut[];
extern u8 game_p4_titexdata_05_texs_tex[];

TiTexDataTextures game_p4_titexdata_05_texs = {
    game_p4_titexdata_05_texs_tlut,
    game_p4_titexdata_05_texs_tex,
};

#define game_p4_titexdata_05_texs_tex_width 288
#define game_p4_titexdata_05_texs_tex_height 24

u16 game_p4_titexdata_05_info[] = {
    game_p4_titexdata_05_texs_tex_width,
    game_p4_titexdata_05_texs_tex_height,
    TITEX_FORMAT_8,
    TITEX_FLAGS_BLOCK,
};

u16 game_p4_titexdata_05_texs_tlut[] ALIGNED(8) = {
#include "assets/game/game_p4/game_p4_titexdata_05_texs_tex.palette.inc"
};
static_assert(ARRAY_COUNT(game_p4_titexdata_05_texs_tlut) == 16 * 16,
              "The dimensions of `game_p4_titexdata_05_texs_tlut` does not match the size of the actual tlut");

u8 game_p4_titexdata_05_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_p4/game_p4_titexdata_05_texs_tex.ci8.inc"
};
static_assert(ARRAY_COUNT(game_p4_titexdata_05_texs_tex) ==
                  game_p4_titexdata_05_texs_tex_width * game_p4_titexdata_05_texs_tex_height,
              "The dimensions of `game_p4_titexdata_05_texs_tex` does not match the size of the actual texture");

/* titexdata_06 */

extern u16 game_p4_titexdata_06_texs_tlut[];
extern u8 game_p4_titexdata_06_texs_tex[];

TiTexDataTextures game_p4_titexdata_06_texs = {
    game_p4_titexdata_06_texs_tlut,
    game_p4_titexdata_06_texs_tex,
};

#define game_p4_titexdata_06_texs_tex_width 288
#define game_p4_titexdata_06_texs_tex_height 24

u16 game_p4_titexdata_06_info[] = {
    game_p4_titexdata_06_texs_tex_width,
    game_p4_titexdata_06_texs_tex_height,
    TITEX_FORMAT_8,
    TITEX_FLAGS_BLOCK,
};

u16 game_p4_titexdata_06_texs_tlut[] ALIGNED(8) = {
#include "assets/game/game_p4/game_p4_titexdata_06_texs_tex.palette.inc"
};
static_assert(ARRAY_COUNT(game_p4_titexdata_06_texs_tlut) == 16 * 16,
              "The dimensions of `game_p4_titexdata_06_texs_tlut` does not match the size of the actual tlut");

u8 game_p4_titexdata_06_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_p4/game_p4_titexdata_06_texs_tex.ci8.inc"
};
static_assert(ARRAY_COUNT(game_p4_titexdata_06_texs_tex) ==
                  game_p4_titexdata_06_texs_tex_width * game_p4_titexdata_06_texs_tex_height,
              "The dimensions of `game_p4_titexdata_06_texs_tex` does not match the size of the actual texture");

/* titexdata_07 */

extern u16 game_p4_titexdata_07_texs_tlut[];
extern u8 game_p4_titexdata_07_texs_tex[];

TiTexDataTextures game_p4_titexdata_07_texs = {
    game_p4_titexdata_07_texs_tlut,
    game_p4_titexdata_07_texs_tex,
};

#define game_p4_titexdata_07_texs_tex_width 288
#define game_p4_titexdata_07_texs_tex_height 24

u16 game_p4_titexdata_07_info[] = {
    game_p4_titexdata_07_texs_tex_width,
    game_p4_titexdata_07_texs_tex_height,
    TITEX_FORMAT_8,
    TITEX_FLAGS_BLOCK,
};

u16 game_p4_titexdata_07_texs_tlut[] ALIGNED(8) = {
#include "assets/game/game_p4/game_p4_titexdata_07_texs_tex.palette.inc"
};
static_assert(ARRAY_COUNT(game_p4_titexdata_07_texs_tlut) == 16 * 16,
              "The dimensions of `game_p4_titexdata_07_texs_tlut` does not match the size of the actual tlut");

u8 game_p4_titexdata_07_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_p4/game_p4_titexdata_07_texs_tex.ci8.inc"
};
static_assert(ARRAY_COUNT(game_p4_titexdata_07_texs_tex) ==
                  game_p4_titexdata_07_texs_tex_width * game_p4_titexdata_07_texs_tex_height,
              "The dimensions of `game_p4_titexdata_07_texs_tex` does not match the size of the actual texture");

/* titexdata_08 */

extern u16 game_p4_titexdata_08_texs_tlut[];
extern u8 game_p4_titexdata_08_texs_tex[];

TiTexDataTextures game_p4_titexdata_08_texs = {
    game_p4_titexdata_08_texs_tlut,
    game_p4_titexdata_08_texs_tex,
};

#define game_p4_titexdata_08_texs_tex_width 72
#define game_p4_titexdata_08_texs_tex_height 48

u16 game_p4_titexdata_08_info[] = {
    game_p4_titexdata_08_texs_tex_width,
    game_p4_titexdata_08_texs_tex_height,
    TITEX_FORMAT_8,
    TITEX_FLAGS_BLOCK,
};

u16 game_p4_titexdata_08_texs_tlut[] ALIGNED(8) = {
#include "assets/game/game_p4/game_p4_titexdata_08_texs_tex.palette.inc"
};
static_assert(ARRAY_COUNT(game_p4_titexdata_08_texs_tlut) == 16 * 16,
              "The dimensions of `game_p4_titexdata_08_texs_tlut` does not match the size of the actual tlut");

u8 game_p4_titexdata_08_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_p4/game_p4_titexdata_08_texs_tex.ci8.inc"
};
static_assert(ARRAY_COUNT(game_p4_titexdata_08_texs_tex) ==
                  game_p4_titexdata_08_texs_tex_width * game_p4_titexdata_08_texs_tex_height,
              "The dimensions of `game_p4_titexdata_08_texs_tex` does not match the size of the actual texture");

/* titexdata_09 */

extern u16 game_p4_titexdata_09_texs_tlut[];
extern u8 game_p4_titexdata_09_texs_tex[];

TiTexDataTextures game_p4_titexdata_09_texs = {
    game_p4_titexdata_09_texs_tlut,
    game_p4_titexdata_09_texs_tex,
};

#define game_p4_titexdata_09_texs_tex_width 64
#define game_p4_titexdata_09_texs_tex_height 192

u16 game_p4_titexdata_09_info[] = {
    game_p4_titexdata_09_texs_tex_width,
    game_p4_titexdata_09_texs_tex_height,
    TITEX_FORMAT_8,
    TITEX_FLAGS_BLOCK,
};

u16 game_p4_titexdata_09_texs_tlut[] ALIGNED(8) = {
#include "assets/game/game_p4/game_p4_titexdata_09_texs_tex.palette.inc"
};
static_assert(ARRAY_COUNT(game_p4_titexdata_09_texs_tlut) == 16 * 16,
              "The dimensions of `game_p4_titexdata_09_texs_tlut` does not match the size of the actual tlut");

u8 game_p4_titexdata_09_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_p4/game_p4_titexdata_09_texs_tex.ci8.inc"
};
static_assert(ARRAY_COUNT(game_p4_titexdata_09_texs_tex) ==
                  game_p4_titexdata_09_texs_tex_width * game_p4_titexdata_09_texs_tex_height,
              "The dimensions of `game_p4_titexdata_09_texs_tex` does not match the size of the actual texture");

#if VERSION_US || VERSION_GW

/* titexdata_10 */

extern u16 game_p4_titexdata_10_texs_tex[];

TiTexDataTextures game_p4_titexdata_10_texs = {
    NULL,
    game_p4_titexdata_10_texs_tex,
};

#define game_p4_titexdata_10_texs_tex_width 32
#define game_p4_titexdata_10_texs_tex_height 132

u16 game_p4_titexdata_10_info[] = {
    game_p4_titexdata_10_texs_tex_width,
    game_p4_titexdata_10_texs_tex_height,
    TITEX_FORMAT_16,
    TITEX_FLAGS_BLOCK,
};

u16 game_p4_titexdata_10_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_p4/game_p4_titexdata_10_texs_tex.rgba16.inc"
};
static_assert(ARRAY_COUNT(game_p4_titexdata_10_texs_tex) ==
                  game_p4_titexdata_10_texs_tex_width * game_p4_titexdata_10_texs_tex_height,
              "The dimensions of `game_p4_titexdata_10_texs_tex` does not match the size of the actual texture");

/* titexdata_11 */

extern u16 game_p4_titexdata_11_texs_tex[];

TiTexDataTextures game_p4_titexdata_11_texs = {
    NULL,
    game_p4_titexdata_11_texs_tex,
};

#define game_p4_titexdata_11_texs_tex_width 48
#define game_p4_titexdata_11_texs_tex_height 16

u16 game_p4_titexdata_11_info[] = {
    game_p4_titexdata_11_texs_tex_width,
    game_p4_titexdata_11_texs_tex_height,
    TITEX_FORMAT_16,
    TITEX_FLAGS_BLOCK,
};

u16 game_p4_titexdata_11_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_p4/game_p4_titexdata_11_texs_tex.rgba16.inc"
};
static_assert(ARRAY_COUNT(game_p4_titexdata_11_texs_tex) ==
                  game_p4_titexdata_11_texs_tex_width * game_p4_titexdata_11_texs_tex_height,
              "The dimensions of `game_p4_titexdata_11_texs_tex` does not match the size of the actual texture");

/* titexdata_12 */

extern u16 game_p4_titexdata_12_texs_tex[];

TiTexDataTextures game_p4_titexdata_12_texs = {
    NULL,
    game_p4_titexdata_12_texs_tex,
};

#define game_p4_titexdata_12_texs_tex_width 48
#define game_p4_titexdata_12_texs_tex_height 16

u16 game_p4_titexdata_12_info[] = {
    game_p4_titexdata_12_texs_tex_width,
    game_p4_titexdata_12_texs_tex_height,
    TITEX_FORMAT_16,
    TITEX_FLAGS_BLOCK,
};

u16 game_p4_titexdata_12_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_p4/game_p4_titexdata_12_texs_tex.rgba16.inc"
};
static_assert(ARRAY_COUNT(game_p4_titexdata_12_texs_tex) ==
                  game_p4_titexdata_12_texs_tex_width * game_p4_titexdata_12_texs_tex_height,
              "The dimensions of `game_p4_titexdata_12_texs_tex` does not match the size of the actual texture");

#elif VERSION_CN

/* titexdata_10 */

extern u16 game_p4_titexdata_10_texs_tex[];

TiTexDataTextures game_p4_titexdata_10_texs = {
    NULL,
    game_p4_titexdata_10_texs_tex,
};

#define game_p4_titexdata_10_texs_tex_width 16
#define game_p4_titexdata_10_texs_tex_height 24

u16 game_p4_titexdata_10_info[] = {
    game_p4_titexdata_10_texs_tex_width,
    game_p4_titexdata_10_texs_tex_height,
    TITEX_FORMAT_16,
    TITEX_FLAGS_BLOCK,
};

u16 game_p4_titexdata_10_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_p4/game_p4_titexdata_10_texs_tex.rgba16.inc"
};
static_assert(ARRAY_COUNT(game_p4_titexdata_10_texs_tex) ==
                  game_p4_titexdata_10_texs_tex_width * game_p4_titexdata_10_texs_tex_height,
              "The dimensions of `game_p4_titexdata_10_texs_tex` does not match the size of the actual texture");

/* titexdata_11 */

extern u8 game_p4_titexdata_11_texs_tex[];

TiTexDataTextures game_p4_titexdata_11_texs = {
    NULL,
    game_p4_titexdata_11_texs_tex,
};

#define game_p4_titexdata_11_texs_tex_width 16
#define game_p4_titexdata_11_texs_tex_height 24

u16 game_p4_titexdata_11_info[] = {
    game_p4_titexdata_11_texs_tex_width,
    game_p4_titexdata_11_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 game_p4_titexdata_11_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_p4/game_p4_titexdata_11_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(game_p4_titexdata_11_texs_tex) ==
                  game_p4_titexdata_11_texs_tex_width * game_p4_titexdata_11_texs_tex_height / 2,
              "The dimensions of `game_p4_titexdata_11_texs_tex` does not match the size of the actual texture");

/* titexdata_12 */

extern u16 game_p4_titexdata_12_texs_tex[];

TiTexDataTextures game_p4_titexdata_12_texs = {
    NULL,
    game_p4_titexdata_12_texs_tex,
};

#define game_p4_titexdata_12_texs_tex_width 32
#define game_p4_titexdata_12_texs_tex_height 132

u16 game_p4_titexdata_12_info[] = {
    game_p4_titexdata_12_texs_tex_width,
    game_p4_titexdata_12_texs_tex_height,
    TITEX_FORMAT_16,
    TITEX_FLAGS_BLOCK,
};

u16 game_p4_titexdata_12_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_p4/game_p4_titexdata_12_texs_tex.rgba16.inc"
};
static_assert(ARRAY_COUNT(game_p4_titexdata_12_texs_tex) ==
                  game_p4_titexdata_12_texs_tex_width * game_p4_titexdata_12_texs_tex_height,
              "The dimensions of `game_p4_titexdata_12_texs_tex` does not match the size of the actual texture");

#endif

/* titexdata_13 */

extern u16 game_p4_titexdata_13_texs_tex[];

TiTexDataTextures game_p4_titexdata_13_texs = {
    NULL,
    game_p4_titexdata_13_texs_tex,
};

#define game_p4_titexdata_13_texs_tex_width 48
#define game_p4_titexdata_13_texs_tex_height 16

u16 game_p4_titexdata_13_info[] = {
    game_p4_titexdata_13_texs_tex_width,
    game_p4_titexdata_13_texs_tex_height,
    TITEX_FORMAT_16,
    TITEX_FLAGS_BLOCK,
};

u16 game_p4_titexdata_13_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_p4/game_p4_titexdata_13_texs_tex.rgba16.inc"
};
static_assert(ARRAY_COUNT(game_p4_titexdata_13_texs_tex) ==
                  game_p4_titexdata_13_texs_tex_width * game_p4_titexdata_13_texs_tex_height,
              "The dimensions of `game_p4_titexdata_13_texs_tex` does not match the size of the actual texture");

#if VERSION_US || VERSION_GW

/* titexdata_14 */

extern u16 game_p4_titexdata_14_texs_tex[];

TiTexDataTextures game_p4_titexdata_14_texs = {
    NULL,
    game_p4_titexdata_14_texs_tex,
};

#define game_p4_titexdata_14_texs_tex_width 16
#define game_p4_titexdata_14_texs_tex_height 24

u16 game_p4_titexdata_14_info[] = {
    game_p4_titexdata_14_texs_tex_width,
    game_p4_titexdata_14_texs_tex_height,
    TITEX_FORMAT_16,
    TITEX_FLAGS_BLOCK,
};

u16 game_p4_titexdata_14_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_p4/game_p4_titexdata_14_texs_tex.rgba16.inc"
};
static_assert(ARRAY_COUNT(game_p4_titexdata_14_texs_tex) ==
                  game_p4_titexdata_14_texs_tex_width * game_p4_titexdata_14_texs_tex_height,
              "The dimensions of `game_p4_titexdata_14_texs_tex` does not match the size of the actual texture");

/* titexdata_15 */

extern u16 game_p4_titexdata_15_texs_tex[];

TiTexDataTextures game_p4_titexdata_15_texs = {
    NULL,
    game_p4_titexdata_15_texs_tex,
};

#define game_p4_titexdata_15_texs_tex_width 304
#define game_p4_titexdata_15_texs_tex_height 26

u16 game_p4_titexdata_15_info[] = {
    game_p4_titexdata_15_texs_tex_width,
    game_p4_titexdata_15_texs_tex_height,
    TITEX_FORMAT_16,
    TITEX_FLAGS_BLOCK,
};

u16 game_p4_titexdata_15_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_p4/game_p4_titexdata_15_texs_tex.rgba16.inc"
};
static_assert(ARRAY_COUNT(game_p4_titexdata_15_texs_tex) ==
                  game_p4_titexdata_15_texs_tex_width * game_p4_titexdata_15_texs_tex_height,
              "The dimensions of `game_p4_titexdata_15_texs_tex` does not match the size of the actual texture");

/* titexdata_16 */

extern u16 game_p4_titexdata_16_texs_tex[];

TiTexDataTextures game_p4_titexdata_16_texs = {
    NULL,
    game_p4_titexdata_16_texs_tex,
};

#define game_p4_titexdata_16_texs_tex_width 32
#define game_p4_titexdata_16_texs_tex_height 12

u16 game_p4_titexdata_16_info[] = {
    game_p4_titexdata_16_texs_tex_width,
    game_p4_titexdata_16_texs_tex_height,
    TITEX_FORMAT_16,
    TITEX_FLAGS_BLOCK,
};

u16 game_p4_titexdata_16_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_p4/game_p4_titexdata_16_texs_tex.rgba16.inc"
};
static_assert(ARRAY_COUNT(game_p4_titexdata_16_texs_tex) ==
                  game_p4_titexdata_16_texs_tex_width * game_p4_titexdata_16_texs_tex_height,
              "The dimensions of `game_p4_titexdata_16_texs_tex` does not match the size of the actual texture");

#elif VERSION_CN

/* titexdata_14 */

extern u16 game_p4_titexdata_14_texs_tex[];

TiTexDataTextures game_p4_titexdata_14_texs = {
    NULL,
    game_p4_titexdata_14_texs_tex,
};

#define game_p4_titexdata_14_texs_tex_width 48
#define game_p4_titexdata_14_texs_tex_height 16

u16 game_p4_titexdata_14_info[] = {
    game_p4_titexdata_14_texs_tex_width,
    game_p4_titexdata_14_texs_tex_height,
    TITEX_FORMAT_16,
    TITEX_FLAGS_BLOCK,
};

u16 game_p4_titexdata_14_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_p4/game_p4_titexdata_14_texs_tex.rgba16.inc"
};
static_assert(ARRAY_COUNT(game_p4_titexdata_14_texs_tex) ==
                  game_p4_titexdata_14_texs_tex_width * game_p4_titexdata_14_texs_tex_height,
              "The dimensions of `game_p4_titexdata_14_texs_tex` does not match the size of the actual texture");

/* titexdata_15 */

extern u16 game_p4_titexdata_15_texs_tex[];

TiTexDataTextures game_p4_titexdata_15_texs = {
    NULL,
    game_p4_titexdata_15_texs_tex,
};

#define game_p4_titexdata_15_texs_tex_width 48
#define game_p4_titexdata_15_texs_tex_height 16

u16 game_p4_titexdata_15_info[] = {
    game_p4_titexdata_15_texs_tex_width,
    game_p4_titexdata_15_texs_tex_height,
    TITEX_FORMAT_16,
    TITEX_FLAGS_BLOCK,
};

u16 game_p4_titexdata_15_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_p4/game_p4_titexdata_15_texs_tex.rgba16.inc"
};
static_assert(ARRAY_COUNT(game_p4_titexdata_15_texs_tex) ==
                  game_p4_titexdata_15_texs_tex_width * game_p4_titexdata_15_texs_tex_height,
              "The dimensions of `game_p4_titexdata_15_texs_tex` does not match the size of the actual texture");

/* titexdata_16 */

extern u16 game_p4_titexdata_16_texs_tex[];

TiTexDataTextures game_p4_titexdata_16_texs = {
    NULL,
    game_p4_titexdata_16_texs_tex,
};

#define game_p4_titexdata_16_texs_tex_width 304
#define game_p4_titexdata_16_texs_tex_height 26

u16 game_p4_titexdata_16_info[] = {
    game_p4_titexdata_16_texs_tex_width,
    game_p4_titexdata_16_texs_tex_height,
    TITEX_FORMAT_16,
    TITEX_FLAGS_BLOCK,
};

u16 game_p4_titexdata_16_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_p4/game_p4_titexdata_16_texs_tex.rgba16.inc"
};
static_assert(ARRAY_COUNT(game_p4_titexdata_16_texs_tex) ==
                  game_p4_titexdata_16_texs_tex_width * game_p4_titexdata_16_texs_tex_height,
              "The dimensions of `game_p4_titexdata_16_texs_tex` does not match the size of the actual texture");

#endif

/* titexdata_17 */

extern u16 game_p4_titexdata_17_texs_tex[];

TiTexDataTextures game_p4_titexdata_17_texs = {
    NULL,
    game_p4_titexdata_17_texs_tex,
};

#define game_p4_titexdata_17_texs_tex_width 32
#define game_p4_titexdata_17_texs_tex_height 12

u16 game_p4_titexdata_17_info[] = {
    game_p4_titexdata_17_texs_tex_width,
    game_p4_titexdata_17_texs_tex_height,
    TITEX_FORMAT_16,
    TITEX_FLAGS_BLOCK,
};

u16 game_p4_titexdata_17_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_p4/game_p4_titexdata_17_texs_tex.rgba16.inc"
};
static_assert(ARRAY_COUNT(game_p4_titexdata_17_texs_tex) ==
                  game_p4_titexdata_17_texs_tex_width * game_p4_titexdata_17_texs_tex_height,
              "The dimensions of `game_p4_titexdata_17_texs_tex` does not match the size of the actual texture");

#if VERSION_US || VERSION_GW

/* titexdata_18 */

extern u8 game_p4_titexdata_18_texs_tex[];

TiTexDataTextures game_p4_titexdata_18_texs = {
    NULL,
    game_p4_titexdata_18_texs_tex,
};

#define game_p4_titexdata_18_texs_tex_width 32
#define game_p4_titexdata_18_texs_tex_height 132

u16 game_p4_titexdata_18_info[] = {
    game_p4_titexdata_18_texs_tex_width,
    game_p4_titexdata_18_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 game_p4_titexdata_18_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_p4/game_p4_titexdata_18_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(game_p4_titexdata_18_texs_tex) ==
                  game_p4_titexdata_18_texs_tex_width * game_p4_titexdata_18_texs_tex_height / 2,
              "The dimensions of `game_p4_titexdata_18_texs_tex` does not match the size of the actual texture");

/* titexdata_19 */

extern u8 game_p4_titexdata_19_texs_tex[];

TiTexDataTextures game_p4_titexdata_19_texs = {
    NULL,
    game_p4_titexdata_19_texs_tex,
};

#define game_p4_titexdata_19_texs_tex_width 48
#define game_p4_titexdata_19_texs_tex_height 16

u16 game_p4_titexdata_19_info[] = {
    game_p4_titexdata_19_texs_tex_width,
    game_p4_titexdata_19_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 game_p4_titexdata_19_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_p4/game_p4_titexdata_19_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(game_p4_titexdata_19_texs_tex) ==
                  game_p4_titexdata_19_texs_tex_width * game_p4_titexdata_19_texs_tex_height / 2,
              "The dimensions of `game_p4_titexdata_19_texs_tex` does not match the size of the actual texture");

#elif VERSION_CN

/* titexdata_18 */

extern u16 game_p4_titexdata_18_texs_tex[];

TiTexDataTextures game_p4_titexdata_18_texs = {
    NULL,
    game_p4_titexdata_18_texs_tex,
};

#define game_p4_titexdata_18_texs_tex_width 32
#define game_p4_titexdata_18_texs_tex_height 12

u16 game_p4_titexdata_18_info[] = {
    game_p4_titexdata_18_texs_tex_width,
    game_p4_titexdata_18_texs_tex_height,
    TITEX_FORMAT_16,
    TITEX_FLAGS_BLOCK,
};

u16 game_p4_titexdata_18_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_p4/game_p4_titexdata_18_texs_tex.rgba16.inc"
};
static_assert(ARRAY_COUNT(game_p4_titexdata_18_texs_tex) ==
                  game_p4_titexdata_18_texs_tex_width * game_p4_titexdata_18_texs_tex_height,
              "The dimensions of `game_p4_titexdata_18_texs_tex` does not match the size of the actual texture");

/* titexdata_19 */

extern u8 game_p4_titexdata_19_texs_tex[];

TiTexDataTextures game_p4_titexdata_19_texs = {
    NULL,
    game_p4_titexdata_19_texs_tex,
};

#define game_p4_titexdata_19_texs_tex_width 32
#define game_p4_titexdata_19_texs_tex_height 132

u16 game_p4_titexdata_19_info[] = {
    game_p4_titexdata_19_texs_tex_width,
    game_p4_titexdata_19_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 game_p4_titexdata_19_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_p4/game_p4_titexdata_19_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(game_p4_titexdata_19_texs_tex) ==
                  game_p4_titexdata_19_texs_tex_width * game_p4_titexdata_19_texs_tex_height / 2,
              "The dimensions of `game_p4_titexdata_19_texs_tex` does not match the size of the actual texture");

#endif

/* titexdata_20 */

extern u8 game_p4_titexdata_20_texs_tex[];

TiTexDataTextures game_p4_titexdata_20_texs = {
    NULL,
    game_p4_titexdata_20_texs_tex,
};

#define game_p4_titexdata_20_texs_tex_width 48
#define game_p4_titexdata_20_texs_tex_height 16

u16 game_p4_titexdata_20_info[] = {
    game_p4_titexdata_20_texs_tex_width,
    game_p4_titexdata_20_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 game_p4_titexdata_20_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_p4/game_p4_titexdata_20_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(game_p4_titexdata_20_texs_tex) ==
                  game_p4_titexdata_20_texs_tex_width * game_p4_titexdata_20_texs_tex_height / 2,
              "The dimensions of `game_p4_titexdata_20_texs_tex` does not match the size of the actual texture");

/* titexdata_21 */

extern u8 game_p4_titexdata_21_texs_tex[];

TiTexDataTextures game_p4_titexdata_21_texs = {
    NULL,
    game_p4_titexdata_21_texs_tex,
};

#define game_p4_titexdata_21_texs_tex_width 48
#define game_p4_titexdata_21_texs_tex_height 16

u16 game_p4_titexdata_21_info[] = {
    game_p4_titexdata_21_texs_tex_width,
    game_p4_titexdata_21_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 game_p4_titexdata_21_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_p4/game_p4_titexdata_21_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(game_p4_titexdata_21_texs_tex) ==
                  game_p4_titexdata_21_texs_tex_width * game_p4_titexdata_21_texs_tex_height / 2,
              "The dimensions of `game_p4_titexdata_21_texs_tex` does not match the size of the actual texture");

#if VERSION_US || VERSION_GW

/* titexdata_22 */

extern u8 game_p4_titexdata_22_texs_tex[];

TiTexDataTextures game_p4_titexdata_22_texs = {
    NULL,
    game_p4_titexdata_22_texs_tex,
};

#define game_p4_titexdata_22_texs_tex_width 16
#define game_p4_titexdata_22_texs_tex_height 24

u16 game_p4_titexdata_22_info[] = {
    game_p4_titexdata_22_texs_tex_width,
    game_p4_titexdata_22_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 game_p4_titexdata_22_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_p4/game_p4_titexdata_22_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(game_p4_titexdata_22_texs_tex) ==
                  game_p4_titexdata_22_texs_tex_width * game_p4_titexdata_22_texs_tex_height / 2,
              "The dimensions of `game_p4_titexdata_22_texs_tex` does not match the size of the actual texture");

#elif VERSION_CN

/* titexdata_22 */

extern u8 game_p4_titexdata_22_texs_tex[];

TiTexDataTextures game_p4_titexdata_22_texs = {
    NULL,
    game_p4_titexdata_22_texs_tex,
};

#define game_p4_titexdata_22_texs_tex_width 48
#define game_p4_titexdata_22_texs_tex_height 16

u16 game_p4_titexdata_22_info[] = {
    game_p4_titexdata_22_texs_tex_width,
    game_p4_titexdata_22_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 game_p4_titexdata_22_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_p4/game_p4_titexdata_22_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(game_p4_titexdata_22_texs_tex) ==
                  game_p4_titexdata_22_texs_tex_width * game_p4_titexdata_22_texs_tex_height / 2,
              "The dimensions of `game_p4_titexdata_22_texs_tex` does not match the size of the actual texture");

#endif

/* titexdata_23 */

extern u8 game_p4_titexdata_23_texs_tex[];

TiTexDataTextures game_p4_titexdata_23_texs = {
    NULL,
    game_p4_titexdata_23_texs_tex,
};

#define game_p4_titexdata_23_texs_tex_width 304
#define game_p4_titexdata_23_texs_tex_height 26

u16 game_p4_titexdata_23_info[] = {
    game_p4_titexdata_23_texs_tex_width,
    game_p4_titexdata_23_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 game_p4_titexdata_23_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_p4/game_p4_titexdata_23_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(game_p4_titexdata_23_texs_tex) ==
                  game_p4_titexdata_23_texs_tex_width * game_p4_titexdata_23_texs_tex_height / 2,
              "The dimensions of `game_p4_titexdata_23_texs_tex` does not match the size of the actual texture");

/* titexdata_24 */

extern u8 game_p4_titexdata_24_texs_tex[];

TiTexDataTextures game_p4_titexdata_24_texs = {
    NULL,
    game_p4_titexdata_24_texs_tex,
};

#define game_p4_titexdata_24_texs_tex_width 32
#define game_p4_titexdata_24_texs_tex_height 12

u16 game_p4_titexdata_24_info[] = {
    game_p4_titexdata_24_texs_tex_width,
    game_p4_titexdata_24_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 game_p4_titexdata_24_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_p4/game_p4_titexdata_24_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(game_p4_titexdata_24_texs_tex) ==
                  game_p4_titexdata_24_texs_tex_width * game_p4_titexdata_24_texs_tex_height / 2,
              "The dimensions of `game_p4_titexdata_24_texs_tex` does not match the size of the actual texture");

/* titexdata_25 */

extern u16 game_p4_titexdata_25_texs_tex[];

TiTexDataTextures game_p4_titexdata_25_texs = {
    NULL,
    game_p4_titexdata_25_texs_tex,
};

#define game_p4_titexdata_25_texs_tex_width 48
#define game_p4_titexdata_25_texs_tex_height 16

u16 game_p4_titexdata_25_info[] = {
    game_p4_titexdata_25_texs_tex_width,
    game_p4_titexdata_25_texs_tex_height,
    TITEX_FORMAT_16,
    TITEX_FLAGS_BLOCK,
};

u16 game_p4_titexdata_25_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_p4/game_p4_titexdata_25_texs_tex.rgba16.inc"
};
static_assert(ARRAY_COUNT(game_p4_titexdata_25_texs_tex) ==
                  game_p4_titexdata_25_texs_tex_width * game_p4_titexdata_25_texs_tex_height,
              "The dimensions of `game_p4_titexdata_25_texs_tex` does not match the size of the actual texture");

/* titexdata_26 */

extern u8 game_p4_titexdata_26_texs_tex[];

TiTexDataTextures game_p4_titexdata_26_texs = {
    NULL,
    game_p4_titexdata_26_texs_tex,
};

#define game_p4_titexdata_26_texs_tex_width 48
#define game_p4_titexdata_26_texs_tex_height 16

u16 game_p4_titexdata_26_info[] = {
    game_p4_titexdata_26_texs_tex_width,
    game_p4_titexdata_26_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 game_p4_titexdata_26_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_p4/game_p4_titexdata_26_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(game_p4_titexdata_26_texs_tex) ==
                  game_p4_titexdata_26_texs_tex_width * game_p4_titexdata_26_texs_tex_height / 2,
              "The dimensions of `game_p4_titexdata_26_texs_tex` does not match the size of the actual texture");

/* titexdata_27 */

extern u16 game_p4_titexdata_27_texs_tex[];

TiTexDataTextures game_p4_titexdata_27_texs = {
    NULL,
    game_p4_titexdata_27_texs_tex,
};

#define game_p4_titexdata_27_texs_tex_width 64
#define game_p4_titexdata_27_texs_tex_height 28

u16 game_p4_titexdata_27_info[] = {
    game_p4_titexdata_27_texs_tex_width,
    game_p4_titexdata_27_texs_tex_height,
    TITEX_FORMAT_16,
    TITEX_FLAGS_BLOCK,
};

u16 game_p4_titexdata_27_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_p4/game_p4_titexdata_27_texs_tex.rgba16.inc"
};
static_assert(ARRAY_COUNT(game_p4_titexdata_27_texs_tex) ==
                  game_p4_titexdata_27_texs_tex_width * game_p4_titexdata_27_texs_tex_height,
              "The dimensions of `game_p4_titexdata_27_texs_tex` does not match the size of the actual texture");

/* titexdata_28 */

extern u8 game_p4_titexdata_28_texs_tex[];

TiTexDataTextures game_p4_titexdata_28_texs = {
    NULL,
    game_p4_titexdata_28_texs_tex,
};

#define game_p4_titexdata_28_texs_tex_width 64
#define game_p4_titexdata_28_texs_tex_height 28

u16 game_p4_titexdata_28_info[] = {
    game_p4_titexdata_28_texs_tex_width,
    game_p4_titexdata_28_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 game_p4_titexdata_28_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_p4/game_p4_titexdata_28_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(game_p4_titexdata_28_texs_tex) ==
                  game_p4_titexdata_28_texs_tex_width * game_p4_titexdata_28_texs_tex_height / 2,
              "The dimensions of `game_p4_titexdata_28_texs_tex` does not match the size of the actual texture");

/* titexdata_29 */

extern u16 game_p4_titexdata_29_texs_tex[];

TiTexDataTextures game_p4_titexdata_29_texs = {
    NULL,
    game_p4_titexdata_29_texs_tex,
};

#define game_p4_titexdata_29_texs_tex_width 64
#define game_p4_titexdata_29_texs_tex_height 15

u16 game_p4_titexdata_29_info[] = {
    game_p4_titexdata_29_texs_tex_width,
    game_p4_titexdata_29_texs_tex_height,
    TITEX_FORMAT_16,
    TITEX_FLAGS_BLOCK,
};

u16 game_p4_titexdata_29_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_p4/game_p4_titexdata_29_texs_tex.rgba16.inc"
};
static_assert(ARRAY_COUNT(game_p4_titexdata_29_texs_tex) ==
                  game_p4_titexdata_29_texs_tex_width * game_p4_titexdata_29_texs_tex_height,
              "The dimensions of `game_p4_titexdata_29_texs_tex` does not match the size of the actual texture");

/* titexdata_30 */

extern u8 game_p4_titexdata_30_texs_tex[];

TiTexDataTextures game_p4_titexdata_30_texs = {
    NULL,
    game_p4_titexdata_30_texs_tex,
};

#define game_p4_titexdata_30_texs_tex_width 64
#define game_p4_titexdata_30_texs_tex_height 15

u16 game_p4_titexdata_30_info[] = {
    game_p4_titexdata_30_texs_tex_width,
    game_p4_titexdata_30_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 game_p4_titexdata_30_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_p4/game_p4_titexdata_30_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(game_p4_titexdata_30_texs_tex) ==
                  game_p4_titexdata_30_texs_tex_width * game_p4_titexdata_30_texs_tex_height / 2,
              "The dimensions of `game_p4_titexdata_30_texs_tex` does not match the size of the actual texture");

TiTexData game_p4_titexdata[] = {
    { &game_p4_titexdata_00_texs, game_p4_titexdata_00_info },
    { &game_p4_titexdata_01_texs, game_p4_titexdata_01_info },
    { &game_p4_titexdata_02_texs, game_p4_titexdata_02_info },
    { &game_p4_titexdata_03_texs, game_p4_titexdata_03_info },
    { &game_p4_titexdata_04_texs, game_p4_titexdata_04_info },
    { &game_p4_titexdata_05_texs, game_p4_titexdata_05_info },
    { &game_p4_titexdata_06_texs, game_p4_titexdata_06_info },
    { &game_p4_titexdata_07_texs, game_p4_titexdata_07_info },
    { &game_p4_titexdata_08_texs, game_p4_titexdata_08_info },
    { &game_p4_titexdata_09_texs, game_p4_titexdata_09_info },
#if VERSION_US || VERSION_GW
    { &game_p4_titexdata_10_texs, game_p4_titexdata_10_info },
    { &game_p4_titexdata_11_texs, game_p4_titexdata_11_info },
#endif
    { &game_p4_titexdata_12_texs, game_p4_titexdata_12_info },
    { &game_p4_titexdata_13_texs, game_p4_titexdata_13_info },
    { &game_p4_titexdata_14_texs, game_p4_titexdata_14_info },
    { &game_p4_titexdata_15_texs, game_p4_titexdata_15_info },
#if VERSION_CN
    { &game_p4_titexdata_10_texs, game_p4_titexdata_10_info },
#endif
    { &game_p4_titexdata_16_texs, game_p4_titexdata_16_info },
    { &game_p4_titexdata_17_texs, game_p4_titexdata_17_info },
    { &game_p4_titexdata_18_texs, game_p4_titexdata_18_info },
    { &game_p4_titexdata_19_texs, game_p4_titexdata_19_info },
    { &game_p4_titexdata_20_texs, game_p4_titexdata_20_info },
    { &game_p4_titexdata_21_texs, game_p4_titexdata_21_info },
    { &game_p4_titexdata_22_texs, game_p4_titexdata_22_info },
#if VERSION_CN
    { &game_p4_titexdata_11_texs, game_p4_titexdata_11_info },
#endif
    { &game_p4_titexdata_23_texs, game_p4_titexdata_23_info },
    { &game_p4_titexdata_24_texs, game_p4_titexdata_24_info },
    { &game_p4_titexdata_25_texs, game_p4_titexdata_25_info },
    { &game_p4_titexdata_26_texs, game_p4_titexdata_26_info },
    { &game_p4_titexdata_27_texs, game_p4_titexdata_27_info },
    { &game_p4_titexdata_28_texs, game_p4_titexdata_28_info },
    { &game_p4_titexdata_29_texs, game_p4_titexdata_29_info },
    { &game_p4_titexdata_30_texs, game_p4_titexdata_30_info },
};

s32 game_p4_titexdata_len = ARRAY_COUNT(game_p4_titexdata);

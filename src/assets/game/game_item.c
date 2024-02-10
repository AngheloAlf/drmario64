#include "tex_func.h"

#include "libc/assert.h"
#include "macros_defines.h"
#include "alignment.h"

extern TiTexData game_item_titexdata[];
extern s32 game_item_titexdata_len;

TiTexDataHeader game_item_header = {
    game_item_titexdata,
    &game_item_titexdata_len,
};

/* titexdata_00 */

extern u16 game_item_titexdata_00_texs_tlut[];
extern u8 game_item_titexdata_00_texs_tex[];

TiTexDataTextures game_item_titexdata_00_texs = {
    game_item_titexdata_00_texs_tlut,
    game_item_titexdata_00_texs_tex,
};

#define game_item_titexdata_00_texs_tex_width 16
#define game_item_titexdata_00_texs_tex_height 128

u16 game_item_titexdata_00_info[] = {
    game_item_titexdata_00_texs_tex_width,
    game_item_titexdata_00_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u16 game_item_titexdata_00_texs_tlut[] ALIGNED(8) = {
#include "assets/game/game_item/game_item_titexdata_00_texs_tex.palette.inc"
};
static_assert(ARRAY_COUNT(game_item_titexdata_00_texs_tlut) == 4 * 4,
              "The dimensions of `game_item_titexdata_00_texs_tlut` does not match the size of the actual tlut");

u8 game_item_titexdata_00_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_item/game_item_titexdata_00_texs_tex.ci4.inc"
};
static_assert(ARRAY_COUNT(game_item_titexdata_00_texs_tex) ==
                  game_item_titexdata_00_texs_tex_width * game_item_titexdata_00_texs_tex_height / 2,
              "The dimensions of `game_item_titexdata_00_texs_tex` does not match the size of the actual texture");

/* titexdata_01 */

extern u16 game_item_titexdata_01_texs_tlut[];
extern u8 game_item_titexdata_01_texs_tex[];

TiTexDataTextures game_item_titexdata_01_texs = {
    game_item_titexdata_01_texs_tlut,
    game_item_titexdata_01_texs_tex,
};

#define game_item_titexdata_01_texs_tex_width 16
#define game_item_titexdata_01_texs_tex_height 128

u16 game_item_titexdata_01_info[] = {
    game_item_titexdata_01_texs_tex_width,
    game_item_titexdata_01_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u16 game_item_titexdata_01_texs_tlut[] ALIGNED(8) = {
#include "assets/game/game_item/game_item_titexdata_01_texs_tex.palette.inc"
};
static_assert(ARRAY_COUNT(game_item_titexdata_01_texs_tlut) == 4 * 4,
              "The dimensions of `game_item_titexdata_01_texs_tlut` does not match the size of the actual tlut");

u8 game_item_titexdata_01_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_item/game_item_titexdata_01_texs_tex.ci4.inc"
};
static_assert(ARRAY_COUNT(game_item_titexdata_01_texs_tex) ==
                  game_item_titexdata_01_texs_tex_width * game_item_titexdata_01_texs_tex_height / 2,
              "The dimensions of `game_item_titexdata_01_texs_tex` does not match the size of the actual texture");

/* titexdata_02 */

extern u16 game_item_titexdata_02_texs_tlut[];
extern u8 game_item_titexdata_02_texs_tex[];

TiTexDataTextures game_item_titexdata_02_texs = {
    game_item_titexdata_02_texs_tlut,
    game_item_titexdata_02_texs_tex,
};

#define game_item_titexdata_02_texs_tex_width 16
#define game_item_titexdata_02_texs_tex_height 220

u16 game_item_titexdata_02_info[] = {
    game_item_titexdata_02_texs_tex_width,
    game_item_titexdata_02_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u16 game_item_titexdata_02_texs_tlut[] ALIGNED(8) = {
#include "assets/game/game_item/game_item_titexdata_02_texs_tex.palette.inc"
};
static_assert(ARRAY_COUNT(game_item_titexdata_02_texs_tlut) == 4 * 4,
              "The dimensions of `game_item_titexdata_02_texs_tlut` does not match the size of the actual tlut");

u8 game_item_titexdata_02_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_item/game_item_titexdata_02_texs_tex.ci4.inc"
};
static_assert(ARRAY_COUNT(game_item_titexdata_02_texs_tex) ==
                  game_item_titexdata_02_texs_tex_width * game_item_titexdata_02_texs_tex_height / 2,
              "The dimensions of `game_item_titexdata_02_texs_tex` does not match the size of the actual texture");

/* titexdata_03 */

extern u16 game_item_titexdata_03_texs_tlut[];
extern u8 game_item_titexdata_03_texs_tex[];

TiTexDataTextures game_item_titexdata_03_texs = {
    game_item_titexdata_03_texs_tlut,
    game_item_titexdata_03_texs_tex,
};

#define game_item_titexdata_03_texs_tex_width 16
#define game_item_titexdata_03_texs_tex_height 220

u16 game_item_titexdata_03_info[] = {
    game_item_titexdata_03_texs_tex_width,
    game_item_titexdata_03_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u16 game_item_titexdata_03_texs_tlut[] ALIGNED(8) = {
#include "assets/game/game_item/game_item_titexdata_03_texs_tex.palette.inc"
};
static_assert(ARRAY_COUNT(game_item_titexdata_03_texs_tlut) == 4 * 4,
              "The dimensions of `game_item_titexdata_03_texs_tlut` does not match the size of the actual tlut");

u8 game_item_titexdata_03_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_item/game_item_titexdata_03_texs_tex.ci4.inc"
};
static_assert(ARRAY_COUNT(game_item_titexdata_03_texs_tex) ==
                  game_item_titexdata_03_texs_tex_width * game_item_titexdata_03_texs_tex_height / 2,
              "The dimensions of `game_item_titexdata_03_texs_tex` does not match the size of the actual texture");

/* titexdata_04 */

extern u16 game_item_titexdata_04_texs_tlut[];

TiTexDataTextures game_item_titexdata_04_texs = {
    game_item_titexdata_04_texs_tlut,
    NULL,
};

#define game_item_titexdata_04_texs_tex_width 2
#define game_item_titexdata_04_texs_tex_height 1

u16 game_item_titexdata_04_info[] = {
    game_item_titexdata_04_texs_tex_width,
    game_item_titexdata_04_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_TILE,
};

u16 game_item_titexdata_04_texs_tlut[] ALIGNED(8) = {
#include "assets/game/game_item/game_item_titexdata_04_texs_tlut.rgba16.inc"
};
static_assert(ARRAY_COUNT(game_item_titexdata_04_texs_tlut) == 4 * 4,
              "The dimensions of `game_item_titexdata_04_texs_tlut` does not match the size of the actual tlut");

/* titexdata_05 */

extern u16 game_item_titexdata_05_texs_tlut[];

TiTexDataTextures game_item_titexdata_05_texs = {
    game_item_titexdata_05_texs_tlut,
    NULL,
};

#define game_item_titexdata_05_texs_tex_width 2
#define game_item_titexdata_05_texs_tex_height 1

u16 game_item_titexdata_05_info[] = {
    game_item_titexdata_05_texs_tex_width,
    game_item_titexdata_05_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_TILE,
};

u16 game_item_titexdata_05_texs_tlut[] ALIGNED(8) = {
#include "assets/game/game_item/game_item_titexdata_05_texs_tlut.rgba16.inc"
};
static_assert(ARRAY_COUNT(game_item_titexdata_05_texs_tlut) == 4 * 4,
              "The dimensions of `game_item_titexdata_05_texs_tlut` does not match the size of the actual tlut");

/* titexdata_06 */

extern u16 game_item_titexdata_06_texs_tlut[];

TiTexDataTextures game_item_titexdata_06_texs = {
    game_item_titexdata_06_texs_tlut,
    NULL,
};

#define game_item_titexdata_06_texs_tex_width 2
#define game_item_titexdata_06_texs_tex_height 1

u16 game_item_titexdata_06_info[] = {
    game_item_titexdata_06_texs_tex_width,
    game_item_titexdata_06_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_TILE,
};

u16 game_item_titexdata_06_texs_tlut[] ALIGNED(8) = {
#include "assets/game/game_item/game_item_titexdata_06_texs_tlut.rgba16.inc"
};
static_assert(ARRAY_COUNT(game_item_titexdata_06_texs_tlut) == 4 * 4,
              "The dimensions of `game_item_titexdata_06_texs_tlut` does not match the size of the actual tlut");

/* titexdata_07 */

extern u16 game_item_titexdata_07_texs_tlut[];

TiTexDataTextures game_item_titexdata_07_texs = {
    game_item_titexdata_07_texs_tlut,
    NULL,
};

#define game_item_titexdata_07_texs_tex_width 2
#define game_item_titexdata_07_texs_tex_height 1

u16 game_item_titexdata_07_info[] = {
    game_item_titexdata_07_texs_tex_width,
    game_item_titexdata_07_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_TILE,
};

u16 game_item_titexdata_07_texs_tlut[] ALIGNED(8) = {
#include "assets/game/game_item/game_item_titexdata_07_texs_tlut.rgba16.inc"
};
static_assert(ARRAY_COUNT(game_item_titexdata_07_texs_tlut) == 4 * 4,
              "The dimensions of `game_item_titexdata_07_texs_tlut` does not match the size of the actual tlut");

/* titexdata_08 */

extern u16 game_item_titexdata_08_texs_tlut[];

TiTexDataTextures game_item_titexdata_08_texs = {
    game_item_titexdata_08_texs_tlut,
    NULL,
};

#define game_item_titexdata_08_texs_tex_width 2
#define game_item_titexdata_08_texs_tex_height 1

u16 game_item_titexdata_08_info[] = {
    game_item_titexdata_08_texs_tex_width,
    game_item_titexdata_08_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_TILE,
};

u16 game_item_titexdata_08_texs_tlut[] ALIGNED(8) = {
#include "assets/game/game_item/game_item_titexdata_08_texs_tlut.rgba16.inc"
};
static_assert(ARRAY_COUNT(game_item_titexdata_08_texs_tlut) == 4 * 4,
              "The dimensions of `game_item_titexdata_08_texs_tlut` does not match the size of the actual tlut");

/* titexdata_09 */

extern u16 game_item_titexdata_09_texs_tlut[];

TiTexDataTextures game_item_titexdata_09_texs = {
    game_item_titexdata_09_texs_tlut,
    NULL,
};

#define game_item_titexdata_09_texs_tex_width 2
#define game_item_titexdata_09_texs_tex_height 1

u16 game_item_titexdata_09_info[] = {
    game_item_titexdata_09_texs_tex_width,
    game_item_titexdata_09_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_TILE,
};

u16 game_item_titexdata_09_texs_tlut[] ALIGNED(8) = {
#include "assets/game/game_item/game_item_titexdata_09_texs_tlut.rgba16.inc"
};
static_assert(ARRAY_COUNT(game_item_titexdata_09_texs_tlut) == 4 * 4,
              "The dimensions of `game_item_titexdata_09_texs_tlut` does not match the size of the actual tlut");

/* titexdata_10 */

extern u16 game_item_titexdata_10_texs_tlut[];

TiTexDataTextures game_item_titexdata_10_texs = {
    game_item_titexdata_10_texs_tlut,
    NULL,
};

#define game_item_titexdata_10_texs_tex_width 2
#define game_item_titexdata_10_texs_tex_height 1

u16 game_item_titexdata_10_info[] = {
    game_item_titexdata_10_texs_tex_width,
    game_item_titexdata_10_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_TILE,
};

u16 game_item_titexdata_10_texs_tlut[] ALIGNED(8) = {
#include "assets/game/game_item/game_item_titexdata_10_texs_tlut.rgba16.inc"
};
static_assert(ARRAY_COUNT(game_item_titexdata_10_texs_tlut) == 4 * 4,
              "The dimensions of `game_item_titexdata_10_texs_tlut` does not match the size of the actual tlut");

/* titexdata_11 */

extern u16 game_item_titexdata_11_texs_tlut[];

TiTexDataTextures game_item_titexdata_11_texs = {
    game_item_titexdata_11_texs_tlut,
    NULL,
};

#define game_item_titexdata_11_texs_tex_width 2
#define game_item_titexdata_11_texs_tex_height 1

u16 game_item_titexdata_11_info[] = {
    game_item_titexdata_11_texs_tex_width,
    game_item_titexdata_11_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_TILE,
};

u16 game_item_titexdata_11_texs_tlut[] ALIGNED(8) = {
#include "assets/game/game_item/game_item_titexdata_11_texs_tlut.rgba16.inc"
};
static_assert(ARRAY_COUNT(game_item_titexdata_11_texs_tlut) == 4 * 4,
              "The dimensions of `game_item_titexdata_11_texs_tlut` does not match the size of the actual tlut");

/* titexdata_12 */

extern u8 game_item_titexdata_12_texs_tex[];

TiTexDataTextures game_item_titexdata_12_texs = {
    NULL,
    game_item_titexdata_12_texs_tex,
};

#define game_item_titexdata_12_texs_tex_width 16
#define game_item_titexdata_12_texs_tex_height 16

u16 game_item_titexdata_12_info[] = {
    game_item_titexdata_12_texs_tex_width,
    game_item_titexdata_12_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 game_item_titexdata_12_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_item/game_item_titexdata_12_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(game_item_titexdata_12_texs_tex) ==
                  game_item_titexdata_12_texs_tex_width * game_item_titexdata_12_texs_tex_height / 2,
              "The dimensions of `game_item_titexdata_12_texs_tex` does not match the size of the actual texture");

/* titexdata_13 */

extern u8 game_item_titexdata_13_texs_tex[];

TiTexDataTextures game_item_titexdata_13_texs = {
    NULL,
    game_item_titexdata_13_texs_tex,
};

#define game_item_titexdata_13_texs_tex_width 16
#define game_item_titexdata_13_texs_tex_height 16

u16 game_item_titexdata_13_info[] = {
    game_item_titexdata_13_texs_tex_width,
    game_item_titexdata_13_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 game_item_titexdata_13_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_item/game_item_titexdata_13_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(game_item_titexdata_13_texs_tex) ==
                  game_item_titexdata_13_texs_tex_width * game_item_titexdata_13_texs_tex_height / 2,
              "The dimensions of `game_item_titexdata_13_texs_tex` does not match the size of the actual texture");

/* titexdata_14 */

extern u8 game_item_titexdata_14_texs_tex[];

TiTexDataTextures game_item_titexdata_14_texs = {
    NULL,
    game_item_titexdata_14_texs_tex,
};

#define game_item_titexdata_14_texs_tex_width 16
#define game_item_titexdata_14_texs_tex_height 16

u16 game_item_titexdata_14_info[] = {
    game_item_titexdata_14_texs_tex_width,
    game_item_titexdata_14_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 game_item_titexdata_14_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_item/game_item_titexdata_14_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(game_item_titexdata_14_texs_tex) ==
                  game_item_titexdata_14_texs_tex_width * game_item_titexdata_14_texs_tex_height / 2,
              "The dimensions of `game_item_titexdata_14_texs_tex` does not match the size of the actual texture");

TiTexData game_item_titexdata[] = {
    { &game_item_titexdata_04_texs, game_item_titexdata_04_info },
    { &game_item_titexdata_05_texs, game_item_titexdata_05_info },
    { &game_item_titexdata_00_texs, game_item_titexdata_00_info },
    { &game_item_titexdata_01_texs, game_item_titexdata_01_info },
    { &game_item_titexdata_06_texs, game_item_titexdata_06_info },
    { &game_item_titexdata_07_texs, game_item_titexdata_07_info },
    { &game_item_titexdata_08_texs, game_item_titexdata_08_info },
    { &game_item_titexdata_09_texs, game_item_titexdata_09_info },
    { &game_item_titexdata_02_texs, game_item_titexdata_02_info },
    { &game_item_titexdata_03_texs, game_item_titexdata_03_info },
    { &game_item_titexdata_10_texs, game_item_titexdata_10_info },
    { &game_item_titexdata_11_texs, game_item_titexdata_11_info },
    { &game_item_titexdata_12_texs, game_item_titexdata_12_info },
    { &game_item_titexdata_13_texs, game_item_titexdata_13_info },
    { &game_item_titexdata_14_texs, game_item_titexdata_14_info },
};

s32 game_item_titexdata_len = ARRAY_COUNT(game_item_titexdata);

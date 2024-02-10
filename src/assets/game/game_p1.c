#include "tex_func.h"

#include "libc/assert.h"
#include "macros_defines.h"
#include "alignment.h"

extern TiTexData game_p1_titexdata[];
extern s32 game_p1_titexdata_len;

TiTexDataHeader game_p1_header = {
    game_p1_titexdata,
    &game_p1_titexdata_len,
};

/* titexdata_00 */

extern u16 game_p1_titexdata_00_texs_tlut[];
extern u8 game_p1_titexdata_00_texs_tex[];

TiTexDataTextures game_p1_titexdata_00_texs = {
    game_p1_titexdata_00_texs_tlut,
    game_p1_titexdata_00_texs_tex,
};

#define game_p1_titexdata_00_texs_tex_width 96
#define game_p1_titexdata_00_texs_tex_height 208

u16 game_p1_titexdata_00_info[] = {
    game_p1_titexdata_00_texs_tex_width, game_p1_titexdata_00_texs_tex_height, TITEX_FORMAT_8, TITEX_FLAGS_BLOCK,
};

u16 game_p1_titexdata_00_texs_tlut[] ALIGNED(8) = {
#include "assets/game/game_p1/game_p1_titexdata_00_texs_tlut.rgba16.inc"
};
static_assert(ARRAY_COUNT(game_p1_titexdata_00_texs_tlut) == 16 * 16, "The dimensions of `game_p1_titexdata_00_texs_tlut` does not match the size of the actual tlut");

u8 game_p1_titexdata_00_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_p1/game_p1_titexdata_00_texs_tex.i8.inc"
};
static_assert(ARRAY_COUNT(game_p1_titexdata_00_texs_tex) == game_p1_titexdata_00_texs_tex_width * game_p1_titexdata_00_texs_tex_height, "The dimensions of `game_p1_titexdata_00_texs_tex` does not match the size of the actual texture");

/* titexdata_01 */

extern u16 game_p1_titexdata_01_texs_tlut[];
extern u8 game_p1_titexdata_01_texs_tex[];

TiTexDataTextures game_p1_titexdata_01_texs = {
    game_p1_titexdata_01_texs_tlut,
    game_p1_titexdata_01_texs_tex,
};

#define game_p1_titexdata_01_texs_tex_width 96
#define game_p1_titexdata_01_texs_tex_height 208

u16 game_p1_titexdata_01_info[] = {
    game_p1_titexdata_01_texs_tex_width, game_p1_titexdata_01_texs_tex_height, TITEX_FORMAT_4, TITEX_FLAGS_BLOCK,
};

u16 game_p1_titexdata_01_texs_tlut[] ALIGNED(8) = {
#include "assets/game/game_p1/game_p1_titexdata_01_texs_tlut.rgba16.inc"
};
static_assert(ARRAY_COUNT(game_p1_titexdata_01_texs_tlut) == 4 * 4, "The dimensions of `game_p1_titexdata_01_texs_tlut` does not match the size of the actual tlut");

u8 game_p1_titexdata_01_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_p1/game_p1_titexdata_01_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(game_p1_titexdata_01_texs_tex) == game_p1_titexdata_01_texs_tex_width * game_p1_titexdata_01_texs_tex_height / 2, "The dimensions of `game_p1_titexdata_01_texs_tex` does not match the size of the actual texture");

/* titexdata_02 */

extern u16 game_p1_titexdata_02_texs_tex[];

TiTexDataTextures game_p1_titexdata_02_texs = {
    NULL,
    game_p1_titexdata_02_texs_tex,
};

#define game_p1_titexdata_02_texs_tex_width 16
#define game_p1_titexdata_02_texs_tex_height 180

u16 game_p1_titexdata_02_info[] = {
    game_p1_titexdata_02_texs_tex_width, game_p1_titexdata_02_texs_tex_height, TITEX_FORMAT_16, TITEX_FLAGS_BLOCK,
};

u16 game_p1_titexdata_02_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_p1/game_p1_titexdata_02_texs_tex.rgba16.inc"
};
static_assert(ARRAY_COUNT(game_p1_titexdata_02_texs_tex) == game_p1_titexdata_02_texs_tex_width * game_p1_titexdata_02_texs_tex_height, "The dimensions of `game_p1_titexdata_02_texs_tex` does not match the size of the actual texture");

/* titexdata_03 */

extern u16 game_p1_titexdata_03_texs_tex[];

TiTexDataTextures game_p1_titexdata_03_texs = {
    NULL,
    game_p1_titexdata_03_texs_tex,
};

#define game_p1_titexdata_03_texs_tex_width 16
#define game_p1_titexdata_03_texs_tex_height 144

u16 game_p1_titexdata_03_info[] = {
    game_p1_titexdata_03_texs_tex_width, game_p1_titexdata_03_texs_tex_height, TITEX_FORMAT_16, TITEX_FLAGS_BLOCK,
};

u16 game_p1_titexdata_03_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_p1/game_p1_titexdata_03_texs_tex.rgba16.inc"
};
static_assert(ARRAY_COUNT(game_p1_titexdata_03_texs_tex) == game_p1_titexdata_03_texs_tex_width * game_p1_titexdata_03_texs_tex_height, "The dimensions of `game_p1_titexdata_03_texs_tex` does not match the size of the actual texture");

/* titexdata_04 */

extern u16 game_p1_titexdata_04_texs_tex[];

TiTexDataTextures game_p1_titexdata_04_texs = {
    NULL,
    game_p1_titexdata_04_texs_tex,
};

#define game_p1_titexdata_04_texs_tex_width 16
#define game_p1_titexdata_04_texs_tex_height 132

u16 game_p1_titexdata_04_info[] = {
    game_p1_titexdata_04_texs_tex_width, game_p1_titexdata_04_texs_tex_height, TITEX_FORMAT_16, TITEX_FLAGS_BLOCK,
};

u16 game_p1_titexdata_04_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_p1/game_p1_titexdata_04_texs_tex.rgba16.inc"
};
static_assert(ARRAY_COUNT(game_p1_titexdata_04_texs_tex) == game_p1_titexdata_04_texs_tex_width * game_p1_titexdata_04_texs_tex_height, "The dimensions of `game_p1_titexdata_04_texs_tex` does not match the size of the actual texture");

/* titexdata_05 */

extern u16 game_p1_titexdata_05_texs_tex[];

TiTexDataTextures game_p1_titexdata_05_texs = {
    NULL,
    game_p1_titexdata_05_texs_tex,
};

#define game_p1_titexdata_05_texs_tex_width 16
#define game_p1_titexdata_05_texs_tex_height 132

u16 game_p1_titexdata_05_info[] = {
    game_p1_titexdata_05_texs_tex_width, game_p1_titexdata_05_texs_tex_height, TITEX_FORMAT_16, TITEX_FLAGS_BLOCK,
};

u16 game_p1_titexdata_05_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_p1/game_p1_titexdata_05_texs_tex.rgba16.inc"
};
static_assert(ARRAY_COUNT(game_p1_titexdata_05_texs_tex) == game_p1_titexdata_05_texs_tex_width * game_p1_titexdata_05_texs_tex_height, "The dimensions of `game_p1_titexdata_05_texs_tex` does not match the size of the actual texture");

/* titexdata_06 */

extern u8 game_p1_titexdata_06_texs_tex[];

TiTexDataTextures game_p1_titexdata_06_texs = {
    NULL,
    game_p1_titexdata_06_texs_tex,
};

#define game_p1_titexdata_06_texs_tex_width 16
#define game_p1_titexdata_06_texs_tex_height 180

u16 game_p1_titexdata_06_info[] = {
    game_p1_titexdata_06_texs_tex_width, game_p1_titexdata_06_texs_tex_height, TITEX_FORMAT_4, TITEX_FLAGS_BLOCK,
};

u8 game_p1_titexdata_06_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_p1/game_p1_titexdata_06_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(game_p1_titexdata_06_texs_tex) == game_p1_titexdata_06_texs_tex_width * game_p1_titexdata_06_texs_tex_height / 2, "The dimensions of `game_p1_titexdata_06_texs_tex` does not match the size of the actual texture");

/* titexdata_07 */

extern u8 game_p1_titexdata_07_texs_tex[];

TiTexDataTextures game_p1_titexdata_07_texs = {
    NULL,
    game_p1_titexdata_07_texs_tex,
};

#define game_p1_titexdata_07_texs_tex_width 16
#define game_p1_titexdata_07_texs_tex_height 144

u16 game_p1_titexdata_07_info[] = {
    game_p1_titexdata_07_texs_tex_width, game_p1_titexdata_07_texs_tex_height, TITEX_FORMAT_4, TITEX_FLAGS_BLOCK,
};

u8 game_p1_titexdata_07_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_p1/game_p1_titexdata_07_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(game_p1_titexdata_07_texs_tex) == game_p1_titexdata_07_texs_tex_width * game_p1_titexdata_07_texs_tex_height / 2, "The dimensions of `game_p1_titexdata_07_texs_tex` does not match the size of the actual texture");

/* titexdata_08 */

extern u16 game_p1_titexdata_08_texs_tex[];

TiTexDataTextures game_p1_titexdata_08_texs = {
    NULL,
    game_p1_titexdata_08_texs_tex,
};

#define game_p1_titexdata_08_texs_tex_width 76
#define game_p1_titexdata_08_texs_tex_height 100

u16 game_p1_titexdata_08_info[] = {
    game_p1_titexdata_08_texs_tex_width, game_p1_titexdata_08_texs_tex_height, TITEX_FORMAT_16, TITEX_FLAGS_BLOCK,
};

u16 game_p1_titexdata_08_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_p1/game_p1_titexdata_08_texs_tex.rgba16.inc"
};
static_assert(ARRAY_COUNT(game_p1_titexdata_08_texs_tex) == game_p1_titexdata_08_texs_tex_width * game_p1_titexdata_08_texs_tex_height, "The dimensions of `game_p1_titexdata_08_texs_tex` does not match the size of the actual texture");

/* titexdata_09 */

extern u8 game_p1_titexdata_09_texs_tex[];

TiTexDataTextures game_p1_titexdata_09_texs = {
    NULL,
    game_p1_titexdata_09_texs_tex,
};

#define game_p1_titexdata_09_texs_tex_width 80
#define game_p1_titexdata_09_texs_tex_height 100

u16 game_p1_titexdata_09_info[] = {
    game_p1_titexdata_09_texs_tex_width, game_p1_titexdata_09_texs_tex_height, TITEX_FORMAT_4, TITEX_FLAGS_BLOCK,
};

u8 game_p1_titexdata_09_texs_tex[] ALIGNED(8) = {
#include "assets/game/game_p1/game_p1_titexdata_09_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(game_p1_titexdata_09_texs_tex) == game_p1_titexdata_09_texs_tex_width * game_p1_titexdata_09_texs_tex_height / 2, "The dimensions of `game_p1_titexdata_09_texs_tex` does not match the size of the actual texture");

TiTexData game_p1_titexdata[] = {
    { &game_p1_titexdata_00_texs, game_p1_titexdata_00_info },
    { &game_p1_titexdata_01_texs, game_p1_titexdata_01_info },
    { &game_p1_titexdata_02_texs, game_p1_titexdata_02_info },
    { &game_p1_titexdata_03_texs, game_p1_titexdata_03_info },
    { &game_p1_titexdata_04_texs, game_p1_titexdata_04_info },
    { &game_p1_titexdata_05_texs, game_p1_titexdata_05_info },
    { &game_p1_titexdata_06_texs, game_p1_titexdata_06_info },
    { &game_p1_titexdata_07_texs, game_p1_titexdata_07_info },
    { &game_p1_titexdata_08_texs, game_p1_titexdata_08_info },
    { &game_p1_titexdata_09_texs, game_p1_titexdata_09_info },
};

s32 game_p1_titexdata_len = ARRAY_COUNT(game_p1_titexdata);

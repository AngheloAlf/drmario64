#include "tex_func.h"

#include "libc/assert.h"
#include "macros_defines.h"
#include "alignment.h"

extern TiTexData menu_story_titexdata[];
extern s32 menu_story_titexdata_len;

TiTexDataHeader menu_story_header = {
    menu_story_titexdata,
    &menu_story_titexdata_len,
};

/* titexdata_00 */

extern u8 menu_story_titexdata_00_texs_tex[];

TiTexDataTextures menu_story_titexdata_00_texs = {
    NULL,
    menu_story_titexdata_00_texs_tex,
};

#define menu_story_titexdata_00_texs_tex_width 64
#define menu_story_titexdata_00_texs_tex_height 32

u16 menu_story_titexdata_00_info[] = {
    menu_story_titexdata_00_texs_tex_width,
    menu_story_titexdata_00_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 menu_story_titexdata_00_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_story/menu_story_titexdata_00_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(menu_story_titexdata_00_texs_tex) ==
                  menu_story_titexdata_00_texs_tex_width * menu_story_titexdata_00_texs_tex_height / 2,
              "The dimensions of `menu_story_titexdata_00_texs_tex` does not match the size of the actual texture");

/* titexdata_01 */

extern u16 menu_story_titexdata_01_texs_tex[];

TiTexDataTextures menu_story_titexdata_01_texs = {
    NULL,
    menu_story_titexdata_01_texs_tex,
};

#define menu_story_titexdata_01_texs_tex_width 64
#define menu_story_titexdata_01_texs_tex_height 32

u16 menu_story_titexdata_01_info[] = {
    menu_story_titexdata_01_texs_tex_width,
    menu_story_titexdata_01_texs_tex_height,
    TITEX_FORMAT_16,
    TITEX_FLAGS_BLOCK,
};

u16 menu_story_titexdata_01_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_story/menu_story_titexdata_01_texs_tex.rgba16.inc"
};
static_assert(ARRAY_COUNT(menu_story_titexdata_01_texs_tex) ==
                  menu_story_titexdata_01_texs_tex_width * menu_story_titexdata_01_texs_tex_height,
              "The dimensions of `menu_story_titexdata_01_texs_tex` does not match the size of the actual texture");

/* titexdata_02 */

extern u16 menu_story_titexdata_02_texs_tlut[];
extern u8 menu_story_titexdata_02_texs_tex[];

TiTexDataTextures menu_story_titexdata_02_texs = {
    menu_story_titexdata_02_texs_tlut,
    menu_story_titexdata_02_texs_tex,
};

#define menu_story_titexdata_02_texs_tex_width 240
#define menu_story_titexdata_02_texs_tex_height 48

u16 menu_story_titexdata_02_info[] = {
    menu_story_titexdata_02_texs_tex_width,
    menu_story_titexdata_02_texs_tex_height,
    TITEX_FORMAT_8,
    TITEX_FLAGS_TILE,
};

u16 menu_story_titexdata_02_texs_tlut[] ALIGNED(8) = {
#include "assets/menu/menu_story/menu_story_titexdata_02_texs_tlut.rgba16.inc"
};
static_assert(ARRAY_COUNT(menu_story_titexdata_02_texs_tlut) == 16 * 16,
              "The dimensions of `menu_story_titexdata_02_texs_tlut` does not match the size of the actual tlut");

u8 menu_story_titexdata_02_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_story/menu_story_titexdata_02_texs_tex.i8.inc"
};
static_assert(ARRAY_COUNT(menu_story_titexdata_02_texs_tex) ==
                  menu_story_titexdata_02_texs_tex_width * menu_story_titexdata_02_texs_tex_height,
              "The dimensions of `menu_story_titexdata_02_texs_tex` does not match the size of the actual texture");

/* titexdata_03 */

extern u16 menu_story_titexdata_03_texs_tlut[];
extern u8 menu_story_titexdata_03_texs_tex[];

TiTexDataTextures menu_story_titexdata_03_texs = {
    menu_story_titexdata_03_texs_tlut,
    menu_story_titexdata_03_texs_tex,
};

#define menu_story_titexdata_03_texs_tex_width 240
#define menu_story_titexdata_03_texs_tex_height 48

u16 menu_story_titexdata_03_info[] = {
    menu_story_titexdata_03_texs_tex_width,
    menu_story_titexdata_03_texs_tex_height,
    TITEX_FORMAT_8,
    TITEX_FLAGS_TILE,
};

u16 menu_story_titexdata_03_texs_tlut[] ALIGNED(8) = {
#include "assets/menu/menu_story/menu_story_titexdata_03_texs_tlut.rgba16.inc"
};
static_assert(ARRAY_COUNT(menu_story_titexdata_03_texs_tlut) == 16 * 16,
              "The dimensions of `menu_story_titexdata_03_texs_tlut` does not match the size of the actual tlut");

u8 menu_story_titexdata_03_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_story/menu_story_titexdata_03_texs_tex.i8.inc"
};
static_assert(ARRAY_COUNT(menu_story_titexdata_03_texs_tex) ==
                  menu_story_titexdata_03_texs_tex_width * menu_story_titexdata_03_texs_tex_height,
              "The dimensions of `menu_story_titexdata_03_texs_tex` does not match the size of the actual texture");

/* titexdata_04 */

extern u16 menu_story_titexdata_04_texs_tlut[];
extern u8 menu_story_titexdata_04_texs_tex[];

TiTexDataTextures menu_story_titexdata_04_texs = {
    menu_story_titexdata_04_texs_tlut,
    menu_story_titexdata_04_texs_tex,
};

#define menu_story_titexdata_04_texs_tex_width 240
#define menu_story_titexdata_04_texs_tex_height 48

u16 menu_story_titexdata_04_info[] = {
    menu_story_titexdata_04_texs_tex_width,
    menu_story_titexdata_04_texs_tex_height,
    TITEX_FORMAT_8,
    TITEX_FLAGS_TILE,
};

u16 menu_story_titexdata_04_texs_tlut[] ALIGNED(8) = {
#include "assets/menu/menu_story/menu_story_titexdata_04_texs_tlut.rgba16.inc"
};
static_assert(ARRAY_COUNT(menu_story_titexdata_04_texs_tlut) == 16 * 16,
              "The dimensions of `menu_story_titexdata_04_texs_tlut` does not match the size of the actual tlut");

u8 menu_story_titexdata_04_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_story/menu_story_titexdata_04_texs_tex.i8.inc"
};
static_assert(ARRAY_COUNT(menu_story_titexdata_04_texs_tex) ==
                  menu_story_titexdata_04_texs_tex_width * menu_story_titexdata_04_texs_tex_height,
              "The dimensions of `menu_story_titexdata_04_texs_tex` does not match the size of the actual texture");

/* titexdata_05 */

extern u16 menu_story_titexdata_05_texs_tlut[];
extern u8 menu_story_titexdata_05_texs_tex[];

TiTexDataTextures menu_story_titexdata_05_texs = {
    menu_story_titexdata_05_texs_tlut,
    menu_story_titexdata_05_texs_tex,
};

#define menu_story_titexdata_05_texs_tex_width 16
#define menu_story_titexdata_05_texs_tex_height 16

u16 menu_story_titexdata_05_info[] = {
    menu_story_titexdata_05_texs_tex_width,
    menu_story_titexdata_05_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u16 menu_story_titexdata_05_texs_tlut[] ALIGNED(8) = {
#include "assets/menu/menu_story/menu_story_titexdata_05_texs_tlut.rgba16.inc"
};
static_assert(ARRAY_COUNT(menu_story_titexdata_05_texs_tlut) == 4 * 4,
              "The dimensions of `menu_story_titexdata_05_texs_tlut` does not match the size of the actual tlut");

u8 menu_story_titexdata_05_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_story/menu_story_titexdata_05_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(menu_story_titexdata_05_texs_tex) ==
                  menu_story_titexdata_05_texs_tex_width * menu_story_titexdata_05_texs_tex_height / 2,
              "The dimensions of `menu_story_titexdata_05_texs_tex` does not match the size of the actual texture");

/* titexdata_06 */

extern u16 menu_story_titexdata_06_texs_tlut[];
extern u8 menu_story_titexdata_06_texs_tex[];

TiTexDataTextures menu_story_titexdata_06_texs = {
    menu_story_titexdata_06_texs_tlut,
    menu_story_titexdata_06_texs_tex,
};

#define menu_story_titexdata_06_texs_tex_width 304
#define menu_story_titexdata_06_texs_tex_height 162

u16 menu_story_titexdata_06_info[] = {
    menu_story_titexdata_06_texs_tex_width,
    menu_story_titexdata_06_texs_tex_height,
    TITEX_FORMAT_8,
    TITEX_FLAGS_BLOCK,
};

u16 menu_story_titexdata_06_texs_tlut[] ALIGNED(8) = {
#include "assets/menu/menu_story/menu_story_titexdata_06_texs_tlut.rgba16.inc"
};
static_assert(ARRAY_COUNT(menu_story_titexdata_06_texs_tlut) == 16 * 16,
              "The dimensions of `menu_story_titexdata_06_texs_tlut` does not match the size of the actual tlut");

u8 menu_story_titexdata_06_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_story/menu_story_titexdata_06_texs_tex.i8.inc"
};
static_assert(ARRAY_COUNT(menu_story_titexdata_06_texs_tex) ==
                  menu_story_titexdata_06_texs_tex_width * menu_story_titexdata_06_texs_tex_height,
              "The dimensions of `menu_story_titexdata_06_texs_tex` does not match the size of the actual texture");

/* titexdata_07 */

extern u16 menu_story_titexdata_07_texs_tlut[];
extern u8 menu_story_titexdata_07_texs_tex[];

TiTexDataTextures menu_story_titexdata_07_texs = {
    menu_story_titexdata_07_texs_tlut,
    menu_story_titexdata_07_texs_tex,
};

#define menu_story_titexdata_07_texs_tex_width 32
#define menu_story_titexdata_07_texs_tex_height 20

u16 menu_story_titexdata_07_info[] = {
    menu_story_titexdata_07_texs_tex_width,
    menu_story_titexdata_07_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u16 menu_story_titexdata_07_texs_tlut[] ALIGNED(8) = {
#include "assets/menu/menu_story/menu_story_titexdata_07_texs_tlut.rgba16.inc"
};
static_assert(ARRAY_COUNT(menu_story_titexdata_07_texs_tlut) == 4 * 4,
              "The dimensions of `menu_story_titexdata_07_texs_tlut` does not match the size of the actual tlut");

u8 menu_story_titexdata_07_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_story/menu_story_titexdata_07_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(menu_story_titexdata_07_texs_tex) ==
                  menu_story_titexdata_07_texs_tex_width * menu_story_titexdata_07_texs_tex_height / 2,
              "The dimensions of `menu_story_titexdata_07_texs_tex` does not match the size of the actual texture");

/* titexdata_08 */

extern u16 menu_story_titexdata_08_texs_tlut[];
extern u8 menu_story_titexdata_08_texs_tex[];

TiTexDataTextures menu_story_titexdata_08_texs = {
    menu_story_titexdata_08_texs_tlut,
    menu_story_titexdata_08_texs_tex,
};

#define menu_story_titexdata_08_texs_tex_width 32
#define menu_story_titexdata_08_texs_tex_height 22

u16 menu_story_titexdata_08_info[] = {
    menu_story_titexdata_08_texs_tex_width,
    menu_story_titexdata_08_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u16 menu_story_titexdata_08_texs_tlut[] ALIGNED(8) = {
#include "assets/menu/menu_story/menu_story_titexdata_08_texs_tlut.rgba16.inc"
};
static_assert(ARRAY_COUNT(menu_story_titexdata_08_texs_tlut) == 4 * 4,
              "The dimensions of `menu_story_titexdata_08_texs_tlut` does not match the size of the actual tlut");

u8 menu_story_titexdata_08_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_story/menu_story_titexdata_08_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(menu_story_titexdata_08_texs_tex) ==
                  menu_story_titexdata_08_texs_tex_width * menu_story_titexdata_08_texs_tex_height / 2,
              "The dimensions of `menu_story_titexdata_08_texs_tex` does not match the size of the actual texture");

/* titexdata_09 */

extern u8 menu_story_titexdata_09_texs_tex[];

TiTexDataTextures menu_story_titexdata_09_texs = {
    NULL,
    menu_story_titexdata_09_texs_tex,
};

#define menu_story_titexdata_09_texs_tex_width 240
#define menu_story_titexdata_09_texs_tex_height 48

u16 menu_story_titexdata_09_info[] = {
    menu_story_titexdata_09_texs_tex_width,
    menu_story_titexdata_09_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_TILE,
};

u8 menu_story_titexdata_09_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_story/menu_story_titexdata_09_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(menu_story_titexdata_09_texs_tex) ==
                  menu_story_titexdata_09_texs_tex_width * menu_story_titexdata_09_texs_tex_height / 2,
              "The dimensions of `menu_story_titexdata_09_texs_tex` does not match the size of the actual texture");

/* titexdata_10 */

extern u8 menu_story_titexdata_10_texs_tex[];

TiTexDataTextures menu_story_titexdata_10_texs = {
    NULL,
    menu_story_titexdata_10_texs_tex,
};

#define menu_story_titexdata_10_texs_tex_width 240
#define menu_story_titexdata_10_texs_tex_height 48

u16 menu_story_titexdata_10_info[] = {
    menu_story_titexdata_10_texs_tex_width,
    menu_story_titexdata_10_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_TILE,
};

u8 menu_story_titexdata_10_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_story/menu_story_titexdata_10_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(menu_story_titexdata_10_texs_tex) ==
                  menu_story_titexdata_10_texs_tex_width * menu_story_titexdata_10_texs_tex_height / 2,
              "The dimensions of `menu_story_titexdata_10_texs_tex` does not match the size of the actual texture");

/* titexdata_11 */

extern u8 menu_story_titexdata_11_texs_tex[];

TiTexDataTextures menu_story_titexdata_11_texs = {
    NULL,
    menu_story_titexdata_11_texs_tex,
};

#define menu_story_titexdata_11_texs_tex_width 240
#define menu_story_titexdata_11_texs_tex_height 48

u16 menu_story_titexdata_11_info[] = {
    menu_story_titexdata_11_texs_tex_width,
    menu_story_titexdata_11_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_TILE,
};

u8 menu_story_titexdata_11_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_story/menu_story_titexdata_11_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(menu_story_titexdata_11_texs_tex) ==
                  menu_story_titexdata_11_texs_tex_width * menu_story_titexdata_11_texs_tex_height / 2,
              "The dimensions of `menu_story_titexdata_11_texs_tex` does not match the size of the actual texture");

/* titexdata_12 */

extern u8 menu_story_titexdata_12_texs_tex[];

TiTexDataTextures menu_story_titexdata_12_texs = {
    NULL,
    menu_story_titexdata_12_texs_tex,
};

#define menu_story_titexdata_12_texs_tex_width 58
#define menu_story_titexdata_12_texs_tex_height 58

u16 menu_story_titexdata_12_info[] = {
    menu_story_titexdata_12_texs_tex_width,
    menu_story_titexdata_12_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_TILE,
};

u8 menu_story_titexdata_12_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_story/menu_story_titexdata_12_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(menu_story_titexdata_12_texs_tex) ==
                  menu_story_titexdata_12_texs_tex_width * menu_story_titexdata_12_texs_tex_height / 2,
              "The dimensions of `menu_story_titexdata_12_texs_tex` does not match the size of the actual texture");

u8 menu_story_titexdata_12_45_pad[0x4] = { 0 };

TiTexData menu_story_titexdata[] = {
    { &menu_story_titexdata_00_texs, menu_story_titexdata_00_info },
    { &menu_story_titexdata_01_texs, menu_story_titexdata_01_info },
    { &menu_story_titexdata_02_texs, menu_story_titexdata_02_info },
    { &menu_story_titexdata_03_texs, menu_story_titexdata_03_info },
    { &menu_story_titexdata_04_texs, menu_story_titexdata_04_info },
    { &menu_story_titexdata_05_texs, menu_story_titexdata_05_info },
    { &menu_story_titexdata_06_texs, menu_story_titexdata_06_info },
    { &menu_story_titexdata_07_texs, menu_story_titexdata_07_info },
    { &menu_story_titexdata_08_texs, menu_story_titexdata_08_info },
    { &menu_story_titexdata_09_texs, menu_story_titexdata_09_info },
    { &menu_story_titexdata_10_texs, menu_story_titexdata_10_info },
    { &menu_story_titexdata_11_texs, menu_story_titexdata_11_info },
    { &menu_story_titexdata_12_texs, menu_story_titexdata_12_info },
};

s32 menu_story_titexdata_len = ARRAY_COUNT(menu_story_titexdata);

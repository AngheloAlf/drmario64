#include "tex_func.h"

#include "libc/assert.h"
#include "macros_defines.h"
#include "alignment.h"

extern TiTexData menu_char_titexdata[];
extern s32 menu_char_titexdata_len;

TiTexDataHeader menu_char_header = {
    menu_char_titexdata,
    &menu_char_titexdata_len,
};

/* titexdata_00 */

extern u16 menu_char_titexdata_00_texs_tex[];

TiTexDataTextures menu_char_titexdata_00_texs = {
    NULL,
    menu_char_titexdata_00_texs_tex,
};

#define menu_char_titexdata_00_texs_tex_width 48
#define menu_char_titexdata_00_texs_tex_height 36

u16 menu_char_titexdata_00_info[] = {
    menu_char_titexdata_00_texs_tex_width,
    menu_char_titexdata_00_texs_tex_height,
    TITEX_FORMAT_16,
    TITEX_FLAGS_BLOCK,
};

u16 menu_char_titexdata_00_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_char/menu_char_titexdata_00_texs_tex.rgba16.inc"
};
static_assert(ARRAY_COUNT(menu_char_titexdata_00_texs_tex) ==
                  menu_char_titexdata_00_texs_tex_width * menu_char_titexdata_00_texs_tex_height,
              "The dimensions of `menu_char_titexdata_00_texs_tex` does not match the size of the actual texture");

/* titexdata_01 */

extern u8 menu_char_titexdata_01_texs_tex[];

TiTexDataTextures menu_char_titexdata_01_texs = {
    NULL,
    menu_char_titexdata_01_texs_tex,
};

#define menu_char_titexdata_01_texs_tex_width 48
#define menu_char_titexdata_01_texs_tex_height 36

u16 menu_char_titexdata_01_info[] = {
    menu_char_titexdata_01_texs_tex_width,
    menu_char_titexdata_01_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 menu_char_titexdata_01_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_char/menu_char_titexdata_01_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(menu_char_titexdata_01_texs_tex) ==
                  menu_char_titexdata_01_texs_tex_width * menu_char_titexdata_01_texs_tex_height / 2,
              "The dimensions of `menu_char_titexdata_01_texs_tex` does not match the size of the actual texture");

/* titexdata_02 */

extern u16 menu_char_titexdata_02_texs_tlut[];
extern u8 menu_char_titexdata_02_texs_tex[];

TiTexDataTextures menu_char_titexdata_02_texs = {
    menu_char_titexdata_02_texs_tlut,
    menu_char_titexdata_02_texs_tex,
};

#define menu_char_titexdata_02_texs_tex_width 64
#define menu_char_titexdata_02_texs_tex_height 48

u16 menu_char_titexdata_02_info[] = {
    menu_char_titexdata_02_texs_tex_width,
    menu_char_titexdata_02_texs_tex_height,
    TITEX_FORMAT_8,
    TITEX_FLAGS_BLOCK,
};

u16 menu_char_titexdata_02_texs_tlut[] ALIGNED(8) = {
#include "assets/menu/menu_char/menu_char_titexdata_02_texs_tlut.rgba16.inc"
};
static_assert(ARRAY_COUNT(menu_char_titexdata_02_texs_tlut) == 16 * 16,
              "The dimensions of `menu_char_titexdata_02_texs_tlut` does not match the size of the actual tlut");

u8 menu_char_titexdata_02_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_char/menu_char_titexdata_02_texs_tex.i8.inc"
};
static_assert(ARRAY_COUNT(menu_char_titexdata_02_texs_tex) ==
                  menu_char_titexdata_02_texs_tex_width * menu_char_titexdata_02_texs_tex_height,
              "The dimensions of `menu_char_titexdata_02_texs_tex` does not match the size of the actual texture");

/* titexdata_03 */

extern u16 menu_char_titexdata_03_texs_tlut[];
extern u8 menu_char_titexdata_03_texs_tex[];

TiTexDataTextures menu_char_titexdata_03_texs = {
    menu_char_titexdata_03_texs_tlut,
    menu_char_titexdata_03_texs_tex,
};

#define menu_char_titexdata_03_texs_tex_width 50
#define menu_char_titexdata_03_texs_tex_height 51

u16 menu_char_titexdata_03_info[] = {
    menu_char_titexdata_03_texs_tex_width,
    menu_char_titexdata_03_texs_tex_height,
    TITEX_FORMAT_8,
    TITEX_FLAGS_TILE,
};

u16 menu_char_titexdata_03_texs_tlut[] ALIGNED(8) = {
#include "assets/menu/menu_char/menu_char_titexdata_03_texs_tex.palette.inc"
};
static_assert(ARRAY_COUNT(menu_char_titexdata_03_texs_tlut) == 16 * 16,
              "The dimensions of `menu_char_titexdata_03_texs_tlut` does not match the size of the actual tlut");

u8 menu_char_titexdata_03_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_char/menu_char_titexdata_03_texs_tex.ci8.inc"
};
static_assert(ARRAY_COUNT(menu_char_titexdata_03_texs_tex) ==
                  menu_char_titexdata_03_texs_tex_width * menu_char_titexdata_03_texs_tex_height,
              "The dimensions of `menu_char_titexdata_03_texs_tex` does not match the size of the actual texture");

/* titexdata_04 */

extern u16 menu_char_titexdata_04_texs_tlut[];
extern u8 menu_char_titexdata_04_texs_tex[];

TiTexDataTextures menu_char_titexdata_04_texs = {
    menu_char_titexdata_04_texs_tlut,
    menu_char_titexdata_04_texs_tex,
};

#define menu_char_titexdata_04_texs_tex_width 52
#define menu_char_titexdata_04_texs_tex_height 51

u16 menu_char_titexdata_04_info[] = {
    menu_char_titexdata_04_texs_tex_width,
    menu_char_titexdata_04_texs_tex_height,
    TITEX_FORMAT_8,
    TITEX_FLAGS_TILE,
};

u16 menu_char_titexdata_04_texs_tlut[] ALIGNED(8) = {
#include "assets/menu/menu_char/menu_char_titexdata_04_texs_tlut.rgba16.inc"
};
static_assert(ARRAY_COUNT(menu_char_titexdata_04_texs_tlut) == 16 * 16,
              "The dimensions of `menu_char_titexdata_04_texs_tlut` does not match the size of the actual tlut");

u8 menu_char_titexdata_04_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_char/menu_char_titexdata_04_texs_tex.i8.inc"
};
static_assert(ARRAY_COUNT(menu_char_titexdata_04_texs_tex) ==
                  menu_char_titexdata_04_texs_tex_width * menu_char_titexdata_04_texs_tex_height,
              "The dimensions of `menu_char_titexdata_04_texs_tex` does not match the size of the actual texture");

u8 menu_char_titexdata_04_17_pad[0x4] = { 0 };

/* titexdata_05 */

extern u16 menu_char_titexdata_05_texs_tlut[];
extern u8 menu_char_titexdata_05_texs_tex[];

TiTexDataTextures menu_char_titexdata_05_texs = {
    menu_char_titexdata_05_texs_tlut,
    menu_char_titexdata_05_texs_tex,
};

#define menu_char_titexdata_05_texs_tex_width 288
#define menu_char_titexdata_05_texs_tex_height 179

u16 menu_char_titexdata_05_info[] = {
    menu_char_titexdata_05_texs_tex_width,
    menu_char_titexdata_05_texs_tex_height,
    TITEX_FORMAT_8,
    TITEX_FLAGS_BLOCK,
};

u16 menu_char_titexdata_05_texs_tlut[] ALIGNED(8) = {
#include "assets/menu/menu_char/menu_char_titexdata_05_texs_tlut.rgba16.inc"
};
static_assert(ARRAY_COUNT(menu_char_titexdata_05_texs_tlut) == 16 * 16,
              "The dimensions of `menu_char_titexdata_05_texs_tlut` does not match the size of the actual tlut");

u8 menu_char_titexdata_05_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_char/menu_char_titexdata_05_texs_tex.i8.inc"
};
static_assert(ARRAY_COUNT(menu_char_titexdata_05_texs_tex) ==
                  menu_char_titexdata_05_texs_tex_width * menu_char_titexdata_05_texs_tex_height,
              "The dimensions of `menu_char_titexdata_05_texs_tex` does not match the size of the actual texture");

/* titexdata_06 */

extern u16 menu_char_titexdata_06_texs_tlut[];
extern u8 menu_char_titexdata_06_texs_tex[];

TiTexDataTextures menu_char_titexdata_06_texs = {
    menu_char_titexdata_06_texs_tlut,
    menu_char_titexdata_06_texs_tex,
};

#define menu_char_titexdata_06_texs_tex_width 56
#define menu_char_titexdata_06_texs_tex_height 30

u16 menu_char_titexdata_06_info[] = {
    menu_char_titexdata_06_texs_tex_width,
    menu_char_titexdata_06_texs_tex_height,
    TITEX_FORMAT_8,
    TITEX_FLAGS_BLOCK,
};

u16 menu_char_titexdata_06_texs_tlut[] ALIGNED(8) = {
#include "assets/menu/menu_char/menu_char_titexdata_06_texs_tlut.rgba16.inc"
};
static_assert(ARRAY_COUNT(menu_char_titexdata_06_texs_tlut) == 16 * 16,
              "The dimensions of `menu_char_titexdata_06_texs_tlut` does not match the size of the actual tlut");

u8 menu_char_titexdata_06_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_char/menu_char_titexdata_06_texs_tex.i8.inc"
};
static_assert(ARRAY_COUNT(menu_char_titexdata_06_texs_tex) ==
                  menu_char_titexdata_06_texs_tex_width * menu_char_titexdata_06_texs_tex_height,
              "The dimensions of `menu_char_titexdata_06_texs_tex` does not match the size of the actual texture");

TiTexData menu_char_titexdata[] = {
    { &menu_char_titexdata_00_texs, menu_char_titexdata_00_info },
    { &menu_char_titexdata_01_texs, menu_char_titexdata_01_info },
    { &menu_char_titexdata_02_texs, menu_char_titexdata_02_info },
    { &menu_char_titexdata_03_texs, menu_char_titexdata_03_info },
    { &menu_char_titexdata_04_texs, menu_char_titexdata_04_info },
    { &menu_char_titexdata_05_texs, menu_char_titexdata_05_info },
    { &menu_char_titexdata_06_texs, menu_char_titexdata_06_info },
};

s32 menu_char_titexdata_len = ARRAY_COUNT(menu_char_titexdata);

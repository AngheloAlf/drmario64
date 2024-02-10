#include "tex_func.h"

#include "libc/assert.h"
#include "macros_defines.h"
#include "alignment.h"

extern TiTexData menu_p4_titexdata[];
extern s32 menu_p4_titexdata_len;

TiTexDataHeader menu_p4_header = {
    menu_p4_titexdata,
    &menu_p4_titexdata_len,
};

/* titexdata_00 */

extern u16 menu_p4_titexdata_00_texs_tlut[];
extern u8 menu_p4_titexdata_00_texs_tex[];

TiTexDataTextures menu_p4_titexdata_00_texs = {
    menu_p4_titexdata_00_texs_tlut,
    menu_p4_titexdata_00_texs_tex,
};

#define menu_p4_titexdata_00_texs_tex_width 48
#define menu_p4_titexdata_00_texs_tex_height 525

u16 menu_p4_titexdata_00_info[] = {
    menu_p4_titexdata_00_texs_tex_width,
    menu_p4_titexdata_00_texs_tex_height,
    TITEX_FORMAT_8,
    TITEX_FLAGS_BLOCK,
};

u16 menu_p4_titexdata_00_texs_tlut[] ALIGNED(8) = {
#include "assets/menu/menu_p4/menu_p4_titexdata_00_texs_tlut.rgba16.inc"
};
static_assert(ARRAY_COUNT(menu_p4_titexdata_00_texs_tlut) == 16 * 16,
              "The dimensions of `menu_p4_titexdata_00_texs_tlut` does not match the size of the actual tlut");

u8 menu_p4_titexdata_00_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_p4/menu_p4_titexdata_00_texs_tex.i8.inc"
};
static_assert(ARRAY_COUNT(menu_p4_titexdata_00_texs_tex) ==
                  menu_p4_titexdata_00_texs_tex_width * menu_p4_titexdata_00_texs_tex_height,
              "The dimensions of `menu_p4_titexdata_00_texs_tex` does not match the size of the actual texture");

/* titexdata_01 */

extern u16 menu_p4_titexdata_01_texs_tlut[];
extern u8 menu_p4_titexdata_01_texs_tex[];

TiTexDataTextures menu_p4_titexdata_01_texs = {
    menu_p4_titexdata_01_texs_tlut,
    menu_p4_titexdata_01_texs_tex,
};

#define menu_p4_titexdata_01_texs_tex_width 304
#define menu_p4_titexdata_01_texs_tex_height 43

u16 menu_p4_titexdata_01_info[] = {
    menu_p4_titexdata_01_texs_tex_width,
    menu_p4_titexdata_01_texs_tex_height,
    TITEX_FORMAT_8,
    TITEX_FLAGS_BLOCK,
};

u16 menu_p4_titexdata_01_texs_tlut[] ALIGNED(8) = {
#include "assets/menu/menu_p4/menu_p4_titexdata_01_texs_tlut.rgba16.inc"
};
static_assert(ARRAY_COUNT(menu_p4_titexdata_01_texs_tlut) == 16 * 16,
              "The dimensions of `menu_p4_titexdata_01_texs_tlut` does not match the size of the actual tlut");

u8 menu_p4_titexdata_01_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_p4/menu_p4_titexdata_01_texs_tex.i8.inc"
};
static_assert(ARRAY_COUNT(menu_p4_titexdata_01_texs_tex) ==
                  menu_p4_titexdata_01_texs_tex_width * menu_p4_titexdata_01_texs_tex_height,
              "The dimensions of `menu_p4_titexdata_01_texs_tex` does not match the size of the actual texture");

/* titexdata_02 */

extern u16 menu_p4_titexdata_02_texs_tlut[];
extern u8 menu_p4_titexdata_02_texs_tex[];

TiTexDataTextures menu_p4_titexdata_02_texs = {
    menu_p4_titexdata_02_texs_tlut,
    menu_p4_titexdata_02_texs_tex,
};

#define menu_p4_titexdata_02_texs_tex_width 304
#define menu_p4_titexdata_02_texs_tex_height 43

u16 menu_p4_titexdata_02_info[] = {
    menu_p4_titexdata_02_texs_tex_width,
    menu_p4_titexdata_02_texs_tex_height,
    TITEX_FORMAT_8,
    TITEX_FLAGS_BLOCK,
};

u16 menu_p4_titexdata_02_texs_tlut[] ALIGNED(8) = {
#include "assets/menu/menu_p4/menu_p4_titexdata_02_texs_tlut.rgba16.inc"
};
static_assert(ARRAY_COUNT(menu_p4_titexdata_02_texs_tlut) == 16 * 16,
              "The dimensions of `menu_p4_titexdata_02_texs_tlut` does not match the size of the actual tlut");

u8 menu_p4_titexdata_02_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_p4/menu_p4_titexdata_02_texs_tex.i8.inc"
};
static_assert(ARRAY_COUNT(menu_p4_titexdata_02_texs_tex) ==
                  menu_p4_titexdata_02_texs_tex_width * menu_p4_titexdata_02_texs_tex_height,
              "The dimensions of `menu_p4_titexdata_02_texs_tex` does not match the size of the actual texture");

/* titexdata_03 */

extern u8 menu_p4_titexdata_03_texs_tex[];

TiTexDataTextures menu_p4_titexdata_03_texs = {
    NULL,
    menu_p4_titexdata_03_texs_tex,
};

#define menu_p4_titexdata_03_texs_tex_width 48
#define menu_p4_titexdata_03_texs_tex_height 20

u16 menu_p4_titexdata_03_info[] = {
    menu_p4_titexdata_03_texs_tex_width,
    menu_p4_titexdata_03_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 menu_p4_titexdata_03_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_p4/menu_p4_titexdata_03_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(menu_p4_titexdata_03_texs_tex) ==
                  menu_p4_titexdata_03_texs_tex_width * menu_p4_titexdata_03_texs_tex_height / 2,
              "The dimensions of `menu_p4_titexdata_03_texs_tex` does not match the size of the actual texture");

/* titexdata_04 */

extern u8 menu_p4_titexdata_04_texs_tex[];

TiTexDataTextures menu_p4_titexdata_04_texs = {
    NULL,
    menu_p4_titexdata_04_texs_tex,
};

#define menu_p4_titexdata_04_texs_tex_width 48
#define menu_p4_titexdata_04_texs_tex_height 20

u16 menu_p4_titexdata_04_info[] = {
    menu_p4_titexdata_04_texs_tex_width,
    menu_p4_titexdata_04_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 menu_p4_titexdata_04_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_p4/menu_p4_titexdata_04_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(menu_p4_titexdata_04_texs_tex) ==
                  menu_p4_titexdata_04_texs_tex_width * menu_p4_titexdata_04_texs_tex_height / 2,
              "The dimensions of `menu_p4_titexdata_04_texs_tex` does not match the size of the actual texture");

/* titexdata_05 */

extern u8 menu_p4_titexdata_05_texs_tex[];

TiTexDataTextures menu_p4_titexdata_05_texs = {
    NULL,
    menu_p4_titexdata_05_texs_tex,
};

#define menu_p4_titexdata_05_texs_tex_width 48
#define menu_p4_titexdata_05_texs_tex_height 20

u16 menu_p4_titexdata_05_info[] = {
    menu_p4_titexdata_05_texs_tex_width,
    menu_p4_titexdata_05_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 menu_p4_titexdata_05_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_p4/menu_p4_titexdata_05_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(menu_p4_titexdata_05_texs_tex) ==
                  menu_p4_titexdata_05_texs_tex_width * menu_p4_titexdata_05_texs_tex_height / 2,
              "The dimensions of `menu_p4_titexdata_05_texs_tex` does not match the size of the actual texture");

/* titexdata_06 */

extern u8 menu_p4_titexdata_06_texs_tex[];

TiTexDataTextures menu_p4_titexdata_06_texs = {
    NULL,
    menu_p4_titexdata_06_texs_tex,
};

#define menu_p4_titexdata_06_texs_tex_width 48
#define menu_p4_titexdata_06_texs_tex_height 20

u16 menu_p4_titexdata_06_info[] = {
    menu_p4_titexdata_06_texs_tex_width,
    menu_p4_titexdata_06_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 menu_p4_titexdata_06_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_p4/menu_p4_titexdata_06_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(menu_p4_titexdata_06_texs_tex) ==
                  menu_p4_titexdata_06_texs_tex_width * menu_p4_titexdata_06_texs_tex_height / 2,
              "The dimensions of `menu_p4_titexdata_06_texs_tex` does not match the size of the actual texture");

/* titexdata_07 */

extern u8 menu_p4_titexdata_07_texs_tex[];

TiTexDataTextures menu_p4_titexdata_07_texs = {
    NULL,
    menu_p4_titexdata_07_texs_tex,
};

#define menu_p4_titexdata_07_texs_tex_width 48
#define menu_p4_titexdata_07_texs_tex_height 20

u16 menu_p4_titexdata_07_info[] = {
    menu_p4_titexdata_07_texs_tex_width,
    menu_p4_titexdata_07_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 menu_p4_titexdata_07_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_p4/menu_p4_titexdata_07_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(menu_p4_titexdata_07_texs_tex) ==
                  menu_p4_titexdata_07_texs_tex_width * menu_p4_titexdata_07_texs_tex_height / 2,
              "The dimensions of `menu_p4_titexdata_07_texs_tex` does not match the size of the actual texture");

/* titexdata_08 */

extern u8 menu_p4_titexdata_08_texs_tex[];

TiTexDataTextures menu_p4_titexdata_08_texs = {
    NULL,
    menu_p4_titexdata_08_texs_tex,
};

#define menu_p4_titexdata_08_texs_tex_width 48
#define menu_p4_titexdata_08_texs_tex_height 20

u16 menu_p4_titexdata_08_info[] = {
    menu_p4_titexdata_08_texs_tex_width,
    menu_p4_titexdata_08_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 menu_p4_titexdata_08_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_p4/menu_p4_titexdata_08_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(menu_p4_titexdata_08_texs_tex) ==
                  menu_p4_titexdata_08_texs_tex_width * menu_p4_titexdata_08_texs_tex_height / 2,
              "The dimensions of `menu_p4_titexdata_08_texs_tex` does not match the size of the actual texture");

TiTexData menu_p4_titexdata[] = {
    { &menu_p4_titexdata_00_texs, menu_p4_titexdata_00_info },
    { &menu_p4_titexdata_01_texs, menu_p4_titexdata_01_info },
    { &menu_p4_titexdata_02_texs, menu_p4_titexdata_02_info },
    { &menu_p4_titexdata_03_texs, menu_p4_titexdata_03_info },
    { &menu_p4_titexdata_04_texs, menu_p4_titexdata_04_info },
    { &menu_p4_titexdata_05_texs, menu_p4_titexdata_05_info },
    { &menu_p4_titexdata_06_texs, menu_p4_titexdata_06_info },
    { &menu_p4_titexdata_07_texs, menu_p4_titexdata_07_info },
    { &menu_p4_titexdata_08_texs, menu_p4_titexdata_08_info },
};

s32 menu_p4_titexdata_len = ARRAY_COUNT(menu_p4_titexdata);

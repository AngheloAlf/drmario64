#include "assets/menu/menu_common.h"
#include "tex_func.h"

#include "libc/assert.h"
#include "macros_defines.h"
#include "alignment.h"

extern TiTexData menu_common_titexdata[];
extern s32 menu_common_titexdata_len;

TiTexDataHeader menu_common_header = {
    menu_common_titexdata,
    &menu_common_titexdata_len,
};

/* titexdata_00 */

extern u8 menu_common_cursor_alpha_texs_tex[];

TexturePtr menu_common_cursor_alpha_texs[2] = {
    NULL,
    menu_common_cursor_alpha_texs_tex,
};

#define menu_common_cursor_alpha_texs_tex_width 32
#define menu_common_cursor_alpha_texs_tex_height 32

u16 menu_common_cursor_alpha_info[] = {
    menu_common_cursor_alpha_texs_tex_width,
    menu_common_cursor_alpha_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 menu_common_cursor_alpha_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_common/menu_common_cursor_alpha_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(menu_common_cursor_alpha_texs_tex) ==
                  menu_common_cursor_alpha_texs_tex_width * menu_common_cursor_alpha_texs_tex_height / 2,
              "The dimensions of `menu_common_cursor_alpha_texs_tex` does not match the size of the actual texture");

/* titexdata_01 */

extern u16 menu_common_cursor_texs_tex[];

TexturePtr menu_common_cursor_texs[2] = {
    NULL,
    menu_common_cursor_texs_tex,
};

#define menu_common_cursor_texs_tex_width 32
#define menu_common_cursor_texs_tex_height 32

u16 menu_common_cursor_info[] = {
    menu_common_cursor_texs_tex_width,
    menu_common_cursor_texs_tex_height,
    TITEX_FORMAT_16,
    TITEX_FLAGS_BLOCK,
};

u16 menu_common_cursor_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_common/menu_common_cursor_texs_tex.rgba16.inc"
};
static_assert(ARRAY_COUNT(menu_common_cursor_texs_tex) ==
                  menu_common_cursor_texs_tex_width * menu_common_cursor_texs_tex_height,
              "The dimensions of `menu_common_cursor_texs_tex` does not match the size of the actual texture");

/* titexdata_02 */

extern u16 menu_common_titexdata_02_texs_tlut[];
extern u8 menu_common_titexdata_02_texs_tex[];

TexturePtr menu_common_titexdata_02_texs[2] = {
    menu_common_titexdata_02_texs_tlut,
    menu_common_titexdata_02_texs_tex,
};

#define menu_common_titexdata_02_texs_tex_width 64
#define menu_common_titexdata_02_texs_tex_height 40

u16 menu_common_titexdata_02_info[] = {
    menu_common_titexdata_02_texs_tex_width,
    menu_common_titexdata_02_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u16 menu_common_titexdata_02_texs_tlut[] ALIGNED(8) = {
#include "assets/menu/menu_common/menu_common_titexdata_02_texs_tex.palette.inc"
};
static_assert(ARRAY_COUNT(menu_common_titexdata_02_texs_tlut) == 4 * 4,
              "The dimensions of `menu_common_titexdata_02_texs_tlut` does not match the size of the actual tlut");

u8 menu_common_titexdata_02_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_common/menu_common_titexdata_02_texs_tex.ci4.inc"
};
static_assert(ARRAY_COUNT(menu_common_titexdata_02_texs_tex) ==
                  menu_common_titexdata_02_texs_tex_width * menu_common_titexdata_02_texs_tex_height / 2,
              "The dimensions of `menu_common_titexdata_02_texs_tex` does not match the size of the actual texture");

/* titexdata_03 */

extern u8 menu_common_titexdata_03_texs_tex[];

TexturePtr menu_common_titexdata_03_texs[2] = {
    NULL,
    menu_common_titexdata_03_texs_tex,
};

#define menu_common_titexdata_03_texs_tex_width 64
#define menu_common_titexdata_03_texs_tex_height 64

u16 menu_common_titexdata_03_info[] = {
    menu_common_titexdata_03_texs_tex_width,
    menu_common_titexdata_03_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 menu_common_titexdata_03_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_common/menu_common_titexdata_03_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(menu_common_titexdata_03_texs_tex) ==
                  menu_common_titexdata_03_texs_tex_width * menu_common_titexdata_03_texs_tex_height / 2,
              "The dimensions of `menu_common_titexdata_03_texs_tex` does not match the size of the actual texture");

/* titexdata_04 */

extern u8 menu_common_titexdata_04_texs_tex[];

TexturePtr menu_common_titexdata_04_texs[2] = {
    NULL,
    menu_common_titexdata_04_texs_tex,
};

#define menu_common_titexdata_04_texs_tex_width 64
#define menu_common_titexdata_04_texs_tex_height 64

u16 menu_common_titexdata_04_info[] = {
    menu_common_titexdata_04_texs_tex_width,
    menu_common_titexdata_04_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 menu_common_titexdata_04_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_common/menu_common_titexdata_04_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(menu_common_titexdata_04_texs_tex) ==
                  menu_common_titexdata_04_texs_tex_width * menu_common_titexdata_04_texs_tex_height / 2,
              "The dimensions of `menu_common_titexdata_04_texs_tex` does not match the size of the actual texture");

/* titexdata_05 */

extern u8 menu_common_titexdata_05_texs_tex[];

TexturePtr menu_common_titexdata_05_texs[2] = {
    NULL,
    menu_common_titexdata_05_texs_tex,
};

#define menu_common_titexdata_05_texs_tex_width 64
#define menu_common_titexdata_05_texs_tex_height 64

u16 menu_common_titexdata_05_info[] = {
    menu_common_titexdata_05_texs_tex_width,
    menu_common_titexdata_05_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 menu_common_titexdata_05_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_common/menu_common_titexdata_05_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(menu_common_titexdata_05_texs_tex) ==
                  menu_common_titexdata_05_texs_tex_width * menu_common_titexdata_05_texs_tex_height / 2,
              "The dimensions of `menu_common_titexdata_05_texs_tex` does not match the size of the actual texture");

/* titexdata_06 */

extern u8 menu_common_titexdata_06_texs_tex[];

TexturePtr menu_common_titexdata_06_texs[2] = {
    NULL,
    menu_common_titexdata_06_texs_tex,
};

#define menu_common_titexdata_06_texs_tex_width 16
#define menu_common_titexdata_06_texs_tex_height 16

u16 menu_common_titexdata_06_info[] = {
    menu_common_titexdata_06_texs_tex_width,
    menu_common_titexdata_06_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 menu_common_titexdata_06_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_common/menu_common_titexdata_06_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(menu_common_titexdata_06_texs_tex) ==
                  menu_common_titexdata_06_texs_tex_width * menu_common_titexdata_06_texs_tex_height / 2,
              "The dimensions of `menu_common_titexdata_06_texs_tex` does not match the size of the actual texture");

/* titexdata_07 */

extern u8 menu_common_titexdata_07_texs_tex[];

TexturePtr menu_common_titexdata_07_texs[2] = {
    NULL,
    menu_common_titexdata_07_texs_tex,
};

#define menu_common_titexdata_07_texs_tex_width 16
#define menu_common_titexdata_07_texs_tex_height 16

u16 menu_common_titexdata_07_info[] = {
    menu_common_titexdata_07_texs_tex_width,
    menu_common_titexdata_07_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 menu_common_titexdata_07_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_common/menu_common_titexdata_07_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(menu_common_titexdata_07_texs_tex) ==
                  menu_common_titexdata_07_texs_tex_width * menu_common_titexdata_07_texs_tex_height / 2,
              "The dimensions of `menu_common_titexdata_07_texs_tex` does not match the size of the actual texture");

/* titexdata_08 */

extern u8 menu_common_titexdata_08_texs_tex[];

TexturePtr menu_common_titexdata_08_texs[2] = {
    NULL,
    menu_common_titexdata_08_texs_tex,
};

#define menu_common_titexdata_08_texs_tex_width 16
#define menu_common_titexdata_08_texs_tex_height 16

u16 menu_common_titexdata_08_info[] = {
    menu_common_titexdata_08_texs_tex_width,
    menu_common_titexdata_08_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 menu_common_titexdata_08_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_common/menu_common_titexdata_08_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(menu_common_titexdata_08_texs_tex) ==
                  menu_common_titexdata_08_texs_tex_width * menu_common_titexdata_08_texs_tex_height / 2,
              "The dimensions of `menu_common_titexdata_08_texs_tex` does not match the size of the actual texture");

/* titexdata_09 */

extern u8 menu_common_titexdata_09_texs_tex[];

TexturePtr menu_common_titexdata_09_texs[2] = {
    NULL,
    menu_common_titexdata_09_texs_tex,
};

#define menu_common_titexdata_09_texs_tex_width 48
#define menu_common_titexdata_09_texs_tex_height 18

u16 menu_common_titexdata_09_info[] = {
    menu_common_titexdata_09_texs_tex_width,
    menu_common_titexdata_09_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 menu_common_titexdata_09_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_common/menu_common_titexdata_09_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(menu_common_titexdata_09_texs_tex) ==
                  menu_common_titexdata_09_texs_tex_width * menu_common_titexdata_09_texs_tex_height / 2,
              "The dimensions of `menu_common_titexdata_09_texs_tex` does not match the size of the actual texture");

/* titexdata_10 */

extern u8 menu_common_titexdata_10_texs_tex[];

TexturePtr menu_common_titexdata_10_texs[2] = {
    NULL,
    menu_common_titexdata_10_texs_tex,
};

#define menu_common_titexdata_10_texs_tex_width 48
#define menu_common_titexdata_10_texs_tex_height 18

u16 menu_common_titexdata_10_info[] = {
    menu_common_titexdata_10_texs_tex_width,
    menu_common_titexdata_10_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 menu_common_titexdata_10_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_common/menu_common_titexdata_10_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(menu_common_titexdata_10_texs_tex) ==
                  menu_common_titexdata_10_texs_tex_width * menu_common_titexdata_10_texs_tex_height / 2,
              "The dimensions of `menu_common_titexdata_10_texs_tex` does not match the size of the actual texture");

/* titexdata_11 */

extern u8 menu_common_titexdata_11_texs_tex[];

TexturePtr menu_common_titexdata_11_texs[2] = {
    NULL,
    menu_common_titexdata_11_texs_tex,
};

#define menu_common_titexdata_11_texs_tex_width 48
#define menu_common_titexdata_11_texs_tex_height 26

u16 menu_common_titexdata_11_info[] = {
    menu_common_titexdata_11_texs_tex_width,
    menu_common_titexdata_11_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 menu_common_titexdata_11_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_common/menu_common_titexdata_11_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(menu_common_titexdata_11_texs_tex) ==
                  menu_common_titexdata_11_texs_tex_width * menu_common_titexdata_11_texs_tex_height / 2,
              "The dimensions of `menu_common_titexdata_11_texs_tex` does not match the size of the actual texture");

/* titexdata_12 */

extern u8 menu_common_titexdata_12_texs_tex[];

TexturePtr menu_common_titexdata_12_texs[2] = {
    NULL,
    menu_common_titexdata_12_texs_tex,
};

#define menu_common_titexdata_12_texs_tex_width 16
#define menu_common_titexdata_12_texs_tex_height 16

u16 menu_common_titexdata_12_info[] = {
    menu_common_titexdata_12_texs_tex_width,
    menu_common_titexdata_12_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 menu_common_titexdata_12_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_common/menu_common_titexdata_12_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(menu_common_titexdata_12_texs_tex) ==
                  menu_common_titexdata_12_texs_tex_width * menu_common_titexdata_12_texs_tex_height / 2,
              "The dimensions of `menu_common_titexdata_12_texs_tex` does not match the size of the actual texture");

/* titexdata_13 */

extern u8 menu_common_titexdata_13_texs_tex[];

TexturePtr menu_common_titexdata_13_texs[2] = {
    NULL,
    menu_common_titexdata_13_texs_tex,
};

#define menu_common_titexdata_13_texs_tex_width 16
#define menu_common_titexdata_13_texs_tex_height 10

u16 menu_common_titexdata_13_info[] = {
    menu_common_titexdata_13_texs_tex_width,
    menu_common_titexdata_13_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 menu_common_titexdata_13_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_common/menu_common_titexdata_13_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(menu_common_titexdata_13_texs_tex) ==
                  menu_common_titexdata_13_texs_tex_width * menu_common_titexdata_13_texs_tex_height / 2,
              "The dimensions of `menu_common_titexdata_13_texs_tex` does not match the size of the actual texture");

/* titexdata_14 */

extern u16 menu_common_menu_options_texs_tlut[];
extern u8 menu_common_menu_options_texs_tex[];

TexturePtr menu_common_menu_options_texs[2] = {
    menu_common_menu_options_texs_tlut,
    menu_common_menu_options_texs_tex,
};

#define menu_common_menu_options_texs_tex_width 128
#define menu_common_menu_options_texs_tex_height 940

u16 menu_common_menu_options_info[] = {
    menu_common_menu_options_texs_tex_width,
    menu_common_menu_options_texs_tex_height,
    TITEX_FORMAT_8,
    TITEX_FLAGS_BLOCK,
};

u16 menu_common_menu_options_texs_tlut[] ALIGNED(8) = {
#include "assets/menu/menu_common/menu_common_menu_options_texs_tex.palette.inc"
};
static_assert(ARRAY_COUNT(menu_common_menu_options_texs_tlut) == 16 * 16,
              "The dimensions of `menu_common_menu_options_texs_tlut` does not match the size of the actual tlut");

u8 menu_common_menu_options_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_common/menu_common_menu_options_texs_tex.ci8.inc"
};
static_assert(ARRAY_COUNT(menu_common_menu_options_texs_tex) ==
                  menu_common_menu_options_texs_tex_width * menu_common_menu_options_texs_tex_height,
              "The dimensions of `menu_common_menu_options_texs_tex` does not match the size of the actual texture");

/* titexdata_15 */

extern u16 menu_common_menu_titles_texs_tlut[];
extern u8 menu_common_menu_titles_texs_tex[];

TexturePtr menu_common_menu_titles_texs[2] = {
    menu_common_menu_titles_texs_tlut,
    menu_common_menu_titles_texs_tex,
};

#define menu_common_menu_titles_texs_tex_width 96
#define menu_common_menu_titles_texs_tex_height 336

u16 menu_common_menu_titles_info[] = {
    menu_common_menu_titles_texs_tex_width,
    menu_common_menu_titles_texs_tex_height,
    TITEX_FORMAT_8,
    TITEX_FLAGS_BLOCK,
};

u16 menu_common_menu_titles_texs_tlut[] ALIGNED(8) = {
#include "assets/menu/menu_common/menu_common_menu_titles_texs_tex.palette.inc"
};
static_assert(ARRAY_COUNT(menu_common_menu_titles_texs_tlut) == 16 * 16,
              "The dimensions of `menu_common_menu_titles_texs_tlut` does not match the size of the actual tlut");

u8 menu_common_menu_titles_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_common/menu_common_menu_titles_texs_tex.ci8.inc"
};
static_assert(ARRAY_COUNT(menu_common_menu_titles_texs_tex) ==
                  menu_common_menu_titles_texs_tex_width * menu_common_menu_titles_texs_tex_height,
              "The dimensions of `menu_common_menu_titles_texs_tex` does not match the size of the actual texture");

TiTexData menu_common_titexdata[] = {
    { menu_common_cursor_alpha_texs, menu_common_cursor_alpha_info }, /* MENUCOMMON_CURSOR_ALPHA */
    { menu_common_cursor_texs, menu_common_cursor_info },             /* MENUCOMMON_CURSOR */
    { menu_common_titexdata_02_texs, menu_common_titexdata_02_info }, /* MENUCOMMON_2 */
    { menu_common_titexdata_03_texs, menu_common_titexdata_03_info }, /* MENUCOMMON_3 */
    { menu_common_titexdata_04_texs, menu_common_titexdata_04_info }, /* MENUCOMMON_4 */
    { menu_common_titexdata_05_texs, menu_common_titexdata_05_info }, /* MENUCOMMON_5 */
    { menu_common_titexdata_06_texs, menu_common_titexdata_06_info }, /* MENUCOMMON_6 */
    { menu_common_titexdata_07_texs, menu_common_titexdata_07_info }, /* MENUCOMMON_7 */
    { menu_common_titexdata_08_texs, menu_common_titexdata_08_info }, /* MENUCOMMON_8 */
    { menu_common_titexdata_09_texs, menu_common_titexdata_09_info }, /* MENUCOMMON_9 */
    { menu_common_titexdata_10_texs, menu_common_titexdata_10_info }, /* MENUCOMMON_10 */
    { menu_common_titexdata_11_texs, menu_common_titexdata_11_info }, /* MENUCOMMON_11 */
    { menu_common_titexdata_12_texs, menu_common_titexdata_12_info }, /* MENUCOMMON_12 */
    { menu_common_titexdata_13_texs, menu_common_titexdata_13_info }, /* MENUCOMMON_13 */
    { menu_common_menu_options_texs, menu_common_menu_options_info }, /* MENUCOMMON_OPTIONS */
    { menu_common_menu_titles_texs, menu_common_menu_titles_info },   /* MENUCOMMON_TITLES */
};

s32 menu_common_titexdata_len = ARRAY_COUNT(menu_common_titexdata);

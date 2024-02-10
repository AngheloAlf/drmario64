#include "tex_func.h"

#include "libc/assert.h"
#include "macros_defines.h"
#include "alignment.h"

extern TiTexData menu_setup_titexdata[];
extern s32 menu_setup_titexdata_len;

TiTexDataHeader menu_setup_header = {
    menu_setup_titexdata,
    &menu_setup_titexdata_len,
};

/* titexdata_00 */

extern u8 menu_setup_titexdata_00_texs_tex[];

TiTexDataTextures menu_setup_titexdata_00_texs = {
    NULL,
    menu_setup_titexdata_00_texs_tex,
};

#define menu_setup_titexdata_00_texs_tex_width 16
#define menu_setup_titexdata_00_texs_tex_height 120

u16 menu_setup_titexdata_00_info[] = {
    menu_setup_titexdata_00_texs_tex_width,
    menu_setup_titexdata_00_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 menu_setup_titexdata_00_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_setup/menu_setup_titexdata_00_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(menu_setup_titexdata_00_texs_tex) ==
                  menu_setup_titexdata_00_texs_tex_width * menu_setup_titexdata_00_texs_tex_height / 2,
              "The dimensions of `menu_setup_titexdata_00_texs_tex` does not match the size of the actual texture");

#if VERSION_US || VERSION_GW

/* titexdata_01 */

extern u8 menu_setup_titexdata_01_texs_tex[];

TiTexDataTextures menu_setup_titexdata_01_texs = {
    NULL,
    menu_setup_titexdata_01_texs_tex,
};

#define menu_setup_titexdata_01_texs_tex_width 32
#define menu_setup_titexdata_01_texs_tex_height 132

u16 menu_setup_titexdata_01_info[] = {
    menu_setup_titexdata_01_texs_tex_width,
    menu_setup_titexdata_01_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 menu_setup_titexdata_01_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_setup/menu_setup_titexdata_01_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(menu_setup_titexdata_01_texs_tex) ==
                  menu_setup_titexdata_01_texs_tex_width * menu_setup_titexdata_01_texs_tex_height / 2,
              "The dimensions of `menu_setup_titexdata_01_texs_tex` does not match the size of the actual texture");

/* titexdata_02 */

extern u8 menu_setup_titexdata_02_texs_tex[];

TiTexDataTextures menu_setup_titexdata_02_texs = {
    NULL,
    menu_setup_titexdata_02_texs_tex,
};

#define menu_setup_titexdata_02_texs_tex_width 64
#define menu_setup_titexdata_02_texs_tex_height 64

u16 menu_setup_titexdata_02_info[] = {
    menu_setup_titexdata_02_texs_tex_width,
    menu_setup_titexdata_02_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 menu_setup_titexdata_02_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_setup/menu_setup_titexdata_02_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(menu_setup_titexdata_02_texs_tex) ==
                  menu_setup_titexdata_02_texs_tex_width * menu_setup_titexdata_02_texs_tex_height / 2,
              "The dimensions of `menu_setup_titexdata_02_texs_tex` does not match the size of the actual texture");

/* titexdata_03 */

extern u8 menu_setup_titexdata_03_texs_tex[];

TiTexDataTextures menu_setup_titexdata_03_texs = {
    NULL,
    menu_setup_titexdata_03_texs_tex,
};

#define menu_setup_titexdata_03_texs_tex_width 48
#define menu_setup_titexdata_03_texs_tex_height 48

u16 menu_setup_titexdata_03_info[] = {
    menu_setup_titexdata_03_texs_tex_width,
    menu_setup_titexdata_03_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 menu_setup_titexdata_03_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_setup/menu_setup_titexdata_03_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(menu_setup_titexdata_03_texs_tex) ==
                  menu_setup_titexdata_03_texs_tex_width * menu_setup_titexdata_03_texs_tex_height / 2,
              "The dimensions of `menu_setup_titexdata_03_texs_tex` does not match the size of the actual texture");

/* titexdata_04 */

extern u8 menu_setup_titexdata_04_texs_tex[];

TiTexDataTextures menu_setup_titexdata_04_texs = {
    NULL,
    menu_setup_titexdata_04_texs_tex,
};

#define menu_setup_titexdata_04_texs_tex_width 48
#define menu_setup_titexdata_04_texs_tex_height 16

u16 menu_setup_titexdata_04_info[] = {
    menu_setup_titexdata_04_texs_tex_width,
    menu_setup_titexdata_04_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 menu_setup_titexdata_04_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_setup/menu_setup_titexdata_04_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(menu_setup_titexdata_04_texs_tex) ==
                  menu_setup_titexdata_04_texs_tex_width * menu_setup_titexdata_04_texs_tex_height / 2,
              "The dimensions of `menu_setup_titexdata_04_texs_tex` does not match the size of the actual texture");

/* titexdata_05 */

extern u8 menu_setup_titexdata_05_texs_tex[];

TiTexDataTextures menu_setup_titexdata_05_texs = {
    NULL,
    menu_setup_titexdata_05_texs_tex,
};

#define menu_setup_titexdata_05_texs_tex_width 56
#define menu_setup_titexdata_05_texs_tex_height 48

u16 menu_setup_titexdata_05_info[] = {
    menu_setup_titexdata_05_texs_tex_width,
    menu_setup_titexdata_05_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_TILE,
};

u8 menu_setup_titexdata_05_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_setup/menu_setup_titexdata_05_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(menu_setup_titexdata_05_texs_tex) ==
                  menu_setup_titexdata_05_texs_tex_width * menu_setup_titexdata_05_texs_tex_height / 2,
              "The dimensions of `menu_setup_titexdata_05_texs_tex` does not match the size of the actual texture");

/* titexdata_06 */

extern u8 menu_setup_titexdata_06_texs_tex[];

TiTexDataTextures menu_setup_titexdata_06_texs = {
    NULL,
    menu_setup_titexdata_06_texs_tex,
};

#define menu_setup_titexdata_06_texs_tex_width 48
#define menu_setup_titexdata_06_texs_tex_height 48

u16 menu_setup_titexdata_06_info[] = {
    menu_setup_titexdata_06_texs_tex_width,
    menu_setup_titexdata_06_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 menu_setup_titexdata_06_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_setup/menu_setup_titexdata_06_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(menu_setup_titexdata_06_texs_tex) ==
                  menu_setup_titexdata_06_texs_tex_width * menu_setup_titexdata_06_texs_tex_height / 2,
              "The dimensions of `menu_setup_titexdata_06_texs_tex` does not match the size of the actual texture");

#elif VERSION_CN

/* titexdata_01 */

extern u8 menu_setup_titexdata_01_texs_tex[];

TiTexDataTextures menu_setup_titexdata_01_texs = {
    NULL,
    menu_setup_titexdata_01_texs_tex,
};

#define menu_setup_titexdata_01_texs_tex_width 64
#define menu_setup_titexdata_01_texs_tex_height 64

u16 menu_setup_titexdata_01_info[] = {
    menu_setup_titexdata_01_texs_tex_width,
    menu_setup_titexdata_01_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 menu_setup_titexdata_01_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_setup/menu_setup_titexdata_01_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(menu_setup_titexdata_01_texs_tex) ==
                  menu_setup_titexdata_01_texs_tex_width * menu_setup_titexdata_01_texs_tex_height / 2,
              "The dimensions of `menu_setup_titexdata_01_texs_tex` does not match the size of the actual texture");

/* titexdata_02 */

extern u8 menu_setup_titexdata_02_texs_tex[];

TiTexDataTextures menu_setup_titexdata_02_texs = {
    NULL,
    menu_setup_titexdata_02_texs_tex,
};

#define menu_setup_titexdata_02_texs_tex_width 48
#define menu_setup_titexdata_02_texs_tex_height 48

u16 menu_setup_titexdata_02_info[] = {
    menu_setup_titexdata_02_texs_tex_width,
    menu_setup_titexdata_02_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 menu_setup_titexdata_02_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_setup/menu_setup_titexdata_02_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(menu_setup_titexdata_02_texs_tex) ==
                  menu_setup_titexdata_02_texs_tex_width * menu_setup_titexdata_02_texs_tex_height / 2,
              "The dimensions of `menu_setup_titexdata_02_texs_tex` does not match the size of the actual texture");

/* titexdata_03 */

extern u8 menu_setup_titexdata_03_texs_tex[];

TiTexDataTextures menu_setup_titexdata_03_texs = {
    NULL,
    menu_setup_titexdata_03_texs_tex,
};

#define menu_setup_titexdata_03_texs_tex_width 56
#define menu_setup_titexdata_03_texs_tex_height 48

u16 menu_setup_titexdata_03_info[] = {
    menu_setup_titexdata_03_texs_tex_width,
    menu_setup_titexdata_03_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_TILE,
};

u8 menu_setup_titexdata_03_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_setup/menu_setup_titexdata_03_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(menu_setup_titexdata_03_texs_tex) ==
                  menu_setup_titexdata_03_texs_tex_width * menu_setup_titexdata_03_texs_tex_height / 2,
              "The dimensions of `menu_setup_titexdata_03_texs_tex` does not match the size of the actual texture");

/* titexdata_04 */

extern u8 menu_setup_titexdata_04_texs_tex[];

TiTexDataTextures menu_setup_titexdata_04_texs = {
    NULL,
    menu_setup_titexdata_04_texs_tex,
};

#define menu_setup_titexdata_04_texs_tex_width 48
#define menu_setup_titexdata_04_texs_tex_height 48

u16 menu_setup_titexdata_04_info[] = {
    menu_setup_titexdata_04_texs_tex_width,
    menu_setup_titexdata_04_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 menu_setup_titexdata_04_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_setup/menu_setup_titexdata_04_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(menu_setup_titexdata_04_texs_tex) ==
                  menu_setup_titexdata_04_texs_tex_width * menu_setup_titexdata_04_texs_tex_height / 2,
              "The dimensions of `menu_setup_titexdata_04_texs_tex` does not match the size of the actual texture");

/* titexdata_05 */

extern u8 menu_setup_titexdata_05_texs_tex[];

TiTexDataTextures menu_setup_titexdata_05_texs = {
    NULL,
    menu_setup_titexdata_05_texs_tex,
};

#define menu_setup_titexdata_05_texs_tex_width 32
#define menu_setup_titexdata_05_texs_tex_height 132

u16 menu_setup_titexdata_05_info[] = {
    menu_setup_titexdata_05_texs_tex_width,
    menu_setup_titexdata_05_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 menu_setup_titexdata_05_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_setup/menu_setup_titexdata_05_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(menu_setup_titexdata_05_texs_tex) ==
                  menu_setup_titexdata_05_texs_tex_width * menu_setup_titexdata_05_texs_tex_height / 2,
              "The dimensions of `menu_setup_titexdata_05_texs_tex` does not match the size of the actual texture");

/* titexdata_06 */

extern u8 menu_setup_titexdata_06_texs_tex[];

TiTexDataTextures menu_setup_titexdata_06_texs = {
    NULL,
    menu_setup_titexdata_06_texs_tex,
};

#define menu_setup_titexdata_06_texs_tex_width 48
#define menu_setup_titexdata_06_texs_tex_height 16

u16 menu_setup_titexdata_06_info[] = {
    menu_setup_titexdata_06_texs_tex_width,
    menu_setup_titexdata_06_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 menu_setup_titexdata_06_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_setup/menu_setup_titexdata_06_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(menu_setup_titexdata_06_texs_tex) ==
                  menu_setup_titexdata_06_texs_tex_width * menu_setup_titexdata_06_texs_tex_height / 2,
              "The dimensions of `menu_setup_titexdata_06_texs_tex` does not match the size of the actual texture");

#endif

/* titexdata_07 */

extern u16 menu_setup_titexdata_07_texs_tex[];

TiTexDataTextures menu_setup_titexdata_07_texs = {
    NULL,
    menu_setup_titexdata_07_texs_tex,
};

#define menu_setup_titexdata_07_texs_tex_width 16
#define menu_setup_titexdata_07_texs_tex_height 120

u16 menu_setup_titexdata_07_info[] = {
    menu_setup_titexdata_07_texs_tex_width,
    menu_setup_titexdata_07_texs_tex_height,
    TITEX_FORMAT_16,
    TITEX_FLAGS_BLOCK,
};

u16 menu_setup_titexdata_07_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_setup/menu_setup_titexdata_07_texs_tex.rgba16.inc"
};
static_assert(ARRAY_COUNT(menu_setup_titexdata_07_texs_tex) ==
                  menu_setup_titexdata_07_texs_tex_width * menu_setup_titexdata_07_texs_tex_height,
              "The dimensions of `menu_setup_titexdata_07_texs_tex` does not match the size of the actual texture");

/* titexdata_08 */

extern u16 menu_setup_titexdata_08_texs_tex[];

TiTexDataTextures menu_setup_titexdata_08_texs = {
    NULL,
    menu_setup_titexdata_08_texs_tex,
};

#define menu_setup_titexdata_08_texs_tex_width 32
#define menu_setup_titexdata_08_texs_tex_height 132

u16 menu_setup_titexdata_08_info[] = {
    menu_setup_titexdata_08_texs_tex_width,
    menu_setup_titexdata_08_texs_tex_height,
    TITEX_FORMAT_16,
    TITEX_FLAGS_BLOCK,
};

u16 menu_setup_titexdata_08_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_setup/menu_setup_titexdata_08_texs_tex.rgba16.inc"
};
static_assert(ARRAY_COUNT(menu_setup_titexdata_08_texs_tex) ==
                  menu_setup_titexdata_08_texs_tex_width * menu_setup_titexdata_08_texs_tex_height,
              "The dimensions of `menu_setup_titexdata_08_texs_tex` does not match the size of the actual texture");

/* titexdata_09 */

extern u16 menu_setup_titexdata_09_texs_tex[];

TiTexDataTextures menu_setup_titexdata_09_texs = {
    NULL,
    menu_setup_titexdata_09_texs_tex,
};

#define menu_setup_titexdata_09_texs_tex_width 64
#define menu_setup_titexdata_09_texs_tex_height 64

u16 menu_setup_titexdata_09_info[] = {
    menu_setup_titexdata_09_texs_tex_width,
    menu_setup_titexdata_09_texs_tex_height,
    TITEX_FORMAT_16,
    TITEX_FLAGS_BLOCK,
};

u16 menu_setup_titexdata_09_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_setup/menu_setup_titexdata_09_texs_tex.rgba16.inc"
};
static_assert(ARRAY_COUNT(menu_setup_titexdata_09_texs_tex) ==
                  menu_setup_titexdata_09_texs_tex_width * menu_setup_titexdata_09_texs_tex_height,
              "The dimensions of `menu_setup_titexdata_09_texs_tex` does not match the size of the actual texture");

/* titexdata_10 */

extern u16 menu_setup_titexdata_10_texs_tex[];

TiTexDataTextures menu_setup_titexdata_10_texs = {
    NULL,
    menu_setup_titexdata_10_texs_tex,
};

#define menu_setup_titexdata_10_texs_tex_width 48
#define menu_setup_titexdata_10_texs_tex_height 48

u16 menu_setup_titexdata_10_info[] = {
    menu_setup_titexdata_10_texs_tex_width,
    menu_setup_titexdata_10_texs_tex_height,
    TITEX_FORMAT_16,
    TITEX_FLAGS_BLOCK,
};

u16 menu_setup_titexdata_10_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_setup/menu_setup_titexdata_10_texs_tex.rgba16.inc"
};
static_assert(ARRAY_COUNT(menu_setup_titexdata_10_texs_tex) ==
                  menu_setup_titexdata_10_texs_tex_width * menu_setup_titexdata_10_texs_tex_height,
              "The dimensions of `menu_setup_titexdata_10_texs_tex` does not match the size of the actual texture");

#if VERSION_US || VERSION_GW

/* titexdata_11 */

extern u16 menu_setup_titexdata_11_texs_tex[];

TiTexDataTextures menu_setup_titexdata_11_texs = {
    NULL,
    menu_setup_titexdata_11_texs_tex,
};

#define menu_setup_titexdata_11_texs_tex_width 48
#define menu_setup_titexdata_11_texs_tex_height 16

u16 menu_setup_titexdata_11_info[] = {
    menu_setup_titexdata_11_texs_tex_width,
    menu_setup_titexdata_11_texs_tex_height,
    TITEX_FORMAT_16,
    TITEX_FLAGS_BLOCK,
};

u16 menu_setup_titexdata_11_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_setup/menu_setup_titexdata_11_texs_tex.rgba16.inc"
};
static_assert(ARRAY_COUNT(menu_setup_titexdata_11_texs_tex) ==
                  menu_setup_titexdata_11_texs_tex_width * menu_setup_titexdata_11_texs_tex_height,
              "The dimensions of `menu_setup_titexdata_11_texs_tex` does not match the size of the actual texture");

/* titexdata_12 */

extern u16 menu_setup_titexdata_12_texs_tex[];

TiTexDataTextures menu_setup_titexdata_12_texs = {
    NULL,
    menu_setup_titexdata_12_texs_tex,
};

#define menu_setup_titexdata_12_texs_tex_width 56
#define menu_setup_titexdata_12_texs_tex_height 48

u16 menu_setup_titexdata_12_info[] = {
    menu_setup_titexdata_12_texs_tex_width,
    menu_setup_titexdata_12_texs_tex_height,
    TITEX_FORMAT_16,
    TITEX_FLAGS_TILE,
};

u16 menu_setup_titexdata_12_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_setup/menu_setup_titexdata_12_texs_tex.rgba16.inc"
};
static_assert(ARRAY_COUNT(menu_setup_titexdata_12_texs_tex) ==
                  menu_setup_titexdata_12_texs_tex_width * menu_setup_titexdata_12_texs_tex_height,
              "The dimensions of `menu_setup_titexdata_12_texs_tex` does not match the size of the actual texture");

/* titexdata_13 */

extern u16 menu_setup_titexdata_13_texs_tex[];

TiTexDataTextures menu_setup_titexdata_13_texs = {
    NULL,
    menu_setup_titexdata_13_texs_tex,
};

#define menu_setup_titexdata_13_texs_tex_width 48
#define menu_setup_titexdata_13_texs_tex_height 48

u16 menu_setup_titexdata_13_info[] = {
    menu_setup_titexdata_13_texs_tex_width,
    menu_setup_titexdata_13_texs_tex_height,
    TITEX_FORMAT_16,
    TITEX_FLAGS_BLOCK,
};

u16 menu_setup_titexdata_13_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_setup/menu_setup_titexdata_13_texs_tex.rgba16.inc"
};
static_assert(ARRAY_COUNT(menu_setup_titexdata_13_texs_tex) ==
                  menu_setup_titexdata_13_texs_tex_width * menu_setup_titexdata_13_texs_tex_height,
              "The dimensions of `menu_setup_titexdata_13_texs_tex` does not match the size of the actual texture");

#elif VERSION_CN

/* titexdata_11 */

extern u16 menu_setup_titexdata_11_texs_tex[];

TiTexDataTextures menu_setup_titexdata_11_texs = {
    NULL,
    menu_setup_titexdata_11_texs_tex,
};

#define menu_setup_titexdata_11_texs_tex_width 56
#define menu_setup_titexdata_11_texs_tex_height 48

u16 menu_setup_titexdata_11_info[] = {
    menu_setup_titexdata_11_texs_tex_width,
    menu_setup_titexdata_11_texs_tex_height,
    TITEX_FORMAT_16,
    TITEX_FLAGS_TILE,
};

u16 menu_setup_titexdata_11_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_setup/menu_setup_titexdata_11_texs_tex.rgba16.inc"
};
static_assert(ARRAY_COUNT(menu_setup_titexdata_11_texs_tex) ==
                  menu_setup_titexdata_11_texs_tex_width * menu_setup_titexdata_11_texs_tex_height,
              "The dimensions of `menu_setup_titexdata_11_texs_tex` does not match the size of the actual texture");

/* titexdata_12 */

extern u16 menu_setup_titexdata_12_texs_tex[];

TiTexDataTextures menu_setup_titexdata_12_texs = {
    NULL,
    menu_setup_titexdata_12_texs_tex,
};

#define menu_setup_titexdata_12_texs_tex_width 48
#define menu_setup_titexdata_12_texs_tex_height 48

u16 menu_setup_titexdata_12_info[] = {
    menu_setup_titexdata_12_texs_tex_width,
    menu_setup_titexdata_12_texs_tex_height,
    TITEX_FORMAT_16,
    TITEX_FLAGS_BLOCK,
};

u16 menu_setup_titexdata_12_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_setup/menu_setup_titexdata_12_texs_tex.rgba16.inc"
};
static_assert(ARRAY_COUNT(menu_setup_titexdata_12_texs_tex) ==
                  menu_setup_titexdata_12_texs_tex_width * menu_setup_titexdata_12_texs_tex_height,
              "The dimensions of `menu_setup_titexdata_12_texs_tex` does not match the size of the actual texture");

/* titexdata_13 */

extern u16 menu_setup_titexdata_13_texs_tex[];

TiTexDataTextures menu_setup_titexdata_13_texs = {
    NULL,
    menu_setup_titexdata_13_texs_tex,
};

#define menu_setup_titexdata_13_texs_tex_width 48
#define menu_setup_titexdata_13_texs_tex_height 16

u16 menu_setup_titexdata_13_info[] = {
    menu_setup_titexdata_13_texs_tex_width,
    menu_setup_titexdata_13_texs_tex_height,
    TITEX_FORMAT_16,
    TITEX_FLAGS_BLOCK,
};

u16 menu_setup_titexdata_13_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_setup/menu_setup_titexdata_13_texs_tex.rgba16.inc"
};
static_assert(ARRAY_COUNT(menu_setup_titexdata_13_texs_tex) ==
                  menu_setup_titexdata_13_texs_tex_width * menu_setup_titexdata_13_texs_tex_height,
              "The dimensions of `menu_setup_titexdata_13_texs_tex` does not match the size of the actual texture");

#endif

/* titexdata_14 */

extern u16 menu_setup_titexdata_14_texs_tlut[];
extern u8 menu_setup_titexdata_14_texs_tex[];

TiTexDataTextures menu_setup_titexdata_14_texs = {
    menu_setup_titexdata_14_texs_tlut,
    menu_setup_titexdata_14_texs_tex,
};

#define menu_setup_titexdata_14_texs_tex_width 72
#define menu_setup_titexdata_14_texs_tex_height 360

u16 menu_setup_titexdata_14_info[] = {
    menu_setup_titexdata_14_texs_tex_width,
    menu_setup_titexdata_14_texs_tex_height,
    TITEX_FORMAT_8,
    TITEX_FLAGS_BLOCK,
};

u16 menu_setup_titexdata_14_texs_tlut[] ALIGNED(8) = {
#include "assets/menu/menu_setup/menu_setup_titexdata_14_texs_tlut.rgba16.inc"
};
static_assert(ARRAY_COUNT(menu_setup_titexdata_14_texs_tlut) == 16 * 16,
              "The dimensions of `menu_setup_titexdata_14_texs_tlut` does not match the size of the actual tlut");

u8 menu_setup_titexdata_14_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_setup/menu_setup_titexdata_14_texs_tex.i8.inc"
};
static_assert(ARRAY_COUNT(menu_setup_titexdata_14_texs_tex) ==
                  menu_setup_titexdata_14_texs_tex_width * menu_setup_titexdata_14_texs_tex_height,
              "The dimensions of `menu_setup_titexdata_14_texs_tex` does not match the size of the actual texture");

/* titexdata_15 */

extern u16 menu_setup_titexdata_15_texs_tlut[];
extern u8 menu_setup_titexdata_15_texs_tex[];

TiTexDataTextures menu_setup_titexdata_15_texs = {
    menu_setup_titexdata_15_texs_tlut,
    menu_setup_titexdata_15_texs_tex,
};

#define menu_setup_titexdata_15_texs_tex_width 40
#define menu_setup_titexdata_15_texs_tex_height 24

u16 menu_setup_titexdata_15_info[] = {
    menu_setup_titexdata_15_texs_tex_width,
    menu_setup_titexdata_15_texs_tex_height,
    TITEX_FORMAT_8,
    TITEX_FLAGS_BLOCK,
};

u16 menu_setup_titexdata_15_texs_tlut[] ALIGNED(8) = {
#include "assets/menu/menu_setup/menu_setup_titexdata_15_texs_tlut.rgba16.inc"
};
static_assert(ARRAY_COUNT(menu_setup_titexdata_15_texs_tlut) == 16 * 16,
              "The dimensions of `menu_setup_titexdata_15_texs_tlut` does not match the size of the actual tlut");

u8 menu_setup_titexdata_15_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_setup/menu_setup_titexdata_15_texs_tex.i8.inc"
};
static_assert(ARRAY_COUNT(menu_setup_titexdata_15_texs_tex) ==
                  menu_setup_titexdata_15_texs_tex_width * menu_setup_titexdata_15_texs_tex_height,
              "The dimensions of `menu_setup_titexdata_15_texs_tex` does not match the size of the actual texture");

/* titexdata_16 */

extern u16 menu_setup_titexdata_16_texs_tlut[];
extern u8 menu_setup_titexdata_16_texs_tex[];

TiTexDataTextures menu_setup_titexdata_16_texs = {
    menu_setup_titexdata_16_texs_tlut,
    menu_setup_titexdata_16_texs_tex,
};

#define menu_setup_titexdata_16_texs_tex_width 16
#define menu_setup_titexdata_16_texs_tex_height 24

u16 menu_setup_titexdata_16_info[] = {
    menu_setup_titexdata_16_texs_tex_width,
    menu_setup_titexdata_16_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u16 menu_setup_titexdata_16_texs_tlut[] ALIGNED(8) = {
#include "assets/menu/menu_setup/menu_setup_titexdata_16_texs_tlut.rgba16.inc"
};
static_assert(ARRAY_COUNT(menu_setup_titexdata_16_texs_tlut) == 4 * 4,
              "The dimensions of `menu_setup_titexdata_16_texs_tlut` does not match the size of the actual tlut");

u8 menu_setup_titexdata_16_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_setup/menu_setup_titexdata_16_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(menu_setup_titexdata_16_texs_tex) ==
                  menu_setup_titexdata_16_texs_tex_width * menu_setup_titexdata_16_texs_tex_height / 2,
              "The dimensions of `menu_setup_titexdata_16_texs_tex` does not match the size of the actual texture");

/* titexdata_17 */

extern u16 menu_setup_titexdata_17_texs_tlut[];
extern u8 menu_setup_titexdata_17_texs_tex[];

TiTexDataTextures menu_setup_titexdata_17_texs = {
    menu_setup_titexdata_17_texs_tlut,
    menu_setup_titexdata_17_texs_tex,
};

#define menu_setup_titexdata_17_texs_tex_width 32
#define menu_setup_titexdata_17_texs_tex_height 132

u16 menu_setup_titexdata_17_info[] = {
    menu_setup_titexdata_17_texs_tex_width,
    menu_setup_titexdata_17_texs_tex_height,
    TITEX_FORMAT_8,
    TITEX_FLAGS_BLOCK,
};

u16 menu_setup_titexdata_17_texs_tlut[] ALIGNED(8) = {
#include "assets/menu/menu_setup/menu_setup_titexdata_17_texs_tlut.rgba16.inc"
};
static_assert(ARRAY_COUNT(menu_setup_titexdata_17_texs_tlut) == 16 * 16,
              "The dimensions of `menu_setup_titexdata_17_texs_tlut` does not match the size of the actual tlut");

u8 menu_setup_titexdata_17_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_setup/menu_setup_titexdata_17_texs_tex.i8.inc"
};
static_assert(ARRAY_COUNT(menu_setup_titexdata_17_texs_tex) ==
                  menu_setup_titexdata_17_texs_tex_width * menu_setup_titexdata_17_texs_tex_height,
              "The dimensions of `menu_setup_titexdata_17_texs_tex` does not match the size of the actual texture");

/* titexdata_18 */

extern u16 menu_setup_titexdata_18_texs_tlut[];
extern u8 menu_setup_titexdata_18_texs_tex[];

TiTexDataTextures menu_setup_titexdata_18_texs = {
    menu_setup_titexdata_18_texs_tlut,
    menu_setup_titexdata_18_texs_tex,
};

#define menu_setup_titexdata_18_texs_tex_width 304
#define menu_setup_titexdata_18_texs_tex_height 91

u16 menu_setup_titexdata_18_info[] = {
    menu_setup_titexdata_18_texs_tex_width,
    menu_setup_titexdata_18_texs_tex_height,
    TITEX_FORMAT_8,
    TITEX_FLAGS_BLOCK,
};

u16 menu_setup_titexdata_18_texs_tlut[] ALIGNED(8) = {
#include "assets/menu/menu_setup/menu_setup_titexdata_18_texs_tlut.rgba16.inc"
};
static_assert(ARRAY_COUNT(menu_setup_titexdata_18_texs_tlut) == 16 * 16,
              "The dimensions of `menu_setup_titexdata_18_texs_tlut` does not match the size of the actual tlut");

u8 menu_setup_titexdata_18_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_setup/menu_setup_titexdata_18_texs_tex.i8.inc"
};
static_assert(ARRAY_COUNT(menu_setup_titexdata_18_texs_tex) ==
                  menu_setup_titexdata_18_texs_tex_width * menu_setup_titexdata_18_texs_tex_height,
              "The dimensions of `menu_setup_titexdata_18_texs_tex` does not match the size of the actual texture");

/* titexdata_19 */

extern u16 menu_setup_titexdata_19_texs_tlut[];
extern u8 menu_setup_titexdata_19_texs_tex[];

TiTexDataTextures menu_setup_titexdata_19_texs = {
    menu_setup_titexdata_19_texs_tlut,
    menu_setup_titexdata_19_texs_tex,
};

#define menu_setup_titexdata_19_texs_tex_width 80
#define menu_setup_titexdata_19_texs_tex_height 11

u16 menu_setup_titexdata_19_info[] = {
    menu_setup_titexdata_19_texs_tex_width,
    menu_setup_titexdata_19_texs_tex_height,
    TITEX_FORMAT_8,
    TITEX_FLAGS_BLOCK,
};

u16 menu_setup_titexdata_19_texs_tlut[] ALIGNED(8) = {
#include "assets/menu/menu_setup/menu_setup_titexdata_19_texs_tlut.rgba16.inc"
};
static_assert(ARRAY_COUNT(menu_setup_titexdata_19_texs_tlut) == 16 * 16,
              "The dimensions of `menu_setup_titexdata_19_texs_tlut` does not match the size of the actual tlut");

u8 menu_setup_titexdata_19_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_setup/menu_setup_titexdata_19_texs_tex.i8.inc"
};
static_assert(ARRAY_COUNT(menu_setup_titexdata_19_texs_tex) ==
                  menu_setup_titexdata_19_texs_tex_width * menu_setup_titexdata_19_texs_tex_height,
              "The dimensions of `menu_setup_titexdata_19_texs_tex` does not match the size of the actual texture");

/* titexdata_20 */

extern u8 menu_setup_titexdata_20_texs_tex[];

TiTexDataTextures menu_setup_titexdata_20_texs = {
    NULL,
    menu_setup_titexdata_20_texs_tex,
};

#define menu_setup_titexdata_20_texs_tex_width 48
#define menu_setup_titexdata_20_texs_tex_height 30

u16 menu_setup_titexdata_20_info[] = {
    menu_setup_titexdata_20_texs_tex_width,
    menu_setup_titexdata_20_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 menu_setup_titexdata_20_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_setup/menu_setup_titexdata_20_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(menu_setup_titexdata_20_texs_tex) ==
                  menu_setup_titexdata_20_texs_tex_width * menu_setup_titexdata_20_texs_tex_height / 2,
              "The dimensions of `menu_setup_titexdata_20_texs_tex` does not match the size of the actual texture");

/* titexdata_21 */

extern u8 menu_setup_titexdata_21_texs_tex[];

TiTexDataTextures menu_setup_titexdata_21_texs = {
    NULL,
    menu_setup_titexdata_21_texs_tex,
};

#define menu_setup_titexdata_21_texs_tex_width 48
#define menu_setup_titexdata_21_texs_tex_height 30

u16 menu_setup_titexdata_21_info[] = {
    menu_setup_titexdata_21_texs_tex_width,
    menu_setup_titexdata_21_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 menu_setup_titexdata_21_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_setup/menu_setup_titexdata_21_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(menu_setup_titexdata_21_texs_tex) ==
                  menu_setup_titexdata_21_texs_tex_width * menu_setup_titexdata_21_texs_tex_height / 2,
              "The dimensions of `menu_setup_titexdata_21_texs_tex` does not match the size of the actual texture");

/* titexdata_22 */

extern u8 menu_setup_titexdata_22_texs_tex[];

TiTexDataTextures menu_setup_titexdata_22_texs = {
    NULL,
    menu_setup_titexdata_22_texs_tex,
};

#define menu_setup_titexdata_22_texs_tex_width 48
#define menu_setup_titexdata_22_texs_tex_height 30

u16 menu_setup_titexdata_22_info[] = {
    menu_setup_titexdata_22_texs_tex_width,
    menu_setup_titexdata_22_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 menu_setup_titexdata_22_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_setup/menu_setup_titexdata_22_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(menu_setup_titexdata_22_texs_tex) ==
                  menu_setup_titexdata_22_texs_tex_width * menu_setup_titexdata_22_texs_tex_height / 2,
              "The dimensions of `menu_setup_titexdata_22_texs_tex` does not match the size of the actual texture");

/* titexdata_23 */

extern u8 menu_setup_titexdata_23_texs_tex[];

TiTexDataTextures menu_setup_titexdata_23_texs = {
    NULL,
    menu_setup_titexdata_23_texs_tex,
};

#define menu_setup_titexdata_23_texs_tex_width 48
#define menu_setup_titexdata_23_texs_tex_height 30

u16 menu_setup_titexdata_23_info[] = {
    menu_setup_titexdata_23_texs_tex_width,
    menu_setup_titexdata_23_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 menu_setup_titexdata_23_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_setup/menu_setup_titexdata_23_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(menu_setup_titexdata_23_texs_tex) ==
                  menu_setup_titexdata_23_texs_tex_width * menu_setup_titexdata_23_texs_tex_height / 2,
              "The dimensions of `menu_setup_titexdata_23_texs_tex` does not match the size of the actual texture");

/* titexdata_24 */

extern u8 menu_setup_titexdata_24_texs_tex[];

TiTexDataTextures menu_setup_titexdata_24_texs = {
    NULL,
    menu_setup_titexdata_24_texs_tex,
};

#define menu_setup_titexdata_24_texs_tex_width 48
#define menu_setup_titexdata_24_texs_tex_height 30

u16 menu_setup_titexdata_24_info[] = {
    menu_setup_titexdata_24_texs_tex_width,
    menu_setup_titexdata_24_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 menu_setup_titexdata_24_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_setup/menu_setup_titexdata_24_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(menu_setup_titexdata_24_texs_tex) ==
                  menu_setup_titexdata_24_texs_tex_width * menu_setup_titexdata_24_texs_tex_height / 2,
              "The dimensions of `menu_setup_titexdata_24_texs_tex` does not match the size of the actual texture");

/* titexdata_25 */

extern u8 menu_setup_titexdata_25_texs_tex[];

TiTexDataTextures menu_setup_titexdata_25_texs = {
    NULL,
    menu_setup_titexdata_25_texs_tex,
};

#define menu_setup_titexdata_25_texs_tex_width 48
#define menu_setup_titexdata_25_texs_tex_height 30

u16 menu_setup_titexdata_25_info[] = {
    menu_setup_titexdata_25_texs_tex_width,
    menu_setup_titexdata_25_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 menu_setup_titexdata_25_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_setup/menu_setup_titexdata_25_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(menu_setup_titexdata_25_texs_tex) ==
                  menu_setup_titexdata_25_texs_tex_width * menu_setup_titexdata_25_texs_tex_height / 2,
              "The dimensions of `menu_setup_titexdata_25_texs_tex` does not match the size of the actual texture");

/* titexdata_26 */

extern u8 menu_setup_titexdata_26_texs_tex[];

TiTexDataTextures menu_setup_titexdata_26_texs = {
    NULL,
    menu_setup_titexdata_26_texs_tex,
};

#define menu_setup_titexdata_26_texs_tex_width 48
#define menu_setup_titexdata_26_texs_tex_height 30

u16 menu_setup_titexdata_26_info[] = {
    menu_setup_titexdata_26_texs_tex_width,
    menu_setup_titexdata_26_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 menu_setup_titexdata_26_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_setup/menu_setup_titexdata_26_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(menu_setup_titexdata_26_texs_tex) ==
                  menu_setup_titexdata_26_texs_tex_width * menu_setup_titexdata_26_texs_tex_height / 2,
              "The dimensions of `menu_setup_titexdata_26_texs_tex` does not match the size of the actual texture");

/* titexdata_27 */

extern u8 menu_setup_titexdata_27_texs_tex[];

TiTexDataTextures menu_setup_titexdata_27_texs = {
    NULL,
    menu_setup_titexdata_27_texs_tex,
};

#define menu_setup_titexdata_27_texs_tex_width 48
#define menu_setup_titexdata_27_texs_tex_height 20

u16 menu_setup_titexdata_27_info[] = {
    menu_setup_titexdata_27_texs_tex_width,
    menu_setup_titexdata_27_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 menu_setup_titexdata_27_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_setup/menu_setup_titexdata_27_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(menu_setup_titexdata_27_texs_tex) ==
                  menu_setup_titexdata_27_texs_tex_width * menu_setup_titexdata_27_texs_tex_height / 2,
              "The dimensions of `menu_setup_titexdata_27_texs_tex` does not match the size of the actual texture");

/* titexdata_28 */

extern u8 menu_setup_titexdata_28_texs_tex[];

TiTexDataTextures menu_setup_titexdata_28_texs = {
    NULL,
    menu_setup_titexdata_28_texs_tex,
};

#define menu_setup_titexdata_28_texs_tex_width 48
#define menu_setup_titexdata_28_texs_tex_height 20

u16 menu_setup_titexdata_28_info[] = {
    menu_setup_titexdata_28_texs_tex_width,
    menu_setup_titexdata_28_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 menu_setup_titexdata_28_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_setup/menu_setup_titexdata_28_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(menu_setup_titexdata_28_texs_tex) ==
                  menu_setup_titexdata_28_texs_tex_width * menu_setup_titexdata_28_texs_tex_height / 2,
              "The dimensions of `menu_setup_titexdata_28_texs_tex` does not match the size of the actual texture");

/* titexdata_29 */

extern u8 menu_setup_titexdata_29_texs_tex[];

TiTexDataTextures menu_setup_titexdata_29_texs = {
    NULL,
    menu_setup_titexdata_29_texs_tex,
};

#define menu_setup_titexdata_29_texs_tex_width 48
#define menu_setup_titexdata_29_texs_tex_height 20

u16 menu_setup_titexdata_29_info[] = {
    menu_setup_titexdata_29_texs_tex_width,
    menu_setup_titexdata_29_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 menu_setup_titexdata_29_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_setup/menu_setup_titexdata_29_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(menu_setup_titexdata_29_texs_tex) ==
                  menu_setup_titexdata_29_texs_tex_width * menu_setup_titexdata_29_texs_tex_height / 2,
              "The dimensions of `menu_setup_titexdata_29_texs_tex` does not match the size of the actual texture");

/* titexdata_30 */

extern u8 menu_setup_titexdata_30_texs_tex[];

TiTexDataTextures menu_setup_titexdata_30_texs = {
    NULL,
    menu_setup_titexdata_30_texs_tex,
};

#define menu_setup_titexdata_30_texs_tex_width 48
#define menu_setup_titexdata_30_texs_tex_height 20

u16 menu_setup_titexdata_30_info[] = {
    menu_setup_titexdata_30_texs_tex_width,
    menu_setup_titexdata_30_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 menu_setup_titexdata_30_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_setup/menu_setup_titexdata_30_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(menu_setup_titexdata_30_texs_tex) ==
                  menu_setup_titexdata_30_texs_tex_width * menu_setup_titexdata_30_texs_tex_height / 2,
              "The dimensions of `menu_setup_titexdata_30_texs_tex` does not match the size of the actual texture");

/* titexdata_31 */

extern u8 menu_setup_titexdata_31_texs_tex[];

TiTexDataTextures menu_setup_titexdata_31_texs = {
    NULL,
    menu_setup_titexdata_31_texs_tex,
};

#define menu_setup_titexdata_31_texs_tex_width 48
#define menu_setup_titexdata_31_texs_tex_height 20

u16 menu_setup_titexdata_31_info[] = {
    menu_setup_titexdata_31_texs_tex_width,
    menu_setup_titexdata_31_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 menu_setup_titexdata_31_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_setup/menu_setup_titexdata_31_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(menu_setup_titexdata_31_texs_tex) ==
                  menu_setup_titexdata_31_texs_tex_width * menu_setup_titexdata_31_texs_tex_height / 2,
              "The dimensions of `menu_setup_titexdata_31_texs_tex` does not match the size of the actual texture");

TiTexData menu_setup_titexdata[] = {
    { &menu_setup_titexdata_00_texs, menu_setup_titexdata_00_info },
#if VERSION_CN
    { &menu_setup_titexdata_05_texs, menu_setup_titexdata_05_info },
#endif
    { &menu_setup_titexdata_01_texs, menu_setup_titexdata_01_info },
    { &menu_setup_titexdata_02_texs, menu_setup_titexdata_02_info },
#if VERSION_CN
    { &menu_setup_titexdata_06_texs, menu_setup_titexdata_06_info },
#endif
    { &menu_setup_titexdata_03_texs, menu_setup_titexdata_03_info },
    { &menu_setup_titexdata_04_texs, menu_setup_titexdata_04_info },
#if VERSION_US || VERSION_GW
    { &menu_setup_titexdata_05_texs, menu_setup_titexdata_05_info },
    { &menu_setup_titexdata_06_texs, menu_setup_titexdata_06_info },
#endif
    { &menu_setup_titexdata_07_texs, menu_setup_titexdata_07_info },
    { &menu_setup_titexdata_08_texs, menu_setup_titexdata_08_info },
    { &menu_setup_titexdata_09_texs, menu_setup_titexdata_09_info },
    { &menu_setup_titexdata_10_texs, menu_setup_titexdata_10_info },
#if VERSION_CN
    { &menu_setup_titexdata_13_texs, menu_setup_titexdata_13_info },
#endif
    { &menu_setup_titexdata_11_texs, menu_setup_titexdata_11_info },
    { &menu_setup_titexdata_12_texs, menu_setup_titexdata_12_info },
#if VERSION_US || VERSION_GW
    { &menu_setup_titexdata_13_texs, menu_setup_titexdata_13_info },
#endif
    { &menu_setup_titexdata_14_texs, menu_setup_titexdata_14_info },
    { &menu_setup_titexdata_15_texs, menu_setup_titexdata_15_info },
    { &menu_setup_titexdata_16_texs, menu_setup_titexdata_16_info },
    { &menu_setup_titexdata_17_texs, menu_setup_titexdata_17_info },
    { &menu_setup_titexdata_18_texs, menu_setup_titexdata_18_info },
    { &menu_setup_titexdata_19_texs, menu_setup_titexdata_19_info },
    { &menu_setup_titexdata_20_texs, menu_setup_titexdata_20_info },
    { &menu_setup_titexdata_21_texs, menu_setup_titexdata_21_info },
    { &menu_setup_titexdata_22_texs, menu_setup_titexdata_22_info },
    { &menu_setup_titexdata_23_texs, menu_setup_titexdata_23_info },
    { &menu_setup_titexdata_24_texs, menu_setup_titexdata_24_info },
    { &menu_setup_titexdata_25_texs, menu_setup_titexdata_25_info },
    { &menu_setup_titexdata_26_texs, menu_setup_titexdata_26_info },
    { &menu_setup_titexdata_27_texs, menu_setup_titexdata_27_info },
    { &menu_setup_titexdata_28_texs, menu_setup_titexdata_28_info },
    { &menu_setup_titexdata_29_texs, menu_setup_titexdata_29_info },
    { &menu_setup_titexdata_30_texs, menu_setup_titexdata_30_info },
    { &menu_setup_titexdata_31_texs, menu_setup_titexdata_31_info },
};

s32 menu_setup_titexdata_len = ARRAY_COUNT(menu_setup_titexdata);

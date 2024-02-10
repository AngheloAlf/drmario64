#include "tex_func.h"

#include "libc/assert.h"
#include "macros_defines.h"
#include "alignment.h"

extern TiTexData menu_level_titexdata[];
extern s32 menu_level_titexdata_len;

TiTexDataHeader menu_level_header = {
    menu_level_titexdata,
    &menu_level_titexdata_len,
};

/* titexdata_00 */

extern u16 menu_level_titexdata_00_texs_tlut[];
extern u8 menu_level_titexdata_00_texs_tex[];

TiTexDataTextures menu_level_titexdata_00_texs = {
    menu_level_titexdata_00_texs_tlut,
    menu_level_titexdata_00_texs_tex,
};

#define menu_level_titexdata_00_texs_tex_width 16
#define menu_level_titexdata_00_texs_tex_height 15

u16 menu_level_titexdata_00_info[] = {
    menu_level_titexdata_00_texs_tex_width,
    menu_level_titexdata_00_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u16 menu_level_titexdata_00_texs_tlut[] ALIGNED(8) = {
#include "assets/menu/menu_level/menu_level_titexdata_00_texs_tex.palette.inc"
};
static_assert(ARRAY_COUNT(menu_level_titexdata_00_texs_tlut) == 4 * 4,
              "The dimensions of `menu_level_titexdata_00_texs_tlut` does not match the size of the actual tlut");

u8 menu_level_titexdata_00_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_level/menu_level_titexdata_00_texs_tex.ci4.inc"
};
static_assert(ARRAY_COUNT(menu_level_titexdata_00_texs_tex) ==
                  menu_level_titexdata_00_texs_tex_width * menu_level_titexdata_00_texs_tex_height / 2,
              "The dimensions of `menu_level_titexdata_00_texs_tex` does not match the size of the actual texture");

/* titexdata_01 */

extern u16 menu_level_titexdata_01_texs_tlut[];
extern u8 menu_level_titexdata_01_texs_tex[];

TiTexDataTextures menu_level_titexdata_01_texs = {
    menu_level_titexdata_01_texs_tlut,
    menu_level_titexdata_01_texs_tex,
};

#define menu_level_titexdata_01_texs_tex_width 288
#define menu_level_titexdata_01_texs_tex_height 90

u16 menu_level_titexdata_01_info[] = {
    menu_level_titexdata_01_texs_tex_width,
    menu_level_titexdata_01_texs_tex_height,
    TITEX_FORMAT_8,
    TITEX_FLAGS_BLOCK,
};

u16 menu_level_titexdata_01_texs_tlut[] ALIGNED(8) = {
#include "assets/menu/menu_level/menu_level_titexdata_01_texs_tex.palette.inc"
};
static_assert(ARRAY_COUNT(menu_level_titexdata_01_texs_tlut) == 16 * 16,
              "The dimensions of `menu_level_titexdata_01_texs_tlut` does not match the size of the actual tlut");

u8 menu_level_titexdata_01_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_level/menu_level_titexdata_01_texs_tex.ci8.inc"
};
static_assert(ARRAY_COUNT(menu_level_titexdata_01_texs_tex) ==
                  menu_level_titexdata_01_texs_tex_width * menu_level_titexdata_01_texs_tex_height,
              "The dimensions of `menu_level_titexdata_01_texs_tex` does not match the size of the actual texture");

#if VERSION_US || VERSION_GW

/* titexdata_02 */

extern u16 menu_level_titexdata_02_texs_tlut[];
extern u8 menu_level_titexdata_02_texs_tex[];

TiTexDataTextures menu_level_titexdata_02_texs = {
    menu_level_titexdata_02_texs_tlut,
    menu_level_titexdata_02_texs_tex,
};

#define menu_level_titexdata_02_texs_tex_width 72
#define menu_level_titexdata_02_texs_tex_height 164

u16 menu_level_titexdata_02_info[] = {
    menu_level_titexdata_02_texs_tex_width,
    menu_level_titexdata_02_texs_tex_height,
    TITEX_FORMAT_8,
    TITEX_FLAGS_BLOCK,
};

u16 menu_level_titexdata_02_texs_tlut[] ALIGNED(8) = {
#include "assets/menu/menu_level/menu_level_titexdata_02_texs_tex.palette.inc"
};
static_assert(ARRAY_COUNT(menu_level_titexdata_02_texs_tlut) == 16 * 16,
              "The dimensions of `menu_level_titexdata_02_texs_tlut` does not match the size of the actual tlut");

u8 menu_level_titexdata_02_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_level/menu_level_titexdata_02_texs_tex.ci8.inc"
};
static_assert(ARRAY_COUNT(menu_level_titexdata_02_texs_tex) ==
                  menu_level_titexdata_02_texs_tex_width * menu_level_titexdata_02_texs_tex_height,
              "The dimensions of `menu_level_titexdata_02_texs_tex` does not match the size of the actual texture");

/* titexdata_03 */

extern u16 menu_level_titexdata_03_texs_tlut[];
extern u8 menu_level_titexdata_03_texs_tex[];

TiTexDataTextures menu_level_titexdata_03_texs = {
    menu_level_titexdata_03_texs_tlut,
    menu_level_titexdata_03_texs_tex,
};

#define menu_level_titexdata_03_texs_tex_width 56
#define menu_level_titexdata_03_texs_tex_height 150

u16 menu_level_titexdata_03_info[] = {
    menu_level_titexdata_03_texs_tex_width,
    menu_level_titexdata_03_texs_tex_height,
    TITEX_FORMAT_8,
    TITEX_FLAGS_BLOCK,
};

u16 menu_level_titexdata_03_texs_tlut[] ALIGNED(8) = {
#include "assets/menu/menu_level/menu_level_titexdata_03_texs_tex.palette.inc"
};
static_assert(ARRAY_COUNT(menu_level_titexdata_03_texs_tlut) == 16 * 16,
              "The dimensions of `menu_level_titexdata_03_texs_tlut` does not match the size of the actual tlut");

u8 menu_level_titexdata_03_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_level/menu_level_titexdata_03_texs_tex.ci8.inc"
};
static_assert(ARRAY_COUNT(menu_level_titexdata_03_texs_tex) ==
                  menu_level_titexdata_03_texs_tex_width * menu_level_titexdata_03_texs_tex_height,
              "The dimensions of `menu_level_titexdata_03_texs_tex` does not match the size of the actual texture");

/* titexdata_04 */

extern u16 menu_level_titexdata_04_texs_tlut[];
extern u8 menu_level_titexdata_04_texs_tex[];

TiTexDataTextures menu_level_titexdata_04_texs = {
    menu_level_titexdata_04_texs_tlut,
    menu_level_titexdata_04_texs_tex,
};

#define menu_level_titexdata_04_texs_tex_width 304
#define menu_level_titexdata_04_texs_tex_height 93

u16 menu_level_titexdata_04_info[] = {
    menu_level_titexdata_04_texs_tex_width,
    menu_level_titexdata_04_texs_tex_height,
    TITEX_FORMAT_8,
    TITEX_FLAGS_BLOCK,
};

u16 menu_level_titexdata_04_texs_tlut[] ALIGNED(8) = {
#include "assets/menu/menu_level/menu_level_titexdata_04_texs_tex.palette.inc"
};
static_assert(ARRAY_COUNT(menu_level_titexdata_04_texs_tlut) == 16 * 16,
              "The dimensions of `menu_level_titexdata_04_texs_tlut` does not match the size of the actual tlut");

u8 menu_level_titexdata_04_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_level/menu_level_titexdata_04_texs_tex.ci8.inc"
};
static_assert(ARRAY_COUNT(menu_level_titexdata_04_texs_tex) ==
                  menu_level_titexdata_04_texs_tex_width * menu_level_titexdata_04_texs_tex_height,
              "The dimensions of `menu_level_titexdata_04_texs_tex` does not match the size of the actual texture");

/* titexdata_05 */

extern u16 menu_level_titexdata_05_texs_tlut[];
extern u8 menu_level_titexdata_05_texs_tex[];

TiTexDataTextures menu_level_titexdata_05_texs = {
    menu_level_titexdata_05_texs_tlut,
    menu_level_titexdata_05_texs_tex,
};

#define menu_level_titexdata_05_texs_tex_width 270
#define menu_level_titexdata_05_texs_tex_height 93

u16 menu_level_titexdata_05_info[] = {
    menu_level_titexdata_05_texs_tex_width,
    menu_level_titexdata_05_texs_tex_height,
    TITEX_FORMAT_8,
    TITEX_FLAGS_TILE,
};

u16 menu_level_titexdata_05_texs_tlut[] ALIGNED(8) = {
#include "assets/menu/menu_level/menu_level_titexdata_05_texs_tex.palette.inc"
};
static_assert(ARRAY_COUNT(menu_level_titexdata_05_texs_tlut) == 16 * 16,
              "The dimensions of `menu_level_titexdata_05_texs_tlut` does not match the size of the actual tlut");

u8 menu_level_titexdata_05_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_level/menu_level_titexdata_05_texs_tex.ci8.inc"
};
static_assert(ARRAY_COUNT(menu_level_titexdata_05_texs_tex) ==
                  menu_level_titexdata_05_texs_tex_width * menu_level_titexdata_05_texs_tex_height,
              "The dimensions of `menu_level_titexdata_05_texs_tex` does not match the size of the actual texture");

/* titexdata_06 */

extern u16 menu_level_titexdata_06_texs_tlut[];
extern u8 menu_level_titexdata_06_texs_tex[];

TiTexDataTextures menu_level_titexdata_06_texs = {
    menu_level_titexdata_06_texs_tlut,
    menu_level_titexdata_06_texs_tex,
};

#define menu_level_titexdata_06_texs_tex_width 48
#define menu_level_titexdata_06_texs_tex_height 32

u16 menu_level_titexdata_06_info[] = {
    menu_level_titexdata_06_texs_tex_width,
    menu_level_titexdata_06_texs_tex_height,
    TITEX_FORMAT_8,
    TITEX_FLAGS_BLOCK,
};

u16 menu_level_titexdata_06_texs_tlut[] ALIGNED(8) = {
#include "assets/menu/menu_level/menu_level_titexdata_06_texs_tex.palette.inc"
};
static_assert(ARRAY_COUNT(menu_level_titexdata_06_texs_tlut) == 16 * 16,
              "The dimensions of `menu_level_titexdata_06_texs_tlut` does not match the size of the actual tlut");

u8 menu_level_titexdata_06_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_level/menu_level_titexdata_06_texs_tex.ci8.inc"
};
static_assert(ARRAY_COUNT(menu_level_titexdata_06_texs_tex) ==
                  menu_level_titexdata_06_texs_tex_width * menu_level_titexdata_06_texs_tex_height,
              "The dimensions of `menu_level_titexdata_06_texs_tex` does not match the size of the actual texture");

#elif VERSION_CN

/* titexdata_02 */

extern u16 menu_level_titexdata_02_texs_tlut[];
extern u8 menu_level_titexdata_02_texs_tex[];

TiTexDataTextures menu_level_titexdata_02_texs = {
    menu_level_titexdata_02_texs_tlut,
    menu_level_titexdata_02_texs_tex,
};

#define menu_level_titexdata_02_texs_tex_width 304
#define menu_level_titexdata_02_texs_tex_height 93

u16 menu_level_titexdata_02_info[] = {
    menu_level_titexdata_02_texs_tex_width,
    menu_level_titexdata_02_texs_tex_height,
    TITEX_FORMAT_8,
    TITEX_FLAGS_BLOCK,
};

u16 menu_level_titexdata_02_texs_tlut[] ALIGNED(8) = {
#include "assets/menu/menu_level/menu_level_titexdata_02_texs_tex.palette.inc"
};
static_assert(ARRAY_COUNT(menu_level_titexdata_02_texs_tlut) == 16 * 16,
              "The dimensions of `menu_level_titexdata_02_texs_tlut` does not match the size of the actual tlut");

u8 menu_level_titexdata_02_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_level/menu_level_titexdata_02_texs_tex.ci8.inc"
};
static_assert(ARRAY_COUNT(menu_level_titexdata_02_texs_tex) ==
                  menu_level_titexdata_02_texs_tex_width * menu_level_titexdata_02_texs_tex_height,
              "The dimensions of `menu_level_titexdata_02_texs_tex` does not match the size of the actual texture");

/* titexdata_03 */

extern u16 menu_level_titexdata_03_texs_tlut[];
extern u8 menu_level_titexdata_03_texs_tex[];

TiTexDataTextures menu_level_titexdata_03_texs = {
    menu_level_titexdata_03_texs_tlut,
    menu_level_titexdata_03_texs_tex,
};

#define menu_level_titexdata_03_texs_tex_width 270
#define menu_level_titexdata_03_texs_tex_height 93

u16 menu_level_titexdata_03_info[] = {
    menu_level_titexdata_03_texs_tex_width,
    menu_level_titexdata_03_texs_tex_height,
    TITEX_FORMAT_8,
    TITEX_FLAGS_TILE,
};

u16 menu_level_titexdata_03_texs_tlut[] ALIGNED(8) = {
#include "assets/menu/menu_level/menu_level_titexdata_03_texs_tex.palette.inc"
};
static_assert(ARRAY_COUNT(menu_level_titexdata_03_texs_tlut) == 16 * 16,
              "The dimensions of `menu_level_titexdata_03_texs_tlut` does not match the size of the actual tlut");

u8 menu_level_titexdata_03_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_level/menu_level_titexdata_03_texs_tex.ci8.inc"
};
static_assert(ARRAY_COUNT(menu_level_titexdata_03_texs_tex) ==
                  menu_level_titexdata_03_texs_tex_width * menu_level_titexdata_03_texs_tex_height,
              "The dimensions of `menu_level_titexdata_03_texs_tex` does not match the size of the actual texture");

/* titexdata_04 */

extern u16 menu_level_titexdata_04_texs_tlut[];
extern u8 menu_level_titexdata_04_texs_tex[];

TiTexDataTextures menu_level_titexdata_04_texs = {
    menu_level_titexdata_04_texs_tlut,
    menu_level_titexdata_04_texs_tex,
};

#define menu_level_titexdata_04_texs_tex_width 48
#define menu_level_titexdata_04_texs_tex_height 32

u16 menu_level_titexdata_04_info[] = {
    menu_level_titexdata_04_texs_tex_width,
    menu_level_titexdata_04_texs_tex_height,
    TITEX_FORMAT_8,
    TITEX_FLAGS_BLOCK,
};

u16 menu_level_titexdata_04_texs_tlut[] ALIGNED(8) = {
#include "assets/menu/menu_level/menu_level_titexdata_04_texs_tex.palette.inc"
};
static_assert(ARRAY_COUNT(menu_level_titexdata_04_texs_tlut) == 16 * 16,
              "The dimensions of `menu_level_titexdata_04_texs_tlut` does not match the size of the actual tlut");

u8 menu_level_titexdata_04_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_level/menu_level_titexdata_04_texs_tex.ci8.inc"
};
static_assert(ARRAY_COUNT(menu_level_titexdata_04_texs_tex) ==
                  menu_level_titexdata_04_texs_tex_width * menu_level_titexdata_04_texs_tex_height,
              "The dimensions of `menu_level_titexdata_04_texs_tex` does not match the size of the actual texture");

/* titexdata_05 */

extern u16 menu_level_titexdata_05_texs_tlut[];
extern u8 menu_level_titexdata_05_texs_tex[];

TiTexDataTextures menu_level_titexdata_05_texs = {
    menu_level_titexdata_05_texs_tlut,
    menu_level_titexdata_05_texs_tex,
};

#define menu_level_titexdata_05_texs_tex_width 72
#define menu_level_titexdata_05_texs_tex_height 164

u16 menu_level_titexdata_05_info[] = {
    menu_level_titexdata_05_texs_tex_width,
    menu_level_titexdata_05_texs_tex_height,
    TITEX_FORMAT_8,
    TITEX_FLAGS_BLOCK,
};

u16 menu_level_titexdata_05_texs_tlut[] ALIGNED(8) = {
#include "assets/menu/menu_level/menu_level_titexdata_05_texs_tex.palette.inc"
};
static_assert(ARRAY_COUNT(menu_level_titexdata_05_texs_tlut) == 16 * 16,
              "The dimensions of `menu_level_titexdata_05_texs_tlut` does not match the size of the actual tlut");

u8 menu_level_titexdata_05_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_level/menu_level_titexdata_05_texs_tex.ci8.inc"
};
static_assert(ARRAY_COUNT(menu_level_titexdata_05_texs_tex) ==
                  menu_level_titexdata_05_texs_tex_width * menu_level_titexdata_05_texs_tex_height,
              "The dimensions of `menu_level_titexdata_05_texs_tex` does not match the size of the actual texture");

/* titexdata_06 */

extern u16 menu_level_titexdata_06_texs_tlut[];
extern u8 menu_level_titexdata_06_texs_tex[];

TiTexDataTextures menu_level_titexdata_06_texs = {
    menu_level_titexdata_06_texs_tlut,
    menu_level_titexdata_06_texs_tex,
};

#define menu_level_titexdata_06_texs_tex_width 56
#define menu_level_titexdata_06_texs_tex_height 150

u16 menu_level_titexdata_06_info[] = {
    menu_level_titexdata_06_texs_tex_width,
    menu_level_titexdata_06_texs_tex_height,
    TITEX_FORMAT_8,
    TITEX_FLAGS_BLOCK,
};

u16 menu_level_titexdata_06_texs_tlut[] ALIGNED(8) = {
#include "assets/menu/menu_level/menu_level_titexdata_06_texs_tex.palette.inc"
};
static_assert(ARRAY_COUNT(menu_level_titexdata_06_texs_tlut) == 16 * 16,
              "The dimensions of `menu_level_titexdata_06_texs_tlut` does not match the size of the actual tlut");

u8 menu_level_titexdata_06_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_level/menu_level_titexdata_06_texs_tex.ci8.inc"
};
static_assert(ARRAY_COUNT(menu_level_titexdata_06_texs_tex) ==
                  menu_level_titexdata_06_texs_tex_width * menu_level_titexdata_06_texs_tex_height,
              "The dimensions of `menu_level_titexdata_06_texs_tex` does not match the size of the actual texture");

#endif

TiTexData menu_level_titexdata[] = {
    { &menu_level_titexdata_00_texs, menu_level_titexdata_00_info },
    { &menu_level_titexdata_01_texs, menu_level_titexdata_01_info },
#if VERSION_CN
    { &menu_level_titexdata_05_texs, menu_level_titexdata_05_info },
    { &menu_level_titexdata_06_texs, menu_level_titexdata_06_info },
#endif
    { &menu_level_titexdata_02_texs, menu_level_titexdata_02_info },
    { &menu_level_titexdata_03_texs, menu_level_titexdata_03_info },
    { &menu_level_titexdata_04_texs, menu_level_titexdata_04_info },
#if VERSION_US || VERSION_GW
    { &menu_level_titexdata_05_texs, menu_level_titexdata_05_info },
    { &menu_level_titexdata_06_texs, menu_level_titexdata_06_info },
#endif
};

s32 menu_level_titexdata_len = ARRAY_COUNT(menu_level_titexdata);

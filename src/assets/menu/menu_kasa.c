#include "tex_func.h"

#include "libc/assert.h"
#include "macros_defines.h"
#include "alignment.h"

extern TiTexData menu_kasa_titexdata[];
extern s32 menu_kasa_titexdata_len;

TiTexDataHeader menu_kasa_header = {
    menu_kasa_titexdata,
    &menu_kasa_titexdata_len,
};

/* titexdata_00 */

extern u8 menu_kasa_titexdata_00_texs_tex[];

TexturePtr menu_kasa_titexdata_00_texs[2] = {
    NULL,
    menu_kasa_titexdata_00_texs_tex,
};

#define menu_kasa_titexdata_00_texs_tex_width 72
#define menu_kasa_titexdata_00_texs_tex_height 96

u16 menu_kasa_titexdata_00_info[] = {
    menu_kasa_titexdata_00_texs_tex_width,
    menu_kasa_titexdata_00_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_TILE,
};

u8 menu_kasa_titexdata_00_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_kasa/menu_kasa_titexdata_00_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(menu_kasa_titexdata_00_texs_tex) ==
                  menu_kasa_titexdata_00_texs_tex_width * menu_kasa_titexdata_00_texs_tex_height / 2,
              "The dimensions of `menu_kasa_titexdata_00_texs_tex` does not match the size of the actual texture");

/* titexdata_01 */

extern u16 menu_kasa_titexdata_01_texs_tex[];

TexturePtr menu_kasa_titexdata_01_texs[2] = {
    NULL,
    menu_kasa_titexdata_01_texs_tex,
};

#define menu_kasa_titexdata_01_texs_tex_width 72
#define menu_kasa_titexdata_01_texs_tex_height 96

u16 menu_kasa_titexdata_01_info[] = {
    menu_kasa_titexdata_01_texs_tex_width,
    menu_kasa_titexdata_01_texs_tex_height,
    TITEX_FORMAT_16,
    TITEX_FLAGS_BLOCK,
};

u16 menu_kasa_titexdata_01_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_kasa/menu_kasa_titexdata_01_texs_tex.rgba16.inc"
};
static_assert(ARRAY_COUNT(menu_kasa_titexdata_01_texs_tex) ==
                  menu_kasa_titexdata_01_texs_tex_width * menu_kasa_titexdata_01_texs_tex_height,
              "The dimensions of `menu_kasa_titexdata_01_texs_tex` does not match the size of the actual texture");

/* titexdata_02 */

extern u16 menu_kasa_titexdata_02_texs_tex[];

TexturePtr menu_kasa_titexdata_02_texs[2] = {
    NULL,
    menu_kasa_titexdata_02_texs_tex,
};

#define menu_kasa_titexdata_02_texs_tex_width 72
#define menu_kasa_titexdata_02_texs_tex_height 96

u16 menu_kasa_titexdata_02_info[] = {
    menu_kasa_titexdata_02_texs_tex_width,
    menu_kasa_titexdata_02_texs_tex_height,
    TITEX_FORMAT_16,
    TITEX_FLAGS_BLOCK,
};

u16 menu_kasa_titexdata_02_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_kasa/menu_kasa_titexdata_02_texs_tex.rgba16.inc"
};
static_assert(ARRAY_COUNT(menu_kasa_titexdata_02_texs_tex) ==
                  menu_kasa_titexdata_02_texs_tex_width * menu_kasa_titexdata_02_texs_tex_height,
              "The dimensions of `menu_kasa_titexdata_02_texs_tex` does not match the size of the actual texture");

/* titexdata_03 */

extern u16 menu_kasa_titexdata_03_texs_tex[];

TexturePtr menu_kasa_titexdata_03_texs[2] = {
    NULL,
    menu_kasa_titexdata_03_texs_tex,
};

#define menu_kasa_titexdata_03_texs_tex_width 72
#define menu_kasa_titexdata_03_texs_tex_height 96

u16 menu_kasa_titexdata_03_info[] = {
    menu_kasa_titexdata_03_texs_tex_width,
    menu_kasa_titexdata_03_texs_tex_height,
    TITEX_FORMAT_16,
    TITEX_FLAGS_BLOCK,
};

u16 menu_kasa_titexdata_03_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_kasa/menu_kasa_titexdata_03_texs_tex.rgba16.inc"
};
static_assert(ARRAY_COUNT(menu_kasa_titexdata_03_texs_tex) ==
                  menu_kasa_titexdata_03_texs_tex_width * menu_kasa_titexdata_03_texs_tex_height,
              "The dimensions of `menu_kasa_titexdata_03_texs_tex` does not match the size of the actual texture");

/* titexdata_04 */

extern u16 menu_kasa_titexdata_04_texs_tex[];

TexturePtr menu_kasa_titexdata_04_texs[2] = {
    NULL,
    menu_kasa_titexdata_04_texs_tex,
};

#define menu_kasa_titexdata_04_texs_tex_width 72
#define menu_kasa_titexdata_04_texs_tex_height 96

u16 menu_kasa_titexdata_04_info[] = {
    menu_kasa_titexdata_04_texs_tex_width,
    menu_kasa_titexdata_04_texs_tex_height,
    TITEX_FORMAT_16,
    TITEX_FLAGS_BLOCK,
};

u16 menu_kasa_titexdata_04_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_kasa/menu_kasa_titexdata_04_texs_tex.rgba16.inc"
};
static_assert(ARRAY_COUNT(menu_kasa_titexdata_04_texs_tex) ==
                  menu_kasa_titexdata_04_texs_tex_width * menu_kasa_titexdata_04_texs_tex_height,
              "The dimensions of `menu_kasa_titexdata_04_texs_tex` does not match the size of the actual texture");

TiTexData menu_kasa_titexdata[] = {
    { menu_kasa_titexdata_00_texs, menu_kasa_titexdata_00_info },
    { menu_kasa_titexdata_01_texs, menu_kasa_titexdata_01_info },
    { menu_kasa_titexdata_02_texs, menu_kasa_titexdata_02_info },
    { menu_kasa_titexdata_03_texs, menu_kasa_titexdata_03_info },
    { menu_kasa_titexdata_04_texs, menu_kasa_titexdata_04_info },
};

s32 menu_kasa_titexdata_len = ARRAY_COUNT(menu_kasa_titexdata);

#include "tex_func.h"

#include "libc/assert.h"
#include "macros_defines.h"
#include "alignment.h"

extern TiTexData menu_name_titexdata[];
extern s32 menu_name_titexdata_len;

TiTexDataHeader menu_name_header = {
    menu_name_titexdata,
    &menu_name_titexdata_len,
};

/* titexdata_00 */

extern u16 menu_name_titexdata_00_texs_tex[];

TexturePtr menu_name_titexdata_00_texs[2] = {
    NULL,
    menu_name_titexdata_00_texs_tex,
};

#define menu_name_titexdata_00_texs_tex_width 12
#define menu_name_titexdata_00_texs_tex_height 12

u16 menu_name_titexdata_00_info[] = {
    menu_name_titexdata_00_texs_tex_width,
    menu_name_titexdata_00_texs_tex_height,
    TITEX_FORMAT_16,
    TITEX_FLAGS_BLOCK,
};

u16 menu_name_titexdata_00_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_name/menu_name_titexdata_00_texs_tex.rgba16.inc"
};
static_assert(ARRAY_COUNT(menu_name_titexdata_00_texs_tex) ==
                  menu_name_titexdata_00_texs_tex_width * menu_name_titexdata_00_texs_tex_height,
              "The dimensions of `menu_name_titexdata_00_texs_tex` does not match the size of the actual texture");

/* titexdata_01 */

extern u8 menu_name_titexdata_01_texs_tex[];

TexturePtr menu_name_titexdata_01_texs[2] = {
    NULL,
    menu_name_titexdata_01_texs_tex,
};

#define menu_name_titexdata_01_texs_tex_width 16
#define menu_name_titexdata_01_texs_tex_height 12

u16 menu_name_titexdata_01_info[] = {
    menu_name_titexdata_01_texs_tex_width,
    menu_name_titexdata_01_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 menu_name_titexdata_01_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_name/menu_name_titexdata_01_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(menu_name_titexdata_01_texs_tex) ==
                  menu_name_titexdata_01_texs_tex_width * menu_name_titexdata_01_texs_tex_height / 2,
              "The dimensions of `menu_name_titexdata_01_texs_tex` does not match the size of the actual texture");

/* titexdata_02 */

extern u16 menu_name_titexdata_02_texs_tlut[];
extern u8 menu_name_titexdata_02_texs_tex[];

TexturePtr menu_name_titexdata_02_texs[2] = {
    menu_name_titexdata_02_texs_tlut,
    menu_name_titexdata_02_texs_tex,
};

#define menu_name_titexdata_02_texs_tex_width 288
#define menu_name_titexdata_02_texs_tex_height 130

u16 menu_name_titexdata_02_info[] = {
    menu_name_titexdata_02_texs_tex_width,
    menu_name_titexdata_02_texs_tex_height,
    TITEX_FORMAT_8,
    TITEX_FLAGS_BLOCK,
};

u16 menu_name_titexdata_02_texs_tlut[] ALIGNED(8) = {
#include "assets/menu/menu_name/menu_name_titexdata_02_texs_tex.palette.inc"
};
static_assert(ARRAY_COUNT(menu_name_titexdata_02_texs_tlut) == 16 * 16,
              "The dimensions of `menu_name_titexdata_02_texs_tlut` does not match the size of the actual tlut");

u8 menu_name_titexdata_02_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_name/menu_name_titexdata_02_texs_tex.ci8.inc"
};
static_assert(ARRAY_COUNT(menu_name_titexdata_02_texs_tex) ==
                  menu_name_titexdata_02_texs_tex_width * menu_name_titexdata_02_texs_tex_height,
              "The dimensions of `menu_name_titexdata_02_texs_tex` does not match the size of the actual texture");

/* titexdata_03 */

extern u16 menu_name_titexdata_03_texs_tlut[];
extern u8 menu_name_titexdata_03_texs_tex[];

TexturePtr menu_name_titexdata_03_texs[2] = {
    menu_name_titexdata_03_texs_tlut,
    menu_name_titexdata_03_texs_tex,
};

#define menu_name_titexdata_03_texs_tex_width 16
#define menu_name_titexdata_03_texs_tex_height 11

u16 menu_name_titexdata_03_info[] = {
    menu_name_titexdata_03_texs_tex_width,
    menu_name_titexdata_03_texs_tex_height,
    TITEX_FORMAT_8,
    TITEX_FLAGS_BLOCK,
};

u16 menu_name_titexdata_03_texs_tlut[] ALIGNED(8) = {
#include "assets/menu/menu_name/menu_name_titexdata_03_texs_tex.palette.inc"
};
static_assert(ARRAY_COUNT(menu_name_titexdata_03_texs_tlut) == 16 * 16,
              "The dimensions of `menu_name_titexdata_03_texs_tlut` does not match the size of the actual tlut");

u8 menu_name_titexdata_03_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_name/menu_name_titexdata_03_texs_tex.ci8.inc"
};
static_assert(ARRAY_COUNT(menu_name_titexdata_03_texs_tex) ==
                  menu_name_titexdata_03_texs_tex_width * menu_name_titexdata_03_texs_tex_height,
              "The dimensions of `menu_name_titexdata_03_texs_tex` does not match the size of the actual texture");

/* titexdata_04 */

extern u16 menu_name_titexdata_04_texs_tlut[];
extern u8 menu_name_titexdata_04_texs_tex[];

TexturePtr menu_name_titexdata_04_texs[2] = {
    menu_name_titexdata_04_texs_tlut,
    menu_name_titexdata_04_texs_tex,
};

#define menu_name_titexdata_04_texs_tex_width 200
#define menu_name_titexdata_04_texs_tex_height 45

u16 menu_name_titexdata_04_info[] = {
    menu_name_titexdata_04_texs_tex_width,
    menu_name_titexdata_04_texs_tex_height,
    TITEX_FORMAT_8,
    TITEX_FLAGS_BLOCK,
};

u16 menu_name_titexdata_04_texs_tlut[] ALIGNED(8) = {
#include "assets/menu/menu_name/menu_name_titexdata_04_texs_tex.palette.inc"
};
static_assert(ARRAY_COUNT(menu_name_titexdata_04_texs_tlut) == 16 * 16,
              "The dimensions of `menu_name_titexdata_04_texs_tlut` does not match the size of the actual tlut");

u8 menu_name_titexdata_04_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_name/menu_name_titexdata_04_texs_tex.ci8.inc"
};
static_assert(ARRAY_COUNT(menu_name_titexdata_04_texs_tex) ==
                  menu_name_titexdata_04_texs_tex_width * menu_name_titexdata_04_texs_tex_height,
              "The dimensions of `menu_name_titexdata_04_texs_tex` does not match the size of the actual texture");

TiTexData menu_name_titexdata[] = {
    { menu_name_titexdata_00_texs, menu_name_titexdata_00_info },
    { menu_name_titexdata_01_texs, menu_name_titexdata_01_info },
    { menu_name_titexdata_02_texs, menu_name_titexdata_02_info },
    { menu_name_titexdata_04_texs, menu_name_titexdata_04_info },
    { menu_name_titexdata_03_texs, menu_name_titexdata_03_info },
};

s32 menu_name_titexdata_len = ARRAY_COUNT(menu_name_titexdata);

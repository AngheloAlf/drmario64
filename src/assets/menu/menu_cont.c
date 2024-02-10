#include "tex_func.h"

#include "libc/assert.h"
#include "macros_defines.h"
#include "alignment.h"

extern TiTexData menu_cont_titexdata[];
extern s32 menu_cont_titexdata_len;

TiTexDataHeader menu_cont_header = {
    menu_cont_titexdata,
    &menu_cont_titexdata_len,
};

/* titexdata_00 */

extern u8 menu_cont_titexdata_00_texs_tex[];

TiTexDataTextures menu_cont_titexdata_00_texs = {
    NULL,
    menu_cont_titexdata_00_texs_tex,
};

#define menu_cont_titexdata_00_texs_tex_width 192
#define menu_cont_titexdata_00_texs_tex_height 113

u16 menu_cont_titexdata_00_info[] = {
    menu_cont_titexdata_00_texs_tex_width,
    menu_cont_titexdata_00_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 menu_cont_titexdata_00_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_cont/menu_cont_titexdata_00_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(menu_cont_titexdata_00_texs_tex) ==
                  menu_cont_titexdata_00_texs_tex_width * menu_cont_titexdata_00_texs_tex_height / 2,
              "The dimensions of `menu_cont_titexdata_00_texs_tex` does not match the size of the actual texture");

/* titexdata_01 */

extern u16 menu_cont_titexdata_01_texs_tlut[];
extern u8 menu_cont_titexdata_01_texs_tex[];

TiTexDataTextures menu_cont_titexdata_01_texs = {
    menu_cont_titexdata_01_texs_tlut,
    menu_cont_titexdata_01_texs_tex,
};

#define menu_cont_titexdata_01_texs_tex_width 80
#define menu_cont_titexdata_01_texs_tex_height 40

u16 menu_cont_titexdata_01_info[] = {
    menu_cont_titexdata_01_texs_tex_width,
    menu_cont_titexdata_01_texs_tex_height,
    TITEX_FORMAT_8,
    TITEX_FLAGS_BLOCK,
};

u16 menu_cont_titexdata_01_texs_tlut[] ALIGNED(8) = {
#include "assets/menu/menu_cont/menu_cont_titexdata_01_texs_tlut.rgba16.inc"
};
static_assert(ARRAY_COUNT(menu_cont_titexdata_01_texs_tlut) == 16 * 16,
              "The dimensions of `menu_cont_titexdata_01_texs_tlut` does not match the size of the actual tlut");

u8 menu_cont_titexdata_01_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_cont/menu_cont_titexdata_01_texs_tex.i8.inc"
};
static_assert(ARRAY_COUNT(menu_cont_titexdata_01_texs_tex) ==
                  menu_cont_titexdata_01_texs_tex_width * menu_cont_titexdata_01_texs_tex_height,
              "The dimensions of `menu_cont_titexdata_01_texs_tex` does not match the size of the actual texture");

/* titexdata_02 */

extern u16 menu_cont_titexdata_02_texs_tlut[];
extern u8 menu_cont_titexdata_02_texs_tex[];

TiTexDataTextures menu_cont_titexdata_02_texs = {
    menu_cont_titexdata_02_texs_tlut,
    menu_cont_titexdata_02_texs_tex,
};

#define menu_cont_titexdata_02_texs_tex_width 96
#define menu_cont_titexdata_02_texs_tex_height 196

u16 menu_cont_titexdata_02_info[] = {
    menu_cont_titexdata_02_texs_tex_width,
    menu_cont_titexdata_02_texs_tex_height,
    TITEX_FORMAT_8,
    TITEX_FLAGS_BLOCK,
};

u16 menu_cont_titexdata_02_texs_tlut[] ALIGNED(8) = {
#include "assets/menu/menu_cont/menu_cont_titexdata_02_texs_tlut.rgba16.inc"
};
static_assert(ARRAY_COUNT(menu_cont_titexdata_02_texs_tlut) == 16 * 16,
              "The dimensions of `menu_cont_titexdata_02_texs_tlut` does not match the size of the actual tlut");

u8 menu_cont_titexdata_02_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_cont/menu_cont_titexdata_02_texs_tex.i8.inc"
};
static_assert(ARRAY_COUNT(menu_cont_titexdata_02_texs_tex) ==
                  menu_cont_titexdata_02_texs_tex_width * menu_cont_titexdata_02_texs_tex_height,
              "The dimensions of `menu_cont_titexdata_02_texs_tex` does not match the size of the actual texture");

TiTexData menu_cont_titexdata[] = {
    { &menu_cont_titexdata_00_texs, menu_cont_titexdata_00_info },
    { &menu_cont_titexdata_01_texs, menu_cont_titexdata_01_info },
    { &menu_cont_titexdata_02_texs, menu_cont_titexdata_02_info },
};

s32 menu_cont_titexdata_len = ARRAY_COUNT(menu_cont_titexdata);

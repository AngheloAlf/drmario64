#include "tex_func.h"

#include "libc/assert.h"
#include "macros_defines.h"
#include "alignment.h"

extern TiTexData menu_p2_titexdata[];
extern s32 menu_p2_titexdata_len;

TiTexDataHeader menu_p2_header = {
    menu_p2_titexdata,
    &menu_p2_titexdata_len,
};

/* titexdata_00 */

extern u16 menu_p2_titexdata_00_texs_tlut[];
extern u8 menu_p2_titexdata_00_texs_tex[];

TiTexDataTextures menu_p2_titexdata_00_texs = {
    menu_p2_titexdata_00_texs_tlut,
    menu_p2_titexdata_00_texs_tex,
};

#define menu_p2_titexdata_00_texs_tex_width 304
#define menu_p2_titexdata_00_texs_tex_height 65

u16 menu_p2_titexdata_00_info[] = {
    menu_p2_titexdata_00_texs_tex_width,
    menu_p2_titexdata_00_texs_tex_height,
    TITEX_FORMAT_8,
    TITEX_FLAGS_BLOCK,
};

u16 menu_p2_titexdata_00_texs_tlut[] ALIGNED(8) = {
#include "assets/menu/menu_p2/menu_p2_titexdata_00_texs_tex.palette.inc"
};
static_assert(ARRAY_COUNT(menu_p2_titexdata_00_texs_tlut) == 16 * 16,
              "The dimensions of `menu_p2_titexdata_00_texs_tlut` does not match the size of the actual tlut");

u8 menu_p2_titexdata_00_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_p2/menu_p2_titexdata_00_texs_tex.ci8.inc"
};
static_assert(ARRAY_COUNT(menu_p2_titexdata_00_texs_tex) ==
                  menu_p2_titexdata_00_texs_tex_width * menu_p2_titexdata_00_texs_tex_height,
              "The dimensions of `menu_p2_titexdata_00_texs_tex` does not match the size of the actual texture");

/* titexdata_01 */

extern u16 menu_p2_titexdata_01_texs_tlut[];
extern u8 menu_p2_titexdata_01_texs_tex[];

TiTexDataTextures menu_p2_titexdata_01_texs = {
    menu_p2_titexdata_01_texs_tlut,
    menu_p2_titexdata_01_texs_tex,
};

#define menu_p2_titexdata_01_texs_tex_width 304
#define menu_p2_titexdata_01_texs_tex_height 65

u16 menu_p2_titexdata_01_info[] = {
    menu_p2_titexdata_01_texs_tex_width,
    menu_p2_titexdata_01_texs_tex_height,
    TITEX_FORMAT_8,
    TITEX_FLAGS_BLOCK,
};

u16 menu_p2_titexdata_01_texs_tlut[] ALIGNED(8) = {
#include "assets/menu/menu_p2/menu_p2_titexdata_01_texs_tex.palette.inc"
};
static_assert(ARRAY_COUNT(menu_p2_titexdata_01_texs_tlut) == 16 * 16,
              "The dimensions of `menu_p2_titexdata_01_texs_tlut` does not match the size of the actual tlut");

u8 menu_p2_titexdata_01_texs_tex[] ALIGNED(8) = {
#include "assets/menu/menu_p2/menu_p2_titexdata_01_texs_tex.ci8.inc"
};
static_assert(ARRAY_COUNT(menu_p2_titexdata_01_texs_tex) ==
                  menu_p2_titexdata_01_texs_tex_width * menu_p2_titexdata_01_texs_tex_height,
              "The dimensions of `menu_p2_titexdata_01_texs_tex` does not match the size of the actual texture");

TiTexData menu_p2_titexdata[] = {
    { &menu_p2_titexdata_00_texs, menu_p2_titexdata_00_info },
    { &menu_p2_titexdata_01_texs, menu_p2_titexdata_01_info },
};

s32 menu_p2_titexdata_len = ARRAY_COUNT(menu_p2_titexdata);

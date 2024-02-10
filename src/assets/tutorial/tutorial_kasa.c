#include "tex_func.h"

#include "libc/assert.h"
#include "macros_defines.h"
#include "alignment.h"

extern TiTexData tutorial_kasa_titexdata[];
extern s32 tutorial_kasa_titexdata_len;

TiTexDataHeader tutorial_kasa_header = {
    tutorial_kasa_titexdata,
    &tutorial_kasa_titexdata_len,
};

/* titexdata_00 */

extern u16 tutorial_kasa_titexdata_00_texs_tex[];

TiTexDataTextures tutorial_kasa_titexdata_00_texs = {
    NULL,
    tutorial_kasa_titexdata_00_texs_tex,
};

#define tutorial_kasa_titexdata_00_texs_tex_width 128
#define tutorial_kasa_titexdata_00_texs_tex_height 12

u16 tutorial_kasa_titexdata_00_info[] = {
    tutorial_kasa_titexdata_00_texs_tex_width,
    tutorial_kasa_titexdata_00_texs_tex_height,
    TITEX_FORMAT_16,
    TITEX_FLAGS_BLOCK,
};

u16 tutorial_kasa_titexdata_00_texs_tex[] ALIGNED(8) = {
#include "assets/tutorial/tutorial_kasa/tutorial_kasa_titexdata_00_texs_tex.rgba16.inc"
};
static_assert(ARRAY_COUNT(tutorial_kasa_titexdata_00_texs_tex) ==
                  tutorial_kasa_titexdata_00_texs_tex_width * tutorial_kasa_titexdata_00_texs_tex_height,
              "The dimensions of `tutorial_kasa_titexdata_00_texs_tex` does not match the size of the actual texture");

/* titexdata_01 */

extern u16 tutorial_kasa_titexdata_01_texs_tex[];

TiTexDataTextures tutorial_kasa_titexdata_01_texs = {
    NULL,
    tutorial_kasa_titexdata_01_texs_tex,
};

#define tutorial_kasa_titexdata_01_texs_tex_width 128
#define tutorial_kasa_titexdata_01_texs_tex_height 12

u16 tutorial_kasa_titexdata_01_info[] = {
    tutorial_kasa_titexdata_01_texs_tex_width,
    tutorial_kasa_titexdata_01_texs_tex_height,
    TITEX_FORMAT_16,
    TITEX_FLAGS_BLOCK,
};

u16 tutorial_kasa_titexdata_01_texs_tex[] ALIGNED(8) = {
#include "assets/tutorial/tutorial_kasa/tutorial_kasa_titexdata_01_texs_tex.rgba16.inc"
};
static_assert(ARRAY_COUNT(tutorial_kasa_titexdata_01_texs_tex) ==
                  tutorial_kasa_titexdata_01_texs_tex_width * tutorial_kasa_titexdata_01_texs_tex_height,
              "The dimensions of `tutorial_kasa_titexdata_01_texs_tex` does not match the size of the actual texture");

/* titexdata_02 */

extern u8 tutorial_kasa_titexdata_02_texs_tex[];

TiTexDataTextures tutorial_kasa_titexdata_02_texs = {
    NULL,
    tutorial_kasa_titexdata_02_texs_tex,
};

#define tutorial_kasa_titexdata_02_texs_tex_width 128
#define tutorial_kasa_titexdata_02_texs_tex_height 12

u16 tutorial_kasa_titexdata_02_info[] = {
    tutorial_kasa_titexdata_02_texs_tex_width,
    tutorial_kasa_titexdata_02_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 tutorial_kasa_titexdata_02_texs_tex[] ALIGNED(8) = {
#include "assets/tutorial/tutorial_kasa/tutorial_kasa_titexdata_02_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(tutorial_kasa_titexdata_02_texs_tex) ==
                  tutorial_kasa_titexdata_02_texs_tex_width * tutorial_kasa_titexdata_02_texs_tex_height / 2,
              "The dimensions of `tutorial_kasa_titexdata_02_texs_tex` does not match the size of the actual texture");

/* titexdata_03 */

extern u8 tutorial_kasa_titexdata_03_texs_tex[];

TiTexDataTextures tutorial_kasa_titexdata_03_texs = {
    NULL,
    tutorial_kasa_titexdata_03_texs_tex,
};

#define tutorial_kasa_titexdata_03_texs_tex_width 128
#define tutorial_kasa_titexdata_03_texs_tex_height 12

u16 tutorial_kasa_titexdata_03_info[] = {
    tutorial_kasa_titexdata_03_texs_tex_width,
    tutorial_kasa_titexdata_03_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 tutorial_kasa_titexdata_03_texs_tex[] ALIGNED(8) = {
#include "assets/tutorial/tutorial_kasa/tutorial_kasa_titexdata_03_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(tutorial_kasa_titexdata_03_texs_tex) ==
                  tutorial_kasa_titexdata_03_texs_tex_width * tutorial_kasa_titexdata_03_texs_tex_height / 2,
              "The dimensions of `tutorial_kasa_titexdata_03_texs_tex` does not match the size of the actual texture");

/* titexdata_04 */

extern u16 tutorial_kasa_titexdata_04_texs_tex[];

TiTexDataTextures tutorial_kasa_titexdata_04_texs = {
    NULL,
    tutorial_kasa_titexdata_04_texs_tex,
};

#define tutorial_kasa_titexdata_04_texs_tex_width 16
#define tutorial_kasa_titexdata_04_texs_tex_height 16

u16 tutorial_kasa_titexdata_04_info[] = {
    tutorial_kasa_titexdata_04_texs_tex_width,
    tutorial_kasa_titexdata_04_texs_tex_height,
    TITEX_FORMAT_16,
    TITEX_FLAGS_BLOCK,
};

u16 tutorial_kasa_titexdata_04_texs_tex[] ALIGNED(8) = {
#include "assets/tutorial/tutorial_kasa/tutorial_kasa_titexdata_04_texs_tex.rgba16.inc"
};
static_assert(ARRAY_COUNT(tutorial_kasa_titexdata_04_texs_tex) ==
                  tutorial_kasa_titexdata_04_texs_tex_width * tutorial_kasa_titexdata_04_texs_tex_height,
              "The dimensions of `tutorial_kasa_titexdata_04_texs_tex` does not match the size of the actual texture");

/* titexdata_05 */

extern u8 tutorial_kasa_titexdata_05_texs_tex[];

TiTexDataTextures tutorial_kasa_titexdata_05_texs = {
    NULL,
    tutorial_kasa_titexdata_05_texs_tex,
};

#define tutorial_kasa_titexdata_05_texs_tex_width 16
#define tutorial_kasa_titexdata_05_texs_tex_height 16

u16 tutorial_kasa_titexdata_05_info[] = {
    tutorial_kasa_titexdata_05_texs_tex_width,
    tutorial_kasa_titexdata_05_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u8 tutorial_kasa_titexdata_05_texs_tex[] ALIGNED(8) = {
#include "assets/tutorial/tutorial_kasa/tutorial_kasa_titexdata_05_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(tutorial_kasa_titexdata_05_texs_tex) ==
                  tutorial_kasa_titexdata_05_texs_tex_width * tutorial_kasa_titexdata_05_texs_tex_height / 2,
              "The dimensions of `tutorial_kasa_titexdata_05_texs_tex` does not match the size of the actual texture");

/* titexdata_06 */

extern u16 tutorial_kasa_titexdata_06_texs_tlut[];
extern u8 tutorial_kasa_titexdata_06_texs_tex[];

TiTexDataTextures tutorial_kasa_titexdata_06_texs = {
    tutorial_kasa_titexdata_06_texs_tlut,
    tutorial_kasa_titexdata_06_texs_tex,
};

#if VERSION_US || VERSION_GW
#define tutorial_kasa_titexdata_06_texs_tex_width 16
#define tutorial_kasa_titexdata_06_texs_tex_height 16

u16 tutorial_kasa_titexdata_06_info[] = {
    tutorial_kasa_titexdata_06_texs_tex_width,
    tutorial_kasa_titexdata_06_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u16 tutorial_kasa_titexdata_06_texs_tlut[] ALIGNED(8) = {
#include "assets/tutorial/tutorial_kasa/tutorial_kasa_titexdata_06_texs_tlut.rgba16.inc"
};
static_assert(ARRAY_COUNT(tutorial_kasa_titexdata_06_texs_tlut) == 4 * 4,
              "The dimensions of `tutorial_kasa_titexdata_06_texs_tlut` does not match the size of the actual tlut");

u8 tutorial_kasa_titexdata_06_texs_tex[] ALIGNED(8) = {
#include "assets/tutorial/tutorial_kasa/tutorial_kasa_titexdata_06_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(tutorial_kasa_titexdata_06_texs_tex) ==
                  tutorial_kasa_titexdata_06_texs_tex_width * tutorial_kasa_titexdata_06_texs_tex_height / 2,
              "The dimensions of `tutorial_kasa_titexdata_06_texs_tex` does not match the size of the actual texture");

/* titexdata_07 */

extern u16 tutorial_kasa_titexdata_07_texs_tlut[];
extern u8 tutorial_kasa_titexdata_07_texs_tex[];

TiTexDataTextures tutorial_kasa_titexdata_07_texs = {
    tutorial_kasa_titexdata_07_texs_tlut,
    tutorial_kasa_titexdata_07_texs_tex,
};

#define tutorial_kasa_titexdata_07_texs_tex_width 128
#define tutorial_kasa_titexdata_07_texs_tex_height 109

u16 tutorial_kasa_titexdata_07_info[] = {
    tutorial_kasa_titexdata_07_texs_tex_width,
    tutorial_kasa_titexdata_07_texs_tex_height,
    TITEX_FORMAT_8,
    TITEX_FLAGS_BLOCK,
};

u16 tutorial_kasa_titexdata_07_texs_tlut[] ALIGNED(8) = {
#include "assets/tutorial/tutorial_kasa/tutorial_kasa_titexdata_07_texs_tlut.rgba16.inc"
};
static_assert(ARRAY_COUNT(tutorial_kasa_titexdata_07_texs_tlut) == 16 * 16,
              "The dimensions of `tutorial_kasa_titexdata_07_texs_tlut` does not match the size of the actual tlut");

u8 tutorial_kasa_titexdata_07_texs_tex[] ALIGNED(8) = {
#include "assets/tutorial/tutorial_kasa/tutorial_kasa_titexdata_07_texs_tex.i8.inc"
};
static_assert(ARRAY_COUNT(tutorial_kasa_titexdata_07_texs_tex) ==
                  tutorial_kasa_titexdata_07_texs_tex_width * tutorial_kasa_titexdata_07_texs_tex_height,
              "The dimensions of `tutorial_kasa_titexdata_07_texs_tex` does not match the size of the actual texture");

#elif VERSION_CN

#define tutorial_kasa_titexdata_06_texs_tex_width 128
#define tutorial_kasa_titexdata_06_texs_tex_height 109

u16 tutorial_kasa_titexdata_06_info[] = {
    tutorial_kasa_titexdata_06_texs_tex_width,
    tutorial_kasa_titexdata_06_texs_tex_height,
    TITEX_FORMAT_8,
    TITEX_FLAGS_BLOCK,
};

u16 tutorial_kasa_titexdata_06_texs_tlut[] ALIGNED(8) = {
#include "assets/tutorial/tutorial_kasa/tutorial_kasa_titexdata_06_texs_tlut.rgba16.inc"
};
static_assert(ARRAY_COUNT(tutorial_kasa_titexdata_06_texs_tlut) == 16 * 16,
              "The dimensions of `tutorial_kasa_titexdata_06_texs_tlut` does not match the size of the actual tlut");

u8 tutorial_kasa_titexdata_06_texs_tex[] ALIGNED(8) = {
#include "assets/tutorial/tutorial_kasa/tutorial_kasa_titexdata_06_texs_tex.i8.inc"
};
static_assert(ARRAY_COUNT(tutorial_kasa_titexdata_06_texs_tex) ==
                  tutorial_kasa_titexdata_06_texs_tex_width * tutorial_kasa_titexdata_06_texs_tex_height,
              "The dimensions of `tutorial_kasa_titexdata_06_texs_tex` does not match the size of the actual texture");

/* titexdata_07 */

extern u16 tutorial_kasa_titexdata_07_texs_tlut[];
extern u8 tutorial_kasa_titexdata_07_texs_tex[];

TiTexDataTextures tutorial_kasa_titexdata_07_texs = {
    tutorial_kasa_titexdata_07_texs_tlut,
    tutorial_kasa_titexdata_07_texs_tex,
};

#define tutorial_kasa_titexdata_07_texs_tex_width 16
#define tutorial_kasa_titexdata_07_texs_tex_height 16

u16 tutorial_kasa_titexdata_07_info[] = {
    tutorial_kasa_titexdata_07_texs_tex_width,
    tutorial_kasa_titexdata_07_texs_tex_height,
    TITEX_FORMAT_4,
    TITEX_FLAGS_BLOCK,
};

u16 tutorial_kasa_titexdata_07_texs_tlut[] ALIGNED(8) = {
#include "assets/tutorial/tutorial_kasa/tutorial_kasa_titexdata_07_texs_tlut.rgba16.inc"
};
static_assert(ARRAY_COUNT(tutorial_kasa_titexdata_07_texs_tlut) == 4 * 4,
              "The dimensions of `tutorial_kasa_titexdata_07_texs_tlut` does not match the size of the actual tlut");

u8 tutorial_kasa_titexdata_07_texs_tex[] ALIGNED(8) = {
#include "assets/tutorial/tutorial_kasa/tutorial_kasa_titexdata_07_texs_tex.i4.inc"
};
static_assert(ARRAY_COUNT(tutorial_kasa_titexdata_07_texs_tex) ==
                  tutorial_kasa_titexdata_07_texs_tex_width * tutorial_kasa_titexdata_07_texs_tex_height / 2,
              "The dimensions of `tutorial_kasa_titexdata_07_texs_tex` does not match the size of the actual texture");
#endif

/* titexdata_08 */

extern u16 tutorial_kasa_titexdata_08_texs_tlut[];
extern u8 tutorial_kasa_titexdata_08_texs_tex[];

TiTexDataTextures tutorial_kasa_titexdata_08_texs = {
    tutorial_kasa_titexdata_08_texs_tlut,
    tutorial_kasa_titexdata_08_texs_tex,
};

#define tutorial_kasa_titexdata_08_texs_tex_width 128
#define tutorial_kasa_titexdata_08_texs_tex_height 70

u16 tutorial_kasa_titexdata_08_info[] = {
    tutorial_kasa_titexdata_08_texs_tex_width,
    tutorial_kasa_titexdata_08_texs_tex_height,
    TITEX_FORMAT_8,
    TITEX_FLAGS_BLOCK,
};

u16 tutorial_kasa_titexdata_08_texs_tlut[] ALIGNED(8) = {
#include "assets/tutorial/tutorial_kasa/tutorial_kasa_titexdata_08_texs_tlut.rgba16.inc"
};
static_assert(ARRAY_COUNT(tutorial_kasa_titexdata_08_texs_tlut) == 16 * 16,
              "The dimensions of `tutorial_kasa_titexdata_08_texs_tlut` does not match the size of the actual tlut");

u8 tutorial_kasa_titexdata_08_texs_tex[] ALIGNED(8) = {
#include "assets/tutorial/tutorial_kasa/tutorial_kasa_titexdata_08_texs_tex.i8.inc"
};
static_assert(ARRAY_COUNT(tutorial_kasa_titexdata_08_texs_tex) ==
                  tutorial_kasa_titexdata_08_texs_tex_width * tutorial_kasa_titexdata_08_texs_tex_height,
              "The dimensions of `tutorial_kasa_titexdata_08_texs_tex` does not match the size of the actual texture");

TiTexData tutorial_kasa_titexdata[] = {
    { &tutorial_kasa_titexdata_00_texs, tutorial_kasa_titexdata_00_info },
    { &tutorial_kasa_titexdata_01_texs, tutorial_kasa_titexdata_01_info },
    { &tutorial_kasa_titexdata_02_texs, tutorial_kasa_titexdata_02_info },
    { &tutorial_kasa_titexdata_03_texs, tutorial_kasa_titexdata_03_info },
    { &tutorial_kasa_titexdata_04_texs, tutorial_kasa_titexdata_04_info },
    { &tutorial_kasa_titexdata_05_texs, tutorial_kasa_titexdata_05_info },
#if VERSION_US || VERSION_GW
    { &tutorial_kasa_titexdata_06_texs, tutorial_kasa_titexdata_06_info },
    { &tutorial_kasa_titexdata_07_texs, tutorial_kasa_titexdata_07_info },
#elif VERSION_CN
    { &tutorial_kasa_titexdata_07_texs, tutorial_kasa_titexdata_07_info },
    { &tutorial_kasa_titexdata_06_texs, tutorial_kasa_titexdata_06_info },
#endif
    { &tutorial_kasa_titexdata_08_texs, tutorial_kasa_titexdata_08_info },
};

s32 tutorial_kasa_titexdata_len = ARRAY_COUNT(tutorial_kasa_titexdata);

#include "assets/title/title_bmp.h"

GRAPHBIN_START_u4(title_bmp_00, 192, 42)
#include "assets/title/title_bmp/title_bmp_00.palette.inc"
    GRAPHBIN_MIDDLE()
#include "assets/title/title_bmp/title_bmp_00.ci4.inc"
        GRAPHBIN_END();

GRAPHBIN_START_u16(title_bmp_01, 144, 16)
#include "assets/title/title_bmp/title_bmp_01_tlut.rgba16.inc"
    GRAPHBIN_MIDDLE()
#include "assets/title/title_bmp/title_bmp_01_tex.rgba16.inc"
        GRAPHBIN_END();

GRAPHBIN_START_u4(title_bmp_02, 144, 16)
#include "assets/title/title_bmp/title_bmp_02.palette.inc"
    GRAPHBIN_MIDDLE()
#include "assets/title/title_bmp/title_bmp_02.ci4.inc"
        GRAPHBIN_END();

#include "assets/title/title_bmp.h"

GraphBin_u4_192_42 title_bmp_00 = {
    {
        "GraphBin",
        192,
        42,
        1,
        4,
        {
#include "assets/title/title_bmp/title_bmp_00.palette.inc"
        },
    },
    {
#include "assets/title/title_bmp/title_bmp_00.ci4.inc"
    },
};

GraphBin_u16_144_16 title_bmp_01 = {
    {
        "GraphBin",
        144,
        16,
        1,
        16,
        {
#include "assets/title/title_bmp/title_bmp_01_tlut.rgba16.inc"
        },
    },
    {
#include "assets/title/title_bmp/title_bmp_01_tex.rgba16.inc"
    },
};

GraphBin_u4_144_16 title_bmp_02 = {
    {
        "GraphBin",
        144,
        16,
        1,
        4,
        {
#include "assets/title/title_bmp/title_bmp_02.palette.inc"
        },
    },
    {
#include "assets/title/title_bmp/title_bmp_02.ci4.inc"
    },
};

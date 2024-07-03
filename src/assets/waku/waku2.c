#include "assets/waku/waku2.h"

GraphBin_u16_320_20 waku2_00 = {
    {
        "GraphBin",
        320,
        20,
        1,
        16,
        {
#include "assets/waku/waku2/waku2_00_tlut.rgba16.inc"
        },
    },
    {
#include "assets/waku/waku2/waku2_00_tex.rgba16.inc"
    },
};

GraphBin_u4_320_20 waku2_01 = {
    {
        "GraphBin",
        320,
        20,
        1,
        4,
        {
#include "assets/waku/waku2/waku2_01.palette.inc"
        },
    },
    {
#include "assets/waku/waku2/waku2_01.ci4.inc"
    },
};

GraphBin_u8_320_80 waku2_02 = {
    {
        "GraphBin",
        320,
        80,
        1,
        8,
        {
#include "assets/waku/waku2/waku2_02.palette.inc"
        },
    },
    {
#include "assets/waku/waku2/waku2_02.ci8.inc"
    },
};

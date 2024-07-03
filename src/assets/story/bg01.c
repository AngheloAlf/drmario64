#include "graphbin.h"

GraphBin_u8_320_160 story_bg01 = {
    {
        "GraphBin",
        320,
        160,
        1,
        8,
        {
#include "assets/story/bg01/bg01.palette.inc"
        },
    },
    {
#include "assets/story/bg01/bg01.ci8.inc"
    },
};

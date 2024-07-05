#include "assets/waku/waku2.h"

GRAPHBIN_START_u16(waku2_00, 320, 20)
#include "assets/waku/waku2/waku2_00_tlut.rgba16.inc"
GRAPHBIN_MIDDLE()
#include "assets/waku/waku2/waku2_00_tex.rgba16.inc"
GRAPHBIN_END();

GRAPHBIN_START_u4(waku2_01, 320, 20)
#include "assets/waku/waku2/waku2_01.palette.inc"
GRAPHBIN_MIDDLE()
#include "assets/waku/waku2/waku2_01.ci4.inc"
GRAPHBIN_END();

GRAPHBIN_START_u8(waku2_02, 320, 80)
#include "assets/waku/waku2/waku2_02.palette.inc"
GRAPHBIN_MIDDLE()
#include "assets/waku/waku2/waku2_02.ci8.inc"
GRAPHBIN_END();

#include "ultra64.h"
#include "include_asm.h"
#include "macros_defines.h"
#include "unknown_structs.h"
#include "unk.h"
#include "main_segment_functions.h"
#include "main_segment_variables.h"


INCLUDE_ASM("asm/nonmatchings/main_segment/graphics/0020D0", func_8002BD20);

void func_8002BEE4(TexturePtr tlut) {
    gDPLoadTLUT_pal256(B_800EBCF4++, tlut);
}

void func_8002BF90(TexturePtr tlut, u32 pal) {
    gDPLoadTLUT_pal16(B_800EBCF4++, pal, tlut);
}

INCLUDE_ASM("asm/nonmatchings/main_segment/graphics/0020D0", func_8002C048);

INCLUDE_ASM("asm/nonmatchings/main_segment/graphics/0020D0", func_8002C1E8);

void func_8002C388(TexturePtr texture, s32 width, s32 height UNUSED, s32 uls, s32 ult, s32 lrs, s32 lrt) {
    gDPLoadTextureTile_4b(B_800EBCF4++, texture, G_IM_FMT_CI, width, height, uls, ult, lrs, lrt, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
}

INCLUDE_ASM("asm/nonmatchings/main_segment/graphics/0020D0", func_8002C4EC);

INCLUDE_ASM("asm/nonmatchings/main_segment/graphics/0020D0", func_8002C688);

// gSPTextureRectangle?
INCLUDE_ASM("asm/nonmatchings/main_segment/graphics/0020D0", func_8002C7C0);

INCLUDE_ASM("asm/nonmatchings/main_segment/graphics/0020D0", func_8002C914);

INCLUDE_ASM("asm/nonmatchings/main_segment/graphics/0020D0", func_8002CA68);

INCLUDE_ASM("asm/nonmatchings/main_segment/graphics/0020D0", func_8002CD08);

INCLUDE_ASM("asm/nonmatchings/main_segment/graphics/0020D0", func_8002CF04);

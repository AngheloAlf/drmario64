#include "ultra64.h"
#include "include_asm.h"
#include "macros_defines.h"
#include "unknown_structs.h"
#include "unk.h"
#include "main_segment_functions.h"
#include "main_segment_variables.h"


#if 0
void func_8002BD20(s32 red, s32 green, s32 blue, s32 alpha, s32 arg4, s32 arg5, s32 arg6, s32 arg7) {
    #if 0
    Gfx *temp_a1;
    Gfx *temp_t3;
    Gfx *temp_v1_2;
    s16 temp_t4;
    s32 temp_a2;
    s32 temp_t0;
    s32 temp_t2;
    s32 temp_v0;
    s32 temp_v1;
    u32 var_a0;

    temp_t3 = B_800EBCF4;
    B_800EBCF4 = temp_t3 + 8;
    temp_t3->words.w0 = 0xE7000000;
    B_800EBCF4 = temp_t3 + 0x10;
    temp_t3->unk_8 = 0xFA000000;
    temp_a1 = temp_t3 + 0x20;
    temp_t0 = arg4 + arg6;
    temp_t3->unk_14 = 0xFFFDF6FB;
    temp_t2 = arg5 + arg7;
    temp_t3->unk_C = (s32) ((arg0 << 0x18) | ((arg1 & 0xFF) << 0x10) | ((arg2 & 0xFF) << 8) | (arg3 & 0xFF));
    B_800EBCF4 = temp_t3 + 0x18;
    temp_t3->unk_18 = (s32) ((((temp_t0 * 4) & ((s32) ~(s16) (temp_t0 * 4) >> 0x1F) & 0xFFC) << 0xC) | (((temp_t2 * 4) & ((s32) ~(s16) (temp_t2 * 4) >> 0x1F) & 0xFFC) | 0xE4000000));
    temp_a2 = arg5 * 4;
    temp_t4 = arg4 * 4;
    B_800EBCF4 = temp_a1;
    B_800EBCF4 = temp_t3 + 0x28;
    temp_t3->words.w1 = 0;
    temp_t3->unk_10 = 0xFCFFFFFF;
    temp_t3->unk_1C = (s32) ((((arg4 * 4) & ((s32) ~temp_t4 >> 0x1F) & 0xFFC) << 0xC) | (temp_a2 & ((s32) ~(s16) (arg5 * 4) >> 0x1F) & 0xFFC));
    temp_t3->unk_20 = 0xE1000000;
    if (temp_t4 < 0) {
        temp_v1 = temp_t4 * 8;
        var_a0 = (temp_v1 & -(temp_v1 < 1)) * -0x10000;
    } else {
        var_a0 = 0;
    }
    temp_a1->words.w1 = var_a0;
    if (arg5 & 0x20000000) {
        temp_v0 = (s32) (temp_a2 << 0x10) >> 0xD;
        temp_a1->words.w1 = var_a0 | (-(temp_v0 & -(temp_v0 < 1)) & 0xFFFF);
    }
    temp_v1_2 = B_800EBCF4;
    B_800EBCF4 = temp_v1_2 + 8;
    temp_v1_2->words.w0 = 0xF1000000;
    temp_v1_2->words.w1 = 0x04000400;
    #endif

    gDPPipeSync(B_800EBCF4++);
    gDPSetPrimColor(B_800EBCF4++, 0, 0, red, green, blue, alpha);
    gDPSetCombineMode(B_800EBCF4++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
    gSPTextureRectangle(B_800EBCF4++, arg4 << 2, arg5 << 2, (arg4 + arg6) << 2, (arg4 + arg7) << 2, G_TX_RENDERTILE, 0, 0, 0x0400, 0x0400);
}
#else
INCLUDE_ASM("asm/nonmatchings/main_segment/graphics/0020D0", func_8002BD20);
#endif

void func_8002BEE4(TexturePtr tlut) {
    gDPLoadTLUT_pal256(B_800EBCF4++, tlut);
}

void func_8002BF90(TexturePtr tlut, u32 pal) {
    gDPLoadTLUT_pal16(B_800EBCF4++, pal, tlut);
}

void func_8002C048(TexturePtr texture, s32 width, s32 height) {
    gDPLoadTextureBlock_4b(B_800EBCF4++,
        texture,
        G_IM_FMT_CI,
        width, height,
        0,
        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
        G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD
    );
}

void func_8002C1E8(TexturePtr texture, s32 width, s32 height) {
    gDPLoadTextureBlock_4b(B_800EBCF4++,
        texture,
        G_IM_FMT_I,
        width, height,
        0,
        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
        G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD
    );
}

void func_8002C388(TexturePtr texture, s32 width, s32 height UNUSED, s32 uls, s32 ult, s32 lrs, s32 lrt) {
    gDPLoadTextureTile_4b(B_800EBCF4++, texture, G_IM_FMT_CI, width, height, uls, ult, lrs, lrt, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
}

void func_8002C4EC(TexturePtr texture, s32 width, s32 height) {
    gDPLoadTextureBlock(B_800EBCF4++,
        texture,
        G_IM_FMT_CI, G_IM_SIZ_8b,
        width, height,
        0,
        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
        G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD
    );
}

INCLUDE_ASM("asm/nonmatchings/main_segment/graphics/0020D0", func_8002C688);

// gSPTextureRectangle?
INCLUDE_ASM("asm/nonmatchings/main_segment/graphics/0020D0", func_8002C7C0);

INCLUDE_ASM("asm/nonmatchings/main_segment/graphics/0020D0", func_8002C914);

INCLUDE_ASM("asm/nonmatchings/main_segment/graphics/0020D0", func_8002CA68);

INCLUDE_ASM("asm/nonmatchings/main_segment/graphics/0020D0", func_8002CD08);

INCLUDE_ASM("asm/nonmatchings/main_segment/graphics/0020D0", func_8002CF04);

#include "static.h"

#include "include_asm.h"
#include "macros_defines.h"
#include "unknown_structs.h"
#include "unk.h"
#include "main_segment_variables.h"

#if VERSION_US || VERSION_CN
void func_8002BD20(u8 red, u8 green, u8 blue, u8 alpha, s32 arg4, s32 arg5, s32 arg6, s32 arg7) {
    s32 a;
    s32 b;
    s32 c;
    s32 d;

    gDPPipeSync(gGfxHead++);
    gDPSetPrimColor(gGfxHead++, 0, 0, red, green, blue, alpha);
    gDPSetCombineMode(gGfxHead++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);

    a = arg4 << 2;
    b = arg5 << 2;
    c = (arg4 + arg6) << 2;
    d = (arg5 + arg7) << 2;

    gSPScisTextureRectangle(gGfxHead++, a, b, c, d, G_TX_RENDERTILE, 0, 0, 0x0400, 0x0400);
}
#endif

#if VERSION_US || VERSION_CN
/**
 * Original name: load_TexPal
 */
void load_TexPal(TexturePtr tlut) {
    gDPLoadTLUT_pal256(gGfxHead++, tlut);
}
#endif

#if VERSION_US || VERSION_CN
void func_8002BF90(TexturePtr tlut, u32 pal) {
    gDPLoadTLUT_pal16(gGfxHead++, pal, tlut);
}
#endif

#if VERSION_US || VERSION_CN
void load_TexBlock_4b(TexturePtr texture, s32 width, s32 height) {
    gDPLoadTextureBlock_4b(gGfxHead++, texture, G_IM_FMT_CI, width, height, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                           G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
}
#endif

#if VERSION_US || VERSION_CN
void func_8002C1E8(TexturePtr texture, s32 width, s32 height) {
    gDPLoadTextureBlock_4b(gGfxHead++, texture, G_IM_FMT_I, width, height, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                           G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
}
#endif

#if VERSION_US || VERSION_CN
void load_TexTile_4b(TexturePtr texture, s32 width, s32 height UNUSED, s32 uls, s32 ult, s32 lrs, s32 lrt) {
    gDPLoadTextureTile_4b(gGfxHead++, texture, G_IM_FMT_CI, width, height, uls, ult, lrs, lrt, 0,
                          G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                          G_TX_NOLOD);
}
#endif

#if VERSION_US || VERSION_CN
void func_8002C4EC(TexturePtr texture, s32 width, s32 height) {
    gDPLoadTextureBlock(gGfxHead++, texture, G_IM_FMT_CI, G_IM_SIZ_8b, width, height, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
}
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/graphics/static", func_8002C688);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/graphics/static", func_8002E36C_cn);
#endif

#if VERSION_US || VERSION_CN
void draw_Tex(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    gSPScisTextureRectangle(gGfxHead++, arg0 << 2, arg1 << 2, (arg0 + arg2) << 2, (arg1 + arg3) << 2, G_TX_RENDERTILE,
                            arg4 << 5, arg5 << 5, 1 << 10, 1 << 10);
}
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/graphics/static", func_8002C914);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/graphics/static", func_8002E5E8_cn);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/graphics/static", func_8002CA68);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/graphics/static", func_8002E710_cn);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/graphics/static", func_8002CD08);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/graphics/static", func_8002E968_cn);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/graphics/static", func_8002CF04);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/graphics/static", func_8002EB24_cn);
#endif

/**
 * Original filename: tex_func.c
 */

#include "tex_func.h"
#include "include_asm.h"
#include "unk.h"
#include "util.h"
#include "macros_defines.h"
#include "boot_functions.h"
#include "boot_variables.h"
#include "main_segment_variables.h"

/**
 * Original name: copy_texture_init_dl
 */
Gfx copy_texture_init_dl[] = {
#include "main_segment/tex_func/copy_texture_init_dl.gfx.inc.c"
};

/**
 * Original name: alpha_texture_init_dl
 */
Gfx alpha_texture_init_dl[] = {
#include "main_segment/tex_func/alpha_texture_init_dl.gfx.inc.c"
};

/**
 * Original name: normal_texture_init_dl
 */
Gfx normal_texture_init_dl[] = {
#include "main_segment/tex_func/normal_texture_init_dl.gfx.inc.c"
};

Gfx D_8008E728[] = {
#include "main_segment/tex_func/D_8008E728.gfx.inc.c"
};

/**
 * Original name: init_dl_155
 */
Gfx init_dl_155[] = {
#include "main_segment/tex_func/init_dl_155.gfx.inc.c"
};

/**
 * Original name: _modes_96
 */
const s32 _modes_96[] = {
    G_SC_ODD_INTERLACE,  // GFXSETSCISSOR_INTERLACE_ODD
    G_SC_EVEN_INTERLACE, // GFXSETSCISSOR_INTERLACE_EVEN
    G_SC_NON_INTERLACE,  // GFXSETSCISSOR_INTERLACE_NO
    G_SC_NON_INTERLACE,  // GFXSETSCISSOR_INTERLACE_NO2
};

/**
 * Original name: gfxSetScissor
 */
void gfxSetScissor(Gfx **gfxP, GfxSetScissorMode mode, s32 x, s32 y, s32 width, s32 height) {
    Gfx *gfx = *gfxP;
    s32 corners[] = {
        CLAMP(x, 0, SCREEN_WIDTH - 1),               // ulx
        CLAMP(y, 0, SCREEN_HEIGHT - 1),              // uly
        CLAMP(x + width - 1, 0, SCREEN_WIDTH - 1),   // lrx
        CLAMP(y + height - 1, 0, SCREEN_HEIGHT - 1), // lry
    };

    gDPSetScissor(gfx++, _modes_96[mode % ARRAY_COUNTU(_modes_96)], corners[0], corners[1], corners[2], corners[3]);

    *gfxP = gfx;
}

void func_80040D34(Gfx **gxfP, s32 x, s32 y, s32 width, s32 height, s32 red, s32 green, s32 blue) {
    Gfx *gfx = *gxfP;
    s32 color = GPACK_RGBA5551(red, green, blue, 1);

    color = color | (color << 0x10);

    gSPDisplayList(gfx++, D_8008E728);
    gDPSetFillColor(gfx++, color);
    gDPScisFillRectangle(gfx++, x, y, x + width - 1, y + height - 1);

    *gxfP = gfx;
}

/**
 * Original name: FillRectRGBA
 */
void FillRectRGBA(Gfx **gfxP, s32 x, s32 y, s32 width, s32 height, s32 red, s32 green, s32 blue, s32 alpha) {
    Gfx *gfx = *gfxP;

    gSPDisplayList(gfx++, init_dl_155);
    gDPSetPrimColor(gfx++, 0, 0, red, green, blue, alpha);
    gDPScisFillRectangle(gfx++, x, y, x + width, y + height);

    *gfxP = gfx;
}

/**
 * Original name: CopyTexBlock
 */
void CopyTexBlock(struct_CopyTexBlock_arg0 *arg0) {
    s32 var_v0;

    var_v0 = arg0->unk_08;
    if (var_v0 >= 0) {
        var_v0 *= 4;
    }

    for (arg0->unk_20 = 0; arg0->unk_20 < arg0->unk_14; arg0->unk_20 += arg0->unk_1C) {
        arg0->unk_24 = MIN(arg0->unk_20 + arg0->unk_1C, arg0->unk_14);

        if (arg0->unk_04 != NULL) {
            arg0->unk_18(arg0);
        }

        gSPScisTextureRectangle((*arg0->gfxP)++, var_v0, (arg0->unk_0C + arg0->unk_20) << 2,
                                ((arg0->unk_08 + arg0->unk_10) - 1) << 2, ((arg0->unk_0C + arg0->unk_24) - 1) << 2,
                                G_TX_RENDERTILE, 0, 0, 4 << 10, 1 << 10);
    }
}

/**
 * Original name: CopyTexBlock4_LoadTex
 */
void CopyTexBlock4_LoadTex(struct_CopyTexBlock_arg0 *arg0) {
    gDPLoadTextureBlock_4b((*arg0->gfxP)++, (u8 *)arg0->unk_04 + ((arg0->unk_10 * arg0->unk_20) / 2), G_IM_FMT_CI,
                           arg0->unk_10, arg0->unk_24 - arg0->unk_20, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                           G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
}

/**
 * Original name: CopyTexBlock4
 */
void CopyTexBlock4(Gfx **gfxP, u16 *tlut, void *arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    struct_CopyTexBlock_arg0 sp18;

    sp18.gfxP = gfxP;

    sp18.unk_04 = arg2;
    sp18.unk_08 = arg3;
    sp18.unk_0C = arg4;
    sp18.unk_10 = arg5;
    sp18.unk_14 = arg6;
    sp18.unk_18 = CopyTexBlock4_LoadTex;
    sp18.unk_1C = 0x1000 / arg5;

    gSPDisplayList((*gfxP)++, copy_texture_init_dl);

    if (tlut != NULL) {
        gDPLoadTLUT_pal16((*gfxP)++, 0, tlut);
    }

    CopyTexBlock(&sp18);
}

/**
 * Original name: CopyTexBlock8_LoadTex
 */
void CopyTexBlock8_LoadTex(struct_CopyTexBlock_arg0 *arg0) {
    gDPLoadTextureBlock((*arg0->gfxP)++, (u8 *)arg0->unk_04 + arg0->unk_10 * arg0->unk_20, G_IM_FMT_CI, G_IM_SIZ_8b,
                        arg0->unk_10, arg0->unk_24 - arg0->unk_20, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK,
                        G_TX_NOLOD, G_TX_NOLOD);
}

/**
 * Original name: CopyTexBlock8
 */
void CopyTexBlock8(Gfx **gfxP, u16 tlut[], TexturePtr arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    struct_CopyTexBlock_arg0 sp18;

    sp18.gfxP = gfxP;
    sp18.unk_04 = arg2;
    sp18.unk_08 = arg3;
    sp18.unk_18 = CopyTexBlock8_LoadTex;
    sp18.unk_0C = arg4;
    sp18.unk_10 = arg5;
    sp18.unk_14 = arg6;
    sp18.unk_1C = 0x800 / arg5;

    gSPDisplayList((*gfxP)++, copy_texture_init_dl);

    if (tlut != NULL) {
        gDPLoadTLUT_pal256((*gfxP)++, tlut);
    }

    CopyTexBlock(&sp18);
}

/**
 * Original name: CopyTexBlock16_LoadTex
 */
void CopyTexBlock16_LoadTex(struct_CopyTexBlock_arg0 *arg0) {
    gDPLoadTextureBlock((*arg0->gfxP)++, (u16 *)arg0->unk_04 + arg0->unk_10 * arg0->unk_20, G_IM_FMT_RGBA, G_IM_SIZ_16b,
                        arg0->unk_10, arg0->unk_24 - arg0->unk_20, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK,
                        G_TX_NOLOD, G_TX_NOLOD);
}

/**
 * Original name: CopyTexBlock16
 */
void CopyTexBlock16(Gfx **gfxP, TexturePtr arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    struct_CopyTexBlock_arg0 sp18;

    sp18.gfxP = gfxP;
    sp18.unk_04 = arg1;
    sp18.unk_08 = arg2;
    sp18.unk_0C = arg3;
    sp18.unk_18 = CopyTexBlock16_LoadTex;
    sp18.unk_10 = arg4;
    sp18.unk_14 = arg5;
    sp18.unk_1C = 0x800 / arg4;

    gSPDisplayList((*gfxP)++, copy_texture_init_dl);
    gDPSetTextureLUT((*gfxP)++, G_TT_NONE);

    CopyTexBlock(&sp18);
}

/**
 * Original name: StretchTexBlock
 */
void StretchTexBlock(StretchTexBlock_arg0 *arg0) {
    s32 sp18[2];
    StretchTexBlock_arg0_unk_4C *temp_s0;
    s32 var_a3;
    s32 var_s2;
    s32 var_s3;
    s32 var_s4;
    s32 var_v0_3;
    s32 var_v1;

    if (arg0->unk_28 < 0) {
        var_a3 = -arg0->unk_28;
        sp18[0] = -1;
    } else if (arg0->unk_28 > 0) {
        var_a3 = arg0->unk_28;
        sp18[0] = 1;
    } else {
        return;
    }

    if (arg0->unk_2C < 0) {
        var_s2 = -arg0->unk_2C;
        sp18[1] = -1;
    } else if (arg0->unk_2C > 0) {
        var_s2 = arg0->unk_2C;
        sp18[1] = 1;
    } else {
        return;
    }

    if ((arg0->unk_04 == 0) && (var_a3 == (arg0->unk_08 << 2)) && (var_s2 == (arg0->unk_0C << 2))) {
        gDPSetTextureFilter((*arg0->gfxP)++, G_TF_POINT);
        var_s4 = 0;
        var_s3 = arg0->unk_38;
    } else {
        gDPSetTextureFilter((*arg0->gfxP)++, G_TF_BILERP);
        var_s4 = -1;
        var_s3 = MAX(arg0->unk_38 - 1, 1);
    }

    temp_s0 = &arg0->unk_4C;

    arg0->unk_4C.unk_00 = arg0->unk_20;
    temp_s0->unk_08 = arg0->unk_20 + var_a3;

    if (sp18[0] < 0) {
        var_v0_3 = (arg0->unk_08 - 1) << 5;
    } else {
        var_v0_3 = 0;
    }
    temp_s0->unk_10 = var_v0_3;

    temp_s0->unk_18 = ((sp18[0] << 0xC) * arg0->unk_08) / var_a3;

    for (arg0->unk_40 = 0; arg0->unk_40 < arg0->unk_0C; arg0->unk_40 += var_s3) {
        arg0->unk_44 = MIN(arg0->unk_40 + arg0->unk_38, arg0->unk_0C);
        arg0->height = arg0->unk_44 - arg0->unk_40;
        if (arg0->unk_10 != NULL) {
            arg0->unk_30(arg0);
        }
        if (arg0->unk_18 != NULL) {
            arg0->unk_34(arg0);
        }

        if (sp18[1] < 0) {
            temp_s0->unk_04 = arg0->unk_0C - arg0->unk_44;
            temp_s0->unk_0C = arg0->unk_0C - arg0->unk_40;
            temp_s0->unk_14 = arg0->height - 1;
        } else {
            temp_s0->unk_04 = arg0->unk_40;
            temp_s0->unk_0C = arg0->unk_44;
            temp_s0->unk_14 = 0;
        }

        temp_s0->unk_04 = arg0->unk_24 + (((temp_s0->unk_04 << 2) * var_s2) / (arg0->unk_0C << 2));
        temp_s0->unk_0C = arg0->unk_24 + (((temp_s0->unk_0C << 2) * var_s2) / (arg0->unk_0C << 2));
        temp_s0->unk_14 = temp_s0->unk_14 << 5;
        temp_s0->unk_1C = (sp18[1] << 0xC) * arg0->unk_0C / var_s2;

        var_v1 = temp_s0->unk_1C;
        if (var_v1 < 0) {
            var_v1 += 0x3F;
        }
        temp_s0->unk_14 -= (var_v1 >> 6) & var_s4;

        arg0->unk_3C(arg0);
    }
}

/**
 * Original name: StretchTexBlock_ScisRect
 */
void StretchTexBlock_ScisRect(StretchTexBlock_arg0 *arg0) {
    StretchTexBlock_arg0_unk_4C *temp_a2 = &arg0->unk_4C;

    gSPScisTextureRectangle((*arg0->gfxP)++, temp_a2->unk_00, temp_a2->unk_04, temp_a2->unk_08, temp_a2->unk_0C,
                            G_TX_RENDERTILE, temp_a2->unk_10, temp_a2->unk_14, temp_a2->unk_18, temp_a2->unk_1C);
}

/**
 * Original name: StretchAlphaTexBlock_LoadColorTex
 */
void StretchAlphaTexBlock_LoadColorTex(StretchTexBlock_arg0 *arg0) {
    gDPLoadTextureBlock((*arg0->gfxP)++, (u16 *)arg0->unk_10 + (arg0->width * arg0->unk_40), G_IM_FMT_RGBA,
                        G_IM_SIZ_16b, arg0->width, arg0->height, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
}

/**
 * Original name: StretchAlphaTexBlock_LoadAlphaTex
 */
void StretchAlphaTexBlock_LoadAlphaTex(StretchTexBlock_arg0 *arg0) {
    gDPLoadMultiBlock_4b((*arg0->gfxP)++, arg0->unk_18 + (arg0->unk_1C * arg0->unk_40) / 2, 0x19A, 1, G_IM_FMT_I,
                         arg0->unk_1C, arg0->height, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                         G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
}

/**
 * Original name: StretchAlphaTexBlock
 */
void StretchAlphaTexBlock(Gfx **gfxP, s32 arg1, s32 arg2, TexturePtr arg3, s32 arg4, TexturePtr arg5, s32 arg6,
                          f32 arg7, f32 arg8, f32 arg9, f32 argA) {
    StretchTexBlock_arg0 sp18;

    sp18.gfxP = gfxP;
    sp18.unk_04 = 0;
    sp18.unk_08 = arg1;
    sp18.unk_20 = arg7 * 4.0;
    sp18.unk_24 = arg8 * 4.0;
    sp18.unk_28 = arg9 * 4.0;
    sp18.unk_2C = argA * 4.0;
    sp18.unk_0C = arg2;
    sp18.unk_10 = arg3;
    sp18.unk_30 = StretchAlphaTexBlock_LoadColorTex;
    sp18.unk_34 = StretchAlphaTexBlock_LoadAlphaTex;
    sp18.width = arg4;
    sp18.unk_18 = arg5;
    sp18.unk_1C = arg6;

    sp18.unk_38 = 0x660 / MAX(arg4, arg6);
    sp18.unk_3C = StretchTexBlock_ScisRect;

    StretchTexBlock(&sp18);
}

/**
 * Original name: StretchTexBlock4_LoadTex
 */
void StretchTexBlock4_LoadTex(StretchTexBlock_arg0 *arg0) {
    gDPLoadTextureBlock_4b((*arg0->gfxP)++, arg0->unk_10 + ((arg0->width * arg0->unk_40) / 2), G_IM_FMT_CI, arg0->width,
                           arg0->height, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK,
                           G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
}

/**
 * Original name: StretchTexBlock4
 */
void StretchTexBlock4(Gfx **gfxP, s32 arg1, s32 arg2, TexturePtr tlut, UNK_PTR arg4, f32 arg5, f32 arg6, f32 arg7,
                      f32 arg8) {
    StretchTexBlock_arg0 sp10;

    sp10.gfxP = gfxP;
    sp10.unk_04 = 0;
    sp10.unk_08 = arg1;
    sp10.unk_0C = arg2;
    sp10.width = arg1;
    sp10.unk_18 = 0;
    sp10.unk_1C = 0;
    sp10.unk_34 = NULL;
    sp10.unk_30 = StretchTexBlock4_LoadTex;
    sp10.unk_3C = StretchTexBlock_ScisRect;
    sp10.unk_10 = arg4;
    sp10.unk_20 = arg5 * 4.0;
    sp10.unk_24 = arg6 * 4.0;
    sp10.unk_28 = arg7 * 4.0;
    sp10.unk_2C = arg8 * 4.0;
    sp10.unk_38 = 0x1000 / arg1;
    if (tlut != NULL) {
        gDPLoadTLUT_pal16((*gfxP)++, 0, tlut);
    }
    StretchTexBlock(&sp10);
}

/**
 * Original name: StretchTexBlock8_LoadTex
 */
void StretchTexBlock8_LoadTex(StretchTexBlock_arg0 *arg0) {
    gDPLoadTextureBlock((*arg0->gfxP)++, (u8 *)arg0->unk_10 + (arg0->width * arg0->unk_40), G_IM_FMT_CI, G_IM_SIZ_8b,
                        arg0->width, arg0->height, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
}

/**
 * Original name: StretchTexBlock8
 */
void StretchTexBlock8(Gfx **gfxP, s32 arg1, s32 arg2, TexturePtr tlut, UNK_PTR arg4, f32 arg5, f32 arg6, f32 arg7,
                      f32 arg8) {
    StretchTexBlock_arg0 sp10;

    sp10.gfxP = gfxP;
    sp10.unk_04 = 0;
    sp10.unk_30 = StretchTexBlock8_LoadTex;
    sp10.unk_08 = arg1;
    sp10.unk_0C = arg2;
    sp10.width = arg1;
    sp10.unk_18 = 0;
    sp10.unk_1C = 0;
    sp10.unk_34 = NULL;
    sp10.unk_3C = StretchTexBlock_ScisRect;
    sp10.unk_10 = arg4;
    sp10.unk_20 = arg5 * 4.0;
    sp10.unk_24 = arg6 * 4.0;
    sp10.unk_28 = arg7 * 4.0;
    sp10.unk_2C = arg8 * 4.0;
    sp10.unk_38 = 0x800 / arg1;
    if (tlut != NULL) {
        gDPLoadTLUT_pal256((*gfxP)++, tlut);
    }

    StretchTexBlock(&sp10);
}

/**
 * Original name: StretchTexBlock16_LoadTex
 */
void StretchTexBlock16_LoadTex(StretchTexBlock_arg0 *arg0) {
    gDPLoadTextureBlock((*arg0->gfxP)++, (u16 *)arg0->unk_10 + (arg0->width * arg0->unk_40), G_IM_FMT_RGBA,
                        G_IM_SIZ_16b, arg0->width, arg0->height, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
}

/**
 * Original name: StretchTexBlock16
 */
void StretchTexBlock16(Gfx **gfxP, s32 arg1, s32 arg2, UNK_PTR arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7) {
    StretchTexBlock_arg0 sp18;

    sp18.gfxP = gfxP;
    sp18.unk_04 = 0;
    sp18.unk_08 = arg1;
    sp18.unk_0C = arg2;
    sp18.unk_10 = arg3;
    sp18.width = arg1;
    sp18.unk_18 = NULL;
    sp18.unk_1C = 0;
    sp18.unk_30 = StretchTexBlock16_LoadTex;
    sp18.unk_34 = NULL;
    sp18.unk_3C = StretchTexBlock_ScisRect;
    sp18.unk_20 = arg4 * 4.0;
    sp18.unk_24 = arg5 * 4.0;
    sp18.unk_28 = arg6 * 4.0;
    sp18.unk_2C = arg7 * 4.0;
    sp18.unk_38 = 0x800 / arg1;
    StretchTexBlock(&sp18);
}

/**
 * Original name: StretchTexBlock4i_LoadTex
 */
void StretchTexBlock4i_LoadTex(StretchTexBlock_arg0 *arg0) {
    gDPLoadTextureBlock_4b((*arg0->gfxP)++, arg0->unk_10 + (arg0->width * arg0->unk_40) / 2, G_IM_FMT_I, arg0->width,
                           arg0->height, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK,
                           G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
}

/**
 * Original name: StretchTexBlock4i
 */
void StretchTexBlock4i(Gfx **gfxP, s32 arg1, s32 arg2, void *arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7) {
    StretchTexBlock_arg0 sp10;

    sp10.gfxP = gfxP;
    sp10.unk_04 = 0;
    sp10.unk_08 = arg1;
    sp10.unk_0C = arg2;
    sp10.unk_10 = arg3;
    sp10.width = arg1;
    sp10.unk_18 = NULL;
    sp10.unk_1C = 0;
    sp10.unk_30 = StretchTexBlock4i_LoadTex;
    sp10.unk_34 = NULL;
    sp10.unk_3C = StretchTexBlock_ScisRect;
    sp10.unk_20 = arg4 * 4.0;
    sp10.unk_24 = arg5 * 4.0;
    sp10.unk_28 = arg6 * 4.0;
    sp10.unk_2C = arg7 * 4.0;
    sp10.unk_38 = 0x2000 / arg1;

    StretchTexBlock(&sp10);
}

void func_800430D0(StretchTexBlock_arg0 *arg0) {
    gDPLoadTextureBlock((*arg0->gfxP)++, arg0->unk_10 + (arg0->width * arg0->unk_40), G_IM_FMT_I, G_IM_SIZ_8b,
                        arg0->width, arg0->height, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
}

void func_800432A8(Gfx **gfxP, s32 arg1, s32 arg2, UNK_PTR arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7) {
    StretchTexBlock_arg0 sp10;

    sp10.gfxP = gfxP;
    sp10.unk_04 = 0;
    sp10.unk_08 = arg1;
    sp10.unk_0C = arg2;
    sp10.unk_10 = arg3;
    sp10.width = arg1;
    sp10.unk_18 = 0;
    sp10.unk_1C = 0;

    sp10.unk_30 = func_800430D0;
    sp10.unk_34 = NULL;
    sp10.unk_3C = StretchTexBlock_ScisRect;

    sp10.unk_20 = arg4 * 4.0;
    sp10.unk_24 = arg5 * 4.0;
    sp10.unk_28 = arg6 * 4.0;
    sp10.unk_2C = arg7 * 4.0;
    sp10.unk_38 = 0x1000 / arg1;

    StretchTexBlock(&sp10);
}

/**
 * Original name: StretchTexTile
 */
void StretchTexTile(StretchTexTile_arg0 *arg0) {
    s32 sp18[2];
    StretchTexTile_arg0_unk_58 *temp_s0;
    s32 temp_s2;
    s32 var_a3;
    s32 var_s3;
    s32 var_s4;
    s32 var_s5;
    s32 var_v1;
    s32 v0;
    s32 t0;

    if (arg0->unk_38 < 0) {
        var_a3 = -arg0->unk_38;
        sp18[0] = -1;
    } else if (arg0->unk_38 > 0) {
        var_a3 = arg0->unk_38;
        sp18[0] = 1;
    } else {
        return;
    }

    if (arg0->unk_3C < 0) {
        var_s3 = -arg0->unk_3C;
        sp18[1] = -1;
    } else if (arg0->unk_3C > 0) {
        var_s3 = arg0->unk_3C;
        sp18[1] = 1;
    } else {
        return;
    }

    v0 = arg0->unk_20;
    t0 = v0 + arg0->unk_28;
    temp_s2 = arg0->unk_24 + arg0->unk_2C;
    if ((arg0->vtxP == NULL) && (var_a3 == (arg0->unk_28 << 2)) && (var_s3 == (arg0->unk_2C << 2))) {
        gDPSetTextureFilter((*arg0->gfxP)++, G_TF_POINT);
        var_s5 = 0;
        var_s4 = arg0->unk_48;
    } else {
        gDPSetTextureFilter((*arg0->gfxP)++, G_TF_BILERP);
        var_s5 = -1;
        var_s4 = MAX(arg0->unk_48 - 1, 1);
    }

    temp_s0 = &arg0->unk_58;

    arg0->unk_58.unk_00 = arg0->unk_30;
    temp_s0->unk_08 = arg0->unk_30 + var_a3;

    temp_s0->unk_10 = ((sp18[0] < 0) ? (t0 - 1) : arg0->unk_20) << 5;

    temp_s0->unk_18 = ((sp18[0] << 0xC) * arg0->unk_28) / var_a3;

    for (arg0->unk_50 = arg0->unk_24; arg0->unk_50 < temp_s2; arg0->unk_50 += var_s4) {
        arg0->unk_54 = MIN(arg0->unk_50 + arg0->unk_48, temp_s2);

        if (arg0->texture != NULL) {
            arg0->unk_40(arg0);
        }

        if (arg0->unk_18 != NULL) {
            arg0->unk_44(arg0);
        }

        if (sp18[1] < 0) {
            temp_s0->unk_04 = temp_s2 - arg0->unk_54;
            temp_s0->unk_0C = temp_s2 - arg0->unk_50;
            temp_s0->unk_14 = arg0->unk_54 - 1;
        } else {
            temp_s0->unk_04 = arg0->unk_50;
            temp_s0->unk_0C = arg0->unk_54;
            temp_s0->unk_14 = arg0->unk_50;
        }

        temp_s0->unk_04 =
            arg0->unk_34 + ((((temp_s0->unk_04 - arg0->unk_24) << 2) * var_s3) / (s32)(arg0->unk_2C << 2));
        temp_s0->unk_0C =
            arg0->unk_34 + ((((temp_s0->unk_0C - arg0->unk_24) << 2) * var_s3) / (s32)(arg0->unk_2C << 2));

        temp_s0->unk_14 = temp_s0->unk_14 << 5;
        temp_s0->unk_1C = ((sp18[1] << 0xC) * arg0->unk_2C) / var_s3;

        var_v1 = temp_s0->unk_1C;
        if (var_v1 < 0) {
            var_v1 += 0x3F;
        }
        temp_s0->unk_14 -= (var_v1 >> 6) & var_s5;

        arg0->unk_4C(arg0);
    }
}

/**
 * Original name: StretchTexTile_ScisRect
 */
void StretchTexTile_ScisRect(StretchTexTile_arg0 *arg0) {
    StretchTexTile_arg0_unk_58 *temp_a2 = &arg0->unk_58;

    gSPScisTextureRectangle((*arg0->gfxP)++, temp_a2->unk_00, temp_a2->unk_04, temp_a2->unk_08, temp_a2->unk_0C,
                            G_TX_RENDERTILE, temp_a2->unk_10, temp_a2->unk_14, temp_a2->unk_18, temp_a2->unk_1C);
}

/**
 * Original name: RectTexTile_ScisRect
 */
void RectTexTile_ScisRect(StretchTexTile_arg0 *arg0) {
    Gfx *gfx = *arg0->gfxP;
    Vtx *vtx = *arg0->vtxP;
    StretchTexTile_arg0_unk_58 *temp_a3;

    gSPVertex(gfx++, vtx, 4, 0);
    gSP2Triangles(gfx++, 0, 1, 2, 0, 3, 2, 1, 0);

    temp_a3 = &arg0->unk_58;

    vtx[0].v.ob[0] = vtx[1].v.ob[0] = temp_a3->unk_00 >> 2;
    vtx[0].v.ob[1] = vtx[2].v.ob[1] = temp_a3->unk_04 >> 2;
    vtx[2].v.ob[0] = vtx[3].v.ob[0] = temp_a3->unk_08 >> 2;
    vtx[1].v.ob[1] = vtx[3].v.ob[1] = temp_a3->unk_0C >> 2;

    vtx[0].v.tc[0] = vtx[1].v.tc[0] = temp_a3->unk_10 << 2;
    vtx[0].v.tc[1] = vtx[2].v.tc[1] = temp_a3->unk_14 << 2;

    vtx[2].v.tc[0] = vtx[3].v.tc[0] =
        (((temp_a3->unk_08 - temp_a3->unk_00) * temp_a3->unk_18) + (temp_a3->unk_10 << 7)) >> 5;

    vtx[1].v.tc[1] = vtx[3].v.tc[1] =
        (((temp_a3->unk_0C - temp_a3->unk_04) * temp_a3->unk_1C) + (temp_a3->unk_14 << 7)) >> 5;

    *(u32 *)&vtx[3].v.ob[2] = 0;
    *(u32 *)&vtx[2].v.ob[2] = 0;
    *(u32 *)&vtx[1].v.ob[2] = 0;
    *(u32 *)&vtx[0].v.ob[2] = 0;
    *(u32 *)vtx[3].v.cn = 0xFFFFFFFF;
    *(u32 *)vtx[2].v.cn = 0xFFFFFFFF;
    *(u32 *)vtx[1].v.cn = 0xFFFFFFFF;
    *(u32 *)vtx[0].v.cn = 0xFFFFFFFF;

    *arg0->vtxP = &vtx[4];
    *arg0->gfxP = gfx;
}

/**
 * Original name: StretchAlphaTexTile_LoadColorTex
 */
void StretchAlphaTexTile_LoadColorTex(StretchTexTile_arg0 *arg0) {
    gDPLoadTextureTile((*arg0->gfxP)++, arg0->texture, G_IM_FMT_RGBA, G_IM_SIZ_16b, arg0->unk_14, 0, arg0->unk_20,
                       arg0->unk_50, ((arg0->unk_20 + arg0->unk_28) - 1), (arg0->unk_54 - 1), 0,
                       G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                       G_TX_NOLOD);
}

/**
 * Original name: StretchAlphaTexTile_LoadAlphaTex
 */
void StretchAlphaTexTile_LoadAlphaTex(StretchTexTile_arg0 *arg0) {
    gDPLoadMultiTile_4b((*arg0->gfxP)++, arg0->unk_18, 0x019A, 1, G_IM_FMT_I, arg0->unk_1C, 0, arg0->unk_20,
                        arg0->unk_50, (arg0->unk_20 + arg0->unk_28) - 1, arg0->unk_54 - 1, 0,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                        G_TX_NOLOD);
}

/**
 * Original name: StretchAlphaTexTile
 */
void StretchAlphaTexTile(Gfx **gfxP, s32 arg1, s32 arg2, void *arg3, s32 arg4, void *arg5, s32 arg6, s32 arg7, s32 arg8,
                         s32 arg9, s32 argA, f32 argB, f32 argC, f32 argD, f32 argE) {
    StretchTexTile_arg0 sp18;

    sp18.gfxP = gfxP;
    sp18.vtxP = NULL;
    sp18.unk_08 = arg1;
    sp18.unk_0C = arg2;
    sp18.texture = arg3;
    sp18.unk_14 = arg4;
    sp18.unk_18 = arg5;
    sp18.unk_1C = arg6;
    sp18.unk_20 = arg7;
    sp18.unk_24 = arg8;
    sp18.unk_28 = arg9;
    sp18.unk_2C = argA;
    sp18.unk_40 = StretchAlphaTexTile_LoadColorTex;
    sp18.unk_44 = StretchAlphaTexTile_LoadAlphaTex;
    sp18.unk_30 = argB * 4.0;
    sp18.unk_34 = argC * 4.0;
    sp18.unk_38 = argD * 4.0;
    sp18.unk_3C = argE * 4.0;

    sp18.unk_48 = 0x660 / MAX(ALIGN4(arg4), ALIGN16(arg6));
    sp18.unk_4C = StretchTexTile_ScisRect;

    StretchTexTile(&sp18);
}

/**
 * Original name: RectAlphaTexTile
 */
void RectAlphaTexTile(Gfx **gfxP, Vtx **vtxP, s32 arg2, s32 arg3, void *arg4, s32 arg5, void *arg6, s32 arg7, s32 arg8,
                      s32 arg9, s32 argA, s32 argB, f32 argC, f32 argD, f32 argE, f32 argF) {
    StretchTexTile_arg0 sp18;

    sp18.gfxP = gfxP;
    sp18.vtxP = vtxP;
    sp18.unk_08 = arg2;
    sp18.unk_0C = arg3;

    sp18.texture = arg4;
    sp18.unk_14 = arg5;
    sp18.unk_18 = arg6;
    sp18.unk_1C = arg7;
    sp18.unk_20 = arg8;
    sp18.unk_24 = arg9;
    sp18.unk_28 = argA;
    sp18.unk_2C = argB;
    sp18.unk_30 = argC * 4.0;
    sp18.unk_34 = argD * 4.0;
    sp18.unk_38 = argE * 4.0;
    sp18.unk_3C = argF * 4.0;

    sp18.unk_40 = StretchAlphaTexTile_LoadColorTex;
    sp18.unk_44 = StretchAlphaTexTile_LoadAlphaTex;

    sp18.unk_48 = 0x660 / MAX(ALIGN4(arg5), ALIGN16(arg7));
    sp18.unk_4C = RectTexTile_ScisRect;

    StretchTexTile(&sp18);
}

/**
 * Original name: StretchTexTile4_LoadTex
 */
void StretchTexTile4_LoadTex(StretchTexTile_arg0 *arg0) {
    gDPLoadTextureTile_4b((*arg0->gfxP)++, arg0->texture, G_IM_FMT_CI, arg0->unk_14, 1, arg0->unk_20, arg0->unk_50,
                          arg0->unk_20 + arg0->unk_28 - 1, arg0->unk_54 - 1, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK,
                          G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
}

/**
 * Original name: StretchTexTile4
 */
void StretchTexTile4(Gfx **gfxP, s32 width, s32 height, u16 *tlut, u8 *tex, s32 arg5, s32 arg6, s32 arg7, s32 arg8,
                     f32 arg9, f32 argA, f32 argB, f32 argC) {
    StretchTexTile_arg0 sp18;

    sp18.gfxP = gfxP;
    sp18.vtxP = NULL;

    sp18.unk_08 = width;
    sp18.unk_0C = height;
    sp18.texture = tex;
    sp18.unk_14 = width;

    sp18.unk_18 = NULL;
    sp18.unk_1C = 0;
    sp18.unk_20 = arg5;
    sp18.unk_24 = arg6;
    sp18.unk_28 = arg7;
    sp18.unk_2C = arg8;

    sp18.unk_30 = arg9 * 4.0;
    sp18.unk_34 = argA * 4.0;
    sp18.unk_38 = argB * 4.0;
    sp18.unk_3C = argC * 4.0;

    sp18.unk_40 = StretchTexTile4_LoadTex;
    sp18.unk_44 = NULL;
    sp18.unk_48 = 0x1000 / ALIGN16(arg7);
    sp18.unk_4C = StretchTexTile_ScisRect;

    if (tlut != NULL) {
        gDPLoadTLUT_pal16((*gfxP)++, 0, tlut);
    }

    StretchTexTile(&sp18);
}

/**
 * Original name: StretchTexTile8_LoadTex
 */
void StretchTexTile8_LoadTex(StretchTexTile_arg0 *arg0) {
    gDPLoadTextureTile((*arg0->gfxP)++, arg0->texture, G_IM_FMT_CI, G_IM_SIZ_8b, arg0->unk_14, 0, arg0->unk_20,
                       arg0->unk_50, arg0->unk_20 + arg0->unk_28 - 1, arg0->unk_54 - 1, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                       G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
}

/**
 * Original name: StretchTexTile8
 */
void StretchTexTile8(Gfx **gfxP, s32 width, s32 height, u16 *tlut, u8 *tex, s32 arg5, s32 arg6, s32 arg7, s32 arg8,
                     f32 arg9, f32 argA, f32 argB, f32 argC) {
    StretchTexTile_arg0 sp18;

    sp18.gfxP = gfxP;
    sp18.vtxP = NULL;
    sp18.unk_08 = width;
    sp18.unk_0C = height;
    sp18.texture = tex;
    sp18.unk_14 = width;
    sp18.unk_18 = NULL;
    sp18.unk_1C = 0;
    sp18.unk_20 = arg5;
    sp18.unk_24 = arg6;
    sp18.unk_28 = arg7;
    sp18.unk_30 = arg9 * 4.0;
    sp18.unk_34 = argA * 4.0;
    sp18.unk_38 = argB * 4.0;
    sp18.unk_3C = argC * 4.0;
    sp18.unk_48 = 0x800 / ALIGN8(arg7);
    sp18.unk_40 = StretchTexTile8_LoadTex;
    sp18.unk_2C = arg8;
    sp18.unk_44 = NULL;
    sp18.unk_4C = StretchTexTile_ScisRect;

    if (tlut != NULL) {
        gDPLoadTLUT_pal256((*gfxP)++, tlut);
    }

    StretchTexTile(&sp18);
}

/**
 * Original name: RectTexTile8
 */
void RectTexTile8(Gfx **gfxP, Vtx **vtxP, s32 arg2, s32 arg3, u16 *tlut, u8 *texture, s32 arg6, s32 arg7, s32 arg8,
                  s32 arg9, f32 argA, f32 argB, f32 argC, f32 argD) {
    StretchTexTile_arg0 sp18;

    sp18.gfxP = gfxP;
    sp18.vtxP = vtxP;
    sp18.unk_08 = arg2;
    sp18.unk_0C = arg3;
    sp18.unk_14 = arg2;
    sp18.unk_18 = NULL;
    sp18.unk_1C = 0;
    sp18.unk_44 = NULL;
    sp18.texture = texture;
    sp18.unk_20 = arg6;
    sp18.unk_24 = arg7;
    sp18.unk_28 = arg8;
    sp18.unk_2C = arg9;
    sp18.unk_30 = argA * 4.0;
    sp18.unk_34 = argB * 4.0;
    sp18.unk_38 = argC * 4.0;
    sp18.unk_3C = argD * 4.0;
    sp18.unk_40 = StretchTexTile8_LoadTex;
    sp18.unk_48 = 0x800 / ALIGN8(arg8);
    sp18.unk_4C = RectTexTile_ScisRect;

    if (tlut != NULL) {
        gDPLoadTLUT_pal256((*gfxP)++, tlut);
    }

    StretchTexTile(&sp18);
}

/**
 * Original name: StretchTexTile16_LoadTex
 */
void StretchTexTile16_LoadTex(StretchTexTile_arg0 *arg0) {
    gDPLoadTextureTile((*arg0->gfxP)++, arg0->texture, G_IM_FMT_RGBA, G_IM_SIZ_16b, arg0->unk_14, 0, arg0->unk_20,
                       arg0->unk_50, arg0->unk_20 + arg0->unk_28 - 1, arg0->unk_54 - 1, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                       G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
}

/**
 * Original name: StretchTexTile16
 */
void StretchTexTile16(Gfx **gfxP, s32 arg1, s32 arg2, u16 *arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, f32 arg8,
                      f32 arg9, f32 argA, f32 argB) {
    StretchTexTile_arg0 sp18;

    sp18.gfxP = gfxP;
    sp18.vtxP = NULL;
    sp18.unk_08 = arg1;
    sp18.unk_0C = arg2;
    sp18.texture = arg3;
    sp18.unk_14 = arg1;
    sp18.unk_18 = NULL;
    sp18.unk_1C = 0;
    sp18.unk_44 = NULL;
    sp18.unk_40 = StretchTexTile16_LoadTex;
    sp18.unk_4C = StretchTexTile_ScisRect;
    sp18.unk_20 = arg4;
    sp18.unk_24 = arg5;
    sp18.unk_28 = arg6;
    sp18.unk_2C = arg7;
    sp18.unk_30 = arg8 * 4.0;
    sp18.unk_34 = arg9 * 4.0;
    sp18.unk_38 = argA * 4.0;
    sp18.unk_3C = argB * 4.0;
    sp18.unk_48 = 0x800 / ALIGN4(arg6);
    StretchTexTile(&sp18);
}

/**
 * Original name: StretchTexTile4i_LoadTex
 */
void StretchTexTile4i_LoadTex(StretchTexTile_arg0 *arg0) {
    gDPLoadTextureTile_4b((*arg0->gfxP)++, arg0->texture, G_IM_FMT_I, arg0->unk_14, 1, arg0->unk_20, arg0->unk_50,
                          arg0->unk_20 + arg0->unk_28 - 1, arg0->unk_54 - 1, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK,
                          G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
}

/**
 * Original name: StretchTexTile4i
 */
void StretchTexTile4i(Gfx **gfxP, s32 width, s32 height, u8 tex[], s32 arg4, s32 arg5, s32 arg6, s32 arg7, f32 arg8,
                      f32 arg9, f32 argA, f32 argB) {
    StretchTexTile_arg0 sp18;

    sp18.gfxP = gfxP;
    sp18.vtxP = NULL;

    sp18.unk_08 = width;
    sp18.unk_0C = height;
    sp18.texture = tex;
    sp18.unk_14 = width;

    sp18.unk_18 = NULL;
    sp18.unk_1C = 0;
    sp18.unk_20 = arg4;
    sp18.unk_24 = arg5;
    sp18.unk_28 = arg6;
    sp18.unk_2C = arg7;
    sp18.unk_30 = arg8 * 4.0;
    sp18.unk_34 = arg9 * 4.0;
    sp18.unk_38 = argA * 4.0;
    sp18.unk_3C = argB * 4.0;

    sp18.unk_40 = StretchTexTile4i_LoadTex;
    sp18.unk_44 = NULL;
    sp18.unk_48 = 0x2000 / ALIGN16(arg6);
    sp18.unk_4C = StretchTexTile_ScisRect;

    StretchTexTile(&sp18);
}

/**
 * Original name: RectTexTile4i
 */
void RectTexTile4i(Gfx **gfxP, Vtx **vtxP, s32 width, s32 height, u8 *tex, s32 arg5, s32 arg6, s32 arg7, s32 arg8,
                   f32 arg9, f32 argA, f32 argB, f32 argC) {
    StretchTexTile_arg0 sp18;

    sp18.gfxP = gfxP;
    sp18.vtxP = vtxP;

    sp18.unk_08 = width;
    sp18.unk_0C = height;
    sp18.texture = tex;
    sp18.unk_14 = width;

    sp18.unk_18 = NULL;
    sp18.unk_1C = 0;
    sp18.unk_20 = arg5;
    sp18.unk_24 = arg6;
    sp18.unk_28 = arg7;
    sp18.unk_2C = arg8;
    sp18.unk_30 = arg9 * 4.0;
    sp18.unk_34 = argA * 4.0;
    sp18.unk_38 = argB * 4.0;
    sp18.unk_3C = argC * 4.0;

    sp18.unk_40 = StretchTexTile4i_LoadTex;
    sp18.unk_44 = NULL;
    sp18.unk_48 = 0x2000 / ALIGN16(arg7);
    sp18.unk_4C = RectTexTile_ScisRect;

    StretchTexTile(&sp18);
}

/**
 * Original name: tiMappingAddr
 */
void tiMappingAddr(TiTexData *tiArr, s32 len, uintptr_t addr) {
    s32 i;

    for (i = 0; i < len; i++) {
        TiTexData *tiTex = &tiArr[i];

        if (tiTex->texs != NULL) {
            tiTex->texs = (void *)((u8 *)tiTex->texs + addr);

            if (tiTex->texs->tlut != NULL) {
                tiTex->texs->tlut = (void *)((uintptr_t)tiTex->texs->tlut + addr);
            }

            if (tiTex->texs->tex != NULL) {
                tiTex->texs->tex = (void *)((uintptr_t)tiTex->texs->tex + addr);
            }
        }

        if (tiTex->info != NULL) {
            tiTex->info = (void *)((uintptr_t)tiTex->info + addr);
        }
    }
}

/**
 * Original name: tiLoadTexData
 */
TiTexData *tiLoadTexData(void **heap, RomOffset segmentRom, RomOffset segmentRomEnd) {
    TiTexDataHeader *header = ALIGN_PTR(*heap);
    TiTexData *texData;
    s32 *texDataLen;

    *heap = DecompressRomToRam(segmentRom, header, segmentRomEnd - segmentRom);

    texData = (void *)((uintptr_t)header->texData + (uintptr_t)header);
    texDataLen = (void *)((uintptr_t)header->texDataLen + (uintptr_t)header);
    header->texData = texData;
    header->texDataLen = texDataLen;

    tiMappingAddr(texData, *texDataLen, (uintptr_t)header);

    return texData;
}

void *func_80045110(void **arg0, void **arg1, s32 arg2, RomOffset segmentRom, RomOffset segmentRomEnd) {
    size_t temp_a3;
    u32 *temp_v1;
    u32 temp_a2;
    s32 i;

    *arg1 = ALIGN_PTR(*arg0);
    *arg0 = DecompressRomToRam(segmentRom, *arg1, segmentRomEnd - segmentRom);

    temp_a3 = (uintptr_t)*arg1 - (uintptr_t)arg2;

    temp_v1 = (u32 *)(*((void **)*arg1 + 0) += temp_a3);
    temp_a2 = *(u32 *)(*((void **)*arg1 + 1) += temp_a3);

    for (i = 0; i < temp_a2; i++) {
        temp_v1[i] += temp_a3;
    }

    return temp_v1;
}

/**
 * Original name: tiCopyTexBlock
 */
void tiCopyTexBlock(Gfx **gfxP, TiTexData *arg1, s32 arg2, s32 arg3, s32 arg4) {
    u16 *tlut;
    TexturePtr texture;

    if (arg2 != 0) {
        tlut = NULL;
        texture = NULL;
    } else {
        tlut = arg1->texs->tlut;
        texture = arg1->texs->tex;
    }

    switch (arg1->info[2]) {
        case TITEX_FORMAT_4:
            CopyTexBlock4(gfxP, tlut, texture, arg3, arg4, arg1->info[0], arg1->info[1]);
            break;

        case TITEX_FORMAT_8:
            CopyTexBlock8(gfxP, tlut, texture, arg3, arg4, arg1->info[0], arg1->info[1]);
            break;

        case TITEX_FORMAT_16:
            CopyTexBlock16(gfxP, texture, arg3, arg4, arg1->info[0], arg1->info[1]);
            break;
    }
}

/**
 * Original name: tiStretchTexBlock
 */
void tiStretchTexBlock(Gfx **gfxP, TiTexData *arg1, s32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6) {
    TexturePtr var_a3;
    TexturePtr var_t0;

    if (arg2 != 0) {
        var_a3 = NULL;
        var_t0 = NULL;
    } else {
        var_a3 = arg1->texs->tlut;
        var_t0 = arg1->texs->tex;
    }

    if (arg1->texs->tlut != NULL) {
        switch (arg1->info[2]) {
            case TITEX_FORMAT_4:
                StretchTexBlock4(gfxP, arg1->info[0], arg1->info[1], var_a3, var_t0, arg3, arg4, arg5, arg6);
                break;

            case TITEX_FORMAT_8:
                StretchTexBlock8(gfxP, arg1->info[0], arg1->info[1], var_a3, var_t0, arg3, arg4, arg5, arg6);
                break;
        }
    } else {
        switch (arg1->info[2]) {
            case TITEX_FORMAT_4:
                StretchTexBlock4i(gfxP, arg1->info[0], arg1->info[1], var_t0, arg3, arg4, arg5, arg6);
                break;

            case TITEX_FORMAT_16:
                StretchTexBlock16(gfxP, arg1->info[0], arg1->info[1], var_t0, arg3, arg4, arg5, arg6);
                break;
        }
    }
}

/**
 * Original name: tiStretchTexTile
 */
void tiStretchTexTile(Gfx **gfxP, TiTexData *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, f32 arg7, f32 arg8,
                      f32 arg9, f32 argA) {
    u16 *tlut;
    TexturePtr texture;

    if (arg2 != 0) {
        tlut = NULL;
        texture = NULL;
    } else {
        tlut = arg1->texs->tlut;
        texture = arg1->texs->tex;
    }

    if (arg1->texs->tlut != NULL) {
        switch (arg1->info[2]) {
            case TITEX_FORMAT_4:
                StretchTexTile4(gfxP, arg1->info[0], arg1->info[1], tlut, texture, arg3, arg4, arg5, arg6, arg7, arg8,
                                arg9, argA);
                break;

            case TITEX_FORMAT_8:
                StretchTexTile8(gfxP, arg1->info[0], arg1->info[1], tlut, texture, arg3, arg4, arg5, arg6, arg7, arg8,
                                arg9, argA);
                break;
        }
    } else {
        switch (arg1->info[2]) {
            case TITEX_FORMAT_4:
                StretchTexTile4i(gfxP, arg1->info[0], arg1->info[1], texture, arg3, arg4, arg5, arg6, arg7, arg8, arg9,
                                 argA);
                break;

            case TITEX_FORMAT_16:
                StretchTexTile16(gfxP, arg1->info[0], arg1->info[1], texture, arg3, arg4, arg5, arg6, arg7, arg8, arg9,
                                 argA);
                break;
        }
    }
}

/**
 * Original name: tiStretchTexItem
 */
void tiStretchTexItem(Gfx **gfxP, TiTexData *arg1, s32 arg2, s32 arg3, s32 arg4, f32 arg5, f32 arg6, f32 arg7,
                      f32 arg8) {
    s32 temp_lo = arg1->info[1] / arg3;
    s32 temp_lo_2 = arg1->info[0] * temp_lo * arg4;
    u16 *tlut;
    TexturePtr texture;

    if (arg2 != 0) {
        tlut = NULL;
        texture = NULL;
    } else {
        tlut = arg1->texs->tlut;
        texture = arg1->texs->tex;

        switch (arg1->info[2]) {
            case TITEX_FORMAT_4:
                texture = (u8 *)texture + temp_lo_2 / 2;
                break;

            case TITEX_FORMAT_8:
                texture = (u8 *)texture + temp_lo_2;
                break;

            case TITEX_FORMAT_16:
                texture = (u8 *)texture + temp_lo_2 * 2;
                break;
        }
    }

    if (arg1->info[3] & TITEX_FLAGS_BLOCK) {
        switch (arg1->info[2]) {
            case TITEX_FORMAT_4:
                StretchTexBlock4(gfxP, arg1->info[0], temp_lo, tlut, texture, arg5, arg6, arg7, arg8);
                break;

            case TITEX_FORMAT_8:
                StretchTexBlock8(gfxP, arg1->info[0], temp_lo, tlut, texture, arg5, arg6, arg7, arg8);
                break;
        }
    } else {
        switch (arg1->info[2]) {
            case TITEX_FORMAT_4:
                StretchTexTile4(gfxP, arg1->info[0], temp_lo, tlut, texture, 0, 0, arg1->info[0], temp_lo, arg5, arg6,
                                arg7, arg8);
                break;

            case TITEX_FORMAT_8:
                StretchTexTile8(gfxP, arg1->info[0], temp_lo, tlut, texture, 0, 0, arg1->info[0], temp_lo, arg5, arg6,
                                arg7, arg8);
                break;
        }
    }
}

/**
 * Original name: tiStretchAlphaTexItem
 */
void tiStretchAlphaTexItem(Gfx **gfxP, TiTexData *arg1, TiTexData *arg2, s32 arg3, s32 arg4, s32 arg5, f32 arg6,
                           f32 arg7, f32 arg8, f32 arg9) {
    s32 var_t3 = MIN(arg1->info[0], arg2->info[0]);
    s32 var_t2 = MIN(arg1->info[1] / arg4, arg2->info[1]);
    TexturePtr sp48[2];

    if (arg3 != 0) {
        sp48[0] = NULL;
        sp48[1] = NULL;
    } else {
        sp48[0] = (u8 *)arg1->texs->tex + (arg1->info[0] * var_t2 * arg5 * 2);
        sp48[1] = (u8 *)arg2->texs->tex + (arg2->info[0] * var_t2 * arg5 / 2);
    }

    if ((arg1->info[3] & TITEX_FLAGS_BLOCK) && (arg2->info[3] & TITEX_FLAGS_BLOCK)) {
        StretchAlphaTexBlock(gfxP, var_t3, var_t2, sp48[0], arg1->info[0], sp48[1], arg2->info[0], arg6, arg7, arg8,
                             arg9);
    } else {
        StretchAlphaTexTile(gfxP, var_t3, var_t2, sp48[0], arg1->info[0], sp48[1], arg2->info[0], 0, 0, var_t3, var_t2,
                            arg6, arg7, arg8, arg9);
    }
}

void func_80045914(Gfx **gfxP, TiTexData *arg1, TiTexData *arg2, s32 arg3, s32 arg4, s32 arg5, f32 arg6, f32 arg7,
                   f32 arg8, f32 arg9) {
    s32 var_t3 = MIN(arg1->info[0], arg2->info[0]);
    s32 var_t1 = MIN(arg1->info[1] / arg4, arg2->info[1]);
    TexturePtr sp40[2];

    if (arg3 != 0) {
        sp40[0] = NULL;
        sp40[1] = NULL;
    } else {
        sp40[0] = (u8 *)arg1->texs->tex + arg1->info[0] * var_t1 * arg5 * 2;
        sp40[1] = (u8 *)arg2->texs->tex;
    }

    if ((arg1->info[3] & TITEX_FLAGS_BLOCK) && (arg2->info[3] & TITEX_FLAGS_BLOCK)) {
        StretchAlphaTexBlock(gfxP, var_t3, var_t1, sp40[0], arg1->info[0], sp40[1], arg2->info[0], arg6, arg7, arg8,
                             arg9);
    } else {
        StretchAlphaTexTile(gfxP, var_t3, var_t1, sp40[0], arg1->info[0], sp40[1], arg2->info[0], 0, 0, var_t3, var_t1,
                            arg6, arg7, arg8, arg9);
    }
}

/**
 * Original name: _pnts_871
 */
const u8 _pnts_871[][8] = {
    { 0, 0, 1, 1, 0, 0, 2, 2 }, { 1, 0, 2, 1, 2, 0, 1, 2 }, { 2, 0, 3, 1, 1, 0, 0, 2 },
    { 0, 1, 1, 2, 0, 2, 2, 1 }, { 1, 1, 2, 2, 2, 2, 1, 1 }, { 2, 1, 3, 2, 1, 2, 0, 1 },
    { 0, 2, 1, 3, 0, 1, 2, 0 }, { 1, 2, 2, 3, 2, 1, 1, 0 }, { 2, 2, 3, 3, 1, 1, 0, 0 },
};

/**
 * Original name: tiStretchAlphaTexItem
 */
void drawCursorPattern(Gfx **gfxP, s32 arg1 UNUSED, s32 arg2 UNUSED, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7,
                       s32 arg8) {
    Gfx *gfx = *gfxP;
    s32 sp8[4];
    s32 sp18[4];
    s32 sp28[4];
    s32 sp38[4];
    s32 sp48[4];
    s32 i;
    s32 temp;

    temp = arg7 + arg3;

    sp8[0] = (arg5 * 4) - (arg3 * 2);
    sp8[3] = sp8[0] + temp * 4;
    sp8[1] = sp8[0] + arg3 * 4;
    sp8[2] = sp8[3] - arg3 * 4;

    sp28[0] = 0;
    sp28[1] = (arg3 - 1) << 5;
    sp28[2] = arg3 << 5;

    temp = arg8 + arg4;

    sp18[0] = (arg6 * 4) - (arg4 * 2);
    sp18[3] = sp18[0] + temp * 4;
    sp18[1] = sp18[0] + arg4 * 4;
    sp18[2] = sp18[3] - arg4 * 4;

    sp38[0] = 0;
    sp38[1] = (arg4 - 1) << 5;
    sp38[2] = arg4 << 5;

    sp48[0] = -0x400;
    sp48[1] = 0;
    sp48[2] = 0x400;

    for (i = 0; i < ARRAY_COUNTU(_pnts_871); i++) {
        // Cast away the const
        u8 *temp_a3_2 = (u8 *)_pnts_871[i];

        gSPScisTextureRectangle(gfx++, sp8[temp_a3_2[0]], sp18[temp_a3_2[1]], sp8[temp_a3_2[2]], sp18[temp_a3_2[3]],
                                G_TX_RENDERTILE, sp28[temp_a3_2[4]], sp38[temp_a3_2[5]], sp48[temp_a3_2[6]],
                                sp48[temp_a3_2[7]]);
    }
    *gfxP = gfx;
}

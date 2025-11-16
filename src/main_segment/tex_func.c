/**
 * Original filename: tex_func.c
 */

#include "tex_func.h"

#include "alignment.h"
#include "macros_defines.h"
#include "libc/stdint.h"

#include "util.h"

/**
 * Original name: copy_texture_init_dl
 */
Gfx copy_texture_init_dl[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_COPY),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_NOOP, G_RM_NOOP2),
    gsDPSetCombineLERP(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetAlphaCompare(G_AC_THRESHOLD),
    gsDPSetBlendColor(0x00, 0x00, 0x00, 0x01),
    gsDPSetTextureFilter(G_TF_POINT),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTexturePersp(G_TP_NONE),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsDPSetTextureConvert(G_TC_FILT),
    gsSPEndDisplayList(),
};

/**
 * Original name: alpha_texture_init_dl
 */
Gfx alpha_texture_init_dl[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_PASS, G_RM_XLU_SURF2),
    gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, TEXEL0),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPSetTextureFilter(G_TF_POINT),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetTexturePersp(G_TP_NONE),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsDPSetTextureConvert(G_TC_FILT),
    gsSPEndDisplayList(),
};

/**
 * Original name: normal_texture_init_dl
 */
Gfx normal_texture_init_dl[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetAlphaCompare(G_AC_THRESHOLD),
    gsDPSetBlendColor(0x00, 0x00, 0x00, 0x01),
    gsDPSetTextureFilter(G_TF_POINT),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTexturePersp(G_TP_NONE),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsDPSetTextureConvert(G_TC_FILT),
    gsSPEndDisplayList(),
};

Gfx D_8008E728[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_FILL),
    gsDPSetRenderMode(G_RM_NOOP, G_RM_NOOP2),
    gsSPEndDisplayList(),
};

/**
 * Original name: init_dl_155
 */
Gfx init_dl_155[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetCombineMode(G_CC_PRIMITIVE, G_CC_PRIMITIVE),
    gsSPEndDisplayList(),
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

/**
 * Original name: FillRectRGB
 */
void FillRectRGB(Gfx **gxfP, s32 x, s32 y, s32 width, s32 height, s32 red, s32 green, s32 blue) {
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

/* Copy block */

struct SCopyTexBlock;

typedef void(SCopyTexBlock_callback)(CONST_ARG struct SCopyTexBlock *st);

/**
 * Original name: SCopyTexBlock
 */
typedef struct SCopyTexBlock {
    /* 0x00 */ Gfx **gfxP;                   /* Original name: gpp */
    /* 0x04 */ const Texture *tex;           /* Original name: tex */
    /* 0x08 */ s32 x;                        /* Original name: x */
    /* 0x0C */ s32 y;                        /* Original name: y */
    /* 0x10 */ s32 w;                        /* Original name: w */
    /* 0x14 */ s32 h;                        /* Original name: h */
    /* 0x18 */ SCopyTexBlock_callback *func; /* Original name: func */
    /* 0x1C */ s32 step;                     /* Original name: step */
    /* 0x20 */ s32 top;                      /* Original name: top */
    /* 0x24 */ s32 bottom;                   /* Original name: bottom */
} SCopyTexBlock;                             // size = 0x28

/**
 * Original name: CopyTexBlock
 */
void CopyTexBlock(SCopyTexBlock *st) {
    s32 x;

    x = st->x;
    if (x >= 0) {
        x <<= 2;
    }

    for (st->top = 0; st->top < st->h; st->top += st->step) {
        st->bottom = MIN(st->top + st->step, st->h);

        if (st->tex != NULL) {
            st->func(st);
        }

        gSPScisTextureRectangle((*st->gfxP)++, x, (st->y + st->top) << 2, ((st->x + st->w) - 1) << 2,
                                ((st->y + st->bottom) - 1) << 2, G_TX_RENDERTILE, 0, 0, 4 << 10, 1 << 10);
    }
}

/**
 * Original name: CopyTexBlock4_LoadTex
 */
void CopyTexBlock4_LoadTex(CONST_ARG SCopyTexBlock *st) {
    gDPLoadTextureBlock_4b((*st->gfxP)++, (u8 *)st->tex + ((st->w * st->top) / 2), G_IM_FMT_CI, st->w,
                           st->bottom - st->top, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK,
                           G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
}

/**
 * Original name: CopyTexBlock4
 */
void CopyTexBlock4(Gfx **gfxP, const u16 tlut[], const u8 tex[], s32 x, s32 y, s32 w, s32 h) {
    SCopyTexBlock st;

    st.gfxP = gfxP;

    st.tex = tex;
    st.x = x;
    st.y = y;
    st.w = w;
    st.h = h;
    st.func = CopyTexBlock4_LoadTex;
    st.step = 0x1000 / w;

    gSPDisplayList((*gfxP)++, copy_texture_init_dl);

    if (tlut != NULL) {
        gDPLoadTLUT_pal16((*gfxP)++, 0, tlut);
    }

    CopyTexBlock(&st);
}

/**
 * Original name: CopyTexBlock8_LoadTex
 */
void CopyTexBlock8_LoadTex(CONST_ARG SCopyTexBlock *st) {
    gDPLoadTextureBlock((*st->gfxP)++, (u8 *)st->tex + st->w * st->top, G_IM_FMT_CI, G_IM_SIZ_8b, st->w,
                        st->bottom - st->top, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                        G_TX_NOLOD);
}

/**
 * Original name: CopyTexBlock8
 */
void CopyTexBlock8(Gfx **gfxP, const u16 tlut[], const u8 tex[], s32 x, s32 y, s32 w, s32 h) {
    SCopyTexBlock st;

    st.gfxP = gfxP;
    st.tex = tex;
    st.x = x;
    st.y = y;
    st.w = w;
    st.h = h;
    st.func = CopyTexBlock8_LoadTex;
    st.step = 0x800 / w;

    gSPDisplayList((*gfxP)++, copy_texture_init_dl);

    if (tlut != NULL) {
        gDPLoadTLUT_pal256((*gfxP)++, tlut);
    }

    CopyTexBlock(&st);
}

/**
 * Original name: CopyTexBlock16_LoadTex
 */
void CopyTexBlock16_LoadTex(CONST_ARG SCopyTexBlock *st) {
    gDPLoadTextureBlock((*st->gfxP)++, (u16 *)st->tex + st->w * st->top, G_IM_FMT_RGBA, G_IM_SIZ_16b, st->w,
                        st->bottom - st->top, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                        G_TX_NOLOD);
}

/**
 * Original name: CopyTexBlock16
 */
void CopyTexBlock16(Gfx **gfxP, const u16 tex[], s32 x, s32 y, s32 w, s32 h) {
    SCopyTexBlock st;

    st.gfxP = gfxP;
    st.tex = tex;

    st.x = x;
    st.y = y;
    st.w = w;
    st.h = h;

    st.func = CopyTexBlock16_LoadTex;
    st.step = 0x800 / w;

    gSPDisplayList((*gfxP)++, copy_texture_init_dl);
    gDPSetTextureLUT((*gfxP)++, G_TT_NONE);

    CopyTexBlock(&st);
}

/* Stretch block */

struct SStretchTexBlock;

typedef void(SStretchTexBlock_callback)(CONST_ARG struct SStretchTexBlock *st);

typedef struct SStretchTex_Rect {
    /* 0x00 */ s32 xl;
    /* 0x04 */ s32 yl;
    /* 0x08 */ s32 xh;
    /* 0x0C */ s32 yh;
    /* 0x10 */ s32 s;
    /* 0x14 */ s32 t;
    /* 0x18 */ s32 dsdx;
    /* 0x1C */ s32 dtdy;
} SStretchTex_Rect; // size = 0x20

/**
 * Original name: SStretchTexBlock
 */
typedef struct SStretchTexBlock {
    /* 0x00 */ Gfx **gfxP;                                      /* Original name: gpp */
    /* 0x04 */ Vtx **vpp; /* Original name: vpp */              // unused
    /* 0x08 */ s32 texW;                                        /* Original name: texW */
    /* 0x0C */ s32 texH;                                        /* Original name: texH */
    /* 0x10 */ const Texture *colorTex;                         /* Original name: colorTex */
    /* 0x14 */ s32 colorTexW;                                   /* Original name: colorTexW */
    /* 0x18 */ const Texture *alphaTex;                         /* Original name: alphaTex */
    /* 0x1C */ s32 alphaTexW;                                   /* Original name: alphaTexW */
    /* 0x20 */ s32 x;                                           /* Original name: x */
    /* 0x24 */ s32 y;                                           /* Original name: y */
    /* 0x28 */ s32 w;                                           /* Original name: w */
    /* 0x2C */ s32 h;                                           /* Original name: h */
    /* 0x30 */ SStretchTexBlock_callback *colorFunc;            /* Original name: colorFunc */
    /* 0x34 */ SStretchTexBlock_callback *alphaFunc;            /* Original name: alphaFunc */
    /* 0x38 */ s32 step;                                        /* Original name: step */
    /* 0x3C */ SStretchTexBlock_callback *rectFunc;             /* Original name: rectFunc */
    /* 0x40 */ s32 top;                                         /* Original name: top */
    /* 0x44 */ s32 bottom;                                      /* Original name: bottom */
    /* 0x48 */ s32 loadH;                                       /* Original name: loadH */
    /* 0x4C */ SStretchTex_Rect rect; /* Original name: rect */ // Originally int rect[8]
} SStretchTexBlock;                                             // size = 0x6C

/**
 * Original name: StretchTexBlock
 */
void StretchTexBlock(SStretchTexBlock *st) {
    s32 sp18[2];
    SStretchTex_Rect *t;
    s32 w;
    s32 h;
    s32 biStep;
    u32 var_s4;

    if (st->w < 0) {
        w = -st->w;
        sp18[0] = -1;
    } else if (st->w > 0) {
        w = st->w;
        sp18[0] = 1;
    } else {
        return;
    }

    if (st->h < 0) {
        h = -st->h;
        sp18[1] = -1;
    } else if (st->h > 0) {
        h = st->h;
        sp18[1] = 1;
    } else {
        return;
    }

    if ((st->vpp == NULL) && (w == (st->texW << 2)) && (h == (st->texH << 2))) {
        gDPSetTextureFilter((*st->gfxP)++, G_TF_POINT);
        var_s4 = 0;
        biStep = st->step;
    } else {
        gDPSetTextureFilter((*st->gfxP)++, G_TF_BILERP);
        var_s4 = ~0;
        biStep = MAX(st->step - 1, 1);
    }

    t = &st->rect;

    t->xl = st->x;
    t->xh = st->x + w;
    t->s = ((sp18[0] < 0) ? (st->texW - 1) : 0) << 5;
    t->dsdx = ((sp18[0] << 0xC) * st->texW) / w;

    for (st->top = 0; st->top < st->texH; st->top += biStep) {
        st->bottom = MIN(st->top + st->step, st->texH);
        st->loadH = st->bottom - st->top;
        if (st->colorTex != NULL) {
            st->colorFunc(st);
        }
        if (st->alphaTex != NULL) {
            st->alphaFunc(st);
        }

        if (sp18[1] < 0) {
            t->yl = st->texH - st->bottom;
            t->yh = st->texH - st->top;
            t->t = st->loadH - 1;
        } else {
            t->yl = st->top;
            t->yh = st->bottom;
            t->t = 0;
        }

        t->yl = st->y + (((t->yl << 2) * h) / (st->texH << 2));
        t->yh = st->y + (((t->yh << 2) * h) / (st->texH << 2));
        t->t = t->t << 5;
        t->dtdy = (sp18[1] << 0xC) * st->texH / h;
        t->t -= (t->dtdy / (1 << 6)) & var_s4;

        st->rectFunc(st);
    }
}

/**
 * Original name: StretchTexBlock_ScisRect
 */
void StretchTexBlock_ScisRect(CONST_ARG SStretchTexBlock *st) {
    CONST_ARG SStretchTex_Rect *t = &st->rect;

    gSPScisTextureRectangle((*st->gfxP)++, t->xl, t->yl, t->xh, t->yh, G_TX_RENDERTILE, t->s, t->t, t->dsdx, t->dtdy);
}

/**
 * Original name: StretchAlphaTexBlock_LoadColorTex
 */
void StretchAlphaTexBlock_LoadColorTex(CONST_ARG SStretchTexBlock *st) {
    gDPLoadTextureBlock((*st->gfxP)++, (u16 *)st->colorTex + (st->colorTexW * st->top), G_IM_FMT_RGBA, G_IM_SIZ_16b,
                        st->colorTexW, st->loadH, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
}

/**
 * Original name: StretchAlphaTexBlock_LoadAlphaTex
 */
void StretchAlphaTexBlock_LoadAlphaTex(CONST_ARG SStretchTexBlock *st) {
    // TODO: what is 0x19A?
    gDPLoadMultiBlock_4b((*st->gfxP)++, (u8 *)st->alphaTex + (st->alphaTexW * st->top) / 2, 0x19A, 1, G_IM_FMT_I,
                         st->alphaTexW, st->loadH, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                         G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
}

/**
 * Original name: StretchAlphaTexBlock
 */
void StretchAlphaTexBlock(Gfx **gfxP, s32 texW, s32 texH, const u16 colorTex[], s32 colorTexW, const u8 alphaTex[],
                          s32 alphaTexW, f32 x, f32 y, f32 w, f32 h) {
    SStretchTexBlock st;

    st.gfxP = gfxP;
    st.vpp = NULL;
    st.texW = texW;
    st.texH = texH;
    st.colorTex = colorTex;
    st.colorTexW = colorTexW;
    st.alphaTex = alphaTex;
    st.alphaTexW = alphaTexW;

    st.x = x * DOUBLE_LITERAL(4);
    st.y = y * DOUBLE_LITERAL(4);
    st.w = w * DOUBLE_LITERAL(4);
    st.h = h * DOUBLE_LITERAL(4);

    st.colorFunc = StretchAlphaTexBlock_LoadColorTex;
    st.alphaFunc = StretchAlphaTexBlock_LoadAlphaTex;

    st.step = 0x660 / MAX(colorTexW, alphaTexW);
    st.rectFunc = StretchTexBlock_ScisRect;

    StretchTexBlock(&st);
}

/**
 * Original name: StretchTexBlock4_LoadTex
 */
void StretchTexBlock4_LoadTex(CONST_ARG SStretchTexBlock *st) {
    gDPLoadTextureBlock_4b((*st->gfxP)++, (u8 *)st->colorTex + ((st->colorTexW * st->top) / 2), G_IM_FMT_CI,
                           st->colorTexW, st->loadH, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                           G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
}

/**
 * Original name: StretchTexBlock4
 */
void StretchTexBlock4(Gfx **gfxP, s32 texW, s32 texH, const u16 tlut[], const u8 tex[], f32 x, f32 y, f32 w, f32 h) {
    SStretchTexBlock st;

    st.gfxP = gfxP;
    st.vpp = NULL;
    st.texW = texW;
    st.texH = texH;

    st.colorTexW = texW;
    st.alphaTex = NULL;

    st.alphaTexW = 0;
    st.alphaFunc = NULL;

    st.colorFunc = StretchTexBlock4_LoadTex;
    st.rectFunc = StretchTexBlock_ScisRect;
    st.colorTex = tex;

    st.x = x * DOUBLE_LITERAL(4);
    st.y = y * DOUBLE_LITERAL(4);
    st.w = w * DOUBLE_LITERAL(4);
    st.h = h * DOUBLE_LITERAL(4);

    st.step = 0x1000 / texW;

    if (tlut != NULL) {
        gDPLoadTLUT_pal16((*gfxP)++, 0, tlut);
    }

    StretchTexBlock(&st);
}

/**
 * Original name: StretchTexBlock8_LoadTex
 */
void StretchTexBlock8_LoadTex(CONST_ARG SStretchTexBlock *st) {
    gDPLoadTextureBlock((*st->gfxP)++, (u8 *)st->colorTex + (st->colorTexW * st->top), G_IM_FMT_CI, G_IM_SIZ_8b,
                        st->colorTexW, st->loadH, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
}

/**
 * Original name: StretchTexBlock8
 */
void StretchTexBlock8(Gfx **gfxP, s32 texW, s32 texH, const u16 tlut[], const u8 tex[], f32 x, f32 y, f32 w, f32 h) {
    SStretchTexBlock st;

    st.gfxP = gfxP;
    st.vpp = NULL;
    st.texW = texW;
    st.texH = texH;

    st.colorTexW = texW;
    st.alphaTex = NULL;

    st.alphaTexW = 0;
    st.alphaFunc = NULL;

    st.colorFunc = StretchTexBlock8_LoadTex;
    st.rectFunc = StretchTexBlock_ScisRect;
    st.colorTex = tex;

    st.x = x * DOUBLE_LITERAL(4);
    st.y = y * DOUBLE_LITERAL(4);
    st.w = w * DOUBLE_LITERAL(4);
    st.h = h * DOUBLE_LITERAL(4);

    st.step = 0x800 / texW;

    if (tlut != NULL) {
        gDPLoadTLUT_pal256((*gfxP)++, tlut);
    }

    StretchTexBlock(&st);
}

/**
 * Original name: StretchTexBlock16_LoadTex
 */
void StretchTexBlock16_LoadTex(CONST_ARG SStretchTexBlock *st) {
    gDPLoadTextureBlock((*st->gfxP)++, (u16 *)st->colorTex + (st->colorTexW * st->top), G_IM_FMT_RGBA, G_IM_SIZ_16b,
                        st->colorTexW, st->loadH, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
}

/**
 * Original name: StretchTexBlock16
 */
void StretchTexBlock16(Gfx **gfxP, s32 texW, s32 texH, const u16 tex[], f32 x, f32 y, f32 w, f32 h) {
    SStretchTexBlock st;

    st.gfxP = gfxP;
    st.vpp = NULL;
    st.texW = texW;
    st.texH = texH;

    st.colorTex = tex;
    st.colorTexW = texW;
    st.alphaTex = NULL;
    st.alphaTexW = 0;

    st.colorFunc = StretchTexBlock16_LoadTex;
    st.alphaFunc = NULL;
    st.rectFunc = StretchTexBlock_ScisRect;

    st.x = x * DOUBLE_LITERAL(4);
    st.y = y * DOUBLE_LITERAL(4);
    st.w = w * DOUBLE_LITERAL(4);
    st.h = h * DOUBLE_LITERAL(4);

    st.step = 0x800 / texW;

    StretchTexBlock(&st);
}

/**
 * Original name: StretchTexBlock4i_LoadTex
 */
void StretchTexBlock4i_LoadTex(CONST_ARG SStretchTexBlock *st) {
    gDPLoadTextureBlock_4b((*st->gfxP)++, st->colorTex + (st->colorTexW * st->top) / 2, G_IM_FMT_I, st->colorTexW,
                           st->loadH, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK,
                           G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
}

/**
 * Original name: StretchTexBlock4i
 */
void StretchTexBlock4i(Gfx **gfxP, s32 texW, s32 texH, const u8 tex[], f32 x, f32 y, f32 w, f32 h) {
    SStretchTexBlock st;

    st.gfxP = gfxP;
    st.vpp = NULL;

    st.texW = texW;
    st.texH = texH;

    st.colorTex = tex;
    st.colorTexW = texW;

    st.alphaTex = NULL;
    st.alphaTexW = 0;

    st.colorFunc = StretchTexBlock4i_LoadTex;
    st.alphaFunc = NULL;
    st.rectFunc = StretchTexBlock_ScisRect;

    st.x = x * DOUBLE_LITERAL(4);
    st.y = y * DOUBLE_LITERAL(4);
    st.w = w * DOUBLE_LITERAL(4);
    st.h = h * DOUBLE_LITERAL(4);

    st.step = 0x2000 / texW;

    StretchTexBlock(&st);
}

void StretchTexBlock8i_LoadTex(CONST_ARG SStretchTexBlock *st) {
    gDPLoadTextureBlock((*st->gfxP)++, st->colorTex + (st->colorTexW * st->top), G_IM_FMT_I, G_IM_SIZ_8b, st->colorTexW,
                        st->loadH, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK,
                        G_TX_NOLOD, G_TX_NOLOD);
}

void StretchTexBlock8i(Gfx **gfxP, s32 texW, s32 texH, const u8 tex[], f32 x, f32 y, f32 w, f32 h) {
    SStretchTexBlock st;

    st.gfxP = gfxP;
    st.vpp = NULL;

    st.texW = texW;
    st.texH = texH;

    st.colorTex = tex;
    st.colorTexW = texW;
    st.alphaTex = NULL;
    st.alphaTexW = 0;

    st.colorFunc = StretchTexBlock8i_LoadTex;
    st.alphaFunc = NULL;
    st.rectFunc = StretchTexBlock_ScisRect;

    st.x = x * DOUBLE_LITERAL(4);
    st.y = y * DOUBLE_LITERAL(4);
    st.w = w * DOUBLE_LITERAL(4);
    st.h = h * DOUBLE_LITERAL(4);

    st.step = 0x1000 / texW;

    StretchTexBlock(&st);
}

/* Stretch tile */

struct SStretchTexTile;

typedef void (*SStretchTexTile_callback)(CONST_ARG struct SStretchTexTile *st);

/**
 * Original name: SStretchTexTile
 */
typedef struct SStretchTexTile {
    /* 0x00 */ Gfx **gfxP;                                      /* Original name: gpp */
    /* 0x04 */ Vtx **vtxP;                                      /* Original name: vpp */
    /* 0x08 */ s32 texW;                                        /* Original name: texW */
    /* 0x0C */ s32 texH;                                        /* Original name: texH */
    /* 0x10 */ const Texture *colorTex;                         /* Original name: colorTex */
    /* 0x14 */ s32 colorTexW;                                   /* Original name: colorTexW */
    /* 0x18 */ const u8 *alphaTex;                              /* Original name: alphaTex */
    /* 0x1C */ s32 alphaTexW;                                   /* Original name: alphaTexW */
    /* 0x20 */ s32 lx;                                          /* Original name: lx */
    /* 0x24 */ s32 ly;                                          /* Original name: ly */
    /* 0x28 */ s32 lw;                                          /* Original name: lw */
    /* 0x2C */ s32 lh;                                          /* Original name: lh */
    /* 0x30 */ s32 x;                                           /* Original name: x */
    /* 0x34 */ s32 y;                                           /* Original name: y */
    /* 0x38 */ s32 w;                                           /* Original name: w */
    /* 0x3C */ s32 h;                                           /* Original name: h */
    /* 0x40 */ SStretchTexTile_callback colorFunc;              /* Original name: colorFunc */
    /* 0x44 */ SStretchTexTile_callback alphaFunc;              /* Original name: alphaFunc */
    /* 0x48 */ s32 step;                                        /* Original name: step */
    /* 0x4C */ SStretchTexTile_callback rectFunc;               /* Original name: rectFunc */
    /* 0x50 */ s32 top;                                         /* Original name: top */
    /* 0x54 */ s32 bottom;                                      /* Original name: bottom */
    /* 0x58 */ SStretchTex_Rect rect; /* Original name: rect */ // Originally int rect[8]
} SStretchTexTile;                                              // size = 0x78

/**
 * Original name: StretchTexTile
 */
void StretchTexTile(SStretchTexTile *st) {
    s32 sp18[2];
    SStretchTex_Rect *t;
    s32 w;
    s32 h;
    s32 biStep;
    u32 var_s5;
    s32 endX;
    s32 endY;

    if (st->w < 0) {
        w = -st->w;
        sp18[0] = -1;
    } else if (st->w > 0) {
        w = st->w;
        sp18[0] = 1;
    } else {
        return;
    }

    if (st->h < 0) {
        h = -st->h;
        sp18[1] = -1;
    } else if (st->h > 0) {
        h = st->h;
        sp18[1] = 1;
    } else {
        return;
    }

    endX = st->lx + st->lw;
    endY = st->ly + st->lh;
    if ((st->vtxP == NULL) && (w == (st->lw << 2)) && (h == (st->lh << 2))) {
        gDPSetTextureFilter((*st->gfxP)++, G_TF_POINT);
        var_s5 = 0;
        biStep = st->step;
    } else {
        gDPSetTextureFilter((*st->gfxP)++, G_TF_BILERP);
        var_s5 = ~0;
        biStep = MAX(st->step - 1, 1);
    }

    t = &st->rect;

    st->rect.xl = st->x;
    t->xh = st->x + w;

    t->s = ((sp18[0] < 0) ? (endX - 1) : st->lx) << 5;

    t->dsdx = ((sp18[0] << 0xC) * st->lw) / w;

    for (st->top = st->ly; st->top < endY; st->top += biStep) {
        st->bottom = MIN(st->top + st->step, endY);

        if (st->colorTex != NULL) {
            st->colorFunc(st);
        }

        if (st->alphaTex != NULL) {
            st->alphaFunc(st);
        }

        if (sp18[1] < 0) {
            t->yl = endY - st->bottom;
            t->yh = endY - st->top;
            t->t = st->bottom - 1;
        } else {
            t->yl = st->top;
            t->yh = st->bottom;
            t->t = st->top;
        }

        t->yl = st->y + ((t->yl - st->ly) << 2) * h / (st->lh << 2);
        t->yh = st->y + ((t->yh - st->ly) << 2) * h / (st->lh << 2);

        t->t <<= 5;

        t->dtdy = ((sp18[1] << 0xC) * st->lh) / h;
        t->t -= (t->dtdy / (1 << 6)) & var_s5;

        st->rectFunc(st);
    }
}

/**
 * Original name: StretchTexTile_ScisRect
 */
void StretchTexTile_ScisRect(CONST_ARG SStretchTexTile *st) {
    CONST_ARG SStretchTex_Rect *t = &st->rect;

    gSPScisTextureRectangle((*st->gfxP)++, t->xl, t->yl, t->xh, t->yh, G_TX_RENDERTILE, t->s, t->t, t->dsdx, t->dtdy);
}

/**
 * Original name: RectTexTile_ScisRect
 */
void RectTexTile_ScisRect(CONST_ARG SStretchTexTile *st) {
    Gfx *gfx = *st->gfxP;
    Vtx *vtx = *st->vtxP;
    CONST_ARG SStretchTex_Rect *t;

    gSPVertex(gfx++, vtx, 4, 0);
    gSP2Triangles(gfx++, 0, 1, 2, 0, 3, 2, 1, 0);

    t = &st->rect;

    vtx[0].v.ob[0] = vtx[1].v.ob[0] = t->xl >> 2;
    vtx[0].v.ob[1] = vtx[2].v.ob[1] = t->yl >> 2;
    vtx[2].v.ob[0] = vtx[3].v.ob[0] = t->xh >> 2;
    vtx[1].v.ob[1] = vtx[3].v.ob[1] = t->yh >> 2;

    vtx[0].v.tc[0] = vtx[1].v.tc[0] = t->s << 2;
    vtx[0].v.tc[1] = vtx[2].v.tc[1] = t->t << 2;

    vtx[2].v.tc[0] = vtx[3].v.tc[0] = (((t->xh - t->xl) * t->dsdx) + (t->s << 7)) >> 5;

    vtx[1].v.tc[1] = vtx[3].v.tc[1] = (((t->yh - t->yl) * t->dtdy) + (t->t << 7)) >> 5;

    // Stinky code
    *(u32 *)&vtx[3].v.ob[2] = 0;
    *(u32 *)&vtx[2].v.ob[2] = 0;
    *(u32 *)&vtx[1].v.ob[2] = 0;
    *(u32 *)&vtx[0].v.ob[2] = 0;
    *(u32 *)vtx[3].v.cn = 0xFFFFFFFF;
    *(u32 *)vtx[2].v.cn = 0xFFFFFFFF;
    *(u32 *)vtx[1].v.cn = 0xFFFFFFFF;
    *(u32 *)vtx[0].v.cn = 0xFFFFFFFF;

    *st->vtxP = &vtx[4];
    *st->gfxP = gfx;
}

/**
 * Original name: StretchAlphaTexTile_LoadColorTex
 */
void StretchAlphaTexTile_LoadColorTex(CONST_ARG SStretchTexTile *st) {
    gDPLoadTextureTile((*st->gfxP)++, st->colorTex, G_IM_FMT_RGBA, G_IM_SIZ_16b, st->colorTexW, 0, st->lx, st->top,
                       ((st->lx + st->lw) - 1), (st->bottom - 1), 0, G_TX_NOMIRROR | G_TX_CLAMP,
                       G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
}

/**
 * Original name: StretchAlphaTexTile_LoadAlphaTex
 */
void StretchAlphaTexTile_LoadAlphaTex(CONST_ARG SStretchTexTile *st) {
    // TODO: what is 0x019A?
    gDPLoadMultiTile_4b((*st->gfxP)++, st->alphaTex, 0x019A, 1, G_IM_FMT_I, st->alphaTexW, 0, st->lx, st->top,
                        (st->lx + st->lw) - 1, st->bottom - 1, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
}

/**
 * Original name: StretchAlphaTexTile
 */
void StretchAlphaTexTile(Gfx **gfxP, s32 texW, s32 texH, const u16 colorTex[], s32 colorTexW, const u8 alphaTex[],
                         s32 alphaTexW, s32 lx, s32 ly, s32 lw, s32 lh, f32 x, f32 y, f32 w, f32 h) {
    SStretchTexTile st;

    st.gfxP = gfxP;
    st.vtxP = NULL;

    st.texW = texW;
    st.texH = texH;

    st.colorTex = colorTex;
    st.colorTexW = colorTexW;
    st.alphaTex = alphaTex;
    st.alphaTexW = alphaTexW;

    st.lx = lx;
    st.ly = ly;
    st.lw = lw;
    st.lh = lh;

    st.x = x * DOUBLE_LITERAL(4);
    st.y = y * DOUBLE_LITERAL(4);
    st.w = w * DOUBLE_LITERAL(4);
    st.h = h * DOUBLE_LITERAL(4);

    st.colorFunc = StretchAlphaTexTile_LoadColorTex;
    st.alphaFunc = StretchAlphaTexTile_LoadAlphaTex;

    st.step = 0x660 / MAX(ALIGN4(colorTexW), ALIGN16(alphaTexW));

    st.rectFunc = StretchTexTile_ScisRect;

    StretchTexTile(&st);
}

/**
 * Original name: RectAlphaTexTile
 */
void RectAlphaTexTile(Gfx **gfxP, Vtx **vtxP, s32 texW, s32 texH, const u16 colorTex[], s32 colorTexW,
                      const u8 alphaTex[], s32 alphaTexW, s32 lx, s32 ly, s32 lw, s32 lh, f32 x, f32 y, f32 w, f32 h) {
    SStretchTexTile st;

    st.gfxP = gfxP;
    st.vtxP = vtxP;

    st.texW = texW;
    st.texH = texH;

    st.colorTex = colorTex;
    st.colorTexW = colorTexW;
    st.alphaTex = alphaTex;
    st.alphaTexW = alphaTexW;

    st.lx = lx;
    st.ly = ly;
    st.lw = lw;
    st.lh = lh;

    st.x = x * DOUBLE_LITERAL(4);
    st.y = y * DOUBLE_LITERAL(4);
    st.w = w * DOUBLE_LITERAL(4);
    st.h = h * DOUBLE_LITERAL(4);

    st.colorFunc = StretchAlphaTexTile_LoadColorTex;
    st.alphaFunc = StretchAlphaTexTile_LoadAlphaTex;

    st.step = 0x660 / MAX(ALIGN4(colorTexW), ALIGN16(alphaTexW));
    st.rectFunc = RectTexTile_ScisRect;

    StretchTexTile(&st);
}

/**
 * Original name: StretchTexTile4_LoadTex
 */
void StretchTexTile4_LoadTex(CONST_ARG SStretchTexTile *st) {
    gDPLoadTextureTile_4b((*st->gfxP)++, st->colorTex, G_IM_FMT_CI, st->colorTexW, 1, st->lx, st->top,
                          st->lx + st->lw - 1, st->bottom - 1, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK,
                          G_TX_NOLOD, G_TX_NOLOD);
}

/**
 * Original name: StretchTexTile4
 */
void StretchTexTile4(Gfx **gfxP, s32 texW, s32 texH, const u16 tlut[], const u8 tex[], s32 lx, s32 ly, s32 lw, s32 lh,
                     f32 x, f32 y, f32 w, f32 h) {
    SStretchTexTile st;

    st.gfxP = gfxP;
    st.vtxP = NULL;

    st.texW = texW;
    st.texH = texH;

    st.colorTex = tex;
    st.colorTexW = texW;
    st.alphaTex = NULL;
    st.alphaTexW = 0;

    st.lx = lx;
    st.ly = ly;
    st.lw = lw;
    st.lh = lh;
    st.x = x * DOUBLE_LITERAL(4);
    st.y = y * DOUBLE_LITERAL(4);
    st.w = w * DOUBLE_LITERAL(4);
    st.h = h * DOUBLE_LITERAL(4);

    st.colorFunc = StretchTexTile4_LoadTex;
    st.alphaFunc = NULL;

    st.step = 0x1000 / ALIGN16(lw);

    st.rectFunc = StretchTexTile_ScisRect;

    if (tlut != NULL) {
        gDPLoadTLUT_pal16((*gfxP)++, 0, tlut);
    }

    StretchTexTile(&st);
}

/**
 * Original name: StretchTexTile8_LoadTex
 */
void StretchTexTile8_LoadTex(CONST_ARG SStretchTexTile *st) {
    gDPLoadTextureTile((*st->gfxP)++, st->colorTex, G_IM_FMT_CI, G_IM_SIZ_8b, st->colorTexW, 0, st->lx, st->top,
                       st->lx + st->lw - 1, st->bottom - 1, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                       G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
}

/**
 * Original name: StretchTexTile8
 */
void StretchTexTile8(Gfx **gfxP, s32 texW, s32 texH, const u16 tlut[], const u8 tex[], s32 lx, s32 ly, s32 lw, s32 lh,
                     f32 x, f32 y, f32 w, f32 h) {
    SStretchTexTile st;

    st.gfxP = gfxP;
    st.vtxP = NULL;

    st.texW = texW;
    st.texH = texH;

    st.colorTex = tex;
    st.colorTexW = texW;
    st.alphaTex = NULL;
    st.alphaTexW = 0;

    st.lx = lx;
    st.ly = ly;
    st.lw = lw;
    st.lh = lh;

    st.x = x * DOUBLE_LITERAL(4);
    st.y = y * DOUBLE_LITERAL(4);
    st.w = w * DOUBLE_LITERAL(4);
    st.h = h * DOUBLE_LITERAL(4);

    st.step = 0x800 / ALIGN8(lw);
    st.colorFunc = StretchTexTile8_LoadTex;
    st.alphaFunc = NULL;
    st.rectFunc = StretchTexTile_ScisRect;

    if (tlut != NULL) {
        gDPLoadTLUT_pal256((*gfxP)++, tlut);
    }

    StretchTexTile(&st);
}

/**
 * Original name: RectTexTile8
 */
void RectTexTile8(Gfx **gfxP, Vtx **vtxP, s32 texW, s32 texH, const u16 tlut[], const u8 tex[], s32 lx, s32 ly, s32 lw,
                  s32 lh, f32 x, f32 y, f32 w, f32 h) {
    SStretchTexTile st;

    st.gfxP = gfxP;
    st.vtxP = vtxP;

    st.texW = texW;
    st.texH = texH;

    st.colorTex = tex;
    st.colorTexW = texW;
    st.alphaTex = NULL;
    st.alphaTexW = 0;

    st.lx = lx;
    st.ly = ly;
    st.lw = lw;
    st.lh = lh;
    st.x = x * DOUBLE_LITERAL(4);
    st.y = y * DOUBLE_LITERAL(4);
    st.w = w * DOUBLE_LITERAL(4);
    st.h = h * DOUBLE_LITERAL(4);

    st.colorFunc = StretchTexTile8_LoadTex;
    st.alphaFunc = NULL;

    st.step = 0x800 / ALIGN8(lw);

    st.rectFunc = RectTexTile_ScisRect;

    if (tlut != NULL) {
        gDPLoadTLUT_pal256((*gfxP)++, tlut);
    }

    StretchTexTile(&st);
}

/**
 * Original name: StretchTexTile16_LoadTex
 */
void StretchTexTile16_LoadTex(CONST_ARG SStretchTexTile *st) {
    gDPLoadTextureTile((*st->gfxP)++, st->colorTex, G_IM_FMT_RGBA, G_IM_SIZ_16b, st->colorTexW, 0, st->lx, st->top,
                       st->lx + st->lw - 1, st->bottom - 1, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                       G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
}

/**
 * Original name: StretchTexTile16
 */
void StretchTexTile16(Gfx **gfxP, s32 texW, s32 texH, const u16 tex[], s32 lx, s32 ly, s32 lw, s32 lh, f32 x, f32 y,
                      f32 w, f32 h) {
    SStretchTexTile st;

    st.gfxP = gfxP;
    st.vtxP = NULL;

    st.texW = texW;
    st.texH = texH;

    st.colorTex = tex;
    st.colorTexW = texW;
    st.alphaTex = NULL;
    st.alphaTexW = 0;

    st.lx = lx;
    st.ly = ly;
    st.lw = lw;
    st.lh = lh;

    st.x = x * DOUBLE_LITERAL(4);
    st.y = y * DOUBLE_LITERAL(4);
    st.w = w * DOUBLE_LITERAL(4);
    st.h = h * DOUBLE_LITERAL(4);

    st.colorFunc = StretchTexTile16_LoadTex;
    st.alphaFunc = NULL;

    st.step = 0x800 / ALIGN4(lw);

    st.rectFunc = StretchTexTile_ScisRect;

    StretchTexTile(&st);
}

/**
 * Original name: StretchTexTile4i_LoadTex
 */
void StretchTexTile4i_LoadTex(CONST_ARG SStretchTexTile *st) {
    gDPLoadTextureTile_4b((*st->gfxP)++, st->colorTex, G_IM_FMT_I, st->colorTexW, 1, st->lx, st->top,
                          st->lx + st->lw - 1, st->bottom - 1, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK,
                          G_TX_NOLOD, G_TX_NOLOD);
}

/**
 * Original name: StretchTexTile4i
 */
void StretchTexTile4i(Gfx **gfxP, s32 texW, s32 texH, const u8 tex[], s32 lx, s32 ly, s32 lw, s32 lh, f32 x, f32 y,
                      f32 w, f32 h) {
    SStretchTexTile st;

    st.gfxP = gfxP;
    st.vtxP = NULL;

    st.texW = texW;
    st.texH = texH;

    st.colorTex = tex;
    st.colorTexW = texW;
    st.alphaTex = NULL;
    st.alphaTexW = 0;

    st.lx = lx;
    st.ly = ly;
    st.lw = lw;
    st.lh = lh;
    st.x = x * DOUBLE_LITERAL(4);
    st.y = y * DOUBLE_LITERAL(4);
    st.w = w * DOUBLE_LITERAL(4);
    st.h = h * DOUBLE_LITERAL(4);

    st.colorFunc = StretchTexTile4i_LoadTex;
    st.alphaFunc = NULL;

    st.step = 0x2000 / ALIGN16(lw);

    st.rectFunc = StretchTexTile_ScisRect;

    StretchTexTile(&st);
}

/**
 * Original name: RectTexTile4i
 */
void RectTexTile4i(Gfx **gfxP, Vtx **vtxP, s32 texW, s32 texH, const u8 tex[], s32 lx, s32 ly, s32 lw, s32 lh, f32 x,
                   f32 y, f32 w, f32 h) {
    SStretchTexTile st;

    st.gfxP = gfxP;
    st.vtxP = vtxP;

    st.texW = texW;
    st.texH = texH;

    st.colorTex = tex;
    st.colorTexW = texW;
    st.alphaTex = NULL;
    st.alphaTexW = 0;

    st.lx = lx;
    st.ly = ly;
    st.lw = lw;
    st.lh = lh;
    st.x = x * DOUBLE_LITERAL(4);
    st.y = y * DOUBLE_LITERAL(4);
    st.w = w * DOUBLE_LITERAL(4);
    st.h = h * DOUBLE_LITERAL(4);

    st.colorFunc = StretchTexTile4i_LoadTex;
    st.alphaFunc = NULL;

    st.step = 0x2000 / ALIGN16(lw);

    st.rectFunc = RectTexTile_ScisRect;

    StretchTexTile(&st);
}

/**
 * Original name: tiMappingAddr
 */
void tiMappingAddr(TiTexData tiArr[], s32 len, uintptr_t addr) {
    s32 i;

    for (i = 0; i < len; i++) {
        TiTexData *tiTex = &tiArr[i];

        if (tiTex->texs != NULL) {
            tiTex->texs = (void *)((u8 *)tiTex->texs + addr);

            if (tiTex->texs[TI_TEX_TLUT] != NULL) {
                tiTex->texs[TI_TEX_TLUT] = (void *)((uintptr_t)tiTex->texs[TI_TEX_TLUT] + addr);
            }

            if (tiTex->texs[TI_TEX_TEX] != NULL) {
                tiTex->texs[TI_TEX_TEX] = (void *)((uintptr_t)tiTex->texs[TI_TEX_TEX] + addr);
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
void tiCopyTexBlock(Gfx **gfxP, const TiTexData *ti, bool cached, s32 x, s32 y) {
    const u16 *tlut;
    const Texture *tex;

    if (cached) {
        tlut = NULL;
        tex = NULL;
    } else {
        tlut = ti->texs[TI_TEX_TLUT];
        tex = ti->texs[TI_TEX_TEX];
    }

    switch (ti->info[TI_INFO_IDX_FORMAT]) {
        case TITEX_FORMAT_4:
            CopyTexBlock4(gfxP, tlut, tex, x, y, ti->info[TI_INFO_IDX_WIDTH], ti->info[TI_INFO_IDX_HEIGHT]);
            break;

        case TITEX_FORMAT_8:
            CopyTexBlock8(gfxP, tlut, tex, x, y, ti->info[TI_INFO_IDX_WIDTH], ti->info[TI_INFO_IDX_HEIGHT]);
            break;

        case TITEX_FORMAT_16:
            CopyTexBlock16(gfxP, tex, x, y, ti->info[TI_INFO_IDX_WIDTH], ti->info[TI_INFO_IDX_HEIGHT]);
            break;
    }
}

/**
 * Original name: tiStretchTexBlock
 */
void tiStretchTexBlock(Gfx **gfxP, const TiTexData *ti, bool cached, f32 x, f32 y, f32 w, f32 h) {
    const Texture *tlut;
    const Texture *tex;

    if (cached) {
        tlut = NULL;
        tex = NULL;
    } else {
        tlut = ti->texs[TI_TEX_TLUT];
        tex = ti->texs[TI_TEX_TEX];
    }

    if (ti->texs[TI_TEX_TLUT] != NULL) {
        switch (ti->info[TI_INFO_IDX_FORMAT]) {
            case TITEX_FORMAT_4:
                StretchTexBlock4(gfxP, ti->info[TI_INFO_IDX_WIDTH], ti->info[TI_INFO_IDX_HEIGHT], tlut, tex, x, y, w,
                                 h);
                break;

            case TITEX_FORMAT_8:
                StretchTexBlock8(gfxP, ti->info[TI_INFO_IDX_WIDTH], ti->info[TI_INFO_IDX_HEIGHT], tlut, tex, x, y, w,
                                 h);
                break;
        }
    } else {
        switch (ti->info[TI_INFO_IDX_FORMAT]) {
            case TITEX_FORMAT_4:
                StretchTexBlock4i(gfxP, ti->info[TI_INFO_IDX_WIDTH], ti->info[TI_INFO_IDX_HEIGHT], tex, x, y, w, h);
                break;

            case TITEX_FORMAT_16:
                StretchTexBlock16(gfxP, ti->info[TI_INFO_IDX_WIDTH], ti->info[TI_INFO_IDX_HEIGHT], tex, x, y, w, h);
                break;
        }
    }
}

/**
 * Original name: tiStretchTexTile
 */
void tiStretchTexTile(Gfx **gfxP, const TiTexData *ti, bool cached, s32 lx, s32 ly, s32 lw, s32 lh, f32 x, f32 y, f32 w,
                      f32 h) {
    const u16 *tlut;
    const Texture *tex;

    if (cached) {
        tlut = NULL;
        tex = NULL;
    } else {
        tlut = ti->texs[TI_TEX_TLUT];
        tex = ti->texs[TI_TEX_TEX];
    }

    if (ti->texs[TI_TEX_TLUT] != NULL) {
        switch (ti->info[TI_INFO_IDX_FORMAT]) {
            case TITEX_FORMAT_4:
                StretchTexTile4(gfxP, ti->info[TI_INFO_IDX_WIDTH], ti->info[TI_INFO_IDX_HEIGHT], tlut, tex, lx, ly, lw,
                                lh, x, y, w, h);
                break;

            case TITEX_FORMAT_8:
                StretchTexTile8(gfxP, ti->info[TI_INFO_IDX_WIDTH], ti->info[TI_INFO_IDX_HEIGHT], tlut, tex, lx, ly, lw,
                                lh, x, y, w, h);
                break;
        }
    } else {
        switch (ti->info[TI_INFO_IDX_FORMAT]) {
            case TITEX_FORMAT_4:
                StretchTexTile4i(gfxP, ti->info[TI_INFO_IDX_WIDTH], ti->info[TI_INFO_IDX_HEIGHT], tex, lx, ly, lw, lh,
                                 x, y, w, h);
                break;

            case TITEX_FORMAT_16:
                StretchTexTile16(gfxP, ti->info[TI_INFO_IDX_WIDTH], ti->info[TI_INFO_IDX_HEIGHT], tex, lx, ly, lw, lh,
                                 x, y, w, h);
                break;
        }
    }
}

/**
 * Original name: tiStretchTexItem
 */
void tiStretchTexItem(Gfx **gfxP, const TiTexData *ti, bool cached, s32 count, s32 index, f32 x, f32 y, f32 w, f32 h) {
    s32 height = ti->info[TI_INFO_IDX_HEIGHT] / count;
    s32 offset = ti->info[TI_INFO_IDX_WIDTH] * height * index;
    const u16 *tlut;
    const Texture *texture;

    if (cached) {
        tlut = NULL;
        texture = NULL;
    } else {
        tlut = ti->texs[TI_TEX_TLUT];
        texture = ti->texs[TI_TEX_TEX];

        switch (ti->info[TI_INFO_IDX_FORMAT]) {
            case TITEX_FORMAT_4:
                texture = (const u8 *)texture + offset / 2;
                break;

            case TITEX_FORMAT_8:
                texture = (const u8 *)texture + offset;
                break;

            case TITEX_FORMAT_16:
                texture = (const u16 *)texture + offset;
                break;
        }
    }

    if (ti->info[TI_INFO_IDX_FLAGS] & TITEX_FLAGS_BLOCK) {
        switch (ti->info[TI_INFO_IDX_FORMAT]) {
            case TITEX_FORMAT_4:
                StretchTexBlock4(gfxP, ti->info[TI_INFO_IDX_WIDTH], height, tlut, texture, x, y, w, h);
                break;

            case TITEX_FORMAT_8:
                StretchTexBlock8(gfxP, ti->info[TI_INFO_IDX_WIDTH], height, tlut, texture, x, y, w, h);
                break;
        }
    } else {
        switch (ti->info[TI_INFO_IDX_FORMAT]) {
            case TITEX_FORMAT_4:
                StretchTexTile4(gfxP, ti->info[TI_INFO_IDX_WIDTH], height, tlut, texture, 0, 0,
                                ti->info[TI_INFO_IDX_WIDTH], height, x, y, w, h);
                break;

            case TITEX_FORMAT_8:
                StretchTexTile8(gfxP, ti->info[TI_INFO_IDX_WIDTH], height, tlut, texture, 0, 0,
                                ti->info[TI_INFO_IDX_WIDTH], height, x, y, w, h);
                break;
        }
    }
}

/**
 * Original name: tiStretchAlphaTexItem
 */
void tiStretchAlphaTexItem(Gfx **gfxP, const TiTexData *tiC, const TiTexData *tiA, bool cached, s32 count, s32 index,
                           f32 x, f32 y, f32 w, f32 h) {
    s32 var_t3 = MIN(tiC->info[TI_INFO_IDX_WIDTH], tiA->info[TI_INFO_IDX_WIDTH]);
    s32 var_t2 = MIN(tiC->info[TI_INFO_IDX_HEIGHT] / count, tiA->info[TI_INFO_IDX_HEIGHT]);
    const Texture *texs[2];

    if (cached) {
        texs[0] = NULL;
        texs[1] = NULL;
    } else {
        texs[0] = (const u16 *)tiC->texs[TI_TEX_TEX] + tiC->info[TI_INFO_IDX_WIDTH] * var_t2 * index;
        texs[1] = (const u8 *)tiA->texs[TI_TEX_TEX] + tiA->info[TI_INFO_IDX_WIDTH] * var_t2 * index / 2;
    }

    if ((tiC->info[TI_INFO_IDX_FLAGS] & TITEX_FLAGS_BLOCK) && (tiA->info[TI_INFO_IDX_FLAGS] & TITEX_FLAGS_BLOCK)) {
        StretchAlphaTexBlock(gfxP, var_t3, var_t2, texs[0], tiC->info[TI_INFO_IDX_WIDTH], texs[1],
                             tiA->info[TI_INFO_IDX_WIDTH], x, y, w, h);
    } else {
        StretchAlphaTexTile(gfxP, var_t3, var_t2, texs[0], tiC->info[TI_INFO_IDX_WIDTH], texs[1],
                            tiA->info[TI_INFO_IDX_WIDTH], 0, 0, var_t3, var_t2, x, y, w, h);
    }
}

void tiStretchAlphaTexItem2(Gfx **gfxP, const TiTexData *tiC, const TiTexData *tiA, bool cached, s32 count, s32 index,
                            f32 x, f32 y, f32 w, f32 h) {
    s32 var_t3 = MIN(tiC->info[TI_INFO_IDX_WIDTH], tiA->info[TI_INFO_IDX_WIDTH]);
    s32 var_t1 = MIN(tiC->info[TI_INFO_IDX_HEIGHT] / count, tiA->info[TI_INFO_IDX_HEIGHT]);
    const Texture *sp40[2];

    if (cached) {
        sp40[0] = NULL;
        sp40[1] = NULL;
    } else {
        sp40[0] = (const u16 *)tiC->texs[TI_TEX_TEX] + tiC->info[TI_INFO_IDX_WIDTH] * var_t1 * index;
        sp40[1] = tiA->texs[TI_TEX_TEX];
    }

    if ((tiC->info[TI_INFO_IDX_FLAGS] & TITEX_FLAGS_BLOCK) && (tiA->info[TI_INFO_IDX_FLAGS] & TITEX_FLAGS_BLOCK)) {
        StretchAlphaTexBlock(gfxP, var_t3, var_t1, sp40[0], tiC->info[TI_INFO_IDX_WIDTH], sp40[1],
                             tiA->info[TI_INFO_IDX_WIDTH], x, y, w, h);
    } else {
        StretchAlphaTexTile(gfxP, var_t3, var_t1, sp40[0], tiC->info[TI_INFO_IDX_WIDTH], sp40[1],
                            tiA->info[TI_INFO_IDX_WIDTH], 0, 0, var_t3, var_t1, x, y, w, h);
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
void drawCursorPattern(Gfx **gfxP, s32 arg1 UNUSED, s32 arg2 UNUSED, s32 frmW, s32 frmH, s32 posX, s32 posY, s32 posW,
                       s32 posH) {
    Gfx *gfx = *gfxP;
    s32 px[4];
    s32 py[4];
    s32 tx[3];
    s32 ty[3];
    s32 dx[3];
    s32 i;
    s32 temp;

    temp = posW + frmW;

    px[0] = (posX * 4) - (frmW * 2);
    px[3] = px[0] + temp * 4;
    px[1] = px[0] + frmW * 4;
    px[2] = px[3] - frmW * 4;

    tx[0] = 0;
    tx[1] = (frmW - 1) << 5;
    tx[2] = frmW << 5;

    temp = posH + frmH;

    py[0] = (posY * 4) - (frmH * 2);
    py[3] = py[0] + temp * 4;
    py[1] = py[0] + frmH * 4;
    py[2] = py[3] - frmH * 4;

    ty[0] = 0;
    ty[1] = (frmH - 1) << 5;
    ty[2] = frmH << 5;

    dx[0] = -0x400;
    dx[1] = 0;
    dx[2] = 0x400;

    for (i = 0; i < ARRAY_COUNTU(_pnts_871); i++) {
        // Cast away the const
        u8 *pnts = (void *)_pnts_871[i];

        gSPScisTextureRectangle(gfx++, px[pnts[0]], py[pnts[1]], px[pnts[2]], py[pnts[3]], G_TX_RENDERTILE, tx[pnts[4]],
                                ty[pnts[5]], dx[pnts[6]], dx[pnts[7]]);
    }

    *gfxP = gfx;
}

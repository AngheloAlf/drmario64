#include "020D10.h"

#include "alignment.h"

#include "libc/stdint.h"

#include "include_asm.h"
#include "macros_defines.h"
#include "unk.h"

#include "buffers.h"
#include "graphic.h"

#define STRUCT_800E53B0_A_UNK_LEN 3

typedef struct struct_800E53B0_a {
    /* 0x00 */ Mtx unk_00;
    /* 0x40 */ u16 perspNorm;
    /* 0x42 */ UNK_TYPE1 unk_42[0x2]; // pad?
    /* 0x44 */ u16 *framebuffer;
    /* 0x48 */ Vtx *unk_48[STRUCT_800E53B0_A_UNK_LEN]; // vtx
    /* 0x54 */ Gfx *unk_54[STRUCT_800E53B0_A_UNK_LEN]; // gfx
    /* 0x60 */ Mtx *unk_60[STRUCT_800E53B0_A_UNK_LEN]; // mtx
    /* 0x6C */ UNK_TYPE unk_6C;
    /* 0x70 */ UNK_TYPE unk_70; // bool?
    /* 0x74 */ u32 unk_74;
    /* 0x78 */ UNK_TYPE unk_78;
    /* 0x7C */ UNK_TYPE1 unk_7C[0x4]; // pad?
} struct_800E53B0_a;                  // size = 0x80

typedef f32(struct_800E53B0_b_unk_7C)[6];

// TODO: maybe same struct as struct_800E53B0_b_unk_7C?
typedef f32(struct_800E53B0_b_unk_80)[6];

typedef struct struct_800E53B0_b {
    /* 0x00 */ Mtx unk_00;
    /* 0x40 */ u16 perspNorm;
    /* 0x42 */ UNK_TYPE1 unk_42[0x2]; // pad?
    /* 0x44 */ u16 *framebuffer;
    /* 0x48 */ Vtx *unk_48[3];
    /* 0x54 */ Gfx *unk_54[3];
    /* 0x60 */ Mtx *unk_60[3];
    /* 0x6C */ UNK_TYPE unk_6C;
    /* 0x70 */ UNK_TYPE unk_70;
    /* 0x74 */ u32 unk_74;
    /* 0x78 */ UNK_TYPE unk_78;
    /* 0x7C */ struct_800E53B0_b_unk_7C *unk_7C;
    /* 0x80 */ struct_800E53B0_b_unk_80 *unk_80;
    /* 0x84 */ UNK_TYPE1 unk_84[0x4]; // pad?
} struct_800E53B0_b;                  // size = 0x88

typedef union struct_800E53B0 {
    struct_800E53B0_a a;
    struct_800E53B0_b b;
} struct_800E53B0;

static struct_800E53B0 *B_800E53B0;

Gfx D_8008CFA0[] = {
    gsDPPipeSync(),
    gsSPGeometryMode(0, 0),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCycleType(G_CYC_COPY),
    gsDPSetRenderMode(G_RM_NOOP, G_RM_NOOP2),
    gsDPSetCombineLERP(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureLUT(G_TT_NONE),
    gsSPEndDisplayList(),
};

s32 D_8008CFE0 = 0;

void func_80038EF0(Mtx *mtx, u16 *perspNorm) {
    f32 sp28[4][4];
    f32 sp68[4][4];
    f32 spA8[4];
    s32 i;

    guTranslateF(sp28, 0.0f, 0.0f, -512.0f);
    guPerspectiveF(sp68, perspNorm, 30.0f, 4.0f / 3.0f, 192.0f, 832.0f, 1.0f);
    guMtxCatF(sp28, sp68, sp68);

    for (i = 0; i < 4; i++) {
        spA8[i] = sp68[0][i] * 160.0f + sp68[1][i] * 120.0f + sp68[3][i];
    }

    guScaleF(sp28, spA8[3] / spA8[0], spA8[3] / spA8[1], 1.0f);
    guMtxCatF(sp28, sp68, sp28);
    guMtxF2L(sp28, mtx);
}

void func_8003901C(Gfx **gfxP, u16 *tex, s32 x, s32 y, s32 w, s32 h) {
    Gfx *gfx = *gfxP;
    s32 step = 0x800 / w;
    s32 top;

    gSPDisplayList(gfx++, D_8008CFA0);

    for (top = 0; top < h; top += step) {
        gDPLoadTextureTile(gfx++, &tex[w * top], G_IM_FMT_RGBA, G_IM_SIZ_16b, w, step, 0, 0, w - 1,
                           MIN(step, h - top) - 1, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                           G_TX_NOLOD);

        gSPScisTextureRectangle(gfx++, x << (x < 0 ? 0 : 2), (y + top) << 2, (x + w - 1) << 2,
                                (MIN(y + top + step, y + h) - 1) << 2, G_TX_RENDERTILE, 0, 0, 4 << 10, 1 << 10);
    }

    *gfxP = gfx;
}

void func_800393DC(Vtx **vtxP, void **heapP) {
    s32 i;

    *vtxP = ALIGN_PTR(*heapP);
    *heapP = (void *)((uintptr_t)*vtxP + sizeof(Vtx) * 0x15 * 0x10);

    for (i = 0; i < 0x15; i++) {
        Vtx *vtx;
        s32 j;

        for (j = 0; j < 0x10; j++) {
            vtx = &(*vtxP)[(i * 0x10) + j];

            vtx->v.ob[0] = i * 0x10 - 0xA0;
            vtx->v.ob[1] = 0x78 - j * 0x10;
            vtx->v.ob[2] = 0;
            vtx->v.flag = 0;
            vtx->v.tc[0] = i << 0xA;
            vtx->v.tc[1] = j << 0xA;
            vtx->v.cn[0] = 0;
            vtx->v.cn[1] = 0;
            vtx->v.cn[2] = 0x7F;
            vtx->v.cn[3] = 0xFF;

            if (i == 0x15 - 1) {
                vtx->v.tc[0] -= 0x80;
            }
        }

        vtx->v.tc[1] -= 0x80;
    }
}

void func_800394A0(Gfx **gfxP, Vtx *vtx, u16 *framebuffer, void **heapP) {
    Gfx *gfx;
    s32 var_t2;
    s32 var_t0;

    *gfxP = ALIGN_PTR(*heapP);
    gfx = *gfxP;

    gSPVertex(gfx++, vtx, 16, 0);

    for (var_t2 = 0; var_t2 < 0x14; var_t2++) {
        // ??
        gSPVertex(gfx++, &vtx[(var_t2 + 1) * 0x10], 16, (var_t2 % 2 == 0) ? 16 : 0);

        for (var_t0 = 0; var_t0 < 0xF; var_t0++) {
            if (var_t0 % 4 == 0) {
                gDPLoadTextureTile(gfx++, framebuffer, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0x140, 0, var_t2 * 0x10,
                                   var_t0 * 0x10, var_t2 * 0x10 + 0xF, MIN(var_t0 * 0x10 + 0x3F, 0xEF), 0,
                                   G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK,
                                   G_TX_NOLOD, G_TX_NOLOD);
            }

            if (var_t2 % 2 != 0) {
                gSP2Triangles(gfx++, var_t0 + 0x10, var_t0 + 0x11, var_t0, 0, var_t0 + 0x11, var_t0 + 1, var_t0, 0);
            } else {
                gSP2Triangles(gfx++, var_t0, var_t0 + 1, var_t0 + 0x10, 0, var_t0 + 1, var_t0 + 0x11, var_t0 + 0x10, 0);
            }
        }
    }

    gSPEndDisplayList(gfx++);

    *heapP = gfx;
}

typedef struct struct_func_8003974C_sp18_unk_00 {
    /* 0x0 */ f32 unk_0;
    /* 0x4 */ f32 unk_4;
    /* 0x8 */ f32 unk_8;
} struct_func_8003974C_sp18_unk_00; // size = 0xC

typedef struct struct_func_8003974C_sp18 {
    /* 0x00 */ struct_func_8003974C_sp18_unk_00 unk_00[0xF];
} struct_func_8003974C_sp18; // size = 0xB4

void func_8003974C(Vtx *vtx);

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/unused/020D10", func_8003974C);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/unused/020D10", func_8003974C);
#endif

#if VERSION_CN
#ifdef NON_MATCHING
void func_8003974C(Vtx *vtx) {
    struct_func_8003974C_sp18 sp18[0x14];
    f32 spE28[8];

    Vtx *temp_a1;
    Vtx *temp_a2;
    Vtx *temp1;
    struct_func_8003974C_sp18 *temp_v0;
    f32 var_ft0;
    s32 var_s0;
    s32 var_s1;
    s32 var_v0;
    s32 temp2;

    // var_t4 = vtx;

    for (var_s1 = 0; var_s1 < 0x14; var_s1++) {
        temp_v0 = &sp18[var_s1];

        for (var_s0 = 0; var_s0 < 0xF; var_s0++) {
            temp_a2 = &vtx[((var_s1 + 1) * 0x10) + var_s0];
            temp_a1 = &vtx[var_s1 * 0x10 + var_s0];
            temp1 = &vtx[var_s1 * 0x10 + var_s0 + 1];
            spE28[0] = (f32)(temp_a1->v.ob[0] - temp_a2->v.ob[0]);
            spE28[1] = (f32)(temp_a1->v.ob[1] - temp_a2->v.ob[1]);
            spE28[2] = (f32)(temp_a1->v.ob[2] - temp_a2->v.ob[2]);
            // no [3]
            spE28[4] = (f32)(temp1->v.ob[0] - temp_a1->v.ob[0]);
            spE28[5] = (f32)(temp1->v.ob[1] - temp_a1->v.ob[1]);
            spE28[6] = (f32)(temp1->v.ob[2] - temp_a1->v.ob[2]);
            temp_v0->unk_00[var_s0].unk_0 = (spE28[1] * spE28[6]) - (spE28[2] * spE28[5]);
            temp_v0->unk_00[var_s0].unk_4 = (spE28[2] * spE28[4]) - (spE28[0] * spE28[6]);
            temp_v0->unk_00[var_s0].unk_8 = (spE28[0] * spE28[5]) - (spE28[1] * spE28[4]);
        }
    }

    for (var_s1 = 1; var_s1 < 0x14; var_s1++) {
        for (var_s0 = 1; var_s0 < 0xF; var_s0++) {
            spE28[0] = sp18[var_s1].unk_00[var_s0].unk_0 + sp18[var_s1].unk_00[var_s0 - 1].unk_0 +
                       sp18[var_s1 - 1].unk_00[var_s0].unk_0 + sp18[var_s1 - 1].unk_00[var_s0 - 1].unk_0;
            spE28[1] = sp18[var_s1].unk_00[var_s0].unk_4 + sp18[var_s1].unk_00[var_s0 - 1].unk_4 +
                       sp18[var_s1 - 1].unk_00[var_s0].unk_4 + sp18[var_s1 - 1].unk_00[var_s0 - 1].unk_4;
            spE28[2] = sp18[var_s1].unk_00[var_s0].unk_8 + sp18[var_s1].unk_00[var_s0 - 1].unk_8 +
                       sp18[var_s1 - 1].unk_00[var_s0].unk_8 + sp18[var_s1 - 1].unk_00[var_s0 - 1].unk_8;

            var_ft0 = sqrtf((spE28[0] * spE28[0]) + (spE28[1] * spE28[1]) + (spE28[2] * spE28[2]));
            if (var_ft0 != 0.0f) {
                var_ft0 = 127.0f / var_ft0;
            }
            temp_a2 = &vtx[var_s1 * 0x10 + var_s0];
            temp_a2->v.cn[0] = (u8)(s32)(spE28[0] * var_ft0);
            temp_a2->v.cn[1] = (u8)(s32)(spE28[1] * var_ft0);
            temp_a2->v.cn[2] = (u8)(s32)(spE28[2] * var_ft0);
        }
    }

    for (var_s1 = 0; var_s1 < 0x15; var_s1 += 0x14) {
        for (var_s0 = 0; var_s0 < 0x10; var_s0 += 0xF) {
            temp_a2 = &vtx[(var_s1 * 0x10) + var_s0];

            var_v0 = ((var_s1 != 0) ? (var_s1 - 1) : 1) * 0x10;

            temp2 = ((var_s0 != 0) ? (var_v0 - 1) : (var_v0 + 1));

            temp_a1 = &vtx[temp2 + var_s0];
            temp_a2->v.cn[0] = temp_a1->v.cn[0];
            temp_a2->v.cn[1] = temp_a1->v.cn[1];
            temp_a2->v.cn[2] = temp_a1->v.cn[2];
        }
    }

    for (var_s1 = 1; var_s1 < 0x14; var_s1++) {
        temp_a2 = &vtx[var_s1 * 0x10];
        temp_a1 = &vtx[var_s1 * 0x10 + 1];
        temp_a2->v.cn[0] = temp_a1->v.cn[0];
        temp_a2->v.cn[1] = temp_a1->v.cn[1];
        temp_a2->v.cn[2] = temp_a1->v.cn[2];

        temp_a2 = &vtx[var_s1 * 0x10 + 0xF];
        temp_a1 = &vtx[var_s1 * 0x10 + 0xE];
        temp_a2->v.cn[0] = temp_a1->v.cn[0];
        temp_a2->v.cn[1] = temp_a1->v.cn[1];
        temp_a2->v.cn[2] = temp_a1->v.cn[2];
    }

    for (var_s0 = 1; var_s0 < 0xF; var_s0++) {
        temp_a2 = &vtx[var_s0];
        temp_a1 = &vtx[var_s0 + 0x10];
        temp_a2->v.cn[0] = temp_a1->v.cn[0];
        temp_a2->v.cn[1] = temp_a1->v.cn[1];
        temp_a2->v.cn[2] = temp_a1->v.cn[2];

        temp_a2 = &vtx[var_s0 + 0x140];
        temp_a1 = &vtx[var_s0 + 0x130];
        temp_a2->v.cn[0] = temp_a1->v.cn[0];
        temp_a2->v.cn[1] = temp_a1->v.cn[1];
        temp_a2->v.cn[2] = temp_a1->v.cn[2];
    }
}
#else
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/unused/020D10", func_8003974C);
#endif
#endif

void func_80039BE0(Vtx *vtx, f32 arg1, f32 arg2, f32 arg3) {
    f32 sp18[0x10];
    s32 var_t0;
    s32 var_s0;

    arg2 = PI_F / arg2;

    for (var_t0 = 0; var_t0 < ARRAY_COUNT(sp18); var_t0++) {
        sp18[var_t0] = (var_t0 + 1) * arg3;
    }

    for (var_s0 = 0; var_s0 < 0x15; var_s0++) {
        Vtx *var_s1 = &vtx[var_s0 * ARRAY_COUNT(sp18)];
        f32 temp_fv1 = sinf((arg1 + var_s0 * 16.0f) * arg2);

        for (var_t0 = 0; var_t0 < ARRAY_COUNT(sp18); var_t0++) {
            var_s1[var_t0].v.ob[2] = (s16)(s32)(temp_fv1 * sp18[var_t0]);
        }
    }

    func_8003974C(vtx);
}

void func_80039D08(Vtx *vtx, s32 arg1, struct_800E53B0_b_unk_7C *arg2, struct_800E53B0_b_unk_80 *arg3, f32 arg4) {
    s32 i;

    for (i = 0; i < arg1; i++) {
        f32 *a = arg2[i];
        f32 *b = arg3[i];

        f32 temp_fs1 = a[0] + (b[0] - a[0]) * arg4;
        f32 temp_fs0 = a[1] + (b[1] - a[1]) * arg4;
        f32 temp_ft1 = a[2] + (b[2] - a[2]) * arg4;
        f32 temp_ft0 = a[3] + (b[3] - a[3]) * arg4;
        f32 temp_fv1 = a[4] + (b[4] - a[4]) * arg4;
        f32 temp_fv0 = a[5] + (b[5] - a[5]) * arg4;

        //! FAKE: Required redundant casts?
        vtx[i].v.ob[0] = (s16)temp_fs1;
        vtx[i].v.ob[1] = (s16)temp_fs0;
        vtx[i].v.ob[2] = (s16)temp_ft1;
        vtx[i].v.cn[0] = (s8)temp_ft0;
        vtx[i].v.cn[1] = (s8)temp_fv1;
        vtx[i].v.cn[2] = (s8)temp_fv0;
    }
}

void *func_80039E14(void *heap) {
    struct_800E53B0_a *temp_s1;
    s32 i;

    B_800E53B0 = ALIGN_PTR(heap);
    temp_s1 = &B_800E53B0->a;
    heap = (void *)((uintptr_t)temp_s1 + sizeof(struct_800E53B0_a));

    func_80038EF0(&temp_s1->unk_00, &temp_s1->perspNorm);

    temp_s1->framebuffer = ALIGN_PTR(heap);
    heap = (void *)((uintptr_t)temp_s1->framebuffer + sizeof(u16) * SCREEN_HEIGHT * SCREEN_WIDTH);
    bcopy(gFramebuffers[gCurrentFramebufferIndex ^ 1], temp_s1->framebuffer,
          sizeof(u16) * SCREEN_HEIGHT * SCREEN_WIDTH);

    for (i = 0; i < STRUCT_800E53B0_A_UNK_LEN; i++) {
        func_800393DC(&temp_s1->unk_48[i], &heap);
        func_8003974C(temp_s1->unk_48[i]);
        func_800394A0(&temp_s1->unk_54[i], temp_s1->unk_48[i], temp_s1->framebuffer, &heap);

        temp_s1->unk_60[i] = ALIGN_PTR(heap);
        heap = (void *)((uintptr_t)temp_s1->unk_60[i] + sizeof(Mtx));

        guMtxIdent(temp_s1->unk_60[i]);
    }

    temp_s1->unk_6C = 0;
    temp_s1->unk_70 = 0;
    temp_s1->unk_74 = 0;
    temp_s1->unk_78 = 0;

    return heap;
}

const Lights1 RO_800ACFB0 = {
    { { { 0x9F, 0x9F, 0x9F }, 0, { 0x9F, 0x9F, 0x9F }, 0 } },
    {
        {
            { { 0xFF, 0xFF, 0xFF }, 0, { 0xFF, 0xFF, 0xFF }, 0, { 0x49, 0x49, 0x49 }, 0 },
        },
    },
};

const Gfx RO_800ACFC8[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_BOTH | G_FOG | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPSetLights1(RO_800ACFB0),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
    gsDPSetCombineMode(G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsDPSetTextureConvert(G_TC_FILT),
    gsDPSetConvert(G_CV_K0, G_CV_K1, G_CV_K2, G_CV_K3, G_CV_K4, G_CV_K5),
    gsSPEndDisplayList(),
};

// TODO: return bool?
s32 func_80039F74(void) {
    struct_800E53B0_a *temp_s2 = &B_800E53B0->a;
    f32 sp18[4][4];
    f32 sp58[4][4];
    f32 temp_fs2;
    f32 var_fv1_2;
    f32 var_ft0;
    s32 temp_s3;

    if (temp_s2->unk_70 != 0) {
        return 0;
    }

    var_fv1_2 = MIN(temp_s2->unk_74 * (1.0f / 40.0f), 1.0f);

    temp_s2->unk_70 = (var_fv1_2 == 1.0f);

    temp_fs2 = var_fv1_2 * 60.0f;
    temp_s3 = (temp_s2->unk_6C + 1) % 3;
    var_ft0 = temp_s2->unk_74;

    func_80039BE0(temp_s2->unk_48[temp_s3], var_ft0, temp_fs2 * 4.0f + 120.0f, temp_fs2 * (1.0f / 2.0f));

    guTranslateF(sp18, 0.0f, -160.0f, 0.0f);
    guRotateRPYF(sp58, -temp_fs2 * 0.5f, 0.0f, 0.0f);
    guMtxCatF(sp18, sp58, sp18);
    guTranslateF(sp58, 0.0f, 160.0f, 0.0f);
    guMtxCatF(sp18, sp58, sp18);
    guMtxF2L(sp18, temp_s2->unk_60[temp_s3]);

    temp_s2->unk_6C = temp_s3;
    temp_s2->unk_74++;

    return 1;
}

void func_8003A1B4(Gfx **gfxP) {
    struct_800E53B0_a *ptr = &B_800E53B0->a;
    Gfx *gfx;
    s32 temp;

    if (ptr->unk_70 != 0) {
        return;
    }

    gfx = *gfxP;
    temp = ptr->unk_6C;

    gSPDisplayList(gfx++, RO_800ACFC8);
    gSPPerspNormalize(gfx++, ptr->perspNorm);
    gSPMatrix(gfx++, &ptr->unk_00, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gSPMatrix(gfx++, ptr->unk_60[temp], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(gfx++, ptr->unk_54[temp]);

    *gfxP = gfx;
    ptr->unk_78++;
}

void *func_8003A26C(void *heap) {
    f32 temp_fs0_2;
    f32 temp_fs1;
    f32 temp_fs2;
    f32 temp_fv0_2;
    struct_800E53B0_b *temp_s3;
    s32 var_s1;
    s32 var_s2;
    s32 var_s5;
    f32 *temp_s0;
    f32 *temp_v1;

    s32 s6;

    B_800E53B0 = ALIGN_PTR(heap);
    temp_s3 = &B_800E53B0->b;
    heap = (void *)((uintptr_t)temp_s3 + sizeof(struct_800E53B0_b));

    func_80038EF0(&temp_s3->unk_00, &temp_s3->perspNorm);

    temp_s3->framebuffer = ALIGN_PTR(heap);
    heap = (void *)((uintptr_t)temp_s3->framebuffer + sizeof(u16) * SCREEN_HEIGHT * SCREEN_WIDTH);

    bcopy(gFramebuffers[gCurrentFramebufferIndex ^ 1], (void *)temp_s3->framebuffer,
          sizeof(u16) * SCREEN_HEIGHT * SCREEN_WIDTH);

    temp_s3->unk_7C = ALIGN_PTR(heap);
    heap = (void *)((uintptr_t)temp_s3->unk_7C + sizeof(struct_800E53B0_b_unk_7C) * 0x15 * 0x10);

    for (var_s2 = 0; var_s2 < 0x15; var_s2++) {
        for (var_s1 = 0; var_s1 < 0x10; var_s1++) {
            temp_v1 = temp_s3->unk_7C[var_s2 * 0x10 + var_s1];

            temp_v1[0] = var_s2 * 0x10 - 0xA0;
            temp_v1[1] = 0x78 - var_s1 * 0x10;
            temp_v1[2] = 0;
            temp_v1[3] = 0;
            temp_v1[4] = 0;
            temp_v1[5] = 127.0f;
        }
    }

    temp_s3->unk_80 = ALIGN_PTR(heap);
    heap = (void *)((uintptr_t)temp_s3->unk_80 + sizeof(struct_800E53B0_b_unk_80) * 0x15 * 0x10);

    for (var_s2 = 0; var_s2 < 0x15; var_s2++) {
        temp_fs1 = sinf(PI_F / 10 * var_s2);
        temp_fs2 = cosf(PI_F / 10 * var_s2);

        for (var_s1 = 0; var_s1 < 0x10; var_s1++) {
            temp_s0 = temp_s3->unk_80[var_s2 * 0x10 + var_s1];

            temp_fs0_2 = sinf(PI_F / 15 * var_s1);
            temp_fv0_2 = cosf(PI_F / 15 * var_s1);

            temp_s0[1] = temp_s0[1 + 3] = temp_fv0_2;
            temp_s0[0] = temp_s0[0 + 3] = -temp_fs1 * temp_fs0_2;
            temp_s0[2] = temp_s0[2 + 3] = -temp_fs2 * temp_fs0_2;

            temp_s0[0] *= 80.0f;
            temp_s0[1] *= 80.0f;
            temp_s0[2] *= 80.0f;
            temp_s0[3] *= 127.0f;
            temp_s0[4] *= 127.0f;
            temp_s0[5] *= 127.0f;
        }
    }

    for (var_s5 = 0; var_s5 < 3; var_s5++) {
        func_800393DC(&temp_s3->unk_48[var_s5], &heap);
        func_80039D08(temp_s3->unk_48[var_s5], 0x150, temp_s3->unk_7C, temp_s3->unk_80, 0);
        func_800394A0(&temp_s3->unk_54[var_s5], temp_s3->unk_48[var_s5], temp_s3->framebuffer, &heap);

        temp_s3->unk_60[var_s5] = ALIGN_PTR(heap);
        heap = (void *)((uintptr_t)temp_s3->unk_60[var_s5] + sizeof(Mtx));

        guRotateRPY(temp_s3->unk_60[var_s5], 0.0f, s6 * 180.0f, 0.0f);
    }

    temp_s3->unk_6C = 0;
    temp_s3->unk_70 = 0;
    temp_s3->unk_74 = 0;
    temp_s3->unk_78 = 0;

    return heap;
}

const Lights1 RO_800AD080 = {
    { { { 0x9F, 0x9F, 0x9F }, 0, { 0x9F, 0x9F, 0x9F }, 0 } },
    {
        {
            { { 0xFF, 0xFF, 0xFF }, 0, { 0xFF, 0xFF, 0xFF }, 0, { 0x49, 0x49, 0x49 }, 0 },
        },
    },
};

const Gfx RO_800AD098[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_FRONT | G_FOG | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPSetLights1(RO_800AD080),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
    gsDPSetCombineMode(G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsDPSetTextureConvert(G_TC_FILT),
    gsDPSetConvert(G_CV_K0, G_CV_K1, G_CV_K2, G_CV_K3, G_CV_K4, G_CV_K5),
    gsSPEndDisplayList(),
};

s32 func_8003A618(void) {
    struct_800E53B0_b *temp_s1 = &B_800E53B0->b;
    f32 var_fs0;
    s32 temp_s2;

    if (temp_s1->unk_70 != 0) {
        return 0;
    }

    var_fs0 = MIN(temp_s1->unk_74 * (1.0f / 30.0f), 1.0f);
    temp_s1->unk_70 = var_fs0 == 1.0f;
    temp_s2 = (temp_s1->unk_6C + 1) % 3;

    if (var_fs0 < 0.5f) {
        // TODO: This is a weird way of writing this
        var_fs0 = 2.0f * var_fs0;
        var_fs0 = 1.0f - var_fs0;
        var_fs0 = var_fs0 * var_fs0;
        var_fs0 = 1.0f - var_fs0;
        func_80039D08(temp_s1->unk_48[temp_s2], 0x150, temp_s1->unk_7C, temp_s1->unk_80, var_fs0);
    } else if (var_fs0 <= 1.0f) {
        var_fs0 = 2.0f * (var_fs0 - 0.5f);
        var_fs0 = 1.0f - var_fs0 * var_fs0;
        func_80039D08(temp_s1->unk_48[temp_s2], 0x150, temp_s1->unk_7C, temp_s1->unk_80, 1.0f);
        guScale(temp_s1->unk_60[temp_s2], var_fs0, var_fs0, var_fs0);
    }

    temp_s1->unk_6C = temp_s2;
    temp_s1->unk_74++;

    return 1;
}

void func_8003A7E4(Gfx **gfxP) {
    struct_800E53B0_b *ptr = &B_800E53B0->b;
    Gfx *gfx;
    s32 temp;

    if (ptr->unk_70 != 0) {
        return;
    }

    gfx = *gfxP;
    temp = ptr->unk_6C;

    gSPPerspNormalize(gfx++, ptr->perspNorm);
    gSPMatrix(gfx++, &ptr->unk_00, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gSPDisplayList(gfx++, RO_800AD098);
    gSPMatrix(gfx++, ptr->unk_60[temp], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(gfx++, ptr->unk_54[temp]);

    *gfxP = gfx;

    ptr->unk_78 += 1;
}

// init?
void *func_8003A89C(void *heap, s32 arg1) {
    D_8008CFE0 = arg1;

    switch (D_8008CFE0) {
        case 0x1:
            heap = func_80039E14(heap);
            break;

        case 0x2:
            heap = func_8003A26C(heap);
            break;
    }

    return heap;
}

// update?
s32 func_8003A8F4(void) {
    s32 var_v1 = 0;

    switch (D_8008CFE0) {
        case 0x1:
            var_v1 = func_80039F74();
            break;

        case 0x2:
            var_v1 = func_8003A618();
            break;
    }

    return var_v1;
}

// draw?
void func_8003A950(Gfx **gfxP) {
    switch (D_8008CFE0) {
        case 0x1:
            func_8003A1B4(gfxP);
            break;

        case 0x2:
            func_8003A7E4(gfxP);
            break;
    }
}

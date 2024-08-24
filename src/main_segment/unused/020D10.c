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

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/unused/020D10", func_8003901C);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/unused/020D10", func_8003901C);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/unused/020D10", func_8003901C);
#endif

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

void func_8003974C(Vtx *vtx);

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/unused/020D10", func_8003974C);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/unused/020D10", func_8003974C);
#endif

#if VERSION_CN
#if 0
void func_8003974C(Vtx *vtx) {
    ? spC;
    ? sp10;
    ? sp14;
    ? sp18;
    ? sp1C;
    ? sp20;
    f32 spE28;
    f32 spE2C;
    f32 spE30;
    f32 spE38;
    f32 spE3C;
    f32 spE40;
    ? *spE48;
    ? *spE4C;
    ? *spE50;
    f32 *spE58;
    f32 *spE5C;
    f32 *spE60;
    f32 *spE64;
    f32 *spE68;
    f32 *spE6C;
    f32 *spE70;
    Vtx *spE74;
    s32 spE78;
    ? *spE7C;
    ? *spE80;
    ? *spE84;
    ? *temp_a0_2;
    ? *var_t6;
    ? *var_t7;
    ? *var_t9;
    Vtx *temp_a1;
    Vtx *temp_a1_2;
    Vtx *temp_a2;
    Vtx *temp_a2_2;
    Vtx *temp_a2_3;
    Vtx *temp_a2_6;
    Vtx *var_t4;
    f32 *temp_v0;
    f32 *var_a0;
    f32 *var_a1;
    f32 *var_a3;
    f32 *var_a3_2;
    f32 *var_fp;
    f32 *var_s4;
    f32 *var_s5;
    f32 *var_s6;
    f32 *var_s7;
    f32 *var_t0;
    f32 *var_t0_2;
    f32 *var_t1;
    f32 *var_t1_2;
    f32 *var_t2;
    f32 *var_t3;
    f32 temp_fa0;
    f32 temp_ft0;
    f32 temp_ft1;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv0_3;
    f32 temp_fv0_4;
    f32 temp_fv1;
    f32 temp_fv1_2;
    f32 var_ft0;
    f32 var_fv1;
    s32 temp_a0;
    s32 temp_t2;
    s32 var_a3_3;
    s32 var_a3_4;
    s32 var_s0;
    s32 var_s0_2;
    s32 var_s0_3;
    s32 var_s0_4;
    s32 var_s1;
    s32 var_s1_2;
    s32 var_s1_3;
    s32 var_s1_4;
    s32 var_s2;
    s32 var_s3;
    s32 var_t0_3;
    s32 var_t0_4;
    s32 var_t1_3;
    s32 var_t1_4;
    s32 var_t5;
    s32 var_v0;
    s32 var_v0_2;
    u8 temp_v1;
    u8 temp_v1_2;
    void *temp_a1_3;
    void *temp_a1_4;
    void *temp_a1_5;
    void *temp_a1_6;
    void *temp_a2_4;
    void *temp_a2_5;
    void *temp_a2_7;

    var_t4 = vtx;
    var_s1 = 0;
    var_s0 = 0;
    do {
        temp_t2 = var_s1 + 1;
        temp_v0 = &sp18 + (var_s1 * 0xB4);
        var_t1 = temp_v0 + 8;
        var_t0 = temp_v0 + 4;
        var_a3 = temp_v0;
loop_2:
        temp_a2 = &var_t4[(temp_t2 * 0x10) + var_s0];
        temp_a0 = (var_s1 * 0x10) + var_s0;
        temp_a1 = &var_t4[temp_a0];
        spE28 = (f32) (temp_a1->v.ob[0] - temp_a2->v.ob[0]);
        temp_ft0 = (f32) (temp_a1->v.ob[1] - temp_a2->v.ob[1]);
        spE2C = temp_ft0;
        temp_a0_2 = &var_t4[temp_a0].unk_10;
        temp_ft1 = (f32) (temp_a1->v.ob[2] - temp_a2->v.ob[2]);
        spE30 = temp_ft1;
        temp_fv0 = (f32) (temp_a0_2->unk_0 - temp_a1->v.ob[0]);
        spE38 = temp_fv0;
        temp_fv1 = (f32) (temp_a0_2->unk_2 - temp_a1->v.ob[1]);
        spE3C = temp_fv1;
        temp_fv0_2 = (f32) (temp_a0_2->unk_4 - temp_a1->v.ob[2]);
        spE40 = temp_fv0_2;
        *var_a3 = (temp_ft0 * temp_fv0_2) - (temp_ft1 * temp_fv1);
        *var_t0 = (temp_ft1 * temp_fv0) - (spE28 * spE40);
        var_s0 += 1;
        var_a3 += 0xC;
        var_t0 += 0xC;
        *var_t1 = (spE28 * spE3C) - (temp_ft0 * spE38);
        var_t1 += 0xC;
        if (var_s0 < 0xF) {
            goto loop_2;
        }
        var_s1 = temp_t2;
        var_s0 = 0;
    } while (var_s1 < 0x14);
    var_s1_2 = 1;
    spE50 = &sp18;
    spE48 = &sp1C;
    var_s3 = 0;
    var_s2 = 0xB4;
    var_t9 = &sp14;
    var_t7 = &sp10;
    var_t6 = &spC;
    spE4C = &sp20;
    do {
        var_s0_2 = 1;
        var_t5 = var_s1_2 * 0x10;
        var_t3 = var_s3 + var_t9 + 0xC;
        var_t1_2 = var_s2 + var_t9 + 0xC;
        var_a3_2 = var_s3 + var_t7 + 0xC;
        var_a0 = var_s2 + var_t7 + 0xC;
        var_s7 = var_s3 + var_t6 + 0xC;
        var_s5 = var_s2 + var_t6 + 0xC;
        var_t2 = var_s3 + spE4C + 0xC;
        var_t0_2 = var_s2 + spE4C + 0xC;
        var_a1 = var_s3 + spE48 + 0xC;
        var_fp = var_s2 + spE48 + 0xC;
        var_s6 = var_s3 + spE50 + 0xC;
        var_s4 = var_s2 + spE50 + 0xC;
loop_6:
        temp_fv0_3 = *var_s4 + *var_s5 + *var_s6 + *var_s7;
        spE28 = temp_fv0_3;
        temp_fv1_2 = *var_fp + *var_a0 + *var_a1 + *var_a3_2;
        spE2C = temp_fv1_2;
        temp_fv0_4 = *var_t0_2 + *var_t1_2 + *var_t2 + *var_t3;
        temp_fa0 = (temp_fv0_3 * temp_fv0_3) + (temp_fv1_2 * temp_fv1_2) + (temp_fv0_4 * temp_fv0_4);
        var_fv1 = sqrtf(temp_fa0);
        spE30 = temp_fv0_4;
        if (var_fv1 != var_fv1) {
            spE58 = var_a0;
            spE5C = var_a1;
            spE60 = var_a3_2;
            spE64 = var_t0_2;
            spE68 = var_t1_2;
            spE6C = var_t2;
            spE70 = var_t3;
            spE74 = var_t4;
            spE78 = var_t5;
            spE7C = var_t6;
            spE80 = var_t7;
            spE84 = var_t9;
            var_fv1 = sqrtf(temp_fa0);
        }
        var_ft0 = var_fv1;
        if (var_ft0 != 0.0f) {
            var_ft0 = 127.0f / var_ft0;
        }
        temp_a2_2 = &var_t4[var_t5 + var_s0_2];
        var_t3 += 0xC;
        var_t2 += 0xC;
        var_t1_2 += 0xC;
        var_t0_2 += 0xC;
        temp_a2_2->v.cn[0] = (u8) (s32) (spE28 * var_ft0);
        var_a3_2 += 0xC;
        var_a1 += 0xC;
        var_a0 += 0xC;
        var_fp += 0xC;
        var_s7 += 0xC;
        temp_a2_2->v.cn[1] = (u8) (s32) (spE2C * var_ft0);
        var_s6 += 0xC;
        var_s5 += 0xC;
        var_s4 += 0xC;
        var_s0_2 += 1;
        temp_a2_2->v.cn[2] = (u8) (s32) (spE30 * var_ft0);
        if (var_s0_2 < 0xF) {
            goto loop_6;
        }
        var_s3 += 0xB4;
        var_s1_2 += 1;
        var_s2 += 0xB4;
    } while (var_s1_2 < 0x14);
    var_s1_3 = 0;
    do {
        var_s0_3 = 0;
loop_14:
        temp_a2_3 = &var_t4[(var_s1_3 * 0x10) + var_s0_3];
        if (var_s1_3 != 0) {
            var_v0 = (var_s1_3 - 1) * 0x10;
        } else {
            var_v0 = 0x10;
        }
        if (var_s0_3 == 0) {
            var_v0_2 = var_v0 + 1;
        } else {
            var_v0_2 = var_v0 - 1 + var_s0_3;
        }
        temp_a1_2 = &var_t4[var_v0_2];
        temp_a2_3->v.cn[0] = temp_a1_2->v.cn[0];
        var_s0_3 += 0xF;
        temp_a2_3->v.cn[1] = temp_a1_2->v.cn[1];
        temp_a2_3->v.cn[2] = temp_a1_2->v.cn[2];
        if (var_s0_3 < 0x10) {
            goto loop_14;
        }
        var_s1_3 += 0x14;
    } while (var_s1_3 < 0x15);
    var_s1_4 = 1;
    var_t1_3 = 0x1E0;
    var_t0_3 = 0x1F0;
    var_a3_3 = 0x110;
    do {
        temp_a2_4 = var_t4 + (var_s1_4 << 8);
        temp_a1_3 = var_t4 + var_a3_3;
        temp_v1 = var_t4->v.cn[var_a3_3];
        var_a3_3 += 0x100;
        temp_a2_4->unk_C = temp_v1;
        var_s1_4 += 1;
        temp_a2_4->unk_D = (u8) temp_a1_3->unk_D;
        temp_a1_4 = var_t4 + var_t1_3;
        var_t1_3 += 0x100;
        temp_a2_4->unk_E = (u8) temp_a1_3->unk_E;
        temp_a2_5 = var_t4 + var_t0_3;
        var_t4->v.cn[var_t0_3] = temp_a1_4->unk_C;
        var_t0_3 += 0x100;
        temp_a2_5->unk_D = (u8) temp_a1_4->unk_D;
        temp_a2_5->unk_E = (u8) temp_a1_4->unk_E;
    } while (var_s1_4 < 0x14);
    var_s0_4 = 1;
    var_t1_4 = 0x1310;
    var_t0_4 = 0x1410;
    var_a3_4 = 0x110;
    do {
        temp_a2_6 = &var_t4[var_s0_4];
        temp_a1_5 = var_t4 + var_a3_4;
        temp_v1_2 = var_t4->v.cn[var_a3_4];
        var_a3_4 += 0x10;
        temp_a2_6->v.cn[0] = temp_v1_2;
        var_s0_4 += 1;
        temp_a2_6->v.cn[1] = temp_a1_5->unk_D;
        temp_a1_6 = var_t4 + var_t1_4;
        var_t1_4 += 0x10;
        temp_a2_6->v.cn[2] = temp_a1_5->unk_E;
        temp_a2_7 = var_t4 + var_t0_4;
        var_t4->v.cn[var_t0_4] = temp_a1_6->unk_C;
        var_t0_4 += 0x10;
        temp_a2_7->unk_D = (u8) temp_a1_6->unk_D;
        temp_a2_7->unk_E = (u8) temp_a1_6->unk_E;
    } while (var_s0_4 < 0xF);
}
#else
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/unused/020D10", func_8003974C);
#endif
#endif

void func_80039BE0(Vtx *vtx, f32 arg1, f32 arg2, f32 arg3) {
    f32 sp18[0x10];
    s32 var_t0;
    s32 var_s0;

    arg2 = 3.141592f / arg2;

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
        temp_fs1 = sinf(var_s2 * (3.141592f / 10));
        temp_fs2 = cosf(var_s2 * (3.141592f / 10));

        for (var_s1 = 0; var_s1 < 0x10; var_s1++) {
            temp_s0 = temp_s3->unk_80[(var_s2 * 0x10) + var_s1];

            temp_fs0_2 = sinf(var_s1 * (3.141592f / 15));
            temp_fv0_2 = cosf(var_s1 * (3.141592f / 15));

            temp_s0[0x04 / 4] = temp_s0[0x10 / 4] = temp_fv0_2;
            temp_s0[0x00 / 4] = temp_s0[0x0C / 4] = -temp_fs1 * temp_fs0_2;
            temp_s0[0x08 / 4] = temp_s0[0x14 / 4] = -temp_fs2 * temp_fs0_2;

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

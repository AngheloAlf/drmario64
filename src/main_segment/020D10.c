#include "020D10.h"

#include "include_asm.h"
#include "macros_defines.h"
#include "unknown_structs.h"
#include "main_segment_variables.h"
#include "buffers.h"
#include "graphic.h"

#define STRUCT_800E53B0_UNK_LEN 3

typedef struct struct_800E53B0 {
    /* 0x00 */ Mtx unk_00;
    /* 0x40 */ u16 perspNorm;
    /* 0x42 */ UNK_TYPE1 unk_42[0x2]; // pad?
    /* 0x44 */ u16 *unk_44;
    /* 0x48 */ UNK_TYPE *unk_48[STRUCT_800E53B0_UNK_LEN];
    /* 0x54 */ Gfx *unk_54[STRUCT_800E53B0_UNK_LEN];
    /* 0x60 */ Mtx *unk_60[STRUCT_800E53B0_UNK_LEN];
    /* 0x6C */ UNK_TYPE unk_6C;
    /* 0x70 */ UNK_TYPE unk_70; // bool?
    /* 0x74 */ u32 unk_74;
    /* 0x78 */ UNK_TYPE unk_78;
    /* 0x7C */ UNK_TYPE1 unk_7C[0x4]; // pad?
} struct_800E53B0;                    // size = 0x80

extern struct_800E53B0 *B_800FC030_cn;

void func_8003C0A4_cn(UNK_TYPE **arg0, void **heap);
void func_8003C168_cn(Gfx **arg0, UNK_TYPE *arg1, u16 *arg2, void **heap);
void func_8003C414_cn(UNK_TYPE *arg0);

void func_8003C978_cn(UNK_TYPE *arg0, f32 arg1, f32 arg2, f32 arg3);

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/020D10", RO_800ACFB0);
#endif

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/020D10", RO_800ACFC8);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/020D10", func_80038EF0);
#endif

#if VERSION_CN
void func_8003BB50_cn(Mtx *mtx, u16 *perspNorm) {
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
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/020D10", func_8003901C);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/020D10", func_8003BCD8_cn);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/020D10", func_800393DC);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/020D10", func_8003C0A4_cn);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/020D10", func_800394A0);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/020D10", func_8003C168_cn);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/020D10", func_8003974C);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/020D10", func_8003C414_cn);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/020D10", func_80039BE0);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/020D10", func_8003C978_cn);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/020D10", func_80039D08);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/020D10", func_8003CAAC_cn);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/020D10", func_80039E14);
#endif

#if VERSION_CN
void *func_80039E14(void *heap) {
    struct_800E53B0 *temp_s1;
    s32 i;

    temp_s1 = ALIGN_PTR(heap);
    B_800FC030_cn = temp_s1;
    heap = (void *)((uintptr_t)temp_s1 + sizeof(struct_800E53B0));

    func_8003BB50_cn(&temp_s1->unk_00, &temp_s1->perspNorm);

    temp_s1->unk_44 = ALIGN_PTR(heap);
    heap = (void *)((uintptr_t)temp_s1->unk_44 + sizeof(u16) * SCREEN_HEIGHT * SCREEN_WIDTH);
    bcopy(gFramebuffers[gCurrentFramebufferIndex ^ 1], temp_s1->unk_44, sizeof(u16) * SCREEN_HEIGHT * SCREEN_WIDTH);

    for (i = 0; i < STRUCT_800E53B0_UNK_LEN; i++) {
        func_8003C0A4_cn(&temp_s1->unk_48[i], &heap);
        func_8003C414_cn(temp_s1->unk_48[i]);
        func_8003C168_cn(&temp_s1->unk_54[i], temp_s1->unk_48[i], temp_s1->unk_44, &heap);

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
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/020D10", func_80039F74);
#endif

#if VERSION_CN
s32 func_80039F74(void) {
    struct_800E53B0 *temp_s2 = B_800FC030_cn;
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

    func_8003C978_cn(temp_s2->unk_48[temp_s3], var_ft0, temp_fs2 * 4.0f + 120.0f, temp_fs2 / 2.0f);

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
#endif

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/020D10", RO_800AD080);
#endif

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/020D10", RO_800AD098);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/020D10", func_8003A1B4);
#endif

extern const Gfx RO_800C4098_cn[];

#if VERSION_CN
void func_8003A1B4(Gfx **gfxP) {
    struct_800E53B0 *ptr = B_800FC030_cn;
    Gfx *gfx;
    s32 temp;

    if (ptr->unk_70 != 0) {
        return;
    }

    gfx = *gfxP;
    temp = ptr->unk_6C;

    gSPDisplayList(gfx++, RO_800C4098_cn);
    gSPPerspNormalize(gfx++, ptr->perspNorm);
    gSPMatrix(gfx++, &ptr->unk_00, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gSPMatrix(gfx++, ptr->unk_60[temp], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(gfx++, ptr->unk_54[temp]);

    *gfxP = gfx;
    ptr->unk_78++;
}
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/020D10", func_8003A26C);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/020D10", func_8003A26C);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/020D10", func_8003A618);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/020D10", func_8003A618);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/020D10", func_8003A7E4);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/020D10", func_8003A7E4);
#endif

#if VERSION_US || VERSION_CN
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
#endif

#if VERSION_US || VERSION_CN
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
#endif

#if VERSION_US || VERSION_CN
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
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/020D10", RO_800C4080_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/020D10", RO_800C4098_cn);
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/020D10", RO_800C4150_cn);
#endif

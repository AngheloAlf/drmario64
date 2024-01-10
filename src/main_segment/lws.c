/**
 * Original filename: lws.c
 */

#include "lws.h"

#include "include_asm.h"
#include "macros_defines.h"
#include "unknown_structs.h"
#include "main_segment_variables.h"

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/lws", lws_anim);
#endif

#if VERSION_CN
#if 0
void makeMatrix(Mtx *, s32, s32, s32, s32, s32, s32);  /* extern */
void matrixConv(Mtx *, Mtx *, s32);                        /* extern */
void matrixMulL(Mtx *, Mtx *, Mtx *);                  /* extern */
extern Mtx AnimProc[0x40]; // guessed size

typedef struct struct_lws_anim_arg2 {
    /* 0x00 */ UNK_TYPE1 unk_00[0x4];
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ UNK_TYPE1 unk_08[0x4];
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 unk_14;
} struct_lws_anim_arg2; // size >= 0x18

typedef struct struct_temp {
    /* 0x0 */ Gfx *unk_0;
    /* 0x4 */ s32 unk_4;
    /* 0x8 */ s32 unk_8;
    /* 0xC */ s32 unk_C;
} struct_temp; 

typedef struct struct_temp_a1 {
    /* 0x00 */ UNK_TYPE unk_00;
    /* 0x04 */ UNK_TYPE unk_04;
    /* 0x08 */ UNK_TYPE2 unk_08;
    /* 0x0A */ UNK_TYPE2 unk_0A;
    /* 0x0C */ UNK_TYPE2 unk_0C;
    /* 0x0E */ UNK_TYPE2 unk_0E;
    /* 0x10 */ UNK_TYPE2 unk_10;
    /* 0x12 */ UNK_TYPE2 unk_12;
    /* 0x14 */ UNK_TYPE2 unk_14;
    /* 0x16 */ UNK_TYPE2 unk_16;
    /* 0x18 */ UNK_TYPE unk_18;
} struct_temp_a1;

s32 lws_anim(Gfx **gfxP, Mtx *mtx, struct_lws_anim_arg2 *arg2, s32 arg3, void *arg4) {
    Mtx sp28;
    Mtx sp68;
    Mtx spA8;
    Gfx *spE8;
    s32 spEC;
    s32 spF0;
    f32 spF8;
    f32 spFC;
    s32 sp100;
    s32 sp10C;
    f32 sp110;
    Mtx *var_a1_2;
    f32 temp_fs0;
    f32 var_fs1;
    f32 var_fs2;
    f32 var_fs3;
    f32 var_fs4;
    f32 var_fs5;
    f32 var_ft5;
    struct_temp_a1 *var_a0;
    struct_temp_a1 *var_a1;
    struct_temp_a1 *var_a2;
    s32 var_a3;
    // s32 var_fp; // var_fp = arg3;
    struct_temp *temp_s5;

    spE8 = *gfxP;

    if (arg3 >= arg2->unk_04) {
        spF0 = 1;
        arg3 = arg2->unk_04 - 1;
    } else {
        spF0 = 0;
    }

    sp100 = 0xFFFFFF;
    sp10C = 0;
    for (spEC = 0; spEC < arg2->unk_0C; spEC++) {
        temp_s5 = (arg2->unk_10 & sp100) + arg4 + sp10C;

        var_a2 = (arg2->unk_14 & sp100) + arg4 + (temp_s5->unk_C * 0x1C);

        var_a1 = var_a2;
        var_a0 = var_a2;

        for (var_a3 = 1; var_a3 < temp_s5->unk_8; var_a3++) {
            var_a2 = var_a2 + 1;
            var_a1 = var_a0;
            if (arg3 < var_a2->unk_00) {
                goto block_11;
            }

            var_a0 = var_a1 + 1;
        }

        if (arg3 >= var_a2->unk_00) {
            var_ft5 = 0.0f;
            var_a1 = var_a2;
        } else {
block_11:
            if (var_a1 != var_a2) {
                var_ft5 = (arg3 - var_a1->unk_00);
            } else {
                var_ft5 = 0.0f;
            }
        }
        var_fs3 = var_a1->unk_08;
        var_fs5 = var_a1->unk_0A;
        var_fs4 = var_a1->unk_0C;
        temp_fs0 = var_a1->unk_0E;
        spF8 = var_a1->unk_10;
        spFC = var_a1->unk_12;
        sp110 = var_a1->unk_14;
        var_fs2 = var_a1->unk_16;
        var_fs1 = var_a1->unk_18;
        if (var_ft5 > 0.0f) {
            f32 temp_ft5;

            temp_ft5 = var_ft5 / (var_a2->unk_00 - var_a1->unk_00);

            var_fs3 += (var_a2->unk_08 - var_fs3) * temp_ft5;
            var_fs5 += (var_a2->unk_0A - var_fs5) * temp_ft5;
            temp_fs0 += (var_a2->unk_0E - temp_fs0) * temp_ft5;
            var_fs4 += (var_a2->unk_0C - var_fs4) * temp_ft5;
            spF8 += (var_a2->unk_10 - spF8) * temp_ft5;
            var_fs2 += (var_a2->unk_16 - var_fs2) * temp_ft5;
            spFC += (var_a2->unk_12 - spFC) * temp_ft5;
            var_fs1 += (var_a2->unk_18 - var_fs1) * temp_ft5;
            sp110 += (var_a2->unk_14 - sp110) * temp_ft5;
        }

        makeScaleMatrix(&sp68, 0x8000U);
        sp68.m[0][0] = (s32) ((sp110 * 8.0) + 0.5);
        sp68.m[1][1] = (s32) ((var_fs2 * 8.0) + 0.5);
        sp68.m[2][2] = (s32) ((var_fs1 * 8.0) + 0.5);
        makeMatrix(&spA8, angleF2S(temp_fs0 * 0.0625), angleF2S(spF8 * 0.0625), angleF2S(spFC * 0.0625), (s32) (var_fs3 * 4096.0), (s32) (var_fs5 * 4096.0), (s32) (var_fs4 * 4096.0));
        matrixMulL(&sp68, &spA8, &sp28);

        if (temp_s5->unk_4 == -1) {
            var_a1_2 = mtx;
        } else {
            var_a1_2 = &AnimProc[temp_s5->unk_4];
        }
        matrixMulL(&sp28, var_a1_2, &AnimProc[spEC]);

        if (temp_s5->unk_0 != 0) {
            matrixConv(&AnimProc[spEC], pObjectMtx, 0);
            gSPMatrix(spE8++, pObjectMtx++, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(spE8++, temp_s5->unk_0);
        }

        sp10C += 0x18;
    }

    *gfxP = spE8;
    return spF0;
}
#else
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/lws", lws_anim);
#endif
#endif

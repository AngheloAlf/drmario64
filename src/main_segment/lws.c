/**
 * Original filename: lws.c
 */

#include "lws.h"

#include "macros_defines.h"
#include "unknown_structs.h"
#include "main_segment_variables.h"

#include "calc.h"
#include "main_story.h"
#include "066840.h"

static Mtx AnimProc[0x40];

s32 lws_anim(Gfx **gfxP, Mtx *mtx, Lws *arg2, s32 arg3, void *arg4) {
    Gfx *gfx = *gfxP;
    s32 i;
    s32 ret;

    if (arg3 >= arg2->unk_04) {
        ret = 1;
        arg3 = arg2->unk_04 - 1;
    } else {
        ret = 0;
    }

    for (i = 0; i < arg2->count; i++) {
        s32 j;
        Mtx sp28;
        Mtx sp68;
        Mtx spA8;
        f32 var_fs3;
        f32 var_fs5;
        f32 var_fs4;
        f32 spF4;
        f32 spF8;
        f32 spFC;
        f32 sp110;
        f32 var_fs2;
        f32 var_fs1;
        f32 var_ft5;
        s16 temp_s0;
        s16 temp_s1;
        s16 a3;
        Lws_unk_14 *var_a1;
        Lws_unk_14 *var_a2;
        Lws_unk_14 *temp;
        Lws_unk_10 *temp_s5;
        s32 a4;
        s32 a5;
        s32 a6;

        temp_s5 = RELOCATE_SEGMENTED(arg2->unk_10, arg4);
        temp_s5 = &temp_s5[i];

        temp = RELOCATE_SEGMENTED(arg2->unk_14, arg4);
        temp = &temp[temp_s5->unk_0C];

        var_a1 = var_a2 = temp;

        for (j = 1; j < temp_s5->unk_08; j++) {
            var_a1 = &temp[j - 1];
            var_a2 = &temp[j];
            if (var_a2->unk_00 > arg3) {
                break;
            }
        }

        if (arg3 >= var_a2->unk_00) {
            var_ft5 = 0.0f;
            var_a1 = var_a2;
        } else if (var_a1 == var_a2) {
            var_ft5 = 0.0f;
        } else {
            var_ft5 = arg3 - var_a1->unk_00;
        }

        var_fs3 = var_a1->unk_08;
        var_fs5 = var_a1->unk_0A;
        var_fs4 = var_a1->unk_0C;
        spF4 = var_a1->unk_0E;
        spF8 = var_a1->unk_10;
        spFC = var_a1->unk_12;
        sp110 = var_a1->unk_14;
        var_fs2 = var_a1->unk_16;
        var_fs1 = var_a1->unk_18;
        if (var_ft5 > 0.0f) {
            var_ft5 /= (var_a2->unk_00 - var_a1->unk_00);

            var_fs3 += (var_a2->unk_08 - var_fs3) * var_ft5;
            var_fs5 += (var_a2->unk_0A - var_fs5) * var_ft5;
            var_fs4 += (var_a2->unk_0C - var_fs4) * var_ft5;
            spF4 += (var_a2->unk_0E - spF4) * var_ft5;
            spF8 += (var_a2->unk_10 - spF8) * var_ft5;
            spFC += (var_a2->unk_12 - spFC) * var_ft5;
            sp110 += (var_a2->unk_14 - sp110) * var_ft5;
            var_fs2 += (var_a2->unk_16 - var_fs2) * var_ft5;
            var_fs1 += (var_a2->unk_18 - var_fs1) * var_ft5;
        }

        makeScaleMatrix(&sp68, 0x8000);

        sp68.m[0][0] = sp110 * 8.0 + 0.5;
        sp68.m[1][1] = var_fs2 * 8.0 + 0.5;
        sp68.m[2][2] = var_fs1 * 8.0 + 0.5;

        a4 = var_fs3 * 4096.0;
        a5 = var_fs5 * 4096.0;
        a6 = var_fs4 * 4096.0;

        temp_s1 = angleF2S(spF4 / 16.0);
        temp_s0 = angleF2S(spF8 / 16.0);
        a3 = angleF2S(spFC / 16.0);

        makeMatrix(&spA8, temp_s1, temp_s0, a3, a4, a5, a6);
        matrixMulL(&sp68, &spA8, &sp28);

        if (temp_s5->unk_04 == -1) {
            matrixMulL(&sp28, mtx, &AnimProc[i]);
        } else {
            matrixMulL(&sp28, &AnimProc[temp_s5->unk_04], &AnimProc[i]);
        }

        if (temp_s5->unk_00 != NULL) {
            matrixConv(&AnimProc[i], pObjectMtx, 0);

            gSPMatrix(gfx++, pObjectMtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            pObjectMtx++;

            gSPDisplayList(gfx++, temp_s5->unk_00);
        }
    }

    *gfxP = gfx;

    return ret;
}

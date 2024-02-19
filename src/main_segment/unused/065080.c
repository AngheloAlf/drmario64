#include "065080.h"

#include "include_asm.h"
#include "macros_defines.h"
#include "unknown_structs.h"
#include "unk.h"

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/unused/065080", func_8007D260);
#endif

#if VERSION_CN
void func_80088260_cn(f32 arg0[3], Mtx *arg1, f32 arg2[3]) {
    f32 sp18[4][4];
    f32 sp58[4];
    f32 sp68[4];
    s32 i;
    s32 j;

    guMtxL2F(sp18, arg1);

    sp68[0] = arg2[0];
    sp68[1] = arg2[1];
    sp68[2] = arg2[2];
    sp68[3] = 1.0f;

    for (i = 0; i < 4; i++) {
        sp58[i] = 0.0f;

        for (j = 0; j < 4; j++) {
            sp58[i] += sp18[j][i] * sp68[j];
        }
    }

    arg0[0] = sp58[0] / sp58[3];
    arg0[1] = sp58[1] / sp58[3];
    arg0[2] = sp58[2] / sp58[3];
}
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/unused/065080", func_8007D348);
#endif

#if VERSION_CN
void func_80088350_cn(f32 arg0[3], Mtx *arg1, f32 arg2[3]) {
    f32 sp18[4][4];
    f32 sp58[4];
    f32 sp68[4];
    s32 i;
    s32 j;

    guMtxL2F(sp18, arg1);

    sp68[0] = arg2[0];
    sp68[1] = arg2[1];
    sp68[2] = arg2[2];
    sp68[3] = 0.0f;

    for (i = 0; i < 4; i++) {
        sp58[i] = 0.0f;

        for (j = 0; j < 4; j++) {
            sp58[i] += sp18[j][i] * sp68[j];
        }
    }

    arg0[0] = sp58[0];
    arg0[1] = sp58[1];
    arg0[2] = sp58[2];
}
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/unused/065080", func_8007D410);
#endif

#if VERSION_CN
void func_80088428_cn(f32 arg0[3], f32 arg1[4][4], f32 arg2[3]) {
    f32 sp58[4];
    f32 sp68[4];
    s32 i;
    s32 j;

    sp68[0] = arg2[0];
    sp68[1] = arg2[1];
    sp68[2] = arg2[2];
    sp68[3] = 1.0f;

    for (i = 0; i < 4; i++) {
        sp58[i] = 0.0f;

        for (j = 0; j < 4; j++) {
            sp58[i] += arg1[j][i] * sp68[j];
        }
    }

    arg0[0] = sp58[0] / sp58[3];
    arg0[1] = sp58[1] / sp58[3];
    arg0[2] = sp58[2] / sp58[3];
}
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/unused/065080", func_8007D4CC);
#endif

#if VERSION_CN
void func_800884E0_cn(f32 arg0[3], f32 arg1[4][4], f32 arg2[3]) {
    f32 sp58[4];
    f32 sp68[4];
    s32 i;
    s32 j;

    sp68[0] = arg2[0];
    sp68[1] = arg2[1];
    sp68[2] = arg2[2];
    sp68[3] = 0.0f;

    for (i = 0; i < 4; i++) {
        sp58[i] = 0.0f;

        for (j = 0; j < 4; j++) {
            sp58[i] += arg1[j][i] * sp68[j];
        }
    }

    arg0[0] = sp58[0];
    arg0[1] = sp58[1];
    arg0[2] = sp58[2];
}
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/unused/065080", func_8007D568);
#endif

#if VERSION_CN
void func_80088580_cn(Mtx *arg0, Mtx *arg1, Mtx *arg2) {
    f32 sp18[4][4];
    f32 sp58[4][4];
    f32 sp98[4][4];
    s32 i;
    s32 j;

    guMtxL2F(sp58, arg1);
    guMtxL2F(sp98, arg2);

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            sp18[i][j] = sp58[i][0] * sp98[0][j] + sp58[i][1] * sp98[1][j] + sp58[i][2] * sp98[2][j] + sp58[i][3] * sp98[3][j];
        }
    }

    guMtxF2L(sp18, arg0);
}
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/unused/065080", func_8007D644);
#endif

#if VERSION_CN
void func_800886C4_cn(f32 arg0[4][4], f32 arg1[4][4], f32 arg2[4][4]) {
    f32 sp8[4][4];
    s32 i;
    s32 j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            sp8[i][j] = arg1[i][0] * arg2[0][j] + arg1[i][1] * arg2[1][j] + arg1[i][2] * arg2[2][j] + arg1[i][3] * arg2[3][j];
        }
    }

    arg0[0][0] = sp8[0][0];
    arg0[0][1] = sp8[0][1];
    arg0[0][2] = sp8[0][2];
    arg0[0][3] = sp8[0][3];

    arg0[1][0] = sp8[1][0];
    arg0[1][1] = sp8[1][1];
    arg0[1][2] = sp8[1][2];
    arg0[1][3] = sp8[1][3];

    arg0[2][0] = sp8[2][0];
    arg0[2][1] = sp8[2][1];
    arg0[2][2] = sp8[2][2];
    arg0[2][3] = sp8[2][3];

    arg0[3][0] = sp8[3][0];
    arg0[3][1] = sp8[3][1];
    arg0[3][2] = sp8[3][2];
    arg0[3][3] = sp8[3][3];
}
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/unused/065080", func_8007D74C);
#endif

#if VERSION_CN
void func_80088830_cn(f32 arg0[3][3], s32 arg1, s32 arg2, s32 arg3) {
    f32 temp_fv1;
    s32 i;

    if (arg1 != 0) {
        if (arg2 == 0) {
            for (i = 0; i < 3; i++) {
                temp_fv1 = arg0[0][i];
                arg0[0][i] = arg0[arg1][i];
                arg0[arg1][i] = temp_fv1;
            }
            arg2 = arg1;
        } else {
            for (i = 0; i < 3; i++) {
                temp_fv1 = arg0[arg3][i];
                arg0[arg3][i] = arg0[arg1][i];
                arg0[arg1][i] = temp_fv1;
            }
            arg3 = arg1;
        }
    }

    if (arg2 != 1) {
        for (i = 0; i < 3; i++) {
            temp_fv1 = arg0[arg3][i];
            arg0[arg3][i] = arg0[arg2][i];
            arg0[arg2][i] = temp_fv1;
        }
    }
}
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/unused/065080", func_8007D83C);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/unused/065080", func_80088920_cn);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/unused/065080", func_8007DB78);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/unused/065080", func_80088C48_cn);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/unused/065080", func_8007DD70);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/unused/065080", func_80088E30_cn);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/unused/065080", func_8007DF64);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/unused/065080", func_80089014_cn);
#endif

#include "065080.h"

#include "macros_defines.h"

void func_8007D260(f32 arg0[3], Mtx *arg1, f32 arg2[3]) {
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

void mult_func_8007D348(f32 arg0[3], Mtx *arg1, f32 arg2[3]) {
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

void mult_func_8007D410(f32 arg0[3], f32 arg1[4][4], f32 arg2[3]) {
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

void mult_func_8007D4CC(f32 arg0[3], f32 arg1[4][4], f32 arg2[3]) {
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

void mult_func_8007D568(Mtx *arg0, Mtx *arg1, Mtx *arg2) {
    f32 sp18[4][4];
    f32 sp58[4][4];
    f32 sp98[4][4];
    s32 i;
    s32 j;

    guMtxL2F(sp58, arg1);
    guMtxL2F(sp98, arg2);

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            sp18[i][j] =
                sp58[i][0] * sp98[0][j] + sp58[i][1] * sp98[1][j] + sp58[i][2] * sp98[2][j] + sp58[i][3] * sp98[3][j];
        }
    }

    guMtxF2L(sp18, arg0);
}

void mult_func_8007D644(f32 arg0[4][4], f32 arg1[4][4], f32 arg2[4][4]) {
    f32 sp8[4][4];
    s32 i;
    s32 j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            sp8[i][j] =
                arg1[i][0] * arg2[0][j] + arg1[i][1] * arg2[1][j] + arg1[i][2] * arg2[2][j] + arg1[i][3] * arg2[3][j];
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

void func_8007D74C(f32 arg0[3][3], s32 arg1, s32 arg2, s32 arg3) {
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

bool func_8007D83C(f32 arg0[3][3], f32 arg1[3][3], s32 arg2) {
    f32 temp_ft1;
    f32 var_fv0;
    f32 var_fv1;
    s32 var_a0;
    s32 var_a2;
    s32 var_a3;
    s32 temp;
    s32 var_t1;

    if (arg2 == 0) {
        var_a3 = 1;
        var_a0 = 2;
    } else if (arg2 == 1) {
        var_a3 = 0;
        var_a0 = 2;
    } else {
        var_a3 = 0;
        var_a0 = 1;
    }

    var_fv1 = (arg0[var_a3][1] < 0.0f) ? -arg0[var_a3][1] : arg0[var_a3][1];
    var_fv0 = (arg0[var_a0][1] < 0.0f) ? -arg0[var_a0][1] : arg0[var_a0][1];

    if (var_fv1 > var_fv0) {
        var_a2 = var_a3;
    } else {
        var_a2 = var_a0;
    }

    temp = (var_a2 == var_a3) ? var_a0 : var_a3;

    if ((arg0[var_a2][1] < DOUBLE_LITERAL(1.0 / 100000000)) && (arg0[var_a2][1] > -DOUBLE_LITERAL(1.0 / 100000000))) {
        return false;
    }

    temp_ft1 = DOUBLE_LITERAL(1) / arg0[var_a2][1];
    arg0[var_a2][1] = 1.0f;
    arg0[var_a2][2] *= temp_ft1;
    arg1[var_a2][var_a2] = temp_ft1;
    arg1[var_a2][arg2] *= temp_ft1;

    for (var_t1 = 0; var_t1 < 3; var_t1++) {
        if (var_t1 == var_a2) {
            continue;
        }
        temp_ft1 = -arg0[var_t1][1];
        arg0[var_t1][1] = 0.0f;
        arg0[var_t1][2] += temp_ft1 * arg0[var_a2][2];
        arg1[var_t1][var_a2] = temp_ft1 * arg1[var_a2][var_a2];
        arg1[var_t1][arg2] += temp_ft1 * arg1[var_a2][arg2];
    }

    if ((arg0[temp][2] < DOUBLE_LITERAL(1.0 / 100000000)) && (arg0[temp][2] > -DOUBLE_LITERAL(1.0 / 100000000))) {
        return false;
    }

    temp_ft1 = DOUBLE_LITERAL(1) / arg0[temp][2];
    arg0[temp][2] = 1.0f;
    arg1[temp][temp] = temp_ft1;
    arg1[temp][arg2] *= temp_ft1;
    arg1[temp][var_a2] *= temp_ft1;

    for (var_t1 = 0; var_t1 < 3; var_t1++) {
        if (var_t1 == temp) {
            continue;
        }
        temp_ft1 = -arg0[var_t1][2];
        arg0[var_t1][2] = 0.0f;
        arg1[var_t1][arg2] += temp_ft1 * arg1[temp][arg2];
        arg1[var_t1][var_a2] += temp_ft1 * arg1[temp][var_a2];
        arg1[var_t1][temp] += temp_ft1 * arg1[temp][temp];
    }

    func_8007D74C(arg1, arg2, var_a2, temp);
    return true;
}

bool func_8007DB78(f32 arg0[3][3], f32 arg1[3][3]) {
    f32 temp_ft1;
    f32 var_ft0;
    f32 var_fv1;
    f32 var_fv0;
    s32 var_a2;
    s32 i;

    arg1[0][0] = arg1[1][1] = arg1[2][2] = 1.0f;
    arg1[0][1] = arg1[0][2] = arg1[1][0] = arg1[1][2] = arg1[2][0] = arg1[2][1] = 0.0f;

    var_ft0 = (arg0[0][0] < 0.0f) ? -arg0[0][0] : arg0[0][0];
    var_fv1 = (arg0[1][0] < 0.0f) ? -arg0[1][0] : arg0[1][0];
    var_fv0 = (arg0[2][0] < 0.0f) ? -arg0[2][0] : arg0[2][0];

    if (var_fv1 < var_ft0) {
        if (var_fv0 < var_ft0) {
            var_a2 = 0;
        } else {
            var_a2 = 2;
        }
    } else {
        if (var_fv0 < var_fv1) {
            var_a2 = 1;
        } else {
            var_a2 = 2;
        }
    }

    if ((arg0[var_a2][0] < DOUBLE_LITERAL(1.0 / 100000000)) && (arg0[var_a2][0] > -DOUBLE_LITERAL(1.0 / 100000000))) {
        return 0;
    }

    temp_ft1 = DOUBLE_LITERAL(1) / arg0[var_a2][0];
    arg0[var_a2][0] = 1.0f;
    arg0[var_a2][1] *= temp_ft1;
    arg0[var_a2][2] *= temp_ft1;
    arg1[var_a2][var_a2] = temp_ft1;

    for (i = 0; i < 3; i++) {
        if (i == var_a2) {
            continue;
        }

        temp_ft1 = -arg0[i][0];
        arg0[i][0] = 0.0f;
        arg0[i][1] += temp_ft1 * arg0[var_a2][1];
        arg0[i][2] += temp_ft1 * arg0[var_a2][2];
        arg1[i][var_a2] = temp_ft1 * arg1[var_a2][var_a2];
    }

    if (!func_8007D83C(arg0, arg1, var_a2)) {
        return false;
    }
    return true;
}

bool func_8007DD70(f32 arg0[4][4], f32 arg1[4], f32 *arg2, s32 *arg3) {
    f32 temp_fv1;
    f32 var_ft0;
    f32 var_fv0;
    s32 i;
    s32 var_t1;

    *arg3 = -1;
    var_fv0 = arg0[3][3] >= 0.0f ? arg0[3][3] : -arg0[3][3];

    if (var_fv0 < DOUBLE_LITERAL(1.0 / 100000000)) {
        var_ft0 = 0.0f;
        for (i = 0; i < 4; i++) {
            if (var_ft0 < arg0[i][3]) {
                *arg3 = i;
                var_ft0 = arg0[i][3];
            } else if (arg0[i][3] < -var_ft0) {
                *arg3 = i;
                var_ft0 = -arg0[i][3];
            }
        }

        if (*arg3 < 0) {
            return false;
        }

        for (var_t1 = 0; var_t1 < 4; var_t1++) {
            temp_fv1 = arg0[3][var_t1];
            arg0[3][var_t1] = arg0[*arg3][var_t1];
            arg0[*arg3][var_t1] = temp_fv1;
        }
    }

    arg1[0] = -arg0[0][3];
    arg1[1] = -arg0[1][3];
    arg1[2] = -arg0[2][3];
    *arg2 = DOUBLE_LITERAL(1) / arg0[3][3];

    arg0[0][3] = arg0[1][3] = arg0[2][3] = 0.0f;
    arg0[3][3] = 1.0f;

    arg0[3][0] *= *arg2;
    arg0[3][1] *= *arg2;
    arg0[3][2] *= *arg2;

    for (i = 0; i < 3; i++) {
        arg0[0][i] += arg1[0] * arg0[3][i];
        arg0[1][i] += arg1[1] * arg0[3][i];
        arg0[2][i] += arg1[2] * arg0[3][i];
    }

    return true;
}

bool func_8007DF64(f32 arg0[4][4], f32 arg1[4][4]) {
    f32 sp18[4][4];
    f32 sp58[3][3];
    f32 sp80[3][3];
    f32 spA8[4];
    f32 spB8[3];
    f32 spC8;
    s32 spCC;
    f32 temp_fv1_2;
    s32 var_s2;
    s32 i;
    s32 j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            sp18[i][j] = arg1[i][j];
            arg0[i][j] = 0.0f;
        }
    }

    arg0[0][0] = 1.0f;
    arg0[1][1] = 1.0f;
    arg0[2][2] = 1.0f;
    arg0[3][3] = 1.0f;

    var_s2 = 0;
    if ((sp18[0][3] == DOUBLE_LITERAL(0)) && (sp18[1][3] == DOUBLE_LITERAL(0)) && (sp18[2][3] == DOUBLE_LITERAL(0)) &&
        (sp18[3][3] == DOUBLE_LITERAL(1))) {
        var_s2 = 1;
    }

    if (!var_s2 && !func_8007DD70(sp18, spA8, &spC8, &spCC)) {
        return false;
    }

    spB8[0] = sp18[3][0];
    spB8[1] = sp18[3][1];
    spB8[2] = sp18[3][2];

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            sp58[i][j] = sp18[i][j];
        }
    }

    if (!func_8007DB78(sp58, sp80)) {
        return false;
    }

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            arg0[i][j] = sp80[i][j];
        }
    }

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            arg0[3][i] -= spB8[j] * sp80[j][i];
        }
    }

    if (var_s2 == 0) {
        for (i = 0; i < 4; i++) {
            arg0[i][3] += spA8[0] * arg0[i][0] + spA8[1] * arg0[i][1] + spA8[2] * arg0[i][2];
            arg0[i][3] *= spC8;
        }

        if (spCC >= 0) {
            for (i = 0; i < 4; i++) {
                temp_fv1_2 = arg0[i][3];
                arg0[i][3] = arg0[i][spCC];
                arg0[i][spCC] = temp_fv1_2;
            }
        }
    }
    return true;
}

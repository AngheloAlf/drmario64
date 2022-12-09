#include "ultra64.h"
#include "include_asm.h"
#include "macros_defines.h"
#include "unknown_structs.h"
#include "unk.h"

#if 0
void func_8007EA20(vs32 *arg0, s32 arg1) {
    s32 temp;

    do {
        temp = *arg0;
        temp -= arg1;
    } while (temp != 0);
    //return temp;
}
#else
INCLUDE_ASM("asm/nonmatchings/main_segment/054DD0", func_8007EA20);
#endif

#if 0
s32 func_8007EA38(s32 arg0) {
    return sqrtf(arg0);
}
#else
INCLUDE_ASM("asm/nonmatchings/main_segment/054DD0", func_8007EA38);
#endif

INCLUDE_ASM("asm/nonmatchings/main_segment/054DD0", func_8007EA58);

INCLUDE_ASM("asm/nonmatchings/main_segment/054DD0", func_8007EAEC);

INCLUDE_ASM("asm/nonmatchings/main_segment/054DD0", func_8007EC54);

INCLUDE_ASM("asm/nonmatchings/main_segment/054DD0", func_8007EC98);

INCLUDE_ASM("asm/nonmatchings/main_segment/054DD0", func_8007EE18);

/**
 * Original name: makeTransrateMatrix
 */
void makeTransrateMatrix(Mtx *mtx, u32 x, u32 y, u32 z) {
    mtx->m[0][0] = 0x8000;
    mtx->m[0][1] = 0;
    mtx->m[0][2] = 0;
    mtx->m[0][3] = 0;
    mtx->m[1][0] = 0;
    mtx->m[1][1] = 0x8000;
    mtx->m[1][2] = 0;
    mtx->m[1][3] = 0;
    mtx->m[2][0] = 0;
    mtx->m[2][1] = 0;
    mtx->m[2][2] = 0x8000;
    mtx->m[2][3] = 0;
    mtx->m[3][0] = x;
    mtx->m[3][1] = y;
    mtx->m[3][2] = z;
    mtx->m[3][3] = 0x8000;
}

/**
 * Original name: makeScaleMatrix
 */
void makeScaleMatrix(Mtx *mtx, u32 scale) {
    mtx->m[0][0] = scale;
    mtx->m[0][1] = 0;
    mtx->m[0][2] = 0;
    mtx->m[0][3] = 0;
    mtx->m[1][0] = 0;
    mtx->m[1][1] = scale;
    mtx->m[1][2] = 0;
    mtx->m[1][3] = 0;
    mtx->m[2][0] = 0;
    mtx->m[2][1] = 0;
    mtx->m[2][2] = scale;
    mtx->m[2][3] = 0;
    mtx->m[3][0] = 0;
    mtx->m[3][1] = 0;
    mtx->m[3][2] = 0;
    mtx->m[3][3] = 0x8000;
}

INCLUDE_ASM("asm/nonmatchings/main_segment/054DD0", func_8007F094);

INCLUDE_ASM("asm/nonmatchings/main_segment/054DD0", func_8007F420);

INCLUDE_ASM("asm/nonmatchings/main_segment/054DD0", func_8007F720);

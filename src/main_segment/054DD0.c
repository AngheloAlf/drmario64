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

void func_8007F004(struct_8007F004_arg0 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    arg0->unk_00 = 0x8000;
    arg0->unk_04 = 0;
    arg0->unk_08 = 0;
    arg0->unk_0C = 0;
    arg0->unk_10 = 0;
    arg0->unk_14 = 0x8000;
    arg0->unk_18 = 0;
    arg0->unk_1C = 0;
    arg0->unk_20 = 0;
    arg0->unk_24 = 0;
    arg0->unk_28 = 0x8000;
    arg0->unk_2C = 0;
    arg0->unk_30 = arg1;
    arg0->unk_34 = arg2;
    arg0->unk_38 = arg3;
    arg0->unk_3C = 0x8000;
}

void func_8007F04C(struct_8007F04C_arg0 *arg0, s32 arg1) {
    arg0->unk_00 = arg1;
    arg0->unk_04 = 0;
    arg0->unk_08 = 0;
    arg0->unk_0C = 0;
    arg0->unk_10 = 0;
    arg0->unk_14 = arg1;
    arg0->unk_18 = 0;
    arg0->unk_1C = 0;
    arg0->unk_20 = 0;
    arg0->unk_24 = 0;
    arg0->unk_28 = arg1;
    arg0->unk_2C = 0;
    arg0->unk_30 = 0;
    arg0->unk_34 = 0;
    arg0->unk_38 = 0;
    arg0->unk_3C = 0x8000;
}

INCLUDE_ASM("asm/nonmatchings/main_segment/054DD0", func_8007F094);

INCLUDE_ASM("asm/nonmatchings/main_segment/054DD0", func_8007F420);

INCLUDE_ASM("asm/nonmatchings/main_segment/054DD0", func_8007F720);

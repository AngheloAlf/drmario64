#include "ultra64.h"
#include "include_asm.h"
#include "macros_defines.h"
#include "unknown_structs.h"
#include "boot_functions.h"
#include "boot_variables.h"
#include "main_segment_functions.h"
#include "main_segment_variables.h"

void func_80071EF0(struct_800F4890_unk_034 *arg0, s32 arg1, s32 arg2) {
    arg0->unk_00 = arg1;
    arg0->unk_04 = arg2;
    arg0->messageWnd.unk_28 = arg1 + 8;
    arg0->messageWnd.unk_2C = arg2 + 8;
}

void func_80071F0C(void) {
}

void func_80071F14(struct_800F4890_unk_034 *arg0, UNK_PTR *arg1) {
    arg0->unk_08 = 0;
    arg0->unk_0C = -0.0625f;
    msgWnd_init(&arg0->messageWnd, arg1, 0xD, 4, 0x20, 0x20);
    arg0->messageWnd.unk_30 = 0xA;
    arg0->messageWnd.unk_34 = 0xC;
    arg0->messageWnd.unk_3C = 5;
    arg0->messageWnd.unk_48 = 0xD;
    arg0->messageWnd.unk_54 = 0.16666667f;
    func_80071EF0(arg0, 0x20, 0x20);
}

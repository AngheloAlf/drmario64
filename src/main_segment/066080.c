#include "066080.h"

#include "include_asm.h"
#include "macros_defines.h"
#include "unknown_structs.h"
#include "main_segment_variables.h"

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/066080", func_8007E260);
#endif

#if VERSION_CN
void func_8007E260(struct_8007E260_arg0 *arg0, struct_8007E260_arg1 *arg1, struct_8007E260_arg2 *arg2) {
    f32 sp8[3];

    sp8[0] = (arg1->unk_4 * arg2->unk_8) - (arg1->unk_8 * arg2->unk_4);
    sp8[1] = (arg1->unk_8 * arg2->unk_0) - (arg1->unk_0 * arg2->unk_8);
    sp8[2] = (arg1->unk_0 * arg2->unk_4) - (arg1->unk_4 * arg2->unk_0);
    arg0->unk_0 = sp8[0];
    arg0->unk_4 = sp8[1];
    arg0->unk_8 = sp8[2];
}
#endif

#include "ultra64.h"
#include "include_asm.h"
#include "macros_defines.h"
#include "unknown_structs.h"
#include "main_segment_functions.h"
#include "main_segment_variables.h"


#ifdef NON_MATCHING
enum_800EBCF0 func_8002DB20(void) {
    enum_800EBCF0 ret = ENUM_800EBCF0_3;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(B_80123700); i++) {
        B_80123700[i].unk_026 = 0xA;
        B_80123700[i].unk_02C = 1;
        B_80123700[i].unk_090 = i;
        B_80123700[i].unk_04B = i;
        B_80123700[i].unk_04C = 0;
        B_80123700[i].unk_04D = i;
        B_80123700[i].unk_04E = 1;
        B_80123700[i].unk_16C = 1;
    }

    B_800FAE79 = 8;
    B_800FAE78 = 8;

    switch (func_80038824()) {
        case 0x5:
            ret = ENUM_800EBCF0_10;
            break;

        case 0x2:
            func_80038878(0, 0);
            //ret = ENUM_800EBCF0_3;
            break;

        default:
            //ret = ENUM_800EBCF0_3;
            break;
    }

    return ret;
}
#else
INCLUDE_ASM("asm/nonmatchings/main_segment/003ED0", func_8002DB20);
#endif

INCLUDE_ASM("asm/nonmatchings/main_segment/003ED0", func_8002DC10);

INCLUDE_RODATA("asm/nonmatchings/main_segment/003ED0", D_800ACE1C);

INCLUDE_RODATA("asm/nonmatchings/main_segment/003ED0", D_800ACE28);

INCLUDE_RODATA("asm/nonmatchings/main_segment/003ED0", D_800ACE2C);

INCLUDE_RODATA("asm/nonmatchings/main_segment/003ED0", D_800ACE4C);

INCLUDE_RODATA("asm/nonmatchings/main_segment/003ED0", D_800ACE5C);

INCLUDE_RODATA("asm/nonmatchings/main_segment/003ED0", D_800ACE70);

INCLUDE_RODATA("asm/nonmatchings/main_segment/003ED0", D_800ACE78);

INCLUDE_RODATA("asm/nonmatchings/main_segment/003ED0", D_800ACE84);

INCLUDE_ASM("asm/nonmatchings/main_segment/003ED0", func_8002E230);

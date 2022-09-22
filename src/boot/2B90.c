#include "ultra64.h"
#include "include_asm.h"
#include "boot_functions.h"
#include "boot_variables.h"

// libultra?
extern UNK_TYPE B_8001D7F8;
extern UNK_TYPE B_8001D7FC;

#ifdef NON_MATCHING
UNK_TYPE func_80001F90(romoffset_t segmentRom, UNK_TYPE arg1, size_t segmentSize) {
    B_80029C00 = segmentRom;
    B_80029C04 = segmentSize;
    B_8001D7F8 = arg1;
    B_8001D7FC = 0;
    func_800021A0();
    func_800020A0();
    return B_8001D7FC;
}
#else
INCLUDE_ASM("boot/2B90", func_80001F90);
#endif

INCLUDE_ASM("boot/2B90", func_80001FD8);

INCLUDE_ASM("boot/2B90", func_80002064);

extern u32 B_8001F990;
extern u32 B_8001D640;
extern u32 B_8001F998;
extern u32 B_8001F9A8;
extern u32 B_80029BE0;
extern u32 B_8001F98C;
extern u8 B_8001B640;


#ifdef NON_EQUIVALENT
s32 func_800020A0(void) {
    u8 sp10[8];
    s32 temp_v0;
    s32 var_v0;
    u32 temp_v1;
    u8 *var_s0;

    func_80002148(NULL, 0);
    temp_v0 = func_80001EB4();
    var_v0 = -1;
    if (temp_v0 != 3) {
        var_s0 = &sp10;
        if (temp_v0 == 0) {
            do {
                temp_v1 = B_80029BE0;
                if (temp_v1 < (u32) B_8001F98C) {
                    B_80029BE0 = temp_v1 + 1;
                    *var_s0 = (&B_8001B640)[temp_v1];
                } else {
                    *var_s0 = func_800021CC(0);
                }
                var_s0 += 1;
                var_v0 = 0;
            } while ((s32) var_s0 < (s32) &sp10[8]);
        }
    }
    return var_v0;
}
#else
INCLUDE_ASM("boot/2B90", func_800020A0);
#endif

INCLUDE_ASM("boot/2B90", func_80002148);

INCLUDE_ASM("boot/2B90", func_800021A0);

INCLUDE_ASM("boot/2B90", func_800021CC);

INCLUDE_ASM("boot/2B90", func_800022A8);

INCLUDE_ASM("boot/2B90", func_80002300);

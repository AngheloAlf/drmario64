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

INCLUDE_ASM("boot/2B90", func_800020A0);

INCLUDE_ASM("boot/2B90", func_80002148);

INCLUDE_ASM("boot/2B90", func_800021A0);

INCLUDE_ASM("boot/2B90", func_800021CC);

INCLUDE_ASM("boot/2B90", func_800022A8);

INCLUDE_ASM("boot/2B90", func_80002300);

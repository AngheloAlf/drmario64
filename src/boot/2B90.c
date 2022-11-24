#include "ultra64.h"
#include "include_asm.h"
#include "boot_functions.h"
#include "boot_variables.h"
#include "macros_defines.h"
#include "libc/stdbool.h"

// libultra?
extern void *B_8001D7F8;
extern UNK_TYPE B_8001D7FC;


#ifdef NON_MATCHING
UNK_TYPE func_80001F90(romoffset_t segmentRom, void *dstAddr, size_t segmentSize) {
    B_80029C00.segmentRom = segmentRom;
    B_80029C00.segmentSize = segmentSize;
    B_8001D7F8 = dstAddr;
    B_8001D7FC = 0;
    func_800021A0();
    func_800020A0();
    return B_8001D7FC;
}
#else
INCLUDE_ASM("asm/nonmatchings/boot/2B90", func_80001F90);
#endif

size_t func_80001FD8(struct_80029C04 *arg0, u8 *arg1, size_t blockSize) {
    size_t alignedSize;

    if (blockSize > arg0->segmentSize) {
        blockSize = arg0->segmentSize;
    }

    alignedSize = ALIGN8(blockSize);
    if (alignedSize > 0) {
        func_80000620(arg0->segmentRom, arg1, alignedSize);
    }

    arg0->segmentSize -= alignedSize;
    arg0->segmentRom += alignedSize;
    if ((s32) arg0->segmentSize < 0) {
        arg0->segmentSize = 0;
    }
    return blockSize;
}

INCLUDE_ASM("asm/nonmatchings/boot/2B90", func_80002064);

extern u32 B_8001F990;
extern u32 B_8001D640;
extern u32 B_8001F998;
extern u32 B_8001F9A8;
extern u32 B_80029BE0;
extern u32 B_8001F98C; // maybe volatile?
extern u8 B_8001B640[0x2000];


s32 func_800020A0(void) {
    u8 sp10[8];
    u8 sp18[8*3] UNUSED;
    s32 temp_v0;
    s32 i;

    func_80002148(NULL, 0);
    temp_v0 = func_80001EB4();

    if (temp_v0 == 3) {
        return -1;
    }
    if (temp_v0 != 0) {
        return -1;
    }

    for (i = 0; i < ARRAY_COUNT(sp10); i++) {
        if (B_80029BE0 < B_8001F98C) {
            sp10[i] = B_8001B640[B_80029BE0++];
        } else {
            sp10[i] = func_800021CC(0);
        }
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/boot/2B90", func_80002148);

extern s32 B_8001FAFC;
extern s32 B_8001FB00;

void func_800021A0(void) {
    B_8001F990 = 0;
    B_80029BE0 = 0;
    B_8001F98C = 0;
    B_8001FB00 = 0;
    B_8001FAFC = 0;
}

#ifdef NON_MATCHING
s32 func_800021CC(s32 arg0) {
    u32 temp_v0;

    for (B_8001F98C = 0; B_8001F98C < ARRAY_COUNT(B_8001B640); B_8001F98C += temp_v0) {
        temp_v0 = func_80001FD8(&B_80029C00, &B_8001B640[B_8001F98C], ARRAY_COUNT(B_8001B640) - B_8001F98C);
        if (temp_v0 + 1 <= 1) {
            break;
        }
    }

    if ( (B_8001F98C != 0) || (arg0 == 0)) {
        B_8001FAFC += B_8001F98C;
        B_80029BE0 = 1;
        return B_8001B640[0];
    }

    return -1;
}
#else
INCLUDE_ASM("asm/nonmatchings/boot/2B90", func_800021CC);
#endif

void func_800022A8(void **arg0, u8 *arg1, s32 arg2) {
    while (true) {
        s32 temp_v0 = func_80002064(arg0, arg1, arg2);

        if (temp_v0 == arg2) {
            return;
        }

        arg2 -= temp_v0;
        arg1 += temp_v0;
    }
}

extern u8 B_80021BE0;

void func_80002300(void) {
    if (B_8001F990 != 0) {
        func_80002148(&B_80021BE0, B_8001F990);
        func_800022A8(&B_8001D7F8, &B_80021BE0, B_8001F990);
        B_8001FB00 += B_8001F990;
        B_8001F990 = 0;
    }
}

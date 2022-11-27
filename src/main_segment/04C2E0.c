#include "ultra64.h"
#include "include_asm.h"
#include "macros_defines.h"
#include "unknown_structs.h"
#include "boot_functions.h"
#include "boot_variables.h"
#include "main_segment_functions.h"
#include "main_segment_variables.h"


INCLUDE_RODATA("asm/nonmatchings/main_segment/04C2E0", D_800B3240);

INCLUDE_ASM("asm/nonmatchings/main_segment/04C2E0", func_80075F30);

INCLUDE_ASM("asm/nonmatchings/main_segment/04C2E0", func_80075F98);

INCLUDE_ASM("asm/nonmatchings/main_segment/04C2E0", func_8007636C);

INCLUDE_ASM("asm/nonmatchings/main_segment/04C2E0", func_8007657C);

INCLUDE_ASM("asm/nonmatchings/main_segment/04C2E0", func_800767DC);

INCLUDE_ASM("asm/nonmatchings/main_segment/04C2E0", func_800768E0);

INCLUDE_ASM("asm/nonmatchings/main_segment/04C2E0", func_80076CA0);

INCLUDE_ASM("asm/nonmatchings/main_segment/04C2E0", func_80076CCC);

INCLUDE_ASM("asm/nonmatchings/main_segment/04C2E0", func_80076DB4);

INCLUDE_ASM("asm/nonmatchings/main_segment/04C2E0", func_800770E8);

void *func_80077170(s32 index, void *dstAddr) {
    size_t size;

    B_800E87A8 = dstAddr;
    B_800E8750 = (void *) ALIGN16((uintptr_t)DecompressRomToRam(D_8000E778[index].unk_0, dstAddr, D_8000E778[index].unk_4 - D_8000E778[index].unk_0));
    size = D_8000E764 - D_8000E760;
    return (void *) ALIGN16((uintptr_t)DecompressRomToRam(D_8000E760, B_800E8750, size));
}

INCLUDE_ASM("asm/nonmatchings/main_segment/04C2E0", func_800771EC);

INCLUDE_ASM("asm/nonmatchings/main_segment/04C2E0", func_800773F0);

INCLUDE_ASM("asm/nonmatchings/main_segment/04C2E0", func_8007744C);

INCLUDE_ASM("asm/nonmatchings/main_segment/04C2E0", func_8007746C);

INCLUDE_ASM("asm/nonmatchings/main_segment/04C2E0", func_800774C4);

INCLUDE_ASM("asm/nonmatchings/main_segment/04C2E0", func_80077504);

INCLUDE_ASM("asm/nonmatchings/main_segment/04C2E0", func_800777E8);

void *func_8007780C(void *dstAddr) {
    void *temp_s0;

    dstAddr = (void*)ALIGN16((uintptr_t)dstAddr);
    B_800E87A8 = dstAddr;
    temp_s0 = (void*)ALIGN16((uintptr_t)DecompressRomToRam(D_8000E740, dstAddr, D_8000E744 - D_8000E740));
    func_8007786C();
    return temp_s0;
}

void func_8007786C(void) {
    guOrtho(&B_800E5F08, -160.0f, 160.0f, -120.0f, 120.0f, 1.0f, 2000.0f, 1.0f);
    D_800AAD34 = 0x15E;
    D_800AAD2C = 0;
    D_800AAD08 = -0x59;
    D_800AAD0C = 0;
}

INCLUDE_ASM("asm/nonmatchings/main_segment/04C2E0", func_800778E8);

void *func_80077D68(void *dstAddr, bool arg1) {
    void *alignedAddress;
    romoffset_t segmentRomStart;
    romoffset_t segmentRomEnd;

    D_800AAD2C = 0;
    guOrtho(&B_800E5F08, -160.0f, 160.0f, -120.0f, 120.0f, 1.0f, 2000.0f, 1.0f);
    alignedAddress = (void*)ALIGN16((uintptr_t)dstAddr);
    B_800E87A8 = alignedAddress;
    if (arg1) {
        segmentRomStart = D_8000E750;
        segmentRomEnd = D_8000E754;
    } else {
        segmentRomStart = D_8000E748;
        segmentRomEnd = D_8000E74C;
    }
    return (void*)ALIGN16((uintptr_t)DecompressRomToRam(segmentRomStart, alignedAddress, segmentRomEnd - segmentRomStart));
}

INCLUDE_ASM("asm/nonmatchings/main_segment/04C2E0", func_80077E2C);

#ifdef NON_MATCHING
void *func_80077FA4(void *dstAddr, bool arg1) {
    romoffset_t romOffsetStart;
    romoffset_t romOffsetEnd;

    if (arg1) {
        B_800E59D8 = 0;
        D_800AAD18 = -0x64;
    } else {
        B_800E59D8 = 0x2D0;
        D_800AAD18 = 0x100;
    }

    B_800E59DC = 0;
    guOrtho(&B_800E5F08, -160.0f, 160.0f, -120.0f, 120.0f, 1.0f, 2000.0f, 1.0f);

    B_800E59E0 = (void*)ALIGN16((uintptr_t)dstAddr);

    B_800E59E4 = (void*)ALIGN16((uintptr_t)DecompressRomToRam(D_8000E768, B_800E59E0, D_8000E76C - D_8000E768));

    romOffsetEnd = D_8000E774;
    romOffsetStart = D_8000E770;
    return (void*) ALIGN16((uintptr_t)DecompressRomToRam(romOffsetStart, B_800E59E4, romOffsetEnd - romOffsetStart));
}
#else
INCLUDE_ASM("asm/nonmatchings/main_segment/04C2E0", func_80077FA4);
#endif

INCLUDE_ASM("asm/nonmatchings/main_segment/04C2E0", func_80078094);

INCLUDE_ASM("asm/nonmatchings/main_segment/04C2E0", func_80078648);

INCLUDE_ASM("asm/nonmatchings/main_segment/04C2E0", func_8007865C);

INCLUDE_ASM("asm/nonmatchings/main_segment/04C2E0", func_8007873C);

INCLUDE_ASM("asm/nonmatchings/main_segment/04C2E0", func_80078F78);

INCLUDE_ASM("asm/nonmatchings/main_segment/04C2E0", func_800791D0);

INCLUDE_ASM("asm/nonmatchings/main_segment/04C2E0", func_800796F4);

INCLUDE_ASM("asm/nonmatchings/main_segment/04C2E0", func_80079B24);

INCLUDE_ASM("asm/nonmatchings/main_segment/04C2E0", func_8007A154);

INCLUDE_ASM("asm/nonmatchings/main_segment/04C2E0", func_8007A440);

void func_8007A9DC(void) {
    void *ptr;
    size_t segmentSize;

    B_800E87AC = D_800AAD3C;

    segmentSize = D_8000E76C - D_8000E768;
    ptr = (void*)ALIGN16((uintptr_t)DecompressRomToRam(D_8000E768, B_800E87AC, segmentSize));
    B_800E8750 = ptr;

    segmentSize = D_8000E75C - D_8000E758;
    ptr = (void*)ALIGN16((uintptr_t)DecompressRomToRam(D_8000E758, ptr, segmentSize));
    B_800E87A8 = ptr;

    segmentSize = D_8000E74C - D_8000E748;
    ptr = (void*)ALIGN16((uintptr_t)DecompressRomToRam(D_8000E748, ptr, segmentSize));
    B_800E87B0 = ptr;
}

INCLUDE_ASM("asm/nonmatchings/main_segment/04C2E0", func_8007AA84);

INCLUDE_ASM("asm/nonmatchings/main_segment/04C2E0", func_8007AEBC);

INCLUDE_ASM("asm/nonmatchings/main_segment/04C2E0", func_8007AEF4);

INCLUDE_ASM("asm/nonmatchings/main_segment/04C2E0", func_8007B62C);

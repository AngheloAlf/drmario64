#include "ultra64.h"
#include "include_asm.h"
#include "macros_defines.h"
#include "unknown_structs.h"
#include "boot_functions.h"
#include "boot_variables.h"
#include "main_segment_functions.h"
#include "main_segment_variables.h"
#include "audio/audio_stuff.h"
#include "other_symbols.h"


INCLUDE_RODATA("asm/nonmatchings/main_segment/04C2E0", D_800B3240);

void func_80075F30(void) {
    D_800A739C = 0;
    B_800E59A0 = 0;
    B_800E59A8 = -8;
    D_80088401 = 0;
    B_800E59A4 = -(B_800EB4F0 == 6) & 0xFF;
    func_80077FA4(&D_80124610, B_800EB4F0 != 6);
}

INCLUDE_ASM("asm/nonmatchings/main_segment/04C2E0", func_80075F98);

INCLUDE_ASM("asm/nonmatchings/main_segment/04C2E0", func_8007636C);

//INCLUDE_ASM("asm/nonmatchings/main_segment/04C2E0", func_8007657C);

const char D_800B32A8[] RODATA = "This game is not designed~nfor use on this system.~z";
const char D_800B3270[] RODATA = "There is no controller~nconnected. Please turn OFF~nthe Nintendo* 64 and insert~na controller in socket 1.~z";
const char D_800B3318[] RODATA = "A Backup File is damaged.~nPress the A Button to delete this file.~z";

extern u8 B_800EBD16;
extern u16 B_800FAF88[];

u32 func_8007657C(struct_800EB670 *arg0) {
    OSMesgQueue sp18;
    OSMesg sp30[8];
    struct_800FAF98_unk_64 sp50;
    void *sp58;
    struct_80124610 *temp_s0 = (void*)ALIGN16((uintptr_t)&D_80124610);
    bool var_s1 = true;

    sp58 = (void*)((uintptr_t)temp_s0 + sizeof(struct_80124610));
    bzero(temp_s0, sizeof(struct_80124610));
    osCreateMesgQueue(&sp18, sp30, ARRAY_COUNT(sp30));
    func_8002A184(arg0, &sp50, &sp18);

    switch (B_800EBCF0) {
        case 0x8:
            func_8005CF78(temp_s0, &sp58, 0x40, 5, 0x40, 0x60);
            func_8005D314(temp_s0, D_800B3270);
            break;

        case 0x9:
            func_8005CF78(temp_s0, &sp58, 0x40, 5, 0x40, 0x72);
            func_8005D314(temp_s0, D_800B32A8);
            break;

        case 0xA:
            func_8005CF78(temp_s0, &sp58, 0x40, 5, 0x28, 0x6C);
            func_8005D314(temp_s0, D_800B3318);
            break;
    }

    func_8005E0BC(temp_s0);

    while (var_s1) {
        func_8002A700();
        osRecvMesg(&sp18, NULL, OS_MESG_BLOCK);
        func_8005D428(temp_s0);
        if ((B_800EBCF0 == 0xA) && (B_800FAF88[B_800EBD16] & 0x8000)) {
            var_s1 = false;
            func_8002B1B4(0x46);
        }
        func_8002AE58();
        D_80088124 = 7;
    }

    D_80088124 = 0;
    while (D_80088128 != 0) {
        osRecvMesg(&sp18, NULL, OS_MESG_BLOCK);
    }

    func_8002A1DC(arg0, &sp50);
    if (B_800EBCF0 == 0xA) {
        func_80038B18(0, 0);
    }
    return 3;
}

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

void *func_80077FA4(void *dstAddr, bool arg1) {
    size_t segmentSize;

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

    segmentSize = D_8000E76C - D_8000E768;
    B_800E59E4 = (void*)ALIGN16((uintptr_t)DecompressRomToRam(D_8000E768, B_800E59E0, segmentSize));

    segmentSize = D_8000E774 - D_8000E770;
    return (void*)ALIGN16((uintptr_t)DecompressRomToRam(D_8000E770, B_800E59E4, segmentSize));
}

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

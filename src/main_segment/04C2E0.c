#include "ultra64.h"
#include "include_asm.h"
#include "macros_defines.h"
#include "unknown_structs.h"
#include "boot_functions.h"
#include "boot_variables.h"
#include "main_segment_functions.h"
#include "main_segment_variables.h"
#include "rom_offsets.h"
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

void func_8007636C(void) {
    s32 color;
    s32 alpha;
    OSScTask *ptr;

    B_800EBCF4 = B_800FB670[D_80088120];

    ptr = &B_800FAE80[D_80088120];
    gSPSegment(B_800EBCF4++, 0x00, NULL);
    func_8002BBD8(1);
    func_8002BC58(1);

    gSPDisplayList(B_800EBCF4++, D_800881E0);

    gDPSetScissor(B_800EBCF4++, G_SC_NON_INTERLACE, 0, 0, SCREEN_WIDTH-1, SCREEN_HEIGHT-1);

    D_800A739C = func_80078094(&B_800EBCF4, D_8008840F != 0);

    color = 255;

    alpha = CLAMP(((B_800E59A4 - 127) * 1.2) + 127.0, 0.0, 255.0);
    if (alpha > 0) {
        func_80040E3C(&B_800EBCF4, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, color, color, color, alpha);
    }

    gDPFullSync(B_800EBCF4++);
    gSPEndDisplayList(B_800EBCF4++);
    osWritebackDCacheAll();

    func_8002B834(ptr, B_800FB670[D_80088120], (B_800EBCF4 - B_800FB670[D_80088120]) * sizeof(Gfx), 0, OS_SC_SWAPBUFFER);
}

const char D_800B32A8[] RODATA = "This game is not designed~nfor use on this system.~z";
const char D_800B3270[] RODATA = "There is no controller~nconnected. Please turn OFF~nthe Nintendo* 64 and insert~na controller in socket 1.~z";
const char D_800B3318[] RODATA = "A Backup File is damaged.~nPress the A Button to delete this file.~z";

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
        if ((B_800EBCF0 == 0xA) && (B_800FAF88[B_800EBD16[0]] & 0x8000)) {
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

void func_800767DC(void) {
    struct_80124610* ptr;

    B_800EBCF4 = B_800FB670[B_800FAD2C];
    ptr = (void*)ALIGN16((uintptr_t)&D_80124610);
    func_8002B9D8();
    func_8002BAB8(1);
    func_8005D78C(ptr, &B_800EBCF4);

    gDPFullSync(B_800EBCF4++);
    gSPEndDisplayList(B_800EBCF4++);

    osWritebackDCacheAll();
    func_8002B834(&B_800FAE80[B_800FAD2C], B_800FB670[B_800FAD2C], (B_800EBCF4 - B_800FB670[B_800FAD2C]) * sizeof(Gfx), 0, OS_SC_SWAPBUFFER);
}

INCLUDE_ASM("asm/nonmatchings/main_segment/04C2E0", func_800768E0);

INCLUDE_ASM("asm/nonmatchings/main_segment/04C2E0", func_80076CA0);

INCLUDE_ASM("asm/nonmatchings/main_segment/04C2E0", func_80076CCC);

INCLUDE_ASM("asm/nonmatchings/main_segment/04C2E0", func_80076DB4);

INCLUDE_ASM("asm/nonmatchings/main_segment/04C2E0", func_800770E8);

void *func_80077170(s32 index, void *dstAddr) {

    B_800E87A8 = dstAddr;
    B_800E8750 = (void *) ALIGN16((uintptr_t)DecompressRomToRam(D_8000E778[index].start, dstAddr, D_8000E778[index].end - D_8000E778[index].start));
    return (void *) ALIGN16((uintptr_t)DecompressRomToRam(D_8000E760.start, B_800E8750, D_8000E760.end - D_8000E760.start));
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

    B_800E87A8 = (void*)ALIGN16((uintptr_t)dstAddr);
    temp_s0 = (void*)ALIGN16((uintptr_t)DecompressRomToRam(D_8000E740.start, B_800E87A8, D_8000E740.end - D_8000E740.start));
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
        segmentRomStart = D_8000E750.start;
        segmentRomEnd = D_8000E750.end;
    } else {
        segmentRomStart = D_8000E748.start;
        segmentRomEnd = D_8000E748.end;
    }
    return (void*)ALIGN16((uintptr_t)DecompressRomToRam(segmentRomStart, alignedAddress, segmentRomEnd - segmentRomStart));
}

INCLUDE_ASM("asm/nonmatchings/main_segment/04C2E0", func_80077E2C);

void *func_80077FA4(void *dstAddr, bool arg1) {
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
    B_800E59E4 = (void*)ALIGN16((uintptr_t)DecompressRomToRam(D_8000E768.start, B_800E59E0, D_8000E768.end - D_8000E768.start));
    return (void*)ALIGN16((uintptr_t)DecompressRomToRam(D_8000E770.start, B_800E59E4, D_8000E770.end - D_8000E770.start));
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

    segmentSize = D_8000E768.end - D_8000E768.start;
    ptr = (void*)ALIGN16((uintptr_t)DecompressRomToRam(D_8000E768.start, B_800E87AC, segmentSize));
    B_800E8750 = ptr;

    segmentSize = D_8000E758.end - D_8000E758.start;
    ptr = (void*)ALIGN16((uintptr_t)DecompressRomToRam(D_8000E758.start, ptr, segmentSize));
    B_800E87A8 = ptr;

    segmentSize = D_8000E748.end - D_8000E748.start;
    ptr = (void*)ALIGN16((uintptr_t)DecompressRomToRam(D_8000E748.start, ptr, segmentSize));
    B_800E87B0 = ptr;
}

extern struct_80124610 B_800E59F0;
extern s32 B_800E5A20;
extern s32 B_800E5A24;
extern s32 B_800E5A2C;
extern s32 B_800E5A38;
extern f32 B_800E5A44;
extern struct_80124610 B_800E5A70;
extern s32 B_800E5A90;
extern s32 B_800E5A94;
extern s32 B_800E5AA0;
extern s32 B_800E5AA4;
extern s32 B_800E5AAC;
extern s32 B_800E5AB8;
extern f32 B_800E5AC4;
extern void B_800E5AF0;
extern struct_80205000 *B_800E5EF0;
extern s32 B_800E5EF4;
extern s32 B_800E5EFC;
extern s32 B_800E5F00;
extern u16 B_800E5F04;
extern s32 B_800E87B4;
extern s16 B_800F6CDE[];
extern s8 D_80088402;
extern u8 D_80088409;
extern void *D_800A8ACC;
extern s32 D_800AAD10;
extern s32 D_800AAD14;
extern s32 D_800AAD1C;
extern s32 D_800AAD20;
extern s32 D_800AAD24;
extern s32 D_800AAD28;
extern struct_80205000 *D_800AAD38;
extern struct_80205000 *D_800AAD40;
extern UNK_TYPE4 D_800AAE00[];

#ifdef NON_EQUIVALENT
s32 func_8007AA84(struct_800EB670 *arg0) {
    OSMesgQueue sp20;
    void *sp38;
    struct_800FAF98_unk_64 sp58;
    s16 *var_v1;
    s32 var_s1;
    s32 var_s1_2;

    osCreateMesgQueue(&sp20, &sp38, 8);
    func_8002A184(arg0, &sp58, &sp20);
    D_80088124 = 0;
    D_800AAD40 = &D_80205000;
    guPerspective(&B_800E5F08, &B_800E5F04, 45.0f, 1.3333334f, 1.0f, 1000.0f, 1.0f);
    var_s1 = 3;
    guOrtho(&B_800E5F08, -160.0f, 160.0f, -120.0f, 120.0f, 1.0f, 2000.0f, 1.0f);

    B_800E87B4 = 1;
    while (var_s1 >= 0) {
        B_800F6CDE[var_s1] = 0xF00;
        var_s1 -= 1;
    }

    D_800AAD3C = &D_80205000 + 0x10000;
    D_800AAD14 = 0x1E;
    D_800A8ACC = &B_800E5AF0;
    D_800AAD38 = &D_80205000;
    D_80088100 = 0;
    D_800AAD08 = 0;
    D_800AAD0C = 0;
    D_800AAD1C = 0;
    D_800AAD10 = 0;
    D_800AAD20 = 0;
    D_800AAD24 = 0;
    D_800AAD28 = 1;
    B_800E5F00 = 0;
    B_800E5EF4 = 0;
    B_800E5EFC = 1;
    func_8005CF78(&B_800E59F0, &D_800A8ACC, 0x10, 3, 0x42, 0xB1);
    B_800E5A20 = 0xC;
    B_800E5A24 = 0xC;
    B_800E5A2C = 6;
    B_800E5A38 = 0xE;
    B_800E5EF0 = &D_80205000;
    B_800E5A44 = 0.4f;
    func_8005CFD4(&B_800E5A70, &B_800E5EF0, 0x77A, 0x14, 0xB, 0x28, 0x16);
    B_800E5A94 = 1;
    B_800E5AA0 = 0xC;
    B_800E5AA4 = 0xC;
    B_800E5AAC = 6;
    B_800E5AB8 = 0xE;
    B_800E5A90 = 1;
    B_800E5AC4 = 0.25f;
    func_8007A9DC();
    func_8002A700();
    func_8002AFC4(D_800AAE00[D_800AACEC]);

    while (B_800E5EFC != 0) {
        osRecvMesg(&sp20, NULL, 1);
        func_8005D428(&B_800E59F0);
        func_8005D428(&B_800E5A70);
        if ((D_800AAD28 == 0) && (D_800AAD10 >= 0x5A)) {
            B_800E5EFC = 0;
        }
        func_8002A700();
        D_80088124 = 1;
        func_8002AE58();
    }

    func_8002AF7C();
    D_80088124 = 0;

    while (true) {
        if ((D_80088128 == 0) || (func_8002AFA4() != 0)) {
            break;
        }
        osRecvMesg(&sp20, NULL, 1);
        func_8002AE58();
    }

    var_s1_2 = 0;
    while (var_s1_2 < 3) {
        osRecvMesg(&sp20, NULL, 1);
        var_s1_2 += 1;
    }

    func_8002A1DC(arg0, &sp58);
    D_80088409 = (u8) D_800AACEC;
    if ((s8) D_800AACEC >= 0xC) {
        D_80088409 = D_800AACEC - 0xC;
    }
    D_80088402 = D_80088409 % 3;
    return (D_80088409 / 3) * 3;
}
#else
INCLUDE_ASM("asm/nonmatchings/main_segment/04C2E0", func_8007AA84);
#endif

INCLUDE_ASM("asm/nonmatchings/main_segment/04C2E0", func_8007AEBC);

INCLUDE_ASM("asm/nonmatchings/main_segment/04C2E0", func_8007AEF4);

INCLUDE_ASM("asm/nonmatchings/main_segment/04C2E0", func_8007B62C);

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

void func_80076CA0(struct_80076CA0_arg0 *arg0, struct_800E8750 *arg1) {
    arg0->unk_04 = arg1->unk_008;
    arg0->unk_08 = arg1->unk_00A;
    arg0->unk_00 = arg1->unk_00E;
    arg0->unk_0C = &arg1->unk_010;
    arg0->unk_10 = &arg1->unk_210;
}

INCLUDE_ASM("asm/nonmatchings/main_segment/04C2E0", func_80076CCC);

INCLUDE_ASM("asm/nonmatchings/main_segment/04C2E0", func_80076DB4);

void func_800770E8(Gfx **arg0, struct_800E8750 *arg1) {
    Gfx *sp28 = *arg0;

    gSPDisplayList(sp28++, D_8008E6B8);
    func_800429B8(&sp28, 0x148, 0xF0, &arg1->unk_010, &arg1->unk_210, 0.0f, 0.0f, 328.0f, 240.0f);
    *arg0 = sp28;
}

void *func_80077170(s32 index, void *dstAddr) {
    B_800E87A8 = dstAddr;
    B_800E8750 = (void *) ALIGN16((uintptr_t)DecompressRomToRam(D_8000E778[index].start, dstAddr, D_8000E778[index].end - D_8000E778[index].start));
    return (void *) ALIGN16((uintptr_t)DecompressRomToRam(D_8000E760.start, B_800E8750, D_8000E760.end - D_8000E760.start));
}

INCLUDE_ASM("asm/nonmatchings/main_segment/04C2E0", func_800771EC);

void func_800773F0(void) {
    if (D_800AAD14 == 0) {
        D_800AAD08 = 0;
        D_800AAD20 = 1;
        D_800AAD24 = 0;
        D_800AAD0C++;
    } else {
        D_800AAD20 = 0;
        D_800AAD14--;
    }
}

void func_8007744C(void) {
    D_800AAD28 = 0;
    D_800AAD10++;
}

void func_8007746C(void) {
    func_8005D09C(&B_800E59F0);
    D_800AAD1C = 0;
    D_800AAD24 = 0;
    D_800AAD08 = 0;
    D_800AAD24 = 0;
    D_800AAD0C++;
}

UNK_TYPE func_800774C4(void) {
    UNK_TYPE temp_v0 = func_8005E0B4(&B_800E59F0);

    if (temp_v0 != 0) {
        func_8007746C();
    }
    return temp_v0;
}

#ifdef NON_EQUIVALENT
void func_80077504(Gfx **arg0, s32 arg1, s32 arg2, s32 arg3, UNK_PTR arg4) {
    //Gfx *sp38;
    //Gfx *temp_a0;
    //Gfx *temp_a0_2;
    Gfx *temp_t0;
    //Gfx *temp_v1;
    //Gfx *temp_v1_2;
    //Gfx *temp_v1_3;
    //Gfx *temp_v1_4;
    f32 temp_f10;
    f32 temp_f14;
    f32 temp_f16;
    s32 temp_a3;
    s32 temp_f2;
    s32 temp_f4_2;
    s32 temp_f6;
    s32 temp_f8;
    s32 var_t1;
    s32 var_v0;

    temp_t0 = *arg0;
    //sp38 = temp_t0;
    if (arg3 < 0xFF) {
        temp_a3 = arg3 & ((s32) ~arg3 >> 0x1F);
        temp_f10 = (f32) ((f64) (f32) ((f64) (f32) temp_a3 / 18.0) * 64.0);
        //sp38 = temp_t0 + 8;
        temp_f16 = (f32) ((f64) (f32) arg1 - temp_f10 / 2.0);
        //temp_t0->words.w0 = 0xE3001001;
        //temp_t0->words.w1 = 0;
        //sp38 = temp_t0 + 0x10;
        temp_f14 = (f32) ((f64) (f32) arg2 - temp_f10 / 2.0);
        //temp_t0->unk_8 = 0xFA000000;
        //temp_t0->unk_C = 0xFF;
        //sp38 = temp_t0 + 0x18;
        //temp_t0->unk_10 = 0xE200001CU;
        //temp_t0->unk_14 = 0x0F0A4000;
        //sp38 = temp_t0 + 0x20;
        //temp_t0->unk_18 = 0xFCFFFFFF;
        //temp_t0->unk_1C = 0xFFFDF6FB;

        gDPSetTextureLUT(temp_t0++, G_TT_NONE);
        gDPSetPrimColor(temp_t0++, 0, 0, 0, 0, 0, 255);
        gDPSetRenderMode(temp_t0++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
        gDPSetCombineMode(temp_t0++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);

        temp_f8 = (s32) (temp_f16 + 1.0f);
        temp_f6 = (s32) ((temp_f16 + temp_f10) - 1.0f);
        temp_f4_2 = (s32) (temp_f14 + 1.0f);
        temp_f2 = (s32) ((temp_f14 + temp_f10) - 1.0f);

        //var_t1 = (temp_f10 < 1.0f);
        //var_v0 = (temp_f10 < 1.0f);
        // PROBLEM HERE
        if (!(temp_a3 & -(((temp_f10 < 1.0f) | (temp_f10 < 1.0f))))) {
            //sp38 = temp_t0 + 0x28;
            //temp_t0->unk_20 = 0xF65003C0;
            //temp_t0->unk_24 = 0;
            gDPFillRectangle(temp_t0++, 0, 0, 320, 240);
        } else {
            if (temp_f8 > 0) {
                //sp38 = temp_t0 + 0x28;
                //temp_t0->unk_20 = (s32) (((temp_f8 & 0x3FF) << 0xE) | 0xF60003C0);
                //temp_t0->unk_24 = 0;
                gDPFillRectangle(temp_t0++, 0, 0, temp_f8, 240);
            }
            if (temp_f6 < 0x140) {
                //temp_v1 = sp38;
                //sp38 = temp_v1 + 8;
                //temp_v1->words.w0 = 0xF65003C0;
                //temp_v1->words.w1 = (temp_f6 & 0x3FF) << 0xE;
                gDPFillRectangle(temp_t0++, temp_f6, 0, 320, 240);
            }
            if (temp_f4_2 > 0) {
                //temp_a0 = sp38;
                //sp38 = temp_a0 + 8;
                //temp_a0->words.w0 = ((temp_f4_2 & 0x3FF) * 4) | 0xF6500000;
                //temp_a0->words.w1 = 0;
                gDPFillRectangle(temp_t0++, 0, 0, 320, temp_f4_2);
            }
            if (temp_f2 < 0xF0) {
                //temp_v1_2 = sp38;
                //sp38 = temp_v1_2 + 8;
                //temp_v1_2->words.w0 = 0xF65003C0;
                //temp_v1_2->words.w1 = (temp_f2 & 0x3FF) * 4;
                gDPFillRectangle(temp_t0++, 0, temp_f2, 320, 240);
            }
            //temp_v1_3 = sp38;
            //sp38 = temp_v1_3 + 8;
            //temp_v1_3->words.w0 = 0xE200001C;
            //temp_v1_3->words.w1 = 0x00504240;
            //sp38 = temp_v1_3 + 0x10;
            //temp_v1_3->unk_8 = 0xFCFFFFFF;
            //temp_v1_3->unk_C = 0xFFFDF2F9;
            gDPSetRenderMode(temp_t0++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
            gDPSetCombineLERP(temp_t0++, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0);
            func_80042FEC(&temp_t0, 0x40, 0x40, arg4, temp_f16, temp_f14, temp_f10, temp_f10);
        }
        //temp_v1_4 = sp38;
        //temp_a0_2 = temp_v1_4 + 8;
        //sp38 = temp_a0_2;
        //temp_v1_4->words.w0 = 0xDE000000;
        //temp_v1_4->words.w1 = (u32) D_8008E6B8;
        gSPDisplayList(temp_t0++, D_8008E6B8);
        *arg0 = temp_t0;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/main_segment/04C2E0", func_80077504);
#endif

void func_800777E8(Gfx **arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_80077504(arg0, arg1, arg2, arg3, &D_800A82C0);
}

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

#if 0
void func_80077E2C(Gfx **arg0, s32 arg1, s32 arg2) {
    struct_8007F004_arg0 sp18;
    Gfx *sp58;
    Gfx *temp_a0;
    Gfx *temp_s0;
    Gfx *temp_v1;
    Gfx *temp_v1_2;

    func_8007AEBC();
    temp_s0 = *arg0;
    #if 0
    sp58 = temp_s0 + 8;
    temp_s0->words.w0 = 0xDB060000;
    temp_s0->words.w1 = 0;
    sp58 = temp_s0 + 0x10;
    temp_s0->unk_8 = 0xDB060014;
    temp_v1 = sp58;
    temp_s0->unk_C = osVirtualToPhysical(B_800E87A8);
    sp58 = temp_v1 + 8;
    temp_v1->words.w1 = (u32) &D_E5F08;
    temp_v1->words.w0 = 0xDA380007;
    sp58 = temp_v1 + 0x10;
    temp_v1->unk_C = D_8008E6B8;
    temp_v1->unk_8 = 0xDE000000;
    sp58 = temp_v1 + 0x18;
    temp_v1->unk_14 = D_800AAD68;
    temp_v1->unk_10 = 0xDE000000;
    sp58 = temp_v1 + 0x20;
    temp_v1->unk_18 = 0xED000000;
    temp_v1->unk_1C = 0x004FC3BC;
    #endif
    gSPSegment(temp_s0++, 0x00, 0x00000000);
    gSPSegment(temp_s0++, 0x05, osVirtualToPhysical(B_800E87A8));
    gSPMatrix(temp_s0++, OS_K0_TO_PHYSICAL(&B_800E5F08), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gSPDisplayList(temp_s0++, D_8008E6B8);
    gSPDisplayList(temp_s0++, D_800AAD68);
    gDPSetScissor(temp_s0++, G_SC_NON_INTERLACE, 0, 0, 319, 239);

    func_8007F004(&sp18, arg1 << 0xF, arg2 << 0xF, -0x03B60000);
    if (func_8007B650(&sp58, &sp18, B_800E87A8, D_800AAD2C, B_800E87A8) == 1) {
        D_800AAD2C = 0;
    } else {
        D_800AAD2C += 1;
    }
    //temp_v1_2 = sp58;
    //temp_a0 = temp_v1_2 + 8;
    //sp58 = temp_a0;
    //temp_v1_2->words.w0 = 0xDE000000;
    //temp_v1_2->words.w1 = (u32) D_8008E6B8;
    gSPDisplayList(temp_s0++, D_8008E6B8);
    *arg0 = temp_s0;
}
#else
INCLUDE_ASM("asm/nonmatchings/main_segment/04C2E0", func_80077E2C);
#endif

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

#if 0
s32 func_8007B650(Gfx **, struct_8007F004_arg0 *, void *, s32, void *); /* extern */
extern void *B_800E59E8;
extern void *B_800E59EC;
extern UNK_TYPE D_800A82C0;
extern s32 D_800A8AC0;
extern s32 D_800A8AC4;
extern s32 D_800A8AC8;

s32 func_80078094(Gfx **arg0, s32 arg1) {
    struct_80076CA0_arg0 sp30;
    struct_80076CA0_arg0 sp48;
    struct_8007F004_arg0 sp60;
    Gfx *spA0;
    s32 temp_s2;
    u8 temp_v1_2;
    s32 var_s0;
    s32 var_s0_2;
    s32 var_s3;
    s32 var_v0;
    s32 var_v0_3;

    func_8007AEBC();
    var_s3 = 0;
    spA0 = *arg0;
    #if 0
    temp_s0 = *arg0;
    spA0 = temp_s0 + 8;
    temp_s0->words.w0 = 0xDB060000;
    temp_s0->words.w1 = 0;
    spA0 = temp_s0 + 0x10;
    temp_s0->unk_8 = 0xDB060014;
    temp_a1 = spA0;
    temp_s0->unk_C = osVirtualToPhysical(B_800E59E0);
    spA0 = temp_a1 + 8;
    temp_a1->words.w1 = (u32) &D_E5F08;
    temp_a1->words.w0 = 0xDA380007;
    spA0 = temp_a1 + 0x10;
    temp_a1->unk_C = D_8008E6B8;
    temp_a1->unk_8 = 0xDE000000;
    spA0 = temp_a1 + 0x18;
    temp_a1->unk_14 = &D_800AAD68;
    temp_a1->unk_10 = 0xDE000000;
    spA0 = temp_a1 + 0x20;
    temp_a1->unk_18 = 0xED000000;
    temp_a1->unk_1C = 0x4FC3BC;
    #endif
    gSPSegment(spA0++, 0x00, 0x00000000);
    temp_s2 = (B_800E59D8 < 0x2D0) ^ 1;
    gSPSegment(spA0++, 0x05, osVirtualToPhysical(B_800E59E0));
    gSPMatrix(spA0++, OS_K0_TO_PHYSICAL(&B_800E5F08), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gSPDisplayList(spA0++, D_8008E6B8);
    gSPDisplayList(spA0++, D_800AAD68);
    gDPSetScissor(spA0++, G_SC_NON_INTERLACE, 0, 0, 319, 239);

    B_800E59E8 = B_800E59E0;
    if (arg1 != 0) {
        //temp_a1->unk_20 = 0xFB000000;
        //temp_a1->unk_24 = 0xB77F5FFF;
        //spA0 = temp_a1 + 0x28;
        gDPSetEnvColor(spA0++, 183, 127, 95, 255);
        #if 0
        var_v0 = B_800E59E0->unk_84 & 0xFFFFFF;
        #else
        // TODO
        B_800E59EC = B_800E59E8 + ((uintptr_t)B_800E59E0[0x84/4] & 0xFFFFFF);
        #endif
    } else {
        //spA0 = temp_a1 + 0x28;
        //temp_a1->unk_20 = 0xFB000000;
        //temp_a1->unk_24 = -1;
        gDPSetEnvColor(spA0++, 255, 255, 255, 255);
        #if 0
        var_v0 = B_800E59E0->unk_00 & 0xFFFFFF;
        #else
        B_800E59EC = B_800E59E8 + ((uintptr_t)B_800E59E0[0x0/4] & 0xFFFFFF);
        #endif
    }
    //B_800E59EC = var_v0 + (uintptr_t)B_800E59E0;
    func_8007F004(&sp60, 0, -0x3C0000, -0x03B60000);
    if ((D_800AAD18 > 0) && (B_800FAF88[*B_800EBD16] & 0xFF3F)) {
        if (temp_s2 != 0) {
            if (B_800E59DC == 0) {
                func_8002B1B4(0x67);
                B_800E59DC = 1;
            }
        } else {
            B_800E59D8 = 0x2D0;
        }
    }

    if (B_800E59DC > 0) {
        B_800E59DC++;
        if (B_800E59DC >= 0x3C) {
            var_s3 = 1;
        }
    }
    if (func_8007B650(&spA0, &sp60, B_800E59EC, B_800E59D8, B_800E59E0) == 1) {
        var_s3 = -1;
    }
    //temp_v1 = spA0;
    //spA0 = temp_v1 + 8;
    //temp_v1->words.w0 = 0xDE000000;
    //temp_v1->words.w1 = (u32) D_8008E6B8;
    gSPDisplayList(spA0++, D_8008E6B8);
    if (D_800AAD18 > 0) {
        B_800E59D8 += 1;
    }
    if (D_800AAD18 < 0x100) {
        //spA0 = temp_v1 + 0x10;
        //temp_v1->unk_8 = 0xDE000000U;
        //temp_v1->unk_C = D_8008E6B8;
        gSPDisplayList(spA0++, D_8008E6B8);
        func_80077504(&spA0, 0xA0, 0x78, D_800AAD18, &D_800A82C0);
        if (D_800AAD18 < 0) {
            temp_v1_2 = 0xFF;
            if (D_800AAD18 >= -0x17) {
                var_s0_2 = (D_800AAD18 * -0xFF) / 24;
                if (var_s0_2 >= 0x100) {
                    var_s0_2 = 0xFF;
                }
                temp_v1_2 = var_s0_2 & ((s32) ~var_s0_2 >> 0x1F);
            }

            if (D_800AAD18 < -0x4C) {
                var_s0_2 = 0xFF - (((D_800AAD18 + 0x4C) * -0xFF) / 24);
                if (var_s0_2 >= 0x100) {
                    var_s0_2 = 0xFF;
                }
                temp_v1_2 = var_s0_2 & ((s32) ~var_s0_2 >> 0x1F);
            }
            func_80076CA0(&sp30, B_800E59E4 + D_800A8AC0);
            //temp_a1_2 = spA0;

            //temp_a1_2->words.w0 = 0xE3001001;
            //temp_a1_2->unk_8 = 0xFA000000;
            //temp_a1_2->words.w1 = 0;
            //temp_a1_2->unk_C = (s32) ((temp_v1_2 << 0x18) | (temp_v1_2 << 0x10) | (temp_v1_2 << 8) | 0xFF);
            //temp_a1_2->unk_10 = 0xE200001C;
            //temp_a1_2->unk_14 = 0x00504240;
            //temp_a1_2->unk_18 = 0xFCFFFFFF;
            //temp_a1_2->unk_1C = 0xFFFDF2F9;
            //spA0 = temp_a1_2 + 8;
            //spA0 = temp_a1_2 + 0x10;
            //spA0 = temp_a1_2 + 0x18;
            //spA0 = temp_a1_2 + 0x20;
            gDPSetTextureLUT(spA0++, G_TT_NONE);
            gDPSetPrimColor(spA0++, 0, 0, temp_v1_2, temp_v1_2, temp_v1_2, 255);
            gDPSetRenderMode(spA0++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
            gDPSetCombineLERP(spA0++, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0);

            func_80042FEC(&spA0, sp30.unk_04, sp30.unk_08, sp30.unk_10, (f32) (0xA0 - (sp30.unk_04 / 2)), (f32) (0x78 - (sp30.unk_08 / 2)), (f32) sp30.unk_04, (f32) sp30.unk_08);
            D_800AAD18 += 1;
        } else {
            D_800AAD18 += 5;
        }
    }
    var_v0_3 = 1;
    if (B_800E59DC == 0) {
        var_v0_3 = 0x10;
    }
    if ((B_800E59D8 & var_v0_3) && (B_800E59D8 > 0x2D0) && (B_800E59DC == 0)) {
        func_80076CA0(&sp30, B_800E59E4 + D_800A8AC4);
        func_80076CA0(&sp48, B_800E59E4 + D_800A8AC8);
        //spA0->words.w0 = 0xDE000000;
        //spA0->words.w1 = (u32) &D_8008E650;
        //spA0 += 8;
        gSPDisplayList(spA0++, D_8008E650);
        func_80042364(&spA0, sp30.unk_04, sp30.unk_08, sp30.unk_10, sp30.unk_04, (s32) sp48.unk_10, sp48.unk_04, 88.0f, 165.0f, (f32) sp30.unk_04, (f32) sp30.unk_08);
    }
    *arg0 = spA0;
    return var_s3;
}
#else
INCLUDE_ASM("asm/nonmatchings/main_segment/04C2E0", func_80078094);
#endif

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

void func_8007AEBC(void) {
    B_800F1DF8 = &B_800E5F50[D_800AAD44];
    D_800AAD44 ^= 1;
}

#if 0
UNK_TYPE func_8002B834(OSScTask *, Gfx *, s32, UNK_TYPE, s32);    /* extern */
UNK_TYPE func_8002BBD8(UNK_TYPE);                                 /* extern */
UNK_TYPE func_8002BC58(UNK_TYPE, s32);                            /* extern */
UNK_TYPE func_800768E0(Gfx **, s32);                       /* extern */
UNK_TYPE func_80076DB4(Gfx **, s32);                       /* extern */
UNK_TYPE func_800770E8(Gfx **, void *);                    /* extern */
UNK_TYPE func_80077504(Gfx **, UNK_TYPE, UNK_TYPE, s32, UNK_TYPE *);            /* extern */
UNK_TYPE func_8007873C(Gfx **, UNK_TYPE);                         /* extern */
UNK_TYPE func_80078F78(Gfx **, UNK_TYPE, UNK_TYPE, u32);                 /* extern */
UNK_TYPE func_800791D0(Gfx **, UNK_TYPE, UNK_TYPE, UNK_TYPE, s32);              /* extern */
UNK_TYPE func_800796F4(Gfx **, UNK_TYPE, UNK_TYPE, UNK_TYPE, s32);              /* extern */
UNK_TYPE func_80079B24(Gfx **, UNK_TYPE, UNK_TYPE);                      /* extern */
UNK_TYPE func_8007A154(Gfx **, UNK_TYPE, UNK_TYPE);                      /* extern */
UNK_TYPE func_8007A440(Gfx **, UNK_TYPE);                         /* extern */
extern void *B_800E59E8;
extern struct_80124610 B_800E5A70;
extern f32 B_800E5ACC;
extern s32 B_800E5EFC;
extern s32 B_800E5F00;
extern s8 D_8008840A;
extern UNK_TYPE D_800A82C0;
extern UNK_TYPE D_E5F08;

void func_8007AEF4(void) {
    UNK_TYPE var_a1;
    UNK_TYPE var_a1_2;
    UNK_TYPE var_a1_3;
    UNK_TYPE var_a1_4;
    UNK_TYPE var_a2;
    UNK_TYPE var_a2_2;
    UNK_TYPE var_a2_3;
    Gfx *temp_s0;
    Gfx *temp_v1;
    Gfx *temp_v1_2;
    Gfx *temp_v1_3;
    Gfx *temp_v1_4;
    Gfx *temp_v1_5;
    OSScTask *temp_s1;
    f32 var_f0;
    s32 temp_v0;

    B_800EBCF4 = B_800FB670[B_800FAD2C];
    temp_s1 = &B_800FAE80[B_800FAD2C];
    func_8007AEBC(B_800FAD2C);
    temp_s0 = B_800EBCF4;
    B_800EBCF4 = temp_s0 + 8;
    temp_s0->words.w0 = 0xDB060000;
    temp_s0->words.w1 = 0;
    B_800EBCF4 = temp_s0 + 0x10;
    temp_s0->unk_8 = 0xDB060014;
    temp_s0->unk_C = osVirtualToPhysical(D_800AAD3C);
    B_800E59E8 = D_800AAD3C;
    func_8002BBD8(1);
    temp_v1 = B_800EBCF4;
    B_800EBCF4 = temp_v1 + 8;
    temp_v1->words.w0 = 0xE7000000;
    B_800EBCF4 = temp_v1 + 0x10;
    temp_v1->unk_C = 0x300000;
    B_800EBCF4 = temp_v1 + 0x18;
    B_800EBCF4 = temp_v1 + 0x20;
    temp_v1->unk_18 = 0xFB000000;
    temp_v1->words.w1 = 0;
    temp_v1->unk_8 = 0xE3000A01;
    temp_v1->unk_10 = 0xE3000A01;
    temp_v1->unk_14 = 0;
    temp_v1->unk_1C = -1;
    func_8002BC58(1, 0xE3000A01);
    temp_v1_2 = B_800EBCF4;
    B_800EBCF4 = temp_v1_2 + 8;
    temp_v1_2->words.w0 = 0xDA380007;
    temp_v1_2->words.w1 = (u32) &D_E5F08;
    if (D_800AAD10 > 0) {
        func_800768E0(&B_800EBCF4, D_800AAD10);
        D_800AAD10 += 1;
    } else {
        switch (D_800AACEC) {
        case 0x0:
        case 0xC:
            func_80078F78(&B_800EBCF4, 1, 0);
            break;
        case 0xA:
            func_80079B24(&B_800EBCF4, 0x14, 0x1B);
            break;
        case 0xB:
            func_80079B24(&B_800EBCF4, 0x16, 0x1C);
            break;
        case 0x16:
            func_8007A440(&B_800EBCF4, 0x17);
            break;
        case 0x17:
            func_8007A440(&B_800EBCF4, 0x19);
            break;
        case 0x1:
            func_8007873C(&B_800EBCF4, 1);
            break;
        case 0x2:
            func_800796F4(&B_800EBCF4, 2, 5, 3, 7);
            break;
        case 0x3:
            var_a1 = 5;
            var_a2 = 9;
block_25:
            B_800EBCF4 += 8;
            B_800EBCF4->words.w0 = 0xFB000000;
            B_800EBCF4->words.w1 = 0xAA96B9FF;
            func_80078F78(&B_800EBCF4, var_a1, var_a2, 0xAA96B9FFU);
            break;
        case 0x4:
            func_800791D0(&B_800EBCF4, 0x22, 0x1D, 7, 0xB);
            break;
        case 0x5:
            func_80078F78(&B_800EBCF4, 9, 0xD);
            break;
        case 0x6:
            func_80078F78(&B_800EBCF4, 0xC, 0xF);
            break;
        case 0x7:
            var_a1_2 = 0x1E;
            if (D_8008840A == 0) {
block_31:
                func_80078F78(&B_800EBCF4, var_a1_2, 0x19);
            } else {
block_32:
                func_80078F78(&B_800EBCF4, 0xD, 0x11);
            }
            break;
        case 0x8:
            if (D_8008840A == 0) {
                var_a1_3 = 0x20;
                var_a2_2 = 0x1A;
            } else {
                var_a1_3 = 0xE;
                var_a2_2 = 0x12;
            }
            func_800791D0(&B_800EBCF4, var_a1_3, var_a2_2, 0x10);
            break;
        case 0x9:
            func_80078F78(&B_800EBCF4, 0x12, 0x14);
            break;
        case 0xD:
            func_8007873C(&B_800EBCF4, 0);
            break;
        case 0xE:
            func_800796F4(&B_800EBCF4, 2, 6, 4, 8);
            break;
        case 0xF:
            var_a1 = 6;
            var_a2 = 0xA;
            goto block_25;
        case 0x10:
            func_800791D0(&B_800EBCF4, 0x22, 0x1D, 8, 0xC);
            break;
        case 0x11:
            func_80078F78(&B_800EBCF4, 0xA, 0xE);
            break;
        case 0x12:
            func_80078F78(&B_800EBCF4, 0xB, 0x10);
            break;
        case 0x13:
            var_a1_2 = 0x1F;
            if (D_8008840A == 0) {
                goto block_31;
            }
            goto block_32;
        case 0x14:
            if (D_8008840A == 0) {
                var_a1_4 = 0x20;
                var_a2_3 = 0x1A;
            } else {
                var_a1_4 = 0xF;
                var_a2_3 = 0x12;
            }
            func_800791D0(&B_800EBCF4, var_a1_4, var_a2_3, 0x11);
            break;
        case 0x15:
            func_8007A154(&B_800EBCF4, 0x13, 0x15);
            break;
        }
        func_80076DB4(&B_800EBCF4, D_800AAD14);
        if (B_800E5F00 == 2) {
            func_8005D78C(&B_800E5A70, &B_800EBCF4);
            if (B_800FAF88[*B_800EBD16] & 0x1000) {
                B_800E5F00 = -1;
            }
            if (B_800EBCF8[*B_800EBD16] & 0xC000) {
                var_f0 = 0.16666667f;
            } else {
                var_f0 = 0.016666668f;
            }
            B_800E5ACC = var_f0;
        }
        func_800770E8(&B_800EBCF4, B_800E8750);
        if (D_800AAD20 != 0) {
            func_8005D78C(&B_800E59F0, &B_800EBCF4);
            temp_v1_3 = B_800EBCF4;
            B_800EBCF4 = temp_v1_3 + 8;
            temp_v1_3->words.w0 = 0xED000000;
            temp_v1_3->words.w1 = 0x4FC3BC;
        }
    }
    if (B_800E5F00 < 0) {
        temp_v1_4 = B_800EBCF4;
        B_800EBCF4 = temp_v1_4 + 8;
        temp_v1_4->words.w0 = 0xDE000000;
        temp_v1_4->words.w1 = (u32) D_8008E6B8;
        func_80077504(&B_800EBCF4, 0xA0, 0x78, D_800AAD18, &D_800A82C0);
        temp_v0 = D_800AAD18 - 4;
        D_800AAD18 = temp_v0;
        if (temp_v0 < -0x14) {
            B_800E5EFC = 0;
        }
    }
    temp_v1_5 = B_800EBCF4;
    D_800AAD08 += 1;
    B_800EBCF4 = temp_v1_5 + 8;
    temp_v1_5->words.w0 = 0xE9000000;
    B_800EBCF4 = temp_v1_5 + 0x10;
    temp_v1_5->words.w1 = 0;
    temp_v1_5->unk_8 = 0xDF000000;
    temp_v1_5->unk_C = 0;
    osWritebackDCacheAll();
    func_8002B834(temp_s1, B_800FB670[B_800FAD2C], ((s32) ((B_800EBCF4 - B_800FB670) - (B_800FAD2C << 0xF)) >> 3) * 8, 0, 0x40);
}
#else
INCLUDE_ASM("asm/nonmatchings/main_segment/04C2E0", func_8007AEF4);
#endif

INCLUDE_ASM("asm/nonmatchings/main_segment/04C2E0", func_8007B62C);

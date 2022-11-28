#include "ultra64.h"
#include "include_asm.h"
#include "unk.h"
#include "macros_defines.h"
#include "boot_functions.h"
#include "boot_variables.h"
#include "main_segment_functions.h"
#include "main_segment_variables.h"


INCLUDE_RODATA("asm/nonmatchings/main_segment/016F60", D_800ADB40);

INCLUDE_ASM("asm/nonmatchings/main_segment/016F60", func_80040BB0);

INCLUDE_ASM("asm/nonmatchings/main_segment/016F60", func_80040D34);

#ifdef NON_EQUIVALENT
void func_80040E3C(Gfx **arg0, s32 x0, s32 y0, s32 x1, s32 y1, s32 red, s32 green, s32 blue, s32 alpha) {
    Gfx *temp_t2;
    Gfx *temp_t2_2;
    Gfx *temp_t2_3;
    s32 temp_a3;
    s32 temp_t0;

    temp_t2 = *arg0;
    gSPDisplayList(temp_t2, D_8008E748);
    //temp_t2->words.w0 = 0xDE000000;
    //temp_t2->words.w1 = (u32) &D_8008E748;
    //temp_t2_2->words.w0 = 0xFA000000;
    //temp_t2_2->words.w1 = ((u8) arg5 << 0x18) | ((u8) arg6 << 0x10) | ((u8) arg7 << 8) | (u8) arg8;
    gDPSetPrimColor(temp_t2+1, 0, 0, red, green, blue, alpha);

    //temp_t2_3->words.w0 = ((temp_a3 & ((s32) ~temp_a3 >> 0x1F) & 0x3FF) << 0xE) | (((temp_t0 & ((s32) ~temp_t0 >> 0x1F) & 0x3FF) * 4) | -0x0A000000);
    //temp_t2_3->words.w1 = ((arg1 & ((s32) ~arg1 >> 0x1F) & 0x3FF) << 0xE) | ((arg2 & ((s32) ~arg2 >> 0x1F) & 0x3FF) * 4);
    gDPFillRectangle(temp_t2+2, x0, y0, x0 + x1, y0 + y1);
    *arg0 = temp_t2 +2;
    //return -0x0A000000;
}
#else
INCLUDE_ASM("asm/nonmatchings/main_segment/016F60", func_80040E3C);
#endif

INCLUDE_ASM("asm/nonmatchings/main_segment/016F60", func_80040F34);

INCLUDE_ASM("asm/nonmatchings/main_segment/016F60", func_8004113C);

INCLUDE_ASM("asm/nonmatchings/main_segment/016F60", func_80041334);

INCLUDE_ASM("asm/nonmatchings/main_segment/016F60", func_80041480);

INCLUDE_ASM("asm/nonmatchings/main_segment/016F60", func_80041668);

INCLUDE_ASM("asm/nonmatchings/main_segment/016F60", func_800417B4);

INCLUDE_ASM("asm/nonmatchings/main_segment/016F60", func_8004199C);

INCLUDE_ASM("asm/nonmatchings/main_segment/016F60", func_80041A54);

INCLUDE_ASM("asm/nonmatchings/main_segment/016F60", func_80041DE0);

INCLUDE_ASM("asm/nonmatchings/main_segment/016F60", func_80041F94);

INCLUDE_ASM("asm/nonmatchings/main_segment/016F60", func_8004216C);

INCLUDE_ASM("asm/nonmatchings/main_segment/016F60", func_80042364);

INCLUDE_ASM("asm/nonmatchings/main_segment/016F60", func_80042468);

INCLUDE_ASM("asm/nonmatchings/main_segment/016F60", func_80042650);

INCLUDE_ASM("asm/nonmatchings/main_segment/016F60", func_800427E0);

INCLUDE_ASM("asm/nonmatchings/main_segment/016F60", func_800429B8);

INCLUDE_ASM("asm/nonmatchings/main_segment/016F60", func_80042B48);

INCLUDE_ASM("asm/nonmatchings/main_segment/016F60", func_80042D20);

INCLUDE_ASM("asm/nonmatchings/main_segment/016F60", func_80042E04);

INCLUDE_ASM("asm/nonmatchings/main_segment/016F60", func_80042FEC);

INCLUDE_ASM("asm/nonmatchings/main_segment/016F60", func_800430D0);

INCLUDE_ASM("asm/nonmatchings/main_segment/016F60", func_800432A8);

INCLUDE_ASM("asm/nonmatchings/main_segment/016F60", func_8004338C);

INCLUDE_ASM("asm/nonmatchings/main_segment/016F60", func_8004371C);

INCLUDE_ASM("asm/nonmatchings/main_segment/016F60", func_800438D0);

INCLUDE_ASM("asm/nonmatchings/main_segment/016F60", func_80043A14);

INCLUDE_ASM("asm/nonmatchings/main_segment/016F60", func_80043BEC);

INCLUDE_ASM("asm/nonmatchings/main_segment/016F60", func_80043DDC);

INCLUDE_ASM("asm/nonmatchings/main_segment/016F60", func_80043F18);

INCLUDE_ASM("asm/nonmatchings/main_segment/016F60", func_80044058);

INCLUDE_ASM("asm/nonmatchings/main_segment/016F60", func_80044238);

INCLUDE_ASM("asm/nonmatchings/main_segment/016F60", func_800443F4);

INCLUDE_ASM("asm/nonmatchings/main_segment/016F60", func_800445C4);

INCLUDE_ASM("asm/nonmatchings/main_segment/016F60", func_80044780);

INCLUDE_ASM("asm/nonmatchings/main_segment/016F60", func_80044940);

INCLUDE_ASM("asm/nonmatchings/main_segment/016F60", func_80044B18);

INCLUDE_ASM("asm/nonmatchings/main_segment/016F60", func_80044C28);

INCLUDE_ASM("asm/nonmatchings/main_segment/016F60", func_80044E08);

INCLUDE_ASM("asm/nonmatchings/main_segment/016F60", func_80044F18);

INCLUDE_ASM("asm/nonmatchings/main_segment/016F60", func_8004502C);

#if 0
//? func_8004502C(s32, s32, s32);                     /* extern */

s32 func_80045098(void **arg0, romoffset_t segmentRom, romoffset_t segmentRomEnd) {
    s32 *temp_v0;
    s32 temp_s0;
    s32 temp_s1;

    temp_s0 = ALIGN16((uintptr_t)*arg0);
    *arg0 = DecompressRomToRam(segmentRom, (void *) temp_s0, segmentRomEnd - segmentRom);
    temp_s1 = temp_s0->unk_0 + temp_s0;
    temp_v0 = temp_s0->unk_4 + temp_s0;
    temp_s0->unk_0 = temp_s1;
    temp_s0->unk_4 = temp_v0;
    func_8004502C(temp_s1, *temp_v0, temp_s0);
    return temp_s1;
}
#else
INCLUDE_ASM("asm/nonmatchings/main_segment/016F60", func_80045098);
#endif

INCLUDE_ASM("asm/nonmatchings/main_segment/016F60", func_80045110);

INCLUDE_ASM("asm/nonmatchings/main_segment/016F60", func_800451C4);

INCLUDE_ASM("asm/nonmatchings/main_segment/016F60", func_800452B0);

INCLUDE_ASM("asm/nonmatchings/main_segment/016F60", func_800453D8);

INCLUDE_ASM("asm/nonmatchings/main_segment/016F60", func_8004554C);

INCLUDE_ASM("asm/nonmatchings/main_segment/016F60", func_80045748);

INCLUDE_ASM("asm/nonmatchings/main_segment/016F60", func_80045914);

INCLUDE_RODATA("asm/nonmatchings/main_segment/016F60", D_800ADBC0);

INCLUDE_ASM("asm/nonmatchings/main_segment/016F60", func_80045AAC);

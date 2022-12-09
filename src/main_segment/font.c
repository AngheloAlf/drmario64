#include "ultra64.h"
#include "include_asm.h"
#include "macros_defines.h"
#include "unknown_structs.h"
#include "unk.h"
#include "main_segment_functions.h"
#include "main_segment_variables.h"

INCLUDE_RODATA("asm/nonmatchings/main_segment/font", RO_800B1950);

s32 fontStr_nextChar(const char *arg0) {
    s32 var_v1;

    if (arg0[0] < 0x80) {
        var_v1 = 1;
        if (arg0[0] == '~') {
            if (arg0[1] == 'z') {
                var_v1 = 0;
            } else {
                var_v1 = (-(arg0[1] == 'w') & 3) | 2;
            }
        }
    } else {
        var_v1 = 2;
        if ((char)(arg0[0] + 0x5F) < 0x3F) {
            var_v1 = 1;
        }
    }
    return var_v1;
}

s32 func_8005B858(const char *arg0) {
    s32 temp_v0;
    s32 var_s0 = 0;

    do {
        temp_v0 = fontStr_nextChar(arg0 + var_s0);
        var_s0 += temp_v0;
    } while (temp_v0 != 0);
    return var_s0;
}

INCLUDE_ASM("asm/nonmatchings/main_segment/font", fontStr_charSize);

u16 func_8005B8D8(u8 arg0) {
    return D_800A6D90[arg0];
}

INCLUDE_ASM("asm/nonmatchings/main_segment/font", func_8005B8F0);

INCLUDE_ASM("asm/nonmatchings/main_segment/font", func_8005B940);

extern Gfx RO_800B1950[];

void font16_initDL(Gfx **gfxP) {
    gSPDisplayList((*gfxP)++, RO_800B1950);
}

void font16_initDL2(Gfx **gfxP) {
    Gfx *gfx = *gfxP;

    font16_initDL(&gfx);

    gDPSetEnvColor(gfx++, 250, 250, 250, 255);
    gDPLoadMultiTile_4b(gfx++, D_800A3A88, 0x019A, 1, G_IM_FMT_I, 12, 0, 0, 0, 11, 11, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK,
                        G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    *gfxP = gfx;
}

INCLUDE_ASM("asm/nonmatchings/main_segment/font", fontXX_draw);

#if 0
bool func_8005BB24(Gfx **gfxP, f32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5) {
    s32 sp0;
    s32 sp4;
    s32 sp8;
    s32 spC;
    s32 sp10;
    s32 sp14;
    s32 sp18;
    s32 sp1C;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 var_a0;
    s32 var_v0_2;
    s32 var_v0_3;
    s32 var_v0_4;
    s32 var_v1;
    s32 var_v1_2;
    void *temp_a0;
    void *temp_a0_2;
    void *temp_a1;
    void *temp_v1;
    void *temp_v1_2;
    void *temp_v1_3;
    void *temp_v1_4;
    void *temp_v1_5;
    void *temp_v1_6;
    void *temp_v1_7;

    var_v0_2 = 1;
    if (!(arg3 <= 0.0f)) {
        var_v0_2 = 0;
    }
    var_v1 = 1;
    if (!(arg4 <= 0.0f)) {
        var_v1 = 0;
    }

    if (((var_v0_2 | var_v1) == 0) && (arg5 != 0)) {
        if (arg5 > 0) {
            //temp_a0 = *gfxP;
            //*gfxP = temp_a0 + 8;
            //temp_a0->unk_0 = 0xFD880005;
            //temp_a0->unk_4 = (void *) (((s32) ((arg5 - 1) * 0xC * 0xC) >> 1) + &D_8008E8C0);
            //temp_v1 = *gfxP;
            //*gfxP = temp_v1 + 8;
            //temp_v1->unk_0 = 0xF5880200;
            //temp_v1->unk_4 = (void *)0x07080200;
            //temp_v1_2 = *gfxP;
            //*gfxP = temp_v1_2 + 8;
            //temp_v1_2->unk_0 = 0xE6000000;
            //temp_v1_2->unk_4 = NULL;
            //temp_v1_3 = *gfxP;
            //*gfxP = temp_v1_3 + 8;
            //temp_v1_3->unk_0 = 0xF4000000;
            //temp_v1_3->unk_4 = (void *)0x0701602C;
            //temp_v1_4 = *gfxP;
            //*gfxP = temp_v1_4 + 8;
            //temp_v1_4->unk_0 = 0xE7000000;
            //temp_v1_4->unk_4 = NULL;
            //temp_v1_5 = *gfxP;
            //*gfxP = temp_v1_5 + 8;
            //temp_v1_5->unk_0 = 0xF5800200;
            //temp_v1_5->unk_4 = (void *)0x80200;
            //temp_v1_6 = *gfxP;
            //*gfxP = temp_v1_6 + 8;
            //temp_v1_6->unk_0 = 0xF2000000;
            //temp_v1_6->unk_4 = (void *)0x2C02C;
            gDPLoadTextureTile_4b((*gfxP)++, 0xFFFFFFFF, G_IM_FMT_I, 12, 0, 0, 0, 11, 11, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

        }
        sp10 = 0;
        sp14 = 0;
        sp0 = (s32) (arg1 * 4.0f);
        sp4 = (s32) (arg2 * 4.0f);
        sp8 = (s32) ((arg1 + arg3) * 4.0f);
        spC = (s32) ((arg2 + arg4) * 4.0f);
        sp18 = (s32) (12288.0f / arg3);
        sp1C = (s32) (12288.0f / arg4);
        /*
        temp_a1 = *gfxP;
        *gfxP = temp_a1 + 8;
        temp_a1->unk_0 = (s32) (((sp8 & ((s32) ~unkspA >> 0x1F) & 0xFFF) << 0xC) | ((spC & ((s32) ~unkspE >> 0x1F) & 0xFFF) | 0xE4000000));
        temp_a1->unk_4 = (void *) (((sp0 & ((s32) ~unksp2 >> 0x1F) & 0xFFF) << 0xC) | (sp4 & ((s32) ~unksp6 >> 0x1F) & 0xFFF));
        temp_v1_7 = *gfxP;
        *gfxP = temp_v1_7 + 8;
        temp_v1_7->unk_0 = 0xE1000000;
        if (unksp2 >= 0) {
            var_a0 = sp10 << 0x10;
        } else {
            if (unksp1A < 0) {
                var_v0_3 = (s32) (unksp2 * unksp1A) >> 7;
                var_v1_2 = (s32) ~var_v0_3 >> 0x1F;
            } else {
                var_v0_3 = (s32) (unksp2 * unksp1A) >> 7;
                var_v1_2 = -(var_v0_3 < 1);
            }
            var_a0 = (sp10 - (var_v0_3 & var_v1_2)) << 0x10;
        }
        if (sp4 >= 0) {
            var_v0_4 = sp14 & 0xFFFF;
        } else if (unksp1E < 0) {
            temp_v0 = (s32) ((s16) sp4 * unksp1E) >> 7;
            var_v0_4 = (sp14 - (temp_v0 & ((s32) ~temp_v0 >> 0x1F))) & 0xFFFF;
        } else {
            temp_v0_2 = (s32) ((s16) sp4 * unksp1E) >> 7;
            var_v0_4 = (sp14 - (temp_v0_2 & -(temp_v0_2 < 1))) & 0xFFFF;
        }
        temp_v1_7->unk_4 = (void *) (var_a0 | var_v0_4);
        temp_a0_2 = *gfxP;
        *gfxP = temp_a0_2 + 8;
        temp_a0_2->unk_0 = 0xF1000000;
        var_v0 = 1;
        temp_a0_2->unk_4 = (void *) ((unksp1A << 0x10) | unksp1E);
        */
        gSPTextureRectangle((*gfxP)++, sp0, sp4, sp8, spC, G_TX_RENDERTILE, sp10, sp14, sp18, sp1C);
        return true;
    }
    return false;
}
#else
INCLUDE_ASM("asm/nonmatchings/main_segment/font", func_8005BB24);
#endif

INCLUDE_ASM("asm/nonmatchings/main_segment/font", fontXX_draw2);

INCLUDE_ASM("asm/nonmatchings/main_segment/font", func_8005BF18);

INCLUDE_ASM("asm/nonmatchings/main_segment/font", func_8005C4BC);

INCLUDE_ASM("asm/nonmatchings/main_segment/font", func_8005C548);

INCLUDE_ASM("asm/nonmatchings/main_segment/font", func_8005C90C);

INCLUDE_ASM("asm/nonmatchings/main_segment/font", func_8005C998);

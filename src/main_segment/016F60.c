#include "ultra64.h"
#include "include_asm.h"
#include "unk.h"
#include "macros_defines.h"
#include "boot_functions.h"
#include "boot_variables.h"
#include "main_segment_functions.h"
#include "main_segment_variables.h"

/**
 * Original name: _modes
 */
const s32 D_800ADB40[] = { G_SC_ODD_INTERLACE, G_SC_EVEN_INTERLACE, G_SC_NON_INTERLACE, G_SC_NON_INTERLACE };

/**
 * Original name: gfxSetScissor
 */
void gfxSetScissor(Gfx **gfxP, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    struct {
        s32 ulx;
        s32 uly;
        s32 lrx;
        s32 lry;
    } corners;
    Gfx *gfx = *gfxP;
    s32 temp_v1;
    s32 temp_v1_2;

    if (arg2 >= 0) {
        if (arg2 < 0x140) {
            corners.ulx = arg2;
        } else {
            corners.ulx = 0x13F;
        }
    } else {
        corners.ulx = 0;
    }

    if (arg3 >= 0) {
        if (arg3 < 0xF0) {
            corners.uly = arg3;
        } else {
            corners.uly = 0xEF;
        }
    } else {
        corners.uly = 0;
    }

    temp_v1 = (arg2 + arg4) - 1;
    if (temp_v1 >= 0) {
        if (temp_v1 < 0x140) {
            corners.lrx = temp_v1;
        } else {
            corners.lrx = 0x13F;
        }
    } else {
        corners.lrx = 0;
    }

    temp_v1_2 = (arg3 + arg5) - 1;
    if (temp_v1_2 >= 0) {
        if (temp_v1_2 < 0xF0) {
            corners.lry = temp_v1_2;
        } else {
            corners.lry = 0xEF;
        }
    } else {
        corners.lry = 0;
    }

    gDPSetScissor(gfx++, D_800ADB40[arg1 % ARRAY_COUNTU(D_800ADB40)], corners.ulx, corners.uly, corners.lrx, corners.lry);
    *gfxP = gfx;
}

INCLUDE_ASM("asm/nonmatchings/main_segment/016F60", func_80040D34);

#ifdef NON_EQUIVALENT
/**
 * Original name: FillRectRGBA
 */
void FillRectRGBA(Gfx **gfxP, s32 x0, s32 y0, s32 x1, s32 y1, s32 red, s32 green, s32 blue, s32 alpha) {
    Gfx *temp_t2;
    Gfx *temp_t2_2;
    Gfx *temp_t2_3;
    s32 temp_a3;
    s32 temp_t0;

    temp_t2 = *gfxP;
    gSPDisplayList(temp_t2, D_8008E748);
    // temp_t2->words.w0 = 0xDE000000;
    // temp_t2->words.w1 = (u32) &D_8008E748;
    // temp_t2_2->words.w0 = 0xFA000000;
    // temp_t2_2->words.w1 = ((u8) arg5 << 0x18) | ((u8) arg6 << 0x10) | ((u8) arg7 << 8) | (u8) arg8;
    gDPSetPrimColor(temp_t2 + 1, 0, 0, red, green, blue, alpha);

    // temp_t2_3->words.w0 = ((temp_a3 & ((s32) ~temp_a3 >> 0x1F) & 0x3FF) << 0xE) | (((temp_t0 & ((s32) ~temp_t0 >> 0x1F) & 0x3FF) * 4) | -0x0A000000);
    // temp_t2_3->words.w1 = ((arg1 & ((s32) ~arg1 >> 0x1F) & 0x3FF) << 0xE) | ((arg2 & ((s32) ~arg2 >> 0x1F) & 0x3FF) * 4);
    gDPFillRectangle(temp_t2 + 2, x0, y0, x0 + x1, y0 + y1);
    *gfxP = temp_t2 + 2;
    // return -0x0A000000;
}
#else
INCLUDE_ASM("asm/nonmatchings/main_segment/016F60", FillRectRGBA);
#endif

INCLUDE_ASM("asm/nonmatchings/main_segment/016F60", func_80040F34);

INCLUDE_ASM("asm/nonmatchings/main_segment/016F60", func_8004113C);

INCLUDE_ASM("asm/nonmatchings/main_segment/016F60", func_80041334);

INCLUDE_ASM("asm/nonmatchings/main_segment/016F60", func_80041480);

INCLUDE_ASM("asm/nonmatchings/main_segment/016F60", func_80041668);

INCLUDE_ASM("asm/nonmatchings/main_segment/016F60", func_800417B4);

INCLUDE_ASM("asm/nonmatchings/main_segment/016F60", func_8004199C);

#if 0
void func_80041A54(struct_80041A54_arg0 *arg0) {
    s32 sp10;
    s32 sp14;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 var_a0;
    s32 var_a2;
    s32 var_s2;
    s32 var_s3;
    s32 var_s4;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v0_3;
    s32 var_v0_4;
    void **temp_a0;
    void **temp_a0_2;
    void *temp_s1;
    void *temp_v1;
    void *temp_v1_2;

    temp_v0 = arg0->unk_28;
    var_a2 = -temp_v0;
    if (temp_v0 < 0) {
        var_v0 = -1;
        goto block_4;
    }
    var_a2 = temp_v0;
    if (temp_v0 > 0) {
        var_v0 = 1;
block_4:
        sp10 = var_v0;
        temp_v0_2 = arg0->unk_2C;
        var_s2 = -temp_v0_2;
        if (temp_v0_2 < 0) {
            var_v0_2 = -1;
            goto block_8;
        }
        var_s2 = temp_v0_2;
        if (temp_v0_2 > 0) {
            var_v0_2 = 1;
block_8:
            sp14 = var_v0_2;
            if ((arg0->unk_4 == 0) && (var_a2 == (arg0->unk_8 * 4)) && (var_s2 == (arg0->unk_C * 4))) {
                temp_a0 = arg0->unk_0;
                temp_v1 = *temp_a0;
                *temp_a0 = temp_v1 + 8;
                temp_v1->unk_0 = 0xE3001201;
                temp_v1->unk_4 = 0;
                var_s3 = arg0->unk_38;
                var_s4 = 0;
            } else {
                temp_a0_2 = arg0->unk_0;
                temp_v1_2 = *temp_a0_2;
                *temp_a0_2 = temp_v1_2 + 8;
                temp_v1_2->unk_0 = 0xE3001201;
                temp_v1_2->unk_4 = 0x2000;
                var_s3 = arg0->unk_38 - 1;
                var_s4 = -1;
                if (var_s3 <= 0) {
                    var_s3 = 1;
                }
            }
            arg0->unk_4C = (s32) arg0->unk_20;
            arg0->unk_54 = (s32) (arg0->unk_20 + var_a2);
            temp_s1 = arg0 + 0x4C;
            if (sp10 < 0) {
                var_v0_3 = (arg0->unk_8 - 1) << 5;
            } else {
                var_v0_3 = 0;
            }
            temp_s1->unk_10 = var_v0_3;
            temp_s1->unk_18 = (s32) ((s32) ((sp10 << 0xC) * arg0->unk_8) / var_a2);
            arg0->unk_40 = 0;
            if (arg0->unk_C > 0) {
                do {
                    var_a0 = arg0->unk_40 + arg0->unk_38;
                    if (arg0->unk_C < var_a0) {
                        var_a0 = arg0->unk_C;
                    }
                    arg0->unk_44 = var_a0;
                    arg0->unk_48 = (s32) (var_a0 - arg0->unk_40);
                    if (arg0->unk_10 != 0) {
                        arg0->unk_30(arg0, arg0->unk_C);
                    }
                    if (arg0->unk_18 != 0) {
                        arg0->unk_34(arg0);
                    }
                    if (sp14 < 0) {
                        temp_s1->unk_4 = (s32) (arg0->unk_C - arg0->unk_44);
                        temp_s1->unk_C = (s32) (arg0->unk_C - arg0->unk_40);
                        temp_s1->unk_14 = (s32) (arg0->unk_48 - 1);
                    } else {
                        temp_s1->unk_4 = (s32) arg0->unk_40;
                        temp_s1->unk_14 = 0;
                        temp_s1->unk_C = (s32) arg0->unk_44;
                    }
                    temp_s1->unk_4 = (s32) (arg0->unk_24 + ((s32) (temp_s1->unk_4 * 4 * var_s2) / (s32) (arg0->unk_C * 4)));
                    temp_s1->unk_14 = (s32) (temp_s1->unk_14 << 5);
                    temp_s1->unk_C = (s32) (arg0->unk_24 + ((s32) (temp_s1->unk_C * 4 * var_s2) / (s32) (arg0->unk_C * 4)));
                    var_v0_4 = (s32) ((sp14 << 0xC) * arg0->unk_C) / var_s2;
                    temp_s1->unk_1C = var_v0_4;
                    if (var_v0_4 < 0) {
                        var_v0_4 += 0x3F;
                    }
                    temp_s1->unk_14 = (s32) (temp_s1->unk_14 - ((var_v0_4 >> 6) & var_s4));
                    arg0->unk_3C(arg0);
                    temp_v0_3 = arg0->unk_40 + var_s3;
                    arg0->unk_40 = temp_v0_3;
                } while (temp_v0_3 < arg0->unk_C);
            }
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/main_segment/016F60", func_80041A54);
#endif

INCLUDE_ASM("asm/nonmatchings/main_segment/016F60", func_80041DE0);

void func_80041F94(struct_80041A54_arg0 *arg0) {
    gDPLoadTextureBlock((*arg0->unk_00)++, (u16 *)arg0->unk_10 + (arg0->unk_14 * arg0->unk_40), G_IM_FMT_RGBA, G_IM_SIZ_16b, arg0->unk_14, arg0->unk_48, 0,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
}

void func_8004216C(struct_80041A54_arg0 *arg0) {
    gDPLoadMultiBlock_4b((*arg0->unk_00)++, arg0->unk_18 + (arg0->unk_1C * arg0->unk_40) / 2, 0x19A, 1, G_IM_FMT_I, arg0->unk_1C, arg0->unk_48, 0,
                         G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
}

#ifdef NON_MATCHING
void func_80042364(Gfx **gfxP, s32 arg1, s32 arg2, UNK_PTR arg3, s32 arg4, s32 arg5, s32 arg6, f32 arg7, f32 arg8, f32 arg9, f32 argA) {
    struct_80041A54_arg0 sp10;

    sp10.unk_00 = gfxP;
    sp10.unk_04 = 0;
    sp10.unk_08 = arg1;
    sp10.unk_0C = arg2;
    sp10.unk_10 = arg3;
    sp10.unk_14 = arg4;
    sp10.unk_18 = arg5;
    sp10.unk_1C = arg6;
    sp10.unk_30 = func_80041F94;
    sp10.unk_34 = func_8004216C;
    sp10.unk_20 = arg7 * 4.0;
    sp10.unk_24 = arg8 * 4.0;
    sp10.unk_28 = arg9 * 4.0;
    sp10.unk_2C = argA * 4.0;
    if (arg4 < arg6) {
        arg4 = arg6;
    }
    sp10.unk_38 = 0x660 / arg4;
    sp10.unk_3C = func_80041DE0;
    func_80041A54(&sp10);
}
#else
INCLUDE_ASM("asm/nonmatchings/main_segment/016F60", func_80042364);
#endif

void func_80042468(struct_80041A54_arg0 *arg0) {
    gDPLoadTextureBlock_4b((*arg0->unk_00)++, arg0->unk_10 + ((arg0->unk_14 * arg0->unk_40) / 2), G_IM_FMT_CI, arg0->unk_14, arg0->unk_48, 0,
                           G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
}

void func_80042650(Gfx **gfxP, s32 arg1, s32 arg2, TexturePtr tlut, UNK_PTR arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8) {
    struct_80041A54_arg0 sp10;

    sp10.unk_00 = gfxP;
    sp10.unk_04 = 0;
    sp10.unk_08 = arg1;
    sp10.unk_0C = arg2;
    sp10.unk_14 = arg1;
    sp10.unk_18 = 0;
    sp10.unk_1C = 0;
    sp10.unk_34 = NULL;
    sp10.unk_30 = func_80042468;
    sp10.unk_3C = func_80041DE0;
    sp10.unk_10 = arg4;
    sp10.unk_20 = arg5 * 4.0;
    sp10.unk_24 = arg6 * 4.0;
    sp10.unk_28 = arg7 * 4.0;
    sp10.unk_2C = arg8 * 4.0;
    sp10.unk_38 = 0x1000 / arg1;
    if (tlut != NULL) {
        gDPLoadTLUT_pal16((*gfxP)++, 0, tlut);
    }
    func_80041A54(&sp10);
}

void func_800427E0(struct_80041A54_arg0 *arg0) {
    gDPLoadTextureBlock((*arg0->unk_00)++, arg0->unk_10 + (arg0->unk_14 * arg0->unk_40), G_IM_FMT_CI, G_IM_SIZ_8b, arg0->unk_14, arg0->unk_48, 0,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
}

void func_800429B8(Gfx **gfxP, s32 arg1, s32 arg2, TexturePtr tlut, UNK_PTR arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8) {
    struct_80041A54_arg0 sp10;

    sp10.unk_00 = gfxP;
    sp10.unk_04 = 0;
    sp10.unk_30 = func_800427E0;
    sp10.unk_08 = arg1;
    sp10.unk_0C = arg2;
    sp10.unk_14 = arg1;
    sp10.unk_18 = 0;
    sp10.unk_1C = 0;
    sp10.unk_34 = NULL;
    sp10.unk_3C = func_80041DE0;
    sp10.unk_10 = arg4;
    sp10.unk_20 = arg5 * 4.0;
    sp10.unk_24 = arg6 * 4.0;
    sp10.unk_28 = arg7 * 4.0;
    sp10.unk_2C = arg8 * 4.0;
    sp10.unk_38 = 0x800 / arg1;
    if (tlut != NULL) {
        gDPLoadTLUT_pal256((*gfxP)++, tlut);
    }
    func_80041A54(&sp10);
}

void func_80042B48(struct_80041A54_arg0 *arg0) {
    gDPLoadTextureBlock((*arg0->unk_00)++, (u16 *)arg0->unk_10 + (arg0->unk_14 * arg0->unk_40), G_IM_FMT_RGBA, G_IM_SIZ_16b, arg0->unk_14, arg0->unk_48, 0,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
}

void func_80042D20(Gfx **gfxP, s32 arg1, s32 arg2, UNK_PTR arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7) {
    struct_80041A54_arg0 sp10;

    sp10.unk_00 = gfxP;
    sp10.unk_30 = func_80042B48;
    sp10.unk_04 = 0;
    sp10.unk_08 = arg1;
    sp10.unk_0C = arg2;
    sp10.unk_10 = arg3;
    sp10.unk_14 = arg1;
    sp10.unk_18 = 0;
    sp10.unk_1C = 0;
    sp10.unk_34 = NULL;
    sp10.unk_3C = func_80041DE0;
    sp10.unk_20 = arg4 * 4.0;
    sp10.unk_24 = arg5 * 4.0;
    sp10.unk_28 = arg6 * 4.0;
    sp10.unk_2C = arg7 * 4.0;
    sp10.unk_38 = 0x800 / arg1;
    func_80041A54(&sp10);
}

void func_80042E04(struct_80041A54_arg0 *arg0) {
    gDPLoadTextureBlock_4b((*arg0->unk_00)++, arg0->unk_10 + (arg0->unk_14 * arg0->unk_40) / 2, G_IM_FMT_I, arg0->unk_14, arg0->unk_48, 0,
                           G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
}

void func_80042FEC(Gfx **gfxP, s32 arg1, s32 arg2, UNK_PTR arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7) {
    struct_80041A54_arg0 sp10;

    sp10.unk_00 = gfxP;
    sp10.unk_30 = func_80042E04;
    sp10.unk_04 = 0;
    sp10.unk_08 = arg1;
    sp10.unk_0C = arg2;
    sp10.unk_10 = arg3;
    sp10.unk_14 = arg1;
    sp10.unk_18 = 0;
    sp10.unk_1C = 0;
    sp10.unk_34 = NULL;
    sp10.unk_3C = func_80041DE0;
    sp10.unk_20 = arg4 * 4.0;
    sp10.unk_24 = arg5 * 4.0;
    sp10.unk_28 = arg6 * 4.0;
    sp10.unk_2C = arg7 * 4.0;
    sp10.unk_38 = 0x2000 / arg1;
    func_80041A54(&sp10);
}

void func_800430D0(struct_80041A54_arg0 *arg0) {
    gDPLoadTextureBlock((*arg0->unk_00)++, arg0->unk_10 + (arg0->unk_14 * arg0->unk_40), G_IM_FMT_I, G_IM_SIZ_8b, arg0->unk_14, arg0->unk_48, 0,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
}

void func_800432A8(Gfx **gfxP, s32 arg1, s32 arg2, UNK_PTR arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7) {
    struct_80041A54_arg0 sp10;

    sp10.unk_00 = gfxP;
    sp10.unk_30 = func_800430D0;
    sp10.unk_04 = 0;
    sp10.unk_08 = arg1;
    sp10.unk_0C = arg2;
    sp10.unk_10 = arg3;
    sp10.unk_14 = arg1;
    sp10.unk_18 = 0;
    sp10.unk_1C = 0;
    sp10.unk_34 = NULL;
    sp10.unk_3C = func_80041DE0;
    sp10.unk_20 = arg4 * 4.0;
    sp10.unk_24 = arg5 * 4.0;
    sp10.unk_28 = arg6 * 4.0;
    sp10.unk_2C = arg7 * 4.0;
    sp10.unk_38 = 0x1000 / arg1;
    func_80041A54(&sp10);
}

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

/**
 * Original name: tiLoadTexData
 */
s32 tiLoadTexData(struct_80124610 **arg0, u32 segmentRom, u32 segmentRomEnd) {
    s32 *temp_v0;
    struct_80124610 *temp_s0;
    s32 temp_s1;

    temp_s0 = (void*)ALIGN16((uintptr_t)*arg0);
    *arg0 = DecompressRomToRam(segmentRom, (void *) temp_s0, segmentRomEnd - segmentRom);
    temp_s1 = temp_s0->unk_00 + (uintptr_t)temp_s0;
    temp_v0 = temp_s0->unk_04 + (uintptr_t)temp_s0;
    temp_s0->unk_00 = temp_s1;
    temp_s0->unk_04 = temp_v0;
    func_8004502C(temp_s1, *temp_v0, temp_s0);
    return temp_s1;
}
#else
INCLUDE_ASM("asm/nonmatchings/main_segment/016F60", tiLoadTexData);
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

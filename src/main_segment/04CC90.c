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
#include "buffers.h"

INCLUDE_ASM("asm/nonmatchings/main_segment/04CC90", func_800768E0);

void func_80076CA0(struct_80076CA0_arg0 *arg0, struct_800E8750 *arg1) {
    arg0->unk_04 = arg1->unk_008;
    arg0->unk_08 = arg1->unk_00A;
    arg0->unk_00 = arg1->unk_00E;
    arg0->unk_0C = &arg1->unk_010;
    arg0->unk_10 = &arg1->unk_210;
}

INCLUDE_ASM("asm/nonmatchings/main_segment/04CC90", func_80076CCC);

INCLUDE_ASM("asm/nonmatchings/main_segment/04CC90", func_80076DB4);

void func_800770E8(Gfx **gfxP, struct_800E8750 *arg1) {
    Gfx *gfx = *gfxP;

    gSPDisplayList(gfx++, normal_texture_init_dl);
    func_800429B8(&gfx, 0x148, 0xF0, &arg1->unk_010, &arg1->unk_210, 0.0f, 0.0f, 328.0f, 240.0f);
    *gfxP = gfx;
}

void *func_80077170(s32 index, void *dstAddr) {
    bgGraphic = dstAddr;
    B_800E8750 = (void *)ALIGN16((uintptr_t)DecompressRomToRam(D_8000E778[index].start, dstAddr, D_8000E778[index].end - D_8000E778[index].start));
    return (void *)ALIGN16((uintptr_t)DecompressRomToRam(D_8000E760.start, B_800E8750, D_8000E760.end - D_8000E760.start));
}

INCLUDE_ASM("asm/nonmatchings/main_segment/04CC90", func_800771EC);

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
    msgWnd_clear(&B_800E59F0);
    D_800AAD1C = 0;
    D_800AAD24 = 0;
    D_800AAD08 = 0;
    D_800AAD24 = 0;
    D_800AAD0C++;
}

bool func_800774C4(void) {
    bool temp_v0 = msgWnd_isEnd(&B_800E59F0);

    if (temp_v0) {
        func_8007746C();
    }
    return temp_v0;
}

#ifdef NON_EQUIVALENT
void story_spot(Gfx **gfxP, s32 arg1, s32 arg2, s32 arg3, UNK_PTR arg4) {
    // Gfx *sp38;
    // Gfx *temp_a0;
    // Gfx *temp_a0_2;
    Gfx *temp_t0;
    // Gfx *temp_v1;
    // Gfx *temp_v1_2;
    // Gfx *temp_v1_3;
    // Gfx *temp_v1_4;
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

    temp_t0 = *gfxP;
    // sp38 = temp_t0;
    if (arg3 < 0xFF) {
        temp_a3 = arg3 & ((s32)~arg3 >> 0x1F);
        temp_f10 = (f32)((f64)(f32)((f64)(f32)temp_a3 / 18.0) * 64.0);
        // sp38 = temp_t0 + 8;
        temp_f16 = (f32)((f64)(f32)arg1 - temp_f10 / 2.0);
        // temp_t0->words.w0 = 0xE3001001;
        // temp_t0->words.w1 = 0;
        // sp38 = temp_t0 + 0x10;
        temp_f14 = (f32)((f64)(f32)arg2 - temp_f10 / 2.0);
        // temp_t0->unk_8 = 0xFA000000;
        // temp_t0->unk_C = 0xFF;
        // sp38 = temp_t0 + 0x18;
        // temp_t0->unk_10 = 0xE200001CU;
        // temp_t0->unk_14 = 0x0F0A4000;
        // sp38 = temp_t0 + 0x20;
        // temp_t0->unk_18 = 0xFCFFFFFF;
        // temp_t0->unk_1C = 0xFFFDF6FB;

        gDPSetTextureLUT(temp_t0++, G_TT_NONE);
        gDPSetPrimColor(temp_t0++, 0, 0, 0, 0, 0, 255);
        gDPSetRenderMode(temp_t0++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
        gDPSetCombineMode(temp_t0++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);

        temp_f8 = (s32)(temp_f16 + 1.0f);
        temp_f6 = (s32)((temp_f16 + temp_f10) - 1.0f);
        temp_f4_2 = (s32)(temp_f14 + 1.0f);
        temp_f2 = (s32)((temp_f14 + temp_f10) - 1.0f);

        // var_t1 = (temp_f10 < 1.0f);
        // var_v0 = (temp_f10 < 1.0f);
        // PROBLEM HERE
        if (!(temp_a3 & -(((temp_f10 < 1.0f) | (temp_f10 < 1.0f))))) {
            // sp38 = temp_t0 + 0x28;
            // temp_t0->unk_20 = 0xF65003C0;
            // temp_t0->unk_24 = 0;
            gDPFillRectangle(temp_t0++, 0, 0, 320, 240);
        } else {
            if (temp_f8 > 0) {
                // sp38 = temp_t0 + 0x28;
                // temp_t0->unk_20 = (s32) (((temp_f8 & 0x3FF) << 0xE) | 0xF60003C0);
                // temp_t0->unk_24 = 0;
                gDPFillRectangle(temp_t0++, 0, 0, temp_f8, 240);
            }
            if (temp_f6 < 0x140) {
                // temp_v1 = sp38;
                // sp38 = temp_v1 + 8;
                // temp_v1->words.w0 = 0xF65003C0;
                // temp_v1->words.w1 = (temp_f6 & 0x3FF) << 0xE;
                gDPFillRectangle(temp_t0++, temp_f6, 0, 320, 240);
            }
            if (temp_f4_2 > 0) {
                // temp_a0 = sp38;
                // sp38 = temp_a0 + 8;
                // temp_a0->words.w0 = ((temp_f4_2 & 0x3FF) * 4) | 0xF6500000;
                // temp_a0->words.w1 = 0;
                gDPFillRectangle(temp_t0++, 0, 0, 320, temp_f4_2);
            }
            if (temp_f2 < 0xF0) {
                // temp_v1_2 = sp38;
                // sp38 = temp_v1_2 + 8;
                // temp_v1_2->words.w0 = 0xF65003C0;
                // temp_v1_2->words.w1 = (temp_f2 & 0x3FF) * 4;
                gDPFillRectangle(temp_t0++, 0, temp_f2, 320, 240);
            }
            // temp_v1_3 = sp38;
            // sp38 = temp_v1_3 + 8;
            // temp_v1_3->words.w0 = 0xE200001C;
            // temp_v1_3->words.w1 = 0x00504240;
            // sp38 = temp_v1_3 + 0x10;
            // temp_v1_3->unk_8 = 0xFCFFFFFF;
            // temp_v1_3->unk_C = 0xFFFDF2F9;
            gDPSetRenderMode(temp_t0++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
            gDPSetCombineLERP(temp_t0++, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0);
            StretchTexBlock4i(&temp_t0, 0x40, 0x40, arg4, temp_f16, temp_f14, temp_f10, temp_f10);
        }
        // temp_v1_4 = sp38;
        // temp_a0_2 = temp_v1_4 + 8;
        // sp38 = temp_a0_2;
        // temp_v1_4->words.w0 = 0xDE000000;
        // temp_v1_4->words.w1 = (u32) normal_texture_init_dl;
        gSPDisplayList(temp_t0++, normal_texture_init_dl);
        *gfxP = temp_t0;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/main_segment/04CC90", story_spot);
#endif

void func_800777E8(Gfx **gfxP, s32 arg1, s32 arg2, s32 arg3) {
    story_spot(gfxP, arg1, arg2, arg3, &changestar_tex);
}

void *func_8007780C(void *dstAddr) {
    void *temp_s0;

    bgGraphic = (void *)ALIGN16((uintptr_t)dstAddr);
    temp_s0 = (void *)ALIGN16((uintptr_t)DecompressRomToRam(D_8000E740.start, bgGraphic, D_8000E740.end - D_8000E740.start));
    init_coffee_break_cnt();
    return temp_s0;
}

void init_coffee_break_cnt(void) {
    guOrtho(&story_viewMtx, -160.0f, 160.0f, -120.0f, 120.0f, 1.0f, 2000.0f, 1.0f);
    D_800AAD34 = 0x15E;
    bgtime = 0;
    D_800AAD08 = -0x59;
    D_800AAD0C = 0;
}

INCLUDE_ASM("asm/nonmatchings/main_segment/04CC90", func_800778E8);

void *init_menu_bg(void *dstAddr, bool arg1) {
    void *alignedAddress;
    romoffset_t segmentRomStart;
    romoffset_t segmentRomEnd;

    bgtime = 0;
    guOrtho(&story_viewMtx, -160.0f, 160.0f, -120.0f, 120.0f, 1.0f, 2000.0f, 1.0f);
    alignedAddress = ALIGN_PTR(dstAddr);
    bgGraphic = alignedAddress;
    if (arg1) {
        segmentRomStart = D_8000E750.start; // PTR_segment_menu_bg2_002b0070
        segmentRomEnd = D_8000E750.end;     // PTR_DAT_002b0074
    } else {
        segmentRomStart = D_8000E748.start; // PTR_segment_menu_bg_002b0068
        segmentRomEnd = D_8000E748.end;     // )PTR_DAT_002b006c
    }
    return ALIGN_PTR(DecompressRomToRam(segmentRomStart, alignedAddress, segmentRomEnd - segmentRomStart));
}

#if 0
void draw_menu_bg(Gfx **gfxP, s32 arg1, s32 arg2) {
    Mtx sp18;
    Gfx *sp58;
    Gfx *temp_a0;
    Gfx *temp_s0;
    Gfx *temp_v1;
    Gfx *temp_v1_2;

    init_objMtx();
    temp_s0 = *arg0;
#if 0
    sp58 = temp_s0 + 8;
    temp_s0->words.w0 = 0xDB060000;
    temp_s0->words.w1 = 0;
    sp58 = temp_s0 + 0x10;
    temp_s0->unk_8 = 0xDB060014;
    temp_v1 = sp58;
    temp_s0->unk_C = osVirtualToPhysical(bgGraphic);
    sp58 = temp_v1 + 8;
    temp_v1->words.w1 = (u32) &D_E5F08;
    temp_v1->words.w0 = 0xDA380007;
    sp58 = temp_v1 + 0x10;
    temp_v1->unk_C = normal_texture_init_dl;
    temp_v1->unk_8 = 0xDE000000;
    sp58 = temp_v1 + 0x18;
    temp_v1->unk_14 = D_800AAD68;
    temp_v1->unk_10 = 0xDE000000;
    sp58 = temp_v1 + 0x20;
    temp_v1->unk_18 = 0xED000000;
    temp_v1->unk_1C = 0x004FC3BC;
#endif
    gSPSegment(temp_s0++, 0x00, 0x00000000);
    gSPSegment(temp_s0++, 0x05, osVirtualToPhysical(bgGraphic));
    gSPMatrix(temp_s0++, OS_K0_TO_PHYSICAL(&story_viewMtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gSPDisplayList(temp_s0++, normal_texture_init_dl);
    gSPDisplayList(temp_s0++, D_800AAD68);
    gDPSetScissor(temp_s0++, G_SC_NON_INTERLACE, 0, 0, 319, 239);

    makeTransrateMatrix(&sp18, arg1 << 0xF, arg2 << 0xF, -0x03B60000);
    if (lws_anim(&sp58, &sp18, bgGraphic, bgtime, bgGraphic) == 1) {
        bgtime = 0;
    } else {
        bgtime += 1;
    }
    //temp_v1_2 = sp58;
    //temp_a0 = temp_v1_2 + 8;
    //sp58 = temp_a0;
    //temp_v1_2->words.w0 = 0xDE000000;
    //temp_v1_2->words.w1 = (u32) normal_texture_init_dl;
    gSPDisplayList(temp_s0++, normal_texture_init_dl);
    *arg0 = temp_s0;
}
#else
INCLUDE_ASM("asm/nonmatchings/main_segment/04CC90", draw_menu_bg);
#endif

/**
 * Original name: init_title
 */
void *init_title(void *dstAddr, bool arg1) {
    if (arg1) {
        title_time = 0;
        story_spot_cnt = -0x64;
    } else {
        title_time = 0x2D0;
        story_spot_cnt = 0x100;
    }

    title_wait = 0;
    guOrtho(&story_viewMtx, -160.0f, 160.0f, -120.0f, 120.0f, 1.0f, 2000.0f, 1.0f);

    title_data = ALIGN_PTR(dstAddr);
    title_bmp_data = ALIGN_PTR(DecompressRomToRam(gSegmentRomOffset_segment_title_all.start, title_data,
                                                  gSegmentRomOffset_segment_title_all.end - gSegmentRomOffset_segment_title_all.start));
    return ALIGN_PTR(DecompressRomToRam(gSegmentRomOffset_segment_title_bmp.start, title_bmp_data,
                                        gSegmentRomOffset_segment_title_bmp.end - gSegmentRomOffset_segment_title_bmp.start));
}

/**
 * Original name: demo_title
 */
s32 demo_title(Gfx **gfxP, bool arg1) {
    struct_80076CA0_arg0 sp30;
    struct_80076CA0_arg0 sp48;
    Mtx sp60;
    Gfx *gfx;
    s32 temp_s2;
    s32 temp_v1_2;
    s32 var_s3;
    s32 var_v0_3;

    init_objMtx();
    var_s3 = 0;
    gfx = *gfxP;

    gSPSegment(gfx++, 0x00, 0x00000000);
    temp_s2 = (title_time >= 0x2D0);
    gSPSegment(gfx++, 0x05, osVirtualToPhysical(title_data));
    gSPMatrix(gfx++, OS_K0_TO_PHYSICAL(&story_viewMtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gSPDisplayList(gfx++, normal_texture_init_dl);
    gSPDisplayList(gfx++, D_800AAD68);
    gDPSetScissor(gfx++, G_SC_NON_INTERLACE, 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1);

    lws_data = title_data;
    if (arg1) {
        gDPSetEnvColor(gfx++, 183, 127, 95, 255);

        lws_scene = (void *)((uintptr_t)title_data + (((uintptr_t)title_data[0x21]) & 0xFFFFFF));
    } else {
        gDPSetEnvColor(gfx++, 255, 255, 255, 255);

        lws_scene = (void *)((((uintptr_t)title_data[0]) & 0xFFFFFF) + (uintptr_t)title_data);
    }

    makeTransrateMatrix(&sp60, 0, 0xFFC4 << 16, 0xFC4A << 16);
    if ((story_spot_cnt > 0) && (gControllerPressedButtons[B_800EBD16[0]] & ALL_BUTTONS)) {
        if (temp_s2 != 0) {
            if (title_wait == 0) {
                dm_snd_play(SND_INDEX_103);
                title_wait = 1;
            }
        } else {
            title_time = 0x2D0;
        }
    }

    if (title_wait > 0) {
        title_wait++;
        if (title_wait >= 0x3C) {
            var_s3 = 1;
        }
    }

    if (lws_anim(&gfx, &sp60, lws_scene, title_time, title_data) == 1) {
        var_s3 = -1;
    }

    gSPDisplayList(gfx++, normal_texture_init_dl);
    if (story_spot_cnt > 0) {
        title_time++;
    }

    if (story_spot_cnt < 0x100) {
        gSPDisplayList(gfx++, normal_texture_init_dl);
        story_spot(&gfx, 0xA0, 0x78, story_spot_cnt, changestar_tex);

        if (story_spot_cnt < 0) {
            temp_v1_2 = 0xFF;
            if (story_spot_cnt > -0x18) {
                temp_v1_2 = (story_spot_cnt * -0xFF) / 24;
                if (temp_v1_2 > 0xFF) {
                    temp_v1_2 = 0xFF;
                }
                temp_v1_2 = temp_v1_2 & (~temp_v1_2 >> 0x1F);
            }
            if (story_spot_cnt < -0x4C) {
                temp_v1_2 = 0xFF - (((story_spot_cnt + 0x4C) * -0xFF) / 24);
                if (temp_v1_2 > 0xFF) {
                    temp_v1_2 = 0xFF;
                }
                temp_v1_2 = temp_v1_2 & (~temp_v1_2 >> 0x1F);
            }

            func_80076CA0(&sp30, title_bmp_data + title_bmp_tbl[0]);

            gDPSetTextureLUT(gfx++, G_TT_NONE);
            gDPSetPrimColor(gfx++, 0, 0, temp_v1_2, temp_v1_2, temp_v1_2, 255);
            gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
            gDPSetCombineLERP(gfx++, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0);

            StretchTexBlock4i(&gfx, sp30.unk_04, sp30.unk_08, sp30.unk_10, (0xA0 - (sp30.unk_04 / 2)), (0x78 - (sp30.unk_08 / 2)), sp30.unk_04, sp30.unk_08);
            story_spot_cnt += 1;
        } else {
            story_spot_cnt += 5;
        }
    }

    var_v0_3 = 1;
    if (title_wait == 0) {
        var_v0_3 = 0x10;
    }

    if ((title_time & var_v0_3) && (title_time > 0x2D0) && (title_wait == 0)) {
        func_80076CA0(&sp30, title_bmp_data + title_bmp_tbl[1]);
        func_80076CA0(&sp48, title_bmp_data + title_bmp_tbl[2]);

        gSPDisplayList(gfx++, alpha_texture_init_dl);
        StretchAlphaTexBlock(&gfx, sp30.unk_04, sp30.unk_08, sp30.unk_10, sp30.unk_04, (s32)sp48.unk_10, sp48.unk_04, 88.0f, 165.0f, sp30.unk_04, sp30.unk_08);
    }

    *gfxP = gfx;
    return var_s3;
}

INCLUDE_ASM("asm/nonmatchings/main_segment/04CC90", func_80078648);

INCLUDE_ASM("asm/nonmatchings/main_segment/04CC90", func_8007865C);

INCLUDE_ASM("asm/nonmatchings/main_segment/04CC90", func_8007873C);

INCLUDE_ASM("asm/nonmatchings/main_segment/04CC90", func_80078F78);

INCLUDE_ASM("asm/nonmatchings/main_segment/04CC90", func_800791D0);

INCLUDE_ASM("asm/nonmatchings/main_segment/04CC90", func_800796F4);

INCLUDE_ASM("asm/nonmatchings/main_segment/04CC90", func_80079B24);

INCLUDE_ASM("asm/nonmatchings/main_segment/04CC90", func_8007A154);

INCLUDE_ASM("asm/nonmatchings/main_segment/04CC90", func_8007A440);

void func_8007A9DC(void) {
    void *ptr;
    size_t segmentSize;

    B_800E87AC = D_800AAD3C;

    segmentSize = gSegmentRomOffset_segment_title_all.end - gSegmentRomOffset_segment_title_all.start;
    ptr = (void *)ALIGN16((uintptr_t)DecompressRomToRam(gSegmentRomOffset_segment_title_all.start, B_800E87AC, segmentSize));
    B_800E8750 = ptr;

    segmentSize = D_8000E758.end - D_8000E758.start;
    ptr = (void *)ALIGN16((uintptr_t)DecompressRomToRam(D_8000E758.start, ptr, segmentSize));
    bgGraphic = ptr;

    segmentSize = D_8000E748.end - D_8000E748.start;
    ptr = (void *)ALIGN16((uintptr_t)DecompressRomToRam(D_8000E748.start, ptr, segmentSize));
    B_800E87B0 = ptr;
}

extern s32 B_800E5A20;
extern s32 B_800E5A24;
extern s32 B_800E5A2C;
extern s32 B_800E5A38;
extern f32 B_800E5A44;
extern MessageWnd B_800E5A70;
extern s32 B_800E5A90;
extern s32 B_800E5A94;
extern s32 B_800E5AA0;
extern s32 B_800E5AA4;
extern s32 B_800E5AAC;
extern s32 B_800E5AB8;
extern f32 B_800E5AC4;
extern void B_800E5AF0;
extern s32 B_800E5EF4;
extern s32 B_800E5EFC;
extern s32 B_800E5F00;
extern u16 story_norm; /* Original name: story_norm */
extern s32 B_800E87B4;
extern s16 B_800F6CDE[];
extern u8 D_80088409;
extern void *D_800A8ACC;

extern UNK_TYPE4 D_800AAE00[];

#ifdef NON_EQUIVALENT
/**
 * Original name: main_story
 */
s32 main_story(struct_800EB670 *arg0) {
    OSMesgQueue sp20;
    void *sp38;
    struct_800FAF98_unk_64 sp58;
    s16 *var_v1;
    s32 var_s1;
    s32 var_s1_2;

    osCreateMesgQueue(&sp20, &sp38, 8);
    func_8002A184(arg0, &sp58, &sp20);
    graphic_no = GRAPHIC_NO_0;
    D_800AAD40 = &D_80205000;
    guPerspective(&story_viewMtx, &story_norm, 45.0f, 1.3333334f, 1.0f, 1000.0f, 1.0f);
    var_s1 = 3;
    guOrtho(&story_viewMtx, -160.0f, 160.0f, -120.0f, 120.0f, 1.0f, 2000.0f, 1.0f);

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
    msgWnd_init(&B_800E59F0, &D_800A8ACC, 0x10, 3, 0x42, 0xB1);
    B_800E5A20 = 0xC;
    B_800E5A24 = 0xC;
    B_800E5A2C = 6;
    B_800E5A38 = 0xE;
    B_800E5EF0 = &D_80205000;
    B_800E5A44 = 0.4f;
    msgWnd_init2(&B_800E5A70, &B_800E5EF0, 0x77A, 0x14, 0xB, 0x28, 0x16);
    B_800E5A94 = 1;
    B_800E5AA0 = 0xC;
    B_800E5AA4 = 0xC;
    B_800E5AAC = 6;
    B_800E5AB8 = 0xE;
    B_800E5A90 = 1;
    B_800E5AC4 = 0.25f;
    func_8007A9DC();
    joyProcCore();
    dm_seq_play(D_800AAE00[story_proc_no]);

    while (B_800E5EFC != 0) {
        osRecvMesg(&sp20, NULL, 1);
        msgWnd_update(&B_800E59F0);
        msgWnd_update(&B_800E5A70);
        if ((D_800AAD28 == 0) && (D_800AAD10 >= 0x5A)) {
            B_800E5EFC = 0;
        }
        joyProcCore();
        graphic_no = GRAPHIC_NO_1;
        dm_audio_update();
    }

    dm_audio_stop();
    graphic_no = GRAPHIC_NO_0;

    while (true) {
        if ((pendingGFX == 0) || dm_audio_is_stopped()) {
            break;
        }
        osRecvMesg(&sp20, NULL, 1);
        dm_audio_update();
    }

    var_s1_2 = 0;
    while (var_s1_2 < 3) {
        osRecvMesg(&sp20, NULL, 1);
        var_s1_2 += 1;
    }

    func_8002A1DC(arg0, &sp58);
    D_80088409 = (u8)story_proc_no;
    if ((s8)story_proc_no >= 0xC) {
        D_80088409 = story_proc_no - 0xC;
    }
    evs_seqnumb = D_80088409 % 3;
    return (D_80088409 / 3) * 3;
}
#else
INCLUDE_ASM("asm/nonmatchings/main_segment/04CC90", main_story);
#endif

/**
 * Original name: init_objMtx
 */
void init_objMtx(void) {
    pObjectMtx = &story_objectMtx[objMtx_FF];
    objMtx_FF ^= 1;
}

#if 0
UNK_TYPE gfxTaskStart(OSScTask *, Gfx *, s32, UNK_TYPE, s32);    /* extern */
UNK_TYPE S2RDPinitRtn(UNK_TYPE);                                 /* extern */
UNK_TYPE S2ClearCFBRtn(UNK_TYPE, s32);                            /* extern */
UNK_TYPE func_800768E0(Gfx **, s32);                       /* extern */
UNK_TYPE func_80076DB4(Gfx **, s32);                       /* extern */
UNK_TYPE func_800770E8(Gfx **, void *);                    /* extern */
UNK_TYPE story_spot(Gfx **, UNK_TYPE, UNK_TYPE, s32, UNK_TYPE *);            /* extern */
UNK_TYPE func_8007873C(Gfx **, UNK_TYPE);                         /* extern */
UNK_TYPE func_80078F78(Gfx **, UNK_TYPE, UNK_TYPE, u32);                 /* extern */
UNK_TYPE func_800791D0(Gfx **, UNK_TYPE, UNK_TYPE, UNK_TYPE, s32);              /* extern */
UNK_TYPE func_800796F4(Gfx **, UNK_TYPE, UNK_TYPE, UNK_TYPE, s32);              /* extern */
UNK_TYPE func_80079B24(Gfx **, UNK_TYPE, UNK_TYPE);                      /* extern */
UNK_TYPE func_8007A154(Gfx **, UNK_TYPE, UNK_TYPE);                      /* extern */
UNK_TYPE func_8007A440(Gfx **, UNK_TYPE);                         /* extern */
extern void *lws_data;
extern struct_80124610 B_800E5A70;
extern f32 B_800E5ACC;
extern s32 B_800E5EFC;
extern s32 B_800E5F00;
extern s8 D_8008840A;
extern UNK_TYPE changestar_tex;
extern UNK_TYPE D_E5F08;

void graphic_story(void) {
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

    gGfxHead = gGfxGlist[B_800FAD2C];
    temp_s1 = &B_800FAE80[B_800FAD2C];
    init_objMtx(B_800FAD2C);
    temp_s0 = gGfxHead;
    gGfxHead = temp_s0 + 8;
    temp_s0->words.w0 = 0xDB060000;
    temp_s0->words.w1 = 0;
    gGfxHead = temp_s0 + 0x10;
    temp_s0->unk_8 = 0xDB060014;
    temp_s0->unk_C = osVirtualToPhysical(D_800AAD3C);
    lws_data = D_800AAD3C;
    S2RDPinitRtn(1);
    temp_v1 = gGfxHead;
    gGfxHead = temp_v1 + 8;
    temp_v1->words.w0 = 0xE7000000;
    gGfxHead = temp_v1 + 0x10;
    temp_v1->unk_C = 0x300000;
    gGfxHead = temp_v1 + 0x18;
    gGfxHead = temp_v1 + 0x20;
    temp_v1->unk_18 = 0xFB000000;
    temp_v1->words.w1 = 0;
    temp_v1->unk_8 = 0xE3000A01;
    temp_v1->unk_10 = 0xE3000A01;
    temp_v1->unk_14 = 0;
    temp_v1->unk_1C = -1;
    S2ClearCFBRtn(1, 0xE3000A01);
    temp_v1_2 = gGfxHead;
    gGfxHead = temp_v1_2 + 8;
    temp_v1_2->words.w0 = 0xDA380007;
    temp_v1_2->words.w1 = (u32) &D_E5F08;
    if (D_800AAD10 > 0) {
        func_800768E0(&gGfxHead, D_800AAD10);
        D_800AAD10 += 1;
    } else {
        switch (story_proc_no) {
        case 0x0:
        case 0xC:
            func_80078F78(&gGfxHead, 1, 0);
            break;
        case 0xA:
            func_80079B24(&gGfxHead, 0x14, 0x1B);
            break;
        case 0xB:
            func_80079B24(&gGfxHead, 0x16, 0x1C);
            break;
        case 0x16:
            func_8007A440(&gGfxHead, 0x17);
            break;
        case 0x17:
            func_8007A440(&gGfxHead, 0x19);
            break;
        case 0x1:
            func_8007873C(&gGfxHead, 1);
            break;
        case 0x2:
            func_800796F4(&gGfxHead, 2, 5, 3, 7);
            break;
        case 0x3:
            var_a1 = 5;
            var_a2 = 9;
block_25:
            gGfxHead += 8;
            gGfxHead->words.w0 = 0xFB000000;
            gGfxHead->words.w1 = 0xAA96B9FF;
            func_80078F78(&gGfxHead, var_a1, var_a2, 0xAA96B9FFU);
            break;
        case 0x4:
            func_800791D0(&gGfxHead, 0x22, 0x1D, 7, 0xB);
            break;
        case 0x5:
            func_80078F78(&gGfxHead, 9, 0xD);
            break;
        case 0x6:
            func_80078F78(&gGfxHead, 0xC, 0xF);
            break;
        case 0x7:
            var_a1_2 = 0x1E;
            if (D_8008840A == 0) {
block_31:
                func_80078F78(&gGfxHead, var_a1_2, 0x19);
            } else {
block_32:
                func_80078F78(&gGfxHead, 0xD, 0x11);
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
            func_800791D0(&gGfxHead, var_a1_3, var_a2_2, 0x10);
            break;
        case 0x9:
            func_80078F78(&gGfxHead, 0x12, 0x14);
            break;
        case 0xD:
            func_8007873C(&gGfxHead, 0);
            break;
        case 0xE:
            func_800796F4(&gGfxHead, 2, 6, 4, 8);
            break;
        case 0xF:
            var_a1 = 6;
            var_a2 = 0xA;
            goto block_25;
        case 0x10:
            func_800791D0(&gGfxHead, 0x22, 0x1D, 8, 0xC);
            break;
        case 0x11:
            func_80078F78(&gGfxHead, 0xA, 0xE);
            break;
        case 0x12:
            func_80078F78(&gGfxHead, 0xB, 0x10);
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
            func_800791D0(&gGfxHead, var_a1_4, var_a2_3, 0x11);
            break;
        case 0x15:
            func_8007A154(&gGfxHead, 0x13, 0x15);
            break;
        }
        func_80076DB4(&gGfxHead, D_800AAD14);
        if (B_800E5F00 == 2) {
            msgWnd_draw(&B_800E5A70, &gGfxHead);
            if (gControllerPressedButtons[*B_800EBD16] & 0x1000) {
                B_800E5F00 = -1;
            }
            if (gControllerHoldButtons[*B_800EBD16] & 0xC000) {
                var_f0 = 0.16666667f;
            } else {
                var_f0 = 0.016666668f;
            }
            B_800E5ACC = var_f0;
        }
        func_800770E8(&gGfxHead, B_800E8750);
        if (D_800AAD20 != 0) {
            msgWnd_draw(&B_800E59F0, &gGfxHead);
            temp_v1_3 = gGfxHead;
            gGfxHead = temp_v1_3 + 8;
            temp_v1_3->words.w0 = 0xED000000;
            temp_v1_3->words.w1 = 0x4FC3BC;
        }
    }
    if (B_800E5F00 < 0) {
        temp_v1_4 = gGfxHead;
        gGfxHead = temp_v1_4 + 8;
        temp_v1_4->words.w0 = 0xDE000000;
        temp_v1_4->words.w1 = (u32) normal_texture_init_dl;
        story_spot(&gGfxHead, 0xA0, 0x78, story_spot_cnt, &changestar_tex);
        temp_v0 = story_spot_cnt - 4;
        story_spot_cnt = temp_v0;
        if (temp_v0 < -0x14) {
            B_800E5EFC = 0;
        }
    }
    temp_v1_5 = gGfxHead;
    D_800AAD08 += 1;
    gGfxHead = temp_v1_5 + 8;
    temp_v1_5->words.w0 = 0xE9000000;
    gGfxHead = temp_v1_5 + 0x10;
    temp_v1_5->words.w1 = 0;
    temp_v1_5->unk_8 = 0xDF000000;
    temp_v1_5->unk_C = 0;
    osWritebackDCacheAll();
    gfxTaskStart(temp_s1, gGfxGlist[B_800FAD2C], ((s32) ((gGfxHead - gGfxGlist) - (B_800FAD2C << 0xF)) >> 3) * 8, 0, 0x40);
}
#else
INCLUDE_ASM("asm/nonmatchings/main_segment/04CC90", graphic_story);
#endif

INCLUDE_ASM("asm/nonmatchings/main_segment/04CC90", func_8007B62C);

/**
 * Original filename: main_story.c
 */

#include "main_story.h"

#include "include_asm.h"
#include "macros_defines.h"
#include "unknown_structs.h"
#include "boot_functions.h"
#include "boot_variables.h"
#include "main_segment_variables.h"
#include "util.h"
#include "rom_offsets.h"
#include "audio/sound.h"
#include "buffers.h"
#include "tex_func.h"
#include "graphic.h"
#include "main1x.h"
#include "nnsched.h"
#include "lws.h"
#include "066840.h"

#if VERSION_US || CC_CHECK
// The compiler needs to not see the declared functions to match the cn version
#include "joy.h"
#endif

extern struct_lws_scene *lws_scene;
extern struct_wakuGraphic *wakuGraphic;

#if VERSION_US || VERSION_CN
/**
 * Original name: story_zoomfade
 */
void story_zoomfade(Gfx **gfxP, s32 arg1) {
    Gfx *gfx = *gfxP;
    u16 *framebuffer = gFramebuffers[gCurrentFramebufferIndex ^ 1];
    f32 temp_fs1_2;
    f32 temp_ft1;
    s32 var_v1;
    f32 temp;
    f32 argA;
    f32 new_var;
    f32 argB;
    f32 temp3;

    gSPDisplayList(gfx++, normal_texture_init_dl);

    gDPSetTextureLUT(gfx++, G_TT_NONE);
    gDPSetTextureFilter(gfx++, G_TF_BILERP);
    gDPSetEnvColor(gfx++, 255, 255, 255, 255);
    gDPSetRenderMode(gfx++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
    gDPSetCombineLERP(gfx++, TEXEL0, ENVIRONMENT, PRIMITIVE, ENVIRONMENT, 0, 0, 0, 1, TEXEL0, ENVIRONMENT, PRIMITIVE,
                      ENVIRONMENT, 0, 0, 0, 1);

    arg1 = MAX(arg1, 0);
    arg1 = MIN(arg1, 0x5A);

    temp_ft1 = arg1;
    temp_ft1 = temp_ft1 / 90.0f;

    if (temp_ft1 > 0.75) {
        temp = (temp_ft1 - 0.75) / (1 / 4.0);
        temp3 = 223.125f;
        temp_fs1_2 = 31.875f;

        var_v1 = (255.0f - temp3 * temp) - temp_fs1_2;
        var_v1 = MAX(var_v1, 0);
    } else {
        var_v1 = (temp_ft1 * 255.0f) / 6.0;
        var_v1 = 0xFF - var_v1;
    }

    gDPSetPrimColor(gfx++, 0, 0, var_v1, var_v1, var_v1, 255);

    temp_fs1_2 = sinf(temp_ft1 * 6.0f) * 1.5;
    temp = cosf(temp_ft1 * 6.0f) * 1.5;
    temp_ft1 = 2.0 * temp_ft1 + 1.0;

    temp_fs1_2 *= temp_ft1;
    temp *= temp_ft1;

    temp_ft1 = 1.0625;
    argA = 320.0 * temp_ft1;
    new_var = 320.0f;
    argB = 240.0 * temp_ft1;
    temp_fs1_2 += (320.0 - argA) / 2;
    temp += (240.0 - argB) / 2;
    StretchTexTile16(&gfx, SCREEN_WIDTH, SCREEN_HEIGHT, framebuffer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, temp_fs1_2,
                     temp, argA, argB);

    gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gDPSetCombineLERP(gfx++, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE);
    gDPSetPrimColor(gfx++, 0, 0, 128, 128, 128, 50);

    StretchTexTile16(&gfx, SCREEN_WIDTH, SCREEN_HEIGHT, framebuffer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f,
                     new_var, 240.0f);

    *gfxP = gfx;
}
#endif

#if VERSION_US || VERSION_CN
void get_gbi_stat(struct_get_gbi_stat_arg0 *arg0, struct_wakuGraphic *arg1) {
    arg0->width = arg1->unk_008;
    arg0->height = arg1->unk_00A;
    arg0->unk_00 = arg1->unk_00E;
    arg0->tlut = &arg1->unk_010;
    arg0->texture = &arg1->unk_210;
}
#endif

#if VERSION_US || VERSION_CN
void curtain_proc(Gfx **gfxP, s32 arg1) {
    Gfx *gfx = *gfxP;
    f32 temp;
    s32 alpha;

    if (arg1 <= 0) {
        return;
    }

    arg1 = MIN(arg1, 30);

    temp = arg1 + 1;
    temp /= 30.0f;

    alpha = temp * 255.0 + 0.5;
    alpha = MIN(alpha, 255);

    gDPSetCombineMode(gfx++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
    gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, alpha);
    gDPFillRectangle(gfx++, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    *gfxP = gfx;
}
#endif

extern u8 curtain_alpha_00_tex[];
extern u16 curtain_00_tex[];

#if VERSION_US || VERSION_CN
void curtain_proc_org(Gfx **gfxP, s32 arg1) {
    Gfx *gfx = *gfxP;
    f32 temp_fv1;
    f32 var_fv0;
    s32 temp_ft3;
    s32 var_t8;
    f32 ftemp;
    f32 ftemp2;
    s32 temp;

    if (arg1 <= 0) {
        return;
    }

    arg1 = MIN(arg1, 0x1E);

    gSPDisplayList(gfx++, alpha_texture_init_dl);
    gDPLoadTextureBlock(gfx++, curtain_00_tex, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 48, 0, G_TX_MIRROR | G_TX_WRAP,
                        G_TX_NOMIRROR | G_TX_CLAMP, 5, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gDPLoadMultiBlock_4b(gfx++, curtain_alpha_00_tex, 0x0180, 1, G_IM_FMT_I, 32, 48, 0, G_TX_MIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_CLAMP, 5, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    ftemp = arg1;
    ftemp /= 30.0f;

    for (var_t8 = 0; var_t8 < 7; var_t8++) {
        temp_fv1 = (6 - var_t8) * 0x28;
        ftemp2 = var_t8 * 8;

        var_fv0 = (ftemp * 280.0f - 48.0) - ftemp2;
        if (temp_fv1 < var_fv0) {
            var_fv0 = temp_fv1;
        }

        temp_ft3 = var_fv0 * 4.0 + 0.5;
        temp = temp_ft3 + 0xC0;

        gSPTextureRectangle(gfx++, 0, temp_ft3, 0x0500, temp, G_TX_RENDERTILE, 0, 0, 0x0400, 0x0400);
    }

    *gfxP = gfx;
}
#endif

#if VERSION_US || VERSION_CN
void func_800770E8(Gfx **gfxP, struct_wakuGraphic *arg1) {
    Gfx *gfx = *gfxP;

    gSPDisplayList(gfx++, normal_texture_init_dl);
    StretchTexBlock8(&gfx, 328, 240, &arg1->unk_010, &arg1->unk_210, 0.0f, 0.0f, 328.0f, 240.0f);
    *gfxP = gfx;
}
#endif

#if VERSION_US || VERSION_CN
void *func_80077170(BgRomDataIndex index, void *dstAddr) {
    bgGraphic = dstAddr;
    wakuGraphic =
        ALIGN_PTR(DecompressRomToRam(bgRomData[index].start, dstAddr, bgRomData[index].end - bgRomData[index].start));
    return ALIGN_PTR(DecompressRomToRam(storyRomData[STORYROMDATA_WAKU2].start, wakuGraphic,
                                        storyRomData[STORYROMDATA_WAKU2].end - storyRomData[STORYROMDATA_WAKU2].start));
}
#endif

extern s32 D_800AAD48[];

#if VERSION_US || VERSION_CN
void story_bg_proc(Gfx **gfxP) {
    struct_get_gbi_stat_arg0 sp48;
    struct_get_gbi_stat_arg0 sp60;
    s32 pad[0x10] UNUSED;
    Gfx *gfx = *gfxP;

    get_gbi_stat(&sp48, bgGraphic);

    gSPDisplayList(gfx++, normal_texture_init_dl);
    StretchTexBlock8(&gfx, sp48.width, sp48.height, sp48.tlut, sp48.texture, 0.0f, 0.0f, sp48.width, sp48.height);

    get_gbi_stat(&sp48, (void *)(((u8 *)wakuGraphic) + D_800AAD48[0]));
    get_gbi_stat(&sp60, (void *)(((u8 *)wakuGraphic) + D_800AAD48[1]));

    gSPDisplayList(gfx++, alpha_texture_init_dl);
    StretchAlphaTexTile(&gfx, sp48.width, sp48.height, sp48.texture, sp48.width, sp60.texture, sp60.width, 0, 0,
                        sp48.width, sp48.height, 0.0f, 140.0f, sp48.width, sp48.height);

    get_gbi_stat(&sp48, (void *)(((u8 *)wakuGraphic) + D_800AAD48[2]));

    gSPDisplayList(gfx++, normal_texture_init_dl);
    StretchTexTile8(&gfx, sp48.width, sp48.height, sp48.tlut, sp48.texture, 0, 0, sp48.width, sp48.height, 0.0f, 160.0f,
                    sp48.width, sp48.height);

    *gfxP = gfx;
}
#endif

#if VERSION_US || VERSION_CN
void func_800773F0(void) {
    if (story_curtain == 0) {
        story_time_cnt = 0;
        story_message_on = 1;
        story_message_start = 0;
        story_seq_step++;
    } else {
        story_message_on = 0;
        story_curtain--;
    }
}
#endif

#if VERSION_US || VERSION_CN
void func_8007744C(void) {
    story_doing = 0;
    story_zoom++;
}
#endif

#if VERSION_US || VERSION_CN
void func_8007746C(void) {
    msgWnd_clear(&mess_st);
    D_800AAD1C = 0;
    story_message_start = 0;
    story_time_cnt = 0;
    story_message_start = 0;
    story_seq_step++;
}
#endif

#if VERSION_US || VERSION_CN
bool func_800774C4(void) {
    bool temp_v0 = msgWnd_isEnd(&mess_st);

    if (temp_v0) {
        func_8007746C();
    }
    return temp_v0;
}
#endif

#if VERSION_US || VERSION_CN
void story_spot(Gfx **gfxP, s32 arg1, s32 arg2, s32 arg3, void *tex) {
    s32 pad[6] UNUSED;
    Gfx *gfx = *gfxP;
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_fv1;
    s32 temp_ft4;
    s32 temp_ft4_2;
    s32 temp_ft4_3;
    s32 temp_ft4_4;
    f32 a;
    f32 b;
    f32 a1;
    f32 a2;

    if (arg3 >= 0xFF) {
        return;
    }

    if (arg3 < 0) {
        arg3 = 0;
    }

    temp_fa0 = ((f32)arg3 / 18.0);
    a1 = arg1;
    a2 = arg2;

    a = temp_fa0 * 64.0;
    b = temp_fa0 * 64.0;

    temp_fa1 = (a1 - a / 2.0);
    temp_fv1 = (a2 - b / 2.0);

    temp_ft4 = temp_fa1 + 1.0f;
    temp_ft4_2 = temp_fa1 + a - 1.0f;
    temp_ft4_3 = temp_fv1 + 1.0f;
    temp_ft4_4 = temp_fv1 + b - 1.0f;

    gDPSetTextureLUT(gfx++, G_TT_NONE);

    gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, 255);

    gDPSetRenderMode(gfx++, G_RM_OPA_SURF, G_RM_OPA_SURF2);

    gDPSetCombineMode(gfx++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);

    if ((a < 1.0f) || (b < 1.0f)) {
        arg3 = 0;
    }

    if (arg3 == 0) {
        gDPFillRectangle(gfx++, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    } else {
        if (temp_ft4 > 0) {
            gDPFillRectangle(gfx++, 0, 0, temp_ft4, SCREEN_HEIGHT);
        }
        if (temp_ft4_2 < SCREEN_WIDTH) {
            gDPFillRectangle(gfx++, temp_ft4_2, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        }
        if (temp_ft4_3 > 0) {
            gDPFillRectangle(gfx++, 0, 0, SCREEN_WIDTH, temp_ft4_3);
        }
        if (temp_ft4_4 < SCREEN_HEIGHT) {
            gDPFillRectangle(gfx++, 0, temp_ft4_4, SCREEN_WIDTH, SCREEN_HEIGHT);
        }

        gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
        gDPSetCombineLERP(gfx++, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0);

        StretchTexBlock4i(&gfx, 0x40, 0x40, tex, temp_fa1, temp_fv1, a, b);
    }

    gSPDisplayList(gfx++, normal_texture_init_dl);

    *gfxP = gfx;
}
#endif

#if VERSION_US || VERSION_CN
void func_800777E8(Gfx **gfxP, s32 arg1, s32 arg2, s32 arg3) {
    story_spot(gfxP, arg1, arg2, arg3, &changestar_tex);
}
#endif

#if VERSION_US || VERSION_CN
void *init_coffee_break(void *dstAddr, UNK_TYPE arg1 UNUSED) {
    void *temp_s0;

    bgGraphic = ALIGN_PTR(dstAddr);
    temp_s0 = ALIGN_PTR(
        DecompressRomToRam(storyRomData[STORYROMDATA_COFFEE_01].start, bgGraphic,
                           storyRomData[STORYROMDATA_COFFEE_01].end - storyRomData[STORYROMDATA_COFFEE_01].start));
    init_coffee_break_cnt();
    return temp_s0;
}
#endif

#if VERSION_US || VERSION_CN
void init_coffee_break_cnt(void) {
    guOrtho(&story_viewMtx, -160.0f, 160.0f, -120.0f, 120.0f, 1.0f, 2000.0f, 1.0f);
    bgtime = 0;
    mes_time = 0x15E;
    story_time_cnt = -0x59;
    story_seq_step = 0;
}
#endif

#if VERSION_US || VERSION_CN
void draw_coffee_break(Gfx **gfxP, s32 arg1, s32 arg2, s32 arg3) {
    Mtx sp20;
    Gfx *sp60;
    bool var_s1;
    void *var_v0;
    void *var_s0;

    init_objMtx();

    sp60 = *gfxP;

    gSPSegment(sp60++, 0x00, 0x00000000);
    gSPSegment(sp60++, 0x05, osVirtualToPhysical(bgGraphic));
    gSPMatrix(sp60++, OS_K0_TO_PHYSICAL(&story_viewMtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gSPDisplayList(sp60++, normal_texture_init_dl);
    gSPDisplayList(sp60++, story_setup);
    gDPSetScissor(sp60++, G_SC_NON_INTERLACE, 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1);

    lws_data = (void **)bgGraphic;
    if (arg2 != 0) {
        gDPSetEnvColor(sp60++, 183, 127, 95, 255);
        var_s0 = RELOCATE_SEGMENTED(lws_data[1], bgGraphic);
        var_v0 = RELOCATE_SEGMENTED(lws_data[6], bgGraphic);
    } else {
        gDPSetEnvColor(sp60++, 255, 255, 255, 255);
        var_s0 = RELOCATE_SEGMENTED(lws_data[0], bgGraphic);
        var_v0 = RELOCATE_SEGMENTED(lws_data[5], bgGraphic);
    }

    makeTransrateMatrix(&sp20, 0U, 0xFFC40000U, 0xFC4A0000U);
    if (lws_anim(&sp60, &sp20, var_s0, bgtime, bgGraphic) == 1) {
        bgtime = 0x31;
    }

    bgtime += 1;
    switch (story_seq_step) {
        case 0:
            var_s0 = RELOCATE_SEGMENTED(lws_data[2], bgGraphic);
            break;

        case 1:
            var_s0 = RELOCATE_SEGMENTED(lws_data[3], bgGraphic);
            break;

        case 2:
            var_s0 = RELOCATE_SEGMENTED(lws_data[4], bgGraphic);
            break;

        default:
            var_s0 = NULL;
            story_time_cnt = -1;
            break;
    }

    var_s1 = false;
    if ((story_time_cnt >= 0) && (var_s0 != NULL)) {
        if (lws_anim(&sp60, &sp20, var_s0, story_time_cnt, bgGraphic) == 1) {
            var_s1 = true;
            story_time_cnt = -1;
            story_seq_step++;
        }
    }

    story_time_cnt++;

    if (var_s1) {
        switch (arg1) {
            case 0:
                story_seq_step = 3;
                break;

            case 1:
                if (story_seq_step == 1) {
                    story_time_cnt = -0x3C;
                } else {
                    story_seq_step = 3;
                }
                break;

            default:
                if (story_seq_step == 1) {
                    story_time_cnt = -0x3C;
                } else if (story_seq_step == 2) {
                    story_time_cnt = -0x28;
                } else {
                    story_seq_step = 3;
                }
                break;
        }
    }

    if (arg3 != 0) {
        if (lws_anim(&sp60, &sp20, var_v0, mes_time, bgGraphic) == 1) {
            mes_time = 0x28A;
        } else {
            mes_time = mes_time + 1;
        }
    }

    gDPSetCycleType(sp60++, G_CYC_1CYCLE);
    gDPSetRenderMode(sp60++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
    gDPSetCombineMode(sp60++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
    gDPSetPrimColor(sp60++, 0, 0, 0, 0, 0, 255);
    gDPFillRectangle(sp60++, 0, 0, SCREEN_WIDTH, 32);
    gDPFillRectangle(sp60++, 0, 208, SCREEN_WIDTH, SCREEN_HEIGHT);
    gSPDisplayList(sp60++, normal_texture_init_dl);

    *gfxP = sp60;
}
#endif

#if VERSION_US || VERSION_CN
void *init_menu_bg(void *dstAddr, bool arg1) {
    void *alignedAddress;
    RomOffset segmentRomStart;
    RomOffset segmentRomEnd;

    bgtime = 0;
    guOrtho(&story_viewMtx, -160.0f, 160.0f, -120.0f, 120.0f, 1.0f, 2000.0f, 1.0f);
    alignedAddress = ALIGN_PTR(dstAddr);
    bgGraphic = alignedAddress;
    if (arg1) {
        segmentRomStart = storyRomData[STORYROMDATA_MENU_BG2].start;
        segmentRomEnd = storyRomData[STORYROMDATA_MENU_BG2].end;
    } else {
        segmentRomStart = storyRomData[STORYROMDATA_MENU_BG].start;
        segmentRomEnd = storyRomData[STORYROMDATA_MENU_BG].end;
    }
    return ALIGN_PTR(DecompressRomToRam(segmentRomStart, alignedAddress, segmentRomEnd - segmentRomStart));
}
#endif

#if VERSION_US || VERSION_CN
void draw_menu_bg(Gfx **gfxP, s32 arg1, s32 arg2) {
    Mtx mtx;
    Gfx *gfx;

    init_objMtx();

    gfx = *gfxP;

    gSPSegment(gfx++, 0x00, 0x00000000);
    gSPSegment(gfx++, 0x05, osVirtualToPhysical(bgGraphic));
    gSPMatrix(gfx++, OS_K0_TO_PHYSICAL(&story_viewMtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gSPDisplayList(gfx++, normal_texture_init_dl);
    gSPDisplayList(gfx++, story_setup);
    gDPSetScissor(gfx++, G_SC_NON_INTERLACE, 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1);

    makeTransrateMatrix(&mtx, arg1 << 0xF, arg2 << 0xF, 0x1F894 << 0xF);
    if (lws_anim(&gfx, &mtx, bgGraphic, bgtime, bgGraphic) == 1) {
        bgtime = 0;
    } else {
        bgtime += 1;
    }

    gSPDisplayList(gfx++, normal_texture_init_dl);

    *gfxP = gfx;
}
#endif

#if VERSION_US || VERSION_CN
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
    title_bmp_data = ALIGN_PTR(
        DecompressRomToRam(storyRomData[STORYROMDATA_TITLE_ALL].start, title_data,
                           storyRomData[STORYROMDATA_TITLE_ALL].end - storyRomData[STORYROMDATA_TITLE_ALL].start));
    return ALIGN_PTR(
        DecompressRomToRam(storyRomData[STORYROMDATA_TITLE_BMP].start, title_bmp_data,
                           storyRomData[STORYROMDATA_TITLE_BMP].end - storyRomData[STORYROMDATA_TITLE_BMP].start));
}
#endif

#if VERSION_US || VERSION_CN
/**
 * Original name: demo_title
 */
s32 demo_title(Gfx **gfxP, bool arg1) {
    struct_get_gbi_stat_arg0 sp30;
    struct_get_gbi_stat_arg0 sp48;
    Mtx sp60;
    Gfx *gfx;
    bool temp_s2;
    s32 temp_v1_2;
    s32 var_s3;
    u32 var_v0_3;

    init_objMtx();

    var_s3 = 0;
    if (title_time >= 720) {
        temp_s2 = true;
    } else {
        temp_s2 = false;
    }

    gfx = *gfxP;

    gSPSegment(gfx++, 0x00, 0x00000000);
    gSPSegment(gfx++, 0x05, osVirtualToPhysical(title_data));
    gSPMatrix(gfx++, OS_K0_TO_PHYSICAL(&story_viewMtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gSPDisplayList(gfx++, normal_texture_init_dl);
    gSPDisplayList(gfx++, story_setup);
    gDPSetScissor(gfx++, G_SC_NON_INTERLACE, 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1);

    lws_data = title_data;
    if (arg1) {
        gDPSetEnvColor(gfx++, 183, 127, 95, 255);

        lws_scene = RELOCATE_SEGMENTED(lws_data[0x21], title_data);
    } else {
        gDPSetEnvColor(gfx++, 255, 255, 255, 255);

        lws_scene = RELOCATE_SEGMENTED(lws_data[0], title_data);
    }

    makeTransrateMatrix(&sp60, 0, 0xFFC4 << 16, 0xFC4A << 16);

    if ((story_spot_cnt > 0) && (gControllerPressedButtons[main_joy[0]] & ANY_BUTTON)) {
        if (temp_s2) {
            if (title_wait == 0) {
                dm_snd_play(SND_INDEX_103);
                title_wait = 1;
            }
        } else {
            title_time = 720;
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
        story_spot(&gfx, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, story_spot_cnt, changestar_tex);

        if (story_spot_cnt < 0) {
            temp_v1_2 = 0xFF;
            if (story_spot_cnt > -0x18) {
                temp_v1_2 = (story_spot_cnt * -0xFF) / 24;
                if (temp_v1_2 > 0xFF) {
                    temp_v1_2 = 0xFF;
                }
                if (temp_v1_2 < 0) {
                    temp_v1_2 = 0;
                }
            }

            if (story_spot_cnt < -0x4C) {
                temp_v1_2 = 0xFF - (((story_spot_cnt + 0x4C) * -0xFF) / 24);
                if (temp_v1_2 >= 0x100) {
                    temp_v1_2 = 0xFF;
                }
                if (temp_v1_2 < 0) {
                    temp_v1_2 = 0;
                }
            }

            get_gbi_stat(&sp30, title_bmp_data + title_bmp_tbl[0]);

            gDPSetTextureLUT(gfx++, G_TT_NONE);
            gDPSetPrimColor(gfx++, 0, 0, temp_v1_2, temp_v1_2, temp_v1_2, 255);
            gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
            gDPSetCombineLERP(gfx++, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0);

            StretchTexBlock4i(&gfx, sp30.width, sp30.height, sp30.texture, SCREEN_WIDTH / 2 - sp30.width / 2,
                              SCREEN_HEIGHT / 2 - sp30.height / 2, sp30.width, sp30.height);

            story_spot_cnt += 1;
        } else {
            story_spot_cnt += 5;
        }
    }

    var_v0_3 = 1;
    if (title_wait == 0) {
        var_v0_3 = 0x10;
    }

    if ((title_time & var_v0_3) && (title_time > 720) && (title_wait == 0)) {
        get_gbi_stat(&sp30, title_bmp_data + title_bmp_tbl[1]);
        get_gbi_stat(&sp48, title_bmp_data + title_bmp_tbl[2]);

        gSPDisplayList(gfx++, alpha_texture_init_dl);
        StretchAlphaTexBlock(&gfx, sp30.width, sp30.height, sp30.texture, sp30.width, sp48.texture, sp48.width, 88.0f,
                             165.0f, sp30.width, sp30.height);
    }

    *gfxP = gfx;
    return var_s3;
}
#endif

#if VERSION_US || VERSION_CN
// unused
void func_80078648(Gfx **gfxP) {
    Gfx *gfx = *gfxP;
    s32 pad[0x1C] UNUSED;

    *gfxP = gfx;
}
#endif

extern s32 st_message_count;

extern s32 fin_frame_543;
extern struct_mes_data *st_mes_ptr;
extern struct_mes_data *mes_data[];

#if VERSION_US || VERSION_CN
void func_8007865C(void) {
    if (st_message_count < st_mes_ptr->unk_0) {
        if (st_mes_ptr[st_message_count + 1].unk_0 < framecont) {
            msgWnd_clear(&mess_st);
            msgWnd_addStr(&mess_st, st_mes_ptr[st_message_count + 1].unk_4);
            st_message_count++;

            if (gControllerHoldButtons[main_joy[0]] & A_BUTTON) {
                msgWnd_skip(&mess_st);
            }
        }
    } else {
        st_message_count = 9999;
    }
}
#endif

extern s32 fin_frame_440;
extern s32 fin_demo_441;

#if VERSION_US || VERSION_CN
void story_st_new_op(Gfx **gfxP, s32 arg1) {
    Gfx *gfx = *gfxP;
    Mtx mtx;
    s32 var_s0;
    s32 var_v0;
    s32 var_v1;

    gSPDisplayList(gfx++, normal_texture_init_dl);
    gSPDisplayList(gfx++, story_setup);

    makeTransrateMatrix(&mtx, 0U, 0xFFF38000U, 0xFC4A0000U);

    switch (story_seq_step) {
        case 0x0:
            if (arg1 != 0) {
                var_s0 = 0x1A;
            } else {
                var_s0 = 0x1B;
            }

            func_800773F0();
            lws_anim(&gfx, &mtx, RELOCATE_SEGMENTED(lws_data[var_s0], story_buffer), 0, story_buffer);
            framecont = 0;
            fin_frame_440 = 0;
            fin_demo_441 = var_s0;
            break;

        case 0x1:
            if (arg1 != 0) {
                var_s0 = 0x1A;
                var_v1 = 0;
            } else {
                var_s0 = 0x1B;
                var_v1 = 1;
            }
            fin_demo_441 = var_s0;
            story_time_cnt = framecont;
            fin_frame_440 = framecont;
            st_mes_ptr = mes_data[var_v1];

            if (gControllerPressedButtons[main_joy[0]] & (B_BUTTON | START_BUTTON)) {
                framecont = 0;
                story_time_cnt = 0;
                st_message_count = 0;
                story_seq_step += 0x63;
            }

            if (gControllerHoldButtons[main_joy[0]] & A_BUTTON) {
                story_time_cnt += 3;
                framecont += 3;
            }

            func_8007865C();
            if (lws_anim(&gfx, &mtx, RELOCATE_SEGMENTED(lws_data[var_s0], story_buffer), story_time_cnt,
                         story_buffer) == 1) {
                if (msgWnd_isEnd(&mess_st)) {
                    framecont = 0;
                    story_time_cnt = 0;
                    st_message_count = 0;
                    story_seq_step += 1;
                }
            }
            break;

        case 0x2:
            var_s0 = 0x1C;
            fin_demo_441 = 0x1C;
            story_time_cnt = framecont;
            fin_frame_440 = framecont;
            st_mes_ptr = mes_data[2];
            if (gControllerPressedButtons[main_joy[0]] & (B_BUTTON | START_BUTTON)) {
                framecont = 0;
                story_time_cnt = 0;
                st_message_count = 0;
                story_seq_step += 0x63;
            }
            if (gControllerHoldButtons[main_joy[0]] & A_BUTTON) {
                story_time_cnt += 3;
                framecont += 3;
            }

            func_8007865C();
            if (lws_anim(&gfx, &mtx, RELOCATE_SEGMENTED(lws_data[var_s0], story_buffer), story_time_cnt,
                         story_buffer) == 1) {
                if (msgWnd_isEnd(&mess_st)) {
                    framecont = 0;
                    story_time_cnt = 0;
                    st_message_count = 0;
                    story_seq_step += 1;
                }
            }

            if (fin_frame_440 > 0x61D) {
                var_v0 = fin_frame_440 - 0x61D;
                var_v0 = ((0x1E - var_v0) * 0xFF) / 30;

                gSPDisplayList(gfx++, normal_texture_init_dl);

                story_spot(&gfx, 0xA0, 0x56, var_v0, changestar_tex);
            }
            break;

        case 0x3:
            var_s0 = 0x1D;
            fin_demo_441 = 0x1D;
            story_time_cnt = framecont;
            fin_frame_440 = framecont;
            st_mes_ptr = mes_data[3];
            if (gControllerPressedButtons[main_joy[0]] & (B_BUTTON | START_BUTTON)) {
                framecont = 0;
                story_time_cnt = 0;
                st_message_count = 0;
                story_seq_step += 0x63;
            }

            if (gControllerHoldButtons[main_joy[0]] & A_BUTTON) {
                story_time_cnt += 3;
                framecont += 3;
            }

            func_8007865C();
            if (lws_anim(&gfx, &mtx, RELOCATE_SEGMENTED(lws_data[var_s0], story_buffer), story_time_cnt,
                         story_buffer) == 1) {
                if (msgWnd_isEnd(&mess_st)) {
                    framecont = 0;
                    story_time_cnt = 0;
                    st_message_count = 0;
                    story_seq_step += 1;
                }
            }

            if (fin_frame_440 < 0x1E) {
                var_v0 = fin_frame_440;
                var_v0 = (var_v0 * 0xFF) / 30;
                gSPDisplayList(gfx++, normal_texture_init_dl);

                story_spot(&gfx, 0xA0, 0x56, var_v0, changestar_tex);
            }
            if (fin_frame_440 > 0x262) {
                var_v0 = fin_frame_440 - 0x262;
                var_v0 = ((0x1E - var_v0) * 0xFF) / 30;

                gSPDisplayList(gfx++, normal_texture_init_dl);

                story_spot(&gfx, 0xA0, 0x56, var_v0, changestar_tex);
            }
            break;

        case 0x4:
            var_s0 = 1;
            fin_demo_441 = 1;
            story_time_cnt = framecont;
            fin_frame_440 = story_time_cnt;
            st_mes_ptr = mes_data[4];
            if (gControllerPressedButtons[main_joy[0]] & (B_BUTTON | START_BUTTON)) {
                story_time_cnt = 0;
                story_seq_step += 1;
            }
            if (gControllerHoldButtons[main_joy[0]] & A_BUTTON) {
                framecont += 3;
                story_time_cnt += 3;
            }

            func_8007865C();
            if (lws_anim(&gfx, &mtx, RELOCATE_SEGMENTED(lws_data[var_s0], story_buffer), story_time_cnt,
                         story_buffer) == 1) {
                if (msgWnd_isEnd(&mess_st)) {
                    story_time_cnt = 0;
                    story_seq_step += 1;
                }
            }
            if (fin_frame_440 < 0x1E) {
                var_v0 = fin_frame_440;
                var_v0 = (var_v0 * 0xFF) / 30;

                gSPDisplayList(gfx++, normal_texture_init_dl);
                story_spot(&gfx, 0xA0, 0x56, var_v0, changestar_tex);
            }
            break;

        default:
            func_8007744C();
            lws_anim(&gfx, &mtx, RELOCATE_SEGMENTED(lws_data[fin_demo_441], story_buffer), fin_frame_440, story_buffer);
            break;
    }

    gDPSetScissor(gfx++, G_SC_NON_INTERLACE, 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1);

    *gfxP = gfx;
}
#endif

#if VERSION_US || VERSION_CN
void story_st_new(Gfx **gfxP, s32 arg1, s32 arg2) {
    Mtx mtx;
    Gfx *gfx = *gfxP;
    void *temp_s1;

    st_mes_ptr = mes_data[arg2];

    gSPDisplayList(gfx++, normal_texture_init_dl);

    gSPDisplayList(gfx++, story_setup);

    makeTransrateMatrix(&mtx, 0, 0x1FFE7 << 0xF, 0x1F894 << 0xF);

    temp_s1 = RELOCATE_SEGMENTED(lws_data[arg1], story_buffer);

    switch (story_seq_step) {
        case 0:
            func_800773F0();
            lws_anim(&gfx, &mtx, temp_s1, 0, story_buffer);
            framecont = 0;
            break;

        case 1:
            story_time_cnt = framecont;
            fin_frame_543 = framecont;
            if (gControllerPressedButtons[main_joy[0]] & (START_BUTTON | B_BUTTON)) {
                story_seq_step = 2;
                story_time_cnt = 0;
            }
            if (gControllerHoldButtons[main_joy[0]] & A_BUTTON) {
                framecont += 3;
                story_time_cnt += 3;
            }

            func_8007865C();
            if ((lws_anim(&gfx, &mtx, temp_s1, story_time_cnt, story_buffer) == 1) && msgWnd_isEnd(&mess_st)) {
                story_time_cnt = 0;
                story_seq_step++;
            }
            break;

        default:
            func_8007744C();
            lws_anim(&gfx, &mtx, temp_s1, fin_frame_543, story_buffer);
            break;
    }

    gDPSetScissor(gfx++, G_SC_NON_INTERLACE, 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1);

    *gfxP = gfx;
}
#endif

extern s32 fin_frame_568;
extern s32 fin_demo_569;

#if VERSION_US || VERSION_CN
void story_st_new2_f(Gfx **gfxP, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    Gfx *gfx = *gfxP;
    Mtx mtx;
    s32 temp;

    gSPDisplayList(gfx++, normal_texture_init_dl);
    gSPDisplayList(gfx++, story_setup);

    makeTransrateMatrix(&mtx, 0U, 0xFFF38000U, 0xFC4A0000U);

    lws_scene = RELOCATE_SEGMENTED(lws_data[arg1], story_buffer);

    switch (story_seq_step) {
        case 0x0:
            func_800773F0();
            lws_anim(&gfx, &mtx, RELOCATE_SEGMENTED(lws_data[arg1], story_buffer), 0, story_buffer);
            framecont = 0;
            fin_frame_568 = 0;
            fin_demo_569 = arg1;
            break;

        case 0x1:
            fin_demo_569 = arg1;
            story_time_cnt = framecont;
            fin_frame_568 = framecont;
            st_mes_ptr = mes_data[arg2];
            if (gControllerPressedButtons[main_joy[0]] & (START_BUTTON | B_BUTTON)) {
                story_seq_step = 0x64;
                framecont = 0;
                story_time_cnt = 0;
                st_message_count = 0;
            }
            if (gControllerHoldButtons[main_joy[0]] & A_BUTTON) {
                story_time_cnt += 3;
                framecont += 3;
            }

            func_8007865C();
            if (lws_anim(&gfx, &mtx, RELOCATE_SEGMENTED(lws_data[arg1], story_buffer), story_time_cnt, story_buffer) ==
                1) {
                if (msgWnd_isEnd(&mess_st)) {
                    framecont = 0;
                    story_time_cnt = 0;
                    st_message_count = 0;
                    story_seq_step += 1;
                }
            }

            if (fin_frame_568 > (lws_scene->unk_04 - 0x20)) {
                temp = fin_frame_568 - (lws_scene->unk_04 - 0x20);
                temp = ((0x1E - temp) * 0xFF) / 30;

                gSPDisplayList(gfx++, normal_texture_init_dl);
                story_spot(&gfx, 0xA0, 0x56, temp, changestar_tex);
            }
            break;

        case 0x2:
            fin_demo_569 = arg3;
            story_time_cnt = framecont;
            fin_frame_568 = framecont;
            st_mes_ptr = mes_data[arg4];
            if (gControllerPressedButtons[main_joy[0]] & (START_BUTTON | B_BUTTON)) {
                story_seq_step = 3;
                story_time_cnt = 0;
            }
            if (gControllerHoldButtons[main_joy[0]] & A_BUTTON) {
                framecont += 3;
                story_time_cnt += 3;
            }

            func_8007865C();
            if ((lws_anim(&gfx, &mtx, RELOCATE_SEGMENTED(lws_data[arg3], story_buffer), story_time_cnt, story_buffer) ==
                 1) &&
                (msgWnd_isEnd(&mess_st) != false)) {
                story_time_cnt = 0;
                story_seq_step += 1;
            }
            if (fin_frame_568 < 0x1E) {
                temp = fin_frame_568;
                temp = (temp * 0xFF) / 30;

                gSPDisplayList(gfx++, normal_texture_init_dl);
                story_spot(&gfx, 0xA0, 0x56, temp, changestar_tex);
            }
            break;

        default:
            func_8007744C();
            lws_anim(&gfx, &mtx, RELOCATE_SEGMENTED(lws_data[fin_demo_569], story_buffer), fin_frame_568, story_buffer);
            break;
    }

    gDPSetScissor(gfx++, G_SC_NON_INTERLACE, 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1);

    *gfxP = gfx;
}
#endif

extern s32 fin_frame_623;
extern s32 fin_demo_624;

#if VERSION_US || VERSION_CN
void story_st_new2(Gfx **gfxP, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    Mtx sp20;
    Gfx *gfx = *gfxP;

    gSPDisplayList(gfx++, normal_texture_init_dl);
    gSPDisplayList(gfx++, story_setup);

    makeTransrateMatrix(&sp20, 0U, 0xFFF38000U, 0xFC4A0000U);

    switch (story_seq_step) {
        case 0x0:
            func_800773F0();
            lws_anim(&gfx, &sp20, RELOCATE_SEGMENTED(lws_data[arg1], story_buffer), 0, story_buffer);
            framecont = 0;
            fin_frame_623 = 0;
            fin_demo_624 = arg1;
            break;

        case 0x1:
            fin_demo_624 = arg1;
            story_time_cnt = framecont;
            fin_frame_623 = framecont;
            st_mes_ptr = mes_data[arg2];
            if (gControllerPressedButtons[*main_joy] & (START_BUTTON | B_BUTTON)) {
                story_seq_step = 0x64;
                framecont = 0;
                story_time_cnt = 0;
                st_message_count = 0;
            }
            if (gControllerHoldButtons[*main_joy] & A_BUTTON) {
                story_time_cnt += 3;
                framecont += 3;
            }
            func_8007865C();
            if ((lws_anim(&gfx, &sp20, RELOCATE_SEGMENTED(lws_data[arg1], story_buffer), story_time_cnt,
                          story_buffer) == 1) &&
                (msgWnd_isEnd(&mess_st) != false)) {
                framecont = 0;
                story_time_cnt = 0;
                st_message_count = 0;
                story_seq_step++;
            }
            break;

        case 0x2:
            fin_demo_624 = arg3;
            story_time_cnt = framecont;
            fin_frame_623 = framecont;
            st_mes_ptr = mes_data[arg4];
            if (gControllerPressedButtons[*main_joy] & (START_BUTTON | B_BUTTON)) {
                story_seq_step = 3;
                story_time_cnt = 0;
            }
            if (gControllerHoldButtons[*main_joy] & A_BUTTON) {
                framecont += 3;
                story_time_cnt += 3;
            }

            func_8007865C();
            if ((lws_anim(&gfx, &sp20, RELOCATE_SEGMENTED(lws_data[arg3], story_buffer), story_time_cnt,
                          story_buffer) == 1) &&
                (msgWnd_isEnd(&mess_st) != false)) {
                story_time_cnt = 0;
                story_seq_step++;
            }
            break;

        default:
            func_8007744C();
            lws_anim(&gfx, &sp20, RELOCATE_SEGMENTED(lws_data[fin_demo_624], story_buffer), fin_frame_623,
                     story_buffer);
            break;
    }

    gDPSetScissor(gfx++, G_SC_NON_INTERLACE, 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1);

    *gfxP = gfx;
}
#endif

extern s32 fin_frame_667;

#if VERSION_US || VERSION_CN
void story_m_end(Gfx **gfxP, s32 arg1, s32 arg2) {
    Mtx sp20;
    Gfx *gfx = *gfxP;
    s32 var_a3;
    s32 var_t0;
    s32 var_t1;
    s32 var_t2;

    gSPDisplayList(gfx++, normal_texture_init_dl);
    gSPDisplayList(gfx++, story_setup);

    makeTransrateMatrix(&sp20, 0U, 0xFFF38000U, 0xFC4A0000U);

    switch (story_seq_step) {
        case 0:
            func_800773F0();
            lws_anim(&gfx, &sp20, RELOCATE_SEGMENTED(lws_data[arg1], story_buffer), 0, story_buffer);
            framecont = 0;
            story_spot_cnt = 0x100;
            st_mes_ptr = mes_data[arg2];
            break;

        case 1:
            story_time_cnt = framecont;
            fin_frame_667 = framecont;

            func_8007865C();
            if (gControllerPressedButtons[*main_joy] & 0x5000) {
                framecont = 0;
                story_time_cnt = 0;
                st_message_count = 0;
                story_seq_step += 1;
            }

            if (lws_anim(&gfx, &sp20, RELOCATE_SEGMENTED(lws_data[arg1], story_buffer), story_time_cnt, story_buffer) ==
                1) {
                framecont = 0;
                story_time_cnt = 0;
                st_message_count = 0;
                story_seq_step += 1;
            }
            break;

        default:
            story_time_cnt = framecont;
            fin_frame_667 = framecont;
            st_mes_ptr = mes_data[0x16];

            var_a3 = 0xFF;
            var_t1 = 0xFF;
            var_t2 = 0xFF;
            if (story_time_cnt >= 0x15F) {
                var_t0 = story_time_cnt - 0x15E;
                if (story_time_cnt < 0x1F4) {
                    var_t2 = ((var_t0 * -0x69) / 149) + 0xFF;
                    var_t1 = (-(var_t0 * 0xA0) / 149) + 0xFF;
                    var_a3 = ((var_t0 * -0xAF) / 149) + 0xFF;
                } else {
                    var_t0 = (story_time_cnt - 0x1F4);
                    if (story_time_cnt < 0x2BC) {
                        var_t2 = ((var_t0 * -0x5F) / 199) + 0x96;
                        var_t1 = (-(var_t0 * 0x10) / 199) + 0x5F;
                        var_a3 = ((var_t0 * 0x1E) / 199) + 0x50;
                    } else if (story_time_cnt < 0x3E8) {
                        var_t2 = 0x37;
                        var_t1 = 0x4F;
                        var_a3 = 0x6E;
                    } else if (story_time_cnt < 0x4E2) {
                        var_t0 = story_time_cnt - 0x3E8;
                        var_t2 = ((var_t0 * 0xC8) / 249) + 0x37;
                        var_t1 = ((var_t0 * 0xB0) / 249) + 0x4F;
                        var_a3 = ((var_t0 * 0x91) / 249) + 0x6E;
                    }
                }
            }

            var_t0 = 0xFF;
            if ((u32)(story_time_cnt - 0x277) < 0x171U) {
                if (story_time_cnt < 0x2BC) {
                    var_t0 = story_time_cnt - 0x276;
                    var_t0 = ((var_t0 * -0xFF) / 69) + 0xFF;
                } else if (story_time_cnt >= 0x3B7) {
                    var_t0 = story_time_cnt - 0x3B6;
                    var_t0 = (var_t0 * 0xFF) / 49;
                } else {
                    var_t0 = 0;
                }
            }

            gDPSetEnvColor(gfx++, var_t2, var_t1, var_a3, var_t0);

            if (story_staff_roll != 0) {
                if (st_message_count != 0x270F) {
                    func_8007865C();
                }
            }

            if (lws_anim(&gfx, &sp20, RELOCATE_SEGMENTED(lws_data[0x15], story_buffer), story_time_cnt, story_buffer) ==
                1) {
                framecont = 0x117;
                story_time_cnt = 0x117;
            }

            if (story_time_cnt >= 0x1F) {
                if (story_staff_roll == 0) {
                    story_staff_roll = 1;
                }
            }
            break;
    }

    gDPSetScissor(gfx++, G_SC_NON_INTERLACE, 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1);

    if ((story_staff_roll == 2) && (msgWnd_isScroll(&mess_roll_st) == false)) {
        story_staff_roll = -1;
    }

    if (story_staff_roll == 1) {
        msgWnd_addStr(&mess_roll_st, st_staffroll_txt);
        msgWnd_skip(&mess_roll_st);
        mess_roll_st.unk_1C = 0;
        story_staff_roll = 2;
        mess_roll_st.unk_5C = 1.0f / 60.0f;
    }

    *gfxP = gfx;
}
#endif

extern s32 fin_frame_737;

#if VERSION_US || VERSION_CN
void story_st_new_w9(Gfx **gfxP, s32 arg1, s32 arg2) {
    Gfx *gfx = *gfxP;
    Mtx mtx;
    s32 red;
    s32 green;
    s32 blue;
    s32 alpha;
    void *temp_s0;

    st_mes_ptr = mes_data[arg2];

    gSPDisplayList(gfx++, normal_texture_init_dl);
    gSPDisplayList(gfx++, story_setup);

    makeTransrateMatrix(&mtx, 0, 0xFFF38000, 0xFC4A0000);

    temp_s0 = RELOCATE_SEGMENTED(lws_data[arg1], story_buffer);

    switch (story_seq_step) {
        case 0:
            func_800773F0();
            lws_anim(&gfx, &mtx, temp_s0, 0, story_buffer);
            framecont = 0;
            break;

        case 1:
            story_time_cnt = framecont;
            fin_frame_737 = framecont;

            red = green = blue = 0;

            if ((story_time_cnt >= 0x2F7) && (story_time_cnt <= 0x333)) {
                alpha = story_time_cnt - 0x2F7;
                alpha = (alpha * 0xFF) / 60;

                green = alpha;
                red = alpha;
                blue = alpha;
            } else if (story_time_cnt > 0x333) {
                blue = 255;
                green = 255;
                red = 255;
            }
            alpha = 255;

            gDPSetEnvColor(gfx++, red, green, blue, alpha);

            if (gControllerPressedButtons[main_joy[0]] & (START_BUTTON | B_BUTTON)) {
                story_time_cnt = 0;
                story_seq_step += 1;
            }
            if (gControllerHoldButtons[main_joy[0]] & A_BUTTON) {
                story_time_cnt += 3;
                framecont += 3;
            }

            func_8007865C();
            if (lws_anim(&gfx, &mtx, temp_s0, story_time_cnt, story_buffer) == 1) {
                story_time_cnt = 0;
                story_seq_step += 1;
            }
            break;

        default:
            func_8007744C();
            lws_anim(&gfx, &mtx, temp_s0, fin_frame_737, story_buffer);
            break;
    }

    gDPSetScissor(gfx++, G_SC_NON_INTERLACE, 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1);

    *gfxP = gfx;
}
#endif

extern s32 fin_frame_768;

#if VERSION_US || VERSION_CN
void story_w_end(Gfx **gfxP, s32 arg1) {
    Mtx sp20;
    Gfx *gfx = *gfxP;
    s32 temp_t0_2;
    s32 var_a3;
    s32 var_t0;
    s32 var_t1;

    gSPDisplayList(gfx++, normal_texture_init_dl);

    gSPDisplayList(gfx++, story_setup);

    makeTransrateMatrix(&sp20, 0U, 0xFFF38000U, 0xFC4A0000U);

    switch (story_seq_step) {
        case 0:
            func_800773F0();
            lws_anim(&gfx, &sp20, RELOCATE_SEGMENTED(lws_data[arg1], story_buffer), 0, story_buffer);
            framecont = 0;
            story_spot_cnt = 0x100;
            st_mes_ptr = mes_data[0x17];
            break;

        case 1:
            story_time_cnt = (s32)framecont;
            fin_frame_768 = (s32)framecont;
            func_8007865C();
            if (gControllerPressedButtons[*main_joy] & 0x5000) {
                framecont = 0;
                story_time_cnt = 0;
                st_message_count = 0;
                story_seq_step += 1;
            }
            if (lws_anim(&gfx, &sp20, RELOCATE_SEGMENTED(lws_data[arg1], story_buffer), story_time_cnt, story_buffer) ==
                1) {
                framecont = 0;
                story_time_cnt = 0;
                st_message_count = 0;
                story_seq_step += 1;
            }
            break;

        default:
            story_time_cnt = (s32)framecont;
            fin_frame_768 = (s32)framecont;
            st_mes_ptr = mes_data[0x18];
            var_a3 = 0xFF;
            var_t0 = 0xFF;
            var_t1 = 0xFF;
            if ((s32)framecont >= 0x262) {
                if ((s32)framecont < 0x31B) {
                    temp_t0_2 = framecont - 0x262;
                    var_t1 = ((temp_t0_2 * -0x69) / 184) + 0xFF;
                    var_t0 = (-(temp_t0_2 * 0xA0) / 184) + 0xFF;
                    var_a3 = ((temp_t0_2 * -0xAF) / 184) + 0xFF;
                } else if ((s32)framecont < 0x3D4) {
                    temp_t0_2 = framecont - 0x31B;
                    var_t1 = ((temp_t0_2 * -0x5F) / 184) + 0x96;
                    var_t0 = (-(temp_t0_2 * 0x10) / 184) + 0x5F;
                    var_a3 = ((temp_t0_2 * 0x1E) / 184) + 0x50;
                } else if ((s32)framecont < 0x5C8) {
                    var_t1 = 0x37;
                    var_t0 = 0x4F;
                    var_a3 = 0x6E;
                } else if ((s32)framecont < 0x708) {
                    temp_t0_2 = framecont - 0x5C8;
                    var_t1 = ((temp_t0_2 * 0xC8) / 319) + 0x37;
                    var_t0 = ((temp_t0_2 * 0xB0) / 319) + 0x4F;
                    var_a3 = ((temp_t0_2 * 0x91) / 319) + 0x6E;
                }
            }

            gDPSetEnvColor(gfx++, var_t1, var_t0, var_a3, 255);

            if (story_staff_roll != 0) {
                if (st_message_count != 0x270F) {
                    func_8007865C();
                }
            }
            if (lws_anim(&gfx, &sp20, RELOCATE_SEGMENTED(lws_data[0x18], story_buffer), story_time_cnt, story_buffer) ==
                1) {
                framecont = 0x6D;
                story_time_cnt = (s32)0x6DU;
            }
            if (story_time_cnt >= 0x1F) {
                if (story_staff_roll == 0) {
                    story_staff_roll = 1;
                }
            }
            break;
    }

    gDPSetScissor(gfx++, G_SC_NON_INTERLACE, 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1);

    if ((story_staff_roll == 2) && (msgWnd_isScroll(&mess_roll_st) == false)) {
        story_staff_roll = -1;
    }

    if (story_staff_roll == 1) {
        msgWnd_addStr(&mess_roll_st, st_staffroll_txt);
        msgWnd_skip(&mess_roll_st);
        mess_roll_st.unk_1C = 0;
        story_staff_roll = 2;
        mess_roll_st.unk_5C = 1.0f / 60.0f;
    }

    *gfxP = gfx;
}
#endif

#if VERSION_US || VERSION_CN
void func_8007A9DC(void) {
    void *ptr = story_buffer;

    storyGraphic = ptr;

    ptr = ALIGN_PTR(
        DecompressRomToRam(storyRomData[STORYROMDATA_TITLE_ALL].start, ptr,
                           storyRomData[STORYROMDATA_TITLE_ALL].end - storyRomData[STORYROMDATA_TITLE_ALL].start));
    wakuGraphic = ptr;

    ptr = ALIGN_PTR(DecompressRomToRam(storyRomData[STORYROMDATA_WAKU].start, ptr,
                                       storyRomData[STORYROMDATA_WAKU].end - storyRomData[STORYROMDATA_WAKU].start));
    bgGraphic = ptr;

    ptr = ALIGN_PTR(
        DecompressRomToRam(storyRomData[STORYROMDATA_MENU_BG].start, ptr,
                           storyRomData[STORYROMDATA_MENU_BG].end - storyRomData[STORYROMDATA_MENU_BG].start));
    messageData = ptr;
}
#endif

extern s32 B_800E5A20;
extern s32 B_800E5A24;
extern s32 B_800E5A2C;
extern s32 B_800E5A38;
extern f32 B_800E5A44;

extern s32 B_800E5A90;
extern s32 B_800E5A94;
extern s32 B_800E5AA0;
extern s32 B_800E5AA4;
extern s32 B_800E5AAC;
extern s32 B_800E5AB8;
extern f32 B_800E5AC4;
extern u64 B_800E5AF0[];

extern s16 B_800F6CDE[];

extern SeqIndex snd_tbl_838[];

#if VERSION_US
#define MESS_ROLL_ST_ARG2 0x77A
#endif
#if VERSION_CN
#define MESS_ROLL_ST_ARG2 0x7A7
#endif

#if VERSION_US || VERSION_CN
void main_story(NNSched *sc) {
    OSMesgQueue scMQ;
    OSMesg scMsgBuf[NN_SC_MAX_MESGS];
    NNScClient scClient;
    s32 var_s1;
    s32 temp;

    osCreateMesgQueue(&scMQ, scMsgBuf, ARRAY_COUNT(scMsgBuf));
    nnScAddClient(sc, &scClient, &scMQ);

    graphic_no = GRAPHIC_NO_0;
    story_z_buffer = gfx_freebuf;
    guPerspective(&story_viewMtx, &story_norm, 45.0f, 4.0f / 3.0f, 1.0f, 1000.0f, 1.0f);
    var_s1 = 0;
    guOrtho(&story_viewMtx, -SCREEN_WIDTH / 2, SCREEN_WIDTH / 2, -SCREEN_HEIGHT / 2, SCREEN_HEIGHT / 2, 1.0f, 2000.0f,
            1.0f);

    first_copy = 1;
    for (; var_s1 < ARRAY_COUNT(joyflg); var_s1++) {
        joyflg[var_s1] = U_JPAD | L_JPAD | R_JPAD | D_JPAD;
    }

    D_800AAD38 = gfx_freebuf;
    story_buffer = D_800AAD38 + 0x10000;
    framecont = 0;
    story_time_cnt = 0;
    story_seq_step = 0;
    D_800AAD1C = 0;
    story_curtain = 0x1E;
    story_zoom = 0;
    story_message_on = 0;
    story_message_start = 0;
    story_doing = 1;
    story_staff_roll = 0;
    st_message_count = 0;
    loop_flg = true;

    mess_heap = &B_800E5AF0;
    msgWnd_init(&mess_st, &mess_heap, 0x10, 3, 0x42, 0xB1);
    mess_st.unk_30 = 0xC;
    mess_st.unk_34 = 0xC;
    mess_st.unk_3C = 6;
    mess_st.unk_48 = 0xE;
    mess_st.unk_54 = 0.4f;

    mess_roll_heap = gfx_freebuf;
    msgWnd_init2(&mess_roll_st, &mess_roll_heap, MESS_ROLL_ST_ARG2, 0x14, 0xB, 0x28, 0x16);
    mess_roll_st.unk_24 = 1;
    mess_roll_st.unk_30 = 0xC;
    mess_roll_st.unk_34 = 0xC;
    mess_roll_st.unk_3C = 6;
    mess_roll_st.unk_48 = 0xE;
    mess_roll_st.unk_20 = 1;
    mess_roll_st.unk_54 = 0.25f;

    func_8007A9DC();
    joyProcCore();
    dm_seq_play(snd_tbl_838[story_proc_no]);

    for (; loop_flg != 0; dm_audio_update()) {
        osRecvMesg(&scMQ, NULL, OS_MESG_BLOCK);

#ifdef NN_SC_PERF
        if (D_80092F10_cn) {
            joyProcCore();
            graphic_no = GRAPHIC_NO_0;
            continue;
        }

        graphic_no = GRAPHIC_NO_1;
#endif
        msgWnd_update(&mess_st);
        msgWnd_update(&mess_roll_st);
        if ((story_doing == 0) && (story_zoom >= 0x5A)) {
            loop_flg = 0;
        }
        joyProcCore();
#ifndef NN_SC_PERF
        graphic_no = GRAPHIC_NO_1;
#endif
    }

    dm_audio_stop();
    graphic_no = GRAPHIC_NO_0;

    while ((pendingGFX != 0) || !dm_audio_is_stopped()) {
        osRecvMesg(&scMQ, NULL, OS_MESG_BLOCK);
        dm_audio_update();
    }

    for (var_s1 = 0; var_s1 < 3; var_s1++) {
        osRecvMesg(&scMQ, NULL, OS_MESG_BLOCK);
    }

    nnScRemoveClient(sc, &scClient);
    evs_story_no = story_proc_no;
    if (evs_story_no >= 0xC) {
        evs_story_no -= 0xC;
    }
    temp = evs_story_no;
    evs_seqnumb = temp % 3;
}
#endif

#if VERSION_US || VERSION_CN
/**
 * Original name: init_objMtx
 */
void init_objMtx(void) {
    pObjectMtx = story_objectMtx[objMtx_FF];
    objMtx_FF ^= 1;
}
#endif

#if VERSION_US || VERSION_CN
void graphic_story(void) {
    s32 pad[6] UNUSED;
    OSScTask *temp_s4;

    gGfxHead = gGfxGlist[gfx_gtask_no];
    temp_s4 = &B_800FAE80[gfx_gtask_no];

    init_objMtx();

    gSPSegment(gGfxHead++, 0x00, 0x00000000);
    gSPSegment(gGfxHead++, 0x05, osVirtualToPhysical(story_buffer));

    lws_data = story_buffer;
    S2RDPinitRtn(1U);

    gDPPipeSync(gGfxHead++);
    gDPSetCycleType(gGfxHead++, G_CYC_FILL);
    gDPSetCycleType(gGfxHead++, G_CYC_1CYCLE);
    gDPSetEnvColor(gGfxHead++, 255, 255, 255, 255);

    S2ClearCFBRtn(1U);

    gSPMatrix(gGfxHead++, OS_K0_TO_PHYSICAL(&story_viewMtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);

    if (story_zoom > 0) {
        story_zoomfade(&gGfxHead, story_zoom);
        story_zoom++;
    } else {
        switch (story_proc_no) {
            case STORY_PROC_NO_0:
            case STORY_PROC_NO_12:
                story_st_new(&gGfxHead, 1, 0);
                break;

            case STORY_PROC_NO_10:
                story_m_end(&gGfxHead, 0x14, 0x1B);
                break;

            case STORY_PROC_NO_11:
                story_m_end(&gGfxHead, 0x16, 0x1C);
                break;

            case STORY_PROC_NO_22:
                story_w_end(&gGfxHead, 0x17);
                break;

            case STORY_PROC_NO_23:
                story_w_end(&gGfxHead, 0x19);
                break;

            case STORY_PROC_NO_1:
                story_st_new_op(&gGfxHead, 1);
                break;

            case STORY_PROC_NO_2:
                story_st_new2(&gGfxHead, 2, 5, 3, 7);
                break;

            case STORY_PROC_NO_3:
                gDPSetEnvColor(gGfxHead++, 170, 150, 185, 255);

                story_st_new(&gGfxHead, 5, 9);
                break;

            case STORY_PROC_NO_4:
                story_st_new2_f(&gGfxHead, 0x22, 0x1D, 7, 0xB);
                break;

            case STORY_PROC_NO_5:
                story_st_new(&gGfxHead, 9, 0xD);
                break;

            case STORY_PROC_NO_6:
                story_st_new(&gGfxHead, 0xC, 0xF);
                break;

            case STORY_PROC_NO_7:
                if (evs_story_level == 0) {
                    story_st_new(&gGfxHead, 0x1E, 0x19);
                } else {
                    story_st_new(&gGfxHead, 0xD, 0x11);
                }
                break;

            case STORY_PROC_NO_8:
                if (evs_story_level == 0) {
                    story_st_new2_f(&gGfxHead, 0x20, 0x1A, 0x10, 0x13);
                } else {
                    story_st_new2_f(&gGfxHead, 0xE, 0x12, 0x10, 0x13);
                }
                break;

            case STORY_PROC_NO_9:
                story_st_new(&gGfxHead, 0x12, 0x14);
                break;

            case STORY_PROC_NO_13:
                story_st_new_op(&gGfxHead, 0);
                break;

            case STORY_PROC_NO_14:
                story_st_new2(&gGfxHead, 2, 6, 4, 8);
                break;

            case STORY_PROC_NO_15:
                gDPSetEnvColor(gGfxHead++, 170, 150, 185, 255);
                story_st_new(&gGfxHead, 6, 0xA);
                break;

            case STORY_PROC_NO_16:
                story_st_new2_f(&gGfxHead, 0x22, 0x1D, 8, 0xC);
                break;

            case STORY_PROC_NO_17:
                story_st_new(&gGfxHead, 0xA, 0xE);
                break;

            case STORY_PROC_NO_18:
                story_st_new(&gGfxHead, 0xB, 0x10);
                break;

            case STORY_PROC_NO_19:
                if (evs_story_level == 0) {
                    story_st_new(&gGfxHead, 0x1F, 0x19);
                } else {
                    story_st_new(&gGfxHead, 0xD, 0x11);
                }
                break;

            case STORY_PROC_NO_20:
                if (evs_story_level == 0) {
                    story_st_new2_f(&gGfxHead, 0x20, 0x1A, 0x11, 0x13);
                } else {
                    story_st_new2_f(&gGfxHead, 0xF, 0x12, 0x11, 0x13);
                }
                break;

            case STORY_PROC_NO_21:
                story_st_new_w9(&gGfxHead, 0x13, 0x15);
                break;

            default:
                break;
        }

        curtain_proc_org(&gGfxHead, story_curtain);
        if (story_staff_roll == 2) {
            msgWnd_draw(&mess_roll_st, &gGfxHead);

            if (gControllerPressedButtons[main_joy[0]] & START_BUTTON) {
                story_staff_roll = -1;
            }

            if (gControllerHoldButtons[main_joy[0]] & (A_BUTTON | B_BUTTON)) {
                mess_roll_st.unk_5C = 1.0f / 6.0f;
            } else {
                mess_roll_st.unk_5C = 1.0f / 60.0f;
            }
        }

        func_800770E8(&gGfxHead, wakuGraphic);
        if (story_message_on != 0) {
            msgWnd_draw(&mess_st, &gGfxHead);
            gDPSetScissor(gGfxHead++, G_SC_NON_INTERLACE, 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1);
        }
    }

    if (story_staff_roll < 0) {
        gSPDisplayList(gGfxHead++, normal_texture_init_dl);
        story_spot(&gGfxHead, 0xA0, 0x78, story_spot_cnt, changestar_tex);
        story_spot_cnt -= 4;
        if (story_spot_cnt < -0x14) {
            loop_flg = false;
        }
    }

    story_time_cnt++;
    gDPFullSync(gGfxHead++);
    gSPEndDisplayList(gGfxHead++);

    osWritebackDCacheAll();
    gfxTaskStart(temp_s4, gGfxGlist[gfx_gtask_no], (gGfxHead - gGfxGlist[gfx_gtask_no]) * sizeof(Gfx), 0,
                 OS_SC_SWAPBUFFER);
}
#endif

#if VERSION_US || VERSION_CN
void func_8007B62C(Gfx **gfxP) {
    draw_menu_bg(gfxP, 0xA0, 0x78);
}
#endif

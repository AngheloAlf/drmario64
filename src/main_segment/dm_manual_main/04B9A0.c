/**
 * Part of dm_manual_main.c
 */

#include "ultra64.h"
#include "include_asm.h"
#include "macros_defines.h"
#include "unknown_structs.h"
#include "main_segment_functions.h"
#include "main_segment_variables.h"
#include "audio/audio_stuff.h"

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main/04B9A0", D_800B31C0);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main/04B9A0", D_800B31D8);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main/04B9A0", D_800B31DC);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main/04B9A0", D_800B31E0);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_manual_main/04B9A0", dm_manual_all_init);

#ifdef NON_MATCHING
/**
 * Original name: dm_manual_main
 */
enum_main_no dm_manual_main(struct_800EB670 *arg0) {
    OSMesgQueue sp10;
    OSMesg sp28[8];
    struct_800FAF98_unk_64 sp48;
    enum_main_no var_v0;
    s32 i;
    s32 var_s3 = 1;
    s32 var_s4 = 0;
    struct_800F4890 *temp_s2;

    osCreateMesgQueue(&sp10, sp28, ARRAY_COUNT(sp28));
    func_8002A184(arg0, &sp48, &sp10);
    dm_manual_all_init();

    temp_s2 = watchManual;
    for (i = 0; i < ARRAY_COUNT(game_state_data); i++) {
        aifMakeFlagSet(&game_state_data[i]);
    }

    while (var_s4 == 0) {
        joyProcCore();
        osRecvMesg(&sp10, NULL, 1);
        func_80071FA0(&temp_s2->unk_034);
        dm_effect_make();

        temp_s2->unk_184++;
        if (temp_s2->unk_010 > 0) {
            var_s4 = temp_s2->unk_00C == 0xFF;
        }

        temp_s2->unk_00C = CLAMP(temp_s2->unk_00C + temp_s2->unk_010, 0, 0xFF);
        switch (evs_manual_no) {
            case 0x0:
                var_s3 = dm_manual_1_main();
                break;
            case 0x1:
                var_s3 = dm_manual_2_main();
                break;
            case 0x2:
                var_s3 = dm_manual_3_main();
                break;
            case 0x3:
                var_s3 = dm_manual_4_main();
                break;
        }
        dm_seq_set_volume(0x60);
        dm_audio_update();
        if (temp_s2->unk_018 != 0) {
            temp_s2->unk_014++;
            if (temp_s2->unk_014 >= temp_s2->unk_018) {
                temp_s2->unk_014 = 0;
                temp_s2->unk_018 = 0;
                dm_seq_play_in_game(evs_seqnumb * 2);
            }
        }
        if (temp_s2->unk_00C == 0) {
            s32 temp = ((-(main_old == MAIN_NO_3) & 0xFF3F) | 0x4000);

            var_s3 &= -((gControllerPressedButtons[B_800EBD16[0]] & temp) == 0);
        }

        if (var_s3 == 0) {
            if (temp_s2->unk_010 < 0) {
                temp_s2->unk_010 = -temp_s2->unk_010;
            }
        }
        graphic_no = GRAPHIC_NO_3;
    }

    dm_audio_stop();
    graphic_no = GRAPHIC_NO_0;

    while (!dm_audio_is_stopped() || (pendingGFX != 0)) {
        osRecvMesg(&sp10, NULL, 1);
        dm_audio_update();
    }

    func_8002A1DC(arg0, &sp48);

    var_v0 = MAIN_NO_3;
    if (main_old != MAIN_NO_3) {
        var_v0 = MAIN_NO_6;
    }
    return var_v0;
}
#else
INCLUDE_ASM("asm/nonmatchings/main_segment/dm_manual_main/04B9A0", dm_manual_main);
#endif

void dm_manual_graphic(void) {
    UNK_TYPE sp28;
    UNK_TYPE sp2C;
    OSScTask *ptr;
    s32 color;
    s32 alpha;
    struct_800F4890 *temp_s1 = watchManual;

    gGfxHead = gGfxGlist[B_800FAD2C];
    ptr = &B_800FAE80[B_800FAD2C];

    sp28 = dm_get_mtx_buf();
    sp2C = dm_get_vtx_buf();

    gSPSegment(gGfxHead++, 0x00, 0x00000000);
    F3RCPinitRtn();
    F3ClearFZRtn(false);

    gDPSetScissor(gGfxHead++, G_SC_NON_INTERLACE, 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1);

    dm_game_draw_snap_bg(&gGfxHead, &sp28, &sp2C, 0);
    dm_manual_draw_fg(&sp28, &sp2C);

    color = 255;
    alpha = CLAMP((temp_s1->unk_00C - 127) * 1.2 + 127, 0, 255);
    if (alpha > 0) {
        FillRectRGBA(&gGfxHead, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, color, color, color, alpha);
    }

    gDPFullSync(gGfxHead++);
    gSPEndDisplayList(gGfxHead++);

    osWritebackDCacheAll();
    gfxTaskStart(ptr, gGfxGlist[B_800FAD2C], (gGfxHead - gGfxGlist[B_800FAD2C]) * sizeof(Gfx), 0, OS_SC_SWAPBUFFER);
}

/**
 * Original filename: dm_title_main.c
 */

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

void func_80075F30(void) {
    title_exit_flag = 0;
    title_mode_type = 0;
    title_fade_step = -8;
    evs_seqence = 0;
    title_fade_count = -(main_old == MAIN_NO_6) & 0xFF;
    init_title(&Heap_bufferp, main_old != MAIN_NO_6);
}

/**
 * Original name: _stageTbl
 */
const u8 _stageTbl[] = {
    0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15,
};

enum_main_no dm_title_main(struct_800EB670 *arg0) {
    OSMesgQueue sp10;
    OSMesg sp28[8];
    struct_800FAF98_unk_64 sp48;
    u32 var_s0 = 0;
    s32 var_s1 = -(main_old == MAIN_NO_6) & 0x63;

    osCreateMesgQueue(&sp10, sp28, ARRAY_COUNT(sp28));
    func_8002A184(arg0, &sp48, &sp10);
    sgenrand(osGetCount());
    func_80075F30();
    evs_playmax = joyResponseCheck();
    osRecvMesg(&sp10, NULL, 1);
    graphic_no = GRAPHIC_NO_2;

    while (var_s0 == 0) {
        joyProcCore();
        osRecvMesg(&sp10, NULL, 1);

        title_fade_count = CLAMP(title_fade_count + title_fade_step, 0, 0xFF);

        switch (title_mode_type) {
            case 0:
                var_s1++;
                if (title_exit_flag == -1) {
                    title_mode_type = 7;
                } else {
                    if (var_s1 == 0x64) {
                        dm_seq_play(0xB);
                    }
                    if (title_exit_flag == 1) {
                        title_mode_type = 6;
                    }
                }
                break;

            case 6:
            case 7:
                title_fade_step = -title_fade_step;
                if (title_mode_type == 6) {
                    var_s0 = 1;
                } else if (title_mode_type == 7) {
                    var_s0 = 2;
                }
                break;
        }

        dm_audio_update();
    }

    dm_seq_stop();

    while (!dm_audio_is_stopped() || (title_fade_count < 0xFF)) {
        osRecvMesg(&sp10, NULL, 1);
        dm_audio_update();

        title_fade_count = CLAMP(title_fade_count + title_fade_step, 0, 0xFF);
    }

    graphic_no = GRAPHIC_NO_0;
    while (pendingGFX != 0) {
        osRecvMesg(&sp10, NULL, 1);
        dm_audio_update();
    }

    func_8002A1DC(arg0, &sp48);

    if (var_s0 == 1) {
        return MAIN_NO_6;
    }

    if (var_s0 != 2) {
        return MAIN_NO_2;
    }

    if (title_demo_flg == 0) {
        u32 temp = rand();

        story_proc_no = _stageTbl[temp % ARRAY_COUNT(_stageTbl)];

        if (title_demo_no == 0) {
            evs_gamesel = ENUM_EVS_GAMESEL_4;
        } else if (title_demo_no == 1) {
            evs_gamesel = ENUM_EVS_GAMESEL_5;
        } else if (title_demo_no == 2) {
            evs_gamesel = ENUM_EVS_GAMESEL_6;
        }

        evs_gamemode = 0;

        title_demo_no++;
        if (title_demo_no >= 3) {
            title_demo_no = 0;
        }
        title_demo_flg ^= 1;
        return MAIN_NO_1;
    }

    if (title_demo_flg == 1) {
        evs_manual_no = title_manual_no;

        title_manual_no++;
        if (title_manual_no >= 4) {
            title_manual_no = 0;
        }
        title_demo_flg = 0;
        return MAIN_NO_4;
    }

#ifdef AVOID_UB
    return title_demo_flg;
#endif
}

/**
 * Original name: dm_title_graphic
 */
void dm_title_graphic(void) {
    s32 color;
    s32 alpha;
    OSScTask *ptr;

    gGfxHead = gGfxGlist[gCurrentFramebufferIndex];

    ptr = &B_800FAE80[gCurrentFramebufferIndex];
    gSPSegment(gGfxHead++, 0x00, NULL);
    S2RDPinitRtn(true);
    S2ClearCFBRtn(true);

    gSPDisplayList(gGfxHead++, D_800881E0);
    gDPSetScissor(gGfxHead++, G_SC_NON_INTERLACE, 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1);

    title_exit_flag = demo_title(&gGfxHead, evs_level_21 != 0);

    color = 255;
    alpha = CLAMP((title_fade_count - 127) * 1.2 + 127, 0.0, 255.0);
    if (alpha > 0) {
        FillRectRGBA(&gGfxHead, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, color, color, color, alpha);
    }

    gDPFullSync(gGfxHead++);
    gSPEndDisplayList(gGfxHead++);
    osWritebackDCacheAll();

    gfxTaskStart(ptr, gGfxGlist[gCurrentFramebufferIndex],
                 (gGfxHead - gGfxGlist[gCurrentFramebufferIndex]) * sizeof(Gfx), 0, OS_SC_SWAPBUFFER);
}

const char D_800B32A8[] RODATA = "This game is not designed~nfor use on this system.~z";

/**
 * Original name: _mesBootContErr
 */
const char _mesBootContErr[] RODATA =
    "There is no controller~nconnected. Please turn OFF~nthe Nintendo* 64 and insert~na controller in socket 1.~z";

/**
 * Original name: _mesBootCSumErr
 */
const char _mesBootCSumErr[] RODATA = "A Backup File is damaged.~nPress the A Button to delete this file.~z";

/**
 * Original name: main_boot_error
 */
enum_main_no main_boot_error(struct_800EB670 *arg0) {
    OSMesgQueue sp18;
    OSMesg sp30[8];
    struct_800FAF98_unk_64 sp50;
    UNK_PTR sp58;
    MessageWnd *messageWnd = ALIGN_PTR(Heap_bufferp);
    bool var_s1 = true;

    sp58 = &messageWnd[1];
    bzero(messageWnd, sizeof(MessageWnd));
    osCreateMesgQueue(&sp18, sp30, ARRAY_COUNT(sp30));
    func_8002A184(arg0, &sp50, &sp18);

    switch (main_no) {
        case MAIN_NO_8:
            msgWnd_init(messageWnd, &sp58, 0x40, 5, 0x40, 0x60);
            msgWnd_addStr(messageWnd, _mesBootContErr);
            break;

        case MAIN_NO_9:
            msgWnd_init(messageWnd, &sp58, 0x40, 5, 0x40, 0x72);
            msgWnd_addStr(messageWnd, D_800B32A8);
            break;

        case MAIN_NO_10:
            msgWnd_init(messageWnd, &sp58, 0x40, 5, 0x28, 0x6C);
            msgWnd_addStr(messageWnd, _mesBootCSumErr);
            break;

        default:
            break;
    }

    msgWnd_skip(messageWnd);

    while (var_s1) {
        joyProcCore();
        osRecvMesg(&sp18, NULL, OS_MESG_BLOCK);
        msgWnd_update(messageWnd);
        if ((main_no == MAIN_NO_10) && (gControllerPressedButtons[B_800EBD16[0]] & A_BUTTON)) {
            var_s1 = false;
            dm_snd_play(SND_INDEX_70);
        }
        dm_audio_update();
        graphic_no = GRAPHIC_NO_7;
    }

    graphic_no = GRAPHIC_NO_0;
    while (pendingGFX != 0) {
        osRecvMesg(&sp18, NULL, OS_MESG_BLOCK);
    }

    func_8002A1DC(arg0, &sp50);
    if (main_no == MAIN_NO_10) {
        EepRom_WriteAll(0, 0);
    }
    return MAIN_NO_3;
}

/**
 * Original name: graphic_boot_error
 */
void graphic_boot_error(void) {
    MessageWnd *ptr;

    gGfxHead = gGfxGlist[gfx_gtask_no];
    ptr = ALIGN_PTR(&Heap_bufferp);
    F3RCPinitRtn();
    F3ClearFZRtn(true);
    msgWnd_draw(ptr, &gGfxHead);

    gDPFullSync(gGfxHead++);
    gSPEndDisplayList(gGfxHead++);

    osWritebackDCacheAll();
    gfxTaskStart(&B_800FAE80[gfx_gtask_no], gGfxGlist[gfx_gtask_no], (gGfxHead - gGfxGlist[gfx_gtask_no]) * sizeof(Gfx),
                 0, OS_SC_SWAPBUFFER);
}

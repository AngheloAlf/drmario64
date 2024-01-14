/**
 * Original filename: dm_title_main.c
 */

#include "dm_title_main.h"

#include "include_asm.h"
#include "macros_defines.h"
#include "unknown_structs.h"
#include "boot_functions.h"
#include "boot_variables.h"
#include "main_segment_variables.h"
#include "rom_offsets.h"
#include "audio/sound.h"
#include "buffers.h"
#include "graphic.h"
#include "joy.h"
#include "record.h"
#include "vr_init.h"
#include "graphics/graphic_dlists.h"
#include "main1x.h"
#include "tex_func.h"
#include "main_story.h"
#include "nnsched.h"

void func_80075F30(void) {
    title_exit_flag = 0;
    title_mode_type = 0;

    title_fade_count = main_old == MAIN_NO_6 ? 0xFF : 0;
    title_fade_step = -8;
    evs_seqence = 0;
    init_title(Heap_bufferp, main_old != MAIN_NO_6);
}

/**
 * Original name: _stageTbl
 */
const u8 _stageTbl[] = {
    STORY_PROC_NO_1,  STORY_PROC_NO_2,  STORY_PROC_NO_3,  STORY_PROC_NO_4,  STORY_PROC_NO_5,  STORY_PROC_NO_6,
    STORY_PROC_NO_7,  STORY_PROC_NO_8,  STORY_PROC_NO_9,  STORY_PROC_NO_13, STORY_PROC_NO_14, STORY_PROC_NO_15,
    STORY_PROC_NO_16, STORY_PROC_NO_17, STORY_PROC_NO_18, STORY_PROC_NO_19, STORY_PROC_NO_20, STORY_PROC_NO_21,
};

/**
 * Original name: dm_title_main
 */
enum_main_no dm_title_main(NNSched *sc) {
    OSMesgQueue scMQ;
    OSMesg scMsgBuf[NN_SC_MAX_MESGS];
    NNScClient scClient;
    s32 var_s1 = (main_old == MAIN_NO_6) ? 0x63 : 0;
    u32 var_s0 = 0;

    osCreateMesgQueue(&scMQ, scMsgBuf, ARRAY_COUNT(scMsgBuf));
    nnScAddClient(sc, &scClient, &scMQ);

    sgenrand(osGetCount());
    func_80075F30();
    evs_playmax = joyResponseCheck();
    osRecvMesg(&scMQ, NULL, OS_MESG_BLOCK);

#if VERSION_US
    graphic_no = GRAPHIC_NO_2;
#endif

    do {
        joyProcCore();
        osRecvMesg(&scMQ, NULL, OS_MESG_BLOCK);

#ifdef NN_SC_PERF
        if (D_80092F10_cn) {
            graphic_no = GRAPHIC_NO_0;
            dm_audio_update();
            continue;
        }
#endif
        title_fade_count = CLAMP(title_fade_count + title_fade_step, 0, 0xFF);

        switch (title_mode_type) {
            case 0:
                var_s1++;
                if (title_exit_flag == -1) {
                    title_mode_type = 7;
                } else {
                    if (var_s1 == 0x64) {
                        dm_seq_play(SEQ_INDEX_11);
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

#ifdef NN_SC_PERF
        graphic_no = GRAPHIC_NO_2;
#endif
    } while (var_s0 == 0);

    dm_seq_stop();

    while (!dm_audio_is_stopped() || (title_fade_count < 0xFF)) {
        osRecvMesg(&scMQ, NULL, OS_MESG_BLOCK);
        dm_audio_update();

        title_fade_count = CLAMP(title_fade_count + title_fade_step, 0, 0xFF);
    }

    graphic_no = GRAPHIC_NO_0;
    while (pendingGFX != 0) {
        osRecvMesg(&scMQ, NULL, OS_MESG_BLOCK);
        dm_audio_update();
    }

    nnScRemoveClient(sc, &scClient);

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

        evs_gamemode = ENUM_EVS_GAMEMODE_0;

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

    gSPDisplayList(gGfxHead++, S2Spriteinit_dl);
    gDPSetScissor(gGfxHead++, G_SC_NON_INTERLACE, 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1);

    title_exit_flag = demo_title(&gGfxHead, evs_level_21 != 0);

    color = 255;
    alpha = CLAMP((title_fade_count - 127) * 1.2 + 127, 0.0, 255.0);
    if (alpha > 0) {
        FillRectRGBA(&gGfxHead, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, color, color, color, alpha);
    }

#ifdef NN_SC_PERF
    func_8002BD7C_cn(&gGfxHead, 0x20, 0xB4);
#endif

    gDPFullSync(gGfxHead++);
    gSPEndDisplayList(gGfxHead++);
    osWritebackDCacheAll();

    gfxTaskStart(ptr, gGfxGlist[gCurrentFramebufferIndex],
                 (gGfxHead - gGfxGlist[gCurrentFramebufferIndex]) * sizeof(Gfx), 0, OS_SC_SWAPBUFFER);
}

#include "build/src/main_segment/dm_title_main.msg.inc"

/**
 * Original name: main_boot_error
 */
enum_main_no main_boot_error(NNSched *sc) {
    OSMesgQueue scMQ;
    OSMesg scMsgBuf[NN_SC_MAX_MESGS];
    NNScClient scClient;
    void *sp58;
    MessageWnd *messageWnd = ALIGN_PTR(Heap_bufferp);
    bool var_s1 = true;

    sp58 = messageWnd + 1;
    bzero(messageWnd, sizeof(MessageWnd));

    osCreateMesgQueue(&scMQ, scMsgBuf, ARRAY_COUNT(scMsgBuf));
    nnScAddClient(sc, &scClient, &scMQ);

    switch (main_no) {
        case MAIN_NO_8:
            msgWnd_init(messageWnd, &sp58, 0x40, 5, 0x40, 0x60);
            msgWnd_addStr(messageWnd, _mesBootContErr);
            break;

        case MAIN_NO_9:
            msgWnd_init(messageWnd, &sp58, 0x40, 5, 0x40, 0x72);
            msgWnd_addStr(messageWnd, STR_800B32A8);
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
        osRecvMesg(&scMQ, NULL, OS_MESG_BLOCK);

#ifdef NN_SC_PERF
        if (D_80092F10_cn) {
            graphic_no = GRAPHIC_NO_0;
            dm_audio_update();
            continue;
        }
#endif

        msgWnd_update(messageWnd);
        if ((main_no == MAIN_NO_10) && (gControllerPressedButtons[main_joy[0]] & A_BUTTON)) {
            var_s1 = false;
            dm_snd_play(SND_INDEX_70);
        }
        dm_audio_update();
        graphic_no = GRAPHIC_NO_7;
    }

    graphic_no = GRAPHIC_NO_0;
    while (pendingGFX != 0) {
        osRecvMesg(&scMQ, NULL, OS_MESG_BLOCK);
    }

    nnScRemoveClient(sc, &scClient);
    if (main_no == MAIN_NO_10) {
        EepRom_WriteAll(NULL, 0);
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

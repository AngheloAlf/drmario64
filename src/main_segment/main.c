/**
 * Original filename: main.c
 */

#include "main.h"

#include "unk.h"
#include "macros_defines.h"

#include "boot_main.h"

#include "aiset.h"
#include "audio/sound.h"
#include "buffers.h"
#include "dm_game_main.h"
#include "dm_manual_main.h"
#include "dm_title_main.h"
#include "graphic.h"
#include "joy.h"
#include "record.h"
#include "main1x.h"
#include "main_story.h"
#include "main_menu.h"
#include "nnsched.h"

NNSched B_800EB670;

/**
 * Original name: main_no
 */
enum_main_no main_no;

/**
 * Orignal name: main_old
 */
enum_main_no main_old;

/**
 * Original name: mainproc
 */
void mainproc(void *arg UNUSED) {
    EepRom_DumpDataSize();

    switch (osTvType) {
        case OS_TV_NTSC:
            nnScCreateScheduler(&B_800EB670, OS_VI_NTSC_LAN1, 1);
            main_no = MAIN_NO_0;
            break;

        case OS_TV_MPAL:
            nnScCreateScheduler(&B_800EB670, OS_VI_MPAL_LAN1, 1);
            main_no = MAIN_NO_0;
            break;

        case OS_TV_PAL:
            nnScCreateScheduler(&B_800EB670, OS_VI_PAL_LAN1, 1);
            main_no = MAIN_NO_9;
            break;

        default:
            nnScCreateScheduler(&B_800EB670, OS_VI_NTSC_LAN1, 1);
            main_no = MAIN_NO_9;
            break;
    }

    dm_audio_init_driver(&B_800EB670);
    gfxInit(gfx_freebuf);
    gfxCreateGraphicThread(&B_800EB670);
    osViSetSpecialFeatures(OS_VI_DITHER_FILTER_ON | OS_VI_GAMMA_DITHER_OFF | OS_VI_GAMMA_OFF);
    joyInit(MAXCONTROLLERS);
    evs_playmax = joyResponseCheck();

    if ((evs_playmax == 0) && (main_no == MAIN_NO_0)) {
        main_no = MAIN_NO_8;
    }

    aifFirstInit();
    func_80000488(make_ai_main);

    while (true) {
        enum_main_no temp_s0 = main_no;

        switch (main_no) {
            case MAIN_NO_0:
                main_no = main11();
                break;

            case MAIN_NO_1:
                main_no = main12();
                break;

            case MAIN_NO_3:
                main_no = dm_title_main(&B_800EB670);
                break;

            case MAIN_NO_4:
                main_no = dm_manual_main(&B_800EB670);
                break;

            case MAIN_NO_5:
                main_no = dm_game_main(&B_800EB670);
                break;

            case MAIN_NO_6:
                main_no = main_menu(&B_800EB670);
                break;

            case MAIN_NO_7:
                main_no = main_techmes(&B_800EB670);
                break;

            case MAIN_NO_8:
            case MAIN_NO_9:
            case MAIN_NO_10:
                main_no = main_boot_error(&B_800EB670);
                break;

            case MAIN_NO_2:
                main_story(&B_800EB670);

                if ((story_proc_no == BGROMDATA_INDEX0) || (story_proc_no == BGROMDATA_INDEX12)) {
                    story_proc_no++;
                    main_no = MAIN_NO_2;
                } else if (((story_proc_no - BGROMDATA_INDEX10) >= BGROMDATA_INDEX12 - BGROMDATA_INDEX10) &&
                           (story_proc_no != BGROMDATA_INDEX22) && (story_proc_no != BGROMDATA_INDEX23)) {
                    main_no = MAIN_NO_1;
                } else {
                    main_no = MAIN_NO_7;
                }
                break;
        }

        main_old = temp_s0;
    }
}

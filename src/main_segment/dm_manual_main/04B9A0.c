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
        func_8006D7B0();

        temp_s2->unk_184++;
        if (temp_s2->unk_010 > 0) {
            var_s4 = temp_s2->unk_00C == 0xFF;
        }

        temp_s2->unk_00C = CLAMP(temp_s2->unk_00C + temp_s2->unk_010, 0, 0xFF);
        switch (D_80088410) {
            case 0x0:
                var_s3 = func_80072AB4();
                break;
            case 0x1:
                var_s3 = func_800733AC();
                break;
            case 0x2:
                var_s3 = func_800739D8();
                break;
            case 0x3:
                var_s3 = func_80074330();
                break;
        }
        dm_seq_set_volume(0x60);
        dm_audio_update();
        if (temp_s2->unk_018 != 0) {
            temp_s2->unk_014++;
            if (temp_s2->unk_014 >= temp_s2->unk_018) {
                temp_s2->unk_014 = 0;
                temp_s2->unk_018 = 0;
                dm_seq_play_in_game(D_80088402 * 2);
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

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_manual_main/04B9A0", dm_manual_graphic);

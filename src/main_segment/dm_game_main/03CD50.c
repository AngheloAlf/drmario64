#include "ultra64.h"
#include "include_asm.h"
#include "macros_defines.h"
#include "unknown_structs.h"
#include "main_segment_functions.h"
#include "main_segment_variables.h"

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/03CD50", func_800669A0);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/03CD50", dm_calc_big_virus_pos);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/03CD50", dm_game_main_1p);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/03CD50", func_8006729C);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/03CD50", func_800673FC);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/03CD50", func_800674EC);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/03CD50", func_800675C8);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/03CD50", func_80067668);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/03CD50", dm_game_main_2p);

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/03CD50", D_800B2068);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/03CD50", D_800B2070);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/03CD50", dm_game_main_4p);

bool dm_game_demo_1p(void) {
    struct_800F3E50 *ptr = watchGame;
    s32 temp_s4 = dm_game_main_cnt_1P(game_state_data, game_map_data, 0);
    s32 i;

    dm_warning_h_line_se();

    for (i = 0; i < 3; i++) {
        AnimeState *animeState = &ptr->animeStates[i];
        AnimeSmog *animeSmog = &ptr->animeSmogs[i];

        animeState_update(animeState);
        animeSmog_update(animeSmog);
    }

    dm_calc_big_virus_pos(game_state_data);

    if ((temp_s4 == 3) && (ptr->unk_3AC < 0)) {
        game_state_data->unk_00C = temp_s4;
        animeState_set(&game_state_data->unk_094, 1);
        if ((game_state_data->unk_04C == 1) || (aiDebugP1 >= 0)) {
            aifMakeFlagSet(game_state_data);
        }

        ptr->unk_3C4 = 1;
    }

    if (ptr->unk_41C != 0) {
        ptr->unk_41C--;

        if (gControllerPressedButtons[main_joy[0]] & ALL_BUTTONS) {
            ptr->unk_41C = 0;
        }

        if (ptr->unk_41C == 0) {
            return true;
        }
    }

    return false;
}

bool dm_game_demo_2p(void) {
    struct_800F3E50 *ptr = watchGame;
    s32 sp10[2];
    s32 i;

    for (i = 0; i < ARRAY_COUNT(sp10); i++) {
        sp10[i] = dm_game_main_cnt(&game_state_data[i], &game_map_data[i], i);
    }

    dm_warning_h_line_se();
    if ((sp10[0] == 3) && (sp10[1] == sp10[0]) && (ptr->unk_3AC < 0)) {
        for (i = 0; i < ARRAY_COUNT(sp10); i++) {
            s32 temp;
            struct_80123700 *temp2 = &game_state_data[i];

            game_state_data[i].unk_00C = 4;
            temp = temp2->unk_04C;

            if ((temp == 1) || (((temp != 1) && (i == 0)) && (aiDebugP1 >= 0))) {
                aifMakeFlagSet(temp2);
            }
        }

        ptr->unk_3C4 = 1;
    }

    if (ptr->unk_41C != 0) {
        ptr->unk_41C--;
        if (gControllerPressedButtons[main_joy[0]] & ALL_BUTTONS) {
            ptr->unk_41C = 0;
        }

        if (ptr->unk_41C == 0) {
            return true;
        }
    }

    return false;
}

bool dm_game_demo_4p(void) {
    struct_800F3E50 *ptr = watchGame;
    s32 sp10[4];
    s32 i;

    for (i = 0; i < ARRAY_COUNT(sp10); i++) {
        sp10[i] = dm_game_main_cnt(&game_state_data[i], &game_map_data[i], i);
    }

    dm_warning_h_line_se();
    if ((sp10[0] == 3) && (sp10[1] == sp10[0]) && (sp10[2] == sp10[1]) && (sp10[3] == sp10[2]) && (ptr->unk_3AC < 0)) {
        for (i = 0; i < ARRAY_COUNT(sp10); i++) {
            struct_80123700 *temp2 = &game_state_data[i];

            game_state_data[i].unk_00C = 4;

            if ((temp2->unk_04C == 1) || (((temp2->unk_04C != 1) && (i == 0)) && (aiDebugP1 >= 0))) {
                aifMakeFlagSet(temp2);
            }
        }

        ptr->unk_3C4 = 1;
    }

    if (ptr->unk_41C != 0) {
        ptr->unk_41C--;

        if (gControllerPressedButtons[main_joy[0]] & ALL_BUTTONS) {
            ptr->unk_41C = 0;
        }

        if (ptr->unk_41C == 0) {
            return true;
        }
    }

    return false;
}

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/03CD50", func_80068DC0);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/03CD50", func_80068DE8);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/03CD50", func_80068E24);

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/03CD50", RO_800B20D0);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/03CD50", func_80069160);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/03CD50", func_80069188);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/03CD50", func_800691F8);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/03CD50", func_800695A8);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/03CD50", func_8006967C);

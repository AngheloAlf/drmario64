/**
 * Some functions are part of dm_game_main.c, not sure if all of them
 */

#include "ultra64.h"
#include "include_asm.h"
#include "macros_defines.h"
#include "unknown_structs.h"
#include "main_segment_functions.h"
#include "main_segment_variables.h"

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/036620", func_80060270);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/036620", dm_make_score);

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/036620", D_800B1C4C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/036620", D_800B1C5C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/036620", D_800B1C74);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/036620", D_800B1C78);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/036620", RO_800B1C80);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/036620", RO_800B1C8C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/036620", RO_800B1C98);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/036620", RO_800B1CA4);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/036620", STR_800B1CB8);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/036620", STR_800B1CE0);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/036620", D_800B1D08);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/036620", D_800B1D18);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/036620", D_800B1D1C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/036620", D_800B1D28);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/036620", D_800B1D2C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/036620", D_800B1D30);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/036620", D_800B1D5C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/036620", D_800B1D60);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/036620", D_800B1D7C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/036620", D_800B1D80);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/036620", D_800B1D84);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/036620", D_800B1D88);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/036620", D_800B1D8C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/036620", D_800B1DBC);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/036620", D_800B1E7C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/036620", RO_800B1E80);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/036620", D_800B1E8C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/036620", D_800B1E90);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/036620", RO_800B1E9C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/036620", RO_800B1EA0);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/036620", func_80060348);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/036620", func_80060424);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/036620", set_down_flg);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/036620", go_down);

void erase_anime(struct_800EBEF0 *arg0) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(arg0->unk_000); i++) {
        struct_800EBEF0_unk_000 *var_s0 = &arg0->unk_000[i];

        if ((var_s0->unk_4 != 0) && (var_s0->unk_6 != 0)) {
            var_s0->unk_2++;

            if (var_s0->unk_8 >= 0) {
                if (var_s0->unk_2 >= 0xF) {
                    clear_map(arg0, var_s0->unk_0, var_s0->unk_1);
                }
            } else {
                if (var_s0->unk_2 >= 7) {
                    clear_map(arg0, var_s0->unk_0, var_s0->unk_1);
                }
            }
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/036620", func_800609B8);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/036620", func_80060A6C);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/036620", func_80060C1C);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/036620", func_80060E10);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/036620", func_80060F60);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/036620", func_80060FA0);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/036620", func_80060FCC);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/036620", func_800610E0);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/036620", func_80061184);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/036620", func_80061194);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/036620", func_8006121C);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/036620", dm_set_virus);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/036620", func_800613D0);

void func_80061490(struct_80123700 *arg0, struct_800EBEF0 *arg1) {
    arg0->unk_036++;

    if (arg0->unk_036 == 10) {
        erase_anime(arg1);
        arg0->unk_035++;
    } else if (arg0->unk_036 > 26) {
        erase_anime(arg1);
        set_down_flg(arg1);
        arg0->unk_00C = 8;
        arg0->unk_035 = 0;
        arg0->unk_036 = 14;
    }
}

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/036620", func_8006151C);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/036620", dm_h_erase_chack);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/036620", dm_h_erase_chack_set);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/036620", func_800618B0);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/036620", dm_w_erase_chack);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/036620", dm_w_erase_chack_set);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/036620", dm_h_ball_chack);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/036620", dm_w_ball_chack);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/036620", func_80061DB8);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/036620", func_80061E7C);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/036620", dm_calc_erase_score_pos);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/036620", func_800620FC);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/036620", func_8006258C);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/036620", func_800626A4);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/036620", dm_game_heap_top);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/036620", func_800628A4);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/036620", func_800628BC);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/036620", dm_get_mtx_buf);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/036620", dm_get_vtx_buf);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/036620", initEtcWork);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/036620", func_80062978);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/036620", func_80062990);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/036620", func_800629AC);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/036620", func_800629C8);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/036620", func_800629E4);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/036620", func_80062A08);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/036620", func_80062A24);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/036620", func_80062A40);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/036620", func_80062A5C);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/036620", func_80062A8C);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/036620", func_80062AA8);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/036620", func_80062AC4);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/036620", func_80062AE0);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/036620", func_80062AFC);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/036620", func_80062B18);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/036620", func_80062B34);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/036620", func_80062B50);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/036620", func_80062B84);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/036620", func_80062BC4);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/036620", func_80062BD4);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/036620", func_80062DA4);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/036620", func_80062DD8);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/036620", func_80062E84);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/036620", func_80062EC0);

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/036620", D_800B1EB8);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/036620", scoreNums_set);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/036620", backup_game_state);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/036620", resume_game_state);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/036620", func_80063378);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/036620", func_800633C0);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/036620", func_800633FC);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/036620", dm_warning_h_line_se);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/036620", func_800634E8);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/036620", func_800635BC);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/036620", func_80063844);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/036620", func_800638AC);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/036620", func_80063A80);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/036620", func_80063FF4);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/036620", func_8006408C);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/036620", func_80064130);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/036620", func_8006417C);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/036620", retryMenu_input);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/036620", func_80064298);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/036620", func_8006431C);

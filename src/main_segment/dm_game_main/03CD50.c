#include "ultra64.h"
#include "include_asm.h"
#include "macros_defines.h"
#include "unknown_structs.h"
#include "main_segment_functions.h"
#include "main_segment_variables.h"
#include "audio/audio_stuff.h"

void func_800669A0(struct_80123700 *arg0) {
    struct_80123700 *sp10 = arg0;

    dm_set_pause_and_volume(&sp10, 1);
}

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/03CD50", dm_calc_big_virus_pos);

s32 dm_game_main_1p(void) {
    s32 temp_s3;
    struct_800F3E50 *temp_s5 = watchGame;
    struct_80123700 *temp = game_state_data;

    func_800669A0(temp);
    temp_s3 = dm_game_main_cnt_1P(temp, game_map_data, 0);
    dm_warning_h_line_se();
    if (temp_s5->unk_410 == 0) {
        s32 var_s2;

        for (var_s2 = 0; var_s2 < 3; var_s2++) {
            animeState_update(&temp_s5->animeStates[var_s2]);
            animeSmog_update(&temp_s5->animeSmogs[var_s2]);
        }
    }

    dm_calc_big_virus_pos(temp);
    dm_play_count_down_se();

    if (temp_s3 == 3) {
        if (temp_s5->unk_3AC < 0) {
            if (temp->unk_00C == 2) {
                temp_s5->unk_3C4 = 1;
                temp->unk_00C = temp_s3;
                animeState_set(&temp->unk_094, 1);
                func_800633FC();
            }
        }
    } else if (temp_s3 == 6) {
        s32 temp_s1;

        func_80062A24(temp->unk_04B);
        dm_seq_play_in_game(0xE);
        temp_s5->unk_3C4 = 0;
        temp->unk_020 = 5;

        if (evs_gamemode == ENUM_EVS_GAMEMODE_3) {
            s32 temp_v0;

            temp->unk_014 = 0x13;
            temp->unk_00C = 0x1A;

            temp_v0 = (0x2A30 - evs_game_time);
            func_80062DD8(&temp_s5->unk_9C8[8], temp->unk_16C, 1, temp_v0 & (~temp_v0 >> 0x1F), temp->unk_174,
                          temp->unk_170, temp->unk_000);
        } else {
            temp->unk_014 = 3;
            temp->unk_00C = 0xA;
        }

        switch (evs_gamemode) {
            case ENUM_EVS_GAMEMODE_3:
                func_80064130(0U, 3);
                break;

            case ENUM_EVS_GAMEMODE_0:
                func_80064130(0U, 5);
                break;

            default:
                break;
        }

        animeState_set(&temp->unk_094, 3);

        switch (evs_gamemode) {
            case ENUM_EVS_GAMEMODE_3:
                temp_s1 = game_state_data->unk_000;
                game_state_data->unk_000 = temp_s5->unk_9F8;
                dm_save_all();
                game_state_data->unk_000 = temp_s1;
                break;

            case ENUM_EVS_GAMEMODE_0:
                dm_save_all();
                break;

            default:
                break;
        }
    } else if (temp_s3 == -1) {
        func_80062A08(temp->unk_04B);
        animeState_set(&temp->unk_094, 4);
        dm_seq_play_in_game(0x11);
        temp->unk_028[3] = 1;
        temp->unk_020 = 8;
        if (evs_gamemode == ENUM_EVS_GAMEMODE_3) {
            temp->unk_014 = 0x15;
            temp->unk_00C = 0x1C;

            func_80062DD8(&temp_s5->unk_9C8[8], temp->unk_16C, 0, 0, temp->unk_174, temp->unk_170, temp->unk_000);
            temp_s5->unk_3C4 = 0;
        } else {
            temp->unk_014 = 4;
            temp->unk_00C = 0xB;
            temp_s5->unk_3C4 = 0;
        }

        if ((temp->unk_026 < 0x16U) || ((temp_s5->unk_378 > 0))) {
            func_80064130(0U, 3);
        } else {
            func_80064130(0U, 2);
        }

        dm_save_all();
    } else {
        if (temp_s3 == 1) {
            return 1;
        }
        if (temp_s3 == 2) {
            return 2;
        }
        if (temp_s3 == 9) {
            return 9;
        }
        if (temp_s3 == 0x64) {
            return -1;
        }
        if (temp_s3 == -2) {
            return -2;
        }
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/03CD50", func_8006729C);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/03CD50", func_800673FC);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/03CD50", func_800674EC);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/03CD50", func_800675C8);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/03CD50", func_80067668);

#if 0
// ? func_80062A40(s32);                               /* extern */
// s32 func_80062BC4(void *);                          /* extern */
// s32 func_8006729C(struct_80123700 *);               /* extern */
// s32 func_800673FC(struct_80123700 *, s32, s32);     /* extern */
// s32 func_800674EC(struct_80123700 *, s32, s32);     /* extern */
// s32 func_800675C8(struct_80123700 *, s32);          /* extern */
// s32 func_80067668(struct_80123700 **);              /* extern */

s32 dm_game_main_2p(void) {
    struct_80123700 *sp20;
    s32 sp3C;
    s32 sp44;
    s32 temp_a2;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 var_fp;
    s32 var_s1;
    s32 var_s1_10;
    s32 var_s1_11;
    s32 var_s1_12;
    s32 var_s1_13;
    s32 var_s1_2;
    s32 var_s1_3;
    s32 var_s1_4;
    s32 var_s1_5;
    s32 var_s1_6;
    s32 var_s1_7;
    s32 var_s1_8;
    s32 var_s1_9;
    s32 var_s2;
    s32 var_s3;
    s32 var_s4;
    s32 var_s5;
    s32 var_s6;
    s32 var_v0;
    struct_800EBEF0 *var_a1;
    struct_800F3E50 *temp_s7;
    struct_800F3E50 *var_s2_2;
    struct_80123700 **var_a1_2;
    struct_80123700 **var_s0;
    struct_80123700 **var_s0_10;
    struct_80123700 **var_s0_11;
    struct_80123700 **var_s0_2;
    struct_80123700 **var_s0_3;
    struct_80123700 **var_s0_4;
    struct_80123700 **var_s0_5;
    struct_80123700 **var_s0_6;
    struct_80123700 **var_s0_7;
    struct_80123700 **var_s0_8;
    struct_80123700 **var_s0_9;
    struct_80123700 **var_v1;
    struct_80123700 **var_v1_2;
    struct_80123700 *temp_a0;
    struct_80123700 *temp_a0_2;
    struct_80123700 *temp_a0_3;
    struct_80123700 *temp_a0_4;
    struct_80123700 *temp_a0_5;
    struct_80123700 *temp_a0_6;
    struct_80123700 *temp_a0_7;
    struct_80123700 *temp_a0_8;
    struct_80123700 *temp_a0_9;
    struct_80123700 *temp_t0;
    struct_80123700 *temp_v1_3;
    struct_80123700 *var_a0;
    u8 temp_v0_3;

    temp_s7 = watchGame;
    var_s6 = 0;
    var_fp = 0;
    var_s1 = 0;
    var_a1 = game_map_data;
    var_v1 = &sp20;
    var_a0 = game_state_data;
    sp44 = 0;
    sp3C = 0;
    do {
        var_v1->unk_8 = var_a1;
        var_a1 += 0x550;
        var_v1->unk_0 = var_a0;
        var_v1 += 4;
        var_s1 += 1;
        var_a0 += 0x3C4;
    } while (var_s1 < 2);
    dm_set_pause_and_volume(&sp20, 2);
    var_s1_2 = 0;
    var_s0 = &sp20;
    do {
        temp_a2 = var_s1_2;
        var_s1_2 += 1;
        var_s0->unk_10 = dm_game_main_cnt(var_s0->unk_0, var_s0->unk_8, temp_a2);
        var_s0 += 4;
    } while (var_s1_2 < 2);
    dm_warning_h_line_se();
    dm_play_count_down_se();
    if (sp30 != 3) {
        var_s1_3 = 0;
        goto block_26;
    }
    if (sp34 != sp30) {
        var_s1_3 = 0;
block_26:
        var_s0_2 = &sp20;
        var_s2 = 0x9D0;
loop_27:
        temp_v1 = var_s0_2->unk_10;
        switch (temp_v1) {                          /* switch 1; irregular */
            case 0x6:                               /* switch 1 */
                if (evs_gamemode == ENUM_EVS_GAMEMODE_3) {
                    func_80062A24(var_s1_3);
                    var_s0_2->unk_0->unk_00C = 0x1A;
                    var_s0_2->unk_0->unk_014 = 0x13;
                    var_s0_2->unk_0->unk_020 = (u32) 0x13;
                    temp_t0 = var_s0_2->unk_0;
                    temp_v0 = 0x2A30 - evs_game_time;
                    func_80062DD8(temp_s7 + var_s2, temp_t0->unk_16C, 1, temp_v0 & ((s32) ~temp_v0 >> 0x1F), temp_t0->unk_174, var_s0_2->unk_0->unk_170, var_s0_2->unk_0->unk_000);
                    _dm_seq_play_in_game(1, 0x10);
                    var_s0_2 += 4;
                } else {
                    sp3C += 1;
                    var_s0_2->unk_0->unk_020 = 5;
block_43:
                    var_s0_2 += 4;
                }
                var_s1_3 += 1;
                var_s2 += 0x2C;
                if (var_s1_3 >= 2) {
                    var_s5 = 0;
                    var_s4 = 0;
                    var_s1_4 = 0;
                    var_s3 = 0x9D0;
                    var_s2_2 = temp_s7;
                    var_s0_3 = &sp20;
                    do {
                        temp_v0_2 = (*var_s0_3)->unk_014;
                        switch (temp_v0_2) {
                            case 0x13:
                            case 0x15:
                            case 0x17:
                                var_s4 += var_s2_2->unk_888 == 0;
                                break;
                            case 0x14:
                            case 0x16:
                            case 0x18:
                                var_s5 += func_80062BC4(temp_s7 + var_s3) != 0;
                                break;
                        }
                        var_s3 += 0x2C;
                        var_s2_2 += 4;
                        var_s1_4 += 1;
                        var_s0_3 += 4;
                    } while (var_s1_4 < 2);
                    var_s1_5 = 0;
                    if (var_s4 == 2) {
                        var_a1_2 = &sp20;
                        do {
                            temp_a0 = *var_a1_2;
                            temp_v1_2 = temp_a0->unk_014;
                            if (temp_v1_2 != 0x15) {
                                if ((u32) temp_v1_2 < 0x16U) {
                                    if (temp_v1_2 == 0x13) {
                                        temp_a0->unk_020 = 0x14;
                                        (*var_a1_2)->unk_014 = (s32) 0x14U;
                                        (*var_a1_2)->unk_00C = 0x1B;
                                        goto block_66;
                                    }
                                    var_s1_5 += 1;
                                } else {
                                    if (temp_v1_2 == 0x17) {
                                        temp_a0->unk_020 = 0x18;
                                        (*var_a1_2)->unk_014 = (s32) 0x18U;
                                        (*var_a1_2)->unk_00C = 0x1F;
                                        goto block_66;
                                    }
                                    var_s1_5 += 1;
                                }
                            } else {
                                temp_a0->unk_020 = 0x16;
                                (*var_a1_2)->unk_014 = (s32) 0x16U;
                                (*var_a1_2)->unk_00C = 0x1D;
block_66:
                                var_s1_5 += 1;
                            }
                            var_a1_2 += 4;
                        } while (var_s1_5 < 2);
                    } else if (var_s5 == 2) {
                        var_fp = func_80067668(&sp20);
                    } else {
                        var_s1_6 = 0;
                        if (((sp3C == 2) | (sp44 == 2)) != 0) {
                            var_s0_4 = &sp20;
                            do {
                                temp_a0_2 = *var_s0_4;
                                var_s0_4 += 4;
                                var_s1_6 += 1;
                                var_s6 = func_800675C8(temp_a0_2, var_s6);
                            } while (var_s1_6 < 2);
                            dm_seq_play_in_game(0x11);
                        } else if (sp3C != 0) {
                            var_s0_5 = &sp20;
                            do {
                                temp_a0_3 = *var_s0_5;
                                var_s1_6 += 1;
                                if (temp_a0_3->unk_020 == 5) {
                                    var_fp = func_8006729C(temp_a0_3);
                                }
                                var_s0_5 += 4;
                            } while (var_s1_6 < 2);
                            var_s1_7 = 0;
                            var_s0_6 = &sp20;
                            do {
                                temp_a0_4 = *var_s0_6;
                                if (temp_a0_4->unk_020 == 5) {
                                    var_s6 = func_800673FC(temp_a0_4, var_fp, var_s6);
                                }
                                var_s1_7 += 1;
                                var_s0_6 += 4;
                            } while (var_s1_7 < 2);
                            var_s1_8 = 0;
                            var_s0_7 = &sp20;
                            do {
                                temp_a0_5 = *var_s0_7;
                                if (temp_a0_5->unk_020 != 5) {
                                    var_s6 = func_800674EC(temp_a0_5, var_fp, var_s6);
                                }
                                var_s1_8 += 1;
                                var_s0_7 += 4;
                            } while (var_s1_8 < 2);
                        } else if (sp44 != 0) {
                            var_s1_9 = 0;
                            var_s0_8 = &sp20;
                            do {
                                temp_a0_6 = *var_s0_8;
                                var_s1_9 += 1;
                                if (temp_a0_6->unk_020 != 8) {
                                    var_fp = func_8006729C(temp_a0_6);
                                }
                                var_s0_8 += 4;
                            } while (var_s1_9 < 2);
                            var_s1_10 = 0;
                            var_s0_9 = &sp20;
                            do {
                                temp_a0_7 = *var_s0_9;
                                if (temp_a0_7->unk_020 != 8) {
                                    var_s6 = func_800673FC(temp_a0_7, var_fp, var_s6);
                                }
                                var_s1_10 += 1;
                                var_s0_9 += 4;
                            } while (var_s1_10 < 2);
                            var_s1_11 = 0;
                            var_s0_10 = &sp20;
                            do {
                                temp_a0_8 = *var_s0_10;
                                if (temp_a0_8->unk_020 == 8) {
                                    var_s6 = func_800674EC(temp_a0_8, var_fp, var_s6);
                                }
                                var_s1_11 += 1;
                                var_s0_10 += 4;
                            } while (var_s1_11 < 2);
                        }
                    }
                    var_v0 = 0;
                    if (var_fp != 0) {
                        dm_save_all();
                        var_v0 = 0;
                    }
                    /* Duplicate return node #107. Try simplifying control flow for better match */
                    return var_v0;
                }
                goto loop_27;
            case 0x-1:                              /* switch 1 */
                if (evs_gamemode == ENUM_EVS_GAMEMODE_3) {
                    if ((u32) evs_game_time >= 0x2A30U) {
                        func_80062A08(var_s1_3);
                        var_s0_2->unk_0->unk_00C = 0x1C;
                        var_s0_2->unk_0->unk_014 = 0x15;
                        var_s0_2->unk_0->unk_020 = (u32) 0x15;
                    } else {
                        func_80062A40(var_s1_3);
                        var_s0_2->unk_0->unk_00C = 0x1E;
                        var_s0_2->unk_0->unk_014 = 0x17;
                        var_s0_2->unk_0->unk_020 = (u32) 0x17;
                    }
                    temp_v1_3 = var_s0_2->unk_0;
                    func_80062DD8(temp_s7 + var_s2, temp_v1_3->unk_16C, 0, 0, temp_v1_3->unk_174, var_s0_2->unk_0->unk_170, var_s0_2->unk_0->unk_000);
                    _dm_seq_play_in_game(1, 0x12);
                } else {
                    sp44 += 1;
                    var_s0_2->unk_0->unk_020 = 8;
                }
                var_s0_2->unk_0->unk_028[3] = 1;
                var_s0_2->unk_0->unk_040[0] = 0x10;
                var_s0_2->unk_0->unk_048[0] = 1;
                goto block_43;
            default:                                /* switch 1 */
                var_v0 = -2;
                if (temp_v1 != 0x64) {
                    if (temp_v1 != -2) {
                        goto block_43;
                    }
                    /* Duplicate return node #107. Try simplifying control flow for better match */
                    return var_v0;
                }
                return -1;
            case 0x2:                               /* switch 1 */
                return 2;
            case 0x9:                               /* switch 1 */
                return 9;
        }
    } else {
        var_v0 = 0;
        if (temp_s7->unk_3AC < 0) {
            var_s1_12 = 0;
            var_v1_2 = &sp20;
loop_12:
            if ((*var_v1_2)->unk_00C == 2) {
                var_s1_12 += 1;
                var_v1_2 += 4;
                if (var_s1_12 < 2) {
                    goto loop_12;
                }
            }
            var_v0 = 0;
            if (var_s1_12 == 2) {
                temp_s7->unk_3C4 = 1;
                var_s1_13 = 0;
                var_s0_11 = &sp20;
                do {
                    (*var_s0_11)->unk_00C = 4;
                    temp_a0_9 = *var_s0_11;
                    temp_v0_3 = temp_a0_9->unk_04C;
                    if (temp_v0_3 != 1) {
                        if (!((temp_v0_3 != 1) & (var_s1_13 == 0))) {
                            var_s1_13 += 1;
                        } else if (aiDebugP1 < 0) {
                            var_s1_13 += 1;
                        } else {
                            goto block_23;
                        }
                    } else {
block_23:
                        var_s1_13 += 1;
                        aifMakeFlagSet(temp_a0_9);
                    }
                    var_s0_11 += 4;
                } while (var_s1_13 < 2);
                func_800633FC();
                return 0;
            }
            /* Duplicate return node #107. Try simplifying control flow for better match */
            return var_v0;
        }
        return var_v0;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/03CD50", dm_game_main_2p);
#endif

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

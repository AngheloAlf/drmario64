#include "ultra64.h"
#include "include_asm.h"
#include "macros_defines.h"
#include "unknown_structs.h"
#include "main_segment_functions.h"
#include "main_segment_variables.h"
#include "audio/audio_stuff.h"

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/03A790", D_800B1EC0);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/03A790", D_800B1ECC);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/03A790", set_bottom_up_virus);

bool bottom_up_bottle_items(struct_800EBEF0 *arg0) {
    s32 i;
    bool var_s4 = false;
    s32 var_s2;
    struct_800EBEF0_unk_000 *var_a3;
    struct_800EBEF0_unk_000 *var_s0;
    s32 var;

    for (i = 0; i < 8; i++) {
        if (arg0->unk_000[i].unk_4 != 0) {
            var_s4 = true;
        }
    }

    var = 0x80;
    for (i = 0, var_a3 = &arg0->unk_000[8]; i < var; i++, var_a3++) {
        arg0->unk_000[i] = *var_a3;
        arg0->unk_000[i].unk_1--;
    }

    var += 8;
    for (var_s2 = 0, var_s0 = arg0->unk_000; i < var; i++, var_s2++) {
        bzero(&var_s0[i], sizeof(struct_800EBEF0_unk_000));
        var_s0[i].unk_0 = var_s2;
        var_s0[i].unk_1 = 0x11;
    }

    return var_s4;
}

#ifdef NON_EQUIVALENT
extern s32 D_800B1ECC[];
extern f32 RO_800B1C98[];

void add_taiQ_bonus_wait(struct_80123700 *arg0) {
    s32 var_a0;
    s32 i;
    struct_800F3E50 *ptr = watchGame;
    s32 *ptr2;

    if (evs_gamemode != 2) {
        return;
    }

    if (arg0->unk_03A < 2) {
        return;
    }

    ptr->unk_3C8 += (arg0->unk_03A - 1) * 0.25;
    ptr->unk_3C8 = MIN(ptr->unk_3C8, RO_800B1C98[arg0->unk_16C]);

    ptr2 = D_800B1ECC;
    var_a0 = ptr2[0] * (arg0->unk_037 + arg0->unk_03A);

    for (i = 1; i < arg0->unk_039; i++) {
        s32 *var_v0_2;

        if (i < 5U) {
            var_v0_2 = &ptr2[i];
        } else {
            var_v0_2 = &ptr2[5];
        }

        var_a0 += *var_v0_2;
    }

    ptr->unk_410 += var_a0;
}
#else
INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/03A790", add_taiQ_bonus_wait);
#endif

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/03A790", countLeadingZeros);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/03A790", func_800648C0);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/03A790", func_80064940);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/03A790", func_8006498C);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/03A790", func_800649CC);

void func_80064E4C(struct_80123700 *arg0) {
    struct_800F3E50 *ptr = watchGame;
    u16 btn = gControllerPressedButtons[main_joy[arg0->unk_04B]];

    if (ptr->unk_9C4 >= 0) {
        return;
    }

    switch (arg0->unk_020) {
        case 0x1:
        case 0xD:
            break;

        case 0x8:
            if (ptr->unk_000 == 0) {
                return;
            }

            if (arg0->unk_014 != 0x11) {
                return;
            }
            break;

        default:
            return;
    }

    if ((arg0->unk_014 != 2) && (arg0->unk_04C == 0)) {
        if (ptr->unk_000 == 0) {
            if (btn & START_BUTTON) {
                ptr->unk_9C0 = 1;
                ptr->unk_9C4 = arg0->unk_04B;
            }
        } else if (btn & (A_BUTTON | B_BUTTON | L_TRIG | R_TRIG | Z_TRIG | START_BUTTON | U_JPAD | L_JPAD | R_JPAD |
                          D_JPAD | U_CBUTTONS | L_CBUTTONS | R_CBUTTONS | D_CBUTTONS)) {
            ptr->unk_9C4 = arg0->unk_04B;
        }
    }
}

#if 0
s8 func_8005F13C(struct_800EBEF0 *, s8 *, s8 *, s8 *); /* extern */
UNK_TYPE func_80060270(struct_80123700 *, s32);            /* extern */
UNK_TYPE func_80060348(struct_80123700 *, s32);            /* extern */
UNK_TYPE func_80060424(struct_80123700 *, struct_800EBEF0 *); /* extern */
UNK_TYPE func_80060FA0(s8 *, s32, s32, u32);               /* extern */
UNK_TYPE func_80060FCC(struct_80123700 *);                 /* extern */
UNK_TYPE func_800610E0(struct_80123700 *);                 /* extern */
s32 func_80061184(struct_80123700 *, struct_800EBEF0 *); /* extern */
s32 func_80062AFC(s32);                             /* extern */
s32 func_80062B18(s32);                             /* extern */
s32 func_80062BC4(s8 *);                            /* extern */
UNK_TYPE func_80062BD4(s8 *, UNK_TYPE);                           /* extern */
UNK_TYPE func_80062DA4(s8 *);                              /* extern */
UNK_TYPE func_80062EC0(s8 *);                              /* extern */
UNK_TYPE func_80063378();                                  /* extern */
UNK_TYPE func_800633C0();                                  /* extern */
UNK_TYPE func_800635BC(struct_80123700 *, struct_800EBEF0 *); /* extern */
UNK_TYPE func_80064E4C();                                  /* extern */
UNK_TYPE func_8007E760(s8 *, s32, s32, u8, s32, s32, UNK_TYPE *); /* extern */
UNK_TYPE go_down(struct_80123700 *, struct_800EBEF0 *, UNK_TYPE); /* extern */
s32 retryMenu_input(s32);                           /* extern */
UNK_TYPE scoreNums_set(s8 *, s32, u8, s32, s32);           /* extern */
UNK_TYPE set_bottom_up_virus(struct_80123700 *, struct_800EBEF0 *); /* extern */
extern UNK_TYPE B_800EF448;
extern UNK_TYPE D_8008841C;
extern s8 D_800A6FD8;
extern UNK_TYPE D_800A7360;
extern UNK_TYPE RO_800ACA10;
extern UNK_TYPE RO_800B1C8C;

s32 dm_game_main_cnt_1P(struct_80123700 *arg0, struct_800EBEF0 *arg1, s32 arg2) {
    s32 sp20;
    UNK_TYPE *var_t0;
    f32 temp_f4;
    f32 var_f0;
    f64 temp_f2;
    s32 temp_s0_2;
    s32 temp_s0_3;
    s32 temp_v0;
    s32 temp_v0_4;
    s32 temp_v0_5;
    s32 temp_v0_6;
    s32 temp_v0_7;
    s32 temp_v0_8;
    s32 temp_v0_9;
    s32 temp_v1;
    s32 temp_v1_10;
    s32 temp_v1_4;
    s32 temp_v1_6;
    s32 temp_v1_9;
    s32 var_a0;
    s32 var_a0_2;
    s32 var_a0_3;
    s32 var_s0;
    s32 var_s0_2;
    s32 var_s0_3;
    s32 var_s0_4;
    s32 var_s0_5;
    s32 var_s0_6;
    s32 var_s2;
    s32 var_s2_2;
    s32 var_s4;
    s32 var_s4_2;
    s32 var_s4_3;
    s32 var_s5;
    s32 var_s7;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v0_3;
    s8 *temp_s1;
    s8 temp_v0_2;
    s8 temp_v0_3;
    struct_800F3E50 *temp_s3;
    struct_800F3E50 *var_s1_2;
    struct_800F3E50 *var_s1_3;
    struct_800F3E50 *var_s1_4;
    struct_800F3E50 *var_s6;
    u16 temp_v1_11;
    u16 temp_v1_12;
    u8 *temp_a2;
    u8 temp_a0;
    u8 temp_a2_2;
    u8 temp_s0;
    u8 temp_v1_2;
    u8 temp_v1_3;
    u8 temp_v1_5;
    u8 temp_v1_7;
    u8 temp_v1_8;
    u8 var_s1;
    void *temp_s0_4;
    void *var_v1;

    //var_s1 = saved_reg_s1;
    //var_s4 = saved_reg_s4;
    temp_s3 = watchGame;
    func_80064E4C();
    animeState_update(&arg0->unk_094);
    func_80062EC0(&temp_s3->unk_000[(arg2 * 0xA4) + 0xB8]);
    if ((evs_gamemode != 3) || ((u32) evs_game_time < 0x2A30U) || (var_v0 = -1, (arg0->unk_020 != 1))) {
        temp_v0 = arg0->unk_00C;
        switch (temp_v0) {
            case 0x1:
                dm_set_virus(arg0, arg1, &virus_map_data[arg2], &virus_map_disp_order[arg2]);
                /* fallthrough */
            case 0x2:
                return 3;
            case 0x3:
                temp_v0_2 = (u8) arg0->unk_02D[2] + 1;
                arg0->unk_02D[2] = temp_v0_2;
                var_v0 = 0;
                if ((temp_v0_2 & 0xFF) == *(&D_8008841C + (u8) arg0->unk_02C)) {
                    temp_a2 = &B_800EF448 + (u8) arg0->unk_030[3];
                    temp_a2_2 = *temp_a2;
                    func_80060FA0(&arg0->unk_178, ((temp_a2_2 >> 4) - ((*temp_a2 / 48) * 3)) & 0xFF, (*temp_a2 % 3) & 0xFF, MULTU_HI(temp_a2_2, 0xAAAAAAAB));
                    arg0->unk_00C = 4;
                    arg0->unk_02D[2] = 0x1E;
                    func_800635BC(arg0, arg1);
                    return 0;
                }
                /* Duplicate return node #174. Try simplifying control flow for better match */
                return var_v0;
            case 0x5:
                var_s0 = 0;
                if (func_80061184(arg0, arg1) != 0) {
                    var_s2 = 0x44C;
                    var_s1_2 = temp_s3;
                    do {
                        if (var_s1_2->animeStates[0].animeSeq.unk_10 != 4) {
                            animeState_set(&temp_s3->animeStates[var_s0], 3);
                        }
                        var_s2 += 0x40;
                        var_s0 += 1;
                        var_s1_2 += 0x40;
                    } while (var_s0 < 3);
                    if (evs_gamemode == 2) {
                        temp_s3->unk_410 = 0;
block_84:
                        return -1;
                    }
                    return -1;
                }
                if ((dm_h_erase_chack(arg1) != 0) || (dm_w_erase_chack(arg1) != 0)) {
                    arg0->unk_00C = 6;
                    arg0->unk_02D[2] = 0;
                } else {
                    arg0->unk_00C = 9;
                }
            default:
block_173:
                var_v0 = 0;
                /* Duplicate return node #174. Try simplifying control flow for better match */
                return var_v0;
            case 0x6:
                temp_v0_3 = (u8) arg0->unk_02D[2] + 1;
                arg0->unk_02D[2] = temp_v0_3;
                var_v0 = 0;
                if ((u32) (temp_v0_3 & 0xFF) >= 0x12U) {
                    arg0->unk_02D[2] = 0;
                    arg0->unk_00C = 7;
                    dm_h_erase_chack_set(arg0, arg1);
                    dm_w_erase_chack_set(arg0, arg1);
                    dm_h_ball_chack(arg1);
                    dm_w_ball_chack(arg1);
                    temp_s0 = (u8) arg0->unk_024[1];
                    var_s4_2 = 0x44C;
                    var_s7 = 0x50C;
                    var_s1_3 = temp_s3;
                    temp_s0_2 = temp_s0 - func_8005F13C(arg1, &temp_s3->unk_3C8[0x50], &temp_s3->unk_3C8[0x51], &temp_s3->unk_3C8[0x52]);
                    var_s0_2 = 0;
                    arg0->unk_024[1] = (u8) arg0->unk_024[1] - temp_s0_2;
                    arg0->unk_170 = (s32) (arg0->unk_170 + temp_s0_2);
                    do {
                        if (temp_s3->unk_000[var_s0_2].unk_418 == 0) {
                            if (var_s1_3->unk_400 != 0) {
                                var_s4_2 += 0x40;
                            } else {
                                var_s1_3->unk_400 = 1;
                                animeState_set((AnimeState *) &temp_s3->unk_000[var_s4_2], 4);
                                animeSmog_start((AnimeSmog *) &temp_s3->unk_000[var_s7]);
                                if ((u8) arg0->unk_024[1] == 0) {
                                    var_s4_2 += 0x40;
                                } else {
                                    dm_snd_play_in_game(0x4A);
                                    var_a0 = 0x39;
                                    goto block_39;
                                }
                            }
                        } else if (!((u8) arg0->unk_038[7] & (0x10 << var_s0_2))) {
                            var_s4_2 += 0x40;
                        } else if (temp_s3->unk_410 != 0) {
                            var_s4_2 += 0x40;
                        } else {
                            animeState_set((AnimeState *) &temp_s3->unk_000[var_s4_2], 2);
                            var_a0 = 0x4A;
block_39:
                            var_s4_2 += 0x40;
                            dm_snd_play_in_game(var_a0);
                        }
                        var_s7 += 0x124;
                        var_s0_2 += 1;
                        var_s1_3 += 4;
                    } while (var_s0_2 < 3);
                    arg0->unk_038[7] = (u8) arg0->unk_038[7] & 0xF;
                    dm_calc_erase_score_pos(arg0, arg1, &sp20);
                    temp_v1 = (s8) (u8) arg0->unk_008[2] / 2;
                    scoreNums_set(&temp_s3->unk_000[(arg2 * 0xA4) + 0xB8], dm_make_score(arg0), (u8) arg0->unk_037[0], arg0->unk_006 + temp_v1 + sp20, arg0->unk_008 + temp_v1 + sp24);
                    if ((u8) arg0->unk_024[1] == 0) {
                        if (evs_gamemode != 2) {
                            temp_a0 = (u8) arg0->unk_038[2];
                            arg0->unk_14 = 3;
                            arg0->unk_00C = 0xA;
                            if ((u8) arg0->unk_038[3] < temp_a0) {
                                arg0->unk_038[3] = (s8) temp_a0;
                            }
                            return 6;
                        }
                        goto block_47;
                    }
block_47:
                    if (((u8) arg0->unk_024[1] < 4U) && (evs_gamemode != 2)) {
                        if (temp_s3->unk_3C0 == 0) {
                            temp_s3->unk_3C0 = 1;
                            dm_snd_play_in_game(0x50);
                        }
                        if (temp_s3->unk_3B4 == 0) {
                            temp_s3->unk_3B4 = 1;
                            temp_s3->unk_3B8 = 1;
                        }
                    }
                    arg0->unk_038[1] = (u8) arg0->unk_038[1] + 1;
                    if ((u8) arg0->unk_038[2] < 2U) {
                        temp_v1_2 = (u8) arg0->unk_038[7];
                        if (temp_v1_2 & 8) {
                            arg0->unk_038[7] = temp_v1_2 & 0xF7;
                            dm_snd_play_in_game(0x38);
                            return 0;
                        }
                        dm_snd_play_in_game(0x3D);
                        return 0;
                    }
                    temp_v1_3 = (u8) arg0->unk_038[7];
                    if (temp_v1_3 & 8) {
                        arg0->unk_038[7] = temp_v1_3 & 0xF7;
                    }
                    temp_v1_4 = (u8) arg0->unk_038[2] - 2;
                    var_s0_3 = 2;
                    if (temp_v1_4 < 3) {
                        var_s0_3 = temp_v1_4;
                    }
                    dm_snd_play_in_game(*(&RO_800ACA10 + arg0->unk_090) + var_s0_3);
                    return 0;
                }
                /* Duplicate return node #174. Try simplifying control flow for better match */
                return var_v0;
            case 0x7:
                func_80061490(arg0, arg1);
                return 0;
            case 0x8:
                go_down(arg0, arg1, 0xE);
                return 0;
            case 0x9:
                add_taiQ_bonus_wait(arg0);
                if ((temp_s3->unk_9BC != 0) && (temp_s3->unk_410 == 0)) {
                    arg0->unk_168 = 0;
                    arg0->unk_00C = 0xC;
                    set_bottom_up_virus(arg0, arg1);
                    dm_snd_play_in_game(0x65);
                    return 0;
                }
                temp_v1_5 = (u8) arg0->unk_038[1];
                if (temp_v1_5 >= 2U) {
                    temp_v1_6 = (arg0->unk_174 + temp_v1_5) - 1;
                    var_a0_2 = 0x63;
                    if (temp_v1_6 < 0x64) {
                        var_a0_2 = temp_v1_6;
                    }
                    arg0->unk_174 = var_a0_2;
                }
                func_80060424(arg0, arg1);
                func_80060FCC(arg0);
                func_800610E0(arg0);
                func_80060348(arg0, arg2);
                animeState_set(&arg0->unk_094, 1);
                temp_v1_7 = arg0->unk_04C;
                if ((temp_v1_7 == 1) || (((temp_v1_7 != 1) & (arg2 == 0)) && (aiDebugP1 >= 0))) {
                    aifMakeFlagSet(arg0);
                }
                temp_v1_8 = (u8) arg0->unk_038[2];
                if ((u8) arg0->unk_038[3] < temp_v1_8) {
                    arg0->unk_038[3] = (s8) temp_v1_8;
                }
                var_s0_4 = 3;
                var_v1 = arg0 + 3;
                arg0->unk_00C = 3;
                arg0->unk_02D[2] = 0;
                arg0->unk_030[1] = 0;
                arg0->unk_038[2] = 0;
                arg0->unk_038[1] = 0;
                arg0->unk_037[0] = 0;
                arg0->unk_038[0] = 0;
                do {
                    var_v1->unk_3C = 0;
                    var_s0_4 -= 1;
                    var_v1 -= 1;
                } while (var_s0_4 >= 0);
                return 0;
            case 0xC:
                temp_v0_4 = arg0->unk_168 + 1;
                arg0->unk_168 = temp_v0_4;
                var_v0 = 0;
                if (temp_v0_4 >= arg0->unk_008[2]) {
                    arg0->unk_168 = 0;
                    temp_s3->unk_9BC = 0;
                    temp_f4 = *(&RO_800B1C8C + (arg0->unk_16C * 4));
                    temp_f2 = (f64) temp_s3->unk_3C8 - 0.5;
                    var_f0 = temp_f4;
                    if (!(temp_f2 < (f64) temp_f4)) {
                        var_f0 = (f32) temp_f2;
                    }
                    temp_s3->unk_3C8 = var_f0;
                    arg0->unk_00C = 8;
                    if (bottom_up_bottle_items(arg1) != 0) {
                        goto block_84;
                    }
                    arg0->unk_024[1] = func_8005F13C(arg1, &temp_s3->unk_3C8[0x50], &temp_s3->unk_3C8[0x51], &temp_s3->unk_3C8[0x52]);
                    var_s0_5 = 0;
                    var_s6 = temp_s3;
                    var_s5 = 0;
                    var_s4_3 = 0x50C;
                    var_s2_2 = 0x44C;
                    var_s1_4 = temp_s3;
                    do {
                        if ((temp_s3->unk_000[var_s0_5].unk_418 != 0) && (var_s1_4->unk_400 != 0)) {
                            animeState_set((AnimeState *) &temp_s3->unk_000[var_s2_2], 0);
                            animeSmog_start((AnimeSmog *) &temp_s3->unk_000[var_s4_3]);
                            var_s1_4->unk_400 = 0;
                        } else if (var_s6->animeStates[0].animeSeq.unk_10 == 3) {
                            animeState_set((AnimeState *) &temp_s3->unk_000[var_s5 + 0x44C], 0);
                        }
                        var_s6 += 0x40;
                        var_s5 += 0x40;
                        var_s4_3 += 0x124;
                        var_s2_2 += 0x40;
                        var_s0_5 += 1;
                        var_s1_4 += 4;
                    } while (var_s0_5 < 3);
                    return 0;
                }
                /* Duplicate return node #174. Try simplifying control flow for better match */
                return var_v0;
            case 0x1A:
            case 0x1C:
                if (arg0->unk_00C == 0x1A) {
                    var_v0_2 = func_80062B18(arg2);
                } else {
                    var_v0_2 = func_80062AFC(arg2);
                }
                var_v0 = 0;
                if (var_v0_2 == 0) {
                    if (gControllerPressedButtons[main_joy[arg2]] & 0xFF3F) {
                        temp_v1_9 = arg0->unk_00C;
                        switch (temp_v1_9) {        /* switch 1; irregular */
                            case 0x1A:              /* switch 1 */
                                arg0->unk_14 = 0x14;
                                arg0->unk_00C = 0x1B;
                                goto block_173;
                            case 0x1C:              /* switch 1 */
                                arg0->unk_14 = 0x16;
                                arg0->unk_00C = 0x1D;
                                goto block_173;
                            default:                /* switch 1 */
                                return 0;
                        }
                    } else {
                        goto block_173;
                    }
                } else {
                    /* Duplicate return node #174. Try simplifying control flow for better match */
                    return var_v0;
                }
                break;
            case 0x1B:
            case 0x1D:
                var_s0_6 = arg2 * 2;
                if (gControllerPressedButtons[main_joy[arg2]] & 0xFF3F) {
                    func_80062DA4(&temp_s3->unk_000[(arg2 * 0x2C) + 0x9D0]);
                    var_s0_6 = arg2 * 2;
                }
                temp_s0_3 = (((var_s0_6 + arg2) * 4) - arg2) * 4;
                temp_s1 = &temp_s3->unk_000[temp_s0_3 + 0x9D0];
                func_80062BD4(temp_s1, 1);
                temp_s0_4 = temp_s3 + temp_s0_3;
                func_80060270(arg0, temp_s0_4->unk_9F4);
                temp_s0_4->unk_9F4 = 0;
                if (func_80062BC4(temp_s1) != 0) {
                    temp_v1_10 = arg0->unk_00C;
                    switch (temp_v1_10) {           /* switch 2; irregular */
                        case 0x1B:                  /* switch 2 */
                            arg0->unk_14 = 3;
                            arg0->unk_00C = 0xA;
                            goto block_173;
                        case 0x1D:                  /* switch 2 */
                            arg0->unk_14 = 4;
                            arg0->unk_00C = 0xB;
                            goto block_173;
                        default:                    /* switch 2 */
                            return 0;
                    }
                } else {
                    goto block_173;
                }
                break;
            case 0xA:
            case 0xB:
                if (arg0->unk_00C == 0xA) {
                    var_v0_3 = func_80062B18(arg2);
                } else {
                    var_v0_3 = func_80062AFC(arg2);
                }
                var_v0 = 0;
                if (var_v0_3 == 0) {
                    if ((temp_s3->unk_AA8 < 0) && ((gControllerHoldButtons[*main_joy] & 0x2230) == 0x2230)) {
                        switch (evs_gamemode) {     /* switch 4; irregular */
                            case 0x3:               /* switch 4 */
                                var_s4 = 1;
block_129:
                                var_s1 = (u8) arg0->unk_16C;
                                break;
                            case 0x0:               /* switch 4 */
                                var_s1 = arg0->unk_026;
                                var_s4 = 0;
                                break;
                            case 0x2:               /* switch 4 */
                                var_s4 = 2;
                                goto block_129;
                        }
                        if ((u8) *B_800FAE78 == 8) {
                            var_t0 = &D_800A7360;
                        } else {
                            var_t0 = ((u8) *B_800FAE78 * 0xD0) + &evs_mem_data->unk_00[1];
                        }
                        if ((u8) temp_s3->unk_9B4[0xF8] == 0) {
                            func_8007E760(&temp_s3->unk_9B4[0xF8], var_s4 & 0xFF, var_s1 & 0xFF, (u8) arg0->unk_02C, arg0->unk_000 / 10, (evs_game_time / 6) & 0xFFFF, var_t0);
                            temp_s3->unk_9B4[0x120] = 0x7E;
                            temp_s3->unk_9B4[0x121] = 0x7A;
                        }
                        msgWnd_clear((MessageWnd *) &temp_s3->unk_9B4[0x74]);
                        msgWnd_addStr((MessageWnd *) &temp_s3->unk_9B4[0x74], &D_800A6FD8);
                        msgWnd_addStr((MessageWnd *) &temp_s3->unk_9B4[0x74], &temp_s3->unk_9B4[0xF8]);
                        msgWnd_skip((MessageWnd *) &temp_s3->unk_9B4[0x74]);
                        temp_s3->unk_AA8 = (s32) -temp_s3->unk_AA8;
                        goto block_173;
                    }
                    if (gControllerPressedButtons[*main_joy] != 0) {
                        temp_v0_5 = temp_s3->unk_AA8;
                        if (temp_v0_5 > 0) {
                            temp_s3->unk_AA8 = (s32) -temp_v0_5;
                        }
                    }
                    temp_v0_6 = retryMenu_input(arg2);
                    if (temp_v0_6 != 1) {
                        if (temp_v0_6 >= 2) {
                            switch (temp_v0_6) {    /* switch 3; irregular */
                                case 0x2:           /* switch 3 */
                                    func_800633C0();
                                    temp_v1_11 = (u16) arg0->unk_004;
                                    if (temp_v1_11 < 0x3E7U) {
                                        arg0->unk_004 = temp_v1_11 + 1;
                                    }
                                    var_a0_3 = 0x3E;
                                    if ((u8) arg0->unk_026 >= 0x16U) {
                                        temp_v0_7 = temp_s3->unk_378;
                                        if (temp_v0_7 > 0) {
                                            temp_s3->unk_378 = (s32) (temp_v0_7 - 1);
                                            var_a0_3 = 0x4E;
                                        }
                                    }
block_171:
                                    dm_snd_play_in_game(var_a0_3);
                                    return 2;
                                case 0x3:           /* switch 3 */
block_172:
                                    dm_snd_play_in_game(0x3E);
                                    return 0x64;
                                default:            /* switch 3 */
                                    return 0;
                            }
                        } else {
                            if (temp_v0_6 != 0) {
                                return 0;
                            }
                            func_80063378();
                            dm_snd_play_in_game(0x3E);
                            return 9;
                        }
                    } else {
                        func_800633C0();
                        dm_snd_play_in_game(0x3E);
                        return 1;
                    }
                } else {
                    /* Duplicate return node #174. Try simplifying control flow for better match */
                    return var_v0;
                }
                break;
            case 0x18:
                temp_v0_8 = retryMenu_input(arg2);
                if (temp_v0_8 != 1) {
                    if (temp_v0_8 >= 2) {
                        if (temp_v0_8 != 2) {
                            return 0;
                        }
                        goto block_172;
                    }
                    if (temp_v0_8 != 0) {
                        return 0;
                    }
                    if (temp_s3->unk_9C4 < 0) {
                        temp_s3->unk_9C4 = arg2;
                    }
                    dm_snd_play_in_game(0x3E);
                    return 0;
                }
                temp_v1_12 = (u16) arg0->unk_004;
                if (temp_v1_12 < 0x3E7U) {
                    arg0->unk_004 = temp_v1_12 + 1;
                }
                var_a0_3 = 0x3E;
                if ((u8) arg0->unk_026 >= 0x16U) {
                    temp_v0_9 = temp_s3->unk_378;
                    if (temp_v0_9 > 0) {
                        temp_s3->unk_378 = (s32) (temp_v0_9 - 1);
                        var_a0_3 = 0x4E;
                    }
                }
                goto block_171;
        }
    } else {
        return var_v0;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/03A790", dm_game_main_cnt_1P);
#endif

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/03A790", func_80065BC4);

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/03A790", RO_800B2020);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/03A790", D_800B202C);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/03A790", func_800666FC);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/03A790", func_80066808);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/03A790", func_8006683C);

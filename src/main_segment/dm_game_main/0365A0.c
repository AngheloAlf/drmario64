/**
 * Some functions are part of dm_game_main.c, not sure if all of them
 */

#include "ultra64.h"
#include "include_asm.h"
#include "macros_defines.h"
#include "unknown_structs.h"
#include "main_segment_functions.h"
#include "main_segment_variables.h"
#include "boot_functions.h"
#include "boot_variables.h"
#include "audio/audio_stuff.h"

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/0365A0", func_800601F0);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/0365A0", func_80060270);

UNK_TYPE dm_make_score(struct_80123700 *arg0, s32 arg1) {
    UNK_TYPE temp_v0;
    s32 temp = arg1;

    if (evs_story_flg != 0) {
        if (evs_story_level < 3) {
            temp = evs_story_level;
        } else {
            temp = 2;
        }
    } else {
        switch (evs_gamesel) {
            case ENUM_EVS_GAMESEL_0:
                temp = arg0->unk_02C;
                break;

            case ENUM_EVS_GAMESEL_1:
                temp = arg0->unk_02C;
                break;

            case ENUM_EVS_GAMESEL_2:
                temp = arg0->unk_02C;
                break;

            case ENUM_EVS_GAMESEL_3:
                temp = arg0->unk_02C;
                break;

            case ENUM_EVS_GAMESEL_4:
                temp = arg0->unk_02C;
                break;

            case ENUM_EVS_GAMESEL_5:
                temp = arg0->unk_02C;
                break;

            case ENUM_EVS_GAMESEL_6:
                temp = arg0->unk_02C;
                break;
        }
    }

    temp_v0 = func_800601F0(arg0, temp);
    func_80060270(arg0, temp_v0);
    return temp_v0;
}

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/0365A0", D_800B1C4C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/0365A0", D_800B1C5C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/0365A0", D_800B1C74);

const u8 _retryMenu_itemCount[] = {
    2, 3, 2, 3, 2, 3,
};

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/0365A0", RO_800B1C80);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/0365A0", RO_800B1C8C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/0365A0", RO_800B1C98);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/0365A0", RO_800B1CA4);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/0365A0", STR_800B1CB8);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/0365A0", STR_800B1CE0);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/0365A0", D_800B1D08);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/0365A0", D_800B1D18);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/0365A0", D_800B1D1C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/0365A0", D_800B1D28);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/0365A0", D_800B1D2C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/0365A0", D_800B1D30);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/0365A0", D_800B1D5C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/0365A0", D_800B1D60);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/0365A0", D_800B1D7C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/0365A0", D_800B1D80);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/0365A0", D_800B1D84);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/0365A0", D_800B1D88);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/0365A0", D_800B1D8C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/0365A0", D_800B1DBC);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/0365A0", D_800B1E7C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/0365A0", RO_800B1E80);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/0365A0", D_800B1E8C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/0365A0", D_800B1E90);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/0365A0", RO_800B1E9C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/0365A0", RO_800B1EA0);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/0365A0", func_80060348);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/0365A0", func_80060424);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/0365A0", set_down_flg);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/0365A0", go_down);

void erase_anime(struct_800EBEF0 *arg0) {
    s32 i;

    for (i = 0; i < 0x10 * 8; i++) {
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

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/0365A0", func_800609B8);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/0365A0", func_80060A6C);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/0365A0", func_80060C1C);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/0365A0", func_80060E10);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/0365A0", func_80060F60);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/0365A0", func_80060FA0);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/0365A0", func_80060FCC);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/0365A0", func_800610E0);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/0365A0", func_80061184);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/0365A0", update_flash_virus_count);

u8 func_8006121C(struct_80123700 *arg0, struct_800EBEF0 *arg1, UNK_TYPE arg2) {
    if (evs_gamemode == ENUM_EVS_GAMEMODE_1) {
        arg0->unk_025 = update_flash_virus_count(arg0, arg1, arg2);
    } else {
        arg0->unk_025 = get_virus_count(arg1);
    }
    return arg0->unk_025;
}

#ifdef NON_EQUIVALENT
void dm_set_virus(struct_80123700 *arg0, struct_800EBEF0 *arg1, struct_virus_map_data *arg2,
                  struct_virus_map_disp_order *arg3) {
    s32 temp_v0;

    if (arg0->unk_014 != 2) {
        return;
    }

    temp_v0 = dm_get_first_virus_count(evs_gamemode, arg0);

    if (arg0->unk_024 < temp_v0) {
        while (arg0->unk_024 < temp_v0) {
            if (!(arg3->unk_00[arg0->unk_024] & 0x80)) {
                break;
            }

            arg0->unk_024++;
        }

        if (arg0->unk_024 < temp_v0) {
            u8 temp_a1;
            temp_a1 = arg3->unk_00[arg0->unk_024];
            arg3->unk_00[arg0->unk_024] = temp_a1 | 0x80;

            set_virus(arg1, arg2->unk_000[temp_a1].unk_1, arg2->unk_000[temp_a1].unk_2, arg2->unk_000[temp_a1].unk_0,
                      virus_anime_table[(arg2->unk_000[temp_a1].unk_0 * 4) + arg0->unk_027]);
            if (arg0->unk_01C == 0x12) {
                arg1->unk_000[temp_a1].unk_3 += 3;
            }
        }
    }

    if (arg0->unk_024 >= temp_v0) {
        arg0->unk_014 = 1;
        arg0->unk_00C = 2;
    }

    func_8006121C(arg0, arg1, 0);
}
#else
INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/0365A0", dm_set_virus);
#endif

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/0365A0", func_800613D0);

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

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/0365A0", dm_make_erase_h_line);

bool dm_h_erase_chack(struct_800EBEF0 *arg0) {
    s32 i;

    for (i = 0; i < 8; i++) {
        s32 j;
        s32 val = 0xF;
        s32 var_a1 = 0;
        s32 var_a3 = -1;
        struct_800EBEF0_unk_000 *temp_v1 = arg0->unk_000;

        for (j = 0; j < 0x10; j++) {
            if (temp_v1[i + j * 8].unk_4 != 0) {
                if (temp_v1[i + j * 8].unk_7 != var_a3) {
                    if (var_a1 < 3) {
                        if (j >= 0xD) {
                            break;
                        }
                        var_a3 = temp_v1[i + j * 8].unk_7;
                        var_a1 = 0;
                    } else {
                        return true;
                    }
                } else {
                    var_a1++;
                    if (j == val) {
                        if (var_a1 >= 3) {
                            return true;
                        }
                    }
                }
            } else if (var_a1 >= 3) {
                return true;
            } else if (j < 0xD) {
                var_a1 = 0;
                var_a3 = -1;
            } else {
                break;
            }
        }
    }

    return false;
}

void dm_h_erase_chack_set(struct_80123700 *arg0, struct_800EBEF0 *arg1) {
    s32 i;

    for (i = 0; i < 8; i++) {
        s32 var_s1 = 0;
        s32 var_s5 = -1;
        s32 var_s2 = -1;
        s32 var_fp = 0;
        s32 j;

        for (j = 0; j < 0x10; j++) {
            struct_800EBEF0_unk_000 *temp_v1 = arg1->unk_000;

            if (temp_v1[i + j * 8].unk_4 != 0) {
                if (temp_v1[i + j * 8].unk_7 != var_s2) {
                    if (var_s1 >= 3) {
                        dm_make_erase_h_line(arg0, arg1, var_s5, var_s1, i);
                        if (arg0->unk_039 == 0) {
                            arg0->unk_03F |= (1 << var_s2);
                        }
                        arg0->unk_03C[var_s2]++;
                        arg0->unk_03A++;
                    }

                    if (j < 0xD) {
                        temp_v1 = arg1->unk_000;

                        var_s5 = j;
                        var_s2 = temp_v1[i + j * 8].unk_7;
                        var_s1 = 0;
                    } else {
                        var_fp = 1;
                    }
                } else {
                    var_s1++;
                    if (j == 0xF) {
                        if (var_s1 >= 3) {
                            dm_make_erase_h_line(arg0, arg1, var_s5, var_s1, i);
                            if (arg0->unk_039 == 0) {
                                arg0->unk_03F |= (1 << var_s2);
                            }
                            arg0->unk_03C[var_s2]++;
                            arg0->unk_03A++;
                        }
                    }
                }
            } else {
                if (var_s1 >= 3) {
                    dm_make_erase_h_line(arg0, arg1, var_s5, var_s1, i);
                    if (arg0->unk_039 == 0) {
                        arg0->unk_03F |= (1 << var_s2);
                    }
                    arg0->unk_03C[var_s2]++;
                    arg0->unk_03A++;
                }

                if (j >= 0xD) {
                    var_fp = 1;
                } else {
                    var_s1 = 0;
                    var_s5 = -1;
                    var_s2 = -1;
                }
            }

            if (var_fp != 0) {
                break;
            }
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/0365A0", dm_make_erase_w_line);

bool dm_w_erase_chack(struct_800EBEF0 *arg0) {
    s32 i;

    for (i = 0; i < 0x10; i++) {
        s32 var_a1 = 0;
        s32 var_a3 = -1;
        s32 j;

        for (j = 0; j < 8; j++) {
            struct_800EBEF0_unk_000 *temp_v1 = arg0->unk_000;

            if (temp_v1[i * 8 + j].unk_4 != 0) {
                if (temp_v1[i * 8 + j].unk_7 != var_a3) {
                    if (var_a1 >= 3) {
                        return true;
                    } else if (j < 5) {
                        var_a3 = temp_v1[i * 8 + j].unk_7;
                        var_a1 = 0;
                    } else {
                        break;
                    }
                } else {
                    var_a1 += 1;
                    if (j == 7) {
                        if (var_a1 >= 3) {
                            return true;
                        }
                    }
                }
            } else if (var_a1 >= 3) {
                return true;
            } else if (j < 5) {
                var_a1 = 0;
                var_a3 = -1;
            } else {
                break;
            }
        }
    }
    return false;
}

void dm_w_erase_chack_set(struct_80123700 *arg0, struct_800EBEF0 *arg1) {
    s32 i;

    for (i = 0; i < 0x10; i++) {
        s32 j;
        s32 var_s1 = 0;
        s32 var_s6 = -1;
        s32 var_s3 = -1;
        bool var_fp = false;

        for (j = 0; j < 8; j++) {
            s32 index = i * 8 + j;
            struct_800EBEF0_unk_000 *temp_v1 = arg1->unk_000;

            if (temp_v1[index].unk_4 != 0) {
                if (temp_v1[index].unk_7 != var_s3) {
                    if (var_s1 >= 3) {
                        dm_make_erase_w_line(arg0, arg1, var_s6, var_s1, i);
                        if (arg0->unk_039 == 0) {
                            arg0->unk_03F |= 1 << var_s3;
                        }
                        arg0->unk_03C[var_s3]++;
                        arg0->unk_03A++;
                    }
                    if (j >= 5) {
                        var_fp = true;
                    } else {
                        temp_v1 = arg1->unk_000;

                        var_s6 = j;
                        var_s3 = temp_v1[index].unk_7;
                        var_s1 = 0;
                    }
                } else {
                    var_s1++;
                    if (j == 7) {
                        if (var_s1 >= 3) {
                            dm_make_erase_w_line(arg0, arg1, var_s6, var_s1, i);
                            if (arg0->unk_039 == 0) {
                                arg0->unk_03F |= 1 << var_s3;
                            }
                            arg0->unk_03C[var_s3]++;
                            arg0->unk_03A++;
                        }
                    }
                }
            } else {
                if (var_s1 >= 3) {
                    dm_make_erase_w_line(arg0, arg1, var_s6, var_s1, i);
                    if (arg0->unk_039 == 0) {
                        arg0->unk_03F |= 1 << var_s3;
                    }
                    arg0->unk_03C[var_s3]++;
                    arg0->unk_03A++;
                }

                if (j >= 5) {
                    var_fp = true;
                } else {
                    var_s1 = 0;
                    var_s6 = -1;
                    var_s3 = -1;
                }
            }

            if (var_fp) {
                break;
            }
        }
    }
}

#ifdef NON_MATCHING
void dm_h_ball_chack(struct_800EBEF0 *arg0) {
    u32 i;

    for (i = 0; i < 8; i++) {
        u32 j;

        for (j = 0; j < 0x10; j++) {
            struct_800EBEF0_unk_000 *temp_a1 = arg0->unk_000;

            if (temp_a1[j * 8 + i].unk_4 != 0) {
                if (temp_a1[j * 8 + i].unk_2 == 0) {
                    if (arg0->unk_000[(1 + j) * 8 + i].unk_2 != 1) {
                        temp_a1[j * 8 + i].unk_2 = 4;
                    }
                } else if (temp_a1[j * 8 + i].unk_2 == 1) {
                    if ((temp_a1[j * 8 + i].unk_1 == temp_a1[j * 8 + i].unk_2) ||
                        (arg0->unk_000[(j - 1) * 8 + i].unk_2 != 0)) {
                        temp_a1[j * 8 + i].unk_2 = 4;
                    }
                }
            }
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/0365A0", dm_h_ball_chack);
#endif

void dm_w_ball_chack(struct_800EBEF0 *arg0) {
    u32 i;

    for (i = 0; i < 0x10; i++) {
        u32 j;

        for (j = 0; j < 8; j++) {
            struct_800EBEF0_unk_000 *temp_v1 = arg0->unk_000;

            if (temp_v1[i * 8 + j].unk_4 != 0) {
                if (temp_v1[i * 8 + j].unk_2 == 2) {
                    if (temp_v1[i * 8 + j + 1].unk_2 != 3) {
                        temp_v1[i * 8 + j].unk_2 = 4;
                    }
                } else if ((temp_v1[i * 8 + j].unk_2 == 3) && (temp_v1[i * 8 + j - 1].unk_2 != 2)) {
                    temp_v1[i * 8 + j].unk_2 = 4;
                }
            }
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/0365A0", func_80061DB8);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/0365A0", func_80061E7C);

void dm_calc_erase_score_pos(struct_80123700 *arg0, struct_800EBEF0 *arg1, dm_calc_erase_score_pos_arg2 *arg2) {
    s32 i;
    s32 var_t2 = 0;

    arg2->unk_4 = 0;
    arg2->unk_0 = 0;

    for (i = 0; i < 0x10; i++) {
        s32 j;

        for (j = 0; j < 8; j++) {
            struct_800EBEF0_unk_000 *temp_a3 = &arg1->unk_000[j + i * 8];

            if (temp_a3->unk_6 != 0) {
                arg2->unk_0 += temp_a3->unk_0;
                arg2->unk_4 += temp_a3->unk_1;
                var_t2++;
            }
        }
    }

    if (var_t2 > 0) {
        arg2->unk_0 = arg2->unk_0 * arg0->unk_00A / var_t2;
        arg2->unk_4 = arg2->unk_4 * arg0->unk_00A / var_t2;
    }
}

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/0365A0", func_800620FC);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/0365A0", func_8006258C);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/0365A0", func_800626A4);

UNK_PTR *dm_game_heap_top(void) {
    return &heapTop;
}

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/0365A0", func_800628A4);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/0365A0", func_800628BC);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/0365A0", dm_get_mtx_buf);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/0365A0", dm_get_vtx_buf);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/0365A0", initEtcWork);

void func_80062978(s32 index, s32 arg1) {
    watchGame->unk_888[index] = arg1;
}

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/0365A0", func_80062990);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/0365A0", func_800629AC);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/0365A0", func_800629C8);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/0365A0", func_800629E4);

void func_80062A08(s32 index) {
    func_80062978(index, 0xB4);
}

void func_80062A24(s32 index) {
    func_80062978(index, 0xB4);
}

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/0365A0", func_80062A40);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/0365A0", func_80062A5C);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/0365A0", func_80062A8C);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/0365A0", func_80062AA8);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/0365A0", func_80062AC4);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/0365A0", func_80062AE0);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/0365A0", func_80062AFC);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/0365A0", func_80062B18);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/0365A0", func_80062B34);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/0365A0", func_80062B50);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/0365A0", func_80062B84);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/0365A0", func_80062BC4);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/0365A0", func_80062BD4);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/0365A0", func_80062DA4);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/0365A0", func_80062DD8);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/0365A0", func_80062E84);

void func_80062EC0(struct_800F3E50_unk_0B8 *arg0) {
    f32 val = 0.025f;
    u32 i = 0;
    s32 var_s0 = arg0->unk_A0;

    while (i < ARRAY_COUNTU(arg0->unk_00)) {
        struct_800F3E50_unk_0B8_unk_00 *temp_s1 = &arg0->unk_00[var_s0];

        if (arg0->unk_00[WrapI(0, ARRAY_COUNTU(arg0->unk_00), var_s0 - 1)].unk_10 > 0.2) {
            temp_s1->unk_10 = MIN(1.0f, temp_s1->unk_10 + val);
        }
        var_s0 = (var_s0 + 1) % ARRAY_COUNTU(arg0->unk_00);
        i++;
    }
}

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/0365A0", D_800B1EB8);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/0365A0", scoreNums_set);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/0365A0", backup_game_state);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/0365A0", resume_game_state);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/0365A0", func_80063378);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/0365A0", func_800633C0);

void func_800633FC(void) {
    if (watchGame->unk_000 != 0) {
        replay_play_init();
    } else {
        replay_record_init(evs_playcnt);
    }
}

void dm_warning_h_line_se(void) {
    struct_800F3E50 *ptr = watchGame;
    s32 var_a0 = 0;
    s32 i;

    for (i = 0; i < evs_playcnt; i++) {
        if (game_state_data[i].unk_020 == 1) {
            var_a0 += game_state_data[i].unk_044 != 0;
        }
    }

    if (var_a0 == 0) {
        ptr->unk_428 = 0;
    } else {
        ptr->unk_428++;

        if (ptr->unk_428 == 1) {
            dm_snd_play_in_game(SND_INDEX_79);
        } else if (ptr->unk_428 >= 300) {
            ptr->unk_428 = 0;
        }
    }
}

void dm_play_count_down_se(void) {
    s32 i;

    if (evs_gamemode != ENUM_EVS_GAMEMODE_3) {
        return;
    }

    for (i = 0; i < evs_playcnt; i++) {
        if (game_state_data[i].unk_020 == 1) {
            break;
        }
    }

    if (i != evs_playcnt) {
        s32 diff = i = 10800 - evs_game_time;
        s32 temp2;
        s32 temp1;

        //! FAKE
        temp2 = diff / 60;
        i = diff % 60;
        temp1 = i;

        if ((temp1 == 0) && (temp2 > 0) && (temp2 < 0xB)) {
            dm_snd_play_in_game(SND_INDEX_72);
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/0365A0", func_800635BC);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/0365A0", func_80063844);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/0365A0", func_800638AC);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/0365A0", func_80063A80);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/0365A0", func_80063FF4);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/0365A0", func_8006408C);

void func_80064130(s32 arg0, s32 arg1) {
    watchGame->unk_348[arg0] = arg1;
    watchGame->unk_358[arg0] = 0;
    watchGame->unk_368[arg0] = -1;

    switch (watchGame->unk_348[arg0]) {
        case 2:
        case 3:
        case 4:
        case 5:
            watchGame->unk_358[arg0]++;
            break;
    }
}

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/0365A0", func_8006417C);

s32 retryMenu_input(s32 arg0) {
    struct_800F3E50 *temp_s1 = watchGame;
    SndIndex soundIndex = SND_INDEX_INVALID;
    s32 ret = -1;
    u16 temp_s0 = joycur[main_joy[arg0]];
    u16 temp_s3 = gControllerPressedButtons[main_joy[arg0]];
    s32 temp_v0_3;
    u32 up;
    u32 down;

    temp_s1->unk_358[arg0] = WrapI(0, _retryMenu_itemCount[temp_s1->unk_348[arg0]], temp_s1->unk_358[arg0]);

    up = (temp_s0 & U_JPAD);
    up = up > 0;
    down = (temp_s0 & D_JPAD);
    down = down > 0;

    temp_v0_3 = WrapI(0, _retryMenu_itemCount[temp_s1->unk_348[arg0]], temp_s1->unk_358[arg0] + (down - up));

    if (temp_v0_3 != temp_s1->unk_358[arg0]) {
        temp_s1->unk_358[arg0] = temp_v0_3;
        soundIndex = SND_INDEX_64;
    } else if (temp_s3 & (A_BUTTON | START_BUTTON)) {
        ret = temp_s1->unk_368[arg0];
    }

    if (soundIndex > SND_INDEX_INVALID) {
        dm_snd_play_in_game(soundIndex);
    }

    return ret;
}

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/0365A0", func_80064298);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/0365A0", func_8006431C);

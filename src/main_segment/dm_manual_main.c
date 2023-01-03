/**
 * Original filename: dm_manual_main.c
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

void func_80071EF0(struct_800F4890_unk_034 *arg0, s32 arg1, s32 arg2) {
    arg0->unk_00 = arg1;
    arg0->unk_04 = arg2;
    arg0->messageWnd.unk_28 = arg1 + 8;
    arg0->messageWnd.unk_2C = arg2 + 8;
}

void func_80071F0C(void) {
}

void func_80071F14(struct_800F4890_unk_034 *arg0, UNK_PTR *arg1) {
    arg0->unk_08 = 0;
    arg0->unk_0C = -0.0625f;
    msgWnd_init(&arg0->messageWnd, arg1, 0xD, 4, 0x20, 0x20);
    arg0->messageWnd.unk_30 = 0xA;
    arg0->messageWnd.unk_34 = 0xC;
    arg0->messageWnd.unk_3C = 5;
    arg0->messageWnd.unk_48 = 0xD;
    arg0->messageWnd.unk_54 = 0.16666667f;
    func_80071EF0(arg0, 0x20, 0x20);
}

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_manual_main", func_80071FA0);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_manual_main", tutolWnd_draw);

extern const UNK_TYPE RO_800B2410;
extern const UNK_TYPE RO_800B2414;
extern const UNK_TYPE RO_800B2430;
extern const UNK_TYPE RO_800B2434;
extern const u8 virus_2_1[][3];
extern const u8 position_2_1[][4];
extern const char mes_2_1[];
extern const char mes_2_2[];
extern const char mes_2_3[];
extern const char mes_2_4[];
extern const char mes_2_5[];
extern const char mes_2_6[];
extern const char mes_2_7[];
extern const char mes_2_8[];
extern const char mes_2_9[];

extern const s32 RO_800B2408;
extern const s32 RO_800B240C;
extern const s32 RO_800B2428;
extern const s32 RO_800B242C;
extern const u8 RO_800B246C[];
extern const u8 RO_800B2474[];
extern const u8 virus_1_1[][3];
extern const u8 position_1_1[][4];
extern const char mes_1_1[];
extern const char mes_1_2[];
extern const char mes_1_3[];
extern const char mes_1_4[];
extern const char mes_1_5[];
extern const char mes_1_6[];
extern const char mes_1_7[];
extern const char mes_1_8[];

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", RO_800B2408);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", RO_800B240C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", RO_800B2410);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", RO_800B2414);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", RO_800B2418);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", RO_800B241C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", RO_800B2420);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", RO_800B2424);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", RO_800B2428);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", RO_800B242C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", RO_800B2430);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", RO_800B2434);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", RO_800B2438);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", RO_800B243C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", RO_800B2440);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", RO_800B2444);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", virus_1_1);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", RO_800B246C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", RO_800B2474);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", position_1_1);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", virus_2_1);

const u8 capsel_2_1[] = {
    0x21, 0x02, 0x10, 0x12, 0x21, 0x00, 0x01, 0x20, 0x21, 0x12, 0x10, 0x10,
};

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", position_2_1);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", RO_800B24FC);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", RO_800B2538);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", RO_800B2544);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", RO_800B256C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", RO_800B259C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", RO_800B25B0);

void func_800721A0(struct_800F4890_unk_034 *arg0) {
    msgWnd_clear(&arg0->messageWnd);
}

void func_800721BC(struct_800F4890_unk_034 *arg0, const char *arg1) {
    msgWnd_addStr(&arg0->messageWnd, arg1);
}

void func_800721D8(struct_800F4890_unk_034 *arg0) {
    if (arg0->unk_0C < 0.0f) {
        arg0->unk_0C = -arg0->unk_0C;
    }
}

void func_80072204(struct_800F4890_unk_034 *arg0) {
    if (arg0->unk_0C > 0.0f) {
        arg0->unk_0C = -arg0->unk_0C;
    }
}

bool func_80072230(struct_800F4890_unk_034 *arg0) {
    return msgWnd_isEnd(&arg0->messageWnd);
}

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_manual_main", func_8007224C);

void func_80072268(struct_800F4890_unk_0E8 *arg0, s32 arg1, s32 arg2) {
    arg0->unk_0 = arg1;
    arg0->unk_1 = 1;
    arg0->unk_2 = arg2;
    arg0->unk_3[0] = 1;
}

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", mes_1_1);

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", mes_1_2);

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", mes_1_3);

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", mes_1_4);

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", mes_1_5);

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", mes_1_6);

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", mes_1_7);

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", mes_1_8);

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", mes_2_1);

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", mes_2_2);

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", mes_2_3);

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", mes_2_4);

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", mes_2_5);

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", mes_2_6);

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", mes_2_7);

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", mes_2_8);

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", mes_2_9);

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", STR_800B2A54);

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", STR_800B2A98);

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", STR_800B2ADC);

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", STR_800B2B24);

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", STR_800B2B58);

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", STR_800B2BA8);

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", STR_800B2BF4);

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", STR_800B2C44);

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", STR_800B2C90);

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", STR_800B2CDC);

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", STR_800B2D28);

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", STR_800B2D60);

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", STR_800B2D90);

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", STR_800B2DD8);

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", STR_800B2E24);

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", STR_800B2E58);

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", STR_800B2E90);

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", STR_800B2ED4);

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", STR_800B2F20);

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", STR_800B2F60);

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", STR_800B2FAC);

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", STR_800B2FE4);

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", STR_800B302C);

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", STR_800B3054);

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", STR_800B3078);

ASM_TEXT;

void dm_manual_attack_capsel_down(void) {
    struct_watchManual *watchManualP = watchManual;
    GameMapGrid *mapGrid = game_map_data;
    bool playSound = false;
    s32 i;

    for (i = 0; i < 4; i++) {
        watchManualP->unk_174[i]++;
        if (watchManualP->unk_174[i] >= 0xE) {
            s32 j;

            watchManualP->unk_174[i] = 0;

            for (j = 0; j < 4; j++) {
                if (watchManualP->unk_0E8[i][j].unk_3[0] == 0) {
                    continue;
                }

                if (get_map_info(&mapGrid[i], watchManualP->unk_0E8[i][j].unk_0,
                                 watchManualP->unk_0E8[i][j].unk_1 + 1)) {
                    set_map(&mapGrid[i], watchManualP->unk_0E8[i][j].unk_0, watchManualP->unk_0E8[i][j].unk_1, 4,
                            watchManualP->unk_0E8[i][j].unk_2);
                    watchManualP->unk_0E8[i][j].unk_3[0] = 0;
                } else {
                    playSound = true;

                    if (watchManualP->unk_0E8[i][j].unk_1 < 0x10) {
                        watchManualP->unk_0E8[i][j].unk_1++;
                    }

                    if (watchManualP->unk_0E8[i][j].unk_1 == 0x10) {
                        set_map(&mapGrid[i], watchManualP->unk_0E8[i][j].unk_0, 0x10, 4,
                                watchManualP->unk_0E8[i][j].unk_2);
                        watchManualP->unk_0E8[i][j].unk_3[0] = 0;
                    }
                }
            }
        }
    }

    if (playSound) {
        dm_snd_play(SND_INDEX_55);
    }
}

void func_800723EC(struct_game_state_data *gameStateDataP, GameMapGrid *mapGrid, s32 arg2 UNUSED) {
    if ((gameStateDataP->unk_014 != 1) & (gameStateDataP->unk_014 != 0xD)) {
        dm_black_up(gameStateDataP, mapGrid);
    }
}

void dm_manual_update_virus_anime(struct_game_state_data *arg0) {
    s32 i;

    for (i = 0; i < 3; i++) {
        animeState_update(get_virus_anime_state(i));
        animeSmog_update(get_virus_smog_state(i));
    }

    dm_calc_big_virus_pos(arg0);
}

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_manual_main", dm_manual_main_cnt);

#ifdef NON_MATCHING
// regalloc
void dm_manual_make_key(struct_game_state_data *arg0, GameMapGrid *mapGrid) {
    struct_watchManual *temp_s3 = watchManual;
    struct_game_state_data_unk_178 *temp_s4;
    u16 temp_s2;
    s32 temp_v0;

    aifKeyOut();

    temp_s2 = joygam[arg0->unk_04B];
    temp_s4 = &arg0->unk_178;

    if (temp_s2 & 0x4000) {
        rotate_capsel(mapGrid, temp_s4, -1);
        temp_s3->unk_01C[3] = 8;
    } else if (temp_s2 & 0x8000) {
        rotate_capsel(mapGrid, temp_s4, 1);
        temp_s3->unk_01C[2] = 8;
    }

    if (temp_s2 & 0x200) {
        translate_capsel(mapGrid, arg0, -1, main_joy[arg0->unk_04B]);
        temp_s3->unk_01C[0] = 8;
    } else if (temp_s2 & 0x100) {
        translate_capsel(mapGrid, arg0, 1, main_joy[arg0->unk_04B]);
        temp_s3->unk_01C[1] = 8;
    }

    arg0->unk_030 = 1;
    if ((temp_s2 & 0x400) && (temp_s4->unk_2 > 0)) {
        temp_v0 = FallSpeed[arg0->unk_02D];
        arg0->unk_030 = (temp_v0 >> 1) + (temp_v0 & 1);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/main_segment/dm_manual_main", dm_manual_make_key);
#endif

#ifdef NON_MATCHING
s32 dm_manual_1_main(void) {
    struct_watchManual *temp_s1 = watchManual;
    struct_game_state_data *gameStateDataP = game_state_data;
    s32 var_s6 = 1;
    GameMapGrid *mapGrid = game_map_data;
    s32 var_s5;
    u32 temp_s0_4;
    s32 var_s0;

    struct_game_state_data_unk_178 *unk_178 = &gameStateDataP->unk_178;

    // var_s5 = saved_reg_s5;

    for (var_s0 = 0; var_s0 < ARRAY_COUNTU(temp_s1->unk_01C); var_s0++) {
        if (temp_s1->unk_01C[var_s0] != -0x14) {
            temp_s1->unk_01C[var_s0]--;
        }
    }

    if (temp_s1->unk_16C != 0) {
        var_s5 = dm_manual_main_cnt(gameStateDataP, mapGrid, 0, 0);
        dm_manual_make_key(gameStateDataP, mapGrid);
    }

    func_800723EC(gameStateDataP, mapGrid, 0);
    dm_virus_anime(gameStateDataP, mapGrid);
    dm_manual_update_virus_anime(gameStateDataP);
    dm_warning_h_line_se();

    switch (temp_s1->unk_164) {
        case 0x0:
            func_80071EF0(&temp_s1->unk_034, RO_800B2408, RO_800B240C);
            temp_s1->unk_000 = 1;
            temp_s1->unk_004 = RO_800B2428;
            temp_s1->unk_008 = RO_800B242C;
            func_80072204(&temp_s1->unk_034);
            temp_s1->unk_164 += 1;

            for (var_s0 = 0; var_s0 < 5U; var_s0++) {
                CapsMagazine[var_s0 + 1] = RO_800B246C[var_s0];
            }

            gameStateDataP->unk_032 = 1;
            dm_set_capsel(gameStateDataP);
            break;

        case 0x1:
            set_virus(mapGrid, virus_1_1[gameStateDataP->unk_025][1], virus_1_1[gameStateDataP->unk_025][2],
                      virus_1_1[gameStateDataP->unk_025][0],
                      virus_anime_table[virus_1_1[gameStateDataP->unk_025][0]][gameStateDataP->unk_027]);

            gameStateDataP->unk_025++;
            if (gameStateDataP->unk_025 >= 4U) {
                temp_s1->unk_164 = 0xA;
            }
            break;

        case 0xA:
            func_800721D8(&temp_s1->unk_034);
            func_800721BC(&temp_s1->unk_034, mes_1_1);
            temp_s1->unk_164 = 0x30A;
            temp_s1->unk_168 = 0x14;
            break;

        case 0x14:
            func_800721A0(&temp_s1->unk_034);
            func_800721BC(&temp_s1->unk_034, mes_1_2);
            temp_s1->unk_164 = 0x30A;
            temp_s1->unk_168 = 0x1E;
            break;

        case 0x1E:
            func_800721A0(&temp_s1->unk_034);
            func_800721BC(&temp_s1->unk_034, mes_1_3);
            temp_s1->unk_164 = 0x30A;
            temp_s1->unk_168 = 0x28;
            break;

        case 0x28U:
            func_800721A0(&temp_s1->unk_034);
            func_800721BC(&temp_s1->unk_034, mes_1_4);
            temp_s1->unk_164 = 0x30A;
            temp_s1->unk_168 = 0x29;
            break;

        case 0x29:
            temp_s1->unk_16C = 1;
            gameStateDataP->unk_00C = 4;
            aifMake2(gameStateDataP, 3, 0xC, 0, 0);
            temp_s1->unk_164 += 1;
            break;

        case 0x2A:
            gameStateDataP->unk_030 = 1;

            switch (unk_178->unk_2) {
                case 0x4:
                    if (unk_178->unk_2 == unk_178->unk_3) {
                        rotate_capsel(mapGrid, unk_178, -1);
                        temp_s1->unk_01C[3] = 8;
                    }
                    break;

                case 0x6:
                    if (unk_178->unk_2 != unk_178->unk_3) {
                        rotate_capsel(mapGrid, unk_178, -1);
                        temp_s1->unk_01C[3] = 8;
                    }
                    break;

                case 0x8:
                    if (unk_178->unk_2 == unk_178->unk_3) {
                        rotate_capsel(mapGrid, unk_178, 1);
                        temp_s1->unk_01C[2] = 8;
                    }
                    break;

                case 0xA:
                    if (unk_178->unk_2 != unk_178->unk_3) {
                        rotate_capsel(mapGrid, unk_178, 1);
                        temp_s1->unk_01C[2] = 8;
                    }
                    break;

                case 0xC:
                    aifMakeFlagSet(gameStateDataP);
                    aifMake2(gameStateDataP, 4, 0xE, 0, 0);
                    temp_s1->unk_164 += 1;
                    break;
            }
            break;

        case 0x2B:
            if (gameStateDataP->unk_23D == 0) {
                temp_s1->unk_164 = 0x32;
            }
            break;

        case 0x32:
            temp_s1->unk_16C = 0;
            func_800721A0(&temp_s1->unk_034);
            func_800721BC(&temp_s1->unk_034, mes_1_5);
            temp_s1->unk_164 = 0x30A;
            temp_s1->unk_168 = 0x33;
            break;

        case 0x33:
            temp_s1->unk_16C = 1;
            aifMake2(gameStateDataP, 2, 0xC, 1, 0);
            temp_s1->unk_164 += 1;
            break;

        case 0x34:
            if (gameStateDataP->unk_23D == 0) {
                aifMake2(gameStateDataP, 5, 0xD, 1, 0);
                temp_s1->unk_164 += 1;
            }
            break;

        case 0x35:
            if (gameStateDataP->unk_23D == 0) {
                temp_s1->unk_164 = 0x3C;
            }
            break;

        case 0x3C:
            temp_s1->unk_16C = 0;
            func_800721A0(&temp_s1->unk_034);
            func_800721BC(&temp_s1->unk_034, mes_1_6);
            temp_s1->unk_164 = 0x30A;
            temp_s1->unk_168 = 0x3D;
            break;

        case 0x3D:
            temp_s1->unk_16C = 1;
            aifMake2(gameStateDataP, 2, 0x10, 0, 0);
            temp_s1->unk_164 += 1;
            break;

        case 0x3E:
            if (var_s5 == 6) {
                dm_seq_play(0xE);
                temp_s1->unk_014 = 0;
                temp_s1->unk_018 = 0x78;
                temp_s1->unk_164 += 1;
            }
            break;

        case 0x3F:
            if (var_s5 == 1) {
                clear_map_all(mapGrid);
                temp_s1->unk_164 += 1;
                gameStateDataP->unk_026 = 0xF;
                _dm_virus_init(0, gameStateDataP, &virus_map_data[0], virus_map_disp_order, var_s5);

                for (var_s0 = 0; var_s0 < 3; var_s0++) {
                    animeState_set(get_virus_anime_state(var_s0), 0);
                    animeSmog_stop(get_virus_smog_state(var_s0));
                }

                for (var_s0 = 0; var_s0 < 5U; var_s0++) {
                    CapsMagazine[var_s0 + 1] = RO_800B2474[var_s0];
                }

                gameStateDataP->unk_032 = 1;
                dm_set_capsel(gameStateDataP);
                gameStateDataP->unk_00C = 1;
                gameStateDataP->unk_014 = 2;
                gameStateDataP->unk_025 = 0;
            }
            break;

        case 0x40:

        {
            s32 index = virus_map_disp_order->unk_00[gameStateDataP->unk_025];

            set_virus(mapGrid, virus_map_data[0].unk_000[index].unk_1, virus_map_data[0].unk_000[index].unk_2,
                      virus_map_data[0].unk_000[index].unk_0,
                      virus_anime_table[virus_map_data[0].unk_000[index].unk_0][gameStateDataP->unk_027]);
        }

            gameStateDataP->unk_025++;
            if (gameStateDataP->unk_025 >= dm_get_first_virus_count(evs_gamemode, gameStateDataP)) {
                temp_s1->unk_164 = 0x46;
            }
            break;

        case 0x46:
            func_800721A0(&temp_s1->unk_034);
            func_800721BC(&temp_s1->unk_034, mes_1_7);
            temp_s1->unk_164 = 0x30A;
            temp_s1->unk_168 = 0x47;
            break;

        case 0x47:
            temp_s1->unk_16C = 1;
            gameStateDataP->unk_00C = 4;
            aifMakeFlagSet(gameStateDataP);
            temp_s1->unk_164 += 1;
            break;

        case 0x48:
            temp_s0_4 = gameStateDataP->unk_032 - 2;
            if (temp_s0_4 < 4U) {
                aifMake2(gameStateDataP, position_1_1[temp_s0_4][0], position_1_1[temp_s0_4][1],
                         position_1_1[temp_s0_4][2], position_1_1[temp_s0_4][3]);
            } else {
                temp_s1->unk_164 = 0x49;
            }
            break;

        case 0x49:
            if (var_s5 == -1) {
                dm_seq_play(0x11);
                temp_s1->unk_164 += 1;
            }
            break;

        case 0x4A:
            if (var_s5 == 0x64) {
                temp_s1->unk_164 = 0x50;
            }
            break;

        case 0x50:
            func_800721A0(&temp_s1->unk_034);
            func_800721BC(&temp_s1->unk_034, mes_1_8);
            temp_s1->unk_164 = 0x30A;
            temp_s1->unk_168 = 0x30C;
            break;

        case 0x30A:
            if (func_80072230(&temp_s1->unk_034)) {
                temp_s1->unk_164 = temp_s1->unk_168;
            }
            break;

        case 0x30C:
            var_s6 = 0;
            break;
    }

    return var_s6;
}
#else
INCLUDE_ASM("asm/nonmatchings/main_segment/dm_manual_main", dm_manual_1_main);
#endif

// probably returns bool
s32 dm_manual_2_main(void) {
    struct_watchManual *watchManualP = watchManual;
    struct_game_state_data *gameStateDataP = game_state_data;
    GameMapGrid *mapGrid = game_map_data;
    s32 ret = 1;
    s32 i;

    if (watchManualP->unk_16C != 0) {
        dm_manual_main_cnt(gameStateDataP, &mapGrid[0], 0, 1);
        dm_manual_main_cnt(&gameStateDataP[1], &mapGrid[1], 1, 1);
        dm_manual_make_key(gameStateDataP, mapGrid);
    }

    func_800723EC(gameStateDataP, mapGrid, 0);
    dm_manual_attack_capsel_down();

    for (i = 0; i < 2; i++) {
        dm_virus_anime(&gameStateDataP[i], &mapGrid[i]);
    }

    dm_warning_h_line_se();

    switch (watchManualP->unk_164) {
        case 0x0:
            func_80071EF0(&watchManualP->unk_034, RO_800B2410, RO_800B2414);
            watchManualP->unk_000 = 1;
            watchManualP->unk_004 = RO_800B2430;
            watchManualP->unk_008 = RO_800B2434;
            func_80072204(&watchManualP->unk_034);
            watchManualP->unk_164 = 1;

            for (i = 0; i < ARRAY_COUNTU(capsel_2_1); i++) {
                CapsMagazine[i + 1] = capsel_2_1[i];
            }
            gameStateDataP->unk_032 = 1;
            dm_set_capsel(gameStateDataP);
            break;

        case 0x1:
            set_virus(mapGrid, virus_2_1[gameStateDataP->unk_025][1], virus_2_1[gameStateDataP->unk_025][2],
                      virus_2_1[gameStateDataP->unk_025][0],
                      virus_anime_table[virus_2_1[gameStateDataP->unk_025][0]][gameStateDataP->unk_027]);

            gameStateDataP->unk_025++;
            if (gameStateDataP->unk_025 >= 0x14U) {
                watchManualP->unk_164 = 0xA;
            }
            break;

        case 0xA:
            func_800721D8(&watchManualP->unk_034);
            func_800721BC(&watchManualP->unk_034, mes_2_1);
            watchManualP->unk_164 = 0x30A;
            watchManualP->unk_168 = 0x14;
            break;

        case 0x14:
            func_800721A0(&watchManualP->unk_034);
            func_800721BC(&watchManualP->unk_034, mes_2_2);
            watchManualP->unk_164 = 0x30A;
            watchManualP->unk_168 = 0x1E;
            break;

        case 0x1E:
            func_800721A0(&watchManualP->unk_034);
            func_800721BC(&watchManualP->unk_034, mes_2_3);
            watchManualP->unk_164 = 0x30A;
            watchManualP->unk_168 = 0x28;
            break;

        case 0x28:
            func_800721A0(&watchManualP->unk_034);
            func_800721BC(&watchManualP->unk_034, mes_2_4);
            watchManualP->unk_164 = 0x30A;
            watchManualP->unk_168 = 0x32;
            break;

        case 0x32:
            func_800721A0(&watchManualP->unk_034);
            func_800721BC(&watchManualP->unk_034, mes_2_5);
            watchManualP->unk_164 = 0x30A;
            watchManualP->unk_168 = 0x3C;
            break;

        case 0x3C:
            func_800721A0(&watchManualP->unk_034);
            func_800721BC(&watchManualP->unk_034, mes_2_6);
            watchManualP->unk_164 = 0x30A;
            watchManualP->unk_168 = 0x3D;
            break;

        case 0x3D:
            gameStateDataP->unk_00C = 4;
            watchManualP->unk_164 = 0x309;
            watchManualP->unk_168 = 0x46;
            break;

        case 0x46:
            func_800721A0(&watchManualP->unk_034);
            func_800721BC(&watchManualP->unk_034, mes_2_7);
            watchManualP->unk_164 = 0x30A;
            watchManualP->unk_168 = 0x47;
            break;

        case 0x47:
            watchManualP->unk_164 = 0x309;
            watchManualP->unk_168 = 0x50;
            break;

        case 0x50:
            watchManualP->unk_164 = 0x309;
            watchManualP->unk_168 = 0x51;
            break;

        case 0x51:
            func_800721A0(&watchManualP->unk_034);
            func_800721BC(&watchManualP->unk_034, mes_2_8);
            watchManualP->unk_164 = 0x30A;
            watchManualP->unk_168 = 0x5A;
            break;

        case 0x5A:
            func_800721A0(&watchManualP->unk_034);
            func_800721BC(&watchManualP->unk_034, mes_2_9);
            watchManualP->unk_164 = 0x30A;
            watchManualP->unk_168 = 0x30C;
            break;

        case 0x309:
            watchManualP->unk_16C = 1;
            i = gameStateDataP->unk_032 - 2;
            if (i < 0xAU) {
                aifMake2(gameStateDataP, position_2_1[i][0], position_2_1[i][1], position_2_1[i][2],
                         position_2_1[i][3]);
            }

            switch (watchManualP->unk_030) {
                case 0:
                    if (i == 2) {
                        func_80072268(watchManualP->unk_0E8[1], 2, 2);
                        func_80072268(&watchManualP->unk_0E8[1][1], 6, 0);
                        watchManualP->unk_174[1] = 0;
                        watchManualP->unk_164 = 0x30B;
                        watchManualP->unk_030 += 1;
                    }
                    break;

                case 1:
                    if (i == 5) {
                        func_80072268(watchManualP->unk_0E8[1], 2, 2);
                        func_80072268(&watchManualP->unk_0E8[1][1], 4, 0);

                        func_80072268(&watchManualP->unk_0E8[1][2], 6, 1);
                        watchManualP->unk_174[1] = 0;
                        watchManualP->unk_164 = 0x30B;
                        watchManualP->unk_030 += 1;
                    }
                    break;

                case 2:
                    if (i == 0xA) {
                        func_80072268(watchManualP->unk_0E8[1], 1, 0);
                        func_80072268(&watchManualP->unk_0E8[1][1], 3, 1);
                        func_80072268(&watchManualP->unk_0E8[1][2], 5, 0);
                        func_80072268(&watchManualP->unk_0E8[1][3], 7, 2);
                        watchManualP->unk_174[1] = 0;
                        watchManualP->unk_164 = 0x30B;
                        watchManualP->unk_030 += 1;
                    }
                    break;
            }
            break;

        case 0x30A:
            watchManualP->unk_16C = 0;
            if (func_80072230(&watchManualP->unk_034)) {
                watchManualP->unk_164 = watchManualP->unk_168;
            }
            break;

        case 0x30B:
            watchManualP->unk_16C = 0;
            if (watchManualP->unk_0E8[1][1].unk_3[0] == 0) {
                watchManualP->unk_164 = watchManualP->unk_168;
            }
            break;

        case 0x30C:
            ret = 0;
            break;

        default:
            break;
    }

    return ret;
}

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_manual_main", dm_manual_3_main);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_manual_main", dm_manual_4_main);

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", RO_800B3130);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", RO_800B3134);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", RO_800B3140);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", RO_800B3144);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", RO_800B3150);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_manual_main", func_80074954);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_manual_main", func_80074B08);

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", RO_800B3178);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", RO_800B317C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", RO_800B3180);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", RO_800B31A0);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_manual_main", func_80074EF0);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_manual_main", func_80074FE0);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_manual_main", dm_manual_draw_fg);

const u16 map_x_table_1036[][4] = {
    { 0x76, 0x76, 0x76, 0x76 },
    { 0x1C, 0xD4, 0x1C, 0xD4 },
    { 0x14, 0x5C, 0xA4, 0xEC },
};
const u8 _seqTbl_1037[] = { 2, 3 };
const u8 map_y_table_1038[] = { 0x2E, 0x2E };
const u8 size_table_1039[] = { 0xA, 8 };

void dm_manual_all_init(void) {
    struct_watchManual *temp_v0_2;
    s32 j;
    s32 i;
    s32 k;
    struct_game_state_data *var_a0_2;
    void **headTopPtr;

    evs_seqnumb = _seqTbl_1037[evs_manual_no % ARRAY_COUNTU(_seqTbl_1037)];
    evs_seqence = 1;

    switch (evs_manual_no) {
        case EVS_MANUAL_NO_0:
        case EVS_MANUAL_NO_3:
            evs_gamesel = ENUM_EVS_GAMESEL_0;
            evs_playcnt = 1;
            break;

        case EVS_MANUAL_NO_1:
        case EVS_MANUAL_NO_4:
            evs_gamesel = ENUM_EVS_GAMESEL_1;
            evs_playcnt = 2;
            break;

        case EVS_MANUAL_NO_2:
        case EVS_MANUAL_NO_5:
            evs_gamesel = ENUM_EVS_GAMESEL_2;
            evs_playcnt = 4;
            break;
    }

    evs_gamemode = ENUM_EVS_GAMEMODE_0;
    story_proc_no = STORY_PROC_NO_1;

    dm_game_init_heap();
    headTopPtr = dm_game_heap_top();
    watchManual = ALIGN_PTR(*headTopPtr);

    temp_v0_2 = watchManual;
    bzero(temp_v0_2, sizeof(struct_watchManual));

    *headTopPtr = &watchManual[1];

    _texAll = tiLoadTexData(headTopPtr, _romDataTbl[ROMDATATBL_TUTORIAL_KASA].start,
                            _romDataTbl[ROMDATATBL_TUTORIAL_KASA].end);
    _texKaSa =
        tiLoadTexData(headTopPtr, _romDataTbl[ROMDATATBL_MENU_KASA].start, _romDataTbl[ROMDATATBL_MENU_KASA].end);

    func_80071F14(&temp_v0_2->unk_034, headTopPtr);
    func_800721D8(&temp_v0_2->unk_034);

    dm_game_init_static();
    dm_game_init_snap_bg();
    dm_game_init(false);
    temp_v0_2->unk_00C = 0xFF;
    temp_v0_2->unk_010 = -8;
    temp_v0_2->unk_170 = 0;

    for (i = 0; i < ARRAY_COUNTU(temp_v0_2->unk_01C); i++) {
        temp_v0_2->unk_01C[i] = -0x14;
    }

    temp_v0_2->unk_02C = 0;
    temp_v0_2->unk_014 = 0;
    temp_v0_2->unk_018 = 0;
    temp_v0_2->unk_184 = 0;

    j = 0;
    for (i = 0; i < 3; i++) {
        temp_v0_2->unk_14C[i].unk_0 = 0;
        temp_v0_2->unk_14C[i].unk_4 = 0;
        temp_v0_2->unk_0C4[i].unk_8 = j;
        temp_v0_2->unk_0C4[i].unk_0 = (sinf(temp_v0_2->unk_0C4[i].unk_8 * 3.141592654 / 180) * 20) + 45;
        temp_v0_2->unk_0C4[i].unk_4 = (cosf(temp_v0_2->unk_0C4[i].unk_8 * 3.141592654 / 180) * -20) + 155;

        j += 120;
    }

    switch (evs_manual_no) {
        case EVS_MANUAL_NO_0:
        case EVS_MANUAL_NO_3:
            k = 0;
            j = 0;
            break;

        case EVS_MANUAL_NO_1:
        case EVS_MANUAL_NO_4:
            k = 0;
            j = 1;
            break;

        case EVS_MANUAL_NO_2:
        case EVS_MANUAL_NO_5:
            k = 1;
            j = 2;
            break;
    }

    var_a0_2 = game_state_data;
    for (i = 0; i < ARRAY_COUNT(game_state_data); i++) {
        var_a0_2[i].unk_008 = map_y_table_1038[k];
        var_a0_2[i].unk_00A = size_table_1039[k];
        var_a0_2[i].unk_006 = map_x_table_1036[j][i];
    }

    var_a0_2 = game_state_data;
    for (i = 0; i < ARRAY_COUNT(game_state_data); i++) {
        s8 *gamespeed_ptr = GameSpeed;
        struct_800F4890_unk_0E8 *temp;

        var_a0_2[i].unk_02C = 1;
        var_a0_2[i].unk_02D = gamespeed_ptr[1];
        var_a0_2[i].unk_04D = 0;
        var_a0_2[i].unk_04E = 2;

        switch (evs_manual_no) {
            case EVS_MANUAL_NO_2:
            case EVS_MANUAL_NO_5:
                var_a0_2[i].unk_02B = 0xC;
                var_a0_2[i].unk_02A = 0;
                break;

            default:
                var_a0_2[i].unk_02B = 8;
                var_a0_2[i].unk_02A = 2;
                break;
        }

        temp_v0_2->unk_174[i] = 0;

        temp = temp_v0_2->unk_0E8[i];
        for (j = 0; j < ARRAY_COUNTU(temp_v0_2->unk_0E8[i]); j++) {
            struct_800F4890_unk_0E8 *temp2 = &temp[j];

            temp2->unk_0 = 0;
            temp2->unk_1 = 0;
            temp2->unk_2 = 0;

            for (k = 0; k < ARRAY_COUNTU(temp2->unk_3); k++) {
                temp2->unk_3[k] = 0;
            }
        }
    }

    temp_v0_2->unk_164 = 0;
    temp_v0_2->unk_168 = 0;
    temp_v0_2->unk_16C = 0;
    temp_v0_2->unk_030 = 0;
}

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
    struct_watchManual *temp_s2;

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
            case EVS_MANUAL_NO_0:
                var_s3 = dm_manual_1_main();
                break;

            case EVS_MANUAL_NO_1:
                var_s3 = dm_manual_2_main();
                break;

            case EVS_MANUAL_NO_2:
                var_s3 = dm_manual_3_main();
                break;

            case EVS_MANUAL_NO_3:
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

            var_s3 &= -((gControllerPressedButtons[main_joy[0]] & temp) == 0);
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
INCLUDE_ASM("asm/nonmatchings/main_segment/dm_manual_main", dm_manual_main);
#endif

void dm_manual_graphic(void) {
    UNK_TYPE sp28;
    UNK_TYPE sp2C;
    OSScTask *ptr;
    s32 color;
    s32 alpha;
    struct_watchManual *temp_s1 = watchManual;

    gGfxHead = gGfxGlist[gfx_gtask_no];
    ptr = &B_800FAE80[gfx_gtask_no];

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
    gfxTaskStart(ptr, gGfxGlist[gfx_gtask_no], (gGfxHead - gGfxGlist[gfx_gtask_no]) * sizeof(Gfx), 0, OS_SC_SWAPBUFFER);
}

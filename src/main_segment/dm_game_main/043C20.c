/**
 * Part of dm_game_main.c
 */

#include "ultra64.h"
#include "include_asm.h"
#include "macros_defines.h"
#include "unknown_structs.h"
#include "boot_functions.h"
#include "boot_variables.h"
#include "main_segment_functions.h"
#include "main_segment_variables.h"
#include "gcc/memory.h"
#include "rom_offsets.h"
#include "buffers.h"
#include "audio/audio_stuff.h"

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/043C20", size_table_5385);

void dm_game_init_heap(void) {
    u32 i;
    u32 temp = 0x3000;

    heapTop = &Heap_bufferp;
    watchGame = ALIGN_PTR(&Heap_bufferp);
    bzero(watchGame, sizeof(struct_800F3E50));

    heapTop = &watchGame[1];
    for (i = 0; i < ARRAY_COUNT(B_800EF440); i++) {
        B_800EF440[i] = ALIGN_PTR(heapTop);
        heapTop = B_800EF440[i] + 0x2FB8;
    }

    B_800F48C0 = heapTop + 8;
    heapTop = B_800F48C0 + temp;
}

extern const u16 map_x_table_5383[][4];
extern const u8 map_y_table_5384[];
extern const u8 size_table_5385[];
extern const f32 _big_virus_def_wait[];

void dm_game_init(bool arg0) {
    struct_800F3E50 *watchGameP = watchGame;
    s32 i;
    s32 j;
    s32 var_a1;
    s32 var_s4;
    struct_80123700 *temp_s0_3;
    struct_80123700 *var_s0_2;
    struct_virus_map_data *var_s1_5;
    struct_virus_map_disp_order *var_s3;

    if (!arg0 || (watchGameP->unk_000 == 0)) {
        watchGameP->unk_000 = 0;
        watchGameP->unk_004 = (genrand(0xFFFF) + osGetTime()) * 0x10001;
        watchGameP->unk_008 = irandom() + osGetTime();
    }

    sgenrand(watchGameP->unk_004);
    randomseed(watchGameP->unk_008);

    if (!arg0) {
        for (i = 0; i < ARRAY_COUNTU(watchGameP->unk_00C); i++) {
            watchGameP->unk_03C[i] = 0;
            watchGameP->unk_00C[i] = 0;
        }

        watchGameP->unk_06C = 0;
        func_80069160(&watchGameP->unk_070, watchGameP->unk_00C, watchGameP->unk_03C);

        // Redundant condition
        if (!arg0) {
            watchGameP->unk_378 = 0;
        }
    }

    for (i = 0; i < ARRAY_COUNTU(watchGameP->unk_0B8); i++) {
        func_80062E84(&watchGameP->unk_0B8[i]);
    }

    for (i = 0; i < ARRAY_COUNTU(watchGameP->unk_37C); i++) {
        watchGameP->unk_37C[i] = 0;
    }

    watchGameP->unk_38C = 0x1E;
    watchGameP->unk_390 = -1;

    for (i = 0; i < ARRAY_COUNTU(watchGameP->unk_39C); i++) {
        watchGameP->unk_39C[i] = 1;
    }

    watchGameP->unk_3AC = 0;
    watchGameP->unk_3B8 = 0;
    watchGameP->unk_3B4 = 0;
    watchGameP->unk_3C0 = 0;
    watchGameP->unk_3BC = (evs_gamemode != ENUM_EVS_GAMEMODE_1 ? 2 : 0) | 1;
    watchGameP->unk_3C4 = main_no != MAIN_NO_5;

    for (i = 0, var_a1 = 1; i < ARRAY_COUNTU(watchGameP->unk_400); i++) {
        watchGameP->unk_400[i] = 0;
        watchGameP->unk_3E8[i] = var_a1;
        watchGameP->unk_3F4[i] = 1.0f;
        var_a1 += 0x78;
    }

    watchGameP->unk_3CC = 0;
    watchGameP->unk_40C = 0;
    watchGameP->unk_410 = 0;
    watchGameP->unk_414 = 0;
    watchGameP->unk_3C8 = 10.0f;

    switch (evs_gamemode) {
        case ENUM_EVS_GAMEMODE_2:
            watchGameP->unk_3C8 = _big_virus_def_wait[game_state_data[0].unk_16C];
            break;

        default:
            break;
    }

    for (i = 0; i < ARRAY_COUNTU(watchGameP->unk_418); i++) {
        watchGameP->unk_418[i] = 0;
    }

    switch (evs_gamesel) {
        case ENUM_EVS_GAMESEL_4:
        case ENUM_EVS_GAMESEL_5:
        case ENUM_EVS_GAMESEL_6:
            watchGameP->unk_41C = 0x708;
            watchGameP->unk_420 = 1;
            break;

        default:
            watchGameP->unk_41C = 0;
            watchGameP->unk_420 = 0;
            break;
    }

    watchGameP->unk_424 = 0;
    watchGameP->unk_428 = 0;

    if (!arg0) {
        for (i = 0; i < ARRAY_COUNT(watchGameP->unk_89C); i++) {
            watchGameP->unk_89C[i] = 0;
        }
    }

    switch (evs_gamemode) {
        case ENUM_EVS_GAMEMODE_2:
        case ENUM_EVS_GAMEMODE_3:
            evs_game_time = 0;
            break;

        default:
            break;
    }

    dm_seq_play_in_game(evs_seqnumb * 2);
    dm_make_magazine();

    for (i = 0; i < ARRAY_COUNT(watchGameP->unk_8DC); i++) {
        for (j = 0; j < ARRAY_COUNT(watchGameP->unk_8DC[i]); j++) {
            watchGameP->unk_8DC[i][j] = -1;
        }
        j = 4;
    }

    watchGameP->unk_9C4 = -1;
    watchGameP->unk_9C8 = -1;
    watchGameP->unk_9CC = -1;
    watchGameP->unk_9BC = 0;
    watchGameP->unk_9C0 = 0;
    watchGameP->unk_A28.unk_74 = 0;
    watchGameP->unk_AA8 = -0x10;
    bzero(&watchGameP->unk_AAC, sizeof(struct_800F3E50_unk_AAC));

    switch (evs_gamesel) {
        case ENUM_EVS_GAMESEL_0:
        case ENUM_EVS_GAMESEL_4:
            var_s4 = 0;
            j = 0;
            break;

        case ENUM_EVS_GAMESEL_1:
        case ENUM_EVS_GAMESEL_3:
        case ENUM_EVS_GAMESEL_5:
            var_s4 = 0;
            j = 1;
            break;

        case ENUM_EVS_GAMESEL_2:
        case ENUM_EVS_GAMESEL_6:
            var_s4 = 1;
            j = 2;
            break;
    }

    temp_s0_3 = game_state_data;
    for (i = 0; i < ARRAY_COUNT(game_state_data); i++) {
        temp_s0_3[i].unk_008 = map_y_table_5384[var_s4];
        temp_s0_3[i].unk_00A = size_table_5385[var_s4];
        temp_s0_3[i].unk_006 = map_x_table_5383[j][i];
    }

    for (i = 0; i < ARRAY_COUNT(game_state_data); i++) {
        temp_s0_3 = &game_state_data[i];

        temp_s0_3->unk_04B = i;
        temp_s0_3->unk_00C = 1;
        temp_s0_3->unk_014 = 2;
        temp_s0_3->unk_01C = 1;
        temp_s0_3->unk_020 = 1;
        temp_s0_3->unk_025 = 0;
        temp_s0_3->unk_024 = 0;
        temp_s0_3->unk_044 = 0;
        temp_s0_3->unk_048 = 0;
        temp_s0_3->unk_049 = 0;
        temp_s0_3->unk_04A = 0;
        temp_s0_3->unk_02D = GameSpeed[temp_s0_3->unk_02C];
        temp_s0_3->unk_031 = 0;
        temp_s0_3->unk_030 = 1;
        temp_s0_3->unk_032 = 1;
        temp_s0_3->unk_02E = 0;
        temp_s0_3->unk_02F = 0;
        temp_s0_3->unk_034 = 0;
        func_80060FCC(temp_s0_3);
        temp_s0_3->unk_027 = 0;
        temp_s0_3->unk_029 = 0;
        temp_s0_3->unk_028 = 1;
        temp_s0_3->unk_035 = 0;
        temp_s0_3->unk_036 = 0;
        temp_s0_3->unk_037 = 0;
        temp_s0_3->unk_038 = 0;
        temp_s0_3->unk_03A = 0;
        temp_s0_3->unk_039 = 0;
        temp_s0_3->unk_168 = 0;
        temp_s0_3->unk_170 = 0;
        temp_s0_3->unk_174 = 0;

        switch (evs_gamesel) {
            case ENUM_EVS_GAMESEL_2:
            case ENUM_EVS_GAMESEL_6:
                temp_s0_3->unk_02B = 0xC;
                temp_s0_3->unk_02A = 0;
                break;

            default:
                temp_s0_3->unk_02B = 8;
                temp_s0_3->unk_02A = 2;
                break;
        }

        for (j = 0; j < ARRAY_COUNT(temp_s0_3->unk_03C); j++) {
            temp_s0_3->unk_03C[j] = 0;
        }

        for (j = 0; j < ARRAY_COUNT(temp_s0_3->unk_050); j++) {
            temp_s0_3->unk_050[j][0] = 0;
            temp_s0_3->unk_050[j][1] = 0;
        }

        init_map_all(&game_map_data[i]);
    }

    var_s3 = virus_map_disp_order;
    var_s1_5 = virus_map_data;
    var_s0_2 = game_state_data;
    for (i = 0; i < evs_playcnt; i++) {
        dm_virus_init(evs_gamemode, &var_s0_2[i], &var_s1_5[i], &var_s3[i]);
        if (evs_gamemode == ENUM_EVS_GAMEMODE_1) {
            make_flash_virus_pos(&var_s0_2[i], &var_s1_5[i], &var_s3[i]);
        } else {
            game_state_data[i].unk_164 = 0;
        }
    }

    for (i = 0; i < evs_playcnt - 1; i++) {
        for (j = i + 1; j < evs_playcnt; j++) {
            if (game_state_data[i].unk_026 == game_state_data[j].unk_026) {
                dm_virus_map_copy(&virus_map_data[i], &virus_map_data[j], &virus_map_disp_order[i],
                                  &virus_map_disp_order[j]);
                if (evs_gamemode == ENUM_EVS_GAMEMODE_1) {
                    game_state_data[j].unk_164 = game_state_data[i].unk_164;
                    bcopy(&game_state_data[i].unk_0D4, &game_state_data[j].unk_0D4, sizeof(struct_80123700_unk_0D4));
                    bcopy(&game_state_data[i].unk_140, &game_state_data[j].unk_140, sizeof(struct_80123700_unk_140));
                }
                break;
            }
        }
    }

    initEtcWork();
    aifGameInit();
    s_hard_mode = 0;
    fool_mode = 0;

    if (evs_story_level == 3) {
        if (evs_story_no == 7) {
            fool_mode = 1;
        } else {
            s_hard_mode = 1;
        }
    }
}

/**
 * Original name: dm_game_init_static
 */
void dm_game_init_static(void) {
    struct_800F3E50 *temp_s3 = watchGame;
    RomOffsetPair *romTableP = _romDataTbl;
    struct_800EF560 *temp_a1;
    s32 i;
    romoffset_t temp_a0;
    romoffset_t start;
    romoffset_t end;
    UNK_TYPE result;
    u32 pad[2] UNUSED;
    s8 temp;

    start = _romDataTbl[ROMDATATBL_GAME_AL].start;

    temp_s3->unk_3B0 = 0;
    temp_s3->unk_878 = 0x7F;
    end = _romDataTbl[ROMDATATBL_GAME_AL].end;
    result = tiLoadTexData(&heapTop, start, end);
    start = _romDataTbl[ROMDATATBL_GAME_ITEM].start;
    // let's silence the warning for now...
    temp_s3->unk_430 = (void *)result;
    end = _romDataTbl[ROMDATATBL_GAME_ITEM].end;
    temp_s3->unk_444 = tiLoadTexData(&heapTop, start, end);
    if (main_no != MAIN_NO_5) {
        temp_s3->unk_448 =
            tiLoadTexData(&heapTop, _romDataTbl[ROMDATATBL_MENU_KASA].start, _romDataTbl[ROMDATATBL_MENU_KASA].end);
    }

    temp_a0 = _romDataTbl[ROMDATATBL_GAME_ETC].start;
    temp_s3->unk_884 = heapTop;
    heapTop = DecompressRomToRam(temp_a0, heapTop, _romDataTbl[ROMDATATBL_GAME_ETC].end - temp_a0);

    for (i = 0; i < ARRAY_COUNT(temp_s3->unk_8AC); i++) {
        temp_s3->unk_8AC[i] = 0;
    }

    temp_s3->unk_394 = 0;
    temp_s3->unk_398 = 1;
    temp_s3->unk_898 = 2;
    func_8006A938(0);
    temp_s3->unk_9AC = 0;
    temp_s3->unk_9B0 = 0;
    temp_s3->unk_9B4 = 0;
    temp_s3->unk_9B8 = 0;

    replay_record_init_buffer(&heapTop);
    replay_record_init(evs_playcnt);

    temp = 0;
    for (i = 0; i < ARRAY_COUNTU(temp_s3->unk_9D0); i++) {
        func_80062B84(&temp_s3->unk_9D0[i]);
    }

    msgWnd_init2(&temp_s3->unk_A28, &heapTop, 0x100, 0xA, 5, temp, 0);
    temp_s3->unk_A28.unk_28 = (s32)(0x140 - (temp_s3->unk_A28.unk_3C * 0x14)) >> 1;
    temp_s3->unk_A28.unk_2C = (s32)(0xF0 - (temp_s3->unk_A28.unk_48 * 2)) >> 1;
    RecWritingMsg_init(&temp_s3->recMessage, &heapTop);

    switch (evs_gamesel) {
        case ENUM_EVS_GAMESEL_4:
            evs_high_score = 0xDD18;
            break;

        case ENUM_EVS_GAMESEL_0:
            temp_a1 = &evs_mem_data[evs_select_name_no[0]];
            if (evs_select_name_no[0] == 8) {
                evs_high_score = 0xDD18;
            } else {
                switch (evs_gamemode) {
                    case ENUM_EVS_GAMEMODE_0:
                        evs_high_score = temp_a1->unk_4C[game_state_data[0].unk_02C].unk_0;
                        break;
                    case ENUM_EVS_GAMEMODE_2:
                        evs_high_score = temp_a1->unk_64[game_state_data[0].unk_16C].unk_0;
                        break;
                    case ENUM_EVS_GAMEMODE_3:
                        evs_high_score = temp_a1->unk_7C[game_state_data[0].unk_16C].unk_0;
                        break;

                    default:
                        break;
                }
            }
            break;

        case ENUM_EVS_GAMESEL_1:
        case ENUM_EVS_GAMESEL_2:
        case ENUM_EVS_GAMESEL_3:
        case ENUM_EVS_GAMESEL_5:
        case ENUM_EVS_GAMESEL_6:
            if (evs_story_flg == 0) {
                evs_high_score = 0;
            }
            break;

        default:
            return;
    }

    switch (evs_gamesel) {
        case ENUM_EVS_GAMESEL_0:
        case ENUM_EVS_GAMESEL_4:
            temp_s3->unk_898 = 1;
            animeState_load(&game_state_data[0].unk_094, &heapTop, CHARANIMEMODE_MARIO);
            animeState_set(&game_state_data[0].unk_094, 2);
            temp_s3->unk_438 =
                tiLoadTexData(&heapTop, romTableP[ROMDATATBL_GAME_P1].start, romTableP[ROMDATATBL_GAME_P1].end);
            temp_s3->unk_434 =
                tiLoadTexData(&heapTop, romTableP[ROMDATATBL_GAME_LS].start, romTableP[ROMDATATBL_GAME_LS].end);

            for (i = 0; i < ARRAY_COUNT(temp_s3->animeStates); i++) {
                animeState_load(&temp_s3->animeStates[i], &heapTop, i + CHARANIMEMODE_VIRUS_R);
            }

            animeSmog_load(temp_s3->animeSmogs, &heapTop);
            for (i = 1; i < ARRAY_COUNT(temp_s3->animeSmogs); i++) {
                animeSmog_init(&temp_s3->animeSmogs[i], &temp_s3->animeSmogs[0]);
            }

            msgWnd_init2(&temp_s3->messageWnd, &heapTop, 0x1000, 0x14, 0xF, 0x28, 0xF);
            temp_s3->messageWnd.unk_24 = 1;
            msgWnd_addStr(&temp_s3->messageWnd, st_staffroll_txt);
            msgWnd_skip(&temp_s3->messageWnd);
            temp_s3->messageWnd.unk_20 = 1;
            temp_s3->messageWnd.unk_1C = 0;
            heapTop = init_coffee_break(heapTop, game_state_data[0].unk_02C);
            break;

        case ENUM_EVS_GAMESEL_1:
        case ENUM_EVS_GAMESEL_3:
        case ENUM_EVS_GAMESEL_5:
            for (i = 0; i < 2; i++) {
                animeState_load(&game_state_data[i].unk_094, &heapTop, game_state_data[i].unk_090);
            }

            if (evs_story_flg == 0) {
                for (i = 0; i < ARRAY_COUNT(temp_s3->unk_8B4); i++) {
                    temp_s3->unk_8B4[i] = 0;
                }

                switch (evs_gamesel) {
                    case ENUM_EVS_GAMESEL_1:
                        for (i = 0; i < ARRAY_COUNT(temp_s3->unk_8B4); i++) {
                            temp_s3->unk_8B4[i] = evs_mem_data[evs_select_name_no[i]].unk_A8;
                        }
                        break;

                    default:
                        break;
                }
            }
            temp_s3->unk_438 =
                tiLoadTexData(&heapTop, romTableP[ROMDATATBL_GAME_P1].start, romTableP[ROMDATATBL_GAME_P1].end);
            temp_s3->unk_43C =
                tiLoadTexData(&heapTop, romTableP[ROMDATATBL_GAME_P2].start, romTableP[ROMDATATBL_GAME_P2].end);
            break;

        case ENUM_EVS_GAMESEL_2:
        case ENUM_EVS_GAMESEL_6:
            temp_s3->unk_438 =
                tiLoadTexData(&heapTop, romTableP[ROMDATATBL_GAME_P1].start, romTableP[ROMDATATBL_GAME_P1].end);
            temp_s3->unk_440 =
                tiLoadTexData(&heapTop, romTableP[ROMDATATBL_GAME_P4].start, romTableP[ROMDATATBL_GAME_P4].end);

            for (i = 0; i < ARRAY_COUNT(game_state_data); i++) {
                animeState_load(&game_state_data[i].unk_094, &heapTop, game_state_data[i].unk_090);
            }

            for (i = 0; i < ARRAY_COUNT(temp_s3->unk_8CC); i++) {
                temp_s3->unk_8CC[i] = 0;
            }

            for (i = 0; i < ARRAY_COUNT(temp_s3->unk_8CC); i++) {
                temp_s3->unk_8CC[game_state_data[i].unk_04F]++;
            }

            temp_s3->unk_8BC = 0;

            for (i = 0; i < ARRAY_COUNT(game_state_data); i++) {
                if (game_state_data[i].unk_04C == 0) {
                    temp_s3->unk_8BC++;
                }
            }

            if (temp_s3->unk_8CC[0] == 1) {
                if (temp_s3->unk_8CC[1] == temp_s3->unk_8CC[0]) {
                    if (temp_s3->unk_8CC[2] == temp_s3->unk_8CC[1]) {
                        if (temp_s3->unk_8CC[3] == temp_s3->unk_8CC[2]) {
                            temp_s3->unk_8C0 = 0;
                            return;
                        }
                    }
                }
            }

            temp_s3->unk_8C0 = 1;
            temp_s3->unk_8C8 = 0;
            temp_s3->unk_8C4 = 0;

            for (i = 0; i < ARRAY_COUNT(game_state_data); i++) {
                if (game_state_data[i].unk_04F == 0) {
                    temp_s3->unk_8C4 |= (1 << i);
                }
            }

            for (i = 0; i < ARRAY_COUNT(game_state_data); i++) {
                if (game_state_data[i].unk_04F == 1) {
                    temp_s3->unk_8C8 |= (game_state_data[i].unk_04F << i);
                }
            }
            break;

        default:
            break;
    }
}

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/043C20", RO_800B2314);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/043C20", RO_800B2330);

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/043C20", D_800B233C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/043C20", D_800B2340);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/043C20", D_800B2344);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/043C20", D_800B2348);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/043C20", D_800B2354);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/043C20", D_800B2358);

ASM_TEXT;

void dm_game_init_snap_bg(void) {
    watchGame->unk_87C = (void *)ALIGN64((uintptr_t)heapTop);
    heapTop = watchGame->unk_87C + 0x26700;
    watchGame->unk_880 = 0;

    switch (evs_gamesel) {
        case ENUM_EVS_GAMESEL_0:
        case ENUM_EVS_GAMESEL_4:
            break;

        default:
            heapTop = func_80077170((BgRomDataIndex)story_proc_no, heapTop);
            break;
    }
}

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/043C20", dm_game_draw_snap_bg);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/043C20", func_8006F628);

enum_main_no dm_game_main(struct_800EB670 *arg0) {
    OSMesgQueue sp10;
    OSMesg sp28[8];
    struct_800FAF98_unk_64 sp48;
    enum_main_no ret;
    bool var_s2 = true;
    s32 var_s4;
    struct_800F3E50 *temp_s3;

    func_8006D0E8();
    osCreateMesgQueue(&sp10, sp28, ARRAY_COUNT(sp28));
    func_8002A184(arg0, &sp48, &sp10);
    func_80040A64();
    dm_game_init_heap();
    temp_s3 = watchGame;
    dm_game_init_static();
    dm_game_init_snap_bg();
    temp_s3->unk_880 = 1;
    dm_game_init(false);
    backup_game_state(0);
    D_800A6FC4 = 1;
    gGfxHead = gGfxGlist[gfx_gtask_no];

    while (var_s2 || (temp_s3->unk_38C != 0x1E)) {
        s16 *sp50;

        osRecvMesg(&sp10, (OSMesg *)&sp50, OS_MESG_BLOCK);
        if (sp10.validCount != 0) {
            D_80088104[1] = 1;
        }

        if (*sp50 != 1) {
            continue;
        }

        if (!var_s2) {
            if (temp_s3->unk_390 < 0) {
                temp_s3->unk_390 = -temp_s3->unk_390;
            }
        } else {
            u16 temp_s1 = gControllerPressedButtons[0];
            s32 i;

            for (i = 0; var_s2 && (i < evs_gamespeed); i++) {
                if (i != 0) {
                    gControllerPressedButtons[0] = 0;
                }
                var_s4 = dm_game_main2();
                var_s2 = var_s4 == 0;
            }

            gControllerPressedButtons[0] = temp_s1;
            if (temp_s3->unk_420 != 0) {
                dm_seq_set_volume(0x40);
            }

            dm_audio_update();
            dm_game_graphic_onDoneSawp();
            graphic_no = GRAPHIC_NO_4;
        }
    }

    D_800A6FC4 = 0;
    temp_s3->unk_878 = 0xF;

    while (temp_s3->unk_878 != 0) {
        osRecvMesg(&sp10, NULL, OS_MESG_BLOCK);
        dm_audio_update();
    }

    graphic_no = GRAPHIC_NO_0;
    memset(gFramebuffers[gCurrentFramebufferIndex ^ 1], 0xFF, sizeof(gFramebuffers[gCurrentFramebufferIndex ^ 1]));
    dm_audio_stop();

    while (!dm_audio_is_stopped() || (pendingGFX != 0)) {
        osRecvMesg(&sp10, NULL, OS_MESG_BLOCK);
        dm_audio_update();
    }

    ret = dm_game_main3(var_s4);
    while (func_80040BA4() != 0) {
        osRecvMesg(&sp10, NULL, OS_MESG_BLOCK);
    }

    func_80040AE4();
    func_8002A1DC(arg0, &sp48);

    return ret;
}

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/043C20", dm_game_main2);

/**
 * Original name: dm_game_main3
 */
INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/043C20", dm_game_main3);

void dm_game_graphic(void) {
    struct_800F3E50 *temp_s0 = watchGame;

    if (temp_s0->unk_878 != 0x7F) {
        osSetThreadPri(NULL, 0xF);
        temp_s0->unk_878 = 0;
        return;
    }

    RecWritingMsg_draw(&temp_s0->recMessage, &gGfxHead);

    gDPFullSync(gGfxHead++);
    gSPEndDisplayList(gGfxHead++);

    osWritebackDCacheAll();

    gfxTaskStart(&B_800FAE80[gfx_gtask_no], gGfxGlist[gfx_gtask_no], (gGfxHead - gGfxGlist[gfx_gtask_no]) * sizeof(Gfx),
                 0, (temp_s0->unk_880 == 0) ? OS_SC_SWAPBUFFER : 0);
    osSetThreadPri(NULL, 0xF);
    dm_game_graphic2();
    osSetThreadPri(NULL, 0x7F);
}

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/043C20", D_800B23C4);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/043C20", RO_800B23CC);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/043C20", D_800B23D4);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/043C20", dm_game_graphic2);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/043C20", dm_game_graphic_onDoneSawp);

void func_80071A44(void) {
}

/**
 * Original name: main_techmes
 */
enum_main_no main_techmes(struct_800EB670 *arg0) {
    OSMesgQueue sp20;
    OSMesg sp38[8];
    struct_800FAF98_unk_64 sp58;
    s32 temp_v1_3;
    s32 temp_v1_5;
    s32 var_a0;
    bool var_s3;
    struct_800F3E50 *temp_s2;
    u8 temp_s1;

    var_s3 = true;
    osCreateMesgQueue(&sp20, sp38, ARRAY_COUNT(sp38));
    func_8002A184(arg0, &sp58, &sp20);
    dm_game_init_heap();
    temp_s2 = watchGame;

    dm_game_init_static();
    heapTop = init_menu_bg(heapTop, false);
    msgWnd_init2(&temp_s2->messageWnd, &heapTop, 0x1000, 0x12, 0x10, 0x34, 0x22);
    msgWnd_addStr(&temp_s2->messageWnd, EndingLastMessage);
    temp_s1 = evs_seqence;
    temp_s2->messageWnd.unk_20 = 1;
    temp_s2->messageWnd.unk_24 = 1;
    evs_seqence = 0;
    dm_game_init(false);
    evs_seqence = temp_s1;
    dm_seq_play_in_game(0x17);

    while (var_s3) {
        osRecvMesg(&sp20, NULL, 1);
        joyProcCore();

        switch (temp_s2->unk_9AC) {
            case 0x0:
                if (temp_s2->unk_9B0 == 0xFF) {
                    temp_s2->unk_9AC = 1;
                } else {
                    temp_v1_3 = temp_s2->unk_9B0 + 4;
                    var_a0 = 0xFF;
                    if (temp_v1_3 <= 0xFF) {
                        var_a0 = temp_v1_3;
                    }
                    temp_s2->unk_9B0 = var_a0;
                }
                break;

            case 0x1:
                if (msgWnd_isEnd(&temp_s2->messageWnd)) {
                    temp_s2->unk_9AC++;
                } else {
                    msgWnd_update(&temp_s2->messageWnd);
                }
                break;

            case 0x2:
                if (gControllerPressedButtons[main_joy[0]] & ALL_BUTTONS) {
                    temp_s2->unk_9AC = 3;
                }
                break;

            case 0x3:
                if (temp_s2->unk_9B0 == 0) {
                    var_s3 = false;
                } else {
                    temp_v1_5 = temp_s2->unk_9B0 - 4;
                    temp_s2->unk_9B0 = (temp_v1_5 & (~temp_v1_5 >> 0x1F));
                }
                break;
        }

        dm_audio_update();
        graphic_no = GRAPHIC_NO_6;
    }

    graphic_no = GRAPHIC_NO_0;
    dm_audio_stop();

    while (!dm_audio_is_stopped() || (pendingGFX != 0)) {
        osRecvMesg(&sp20, NULL, 1);
        dm_audio_update();
    }

    func_8002A1DC(arg0, &sp58);
    return MAIN_NO_3;
}

void graphic_techmes(void) {
    struct_800F3E50 *temp_s1 = watchGame;
    UNK_TYPE sp28;
    UNK_TYPE sp2C;

    gGfxHead = gGfxGlist[gfx_gtask_no];
    sp28 = dm_get_mtx_buf();
    sp2C = dm_get_vtx_buf();
    F3RCPinitRtn();
    F3ClearFZRtn(false);

    gDPSetEnvColor(gGfxHead++, 0, 0, 0, 255);
    gDPSetPrimColor(gGfxHead++, 0, 0, 255, 255, 255, 255);

    draw_menu_bg(&gGfxHead, 0, -0x78);

    dm_draw_KaSaMaRu(&gGfxHead, &sp28, &sp2C, msgWnd_isSpeaking(&temp_s1->messageWnd), 0xC8, 0x80, 1, 0xFFU);
    msgWnd_draw(&temp_s1->messageWnd, &gGfxHead);
    if (temp_s1->unk_9AC == 2) {
        push_any_key_draw(128, 192);
    }

    FillRectRGBA(&gGfxHead, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, 0, 255 - temp_s1->unk_9B0);

    temp_s1->unk_424++;

    gDPFullSync(gGfxHead++);
    gSPEndDisplayList(gGfxHead++);

    osWritebackDCacheAll();
    gfxTaskStart(&B_800FAE80[gfx_gtask_no], gGfxGlist[gfx_gtask_no], (gGfxHead - gGfxGlist[gfx_gtask_no]) * sizeof(Gfx),
                 0, OS_SC_SWAPBUFFER);
}

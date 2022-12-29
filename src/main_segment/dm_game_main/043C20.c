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

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/043C20", D_800B22B0);

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

extern const u16 D_800B2294[][4];
extern const u8 D_800B22AC[];
extern const u8 D_800B22B0[];
extern const f32 RO_800B1C80[];

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
            watchGameP->unk_3C8 = RO_800B1C80[game_state_data->unk_16C];
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
    func_80060E10();

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
        temp_s0_3[i].unk_008 = D_800B22AC[var_s4];
        temp_s0_3[i].unk_00A = D_800B22B0[var_s4];
        temp_s0_3[i].unk_006 = D_800B2294[j][i];
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

const u32 rodataPadding_800B22D4 = 0;

#if 0
? RecWritingMsg_init(s8 *, struct_80124610 **, s32);     /* extern */
? animeState_load(s8 *, struct_80124610 **, s32);     /* extern */
? animeState_set(s8 *, ?);                           /* extern */
? animeSmog_init(s8 *, s8 *);                        /* extern */
? animeSmog_load(s8 *, struct_80124610 **);          /* extern */
? func_80062B84(s8 *);                              /* extern */
? func_8006A938(?);                                 /* extern */
? replay_record_init_buffer(struct_80124610 **);                /* extern */
? replay_record_init(u8);                                /* extern */
extern ? evs_mem_data;
extern ? B_800EF608;
extern u32 evs_gamesel;
extern u8 evs_select_name_no;
extern u8 B_8012372C;
extern ? B_8012374C;
extern ? B_8012374F;
extern ? B_80123790;
extern s8 B_80123794;
extern s32 B_8012386C;
extern u8 evs_playcnt;
extern s8 evs_story_flg;
extern s32 D_80088414;
extern s8 D_800A8AD0;

/**
 * Original name: dm_game_init_static
 */
void dm_game_init_static(void) {
    s32 temp_a2;
    s32 temp_a2_2;
    s32 temp_a2_3;
    s32 temp_v0_3;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 var_a0_4;
    s32 var_a0_5;
    s32 var_a0_6;
    s32 var_s0;
    s32 var_s0_2;
    s32 var_s0_3;
    s32 var_s1;
    s32 var_s1_10;
    s32 var_s1_11;
    s32 var_s1_12;
    s32 var_s1_13;
    s32 var_s1_3;
    s32 var_s1_4;
    s32 var_s1_5;
    s32 var_s1_6;
    s32 var_s1_7;
    s32 var_s1_8;
    s32 var_s1_9;
    s32 var_s2;
    s32 var_s2_3;
    s32 var_v1_2;
    s8 *temp_s0;
    s8 *var_a0;
    s8 *var_a0_3;
    s8 *var_s2_2;
    s8 *var_s4;
    s8 *var_v0;
    s8 *var_v0_2;
    s8 *var_v1;
    struct_800F3E50 *temp_s3;
    struct_800F3E50 *var_a0_2;
    u16 temp_v0;
    u32 var_s1_2;
    u8 temp_v1_3;
    void *temp_a1;
    void *temp_v0_2;

    temp_s3 = watchGame;
    temp_s3->unk_3B0 = 0;
    temp_s3->unk_878 = 0x7F;
    temp_s3->unk_430 = tiLoadTexData(&heapTop, D_8000E9B0, D_8000E9B4);
    temp_s3->unk_444 = tiLoadTexData(&heapTop, D_8000E9D8, D_8000E9DC);
    if (main_no != 5) {
        temp_s3->unk_448 = tiLoadTexData(&heapTop, D_8000EA40, D_8000EA44);
    }
    temp_s3->unk_884 = (struct_80124610 *) heapTop;
    var_s1 = 1;
    var_v1 = &temp_s3->unk_000[4];
    heapTop = DecompressRomToRam(D_8000E9E0, heapTop, D_8000E9E4 - D_8000E9E0);
    do {
        var_v1->unk_8AC = 0;
        var_s1 -= 1;
        var_v1 -= 4;
    } while (var_s1 >= 0);
    temp_s3->unk_394 = 0;
    temp_s3->unk_398 = 1;
    temp_s3->unk_898 = 2;
    func_8006A938(0);
    temp_s3->unk_9AC = 0;
    temp_s3->unk_9B0 = 0;
    temp_s3->unk_9B4 = 0;
    temp_s3->unk_9B8 = 0;
    replay_record_init_buffer(&heapTop);
    var_s1_2 = 0;
    var_s0 = 0x9D0;
    replay_record_init(evs_playcnt);
    do {
        func_80062B84(&temp_s3->unk_000[var_s0]);
        var_s1_2 += 1;
        var_s0 += 0x2C;
    } while (var_s1_2 < 2U);
    msgWnd_init2((struct_80124610 *) &temp_s3->unk_000[0xA28], &heapTop, 0x100, 0xA, 5, 0, 0);
    temp_a2 = temp_s3->unk_A70 * 2;
    temp_s3->unk_A50 = (s32) ((s32) (0x140 - (temp_s3->unk_A64 * 0x14)) >> 1);
    temp_s3->unk_A54 = (s32) ((s32) (0xF0 - temp_a2) >> 1);
    RecWritingMsg_init(&temp_s3->unk_000[0xAD8], &heapTop, temp_a2);
    switch (evs_gamesel) {                           /* switch 1 */
    case 0x0:                                       /* switch 1 */
        temp_a1 = (evs_select_name_no * 0xD0) + &evs_mem_data;
        if (evs_select_name_no == 8) {
        case 0x4:                                   /* switch 1 */
            D_80088414 = 0xDD18;
        } else {
            switch (*evs_gamemode) {                  /* switch 3; irregular */
            case 0x0:                               /* switch 3 */
                D_80088414 = (temp_a1 + (B_8012372C * 8))->unk_4C;
                break;
            case 0x2:                               /* switch 3 */
                D_80088414 = (temp_a1 + (B_8012386C * 8))->unk_64;
                break;
            case 0x3:                               /* switch 3 */
                D_80088414 = (temp_a1 + (B_8012386C * 0xC))->unk_7C;
                break;
            }
        }
block_23:
        switch (evs_gamesel) {                       /* switch 2 */
        case 0x0:                                   /* switch 2 */
        case 0x4:                                   /* switch 2 */
            temp_s3->unk_898 = 1;
            animeState_load(&B_80123794, &heapTop, 0xF);
            animeState_set(&B_80123794, 2);
            var_s1_3 = 0;
            temp_s3->unk_438 = tiLoadTexData(&heapTop, gRomOffset_N64WaveTables_Start.unk_180, gRomOffset_N64WaveTables_Start.unk_184);
            var_s2 = 0x44C;
            temp_s3->unk_434 = tiLoadTexData(&heapTop, gRomOffset_N64WaveTables_Start.unk_198, gRomOffset_N64WaveTables_Start.unk_19C);
            do {
                animeState_load(&temp_s3->unk_000[var_s2], &heapTop, var_s1_3 + 0x10);
                var_s1_3 += 1;
                var_s2 += 0x40;
            } while (var_s1_3 < 3);
            animeSmog_load(&temp_s3->unk_000[0x50C], &heapTop);
            var_s1_4 = 1;
            var_s0_2 = 0x630;
            do {
                animeSmog_init(&temp_s3->unk_000[var_s0_2], &temp_s3->unk_000[0x50C]);
                var_s1_4 += 1;
                var_s0_2 += 0x124;
            } while (var_s1_4 < 3);
            temp_s0 = &temp_s3->unk_000[0x91C];
            msgWnd_init2((struct_80124610 *) temp_s0, &heapTop, 0x1000, 0x14, 0xF, 0x28, 0xF);
            temp_s3->unk_940 = 1;
            msgWnd_addStr((struct_80124610 *) temp_s0, &D_800A8AD0);
            msgWnd_skip((struct_80124610 *) temp_s0);
            temp_s3->unk_93C = 1;
            temp_s3->unk_938 = 0;
            heapTop = init_coffee_break(heapTop);
            return;
        case 0x1:                                   /* switch 2 */
        case 0x3:                                   /* switch 2 */
        case 0x5:                                   /* switch 2 */
            var_s1_5 = 0;
            var_s2_2 = &B_80123794;
            var_s0_3 = 0;
            var_a0 = &B_80123794;
            do {
                temp_a2_2 = *(&B_80123790 + var_s0_3);
                var_s2_2 += 0x3C4;
                var_s0_3 += 0x3C4;
                var_s1_5 += 1;
                animeState_load(var_a0, &heapTop, temp_a2_2);
                var_a0 = var_s2_2;
            } while (var_s1_5 < 2);
            var_s1_6 = 1;
            if (evs_story_flg == 0) {
                var_v0 = &temp_s3->unk_000[4];
                do {
                    var_v0->unk_8B4 = 0;
                    var_s1_6 -= 1;
                    var_v0 -= 4;
                } while (var_s1_6 >= 0);
                var_s1_7 = 0;
                if (evs_gamesel == 1) {
                    var_a0_2 = temp_s3;
                    do {
                        temp_v0 = *(&B_800EF608 + ((&evs_select_name_no)[var_s1_7] * 0xD0));
                        var_s1_7 += 1;
                        var_a0_2->unk_8B4 = (s32) temp_v0;
                        var_a0_2 += 4;
                    } while (var_s1_7 < 2);
                }
            }
            temp_s3->unk_438 = tiLoadTexData(&heapTop, gRomOffset_N64WaveTables_Start.unk_180, gRomOffset_N64WaveTables_Start.unk_184);
            temp_s3->unk_43C = tiLoadTexData(&heapTop, gRomOffset_N64WaveTables_Start.unk_188, gRomOffset_N64WaveTables_Start.unk_18C);
            return;
        case 0x2:                                   /* switch 2 */
        case 0x6:                                   /* switch 2 */
            var_s4 = &B_80123794;
            var_s1_8 = 0;
            temp_s3->unk_438 = tiLoadTexData(&heapTop, gRomOffset_N64WaveTables_Start.unk_180, gRomOffset_N64WaveTables_Start.unk_184);
            var_s2_3 = 0;
            temp_s3->unk_440 = tiLoadTexData(&heapTop, gRomOffset_N64WaveTables_Start.unk_190, gRomOffset_N64WaveTables_Start.unk_194);
            var_a0_3 = &B_80123794;
            do {
                temp_a2_3 = *(&B_80123790 + var_s2_3);
                var_s4 += 0x3C4;
                var_s2_3 += 0x3C4;
                var_s1_8 += 1;
                animeState_load(var_a0_3, &heapTop, temp_a2_3);
                var_a0_3 = var_s4;
            } while (var_s1_8 < 4);
            var_s1_9 = 3;
            var_v0_2 = &temp_s3->unk_000[0xC];
            do {
                var_v0_2->unk_8CC = 0;
                var_s1_9 -= 1;
                var_v0_2 -= 4;
            } while (var_s1_9 >= 0);
            var_s1_10 = 0;
            var_a0_4 = 0;
            do {
                temp_v0_2 = (*(&B_8012374F + var_a0_4) * 4) + temp_s3;
                var_s1_10 += 1;
                temp_v0_2->unk_8CC = (s32) (temp_v0_2->unk_8CC + 1);
                var_a0_4 += 0x3C4;
            } while (var_s1_10 < 4);
            temp_s3->unk_8BC = 0;
            var_s1_11 = 0;
            var_v1_2 = 0;
            do {
                var_s1_11 += 1;
                if (*(&B_8012374C + var_v1_2) == 0) {
                    temp_s3->unk_8BC = (s32) (temp_s3->unk_8BC + 1);
                }
                var_v1_2 += 0x3C4;
            } while (var_s1_11 < 4);
            temp_v1 = temp_s3->unk_8CC;
            if (temp_v1 != 1) {
                var_s1_12 = 0;
                goto block_56;
            }
            temp_v0_3 = temp_s3->unk_8D0;
            var_s1_12 = 0;
            if (temp_v0_3 == temp_v1) {
                temp_v1_2 = temp_s3->unk_8D4;
                if (temp_v1_2 == temp_v0_3) {
                    if (temp_s3->unk_8D8 == temp_v1_2) {
                        temp_s3->unk_8C0 = 0;
                        return;
                    }
                    goto block_57;
                }
            }
block_56:
block_57:
            var_a0_5 = 0;
            temp_s3->unk_8C0 = 1;
            temp_s3->unk_8C8 = 0;
            temp_s3->unk_8C4 = 0;
            do {
                if (*(&B_8012374F + var_a0_5) == 0) {
                    temp_s3->unk_8C4 = (s32) (temp_s3->unk_8C4 | (1 << var_s1_12));
                }
                var_s1_12 += 1;
                var_a0_5 += 0x3C4;
            } while (var_s1_12 < 4);
            var_s1_13 = 0;
            var_a0_6 = 0;
            do {
                temp_v1_3 = *(&B_8012374F + var_a0_6);
                if (temp_v1_3 == 1) {
                    temp_s3->unk_8C8 = (s32) (temp_s3->unk_8C8 | (temp_v1_3 << var_s1_13));
                }
                var_s1_13 += 1;
                var_a0_6 += 0x3C4;
            } while (var_s1_13 < 4);
        default:                                    /* switch 1 */
        default:                                    /* switch 2 */
            return;
        }
        break;
    case 0x1:                                       /* switch 1 */
    case 0x2:                                       /* switch 1 */
    case 0x3:                                       /* switch 1 */
    case 0x5:                                       /* switch 1 */
    case 0x6:                                       /* switch 1 */
        if (evs_story_flg == 0) {
            D_80088414 = 0;
        }
        goto block_23;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/043C20", dm_game_init_static);
#endif

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

#include "ultra64.h"
#include "include_asm.h"
#include "macros_defines.h"
#include "unknown_structs.h"
#include "main_segment_functions.h"
#include "main_segment_variables.h"

/**
 * Original name: main11
 */
enum_main_no main11(void) {
    enum_main_no ret = MAIN_NO_3;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(game_state_data); i++) {
        game_state_data[i].unk_026 = 0xA;
        game_state_data[i].unk_02C = 1;
        game_state_data[i].unk_090 = i;
        game_state_data[i].unk_04B = i;
        game_state_data[i].unk_04C = 0;
        game_state_data[i].unk_04D = i;
        game_state_data[i].unk_04E = 1;
        game_state_data[i].unk_16C = 1;
    }

    B_800FAE79 = 8;
    B_800FAE78[0] = 8;

    switch (EepRom_Init()) {
        case 0x2:
            EepRom_InitFirst(0, 0);
            break;

        case 0x5:
            ret = MAIN_NO_10;
            break;

        default:
            break;
    }

    return ret;
}

/**
 * Original name: adjust_story_ai
 */
INCLUDE_ASM("asm/nonmatchings/main_segment/main1x", adjust_story_ai);

INCLUDE_RODATA("asm/nonmatchings/main_segment/main1x", D_800ACE1C);

INCLUDE_RODATA("asm/nonmatchings/main_segment/main1x", D_800ACE28);

INCLUDE_RODATA("asm/nonmatchings/main_segment/main1x", D_800ACE2C);

INCLUDE_RODATA("asm/nonmatchings/main_segment/main1x", D_800ACE4C);

INCLUDE_RODATA("asm/nonmatchings/main_segment/main1x", D_800ACE5C);

INCLUDE_RODATA("asm/nonmatchings/main_segment/main1x", D_800ACE70);

INCLUDE_RODATA("asm/nonmatchings/main_segment/main1x", D_800ACE78);

INCLUDE_RODATA("asm/nonmatchings/main_segment/main1x", D_800ACE84);

/**
 * Original name: main12
 */
#if 0
extern s8 D_80088409;
extern s8 D_8008840A;
extern u8 D_800ACE1C[];
extern u8 D_800ACE28[];
extern u8 D_800ACE2C[][0xA];
extern s8 D_800ACE4C[];
extern u8 D_800ACE5C[][0xA];
extern s8 D_800ACE70[][4];
extern u8 D_800ACE78[][4];
extern u8 D_800ACE84[];
extern s8 evs_story_flg;

__asm__(".section .text\n");
enum_main_no main12() {
    struct_80123700 *ptr;
    s32 arg1;
    s32 arg2;
    s32 temp_a3;
    s32 temp_v1;
    s32 var_a1_2;
    s32 i;

    evs_playcnt = D_800ACE84[evs_gamesel];

    switch (evs_gamesel) {
        case ENUM_EVS_GAMESEL_0:
            game_state_data[0].unk_04C = 0;
            evs_story_flg = 0;
            break;

        case ENUM_EVS_GAMESEL_1:
            evs_story_flg = 0;

            for (i = 1; i >= 0; i--) {
                ptr = &game_state_data[i];
                ptr->unk_04C = 0;
            }
            break;

        case ENUM_EVS_GAMESEL_2:
            for (i = 0; i < 4; i++) {
                game_state_data[i].unk_04D = D_800ACE4C[game_state_data[i].unk_090];
            }
            break;

        case ENUM_EVS_GAMESEL_3:
            if (evs_story_flg != 0) {
                temp_a3 = (story_proc_no >= 0xC);
                ptr = game_state_data;
                for (i = 0; i < 4; i++) {
                    var_a1_2 = 2;
                    if (D_8008840A < 3) {
                        var_a1_2 = D_8008840A;
                    }
                    ptr[i].unk_026 = D_800ACE2C[var_a1_2][D_80088409];
                    ptr[i].unk_02C = 1;
                    ptr[i].unk_090 = D_800ACE5C[temp_a3][D_80088409];
                    ptr[i].unk_04D = D_800ACE4C[ptr[i].unk_090];
                    ptr[i].unk_16C = var_a1_2;
                    ptr[i].unk_04C = 1;
                    ptr[i].unk_04E = var_a1_2;
                    ptr[i].unk_04F = D_800ACE78[var_a1_2][i];
                }

                if ((D_8008840A > 0) && (D_80088409 == 7)) {

                    evs_gamesel = ENUM_EVS_GAMESEL_2;
                    evs_playcnt = 4;

                    for (i = 0; i < 4; i++) {
                        ptr = game_state_data;

                        temp_v1 = D_800ACE70[temp_a3][i];
                        ptr[i].unk_04D = D_800ACE4C[temp_v1];
                        ptr[i].unk_090 = temp_v1;
                        if (D_8008840A < 3) {
                            ptr[i].unk_04E = 0;
                        }
                    }
                } else {
                    ptr = game_state_data;
                    evs_playcnt = 2;
                    ptr->unk_090 = temp_a3;
                }
                ptr = game_state_data;

                ptr->unk_04C = 0;
                adjust_story_ai();

                evs_seqnumb = D_800ACE1C[D_80088409];
                evs_seqence = 1;
            } else {
                ptr = game_state_data;

                ptr[1].unk_04D = D_800ACE4C[ptr[1].unk_090];
                ptr[0].unk_04C = 0;
                ptr[1].unk_04C = 1;
            }
            break;

        case ENUM_EVS_GAMESEL_4:
            evs_playcnt = 1;
            evs_game_time = 0;
            D_8008840E = 0;
            game_state_data[0].unk_04D = D_800ACE4C[0];
            game_state_data[0].unk_000 = 0;
            game_state_data[0].unk_04B = 0;
            game_state_data[0].unk_04C = 1;
            game_state_data[0].unk_04E = 1;
            game_state_data[0].unk_026 = 0xA;
            game_state_data[0].unk_02C = 1;
            game_state_data[0].unk_090 = 0;
            evs_seqence = 1;

            evs_seqnumb = D_800ACE28[rand() & 2];
            break;

        case ENUM_EVS_GAMESEL_5:
            evs_playcnt = 2;
            evs_story_flg = 0;
            D_8008840E = 0;
            for (i = 0; i < 2; i++) {
                B_800FAE78[i] = 8;
                ptr = game_state_data;

                do {
                    game_state_data[i].unk_090 = genrand(0xD);

                    arg2 = 0;
                    for (arg1 = 0; arg1 < 2; arg1++) {
                        if (i != arg1) {
                            arg2 += game_state_data[i].unk_090 == game_state_data[arg1].unk_090;
                        }
                    }
                } while (arg2 != 0);

                game_state_data[i].unk_04D = D_800ACE4C[game_state_data[i].unk_090];
                game_state_data[i].unk_04B = i;
                game_state_data[i].unk_000 = 0;
                game_state_data[i].unk_04C = 1;
                game_state_data[i].unk_04E = 1;
                game_state_data[i].unk_02C = 1;
                game_state_data[i].unk_026 = 0xA;
            }

            evs_seqence = 1;
            evs_seqnumb = D_800ACE28[rand() & 2];
            break;

        case ENUM_EVS_GAMESEL_6:
            evs_playcnt = 4;
            evs_story_flg = 0;
            D_8008840E = 0;
            for (i = 0; i < 4; i++) {
                do {
                    game_state_data[i].unk_090 = genrand(0xD);

                    arg2 = 0;
                    for (arg1 = 0; arg1 < 4; arg1++) {
                        if (i != arg1) {
                            arg2 += game_state_data[i].unk_090 == game_state_data[arg1].unk_090;
                        }
                    }
                } while (arg2 != 0);

                game_state_data[i].unk_04D = D_800ACE4C[game_state_data[i].unk_090];
                game_state_data[i].unk_04C = 1;
                game_state_data[i].unk_04E = 1;
                game_state_data[i].unk_02C = 1;
                game_state_data[i].unk_000 = 0;
                game_state_data[i].unk_04B = i;
                game_state_data[i].unk_04F = i;
                game_state_data[i].unk_026 = 0xA;
            }
            evs_seqence = 1;
            evs_seqnumb = D_800ACE28[rand() & 2];
            break;
    }

    return MAIN_NO_5;
}
#else
INCLUDE_ASM("asm/nonmatchings/main_segment/main1x", main12);
#endif

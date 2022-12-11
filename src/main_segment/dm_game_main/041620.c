#include "ultra64.h"
#include "include_asm.h"
#include "macros_defines.h"
#include "unknown_structs.h"
#include "main_segment_functions.h"
#include "main_segment_variables.h"

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/041620", D_800B2160);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/041620", D_800B2168);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/041620", D_800B2170);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/041620", D_800B2178);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/041620", D_800B2180);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/041620", D_800B2184);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/041620", D_800B2188);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/041620", D_800B218C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/041620", D_800B21D0);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/041620", func_8006B270);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/041620", func_8006B8E0);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/041620", func_8006BBEC);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/041620", func_8006BC5C);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/041620", func_8006BD00);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/041620", dm_draw_KaSaMaRu);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/041620", func_8006C1D0);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/041620", func_8006C580);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/041620", func_8006C6FC);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/041620", func_8006C88C);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/041620", func_8006D0E8);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/041620", dm_make_key);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/041620", key_control_main);

void func_8006D620(void) {
    s32 i;
    struct_80123700 *ptr;

    if (D_800A6FC4 == 0) {
        return;
    }

    switch (evs_gamesel) {
        case ENUM_EVS_GAMESEL_1:
        case ENUM_EVS_GAMESEL_3:
        case ENUM_EVS_GAMESEL_5:
            for (i = 0; i < 2; i++) {
                ptr = &game_state_data[i];

                if (((ptr->unk_04C == 1) || (((ptr->unk_04C != 1) && (i == 0)) && (D_80088508 >= 0))) && (game_state_data[i].unk_020 == 1)) {
                    func_8002EFF0(&game_state_data[i]);
                }
            }
            break;

        case ENUM_EVS_GAMESEL_2:
        case ENUM_EVS_GAMESEL_6:
            for (i = 0; i < 4; i++) {
                ptr = &game_state_data[i];

                if (((ptr->unk_04C == 1) || (((ptr->unk_04C != 1) && (i == 0)) && (D_80088508 >= 0))) && (game_state_data[i].unk_020 == 1)) {
                    func_8002EFF0(&game_state_data[i]);
                }
            }
            break;

        case ENUM_EVS_GAMESEL_0:
        case ENUM_EVS_GAMESEL_4:
            if ((game_state_data->unk_04C == 1) || (D_80088508 >= 0)) {
                func_8002EFF0(&game_state_data[0]);
            }
            break;

        default:
            break;
    }
}

void dm_effect_make(void) {
    struct_800F3E50 *temp = watchGame;
    s32 i;

    temp->unk_424++;
    temp->unk_394 = CLAMP(temp->unk_394 + temp->unk_398, 0, 20);

    for (i = 0; i < evs_playcnt; i++) {
        if (game_state_data[i].unk_020 == 1) {
            if ((temp->unk_3C4 != 0) && (evs_game_time <= 0x57E03)) {
                evs_game_time++;
            }
            break;
        }
    }
}

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/041620", D_800B2294);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/041620", D_800B22AC);

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

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/041620", func_8006BDFC);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/041620", func_8006C1D0);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/041620", func_8006C580);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/041620", func_8006C6FC);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/041620", func_8006C88C);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/041620", func_8006D0E8);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/041620", dm_make_key);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/041620", key_control_main);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/041620", func_8006D620);

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

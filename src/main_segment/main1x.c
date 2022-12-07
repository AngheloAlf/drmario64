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
    B_800FAE78 = 8;

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
INCLUDE_ASM("asm/nonmatchings/main_segment/main1x", main12);

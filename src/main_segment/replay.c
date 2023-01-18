/**
 * Original filename: replay.c
 */

#include "ultra64.h"
#include "include_asm.h"
#include "macros_defines.h"
#include "unknown_structs.h"
#include "unk.h"

INCLUDE_ASM("asm/us/nonmatchings/main_segment/replay", func_8007E260);

INCLUDE_ASM("asm/us/nonmatchings/main_segment/replay", replay_record_init_buffer);

INCLUDE_ASM("asm/us/nonmatchings/main_segment/replay", replay_record_init);

INCLUDE_ASM("asm/us/nonmatchings/main_segment/replay", replay_record);

INCLUDE_ASM("asm/us/nonmatchings/main_segment/replay", replay_play_init);

INCLUDE_ASM("asm/us/nonmatchings/main_segment/replay", replay_play);

INCLUDE_ASM("asm/us/nonmatchings/main_segment/replay", func_8007E760);

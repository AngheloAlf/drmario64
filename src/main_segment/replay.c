/**
 * Original filename: replay.c
 */

#include "libultra.h"
#include "include_asm.h"
#include "macros_defines.h"
#include "unknown_structs.h"
#include "unk.h"

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/replay", func_8007E260);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/replay", replay_record_init_buffer);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/replay", replay_record_init);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/replay", replay_record);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/replay", replay_play_init);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/replay", replay_play);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/replay", func_8007E760);
#endif

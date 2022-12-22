/**
 * Originally part of dm_virus_init.c
 */

#include "ultra64.h"
#include "include_asm.h"
#include "macros_defines.h"
#include "unknown_structs.h"
#include "unk.h"
#include "boot_functions.h"
#include "boot_variables.h"
#include "main_segment_functions.h"
#include "main_segment_variables.h"

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_virus_init/035AB0", D_800B1BA0);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_virus_init/035AB0", D_800B1BBC);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_virus_init/035AB0", D_800B1BC8);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_virus_init/035AB0", D_800B1BCC);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_virus_init/035AB0", func_8005F700);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_virus_init/035AB0", func_8005FC50);

void func_8005FC6C(struct_8005FC6C_arg0 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    bzero(arg0, sizeof(struct_8005FC6C_arg0));
    arg0->unk_000 = arg1;
    arg0->unk_004 = arg2;
    arg0->unk_008 = arg3;
}

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_virus_init/035AB0", _makeFlash_checkOrdre);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_virus_init/035AB0", func_8005FE68);

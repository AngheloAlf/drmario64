#include "ultra64.h"
#include "include_asm.h"
#include "macros_defines.h"
#include "unknown_structs.h"
#include "unk.h"
#include "boot_functions.h"
#include "boot_variables.h"
#include "main_segment_functions.h"
#include "main_segment_variables.h"


INCLUDE_RODATA("asm/nonmatchings/main_segment/0362B0", D_800B1BD0);

struct _m2c_stack_func_8005FF00 {
    /* 0x000 */ char pad_0[0x10];
    /* 0x010 */ struct_8005FC6C_arg0 sp10;
    /* 0x304 */ char pad_304[8];
    /* 0x30C */ void *sp30C;
    /* 0x310 */ char pad_310[0x30];
};                                                  /* size = 0x340 */

INCLUDE_ASM("asm/nonmatchings/main_segment/0362B0", func_8005FF00);

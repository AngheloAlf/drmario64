/**
 * Original filename: lws.c
 */

#include "libultra.h"
#include "include_asm.h"
#include "macros_defines.h"
#include "unknown_structs.h"
#include "main_segment_functions.h"
#include "main_segment_variables.h"

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/lws", lws_anim);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/lws", lws_anim);
#endif

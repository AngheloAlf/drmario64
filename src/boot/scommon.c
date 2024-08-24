#include "lib/ultralib/include/PRinternal/controller.h"
#include "lib/ultralib/include/PRinternal/piint.h"
#include "lib/ultralib/include/PRinternal/osint.h"
#undef STACK

#include "attributes.h"
#include "alignment.h"
#include "macros_defines.h"

#include "boot_main.h"
#include "gzip.h"

ASM_BSS;

#if !SCOMMON_IN_COMMON
u32 bk BSS;

u32 __osBaseCounter BSS;

GzipFileDescriptor ofd BSS;

u32 __osBbRCountWraps BSS;
u32 __osBbLastRCount BSS;

u32 __osViIntrCount BSS;

u32 insize BSS;

size_t outcnt BSS;

u8 __osMaxControllers BSS;

u32 bb BSS;

OSTime __osCurrentTime BSS;

u32 hufts BSS;

s32 bytes_in BSS;

u32 __osBbLastVCount BSS;

s32 bytes_out BSS;

u8 __osContLastCmd BSS;

OSMesg __osEepromTimerMsg BSS;

u32 __osTimerCounter BSS;

u32 __osBbVCountWraps BSS;

u32 __osFinalrom BSS;

u32 inptr BSS;

GzipFileDescriptor ifd BSS;
#endif

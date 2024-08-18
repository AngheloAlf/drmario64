#define DECLARE_COMMON_SYMS 1

#include "attributes.h"
#include "alignment.h"
#include "macros_defines.h"

#include "lib/ultralib/src/io/controller.h"
#include "lib/ultralib/src/io/piint.h"
#include "lib/ultralib/src/os/osint.h"

#include "boot_main.h"
#include "gzip.h"

ASM_BSS;

u8 inbuf[INBUFSIZ] BSS;

#if VERSION_US || VERSION_GW
u32 bk BSS;

u32 __osBaseCounter BSS;
#endif

OSThread __osThreadSave;

#if VERSION_US || VERSION_GW
GzipFileDescriptor ofd BSS;
#endif

OSPifRam __osContPifRam ALIGNED(16) BSS;

OSPiHandle __Dom2SpeedParam ALIGNED(8) BSS;

STACK(gBootThreadStack, BOOT_STACK_SIZE) BSS;

OSMesg sPiMgrCmdBuff[SPIMGRCMDBUFF_LEN] BSS;

#if VERSION_US || VERSION_GW
u32 __osViIntrCount BSS;

u32 insize BSS;

size_t outcnt BSS;

u8 __osMaxControllers BSS;

u32 bb BSS;

OSTime __osCurrentTime BSS;

u32 hufts BSS;
#endif

OSPiHandle __CartRomHandle ALIGNED(8) BSS;

OSPifRam __osEepPifRam ALIGNED(16) BSS;

OSMesgQueue __osPiAccessQueue ALIGNED(8) BSS;

OSPiHandle __Dom1SpeedParam ALIGNED(8) BSS;

#if VERSION_US || VERSION_GW
s32 bytes_in BSS;

s32 bytes_out BSS;

u8 __osContLastCmd BSS;

OSMesg __osEepromTimerMsg BSS;
#endif

OSTimer __osBaseTimer BSS;

#if VERSION_US || VERSION_GW
u32 __osTimerCounter BSS;

/* Automatically generated and unreferenced pad */
u8 D_8001FB34[0x0C] BSS; // TODO
#endif

u8 D_8001FB40[0x2000] BSS; // TODO

OSTimer __osEepromTimer BSS;

#if VERSION_CN
#undef OS_NUM_EVENTS
#define OS_NUM_EVENTS 31
#endif
__OSEventState __osEventStateTab[OS_NUM_EVENTS] ALIGNED(8) BSS;

#if VERSION_US || VERSION_GW
u32 __osFinalrom BSS;

/* Automatically generated and unreferenced pad */
u8 D_80021BDC[0x04] BSS; // TODO
#endif

u8 window[WSIZE] BSS;

#if VERSION_US || VERSION_GW
u32 inptr BSS;
#endif

OSMesgQueue __osEepromTimerQ BSS ALIGNED(8);

#if VERSION_US || VERSION_GW
GzipFileDescriptor ifd BSS;
#endif

OSMesgQueue sPiMgrCmdQueue BSS;

OSMesgQueue __osSiAccessQueue ALIGNED(8) BSS;

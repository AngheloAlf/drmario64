#include "ultra64.h"
#include "macros_defines.h"

u8 B_80010E60[0x1B0] BSS;

u8 B_80011010[0x21B0] BSS;

u8 B_800131C0[0x2000] BSS;

u8 B_800151C0[0x18] BSS;

u8 B_800151D8[0x08] BSS;

u8 B_800151E0[0x4000] BSS;

/* pimgr */

u8 piThread[0x1B0] BSS;

u8 piThreadStack[0x1000] BSS;

u8 piEventQueue[0x18] BSS;

u8 piEventBuf[0x08] BSS;

/* pimgr */

u8 piAccessBuf[0x10] BSS;

u8 B_8001A3C0[0x04] BSS;

u8 B_8001A3C4[0x0C] BSS;

u8 B_8001A3D0[0x08] BSS;

u8 B_8001A3D8[0x04] BSS;

u8 B_8001A3DC[0x04] BSS;

u8 B_8001A3E0[0x08] BSS;

u8 B_8001A3E8[0x04] BSS;

u8 B_8001A3EC[0x04] BSS;

u8 B_8001A3F0[0x08] BSS;

u8 B_8001A3F8[0x04] BSS;

u8 B_8001A3FC[0x04] BSS;

u8 siAccessBuf[0x10] BSS;

u8 B_8001A410[0x08] BSS;

u8 viThread[0x1B0] BSS;

u8 D_8001A5C8[0x08] BSS;

u8 viThreadStack[0x1000] BSS;

u8 viEventQueue[0x18] BSS;

u8 viEventBuf[0x18] BSS;

u8 viRetraceMsg[0x18] BSS;

u8 viCounterMsg[0x18] BSS;

/* rand */

u8 sRandNext[0x10] BSS;

/*  */

u8 B_8001B640[0x2000] BSS;

u8 B_8001D640[0x04] BSS;

u8 __osBaseCounter[0x04] BSS;

u8 __osThreadSave[0x1B0] BSS;

u8 B_8001D7F8[0x08] BSS;

u8 __osContPifRam[0x38] BSS;

u8 B_8001D838[0x04] BSS;

u8 B_8001D83C[0x04] BSS;

u8 __Dom2SpeedParam[0x74] BSS;

u8 D_8001D8B4[0x0C] BSS;

u8 sBootThreadStack[0x2000] BSS;

u8 B_8001F8C0[0xC8] BSS;

u8 B_8001F988[0x04] BSS;

u8 B_8001F98C[0x04] BSS;

u8 B_8001F990[0x04] BSS;

u8 __osMaxControllers[0x04] BSS;

u8 B_8001F998[0x08] BSS;

u8 __osCurrentTime[0x08] BSS;

u8 B_8001F9A8[0x08] BSS;

/* cartrominit */

u8 __CartRomHandle[0x74] BSS;

u8 D_8001FA24[0x0C] BSS;

/* cartrominit */

u8 B_8001FA30[0x3C] BSS;

u8 B_8001FA6C[0x04] BSS;

u8 __osPiAccessQueue[0x18] BSS;

u8 __Dom1SpeedParam[0x74] BSS;

u8 B_8001FAFC[0x04] BSS;

u8 B_8001FB00[0x04] BSS;

u8 __osContLastCmd[0x04] BSS;

u8 __osEepromTimerMsg[0x08] BSS;

u8 __osBaseTimer[0x20] BSS;

u8 __osTimerCounter[0x2010] BSS;

u8 __osEepromTimer[0x20] BSS;

u8 __osEventStateTab[0x78] BSS;

u8 __osFinalrom[0x08] BSS;

u8 B_80021BE0[0x8000] BSS;

u8 B_80029BE0[0x08] BSS;

u8 __osEepromTimerQ[0x18] BSS;

u8 B_80029C00[0x08] BSS;

u8 B_80029C08[0x18] BSS;

u8 __osSiAccessQueue[0x20] BSS;

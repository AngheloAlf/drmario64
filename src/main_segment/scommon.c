#define DECLARE_COMMON_SYMS 1

#include "attributes.h"
#include "alignment.h"
#include "macros_defines.h"

#include "aiset.h"
#include "dm_virus_init.h"
#include "game_etc.h"
#include "graphic.h"
#include "nnsched.h"
#include "record.h"

#if VERSION_CN
#if VERSION_GW || VERSION_CN
u8 B_800CA1C0_cn[0x4] BSS; // TODO
#endif

u8 aiRootP[0x04] BSS; // TODO

u8 aiWall BSS; // TODO

s16 gfx_msg_no BSS; // TODO

#if VERSION_US
/* Automatically generated and unreferenced pad */
u8 D_800E9BB8[0x08] BSS; // TODO
#endif
#if VERSION_GW || VERSION_CN
/* Automatically generated and unreferenced pad */
u8 D_800EAA1C[0x4] BSS; // TODO
#endif




u8 success BSS; // TODO

/* Automatically generated and unreferenced pad */
// u8 D_800EA281[0x03] BSS; // TODO

s32 attack_sprite_idx BSS; // TODO

/* Automatically generated and unreferenced pad */
u8 D_800EA288[0x08] BSS; // TODO





u8 main_old[0x04] BSS; // TODO

u8 _menuMain_lastDepth[0x04] BSS; // TODO




u8 aiTEdgeCnt BSS; // TODO

/* Automatically generated and unreferenced pad */
u8 D_800EB660[0xF] ALIGNED(ALIGNOF(u8)) BSS; // TODO



/* Automatically generated and unreferenced pad */
u8 D_800EBCEC[0x04] BSS; // TODO

u8 main_no[0x04] BSS; // TODO

u8 gGfxHead[0x04] BSS; // TODO




/* Automatically generated and unreferenced pad */
u8 D_800EBD0C[0x04] BSS; // TODO

u8 PlayTime[0x04] BSS; // TODO

#if VERSION_GW || VERSION_CN
u8 B_800CA1F0_cn[0x4] BSS; // TODO
#endif

u8 aiNext[0x02] BSS; // TODO

u8 main_joy[0x04] ALIGNED(ALIGNOF(u8)) BSS; // TODO




u8 gfx_msg[0x02] BSS; // TODO



u8 gameBackup[0x08] BSS; // TODO





s32 attack_effect_idx BSS; // TODO

u8 diskrom_handle[0x04] BSS; // TODO

u8 fool_mode[0x04] BSS; // TODO

u16 joycur1 BSS; // TODO

u8 decide BSS; // TODO




u8 evs_gamesel[0x04] BSS; // TODO

/* Automatically generated and unreferenced pad */
u8 D_800EFCD4[0x0C] BSS; // TODO





u8 evs_playmax BSS; // TODO

/* Automatically generated and unreferenced pad */
// u8 D_800F1CE1[0x07] BSS; // TODO





u8 pObjectMtx[0x04] BSS; // TODO

/* Automatically generated and unreferenced pad */
u8 D_800F1DFC[0x04] BSS; // TODO



u16 joycur2 BSS; // TODO

/* Automatically generated and unreferenced pad */
// u8 D_800F1E22[0x0E] BSS; // TODO



s16 aiHiErB BSS; // TODO



u16 aiPriOfs BSS; // TODO

u8 aiRollFinal BSS; // TODO

/* Automatically generated and unreferenced pad */
// u8 D_800F3E35[0x03] BSS; // TODO




u8 watchGame[0x04] BSS; // TODO

u8 aiFlagCnt BSS; // TODO

u16 aiGoalX BSS; // TODO

#if VERSION_GW || VERSION_CN
NNScPerf *nnsc_perf_ptr BSS; // TODO
#endif

/* Automatically generated and unreferenced pad */
u8 D_800F3E58[0x04] BSS; // TODO

u8 watchMenu[0x04] BSS; // TODO

u8 B_800F3E60[0x04] BSS; // TODO






u8 link_joy[0x04] BSS; // TODO

u8 aiHiErY[0x02] BSS; // TODO






u8 watchManual[0x04] BSS; // TODO

u8 aiRootCnt[0x01] BSS; // TODO

/* Automatically generated and unreferenced pad */
// u8 D_800F4895[0x03] BSS; // TODO





NNScClient gfx_client BSS; // TODO

u8 joygam[0x08] BSS; // TODO

struct_gameGeom *gameGeom BSS; // TODO




#if VERSION_GW || VERSION_CN
u8 B_800CA26C_cn[0x4] BSS; // TODO
#endif

u8 MissRate[0x04] BSS; // TODO







u8 __muscontrol_flag[0x04] BSS; // TODO

u8 joyflg[0x08] BSS; // TODO

u8 aiYEdgeCnt BSS; // TODO

/* Automatically generated and unreferenced pad */
u8 D_800F6CE1[0x0F] ALIGNED(ALIGNOF(u8)) BSS; // TODO






#if VERSION_GW || VERSION_CN
s8 B_800CA281_cn BSS; // TODO
#endif

/* Automatically generated and unreferenced pad */
// u8 D_800F7486[0x02] BSS; // TODO

s32 s_hard_mode BSS; // TODO

u8 (*attack_sprite_address)[10][32 * 32 / 2] BSS; // TODO













u8 aiHiErR[0x04] BSS; // TODO

#if VERSION_GW || VERSION_CN
u8 B_800CA290_cn[0x4] BSS; // TODO
#endif

u32 gfx_gtask_no BSS; // TODO

#if VERSION_GW || VERSION_CN
NNScPerf *nnsc_perf_inptr BSS; // TODO
#endif

u8 aiSelCom BSS; // TODO

#if VERSION_GW || VERSION_CN
u8 B_800CA29B_cn BSS; // TODO
#endif

u8 joygmf[0x04] ALIGNED(ALIGNOF(u8)) BSS; // TODO

/* Automatically generated and unreferenced pad */
// u8 D_800FAD35[0x01] BSS; // TODO

u16 aiGoalY BSS; // TODO

u8 aipn BSS; // TODO

/* Automatically generated and unreferenced pad */
u8 D_800FAD39[0x07] ALIGNED(ALIGNOF(u8)) BSS; // TODO





u8 evs_select_name_no[0x02] BSS; // TODO

/* Automatically generated and unreferenced pad */
// u8 D_800FAE7A[0x06] BSS; // TODO









u8 aiSelSpeed BSS; // TODO

OSMesgQueue *sched_gfxMQ BSS; // TODO

u8 gAudio_800FAF98[0x04] BSS; // TODO

u16 aiHiEraseCtr BSS; // TODO









u8 aiMoveSF BSS; // TODO

/* Automatically generated and unreferenced pad */
// u8 D_800FB3A1[0x03] BSS; // TODO

u32 evs_game_time BSS; // TODO








/* Automatically generated and unreferenced pad */
u8 D_800FB668[0x08] BSS; // TODO








u8 evs_gamemode[0x04] BSS; // TODO

/* Automatically generated and unreferenced pad */
u8 D_801236F4[0x0C] BSS; // TODO







u8 B_800CA2C0_cn[2] BSS; // TODO

#endif

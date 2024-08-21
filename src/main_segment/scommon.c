#include "attributes.h"
#include "alignment.h"
#include "macros_defines.h"

#include "audio/music_driver.h"
#include "audio/sound.h"
#include "ai.h"
#include "aiset.h"
#include "bg_tasks.h"
#include "dm_manual_main.h"
#include "dm_game_main.h"
#include "dm_virus_init.h"
#include "game_etc.h"
#include "gamemap.h"
#include "graphic.h"
#include "joy.h"
#include "main.h"
#include "main1x.h"
#include "main_menu.h"
#include "nnsched.h"
#include "record.h"

ASM_BSS;

#if !SCOMMON_IN_COMMON
#ifdef NN_SC_PERF
u8 *B_800CA1C0_cn BSS; // TODO
#endif

f32 aiRootP BSS; // TODO

u8 aiWall BSS; // TODO

s16 gfx_msg_no BSS; // TODO




u8 success BSS; // TODO

s32 attack_sprite_idx BSS; // TODO



enum_main_no main_old BSS; // TODO

s32 _menuMain_lastDepth BSS; // TODO




u8 aiTEdgeCnt BSS; // TODO

enum_main_no main_no BSS; // TODO

Gfx* gGfxHead BSS; // TODO




/* Automatically generated and unreferenced pad */
u8 D_800EBD0C[0x04] BSS; // TODO

u32 PlayTime BSS; // TODO

#ifdef NN_SC_PERF
struct_801020E8_cn *B_800CA1F0_cn BSS; // TODO
#endif

u8 aiNext[0x02] BSS; // TODO

u8 main_joy[MAXCONTROLLERS] BSS; // TODO




s16 gfx_msg BSS; // TODO



struct_gameBackup *gameBackup[2] BSS; // TODO





s32 attack_effect_idx BSS; // TODO

u8 diskrom_handle[0x04] BSS; // TODO

bool fool_mode BSS; // TODO

u16 joycur1 BSS; // TODO

u8 decide BSS; // TODO




enum_evs_gamesel evs_gamesel BSS; // TODO



u8 evs_playmax BSS; // TODO



Mtx *pObjectMtx BSS; // TODO


u16 joycur2 BSS; // TODO



s16 aiHiErB BSS; // TODO



u16 aiPriOfs BSS; // TODO

u8 aiRollFinal BSS; // TODO



struct struct_watchGame *watchGame BSS; // TODO

u8 aiFlagCnt BSS; // TODO

u16 aiGoalX BSS; // TODO

#ifdef NN_SC_PERF
NNScPerf *nnsc_perf_ptr BSS; // TODO
#endif

/* Automatically generated and unreferenced pad */
u8 D_800F3E58[0x04] BSS; // TODO

struct_watchMenu *watchMenu BSS; // TODO

OSMesg B_800F3E60[1] BSS; // TODO






u8 link_joy[0x04] BSS; // TODO

s16 aiHiErY BSS; // TODO



u32 D_800F3E80 BSS; // TODO


struct struct_watchManual *watchManual BSS; // TODO

u8 aiRootCnt BSS; // TODO





NNScClient gfx_client BSS; // TODO

u16 joygam[MAXCONTROLLERS] BSS; // TODO

struct_gameGeom *gameGeom BSS; // TODO




#ifdef NN_SC_PERF
u8 B_800CA26C_cn[B_800CA26C_CN_ARR_LEN] BSS; // TODO
#endif

s32 MissRate BSS; // TODO







unsigned long __muscontrol_flag BSS; // TODO

u16 joyflg[MAXCONTROLLERS] BSS; // TODO

u8 aiYEdgeCnt BSS; // TODO





#ifdef NN_SC_PERF
s8 B_800CA281_cn BSS; // TODO
#endif

bool s_hard_mode BSS; // TODO

u8 (*attack_sprite_address)[10][32 * 32 / 2] BSS; // TODO













s16 aiHiErR BSS; // TODO

#ifdef NN_SC_PERF
struct_801020E8_cn *B_800CA290_cn BSS; // TODO
#endif

u32 gfx_gtask_no BSS; // TODO

#ifdef NN_SC_PERF
NNScPerf *nnsc_perf_inptr BSS; // TODO
#endif

u8 aiSelCom BSS; // TODO

#ifdef NN_SC_PERF
u8 B_800CA29B_cn BSS; // TODO
#endif

u8 joygmf[MAXCONTROLLERS] BSS; // TODO

u16 aiGoalY BSS; // TODO

u8 aipn BSS; // TODO





u8 evs_select_name_no[0x02] BSS; // TODO









s8 aiSelSpeed BSS; // TODO

OSMesgQueue *sched_gfxMQ BSS; // TODO

Audio_struct_800FAF98 *gAudio_800FAF98 BSS; // TODO

u16 aiHiEraseCtr BSS; // TODO









u8 aiMoveSF BSS; // TODO

u32 evs_game_time BSS; // TODO











enum_evs_gamemode evs_gamemode BSS; // TODO




u8 B_800CA2C0_cn[2] BSS; // TODO

#endif

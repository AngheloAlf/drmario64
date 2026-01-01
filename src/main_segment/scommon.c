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
u8 *B_800CA1C0_cn BSS;
#endif

f32 aiRootP BSS;

u8 aiWall BSS;

s16 gfx_msg_no BSS;

u8 success BSS;

s32 attack_sprite_idx BSS;

enum_main_no main_old BSS;

s32 _menuMain_lastDepth BSS;

u8 aiTEdgeCnt BSS;

enum_main_no main_no BSS;

Gfx *gGfxHead BSS;

/* Automatically generated and unreferenced pad */
s32 D_800EBD0C BSS;

u32 PlayTime BSS;

#ifdef NN_SC_PERF
struct_801020E8_cn *B_800CA1F0_cn BSS;
#endif

u8 aiNext[0x02] BSS;

u8 main_joy[MAXCONTROLLERS] BSS;

s16 gfx_msg BSS;

struct GameStateBackup *gameBackup[2] BSS;

s32 attack_effect_idx BSS;

OSPiHandle *diskrom_handle BSS;

bool fool_mode BSS;

u16 joycur1 BSS;

u8 decide BSS;

enum_evs_gamesel evs_gamesel BSS;

u8 evs_playmax BSS;

Mtx *pObjectMtx BSS;

u16 joycur2 BSS;

s16 aiHiErB BSS;

u16 aiPriOfs BSS;

u8 aiRollFinal BSS;

struct struct_watchGame *watchGame BSS;

u8 aiFlagCnt BSS;

u16 aiGoalX BSS;

#ifdef NN_SC_PERF
NNScPerf *nnsc_perf_ptr BSS;
#endif

/* Automatically generated and unreferenced pad */
s32 D_800F3E58 BSS;

SMenuAll *watchMenu BSS;

OSMesg B_800F3E60[1] BSS;

u8 link_joy[MAXCONTROLLERS] BSS;

s16 aiHiErY BSS;

u32 D_800F3E80 BSS;

struct struct_watchManual *watchManual BSS;

u8 aiRootCnt BSS;

NNScClient gfx_client BSS;

u16 joygam[MAXCONTROLLERS] BSS;

struct struct_gameGeom *gameGeom BSS;

#ifdef NN_SC_PERF
u8 B_800CA26C_cn[B_800CA26C_CN_ARR_LEN] BSS;
#endif

s32 MissRate BSS;

unsigned long __muscontrol_flag BSS;

u16 joyflg[MAXCONTROLLERS] BSS;

u8 aiYEdgeCnt BSS;

#ifdef NN_SC_PERF
s8 B_800CA281_cn BSS;
#endif

bool s_hard_mode BSS;

u8 (*attack_sprite_address)[10][32 * 32 / 2] BSS;

s16 aiHiErR BSS;

#ifdef NN_SC_PERF
struct_801020E8_cn *B_800CA290_cn BSS;
#endif

u32 gfx_gtask_no BSS;

#ifdef NN_SC_PERF
NNScPerf *nnsc_perf_inptr BSS;
#endif

u8 aiSelCom BSS;

#ifdef NN_SC_PERF
u8 B_800CA29B_cn BSS;
#endif

u8 joygmf[MAXCONTROLLERS] BSS;

u16 aiGoalY BSS;

u8 aipn BSS;

u8 evs_select_name_no[EVS_SELECT_NAME_NO_COUNT] BSS;

s8 aiSelSpeed BSS;

OSMesgQueue *sched_gfxMQ BSS;

Audio_struct_800FAF98 *gAudio_800FAF98 BSS;

u16 aiHiEraseCtr BSS;

u8 aiMoveSF BSS;

u32 evs_game_time BSS;

enum_evs_gamemode evs_gamemode BSS;

u8 B_800CA2C0_cn[2] BSS;
#endif

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

#if SCOMMON_IN_COMMON
#ifdef NN_SC_PERF
u8 *B_800CA1C0_cn BSS;
#endif

f32 aiRootP BSS;

u8 aiWall BSS;

s16 gfx_msg_no BSS;
#endif /* SCOMMON_IN_COMMON */

struct_ai_char_data ai_char_data[AI_CHAR_DATA_LEN] ALIGNED(0x10) BSS;

#if SCOMMON_IN_COMMON
u8 success BSS;

s32 attack_sprite_idx BSS;
#endif /* SCOMMON_IN_COMMON */

BgTasksManager sBgTasksManager_Manager ALIGNED(0x10) BSS;

#ifdef NN_SC_PERF
struct_801020E8_cn B_801020E8_cn[B_800CA26C_CN_ARR_LEN][B_801020E8_CN_ARR_ARR_LEN] BSS;
#endif

OSContPad B_800EB4D8[MAXCONTROLLERS] BSS;

#if SCOMMON_IN_COMMON
enum_main_no main_old BSS;

s32 _menuMain_lastDepth BSS;
#endif /* SCOMMON_IN_COMMON */

Unk_AIFEntry aiRecurData[GAME_MAP_ROWS + 1][GAME_MAP_COLUMNS + 2] BSS;

#if SCOMMON_IN_COMMON
u8 aiTEdgeCnt BSS;
#endif /* SCOMMON_IN_COMMON */

#if VERSION_US || VERSION_GW
ALIGNED(0x10)
#endif
NNSched B_800EB670 BSS;

#if SCOMMON_IN_COMMON
enum_main_no main_no BSS;

Gfx *gGfxHead BSS;
#endif /* SCOMMON_IN_COMMON */

u16 gControllerHoldButtons[MAXCONTROLLERS + 1] BSS;

#if VERSION_US || VERSION_GW
ALIGNED(ALIGNOF(u8))
#endif
u8 hei_data[HEI_WEI_DATA_LEN] BSS;

#if SCOMMON_IN_COMMON
/* Automatically generated and unreferenced pad */
s32 D_800EBD0C BSS;

u32 PlayTime BSS;

#ifdef NN_SC_PERF
struct_801020E8_cn *B_800CA1F0_cn BSS;
#endif

u8 aiNext[0x02] BSS;

#if VERSION_US || VERSION_GW
ALIGNED(ALIGNOF(u8))
#endif
u8 main_joy[MAXCONTROLLERS] BSS;
#endif /* SCOMMON_IN_COMMON */

OSThread gfxThread BSS;

OSMesg gfx_msgbuf[8] BSS;

GameMapCell game_map_data[4][GAME_MAP_ROWS * GAME_MAP_COLUMNS] BSS;

#if SCOMMON_IN_COMMON
s16 gfx_msg BSS;
#endif /* SCOMMON_IN_COMMON */

STACK(nnScGraphicsStack, NN_SC_STACKSIZE) BSS;

#if SCOMMON_IN_COMMON
struct GameStateBackup *gameBackup[2] BSS;
#endif /* SCOMMON_IN_COMMON */

u8 CapsMagazine[0x100] BSS;

#if SCOMMON_IN_COMMON
s32 attack_effect_idx BSS;

OSPiHandle *diskrom_handle BSS;

bool fool_mode BSS;

u16 joycur1 BSS;

u8 decide BSS;
#endif /* SCOMMON_IN_COMMON */

struct_evs_mem_data evs_mem_data[9] ALIGNED(0x10) BSS;

s32 _menuMain_lastSelect[8] BSS;

#if SCOMMON_IN_COMMON
enum_evs_gamesel evs_gamesel BSS;
#endif /* SCOMMON_IN_COMMON */

STACK(nnScStack, NN_SC_STACKSIZE) BSS;

#if SCOMMON_IN_COMMON
u8 evs_playmax BSS;
#endif /* SCOMMON_IN_COMMON */

Unk_AIFEntry aiFieldData[GAME_MAP_ROWS][GAME_MAP_COLUMNS] ALIGNED(8) BSS;

#if SCOMMON_IN_COMMON
Mtx *pObjectMtx BSS;
#endif /* SCOMMON_IN_COMMON */

s32 evs_default_name[8] ALIGNED(0x10) BSS;

#if SCOMMON_IN_COMMON
u16 joycur2 BSS;
#endif /* SCOMMON_IN_COMMON */

STACK(sGraphicStack, GRAPHIC_STACK_SIZE) BSS;

#if SCOMMON_IN_COMMON
s16 aiHiErB BSS;
#endif /* SCOMMON_IN_COMMON */

#ifdef NN_SC_PERF
NNScPerf nnsc_perf[NN_SC_PERF_NUM] ALIGNED(0x10) BSS;
#endif /* SCOMMON_IN_COMMON */

#if SCOMMON_IN_COMMON
u16 aiPriOfs BSS;

u8 aiRollFinal BSS;
#endif /* SCOMMON_IN_COMMON */

OSMesgQueue B_800F3E38 ALIGNED(8) BSS;

#if SCOMMON_IN_COMMON
struct struct_watchGame *watchGame BSS;

u8 aiFlagCnt BSS;

u16 aiGoalX BSS;

#ifdef NN_SC_PERF
NNScPerf *nnsc_perf_ptr BSS;
#endif

/* Automatically generated and unreferenced pad */
s32 D_800F3E58 BSS;

struct_watchMenu *watchMenu BSS;

OSMesg B_800F3E60[1] BSS;
#endif /* SCOMMON_IN_COMMON */

u16 gControllerPrevHoldButtons[MAXCONTROLLERS + 1] BSS;

#if VERSION_US || VERSION_GW
ALIGNED(ALIGNOF(u8))
#endif
u8 wid_data[HEI_WEI_DATA_LEN] BSS;

#if SCOMMON_IN_COMMON
u8 link_joy[MAXCONTROLLERS] BSS;

s16 aiHiErY BSS;

u32 D_800F3E80 BSS;
#endif /* SCOMMON_IN_COMMON */

#ifdef NN_SC_PERF
u8 B_8010B140_cn[B_800CA26C_CN_ARR_LEN][B_801020E8_CN_ARR_ARR_LEN] BSS;
#endif

struct_attack_sprite attack_sprite[0x80] ALIGNED(0x10) BSS;

#if SCOMMON_IN_COMMON
struct struct_watchManual *watchManual BSS;

u8 aiRootCnt BSS;
#endif /* SCOMMON_IN_COMMON */

OSMesgQueue gfx_msgQ BSS;

#if SCOMMON_IN_COMMON
NNScClient gfx_client BSS;

u16 joygam[MAXCONTROLLERS] BSS;

struct struct_gameGeom *gameGeom BSS;
#endif /* SCOMMON_IN_COMMON */

u16 joycur[MAXCONTROLLERS + 1] BSS;

struct_ai_param ai_param[AI_PARAM_LEN1][AI_PARAM_LEN2] BSS;

#if SCOMMON_IN_COMMON
#ifdef NN_SC_PERF
u8 B_800CA26C_cn[B_800CA26C_CN_ARR_LEN] BSS;
#endif
#endif /* SCOMMON_IN_COMMON */

#if SCOMMON_IN_COMMON
s32 MissRate BSS;
#endif /* SCOMMON_IN_COMMON */

#if VERSION_US || VERSION_GW
ALIGNED(0x8)
#endif
OSContStatus B_800F5358[4] BSS;

#if VERSION_US || VERSION_GW
ALIGNED(0x10)
#endif
struct_aiFlag aiFlag[AIFLAG_LEN] BSS;

struct_aiRoot aiRoot[AIROOT_LEN] BSS;

#if SCOMMON_IN_COMMON
unsigned long __muscontrol_flag BSS;

u16 joyflg[MAXCONTROLLERS] BSS;

u8 aiYEdgeCnt BSS;
#endif /* SCOMMON_IN_COMMON */

#if VERSION_US || VERSION_GW
ALIGNED(0x10)
#endif
struct_virus_map_data virus_map_data[4][16 * 8] BSS;

u8 virus_map_disp_order[4][VIRUS_MAP_DISP_ORDER_LEN] BSS;

struct_evs_cfg_4p evs_cfg_4p BSS;

#if SCOMMON_IN_COMMON
#ifdef NN_SC_PERF
s8 B_800CA281_cn BSS;
#endif

bool s_hard_mode BSS;

u8 (*attack_sprite_address)[10][32 * 32 / 2] BSS;
#endif /* SCOMMON_IN_COMMON */

STACK(gfxYieldBuf, GFXYIELDBUF_SIZE) BSS;

/* Automatically generated and unreferenced pad */
u8 D_800F8090[0xC00] BSS;

u8 __libmus_alglobals[0x4C] BSS;

STACK(nnScAudioStack, NN_SC_STACKSIZE) BSS;

struct_800FACE0 sound_song_id BSS;

#if SCOMMON_IN_COMMON
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

u8 joygmf[MAXCONTROLLERS] ALIGNED(ALIGNOF(u8)) BSS;

u16 aiGoalY BSS;

u8 aipn BSS;
#endif /* SCOMMON_IN_COMMON */

Unk_AIFEntry aif_field[GAME_MAP_ROWS][GAME_MAP_COLUMNS] ALIGNED(8) BSS;

u8 gReverbFx[0x28] BSS;

#if SCOMMON_IN_COMMON
u8 evs_select_name_no[EVS_SELECT_NAME_NO_COUNT] BSS;
#endif /* SCOMMON_IN_COMMON */

OSScTask B_800FAE80[GTASK_NO_MAX] BSS;

u16 gControllerPressedButtons[MAXCONTROLLERS + 1] BSS;

#if SCOMMON_IN_COMMON
s8 aiSelSpeed BSS;

OSMesgQueue *sched_gfxMQ BSS;

Audio_struct_800FAF98 *gAudio_800FAF98 BSS;

u16 aiHiEraseCtr BSS;
#endif /* SCOMMON_IN_COMMON */

STACK(dram_stack, DRAM_STACK_SIZE) ALIGNED(0x10) BSS;

#if SCOMMON_IN_COMMON
u8 aiMoveSF BSS;

u32 evs_game_time BSS;
#endif /* SCOMMON_IN_COMMON */

struct_attack_effect attack_effect[0x10] BSS;

Gfx gGfxGlist[GTASK_NO_MAX][0x1000] ALIGNED(0x10) BSS;

u16 joycnt[MAXCONTROLLERS][0x10] BSS;

STACK(rdp_output, RDP_OUTPUT_SIZE) BSS;

#if SCOMMON_IN_COMMON
enum_evs_gamemode evs_gamemode BSS;
#endif /* SCOMMON_IN_COMMON */

struct_game_state_data game_state_data[4] ALIGNED(0x10) BSS;

#if SCOMMON_IN_COMMON
#ifdef NN_SC_PERF
u8 B_800CA2C0_cn[2] BSS;
#endif
#endif /* SCOMMON_IN_COMMON */

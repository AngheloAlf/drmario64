#define DECLARE_COMMON_SYMS 1

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

#if VERSION_US || VERSION_GW
#ifdef NN_SC_PERF
u8 *B_800CA1C0_cn BSS; // TODO
#endif

f32 aiRootP BSS; // TODO

u8 aiWall BSS; // TODO

s16 gfx_msg_no BSS; // TODO

#if VERSION_US
/* Automatically generated and unreferenced pad */
u8 D_800E9BB8[0x08] BSS; // TODO
#endif
#if VERSION_GW
/* Automatically generated and unreferenced pad */
u8 D_800EAA1C[0x4] BSS; // TODO
#endif
#endif

struct_ai_char_data ai_char_data[AI_CHAR_DATA_LEN] ALIGNED(0x10) BSS; // TODO

#if VERSION_US || VERSION_GW
u8 success BSS; // TODO

/* Automatically generated and unreferenced pad */
// u8 D_800EA281[0x03] BSS; // TODO

s32 attack_sprite_idx BSS; // TODO

/* Automatically generated and unreferenced pad */
u8 D_800EA288[0x08] BSS; // TODO
#endif

BgTasksManager sBgTasksManager_Manager BSS; // TODO

#ifdef NN_SC_PERF
struct_801020E8_cn B_801020E8_cn[B_800CA26C_CN_ARR_LEN][B_801020E8_CN_ARR_ARR_LEN] BSS; // TODO
#endif

OSContPad B_800EB4D8[MAXCONTROLLERS] BSS; // TODO

#if VERSION_US || VERSION_GW
enum_main_no main_old BSS; // TODO

s32 _menuMain_lastDepth BSS; // TODO
#endif

Unk_AIFEntry aiRecurData[GAME_MAP_ROWS + 1][GAME_MAP_COLUMNS + 2] BSS; // TODO

#if VERSION_US || VERSION_GW
u8 aiTEdgeCnt BSS; // TODO

/* Automatically generated and unreferenced pad */
u8 D_800EB660[0xF] ALIGNED(ALIGNOF(u8)) BSS; // TODO
#endif

NNSched B_800EB670 BSS; // TODO

#if VERSION_US || VERSION_GW
enum_main_no main_no BSS; // TODO

Gfx* gGfxHead BSS; // TODO
#endif

u16 gControllerHoldButtons[MAXCONTROLLERS+1] BSS; // TODO

#if VERSION_CN
/* Automatically generated and unreferenced pad */
u8 D_80102BF2[0x02] ALIGNED(ALIGNOF(u8)) BSS; // TODO
#endif

u8 hei_data[0x0A] ALIGNED(ALIGNOF(u8)) BSS; // TODO

#if VERSION_US || VERSION_GW
/* Automatically generated and unreferenced pad */
u8 D_800EBD0C[0x04] BSS; // TODO

u32 PlayTime BSS; // TODO

#ifdef NN_SC_PERF
struct_801020E8_cn *B_800CA1F0_cn BSS; // TODO
#endif

u8 aiNext[0x02] BSS; // TODO

u8 main_joy[MAXCONTROLLERS] ALIGNED(ALIGNOF(u8)) BSS; // TODO

/* Automatically generated and unreferenced pad */
// u8 D_800EBD1A[0x06] BSS; // TODO
#endif

OSThread gfxThread BSS; // TODO

OSMesg gfx_msgbuf[8] BSS; // TODO

GameMapCell game_map_data[4][GAME_MAP_ROWS * GAME_MAP_COLUMNS] BSS; // TODO

#if VERSION_US || VERSION_GW
s16 gfx_msg BSS; // TODO
#endif

/* Automatically generated and unreferenced pad */
// u8 D_800ED432[0x0E] BSS; // TODO

STACK(nnScGraphicsStack, NN_SC_STACKSIZE) BSS; // TODO

#if VERSION_US || VERSION_GW
struct_gameBackup *gameBackup[2] BSS; // TODO
#endif

u8 CapsMagazine[0x100] BSS; // TODO

#if VERSION_US || VERSION_GW
s32 attack_effect_idx BSS; // TODO

u8 diskrom_handle[0x04] BSS; // TODO

bool fool_mode BSS; // TODO

u16 joycur1 BSS; // TODO

u8 decide BSS; // TODO
#endif

/* Automatically generated and unreferenced pad */
// u8 D_800EF557[0x09] BSS; // TODO

struct_evs_mem_data evs_mem_data[9] ALIGNED(0x10) BSS; // TODO

s32 _menuMain_lastSelect[8] BSS; // TODO

#if VERSION_US || VERSION_GW
enum_evs_gamesel evs_gamesel BSS; // TODO

/* Automatically generated and unreferenced pad */
u8 D_800EFCD4[0x0C] BSS; // TODO
#endif

STACK(nnScStack, NN_SC_STACKSIZE) BSS; // TODO

#if VERSION_US || VERSION_GW
u8 evs_playmax BSS; // TODO

/* Automatically generated and unreferenced pad */
// u8 D_800F1CE1[0x07] BSS; // TODO
#endif

Unk_AIFEntry aiFieldData[GAME_MAP_ROWS][GAME_MAP_COLUMNS] ALIGNED(8) BSS; // TODO

#if VERSION_US || VERSION_GW
Mtx *pObjectMtx BSS; // TODO

/* Automatically generated and unreferenced pad */
u8 D_800F1DFC[0x04] BSS; // TODO
#endif

s32 evs_default_name[8] BSS; // TODO

#if VERSION_US || VERSION_GW
u16 joycur2 BSS; // TODO

/* Automatically generated and unreferenced pad */
// u8 D_800F1E22[0x0E] BSS; // TODO
#endif

STACK(sGraphicStack, GRAPHIC_STACK_SIZE) BSS; // TODO

#if VERSION_US || VERSION_GW
s16 aiHiErB BSS; // TODO
#endif

#if VERSION_GW
/* Automatically generated and unreferenced pad */
u8 D_800F4F92[0x0E] ALIGNED(ALIGNOF(u8)) BSS; // TODO
#endif

#if VERSION_GW || VERSION_CN
NNScPerf nnsc_perf[NN_SC_PERF_NUM] BSS; // TODO
#endif

#if VERSION_US || VERSION_GW
u16 aiPriOfs BSS; // TODO

u8 aiRollFinal BSS; // TODO

/* Automatically generated and unreferenced pad */
// u8 D_800F3E35[0x03] BSS; // TODO
#endif

OSMesgQueue B_800F3E38 ALIGNED(8) BSS; // TODO

#if VERSION_US || VERSION_GW
struct struct_watchGame *watchGame BSS; // TODO

u8 aiFlagCnt BSS; // TODO

u16 aiGoalX BSS; // TODO

#if VERSION_GW
NNScPerf *nnsc_perf_ptr BSS; // TODO
#endif

/* Automatically generated and unreferenced pad */
u8 D_800F3E58[0x04] BSS; // TODO

struct_watchMenu *watchMenu BSS; // TODO

OSMesg B_800F3E60[1] BSS; // TODO
#endif

u16 gControllerPrevHoldButtons[MAXCONTROLLERS+1] BSS; // TODO

#if VERSION_CN
/* Automatically generated and unreferenced pad */
u8 D_8010B132[0x2] ALIGNED(ALIGNOF(u8)) BSS; // TODO
#endif

u8 wid_data[0x0A] ALIGNED(ALIGNOF(u8)) BSS; // TODO

#if VERSION_US || VERSION_GW
u8 link_joy[MAXCONTROLLERS] BSS; // TODO

s16 aiHiErY BSS; // TODO
#endif

#if VERSION_US
/* Automatically generated and unreferenced pad */
u8 D_800F3E7E[0x12] ALIGNED(ALIGNOF(u8)) BSS; // TODO
#endif

#if VERSION_GW
/* Automatically generated and unreferenced pad */
u8 D_800F5452[0x06] ALIGNED(ALIGNOF(u8)) BSS; // TODO
#endif

#ifdef NN_SC_PERF
u8 B_8010B140_cn[B_800CA26C_CN_ARR_LEN][B_801020E8_CN_ARR_ARR_LEN] BSS; // TODO
#endif

#if VERSION_GW
/* Automatically generated and unreferenced pad */
u8 D_800F5498[0x08] ALIGNED(ALIGNOF(u8)) BSS; // TODO
#endif

struct_attack_sprite attack_sprite[0x80] BSS; // TODO

#if VERSION_US || VERSION_GW
struct struct_watchManual *watchManual BSS; // TODO

u8 aiRootCnt BSS; // TODO

/* Automatically generated and unreferenced pad */
// u8 D_800F4895[0x03] BSS; // TODO
#endif

OSMesgQueue gfx_msgQ BSS; // TODO

#if VERSION_US || VERSION_GW
NNScClient gfx_client BSS; // TODO

u16 joygam[MAXCONTROLLERS] BSS; // TODO

struct_gameGeom *gameGeom BSS; // TODO
#endif

u16 joycur[MAXCONTROLLERS+1] BSS; // TODO

/* Automatically generated and unreferenced pad */
// u8 D_800F48CE[0x02] BSS; // TODO

struct_ai_param ai_param[AI_PARAM_LEN1][AI_PARAM_LEN2] BSS; // TODO

#if VERSION_US || VERSION_GW
#ifdef NN_SC_PERF
u8 B_800CA26C_cn[B_800CA26C_CN_ARR_LEN] BSS; // TODO
#endif
#endif

#if VERSION_US || VERSION_GW
s32 MissRate BSS; // TODO
#endif

#if VERSION_US
/* Automatically generated and unreferenced pad */
u8 D_800F5354[0x04] BSS; // TODO
#endif

OSContStatus B_800F5358[4] BSS; // TODO

#if VERSION_US || VERSION_GW
/* Automatically generated and unreferenced pad */
u8 D_800F5368[0x08] BSS; // TODO
#endif

struct_aiFlag aiFlag[AIFLAG_LEN] BSS; // TODO

u8 aiRoot[AIROOT_LEN][2] BSS; // TODO

#if VERSION_US || VERSION_GW
u8 __muscontrol_flag[0x04] BSS; // TODO

u16 joyflg[MAXCONTROLLERS] BSS; // TODO

u8 aiYEdgeCnt BSS; // TODO

/* Automatically generated and unreferenced pad */
u8 D_800F6CE1[0x0F] ALIGNED(ALIGNOF(u8)) BSS; // TODO
#endif

struct_virus_map_data virus_map_data[4][16 * 8] BSS; // TODO

u8 virus_map_disp_order[4][VIRUS_MAP_DISP_ORDER_LEN] BSS; // TODO

struct_evs_cfg_4p evs_cfg_4p BSS; // TODO

#if VERSION_US || VERSION_GW
#if VERSION_GW
s8 B_800CA281_cn BSS; // TODO
#endif

/* Automatically generated and unreferenced pad */
// u8 D_800F7486[0x02] BSS; // TODO

bool s_hard_mode BSS; // TODO

u8 (*attack_sprite_address)[10][32 * 32 / 2] BSS; // TODO
#endif

STACK(gfxYieldBuf, GFXYIELDBUF_SIZE) BSS; // TODO

/* Automatically generated and unreferenced pad */
u8 D_800F8090[0xC00] BSS; // TODO

u8 __libmus_alglobals[0x4C] BSS; // TODO

/* Automatically generated and unreferenced pad */
u8 D_800F8CDC[0x04] BSS; // TODO

STACK(nnScAudioStack, NN_SC_STACKSIZE) BSS; // TODO

struct_800FACE0 sound_song_id BSS; // TODO

#if VERSION_US || VERSION_GW
s16 aiHiErR BSS; // TODO

#ifdef NN_SC_PERF
struct_801020E8_cn *B_800CA290_cn BSS; // TODO
#endif

u32 gfx_gtask_no BSS; // TODO

#if VERSION_GW
NNScPerf *nnsc_perf_inptr BSS; // TODO
#endif

u8 aiSelCom BSS; // TODO

#if VERSION_GW
u8 B_800CA29B_cn BSS; // TODO
#endif

u8 joygmf[MAXCONTROLLERS] ALIGNED(ALIGNOF(u8)) BSS; // TODO

/* Automatically generated and unreferenced pad */
// u8 D_800FAD35[0x01] BSS; // TODO

u16 aiGoalY BSS; // TODO

u8 aipn BSS; // TODO

/* Automatically generated and unreferenced pad */
u8 D_800FAD39[0x07] ALIGNED(ALIGNOF(u8)) BSS; // TODO
#endif

Unk_AIFEntry aif_field[GAME_MAP_ROWS][GAME_MAP_COLUMNS] BSS; // TODO

u8 gReverbFx[0x28] BSS; // TODO

#if VERSION_US || VERSION_GW
u8 evs_select_name_no[0x2] BSS; // TODO

/* Automatically generated and unreferenced pad */
// u8 D_800FAE7A[0x06] BSS; // TODO
#endif

OSScTask B_800FAE80[GTASK_NO_MAX] BSS; // TODO

u16 gControllerPressedButtons[MAXCONTROLLERS+1] BSS; // TODO

#if VERSION_US || VERSION_GW
s8 aiSelSpeed BSS; // TODO

OSMesgQueue *sched_gfxMQ BSS; // TODO

Audio_struct_800FAF98 *gAudio_800FAF98 BSS; // TODO

u16 aiHiEraseCtr BSS; // TODO
#endif

/* Automatically generated and unreferenced pad */
// u8 D_800FAF9E[0x02] BSS; // TODO

#if VERSION_CN
/* Automatically generated and unreferenced pad */
u8 D_80112212[0x0E] ALIGNED(ALIGNOF(u8)) BSS; // TODO
#endif

STACK(dram_stack, DRAM_STACK_SIZE) BSS; // TODO

#if VERSION_US || VERSION_GW
u8 aiMoveSF BSS; // TODO

/* Automatically generated and unreferenced pad */
// u8 D_800FB3A1[0x03] BSS; // TODO

u32 evs_game_time BSS; // TODO
#endif

struct_attack_effect attack_effect[0x10] BSS; // TODO

#if VERSION_US || VERSION_GW
/* Automatically generated and unreferenced pad */
u8 D_800FB668[0x08] BSS; // TODO
#endif

Gfx gGfxGlist[GTASK_NO_MAX][0x1000] BSS; // TODO

u16 joycnt[MAXCONTROLLERS][0x10] BSS; // TODO

STACK(rdp_output, RDP_OUTPUT_SIZE) BSS; // TODO

#if VERSION_US || VERSION_GW
enum_evs_gamemode evs_gamemode BSS; // TODO

/* Automatically generated and unreferenced pad */
u8 D_801236F4[0x0C] BSS; // TODO
#endif

struct_game_state_data game_state_data[4] BSS; // TODO

#if VERSION_GW
u8 B_800CA2C0_cn[2] BSS; // TODO
#endif

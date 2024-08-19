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

#if VERSION_US
u8 aiRootP[0x04] BSS; // TODO

u8 aiWall BSS; // TODO

s16 gfx_msg_no BSS; // TODO

/* Automatically generated and unreferenced pad */
u8 D_800E9BB8[0x08] BSS; // TODO

struct_ai_char_data ai_char_data[AI_CHAR_DATA_LEN] BSS; // TODO

u8 success BSS; // TODO

/* Automatically generated and unreferenced pad */
// u8 D_800EA281[0x03] BSS; // TODO

s32 attack_sprite_idx BSS; // TODO

/* Automatically generated and unreferenced pad */
u8 D_800EA288[0x08] BSS; // TODO

u8 sBgTasksManager_Manager[0x1248] BSS; // TODO

u8 B_800EB4D8[0x18] BSS; // TODO

u8 main_old[0x04] BSS; // TODO

u8 _menuMain_lastDepth[0x04] BSS; // TODO

Unk_AIFEntry aiRecurData[GAME_MAP_ROWS + 1][GAME_MAP_COLUMNS + 2] BSS; // TODO

u8 aiTEdgeCnt[0x10] BSS; // TODO

u8 B_800EB670[0x67C] BSS; // TODO

/* Automatically generated and unreferenced pad */
u8 D_800EBCEC[0x04] BSS; // TODO

u8 main_no[0x04] BSS; // TODO

u8 gGfxHead[0x04] BSS; // TODO

u16 gControllerHoldButtons[5] BSS; // TODO

u8 hei_data[0x0A] ALIGNED(ALIGNOF(u8)) BSS; // TODO

/* Automatically generated and unreferenced pad */
u8 D_800EBD0C[0x04] BSS; // TODO

u8 PlayTime[0x04] BSS; // TODO

u8 aiNext[0x02] BSS; // TODO

u8 main_joy[0x04] ALIGNED(ALIGNOF(u8)) BSS; // TODO

/* Automatically generated and unreferenced pad */
// u8 D_800EBD1A[0x06] BSS; // TODO

OSThread gfxThread BSS; // TODO

u8 gfx_msgbuf[0x20] BSS; // TODO

GameMapCell game_map_data[4][GAME_MAP_ROWS * GAME_MAP_COLUMNS] BSS; // TODO

u8 gfx_msg[0x02] BSS; // TODO

/* Automatically generated and unreferenced pad */
// u8 D_800ED432[0x0E] BSS; // TODO

STACK(nnScGraphicsStack, NN_SC_STACKSIZE) BSS; // TODO

u8 gameBackup[0x08] BSS; // TODO

u8 CapsMagazine[0x100] BSS; // TODO

s32 attack_effect_idx BSS; // TODO

u8 diskrom_handle[0x04] BSS; // TODO

u8 fool_mode[0x04] BSS; // TODO

u16 joycur1 BSS; // TODO

u8 decide BSS; // TODO

/* Automatically generated and unreferenced pad */
// u8 D_800EF557[0x09] BSS; // TODO

struct_evs_mem_data evs_mem_data[9] ALIGNED(0x10) BSS; // TODO

u8 _menuMain_lastSelect[0x20] BSS; // TODO

u8 evs_gamesel[0x04] BSS; // TODO

/* Automatically generated and unreferenced pad */
u8 D_800EFCD4[0x0C] BSS; // TODO

STACK(nnScStack, NN_SC_STACKSIZE) BSS; // TODO

u8 evs_playmax BSS; // TODO

/* Automatically generated and unreferenced pad */
// u8 D_800F1CE1[0x07] BSS; // TODO

Unk_AIFEntry aiFieldData[GAME_MAP_ROWS][GAME_MAP_COLUMNS] ALIGNED(8) BSS; // TODO

u8 pObjectMtx[0x04] BSS; // TODO

/* Automatically generated and unreferenced pad */
u8 D_800F1DFC[0x04] BSS; // TODO

u8 evs_default_name[0x20] BSS; // TODO

u16 joycur2 BSS; // TODO

/* Automatically generated and unreferenced pad */
// u8 D_800F1E22[0x0E] BSS; // TODO

STACK(sGraphicStack, GRAPHIC_STACK_SIZE) BSS; // TODO

s16 aiHiErB BSS; // TODO

u16 aiPriOfs BSS; // TODO

u8 aiRollFinal BSS; // TODO

/* Automatically generated and unreferenced pad */
// u8 D_800F3E35[0x03] BSS; // TODO

OSMesgQueue B_800F3E38 BSS; // TODO

u8 watchGame[0x04] BSS; // TODO

u8 aiFlagCnt BSS; // TODO

u16 aiGoalX BSS; // TODO

/* Automatically generated and unreferenced pad */
u8 D_800F3E58[0x04] BSS; // TODO

u8 watchMenu[0x04] BSS; // TODO

u8 B_800F3E60[0x04] BSS; // TODO

u8 gControllerPrevHoldButtons[0x0A] BSS; // TODO

u8 wid_data[0x0A] ALIGNED(ALIGNOF(u8)) BSS; // TODO

u8 link_joy[0x04] BSS; // TODO

u8 aiHiErY[0x02] BSS; // TODO

/* Automatically generated and unreferenced pad */
u8 D_800F3E7E[0x12] ALIGNED(ALIGNOF(u8)) BSS; // TODO

struct_attack_sprite attack_sprite[0x80] BSS; // TODO

u8 watchManual[0x04] BSS; // TODO

u8 aiRootCnt[0x01] BSS; // TODO

/* Automatically generated and unreferenced pad */
// u8 D_800F4895[0x03] BSS; // TODO

OSMesgQueue gfx_msgQ BSS; // TODO

NNScClient gfx_client BSS; // TODO

u8 joygam[0x08] BSS; // TODO

struct_gameGeom *gameGeom BSS; // TODO

u8 joycur[0x0A] BSS; // TODO

/* Automatically generated and unreferenced pad */
// u8 D_800F48CE[0x02] BSS; // TODO

struct_ai_param ai_param[AI_PARAM_LEN1][AI_PARAM_LEN2] BSS; // TODO

u8 MissRate[0x04] BSS; // TODO

/* Automatically generated and unreferenced pad */
u8 D_800F5354[0x04] BSS; // TODO

u8 B_800F5358[0x10] BSS; // TODO

/* Automatically generated and unreferenced pad */
u8 D_800F5368[0x08] BSS; // TODO

struct_aiFlag aiFlag[AIFLAG_LEN] BSS; // TODO

u8 aiRoot[AIROOT_LEN][2] BSS; // TODO

u8 __muscontrol_flag[0x04] BSS; // TODO

u8 joyflg[0x08] BSS; // TODO

u8 aiYEdgeCnt BSS; // TODO

/* Automatically generated and unreferenced pad */
u8 D_800F6CE1[0x0F] ALIGNED(ALIGNOF(u8)) BSS; // TODO

struct_virus_map_data virus_map_data[4][16 * 8] BSS; // TODO

u8 virus_map_disp_order[4][VIRUS_MAP_DISP_ORDER_LEN] BSS; // TODO

struct_evs_cfg_4p evs_cfg_4p BSS; // TODO

/* Automatically generated and unreferenced pad */
// u8 D_800F7486[0x02] BSS; // TODO

s32 s_hard_mode BSS; // TODO

u8 (*attack_sprite_address)[10][32 * 32 / 2] BSS; // TODO

u8 gfxYieldBuf[0xC00] BSS; // TODO

/* Automatically generated and unreferenced pad */
u8 D_800F8090[0xC00] BSS; // TODO

u8 __libmus_alglobals[0x4C] BSS; // TODO

/* Automatically generated and unreferenced pad */
u8 D_800F8CDC[0x04] BSS; // TODO

STACK(nnScAudioStack, NN_SC_STACKSIZE) BSS; // TODO

u8 sound_song_id[0x48] BSS; // TODO

u8 aiHiErR[0x04] BSS; // TODO

u32 gfx_gtask_no BSS; // TODO

u8 aiSelCom BSS; // TODO

u8 joygmf[0x04] ALIGNED(ALIGNOF(u8)) BSS; // TODO

/* Automatically generated and unreferenced pad */
// u8 D_800FAD35[0x01] BSS; // TODO

u16 aiGoalY BSS; // TODO

u8 aipn BSS; // TODO

/* Automatically generated and unreferenced pad */
u8 D_800FAD39[0x07] ALIGNED(ALIGNOF(u8)) BSS; // TODO

Unk_AIFEntry aif_field[GAME_MAP_ROWS][GAME_MAP_COLUMNS] BSS; // TODO

u8 gReverbFx[0x28] BSS; // TODO

u8 evs_select_name_no[0x02] BSS; // TODO

/* Automatically generated and unreferenced pad */
// u8 D_800FAE7A[0x06] BSS; // TODO

OSScTask B_800FAE80[GTASK_NO_MAX] BSS; // TODO

u8 gControllerPressedButtons[0x0A] BSS; // TODO

u8 aiSelSpeed BSS; // TODO

OSMesgQueue *sched_gfxMQ BSS; // TODO

u8 gAudio_800FAF98[0x04] BSS; // TODO

u16 aiHiEraseCtr BSS; // TODO

/* Automatically generated and unreferenced pad */
// u8 D_800FAF9E[0x02] BSS; // TODO

STACK(dram_stack, 0x400) BSS; // TODO

u8 aiMoveSF BSS; // TODO

/* Automatically generated and unreferenced pad */
// u8 D_800FB3A1[0x03] BSS; // TODO

u32 evs_game_time BSS; // TODO

struct_attack_effect attack_effect[0x10] BSS; // TODO

/* Automatically generated and unreferenced pad */
u8 D_800FB668[0x08] BSS; // TODO

u8 gGfxGlist[0x18000] BSS; // TODO

u8 joycnt[0x80] BSS; // TODO

u8 rdp_output[0x10000] BSS; // TODO

u8 evs_gamemode[0x04] BSS; // TODO

/* Automatically generated and unreferenced pad */
u8 D_801236F4[0x0C] BSS; // TODO

u8 game_state_data[0xF10] BSS; // TODO
#endif

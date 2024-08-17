#ifndef MAIN_SEGMENT_VARIABLES_H
#define MAIN_SEGMENT_VARIABLES_H

#include "libultra.h"
#include "libc/stdint.h"
#include "libc/stdbool.h"
#include "PR/sched.h"
#include "unknown_structs.h"
#include "unk.h"
#include "alignment.h"
#include "stack.h"

struct struct_watchMenu;

// bss

// extern UNK_TYPE aiRootP;
// extern UNK_TYPE aiWall;
extern s16 gfx_msg_no;

extern u8 success;
// extern UNK_TYPE attack_sprite_idx;

// extern UNK_TYPE B_800EB290;
extern s32 B_800EB4CC;
extern s32 B_800EB4D0;
extern OSContPad B_800EB4D8[MAXCONTROLLERS];
extern enum_main_no main_old; /* Orignal name: main_old */
extern s32 _menuMain_lastDepth;

// extern UNK_TYPE B_800EB4F9;
// extern UNK_TYPE B_800EB50A;
// extern UNK_TYPE B_800EB50B;
// extern UNK_TYPE B_800EB64C;
// extern UNK_TYPE B_800EB64D;
// extern UNK_TYPE aiTEdgeCnt;

extern enum_main_no main_no; /* Original name: main_no */
extern Gfx* gGfxHead; /* Original name: gp */ // main display list head
extern u16 gControllerHoldButtons[MAXCONTROLLERS+1];
// extern UNK_TYPE hei_data;
// extern UNK_TYPE B_800EBD03;
// extern UNK_TYPE B_800EBD04;
// extern UNK_TYPE B_800EBD05;
// extern UNK_TYPE B_800EBD07;
// extern UNK_TYPE B_800EBD0B;
extern u32 PlayTime;
extern u8 aiNext[]; // maybe a struct?
extern u8 main_joy[];
extern OSThread gfxThread; /* Original name */
extern OSMesg gfx_msgbuf[8];

extern s16 gfx_msg;

extern struct_gameBackup *gameBackup[2];
extern u8 CapsMagazine[0x100];
// extern UNK_TYPE attack_effect_idx;
// extern UNK_TYPE B_800EF54C;

extern s32 fool_mode; // maybe bool?
extern u16 joycur1; /* Original name: joycur1 */
extern u8 decide;

extern s32 _menuMain_lastSelect[8]; // probably an enum
extern enum_evs_gamesel evs_gamesel; /* Original name: evs_gamesel */

extern u8 evs_playmax; /* Original name: evs_playmax */
// extern UNK_TYPE B_800F1CE9;
extern Mtx *pObjectMtx;
extern s32 evs_default_name[];
extern u16 joycur2; /* Original name: joycur2 */
extern STACK(sGraphicStack, 0x2000);
// extern UNK_TYPE aiHiErB;
// extern UNK_TYPE aiPriOfs;
// extern UNK_TYPE aiRollFinal;
extern OSMesgQueue B_800F3E38;
extern struct_watchGame *watchGame;
extern u8 aiFlagCnt;
extern u16 aiGoalX;
extern struct struct_watchMenu *watchMenu;
extern OSMesg B_800F3E60[1];
extern u16 gControllerPrevHoldButtons[MAXCONTROLLERS+1];
// extern UNK_TYPE wid_data;
// extern UNK_TYPE B_800F3E6F;
// extern UNK_TYPE B_800F3E70;
// extern UNK_TYPE B_800F3E71;
// extern UNK_TYPE B_800F3E73;
// extern UNK_TYPE B_800F3E77;
extern u8 link_joy[];
// extern UNK_TYPE aiHiErY;
// extern UNK_TYPE attack_sprite;
// extern UNK_TYPE B_800F3E94;
// extern UNK_TYPE B_800F3E98;
// extern UNK_TYPE B_800F3E9C;
// extern UNK_TYPE B_800F3EA0;
extern struct_watchManual *watchManual; /* Original name: watchManual */
extern u8 aiRootCnt;
extern OSMesgQueue gfx_msgQ;

extern u16 joygam[4];

extern u16 joycur[MAXCONTROLLERS+1];
extern s32 MissRate;
extern OSContStatus B_800F5358[4];

// extern UNK_TYPE B_800F6C71;
// extern UNK_TYPE B_800F6CD4;
extern u16 joyflg[MAXCONTROLLERS];
// extern UNK_TYPE aiYEdgeCnt;

extern struct_evs_cfg_4p evs_cfg_4p;
extern s32 s_hard_mode; // maybe bool?
// extern UNK_TYPE attack_sprite_address;
extern STACK(gfxYieldBuf, 0xC00);
// extern UNK_TYPE B_800F8C90;

// extern UNK_TYPE aiHiErR;
// extern UNK_TYPE aiSelCom;
extern u8 joygmf[4];
extern u16 aiGoalY;
extern u8 aipn;
// extern UNK_TYPE aif_field;
// extern UNK_TYPE B_800FAD41;
// extern UNK_TYPE B_800FAE50;
// extern UNK_TYPE B_800FAE60;
// extern UNK_TYPE B_800FAE64;
// extern UNK_TYPE B_800FAE68;
// extern UNK_TYPE B_800FAE6C;
// extern UNK_TYPE B_800FAE70;
// extern UNK_TYPE B_800FAE74;
extern u8 evs_select_name_no[2];
extern OSScTask B_800FAE80[];
extern u16 gControllerPressedButtons[MAXCONTROLLERS+1]; /* Original name: joyupd */
extern s8 aiSelSpeed;
extern OSMesgQueue *sched_gfxMQ;

// extern UNK_TYPE aiHiEraseCtr;
extern STACK(dram_stack, 0x400); // dram_stack?
extern u8 aiMoveSF; // maybe bool?
extern u32 evs_game_time;
// extern UNK_TYPE attack_effect;
// extern UNK_TYPE B_800FB3AC;
// extern UNK_TYPE B_800FB3B0;
// extern UNK_TYPE B_800FB3B4;
// extern UNK_TYPE B_800FB3B8;
// extern UNK_TYPE B_800FB3BC;
// extern UNK_TYPE B_800FB3C0;
// extern UNK_TYPE B_800FB3C4;
// extern UNK_TYPE B_800FB3C8;
// extern UNK_TYPE B_800FB3CC;
// extern UNK_TYPE B_800FB3D0;

// TODO: replace 3 with GTASK_NO_MAX
extern Gfx gGfxGlist[3][0x1000]; /* Original name: gfx_glist */

extern u16 joycnt[4][0x10]; /* Original name: joycnt */
extern STACK(rdp_output, 0x10000);
extern enum_evs_gamemode evs_gamemode;

extern struct_game_state_data game_state_data[4]; /* Original name: game_state_data */


#endif

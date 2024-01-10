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


// data

// extern UNK_TYPE D_80088490;
extern u8 aiVirusLevel[][3];
extern u8 D_800884C0[][3];
extern u8 aiSlideFSpeed[][3];
extern u8 D_800884F0[][3];
extern s8 aiDebugP1;
extern u8 capsGCnv_122[];
extern u8 capsCCnv_123[];
// extern UNK_TYPE D_8008852C;
// extern UNK_TYPE D_80088534;
// extern UNK_TYPE D_80088535;
// extern UNK_TYPE D_8008853C;
// extern UNK_TYPE D_8008854C;
// extern UNK_TYPE D_8008855E;
// extern UNK_TYPE D_80088564;
// extern UNK_TYPE D_8008856A;
// extern UNK_TYPE D_8008856C;
// extern UNK_TYPE D_80088570;
// extern UNK_TYPE D_80088572;
// extern UNK_TYPE D_80088574;
// extern UNK_TYPE D_80088584;
// extern UNK_TYPE D_80088588;
// extern UNK_TYPE D_8008858C;
// extern UNK_TYPE D_80088590;
// extern UNK_TYPE D_80088592;
// extern UNK_TYPE D_80088594;
// extern UNK_TYPE D_80088596;
// extern UNK_TYPE D_80088598;
// extern UNK_TYPE D_8008859A;
// extern UNK_TYPE D_8008859C;
// extern UNK_TYPE D_800885A0;
// extern UNK_TYPE D_800885A4;
// extern UNK_TYPE D_800885A6;
// extern UNK_TYPE D_800885A8;
// extern UNK_TYPE D_800885AA;
// extern UNK_TYPE D_800885AC;
// extern UNK_TYPE D_800885AE;
// extern UNK_TYPE D_800885B0;
// extern UNK_TYPE D_800885B4;
// extern UNK_TYPE D_800885B8;
// extern UNK_TYPE D_800885BA;
// extern UNK_TYPE D_800885BC;
// extern UNK_TYPE D_800885BE;
// extern UNK_TYPE D_800885C0;
// extern UNK_TYPE D_800885C2;
// extern UNK_TYPE D_800885C4;
// extern UNK_TYPE D_800885C6;
// extern UNK_TYPE D_800885C8;
// extern UNK_TYPE D_800885CA;
// extern UNK_TYPE D_800885CC;
// extern UNK_TYPE D_800885D2;
// extern UNK_TYPE D_800885D4;
// extern UNK_TYPE D_800885D6;
// extern UNK_TYPE D_800885D8;
// extern UNK_TYPE D_800885F8;
// extern UNK_TYPE D_80088638;
extern struct_ai_param ai_param_org[AI_PARAM_LEN1][AI_PARAM_LEN2];
extern struct_ai_char_data ai_char_data_org[AI_CHAR_DATA_LEN];

// extern UNK_TYPE D_8008CFA0;
extern s32 D_8008CFE0;

extern u8 virus_anime_table[3][4];
// extern UNK_TYPE dm_chaine_se_table_vs_178;
// extern UNK_TYPE dm_chaine_se_table_4p_179;
extern s32 rotate_table_474[];
extern s32 rotate_mtx_475[];
extern s32 D_800A6FC4;
// extern UNK_TYPE visible_fall_point;
extern char _mesPassword[];
extern char _mesEasyCont[];
extern char _mesEasyNoCont[];
extern char _mesNormalCont[];
extern char _mesNormalNoCont[];
extern char _mesHardCont[];
extern char _mesHardNoCont[];
extern char _mesSHardCont[];
extern char _mesSHardNoCont[];
extern s32 _n_1199[];
extern u8 D_800A7360[];
// extern UNK_TYPE tbl_4589;
// extern UNK_TYPE col_4590;
// extern UNK_TYPE D_800A7379;
// extern UNK_TYPE D_800A737A;
// extern UNK_TYPE D_800A737B;
extern s32 title_demo_flg;
extern s32 title_demo_no; /* Original name: title_demo_no */
extern s32 title_manual_no;
extern s32 title_exit_flag; /* Original name: title_exit_flag */

// extern UNK_TYPE D_800A73A0;
// extern UNK_TYPE D_800A73B8;

// extern UNK_TYPE D_800AAE60;
// extern UNK_TYPE D_800AAFF4;
// extern UNK_TYPE D_800AB170;
// extern UNK_TYPE D_800AB1B4;
// extern UNK_TYPE D_800AB1D4;
// extern UNK_TYPE D_800AB1EC;
// extern UNK_TYPE D_800AB1FC;
// extern UNK_TYPE D_800AB20C;
// extern UNK_TYPE D_800AB21C;
// extern UNK_TYPE D_800AB29C;
// extern UNK_TYPE D_800AB320;
// extern UNK_TYPE D_800AB32C;
// extern UNK_TYPE D_800AB334;
// extern UNK_TYPE D_800AB3B4;
extern u16 D_800AB440[];
// extern UNK_TYPE D_800ABC50;
// extern UNK_TYPE D_800ABD10;
// extern UNK_TYPE D_800ABD78;
// extern UNK_TYPE D_800ABE00;
// extern UNK_TYPE D_800ABE28;
// extern UNK_TYPE D_800ABEB0;
// extern UNK_TYPE D_800ABED8;
// extern UNK_TYPE D_800ABF00;
// extern UNK_TYPE D_800ABF04;
// extern UNK_TYPE D_800ABF20;
// extern UNK_TYPE D_800ABF2C;
// extern UNK_TYPE D_800ABF30;
// extern UNK_TYPE D_800ABF40;


// rodata


// bss

extern u8 B_800B3640[0x31000];
extern struct_game_state_data *pGameState;
// extern UNK_TYPE B_800E5008;
extern s32 delpos_cnt;
// extern UNK_TYPE B_800E519C;
extern s32 last_flash;

// Its size must be a multiple of 8
extern u8 _cache_1333[0x200]; /* Original name: _cache_1333 */

// extern UNK_TYPE B_800E53B0;

// extern UNK_TYPE fbuf;
// extern UNK_TYPE sPrinterState;
extern s32 B_800E58B0;
extern s32 B_800E58B4;
extern s32 B_800E58B8;
extern bool B_800E58BC;
// extern UNK_TYPE B_800E58BE;
extern s16 B_800E58C0[];
extern s32 B_800E5910;
extern s32 B_800E5914;
extern s32 B_800E5918;
extern s32 B_800E591C;
extern s32 B_800E5920;
extern s32 B_800E5924;
extern s32 B_800E5928;
extern s32 B_800E592C;
extern s32 B_800E5930;
extern s32 B_800E5934;

extern s32 B_800E596C;
extern s32 B_800E5970[];
extern UNK_PTR heapTop; /* Original name: heapTop */
extern struct TiTexData *_texAll;
extern struct TiTexData *_texKaSa;
extern s32 title_mode_type;
extern s32 title_fade_count; /* Original name: title_fade_count */
extern s32 title_fade_step;
// extern UNK_TYPE B_800E59B0;
// extern UNK_TYPE B_800E59B4;
// extern UNK_TYPE fin_frame_543;
// extern UNK_TYPE B_800E59BC;
// extern UNK_TYPE B_800E59C0;
// extern UNK_TYPE fin_frame_623;
// extern UNK_TYPE fin_demo_624;
// extern UNK_TYPE fin_frame_667;
// extern UNK_TYPE fin_frame_737;
// extern UNK_TYPE fin_frame_768;
extern s32 title_time;
extern s32 title_wait;
extern void **title_data;
extern void *title_bmp_data;
extern void **lws_data;
// extern struct_lws_scene *lws_scene;
extern MessageWnd mess_st;
extern MessageWnd mess_roll_st;
// extern UNK_TYPE B_800E5AF0;
extern void *mess_roll_heap;
// extern UNK_TYPE st_message_count;
// extern UNK_TYPE st_mes_ptr;
extern bool loop_flg;
extern s32 story_staff_roll;
extern u16 story_norm; /* Original name: story_norm */
extern Mtx story_viewMtx; /* Original name: story_viewMtx */
extern Mtx story_objectMtx[2][0x50];
// extern struct_wakuGraphic *wakuGraphic;
extern void *bgGraphic; /* Original name: bgGraphic */
extern void *storyGraphic;
extern void *messageData;
extern s32 first_copy;
extern struct_800E87C0 B_800E87C0[0x40];
extern s32 randomindex;
extern s32 randomtable[55];

// extern UNK_TYPE B_800E98A0;
// extern UNK_TYPE rec_buff;
// extern UNK_TYPE pRecBuff;
// extern UNK_TYPE B_800E98BC;
// extern UNK_TYPE B_800E98C0;
// extern UNK_TYPE B_800E98C4;
// extern UNK_TYPE oldCont;
// extern UNK_TYPE RecPos;
// extern UNK_TYPE PlayPos;
// extern UNK_TYPE WaitTime;
// extern UNK_TYPE max_rec;
// extern UNK_TYPE replay_player;
// extern UNK_TYPE B_800E9910;
// extern UNK_TYPE B_800E9914;
// extern UNK_TYPE B_800E9918;
// extern UNK_TYPE B_800E9924;
// extern UNK_TYPE B_800E9928;
// extern UNK_TYPE B_800E992C;
// extern UNK_TYPE B_800E9930;
// extern UNK_TYPE B_800E9934;
// extern UNK_TYPE B_800E9938;
// extern UNK_TYPE B_800E993C;
// extern UNK_TYPE B_800E993E;
// extern UNK_TYPE B_800E9940;
// extern UNK_TYPE B_800E9944;
// extern UNK_TYPE B_800E9948;
// extern UNK_TYPE B_800E994C;
// extern UNK_TYPE B_800E9950;
// extern UNK_TYPE B_800E9954;
// extern UNK_TYPE B_800E9958;
// extern UNK_TYPE B_800E995C;
// extern UNK_TYPE B_800E9960;
// extern UNK_TYPE B_800E9964;
// extern UNK_TYPE B_800E9968;
// extern UNK_TYPE B_800E996C;
// extern UNK_TYPE B_800E9970;
// extern UNK_TYPE B_800E9980;
// extern UNK_TYPE B_800E9984;
// extern UNK_TYPE B_800E9988;
// extern UNK_TYPE B_800E998C;
// extern UNK_TYPE B_800E9990;
// extern UNK_TYPE B_800E9994;
// extern UNK_TYPE B_800E9998;
// extern UNK_TYPE B_800E99A0;
// extern UNK_TYPE B_800E99B8;
// extern UNK_TYPE B_800E99C0;
// extern UNK_TYPE B_800E99C4;
// extern UNK_TYPE B_800E99D0;
// extern UNK_TYPE B_800E9B80;
// extern UNK_TYPE B_800E9B84;
// extern UNK_TYPE B_800E9B88;
// extern UNK_TYPE B_800E9B90;
// extern UNK_TYPE B_800E9B94;

// extern UNK_TYPE aiRootP;
// extern UNK_TYPE B_800E9BB4;
extern s16 B_800E9BB6;
extern struct_ai_char_data ai_char_data[AI_CHAR_DATA_LEN];
// extern UNK_TYPE B_800EA0D0;
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
// extern UNK_TYPE B_800EB660;

extern enum_main_no main_no; /* Original name: main_no */
extern Gfx* gGfxHead; /* Original name: gp */ // main display list head
extern u16 gControllerHoldButtons[MAXCONTROLLERS+1];
// extern UNK_TYPE B_800EBD02;
// extern UNK_TYPE B_800EBD03;
// extern UNK_TYPE B_800EBD04;
// extern UNK_TYPE B_800EBD05;
// extern UNK_TYPE B_800EBD07;
// extern UNK_TYPE B_800EBD0B;
extern u32 PlayTime;
extern u8 aiNext[]; // maybe a struct?
extern u8 main_joy[];
extern OSThread sGraphicThread;
extern OSMesg B_800EBED0[8];

extern s16 B_800ED430;

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
// extern UNK_TYPE B_800F3E32;
// extern UNK_TYPE aiRollFinal;
extern OSMesgQueue B_800F3E38;
extern struct_watchGame *watchGame;
extern u8 aiFlagCnt;
extern u16 aiGoalX;
extern struct struct_watchMenu *watchMenu;
extern OSMesg B_800F3E60[1];
extern u16 gControllerPrevHoldButtons[MAXCONTROLLERS+1];
// extern UNK_TYPE B_800F3E6E;
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
extern OSMesgQueue B_800F4898;

extern u16 joygam[4];

extern u16 joycur[MAXCONTROLLERS+1];
extern struct_ai_param ai_param[AI_PARAM_LEN1][AI_PARAM_LEN2];
extern s32 MissRate;
extern OSContStatus B_800F5358[4];

// extern UNK_TYPE B_800F6C71;
// extern UNK_TYPE B_800F6CD4;
extern u16 joyflg[MAXCONTROLLERS];
// extern UNK_TYPE B_800F6CE0;

extern struct_evs_cfg_4p evs_cfg_4p;
extern s32 s_hard_mode; // maybe bool?
// extern UNK_TYPE attack_sprite_address;
extern STACK(B_800F7490, 0xC00);
// extern UNK_TYPE B_800F8C90;

// extern UNK_TYPE aiHiErR;
// extern UNK_TYPE B_800FAD30;
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
extern OSMesgQueue *B_800FAF94;

// extern UNK_TYPE aiHiEraseCtr;
extern STACK(B_800FAFA0, 0x400);
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
extern STACK(B_801136F0, 0x10000);
extern enum_evs_gamemode evs_gamemode;

extern struct_game_state_data game_state_data[4]; /* Original name: game_state_data */


#if VERSION_CN || VERSION_GW
extern s32 D_800BEF08_cn;
#endif

#endif

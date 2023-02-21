#ifndef MAIN_SEGMENT_VARIABLES_H
#define MAIN_SEGMENT_VARIABLES_H

#include "libultra.h"
#include "libc/stdint.h"
#include "libc/stdbool.h"
#include "PR/sched.h"
#include "unknown_structs.h"
#include "unk.h"
#include "alignment.h"


// data

extern s32 D_80088100;
extern s8 D_80088104[];
#if VERSION_CN
extern s32 D_80092EA8_cn;
extern bool D_80092EAC_cn;
// u32 D_80092EB0_cn[];
extern bool D_80092F10_cn;
#endif

extern Vp D_80088130;
extern s32 D_80088140;
extern Gfx D_80088150[];
extern Gfx D_800881B8[];
extern Gfx S2Spriteinit_dl[];
extern Gfx D_80088228[];
extern Gfx D_80088308[];
extern Gfx D_80088328[];

extern s8 evs_stereo;
extern u8 evs_seqence;
extern u8 evs_seqnumb;
extern u8 evs_playcnt;
extern u8 evs_keyrept[];
extern u8 evs_gamespeed; /* Original name: evs_gamespeed */
extern s8 evs_score_flag;
extern s8 evs_story_flg;
extern s8 evs_story_no;
extern s8 evs_story_level;
extern u8 evs_secret_flg[2];
extern u8 evs_one_game_flg; // maybe part of a struct?
extern u8 evs_level_21; /* Original name: evs_level_21 */
#ifndef M2CTX
extern s8 evs_manual_no;
#else
extern enum_evs_manual_no evs_manual_no;
#endif
extern s32 evs_high_score;
extern s32 evs_vs_count;
extern u8 FlyingCnt[];
// extern UNK_TYPE D_8008841D;
extern UNK_TYPE1 GameSpeed[4];
extern u8 FallSpeed[];
// extern UNK_TYPE D_8008846C;
extern s32 mti;
// extern UNK_TYPE D_80088484;
// extern UNK_TYPE aiVirusLevel;
// extern UNK_TYPE D_800884C0;
extern u8 aiSlideFSpeed[][3];
// extern UNK_TYPE D_800884F0;
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
// extern UNK_TYPE D_80088660;
// extern UNK_TYPE D_800890E0;
// extern UNK_TYPE D_800897A0;
// extern UNK_TYPE D_800897A2;
// extern UNK_TYPE D_800897A8;
// extern UNK_TYPE D_800899A8;
// extern UNK_TYPE D_8008CF90;
// extern UNK_TYPE D_8008CFA0;
extern s32 D_8008CFE0;

// extern UNK_TYPE D_8008CFF0;
// extern UNK_TYPE D_8008CFF4;
// extern UNK_TYPE D_8008CFF8;
// extern UNK_TYPE cont_table;
// extern UNK_TYPE D_8008D024;
// extern UNK_TYPE D_8008D028;
// extern UNK_TYPE etc_parts_tbl;
// extern UNK_TYPE D_8008D08C;
// extern UNK_TYPE D_8008D0A8;
// extern UNK_TYPE D_8008D0AC;
// extern UNK_TYPE D_8008D0B0;
// extern UNK_TYPE D_8008D0B8;
// extern UNK_TYPE D_8008D0BC;
extern UNK_TYPE4 x2p[];
extern UNK_TYPE4 x4p[];
// extern UNK_TYPE D_8008D0D8;
extern Gfx etc_setup[];
// extern UNK_TYPE D_8008D183;
// extern UNK_TYPE D_8008D187;
// extern UNK_TYPE D_8008D18B;
// extern UNK_TYPE D_8008D1B3;
// extern UNK_TYPE D_8008D1B7;
// extern UNK_TYPE D_8008D1BB;
// extern UNK_TYPE D_8008D1E0;
// extern UNK_TYPE D_8008D1F4;
// extern UNK_TYPE D_8008D248;
// extern UNK_TYPE D_8008D290;
// extern UNK_TYPE D_8008D2D0;
// extern UNK_TYPE D_8008D500;
// extern UNK_TYPE D_8008E1B0;
// extern UNK_TYPE D_8008E290;
// extern UNK_TYPE D_8008E340;
// extern UNK_TYPE D_8008E358;
// extern UNK_TYPE D_8008E364;
// extern UNK_TYPE D_8008E370;
// extern UNK_TYPE D_8008E380;
// extern UNK_TYPE D_8008E398;
// extern UNK_TYPE D_8008E3B8;
// extern UNK_TYPE D_8008E3BC;
// extern UNK_TYPE D_8008E3C0;
// extern UNK_TYPE D_8008E400;
// extern UNK_TYPE D_8008E420;
// extern UNK_TYPE D_8008E454;
// extern UNK_TYPE D_8008E480;
// extern UNK_TYPE D_8008E490;
// extern UNK_TYPE D_8008E4A0;
// extern UNK_TYPE D_8008E4AC;
// extern UNK_TYPE D_8008E4DC;
// extern UNK_TYPE D_8008E4F0;
// extern UNK_TYPE D_8008E508;
// extern UNK_TYPE D_8008E538;
// extern UNK_TYPE D_8008E540;
// extern UNK_TYPE D_8008E548;
// extern UNK_TYPE D_8008E554;
// extern UNK_TYPE D_8008E558;
// extern UNK_TYPE D_8008E564;
// extern UNK_TYPE D_8008E568;
// extern UNK_TYPE D_8008E574;
// extern UNK_TYPE D_8008E57C;
// extern UNK_TYPE D_8008E584;
// extern UNK_TYPE D_8008E590;
// extern UNK_TYPE D_8008E598;
// extern UNK_TYPE D_8008E5A0;
// extern UNK_TYPE D_8008E5B0;
// extern UNK_TYPE D_8008E5B4;
extern s32 D_8008E5D0;
// extern UNK_TYPE D_8008E5E0;
extern Gfx alpha_texture_init_dl[];
extern Gfx normal_texture_init_dl[];
// extern UNK_TYPE D_8008E728;
extern Gfx D_8008E748[];

// extern UNK_TYPE D_8008E8C0;
// extern UNK_TYPE D_80094350;
// extern UNK_TYPE D_8009F870;
// extern UNK_TYPE D_800A0E78;
extern u8 font_grade_tex[];
// extern UNK_TYPE D_800A3AD0;
// extern UNK_TYPE D_800A3BD0;
extern u16 char_code_tbl[];
extern u16 D_800A6D90[];
// extern UNK_TYPE D_800A6F70;
extern u8 virus_anime_table[3][4];
// extern UNK_TYPE D_800A6F8C;
// extern UNK_TYPE D_800A6F90;
extern s32 rotate_table_474[];
extern s32 rotate_mtx_475[];
extern s32 D_800A6FC4;
// extern UNK_TYPE D_800A6FC8;
extern char _mesPassword[];
extern char _mesEasyCont[];
extern char _mesEasyNoCont[];
extern char _mesNormalCont[];
extern char _mesNormalNoCont[];
extern char _mesHardCont[];
extern char _mesHardNoCont[];
extern char _mesSHardCont[];
extern char _mesSHardNoCont[];
// extern UNK_TYPE D_800A7354;
extern u8 D_800A7360[];
// extern UNK_TYPE D_800A7374;
// extern UNK_TYPE D_800A7378;
// extern UNK_TYPE D_800A7379;
// extern UNK_TYPE D_800A737A;
// extern UNK_TYPE D_800A737B;
extern s32 title_demo_flg;
extern s32 title_demo_no; /* Original name: title_demo_no */
extern s32 title_manual_no;
extern s32 title_exit_flag; /* Original name: title_exit_flag */
// extern UNK_TYPE D_800A73C0;
// extern UNK_TYPE D_800A76C0;
extern u8 changestar_tex[];
extern UNK_TYPE title_bmp_tbl[3];
// extern UNK_TYPE D_800A8ACC;
extern char st_staffroll_txt[];
// extern UNK_TYPE D_800A923C;
// extern UNK_TYPE D_800A9278;
// extern UNK_TYPE D_800A92C0;
// extern UNK_TYPE D_800A92D8;
// extern UNK_TYPE D_800A9314;
// extern UNK_TYPE D_800A935C;
// extern UNK_TYPE D_800A9390;
// extern UNK_TYPE D_800A93B0;
// extern UNK_TYPE D_800A93F0;
// extern UNK_TYPE D_800A9418;
// extern UNK_TYPE D_800A9444;
// extern UNK_TYPE D_800A9484;
// extern UNK_TYPE D_800A94D4;
// extern UNK_TYPE D_800A9520;
// extern UNK_TYPE D_800A9558;
// extern UNK_TYPE D_800A959C;
// extern UNK_TYPE D_800A95D4;
// extern UNK_TYPE D_800A95EC;
// extern UNK_TYPE D_800A962C;
// extern UNK_TYPE D_800A965C;
// extern UNK_TYPE D_800A96A0;
// extern UNK_TYPE D_800A96D8;
// extern UNK_TYPE D_800A9720;
// extern UNK_TYPE D_800A9764;
// extern UNK_TYPE D_800A97AC;
// extern UNK_TYPE D_800A97EC;
// extern UNK_TYPE D_800A9838;
// extern UNK_TYPE D_800A9878;
// extern UNK_TYPE D_800A9890;
// extern UNK_TYPE D_800A98D4;
// extern UNK_TYPE D_800A9918;
// extern UNK_TYPE D_800A9930;
// extern UNK_TYPE D_800A9974;
// extern UNK_TYPE D_800A99B0;
// extern UNK_TYPE D_800A99EC;
// extern UNK_TYPE D_800A9A18;
// extern UNK_TYPE D_800A9A50;
// extern UNK_TYPE D_800A9A94;
// extern UNK_TYPE D_800A9ACC;
// extern UNK_TYPE D_800A9AF4;
// extern UNK_TYPE D_800A9B30;
// extern UNK_TYPE D_800A9B6C;
// extern UNK_TYPE D_800A9BB8;
// extern UNK_TYPE D_800A9BE0;
// extern UNK_TYPE D_800A9C18;
// extern UNK_TYPE D_800A9C58;
// extern UNK_TYPE D_800A9C74;
// extern UNK_TYPE D_800A9CA0;
// extern UNK_TYPE D_800A9CF0;
// extern UNK_TYPE D_800A9D20;
// extern UNK_TYPE D_800A9D5C;
// extern UNK_TYPE D_800A9DA0;
// extern UNK_TYPE D_800A9DDC;
// extern UNK_TYPE D_800A9DFC;
// extern UNK_TYPE D_800A9E44;
// extern UNK_TYPE D_800A9E7C;
// extern UNK_TYPE D_800A9EB8;
// extern UNK_TYPE D_800A9ED4;
// extern UNK_TYPE D_800A9EFC;
// extern UNK_TYPE D_800A9F48;
// extern UNK_TYPE D_800A9F7C;
// extern UNK_TYPE D_800A9FB4;
// extern UNK_TYPE D_800A9FD4;
// extern UNK_TYPE D_800AA014;
// extern UNK_TYPE D_800AA040;
// extern UNK_TYPE D_800AA07C;
// extern UNK_TYPE D_800AA09C;
// extern UNK_TYPE D_800AA0C4;
// extern UNK_TYPE D_800AA104;
// extern UNK_TYPE D_800AA130;
// extern UNK_TYPE D_800AA168;
// extern UNK_TYPE D_800AA194;
// extern UNK_TYPE D_800AA1BC;
// extern UNK_TYPE D_800AA200;
// extern UNK_TYPE D_800AA238;
// extern UNK_TYPE D_800AA26C;
// extern UNK_TYPE D_800AA29C;
// extern UNK_TYPE D_800AA2C4;
// extern UNK_TYPE D_800AA300;
// extern UNK_TYPE D_800AA318;
// extern UNK_TYPE D_800AA334;
// extern UNK_TYPE D_800AA354;
// extern UNK_TYPE D_800AA398;
// extern UNK_TYPE D_800AA3DC;
// extern UNK_TYPE D_800AA41C;
// extern UNK_TYPE D_800AA454;
// extern UNK_TYPE D_800AA474;
// extern UNK_TYPE D_800AA494;
// extern UNK_TYPE D_800AA4DC;
// extern UNK_TYPE D_800AA4EC;
// extern UNK_TYPE D_800AA528;
// extern UNK_TYPE D_800AA538;
// extern UNK_TYPE D_800AA570;
// extern UNK_TYPE D_800AA5AC;
// extern UNK_TYPE D_800AA5C4;
// extern UNK_TYPE D_800AA604;
// extern UNK_TYPE D_800AA63C;
// extern UNK_TYPE D_800AA668;
// extern UNK_TYPE D_800AA688;
// extern UNK_TYPE D_800AA6CC;
// extern UNK_TYPE D_800AA714;
// extern UNK_TYPE D_800AA758;
// extern UNK_TYPE D_800AA778;
// extern UNK_TYPE D_800AA7C4;
// extern UNK_TYPE D_800AA808;
// extern UNK_TYPE D_800AA844;
// extern UNK_TYPE D_800AA864;
// extern UNK_TYPE D_800AA894;
// extern UNK_TYPE D_800AA8CC;
// extern UNK_TYPE D_800AA8F0;
// extern UNK_TYPE D_800AA928;
// extern UNK_TYPE D_800AA96C;
// extern UNK_TYPE D_800AA9A8;
// extern UNK_TYPE D_800AA9E0;
// extern UNK_TYPE D_800AAA10;
// extern UNK_TYPE D_800AAA4C;
// extern UNK_TYPE D_800AAA80;
// extern UNK_TYPE D_800AAAA0;
// extern UNK_TYPE D_800AAAE0;
// extern UNK_TYPE D_800AAB18;
// extern UNK_TYPE D_800AAB5C;
// extern UNK_TYPE D_800AAB7C;
// extern UNK_TYPE D_800AABB4;
// extern UNK_TYPE D_800AABC8;
// extern UNK_TYPE D_800AABE0;
// extern UNK_TYPE D_800AAC10;
// extern UNK_TYPE D_800AAC5C;
// extern UNK_TYPE D_800AAC74;
// extern UNK_TYPE D_800AAC7C;
// extern UNK_TYPE D_800AAC80;
// extern UNK_TYPE D_800AAC84;
// extern UNK_TYPE D_800AACCC;
// extern UNK_TYPE D_800AACD0;
// extern UNK_TYPE D_800AACD4;
extern enum_story_proc_no story_proc_no; /* Original name: story_proc_no */
// extern UNK_TYPE D_800AACF0;
extern char *EndingLastMessage; /* Original name: EndingLastMessage */
extern s32 D_800AAD08;
extern s32 D_800AAD0C;
extern UNK_TYPE4 story_zoom;
extern UNK_TYPE4 D_800AAD14;
extern s32 story_spot_cnt;
extern UNK_TYPE4 D_800AAD1C;
extern UNK_TYPE4 story_message_on;
extern UNK_TYPE4 D_800AAD24;
extern UNK_TYPE4 D_800AAD28;
extern s32 bgtime; /* Original name: bgtime */
extern s32 D_800AAD34;
// extern UNK_TYPE D_800AAD38;
extern void *D_800AAD3C;
// extern UNK_TYPE D_800AAD40;
extern s32 objMtx_FF;
// extern UNK_TYPE D_800AAD48;
// extern UNK_TYPE D_800AAD4C;
// extern UNK_TYPE D_800AAD50;
extern Vp D_800AAD58;
extern Gfx D_800AAD68[];
// extern UNK_TYPE D_800AAE00;
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

extern const Gfx fade_normal_texture_init_dl[];


// bss

extern u8 B_800B3640[0x31000];
extern u32 mt[0x270];
extern struct_game_state_data *pGameState;
// extern UNK_TYPE B_800E5008;
extern s32 delpos_cnt;
// extern UNK_TYPE B_800E519C;
extern s32 last_flash;
// extern UNK_TYPE B_800E51B0;
// extern UNK_TYPE B_800E53B0;
extern s32 binCount;
// extern UNK_TYPE cont_bg_flg;
// extern UNK_TYPE etcTexAddress;

// extern UNK_TYPE logo_ofsY;
// extern UNK_TYPE etc_mode;
// extern UNK_TYPE g_etc_work;
// extern UNK_TYPE B_800E541C;
// extern UNK_TYPE B_800E5420;
// extern UNK_TYPE B_800E5424;
// extern UNK_TYPE B_800E5428;
// extern UNK_TYPE B_800E54A8;
// extern UNK_TYPE B_800E54C8;
extern Mtx etc_viewMtx;
// extern UNK_TYPE B_800E5860;
// extern UNK_TYPE B_800E5890;
// extern UNK_TYPE B_800E58B0;
// extern UNK_TYPE B_800E58B4;
// extern UNK_TYPE B_800E58B8;
// extern UNK_TYPE B_800E58BC;
// extern UNK_TYPE B_800E58BE;
// extern UNK_TYPE B_800E58C0;
// extern UNK_TYPE B_800E58C2;
// extern UNK_TYPE B_800E58C4;
// extern UNK_TYPE B_800E58C6;
// extern UNK_TYPE B_800E5910;
// extern UNK_TYPE B_800E5914;
// extern UNK_TYPE B_800E5918;
// extern UNK_TYPE B_800E591C;
// extern UNK_TYPE B_800E5920;
// extern UNK_TYPE B_800E5924;
// extern UNK_TYPE B_800E5928;
// extern UNK_TYPE B_800E592C;
// extern UNK_TYPE B_800E5930;
// extern UNK_TYPE B_800E5934;
// extern UNK_TYPE B_800E5938;
// extern UNK_TYPE B_800E5968;
// extern UNK_TYPE B_800E5969;
// extern UNK_TYPE B_800E596C;
// extern UNK_TYPE B_800E5970;
// extern UNK_TYPE B_800E5974;
// extern UNK_TYPE B_800E5978;
// extern UNK_TYPE B_800E597C;
extern UNK_PTR heapTop; /* Original name: heapTop */
extern TiTexData *_texAll;
extern TiTexData *_texKaSa;
extern s32 title_mode_type;
extern s32 title_fade_count; /* Original name: title_fade_count */
extern s32 title_fade_step;
// extern UNK_TYPE B_800E59B0;
// extern UNK_TYPE B_800E59B4;
// extern UNK_TYPE B_800E59B8;
// extern UNK_TYPE B_800E59BC;
// extern UNK_TYPE B_800E59C0;
// extern UNK_TYPE B_800E59C4;
// extern UNK_TYPE B_800E59C8;
// extern UNK_TYPE B_800E59CC;
// extern UNK_TYPE B_800E59D0;
// extern UNK_TYPE B_800E59D4;
extern s32 title_time;
extern s32 title_wait;
extern void **title_data;
extern void *title_bmp_data;
extern void **lws_data;
extern void *lws_scene;
extern MessageWnd mess_st;
extern MessageWnd mess_roll_st;
// extern UNK_TYPE B_800E5AF0;
// extern UNK_TYPE B_800E5EF0;
// extern UNK_TYPE B_800E5EF4;
// extern UNK_TYPE B_800E5EF8;
// extern UNK_TYPE loop_flg;
// extern UNK_TYPE story_staff_roll;
// extern UNK_TYPE story_norm;
extern Mtx story_viewMtx; /* Original name: story_viewMtx */
extern struct_800F1DF8 story_objectMtx[2];
extern void *B_800E8750;
extern void *bgGraphic; /* Original name: bgGraphic */
extern void *B_800E87AC;
extern void *B_800E87B0;
// extern UNK_TYPE B_800E87B4;
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
// extern UNK_TYPE B_800E9BC0;
// extern UNK_TYPE B_800EA0D0;
extern u8 success;
// extern UNK_TYPE B_800EA284;
extern struct_800EA290 B_800EA290;
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
extern struct_800EB670 B_800EB670;
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
extern OSThread B_800EBD20;
extern OSMesg B_800EBED0[8];

extern s16 B_800ED430;
extern STACK(B_800ED440, 0x2000);
extern struct_gameBackup *gameBackup[2];
extern u8 CapsMagazine[];
// extern UNK_TYPE attack_effect_idx;
// extern UNK_TYPE B_800EF54C;

extern s32 fool_mode; // maybe bool?
extern u16 joycur1; /* Original name: joycur1 */
extern s8 decide;
extern struct_800EF560 evs_mem_data[9];

extern s32 _menuMain_lastSelect[8]; // probably an enum
extern enum_evs_gamesel evs_gamesel; /* Original name: evs_gamesel */
extern STACK(B_800EFCE0, 0x2000);
extern u8 evs_playmax; /* Original name: evs_playmax */
// extern UNK_TYPE B_800F1CE9;
extern struct_800F1DF8 *pObjectMtx;
extern s32 evs_default_name[];
extern u16 joycur2; /* Original name: joycur2 */
extern STACK(B_800F1E30, 0x2000);
// extern UNK_TYPE aiHiErB;
// extern UNK_TYPE B_800F3E32;
// extern UNK_TYPE aiRollFinal;
extern OSMesgQueue B_800F3E38;
extern struct_watchGame *watchGame;
extern u8 aiFlagCnt;
extern s16 aiGoalX;
extern struct_watchMenu *watchMenu;
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
// extern UNK_TYPE B_800F3E90;
// extern UNK_TYPE B_800F3E94;
// extern UNK_TYPE B_800F3E98;
// extern UNK_TYPE B_800F3E9C;
// extern UNK_TYPE B_800F3EA0;
extern struct_watchManual *watchManual; /* Original name: watchManual */
extern u8 aiRootCnt;
extern OSMesgQueue B_800F4898;
extern struct_800FAF98_unk_64 B_800F48B0;
extern UNK_TYPE2 joygam[4];

extern u16 joycur[MAXCONTROLLERS+1];
// extern UNK_TYPE B_800F48D0;
extern s32 MissRate;
extern OSContStatus B_800F5358[4];
extern u8 aiFlag[];
// extern UNK_TYPE aiRoot;
// extern UNK_TYPE B_800F6C71;
// extern UNK_TYPE B_800F6CD4;
extern u16 joyflg[MAXCONTROLLERS];
// extern UNK_TYPE B_800F6CE0;
extern struct_virus_map_data virus_map_data[4];
extern struct_virus_map_disp_order virus_map_disp_order[4];
extern struct_800F7470 evs_cfg_4p;
extern s32 s_hard_mode; // maybe bool?
// extern UNK_TYPE B_800F748C;
extern STACK(B_800F7490, 0xC00);
// extern UNK_TYPE B_800F8C90;

extern STACK(B_800F8CE0, 0x2000);
// extern UNK_TYPE aiHiErR;
// extern UNK_TYPE B_800FAD30;
extern UNK_TYPE1 joygmf[4];
extern s16 aiGoalY;
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
extern s8 aiMoveSF; // maybe bool?
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


#ifdef VERSION_CN
extern s32 D_800BEF08_cn;

extern struct_8010ACB0_cn *B_800CA234_cn;
extern struct_8010ACB0_cn *B_800CA298_cn;
extern struct_8010ACB0_cn B_8010ACB0_cn[]; // maybe length 4?
#endif

#endif

#ifndef MAIN1X_H
#define MAIN1X_H

#include "libultra.h"
#include "main.h"

// TODO: use MAXCONTROLLERS instead?
#define STRUCT_EVS_CFG_4P_COUNT 4

typedef struct struct_evs_cfg_4p {
    /* 0x00 */ u8 p4_team[STRUCT_EVS_CFG_4P_COUNT]; /* Original name: p4_team */
    /* 0x04 */ u8 p4_lv[STRUCT_EVS_CFG_4P_COUNT]; /* Original name: p4_lv */
    /* 0x08 */ u8 p4_fl_lv[STRUCT_EVS_CFG_4P_COUNT]; /* Original name: p4_fl_lv */
    /* 0x0C */ u8 p4_no[STRUCT_EVS_CFG_4P_COUNT]; /* Original name: p4_no */
    /* 0x10 */ u8 p4_sp[STRUCT_EVS_CFG_4P_COUNT]; /* Original name: p4_sp */
    /* 0x14 */ u8 unk_14;
    /* 0x15 */ u8 unk_15;
} struct_evs_cfg_4p; // size = 0x16

#if 0
typedef struct /* struct_record_c_66 */ {
    // total size: 0x16
    unsigned char p4_team[4]; // offset 0x0, size 0x4
    unsigned char p4_lv[4]; // offset 0x4, size 0x4
    unsigned char p4_fl_lv[4]; // offset 0x8, size 0x4
    unsigned char p4_no[4]; // offset 0xC, size 0x4
    unsigned char p4_sp[4]; // offset 0x10, size 0x4
    unsigned char p4_st; // offset 0x14, size 0x1
    unsigned char p4_m; // offset 0x15, size 0x1
} struct_record_c_66;
#endif


typedef enum enum_evs_manual_no {
    /* 0 */ EVS_MANUAL_NO_0,
    /* 1 */ EVS_MANUAL_NO_1,
    /* 2 */ EVS_MANUAL_NO_2,
    /* 3 */ EVS_MANUAL_NO_3,
    /* 4 */ EVS_MANUAL_NO_4,
    /* 5 */ EVS_MANUAL_NO_5
} enum_evs_manual_no;

typedef enum enum_evs_gamesel {
    /* 0 */ ENUM_EVS_GAMESEL_0,
    /* 1 */ ENUM_EVS_GAMESEL_1,
    /* 2 */ ENUM_EVS_GAMESEL_2,
    /* 3 */ ENUM_EVS_GAMESEL_3,
    /* 4 */ ENUM_EVS_GAMESEL_4,
    /* 5 */ ENUM_EVS_GAMESEL_5,
    /* 6 */ ENUM_EVS_GAMESEL_6,
    /* 7 */ ENUM_EVS_GAMESEL_MAX
} enum_evs_gamesel;


enum_main_no main11(void);
void adjust_story_ai(void);
enum_main_no main12(void);


// .data

extern u8 evs_stereo;
extern u8 evs_seqence;
extern u8 evs_seqnumb;
extern u8 evs_playcnt;
extern u8 evs_keyrept[];
extern u8 evs_gamespeed; /* Original name: evs_gamespeed */
extern u8 evs_score_flag;
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
extern u32 evs_high_score;
extern s32 evs_vs_count;
extern u8 FlyingCnt[];
extern u8 BonusWait[3][3];
// extern UNK_TYPE D_8008842C;
extern s8 GameSpeed[4];
extern u8 FallSpeed[];
extern u8 Score1p[][6];

// COMMON

extern u8 evs_playmax;
extern enum_evs_gamesel evs_gamesel;
extern s32 evs_default_name[8];
extern struct_evs_cfg_4p evs_cfg_4p;
extern u8 evs_select_name_no[2];
extern u32 evs_game_time;

#endif

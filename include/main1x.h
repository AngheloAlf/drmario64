#ifndef MAIN1X_H
#define MAIN1X_H

#include "libultra.h"
#include "main.h"

typedef enum enum_evs_manual_no {
    /* 0 */ EVS_MANUAL_NO_0,
    /* 1 */ EVS_MANUAL_NO_1,
    /* 2 */ EVS_MANUAL_NO_2,
    /* 3 */ EVS_MANUAL_NO_3,
    /* 4 */ EVS_MANUAL_NO_4,
    /* 5 */ EVS_MANUAL_NO_5
} enum_evs_manual_no;


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


#endif

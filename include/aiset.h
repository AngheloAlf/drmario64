#ifndef AISET_H
#define AISET_H

#include "libultra.h"
#include "libc/stdbool.h"
#include "ai.h"
#include "gamemap.h"
#include "unk.h"

struct struct_game_state_data;

#define AI_PARAM_LEN1 6
#define AI_PARAM_LEN2 8

#define AI_CHAR_DATA_LEN (12+4)

typedef struct struct_ai_param {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ s16 unk_0E;
    /* 0x10 */ s16 unk_10;
    /* 0x12 */ s16 unk_12;
    /* 0x14 */ s16 unk_14;
    /* 0x16 */ s16 unk_16;
    /* 0x18 */ s16 unk_18;
    /* 0x1A */ s16 unk_1A;
    /* 0x1C */ s16 unk_1C;
    /* 0x1E */ s16 unk_1E;
    /* 0x20 */ s16 unk_20;
    /* 0x22 */ s16 unk_22;
    /* 0x24 */ s16 unk_24;
    /* 0x26 */ s16 unk_26;
    /* 0x28 */ s16 unk_28;
    /* 0x2A */ s16 unk_2A;
    /* 0x2C */ s16 unk_2C;
    /* 0x2E */ s16 unk_2E;
    /* 0x30 */ s16 unk_30;
    /* 0x32 */ s16 unk_32;
    /* 0x34 */ s16 unk_34;
    /* 0x36 */ s16 unk_36;
} struct_ai_param; // size = 0x38

#define STRUCT_AI_CHAR_DATA_LEN 16
#define STRUCT_AI_CHAR_DATA_LEN2 8

typedef struct struct_ai_char_data {
    /* 0x00 */ UNK_TYPE1 unk_00;
    /* 0x01 */ UNK_TYPE1 speed;
    /* 0x02 */ UNK_TYPE2 unk_02;
    /* 0x04 */ s8 performance[STRUCT_AI_CHAR_DATA_LEN2];
    /* 0x0C */ s8 unk_0C[STRUCT_AI_CHAR_DATA_LEN];
    /* 0x1C */ s16 unk_1C[STRUCT_AI_CHAR_DATA_LEN];
    /* 0x3C */ s8 unk_3C[STRUCT_AI_CHAR_DATA_LEN];
    /* 0x4C */ s16 unk_4C[STRUCT_AI_CHAR_DATA_LEN];
} struct_ai_char_data; // size = 0x6C

typedef struct Unk_AIFEntry {
    /* 0x0 */ u8 unk_0;
    /* 0x1 */ u8 unk_1;
} Unk_AIFEntry; // size = 0x2

void func_8002EB00(struct struct_game_state_data *gameStateDataRef);
void aifMakeBlkWork(struct struct_game_state_data *gameStateDataRef);
#if VERSION_US || VERSION_GW || CC_CHECK
void aifMakeFlagSet(struct struct_game_state_data *gameStateDataRef);
#endif
void aifGameInit(void);
void aifFirstInit(void);
void aifMake(struct struct_game_state_data *gameStateDataRef);
bool aifMake2(struct struct_game_state_data * gameStateDataRef, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void aiHiruSideLineEraser(struct struct_game_state_data *gameStateDataRef);
// void func_8002F924();
bool aifEraseLineCore(s32 col, s32 row);
s32 aifRensaCheckCore(struct struct_game_state_data *gameStateDataRef, struct_aiFlag *aiFlagRef, u8 arg2, u8 arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9);
// void aifRensaCheck();
bool aifSearchLineCore(s32 arg0, s32 arg1, s32 arg2);
s32 aifMiniPointK3(u8 *arg0, u8 arg1, u8 *arg2, u8 arg3, u8 arg4, u8 arg5);
s32 aifMiniAloneCapNumber(u8 arg0, u8 arg1, u8 arg2, s32 arg3);
s32 aifMiniAloneCapNumberW(u8 arg0, u8 arg1, u8 arg2, s32 arg3);
s32 flash_virus(s32 col, s32 row);
bool search_Vflash(s32 arg0, s32 arg1, s32 arg2);
// void func_8003151C();
s32 aifSearchLineMS(struct_aiFlag *arg0, UNK_TYPE arg1, UNK_TYPE arg2, UNK_TYPE arg3, UNK_TYPE arg4, UNK_TYPE arg5, UNK_TYPE arg6, UNK_TYPE arg7);
void aiHiruAllPriSet(struct struct_game_state_data *gameStateDataRef);
void aiSetCharacter(struct struct_game_state_data *gameStateDataRef);
void aifFieldCopy(struct struct_game_state_data *gameStateDataRef);
// void func_80034310();
void aifPlaceSearch(void);
void aifMoveCheck(void);
// void aifTRecur();
void aifTRecurUP(u8 arg0, u8 arg1, u8 arg2);
// void aifYRecur();
void aifYRecurUP(u8 arg0, u8 arg1, u8 arg2);
void aifReMoveCheck(void);
void aifKeyMake(struct struct_game_state_data *gameStateDataRef);
void aifKeyOut(struct struct_game_state_data *gameStateDataRef);
s32 search_flash_3(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
s32 flash_special(void);
void aiCOM_MissTake(void);

// data

extern u8 D_80088490[];
extern u8 aiVirusLevel[][3];
extern u8 aiDownSpeed[][3];
extern u8 aiSlideFSpeed[][3];
extern u8 aiSlideSpeed[][3];
extern s8 aiDebugP1;
extern u8 capsGCnv_122[];
extern u8 capsCCnv_123[];
extern u8 aiLinePri[];
extern u8 srh_466[][2];
extern s16 bad_point[];
extern s16 bad_point2[];
extern s16 pri_point[];
extern s16 EraseLinP[];
extern f32 HeiEraseLinRate;
extern f32 WidEraseLinRate;
extern s16 HeiLinesAllp[];
extern s16 WidLinesAllp[];
extern s16 AloneCapP[];
extern s16 AloneCapWP[];
extern s32 OnVirusP;
extern s16 D_800885D0;
extern s16 RensaP;
extern s16 RensaMP;
extern s16 LPriP;
extern u8 BadLineRate[][8];
extern s16 WallRate[][8];
extern s32 tbl_2973[];
extern struct_ai_param ai_param_org[AI_PARAM_LEN1][AI_PARAM_LEN2];
extern struct_ai_char_data ai_char_data_org[AI_CHAR_DATA_LEN];

// COMMON

// TODO: consider moving the `ai*` variables to `ai.h` or merge that header with this one.

#define HEI_WEI_DATA_LEN 10

extern struct_ai_char_data ai_char_data[AI_CHAR_DATA_LEN];
extern struct_ai_param ai_param[AI_PARAM_LEN1][AI_PARAM_LEN2];

extern Unk_AIFEntry aiRecurData[GAME_MAP_ROWS+1][GAME_MAP_COLUMNS+2];
extern Unk_AIFEntry aiFieldData[GAME_MAP_ROWS][GAME_MAP_COLUMNS];
extern Unk_AIFEntry aif_field[GAME_MAP_ROWS][GAME_MAP_COLUMNS];

extern f32 aiRootP;
extern u8 aiRollFinal;
extern u8 aiSelCom;
extern u8 aiWall;
extern u8 hei_data[HEI_WEI_DATA_LEN];
extern u8 wid_data[HEI_WEI_DATA_LEN];
extern s16 aiHiErB;
extern u16 aiPriOfs;
extern s16 aiHiErY;
extern s16 aiHiErR;
extern u16 aiHiEraseCtr;
extern bool fool_mode;
extern bool s_hard_mode;
extern u32 PlayTime;
extern s32 MissRate;
extern u8 success;
extern u8 decide;
extern u8 aiFlagCnt;
extern u16 aiGoalX;
extern u16 aiGoalY;
extern u8 aiMoveSF; // maybe bool?
extern u8 aiNext[2]; // maybe a struct?
extern u8 aipn;
extern u8 aiRootCnt;
extern s8 aiSelSpeed;
extern u8 aiTEdgeCnt;
extern u8 aiYEdgeCnt;


#endif

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

// TODO: when adding enums remember to use those values in ai_char_data_org too
typedef struct struct_ai_char_data {
    /* 0x00 */ s8 wait_attack; /* Original name: wait_attack */
    /* 0x01 */ s8 speed; /* Original name: speed */
    /* 0x02 */ s16 luck; /* Original name: luck */ /* unused */
    /* 0x04 */ s8 performance[STRUCT_AI_CHAR_DATA_LEN2]; /* Original name: logic */
    /* 0x0C */ s8 condition[STRUCT_AI_CHAR_DATA_LEN]; /* Original name: condition */ /* TODO: enum */
    /* 0x1C */ s16 condition_param[STRUCT_AI_CHAR_DATA_LEN]; /* Original name: condition_param */ /* TODO: enum? */
    /* 0x3C */ s8 effect[STRUCT_AI_CHAR_DATA_LEN]; /* Original name: effect */ /* TODO: enum? */
    /* 0x4C */ s16 effect_param[STRUCT_AI_CHAR_DATA_LEN]; /* Original name: effect_param */ /* TODO: enum? */
} struct_ai_char_data; // size = 0x6C

// See `struct_game_state_data_blk`
typedef struct Unk_AIFEntry {
    /* 0x0 */ u8 co; /* Original name: co */
    /* 0x1 */ u8 st; /* Original name: st */
} Unk_AIFEntry; // size = 0x2

void aifMakeBlkWork(struct struct_game_state_data *uupw);
#if VERSION_US || VERSION_GW || CC_CHECK
void aifMakeFlagSet(struct struct_game_state_data *uupw);
#endif
void aifGameInit(void);
void aifFirstInit(void);
void aifMake(struct struct_game_state_data *uupw);
bool aifMake2(struct struct_game_state_data *uupw, s32 x, s32 y, s32 tateFlag, s32 revFlag);
void aiHiruSideLineEraser(struct struct_game_state_data *xpw);
bool aifEraseLineCore(s32 col, s32 row);
s32 aifRensaCheckCore(struct struct_game_state_data *uupw, struct_aiFlag *aiFlagRef, u8 mx, u8 my, u8 mco, u8 mst,
                      u8 sx, u8 sy, u8 sco, u8 sst);
s32 aifRensaCheck(struct struct_game_state_data *uupw, struct_aiFlag *af);
bool aifSearchLineCore(s32 mx, s32 my, s32 fg);
s32 aifMiniPointK3(u8 *tbl, u8 sub, u8 *elin, u8 flag, u8 tory, u8 ec);
s32 aifMiniAloneCapNumber(u8 x, u8 y, u8 f, s32 ec);
s32 aifMiniAloneCapNumberW(u8 x, u8 y, u8 f, s32 ec);

s32 aifSearchLineMS(struct_aiFlag *ag, UNK_TYPE mx, UNK_TYPE my, UNK_TYPE mco, UNK_TYPE sx, UNK_TYPE sy, UNK_TYPE sco,
                    UNK_TYPE ec);
void aiHiruAllPriSet(struct struct_game_state_data *gameStateDataRef);
void aiSetCharacter(struct struct_game_state_data *xpw);
void aifFieldCopy(struct struct_game_state_data *uupw);
void aifPlaceSearch(void);
void aifMoveCheck(void);
void aifTRecur(u8 x, u8 y, u8 cnt);
void aifTRecurUP(u8 x, u8 y, u8 cnt);
void aifYRecur(u8 x, u8 y, u8 cnt);
void aifYRecurUP(u8 x, u8 y, u8 cnt);
void aifReMoveCheck(void);
void aifKeyMake(struct struct_game_state_data *uupw);
void aifKeyOut(struct struct_game_state_data *gameStateDataRef);
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
extern u8 aiSelCom; // TODO: enum
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

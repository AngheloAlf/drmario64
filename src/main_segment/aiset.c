/**
 * Original filename: aiset.c
 */

#include "aiset.h"

#include "libc/assert.h"
#include "include_asm.h"
#include "macros_defines.h"

#include "dm_virus_init.h"
#include "gamemap.h"
#include "joy.h"
#include "main1x.h"
#include "nnsched.h"
#include "vr_init.h"

#define AIROOTP_CAP 100

s32 flash_special(void);
s32 flash_virus(s32 col, s32 row);

/**
 * Original name: ai_char_data
 */
struct_ai_char_data ai_char_data[AI_CHAR_DATA_LEN];

/**
 * Original name: ai_param
 */
struct_ai_param ai_param[AI_PARAM_LEN1][AI_PARAM_LEN2];

/**
 * Original name: aiRecurData
 */
Unk_AIFEntry aiRecurData[GAME_MAP_ROWS + 1][GAME_MAP_COLUMNS + 2];
/**
 * Original name: aiFieldData
 */
Unk_AIFEntry aiFieldData[GAME_MAP_ROWS][GAME_MAP_COLUMNS];
/**
 * Original name: aif_field
 */
Unk_AIFEntry aif_field[GAME_MAP_ROWS][GAME_MAP_COLUMNS];

/**
 * Original name: aiRootP
 */
f32 aiRootP;

/**
 * Original name: aiRollFinal
 */
u8 aiRollFinal;

/**
 * Original name: aiSelCom
 */
u8 aiSelCom;

/**
 * Original name: aiWall
 */
u8 aiWall;

/**
 * Original name: hei_data
 */
u8 hei_data[HEI_WEI_DATA_LEN];

/**
 * Original name: wid_data
 */
u8 wid_data[HEI_WEI_DATA_LEN];

/**
 * Original name: aiHiErB
 */
s16 aiHiErB;

/**
 * Original name: aiPriOfs
 */
u16 aiPriOfs;

/**
 * Original name: aiHiErY
 */
s16 aiHiErY;

/**
 * Original name: aiHiErR
 */
s16 aiHiErR;

/**
 * Original name: aiHiEraseCtr
 */
u16 aiHiEraseCtr;

/**
 * Original name: fool_mode
 */
bool fool_mode;

/**
 * Original name: s_hard_mode
 */
bool s_hard_mode;

/**
 * Original name: PlayTime
 */
u32 PlayTime;

/**
 * Original name: MissRate
 */
s32 MissRate;

/**
 * Original name: success
 */
u8 success;
/**
 * Original name: decide
 */
u8 decide;
/**
 * Original name: aiFlagCnt
 */
u8 aiFlagCnt;
/**
 * Original name: aiGoalX
 */
u16 aiGoalX;
/**
 * Original name: aiGoalY
 */
u16 aiGoalY;
/**
 * Original name: aiMoveSF
 */
u8 aiMoveSF;
/**
 * Original name: aiNext
 */
u8 aiNext[2];
/**
 * Original name: aipn
 */
u8 aipn;
/**
 * Original name: aiRootCnt
 */
u8 aiRootCnt;
/**
 * Original name: aiSelSpeed
 */
s8 aiSelSpeed;
/**
 * Original name: aiTEdgeCnt
 */
u8 aiTEdgeCnt;
/**
 * Original name: aiYEdgeCnt
 */
u8 aiYEdgeCnt;

/**
 * Original name: aiFlag
 */
struct_aiFlag aiFlag[AIFLAG_LEN];
/**
 * Original name: aiRoot
 */
struct_aiRoot aiRoot[AIROOT_LEN];

/**
 * Original name: pGameState
 */
static struct_game_state_data *pGameState;
/**
 * Original name: delpos_tbl
 */
static s32 delpos_tbl[100];
/**
 * Original name: delpos_cnt
 */
static s32 delpos_cnt;
/**
 * Original name: OnVirusP_org
 */
static s32 OnVirusP_org;
/**
 * Original name: last_flash
 */
static s32 last_flash;

// unused
u8 D_80088490[] = {
    0x03, 0x02, 0x01, 0x03, 0x02, 0x01, 0x02, 0x02, 0x01, 0x02, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
};

u8 aiVirusLevel[8][3] = {
    { 0x1E, 0x18, 0x12 }, { 0x1E, 0x18, 0x12 }, { 0x18, 0x13, 0xE }, { 0x12, 0xE, 0xA },
    { 0xE, 0xB, 8 },      { 6, 6, 6 },          { 1, 1, 1 },         { 6, 6, 6 },
};
u8 aiDownSpeed[8][3] = {
    { 7, 4, 4 }, { 7, 4, 4 }, { 7, 4, 4 }, { 7, 4, 4 }, { 7, 4, 4 }, { 4, 3, 2 }, { 1, 1, 1 }, { 7, 4, 4 },
};

u8 aiSlideFSpeed[8][3] = {
    {
        0x1E, // THINKLEVEL_0
        0x18, // THINKLEVEL_1
        0x12, // THINKLEVEL_2
    },
    {
        0x1E, // THINKLEVEL_0
        0x18, // THINKLEVEL_1
        0x12, // THINKLEVEL_2
    },
    {
        0x19, // THINKLEVEL_0
        0x14, // THINKLEVEL_1
        0x10, // THINKLEVEL_2
    },
    {
        0x15, // THINKLEVEL_0
        0x11, // THINKLEVEL_1
        0xD,  // THINKLEVEL_2
    },
    {
        0x11, // THINKLEVEL_0
        0xE,  // THINKLEVEL_1
        0xB,  // THINKLEVEL_2
    },
    {
        0xA, // THINKLEVEL_0
        6,   // THINKLEVEL_1
        4,   // THINKLEVEL_2
    },
    {
        1, // THINKLEVEL_0
        1, // THINKLEVEL_1
        1, // THINKLEVEL_2
    },
    {
        0x11, // THINKLEVEL_0
        0xE,  // THINKLEVEL_1
        0xB,  // THINKLEVEL_2
    },
};
static_assert(ARRAY_COUNT(aiSlideFSpeed[0]) == THINKLEVEL_MAX, "");

u8 aiSlideSpeed[8][3] = {
    { 0x1E, 0x16, 0xE }, { 0x1E, 0x16, 0xE }, { 0xF, 0xC, 0xA }, { 8, 7, 6 },
    { 5, 5, 5 },         { 5, 3, 2 },         { 1, 1, 1 },       { 5, 5, 5 },
};
s8 aiDebugP1 = THINKTYPE_INVALID;
u8 capsGCnv_122[] = {
    0, 1, 2, 3, 4, 8, 8, 5, 5, 6, 6, 7, 7, 9, 9, 0xA, 5, 5, 6, 6, 7, 7,
};
u8 capsCCnv_123[] = {
    0, 1, 2, 0, 1, 2,
};
u8 aiLinePri[] = {
    4, 3, 5, 2, 6, 1, 7, 0,
};
u8 srh_466[][2] = {
    { 1, 0 },
    { 0xFF, 0 },
    { 0, 1 },
    { 0, 0xFF },
};
s16 bad_point[] = {
    -0x5A, -0x10E, -0x168, -0x384, -0x384, -0x168, -0x10E, -0x5A,
};
s16 bad_point2[] = {
    -0x5A, -0x10E, -0x168, -0x2328, -0x2328, -0x168, -0x10E, -0x5A,
};
s16 pri_point[] = {
    0, 0xB4, 9, 0, 0x1F, 0, 0, 0, 0,
};
s16 EraseLinP[] = {
    0, 0x1E, 0x5A, 0xB4, 0x10E, 0x168, 0x21C, 0x21C, 0x21C,
};
f32 HeiEraseLinRate = 1.0f;
f32 WidEraseLinRate = 1.0f;

s16 HeiLinesAllp[] = {
    0x00, 0x00, 0x0E, 0x28, 0x2D, 0x2D, 0x2D, 0x2D, 0x2D,
};

s16 WidLinesAllp[] = { 0, 0, 0xE, 0x28, 0x2D, 0x2D, 0x2D, 0x2D, 0x2D };
s16 AloneCapP[] = { 0, -0x3C, -0x46, -0x5A, -0x50, -0x64 };
s16 AloneCapWP[] = { 0, 0, 0, 0, 0, 0 };
s32 OnVirusP = 0;

// unused
s16 D_800885D0 = 0x0028;

s16 RensaP = 0x12C;
s16 RensaMP = -0x12C;
s16 LPriP = 0;
u8 BadLineRate[][8] = {
    { 6, 7, 8, 9, 9, 8, 7, 6 },
    { 6, 7, 8, 9, 9, 8, 7, 6 },
    { 2, 2, 4, 7, 7, 4, 2, 2 },
    { 1, 1, 2, 4, 4, 2, 1, 1 },
};
s16 WallRate[][8] = {
    { 0xA, 0xA, 0xA, 0xA, 0xA, 0xA, 0xA, 0xA },
    { 0x40, 0x40, 0x20, 0x10, 8, 4, 2, 1 },
    { 1, 2, 4, 8, 0x10, 0x20, 0x40, 0x40 },
    { 0x40, 0x40, 0x10, 4, 4, 0x10, 0x40, 0x40 },
};
s32 tbl_2973[] = { -3, -2, -1, 0, 1, 2, 3, 0, 0, 0 };
struct_ai_param ai_param_org[AI_PARAM_LEN1][AI_PARAM_LEN2] = {
    {
        { 0, 0, -0x32, 0,     0x64,   0x64, 0xA, -0xAA, -0xBE, -0xE6, -0xFA, 0, 0, 0,
          0, 0, 0,     0x3E8, -0x190, 0,    0,   0,     0xC2,  0x1EA, 0x1EA, 0, 0, 0 },
        { 5, 0xA, 0x1E, 0, 0x64, 0x64, 0xA, -0x46, -0x5A, -0x50, -0x64, 0,   0,    0,
          0, 0,   0,    0, 0,    0,    0,   0,     0xE,   0x28,  0x2D,  0xE, 0x28, 0x2D },
        { 0x83, 0x7EE, 0x1E,  0, 0x190, 0x190, 0xA, -0xAA, -0xBE, -0xE6, -0xFA, 0, 0, 0,
          0,    0,     0xBB8, 0, 0,     0,     0,   0,     0xE,   0x28,  0x2D,  0, 0, 0 },
        { 0x83, 0x7EE, 0x1E,  0, 0x190, 0x190, 0xA, -0x172, -0x186, -0x1AE, -0x1C2, 0, 0, 0,
          0,    0,     0xBB8, 0, 0,     0,     0,   1,      0xE,    0x28,   0x2D,   0, 0, 0 },
        { 0x1AF,  0x7EE,  0x1E,  0, 0x3E8, 0x3E8, 0xA, -0x46, -0x5A, -0x50, -0x64, -0x168, -0x1A4, -0x21C,
          -0x1E0, -0x1F4, 0xBB8, 0, 0,     0,     0,   1,     0,     0,     0,     0x36,   0x8C,   0x91 },
        { 5,     0xA,   0x1E, 0, 0, 0x1F4, 0xA,  -0x46, -0x5A, -0x50, -0x64, 0,    -0x8C, -0xB4,
          -0xA0, -0xC8, 0,    0, 0, 0x32,  0x32, 0,     0,     0,     0,     0x72, 0xF0,  0xF5 },
        { 0, 0, 0, 0, 0, 0, 0xA, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0x1F, 0x32, 0, 0x190, 0x190, 3, -0xAA, -0xBE, -0xE6, -0xFA, 0, 0, 0,
          0, 0,    0,    0, 0,     0,     0, 0,     0xE,   0x28,  0x28,  0, 0, 0 },
    },
    {
        { 0, 0, -0x32, 0,     0x64,   0x64, 0xA, -0xAA, -0xBE, -0xE6, -0xFA, 0, 0, 0,
          0, 0, 0,     0x3E8, -0x190, 0,    0,   0,     0xC2,  0x1EA, 0x1EA, 0, 0, 0 },
        { 5, 0xA, 0x1E, 0,     0x64, 0x64, 0xA, -0x46, -0x5A, -0x50, -0x64, 0,   0,    0,
          0, 0,   0,    0x1F4, 0,    0,    0,   0,     0xE,   0x28,  0x2D,  0xE, 0x28, 0x2D },
        { 0x83, 0x7EE, 0x1E,  0,    0x190, 0x190, 0xA, -0xAA, -0xBE, -0xE6, -0xFA, 0, 0, 0,
          0,    0,     0xBB8, 0xC8, -0xC8, 0,     0,   0,     0x40,  0x8C,  0x91,  0, 0, 0 },
        { 0x83, 0x7EE, 0x1E,  0,    0x190, 0x190, 0xA, -0x172, -0x186, -0x212, -0x226, 0, 0, 0,
          0,    0,     0xBB8, 0xC8, 0,     0,     0,   1,      0x40,   0x8C,   0x91,   0, 0, 0 },
        { 0x1AF,  0x7EE,  0x1E,  0,    0x3E8, 0x3E8, 0xA, -0x46, -0x5A, -0x50, -0x64, -0x168, -0x1A4, -0x21C,
          -0x1E0, -0x258, 0xBB8, 0xC8, 0,     0,     0,   1,     0,     0,     0,     0x40,   0x8C,   0x91 },
        { 5,     0xA,   0x1E, 0,    0, 0x1F4, 0xA,  -0x46, -0x5A, -0x50, -0x64, 0,    -0x8C, -0xB4,
          -0xA0, -0xC8, 0,    0xC8, 0, 0x32,  0x32, 0,     0,     0,     0,     0x72, 0xF0,  0xF5 },
        { 0x1F, 0x32, 0x1E, 0,     0x190, 0x190, 0xA,   -0x172, -0x186, -0x1AE, -0x1C2, 0, 0, 0,
          0,    0,    0,    0xCE4, 0,     0x14A, 0x14A, 0,      0xC2,   0x1EA,  0x1EA,  0, 0, 0 },
        { 0x1F, 0x32, 0x1E, 0,     0x190, 0x190, 0xA, -0x172, -0x186, -0x1AE, -0x1C2, 0, 0, 0,
          0,    0,    0,    0x12C, -0xC8, 0,     0,   0,      0xC2,   0x1EA,  0x1EA,  0, 0, 0 },
    },
    {
        { 0, 0, -0x32, 0,     0x64,   0x64, 0xA, -0xAA, -0xBE, -0xE6, -0xFA, 0, 0, 0,
          0, 0, 0,     0x3E8, -0x190, 0,    0,   0,     0xC2,  0x1EA, 0x1EA, 0, 0, 0 },
        { 5, 0xA, 0x1E, 0,     0x64, 0x64, 0xA, -0x46, -0x5A, -0x50, -0x64, 0,   0,    0,
          0, 0,   0,    0x1F4, 0,    0,    0,   0,     0xE,   0x28,  0x2D,  0xE, 0x28, 0x2D },
        { 0x83, 0x7EE, 0x1E,  0,     0x190,  0x190, 0xA, -0xAA, -0xBE, -0xE6, -0xFA, 0, 0, 0,
          0,    0,     0xBB8, 0x1F4, -0x1F4, 0,     0,   0,     0x72,  0xF0,  0xF5,  0, 0, 0 },
        { 0x83, 0x7EE, 0x1E,  0,     0x190, 0x190, 0xA, -0x172, -0x186, -0x1AE, -0x1C2, 0, 0, 0,
          0,    0,     0xBB8, 0x1F4, 0,     0,     0,   1,      0x72,   0xF0,   0xF5,   0, 0, 0 },
        { 0x1AF,  0x7EE,  0x1E,  0,    0x3E8, 0x3E8, 0xA, -0x46, -0x5A, -0x50, -0x64, -0x168, -0x1A4, -0x21C,
          -0x1E0, -0x258, 0xBB8, 0xC8, 0,     0,     0,   1,     0,     0,     0,     0x40,   0x8C,   0x91 },
        { 5,     0xA,   0x1E, 0,     0, 0x1F4, 0xA,  -0x46, -0x5A, -0x50, -0x64, 0,    -0x8C, -0xB4,
          -0xA0, -0xC8, 0,    0x1F4, 0, 0x32,  0x32, 0,     0,     0,     0,     0x72, 0xF0,  0xF5 },
        { 0x1F, 0x32, 0x1E, 0,      0x190, 0x190, 0xA,   -0xAA, -0xBE, -0xE6, -0xFA, 0, 0, 0,
          0,    0,    0,    0x1130, 0,     0x1B8, 0x1B8, 0,     0xC2,  0x1EA, 0x1EA, 0, 0, 0 },
        { 0x1F, 0x32, 0x1E, 0,     0x190,  0x190, 0x1E, -0xAA, -0xBE, -0xE6, -0xFA, 0, 0, 0,
          0,    0,    0,    0x578, -0x320, 0,     0,    0,     0xC2,  0x1EA, 0x1EA, 0, 0, 0 },
    },
    {
        { 0, 0, -0x32, 0,     0x64,   0x64, 0xA, -0xAA, -0xBE, -0xE6, -0xFA, 0, 0, 0,
          0, 0, 0,     0x3E8, -0x190, 0,    0,   0,     0xC2,  0x1EA, 0x1EA, 0, 0, 0 },
        { 5, 0xA, 0x1E, 0,     0x64, 0x64, 0xA, -0x46, -0x5A, -0x50, -0x64, 0,   0,    0,
          0, 0,   0,    0x1F4, 0,    0,    0,   0,     0xE,   0x28,  0x2D,  0xE, 0x28, 0x2D },
        { 0x83, 0x7EE, 0x1E,  0,     0x190,  0x190, 0xA, -0xAA, -0xBE, -0xE6, -0xFA, 0, 0, 0,
          0,    0,     0xBB8, 0x1F4, -0x1F4, 0,     0,   0,     0x72,  0xF0,  0xF5,  0, 0, 0 },
        { 0x83, 0x7EE, 0x1E,  0,     0x190, 0x190, 0xA, -0x172, -0x186, -0x1AE, -0x1C2, 0, 0, 0,
          0,    0,     0xBB8, 0x1F4, 0,     0,     0,   1,      0x72,   0xF0,   0xF5,   0, 0, 0 },
        { 0x1AF,  0x7EE,  0x1E,  0,    0x3E8, 0x3E8, 0xA, -0x46, -0x5A, -0x50, -0x64, -0x168, -0x1A4, -0x21C,
          -0x1E0, -0x258, 0xBB8, 0xC8, 0,     0,     0,   1,     0,     0,     0,     0x40,   0x8C,   0x91 },
        { 5,     0xA,   0x1E, 0,     0, 0x1F4, 0xA,  -0x46, -0x5A, -0x50, -0x64, 0,    -0x8C, -0xB4,
          -0xA0, -0xC8, 0,    0x1F4, 0, 0x32,  0x32, 0,     0,     0,     0,     0x72, 0xF0,  0xF5 },
        { 0, 0, -0x32, 0,      0x64, 0x64,  0xA,   -0xAA, -0xBE, -0xE6, -0xFA, 0, 0, 0,
          0, 0, 0,     0x1130, 0,    0x1B8, 0x1B8, 0,     0xC2,  0x1EA, 0x1EA, 0, 0, 0 },
        { 0, 0, -0x32, 0,     0x64,   0x64, 0x64, -0xAA, -0xBE, -0xE6, -0xFA, 0, 0, 0,
          0, 0, 0,     0x578, -0x320, 0,    0,    0,     0xC2,  0x1EA, 0x3DE, 0, 0, 0 },
    },
    {
        { 0, 0, -0x32, 0,     0x64,   0x64, 0xA, -0xAA, -0xBE, -0xE6, -0xFA, 0,    0,     0,
          0, 0, 0,     0x3E8, -0x190, 0,    0,   0,     0,     0,     0,     0xC2, 0x1EA, 0x1EA },
        { 5, 0xA, 0x1E, 0,     0x64, 0x64, 0xA, -0x46, -0x5A, -0x50, -0x64, 0,   0,    0,
          0, 0,   0,    0x1F4, 0,    0,    0,   0,     0xE,   0x28,  0x2D,  0xE, 0x28, 0x2D },
        { 0x83, 0x7EE, 0x1E,  0,     0x190,  0x190, 0xA, -0xAA, -0xBE, -0xE6, -0xFA, 0, 0, 0,
          0,    0,     0xBB8, 0x1F4, -0x1F4, 0,     0,   0,     0x72,  0xF0,  0xF5,  0, 0, 0 },
        { 0x83, 0x7EE, 0x1E,  0,     0x190, 0x190, 0xA, -0x172, -0x186, -0x1AE, -0x1C2, 0, 0, 0,
          0,    0,     0xBB8, 0x1F4, 0,     0,     0,   1,      0x72,   0xF0,   0xF5,   0, 0, 0 },
        { 0x1AF,  0x7EE,  0x1E,  0,    0x3E8, 0x3E8, 0xA, -0x46, -0x5A, -0x50, -0x64, -0x168, -0x1A4, -0x21C,
          -0x1E0, -0x258, 0xBB8, 0xC8, 0,     0,     0,   1,     0,     0,     0,     0x40,   0x8C,   0x91 },
        { 5,     0xA,   0x1E, 0,     0, 0x1F4, 0xA,  -0x46, -0x5A, -0x50, -0x64, 0,    -0x8C, -0xB4,
          -0xA0, -0xC8, 0,    0x1F4, 0, 0x32,  0x32, 0,     0,     0,     0,     0x72, 0xF0,  0xF5 },
        { 0x1F, 0x32, 0x1E, 0,      0x190, 0x190, 0xA,   -0xAA, -0xBE, -0xE6, -0xFA, 0, 0, 0,
          0,    0,    0,    0x1130, 0,     0x1B8, 0x1B8, 0,     0xC2,  0x1EA, 0x1EA, 0, 0, 0 },
        { 0x1F,  0x32,  0x1E, 0,     0x190, 0x320, 0x1E, -0xAA, -0xBE, -0xE6, -0xFA, 0,    -0xAA, -0xBE,
          -0xE6, -0xFA, 0,    0x578, 0,     0,     0,    0,     0,     0,     0,     0xC2, 0x1EA, 0x1EA },
    },
    {
        { 0, 0, -0x32, 0x3E8, 0x64,   0x64, 0xA, -0xAA, -0xBE, -0xE6, -0xFA, 0,    0,     0,
          0, 0, 0,     0,     -0x190, 0,    0,   0,     0xC2,  0x1EA, 0x1EA, 0xC2, 0x1EA, 0x1EA },
        { 5, 0xA, 0x1E, 0x1F4, 0x64, 0x64, 0xA, -0x46, -0x5A, -0x50, -0x64, 0,   0,    0,
          0, 0,   0,    0,     0,    0,    0,   0,     0xE,   0x28,  0x2D,  0xE, 0x28, 0x2D },
        { 0x83, 0x7EE, 0x1E,  0x1F4, 0x190,  0x190, 0xA, -0xAA, -0xBE, -0xE6, -0xFA, 0, 0, 0,
          0,    0,     0xBB8, 0,     -0x1F4, 0,     0,   0,     0x72,  0xF0,  0xF5,  0, 0, 0 },
        { 0x83, 0x7EE, 0x1E,  0x1F4, 0x190, 0x190, 0xA, -0x172, -0x186, -0x1AE, -0x1C2, 0, 0, 0,
          0,    0,     0xBB8, 0,     0,     0,     0,   1,      0x72,   0xF0,   0xF5,   0, 0, 0 },
        { 0x1AF,  0x7EE,  0x1E,  0xC8, 0x3E8, 0x3E8, 0xA, -0x46, -0x5A, -0x50, -0x64, -0x168, -0x1A4, -0x21C,
          -0x1E0, -0x258, 0xBB8, 0,    0,     0,     0,   1,     0,     0,     0,     0x40,   0x8C,   0x91 },
        { 5,     0xA,   0x1E, 0x1F4, 0, 0x1F4, 0xA,  -0x46, -0x5A, -0x50, -0x64, 0,    -0x8C, -0xB4,
          -0xA0, -0xC8, 0,    0,     0, 0x32,  0x32, 0,     0,     0,     0,     0x72, 0xF0,  0xF5 },
        { 0, 0, -0x32, 0x1130, 0x64, 0x64,  0xA,   -0xAA, -0xBE, -0xE6, -0xFA, 0, 0, 0,
          0, 0, 0,     0,      0,    0x1B8, 0x1B8, 0,     0xC2,  0x1EA, 0x1EA, 0, 0, 0 },
        { 0,     0,     -0x32, 0x578, 0x64,   0x64, 0x64, -0xAA, -0xBE, -0xE6, -0xFA, 0,    -0xAA, -0xBE,
          -0xE6, -0xFA, 0,     0x2BC, -0x320, 0,    0,    0,     0xC2,  0x1EA, 0x3DE, 0xC2, 0x1EA, 0x3DE },
    },
};

struct_ai_char_data ai_char_data_org[AI_CHAR_DATA_LEN] = {
    // THINKTYPE_0
    {
        1,
        3,
        0,
        { 2, 2, 2, 2, 2, 2, 2, 2 },
        { 2, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0x14, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 2, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    },
    // THINKTYPE_1
    {
        0,
        1,
        0,
        { 0, 0, 0, 0, 0, 0, 0, 0 },
        { 1, 3, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0x14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 2, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    },
    // THINKTYPE_2
    {
        0,
        1,
        0,
        { 0, 0, 0, 0, 0, 0, 0, 0 },
        { 3, 3, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0x32, 0x14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 4, 8, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 5, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    },
    // THINKTYPE_3
    {
        0,
        2,
        0,
        { 0, 0, 0, 0, 0, 0, 0, 0 },
        { 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0x1E, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 1, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    },
    // THINKTYPE_4
    {
        0,
        2,
        0,
        { 1, 1, 1, 1, 1, 1, 1, 1 },
        { 0xB, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 1, 0x1E, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 6, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    },
    // THINKTYPE_5
    {
        0,
        4,
        0,
        { 4, 4, 4, 4, 4, 4, 4, 4 },
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    },
    // THINKTYPE_6
    {
        0,
        3,
        0,
        { 1, 1, 1, 1, 1, 1, 1, 1 },
        { 3, 2, 0xA, 0xB, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0x14, 0xA, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 8, 2, 1, 0xA, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    },
    // THINKTYPE_7
    {
        1,
        1,
        0,
        { 2, 2, 2, 2, 2, 2, 2, 2 },
        { 2, 3, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0x14, 0, 0x32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 7, 0xA, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    },
    // THINKTYPE_8
    {
        1,
        4,
        0,
        { 5, 5, 5, 5, 5, 5, 5, 5 },
        { 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0x21, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    },
    // THINKTYPE_9
    {
        1,
        3,
        0,
        { 3, 3, 3, 3, 3, 3, 3, 3 },
        { 6, 0xB, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 6, 4, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    },
    // THINKTYPE_A
    {
        1,
        4,
        0,
        { 2, 2, 2, 2, 2, 2, 2, 2 },
        { 0xA, 5, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0xA, 0xA, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 4, 5, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    },
    // THINKTYPE_B
    {
        0,
        4,
        0,
        { 3, 3, 3, 3, 3, 3, 3, 3 },
        { 4, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 5, 0xA, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    },
    // THINKTYPE_C
    {
        1,
        3,
        0,
        { 0, 1, 2, 3, 4, 5, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    },
    // THINKTYPE_D
    {
        1,
        3,
        0,
        { 0, 1, 2, 3, 4, 5, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    },
    // THINKTYPE_E
    {
        1,
        3,
        0,
        { 0, 1, 2, 3, 4, 5, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    },
    // THINKTYPE_F
    {
        1,
        3,
        0,
        { 0, 1, 2, 3, 4, 5, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    },
};

/**
 * Original name: aifMakeWork
 */
void aifMakeWork(struct_game_state_data *uupw) {
    uupw->cap.mx = uupw->now_cap.pos_x[0];
    uupw->cap.my = uupw->now_cap.pos_y[0];
    uupw->cap.cn = uupw->cap_speed_count;
    uupw->cap.sp = uupw->cap_speed;
    uupw->cap.ca = uupw->now_cap.capsel_p[0];
    uupw->cap.cb = uupw->now_cap.capsel_p[1];
    uupw->vs = uupw->virus_number;
    uupw->lv = uupw->virus_level;
    uupw->gs = uupw->cnd_now == dm_cnd_training;
    uupw->pn = uupw->player_no;

    if (uupw->pn == 0) {
        game_state_data[0].think_level = game_state_data[1].think_level;
    }
}

/**
 * Original name: aifMakeBlkWork
 */
void aifMakeBlkWork(struct_game_state_data *uupw) {
    s32 column;
    s32 row;

    for (column = 0; column < GAME_MAP_COLUMNS; column++) {
        uupw->blk[0][column].st = 10;
        uupw->blk[0][column].co = 3;
    }

    for (row = 1; row < GAME_MAP_ROWS; row++) {
        for (column = 0; column < GAME_MAP_COLUMNS; column++) {
            s32 index = GAME_MAP_GET_INDEX(row - 1, column);

            if (game_map_data[uupw->pn][index].capsel_m_flg[0] != 0) {
                uupw->blk[row][column].st = capsGCnv_122[game_map_data[uupw->pn][index].capsel_m_g];
                uupw->blk[row][column].co = capsCCnv_123[game_map_data[uupw->pn][index].capsel_m_p];
            } else {
                uupw->blk[row][column].st = 10;
                uupw->blk[row][column].co = 3;
            }
        }
    }

    if (uupw->now_cap.pos_y[0] != 0) {
        uupw->blk[uupw->now_cap.pos_y[0] - 1][uupw->now_cap.pos_x[0]].st = 10;
        uupw->blk[uupw->now_cap.pos_y[0] - 1][uupw->now_cap.pos_x[0]].co = 3;
        uupw->blk[uupw->now_cap.pos_y[1] - 1][uupw->now_cap.pos_x[1]].st = 10;
        uupw->blk[uupw->now_cap.pos_y[1] - 1][uupw->now_cap.pos_x[1]].co = 3;
    }
}

/**
 * Original name: aifMakeFlagSet
 */
void aifMakeFlagSet(struct_game_state_data *uupw) {
    uupw->ai.aiok = false;
    uupw->ai.aiOldRollCnt = 0;
    uupw->ai.aiRollCnt = 0;
    uupw->ai.aiRollFinal = 0;
    uupw->ai.aiRollHabit = 0;
}

/**
 * Original name: aifGameInit
 */
void aifGameInit(void) {
    s32 i;

    fool_mode = false;
    s_hard_mode = false;
    MissRate = 0;
    PlayTime = 0;
    for (i = 0; i < ARRAY_COUNT(game_state_data); i++) {
        s32 j;

        game_state_data[i].ai.aiok = true;
        game_state_data[i].ai.aiRandFlag = true;
        game_state_data[i].ai.aiState = 0;
        game_state_data[i].ai.aiRootP = AIROOTP_CAP;

        for (j = 0; j < AI_EFFECT_LEN; j++) {
            game_state_data[i].ai.aiEffectNo[j] = 0;
            game_state_data[i].ai.aiEffectCount[j] = 0;
        }
    }
}

/**
 * Original name: aifFirstInit
 */
void aifFirstInit(void) {
    s32 i;

    for (i = 0; i < AI_PARAM_LEN2; i++) {
        s32 j;

        for (j = 0; j < AI_PARAM_LEN1; j++) {
            ai_param[j][i] = ai_param_org[j][i];
        }
    }

    for (i = 0; i < AI_CHAR_DATA_LEN; i++) {
        ai_char_data[i] = ai_char_data_org[i];
    }

    aifGameInit();
}

/**
 * Original name: aifMake
 */
void aifMake(struct_game_state_data *uupw) {
    pGameState = uupw;

    if (!uupw->ai.aiok) {
        aifMakeWork(uupw);
        aifMakeBlkWork(uupw);

        aiGoalX = uupw->cap.mx + 1;

        aiGoalY = uupw->cap.my;
        if (aiGoalY == 0) {
            aiGoalY++;
        }

        aipn = uupw->pn;
        uupw->ai.aivl = uupw->think_level;
        if (FallSpeed[uupw->cap.sp] > aiSlideFSpeed[aiSelSpeed][uupw->ai.aivl]) {
            aiMoveSF = 1;
        } else {
            aiMoveSF = 0;
        }

        aifFieldCopy(uupw);
        aifPlaceSearch();
        aifMoveCheck();
        delpos_cnt = 0;

        if (evs_gamemode == GMD_FLASH) {
            s32 var_v1;

            flash_special();
            last_flash = 0;

            for (var_v1 = 0; var_v1 < pGameState->flash_virus_count; var_v1++) {
                if (pGameState->flash_virus_pos[var_v1].color >= 0) {
                    last_flash++;
                }
            }
        }

        aiSetCharacter(uupw);
        aiHiruAllPriSet(uupw);
        aiHiruSideLineEraser(uupw);
        aifReMoveCheck();
        aifKeyMake(uupw);
        uupw->ai.aiKeyCount = 0;
        uupw->ai.aiok = true;
    }
}

/**
 * Original name: aifMake2
 */
bool aifMake2(struct_game_state_data *uupw, s32 x, s32 y, s32 tateFlag, s32 revFlag) {
    if (uupw->ai.aiok) {
        return false;
    }

    aifMakeWork(uupw);
    aifMakeBlkWork(uupw);

    MissRate = 0;
    aiGoalX = uupw->cap.mx + 1;
    aiGoalY = uupw->cap.my;
    if (aiGoalY == 0) {
        aiGoalY++;
    }

    aipn = uupw->pn;
    uupw->ai.aivl = uupw->think_level;
    if (FallSpeed[uupw->cap.sp] > aiSlideFSpeed[aiSelSpeed][uupw->ai.aivl]) {
        aiMoveSF = 1;
    } else {
        aiMoveSF = 0;
    }

    aifFieldCopy(uupw);

    aiFlag[0].tory = tateFlag == 0;
    aiFlag[0].x = x + 1;
    aiFlag[0].y = y;
    aiFlag[0].rev = revFlag != 0;

    aiFlagCnt = 1;
    decide = 0;
    aifReMoveCheck();
    aifKeyMake(uupw);
    uupw->ai.aiKeyCount = 0;
    uupw->ai.aiok = true;

    return true;
}

/**
 * Original name: aiHiruSideLineEraser
 */
void aiHiruSideLineEraser(struct_game_state_data *xpw) {
    s32 sp8[2];
    s32 sp10[2];
    s32 sp18[2];
    u8 sp20[0x10];
    u8 sp30[0x10];
    u8 sp40[0x10];
    u8 sp50[0x10];
    u8 chk_line[0x8];
    s32 sp68;
    s32 sp80;
    s32 temp_s3;
    s32 var_a3;
    s32 var_s1;
    s32 var_t0;
    s32 var_t0_3;
    s32 var_t1;
    s32 var_t3_2;
    s32 var_t8_2;
    s32 temp_a2_2;
    s32 temp_t5;
    s32 temp_v0_8;
    s32 var_a1;
    s32 var_t6_2;

#if 0
    int x; // r4
    int y; // r23
    int z; // r24
    int i; // r11
    int f; // r5
    int f2; // r6
    int fc; // r1+0x8
    int r; // r23
    int h[2]; // r1+0x68
    int w[2]; // r1+0x60
    int m; // r26
    int p; // r22
    int v; // r1+0x8
    int c; // r1+0x8
    int e; // r25
    int g; // r1+0x8
    int g2; // r26
    int xx; // r27
    int cf[2]; // r1+0x54
    unsigned char low_virus[12]; // r1+0x48
    unsigned char low_capsx[12]; // r1+0x3C
    unsigned char lst_virus[12]; // r1+0x30
    unsigned char lst_capsx[12]; // r1+0x24
    // unsigned char chk_line[8]; // r1+0x1C
#endif

    if ((aiFlag[decide].hei[0][4] != 0) || (aiFlag[decide].hei[1][4] != 0)) {
        return;
    }

    sp68 = 0;
    sp80 = 1;
    var_s1 = 0;

    for (var_a3 = 0; var_a3 < 8; var_a3++) {
        sp20[var_a3] = sp30[var_a3] = sp50[var_a3] = 0x11;
        sp40[var_a3] = 0;
    }

    for (var_a3 = 0; var_a3 < 8; var_a3++) {
        for (var_a1 = GAME_MAP_ROWS - 1, var_t0 = 0, var_t1 = 0; var_a1 >= 2; var_a1--) {
            if (xpw->blk[var_a1][var_a3].st == 0xA) {
                var_t1 += 1;
            } else if ((xpw->blk[var_a1][var_a3].st >= 5) && (xpw->blk[var_a1][var_a3].st <= 7)) {
                if (var_t0 == 0) {
                    sp40[var_a3] = var_a1;
                    if (var_t1 >= 3) {
                        sp20[var_a3] = var_a1;
                    } else {
                        temp_a2_2 = xpw->blk[var_a1][var_a3].co;
                        if (((xpw->blk[var_a1 + 2][var_a3].st == 0xA) ||
                             (xpw->blk[var_a1 + 2][var_a3].co == temp_a2_2)) &&
                            (xpw->blk[var_a1 + 3][var_a3].co == temp_a2_2)) {
                            sp20[var_a3] = var_a1;
                        } else if ((var_a3 == 2) || (var_a3 == 3) || (var_a3 == 4) || (var_a3 == 5)) {
                            var_t0 = -1;
                            var_t1 = 0;
                            sp40[var_a3] = 0;
                            sp30[var_a3] = var_a1;
                            sp50[var_a3] = var_a1;
                        }
                    }
                    var_t0 += 1;
                }
            } else {
                if (var_t0 == 0) {
                    sp30[var_a3] = var_a1;
                    var_t1 = 0;
                }
                sp50[var_a3] = var_a1;
            }
        }

        if (sp40[var_a3] != 0) {
            if (sp50[var_a3] < 6) {
                sp80 = 0;
                if ((var_a3 == 2) || (var_a3 == 3) || (var_a3 == 4) || (var_a3 == 5)) {
                    sp68 = 1;
                    var_s1 = 0;
                    break;
                }
            }
        }

        if (sp40[var_a3] >= 0xE) {
            var_s1 = 1;
        }
    }

    if (var_s1 | sp80) {
        return;
    }

    for (var_a3 = 0; var_a3 < 8; var_a3++) {
        chk_line[var_a3] = 1;
    }

    sp18[0] = sp18[1] = 1;
    var_s1 = 0;

    for (var_t8_2 = 0; (var_t8_2 < 8) && (var_s1 == 0); var_t8_2++) {
        var_a3 = aiLinePri[var_t8_2];
        temp_t5 = sp20[var_a3];

        if (temp_t5 >= 0xE) {
            continue;
        }

        chk_line[var_a3] = 0;
        if (sp18[var_a3 / 4] == 0) {
            continue;
        }

        sp18[var_a3 / 4] = 0;
        temp_v0_8 = sp30[var_a3];
        temp_s3 = temp_v0_8 - temp_t5;

        if (var_a3 >= 4) {
            var_t6_2 = var_a3 - 1;
        } else {
            var_t6_2 = var_a3;
        }

        for (var_t3_2 = 0, sp8[0] = sp8[1] = sp10[0] = sp10[1] = 0; var_t3_2 < aiFlagCnt; var_t3_2++) {
            if ((aiFlag[var_t3_2].ok != 1) || (aiFlag[var_t3_2].y != temp_v0_8 - 1)) {
                continue;
            }

            if (aiFlag[var_t3_2].tory == 0) {
                if (aiFlag[var_t3_2].x - 1 == var_a3) {
                    sp8[aiFlag[var_t3_2].rev] = var_t3_2 + 1;
                }
            } else if (aiFlag[var_t3_2].x - 1 == var_t6_2) {
                sp10[aiFlag[var_t3_2].rev] = var_t3_2 + 1;
            }
        }

        if ((sp8[0] + sp10[0] + sp8[1] + sp10[1]) == 0) {
            continue;
        }

        temp_a2_2 = xpw->blk[temp_t5][var_a3].co;
        if (temp_s3 == 5) {
            if ((sp10[0] + sp10[1]) != 0) {
                var_s1 = sp10[0];
            }

            if ((sp8[0] + sp8[1]) != 0) {
                if (aiNext[0] == temp_a2_2) {
                    var_s1 = sp8[0];
                } else if (aiNext[1] == temp_a2_2) {
                    var_s1 = sp8[1];
                }
            }
        } else if (temp_s3 < 5) {
            if ((sp10[0] + sp10[1]) != 0) {
                if (aiNext[0] == temp_a2_2) {
                    if (var_a3 < 4) {
                        var_s1 = sp10[0];
                    } else {
                        var_s1 = sp10[1];
                    }
                } else if (aiNext[1] == temp_a2_2) {
                    if (var_a3 < 4) {
                        var_s1 = sp10[1];
                    } else {
                        var_s1 = sp10[0];
                    }
                }
            }

            if (sp8[0] + sp8[1]) {
                if ((aiNext[0] == aiNext[1]) && (temp_a2_2 == aiNext[0])) {
                    var_s1 = sp8[0];
                }
            }
        } else {
            if (sp8[0] != 0) {
                var_s1 = sp8[0];
            }
        }
    }

    if (var_s1 != 0) {
        decide = var_s1 - 1;
        return;
    }

    if (sp68 != 0) {
        return;
    }

    var_t1 = -1;
    var_a3 = -1000001;

    for (var_t0_3 = 0; var_t0_3 < aiFlagCnt; var_t0_3++) {
        if (aiFlag[var_t0_3].tory == 0) {
            if ((chk_line[aiFlag[var_t0_3].x - 1] != 0) || (sp20[aiFlag[var_t0_3].x - 1] > aiFlag[var_t0_3].y)) {
                if (aiFlag[var_t0_3].pri > var_a3) {
                    var_a3 = aiFlag[var_t0_3].pri;
                    var_t1 = var_t0_3;
                }
            }
        } else {
            if (((chk_line[aiFlag[var_t0_3].x - 1] != 0) || (sp20[aiFlag[var_t0_3].x - 1] > aiFlag[var_t0_3].y)) &&
                ((chk_line[aiFlag[var_t0_3].x] != 0) || (sp20[aiFlag[var_t0_3].x] > aiFlag[var_t0_3].y))) {
                if (aiFlag[var_t0_3].pri > var_a3) {
                    var_a3 = aiFlag[var_t0_3].pri;
                    var_t1 = var_t0_3;
                }
            }
        }
    }

    if (var_t1 != -1) {
        decide = var_t1;
    }
}

/**
 * Original name: aif_MiniChangeBall
 */
BAD_RETURN(s32) aif_MiniChangeBall(u8 row, u8 col) {
    if (aif_field[row][col].st != 4) {
        s8 st = aif_field[row][col].st;
        s8 yy = row + srh_466[st][0];
        s8 xx = col + srh_466[st][1];

        if ((yy > 0) && (yy < GAME_MAP_ROWS) && (xx >= 0) && (xx < GAME_MAP_COLUMNS)) {
            aif_field[yy][xx].st = 4;
        }
    }
}

/**
 * Original name: aifEraseLineCore
 */
bool aifEraseLineCore(s32 col, s32 row) {
    bool sp18 = false;
    bool ret = false;
    u8 tc = aif_field[row][col].co;
    s32 i;

    if (hei_data[2] >= 4) {
        sp18 = true;

        for (i = row - 1; (i > 0) && (i > row - 4); i--) {
            if (aif_field[i][col].co == tc) {
                if ((aif_field[i][col].st > 4) && (aif_field[i][col].st < 8)) {
                    hei_data[1]++;
                } else {
                    aif_MiniChangeBall(i, col);
                }

                if (evs_gamemode == GMD_FLASH) {
                    if (flash_virus(col, i) != 0) {
                        ret = true;
                    }
                }

                aif_field[i][col].st = 0xA;
                aif_field[i][col].co = 3;
            } else {
                i = 0;
            }
        }

        for (i = row + 1; (i < row + 4) && (i < GAME_MAP_ROWS); i++) {
            if (aif_field[i][col].co == tc) {
                if ((aif_field[i][col].st > 4) && (aif_field[i][col].st < 8)) {
                    hei_data[1]++;
                } else {
                    aif_MiniChangeBall(i, col);
                }

                aif_field[i][col].st = 0xA;
                aif_field[i][col].co = 3;
            } else {
                i = GAME_MAP_ROWS;
            }
        }
    }

    if (wid_data[2] >= 4) {
        sp18 = true;

        for (i = col - 1; (i > -1) && (i > col - 4); i--) {
            if (aif_field[row][i].co == tc) {
                if ((aif_field[row][i].st > 4) && (aif_field[row][i].st < 8)) {
                    wid_data[1]++;
                } else {
                    aif_MiniChangeBall(row, i);
                }

                aif_field[row][i].st = 0xA;
                aif_field[row][i].co = 3;
            } else {
                i = -1;
            }
        }

        for (i = col + 1; (i < col + 4) && (i < GAME_MAP_COLUMNS); i++) {
            if (aif_field[row][i].co == tc) {
                if ((aif_field[row][i].st > 4) && (aif_field[row][i].st < 8)) {
                    wid_data[1]++;
                } else {
                    aif_MiniChangeBall(row, i);
                }

                if (evs_gamemode == GMD_FLASH) {
                    if (flash_virus(i, row) != 0) {
                        ret = true;
                    }
                }

                aif_field[row][i].st = 0xA;
                aif_field[row][i].co = 3;
            } else {
                i = GAME_MAP_COLUMNS;
            }
        }
    }

    if (sp18) {
        aif_MiniChangeBall(row, col);

        aif_field[row][col].st = 0xA;
        aif_field[row][col].co = 3;
    }

    return ret;
}

/**
 * Original name: aifRensaCheckCore
 */
s32 aifRensaCheckCore(struct_game_state_data *uupw, struct_aiFlag *af UNUSED, u8 mx, u8 my, u8 mco, u8 mst, u8 sx,
                      u8 sy, u8 sco, u8 sst) {
    u8 sp18 = 0;
    u8 var_s1;
    u8 var_s3;
    u8 temp;
    s32 row;
    s32 col;

#if 0
    int idx; // r27
    int idy; // r26
    unsigned char ctr; // r1+0x8
    unsigned char co; // r23
    unsigned char c; // r24
    unsigned char i; // r26
#endif

    for (col = 0; col < GAME_MAP_COLUMNS; col++) {
        for (row = 0; row < GAME_MAP_ROWS; row++) {
            aif_field[row][col].co = uupw->blk[row][col].co;
            aif_field[row][col].st = uupw->blk[row][col].st;
        }
    }

    aiHiEraseCtr = 0;

    for (col = 0; col < GAME_MAP_COLUMNS; col++) {
        for (row = 1; row < 4; row++) {
            if (aif_field[row][col].st < 8U) {
                aiHiEraseCtr += BadLineRate[row][col];
            }
        }
    }

    if (my != 0) {
        aif_field[my][mx].st = mst;
        aif_field[my][mx].co = mco;
    }

    if (sy != 0) {
        aif_field[sy][sx].st = sst;
        aif_field[sy][sx].co = sco;
    }

    for (row = 1; row < GAME_MAP_ROWS; row++) {
        for (col = 0; col < GAME_MAP_COLUMNS - 3; col++) {
            if (aif_field[row][col].st != 0xA) {
                temp = aif_field[row][col].co;
                for (var_s3 = 1; col + var_s3 < 8; var_s3++) {
                    if ((aif_field[row][col + var_s3].st == 0xA) || (aif_field[row][col + var_s3].co != temp)) {
                        break;
                    }
                }

                if (var_s3 >= 4) {
                    sp18 += var_s3 / 4;

                    for (var_s1 = 0; var_s1 < var_s3; var_s1++) {
                        aif_MiniChangeBall(row, col + var_s1);
                        aif_field[row][col + var_s1].st = 8;
                    }
                }
                col += var_s3 - 1;
            }
        }
    }

    for (col = 0; col < GAME_MAP_COLUMNS; col++) {
        for (row = 1; row < GAME_MAP_ROWS - 3; row++) {
            if (aif_field[row][col].st != 0xA) {
                temp = aif_field[row][col].co;
                for (var_s3 = 1; row + var_s3 < GAME_MAP_ROWS; var_s3++) {
                    if ((aif_field[row + var_s3][col].st == 0xA) || (aif_field[row + var_s3][col].co != temp)) {
                        break;
                    }
                }

                if (var_s3 >= 4U) {
                    sp18 += var_s3 / 4;

                    for (var_s1 = 0; var_s1 < var_s3; var_s1++) {
                        aif_MiniChangeBall(row + var_s1, col);
                        aif_field[row + var_s1][col].st = 8;
                    }
                }

                row += var_s3 - 1;
            }
        }
    }

    var_s3 = 1;

    for (row = GAME_MAP_ROWS - 1; row > 0; row--) {
        for (col = GAME_MAP_COLUMNS - 1; col >= 0; col--) {
            switch (aif_field[row][col].st) {
                case 0x8:
                    aif_field[row][col].st = 0xA;
                    break;

                case 0x4:
                    if (row != GAME_MAP_ROWS - 1) {
                        if (aif_field[row + 1][col].st == 0xA) {
                            var_s3 = 0;

                            for (var_s1 = row + 1; var_s1 < GAME_MAP_ROWS; var_s1++) {
                                if (aif_field[var_s1][col].st != 0xA) {
                                    break;
                                }
                            }

                            var_s1--;
                            aif_field[var_s1][col].st = aif_field[row][col].st;
                            aif_field[var_s1][col].co = aif_field[row][col].co;
                            aif_field[row][col].st = 0xA;
                        }
                    }
                    break;

                case 1:
                    if (row != GAME_MAP_ROWS - 1) {
                        if (aif_field[row + 1][col].st == 0xA) {
                            var_s3 = 0;

                            for (var_s1 = row + 1; var_s1 < GAME_MAP_ROWS; var_s1++) {
                                if (aif_field[var_s1][col].st != 0xA) {
                                    break;
                                }
                            }

                            var_s1--;
                            aif_field[var_s1][col].st = aif_field[row][col].st;
                            aif_field[var_s1][col].co = aif_field[row][col].co;
                            aif_field[row][col].st = 0xA;

                            aif_field[var_s1 - 1][col].st = aif_field[row - 1][col].st;
                            aif_field[var_s1 - 1][col].co = aif_field[row - 1][col].co;
                            aif_field[row - 1][col].st = 0xA;
                        }
                    }
                    break;

                case 2:
                    if (row != GAME_MAP_ROWS - 1) {
                        if ((aif_field[row + 1][col].st == 0xA) &&
                            (aif_field[row + 1][col + 1].st == aif_field[row + 1][col].st)) {
                            var_s3 = 0;

                            for (var_s1 = row + 1; (var_s1 < GAME_MAP_ROWS) && (aif_field[var_s1][col].st == 0xA) &&
                                                   (aif_field[var_s1][col + 1].st == 0xA);
                                 var_s1++) {
                                ;
                            }

                            var_s1--;
                            aif_field[var_s1][col].st = aif_field[row][col].st;
                            aif_field[var_s1][col].co = aif_field[row][col].co;
                            aif_field[row][col].st = 0xA;

                            aif_field[var_s1][col + 1].st = aif_field[row][col + 1].st;
                            aif_field[var_s1][col + 1].co = aif_field[row][col + 1].co;
                            aif_field[row][col + 1].st = 0xA;
                        }
                    }
                    break;
            }
        }
    }

    for (col = 0; col < GAME_MAP_COLUMNS; col++) {
        for (row = 1; row < 4; row++) {
            if (aif_field[row][col].st < 8U) {
                aiHiEraseCtr -= BadLineRate[row][col];
            }
        }
    }

    if (sp18 >= 2) {
        if (var_s3 != 0) {
            return 2;
        }
        return 1;
    }

    for (row = 1; row < GAME_MAP_ROWS; row++) {
        for (col = 0; col < GAME_MAP_COLUMNS - 3; col++) {
            if (aif_field[row][col].st != 0xA) {
                temp = aif_field[row][col].co;
                for (var_s3 = 1; (col + var_s3 < GAME_MAP_COLUMNS) && (aif_field[row][col + var_s3].st != 0xA) &&
                                 (aif_field[row][col + var_s3].co == temp);
                     var_s3++) {
                    ;
                }

                if (var_s3 >= 4U) {
                    return 1;
                }
            }
        }
    }

    for (col = 0; col < GAME_MAP_COLUMNS; col++) {
        for (row = 1; row < GAME_MAP_ROWS - 3; row++) {
            if (aif_field[row][col].st != 0xA) {
                temp = aif_field[row][col].co;
                for (var_s3 = 1; (row + var_s3 < GAME_MAP_ROWS) && (aif_field[row + var_s3][col].st != 0xA) &&
                                 (aif_field[row + var_s3][col].co == temp);
                     var_s3++) {
                    ;
                }

                if (var_s3 >= 4) {
                    return 1;
                }
            }
        }
    }

    return 0;
}

/**
 * Original name: aifRensaCheck
 */
s32 aifRensaCheck(struct_game_state_data *uupw, struct_aiFlag *af) {
    u8 mx = af->x - 1;
    u8 my = af->y;
    u8 mco;
    u8 mst;
    u8 sx;
    u8 sy;
    u8 sco; //! @bug: sometimes not set
    u8 sst;

    if (af->tory == 0) {
        mst = 1;
        sx = mx;
        sy = my - 1;
        sst = 0;
        if (af->rev == 0) {
            mco = aiNext[1];
            if (my - 1 > 0) {
                sco = aiNext[0];
            }
        } else {
            mco = aiNext[0];
            if (my - 1 > 0) {
                sco = aiNext[1];
            }
        }
    } else {
        mst = 2;
        sx = mx + 1;
        sy = my;
        sst = 3;
        if (af->rev == 0) {
            mco = aiNext[0];
            sco = aiNext[1];
        } else {
            mco = aiNext[1];
            sco = aiNext[0];
        }
    }

    return aifRensaCheckCore(uupw, af, mx, my, mco, mst, sx, sy, sco, sst);
}

/**
 * Original name: aifSearchLineCore
 */
// TODO: I wonder if arg2 could be an enum
bool aifSearchLineCore(s32 mx, s32 my, s32 fg) {
    u8 tc = aif_field[my][mx].co;
    s32 i;
    s32 j;
    s32 k;
    s32 var_t3;
    bool var_t0_3;
    bool var_t4;

#if 0
    int i; // r27
    int x; // r11
    int y; // r10
    int z; // r1+0x8
    int w; // r11
    int p; // r26
    unsigned char tc; // r12
#endif

    for (j = 0; j < HEI_WEI_DATA_LEN; j++) {
        hei_data[j] = wid_data[j] = 0;
    }

    if (aif_field[my][mx].st == 0xA) {
        return false;
    }

    if (fg != 2) {
        var_t4 = true;

        for (k = my - 1; (k > 0) && (k > my - 4); k--) {
            if (aif_field[k][mx].co != tc) {
                if (aif_field[k][mx].co != 3) {
                    k = 0;
                } else {
                    var_t4 = false;
                }
            } else {
                hei_data[3]++;
                if ((aif_field[k][mx].st > 4) && (aif_field[k][mx].st < 8)) {
                    hei_data[4]++;
                    if (k < 4) {
                        hei_data[8] += BadLineRate[k][mx];
                    }
                } else if (k < 4) {
                    hei_data[7] += BadLineRate[k][mx];
                }
                if (var_t4) {
                    hei_data[2]++;
                }
            }

            if (k > 0) {
                hei_data[5]++;
            }
        }

        for (k = my + 1, var_t4 = true, var_t3 = 0; k < GAME_MAP_ROWS; k++, var_t3++) {
            if (aif_field[k][mx].co != tc) {
                if (aif_field[k][mx].co != 3) {
                    k = 0x11;
                } else {
                    var_t4 = false;
                }
            } else {
                hei_data[3]++;

                if ((aif_field[k][mx].st > 4) && (aif_field[k][mx].st < 8)) {
                    if (var_t3 < 3) {
                        hei_data[4]++;
                        if (k < 4) {
                            hei_data[8] += BadLineRate[k][mx];
                        }
                    }
                } else if (k < 4) {
                    hei_data[7] += BadLineRate[k][mx];
                }

                if (var_t4) {
                    hei_data[2]++;
                }
                hei_data[5]++;
            }
        }

        hei_data[2]++;
        hei_data[3]++;
        hei_data[5]++;
    }

    if (fg != 1) {
        for (i = mx - 1, var_t3 = 1, var_t4 = true; (i >= 0) && (i > mx - 4); i--) {
            if (aif_field[my][i].co != tc) {
                if (aif_field[my][i].co != 3) {
                    i = -1;
                } else {
                    var_t4 = false;
                    if (var_t3 != 0) {
                        var_t0_3 = false;

                        for (j = 0; j < aiFlagCnt; j++) {
                            if ((aiFlag[j].ok == 1) && (aiFlag[j].tory == 0) && ((aiFlag[j].x - 1) == i)) {
                                if ((aiFlag[j].y == my) || (aiFlag[j].y == (my + 1))) {
                                    var_t0_3 = true;
                                    wid_data[5]++;
                                    j = aiFlagCnt;
                                }
                            }
                        }

                        if (!var_t0_3) {
                            var_t3 = 0;
                        }
                    }
                }
            } else {
                wid_data[3]++;
                if ((aif_field[my][i].st > 4) && (aif_field[my][i].st < 8)) {
                    wid_data[4]++;
                    if (my < 4) {
                        wid_data[8] += BadLineRate[my][i];
                    }
                } else if (my < 4) {
                    wid_data[7] += BadLineRate[my][i];
                }
                if (var_t4) {
                    wid_data[2]++;
                }
                if (var_t3 != 0) {
                    wid_data[5]++;
                }
            }
        }

        for (i = mx + 1, var_t3 = 1, var_t4 = true; (i < mx + 4) && (i < GAME_MAP_COLUMNS); i++) {
            if (aif_field[my][i].co != tc) {
                if (aif_field[my][i].co != 3) {
                    i = 8;
                } else {
                    var_t4 = false;
                    if (var_t3 != 0) {
                        var_t0_3 = false;

                        for (j = 0; j < aiFlagCnt; j++) {
                            if ((aiFlag[j].ok == 1) && (aiFlag[j].tory == 0) && ((aiFlag[j].x - 1) == i)) {
                                if ((aiFlag[j].y == my) || (aiFlag[j].y == (my + 1))) {
                                    var_t0_3 = true;
                                    wid_data[5]++;
                                    j = aiFlagCnt;
                                }
                            }
                        }

                        if (!var_t0_3) {
                            var_t3 = 0;
                        }
                    }
                }
            } else {
                wid_data[3] += 1;
                if ((aif_field[my][i].st > 4) && (aif_field[my][i].st < 8)) {
                    wid_data[4]++;
                    if (my < 4) {
                        wid_data[8] += BadLineRate[my][i];
                    }
                } else if (my < 4) {
                    wid_data[7] += BadLineRate[my][i];
                }

                if (var_t4) {
                    wid_data[2]++;
                }

                if (var_t3 != 0) {
                    wid_data[5]++;
                }
            }
        }

        wid_data[2]++;
        wid_data[3]++;
        wid_data[5]++;
    }

    var_t4 = false;
    if (hei_data[2] >= 4) {
        var_t4 = true;
        hei_data[0] = 1;
        if (hei_data[2] == 8) {
            hei_data[0] = 2;
        }
    }

    if (wid_data[2] >= 4) {
        var_t4 = true;
        wid_data[0] = 1;
        if (wid_data[2] == 8) {
            wid_data[0] = 2;
        }
    }

    if (var_t4) {
        if (hei_data[0] != 0) {
            if (wid_data[0] == 0) {
                wid_data[9] = 1;
            }
        } else {
            hei_data[9] = 1;
        }
    }

    return var_t4;
}

/**
 * Original name: aifMiniPointK3
 */
s32 aifMiniPointK3(u8 *tbl, u8 sub, u8 *elin, u8 flag, u8 tory, u8 ec) {
    s32 ex = 0;
    s32 i;

    if (tbl[0] != 0) {
        *elin += tbl[0];
        tbl[7] = 0;
        tbl[8] = 0;

        for (i = 1; i < 9; i++) {
            ex += tbl[i] * pri_point[i];
        }
    } else if (tbl[9] == 0) {
        if (tbl[5] >= 4) {
            if (flag) {
                if ((ec == 0) || (tory != 0) || (tbl[3] >= 3)) {
                    ex = HeiLinesAllp[tbl[3]];
                }
            } else {
                if ((ec == 0) || (tory != 1) || (tbl[3] >= 3)) {
                    ex = WidLinesAllp[tbl[3]];
                }
            }
            ex += tbl[4] * pri_point[4];
        }
    }

    if (sub == 1) {
        ex /= 3;
    }

    return ex;
}

/**
 * Original name: aifMiniAloneCapNumber
 */
s32 aifMiniAloneCapNumber(u8 x, u8 y, u8 f, s32 ec) {
    s32 var_t0 = 0;
    s32 temp = aif_field[y + 1][x].st;

#if 0
    int m; // r3
    int d; // r7
#endif

    if ((((hei_data[2] == 1) || ((hei_data[2] != 0) && (hei_data[5] < 4))) &&
         ((wid_data[2] == 1) || ((wid_data[2] != 0) && (wid_data[5] < 4)))) ||
        ((ec == 1) && (hei_data[2] != 0) && (wid_data[2] != 0) &&
         ((hei_data[5] >= 4) ? hei_data[2] : 0) + ((wid_data[5] >= 4) ? wid_data[2] : 0) < 4)) {
        if (y == 0x10) {
            var_t0 = 1;
        } else if (f != 0) {
            if (temp >= 5) {
                var_t0 = 3;
            } else {
                var_t0 = 2;
            }
        } else {
            if (temp >= 5) {
                var_t0 = 5;
            } else {
                var_t0 = 4;
            }
        }
    }

    return var_t0;
}

/**
 * Original name: aifMiniAloneCapNumberW
 */
s32 aifMiniAloneCapNumberW(u8 x, u8 y, u8 f, s32 ec) {
    s32 var_v1 = 0;
    s32 temp = aif_field[y + 1][x].st;

#if 0
    int m; // r3
    int d; // r7
#endif

    if ((wid_data[2] == 1) || ((ec == 1) && (wid_data[2] == 2))) {
        if (y == 0x10) {
            var_v1 = 1;
        } else if (f != 0) {
            if (temp >= 5) {
                var_v1 = 3;
            } else {
                var_v1 = 2;
            }
        } else {
            if (temp >= 5) {
                var_v1 = 5;
            } else {
                var_v1 = 4;
            }
        }
    }

    return var_v1;
}

/**
 * Original name: flash_virus
 */
s32 flash_virus(s32 col, s32 row) {
    s32 i;

    for (i = 0; i < pGameState->flash_virus_count; i++) {
        if ((pGameState->flash_virus_pos[i].color >= 0) && (col == pGameState->flash_virus_pos[i].column) &&
            (row == pGameState->flash_virus_pos[i].row)) {
            return pGameState->flash_virus_pos[i].color;
        }
    }

    return -1;
}

/**
 * Original name: search_Vflash
 */
bool search_Vflash(s32 x, s32 y, s32 col) {
    s32 i;

    for (i = y + 1; i <= y + 3; i++) {
        if (i >= GAME_MAP_ROWS) {
            return false;
        }

        if (aiFieldData[i][x].co != 3) {
            if (aiFieldData[i][x].co == col) {
                s32 j;

                for (j = 0; j < pGameState->flash_virus_count; j++) {
                    if (pGameState->flash_virus_pos[j].color >= 0) {
                        if (x == pGameState->flash_virus_pos[j].column) {
                            return true;
                        }
                    }
                }
            }
            break;
        }
    }

    return false;
}

/**
 * Original name: search_Lflash
 */
bool search_Lflash(s32 arg0 UNUSED, s32 y) {
    s32 i;

    for (i = 0; i < pGameState->flash_virus_count; i++) {
        if ((pGameState->flash_virus_pos[i].color >= 0) && (y == pGameState->flash_virus_pos[i].row)) {
            return true;
        }
    }

    return false;
}

/**
 * Original name: aifSearchLineMS
 */
s32 aifSearchLineMS(struct_aiFlag *ag, s32 mx, s32 my, s32 mco, s32 sx, s32 sy, s32 sco, s32 ec) {
    u8 ss[8];
    bool sp28;
    bool sp2C;
    s32 temp;
    s32 sp30;
    s32 var_a0;
    s32 var_a2;
    s32 var_a2_2;
    s32 var_a2_3;
    s32 var_s0;
    s32 var_s1;
    s32 var_s2;
    s32 var_s4;

#if 0
    int i; // r7
    int f; // r1+0x8
    int z; // r1+0x8
    int z2; // r16
    int x; // r7
    int y; // r6
    int j; // r3
    int m; // r28
    int s; // r9
    int opt; // r22
    int sy2; // r17
    unsigned char ss[8]; // r1+0x34
#endif

    var_s4 = 0;
    temp = my;
    sp30 = sy;

    for (var_a2 = 0; var_a2 < STRUCT_AIFLAG_UNK_LEN; var_a2++) {
        ag->wid[0][var_a2] = ag->hei[0][var_a2] = ag->wid[1][var_a2] = ag->hei[1][var_a2] = 0;
    }

    ag->elin[0] = ag->elin[1] = 0;
    ag->sub = 0;
    ag->only[0] = ag->only[1] = 0;
    ag->wonly[0] = ag->wonly[1] = 0;
    sp28 = aifSearchLineCore(mx, my, 0);
    sp2C = false;

    if (aifEraseLineCore(mx, my)) {
        var_s4 = 1;
        ag->pri += 0x2710;
    }

    if (sp28 == false) {
        ag->only[0] = aifMiniAloneCapNumber(mx, my, 0, ec);
        ag->wonly[0] = aifMiniAloneCapNumberW(mx, my, 0, ec);
    }

    for (var_a2_2 = 0; var_a2_2 < STRUCT_AIFLAG_UNK_LEN; var_a2_2++) {
        ag->hei[0][var_a2_2] = hei_data[var_a2_2];
        ag->wid[0][var_a2_2] = wid_data[var_a2_2];
    }

    if (aif_field[sy][sx].st != 0xA) {
        if (ec != 0) {
            if (ag->tory == 0) {
                var_a2_3 = 2;
            } else {
                var_a2_3 = 1;
            }
        } else {
            var_a2_3 = 0;
        }

        var_s0 = 0;
        sp2C = aifSearchLineCore(sx, sy, var_a2_3);
        if (sp2C == false) {
            if (sp28 != false) {
                for (var_s1 = 0x10; var_s1 > sy; var_s1--) {
                    if (aif_field[var_s1][sx].st == 4) {
                        for (var_a2_2 = var_s1 + 1; var_a2_2 < 0x11; var_a2_2++) {
                            if (aif_field[var_a2_2][sx].st != 0xA) {
                                break;
                            }
                        }

                        if (var_a2_2 != var_s1 + 1) {
                            aif_field[var_a2_2 - 1][sx].st = 4;
                            aif_field[var_a2_2 - 1][sx].co = aif_field[var_s1][sx].co;
                            aif_field[var_s1][sx].st = 0xA;
                            aif_field[var_s1][sx].co = 3;
                        }
                    }
                }
            }

            for (var_a2_2 = sy + 1; (var_a2_2 < 0x11) && (aif_field[var_a2_2][sx].st == 0xA); var_a2_2++) {
                ;
            }

            if (var_a2_2 != sy + 1) {
                aif_field[var_a2_2 - 1][sx].st = 4;
                aif_field[var_a2_2 - 1][sx].co = aif_field[sy][sx].co;
                aif_field[sy][sx].st = 0xA;
                aif_field[sy][sx].co = 3;

                var_s0 = 1;
                sy = var_a2_2 - 1;
                if (sp28 == false) {
                    ag->sub = 1;
                }
                sp2C = aifSearchLineCore(sx, sy, 0);
            }
        }

        if (aifEraseLineCore(sx, sy)) {
            var_s4 = 1;
            ag->pri += 0x2710;
        }

        if (sp2C == false) {
            ag->only[1] = aifMiniAloneCapNumber(sx, sy, var_s0, ec);
            ag->wonly[1] = aifMiniAloneCapNumberW(sx, sy, var_s0, ec);
        }

        for (var_a2_2 = 0; var_a2_2 < 0xA; var_a2_2++) {
            ag->hei[1][var_a2_2] = hei_data[var_a2_2];
            ag->wid[1][var_a2_2] = wid_data[var_a2_2];
        }
    }

    if (evs_gamemode == GMD_FLASH) {
        OnVirusP = OnVirusP_org + 0x7D0;
        if (var_s4 == 0) {
            if (ec != 0) {
                if (search_Vflash(mx, my, mco) != false) {
                    var_s4 = 1;
                }
                if (search_Vflash(sx, sy, sco) != false) {
                    var_s4 = 1;
                }
                if (var_s4 != 0) {
                    ag->pri += 0xBB8;
                }
            } else if (ag->tory == evs_gamemode) {
                if (search_Vflash(mx, my, mco)) {
                    var_s4 = 1;
                }
                if (search_Vflash(sx, sy, sco)) {
                    var_s4 = 1;
                }
                if (var_s4 != 0) {
                    ag->pri += 0x3E8;
                }
            }
        }
    }

    ag->pri += aifMiniPointK3(ag->hei[0], 0, &ag->elin[0], 1, ag->tory, ec);
    ag->pri += aifMiniPointK3(ag->hei[1], ag->sub, &ag->elin[ag->sub], 1, ag->tory, ec);
    ag->pri += aifMiniPointK3(ag->wid[0], 0, &ag->elin[0], 0, ag->tory, ec);
    ag->pri += aifMiniPointK3(ag->wid[1], ag->sub, &ag->elin[ag->sub], 0, ag->tory, ec);

    if (AloneCapP[ag->only[0]] != 0) {
        ag->pri += AloneCapP[ag->only[0]];
    }
    if (AloneCapP[ag->only[1]] != 0) {
        ag->pri += AloneCapP[ag->only[1]];
    }
    if ((AloneCapP[ag->only[0]] != 0) && (AloneCapP[ag->only[1]] != 0)) {
        ag->pri -= (0x11 - temp) * LPriP;
    }
    if (AloneCapWP[ag->wonly[0]] != 0) {
        ag->pri += AloneCapWP[ag->only[0]];
    }
    if (AloneCapWP[ag->wonly[1]] != 0) {
        ag->pri += AloneCapWP[ag->only[1]];
    }

    ag->pri += (s32)(EraseLinP[ag->hei[0][0] + ag->hei[1][0]] * HeiEraseLinRate);
    ag->pri += (s32)(EraseLinP[ag->wid[0][0] + ag->wid[1][0]] * WidEraseLinRate);

    if ((OnVirusP != 0) && (temp < 0x10)) {
        var_s0 = 1;

        for (var_s1 = temp - 1; var_s1 >= 4; var_s1--) {
            if ((aiFieldData[var_s1][mx].st >= 5) && (aiFieldData[var_s1][mx].st <= 7)) {
                var_s0 = 0;
                break;
            }
        }

        if (var_s0 == 1) {
            var_s0 = 0;

            for (var_s1 = temp + 1; var_s1 < 0x11; var_s1 += 1) {
                if ((aiFieldData[var_s1][mx].st >= 5) && (aiFieldData[var_s1][mx].st <= 7)) {
                    var_s0 = 1;
                    break;
                }
            }
        }

        var_s2 = 1;
        for (var_s1 = sp30 - 1; var_s1 >= 4; var_s1--) {
            if ((aiFieldData[var_s1][sx].st >= 5) && (aiFieldData[var_s1][sx].st <= 7)) {
                var_s2 = 0;
                break;
            }
        }

        if (var_s2 != 0) {
            var_s2 = 0;
            for (var_s1 = sp30 + 1; var_s1 < 0x11; var_s1++) {
                if ((aiFieldData[var_s1][sx].st >= 5) && (aiFieldData[var_s1][sx].st <= 7)) {
                    var_s2 = 1;
                    break;
                }
            }
        }

        var_s4 = 0;
        if (evs_gamemode == GMD_FLASH) {
            if (var_s0 != 0) {
                for (var_s1 = temp + 1; var_s1 < 0x11; var_s1++) {
                    if (flash_virus(mx, var_s1) != -1) {
                        var_s4 += OnVirusP;
                    }
                }
            }

            if (var_s2 != 0) {
                for (var_s1 = sp30 + 1; var_s1 < 0x11; var_s1++) {
                    if (flash_virus(sx, var_s1) != -1) {
                        var_s4 += OnVirusP;
                    }
                }
            }
        }

        if (aiFieldData[my + 1][mx].st < 8U) {
            if (var_s0 != 0) {
                if ((ag->hei[0][2] >= (((ec != 0) && (ag->tory == 0)) ? 3 : 2)) && (ag->hei[0][5] >= 4)) {
                    if (ag->tory == 0) {
                        if (ec != 0) {
                            ag->pri += (OnVirusP + var_s4) * 2;
                        } else if (sp28 == false) {
                            ag->pri -= OnVirusP * 2;
                        }
                    } else {
                        if (var_s2 != 0) {
                            if ((ag->hei[1][3] >= 2) && (ag->hei[1][5] >= 4)) {
                                ag->pri += OnVirusP + var_s4;
                            } else {
                                ag->pri -= OnVirusP * 2;
                            }
                        } else {
                            ag->pri += OnVirusP + var_s4;
                        }
                    }
                } else {
                    ag->pri -= OnVirusP * 2;
                }
            } else if (var_s2 != 0) {
                if ((ag->hei[1][3] >= 2) && (ag->hei[1][5] >= 4)) {
                    if ((ag->hei[0][2] >= 3) && (ag->hei[0][5] >= 4)) {
                        ag->pri += OnVirusP + var_s4;
                    } else {
                        ag->pri -= OnVirusP * 2;
                    }
                } else {
                    ag->pri -= OnVirusP * 2;
                }
            }
        } else if (var_s2 != 0) {
            if ((ag->hei[1][2] >= 2) && (ag->hei[1][5] >= 4)) {
                if (var_s0 != 0) {
                    if ((ag->hei[0][3] >= 2) && (ag->hei[0][5] >= 4)) {
                        ag->pri += OnVirusP + var_s4;
                    } else {
                        ag->pri -= OnVirusP * 2;
                    }
                } else {
                    ag->pri += OnVirusP + var_s4;
                }
            } else {
                ag->pri -= OnVirusP * 2;
            }
        } else if (var_s0 != 0) {
            if ((ag->hei[0][3] >= 2) && (ag->hei[0][5] >= 4)) {
                if ((ag->hei[1][2] >= 3) && (ag->hei[1][5] >= 4)) {
                    ag->pri += OnVirusP + var_s4;
                } else {
                    ag->pri -= OnVirusP * 2;
                }
            } else {
                ag->pri -= OnVirusP * 2;
            }
        }

        if ((sp28 != false) && (ec == 0) && (ag->tory == 0) && (temp < 0x10)) {
            var_a2_2 = 0;

            for (var_s0 = temp + 1; var_s0 < 0x11; var_s0++) {
                if ((aiFieldData[var_s0][sx].st >= 8U) || (aiFieldData[var_s0][sx].co != mco)) {
                    var_a2_2 = 1;
                    break;
                }
            }

            if (var_a2_2 != 0) {
                var_a2_2 = 0;
                for (var_s1 = var_s0; var_s1 < 0x11; var_s1++) {
                    if ((aiFieldData[var_s1][sx].st >= 5) && (aiFieldData[var_s1][sx].st <= 7)) {
                        var_a2_2 = 1;
                        break;
                    }
                }
            }

            if (var_a2_2 != 0) {
                for (var_s1 = var_s0; var_s1 < 0x11; var_s1++) {
                    if (aiFieldData[var_s1][sx].st < 8) {
                        if (aiFieldData[var_s1][sx].co == sco) {
                            ag->pri += (OnVirusP + var_s4) * 4;
                        } else {
                            ag->pri -= OnVirusP * 2;
                        }
                        break;
                    }
                }
            }
        }
    }

    for (var_a0 = 0; var_a0 < 8; var_a0++) {
        for (var_s1 = 1; var_s1 < 0x11; var_s1++) {
            if (aif_field[var_s1][var_a0].st != 0xA) {
                ss[var_a0] = var_s1 - 1;
                break;
            }
        }
    }

    ag->dead = 0;
    var_s0 = 0;
    if ((ss[sx] < 4U) && (sy < 5) && (sy > 0)) {
        if (aif_field[sy][sx].st != 0xA) {
            if (ag->hei[1][2] + ss[sx] < 4) {
                ag->dead += (bad_point[sx] / (sy * 2 - 1));
                var_s0 = 1;
            }
        }
    }

    if ((ss[mx] < 4) && (my < 4) && (my > 0) && ((ec == 0) || (ag->tory != 0))) {
        if ((aif_field[my][mx].st != 0xA) && ((ag->hei[0][2] + ss[mx]) < 4)) {
            if (var_s0 != 0) {
                ag->dead += bad_point2[mx] + bad_point2[sx] - (bad_point[sx] / (sy * 2 - 1));
            } else {
                ag->dead += bad_point[mx] / (my * 2 - 1);
            }
        }
    }

    ag->pri += ag->dead;
    if (aiWall != 0) {
        if (WallRate[aiWall][mx] > WallRate[aiWall][sx]) {
            ag->pri = ag->pri * WallRate[aiWall][mx] / 10;
        } else {
            ag->pri = ag->pri * WallRate[aiWall][sx] / 10;
        }
    }

    if (sp28) {
        return 1;
    }
    if (sp2C) {
        return 2;
    }
    return 0;
}

#if VERSION_US
/**
 * Original name: aiHiruAllPriSet
 */
#if 0
u8 aifRensaCheckCore(struct_game_state_data *, u8 *, u32, u8, s32, s32, u32, s32, s32, s32); /* extern */
s32 aifSearchLineMS(u8 *, s32, u8, s32);              /* extern */
extern u16 aiHiErB;
extern u16 aiPriOfs;
extern u16 aiHiErY;
extern u16 aiHiErR;
extern u16 aiHiEraseCtr;
extern s16 D_8008856A;
extern s16 RensaP;
extern s16 RensaMP;

void aiHiruAllPriSet(struct_game_state_data *gameStateDataRef) {
    struct_game_state_data *sp2C;
    s32 sp34;
    u8 sp3F;
    s8 sp47;                                        /* compiler-managed */
    u8 sp4F;
    u8 sp57;
    u8 sp5F;
    u8 sp67;
    u8 sp6F;
    s32 sp8C;
    s32 sp90;
    s32 temp_a0_3;
    s32 temp_a0_4;
    s32 temp_fp;
    s32 temp_s0;
    s32 temp_s0_11;
    s32 temp_s0_13;
    s32 temp_s0_14;
    s32 temp_s0_3;
    s32 temp_s0_5;
    s32 temp_s0_6;
    s32 temp_s0_8;
    s32 temp_s0_9;
    s32 temp_s1;
    s32 temp_s2;
    s32 temp_s2_2;
    s32 temp_s2_3;
    s32 temp_s4;
    s32 temp_s5_2;
    s32 temp_s5_3;
    s32 temp_t4;
    s32 temp_t4_3;
    s32 temp_t4_4;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 temp_v0_5;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 var_a0;
    s32 var_a1;
    s32 var_a1_2;
    s32 var_a2_2;
    s32 var_a3;
    s32 var_s0;
    s32 var_s0_2;
    s32 var_s0_3;
    s32 var_s1_2;
    s32 var_s1_3;
    s32 var_s2;
    s32 var_s2_2;
    s32 var_s2_3;
    s32 var_s4;
    s32 var_s4_2;
    s32 var_s5;
    s32 var_t1_2;
    s32 var_v0;
    s8 temp_a0_2;
    s8 var_t1;
    u32 temp_s1_2;
    u32 temp_s1_3;
    u32 temp_s1_4;
    u32 temp_s1_5;
    u32 temp_s1_6;
    u32 temp_s1_7;
    u32 temp_s2_4;
    u32 temp_s5;
    u32 temp_s6;
    u8 *temp_s3;
    u8 temp_a0;
    u8 temp_s0_10;
    u8 temp_s0_12;
    u8 temp_s0_2;
    u8 temp_s0_4;
    u8 temp_s0_7;
    u8 temp_t4_2;
    u8 var_a2;
    u8 var_s1;
    u8 var_v1;

    sp2C = gameStateDataRef;
    sp34 = 0;
    if ((s32) aiFlagCnt > 0) {
        sp8C = 0;
        do {
            if (aiFlag[sp8C].unk_0 != 0) {
                temp_s3 = &aiFlag[sp8C];
                bcopy(aiFieldData, &aif_field, 0x110);
                var_a2 = temp_s3->unk_3;
                temp_a0 = temp_s3->unk_2;
                temp_s4 = temp_a0 - 1;
                if (temp_s3->unk_1 == 0) {
                    var_s5 = temp_s4;
                    var_s2 = var_s5;
                    temp_a0_2 = var_a2 - 1;
                    sp3F = var_a2;
                    sp47 = temp_a0_2;
                    sp57 &= -(temp_a0_2 < 1);
                    if (temp_s3->unk_4 == 0) {
                        var_s1 = aiNext[1];
                        if (temp_a0_2 > 0) {
                            sp4F = *aiNext;
                        }
                    } else {
                        var_s1 = *aiNext;
                        if (temp_a0_2 > 0) {
                            sp4F = aiNext[1];
                        }
                    }
                    if (sp3F != 0) {
                        temp_v0 = ((var_s5 & 0xFF) * 2) + (sp3F * 0x10);
                        *(&B_800FAD41 + temp_v0) = 1;
                        *(&aif_field + temp_v0) = var_s1;
                    }
                    if ((u8) sp47 != 0) {
                        temp_v0_2 = ((var_s2 & 0xFF) * 2) + ((u8) sp47 * 0x10);
                        *(&B_800FAD41 + temp_v0_2) = sp57;
                        *(&aif_field + temp_v0_2) = sp4F;
                    }
                    temp_a0_3 = temp_s4 * 2;
                    if (*(&aif_field + (temp_a0_3 + ((var_a2 - 1) * 0x10))) == *(&aif_field + (temp_a0_3 + (var_a2 * 0x10)))) {

                    }
                    var_a1 = temp_s4;
                    var_a3 = var_s1 & 0xFF;
                    sp90 = (s32) 1;
                } else {
                    var_s5 = temp_s4;
                    if (*(&B_800FAD41 + ((temp_s4 * 2) + ((var_a2 + 1) * 0x10))) != 0xA) {
                        sp3F = var_a2;
                        var_t1 = 2;
                        var_s2 = (s32) temp_a0;
                        sp47 = sp3F;
                        sp57 = 3;
                        if (temp_s3->unk_4 == 0) {
                            var_s1 = *aiNext;
                            sp4F = aiNext[1];
                        } else {
                            var_s1 = aiNext[1];
                            sp4F = *aiNext;
                        }
                    } else {
                        var_s5 = (s32) temp_a0;
                        sp3F = var_a2;
                        var_t1 = 3;
                        var_s2 = temp_s4;
                        sp47 = sp3F;
                        sp57 = 2;
                        if (temp_s3->unk_4 == 0) {
                            var_s1 = aiNext[1];
                            sp4F = *aiNext;
                        } else {
                            var_s1 = *aiNext;
                            sp4F = aiNext[1];
                        }
                    }
                    var_a3 = var_s1 & 0xFF;
                    if (var_a3 == sp4F) {

                    }
                    var_a2 = sp3F;
                    if (var_a2 != 0) {
                        temp_v0_3 = ((var_s5 & 0xFF) * 2) + (var_a2 * 0x10);
                        *(&B_800FAD41 + temp_v0_3) = var_t1;
                        *(&aif_field + temp_v0_3) = var_s1;
                    }
                    if (sp47 != 0) {
                        temp_v0_4 = ((var_s2 & 0xFF) * 2) + (sp47 * 0x10);
                        *(&B_800FAD41 + temp_v0_4) = sp57;
                        *(&aif_field + temp_v0_4) = sp4F;
                    }
                    var_a1 = var_s5 & 0xFF;
                    sp90 = (s32) var_t1;
                }
                temp_v0_5 = aifSearchLineMS(temp_s3, var_a1, var_a2, var_a3);
                var_t1_2 = sp90;
                if ((temp_v0_5 != 0) && (RensaP != 0)) {
                    if (temp_v0_5 == 2) {
                        temp_s0 = var_s5;
                        var_s5 = var_s2;
                        var_s2 = temp_s0;
                        temp_t4_2 = sp47;
                        sp47 = sp3F;
                        temp_s0_2 = var_s1;
                        var_s1 = sp4F;
                        sp4F = temp_s0_2;
                        temp_s0_3 = var_t1_2;
                        var_t1_2 = (s32) sp57;
                        sp3F = temp_t4_2;
                        sp57 = (u8) temp_s0_3;
                    }
                    temp_s6 = var_s5 & 0xFF;
                    temp_fp = var_s1 & 0xFF;
                    temp_s1 = var_t1_2 & 0xFF;
                    temp_s5 = var_s2 & 0xFF;
                    sp5F = aifRensaCheckCore(sp2C, temp_s3, temp_s6, sp3F, temp_fp, temp_s1, temp_s5, (s32) sp47, 0, (s32) sp57);
                    aiHiErR = aiHiEraseCtr;
                    sp67 = aifRensaCheckCore(sp2C, temp_s3, temp_s6, sp3F, temp_fp, temp_s1, temp_s5, (s32) sp47, 1, (s32) sp57);
                    aiHiErY = aiHiEraseCtr;
                    sp6F = aifRensaCheckCore(sp2C, temp_s3, temp_s6, sp3F, temp_fp, temp_s1, temp_s5, (s32) sp47, 2, (s32) sp57);
                    aiHiErB = aiHiEraseCtr;
                    var_s0 = 0;
                    if (temp_s6 == temp_s5) {
                        temp_s2 = var_s2 - 1;
                        if (sp47 < sp3F) {
                            temp_s1_2 = temp_s2 & 0xFF;
                            sp47 += 1;
                            temp_s5_2 = (u8) sp47 * 0x10;
                            if (sp2C->unk_29C[0][0][(temp_s1_2 * 2) + temp_s5_2] == 0xA) {
                                temp_s0_4 = aifRensaCheckCore(sp2C, temp_s3, temp_s6, sp3F, temp_fp, 3, temp_s1_2, (s32) (u8) sp47, 0, 2);
                                temp_s0_5 = temp_s0_4 | aifRensaCheckCore(sp2C, temp_s3, temp_s6, sp3F, temp_fp, 3, temp_s1_2, (s32) (u8) sp47, 1, 2);
                                var_s0 = temp_s0_5 | aifRensaCheckCore(sp2C, temp_s3, temp_s6, sp3F, temp_fp, 3, temp_s1_2, (s32) (u8) sp47, 2, 2);
                            }
                            temp_s1_3 = (temp_s2 + 2) & 0xFF;
                            sp57 = 3;
                            if (sp2C->unk_29C[0][0][(temp_s1_3 * 2) + temp_s5_2] == 0xA) {
                                temp_s0_6 = var_s0 | aifRensaCheckCore(sp2C, temp_s3, temp_s6, sp3F, temp_fp, 2, temp_s1_3, (s32) (u8) sp47, 0, 3);
                                var_s0_2 = temp_s0_6 | aifRensaCheckCore(sp2C, temp_s3, temp_s6, sp3F, temp_fp, 2, temp_s1_3, (s32) (u8) sp47, 1, 3);
                                goto block_53;
                            }
                        } else {
                            temp_s1_4 = temp_s2 & 0xFF;
                            sp47 = (u8) sp47 - 1;
                            temp_s5_3 = (u8) sp47 * 0x10;
                            if (sp2C->unk_29C[0][0][(temp_s1_4 * 2) + temp_s5_3] == 0xA) {
                                temp_s0_7 = aifRensaCheckCore(sp2C, temp_s3, temp_s6, sp3F, temp_fp, 3, temp_s1_4, (s32) (u8) sp47, 0, 2);
                                temp_s0_8 = temp_s0_7 | aifRensaCheckCore(sp2C, temp_s3, temp_s6, sp3F, temp_fp, 3, temp_s1_4, (s32) (u8) sp47, 1, 2);
                                var_s0 = temp_s0_8 | aifRensaCheckCore(sp2C, temp_s3, temp_s6, sp3F, temp_fp, 3, temp_s1_4, (s32) (u8) sp47, 2, 2);
                            }
                            temp_s1_5 = (temp_s2 + 2) & 0xFF;
                            sp57 = 3;
                            if (sp2C->unk_29C[0][0][(temp_s1_5 * 2) + temp_s5_3] == 0xA) {
                                temp_s0_9 = var_s0 | aifRensaCheckCore(sp2C, temp_s3, temp_s6, sp3F, temp_fp, 2, temp_s1_5, (s32) (u8) sp47, 0, 3);
                                var_s0_2 = temp_s0_9 | aifRensaCheckCore(sp2C, temp_s3, temp_s6, sp3F, temp_fp, 2, temp_s1_5, (s32) (u8) sp47, 1, 3);
                                goto block_53;
                            }
                        }
                    } else {
                        temp_v1 = sp47 * 0x10;
                        if (temp_s5 < temp_s6) {
                            temp_s2_2 = var_s2 + 2;
                            temp_s1_6 = temp_s2_2 & 0xFF;
                            if (sp2C->unk_29C[0][0][(temp_s1_6 * 2) + temp_v1] == 0xA) {
                                temp_s0_10 = aifRensaCheckCore(sp2C, temp_s3, temp_s6, sp3F, temp_fp, 2, temp_s1_6, (s32) sp47, 0, 3);
                                temp_s0_11 = temp_s0_10 | aifRensaCheckCore(sp2C, temp_s3, temp_s6, sp3F, temp_fp, 2, temp_s1_6, (s32) sp47, 1, 3);
                                var_s0 = temp_s0_11 | aifRensaCheckCore(sp2C, temp_s3, temp_s6, sp3F, temp_fp, 2, temp_s1_6, (s32) sp47, 2, 3);
                            }
                            var_s2_2 = temp_s2_2 - 1;
                        } else {
                            temp_s2_3 = var_s2 - 2;
                            temp_s1_7 = temp_s2_3 & 0xFF;
                            if (sp2C->unk_29C[0][0][(temp_s1_7 * 2) + temp_v1] == 0xA) {
                                temp_s0_12 = aifRensaCheckCore(sp2C, temp_s3, temp_s6, sp3F, temp_fp, 3, temp_s1_7, (s32) sp47, 0, 2);
                                temp_s0_13 = temp_s0_12 | aifRensaCheckCore(sp2C, temp_s3, temp_s6, sp3F, temp_fp, 3, temp_s1_7, (s32) sp47, 1, 2);
                                var_s0 = temp_s0_13 | aifRensaCheckCore(sp2C, temp_s3, temp_s6, sp3F, temp_fp, 3, temp_s1_7, (s32) sp47, 2, 2);
                            }
                            var_s2_2 = temp_s2_3 + 1;
                        }
                        temp_s2_4 = var_s2_2 & 0xFF;
                        sp47 = (u8) sp47 - 1;
                        sp57 = 0;
                        if (sp2C->unk_29C[0][0][(temp_s2_4 * 2) + ((u8) sp47 * 0x10)] == 0xA) {
                            temp_s0_14 = var_s0 | aifRensaCheckCore(sp2C, temp_s3, temp_s6, sp3F, temp_fp, 1, temp_s2_4, (s32) (u8) sp47, 0, 0);
                            var_s0_2 = temp_s0_14 | aifRensaCheckCore(sp2C, temp_s3, temp_s6, sp3F, temp_fp, 1, temp_s2_4, (s32) (u8) sp47, 1, 0);
block_53:
                            var_s0 = var_s0_2 | aifRensaCheckCore(sp2C, temp_s3, temp_s6, sp3F);
                        }
                    }
                    switch (sp4F) {                 /* irregular */
                        case 0x0:
                            var_a1_2 = temp_s3->unk_8 + ((s16) aiHiErR * D_8008856A);
                            temp_s3->unk_8 = var_a1_2;
                            if (sp5F != 0) {
                                if ((((sp67 != 0) | (sp6F != 0)) != 0) || (var_s0 & 0xFF)) {
                                    var_v0 = var_a1_2 + (RensaP * sp5F);
                                } else {
                                    var_v0 = var_a1_2 + (RensaP * sp5F);
                                }
                                goto block_88;
                            }
                            var_v1 = sp67;
block_68:
                            if ((((var_v1 != 0) | (sp6F != 0)) == 0) && !(var_s0 & 0xFF)) {
                                temp_s3->unk_8 = var_a1_2;
                            } else {
block_86:
                                if (sp3F >= 3U) {
                                    var_v0 = var_a1_2 + RensaMP;
block_88:
                                    temp_s3->unk_8 = var_v0;
                                }
                            }
                            break;
                        case 0x1:
                            var_a1_2 = temp_s3->unk_8 + ((s16) aiHiErY * D_8008856A);
                            temp_s3->unk_8 = var_a1_2;
                            if (sp67 != 0) {
                                if ((((sp5F != 0) | (sp6F != 0)) != 0) || (var_s0 & 0xFF)) {
                                    var_v0 = var_a1_2 + (RensaP * sp67);
                                } else {
                                    var_v0 = var_a1_2 + (RensaP * sp67);
                                }
                                goto block_88;
                            }
                            var_v1 = sp5F;
                            goto block_68;
                        case 0x2:
                            var_a1_2 = temp_s3->unk_8 + ((s16) aiHiErB * D_8008856A);
                            temp_s3->unk_8 = var_a1_2;
                            if (sp6F != 0) {
                                if ((((sp67 != 0) | (sp5F != 0)) != 0) || (var_s0 & 0xFF)) {
                                    var_v0 = var_a1_2 + (RensaP * sp6F);
                                } else {
                                    var_v0 = var_a1_2 + (RensaP * sp6F);
                                }
                                goto block_88;
                            }
                            if (((sp67 != 0) | (sp5F != 0)) == 0) {
                                if (!(var_s0 & 0xFF)) {
                                    temp_s3->unk_8 = var_a1_2;
                                } else {
                                    goto block_86;
                                }
                            } else {
                                goto block_86;
                            }
                            break;
                    }
                }
            } else {
                (aiFlag + 8)[sp8C] = 0xFFF0BDC0;
            }
            sp8C += 0x40;
            temp_t4 = sp34 + 1;
            sp34 = temp_t4;
        } while (temp_t4 < (s32) aiFlagCnt);
    }
    if ((u8) sp2C->unk_23E != 0) {
        var_s4 = 0xFFF0BDBF;
        var_s0_3 = 0;
        sp34 = 0;
        if ((s32) aiFlagCnt > 0) {
            var_s1_2 = 0;
            do {
                var_a2_2 = 0;
                if (aiPriOfs != 0) {
                    var_a2_2 = genrand((s32) aiPriOfs) & 0xFFFF;
                }
                temp_v1_2 = (aiFlag + 8)[var_s1_2] + var_a2_2;
                if (var_s4 < temp_v1_2) {
                    var_s4 = temp_v1_2;
                    var_s0_3 = sp34;
                }
                var_s1_2 += 0x40;
                temp_t4_3 = sp34 + 1;
                sp34 = temp_t4_3;
            } while (temp_t4_3 < (s32) aiFlagCnt);
        }
    } else {
        var_s2_3 = 0xFFF0BDBF;
        var_s4_2 = -0xF4241;
        var_s0_3 = 0;
        sp34 = 0;
        if ((s32) aiFlagCnt > 0) {
            var_s1_3 = 0;
            do {
                if (aiPriOfs != 0) {
                    var_a0 = (aiPriOfs + 0x64) & 0xFFFF;
                } else {
                    var_a0 = 0x64;
                }
                temp_a0_4 = (aiFlag + 8)[var_s1_3];
                temp_v1_3 = temp_a0_4 + (genrand(var_a0) & 0xFFFF);
                if (var_s2_3 < temp_v1_3) {
                    var_s2_3 = temp_v1_3;
                    if (var_s4_2 < temp_a0_4) {
                        var_s4_2 = temp_a0_4;
                    }
                    var_s0_3 = sp34;
                }
                if (*(aiFlag + 8 + (var_s0_3 << 6)) < var_s4_2) {
                    sp2C->unk_23E = 1;
                }
                var_s1_3 += 0x40;
                temp_t4_4 = sp34 + 1;
                sp34 = temp_t4_4;
            } while (temp_t4_4 < (s32) aiFlagCnt);
        }
    }
    decide = (s8) var_s0_3;
}
#else
INCLUDE_ASM("asm/us/nonmatchings/main_segment/aiset", aiHiruAllPriSet);
#endif
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/aiset", aiHiruAllPriSet);
#endif

#if VERSION_CN
#ifdef NON_MATCHING
void aiHiruAllPriSet(struct_game_state_data *gameStateDataRef) {
    struct_aiFlag *temp;
    s32 sp30;
    s32 temp_s0;
    s32 temp2;
    s32 var_s2;
    s32 var_t1;
    s32 var_s3_2;

    u8 var_s0;
    u8 var_s1;
    u8 var_s7;
    u8 var_s4;
    u8 var_s5;
    u8 var_s6;
    u8 var_s3;
    u8 var_v0_2;
    u8 sp38;
    u8 sp3C;
    u8 sp40;
    u8 sp44;

    for (sp30 = 0; sp30 < aiFlagCnt; sp30++) {
        if (aiFlag[sp30].ok != 0) {
            temp = &aiFlag[sp30];

            bcopy(aiFieldData, aif_field, sizeof(Unk_AIFEntry) * GAME_MAP_ROWS * GAME_MAP_COLUMNS);

            temp_s0 = temp->x - 1;
            temp2 = temp->y;
            var_t1 = 0;

            if (temp->tory == 0) {
                var_s6 = temp_s0;
                var_s7 = temp2;
                var_s4 = 1;
                var_s1 = temp_s0;
                var_s3 = temp2 - 1;

                if (temp2 - 1 > 0) {
                    sp38 = 0;
                }

                if (temp->rev == 0) {
                    var_s5 = aiNext[1];
                    if (temp2 - 1 > 0) {
                        var_v0_2 = aiNext[0];
                    }
                } else {
                    var_s5 = aiNext[0];
                    if (temp2 - 1 > 0) {
                        var_v0_2 = aiNext[1];
                    }
                }

                if (var_s7 != 0) {
                    aif_field[var_s7][var_s6].st = var_s4;
                    aif_field[var_s7][var_s6].co = var_s5;
                }

                if (var_s3 != 0) {
                    aif_field[var_s3][var_s1].st = sp38;
                    aif_field[var_s3][var_s1].co = var_v0_2;
                }

                if (aif_field[temp2 - 1][temp_s0].st == aif_field[temp2][temp_s0].st) {
                    var_t1 = 1;
                }
                var_s2 = aifSearchLineMS(temp, temp_s0, temp2, var_s5, temp_s0, temp2 - 1, var_v0_2, var_t1);
            } else {
                if (aif_field[temp2 + 1][temp_s0].st != 0xA) {
                    var_s6 = temp_s0;
                    var_s7 = temp2;
                    var_s4 = 2;
                    var_s1 = temp_s0 + 1;
                    var_s3 = temp2;
                    sp38 = 3;
                    if (temp->rev != 0) {
                        var_s5 = aiNext[1];
                        var_v0_2 = aiNext[0];
                    } else {
                        var_s5 = aiNext[0];
                        var_v0_2 = aiNext[1];
                    }
                } else {
                    var_s6 = temp_s0 + 1;
                    var_s7 = temp2;
                    var_s4 = 3;
                    var_s1 = temp_s0;
                    var_s3 = temp2;
                    sp38 = 2;
                    if (temp->rev == 0) {
                        var_s5 = aiNext[1];
                        var_v0_2 = aiNext[0];
                    } else {
                        var_s5 = aiNext[0];
                        var_v0_2 = aiNext[1];
                    }
                }
                if (var_s5 == var_v0_2) {
                    var_t1 = 1;
                }
                if (var_s7 != 0) {
                    aif_field[var_s7][var_s6].st = var_s4;
                    aif_field[var_s7][var_s6].co = var_s5;
                }
                if (var_s3 != 0) {
                    aif_field[var_s3][var_s1].st = sp38;
                    aif_field[var_s3][var_s1].co = var_v0_2;
                }
                var_s2 = aifSearchLineMS(temp, var_s6, var_s7, var_s5, var_s1, var_s3, var_v0_2, var_t1);
            }

            if ((var_s2 != 0) && (RensaP != 0)) {
                if (var_s2 == 2) {
                    var_s0 = var_s6;
                    var_s6 = var_s1;
                    var_s1 = var_s0;

                    var_s0 = var_s7;
                    var_s7 = var_s3;
                    var_s3 = var_s0;

                    var_s0 = var_s5;
                    var_s5 = var_v0_2;
                    var_v0_2 = var_s0;

                    var_s0 = var_s4;
                    var_s4 = sp38;
                    sp38 = var_s0;
                }

                sp3C =
                    aifRensaCheckCore(gameStateDataRef, temp, var_s6, var_s7, var_s5, var_s4, var_s1, var_s3, 0, sp38);
                aiHiErR = aiHiEraseCtr;
                sp40 =
                    aifRensaCheckCore(gameStateDataRef, temp, var_s6, var_s7, var_s5, var_s4, var_s1, var_s3, 1, sp38);
                aiHiErY = aiHiEraseCtr;
                sp44 =
                    aifRensaCheckCore(gameStateDataRef, temp, var_s6, var_s7, var_s5, var_s4, var_s1, var_s3, 2, sp38);
                aiHiErB = aiHiEraseCtr;

                var_s0 = 0;
                if (var_s6 == var_s1) {
                    if (var_s3 < var_s7) {
                        var_s4 = 3;
                        var_s1--;
                        var_s3++;
                        sp38 = 2;
                        if (gameStateDataRef->blk[var_s3][var_s1].st == 0xA) {
                            var_s0 |= aifRensaCheckCore(gameStateDataRef, temp, var_s6, var_s7, var_s5, var_s4, var_s1,
                                                        var_s3, 0, sp38);
                            var_s0 |= aifRensaCheckCore(gameStateDataRef, temp, var_s6, var_s7, var_s5, var_s4, var_s1,
                                                        var_s3, 1, sp38);
                            var_s0 |= aifRensaCheckCore(gameStateDataRef, temp, var_s6, var_s7, var_s5, var_s4, var_s1,
                                                        var_s3, 2, sp38);
                        }

                        var_s4 = 2;
                        var_s1 += 2;
                        sp38 = 3;
                        if (gameStateDataRef->blk[var_s3][var_s1].st == 0xA) {
                            var_s0 |= aifRensaCheckCore(gameStateDataRef, temp, var_s6, var_s7, var_s5, var_s4, var_s1,
                                                        var_s3, 0, sp38);
                            var_s0 |= aifRensaCheckCore(gameStateDataRef, temp, var_s6, var_s7, var_s5, var_s4, var_s1,
                                                        var_s3, 1, sp38);
                            var_s0 |= aifRensaCheckCore(gameStateDataRef, temp, var_s6, var_s7, var_s5, var_s4, var_s1,
                                                        var_s3, 2, sp38);
                        }
                    } else {
                        var_s4 = 3;
                        var_s1--;
                        var_s3--;
                        sp38 = 2;
                        if (gameStateDataRef->blk[var_s3][var_s1].st == 0xA) {
                            var_s0 |= aifRensaCheckCore(gameStateDataRef, temp, var_s6, var_s7, var_s5, var_s4, var_s1,
                                                        var_s3, 0, sp38);
                            var_s0 |= aifRensaCheckCore(gameStateDataRef, temp, var_s6, var_s7, var_s5, var_s4, var_s1,
                                                        var_s3, 1, sp38);
                            var_s0 |= aifRensaCheckCore(gameStateDataRef, temp, var_s6, var_s7, var_s5, var_s4, var_s1,
                                                        var_s3, 2, sp38);
                        }

                        var_s4 = 2;
                        var_s1 += 2;
                        sp38 = 3;
                        if (gameStateDataRef->blk[var_s3][var_s1].st == 0xA) {
                            var_s0 |= aifRensaCheckCore(gameStateDataRef, temp, var_s6, var_s7, var_s5, var_s4, var_s1,
                                                        var_s3, 0, sp38);
                            var_s0 |= aifRensaCheckCore(gameStateDataRef, temp, var_s6, var_s7, var_s5, var_s4, var_s1,
                                                        var_s3, 1, sp38);
                            var_s0 |= aifRensaCheckCore(gameStateDataRef, temp, var_s6, var_s7, var_s5, var_s4, var_s1,
                                                        var_s3, 2, sp38);
                        }
                    }
                } else {
                    if (var_s1 < var_s6) {
                        var_s4 = 2;
                        var_s1 += 2;
                        sp38 = 3;
                        if (gameStateDataRef->blk[var_s3][var_s1].st == 0xA) {
                            var_s0 |= aifRensaCheckCore(gameStateDataRef, temp, var_s6, var_s7, var_s5, var_s4, var_s1,
                                                        var_s3, 0, sp38);
                            var_s0 |= aifRensaCheckCore(gameStateDataRef, temp, var_s6, var_s7, var_s5, var_s4, var_s1,
                                                        var_s3, 1, sp38);
                            var_s0 |= aifRensaCheckCore(gameStateDataRef, temp, var_s6, var_s7, var_s5, var_s4, var_s1,
                                                        var_s3, 2, sp38);
                        }

                        var_s4 = 1;
                        var_s1--;
                        var_s3--;
                        sp38 = 0;
                        if (gameStateDataRef->blk[var_s3][var_s1].st == 0xA) {
                            var_s0 |= aifRensaCheckCore(gameStateDataRef, temp, var_s6, var_s7, var_s5, var_s4, var_s1,
                                                        var_s3, 0, sp38);
                            var_s0 |= aifRensaCheckCore(gameStateDataRef, temp, var_s6, var_s7, var_s5, var_s4, var_s1,
                                                        var_s3, 1, sp38);
                            var_s0 |= aifRensaCheckCore(gameStateDataRef, temp, var_s6, var_s7, var_s5, var_s4, var_s1,
                                                        var_s3, 2, sp38);
                        }
                    } else {
                        var_s4 = 3;
                        var_s1 -= 2;
                        sp38 = 2;
                        if (gameStateDataRef->blk[var_s3][var_s1].st == 0xA) {
                            var_s0 |= aifRensaCheckCore(gameStateDataRef, temp, var_s6, var_s7, var_s5, var_s4, var_s1,
                                                        var_s3, 0, sp38);
                            var_s0 |= aifRensaCheckCore(gameStateDataRef, temp, var_s6, var_s7, var_s5, var_s4, var_s1,
                                                        var_s3, 1, sp38);
                            var_s0 |= aifRensaCheckCore(gameStateDataRef, temp, var_s6, var_s7, var_s5, var_s4, var_s1,
                                                        var_s3, 2, sp38);
                        }

                        var_s4 = 1;
                        var_s1++;
                        var_s3--;
                        sp38 = 0;
                        if (gameStateDataRef->blk[var_s3][var_s1].st == 0xA) {
                            var_s0 |= aifRensaCheckCore(gameStateDataRef, temp, var_s6, var_s7, var_s5, var_s4, var_s1,
                                                        var_s3, 0, sp38);
                            var_s0 |= aifRensaCheckCore(gameStateDataRef, temp, var_s6, var_s7, var_s5, var_s4, var_s1,
                                                        var_s3, 1, sp38);
                            var_s0 |= aifRensaCheckCore(gameStateDataRef, temp, var_s6, var_s7, var_s5, var_s4, var_s1,
                                                        var_s3, 2, sp38);
                        }
                    }
                }

                switch (var_v0_2) {
                    case 0:
                        temp->pri += aiHiErR * pri_point[7];
                        if (sp3C != 0) {
                            if ((sp40 != 0) || (sp44 != 0) || (var_s0 != 0)) {
                                temp->pri += RensaP * sp3C;
                            } else {
                                temp->pri += RensaP * sp3C;
                            }
                        } else {
                            if ((sp40 != 0) || (sp44 != 0) || (var_s0 != 0)) {
                                if (var_s7 >= 3U) {
                                    temp->pri += RensaMP;
                                }
                            } else {
                                temp->pri += 0;
                            }
                        }
                        break;

                    case 1:
                        temp->pri += aiHiErY * pri_point[7];
                        if (sp40 != 0) {
                            if ((sp3C != 0) || (sp44 != 0) || (var_s0 != 0)) {
                                temp->pri += RensaP * sp40;
                            } else {
                                temp->pri += RensaP * sp40;
                            }
                        } else {
                            if ((sp3C != 0) || (sp44 != 0) || (var_s0 != 0)) {
                                if (var_s7 >= 3U) {
                                    temp->pri += RensaMP;
                                }
                            }
                        }
                        break;

                    case 2:
                        temp->pri += (aiHiErB * pri_point[7]);
                        if (sp44 != 0) {
                            if ((sp40 != 0) || (sp3C != 0) || (var_s0 != 0)) {
                                temp->pri += RensaP * sp44;
                            } else {
                                temp->pri += RensaP * sp44;
                            }
                        } else {
                            if ((sp40 != 0) || (sp3C != 0) || (var_s0 != 0)) {
                                if (var_s7 >= 3U) {
                                    temp->pri += RensaMP;
                                }
                            }
                        }
                        break;
                }
            }
        } else {
            aiFlag[sp30].pri = -0xF4240;
        }
    }

    if (gameStateDataRef->ai.aiRandFlag != 0) {
        for (sp30 = var_s2 = 0, temp_s0 = -0xF4241; sp30 < aiFlagCnt; sp30++) {
            if (aiPriOfs != 0) {
                temp2 = genrand(aiPriOfs);
            } else {
                temp2 = 0;
            }

            if (temp_s0 < aiFlag[sp30].pri + temp2) {
                temp_s0 = aiFlag[sp30].pri + temp2;
                var_s2 = sp30;
            }
        }
    } else {
        for (sp30 = var_s2 = 0, temp_s0 = var_s3_2 = -0xF4241; sp30 < aiFlagCnt; sp30++) {
            if (aiPriOfs != 0) {
                temp2 = genrand(aiPriOfs + 0x64);
            } else {
                temp2 = genrand(0x64);
            }

            if (var_s3_2 < temp2 + aiFlag[sp30].pri) {
                var_s3_2 = temp2 + aiFlag[sp30].pri;
                if (temp_s0 < aiFlag[sp30].pri) {
                    temp_s0 = aiFlag[sp30].pri;
                }
                var_s2 = sp30;
            }

            if (aiFlag[var_s2].pri < temp_s0) {
                gameStateDataRef->ai.aiRandFlag = 1;
            }
        }
    }

    decide = var_s2;
}
#else
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/aiset", aiHiruAllPriSet);
#endif
#endif

/**
 * Original name: aiSetCharacter
 */
void aiSetCharacter(struct_game_state_data *xpw) {
    u8 var_a0_8;
    s32 var_a1_2;
    u8 var_a2_3;
    u8 var_a3_4;
    s32 var_s0;
    struct_ai_char_data *char_data;
    u8 var_s3;
    s32 var_s5;
    u8 var_s6;
    s32 var_t0_2;
    struct_ai_param *ptr;
    u8 var_t3_2;
    s32 var_v1;
    s32 var_t1;
    struct_ai_param(*aiDataPtr)[AI_PARAM_LEN2];

#if 0
    int i; // r8
    int j; // r1+0x8
    int x; // r9
    int y; // r1+0x8
    unsigned char badLine; // r3
    unsigned char leading; // r1+0x8
    unsigned char wall; // r28
    unsigned char hicaps; // r4
    unsigned char lowvrs; // r5
    int vrsCnt; // r6
    unsigned char char_no; // r9
    int aidt; // r27
    // struct_aiset_c_816 (* aiDataPtr)[][8]; // r1+0x8
    // struct_aiset_c_858 * char_data; // r26
    int doEffectFlag; // r4
    // struct_aiset_c_816 * ptr; // r4
#endif

    {
        s32 dummy = xpw->lv;

        if (dummy < 0x18) {
            dummy = 1;
        }
    }

    var_s3 = 0;

    for (var_t1 = 2; var_t1 < 6; var_t1++) {
        var_s0 = 0;

        for (var_v1 = 1; var_v1 < 4; var_v1++) {
            if (var_s0 == 0) {
                if (aiFieldData[var_v1][var_t1].st != 0xA) {
                    var_s0 = 1;
                    var_a1_2 = aiFieldData[var_v1][var_t1].co;
                }
            }

            if (var_s0 != 0) {
                if ((aiFieldData[var_v1 + 1][var_t1].st == 0xA) || (aiFieldData[var_v1 + 1][var_t1].co != var_a1_2)) {
                    if ((var_t1 == 3) || (var_t1 == 4)) {
                        var_s0 = 2;
                    } else {
                        var_s0 = 0;
                    }
                    break;
                }
            }
        }

        if (var_s0 != 0) {
            var_s3 = var_s0;
            if (var_s0 == 2) {
                break;
            }
        }
    }

    var_s6 = 0;
    var_t3_2 = 0x11;
    var_t0_2 = 0;

    for (var_t1 = 4; var_t1 < 8; var_t1++) {
        for (var_v1 = 1; var_v1 < 4; var_v1++) {
            if (aiFieldData[var_v1][var_t1].st != 0xA) {
                break;
            }
        }

        if (var_v1 < 4) {
            var_s6 |= 2;
            var_a1_2 = var_t1;
            break;
        }

        for (; var_v1 < 0x11; var_v1++) {
            if ((aiFieldData[var_v1][var_t1].st != 0xA) && (var_v1 < var_t3_2)) {
                var_t3_2 = var_v1;
            }
            if ((aiFieldData[var_v1][var_t1].st >= 5) && (aiFieldData[var_v1][var_t1].st <= 7)) {
                var_t0_2 += 1;
            }
        }
    }

    for (var_t1 = 3; var_t1 >= 0; var_t1--) {
        for (var_v1 = 1; var_v1 < 4; var_v1++) {
            if (aiFieldData[var_v1][var_t1].st != 0xA) {
                break;
            }
        }

        if (var_v1 < 4) {
            var_s6 |= 1;
            if ((var_a1_2 - var_t1) < 4) {
                var_s6 = 0;
                var_t0_2 = xpw->vs;
            }
            break;
        }

        for (; var_v1 < 0x11; var_v1++) {
            if ((aiFieldData[var_v1][var_t1].st != 0xA) && (var_v1 < var_t3_2)) {
                var_t3_2 = var_v1;
            }
            if ((aiFieldData[var_v1][var_t1].st >= 5) && (aiFieldData[var_v1][var_t1].st <= 7)) {
                var_t0_2 += 1;
            }
        }
    }

    var_a2_3 = 0;

    for (var_t1 = 0; var_t1 < 8; var_t1++) {
        for (var_v1 = 0x11; var_v1 >= 4; var_v1--) {
            if ((aiFieldData[var_v1][var_t1].st >= 5) && (aiFieldData[var_v1][var_t1].st <= 7)) {
                if (var_a2_3 < var_v1) {
                    var_a2_3 = var_v1;
                }
                break;
            }
        }
    }

    var_a3_4 = 1;
    if (evs_gamesel == ENUM_EVS_GAMESEL_3) {
        for (var_s0 = 0; var_s0 < evs_playcnt; var_s0++) {
            if (game_state_data[var_s0].vs < game_state_data[aipn].vs) {
                var_a3_4 = 0;
            }
        }
    }

    //! FAKE?
    aiDataPtr = ai_param;

    var_a0_8 = xpw->think_type;
    if ((aipn == 0) && (aiDebugP1 > THINKTYPE_INVALID)) {
        var_a0_8 = aiDebugP1;
    }
    char_data = &ai_char_data[var_a0_8];

    xpw->ai.aiPriOfs = 0;
    xpw->ai.aiRollHabit &= ~0xFE;
    xpw->ai.aiState &= ~4;
    aiPriOfs = 0;

    if (xpw->gs != 0) {
        var_s5 = 0;
    } else if (aiRootP < DOUBLE_LITERAL(4)) {
        var_s5 = 1;
    } else if (((xpw->vs < 7) && (var_a3_4 != 0)) || (var_t0_2 < 3)) {
        if ((var_t0_2 != 0) || (var_t3_2 < var_a2_3 - 4) || (var_t3_2 < 9)) {
            if (var_t0_2 != 0) {
                var_s5 = 2;
            } else {
                var_s5 = 3;
            }
        } else {
            var_s5 = 4;
        }
    } else {
        if (var_s3 == 2) {
            var_s5 = 5;
        } else {
            if (var_s3 == 1) {
                var_s5 = 6;
            } else {
                var_s5 = 7;
            }
        }
    }

    aiSelCom = char_data->performance[var_s5];
    aiSelSpeed = char_data->speed;

    if (evs_gamemode == GMD_FLASH) {
        if (last_flash > 1) {
            aiSelCom = 0;
        } else {
            aiSelCom = 4;
        }
    }

    if (s_hard_mode) {
        if (var_s5 == 7) {
            switch (aiSelCom) {
                case 0x0:
                    aiSelCom = 2;
                    break;

                case 0x1:
                    aiSelCom = 3;
                    break;

                case 0x4:
                    aiSelCom = 4;
                    break;

                case 0x5:
                    aiSelCom = 5;
                    break;
            }
        }
    }

    if ((fool_mode == true) && (framecont & 0x200)) {
        for (var_a1_2 = 0; var_a1_2 < 0x10; var_a1_2++) {
            xpw->ai.aiEffectNo[var_a1_2] = 0;
        }

        aiSelCom = 0;
    }

    for (var_s0 = 0; var_s0 < 0x10; var_s0++) {
        s32 var_t1_5; // bool
        var_t1_5 = 0;

        xpw->ai.aiEffectCount[var_s0] = MIN(0x3E7, xpw->ai.aiEffectCount[var_s0] + 1);

        switch (xpw->ai.aiEffectNo[var_s0]) {
            case 1:
            case 2:
                xpw->ai.aiEffectNo[var_s0] = 0;
                break;

            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
                if (xpw->ai.aiEffectParam[var_s0] != 0) {
                    if (xpw->ai.aiEffectCount[var_s0] >= xpw->ai.aiEffectParam[var_s0]) {
                        xpw->ai.aiEffectNo[var_s0] = 0;
                    }
                }
                break;
        }

        if (xpw->ai.aiEffectNo[var_s0] == 0) {
            switch (char_data->condition[var_s0]) {
                case 0x2:
                    var_t1_5 = genrand(0x64U) <= char_data->condition_param[var_s0];
                    break;

                case 0x3:
                    if (xpw->ai.aiState & 1) {
                        var_t1_5 = 1;
                        xpw->ai.aiState &= ~1;
                    }
                    break;

                case 0x4:
                    for (var_a1_2 = 0; var_a1_2 < evs_playcnt; var_a1_2++) {
                        if (var_a1_2 == aipn) {
                            continue;
                        }
                        if ((game_state_data[aipn].vs - game_state_data[var_a1_2].virus_number) >=
                            char_data->condition_param[var_s0]) {
                            var_t1_5 = 1;
                            break;
                        }
                    }
                    break;

                case 0x5:
                    for (var_a1_2 = 0; var_a1_2 < evs_playcnt; var_a1_2++) {
                        if (var_a1_2 == aipn) {
                            continue;
                        }
                        if ((game_state_data[var_a1_2].virus_number - game_state_data[aipn].vs) >=
                            char_data->condition_param[var_s0]) {
                            var_t1_5 = 1;
                            break;
                        }
                    }
                    break;

                case 0x6:
                    for (var_a1_2 = 0; var_a1_2 < evs_playcnt; var_a1_2++) {
                        if (var_a1_2 == aipn) {
                            continue;
                        }
                        if (game_state_data[var_a1_2].ai.aiRootP < 5) {
                            var_t1_5 = 1;
                            break;
                        }
                    }
                    break;

                case 0x7:
                    var_t1_5 = xpw->ai.aivl == THINKLEVEL_0;
                    break;

                case 0x8:
                    var_t1_5 = xpw->ai.aivl == THINKLEVEL_1;
                    break;

                case 0x9:
                    var_t1_5 = xpw->ai.aivl == THINKLEVEL_2;
                    break;

                case 0xA:
                    var_t1_5 = xpw->vs <= char_data->condition_param[var_s0];
                    break;

                case 0xB:
                    var_t1_5 = xpw->ai.aiFlagDecide.rensa != 0;
                    break;

                case 0x1:
                    var_t1_5 = 1;
                    break;

                case 0xC:
                    var_t1_5 = dm_get_first_virus_count(evs_gamemode, xpw) >= char_data->condition_param[var_s0];
                    break;
            }

            if (var_t1_5 != 0) {
                xpw->ai.aiEffectNo[var_s0] = char_data->effect[var_s0];
                xpw->ai.aiEffectParam[var_s0] = char_data->effect_param[var_s0];
                xpw->ai.aiEffectCount[var_s0] = 0;
            }
        }
    }

    for (var_s0 = 0; var_s0 < 0x10; var_s0++) {
        switch (xpw->ai.aiEffectNo[var_s0]) {
            case 0x1:
                xpw->ai.aiRollHabit |= 2;
                break;

            case 0x3:
                xpw->ai.aiState |= 4;
                break;

            case 0x4:
                aiSelSpeed = MAX(aiSelSpeed, 5);
                break;

            case 0x5:
                aiSelSpeed = MIN(aiSelSpeed, 1);
                break;

            case 0x6:
                aiSelSpeed = 6;
                break;

            case 0x7:
                aiSelSpeed = (xpw->ai.aiEffectCount[var_s0] / 5) + 1;
                aiSelSpeed = MIN(aiSelSpeed, 6);
                break;

            case 0x8:
                aiSelCom = MIN(aiSelCom + 1, 3);
                break;

            case 0x9:
                aiSelCom = MAX(aiSelCom - 1, 0);
                break;

            case 0xA:
                if (xpw->ai.aiEffectParam[var_s0] != 0) {
                    xpw->ai.aiEffectNo[(xpw->ai.aiEffectParam[var_s0] - 1) % AI_EFFECT_LEN] = 0;
                } else {
                    for (var_a1_2 = 0; var_a1_2 < 0x10; var_a1_2++) {
                        xpw->ai.aiEffectNo[var_a1_2] = 0;
                    }
                }
                break;
        }
    }

    if (aiSelSpeed == 6) {
        xpw->ai.aiRollHabit &= ~0x2;
        for (var_s0 = 0; var_s0 < 0x10; var_s0++) {
            if (xpw->ai.aiEffectNo[var_s0] == 2) {
                xpw->ai.aiEffectNo[var_s0] = 0;
            }
        }
    }

    ptr = &aiDataPtr[aiSelCom][var_s5];

    pri_point[4] = ptr->unk_00;
    pri_point[1] = ptr->unk_02;
    EraseLinP[1] = ptr->unk_04;
    EraseLinP[2] = (ptr->unk_04 + ptr->unk_06) >> 1;

    for (var_s0 = 3; var_s0 < 9; var_s0++) {
        EraseLinP[var_s0] = ptr->unk_06;
    }
    HeiEraseLinRate = ptr->unk_08 * 0.01f;
    WidEraseLinRate = ptr->unk_0A * 0.01f;

    LPriP = ptr->unk_0C;

    AloneCapP[2] = ptr->unk_0E;
    AloneCapP[3] = ptr->unk_10;
    AloneCapP[4] = ptr->unk_12;
    AloneCapP[5] = ptr->unk_14;

    AloneCapWP[1] = ptr->unk_16;
    AloneCapWP[2] = ptr->unk_18;
    AloneCapWP[3] = ptr->unk_1A;
    AloneCapWP[4] = ptr->unk_1C;
    AloneCapWP[5] = ptr->unk_1E;

    OnVirusP = ptr->unk_20;
    RensaP = ptr->unk_22;
    RensaMP = ptr->unk_24;

    pri_point[7] = ptr->unk_26;
    pri_point[8] = ptr->unk_28;

    aiWall = (ptr->unk_2A != 0) ? var_s6 : 0;
    OnVirusP_org = OnVirusP;

    HeiLinesAllp[2] = ptr->unk_2C;
    HeiLinesAllp[3] = ptr->unk_2E;
    HeiLinesAllp[4] = ptr->unk_30;
    HeiLinesAllp[5] = ptr->unk_30;
    HeiLinesAllp[6] = ptr->unk_30;
    HeiLinesAllp[7] = ptr->unk_30;
    HeiLinesAllp[8] = ptr->unk_30;

    WidLinesAllp[2] = ptr->unk_32;
    WidLinesAllp[3] = ptr->unk_34;
    WidLinesAllp[4] = ptr->unk_36;
    WidLinesAllp[5] = ptr->unk_36;
    WidLinesAllp[6] = ptr->unk_36;
    WidLinesAllp[7] = ptr->unk_36;
    WidLinesAllp[8] = ptr->unk_36;

    if (char_data->wait_attack) {
        for (var_s0 = 0; var_s0 < evs_playcnt; var_s0++) {
            if (var_s0 == aipn) {
                continue;
            }

            if (game_state_data[var_s0].cap_attack_work[0].unk_0 == 0) {
                continue;
            }

            for (var_a1_2 = 2; var_a1_2 < 8; var_a1_2++) {
                if (EraseLinP[var_a1_2] > 0) {
                    EraseLinP[var_a1_2] = -EraseLinP[var_a1_2];
                }
            }
            var_s0 = evs_playcnt;
        }
    }
}

/**
 * Original name: aifFieldCopy
 */
void aifFieldCopy(struct_game_state_data *uupw) {
    s32 column;
    s32 row;

    aiNext[0] = uupw->cap.ca;
    aiNext[1] = uupw->cap.cb;

    for (column = 0; column < GAME_MAP_COLUMNS; column++) {
        for (row = 0; row < GAME_MAP_ROWS; row++) {
            aiRecurData[row][column + 1].co = aiFieldData[row][column].co = uupw->blk[row][column].co;
            aiRecurData[row][column + 1].st = aiFieldData[row][column].st = uupw->blk[row][column].st;
        }
    }

    for (column = 0; column < ARRAY_COUNT(*aiRecurData); column++) {
        aiRecurData[ARRAY_COUNTU(aiRecurData) - 1][column].co = 0xFF;
        aiRecurData[ARRAY_COUNTU(aiRecurData) - 1][column].st = 0xFF;
    }

    for (row = 0; row < ARRAY_COUNT(aiRecurData); row++) {
        aiRecurData[row][0].co = 0xFF;
        aiRecurData[row][0].st = 0xFF;
        aiRecurData[row][ARRAY_COUNTU(aiRecurData[row]) - 1].co = 0xFF;
        aiRecurData[row][ARRAY_COUNTU(aiRecurData[row]) - 1].st = 0xFF;
    }
}

/**
 * Original name: aifRecurCopy
 */
void aifRecurCopy(void) {
    s32 column;

    for (column = 0; column < GAME_MAP_COLUMNS; column++) {
        s32 row;

        for (row = 0; row < GAME_MAP_ROWS; row++) {
            aiRecurData[row][column + 1].co = aiFieldData[row][column].co;
            aiRecurData[row][column + 1].st = aiFieldData[row][column].st;
        }
    }
}

/**
 * Original name: aifPlaceSearch
 */
void aifPlaceSearch(void) {
    typedef struct struct_aiEdge {
        /* 0x0 */ u8 tory;
        /* 0x1 */ u8 x;
        /* 0x2 */ u8 y;
    } struct_aiEdge;
    struct_aiEdge aiEdge[100];

    s32 var_t5 = 0;
    s32 row;
    s32 column;

    aiYEdgeCnt = 0;
    aiTEdgeCnt = 0;

    for (row = 1; row < ARRAY_COUNT(aiRecurData) - 1; row++) {
        for (column = 1; column < ARRAY_COUNT(aiRecurData[0]) - 1; column++) {
            if (aiRecurData[row][column].co != 3) {
                continue;
            }
            if (aiRecurData[row + 1][column].co == 3) {
                continue;
            }
            if (aiRecurData[row - 1][column].co != 3) {
                continue;
            }

            aiEdge[var_t5].tory = 0;
            aiEdge[var_t5].x = column;
            aiEdge[var_t5].y = row;

            var_t5++;
            aiTEdgeCnt++;
        }
    }

    for (row = 1; row < 0x11; row++) {
        for (column = 1; column < 8; column++) {
            if (aiRecurData[row][column].co != 3) {
                continue;
            }

            if ((aiRecurData[row + 1][column].co == 3) && (aiRecurData[row + 1][column + 1].co == 3)) {
                continue;
            }

            if (aiRecurData[row][column + 1].co != 3) {
                continue;
            }

            aiEdge[var_t5].tory = 1;
            aiEdge[var_t5].x = column;
            aiEdge[var_t5].y = row;
            var_t5++;
            aiYEdgeCnt++;
        }
    }

    var_t5 = 0;

    for (column = 0; column < aiTEdgeCnt; column++) {
        aiFlag[var_t5].tory = 0;
        aiFlag[var_t5].x = aiEdge[column].x;
        aiFlag[var_t5].y = aiEdge[column].y;
        aiFlag[var_t5].rev = 0;

        var_t5++;
    }

    if (aiNext[0] != aiNext[1]) {
        for (column = 0; column < aiTEdgeCnt; column++) {
            aiFlag[var_t5].tory = 0;
            aiFlag[var_t5].x = aiEdge[column].x;
            aiFlag[var_t5].y = aiEdge[column].y;
            aiFlag[var_t5].rev = 1;

            var_t5++;
        }
    }

    for (column = 0; column < aiYEdgeCnt; column++) {
        aiFlag[var_t5].tory = 1;
        aiFlag[var_t5].x = aiEdge[aiTEdgeCnt + column].x;
        aiFlag[var_t5].y = aiEdge[aiTEdgeCnt + column].y;
        aiFlag[var_t5].rev = 0;

        var_t5++;
    }

    if (aiNext[0] != aiNext[1]) {
        for (column = 0; column < aiYEdgeCnt; column++) {
            aiFlag[var_t5].tory = 1;
            aiFlag[var_t5].x = aiEdge[aiTEdgeCnt + column].x;
            aiFlag[var_t5].y = aiEdge[aiTEdgeCnt + column].y;
            aiFlag[var_t5].rev = 1;

            var_t5++;
        }
    }

    aiFlagCnt = var_t5;
}

/**
 * Original name: aifMoveCheck
 */
void aifMoveCheck(void) {
    s32 i;
    s32 j;
    s32 okrootctr;
    s32 okctr;

    for (j = 0; j < aiFlagCnt; j++) {
        aiFlag[j].pri = 0;
    }

    okrootctr = 0;
    okctr = 0;

    for (i = 0; i < aiFlagCnt; i++) {
        for (j = 0; j < ARRAY_COUNT(aiRecurData[0]); j++) {
            aiRecurData[0][j].co = 0xF;
        }

        aifRecurCopy();

        aiRootCnt = 0;
        aiRollFinal = 0;
        success = 0;

        if (aiFlag[i].tory == 0) {
            aifTRecur(aiFlag[i].x, aiFlag[i].y, i);
        } else {
            aifYRecur(aiFlag[i].x, aiFlag[i].y, i);
        }

        aiFlag[i].ok = success;
        if (success == 0) {
            if (aiSelCom >= 2) {
                aiRollFinal = 1;

                if (aiFlag[i].tory == 0) {
                    if (aiFlag[i].x < 7) {
                        if (aiRecurData[aiFlag[i].y][aiFlag[i].x + 1].st == 0xA) {
                            aifYRecur(aiFlag[i].x, aiFlag[i].y, i);
                        }
                    }
                } else if (aiRecurData[aiFlag[i].y - 1][aiFlag[i].x].st == 0xA) {
                    aifTRecur(aiFlag[i].x, aiFlag[i].y, i);
                } else if (aiRecurData[aiFlag[i].y - 1][aiFlag[i].x + 1].st == 0xA) {
                    if ((aiRecurData[aiFlag[i].y][aiFlag[i].x + 2].st != 0xA) || (aiFlag[i].x == 6)) {
                        aifTRecur(aiFlag[i].x + 1, aiFlag[i].y, i);
                    }
                }

                aiFlag[i].ok = success;
            }
        }

        if (success != 0) {
            okctr++;
            okrootctr += aiRootCnt;
        }
    }

    if (okctr != 0) {
        aiRootP = (f32)okrootctr / (f32)okctr;
    } else {
        aiRootP = 0.0f;
    }
}

/**
 * Original name: aifTRecur
 */
void aifTRecur(u8 x, u8 y, u8 cnt) {
    aiRecurData[y][x].co = 0xF;

    if ((x == aiGoalX) && (y == aiGoalY)) {
        success = 1;
    }

    if (success != 1) {
        if ((aiRecurData[y - 1][x].co == 3) && (aiRecurData[y - 2][x].st == 0xA)) {
            aifTRecur(x, y - 1, cnt);
        }
    }

    if (success != 1) {
        if ((aiRecurData[y][x + 1].co == 3) && (aiRecurData[y - 1][x + 1].st == 0xA)) {
            if (aiMoveSF != 0) {
                aifTRecur(x + 1, y, cnt);
            } else {
                aifTRecurUP(x + 1, y, cnt);
            }
        }
    }

    if (success != 1) {
        if ((aiRecurData[y][x - 1].co == 3) && (aiRecurData[y - 1][x - 1].st == 0xA)) {
            if (aiMoveSF != 0) {
                aifTRecur(x - 1, y, cnt);
            } else {
                aifTRecurUP(x - 1, y, cnt);
            }
        }
    }

    if (success == 1) {
        aiRoot[aiRootCnt].x = x;
        aiRoot[aiRootCnt].y = y;
        aiRootCnt++;
    }
}

/**
 * Original name: aifTRecurUP
 */
void aifTRecurUP(u8 x, u8 y, u8 cnt) {
    if ((x == aiGoalX) && (y == aiGoalY)) {
        success = 1;
    }

    if (success != 1) {
        if ((aiRecurData[y - 1][x].co == 3) && (aiRecurData[y - 2][x].st == 0xA)) {
            aifTRecur(x, y - 1, cnt);
        }
    }

    if (success == 1) {
        aiRoot[aiRootCnt].x = x;
        aiRoot[aiRootCnt].y = y;
        aiRootCnt++;
    }
}

/**
 * Original name: aifYRecur
 */
void aifYRecur(u8 x, u8 y, u8 cnt) {
    aiRecurData[y][x].co = 0xF;

    if ((x == aiGoalX) && (y == aiGoalY)) {
        success = 1;
    }

    if (success != 1) {
        if ((aiRecurData[y - 1][x].co == 3) && (aiRecurData[y - 1][x + 1].st == 0xA)) {
            aifYRecur(x, y - 1, cnt);
        }
    }

    if (success != 1) {
        if ((aiRecurData[y][x + 1].co == 3) && (aiRecurData[y][x + 2].st == 0xA)) {
            if (aiMoveSF != 0) {
                aifYRecur(x + 1, y, cnt);
            } else {
                aifYRecurUP(x + 1, y, cnt);
            }
        }
    }

    if (success != 1) {
        if ((aiRecurData[y][x - 1].co == 3) && (aiRecurData[y][x].st == 0xA)) {
            if (aiMoveSF != 0) {
                aifYRecur(x - 1, y, cnt);
            } else {
                aifYRecurUP(x - 1, y, cnt);
            }
        }
    }

    if (success == 1) {
        aiRoot[aiRootCnt].x = x;
        aiRoot[aiRootCnt].y = y;
        aiRootCnt++;
    }
}

/**
 * Original name: aifYRecurUP
 */
void aifYRecurUP(u8 x, u8 y, u8 cnt) {
    if ((x == aiGoalX) && (y == aiGoalY)) {
        success = 1;
    }

    if (success != 1) {
        if ((aiRecurData[y - 1][x].co == 3) && (aiRecurData[y - 1][x + 1].st == 0xA)) {
            aifYRecur(x, y - 1, cnt);
        }
    }

    if (success == 1) {
        aiRoot[aiRootCnt].x = x;
        aiRoot[aiRootCnt].y = y;
        aiRootCnt += 1;
    }
}

/**
 * Original name: aifReMoveCheck
 */
void aifReMoveCheck(void) {
    s32 i;

    for (i = 0; i < 0x32; i++) {
        aiRoot[i].x = 0;
        aiRoot[i].y = 0;
    }

    aiRootCnt = 0;
    aiRollFinal = 0;
    aiMoveSF = 1;
    success = 0;

    aifRecurCopy();

    if (aiFlag[decide].tory == 0) {
        aifTRecur(aiFlag[decide].x, aiFlag[decide].y, decide);
    } else {
        aifYRecur(aiFlag[decide].x, aiFlag[decide].y, decide);
    }

    if (success == 0) {
        aiRollFinal = 1;
        aifRecurCopy();

        if (aiFlag[decide].tory == 0) {
            if (aiRecurData[aiFlag[decide].y][aiFlag[decide].x + 1].st == 0xA) {
                aifYRecur(aiFlag[decide].x, aiFlag[decide].y, decide);
            }
        } else if (aiRecurData[aiFlag[decide].y - 1][aiFlag[decide].x].st == 0xA) {
            aifTRecur(aiFlag[decide].x, aiFlag[decide].y, decide);
        } else if (aiRecurData[aiFlag[decide].y - 1][aiFlag[decide].x + 1].st == 0xA) {
            if ((aiRecurData[aiFlag[decide].y][aiFlag[decide].x + 2].st != 0xA) || (aiFlag[decide].x == 6)) {
                aifTRecur(aiFlag[decide].x + 1, aiFlag[decide].y, decide);
            }
        }
    }

    aiRoot[aiRootCnt].x = aiRoot[aiRootCnt - 1].x;
    aiRoot[aiRootCnt].y = aiRoot[aiRootCnt - 1].y + 1;
}

/**
 * Original name: aifKeyMake
 */
void aifKeyMake(struct_game_state_data *uupw) {
    s32 roll[2][2] = { { 1, 3 }, { 0, 2 } };
    s32 cnt;
    u8 lev;

    uupw->ai.aiFlagDecide = aiFlag[decide];

    for (cnt = 0; cnt < AIROOT_LEN; cnt++) {
        uupw->ai.aiRootDecide[cnt].x = aiRoot[cnt].x;
        uupw->ai.aiRootDecide[cnt].y = aiRoot[cnt].y;
    }

    uupw->ai.aiEX = aiRoot[aiRootCnt - 1].x;
    uupw->ai.aiEY = aiRoot[aiRootCnt - 1].y;

    uupw->ai.aiFlagDecide.rensa = aifRensaCheck(uupw, &uupw->ai.aiFlagDecide);

    uupw->ai.aiRollCnt = (0x28 + roll[uupw->ai.aiFlagDecide.tory][uupw->ai.aiFlagDecide.rev] - uupw->ai.aiOldRollCnt +
                          uupw->ai.aiRollCnt - aiRollFinal + uupw->ai.aiRollFinal) %
                         4;
    uupw->ai.aiOldRollCnt = uupw->ai.aiRollCnt;
    uupw->ai.aiRollFinal = aiRollFinal;
    uupw->ai.aiSelSpeed = aiSelSpeed;
    uupw->ai.aiSpeedCnt = 2;
    uupw->ai.aiKRFlag = true;
    uupw->ai.aiRootP = (aiRootP > AIROOTP_CAP) ? AIROOTP_CAP : aiRootP;

    lev = genrand(aiVirusLevel[aiSelSpeed][uupw->ai.aivl]);
    if (lev >= 7) {
        uupw->ai.aiSpUpFlag = false;
    } else {
        uupw->ai.aiSpUpFlag = true;
        uupw->ai.aiSpUpStart = genrand(5);
    }
}

const s32 wave_tbl_2879[] = {
    0, 1, 1, 0, -1, -1, 0, 1,
};

void aifKeyOut(struct_game_state_data *gameStateDataRef) {
    s32 idy;
    s32 dx;
    s32 i;
    s32 idx;

    aifMakeWork(gameStateDataRef);

    joygam[gameStateDataRef->pn] = 0;
    if (!gameStateDataRef->ai.aiok) {
        return;
    }

    if (gameStateDataRef->cap.my == 0) {
        return;
    }

    if (gameStateDataRef->cap.mx == (gameStateDataRef->ai.aiRootDecide[gameStateDataRef->ai.aiKeyCount].x - 1)) {
        if (gameStateDataRef->cap.my == gameStateDataRef->ai.aiRootDecide[gameStateDataRef->ai.aiKeyCount].y) {
            gameStateDataRef->ai.aiKeyCount++;
        }
    }

    gameStateDataRef->ai.aiSpeedCnt--;

    idx = gameStateDataRef->ai.aiRootDecide[gameStateDataRef->ai.aiKeyCount].x - 1 - gameStateDataRef->cap.mx;
    idy = gameStateDataRef->ai.aiRootDecide[gameStateDataRef->ai.aiKeyCount].y - gameStateDataRef->cap.my;

    if ((idy != 0) && (gameStateDataRef->cap.my < gameStateDataRef->ai.aiEY - 3)) {
        for (i = 0; i < ARRAY_COUNT(gameStateDataRef->ai.aiEffectNo); i++) {
            if (gameStateDataRef->ai.aiEffectNo[i] == 2) {
                dx =
                    idx +
                    wave_tbl_2879[(gameStateDataRef->ai.aiEY + gameStateDataRef->cap.my) % ARRAY_COUNTU(wave_tbl_2879)];

                if (gameStateDataRef->blk[gameStateDataRef->cap.my + 1][gameStateDataRef->cap.mx + dx - 1].st == 0xA) {
                    if (gameStateDataRef->blk[gameStateDataRef->cap.my + 1][gameStateDataRef->cap.mx + dx].st == 0xA) {
                        if (gameStateDataRef->blk[gameStateDataRef->cap.my + 1][gameStateDataRef->cap.mx + dx + 1].st ==
                            0xA) {
                            idx = dx;
                        }
                    }
                }
                break;
            }
        }
    }

    if ((gameStateDataRef->ai.aiSpeedCnt == 0) && !(gameStateDataRef->ai.aiState & 4)) {
        if ((gameStateDataRef->ai.aiRollCnt == 0) && (gameStateDataRef->ai.aiRollHabit & 2)) {
            if (((genrand(5) == 0) && (gameStateDataRef->cap.my < gameStateDataRef->ai.aiEY - 3)) ||
                (gameStateDataRef->ai.aiRollHabit & 1)) {
                gameStateDataRef->ai.aiRollCnt += 2;
                gameStateDataRef->ai.aiRollHabit ^= 1;
            }
        }

        if (gameStateDataRef->ai.aiRollCnt != 0) {
            if (gameStateDataRef->ai.aiRollCnt == 3) {
                joygam[gameStateDataRef->pn] = B_BUTTON;
                gameStateDataRef->ai.aiRollCnt = 0;
            } else {
                joygam[gameStateDataRef->pn] = A_BUTTON;
                gameStateDataRef->ai.aiRollCnt--;
            }
            gameStateDataRef->ai.aiSpeedCnt = 5;
        }

        if (idy < 0) {
            gameStateDataRef->ai.aiSpeedCnt = 1;
            gameStateDataRef->ai.aiKeyCount++;
            if (gameStateDataRef->ai.aiEY < gameStateDataRef->cap.my) {
                gameStateDataRef->ai.aiok = false;
            }
        }

        if (idx > 0) {
            joygam[gameStateDataRef->pn] |= R_JPAD;

            gameStateDataRef->ai.aiSpeedCnt =
                !gameStateDataRef->ai.aiKRFlag
                    ? aiSlideFSpeed[gameStateDataRef->ai.aiSelSpeed][gameStateDataRef->ai.aivl]
                    : aiSlideSpeed[gameStateDataRef->ai.aiSelSpeed][gameStateDataRef->ai.aivl];
            gameStateDataRef->ai.aiKRFlag++;
        }

        if (idx < 0) {
            joygam[gameStateDataRef->pn] |= L_JPAD;

            gameStateDataRef->ai.aiSpeedCnt =
                !gameStateDataRef->ai.aiKRFlag
                    ? aiSlideFSpeed[gameStateDataRef->ai.aiSelSpeed][gameStateDataRef->ai.aivl]
                    : aiSlideSpeed[gameStateDataRef->ai.aiSelSpeed][gameStateDataRef->ai.aivl];
            gameStateDataRef->ai.aiKRFlag++;
        }

        if (idy > 0) {
            if (!gameStateDataRef->ai.aiKRFlag) {
                if ((gameStateDataRef->ai.aiSelSpeed == 6) ||
                    (gameStateDataRef->ai.aiRootDecide[gameStateDataRef->ai.aiKeyCount].y !=
                     gameStateDataRef->ai.aiRootDecide[gameStateDataRef->ai.aiKeyCount + 1].y)) {
                    if ((gameStateDataRef->ai.aiSelSpeed == 5) || (gameStateDataRef->ai.aiSelSpeed == 6) ||
                        (gameStateDataRef->cap.my >= 3) ||
                        ((gameStateDataRef->ai.aiSelSpeed >= 2) && (gameStateDataRef->cap.my == 2) &&
                         (FallSpeed[gameStateDataRef->cap.sp] / 2 < gameStateDataRef->cap.cn))) {
                        if (evs_gamesel != ENUM_EVS_GAMESEL_3) {
                            joygam[gameStateDataRef->pn] |= D_JPAD;
                        } else if (gameStateDataRef->ai.aiFlagDecide.rensa == 0) {
                            joygam[gameStateDataRef->pn] |= D_JPAD;
                        } else if (game_state_data[1 - aipn].cap_attack_work[0].unk_0 == 0) {
                            joygam[gameStateDataRef->pn] |= D_JPAD;
                        }
                    }

                    if (gameStateDataRef->ai.aiSpUpFlag == true) {
                        if (gameStateDataRef->ai.aiKeyCount > gameStateDataRef->ai.aiSpUpStart) {
                            gameStateDataRef->ai.aiSpeedCnt++;
                        } else {
                            gameStateDataRef->ai.aiSpeedCnt +=
                                aiDownSpeed[gameStateDataRef->ai.aiSelSpeed][gameStateDataRef->ai.aivl];
                        }
                    } else {
                        gameStateDataRef->ai.aiSpeedCnt +=
                            aiDownSpeed[gameStateDataRef->ai.aiSelSpeed][gameStateDataRef->ai.aivl];
                    }
                } else {
                    gameStateDataRef->ai.aiSpeedCnt++;
                }
            } else {
                gameStateDataRef->ai.aiSpeedCnt +=
                    aiSlideFSpeed[gameStateDataRef->ai.aiSelSpeed][gameStateDataRef->ai.aivl];
                gameStateDataRef->ai.aiKRFlag = false;
            }
        }
    }

    if ((gameStateDataRef->cap.mx == gameStateDataRef->ai.aiEX - 1) &&
        (gameStateDataRef->cap.my == gameStateDataRef->ai.aiEY) && (gameStateDataRef->ai.aiRollFinal != 0)) {
        if ((joygam[gameStateDataRef->pn] != A_BUTTON) && (joygam[gameStateDataRef->pn] != B_BUTTON)) {
            joygam[gameStateDataRef->pn] = A_BUTTON;
            gameStateDataRef->ai.aiRollFinal = 0;
        }
    }

    if (gameStateDataRef->ai.aiSelSpeed == 6) {
        gameStateDataRef->ai.aiSpeedCnt = 1;
    }
}

s32 search_flash_3(s32 cx, s32 cy, s32 col, s32 tory, s32 ec) {
    s8 sp8[8];
    s8 sp10[8];
    s32 pad[2] UNUSED;
    s32 x;
    s32 y;
    s32 cnt;
    s32 idx;
    s32 i;
    s32 j;
    s32 k;

#if 0
    signed char tmp[8]; // r1+0x44
#endif

    for (i = 0; i < pGameState->flash_virus_count; i++) {
        if (pGameState->flash_virus_pos[i].color != col) {
            continue;
        }

        x = pGameState->flash_virus_pos[i].column;
        y = pGameState->flash_virus_pos[i].row;

        if (cy == y) {
            idx = 0;
            for (j = 0; j < 8; j++) {
                sp8[j] = -1;
            }

            for (j = -3; j < 4; j++) {
                if ((x + j >= 0) && (x + j < GAME_MAP_COLUMNS)) {
                    if (aiFieldData[y][x + j].co != col) {
                        if (aiFieldData[y][x + j].co == 3) {
                            sp8[idx] = 0;
                        } else {
                            sp8[idx] = -1;
                        }
                    } else {
                        sp8[idx] = 1;
                    }
                } else {
                    sp8[idx] = -1;
                }
                idx++;
            }

            if ((ec == 1) && (tory == 1)) {
                if ((sp8[0] == 0) && (sp8[1] == 0) && (sp8[2] == 1)) {
                    if (cx == x - 3) {
                        return 0x2710;
                    }
                }

                if ((sp8[1] == 0) && (sp8[2] == 0) && (sp8[4] == 1)) {
                    if (cx == x - 2) {
                        return 0x2710;
                    }
                }

                if ((sp8[0] == 1) && (sp8[1] == 0) && (sp8[2] == 0)) {
                    if (cx == x - 2) {
                        return 0x2710;
                    }
                }

                if ((sp8[2] == 1) && (sp8[4] == 0) && (sp8[5] == 0)) {
                    if (cx == x + 1) {
                        return 0x2710;
                    }
                }

                if ((sp8[4] == 0) && (sp8[5] == 0) && (sp8[6] == 1)) {
                    if (cx == x + 1) {
                        return 0x2710;
                    }
                }

                if ((sp8[4] == 1) && (sp8[5] == 0) && (sp8[6] == 0)) {
                    if (cx == x + 2) {
                        return 0x2710;
                    }
                }

                if ((sp8[1] == 0) && (sp8[2] == 0)) {
                    if (cx == x - 2) {
                        return 0x1388;
                    }
                }

                if ((sp8[4] == 0) && (sp8[5] == 0)) {
                    if (cx == x + 1) {
                        return 0x1388;
                    }
                }
            }

            for (j = 0; j < 7; j++) {
                sp10[j] = sp8[j];
            }

            for (j = 0; j < 7; j++) {
                if (sp8[j] != 0) {
                    continue;
                }

                sp8[j] = 1;
                cnt = 0;

                for (k = 0; k < 7; k++) {
                    if (sp8[k] != 1) {
                        cnt = 0;
                    } else {
                        cnt += 1;
                    }

                    if ((cnt >= 4) && (cx == x + tbl_2973[j])) {
                        return 0x1388;
                    }
                }

                sp8[j] = 0;
            }
        }

        if (cx == x) {
            idx = 0;

            for (j = 0; j < 8; j++) {
                sp8[j] = -1;
            }

            for (j = -3; j < 4; j++) {
                if ((y + j >= 0) && (y + j < GAME_MAP_ROWS)) {
                    if (aiFieldData[y + j][x].co != col) {
                        if (aiFieldData[y + j][x].co == 3) {
                            sp8[idx] = 0;
                        } else {
                            sp8[idx] = -1;
                        }
                    } else {
                        sp8[idx] = 1;
                    }
                } else {
                    sp8[idx] = -1;
                }
                idx++;
            }

            if ((ec == 1) && (tory == 0)) {
                if ((sp8[0] == 0) && (sp8[1] == 0) && (sp8[2] == 1)) {
                    if (cy == (y - 2)) {
                        return 0x2710;
                    }
                }

                if ((sp8[1] == 0) && (sp8[2] == 0) && (sp8[4] == 1)) {
                    if (cy == (y - 1)) {
                        return 0x2710;
                    }
                }

                if ((sp8[0] == 1) && (sp8[1] == 0) && (sp8[2] == 0)) {
                    if (cy == (y - 1)) {
                        return 0x2710;
                    }
                }

                if ((sp8[2] == 1) && (sp8[4] == 0) && (sp8[5] == 0)) {
                    if (cy == y + 2) {
                        return 0x2710;
                    }
                }

                if ((sp8[4] == 0) && (sp8[5] == 0) && (sp8[6] == 1)) {
                    if (cy == y + 2) {
                        return 0x2710;
                    }
                }

                if ((sp8[4] == 1) && (sp8[5] == 0) && (sp8[6] == 0)) {
                    if (cy == y + 3) {
                        return 0x2710;
                    }
                }

                if ((sp8[1] == 0) && (sp8[2] == 0)) {
                    if (cy == y - 1) {
                        return 0x1388;
                    }
                }

                if ((sp8[4] == 0) && (sp8[5] == 0)) {
                    if (cy == y + 2) {
                        return 0x1388;
                    }
                }
            }

            for (j = 0; j < 7; j++) {
                sp10[j] = sp8[j];
            }

            for (j = 0; j < 7; j++) {
                if (sp8[j] != 0) {
                    continue;
                }

                sp8[j] = 1;
                cnt = 0;

                for (k = 0; k < 7; k++) {
                    if (sp8[k] != 1) {
                        cnt = 0;
                    } else {
                        cnt += 1;
                    }

                    if (cnt < 4) {
                        continue;
                    }
                    if (cy == (y + tbl_2973[j])) {
                        return 0x1388;
                    }
                }

                sp8[j] = 0;
            }
        }
    }

    return 0;
}

/**
 * Original name: flash_special
 */
s32 flash_special(void) {
    s32 sp20[2];
    s32 sp28[2];
    s32 sp30[2];
    s32 ret;
    s32 ec;
    s32 i;

    delpos_cnt = 0;

    for (i = 0; i < aiFlagCnt; i++) {
        if (aiFlag[i].ok != 1) {
            continue;
        }

        sp20[0] = aiFlag[i].x - 1;
        sp28[0] = aiFlag[i].y;
        if (aiFlag[i].tory == 0) {
            sp20[1] = sp20[0];
            sp28[1] = sp28[0] - 1;
            if (aiFlag[i].rev == 0) {
                sp30[0] = aiNext[1];
                sp30[1] = aiNext[0];
            } else {
                sp30[0] = aiNext[0];
                sp30[1] = aiNext[1];
            }
        } else {
            sp20[1] = sp20[0] + 1;
            sp28[1] = sp28[0];
            if (aiFlag[i].rev == 0) {
                sp30[0] = aiNext[0];
                sp30[1] = aiNext[1];
            } else {
                sp30[0] = aiNext[1];
                sp30[1] = aiNext[0];
            }
        }

        if (sp30[0] == sp30[1]) {
            ec = 1;
        } else {
            ec = 0;
        }

        ret = search_flash_3(sp20[0], sp28[0], sp30[0], aiFlag[i].tory, ec);
        if (ret > 0) {
            delpos_tbl[delpos_cnt] = i;
            delpos_cnt += 1;
            aiFlag[i].pri += ret;
        }

        ret = search_flash_3(sp20[1], sp28[1], sp30[1], aiFlag[i].tory, ec);
        if (ret > 0) {
            delpos_tbl[delpos_cnt] = i;
            delpos_cnt += 1;
            aiFlag[i].pri += ret;
        }
    }

    if (delpos_cnt > 0) {
        for (i = 0; i < aiFlagCnt; i++) {
            aiFlag[i].ok = 0;
        }

        for (i = 0; i < delpos_cnt; i++) {
            aiFlag[delpos_tbl[i]].ok = 1;
        }
    }

    return delpos_cnt;
}

/**
 * Original name: aiCOM_MissTake
 */
void aiCOM_MissTake(void) {
    PlayTime++;

    if (PlayTime > 18000) {
        MissRate = (PlayTime - 18000) / 720;
    } else {
        MissRate = 0;
    }
}

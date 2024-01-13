#ifndef AISET_H
#define AISET_H

#include "libultra.h"
#include "libc/stdbool.h"
#include "ai.h"
#include "gamemap.h"
#include "unk.h"

struct struct_game_state_data;

typedef struct Unk_AIFEntry {
    /* 0x0 */ u8 unk_0;
    /* 0x1 */ u8 unk_1;
} Unk_AIFEntry; // size = 0x2

extern Unk_AIFEntry aiRecurData[GAME_MAP_ROWS+1][GAME_MAP_COLUMNS+2];
extern Unk_AIFEntry aiFieldData[GAME_MAP_ROWS][GAME_MAP_COLUMNS];

extern Unk_AIFEntry aif_field[GAME_MAP_ROWS][GAME_MAP_COLUMNS];

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
s32 aifEraseLineCore(s32 arg0, s32 arg1);
s32 aifRensaCheckCore(struct struct_game_state_data *gameStateDataRef, struct_aiFlag *aiFlagRef, u8 arg2, u8 arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9);
// void aifRensaCheck();
bool aifSearchLineCore(s32 arg0, s32 arg1, s32 arg2);
s32 aifMiniPointK3(u8 *arg0, u8 arg1, u8 *arg2, u8 arg3, u8 arg4, u8 arg5);
s32 aifMiniAloneCapNumber(u8 arg0, u8 arg1, u8 arg2, s32 arg3);
s32 aifMiniAloneCapNumberW(u8 arg0, u8 arg1, u8 arg2, s32 arg3);
s32 flash_virus(s32 arg0, s32 arg1);
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
s32 search_flash_3(s32, s32, s32, s32, s32);
s32 flash_special(void);
void aiCOM_MissTake(void);

#endif
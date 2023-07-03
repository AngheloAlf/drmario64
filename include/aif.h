#ifndef AIF_H
#define AIF_H

#include "libultra.h"
#include "gamemap.h"

struct struct_game_state_data;

/**
 * Artificial intelligence field?
 */

typedef struct Unk_AIFEntry {
    /* 0x0 */ u8 unk_0;
    /* 0x1 */ u8 unk_1;
} Unk_AIFEntry; // size = 0x2

extern Unk_AIFEntry aiRecurData[GAME_MAP_ROWS+1][GAME_MAP_COLUMNS+2];
extern Unk_AIFEntry aiFieldData[GAME_MAP_ROWS][GAME_MAP_COLUMNS];

extern Unk_AIFEntry aif_field[GAME_MAP_ROWS][GAME_MAP_COLUMNS];

void func_8002EB00(struct struct_game_state_data *gameStateDataRef);
void aifMakeBlkWork(struct struct_game_state_data *gameStateDataRef);
void aifMakeFlagSet(struct struct_game_state_data *gameStateDataRef);
void aifGameInit(void);
void aifFirstInit(void);
void aifMake(struct struct_game_state_data *gameStateDataRef);
bool aifMake2(struct struct_game_state_data * gameStateDataRef, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void aiHiruSideLineEraser(struct struct_game_state_data *gameStateDataRef);
// void func_8002F924();
// void aifEraseLineCore();
// void aifRensaCheckCore();
// void aifRensaCheck();
// void aifSearchLineCore();
// void aifMiniPointK3();
// void aifMiniAloneCapNumber();
// void aifMiniAloneCapNumberW();
// void flash_virus();
// void search_Vflash();
// void func_8003151C();
// void aifSearchLineMS();
void aiHiruAllPriSet(struct struct_game_state_data *gameStateDataRef);
void aiSetCharacter(struct struct_game_state_data *gameStateDataRef);
void aifFieldCopy(struct struct_game_state_data *gameStateDataRef);
// void func_80034310();
void aifPlaceSearch(void);
void aifMoveCheck(void);
// void aifTRecur();
// void aifTRecurUP();
// void aifYRecur();
// void aifYRecurUP();
void aifReMoveCheck(void);
void aifKeyMake(struct struct_game_state_data *gameStateDataRef);
void aifKeyOut(struct struct_game_state_data *gameStateDataRef);
// void search_flash_3();
void flash_special(void);
void aiCOM_MissTake(void);

#endif
#ifndef JOY_H
#define JOY_H

#include "libultra.h"

#ifndef AVOID_JOY_FUNCTIONS
s32 joyInit(s32 arg0);
void joyProcCore(void);
void joyCursorFastSet(u16 mask, u8 index);
s32 joyResponseCheck(void);
#endif

// COMMON

extern u16 joycur[MAXCONTROLLERS+1];
extern u16 gControllerPressedButtons[MAXCONTROLLERS+1];
extern u16 gControllerPrevHoldButtons[MAXCONTROLLERS+1];
extern u16 gControllerHoldButtons[MAXCONTROLLERS+1];
extern u16 joycnt[MAXCONTROLLERS][0x10];
extern u16 joyflg[MAXCONTROLLERS];
extern u16 joygam[MAXCONTROLLERS];
extern u8 joygmf[MAXCONTROLLERS];
extern u8 link_joy[MAXCONTROLLERS];
extern u8 main_joy[MAXCONTROLLERS];
extern u16 joycur1;
extern u16 joycur2;

extern OSContStatus B_800F5358[4];
extern OSMesgQueue B_800F3E38;
extern OSMesg B_800F3E60[1];
extern OSContPad B_800EB4D8[MAXCONTROLLERS];


#endif

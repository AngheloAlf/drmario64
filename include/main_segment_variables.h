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

// bss

// extern UNK_TYPE aiRootP;
// extern UNK_TYPE aiWall;

extern u8 success;
// extern UNK_TYPE attack_sprite_idx;

// extern UNK_TYPE B_800EB290;
extern s32 B_800EB4CC;
extern s32 B_800EB4D0;

// extern UNK_TYPE B_800EB4F9;
// extern UNK_TYPE B_800EB50A;
// extern UNK_TYPE B_800EB50B;
// extern UNK_TYPE B_800EB64C;
// extern UNK_TYPE B_800EB64D;
// extern UNK_TYPE aiTEdgeCnt;

// extern UNK_TYPE hei_data;
// extern UNK_TYPE B_800EBD03;
// extern UNK_TYPE B_800EBD04;
// extern UNK_TYPE B_800EBD05;
// extern UNK_TYPE B_800EBD07;
// extern UNK_TYPE B_800EBD0B;
extern u8 aiNext[]; // maybe a struct?

// extern UNK_TYPE attack_effect_idx;
// extern UNK_TYPE B_800EF54C;

extern u8 decide;

// extern UNK_TYPE B_800F1CE9;

// extern UNK_TYPE aiHiErB;
// extern UNK_TYPE aiPriOfs;
// extern UNK_TYPE aiRollFinal;
extern u8 aiFlagCnt;
extern u16 aiGoalX;
// extern UNK_TYPE wid_data;
// extern UNK_TYPE B_800F3E6F;
// extern UNK_TYPE B_800F3E70;
// extern UNK_TYPE B_800F3E71;
// extern UNK_TYPE B_800F3E73;
// extern UNK_TYPE B_800F3E77;
// extern UNK_TYPE aiHiErY;
// extern UNK_TYPE attack_sprite;
// extern UNK_TYPE B_800F3E94;
// extern UNK_TYPE B_800F3E98;
// extern UNK_TYPE B_800F3E9C;
// extern UNK_TYPE B_800F3EA0;
extern u8 aiRootCnt;


// extern UNK_TYPE B_800F6C71;
// extern UNK_TYPE B_800F6CD4;
// extern UNK_TYPE aiYEdgeCnt;

// extern UNK_TYPE attack_sprite_address;
// extern UNK_TYPE B_800F8C90;

// extern UNK_TYPE aiHiErR;
// extern UNK_TYPE aiSelCom;
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
extern s8 aiSelSpeed;

// extern UNK_TYPE aiHiEraseCtr;
extern u8 aiMoveSF; // maybe bool?
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


#endif

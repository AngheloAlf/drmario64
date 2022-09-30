#ifndef BOOT_VARIABLES_H
#define BOOT_VARIABLES_H

#include "ultra64.h"
#include "libc/stdint.h"
#include "unknown_structs.h"
#include "unk.h"
#include "alignment.h"

// data

extern void (*D_8000E190)();
extern s8 D_8000E1A0;
// extern UNK_TYPE D_8000E1B0;
// extern UNK_TYPE D_8000E1FC;
// extern UNK_TYPE D_8000E23C;
// extern UNK_TYPE D_8000E27C;
// extern UNK_TYPE D_8000E2B8;
// extern UNK_TYPE D_8000E2F4;
// extern UNK_TYPE D_8000E318;
// extern UNK_TYPE D_8000E31C;
// extern UNK_TYPE D_8000E320;
// extern UNK_TYPE D_8000E324;
// extern UNK_TYPE D_8000E338;
// extern UNK_TYPE D_8000E738;


// bss


extern OSThread B_80010E60;
extern OSThread B_80011010;
extern STACK(B_800131C0, 0x2000);
extern OSMesgQueue B_800151C0;
extern OSMesg B_800151D8[1];
// extern UNK_TYPE B_800151E0;
// extern UNK_TYPE B_800191E0;
// extern UNK_TYPE B_8001A390;
// extern UNK_TYPE B_8001A3A8;
// extern UNK_TYPE B_8001A3B0;
// extern UNK_TYPE B_8001A3C0;
// extern UNK_TYPE B_8001A3C4;
// extern UNK_TYPE B_8001A3D0;
// extern UNK_TYPE B_8001A3D8;
// extern UNK_TYPE B_8001A3DC;
// extern UNK_TYPE B_8001A3E0;
// extern UNK_TYPE B_8001A3E8;
// extern UNK_TYPE B_8001A3EC;
// extern UNK_TYPE B_8001A3F0;
// extern UNK_TYPE B_8001A3F8;
// extern UNK_TYPE B_8001A3FC;

// extern UNK_TYPE B_8001A410;
// extern UNK_TYPE B_8001B640;

extern struct_80029C04 B_80029C00;
extern OSMesgQueue B_80029C08;

#endif

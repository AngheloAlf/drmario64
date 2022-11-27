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
extern romoffset_t D_8000E740;
extern romoffset_t D_8000E744;
extern romoffset_t D_8000E748;
extern romoffset_t D_8000E74C;
// extern UNK_TYPE D_8000E750;
// extern UNK_TYPE D_8000E754;
extern romoffset_t D_8000E758;
extern romoffset_t D_8000E75C;
extern romoffset_t D_8000E760;
extern romoffset_t D_8000E764;
extern romoffset_t D_8000E768;
extern romoffset_t D_8000E76C;
extern romoffset_t D_8000E770;
extern romoffset_t D_8000E774;

extern struct_8000E778 D_8000E778[0x30];

extern romoffset_t gRomOffset_N64WaveTables_Start;
extern romoffset_t gRomOffset_N64WaveTables_End;
extern romoffset_t gRomOffset_N64PtrTables_Start;
extern romoffset_t gRomOffset_N64PtrTables_End;
extern romoffset_t D_8000E848;
extern romoffset_t D_8000E84C;
extern romoffset_t D_8000E9B0;
extern romoffset_t D_8000E9B4;
extern romoffset_t D_8000E9D8;
extern romoffset_t D_8000E9DC;
extern romoffset_t D_8000E9E0;
extern romoffset_t D_8000E9E4;
extern romoffset_t D_8000EA40;
extern romoffset_t D_8000EA44;
extern romoffset_t D_8000EA48;
extern romoffset_t D_8000EA4C;


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

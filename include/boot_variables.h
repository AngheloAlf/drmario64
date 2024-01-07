#ifndef BOOT_VARIABLES_H
#define BOOT_VARIABLES_H

#include "libultra.h"
#include "libc/stdint.h"
#include "unknown_structs.h"
#include "unk.h"
#include "alignment.h"
#include "hasm.h"
#include "stack.h"

// data

extern s8 sDmaDataNeedsInitialization;

// bss


extern OSMesgQueue B_800151C0;
extern OSMesg B_800151D8[1];
// extern UNK_TYPE gzip_mem_buff;
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
// extern UNK_TYPE inbuf;

extern STACK(gBootThreadStack, BOOT_STACK_SIZE);


#endif

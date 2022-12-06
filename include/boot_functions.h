#ifndef BOOT_FUNCTIONS
#define BOOT_FUNCTIONS

#include "ultra64.h"
#include "libc/stdint.h"
#include "unknown_structs.h"
#include "unk.h"


void func_80000460(void);
void func_80000468(void);
void func_80000488(void* arg0);
void bootproc(void);

void func_800004F0(void *arg0);
void func_80000580(void* arg0);

void *func_80000620(romoffset_t segmentRom, void *segmentVram, size_t segmentSize);
void *func_80000720(s32 arg0);
void func_8000075C(void);
// void func_80000778();
UNK_TYPE func_80000D0C(UNK_PTR arg0);
// void func_80000D48();
s32 func_80001260(void);
s32 func_80001480(void);
s32 func_80001620(void);
s32 func_80001D4C(s32 *arg0);
s32 func_80001EB4(void);
size_t func_80001F90(romoffset_t segmentRom, void *dstAddr, size_t segmentSize);
size_t func_80001FD8(struct_80029C04 *arg0, u8 *arg1, size_t blockSize);
size_t func_80002064(struct_8001D7F8 *arg0, u8 *arg1, size_t arg2);
UNK_TYPE func_800020A0(void);
u32 func_80002148(u8 *arg0, size_t arg1);
void func_800021A0(void);
s32 func_800021CC(s32 arg0);
void func_800022A8(struct_8001D7F8 *arg0, u8 *arg1, size_t arg2);
void func_80002300(void);
void *DecompressRomToRam(romoffset_t segmentRom, void *dstAddr, size_t segmentSize);
s32 func_800023B4(s32 arg0, s32 arg1, s32 arg2);
f32 func_80002400(f32 arg0, f32 arg1, f32 arg2);

#endif

#ifndef AUDIO_STUFF_H
#define AUDIO_STUFF_H

#include "ultra64.h"
#include "libc/stdint.h"
#include "libc/stdbool.h"
#include "PR/libmus.h"
#include "unk.h"
#include "unknown_structs.h"


typedef struct Audio_struct_800FAF98_unk_14 {
    /* 0x0 */ struct Audio_struct_800FAF98_unk_14 *unk_0;
    /* 0x4 */ UNK_TYPE4 unk_4;
    /* 0x8 */ musHandle unk_8;
} Audio_struct_800FAF98_unk_14; // size = 0xC

typedef struct Audio_struct_800FAF98 {
    /* 0x00 */ struct_800EB670 *unk_00;
    /* 0x04 */ UNK_TYPE unk_04;
    /* 0x08 */ UNK_TYPE unk_08;
    /* 0x0C */ void *unk_0C; // vram
    /* 0x10 */ size_t unk_10;
    /* 0x14 */ Audio_struct_800FAF98_unk_14* unk_14;
    /* 0x18 */ UNK_TYPE unk_18;
    /* 0x1C */ void *unk_1C;
    /* 0x20 */ size_t unk_20;
    /* 0x24 */ musHandle *unk_24;
    /* 0x28 */ s32 unk_28; // len of unk_24
    /* 0x2C */ OSMesgQueue unk_2C;
    /* 0x44 */ OSMesg unk_44[8];
    /* 0x64 */ struct_800FAF98_unk_64 unk_64;
    /* 0x6C */ OSMesgQueue unk_6C;
    /* 0x84 */ OSMesg unk_84[4];
    /* 0x94 */ OSMesgQueue unk_94;
    /* 0xAC */ OSMesg unk_AC[4];
    /* 0xBC */ UNK_TYPE unk_BC;
} Audio_struct_800FAF98; // size >= 0xC0

/// 000E30.c

UNK_TYPE func_8002AA80();
void func_8002AAD8(struct_800FACE0_unk_08 *arg0, UNK_TYPE arg1);
// void func_8002AAE8();
// void func_8002AB28();
// void func_8002ABC0();
// void func_8002AC64();
// void func_8002ACE0();
void func_8002AD38(struct_800EB670* arg0);
// void func_8002AE58();
// void func_8002AF7C();
// void func_8002AFA4();
// void func_8002AFC4();
// void func_8002AFE4();
// void func_8002B000();
// void func_8002B028();
// void func_8002B078();
// void func_8002B098();
void func_8002B0E4(void);
void func_8002B100(s32 arg0);
s32 func_8002B13C(s32 arg0);
s32 func_8002B15C(s32 arg0, s32 arg1);
bool func_8002B178(void);
bool func_8002B194(s32 arg0);
void func_8002B1B4(s32 arg0);
void func_8002B344(s32 arg0);
s32 func_8002B370(void);
// void func_8002B394();
void func_8002B490(UNK_PTR);
void func_8002B4BC(struct_800EB670 *);
void func_8002B5E4(void);
void func_8002B710(void);
void func_8002B728(void);
void func_8002B754(void);
void func_8002B7A8(struct_800EB670 *arg0);
s16 func_8002B800(void);
// void func_8002B834();
// void func_8002B9D8();
// void func_8002BAB8();
// void func_8002BBD8();
// void func_8002BC58();


s32 func_8002D170(struct_800EB670 *arg0, UNK_PTR arg1, UNK_TYPE arg2, size_t arg3, UNK_TYPE arg4, UNK_TYPE arg5, size_t arg6, UNK_TYPE arg7, OSPri thread_priority);
bool func_8002D3B0(romoffset_t segmentRom, size_t segmentSize, void *wbank);
bool func_8002D428(s32 index, romoffset_t segmentRom, size_t segmentSize);
void func_8002D4A4(s32 index);
musHandle func_8002D4F8(s32 index);
s32 func_8002D51C(s32 index);
s32 func_8002D554(s32 index, s32 speed);
s32 func_8002D58C(s32 index, s32 volume);
s32 func_8002D5C4(s32 index, s32 pan);
s32 func_8002D5FC(s32 index, s32 tempo);
s32 func_8002D634(s32 index);
s32 func_8002D66C(s32 index);
bool func_8002D6A4(romoffset_t segmentRom, size_t segmentSize);
void *func_8002D710(void);
void func_8002D720(s32 index, s32 number);
void func_8002D768(s32 index, s32 number, s32 volume, s32 pan, s32 restartflag, s32 priority);
s32 func_8002D7C4(s32 index);
s32 func_8002D7E0(s32 index);
s32 func_8002D810(s32 index, s32 speed);
s32 func_8002D840(s32 index, s32 volume);
s32 func_8002D870(s32 index, s32 pan);
s32 func_8002D8A0(s32 index, f32 offset);
void func_8002D8D0(romoffset_t segmentRom, void *segmentVram, size_t segmentSize);
void func_8002D984(void);
void func_8002D9E4(void);
void func_8002DA48(musTask *arg0);


// data

extern musSched D_800883F0;


// bss

extern Audio_struct_800FAF98 *gAudio_800FAF98;


#endif

#ifndef AUDIO_003520_H
#define AUDIO_003520_H

#include "libultra.h"
#include "PR/libmus.h"
#include "libc/stdbool.h"
#include "nnsched.h"
#include "other_types.h"
#include "unk.h"

struct NNSched;

typedef struct Audio_struct_800FAF98_unk_14 {
    /* 0x0 */ void *unk_0;
    /* 0x4 */ UNK_TYPE4 unk_4;
    /* 0x8 */ musHandle unk_8;
} Audio_struct_800FAF98_unk_14; // size = 0xC

typedef struct Audio_struct_800FAF98 {
    /* 0x00 */ struct NNSched *sc;
    /* 0x04 */ void *unk_04;
    /* 0x08 */ size_t unk_08;
    /* 0x0C */ void *unk_0C; // vram
    /* 0x10 */ size_t unk_10;
    /* 0x14 */ Audio_struct_800FAF98_unk_14* unk_14;
    /* 0x18 */ UNK_TYPE unk_18;
    /* 0x1C */ void *fxbank;
    /* 0x20 */ size_t unk_20;
    /* 0x24 */ musHandle *unk_24;
    /* 0x28 */ s32 unk_28; // len of unk_24
    /* 0x2C */ OSMesgQueue dma_queue;
    /* 0x44 */ OSMesg dma_messages[8];
    /* 0x64 */ NNScClient nnclient;
    /* 0x6C */ OSMesgQueue nnframe_queue;
    /* 0x84 */ OSMesg nnframe_messages[4];
    /* 0x94 */ OSMesgQueue nntask_queue;
    /* 0xAC */ OSMesg nntask_messages[4];
} Audio_struct_800FAF98; // size = 0xBC

size_t InitMusicDriver(struct NNSched *sc, void *heap, size_t heap_length, size_t arg3, UNK_TYPE arg4, UNK_TYPE arg5, size_t arg6, UNK_TYPE arg7, OSPri thread_priority);
bool func_8002D3B0(RomOffset segmentRom, size_t segmentSize, void *wbank);
bool func_8002D428(s32 index, RomOffset segmentRom, size_t segmentSize);
void func_8002D4A4(s32 index);
musHandle func_8002D4F8(s32 index);
s32 func_8002D51C(s32 index);
s32 func_8002D554(s32 index, s32 speed);
s32 func_8002D58C(s32 index, s32 volume);
s32 func_8002D5C4(s32 index, s32 pan);
s32 func_8002D5FC(s32 index, s32 tempo);
s32 func_8002D634(s32 index);
s32 func_8002D66C(s32 index);
bool func_8002D6A4(RomOffset segmentRom, size_t segmentSize);
void *func_8002D710(void);
void func_8002D720(s32 index, s32 number);
void func_8002D768(s32 index, s32 number, s32 volume, s32 pan, s32 restartflag, s32 priority);
s32 func_8002D7C4(s32 index);
s32 func_8002D7E0(s32 index);
s32 func_8002D810(s32 index, s32 speed);
s32 func_8002D840(s32 index, s32 volume);
s32 func_8002D870(s32 index, s32 pan);
s32 func_8002D8A0(s32 index, f32 offset);

extern Audio_struct_800FAF98 *gAudio_800FAF98;

#endif

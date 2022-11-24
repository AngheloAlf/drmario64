#ifndef UNKNOWN_STRUCTS_H
#define UNKNOWN_STRUCTS_H

#include "libc/stdint.h"
#include "unk.h"

typedef struct struct_80029C04 {
    romoffset_t segmentRom;
    size_t segmentSize;
} struct_80029C04;

typedef struct struct_800EB670 {
    /* 0x000 */ s16 unk_000;
    /* 0x002 */ s16 unk_002;
    /* 0x004 */ OSMesgQueue unk_004;
    /* 0x01C */ UNK_TYPE unk_01C;
    /* 0x020 */ UNK_TYPE1 unk_020[0x1C];
    /* 0x03C */ OSMesgQueue unk_03C;
    /* 0x054 */ UNK_TYPE unk_054;
    /* 0x058 */ UNK_TYPE1 unk_058[0x1C];
    /* 0x074 */ OSMesgQueue unk_074;
    /* 0x08C */ UNK_TYPE unk_08C;
    /* 0x090 */ UNK_TYPE1 unk_090[0x1C];
    /* 0x0AC */ OSMesgQueue unk_0AC;
    /* 0x0C4 */ UNK_TYPE unk_0C4;
    /* 0x0C8 */ UNK_TYPE1 unk_0C8[0x1C];
    /* 0x0E4 */ OSMesgQueue unk_0E4;
    /* 0x0FC */ UNK_TYPE unk_0FC;
    /* 0x100 */ UNK_TYPE1 unk_100[0x1C];
    /* 0x11C */ OSMesgQueue unk_11C;
    /* 0x134 */ UNK_TYPE unk_134;
    /* 0x138 */ UNK_TYPE1 unk_138[0x20];
    /* 0x158 */ OSThread unk_158;
    /* 0x308 */ OSThread unk_308;
    /* 0x4B8 */ OSThread unk_4B8;
    /* 0x668 */ UNK_TYPE unk_668;
    /* 0x66C */ UNK_TYPE unk_66C;
    /* 0x670 */ UNK_TYPE unk_670;
    /* 0x674 */ UNK_TYPE unk_674;
    /* 0x678 */ UNK_TYPE unk_678;
} struct_800EB670; // size >= 0x67C



#endif

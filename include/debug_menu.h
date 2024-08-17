#ifndef DEBUG_MENU_H
#define DEBUG_MENU_H

#include "libultra.h"

typedef struct struct_800E5938 {
    /* 0x0 */ s8 unk_0;
    /* 0x1 */ s8 unk_1;
    /* 0x2 */ u16 unk_2;
} struct_800E5938; // size = 0x4

typedef struct struct_800E5968 {
    /* 0x0 */ s8 unk_0;
    /* 0x1 */ s8 unk_1;
} struct_800E5968; // size = 0x2

void DebugMenu_8003FB00(void);
void DebugMenu_8003FD0C(Gfx** gxfP);

void DebugMenu_800409A0(void);
void DebugMenu_800409DC(Gfx **gfxP);

#endif

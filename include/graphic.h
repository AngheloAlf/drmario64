#ifndef GRAPHIC_H
#define GRAPHIC_H

#include "libultra.h"

struct OSScTask_s;
struct NNSched;

#define GTASK_NO_MAX 3

typedef enum enum_graphic_no {
    /* 0 */ GRAPHIC_NO_0, // NONE?
    /* 1 */ GRAPHIC_NO_1,
    /* 2 */ GRAPHIC_NO_2,
    /* 3 */ GRAPHIC_NO_3,
    /* 4 */ GRAPHIC_NO_4,
    /* 5 */ GRAPHIC_NO_5,
    /* 6 */ GRAPHIC_NO_6,
    /* 7 */ GRAPHIC_NO_7 // ERROR?
} enum_graphic_no;

void gfxInit(void *arg0);
void gfxproc(void *arg);
void gfxproc_onRetrace(void);
void func_8002B710(void);
void func_8002B728(void);
void func_8002B754(void);
void gfxCreateGraphicThread(struct NNSched *sc);
s16 gfxWaitMessage(void);
void gfxTaskStart(struct OSScTask_s *scTask, void *data_ptr, size_t data_size, s32 arg3, u32 flags);
void F3RCPinitRtn(void);
void F3ClearFZRtn(u8 arg0);
void S2RDPinitRtn(u8 arg0);
void S2ClearCFBRtn(u8 arg0);

// data
extern void* gfx_ucode[][2];
extern s32 gCurrentFramebufferIndex;
extern enum_graphic_no graphic_no;
extern u32 pendingGFX;
extern Vp vp;
extern s32 rdpinit_flag_161;

extern Gfx S2RDPinit_dl[];
extern Gfx S2ClearCFB_dl[];
extern Gfx S2Spriteinit_dl[];
extern Gfx F3RDPinit_dl[];
extern Gfx F3SetupRDP_dl[];
extern Gfx F3SetupRSP_dl[];
extern Gfx D_80088360[];
extern Gfx D_800883A8[];

// bss
extern u32 gfx_gtask_no;

#endif

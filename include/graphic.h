#ifndef GRAPHIC_H
#define GRAPHIC_H

#include "libultra.h"
#include "PR/sched.h"

#include "stack.h"

struct NNSched;
struct NNScClient;

#define GRAPHIC_STACK_SIZE 0x2000
#define RDP_OUTPUT_SIZE 0x10000
#define DRAM_STACK_SIZE 0x400
#define GFXYIELDBUF_SIZE 0xC00

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
void gfxproc_onDoneSwap(void);
void gfxproc_onDoneTask(void);
void gfxproc_onPreNMI(void);
void gfxCreateGraphicThread(struct NNSched *sc);
s16 gfxWaitMessage(void);
void gfxTaskStart(OSScTask *scTask, void *data_ptr, size_t data_size, s32 arg3, u32 flags);
void F3RCPinitRtn(void);
void F3ClearFZRtn(u8 f);
void S2RDPinitRtn(u8 f);
void S2ClearCFBRtn(u8 f);

// data
extern void *gfx_ucode[][2];
extern s32 gCurrentFramebufferIndex;
extern enum_graphic_no graphic_no;
extern u32 pendingGFX;
extern Vp vp;
extern s32 rdpinit_flag_161;

// COMMON

extern STACK(sGraphicStack, GRAPHIC_STACK_SIZE);
extern STACK(rdp_output, RDP_OUTPUT_SIZE);
extern STACK(dram_stack, DRAM_STACK_SIZE);
extern STACK(gfxYieldBuf, GFXYIELDBUF_SIZE);
extern u32 gfx_gtask_no;
extern struct NNScClient gfx_client;
extern Gfx *gGfxHead;
extern Gfx gGfxGlist[GTASK_NO_MAX][0x1000];
extern OSScTask B_800FAE80[GTASK_NO_MAX];
extern s16 gfx_msg;
extern s16 gfx_msg_no;
extern OSMesgQueue gfx_msgQ;
extern OSMesg gfx_msgbuf[8];
extern OSMesgQueue *sched_gfxMQ;
extern OSThread gfxThread;

#endif

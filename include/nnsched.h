#ifndef _000280_H
#define _000280_H

#include "libultra.h"
#include "PR/sched.h"
#include "libc/stdbool.h"
#include "stack.h"
#include "unk.h"

#define NN_SC_STACKSIZE    0x2000  /* thread stack size */
#define NN_SC_SWAPBUFFER   0x0040  /* frame buffer swap */
#define NN_SC_RETRACE_MSG  1  /* retrace message */
#define NN_SC_DONE_MSG     2  /* task end message */
#define NN_SC_PRE_NMI_MSG  3  /*  NMI message */
#define NN_SC_GTASKEND_MSG 4  /*  task end  message (in the case of a graphic task,  task end only */
#define NN_SC_MAX_MESGS    8  /*  message buffer size */

/* define event message */
#define VIDEO_MSG       666  /* retrace message  */
#define RSP_DONE_MSG    667  /* RSP task done */
#define RDP_DONE_MSG    668  /* RDP draw done  */
#define PRE_NMI_MSG     669  /* NMI message */

/*
    For performance check.
    Please define NN_SC_PERF in order to check PCP performance.
 */
// #define NN_SC_PERF
#define NN_SC_PERF_NUM    4
#define NN_SC_GTASK_NUM   8   /* graphic task maximum number */
#define NN_SC_AUTASK_NUM   4  /* audio task maximum number */

typedef short NNScMsg;  /*  scheduler message type */

/**
 * Original name: NNScClient
 */
typedef struct NNScClient {
    /* 0x0 */ struct NNScClient *next; /* Original name: next */
    /* 0x4 */ OSMesgQueue *msgQ; /* Original name: msgQ */
} NNScClient; // size = 0x8

/**
 * Original name: NNSched
 */
typedef struct NNSched {
    /* 0x000 */ NNScMsg retraceMsg; /* Original name: retraceMsg */
    /* 0x002 */ NNScMsg prenmiMsg; /* Original name: prenmiMsg */
    /* 0x004 */ OSMesgQueue audioRequestMQ; /* Original name: audioRequestMQ */
    /* 0x01C */ OSMesg audioRequestBuf[NN_SC_MAX_MESGS]; /* Original name: audioRequestBuf */
    /* 0x03C */ OSMesgQueue graphicsRequestMQ; /* Original name: graphicsRequestMQ */
    /* 0x054 */ OSMesg graphicsRequestBuf[NN_SC_MAX_MESGS]; /* Original name: graphicsRequestBuf */
    /* 0x074 */ OSMesgQueue retraceMQ; /* Original name: retraceMQ */
    /* 0x08C */ OSMesg retraceMsgBuf[NN_SC_MAX_MESGS]; /* Original name: retraceMsgBuf */
    /* 0x0AC */ OSMesgQueue rspMQ; /* Original name: rspMQ */
    /* 0x0C4 */ OSMesg rspMsgBuf[NN_SC_MAX_MESGS]; /* Original name: rspMsgBuf */
    /* 0x0E4 */ OSMesgQueue rdpMQ; /* Original name: rdpMQ */
    /* 0x0FC */ OSMesg rdpMsgBuf[NN_SC_MAX_MESGS]; /* Original name: rdpMsgBuf */
    /* 0x11C */ OSMesgQueue waitMQ; /* Original name: waitMQ */
    /* 0x134 */ OSMesg waitMsgBuf[NN_SC_MAX_MESGS]; /* Original name: waitMsgBuf */
    /* 0x158 */ OSThread schedulerThread; /* Original name: schedulerThread */
    /* 0x308 */ OSThread audioThread; /* Original name: audioThread */
    /* 0x4B8 */ OSThread graphicsThread; /* Original name: graphicsThread */
    /* 0x668 */ NNScClient *clientList; /* Original name: clientList */
    /* 0x66C */ OSScTask *curGraphicsTask; /* Original name: curGraphicsTask */
    /* 0x670 */ OSScTask *curAudioTask; /* Original name: curAudioTask */
    /* 0x674 */ OSScTask *graphicsTaskSuspended; /* Original name: graphicsTaskSuspended */
    /* 0x678 */ bool firstTime; /* Original name: firstTime */
} NNSched; // size = 0x67C

#if VERSION_CN || VERSION_GW
typedef struct struct_8010ACB0_cn {
    /* 0x000 */ s32 unk_000;
    /* 0x000 */ s32 unk_004;
    /* 0x008 */ u64 unk_008;
    /* 0x010 */ u64 unk_010[8];
    /* 0x050 */ u64 unk_050[8];
    /* 0x090 */ u64 unk_090[8];
    /* 0x0D0 */ u64 unk_0D0[4];
    /* 0x0F0 */ u64 unk_0F0[4];
    /* 0x110 */ UNK_TYPE1 unk_110[0x8];
} struct_8010ACB0_cn; // size = 0x118
#endif


void nnScCreateScheduler(struct NNSched *sc, u8 viModeIndex, u8 retraceCount);
OSMesgQueue *nnScGetAudioMQ(struct NNSched *sc);
OSMesgQueue *nnScGetGfxMQ(struct NNSched *sc);
void nnScEventHandler(void *arg);
void nnScAddClient(struct NNSched *sc, struct NNScClient *c, OSMesgQueue *msgQ);
void nnScRemoveClient(struct NNSched *sc, struct NNScClient *c);
void nnScEventBroadcast(struct NNSched *sc, NNScMsg *msg);
void nnScExecuteAudio(void * arg);
void func_8002A3F4(struct NNSched *sc, OSScTask *task);
void nnScExecuteGraphics(void *arg);
void nnScWaitTaskReady(struct NNSched *sc, OSScTask *task);

extern u32 framecont;
extern u8 D_80088104;
extern s8 D_80088105;

#if VERSION_CN || VERSION_GW
void func_8002B8B4_cn(void);
void func_8002B910_cn();
void func_8002BA98_cn(u8 arg0, u8 arg1);
void func_8002BC30_cn(u8 arg0);
void func_8002BD04_cn(void);
void func_8002BD7C_cn(Gfx **gfxP, s32 arg1, s32 arg2);

extern s32 D_80092EA8_cn;
extern bool D_80092EAC_cn;
extern u32 D_80092EB0_cn[];
extern bool D_80092F10_cn;

extern struct_8010ACB0_cn *B_800CA234_cn;
extern struct_8010ACB0_cn *B_800CA298_cn;
extern struct_8010ACB0_cn B_8010ACB0_cn[]; // maybe length 4?
#endif

extern STACK(nnScStack, NN_SC_STACKSIZE);

extern STACK(nnScAudioStack, NN_SC_STACKSIZE);

extern STACK(nnScGraphicsStack, NN_SC_STACKSIZE);

#endif

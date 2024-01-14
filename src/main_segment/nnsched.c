/**
 * Original filename: nnsched.c
 *
 * A modified version of nnsched.c from the official SDK
 */

#include "nnsched.h"

#include "macros_defines.h"
#include "dm_thread.h"

/**
 * Original name: framecont
 */
u32 framecont = 0;

u8 D_80088104 = 1;
s8 D_80088105 = 0;

#if VERSION_CN || VERSION_GW
s32 D_80092EA8_cn = 0;

bool D_80092EAC_cn = false;

// unreferenced
u32 D_80092EB0_cn[] = {
    0x00010003, 0x00050007, 0x0009000B, 0x000D000F, 0x00110006, 0x00000000, 0x00110011, 0xFFC1FFC1,
    0xF83FF83F, 0x843F843F, 0x84218421, 0x07FF07FF, 0x003F003F, 0x07C107C1, 0xF801F801, 0xFD41FD41,
    0xFFFFFFFF, 0x00010001, 0x00010001, 0xF801F801, 0xFFFFFFFF, 0x00000000, 0x00000000, 0x00000000,
};

bool D_80092F10_cn = false;
#endif

/**
 * Original name: nnScCreateScheduler
 *
 * Create scheduler
 */
void nnScCreateScheduler(NNSched *sc, u8 viModeIndex, u8 retraceCount) {
    /* initialize variables */
    sc->curGraphicsTask = NULL;
    sc->curAudioTask = NULL;
    sc->graphicsTaskSuspended = NULL;
    sc->clientList = NULL;
    sc->firstTime = true;
    sc->retraceMsg = NN_SC_RETRACE_MSG;
    sc->prenmiMsg = NN_SC_PRE_NMI_MSG;

    /* create message queue */
    osCreateMesgQueue(&sc->retraceMQ, sc->retraceMsgBuf, ARRAY_COUNT(sc->retraceMsgBuf));
    osCreateMesgQueue(&sc->rspMQ, sc->rspMsgBuf, ARRAY_COUNT(sc->rspMsgBuf));
    osCreateMesgQueue(&sc->rdpMQ, sc->rdpMsgBuf, ARRAY_COUNT(sc->rdpMsgBuf));
    osCreateMesgQueue(&sc->graphicsRequestMQ, sc->graphicsRequestBuf, ARRAY_COUNT(sc->graphicsRequestBuf));
    osCreateMesgQueue(&sc->audioRequestMQ, sc->audioRequestBuf, ARRAY_COUNT(sc->audioRequestBuf));
    osCreateMesgQueue(&sc->waitMQ, sc->waitMsgBuf, ARRAY_COUNT(sc->waitMsgBuf));

    /* video mode settings  */
    osCreateViManager(OS_PRIORITY_VIMGR);
    osViSetMode(&osViModeTable[viModeIndex]);
    osViBlack(true);

    /* register event handler */
    osViSetEvent(&sc->retraceMQ, (OSMesg)VIDEO_MSG, retraceCount);
    osSetEventMesg(OS_EVENT_SP, &sc->rspMQ, (OSMesg)RSP_DONE_MSG);
    osSetEventMesg(OS_EVENT_DP, &sc->rdpMQ, (OSMesg)RDP_DONE_MSG);
    osSetEventMesg(OS_EVENT_PRENMI, &sc->retraceMQ, (OSMesg)PRE_NMI_MSG);

    /* start scheduler thread */
    osCreateThread(&sc->schedulerThread, THREAD_ID_19, nnScEventHandler, sc, STACK_TOP(nnScStack),
                   THREAD_PRI_NN_SC_EVENT);
    osStartThread(&sc->schedulerThread);

#if VERSION_CN || VERSION_GW
    func_8002B8B4_cn();
#endif

    osCreateThread(&sc->audioThread, THREAD_ID_18, nnScExecuteAudio, sc, STACK_TOP(nnScAudioStack),
                   THREAD_PRI_NN_SC_AUDIO);
    osStartThread(&sc->audioThread);

    osCreateThread(&sc->graphicsThread, THREAD_ID_17, nnScExecuteGraphics, sc, STACK_TOP(nnScGraphicsStack),
                   THREAD_PRI_NN_SC_GRAPHICS);
    osStartThread(&sc->graphicsThread);
}

/**
 * Original name: nnScGetAudioMQ
 *
 * Get audio message queue
 */
OSMesgQueue *nnScGetAudioMQ(NNSched *sc) {
    return &sc->audioRequestMQ;
}

/**
 * Original name: nnScGetGfxMQ
 *
 * Get grahics message queue
 */
OSMesgQueue *nnScGetGfxMQ(NNSched *sc) {
    return &sc->graphicsRequestMQ;
}

/**
 * Original name: nnScEventHandler
 *
 * Process system event
 */
void nnScEventHandler(void *arg) {
    u32 msg = 0;

    while (true) {
        NNSched *ptr = arg;

        osRecvMesg(&ptr->retraceMQ, (OSMesg)&msg, OS_MESG_BLOCK);

#if VERSION_US
        framecont++;
#elif VERSION_CN || VERSION_GW
        if (!D_80092F10_cn) {
            framecont++;
        }
#endif

        switch (msg) {
            case VIDEO_MSG:
                /* process retrace signal */
                nnScEventBroadcast(ptr, &ptr->retraceMsg);
                osSetTime(0);

#if VERSION_CN || VERSION_GW
                func_8002B910_cn();
                if (!D_80092EAC_cn) {
                    D_80092EAC_cn = true;
                    B_800CA234_cn = &B_8010ACB0_cn[D_80092EA8_cn];

                    D_80092EA8_cn = INC_WRAP(D_80092EA8_cn, 4);
                    B_800CA298_cn = &B_8010ACB0_cn[D_80092EA8_cn];
                    B_800CA298_cn->unk_004 = 0;
                    B_800CA298_cn->unk_000 = 0;
                    B_800CA298_cn->unk_008 = OS_CYCLES_TO_USEC(osGetTime());
                }
#endif
                break;

            case PRE_NMI_MSG:
                /* process NMI signal */
                nnScEventBroadcast(arg, &ptr->prenmiMsg);
                break;

            default:
                break;
        }
    }
}

/**
 * Original name: nnScAddClient
 *
 * Register client
 */
void nnScAddClient(NNSched *sc, NNScClient *c, OSMesgQueue *msgQ) {
    OSIntMask intMask = osSetIntMask(OS_IM_NONE);

    c->msgQ = msgQ;
    c->next = sc->clientList;
    sc->clientList = c;
    osSetIntMask(intMask);
}

/**
 * Original name: nnScRemoveClient
 *
 * Remove client
 */
void nnScRemoveClient(NNSched *sc, NNScClient *c) {
    NNScClient *iter = sc->clientList;
    NNScClient *prev = NULL;
    OSIntMask intMask = osSetIntMask(OS_IM_NONE);

    while (iter != NULL) {
        if (iter == c) {
            if (prev != NULL) {
                prev->next = iter->next;
            } else {
                sc->clientList = iter->next;
            }
            break;
        }
        prev = iter;
        iter = iter->next;
    }

    osSetIntMask(intMask);
}

/**
 * Original name: nnScEventBroadcast
 *
 * Transmit message to client
 */
void nnScEventBroadcast(NNSched *sc, NNScMsg *msg) {
    NNScClient *client = sc->clientList;

    /* inform necessary clients of retrace message */
    while (client != NULL) {
        osSendMesg(client->msgQ, msg, OS_MESG_NOBLOCK);
        client = client->next;
    }
}

/**
 * Original name: nnScExecuteAudio
 *
 * Execute audio task
 */
void nnScExecuteAudio(void *arg) {
    OSMesg msg = NULL;
    OSScTask *task = NULL;
    NNSched *sc = arg;

    while (true) {
        OSScTask *gfxTask;
        s32 yieldFlag;
#if VERSION_CN || VERSION_GW
        s32 var_s7;
#endif

        /* wait for audio execution request */
        osRecvMesg(&sc->audioRequestMQ, (OSMesg *)&task, OS_MESG_BLOCK);
        osWritebackDCacheAll();

        /* Inspect current RSP stack */
        gfxTask = sc->curGraphicsTask;
        yieldFlag = 0;
        if (gfxTask != NULL) {
            /* wait for graphic task to end (yield) */
            osSpTaskYield();
            osRecvMesg(&sc->rspMQ, &msg, OS_MESG_BLOCK);

            /* verify that task has actually yielded */
            yieldFlag = (osSpTaskYielded(&gfxTask->list) != 0) ? 1 : 2;
        }

#if VERSION_CN || VERSION_GW
        func_8002BC30_cn(7);
        if (B_800CA298_cn->unk_004 < ARRAY_COUNTU(B_800CA298_cn->unk_0D0)) {
            var_s7 = B_800CA298_cn->unk_004;

            B_800CA298_cn->unk_0D0[var_s7] = OS_CYCLES_TO_USEC(osGetTime()) - B_800CA298_cn->unk_008;
        }
#endif

        sc->curAudioTask = task;
        /* execute task */
        osSpTaskStart(&task->list);

        /* wait for end of RSP task */
        osRecvMesg(&sc->rspMQ, &msg, OS_MESG_BLOCK);
        sc->curAudioTask = NULL;

#if VERSION_CN || VERSION_GW
        func_8002BD04_cn();
        if (B_800CA298_cn->unk_004 < ARRAY_COUNTU(B_800CA298_cn->unk_0F0)) {
            B_800CA298_cn->unk_0F0[var_s7] = OS_CYCLES_TO_USEC(osGetTime()) - B_800CA298_cn->unk_008;
            B_800CA298_cn->unk_004++;
        }
#endif

        if (sc->graphicsTaskSuspended != NULL) {
            osSendMesg(&sc->waitMQ, &msg, OS_MESG_BLOCK);
        }

        /* restart graphic task that yielded */
        if (yieldFlag == 1) {
            osSpTaskStart(&gfxTask->list);
        } else if (yieldFlag == 2) {
            osSendMesg(&sc->rspMQ, &msg, OS_MESG_BLOCK);
        }

        /* inform thread started by audio task that task has ended */
        osSendMesg(task->msgQ, task->msg, OS_MESG_BLOCK);
    }
}

void func_8002A3F4(NNSched *sc, OSScTask *task) {
    OSMesg msg = NULL;
#if VERSION_CN || VERSION_GW
    s32 var_s5;
#endif

    /* wait for frame buffer to become available for use */
    nnScWaitTaskReady(sc, task);

    if (sc->curAudioTask != NULL) {
        sc->graphicsTaskSuspended = task;
        osRecvMesg(&sc->waitMQ, &msg, OS_MESG_BLOCK);
        sc->graphicsTaskSuspended = NULL;
    }

#if VERSION_CN || VERSION_GW
    func_8002BC30_cn(5);
    if (B_800CA298_cn->unk_000 < ARRAY_COUNTU(B_800CA298_cn->unk_010)) {
        var_s5 = B_800CA298_cn->unk_000;
        B_800CA298_cn->unk_010[var_s5] = OS_CYCLES_TO_USEC(osGetTime()) - B_800CA298_cn->unk_008;
    }
#endif

    sc->curGraphicsTask = task;
    /* execute task */
    osSpTaskStart(&task->list);

    /* wait for end of RSP task */
    osRecvMesg(&sc->rspMQ, &msg, OS_MESG_BLOCK);
    sc->curGraphicsTask = NULL;

#if VERSION_CN || VERSION_GW
    func_8002BC30_cn(6);

    if (B_800CA298_cn->unk_000 < ARRAY_COUNTU(B_800CA298_cn->unk_090)) {
        B_800CA298_cn->unk_090[var_s5] = OS_CYCLES_TO_USEC(osGetTime()) - B_800CA298_cn->unk_008;
    }
#endif

    /* wait for end of  RDP task */
    osRecvMesg(&sc->rdpMQ, &msg, OS_MESG_BLOCK);

#if VERSION_CN || VERSION_GW
    func_8002BD04_cn();
    func_8002BD04_cn();

    if (B_800CA298_cn->unk_000 < ARRAY_COUNTU(B_800CA298_cn->unk_050)) {
        B_800CA298_cn->unk_050[var_s5] = (OS_CYCLES_TO_USEC(osGetTime()) - B_800CA298_cn->unk_008);
        B_800CA298_cn->unk_000++;
    }
#endif

    /* invalidate video blackout first time only */
    if (sc->firstTime) {
        osViBlack(false);
        sc->firstTime = false;
    }

    /* specify next frame buffer to display */
    if (task->flags & OS_SC_SWAPBUFFER) {
        osViSwapBuffer(task->framebuffer);
        D_80088104 = 1;

#if VERSION_CN || VERSION_GW
        D_80092EAC_cn = false;
#endif
    }

    /* inform thread started by graphic task that task has ended */
    osSendMesg(task->msgQ, task->msg, OS_MESG_BLOCK);
}

/**
 * Original name: nnScExecuteGraphics
 *
 * Execute graphic task
 */
void nnScExecuteGraphics(void *arg) {
    NNSched *sc = arg;

    while (true) {
        OSScTask *msg;

        /* wait for graphic task execution request */
        osRecvMesg(&sc->graphicsRequestMQ, (OSMesg *)&msg, OS_MESG_BLOCK);

        func_8002A3F4(sc, msg);
    }
}

/**
 * Original name: nnScWaitTaskReady
 *
 * Wait for frame buffer to become available for use
 */
void nnScWaitTaskReady(NNSched *sc, OSScTask *task) {
    OSMesg msg = NULL;
    void *framebuffer = task->framebuffer;

    /* wait for next retrace if frame buffer is not empty */
    while ((osViGetCurrentFramebuffer() == framebuffer) || (osViGetNextFramebuffer() == framebuffer)) {
        NNScClient client;

        nnScAddClient(sc, &client, &sc->waitMQ);
        osRecvMesg(&sc->waitMQ, &msg, OS_MESG_BLOCK);
        nnScRemoveClient(sc, &client);
    }
}

#if VERSION_CN || VERSION_GW
#define B_800CA26C_CN_ARR_LEN 2
#define B_801020E8_CN_ARR_ARR_LEN 0x20

typedef struct struct_801020E8_cn {
    /* 0x0 */ u8 unk_0;
    /* 0x1 */ u8 unk_1;
    /* 0x4 */ s32 unk_4;
    /* 0x8 */ s32 unk_8;
} struct_801020E8_cn; // size = 0xC

extern struct_801020E8_cn B_801020E8_cn[][B_801020E8_CN_ARR_ARR_LEN];
extern struct_801020E8_cn *B_800CA1F0_cn;
extern u8 B_8010B140_cn[][B_801020E8_CN_ARR_ARR_LEN];

extern u8 B_800CA26C_cn[B_800CA26C_CN_ARR_LEN];
extern s8 B_800CA281_cn;
extern struct_801020E8_cn *B_800CA290_cn;
extern u8 B_800CA29B_cn;
extern u8 B_800CA2C0_cn[B_800CA26C_CN_ARR_LEN];
extern u8 *B_800CA1C0_cn;

void func_8002B8B4_cn(void) {
    s32 i;

    B_800CA29B_cn = 1;
    B_800CA281_cn = 1;
    B_800CA290_cn = B_801020E8_cn[1];
    for (i = 0; i < B_800CA26C_CN_ARR_LEN; i++) {
        B_800CA2C0_cn[i] = B_800CA26C_cn[i] = 0;
    }
}

void func_8002B910_cn(void) {
    s32 i;

    if (D_80088104 == 1) {
        B_800CA290_cn = B_800CA1F0_cn;
        B_800CA281_cn = B_800CA29B_cn;
        B_800CA29B_cn ^= 1;
        B_800CA1F0_cn = B_801020E8_cn[B_800CA29B_cn];
        B_800CA1C0_cn = B_8010B140_cn[B_800CA29B_cn];

        for (i = 0; i < B_801020E8_CN_ARR_ARR_LEN; i++) {
            B_800CA1F0_cn[i].unk_0 = 0xA;
            B_800CA1F0_cn[i].unk_4 = B_800CA1F0_cn[i].unk_8 = 0;

            B_800CA1C0_cn[i] = 0xA;
        }

        B_800CA2C0_cn[B_800CA29B_cn] = 1;

        B_800CA1F0_cn->unk_0 = 0xC;
        B_800CA1F0_cn->unk_4 = OS_CYCLES_TO_USEC(osGetTime());

        B_800CA26C_cn[B_800CA29B_cn] = 0;
        D_80088104 = 0;
        func_8002BA98_cn(0, 0);
    }
}

void func_8002BA98_cn(u8 arg0, u8 arg1) {
    B_800CA1F0_cn[B_800CA2C0_cn[B_800CA29B_cn] - 1].unk_8 = OS_CYCLES_TO_USEC(osGetTime());

    if (B_800CA2C0_cn[B_800CA29B_cn] < B_801020E8_CN_ARR_ARR_LEN) {
        B_800CA1F0_cn[B_800CA2C0_cn[B_800CA29B_cn]].unk_0 = arg0;
        B_800CA1F0_cn[B_800CA2C0_cn[B_800CA29B_cn]].unk_1 = arg1;
        B_800CA1F0_cn[B_800CA2C0_cn[B_800CA29B_cn]].unk_4 = OS_CYCLES_TO_USEC(osGetTime());

        B_800CA2C0_cn[B_800CA29B_cn]++;
    }
}

void func_8002BC30_cn(u8 arg0) {
    if (B_800CA26C_cn[B_800CA29B_cn] < B_801020E8_CN_ARR_ARR_LEN) {
        B_800CA1C0_cn[B_800CA26C_cn[B_800CA29B_cn]] = B_800CA1F0_cn[B_800CA2C0_cn[B_800CA29B_cn] - 1].unk_0;

        B_800CA26C_cn[B_800CA29B_cn]++;
        func_8002BA98_cn(arg0, 1);
    } else {
        func_8002BA98_cn(0xB, 1);
        func_8002BA98_cn(arg0, 1);
    }
}

void func_8002BD04_cn(void) {
    if (B_800CA26C_cn[B_800CA29B_cn] != 0) {
        B_800CA26C_cn[B_800CA29B_cn]--;
        func_8002BA98_cn(B_800CA1C0_cn[B_800CA26C_cn[B_800CA29B_cn]], 2);
    } else {
        func_8002BA98_cn(0xB, 2);
    }
}

void func_8002BD7C_cn(Gfx **gfxP, s32 arg1 UNUSED, s32 arg2 UNUSED) {
    Gfx *gfx = *gfxP;
    s32 what[4] UNUSED;

    gDPPipeSync(gfx);
}
#endif

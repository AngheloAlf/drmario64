/**
 * Original filename: nnsched.c
 *
 * A modified version of nnsched.c from the official SDK demos
 */

#include "nnsched.h"

#include "macros_defines.h"
#include "dm_thread.h"

STACK(nnScStack, NN_SC_STACKSIZE);
STACK(nnScAudioStack, NN_SC_STACKSIZE);
STACK(nnScGraphicsStack, NN_SC_STACKSIZE);

/**
 * Original name: framecont
 */
u32 framecont = 0;

u8 D_80088104 = 1;
s8 D_80088105 = 0;

#ifdef NN_SC_PERF
/**
 * Original name: nnsc_perf_ptr
 */
NNScPerf *nnsc_perf_ptr;

/**
 * Original name: nnsc_perf_inptr
 */
NNScPerf *nnsc_perf_inptr;

/**
 * Original name: nnsc_perf
 */
NNScPerf nnsc_perf[NN_SC_PERF_NUM];

/**
 * Original name: nnsc_perf_index
 */
s32 nnsc_perf_index = 0;

/**
 * Original name: nnsc_perf_flag
 */
bool nnsc_perf_flag = false;

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
    osCreateThread(&sc->schedulerThread, THREAD_ID_NN_SC_EVENT, nnScEventHandler, sc, STACK_TOP(nnScStack),
                   THREAD_PRI_NN_SC_EVENT);
    osStartThread(&sc->schedulerThread);

#ifdef NN_SC_PERF
    func_8002B8B4_cn();
#endif

    osCreateThread(&sc->audioThread, THREAD_ID_NN_SC_AUDIO, nnScExecuteAudio, sc, STACK_TOP(nnScAudioStack),
                   THREAD_PRI_NN_SC_AUDIO);
    osStartThread(&sc->audioThread);

    osCreateThread(&sc->graphicsThread, THREAD_ID_NN_SC_GRAPHICS, nnScExecuteGraphics, sc, STACK_TOP(nnScGraphicsStack),
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

#ifdef NN_SC_PERF
        if (!D_80092F10_cn) {
            framecont++;
        }
#else
        framecont++;
#endif

        switch (msg) {
            case VIDEO_MSG:
                /* process retrace signal */
                nnScEventBroadcast(ptr, &ptr->retraceMsg);
                osSetTime(0);

#ifdef NN_SC_PERF
                func_8002B910_cn();

                if (!nnsc_perf_flag) {
                    /* do not initialize until all graphic tasks are completed */
                    nnsc_perf_flag = true;

                    /* enable externally derived reference to measured buffer pointer */
                    nnsc_perf_ptr = &nnsc_perf[nnsc_perf_index];

                    /* swap buffer */
                    nnsc_perf_index = INC_WRAP(nnsc_perf_index, NN_SC_PERF_NUM);

                    nnsc_perf_inptr = &nnsc_perf[nnsc_perf_index];
                    nnsc_perf_inptr->autask_cnt = 0;
                    nnsc_perf_inptr->gtask_cnt = 0;

                    /* get retrace time */
                    nnsc_perf_inptr->retrace_time = OS_CYCLES_TO_USEC(osGetTime());
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
#ifdef NN_SC_PERF
        u32 task_cnt;
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

#ifdef NN_SC_PERF
        func_8002BC30_cn(ENUM_8002BA98_CN_ARG0_7);

        if (nnsc_perf_inptr->autask_cnt < ARRAY_COUNTU(nnsc_perf_inptr->autask_stime)) {
            task_cnt = nnsc_perf_inptr->autask_cnt;

            nnsc_perf_inptr->autask_stime[task_cnt] = OS_CYCLES_TO_USEC(osGetTime()) - nnsc_perf_inptr->retrace_time;
        }
#endif

        sc->curAudioTask = task;
        /* execute task */
        osSpTaskStart(&task->list);

        /* wait for end of RSP task */
        osRecvMesg(&sc->rspMQ, &msg, OS_MESG_BLOCK);
        sc->curAudioTask = NULL;

#ifdef NN_SC_PERF
        func_8002BD04_cn();
        if (nnsc_perf_inptr->autask_cnt < ARRAY_COUNTU(nnsc_perf_inptr->autask_etime)) {
            nnsc_perf_inptr->autask_etime[task_cnt] = OS_CYCLES_TO_USEC(osGetTime()) - nnsc_perf_inptr->retrace_time;
            nnsc_perf_inptr->autask_cnt++;
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
#ifdef NN_SC_PERF
    u32 task_cnt;
#endif

    /* wait for frame buffer to become available for use */
    nnScWaitTaskReady(sc, task);

    if (sc->curAudioTask != NULL) {
        sc->graphicsTaskSuspended = task;
        osRecvMesg(&sc->waitMQ, &msg, OS_MESG_BLOCK);
        sc->graphicsTaskSuspended = NULL;
    }

#ifdef NN_SC_PERF
    func_8002BC30_cn(ENUM_8002BA98_CN_ARG0_5);
    if (nnsc_perf_inptr->gtask_cnt < ARRAY_COUNTU(nnsc_perf_inptr->gtask_stime)) {
        task_cnt = nnsc_perf_inptr->gtask_cnt;
        nnsc_perf_inptr->gtask_stime[task_cnt] = OS_CYCLES_TO_USEC(osGetTime()) - nnsc_perf_inptr->retrace_time;
    }
#endif

    sc->curGraphicsTask = task;
    /* execute task */
    osSpTaskStart(&task->list);

    /* wait for end of RSP task */
    osRecvMesg(&sc->rspMQ, &msg, OS_MESG_BLOCK);
    sc->curGraphicsTask = NULL;

#ifdef NN_SC_PERF
    func_8002BC30_cn(ENUM_8002BA98_CN_ARG0_6);

    if (nnsc_perf_inptr->gtask_cnt < ARRAY_COUNTU(nnsc_perf_inptr->rsp_etime)) {
        nnsc_perf_inptr->rsp_etime[task_cnt] = OS_CYCLES_TO_USEC(osGetTime()) - nnsc_perf_inptr->retrace_time;
    }
#endif

    /* wait for end of  RDP task */
    osRecvMesg(&sc->rdpMQ, &msg, OS_MESG_BLOCK);

#ifdef NN_SC_PERF
    func_8002BD04_cn();
    func_8002BD04_cn();

    if (nnsc_perf_inptr->gtask_cnt < ARRAY_COUNTU(nnsc_perf_inptr->rdp_etime)) {
        nnsc_perf_inptr->rdp_etime[task_cnt] = (OS_CYCLES_TO_USEC(osGetTime()) - nnsc_perf_inptr->retrace_time);
        nnsc_perf_inptr->gtask_cnt++;
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

#ifdef NN_SC_PERF
        nnsc_perf_flag = false;
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

#ifdef NN_SC_PERF
struct_801020E8_cn B_801020E8_cn[B_800CA26C_CN_ARR_LEN][B_801020E8_CN_ARR_ARR_LEN];
struct_801020E8_cn *B_800CA1F0_cn;
u8 B_8010B140_cn[B_800CA26C_CN_ARR_LEN][B_801020E8_CN_ARR_ARR_LEN]; // enum_8002BA98_cn_arg0

u8 B_800CA26C_cn[B_800CA26C_CN_ARR_LEN];
s8 B_800CA281_cn;
struct_801020E8_cn *B_800CA290_cn;
u8 B_800CA29B_cn;
u8 B_800CA2C0_cn[B_800CA26C_CN_ARR_LEN];
u8 *B_800CA1C0_cn; // enum_8002BA98_cn_arg0

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
            B_800CA1F0_cn[i].unk_0 = ENUM_8002BA98_CN_ARG0_10;
            B_800CA1F0_cn[i].unk_4 = B_800CA1F0_cn[i].unk_8 = 0;

            B_800CA1C0_cn[i] = ENUM_8002BA98_CN_ARG0_10;
        }

        B_800CA2C0_cn[B_800CA29B_cn] = 1;

        B_800CA1F0_cn[0].unk_0 = ENUM_8002BA98_CN_ARG0_12;
        B_800CA1F0_cn[0].unk_4 = OS_CYCLES_TO_USEC(osGetTime());

        B_800CA26C_cn[B_800CA29B_cn] = 0;
        D_80088104 = 0;
        func_8002BA98_cn(ENUM_8002BA98_CN_ARG0_0, 0);
    }
}

void func_8002BA98_cn(enum_8002BA98_cn_arg0 arg0, s32 arg1) {
    u8 s2 = arg0;
    u8 s3 = arg1;

    B_800CA1F0_cn[B_800CA2C0_cn[B_800CA29B_cn] - 1].unk_8 = OS_CYCLES_TO_USEC(osGetTime());

    if (B_800CA2C0_cn[B_800CA29B_cn] < B_801020E8_CN_ARR_ARR_LEN) {
        B_800CA1F0_cn[B_800CA2C0_cn[B_800CA29B_cn]].unk_0 = s2;
        B_800CA1F0_cn[B_800CA2C0_cn[B_800CA29B_cn]].unk_1 = s3;
        B_800CA1F0_cn[B_800CA2C0_cn[B_800CA29B_cn]].unk_4 = OS_CYCLES_TO_USEC(osGetTime());

        B_800CA2C0_cn[B_800CA29B_cn]++;
    }
}

void func_8002BC30_cn(enum_8002BA98_cn_arg0 arg0) {
    u8 s0 = arg0;

    if (B_800CA26C_cn[B_800CA29B_cn] < B_801020E8_CN_ARR_ARR_LEN) {
        B_800CA1C0_cn[B_800CA26C_cn[B_800CA29B_cn]] = B_800CA1F0_cn[B_800CA2C0_cn[B_800CA29B_cn] - 1].unk_0;

        B_800CA26C_cn[B_800CA29B_cn]++;
        func_8002BA98_cn(s0, 1);
    } else {
        func_8002BA98_cn(ENUM_8002BA98_CN_ARG0_11, 1);
        func_8002BA98_cn(s0, 1);
    }
}

void func_8002BD04_cn(void) {
    if (B_800CA26C_cn[B_800CA29B_cn] != 0) {
        B_800CA26C_cn[B_800CA29B_cn]--;
        func_8002BA98_cn(B_800CA1C0_cn[B_800CA26C_cn[B_800CA29B_cn]], 2);
    } else {
        func_8002BA98_cn(ENUM_8002BA98_CN_ARG0_11, 2);
    }
}

void func_8002BD7C_cn(Gfx **gfxP, s32 arg1 UNUSED, s32 arg2 UNUSED) {
    Gfx *gfx = *gfxP;
    s32 what[4] UNUSED;

    gDPPipeSync(gfx);
}
#endif

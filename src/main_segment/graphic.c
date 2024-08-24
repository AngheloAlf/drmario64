/**
 * Original filename: graphic.c
 *
 * A modified version of graphic.c from the official SDK demos
 */

#include "graphic.h"

#include "macros_defines.h"

#include "gs2dex.h"

#include "boot_main.h"

#include "audio/sound.h"
#include "buffers.h"
#include "dm_game_main.h"
#include "dm_manual_main.h"
#include "dm_title_main.h"
#include "dm_thread.h"
#include "main_story.h"
#include "main_menu.h"
#include "nnsched.h"

STACK(sGraphicStack, GRAPHIC_STACK_SIZE);

/**
 * Original name: rdp_output
 */
STACK(rdp_output, RDP_OUTPUT_SIZE);

STACK(dram_stack, DRAM_STACK_SIZE);

STACK(gfxYieldBuf, GFXYIELDBUF_SIZE);

/**
 * Original name: gfx_gtask_no
 */
u32 gfx_gtask_no;

/**
 * Original name: gfx_client
 */
NNScClient gfx_client;

/**
 * Original name: gp
 *
 * main display list head
 */
Gfx *gGfxHead;

/**
 * Original name: gfx_glist
 */
Gfx gGfxGlist[GTASK_NO_MAX][0x1000];

OSScTask B_800FAE80[GTASK_NO_MAX];

/**
 * Original name: gfx_msg
 */
s16 gfx_msg;

/**
 * Original name: gfx_msg_no
 */
s16 gfx_msg_no;

/**
 * Original name: gfx_msgQ
 */
OSMesgQueue gfx_msgQ;

/**
 * Original name: gfx_msgbuf
 */
OSMesg gfx_msgbuf[8];

/**
 * Original name: sched_gfxMQ
 */
OSMesgQueue *sched_gfxMQ;

/**
 * Original name: gfxThread
 */
OSThread gfxThread;

/**
 * Original name: gfx_ucode
 */
void *gfx_ucode[][2] = {
    { gspF3DEX2_fifoTextStart, gspF3DEX2_fifoDataStart },
    { gspS2DEX_fifoTextStart, gspS2DEX_fifoDataStart },
};

/**
 *  Original name: wb_flag
 */
s32 gCurrentFramebufferIndex = 0;

/**
 *  Original name: graphic_no
 */
enum_graphic_no graphic_no = GRAPHIC_NO_0;

/**
 *  Original name: pendingGFX
 */
u32 pendingGFX = 0;

/**
 *  Original name: vp
 */
Vp vp = { { { 0x280, 0x1E0, 0x1FF, 0 }, { 0x280, 0x1E0, 0x1FF, 0 } } };

/**
 *  Original name: static rdpinit_flag
 *
 * flag to initialize RDP
 */
s32 rdpinit_flag_161 = 1;

STACK(sGraphicStack, GRAPHIC_STACK_SIZE);

/**
 * Original name: gfxInit
 *
 * Initialize graphic parameter
 */
void gfxInit(void *arg0 UNUSED) {
    /* Set graphic task end message */

    /* End task/switch buffer message  */
    gfx_msg = NN_SC_DONE_MSG;
    /* End task message only */
    gfx_msg_no = NN_SC_GTASKEND_MSG;

    /* Initialize graphic thread branch flag */
    graphic_no = GRAPHIC_NO_0;
    gfx_gtask_no = 0;
}

/**
 * Original name: gfxproc
 *
 * Graphic thread
 */
void gfxproc(void *arg) {
    NNSched *sc = arg;
    s16 *msg_type = NULL;

    pendingGFX = 0;

    /* create message queue for VI reatrace */
    osCreateMesgQueue(&gfx_msgQ, gfx_msgbuf, ARRAY_COUNT(gfx_msgbuf));
    nnScAddClient(sc, &gfx_client, &gfx_msgQ);

    /* Acquire graphic message queue */
    sched_gfxMQ = nnScGetGfxMQ(sc);

    while (true) {
        osRecvMesg(&gfx_msgQ, (OSMesg *)&msg_type, OS_MESG_BLOCK);

        switch (*msg_type) {
            case NN_SC_RETRACE_MSG:
                /* Retrace message processing */
                gfxproc_onRetrace();
                break;

            case NN_SC_DONE_MSG:
                /* graphic task end message*/
                func_8002B710();
                break;

            case NN_SC_GTASKEND_MSG:
                func_8002B728();
                break;

            case NN_SC_PRE_NMI_MSG:
                /* PRE NMI message */
                func_8002B754();
                break;
        }
    }
}

/**
 * Original name: gfxproc_onRetrace
 */
void gfxproc_onRetrace(void) {
#ifdef NN_SC_PERF
    func_8002BC30_cn(ENUM_8002BA98_CN_ARG0_3);
#endif

    switch (graphic_no) {
        case GRAPHIC_NO_0:
            break;

        case GRAPHIC_NO_1:
            if (pendingGFX < 2) {
                graphic_story();
            }
            break;

        case GRAPHIC_NO_2:
            if (pendingGFX < 2) {
                dm_title_graphic();
            }
            break;

        case GRAPHIC_NO_3:
            if (pendingGFX < 2) {
                dm_manual_graphic();
            }
            break;

        case GRAPHIC_NO_4:
            if (pendingGFX == 0) {
                dm_game_graphic();
            }
            break;

        case GRAPHIC_NO_5:
            if (pendingGFX < 2) {
                graphic_menu();
            }
            break;

        case GRAPHIC_NO_6:
            if (pendingGFX < 2) {
                graphic_techmes();
            }
            break;

        case GRAPHIC_NO_7:
            if (pendingGFX < 2) {
                graphic_boot_error();
            }
            break;
    }

#ifdef NN_SC_PERF
    func_8002BD04_cn();
#endif
}

/**
 * graphic task end message
 */
void func_8002B710(void) {
    pendingGFX--;
}

void func_8002B728(void) {
    if (graphic_no == GRAPHIC_NO_4) {
        func_80071A44();
    }
}

/**
 * PRE NMI message
 */
void func_8002B754(void) {
    /* !!important!! Make Y scale value back to 1.0  */
    osViSetYScale(1.0f);

    /*do not create task */
    pendingGFX += 2;

    osViBlack(true);
    Main_StopThread();
    MusStop(MUSFLAG_EFFECTS | MUSFLAG_SONGS, 0);
}

/**
 * Original name: gfxCreateGraphicThread
 *
 * Create and activate graphic thread
 */
void gfxCreateGraphicThread(NNSched *sc) {
    osCreateThread(&gfxThread, THREAD_ID_GRAPHIC, gfxproc, sc, STACK_TOP(sGraphicStack), THREAD_PRI_GRAPHIC);
    osStartThread(&gfxThread);
}

/**
 * Original name: gfxWaitMessage
 *
 * Wait for message from scheduler
 *  return : message type from scheduler
 *  OS_SC_RETRACE_MSG    :retrace message
 *  OS_SC_PRE_NMI_MSG    :  PRE NMI message
 */
s16 gfxWaitMessage(void) {
    s16 *msg_type = NULL;

    osRecvMesg(&gfx_msgQ, (OSMesg *)&msg_type, OS_MESG_BLOCK);
    return *msg_type;
}

/**
 * Original name: gfxTaskStart
 *
 * Send graphic task activating message to scheduler
 *   NNScTask *gtask     :task structure
 *   Gfx*        glist_ptr :pointer of display list
 *   s32         glist_size:display list size
 *   u32         ucode_type:type of micro code (see graphic.h)
 *   u32         flag      :flag to change frame buffer
 */
void gfxTaskStart(OSScTask *scTask, void *data_ptr, size_t data_size, s32 arg3, u32 flags) {
    scTask->list.t.data_ptr = data_ptr;
    scTask->list.t.data_size = data_size;

    scTask->list.t.type = M_GFXTASK;
    scTask->list.t.flags = OS_SC_NEEDS_RSP | OS_SC_DRAM_DLIST;

    scTask->list.t.ucode_boot = (void *)rspbootTextStart;
    scTask->list.t.ucode_boot_size = (u8 *)rspbootTextEnd - (u8 *)rspbootTextStart;

    scTask->list.t.ucode = gfx_ucode[arg3][0];
    scTask->list.t.ucode_data = gfx_ucode[arg3][1];
    scTask->list.t.ucode_data_size = SP_UCODE_DATA_SIZE;

    scTask->list.t.dram_stack = dram_stack;
    scTask->list.t.dram_stack_size = sizeof(dram_stack);

    scTask->list.t.output_buff = rdp_output;
    scTask->list.t.output_buff_size = STACK_TOP(rdp_output);

    scTask->list.t.yield_data_ptr = gfxYieldBuf;
    scTask->list.t.yield_data_size = sizeof(gfxYieldBuf);

    scTask->next = NULL;
    scTask->flags = flags;
    scTask->msgQ = &gfx_msgQ;

    if (flags & OS_SC_SWAPBUFFER) {
        scTask->msg = &gfx_msg;
        pendingGFX++;
    } else {
        scTask->msg = &gfx_msg_no;
    }

    scTask->framebuffer = &gFramebuffers[gCurrentFramebufferIndex];
    osSendMesg(sched_gfxMQ, scTask, OS_MESG_BLOCK);
    if (flags & OS_SC_SWAPBUFFER) {
        gCurrentFramebufferIndex ^= 1;
    }

    gfx_gtask_no = INC_WRAP(gfx_gtask_no, GTASK_NO_MAX);
}

/**
 * Original name: F3RCPinitRtn/gfxRCPIinit
 *
 * Initialize RSP RDP
 */
void F3RCPinitRtn(void) {
    /* set RSP segment register */
    /* for CPU virtual address */
    gSPSegment(gGfxHead++, 0x00, 0x00000000);

    /* set RSP  */
    gSPDisplayList(gGfxHead++, OS_K0_TO_PHYSICAL(F3SetupRSP_dl));

    gSPViewport(gGfxHead++, &vp);

    /* initialize RDP (one time only)  */
    if (rdpinit_flag_161 == 1) {
        gSPDisplayList(gGfxHead++, OS_K0_TO_PHYSICAL(F3RDPinit_dl));
        rdpinit_flag_161 = 0;
    }

    /* set RDP*/
    gSPDisplayList(gGfxHead++, OS_K0_TO_PHYSICAL(F3SetupRDP_dl));

    gDPSetScissor(gGfxHead++, G_SC_NON_INTERLACE, 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1);
}

/**
 * Original name: F3ClearFZRtn
 *
 * Based on DrawWindow?
 */
void F3ClearFZRtn(u8 arg0) {
    gDPSetCycleType(gGfxHead++, G_CYC_FILL);
    gDPSetColorImage(gGfxHead++, G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WIDTH,
                     osVirtualToPhysical(gFramebuffers[gCurrentFramebufferIndex]));

    if (arg0) {
        gDPSetFillColor(gGfxHead++, (GPACK_RGBA5551(0, 0, 0, 1) << 16) | GPACK_RGBA5551(0, 0, 0, 1));
        gDPFillRectangle(gGfxHead++, 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1);
    }

    gDPPipeSync(gGfxHead++);
    gDPSetCycleType(gGfxHead++, G_CYC_1CYCLE);
}

/**
 * Original name: S2RDPinitRtn
 */
void S2RDPinitRtn(u8 arg0) {
    gSPDisplayList(gGfxHead++, OS_K0_TO_PHYSICAL(S2RDPinit_dl));
    if (arg0) {
        gDPSetScissor(gGfxHead++, G_SC_NON_INTERLACE, 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1);
    } else {
        gDPSetScissor(gGfxHead++, G_SC_NON_INTERLACE, 12, 8, SCREEN_WIDTH - 1 - 12, SCREEN_HEIGHT - 1 - 8);
    }
}

/**
 * Original name: S2ClearCFBRtn
 */
void S2ClearCFBRtn(u8 arg0) {
    gDPSetColorImage(gGfxHead++, G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WIDTH,
                     osVirtualToPhysical(gFramebuffers[gCurrentFramebufferIndex]));
    if (arg0) {
        gSPDisplayList(gGfxHead++, OS_K0_TO_PHYSICAL(S2ClearCFB_dl));
        gDPFillRectangle(gGfxHead++, 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1);
    }
}

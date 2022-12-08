/**
 * Original filename: graphic.c
 */

#include "macros_defines.h"
#include "unknown_structs.h"
#include "boot_functions.h"
#include "boot_variables.h"
#include "main_segment_functions.h"
#include "main_segment_variables.h"
#include "audio/audio_stuff.h"
#include "buffers.h"

/**
 * Original name: gfxInit
 */
void gfxInit(UNK_PTR arg0 UNUSED) {
    B_800ED430 = 2;
    B_800E9BB6 = 4;
    graphic_no = 0;
    B_800FAD2C = 0;
}

/**
 * Original name: gfxproc
 */
void gfxproc(struct_800EB670 *arg0) {
    s16 *sp10 = NULL;

    pendingGFX = 0;
    osCreateMesgQueue(&B_800F4898, B_800EBED0, ARRAY_COUNT(B_800EBED0));
    func_8002A184(arg0, &B_800F48B0, &B_800F4898);
    B_800FAF94 = func_8002A0D4(arg0);

    while (true) {
        osRecvMesg(&B_800F4898, (OSMesg *)&sp10, OS_MESG_BLOCK);

        switch (*sp10) {
            case 1:
                gfxproc_onRetrace();
                break;

            case 2:
                func_8002B710();
                break;

            case 4:
                func_8002B728();
                break;

            case 3:
                func_8002B754();
                break;
        }
    }
}

/**
 * Original name: gfxproc_onRetrace
 */
void gfxproc_onRetrace(void) {
    switch (graphic_no) {
        case 0:
            break;

        case 1:
            if (pendingGFX < 2) {
                func_8007AEF4();
            }
            break;

        case 2:
            if (pendingGFX < 2) {
                dm_title_graphic();
            }
            break;

        case 3:
            if (pendingGFX < 2) {
                func_80075CF8();
            }
            break;

        case 4:
            if (pendingGFX == 0) {
                func_8007023C();
            }
            break;

        case 5:
            if (pendingGFX < 2) {
                func_8005B658();
            }
            break;

        case 6:
            if (pendingGFX < 2) {
                func_80071CE0();
            }
            break;

        case 7:
            if (pendingGFX < 2) {
                graphic_boot_error();
            }
            break;
    }
}

void func_8002B710(void) {
    pendingGFX -= 1;
}

void func_8002B728(void) {
    if (graphic_no == 4) {
        func_80071A44();
    }
}

void func_8002B754(void) {
    osViSetYScale(1.0f);
    pendingGFX += 2;
    osViBlack(true);
    func_80000468();
    MusStop(MUSFLAG_EFFECTS | MUSFLAG_SONGS, 0);
}

/**
 * Original name: gfxCreateGraphicThread
 */
void gfxCreateGraphicThread(struct_800EB670 *arg0) {
    osCreateThread(&B_800EBD20, 5, (StartThreadFunc)gfxproc, arg0, STACK_TOP(B_800F1E30), 0xF);
    osStartThread(&B_800EBD20);
}

s16 func_8002B800(void) {
    s16 *sp10 = NULL;

    osRecvMesg(&B_800F4898, (OSMesg *)&sp10, OS_MESG_BLOCK);
    return *sp10;
}

/**
 * Original name: gfxTaskStart
 */
void gfxTaskStart(OSScTask *scTask, void *data_ptr, size_t data_size, s32 arg3, u32 flags) {
    scTask->list.t.type = M_GFXTASK;
    scTask->list.t.flags = OS_SC_NEEDS_RSP | OS_SC_DRAM_DLIST;
    scTask->list.t.data_ptr = data_ptr;
    scTask->list.t.data_size = data_size;
    scTask->list.t.ucode_boot = (void *)rspbootTextStart;
    scTask->list.t.ucode_boot_size = (u8 *)rspbootTextEnd - (u8 *)rspbootTextStart;
    scTask->list.t.ucode = D_80088110[arg3][0];
    scTask->list.t.ucode_data = D_80088110[arg3][1];
    scTask->list.t.ucode_data_size = SP_UCODE_DATA_SIZE;
    scTask->list.t.dram_stack = B_800FAFA0;
    scTask->list.t.dram_stack_size = sizeof(B_800FAFA0);
    scTask->list.t.output_buff = B_801136F0;
    scTask->list.t.output_buff_size = (u64 *)&B_801236F0;
    scTask->list.t.yield_data_ptr = B_800F7490;
    scTask->list.t.yield_data_size = sizeof(B_800F7490);
    scTask->next = NULL;
    scTask->msgQ = &B_800F4898;
    scTask->flags = flags;
    if (flags & OS_SC_SWAPBUFFER) {
        scTask->msg = &B_800ED430;
        pendingGFX++;
    } else {
        scTask->msg = &B_800E9BB6;
    }
    scTask->framebuffer = &gFramebuffers[gCurrentFramebufferIndex];
    osSendMesg(B_800FAF94, scTask, OS_MESG_BLOCK);
    if (flags & OS_SC_SWAPBUFFER) {
        gCurrentFramebufferIndex ^= 1;
    }
    B_800FAD2C = (B_800FAD2C + 1) % 3;
}

/**
 * Original name: F3RCPinitRtn
 */
void F3RCPinitRtn(void) {
    gSPSegment(gGfxHead++, 0x00, 0x00000000);
    gSPDisplayList(gGfxHead++, OS_K0_TO_PHYSICAL(D_80088328));
    gSPViewport(gGfxHead++, &D_80088130);

    if (D_80088140 == 1) {
        gSPDisplayList(gGfxHead++, OS_K0_TO_PHYSICAL(D_80088228));
        D_80088140 = 0;
    }

    gSPDisplayList(gGfxHead++, OS_K0_TO_PHYSICAL(D_80088308));
    gDPSetScissor(gGfxHead++, G_SC_NON_INTERLACE, 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1);
}

/**
 * Original name: F3ClearFZRtn
 */
void F3ClearFZRtn(u8 arg0) {
    gDPSetCycleType(gGfxHead++, G_CYC_FILL);
    gDPSetColorImage(gGfxHead++, G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WIDTH, osVirtualToPhysical(gFramebuffers[gCurrentFramebufferIndex]));

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
    gSPDisplayList(gGfxHead++, OS_K0_TO_PHYSICAL(D_80088150));
    if (arg0) {
        gDPSetScissor(gGfxHead++, G_SC_NON_INTERLACE, 0, 0, 319, 239);
    } else {
        gDPSetScissor(gGfxHead++, G_SC_NON_INTERLACE, 12, 8, 307, 231);
    }
}

/**
 * Original name: S2ClearCFBRtn
 */
void S2ClearCFBRtn(u8 arg0) {
    gDPSetColorImage(gGfxHead++, G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WIDTH, osVirtualToPhysical(gFramebuffers[gCurrentFramebufferIndex]));
    if (arg0) {
        gSPDisplayList(gGfxHead++, OS_K0_TO_PHYSICAL(D_800881B8));
        gDPFillRectangle(gGfxHead++, 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1);
    }
}

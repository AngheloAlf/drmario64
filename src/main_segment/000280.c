#include "ultra64.h"
#include "libc/stdbool.h"
#include "include_asm.h"
#include "unk.h"
#include "macros_defines.h"
#include "main_segment_functions.h"
#include "main_segment_variables.h"
#include "audio/audio_stuff.h"

void func_80029ED0(struct_800EB670 *arg0, u8 viModeIndex, u8 retraceCount) {
    arg0->unk_678 = 1;
    arg0->unk_000 = 1;
    arg0->unk_66C = 0;
    arg0->unk_670 = 0;
    arg0->unk_674 = 0;
    arg0->unk_668 = 0;
    arg0->unk_002 = 3;

    osCreateMesgQueue(&arg0->unk_074, arg0->unk_08C, ARRAY_COUNT(arg0->unk_08C));
    osCreateMesgQueue(&arg0->unk_0AC, arg0->unk_0C4, ARRAY_COUNT(arg0->unk_0C4));
    osCreateMesgQueue(&arg0->unk_0E4, arg0->unk_0FC, ARRAY_COUNT(arg0->unk_0FC));
    osCreateMesgQueue(&arg0->unk_03C, arg0->unk_054, ARRAY_COUNT(arg0->unk_054));
    osCreateMesgQueue(&arg0->unk_004, arg0->unk_01C, ARRAY_COUNT(arg0->unk_01C));
    osCreateMesgQueue(&arg0->unk_11C, arg0->unk_134, ARRAY_COUNT(arg0->unk_134));

    osCreateViManager(OS_PRIORITY_VIMGR);
    osViSetMode(&osViModeTable[viModeIndex]);
    osViBlack(true);

    osViSetEvent(&arg0->unk_074, (OSMesg)0x29A, retraceCount);

    osSetEventMesg(OS_EVENT_SP, &arg0->unk_0AC, (OSMesg)0x29B);
    osSetEventMesg(OS_EVENT_DP, &arg0->unk_0E4, (OSMesg)0x29C);
    osSetEventMesg(OS_EVENT_PRENMI, &arg0->unk_074, (OSMesg)0x29D);

    osCreateThread(&arg0->unk_158, 0x13, (StartThreadFunc)func_8002A0DC, arg0, STACK_TOP(B_800EFCE0), 0x78);
    osStartThread(&arg0->unk_158);
    osCreateThread(&arg0->unk_308, 0x12, (StartThreadFunc)func_8002A2B8, arg0, STACK_TOP(B_800F8CE0), 0x6E);
    osStartThread(&arg0->unk_308);
    osCreateThread(&arg0->unk_4B8, 0x11, (StartThreadFunc)func_8002A4D8, arg0, STACK_TOP(B_800ED440), 0x64);
    osStartThread(&arg0->unk_4B8);
}

OSMesgQueue *func_8002A0CC(struct_800EB670 *arg0, UNK_PTR arg1 UNUSED) {
    return &arg0->unk_004;
}

OSMesgQueue *func_8002A0D4(struct_800EB670 *arg0) {
    return &arg0->unk_03C;
}

void func_8002A0DC(struct_800EB670 *arg) {
    OSMesg msg = (OSMesg)0;

    while (true) {
        osRecvMesg(&arg->unk_074, &msg, OS_MESG_BLOCK);

        D_80088100++;

        switch ((u32)msg) {
            case 0x29A:
                func_8002A26C(arg, arg);
                osSetTime(0);
                break;

            case 0x29D:
                func_8002A26C(arg, &arg->unk_002);
                break;

            default:
                break;
        }
    }
}

void func_8002A184(struct_800EB670 *arg0, struct_800FAF98_unk_64 *arg1, OSMesgQueue *arg2) {
    OSIntMask intMask = osSetIntMask(OS_IM_NONE);

    arg1->unk_4 = arg2;
    arg1->unk_0 = arg0->unk_668;
    arg0->unk_668 = arg1;
    osSetIntMask(intMask);
}

void func_8002A1DC(struct_800EB670 *arg0, struct_800FAF98_unk_64 *arg1) {
    struct_800FAF98_unk_64 *iter = arg0->unk_668;
    struct_800FAF98_unk_64 *prev = NULL;
    OSIntMask intMask = osSetIntMask(OS_IM_NONE);

    while (iter != NULL) {
        if (iter == arg1) {
            if (prev != NULL) {
                prev->unk_0 = iter->unk_0;
            } else {
                arg0->unk_668 = iter->unk_0;
            }
            break;
        }
        prev = iter;
        iter = iter->unk_0;
    }

    osSetIntMask(intMask);
}

void func_8002A26C(struct_800EB670 *arg0, OSMesg msg) {
    struct_800FAF98_unk_64 *var_s0 = arg0->unk_668;

    while (var_s0 != NULL) {
        osSendMesg(var_s0->unk_4, msg, OS_MESG_NOBLOCK);
        var_s0 = var_s0->unk_0;
    }
}

void func_8002A2B8(struct_800EB670 *arg0) {
    OSMesg sp14 = NULL;
    struct_8002A2B8_sp10 *sp10 = NULL;

    while (true) {
        struct_800EB670_unk_66C *temp_s2;
        s32 var_s0;

        osRecvMesg(&arg0->unk_004, (OSMesg *)&sp10, OS_MESG_BLOCK);
        var_s0 = 0;
        osWritebackDCacheAll();
        temp_s2 = arg0->unk_66C;
        if (temp_s2 != NULL) {
            var_s0 = 2;
            osSpTaskYield();
            osRecvMesg(&arg0->unk_0AC, &sp14, OS_MESG_BLOCK);
            if (osSpTaskYielded(&temp_s2->unk_10)) {
                var_s0 = 1;
            }
        }

        arg0->unk_670 = sp10;
        osSpTaskLoad(&sp10->unk_10);
        osSpTaskStartGo(&sp10->unk_10);
        osRecvMesg(&arg0->unk_0AC, &sp14, OS_MESG_BLOCK);
        arg0->unk_670 = NULL;
        if (arg0->unk_674 != 0) {
            osSendMesg(&arg0->unk_11C, &sp14, OS_MESG_BLOCK);
        }

        if (var_s0 == 1) {
            osSpTaskLoad(&temp_s2->unk_10);
            osSpTaskStartGo(&temp_s2->unk_10);
        } else if (var_s0 == 2) {
            osSendMesg(&arg0->unk_0AC, &sp14, OS_MESG_BLOCK);
        }
        osSendMesg(sp10->unk_50, sp10->unk_54, OS_MESG_BLOCK);
    }
}

void func_8002A3F4(struct_800EB670 *arg0, struct_800EB670_unk_66C *arg1) {
    OSMesg sp10 = NULL;

    func_8002A51C(arg0, arg1);
    if (arg0->unk_670 != NULL) {
        arg0->unk_674 = (s32)arg1;
        osRecvMesg(&arg0->unk_11C, &sp10, OS_MESG_BLOCK);
        arg0->unk_674 = 0;
    }

    arg0->unk_66C = arg1;
    osSpTaskLoad(&arg1->unk_10);
    osSpTaskStartGo(&arg1->unk_10);
    osRecvMesg(&arg0->unk_0AC, &sp10, OS_MESG_BLOCK);
    arg0->unk_66C = NULL;
    osRecvMesg(&arg0->unk_0E4, &sp10, OS_MESG_BLOCK);
    if (arg0->unk_678 != 0) {
        osViBlack(false);
        arg0->unk_678 = 0;
    }
    if (arg1->unk_08 & 0x40) {
        osViSwapBuffer(arg1->unk_0C);
        D_80088104[0] = 1;
    }

    osSendMesg(arg1->unk_50, arg1->unk_54, OS_MESG_BLOCK);
}

void func_8002A4D8(struct_800EB670 *arg0) {
    while (true) {
        OSMesg msg;

        osRecvMesg(&arg0->unk_03C, &msg, OS_MESG_BLOCK);
        func_8002A3F4(arg0, msg);
    }
}

void func_8002A51C(struct_800EB670 *arg0, struct_800EB670_unk_66C *arg1) {
    OSMesg sp18 = NULL;
    void *framebuffer = arg1->unk_0C;

    while ((osViGetCurrentFramebuffer() == framebuffer) || (osViGetNextFramebuffer() == framebuffer)) {
        struct_800FAF98_unk_64 sp10;

        func_8002A184(arg0, &sp10, &arg0->unk_11C);
        osRecvMesg(&arg0->unk_11C, &sp18, OS_MESG_BLOCK);
        func_8002A1DC(arg0, &sp10);
    }
}

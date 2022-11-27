#include "ultra64.h"
#include "libc/stdbool.h"
#include "include_asm.h"
#include "unk.h"
#include "macros_defines.h"
#include "main_segment_functions.h"
#include "main_segment_variables.h"
#include "audio/audio_stuff.h"


void func_80029ED0(struct_800EB670* arg0, u8 viModeIndex, u8 retraceCount) {
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

    // TODO: determine the start of those 3 stacks

    osCreateThread(&arg0->unk_158, 0x13, (StartThreadFunc)func_8002A0DC, arg0, &B_800F1CE0, 0x78);
    osStartThread(&arg0->unk_158);
    osCreateThread(&arg0->unk_308, 0x12, (StartThreadFunc)func_8002A2B8, arg0, &B_800FACE0, 0x6E);
    osStartThread(&arg0->unk_308);
    osCreateThread(&arg0->unk_4B8, 0x11, (StartThreadFunc)func_8002A4D8, arg0, &B_800EF440, 0x64);
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

        switch ((u32)msg)  {
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

#if 0
void func_8002A184(void *arg0, struct_800FAF98_unk_64 *arg1, OSMesgQueue *arg2) {
    OSIntMask temp_v0 = osSetIntMask(1);

    arg1->unk_4 = arg2;
    arg1->unk_0 = (void *) arg0->unk_668;
    arg0->unk_668 = arg1;
    osSetIntMask(temp_v0);
}
#else
INCLUDE_ASM("asm/nonmatchings/main_segment/000280", func_8002A184);
#endif

INCLUDE_ASM("asm/nonmatchings/main_segment/000280", func_8002A1DC);

void func_8002A26C(struct_800EB670 *arg0, OSMesg msg) {
    struct_800EB670_unk_668 *var_s0 = arg0->unk_668;

    while (var_s0 != NULL) {
        osSendMesg(var_s0->unk_4, msg, OS_MESG_NOBLOCK);
        var_s0 = var_s0->unk_0;
    }
}

INCLUDE_ASM("asm/nonmatchings/main_segment/000280", func_8002A2B8);

INCLUDE_ASM("asm/nonmatchings/main_segment/000280", func_8002A3F4);

void func_8002A4D8(struct_800EB670 *arg0) {
    while (true) {
        OSMesg msg;

        osRecvMesg(&arg0->unk_03C, &msg, OS_MESG_BLOCK);
        func_8002A3F4(arg0, msg);
    }
}

INCLUDE_ASM("asm/nonmatchings/main_segment/000280", func_8002A51C);

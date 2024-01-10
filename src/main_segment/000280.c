#include "000280.h"

#include "macros_defines.h"
#include "dm_thread.h"

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

void func_80029ED0(struct_800EB670 *arg0, u8 viModeIndex, u8 retraceCount) {
    arg0->unk_66C = NULL;
    arg0->unk_670 = NULL;
    arg0->unk_674 = NULL;
    arg0->unk_668 = NULL;
    arg0->unk_678 = 1;
    arg0->unk_000 = 1;
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

    osCreateThread(&arg0->unk_158, THREAD_ID_19, func_8002A0DC, arg0, STACK_TOP(B_800EFCE0), THREAD_PRI_19);
    osStartThread(&arg0->unk_158);

#if VERSION_CN || VERSION_GW
    func_8002B8B4_cn();
#endif

    osCreateThread(&arg0->unk_308, THREAD_ID_18, func_8002A2B8, arg0, STACK_TOP(B_800F8CE0), THREAD_PRI_18);
    osStartThread(&arg0->unk_308);
    osCreateThread(&arg0->unk_4B8, THREAD_ID_17, func_8002A4D8, arg0, STACK_TOP(B_800ED440), THREAD_PRI_17);
    osStartThread(&arg0->unk_4B8);
}

OSMesgQueue *func_8002A0CC(struct_800EB670 *arg0, void *arg1 UNUSED) {
    return &arg0->unk_004;
}

OSMesgQueue *func_8002A0D4(struct_800EB670 *arg0) {
    return &arg0->unk_03C;
}

void func_8002A0DC(void *arg) {
    u32 msg = 0;

    while (true) {
        struct_800EB670 *ptr = arg;

        osRecvMesg(&ptr->unk_074, (OSMesg)&msg, OS_MESG_BLOCK);

#if VERSION_US
        framecont++;
#elif VERSION_CN || VERSION_GW
        if (!D_80092F10_cn) {
            framecont++;
        }
#endif

        switch (msg) {
            case 0x29A:
                func_8002A26C(ptr, &ptr->unk_000);
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

            case 0x29D:
                func_8002A26C(arg, &ptr->unk_002);
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

void func_8002A2B8(void *arg) {
    OSMesg sp14 = NULL;
    OSScTask *sp10 = NULL;
    struct_800EB670 *ptr = arg;

    while (true) {
        OSScTask *temp_s2;
        s32 var_s0;
#if VERSION_CN || VERSION_GW
        s32 var_s7;
#endif

        osRecvMesg(&ptr->unk_004, (OSMesg *)&sp10, OS_MESG_BLOCK);
        osWritebackDCacheAll();
        temp_s2 = ptr->unk_66C;

        var_s0 = 0;
        if (temp_s2 != NULL) {
            osSpTaskYield();
            osRecvMesg(&ptr->unk_0AC, &sp14, OS_MESG_BLOCK);

            var_s0 = (osSpTaskYielded(&temp_s2->list) != 0) ? 1 : 2;
        }

#if VERSION_CN || VERSION_GW
        func_8002BC30_cn(7);
        if (B_800CA298_cn->unk_004 < ARRAY_COUNTU(B_800CA298_cn->unk_0D0)) {
            var_s7 = B_800CA298_cn->unk_004;

            B_800CA298_cn->unk_0D0[var_s7] = OS_CYCLES_TO_USEC(osGetTime()) - B_800CA298_cn->unk_008;
        }
#endif

        ptr->unk_670 = sp10;
        osSpTaskLoad(&sp10->list);
        osSpTaskStartGo(&sp10->list);
        osRecvMesg(&ptr->unk_0AC, &sp14, OS_MESG_BLOCK);
        ptr->unk_670 = NULL;

#if VERSION_CN || VERSION_GW
        func_8002BD04_cn();
        if (B_800CA298_cn->unk_004 < ARRAY_COUNTU(B_800CA298_cn->unk_0F0)) {
            B_800CA298_cn->unk_0F0[var_s7] = OS_CYCLES_TO_USEC(osGetTime()) - B_800CA298_cn->unk_008;
            B_800CA298_cn->unk_004++;
        }
#endif

        if (ptr->unk_674 != NULL) {
            osSendMesg(&ptr->unk_11C, &sp14, OS_MESG_BLOCK);
        }

        if (var_s0 == 1) {
            osSpTaskLoad(&temp_s2->list);
            osSpTaskStartGo(&temp_s2->list);
        } else if (var_s0 == 2) {
            osSendMesg(&ptr->unk_0AC, &sp14, OS_MESG_BLOCK);
        }

        osSendMesg(sp10->msgQ, sp10->msg, OS_MESG_BLOCK);
    }
}

void func_8002A3F4(struct_800EB670 *arg0, OSScTask *arg1) {
    OSMesg sp10 = NULL;
#if VERSION_CN || VERSION_GW
    s32 var_s5;
#endif

    func_8002A51C(arg0, arg1);
    if (arg0->unk_670 != NULL) {
        arg0->unk_674 = arg1;
        osRecvMesg(&arg0->unk_11C, &sp10, OS_MESG_BLOCK);
        arg0->unk_674 = 0;
    }

#if VERSION_CN || VERSION_GW
    func_8002BC30_cn(5);
    if (B_800CA298_cn->unk_000 < ARRAY_COUNTU(B_800CA298_cn->unk_010)) {
        var_s5 = B_800CA298_cn->unk_000;
        B_800CA298_cn->unk_010[var_s5] = OS_CYCLES_TO_USEC(osGetTime()) - B_800CA298_cn->unk_008;
    }
#endif

    arg0->unk_66C = arg1;
    osSpTaskLoad(&arg1->list);
    osSpTaskStartGo(&arg1->list);
    osRecvMesg(&arg0->unk_0AC, &sp10, OS_MESG_BLOCK);
    arg0->unk_66C = NULL;

#if VERSION_CN || VERSION_GW
    func_8002BC30_cn(6);

    if (B_800CA298_cn->unk_000 < ARRAY_COUNTU(B_800CA298_cn->unk_090)) {
        B_800CA298_cn->unk_090[var_s5] = OS_CYCLES_TO_USEC(osGetTime()) - B_800CA298_cn->unk_008;
    }
#endif

    osRecvMesg(&arg0->unk_0E4, &sp10, OS_MESG_BLOCK);

#if VERSION_CN || VERSION_GW
    func_8002BD04_cn();
    func_8002BD04_cn();

    if (B_800CA298_cn->unk_000 < ARRAY_COUNTU(B_800CA298_cn->unk_050)) {
        B_800CA298_cn->unk_050[var_s5] = (OS_CYCLES_TO_USEC(osGetTime()) - B_800CA298_cn->unk_008);
        B_800CA298_cn->unk_000++;
    }
#endif

    if (arg0->unk_678 != 0) {
        osViBlack(false);
        arg0->unk_678 = 0;
    }

    if (arg1->flags & OS_SC_SWAPBUFFER) {
        osViSwapBuffer(arg1->framebuffer);
        D_80088104 = 1;

#if VERSION_CN || VERSION_GW
        D_80092EAC_cn = false;
#endif
    }

    osSendMesg(arg1->msgQ, arg1->msg, OS_MESG_BLOCK);
}

void func_8002A4D8(void *arg) {
    struct_800EB670 *ptr = arg;

    while (true) {
        OSScTask *msg;

        osRecvMesg(&ptr->unk_03C, (OSMesg *)&msg, OS_MESG_BLOCK);
        func_8002A3F4(ptr, msg);
    }
}

void func_8002A51C(struct_800EB670 *arg0, OSScTask *arg1) {
    OSMesg sp18 = NULL;
    void *framebuffer = arg1->framebuffer;

    while ((osViGetCurrentFramebuffer() == framebuffer) || (osViGetNextFramebuffer() == framebuffer)) {
        struct_800FAF98_unk_64 sp10;

        func_8002A184(arg0, &sp10, &arg0->unk_11C);
        osRecvMesg(&arg0->unk_11C, &sp18, OS_MESG_BLOCK);
        func_8002A1DC(arg0, &sp10);
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

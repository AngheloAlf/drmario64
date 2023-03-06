#include "libultra.h"
#include "libc/stdbool.h"
#include "include_asm.h"
#include "unk.h"
#include "macros_defines.h"
#include "main_segment_functions.h"
#include "main_segment_variables.h"
#include "audio/audio_stuff.h"
#include "dm_thread.h"

s32 D_80088100 = 0;

s8 D_80088104[] = { 1, 0 };

#if VERSION_CN
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
    arg0->unk_674 = 0;
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

    osCreateThread(&arg0->unk_158, THREAD_ID_19, (StartThreadFunc)func_8002A0DC, arg0, STACK_TOP(B_800EFCE0),
                   THREAD_PRI_19);
    osStartThread(&arg0->unk_158);

#if VERSION_CN
    func_8002B8B4_cn();
#endif

    osCreateThread(&arg0->unk_308, THREAD_ID_18, (StartThreadFunc)func_8002A2B8, arg0, STACK_TOP(B_800F8CE0),
                   THREAD_PRI_18);
    osStartThread(&arg0->unk_308);
    osCreateThread(&arg0->unk_4B8, THREAD_ID_17, (StartThreadFunc)func_8002A4D8, arg0, STACK_TOP(B_800ED440),
                   THREAD_PRI_17);
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

#if VERSION_CN
        if (!D_80092F10_cn) {
#endif
            D_80088100++;
#if VERSION_CN
        }
#endif

        switch ((u32)msg) {
            case 0x29A:
                func_8002A26C(arg, arg);
                osSetTime(0);

#if VERSION_CN
                func_8002B910_cn();
                if (!D_80092EAC_cn) {
                    D_80092EAC_cn = true;
                    B_800CA234_cn = &B_8010ACB0_cn[D_80092EA8_cn];

                    D_80092EA8_cn = (D_80092EA8_cn + 1) % 4U;
                    B_800CA298_cn = &B_8010ACB0_cn[D_80092EA8_cn];
                    B_800CA298_cn->unk_004 = 0;
                    B_800CA298_cn->unk_000 = 0;
                    B_800CA298_cn->unk_008 = OS_CYCLES_TO_USEC(osGetTime());
                }
#endif
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
#if VERSION_CN
        s32 var_s7;
#endif

        osRecvMesg(&arg0->unk_004, (OSMesg *)&sp10, OS_MESG_BLOCK);
        osWritebackDCacheAll();
        temp_s2 = arg0->unk_66C;

        var_s0 = 0;
        if (temp_s2 != NULL) {
            osSpTaskYield();
            osRecvMesg(&arg0->unk_0AC, &sp14, OS_MESG_BLOCK);

            var_s0 = (osSpTaskYielded(&temp_s2->unk_10) != 0) ? 1 : 2;
        }

#if VERSION_CN
        func_8002BC30_cn(7);
        if (B_800CA298_cn->unk_004 < ARRAY_COUNTU(B_800CA298_cn->unk_0D0)) {
            var_s7 = B_800CA298_cn->unk_004;

            B_800CA298_cn->unk_0D0[var_s7] = OS_CYCLES_TO_USEC(osGetTime()) - B_800CA298_cn->unk_008;
        }
#endif

        arg0->unk_670 = sp10;
        osSpTaskLoad(&sp10->unk_10);
        osSpTaskStartGo(&sp10->unk_10);
        osRecvMesg(&arg0->unk_0AC, &sp14, OS_MESG_BLOCK);
        arg0->unk_670 = NULL;

#if VERSION_CN
        func_8002BD04_cn();
        if (B_800CA298_cn->unk_004 < ARRAY_COUNTU(B_800CA298_cn->unk_0F0)) {
            B_800CA298_cn->unk_0F0[var_s7] = OS_CYCLES_TO_USEC(osGetTime()) - B_800CA298_cn->unk_008;
            B_800CA298_cn->unk_004++;
        }
#endif

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
#if VERSION_CN
    s32 var_s5;
#endif

    func_8002A51C(arg0, arg1);
    if (arg0->unk_670 != NULL) {
        arg0->unk_674 = (s32)arg1;
        osRecvMesg(&arg0->unk_11C, &sp10, OS_MESG_BLOCK);
        arg0->unk_674 = 0;
    }

#if VERSION_CN
    func_8002BC30_cn(5);
    if (B_800CA298_cn->unk_000 < ARRAY_COUNTU(B_800CA298_cn->unk_010)) {
        var_s5 = B_800CA298_cn->unk_000;
        B_800CA298_cn->unk_010[var_s5] = OS_CYCLES_TO_USEC(osGetTime()) - B_800CA298_cn->unk_008;
    }
#endif

    arg0->unk_66C = arg1;
    osSpTaskLoad(&arg1->unk_10);
    osSpTaskStartGo(&arg1->unk_10);
    osRecvMesg(&arg0->unk_0AC, &sp10, OS_MESG_BLOCK);
    arg0->unk_66C = NULL;

#if VERSION_CN
    func_8002BC30_cn(6);

    if (B_800CA298_cn->unk_000 < ARRAY_COUNTU(B_800CA298_cn->unk_090)) {
        B_800CA298_cn->unk_090[var_s5] = OS_CYCLES_TO_USEC(osGetTime()) - B_800CA298_cn->unk_008;
    }
#endif

    osRecvMesg(&arg0->unk_0E4, &sp10, OS_MESG_BLOCK);

#if VERSION_CN
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

    if (arg1->unk_08 & 0x40) {
        osViSwapBuffer(arg1->unk_0C);
        D_80088104[0] = 1;

#if VERSION_CN
        D_80092EAC_cn = false;
#endif
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

#if VERSION_CN
#if 0
void func_8002B8B4_cn(void) {
    s32 var_a1;
    s8 *temp_a0;
    s8 *temp_v1;

    var_a1 = 0;
    B_800CA29B_cn = 1;
    B_800CA281_cn = 1;
    B_800CA290_cn = &B_80102268_cn;
    do {
        temp_a0 = var_a1 + &B_800CA2C0_cn;
        temp_v1 = var_a1 + &B_800CA26C_cn;
        var_a1 += 1;
        *temp_v1 = 0;
        *temp_a0 = 0;
    } while (var_a1 < 2);
}
#else
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/000280", func_8002B8B4_cn);
#endif

#if 0
void func_8002B910_cn(void) {
    s32 var_a2;
    s32 var_a3;
    s8 *temp_a0_2;
    u32 temp_v1_2;
    u32 temp_v1_3;
    u64 temp_ret;
    u8 temp_a0;
    u8 temp_v0;
    void *temp_v1;

    if ((u8) *D_80088104 == 1) {
        var_a3 = 0;
        var_a2 = 0;
        temp_a0 = B_800CA29B_cn;
        temp_v0 = temp_a0 ^ 1;
        B_800CA29B_cn = temp_v0;
        B_800CA281_cn = temp_a0;
        B_800CA290_cn = B_800CA1F0_cn;
        B_800CA1F0_cn = ((temp_v0 & 0xFF) * 0x180) + &B_801020E8_cn;
        B_800CA1C0_cn = (B_800CA29B_cn << 5) + &B_8010B140_cn;
        do {
            *(var_a2 + B_800CA1F0_cn) = 0xA;
            temp_v1 = var_a2 + B_800CA1F0_cn;
            temp_v1->unk_8 = 0;
            temp_v1->unk_4 = 0;
            var_a2 += 0xC;
            temp_a0_2 = B_800CA1C0_cn + var_a3;
            var_a3 += 1;
            *temp_a0_2 = 0xA;
        } while (var_a3 < 0x20);
        *(&B_800CA2C0_cn + B_800CA29B_cn) = 1;
        B_800CA1F0_cn->unk_0 = 0xC;
        temp_ret = osGetTime();
        temp_v1_2 = (u32) temp_ret;
        temp_v1_3 = (u32) __udivdi3((temp_ret << 6) | (temp_v1_2 >> 0x1A), temp_v1_2 << 6, 0, 0xBB8);
        *D_80088104 = 0;
        B_800CA1F0_cn->unk_4 = temp_v1_3;
        *(&B_800CA26C_cn + B_800CA29B_cn) = 0;
        func_8002BA98_cn(0U, 0, B_800CA29B_cn);
    }
}
#else
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/000280", func_8002B910_cn);
#endif

#if 0
void func_8002BA98_cn(u8 arg0, s32 arg1) {
    u32 temp_v1;
    u32 temp_v1_2;
    u64 temp_ret;
    u64 temp_ret_2;
    u8 *temp_a0;
    u8 *temp_a0_2;
    void *temp_s0;
    void *temp_s0_2;

    temp_ret = osGetTime();
    temp_v1 = (u32) temp_ret;
    temp_s0 = ((*(&B_800CA2C0_cn + B_800CA29B_cn) * 0xC) + B_800CA1F0_cn) - 0xC;
    temp_s0->unk_8 = (u32) __udivdi3((temp_ret << 6) | (temp_v1 >> 0x1A), temp_v1 << 6, 0, 0xBB8);
    temp_a0 = B_800CA29B_cn + &B_800CA2C0_cn;
    if ((u8) *temp_a0 < 0x20U) {
        *((*temp_a0 * 0xC) + B_800CA1F0_cn) = arg0 & 0xFF;
        ((*(B_800CA29B_cn + &B_800CA2C0_cn) * 0xC) + B_800CA1F0_cn)->unk_1 = (s8) (arg1 & 0xFF);
        temp_ret_2 = osGetTime();
        temp_v1_2 = (u32) temp_ret_2;
        temp_s0_2 = (*(B_800CA29B_cn + &B_800CA2C0_cn) * 0xC) + B_800CA1F0_cn;
        temp_s0_2->unk_4 = (u32) __udivdi3((temp_ret_2 << 6) | (temp_v1_2 >> 0x1A), temp_v1_2 << 6, 0, 0xBB8);
        temp_a0_2 = B_800CA29B_cn + &B_800CA2C0_cn;
        *temp_a0_2 += 1;
    }
}
#else
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/000280", func_8002BA98_cn);
#endif

#if 0
void func_8002BC30_cn(s32 arg0) {
    u8 *temp_a1;
    u8 *temp_a2;

    temp_a1 = B_800CA29B_cn + &B_800CA26C_cn;
    if ((u8) *temp_a1 < 0x20U) {
        *(B_800CA1C0_cn + *temp_a1) = ((*(&B_800CA2C0_cn + B_800CA29B_cn) * 0xC) + B_800CA1F0_cn)->unk_-C;
        temp_a2 = B_800CA29B_cn + &B_800CA26C_cn;
        *temp_a2 += 1;
    } else {
        func_8002BA98_cn(0xBU, 1);
    }
    func_8002BA98_cn(arg0 & 0xFF, 1);
}
#else
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/000280", func_8002BC30_cn);
#endif

#if 0
void func_8002BD04_cn(void) {
    u8 *temp_a0;
    u8 temp_v0;
    u8 var_a0;

    temp_a0 = B_800CA29B_cn + &B_800CA26C_cn;
    temp_v0 = *temp_a0;
    if (temp_v0 != 0) {
        *temp_a0 = temp_v0 - 1;
        var_a0 = *(B_800CA1C0_cn + *(B_800CA29B_cn + &B_800CA26C_cn));
    } else {
        var_a0 = 0xB;
    }
    func_8002BA98_cn(var_a0, 2);
}
#else
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/000280", func_8002BD04_cn);
#endif

void func_8002BD7C_cn(Gfx **gfxP, s32 arg1 UNUSED, s32 arg2 UNUSED) {
    Gfx *gfx = *gfxP;
    s32 what[4] UNUSED;

    gDPPipeSync(gfx);
}
#endif

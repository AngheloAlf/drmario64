/**
 * Original filename: joy.c
 */

#include "joy.h"

#include "macros_defines.h"
#include "unknown_structs.h"
#include "main_segment_variables.h"

#include "gateway.h"
#include "nnsched.h"

/**
 * Original name: joycur
 */
u16 joycur[MAXCONTROLLERS + 1];

/**
 * Original name: joyupd
 */
u16 gControllerPressedButtons[MAXCONTROLLERS + 1];

u16 gControllerPrevHoldButtons[MAXCONTROLLERS + 1];

u16 gControllerHoldButtons[MAXCONTROLLERS + 1];

/**
 * Original name: joycnt
 */
u16 joycnt[MAXCONTROLLERS][0x10];

/**
 * Original name: joyflg
 */
u16 joyflg[MAXCONTROLLERS];

/**
 * Original name: joygam
 */
u16 joygam[MAXCONTROLLERS];

/**
 * Original name: joygmf
 */
u8 joygmf[MAXCONTROLLERS];

/**
 * Original name: link_joy
 */
u8 link_joy[MAXCONTROLLERS];

/**
 * Original name: main_joy
 */
u8 main_joy[MAXCONTROLLERS];

/**
 * Original name: joycur1
 */
u16 joycur1;

/**
 * Original name: joycur2
 */
u16 joycur2;

OSContStatus B_800F5358[4];
OSMesgQueue B_800F3E38;
OSMesg B_800F3E60[1];
OSContPad B_800EB4D8[MAXCONTROLLERS];

/**
 * Original filename: joyInit
 */
s32 joyInit(s32 arg0 UNUSED) {
    OSMesgQueue mq;
    OSMesg sp28[1];
    u8 bitpattern;
    s32 i;

    osCreateMesgQueue(&mq, sp28, ARRAY_COUNT(sp28));
    osSetEventMesg(OS_EVENT_SI, &mq, NULL);
    osContSetCh(MAXCONTROLLERS);
    osContInit(&mq, &bitpattern, B_800F5358);
    osCreateMesgQueue(&B_800F3E38, B_800F3E60, ARRAY_COUNT(B_800F3E60));
    osSetEventMesg(OS_EVENT_SI, &B_800F3E38, NULL);

    for (i = 0; i < ARRAY_COUNT(gControllerPressedButtons); i++) {
        joycur[i] = 0;
        gControllerPressedButtons[i] = 0;
        gControllerPrevHoldButtons[i] = 0;
        gControllerHoldButtons[i] = 0;
    }

    for (i = 0; i < ARRAY_COUNT(joycnt); i++) {
        s32 j;

        for (j = 0; j < ARRAY_COUNT(joycnt[i]); j++) {
            joycnt[i][j] = 0;
        }

        joyflg[i] = 0;
        joygam[i] = 0;
        joygmf[i] = 0;
    }

    joycur1 = 0x14;
    joycur2 = 4;
    return 4;
}

/**
 * Original filename: joyProcCore
 */
void joyProcCore(void) {
    u16 i;

#if VERSION_GW
    bool pressingOppositeDirections = false;
#endif

#ifdef NN_SC_PERF
    bool temp = D_80092F10_cn;

    func_8002BC30_cn(ENUM_8002BA98_CN_ARG0_4);
#endif

    osContStartReadData(&B_800F3E38);
    osRecvMesg(&B_800F3E38, NULL, OS_MESG_BLOCK);
    osContGetReadData(B_800EB4D8);

#if VERSION_GW
    for (i = 0; i < MAXCONTROLLERS; i++) {
        if (CHECK_FLAG_ALL(B_800EB4D8[i].button, U_JPAD | D_JPAD)) {
            temp = true;
            pressingOppositeDirections = true;
        } else if (CHECK_FLAG_ALL(B_800EB4D8[i].button, L_JPAD | R_JPAD)) {
            temp = false;
            pressingOppositeDirections = true;
        }
    }

    if (pressingOppositeDirections) {
        for (i = 0; i < MAXCONTROLLERS; i++) {
            B_800EB4D8[i].button = 0;
            B_800EB4D8[i].stick_x = 0;
            B_800EB4D8[i].stick_y = 0;
        }
    }
#endif

    for (i = 0; i < ARRAY_COUNT(joycnt); i++) {
        u16 j;

#if VERSION_CN
        u16 mask;
#endif

#if VERSION_US || VERSION_GW
        u32 mask;
        u32 button = B_800EB4D8[i].button;

        gControllerHoldButtons[i] = button;

        gControllerPressedButtons[i] = ~gControllerPrevHoldButtons[i];
        gControllerPressedButtons[i] &= button;
#endif

#if VERSION_CN
        gControllerHoldButtons[i] = B_800EB4D8[i].button;

        gControllerPressedButtons[i] = ~gControllerPrevHoldButtons[i];
        gControllerPressedButtons[i] &= B_800EB4D8[i].button;
#endif

        joycur[i] = 0;

        for (j = 0, mask = 0x8000; j < ARRAY_COUNT(joycnt[i]); j++, mask >>= 1) {
            if (joyflg[i] & mask) {
                if (mask & gControllerHoldButtons[i]) {
                    joycnt[i][j]++;
                    if ((joycnt[i][j] == 1) ||
                        ((joycnt[i][j] >= joycur1) && (((joycnt[i][j] - joycur1) % joycur2) == 0))) {
                        joycur[i] |= mask;
                    }
                } else {
                    joycnt[i][j] = 0;
                }
            }
        }

        gControllerPrevHoldButtons[i] = gControllerHoldButtons[i];
    }

#ifdef NN_SC_PERF
    i = !!temp;
    if (D_80092F10_cn) {
        i++;
    }

    if (i == 1) {
        D_80092F10_cn = temp;
        Gateway_80002AE8_cn(D_80092F10_cn);
    }

    func_8002BD04_cn();
#endif
}

/**
 * Original filename: joyCursorFastSet
 */
void joyCursorFastSet(u16 mask, u8 index) {
    s32 var_a0 = mask;
    s32 j;

    for (j = ARRAY_COUNT(joycnt[0]) - 1; j >= 0; j--) {
        if (var_a0 & 1) {
            break;
        }

        var_a0 >>= 1;
    }
    joycnt[index][j] = joycur1 + joycur2 - 1;
}

/**
 * Returns the amount of connected controllers
 *
 * Original filename: joyResponseCheck
 */
s32 joyResponseCheck(void) {
    s32 connectedControllers = 0;
    OSContStatus padStatus[MAXCONTROLLERS];
    s8 j;
    s8 i;

    osContStartQuery(&B_800F3E38);
    osRecvMesg(&B_800F3E38, NULL, OS_MESG_BLOCK);
    osContGetQuery(padStatus);

    for (i = 0; i < 4; i++) {
        main_joy[i] = 4;
    }

    j = 0;
    for (i = 0; i < ARRAY_COUNT(padStatus); i++) {
        link_joy[i] = false;

        switch (padStatus[i].errno) {
            case CONT_NO_RESPONSE_ERROR:
                break;

            default:
                if ((padStatus[i].type & CONT_TYPE_MASK) == CONT_TYPE_NORMAL) {
                    link_joy[i] = true;
                    main_joy[j] = i;
                    connectedControllers++;
                    j++;
                }
        }
    }

    return connectedControllers;
}

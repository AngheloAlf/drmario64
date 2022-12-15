/**
 * Original filename: joy.c
 */

#include "ultra64.h"
#include "include_asm.h"
#include "macros_defines.h"
#include "unknown_structs.h"
#include "boot_functions.h"
#include "boot_variables.h"
#include "main_segment_functions.h"
#include "main_segment_variables.h"

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
        B_800F48C4[i] = 0;
        gControllerPressedButtons[i] = 0;
        gControllerPrevHoldButtons[i] = 0;
        gControllerHoldButtons[i] = 0;
    }

    for (i = 0; i < ARRAY_COUNT(joycnt); i++) {
        s32 j;

        for (j = ARRAY_COUNT(joycnt[i]) - 1; j >= 0; j--) {
            joycnt[i][j] = 0;
        }

        joyflg[i] = 0;
        joygam[i] = 0;
        B_800FAD31[i] = 0;
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

    osContStartReadData(&B_800F3E38);
    osRecvMesg(&B_800F3E38, NULL, OS_MESG_BLOCK);
    osContGetReadData(B_800EB4D8);

    for (i = 0; i < ARRAY_COUNT(joycnt); i++) {
        u16 button = B_800EB4D8[i].button;
        u16 j;
        u32 mask;

        gControllerHoldButtons[i] = button;

        gControllerPressedButtons[i] = ~gControllerPrevHoldButtons[i];
        gControllerPressedButtons[i] &= button;

        B_800F48C4[i] = 0;

        for (j = 0, mask = 0x8000; j < ARRAY_COUNT(joycnt[i]); j++, mask >>= 1) {
            if (joyflg[i] & mask) {
                if (mask & gControllerHoldButtons[i]) {
                    joycnt[i][j]++;
                    if ((joycnt[i][j] == 1) ||
                        ((joycnt[i][j] >= joycur1) && (((joycnt[i][j] - joycur1) % joycur2) == 0))) {
                        B_800F48C4[i] |= mask;
                    }
                } else {
                    joycnt[i][j] = 0;
                }
            }
        }

        gControllerPrevHoldButtons[i] = gControllerHoldButtons[i];
    }
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
        B_800EBD16[i] = 4;
    }

    j = 0;
    for (i = 0; i < 4; i++) {
        B_800F3E78[i] = 0;
        switch (padStatus[i].errno) {
            case CONT_NO_RESPONSE_ERROR:
                break;

            default:
                if ((padStatus[i].type & CONT_TYPE_MASK) == CONT_TYPE_NORMAL) {
                    B_800F3E78[i] = 1;
                    B_800EBD16[j] = i;
                    connectedControllers++;
                    j++;
                }
        }
    }

    return connectedControllers;
}

#include "ultra64.h"
#include "include_asm.h"
#include "macros_defines.h"
#include "unknown_structs.h"
#include "boot_functions.h"
#include "boot_variables.h"
#include "main_segment_functions.h"
#include "main_segment_variables.h"

s32 func_8002A5B0(UNK_TYPE arg0 UNUSED) {
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

    for (i = 0; i < 5; i++) {
        B_800F48C4[i] = 0;
        B_800FAF88[i] = 0;
        B_800F3E64[i] = 0;
        B_800EBCF8[i] = 0;
    }

    for (i = 0; i < 4; i++) {
        s32 j;

        for (j = ARRAY_COUNT(B_80113670[i]) - 1; j >= 0; j--) {
            B_80113670[i][j] = 0;
        }

        B_800F6CD8[i] = 0;
        B_800F48B8[i] = 0;
        B_800FAD31[i] = 0;
    }

    B_800EF554 = 0x14;
    B_800F1E20 = 4;
    return 4;
}

void func_8002A700(void) {
    u16 i;

    osContStartReadData(&B_800F3E38);
    osRecvMesg(&B_800F3E38, NULL, OS_MESG_BLOCK);
    osContGetReadData(B_800EB4D8);

    for (i = 0; i < ARRAY_COUNT(B_80113670); i++) {
        u16 button = B_800EB4D8[i].button;
        u16 j;
        u32 mask;

        B_800EBCF8[i] = button;

        B_800FAF88[i] = ~B_800F3E64[i];
        B_800FAF88[i] &= button;

        B_800F48C4[i] = 0;

        for (j = 0, mask = 0x8000; j < ARRAY_COUNT(B_80113670[i]); j++, mask >>= 1) {
            if (B_800F6CD8[i] & mask) {
                if (mask & B_800EBCF8[i]) {
                    B_80113670[i][j]++;
                    if ((B_80113670[i][j] == 1) || ((B_80113670[i][j] >= B_800EF554) && (((B_80113670[i][j] - B_800EF554) % B_800F1E20) == 0))) {
                        B_800F48C4[i] |= mask;
                    }
                } else {
                    B_80113670[i][j] = 0;
                }
            }
        }

        B_800F3E64[i] = B_800EBCF8[i];
    }
}

void func_8002A8F8(u16 mask, u8 index) {
    s32 var_a0 = mask;
    s32 j;

    for (j = ARRAY_COUNT(*B_80113670) - 1; j >= 0; j--) {
        if (var_a0 & 1) {
            break;
        }

        var_a0 >>= 1;
    }
    B_80113670[index][j] = B_800EF554 + B_800F1E20 - 1;
}

/**
 * Returns the amount of connected controllers
 */
s32 func_8002A954(void) {
    s32 connectedControllers = 0;
    OSContStatus padStatus[MAXCONTROLLERS];
    s8 var_a2;
    s8 i;

    osContStartQuery(&B_800F3E38);
    osRecvMesg(&B_800F3E38, NULL, OS_MESG_BLOCK);
    osContGetQuery(padStatus);

    for (i = 0; i < 4; i++) {
        B_800EBD16[i] = 4;
    }

    var_a2 = 0;
    for (i = 0; i < 4; i++) {
        B_800F3E78[i] = 0;
        switch (padStatus[i].errno) {
            case CONT_NO_RESPONSE_ERROR:
                break;

            default:
                if ((padStatus[i].type & CONT_TYPE_MASK) == CONT_TYPE_NORMAL) {
                    B_800F3E78[i] = 1;
                    B_800EBD16[var_a2] = i;
                    connectedControllers++;
                    var_a2++;
                }
        }
    }

    return connectedControllers;
}

/**
 * Original filename: msgwnd.c
 */

#include "ultra64.h"
#include "include_asm.h"
#include "macros_defines.h"
#include "unknown_structs.h"
#include "unk.h"
#include "main_segment_functions.h"
#include "main_segment_variables.h"
#include "gcc/memory.h"

INCLUDE_RODATA("asm/nonmatchings/main_segment/msgwnd", RO_800B1990);

bool func_8005CF20(s32 arg0, u32 buttonMask) {
    s32 i = 0;

    while (i < 4) {
        if ((arg0 >> i) & 1) {
            if (gControllerPressedButtons[B_800EBD16[i]] & buttonMask) {
                break;
            }
        }
        i++;
    }
    return i < 4;
}

/**
 * Original name: msgWnd_init
 */
INCLUDE_ASM("asm/nonmatchings/main_segment/msgwnd", msgWnd_init);

/**
 * Original name: msgWnd_init2
 */
INCLUDE_ASM("asm/nonmatchings/main_segment/msgwnd", msgWnd_init2);

/**
 * Original name: msgWnd_clear
 */
INCLUDE_ASM("asm/nonmatchings/main_segment/msgwnd", msgWnd_clear);

/**
 * Original name: msgWnd_layout
 */
INCLUDE_ASM("asm/nonmatchings/main_segment/msgwnd", msgWnd_layout);

#ifdef NON_MATCHING
void msgWnd_layout(void *, void *); /* extern */

/**
 * Original name: msgWnd_addStr
 */
void msgWnd_addStr(MessageWnd *messageWnd, const char *arg1) {
    s32 temp_a1;
    s32 temp_s1;
    s32 var_s2;
    char *temp_a1_2;

    temp_s1 = func_8005B858(messageWnd->unk_0C + messageWnd->unk_14);

    var_s2 = func_8005B858(arg1);
    if (messageWnd->unk_10 < (temp_s1 + var_s2 + 2)) {
        var_s2 = (messageWnd->unk_10 - temp_s1) - 2;
    }

    memmove(messageWnd->unk_0C, messageWnd->unk_0C + messageWnd->unk_14, temp_s1);

    messageWnd->unk_18 -= messageWnd->unk_14;
    messageWnd->unk_14 = 0;
    memmove(messageWnd->unk_0C + temp_s1, (void *)arg1, var_s2);
    temp_a1 = temp_s1 + var_s2;
    messageWnd->unk_0C[temp_a1] = 0x7E;
    temp_a1_2 = temp_a1 + messageWnd->unk_0C;
    temp_a1_2[1] = 0x7A;
    messageWnd->unk_60 = 0;
    msgWnd_layout(messageWnd, temp_a1_2);
}
#else
INCLUDE_ASM("asm/nonmatchings/main_segment/msgwnd", msgWnd_addStr);
#endif

INCLUDE_ASM("asm/nonmatchings/main_segment/msgwnd", func_8005D3F8);

/**
 * Original name: msgWnd_update
 */
INCLUDE_ASM("asm/nonmatchings/main_segment/msgwnd", msgWnd_update);

INCLUDE_RODATA("asm/nonmatchings/main_segment/msgwnd", D_800B1A54);

/**
 * Original name: msgWnd_draw
 */
INCLUDE_ASM("asm/nonmatchings/main_segment/msgwnd", msgWnd_draw);

/**
 * Original name: msgWnd_isEnd
 */
INCLUDE_ASM("asm/nonmatchings/main_segment/msgwnd", msgWnd_isEnd);

/**
 * Original name: msgWnd_skip
 */
INCLUDE_ASM("asm/nonmatchings/main_segment/msgwnd", msgWnd_skip);

/**
 * Original name: msgWnd_isSpeaking
 */
INCLUDE_ASM("asm/nonmatchings/main_segment/msgwnd", msgWnd_isSpeaking);

/**
 * Original name: msgWnd_isScroll
 */
INCLUDE_ASM("asm/nonmatchings/main_segment/msgwnd", msgWnd_isScroll);

/**
 * Original name: msgWnd_getWidth
 */
INCLUDE_ASM("asm/nonmatchings/main_segment/msgwnd", msgWnd_getWidth);

/**
 * Original name: msgWnd_getHeight
 */
INCLUDE_ASM("asm/nonmatchings/main_segment/msgwnd", msgWnd_getHeight);

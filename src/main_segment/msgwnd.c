/**
 * Original filename: msgwnd.c
 */

#include "msgwnd.h"

#include "include_asm.h"
#include "macros_defines.h"
#include "unknown_structs.h"
#include "unk.h"
#include "main_segment_variables.h"
#include "gcc/memory.h"
#include "tex_func.h"
#include "font.h"

/**
 * Original name: _msgColorTbl
 */
const Color_RGB8 sMessageColorTable[] = {
    /* 0 */ { 0, 0, 0 },       // Black
    /* 1 */ { 0, 0, 255 },     // Blue
    /* 2 */ { 0, 200, 0 },     // Green
    /* 3 */ { 0, 200, 200 },   // Cyan
    /* 4 */ { 220, 50, 0 },    // Orange
    /* 5 */ { 210, 0, 210 },   // Magenta
    /* 6 */ { 220, 140, 0 },   // Orange 2
    /* 7 */ { 255, 255, 255 }, // White
};

#if VERSION_US || VERSION_CN
bool func_8005CF20(s32 arg0, u32 buttonMask) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if ((arg0 >> i) & 1) {
            if (gControllerPressedButtons[main_joy[i]] & buttonMask) {
                break;
            }
        }
    }
    return i < 4;
}
#endif

#if VERSION_US || VERSION_CN
/**
 * Original name: msgWnd_init
 */
void msgWnd_init(MessageWnd *messageWnd, UNK_PTR *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    uintptr_t temp_t1;
    u32 temp;

    temp_t1 = (uintptr_t)*arg1;
    temp = 0x400;
    temp -= ALIGN16(temp_t1) - temp_t1;
    temp -= ((arg3 + 1) * sizeof(MessageWnd_unk_04));
    msgWnd_init2(messageWnd, arg1, temp, arg2, arg3, arg4, arg5);
}
#endif

#if VERSION_US || VERSION_CN
/**
 * Original name: msgWnd_init2
 */
void msgWnd_init2(MessageWnd *messageWnd, UNK_PTR *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    unsigned char *temp;

    messageWnd->unk_00 = *arg1;
    messageWnd->unk_04 = ALIGN_PTR(messageWnd->unk_00);

    messageWnd->unk_08 = (arg4 + 1);
    temp = (void *)((uintptr_t)messageWnd->unk_04 + ((arg4 + 1) * sizeof(MessageWnd_unk_04)));
    messageWnd->unk_0C = temp;

    messageWnd->unk_10 = arg2;
    messageWnd->unk_1C = 1;
    messageWnd->unk_20 = 0;
    messageWnd->unk_24 = 0;
    messageWnd->unk_28 = arg5;
    messageWnd->unk_2C = arg6;
    messageWnd->unk_30 = 0xC;
    messageWnd->unk_34 = 0xC;
    messageWnd->unk_38 = arg3;
    messageWnd->unk_38 = arg3;
    messageWnd->unk_38 = arg3 * 2;
    messageWnd->unk_3C = 6;
    messageWnd->unk_44 = arg4;
    messageWnd->unk_48 = 0xE;
    messageWnd->unk_54 = 0.25f;
    messageWnd->unk_5C = 0.125f;
    messageWnd->unk_74 = 0xFF;
    messageWnd->unk_78 = 1;

    temp = &messageWnd->unk_0C[arg2];
    *arg1 = temp;

    msgWnd_clear(messageWnd);
}
#endif

/**
 * Original name: msgWnd_clear
 */
#if VERSION_US || VERSION_CN
void msgWnd_clear(MessageWnd *messageWnd) {
    messageWnd->unk_0C[0] = '~';
    messageWnd->unk_0C[1] = 'z';
    messageWnd->unk_14 = 0;
    messageWnd->unk_18 = 0;
    messageWnd->column = 0;
    messageWnd->line = 0;
    messageWnd->unk_50 = 0.0f;
    messageWnd->unk_58 = 0;
    messageWnd->hasEnded = false;
    messageWnd->isSpeaking = false;
    messageWnd->color = MSGWND_COLOR_WHITE;
    messageWnd->unk_6C = 0;
    messageWnd->timer = 0;
    messageWnd->unk_7C = 0;
}
#endif

#if VERSION_US || VERSION_CN
/**
 * Original name: msgWnd_layout
 */
void msgWnd_layout(MessageWnd *messageWnd) {
    bool keepGoing = true;
    s32 var_s5 = 0;
    s32 var_s6 = 0;
    s32 var_s3 = messageWnd->unk_14;
    s32 sp18 = (messageWnd->unk_3C * 2) - messageWnd->unk_30;
    s32 width = msgWnd_getWidth(messageWnd);
    f32 temp_fs0 = messageWnd->unk_30 / 12.0f;
    s32 color = messageWnd->color;

    messageWnd->unk_04->unk_0 = var_s3;
    messageWnd->unk_04->color = color;

    while (keepGoing) {
        s32 var_s1 = false;

        if (messageWnd->unk_0C[var_s3] == '~') {
            switch (messageWnd->unk_0C[var_s3 + 1]) {
                case 'w':
                    break;

                case 'h':
                    var_s1 = true;
                    break;

                case 'm':
                    var_s1 = (var_s5 + messageWnd->unk_3C);
                    var_s1 = width < var_s1;
                    break;

                case 'z':
                    var_s1 = true;
                    keepGoing = false;
                    break;

                case 'n':
                    var_s1 = true;
                    break;

                default:
                    color = messageWnd->unk_0C[var_s3 + 1] - '0';
                    break;
            }

            var_s3 += fontStr_nextChar(&messageWnd->unk_0C[var_s3]);
        } else {
            s32 temp = fontStr_charSize(&messageWnd->unk_0C[var_s3], messageWnd->unk_20) * temp_fs0 + sp18;
            s32 temp_s0 = var_s5 + temp;

            if (width >= temp_s0) {
                var_s3 += fontStr_nextChar(&messageWnd->unk_0C[var_s3]);
            }
            if (temp_s0 >= width) {
                var_s1 = true;
            }
            if (width >= temp_s0) {
                var_s5 = temp_s0;
            }
        }

        if (var_s1) {
            messageWnd->unk_04[var_s6].unk_4 = var_s3;
            messageWnd->unk_04[var_s6].unk_8 = var_s5;
            var_s5 = 0;

            var_s6++;
            if (var_s6 < messageWnd->unk_08) {
                messageWnd->unk_04[var_s6].unk_0 = var_s3;
                messageWnd->unk_04[var_s6].color = color;
            } else {
                keepGoing = false;
            }
        }
    }
}
#endif

#if VERSION_US || VERSION_CN
void msgWnd_addStr(MessageWnd *messageWnd, const char *arg1) {
    s32 length1 = fontStr_length(&messageWnd->unk_0C[messageWnd->unk_14]);
    s32 length2;

    length2 = fontStr_length(arg1);
    if (messageWnd->unk_10 < (length1 + length2 + 2)) {
        length2 = (messageWnd->unk_10 - length1) - 2;
    }

    memmove(messageWnd->unk_0C, &messageWnd->unk_0C[messageWnd->unk_14], length1);

    messageWnd->unk_18 -= messageWnd->unk_14;
    messageWnd->unk_14 = 0;

    memmove(&messageWnd->unk_0C[length1], (void *)arg1, length2);

    messageWnd->unk_0C[length1 + length2] = '~';
    messageWnd->unk_0C[length1 + length2 + 1] = 'z';

    messageWnd->hasEnded = false;
    msgWnd_layout(messageWnd);
}
#endif

#if VERSION_US || VERSION_CN
void func_8005D3F8(MessageWnd *messageWnd) {
    messageWnd->unk_14 = messageWnd->unk_04[1].unk_0;
    messageWnd->color = messageWnd->unk_04[1].color;

    msgWnd_layout(messageWnd);
}
#endif

#if VERSION_US || VERSION_CN
/**
 * Original name: msgWnd_update
 */
void msgWnd_update(MessageWnd *messageWnd) {
    s32 temp_s2 = messageWnd->unk_3C * 2 - messageWnd->unk_30;
    s32 width = msgWnd_getWidth(messageWnd);
    f32 temp_fs0 = messageWnd->unk_30 / 12.0f;

    if ((messageWnd->unk_6C == 0) && func_8005CF20(messageWnd->unk_1C, A_BUTTON | B_BUTTON | START_BUTTON)) {
        msgWnd_skip(messageWnd);
    }

    if (messageWnd->unk_58 > 0.0) {
        messageWnd->unk_58 -= messageWnd->unk_5C;
        if (messageWnd->unk_58 > 0.0) {
            return;
        }

        messageWnd->line--;
        func_8005D3F8(messageWnd);
    }

    if (messageWnd->line >= messageWnd->unk_44) {
        messageWnd->unk_58 += 1.0;
        return;
    }

    messageWnd->unk_58 = 0;
    if (messageWnd->unk_6C != 0) {
        messageWnd->timer = 0;
        if (func_8005CF20(messageWnd->unk_1C, A_BUTTON | B_BUTTON | START_BUTTON)) {
            messageWnd->unk_6C = 0;
        }
        return;
    }

    if (messageWnd->timer > 0) {
        messageWnd->timer--;
        return;
    }

    messageWnd->unk_50 += messageWnd->unk_54;
    while (messageWnd->unk_50 >= 1.0) {
        if (messageWnd->unk_0C[messageWnd->unk_18] == '~') {
            switch (messageWnd->unk_0C[messageWnd->unk_18 + 1]) {
                case 'w':
                    messageWnd->timer = (messageWnd->unk_0C[messageWnd->unk_18 + 2] - '0') * 60;
                    messageWnd->unk_50 = 0.0f;
                    break;

                case 'h':
                    messageWnd->unk_50 = 0.0f;
                    messageWnd->column = 0;
                    messageWnd->line = 0;
                    messageWnd->unk_14 = messageWnd->unk_18 + fontStr_nextChar(&messageWnd->unk_0C[messageWnd->unk_18]);
                    msgWnd_layout(messageWnd);
                    break;

                case 'm':
                    messageWnd->unk_6C = 1;
                    messageWnd->unk_50 = 0.0f;
                    if (width < (messageWnd->column + messageWnd->unk_3C)) {
                        messageWnd->column = 0;
                        messageWnd->line++;
                    }
                    break;

                case 'n':
                    messageWnd->column = 0;
                    messageWnd->line++;
                    break;

                case 'z':
                    messageWnd->hasEnded = true;
                    messageWnd->unk_50 = 0.0f;
                    break;
            }

            messageWnd->unk_18 += fontStr_nextChar(messageWnd->unk_0C + messageWnd->unk_18);
            messageWnd->isSpeaking = false;
        } else {
            messageWnd->column +=
                fontStr_charSize(&messageWnd->unk_0C[messageWnd->unk_18], messageWnd->unk_20) * temp_fs0 + temp_s2;

            if (width >= messageWnd->column) {
                messageWnd->unk_18 += fontStr_nextChar(&messageWnd->unk_0C[messageWnd->unk_18]);
                messageWnd->unk_50 -= 1.0;
            }

            if (messageWnd->column >= width) {
                messageWnd->column = 0;
                messageWnd->line++;
            }

            messageWnd->isSpeaking = true;
        }
    }
}
#endif

ASM_RODATA;
const char STR_800B1A54[] = "▼";

#if VERSION_US
#ifdef NON_EQUIVALENT
/**
 * Original name: msgWnd_draw
 */
void msgWnd_draw(MessageWnd *messageWnd, Gfx **gfxP) {
    Gfx *gfx;
    s32 sp2C;
    s32 sp34;
    // Gfx *temp_a2;
    // Gfx *temp_a2_2;
    // Gfx *temp_v1;
    // Gfx *temp_v1_4;
    f32 var_f20;
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_a0_5;
    s32 temp_a0_6;
    s32 temp_s4;
    s32 temp_s5;
    s32 messageWidth; // temp_s6;
    s32 temp_v0;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 var_a2;
    s32 var_fp;
    s32 var_s0;
    s32 var_s2;
    s32 var_s3;
    s32 var_s7;

    gfx = *gfxP;

    sp2C = (messageWnd->unk_3C * 2) - messageWnd->unk_30;
    temp_a0 = messageWnd->unk_30;
    var_s7 = messageWnd->color;
    messageWidth = msgWnd_getWidth(messageWnd);
    sp34 = (temp_a0 * 0xA) / 12;

    if (messageWnd->unk_20 != 0) {
        font16_initDL2(&gfx);
    } else {
        font16_initDL(&gfx);
    }

    if (messageWnd->unk_78 != 0) {
        gfxSetScissor(&gfx, 2, messageWnd->unk_28, messageWnd->unk_2C, msgWnd_getWidth(messageWnd),
                      msgWnd_getHeight(messageWnd));
    }

    var_s0 = messageWnd->unk_14;
    var_s2 = 0;
    var_fp = messageWnd->unk_44;
    var_f20 = 0.0f;
    var_s3 = 0;
    if (messageWnd->unk_58 > 0.0) {
        var_fp += 1;
        var_f20 = (1.0 - messageWnd->unk_58) * messageWnd->unk_48;
    }
    // temp_a0_2 = var_s7 * 3;
    // temp_a2 = gfx;
    // gfx = temp_a2 + 8;
    // temp_a2->words.w0 = 0xFA000000;
    // temp_a2->words.w1 = (sMessageColorTable[var_s7].unk_0 << 0x18) | (*(&sMessageColorTable->unk_1 + temp_a0_2) <<
    // 0x10) | (*(&sMessageColorTable->unk_2 + temp_a0_2) << 8) | (u8)messageWnd->unk_74;
    gDPSetPrimColor(gfx++, 0, 0, sMessageColorTable[var_s7].r, sMessageColorTable[var_s7].g,
                    sMessageColorTable[var_s7].b, messageWnd->unk_74);

    if ((messageWnd->unk_30 == 0xC) || (messageWnd->unk_34 != 0xC) || (var_f20 != 0.0f)) {
        // temp_v1 = gfx;
        // gfx = temp_v1 + 8;
        // temp_v1->words.w0 = 0xE3001201;
        // temp_v1->words.w1 = 0x2000;
        gDPSetTextureFilter(gfx++, G_TF_BILERP);
    }

    do {
        if (var_s0 >= messageWnd->unk_18) {
            break;
        }

        if (messageWnd->unk_0C[var_s0] == '~') {
            switch (messageWnd->unk_0C[var_s0 + 1]) {
                case 'w':
                    break;

                case 'h':
                    var_s2 = 0;
                    var_s3 = 0;
                    break;

                case 'm':
                    if (messageWidth >= (var_s2 + messageWnd->unk_3C)) {
                        break;
                    }
                    /* Fallthrough */
                case 'n':
                    var_s2 = 0;
                    var_s3 += 1;
                    break;

                default:
                    var_s7 = messageWnd->unk_0C[var_s0 + 1] - '0';
                    // temp_a0_5 = var_s7 * 3;
                    // temp_a2_2 = gfx;
                    // gfx = temp_a2_2 + 8;
                    // temp_a2_2->words.w0 = 0xFA000000;
                    // temp_a2_2->words.w1 = (sMessageColorTable[var_s7].unk_0 << 0x18) | (*(&sMessageColorTable->unk_1
                    // + temp_a0_5) << 0x10) |
                    // (*(&sMessageColorTable->unk_2 + temp_a0_5) << 8) | (u8)messageWnd->unk_74;
                    gDPSetPrimColor(gfx++, 0, 0, sMessageColorTable[var_s7].r, sMessageColorTable[var_s7].g,
                                    sMessageColorTable[var_s7].b, messageWnd->unk_74);
                    break;
            }

            var_s0 += fontStr_nextChar(&messageWnd->unk_0C[var_s0]);
        } else {
            temp_s4 = fontStr_nextChar(&messageWnd->unk_0C[var_s0]);
            temp_s5 = (s32)(
                ((f32)fontStr_charSize(&messageWnd->unk_0C[var_s0], messageWnd->unk_20) * ((f32)temp_a0 / 12.0f)) +
                (f32)sp2C);
            if (messageWnd->unk_24 != 0) {
#if 1
                var_a2 = (s32)(messageWidth - ((u32 *)((var_s3 * 0x10) + messageWnd->unk_04))[0x8 / 4]) >> 1;
#endif
            } else {
                var_a2 = 0;
            }

            switch (temp_s4) {
                case 1:
                    if (messageWidth >= (var_s2 + temp_s5)) {
                        switch (messageWnd->unk_20) {
                            case 0:
                                fontAsc_draw(
                                    &gfx, (f32)(messageWnd->unk_28 + var_s2 + var_a2),
                                    (f32)(s32)((f32)(messageWnd->unk_2C + (var_s3 * messageWnd->unk_48)) - var_f20),
                                    (f32)sp34, (f32)messageWnd->unk_34, &messageWnd->unk_0C[var_s0]);
                                break;

                            case 1:
                                if (messageWnd->unk_20 == temp_s4) {
                                    fontAsc_draw2(
                                        &gfx, (f32)(messageWnd->unk_28 + var_s2 + var_a2),
                                        (f32)(s32)((f32)(messageWnd->unk_2C + (var_s3 * messageWnd->unk_48)) - var_f20),
                                        (f32)sp34, (f32)messageWnd->unk_34, &messageWnd->unk_0C[var_s0]);
                                }
                                break;
                        }

                        var_s0 += temp_s4;
                    }
                    var_s2 += temp_s5;
                    break;

                case 2:
                    if (messageWidth >= (var_s2 + temp_s5)) {
                        switch (messageWnd->unk_20) {
                            case 0:
                                fontXX_draw(
                                    &gfx, (f32)(messageWnd->unk_28 + var_s2 + var_a2),
                                    (f32)(s32)((f32)(messageWnd->unk_2C + (var_s3 * messageWnd->unk_48)) - var_f20),
                                    (f32)messageWnd->unk_30, (f32)messageWnd->unk_34, &messageWnd->unk_0C[var_s0]);
                                break;
                            case 1:
                                fontXX_draw2(
                                    &gfx, (f32)(messageWnd->unk_28 + var_s2 + var_a2),
                                    (f32)(s32)((f32)(messageWnd->unk_2C + (var_s3 * messageWnd->unk_48)) - var_f20),
                                    (f32)messageWnd->unk_30, (f32)messageWnd->unk_34, &messageWnd->unk_0C[var_s0]);
                                break;

                            default:
                                break;
                        }

                        var_s0 += temp_s4;
                    }
                    var_s2 += temp_s5;
                    break;

                default:
                    break;
            }

            if (var_s2 >= messageWidth) {
                var_s2 = 0;
                var_s3 += 1;
            }
        }
    } while (var_s3 < var_fp);

    if ((messageWnd->unk_6C != false) && (messageWnd->unk_58 == 0.0)) {
        temp_a0_6 =
            (s32)(((f32)sins((messageWnd->unk_7C << 0xA) & 0xFC00) * 0.001953125f) + 191.0f) * messageWnd->unk_74;
        // temp_v1_2 = var_s7 * 3;
        // gfx->words.w0 = 0xFA000000;
        // gfx->words.w1 = (sMessageColorTable[var_s7].unk_0 << 0x18) | (*(&sMessageColorTable->unk_1 + temp_v1_2) <<
        // 0x10) | (*(&sMessageColorTable->unk_2 + temp_v1_2) << 8) | ((temp_a0_6 >> 8) & 0xFF); gfx += 8;
        gDPSetPrimColor(gfx++, 0, 0, sMessageColorTable[var_s7].r, sMessageColorTable[var_s7].g,
                        sMessageColorTable[var_s7].b, temp_a0_6 >> 8);

        switch (messageWnd->unk_20) {
            case 0x0:
                fontXX_draw(&gfx, (f32)(messageWnd->unk_28 + (var_s2 * messageWnd->unk_3C)),
                            (f32)(s32)((f32)(messageWnd->unk_2C + (var_s3 * messageWnd->unk_48)) - var_f20),
                            (f32)messageWnd->unk_30, (f32)messageWnd->unk_34, STR_800B1A54);
                break;
            case 0x1:
                fontXX_draw2(&gfx, (f32)(messageWnd->unk_28 + (var_s2 * messageWnd->unk_3C)),
                             (f32)(s32)((f32)(messageWnd->unk_2C + (var_s3 * messageWnd->unk_48)) - var_f20),
                             (f32)messageWnd->unk_30, (f32)messageWnd->unk_34, STR_800B1A54);
                break;

            default:
                break;
        }
    }
    // gfx->words.w0 = 0xED000000;
    // gfx->words.w1 = 0x4F0000 | 0xC3BC;
    // temp_v1_4 = gfx + 8;
    // gfx = temp_v1_4;
    gDPSetScissor(gfx++, G_SC_NON_INTERLACE, 0, 0, 319, 239);
    messageWnd->unk_7C += 1;
    *gfxP = gfx;
}
#else
INCLUDE_ASM("asm/us/nonmatchings/main_segment/msgwnd", msgWnd_draw);
#endif
#endif

#if VERSION_CN
#ifdef NON_MATCHING
STATIC_INLINE s32 inlined_func(MessageWnd *messageWnd, s32 var_s3, f32 var_fs0) {
    return messageWnd->unk_2C + var_s3 * messageWnd->unk_48 - var_fs0;
}

// regalloc
void msgWnd_draw(MessageWnd *messageWnd, Gfx **gfxP) {
    Gfx *gfx;
    s32 sp24;
    s32 sp28;
    s32 sp2C;
    f32 var_fs0;
    s32 temp_s4;
    s32 temp_s5;
    s32 temp_s6;
    s32 var_a1;
    s32 var_s0;
    s32 var_s2;
    s32 var_s3;
    s32 var_s7;
    f32 new_var2;

    gfx = *gfxP;

    sp28 = (messageWnd->unk_3C * 2) - messageWnd->unk_30;
    temp_s6 = msgWnd_getWidth(messageWnd);
    sp2C = (messageWnd->unk_30 * 0xA) / 12;
    new_var2 = messageWnd->unk_30 / 12.0f;
    var_s7 = messageWnd->color;

    if (messageWnd->unk_20 != 0) {
        font16_initDL2(&gfx);
    } else {
        font16_initDL(&gfx);
    }

    if (messageWnd->unk_78 != 0) {
        gfxSetScissor(&gfx, 2, messageWnd->unk_28, messageWnd->unk_2C, msgWnd_getWidth(messageWnd),
                      msgWnd_getHeight(messageWnd));
    }

    var_s0 = messageWnd->unk_14;
    var_s2 = 0;

    sp24 = messageWnd->unk_44;
    var_fs0 = 0.0f;
    var_s3 = 0;
    if (messageWnd->unk_58 > 0.0) {
        sp24 = messageWnd->unk_44 + 1;
        var_fs0 = (1.0 - messageWnd->unk_58) * messageWnd->unk_48;
    }

    gDPSetPrimColor(gfx++, 0, 0, sMessageColorTable[var_s7].r, sMessageColorTable[var_s7].g,
                    sMessageColorTable[var_s7].b, messageWnd->unk_74);

    if ((messageWnd->unk_30 != 0xC) || (messageWnd->unk_34 != messageWnd->unk_30) || (var_fs0 != 0.0f)) {
        gDPSetTextureFilter(gfx++, G_TF_BILERP);
    }

    while (var_s0 < messageWnd->unk_18) {
        if (messageWnd->unk_0C[var_s0] == 0x7E) {
            switch (messageWnd->unk_0C[var_s0 + 1]) {
                case 0x6E:
                    var_s2 = 0;
                    var_s3 += 1;
                    break;

                case 0x6D:
                    if (temp_s6 < (var_s2 + messageWnd->unk_3C)) {
                        var_s2 = 0;
                        var_s3 += 1;
                    }
                    break;

                case 0x77:
                    break;

                case 0x68:
                    var_s2 = 0;
                    var_s3 = 0;
                    break;

                default:
                    var_s7 = messageWnd->unk_0C[var_s0 + 1] - 0x30;
                    gDPSetPrimColor(gfx++, 0, 0, sMessageColorTable[var_s7].r, sMessageColorTable[var_s7].g,
                                    sMessageColorTable[var_s7].b, messageWnd->unk_74);
                    break;
            }

            var_s0 += fontStr_nextChar(&messageWnd->unk_0C[var_s0]);
        } else {
            temp_s5 = fontStr_nextChar(&messageWnd->unk_0C[var_s0]);

            temp_s4 = fontStr_charSize(&messageWnd->unk_0C[var_s0], messageWnd->unk_20) * new_var2 + sp28;

            var_a1 = (messageWnd->unk_24 != 0) ? (temp_s6 - messageWnd->unk_04[var_s3].unk_8) >> 1 : 0;

            switch (temp_s5) {
                case 1:
                    if (temp_s6 >= var_s2 + temp_s4) {
                        switch (messageWnd->unk_20) {
                            case 0:
                                fontAsc_draw(&gfx, messageWnd->unk_28 + var_s2 + var_a1,
                                             inlined_func(messageWnd, var_s3, var_fs0), sp2C, messageWnd->unk_34,
                                             &messageWnd->unk_0C[var_s0]);
                                break;

                            case 1:
                                fontAsc_draw2(&gfx, messageWnd->unk_28 + var_s2 + var_a1,
                                              inlined_func(messageWnd, var_s3, var_fs0), sp2C, messageWnd->unk_34,
                                              &messageWnd->unk_0C[var_s0]);
                                break;
                        }
                        var_s0 += temp_s5;
                    }
                    var_s2 += temp_s4;
                    break;

                case 2:
                    if (temp_s6 >= (var_s2 + temp_s4)) {
                        switch (messageWnd->unk_20) {
                            case 0:
                                fontXX_draw(&gfx, messageWnd->unk_28 + var_s2 + var_a1,
                                            inlined_func(messageWnd, var_s3, var_fs0), messageWnd->unk_30,
                                            messageWnd->unk_34, &messageWnd->unk_0C[var_s0]);
                                break;

                            case 1:
                                fontXX_draw2(&gfx, messageWnd->unk_28 + var_s2 + var_a1,
                                             inlined_func(messageWnd, var_s3, var_fs0), messageWnd->unk_30,
                                             messageWnd->unk_34, &messageWnd->unk_0C[var_s0]);
                                break;
                        }

                        var_s0 += temp_s5;
                    }
                    var_s2 += 2 + temp_s4;
                    break;
            }

            if (var_s2 >= temp_s6) {
                var_s2 = 0;
                var_s3 += 1;
            }
        }

        if (var_s3 >= sp24) {
            break;
        }
    }

    if ((messageWnd->unk_6C != 0) && (messageWnd->unk_58 == 0.0)) {
        s32 temp;

        temp = sins((messageWnd->unk_7C << 10) & 0xFC00) * (1.0f / 0x200) + 191.0f;
        temp = (temp * messageWnd->unk_74) >> 8;

        gDPSetPrimColor(gfx++, 0, 0, sMessageColorTable[var_s7].r, sMessageColorTable[var_s7].g,
                        sMessageColorTable[var_s7].b, temp);

        switch (messageWnd->unk_20) {
            case 0:
                fontXX_draw(&gfx, messageWnd->unk_28 + var_s2 * messageWnd->unk_3C,
                            inlined_func(messageWnd, var_s3, var_fs0), messageWnd->unk_30, messageWnd->unk_34,
                            STR_800B1A54);
                break;

            case 1:
                fontXX_draw2(&gfx, messageWnd->unk_28 + var_s2 * messageWnd->unk_3C,
                             inlined_func(messageWnd, var_s3, var_fs0), messageWnd->unk_30, messageWnd->unk_34,
                             STR_800B1A54);
                break;
        }
    }

    gDPSetScissor(gfx++, G_SC_NON_INTERLACE, 0, 0, 319, 239);

    messageWnd->unk_7C += 1;

    *gfxP = gfx;
}
#else
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/msgwnd", msgWnd_draw);
#endif
#endif

#if VERSION_US || VERSION_CN
/**
 * Original name: msgWnd_isEnd
 */
bool msgWnd_isEnd(MessageWnd *messageWnd) {
    return messageWnd->hasEnded;
}
#endif

#if VERSION_US || VERSION_CN
/**
 * Original name: msgWnd_skip
 */
void msgWnd_skip(MessageWnd *messageWnd) {
    messageWnd->unk_50 = messageWnd->unk_10;
    messageWnd->timer = 0;
}
#endif

#if VERSION_US || VERSION_CN
/**
 * Original name: msgWnd_isSpeaking
 */
bool msgWnd_isSpeaking(MessageWnd *messageWnd) {
    return messageWnd->isSpeaking;
}
#endif

/**
 * Original name: msgWnd_isScroll
 */
#if VERSION_US || VERSION_CN
bool msgWnd_isScroll(MessageWnd *messageWnd) {
    return messageWnd->line >= messageWnd->unk_44;
}
#endif

/**
 * Original name: msgWnd_getWidth
 */
#if VERSION_US || VERSION_CN
s32 msgWnd_getWidth(MessageWnd *messageWnd) {
    return messageWnd->unk_38 * messageWnd->unk_3C;
}
#endif

/**
 * Original name: msgWnd_getHeight
 */
#if VERSION_US || VERSION_CN
s32 msgWnd_getHeight(MessageWnd *messageWnd) {
    return messageWnd->unk_44 * messageWnd->unk_48;
}
#endif

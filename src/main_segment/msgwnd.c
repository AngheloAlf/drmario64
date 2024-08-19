/**
 * Original filename: msgwnd.c
 */

#include "msgwnd.h"

#include "macros_defines.h"
#include "unknown_structs.h"
#include "unk.h"
#include "main_segment_variables.h"

#include "gcc/memory.h"

#include "font.h"
#include "joy.h"
#include "tex_func.h"

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

/**
 * Original name: msgWnd_init
 */
void msgWnd_init(MessageWnd *messageWnd, void **heapP, s32 arg2, s32 arg3, s32 xPos, s32 yPos) {
    void *heap = *heapP;
    u32 temp;

    temp = 0x400;
    temp -= ALIGN16((uintptr_t)heap) - (uintptr_t)heap;
    temp -= ((arg3 + 1) * sizeof(MessageWnd_unk_04));
    msgWnd_init2(messageWnd, heapP, temp, arg2, arg3, xPos, yPos);
}

/**
 * Original name: msgWnd_init2
 */
void msgWnd_init2(MessageWnd *messageWnd, void **heapP, s32 arg2, s32 arg3, s32 arg4, s32 xPos, s32 yPos) {
    void *heap;

    heap = messageWnd->heap = *heapP;
    messageWnd->unk_04 = ALIGN_PTR(heap);

    messageWnd->unk_08 = arg4 + 1;
    heap = (void *)((uintptr_t)messageWnd->unk_04 + messageWnd->unk_08 * sizeof(MessageWnd_unk_04));

    messageWnd->unk_0C = heap;
    messageWnd->unk_10 = arg2;
    heap = (void *)((uintptr_t)messageWnd->unk_0C + arg2);

    messageWnd->unk_1C = 1;
    messageWnd->unk_20 = 0;
    messageWnd->unk_24 = 0;
    messageWnd->xPos = xPos;
    messageWnd->yPos = yPos;
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
    messageWnd->alpha = 255;
    messageWnd->unk_78 = true;

    *heapP = heap;

    msgWnd_clear(messageWnd);
}

/**
 * Original name: msgWnd_clear
 */
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
    messageWnd->unk_6C = false;
    messageWnd->timer = 0;
    messageWnd->unk_7C = 0;
}

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

/**
 * Original name: msgWnd_addStr
 */
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

void func_8005D3F8(MessageWnd *messageWnd) {
    messageWnd->unk_14 = messageWnd->unk_04[1].unk_0;
    messageWnd->color = messageWnd->unk_04[1].color;

    msgWnd_layout(messageWnd);
}

/**
 * Original name: msgWnd_update
 */
void msgWnd_update(MessageWnd *messageWnd) {
    s32 temp_s2 = messageWnd->unk_3C * 2 - messageWnd->unk_30;
    s32 width = msgWnd_getWidth(messageWnd);
    f32 temp_fs0 = messageWnd->unk_30 / 12.0f;

    if (!messageWnd->unk_6C && func_8005CF20(messageWnd->unk_1C, A_BUTTON | B_BUTTON | START_BUTTON)) {
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
    if (messageWnd->unk_6C) {
        messageWnd->timer = 0;
        if (func_8005CF20(messageWnd->unk_1C, A_BUTTON | B_BUTTON | START_BUTTON)) {
            messageWnd->unk_6C = false;
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
                    messageWnd->unk_6C = true;
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

#if VERSION_US || VERSION_GW
#define MSGWND_DRAW_UNK_SPACE 0
#elif VERSION_CN
#define MSGWND_DRAW_UNK_SPACE 2
#endif

/**
 * Original name: msgWnd_draw
 */
void msgWnd_draw(MessageWnd *messageWnd, Gfx **gfxP) {
    Gfx *gfx = *gfxP;
    s32 sp24;
    s32 sp28 = (messageWnd->unk_3C * 2) - messageWnd->unk_30;
    s32 width = msgWnd_getWidth(messageWnd);
    s32 sp2C = (messageWnd->unk_30 * 0xA) / 12;
    f32 new_var2 = messageWnd->unk_30 / 12.0f;
    s32 color = messageWnd->color;
    f32 var_fs0;
    s32 charWidth;
    s32 temp_s5;
    s32 var_a1;
    s32 index;
    s32 column;
    s32 line;

    if (messageWnd->unk_20 != 0) {
        font16_initDL2(&gfx);
    } else {
        font16_initDL(&gfx);
    }

    if (messageWnd->unk_78) {
        gfxSetScissor(&gfx, GFXSETSCISSOR_INTERLACE_NO, messageWnd->xPos, messageWnd->yPos, msgWnd_getWidth(messageWnd),
                      msgWnd_getHeight(messageWnd));
    }

    index = messageWnd->unk_14;
    column = 0;

    sp24 = messageWnd->unk_44;
    var_fs0 = 0.0f;
    line = 0;
    if (messageWnd->unk_58 > 0.0) {
        sp24++;
        var_fs0 = (1.0 - messageWnd->unk_58) * messageWnd->unk_48;
    }

    gDPSetPrimColor(gfx++, 0, 0, sMessageColorTable[color].r, sMessageColorTable[color].g, sMessageColorTable[color].b,
                    messageWnd->alpha);

    if ((messageWnd->unk_30 != 0xC) || (messageWnd->unk_34 != messageWnd->unk_30) || (var_fs0 != 0.0f)) {
        gDPSetTextureFilter(gfx++, G_TF_BILERP);
    }

    while (index < messageWnd->unk_18) {
        if (messageWnd->unk_0C[index] == '~') {
            switch (messageWnd->unk_0C[index + 1]) {
                case 'n':
                    column = 0;
                    line++;
                    break;

                case 'm':
                    if (width < (column + messageWnd->unk_3C)) {
                        column = 0;
                        line++;
                    }
                    break;

                case 'w':
                    break;

                case 'h':
                    column = 0;
                    line = 0;
                    break;

                default:
                    color = messageWnd->unk_0C[index + 1] - '0';
                    gDPSetPrimColor(gfx++, 0, 0, sMessageColorTable[color].r, sMessageColorTable[color].g,
                                    sMessageColorTable[color].b, messageWnd->alpha);
                    break;
            }

            index += fontStr_nextChar(&messageWnd->unk_0C[index]);
        } else {
            temp_s5 = fontStr_nextChar(&messageWnd->unk_0C[index]);

            charWidth = fontStr_charSize(&messageWnd->unk_0C[index], messageWnd->unk_20) * new_var2 + sp28;

            var_a1 = (messageWnd->unk_24 != 0) ? (width - messageWnd->unk_04[line].unk_8) >> 1 : 0;

            switch (temp_s5) {
                case 1:
                    if (column + charWidth <= width) {
                        switch (messageWnd->unk_20) {
                            case 0:
                                fontAsc_draw(&gfx, messageWnd->xPos + column + var_a1,
                                             (s32)(messageWnd->yPos + line * messageWnd->unk_48 - var_fs0), sp2C,
                                             messageWnd->unk_34, &messageWnd->unk_0C[index]);
                                break;

                            case 1:
                                fontAsc_draw2(&gfx, messageWnd->xPos + column + var_a1,
                                              (s32)(messageWnd->yPos + line * messageWnd->unk_48 - var_fs0), sp2C,
                                              messageWnd->unk_34, &messageWnd->unk_0C[index]);
                                break;
                        }
                        index += temp_s5;
                    }
                    column += charWidth;
                    break;

                case 2:
                    if (column + charWidth <= width) {
                        switch (messageWnd->unk_20) {
                            case 0:
                                fontXX_draw(&gfx, messageWnd->xPos + column + var_a1,
                                            (s32)(messageWnd->yPos + line * messageWnd->unk_48 - var_fs0),
                                            messageWnd->unk_30, messageWnd->unk_34, &messageWnd->unk_0C[index]);
                                break;

                            case 1:
                                fontXX_draw2(&gfx, messageWnd->xPos + column + var_a1,
                                             (s32)(messageWnd->yPos + line * messageWnd->unk_48 - var_fs0),
                                             messageWnd->unk_30, messageWnd->unk_34, &messageWnd->unk_0C[index]);
                                break;
                        }
                        index += temp_s5;
                    }
                    column += MSGWND_DRAW_UNK_SPACE + charWidth;
                    break;
            }

            if (column >= width) {
                column = 0;
                line += 1;
            }
        }

        if (line >= sp24) {
            break;
        }
    }

    if (messageWnd->unk_6C && (messageWnd->unk_58 == 0.0)) {
        s32 alpha = sins(messageWnd->unk_7C << 10) * (1.0f / 0x200) + 191.0f;

        alpha = (alpha * messageWnd->alpha) >> 8;
        gDPSetPrimColor(gfx++, 0, 0, sMessageColorTable[color].r, sMessageColorTable[color].g,
                        sMessageColorTable[color].b, alpha);

        switch (messageWnd->unk_20) {
            case 0:
                fontXX_draw(&gfx, messageWnd->xPos + column * messageWnd->unk_3C,
                            (s32)(messageWnd->yPos + line * messageWnd->unk_48 - var_fs0), messageWnd->unk_30,
                            messageWnd->unk_34, "▼");
                break;

            case 1:
                fontXX_draw2(&gfx, messageWnd->xPos + column * messageWnd->unk_3C,
                             (s32)(messageWnd->yPos + line * messageWnd->unk_48 - var_fs0), messageWnd->unk_30,
                             messageWnd->unk_34, "▼");
                break;
        }
    }

    gDPSetScissor(gfx++, G_SC_NON_INTERLACE, 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1);

    messageWnd->unk_7C++;

    *gfxP = gfx;
}

/**
 * Original name: msgWnd_isEnd
 */
bool msgWnd_isEnd(MessageWnd *messageWnd) {
    return messageWnd->hasEnded;
}

/**
 * Original name: msgWnd_skip
 */
void msgWnd_skip(MessageWnd *messageWnd) {
    messageWnd->unk_50 = messageWnd->unk_10;
    messageWnd->timer = 0;
}

/**
 * Original name: msgWnd_isSpeaking
 */
bool msgWnd_isSpeaking(MessageWnd *messageWnd) {
    return messageWnd->isSpeaking;
}

/**
 * Original name: msgWnd_isScroll
 */
bool msgWnd_isScroll(MessageWnd *messageWnd) {
    return messageWnd->line >= messageWnd->unk_44;
}

/**
 * Original name: msgWnd_getWidth
 */
s32 msgWnd_getWidth(MessageWnd *messageWnd) {
    return messageWnd->unk_38 * messageWnd->unk_3C;
}

/**
 * Original name: msgWnd_getHeight
 */
s32 msgWnd_getHeight(MessageWnd *messageWnd) {
    return messageWnd->unk_44 * messageWnd->unk_48;
}

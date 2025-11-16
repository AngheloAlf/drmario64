/**
 * Original filename: msgwnd.c
 */

#include "msgwnd.h"

#include "alignment.h"
#include "gcc/memory.h"
#include "libc/stdint.h"
#include "macros_defines.h"

#include "color.h"
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

/**
 * Original name: _checkKeyTrg
 */
bool _checkKeyTrg(s32 contFlags, u32 buttonMask) {
    s32 i;

    for (i = 0; i < MAXCONTROLLERS; i++) {
        if ((contFlags >> i) & 1) {
            if (gControllerPressedButtons[main_joy[i]] & buttonMask) {
                break;
            }
        }
    }
    return i < MAXCONTROLLERS;
}

/**
 * Original name: msgWnd_init
 */
void msgWnd_init(MessageWnd *messageWnd, void **heapP, s32 cols, s32 rows, s32 xPos, s32 yPos) {
    void *heap = *heapP;
    s32 size;

    size = 0x40 * sizeof(MessageWndLayout);
    size -= ALIGN16((uintptr_t)heap) - (uintptr_t)heap;
    size -= ((rows + 1) * sizeof(MessageWndLayout));
    msgWnd_init2(messageWnd, heapP, size, cols, rows, xPos, yPos);
}

/**
 * Original name: msgWnd_init2
 */
void msgWnd_init2(MessageWnd *messageWnd, void **heapP, s32 bufSize, s32 cols, s32 rows, s32 xPos, s32 yPos) {
    void *heap;

    heap = messageWnd->heap = *heapP;

    messageWnd->layout = ALIGN_PTR(heap);
    messageWnd->layoutSize = rows + 1;
    heap = (void *)((uintptr_t)messageWnd->layout + messageWnd->layoutSize * sizeof(MessageWndLayout));

    messageWnd->msgBuf = heap;
    messageWnd->msgBufSize = bufSize;
    heap = (void *)((uintptr_t)messageWnd->msgBuf + bufSize);

    messageWnd->contFlags = 1 << 0;
    messageWnd->fontType = FONTTYPE_0;
    messageWnd->centering = false;
    messageWnd->posX = xPos;
    messageWnd->posY = yPos;
    messageWnd->fntW = 0xC;
    messageWnd->fntH = 0xC;
    messageWnd->colSize = cols * 2;
    messageWnd->colStep = 6;
    messageWnd->rowSize = rows;
    messageWnd->rowStep = 14;
    messageWnd->msgSpeed = 1.0f / 4;
    messageWnd->scrSpeed = 1.0f / 8;
    messageWnd->alpha = 255;
    messageWnd->scisFlag = true;

    *heapP = heap;

    msgWnd_clear(messageWnd);
}

/**
 * Original name: msgWnd_clear
 */
void msgWnd_clear(MessageWnd *messageWnd) {
    // MSG_END
    messageWnd->msgBuf[0] = '~';
    messageWnd->msgBuf[1] = 'z';

    messageWnd->msgBufTop = 0;
    messageWnd->msgBufNow = 0;
    messageWnd->colNow = 0;
    messageWnd->rowNow = 0;
    messageWnd->msgCount = 0.0f;
    messageWnd->scrCount = 0;
    messageWnd->msgIsEnd = false;
    messageWnd->isSpeak = false;
    messageWnd->topColor = MSGWND_COLOR_WHITE;
    messageWnd->keyWait = false;
    messageWnd->countWait = 0;
    messageWnd->grapCount = 0;
}

/**
 * Original name: msgWnd_layout
 */
void msgWnd_layout(MessageWnd *messageWnd) {
    bool keepGoing = true;
    s32 col = 0;
    s32 row = 0;
    s32 top = messageWnd->msgBufTop;
    s32 space = messageWnd->colStep * 2 - messageWnd->fntW;
    s32 width = msgWnd_getWidth(messageWnd);
    f32 fnt2scr = messageWnd->fntW / 12.0f;
    s32 color = messageWnd->topColor;

    messageWnd->layout[0].top = top;
    messageWnd->layout[0].color = color;

    while (keepGoing) {
        s32 layoutFlag = false;

        if (messageWnd->msgBuf[top] == '~') {
            switch (messageWnd->msgBuf[top + 1]) {
                case 'w': // MSG_WAIT
                    break;

                case 'h': // MSG_H
                    layoutFlag = true;
                    break;

                case 'm': // MSG_M
                    layoutFlag = col + messageWnd->colStep > width;
                    break;

                case 'z': // MSG_END
                    layoutFlag = true;
                    keepGoing = false;
                    break;

                case 'n': // MSG_NEWLINE
                    layoutFlag = true;
                    break;

                default: // MSG_COLOR
                    color = messageWnd->msgBuf[top + 1] - '0';
                    break;
            }

            top += fontStr_nextChar(&messageWnd->msgBuf[top]);
        } else {
            s32 step = fontStr_charSize(&messageWnd->msgBuf[top], messageWnd->fontType) * fnt2scr + space;
            s32 temp_s0 = col + step;

            if (width >= temp_s0) {
                top += fontStr_nextChar(&messageWnd->msgBuf[top]);
            }
            if (temp_s0 >= width) {
                layoutFlag = true;
            }
            if (width >= temp_s0) {
                col = temp_s0;
            }
        }

        if (layoutFlag) {
            messageWnd->layout[row].end = top;
            messageWnd->layout[row].width = col;
            col = 0;

            row++;
            if (row < messageWnd->layoutSize) {
                messageWnd->layout[row].top = top;
                messageWnd->layout[row].color = color;
            } else {
                keepGoing = false;
            }
        }
    }
}

/**
 * Original name: msgWnd_addStr
 */
void msgWnd_addStr(MessageWnd *messageWnd, const char *str) {
    s32 bufLen = fontStr_length(&messageWnd->msgBuf[messageWnd->msgBufTop]);
    s32 strLen = fontStr_length(str);

    // +2 to account for the extra MSG_END
    if (messageWnd->msgBufSize < bufLen + strLen + 2) {
        strLen = messageWnd->msgBufSize - bufLen - 2;
    }

    memmove(messageWnd->msgBuf, &messageWnd->msgBuf[messageWnd->msgBufTop], bufLen);

    messageWnd->msgBufNow -= messageWnd->msgBufTop;
    messageWnd->msgBufTop = 0;

    memmove(&messageWnd->msgBuf[bufLen], (void *)str, strLen);

    // Make sure there's an MSG_END at the end of the string
    messageWnd->msgBuf[bufLen + strLen] = '~';
    messageWnd->msgBuf[bufLen + strLen + 1] = 'z';

    messageWnd->msgIsEnd = false;
    msgWnd_layout(messageWnd);
}

void msgWnd_shiftUp(MessageWnd *messageWnd) {
    messageWnd->msgBufTop = messageWnd->layout[1].top;
    messageWnd->topColor = messageWnd->layout[1].color;

    msgWnd_layout(messageWnd);
}

/**
 * Original name: msgWnd_update
 */
void msgWnd_update(MessageWnd *messageWnd) {
    s32 space = messageWnd->colStep * 2 - messageWnd->fntW;
    s32 width = msgWnd_getWidth(messageWnd);
    f32 fnt2scr = messageWnd->fntW / 12.0f;

    if (!messageWnd->keyWait && _checkKeyTrg(messageWnd->contFlags, A_BUTTON | B_BUTTON | START_BUTTON)) {
        msgWnd_skip(messageWnd);
    }

    if (messageWnd->scrCount > 0.0) {
        messageWnd->scrCount -= messageWnd->scrSpeed;
        if (messageWnd->scrCount > 0.0) {
            return;
        }

        messageWnd->rowNow--;
        msgWnd_shiftUp(messageWnd);
    }

    if (messageWnd->rowNow >= messageWnd->rowSize) {
        messageWnd->scrCount += 1.0;
        return;
    }

    messageWnd->scrCount = 0;
    if (messageWnd->keyWait) {
        messageWnd->countWait = 0;
        if (_checkKeyTrg(messageWnd->contFlags, A_BUTTON | B_BUTTON | START_BUTTON)) {
            messageWnd->keyWait = false;
        }
        return;
    }

    if (messageWnd->countWait > 0) {
        messageWnd->countWait--;
        return;
    }

    messageWnd->msgCount += messageWnd->msgSpeed;
    while (messageWnd->msgCount >= 1.0) {
        if (messageWnd->msgBuf[messageWnd->msgBufNow] == '~') {
            switch (messageWnd->msgBuf[messageWnd->msgBufNow + 1]) {
                case 'w': // MSG_WAIT
                    messageWnd->countWait = (messageWnd->msgBuf[messageWnd->msgBufNow + 2] - '0') * 60;
                    messageWnd->msgCount = 0.0f;
                    break;

                case 'h': // MSG_H
                    messageWnd->msgCount = 0.0f;
                    messageWnd->colNow = 0;
                    messageWnd->rowNow = 0;
                    messageWnd->msgBufTop =
                        messageWnd->msgBufNow + fontStr_nextChar(&messageWnd->msgBuf[messageWnd->msgBufNow]);
                    msgWnd_layout(messageWnd);
                    break;

                case 'm': // MSG_M
                    messageWnd->keyWait = true;
                    messageWnd->msgCount = 0.0f;
                    if (width < messageWnd->colNow + messageWnd->colStep) {
                        messageWnd->colNow = 0;
                        messageWnd->rowNow++;
                    }
                    break;

                case 'n': // MSG_NEWLINE
                    messageWnd->colNow = 0;
                    messageWnd->rowNow++;
                    break;

                case 'z': // MSG_END
                    messageWnd->msgIsEnd = true;
                    messageWnd->msgCount = 0.0f;
                    break;
            }

            messageWnd->msgBufNow += fontStr_nextChar(&messageWnd->msgBuf[messageWnd->msgBufNow]);
            messageWnd->isSpeak = false;
        } else {
            messageWnd->colNow +=
                fontStr_charSize(&messageWnd->msgBuf[messageWnd->msgBufNow], messageWnd->fontType) * fnt2scr + space;

            if (width >= messageWnd->colNow) {
                messageWnd->msgBufNow += fontStr_nextChar(&messageWnd->msgBuf[messageWnd->msgBufNow]);
                messageWnd->msgCount -= DOUBLE_LITERAL(1);
            }

            if (messageWnd->colNow >= width) {
                messageWnd->colNow = 0;
                messageWnd->rowNow++;
            }

            messageWnd->isSpeak = true;
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
    s32 now;
    s32 col;
    s32 row;
    s32 rowSize;
    s32 space = messageWnd->colStep * 2 - messageWnd->fntW;
    s32 width = msgWnd_getWidth(messageWnd);
    s32 color = messageWnd->topColor;
    s32 ascFntW = (messageWnd->fntW * 0xA) / 12;
    f32 fnt2scr = messageWnd->fntW / 12.0f;
    f32 scrY;

    if (messageWnd->fontType != FONTTYPE_0) {
        font16_initDL2(&gfx);
    } else {
        font16_initDL(&gfx);
    }

    if (messageWnd->scisFlag) {
        gfxSetScissor(&gfx, GFXSETSCISSOR_INTERLACE_NO, messageWnd->posX, messageWnd->posY, msgWnd_getWidth(messageWnd),
                      msgWnd_getHeight(messageWnd));
    }

    now = messageWnd->msgBufTop;
    col = 0;

    rowSize = messageWnd->rowSize;
    scrY = 0.0f;
    row = 0;
    if (messageWnd->scrCount > 0.0) {
        rowSize++;
        scrY = (1.0 - messageWnd->scrCount) * messageWnd->rowStep;
    }

    gDPSetPrimColor(gfx++, 0, 0, sMessageColorTable[color].r, sMessageColorTable[color].g, sMessageColorTable[color].b,
                    messageWnd->alpha);

    if ((messageWnd->fntW != 0xC) || (messageWnd->fntH != messageWnd->fntW) || (scrY != 0.0f)) {
        gDPSetTextureFilter(gfx++, G_TF_BILERP);
    }

    while (now < messageWnd->msgBufNow) {
        if (messageWnd->msgBuf[now] == '~') {
            switch (messageWnd->msgBuf[now + 1]) {
                case 'n': // MSG_NEWLINE
                    col = 0;
                    row++;
                    break;

                case 'm': // MSG_M
                    if (width < (col + messageWnd->colStep)) {
                        col = 0;
                        row++;
                    }
                    break;

                case 'w': // MSG_WAIT
                    break;

                case 'h': // MSG_H
                    col = 0;
                    row = 0;
                    break;

                default: // MSG_COLOR
                    color = messageWnd->msgBuf[now + 1] - '0';
                    gDPSetPrimColor(gfx++, 0, 0, sMessageColorTable[color].r, sMessageColorTable[color].g,
                                    sMessageColorTable[color].b, messageWnd->alpha);
                    break;
            }

            now += fontStr_nextChar(&messageWnd->msgBuf[now]);
        } else {
            s32 nextChar = fontStr_nextChar(&messageWnd->msgBuf[now]);
            s32 charSize = fontStr_charSize(&messageWnd->msgBuf[now], messageWnd->fontType) * fnt2scr + space;
            s32 orgX = messageWnd->centering ? (width - messageWnd->layout[row].width) >> 1 : 0;

            switch (nextChar) {
                case 1:
                    if (col + charSize <= width) {
                        switch (messageWnd->fontType) {
                            case FONTTYPE_0:
                                fontAsc_draw(&gfx, messageWnd->posX + col + orgX,
                                             (s32)(messageWnd->posY + row * messageWnd->rowStep - scrY), ascFntW,
                                             messageWnd->fntH, &messageWnd->msgBuf[now]);
                                break;

                            case FONTTYPE_1:
                                fontAsc_draw2(&gfx, messageWnd->posX + col + orgX,
                                              (s32)(messageWnd->posY + row * messageWnd->rowStep - scrY), ascFntW,
                                              messageWnd->fntH, &messageWnd->msgBuf[now]);
                                break;

                            default:
                                break;
                        }
                        now += nextChar;
                    }
                    col += charSize;
                    break;

                case 2:
                    if (col + charSize <= width) {
                        switch (messageWnd->fontType) {
                            case FONTTYPE_0:
                                fontXX_draw(&gfx, messageWnd->posX + col + orgX,
                                            (s32)(messageWnd->posY + row * messageWnd->rowStep - scrY),
                                            messageWnd->fntW, messageWnd->fntH, &messageWnd->msgBuf[now]);
                                break;

                            case FONTTYPE_1:
                                fontXX_draw2(&gfx, messageWnd->posX + col + orgX,
                                             (s32)(messageWnd->posY + row * messageWnd->rowStep - scrY),
                                             messageWnd->fntW, messageWnd->fntH, &messageWnd->msgBuf[now]);
                                break;

                            default:
                                break;
                        }
                        now += nextChar;
                    }
                    col += charSize + MSGWND_DRAW_UNK_SPACE;
                    break;
            }

            if (col >= width) {
                col = 0;
                row++;
            }
        }

        if (row >= rowSize) {
            break;
        }
    }

    if (messageWnd->keyWait && (messageWnd->scrCount == 0.0)) {
        s32 blink = sins(messageWnd->grapCount << 10) * (1.0f / 0x200) + 191.0f;

        blink = (blink * messageWnd->alpha) >> 8;
        gDPSetPrimColor(gfx++, 0, 0, sMessageColorTable[color].r, sMessageColorTable[color].g,
                        sMessageColorTable[color].b, blink);

        switch (messageWnd->fontType) {
            case FONTTYPE_0:
                fontXX_draw(&gfx, messageWnd->posX + col * messageWnd->colStep,
                            (s32)(messageWnd->posY + row * messageWnd->rowStep - scrY), messageWnd->fntW,
                            messageWnd->fntH, "▼");
                break;

            case FONTTYPE_1:
                fontXX_draw2(&gfx, messageWnd->posX + col * messageWnd->colStep,
                             (s32)(messageWnd->posY + row * messageWnd->rowStep - scrY), messageWnd->fntW,
                             messageWnd->fntH, "▼");
                break;

            default:
                break;
        }
    }

    gDPSetScissor(gfx++, G_SC_NON_INTERLACE, 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1);

    messageWnd->grapCount++;

    *gfxP = gfx;
}

/**
 * Original name: msgWnd_isEnd
 */
bool msgWnd_isEnd(const MessageWnd *messageWnd) {
    return messageWnd->msgIsEnd;
}

/**
 * Original name: msgWnd_skip
 */
void msgWnd_skip(MessageWnd *messageWnd) {
    messageWnd->msgCount = messageWnd->msgBufSize;
    messageWnd->countWait = 0;
}

/**
 * Original name: msgWnd_isSpeaking
 */
bool msgWnd_isSpeaking(const MessageWnd *messageWnd) {
    return messageWnd->isSpeak;
}

/**
 * Original name: msgWnd_isScroll
 */
bool msgWnd_isScroll(const MessageWnd *messageWnd) {
    return messageWnd->rowNow >= messageWnd->rowSize;
}

/**
 * Original name: msgWnd_getWidth
 */
s32 msgWnd_getWidth(const MessageWnd *messageWnd) {
    return messageWnd->colSize * messageWnd->colStep;
}

/**
 * Original name: msgWnd_getHeight
 */
s32 msgWnd_getHeight(const MessageWnd *messageWnd) {
    return messageWnd->rowSize * messageWnd->rowStep;
}

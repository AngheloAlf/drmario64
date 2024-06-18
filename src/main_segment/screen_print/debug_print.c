#include "screen_print/debug_print.h"

#include "libultra.h"
#include "macros_defines.h"
#include "unknown_structs.h"
#include "main_segment_variables.h"
#include "screen_print/printf_impl.h"
#include "libc/assert.h"

// unused
Gfx D_8008D2A0[] = {
    gsSPEndDisplayList(),
};

// unused
u8 D_8008D2A8[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF,
};

// unused
Gfx D_8008D2C8[] = {
    gsSPEndDisplayList(),
};

#define DEBUG_PRINT_FONT_TEX_WIDTH 160
#define DEBUG_PRINT_FONT_TEX_HEIGHT 48

u8 sDebugPrintFontTex[] ALIGNED(8) = {
#include "main_segment/screen_print/debug_print/sDebugPrintFontTex.i4.inc"
};

static_assert(sizeof(sDebugPrintFontTex) == DEBUG_PRINT_FONT_TEX_WIDTH * DEBUG_PRINT_FONT_TEX_HEIGHT * sizeof(u8) / 2,
              "Texture does not have the expected resolution");

#define FONT_COLS_PER_ROW (26)

#define FONT_MAP_PACK(row, col) (((row)*FONT_COLS_PER_ROW) + ((col) % FONT_COLS_PER_ROW))
#define FONT_MAP_GET_ROW(value) ((value) % FONT_COLS_PER_ROW)
#define FONT_MAP_GET_COL(value) ((value) / FONT_COLS_PER_ROW)

char sDebugPrintFontMap[] = {
    /* 0x20 ' '  */ -1,
    /* 0x21 '!'  */ -1,
    /* 0x22 '"'  */ -1,
    /* 0x23 '#'  */ -1,
    /* 0x24 '$'  */ -1,
    /* 0x25 '%'  */ FONT_MAP_PACK(2, 14),
    /* 0x26 '&'  */ FONT_MAP_PACK(2, 11),
    /* 0x27 '\'' */ FONT_MAP_PACK(2, 24),
    /* 0x28 '('  */ -1,
    /* 0x29 ')'  */ -1,
    /* 0x2A '*'  */ -1,
    /* 0x2B '+'  */ -1,
    /* 0x2C ','  */ FONT_MAP_PACK(4, 21),
    /* 0x2D '-'  */ FONT_MAP_PACK(2, 10),
    /* 0x2E '.'  */ FONT_MAP_PACK(4, 22),
    /* 0x2F '/'  */ FONT_MAP_PACK(2, 23),
    /* 0x30 '0'  */ FONT_MAP_PACK(2, 0),
    /* 0x31 '1'  */ FONT_MAP_PACK(2, 1),
    /* 0x32 '2'  */ FONT_MAP_PACK(2, 2),
    /* 0x33 '3'  */ FONT_MAP_PACK(2, 3),
    /* 0x34 '4'  */ FONT_MAP_PACK(2, 4),
    /* 0x35 '5'  */ FONT_MAP_PACK(2, 5),
    /* 0x36 '6'  */ FONT_MAP_PACK(2, 6),
    /* 0x37 '7'  */ FONT_MAP_PACK(2, 7),
    /* 0x38 '8'  */ FONT_MAP_PACK(2, 8),
    /* 0x39 '9'  */ FONT_MAP_PACK(2, 9),
    /* 0x3A ':'  */ FONT_MAP_PACK(2, 13),
    /* 0x3B ';'  */ -1,
    /* 0x3C '<'  */ FONT_MAP_PACK(2, 21),
    /* 0x3D '='  */ -1,
    /* 0x3E '>'  */ FONT_MAP_PACK(2, 18),
    /* 0x3F '?'  */ FONT_MAP_PACK(2, 22),
    /* 0x40 '@'  */ -1,
    /* 0x41 'A'  */ FONT_MAP_PACK(0, 0),
    /* 0x42 'B'  */ FONT_MAP_PACK(0, 1),
    /* 0x43 'C'  */ FONT_MAP_PACK(0, 2),
    /* 0x44 'D'  */ FONT_MAP_PACK(0, 3),
    /* 0x45 'E'  */ FONT_MAP_PACK(0, 4),
    /* 0x46 'F'  */ FONT_MAP_PACK(0, 5),
    /* 0x47 'G'  */ FONT_MAP_PACK(0, 6),
    /* 0x48 'H'  */ FONT_MAP_PACK(0, 7),
    /* 0x49 'I'  */ FONT_MAP_PACK(0, 8),
    /* 0x4A 'J'  */ FONT_MAP_PACK(0, 9),
    /* 0x4B 'K'  */ FONT_MAP_PACK(0, 10),
    /* 0x4C 'L'  */ FONT_MAP_PACK(0, 11),
    /* 0x4D 'M'  */ FONT_MAP_PACK(0, 12),
    /* 0x4E 'N'  */ FONT_MAP_PACK(0, 13),
    /* 0x4F 'O'  */ FONT_MAP_PACK(0, 14),
    /* 0x50 'P'  */ FONT_MAP_PACK(0, 15),
    /* 0x51 'Q'  */ FONT_MAP_PACK(0, 16),
    /* 0x52 'R'  */ FONT_MAP_PACK(0, 17),
    /* 0x53 'S'  */ FONT_MAP_PACK(0, 18),
    /* 0x54 'T'  */ FONT_MAP_PACK(0, 19),
    /* 0x55 'U'  */ FONT_MAP_PACK(0, 20),
    /* 0x56 'V'  */ FONT_MAP_PACK(0, 21),
    /* 0x57 'W'  */ FONT_MAP_PACK(0, 22),
    /* 0x58 'X'  */ FONT_MAP_PACK(0, 23),
    /* 0x59 'Y'  */ FONT_MAP_PACK(0, 24),
    /* 0x5A 'Z'  */ FONT_MAP_PACK(0, 25),
    /* 0x5B '['  */ FONT_MAP_PACK(2, 16),
    /* 0x5C '\\' */ -1,
    /* 0x5D ']'  */ FONT_MAP_PACK(2, 17),
    /* 0x5E '^'  */ FONT_MAP_PACK(2, 12),
    /* 0x5F '_'  */ -1,
    /* 0x60 '`'  */ -1,
    /* 0x61 'a'  */ FONT_MAP_PACK(1, 0),
    /* 0x62 'b'  */ FONT_MAP_PACK(1, 1),
    /* 0x63 'c'  */ FONT_MAP_PACK(1, 2),
    /* 0x64 'd'  */ FONT_MAP_PACK(1, 3),
    /* 0x65 'e'  */ FONT_MAP_PACK(1, 4),
    /* 0x66 'f'  */ FONT_MAP_PACK(1, 5),
    /* 0x67 'g'  */ FONT_MAP_PACK(1, 6),
    /* 0x68 'h'  */ FONT_MAP_PACK(1, 7),
    /* 0x69 'i'  */ FONT_MAP_PACK(1, 8),
    /* 0x6A 'j'  */ FONT_MAP_PACK(1, 9),
    /* 0x6B 'k'  */ FONT_MAP_PACK(1, 10),
    /* 0x6C 'l'  */ FONT_MAP_PACK(1, 11),
    /* 0x6D 'm'  */ FONT_MAP_PACK(1, 12),
    /* 0x6E 'n'  */ FONT_MAP_PACK(1, 13),
    /* 0x6F 'o'  */ FONT_MAP_PACK(1, 14),
    /* 0x70 'p'  */ FONT_MAP_PACK(1, 15),
    /* 0x71 'q'  */ FONT_MAP_PACK(1, 16),
    /* 0x72 'r'  */ FONT_MAP_PACK(1, 17),
    /* 0x73 's'  */ FONT_MAP_PACK(1, 18),
    /* 0x74 't'  */ FONT_MAP_PACK(1, 19),
    /* 0x75 'u'  */ FONT_MAP_PACK(1, 20),
    /* 0x76 'v'  */ FONT_MAP_PACK(1, 21),
    /* 0x77 'w'  */ FONT_MAP_PACK(1, 22),
    /* 0x78 'x'  */ FONT_MAP_PACK(1, 23),
    /* 0x79 'y'  */ FONT_MAP_PACK(1, 24),
    /* 0x7A 'z'  */ FONT_MAP_PACK(1, 25),
    /* 0x7B '{'  */ -1,
    /* 0x7C '|'  */ -1,
    /* 0x7D '}'  */ -1,
    /* 0x7E '~'  */ FONT_MAP_PACK(2, 15),
    /* 0x7F ''   */ -1,
    /* 0x80 ''   */ FONT_MAP_PACK(5, 9),
    /* 0x81 ''   */ FONT_MAP_PACK(5, 10),
    /* 0x82 ''   */ FONT_MAP_PACK(5, 12),
    /* 0x83 ''   */ FONT_MAP_PACK(5, 11),
    /* 0x84 ''   */ -1,
    /* 0x85 ''   */ -1,
    /* 0x86 ''   */ -1,
    /* 0x87 ''   */ -1,
    /* 0x88 ''   */ -1,
    /* 0x89 ''   */ -1,
    /* 0x8A ''   */ -1,
    /* 0x8B ''   */ -1,
    /* 0x8C ''   */ -1,
    /* 0x8D ''   */ -1,
    /* 0x8E ''   */ -1,
    /* 0x8F ''   */ -1,
    /* 0x90 ''   */ -1,
    /* 0x91 ''   */ -1,
    /* 0x92 ''   */ -1,
    /* 0x93 ''   */ -1,
    /* 0x94 ''   */ -1,
    /* 0x95 ''   */ -1,
    /* 0x96 ''   */ -1,
    /* 0x97 ''   */ -1,
    /* 0x98 ''   */ -1,
    /* 0x99 ''   */ -1,
    /* 0x9A ''   */ -1,
    /* 0x9B ''   */ -1,
    /* 0x9C ''   */ -1,
    /* 0x9D ''   */ -1,
    /* 0x9E ''   */ -1,
    /* 0x9F ''   */ -1,
    /* 0xA0 ''   */ -1,
    /* 0xA1 ''   */ FONT_MAP_PACK(4, 22),
    /* 0xA2 ''   */ -1,
    /* 0xA3 ''   */ -1,
    /* 0xA4 ''   */ FONT_MAP_PACK(4, 21),
    /* 0xA5 ''   */ FONT_MAP_PACK(2, 20),
    /* 0xA6 ''   */ FONT_MAP_PACK(4, 19),
    /* 0xA7 ''   */ FONT_MAP_PACK(5, 0),
    /* 0xA8 ''   */ FONT_MAP_PACK(5, 1),
    /* 0xA9 ''   */ FONT_MAP_PACK(5, 2),
    /* 0xAA ''   */ FONT_MAP_PACK(5, 3),
    /* 0xAB ''   */ FONT_MAP_PACK(5, 4),
    /* 0xAC ''   */ FONT_MAP_PACK(5, 6),
    /* 0xAD ''   */ FONT_MAP_PACK(5, 7),
    /* 0xAE ''   */ FONT_MAP_PACK(5, 8),
    /* 0xAF ''   */ FONT_MAP_PACK(5, 5),
    /* 0xB0 ''   */ FONT_MAP_PACK(2, 19),
    /* 0xB1 ''   */ FONT_MAP_PACK(3, 0),
    /* 0xB2 ''   */ FONT_MAP_PACK(3, 1),
    /* 0xB3 ''   */ FONT_MAP_PACK(3, 2),
    /* 0xB4 ''   */ FONT_MAP_PACK(3, 3),
    /* 0xB5 ''   */ FONT_MAP_PACK(3, 4),
    /* 0xB6 ''   */ FONT_MAP_PACK(3, 5),
    /* 0xB7 ''   */ FONT_MAP_PACK(3, 6),
    /* 0xB8 ''   */ FONT_MAP_PACK(3, 7),
    /* 0xB9 ''   */ FONT_MAP_PACK(3, 8),
    /* 0xBA ''   */ FONT_MAP_PACK(3, 9),
    /* 0xBB ''   */ FONT_MAP_PACK(3, 10),
    /* 0xBC ''   */ FONT_MAP_PACK(3, 11),
    /* 0xBD ''   */ FONT_MAP_PACK(3, 12),
    /* 0xBE ''   */ FONT_MAP_PACK(3, 13),
    /* 0xBF ''   */ FONT_MAP_PACK(3, 14),
    /* 0xC0 ''   */ FONT_MAP_PACK(3, 15),
    /* 0xC1 ''   */ FONT_MAP_PACK(3, 16),
    /* 0xC2 ''   */ FONT_MAP_PACK(3, 17),
    /* 0xC3 ''   */ FONT_MAP_PACK(3, 18),
    /* 0xC4 ''   */ FONT_MAP_PACK(3, 19),
    /* 0xC5 ''   */ FONT_MAP_PACK(3, 20),
    /* 0xC6 ''   */ FONT_MAP_PACK(3, 21),
    /* 0xC7 ''   */ FONT_MAP_PACK(3, 22),
    /* 0xC8 ''   */ FONT_MAP_PACK(3, 23),
    /* 0xC9 ''   */ FONT_MAP_PACK(3, 24),
    /* 0xCA ''   */ FONT_MAP_PACK(4, 0),
    /* 0xCB ''   */ FONT_MAP_PACK(4, 1),
    /* 0xCC ''   */ FONT_MAP_PACK(4, 2),
    /* 0xCD ''   */ FONT_MAP_PACK(4, 3),
    /* 0xCE ''   */ FONT_MAP_PACK(4, 4),
    /* 0xCF ''   */ FONT_MAP_PACK(4, 5),
    /* 0xD0 ''   */ FONT_MAP_PACK(4, 6),
    /* 0xD1 ''   */ FONT_MAP_PACK(4, 7),
    /* 0xD2 ''   */ FONT_MAP_PACK(4, 8),
    /* 0xD3 ''   */ FONT_MAP_PACK(4, 9),
    /* 0xD4 ''   */ FONT_MAP_PACK(4, 10),
    /* 0xD5 ''   */ FONT_MAP_PACK(4, 11),
    /* 0xD6 ''   */ FONT_MAP_PACK(4, 12),
    /* 0xD7 ''   */ FONT_MAP_PACK(4, 13),
    /* 0xD8 ''   */ FONT_MAP_PACK(4, 14),
    /* 0xD9 ''   */ FONT_MAP_PACK(4, 15),
    /* 0xDA ''   */ FONT_MAP_PACK(4, 16),
    /* 0xDB ''   */ FONT_MAP_PACK(4, 17),
    /* 0xDC ''   */ FONT_MAP_PACK(4, 18),
    /* 0xDD ''   */ FONT_MAP_PACK(4, 20),
    /* 0xDE ''   */ FONT_MAP_PACK(4, 23),
    /* 0xDF ''   */ FONT_MAP_PACK(4, 24),
};

Gfx D_8008E290[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetScissor(G_SC_NON_INTERLACE, 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_TEX_EDGE, G_RM_TEX_EDGE2),
    gsDPSetCombineMode(G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM),
    gsDPSetTexturePersp(G_TP_NONE),
    gsDPSetTextureFilter(G_TF_POINT),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetTextureConvert(G_TC_FILT),
    gsDPSetColorDither(G_CD_BAYER),
    gsDPLoadTextureBlock_4b(sDebugPrintFontTex, G_IM_FMT_I, DEBUG_PRINT_FONT_TEX_WIDTH, DEBUG_PRINT_FONT_TEX_HEIGHT, 0,
                            G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK,
                            G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetPrimColor(0, 0, 255, 255, 255, 255),
    gsSPEndDisplayList(),
};

Color_RGB8 D_8008E340[] = {
    /* 0 */ { 0, 0, 0 },       // Black
    /* 1 */ { 0, 0, 255 },     // Blue
    /* 2 */ { 0, 255, 0 },     // Green
    /* 3 */ { 0, 255, 255 },   // Cyan
    /* 4 */ { 255, 0, 0 },     // Red
    /* 5 */ { 255, 0, 255 },   // Magenta
    /* 6 */ { 255, 255, 0 },   // Yellow
    /* 7 */ { 255, 255, 255 }, // White
};

void DebugPrint_8003E1E0(Gfx **gfxP) {
    Gfx *gfx = *gfxP;

    gSPDisplayList(gfx++, D_8008E290);

    *gfxP = gfx;
}

void DebugPrint_SetColor(Gfx **gfxP, s32 colorIndex) {
    Gfx *gfx = *gfxP;
    Color_RGB8 *color = &D_8008E340[colorIndex % ARRAY_COUNTU(D_8008E340)];

    gDPPipeSync(gfx++);
    gDPSetPrimColor(gfx++, 0, 0, color->r, color->g, color->b, 255);

    *gfxP = gfx;
}

void DebugPrint_8003E278(Gfx **gfxP, int x, int y, int arg3) {
    Gfx *gfx = *gfxP;
    int s = (FONT_MAP_GET_ROW(arg3) * DBGPRT_FONT_CHAR_WIDTH) << 5;
    int t = (FONT_MAP_GET_COL(arg3) * DBGPRT_FONT_CHAR_HEIGHT) << 5;

    gSPScisTextureRectangle(gfx++, x << 2, y << 2, (x + DBGPRT_FONT_CHAR_WIDTH) << 2,
                            (y + DBGPRT_FONT_CHAR_HEIGHT) << 2, G_TX_RENDERTILE, s, t, 1 << 10, 1 << 10);

    *gfxP = gfx;
}

void DebugPrint_DrawCharacter(Gfx **gfxP, s32 x, s32 y, s32 character) {
    if (character - 0x20 - 1 < ARRAY_COUNTU(sDebugPrintFontMap) - 1) {
        s32 val = sDebugPrintFontMap[character - 0x20];

        if (val != -1) {
            DebugPrint_8003E278(gfxP, x, y, val);
        }
    }
}

s32 DebugPrint_CallbackOpen(Printer *printer, va_list args) {
    PrinterState *state = printer->state;

    state->gfxP = va_arg(args, Gfx **);
    state->callback = va_arg(args, PrinterState_Callback);
    state->posX = va_arg(args, int);
    state->posY = va_arg(args, int);

    state->curCol = 0;
    state->curRow = 0;
    state->modifierCharacter = '\0';

    if (state->gfxP != NULL) {
        DebugPrint_8003E1E0(state->gfxP);
    }

    return 0;
}

s32 DebugPrint_CallbackClose(void) {
    return 0;
}

s32 DebugPrint_CallbackPutChars(Printer *printer, const char *chars, size_t length) {
    PrinterState *state = printer->state;
    s32 remainingChars = length;

    while (remainingChars > 0) {
        s32 character;

        remainingChars--;
        character = *(const unsigned char *)chars++;

        switch (state->modifierCharacter) {
            case '@':
                switch (character) {
                    case 'c':
                    case 'm':
                        state->modifierCharacter = character;
                        break;

                    default:
                        state->modifierCharacter = '\0';
                        break;
                }
                break;

            case 'c':
                if (state->gfxP != NULL) {
                    DebugPrint_SetColor(state->gfxP, character - '0');
                }
                state->modifierCharacter = 0xFF;
                break;

            case 'm':
                if (state->callback != NULL) {
                    state->callback(state->gfxP, state->posX + (state->curCol * DBGPRT_FONT_CHAR_WIDTH),
                                    state->posY + (state->curRow * DBGPRT_FONT_CHAR_HEIGHT), character);
                }
                state->modifierCharacter = 0xFF;
                break;

            default:
                state->modifierCharacter = '\0';
                break;
        }

        if (state->modifierCharacter == '\0') {
            if (character == '@') {
                state->modifierCharacter = character;
            } else if (character < ' ') {
                switch (character) {
                    case '\t':
                        state->curCol = ALIGN4(state->curCol + 1);
                        break;

                    case '\n':
                        state->curCol = 0;
                        state->curRow++;
                        break;
                }
            } else {
                if (state->gfxP != NULL) {
                    DebugPrint_DrawCharacter(state->gfxP, state->posX + state->curCol * DBGPRT_FONT_CHAR_WIDTH,
                                             state->posY + state->curRow * DBGPRT_FONT_CHAR_HEIGHT, character);
                }
                state->curCol++;
            }
        }
    }

    return length;
}

PrinterCallbacks sPrinterCallbacks = {
    DebugPrint_CallbackOpen,
    DebugPrint_CallbackClose,
    DebugPrint_CallbackPutChars,
};

static PrinterState sPrinterState;

Printer sPrinterInstance = {
    &sPrinterCallbacks,
    &sPrinterState,
};

s32 DebugPrint_Open(Gfx **gfxP, PrinterState_Callback callback, s32 posX, s32 posY) {
    return Printer_Open(&sPrinterInstance, gfxP, callback, posX, posY);
}

void DebugPrint_Close(void) {
    Printer_Close(&sPrinterInstance);
}

void DebugPrint_Printf(const char *fmt, ...) {
    va_list args;

    va_start(args, fmt);

#if VERSION_US || VERSION_GW
    _kmcprt(&sPrinterInstance, fmt, args);
#endif

    va_end(args);
}

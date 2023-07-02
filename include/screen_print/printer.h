#ifndef SCREEN_PRINT_PRINTER_H
#define SCREEN_PRINT_PRINTER_H

#include "libultra.h"
#include "libc/stdarg.h"
#include "libc/stddef.h"

struct Printer;

typedef s32 (*PrinterCallbacks_Open)(struct Printer *, va_list);

typedef s32 (*PrinterCallbacks_Close)(void);

typedef s32 (*PrinterCallbacks_PutChars)(struct Printer *, const char *, size_t);

typedef struct PrinterCallbacks {
    /* 0x0 */ PrinterCallbacks_Open open;
    /* 0x0 */ PrinterCallbacks_Close close;
    /* 0x0 */ PrinterCallbacks_PutChars putChars;
} PrinterCallbacks; // size = 0xC

typedef void (*PrinterState_Callback)(Gfx **, s32, s32, s32);

typedef struct PrinterState {
    /* 0x00 */ Gfx **gfxP;
    /* 0x00 */ PrinterState_Callback callback;
    /* 0x00 */ s16 posX;
    /* 0x00 */ s16 posY;
    /* 0x00 */ s16 curCol;
    /* 0x00 */ s16 curRow;
    /* 0x00 */ s16 modifierCharacter;
} PrinterState; // size = 0x12

typedef struct Printer {
    /* 0x0 */ PrinterCallbacks *callbacks;
    /* 0x4 */ PrinterState *state;
} Printer; // size = 4

s32 Printer_Open(Printer *printer, ...);
s32 Printer_Close(Printer *printer);
s32 Printer_PutChars(Printer *printer, const char *chars, size_t length);

#endif

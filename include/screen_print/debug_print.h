#ifndef SCREEN_PRINT_DEBUG_PRINT_H
#define SCREEN_PRINT_DEBUG_PRINT_H

#include "printer.h"

#define DBGPRT_FONT_CHAR_WIDTH (6)
#define DBGPRT_FONT_CHAR_HEIGHT (8)


void DebugPrint_SetColor(Gfx **gfxP, s32 colorIndex);
void DebugPrint_DrawCharacter(Gfx **gfxP, s32 x, s32 y, s32 character);
s32 DebugPrint_Open(Gfx **gfxP, PrinterState_Callback callback, s32 posX, s32 posY);
void DebugPrint_Close(void);
void DebugPrint_Printf(const char *fmt, ...);

#define DBGPRT_COLOR_BLACK   0
#define DBGPRT_COLOR_BLUE    1
#define DBGPRT_COLOR_GREEN   2
#define DBGPRT_COLOR_CYAN    3
#define DBGPRT_COLOR_RED     4
#define DBGPRT_COLOR_MAGENTA 5
#define DBGPRT_COLOR_YELLOW  6
#define DBGPRT_COLOR_WHITE   7

#define DBGPRT_COLOR_EXPAND0(color) #color
#define DBGPRT_COLOR_EXPAND1(color) DBGPRT_COLOR_EXPAND0(color)
#define DBGPRT_COLOR_EXPAND2(color) DBGPRT_COLOR_EXPAND1(DBGPRT_COLOR_##color)

#define DBGPRT_COLOR_RAW "@c"
#define DBGPRT_COLOR(color) DBGPRT_COLOR_RAW DBGPRT_COLOR_EXPAND2(color)
#define DBGPRT_CALLBACK "@m"

#endif

#ifndef SCREEN_PRINT_DEBUG_PRINT_H
#define SCREEN_PRINT_DEBUG_PRINT_H

#include "printer.h"

typedef void (*DebugPrint_8003E69C_arg1)(Gfx **, s32, s32, s32);


void DebugPrint_SetColor(Gfx **gfxP, s32 colorIndex);
void DebugPrint_8003E3F0(Gfx **gfxP, s32 arg1, s32 arg2, s32 character);
s32 DebugPrint_8003E69C(Gfx **gfxP, DebugPrint_8003E69C_arg1 arg1, s32 arg2, s32 arg3);
void DebugPrint_8003E6D8(void);
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

#define DBGPRT_COLOR(color) "@c" DBGPRT_COLOR_EXPAND2(color)
#define DBGPRT_CALLBACK(color) "@m"

#endif

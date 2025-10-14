#ifndef TEX_FUNC_H
#define TEX_FUNC_H

#include "libultra.h"
#include "unk.h"
#include "libc/stdint.h"
#include "other_types.h"



typedef enum TiTexDataFormat {
    /* 0x04 */ TITEX_FORMAT_4 = 4,
    /* 0x08 */ TITEX_FORMAT_8 = 8,
    /* 0x10 */ TITEX_FORMAT_16 = 16,
} TiTexDataFormat;

#define TITEX_FLAGS_TILE  (0x0)
#define TITEX_FLAGS_BLOCK (0x1)

typedef struct TiTexData {
    /**
     * [0]: tlut
     * [1]: texture
     */
    /* 0x0 */ TexturePtr *texs;

    /**
     * [0]: width
     * [1]: height
     * [2]: format. See TiTexDataFormat
     * [2]: bitflags: See TITEX_FLAGS_*
     */
    /* 0x4 */ u16 *info;
} TiTexData; // size = 0x8

typedef struct TiTexDataHeader {
    /* 0x0 */ TiTexData *texData;
    /* 0x4 */ s32 *texDataLen;
} TiTexDataHeader; // size = 0x8



typedef enum GfxSetScissorMode {
    /* 0 */ GFXSETSCISSOR_INTERLACE_ODD,
    /* 1 */ GFXSETSCISSOR_INTERLACE_EVEN,
    /* 2 */ GFXSETSCISSOR_INTERLACE_NO,
    /* 3 */ GFXSETSCISSOR_INTERLACE_NO2,
} GfxSetScissorMode;


void gfxSetScissor(Gfx **gfxP, GfxSetScissorMode mode, s32 x, s32 y, s32 width, s32 height);

void FillRectRGB(Gfx **gxfP, s32 x, s32 y, s32 width, s32 height, s32 red, s32 green, s32 blue);
void FillRectRGBA(Gfx **gfxP, s32 x, s32 y, s32 width, s32 height, s32 red, s32 green, s32 blue, s32 alpha);

void CopyTexBlock4(Gfx **gfxP, u16 *tlut, void *arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
void CopyTexBlock8(Gfx **gfxP, u16 tlut[], TexturePtr arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
void CopyTexBlock16(Gfx **gfxP, TexturePtr arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);

void StretchAlphaTexBlock(Gfx **gfxP, s32 arg1, s32 arg2, TexturePtr arg3, s32 arg4, TexturePtr arg5, s32 arg6, f32 arg7, f32 arg8, f32 arg9, f32 argA);
void StretchTexBlock4(Gfx **gfxP, s32 arg1, s32 arg2, TexturePtr tlut, UNK_PTR arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8);
void StretchTexBlock8(Gfx **gfxP, s32 arg1, s32 arg2, TexturePtr tlut, UNK_PTR arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8);
void StretchTexBlock16(Gfx **gfxP, s32 arg1, s32 arg2, UNK_PTR arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7);
void StretchTexBlock4i(Gfx **gfxP, s32 arg1, s32 arg2, UNK_PTR arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7);
void func_800432A8(Gfx **gfxP, s32 arg1, s32 arg2, UNK_PTR arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7);

void StretchAlphaTexTile(Gfx **gfxP, s32 arg1, s32 arg2, TexturePtr arg3, s32 arg4, TexturePtr arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 argA, f32 argB, f32 argC, f32 argD, f32 argE);
void RectAlphaTexTile(Gfx **gfxP, Vtx **vtxP, s32 arg2, s32 arg3, void *arg4, s32 arg5, void *arg6, s32 arg7, s32 arg8, s32 arg9, s32 argA, s32 argB, f32 argC, f32 argD, f32 argE, f32 argF);
void StretchTexTile4(Gfx **gfxP, s32 width, s32 height, u16 tlut[], u8 tex[], s32 arg5, s32 arg6, s32 arg7, s32 arg8, f32 arg9, f32 argA, f32 argB, f32 argC);
void StretchTexTile8(Gfx **gfxP, s32 width, s32 height, u16 tlut[], u8 tex[], UNK_TYPE arg5, UNK_TYPE arg6, UNK_TYPE arg7, UNK_TYPE arg8, f32 arg9, f32 argA, f32 argB, f32 argC);
void RectTexTile8(Gfx **gfxP, Vtx **vtxP, s32 arg2, s32 arg3, u16 *tlut, u8 *texture, s32 arg6, s32 arg7, s32 arg8, s32 arg9, f32 argA, f32 argB, f32 argC, f32 argD);
void StretchTexTile16(Gfx **gfxP, s32 arg1, s32 arg2, u16 *arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, f32 arg8, f32 arg9, f32 argA, f32 argB);
void StretchTexTile4i(Gfx **gfxP, s32 width, s32 height, u8 tex[], s32 arg4, s32 arg5, s32 arg6, s32 arg7, f32 arg8, f32 arg9, f32 argA, f32 argB);
void RectTexTile4i(Gfx **gfxP, Vtx **vtxP, s32 width, s32 height, u8 *tex, s32 arg5, s32 arg6, s32 arg7, s32 arg8, f32 arg9, f32 argA, f32 argB, f32 argC);

void tiMappingAddr(TiTexData *tiArr, s32 len, uintptr_t addr);
TiTexData *tiLoadTexData(UNK_PTR *heap, RomOffset segmentRom, RomOffset segmentRomEnd);
// void func_80045110();
void tiCopyTexBlock(Gfx **gfxP, TiTexData *arg1, s32 arg2, s32 arg3, s32 arg4);
void tiStretchTexBlock(Gfx **gfxP, TiTexData *arg1, s32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6);
void tiStretchTexTile(Gfx **gfxP, TiTexData *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, f32 arg7, f32 arg8, f32 arg9, f32 argA);
void tiStretchTexItem(Gfx **gfxP, TiTexData *arg1, s32 arg2, s32 arg3, s32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8);
void tiStretchAlphaTexItem(Gfx **gfxP, TiTexData *arg1, TiTexData * arg2, s32 arg3, s32 arg4, s32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9);
void func_80045914(Gfx **gfxP, TiTexData *arg1, TiTexData *arg2, s32 arg3, s32 arg4, s32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9);
void drawCursorPattern(Gfx** gfxP, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8);


// .data

extern Gfx copy_texture_init_dl[];
extern Gfx alpha_texture_init_dl[];
extern Gfx normal_texture_init_dl[];
extern Gfx D_8008E728[];
extern Gfx init_dl_155[];

#endif

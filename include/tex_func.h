#ifndef TEX_FUNC_H
#define TEX_FUNC_H

#include "libultra.h"
#include "unk.h"
#include "libc/stdbool.h"
#include "libc/stdint.h"
#include "other_types.h"


typedef enum TiTexDataFormat {
    /* 0x04 */ TITEX_FORMAT_4 = 4,
    /* 0x08 */ TITEX_FORMAT_8 = 8,
    /* 0x10 */ TITEX_FORMAT_16 = 16,
} TiTexDataFormat;

#define TITEX_FLAGS_TILE  (0x0)
#define TITEX_FLAGS_BLOCK (0x1)

// TODO: try to change members to const
typedef struct TiTexData {
    #define TI_TEX_TLUT (0)
    #define TI_TEX_TEX (1)
    /**
     * [0]: tlut
     * [1]: texture
     */
    /* 0x0 */ Texture **texs; /* Original name: addr */

    #define TI_INFO_IDX_WIDTH (0)
    #define TI_INFO_IDX_HEIGHT (1)
    #define TI_INFO_IDX_FORMAT (2)
    #define TI_INFO_IDX_FLAGS (3)
    /**
     * [0]: width
     * [1]: height
     * [2]: format. See TiTexDataFormat
     * [3]: bitflags: See TITEX_FLAGS_*
     */
    /* 0x4 */ u16 *info; /* Original name: size */
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

void CopyTexBlock4(Gfx **gfxP, const u16 tlut[], const u8 tex[], s32 x, s32 y, s32 w, s32 h);
void CopyTexBlock8(Gfx **gfxP, const u16 tlut[], const u8 tex[], s32 x, s32 y, s32 w, s32 h);
void CopyTexBlock16(Gfx **gfxP, const u16 tex[], s32 x, s32 y, s32 w, s32 h);

void StretchAlphaTexBlock(Gfx **gfxP, s32 texW, s32 texH, const u16 colorTex[], s32 colorTexW, const u8 alphaTex[],
                          s32 alphaTexW, f32 x, f32 y, f32 w, f32 h);
void StretchTexBlock4(Gfx **gfxP, s32 texW, s32 texH, const u16 tlut[], const u8 tex[], f32 x, f32 y, f32 w, f32 h);
void StretchTexBlock8(Gfx **gfxP, s32 texW, s32 texH, const u16 tlut[], const u8 tex[], f32 x, f32 y, f32 w, f32 h);
void StretchTexBlock16(Gfx **gfxP, s32 texW, s32 texH, const u16 tex[], f32 x, f32 y, f32 w, f32 h);
void StretchTexBlock4i(Gfx **gfxP, s32 texW, s32 texH, const u8 tex[], f32 x, f32 y, f32 w, f32 h);
void StretchTexBlock8i(Gfx **gfxP, s32 texW, s32 texH, const u8 tex[], f32 x, f32 y, f32 w, f32 h);

void StretchAlphaTexTile(Gfx **gfxP, s32 texW, s32 texH, const u16 colorTex[], s32 colorTexW, const u8 alphaTex[],
                         s32 alphaTexW, s32 lx, s32 ly, s32 lw, s32 lh, f32 x, f32 y, f32 w, f32 h);
void RectAlphaTexTile(Gfx **gfxP, Vtx **vtxP, s32 texW, s32 texH, const u16 colorTex[], s32 colorTexW,
                      const u8 alphaTex[], s32 alphaTexW, s32 lx, s32 ly, s32 lw, s32 lh, f32 x, f32 y, f32 w, f32 h);
void StretchTexTile4(Gfx **gfxP, s32 texW, s32 texH, const u16 tlut[], const u8 tex[], s32 lx, s32 ly, s32 lw, s32 lh,
                     f32 x, f32 y, f32 w, f32 h);
void StretchTexTile8(Gfx **gfxP, s32 texW, s32 texH, const u16 tlut[], const u8 tex[], s32 lx, s32 ly, s32 lw, s32 lh,
                     f32 x, f32 y, f32 w, f32 h);
void RectTexTile8(Gfx **gfxP, Vtx **vtxP, s32 texW, s32 texH, const u16 tlut[], const u8 tex[], s32 lx, s32 ly, s32 lw,
                  s32 lh, f32 x, f32 y, f32 w, f32 h);
void StretchTexTile16(Gfx **gfxP, s32 texW, s32 texH, const u16 tex[], s32 lx, s32 ly, s32 lw, s32 lh, f32 x, f32 y,
                      f32 w, f32 h);
void StretchTexTile4i(Gfx **gfxP, s32 texW, s32 texH, const u8 tex[], s32 lx, s32 ly, s32 lw, s32 lh, f32 x, f32 y,
                      f32 w, f32 h);
void RectTexTile4i(Gfx **gfxP, Vtx **vtxP, s32 texW, s32 texH, const u8 tex[], s32 lx, s32 ly, s32 lw, s32 lh, f32 x,
                   f32 y, f32 w, f32 h);

void tiMappingAddr(TiTexData *tiArr, s32 len, uintptr_t addr);
TiTexData *tiLoadTexData(UNK_PTR *heap, RomOffset segmentRom, RomOffset segmentRomEnd);
void *func_80045110(void **arg0, void **arg1, s32 arg2, RomOffset segmentRom, RomOffset segmentRomEnd);
void tiCopyTexBlock(Gfx **gfxP, const TiTexData *ti, bool cached, s32 x, s32 y);
void tiStretchTexBlock(Gfx **gfxP, const TiTexData *ti, bool cached, f32 x, f32 y, f32 w, f32 h);
void tiStretchTexTile(Gfx **gfxP, const TiTexData *ti, bool cached, s32 lx, s32 ly, s32 lw, s32 lh, f32 x, f32 y, f32 w,
                      f32 h);
void tiStretchTexItem(Gfx **gfxP, const TiTexData *ti, bool cached, s32 count, s32 index, f32 x, f32 y, f32 w, f32 h);
void tiStretchAlphaTexItem(Gfx **gfxP, const TiTexData *tiC, const TiTexData *tiA, bool cached, s32 count, s32 index,
                           f32 x, f32 y, f32 w, f32 h);
void tiStretchAlphaTexItem2(Gfx **gfxP, const TiTexData *tiC, const TiTexData *tiA, bool cached, s32 count, s32 index,
                            f32 x, f32 y, f32 w, f32 h);

void drawCursorPattern(Gfx **gfxP, s32 arg1, s32 arg2, s32 frmW, s32 frmH, s32 posX, s32 posY, s32 posW, s32 posH);

// .data

extern Gfx copy_texture_init_dl[];
extern Gfx alpha_texture_init_dl[];
extern Gfx normal_texture_init_dl[];
extern Gfx D_8008E728[];
extern Gfx init_dl_155[];

#endif

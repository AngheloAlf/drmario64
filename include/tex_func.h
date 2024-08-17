#ifndef TEX_FUNC_H
#define TEX_FUNC_H

#include "libultra.h"
#include "unk.h"
#include "libc/stdint.h"
#include "other_types.h"

struct StretchTexBlock_arg0;
struct StretchTexTile_arg0;


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


typedef void (*StretchTexBlock_arg0_callback)(struct StretchTexBlock_arg0 *arg0);

typedef struct StretchTexBlock_arg0_unk_4C {
    /* 0x00 */ s32 unk_00; // xl
    /* 0x04 */ s32 unk_04; // yl
    /* 0x08 */ s32 unk_08; // xh
    /* 0x0C */ s32 unk_0C; // yh
    /* 0x0C */ s32 unk_10; // s
    /* 0x0C */ s32 unk_14; // t
    /* 0x0C */ s32 unk_18; // dsdx
    /* 0x0C */ s32 unk_1C; // dtdy
} StretchTexBlock_arg0_unk_4C; // size = 0x20

typedef struct StretchTexBlock_arg0 {
    /* 0x00 */ Gfx **gfxP;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ TexturePtr unk_10;
    /* 0x14 */ s32 width;
    /* 0x18 */ TexturePtr unk_18;
    /* 0x1C */ s32 unk_1C;
    /* 0x20 */ s32 unk_20;
    /* 0x24 */ s32 unk_24;
    /* 0x28 */ s32 unk_28;
    /* 0x2C */ s32 unk_2C;
    /* 0x30 */ StretchTexBlock_arg0_callback unk_30;
    /* 0x34 */ StretchTexBlock_arg0_callback unk_34;
    /* 0x38 */ s32 unk_38;
    /* 0x3C */ StretchTexBlock_arg0_callback unk_3C;
    /* 0x40 */ s32 unk_40;
    /* 0x44 */ s32 unk_44;
    /* 0x48 */ s32 height;
    /* 0x4C */ StretchTexBlock_arg0_unk_4C unk_4C;
    /* 0x6C */ UNK_TYPE1 unk_6C[0x4];
} StretchTexBlock_arg0; // size >= 0x70?


typedef void (*StretchTexTile_arg0_callback)(struct StretchTexTile_arg0 *arg0);

// Maybe merge with StretchTexBlock_arg0_unk_4C ?
typedef struct StretchTexTile_arg0_unk_58 {
    /* 0x00 */ s32 unk_00; // xl
    /* 0x04 */ s32 unk_04; // yl
    /* 0x08 */ s32 unk_08; // xh
    /* 0x0C */ s32 unk_0C; // yh
    /* 0x0C */ s32 unk_10; // s
    /* 0x0C */ s32 unk_14; // t
    /* 0x0C */ s32 unk_18; // dsdx
    /* 0x0C */ s32 unk_1C; // dtdy
} StretchTexTile_arg0_unk_58; // size = 0x20

typedef struct StretchTexTile_arg0 {
    /* 0x00 */ Gfx **gfxP;
    /* 0x04 */ Vtx **vtxP;
    /* 0x08 */ UNK_TYPE unk_08;
    /* 0x0C */ UNK_TYPE unk_0C;
    /* 0x10 */ TexturePtr texture;
    /* 0x14 */ s32 unk_14; // width
    /* 0x18 */ TexturePtr unk_18;
    /* 0x1C */ UNK_TYPE unk_1C;
    /* 0x20 */ s32 unk_20; // uls
    /* 0x24 */ UNK_TYPE unk_24;
    /* 0x28 */ UNK_TYPE unk_28;
    /* 0x2C */ UNK_TYPE unk_2C;
    /* 0x30 */ UNK_TYPE unk_30;
    /* 0x34 */ UNK_TYPE unk_34;
    /* 0x38 */ UNK_TYPE unk_38;
    /* 0x3C */ UNK_TYPE unk_3C;
    /* 0x40 */ StretchTexTile_arg0_callback unk_40;
    /* 0x44 */ StretchTexTile_arg0_callback unk_44;
    /* 0x48 */ UNK_TYPE unk_48;
    /* 0x4C */ StretchTexTile_arg0_callback unk_4C;
    /* 0x50 */ s32 unk_50; // ult
    /* 0x54 */ UNK_TYPE unk_54;
    /* 0x58 */ StretchTexTile_arg0_unk_58 unk_58;
} StretchTexTile_arg0; // size = 0x78

struct struct_CopyTexBlock_arg0;

typedef void (*struct_CopyTexBlock_arg0_unk_18)(struct struct_CopyTexBlock_arg0 *arg0);

typedef struct struct_CopyTexBlock_arg0 {
    /* 0x00 */ Gfx **gfxP;
    /* 0x04 */ TexturePtr unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ struct_CopyTexBlock_arg0_unk_18 unk_18;
    /* 0x1C */ s32 unk_1C;
    /* 0x20 */ s32 unk_20;
    /* 0x24 */ s32 unk_24;
} struct_CopyTexBlock_arg0; // size >= 0x28

typedef enum GfxSetScissorMode {
    /* 0 */ GFXSETSCISSOR_INTERLACE_ODD,
    /* 1 */ GFXSETSCISSOR_INTERLACE_EVEN,
    /* 2 */ GFXSETSCISSOR_INTERLACE_NO,
    /* 3 */ GFXSETSCISSOR_INTERLACE_NO2,
} GfxSetScissorMode;

void gfxSetScissor(Gfx **gfxP, GfxSetScissorMode mode, s32 x, s32 y, s32 width, s32 height);
void func_80040D34(Gfx **gxfP, s32 x, s32 y, s32 width, s32 height, s32 red, s32 green, s32 blue);
void FillRectRGBA(Gfx **gfxP, s32 x, s32 y, s32 width, s32 height, s32 red, s32 green, s32 blue, s32 alpha);
void CopyTexBlock(struct_CopyTexBlock_arg0 *arg0);
void CopyTexBlock4_LoadTex(struct_CopyTexBlock_arg0 *arg0);
void CopyTexBlock4(Gfx **gfxP, u16 *tlut, void *arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
void CopyTexBlock8_LoadTex(struct_CopyTexBlock_arg0 *arg0);
void CopyTexBlock8(Gfx **gfxP, u16 tlut[], TexturePtr arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
void CopyTexBlock16_LoadTex(struct_CopyTexBlock_arg0 *arg0);
void CopyTexBlock16(Gfx **gfxP, TexturePtr arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
void StretchTexBlock(StretchTexBlock_arg0 *arg0);
void StretchTexBlock_ScisRect(StretchTexBlock_arg0 *arg0);
void StretchAlphaTexBlock_LoadColorTex(StretchTexBlock_arg0 *arg0);
void StretchAlphaTexBlock_LoadAlphaTex(StretchTexBlock_arg0 *arg0);
void StretchAlphaTexBlock(Gfx **gfxP, s32 arg1, s32 arg2, TexturePtr arg3, s32 arg4, TexturePtr arg5, s32 arg6, f32 arg7, f32 arg8, f32 arg9, f32 argA);
void StretchTexBlock4_LoadTex(StretchTexBlock_arg0 *arg0);
void StretchTexBlock4(Gfx **gfxP, s32 arg1, s32 arg2, TexturePtr tlut, UNK_PTR arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8);
void StretchTexBlock8_LoadTex(StretchTexBlock_arg0 *arg0);
void StretchTexBlock8(Gfx **gfxP, s32 arg1, s32 arg2, TexturePtr tlut, UNK_PTR arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8);
void StretchTexBlock16_LoadTex(StretchTexBlock_arg0 *arg0);
void StretchTexBlock16(Gfx **gfxP, s32 arg1, s32 arg2, UNK_PTR arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7);
void StretchTexBlock4i_LoadTex(StretchTexBlock_arg0 *arg0);
void StretchTexBlock4i(Gfx **gfxP, s32 arg1, s32 arg2, UNK_PTR arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7);
void func_800430D0(StretchTexBlock_arg0 *arg0);
void func_800432A8(Gfx **gfxP, s32 arg1, s32 arg2, UNK_PTR arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7);
void StretchTexTile(StretchTexTile_arg0 *arg0);
void StretchTexTile_ScisRect(StretchTexTile_arg0 *arg0);
void RectTexTile_ScisRect(StretchTexTile_arg0 *arg0);
void StretchAlphaTexTile_LoadColorTex(StretchTexTile_arg0 *arg0);
void StretchAlphaTexTile_LoadAlphaTex(StretchTexTile_arg0 *arg0);
void StretchAlphaTexTile(Gfx **gfxP, s32 arg1, s32 arg2, TexturePtr arg3, s32 arg4, TexturePtr arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 argA, f32 argB, f32 argC, f32 argD, f32 argE);
void RectAlphaTexTile(Gfx **gfxP, Vtx **vtxP, s32 arg2, s32 arg3, void *arg4, s32 arg5, void *arg6, s32 arg7, s32 arg8, s32 arg9, s32 argA, s32 argB, f32 argC, f32 argD, f32 argE, f32 argF);
void StretchTexTile4_LoadTex(StretchTexTile_arg0 *arg0);
void StretchTexTile4(Gfx **gfxP, s32 width, s32 height, u16 tlut[], u8 tex[], s32 arg5, s32 arg6, s32 arg7, s32 arg8, f32 arg9, f32 argA, f32 argB, f32 argC);
void StretchTexTile8_LoadTex(StretchTexTile_arg0 *arg0);
void StretchTexTile8(Gfx **gfxP, s32 width, s32 height, u16 tlut[], u8 tex[], UNK_TYPE arg5, UNK_TYPE arg6, UNK_TYPE arg7, UNK_TYPE arg8, f32 arg9, f32 argA, f32 argB, f32 argC);
void RectTexTile8(Gfx **gfxP, Vtx **vtxP, s32 arg2, s32 arg3, u16 *tlut, u8 *texture, s32 arg6, s32 arg7, s32 arg8, s32 arg9, f32 argA, f32 argB, f32 argC, f32 argD);
void StretchTexTile16_LoadTex(StretchTexTile_arg0 *arg0);
void StretchTexTile16(Gfx **gfxP, s32 arg1, s32 arg2, u16 *arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, f32 arg8, f32 arg9, f32 argA, f32 argB);
void StretchTexTile4i_LoadTex(StretchTexTile_arg0 *arg0);
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

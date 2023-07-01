#include "libultra.h"
#include "include_asm.h"
#include "macros_defines.h"
#include "unknown_structs.h"
#include "main_segment_functions.h"
#include "main_segment_variables.h"
#include "screen_print/026000.h"
#include "screen_print/printf_impl.h"

extern struct_8008E364_unk_4 B_800E5890;

extern u8 D_8008D2D0[];
extern u8 D_8008E1D0[];
extern Gfx D_8008E290[];
extern Color_RGB8 D_8008E340[];
extern struct_8008E364_unk_0 D_8008E358;
extern struct_8008E364 D_8008E364;

#if VERSION_US
u8 D_8008D2D0[] = {
#include "main_segment/screen_print/026000/D_8008D2D0.i4.inc"
};

u8 D_8008E1D0[] = {
    /* */ 0xFF,
    /* */ 0xFF,
    /* */ 0xFF,
    /* */ 0xFF,
    /* */ 0xFF,
    /* */ 0x42,
    /* */ 0x3F,
    /* */ 0x4C,
    /* */ 0xFF,
    /* */ 0xFF,
    /* */ 0xFF,
    /* */ 0xFF,
    /* */ 0x7D,
    /* */ 0x3E,
    /* */ 0x7E,
    /* */ 0x4B,
    /* */ 0x34,
    /* */ 0x35,
    /* */ 0x36,
    /* */ 0x37,
    /* */ 0x38,
    /* */ 0x39,
    /* */ 0x3A,
    /* */ 0x3B,
    /* */ 0x3C,
    /* */ 0x3D,
    /* */ 0x41,
    /* */ 0xFF,
    /* */ 0x49,
    /* */ 0xFF,
    /* */ 0x46,
    /* */ 0x4A,
    /* */ 0xFF,
    /* */ 0x00,
    /* */ 0x01,
    /* */ 0x02,
    /* */ 0x03,
    /* */ 0x04,
    /* */ 0x05,
    /* */ 0x06,
    /* */ 0x07,
    /* */ 0x08,
    /* */ 0x09,
    /* */ 0x0A,
    /* */ 0x0B,
    /* */ 0x0C,
    /* */ 0x0D,
    /* */ 0x0E,
    /* */ 0x0F,
    /* */ 0x10,
    /* */ 0x11,
    /* */ 0x12,
    /* */ 0x13,
    /* */ 0x14,
    /* */ 0x15,
    /* */ 0x16,
    /* */ 0x17,
    /* */ 0x18,
    /* */ 0x19,
    /* */ 0x44,
    /* */ 0xFF,
    /* */ 0x45,
    /* */ 0x40,
    /* */ 0xFF,
    /* */ 0xFF,
    /* */ 0x1A,
    /* */ 0x1B,
    /* */ 0x1C,
    /* */ 0x1D,
    /* */ 0x1E,
    /* */ 0x1F,
    /* */ 0x20,
    /* */ 0x21,
    /* */ 0x22,
    /* */ 0x23,
    /* */ 0x24,
    /* */ 0x25,
    /* */ 0x26,
    /* */ 0x27,
    /* */ 0x28,
    /* */ 0x29,
    /* */ 0x2A,
    /* */ 0x2B,
    /* */ 0x2C,
    /* */ 0x2D,
    /* */ 0x2E,
    /* */ 0x2F,
    /* */ 0x30,
    /* */ 0x31,
    /* */ 0x32,
    /* */ 0x33,
    /* */ 0xFF,
    /* */ 0xFF,
    /* */ 0xFF,
    /* */ 0x43,
    /* */ 0xFF,
    /* */ 0x8B,
    /* */ 0x8C,
    /* */ 0x8E,
    /* */ 0x8D,
    /* */ 0xFF,
    /* */ 0xFF,
    /* */ 0xFF,
    /* */ 0xFF,
    /* */ 0xFF,
    /* */ 0xFF,
    /* */ 0xFF,
    /* */ 0xFF,
    /* */ 0xFF,
    /* */ 0xFF,
    /* */ 0xFF,
    /* */ 0xFF,
    /* */ 0xFF,
    /* */ 0xFF,
    /* */ 0xFF,
    /* */ 0xFF,
    /* */ 0xFF,
    /* */ 0xFF,
    /* */ 0xFF,
    /* */ 0xFF,
    /* */ 0xFF,
    /* */ 0xFF,
    /* */ 0xFF,
    /* */ 0xFF,
    /* */ 0xFF,
    /* */ 0xFF,
    /* */ 0xFF,
    /* */ 0xFF,
    /* */ 0xFF,
    /* */ 0x7E,
    /* */ 0xFF,
    /* */ 0xFF,
    /* */ 0x7D,
    /* */ 0x48,
    /* */ 0x7B,
    /* */ 0x82,
    /* */ 0x83,
    /* */ 0x84,
    /* */ 0x85,
    /* */ 0x86,
    /* */ 0x88,
    /* */ 0x89,
    /* */ 0x8A,
    /* */ 0x87,
    /* */ 0x47,
    /* */ 0x4E,
    /* */ 0x4F,
    /* */ 0x50,
    /* */ 0x51,
    /* */ 0x52,
    /* */ 0x53,
    /* */ 0x54,
    /* */ 0x55,
    /* */ 0x56,
    /* */ 0x57,
    /* */ 0x58,
    /* */ 0x59,
    /* */ 0x5A,
    /* */ 0x5B,
    /* */ 0x5C,
    /* */ 0x5D,
    /* */ 0x5E,
    /* */ 0x5F,
    /* */ 0x60,
    /* */ 0x61,
    /* */ 0x62,
    /* */ 0x63,
    /* */ 0x64,
    /* */ 0x65,
    /* */ 0x66,
    /* */ 0x68,
    /* */ 0x69,
    /* */ 0x6A,
    /* */ 0x6B,
    /* */ 0x6C,
    /* */ 0x6D,
    /* */ 0x6E,
    /* */ 0x6F,
    /* */ 0x70,
    /* */ 0x71,
    /* */ 0x72,
    /* */ 0x73,
    /* */ 0x74,
    /* */ 0x75,
    /* */ 0x76,
    /* */ 0x77,
    /* */ 0x78,
    /* */ 0x79,
    /* */ 0x7A,
    /* */ 0x7C,
    /* */ 0x7F,
    /* */ 0x80,
};

Gfx D_8008E290[] = {
#include "main_segment/screen_print/026000/D_8008E290.gfx.inc.c"
};

Color_RGB8 D_8008E340[] = {
    { 0, 0, 0 },    { 0, 0, 0xFF },    { 0, 0xFF, 0 },    { 0, 0xFF, 0xFF },
    { 0xFF, 0, 0 }, { 0xFF, 0, 0xFF }, { 0xFF, 0xFF, 0 }, { 0xFF, 0xFF, 0xFF },
};

struct_8008E364_unk_0 D_8008E358 = {
    func_8003E430,
    func_8003E4AC,
    func_8003E4B4,
};

struct_8008E364 D_8008E364 = {
    &D_8008E358,
    &B_800E5890,
};

#endif

#if VERSION_US
void func_8003E1E0(Gfx **gfxP) {
    Gfx *gfx = *gfxP;

    gSPDisplayList(gfx++, D_8008E290);

    *gfxP = gfx;
}
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/screen_print/026000", func_800400C0_cn);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/screen_print/026000", func_8003EC70_gw);
#endif

void func_8003E208(Gfx **gfxP, s32 index) {
    Gfx *gfx = *gfxP;
    Color_RGB8 *color = &D_8008E340[index % 8U];

    gDPPipeSync(gfx++);
    gDPSetPrimColor(gfx++, 0, 0, color->r, color->g, color->b, 255);

    *gfxP = gfx;
}

void func_8003E278(Gfx **gfxP, s32 arg1, s32 arg2, s32 arg3);

#if VERSION_US
#if 0
void func_8003E278(Gfx **gfxP, s32 arg1, s32 arg2, s32 arg3) {
    Gfx *gfx = *gfxP;

    gSPScisTextureRectangle(gfx++, arg1 + 6, arg2 + 8, arg1, arg2, G_TX_RENDERTILE, arg3 % 26, arg3 / 26, 0x0400, 0x0400);

    *gfxP = gfx;
#if 0
    Gfx *temp_t1;
    Gfx *temp_t1_2;
    Gfx *temp_t1_3;
    s16 temp_a1;
    s32 temp_a0;
    s32 temp_a2;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v1;
    s32 var_a0;
    s32 var_v0;

    temp_t1 = *gfxP;
    temp_v0 = arg1 + 6;
    temp_v0_2 = arg2 + 8;
    temp_a1 = arg1 * 4;
    temp_t1_2 = temp_t1 + 8;
    temp_t1_3 = temp_t1_2 + 8;
    temp_t1->words.w0 = (((temp_v0 * 4) & ((s32) ~(s16) (temp_v0 * 4) >> 0x1F) & 0xFFC) << 0xC) | (((temp_v0_2 * 4) & ((s32) ~(s16) (temp_v0_2 * 4) >> 0x1F) & 0xFFC) | 0xE4000000);
    temp_t1->words.w1 = (((arg1 * 4) & ((s32) ~temp_a1 >> 0x1F) & 0xFFC) << 0xC) | ((arg2 * 4) & ((s32) ~(s16) (arg2 * 4) >> 0x1F) & 0xFFC);
    temp_t1_2->words.w0 = 0xE1000000;
    temp_a0 = (arg3 % 26) * 0xC0;
    temp_a2 = (arg3 / 26) << 8;
    if (temp_a1 < 0) {
        temp_v1 = temp_a1 * 8;
        var_a0 = (temp_a0 - (temp_v1 & -(temp_v1 < 1))) << 0x10;
    } else {
        var_a0 = temp_a0 << 0x10;
    }
    if (!(arg2 & 0x20000000)) {
        var_v0 = temp_a2 & 0xFFFF;
    } else {
        temp_v0_3 = (s32) (arg2 << 0x12) >> 0xD;
        var_v0 = (temp_a2 - (temp_v0_3 & -(temp_v0_3 < 1))) & 0xFFFF;
    }
    temp_t1_2->words.w1 = var_a0 | var_v0;
    temp_t1_3->words.w0 = 0xF1000000;
    temp_t1_3->words.w1 = 0x04000400;
    *gfxP = temp_t1_3 + 8;
#endif
}
#else
INCLUDE_ASM("asm/us/nonmatchings/main_segment/screen_print/026000", func_8003E278);
#endif
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/screen_print/026000", func_80040158_cn);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/screen_print/026000", func_8003ED08_gw);
#endif

#if VERSION_US
void func_8003E3F0(Gfx **gfxP, s32 arg1, s32 arg2, s32 character) {
    s8 val = -1;

    if (character - 0x20 - 1 >= 0xC0U - 1) {
        return;
    }

    if (D_8008E1D0[character - 0x20] != val) {
        func_8003E278(gfxP, arg1, arg2, D_8008E1D0[character - 0x20]);
    }
}
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/screen_print/026000", func_8003E3F0);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/screen_print/026000", func_8003E3F0);
#endif

#if VERSION_US
s32 func_8003E430(struct_8008E364 *arg0, va_list args) {
    struct_8008E364_unk_4 *ptr = arg0->unk_4;

    ptr->gfxP = va_arg(args, Gfx **);
    ptr->unk_04 = va_arg(args, struct_8008E364_unk_4_unk_04);
    ptr->unk_08 = va_arg(args, UNK_TYPE);
    ptr->unk_0A = va_arg(args, UNK_TYPE);

    ptr->unk_0C = 0;
    ptr->unk_0E = 0;
    ptr->unk_10 = 0;

    if (ptr->gfxP != NULL) {
        func_8003E1E0(ptr->gfxP);
    }

    return 0;
}
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/screen_print/026000", func_800402F8_cn);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/screen_print/026000", func_8003EEC0_gw);
#endif

#if VERSION_US
s32 func_8003E4AC(void) {
    return 0;
}
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/screen_print/026000", func_80040388_cn);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/screen_print/026000", func_8003EF3C_gw);
#endif

#if VERSION_US
s32 func_8003E4B4(struct_8008E364 *arg0, char *arg1, size_t arg2) {
    s32 var_s3 = arg2;
    struct_8008E364_unk_4 *temp_s0 = arg0->unk_4;

    while (var_s3 > 0) {
        s32 temp_v1;
        s32 temp_s1;

        var_s3--;
        temp_v1 = temp_s0->unk_10;
        temp_s1 = *arg1++;

        switch (temp_v1) {
            case '@':
                switch (temp_s1) {
                    case 'c':
                    case 'm':
                        temp_s0->unk_10 = temp_s1;
                        break;

                    default:
                        temp_s0->unk_10 = 0;
                        break;
                }
                break;

            case 'c':
                if (temp_s0->gfxP != NULL) {
                    func_8003E208(temp_s0->gfxP, temp_s1 - '0');
                }
                temp_s0->unk_10 = 0xFF;
                break;

            case 'm':
                if (temp_s0->unk_04 != NULL) {
                    temp_s0->unk_04(temp_s0->gfxP, temp_s0->unk_08 + (temp_s0->unk_0C * 6),
                                    temp_s0->unk_0A + (temp_s0->unk_0E * 8), temp_s1);
                }
                temp_s0->unk_10 = 0xFF;
                break;

            default:
                temp_s0->unk_10 = '\0';
                break;
        }

        if (temp_s0->unk_10 == '\0') {
            if (temp_s1 == '@') {
                temp_s0->unk_10 = temp_s1;
            } else if (temp_s1 < ' ') {
                switch (temp_s1) {
                    case '\t':
                        temp_s0->unk_0C = (temp_s0->unk_0C + 4) & ~3;
                        break;

                    case '\n':
                        temp_s0->unk_0C = 0;
                        temp_s0->unk_0E++;
                        break;
                }
            } else {
                if (temp_s0->gfxP != NULL) {
                    func_8003E3F0(temp_s0->gfxP, temp_s0->unk_08 + temp_s0->unk_0C * 6,
                                  temp_s0->unk_0A + temp_s0->unk_0E * 8, temp_s1);
                }
                temp_s0->unk_0C++;
            }
        }
    }
    return arg2;
}
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/screen_print/026000", func_80040390_cn);
#endif

#if VERSION_GW
INCLUDE_ASM("asm/gw/nonmatchings/main_segment/screen_print/026000", func_8003EF44_gw);
#endif

s32 func_8003E69C(Gfx **gfxP, func_8003E69C_arg1 arg1, s32 arg2, s32 arg3) {
    return func_8003CDA0(&D_8008E364, gfxP, arg1, arg2, arg3);
}

void func_8003E6D8(void) {
    func_8003CDD4(&D_8008E364);
}

void func_8003E6F8(const char *fmt UNUSED, ...) {
#if VERSION_US || VERSION_GW
    va_list args;

    va_start(args, fmt);

    func_8003D6D0(&D_8008E364, fmt, args);

    va_end(args);
#endif
}

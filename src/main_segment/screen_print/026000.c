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

#if VERSION_US
void func_8003E278(Gfx **gfxP, s32 arg1, s32 arg2, s32 arg3) {
    Gfx *gfx = *gfxP;
    s32 s UNUSED = (arg3 % 26) * 0xC0;
    s32 t UNUSED = (arg3 / 26) * 0x100;

    gSPScisTextureRectangle(gfx++, arg1 * 4, arg2 * 4, (arg1 + 6) * 4, (arg2 + 8) * 4, G_TX_RENDERTILE,
                            (arg3 % 26) * 0xC0, (arg3 / 26) * 0x100, 0x0400, 0x0400);

    *gfxP = gfx;
}
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
s32 func_8003E4B4(struct_8008E364 *arg0, char *arg1, s32 arg2) {
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

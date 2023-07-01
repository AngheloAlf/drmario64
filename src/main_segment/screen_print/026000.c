#include "libultra.h"
#include "include_asm.h"
#include "macros_defines.h"
#include "unknown_structs.h"
#include "main_segment_functions.h"
#include "main_segment_variables.h"
#include "screen_print/026000.h"
#include "screen_print/printf_impl.h"

extern struct_8008E364_unk_4 B_800E5890;

u8 D_8008D2D0[] = {
#include "main_segment/screen_print/026000/D_8008D2D0.i4.inc"
};

#define FONT_COLS_PER_ROW (26)

#define D_8008E1D0_VALUE(s, t) ((((s) + (t) / FONT_COLS_PER_ROW) * FONT_COLS_PER_ROW) + ((t) % FONT_COLS_PER_ROW))

#if VERSION_US || VERSION_GW
#define D_8008E1D0_TYPE u8
#else
#define D_8008E1D0_TYPE s8
#endif

D_8008E1D0_TYPE D_8008E1D0[] = {
    /* 0x20 ' '  */ -1,
    /* 0x21 '!'  */ -1,
    /* 0x22 '"'  */ -1,
    /* 0x23 '#'  */ -1,
    /* 0x24 '$'  */ -1,
    /* 0x25 '%'  */ D_8008E1D0_VALUE(2, 14),
    /* 0x26 '&'  */ D_8008E1D0_VALUE(2, 11),
    /* 0x27 '\'' */ D_8008E1D0_VALUE(2, 24),
    /* 0x28 '('  */ -1,
    /* 0x29 ')'  */ -1,
    /* 0x2A '*'  */ -1,
    /* 0x2B '+'  */ -1,
    /* 0x2C ','  */ D_8008E1D0_VALUE(4, 21),
    /* 0x2D '-'  */ D_8008E1D0_VALUE(2, 10),
    /* 0x2E '.'  */ D_8008E1D0_VALUE(4, 22),
    /* 0x2F '/'  */ D_8008E1D0_VALUE(2, 23),
    /* 0x30 '0'  */ D_8008E1D0_VALUE(2, 0),
    /* 0x31 '1'  */ D_8008E1D0_VALUE(2, 1),
    /* 0x32 '2'  */ D_8008E1D0_VALUE(2, 2),
    /* 0x33 '3'  */ D_8008E1D0_VALUE(2, 3),
    /* 0x34 '4'  */ D_8008E1D0_VALUE(2, 4),
    /* 0x35 '5'  */ D_8008E1D0_VALUE(2, 5),
    /* 0x36 '6'  */ D_8008E1D0_VALUE(2, 6),
    /* 0x37 '7'  */ D_8008E1D0_VALUE(2, 7),
    /* 0x38 '8'  */ D_8008E1D0_VALUE(2, 8),
    /* 0x39 '9'  */ D_8008E1D0_VALUE(2, 9),
    /* 0x3A ':'  */ D_8008E1D0_VALUE(2, 13),
    /* 0x3B ';'  */ -1,
    /* 0x3C '<'  */ D_8008E1D0_VALUE(2, 21),
    /* 0x3D '='  */ -1,
    /* 0x3E '>'  */ D_8008E1D0_VALUE(2, 18),
    /* 0x3F '?'  */ D_8008E1D0_VALUE(2, 22),
    /* 0x40 '@'  */ -1,
    /* 0x41 'A'  */ D_8008E1D0_VALUE(0, 0),
    /* 0x42 'B'  */ D_8008E1D0_VALUE(0, 1),
    /* 0x43 'C'  */ D_8008E1D0_VALUE(0, 2),
    /* 0x44 'D'  */ D_8008E1D0_VALUE(0, 3),
    /* 0x45 'E'  */ D_8008E1D0_VALUE(0, 4),
    /* 0x46 'F'  */ D_8008E1D0_VALUE(0, 5),
    /* 0x47 'G'  */ D_8008E1D0_VALUE(0, 6),
    /* 0x48 'H'  */ D_8008E1D0_VALUE(0, 7),
    /* 0x49 'I'  */ D_8008E1D0_VALUE(0, 8),
    /* 0x4A 'J'  */ D_8008E1D0_VALUE(0, 9),
    /* 0x4B 'K'  */ D_8008E1D0_VALUE(0, 10),
    /* 0x4C 'L'  */ D_8008E1D0_VALUE(0, 11),
    /* 0x4D 'M'  */ D_8008E1D0_VALUE(0, 12),
    /* 0x4E 'N'  */ D_8008E1D0_VALUE(0, 13),
    /* 0x4F 'O'  */ D_8008E1D0_VALUE(0, 14),
    /* 0x50 'P'  */ D_8008E1D0_VALUE(0, 15),
    /* 0x51 'Q'  */ D_8008E1D0_VALUE(0, 16),
    /* 0x52 'R'  */ D_8008E1D0_VALUE(0, 17),
    /* 0x53 'S'  */ D_8008E1D0_VALUE(0, 18),
    /* 0x54 'T'  */ D_8008E1D0_VALUE(0, 19),
    /* 0x55 'U'  */ D_8008E1D0_VALUE(0, 20),
    /* 0x56 'V'  */ D_8008E1D0_VALUE(0, 21),
    /* 0x57 'W'  */ D_8008E1D0_VALUE(0, 22),
    /* 0x58 'X'  */ D_8008E1D0_VALUE(0, 23),
    /* 0x59 'Y'  */ D_8008E1D0_VALUE(0, 24),
    /* 0x5A 'Z'  */ D_8008E1D0_VALUE(0, 25),
    /* 0x5B '['  */ D_8008E1D0_VALUE(2, 16),
    /* 0x5C '\\' */ -1,
    /* 0x5D ']'  */ D_8008E1D0_VALUE(2, 17),
    /* 0x5E '^'  */ D_8008E1D0_VALUE(2, 12),
    /* 0x5F '_'  */ -1,
    /* 0x60 '`'  */ -1,
    /* 0x61 'a'  */ D_8008E1D0_VALUE(1, 0),
    /* 0x62 'b'  */ D_8008E1D0_VALUE(1, 1),
    /* 0x63 'c'  */ D_8008E1D0_VALUE(1, 2),
    /* 0x64 'd'  */ D_8008E1D0_VALUE(1, 3),
    /* 0x65 'e'  */ D_8008E1D0_VALUE(1, 4),
    /* 0x66 'f'  */ D_8008E1D0_VALUE(1, 5),
    /* 0x67 'g'  */ D_8008E1D0_VALUE(1, 6),
    /* 0x68 'h'  */ D_8008E1D0_VALUE(1, 7),
    /* 0x69 'i'  */ D_8008E1D0_VALUE(1, 8),
    /* 0x6A 'j'  */ D_8008E1D0_VALUE(1, 9),
    /* 0x6B 'k'  */ D_8008E1D0_VALUE(1, 10),
    /* 0x6C 'l'  */ D_8008E1D0_VALUE(1, 11),
    /* 0x6D 'm'  */ D_8008E1D0_VALUE(1, 12),
    /* 0x6E 'n'  */ D_8008E1D0_VALUE(1, 13),
    /* 0x6F 'o'  */ D_8008E1D0_VALUE(1, 14),
    /* 0x70 'p'  */ D_8008E1D0_VALUE(1, 15),
    /* 0x71 'q'  */ D_8008E1D0_VALUE(1, 16),
    /* 0x72 'r'  */ D_8008E1D0_VALUE(1, 17),
    /* 0x73 's'  */ D_8008E1D0_VALUE(1, 18),
    /* 0x74 't'  */ D_8008E1D0_VALUE(1, 19),
    /* 0x75 'u'  */ D_8008E1D0_VALUE(1, 20),
    /* 0x76 'v'  */ D_8008E1D0_VALUE(1, 21),
    /* 0x77 'w'  */ D_8008E1D0_VALUE(1, 22),
    /* 0x78 'x'  */ D_8008E1D0_VALUE(1, 23),
    /* 0x79 'y'  */ D_8008E1D0_VALUE(1, 24),
    /* 0x7A 'z'  */ D_8008E1D0_VALUE(1, 25),
    /* 0x7B '{'  */ -1,
    /* 0x7C '|'  */ -1,
    /* 0x7D '}'  */ -1,
    /* 0x7E '~'  */ D_8008E1D0_VALUE(2, 15),
    /* 0x7F ''   */ -1,
    /* 0x80 ''   */ D_8008E1D0_VALUE(5, 9),
    /* 0x81 ''   */ D_8008E1D0_VALUE(5, 10),
    /* 0x82 ''   */ D_8008E1D0_VALUE(5, 12),
    /* 0x83 ''   */ D_8008E1D0_VALUE(5, 11),
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
    /* 0xA1 ''   */ D_8008E1D0_VALUE(4, 22),
    /* 0xA2 ''   */ -1,
    /* 0xA3 ''   */ -1,
    /* 0xA4 ''   */ D_8008E1D0_VALUE(4, 21),
    /* 0xA5 ''   */ D_8008E1D0_VALUE(2, 20),
    /* 0xA6 ''   */ D_8008E1D0_VALUE(4, 19),
    /* 0xA7 ''   */ D_8008E1D0_VALUE(5, 0),
    /* 0xA8 ''   */ D_8008E1D0_VALUE(5, 1),
    /* 0xA9 ''   */ D_8008E1D0_VALUE(5, 2),
    /* 0xAA ''   */ D_8008E1D0_VALUE(5, 3),
    /* 0xAB ''   */ D_8008E1D0_VALUE(5, 4),
    /* 0xAC ''   */ D_8008E1D0_VALUE(5, 6),
    /* 0xAD ''   */ D_8008E1D0_VALUE(5, 7),
    /* 0xAE ''   */ D_8008E1D0_VALUE(5, 8),
    /* 0xAF ''   */ D_8008E1D0_VALUE(5, 5),
    /* 0xB0 ''   */ D_8008E1D0_VALUE(2, 19),
    /* 0xB1 ''   */ D_8008E1D0_VALUE(3, 0),
    /* 0xB2 ''   */ D_8008E1D0_VALUE(3, 1),
    /* 0xB3 ''   */ D_8008E1D0_VALUE(3, 2),
    /* 0xB4 ''   */ D_8008E1D0_VALUE(3, 3),
    /* 0xB5 ''   */ D_8008E1D0_VALUE(3, 4),
    /* 0xB6 ''   */ D_8008E1D0_VALUE(3, 5),
    /* 0xB7 ''   */ D_8008E1D0_VALUE(3, 6),
    /* 0xB8 ''   */ D_8008E1D0_VALUE(3, 7),
    /* 0xB9 ''   */ D_8008E1D0_VALUE(3, 8),
    /* 0xBA ''   */ D_8008E1D0_VALUE(3, 9),
    /* 0xBB ''   */ D_8008E1D0_VALUE(3, 10),
    /* 0xBC ''   */ D_8008E1D0_VALUE(3, 11),
    /* 0xBD ''   */ D_8008E1D0_VALUE(3, 12),
    /* 0xBE ''   */ D_8008E1D0_VALUE(3, 13),
    /* 0xBF ''   */ D_8008E1D0_VALUE(3, 14),
    /* 0xC0 ''   */ D_8008E1D0_VALUE(3, 15),
    /* 0xC1 ''   */ D_8008E1D0_VALUE(3, 16),
    /* 0xC2 ''   */ D_8008E1D0_VALUE(3, 17),
    /* 0xC3 ''   */ D_8008E1D0_VALUE(3, 18),
    /* 0xC4 ''   */ D_8008E1D0_VALUE(3, 19),
    /* 0xC5 ''   */ D_8008E1D0_VALUE(3, 20),
    /* 0xC6 ''   */ D_8008E1D0_VALUE(3, 21),
    /* 0xC7 ''   */ D_8008E1D0_VALUE(3, 22),
    /* 0xC8 ''   */ D_8008E1D0_VALUE(3, 23),
    /* 0xC9 ''   */ D_8008E1D0_VALUE(3, 24),
    /* 0xCA ''   */ D_8008E1D0_VALUE(4, 0),
    /* 0xCB ''   */ D_8008E1D0_VALUE(4, 1),
    /* 0xCC ''   */ D_8008E1D0_VALUE(4, 2),
    /* 0xCD ''   */ D_8008E1D0_VALUE(4, 3),
    /* 0xCE ''   */ D_8008E1D0_VALUE(4, 4),
    /* 0xCF ''   */ D_8008E1D0_VALUE(4, 5),
    /* 0xD0 ''   */ D_8008E1D0_VALUE(4, 6),
    /* 0xD1 ''   */ D_8008E1D0_VALUE(4, 7),
    /* 0xD2 ''   */ D_8008E1D0_VALUE(4, 8),
    /* 0xD3 ''   */ D_8008E1D0_VALUE(4, 9),
    /* 0xD4 ''   */ D_8008E1D0_VALUE(4, 10),
    /* 0xD5 ''   */ D_8008E1D0_VALUE(4, 11),
    /* 0xD6 ''   */ D_8008E1D0_VALUE(4, 12),
    /* 0xD7 ''   */ D_8008E1D0_VALUE(4, 13),
    /* 0xD8 ''   */ D_8008E1D0_VALUE(4, 14),
    /* 0xD9 ''   */ D_8008E1D0_VALUE(4, 15),
    /* 0xDA ''   */ D_8008E1D0_VALUE(4, 16),
    /* 0xDB ''   */ D_8008E1D0_VALUE(4, 17),
    /* 0xDC '\ ' */ D_8008E1D0_VALUE(4, 18),
    /* 0xDD ''   */ D_8008E1D0_VALUE(4, 20),
    /* 0xDE ''   */ D_8008E1D0_VALUE(4, 23),
    /* 0xDF ''   */ D_8008E1D0_VALUE(4, 24),
};

Gfx D_8008E290[] = {
#include "main_segment/screen_print/026000/D_8008E290.gfx.inc.c"
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

struct_8008E364_unk_0 D_8008E358 = {
    func_8003E430,
    func_8003E4AC,
    func_8003E4B4,
};

struct_8008E364 D_8008E364 = {
    &D_8008E358,
    &B_800E5890,
};

void func_8003E1E0(Gfx **gfxP) {
    Gfx *gfx = *gfxP;

    gSPDisplayList(gfx++, D_8008E290);

    *gfxP = gfx;
}

void func_8003E208(Gfx **gfxP, s32 index) {
    Gfx *gfx = *gfxP;
    Color_RGB8 *color = &D_8008E340[index % ARRAY_COUNTU(D_8008E340)];

    gDPPipeSync(gfx++);
    gDPSetPrimColor(gfx++, 0, 0, color->r, color->g, color->b, 255);

    *gfxP = gfx;
}

#if VERSION_US || VERSION_GW
void func_8003E278(Gfx **gfxP, s32 arg1, s32 arg2, s32 arg3) {
    Gfx *gfx = *gfxP;
    //! FAKE:
    s32 s UNUSED = (arg3 % FONT_COLS_PER_ROW) * 0xC0;
    s32 t UNUSED = (arg3 / FONT_COLS_PER_ROW) * 0x100;

    gSPScisTextureRectangle(gfx++, arg1 * 4, arg2 * 4, (arg1 + 6) * 4, (arg2 + 8) * 4, G_TX_RENDERTILE,
                            (arg3 % FONT_COLS_PER_ROW) * 0xC0, (arg3 / FONT_COLS_PER_ROW) * 0x100, 0x0400, 0x0400);

    *gfxP = gfx;
}
#endif

#if VERSION_CN
void func_8003E278(Gfx **gfxP, s32 arg1, s32 arg2, s32 arg3) {
    Gfx *gfx = *gfxP;
    s32 s = (arg3 % FONT_COLS_PER_ROW) * 0xC0;
    s32 t = (arg3 / FONT_COLS_PER_ROW) * 0x100;

    gSPScisTextureRectangle(gfx++, arg1 * 4, arg2 * 4, (arg1 + 6) * 4, (arg2 + 8) * 4, G_TX_RENDERTILE, s, t, 0x0400,
                            0x0400);

    *gfxP = gfx;
}
#endif

void func_8003E3F0(Gfx **gfxP, s32 arg1, s32 arg2, s32 character) {
    if (character - 0x20 - 1 < ARRAY_COUNTU(D_8008E1D0) - 1) {
        s32 val = D_8008E1D0[character - 0x20];

        if (val != -1) {
            func_8003E278(gfxP, arg1, arg2, val);
        }
    }
}

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

s32 func_8003E4AC(void) {
    return 0;
}

s32 func_8003E4B4(struct_8008E364 *arg0, char *arg1, size_t arg2) {
    s32 var_s3 = arg2;
    struct_8008E364_unk_4 *temp_s0 = arg0->unk_4;

    while (var_s3 > 0) {
        s32 temp_s1;

        var_s3--;
        temp_s1 = *arg1++;

        switch (temp_s0->unk_10) {
            case '@':
                switch (temp_s1) {
                    case 'c':
                    case 'm':
                        temp_s0->unk_10 = temp_s1;
                        break;

                    default:
                        temp_s0->unk_10 = '\0';
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

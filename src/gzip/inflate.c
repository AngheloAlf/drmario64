#include "gzip.h"
#include "include_asm.h"
#include "macros_defines.h"
#include "attributes.h"

typedef struct huft {
    /* 0x0 */ unsigned char e;
    /* 0x1 */ unsigned char b;
    /* 0x4 */ union {
        unsigned short n;
        struct huft *t;
    } v;
} huft; // size = 0x8

s32 huft_free(huft *arg0);

extern u16 cplens[];
extern u16 cplext[];
extern u16 cpdist[];
extern u16 cpdext[];

extern u16 mask_bits[];

extern u32 border[];
extern s32 lbits;
extern s32 dbits;

extern s32 gzip_malloc_tmp;
extern void *gzip_malloc_addr;

/**
 * Original name: gzip_mem_buff
 */
extern u8 gzip_mem_buff[];

/**
 * Original name: bk
 */
extern u32 bk;
/**
 * Original name: bb
 */
extern u32 bb;
/**
 * Original name: hufts
 */
extern u32 hufts;

#if VERSION_US || VERSION_CN
/**
 * Original name: border
 */
u32 border[0x13] = {
    0x10, 0x11, 0x12, 0, 8, 7, 9, 6, 0xA, 5, 0xB, 4, 0xC, 3, 0xD, 2, 0xE, 1, 0xF,
};

/**
 * Original name: cplens
 */
u16 cplens[0x20] = {
    3,    4,    5,    6,    7,    8,    9,    0xA,  0xB,  0xD,  0xF,  0x11, 0x13,  0x17, 0x1B, 0x1F,
    0x23, 0x2B, 0x33, 0x3B, 0x43, 0x53, 0x63, 0x73, 0x83, 0xA3, 0xC3, 0xE3, 0x102, 0,    0,    0,
};

/**
 * Original name: cplext
 */
u16 cplext[0x20] = {
    0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 0, 0x63, 0x63, 0,
};

/**
 * Original name: cpdist
 */
u16 cpdist[0x1E] = {
    1,    2,     3,     4,     5,     7,     9,     0xD,   0x11,  0x19,   0x21,   0x31,   0x41,   0x61,   0x81,
    0xC1, 0x101, 0x181, 0x201, 0x301, 0x401, 0x601, 0x801, 0xC01, 0x1001, 0x1801, 0x2001, 0x3001, 0x4001, 0x6001,
};

/**
 * Original name: cpdext
 */
u16 cpdext[0x1E] = {
    0, 0, 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 0xA, 0xA, 0xB, 0xB, 0xC, 0xC, 0xD, 0xD,
};

/**
 * Original name: mask_bits
 */
u16 mask_bits[] = {
    0, 1, 3, 7, 0xF, 0x1F, 0x3F, 0x7F, 0xFF, 0x1FF, 0x3FF, 0x7FF, 0xFFF, 0x1FFF, 0x3FFF, 0x7FFF, 0xFFFF,
};

/**
 * Original name: lbits
 */
s32 lbits = 9;

/**
 * Original name: dbits
 */
s32 dbits = 6;

/**
 * Original name: gzip_malloc_addr
 */
void *gzip_malloc_addr = gzip_mem_buff;

/**
 * Original name: gzip_malloc_tmp
 */
s32 gzip_malloc_tmp = 0;
#endif

#if VERSION_US || VERSION_CN
void *func_80000720(size_t size) {
    void *ret;

    gzip_malloc_tmp += size;
    if (gzip_malloc_tmp > 0x4000) {
        return NULL;
    }

    ret = gzip_malloc_addr;
    gzip_malloc_addr = (void *)(((uintptr_t)gzip_malloc_addr) + size);
    return ret;
}
#endif

#if VERSION_US || VERSION_CN
void func_8000075C(void *arg UNUSED) {
    gzip_malloc_tmp = 0;
    gzip_malloc_addr = gzip_mem_buff;
}
#endif

#if VERSION_US || VERSION_CN
/**
 * Original name: huft_build
 */
s32 huft_build(u32 *arg0, u32 arg1, u32 arg2, u16 *arg3, u16 *arg4, huft **arg5, s32 *arg6) {
    u32 var_t2;      // a
    u32 sp18[17];    // c
    u32 var_a0;      // f
    s32 sp5AC;       // g
    s32 var_t1;      // h
    u32 var_s1_2;    // i
    u32 var_s0_2;    // j
    s32 var_t3;      // k
    s32 var_a3;      // l
    u32 *var_s4;     // p
    huft *temp_v0_3; // q
    huft sp60;       // r
    huft *sp68[16];  // u
    u32 spA8[288];   // v
    s32 var_s5;      // w
    u32 sp528[17];   // x
    u32 *var_a1;     // xp
    s32 var_t5;      // y
    u32 var_s3;      // z

    for (var_s0_2 = 0; var_s0_2 < 0x11U; var_s0_2++) {
        sp18[var_s0_2] = 0;
    }

    var_s4 = arg0;
    var_s1_2 = arg1;
    do {
        sp18[*var_s4] += 1;
        var_s4++;
        var_s1_2--;
    } while (var_s1_2 != 0);

    if (sp18[0] == arg1) {
        *arg5 = NULL;
        *arg6 = 0;
        return 0;
    }

    var_a3 = *arg6;
    for (var_s0_2 = 1; var_s0_2 < 0x11U; var_s0_2++) {
        if (sp18[var_s0_2] != 0) {
            break;
        }
    }

    var_t3 = var_s0_2;
    if (var_a3 < var_s0_2) {
        var_a3 = var_s0_2;
    }

    for (var_s1_2 = 0x10; var_s1_2 != 0; var_s1_2--) {
        if (sp18[var_s1_2] != 0) {
            break;
        }
    }

    sp5AC = var_s1_2;
    if (var_s1_2 < var_a3) {
        var_a3 = var_s1_2;
    }

    *arg6 = var_a3;

    for (var_t5 = 1 << var_s0_2; var_s0_2 < var_s1_2; var_s0_2++, var_t5 <<= 1) {
        var_t5 -= sp18[var_s0_2];
        if (var_t5 < 0) {
            return 2;
        }
    }

    var_t5 -= sp18[var_s1_2];
    if (var_t5 < 0) {
        return 2;
    }
    sp18[var_s1_2] += var_t5;

    var_s0_2 = 0;
    sp528[1] = 0;

    var_s4 = &sp18[1];
    var_a1 = &sp528[2];
    var_s1_2 = var_s1_2 - 1;

    while (var_s1_2 != 0) {
        var_s0_2 += *var_s4++;
        *var_a1++ = var_s0_2;
        var_s1_2 -= 1;
    }

    var_s4 = arg0;
    var_s1_2 = 0;
    do {
        var_s0_2 = *var_s4++;
        if (var_s0_2 != 0) {
            spA8[sp528[var_s0_2]++] = var_s1_2;
        }
        var_s1_2 += 1;
    } while (var_s1_2 < arg1);

    var_s1_2 = 0;
    sp528[0] = 0;
    var_s4 = spA8;
    var_t1 = -1;
    var_s5 = -var_a3;
    sp68[0] = NULL;
    temp_v0_3 = NULL;
    var_s3 = 0;

    for (; var_t3 <= sp5AC; var_t3++) {
        var_t2 = sp18[var_t3];
        var_t2--;

        for (; var_t2 != -1; var_t2--) {
            while (var_t3 > var_s5 + var_a3) {
                var_t1++;
                var_s5 += var_a3;

                var_s3 = sp5AC - var_s5;

                var_s3 = (var_s3 > var_a3) ? var_a3 : var_s3;

                var_s0_2 = var_t3 - var_s5;
                var_a0 = 1 << var_s0_2;

                if (var_a0 > var_t2 + 1) {
                    var_a0 -= var_t2 + 1;
                    var_s0_2 += 1;
                    var_a1 = &sp18[var_t3];
                    while (var_s0_2 < var_s3) {
                        var_a0 <<= 1;
                        if (var_a0 <= *++var_a1) {
                            break;
                        }
                        var_a0 -= *var_a1;
                        var_s0_2 += 1;
                    }
                }

                var_s3 = 1 << var_s0_2;

                temp_v0_3 = func_80000720((var_s3 + 1) * sizeof(huft));
                if (temp_v0_3 == NULL) {
                    if (var_t1 != 0) {
                        huft_free(sp68[0]);
                    }
                    return 3;
                }

                hufts += var_s3 + 1;

                *arg5 = &temp_v0_3[1];
                arg5 = &temp_v0_3->v.t;
                temp_v0_3->v.t = NULL;

                sp68[var_t1] = ++temp_v0_3;

                if (var_t1 != 0) {
                    sp528[var_t1] = var_s1_2;

                    sp60.b = var_a3;
                    sp60.e = var_s0_2 + 0x10;
                    sp60.v.t = temp_v0_3;

                    var_s0_2 = var_s1_2 >> (var_s5 - var_a3);
                    sp68[var_t1 - 1][var_s0_2] = sp60;
                }
            }

            sp60.b = var_t3 - var_s5;
            if (var_s4 >= &spA8[arg1]) {
                sp60.e = 0x63;
            } else if (*var_s4 < arg2) {
                sp60.e = (*var_s4 < 0x100 ? 0x10 : 0xF);
                sp60.v.n = *var_s4;
                var_s4++;
            } else {
                sp60.e = arg4[*var_s4 - arg2];
                sp60.v.n = arg3[*var_s4 - arg2];
                var_s4++;
            }

            var_a0 = 1 << (var_t3 - var_s5);
            for (var_s0_2 = var_s1_2 >> var_s5; var_s0_2 < var_s3; var_s0_2 += var_a0) {
                temp_v0_3[var_s0_2] = sp60;
            }

            for (var_s0_2 = 1 << (var_t3 - 1); var_s1_2 & var_s0_2; var_s0_2 = var_s0_2 >> 1) {
                var_s1_2 ^= var_s0_2;
            }
            var_s1_2 ^= var_s0_2;

            while ((var_s1_2 & ((1 << var_s5) - 1)) != sp528[var_t1]) {
                var_t1--;
                var_s5 -= var_a3;
            }
        }
    }

    return ((var_t5 != 0) && (sp5AC != 1)) ? 1 : 0;
}
#endif

#if VERSION_US || VERSION_CN
/**
 * Original name: huft_free
 */
s32 huft_free(huft *arg0) {
    huft *temp_s0;

    while (arg0 != NULL) {
        arg0--;

        temp_s0 = arg0->v.t;
        func_8000075C(arg0);
        arg0 = temp_s0;
    }
    return 0;
}
#endif

#if VERSION_US || VERSION_CN
/**
 * Original name: inflate_codes
 */
s32 inflate_codes(huft *arg0, huft *arg1, s32 arg2, s32 arg3) {
    u32 var_s0;   // e
    u32 var_s6;   // n
    u32 var_s2_3; // d
    u32 var_s4;   // w
    huft *var_s2; // t

    u32 sp18; // ml
    u32 sp1C; // md

    u32 var_s3; // b
    u32 var_s1; // k

    var_s3 = bb;
    var_s1 = bk;
    var_s4 = outcnt;

    sp18 = mask_bits[arg2];
    sp1C = mask_bits[arg3];

    for (;;) {
        while (var_s1 < arg2) {
            if (inptr < insize) {
                var_s3 |= inbuf[inptr++] << var_s1;
            } else {
                var_s3 |= (fill_inbuf(0) & 0xFF) << var_s1;
            }
            var_s1 += 8;
        }

        var_s2 = &arg0[var_s3 & sp18];

        if ((var_s0 = var_s2->e) >= 0x11U) {
            do {
                if (var_s0 == 0x63) {
                    return 1;
                }

                var_s3 >>= var_s2->b;
                var_s1 -= var_s2->b;

                var_s0 = var_s0 - 0x10;

                while (var_s1 < var_s0) {
                    if (inptr < insize) {
                        var_s3 |= inbuf[inptr++] << var_s1;
                    } else {
                        var_s3 |= (fill_inbuf(0) & 0xFF) << var_s1;
                    }
                    var_s1 += 8;
                }
                var_s2 = &var_s2->v.t[var_s3 & mask_bits[var_s0]];
            } while ((var_s0 = var_s2->e) >= 0x11U);
        }

        var_s3 >>= var_s2->b;
        var_s1 -= var_s2->b;

        if (var_s0 == 0x10) {
            window[var_s4++] = var_s2->v.n;
            if (var_s4 == 0x8000) {
                outcnt = var_s4;
                flush_window();
                var_s4 = 0;
            }
            continue;
        }

        if (var_s0 == 0xF) {
            break;
        }

        while (var_s1 < var_s0) {
            if (inptr < insize) {
                var_s3 |= inbuf[inptr++] << var_s1;
            } else {
                var_s3 |= (fill_inbuf(0) & 0xFF) << var_s1;
            }
            var_s1 += 8;
        }

        var_s6 = var_s2->v.n + (var_s3 & mask_bits[var_s0]);

        var_s3 >>= var_s0;
        var_s1 -= var_s0;

        while (var_s1 < arg3) {
            if (inptr < insize) {
                var_s3 |= inbuf[inptr++] << var_s1;
            } else {
                var_s3 |= (fill_inbuf(0) & 0xFF) << var_s1;
            }
            var_s1 += 8;
        }

        var_s2 = &arg1[var_s3 & sp1C];
        if ((var_s0 = var_s2->e) >= 0x11U) {
            do {
                if (var_s0 == 0x63) {
                    return 1;
                }

                var_s3 >>= var_s2->b;
                var_s1 -= var_s2->b;

                var_s0 = var_s0 - 0x10;

                while (var_s1 < var_s0) {
                    if (inptr < insize) {
                        var_s3 |= inbuf[inptr++] << var_s1;
                    } else {
                        var_s3 |= (fill_inbuf(0) & 0xFF) << var_s1;
                    }
                    var_s1 += 8;
                }

                var_s2 = &var_s2->v.t[var_s3 & mask_bits[var_s0]];
            } while ((var_s0 = var_s2->e) >= 0x11U);
        }

        var_s3 >>= var_s2->b;
        var_s1 -= var_s2->b;

        while (var_s1 < var_s0) {
            if (inptr < insize) {
                var_s3 |= inbuf[inptr++] << var_s1;
            } else {
                var_s3 |= (fill_inbuf(0) & 0xFF) << var_s1;
            }
            var_s1 += 8;
        }

        var_s2_3 = var_s4 - var_s2->v.n - (var_s3 & mask_bits[var_s0]);

        var_s3 >>= var_s0;
        var_s1 -= var_s0;

        do {
            var_s0 = (((var_s0 = 0x8000 - (((var_s2_3 &= 0x7FFF) > var_s4) ? var_s2_3 : var_s4)) > var_s6) ? var_s6
                                                                                                           : var_s0);
            var_s6 -= var_s0;

            do {
                window[var_s4++] = window[var_s2_3++];
                var_s0 -= 1;
            } while (var_s0 != 0);

            if (var_s4 == 0x8000) {
                outcnt = var_s4;
                flush_window();
                var_s4 = 0;
            }
        } while (var_s6 != 0);
    }

    outcnt = var_s4;
    bb = var_s3;
    bk = var_s1;

    return 0;
}
#endif

#if VERSION_US || VERSION_CN
/**
 * Original name: inflate_stored
 */
s32 inflate_stored(void) {
    s32 var_s2;
    u32 var_s0;
    u32 var_s1;
    u32 var_s4;

    var_s1 = bb;
    var_s0 = bk;
    var_s4 = outcnt;

    var_s2 = var_s0 & 7;
    var_s0 = var_s0 - var_s2;
    var_s1 = var_s1 >> var_s2;

    while (var_s0 < 0x10U) {
        if (inptr < insize) {
            var_s1 |= inbuf[inptr++] << var_s0;
        } else {
            var_s1 |= (fill_inbuf(0) & 0xFF) << var_s0;
        }
        var_s0 += 8;
    }

    var_s2 = var_s1 & 0xFFFF;
    var_s0 = var_s0 - 0x10;
    var_s1 = var_s1 >> 0x10;

    while (var_s0 < 0x10U) {
        if (inptr < insize) {
            var_s1 |= inbuf[inptr++] << var_s0;
        } else {
            var_s1 |= (fill_inbuf(0) & 0xFF) << var_s0;
        }
        var_s0 += 8;
    }

    if (var_s2 != (~var_s1 & 0xFFFF)) {
        return 1;
    }

    var_s1 = var_s1 >> 0x10;
    var_s0 = var_s0 - 0x10;
    var_s2 = var_s2 - 1;

    while (var_s2 != -1) {
        while (var_s0 < 8U) {
            if (inptr < insize) {
                var_s1 |= inbuf[inptr++] << var_s0;
            } else {
                var_s1 |= (fill_inbuf(0) & 0xFF) << var_s0;
            }
            var_s0 += 8;
        }

        window[var_s4++] = var_s1;
        if (var_s4 == 0x8000) {
            outcnt = var_s4;
            flush_window();
            var_s4 = 0;
        }

        var_s1 = var_s1 >> 8;
        var_s2 -= 1;
        var_s0 -= 8;
    }

    outcnt = var_s4;
    bb = var_s1;
    bk = var_s0;

    return 0;
}
#endif

#if VERSION_US || VERSION_CN
/**
 * Original name: inflate_fixed
 */
s32 inflate_fixed(void) {
    u32 sp28[0x120];
    huft *sp4A8;
    s32 sp4AC;
    huft *sp4B0;
    s32 sp4B4;
    s32 i;

    for (i = 0; i < 0x90; i++) {
        sp28[i] = 8;
    }
    for (; i < 0x100; i++) {
        sp28[i] = 9;
    }
    for (; i < 0x118; i++) {
        sp28[i] = 7;
    }
    for (; i < 0x120; i++) {
        sp28[i] = 8;
    }

    sp4AC = 7;
    i = huft_build(sp28, 0x120, 0x101, cplens, cplext, &sp4A8, &sp4AC);
    if (i != 0) {
        return i;
    }

    for (i = 0; i < 0x1E; i++) {
        sp28[i] = 5;
    }

    sp4B4 = 5;
    i = huft_build(sp28, 0x1E, 0, cpdist, cpdext, &sp4B0, &sp4B4);
    if (i >= 2) {
        huft_free(sp4A8);
        return i;
    }

    if (inflate_codes(sp4A8, sp4B0, sp4AC, sp4B4) != 0) {
        return 1;
    }

    huft_free(sp4B0);
    huft_free(sp4A8);
    return 0;
}
#endif

#if VERSION_US || VERSION_CN
/**
 * Original name: inflate_dynamic
 */
s32 inflate_dynamic(void) {
    s32 var_s3;    // i
    u32 var_s0;    // j
    u32 var_s5;    // l
    u32 sp538;     // m
    u32 temp_s6_2; // n
    huft *sp528;   // tl
    huft *sp530;   // td
    s32 sp52C;     // bl
    s32 sp534;     // bd
    u32 temp_s6;   // nb
    u32 sp53C;     // nl
    u32 sp540;     // nd
    u32 sp28[320]; // ll
    u32 var_s1;    // k
    u32 var_s2;    // b

    var_s1 = bk;
    var_s2 = bb;

    while (var_s1 < 5U) {
        if (inptr < insize) {
            var_s2 |= inbuf[inptr++] << var_s1;
        } else {
            var_s2 |= (fill_inbuf(0) & 0xFF) << var_s1;
        }
        var_s1 += 8;
    }

    sp53C = (var_s2 & 0x1F) + 0x101;

    var_s2 = var_s2 >> 5;
    var_s1 = var_s1 - 5;

    while (var_s1 < 5U) {
        if (inptr < insize) {
            var_s2 |= inbuf[inptr++] << var_s1;
        } else {
            var_s2 |= (fill_inbuf(0) & 0xFF) << var_s1;
        }
        var_s1 += 8;
    }

    sp540 = (var_s2 & 0x1F) + 1;

    var_s2 = var_s2 >> 5;
    var_s1 = var_s1 - 5;
    while (var_s1 < 4U) {
        if (inptr < insize) {
            var_s2 |= inbuf[inptr++] << var_s1;
        } else {
            var_s2 |= (fill_inbuf(0) & 0xFF) << var_s1;
        }
        var_s1 += 8;
    }

    temp_s6 = (var_s2 & 0xF) + 4;
    var_s2 = var_s2 >> 4;
    var_s1 = var_s1 - 4;

    if ((sp53C > 0x120U) || (sp540 > 0x20U)) {
        return 1;
    }

    for (var_s0 = 0; var_s0 < temp_s6; var_s0++) {
        while (var_s1 < 3U) {
            if (inptr < insize) {
                var_s2 |= inbuf[inptr++] << var_s1;
            } else {
                var_s2 |= (fill_inbuf(0) & 0xFF) << var_s1;
            }
            var_s1 += 8;
        }

        sp28[border[var_s0]] = var_s2 & 7;

        var_s2 >>= 3;
        var_s1 -= 3;
    }

    for (; var_s0 < 0x13U; var_s0++) {
        sp28[border[var_s0]] = 0;
    }

    sp52C = 7;
    var_s3 = huft_build(sp28, 0x13U, 0x13U, NULL, NULL, &sp528, &sp52C);
    if (var_s3 != 0) {
        if (var_s3 == 1) {
            huft_free(sp528);
        }
        return var_s3;
    }

    temp_s6_2 = sp53C + sp540;
    sp538 = mask_bits[sp52C];
    var_s5 = 0;
    var_s3 = 0;
    while (var_s3 < temp_s6_2) {
        while (var_s1 < sp52C) {
            if (inptr < insize) {
                var_s2 |= inbuf[inptr++] << var_s1;
            } else {
                var_s2 |= (fill_inbuf(0) & 0xFF) << var_s1;
            }
            var_s1 += 8;
        }

        sp530 = &sp528[var_s2 & sp538];
        var_s0 = sp530->b;

        var_s2 >>= var_s0;
        var_s1 -= var_s0;

        var_s0 = sp530->v.n;

        if (var_s0 < 0x10U) {
            var_s5 = var_s0;
            sp28[var_s3++] = var_s5;
        } else if (var_s0 == 0x10) {
            while (var_s1 < 2U) {
                if (inptr < insize) {
                    var_s2 |= inbuf[inptr++] << var_s1;
                } else {
                    var_s2 |= (fill_inbuf(0) & 0xFF) << var_s1;
                }
                var_s1 += 8;
            }

            var_s0 = 3 + (var_s2 & 3);

            var_s2 >>= 2;
            var_s1 -= 2;

            if (var_s3 + var_s0 > temp_s6_2) {
                return 1;
            }

            var_s0--;
            while (var_s0 != -1) {
                sp28[var_s3++] = var_s5;
                var_s0--;
            }
        } else if (var_s0 == 0x11) {
            while (var_s1 < 3U) {
                if (inptr < insize) {
                    var_s2 |= inbuf[inptr++] << var_s1;
                } else {
                    var_s2 |= (fill_inbuf(0) & 0xFF) << var_s1;
                }
                var_s1 += 8;
            }
            var_s0 = 3 + (var_s2 & 7);

            var_s2 = var_s2 >> 3;
            var_s1 -= 3;

            if (var_s3 + var_s0 > temp_s6_2) {
                return 1;
            }

            var_s0--;
            while (var_s0 != -1) {
                sp28[var_s3++] = 0;
                var_s0--;
            }
            var_s5 = 0;
        } else {

            while (var_s1 < 7U) {
                if (inptr < insize) {
                    var_s2 |= inbuf[inptr++] << var_s1;
                } else {
                    var_s2 |= (fill_inbuf(0) & 0xFF) << var_s1;
                }
                var_s1 += 8;
            }

            var_s0 = 11 + (var_s2 & 0x7F);

            var_s2 = var_s2 >> 7;
            var_s1 -= 7;
            if (var_s3 + var_s0 > temp_s6_2) {
                return 1;
            }

            var_s0--;
            while (var_s0 != -1) {
                sp28[var_s3++] = 0;
                var_s0--;
            }

            var_s5 = 0;
        }
    }

    huft_free(sp528);

    bb = var_s2;
    bk = var_s1;

    sp52C = lbits;
    var_s3 = huft_build(&sp28[0], sp53C, 0x101U, cplens, cplext, &sp528, &sp52C);
    if (var_s3 != 0) {
        if (var_s3 == 1) {
            huft_free(sp528);
        }
        return var_s3;
    }

    sp534 = dbits;
    var_s3 = huft_build(&sp28[sp53C], sp540, 0U, cpdist, cpdext, &sp530, &sp534);
    if (var_s3 != 0) {
        if (var_s3 == 1) {
            var_s3 = 0;
        }
    }

    if (inflate_codes(sp528, sp530, sp52C, sp534) != 0) {
        return 1;
    }

    huft_free(sp530);
    huft_free(sp528);
    return 0;
}
#endif

#if VERSION_US || VERSION_CN
/**
 * Original name: inflate_block
 */
s32 inflate_block(s32 *arg0) {
    s32 temp_v1;
    u32 var_s0;
    u32 var_s1;

    var_s1 = bb;
    var_s0 = bk;

    while (var_s0 == 0) {
        if (inptr < insize) {
            var_s1 |= inbuf[inptr++] << var_s0;
        } else {
            var_s1 |= (fill_inbuf(0) & 0xFF) << var_s0;
        }
        var_s0 += 8;
    }

    *arg0 = var_s1 & 1;

    var_s0 = var_s0 - 1;
    var_s1 = var_s1 >> 1;

    while (var_s0 < 2U) {
        if (inptr < insize) {
            var_s1 |= inbuf[inptr++] << var_s0;
        } else {
            var_s1 |= (fill_inbuf(0) & 0xFF) << var_s0;
        }
        var_s0 += 8;
    }

    temp_v1 = var_s1 & 3;

    var_s1 = var_s1 >> 2;
    var_s0 = var_s0 - 2;

    bb = var_s1;
    bk = var_s0;

    if (temp_v1 == 2) {
        return inflate_dynamic();
    }
    if (temp_v1 == 0) {
        return inflate_stored();
    }
    if (temp_v1 == 1) {
        return inflate_fixed();
    }
    return 2;
}
#endif

#if VERSION_US || VERSION_CN
/**
 * Original name: inflate
 */
s32 inflate(void) {
    s32 sp10;
    s32 ret;
    u32 var_s0 = 0;

    outcnt = 0;
    bk = 0;
    bb = 0;
    gzip_malloc_tmp = 0;
    gzip_malloc_addr = gzip_mem_buff;

    while (true) {
        hufts = 0;
        ret = inflate_block(&sp10);
        if (ret != 0) {
            break;
        }

        if (var_s0 < hufts) {
            var_s0 = hufts;
        }

        if (sp10 != 0) {
            while (bk >= 8) {
                bk -= 8;
                inptr -= 1;
            }

            flush_window();
            ret = 0;
            break;
        }
    }

    return ret;
}
#endif

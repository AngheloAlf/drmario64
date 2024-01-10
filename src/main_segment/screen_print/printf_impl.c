/**
 * printf implementation based on kmc's libgcc PRINTF.C
 *
 * The name is completely made up.
 */

#include "libultra.h"
#include "include_asm.h"
#include "macros_defines.h"
#include "unknown_structs.h"
#include "gcc/memory.h"
#include "gcc/string.h"
#include "libc/ctype.h"
#include "libc/stdarg.h"
#include "libc/math.h"
#include "screen_print/printer.h"
#include "libkmc/explog.h"

#if VERSION_US
char basc[] = "0123456789abcdefx";

char BASC[] = "0123456789ABCDEFX";

f64 _div_data[] = {
    1e+1, 1e+2, 1e+4, 1e+8, 1e+16, 1e+32, 1e+64, 1e+128, 1e+256,
};

f64 _mul_data[] = {
    1e-1, 1e-2, 1e-4, 1e-8, 1e-16, 1e-32, 1e-64, 1e-128, 1e-256,
};

static char fbuf[FBUF_SIZE];
#endif

#if VERSION_US
char *cvt_radix(char buf[ABUFSIZE], unsigned int value, int radix, const char *binasc) {
    buf += ABUFSIZE;

    do {
        buf -= 1;
        *buf = binasc[value % radix];

        value /= radix;
    } while (value != 0);

    return buf;
}
#endif

#if VERSION_US
char *cvtl_radix(char buf[ABUFSIZE], unsigned long long value, int radix, const char *binasc) {
    buf += ABUFSIZE;

    do {
        volatile int index = value % radix;

        buf--;
        *buf = binasc[index];

        value /= radix;
    } while (value != 0);

    return buf;
}
#endif

#if VERSION_US
int round_asc(char *p, int exp, int n) {
    char *pbak;

    p = &p[n];
    if (*p < '5') {
        *p = '\0';
        return exp;
    }

    pbak = p;

    n--;
    *pbak = '\0';

    while (n >= 0) {
        p--;
        n--;
        if (*p != '9') {
            *p = *p + 1;
            return exp;
        }

        *p = '0';
    }

    *p = '1';
    *pbak++ = '0';
    *pbak++ = '\0';
    return exp + 1;
}
#endif

#if VERSION_US
void eprt_sub(char *s, s32 ndig, s32 exp, char *arg3, s32 letter_e, s32 sharp_flg) {
    ndig--;
    *arg3++ = *s++;
    *arg3++ = '.';

    memcpy(arg3, s, ndig);
    arg3 = &arg3[ndig];

    if (sharp_flg == 0) {
        while (arg3[-1] == '0') {
            arg3--;
        }

        if (arg3[-1] == '.') {
            arg3--;
        }
    }

    *arg3++ = letter_e;
    if (exp < 0) {
        exp = -exp;
        *arg3++ = '-';
    } else {
        *arg3++ = '+';
    }

    if (exp >= 100) {
        *arg3++ = (exp / 100) + '0';
        exp %= 100;
    }

    *arg3++ = (exp / 10) + '0';
    exp %= 10;

    *arg3++ = exp + '0';
    *arg3++ = '\0';
}
#endif

typedef union {
    struct {
        /* 0x0 */ u32 hi;
        /* 0x4 */ u32 lo;
    } word;
    /* 0x0 */ f64 d;
} du; // size = 0x8

#if VERSION_US
char *ecvt(double x, int ndig, int *dec, int *sign) {
    int exp = 0;
    int exp_index = 0x100;
    int ndig1 = ndig;
    volatile double x1;
    du val;
    double ipart;
    int i;
    char *p;

    *sign = 0;

    if (ndig > VALID_CT) {
        ndig = VALID_CT + 1;
        ndig1 = VALID_CT;
    }

    val.d = x;

    switch (val.word.hi & 0x7FF00000) {
        case 0x0:
            p = fbuf;
            for (i = 0; i < ndig; i++) {
                *p++ = '0';
            }

            *dec = 1;
            return fbuf;

        case 0x7FF00000:
            *dec = 0x7FFFFFFF;
            if ((val.word.hi & 0xFFFFF) || (val.word.lo != 0)) {
                strcpy(fbuf, "NAN");
                *sign = 0;
                return fbuf;
            }
            strcpy(fbuf, "INF");
            return fbuf;
    }

    if (x < 0.0) {
        *sign = 1;
        x = -x;
    }

    if (x >= 1.0) {
        for (i = 8; i >= 0; i--) {
            if (_div_data[i] <= x) {
                exp += exp_index;
                x *= _mul_data[i];
            }
            exp_index >>= 1;
        }
    } else {
        for (i = 8; i >= 0; i--) {
            if (x < _mul_data[i]) {
                exp -= exp_index;
                x *= _div_data[i];
            }
            exp_index >>= 1;
        }
        exp--;
        x *= 10.0;
    }

    x1 = x;

exp_loop:
    if (x1 >= 10.0) {
        exp += 1;
        x1 *= 0.1;
        goto exp_loop;
    } else if (x1 < 1.0) {
        exp -= 1;
        x1 *= 10.0;
        goto exp_loop;
    }

    p = fbuf;
    do {
        x1 = modf(x1, &ipart) * 10.0;
        *p++ = (int)ipart + '0';
        ndig1--;
    } while (ndig1 >= 0);

    if (ndig > VALID_CT) {
        *dec = exp + 1;
    } else {
        *dec = round_asc(fbuf, exp, ndig) + 1;
    }

    return fbuf;
}
#endif

#if VERSION_US
char *fcvt(double x, int ndig, int *dec, int *sign) {
    char *p = ecvt(x, VALID_CT + 1, dec, sign);
    int exp = *dec;
    int epos;

    if (exp == 0x7FFFFFFF) {
        return fbuf;
    }

    epos = exp + ndig;
    if (epos < 0) {
        return fbuf;
    }

    if (epos <= VALID_CT) {
        *dec = round_asc(fbuf, exp, epos);
    } else {
        epos = MIN(epos, FBUF_SIZE);

        epos -= VALID_CT + 1;
        p += VALID_CT + 1;
        for (; epos > 0; epos--) {
            *p++ = '0';
        }
    }

    return fbuf;
}
#endif

#if VERSION_US
char *gcvt(double x, s32 ndig, char *bufp, s32 letter_e, s32 sharp_flg) {
    int exp;
    int sign;
    char *p = ecvt(x, ndig, &exp, &sign);
    char *q = bufp;

    if (sign != 0) {
        *bufp = '-';
        q = bufp + 1;
    }

    if (exp == 0x7FFFFFFF) {
        strcpy(q, p);
        return bufp;
    }

    if (exp <= 0) {
        if (exp > -4) {
            *q++ = '0';
            *q++ = '.';

            while (exp != 0) {
                *q++ = '0';
                exp++;
            }

            memcpy(q, p, ndig);
            q += ndig;

        del_zero:
            if (sharp_flg == 0) {
                while (q[-1] == '0') {
                    q -= 1;
                }

                if (q[-1] == '.') {
                    q--;
                }
            }
            q[0] = 0;

            return bufp;
        }
    } else if (exp < ndig) {
        ndig--;
        while (ndig != -1) {
            *q++ = *p++;
            exp--;
            if (exp == 0) {
                *q++ = '.';
            }
            ndig--;
        }

        goto del_zero;
    } else if (ndig + 1 >= exp) {
        memcpy(q, p, exp);
        q[ndig] = '0';

        if (sharp_flg == 0) {
            q[exp] = '\0';
        } else {
            q[exp] = '.';
            *(q + exp + 1) = '\0';
        }

        return bufp;
    }

    eprt_sub(p, ndig, exp - 1, q, letter_e, sharp_flg);
    return bufp;
}
#endif

#if VERSION_US
#ifdef NON_MATCHING
int _kmcprt(Printer *arg0, const char *fmt, va_list args) {
    char sp18[ABUFSIZE];
    char sp118;
    int sp11C;
    int sp120;
    int sp124;
    int sp128;
    char sp12C;
    char sp12D;
    char sp12E;
    char sp12F;
    s32 sp144;
    s32 sp14C;
    s32 sp154;
    char *sp15C;
    s32 sp164;
    double var_fa0;
    double var_fs0;
    s32 var_a1;
    long long var_a2;
    s32 var_fp;
    s32 var_s2;
    s32 var_s3;
    int var_s4;
    s32 var_s6;
    s32 var_s7;
    s32 var_v1_3;
    char *temp_a1;
    char *var_s0_3;
    char *var_s1;
    char *var_s2_3;
    s32 var_s0;

    var_fp = 0;

    while (true) {
        sp118 = *fmt++;

        if (sp118 != '%') {
            if (sp118 == 0) {
                sp164 = 0;
                return var_fp;
            }
            if (__ctype_map[sp118] & 0x80) {
                Printer_PutChars(arg0, &sp118, 1);
                var_fp += 1;
                sp118 = *fmt++;
            }
            Printer_PutChars(arg0, &sp118, 1);
            var_fp += 1;
            continue;
        }

        var_s3 = 0;
        sp164 = 0;

    loop_6:
        sp118 = *fmt++;
        switch (sp118) { /* switch 1 */
            case 0x2D:   /* switch 1 */
                var_s3 |= 1;
                goto loop_6;

            case 0x2B: /* switch 1 */
                var_s3 |= 2;
                goto loop_6;

            case 0x30: /* switch 1 */
                var_s3 |= 4;
                goto loop_6;

            case 0x20: /* switch 1 */
                var_s3 |= 8;
                goto loop_6;

            case 0x23: /* switch 1 */
                sp164 = 1;
                goto loop_6;
        }

        if (sp118 == '*') { // 0x2A
            var_s6 = va_arg(args, int);

            if (var_s6 < 0) {
                var_s3 |= 1;
                var_s6 = -var_s6;
            }
            sp118 = *fmt++;
        } else {
            var_s6 = 0;
            while (__ctype_map[sp118] & 8) {
                var_s6 = (var_s6 * 0xA) + (sp118 - 0x30);
                sp118 = *fmt++;
            }
        }

        var_s2 = 0;
        var_s4 = 6;
        if (sp118 == '.') { // 0x2E
            sp118 = *fmt++;
            if (sp118 == '*') { // 0x2A
                var_s2 = va_arg(args, int);
                sp118 = *fmt++;
            } else {
                var_s4 = 0;
                while (__ctype_map[sp118] & 8) {
                    var_s2 = (var_s2 * 0xA) + (sp118 - 0x30);
                    sp118 = *fmt++;
                }
            }

            var_s4 = var_s2;
        }

        sp154 = 0;
        sp144 = 0;
        sp15C = basc;
        sp14C = 0xA;

    loop_26:
        switch (sp118) {
            case 'd': // 0x64
            case 'i': // 0x69
                sp144 = 1;
                goto block_100;

            case 'u': // 0x75
                goto block_100;

            case 'o': // 0x6F
                sp14C = 8;
                var_s3 &= ~0xA;
                goto block_100;

            case 'X': // 0x58
                sp15C = BASC;
                /* fallthrough */
                FALLTHROUGH;

            case 'x': // 0x78
                sp14C = 0x10;
                var_s3 &= ~0xA;
                goto block_100;

            case 'c': // 0x63
                var_s1 = sp18;
                sp18[0] = va_arg(args, int);
                var_s0 = 1;
                goto block_151;

            case 's': // 0x73
                var_s1 = va_arg(args, char *);

                if (var_s1 == NULL) {
                    var_s1 = "(null)";
                }
                var_s0 = strlen(var_s1);
                if ((var_s2 != 0) & (var_s2 < var_s0)) {
                    var_s0 = var_s2;
                }
                goto block_151;

            case 'f': // 0x66
            {
                var_fs0 = va_arg(args, double);

                var_s2_3 = fcvt(var_fs0, var_s4, &sp11C, &sp120);
                if (sp120 != 0) {
                    var_s3 |= 0x100;
                }
                var_s0_3 = var_s1 = &sp18[1];
                if (sp11C == 0x7FFFFFFF) {
                    strcpy(var_s0_3, var_s2_3);
                } else {
                    if (sp11C <= 0) {
                        *var_s0_3++ = 0x30;
                        *var_s0_3++ = 0x2E;
                        var_v1_3 = 0;
                        while (sp11C != 0) {
                            *var_s0_3++ = 0x30;
                            var_v1_3 += 1;
                            sp11C = sp11C + 1;
                            if (var_v1_3 == var_s4) {
                                // goto block_80;
                                break;
                            }
                        }

                        while (var_v1_3 != var_s4) {
                            *var_s0_3++ = *var_s2_3++;
                            var_v1_3 += 1;
                        }

                        *var_s0_3 = 0;
                    } else if (sp11C + var_s4 < 0x28) {
                        memcpy(var_s0_3, var_s2_3, sp11C);
                        var_s2_3 += sp11C;
                        var_s0_3 += sp11C;
                        if (var_s4 != 0) {
                            *var_s0_3 = 0x2E;
                            var_s0_3 = var_s0_3 + 1;
                            memcpy(var_s0_3, var_s2_3, var_s4);
                        } else {
                            if (sp164 != 0) {
                                *var_s0_3 = 0x2E;
                                var_s0_3 += 1;
                            }
                        }
                        var_s0_3[var_s4] = 0;
                    } else if (sp11C + var_s4 < 0xFF) {
                        memcpy(var_s0_3, var_s2_3, 0x28);

                        if (sp11C <= 0x28) {
                            var_s0_3 += sp11C;
                        } else {
                            var_s0_3 += 0x28;
                            var_v1_3 = sp11C - 0x28;
                            do {
                                *var_s0_3++ = 0x30;
                                var_v1_3 -= 1;
                            } while (var_v1_3 != 0);
                        }

                        if (var_s4 != 0) {
                            *var_s0_3++ = 0x2E;
                            var_v1_3 = var_s4;
                            do {
                                *var_s0_3++ = 0x30;
                                var_v1_3 -= 1;
                            } while (var_v1_3 != 0);
                        } else {
                            if (sp164 != 0) {
                                *var_s0_3 = 0x2E;
                                var_s0_3 += 1;
                            }
                        }
                        *var_s0_3 = 0;
                    } else {
                        var_s4 = 0x14;
                        sp118 = 0x65;
                        goto block_83;
                    }
                }
                var_s0 = strlen(var_s1);
                var_s2 = 0;
                sp154 = 1;
            }
                goto block_117;

            case 'E': // 0x45
            case 'e': // 0x65
            {
                var_fs0 = va_arg(args, double);
            block_83:
                temp_a1 = ecvt(var_fs0, var_s4, &sp124, &sp128);
                var_s0_3 = var_s1 = &sp18[1];
                if (sp128 != 0) {
                    var_s3 |= 0x100;
                }

                if (sp124 == 0x7FFFFFFF) {
                    strcpy(var_s0_3, temp_a1);
                } else {
                    eprt_sub(temp_a1, var_s4, sp124 - 1, var_s0_3, sp118, sp164);
                }
                var_s0 = strlen(var_s1);
                var_s2 = 0;
                sp154 = 1;
                goto block_117;
            }

            case 'G': // 0x47
            case 'g': // 0x67
                var_fa0 = va_arg(args, double);
                if (var_fa0 < 0.0) {
                    var_s3 |= 0x100;
                    var_fa0 = -var_fa0;
                }
                var_s1 = gcvt(var_fa0, var_s4, sp18 + 1, sp118 - 2, sp164);
                var_s0 = strlen(var_s1);
                var_s2 = 0;
                sp154 = 1;
                goto block_117;

            case 'n': // 0x6E
            {
                int *n = va_arg(args, int *);
                *n = var_fp;
            }
                goto next;
                break;

            case 'p': // 0x70
                var_s3 = 0;
                var_s2 = 8;
                sp15C = BASC;
                sp14C = 0x10;
                goto block_100;

            case 'h': // 0x68
                var_s3 |= 0x40;
                sp118 = *fmt++;
                goto loop_26;

            case 'l': // 0x6C
                sp118 = *fmt++;
                if (sp118 == 0x6C) {
                    var_s3 |= 0x20;
                    sp118 = *fmt++;
                }
                goto loop_26;

            case 'L': // 0x4C
                var_s3 |= 0x80;
                sp118 = *fmt++;
                goto loop_26;

            default:
                Printer_PutChars(arg0, &sp118, 1);
                var_fp += 1;
                goto next;
                break;
        }
        {
        block_100:
            if (var_s2 != 0) {
                var_s3 &= ~4;
            }
            if (var_s3 & 0x20) {
                var_a2 = va_arg(args, long long);
                if (sp144 != 0) {
                    if (var_a2 < 0) {
                        var_a2 = -var_a2;
                        var_s3 |= 0x100;
                    }
                }
                var_s1 = cvtl_radix(sp18, var_a2, sp14C, sp15C);
            } else {
                var_a1 = va_arg(args, int);
                if (var_s3 & 0x40) {
                    if (sp144 != 0) {
                        var_a1 = (s16)var_a1;
                    } else {
                        var_a1 = (u16)var_a1;
                    }
                }
                if (sp144 != 0) {
                    if (var_a1 < 0) {
                        var_a1 = -var_a1;
                        var_s3 |= 0x100;
                    }
                }
                var_s1 = cvt_radix(sp18, var_a1, sp14C, sp15C);
            }

            // what
            // var_s0 = (sp - var_s1) + 0x118;
            // var_s0 = var_s1[-sp118];
            var_s0 = (u32)&sp18[0x100] - (u32)var_s1;

        block_117:
            var_s7 = 0;
            if (sp164 && (sp14C != 0xA)) {
                if ((sp144 == 0) && (*var_s1 != 0x30)) {
                    var_s7 = 1;
                    if (sp14C == 0x10) {
                        var_s7 = 2;
                    }
                }
            }

            if ((var_s3 & 4) && !(var_s3 & 1)) {
                var_s2 = var_s6;
            }
            if (var_s2 != 0) {
                if (var_s3 & 0x10A) {
                    var_s2 -= 1;
                    if (sp154 != 0) {
                        var_s6 -= 1;
                        var_fp += 1;
                        if (var_s3 & 0x100) {
                            sp12C = 0x2D;
                            Printer_PutChars(arg0, &sp12C, 1);
                        } else {
                            if (var_s3 & 2) {
                                sp12C = 0x2B;
                            } else {
                                sp12C = 0x20;
                            }
                            Printer_PutChars(arg0, &sp12C, 1);
                        }
                        var_s3 &= ~0x10A;
                    }
                }
                var_s2 = var_s2 - var_s7;
                while (var_s0 < var_s2) {
                    if (sp154 != 0) {
                        sp12D = 0x30;
                        Printer_PutChars(arg0, &sp12D, 1);
                        var_s6 -= 1;
                        var_fp += 1;
                        var_s2 -= 1;
                    } else {
                        var_s1 -= 1;
                        *var_s1 = 0x30;
                        var_s0 += 1;
                    }
                }
            }
            if (var_s7 != 0) {
                if (var_s7 == 2) {
                    var_s1 -= 1;
                    *var_s1 = sp15C[0x10];
                }
                var_s1 -= 1;
                *var_s1 = 0x30;
                var_s0 += var_s7;
            }
            if (var_s3 & 0x10A) {
                var_s0 += 1;
                var_s1 -= 1;
                if (var_s3 & 0x100) {
                    *var_s1 = 0x2D;
                } else {
                    if (var_s3 & 2) {
                        *var_s1 = 0x2B;
                    } else {
                        *var_s1 = 0x20;
                    }
                }
            }

        block_151:
            if (!(var_s3 & 1)) {
                while (var_s0 < var_s6) {
                    sp12E = 0x20;
                    Printer_PutChars(arg0, &sp12E, 1);
                    var_s6 -= 1;
                    var_fp += 1;
                }
            }

            var_s6 = var_s6 - var_s0;
            var_fp += var_s0;
            var_s0 = var_s0 - 1;
            while (var_s0 != -1) {
                Printer_PutChars(arg0, var_s1++, 1);
                var_s0 -= 1;
            }
            while (var_s6 > 0) {
                sp12F = 0x20;
                Printer_PutChars(arg0, &sp12F, 1);
                var_s6 -= 1;
                var_fp += 1;
            }
        }
    next:;
    }
}
#else
INCLUDE_ASM("asm/us/nonmatchings/main_segment/screen_print/printf_impl", _kmcprt);
#endif
#endif

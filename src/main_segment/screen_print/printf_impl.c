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
void eprt_sub(char *s, s32 ndig, s32 exp, char *arg3, s32 letter_e, bool sharp_flg) {
    ndig--;
    *arg3++ = *s++;
    *arg3++ = '.';

    memcpy(arg3, s, ndig);
    arg3 = &arg3[ndig];

    if (!sharp_flg) {
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
char *gcvt(double x, s32 ndig, char *bufp, s32 letter_e, bool sharp_flg) {
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
            if (!sharp_flg) {
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

        if (!sharp_flg) {
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

/* printf flags */
#define MINUS 1 /* - */
#define PLUS 2  /* + */
#define ZERO 4  /* 0 */
#define SPACE 8 /*   */

/* printf type size */
#define LONG_TYPE 0x20
#define SHORT_TYPE 0x40
#define LDOUBLE_TYPE 0x80

#define SIGNE_M 0x100 /* minus value */

#if VERSION_US
int _kmcprt(Printer *arg0, const char *fmt, va_list args) {
    char _asc_buf[ABUFSIZE];
    char c;
    bool sign;
    int radix;
    bool float_flg;
    char *binasc;
    bool sharp_flg;
    double dval;
    int n_ct;
    int prec;
    unsigned int flg;
    int fprec;
    int width;
    int heder_len;
    char *asc;
    int len;
    int letter_e;

    n_ct = 0;

    while (true) {
        c = *fmt++;

        if (c != '%') {
            if (c == '\0') {
                return n_ct;
            }
            if (iskanji(c)) {
                Printer_PutChars(arg0, &c, 1);
                n_ct += 1;
                c = *fmt++;
            }
            Printer_PutChars(arg0, &c, 1);
            n_ct += 1;
            continue;
        }

        /* printf flag */
        flg = 0;
        sharp_flg = false;

    flag_loop:
        c = *fmt++;
        switch (c) {
            case '-':
                flg |= MINUS;
                goto flag_loop;

            case '+':
                flg |= PLUS;
                goto flag_loop;

            case '0':
                flg |= ZERO;
                goto flag_loop;

            case ' ':
                flg |= SPACE;
                goto flag_loop;

            case '#':
                sharp_flg = true;
                goto flag_loop;
        }

        /* printf width */
        if (c == '*') {
            width = va_arg(args, int);

            if (width < 0) {
                flg |= MINUS;
                width = -width;
            }
            c = *fmt++;
        } else {
            width = 0;
            while (isdigit(c)) {
                width = (width * 10) + (c - '0');
                c = *fmt++;
            }
        }

        /* precision */
        prec = 0;
        fprec = 6;
        if (c == '.') {
            c = *fmt++;
            if (c == '*') {
                prec = va_arg(args, int);
                c = *fmt++;
            } else {
                fprec = 0;
                while (isdigit(c)) {
                    prec = (prec * 10) + (c - '0');
                    c = *fmt++;
                }
            }

            fprec = prec;
        }

        /* type */
        float_flg = false;
        sign = false;
        binasc = basc;
        radix = 10;

    type_loop:
        switch (c) {
            case 'd':
            case 'i':
                sign = true;
                goto block_100;

            case 'u':
                goto block_100;

            case 'o':
                radix = 8;
                flg &= ~(PLUS | SPACE);
                goto block_100;

            case 'X':
                binasc = BASC;
                FALLTHROUGH;
            case 'x':
                radix = 0x10;
                flg &= ~(PLUS | SPACE);
                goto block_100;

            case 'c':
                asc = _asc_buf;
                _asc_buf[0] = va_arg(args, int);
                len = 1;
                goto prt_all;

            case 's': // 0x73
                asc = va_arg(args, char *);

                if (asc == NULL) {
                    asc = "(null)";
                }
                len = strlen(asc);
                if ((prec != 0) & (prec < len)) {
                    len = prec;
                }
                goto prt_all;

            case 'f': // 0x66
            {
                int fsign;
                int exp;
                int n;
                char *p;
                char *q;

                dval = va_arg(args, double);

                p = fcvt(dval, fprec, &exp, &fsign);
                if (fsign != 0) {
                    flg |= SIGNE_M;
                }
                q = asc = &_asc_buf[1];
                if (exp == 0x7FFFFFFF) {
                    strcpy(q, p);
                } else if (exp <= 0) {
                    *q++ = '0';
                    *q++ = '.';
                    n = 0;
                    while (exp != 0) {
                        *q++ = '0';
                        n++;
                        exp++;
                        if (n == fprec) {
                            break;
                        }
                    }

                    while (n != fprec) {
                        *q++ = *p++;
                        n++;
                    }

                    *q = '\0';
                } else if (exp + fprec < FBUF_SIZE) {
                    memcpy(q, p, exp);
                    p += exp;
                    q += exp;
                    if (fprec != 0) {
                        *q++ = '.';
                        memcpy(q, p, fprec);
                    } else if (sharp_flg) {
                        *q++ = '.';
                    }
                    q[fprec] = '\0';
                } else if (exp + fprec < ABUFSIZE - 1) {
                    memcpy(q, p, FBUF_SIZE);

                    if (exp <= FBUF_SIZE) {
                        q += exp;
                    } else {
                        q += FBUF_SIZE;
                        n = exp - FBUF_SIZE;
                        do {
                            *q++ = '0';
                            n -= 1;
                        } while (n != 0);
                    }

                    if (fprec != 0) {
                        *q++ = '.';
                        n = fprec;
                        do {
                            *q++ = '0';
                            n -= 1;
                        } while (n != 0);
                    } else {
                        if (sharp_flg) {
                            *q++ = '.';
                        }
                    }
                    *q = '\0';
                } else {
                    fprec = VALID_CT + 1;
                    c = 'e';
                    goto format_e;
                }

                len = strlen(asc);
                prec = 0;
                float_flg = true;
            }
                goto prt_float;

            case 'E':
            case 'e': {
                int fsign;
                int exp;
                char *p;
                char *q;

                dval = va_arg(args, double);
            format_e:
                p = ecvt(dval, fprec, &exp, &fsign);
                q = asc = &_asc_buf[1];
                if (fsign != 0) {
                    flg |= SIGNE_M;
                }

                if (exp == 0x7FFFFFFF) {
                    strcpy(q, p);
                } else {
                    letter_e = c;
                    eprt_sub(p, fprec, exp - 1, q, letter_e, sharp_flg);
                }
                len = strlen(asc);
                prec = 0;
                float_flg = true;
                goto prt_float;
            }

            case 'G':
            case 'g': {
                double dval;

                dval = va_arg(args, double);
                if (dval < 0.0) {
                    flg |= SIGNE_M;
                    dval = -dval;
                }
                letter_e = c - 2;
                asc = gcvt(dval, fprec, &_asc_buf[1], letter_e, sharp_flg);
                len = strlen(asc);
                prec = 0;
                float_flg = true;
                goto prt_float;
            }

            case 'n': {
                int *np = va_arg(args, int *);

                *np = n_ct;
                goto next;
            }

            case 'p':
                flg = 0;
                prec = 8;
                binasc = BASC;
                radix = 0x10;
                goto block_100;

            case 'h':
                flg |= SHORT_TYPE;
                c = *fmt++;
                goto type_loop;

            case 'l':
                c = *fmt++;
                if (c == 'l') {
                    flg |= LONG_TYPE;
                    c = *fmt++;
                }
                goto type_loop;

            case 'L':
                flg |= LDOUBLE_TYPE;
                c = *fmt++;
                goto type_loop;

            default:
                Printer_PutChars(arg0, &c, 1);
                n_ct += 1;
                goto next;
                break;
        }
        {
        block_100:
            if (prec != 0) {
                flg &= ~ZERO;
            }

            if (flg & LONG_TYPE) {
                long long lval = va_arg(args, long long);

                if (sign) {
                    if (lval < 0) {
                        lval = -lval;
                        flg |= SIGNE_M;
                    }
                }
                asc = cvtl_radix(_asc_buf, lval, radix, binasc);
            } else {
                long val = va_arg(args, long);

                if (flg & SHORT_TYPE) {
                    if (sign) {
                        val = (s16)val;
                    } else {
                        val = (u16)val;
                    }
                }
                if (sign) {
                    if (val < 0) {
                        val = -val;
                        flg |= SIGNE_M;
                    }
                }
                asc = cvt_radix(_asc_buf, val, radix, binasc);
            }

            // what?
            len = (s32)(&_asc_buf[ABUFSIZE] - asc);

        prt_float:
            heder_len = 0;
            if (sharp_flg && (radix != 10)) {
                if (!sign && (*asc != 0x30)) {
                    heder_len = (radix == 0x10) ? 2 : 1;
                }
            }

            if ((flg & ZERO) && !(flg & MINUS)) {
                prec = width;
            }
            if (prec != 0) {
                if (flg & (PLUS | SPACE | SIGNE_M)) {
                    prec--;
                    if (float_flg) {
                        char sp12C;

                        width--;
                        n_ct++;
                        if (flg & SIGNE_M) {
                            sp12C = '-';
                            Printer_PutChars(arg0, &sp12C, 1);
                        } else {
                            if (flg & PLUS) {
                                sp12C = '+';
                            } else {
                                sp12C = ' ';
                            }
                            Printer_PutChars(arg0, &sp12C, 1);
                        }
                        flg &= ~(PLUS | SPACE | SIGNE_M);
                    }
                }

                prec = prec - heder_len;
                while (len < prec) {
                    if (float_flg) {
                        char sp12D = '0';
                        Printer_PutChars(arg0, &sp12D, 1);
                        width--;
                        n_ct++;
                        prec--;
                    } else {
                        asc--;
                        *asc = '0';
                        len++;
                    }
                }
            }

            if (heder_len != 0) {
                if (heder_len == 2) {
                    asc--;
                    *asc = binasc[0x10];
                }
                asc--;
                *asc = '0';
                len += heder_len;
            }

            if (flg & (PLUS | SPACE | SIGNE_M)) {
                len++;
                asc--;
                if (flg & SIGNE_M) {
                    *asc = '-';
                } else if (flg & PLUS) {
                    *asc = '+';
                } else {
                    *asc = ' ';
                }
            }

        prt_all:
            if (!(flg & MINUS)) {
                while (len < width) {
                    char sp12E = ' ';

                    Printer_PutChars(arg0, &sp12E, 1);
                    width--;
                    n_ct++;
                }
            }

            width -= len;
            n_ct += len;
            len--;
            while (len != -1) {
                Printer_PutChars(arg0, asc++, 1);
                len -= 1;
            }
            while (width > 0) {
                char sp12F = ' ';

                Printer_PutChars(arg0, &sp12F, 1);
                width--;
                n_ct++;
            }
        }
    next:;
    }
}
#endif

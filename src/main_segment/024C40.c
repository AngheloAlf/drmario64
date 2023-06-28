#include "libultra.h"
#include "include_asm.h"
#include "macros_defines.h"
#include "unknown_structs.h"
#include "main_segment_functions.h"
#include "gcc/memory.h"
#include "gcc/string.h"
#include "libc/stdarg.h"
#include "libc/math.h"

#if VERSION_US
char *func_8003CE20(char arg0[0x100], u32 arg1, u32 arg2, char *arg3) {
    char *var_a0 = &arg0[0x100];

    do {
        var_a0 -= 1;
        *var_a0 = arg3[arg1 % arg2];

        arg1 = arg1 / arg2;
    } while (arg1 != 0);

    return var_a0;
}
#endif

#if VERSION_US
char *func_8003CE5C(char arg0[0x100], u64 arg2, s32 arg4, char *arg5) {
    arg0 = &arg0[0x100];

    do {
        vs32 index = arg2 % arg4;

        arg0--;
        *arg0 = arg5[index];

        arg2 /= arg4;
    } while (arg2 != 0);

    return arg0;
}
#endif

#if VERSION_US
s32 func_8003CF2C(char *arg0, s32 arg1, s32 arg2) {
    char *temp_a3;

    arg0 = &arg0[arg2];
    if (*arg0 < '5') {
        *arg0 = '\0';
        return arg1;
    }

    temp_a3 = arg0;

    arg2--;
    *temp_a3 = '\0';

    while (arg2 >= 0) {
        arg0--;
        arg2--;
        if (*arg0 != '9') {
            *arg0 = *arg0 + 1;
            return arg1;
        }

        *arg0 = '0';
    }

    *arg0 = '1';
    *temp_a3++ = '0';
    *temp_a3++ = '\0';
    return arg1 + 1;
}
#endif

#if VERSION_US
void func_8003CFA8(char *arg0, u32 arg1, s32 arg2, char *arg3, s32 arg4, s32 arg5) {
    arg1--;
    *arg3++ = *arg0++;
    *arg3++ = '.';

    memcpy(arg3, arg0, arg1);
    arg3 = &arg3[arg1];

    if (arg5 == 0) {
        while (arg3[-1] == '0') {
            arg3--;
        }

        if (arg3[-1] == '.') {
            arg3--;
        }
    }

    *arg3++ = arg4;
    if (arg2 < 0) {
        arg2 = -arg2;
        *arg3++ = '-';
    } else {
        *arg3++ = '+';
    }

    if (arg2 >= 100) {
        *arg3++ = (arg2 / 100) + '0';
        arg2 %= 100;
    }

    *arg3++ = (arg2 / 10) + '0';
    arg2 %= 10;

    *arg3++ = arg2 + '0';
    *arg3++ = '\0';
}
#endif

extern char B_800E5860[];

extern f64 D_8008D208[];
extern f64 D_8008D250[];

typedef union {
    struct {
        /* 0x0 */ u32 hi;
        /* 0x4 */ u32 lo;
    } word;
    /* 0x0 */ f64 d;
} du; // size = 0x8

#if VERSION_US
char *func_8003D110(f64 arg0, s32 arg2, s32 *arg3, s32 *arg4) {
    volatile f64 sp10;
    du var_fa0;
    f64 sp18;
    s32 var_a2;
    s32 var_s1;
    s32 var_s2;
    s32 var_v1;
    char *var_s0;

    var_s1 = 0;
    var_a2 = 0x100;
    var_s2 = arg2;
    *arg4 = 0;
    if (arg2 >= 0x14) {
        arg2 = 0x14;
        var_s2 = 0x13;
    }
    var_fa0.d = arg0;

    switch (var_fa0.word.hi & 0x7FF00000) {
        case 0x0:
            var_s0 = B_800E5860;
            for (var_v1 = 0; var_v1 < arg2; var_v1++) {
                *var_s0++ = 0x30;
            }

            *arg3 = 1;
            break;

        case 0x7FF00000:
            *arg3 = 0x7FFFFFFF;
            if ((var_fa0.word.hi & 0xFFFFF) || (var_fa0.word.lo != 0)) {
                strcpy(B_800E5860, "NAN");
                *arg4 = 0;
                return B_800E5860;
            } else {
                strcpy(B_800E5860, "INF");
                return B_800E5860;
            }
            break;

        default:
            if (arg0 < 0.0) {
                *arg4 = 1;
                arg0 = -arg0;
            }

            if (arg0 >= 1.0) {
                for (var_v1 = 8; var_v1 >= 0; var_v1--) {
                    if (D_8008D208[var_v1] <= arg0) {
                        var_s1 += var_a2;
                        arg0 *= D_8008D250[var_v1];
                    }
                    var_a2 = var_a2 >> 1;
                }
            } else {
                for (var_v1 = 8; var_v1 >= 0; var_v1--) {
                    if (arg0 < D_8008D250[var_v1]) {
                        var_s1 -= var_a2;
                        arg0 *= D_8008D208[var_v1];
                    }
                    var_a2 = var_a2 >> 1;
                }
                var_s1 -= 1;
                arg0 *= 10.0;
            }

            sp10 = arg0;
        dumb_loop:
            if (sp10 >= 10.0) {
                var_s1 += 1;
                sp10 *= 0.1;
            } else if (sp10 < 1.0) {
                var_s1 -= 1;
                sp10 *= 10.0;
            } else {
                goto loop_end;
            }
            goto dumb_loop;
        loop_end:;

            var_s0 = B_800E5860;
            do {
                sp10 = modf(sp10, &sp18) * 10.0;
                *var_s0++ = (s32)sp18 + '0';
                var_s2--;
            } while (var_s2 >= 0);

            if (arg2 >= 20) {
                *arg3 = var_s1 + 1;
            } else {
                *arg3 = func_8003CF2C(B_800E5860, var_s1, arg2) + 1;
            }
            break;
    }

    return B_800E5860;
}
#endif

#if VERSION_US
char *func_8003D41C(f64 arg0, s32 arg2, s32 *arg3, s32 *arg4) {
    s32 temp_a1;
    s32 var_a2;
    char *temp_v1;

    temp_v1 = func_8003D110(arg0, 0x14, arg3, arg4);
    temp_a1 = *arg3;
    if (temp_a1 == 0x7FFFFFFF) {
        return B_800E5860;
    }

    var_a2 = temp_a1 + arg2;
    if (var_a2 < 0) {
        return B_800E5860;
    }

    if (var_a2 < 0x14) {
        *arg3 = func_8003CF2C(B_800E5860, temp_a1, var_a2);
    } else {
        var_a2 = MIN(var_a2, 40);

        var_a2 -= 20;
        temp_v1 += 20;
        for (; var_a2 > 0; var_a2--) {
            *temp_v1++ = '0';
        }
    }

    return B_800E5860;
}
#endif

#if VERSION_US
char *func_8003D4C8(f64 arg0, s32 arg2, char *arg3, s32 arg4, s32 arg5) {
    s32 sp18;
    s32 sp1C;
    char *var_a1;
    char *var_s0;

    var_a1 = func_8003D110(arg0, arg2, &sp18, &sp1C);
    var_s0 = arg3;
    if (sp1C != 0) {
        *arg3 = 0x2D;
        var_s0 = arg3 + 1;
    }

    if (sp18 == 0x7FFFFFFF) {
        strcpy(var_s0, var_a1);
        return arg3;
    }

    if (sp18 <= 0) {
        if (sp18 >= -3) {
            *var_s0++ = 0x30;
            *var_s0++ = 0x2E;

            while (sp18 != 0) {
                *var_s0++ = 0x30;
                sp18 = sp18 + 1;
            }

            memcpy(var_s0, var_a1, arg2);
            var_s0 = var_s0 + arg2;

        label:
            if (arg5 == 0) {
                while (var_s0[-1] == 0x30) {
                    var_s0 -= 1;
                }

                if (var_s0[-1] == 0x2E) {
                    var_s0--;
                }
            }
            var_s0[0] = 0;

            return arg3;
        }
    } else if (sp18 < arg2) {
        arg2 = arg2 - 1;
        while (arg2 != -1) {
            *var_s0++ = *var_a1++;
            sp18--;
            if (sp18 == 0) {
                *var_s0++ = 0x2E;
            }
            arg2 -= 1;
        }

        goto label;
    } else if (arg2 + 1 >= sp18) {
        memcpy(var_s0, var_a1, sp18);
        var_s0[arg2] = 0x30;

        if (arg5 == 0) {
            var_s0[sp18] = 0;
        } else {
            var_s0[sp18] = 0x2E;
            *(var_s0 + sp18 + 1) = 0;
        }

        return arg3;
    }

    func_8003CFA8(var_a1, arg2, sp18 - 1, var_s0, arg4, arg5);
    return arg3;
}
#endif

extern u8 D_80010940[];
extern char D_8008D1E0[];
extern char D_8008D1F4[];

#if VERSION_US
#ifdef NON_MATCHING
int func_8003D6D0(struct_8008E364 *arg0, const char *fmt, va_list args) {
    char sp18[0x100];
    char sp118;
    s32 sp11C;
    s32 sp120;
    s32 sp124;
    s32 sp128;
    char sp12C;
    char sp12D;
    char sp12E;
    char sp12F;
    // struct_8008E364 *sp134;
    // s8 *sp13C;
    s32 sp144;
    s32 sp14C;
    s32 sp154;
    char *sp15C;
    s32 sp164;
    f64 var_fa0;
    f64 var_fs0;
    s32 var_a1;
    long long var_a2;
    s32 var_fp;
    s32 var_s2;
    s32 var_s3;
    s32 var_s4;
    s32 var_s6;
    s32 var_s7;
    s32 var_v1_3;
    char *temp_a1;
    char *var_s0_3;
    char *var_s1;
    char *var_s2_3;
    // s8 *var_s5;
    s32 var_s0;

    // var_s5 = fmt;
    var_fp = 0;
    // sp134 = arg0;
    // sp13C = args;

    while (true) {
        sp118 = *fmt++;

        if (sp118 != 0x25) {
            if (sp118 == 0) {
                return var_fp;
            }
            if (D_80010940[sp118] & 0x80) {
                func_8003CDF8(arg0, &sp118, 1);
                var_fp += 1;
                sp118 = *fmt++;
            }
            func_8003CDF8(arg0, &sp118, 1);
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
            while (D_80010940[sp118] & 8) {
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
                while (D_80010940[sp118] & 8) {
                    var_s2 = (var_s2 * 0xA) + (sp118 - 0x30);
                    sp118 = *fmt++;
                }
            }

            var_s4 = var_s2;
        }

        sp154 = 0;
        sp144 = 0;
        sp15C = D_8008D1E0;
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
                sp15C = D_8008D1F4;
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

                var_s2_3 = func_8003D41C(var_fs0, var_s4, &sp11C, &sp120);
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
                var_fs0 = va_arg(args, double);
            block_83:
                temp_a1 = func_8003D110(var_fs0, var_s4, &sp124, &sp128);
                var_s0_3 = var_s1 = &sp18[1];
                if (sp128 != 0) {
                    var_s3 |= 0x100;
                }
                if (sp124 == 0x7FFFFFFF) {
                    strcpy(var_s0_3, temp_a1);
                } else {
                    func_8003CFA8(temp_a1, var_s4, sp124 - 1, var_s0_3, sp118, sp164);
                }
                var_s0 = strlen(var_s1);
                var_s2 = 0;
                sp154 = 1;
                goto block_117;

            case 'G': // 0x47
            case 'g': // 0x67
                var_fa0 = va_arg(args, double);
                if (var_fa0 < 0.0) {
                    var_s3 |= 0x100;
                    var_fa0 = -var_fa0;
                }
                var_s1 = func_8003D4C8(var_fa0, var_s4, sp18 + 1, sp118 - 2, sp164);
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
                sp15C = D_8008D1F4;
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
                func_8003CDF8(arg0, &sp118, 1);
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
                var_s1 = func_8003CE5C(sp18, var_a2, sp14C, sp15C);
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
                var_s1 = func_8003CE20(sp18, var_a1, sp14C, sp15C);
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
                            func_8003CDF8(arg0, &sp12C, 1);
                        } else {
                            if (var_s3 & 2) {
                                sp12C = 0x2B;
                            } else {
                                sp12C = 0x20;
                            }
                            func_8003CDF8(arg0, &sp12C, 1);
                        }
                        var_s3 &= ~0x10A;
                    }
                }
                var_s2 = var_s2 - var_s7;
                while (var_s0 < var_s2) {
                    if (sp154 != 0) {
                        sp12D = 0x30;
                        func_8003CDF8(arg0, &sp12D, 1);
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
                    func_8003CDF8(arg0, &sp12E, 1);
                    var_s6 -= 1;
                    var_fp += 1;
                }
            }

            var_s6 = var_s6 - var_s0;
            var_fp += var_s0;
            var_s0 = var_s0 - 1;
            while (var_s0 != -1) {
                func_8003CDF8(arg0, var_s1++, 1);
                var_s0 -= 1;
            }
            while (var_s6 > 0) {
                sp12F = 0x20;
                func_8003CDF8(arg0, &sp12F, 1);
                var_s6 -= 1;
                var_fp += 1;
            }
        }
    next:;
    }
}
#else
INCLUDE_ASM("asm/us/nonmatchings/main_segment/024C40", func_8003D6D0);
#endif
#endif

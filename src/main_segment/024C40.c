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

char *func_8003D110(f64 arg0, s32 arg2, s32 *arg3, s32 *arg4);
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
#ifdef NON_EQUIVALENT
char *func_8003D110(f64 arg0, s32 arg2, s32 *arg3, s32 *arg4) {
    du var_fa0;
    f64 sp18;
    s32 var_a2;
    s32 var_s1;
    s32 var_s2;
    s32 var_v1;
    s8 *var_s0;

    var_s1 = 0;
    var_a2 = 0x100;
    var_s2 = arg2;
    *arg4 = 0;
    if (arg2 >= 0x14) {
        arg2 = 0x14;
        var_s2 = 0x13;
    }
    var_fa0.d = arg0;

    switch (var_fa0.word.hi & 0x7FF00000) { /* irregular */
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
            } else {
                strcpy(B_800E5860, "INF");
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

            while (true) {
                if (arg0 >= 10.0) {
                    var_s1 += 1;
                    arg0 *= 0.1;
                } else if (arg0 < 1.0) {
                    var_s1 -= 1;
                    arg0 *= 10.0;
                } else {
                    break;
                }
            }

            var_s0 = B_800E5860;
            do {
                arg0 = modf(arg0, &sp18) * 10.0;
                *var_s0++ = (s32)sp18 + 0x30;
                var_s2 -= 1;
            } while (var_s2 >= 0);

            if (arg2 >= 0x14) {
                *arg3 = var_s1 + 1;
            } else {
                *arg3 = func_8003CF2C(&B_800E5860, var_s1, arg2) + 1;
            }
            break;
    }

    return B_800E5860;
}
#else
INCLUDE_ASM("asm/us/nonmatchings/main_segment/024C40", func_8003D110);
#endif
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

char *func_8003D4C8(f64 arg0, s32 arg2, char *arg3, s32 arg4, s32 arg5);

#if VERSION_US
#ifdef NON_EQUIVALENT
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

            memcpy(var_s0, var_a1, (u32)arg2);
            var_s0 = var_s0 + arg2;
            if (arg5 != 0) {
                var_s0[0] = 0;
            } else {
                while (var_s0[-1] == 0x30) {
                    var_s0 -= 1;
                }

                var_s0[var_s0[-1] == 0x2E ? -1 : 0] = 0;
            }
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

        if (arg5 != 0) {
            var_s0[0] = 0;
        } else {
            while (var_s0[-1] == 0x30) {
                var_s0 -= 1;
            }

            var_s0[var_s0[-1] == 0x2E ? -1 : 0] = 0;
        }
        return arg3;
    } else if ((arg2 + 1) >= sp18) {
        memcpy(var_s0, var_a1, sp18);
        var_s0[arg2] = 0x30;
        if (arg5 == 0) {
            var_s0[sp18] = 0;
        } else {
            var_s0[sp18] = 0x2E;
            var_s0[sp18 + 1] = 0;
        }
        return arg3;
    }

    func_8003CFA8(var_a1, arg2, sp18 - 1, var_s0, arg4, arg5);
    return arg3;
}
#else
INCLUDE_ASM("asm/us/nonmatchings/main_segment/024C40", func_8003D4C8);
#endif
#endif

extern u8 D_80010940[];
extern char D_8008D1E0[];
extern char D_8008D1F4[];

#if VERSION_US
#if 0
//? func_8003CDF8(struct_8008E364 *, u8 *, ?);        /* extern */
// s8 *func_8003CE20(u8 *, s16, s32, ? *);             /* extern */
// s8 *func_8003CE5C(u8 *, s32, ? *);                  /* extern */
//? func_8003CFA8(s8 *, u32, s32, s8 *, s32, s32);    /* extern */
// s8 *func_8003D110(f64, u32, s32 *, s32 *);          /* extern */
// s8 *func_8003D41C(f64, u32, s32 *, s32 *);          /* extern */
// s8 *func_8003D4C8(f64, u32, s8 *, s32, s32);        /* extern */

#define unaligned

void func_8003D6D0(struct_8008E364 *arg0, const char *fmt, va_list args) {
    u8 sp18;
    s8 sp19;
    s8 sp1A;
    s8 sp1B;
    u8 sp118;
    s32 sp11C;
    s32 sp120;
    s32 sp124;
    s32 sp128;
    u8 sp12C;
    u8 sp12D;
    u8 sp12E;
    u8 sp12F;
    // struct_8008E364 *sp134;
    // s8 *sp13C;
    s32 sp144;
    s32 sp14C;
    s32 sp154;
    char *sp15C;
    s32 sp164;
    f64 var_fa0;
    f64 var_fs0;
    s32 *temp_v0_10;
    s32 *temp_v0_11;
    s32 *temp_v0_12;
    s32 *temp_v0_14;
    s32 *temp_v0_15;
    s32 **temp_v0_16;
    s32 *temp_v0_3;
    s32 *temp_v0_6;
    s32 *temp_v0_7;
    s32 *temp_v0_8;
    s32 *temp_v0_9;
    s32 temp_v1;
    s32 temp_v1_3;
    s32 temp_v1_6;
    s32 var_a1;
    s32 var_fp;
    s32 var_s0_2;
    s32 var_s2;
    s32 var_s2_2;
    s32 var_s3;
    s32 var_s4;
    s32 var_s6;
    s32 var_s6_2;
    s32 var_s7;
    s32 var_t1;
    s32 var_v0;
    s32 var_v1;
    s32 var_v1_2;
    s32 var_v1_3;
    s32 var_v1_4;
    s8 *temp_a1;
    s8 *temp_t0;
    s8 *temp_t0_2;
    s8 *var_a2;
    s8 *var_s0_3;
    s8 *var_s0_5;
    s8 *var_s2_3;
    // char *var_s5;
    u32 var_s0;
    u8 *temp_s0;
    u8 *var_a1_2;
    u8 *var_a3;
    u8 *var_s0_4;
    u8 *var_s1;
    u8 *var_v0_2;
    u8 temp_a0;
    u8 temp_a0_2;
    u8 temp_v0;
    u8 *temp_v0_13;
    u8 *temp_v0_17;
    u8 temp_v0_2;
    u8 *temp_v0_4;
    u8 temp_v0_5;
    u8 temp_v1_2;
    u8 temp_v1_4;
    u8 temp_v1_5;
    u8 temp_v1_7;
    u8 var_v0_3;

    // var_s5 = fmt;

    var_fp = 0;
    // sp134 = arg0;
    // sp13C = args;

    while (true) {
        temp_v0 = (u8)*fmt;
        temp_v1 = temp_v0 & 0xFF;
        sp118 = temp_v0;
        fmt += 1;
        if (temp_v1 == 0x25) {
            var_s3 = 0;
            sp164 = 0;

            while (true) {

                sp118 = *fmt++;
                switch (sp118) { /* switch 1 */
                    case 0x2D:   /* switch 1 */
                        var_s3 |= 1;
                        break;

                    case 0x2B: /* switch 1 */
                        var_s3 |= 2;
                        break;

                    case 0x30: /* switch 1 */
                        var_s3 |= 4;
                        break;

                    case 0x20: /* switch 1 */
                        var_s3 |= 8;
                        break;

                    case 0x23: /* switch 1 */
                        sp164 = 1;
                        break;

                    default:
                        goto loop_6_end;
                        break;
                }
            }

        loop_6_end:;

            if (sp118 == 0x2A) {
                temp_v0_3 = ((uintptr_t)args + 3) & ~3;
                var_s6 = *temp_v0_3;
                args = temp_v0_3 + 4;
                if (var_s6 < 0) {
                    var_s3 |= 1;
                    var_s6 = -var_s6;
                }
                sp118 = *fmt++;
            } else {
                var_s6 = 0;
                while (D_80010940[sp118] & 8) {
                    temp_a0 = sp118;
                    sp118 = *fmt++;
                    var_s6 = (var_s6 * 0xA) - 0x30 + temp_a0;
                }
            }

            var_s2 = 0;
            var_s4 = 6;
            if (sp118 == 0x2E) {
                temp_v0_5 = (u8)*fmt;
                temp_v1_3 = temp_v0_5 & 0xFF;
                sp118 = temp_v0_5;
                fmt += 1;
                if (temp_v1_3 == 0x2A) {
                    temp_v0_6 = (s32)(args + 3) & ~3;
                    var_s2 = *temp_v0_6;
                    sp118 = *fmt++;
                    args = temp_v0_6 + 4;
                } else {
                    var_s4 = 0;
                    while (D_80010940[temp_v1_3] & 8) {
                        temp_a0_2 = sp118;
                        sp118 = *fmt++;
                        var_s2 = (var_s2 * 0xA) - 0x30 + temp_a0_2;
                    }
                }
                var_s4 = var_s2;
            }

            sp15C = D_8008D1E0;
            sp154 = 0;
            sp144 = 0;
            sp14C = 0xA;

            while (true) {
                switch (sp118) { /* switch 2 */
                    case 0x64:   /* switch 2 */
                    case 0x69:   /* switch 2 */
                        sp144 = 1;
                        goto block_100;

                    case 0x75: /* switch 2 */
                    block_100:
                        if (var_s2 != 0) {
                            var_s3 &= ~4;
                        }

                        if (var_s3 & 0x20) {
                            temp_v0_7 = (s32)(args + 7) & ~7;
                            args = temp_v0_7 + 8;
                            if ((sp144 != 0) && (temp_v0_7[0] < 0)) {
                                var_s3 |= 0x100;
                            }
                            var_s1 = func_8003CE5C(&sp18, sp14C, sp15C);
                        } else {
                            temp_v0_8 = (s32)(args + 3) & ~3;
                            args = temp_v0_8 + 4;
                            var_a1 = *temp_v0_8;
                            if (var_s3 & 0x40) {
                                if (sp144 != 0) {
                                    var_a1 = (s32)(s16)var_a1;
                                } else {
                                    var_a1 &= 0xFFFF;
                                }
                            }
                            if ((sp144 != 0) && (var_a1 < 0)) {
                                var_a1 = -var_a1;
                                var_s3 |= 0x100;
                            }
                            var_s1 = func_8003CE20(&sp18, (s16)var_a1, sp14C, sp15C);
                        }
                        var_s0 = (&sp118 - var_s1);

                    block_117:
                        var_s7 = 0;
                        if (sp164 & (sp14C != 0xA)) {
                            var_v1 = var_s3 & 5;
                            if ((sp144 == 0) && (*var_s1 != 0x30)) {
                                var_s7 = 1;
                                if (sp14C == 0x10) {
                                    var_s7 = 2;
                                    var_v1 = var_s3 & 5;
                                    goto block_122;
                                }
                            }
                        } else {
                            var_v1 = var_s3 & 5;
                        }
                        block_122:

                        if (var_v1 == 4) {
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
                                    } else if (var_s3 & 2) {
                                        sp12C = 0x2B;
                                    } else {
                                        sp12C = 0x20;
                                    }
                                    func_8003CDF8(arg0, &sp12C, 1);
                                    var_s3 &= ~0x10A;
                                }
                            }
                            var_s2_2 = var_s2 - var_s7;
                            while ((s32)var_s0 < var_s2_2) {
                                if (sp154 != 0) {
                                    sp12D = 0x30;
                                    func_8003CDF8(arg0, &sp12D, 1);
                                    var_s6 -= 1;
                                    var_fp += 1;
                                    var_s2_2 -= 1;
                                } else {
                                    var_s1 -= 1;
                                    *var_s1 = 0x30;
                                    var_s0 += 1;
                                }
                            }
                        }
                        if (var_s7 != 0) {
                            var_s1 -= 1;
                            if (var_s7 == 2) {
                                *var_s1 = (&sp15C)[0x10];
                                var_s1 -= 1;
                            }
                            *var_s1 = 0x30;
                            var_s0 += var_s7;
                        }

                        if (var_s3 & 0x10A) {
                            var_s0 += 1;
                            var_s1 -= 1;
                            if (var_s3 & 0x100) {
                                *var_s1 = 0x2D;
                            } else if (var_s3 & 2) {
                                *var_s1 = 0x2B;
                            } else {
                                *var_s1 = 0x20;
                            }
                        }

                    block_151:
                        var_v0 = var_s3 & 1;
                    block_152:
                        if (var_v0 == 0) {
                            while ((s32)var_s0 < var_s6) {
                                sp12E = 0x20;
                                func_8003CDF8(arg0, &sp12E, 1);
                                var_s6 -= 1;
                                var_fp += 1;
                            }
                        }
                        var_s6_2 = var_s6 - var_s0;
                        var_fp += var_s0;
                        var_s0_2 = var_s0 - 1;
                        var_a1_2 = var_s1;
                        while (var_s0_2 != -1) {
                            var_s1 += 1;
                            func_8003CDF8(arg0, var_a1_2, 1);
                            var_s0_2 -= 1;
                            var_a1_2 = var_s1;
                        }
                        while (var_s6_2 > 0) {
                            sp12F = 0x20;
                            func_8003CDF8(arg0, &sp12F, 1);
                            var_s6_2 -= 1;
                            var_fp += 1;
                        }
                        goto loop_26_end;
                        break;

                    case 0x6F: /* switch 2 */
                        var_t1 = 8;
                        sp14C = var_t1;
                        var_s3 &= ~0xA;
                        goto block_100;

                    case 0x58: /* switch 2 */
                        sp15C = D_8008D1F4;
                        /* fallthrough */
                    case 0x78: /* switch 2 */
                        var_t1 = 0x10;
                        sp14C = var_t1;
                        var_s3 &= ~0xA;
                        goto block_100;

                    case 0x63: /* switch 2 */
                        var_s1 = &sp18;
                        temp_v0_9 = (s32)(args + 3) & ~3;
                        var_s0 = 1;
                        args = temp_v0_9 + 4;
                        sp18 = (u8)*temp_v0_9;
                        goto block_151;

                    case 0x73: /* switch 2 */
                        temp_v0_10 = (s32)(args + 3) & ~3;
                        var_s1 = *temp_v0_10;
                        args = temp_v0_10 + 4;
                        if (var_s1 == NULL) {
                            var_s1 = "(null)";
                        }
                        var_s0 = strlen(var_s1);
                        if ((var_s2 != 0) & (var_s2 < (s32)var_s0)) {
                            var_s0 = (u32)var_s2;
                            goto block_151;
                        }
                        var_v0 = var_s3 & 1;
                        goto block_152;

                    case 0x66: /* switch 2 */
                        temp_v0_11 = (s32)(args + 7) & ~7;
                        args = temp_v0_11 + 8;
                        var_fs0 = *temp_v0_11;
                        var_s2_3 = func_8003D41C(var_fs0, (u32)var_s4, &sp11C, &sp120);
                        if (sp120 != 0) {
                            var_s3 |= 0x100;
                        }

                        var_s1 = (u8 *)&sp19;
                        if (sp11C == 0x7FFFFFFF) {
                            strcpy((s8 *)var_s1, var_s2_3);
                        } else {
                            temp_v1_6 = sp11C + var_s4;
                            if (sp11C <= 0) {
                                var_s0_3 = &sp1B;
                                var_v1_2 = 0;
                                sp19 = 0x30;
                                sp1A = 0x2E;
                                while (sp11C != 0) {
                                    *var_s0_3 = 0x30;
                                    var_s0_3 += 1;
                                    var_v1_2 += 1;
                                    sp11C = sp11C + 1;
                                    if (var_v1_2 == var_s4) {
                                        goto block_80;
                                    }
                                }

                                while (var_v1_2 != var_s4) {
                                    temp_v0_13 = (u8)*var_s2_3;
                                    var_s2_3 += 1;
                                    var_v1_2 += 1;
                                    *var_s0_3 = (s8)temp_v0_13;
                                    var_s0_3 += 1;
                                }
                                *var_s0_3 = 0;

                            } else if (temp_v1_6 < 0x28) {
                                memcpy(var_s1, var_s2_3, (u32)sp11C);
                                var_s0_4 = &var_s1[sp11C];
                                if (var_s4 != 0) {
                                    *var_s0_4 = 0x2E;
                                    temp_s0 = var_s0_4 + 1;
                                    memcpy(temp_s0, &var_s2_3[sp11C], (u32)var_s4);
                                    var_v0_2 = &temp_s0[var_s4];
                                } else {
                                    if (sp164 != 0) {
                                        *var_s0_4 = 0x2E;
                                        var_s0_4 += 1;
                                    }
                                    var_v0_2 = &var_s0_4[var_s4];
                                }
                                *var_v0_2 = 0;
                            } else {
                                var_a2 = var_s2_3;
                                if (temp_v1_6 < 0xFF) {
                                    var_a3 = var_s1;
#if 0
                            if (((s32) var_a2 | (s32) var_s1) & 3) {
                                temp_t0 = var_a2 + 0x20;
                                do {
                                    var_a3->unk_0 = (unaligned s32) var_a2->unk_0;
                                    var_a3->unk_4 = (unaligned s32) var_a2->unk_4;
                                    var_a3->unk_8 = (unaligned s32) var_a2->unk_8;
                                    var_a3->unk_C = (unaligned s32) var_a2->unk_C;
                                    var_a2 += 0x10;
                                    var_a3 += 0x10;
                                } while (var_a2 != temp_t0);
                            } else {
                                temp_t0_2 = var_a2 + 0x20;
                                do {
                                    var_a3->unk_0 = (s32) var_a2->unk_0;
                                    var_a3->unk_4 = (s32) var_a2->unk_4;
                                    var_a3->unk_8 = (s32) var_a2->unk_8;
                                    var_a3->unk_C = (s32) var_a2->unk_C;
                                    var_a2 += 0x10;
                                    var_a3 += 0x10;
                                } while (var_a2 != temp_t0_2);
                            }
                            var_a3->unk_0 = (unaligned s32) var_a2->unk_0;
                            var_a3->unk_4 = (unaligned s32) var_a2->unk_4;
#endif
                                    if (sp11C >= 0x29) {
                                        var_s0_3 = (s8 *)(var_s1 + 0x28);
                                        var_v1_3 = sp11C - 0x28;
                                        do {
                                            *var_s0_3 = 0x30;
                                            var_v1_3 -= 1;
                                            var_s0_3 += 1;
                                        } while (var_v1_3 != 0);
                                    } else {
                                        var_s0_3 = &var_s1[sp11C];
                                    }

                                    if (var_s4 != 0) {
                                        *var_s0_3 = 0x2E;
                                        var_s0_5 = var_s0_3 + 1;
                                        var_v1_4 = var_s4;
                                        while (var_v1_4 != 0) {
                                            *var_s0_5 = 0x30;
                                            var_v1_4 -= 1;
                                            var_s0_5 += 1;
                                        }
                                        *var_s0_5 = 0;
                                    } else {
                                        if (sp164 != 0) {
                                            *var_s0_3 = 0x2E;
                                            var_s0_3 += 1;
                                        }
                                    block_80:
                                        *var_s0_3 = 0;
                                    }
                                } else {
                                    var_s4 = 0x14;
                                    sp118 = 0x65;
                                block_83:
                                    var_s1 = (u8 *)&sp19;
                                    temp_a1 = func_8003D110(var_fs0, (u32)var_s4, &sp124, &sp128);
                                    if (sp128 != 0) {
                                        var_s3 |= 0x100;
                                    }
                                    if (sp124 == 0x7FFFFFFF) {
                                        strcpy((s8 *)var_s1, temp_a1);
                                    } else {
                                        func_8003CFA8(temp_a1, (u32)var_s4, sp124 - 1, (s8 *)var_s1, (s32)sp118, sp164);
                                    }
                                }
                            }
                        }
                        var_s0 = strlen((s8 *)var_s1);
                        var_s2 = 0;
                        sp154 = 1;
                        goto block_117;

                    case 0x45: /* switch 2 */
                    case 0x65: /* switch 2 */
                        temp_v0_14 = (s32)(args + 7) & ~7;
                        args = temp_v0_14 + 8;
                        var_fs0 = *temp_v0_14;
                        goto block_83;

                    case 0x47: /* switch 2 */
                    case 0x67: /* switch 2 */
                        temp_v0_15 = (s32)(args + 7) & ~7;
                        var_fa0 = *temp_v0_15;
                        args = temp_v0_15 + 8;
                        if (var_fa0 < 0.0) {
                            var_s3 |= 0x100;
                            var_fa0 = -var_fa0;
                        }
                        sp154 = 1;
                        var_s2 = 0;
                        var_s1 = func_8003D4C8(var_fa0, (u32)var_s4, &sp19, sp118 - 2, sp164);
                        var_s0 = strlen((s8 *)var_s1);
                        goto block_117;

                    case 0x6E: /* switch 2 */
                        temp_v0_16 = (s32)(args + 3) & ~3;
                        args = temp_v0_16 + 4;
                        **temp_v0_16 = var_fp;
                        goto loop_26_end;
                        break;

                    case 0x70: /* switch 2 */
                        var_s3 = 0;
                        var_s2 = 8;
                        sp15C = D_8008D1F4;
                        sp14C = 0x10;
                        goto block_100;

                    case 0x68: /* switch 2 */
                        var_v0_3 = (u8)*fmt;
                        var_s3 |= 0x40;

                        fmt += 1;
                        sp118 = var_v0_3;
                        continue;

                    case 0x6C: /* switch 2 */
                        temp_v1_7 = (u8)*fmt;
                        sp118 = temp_v1_7;
                        fmt += 1;
                        if ((temp_v1_7 & 0xFF) == 0x6C) {
                            var_v0_3 = (u8)*fmt;
                            var_s3 |= 0x20;
                            fmt += 1;
                            sp118 = var_v0_3;
                        }
                        continue;

                    case 0x4C: /* switch 2 */
                        var_v0_3 = (u8)*fmt;
                        var_s3 |= 0x80;
                        fmt += 1;
                        sp118 = var_v0_3;
                        continue;

                    default: /* switch 2 */
                        func_8003CDF8(arg0, &sp118, 1);
                        var_fp += 1;
                        goto loop_26_end;
                        break;
                }
            }

        loop_26_end:;
        } else if (temp_v1 != 0) {
            if (D_80010940[temp_v1] & 0x80) {
                func_8003CDF8(arg0, &sp118, 1);
                temp_v0_17 = (u8)*fmt;
                var_fp += 1;
                fmt += 1;
                sp118 = temp_v0_17;
            }
            func_8003CDF8(arg0, &sp118, 1);
            var_fp += 1;
        } else {
            break;
        }
    }
}
#else
INCLUDE_ASM("asm/us/nonmatchings/main_segment/024C40", func_8003D6D0);
#endif
#endif

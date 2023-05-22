#ifndef MACROS_DEFINES_H
#define MACROS_DEFINES_H

#include "version.h"

#if defined(_MSC_VER)
#  define UNREACHABLE __assume(0)
#elif __IS_OLD_COMP__
#  define UNREACHABLE
#elif defined(__GNUC__) || defined(__clang__)
#  define UNREACHABLE __builtin_unreachable()
#else
#  define UNREACHABLE
#endif

#define SCREEN_WIDTH  320
#define SCREEN_HEIGHT 240


#define CHECK_FLAG_ALL(flags, mask) (((flags) & (mask)) == (mask))


#define ARRAY_COUNT(arr) (s32)(sizeof(arr) / sizeof(arr[0]))
#define ARRAY_COUNTU(arr) (u32)(sizeof(arr) / sizeof(arr[0]))

#define CLAMP(x, min, max) ((x) < (min) ? (min) : (x) > (max) ? (max) : (x))
#define CLAMP_MAX(x, max) ((x) > (max) ? (max) : (x))
#define CLAMP_MIN(x, min) ((x) < (min) ? (min) : (x))

#define SQ(x) ((x) * (x))

#define ASM_TEXT __asm__(".section .text")
#define ASM_DATA __asm__(".section .data")
#define ASM_RODATA __asm__(".section .rodata")
#define ASM_BSS __asm__(".section .bss")

#define INC_WRAP(value, limit) (((value) + 1) % (u32)(limit))

#define ANY_BUTTON (A_BUTTON | B_BUTTON | L_TRIG | R_TRIG | Z_TRIG | START_BUTTON | U_JPAD | L_JPAD | R_JPAD | D_JPAD | U_CBUTTONS | L_CBUTTONS | R_CBUTTONS | D_CBUTTONS)



#define saved_reg_s0 0
#define saved_reg_s1 0
#define saved_reg_s2 0
#define saved_reg_s3 0
#define saved_reg_s4 0
#define saved_reg_s5 0
#define saved_reg_s6 0
#define saved_reg_s7 0
#define bitwise
#define saved_reg_f20 0.0f
#define saved_reg_f22 0.0f


#endif

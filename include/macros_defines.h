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

#define STATIC_INLINE static inline
#ifdef PERMUTER
#define INLINE static inline
#else
#define INLINE inline
#endif

#ifndef PRESERVE_UB
#define BAD_RETURN(type) type
#else
#define BAD_RETURN(type) void
#endif

#define CLAMP(x, min, max) ((x) < (min) ? (min) : (x) > (max) ? (max) : (x))

#define SQ(x) ((x) * (x))

// Mark a value is a double literal.
// This is usually unintended effect due to a missing `f` suffix.
// Having this macro makes this easier to trackdown.
#define DOUBLE_LITERAL(x) ((f64)(x))

#define ASM_TEXT __asm__(".section .text")
#define ASM_DATA __asm__(".section .data")
#define ASM_RODATA __asm__(".section .rodata")
#define ASM_BSS __asm__(".section .bss")

#define INC_WRAP(value, limit) (((value) + 1) % (u32)(limit))

#define ANY_BUTTON (A_BUTTON | B_BUTTON | L_TRIG | R_TRIG | Z_TRIG | START_BUTTON | U_JPAD | L_JPAD | R_JPAD | D_JPAD | U_CBUTTONS | L_CBUTTONS | R_CBUTTONS | D_CBUTTONS)

#define RELOCATE_SEGMENTED(ptr, baseAddr) ((void *)(SEGMENT_OFFSET((ptr)) + (uintptr_t)(baseAddr)))
#define RELOCATE_OFFSET(ptr, offset) ((void *)((uintptr_t)(ptr) + (uintptr_t)(offset)))


#define saved_reg_s0 0
#define saved_reg_s1 0
#define saved_reg_s2 0
#define saved_reg_s3 0
#define saved_reg_s4 0
#define saved_reg_s5 0
#define saved_reg_s6 0
#define saved_reg_s7 0
#define saved_reg_fp 0
#define bitwise
#define saved_reg_f20 0.0f
#define saved_reg_f22 0.0f

#define HELP (*(vu32*)0 = 0x1234)

// #define DEBUG_EN 1
#if DEBUG_EN
#define T(jp, en) en
#else
#define T(jp, en) jp
#endif

#endif

#ifndef MACROS_DEFINES_H
#define MACROS_DEFINES_H

#include "version.h"

#if (!defined(__GNUC__) && !defined(__clang__)) || defined(M2CTX)
#define __attribute__(x)
#endif

#if __STDC_VERSION__ >= 202000L
#define CONST [[gnu::const]]
#define DEPRECATED(reason) [[deprecated (reason)]]
#define FALLTHROUGH [[fallthrough]]
#define NODISCARD [[nodiscard]]
#define NORETURN [[noreturn]]
#define PURE [[gnu::pure]]
#define RETURNS_NON_NULL [[gnu::returns_nonnull]]
#define UNUSED [[maybe_unused]]
#else
#define CONST __attribute__((const))
#define DEPRECATED(reason) __attribute__((deprecated (reason)))
#if __IS_KMC__
#define FALLTHROUGH
#else
#define FALLTHROUGH __attribute__((fallthrough))
#endif
#define NODISCARD __attribute__((warn_unused_result))
#define NORETURN _Noreturn
#define PURE __attribute__((pure))
#define RETURNS_NON_NULL __attribute__((returns_nonnull))
#define UNUSED __attribute__((unused))
#endif


#if defined(_MSC_VER)
#  define UNREACHABLE __assume(0)
#elif __IS_KMC__
#  define UNREACHABLE
#elif defined(__GNUC__) || defined(__clang__)
#  define UNREACHABLE __builtin_unreachable()
#else
#  define UNREACHABLE
#endif

#define SCREEN_WIDTH  320
#define SCREEN_HEIGHT 240


#define ARRAY_COUNT(arr) (s32)(sizeof(arr) / sizeof(arr[0]))
#define ARRAY_COUNTU(arr) (u32)(sizeof(arr) / sizeof(arr[0]))

#define CLAMP(x, min, max) ((x) < (min) ? (min) : (x) > (max) ? (max) : (x))
#define CLAMP_MAX(x, max) ((x) > (max) ? (max) : (x))
#define CLAMP_MIN(x, min) ((x) < (min) ? (min) : (x))

#define MAX_ALT(a, b) ((b) > (a) ? (b) : (a))
#define MIN_ALT(a, b) ((b) < (a) ? (b) : (a))

#define SQ(x) ((x) * (x))

#define ASM_TEXT __asm__(".section .text")
#define ASM_RODATA __asm__(".section .rodata")

#define RODATA __attribute__ ((section (".rodata")))
#define BSS __attribute__ ((section (".bss")))


#define ALL_BUTTONS (A_BUTTON | B_BUTTON | L_TRIG | R_TRIG | Z_TRIG | START_BUTTON | U_JPAD | L_JPAD | R_JPAD | D_JPAD | U_CBUTTONS | L_CBUTTONS | R_CBUTTONS | D_CBUTTONS)



#define saved_reg_s0 0
#define saved_reg_s1 0
#define saved_reg_s2 0
#define saved_reg_s3 0
#define saved_reg_s4 0
#define saved_reg_s5 0
#define saved_reg_s6 0
#define bitwise 


#endif

#ifndef MACROS_DEFINES_H
#define MACROS_DEFINES_H

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
#define FALLTHROUGH __attribute__((fallthrough))
#define NODISCARD __attribute__((warn_unused_result))
#define NORETURN _Noreturn
#define PURE __attribute__((pure))
#define RETURNS_NON_NULL __attribute__((returns_nonnull))
#define UNUSED __attribute__((unused))
#endif


#if defined(_MSC_VER)
#  define UNREACHABLE __assume(0)
#elif defined(__GNUC__) || defined(__clang__)
#  define UNREACHABLE __builtin_unreachable()
#else
#  define UNREACHABLE
#endif


#define ARRAY_COUNT(arr) (s32)(sizeof(arr) / sizeof(arr[0]))
#define ARRAY_COUNTU(arr) (u32)(sizeof(arr) / sizeof(arr[0]))

#define CLAMP(x, min, max) ((x) < (min) ? (min) : (x) > (max) ? (max) : (x))
#define CLAMP_MAX(x, max) ((x) > (max) ? (max) : (x))
#define CLAMP_MIN(x, min) ((x) < (min) ? (min) : (x))

#define RODATA __attribute__ ((section (".rodata")))
#define BSS __attribute__ ((section (".bss")))

#endif

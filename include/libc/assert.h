#ifndef ASSERT_H
#define ASSERT_H

#if !defined(__GNUC__) && !defined(__attribute__)
#define __attribute__(x)
#endif

// Runtime assertions

// TODO

// Static/compile-time assertions

#if __STDC_VERSION__ >= 201112L || CC_CHECK
# define static_assert(cond, msg) _Static_assert(cond, msg)
#else
# ifndef GLUE
#  define GLUE(a, b) a##b
# endif
# ifndef GLUE2
#  define GLUE2(a, b) GLUE(a, b)
# endif

# define static_assert(cond, msg) typedef char GLUE2(static_assertion_failed, __LINE__)[(cond) ? 1 : -1]
#endif

#endif

#ifndef VERSION_H
#define VERSION_H

/**
 * Macros for checking specific compiler
 */

#ifndef __IS_KMC__
#define __IS_KMC__ ((__GNUC__== 2) && (__GNUC_MINOR__ == 7))
#endif

#ifndef __IS_EGCS__
#define __IS_EGCS__ ((__GNUC__== 2) && (__GNUC_MINOR__ == 91))
#endif

#ifndef __IS_OLD_COMP__
#define __IS_OLD_COMP__ (__IS_KMC__ || __IS_EGCS__)
#endif


/**
 * Version macros
 */

#if defined(VERSION_US) + defined(VERSION_CN) + defined(VERSION_GW) == 0
#error "A version must be selected"
#endif

#if defined(VERSION_US) + defined(VERSION_CN) + defined(VERSION_GW) != 1
#error "Only one version must be defined"
#endif


#ifndef CHAR_SIGNED
#if VERSION_CN
#define CHAR_SIGNED signed
#else 
#define CHAR_SIGNED unsigned
#endif
#endif

#endif

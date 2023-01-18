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


/**
 * Version macros
 */

#define VERSION_NONE 0
#define VERSION_US   1
#define VERSION_CN   2

#ifndef VERSION
#define VERSION VERSION_NONE
#endif

#endif

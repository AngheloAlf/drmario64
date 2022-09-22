#ifndef STDBOOL
#define STDBOOL

#define __bool_true_false_are_defined 1

#ifndef __cplusplus

typedef enum bool {
    false,
    true
} bool;

#endif /* __cplusplus */

#endif /* STDBOOL */

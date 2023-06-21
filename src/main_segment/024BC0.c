#include "libultra.h"
#include "include_asm.h"
#include "macros_defines.h"
#include "unknown_structs.h"
#include "main_segment_functions.h"
#include "main_segment_variables.h"

#if VERSION_US
UNK_TYPE func_8003CDA0(struct_8008E364 *arg0, ...) {
    UNK_TYPE ret;
    va_list args;

    va_start(args, arg0);

    ret = arg0->unk_0->unk_0(arg0, args);

    va_end(args);

    return ret;
}
#endif

#if VERSION_US
UNK_TYPE func_8003CDD4(struct_8008E364 *arg0) {
    return arg0->unk_0->unk_4();
}
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/024BC0", func_8003CDF8);
#endif

#ifndef BOOT_VARIABLES_H
#define BOOT_VARIABLES_H

#include "libultra.h"
#include "libc/stdint.h"
#include "unknown_structs.h"
#include "unk.h"
#include "alignment.h"
#include "hasm.h"
#include "stack.h"

// bss


extern STACK(gBootThreadStack, BOOT_STACK_SIZE);


#endif

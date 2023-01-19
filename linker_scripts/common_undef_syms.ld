#include "hasm.h"

boot_BSS_START_HI = boot_BSS_START >> 16;
boot_BSS_START_LO = boot_BSS_START & 0xFFFF;
boot_BSS_SIZE_HI = boot_BSS_SIZE >> 16;
boot_BSS_SIZE_LO = boot_BSS_SIZE & 0xFFFF;

bootproc_HI = bootproc >> 16;
bootproc_LO = bootproc & 0xFFFF;

gBootThreadStack_HI = gBootThreadStack >> 16;
gBootThreadStack_LO = gBootThreadStack & 0xFFFF;

gBootThreadStackTop = gBootThreadStack + BOOT_STACK_SIZE;
gBootThreadStackTop_HI = gBootThreadStackTop >> 16;
gBootThreadStackTop_LO = gBootThreadStackTop & 0xFFFF;

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

ASSERT ((boot_ROM_END <= 0x101000), "Error: boot_ROM_END is larger than 1 MB");


ASSERT ((buffer1_VRAM_END <= 0x80205000), "Error: The segment 'buffer1' is overflowing the ram limit");
ASSERT ((buffer2_bss_VRAM == 0x80205000), "Error: buffer2 shifted?");
ASSERT ((framebuffer_bss_VRAM == 0x803B5000), "Error: framebuffer shifted?");


ENTRY(entrypoint);

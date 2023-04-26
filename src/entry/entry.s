#include "hasm.h"

.section .text

.balign 16

LEAF(entrypoint)
    LA($t0, boot_BSS_START)
    LA($t1, boot_BSS_SIZE)

.clear_bss:
    sw      $zero, 0x0($t0)
    sw      $zero, 0x4($t0)
    addi    $t0, $t0, 0x8
    addi    $t1, $t1, -0x8
    bnez    $t1, .clear_bss

.enter_program:
#if VERSION_US || VERSION_GW
    LA($t2, bootproc)
#endif
    LA($sp, gBootThreadStackTop)
#if VERSION_CN
    LA($t2, bootproc)
#endif
    jr      $t2
END(entrypoint)

.fill 0x60 - (. - entrypoint)

#ifndef HASM_H
#define HASM_H

#include "version.h"

#ifdef _LANGUAGE_ASSEMBLY

#define LEAF(x)                 \
    .align 2                   ;\
    .globl x                   ;\
    .type x, @function         ;\
    x:                         ;\
        .ent x, 0              ;\
        .frame $sp, 0, $ra

#define END(x)                  \
    .size x, . - x             ;\
    .end x

.macro move dst, src
    addu \dst, \src, $zero
.endm

// divu dst
.macro divu_ds dst, dividend, divisor
    .set noreorder
    divu        $zero, \dividend, \divisor
    bnez        \divisor, 0f
     nop
    break       7
0:
    mflo        \dst
    .set reorder
.endm

#if VERSION_US
#define LA(dst, address) \
    lui         dst, %hi(address); \
    addiu       dst, dst, %lo(address)
#endif
#if VERSION_CN
#define LA(dst, address) \
    lui         dst, address ## _HI; \
    ori         dst, dst, address ## _LO
#endif

#endif

#define BOOT_STACK_SIZE 0x2000

#endif

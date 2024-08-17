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

#define SYM_START(x)            \
    .align 2                   ;\
    .globl x                   ;\
    .type	 x, @object        ;\
    x:

#define SYM_END(x)              \
    .size x, . - x

#define EXPORT(x)               \
    .globl  x                  ;\
    x:

#define ABS(x, y)               \
    .globl  x                  ;\
    x = y

.macro move dst, src
    addu \dst, \src, $zero
.endm

#if VERSION_US || VERSION_GW
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

#define LA(dst, address) \
    lui         dst, %hi(address); \
    addiu       dst, dst, %lo(address)

#define NOP_N64 nop
#define NOP_IQUE

#elif VERSION_CN
// divu dst
.macro divu_ds dst, dividend, divisor
    .set noreorder
    bnez        \divisor, 0f
     divu       $zero, \dividend, \divisor
    break       7
0:
    mflo        \dst
    .set reorder
.endm

#define LA(dst, address) \
    lui         dst, address ## _HI; \
    ori         dst, dst, address ## _LO

#define NOP_N64
#define NOP_IQUE nop
#endif

#endif

#define BOOT_STACK_SIZE 0x2000

#endif

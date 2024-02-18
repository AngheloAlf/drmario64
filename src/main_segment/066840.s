#include "hasm.h"
.include "macro.inc"

.section .text, "ax"

/*
A few notes about formatting this file :
- Each branch is followed by an empty line.
- Loops are indented whenever possible.
- Each function should have its C declaration as a comment.
*/

/**
 * void func_8007EA20(s32 *arg0, s32 arg1);
 *
 * This function does not halt until `*arg0` is equal to `arg1`.
 */
LEAF(func_8007EA20)
    lw          $v0, 0x0($a0)
    subu        $v0, $v0, $a1
    bnez        $v0, func_8007EA20

    jr          $ra
END(func_8007EA20)

/**
 * s32 func_8007EA38(s32 arg0);
 *
 * Returns square root of `arg0`.
 */
LEAF(func_8007EA38)
    mtc1        $a0, $ft0
    NOP_N64
    cvt.s.w     $fv0, $ft0
    sqrt.s      $ft1, $fv0
    trunc.w.s   $ft2, $ft1
    mfc1        $v0, $ft2
    nop
    jr          $ra
END(func_8007EA38)

/**
 * u32 func_8007EA58(s32 arg0, s32 arg1);
 */
LEAF(func_8007EA58)
    addu        $v0, $zero, $zero
    addu        $v1, $zero, $zero
    addiu       $t0, $zero, 0x20
    slt         $t8, $a1, $zero
    sll         $a1, $a1, 1
    slt         $t9, $a0, $zero
    sll         $a0, $a0, 1
    or          $a0, $a0, $t8
    sll         $v1, $v1, 1
    or          $v1, $v1, $t9

    .L8007EA80:
        slt         $t8, $a1, $zero
        sll         $a1, $a1, 1
        slt         $t9, $a0, $zero
        sll         $a0, $a0, 1
        or          $a0, $a0, $t8
        sll         $v1, $v1, 1
        or          $v1, $v1, $t9
        sll         $v0, $v0, 1
        addiu       $v0, $v0, 0x1
        sltu        $at, $v1, $v0
        bnez        $at, .L8007EAB8

        subu        $v1, $v1, $v0
        addiu       $v0, $v0, 0x2

    .L8007EAB8:
        slt         $t8, $a1, $zero
        sll         $a1, $a1, 1
        slt         $t9, $a0, $zero
        sll         $a0, $a0, 1
        or          $a0, $a0, $t8
        sll         $v1, $v1, 1
        or          $v1, $v1, $t9
        addiu       $v0, $v0, -0x1
        addiu       $t0, $t0, -0x1
    bgtz        $t0, .L8007EA80

    srl        $v0, $v0, 1
    NOP_IQUE
    jr          $ra
END(func_8007EA58)

/**
 * s32 func_8007EAEC(s32 arg0, s32 arg1);
 *
 * TODO: this function is used (by an unused function, duh), so it would be nice
 * to document it.
 */
LEAF(func_8007EAEC)
    addu       $t4, $zero, $zero
    NOP_IQUE
    bnez        $a0, .L8007EB1C

    bnez        $a1, .L8007EB04

    addiu      $v0, $zero, 0x0
    NOP_IQUE
    b           .L8007EC48

.L8007EB04:
    bgez        $a1, .L8007EB14

    ori        $v0, $zero, 0xC000
    NOP_IQUE
    b           .L8007EC48

.L8007EB14:
    addiu      $v0, $zero, 0x4000
    NOP_IQUE
    b           .L8007EC48

.L8007EB1C:
    bgez        $a0, .L8007EB2C

    negu        $a0, $a0
    xori        $t4, $t4, 0x110
.L8007EB2C:
    bnez        $a1, .L8007EB4C

    bnez        $t4, .L8007EB44

    addiu      $v0, $zero, 0x0
    NOP_IQUE
    b           .L8007EC48

.L8007EB44:
    ori        $v0, $zero, 0x8000
    NOP_IQUE
    b           .L8007EC48

.L8007EB4C:
    bgez        $a1, .L8007EB5C

    negu        $a1, $a1
    xori        $t4, $t4, 0x10
.L8007EB5C:
    subu        $t8, $a0, $a1
    bgez        $t8, .L8007EB78

    addu        $t8, $a0, $zero
    addu        $a0, $a1, $zero
    addu        $a1, $t8, $zero
    xori        $t4, $t4, 0x1
.L8007EB78:
    lui         $t8, (0x40000000 >> 16)
    divu_ds     $t8, $t8, $a0

    nop
    nop
    multu       $t8, $a1
    mflo        $t9
    srl         $a0, $t9, 2
    srl         $t8, $a0, 24
    lui         $v1, %hi(D_800AB320)
    addu        $v1, $v1, $t8
    lbu         $v1, %lo(D_800AB320)($v1)
    sll         $t2, $v1, 2

    .L8007EBB8:
        lui         $t9, %hi(D_800AB334)
        addu        $t9, $t9, $t2
        lw          $t9, %lo(D_800AB334)($t9)
        addiu       $v1, $v1, 0x1
        addiu       $t2, $t2, 0x4
        subu        $t8, $a0, $t9
    bgez        $t8, .L8007EBB8

    addiu       $v1, $v1, -0x2
    lui         $t8, %hi(D_800AB32C)
    addu        $t8, $t8, $t2
    lw          $t8, %lo(D_800AB32C)($t8)
    sll        $v0, $v1, 8
    NOP_IQUE
    beq         $a0, $t8, .L8007EC14

    subu        $t3, $a0, $t8
    lui         $t8, %hi(D_800AB3B4)
    addu        $t8, $t8, $t2
    lw          $t8, %lo(D_800AB3B4)($t8)
    multu       $t3, $t8
    mfhi        $t8
    srl         $t8, $t8, 8
    andi        $t9, $t8, 0xFF
    or          $v0, $v0, $t9
.L8007EC14:
    andi        $t8, $t4, 0x1
    beqz        $t8, .L8007EC28

    addiu       $t8, $zero, 0x4000
    subu        $v0, $t8, $v0
.L8007EC28:
    andi        $t8, $t4, 0x10
    beqz        $t8, .L8007EC38

    negu        $v0, $v0
.L8007EC38:
    andi        $t8, $t4, 0x100
    beqz        $t8, .L8007EC48

    addiu       $v0, $v0, -0x8000
.L8007EC48:
    sll         $t8, $v0, 16
    sra        $v0, $t8, 16
    NOP_IQUE
    jr          $ra
END(func_8007EAEC)

/**
 * s16 func_8007EC54(u32 arg0);
 */
LEAF(func_8007EC54)
    srl         $t8, $a0, 5
    andi        $t9, $a0, 0x3F
    andi        $t8, $t8, 0x7FE
    lh          $v0, (D_800AB440)($t8)
    NOP_IQUE
    beqz        $t9, .L8007EC90

    lh          $t8, (D_800AB440 + 0x2)($t8)
    subu        $t8, $t8, $v0
    multu       $t8, $t9
    mflo        $t8
    sra         $t9, $t8, 6
    addu        $v0, $v0, $t9

.L8007EC90:
    jr          $ra
END(func_8007EC54)

/**
 * s16 func_8007EC98(u32 arg0);
 */
LEAF(func_8007EC98)
    addiu       $v0, $a0, 0x4000
    srl         $t8, $v0, 5
    andi        $t9, $v0, 0x3F
    andi        $t8, $t8, 0x7FE

    lh          $v0, (D_800AB440)($t8)
    NOP_IQUE
    beqz        $t9, .L8007ECD8

    lh          $t8, (D_800AB440 + 0x2)($t8)
    subu        $t8, $t8, $v0
    multu       $t8, $t9
    mflo        $t8
    sra         $t9, $t8, 6
    addu        $v0, $v0, $t9

.L8007ECD8:
    jr          $ra
END(func_8007EC98)

/**
 * void func_8007ECE0(UNK_TYPE *arg0, s32 arg1, s32 arg2, s32 arg3, s32 *arg4)
 */
LEAF(func_8007ECE0)
    addiu       $v0, $zero, 0x3
    addiu       $t1, $sp, 0x10

.L8007ECE8:
        lw          $t0, 0x0($a0)
        lw          $t7, 0x10($a0)
        lw          $t6, 0x20($a0)
        mult        $t0, $a1
        mfhi        $t8
        mflo        $t9
        lw          $t0, 0x0($t1)
        addiu       $t1, $t1, 0x4
        mult        $t7, $a2
        mfhi        $t2
        mflo        $t3
        addu        $t5, $t3, $t9
        sltu        $t3, $t5, $t9
        addu        $t3, $t3, $t2
        addu        $t4, $t3, $t8
        NOP_N64
        mult        $t6, $a3
        mfhi        $t2
        mflo        $t3
        addu        $t9, $t3, $t5
        sltu        $t3, $t9, $t5
        addu        $t3, $t3, $t2
        addu        $t8, $t3, $t4
        lw          $t6, 0x30($a0)
        addiu       $a0, $a0, 0x4
        sll         $t2, $t8, 17
        srl         $t3, $t9, 15
        or          $t9, $t3, $t2
        addu        $t3, $t6, $t9
        sw          $t3, 0x0($t0)
        addiu       $v0, $v0, -0x1
    bgtz        $v0, .L8007ECE8

    jr          $ra
END(func_8007ECE0)

/**
 * void func_8007ED74(UNK_TYPE *arg0, s32 arg1, s32 arg2, s32 arg3, s32 *arg4)
 */
LEAF(func_8007ED74)
    addiu       $v0, $zero, 0x3
    addiu       $t1, $sp, 0x10
    lw          $t5, 0x30($a0)
    lw          $t6, 0x34($a0)
    lw          $t7, 0x38($a0)
    subu        $a1, $a1, $t5
    subu        $a2, $a2, $t6
    subu        $a3, $a3, $t7

.L8007ED94:
        lw          $t0, 0x0($a0)
        lw          $t7, 0x4($a0)
        lw          $t6, 0x8($a0)
        addiu       $a0, $a0, 0x10
        mult        $t0, $a1
        mfhi        $t8
        mflo        $t9
        lw          $t0, 0x0($t1)
        addiu       $t1, $t1, 0x4
        mult        $t7, $a2
        mfhi        $t2
        mflo        $t3
        addu        $t5, $t3, $t9
        sltu        $t3, $t5, $t9
        addu        $t3, $t3, $t2
        addu        $t4, $t3, $t8
        NOP_N64
        mult        $t6, $a3
        mfhi        $t2
        mflo        $t3
        addu        $t9, $t3, $t5
        sltu        $t3, $t9, $t5
        addu        $t3, $t3, $t2
        addu        $t8, $t3, $t4
        sll         $t2, $t8, 17
        srl         $t3, $t9, 15
        or          $t9, $t3, $t2
        sw          $t9, 0x0($t0)
        addiu       $v0, $v0, -0x1
    bgtz        $v0, .L8007ED94

    jr          $ra
END(func_8007ED74)

/**
 * void matrixMulL(Mtx *, Mtx *, Mtx *);
 */
LEAF(matrixMulL)
    ori         $t8, $zero, 0x8000
    sw          $zero, 0x2C($a2)
    sw          $zero, 0x1C($a2)
    sw          $zero, 0xC($a2)
    sw          $t8, 0x3C($a2)
    addiu       $v0, $zero, 0x3
    addu        $v1, $a2, $zero
    addu        $t0, $a1, $zero
    addu        $t1, $a0, $zero

.L8007EE3C:
        lw          $t7, 0x0($t1)
        lw          $t6, 0x4($t1)
        lw          $t9, 0x0($a1)
        lw          $t5, 0x10($a1)
        mult        $t7, $t9
        mflo        $t3
        mfhi        $t2
        lw          $t8, 0x8($t1)
        lw          $t9, 0x20($a1)
        mult        $t6, $t5
        mflo        $t4
        addu        $t5, $t3, $t4
        sltu        $t3, $t5, $t4
        mfhi        $t4
        addu        $t4, $t2, $t4
        addu        $t4, $t4, $t3
        mult        $t8, $t9
        mflo        $t3
        mfhi        $t2
        addu        $t9, $t3, $t5
        sltu        $t3, $t9, $t5
        addu        $t3, $t3, $t2
        addu        $t8, $t3, $t4
        sll         $t2, $t8, 17
        srl         $t3, $t9, 15
        or          $t8, $t3, $t2
        sw          $t8, 0x0($v1)
        lw          $t9, 0x4($a1)
        lw          $t5, 0x14($a1)
        mult        $t7, $t9
        mflo        $t3
        mfhi        $t2
        lw          $t8, 0x8($t1)
        lw          $t9, 0x24($a1)
        mult        $t6, $t5
        mflo        $t4
        addu        $t5, $t3, $t4
        sltu        $t3, $t5, $t4
        mfhi        $t4
        addu        $t4, $t2, $t4
        addu        $t4, $t4, $t3
        mult        $t8, $t9
        mflo        $t3
        mfhi        $t2
        addu        $t9, $t3, $t5
        sltu        $t3, $t9, $t5
        addu        $t3, $t3, $t2
        addu        $t8, $t3, $t4
        sll         $t2, $t8, 17
        srl         $t3, $t9, 15
        or          $t8, $t3, $t2
        sw          $t8, 0x4($v1)
        lw          $t9, 0x8($a1)
        lw          $t5, 0x18($a1)
        mult        $t7, $t9
        mflo        $t3
        mfhi        $t2
        lw          $t8, 0x8($t1)
        lw          $t9, 0x28($a1)
        mult        $t6, $t5
        mflo        $t4
        addu        $t5, $t3, $t4
        sltu        $t3, $t5, $t4
        mfhi        $t4
        addu        $t4, $t2, $t4
        addu        $t4, $t4, $t3
        mult        $t8, $t9
        mflo        $t3
        mfhi        $t2
        addu        $t9, $t3, $t5
        sltu        $t3, $t9, $t5
        addu        $t3, $t3, $t2
        addu        $t8, $t3, $t4
        sll         $t2, $t8, 17
        srl         $t3, $t9, 15
        or          $t8, $t3, $t2
        sw          $t8, 0x8($v1)
        lw          $t2, 0x30($a0)
        lw          $t3, 0x0($t0)
        lw          $t4, 0x34($a0)
        lw          $t5, 0x10($t0)
        mult        $t2, $t3
        mflo        $t9
        mfhi        $t8
        lw          $t6, 0x38($a0)
        lw          $t7, 0x20($t0)
        mult        $t4, $t5
        mflo        $t3
        mfhi        $t2
        addu        $t5, $t3, $t9
        sltu        $t3, $t5, $t9
        addu        $t3, $t3, $t2
        addu        $t4, $t3, $t8
        mult        $t6, $t7
        mflo        $t3
        mfhi        $t2
        addu        $t9, $t3, $t5
        sltu        $t3, $t9, $t5
        addu        $t3, $t3, $t2
        addu        $t8, $t3, $t4
        lw          $t6, 0x30($t0)
        sll         $t2, $t8, 17
        srl         $t3, $t9, 15
        or          $t9, $t3, $t2
        addu        $t3, $t6, $t9
        sw          $t3, 0x30($a2)
        addiu       $v0, $v0, -0x1
        addiu       $v1, $v1, 0x10
        addiu       $t1, $t1, 0x10
        addiu       $a2, $a2, 0x4
        addiu      $t0, $t0, 0x4
        NOP_IQUE
    bgtz        $v0, .L8007EE3C

    jr          $ra
END(matrixMulL)

/**
 * void makeTransrateMatrix(Mtx *mtx, u32 x, u32 y, u32 z);
 *
 * Initializes `mtx` to :
 *
 * | 0x8000      0      0      0 |
 * |      0 0x8000      0      0 |
 * |      0      0 0x8000      0 |
 * |      x      y      z 0x8000 |
 *
 */
LEAF(makeTransrateMatrix)
    ori         $v0, $zero, 0x8000
    sw          $v0, 0x0($a0)
    sw          $zero, 0x4($a0)
    sw          $zero, 0x8($a0)
    sw          $zero, 0xC($a0)
    sw          $zero, 0x10($a0)
    sw          $v0, 0x14($a0)
    sw          $zero, 0x18($a0)
    sw          $zero, 0x1C($a0)
    sw          $zero, 0x20($a0)
    sw          $zero, 0x24($a0)
    sw          $v0, 0x28($a0)
    sw          $zero, 0x2C($a0)
    sw          $a1, 0x30($a0)
    sw          $a2, 0x34($a0)
    sw          $a3, 0x38($a0)
    sw          $v0, 0x3C($a0)
    NOP_IQUE
    jr          $ra
END(makeTransrateMatrix)

/**
 * void makeScaleMatrix(Mtx *mtx, u32 scale);
 *
 * Initializes `mtx` to :
 *
 * |  scale      0      0      0 |
 * |      0  scale      0      0 |
 * |      0      0  scale      0 |
 * |      0      0      0 0x8000 |
 *
 */
LEAF(makeScaleMatrix)
    ori         $v0, $zero, 0x8000
    sw          $a1, 0x0($a0)
    sw          $zero, 0x4($a0)
    sw          $zero, 0x8($a0)
    sw          $zero, 0xC($a0)
    sw          $zero, 0x10($a0)
    sw          $a1, 0x14($a0)
    sw          $zero, 0x18($a0)
    sw          $zero, 0x1C($a0)
    sw          $zero, 0x20($a0)
    sw          $zero, 0x24($a0)
    sw          $a1, 0x28($a0)
    sw          $zero, 0x2C($a0)
    sw          $zero, 0x30($a0)
    sw          $zero, 0x34($a0)
    sw          $zero, 0x38($a0)
    sw          $v0, 0x3C($a0)
    NOP_IQUE
    jr          $ra
END(makeScaleMatrix)

/**
 * void makeMatrix(Mtx *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
 */
LEAF(makeMatrix)
    addu        $t1, $ra, $zero
    addu        $t0, $a0, $zero
    lw          $t2, 0x10($sp)
    lw          $t3, 0x14($sp)
    lw          $t4, 0x18($sp)
    sw          $zero, 0x2C($t0)
    sw          $zero, 0x1C($t0)
    sw          $zero, 0xC($t0)
    ori         $t8, $zero, 0x8000
    sw          $t8, 0x3C($t0)
    sw          $t2, 0x30($t0)
    sw          $t3, 0x34($t0)
    sw          $t4, 0x38($t0)
    addu        $a0, $a2, $zero
    NOP_IQUE
    bal         func_8007EC54

    addu        $t2, $v0, $zero
    NOP_IQUE
    bal         func_8007EC98

    addu        $t3, $v0, $zero
    addu        $a0, $a3, $zero
    NOP_IQUE
    bal         func_8007EC54

    addu        $t4, $v0, $zero
    NOP_IQUE
    bal         func_8007EC98

    addu        $t5, $v0, $zero
    addu        $a0, $a1, $zero
    NOP_IQUE
    bal         func_8007EC54

    addu        $t6, $v0, $zero
    NOP_IQUE
    bal         func_8007EC98

    negu        $t8, $t6
    sw          $t8, 0x24($t0)
    NOP_N64
    multu       $t4, $v0
    mflo        $t8
    sra         $t9, $t8, 15
    sw          $t9, 0x4($t0)
    multu       $t5, $v0
    mflo        $t8
    sra         $t9, $t8, 15
    sw          $t9, 0x14($t0)
    multu       $t2, $v0
    mflo        $t8
    sra         $t9, $t8, 15
    sw          $t9, 0x20($t0)
    NOP_N64
    multu       $t3, $v0
    mflo        $t8
    sra         $t9, $t8, 15
    sw          $t9, 0x28($t0)
    NOP_N64
    multu       $t2, $t6
    mflo        $t8
    sra         $v0, $t8, 15
    nop
    multu       $t5, $t3
    mflo        $t9
    nop
    nop
    multu       $t4, $v0
    mflo        $t8
    addu        $t7, $t8, $t9
    sra         $t8, $t7, 15
    sw          $t8, 0x0($t0)
    multu       $t4, $t3
    mflo        $t9
    nop
    nop
    multu       $t5, $v0
    mflo        $t8
    subu        $t7, $t8, $t9
    sra         $t8, $t7, 15
    sw          $t8, 0x10($t0)
    NOP_N64
    multu       $t3, $t6
    mflo        $t8
    sra         $v0, $t8, 15
    nop
    multu       $t5, $t2
    mflo        $t9
    nop
    nop
    multu       $t4, $v0
    mflo        $t8
    subu        $t7, $t8, $t9
    sra         $t8, $t7, 15
    sw          $t8, 0x8($t0)
    multu       $t4, $t2
    mflo        $t9
    nop
    nop
    multu       $t5, $v0
    mflo        $t8
    addu        $t7, $t8, $t9
    sra         $t8, $t7, 15
    sw          $t8, 0x18($t0)
    addu        $ra, $t1, $zero
    jr          $ra
END(makeMatrix)

/**
 * void func_8007F214(UNK_TYPE *arg0, u32 arg1, s32 arg2, s32 arg3, s32 arg4);
 *
 * `arg0` may be a `Mtx *`
 */
LEAF(func_8007F214)
    addu        $t1, $ra, $zero
    addu        $t0, $a0, $zero
    lw          $t2, 0x10($sp)
    sw          $zero, 0x2C($t0)
    sw          $zero, 0x1C($t0)
    sw          $zero, 0xC($t0)
    sw          $a2, 0x30($t0)
    sw          $a3, 0x34($t0)
    sw          $t2, 0x38($t0)
    ori         $t2, $zero, 0x8000
    sw          $t2, 0x3C($t0)
    addu        $a0, $a1, $zero
    NOP_IQUE
    bal         func_8007EC54

    addu        $t3, $v0, $zero
    NOP_IQUE
    bal         func_8007EC98

    sw          $t2, 0x0($t0)
    sw          $zero, 0x4($t0)
    sw          $zero, 0x8($t0)
    sw          $zero, 0x10($t0)
    sw          $v0, 0x14($t0)
    sw          $t3, 0x18($t0)
    sw          $zero, 0x20($t0)
    negu        $t8, $t3
    sw          $t8, 0x24($t0)
    sw          $v0, 0x28($t0)
    addu        $ra, $t1, $zero
    jr          $ra
END(func_8007F214)

/**
 * void func_8007F284(UNK_TYPE *arg0, u32 arg1, s32 arg2, s32 arg3, s32 arg4);
 *
 * `arg0` may be a `Mtx *`
 */
LEAF(func_8007F284)
    addu        $t1, $ra, $zero
    addu        $t0, $a0, $zero
    lw          $t2, 0x10($sp)
    sw          $zero, 0x2C($t0)
    sw          $zero, 0x1C($t0)
    sw          $zero, 0xC($t0)
    sw          $a2, 0x30($t0)
    sw          $a3, 0x34($t0)
    sw          $t2, 0x38($t0)
    ori         $t2, $zero, 0x8000
    sw          $t2, 0x3C($t0)
    addu        $a0, $a1, $zero
    NOP_IQUE
    bal         func_8007EC54

    addu        $t3, $v0, $zero
    NOP_IQUE
    bal         func_8007EC98

    sw          $v0, 0x0($t0)
    sw          $zero, 0x4($t0)
    negu        $t8, $t3
    sw          $t8, 0x8($t0)
    sw          $zero, 0x10($t0)
    sw          $t2, 0x14($t0)
    sw          $zero, 0x18($t0)
    sw          $t3, 0x20($t0)
    sw          $zero, 0x24($t0)
    sw          $v0, 0x28($t0)
    addu        $ra, $t1, $zero
    jr          $ra
END(func_8007F284)

/**
 * void func_8007F2F4(UNK_TYPE *arg0, u32 arg1, s32 arg2, s32 arg3, s32 arg4);
 *
 * `arg0` may be a `Mtx *`
 */
LEAF(func_8007F2F4)
    addu        $t1, $ra, $zero
    addu        $t0, $a0, $zero
    lw          $t2, 0x10($sp)
    sw          $zero, 0x2C($t0)
    sw          $zero, 0x1C($t0)
    sw          $zero, 0xC($t0)
    sw          $a2, 0x30($t0)
    sw          $a3, 0x34($t0)
    sw          $t2, 0x38($t0)
    ori         $t2, $zero, 0x8000
    sw          $t2, 0x3C($t0)
    addu        $a0, $a1, $zero
    NOP_IQUE
    bal         func_8007EC54

    addu        $t3, $v0, $zero
    NOP_IQUE
    bal         func_8007EC98

    sw          $v0, 0x0($t0)
    sw          $t3, 0x4($t0)
    sw          $zero, 0x8($t0)
    negu        $t8, $t3
    sw          $t8, 0x10($t0)
    sw          $v0, 0x14($t0)
    sw          $zero, 0x18($t0)
    sw          $zero, 0x20($t0)
    sw          $zero, 0x24($t0)
    sw          $t2, 0x28($t0)
    addu        $ra, $t1, $zero
    jr          $ra
END(func_8007F2F4)

/**
 * void func_8007F364(UNK_TYPE *arg0, s32 arg1, s32 arg2);
 *
 * `arg0` may be a `Mtx *`
 */
LEAF(func_8007F364)
    addu        $t1, $ra, $zero
    addu        $t0, $a0, $zero
    sw          $zero, 0x2C($t0)
    sw          $zero, 0x1C($t0)
    sw          $zero, 0xC($t0)
    sw          $zero, 0x30($t0)
    sw          $zero, 0x34($t0)
    sw          $zero, 0x38($t0)
    ori         $t2, $zero, 0x8000
    sw          $t2, 0x3C($t0)
    addu        $a0, $a2, $zero
    NOP_IQUE
    bal         func_8007EC54

    addu        $t2, $v0, $zero
    NOP_IQUE
    bal         func_8007EC98

    addu        $t3, $v0, $zero
    addu        $a0, $a1, $zero
    NOP_IQUE
    bal         func_8007EC54

    addu        $t4, $v0, $zero
    NOP_IQUE
    bal         func_8007EC98

    sw          $t3, 0x0($t0)
    sw          $t2, 0x4($t0)
    sw          $zero, 0x8($t0)
    negu        $t8, $t2
    multu       $t8, $v0
    mflo        $t9
    sra         $t8, $t9, 15
    sw          $t8, 0x10($t0)
    NOP_N64
    multu       $t3, $v0
    mflo        $t9
    sra         $t8, $t9, 15
    sw          $t8, 0x14($t0)
    sw          $t4, 0x18($t0)
    NOP_N64
    multu       $t2, $t4
    mflo        $t9
    sra         $t8, $t9, 15
    sw          $t8, 0x20($t0)
    negu        $t8, $t4
    multu       $t8, $t3
    mflo        $t9
    sra         $t8, $t9, 15
    sw          $t8, 0x24($t0)
    sw          $v0, 0x28($t0)
    addu        $ra, $t1, $zero
    jr          $ra
END(func_8007F364)

/**
 * void matrixConv(Mtx *arg0, Mtx *arg1, s32 arg2);
 */
LEAF(matrixConv)
    lui         $t0, (0xFFFF0000 >> 16)
    addiu       $v0, $zero, 0x8
    NOP_IQUE
    beqz        $a2, .L8007F4CC

    addiu       $v0, $zero, 0x6
    NOP_IQUE
    bgtz        $a2, .L8007F484

    negu        $a2, $a2
    addiu       $a2, $a2, -0x1

    .L8007F43C:
        lw          $t8, 0x0($a0)
        lw          $t9, 0x4($a0)
        addiu       $a0, $a0, 0x8
        addiu       $v0, $v0, -0x1
        srav        $t2, $t8, $a2
        srav        $t3, $t9, $a2
        and         $t4, $t2, $t0
        srl         $t5, $t3, 16
        sll         $t6, $t2, 16
        andi        $t7, $t3, 0xFFFF
        or          $t8, $t4, $t5
        or          $t9, $t6, $t7
        sw          $t8, 0x0($a1)
        sw          $t9, 0x20($a1)
        addiu       $a1, $a1, 0x4
        NOP_IQUE
    bgtz        $v0, .L8007F43C

    b           .L8007F4C8

.L8007F484:
    addiu       $a2, $a2, 0x1

    .L8007F488:
        lw          $t8, 0x0($a0)
        lw          $t9, 0x4($a0)
        addiu       $a0, $a0, 0x8
        addiu       $v0, $v0, -0x1
        sllv        $t2, $t8, $a2
        sllv        $t3, $t9, $a2
        and         $t4, $t2, $t0
        srl         $t5, $t3, 16
        sll         $t6, $t2, 16
        andi        $t7, $t3, 0xFFFF
        or          $t8, $t4, $t5
        or          $t9, $t6, $t7
        sw          $t8, 0x0($a1)
        sw          $t9, 0x20($a1)
        addiu       $a1, $a1, 0x4
        NOP_IQUE
    bgtz        $v0, .L8007F488

.L8007F4C8:
    addiu       $v0, $zero, 0x2

    .L8007F4CC:
        lw          $t8, 0x0($a0)
        lw          $t9, 0x4($a0)
        addiu       $a0, $a0, 0x8
        addiu       $v0, $v0, -0x1
        sll         $t2, $t8, 1
        sll         $t3, $t9, 1
        and         $t4, $t2, $t0
        srl         $t5, $t3, 16
        sll         $t6, $t2, 16
        andi        $t7, $t3, 0xFFFF
        or          $t8, $t4, $t5
        or          $t9, $t6, $t7
        sw          $t8, 0x0($a1)
        sw          $t9, 0x20($a1)
        addiu       $a1, $a1, 0x4
        NOP_IQUE
    bgtz        $v0, .L8007F4CC

    jr          $ra
END(matrixConv)

/**
 * void func_8007F514(UNK_TYPE *arg0, UNK_TYPE *arg1);
 *
 * `arg0` and `arg1` may be `Mtx *`
 */
LEAF(func_8007F514)
    addiu       $t8, $zero, 0x4

.L8007F518:
    lw          $t2, 0x0($a1)
    lw          $t3, 0x4($a1)
    lw          $t4, 0x8($a1)
    lw          $t5, 0xC($a1)
    sw          $t2, 0x0($a0)
    sw          $t3, 0x4($a0)
    sw          $t4, 0x8($a0)
    sw          $t5, 0xC($a0)
    addi        $t8, $t8, -0x1
    addi        $a0, $a0, 0x10
    addi        $a1, $a1, 0x10
    NOP_IQUE
    bgtz        $t8, .L8007F518

    jr          $ra
END(func_8007F514)

/**
 * void func_8007F550(UNK_TYPE *arg0, u32 arg1, s32 arg2, s32 arg3, s32 arg4);
 *
 * `arg0` may be a `Mtx *`
 */
LEAF(func_8007F550)
    addu        $t1, $ra, $zero
    lw          $t0, 0x10($sp)
    NOP_IQUE
    bal         func_8007EC98

    addu        $v1, $v0, $zero
    NOP_IQUE
    bal         func_8007EC54

    lw          $t7, 0x0($t0)
    lw          $t6, 0x0($a3)
    subu        $t9, $t7, $a2
    NOP_N64
    mult        $t9, $v1
    mfhi        $t2
    mflo        $t3
    subu        $t8, $t6, $a1
    negu        $t9, $t9
    NOP_N64
    mult        $t8, $v0
    mfhi        $t4
    mflo        $t5
    addu        $a0, $t3, $t5
    sltu        $t6, $a0, $t5
    addu        $t7, $t6, $t2
    addu        $t6, $t7, $t4
    srl         $t5, $a0, 15
    sll         $t4, $t6, 17
    NOP_N64
    mult        $t8, $v1
    mfhi        $t2
    mflo        $t3
    or          $v1, $t4, $t5
    addu        $a2, $a2, $v1
    NOP_N64
    mult        $t9, $v0
    mfhi        $t4
    mflo        $t5
    addu        $a0, $t3, $t5
    sltu        $t6, $a0, $t5
    addu        $t7, $t6, $t2
    addu        $v1, $t7, $t4
    srl         $t5, $a0, 15
    sll         $t4, $v1, 17
    or          $v1, $t4, $t5
    addu        $a1, $a1, $v1
    sw          $a2, 0x0($t0)
    sw          $a1, 0x0($a3)
    addu        $ra, $t1, $zero
    jr          $ra
END(func_8007F550)

/**
 * s32 func_8007F60C(s32 arg0, s32 arg1)
 */
LEAF(func_8007F60C)
    andi        $t2, $a0, 0xFFFF
    andi        $t3, $a1, 0xFFFF
    lui         $v0, (0x10000 >> 16)
    slt         $at, $t2, $t3
    beqz        $at, .L8007F630

    addu        $t4, $t2, $v0
    addu        $t5, $t3, $zero
    NOP_IQUE
    b           .L8007F638

.L8007F630:
    addu        $t4, $t2, $zero
    addu        $t5, $t3, $v0
.L8007F638:
    subu        $v0, $t3, $t2
    subu        $v1, $t5, $t4
    addu        $t2, $v0, $zero
    bgez        $v0, .L8007F64C

    sub         $t2, $zero, $v0
.L8007F64C:
    addu        $t3, $v1, $zero
    bgez        $v1, .L8007F658

    sub         $t3, $zero, $v1
.L8007F658:
    slt         $at, $t3, $t2
    beqz        $at, .L8007F668

    addu        $v0, $v1, $zero
.L8007F668:
    jr          $ra
END(func_8007F60C)

/**
 * s32 func_8007F670(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
 */
LEAF(func_8007F670)
    subu        $v1, $a3, $a0
    lw          $t6, 0x10($sp)
    mult        $v1, $v1
    mflo        $t8
    subu        $t0, $t6, $a1
    lw          $t7, 0x14($sp)
    mult        $t0, $t0
    mflo        $t9
    subu        $t1, $t7, $a2
    addu        $t2, $t8, $t9
    mult        $t1, $t1
    mflo        $t3
    addu        $t4, $t2, $t3
    mtc1        $t4, $ft0
    NOP_N64
    cvt.s.w     $fv0, $ft0
    sqrt.s      $ft1, $fv0
    trunc.w.s   $ft2, $ft1
    mfc1        $v0, $ft2
    nop
    jr          $ra
END(func_8007F670)

/**
 * s32 func_8007F6C4(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
 */
LEAF(func_8007F6C4)
    lw          $t8, 0x10($sp)
    lw          $t9, 0x14($sp)
    subu        $v0, $a3, $a0
    subu        $t8, $t8, $a1
    subu        $t9, $t9, $a2
    mtc1        $v0, $ft0
    mtc1        $t8, $ft1
    mtc1        $t9, $ft2
    cvt.s.w     $fv0, $ft0
    cvt.s.w     $ft0, $ft1
    cvt.s.w     $ft1, $ft2
    mul.s       $fv0, $fv0, $fv0
    NOP_N64
    mul.s       $ft0, $ft0, $ft0
    NOP_N64
    mul.s       $ft1, $ft1, $ft1
    add.s       $ft2, $fv0, $ft0
    add.s       $fv0, $ft1, $ft2
    sqrt.s      $ft1, $fv0
    trunc.w.s   $ft2, $ft1
    mfc1        $v0, $ft2
    nop
    jr          $ra
END(func_8007F6C4)

/**
 * s32 func_8007F720(s32 arg0, s32 arg1);
 */
LEAF(func_8007F720)
    mtc1        $a0, $ft0
    mtc1        $a1, $ft1
    cvt.s.w     $fv0, $ft0
    cvt.s.w     $ft0, $ft1
    mul.s       $ft1, $fv0, $fv0
    NOP_N64
    mul.s       $ft2, $ft0, $ft0
    add.s       $fv0, $ft1, $ft2
    sqrt.s      $ft1, $fv0
    trunc.w.s   $ft2, $ft1
    mfc1        $v0, $ft2
    nop
    jr          $ra
END(func_8007F720)

/**
 * s32 func_8007F754(s32 arg0, s32 arg1, s32 arg2);
 */
LEAF(func_8007F754)
    mtc1        $a0, $ft0
    mtc1        $a1, $ft1
    mtc1        $a2, $ft2
    cvt.s.w     $fv0, $ft0
    cvt.s.w     $ft0, $ft1
    mul.s       $ft1, $fv0, $fv0
    NOP_N64
    mul.s       $fv0, $ft0, $ft0
    cvt.s.w     $ft0, $ft2
    mul.s       $ft2, $ft0, $ft0
    add.s       $ft0, $ft1, $fv0
    add.s       $fv0, $ft0, $ft2
    sqrt.s      $ft1, $fv0
    trunc.w.s   $ft2, $ft1
    mfc1        $v0, $ft2
    nop
    jr          $ra
END(func_8007F754)

/**
 * s32 func_8007F798(s32 arg0, s32 arg1, s32 arg2);
 */
LEAF(func_8007F798)
    NOP_N64
    xor         $t9, $a0, $a1
    xor         $t8, $t9, $a2
    addu        $t2, $a0, $zero
    bgez        $a0, .L8007F7B0

    sub         $t2, $zero, $a0
.L8007F7B0:
    addu       $t3, $a1, $zero
    bgez        $a1, .L8007F7BC

    sub         $t3, $zero, $a1
.L8007F7BC:
    addu        $t7, $a2, $zero
    bgez        $a2, .L8007F7C8

    sub         $t7, $zero, $a2
.L8007F7C8:
    NOP_N64
    mult        $t2, $t3
    addiu       $t9, $zero, 0x20
    addu        $v0, $zero, $zero
    mflo        $t1
    mfhi        $t0

    .L8007F7E0:
        sll         $v0, $v0, 1
        slt         $at, $t0, $t7
        bnez        $at, .L8007F7F8

        ori         $v0, $v0, 0x1
        subu        $t0, $t0, $t7
    .L8007F7F8:
        addiu       $t9, $t9, -0x1
        srl         $t2, $t1, 31
        sll         $t3, $t0, 1
        sll         $t1, $t1, 1
        or          $t0, $t2, $t3
        NOP_IQUE
    bgez        $t9, .L8007F7E0

    bgez        $t8, .L8007F81C

    sub         $v0, $zero, $v0

.L8007F81C:
    jr          $ra
END(func_8007F798)


/**
 * void func_8007F824(UNK_TYPE *arg0, u32 arg1, s32 arg2, s32 arg3, s32 arg4);
 *
 * `arg0` may be a `Mtx *`
 */
LEAF(func_8007F824)
    addu        $t1, $ra, $zero
    lw          $t0, 0x10($sp)
    NOP_IQUE
    bal         func_8007EC54

    negu        $t4, $v0
    NOP_IQUE
    bal         func_8007EC98

    addu        $t5, $v0, $zero
    addu        $a0, $a1, $zero
    NOP_IQUE
    bal         func_8007EC54

    addu        $t2, $v0, $zero
    NOP_IQUE
    bal         func_8007EC98

    addu        $t3, $v0, $zero
    sw          $t4, 0x0($a3)
    NOP_N64
    multu       $t2, $t5
    mflo        $t8
    sra         $t9, $t8, 15
    sw          $t9, 0x0($a2)
    NOP_N64
    multu       $t3, $t5
    mflo        $t8
    sra         $t9, $t8, 15
    sw          $t9, 0x0($t0)
    addu        $ra, $t1, $zero
    jr          $ra
END(func_8007F824)

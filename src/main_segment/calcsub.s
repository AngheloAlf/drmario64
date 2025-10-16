/**
 * Original assumed filename: calcsub.s
 *
 * The Gamecube version implements these functions in calcsub.c
 */

#include "hasm.h"

.section .text, "ax"

/*
A few notes about formatting this file :
- Each branch is followed by an empty line.
- Loops are indented whenever possible.
- Each function should have its C declaration as a comment.
*/

/**
 * void waitEQ4(vs32 *var, s32 data);
 *
 * This function does not halt until `*var` is equal to `data`.
 *
 * Roughly equivalent to:
 * ```
void waitEQ4(vs32 *var, s32 data) {
    while (*var - data != 0) {}
}
 * ```
 */
LEAF(waitEQ4)
1:
    lw          $v0, 0x0($a0)
    subu        $v0, $v0, $a1
    bnez        $v0, 1b

    jr          $ra
END(waitEQ4)

/**
 * s32 sqrtS(s32 value);
 *
 * Returns square root of `value`.
 *
 * Roughly equivalent to:
 * ```
s32 sqrtS(s32 value) {
    return sqrtf(value);
}
 * ```
 */
LEAF(sqrtS)
    mtc1        $a0, $ft0
    cvt.s.w     $fv0, $ft0
    sqrt.s      $ft1, $fv0
    trunc.w.s   $ft2, $ft1
    mfc1        $v0, $ft2

    jr          $ra
END(sqrtS)

/**
 * s32 sqrtL(s32 arg0, s32 arg1);
 *
 * Roughly equivalent to:
 * ```
s32 sqrtL(s32 arg0, s32 arg1) {
    s32 v0;
    s32 v1;
    s32 t8;
    s32 t9;
    s32 i;

    v0 = 0;
    v1 = 0;

    t8 = arg1 < 0;
    t9 = arg0 < 0;

    arg1 = arg1 << 1;
    arg0 = (arg0 << 1) | t8;
    v1 = (v1 << 1) | t9;

    for (i = 0; i < 32; i++) {
        t8 = arg1 < 0;
        t9 = arg0 < 0;

        arg1 = arg1 << 1;
        arg0 = (arg0 << 1) | t8;
        v1 = (v1 << 1) | t9;
        v0 = (v0 << 1) + 1;
        if (v1 >= v0) {
            v1 -= v0;
            v0 += 2;
        }

        t8 = arg1 < 0;
        t9 = arg0 < 0;

        arg1 = arg1 << 1;
        arg0 = (arg0 << 1) | t8;
        v1 = (v1 << 1) | t9;
        v0 = v0 - 1;
    }
    return v0 >> 1;
}
 * ```
 */
LEAF(sqrtL)
    move        $v0, $zero
    move        $v1, $zero
    li          $t0, 0x20
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
        bltu        $v1, $v0, .L8007EAB8

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

    srl         $v0, $v0, 1
    jr          $ra
END(sqrtL)

.section .data, "wa"

SYM_START(D_800AB320)
    .byte 0x00, 0x03, 0x06, 0x08
    .byte 0x0A, 0x0D, 0x0F, 0x11
    .byte 0x13, 0x15, 0x17, 0x19
    .byte 0x1B, 0x1C, 0x1E, 0x1F
    .byte 0x20, 0x20, 0x20, 0x20
SYM_END(D_800AB320)

SYM_START(D_800AB334)
    .word 0x00000000, 0x00648D18, 0x00C9393C, 0x012E239C
    .word 0x01936BB8, 0x01F93183, 0x025F958E, 0x02C6B932
    .word 0x032EBEBC, 0x0397C99D, 0x0401FE9D, 0x046D840F
    .word 0x04DA820D, 0x054922B8, 0x05B9927D, 0x062C0065
    .word 0x06A09E66, 0x0717A1C6, 0x07914383, 0x080DC0CD
    .word 0x088D5B8C, 0x09105AF7, 0x09970C44, 0x0A21C36D
    .word 0x0AB0DC15, 0x0B44BA8A, 0x0BDDCCF6, 0x0C7C8CBE
    .word 0x0D218015, 0x0DCD3BE0, 0x0E8065E3, 0x0F3BB757
    .word 0x10000000, 0xFFFFFFFF
SYM_END(D_800AB334)

SYM_START(D_800AB3BC)
    .word 0x028BC48E, 0x028AFB8E, 0x02896A18, 0x02871113
    .word 0x0283F1FB, 0x02800EBC, 0x027B69B9, 0x027605D4
    .word 0x026FE65E, 0x02690F18, 0x02618440, 0x02594A7D
    .word 0x025066DF, 0x0246DEE6, 0x023CB868, 0x0231F9B4
    .word 0x0226A964, 0x021ACE77, 0x020E7038, 0x02019645
    .word 0x01F44893, 0x01E68F51, 0x01D872F9, 0x01C9FC39
    .word 0x01BB3404, 0x01AC2375, 0x019CD3D2, 0x018D4E95
    .word 0x017D9D49, 0x016DC99D, 0x015DDD57, 0x014DE244
    .word 0x013DE246
SYM_END(D_800AB3BC)

.section .text, "ax"

/**
 * s16 get_angle(s32 x, s32 y);
 *
 * Compute an angle by using atan2.
 *
 *
 * Roughly equivalent to:
 * ```
s16 get_angle(s32 x, s32 y) {
    #define ATAN2_FLG_SWAP 0x1
    #define ATAN2_FLG_NEGY 0x10
    #define ATAN2_FLG_NEGX 0x100

    s32 angle;
    u32 flags;
    s32 temp_t8_2;
    s32 temp_t9;
    s32 temp_a0;
    s32 var_v1;

    if (x == 0) {
        if (y == 0) {
            return 0;
        } if (y < 0) {
            // -PI/2
            return 0xC000;
        }
        // PI/2
        return 0x4000;
    }

    if (x < 0) {
        x = -x;
        flags = ATAN2_FLG_NEGX | ATAN2_FLG_NEGY;
    } else {
        flags = 0;
    }

    if (y == 0) {
        if (flags == 0) {
            return 0;
        }
        // PI
        return 0x8000;
    }

    if (y < 0) {
        y = -y;
        flags ^= ATAN2_FLG_NEGY;
    }

    if (x < y) {
        // swap
        s32 temp_t8;

        temp_t8 = x;
        x = y;
        y = temp_t8;

        flags ^= ATAN2_FLG_SWAP;
    }

    // Calculate arctan(y/x) I think?
    temp_a0 = ((0x40000000U / (u32) x) * y) >> 2;

    var_v1 = D_800AB320[temp_a0 >> 0x18];
    do {
        temp_t9 = D_800AB334[var_v1];
        var_v1++;
    } while ((temp_a0 - temp_t9) >= 0);

    temp_t8_2 = D_800AB334[var_v1-2];

    angle = (var_v1 - 2) << 8;
    if (temp_a0 != temp_t8_2) {
        temp_t8_2 = ((u64)(temp_a0 - temp_t8_2) / (u64)D_800AB3BC[var_v1 - 2]) >> 32;
        angle |= (temp_t8_2 >> 8) & 0xFF;
    }

    if (flags & ATAN2_FLG_SWAP) {
        angle = 0x4000 - angle;
    }
    if (flags & ATAN2_FLG_NEGY) {
        angle = -angle;
    }
    if (flags & ATAN2_FLG_NEGX) {
        angle -= 0x8000;
    }
    return angle;

    #undef ATAN2_FLG_SWAP
    #undef ATAN2_FLG_NEGY
    #undef ATAN2_FLG_NEGX
}
 * ```
 */
LEAF(get_angle)

    #define ATAN2_FLG_SWAP 0x1
    #define ATAN2_FLG_NEGY 0x10
    #define ATAN2_FLG_NEGX 0x100

    move        $t4, $zero

    bnez        $a0, .Latan2_x_not_zero
    bnez        $a1, .Latan2_x_zero_y_not_zero

    /* x and y are 0 */
    li          $v0, 0x0
    b           .Latan2_ret

.Latan2_x_zero_y_not_zero:
    bgez        $a1, .Latan2_x_zero_y_ge_zero

    li          $v0, 0xC000 /* -PI/2 */
    b           .Latan2_ret

.Latan2_x_zero_y_ge_zero:
    li          $v0, 0x4000 /* PI/2 */
    b           .Latan2_ret

.Latan2_x_not_zero:

    bgez        $a0, .Latan2_x_ge_zero

    /* x < 0 */
    negu        $a0, $a0
    xori        $t4, $t4, ATAN2_FLG_NEGX | ATAN2_FLG_NEGY
.Latan2_x_ge_zero:

    bnez        $a1, .Latan2_y_non_zero

    bnez        $t4, .Latan2_y_zero_x_negative

    /* Both are zero */
    li          $v0, 0x0
    b           .Latan2_ret

.Latan2_y_zero_x_negative:
    li          $v0, 0x8000 /* PI */
    b           .Latan2_ret

.Latan2_y_non_zero:

    bgez        $a1, 1f

    /* y < 0 */
    negu        $a1, $a1
    xori        $t4, $t4, ATAN2_FLG_NEGY

1:
    subu        $t8, $a0, $a1
    bgez        $t8, .Latan2_after_swap

    /* (x < y) => swap them */
    move        $t8, $a0
    move        $a0, $a1
    move        $a1, $t8
    xori        $t4, $t4, ATAN2_FLG_SWAP

.Latan2_after_swap:
    li          $t8, 0x40000000
    divu        $t8, $t8, $a0
    mul         $t9, $t8, $a1
    srl         $a0, $t9, 2
    srl         $t8, $a0, 24
    lbu         $v1, (D_800AB320)($t8)
    sll         $t2, $v1, 2

    .Latan2_search:
        lw          $t9, (D_800AB334)($t2)
        addiu       $v1, $v1, 0x1
        addiu       $t2, $t2, 0x4
        subu        $t8, $a0, $t9
    bgez        $t8, .Latan2_search

    addiu       $v1, $v1, -0x2
    lw          $t8, (D_800AB334 - 0x8)($t2)
    sll         $v0, $v1, 8

    beq         $a0, $t8, .Latan2_flg_swap

    /* Interpolate a value */
    subu        $t3, $a0, $t8
    lw          $t8, (D_800AB3BC - 0x8)($t2)
    multu       $t3, $t8
    mfhi        $t8
    srl         $t8, $t8, 8
    andi        $t9, $t8, 0xFF
    or          $v0, $v0, $t9

.Latan2_flg_swap:
    andi        $t8, $t4, ATAN2_FLG_SWAP
    beqz        $t8, .Latan2_flg_negy

    li          $t8, 0x4000
    subu        $v0, $t8, $v0

.Latan2_flg_negy:
    andi        $t8, $t4, ATAN2_FLG_NEGY
    beqz        $t8, .Latan2_flg_negx

    negu        $v0, $v0

.Latan2_flg_negx:
    andi        $t8, $t4, ATAN2_FLG_NEGX
    beqz        $t8, .Latan2_ret

    addiu       $v0, $v0, -0x8000

.Latan2_ret:
    sll         $t8, $v0, 16
    sra         $v0, $t8, 16
    jr          $ra

    #undef ATAN2_FLG_SWAP
    #undef ATAN2_FLG_NEGY
    #undef ATAN2_FLG_NEGX

END(get_angle)

.section .data, "wa"

/**
 * Original name: sintable
 */
SYM_START(calc_sintable)
               /*            0        1        2        3        4        5        6        7 */
    /* 0x000 */ .short  0x0000,  0x00C9,  0x0192,  0x025B,  0x0324,  0x03ED,  0x04B6,  0x057F
    /* 0x008 */ .short  0x0648,  0x0711,  0x07D9,  0x08A2,  0x096B,  0x0A33,  0x0AFB,  0x0BC4
    /* 0x010 */ .short  0x0C8C,  0x0D54,  0x0E1C,  0x0EE4,  0x0FAB,  0x1073,  0x113A,  0x1201
    /* 0x018 */ .short  0x12C8,  0x138F,  0x1455,  0x151C,  0x15E2,  0x16A8,  0x176E,  0x1833
    /* 0x020 */ .short  0x18F9,  0x19BE,  0x1A83,  0x1B47,  0x1C0C,  0x1CD0,  0x1D93,  0x1E57
    /* 0x028 */ .short  0x1F1A,  0x1FDD,  0x209F,  0x2162,  0x2224,  0x22E5,  0x23A7,  0x2467
    /* 0x030 */ .short  0x2528,  0x25E8,  0x26A8,  0x2768,  0x2827,  0x28E5,  0x29A4,  0x2A62
    /* 0x038 */ .short  0x2B1F,  0x2BDC,  0x2C99,  0x2D55,  0x2E11,  0x2ECC,  0x2F87,  0x3042
    /* 0x040 */ .short  0x30FC,  0x31B5,  0x326E,  0x3327,  0x33DF,  0x3497,  0x354E,  0x3604
    /* 0x048 */ .short  0x36BA,  0x3770,  0x3825,  0x38D9,  0x398D,  0x3A40,  0x3AF3,  0x3BA5
    /* 0x050 */ .short  0x3C57,  0x3D08,  0x3DB8,  0x3E68,  0x3F17,  0x3FC6,  0x4074,  0x4121
    /* 0x058 */ .short  0x41CE,  0x427A,  0x4326,  0x43D1,  0x447B,  0x4524,  0x45CD,  0x4675
    /* 0x060 */ .short  0x471D,  0x47C4,  0x486A,  0x490F,  0x49B4,  0x4A58,  0x4AFB,  0x4B9E
    /* 0x068 */ .short  0x4C40,  0x4CE1,  0x4D81,  0x4E21,  0x4EC0,  0x4F5E,  0x4FFB,  0x5098
    /* 0x070 */ .short  0x5134,  0x51CF,  0x5269,  0x5303,  0x539B,  0x5433,  0x54CA,  0x5560
    /* 0x078 */ .short  0x55F6,  0x568A,  0x571E,  0x57B1,  0x5843,  0x58D4,  0x5964,  0x59F4
    /* 0x080 */ .short  0x5A82,  0x5B10,  0x5B9D,  0x5C29,  0x5CB4,  0x5D3E,  0x5DC8,  0x5E50
    /* 0x088 */ .short  0x5ED7,  0x5F5E,  0x5FE4,  0x6068,  0x60EC,  0x616F,  0x61F1,  0x6272
    /* 0x090 */ .short  0x62F2,  0x6371,  0x63EF,  0x646C,  0x64E9,  0x6564,  0x65DE,  0x6657
    /* 0x098 */ .short  0x66D0,  0x6747,  0x67BD,  0x6832,  0x68A7,  0x691A,  0x698C,  0x69FD
    /* 0x0A0 */ .short  0x6A6E,  0x6ADD,  0x6B4B,  0x6BB8,  0x6C24,  0x6C8F,  0x6CF9,  0x6D62
    /* 0x0A8 */ .short  0x6DCA,  0x6E31,  0x6E97,  0x6EFB,  0x6F5F,  0x6FC2,  0x7023,  0x7083
    /* 0x0B0 */ .short  0x70E3,  0x7141,  0x719E,  0x71FA,  0x7255,  0x72AF,  0x7308,  0x735F
    /* 0x0B8 */ .short  0x73B6,  0x740B,  0x7460,  0x74B3,  0x7505,  0x7556,  0x75A6,  0x75F4
    /* 0x0C0 */ .short  0x7642,  0x768E,  0x76D9,  0x7723,  0x776C,  0x77B4,  0x77FB,  0x7840
    /* 0x0C8 */ .short  0x7885,  0x78C8,  0x790A,  0x794A,  0x798A,  0x79C9,  0x7A06,  0x7A42
    /* 0x0D0 */ .short  0x7A7D,  0x7AB7,  0x7AEF,  0x7B27,  0x7B5D,  0x7B92,  0x7BC6,  0x7BF9
    /* 0x0D8 */ .short  0x7C2A,  0x7C5A,  0x7C89,  0x7CB7,  0x7CE4,  0x7D0F,  0x7D3A,  0x7D63
    /* 0x0E0 */ .short  0x7D8A,  0x7DB1,  0x7DD6,  0x7DFB,  0x7E1E,  0x7E3F,  0x7E60,  0x7E7F
    /* 0x0E8 */ .short  0x7E9D,  0x7EBA,  0x7ED6,  0x7EF0,  0x7F0A,  0x7F22,  0x7F38,  0x7F4E
    /* 0x0F0 */ .short  0x7F62,  0x7F75,  0x7F87,  0x7F98,  0x7FA7,  0x7FB5,  0x7FC2,  0x7FCE
    /* 0x0F8 */ .short  0x7FD9,  0x7FE2,  0x7FEA,  0x7FF1,  0x7FF6,  0x7FFA,  0x7FFE,  0x7FFF
    /* 0x100 */ .short  0x7FFF,  0x7FFF,  0x7FFE,  0x7FFA,  0x7FF6,  0x7FF1,  0x7FEA,  0x7FE2
    /* 0x108 */ .short  0x7FD9,  0x7FCE,  0x7FC2,  0x7FB5,  0x7FA7,  0x7F98,  0x7F87,  0x7F75
    /* 0x110 */ .short  0x7F62,  0x7F4E,  0x7F38,  0x7F22,  0x7F0A,  0x7EF0,  0x7ED6,  0x7EBA
    /* 0x118 */ .short  0x7E9D,  0x7E7F,  0x7E60,  0x7E3F,  0x7E1E,  0x7DFB,  0x7DD6,  0x7DB1
    /* 0x120 */ .short  0x7D8A,  0x7D63,  0x7D3A,  0x7D0F,  0x7CE4,  0x7CB7,  0x7C89,  0x7C5A
    /* 0x128 */ .short  0x7C2A,  0x7BF9,  0x7BC6,  0x7B92,  0x7B5D,  0x7B27,  0x7AEF,  0x7AB7
    /* 0x130 */ .short  0x7A7D,  0x7A42,  0x7A06,  0x79C9,  0x798A,  0x794A,  0x790A,  0x78C8
    /* 0x138 */ .short  0x7885,  0x7840,  0x77FB,  0x77B4,  0x776C,  0x7723,  0x76D9,  0x768E
    /* 0x140 */ .short  0x7642,  0x75F4,  0x75A6,  0x7556,  0x7505,  0x74B3,  0x7460,  0x740B
    /* 0x148 */ .short  0x73B6,  0x735F,  0x7308,  0x72AF,  0x7255,  0x71FA,  0x719E,  0x7141
    /* 0x150 */ .short  0x70E3,  0x7083,  0x7023,  0x6FC2,  0x6F5F,  0x6EFB,  0x6E97,  0x6E31
    /* 0x158 */ .short  0x6DCA,  0x6D62,  0x6CF9,  0x6C8F,  0x6C24,  0x6BB8,  0x6B4B,  0x6ADD
    /* 0x160 */ .short  0x6A6E,  0x69FD,  0x698C,  0x691A,  0x68A7,  0x6832,  0x67BD,  0x6747
    /* 0x168 */ .short  0x66D0,  0x6657,  0x65DE,  0x6564,  0x64E9,  0x646C,  0x63EF,  0x6371
    /* 0x170 */ .short  0x62F2,  0x6272,  0x61F1,  0x616F,  0x60EC,  0x6068,  0x5FE4,  0x5F5E
    /* 0x178 */ .short  0x5ED7,  0x5E50,  0x5DC8,  0x5D3E,  0x5CB4,  0x5C29,  0x5B9D,  0x5B10
    /* 0x180 */ .short  0x5A82,  0x59F4,  0x5964,  0x58D4,  0x5843,  0x57B1,  0x571E,  0x568A
    /* 0x188 */ .short  0x55F6,  0x5560,  0x54CA,  0x5433,  0x539B,  0x5303,  0x5269,  0x51CF
    /* 0x190 */ .short  0x5134,  0x5098,  0x4FFB,  0x4F5E,  0x4EC0,  0x4E21,  0x4D81,  0x4CE1
    /* 0x198 */ .short  0x4C40,  0x4B9E,  0x4AFB,  0x4A58,  0x49B4,  0x490F,  0x486A,  0x47C4
    /* 0x1A0 */ .short  0x471D,  0x4675,  0x45CD,  0x4524,  0x447B,  0x43D1,  0x4326,  0x427A
    /* 0x1A8 */ .short  0x41CE,  0x4121,  0x4074,  0x3FC6,  0x3F17,  0x3E68,  0x3DB8,  0x3D08
    /* 0x1B0 */ .short  0x3C57,  0x3BA5,  0x3AF3,  0x3A40,  0x398D,  0x38D9,  0x3825,  0x3770
    /* 0x1B8 */ .short  0x36BA,  0x3604,  0x354E,  0x3497,  0x33DF,  0x3327,  0x326E,  0x31B5
    /* 0x1C0 */ .short  0x30FC,  0x3042,  0x2F87,  0x2ECC,  0x2E11,  0x2D55,  0x2C99,  0x2BDC
    /* 0x1C8 */ .short  0x2B1F,  0x2A62,  0x29A4,  0x28E5,  0x2827,  0x2768,  0x26A8,  0x25E8
    /* 0x1D0 */ .short  0x2528,  0x2467,  0x23A7,  0x22E5,  0x2224,  0x2162,  0x209F,  0x1FDD
    /* 0x1D8 */ .short  0x1F1A,  0x1E57,  0x1D93,  0x1CD0,  0x1C0C,  0x1B47,  0x1A83,  0x19BE
    /* 0x1E0 */ .short  0x18F9,  0x1833,  0x176E,  0x16A8,  0x15E2,  0x151C,  0x1455,  0x138F
    /* 0x1E8 */ .short  0x12C8,  0x1201,  0x113A,  0x1073,  0x0FAB,  0x0EE4,  0x0E1C,  0x0D54
    /* 0x1F0 */ .short  0x0C8C,  0x0BC4,  0x0AFB,  0x0A33,  0x096B,  0x08A2,  0x07D9,  0x0711
    /* 0x1F8 */ .short  0x0648,  0x057F,  0x04B6,  0x03ED,  0x0324,  0x025B,  0x0192,  0x00C9
    /* 0x200 */ .short  0x0000, -0x00C9, -0x0192, -0x025B, -0x0324, -0x03ED, -0x04B6, -0x057F
    /* 0x208 */ .short -0x0648, -0x0711, -0x07D9, -0x08A2, -0x096B, -0x0A33, -0x0AFB, -0x0BC4
    /* 0x210 */ .short -0x0C8C, -0x0D54, -0x0E1C, -0x0EE4, -0x0FAB, -0x1073, -0x113A, -0x1201
    /* 0x218 */ .short -0x12C8, -0x138F, -0x1455, -0x151C, -0x15E2, -0x16A8, -0x176E, -0x1833
    /* 0x220 */ .short -0x18F9, -0x19BE, -0x1A83, -0x1B47, -0x1C0C, -0x1CD0, -0x1D93, -0x1E57
    /* 0x228 */ .short -0x1F1A, -0x1FDD, -0x209F, -0x2162, -0x2224, -0x22E5, -0x23A7, -0x2467
    /* 0x230 */ .short -0x2528, -0x25E8, -0x26A8, -0x2768, -0x2827, -0x28E5, -0x29A4, -0x2A62
    /* 0x238 */ .short -0x2B1F, -0x2BDC, -0x2C99, -0x2D55, -0x2E11, -0x2ECC, -0x2F87, -0x3042
    /* 0x240 */ .short -0x30FC, -0x31B5, -0x326E, -0x3327, -0x33DF, -0x3497, -0x354E, -0x3604
    /* 0x248 */ .short -0x36BA, -0x3770, -0x3825, -0x38D9, -0x398D, -0x3A40, -0x3AF3, -0x3BA5
    /* 0x250 */ .short -0x3C57, -0x3D08, -0x3DB8, -0x3E68, -0x3F17, -0x3FC6, -0x4074, -0x4121
    /* 0x258 */ .short -0x41CE, -0x427A, -0x4326, -0x43D1, -0x447B, -0x4524, -0x45CD, -0x4675
    /* 0x260 */ .short -0x471D, -0x47C4, -0x486A, -0x490F, -0x49B4, -0x4A58, -0x4AFB, -0x4B9E
    /* 0x268 */ .short -0x4C40, -0x4CE1, -0x4D81, -0x4E21, -0x4EC0, -0x4F5E, -0x4FFB, -0x5098
    /* 0x270 */ .short -0x5134, -0x51CF, -0x5269, -0x5303, -0x539B, -0x5433, -0x54CA, -0x5560
    /* 0x278 */ .short -0x55F6, -0x568A, -0x571E, -0x57B1, -0x5843, -0x58D4, -0x5964, -0x59F4
    /* 0x280 */ .short -0x5A82, -0x5B10, -0x5B9D, -0x5C29, -0x5CB4, -0x5D3E, -0x5DC8, -0x5E50
    /* 0x288 */ .short -0x5ED7, -0x5F5E, -0x5FE4, -0x6068, -0x60EC, -0x616F, -0x61F1, -0x6272
    /* 0x290 */ .short -0x62F2, -0x6371, -0x63EF, -0x646C, -0x64E9, -0x6564, -0x65DE, -0x6657
    /* 0x298 */ .short -0x66D0, -0x6747, -0x67BD, -0x6832, -0x68A7, -0x691A, -0x698C, -0x69FD
    /* 0x2A0 */ .short -0x6A6E, -0x6ADD, -0x6B4B, -0x6BB8, -0x6C24, -0x6C8F, -0x6CF9, -0x6D62
    /* 0x2A8 */ .short -0x6DCA, -0x6E31, -0x6E97, -0x6EFB, -0x6F5F, -0x6FC2, -0x7023, -0x7083
    /* 0x2B0 */ .short -0x70E3, -0x7141, -0x719E, -0x71FA, -0x7255, -0x72AF, -0x7308, -0x735F
    /* 0x2B8 */ .short -0x73B6, -0x740B, -0x7460, -0x74B3, -0x7505, -0x7556, -0x75A6, -0x75F4
    /* 0x2C0 */ .short -0x7642, -0x768E, -0x76D9, -0x7723, -0x776C, -0x77B4, -0x77FB, -0x7840
    /* 0x2C8 */ .short -0x7885, -0x78C8, -0x790A, -0x794A, -0x798A, -0x79C9, -0x7A06, -0x7A42
    /* 0x2D0 */ .short -0x7A7D, -0x7AB7, -0x7AEF, -0x7B27, -0x7B5D, -0x7B92, -0x7BC6, -0x7BF9
    /* 0x2D8 */ .short -0x7C2A, -0x7C5A, -0x7C89, -0x7CB7, -0x7CE4, -0x7D0F, -0x7D3A, -0x7D63
    /* 0x2E0 */ .short -0x7D8A, -0x7DB1, -0x7DD6, -0x7DFB, -0x7E1E, -0x7E3F, -0x7E60, -0x7E7F
    /* 0x2E8 */ .short -0x7E9D, -0x7EBA, -0x7ED6, -0x7EF0, -0x7F0A, -0x7F22, -0x7F38, -0x7F4E
    /* 0x2F0 */ .short -0x7F62, -0x7F75, -0x7F87, -0x7F98, -0x7FA7, -0x7FB5, -0x7FC2, -0x7FCE
    /* 0x2F8 */ .short -0x7FD9, -0x7FE2, -0x7FEA, -0x7FF1, -0x7FF6, -0x7FFA, -0x7FFE, -0x7FFF
    /* 0x300 */ .short -0x8000, -0x7FFF, -0x7FFE, -0x7FFA, -0x7FF6, -0x7FF1, -0x7FEA, -0x7FE2
    /* 0x308 */ .short -0x7FD9, -0x7FCE, -0x7FC2, -0x7FB5, -0x7FA7, -0x7F98, -0x7F87, -0x7F75
    /* 0x310 */ .short -0x7F62, -0x7F4E, -0x7F38, -0x7F22, -0x7F0A, -0x7EF0, -0x7ED6, -0x7EBA
    /* 0x318 */ .short -0x7E9D, -0x7E7F, -0x7E60, -0x7E3F, -0x7E1E, -0x7DFB, -0x7DD6, -0x7DB1
    /* 0x320 */ .short -0x7D8A, -0x7D63, -0x7D3A, -0x7D0F, -0x7CE4, -0x7CB7, -0x7C89, -0x7C5A
    /* 0x328 */ .short -0x7C2A, -0x7BF9, -0x7BC6, -0x7B92, -0x7B5D, -0x7B27, -0x7AEF, -0x7AB7
    /* 0x330 */ .short -0x7A7D, -0x7A42, -0x7A06, -0x79C9, -0x798A, -0x794A, -0x790A, -0x78C8
    /* 0x338 */ .short -0x7885, -0x7840, -0x77FB, -0x77B4, -0x776C, -0x7723, -0x76D9, -0x768E
    /* 0x340 */ .short -0x7642, -0x75F4, -0x75A6, -0x7556, -0x7505, -0x74B3, -0x7460, -0x740B
    /* 0x348 */ .short -0x73B6, -0x735F, -0x7308, -0x72AF, -0x7255, -0x71FA, -0x719E, -0x7141
    /* 0x350 */ .short -0x70E3, -0x7083, -0x7023, -0x6FC2, -0x6F5F, -0x6EFB, -0x6E97, -0x6E31
    /* 0x358 */ .short -0x6DCA, -0x6D62, -0x6CF9, -0x6C8F, -0x6C24, -0x6BB8, -0x6B4B, -0x6ADD
    /* 0x360 */ .short -0x6A6E, -0x69FD, -0x698C, -0x691A, -0x68A7, -0x6832, -0x67BD, -0x6747
    /* 0x368 */ .short -0x66D0, -0x6657, -0x65DE, -0x6564, -0x64E9, -0x646C, -0x63EF, -0x6371
    /* 0x370 */ .short -0x62F2, -0x6272, -0x61F1, -0x616F, -0x60EC, -0x6068, -0x5FE4, -0x5F5E
    /* 0x378 */ .short -0x5ED7, -0x5E50, -0x5DC8, -0x5D3E, -0x5CB4, -0x5C29, -0x5B9D, -0x5B10
    /* 0x380 */ .short -0x5A82, -0x59F4, -0x5964, -0x58D4, -0x5843, -0x57B1, -0x571E, -0x568A
    /* 0x388 */ .short -0x55F6, -0x5560, -0x54CA, -0x5433, -0x539B, -0x5303, -0x5269, -0x51CF
    /* 0x390 */ .short -0x5134, -0x5098, -0x4FFB, -0x4F5E, -0x4EC0, -0x4E21, -0x4D81, -0x4CE1
    /* 0x398 */ .short -0x4C40, -0x4B9E, -0x4AFB, -0x4A58, -0x49B4, -0x490F, -0x486A, -0x47C4
    /* 0x3A0 */ .short -0x471D, -0x4675, -0x45CD, -0x4524, -0x447B, -0x43D1, -0x4326, -0x427A
    /* 0x3A8 */ .short -0x41CE, -0x4121, -0x4074, -0x3FC6, -0x3F17, -0x3E68, -0x3DB8, -0x3D08
    /* 0x3B0 */ .short -0x3C57, -0x3BA5, -0x3AF3, -0x3A40, -0x398D, -0x38D9, -0x3825, -0x3770
    /* 0x3B8 */ .short -0x36BA, -0x3604, -0x354E, -0x3497, -0x33DF, -0x3327, -0x326E, -0x31B5
    /* 0x3C0 */ .short -0x30FC, -0x3042, -0x2F87, -0x2ECC, -0x2E11, -0x2D55, -0x2C99, -0x2BDC
    /* 0x3C8 */ .short -0x2B1F, -0x2A62, -0x29A4, -0x28E5, -0x2827, -0x2768, -0x26A8, -0x25E8
    /* 0x3D0 */ .short -0x2528, -0x2467, -0x23A7, -0x22E5, -0x2224, -0x2162, -0x209F, -0x1FDD
    /* 0x3D8 */ .short -0x1F1A, -0x1E57, -0x1D93, -0x1CD0, -0x1C0C, -0x1B47, -0x1A83, -0x19BE
    /* 0x3E0 */ .short -0x18F9, -0x1833, -0x176E, -0x16A8, -0x15E2, -0x151C, -0x1455, -0x138F
    /* 0x3E8 */ .short -0x12C8, -0x1201, -0x113A, -0x1073, -0x0FAB, -0x0EE4, -0x0E1C, -0x0D54
    /* 0x3F0 */ .short -0x0C8C, -0x0BC4, -0x0AFB, -0x0A33, -0x096B, -0x08A2, -0x07D9, -0x0711
    /* 0x3F8 */ .short -0x0648, -0x057F, -0x04B6, -0x03ED, -0x0324, -0x025B, -0x0192, -0x00C9
                /* Extra entries to avoid OoB accesses */
    /* 0x400 */ .short  0x0000,  0x0000
SYM_END(calc_sintable)

.section .text, "ax"

/**
 * s16 sinL(s16 angle);
 *
 * Calculate sin of a binary angle.
 *
 * Roughly equivalent to:
 * ```
s16 sinL(s16 angle) {
    s32 low_bits = (u32)angle & 0x3F;
    s32 upper_bits = ((u32)angle >> 5) & 0x7FE;
    s32 ret;

    ret = calc_sintable[upper_bits/2];
    if (low_bits != 0) {
        // If low_bits are not zero, then do a linear interpolation between
        // this point and the next one.
        // Divide by 0x40 since that's the max amount for low_bits because of
        // the 0x3F mask.
        ret += ((calc_sintable[upper_bits/2 + 1] - ret) * low_bits) / 0x40;
    }
    return ret;
}
 * ```
 */
LEAF(sinL)
    /*
    Implementation detail:
    Functions down below call this function and they rely on this function not
    clobbering many most $tX registers nor $aX registers.
    */

    srl         $t8, $a0, 5
    andi        $t9, $a0, 0x3F
    andi        $t8, $t8, 0x7FE
    lh          $v0, (calc_sintable)($t8)
    beqz        $t9, 1f

    // Interpolate angle
    lh          $t8, (calc_sintable + 0x2)($t8)
    subu        $t8, $t8, $v0
    mul         $t8, $t8, $t9
    sra         $t9, $t8, 6
    addu        $v0, $v0, $t9

1:
    jr          $ra
END(sinL)

/**
 * s16 cosL(s16 angle);
 *
 * Calculate cos of a binary angle.
 *
 * Roughly equivalent to:
 * ```
```
s16 cosL(s16 angle) {
    s32 low_bits = (u32)(angle + 0x4000) & 0x3F;
    s32 upper_bits = ((u32)(angle + 0x4000) >> 5) & 0x7FE;
    s32 ret;

    ret = calc_sintable[upper_bits/2];
    if (low_bits != 0) {
        // If low_bits are not zero, then do a linear interpolation between
        // this point and the next one.
        // Divide by 0x40 since that's the max amount for low_bits because of
        // the 0x3F mask.
        ret += ((calc_sintable[upper_bits/2 + 1] - ret) * low_bits) / 0x40;
    }
    return ret;
}
```
 */
LEAF(cosL)
    /*
    Implementation detail:
    Functions down below call this function and they rely on this function not
    clobbering many most $tX registers nor $aX registers.
    */

    addiu       $v0, $a0, 0x4000
    srl         $t8, $v0, 5
    andi        $t9, $v0, 0x3F
    andi        $t8, $t8, 0x7FE
    lh          $v0, (calc_sintable)($t8)
    beqz        $t9, 1f

    // Interpolate angle
    lh          $t8, (calc_sintable + 0x2)($t8)
    subu        $t8, $t8, $v0
    mul         $t8, $t8, $t9
    sra         $t9, $t8, 6
    addu        $v0, $v0, $t9

1:
    jr          $ra
END(cosL)

/**
 * void lc2wc(Mtx *arg0, s32 arg1, s32 arg2, s32 arg3, s32 *arg4, s32 *arg5, s32 *arg6);
 *
 * Roughly equivalent to:
 * ```
```
void lc2wc(Mtx *arg0, s32 arg1, s32 arg2, s32 arg3, s32 *arg4, s32 *arg5, s32 *arg6) {
    s32 *arr[] = {arg4, arg5, arg6};
    s32 i;
    s64 value;
    s32 hi;
    s32 lo;
    s32 shifted;

    for (i = 0; i < 3; i++) {
        value  = (s64)arg0->m[0][i] * (s64)arg1;
        value += (s64)arg0->m[1][i] * (s64)arg2;
        value += (s64)arg0->m[2][i] * (s64)arg3;

        hi = ((u64)value) >> 32;
        lo = ((u64)value) & 0xFFFFFFFF;
        shifted = (lo >> 15) | (hi << 17);

        *(arr[i]) = arg0->m[3][i] + shifted;
    }
}
```
 */
LEAF(lc2wc)
    li          $v0, 0x3
    addiu       $t1, $sp, 0x10

.L8007ECE8:
        lw          $t0, 0x0($a0)
        lw          $t7, 0x10($a0)
        lw          $t6, 0x20($a0)
        /* (s64)arg0->m[0][i] * (s64)arg1 */
        mult        $t0, $a1
        mfhi        $t8
        mflo        $t9

        lw          $t0, 0x0($t1)
        addiu       $t1, $t1, 0x4
        /* (s64)arg0->m[1][i] * (s64)arg2 */
        mult        $t7, $a2
        mfhi        $t2
        mflo        $t3

        addu        $t5, $t3, $t9
        sltu        $t3, $t5, $t9
        addu        $t3, $t3, $t2
        addu        $t4, $t3, $t8

        /* (s64)arg0->m[2][i] * (s64)arg3 */
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
END(lc2wc)

/**
 * void wc2lc(Mtx *arg0, s32 arg1, s32 arg2, s32 arg3, s32 *arg4, s32 *arg5, s32 *arg6);
 *
 * Roughly equivalent to:
 * ```
```
void wc2lc(Mtx *arg0, s32 arg1, s32 arg2, s32 arg3, s32 *arg4, s32 *arg5, s32 *arg6) {
    s32 *arr[] = {arg4, arg5, arg6};
    s32 i;
    s64 value;
    s32 hi;
    s32 lo;
    s32 shifted;

    arg1 -= arg0->m[3][0];
    arg2 -= arg0->m[3][1];
    arg3 -= arg0->m[3][2];

    for (i = 0; i < 3; i++) {
        value  = (s64)arg0->m[i][0] * (s64)arg1;
        value += (s64)arg0->m[i][1] * (s64)arg2;
        value += (s64)arg0->m[i][2] * (s64)arg3;

        hi = ((u64)value) >> 32;
        lo = ((u64)value) & 0xFFFFFFFF;
        shifted = (lo >> 15) | (hi << 17);

        *(arr[i]) = shifted;
    }
}
```
 */
LEAF(wc2lc)
    li          $v0, 0x3
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
        /* (s64)arg0->m[i][0] * (s64)arg1 */
        mult        $t0, $a1
        mfhi        $t8
        mflo        $t9
        /* (s64)arg0->m[i][1] * (s64)arg2 */
        lw          $t0, 0x0($t1)
        addiu       $t1, $t1, 0x4
        mult        $t7, $a2
        mfhi        $t2
        mflo        $t3

        addu        $t5, $t3, $t9
        sltu        $t3, $t5, $t9
        addu        $t3, $t3, $t2
        addu        $t4, $t3, $t8

        /* (s64)arg0->m[i][2] * (s64)arg3 */
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
END(wc2lc)

/**
 * void matrixMulL(const Mtx *m, const Mtx *n, Mtx *r);
 *
 * r = m * n;
 *
 * Roughly equivalent to:
 * ```
void matrixMulL(const Mtx *m, const Mtx *n, Mtx *r) {
    s32 i;

    r->m[2][3] = 0;
    r->m[1][3] = 0;
    r->m[0][3] = 0;

    r->m[3][3] = 0x8000;

    for (i = 0; i < 3; i++) {
        s64 value;
        s32 j;
        s32 k;
        s32 hi;
        s32 lo;
        s32 shifted;

        for (j = 0; j < 3; j++) {
            value = 0;
            for (k = 0; k < 3; k++) {
                value += (s64)m->m[i][k] * (s64)n->m[k][j];
            }

            hi = ((u64)value) >> 32;
            lo = ((u64)value) & 0xFFFFFFFF;
            shifted = (lo >> 15) | (hi << 17);
            r->m[i][j] = shifted;
        }

        value = 0;
        for (k = 0; k < 3; k++) {
            value += (s64)m->m[3][k] * (s64)n->m[k][i];
        }

        hi = ((u64)value) >> 32;
        lo = ((u64)value) & 0xFFFFFFFF;
        shifted = (lo >> 15) | (hi << 17);

        r->m[3][i] = n->m[3][i] + shifted;
    }
}
 * ```
 */
LEAF(matrixMulL)
    /* Set last column to [0, 0, 0, 0x8000] */
    li          $t8, 0x8000
    sw          $zero, 0x2C($a2)
    sw          $zero, 0x1C($a2)
    sw          $zero, 0xC($a2)
    sw          $t8, 0x3C($a2)
    li          $v0, 0x3
    move        $v1, $a2
    move        $t0, $a1
    move        $t1, $a0

    .Lmul_loop:
        /*
            j = 0;
            value = 0;
            for (k = 0; k < 3; k++) {
                value += (s64)m->m[i][k] * (s64)n->m[k][j];
            }

            hi = ((u64)value) >> 32;
            lo = ((u64)value) & 0xFFFFFFFF;
            shifted = (lo >> 15) | (hi << 17);
            r->m[i][j] = shifted;
        */
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

        /* Same as previous block, but j = 1; */
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

        /* Same as previous block, but j = 2; */
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

        /*
        value = 0;
        for (k = 0; k < 3; k++) {
            value += (s64)m->m[3][k] * (s64)n->m[k][i];
        }

        hi = ((u64)value) >> 32;
        lo = ((u64)value) & 0xFFFFFFFF;
        shifted = (lo >> 15) | (hi << 17);

        r->m[3][i] = n->m[3][i] + shifted;
        */
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

        /* loop stuff */
        addiu       $v0, $v0, -0x1
        addiu       $v1, $v1, 0x10
        addiu       $t1, $t1, 0x10
        addiu       $a2, $a2, 0x4
        addiu       $t0, $t0, 0x4
    bgtz        $v0, .Lmul_loop

    jr          $ra
END(matrixMulL)

/**
 * void makeTransrateMatrix(Mtx *m, s32 xofs, s32 yofs, s32 zofs);
 *
 * Initializes `m` to:
 *
 * | 0x8000      0      0      0 |
 * |      0 0x8000      0      0 |
 * |      0      0 0x8000      0 |
 * |      x      y      z 0x8000 |
 *
 * Roughly equivalent to:
 * ```
void makeTransrateMatrix(Mtx *m, s32 xofs, s32 yofs, s32 zofs) {
    m->m[0][0] = 0x8000;
    m->m[0][1] = 0;
    m->m[0][2] = 0;
    m->m[0][3] = 0;
    m->m[1][0] = 0;
    m->m[1][1] = 0x8000;
    m->m[1][2] = 0;
    m->m[1][3] = 0;
    m->m[2][0] = 0;
    m->m[2][1] = 0;
    m->m[2][2] = 0x8000;
    m->m[2][3] = 0;
    m->m[3][0] = xofs;
    m->m[3][1] = yofs;
    m->m[3][2] = zofs;
    m->m[3][3] = 0x8000;
}
 * ```
 */
LEAF(makeTransrateMatrix)
    li          $v0, 0x8000
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
    jr          $ra
END(makeTransrateMatrix)

/**
 * void makeScaleMatrix(Mtx *m, s32 scale);
 *
 * Initializes `m` to :
 *
 * |  scale      0      0      0 |
 * |      0  scale      0      0 |
 * |      0      0  scale      0 |
 * |      0      0      0 0x8000 |
 *
 * Roughly equivalent to:
 * ```
void makeScaleMatrix(Mtx *m, s32 scale) {
    m->m[0][0] = scale;
    m->m[0][1] = 0;
    m->m[0][2] = 0;
    m->m[0][3] = 0;
    m->m[1][0] = 0;
    m->m[1][1] = scale;
    m->m[1][2] = 0;
    m->m[1][3] = 0;
    m->m[2][0] = 0;
    m->m[2][1] = 0;
    m->m[2][2] = scale;
    m->m[2][3] = 0;
    m->m[3][0] = 0;
    m->m[3][1] = 0;
    m->m[3][2] = 0;
    m->m[3][3] = 0x8000;
}
 * ```
 */
LEAF(makeScaleMatrix)
    li          $v0, 0x8000
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

    jr          $ra
END(makeScaleMatrix)

/**
 * void makeMatrix(Mtx *m, s16 xrot, s16 yrot, s16 zrot, s32 xofs, s32 yofs, s32 zofs);
 *
 * Initializes `m` to (kinda):
 *
 * |    sin(z) * sin(y) * sin(x) + cos(z) * cos(y)                               sin(z) * cos(x)    sin(z) * cos(y) * sin(x) - cos(z) * sin(y)                                             0 |
 * |    cos(z) * sin(y) * sin(x) - sin(z) * cos(y)                               cos(z) * cos(x)    cos(z) * cos(y) * sin(x) + sin(z) * sin(y)                                             0 |
 * |                               sin(y) * cos(x)                                       -sin(x)                               cos(y) * cos(x)                                             0 |
 * |                                          xofs                                          yofs                                          zofs                                        0x8000 |
 *
 * Roughly equivalent to:
 * ```
void makeMatrix(Mtx *m, s16 xrot, s16 yrot, s16 zrot, s32 xofs, s32 yofs, s32 zofs) {
    s32 sin_y;
    s32 cos_y;
    s32 sin_z;
    s32 cos_z;
    s32 sin_x;
    s32 cos_x;

    m->m[2][3] = 0;
    m->m[1][3] = 0;
    m->m[0][3] = 0;
    m->m[3][3] = 0x8000;
    m->m[3][0] = xofs;
    m->m[3][1] = yofs;
    m->m[3][2] = zofs;

    sin_x = sinL(xrot);
    cos_x = cosL(xrot);
    sin_y = sinL(yrot);
    cos_y = cosL(yrot);
    sin_z = sinL(zrot);
    cos_z = cosL(zrot);

    m->m[0][0] = ((sin_z * ((sin_y * sin_x) >> 15)) + (cos_z * cos_y)) >> 15;
    m->m[0][1] = (sin_z * cos_x) >> 15;
    m->m[0][2] = ((sin_z * ((cos_y * sin_x) >> 15)) - (cos_z * sin_y)) >> 15;

    m->m[1][0] = ((cos_z * ((sin_y * sin_x) >> 15)) - (sin_z * cos_y)) >> 15;
    m->m[1][1] = (cos_z * cos_x) >> 15;
    m->m[1][2] = ((cos_z * ((cos_y * sin_x) >> 15)) + (sin_z * sin_y)) >> 15;

    m->m[2][0] = (sin_y * cos_x) >> 15;
    m->m[2][1] = -sin_x;
    m->m[2][2] = (cos_y * cos_x) >> 15;
}
 * ```
 */
LEAF(makeMatrix)
    /*
    The following code abuses the fact that we know what registers by sinL
    and cosL functions, so it doesn't bother with avoiding registers from being
    clobbered, i.e. it just uses $tX registers instead of $sX before the `bal`s
    or not setting $a0 again after a call because it knows the function doesn't
    modify it.
    */

    move        $t1, $ra
    move        $t0, $a0
    lw          $t2, 0x10($sp)
    lw          $t3, 0x14($sp)
    lw          $t4, 0x18($sp)
    sw          $zero, 0x2C($t0)
    sw          $zero, 0x1C($t0)
    sw          $zero, 0xC($t0)
    li          $t8, 0x8000
    sw          $t8, 0x3C($t0)
    sw          $t2, 0x30($t0)
    sw          $t3, 0x34($t0)
    sw          $t4, 0x38($t0)

    move        $a0, $a2
    bal         sinL
    move        $t2, $v0

    bal         cosL
    move        $t3, $v0

    move        $a0, $a3
    bal         sinL
    move        $t4, $v0

    bal         cosL
    move        $t5, $v0

    move        $a0, $a1
    bal         sinL
    move        $t6, $v0

    bal         cosL

    negu        $t8, $t6
    sw          $t8, 0x24($t0)

    mul         $t8, $t4, $v0
    sra         $t9, $t8, 15
    sw          $t9, 0x4($t0)
    mul         $t8, $t5, $v0
    sra         $t9, $t8, 15
    sw          $t9, 0x14($t0)
    mul         $t8, $t2, $v0
    sra         $t9, $t8, 15
    sw          $t9, 0x20($t0)

    mul         $t8, $t3, $v0
    sra         $t9, $t8, 15
    sw          $t9, 0x28($t0)

    mul         $t8, $t2, $t6
    sra         $v0, $t8, 15

    mul         $t9, $t5, $t3
    mul         $t8, $t4, $v0
    addu        $t7, $t8, $t9
    sra         $t8, $t7, 15
    sw          $t8, 0x0($t0)
    mul         $t9, $t4, $t3

    mul         $t8, $t5, $v0
    subu        $t7, $t8, $t9
    sra         $t8, $t7, 15
    sw          $t8, 0x10($t0)

    mul         $t8, $t3, $t6
    sra         $v0, $t8, 15

    mul         $t9, $t5, $t2

    mul         $t8, $t4, $v0
    subu        $t7, $t8, $t9
    sra         $t8, $t7, 15
    sw          $t8, 0x8($t0)
    mul         $t9, $t4, $t2

    mul         $t8, $t5, $v0
    addu        $t7, $t8, $t9
    sra         $t8, $t7, 15
    sw          $t8, 0x18($t0)

    move        $ra, $t1
    jr          $ra
END(makeMatrix)

/**
 * void makeXrotMatrix(Mtx *m, s16 xrot, s32 xofs, s32 yofs, s32 zofs);
 *
 * Initializes `m` to:
 *
 * |  0x8000       0       0       0 |
 * |       0  cos(x)  sin(x)       0 |
 * |       0 -sin(x)  cos(x)       0 |
 * |    xofs    yofs    zofs  0x8000 |
 *
 * Roughly equivalent to:
 * ```
void makeXrotMatrix(Mtx *m, s16 xrot, s32 xofs, s32 yofs, s32 zofs) {
    s32 sin_x;
    s32 cos_x;

    m->m[2][3] = 0;
    m->m[1][3] = 0;
    m->m[0][3] = 0;
    m->m[3][0] = xofs;
    m->m[3][1] = yofs;
    m->m[3][2] = zofs;
    m->m[3][3] = 0x8000;

    sin_x = sinL(xrot);
    cos_x = cosL(xrot);

    m->m[0][0] = 0x8000;
    m->m[0][1] = 0;
    m->m[0][2] = 0;

    m->m[1][0] = 0;
    m->m[1][1] = cos_x;
    m->m[1][2] = sin_x;

    m->m[2][0] = 0;
    m->m[2][1] = -sin_x;
    m->m[2][2] = cos_x;
}
 * ```
 */
LEAF(makeXrotMatrix)
    move        $t1, $ra

    move        $t0, $a0
    lw          $t2, 0x10($sp)
    sw          $zero, 0x2C($t0)
    sw          $zero, 0x1C($t0)
    sw          $zero, 0xC($t0)
    sw          $a2, 0x30($t0)
    sw          $a3, 0x34($t0)
    sw          $t2, 0x38($t0)
    li          $t2, 0x8000
    sw          $t2, 0x3C($t0)

    move        $a0, $a1
    bal         sinL
    move        $t3, $v0

    bal         cosL

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

    move        $ra, $t1
    jr          $ra
END(makeXrotMatrix)

/**
 * void makeYrotMatrix(Mtx *m, s16 yrot, s32 xofs, s32 yofs, s32 zofs);
 *
 * Initializes `m` to:
 *
 * |  cos(y)       0 -sin(y)       0 |
 * |       0  0x8000       0       0 |
 * |  sin(y)       0  cos(y)       0 |
 * |    xofs    yofs    zofs  0x8000 |
 *
 * Roughly equivalent to:
 * ```
void makeYrotMatrix(Mtx *m, s16 yrot, s32 xofs, s32 yofs, s32 zofs) {
    s32 sin_y;
    s32 cos_y;

    m->m[2][3] = 0;
    m->m[1][3] = 0;
    m->m[0][3] = 0;
    m->m[3][0] = xofs;
    m->m[3][1] = yofs;
    m->m[3][2] = zofs;
    m->m[3][3] = 0x8000;

    sin_y = sinL(yrot);
    cos_y = cosL(yrot);

    m->m[0][0] = cos_y;
    m->m[0][1] = 0;
    m->m[0][2] = -sin_y;

    m->m[1][0] = 0;
    m->m[1][1] = 0x8000;
    m->m[1][2] = 0;

    m->m[2][0] = sin_y;
    m->m[2][1] = 0;
    m->m[2][2] = cos_y;
}
 * ```
 */
LEAF(makeYrotMatrix)
    move        $t1, $ra

    move        $t0, $a0
    lw          $t2, 0x10($sp)
    sw          $zero, 0x2C($t0)
    sw          $zero, 0x1C($t0)
    sw          $zero, 0xC($t0)
    sw          $a2, 0x30($t0)
    sw          $a3, 0x34($t0)
    sw          $t2, 0x38($t0)
    li          $t2, 0x8000
    sw          $t2, 0x3C($t0)

    move        $a0, $a1
    bal         sinL
    move        $t3, $v0

    bal         cosL

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

    move        $ra, $t1
    jr          $ra
END(makeYrotMatrix)

/**
 * void makeZrotMatrix(Mtx *m, s16 zrot, s32 xofs, s32 yofs, s32 zofs);
 *
 * Initializes `m` to:
 *
 * |  cos(z)  sin(z)       0       0 |
 * | -sin(z)  cos(z)       0       0 |
 * |       0       0       0       0 |
 * |    xofs    yofs    zofs  0x8000 |
 *
 * Roughly equivalent to:
 * ```
void makeZrotMatrix(Mtx *m, s16 zrot, s32 xofs, s32 yofs, s32 zofs) {
    s32 sin_z;
    s32 cos_z;

    m->m[2][3] = 0;
    m->m[1][3] = 0;
    m->m[0][3] = 0;
    m->m[3][0] = xofs;
    m->m[3][1] = yofs;
    m->m[3][2] = zofs;
    m->m[3][3] = 0x8000;

    sin_z = sinL(zrot);
    cos_z = cosL(zrot);

    m->m[0][0] = cos_z;
    m->m[0][1] = sin_z;
    m->m[0][2] = 0;

    m->m[1][0] = -sin_z;
    m->m[1][1] = cos_z;
    m->m[1][2] = 0;

    m->m[2][0] = 0;
    m->m[2][1] = 0;
    m->m[2][2] = 0x8000;
}
 * ```
 */
LEAF(makeZrotMatrix)
    move        $t1, $ra

    move        $t0, $a0
    lw          $t2, 0x10($sp)
    sw          $zero, 0x2C($t0)
    sw          $zero, 0x1C($t0)
    sw          $zero, 0xC($t0)
    sw          $a2, 0x30($t0)
    sw          $a3, 0x34($t0)
    sw          $t2, 0x38($t0)
    li          $t2, 0x8000
    sw          $t2, 0x3C($t0)

    move        $a0, $a1
    bal         sinL
    move        $t3, $v0

    bal         cosL

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

    move        $ra, $t1
    jr          $ra
END(makeZrotMatrix)

/**
 * void makeXZMatrix(Mtx *m, s16 xrot, s16 zrot);
 *
 * Initializes `m` to:
 *
 * |           cos(z)           sin(z)                0                0 |
 * | -sin(z) * cos(x)  cos(z) * cos(x)           sin(x)                0 |
 * |  sin(z) * sin(x) -cos(z) * sin(x)           cos(x)                0 |
 * |                0                0                0                0 |
 * |                0                0                0           0x8000 |
 *
 * Roughly equivalent to:
 * ```
void makeXZMatrix(Mtx *m, s32 xrot, s32 zrot) {
    s32 sin_z;
    s32 cos_z;
    s32 sin_x;
    s32 cos_x;

    m->m[2][3] = 0;
    m->m[1][3] = 0;
    m->m[0][3] = 0;
    m->m[3][0] = 0;
    m->m[3][1] = 0;
    m->m[3][2] = 0;
    m->m[3][3] = 0x8000;

    sin_z = sinL(zrot);
    cos_z = cosL(zrot);
    sin_x = sinL(xrot);
    cos_x = cosL(xrot);

    m->m[0][0] = cos_z;
    m->m[0][1] = sin_z;
    m->m[0][2] = 0;

    m->m[1][0] = (-sin_z * cos_x) >> 0xF;
    m->m[1][1] = (cos_z * cos_x) >> 0xF;
    m->m[1][2] = sin_x;

    m->m[2][0] = (sin_z * sin_x) >> 0xF;
    m->m[2][1] = (-sin_x * cos_z) >> 0xF;
    m->m[2][2] = cos_x;
}
 * ```
 */
LEAF(makeXZMatrix)
    move        $t1, $ra

    move        $t0, $a0
    sw          $zero, 0x2C($t0)
    sw          $zero, 0x1C($t0)
    sw          $zero, 0xC($t0)
    sw          $zero, 0x30($t0)
    sw          $zero, 0x34($t0)
    sw          $zero, 0x38($t0)
    li          $t2, 0x8000
    sw          $t2, 0x3C($t0)

    move        $a0, $a2
    bal         sinL
    move        $t2, $v0

    bal         cosL
    move        $t3, $v0

    move        $a0, $a1
    bal         sinL
    move        $t4, $v0

    bal         cosL

    sw          $t3, 0x0($t0)
    sw          $t2, 0x4($t0)
    sw          $zero, 0x8($t0)

    negu        $t8, $t2
    mul         $t9, $t8, $v0
    sra         $t8, $t9, 15
    sw          $t8, 0x10($t0)

    mul         $t9, $t3, $v0
    sra         $t8, $t9, 15
    sw          $t8, 0x14($t0)
    sw          $t4, 0x18($t0)

    mul         $t9, $t2, $t4
    sra         $t8, $t9, 15
    sw          $t8, 0x20($t0)
    negu        $t8, $t4
    mul         $t9, $t8, $t3
    sra         $t8, $t9, 15
    sw          $t8, 0x24($t0)
    sw          $v0, 0x28($t0)

    move        $ra, $t1
    jr          $ra
END(makeXZMatrix)

/**
 * void matrixConv(const Mtx *m, Mtx *mtx, s32 shift);
 *
 * Roughly equivalent to:
 * ```
void matrixConv(const Mtx *m, Mtx *mtx, s32 shift) {
    const s32 *a0 = (const s32 *)m->m;
    s32 *a1 = (s32 *)mtx->m;
    s32 temp_a2;
    s32 temp_t2;
    s32 temp_t3;
    s32 var_v0;

    if (shift != 0) {
        var_v0 = 6;
        if (shift <= 0) {
            temp_a2 = -(shift + 1);
            for (; var_v0 > 0; var_v0--) {
                temp_t2 = (*a0++) >> temp_a2;
                temp_t3 = (*a0++) >> temp_a2;
                a1[0] = (temp_t2 & 0xFFFF0000) | (temp_t3 >> 0x10);
                a1[8] = (temp_t2 << 0x10) | (temp_t3 & 0xFFFF);
                a1++;
            }
        } else {
            temp_a2 = shift + 1;
            for (; var_v0 > 0; var_v0--) {
                temp_t2 = (*a0++) << temp_a2;
                temp_t3 = (*a0++) << temp_a2;
                a1[0] = (temp_t2 & 0xFFFF0000) | (temp_t3 >> 0x10);
                a1[8] = (temp_t2 << 0x10) | (temp_t3 & 0xFFFF);
                a1++;
            }
        }

        var_v0 = 2;
    } else {
        var_v0 = 8;
    }

    for (; var_v0 > 0; var_v0--) {
        temp_t2 = (*a0++) << 1;
        temp_t3 = (*a0++) << 1;
        a1[0] = (temp_t2 & 0xFFFF0000) | (temp_t3 >> 0x10);
        a1[8] = (temp_t2 << 0x10) | (temp_t3 & 0xFFFF);
        a1++;
    }
}
 * ```
 */
LEAF(matrixConv)
    li          $t0, 0xFFFF0000
    li          $v0, 0x8
    beqz        $a2, .L8007F4CC

    li          $v0, 0x6
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
    bgtz        $v0, .L8007F488

.L8007F4C8:
    li          $v0, 0x2

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
    bgtz        $v0, .L8007F4CC

    jr          $ra
END(matrixConv)

/**
 * void matrixCopyL(Mtx *dst, Mtx *src);
 *
 * Roughly equivalent to:
 * ```
void matrixCopyL(Mtx *dst, const Mtx *src) {
    s32 i;
    s32 j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            dst->m[i][j] = src->m[i][j];
        }
    }
}
 * ```
 */
LEAF(matrixCopyL)
    li          $t8, 0x4

    1:
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
    bgtz        $t8, 1b

    jr          $ra
END(matrixCopyL)

/**
 * void rotpointL(s16 angle, s32 center_x, s32 center_y, s32 *x, s32 *y);
 *
 * Rotate (`x`, `y`) relative to (`center_x`, `center_y`) by `angle` degrees.
 *
 * Roughly equivalent to:
 * ```
void rotpointL(s16 angle, s32 center_x, s32 center_y, s32 *x, s32 *y) {
    s64 cos = (s64)(s32)cosL(angle);
    s64 sin = (s64)(s32)sinL(angle);
    s64 delta_y = *y - center_y;
    s64 delta_x = *x - center_x;
    s64 value;
    s32 hi;
    s32 lo;
    s32 shifted;

    value = delta_x * sin + delta_y * cos;
    hi = ((u64)value) >> 32;
    lo = ((u64)value) & 0xFFFFFFFF;
    shifted = (lo >> 15) | (hi << 17);

    *y = center_y + shifted;

    value = delta_x * cos - delta_y * sin;
    hi = ((u64)value) >> 32;
    lo = ((u64)value) & 0xFFFFFFFF;
    shifted = (lo >> 15) | (hi << 17);

    *x = center_x + shifted;
}
 * ```
 */
LEAF(rotpointL)
    move        $t1, $ra
    lw          $t0, 0x10($sp)

    bal         cosL
    move        $v1, $v0

    bal         sinL

    lw          $t7, 0x0($t0)
    lw          $t6, 0x0($a3)
    subu        $t9, $t7, $a2

    mult        $t9, $v1
    mfhi        $t2
    mflo        $t3
    subu        $t8, $t6, $a1
    negu        $t9, $t9

    mult        $t8, $v0
    mfhi        $t4
    mflo        $t5
    addu        $a0, $t3, $t5
    sltu        $t6, $a0, $t5
    addu        $t7, $t6, $t2
    addu        $t6, $t7, $t4
    srl         $t5, $a0, 15
    sll         $t4, $t6, 17

    mult        $t8, $v1
    mfhi        $t2
    mflo        $t3
    or          $v1, $t4, $t5
    addu        $a2, $a2, $v1

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

    move        $ra, $t1
    jr          $ra
END(rotpointL)

/**
 * s32 defangleL(s32 a1, s32 a2);
 *
 * Roughly equivalent to:
 * ```
s32 defangleL(s32 a1, s32 a2) {
    s32 angle1 = a1 & 0xFFFF;
    s32 angle2 = a2 & 0xFFFF;
    s32 angle01;
    s32 angle02;
    s32 d;

    if (angle1 < angle2) {
        angle01 = angle1 + 0x10000;
        angle02 = angle2;
    } else {
        angle01 = angle1;
        angle02 = angle2 + 0x10000;
    }

    angle2 -= angle1;
    angle02 -= angle01;
    if (ABS(angle2) > ABS(angle02)) {
        d = angle02;
    } else {
        d = angle2;
    }
    return d;
}
 * ```
 */

#if VERSION_CN
.global defangleL.NON_MATCHING
.type defangleL.NON_MATCHING, @object
defangleL.NON_MATCHING:
#endif

LEAF(defangleL)
    andi        $t2, $a0, 0xFFFF
    andi        $t3, $a1, 0xFFFF
    li          $v0, 0x10000
    bge         $t2, $t3, .L8007F630

    addu        $t4, $t2, $v0
    move        $t5, $t3
    b           .L8007F638

.L8007F630:
    move        $t4, $t2
    addu        $t5, $t3, $v0

.L8007F638:
    subu        $v0, $t3, $t2
    subu        $v1, $t5, $t4

    // TODO: No clue how to fix this
#if VERSION_CN
.set noreorder
    bgez        $v0, .L8007F64C
     move        $t2, $v0
.set reorder
#else
    move        $t2, $v0
    bgez        $v0, .L8007F64C
#endif

    neg         $t2, $v0
.L8007F64C:

#if VERSION_CN
.set noreorder
    bgez        $v1, .L8007F658
     move        $t3, $v1
.set reorder
#else
    move        $t3, $v1
    bgez        $v1, .L8007F658
#endif

    neg         $t3, $v1
.L8007F658:

    bge         $t3, $t2, .L8007F668

    move        $v0, $v1
.L8007F668:
    jr          $ra
END(defangleL)

#if VERSION_CN
.size defangleL.NON_MATCHING, . - defangleL.NON_MATCHING
#endif


/**
 * s32 distanceS(s32 x0, s32 y0, s32 z0, s32 x1, s32 y1, s32 z1);
 *
 * Distance between 3D points.
 *
 * Uses integer operations internally, so there will be precision loss.
 *
 * Roughly equivalent to:
 * ```
s32 distanceS(s32 x0, s32 y0, s32 z0, s32 x1, s32 y1, s32 z1) {
    s32 x_diff = x1 - x0;
    s32 y_diff = y1 - y0;
    s32 z_diff = z1 - z0;
    f32 sq = SQ(x_diff) + SQ(y_diff) + SQ(z_diff);

    return sqrtf(sq);
}
 * ```
 */
LEAF(distanceS)
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
    cvt.s.w     $fv0, $ft0
    sqrt.s      $ft1, $fv0
    trunc.w.s   $ft2, $ft1
    mfc1        $v0, $ft2

    jr          $ra
END(distanceS)

/**
 * s32 distanceL(s32 x0, s32 y0, s32 z0, s32 x1, s32 y1, s32 z1);
 *
 * Distance between 3D points.
 *
 * Uses float operations internally for minimal precision loss.
 *
 * Roughly equivalent to:
 * ```
s32 distanceL(s32 x0, s32 y0, s32 z0, s32 x1, s32 y1, s32 z1) {
    f32 x_diff = x1 - x0;
    f32 y_diff = y1 - y0;
    f32 z_diff = z1 - z0;
    f32 sq = SQ(x_diff) + SQ(y_diff) + SQ(z_diff);

    return sqrtf(sq);
}
 * ```
 */
LEAF(distanceL)
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
    mul.s       $ft0, $ft0, $ft0
    mul.s       $ft1, $ft1, $ft1

    add.s       $ft2, $fv0, $ft0
    add.s       $fv0, $ft1, $ft2

    sqrt.s      $ft1, $fv0
    trunc.w.s   $ft2, $ft1
    mfc1        $v0, $ft2

    jr          $ra
END(distanceL)

/**
 * s32 sqrt_a2b2(s32 a, s32 b);
 *
 * Roughly equivalent to:
 * ```
 * s32 sqrt_a2b2(s32 a, s32 b) {
 *    return sqrtf( SQ( (f32)a ) + SQ( (f32)b ));
 * }
 * ```
 */
LEAF(sqrt_a2b2)
    mtc1        $a0, $ft0
    mtc1        $a1, $ft1
    cvt.s.w     $fv0, $ft0
    cvt.s.w     $ft0, $ft1
    mul.s       $ft1, $fv0, $fv0
    mul.s       $ft2, $ft0, $ft0
    add.s       $fv0, $ft1, $ft2
    sqrt.s      $ft1, $fv0
    trunc.w.s   $ft2, $ft1
    mfc1        $v0, $ft2

    jr          $ra
END(sqrt_a2b2)

/**
 * s32 sqrt_abc(s32 arg0, s32 arg1, s32 arg2);
 *
 * Roughly equivalent to:
 * ```
 * s32 sqrt_abc(s32 a, s32 b) {
 *    return sqrtf( SQ( (f32)a ) + SQ( (f32)b ) + SQ( (f32)c ));
 * }
 * ```
 */
LEAF(sqrt_abc)
    mtc1        $a0, $ft0
    mtc1        $a1, $ft1
    mtc1        $a2, $ft2
    cvt.s.w     $fv0, $ft0
    cvt.s.w     $ft0, $ft1
    mul.s       $ft1, $fv0, $fv0
    mul.s       $fv0, $ft0, $ft0
    cvt.s.w     $ft0, $ft2
    mul.s       $ft2, $ft0, $ft0
    add.s       $ft0, $ft1, $fv0
    add.s       $fv0, $ft0, $ft2
    sqrt.s      $ft1, $fv0
    trunc.w.s   $ft2, $ft1
    mfc1        $v0, $ft2

    jr          $ra
END(sqrt_abc)

/**
 * s32 muldiv(s32 a, s32 b, s32 c);
 *
 * Computes (a * b) / c without overflowing.
 *
 * Roughly equivalent to:
 * ```
s32 muldiv(s32 a, s32 b, s32 c) {
    s32 sign = (a ^ b ^ c);
    s32 i;
    u32 hi;
    u32 lo;
    s64 mult64;
    s32 ret;

    a = ABS(a);
    b = ABS(b);
    c = ABS(c);

    // Grab the hi32 and lo32 bits
    mult64 = (s64)a * (s64)b;
    lo = (s32)mult64;
    hi = (s32)(mult64 >> 32);

    // Shift-subtract division algorithm
    ret = 0;
    for (i = 0; i < 32; i++) {
        ret <<= 1;
        if (hi >= c) {
            ret |= 1;
            hi -= c;
        }
        hi = (lo >> 31) | (hi << 1);
        lo *= 2;
    }

    if (sign < 0) {
        return -ret;
    }
    return ret;
}
 * ```
 */

#if VERSION_CN
.global muldiv.NON_MATCHING
.type muldiv.NON_MATCHING, @object
muldiv.NON_MATCHING:
#endif

LEAF(muldiv)
    // Figure out the sign
    xor         $t9, $a0, $a1
    xor         $t8, $t9, $a2

    // TODO: No clue how to fix this
#if VERSION_CN
.set noreorder
    // Abs a
    bgez        $a0, 1f
     move        $t2, $a0
    neg         $t2, $a0
1:

    // Abs b
    bgez        $a1, 1f
     move        $t3, $a1
    neg         $t3, $a1
1:

    // Abs c
    bgez        $a2, 1f
     move        $t7, $a2
    neg         $t7, $a2
1:
.set reorder
#else
    // Abs a
    move        $t2, $a0
    bgez        $a0, 1f
    neg         $t2, $a0
1:

    // Abs b
    move        $t3, $a1
    bgez        $a1, 1f
    neg         $t3, $a1
1:

    // Abs c
    move        $t7, $a2
    bgez        $a2, 1f
    neg         $t7, $a2
1:
#endif

    mult        $t2, $t3
    li          $t9, 32
    move        $v0, $zero
    mflo        $t1
    mfhi        $t0

    // Shift-subtract division algorithm
    .Ldiv_loop:
        sll         $v0, $v0, 1

        blt         $t0, $t7, 1f
        ori         $v0, $v0, 1
        subu        $t0, $t0, $t7
    1:

        subu        $t9, $t9, 0x1
        srl         $t2, $t1, 31
        sll         $t3, $t0, 1
        sll         $t1, $t1, 1
        or          $t0, $t2, $t3
    bgez        $t9, .Ldiv_loop

    // Negate result if there was an odd amount of negative inputs.
    bgez        $t8, .Lend
    neg         $v0, $v0

.Lend:
    jr          $ra
END(muldiv)

#if VERSION_CN
.size muldiv.NON_MATCHING, . - muldiv.NON_MATCHING
#endif


/**
 * void makeVect(s16 arg0, s16 arg1, s32 *arg2, s32 *arg3, s32 *arg4);
 *
 * Roughly equivalent to:
 * ```
void makeVect(s16 arg0, s16 arg1, s32 *arg2, s32 *arg3, s32 *arg4) {
    s32 temp_s5 = -sinL(arg0);
    s32 temp_s6 = cosL(arg0);
    s32 temp_s7 = sinL(arg1);
    s32 temp_t3 = cosL(arg1);

    // spherical coordinates of radius 1?
    *arg3 = temp_s5;
    *arg2 = (temp_s7 * temp_s6) >> 15;
    *arg4 = (temp_t3 * temp_s6) >> 15;
}
 * ```
 */
LEAF(makeVect)
    move        $t1, $ra

    lw          $t0, 0x10($sp)
    bal         sinL
    negu        $t4, $v0

    bal         cosL
    move        $t5, $v0

    move        $a0, $a1
    bal         sinL
    move        $t2, $v0

    bal         cosL
    move        $t3, $v0

    sw          $t4, 0x0($a3)

    mul         $t8, $t2, $t5
    sra         $t9, $t8, 15
    sw          $t9, 0x0($a2)

    mul         $t8, $t3, $t5
    sra         $t9, $t8, 15
    sw          $t9, 0x0($t0)

    move        $ra, $t1
    jr          $ra
END(makeVect)

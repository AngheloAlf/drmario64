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

    srl        $v0, $v0, 1
    NOP_IQUE
    jr          $ra
END(func_8007EA58)

.section .data, "wa"

SYM_START(D_800AB320)
    .byte 0x00, 0x03, 0x06, 0x08
    .byte 0x0A, 0x0D, 0x0F, 0x11
    .byte 0x13, 0x15, 0x17, 0x19
SYM_END(D_800AB320)

/* Fake symbol? */
SYM_START(D_800AB32C)
    .word 0x1B1C1E1F
    .word 0x20202020
SYM_END(D_800AB32C)

SYM_START(D_800AB334)
    .word 0x00000000, 0x00648D18, 0x00C9393C, 0x012E239C
    .word 0x01936BB8, 0x01F93183, 0x025F958E, 0x02C6B932
    .word 0x032EBEBC, 0x0397C99D, 0x0401FE9D, 0x046D840F
    .word 0x04DA820D, 0x054922B8, 0x05B9927D, 0x062C0065
    .word 0x06A09E66, 0x0717A1C6, 0x07914383, 0x080DC0CD
    .word 0x088D5B8C, 0x09105AF7, 0x09970C44, 0x0A21C36D
    .word 0x0AB0DC15, 0x0B44BA8A, 0x0BDDCCF6, 0x0C7C8CBE
    .word 0x0D218015, 0x0DCD3BE0, 0x0E8065E3, 0x0F3BB757
SYM_END(D_800AB334)

SYM_START(D_800AB3B4)
    .word 0x10000000, 0xFFFFFFFF, 0x028BC48E, 0x028AFB8E
    .word 0x02896A18, 0x02871113, 0x0283F1FB, 0x02800EBC
    .word 0x027B69B9, 0x027605D4, 0x026FE65E, 0x02690F18
    .word 0x02618440, 0x02594A7D, 0x025066DF, 0x0246DEE6
    .word 0x023CB868, 0x0231F9B4, 0x0226A964, 0x021ACE77
    .word 0x020E7038, 0x02019645, 0x01F44893, 0x01E68F51
    .word 0x01D872F9, 0x01C9FC39, 0x01BB3404, 0x01AC2375
    .word 0x019CD3D2, 0x018D4E95, 0x017D9D49, 0x016DC99D
    .word 0x015DDD57, 0x014DE244, 0x013DE246
SYM_END(D_800AB3B4)

.section .text, "ax"

/**
 * s32 func_8007EAEC(s32 arg0, s32 arg1);
 *
 * TODO: this function is used (by an unused function, duh), so it would be nice
 * to document it.
 */
LEAF(func_8007EAEC)
    move        $t4, $zero
    NOP_IQUE
    bnez        $a0, .L8007EB1C

    bnez        $a1, .L8007EB04

    li          $v0, 0x0
    NOP_IQUE
    b           .L8007EC48

.L8007EB04:
    bgez        $a1, .L8007EB14

    li          $v0, 0xC000
    NOP_IQUE
    b           .L8007EC48

.L8007EB14:
    li          $v0, 0x4000
    NOP_IQUE
    b           .L8007EC48

.L8007EB1C:
    bgez        $a0, .L8007EB2C

    negu        $a0, $a0
    xori        $t4, $t4, 0x110
.L8007EB2C:
    bnez        $a1, .L8007EB4C

    bnez        $t4, .L8007EB44

    li          $v0, 0x0
    NOP_IQUE
    b           .L8007EC48

.L8007EB44:
    li          $v0, 0x8000
    NOP_IQUE
    b           .L8007EC48

.L8007EB4C:
    bgez        $a1, .L8007EB5C

    negu        $a1, $a1
    xori        $t4, $t4, 0x10
.L8007EB5C:
    subu        $t8, $a0, $a1
    bgez        $t8, .L8007EB78

    move        $t8, $a0
    move        $a0, $a1
    move        $a1, $t8
    xori        $t4, $t4, 0x1
.L8007EB78:
    li          $t8, 0x40000000
    divu_ds     $t8, $t8, $a0

    nop
    nop
    multu       $t8, $a1
    mflo        $t9
    srl         $a0, $t9, 2
    srl         $t8, $a0, 24
    lbu         $v1, (D_800AB320)($t8)
    sll         $t2, $v1, 2

    .L8007EBB8:
        lw          $t9, (D_800AB334)($t2)
        addiu       $v1, $v1, 0x1
        addiu       $t2, $t2, 0x4
        subu        $t8, $a0, $t9
    bgez        $t8, .L8007EBB8

    addiu       $v1, $v1, -0x2
    lw          $t8, (D_800AB32C)($t2)
    sll         $v0, $v1, 8
    NOP_IQUE
    beq         $a0, $t8, .L8007EC14

    subu        $t3, $a0, $t8
    lw          $t8, (D_800AB3B4)($t2)
    multu       $t3, $t8
    mfhi        $t8
    srl         $t8, $t8, 8
    andi        $t9, $t8, 0xFF
    or          $v0, $v0, $t9
.L8007EC14:
    andi        $t8, $t4, 0x1
    beqz        $t8, .L8007EC28

    li          $t8, 0x4000
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

.section .data, "wa"

SYM_START(D_800AB440)
    .short 0x0000, 0x00C9, 0x0192, 0x025B, 0x0324, 0x03ED, 0x04B6, 0x057F, 0x0648, 0x0711, 0x07D9, 0x08A2, 0x096B, 0x0A33, 0x0AFB, 0x0BC4
    .short 0x0C8C, 0x0D54, 0x0E1C, 0x0EE4, 0x0FAB, 0x1073, 0x113A, 0x1201, 0x12C8, 0x138F, 0x1455, 0x151C, 0x15E2, 0x16A8, 0x176E, 0x1833
    .short 0x18F9, 0x19BE, 0x1A83, 0x1B47, 0x1C0C, 0x1CD0, 0x1D93, 0x1E57, 0x1F1A, 0x1FDD, 0x209F, 0x2162, 0x2224, 0x22E5, 0x23A7, 0x2467
    .short 0x2528, 0x25E8, 0x26A8, 0x2768, 0x2827, 0x28E5, 0x29A4, 0x2A62, 0x2B1F, 0x2BDC, 0x2C99, 0x2D55, 0x2E11, 0x2ECC, 0x2F87, 0x3042
    .short 0x30FC, 0x31B5, 0x326E, 0x3327, 0x33DF, 0x3497, 0x354E, 0x3604, 0x36BA, 0x3770, 0x3825, 0x38D9, 0x398D, 0x3A40, 0x3AF3, 0x3BA5
    .short 0x3C57, 0x3D08, 0x3DB8, 0x3E68, 0x3F17, 0x3FC6, 0x4074, 0x4121, 0x41CE, 0x427A, 0x4326, 0x43D1, 0x447B, 0x4524, 0x45CD, 0x4675
    .short 0x471D, 0x47C4, 0x486A, 0x490F, 0x49B4, 0x4A58, 0x4AFB, 0x4B9E, 0x4C40, 0x4CE1, 0x4D81, 0x4E21, 0x4EC0, 0x4F5E, 0x4FFB, 0x5098
    .short 0x5134, 0x51CF, 0x5269, 0x5303, 0x539B, 0x5433, 0x54CA, 0x5560, 0x55F6, 0x568A, 0x571E, 0x57B1, 0x5843, 0x58D4, 0x5964, 0x59F4
    .short 0x5A82, 0x5B10, 0x5B9D, 0x5C29, 0x5CB4, 0x5D3E, 0x5DC8, 0x5E50, 0x5ED7, 0x5F5E, 0x5FE4, 0x6068, 0x60EC, 0x616F, 0x61F1, 0x6272
    .short 0x62F2, 0x6371, 0x63EF, 0x646C, 0x64E9, 0x6564, 0x65DE, 0x6657, 0x66D0, 0x6747, 0x67BD, 0x6832, 0x68A7, 0x691A, 0x698C, 0x69FD
    .short 0x6A6E, 0x6ADD, 0x6B4B, 0x6BB8, 0x6C24, 0x6C8F, 0x6CF9, 0x6D62, 0x6DCA, 0x6E31, 0x6E97, 0x6EFB, 0x6F5F, 0x6FC2, 0x7023, 0x7083
    .short 0x70E3, 0x7141, 0x719E, 0x71FA, 0x7255, 0x72AF, 0x7308, 0x735F, 0x73B6, 0x740B, 0x7460, 0x74B3, 0x7505, 0x7556, 0x75A6, 0x75F4
    .short 0x7642, 0x768E, 0x76D9, 0x7723, 0x776C, 0x77B4, 0x77FB, 0x7840, 0x7885, 0x78C8, 0x790A, 0x794A, 0x798A, 0x79C9, 0x7A06, 0x7A42
    .short 0x7A7D, 0x7AB7, 0x7AEF, 0x7B27, 0x7B5D, 0x7B92, 0x7BC6, 0x7BF9, 0x7C2A, 0x7C5A, 0x7C89, 0x7CB7, 0x7CE4, 0x7D0F, 0x7D3A, 0x7D63
    .short 0x7D8A, 0x7DB1, 0x7DD6, 0x7DFB, 0x7E1E, 0x7E3F, 0x7E60, 0x7E7F, 0x7E9D, 0x7EBA, 0x7ED6, 0x7EF0, 0x7F0A, 0x7F22, 0x7F38, 0x7F4E
    .short 0x7F62, 0x7F75, 0x7F87, 0x7F98, 0x7FA7, 0x7FB5, 0x7FC2, 0x7FCE, 0x7FD9, 0x7FE2, 0x7FEA, 0x7FF1, 0x7FF6, 0x7FFA, 0x7FFE, 0x7FFF
    .short 0x7FFF, 0x7FFF, 0x7FFE, 0x7FFA, 0x7FF6, 0x7FF1, 0x7FEA, 0x7FE2, 0x7FD9, 0x7FCE, 0x7FC2, 0x7FB5, 0x7FA7, 0x7F98, 0x7F87, 0x7F75
    .short 0x7F62, 0x7F4E, 0x7F38, 0x7F22, 0x7F0A, 0x7EF0, 0x7ED6, 0x7EBA, 0x7E9D, 0x7E7F, 0x7E60, 0x7E3F, 0x7E1E, 0x7DFB, 0x7DD6, 0x7DB1
    .short 0x7D8A, 0x7D63, 0x7D3A, 0x7D0F, 0x7CE4, 0x7CB7, 0x7C89, 0x7C5A, 0x7C2A, 0x7BF9, 0x7BC6, 0x7B92, 0x7B5D, 0x7B27, 0x7AEF, 0x7AB7
    .short 0x7A7D, 0x7A42, 0x7A06, 0x79C9, 0x798A, 0x794A, 0x790A, 0x78C8, 0x7885, 0x7840, 0x77FB, 0x77B4, 0x776C, 0x7723, 0x76D9, 0x768E
    .short 0x7642, 0x75F4, 0x75A6, 0x7556, 0x7505, 0x74B3, 0x7460, 0x740B, 0x73B6, 0x735F, 0x7308, 0x72AF, 0x7255, 0x71FA, 0x719E, 0x7141
    .short 0x70E3, 0x7083, 0x7023, 0x6FC2, 0x6F5F, 0x6EFB, 0x6E97, 0x6E31, 0x6DCA, 0x6D62, 0x6CF9, 0x6C8F, 0x6C24, 0x6BB8, 0x6B4B, 0x6ADD
    .short 0x6A6E, 0x69FD, 0x698C, 0x691A, 0x68A7, 0x6832, 0x67BD, 0x6747, 0x66D0, 0x6657, 0x65DE, 0x6564, 0x64E9, 0x646C, 0x63EF, 0x6371
    .short 0x62F2, 0x6272, 0x61F1, 0x616F, 0x60EC, 0x6068, 0x5FE4, 0x5F5E, 0x5ED7, 0x5E50, 0x5DC8, 0x5D3E, 0x5CB4, 0x5C29, 0x5B9D, 0x5B10
    .short 0x5A82, 0x59F4, 0x5964, 0x58D4, 0x5843, 0x57B1, 0x571E, 0x568A, 0x55F6, 0x5560, 0x54CA, 0x5433, 0x539B, 0x5303, 0x5269, 0x51CF
    .short 0x5134, 0x5098, 0x4FFB, 0x4F5E, 0x4EC0, 0x4E21, 0x4D81, 0x4CE1, 0x4C40, 0x4B9E, 0x4AFB, 0x4A58, 0x49B4, 0x490F, 0x486A, 0x47C4
    .short 0x471D, 0x4675, 0x45CD, 0x4524, 0x447B, 0x43D1, 0x4326, 0x427A, 0x41CE, 0x4121, 0x4074, 0x3FC6, 0x3F17, 0x3E68, 0x3DB8, 0x3D08
    .short 0x3C57, 0x3BA5, 0x3AF3, 0x3A40, 0x398D, 0x38D9, 0x3825, 0x3770, 0x36BA, 0x3604, 0x354E, 0x3497, 0x33DF, 0x3327, 0x326E, 0x31B5
    .short 0x30FC, 0x3042, 0x2F87, 0x2ECC, 0x2E11, 0x2D55, 0x2C99, 0x2BDC, 0x2B1F, 0x2A62, 0x29A4, 0x28E5, 0x2827, 0x2768, 0x26A8, 0x25E8
    .short 0x2528, 0x2467, 0x23A7, 0x22E5, 0x2224, 0x2162, 0x209F, 0x1FDD, 0x1F1A, 0x1E57, 0x1D93, 0x1CD0, 0x1C0C, 0x1B47, 0x1A83, 0x19BE
    .short 0x18F9, 0x1833, 0x176E, 0x16A8, 0x15E2, 0x151C, 0x1455, 0x138F, 0x12C8, 0x1201, 0x113A, 0x1073, 0x0FAB, 0x0EE4, 0x0E1C, 0x0D54
    .short 0x0C8C, 0x0BC4, 0x0AFB, 0x0A33, 0x096B, 0x08A2, 0x07D9, 0x0711, 0x0648, 0x057F, 0x04B6, 0x03ED, 0x0324, 0x025B, 0x0192, 0x00C9
    .short 0x0000, 0xFF37, 0xFE6E, 0xFDA5, 0xFCDC, 0xFC13, 0xFB4A, 0xFA81, 0xF9B8, 0xF8EF, 0xF827, 0xF75E, 0xF695, 0xF5CD, 0xF505, 0xF43C
    .short 0xF374, 0xF2AC, 0xF1E4, 0xF11C, 0xF055, 0xEF8D, 0xEEC6, 0xEDFF, 0xED38, 0xEC71, 0xEBAB, 0xEAE4, 0xEA1E, 0xE958, 0xE892, 0xE7CD
    .short 0xE707, 0xE642, 0xE57D, 0xE4B9, 0xE3F4, 0xE330, 0xE26D, 0xE1A9, 0xE0E6, 0xE023, 0xDF61, 0xDE9E, 0xDDDC, 0xDD1B, 0xDC59, 0xDB99
    .short 0xDAD8, 0xDA18, 0xD958, 0xD898, 0xD7D9, 0xD71B, 0xD65C, 0xD59E, 0xD4E1, 0xD424, 0xD367, 0xD2AB, 0xD1EF, 0xD134, 0xD079, 0xCFBE
    .short 0xCF04, 0xCE4B, 0xCD92, 0xCCD9, 0xCC21, 0xCB69, 0xCAB2, 0xC9FC, 0xC946, 0xC890, 0xC7DB, 0xC727, 0xC673, 0xC5C0, 0xC50D, 0xC45B
    .short 0xC3A9, 0xC2F8, 0xC248, 0xC198, 0xC0E9, 0xC03A, 0xBF8C, 0xBEDF, 0xBE32, 0xBD86, 0xBCDA, 0xBC2F, 0xBB85, 0xBADC, 0xBA33, 0xB98B
    .short 0xB8E3, 0xB83C, 0xB796, 0xB6F1, 0xB64C, 0xB5A8, 0xB505, 0xB462, 0xB3C0, 0xB31F, 0xB27F, 0xB1DF, 0xB140, 0xB0A2, 0xB005, 0xAF68
    .short 0xAECC, 0xAE31, 0xAD97, 0xACFD, 0xAC65, 0xABCD, 0xAB36, 0xAAA0, 0xAA0A, 0xA976, 0xA8E2, 0xA84F, 0xA7BD, 0xA72C, 0xA69C, 0xA60C
    .short 0xA57E, 0xA4F0, 0xA463, 0xA3D7, 0xA34C, 0xA2C2, 0xA238, 0xA1B0, 0xA129, 0xA0A2, 0xA01C, 0x9F98, 0x9F14, 0x9E91, 0x9E0F, 0x9D8E
    .short 0x9D0E, 0x9C8F, 0x9C11, 0x9B94, 0x9B17, 0x9A9C, 0x9A22, 0x99A9, 0x9930, 0x98B9, 0x9843, 0x97CE, 0x9759, 0x96E6, 0x9674, 0x9603
    .short 0x9592, 0x9523, 0x94B5, 0x9448, 0x93DC, 0x9371, 0x9307, 0x929E, 0x9236, 0x91CF, 0x9169, 0x9105, 0x90A1, 0x903E, 0x8FDD, 0x8F7D
    .short 0x8F1D, 0x8EBF, 0x8E62, 0x8E06, 0x8DAB, 0x8D51, 0x8CF8, 0x8CA1, 0x8C4A, 0x8BF5, 0x8BA0, 0x8B4D, 0x8AFB, 0x8AAA, 0x8A5A, 0x8A0C
    .short 0x89BE, 0x8972, 0x8927, 0x88DD, 0x8894, 0x884C, 0x8805, 0x87C0, 0x877B, 0x8738, 0x86F6, 0x86B6, 0x8676, 0x8637, 0x85FA, 0x85BE
    .short 0x8583, 0x8549, 0x8511, 0x84D9, 0x84A3, 0x846E, 0x843A, 0x8407, 0x83D6, 0x83A6, 0x8377, 0x8349, 0x831C, 0x82F1, 0x82C6, 0x829D
    .short 0x8276, 0x824F, 0x822A, 0x8205, 0x81E2, 0x81C1, 0x81A0, 0x8181, 0x8163, 0x8146, 0x812A, 0x8110, 0x80F6, 0x80DE, 0x80C8, 0x80B2
    .short 0x809E, 0x808B, 0x8079, 0x8068, 0x8059, 0x804B, 0x803E, 0x8032, 0x8027, 0x801E, 0x8016, 0x800F, 0x800A, 0x8006, 0x8002, 0x8001
    .short 0x8000, 0x8001, 0x8002, 0x8006, 0x800A, 0x800F, 0x8016, 0x801E, 0x8027, 0x8032, 0x803E, 0x804B, 0x8059, 0x8068, 0x8079, 0x808B
    .short 0x809E, 0x80B2, 0x80C8, 0x80DE, 0x80F6, 0x8110, 0x812A, 0x8146, 0x8163, 0x8181, 0x81A0, 0x81C1, 0x81E2, 0x8205, 0x822A, 0x824F
    .short 0x8276, 0x829D, 0x82C6, 0x82F1, 0x831C, 0x8349, 0x8377, 0x83A6, 0x83D6, 0x8407, 0x843A, 0x846E, 0x84A3, 0x84D9, 0x8511, 0x8549
    .short 0x8583, 0x85BE, 0x85FA, 0x8637, 0x8676, 0x86B6, 0x86F6, 0x8738, 0x877B, 0x87C0, 0x8805, 0x884C, 0x8894, 0x88DD, 0x8927, 0x8972
    .short 0x89BE, 0x8A0C, 0x8A5A, 0x8AAA, 0x8AFB, 0x8B4D, 0x8BA0, 0x8BF5, 0x8C4A, 0x8CA1, 0x8CF8, 0x8D51, 0x8DAB, 0x8E06, 0x8E62, 0x8EBF
    .short 0x8F1D, 0x8F7D, 0x8FDD, 0x903E, 0x90A1, 0x9105, 0x9169, 0x91CF, 0x9236, 0x929E, 0x9307, 0x9371, 0x93DC, 0x9448, 0x94B5, 0x9523
    .short 0x9592, 0x9603, 0x9674, 0x96E6, 0x9759, 0x97CE, 0x9843, 0x98B9, 0x9930, 0x99A9, 0x9A22, 0x9A9C, 0x9B17, 0x9B94, 0x9C11, 0x9C8F
    .short 0x9D0E, 0x9D8E, 0x9E0F, 0x9E91, 0x9F14, 0x9F98, 0xA01C, 0xA0A2, 0xA129, 0xA1B0, 0xA238, 0xA2C2, 0xA34C, 0xA3D7, 0xA463, 0xA4F0
    .short 0xA57E, 0xA60C, 0xA69C, 0xA72C, 0xA7BD, 0xA84F, 0xA8E2, 0xA976, 0xAA0A, 0xAAA0, 0xAB36, 0xABCD, 0xAC65, 0xACFD, 0xAD97, 0xAE31
    .short 0xAECC, 0xAF68, 0xB005, 0xB0A2, 0xB140, 0xB1DF, 0xB27F, 0xB31F, 0xB3C0, 0xB462, 0xB505, 0xB5A8, 0xB64C, 0xB6F1, 0xB796, 0xB83C
    .short 0xB8E3, 0xB98B, 0xBA33, 0xBADC, 0xBB85, 0xBC2F, 0xBCDA, 0xBD86, 0xBE32, 0xBEDF, 0xBF8C, 0xC03A, 0xC0E9, 0xC198, 0xC248, 0xC2F8
    .short 0xC3A9, 0xC45B, 0xC50D, 0xC5C0, 0xC673, 0xC727, 0xC7DB, 0xC890, 0xC946, 0xC9FC, 0xCAB2, 0xCB69, 0xCC21, 0xCCD9, 0xCD92, 0xCE4B
    .short 0xCF04, 0xCFBE, 0xD079, 0xD134, 0xD1EF, 0xD2AB, 0xD367, 0xD424, 0xD4E1, 0xD59E, 0xD65C, 0xD71B, 0xD7D9, 0xD898, 0xD958, 0xDA18
    .short 0xDAD8, 0xDB99, 0xDC59, 0xDD1B, 0xDDDC, 0xDE9E, 0xDF61, 0xE023, 0xE0E6, 0xE1A9, 0xE26D, 0xE330, 0xE3F4, 0xE4B9, 0xE57D, 0xE642
    .short 0xE707, 0xE7CD, 0xE892, 0xE958, 0xEA1E, 0xEAE4, 0xEBAB, 0xEC71, 0xED38, 0xEDFF, 0xEEC6, 0xEF8D, 0xF055, 0xF11C, 0xF1E4, 0xF2AC
    .short 0xF374, 0xF43C, 0xF505, 0xF5CD, 0xF695, 0xF75E, 0xF827, 0xF8EF, 0xF9B8, 0xFA81, 0xFB4A, 0xFC13, 0xFCDC, 0xFDA5, 0xFE6E, 0xFF37
    .short 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000
SYM_END(D_800AB440)

.section .text, "ax"

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
    li          $v0, 0x3
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
    li          $t8, 0x8000
    sw          $zero, 0x2C($a2)
    sw          $zero, 0x1C($a2)
    sw          $zero, 0xC($a2)
    sw          $t8, 0x3C($a2)
    li          $v0, 0x3
    move        $v1, $a2
    move        $t0, $a1
    move        $t1, $a0

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
    NOP_IQUE
    jr          $ra
END(makeScaleMatrix)

/**
 * void makeMatrix(Mtx *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
 */
LEAF(makeMatrix)
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
    NOP_IQUE
    bal         func_8007EC54

    move        $t2, $v0
    NOP_IQUE
    bal         func_8007EC98

    move        $t3, $v0
    move        $a0, $a3
    NOP_IQUE
    bal         func_8007EC54

    move        $t4, $v0
    NOP_IQUE
    bal         func_8007EC98

    move        $t5, $v0
    move        $a0, $a1
    NOP_IQUE
    bal         func_8007EC54

    move        $t6, $v0
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
    move        $ra, $t1
    jr          $ra
END(makeMatrix)

/**
 * void func_8007F214(UNK_TYPE *arg0, u32 arg1, s32 arg2, s32 arg3, s32 arg4);
 *
 * `arg0` may be a `Mtx *`
 */
LEAF(func_8007F214)
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
    NOP_IQUE
    bal         func_8007EC54

    move        $t3, $v0
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
    move        $ra, $t1
    jr          $ra
END(func_8007F214)

/**
 * void func_8007F284(UNK_TYPE *arg0, u32 arg1, s32 arg2, s32 arg3, s32 arg4);
 *
 * `arg0` may be a `Mtx *`
 */
LEAF(func_8007F284)
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
    NOP_IQUE
    bal         func_8007EC54

    move        $t3, $v0
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
    move        $ra, $t1
    jr          $ra
END(func_8007F284)

/**
 * void func_8007F2F4(UNK_TYPE *arg0, u32 arg1, s32 arg2, s32 arg3, s32 arg4);
 *
 * `arg0` may be a `Mtx *`
 */
LEAF(func_8007F2F4)
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
    NOP_IQUE
    bal         func_8007EC54

    move        $t3, $v0
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
    move        $ra, $t1
    jr          $ra
END(func_8007F2F4)

/**
 * void func_8007F364(UNK_TYPE *arg0, s32 arg1, s32 arg2);
 *
 * `arg0` may be a `Mtx *`
 */
LEAF(func_8007F364)
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
    NOP_IQUE
    bal         func_8007EC54

    move        $t2, $v0
    NOP_IQUE
    bal         func_8007EC98

    move        $t3, $v0
    move        $a0, $a1
    NOP_IQUE
    bal         func_8007EC54

    move        $t4, $v0
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
    move        $ra, $t1
    jr          $ra
END(func_8007F364)

/**
 * void matrixConv(Mtx *arg0, Mtx *arg1, s32 arg2);
 */
LEAF(matrixConv)
    li          $t0, 0xFFFF0000
    li          $v0, 0x8
    NOP_IQUE
    beqz        $a2, .L8007F4CC

    li          $v0, 0x6
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
    li          $t8, 0x4

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
    move        $t1, $ra
    lw          $t0, 0x10($sp)
    NOP_IQUE
    bal         func_8007EC98

    move        $v1, $v0
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
    move        $ra, $t1
    jr          $ra
END(func_8007F550)

/**
 * s32 func_8007F60C(s32 arg0, s32 arg1)
 */
LEAF(func_8007F60C)
    andi        $t2, $a0, 0xFFFF
    andi        $t3, $a1, 0xFFFF
    li          $v0, 0x10000
    bge         $t2, $t3, .L8007F630

    addu        $t4, $t2, $v0
    move        $t5, $t3
    NOP_IQUE
    b           .L8007F638

.L8007F630:
    move        $t4, $t2
    addu        $t5, $t3, $v0
.L8007F638:
    subu        $v0, $t3, $t2
    subu        $v1, $t5, $t4
    move        $t2, $v0
    bgez        $v0, .L8007F64C

    neg         $t2, $v0
.L8007F64C:
    move        $t3, $v1
    bgez        $v1, .L8007F658

    neg         $t3, $v1
.L8007F658:
    bge         $t3, $t2, .L8007F668

    move        $v0, $v1
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
    move        $t2, $a0
    bgez        $a0, .L8007F7B0

    neg         $t2, $a0
.L8007F7B0:
    move        $t3, $a1
    bgez        $a1, .L8007F7BC

    neg         $t3, $a1
.L8007F7BC:
    move        $t7, $a2
    bgez        $a2, .L8007F7C8

    neg         $t7, $a2
.L8007F7C8:
    NOP_N64
    mult        $t2, $t3
    li          $t9, 0x20
    move        $v0, $zero
    mflo        $t1
    mfhi        $t0

    .L8007F7E0:
        sll         $v0, $v0, 1
        blt         $t0, $t7, .L8007F7F8

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

    neg         $v0, $v0

.L8007F81C:
    jr          $ra
END(func_8007F798)


/**
 * void func_8007F824(UNK_TYPE *arg0, u32 arg1, s32 arg2, s32 arg3, s32 arg4);
 *
 * `arg0` may be a `Mtx *`
 */
LEAF(func_8007F824)
    move        $t1, $ra
    lw          $t0, 0x10($sp)
    NOP_IQUE
    bal         func_8007EC54

    negu        $t4, $v0
    NOP_IQUE
    bal         func_8007EC98

    move        $t5, $v0
    move        $a0, $a1
    NOP_IQUE
    bal         func_8007EC54

    move        $t2, $v0
    NOP_IQUE
    bal         func_8007EC98

    move        $t3, $v0
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
    move        $ra, $t1
    jr          $ra
END(func_8007F824)

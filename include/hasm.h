#ifndef HASM_H
#define HASM_H


#define LEAF(x)                 \
    .balign 4                  ;\
    .globl x                   ;\
    .type x, @function         ;\
    x:                         ;\
        .ent x, 0              ;\
        .frame $sp, 0, $ra

#define END(x)                  \
    .size x, . - x             ;\
    .end x


#define BOOT_STACK_SIZE 0x2000


#endif

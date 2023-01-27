.macro glabel label
    .global \label
    .type \label, @function
    \label:
.endm

.macro dlabel label
    .global \label
    \label:
.endm

.macro jlabel label
#if VERSION_CN
    .global \label
    .type \label, @function
#endif
    \label:
.endm

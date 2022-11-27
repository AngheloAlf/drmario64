.macro glabel label
    .global \label
    \label:
.endm

.macro dlabel label
    .global \label
    \label:
.endm

.macro jlabel label
    \label:
.endm

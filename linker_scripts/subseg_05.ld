SECTIONS {
    . = 0x05000000;

    .text         : {  FILL(0x00000000); *(.text*)          }
    .rodata       : {  FILL(0x00000000); *(.rodata*)        }
    .data         : {  FILL(0x00000000); *(.data*)          }
    .bss (NOLOAD) : {  FILL(0x00000000); *(.bss*) *(COMMON) }

    .reloc    0 : { *(.reloc*)   }
    .symtab   0 : { *(.symtab)   }
    .strtab   0 : { *(.strtab)   }
    .shstrtab 0 : { *(.shstrtab) }

    /DISCARD/ :
    {
        *(.reginfo);
        *(.MIPS.abiflags);
        *(.MIPS.options);
        *(.note.gnu.build-id);
        *(.interp);
        *(.eh_frame);
        *(*);
    }
}


ENTRY(kernel_start)
OUTPUT_FORMAT(elf32-i386)
OUTPUT_ARCH(i386:i386)

SECTIONS
{
    . = 1M;

    .text : ALIGN(4K) {
        . = ALIGN(8);
		*(.multiboot)
        *(.text*)
        *(.init)
        *(.fini)
        *(.rodata)
    }

    .data : ALIGN(4K) {
        ctors_begin = .;
        KEEP(*(.init_array))
        KEEP(*(SORT_BY_INIT_PRIORITY(.init_array.*)))
        ctors_end = .;

        *(.data)
    }

    .bss : ALIGN(4K) {
        *(.bss)
    }

    /DISCARD/ : {
        *(.fini_array*)
        *(.comment)
    }
}

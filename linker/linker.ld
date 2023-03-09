
ENTRY(kernel_start)
OUTPUT_FORMAT(elf32_i386)
OUTPUT_ARCH(i386:i386)

SECTIONS
{
    . = 1M;

    .text : {
        *(.multiboot)
        *(.text*)
        *(.rodata)
    }

    .data : {
        ctors_begin = .;
        KEEP(*(.init_array))
        KEEP(*(SORT_BY_INIT_PRIORITY(.init_array.*)))
        ctors_end = .;

        *(.data)
    }

    .bss : {
        *(.bss)
    }

    /DISCARD/ : {
        *(.fini_array*)
        *(.comment)
    }
}
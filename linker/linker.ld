
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
        *(.gnu.linkonce.t*)
    }

    .rodata : ALIGN(4K) {
        *(.rodata*)
        *(.gnu.linkonce.r*)
    }

    .data : ALIGN(4K) {
        *(.data)
        *(.gnu.linkonce.d*)
    }

    .bss : ALIGN(4K) {
        start_bss = .;
        *(.bss)
        *(COMMON)
        *(.gnu.linkonce.b*)
        end_bss = .;
    }

    /DISCARD/ : {
        *(.comment)
        *(.eh_frame)
    }
}

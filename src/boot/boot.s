; Multiboot constants
MBALIGN equ 1<<0
MEMINFO equ 1<<1
MBFLAGS equ (MBALIGN) | (MEMINFO)
MBMAGIC equ 0x1badb002
MBCHECK equ -(MBMAGIC + MBFLAGS)

; Multiboot header
section .multiboot
align 4
    dd MBMAGIC
    dd MBFLAGS
    dd MBCHECK

; Stack
section .bss
align 16
stack_bottom:
    resb 64 * 1024 * 1024
stack_top:

; Code
section .text
global kernel_start
kernel_start:
    mov esp, stack_top
    cli
.forever:
    hlt
    jmp .forever

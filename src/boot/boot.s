; Multiboot constants
MBMAGIC equ 0xE85250D6                                  ; Multiboot2 magic
MBARCH  equ 0                                           ; Protected mode i386
MBSIZE  equ (multiboot_header.end - multiboot_header)   ; Total header size
MBCHECK equ -(MBMAGIC + MBARCH + MBSIZE)                ; Checksum

; Multiboot header
section .multiboot
align 8
multiboot_header:
; Magic bytes
    dd MBMAGIC
    dd MBARCH
    dd MBSIZE
    dd MBCHECK
    
; Information request
.inforeq:
    dw 1    ; Type = INFORMATION REQUEST
    dw 0    ; Flags
    dd (.inforeq_end - .inforeq)    ; Size

    dd 6    ; Memory map
.inforeq_end:

; Terminate tag (end of header)
    dw 0
    dw 0
    dd 8
.end:

; Stack
section .bss
align 16
stack_bottom:
    resb 64 * 1024 * 1024
stack_top:

; Code
section .text
extern kernel_main
global kernel_start
kernel_start:
    mov esp, stack_top
    push ebx
    push eax
    call kernel_main
    add esp, 8
    cli
.forever:
    hlt
    jmp .forever

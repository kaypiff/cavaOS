
section .text

global load_gdt
load_gdt:
    cli
    mov ax, [esp + 4]
    mov word [gdt_descriptor], ax
    mov eax, [esp + 8]
    mov dword [gdt_descriptor + 2], eax
    lgdt [gdt_descriptor]
    jmp 0x08:.reload_segments
.reload_segments:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    ret

section .data

gdt_descriptor:
    dw 0
    dd 0

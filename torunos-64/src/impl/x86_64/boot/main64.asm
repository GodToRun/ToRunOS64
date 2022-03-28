global long_mode_start
extern _Z11kernel_mainv

section .text
bits 64
long_mode_start:
    ; load null into all data segment registers
    mov ax, 0
    mov ss, ax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    call _Z11kernel_mainv
    hlt

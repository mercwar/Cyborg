; =============================================================================
;  AVIS MACRO STUB
;  FILE: fire-macro.asm
; =============================================================================
; fire-macro.asm
section .data
    msg db "hello from the macro.ini", 0xa
    len equ $ - msg

section .text
    global _start
_start:
    ; Hardware-level greeting
    mov rax, 1          ; sys_write
    mov rdi, 1          ; stdout
    mov rsi, msg
    mov rdx, len
    syscall

    mov rax, 60
    xor rdi, rdi
    syscall

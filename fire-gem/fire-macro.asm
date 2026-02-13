; =============================================================================
;  AVIS MACRO STUB
;  FILE: fire-macro.asm
; =============================================================================
section .data
    hello_msg db "hello from the macro.ini", 0xa
    hello_len equ $ - hello_msg

section .text
    global _start
_start:
    ; Hardware-level broadcast of the macro intent
    mov rax, 1          ; sys_write
    mov rdi, 1          ; stdout
    mov rsi, hello_msg
    mov rdx, hello_len
    syscall

    ; Signal completion to the macro engine
    mov rax, 60
    xor rdi, rdi
    syscall

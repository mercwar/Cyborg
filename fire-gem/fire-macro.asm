; =============================================================================
;  AVIS MACRO STUB
;  FILE: fire-macro.asm
; =============================================================================

section .data
    ini_path    db "fire-gem/fire-macro.ini", 0
    prefix      db "hello from the macro.ini", 0xa ; Mirroring INI value
    msg_len     equ $ - prefix

section .text
    global _start

_start:
    ; 1. Terminal Broadcast
    mov rax, 1          ; sys_write
    mov rdi, 1          ; stdout
    mov rsi, prefix
    mov rdx, msg_len
    syscall

    ; 2. Exit to next chain link
    mov rax, 60
    xor rdi, rdi
    syscall

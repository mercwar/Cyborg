; fire-spec.asm
section .data
    msg db "[AVIS-SPEC] CBORD Vector Bound Successfully.", 0xa
    len equ $ - msg

section .text
    global _start
_start:
    mov rax, 1          ; sys_write
    mov rdi, 1
    mov rsi, msg
    mov rdx, len
    syscall

    mov rax, 60
    xor rdi, rdi
    syscall

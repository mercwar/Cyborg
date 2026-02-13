section .data
    msg db 'fire-seed stub active', 0xa
    len equ $ - msg

section .text
    global _start

_start:
    ; Print message to terminal
    mov rax, 1          ; sys_write
    mov rdi, 1          ; stdout
    mov rsi, msg
    mov rdx, len
    syscall

    ; Exit
    mov rax, 60         ; sys_exit
    xor rdi, rdi
    syscall

; fire-gem/fire-gem.asm
section .data
    hello_msg db 'hello', 0xa  ; The message you requested
    hello_len equ $ - hello_msg

section .text
    global _start

_start:
    ; Write syscall to output 'hello'
    mov rax, 1          ; sys_write
    mov rdi, 1          ; stdout
    mov rsi, hello_msg
    mov rdx, hello_len
    syscall

    ; Exit syscall
    mov rax, 60         ; sys_exit
    xor rdi, rdi        ; status 0
    syscall

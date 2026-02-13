section .data
    dir1 db "fire-gem/deployed", 0
    file1 db "fire-gem/deployed/hello.txt", 0
    msg db "hello from fire-gem", 0xa
    len equ $ - msg

section .text
    global _start
_start:
    mov rax, 83         ; sys_mkdir
    mov rdi, dir1
    mov rsi, 0755o
    syscall

    mov rax, 2          ; sys_open
    mov rdi, file1
    mov rsi, 65         ; O_CREAT | O_WRONLY
    mov rdx, 0644o
    syscall

    mov rdi, rax
    mov rax, 1          ; sys_write
    mov rsi, msg
    mov rdx, len
    syscall

    mov rax, 60         ; Exit builder
    xor rdi, rdi
    syscall

section .data
    done_msg db "[SYNC] AVIS Environment Complete. HAHA!", 0xa
    done_len equ $ - done_msg
    log_path db "fire-gem/fire-gem.log", 0

section .text
    global _start
_start:
    ; Open log in Append mode
    mov rax, 2          ; sys_open
    mov rdi, log_path
    mov rsi, 1089       ; O_CREAT | O_WRONLY | O_APPEND
    mov rdx, 0644o
    syscall

    ; Write termination signal
    mov rdi, rax
    mov rax, 1          ; sys_write
    mov rsi, done_msg
    mov rdx, done_len
    syscall

    ; Final Kernel Exit
    mov rax, 60         ; sys_exit
    xor rdi, rdi
    syscall

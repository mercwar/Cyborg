; fire-end.asm
section .data
    log_path db "fire-gem/fire-gem.log", 0
    end_msg  db "[AVIS-END] Chain Sync Complete. HAHA!", 0xa
    end_len  equ $ - end_msg

section .text
    global _start
_start:
    ; 1. Open log to append final signal
    mov rax, 2
    mov rdi, log_path
    mov rsi, 1089
    mov rdx, 0644o
    syscall
    mov r8, rax

    mov rax, 1
    mov rdi, r8
    mov rsi, end_msg
    mov rdx, end_len
    syscall

    ; 2. Force Disk Sync
    mov rax, 74         ; sys_fsync
    mov rdi, r8
    syscall

    ; 3. Kernel Shutdown
    mov rax, 60
    xor rdi, rdi
    syscall

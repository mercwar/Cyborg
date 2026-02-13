; fire-gem/fire-end.asm
section .data
    log_path db "fire-gem/fire-gem.log", 0
    end_msg  db "[AVIS-END] Chain Sync Complete. HAHA!", 0xa
    end_len  equ $ - end_msg

section .text
    global _start

_start:
    ; Open log in Append mode (1089)
    mov rax, 2          ; sys_open
    mov rdi, log_path
    mov rsi, 1089       
    mov rdx, 0644o
    syscall
    
    ; Write the terminator signal
    mov rdi, rax
    mov rax, 1          ; sys_write
    mov rsi, end_msg
    mov rdx, end_len
    syscall

    ; Final exit
    mov rax, 60
    xor rdi, rdi
    syscall

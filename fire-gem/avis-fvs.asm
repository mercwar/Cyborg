; avis-fvs.asm
section .data
    log_path db "fire-gem/fire-gem.log", 0
    fvs_msg  db "[AVIS-FVS] Identity Verified: Registers Cleared. HAHA!", 0xa
    fvs_len  equ $ - fvs_msg

section .text
    global _start
_start:
    ; 1. Clear GPRs 
    xor rax, rax
    xor rbx, rbx
    xor rcx, rcx
    xor rdx, rdx

    ; 2. Log Handshake
    mov rax, 2          ; sys_open
    mov rdi, log_path
    mov rsi, 1089       ; O_CREAT|O_WRONLY|O_APPEND
    mov rdx, 0644o
    syscall
    mov rdi, rax
    mov rax, 1          ; sys_write
    mov rsi, fvs_msg
    mov rdx, fvs_len
    syscall

    ; 3. Exit
    mov rax, 60
    xor rdi, rdi
    syscall

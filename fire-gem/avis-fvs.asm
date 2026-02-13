; avis-fvs.asm
section .data
    log_path db "fire-gem/fire-gem.log", 0
    msg      db "[AVIS-FVS] Identity Verified: Registers Cleared. HAHA!", 0xa
    len      equ $ - msg

section .text
    global _start
_start:
    ; 1. Clear GPRs for baseline
    xor rax, rax
    xor rbx, rbx
    xor rcx, rcx
    xor rdx, rdx

    ; 2. Log FVS Handshake
    mov rax, 2          ; sys_open
    mov rdi, log_path
    mov rsi, 1089       ; O_CREAT|O_WRONLY|O_APPEND
    mov rdx, 0644o
    syscall
    mov rdi, rax
    mov rax, 1          ; sys_write
    mov rsi, msg
    mov rdx, len
    syscall

    ; 3. Exit
    mov rax, 60
    xor rdi, rdi
    syscall

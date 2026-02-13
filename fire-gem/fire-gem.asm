section .data
    log_path db "fire-gem/fire-gem.log", 0
    msg      db "[AVIS-ASM] Identity: fire-gem-asm -> hello", 0xa
    len      equ $ - msg

section .text
    global _start

_start:
    ; Open log: O_CREAT (64) | O_WRONLY (1) | O_APPEND (1024) = 1089
    mov rax, 2          ; sys_open
    mov rdi, log_path
    mov rsi, 1089       ; Append mode
    mov rdx, 0644o
    syscall
    
    ; Save File Descriptor and Write
    mov rdi, rax        
    mov rax, 1          ; sys_write
    mov rsi, msg
    mov rdx, len
    syscall

    ; Exit
    mov rax, 60         ; sys_exit
    xor rdi, rdi
    syscall


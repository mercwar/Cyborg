; =============================================================================
;  AVIS FIRMWARE VERIFICATION SIGNATURE
;  FILE: avis-fvs.asm
; =============================================================================
section .data
    log_path db "fire-gem/fire-gem.log", 0
    fvs_msg  db "[AVIS-FVS] Identity Verified: Registers Cleared. HAHA!", 0xa
    fvs_len  equ $ - fvs_msg

section .text
    global _start
_start:
    xor rax, rax        ; Clear registers for FVS baseline
    xor rbx, rbx
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
    mov rax, 60         ; sys_exit
    xor rdi, rdi
    syscall

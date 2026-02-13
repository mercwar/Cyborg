; =============================================================================
;  AVIS MACRO STUB
;  FILE: fire-macro.asm
; =============================================================================
section .data
    site_script db "fire-gem/fire-site.sh", 0
    msg_bot     db "[AVIS-MACRO] Little Bot calling fire-site.sh...", 0xa
    len_bot     equ $ - msg_bot

section .text
    global _start
_start:
    ; 1. Log intent to stdout (GitHub Console)
    mov rax, 1
    mov rdi, 1
    mov rsi, msg_bot
    mov rdx, len_bot
    syscall

    ; 2. Execute the sitemap logic
    mov rax, 59             ; sys_execve
    mov rdi, site_script
    xor rsi, rsi
    xor rdx, rdx
    syscall

    ; 3. Exit
    mov rax, 60
    xor rdi, rdi
    syscall

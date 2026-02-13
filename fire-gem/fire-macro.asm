; =============================================================================
;  AVIS MACRO STUB
;  FILE: fire-macro.asm
; =============================================================================
section .data
    log_path db "fire-gem/fire-gem.log", 0
    ; Matches the message defined in [AVIS_MACRO_CONFIG]
    macro_msg db "[AVIS-MACRO] hello from the macro.ini", 0xa
    macro_len equ $ - macro_msg

section .text
    global _start

_start:
    ; 1. Open Log in Append Mode
    mov rax, 2          ; sys_open
    mov rdi, log_path
    mov rsi, 1089       ; O_CREAT | O_WRONLY | O_APPEND
    mov rdx, 0644o
    syscall
    mov r8, rax         ; Store FD

    ; 2. Inject Macro Handshake
    mov rax, 1          ; sys_write
    mov rdi, r8
    mov rsi, macro_msg
    mov rdx, macro_len
    syscall

    ; 3. Exit back to Sequential Loader
    mov rax, 60
    xor rdi, rdi
    syscall

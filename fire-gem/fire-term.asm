; =============================================================
;  AVIS TERMINAL SURFACE CONTROLLER
;  FILE: fire-term.asm
; =============================================================

section .data
    term_hdr db "--- AVIS TERMINAL SURFACE ENGAGED ---", 0xa
    term_len equ $ - term_hdr
    term_msg db "[AVIS-TERM] Initializing Surface Interface...", 0xa
    msg_len  equ $ - term_msg

section .text
    global _start
    extern FIRE_LOG_STRIKE  ; Calling our modular log object

_start:
    ; 1. LOG TO THE FILE (MODULAR OBJECT)
    lea rdi, [term_msg]
    mov rsi, msg_len
    call FIRE_LOG_STRIKE

    ; 2. STRIKE THE GITHUB SURFACE (STDOUT)
    ; This makes the terminal 'visible' in the GitHub UI
    mov rax, 1          ; sys_write
    mov rdi, 1          ; stdout
    mov rsi, term_hdr
    mov rdx, term_len
    syscall

    ; 3. EXIT
    mov rax, 60
    xor rdi, rdi
    syscall

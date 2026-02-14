; =============================================================
;  AVIS MASTER ENGINE [REVISED]
;  FILE: fire-gem.asm
; =============================================================

section .data
    msg_ignite db "[AVIS-CORE] Ignition: Log Object Active. HAHA!", 0xa
    len_ignite equ $ - msg_ignite

section .text
    global _start
    extern FIRE_LOG_STRIKE  ; The modular entry point

_start:
    ; --- CALL MODULAR LOG OBJECT ---
    lea rdi, [msg_ignite]
    mov rsi, len_ignite
    call FIRE_LOG_STRIKE

    ; --- PROCEED TO CBORD CHAIN ---
    ; [SEED -> SPEC -> MACRO]
    
    mov rax, 60
    xor rdi, rdi
    syscall

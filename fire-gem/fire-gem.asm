; =============================================================
;  AVIS MASTER ENGINE (Revised for Log Object)
;  FILE: fire-gem.asm
; =============================================================

section .data
    msg_boot db "[AVIS-CORE] Ignition Sequence Started. HAHA!", 0xa
    len_boot equ $ - msg_boot

section .text
    global _start
    extern AVIS_LOG_STRIKE  ; Import the new Log Object

_start:
    ; --- 1. CALL THE LOG OBJECT ---
    lea rdi, [msg_boot]     ; Load string address
    mov rsi, len_boot       ; Load string length
    call AVIS_LOG_STRIKE    ; Strike the log via the object

    ; --- 2. CONTINUE TO SEED/SPEC ---
    ; (Rest of the macro-logic)

    mov rax, 60
    xor rdi, rdi
    syscall


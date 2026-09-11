; ============================================================
; FIRE-LOG.ASM — Modular Log Object [AVIS-Law Compliant]
; ============================================================

section .data
    log_path db "fire-gem/fire-gem.log", 0

section .text
    global FIRE_LOG_STRIKE

; ------------------------------------------------------------
; FIRE_LOG_STRIKE
; RDI = Pointer to String | RSI = Length
; ------------------------------------------------------------
FIRE_LOG_STRIKE:
    push rbp
    mov rbp, rsp

    ; 1. Open Log (O_APPEND)
    mov rax, 2          ; sys_open
    mov rdi, log_path
    mov rsi, 1089       ; O_CREAT|O_WRONLY|O_APPEND
    mov rdx, 0644o
    syscall
    mov r12, rax        ; r12 = FD

    ; 2. Strike String to Disk
    mov rdx, rsi        ; Length
    mov rsi, rdi        ; Buffer
    mov rdi, r12
    mov rax, 1          ; sys_write
    syscall

    ; 3. Close
    mov rax, 3
    mov rdi, r12
    syscall

    leave
    ret

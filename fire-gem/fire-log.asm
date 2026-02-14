; =============================================================
;  AVIS LOG OBJECT
;  FILE: fire-log.asm
;  PURPOSE: Stable Entry Point for all AVIS Modules
; =============================================================

section .data
    log_path db "fire-gem/fire-gem.log", 0

section .text
    global AVIS_LOG_STRIKE

; -------------------------------------------------------------
; AVIS_LOG_STRIKE
; Expects: RDI = Pointer to Null-Terminated String
;          RSI = Length of String
; -------------------------------------------------------------
AVIS_LOG_STRIKE:
    push rbp
    mov rbp, rsp
    push rdi            ; Save string pointer
    push rsi            ; Save length

    ; 1. OPEN LOG (O_APPEND)
    mov rax, 2          ; sys_open
    mov rdi, log_path
    mov rsi, 1089       ; O_CREAT|O_WRONLY|O_APPEND
    mov rdx, 0644o
    syscall
    mov r12, rax        ; r12 = FD

    ; 2. WRITE MESSAGE
    pop rdx             ; Restore length to RDX
    pop rsi             ; Restore string pointer to RSI
    mov rax, 1          ; sys_write
    mov rdi, r12
    syscall

    ; 3. CLOSE
    mov rax, 3          ; sys_close
    mov rdi, r12
    syscall

    leave
    ret

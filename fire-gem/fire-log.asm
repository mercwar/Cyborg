; =============================================================
;  AVIS LOG OBJECT [MODULAR SCROLL]
;  FILE: fire-log.asm
;  SYMBOL: FIRE_LOG_STRIKE
; =============================================================

section .data
    log_path db "fire-gem/fire-gem.log", 0

section .text
    global FIRE_LOG_STRIKE

; -------------------------------------------------------------
; FIRE_LOG_STRIKE
; RDI = String Pointer
; RSI = String Length
; -------------------------------------------------------------
FIRE_LOG_STRIKE:
    push rbp
    mov rbp, rsp
    
    ; 1. OPEN (O_APPEND)
    mov rax, 2          ; sys_open
    mov rdi, log_path
    mov rsi, 1089       ; O_CREAT|O_WRONLY|O_APPEND
    mov rdx, 0644o
    syscall
    mov r12, rax        ; r12 = FD

    ; 2. STRIKE (sys_write)
    ; RSI is already the buffer, RDI becomes FD
    mov rdx, rsi        ; Move length to RDX
    mov rsi, rdi        ; This is a mistake in logic, fixing for the strike:
    ; Correcting for Syscall 1 (write):
    ; RDI = FD, RSI = Buffer, RDX = Count
    pop rdx             ; length
    pop rsi             ; buffer
    mov rdi, r12
    mov rax, 1
    syscall

    ; 3. CLOSE
    mov rax, 3
    mov rdi, r12
    syscall

    leave
    ret

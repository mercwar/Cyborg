; =============================================================================
;  AVIS MASTER ENGINE (Dynamic INI Loader)
;  FILE: fire-gem.asm
; =============================================================================

section .data
    ini_path    db "fire-gem/fire-macro.ini", 0
    key_target  db "fire_seed=", 0
    key_len     equ 10
    log_path    db "fire-gem/fire-gem.log", 0
    msg_engine  db "[AVIS-ENGINE] Parsing Macro INI...", 0xa
    msg_len     equ $ - msg_engine

section .bss
    buffer      resb 2048   ; Buffer for INI data
    target_path resb 128    ; Extracted binary path

section .text
    global _start

_start:
    ; --- 1. LOG ENGINE START ---
    mov rax, 2          ; sys_open
    mov rdi, log_path
    mov rsi, 1089       ; O_CREAT | O_WRONLY | O_APPEND
    mov rdx, 0644o
    syscall
    mov rdi, rax
    mov rax, 1          ; sys_write
    mov rsi, msg_engine
    mov rdx, msg_len
    syscall

    ; --- 2. OPEN & READ INI ---
    mov rax, 2          ; sys_open
    mov rdi, ini_path
    mov rsi, 0          ; O_RDONLY
    syscall
    mov r12, rax

    mov rax, 0          ; sys_read
    mov rdi, r12
    mov rsi, buffer
    mov rdx, 2048
    syscall

    ; --- 3. DYNAMIC HANDOFF ---
    ; (Handoff logic executes binaries built by fire-begin.sh)
    mov rax, 60
    xor rdi, rdi
    syscall


; =============================================================================
;  AVIS VAULT ARCHITECT [FINAL HIGH-PRECISION STRIKE]
;  FILE: fire-end.asm
;  PURPOSE: Kill the 00000000 glitch and seal the archive forever.
; =============================================================================

section .data
    log_dir  db "fire-gem/fire-log", 0
    old_name db "fire-gem/fire-gem.log", 0
    prefix   db "fire-gem/fire-log/fire-log-", 0
    ext      db ".avis", 0
    msg_sync db "[SYNC] High-Precision Seal: COMPLETE. HAHA!", 0xa

section .bss
    new_name resb 128
    tv       resq 2      ; timeval struct: [seconds, microseconds]

section .text
    global _start

_start:
    ; --- 1. FORCE DIRECTORY AUTHORITY ---
    mov rax, 83         ; sys_mkdir
    mov rdi, log_dir
    mov rsi, 0755o
    syscall

    ; --- 2. FINAL LOG INJECTION ---
    mov rax, 2          ; sys_open
    mov rdi, old_name
    mov rsi, 1089       ; O_CREAT|O_WRONLY|O_APPEND
    mov rdx, 0644o
    syscall
    mov r15, rax

    mov rax, 1          ; sys_write
    mov rdi, r15
    mov rsi, msg_sync
    mov rdx, 42
    syscall

    ; --- 3. FORCE DISK FLUSH ---
    mov rax, 74         ; sys_fsync
    mov rdi, r15
    syscall

    mov rax, 3          ; sys_close
    mov rdi, r15
    syscall

    ; --- 4. THE TIME STRIKE (sys_gettimeofday) ---
    mov rax, 96         ; sys_gettimeofday
    lea rdi, [tv]       ; Pointer to our struct
    xor rsi, rsi        ; TZ = NULL
    syscall

    ; --- 5. CONSTRUCT DYNAMIC FILENAME ---
    lea rdi, [new_name]
    lea rsi, [prefix]
.copy_pre:
    lodsb
    test al, al
    jz .load_seconds
    stosb
    jmp .copy_pre

.load_seconds:
    mov rax, [tv]       ; LOAD ACTUAL SECONDS FROM MEMORY
    
    ; Convert 64-bit RAX to Hex ASCII
    mov rcx, 16         ; Full 64-bit spread
.hex_loop:
    rol rax, 4
    mov rbx, rax
    and rbx, 0x0F
    cmp bl, 10
    jl .digit
    add bl, 7           ; Hex 'A'-'F'
.digit:
    add bl, '0'
    mov [rdi], bl
    inc rdi
    loop .hex_loop

    ; Add Extension
    lea rsi, [ext]
.copy_ext:
    lodsb
    test al, al
    jz .do_rename
    stosb
    jmp .copy_ext

.do_rename:
    mov byte [rdi], 0

    ; --- 6. HARDWARE MIGRATION ---
    mov rax, 82         ; sys_rename
    mov rdi, old_name
    lea rsi, [new_name]
    syscall

    ; --- 7. EXIT ---
    mov rax, 60
    xor rdi, rdi
    syscall

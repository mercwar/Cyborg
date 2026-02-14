; =============================================================================
;  AVIS VAULT ARCHITECT [FINAL TIME-STRIKE]
;  FILE: fire-end.asm
; =============================================================================

section .data
    log_dir  db "fire-gem/fire-log", 0
    old_name db "fire-gem/fire-gem.log", 0
    prefix   db "fire-gem/fire-log/fire-log-", 0
    ext      db ".avis", 0

section .bss
    new_name resb 128
    tv       resq 2      ; Timeval struct (seconds, microseconds)

section .text
    global _start

_start:
    ; --- 1. CREATE VAULT ---
    mov rax, 83         ; sys_mkdir
    mov rdi, log_dir
    mov rsi, 0755o
    syscall

    ; --- 2. GET HIGH-PRECISION TIME (sys_gettimeofday) ---
    mov rax, 96         ; sys_gettimeofday
    lea rdi, [tv]       ; Pointer to timeval
    xor rsi, rsi        ; NULL timezone
    syscall

    ; --- 3. CONSTRUCT DYNAMIC NAME ---
    lea rdi, [new_name]
    
    ; Copy Prefix
    lea rsi, [prefix]
.copy_pre:
    lodsb
    test al, al
    jz .load_time
    stosb
    jmp .copy_pre

.load_time:
    mov rax, [tv]       ; Load the SECONDS into RAX for hex conversion
    
    ; Convert RAX to Hex ASCII (16 chars)
    mov rcx, 16
.hex_loop:
    rol rax, 4
    mov rbx, rax
    and rbx, 0x0F
    add bl, 0x30
    cmp bl, 0x39
    jle .store
    add bl, 7           ; Hex 'A'-'F' adjustment
.store:
    mov [rdi], bl
    inc rdi
    loop .hex_loop

    ; Copy Extension
    lea rsi, [ext]
.copy_ext:
    lodsb
    test al, al
    jz .finalize
    stosb
    jmp .copy_ext

.finalize:
    mov byte [rdi], 0

    ; --- 4. HARDWARE RENAME ---
    mov rax, 82         ; sys_rename
    mov rdi, old_name
    lea rsi, [new_name]
    syscall

    ; --- 5. EXIT ---
    mov rax, 60
    xor rdi, rdi
    syscall

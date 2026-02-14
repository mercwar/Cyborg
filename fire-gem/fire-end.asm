; =============================================================================
;  AVIS VAULT ARCHITECT [FIXED NAME ENGINE]
;  FILE: fire-end.asm
; =============================================================================

section .data
    log_dir  db "fire-gem/fire-log", 0
    old_name db "fire-gem/fire-gem.log", 0
    prefix   db "fire-gem/fire-log/fire-log-", 0
    ext      db ".avis", 0
    msg_sync db "[SYNC] Vault Sealed & Named. HAHA!", 0xa

section .bss
    new_name resb 128

section .text
    global _start

_start:
    ; --- 1. CREATE VAULT ---
    mov rax, 83         ; sys_mkdir
    mov rdi, log_dir
    mov rsi, 0755o
    syscall             ; EEXIST is ignored

    ; --- 2. FINAL LOG ENTRY ---
    mov rax, 2          ; sys_open
    mov rdi, old_name
    mov rsi, 1089       ; O_CREAT|WRONLY|APPEND
    mov rdx, 0644o
    syscall
    mov r15, rax

    mov rax, 1          ; sys_write
    mov rdi, r15
    mov rsi, msg_sync
    mov rdx, 36
    syscall

    mov rax, 3          ; sys_close
    mov rdi, r15
    syscall

    ; --- 3. GET TIME & CONSTRUCT NAME ---
    mov rax, 201        ; sys_time
    xor rdi, rdi
    syscall             ; RAX = Unix Epoch

    lea rdi, [new_name]
    
    ; Copy Prefix
    lea rsi, [prefix]
.copy_pre:
    lodsb
    test al, al
    jz .do_hex
    stosb
    jmp .copy_pre

.do_hex:
    ; Convert RAX to Hex ASCII
    mov rcx, 8          ; 8 bytes
.hex_loop:
    rol rax, 4
    mov rbx, rax
    and rbx, 0x0F
    cmp bl, 10
    jl .is_digit
    add bl, 7           ; Adjust for 'A'-'F'
.is_digit:
    add bl, '0'
    mov [rdi], bl
    inc rdi
    loop .hex_loop

    ; Copy Extension
    lea rsi, [ext]
.copy_ext:
    lodsb
    test al, al
    jz .apply_rename
    stosb
    jmp .copy_ext

.apply_rename:
    mov byte [rdi], 0   ; NULL

    ; --- 4. HARDWARE RENAME ---
    mov rax, 82         ; sys_rename
    mov rdi, old_name
    lea rsi, [new_name]
    syscall

    ; --- 5. EXIT ---
    mov rax, 60
    xor rdi, rdi
    syscall

; =============================================================================
;  AVIS VAULT ARCHITECT
;  FILE: fire-end.asm
;  PURPOSE: Create /fire-log/ and migrate log via sys_mkdir & sys_rename
; =============================================================================

section .data
    log_dir  db "fire-gem/fire-log", 0
    old_name db "fire-gem/fire-gem.log", 0
    ; Final path: fire-gem/fire-log/fire-log-[HEX].avis
    prefix   db "fire-gem/fire-log/fire-log-", 0
    ext      db ".avis", 0
    msg_sync db "[SYNC] Creating Vault and Migrating Log. HAHA!", 0xa

section .bss
    new_name resb 128

section .text
    global _start

_start:
    ; --- 1. CREATE THE VAULT DIRECTORY ---
    ; sys_mkdir(log_dir, 0755o)
    mov rax, 83         ; sys_mkdir
    mov rdi, log_dir
    mov rsi, 0755o      ; Standard permissions
    syscall             ; If it exists, it returns -17 (EEXIST), which we ignore

    ; --- 2. FINAL LOG ENTRY ---
    mov rax, 2          ; sys_open
    mov rdi, old_name
    mov rsi, 1089       ; O_CREAT|O_WRONLY|O_APPEND
    mov rdx, 0644o
    syscall
    mov r15, rax

    mov rax, 1          ; sys_write
    mov rdi, r15
    mov rsi, msg_sync
    mov rdx, 45
    syscall

    mov rax, 3          ; sys_close
    mov rdi, r15
    syscall

    ; --- 3. GENERATE DYNAMIC PATH ---
    mov rax, 201        ; sys_time
    xor rdi, rdi
    syscall             ; RAX = Timestamp

    lea rdi, [new_name]
    lea rsi, [prefix]
.copy_pre:
    lodsb
    test al, al
    jz .add_hex
    stosb
    jmp .copy_pre

.add_hex:
    ; [Hex conversion logic for RAX timestamp into RDI]
    ; ... (as implemented in previous dynamic version) ...

    lea rsi, [ext]
.copy_ext:
    lodsb
    test al, al
    jz .do_rename
    stosb
    jmp .copy_ext

.do_rename:
    mov byte [rdi], 0

    ; --- 4. HARDWARE MIGRATION ---
    mov rax, 82         ; sys_rename
    mov rdi, old_name
    lea rsi, [new_name]
    syscall

    ; --- 5. EXIT ---
    mov rax, 60
    xor rdi, rdi
    syscall

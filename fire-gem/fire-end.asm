; =============================================================================
;  AVIS TERMINAL MIGRATOR
;  FILE: fire-end.asm
; =============================================================================

section .data
    old_name db "fire-gem/fire-gem.log", 0
    ; For the demo, we use a fixed timestamp-placeholder. 
    ; In a full FVS, this is generated dynamically.
    new_name db "fire-gem/fire-log-02-13-2025-2359.avis", 0
    
    sync_msg db "[SYNC] Migrating Log to Archive... HAHA!", 0xa
    sync_len equ $ - sync_msg

section .text
    global _start

_start:
    ; --- 1. FINAL SYNC WRITE ---
    mov rax, 2          ; sys_open
    mov rdi, old_name
    mov rsi, 1089       ; O_CREAT|O_WRONLY|O_APPEND
    mov rdx, 0644o
    syscall
    mov r15, rax

    mov rax, 1          ; sys_write
    mov rdi, r15
    mov rsi, sync_msg
    mov rdx, sync_len
    syscall

    ; --- 2. CLOSE BEFORE RENAME ---
    mov rax, 3          ; sys_close
    mov rdi, r15
    syscall

    ; --- 3. HARDWARE MIGRATION (sys_rename) ---
    ; rax = 82, rdi = oldname, rsi = newname
    mov rax, 82         
    mov rdi, old_name
    mov rsi, new_name
    syscall

    ; --- 4. KERNEL EXIT ---
    mov rax, 60
    xor rdi, rdi
    syscall

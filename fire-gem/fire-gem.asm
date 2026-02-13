; fire-gem.asm - Core Loader with Debug Logging
section .data
    ; Paths
    log_path    db "fire-gem/fire-gem.log", 0
    sh_loader   db "fire-gem/fire-gem.sh", 0
    
    ; Logging Messages
    msg_init    db "[AVIS] Starting fire-gem.asm...", 0xa
    msg_err_log db "[CRITICAL] Cannot open fire-gem.log", 0xa
    msg_sh_exec db "[AVIS] Handing off to fire-gem.sh", 0xa
    
    ; Argv for fire-gem.sh
    arg0        db "fire-gem.sh", 0
    argv        dq arg0, 0
    envp        dq 0

section .text
    global _start

_start:
    ; --- 1. OPEN LOG (fire-gem/fire-gem.log) ---
    ; sys_open flags: O_CREAT (0x40) | O_WRONLY (0x1) | O_APPEND (0x400) = 0x441
    mov rax, 2          ; sys_open
    mov rdi, log_path
    mov rsi, 0x441      ; O_CREAT | O_WRONLY | O_APPEND
    mov rdx, 0666o      ; Permissions
    syscall
    
    ; Verify file descriptor (negative = error)
    test rax, rax
    js .log_error_fallback
    mov r15, rax        ; Store Log FD in r15

    ; --- 2. LOG INITIALIZATION ---
    mov rax, 1          ; sys_write
    mov rdi, r15
    mov rsi, msg_init
    mov rdx, 33
    syscall

    ; --- 3. LOG BASH HANDOFF ---
    mov rax, 1
    mov rdi, r15
    mov rsi, msg_sh_exec
    mov rdx, 33
    syscall

    ; --- 4. EXECUTE fire-gem.sh ---
    mov rax, 59         ; sys_execve
    mov rdi, sh_loader
    mov rsi, argv
    mov rdx, envp
    syscall

    ; If execve returns, it failed
    jmp .exit

.log_error_fallback:
    ; Write error message to STDERR (FD 2) if log file failed
    mov rax, 1          ; sys_write
    mov rdi, 2          ; STDERR
    mov rsi, msg_err_log
    mov rdx, 35
    syscall

.exit:
    mov rax, 60         ; sys_exit
    xor rdi, rdi
    syscall

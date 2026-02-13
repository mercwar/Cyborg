; fire-gem.asm
section .data
    ; Use a leading dot to ensure relative pathing is explicit
    log_path    db "./fire-gem/fire-gem.log", 0
    
    msg_init    db "[AVIS] START: Loading fire-gem.sh", 0xa
    msg_len     equ $ - msg_init
    
    msg_err     db "[ERROR] Could not open log file", 0xa
    err_len     equ $ - msg_err

section .text
    global _start

_start:
    ; --- 1. OPEN LOG ---
    ; Flags: O_CREAT(64) | O_WRONLY(1) | O_APPEND(1024) | O_SYNC(1048576)
    ; Total = 1050049 (0x100441)
    mov rax, 2          ; sys_open
    mov rdi, log_path
    mov rsi, 0x100441   ; Synchronous Append mode
    mov rdx, 0666o      ; Read/Write permissions
    syscall
    
    ; Check if open failed (RAX < 0)
    cmp rax, 0
    jl .emergency_exit

    mov r15, rax        ; Store FD in r15

    ; --- 2. FORCE WRITE ---
    mov rax, 1          ; sys_write
    mov rdi, r15        ; Use the Log FD
    mov rsi, msg_init
    mov rdx, msg_len
    syscall

    ; --- 3. FSYNC (Force Disk Commit) ---
    mov rax, 74         ; sys_fsync
    mov rdi, r15
    syscall

    ; --- 4. CLOSE & EXIT ---
    mov rax, 3          ; sys_close
    mov rdi, r15
    syscall

    mov rax, 60         ; sys_exit
    xor rdi, rdi
    syscall

.emergency_exit:
    ; If the log failed, print error to your actual terminal (FD 1)
    mov rax, 1
    mov rdi, 1          ; stdout
    mov rsi, msg_err
    mov rdx, err_len
    syscall
    
    mov rax, 60
    mov rdi, 1          ; Exit code 1 (Error)
    syscall

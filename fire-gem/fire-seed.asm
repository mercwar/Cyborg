section .data
    log_path db "fire-gem/fire-gem.log", 0
    msg      db "[AVIS] DEPLOYMENT SUCCESS", 0xa
    msg_len  equ $ - msg

section .text
    global _start

_start:
    ; --- 1. OPEN LOG ---
    mov rax, 2          ; sys_open
    lea rdi, [rel log_path] ; Use relative addressing for safety
    mov rsi, 65         ; O_CREAT (64) | O_WRONLY (1)
    mov rdx, 0666o      ; Permissions
    syscall
    
    ; --- 2. VALIDATE FD ---
    test rax, rax
    js .fail            ; If RAX < 0, open failed
    mov r8, rax         ; Move FD to r8 (callee-saved-ish)

    ; --- 3. WRITE TO LOG ---
    mov rax, 1          ; sys_write
    mov rdi, r8         ; rdi = the log's file descriptor
    lea rsi, [rel msg]  ; rsi = address of the string
    mov rdx, msg_len    ; rdx = length
    syscall

    ; --- 4. CLOSE & EXIT ---
    mov rax, 3          ; sys_close
    mov rdi, r8
    syscall
    jmp .exit

.fail:
    mov rdi, 1          ; Exit with error code 1
    jmp .finish

.exit:
    xor rdi, rdi        ; Exit with code 0

.finish:
    mov rax, 60         ; sys_exit
    syscall

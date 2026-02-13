section .data
    log_path db "fire-gem/fire-gem.log", 0
    msg      db "[AVIS] DEPLOYMENT SUCCESS: mercwar", 0xa
    len      equ $ - msg

section .text
    global _start

_start:
    ; OPEN LOG WITH TRUNCATE
    ; Flags: O_CREAT (64) | O_WRONLY (1) | O_TRUNC (512) = 577
    mov rax, 2          ; sys_open
    mov rdi, log_path
    mov rsi, 577        ; This clears the old log every run
    mov rdx, 0666o
    syscall

    
    ; 2. If open worked, write to file
    test rax, rax
    js .write_stdout    ; If log fails, jump to stdout
    
    mov rdi, rax        ; FD from open
    mov rax, 1          ; sys_write
    mov rsi, msg
    mov rdx, len
    syscall

.write_stdout:
    ; 3. Write to STDOUT regardless (for GitHub Actions console)
    mov rax, 1          ; sys_write
    mov rdi, 1          ; STDOUT
    mov rsi, msg
    mov rdx, len
    syscall

    ; 4. Exit
    mov rax, 60
    xor rdi, rdi
    syscall

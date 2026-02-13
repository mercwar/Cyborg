section .data
    ; Specific log path
    log_path    db "fire-gem/fire-gem.log", 0
    
    ; Environment Tree Paths
    dir1        db "dir-1", 0
    file_a      db "dir-1/file-a", 0
    
    ; Log entries
    log_init    db "[STATUS] Engine engaged. Target: fire-gem.bin", 0xa
    log_mkdir   db "[ACTION] mkdir dir-1 initiated", 0xa
    log_deploy  db "[ACTION] <copy file> file-a success", 0xa
    log_done    db "[FINISH] Environment tree deployed.", 0xa

section .text
    global _start

_start:
    ; --- 1. OPEN THE LOG ---
    ; sys_open("fire-gem/fire-gem.log", O_CREAT | O_WRONLY | O_APPEND, 0666)
    mov rax, 2
    mov rdi, log_path
    mov rsi, 1089       ; O_CREAT | O_WRONLY | O_APPEND
    mov rdx, 0666o
    syscall
    mov r15, rax        ; Store Log FD in r15 for the duration

    ; Write Init to Log
    mov rax, 1
    mov rdi, r15
    mov rsi, log_init
    mov rdx, 46
    syscall

    ; --- 2. EXECUTE KB TREE ---
    ; mkdir dir-1
    mov rax, 83         ; sys_mkdir
    mov rdi, dir1
    mov rsi, 0755o
    syscall
    
    ; Log mkdir action
    mov rax, 1
    mov rdi, r15
    mov rsi, log_mkdir
    mov rdx, 31
    syscall

    ; --- 3. <COPY FILE> file-a ---
    ; Create file-a
    mov rax, 2          ; sys_open
    mov rdi, file_a
    mov rsi, 65         ; O_CREAT | O_WRONLY
    mov rdx, 0755o
    syscall
    mov rbx, rax        ; rbx = file_a FD

    ; Log deployment
    mov rax, 1
    mov rdi, r15
    mov rsi, log_deploy
    mov rdx, 38
    syscall

    ; Close file_a
    mov rax, 3
    mov rdi, rbx
    syscall

    ; --- 4. FINAL LOG & EXIT ---
    mov rax, 1
    mov rdi, r15
    mov rsi, log_done
    mov rdx, 36
    syscall

    ; Close log
    mov rax, 3
    mov rdi, r15
    syscall

    mov rax, 60
    xor rdi, rdi
    syscall

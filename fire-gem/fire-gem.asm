section .data
    ; Command 1: nasm -f elf64 fire-seed.asm -o fire-seed.o
    nasm_path db '/usr/bin/nasm', 0
    arg1_0    db 'nasm', 0
    arg1_1    db '-f', 0
    arg1_2    db 'elf64', 0
    arg1_3    db 'fire-seed.asm', 0
    arg1_4    db '-o', 0
    arg1_5    db 'fire-seed.o', 0
    args1     dq arg1_0, arg1_1, arg1_2, arg1_3, arg1_4, arg1_5, 0

    ; Command 2: ld fire-seed.o -o fire-seed
    ld_path   db '/usr/bin/ld', 0
    arg2_0    db 'ld', 0
    arg2_1    db 'fire-seed.o', 0
    arg2_2    db '-o', 0
    arg2_3    db 'fire-seed', 0
    args2     dq arg2_0, arg2_1, arg2_2, arg2_3, 0

    ; Command 3: ./fire-seed
    run_path  db './fire-seed', 0
    args3     dq run_path, 0

    env       dq 0 ; Empty environment variables

section .text
    global _start

_start:
    ; --- Step 1: Call NASM ---
    mov rax, 57         ; sys_fork
    syscall
    cmp rax, 0
    jne wait_1          ; Parent waits
    mov rax, 59         ; sys_execve
    mov rdi, nasm_path
    mov rsi, args1
    mov rdx, env
    syscall
wait_1:
    mov rax, 61         ; sys_wait4
    mov rdi, -1
    xor rsi, rsi
    xor rdx, rdx
    xor r10, r10
    syscall

    ; --- Step 2: Call LD ---
    mov rax, 57         ; sys_fork
    syscall
    cmp rax, 0
    jne wait_2
    mov rax, 59         ; sys_execve
    mov rdi, ld_path
    mov rsi, args2
    mov rdx, env
    syscall
wait_2:
    mov rax, 61         ; sys_wait4
    mov rdi, -1
    xor rsi, rsi
    xor rdx, rdx
    xor r10, r10
    syscall

    ; --- Step 3: Run fire-seed ---
    mov rax, 59         ; sys_execve
    mov rdi, run_path
    mov rsi, args3
    mov rdx, env
    syscall

    ; Exit
    mov rax, 60
    xor rdi, rdi
    syscall

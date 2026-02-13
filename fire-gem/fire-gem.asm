; =============================================================================
;  AVIS MASTER ENGINE
;  FILE: fire-gem.asm
;  PURPOSE: Parse fire-gem.ini and execute the dynamic seed target
; =============================================================================

section .data
    ini_path    db "fire-gem/fire-gem.ini", 0
    search_key  db "fire_seed=", 0
    key_len     equ 10

section .bss
    buffer      resb 2048   ; Buffer for INI reading
    exec_target resb 128    ; Buffer for extracted filename

section .text
    global _start

_start:
    ; --- 1. OPEN INI ---
    mov rax, 2              ; sys_open
    mov rdi, ini_path
    mov rsi, 0              ; O_RDONLY
    syscall
    mov r12, rax            ; Store FD

    ; --- 2. READ CONTENT ---
    mov rax, 0              ; sys_read
    mov rdi, r12
    mov rsi, buffer
    mov rdx, 2048
    syscall

    ; --- 3. PARSE FOR fire_seed= ---
    lea rsi, [buffer]
.find_loop:
    mov rdi, search_key
    mov rcx, key_len
    push rsi
    repe cmpsb              ; Check if we found the key
    pop rsi
    je .found
    inc rsi
    jmp .find_loop

.found:
    add rsi, key_len        ; Skip the "fire_seed=" string
    lea rdi, [exec_target]
.copy:
    mov al, [rsi]
    cmp al, 0xa             ; Stop at newline
    je .done
    mov [rdi], al
    inc rsi
    inc rdi
    jmp .copy
.done:
    mov byte [rdi], 0       ; Null terminator for syscall

    ; --- 4. DYNAMIC EXECUTION ---
    ; sys_execve(exec_target, argv, envp)
    mov rax, 59             ; sys_execve
    lea rdi, [exec_target]
    xor rsi, rsi            ; No argv
    xor rdx, rdx            ; No envp
    syscall

    ; --- EXIT IF EXECVE FAILS ---
    mov rax, 60
    mov rdi, 1
    syscall



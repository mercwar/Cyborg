; =============================================================================
;  AVIS MACRO STUB (Flag-Aware)
;  FILE: fire-macro.asm
; =============================================================================
section .data
    ini_path    db "fire-gem/fire-macro.ini", 0
    site_script db "fire-gem/fire-site.sh", 0
    flag_key    db "sitemap_flag=1", 0
    flag_len    equ 14
    msg_run     db "[AVIS-MACRO] Flag: 1. Launching fire-site.sh...", 0xa
    msg_skip    db "[AVIS-MACRO] Flag: 0. Skipping Sitemap Generation.", 0xa

section .bss
    buffer      resb 2048

section .text
    global _start

_start:
    ; 1. OPEN AND READ MACRO INI
    mov rax, 2          ; sys_open
    mov rdi, ini_path
    mov rsi, 0          ; O_RDONLY
    syscall
    mov r12, rax        ; r12 = FD

    mov rax, 0          ; sys_read
    mov rdi, r12
    mov rsi, buffer
    mov rdx, 2048
    syscall

    ; 2. SCAN BUFFER FOR FLAG
    lea rsi, [buffer]
    mov rcx, 2048
.find:
    lea rdi, [flag_key]
    push rcx
    mov rcx, flag_len
    repe cmpsb          ; Compare current pointer to "sitemap_flag=1"
    pop rcx
    je .trigger
    inc rsi
    loop .find

    ; 3. SKIP LOGIC
    mov rax, 1
    mov rdi, 1
    mov rsi, msg_skip
    mov rdx, 48
    syscall
    jmp .exit

.trigger:
    ; 4. EXECUTE fire-site.sh
    mov rax, 1
    mov rdi, 1
    mov rsi, msg_run
    mov rdx, 49
    syscall

    mov rax, 59         ; sys_execve
    mov rdi, site_script
    xor rsi, rsi
    xor rdx, rdx
    syscall

.exit:
    mov rax, 60
    xor rdi, rdi
    syscall

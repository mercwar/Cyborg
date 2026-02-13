; Cyborg/fire-gem/fire-seed.asm
; Author: mercwar
section .data
    ; Avis & KB Config
    bin_name    db "fire-gem.bin", 0
    
    ; Directory Tree (mkdir -p logic)
    dir1        db "dir-1", 0
    dir2        db "dir-2", 0
    dir2_sub    db "dir-2/sub-dir", 0

    ; <copy file> Targets
    file_a      db "dir-1/file-a", 0
    file_b      db "dir-1/file-b", 0
    file_c      db "dir-2/sub-dir/file-c", 0
    file_d      db "root-file-d", 0

    ; Base64 Packet (Test Payload)
    ; "hello" encoded as a placeholder for fire-gem.bin data
    packet      db "aGVsbG8K", 0 
    packet_len  equ $ - packet

section .text
    global _start

_start:
    ; --- 1. BUILD DIRECTORIES ---
    ; mkdir("dir-1")
    mov rax, 83         ; sys_mkdir
    mov rdi, dir1
    mov rsi, 0755o      ; permissions
    syscall

    ; mkdir("dir-2")
    mov rax, 83
    mov rdi, dir2
    syscall

    ; mkdir("dir-2/sub-dir")
    mov rax, 83
    mov rdi, dir2_sub
    syscall

    ; --- 2. DEPLOY FILES (<copy file> logic) ---
    ; Deploying file-a to dir-1
    mov rdi, file_a
    call create_and_write

    ; Deploying file-c to dir-2/sub-dir
    mov rdi, file_c
    call create_and_write

    ; --- 3. EXIT ---
    mov rax, 60         ; sys_exit
    xor rdi, rdi
    syscall

create_and_write:
    ; Open/Create File
    mov rax, 2          ; sys_open
    ; rdi is already set to filename
    mov rsi, 65         ; O_CREAT | O_WRONLY
    mov rdx, 0755o      ; chmod +x
    syscall
    
    ; Write Packet
    mov rdi, rax        ; fd
    mov rax, 1          ; sys_write
    mov rsi, packet     ; source_data
    mov rdx, packet_len
    syscall
    
    ; Close
    mov rax, 3          ; sys_close
    syscall
    ret

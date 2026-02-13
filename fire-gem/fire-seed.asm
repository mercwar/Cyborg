; fire-seed.asm - Deployment Engine for fire-gem environment
section .data
    ; Configuration from avis
    bin_file    db "fire-gem.bin", 0
    root_path   db "./fire_root", 0

    ; Directory Tree (nested mkdir logic)
    d1          db "dir-1", 0
    d2          db "dir-2", 0
    d2_sub      db "dir-2/sub-dir", 0

    ; File Targets (based on environment_tree)
    f_a         db "dir-1/file-a", 0
    f_b         db "dir-1/file-b", 0
    f_c         db "dir-2/sub-dir/file-c", 0
    f_d         db "root-file-d", 0

section .bss
    buffer      resb 1024  ; Buffer for decoding base64

section .text
    global _start

_start:
    ; --- Step 1: Create Directories (sys_mkdir 83) ---
    ; Emulating 'mkdir -p' from JSON install_commands
    mov rax, 83         ; sys_mkdir
    mov rdi, d1
    mov rsi, 0755o      ; Root authority permissions
    syscall

    mov rax, 83
    mov rdi, d2
    syscall

    mov rax, 83
    mov rdi, d2_sub
    syscall

    ; --- Step 2: Process Base64 Packets (sys_open 2) ---
    ; Open fire-gem.bin to read source_data
    mov rax, 2          ; sys_open
    mov rdi, bin_file
    mov rsi, 0          ; O_RDONLY
    syscall
    mov r12, rax        ; Store FD of bin in r12

    ; --- Step 3: Deploy file-a (Offset 0x00) ---
    ; Seek to offset defined in KB
    mov rax, 8          ; sys_lseek
    mov rdi, r12
    mov rsi, 0x00       ; source_offset for file-a
    mov rdx, 0          ; SEEK_SET
    syscall

    ; Read, Decode (Placeholder for base64 decode logic), and Write
    call deploy_file_a

    ; --- Step 4: Exit ---
    mov rax, 60         ; sys_exit
    xor rdi, rdi
    syscall

deploy_file_a:
    ; Read from source_data
    mov rax, 0          ; sys_read
    mov rdi, r12
    mov rsi, buffer
    mov rdx, 1024
    syscall

    ; Create target file (sys_open with O_CREAT)
    mov rax, 2
    mov rdi, f_a
    mov rsi, 65         ; O_CREAT | O_WRONLY
    mov rdx, 0755o      ; Apply chmod +x authority
    syscall
    
    ; Write decoded content (sys_write)
    mov rdi, rax
    mov rax, 1
    mov rsi, buffer
    mov rdx, 1024
    syscall
    ret

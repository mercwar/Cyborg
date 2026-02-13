section .data
    ; Paths from your environment_tree
    bin_source  db "fire-gem.bin", 0
    
    dir_1       db "dir-1", 0
    dir_2       db "dir-2", 0
    dir_2_sub   db "dir-2/sub-dir", 0
    
    file_a      db "dir-1/file-a", 0
    file_b      db "dir-1/file-b", 0
    file_c      db "dir-2/sub-dir/file-c", 0
    file_d      db "root-file-d", 0

section .bss
    buffer resb 64  ; Buffer to hold decoded chunks from fire-gem.bin

section .text
    global _start

_start:
    ; 1. CREATE DIRECTORIES (mkdir -p logic)
    mov rax, 83         ; sys_mkdir
    mov rdi, dir_1
    mov rsi, 0755o      ; permissions
    syscall

    mov rax, 83
    mov rdi, dir_2
    syscall

    mov rax, 83
    mov rdi, dir_2_sub
    syscall

    ; 2. OPEN SOURCE DATA (fire-gem.bin)
    mov rax, 2          ; sys_open
    mov rdi, bin_source
    mov rsi, 0          ; O_RDONLY
    syscall
    mov r12, rax        ; Save source FD to r12

    ; 3. DEPLOY FILE-A (Source Offset 0x00)
    ; Seek to 0x00
    mov rax, 8          ; sys_lseek
    mov rdi, r12
    mov rsi, 0x00       ; offset from JSON
    mov rdx, 0          ; SEEK_SET
    syscall
    call copy_chunk_to_file_a

    ; 4. DEPLOY FILE-C (Source Offset 0x80)
    ; Seek to 0x80
    mov rax, 8
    mov rdi, r12
    mov rsi, 0x80       ; offset from JSON
    mov rdx, 0
    syscall
    call copy_chunk_to_file_c

    ; EXIT
    mov rax, 60
    xor rdi, rdi
    syscall

; --- Helper Functions ---

copy_chunk_to_file_a:
    ; Read from bin
    mov rax, 0          ; sys_read
    mov rdi, r12
    mov rsi, buffer
    mov rdx, 64
    syscall
    
    ; Create file-a
    mov rax, 2          ; sys_open
    mov rdi, file_a
    mov rsi, 65         ; O_CREAT | O_WRONLY
    mov rdx, 0755o      ; Apply chmod +x authority
    syscall
    
    ; Write to file-a
    mov rdi, rax
    mov rax, 1          ; sys_write
    mov rsi, buffer
    mov rdx, 64
    syscall
    ret

copy_chunk_to_file_c:
    ; Similar logic for nested file-c
    mov rax, 0
    mov rdi, r12
    mov rsi, buffer
    mov rdx, 64
    syscall

    mov rax, 2
    mov rdi, file_c
    mov rsi, 65
    mov rdx, 0755o
    syscall

    mov rdi, rax
    mov rax, 1
    mov rsi, buffer
    mov rdx, 64
    syscall
    ret

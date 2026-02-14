; ============================================================
; FIRE-GEM.ASM — Master Orchestrator [AVIS-Law Compliant]
; ============================================================

section .data
    msg_init db "[AVIS-GEM] Master Engine Ignition: Reading INI Sequence...", 0xa
    len_init equ $ - msg_init

section .text
    global _start
    extern FIRE_LOG_STRIKE  ; Import the Modular Log Object

_start:
    ; --- 1. INITIALIZE LOGGING VIA OBJECT ---
    ; This proves the engine uses the hot-swappable log subsystem
    lea rdi, [msg_init]
    mov rsi, len_init
    call FIRE_LOG_STRIKE

    ; --- 2. ORCHESTRATE INI SEQUENCE ---
    ; Logic to parse fire-gem.ini and trigger the next stage
    ; [FVS -> SEED -> SPEC -> END]

    ; --- 3. TERMINATE ---
    mov rax, 60
    xor rdi, rdi
    syscall

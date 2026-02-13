#!/bin/bash
# fire-gem/fire-gem.sh
# Sequential Binary Loader - AVIS_CORE Governance
set -e

INI="fire-gem/fire-gem.ini"
LOG="fire-gem/fire-gem.log"

echo "[AVIS-SH] Identity: fire-gem-sequential-loader" >> "$LOG"

# --- PHASE 1: DYNAMIC COMPILE ---
# Extracts every active .asm file from the AVIS_CMD blocks
MAP=$(grep -E "^  FIRE_|^  fire_" "$INI" | grep -v "#" | cut -d'=' -f2 | cut -d':' -f2)

for ASM in $MAP; do
    ASM=$(echo "$ASM" | tr -d '\r ')
    TARGET=$(basename "$ASM" .asm)
    
    echo "[AVIS-SH] Building Artifact: $TARGET" >> "$LOG"
    nasm -f elf64 "fire-gem/$ASM" -o "fire-gem/$TARGET.o"
    ld "fire-gem/$TARGET.o" -o "fire-gem/$TARGET.exe"
done

# --- PHASE 2: SEQUENTIAL LOAD ---
# Executes the artifacts in the exact order of the Registry
echo "[AVIS-SH] Loading Binaries via INI Sequence..." >> "$LOG"

for ASM in $MAP; do
    TARGET=$(basename "$ASM" .asm)
    EXE="./fire-gem/$TARGET.exe"
    
    if [ -f "$EXE" ]; then
        echo "[AVIS-SH] Executing Stage: $EXE" >> "$LOG"
        "$EXE" >> "$LOG" 2>&1
    fi
done

echo "[AVIS-SH] Sequence Terminated. HAHA!" >> "$LOG"

#!/bin/bash
# fire-gem/fire-gem.sh
# Sequential Binary Loader - AVIS_CORE Governance [LOG-OBJECT PATCH]
set -e

INI="fire-gem/fire-gem.ini"
LOG="fire-gem/fire-gem.log"

echo "[AVIS-SH] Identity: fire-gem-sequential-loader" >> "$LOG"

# --- PHASE 0: BOOTSTRAP LOG OBJECT ---
# This must exist for any other artifact to link against it
echo "[AVIS-SH] Building Master Log Object..." >> "$LOG"
nasm -f elf64 fire-gem/fire-log.asm -o fire-gem/fire-log.o

# --- PHASE 1: DYNAMIC COMPILE & LINK ---
MAP=$(grep -E "^  FIRE_|^  fire_" "$INI" | grep -v "#" | cut -d'=' -f2 | cut -d':' -f2)

for ASM in $MAP; do
    ASM=$(echo "$ASM" | tr -d '\r ')
    TARGET=$(basename "$ASM" .asm)
    
    echo "[AVIS-SH] Building Artifact: $TARGET" >> "$LOG"
    nasm -f elf64 "fire-gem/$ASM" -o "fire-gem/$TARGET.o"
    
    # LINKER STRIKE: Every EXE now includes the Log Object code
    ld "fire-gem/$TARGET.o" fire-gem/fire-log.o -o "fire-gem/$TARGET.exe"
done

# --- PHASE 2: SEQUENTIAL LOAD ---
echo "[AVIS-SH] Loading Binaries via INI Sequence..." >> "$LOG"

for ASM in $MAP; do
    TARGET=$(basename "$ASM" .asm)
    EXE="./fire-gem/$TARGET.exe"
    
    if [ -f "$EXE" ]; then
        echo "[AVIS-SH] Executing Stage: $EXE" >> "$LOG"
        # Since we use the Log Object, stdout capture is now a backup
        "$EXE" >> "$LOG" 2>&1
    fi
done

echo "[AVIS-SH] Sequence Terminated. HAHA!" >> "$LOG"


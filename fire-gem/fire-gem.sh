#!/bin/bash
# fire-gem/fire-gem.sh
set -e

INI="fire-gem/fire-gem.ini"
LOG="fire-gem/fire-gem.log"

echo "[AVIS-SH] ENGAGED: Sequential Loader Active" >> "$LOG"

# --- PHASE 1: THE COMPILE SEQUENCE ---
# Extract filenames from the INI and build the artifacts
COMPILE_SEQ=$(grep -E "^fire_[a-zA-Z0-9_]+=" "$INI" | cut -d'=' -f2)

for ASM_FILE in $COMPILE_SEQ; do
    ASM_FILE=$(echo "$ASM_FILE" | tr -d '\r ')
    TARGET=$(basename "$ASM_FILE" .asm)
    
    echo "[AVIS-SH] Compiling Stage: $TARGET" >> "$LOG"
    nasm -f elf64 "fire-gem/$ASM_FILE" -o "fire-gem/$TARGET.o"
    ld "fire-gem/$TARGET.o" -o "fire-gem/$TARGET.exe"
done

# --- PHASE 2: THE LOAD SEQUENCE ---
# Now we load and run the .exe files EXACTLY as defined in the INI
echo "[AVIS-SH] Loading Binaries from INI Sequence..." >> "$LOG"

for ASM_FILE in $COMPILE_SEQ; do
    TARGET=$(basename "$ASM_FILE" .asm)
    EXE="./fire-gem/$TARGET.exe"
    
    if [ -f "$EXE" ]; then
        echo "[AVIS-SH] Executing: $EXE" >> "$LOG"
        # Run the binary and pipe output to the log
        "$EXE" >> "$LOG" 2>&1
    fi
done

echo "[AVIS-SH] Sequence Complete. Server Sync Ready." >> "$LOG"

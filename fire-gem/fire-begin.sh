#!/bin/bash
# fire-gem/fire-begin.sh
# Parses fire-gem.ini and builds the hardware environment.
set -e

INI="fire-gem/fire-gem.ini"
LOG="fire-gem/fire-gem.log"

echo "[AVIS-BEGIN] LOADING INI: $INI" >> "$LOG"

# 1. Compile the Master Engine (fire-gem.asm)
nasm -f elf64 fire-gem/fire-gem.asm -o fire-gem/fire-gem.o
ld fire-gem/fire-gem.o -o fire-gem/fire-gem.exe

# 2. Extract active 'fire_' keys from the INI and compile them
# This builds fire-seed, fire-spec, avis_fvs, etc.
MODULES=$(grep -E "^fire_[a-zA-Z0-9_]+=" "$INI" | cut -d'=' -f2)

for ASM_FILE in $MODULES; do
    ASM_FILE=$(echo "$ASM_FILE" | tr -d '\r ' )
    TARGET=$(basename "$ASM_FILE" .asm)
    
    if [ -f "fire-gem/$ASM_FILE" ]; then
        echo "[AVIS-BEGIN] COMPILING: $TARGET" >> "$LOG"
        nasm -f elf64 "fire-gem/$ASM_FILE" -o "fire-gem/$TARGET.o"
        ld "fire-gem/$TARGET.o" -o "fire-gem/$TARGET"
    fi
done

# 3. Handoff to the hardware engine
./fire-gem/fire-gem.exe

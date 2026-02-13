#!/bin/bash
# fire-gem/fire-gem.sh

LOG="fire-gem/fire-gem.log"

# AVIS SH-Level Logging
echo "[AVIS-SH] Identity: fire-gem-sh" >> "$LOG"
echo "[AVIS-SH] Status: Compiling ASM Chain..." >> "$LOG"

# 1. Assemble the core
nasm -f elf64 fire-gem/fire-gem.asm -o fire-gem/fire-gem.o

# 2. Link to create the executable
ld fire-gem/fire-gem.o -o fire-gem/fire-gem.exe

# 3. Execute the ASM (Hardware Level)
./fire-gem/fire-gem.exe

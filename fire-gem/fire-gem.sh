#!/bin/bash
# fire-gem/fire-gem.sh

LOG="fire-gem/fire-gem.log"

echo "[AVIS-SH] Identity: fire-gem-sh" >> "$LOG"
echo "[AVIS-SH] Status: Compiling ASM..." >> "$LOG"

# Assemble and Link
#nasm -f elf64 fire-gem/fire-gem.asm -o fire-gem/fire-gem.o
#ld fire-gem/fire-gem.o -o fire-gem/fire-gem.exe

# COMMENT OUT THIS LINE to stop at SH level
#./fire-gem/fire-gem.exe

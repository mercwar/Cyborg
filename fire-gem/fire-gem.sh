#!/bin/bash
LOG="fire-gem/fire-gem.log"

echo "[AVIS-SH] Identity: fire-gem-sh" >> "$LOG"
echo "[AVIS-SH] Status: Building Hardware Chain..." >> "$LOG"

# Build/Run Core
nasm -f elf64 fire-gem/fire-gem.asm -o fire-gem/fire-gem.o
ld fire-gem/fire-gem.o -o fire-gem/fire-gem.exe
./fire-gem/fire-gem.exe

# Build/Run Terminator
nasm -f elf64 fire-gem/fire-end.asm -o fire-gem/fire-end.o
ld fire-gem/fire-end.o -o fire-gem/fire-end.exe
./fire-gem/fire-end.exe

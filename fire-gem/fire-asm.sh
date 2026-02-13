#!/bin/bash
# fire-gem/fire-asm.sh
set -e

# Assemble
nasm -f elf64 fire-gem/fire-gem.asm -o fire-gem/fire-gem.o

# Link
ld fire-gem/fire-gem.o -o fire-gem/fire-gem.exe

# Execute
./fire-gem/fire-gem.exe

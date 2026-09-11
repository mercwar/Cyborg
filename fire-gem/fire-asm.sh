#!/bin/bash
# fire-gem/fire-gem.sh
set -e

# 1. Compile the Log Object
nasm -f elf64 fire-gem/fire-log.asm -o fire-gem/fire-log.o

# 2. Compile the Master Engine
nasm -f elf64 fire-gem/fire-gem.asm -o fire-gem/fire-gem.o

# 3. LINK BOTH INTO ONE EXECUTIVE
# This allows fire-gem to see the AVIS_LOG_STRIKE symbol
ld fire-gem/fire-gem.o fire-gem/fire-log.o -o fire-gem.exe

# 4. Run it
./fire-gem.exe

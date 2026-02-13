#!/bin/bash
set -e

# Compile the core and the terminator
nasm -f elf64 fire-gem/fire-gem.asm -o fire-gem/fire-gem.o
nasm -f elf64 fire-gem/fire-end.asm -o fire-gem/fire-end.o

# Link them
ld fire-gem/fire-gem.o -o fire-gem/fire-gem.exe
ld fire-gem/fire-end.o -o fire-gem/fire-end.exe

# Execute Chain
./fire-gem/fire-gem.exe
./fire-gem/fire-end.exe

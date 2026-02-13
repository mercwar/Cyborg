#!/bin/bash
# fire-gem/fire-gem.sh

# Assemble the code
nasm -f elf64 fire-gem/fire-gem.asm -o fire-gem/fire-gem.o

# Link to create the executable
ld fire-gem/fire-gem.o -o fire-gem/fire-gem.exe

# Run the final fire-gem asm program
./fire-gem/fire-gem.exe

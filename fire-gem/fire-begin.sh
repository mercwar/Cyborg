#!/bin/bash
# fire-gem/fire-begin.sh
set -e

# Compile the new FVS and Macro stubs
nasm -f elf64 fire-gem/avis-fvs.asm -o fire-gem/avis-fvs.o
ld fire-gem/avis-fvs.o -o fire-gem/avis-fvs

nasm -f elf64 fire-gem/fire-macro.asm -o fire-gem/fire-macro.o
ld fire-gem/fire-macro.o -o fire-gem/fire-macro

# Now run the Master Engine
./fire-gem/fire-gem.exe

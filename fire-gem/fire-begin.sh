#!/bin/bash
# fire-gem/fire-begin.sh
set -e

# Compile the new FVS Buddy and the Macro Stub
nasm -f elf64 fire-gem/avis-fvs.asm -o fire-gem/avis-fvs.o
ld fire-gem/avis-fvs.o -o fire-gem/avis-fvs

nasm -f elf64 fire-gem/fire-macro.asm -o fire-gem/fire-macro.o
ld fire-gem/fire-macro.o -o fire-gem/fire-macro

# The Engine (fire-gem.exe) will now find these in the path
./fire-gem/fire-gem.exe

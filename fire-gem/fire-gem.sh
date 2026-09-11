#!/bin/bash
# =============================================================================
#  AVIS_CORE: DUMB BOOTSTRAPPER (v3.0 - POST-MIGRATION)
#  FILE: fire-gem.sh
#  PURPOSE: Initialize the AVIS-CORE Smithy and Handoff to ASM-Orchestrator.
#  GOVERNANCE: AVIS_SECTOR: ASM | STATUS: SHELL_DECOUPLED
# =============================================================================
set -e

# --- PHASE 0: BOOTSTRAP MASTER OBJECTS ---
# [MIGRATION NOTE]: PHASES 1 & 2 (Dynamic Compile/Load) have been migrated 
# to fire-compile.asm and fire-gem.asm respectively. 
# The Shell no longer greps the INI or manages the execution loop.

# Build the Master Log Object (Mandatory for all downstream links)
nasm -f elf64 fire-gem/fire-log.asm -o fire-gem/fire-log.o

# Build the Master Engine (The new Orchestrator of the INI sequence)
nasm -f elf64 fire-gem/fire-gem.asm -o fire-gem/fire-gem.o

# --- PHASE 1: LINK MASTER ENGINE ---
# [AVIS-LAW]: Every binary in the chain must link against fire-log.o
# to ensure the [SYNC] High-Precision Seal remains deterministic.
ld fire-gem/fire-gem.o fire-gem/fire-log.o -o fire-gem.exe

# --- PHASE 2: TOTAL HANDOFF ---
# [AVIS-CMD]: Handing control to the Hardware Smithy. 
# fire-gem.exe will now parse fire-gem.ini and fire-compile.ini internally.
./fire-gem.exe

# =============================================================================
#  END OF SHELL AUTHORITY - [HAHA!]
# =============================================================================

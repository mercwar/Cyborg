#!/bin/bash
# fire-gem/fire-gem.sh

LOG_FILE="fire-gem/fire-gem.log"

# 1. AVIS Initialization Log
echo "[AVIS-SH] Starting build process..." >> "$LOG_FILE"

# 2. Assemble the code
# Redirecting stderr to log to catch "nasm" errors
if ! nasm -f elf64 fire-gem/fire-gem.asm -o fire-gem/fire-gem.o >> "$LOG_FILE" 2>&1; then
    echo "[AVIS-SH] CRITICAL: Assembly failed." >> "$LOG_FILE"
    exit 1
fi

# 3. Link to create the executable
if ! ld fire-gem/fire-gem.o -o fire-gem/fire-gem.exe >> "$LOG_FILE" 2>&1; then
    echo "[AVIS-SH] CRITICAL: Linking failed." >> "$LOG_FILE"
    exit 1
fi

# 4. Execute and Log AVIS Handoff
echo "[AVIS-SH] Executing ./fire-gem/fire-gem.exe..." >> "$LOG_FILE"

# Run the program and capture the exit code
./fire-gem/fire-gem.exe >> "$LOG_FILE" 2>&1
EXIT_CODE=$?

# 5. Final AVIS Status
echo "[AVIS-SH] Execution finished with Exit Code: $EXIT_CODE" >> "$LOG_FILE"

# If it exited with 127 or 139 (segfault), we'll finally know.
exit $EXIT_CODE

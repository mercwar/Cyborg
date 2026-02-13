#!/bin/bash
# fire-gem/fire-gem.sh

LOG_FILE="fire-gem/fire-gem.log"

# AVIS Logging Block
echo "--- AVIS LOG START ---" >> "$LOG_FILE"
echo "[AVIS] IDENTITY: fire-gem-loader" >> "$LOG_FILE"
echo "[AVIS] TIMESTAMP: $(date)" >> "$LOG_FILE"
echo "[AVIS] DIRECTORY: $(pwd)" >> "$LOG_FILE"
echo "[AVIS] STATUS: Environment Initialized" >> "$LOG_FILE"

# The ASM Handoff (Commented out as requested)
# echo "[AVIS] HANDOFF: Triggering fire-asm.sh..." >> "$LOG_FILE"
# ./fire-gem/fire-asm.sh >> "$LOG_FILE" 2>&1

echo "[AVIS] STATUS: Handoff skipped. Standalone logging complete." >> "$LOG_FILE"
echo "--- AVIS LOG END ---" >> "$LOG_FILE"


#!/bin/bash
# fire-gem/fire-gem.sh
# Primary trigger for the AVIS installation.

LOG="fire-gem/fire-gem.log"
mkdir -p fire-gem

echo "[AVIS-SH] ENGAGED: Starting fire-gem.sh" >> "$LOG"

# Set permissions and hand off to fire-begin.sh
chmod +x fire-gem/fire-begin.sh
./fire-gem/fire-begin.sh

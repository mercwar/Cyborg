#!/bin/bash
# fire-gem/fire-site.sh
# Purpose: Dynamic Sitemap Generation for AVIS Environment

SITE_URL="https://mercwar.github.io"
LOG="fire-gem/fire-gem.log"

echo "[AVIS-BOT] Initiating fire-site.sh: Mapping Repository..." >> "$LOG"

# Create the XML header
echo '<?xml version="1.0" encoding="UTF-8"?>' > sitemap.xml
echo '<urlset xmlns="http://www.sitemaps.org">' >> sitemap.xml

# Map all HTML files in the root and subdirectories
find . -name "*.html" ! -path "./node_modules/*" | while read -r file; do
    # Strip leading dot and format URL
    CLEAN_PATH=$(echo "$file" | sed 's|^\.||')
    echo "  <url><loc>${SITE_URL}${CLEAN_PATH}</loc></url>" >> sitemap.xml
done

echo '</urlset>' >> sitemap.xml
echo "[AVIS-BOT] fire-site.sh complete: sitemap.xml updated. HAHA!" >> "$LOG"

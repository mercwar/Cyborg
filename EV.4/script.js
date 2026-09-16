const TARGET_DIR = 'EV.4/xml/';
const USERNAME = 'mercwar';
const REPO = 'Cyborg';
const BRANCH = 'main'; // adjust if needed

function safeUrlDecode(str) {
  try { return decodeURIComponent(str); }
  catch (e) { return unescape(str); }
}

async function scanServerDirectory() {
  const treeContainer = document.getElementById('file-tree');
  treeContainer.innerHTML = 'Reading...';

  try {
    let fileList = [];
    // Strips out any potential duplicate back-to-back slash configurations cleanly
    const cleanPath = TARGET_DIR.replace(/^\/+|\/+$/g, '');
    const apiUrl = `https://api.github.com/repos/${USERNAME}/${REPO}/contents/${cleanPath}`;
    
    const ghResponse = await fetch(apiUrl);

    if (ghResponse && ghResponse.ok) {
      const data = await ghResponse.json();
      if (Array.isArray(data)) {
         fileList = data.filter(item => item.type === 'file' && item.name.endsWith('.txt')).map(item => item.name);
      }
    } else {
      // Exposes any hidden HTTP status code blocks (like 404 or 403 Rate Limits) straight to the sidebar container
      treeContainer.innerHTML = `API HTTP Error: ${ghResponse ? ghResponse.status : 'No response'}`;
      return;
    }

    if (fileList.length === 0) {
      treeContainer.innerHTML = 'No files found.';
      return;
    }

    renderSidebar(fileList);
  } catch (err) {
    console.warn("Server directory scan error:", err);
    treeContainer.innerHTML = 'Error loading directory.';
  }
}

function renderSidebar(files) {
  const treeContainer = document.getElementById('file-tree');
  treeContainer.innerHTML = '';

  files.forEach((fileName, index) => {
    const item = document.createElement('div');
    item.className = 'tree-item';
    item.id = `page-btn-${index}`;

    // Fix raw file link construction to avoid string tracking assembly double slashes
    const cleanDir = TARGET_DIR.endsWith('/') ? TARGET_DIR : TARGET_DIR + '/';
    const fullPath = `https://raw.githubusercontent.com/${USERNAME}/${REPO}/${BRANCH}/${cleanDir}${fileName}`;

    item.textContent = `PAGE ${index + 1}`;
    item.onclick = () => {
      document.querySelectorAll('.tree-item').forEach(el => el.classList.remove('active'));
      item.classList.add('active');
      loadSovereignData(fullPath, fileName);
    };

    treeContainer.appendChild(item);
  });
}

async function loadSovereignData(filepath, displayName) {
  const statusBar = document.getElementById('status-bar');
  try {
    statusBar.innerText = `FETCHING FILE: [${displayName}]...`;
    const response = await fetch(filepath);
    if (!response.ok) throw new Error(`HTTP ${response.status}`);

    const xmlText = await response.text();
    parseAndRenderXML(xmlText, displayName);
  } catch (err) {
    statusBar.innerText = `ERROR: ${err.message}`;
  }
}

function parseAndRenderXML(xmlText, sourceName) {
  const statusBar = document.getElementById('status-bar');
  const appVolume = document.getElementById('app-volume');
  const metaContainer = document.getElementById('meta-container');
  const translationContainer = document.getElementById('translation-container');
  const telemetryContainer = document.getElementById('telemetry-container');

  const parser = new DOMParser();
  const xmlDoc = parser.parseFromString(xmlText, "text/xml");

  if (xmlDoc.querySelector("parsererror")) {
    statusBar.innerText = "ERROR: XML Parsing Failed";
    if (telemetryContainer) {
      telemetryContainer.innerHTML = '<div style="color: var(--text-alert);">[SYSTEM EXCEPTION]: Failed to interpret XML structure elements. Check encoding syntax.</div>';
    }
    return;
  }

  // 1. Parse Root Attribute Metrics
  const rootNode = xmlDoc.querySelector("SovereignFramework");
  const volAttr = rootNode ? rootNode.getAttribute("volume") : null;
  if (appVolume && volAttr) {
    appVolume.innerText = `VOL: ${volAttr}`;
  }

  // 2. Parse Meta Configuration Array Nodes Safely
  if (metaContainer) {
    const dirRoot = xmlDoc.querySelector("DirectoryRoot")?.textContent || "N/A";
    const hwAffinity = xmlDoc.querySelector("HardwareAffinity")?.textContent || "N/A";
    const segmentBase = xmlDoc.querySelector("TargetSegmentBase")?.textContent || "N/A";

    metaContainer.innerHTML = `
        <div class="meta-item"><span class="meta-label">Matrix Root:</span> <span style="color: var(--text-accent);">${dirRoot}</span></div>
        <div class="meta-item"><span class="meta-label">Hardware Profile:</span> ${hwAffinity}</div>
        <div class="meta-item"><span class="meta-label">Allocation Limit:</span> <span style="color: var(--text-telemetry);">${segmentBase}</span></div>
    `;
  }

  // 3. Extract and Build Translation Matrix Workspace Rows
  if (translationContainer) {
    let matrixHTML = '';
    const subjectPages = xmlDoc.querySelectorAll("SubjectPage");

    subjectPages.forEach(page => {
      const pageId = page.getAttribute("id") || "--";
      const topicName = page.getAttribute("topic") || "GENERIC_VECTOR";
      
      const engTitle = page.querySelector("EnglishSection > Title")?.textContent || "Untitled Block";
      const engContent = page.querySelector("EnglishSection > Content")?.textContent || "";
      
      const cyTitle = page.querySelector("CyborgSection > Title")?.textContent || "";
      const cyContent = page.querySelector("CyborgSection > Content")?.textContent || "";
      
      const machTitle = page.querySelector("MachineSection > Title")?.textContent || "";
      const machContent = page.querySelector("MachineSection > Content")?.textContent || "";

      matrixHTML += `
        <div style="background: var(--bg-panel); border: 1px solid rgba(46, 160, 67, 0.3); border-radius: 6px; padding: 16px; margin-bottom: 20px;">
          <div style="display: flex; justify-content: space-between; border-bottom: 1px solid rgba(255,255,255,0.05); padding-bottom: 8px; margin-bottom: 12px;">
            <span style="color: var(--text-accent); font-weight: bold; font-size: 0.9rem;">PAGE IDENTIFIER: ${pageId}</span>
            <span style="color: var(--text-muted); font-size: 0.8rem;">TOPIC: ${topicName}</span>
          </div>

          <!-- Section I: English -->
          <div style="margin-bottom: 12px;">
            <div style="color: #ffffff; font-size: 0.85rem; margin-bottom: 4px; font-weight: bold;">[I] ${engTitle}</div>
            <div style="color: var(--text-main); font-size: 0.8rem; line-height: 1.5; text-align: justify; font-family: sans-serif;">${engContent}</div>
          </div>

          <!-- Section II: Cyborg Code Definition -->
          <div style="margin-bottom: 12px;">
            <div style="color: var(--text-accent); font-size: 0.8rem; margin-bottom: 4px; font-weight: bold;">[II] ${cyTitle}</div>
            <div style="color: #8b949e; background: rgba(0,0,0,0.3); border-left: 2px solid var(--border-color); padding: 6px 10px; font-size: 0.75rem; line-height: 1.4;">${cyContent}</div>
          </div>

          <!-- Section III: Direct Assembly Machine Block -->
          <div>
            <div style="color: var(--text-telemetry); font-size: 0.8rem; margin-bottom: 4px; font-weight: bold;">[III] ${machTitle}</div>
            <div style="color: #52f87a; background: #000000; border: 1px solid rgba(255,255,255,0.05); padding: 8px; font-family: monospace; font-size: 0.75rem; white-space: pre-wrap; letter-spacing: 0.5px;">${machContent}</div>
          </div>
        </div>
      `;
    });

    translationContainer.innerHTML = matrixHTML || '<div style="color: var(--text-muted);">No conversion metrics inside matrix payload.</div>';
  }

  // 4. Populate Telemetry Corridor Streams
  if (telemetryContainer) {
    let telemetryHTML = '';
    const indexNodes = xmlDoc.querySelectorAll("TelemetryLogCorridor > NodeIndex");
    
    indexNodes.forEach(node => {
      const nodeId = node.getAttribute("id");
      telemetryHTML += `<div style="margin-bottom: 4px;"><span style="color: var(--text-telemetry);">[NODE_${nodeId}]:</span> <span style="color: var(--text-main); font-family: monospace;">${node.textContent}</span></div>`;
    });

    // Check for trailing structural padding data blocks
    const padding = xmlDoc.querySelector("PaddingBlocks")?.textContent;
    if (padding) {
      const cleanLines = padding.split('\n').map(line => line.trim()).filter(line => line.length > 0);
      cleanLines.slice(0, 4).forEach(line => {
        telemetryHTML += `<div style="color: var(--text-muted); opacity: 0.65; font-family: monospace;">[PADDING_STREAM]: ${line}</div>`;
      });
      if (cleanLines.length > 4) {
        telemetryHTML += `<div style="color: var(--text-accent); font-size: 0.7rem; opacity: 0.5;">... [+${cleanLines.length - 4} High-Density Loop Snapshots Omitted from Display View]</div>`;
      }
    }

    telemetryContainer.innerHTML = telemetryHTML || '<div style="color: var(--text-muted);">Pipeline stream idle.</div>';
    telemetryContainer.scrollTop = telemetryContainer.scrollHeight; // Keep scrolling pushed down to current logs
  }

  statusBar.innerText = `SOURCE: [${sourceName}] LOADED & PARSED OK`;
}
// ============================================================================
// MERCWAR EV.4 EVENT HANDLING PATCH — INTERACTION EXTENSIONS
// ============================================================================

(function injectSovereignEventHandlers() {
    // Master Registry tracker for active file indices
    let activeIndex = -1;

    // 1. Keyboard Navigation Interface
    window.addEventListener('keydown', (e) => {
        const items = document.querySelectorAll('#file-tree .tree-item');
        if (items.length === 0) return;

        // Sync local index tracking to the active selection array state
        const currentActive = document.querySelector('#file-tree .tree-item.active');
        if (currentActive) {
            activeIndex = Array.from(items).indexOf(currentActive);
        }

        if (e.key === 'ArrowDown' || e.key.toLowerCase() === 's') {
            e.preventDefault();
            activeIndex = (activeIndex + 1) % items.length;
            triggerItemSelection(items[activeIndex]);
        } else if (e.key === 'ArrowUp' || e.key.toLowerCase() === 'w') {
            e.preventDefault();
            activeIndex = (activeIndex - 1 + items.length) % items.length;
            triggerItemSelection(items[activeIndex]);
        }
    });

    // Auxiliary helper function to safely fire DOM clicks and focus targets
    function triggerItemSelection(element) {
        if (!element) return;
        element.click();
        element.scrollIntoView({ block: 'nearest', behavior: 'smooth' });
    }

    // 2. Interactive Telemetry Tracking Overrides
    const telemetryBox = document.getElementById('telemetry-container');
    if (telemetryBox) {
        // Pauses strict autoscroll lock loops if manual user inspection is ongoing
        let isUserScrolling = false;
        
        telemetryBox.addEventListener('scroll', () => {
            const isAtBottom = telemetryBox.scrollHeight - telemetryBox.scrollTop <= telemetryBox.clientHeight + 10;
            isUserScrolling = !isAtBottom;
        });

        // Set up mutation configuration observer to snap current logs into view dynamically
        const observer = new MutationObserver(() => {
            if (!isUserScrolling) {
                telemetryBox.scrollTop = telemetryBox.scrollHeight;
            }
        });

        observer.observe(telemetryBox, { childList: true });
    }

    console.log("[EVENT_PATCH]: Vector map configurations initialized successfully.");
})();

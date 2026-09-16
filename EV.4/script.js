    const TARGET_DIR = 'xml/';

    function safeUrlDecode(str) {
        try {
            return decodeURIComponent(str);
        } catch (e) {
            return unescape(str);
        }
    }
    async function scanServerDirectory() {
        const treeContainer = document.getElementById('file-tree');
        treeContainer.innerHTML = '<div style="grid-column: span 2; padding: 10px; color: var(--text-muted); font-size: 0.8rem; text-align: center;">Reading...</div>';

        try {
            let fileList = [];
            const isGitHubPages = window.location.hostname.includes('github.io');

            if (isGitHubPages) {
                // Parse repository details directly from the URL structure: username.github.io/repo-name
                const pathParts = window.location.pathname.split('/').filter(Boolean);
                const username = window.location.hostname.split('.')[0];
                const repo = pathParts[0]; 

                if (username && repo) {
                    // Fetch file list via GitHub Public Contents API
                    const apiUrl = `https://api.github.com{username}/${repo}/contents/${TARGET_DIR.replace(/\/$/, '')}`;
                    let ghResponse = await fetch(apiUrl).catch(() => null);
                    
                    if (ghResponse && ghResponse.ok) {
                        const data = await ghResponse.json();
                        fileList = data
                            .filter(item => item.type === 'file' && (item.name.endsWith('.txt') || item.name.endsWith('.xml')))
                            .map(item => item.name);
                    }
                }
            }

            // Fallback to local server methods if GitHub API path wasn't used or failed
            if (fileList.length === 0) {
                let response = await fetch('list_files.php').catch(() => null);

                if (response && response.ok) {
                    fileList = await response.json();
                } else {
                    response = await fetch(TARGET_DIR);
                    if (!response.ok) throw new Error(`Directory index inaccessible at '${TARGET_DIR}'`);
                    
                    const htmlText = await response.text();
                    const parser = new DOMParser();
                    const doc = parser.parseFromString(htmlText, 'text/html');
                    
                    const links = Array.from(doc.querySelectorAll('a'));
                    fileList = links
                        .map(a => a.getAttribute('href'))
                        .filter(href => href && (href.endsWith('.txt') || href.endsWith('.xml')))
                        .map(href => href.replace(/^.*[\\\/]/, ''));
                }
            }

            fileList = fileList.map(name => safeUrlDecode(name));
            renderSidebar(fileList);
        } catch (err) {
            console.warn("Server directory scan error:", err);
            treeContainer.innerHTML = `
                <div style="grid-column: span 2; padding: 10px; color: var(--text-muted); font-size: 0.8rem; text-align: center;">
                    Auto-index off.<br><br>
                    <a href="#" onclick="manualPagePrompt()" style="color: var(--text-accent);">[Enter Page #]</a>
                </div>
            `;
        }
    }


    function extractPageNumber(fileName, index) {
        const decodedName = safeUrlDecode(fileName);
        const match = decodedName.match(/\d+/g);
        if (match) {
            let numStr = match.join('');
            return numStr.length === 1 ? '0' + numStr : numStr;
        }
        return String(index + 1).padStart(2, '0');
    }

    function renderSidebar(files) {
        const treeContainer = document.getElementById('file-tree');
        treeContainer.innerHTML = '';

        if (!files || files.length === 0) {
            treeContainer.innerHTML = '<div style="grid-column: span 2; padding: 10px; color: var(--text-muted); font-size: 0.8rem; text-align: center;">No pages found.</div>';
            return;
        }

        const pages = files.map((fileName, idx) => {
            const decoded = safeUrlDecode(fileName);
            return {
                numStr: extractPageNumber(decoded, idx),
                numVal: parseInt(extractPageNumber(decoded, idx), 10) || (idx + 1),
                fileName: decoded
            };
        }).sort((a, b) => a.numVal - b.numVal);

        pages.forEach((page, index) => {
            const item = document.createElement('div');
            item.className = 'tree-item';
            item.id = `page-btn-${index}`;
            const fullPath = TARGET_DIR + encodeURIComponent(page.fileName);

            item.innerHTML = `
                <span class="item-label">PAGE</span>
                <span class="item-number">${page.numStr}</span>
            `;
            
            item.onclick = () => {
                document.querySelectorAll('.tree-item').forEach(el => el.classList.remove('active'));
                item.classList.add('active');
                loadSovereignData(fullPath, page.fileName);
            };

            treeContainer.appendChild(item);
        });

        const first = document.getElementById('page-btn-0');
        if (first) first.click();
    }

    function manualPagePrompt() {
        const pageNum = prompt("Enter page/volume number (e.g., 11):", "011");
        if (pageNum) {
            const formatted = pageNum.padStart(3, '0');
            renderSidebar([`vol_${formatted}.xml`]);
        }
    }

    async function loadSovereignData(filepath, displayName) {
        const statusBar = document.getElementById('status-bar');
        const readableName = safeUrlDecode(displayName || filepath);
        
        try {
            statusBar.innerText = `FETCHING FILE: [${readableName}]...`;
            const response = await fetch(filepath);
            if (!response.ok) throw new Error(`HTTP ${response.status}: Failed to load '${readableName}'`);

            const xmlText = await response.text();
            parseAndRenderXML(xmlText, readableName);
        } catch (err) {
            statusBar.innerText = `ERROR: ${err.message}`;
            document.getElementById('translation-container').innerHTML = `
                <div class="error-msg">
                    <strong>Load Failure:</strong> Unable to retrieve <code>${readableName}</code>.
                </div>
            `;
        }
    }

    function parseAndRenderXML(xmlText, sourceName) {
        const statusBar = document.getElementById('status-bar');
        const parser = new DOMParser();
        const xmlDoc = parser.parseFromString(xmlText, "text/xml");

        const parserError = xmlDoc.querySelector("parsererror");
        if (parserError) {
            statusBar.innerText = "ERROR: XML Parsing Failed";
            return;
        }

        renderDHTML(xmlDoc);
        statusBar.innerText = `SOURCE: [${safeUrlDecode(sourceName)}] LOADED & PARSED OK`;
    }

    function renderDHTML(xml) {
        const root = xml.querySelector("SovereignFramework");
        if (root) {
            document.getElementById('app-title').innerText = `${root.getAttribute("project")} ${root.getAttribute("version")} Sovereign Framework`;
            document.getElementById('app-volume').innerText = `VOL: ${root.getAttribute("volume")}`;
        }

        const meta = xml.querySelector("MetaConfiguration");
        if (meta) {
            document.getElementById('meta-container').innerHTML = `
                <div class="meta-item"><span class="meta-label">Directory Root:</span> ${getNodeText(meta, "DirectoryRoot")}</div>
                <div class="meta-item"><span class="meta-label">Hardware:</span> ${getNodeText(meta, "HardwareAffinity")}</div>
                <div class="meta-item"><span class="meta-label">Hex Signature:</span> ${getNodeText(meta, "VolumeHexSignature")}</div>
                <div class="meta-item"><span class="meta-label">Target Base:</span> ${getNodeText(meta, "TargetSegmentBase")}</div>
            `;
        }

        const pages = xml.querySelectorAll("SubjectPage");
        let translationHTML = '';

        pages.forEach(page => {
            const eng = page.querySelector("EnglishSection");
            const cyborg = page.querySelector("CyborgSection");
            const machine = page.querySelector("MachineSection");

            translationHTML += `
                <div style="margin-bottom: 20px;">
                    <h2 style="font-size: 1.0rem; color: var(--text-accent); border-bottom: 1px dashed var(--text-accent); padding-bottom: 4px;">
                        Vector #${page.getAttribute("id")} — ${page.getAttribute("topic")}
                    </h2>
                    
                    ${eng ? `<div class="translation-block"><div class="section-header">ENGLISH // ${getNodeText(eng, "Title")}</div><div class="section-body">${getNodeText(eng, "Content")}</div></div>` : ''}
                    ${cyborg ? `<div class="translation-block"><div class="section-header">CYBORG // ${getNodeText(cyborg, "Title")}</div><div class="section-body">${getNodeText(cyborg, "Content")}</div></div>` : ''}
                    ${machine ? `<div class="translation-block"><div class="section-header">MACHINE // ${getNodeText(machine, "Title")}</div><div class="section-body"><div class="code-block">${getNodeText(machine, "Content")}</div></div></div>` : ''}
                </div>
            `;
        });

        document.getElementById('translation-container').innerHTML = translationHTML;

        const telemetry = xml.querySelector("TelemetryLogCorridor");
        if (telemetry) {
            let telemetryHTML = '';
            telemetry.querySelectorAll("NodeIndex").forEach(node => {
                telemetryHTML += `<div class="node-index">[NODE ${node.getAttribute("id")}] ${node.textContent}</div>`;
            });

            const padding = telemetry.querySelector("PaddingBlocks");
            if (padding) {
                telemetryHTML += `<div style="color: var(--text-muted); margin-top: 8px;">${padding.textContent.trim().replace(/\n/g, '<br>')}</div>`;
            }

            document.getElementById('telemetry-container').innerHTML = telemetryHTML;
        }
    }

    function getNodeText(parent, selector) {
        const el = parent.querySelector(selector);
        return el ? el.textContent : 'N/A';
    }

    window.addEventListener('DOMContentLoaded', () => {
        scanServerDirectory();
    });
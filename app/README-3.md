
# ⭐ **README 3 — Technical Architecture & File System Reference**  
### *The deep technical explanation of Cyborg, Constellation, and AVIS*

## 🧩 Cyborg Architecture  
Cyborg is a deterministic, reversible encoding system.

### Core Principles

- **Determinism** — same input → same output  
- **Reversibility** — all transformations undoable  
- **Clarity** — readable by humans and AIs  
- **Compatibility** — aligned with Windows messaging  

### Message Flow

```
Cyborg Message
→ Protocol Translator
→ AVIS Validator
→ Constellation Ingestion
→ Windows Message Layer
```

---

## 🌐 Constellation Architecture  
Constellation is the ingestion and navigation engine.

### Pipeline Stages

1. **Scanner** — discovers schemas, versions, artifacts  
2. **Reducer** — normalizes data  
3. **Autobuild** — compiles intelligence  
4. **Linker** — merges fragments  
5. **Validator** — enforces AVIS  
6. **Publisher** — stores intelligence  

### Navigation  
Constellation exposes:

- schemas  
- maps  
- intelligence blocks  
- node definitions  
- routing graphs  

All navigation flows through Constellation.

---

## 📜 AVIS Architecture  
AVIS is the artifact visibility system.

### AVIS Guarantees

- every file identifies itself  
- every artifact is traceable  
- every schema is visible  
- every intelligence block is indexable  

### AVIS Header Format

```
AIFVS-ARTIFACT
# filename.ext
```

This is mandatory.

---

## 📂 Repository Structure (Technical)  

| Directory | Purpose |
|----------|---------|
| `Constellation/` | Core Navigation |
| `Sentinel/` | Core Return |
| `Nexus/` | Navigation Return|
| `AVIS/` | Navigation Language |
| `Cyborg/` | Language Core|
| `AVIS-DATALAKE/` | Return logic |

---
<!-- START LEGAL CONTRIBUTING SECTION -->
<div class="markdown-body" style="box-sizing: border-box; margin: 24px 0px; padding: 24px; color: #e6edf3; background-color: #161b22; border: 1px solid #30363d; border-radius: 6px; font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', 'Noto Sans', Helvetica, Arial, sans-serif;">
    <h2 style="box-sizing: border-box; margin-top: 0px; margin-bottom: 16px; font-size: 1.5em; font-weight: 600; line-height: 1.25; padding-bottom: 0.3em; border-bottom: 1px solid #21262d; color: #f0f6fc;">
        ⚖️ Legal Terms for Ecosystem Contributions
    </h2>
    <p style="box-sizing: border-box; margin-top: 0px; margin-bottom: 16px; font-size: 14px; line-height: 1.6;">
        By submitting code, documentation, schemas, or modifications to any repository within the <strong>Mercwar Ecosystem</strong>, you explicitly agree to the following deterministic terms of contribution. If you do not agree to these terms, you are not authorized to submit modifications or open pull requests.
    </p>
    <h3 style="font-size: 16px; font-weight: 600; color: #f0f6fc; margin-top: 16px; margin-bottom: 8px;">1. Intellectual Property & Licensing</h3>
    <p style="font-size: 14px; margin-bottom: 12px; color: #c9d1d9; padding-left: 8px; border-left: 2px solid #30363d;">
        All contributions are received under the native license governing the destination repository (e.g., Apache 2.0, MIT, or custom ecosystem constraints). You certify that you are the original author of the submission and possess the unrestricted legal right to grant an irrevocable, perpetual, worldwide, royalty-free license to use, modify, sub-license, and distribute your code without attribution requirements.
    </p>
    <h3 style="font-size: 16px; font-weight: 600; color: #f0f6fc; margin-top: 16px; margin-bottom: 8px;">2. AI-Agent and Autonomous Interaction Rules</h3>
    <p style="font-size: 14px; margin-bottom: 12px; color: #c9d1d9; padding-left: 8px; border-left: 2px solid #30363d;">
        Because this ecosystem relies heavily on autonomous processing via the AVIS protocol and algorithmic parsers, you acknowledge that any data committed may be immediately ingested, parsed, and utilized by artificial intelligence models, scrapers, or automated systems. You waive any subsequent data privacy or restriction claims regarding algorithmic training or parsing outputs executed on public repository data layers.
    </p>
    <h3 style="font-size: 16px; font-weight: 600; color: #f0f6fc; margin-top: 16px; margin-bottom: 8px;">3. Disclaimer of Warranty & Liability Limit</h3>
    <p style="font-size: 14px; margin-bottom: 12px; color: #c9d1d9; padding-left: 8px; border-left: 2px solid #30363d;">
        Submissions are evaluated and merged "AS IS," without warranty of any kind, explicit or implied. The repository maintainers accept no liability for compilation failures, execution anomalies, or downstream operating system conflicts resulting from contributed patches or files.
    </p>
</div>
<!-- END LEGAL CONTRIBUTING SECTION -->

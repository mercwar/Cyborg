
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

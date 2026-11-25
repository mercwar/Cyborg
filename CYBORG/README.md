
<!-- BEGIN_SEED MERCG_AVIS_CORE_2026
GUID: AVIS-CORE-README-2026
TITLE: AVIS – AI Visual Instruction System & Seed Language Specification
AUTHOR: CGPT / MercWar
DATE: 2026-01-14
-->



## 🧬 The Cyborg System
<a target="_self" title="CLICK HERE to ENTER the GATEWAY FREE!" href="https://mercwar.github.io/Constellation/index.html">
<img 
    src="https://raw.githubusercontent.com/mercwar/Robo-Knight-Gallery/refs/heads/main/Version%207/image_d2a07390.png" 
    alt="Mercwar Constellation" 
    style="width:100%; height:auto;"
/>
</a>

### 💫 Cyborg — Headless DLL & Command-Line Digital Signer

##### 📦 *Headless DLL & Command-Line Digital Signer for Windows x64*

<div align="center">

<img src="images/cb1.jpg" alt="Cyborg Digital Signature Banner" />

<br />

</div>

> **Build it. Sign it. Trust it.**  
> Modular, zero-hardcode Windows Authenticode signing suite split into a headless C engine (`cyborg.dll`)  
> Native CLI client (`cyborg.exe`), driven completely by JSON configuration.



---

### 🎯 Overview

## 🗝️ Getting Started
1. **Clone the repository:**
   ```bash
    git clone https://github.com/mercwar/cyborg/CYBORG
   ```
#####

**Cyborg** automates end-to-end Windows code signing workflows using only standard Windows SDK tools (`makecat.exe`, `signtool.exe`) and the free MSVC toolchain:

######

* 🔐 **Self-Signed Certificate Generation** 
- Creates `.pfx` signing certificates on demand.
* 📋 **Catalog Definition & Compilation** 
- Generates `.cdf` manifests from `manifest.ini` and compiles security catalogs via `makecat.exe`.
* ✍️ **Authenticode Signing & Verification**
- Signs executables, DLLs, and catalogs via `signtool.exe` and verifies SHA-256 hashes and trust chains.
* ⚙️ **100% JSON-Driven** 
- All certificate subjects, passwords, file targets, and output directories live in `cyborg.json`.

---



### 🏗️ Architecture

######

| Component | Binary | Responsibilities |
| :--- | :--- | :--- |
| **Headless Engine** | `cyborg.dll` | Exports core signing and config routines via `cyborg.def`. Dynamically loads `dc_cjson.dll` for JSON parsing and `dc_path_wrap.dll` (`@1`–`@11`) via `LoadLibraryA` / `GetProcAddress` (zero header coupling). Orchestrates `.pfx`, `.cdf`, `makecat.exe`, and `signtool.exe`. |
| **CLI Host Client** | `cyborg.exe` | Resolves `cyborg.dll` across the `.exe` folder, `System32` / `SysWOW64`, `PATH`, or `--dll`. Embeds `favicon.ico` (`IDI_APP_ICON`) and version resources, sets the console window icon, and renders color-coded status logs, file metadata, SHA-256 digests, and signature verification results. |

---

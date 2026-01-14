![MercWar Banner](images/mercwar_v017.png)
# Cyborg KB v1.2 · Symbolic Opcode Knowledge Base

Cyborg is a symbolic opcode language and knowledge base designed for programmers, researchers, and digital architects who want a human-readable layer over bytecode, interrupts, and VM internals.

This project is AI-assisted and human-directed, created in collaboration with Demon (CVBGOD), CGPT, and Microsoft Copilot.

---

## Cyborg AI Language  
### Live Online Version (Loads index.html Directly)

You can open the Cyborg KB as a live web page directly from OneDrive.  
This link renders the project's index.html in your browser with no downloads required:

### ✅ **[Cyborg AI Language Browser](https://mercwar01.byethost3.com/)**

This online view includes:

- Symbol browser  
- Documentation viewer  
- Expansion pack loader  
- Full KB interface exactly as intended  

It is the recommended way to preview the KB instantly.

---

## OneDrive Repository (Expansion Packs, Assets, Tools)

The full Cyborg KB v1 folder runs on a web site: [Resource is in the web site [https://mercwar01.hstn.me/](https://mercwar01.byethost3.com/)

Note: This is a folder view.  
To load expansions dynamically, you must use the direct download link for each ZIP file inside the folder.

---

## Features

- 256-entry opcode and symbol table  
- MSDN-style documentation for each symbol  
- Browser-based knowledge base (index.html and loader.js)  
- ZIP-based expansion pack system  
- Offline-first, online-aware design  
- Supports VM/compiler experimentation across DOS, x86, Windows, and custom VMs  

---

## Quick Start

1. Download or clone the repository.  
2. Place the Cyborg_KB_v1.2 folder anywhere on disk or cloud.  
3. Open index.html in a modern browser.  
4. Add ZIP expansion packs to the expansions folder.  
5. Click "Load Local Expansion Pack" to merge them.  
6. (Optional) Configure loader.js with direct OneDrive download links for remote expansions.

---

## Repository Structure

Cyborg_KB_v1.2/  
  index.html — interactive KB front-end  
  loader.js — expansion loader and manager  
  cyborg_copilot_access.json — Copilot / CGPT access  

  kb/  
    symbols.json — core 256-symbol table  
    symbols/ — per-symbol documentation  

  resources/  
    style.css — KB styling  
    images/ — diagrams and icons  

  expansions/ — ZIP expansion packs  

  README.md — this documentation  

---

## Example: Symbolic Hello World

BEGIN_SEED HelloProgram  
  MOV_REG_ AH=09h  
  LEA_REG_ DX = MSG_STR_  
  INT_CALL_ 0x21  

  TERM_DOS_ AH=4Ch  
  CODE0___  
  INT_CALL_ 0x21  
END_SEED

---

## Contributing

- Add or modify symbols in kb/symbols.json  
- Create ZIP expansion packs for optional modules  
- Update cyborg_copilot_access.json for versioning and overrides  
- Store sample programs in a programs folder for testing  

---

## Related Inspirations

- Simple bytecode VMs  
- Symbolic languages that compile to compact runtimes  
- JavaScript-based VMs  
- Lua, NekoVM, and other modular runtimes  

---

## License

Specify your license here (MIT, BSD, Public Domain, etc.)

---

## Authors and Credits

Demon (CVBGOD) — primary architect and creator  
CGPT — symbolic co-designer and early collaborator  
Microsoft Copilot — documentation and refinement support  

---

## Greetings

Welcome to the mercwar/Cyborg repository.  
This project represents a live experiment in human + AI co-designed symbolic systems.  
Explore the scrolls, extend the language, and build your own tools on top of it.

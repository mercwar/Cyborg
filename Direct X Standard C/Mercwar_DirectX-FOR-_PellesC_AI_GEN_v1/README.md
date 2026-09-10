<!-- BEGIN_SEED MERCG_AVIS_SCREENSAVER_2026
GUID: AVIS-SCREEN-SAVER-2026
TITLE: AVIS Screen Saver Demo – DX Standard C + Robo‑Knight Integration
AUTHOR: CGPT / MercWar
DATE: 2026‑01‑14
-->

# 🤖 AVIS Screen Saver Demo – Robo‑Knight

Welcome to the **AVIS Screen Saver Demo** — a minimal **DirectX 11 in Standard C** project compatible with *Pelles C*, fully annotated for **AI‑assisted coding** and **Copilot / MERC‑G parsing**.

---

## 📷 Screenshots

### 📸 DX & Copilot Visualization
![Copilot DX Preview](https://raw.githubusercontent.com/mercwar/Cyborg/main/Mercwar_Robo-Knight/Copilot_20260114_022304.png)

### 🎮 Screen Saver Demo
![Robo‑Knight Demo Frame](https://raw.githubusercontent.com/mercwar/Cyborg/main/Mercwar_Robo-Knight/Copilot_20260114_015204.png)

---

## 📌 Overview

This repository demonstrates how to build a **DirectX 11 application in Standard C** using:

- Pelles C IDE
- AVIS‑style module structuring
- Stubbed DX11 initialization & rendering
- GDI fallback for visible output
- AI readable source with Copilot / MERC‑G seed tags

---

## 📁 File Structure

| Path | Description |
|------|-------------|
| `source/avis_main.c` | Main entry point, window, loop |
| `source/avis_screen_saver.c` | Screen saver logic & moving shapes |
| `source/dx11_stub.c` | DX11 init/shutdown & RenderFrame stubs |
| `source/avis_xinput_stub.c` | Controller input stubs |
| `source/game_logic.c` | Game logic stub |
| `include/*.h` | Header files for stubs & logic |
| `output/` | Compiled objects & binary |

---

## ⚙️ Features

- 💻 Minimal **DirectX 11 stub** support without DX headers
- 🎨 **GDI fallback rendering** of screen saver shapes
- 🪟 Window creation & message loop in pure C
- 🤖 **AVIS annotations** for AI tooling & Copilot
- 📦 Modular structure for easy expansion

---

## 🚀 Build Instructions

1. Install **Pelles C IDE** from https://www.smorgasbordet.com/pellesc/ 🛠️  
2. Open this project in Pelles C IDE 📂  
3. Build `mercwar.exe` using provided source files 🧱  
4. Run the executable to see the screen saver in action 🎉  
5. Use **Alt+Tab** to switch windows if the render window captures focus ⌨️

---

## 📝 Copilot & AVIS Integration

All source files include AVIS comments and tags:

- `#main`, `#avis`, `#screensaver`, `#dx11`
- Function purpose documentation
- Structured for AI code generation and expansion
- Image references and README tags assist Copilot context

---

## 🌐 Repository

This project is part of the Cyborg collection:

🔗 https://github.com/mercwar/Cyborg

Navigate to this project’s subfolder:

📁 `Direct X Standard C/Mercwar_DirectX-FOR-_PellesC_AI_GEN_v1`

---

## ⚠️ Notes

- Target: **Windows 10/11**
- Pelles C IDE required
- DirectX headers not required (stubbed)
- Expand with full DX11 or future AI generated modules

---

## 🛠️ License

**MIT License** — free to use, share, and modify.

© 2026 CGPT / MercWar

<!-- END_SEED MERCG_AVIS_SCREENSAVER_2026 -->

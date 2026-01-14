<!-- #avis #readme #github #dx11 #screensaver #roboknight -->
<!-- AVIS: README for Mercwar_Robo-Knight screen saver demo. Copilot-parsable, structured, and seed-aligned. -->

<h1 align="center">🤖 Mercwar – AVIS Robo‑Knight Screen Saver</h1>

<p align="center">
  <b>GUID:</b> AVIS-ROBOKNIGHT-README-2026<br/>
  <b>Author:</b> CGPT / MercWar<br/>
  <b>Date:</b> 2026‑01‑14
</p>

---

## 🌌 Overview
![Robo-Knight Emblem Concept](Direct%20X%20Standard%20C/Mercwar_Robo-Knight/team_.png)

<!-- AVIS: High-level description of the project. -->
The **Mercwar_Robo-Knight** project is an AVIS‑structured, Pelles‑C‑friendly screen saver demo that uses:

- A **DX11 stub** (no real Direct3D headers required)
- **GDI rendering** for visible motion
- A modular layout designed for **MERC‑GUID / AVIS seeds**
- A future‑facing slot for a **Robo‑Knight** themed visual layer

This README is written as an **HTML + Markdown hybrid** so both humans and Copilot can parse it cleanly.

---

## 📁 Project structure

<!-- AVIS: File structure table for Copilot and humans. -->

| File / Folder              | Role / Description                                           |
|----------------------------|--------------------------------------------------------------|
| `avis_main.c`             | Entry point, window creation, main loop, global state.       |
| `avis_screen_saver.c`     | Screen saver logic (moving shapes / Robo‑Knight stage).      |
| `avis_screen_saver.h`     | Declarations for screen saver functions.                     |
| `dx11_stub.c`             | DX11 stub implementation (no real D3D headers).             |
| `dx11_stub.h`             | DX11 stub interface and opaque DX globals.                   |
| `game_logic.c`            | Game logic stub, called once per frame.                      |
| `game_logic.h`            | Declarations for game logic.                                 |
| `avis_xinput_stub.c`      | XInput stub for controller input.                            |
| `avis_xinput_stub.h`      | Declarations for XInput stub.                                |
| `README.md`               | This document.                                               |
| `assets/`                 | (Optional) Robo‑Knight images, logos, and screenshots.       |
| `Mercwar_Robo-Knight/`    | GitHub folder containing this project and related assets.    |

> AVIS: MERC‑GUID can use this table to map modules to seed entries and generate drop‑in files.

---

## 🧠 AVIS & MERC‑GUID conventions

<!-- AVIS: Explain tags and seed behavior. -->

- **AVIS tags** (in comments and seeds):
  - `#avis` – AVIS‑compliant module
  - `#screensaver` – Screen saver logic or entry point
  - `#dx11` – DX11‑related interface (stub or real)
  - `#readme` – Documentation artifact
- **MERC‑GUID**:
  - Treats `BEGIN_SEED` blocks as canonical project descriptors.
  - Maps `KEYWORDS` → `FILES` → `MODULES` → `GLOBALS`.
  - Generates **drop‑in C files** and documentation from seeds like  
    `MERCG_AVIS_ROBOKNIGHT_README_2026`.

This README is designed so MERC‑GUID can re‑emit or transform it without losing structure.

---

## 🛠️ Build instructions (Pelles C, DX11 stub)

<!-- AVIS: Build steps must be explicit and internal. -->

### 1. Requirements

- **Pelles C** (Windows, 32‑bit or 64‑bit)
- Standard Win32 SDK headers bundled with Pelles C
- No external DirectX SDK or Windows Kits required for the stub build

### 2. Add source files to project

Create a new Pelles C project (Win32 GUI application) and add:

- `avis_main.c`
- `avis_screen_saver.c`
- `avis_screen_saver.h`
- `dx11_stub.c`
- `dx11_stub.h`
- `game_logic.c`
- `game_logic.h`
- `avis_xinput_stub.c`
- `avis_xinput_stub.h`

### 3. Include paths

Use only Pelles C’s own include paths:

- `D:\Program Files\PellesC\Include`
- `D:\Program Files\PellesC\Include\Win`

No Windows Kits include paths are required for the **stub** version.

### 4. Build

- Set configuration to **Win32** or **x64** as desired.
- Build the project.
- Run the resulting executable: it should open a window with a moving rectangle (Robo‑Knight stage placeholder).

---

## 🎮 Runtime behavior

<!-- AVIS: Describe loop and globals. -->

- **Globals**:
  - `g_screenWidth`, `g_screenHeight` – current client area size
  - `g_hDC` – window device context for GDI rendering
  - `g_pDXDevice`, `g_pDXContext`, `g_pDXSwapChain` – opaque DX11 stub pointers
- **Loop**:
  - Processes messages with `PeekMessage`.
  - Calls:
    - `UpdateGame()`
    - `AvisXInput_Update()`
    - `UpdateScreenSaver()`
    - `RenderFrame()` (DX11 stub)
    - `RenderScreenSaver()` (GDI)

The current visual is a **bouncing rectangle**; the Robo‑Knight theme can be layered on top (sprites, logos, or emblem rendering) without changing the loop.

---

## 🖼️ Screenshots & GitHub references

<!-- AVIS: GitHub-friendly image references; paths are symbolic for now. -->

Screenshots and Robo‑Knight visuals are expected to live under:

- `Mercwar_Robo-Knight/assets/`
- `Mercwar_Robo-Knight/docs/`

Example GitHub‑style references:



![Robo-Knight Emblem Concept](Direct%20X%20Standard%20C/Mercwar_Robo-Knight/laser bike.png)

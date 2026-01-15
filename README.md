<!-- BEGIN_SEED MERCG_AVIS_SERIES_2026
GUID: AVIS-ROBOKNIGHT-SERIES-2026
TITLE: RoboNight Series – All Apps
AUTHOR: CGPT / MercWar
DATE: 2026-01-14
-->

# 🚀 RoboNight Series – AVIS + DX11 + Standard C

This repository collects all **RoboNight projects**, including the **Screen Saver Demo**, **Standard C Apps**, and the **Robo‑Knight Demo**.

---

## 📁 Projects in the Series

| Project | README | Screenshot |
|---------|--------|------------|
| **Screen Saver Demo** | [README_ScreenSaver.md](README_ScreenSaver.md) | <div><strong>Screen Saver</strong><br><img src="https://raw.githubusercontent.com/mercwar/Cyborg/main/Mercwar_Robo-Knight/Copilot_20260114_022304.png" style="max-width:200px; border-radius:8px; box-shadow:0 4px 10px rgba(0,0,0,0.3);"></div> |
| **Standard C Apps + AVIS** | [README_StandardCApps.md](README_StandardCApps.md) | <div><strong>Standard C App</strong><br><img src="https://raw.githubusercontent.com/mercwar/Cyborg/main/Mercwar_Robo-Knight/Copilot_20260114_015204.png" style="max-width:200px; border-radius:8px; box-shadow:0 4px 10px rgba(0,0,0,0.3);"></div> |
| **Robo‑Knight Demo** | [README_RoboKnight.md](README_RoboKnight.md) | <div><strong>Robo‑Knight Demo</strong><br><img src="https://raw.githubusercontent.com/mercwar/Cyborg/main/Mercwar_Robo-Knight/Copilot_20260114_022304.png" style="max-width:200px; border-radius:8px; box-shadow:0 4px 10px rgba(0,0,0,0.3);"></div> |

---

## ⚙️ Features Across the Series
- DX11 stubbed & GDI fallback rendering  
- Modular AVIS‑style code for AI / Copilot integration  
- Cross‑file global management  
- Pelles C Standard C compatibility  
- Expandable for future RoboNight apps  

---

## 🚀 Getting Started
1. Install **Pelles C IDE**  
2. Open individual project folders  
3. Build each `.c` project  
4. Run `mercwar.exe`  

---

## 🌐 Repository
Full series on GitHub:  
**https://github.com/mercwar/Cyborg**

---

© 2026 CGPT / MercWar

<!-- END_SEED MERCG_AVIS_SERIES_2026 -->


<!-- BEGIN_SEED MERCG_AVIS_ROBOKNIGHT_2026
GUID: AVIS-ROBOKNIGHT-2026
TITLE: Robo-Knight Demo – RoboNight Series
AUTHOR: CGPT / MercWar
DATE: 2026-01-14
-->

# 🤖 Robo‑Knight Demo – RoboNight

---

## 🖼️ Robo‑Knight DX Demo
<div style="text-align:center; margin-bottom:20px;">
  <img src="https://raw.githubusercontent.com/mercwar/Cyborg/main/Mercwar_Robo-Knight/Copilot_20260114_022304.png" 
       alt="Robo-Knight DX Demo" style="max-width:80%; border-radius:12px; box-shadow:0 4px 15px rgba(0,0,0,0.3);">
</div>

## 🖼️ Screen Saver Frame
<div style="text-align:center; margin-bottom:20px;">
  <img src="https://raw.githubusercontent.com/mercwar/Cyborg/main/Mercwar_Robo-Knight/Copilot_20260114_015204.png" 
       alt="Robo-Knight Screen Saver Frame" style="max-width:70%; border-radius:10px; box-shadow:0 4px 15px rgba(0,0,0,0.3);">
</div>

## 🖼️ Laser Bike Render
<div style="text-align:center; margin-bottom:20px;">
  <img src="https://raw.githubusercontent.com/mercwar/Cyborg/main/Mercwar_Robo-Knight/laser%20bike.png" 
       alt="Robo-Knight Laser Bike" style="max-width:70%; border-radius:10px; box-shadow:0 4px 15px rgba(0,0,0,0.3);">
</div>

---

## 📌 Overview
- Robo‑Knight themed DX11 screen saver  
- Stubbed GDI / DX11 rendering  
- AVIS‑style comments for AI & Copilot  
- Modular frame update logic  

---

## 📁 File Structure

| File | Description |
|------|-------------|
| `source/avis_main.c` | Entry point |
| `source/avis_screen_saver.c` | Screen saver logic |
| `source/dx11_stub.c` | DX11 stub init/shutdown |
| `source/avis_xinput_stub.c` | Controller stub |
| `source/game_logic.c` | Frame logic |
| `include/*.h` | Headers |
| `output/` | Objects & binaries |

---

## 🚀 Build Instructions
1. Open project in **Pelles C IDE**  
2. Build `mercwar.exe`  
3. Run to see Robo‑Knight demo  

---

© 2026 CGPT / MercWar

<!-- END_SEED MERCG_AVIS_ROBOKNIGHT_2026 -->
<!-- BEGIN_SEED MERCG_AVIS_SCREENSAVER_2026
GUID: AVIS-SCREEN-SAVER-2026
TITLE: AVIS Screen Saver & Game Template Demo – RoboNight
AUTHOR: CGPT / MercWar
DATE: 2026-01-14
-->

# 🚀 AVIS Screen Saver & Game Template Demo – RoboNight

<div style="text-align:center; margin-bottom:16px;">
  <img src="Mercwar_Robo-Knight/MERCWAR_V030.png"
       alt="MercWar Banner"
       style="max-width:80%; border-radius:12px; box-shadow:0 4px 15px rgba(0,0,0,0.3);">
</div>

**DirectX 11 in Standard C** – minimal DX11/GDI screen saver with AVIS comments for AI-assisted coding. 🖥️🎮

---

## 📌 Overview
- 🪟 Window creation & message loop  
- ⚡ DX11 init/shutdown stubs  
- 🌌 Screen saver with moving shapes  
- 🤖 AVIS-style comments for AI parsing  

---

## 📁 File Structure

| File | Description |
|------|-------------|
| `source/avis_main.c` | Main entry & message loop |
| `source/avis_screen_saver.c` | Screen saver + game logic |
| `source/dx11_stub.c` | DX11 stubbed rendering |
| `source/avis_xinput_stub.c` | Controller input stub |
| `source/game_logic.c` | Game update stub |
| `include/*.h` | DX / screen saver / XInput headers |
| `output/` | Compiled objects & executables |

---

## ⚙️ Features
- 💻 AVIS screen saver template  
- 🖌️ Stubbed rendering (GDI fallback)  
- 🔧 Optional debug frames (MessageBox)  
- 🌍 Global management: `g_hDC`, `g_screenWidth`, `g_screenHeight`  

---

## 🚀 Build Instructions
1. Install [Pelles C IDE](https://www.smorgasbordet.com/pellesc/)  
2. Open project folder  
3. Build `mercwar.exe` ✅  
4. Run to see screen saver demo  

---

⚠️ Notes
- Windows 10/11 recommended  
- DirectX headers optional (stubs included)  

<div style="text-align:center; margin-top:20px;">
  <img src="https://raw.githubusercontent.com/mercwar/Cyborg/main/Mercwar_Robo-Knight/Copilot_20260114_020131.png" 
       alt="Screen Saver Demo"
       style="max-width:80%; border-radius:12px; box-shadow:0 4px 15px rgba(0,0,0,0.3);">
</div>

© 2026 CGPT / MercWar

<!-- END_SEED MERCG_AVIS_SCREENSAVER_2026 -->

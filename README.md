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

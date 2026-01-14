<!-- BEGIN_SEED MERCG_AVIS_SCREENSAVER_2026 
GUID: AVIS-SCREEN-SAVER-2026
TITLE: AVIS Screen Saver Demo – Robo-Knight
AUTHOR: CGPT / MercWar
DATE: 2026-01-14
-->

# 🤖 AVIS Screen Saver Demo – Robo-Knight

![Robo-Knight DX Demo](https://raw.githubusercontent.com/mercwar/Cyborg/main/IMAGE%20ARTIFACTS/ner_roboknight.png)

**DirectX in Standard C** – Minimal DX11 setup, screen saver demo, and AVIS-style structured comments for AI-assisted coding. 🖥️⚡

---

## 📌 Overview

This project demonstrates building a **DirectX 11 application in Standard C** using Pelles C, including:

- 🪟 Window creation & message loop  
- ⚡ DX11 initialization and shutdown stubs  
- 🌌 Screen saver logic with frame updates  
- 🎮 XInput controller stubs  
- 🤖 AVIS-style comments for AI & Copilot integration  

---

## 📁 File Structure

| Folder/File | Description |
|------------|------------|
| `source/avis_main.c` | Main entry point and message loop |
| `source/avis_screen_saver.c` | Screen saver logic & rendering |
| `source/dx11_stub.c` | DirectX initialization & shutdown stubs |
| `source/avis_xinput_stub.c` | XInput controller stub |
| `source/game_logic.c` | Game logic stub for demo frames |
| `include/*.h` | Header files for DX stubs, screen saver, game logic, and XInput |
| `output/` | Compiled binaries & object files |

---

## ⚙️ Features

- 💻 Full AVIS Screen Saver Demo – minimal DX11 / GDI fallback  
- 🖌️ Stub Rendering – runs even without real DirectX headers  
- 🔧 Frame Debugging – optional MessageBox per frame  
- 🌍 Cross-file Globals – `g_screenWidth`, `g_screenHeight`, `g_hDC`, etc.  

---

## 🚀 Build Instructions

1. Install [Pelles C IDE](https://www.smorgasbordet.com/pellesc/) 🛠️  
2. Open the project folder in Pelles C IDE 📂  
3. Build `mercwar.exe` using the provided source files ✅  
4. Run the executable to see the screen saver demo with stubbed rendering 🎉  
5. Use **Alt+Tab** to switch windows if DX window captures focus ⌨️  

---

## 📝 AVIS Comments & Copilot Integration

All source files use AVIS-style comments:

- `#main`, `#avis`, `#screensaver`, `#dx11` tags  
- Function purpose documentation included  
- MessageBox debug frames can halt execution for inspection 🛑  

---

## 🌐 Repository

Check out the project on GitHub: [https://github.com/mercwar/Cyborg](https://github.com/mercwar/Cyborg)

---

## 🎨 Screenshots

![Robo-Knight Screen Saver Frame](https://raw.githubusercontent.com/mercwar/Cyborg/main/IMAGE%20ARTIFACTS/ner_roboknight.png)

---

## ⚠️ Notes

- Windows 10/11 recommended  
- Pelles C IDE required  
- DirectX headers optional; stubs allow compilation without them  

---

## 🛠️ License

MIT License – free to use and modify.  

---

&copy; 2026 CGPT / MercWar

<!-- END_SEED MERCG_AVIS_SCREENSAVER_2026 -->

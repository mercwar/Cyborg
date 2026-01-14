<!-- AVIS / Cyborg DirectX Standard C README -->

<h1 style="text-align:center; color:#ffd166; font-size:48px;">🚀 AVIS Screen Saver Demo</h1>

<div style="text-align:center;">
  <img src="https://raw.githubusercontent.com/mercwar/Cyborg/main/IMAGE%20ARTIFACTS/a%20futuristic%20armored4.png" 
       alt="Cyborg DX Demo" style="max-width:80%; border-radius:12px; box-shadow: 0 4px 15px rgba(0,0,0,0.3);">
</div>

<p style="font-size:18px; text-align:center; margin-top:12px;">
<strong>DirectX in Standard C</strong> – Minimal DX11 setup, screen saver demo, and AVIS-style structured comments for AI-assisted coding. 🖥️🎮
</p>

<hr style="border:1px solid #ffd166;">

<h2 style="color:#06d6a0;">📌 Overview</h2>
<p>This project demonstrates building a <strong>DirectX 11 application in Standard C</strong> using Pelles C, including:</p>
<ul>
  <li>Window creation & message loop 🪟</li>
  <li>DX11 initialization and shutdown stubs ⚡</li>
  <li>Screen saver logic with frame updates 🌌</li>
  <li>XInput controller stubs 🎮</li>
  <li>AVIS-style comments for AI & Copilot integration 🤖</li>
</ul>

<h2 style="color:#06d6a0;">📁 File Structure</h2>
<table style="width:100%; border-collapse:collapse;">
  <tr style="background-color:#ffd166; color:#073b4c;">
    <th>Folder/File</th>
    <th>Description</th>
  </tr>
  <tr>
    <td>source/avis_main.c</td>
    <td>Main entry point and message loop</td>
  </tr>
  <tr style="background-color:#f1f1f1;">
    <td>source/avis_screen_saver.c</td>
    <td>Screen saver logic & rendering</td>
  </tr>
  <tr>
    <td>source/dx11_stub.c</td>
    <td>DirectX initialization & shutdown stubs</td>
  </tr>
  <tr style="background-color:#f1f1f1;">
    <td>source/avis_xinput_stub.c</td>
    <td>XInput controller stub</td>
  </tr>
  <tr>
    <td>source/game_logic.c</td>
    <td>Game logic stub for demo frames</td>
  </tr>
  <tr style="background-color:#f1f1f1;">
    <td>include/*.h</td>
    <td>Header files for DX stubs, screen saver, game logic, and XInput</td>
  </tr>
  <tr>
    <td>output/</td>
    <td>Compiled binaries & object files</td>
  </tr>
</table>

<h2 style="color:#06d6a0;">⚙️ Features</h2>
<ul>
  <li>💻 Full AVIS Screen Saver Demo – minimal DX11 / GDI fallback</li>
  <li>🖌️ Stub Rendering – runs even without real DirectX headers</li>
  <li>🔧 Frame Debugging – optional MessageBox per frame</li>
  <li>🌍 Cross-file Globals – g_screenWidth, g_screenHeight, g_hDC, etc.</li>
</ul>

<h2 style="color:#06d6a0;">🚀 Build Instructions</h2>
<ol>
  <li>Install <a href="https://www.smorgasbordet.com/pellesc/" target="_blank">Pelles C IDE</a> 🛠️</li>
  <li>Open the project folder in Pelles C IDE 📂</li>
  <li>Build <code>mercwar.exe</code> using the provided source files ✅</li>
  <li>Run the executable to see the screen saver demo with stubbed rendering 🎉</li>
  <li>Use <strong>Alt+Tab</strong> to switch windows if DX window captures focus ⌨️</li>
</ol>

<h2 style="color:#06d6a0;">📝 AVIS Comments & Copilot Integration</h2>
<p>All source files use AVIS-style comments:</p>
<ul>
  <li>#main, #dx11, #avis, #screensaver tags</li>
  <li>Function purpose documentation included</li>
  <li>MessageBox debug frames can halt execution for inspection 🛑</li>
</ul>

<h2 style="color:#06d6a0;">🌐 Repository</h2>
<p>Check out the project on GitHub: <a href="https://github.com/mercwar/Cyborg" target="_blank">https://github.com/mercwar/Cyborg</a></p>

<h2 style="color:#06d6a0;">🎨 Screenshots</h2>
<div style="display:flex; justify-content:center;">
  <img src="https://raw.githubusercontent.com/mercwar/Cyborg/main/IMAGE%20ARTIFACTS/a%20futuristic%20armored4.png" 
       alt="Screen Saver Frame" style="max-width:60%; border-radius:10px; margin:10px; box-shadow: 0 4px 15px rgba(0,0,0,0.3);">
</div>

<h2 style="color:#06d6a0;">⚠️ Notes</h2>
<ul>
  <li>Windows 10/11 recommended</li>
  <li>Pelles C IDE required</li>
  <li>DirectX headers optional; stubs allow compilation without them</li>
</ul>

<h2 style="color:#06d6a0;">🛠️ License</h2>
<p>MIT License – free to use and modify.</p>

<hr style="border:1px solid #ffd166;">
<p style="text-align:center; color:#06d6a0;">&copy; 2026 CGPT / MercWar</p>

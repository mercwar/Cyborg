@echo off
setlocal enabledelayedexpansion
title COMET.BAT - Clipboard Batch Tool

:: ====================================================
:: CONFIGURATION
:: ====================================================
set "TOOLS_DIR=G:\BLUE_DISK\TOOLS"
set "DEFAULT_NAME=CLIPBOARD_SCRIPT"
set "PSCLIP=powershell -NoLogo -NoProfile -Command"

if not exist "%TOOLS_DIR%" (
    md "%TOOLS_DIR%" 2>nul
)

:: ====================================================
:: MAIN MENU LOOP
:: ====================================================
:main_menu
cls
echo ============================
echo          COMET MENU
echo ============================
echo  Use UP/DOWN ARROWS, ENTER
echo  or press Q to quit.
echo.
set "menu[0]=Copy clipboard to .BAT"
set "menu[1]=Quit"
set "menu.count=2"
set "sel=0"

:draw_menu
cls
echo ============================
echo          COMET MENU
echo ============================
echo  Use UP/DOWN ARROWS, ENTER
echo  or press Q to quit.
echo.

for /L %%I in (0,1,1) do (
    if "%%I"=="!sel!" (
        echo   ^> !menu[%%I]!
    ) else (
        echo     !menu[%%I]!
    )
)

call :read_key
if /i "!key!"=="UP" (
    if !sel! gtr 0 set /a sel-=1
    goto draw_menu
)
if /i "!key!"=="DOWN" (
    if !sel! lss !menu.count!-1 set /a sel+=1
    goto draw_menu
)
if /i "!key!"=="ENTER" goto do_action
if /i "!key!"=="Q" goto :eof
goto draw_menu

:: ====================================================
:: HANDLE MENU SELECTION
:: ====================================================
:do_action
if "!sel!"=="0" goto action_clip_to_bat
if "!sel!"=="1" goto :eof
goto main_menu

:: ====================================================
:: ACTION: SAVE CLIPBOARD AS .BAT
:: ====================================================
:action_clip_to_bat
cls
echo ============================
echo  SAVE CLIPBOARD TO .BAT
echo ============================
echo This will read text from the
echo Windows clipboard and save it
echo as a batch file in:
echo   %TOOLS_DIR%
echo.
set "fname="
set /p "fname=Enter file name (no extension) or press ENTER for %DEFAULT_NAME%: "

if "%fname%"=="" set "fname=%DEFAULT_NAME%"
set "out=%TOOLS_DIR%\%fname%.bat"

echo.
echo Reading clipboard and writing:
echo   "%out%"
echo.

:: Use PowerShell to dump clipboard text as UTF-8
%PSCLIP% ^
  "Add-Type -AssemblyName System.Windows.Forms;[Windows.Forms.Clipboard]::GetText()" ^
  > "%out%"

if errorlevel 1 (
    echo.
    echo ERROR: Could not read clipboard or write file.
    echo Ensure clipboard has text and PowerShell is available.
    pause
    goto main_menu
)

echo.
echo Done. File created:
echo   "%out%"
echo.
pause
goto main_menu

:: ====================================================
:: READ KEY (ARROW / ENTER / Q) USING POWERSHELL
:: ====================================================
:read_key
set "key="
for /f "usebackq delims=" %%K in (`%PSCLIP% "$k=$Host.UI.RawUI.ReadKey('NoEcho,IncludeKeyDown');$k.VirtualKeyCode"` ) do (
    set "vk=%%K"
)

:: Map VK codes:
:: 38 = UpArrow, 40 = DownArrow, 13 = Enter, 81 = Q, 27 = Esc
if "%vk%"=="38" (set "key=UP"    & goto :eof)
if "%vk%"=="40" (set "key=DOWN"  & goto :eof)
if "%vk%"=="13" (set "key=ENTER" & goto :eof)
if "%vk%"=="81" (set "key=Q"     & goto :eof)
if "%vk%"=="27" (set "key=Q"     & goto :eof)

goto :read_key

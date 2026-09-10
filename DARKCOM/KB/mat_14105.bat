@echo off
setlocal EnableDelayedExpansion
echo ============================================
echo        DARKCOM SHORTCUT + LAUNCHER
echo ============================================
echo.
set "INDEX=G:\Darkcom\KB\index.txt"
set "TARGET=CBORG-G::DARKCOM-LAUNCHER-1.0"
set "FOUND="
echo Creating DARKCOM shortcut...
echo @echo off> "G:\Darkcom\DARKCOM_SHORTCUT.BAT"
echo call G:\Darkcom\KB\mat_launcher.bat>> "G:\Darkcom\DARKCOM_SHORTCUT.BAT"
echo Shortcut created at G:\Darkcom\DARKCOM_SHORTCUT.BAT
echo.
echo Searching for DARKCOM LAUNCHER in KB...
for /f "usebackq tokens=1-6 delims=|" %%A in ("%INDEX%") do (
    set "GUID=%%A"
    set "MATFILE=%%C"
    rem Trim leading spaces
    set "G="
    for /l %%i in (1,1,50) do if "~0,1G:~1"
    if /i ""=="" (
        set "FOUND=1"
        echo Running DARKCOM LAUNCHER...
        call ""
    )
)
if not defined FOUND (
    echo [ERROR] DARKCOM LAUNCHER not found in KB.
    pause
)

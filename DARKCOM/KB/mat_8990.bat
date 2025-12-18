@echo off
setlocal
set "ROOT=G:\Darkcom"
set "KB=%ROOT%\KB"
set "SHORT=%ROOT%\Shortcuts"
if not exist "%SHORT%" mkdir "%SHORT%"
echo ============================================
echo        DARKCOM SHORTCUT SERVICE v1
echo ============================================
echo.
echo Creating shortcut for latest shell...
:: Find last shell entry
set "TARGET="
for /f "usebackq delims=" %%L in ("%KB%\index.txt") do (
    echo %%L | findstr /i "SHELL" >nul
    if not errorlevel 1 (
        for /f "tokens=3 delims=|" %%X in ("%%L") do set "TARGET=%%X"
    )
)
if not defined TARGET (
    echo No shell found in KB.
    pause
    exit /b
)
set "OUT=%SHORT%\DARKCOM_SHELL_SHORTCUT.BAT"
echo @echo off> "%OUT%"
echo call "%TARGET%">> "%OUT%"
echo Shortcut created:
echo   %OUT%
echo.
pause

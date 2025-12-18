@echo off
setlocal
title DARKCOM SHELL 7.0 - CLIENT SUPPORT + CLIPBOARD
set "ROOT=G:\Darkcom"
set "KB=%ROOT%\KB"
set "INDEX=%KB%\index.txt"
:main
cls
echo ============================================
echo            DARKCOM SHELL 7.0
echo ============================================
echo ROOT: %ROOT%
echo KB:   %KB%
echo.
echo 1. List KB Artifacts
echo 2. Run Artifact (choose by number)
echo 3. Clipboard Tools
echo 4. Shortcut Tools
echo 5. Exit
echo.
set /p choice=Choose:
if "%choice%"=="1" goto list
if "%choice%"=="2" goto run
if "%choice%"=="3" goto clip
if "%choice%"=="4" goto short
if "%choice%"=="5" exit /b
goto main
:list
cls
echo ============================================
echo           KB ARTIFACT LIST
echo ============================================
echo.
set /a n=0
for /f "usebackq delims=" %%L in ("%INDEX%") do (
    set /a n+=1
    echo : %%L
)
echo.
pause
goto main
:run
cls
echo ============================================
echo        RUN ARTIFACT BY NUMBER
echo ============================================
echo.
set /a n=0
for /f "usebackq delims=" %%L in ("%INDEX%") do (
    set /a n+=1
    echo : %%L
)
echo.
set /p pick=Enter number:
set /a n=0
set "FILE="
for /f "usebackq delims=" %%L in ("%INDEX%") do (
    set /a n+=1
    if ""=="%pick%" (
        for /f "tokens=3 delims=|" %%X in ("%%L") do set "FILE=%%X"
    )
)
if not defined FILE (
    echo Invalid selection.
    pause
    goto main
)
echo Running: %FILE%
call %FILE%
goto main
:clip
cls
echo ============================================
echo             CLIPBOARD TOOLS
echo ============================================
echo.
echo 1. Import Clipboard to KB
echo 2. Return to Main Menu
echo.
set /p c=Choose:
if "%c%"=="1" goto clip_run
if "%c%"=="2" goto main
goto clip
:clip_run
cls
echo Running clipboard importer...
echo.
:: Find clipboard artifact
set "FILE="
for /f "usebackq delims=" %%L in ("%INDEX%") do (
    echo %%L | findstr /i "CLIPBOARD" >nul
    if not errorlevel 1 (
        for /f "tokens=3 delims=|" %%X in ("%%L") do set "FILE=%%X"
    )
)
if not defined FILE (
    echo Clipboard artifact not found.
    pause
    goto clip
)
call "%FILE%"
goto clip
:short
cls
echo ============================================
echo             SHORTCUT TOOLS
echo ============================================
echo.
echo 1. Create Shell Shortcut
echo 2. Return to Main Menu
echo.
set /p s=Choose:
if "%s%"=="1" goto short_run
if "%s%"=="2" goto main
goto short
:short_run
cls
echo Running shortcut service...
echo.
set "FILE="
for /f "usebackq delims=" %%L in ("%INDEX%") do (
    echo %%L | findstr /i "SHORTCUT-SERVICE" >nul
    if not errorlevel 1 (
        for /f "tokens=3 delims=|" %%X in ("%%L") do set "FILE=%%X"
    )
)
if not defined FILE (
    echo Shortcut service not found.
    pause
    goto short
)
call "%FILE%"
goto short

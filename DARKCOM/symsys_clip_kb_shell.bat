@echo off
setlocal EnableDelayedExpansion

:: ============================================================
::  SYMSYS SHELL v3.0  —  CLEAN + FILE-TYPE AWARE
::  PURPOSE:
::      - Load artifacts from clipboard
::      - Parse GUID / TYPE / VERSION
::      - Store full artifacts in KB
::      - Materialize CONTENT into correct file types
::      - Use safe KB root in user profile
:: ============================================================

:: ---------------- CONFIG ----------------

set "WRAPPER_VERSION=3.0.0"
set "KB_ROOT=%USERPROFILE%\SYMSYS_KB"
set "KB_INDEX=%KB_ROOT%\index.txt"

if not exist "%KB_ROOT%" mkdir "%KB_ROOT%"
if not exist "%KB_INDEX%" (
    echo ; SYMSYS ARTIFACT KB INDEX > "%KB_INDEX%"
    echo ; GUID ^| RAWFILE ^| MATERIALIZED ^| TYPE ^| DATE ^| VERSION >> "%KB_INDEX%"
)

:: ---------------- MENU ----------------

:MENU
cls
echo ============================================
echo SYMSYS SHELL v3.0
echo KB root: %KB_ROOT%
echo ============================================
echo 1. Load artifact from clipboard
echo 2. Print clipboard
echo 3. List KB index
echo 4. Exit
echo ============================================
set /p CH=Choose:

if "%CH%"=="1" goto LOADCLIP
if "%CH%"=="2" goto PRINTCLIP
if "%CH%"=="3" goto LISTKB
if "%CH%"=="4" exit /b
goto MENU

:: ---------------- LOAD CLIPBOARD ----------------

:LOADCLIP
cls
echo [SYMSYS] Reading clipboard...
powershell -command "try { Get-Clipboard -Raw } catch { '' }" > "%temp%\symsys_clip.txt"

for %%Z in ("%temp%\symsys_clip.txt") do if %%~zZ==0 (
    echo [SYMSYS] Clipboard is empty.
    pause
    goto MENU
)

findstr /i "ARTIFACT::" "%temp%\symsys_clip.txt" >nul
if errorlevel 1 (
    echo [SYMSYS] Clipboard is not a SYMSYS artifact.
    pause
    goto MENU
)

goto PARSE_HEADER

:: ---------------- PARSE HEADER ----------------

:PARSE_HEADER
set "ART_GUID=UNKNOWN"
set "ART_TYPE=UNKNOWN"
set "ART_VERSION=UNKNOWN"

for /f "tokens=1,* delims=:" %%A in ('findstr /i "GUID::" "%temp%\symsys_clip.txt"') do set "ART_GUID=%%B"
for /f "tokens=1,* delims=:" %%A in ('findstr /i "TYPE::" "%temp%\symsys_clip.txt"') do set "ART_TYPE=%%B"
for /f "tokens=1,* delims=:" %%A in ('findstr /i "VERSION::" "%temp%\symsys_clip.txt"') do set "ART_VERSION=%%B"

set "ART_GUID=%ART_GUID: =%"
set "ART_TYPE=%ART_TYPE: =%"
set "ART_VERSION=%ART_VERSION: =%"

echo [SYMSYS] Artifact GUID: %ART_GUID%
echo [SYMSYS] Artifact TYPE: %ART_TYPE%
echo [SYMSYS] Artifact VERSION: %ART_VERSION%
echo.

:: ---------------- DETERMINE EXTENSION ----------------

set "EXT=.txt"
if /I "%ART_TYPE%"=="BATCH_WRAPPER" set "EXT=.bat"
if /I "%ART_TYPE%"=="SOURCE_SNIPPET" set "EXT=.bat"

echo [SYMSYS] Materialized extension: %EXT%
echo.
echo 1. Install artifact to KB
echo 2. Cancel
set /p MODE=Choose:

if "%MODE%"=="1" goto INSTALL
goto MENU

:: ---------------- INSTALL ARTIFACT ----------------

:INSTALL
cls
echo [SYMSYS] Installing artifact...

set "STAMP=%RANDOM%"
set "RAW_FILE=%KB_ROOT%\artifact_%STAMP%.art"
copy "%temp%\symsys_clip.txt" "%RAW_FILE%" >nul

if errorlevel 1 (
    echo [SYMSYS] ERROR: Could not write raw artifact.
    pause
    goto MENU
)

echo [SYMSYS] Raw artifact saved as:
echo     %RAW_FILE%

set "MAT_FILE=%KB_ROOT%\mat_%STAMP%%EXT%"
call :EXTRACT_CONTENT "%RAW_FILE%" "%MAT_FILE%"

if not exist "%MAT_FILE%" (
    echo [SYMSYS] ERROR: Materialized file not created.
    pause
    goto MENU
)

echo [SYMSYS] Materialized file created:
echo     %MAT_FILE%

for /f "tokens=1 delims=." %%A in ('wmic os get LocalDateTime ^| find "."') do set NOW=%%A
set "DATE=!NOW:~0,4!-!NOW:~4,2!-!NOW:~6,2!"

echo %ART_GUID% ^| %RAW_FILE% ^| %MAT_FILE% ^| %ART_TYPE% ^| %DATE% ^| %ART_VERSION%>> "%KB_INDEX%"

echo.
echo [SYMSYS] Artifact installed successfully.
pause
goto MENU

:: ---------------- EXTRACT CONTENT ----------------

:EXTRACT_CONTENT
setlocal EnableDelayedExpansion
set "IN=0"
set "SRC=%~1"
set "OUT=%~2"

if exist "%OUT%" del "%OUT%" >nul

for /f "usebackq delims=" %%L in ("%SRC%") do (
    set "LINE=%%L"
    if /I "!LINE!"=="CONTENT::" (
        set "IN=1"
    ) else if /I "!LINE!"=="END_CONTENT" (
        set "IN=0"
        goto :done
    ) else (
        if "!IN!"=="1" (
            >> "%OUT%" echo !LINE!
        )
    )
)

:done
endlocal & exit /b

:: ---------------- PRINT CLIPBOARD ----------------

:PRINTCLIP
cls
powershell -command "try { Get-Clipboard -Raw } catch { '' }"
pause
goto MENU

:: ---------------- LIST KB ----------------

:LISTKB
cls
type "%KB_INDEX%"
pause
goto MENU
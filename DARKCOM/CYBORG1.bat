@echo off
setlocal EnableDelayedExpansion

:: ============================================================
::  CBORG SHELL v3.1 — FULL STANDALONE SHELL
::  ROOTED AT: G:\Darkcom\KB
:: ============================================================

:: ---------------- CONFIG ----------------
set "WRAPPER_VERSION=3.1.0"
set "KB_ROOT=G:\Darkcom\KB"
set "KB_INDEX=%KB_ROOT%\index.txt"

if not exist "%KB_ROOT%" mkdir "%KB_ROOT%"
if not exist "%KB_INDEX%" (
    echo ; SYMSYS ARTIFACT KB INDEX > "%KB_INDEX%"
    echo ; GUID ^| RAWFILE ^| MATERIALIZED ^| TYPE ^| DATE ^| VERSION >> "%KB_INDEX%"
)

set "SYMSYS_EXT_DEFAULT=.txt"
set "SYMSYS_EXT_BATCH_WRAPPER=.bat"
set "SYMSYS_EXT_SOURCE_SNIPPET=.bat"
set "SYMSYS_EXT_CLIPBOARD_ARTIFACT=.txt"

:: ---------------- MAIN MENU ----------------
:MENU
cls
echo ============================================================
echo                     CBORG SHELL v3.1
echo ============================================================
echo KB Root: %KB_ROOT%
echo.
echo 1. Load artifact from clipboard
echo 2. Print clipboard
echo 3. List KB index
echo 4. Exit
echo ============================================================
set /p CH=Choose:

if "%CH%"=="1" goto LOADCLIP
if "%CH%"=="2" goto PRINTCLIP
if "%CH%"=="3" goto LISTKB
if "%CH%"=="4" exit /b
goto MENU

:: ---------------- LOAD CLIPBOARD ----------------
:LOADCLIP
cls
echo [CBORG] Reading clipboard...
powershell -command "try { Get-Clipboard -Raw } catch { '' }" > "%temp%\cborg_clip.txt"

for %%Z in ("%temp%\cborg_clip.txt") do if %%~zZ==0 (
    echo [CBORG] Clipboard is empty.
    pause
    goto MENU
)

findstr /i "ARTIFACT::" "%temp%\cborg_clip.txt" >nul
if errorlevel 1 (
    echo [CBORG] Clipboard does not contain a SYMSYS artifact.
    pause
    goto MENU
)

goto PARSE_HEADER

:: ---------------- PARSE HEADER ----------------
:PARSE_HEADER
set "ART_GUID=UNKNOWN"
set "ART_TYPE=UNKNOWN"
set "ART_VERSION=UNKNOWN"

for /f "tokens=1,* delims=:" %%A in ('findstr /i "GUID::" "%temp%\cborg_clip.txt"') do set "ART_GUID=%%B"
for /f "tokens=1,* delims=:" %%A in ('findstr /i "TYPE::" "%temp%\cborg_clip.txt"') do set "ART_TYPE=%%B"
for /f "tokens=1,* delims=:" %%A in ('findstr /i "VERSION::" "%temp%\cborg_clip.txt"') do set "ART_VERSION=%%B"

set "ART_GUID=%ART_GUID: =%"
set "ART_TYPE=%ART_TYPE: =%"
set "ART_VERSION=%ART_VERSION: =%"

echo [CBORG] Artifact GUID: %ART_GUID%
echo [CBORG] Artifact TYPE: %ART_TYPE%
echo [CBORG] Artifact VERSION: %ART_VERSION%
echo.

goto RESOLVE_EXT

:: ---------------- RESOLVE EXTENSION ----------------
:RESOLVE_EXT
set "EXT=%SYMSYS_EXT_DEFAULT%"
if /I "%ART_TYPE%"=="BATCH_WRAPPER" set "EXT=%SYMSYS_EXT_BATCH_WRAPPER%"
if /I "%ART_TYPE%"=="SOURCE_SNIPPET" set "EXT=%SYMSYS_EXT_SOURCE_SNIPPET%"
if /I "%ART_TYPE%"=="CLIPBOARD_ARTIFACT" set "EXT=%SYMSYS_EXT_CLIPBOARD_ARTIFACT%"

echo [CBORG] Materialized extension: %EXT%
echo.
echo 1. Install artifact to KB
echo 2. Cancel
set /p MODE=Choose:

if "%MODE%"=="1" goto INSTALL
goto MENU

:: ---------------- INSTALL ARTIFACT ----------------
:INSTALL
cls
echo [CBORG] Installing artifact...

set "STAMP=%RANDOM%"
set "RAW_FILE=%KB_ROOT%\artifact_%STAMP%.art"
copy "%temp%\cborg_clip.txt" "%RAW_FILE%" >nul

if errorlevel 1 (
    echo [CBORG] ERROR: Could not write raw artifact.
    pause
    goto MENU
)

echo [CBORG] Raw artifact saved as:
echo     %RAW_FILE%

set "MAT_FILE=%KB_ROOT%\mat_%STAMP%%EXT%"
call :EXTRACT_CONTENT "%RAW_FILE%" "%MAT_FILE%"

if not exist "%MAT_FILE%" (
    echo [CBORG] ERROR: Materialized file not created.
    pause
    goto MENU
)

echo [CBORG] Materialized file created:
echo     %MAT_FILE%

for /f "tokens=1 delims=." %%A in ('wmic os get LocalDateTime ^| find "."') do set NOW=%%A
set "DATE=!NOW:~0,4!-!NOW:~4,2!-!NOW:~6,2!"

echo %ART_GUID% ^| %RAW_FILE% ^| %MAT_FILE% ^| %ART_TYPE% ^| %DATE% ^| %ART_VERSION%>> "%KB_INDEX%"

echo.
echo [CBORG] Artifact installed successfully.
pause
goto MENU

:: ---------------- CONTENT EXTRACTOR ----------------
:EXTRACT_CONTENT
setlocal EnableDelayedExpansion
set "IN=0"
set "SRC=%~1"
set "OUT=%~2"

if exist "!OUT!" del "!OUT!" >nul

for /f "usebackq delims=" %%L in ("!SRC!") do (
    set "LINE=%%L"
    if /I "!LINE!"=="CONTENT::" (
        set "IN=1"
    ) else if /I "!LINE!"=="END_CONTENT" (
        set "IN=0"
        goto :done
    ) else (
        if "!IN!"=="1" (
            >> "!OUT!" echo !LINE!
        )
    )
)

:done
endlocal & exit /b

:: ---------------- PRINT CLIPBOARD ----------------
:PRINTCLIP
cls
powershell -command "try { Get-Clipboard -Raw } catch { '' }"
echo.
pause
goto MENU

:: ---------------- LIST KB ----------------
:LISTKB
cls
type "%KB_INDEX%"
echo.
pause
goto MENU
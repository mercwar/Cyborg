@echo off
setlocal EnableDelayedExpansion

:: ============================================================
::  SYMSYS SHELL v3.1  —  G:\Darkcom\KB ROOTED
:: ============================================================

call :SYMSYS_CONFIG_V31

:MENU
cls
echo ============================================
echo SYMSYS SHELL v3.1
echo KB root: %KB_ROOT%
echo Index : %KB_INDEX%
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

:LOADCLIP
cls
call :DRV_CLIPBOARD_READ
call :DRV_ARTIFACT_PARSE_HEADER
echo.
echo 1. Install artifact to KB
echo 2. Cancel
set /p MODE=Choose:

if "%MODE%"=="1" call :DRV_ARTIFACT_INSTALL
goto MENU

:PRINTCLIP
cls
powershell -command "try { Get-Clipboard -Raw } catch { '' }"
echo.
pause
goto MENU

:LISTKB
cls
if exist "%KB_INDEX%" (
    type "%KB_INDEX%"
) else (
    echo [SYMSYS] KB index does not exist: %KB_INDEX%
)
echo.
pause
goto MENU

:: ================== CONFIG FROM JSON SPEC ===================

:SYMSYS_CONFIG_V31
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
goto :eof

:: =================== DRIVERS FROM JSON SPEC =================

:DRV_CLIPBOARD_READ
echo [SYMSYS] Reading clipboard...
powershell -command "try { Get-Clipboard -Raw } catch { '' }" > "%temp%\symsys_clip.txt"

for %%Z in ("%temp%\symsys_clip.txt") do if %%~zZ==0 (
    echo [SYMSYS] Clipboard is empty.
    pause
    goto MENU
)
goto :eof

:DRV_ARTIFACT_PARSE_HEADER
set "ART_GUID=UNKNOWN"
set "ART_TYPE=UNKNOWN"
set "ART_VERSION=UNKNOWN"

findstr /i "ARTIFACT::" "%temp%\symsys_clip.txt" >nul
if errorlevel 1 (
    echo [SYMSYS] Clipboard is not a SYMSYS artifact.
    pause
    goto MENU
)

for /f "tokens=1,* delims=:" %%A in ('findstr /i "GUID::" "%temp%\symsys_clip.txt"') do set "ART_GUID=%%B"
for /f "tokens=1,* delims=:" %%A in ('findstr /i "TYPE::" "%temp%\symsys_clip.txt"') do set "ART_TYPE=%%B"
for /f "tokens=1,* delims=:" %%A in ('findstr /i "VERSION::" "%temp%\symsys_clip.txt"') do set "ART_VERSION=%%B"

set "ART_GUID=%ART_GUID: =%"
set "ART_TYPE=%ART_TYPE: =%"
set "ART_VERSION=%ART_VERSION: =%"

echo [SYMSYS] Artifact GUID: %ART_GUID%
echo [SYMSYS] Artifact TYPE: %ART_TYPE%
echo [SYMSYS] Artifact VERSION: %ART_VERSION%
goto :eof

:DRV_ARTIFACT_RESOLVE_EXT
set "EXT=%SYMSYS_EXT_DEFAULT%"
if /I "%ART_TYPE%"=="BATCH_WRAPPER" set "EXT=%SYMSYS_EXT_BATCH_WRAPPER%"
if /I "%ART_TYPE%"=="SOURCE_SNIPPET" set "EXT=%SYMSYS_EXT_SOURCE_SNIPPET%"
if /I "%ART_TYPE%"=="CLIPBOARD_ARTIFACT" set "EXT=%SYMSYS_EXT_CLIPBOARD_ARTIFACT%"
echo [SYMSYS] Materialized extension: %EXT%
goto :eof

:DRV_ARTIFACT_MATERIALIZE
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
        goto :mat_done
    ) else (
        if "!IN!"=="1" (
            >> "!OUT!" echo !LINE!
        )
    )
)

:mat_done
endlocal & exit /b

:DRV_ARTIFACT_INSTALL
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

call :DRV_ARTIFACT_RESOLVE_EXT
set "MAT_FILE=%KB_ROOT%\mat_%STAMP%%EXT%"
call :DRV_ARTIFACT_MATERIALIZE "%RAW_FILE%" "%MAT_FILE%"

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
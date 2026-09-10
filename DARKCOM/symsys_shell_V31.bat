@echo off
setlocal enabledelayedexpansion

:: ============================================================
::  SYMSYS WRAPPER SHELL v1.0
::  FILE: symsys_shell.bat
::  VERSION: v1.0.0
::  UPDATED: 2025-01-17
::  AUTHOR: Demon
::  SYMDISK: SYMDISK_01
::  SUBSYSTEM: CBORG_VM / ARTIFACT_ENGINE / CLIPBOARD
:: ------------------------------------------------------------
::  PURPOSE:
::      Unified batch shell with Cyborg-G artifact detection,
::      clipboard loader, KB writer, and DOSKEY command layer.
::
::  ARTIFACT #1 (MANDATORY - BAT FILE ONLY):
::      ARTIFACT::symsys_shell.bat
::          GUID::CYBORG-G::SRC-BATCH-SHELL-SYMDISK01-0001
::          TYPE::BATCH_FILE
::          STATUS::ACTIVE
::          NOTES::Primary wrapper shell
::      END ARTIFACT
::
::  ARTIFACT #2 (OPTIONAL - SOURCE SNIPPET KB):
::      ARTIFACT::ARTIFACTS.LANGUAGES.BATCH.SNIPPETS
::          GUID::CYBORG-G::SRC-BATCH-SNIP-SYMDISK01-<AUTO>
::          TYPE::SOURCE_SNIPPET
::          LANGUAGE::BATCH
::          STATUS::KB
::          NOTES::Stored in /KB/
::      END ARTIFACT
:: ============================================================

:: Create KB directory if missing
if not exist "%~dp0KB" mkdir "%~dp0KB"

:: ------------------------------------------------------------
:: DOSKEY COMMANDS
:: ------------------------------------------------------------
doskey clip=getclip
doskey putclip=setclip
doskey artifact=call "%~f0" artifact $*
doskey kb=call "%~f0" kb $*
doskey shell=call "%~f0" menu

:: ------------------------------------------------------------
:: MAIN ENTRY
:: ------------------------------------------------------------
if "%1"=="" goto MENU
goto %1

:: ------------------------------------------------------------
:: MENU
:: ------------------------------------------------------------
:MENU
cls
echo ============================================
echo SYMSYS WRAPPER SHELL
echo ============================================
echo 1. Load artifact from clipboard
echo 2. Print clipboard
echo 3. Write clipboard to KB
echo 4. Create new artifact
echo 5. List KB
echo 6. Exit
echo ============================================
set /p CH=Choose:

if "%CH%"=="1" goto LOAD_CLIP
if "%CH%"=="2" goto PRINT_CLIP
if "%CH%"=="3" goto WRITE_KB
if "%CH%"=="4" goto NEW_ARTIFACT
if "%CH%"=="5" goto LIST_KB
if "%CH%"=="6" exit /b
goto MENU

:: ------------------------------------------------------------
:: LOAD ARTIFACT FROM CLIPBOARD
:: ------------------------------------------------------------
:LOAD_CLIP
powershell -command "Get-Clipboard" > "%temp%\clip.txt"

findstr /i "CYBORG-G::" "%temp%\clip.txt" >nul
if %errorlevel%==0 (
    echo Cyborg-G artifact detected.
    set TARGET="%~dp0KB\artifact_%random%.txt"
    copy "%temp%\clip.txt" %TARGET% >nul
    echo Installed artifact as %TARGET%
    pause
    goto MENU
)

echo No Cyborg-G signature found.
pause
goto MENU

:: ------------------------------------------------------------
:: PRINT CLIPBOARD
:: ------------------------------------------------------------
:PRINT_CLIP
powershell -command "Get-Clipboard"
pause
goto MENU

:: ------------------------------------------------------------
:: WRITE CLIPBOARD TO KB
:: ------------------------------------------------------------
:WRITE_KB
powershell -command "Get-Clipboard" > "%temp%\clip.txt"
set TARGET="%~dp0KB\snippet_%random%.txt"
copy "%temp%\clip.txt" %TARGET% >nul
echo Saved clipboard snippet to %TARGET%
pause
goto MENU

:: ------------------------------------------------------------
:: CREATE NEW ARTIFACT
:: ------------------------------------------------------------
:NEW_ARTIFACT
set /p NAME=Artifact name:
set FILE="%~dp0KB\%NAME%.txt"

echo ARTIFACT::ARTIFACTS.LANGUAGES.BATCH.SNIPPETS > %FILE%
echo     GUID::CYBORG-G::SRC-BATCH-SNIP-SYMDISK01-%random% >> %FILE%
echo     TYPE::SOURCE_SNIPPET >> %FILE%
echo     LANGUAGE::BATCH >> %FILE%
echo     STATUS::NEW >> %FILE%
echo     CONTENT:: >> %FILE%
echo         <EMPTY> >> %FILE%
echo     END_CONTENT >> %FILE%
echo END ARTIFACT >> %FILE%

echo Created artifact: %FILE%
pause
goto MENU

:: ------------------------------------------------------------
:: LIST KB
:: ------------------------------------------------------------
:LIST_KB
dir "%~dp0KB"
pause
goto MENU
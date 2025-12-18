@echo off
setlocal EnableDelayedExpansion
:: Enable DOSKEY history and arrow recall
doskey /listsize=50
doskey /history
title DARKCOM SHELL v3.0
set "KB=G:\Darkcom\KB"
set "INDEX=%KB%\index.txt"
:main
cls
echo ============================================
echo            DARKCOM SHELL v3.0
echo ============================================
echo KB Root: %KB%
echo.
echo 1. List KB Artifacts
echo 2. Run Artifact by GUID (auto-select latest version)
echo 3. Exit
echo.
set /p choice=Choose:
if "%choice%"=="1" goto list
if "%choice%"=="2" goto run
if "%choice%"=="3" exit /b
goto main
:list
cls
echo ============================================
echo           DARKCOM KB ARTIFACT LIST
echo ============================================
echo.
for /f "usebackq tokens=1-6 delims=|" %%A in ("%INDEX%") do (
    set "GUID=%%A"
    set "ARTFILE=%%B"
    set "MATFILE=%%C"
    set "TYPE=%%D"
    set "DATE=%%E"
    set "VER=%%F"
    rem Trim leading spaces
    for %%X in (GUID ARTFILE MATFILE TYPE DATE VER) do (
        set "VAL="
        for /l %%i in (1,1,50) do if "~0,1VAL:~1"
        set "%%X="
    )
    if not "~0,1"==";" (
        echo GUID: 
        echo TYPE: 
        echo VERSION: 
        echo MATERIALIZED: 
        echo --------------------------------------------
    )
)
echo.
pause
goto main
:run
cls
echo ============================================
echo        RUN ARTIFACT BY GUID (LATEST)
echo ============================================
echo.
set /p target=Enter GUID prefix (ex: CBORG-G::PARSER):
set "BEST_VER=0"
set "BEST_FILE="
for /f "usebackq tokens=1-6 delims=|" %%A in ("%INDEX%") do (
    set "GUID=%%A"
    set "MATFILE=%%C"
    set "VER=%%F"
    rem Trim
    set "G="
    set "V="
    for /l %%i in (1,1,50) do if "~0,1G:~1"
    for /l %%i in (1,1,50) do if "~0,1V:~1"
    rem Match prefix
    echo  | findstr /i "%target%" >nul
    if not errorlevel 1 (
        rem Compare versions numerically
        for /f "tokens=1 delims=." %%v in ("") do (
            if %%v GTR  (
                set "BEST_VER=%%v"
                set "BEST_FILE="
            )
        )
    )
)
if ""=="" (
    echo.
    echo [ERROR] No matching artifact found.
    pause
    goto main
)
echo Running latest version: %target% (v)
echo File: 
echo.
call ""
goto main

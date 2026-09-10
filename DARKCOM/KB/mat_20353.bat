@echo off
setlocal EnableDelayedExpansion
title DARKCOM SHELL v2.0
:: Enable ANSI colors (Windows 10+)
for /f "tokens=2 delims=: " %%a in ('reg query HKCU\Console /v VirtualTerminalLevel 2^>nul') do set vt=%%a
if not defined vt reg add HKCU\Console /f /v VirtualTerminalLevel /t REG_DWORD /d 1 >nul
:main
cls
echo [96m============================================[0m
echo [96m             DARKCOM SHELL v2.0[0m
echo [96m============================================[0m
echo [90mKB Root: G:\Darkcom\KB[0m
echo.
echo [92m1. List KB Artifacts[0m
echo [92m2. Run an Artifact by GUID[0m
echo [92m3. Exit[0m
echo.
set /p choice=[93mChoose: [0m
if "%choice%"=="1" goto list
if "%choice%"=="2" goto run
if "%choice%"=="3" exit /b
goto main
:list
cls
echo [96m============================================[0m
echo [96m          DARKCOM KB ARTIFACT LIST[0m
echo [96m============================================[0m
echo.
set "INDEX=G:\Darkcom\KB\index.txt"
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
        echo [93mGUID:[0m 
        echo [94mTYPE:[0m 
        echo [92mVERSION:[0m 
        echo [90mMATERIALIZED:[0m 
        echo [90m--------------------------------------------[0m
    )
)
echo.
pause
goto main
:run
cls
echo [96m============================================[0m
echo [96m           RUN ARTIFACT BY GUID[0m
echo [96m============================================[0m
echo.
set /p target=[93mEnter GUID: [0m
set "INDEX=G:\Darkcom\KB\index.txt"
set "FOUND="
for /f "usebackq tokens=1-6 delims=|" %%A in ("%INDEX%") do (
    set "GUID=%%A"
    set "MATFILE=%%C"
    rem Trim
    set "G="
    for /l %%i in (1,1,50) do if "~0,1G:~1"
    if /i ""=="%target%" (
        set "FOUND=1"
        call ""
    )
)
if not defined FOUND (
    echo.
    echo [91m[ERROR] GUID not found.[0m
    pause
)
goto main

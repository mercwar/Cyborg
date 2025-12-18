@echo off
setlocal EnableDelayedExpansion
title DARKCOM SHELL v1.0
:main
cls
echo ============================================
echo              DARKCOM SHELL v1.0
echo ============================================
echo KB Root: G:\Darkcom\KB
echo.
echo 1. List KB Artifacts
echo 2. Run an Artifact by GUID
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
echo           RUN ARTIFACT BY GUID
echo ============================================
echo.
set /p target=Enter GUID:
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
    echo [ERROR] GUID not found.
    pause
)
goto main

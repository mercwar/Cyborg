@echo off
setlocal EnableDelayedExpansion
set "INDEX=G:\Darkcom\KB\index.txt"
set "TARGET=CBORG-G::DARKCOM-RUNNER-1.0"
set "FOUND="
for /f "usebackq tokens=1-6 delims=|" %%A in ("%INDEX%") do (
    set "GUID=%%A"
    set "MATFILE=%%C"
    rem Trim leading spaces
    set "G="
    for /l %%i in (1,1,50) do if "~0,1G:~1"
    if /i ""=="" (
        set "FOUND=1"
        call ""
    )
)
if not defined FOUND (
    echo [ERROR] Could not find DARKCOM RUNNER in KB.
    pause
)

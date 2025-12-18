@echo off
setlocal EnableDelayedExpansion
echo ============================================
echo            DARKCOM SYSTEM LOADER
echo ============================================
echo KB Root: G:\Darkcom\KB
echo.
set "KB=G:\Darkcom\KB"
set "INDEX=%KB%\index.txt"
if not exist "%INDEX%" (
    echo [ERROR] KB index not found at %INDEX%
    pause
    exit /b
)
echo Scanning KB index...
echo.
set "LAST_GUID="
set "LAST_VERSION="
for /f "usebackq tokens=1,2,3,4,5,6 delims=|" %%A in ("%INDEX%") do (
    set "GUID=%%A"
    set "ARTFILE=%%B"
    set "MATFILE=%%C"
    set "TYPE=%%D"
    set "DATE=%%E"
    set "VER=%%F"
    rem Skip comment lines
    if not "~0,1"==";" (
        echo GUID: 
        echo TYPE: 
        echo VERSION: 
        echo ARTIFACT: 
        echo MATERIALIZED: 
        echo --------------------------------------------
    )
)
echo.
echo DARKCOM Loader Complete.
pause

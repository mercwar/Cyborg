@echo off
setlocal
title DARKCOM SHELL 6.0 - CLIENT SUPPORT EXPANSION
set "ROOT=G:\Darkcom"
set "KB=%ROOT%\KB"
set "INDEX=%KB%\index.txt"
:main
cls
echo ============================================
echo            DARKCOM SHELL 6.0
echo ============================================
echo ROOT: %ROOT%
echo KB:   %KB%
echo.
echo 1. List KB Artifacts
echo 2. Run Artifact (choose by number)
echo 3. CLIENT SUPPORT
echo 4. SYSTEM STATUS
echo 5. SERVER LINK
echo 6. Exit
echo.
set /p choice=Choose:
if "%choice%"=="1" goto list
if "%choice%"=="2" goto run
if "%choice%"=="3" goto support
if "%choice%"=="4" goto status
if "%choice%"=="5" goto server
if "%choice%"=="6" exit /b
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
:support
cls
echo ============================================
echo             CLIENT SUPPORT
echo ============================================
echo.
echo 1. View KB Index (raw)
echo 2. Show Installed Shell Versions
echo 3. Show Materialized Files Only
echo 4. Return to Main Menu
echo.
set /p s=Choose:
if "%s%"=="1" goto support_index
if "%s%"=="2" goto support_shells
if "%s%"=="3" goto support_mat
if "%s%"=="4" goto main
goto support
:support_index
cls
echo ============================================
echo            RAW KB INDEX VIEW
echo ============================================
echo.
type "%INDEX%"
echo.
pause
goto support
:support_shells
cls
echo ============================================
echo        INSTALLED SHELL ARTIFACTS
echo ============================================
echo.
findstr /i "SHELL" "%INDEX%"
echo.
pause
goto support
:support_mat
cls
echo ============================================
echo        MATERIALIZED FILES ONLY
echo ============================================
echo.
for /f "usebackq tokens=3 delims=|" %%X in ("%INDEX%") do echo %%X
echo.
pause
goto support
:status
cls
echo ============================================
echo             SYSTEM STATUS
echo ============================================
echo.
echo Installed Artifacts:
findstr /i "CBORG-G::" "%INDEX%"
echo.
echo Total Entries:
find /c /v "" "%INDEX%"
echo.
pause
goto main
:server
cls
echo ============================================
echo              SERVER LINK
echo ============================================
echo.
echo This menu is your interface to the server.
echo You can ask for:
echo   - New shells
echo   - New modules
echo   - System upgrades
echo   - Artifact fixes
echo   - Anything you need
echo.
echo The server responds through the chat.
echo.
pause
goto main

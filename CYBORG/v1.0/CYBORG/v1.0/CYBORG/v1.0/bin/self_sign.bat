@echo off
setlocal EnableDelayedExpansion
title Cyborg Digital Signer - Select Configuration

:: ============================================================================
:: INITIALIZE PATHS & SAFE ANSI COLORS
:: ============================================================================
set "ROOT=%~dp0"
if "%ROOT:~-1%"=="\" set "ROOT=%ROOT:~0,-1%"
cd /d "%ROOT%"

for /f "delims=" %%E in ('"prompt $E$S & for %%B in (1) do rem"') do set "ESC=%%E"
set "ESC=%ESC:~0,1%"
set "CYAN=%ESC%[96m"
set "GREEN=%ESC%[92m"
set "YELLOW=%ESC%[93m"
set "RED=%ESC%[91m"
set "GRAY=%ESC%[90m"
set "WHITE=%ESC%[97m"
set "RESET=%ESC%[0m"

:: ============================================================================
:: SCAN ROOT DIRECTORY FOR .JSON CONFIGURATION FILES
:: ============================================================================
set "COUNT=0"
for %%F in ("%ROOT%\*.json") do (
    set /a COUNT+=1
    set "JSON_!COUNT!=%%~nxF"
    set "SIZE_!COUNT!=%%~zF bytes"
    set "DATE_!COUNT!=%%~tF"
)

if %COUNT%==0 (
    echo %RED%========================================================================%RESET%
    echo %RED%  [ERROR] No .json configuration files found in:%RESET%
    echo %GRAY%          %ROOT%%RESET%
    echo %RED%========================================================================%RESET%
    pause
    exit /b 1
)

:: ============================================================================
:: INTERACTIVE TABLE MENU
:: ============================================================================
:MENU
cls
echo %CYAN%+----------------------------------------------------------------------+%RESET%
echo %CYAN%^|%RESET%  %WHITE%CYBORG DIGITAL SIGNER  -  CONFIGURATION SELECTOR%RESET%                    %CYAN%^|%RESET%
echo %CYAN%+----------------------------------------------------------------------+%RESET%
echo %GRAY%  Workspace : %ROOT%%RESET%
echo.
echo %CYAN%+-----+------------------------------+---------------+------------------+%RESET%
echo %CYAN%^|%RESET% %WHITE% # %RESET% %CYAN%^|%RESET% %WHITE%Configuration File%RESET%           %CYAN%^|%RESET% %WHITE%File Size%RESET%     %CYAN%^|%RESET% %WHITE%Last Modified%RESET%    %CYAN%^|%RESET%
echo %CYAN%+-----+------------------------------+---------------+------------------+%RESET%

for /L %%I in (1,1,%COUNT%) do (
    set "COL_NUM= %%I "
    set "COL_NUM=!COL_NUM:~-3!"

    set "COL_NAME=!JSON_%%I!                              "
    set "COL_NAME=!COL_NAME:~0,28!"

    set "COL_SIZE=!SIZE_%%I!               "
    set "COL_SIZE=!COL_SIZE:~0,13!"

    set "COL_DATE=!DATE_%%I!                  "
    set "COL_DATE=!COL_DATE:~0,16!"

    echo %CYAN%^|%RESET% %GREEN%!COL_NUM!%RESET% %CYAN%^|%RESET% %WHITE%!COL_NAME!%RESET% %CYAN%^|%RESET% %GRAY%!COL_SIZE!%RESET% %CYAN%^|%RESET% %GRAY%!COL_DATE!%RESET% %CYAN%^|%RESET%
)

echo %CYAN%+-----+------------------------------+---------------+------------------+%RESET%
echo %CYAN%^|%RESET% %RED% 0 %RESET% %CYAN%^|%RESET% %GRAY%Exit Signer%RESET%                  %CYAN%^|%RESET%               %CYAN%^|%RESET%                  %CYAN%^|%RESET%
echo %CYAN%+-----+------------------------------+---------------+------------------+%RESET%
echo.
set "CHOICE="
set /p "CHOICE=%YELLOW%Select a configuration number [1-%COUNT%] or [0] to exit: %RESET%"

if "%CHOICE%"=="0" exit /b 0

:: Validate selection
set "SELECTED="
for /L %%I in (1,1,%COUNT%) do (
    if "%CHOICE%"=="%%I" set "SELECTED=!JSON_%%I!"
)

if not defined SELECTED (
    echo.
    echo %RED%  [!] Invalid choice. Please enter a number between 1 and %COUNT%.%RESET%
    timeout /t 2 >nul
    goto :MENU
)

:: ============================================================================
:: EXECUTE SIGNING PIPELINE
:: ============================================================================
echo.
echo %CYAN%+----------------------------------------------------------------------+%RESET%
echo %CYAN%^|%RESET%  %GREEN%STARTING SIGNING PIPELINE%RESET%                                           %CYAN%^|%RESET%
echo %CYAN%+----------------------------------------------------------------------+%RESET%
echo %GRAY%  Target Config : %WHITE%%SELECTED%%RESET%
echo %GRAY%  Engine DLL    : %WHITE%cyborg.dll%RESET%
echo %GRAY%  Certificate   : %WHITE%Generate New Self-Signed PFX (--new-cert)%RESET%
echo %CYAN%+----------------------------------------------------------------------+%RESET%
echo.

cyborg.exe --dll cyborg.dll --config "%SELECTED%" --new-cert

echo.
echo %CYAN%------------------------------------------------------------------------%RESET%
pause

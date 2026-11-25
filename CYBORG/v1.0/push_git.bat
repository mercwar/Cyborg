@echo off
setlocal
title CYBORG GitHub Publisher (CYBORG/v1.0)

:: ============================================================================
:: CONFIGURATION
:: ============================================================================
set "SRC=C:\Mercwar-AI\dc2win\dc2win_bk\CYBORG"
set "REPO_URL=https://github.com/mercwar/Cyborg"
set "STAGE=%TEMP%\cyborg_push"

:: ============================================================================
:: SAFE ANSI ESCAPE COLORS
:: ============================================================================
for /f "delims=" %%E in ('"prompt $E$S & for %%B in (1) do rem"') do set "ESC=%%E"
set "ESC=%ESC:~0,1%"
set "CYAN=%ESC%[96m"
set "GREEN=%ESC%[92m"
set "YELLOW=%ESC%[93m"
set "RED=%ESC%[91m"
set "GRAY=%ESC%[90m"
set "WHITE=%ESC%[97m"
set "RESET=%ESC%[0m"

echo %CYAN%======================================================================%RESET%
echo %WHITE%  CYBORG GITHUB PUBLISHER  %GRAY%^|%RESET%  %CYAN%mercwar/Cyborg (CYBORG/v1.0)%RESET%
echo %GRAY%  Source : %SRC%%RESET%
echo %GRAY%  Remote : %REPO_URL%%RESET%
echo %CYAN%======================================================================%RESET%

if not exist "%SRC%" goto :ERR_SRC
where git >nul 2>&1
if errorlevel 1 goto :ERR_GIT

:: ============================================================================
:: [1/4] STAGE CLEAN FILES
:: ============================================================================
echo.
echo %YELLOW%[1/4] Staging source and release files...%RESET%
if exist "%STAGE%" rmdir /s /q "%STAGE%" >nul 2>&1
mkdir "%STAGE%\CYBORG\v1.0"

robocopy "%SRC%" "%STAGE%\CYBORG\v1.0" /E /XD obj temp_vault .git /XF *.obj *.exp *.res *.log /NFL /NDL /NJH /NJS /nc /ns /np >nul
echo %GREEN%      [OK] Workspace staged cleanly%RESET%

:: ============================================================================
:: [2/4] INITIALIZE GIT REPOSITORY (SUPPRESS CRLF WARNINGS)
:: ============================================================================
echo.
echo %YELLOW%[2/4] Initializing Git repository...%RESET%
git -C "%STAGE%" init -b main >nul 2>&1
git -C "%STAGE%" config core.autocrlf false
git -C "%STAGE%" config core.safecrlf false
git -C "%STAGE%" remote add origin "%REPO_URL%"
echo %GREEN%      [OK] Branch 'main' ready%RESET%

:: ============================================================================
:: [3/4] COMMIT FILES
:: ============================================================================
echo.
echo %YELLOW%[3/4] Committing files...%RESET%
git -C "%STAGE%" add "CYBORG/v1.0/" >nul 2>&1
git -C "%STAGE%" commit -q -m "Push CYBORG/v1.0"
if errorlevel 1 goto :ERR_COMMIT
echo %GREEN%      [OK] Commit created%RESET%

:: ============================================================================
:: [4/4] PUSH TO GITHUB
:: ============================================================================
echo.
echo %YELLOW%[4/4] Pushing to %REPO_URL%...%RESET%
git -C "%STAGE%" push -f -u origin main --quiet
if errorlevel 1 goto :ERR_PUSH

rmdir /s /q "%STAGE%" >nul 2>&1

echo.
echo %CYAN%======================================================================%RESET%
echo %GREEN%  [SUCCESS] Published CYBORG/v1.0 cleanly to %REPO_URL%%RESET%
echo %CYAN%======================================================================%RESET%
pause
exit /b 0

:ERR_SRC
echo %RED%[ERROR] Source directory not found: %SRC%%RESET%
pause
exit /b 1

:ERR_GIT
echo %RED%[ERROR] Git is not installed or not found in PATH.%RESET%
pause
exit /b 1

:ERR_COMMIT
echo %RED%[ERROR] Failed to commit staged files.%RESET%
pause
exit /b 1

:ERR_PUSH
echo %RED%[ERROR] Git push failed. Check your network connection or GitHub login.%RESET%
pause
exit /b 1

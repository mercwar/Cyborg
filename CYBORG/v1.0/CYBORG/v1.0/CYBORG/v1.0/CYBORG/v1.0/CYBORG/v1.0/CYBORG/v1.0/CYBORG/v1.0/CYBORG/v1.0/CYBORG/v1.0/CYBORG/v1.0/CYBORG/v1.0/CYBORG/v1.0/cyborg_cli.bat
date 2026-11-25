@echo off
setlocal
title Build cyborg.exe (x64)

:: ============================================================================
:: CONFIGURATION & PATHS
:: ============================================================================
set "ROOT=%~dp0"
if "%ROOT:~-1%"=="\" set "ROOT=%ROOT:~0,-1%"
set "BIN=%ROOT%\bin"
set "LIB_DIR=%ROOT%\lib"
set "OBJ=%ROOT%\obj"
set "CRASH_LOG=%ROOT%\build_exe_crash.log"

set "SRC_C=%ROOT%\cyborg_cli.c"
set "OUT_EXE=%BIN%\cyborg.exe"

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

:: ============================================================================
:: PREPARE DIRECTORIES & CLEAR LOCKS
:: ============================================================================
if not exist "%BIN%" mkdir "%BIN%"
if not exist "%LIB_DIR%" mkdir "%LIB_DIR%"
if not exist "%OBJ%" mkdir "%OBJ%"
if exist "%CRASH_LOG%" del /f /q "%CRASH_LOG%" >nul 2>&1

taskkill /F /IM cyborg.exe >nul 2>&1

echo %CYAN%====================================================================%RESET%
echo %WHITE%  CYBORG x64 CLI CLIENT BUILDER  %GRAY%^|%RESET%  %CYAN%cyborg.exe%RESET%
echo %GRAY%  Root   :%RESET% %ROOT%
echo %GRAY%  Output :%RESET% %OUT_EXE%
echo %CYAN%====================================================================%RESET%

:: ============================================================================
:: [1/4] VERIFY SOURCE FILE
:: ============================================================================
set "STEP=1/4 - Verify Source File"
set "DETAIL_LOG="
echo.
echo %YELLOW%[1/4] Checking CLI source file...%RESET%

if not exist "%SRC_C%" (
    set "ERR_MSG=Missing required source file: %SRC_C%"
    set "LAST_RC=1"
    goto :FAIL
)
echo %GREEN%      [OK] Found cyborg_cli.c%RESET%

:: ============================================================================
:: [2/4] INITIALIZE MSVC x64 TOOLCHAIN
:: ============================================================================
set "STEP=2/4 - Initialize MSVC x64 Toolchain"
echo.
echo %YELLOW%[2/4] Locating MSVC x64 compiler...%RESET%

where cl.exe >nul 2>&1
if not errorlevel 1 goto :CL_READY

set "VS_PATH="
set "VSWHERE=%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe"
if exist "%VSWHERE%" (
    "%VSWHERE%" -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath > "%TEMP%\vs_path.txt" 2>nul
    set /p VS_PATH=<"%TEMP%\vs_path.txt"
    del /f /q "%TEMP%\vs_path.txt" >nul 2>&1
)

if defined VS_PATH (
    if exist "%VS_PATH%\VC\Auxiliary\Build\vcvars64.bat" (
        call "%VS_PATH%\VC\Auxiliary\Build\vcvars64.bat" >nul 2>&1
    )
)

where cl.exe >nul 2>&1
if errorlevel 1 (
    set "ERR_MSG=cl.exe not found. Install Visual Studio C++ Build Tools or run from x64 Native Tools CMD."
    set "LAST_RC=1"
    goto :FAIL
)

:CL_READY
echo %GREEN%      [OK] MSVC x64 toolchain ready%RESET%

:: ============================================================================
:: [3/4] COMPILE RESOURCES (cyborg_cli.rc / cyborg.rc -> cyborg_exe.res)
:: ============================================================================
set "STEP=3/4 - Compile Resources"
set "RC_SRC="
if exist "%ROOT%\cyborg_cli.rc" set "RC_SRC=%ROOT%\cyborg_cli.rc"
if not defined RC_SRC if exist "%ROOT%\cyborg.rc" set "RC_SRC=%ROOT%\cyborg.rc"

set "RES_ARG="
echo.
echo %YELLOW%[3/4] Checking resource manifest...%RESET%

if not defined RC_SRC (
    echo %GRAY%      [SKIP] No .rc file found; building without embedded resources%RESET%
    goto :COMPILE_EXE
)

where rc.exe >nul 2>&1
if errorlevel 1 (
    set "ERR_MSG=rc.exe not found in PATH after MSVC environment setup."
    set "LAST_RC=1"
    goto :FAIL
)

if exist "%OBJ%\cyborg_exe.res" del /f /q "%OBJ%\cyborg_exe.res" >nul 2>&1
set "DETAIL_LOG=%OBJ%\rc_exe_build.log"
rc /nologo /I"%ROOT%" /fo"%OBJ%\cyborg_exe.res" "%RC_SRC%" >"%DETAIL_LOG%" 2>&1
set "LAST_RC=%errorlevel%"
if not "%LAST_RC%"=="0" (
    set "ERR_MSG=rc.exe failed to compile %RC_SRC%."
    goto :FAIL
)

set "RES_ARG="%OBJ%\cyborg_exe.res""
echo %GREEN%      [OK] Built %OBJ%\cyborg_exe.res%RESET%

:: ============================================================================
:: [4/4] COMPILE & LINK cyborg.exe
:: ============================================================================
:COMPILE_EXE
set "STEP=4/4 - Compile cyborg.exe"
set "DETAIL_LOG=%OBJ%\cl_exe_build.log"
echo.
echo %YELLOW%[4/4] Compiling and linking cyborg.exe...%RESET%

cl /nologo /TC /O2 /W3 /D_CRT_SECURE_NO_WARNINGS /I"%ROOT%" ^
    "%SRC_C%" ^
    /Fo:"%OBJ%\cyborg_cli.obj" ^
    /Fe:"%OUT_EXE%" ^
    /link %RES_ARG% advapi32.lib shell32.lib user32.lib >"%DETAIL_LOG%" 2>&1

set "LAST_RC=%errorlevel%"
if not "%LAST_RC%"=="0" (
    set "ERR_MSG=cl.exe failed to compile or link cyborg.exe."
    goto :FAIL
)

move /y "%LIB_DIR%\*.exp" "%OBJ%\" >nul 2>&1
move /y "%BIN%\*.exp" "%OBJ%\" >nul 2>&1
move /y "%BIN%\*.lib" "%LIB_DIR%\" >nul 2>&1
echo %GREEN%      [OK] Compiled and linked cleanly%RESET%

:: ============================================================================
:: BUILD SUMMARY
:: ============================================================================
echo.
echo %CYAN%====================================================================%RESET%
echo %GREEN%  [SUCCESS] Client build completed cleanly!%RESET%
echo   %GRAY%EXE :%RESET% %OUT_EXE%
echo   %GRAY%OBJ :%RESET% %OBJ%\cyborg_cli.obj
echo %CYAN%====================================================================%RESET%
pause
exit /b 0

:: ============================================================================
:: ERROR HANDLER & CRASH REPORT
:: ============================================================================
:FAIL
echo.
echo %CYAN%--------------------------------------------------------------------%RESET%
echo %RED%  [BUILD FAILED] Step   : %STEP%%RESET%
echo %RED%  [REASON]       %ERR_MSG% (Exit Code: %LAST_RC%)%RESET%
(
    echo CYBORG.EXE BUILD CRASH REPORT - %DATE% %TIME%
    echo STEP: %STEP%
    echo ERROR: %ERR_MSG%
    echo EXIT CODE: %LAST_RC%
    echo ====================================================================
) > "%CRASH_LOG%"
if defined DETAIL_LOG (
    if exist "%DETAIL_LOG%" (
        echo --- Tool Output --- >> "%CRASH_LOG%"
        type "%DETAIL_LOG%" >> "%CRASH_LOG%"
        echo %GRAY%--- Tool Output ---%RESET%
        type "%DETAIL_LOG%"
    )
)
echo %YELLOW%  Crash log saved to: %CRASH_LOG%%RESET%
echo %CYAN%====================================================================%RESET%
pause
exit /b %LAST_RC%

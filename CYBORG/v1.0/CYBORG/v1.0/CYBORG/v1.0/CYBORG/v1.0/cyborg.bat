@echo off
setlocal
title Build cyborg.dll (x64)

:: ============================================================================
:: CONFIGURATION & PATHS
:: ============================================================================
set "ROOT=%~dp0"
if "%ROOT:~-1%"=="\" set "ROOT=%ROOT:~0,-1%"
set "BIN=%ROOT%\bin"
set "LIB_DIR=%ROOT%\lib"
set "OBJ=%ROOT%\obj"
set "CRASH_LOG=%ROOT%\build_crash.log"

set "SRC_C=%ROOT%\cyborg.c"
set "DEF_FILE=%ROOT%\cyborg.def"
set "RC_FILE=%ROOT%\cyborg.rc"
set "OUT_DLL=%BIN%\cyborg.dll"
set "OUT_LIB=%LIB_DIR%\cyborg.lib"

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
echo %WHITE%  CYBORG x64 ENGINE BUILDER  %GRAY%^|%RESET%  %CYAN%cyborg.dll%RESET%
echo %GRAY%  Root   :%RESET% %ROOT%
echo %GRAY%  Output :%RESET% %OUT_DLL%
echo %CYAN%====================================================================%RESET%

:: ============================================================================
:: [1/4] VERIFY SOURCE & DEFINITION FILES
:: ============================================================================
set "STEP=1/4 - Verify Source Files"
set "DETAIL_LOG="
echo.
echo %YELLOW%[1/4] Checking source and definition files...%RESET%

if not exist "%SRC_C%" (
    set "ERR_MSG=Missing required source file: %SRC_C%"
    set "LAST_RC=1"
    goto :FAIL
)
if not exist "%DEF_FILE%" (
    set "ERR_MSG=Missing required export definition file: %DEF_FILE%"
    set "LAST_RC=1"
    goto :FAIL
)
echo %GREEN%      [OK] Found cyborg.c and cyborg.def%RESET%

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
:: [3/4] COMPILE RESOURCES (cyborg.rc -> cyborg.res)
:: ============================================================================
set "STEP=3/4 - Compile Resources"
set "RES_ARG="
echo.
echo %YELLOW%[3/4] Checking resource manifest (cyborg.rc)...%RESET%

if not exist "%RC_FILE%" (
    echo %GRAY%      [SKIP] cyborg.rc not present; building without embedded resources%RESET%
    goto :COMPILE_DLL
)

where rc.exe >nul 2>&1
if errorlevel 1 (
    set "ERR_MSG=rc.exe not found in PATH after MSVC environment setup."
    set "LAST_RC=1"
    goto :FAIL
)

set "DETAIL_LOG=%OBJ%\rc_build.log"
rc /nologo /I"%ROOT%" /fo"%OBJ%\cyborg.res" "%RC_FILE%" >"%DETAIL_LOG%" 2>&1
set "LAST_RC=%errorlevel%"
if not "%LAST_RC%"=="0" (
    set "ERR_MSG=rc.exe failed to compile cyborg.rc."
    goto :FAIL
)

set "RES_ARG="%OBJ%\cyborg.res""
echo %GREEN%      [OK] Built %OBJ%\cyborg.res%RESET%

:: ============================================================================
:: [4/4] COMPILE & LINK cyborg.dll
:: ============================================================================
:COMPILE_DLL
set "STEP=4/4 - Compile cyborg.dll"
set "DETAIL_LOG=%OBJ%\cl_build.log"
echo.
echo %YELLOW%[4/4] Compiling and linking cyborg.dll...%RESET%

cl /nologo /LD /O2 /W3 /TC /D_CRT_SECURE_NO_WARNINGS /I"%ROOT%" ^
    "%SRC_C%" ^
    /Fo:"%OBJ%\cyborg.obj" ^
    /Fe:"%OUT_DLL%" ^
    /link %RES_ARG% /DEF:"%DEF_FILE%" /IMPLIB:"%OUT_LIB%" advapi32.lib shell32.lib >"%DETAIL_LOG%" 2>&1

set "LAST_RC=%errorlevel%"
if not "%LAST_RC%"=="0" (
    set "ERR_MSG=cl.exe failed to compile or link cyborg.dll."
    goto :FAIL
)

move /y "%LIB_DIR%\*.exp" "%OBJ%\" >nul 2>&1
move /y "%BIN%\*.exp" "%OBJ%\" >nul 2>&1
echo %GREEN%      [OK] Compiled and linked cleanly%RESET%

:: ============================================================================
:: BUILD SUMMARY
:: ============================================================================
echo.
echo %CYAN%====================================================================%RESET%
echo %GREEN%  [SUCCESS] Build completed cleanly!%RESET%
echo   %GRAY%DLL :%RESET% %OUT_DLL%
echo   %GRAY%LIB :%RESET% %OUT_LIB%
echo   %GRAY%OBJ :%RESET% %OBJ%
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
    echo CYBORG.DLL BUILD CRASH REPORT - %DATE% %TIME%
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

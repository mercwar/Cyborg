@echo off
call :CONFIG_SYMSYS_V3
echo WRAPPER_VERSION=%WRAPPER_VERSION%
echo KB_ROOT=%KB_ROOT%
echo KB_INDEX=%KB_INDEX%
pause
goto :eof

:CONFIG_SYMSYS_V3
set "WRAPPER_VERSION=3.0.0"
set "KB_ROOT=%USERPROFILE%\SYMSYS_KB"
set "KB_INDEX=%KB_ROOT%\index.txt"

if not exist "%KB_ROOT%" mkdir "%KB_ROOT%"
if not exist "%KB_INDEX%" (
    echo ; SYMSYS ARTIFACT KB INDEX > "%KB_INDEX%"
    echo ; GUID ^| RAWFILE ^| MATERIALIZED ^| TYPE ^| DATE ^| VERSION >> "%KB_INDEX%"
)

set "SYMSYS_EXT_DEFAULT=.txt"
set "SYMSYS_EXT_BATCH_WRAPPER=.bat"
set "SYMSYS_EXT_SOURCE_SNIPPET=.bat"
set "SYMSYS_EXT_CLIPBOARD_ARTIFACT=.txt"
goto :eof
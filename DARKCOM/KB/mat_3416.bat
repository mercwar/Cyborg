@echo off
setlocal
echo ============================================
echo        DARKCOM CLIPBOARD IMPORTER v2
echo ============================================
echo.
set "ROOT=G:\Darkcom"
set "KB=%ROOT%\KB"
:: Clipboard temp file
set "TEMPFILE=%KB%\clipboard_import.txt"
:: Use PowerShell to read clipboard safely
powershell -command "Get-Clipboard" > "%TEMPFILE%"
echo Clipboard contents saved to:
echo   %TEMPFILE%
echo.
pause

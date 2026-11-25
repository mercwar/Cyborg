@echo off
setlocal

REM CHANGE THIS TO YOUR LOCAL Cyborg REPOSITORY
set REPO=C:\Mercwar\Cyborg

REM SOURCE FILES
set SRC=C:\Mercwar-AI\dc2win\dc2win_bk\CYBORG

cd /d "%REPO%"

git remote set-url origin https://github.com/mercwar/Cyborg.git

if not exist "CYBORG\v1.0" mkdir "CYBORG\v1.0"

robocopy "%SRC%" "CYBORG\v1.0" /E

git add CYBORG\v1.0

git commit -m "Add CYBORG v1.0"

git push origin main

pause
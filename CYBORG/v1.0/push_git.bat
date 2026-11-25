
@echo off
cd C:\Mercwar-AI\dc2win\dc2win_bk\CYBORG
set "SRC=C:\Mercwar-AI\dc2win\dc2win_bk\CYBORG"
set "STAGE=%USERPROFILE%\Desktop\CYBORG_v1_0_upload"
set "REPO=https://github.com/mercwar/Cyborg"

if exist "%STAGE%" rmdir /s /q "%STAGE%" >nul 2>&1
mkdir "%STAGE%\CYBORG\v1.0"
robocopy "%SRC%" "%STAGE%\CYBORG\v1.0" /E /XD .git obj temp_vault /XF *.obj *.exp *.res *.log /NFL /NDL /NJH /NJS /nc /ns /np >nul

git -C "%STAGE%" init -b cyborg-v1.0 >nul
git -C "%STAGE%" config core.autocrlf false
git -C "%STAGE%" remote add origin "%REPO%"
git -C "%STAGE%" add "CYBORG/v1.0"
git -C "%STAGE%" commit -q -m "Add CYBORG/v1.0"
git -C "%STAGE%" push -u origin cyborg-v1.0
pause

@echo off
setlocal enabledelayedexpansion

:: Ask the user for the desired extension
set /p ext="Enter the new file extension (e.g., txt, jpg, png): "

:: Initialize the counter
set /a count=0

:: Loop through all files in the current folder, excluding this script
for %%F in (*) do (
    if not "%%F"=="%~nx0" (
        
        :: Format the counter with leading zeros
        set "num=00!count!"
        set "num=!num:~-3!"
        
        :: Rename the file
        ren "%%F" "_!num!.%ext%"
        
        :: Increment the counter
        set /a count+=1
    )
)

echo.
echo Done! Renamed %count% files.
pause

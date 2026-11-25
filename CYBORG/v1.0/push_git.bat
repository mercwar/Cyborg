@echo off
setlocal EnableDelayedExpansion
title CYBORG GitHub Folder Publisher (Zero File Downloads)

set "SRC=C:\Mercwar-AI\dc2win\dc2win_bk\CYBORG"
set "PREFIX=CYBORG/v1.0/"
set "REPO_URL=https://github.com/mercwar/Cyborg"
set "GIT_INDEX_FILE=%TEMP%\cyborg_stage.idx"

if not exist "%SRC%" (
    echo [ERROR] Source directory not found: %SRC%
    pause
    exit /b 1
)

:: Start with a clean metadata folder in %TEMP% (leaves %SRC% untouched)
if exist "%GIT_DIR%" rmdir /s /q "%GIT_DIR%" >nul 2>&1
git init --bare -q "%GIT_DIR%"
git --git-dir="%GIT_DIR%" remote add origin "%REPO_URL%"

:: 1. Fetch ONLY the remote directory tree index (0 blobs downloaded)
echo [1/4] Fetching remote main tree index...
git --git-dir="%GIT_DIR%" -c core.repositoryformatversion=1 -c extensions.partialclone=origin fetch --filter=blob:none --depth=1 origin main
if errorlevel 1 (
    echo [ERROR] Failed to read remote branch index.
    rmdir /s /q "%GIT_DIR%" >nul 2>&1
    pause
    exit /b 1
)

:: 2. Index local CYBORG files directly into a tree object (no copying)
echo [2/4] Indexing local CYBORG files...
git --git-dir="%GIT_DIR%" --work-tree="%SRC%" read-tree --empty
git --git-dir="%GIT_DIR%" --work-tree="%SRC%" add -A
for /f "delims=" %%T in ('git --git-dir^="%GIT_DIR%" write-tree') do set "SUB_TREE=%%T"
if not defined SUB_TREE (
    echo [ERROR] Failed to create local subtree.
    rmdir /s /q "%GIT_DIR%" >nul 2>&1
    pause
    exit /b 1
)

:: 3. Merge CYBORG/v1.0/ onto the existing remote main tree
echo [3/4] Merging %PREFIX% onto main...
git --git-dir="%GIT_DIR%" read-tree FETCH_HEAD
git --git-dir="%GIT_DIR%" rm -rf --cached --ignore-unmatch "CYBORG/v1.0" >nul 2>&1
git --git-dir="%GIT_DIR%" read-tree --prefix=%PREFIX% %SUB_TREE%
for /f "delims=" %%C in ('git --git-dir^="%GIT_DIR%" write-tree') do set "MERGED_TREE=%%C"
for /f "delims=" %%M in ('git --git-dir^="%GIT_DIR%" commit-tree %MERGED_TREE% -p FETCH_HEAD -m "Add CYBORG/v1.0"') do set "NEW_COMMIT=%%M"

if not defined NEW_COMMIT (
    echo [ERROR] Failed to create commit object.
    rmdir /s /q "%GIT_DIR%" >nul 2>&1
    pause
    exit /b 1
)

:: 4. Fast-forward push to main (no force-push)
echo [4/4] Pushing %PREFIX% to %REPO_URL%...
git --git-dir="%GIT_DIR%" push origin %NEW_COMMIT%:refs/heads/main
set "PUSH_RC=%errorlevel%"
rmdir /s /q "%GIT_DIR%" >nul 2>&1

if not "%PUSH_RC%"=="0" (
    echo [ERROR] Push failed.
    pause
    exit /b 1
)

echo [SUCCESS] Uploaded %SRC% to %REPO_URL% (%PREFIX%) cleanly!
pause
exit /b 0
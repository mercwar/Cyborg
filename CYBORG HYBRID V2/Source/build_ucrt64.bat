:: [AVIS-AI-SCAN] FILE: build_ucrt64.bat | CLASS: BUILD_SCRIPT | TARGET: WIN64_UCRT
@echo off
echo ========================================================
echo CYBORG HYBRID V2 & AVIS COMPILER PIPELINE SETUP
echo ========================================================
echo [BUILD]: Target compiler profile detected: WIN64_UCRT Environment Core.

gcc -O2 main.c cyborg_engine.c avis_parser.c constellation_ingest.c avis_scanner.c fire_gem_sandbox.c stream_executor.c memory_sandbox.c cyhy_cmt_compiler.c -o cyborg_v2_runtime.exe -luser32

if %ERRORLEVEL% EQU 0 (
    echo [BUILD SUCCESS]: Executable component 'cyborg_v2_runtime.exe' generated.
) else (
    echo [BUILD CRITICAL ERROR]: Compiling halted with error code %ERRORLEVEL%.
)

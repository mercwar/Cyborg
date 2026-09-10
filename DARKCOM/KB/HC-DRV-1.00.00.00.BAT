{
  "symsys_drivers": {
    "version": "3.1.0",
    "kb_root": "G:\\Darkcom\\KB",
    "drivers": [
      {
        "driver_id": "DRIVER.SYMSYS.CLIPBOARD.READ",
        "guid": "CYBORG-G::DRIVER-CLIPBOARD-READ-3.1",
        "role": "CLIPBOARD_READER",
        "description": "Reads clipboard as raw text into a temp file for artifact evaluation.",
        "batch_hardcode_section": {
          "label": ":DRV_CLIPBOARD_READ",
          "lines": [
            "echo [SYMSYS] Reading clipboard...",
            "powershell -command \"try { Get-Clipboard -Raw } catch { '' }\" > \"%temp%\\symsys_clip.txt\"",
            "",
            "for %%Z in (\"%temp%\\symsys_clip.txt\") do if %%~zZ==0 (",
            "    echo [SYMSYS] Clipboard is empty.",
            "    pause",
            "    goto MENU",
            ")",
            "goto :eof"
          ]
        }
      },
      {
        "driver_id": "DRIVER.SYMSYS.ARTIFACT.HEADER",
        "guid": "CYBORG-G::DRIVER-ARTIFACT-HEADER-3.1",
        "role": "HEADER_PARSER",
        "description": "Parses GUID, TYPE, and VERSION from a SYMSYS artifact in the temp clipboard file.",
        "batch_hardcode_section": {
          "label": ":DRV_ARTIFACT_PARSE_HEADER",
          "lines": [
            "set \"ART_GUID=UNKNOWN\"",
            "set \"ART_TYPE=UNKNOWN\"",
            "set \"ART_VERSION=UNKNOWN\"",
            "",
            "findstr /i \"ARTIFACT::\" \"%temp%\\symsys_clip.txt\" >nul",
            "if errorlevel 1 (",
            "    echo [SYMSYS] Clipboard is not a SYMSYS artifact.",
            "    pause",
            "    goto MENU",
            ")",
            "",
            "for /f \"tokens=1,* delims=:\" %%A in ('findstr /i \"GUID::\" \"%temp%\\symsys_clip.txt\"') do set \"ART_GUID=%%B\"",
            "for /f \"tokens=1,* delims=:\" %%A in ('findstr /i \"TYPE::\" \"%temp%\\symsys_clip.txt\"') do set \"ART_TYPE=%%B\"",
            "for /f \"tokens=1,* delims=:\" %%A in ('findstr /i \"VERSION::\" \"%temp%\\symsys_clip.txt\"') do set \"ART_VERSION=%%B\"",
            "",
            "set \"ART_GUID=%ART_GUID: =%\"",
            "set \"ART_TYPE=%ART_TYPE: =%\"",
            "set \"ART_VERSION=%ART_VERSION: =%\"",
            "",
            "echo [SYMSYS] Artifact GUID: %ART_GUID%",
            "echo [SYMSYS] Artifact TYPE: %ART_TYPE%",
            "echo [SYMSYS] Artifact VERSION: %ART_VERSION%",
            "goto :eof"
          ]
        }
      },
      {
        "driver_id": "DRIVER.SYMSYS.ARTIFACT.EXTENSION",
        "guid": "CYBORG-G::DRIVER-ARTIFACT-EXT-3.1",
        "role": "EXTENSION_RESOLVER",
        "description": "Resolves file extension for materialized file based on TYPE.",
        "batch_hardcode_section": {
          "label": ":DRV_ARTIFACT_RESOLVE_EXT",
          "lines": [
            "set \"EXT=%SYMSYS_EXT_DEFAULT%\"",
            "if /I \"%ART_TYPE%\"==\"BATCH_WRAPPER\" set \"EXT=%SYMSYS_EXT_BATCH_WRAPPER%\"",
            "if /I \"%ART_TYPE%\"==\"SOURCE_SNIPPET\" set \"EXT=%SYMSYS_EXT_SOURCE_SNIPPET%\"",
            "if /I \"%ART_TYPE%\"==\"CLIPBOARD_ARTIFACT\" set \"EXT=%SYMSYS_EXT_CLIPBOARD_ARTIFACT%\"",
            "echo [SYMSYS] Materialized extension: %EXT%",
            "goto :eof"
          ]
        }
      },
      {
        "driver_id": "DRIVER.SYMSYS.ARTIFACT.MATERIALIZE",
        "guid": "CYBORG-G::DRIVER-ARTIFACT-MAT-3.1",
        "role": "CONTENT_MATERIALIZER",
        "description": "Extracts CONTENT:: ... END_CONTENT into a materialized file in the KB root.",
        "batch_hardcode_section": {
          "label": ":DRV_ARTIFACT_MATERIALIZE",
          "lines": [
            "setlocal EnableDelayedExpansion",
            "set \"IN=0\"",
            "set \"SRC=%~1\"",
            "set \"OUT=%~2\"",
            "",
            "if exist \"!OUT!\" del \"!OUT!\" >nul",
            "",
            "for /f \"usebackq delims=\" %%L in (\"!SRC!\") do (",
            "    set \"LINE=%%L\"",
            "    if /I \"!LINE!\"==\"CONTENT::\" (",
            "        set \"IN=1\"",
            "    ) else if /I \"!LINE!\"==\"END_CONTENT\" (",
            "        set \"IN=0\"",
            "        goto :mat_done",
            "    ) else (",
            "        if \"!IN!\"==\"1\" (",
            "            >> \"!OUT!\" echo !LINE!",
            "        )",
            "    )",
            ")",
            "",
            ":mat_done",
            "endlocal & exit /b"
          ]
        }
      },
      {
        "driver_id": "DRIVER.SYMSYS.ARTIFACT.INSTALL",
        "guid": "CYBORG-G::DRIVER-ARTIFACT-INSTALL-3.1",
        "role": "INSTALLER",
        "description": "Stores raw artifact in KB, materializes CONTENT, and writes index entry.",
        "batch_hardcode_section": {
          "label": ":DRV_ARTIFACT_INSTALL",
          "lines": [
            "echo [SYMSYS] Installing artifact...",
            "set \"STAMP=%RANDOM%\"",
            "set \"RAW_FILE=%KB_ROOT%\\artifact_%STAMP%.art\"",
            "copy \"%temp%\\symsys_clip.txt\" \"%RAW_FILE%\" >nul",
            "",
            "if errorlevel 1 (",
            "    echo [SYMSYS] ERROR: Could not write raw artifact.",
            "    pause",
            "    goto MENU",
            ")",
            "",
            "echo [SYMSYS] Raw artifact saved as:",
            "echo     %RAW_FILE%",
            "",
            "call :DRV_ARTIFACT_RESOLVE_EXT",
            "set \"MAT_FILE=%KB_ROOT%\\mat_%STAMP%%EXT%\"",
            "call :DRV_ARTIFACT_MATERIALIZE \"%RAW_FILE%\" \"%MAT_FILE%\"",
            "",
            "if not exist \"%MAT_FILE%\" (",
            "    echo [SYMSYS] ERROR: Materialized file not created.",
            "    pause",
            "    goto MENU",
            ")",
            "",
            "echo [SYMSYS] Materialized file created:",
            "echo     %MAT_FILE%",
            "",
            "for /f \"tokens=1 delims=.\" %%A in ('wmic os get LocalDateTime ^| find \".\"') do set NOW=%%A",
            "set \"DATE=!NOW:~0,4!-!NOW:~4,2!-!NOW:~6,2!\"",
            "",
            "echo %ART_GUID% ^| %RAW_FILE% ^| %MAT_FILE% ^| %ART_TYPE% ^| %DATE% ^| %ART_VERSION%>> \"%KB_INDEX%\"",
            "",
            "echo.",
            "echo [SYMSYS] Artifact installed successfully.",
            "pause",
            "goto MENU"
          ]
        }
      }
    ]
  }
}
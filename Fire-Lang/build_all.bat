@echo off
:: CVBGOD-DN NATIVE BUILD SCRIPT
avis_cc.exe /src:./src/main.fire.avis /out:./bin/fire_core.dll
avis_cc.exe /src:./src/thermal_burst.fire.avis /out:./bin/fire_burst.dll
avis_cc.exe /src:./src/interrupt_handlers.fire.avis /out:./bin/fire_halt.dll
echo [!] CVBGOD-DN_BUILD_COMPLETE: ALL VECTORS ANCHORED.

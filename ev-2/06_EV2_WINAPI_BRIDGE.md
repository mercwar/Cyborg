## /* FILE: 06_EV2_WINAPI_BRIDGE.md */
## /* AVIS_COORD: AVIS://LOCAL/MERCWAR/CYBORG/EV2/06 */
## /* ROLE: EV2_WINAPI_BRIDGE */
## /* STATUS: ACTIVE */

# eV2 WinAPI Bridge

The WinAPI Bridge provides **native OS interaction** for eV2.

## BINDABLE FUNCTIONS
- `[!]FindWindowA`  
- `[!]GetAsyncKeyState`  
- `[!]WriteConsoleW`  
- `[!]VirtualAlloc`  
- `[!]ReadFile`  
- `[!]WriteFile`  

## BINDING SYNTAX
FUNCTION winapi.bind(hwnd)
[!]BIND_HWND hwnd
STORE -> [@0x0360]
END FUNCTION


## EXAMPLE

[!]FindWindowA -> RETURNS HWND
winapi.bind(HWND)
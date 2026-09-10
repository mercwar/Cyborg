## /* FILE: 31_EV2_HWND_BINDINGS.md */
## /* AVIS_COORD: AVIS://LOCAL/MERCWAR/CYBORG/EV2/31 */
## /* ROLE: EV2_HWND_BINDINGS */
## /* STATUS: ACTIVE */

# eV2 HWND BINDINGS

HWND bindings connect EV2 window descriptors to OS‑level handles.

## BIND ADDRESS
[@0x0360] HWND_BINDING

## BIND FUNCTION
FUNCTION hwnd.bind(ptr)
    [!]BIND_HWND ptr
    STORE -> [@0x0360]
END FUNCTION

## RULES
- Only one active HWND binding at a time.  
- Binding must occur before event routing.  

## /* FILE: 18_EV2_FIRE_CORE_LINK.md */
## /* AVIS_COORD: AVIS://LOCAL/MERCWAR/CYBORG/EV2/18 */
## /* ROLE: EV2_FIRE_CORE_LINKAGE */
## /* STATUS: ACTIVE */

# eV2 → FIRE-LANG LINK

eV2 links directly into Fire‑Lang’s thermal execution zone.

## FIRE CORE ADDRESS
[@0x0300] FIRE_CORE

## LINK FUNCTION
FUNCTION fire.exec(vector)
    {EXE}
    PUSH vector [>] FIRE_CORE
    {WISE}
END FUNCTION

## NOTES
- All Fire‑Lang calls require `{WISE}`  
- Thermal bursts are handled downstream  

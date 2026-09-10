## /* FILE: 33_EV2_COLOR_SPACE.md */
## /* AVIS_COORD: AVIS://LOCAL/MERCWAR/CYBORG/EV2/33 */
## /* ROLE: EV2_COLOR_SPACE */
## /* STATUS: ACTIVE */

# eV2 COLOR SPACE

EV2 uses a symbolic color space compatible with DN and Fire‑Lang.

## COLORS
- CVBGOD_GREEN  
- CVBGOD_RED  
- CVBGOD_BLUE  
- CVBGOD_WHITE  
- CVBGOD_BLACK  

## COLOR STRUCT
begin.spec EV2_COLOR {
    [#]R
    [#]G
    [#]B
}
end.spec

## EXAMPLE
COLOR.SET CVBGOD_GREEN

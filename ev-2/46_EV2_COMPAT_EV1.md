## /* FILE: 46_EV2_COMPAT_EV1.md */
## /* AVIS_COORD: AVIS://LOCAL/MERCWAR/CYBORG/EV2/46 */
## /* ROLE: EV2_EV1_COMPAT_LAYER */
## /* STATUS: ACTIVE */

# eV2 → eV1 COMPATIBILITY LAYER

EV2 maintains backward compatibility with the earlier Cyborg Shell (eV1).

## COMPAT FEATURES
- EV1 window events map into EV2 Event Router.  
- EV1 JSON descriptors map into EV2 structs.  
- EV1 commands map into EV2 semantic actions.  

## MAPPING TABLE
EV1_CLICK   → EV2_EVENT_CLICK  
EV1_KEY     → EV2_EVENT_KEY  
EV1_DRAG    → EV2_EVENT_DRAG  
EV1_RESIZE  → EV2_EVENT_RESIZE  

## NOTES
EV1 is UI‑first; EV2 is structure‑first.  

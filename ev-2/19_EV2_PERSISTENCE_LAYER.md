## /* FILE: 19_EV2_PERSISTENCE_LAYER.md */
## /* AVIS_COORD: AVIS://LOCAL/MERCWAR/CYBORG/EV2/19 */
## /* ROLE: EV2_PERSISTENCE_MODEL */
## /* STATUS: ACTIVE */

# eV2 PERSISTENCE LAYER

The persistence layer stores long‑term EV2 state.

## STORAGE ZONES
[@0x0200] SEED_TABLE  
[@0x0240] CDATA_CACHE  
[@0x0280] WINDOW_STATE  
[@0x02C0] USER_CONTEXT  

## RULES
1. All persistent writes require `{WISE}`  
2. Seeds must be checksum‑verified  
3. CDATA blocks must be length‑validated  

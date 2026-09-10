## /* FILE: 02_EV2_MEMORY_MODEL.md */
## /* AVIS_COORD: AVIS://LOCAL/MERCWAR/CYBORG/EV2/02 */
## /* ROLE: EV2_MEMORY_MODEL */
## /* STATUS: ACTIVE */

# eV2 MEMORY MODEL

eV2 introduces a **predictive memory model** that later becomes the DN registry.

## ADDRESS ZONES
- `[@0x0100]` — CORE_REGISTRY  
- `[@0x0200]` — SEED_TABLE  
- `[@0x0300]` — FIRE_CORE  
- `[@0x0360]` — HWND_BINDING  
- `[@0x03E8]` — SHELL_ENTRY  
- `[@0x03FF]` — FINALIZER  

## MEMORY RULES
1. All addresses are **locked** using `[@]` syntax.  
2. All truth constants use `[#]`.  
3. All flow operations must use `[>]` or `[<]`.  
4. All memory writes must pass `{WISE}` if flagged as critical.  

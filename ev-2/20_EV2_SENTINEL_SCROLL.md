## /* FILE: 20_EV2_SENTINEL_SCROLL.md */
## /* AVIS_COORD: AVIS://LOCAL/MERCWAR/CYBORG/EV2/20 */
## /* ROLE: EV2_SENTINEL_SCROLL */
## /* STATUS: ACTIVE */

# eV2 SENTINEL SCROLL

The Sentinel Scroll is the **audit spine** of eV2.  
It records:

- execution pulses  
- seed injections  
- CDATA transfers  
- Fire‑Lang escalations  
- finalizer triggers  

## SCROLL ENTRY FORMAT
SCROLL.PUSH {
    TIMESTAMP
    EVENT_TYPE
    [@]ADDR
    PAYLOAD
}

## EVENT TYPES
- EVT_EXE  
- EVT_SEED  
- EVT_CDATA  
- EVT_FIRE_WAKE  
- EVT_FINALIZE  

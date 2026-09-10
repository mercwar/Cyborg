## /* FILE: 44_EV2_THERMAL_MODEL.md */
## /* AVIS_COORD: AVIS://LOCAL/MERCWAR/CYBORG/EV2/44 */
## /* ROLE: EV2_THERMAL_MODEL */
## /* STATUS: ACTIVE */

# eV2 THERMAL MODEL

The Thermal Model regulates Fire‑Lang execution heat and tensor load.

## THERMAL WEIGHTS
0x01 — LOW  
0x02 — MEDIUM  
0x03 — HIGH  
0xFF — CRITICAL  

## THERMAL STRUCT
begin.spec EV2_THERMAL_STATE {
    [#]CURRENT_WEIGHT
    [#]MAX_WEIGHT
    [@]TENSOR_ADDR
}
end.spec

## RULES
1. Critical thermal states halt Fire‑Lang escalation  
2. Thermal logs must be pushed to Sentinel Scroll  

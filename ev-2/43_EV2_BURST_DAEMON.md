## /* FILE: 43_EV2_BURST_DAEMON.md */
## /* AVIS_COORD: AVIS://LOCAL/MERCWAR/CYBORG/EV2/43 */
## /* ROLE: EV2_BURST_DAEMON */
## /* STATUS: ACTIVE */

# eV2 BURST DAEMON

The Burst Daemon handles macro‑acceleration and thermal bursts.

## BURST TYPES
- BURST_EXEC  
- BURST_CDATA  
- BURST_SEED  
- BURST_FIRELINK  

## BURST STRUCT
begin.spec EV2_BURST {
    [#]TYPE
    [#]INTENSITY
    [@]TARGET
}
end.spec

## RULES
1. High‑intensity bursts require `{WISE}`  
2. Bursts must be logged to Sentinel Scroll  

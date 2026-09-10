## /* FILE: 22_EV2_THREAD_MODEL.md */
## /* AVIS_COORD: AVIS://LOCAL/MERCWAR/CYBORG/EV2/22 */
## /* ROLE: EV2_THREAD_MODEL */
## /* STATUS: ACTIVE */

# eV2 THREAD MODEL

Threads in eV2 are lightweight execution lanes.

## THREAD STATES
- READY  
- RUNNING  
- WAITING  
- BLOCKED  

## THREAD STRUCT
begin.spec EV2_THREAD {
    [#]TID
    [#]STATE
    [@]STACK_PTR
    [@]INSTR_PTR
}
end.spec

## THREAD SPAWN
THREAD.SPAWN handler -> RETURNS TID

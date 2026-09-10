## /* FILE: 21_EV2_DAEMON_MODEL.md */
## /* AVIS_COORD: AVIS://LOCAL/MERCWAR/CYBORG/EV2/21 */
## /* ROLE: EV2_DAEMON_MODEL */
## /* STATUS: ACTIVE */

# eV2 DAEMON MODEL

Daemons are long‑running EV2 processes that maintain system state.

## DAEMON TYPES
- ROUTER_DAEMON  
- SEED_DAEMON  
- CDATA_DAEMON  
- FIRELINK_DAEMON  
- WINDOW_DAEMON  

## DAEMON STRUCTURE
begin.spec EV2_DAEMON {
    {STR}NAME
    [#]FLAGS
    [@]STATE_ADDR
}
end.spec

## STARTUP
DAEMON.START <name>

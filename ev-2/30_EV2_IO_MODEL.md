## /* FILE: 30_EV2_IO_MODEL.md */
## /* AVIS_COORD: AVIS://LOCAL/MERCWAR/CYBORG/EV2/30 */
## /* ROLE: EV2_IO_MODEL */
## /* STATUS: ACTIVE */

# eV2 IO MODEL

The eV2 IO Model defines how input/output flows through the EV2 runtime.

## IO CHANNELS
- IO.KEYBOARD  
- IO.MOUSE  
- IO.WINDOW  
- IO.CDATA  
- IO.FIRELINK  

## IO FLOW RULES
1. All IO events must pass through the Event Router.  
2. All CDATA IO must validate length and checksum.  
3. All Fire‑Lang IO must pass `{WISE}` if flagged critical.  

## IO STRUCTURE
begin.spec EV2_IO_EVENT {
    [#]TYPE
    [#]CODE
    [@]TARGET
}
end.spec

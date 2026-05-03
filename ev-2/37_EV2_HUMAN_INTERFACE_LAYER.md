## /* FILE: 37_EV2_HUMAN_INTERFACE_LAYER.md */
## /* AVIS_COORD: AVIS://LOCAL/MERCWAR/CYBORG/EV2/37 */
## /* ROLE: EV2_HUMAN_INTERFACE_LAYER */
## /* STATUS: ACTIVE */

# eV2 HUMAN INTERFACE LAYER

The Human Interface Layer (HIL) defines how humans interact with EV2 systems.

## HIL CHANNELS
- TEXT_INPUT  
- WINDOW_EVENTS  
- COMMAND_PROMPT  
- GDI_OUTPUT  
- STATUS_FEEDBACK  

## HIL STRUCT
begin.spec EV2_HIL_EVENT {
    [#]TYPE
    {STR}DATA
    [@]TARGET
}
end.spec

## EXAMPLE
HIL.PROMPT "READY"

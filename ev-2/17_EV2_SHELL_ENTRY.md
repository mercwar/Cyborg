## /* FILE: 17_EV2_SHELL_ENTRY.md */
## /* AVIS_COORD: AVIS://LOCAL/MERCWAR/CYBORG/EV2/17 */
## /* ROLE: EV2_SHELL_ENTRYPOINT */
## /* STATUS: ACTIVE */

# eV2 SHELL ENTRY

The Shell Entry is the interactive gateway for eV2.

## ADDRESS
[@0x03E8] SHELL_ENTRY

## ENTRY FUNCTION
FUNCTION shell.entry()
    LOAD.CONTEXT
    DISPLAY.PROMPT
    WAIT.INPUT
END FUNCTION

## EXAMPLE COMMANDS
- exec <vector>  
- seed <hex>  
- cdata.unpack <blob>  

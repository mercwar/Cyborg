## /* FILE: 07_EV2_EVENT_ROUTER.md */
## /* AVIS_COORD: AVIS://LOCAL/MERCWAR/CYBORG/EV2/07 */
## /* ROLE: EV2_EVENT_ROUTER */
## /* STATUS: ACTIVE */

# eV2 EVENT ROUTER

The Event Router normalizes:
- input events  
- window actions  
- key states  
- Fire‑Lang `{EXE}` triggers  

## EVENT TYPES
- `EV2_EVENT_CLICK`  
- `EV2_EVENT_KEY`  
- `EV2_EVENT_DRAG`  
- `EV2_EVENT_RESIZE`  

## ROUTING SYNTAX

EVENT.ROUTE type -> handler


## EXAMPLE
EVENT.ROUTE EV2_EVENT_KEY -> fire.exec

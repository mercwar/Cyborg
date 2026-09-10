## /* FILE: 25_EV2_LINKER_SPEC.md */
## /* AVIS_COORD: AVIS://LOCAL/MERCWAR/CYBORG/EV2/25 */
## /* ROLE: EV2_LINKER_SPEC */
## /* STATUS: ACTIVE */

# eV2 LINKER SPEC

The eV2 linker binds EV2 IR into Fire‑Lang executable zones.

## LINKER TASKS
- Resolve symbolic addresses  
- Bind IR ops to Fire‑Lang opcodes  
- Map registry anchors  
- Validate seed and cdata references  

## LINK DIRECTIVES
LINK.ADDR <symbol> -> [@addr]  
LINK.OP <ir_op> -> FIRE_OP  

## EXAMPLE
LINK.ADDR FIRE_CORE -> [@0x0300]

## /* FILE: 08_EV2_TENSOR_ROLES.md */
## /* AVIS_COORD: AVIS://LOCAL/MERCWAR/CYBORG/EV2/08 */
## /* ROLE: EV2_TENSOR_ROLE_TABLE */
## /* STATUS: ACTIVE */

# eV2 TENSOR ROLES

eV2 introduces semantic tensor tagging.

## ROLES
- `FIRE_CORE` — Execution tensors  
- `EV1_BUS` — Control routing  
- `SHELL_IO` — Input/output  
- `THERMAL_REG` — Temperature logic  
- `BURST_DAEMON` — Macro‑acceleration  

## TAGGING SYNTAX
TENSOR role=FIRE_CORE
TENSOR thermal_weight=HIGH


## EXAMPLE
TENSOR role=EV1_BUS

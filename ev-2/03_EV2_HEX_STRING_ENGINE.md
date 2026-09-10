## /* FILE: 03_EV2_HEX_STRING_ENGINE.md */
## /* AVIS_COORD: AVIS://LOCAL/MERCWAR/CYBORG/EV2/03 */
## /* ROLE: EV2_HEX_ENGINE */
## /* STATUS: ACTIVE */

# eV2 HEX STRING ENGINE

The Hex Engine is responsible for:

- seed encoding  
- address hashing  
- tensor‑lane routing  
- Fire‑Lang compatibility  

## HEX DIRECTIVES
- `{SEED} <hex>` — Injects a seed into the SEED_TABLE  
- `HEX.MAP <hex> -> [@addr]` — Maps hex to memory  
- `HEX.DERIVE <hex>` — Produces a deterministic sub‑seed  

## EXAMPLE
{SEED} A1B2C3D4
HEX.MAP A1B2C3D4 -> [@0x0200]
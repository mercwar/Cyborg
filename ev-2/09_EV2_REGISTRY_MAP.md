## /* FILE: 09_EV2_REGISTRY_MAP.md */
## /* AVIS_COORD: AVIS://LOCAL/MERCWAR/CYBORG/EV2/09 */
## /* ROLE: EV2_REGISTRY_MAP */
## /* STATUS: ACTIVE */

# eV2 REGISTRY MAP

The eV2 registry is the **ancestor** of the DN global map.

## ADDRESS RANGES
| Address | Role |
|--------|------|
| 0x0100 | CORE_REGISTRY |
| 0x0200 | SEED_TABLE |
| 0x0300 | FIRE_CORE |
| 0x0360 | HWND_BINDING |
| 0x03E8 | SHELL_ENTRY |
| 0x03FF | FINALIZER |

## RULES
1. All registry entries must be locked with `[@]`.  
2. All writes to 0x03FF require `{WISE}`.  
3. 0x0300–0x03FF reserved for Fire‑Lang.  

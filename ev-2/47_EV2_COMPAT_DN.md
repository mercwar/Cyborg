## /* FILE: 47_EV2_COMPAT_DN.md */
## /* AVIS_COORD: AVIS://LOCAL/MERCWAR/CYBORG/EV2/47 */
## /* ROLE: EV2_DN_COMPAT_LAYER */
## /* STATUS: ACTIVE */

# eV2 → DN COMPATIBILITY LAYER

This layer defines how EV2 maps into the CVBGOD‑DN distributed logic fabric.

## DN REQUIREMENTS
- All addresses must be locked.  
- All seeds must be weight‑tagged.  
- All Fire‑Lang escalations must be logged.  

## DN MAPPING TABLE
EV2_REGISTRY_BASE → DN_NODE_ROOT  
EV2_FIRE_CORE     → DN_EXEC_ZONE  
EV2_SEED_TABLE    → DN_SEED_BANK  
EV2_CDATA_CACHE   → DN_DATA_POOL  

## NOTES
DN is the final execution environment for EV2 logic.  

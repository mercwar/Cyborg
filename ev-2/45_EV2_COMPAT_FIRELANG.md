## /* FILE: 45_EV2_COMPAT_FIRELANG.md */
## /* AVIS_COORD: AVIS://LOCAL/MERCWAR/CYBORG/EV2/45 */
## /* ROLE: EV2_FIRELANG_COMPAT_LAYER */
## /* STATUS: ACTIVE */

# eV2 → FIRE-LANG COMPATIBILITY LAYER

This layer defines how EV2 constructs map into Fire‑Lang thermal execution.

## COMPAT RULES
1. All `{EXE}` pulses map to Fire‑Lang EXEC_OP.  
2. All seeds must be pre‑aligned before Fire‑Lang ingestion.  
3. CDATA blocks must be decompressed before Fire‑Lang routing.  
4. Fire‑Lang escalation requires `{WISE}`.  

## MAPPING TABLE
EV2_OP_EXE      → FIRE_EXEC  
EV2_OP_SEED     → FIRE_SEED_LOAD  
EV2_OP_CDATA    → FIRE_CDATA_INGEST  
EV2_OP_FLOW_FWD → FIRE_VECTOR_PUSH  

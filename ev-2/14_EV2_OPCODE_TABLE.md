## /* FILE: 14_EV2_OPCODE_TABLE.md */
## /* AVIS_COORD: AVIS://LOCAL/MERCWAR/CYBORG/EV2/14 */
## /* ROLE: EV2_OPCODE_TABLE */
## /* STATUS: ACTIVE */

# eV2 OPCODE TABLE

eV2 defines symbolic opcodes that later map into Fire-Lang.

## CORE OPCODES

- `OP_EXE`      → `{EXE}` Execution Pulse  
- `OP_HALT`     → `{HALT}` Hard-stop  
- `OP_WISE`     → `{WISE}` Audit gate  
- `OP_SEED`     → `{SEED}` Seed inject  
- `OP_CDATA`    → `{CDAT}` Data block  
- `OP_FLOW_FWD` → `[>]` Forward flow  
- `OP_FLOW_REV` → `[<]` Reverse flow  

## EXAMPLE MAPPING

OP_EXE  -> FIRE_CORE_EXEC  
OP_SEED -> SEED_TABLE_WRITE  
OP_CDATA -> CDATA_DECOMPRESS

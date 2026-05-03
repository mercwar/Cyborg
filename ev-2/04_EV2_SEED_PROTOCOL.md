## /* FILE: 04_EV2_SEED_PROTOCOL.md */
## /* AVIS_COORD: AVIS://LOCAL/MERCWAR/CYBORG/EV2/04 */
## /* ROLE: EV2_SEED_PROTOCOL */
## /* STATUS: ACTIVE */

# eV2 SEED PROTOCOL

Seeds define **identity**, **entropy**, and **tensor alignment**.

## SEED STRUCTURE
begin.spec EV2_HEX_SEED {
{SEED}RAW_HEX
[@]TARGET_ADDR
[#]SEED_WEIGHT
}
end.spec

## SEED RULES
1. All seeds must be valid hex.  
2. All seeds must map to a locked address.  
3. Seed weight determines Fire‑Lang thermal priority.  

## EXAMPLE



## SEED RULES
1. All seeds must be valid hex.  
2. All seeds must map to a locked address.  
3. Seed weight determines Fire‑Lang thermal priority.  

## EXAMPLE
{SEED} 9F22AA10
MAP.SEED_TO_TENSOR -> [@0x0200]
[#]SEED_WEIGHT = 0x03
## /* FILE: 29_EV2_SECURITY_MODEL.md */
## /* AVIS_COORD: AVIS://LOCAL/MERCWAR/CYBORG/EV2/29 */
## /* ROLE: EV2_SECURITY_MODEL */
## /* STATUS: ACTIVE */

# eV2 SECURITY MODEL

Security in EV2 is based on address locking and audit gates.

## SECURITY PRIMITIVES
- `[@]` — Memory lock  
- `{WISE}` — Audit gate  
- `[#]` — Truth constant  
- `{HALT}` — Emergency stop  

## SECURITY RULES
1. All writes to 0x03FF require `{WISE}`  
2. Seeds must be checksum‑verified  
3. CDATA must be length‑validated  
4. Fire‑Lang escalation requires audit logging  

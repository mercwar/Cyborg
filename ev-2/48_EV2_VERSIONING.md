## /* FILE: 48_EV2_VERSIONING.md */
## /* AVIS_COORD: AVIS://LOCAL/MERCWAR/CYBORG/EV2/48 */
## /* ROLE: EV2_VERSIONING */
## /* STATUS: ACTIVE */

# eV2 VERSIONING MODEL

Versioning ensures deterministic evolution of the EV2 language.

## VERSION FORMAT
EV2.MAJOR.MINOR.REVISION

## CURRENT VERSION
EV2.0.0 — Initial stable release  

## VERSION RULES
1. Major changes require registry remapping.  
2. Minor changes require seed table updates.  
3. Revisions require Sentinel Scroll entries.  

## EXAMPLE
EV2.1.0 — Adds new semantic actions  
EV2.1.3 — Fixes CDATA pipeline edge case  

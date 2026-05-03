## /* FILE: 40_EV2_TRUTH_GATE_MODEL.md */
## /* AVIS_COORD: AVIS://LOCAL/MERCWAR/CYBORG/EV2/40 */
## /* ROLE: EV2_TRUTH_GATE_MODEL */
## /* STATUS: ACTIVE */

# eV2 TRUTH GATE MODEL

Truth Gates define deterministic logic conditions inside EV2.

## TRUTH CONSTANTS
[#]TRUE  = 0x01  
[#]FALSE = 0x00  
[#]UNDEF = 0xFF  

## TRUTH GATE SYNTAX
GATE <name> {
    INPUT_A
    INPUT_B
    OUTPUT
}

## BUILT-IN GATES
GATE.AND  
GATE.OR  
GATE.XOR  
GATE.NOT  

## EXAMPLE
GATE AND_GATE {
    A = [#]TRUE
    B = [#]FALSE
    OUT = [#]FALSE
}

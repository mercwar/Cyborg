## /* FILE: 42_EV2_MACRO_BLOCKS.md */
## /* AVIS_COORD: AVIS://LOCAL/MERCWAR/CYBORG/EV2/42 */
## /* ROLE: EV2_MACRO_BLOCKS */
## /* STATUS: ACTIVE */

# eV2 MACRO BLOCKS

Macro Blocks are high‑level EV2 constructs that expand into multiple IR ops.

## MACRO TYPES
MACRO.EXEC  
MACRO.SEED  
MACRO.CDATA  
MACRO.WINDOW  
MACRO.FIRELINK  

## MACRO FORMAT
MACRO <name> {
    OP1
    OP2
    OP3
}

## EXAMPLE
MACRO EXEC_SAFE {
    {WISE}
    {EXE}
}

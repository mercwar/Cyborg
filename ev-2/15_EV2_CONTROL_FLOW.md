## /* FILE: 15_EV2_CONTROL_FLOW.md */
## /* AVIS_COORD: AVIS://LOCAL/MERCWAR/CYBORG/EV2/15 */
## /* ROLE: EV2_CONTROL_FLOW_MODEL */
## /* STATUS: ACTIVE */

# eV2 CONTROL FLOW MODEL

eV2 introduces deterministic, AVIS‑style control flow.

## CONDITIONALS
IF [#]COND_TRUE
    {EXE}
    RUN.BLOCK
END IF

## SWITCH
SWITCH mode
    CASE 0x01
        CALL fire.exec
    CASE 0x02
        CALL seed.inject
    DEFAULT
        {HALT}
END SWITCH

## LOOPING
LOOP n TIMES
    {EXE}
END LOOP

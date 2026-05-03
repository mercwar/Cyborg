## /* FILE: 27_EV2_FINALIZER.md */
## /* AVIS_COORD: AVIS://LOCAL/MERCWAR/CYBORG/EV2/27 */
## /* ROLE: EV2_FINALIZER */
## /* STATUS: ACTIVE */

# eV2 FINALIZER

The Finalizer performs system sealing and shutdown.

## FINALIZER ADDRESS
[@0x03FF] FINALIZER

## FINALIZER FUNCTION
FUNCTION dn.finalize()
    WRITE.LOG [>] SENTINEL_SCROLL
    APPLY.SEAL [#]0xFF_OMEGA
END FUNCTION

## RULES
- All finalizer calls require `{WISE}`  
- Finalizer cannot be overridden  

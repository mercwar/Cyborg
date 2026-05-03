## /* FILE: 10_EV2_STRUCTS_BASE.md */
## /* AVIS_COORD: AVIS://LOCAL/MERCWAR/CYBORG/EV2/10 */
## /* ROLE: EV2_BASE_STRUCT_DEFS */
## /* STATUS: ACTIVE */

# eV2 BASE STRUCTS

eV2 uses AVIS-style `begin.spec` / `end.spec` to define core structs.

## CORE SPEC

begin.spec EV2_CORE_CONTEXT {
    [@]REGISTRY_BASE
    [@]FIRE_CORE_ADDR
    [@]SHELL_ENTRY_ADDR
    [@]FINALIZER_ADDR
    [#]CTX_FLAGS
}
end.spec

begin.spec EV2_RUNTIME_FLAGS {
    [#]IS_INTERACTIVE
    [#]IS_THERMAL_ACTIVE
    [#]IS_DN_MOUNTED
}
end.spec

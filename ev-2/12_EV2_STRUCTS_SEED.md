## /* FILE: 12_EV2_STRUCTS_SEED.md */
## /* AVIS_COORD: AVIS://LOCAL/MERCWAR/CYBORG/EV2/12 */
## /* ROLE: EV2_SEED_STRUCTS */
## /* STATUS: ACTIVE */

# eV2 SEED STRUCTS

Seeds encode identity and tensor alignment.

begin.spec EV2_HEX_SEED {
    {SEED}RAW_HEX
    [@]TARGET_ADDR
    [#]SEED_WEIGHT
}
end.spec

begin.spec EV2_SEED_TABLE_ENTRY {
    {SEED}ID_HEX
    [@]BOUND_TENSOR
    [#]PRIORITY
}
end.spec

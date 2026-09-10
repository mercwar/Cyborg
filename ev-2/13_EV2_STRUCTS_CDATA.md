## /* FILE: 13_EV2_STRUCTS_CDATA.md */
## /* AVIS_COORD: AVIS://LOCAL/MERCWAR/CYBORG/EV2/13 */
## /* ROLE: EV2_CDATA_STRUCTS */
## /* STATUS: ACTIVE */

# eV2 CDATA STRUCTS

Compressed data packets for EV2 → Fire-Lang transfer.

begin.spec EV2_CDATA_PACKET {
    {CDAT}RAW
    [>]DECOMPRESSED_OUT
    [#]LENGTH
}
end.spec

begin.spec EV2_CDATA_CHANNEL {
    [@]SRC_ADDR
    [@]DST_ADDR
    [#]CHANNEL_FLAGS
}
end.spec

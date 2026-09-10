## /* FILE: 11_EV2_STRUCTS_WINDOW.md */
## /* AVIS_COORD: AVIS://LOCAL/MERCWAR/CYBORG/EV2/11 */
## /* ROLE: EV2_WINDOW_STRUCTS */
## /* STATUS: ACTIVE */

# eV2 WINDOW STRUCTS

Window descriptors bridge UI and DN addresses.

begin.spec EV2_WINDOW_DESCRIPTOR {
    [@]PTR_HWND
    {STR}TITLE
    [#]WINDOW_FLAGS
    {CDAT}STYLE_BLOCK
}
end.spec

begin.spec EV2_WINDOW_EVENT {
    [#]EVENT_TYPE
    [#]KEY_CODE
    [#]MOUSE_STATE
    [@]TARGET_WINDOW
}
end.spec

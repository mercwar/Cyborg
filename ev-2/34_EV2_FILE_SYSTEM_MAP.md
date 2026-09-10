## /* FILE: 34_EV2_FILE_SYSTEM_MAP.md */
## /* AVIS_COORD: AVIS://LOCAL/MERCWAR/CYBORG/EV2/34 */
## /* ROLE: EV2_FILE_SYSTEM_MAP */
## /* STATUS: ACTIVE */

# eV2 FILE SYSTEM MAP

The EV2 File System Map defines how EV2 interacts with structured storage.

## FILE ZONES
- FS.CONFIG  
- FS.CDATA  
- FS.WINDOW_STATE  
- FS.LOGS  
- FS.SENTINEL_SCROLL  

## FILE STRUCT
begin.spec EV2_FILE_ENTRY {
    {STR}NAME
    [#]TYPE
    [#]SIZE
    [@]ADDR
}
end.spec

## RULES
1. All FS writes must be logged to Sentinel Scroll.  
2. CDATA files must be checksum‑verified.  
3. Config files must be seed‑signed.  

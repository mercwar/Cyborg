## /* FILE: 05_EV2_CDATA_PIPE.md */
## /* AVIS_COORD: AVIS://LOCAL/MERCWAR/CYBORG/EV2/05 */
## /* ROLE: EV2_CDATA_PIPELINE */
## /* STATUS: ACTIVE */

# eV2 CDATA PIPELINE

The CDATA Pipeline handles:
- compressed data blocks  
- binary‑safe transfers  
- Fire‑Lang decompression  
- DN registry ingestion  

## DIRECTIVES
- `{CDAT} <blob>` — Declare compressed block  
- `CDAT.UNPACK -> [>]` — Decompress into memory  
- `CDAT.MAP <blob> -> [@addr]` — Bind to address  

## STRUCTURE
begin.spec EV2_CDATA_PACKET {
{CDAT}RAW
[>]DECOMPRESSED_OUT
[#]LENGTH
}
end.spec


## EXAMPLE


{CDAT} 7A6F3B10FF
CDAT.UNPACK -> [>] BUFFER

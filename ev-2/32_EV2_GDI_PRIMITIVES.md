## /* FILE: 32_EV2_GDI_PRIMITIVES.md */
## /* AVIS_COORD: AVIS://LOCAL/MERCWAR/CYBORG/EV2/32 */
## /* ROLE: EV2_GDI_PRIMITIVES */
## /* STATUS: ACTIVE */

# eV2 GDI PRIMITIVES

GDI primitives define the drawing operations available to EV2.

## PRIMITIVES
- GDI.LINE  
- GDI.RECT  
- GDI.TEXT  
- GDI.FILL  
- GDI.CLEAR  

## PRIMITIVE STRUCT
begin.spec EV2_GDI_COMMAND {
    [#]CMD_TYPE
    [#]X1
    [#]Y1
    [#]X2
    [#]Y2
    {STR}TEXT
}
end.spec

## EXAMPLE
GDI.LINE 10 10 200 10

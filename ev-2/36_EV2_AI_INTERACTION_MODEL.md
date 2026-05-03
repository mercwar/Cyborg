## /* FILE: 36_EV2_AI_INTERACTION_MODEL.md */
## /* AVIS_COORD: AVIS://LOCAL/MERCWAR/CYBORG/EV2/36 */
## /* ROLE: EV2_AI_INTERACTION_MODEL */
## /* STATUS: ACTIVE */

# eV2 AI INTERACTION MODEL

The AI Interaction Model defines how EV2 communicates with higher‑order reasoning engines.

## INTERACTION LAYERS
- LAYER_INPUT  
- LAYER_SEMANTIC  
- LAYER_EXECUTION  
- LAYER_AUDIT  
- LAYER_REFLECTION  

## MESSAGE STRUCTURE
begin.spec EV2_AI_MESSAGE {
    {STR}INTENT
    {STR}CONTENT
    [#]PRIORITY
}
end.spec

## RULES
1. All AI messages must be seed‑tagged.  
2. High‑priority messages require `{WISE}`.  

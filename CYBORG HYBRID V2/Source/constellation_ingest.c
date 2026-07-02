// [AVIS-AI-SCAN] FILE: constellation_ingest.c | CLASS: INGESTION_PIPELINE | TARGET: WIN64_UCRT
#include "cyborg_core.h"
#include "constellation_map.h"

MapNode WorkspaceGraph[MAX_NODES];
int ActiveGraphNodeCount = 0;

void InitConstellationMap(void) {
    ActiveGraphNodeCount = 0;
    memset(WorkspaceGraph, 0, sizeof(WorkspaceGraph));
    printf("[CONSTELLATION INGEST]: Topological Graph Matrix Cleared.\n");
}

void RegisterIngestArtifact(const char* filepath) {
    if (ActiveGraphNodeCount >= MAX_NODES) return;
    
    strncpy(WorkspaceGraph[ActiveGraphNodeCount].node_id, filepath, 63);
    WorkspaceGraph[ActiveGraphNodeCount].visibility_flag = 1;
    
    printf("[CONSTELLATION INGEST]: Ingested node [%d]: %s (Visibility Asserted)\n", 
           ActiveGraphNodeCount, WorkspaceGraph[ActiveGraphNodeCount].node_id);
    ActiveGraphNodeCount++;
}

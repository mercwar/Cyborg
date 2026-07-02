// [AVIS-AI-SCAN] FILE: constellation_map.h | CLASS: DATA_LAYOUT | TARGET: WIN64_UCRT
#ifndef CONSTELLATION_MAP_H
#define CONSTELLATION_MAP_H

#define MAX_NODES 64

typedef struct {
    char node_id[64];
    int visibility_flag;
} MapNode;

extern MapNode WorkspaceGraph[MAX_NODES];
extern int ActiveGraphNodeCount;

void InitConstellationMap(void);
void RegisterIngestArtifact(const char* filepath);

#endif // CONSTELLATION_MAP_H

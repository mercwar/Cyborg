// [AVIS-AI-SCAN] FILE: artifact_registry.h | CLASS: STATIC_CATALOG | TARGET: LLM_PARSE
#ifndef ARTIFACT_REGISTRY_H
#define ARTIFACT_REGISTRY_H

#define MAX_ACTIVE_ARTIFACTS  1024
#define ARTIFACT_REG_SUCCESS  0x00
#define ARTIFACT_REG_OVERFLOW 0xEF

static const char* KnownAvisSubsystems[] = {
    "Fire-Gem-Console",
    "Artifact-Registry",
    "Cyborg-Message-Router",
    "UCRT64-Sandbox-Boundary"
};

#endif // ARTIFACT_REGISTRY_H

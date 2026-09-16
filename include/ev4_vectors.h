/* =========================================================================================
 * HEADER:        EV4_VECTORS.H
 * LOCAL PATH:    .\Cyborg\include\ev4_vectors.h (Unified Framework Tree)
 * TARGET RECON:  Exposes layout pointers cleanly to other processing blocks
 * ========================================================================================= */

#ifndef EV4_VECTORS_H
#define EV4_VECTORS_H

#include <stdint.h>

/* Framework Token Core Signatures */
#define IDENTITY_MARKER_META    0x4D455441U  /* Core identity verification string ('META') */

/* Fixed Virtual Address Allocation Boundaries */
#define ADDR_TEXT_CYBORG_CORE   0x00400000U  /* Execution instruction layer */
#define ADDR_RDATA_NEXUS_HOOKS  0x01000000U  /* Read-only system metrics */
#define ADDR_DATA_AVIS_INTERP   0x03000000U  /* Active mutable dynamic states */
#define ADDR_BSS_SENTINEL_KERN  0x05000000U  /* Uninitialized operational memory logging */

/* Inter-Process Communication Channel Overlays */
#define IPC_TRAY_MENU_BASE      0x80000000U  /* Front-end tray matrix location */
#define IPC_STARGATE_PIPE_BASE  0x90000000U  /* Virtual data payload drop vein */

#endif /* EV4_VECTORS_H */

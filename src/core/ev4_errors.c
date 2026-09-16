/* =========================================================================================
 * IMPLEMENTATION: EV.4 SYSTEM ERROR LOOKUP AND SUBSYSTEM INTERCEPT MANAGEMENT
 * LOCAL PATH:     .\Cyborg\src\core\ev4_errors.c
 * ========================================================================================= */

#include "../include/ev4_vectors.h"
#include <stdbool.h>

/* Explicit Error Level Manifest Mapping */
typedef enum {
    EV4_LEVEL_SUCCESS  = 0x00000000U,  /* Everything aligned */
    EV4_LEVEL_WARNING  = 0x0000A401U,  /* Recoverable pipe pollution */
    EV4_LEVEL_FAULT    = 0x0000E402U,  /* Engine buffer exhaustion */
    EV4_LEVEL_CRITICAL = 0xDEADBEEFU   /* Framework tracking breakdown */
} Ev4ErrorLevel;

/* Low-level Assembly hook to perform rapid data lane purge on Level 1 & 2 errors */
extern void ClearStargateVein(void);

/* -----------------------------------------------------------------------------------------
 * FUNCTION: ProcessEv4ErrorHorizon
 * DIRECTIVE: Direct register-level inspection and status routing based on code severity
 * ----------------------------------------------------------------------------------------- */
uint32_t ProcessEv4ErrorHorizon(Ev4ErrorLevel reported_level) {
    volatile uint32_t *stargate_vein  = (volatile uint32_t *)0x90000000;
    volatile uint32_t *tray_menu_pipe = (volatile uint32_t *)0x80000000;

    // Direct error mapping logic block
    switch(reported_level) {
        
        case EV4_LEVEL_SUCCESS:
            // State: Aligned. Pulse normal operational signature to UI layout.
            *stargate_vein = 0x00A400FFU; 
            return 0;

        case EV4_LEVEL_WARNING:
            // State: Pipe drift detected. Flush the Stargate communication vein natively.
            ClearStargateVein();
            *stargate_vein = EV4_LEVEL_WARNING;
            return 1;

        case EV4_LEVEL_FAULT:
            // State: Stargate payload threshold bottleneck. Freeze active AI context tracking.
            // Instructs robot processing loops to temporarily cache pending string tokens
            *stargate_vein = EV4_LEVEL_FAULT;
            return 2;

        case EV4_LEVEL_CRITICAL:
        default:
            // State: Fatal token mismatch. Force immediate framework isolation.
            *stargate_vein = EV4_LEVEL_CRITICAL;
            *tray_menu_pipe = 0x00000000U; // Wipe human-machine interface pipeline link
            return 3;
    }
}

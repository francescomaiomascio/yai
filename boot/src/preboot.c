#include "preboot.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>

int yai_ensure_directories(const char *ws_id) {
    char path[1024];
    const char* home = getenv("HOME");
    
    // Costruiamo ~/.yai/run/{ws_id}
    snprintf(path, sizeof(path), "%s/.yai/run/%s", home, ws_id);
    
    // mkdir -p (molto semplificato per C)
    char tmp[1024];
    snprintf(tmp, sizeof(tmp), "mkdir -p %s", path);
    
    if (system(tmp) != 0) {
        fprintf(stderr, "[PREBOOT-ERROR] Failed to create runtime directory: %s\n", path);
        return -1;
    }
    return 0;
}

int yai_run_preboot_checks() {
    if (getuid() == 0) {
        printf("[PREBOOT] Warning: Running as root is not YAI-compliant (Risk Violation)\n");
    }
    return 0; 
}

void yai_discover_environment(yai_vault_t *vault) {
    printf("[DISCOVERY] Mapping workspace: %s\n", vault->workspace_id);
    
    // Garantiamo che la cartella esista prima di provare a creare il socket
    if (yai_ensure_directories(vault->workspace_id) == 0) {
        printf("[DISCOVERY] Runtime directory ready for %s\n", vault->workspace_id);
    }

    snprintf(vault->trace_id, MAX_TRACE_ID, "boot-%08x", 0xDEADC0DE);
}
#ifndef PREBOOT_H
#define PREBOOT_H

#include "yai_vault.h"

// Verifica l'integrità dell'ambiente
int yai_run_preboot_checks();

// Mappa l'ambiente, crea le directory (~/.yai/run/dev) e popola il Vault
void yai_discover_environment(yai_vault_t *vault);

// Helper per garantire che i path esistano
int yai_ensure_directories(const char *ws_id);

#endif
#ifndef YAI_PREBOOT_H
#define YAI_PREBOOT_H

#include "yai_vault.h"

int yai_run_preboot_checks(void);
int yai_ensure_runtime_layout(const char *ws_id);
void yai_discover_environment(yai_vault_t *vault);

#endif

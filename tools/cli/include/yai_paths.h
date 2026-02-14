#ifndef YAI_PATHS_H
#define YAI_PATHS_H

#include <stddef.h>

// ADR-002: Il punto di ingresso unico
int yai_path_root_sock(char *out, size_t cap);

// ADR-001: Gestione directory tenant e database
int yai_path_ws_run_dir(const char *ws_id, char *out, size_t cap);
int yai_path_ws_db(const char *ws_id, char *out, size_t cap);

// Legacy/Compatibility
int yai_path_control_sock(const char *ws_id, char *out, size_t cap);

#endif
#ifndef YAI_PATHS_H
#define YAI_PATHS_H

#include <stddef.h>

/* ============================================================
   ROOT (Machine Plane)
   ============================================================ */

int yai_path_root_sock(char *out, size_t cap);

/* ============================================================
   WORKSPACE (Tenant Plane)
   ============================================================ */

int yai_path_ws_sock(const char *ws_id, char *out, size_t cap);
int yai_path_ws_run_dir(const char *ws_id, char *out, size_t cap);
int yai_path_ws_db(const char *ws_id, char *out, size_t cap);

#endif

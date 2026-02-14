// tools/cli/src/paths.c
#include "yai_paths.h"
#include "yai_env.h"
#include <stdio.h>
#include <string.h>

/**
 * Ritorna il socket del Root Control Plane (ADR-002).
 * La CLI si connette SEMPRE qui, indipendentemente dal workspace.
 */
int yai_path_root_sock(char *out, size_t cap) {
    if (!out || cap < 8) return -1;
    const char *home = yai_env_home();
    if (!home) return -2;

    int n = snprintf(out, cap, "%s/.yai/run/root.sock", home);
    if (n <= 0 || (size_t)n >= cap) return -3;
    return 0;
}

/**
 * Ritorna il path per il database SQLite di un workspace specifico.
 * Utile per il Blocco 3 (Storage Gate).
 */
int yai_path_ws_db(const char *ws_id, char *out, size_t cap) {
    if (!ws_id || !ws_id[0] || !out || cap < 8) return -1;
    const char *home = yai_env_home();
    if (!home) return -2;

    int n = snprintf(out, cap, "%s/.yai/run/%s/semantic.sqlite", home, ws_id);
    if (n <= 0 || (size_t)n >= cap) return -3;
    return 0;
}

/**
 * Deprecato/Legacy: Manteniamo la firma per compatibilità se necessaria,
 * ma facciamo in modo che punti al root socket per evitare errori di connessione.
 */
int yai_path_control_sock(const char *ws_id, char *out, size_t cap) {
    (void)ws_id; // ws_id ignorato, usiamo il Root Plane
    return yai_path_root_sock(out, cap);
}
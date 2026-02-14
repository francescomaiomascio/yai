#include "../include/yai_envelope.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

/**
 * Genera un Trace ID unico per la sessione CLI.
 * Formato: cli-<timestamp>-<pid>-<counter>
 */
void yai_make_trace_id(char out[64]) {
    static unsigned long long ctr = 0;
    unsigned long long t = (unsigned long long)time(NULL);
    unsigned long long p = (unsigned long long)getpid();
    ctr++;
    snprintf(out, 64, "cli-%llx-%llx-%llx", t, p, ctr);
}

/**
 * ADR-004: Costruttore dell'Envelope V1.
 * Questa è l'unica funzione che genera il JSON che viaggia sul Root Socket.
 */
int yai_build_v1_envelope(
    const char *bin,         // L1: kernel, L2: engine, L3: mind
    const char *ws_id,       // Tenant ID (opzionale per L1, obbligatorio per L3)
    const char *trace_id,    // Per il debugging distribuito
    const char *req_type,    // Il metodo RPC (es. "put_node")
    const char *payload_json,// Il corpo della richiesta (già JSON)
    char *out,
    size_t out_cap
) {
    if (!bin || !bin[0] || !req_type || !req_type[0] || !out || out_cap < 64) {
        return -1;
    }

    // Gestione dei null per il JSON
    const char *target_ws = (ws_id && ws_id[0]) ? ws_id : NULL;
    const char *body = (payload_json && payload_json[0]) ? payload_json : "{}";

    // Costruiamo la struttura piatta per massimizzare la velocità di parsing nel Kernel
    // { "v": 1, "bin": "...", "ws_id": "...", "type": "...", "trace": "...", "params": {...} }
    int n;
    if (target_ws) {
        n = snprintf(
            out, out_cap,
            "{\"v\":1,\"bin\":\"%s\",\"ws_id\":\"%s\",\"type\":\"%s\",\"trace\":\"%s\",\"params\":%s}\n",
            bin, target_ws, req_type, trace_id, body
        );
    } else {
        n = snprintf(
            out, out_cap,
            "{\"v\":1,\"bin\":\"%s\",\"ws_id\":null,\"type\":\"%s\",\"trace\":\"%s\",\"params\":%s}\n",
            bin, req_type, trace_id, body
        );
    }

    if (n <= 0 || (size_t)n >= out_cap) return -2;
    return 0;
}

/**
 * Deprecato: Mantenuto per compatibilità con i vecchi moduli cmd_*.
 * Reindirizza alla nuova logica V1.
 */
int yai_build_request_jsonl(
    const char *ws_id,
    const char *trace_id,
    int arming,
    const char *role,
    const char *req_type,
    const char *payload_json,
    char *out,
    size_t out_cap
) {
    (void)arming; (void)role; // Informazioni ora gestite nell'header della sessione Kernel
    return yai_build_v1_envelope("kernel", ws_id, trace_id, req_type, payload_json, out, out_cap);
}
#ifndef YAI_ENVELOPE_H
#define YAI_ENVELOPE_H

#include <stddef.h>

#define YAI_RPC_V1 1

void yai_make_trace_id(char out[64]);

// La nuova busta ADR-004
int yai_build_v1_envelope(
    const char *bin,
    const char *ws_id,
    const char *trace_id,
    const char *req_type,
    const char *payload_json,
    char *out,
    size_t out_cap
);

// Vecchia firma (mantenuta per evitare break immediati altrove)
int yai_build_request_jsonl(
    const char *ws_id,
    const char *trace_id,
    int arming,
    const char *role,
    const char *req_type,
    const char *payload_json,
    char *out,
    size_t out_cap
);

#endif
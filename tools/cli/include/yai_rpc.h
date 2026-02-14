#ifndef YAI_RPC_H
#define YAI_RPC_H

#include <stddef.h>

#define YAI_RPC_LINE_MAX 4096

typedef struct {
    int fd;
    char ws_id[64];
} yai_rpc_client_t;

int yai_rpc_connect(yai_rpc_client_t *c, const char *ws_id);
void yai_rpc_close(yai_rpc_client_t *c);

// DEVE AVERE 3 ARGOMENTI: client, binary, version
int yai_rpc_handshake(yai_rpc_client_t *c, const char *bin, const char *cv);
int yai_rpc_call(
    yai_rpc_client_t *c,
    const char *bin,
    const char *request_type,
    const char *payload_json,
    char *out_line,
    size_t out_cap
);

#endif
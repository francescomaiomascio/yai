#include "../include/yai_cli.h"
#include "../include/yai_rpc.h"
#include <stdio.h>
#include <string.h>

/**
 * L2: Engine Gates Dispatcher
 * Gestisce l'accesso ai gate di sistema (Storage, Network, Resource).
 */
int yai_cmd_engine(int argc, char **argv, const yai_cli_opts_t *opt) {
    if (argc < 2) {
        printf("Engine Gates (L2)\nUsage: yai engine [--ws id] <storage|network|resource> <method> [params]\n");
        return 1;
    }

    const char *gate = argv[0];
    const char *method = argv[1];
    const char *params = (argc > 2) ? argv[2] : "{}";

    yai_rpc_client_t client;
    char response[YAI_RPC_LINE_MAX];

    // ADR-001: L'Engine richiede isolamento per workspace
    if (yai_rpc_connect(&client, opt->ws_id) != 0) {
        fprintf(stderr, "ERR: Could not connect to Root Plane.\n");
        return -1;
    }

    // Prefissiamo il metodo con il gate (es: "storage_put_node")
    char rpc_method[128];
    snprintf(rpc_method, sizeof(rpc_method), "%s_%s", gate, method);

    // CORREZIONE: Firma a 6 argomenti allineata a yai_rpc.h
    int rc = yai_rpc_call(
        &client, 
        "engine",         // bin target (L2)
        rpc_method,       // request type 
        params,           // payload json
        response,         // buffer di output
        sizeof(response)  // dimensione buffer
    );
    
    if (rc == 0) {
        printf("%s\n", response);
    } else {
        fprintf(stderr, "RPC_ERROR: %d\n", rc);
    }

    yai_rpc_close(&client);
    return rc;
}
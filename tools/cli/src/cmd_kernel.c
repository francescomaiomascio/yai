#include "../include/yai_cli.h"
#include "../include/yai_rpc.h"
#include <stdio.h>
#include <string.h>

/**
 * L1: Kernel Dispatcher
 * Gestisce i comandi di sistema che non richiedono isolamento tenant.
 */
int yai_cmd_kernel(int argc, char **argv, const yai_cli_opts_t *opt) {
    if (argc < 1) {
        printf("Kernel Control (L1)\nUsage: yai kernel <status|ping|stop>\n");
        return 1;
    }

    const char *cmd = argv[0];
    yai_rpc_client_t client;
    char response[YAI_RPC_LINE_MAX];

    // Il kernel (L1) solitamente non richiede ws_id per lo status globale
    if (yai_rpc_connect(&client, NULL) != 0) {
        fprintf(stderr, "ERR: Connection to Root Plane failed. Is yai-kernel running?\n");
        return -1;
    }

    // Handshake iniziale per validare la versione del protocollo
    const char *ver = opt->client_version ? opt->client_version : "cli-c/1.0";
    if (yai_rpc_handshake(&client, "kernel", ver) != 0) {
        fprintf(stderr, "ERR: Protocol handshake failed.\n");
        yai_rpc_close(&client);
        return 4;
    }

    // CORREZIONE: Firma a 6 argomenti allineata a yai_rpc.h
    int rc = yai_rpc_call(
        &client, 
        "kernel",         // bin target
        cmd,              // request type
        "{}",             // payload vuoto per comandi base
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
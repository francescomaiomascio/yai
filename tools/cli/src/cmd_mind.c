#include "../include/yai_cmd.h"
#include "../include/yai_rpc.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * L3: Mind & Cognition Dispatcher
 * Gestisce chat, query e task cognitivi.
 */
int yai_cmd_mind(int argc, char **argv, const yai_cli_opts_t *opt) {
    if (argc < 1) {
        printf("Mind Intelligence Interface (L3)\n");
        printf("Usage: yai mind <chat|think|query> <prompt>\n");
        return 1;
    }

    const char *method = argv[0];
    const char *prompt = (argc >= 2) ? argv[1] : "";

    if (strlen(prompt) == 0) {
        fprintf(stderr, "ERR: Mind level requires a prompt/input.\n");
        return 2;
    }

    yai_rpc_client_t client;
    char response[YAI_RPC_LINE_MAX];

    // Connessione al Root Plane (Isolation enforced by ws_id)
    if (yai_rpc_connect(&client, opt->ws_id) != 0) {
        fprintf(stderr, "ERR: Could not connect to Root Plane.\n");
        return -1;
    }

    // Costruiamo il payload per la cognizione
    char payload[2048]; // Buffer più largo per i prompt
    snprintf(payload, sizeof(payload), "{\"prompt\":\"%s\",\"stream\":false}", prompt);

    printf("[MIND:%s] Thinking...\n", opt->ws_id);

    // CORREZIONE: Passiamo correttamente i 6 argomenti definiti in yai_rpc.h
    int rc = yai_rpc_call(
        &client, 
        "mind",           // bin target
        method,           // request type (chat/think/etc)
        payload,          // payload json
        response,         // output buffer
        sizeof(response)  // output cap
    );

    if (rc == 0) {
        // Stampiamo la risposta. Se non è --json, potremmo voler pulire l'output in futuro
        printf("\n%s\n", response);
    } else {
        fprintf(stderr, "ERR: Mind RPC call failed (rc=%d)\n", rc);
    }

    yai_rpc_close(&client);
    return rc;
}
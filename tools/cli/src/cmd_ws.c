#include "../include/yai_cli.h"
#include "../include/yai_rpc.h"
#include "../../../engine/src/external/cJSON.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Aggiunto const qui
int yai_cmd_ws(int argc, char **argv, const yai_cli_opts_t *opt) {
    if (argc < 1) {
        printf("Workspace Management (L1)\n");
        printf("Usage: yai kernel ws <create|list|destroy> [id]\n");
        return 1;
    }

    const char *sub = argv[0];
    yai_rpc_client_t client;
    char response[YAI_RPC_LINE_MAX];

    if (yai_rpc_connect(&client, opt->ws_id) != 0) {
        fprintf(stderr, "FATAL: Could not connect to Root Plane.\n");
        return -1;
    }

    int status = 0;

    if (strcmp(sub, "create") == 0) {
        if (argc < 2) { fprintf(stderr, "Usage: yai kernel ws create <id>\n"); return 1; }
        char payload[128];
        snprintf(payload, sizeof(payload), "{\"ws_id\":\"%s\"}", argv[1]);
        status = yai_rpc_call(&client, "kernel", "ws_create", payload, response, sizeof(response));
        if (status == 0) printf("WS_CREATED: %s\n", argv[1]);
    } 
    else if (strcmp(sub, "list") == 0) {
        status = yai_rpc_call(&client, "kernel", "ws_list", "{}", response, sizeof(response));
        if (status == 0) {
            if (opt->json) {
                printf("%s\n", response);
            } else {
                cJSON *root = cJSON_Parse(response);
                if (root) {
                    // Otteniamo la lista "params" (assumendo sia un array)
                    cJSON *list = cJSON_GetObjectItem(root, "params");
                    printf("Active Workspaces:\n");
                    
                    // Sostituiamo la macro problematica con un loop standard cJSON
                    cJSON *item = NULL;
                    if (list) {
                        for (item = list->child; item != NULL; item = item->next) {
                             if (item->valuestring) printf(" - %s\n", item->valuestring);
                        }
                    }
                    cJSON_Delete(root);
                }
            }
        }
    }
    else if (strcmp(sub, "destroy") == 0) {
        if (argc < 2) { fprintf(stderr, "Usage: yai kernel ws destroy <id>\n"); return 1; }
        if (!opt->arming) { 
            fprintf(stderr, "ERR: Destroying a workspace requires --arming flag.\n"); 
            return 1; 
        }
        char payload[128];
        snprintf(payload, sizeof(payload), "{\"ws_id\":\"%s\"}", argv[1]);
        status = yai_rpc_call(&client, "kernel", "ws_destroy", payload, response, sizeof(response));
        if (status == 0) printf("WS_DESTROYED: %s\n", argv[1]);
    } 

    yai_rpc_close(&client);
    return status;
}
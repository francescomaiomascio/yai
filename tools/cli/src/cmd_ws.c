#include "../include/yai_fmt.h"
#include "../include/yai_cli.h"
#include "../include/yai_rpc.h"

#include <protocol/yai_protocol_ids.h>

#include <stdio.h>
#include <string.h>

/* ============================================================
   L1: Workspace Management (via Root Machine Plane)
   ============================================================ */

static void ws_usage(void) {
    printf("Workspace Management (L1 - Root Plane)\n");
    printf("Usage:\n");
    printf("  yai ws create  <id>\n");
    printf("  yai ws list\n");
    printf("  yai ws destroy <id>   (requires --arming)\n");
}

int yai_cmd_ws(int argc, char **argv, const yai_cli_opts_t *opt)
{
    if (argc < 1) {
        ws_usage();
        return 1;
    }

    const char *sub = argv[0];

    yai_rpc_client_t client;
    char response[YAI_RPC_LINE_MAX];
    uint32_t resp_len = 0;

    /* ============================================================
       CONNECT TO ROOT MACHINE PLANE
       ============================================================ */

    /* CRITICAL: root machine ws_id is "system" */
    if (yai_rpc_connect(&client, "system") != 0) {
        fprintf(stderr, "ERR: cannot connect to root plane\n");
        return -1;
    }

    /* ============================================================
       AUTHORITY
       ============================================================ */

    yai_rpc_set_authority(
        &client,
        (opt && opt->arming) ? 1 : 0,
        (opt && opt->role) ? opt->role : "operator"
    );

    /* ============================================================
       HANDSHAKE
       ============================================================ */

    if (yai_rpc_handshake(&client) != 0) {
        fprintf(stderr, "ERR: handshake failed\n");
        yai_rpc_close(&client);
        return -2;
    }

    /* ============================================================
       BUILD PAYLOAD
       ============================================================ */

    char payload[512];

    if (strcmp(sub, "list") == 0) {

        snprintf(payload, sizeof(payload),
                 "{\"method\":\"ws_list\",\"params\":{}}");

    } 
    else if (strcmp(sub, "create") == 0 ||
             strcmp(sub, "destroy") == 0) {

        if (argc < 2) {
            ws_usage();
            yai_rpc_close(&client);
            return -3;
        }

        const char *method =
            (strcmp(sub, "create") == 0)
            ? "ws_create"
            : "ws_destroy";

        snprintf(payload, sizeof(payload),
                 "{\"method\":\"%s\",\"params\":{\"ws_id\":\"%s\"}}",
                 method,
                 argv[1]);
    } 
    else {
        ws_usage();
        yai_rpc_close(&client);
        return -4;
    }

    /* ============================================================
       RPC CALL
       ============================================================ */

    int rc = yai_rpc_call_raw(
        &client,
        YAI_CMD_CONTROL,
        payload,
        (uint32_t)strlen(payload),
        response,
        sizeof(response) - 1,
        &resp_len
    );

    if (rc == 0) {
        response[resp_len] = '\0';
        yai_print_response(response, opt ? opt->json : 0);
    } else {
        fprintf(stderr, "ERR: ws command failed (%d)\n", rc);
    }

    yai_rpc_close(&client);
    return rc;
}

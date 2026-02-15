#include "../include/yai_fmt.h"
#include "../include/yai_cmd.h"
#include "../include/yai_rpc.h"

#include <protocol/yai_protocol_ids.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* ============================================================
   L3: Mind Dispatcher (Workspace Plane)
   ============================================================ */

int yai_cmd_mind(int argc, char **argv, const yai_cli_opts_t *opt)
{
    if (argc < 2) {
        printf("Mind (L3)\n");
        printf("Usage: yai mind --ws <id> <chat|think|query> <prompt>\n");
        return 1;
    }

    if (!opt || !opt->ws_id || !opt->ws_id[0]) {
        fprintf(stderr, "FATAL: mind requires --ws <id>\n");
        return 2;
    }

    const char *method = argv[0];
    const char *prompt = argv[1];

    yai_rpc_client_t client;
    char response[YAI_RPC_LINE_MAX];
    uint32_t resp_len = 0;

    /* -------- CONNECT TO WORKSPACE PLANE -------- */

    if (yai_rpc_connect(&client, opt->ws_id) != 0)
        return -3;

    /* -------- AUTHORITY -------- */

    yai_rpc_set_authority(
        &client,
        opt->arming ? 1 : 0,
        opt->role ? opt->role : "guest"
    );

    /* -------- HANDSHAKE -------- */

    if (yai_rpc_handshake(&client) != 0) {
        yai_rpc_close(&client);
        return -4;
    }

    /* -------- PAYLOAD -------- */

    char payload[8192];

    int n = snprintf(
        payload,
        sizeof(payload),
        "{\"method\":\"%s\",\"params\":{\"prompt\":\"%s\",\"stream\":false}}",
        method,
        prompt
    );

    if (n <= 0 || (size_t)n >= sizeof(payload)) {
        yai_rpc_close(&client);
        return -5;
    }

    /* -------- RPC CALL -------- */

    int rc = yai_rpc_call_raw(
        &client,
        YAI_CMD_PROVIDER_RPC,   /* Mind still routed via provider gate */
        payload,
        (uint32_t)strlen(payload),
        response,
        sizeof(response) - 1,
        &resp_len
    );

    if (rc == 0) {
        response[resp_len] = '\0';
        yai_print_response(response, opt ? opt->json : 0);
    }

    yai_rpc_close(&client);
    return rc;
}

#include "../include/yai_fmt.h"
#include "../include/yai_cli.h"
#include "../include/yai_rpc.h"

#include <protocol/yai_protocol_ids.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
 * L1: Kernel Dispatcher (via Root Machine Plane)
 *
 * Usage:
 *   yai kernel <ping|status|stop|...>
 *
 * Behavior:
 *   - Connects to Root Machine Plane (ws_id = "system")
 *   - Authority set before handshake
 *   - Strict binary envelope
 */

int yai_cmd_kernel(int argc, char **argv, const yai_cli_opts_t *opt)
{
    if (argc < 1) {
        fprintf(stderr, "Usage: yai kernel <command>\n");
        return 1;
    }

    const char *cmd = argv[0];

    uint32_t command_id =
        (strcmp(cmd, "ping") == 0)
        ? YAI_CMD_PING
        : YAI_CMD_CONTROL;

    yai_rpc_client_t client;
    char response[YAI_RPC_LINE_MAX];
    uint32_t resp_len = 0;

    /* ============================================================
       CONNECT TO ROOT MACHINE PLANE
       ============================================================ */

    /* CRITICAL: root plane ws_id is "system" */
    if (yai_rpc_connect(&client, "system") != 0) {
        fprintf(stderr, "ERR: cannot connect to root plane\n");
        return -1;
    }

    /* ============================================================
       AUTHORITY
       ============================================================ */

    yai_rpc_set_authority(
        &client,
        opt ? opt->arming : 0,
        opt && opt->role ? opt->role : "operator"
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

    char payload[256];

    int n = snprintf(
        payload,
        sizeof(payload),
        "{\"method\":\"%s\",\"params\":{}}",
        cmd
    );

    if (n <= 0 || (size_t)n >= sizeof(payload)) {
        fprintf(stderr, "ERR: payload build failed\n");
        yai_rpc_close(&client);
        return -3;
    }

    /* ============================================================
       RPC CALL
       ============================================================ */

    int rc = yai_rpc_call_raw(
        &client,
        command_id,
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
        fprintf(stderr, "ERR: kernel command failed (%d)\n", rc);
    }

    yai_rpc_close(&client);
    return rc;
}

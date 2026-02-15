#define _POSIX_C_SOURCE 200809L

#include "../include/yai_cmd.h"
#include "../include/yai_rpc.h"
#include "../include/yai_fmt.h"

#include <protocol/yai_protocol_ids.h>

#include <stdio.h>
#include <string.h>

/* ============================================================
   USAGE
   ============================================================ */

static void usage_root(void)
{
    fprintf(stderr,
        "Machine Root Plane\n"
        "Usage:\n"
        "  yai root status\n"
        "  yai root ping\n");
}

/* ============================================================
   CONNECT ROOT (system plane)
   ============================================================ */

static int connect_root(yai_rpc_client_t *c)
{
    memset(c, 0, sizeof(*c));

    /* Root machine plane uses ws_id = "system" */
    if (yai_rpc_connect(c, "system") != 0)
        return -1;

    return 0;
}

/* ============================================================
   HANDSHAKE
   ============================================================ */

static int root_handshake(yai_rpc_client_t *c,
                          const yai_cli_opts_t *opt)
{
    /* Authority before handshake */
    yai_rpc_set_authority(
        c,
        opt && opt->arming ? 1 : 0,
        opt && opt->role ? opt->role : "operator"
    );

    return yai_rpc_handshake(c);
}

/* ============================================================
   STATUS / PING
   ============================================================ */

static int cmd_root_status(const yai_cli_opts_t *opt)
{
    yai_rpc_client_t c;

    if (connect_root(&c) != 0)
        return -5;

    if (root_handshake(&c, opt) != 0) {
        yai_rpc_close(&c);
        return -6;
    }

    char response[YAI_RPC_LINE_MAX];
    uint32_t resp_len = 0;

    int rc = yai_rpc_call_raw(
        &c,
        YAI_CMD_PING,
        NULL,
        0,
        response,
        sizeof(response) - 1,
        &resp_len
    );

    if (rc == 0) {
        response[resp_len] = '\0';
        yai_print_response(response, opt ? opt->json : 0);
    }

    yai_rpc_close(&c);
    return rc;
}

static int cmd_root_ping(const yai_cli_opts_t *opt)
{
    return cmd_root_status(opt);
}

/* ============================================================
   ENTRY
   ============================================================ */

int yai_cmd_root(int argc,
                 char **argv,
                 const yai_cli_opts_t *opt)
{
    if (argc < 1) {
        usage_root();
        return 1;
    }

    if (strcmp(argv[0], "status") == 0)
        return cmd_root_status(opt);

    if (strcmp(argv[0], "ping") == 0)
        return cmd_root_ping(opt);

    if (strcmp(argv[0], "help") == 0) {
        usage_root();
        return 0;
    }

    usage_root();
    return 2;
}

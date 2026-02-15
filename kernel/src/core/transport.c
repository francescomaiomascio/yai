#define _POSIX_C_SOURCE 200809L

#include <protocol/transport.h>
#include <protocol/yai_protocol_ids.h>

#include "kernel.h"
#include "yai_kernel.h"
#include "yai_session.h"
#include "control_transport.h"

#include <sys/socket.h>
#include <sys/un.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

#ifndef YAI_RUNTIME_BACKLOG
#define YAI_RUNTIME_BACKLOG 8
#endif

static int server_fd = -1;

/* ============================================================
   SOCKET PATH (ENGINE RUNTIME PLANE)
============================================================ */

static int resolve_socket_path(char *out, size_t cap)
{
    if (!out || cap < 32)
        return -1;

    const char *home = getenv("HOME");
    if (!home || !home[0])
        home = "/tmp";

    int n = snprintf(out,
                     cap,
                     "%s/.yai/run/engine/control.sock",
                     home);

    if (n <= 0 || (size_t)n >= cap)
        return -2;

    return 0;
}

/* ============================================================
   HANDLE CLIENT (STRICT BINARY FRAME)
============================================================ */

static void handle_client(int client_fd)
{
    yai_rpc_envelope_t env;
    char payload[YAI_MAX_PAYLOAD];

    ssize_t plen =
        yai_control_read_frame(client_fd,
                               &env,
                               payload,
                               sizeof(payload));

    if (plen <= 0) {
        close(client_fd);
        return;
    }

    /* --- STRICT HEADER CHECK --- */

    if (env.magic != YAI_FRAME_MAGIC) {
        fprintf(stderr, "[ENGINE] Bad magic\n");
        close(client_fd);
        return;
    }

    if (env.version != YAI_PROTOCOL_IDS_VERSION) {
        fprintf(stderr, "[ENGINE] Bad version\n");
        close(client_fd);
        return;
    }

    /* --- ws_id sanity (NO slash allowed) --- */

    if (strchr(env.ws_id, '/')) {
        fprintf(stderr,
            "[ENGINE] Invalid ws_id detected: %s\n",
            env.ws_id);
        close(client_fd);
        return;
    }

    /* --- Dispatch --- */

    yai_session_dispatch(client_fd, &env, payload);

    close(client_fd);
}

/* ============================================================
   INIT
============================================================ */

int yai_transport_init(void)
{
    char path[256];

    if (resolve_socket_path(path, sizeof(path)) != 0)
        return -1;

    unlink(path);

    server_fd = yai_control_listen_at(path);
    if (server_fd < 0)
        return -2;

    fprintf(stderr,
        "[ENGINE] Runtime Plane online (%s)\n",
        path);

    return 0;
}

/* ============================================================
   SERVE LOOP
============================================================ */

void yai_transport_serve_once(void)
{
    if (server_fd < 0)
        return;

    int client_fd = accept(server_fd, NULL, NULL);

    if (client_fd < 0)
        return;

    handle_client(client_fd);
}

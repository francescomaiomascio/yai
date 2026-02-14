#include "../include/yai_rpc.h"
#include "../include/yai_paths.h"
#include "../include/yai_envelope.h"

#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>

static const char *safe_cstr(const char *s) { return (s && s[0]) ? s : ""; }

static int write_all(int fd, const void *buf, size_t n) {
    const char *p = (const char *)buf;
    size_t off = 0;
    while (off < n) {
        ssize_t w = write(fd, p + off, n - off);
        if (w < 0) {
            if (errno == EINTR) continue;
            return -1;
        }
        off += (size_t)w;
    }
    return 0;
}

static int read_line(int fd, char *out, size_t cap) {
    if (!out || cap < 2) return -1;
    size_t i = 0;
    while (i + 1 < cap) {
        char c;
        ssize_t r = read(fd, &c, 1);
        if (r <= 0) {
            if (r < 0 && errno == EINTR) continue;
            break;
        }
        out[i++] = c;
        if (c == '\n') break;
    }
    out[i] = '\0';
    return (int)i;
}

/**
 * ADR-002: Connessione al Root Control Plane.
 * Il ws_id non serve più per trovare il socket, ma lo salviamo nel contesto 
 * del client per includerlo in ogni chiamata successiva.
 */
int yai_rpc_connect(yai_rpc_client_t *c, const char *ws_id) {
    if (!c) return -1;
    memset(c, 0, sizeof(*c));
    c->fd = -1;

    char sock_path[512];
    // Ora puntiamo SEMPRE al root.sock
    if (yai_path_root_sock(sock_path, sizeof(sock_path)) != 0) return -2;

    int fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (fd < 0) return -3;

    struct sockaddr_un addr;
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, sock_path, sizeof(addr.sun_path) - 1);

    if (connect(fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        close(fd);
        return -5; // Kernel probabilmente non avviato
    }

    c->fd = fd;
    // Salviamo il target per le chiamate future
    if (ws_id) strncpy(c->ws_id, ws_id, sizeof(c->ws_id) - 1);
    
    return 0;
}

void yai_rpc_close(yai_rpc_client_t *c) {
    if (c && c->fd >= 0) {
        close(c->fd);
        c->fd = -1;
    }
}

/**
 * Esegue la chiamata RPC iniettando 'bin' (L1/L2/L3) e 'ws_id'.
 */
int yai_rpc_call(
    yai_rpc_client_t *c,
    const char *bin,         // Nuovo: specifica se kernel, engine o mind
    const char *request_type,
    const char *payload_json,
    char *out_line,
    size_t out_cap
) {
    if (!c || c->fd < 0) return -1;
    
    char trace_id[64];
    yai_make_trace_id(trace_id);

    // Costruiamo il JSONL con la nuova struttura multi-tenant ADR-004
    char buf[YAI_RPC_LINE_MAX];
    
    // NOTA: yai_build_request_jsonl deve essere aggiornato per accettare 'bin'
    int rc = yai_build_v1_envelope(
        safe_cstr(bin),
        safe_cstr(c->ws_id),
        trace_id,
        request_type,
        payload_json ? payload_json : "{}",
        buf,
        sizeof(buf)
    );
    
    if (rc != 0) return -4;

    if (write_all(c->fd, buf, strlen(buf)) != 0) return -5;

    int r = read_line(c->fd, out_line, out_cap);
    return (r > 0) ? 0 : -6;
}

int yai_rpc_handshake(yai_rpc_client_t *c, const char *bin, const char *cv) {
    char payload[256];
    snprintf(payload, sizeof(payload), "{\"version\":\"%s\"}", safe_cstr(cv));
    char line[1024];
    return yai_rpc_call(c, bin, "handshake", payload, line, sizeof(line));
}
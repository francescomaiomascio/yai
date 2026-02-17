#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>

#include "yai_kernel.h"
#include "control_transport.h"

#include <transport.h>
#include <yai_protocol_ids.h>
#include <protocol.h>

#define YAI_BINARY_PAYLOAD_MAX 65536

/* ============================================================
   Internal: send a binary frame (envelope + payload)
============================================================ */
static void send_frame(
    int fd,
    const yai_rpc_envelope_t *req,
    uint32_t command_id,
    const void *payload,
    uint32_t payload_len
) {
    yai_rpc_envelope_t resp;
    memset(&resp, 0, sizeof(resp));

    resp.magic       = YAI_FRAME_MAGIC;
    resp.version     = YAI_PROTOCOL_IDS_VERSION;
    resp.command_id  = command_id;
    resp.payload_len = payload_len;

    strncpy(resp.ws_id, req->ws_id, sizeof(resp.ws_id) - 1);
    strncpy(resp.trace_id, req->trace_id, sizeof(resp.trace_id) - 1);

    resp.role     = 0;
    resp.arming   = 0;
    resp.checksum  = 0;

    yai_control_write_frame(fd, &resp, payload);
}

/* ============================================================
   Binary connection handler (one-shot, Root or WS)
============================================================ */
void yai_kernel_handle_binary_connection(int cfd)
{
    yai_rpc_envelope_t env;
    char payload[YAI_BINARY_PAYLOAD_MAX + 1];

    ssize_t r = yai_control_read_frame(
        cfd,
        &env,
        payload,
        sizeof(payload) - 1
    );

    if (r < 0) {
        close(cfd);
        return;
    }

    printf("[KERNEL] RECV cmd=%u len=%u role=%u arming=%u\n",
           env.command_id,
           env.payload_len,
           env.role,
           env.arming);

    /* -------- Strict protocol validation -------- */
    if (env.magic != YAI_FRAME_MAGIC || env.version != YAI_PROTOCOL_IDS_VERSION) {
        close(cfd);
        return;
    }

    /* -------- HANDSHAKE -------- */
    if (env.command_id == YAI_CMD_HANDSHAKE) {

        if ((size_t)r != sizeof(yai_handshake_req_t)) {
            close(cfd);
            return;
        }

        yai_handshake_req_t *req = (yai_handshake_req_t *)payload;
        yai_handshake_ack_t ack;
        memset(&ack, 0, sizeof(ack));

        ack.server_version       = YAI_PROTOCOL_IDS_VERSION;
        ack.capabilities_granted = req->capabilities_requested;
        ack.session_id           = 1;
        ack.status               = YAI_PROTO_STATE_READY;

        send_frame(cfd, &env, YAI_CMD_HANDSHAKE, &ack, sizeof(ack));
        printf("[KERNEL] Handshake OK\n");
        close(cfd);
        return;
    }

    /* -------- PING / Root Status -------- */
    if (env.command_id == YAI_CMD_PING) {

        // Distinguish between Root Plane and WS if needed
        const char *pong;
        if (strcmp(env.ws_id, "root") == 0) {
            pong = "{\"status\":\"pong\",\"plane\":\"root\"}";
        } else {
            pong = "{\"status\":\"pong\"}";
        }

        send_frame(cfd, &env, YAI_CMD_PING, pong, (uint32_t)strlen(pong));
        printf("[KERNEL] Pong sent\n");
        close(cfd);
        return;
    }

    /* -------- DEFAULT RESPONSE -------- */
    const char *ok = "{\"status\":\"ok\"}";
    send_frame(cfd, &env, env.command_id, ok, (uint32_t)strlen(ok));
    close(cfd);
}

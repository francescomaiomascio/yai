#pragma once

#include "../../law/specs/protocol/transport.h"       // definizione yai_rpc_envelope_t
#include "../../law/specs/protocol/yai_protocol_ids.h" // YAI_PROTOCOL_IDS_VERSION
#include <stdbool.h>
#include <string.h>

/* ============================================================
   VALIDAZIONE ENVELOPE LATO KERNEL
============================================================ */
static inline bool yai_envelope_validate_kernel(
    const yai_rpc_envelope_t* env,
    const char* expected_ws_id)
{
    if (!env) return false;
    if (env->magic != YAI_FRAME_MAGIC) return false;
    if (env->version != YAI_PROTOCOL_IDS_VERSION) return false;

    if (!expected_ws_id || expected_ws_id[0] == '\0')
        return true; // skip check se non richiesto

    if (strncmp(env->ws_id, expected_ws_id, sizeof(env->ws_id)) != 0)
        return false;

    // checksum eventualmente aggiunto qui
    return true;
}

/* ============================================================
   PREPARA ACK LATO KERNEL
============================================================ */
static inline void yai_envelope_prepare_ack_kernel(
    yai_rpc_envelope_t* out,
    const yai_rpc_envelope_t* request)
{
    if (!out || !request) return;

    memset(out, 0, sizeof(*out));
    out->magic       = YAI_FRAME_MAGIC;
    out->version     = YAI_PROTOCOL_IDS_VERSION;
    out->command_id  = request->command_id;
    out->payload_len = 0;

    strncpy(out->ws_id, request->ws_id, sizeof(out->ws_id) - 1);
    strncpy(out->trace_id, request->trace_id, sizeof(out->trace_id) - 1);

    out->role      = 0;
    out->arming    = 0;
    out->checksum  = 0;
}

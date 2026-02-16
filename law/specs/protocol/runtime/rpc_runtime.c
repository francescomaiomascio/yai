/**
 * @file rpc_runtime.c
 * @brief Implementation of YAI RPC runtime helpers.
 */

#include "rpc_runtime.h"

#include <protocol/yai_protocol_ids.h>
#include <string.h>
#include <stdio.h>

/**
 * @brief Validate an RPC envelope.
 */
bool yai_envelope_validate(
    const yai_rpc_envelope_t* env,
    const char* expected_ws_id)
{
    if (!env)
        return false;

    if (env->magic != YAI_FRAME_MAGIC)
        return false;

    if (env->version != YAI_PROTOCOL_IDS_VERSION)
        return false;

    if (!expected_ws_id || expected_ws_id[0] == '\0')
        return true;

    if (strncmp(env->ws_id,
                expected_ws_id,
                sizeof(env->ws_id)) != 0)
        return false;

    return true;
}

/**
 * @brief Prepare an ACK envelope.
 */
void yai_envelope_prepare_ack(
    yai_rpc_envelope_t* out,
    const yai_rpc_envelope_t* request)
{
    if (!out || !request)
        return;

    memset(out, 0, sizeof(*out));

    out->magic       = YAI_FRAME_MAGIC;
    out->version     = YAI_PROTOCOL_IDS_VERSION;
    out->command_id  = request->command_id;
    out->payload_len = 0;

    /* Safe copy */
    snprintf(out->ws_id,
             sizeof(out->ws_id),
             "%s",
             request->ws_id);

    snprintf(out->trace_id,
             sizeof(out->trace_id),
             "%s",
             request->trace_id);

    out->role     = 0;
    out->arming   = 0;
    out->checksum = 0;
}

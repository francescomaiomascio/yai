#pragma once

#include <stdbool.h>
#include <protocol/transport.h>
#include <protocol/protocol.h>   /* <-- IMPORTANTE */

#ifdef __cplusplus
extern "C" {
#endif

bool yai_envelope_validate(
    const yai_rpc_envelope_t* env,
    const char* expected_ws_id);

void yai_envelope_prepare_response(
    yai_rpc_envelope_t* out,
    const yai_rpc_envelope_t* request,
    uint32_t command_id,
    uint32_t payload_len);

#ifdef __cplusplus
}
#endif

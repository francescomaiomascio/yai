#pragma once

/**
 * @file rpc_runtime.h
 * @brief Runtime helpers for YAI RPC envelope handling.
 *
 * This module centralizes:
 *  - Envelope validation
 *  - ACK preparation
 *
 * It must be the ONLY implementation of envelope helpers
 * across Root, Kernel, Engine and CLI.
 */

#include <stdbool.h>
#include <protocol/transport.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Validate an incoming RPC envelope.
 *
 * Performs:
 *  - Magic validation
 *  - Protocol version validation
 *  - Optional workspace ID validation
 *
 * @param env Pointer to envelope.
 * @param expected_ws_id Expected workspace ID (NULL or empty to skip check).
 *
 * @return true if valid, false otherwise.
 */
bool yai_envelope_validate(
    const yai_rpc_envelope_t* env,
    const char* expected_ws_id);

/**
 * @brief Prepare an ACK envelope from a request.
 *
 * Initializes:
 *  - magic
 *  - version
 *  - command_id
 *  - ws_id
 *  - trace_id
 *
 * Payload length is set to zero.
 *
 * @param out Output envelope.
 * @param request Original request envelope.
 */
void yai_envelope_prepare_ack(
    yai_rpc_envelope_t* out,
    const yai_rpc_envelope_t* request);

#ifdef __cplusplus
}
#endif

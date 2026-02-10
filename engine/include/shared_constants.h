#ifndef YAI_SHARED_CONSTANTS_H
#define YAI_SHARED_CONSTANTS_H

// Engine Lifecycle
#define STATUS_OFFLINE    0
#define STATUS_BOOTING    1
#define STATUS_READY      2
#define STATUS_BUSY       3
#define STATUS_ERROR      4
#define STATUS_PANIC      5

// Costanti di Rete e IPC
#include "yai_protocol_ids.h"
#include "yai_vault_abi.h"
#include "yai_vault.h"

#ifndef YAI_PROTOCOL_IDS_VERSION
#error "Missing Law-generated yai_protocol_ids.h"
#endif
#define SOCKET_RUNTIME_PATH "/tmp/yai_runtime.sock"

// Limiti Risorse
#define MAX_WS_ID 64
#define MAX_TRACE_ID 64
#define MAX_ERR_MSG 256

#endif

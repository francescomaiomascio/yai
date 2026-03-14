#pragma once

#ifndef INCLUDE_IPC_TYPES_H
#define INCLUDE_IPC_TYPES_H

#include <stdint.h>

typedef uint64_t yai_ipc_channel_id_t;
typedef uint64_t yai_ipc_session_id_t;
typedef uint64_t yai_ipc_message_id_t;

enum yai_ipc_message_kind {
    YAI_IPC_MESSAGE_UNKNOWN = 0,
    YAI_IPC_MESSAGE_REQUEST,
    YAI_IPC_MESSAGE_RESPONSE,
    YAI_IPC_MESSAGE_EVENT,
    YAI_IPC_MESSAGE_CONTROL
};

#endif

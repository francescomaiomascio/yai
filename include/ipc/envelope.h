#pragma once

#ifndef INCLUDE_IPC_ENVELOPE_H
#define INCLUDE_IPC_ENVELOPE_H

#include <ipc/types.h>

struct yai_ipc_envelope {
    yai_ipc_message_id_t message_id;
    yai_ipc_channel_id_t channel_id;
    enum yai_ipc_message_kind kind;
};

#endif

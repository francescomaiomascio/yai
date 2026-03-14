#pragma once

#ifndef INCLUDE_TRANSPORT_DELIVERY_H
#define INCLUDE_TRANSPORT_DELIVERY_H

#include <transport/message.h>
#include <transport/result.h>

struct yai_transport_delivery {
    yai_transport_message_id_t message_id;
    enum yai_transport_result result;
};

#endif

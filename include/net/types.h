#pragma once

#ifndef INCLUDE_NET_TYPES_H
#define INCLUDE_NET_TYPES_H

#include <stdint.h>

typedef uint64_t yai_net_peer_id_t;
typedef uint64_t yai_net_route_id_t;
typedef uint64_t yai_net_session_id_t;

enum yai_net_plane_kind {
    YAI_NET_PLANE_UNKNOWN = 0,
    YAI_NET_PLANE_CONTROL,
    YAI_NET_PLANE_DISCOVERY,
    YAI_NET_PLANE_DATA,
    YAI_NET_PLANE_OVERLAY
};

#endif

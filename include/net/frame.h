#pragma once

#ifndef INCLUDE_NET_FRAME_H
#define INCLUDE_NET_FRAME_H

#include <net/types.h>

struct yai_net_frame {
    enum yai_net_plane_kind plane;
    unsigned int payload_size;
};

#endif

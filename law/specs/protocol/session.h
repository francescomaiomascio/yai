#ifndef YAI_PROTOCOL_SESSION_H
#define YAI_PROTOCOL_SESSION_H

#include <stdint.h>

/* ============================================================
   Session Status Codes (Handshake ACK)
   ============================================================ */

typedef enum {
    YAI_SESSION_DENIED = 0,
    YAI_SESSION_READY  = 1
} yai_session_status_t;

#endif

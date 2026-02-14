#ifndef YAI_PROTOCOL_H
#define YAI_PROTOCOL_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "yai_protocol_ids.h"
#include "transport.h"

#define YAI_PROTOCOL_MAGIC   0x59414950u /* 'Y''A''I''P' */
#define YAI_PROTOCOL_VERSION 1u

/* * Session States: Definisce cosa può fare il Mind in ogni momento.
 * L'Engine rifiuterà comandi STORAGE se lo stato non è almeno READY.
 */
typedef enum {
    YAI_PROTO_STATE_IDLE       = 0, // Appena connesso, attesa Handshake
    YAI_PROTO_STATE_HANDSHAKE  = 1, // Negoziazione versioni e capabilities
    YAI_PROTO_STATE_READY      = 2, // Operativo (Storage/Provider ok)
    YAI_PROTO_STATE_ARMED      = 3, // Privilegiato (Reconfigure/Delete ok)
    YAI_PROTO_STATE_ERROR      = 4  // Violazione protocollo o checksum fallito
} yai_proto_state_t;

/*
 * Capability Flags: Cosa sa fare questo specifico Engine?
 * Il Mind legge questi bit per sapere se può chiedere inferenze o meno.
 */
#define YAI_CAP_STORAGE     (1u << 0)
#define YAI_CAP_INFERENCE   (1u << 1)
#define YAI_CAP_VECTOR      (1u << 2)
#define YAI_CAP_ENCRYPTION  (1u << 3)

#pragma pack(push, 1)

/* Messaggio di Handshake (Payload del primo pacchetto) */
typedef struct yai_handshake_payload {
    uint32_t client_version;
    uint32_t capabilities_requested;
    char     client_name[32];
} yai_handshake_payload_t;

/* Risposta di Handshake dall'Engine */
typedef struct yai_handshake_ack {
    uint32_t server_version;
    uint32_t capabilities_granted;
    uint16_t session_id;
    uint8_t  status; // yai_proto_state_t
} yai_handshake_ack_t;

#pragma pack(pop)

#endif /* YAI_PROTOCOL_H */
#ifndef YAI_PROTOCOL_COMMANDS_H
#define YAI_PROTOCOL_COMMANDS_H

#include <stdint.h>
#include <stddef.h>

#define YAI_MAX_COMMAND_PAYLOAD 1024u

typedef enum yai_command_id {
    YAI_CMD_NONE = 0,
    YAI_CMD_PING = 1,
    YAI_CMD_NOOP = 2
} yai_command_id_t;

#ifndef ICE_CMD_PING
#define ICE_CMD_PING YAI_CMD_PING
#endif
#ifndef ICE_CMD_NOOP
#define ICE_CMD_NOOP YAI_CMD_NOOP
#endif

#pragma pack(push, 1)
typedef struct yai_command_envelope {
    uint32_t magic;
    uint32_t version;
    uint32_t command_id;
    uint32_t seq;
    uint32_t payload_len;
    uint32_t reserved;
} yai_command_envelope_t;
#pragma pack(pop)

_Static_assert(sizeof(yai_command_envelope_t) == 24, "yai_command_envelope_t size mismatch");

#endif /* YAI_PROTOCOL_COMMANDS_H */
